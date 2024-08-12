#ifndef TERMINAL_IO_H
#define TERMINAL_IO_H

#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/select.h>

static struct termios oldt, newt;

void initTermios(int echo)
{
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ICANON;
    if (!echo)
    {
        newt.c_lflag &= ~ECHO;
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void resetTermios()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

int key_pressed(void)
{
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}

#endif