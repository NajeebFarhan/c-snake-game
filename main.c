#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "terminal_io.h"

#define ROWS 15
#define COLS 60

void renderfield();
void keepbound();
void controls(char key);

int xpos = 0;
int ypos = 0;
int xspeed = 1;
int yspeed = 0;

int main()
{
    // Hide cursor
    printf("\e[?25l");

    char key;

    initTermios(0); // Initialize with no echo

    //! something wrong with this thing, just let it be commented for eternity
    // fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK); // Make stdin non-blocking

    printf("Press q to quite\n");

    while (key != 'q')
    {
        renderfield();

        // Move cursor back to top for rerendering
        printf("\e[%iA", ROWS + 2);

        // For faster rendering
        fflush(stdout);

        // for some delay or shet go zoom
        if (key_pressed())
        {
            key = getchar();

            // Controlling the player entity
            controls(key);
        }

        usleep(150000);
        xpos += xspeed;
        ypos += yspeed;
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

    keepbound();
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

void controls(char key)
{
    switch (key)
    {
    case 'w':
        yspeed = -1;
        xspeed = 0;
        break;
    case 's':
        yspeed = 1;
        xspeed = 0;
        break;
    case 'a':
        yspeed = 0;
        xspeed = -1;
        break;
    case 'd':
        yspeed = 0;
        xspeed = 1;
        break;
    default:
        break;
    }
}