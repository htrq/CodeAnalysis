#ifndef LINUX_TERMINAL_HPP_HTRQ
#define LINUX_TERMINAL_HPP_HTRQ
#include <FL/Fl_Terminal.H>

class linuxTerminal : public Fl_Terminal {
  Fl_Terminal *flTerminal{};
  static constexpr int rows{12};
  static constexpr int cols{89};
  int master_fd;

public:
  linuxTerminal(int X, int Y, int W, int H, const char *label = nullptr)
      : Fl_Terminal(X, Y, W, H, label) {
    ansi(true);
    show_unknown(false);

    display_rows(rows);
    history_lines(1000);

    scrollbar_size(12);
  }
  ~linuxTerminal();
  void enterFirstPromt();
  void makeTerminalKeyboardEventHandler();
  int handle(int event) override;
  void createPTY();
  static void pty_cb(int fd, void *userdata);
};

#endif