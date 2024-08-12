#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "terminal_io.h"

#define ROWS 15
#define COLS 60

void renderfield();
void keepbound();

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

    printf("Press q to quite\n");

    while (key != 'q')
    {
        keepbound();
        renderfield();

        // Move cursor back to top for rerendering
        printf("\e[%iA", ROWS + 2);

        // For faster rendering
        fflush(stdout);

        // for some delay or shet go zoom
        usleep(20000);
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

void keepbound()
{
    if (xpos > COLS - 1)
    {
        xpos = 0;
    }
    if (xpos < 0)
    {
        xpos = COLS - 1;
    }
    if (ypos > ROWS - 1)
    {
        ypos = 0;
    }
    if (ypos < 0)
    {
        ypos = ROWS - 1;
    }
}