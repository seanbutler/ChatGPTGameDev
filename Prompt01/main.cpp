//
// Created by sean on 14/02/23.
//
// https://chat.openai.com/chat using prompt "generate a c++ program for a simple video game"
//


#include <iostream>
#include <ncurses.h>

using namespace std;

int main()
{
    // Initialize ncurses
    initscr();
    noecho();
    curs_set(0);

    // Set up game variables
    int x = 0, y = 0;
    int max_x = 0, max_y = 0;
    int ch = 0;

    // Get screen size
    getmaxyx(stdscr, max_y, max_x);

    // Main game loop
    while (ch != 'q')
    {
        // Clear the screen
        clear();

        // Draw the player character
        mvprintw(y, x, "O");

        // Move the player character based on user input
        switch (ch)
        {
            case KEY_UP:
                if (y > 0)
                    y--;
                break;
            case KEY_DOWN:
                if (y < max_y - 1)
                    y++;
                break;
            case KEY_LEFT:
                if (x > 0)
                    x--;
                break;
            case KEY_RIGHT:
                if (x < max_x - 1)
                    x++;
                break;
        }

        // Refresh the screen
        refresh();

        // Get user input
        ch = getch();
    }

    // Clean up ncurses
    endwin();

    return 0;
}
