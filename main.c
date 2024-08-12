#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "terminal_io.h"

#define ROWS 15
#define COLS 60

void renderfield();

int xpos = 0;
int ypos = 0;

int main()
{
    // Hide cursor
    printf("\e[?25l");

    char key;

    initTermios(0); // Initialize with no echo

    //! something wrong with this thing, just let be commented for eternity
    // fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK); // Make stdin non-blocking

    while (key != 'q')
    {
        renderfield();

        // Move cursor back to top
        printf("\e[%iA", ROWS + 2);

        // usleep(50000);

        if (key_pressed())
        {
            key = getchar();

            switch (key)
            {
            case 'w':
                ypos--;
                break;
            case 's':
                ypos++;
                break;
            case 'a':
                xpos--;
                break;
            case 'd':
                xpos++;
                break;
            default:
                break;
            }
        }
    };

    // Show cursor
    printf("\e[?25h");
    resetTermios(); // Restore terminal settings
    // Clear screen
    printf("\e[2J\e[H");

    fflush(stdin);

    return 0;
}

void renderfield()
{
    for (int i = 0; i < COLS + 2; i++)
        printf("-");
    printf("\n");

    for (int i = 0; i < ROWS; i++)
    {
        printf("|");
        for (int j = 0; j < COLS; j++)
        {
            if (i == ypos && j == xpos)
            {
                printf("O");
            }
            else
                printf(".");
        }
        printf("|\n");
    }

    for (int i = 0; i < COLS + 2; i++)
        printf("-");
    printf("\n");

    // printf("\e[%iA", ROWS + 3);
}
