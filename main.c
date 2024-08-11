#include <stdio.h>
#include <unistd.h>
#include "terminal_io.h"

#define ROWS 15
#define COLS 60

void renderfield();

int main()
{
    // Hide cursor
    printf("\e[?25l");

    char key;

    initTermios(0);                           // Initialize with no echo
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK); // Make stdin non-blocking

    do
    {
        renderfield();

        // Move cursor back to top
        printf("\e[%iA", ROWS + 10);

        if (kbhit())
        {
            key = getchar();
            if (key == 'q')
                break;
        }
    } while (1);

    // Show cursor
    printf("\e[?25h");
    resetTermios(); // Restore terminal settings
    // Clear screen
    // printf("\e[2J\e[H");

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
            printf(".");
        printf("|\n");
    }

    for (int i = 0; i < COLS + 2; i++)
        printf("-");
    printf("\n");

    // printf("\e[%iA", ROWS + 3);
}
