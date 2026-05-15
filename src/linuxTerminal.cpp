#include "../include/linuxTerminal.hpp"
#include <FL/Enumerations.H>
#include <FL/Fl.H>
#include <FL/Fl_Terminal.H>
#include <FL/fl_utf8.h>
#include <asm/termbits.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <print>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <unistd.h>
#include <regex>

void linuxTerminal::enterFirstPromt() { write(master_fd, "Hellow world\n", 16); }

int linuxTerminal::handle(int event) {
  if (event == FL_KEYDOWN) {
    int key = Fl::event_key();
    const char *text = Fl::event_text();
    size_t size = strlen(text);
    std::println("key {} was pushed", key);
    std::println("Scrollbar size: {}", scrollbar_size());

    switch (key) {
    case FL_BackSpace:
      write(master_fd, "\x7f", 1);
      break;
    case FL_Enter:
      write(master_fd, "\n", 1);
      break;
    case FL_Up:
      write(master_fd, "\x1b[A", 3);
      break;
    case FL_Down:
      write(master_fd, "\x1b[B", 3);
      break;
    default: 
      write(master_fd, text, size);
    }
    return 1;
  }

  return Fl_Terminal::handle(event);
}

void linuxTerminal::createPTY() {
    master_fd = posix_openpt(O_RDWR | O_NOCTTY);
    if (master_fd < 0) {
        perror("posix_openpt");
        exit(1);
    }

    grantpt(master_fd);
    unlockpt(master_fd);

    char *slave_name = ptsname(master_fd);

    pid_t pid = fork();

    if (pid == 0) {
        setsid();

        int slave_fd = open(slave_name, O_RDWR);

        ioctl(slave_fd, TIOCSCTTY, 0);

        winsize ws{};
        ws.ws_row = 24;
        ws.ws_col = 80;
        ioctl(slave_fd, TIOCSWINSZ, &ws);

        dup2(slave_fd, STDIN_FILENO);
        dup2(slave_fd, STDOUT_FILENO);
        dup2(slave_fd, STDERR_FILENO);

        close(master_fd);
        close(slave_fd);

        setenv("TERM", "xterm-256color", 1);

        execlp("bash", "bash", nullptr);

        perror("execlp");
        exit(1);
    }

    Fl::add_fd(master_fd, FL_READ,
               linuxTerminal::pty_cb, this);
}

void linuxTerminal::pty_cb(int fd, void *userdata)
{
    auto *self = static_cast<linuxTerminal *>(userdata);

    char buf[4096];
    ssize_t n = read(fd, buf, sizeof(buf));

    if (n <= 0)
        return;

    std::string out;
    out.reserve(n);

    for (ssize_t i = 0; i < n; ++i)
    {
        // ESC
        if (buf[i] == '\x1b')
        {
            // CSI: ESC[?2004h/l
            if (i + 1 < n && buf[i + 1] == '[')
            {
                while (i < n &&
                       !std::isalpha(buf[i]))
                {
                    ++i;
                }
                continue;
            }

            // OSC: ESC ] ... BEL
            if (i + 1 < n && buf[i + 1] == ']')
            {
                i += 2;

                while (i < n && buf[i] != '\a')
                    ++i;

                continue;
            }
        }

        out += buf[i];
    }

    self->append(out.c_str());
}

linuxTerminal::~linuxTerminal() { Fl::remove_fd(master_fd); };