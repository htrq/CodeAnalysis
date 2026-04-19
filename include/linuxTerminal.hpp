#ifndef LINUX_TERMINAL_HPP_HTRQ
#define LINUX_TERMINAL_HPP_HTRQ
#include <FL/Fl_Terminal.H>



class linuxTerminal : public Fl_Terminal
{
    Fl_Terminal* flTerminal{};
    static constexpr int rows { 12 };
    static constexpr int cols { 89 };
    int master_fd;
public:
    using Fl_Terminal::Fl_Terminal;
    ~linuxTerminal();
    void enterFirstPromt();
    void makeTerminalKeyboardEventHandler();
    int handle(int event) override;
    void createPTY();
    static void pty_cb(int fd, void*);
};

#endif