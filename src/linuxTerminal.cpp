#include "../include/linuxTerminal.hpp"
#include <FL/Fl.H>
#include <FL/Enumerations.H>
#include <FL/Fl_Terminal.H>
#include <FL/fl_utf8.h>
#include <cstdio>
#include <cstdlib>
#include <print>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <asm/termbits.h> 


void linuxTerminal::enterFirstPromt() { append("echo \"Hellow world\""); }


int linuxTerminal::handle(int event) {
  if (event == FL_KEYDOWN) {
    int key = Fl::event_key();
    const char* text = Fl::event_text();
      std::println("key {} was pushed", key);
  }

  // ВАЖНО: передать событие родителю
  return Fl_Terminal::handle(event);
}

void linuxTerminal::createPTY()
{
  master_fd = posix_openpt(O_RDWR | O_NOCTTY);
  if (master_fd < 0) {
    perror("posix_openpt");
    exit(1);
  }
  grantpt(master_fd);
  unlockpt(master_fd);
  char* slave_name = ptsname(master_fd);

  pid_t pid = fork();
  if (pid == 0) {
    setsid();
    int slave_fd = open(slave_name, O_RDWR);
    ioctl(slave_fd, TIOCSCTTY, 0);

    dup2(slave_fd, STDIN_FILENO);
    dup2(slave_fd, STDOUT_FILENO);
    dup2(slave_fd, STDERR_FILENO);

    close(master_fd);
    close(slave_fd);

    execlp("bash", "bash", nullptr);
    perror("execlp");
    exit(1);
  }
  Fl::add_fd(master_fd, FL_READ, linuxTerminal::pty_cb, this);
}

void linuxTerminal::pty_cb(int fd, void* userdata) {
    auto* self = static_cast<linuxTerminal*>(userdata);
    char buf[4096];
    ssize_t n = read(fd, buf, sizeof(buf));
    if (n > 0) {
        self->append(buf, n);
    }
}

linuxTerminal::~linuxTerminal() = default;