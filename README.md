# ChatGPTGameDev

## Prompt01

### prompt

"generate a c++ program for a simple video game"

## result

the generated code was acompanied by the text:

"Sure, here is an example C++ program for a simple video game using the ncurses library:"

~~~cpp
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

~~~

This program uses the ncurses library to create a simple game where the player can move a character around the screen using the arrow keys. The game loop clears the screen, draws the player character at the current position, moves the player character based on user input, and refreshes the screen. The loop continues until the user presses the 'q' key. This is just a simple example, but it could be expanded to include obstacles, enemies, and other game mechanics.


## discussion

it worked but its not a video game. 
apart from one line of code missing which was necessary to make ncurses read the arrow keys properly. added necessary code.
its almost as if its the starting code a course might give students to work from an initial shell to get them going.

![IMG](Prompt01.png)


# Prompt 02

## prompt

"generate a c++ program for a simple video game including obstacles and enemies"

## result 

Here is an example C++ program for a simple video game that includes obstacles and enemies, using the ncurses library

~~~cpp

#include <iostream>
#include <vector>
#include <ncurses.h>

using namespace std;

// Structs for game objects
struct GameObject
{
    int x, y;
    char symbol;
};

struct Obstacle : public GameObject
{
    Obstacle(int x, int y) { this->x = x; this->y = y; this->symbol = '#'; }
};

struct Enemy : public GameObject
{
    Enemy(int x, int y) { this->x = x; this->y = y; this->symbol = 'X'; }
};

// Function to check for collisions
bool checkCollision(int x1, int y1, int x2, int y2)
{
    return x1 == x2 && y1 == y2;
}

int main()
{
    // Initialize ncurses
    initscr();
    noecho();
    curs_set(0);

    // Set up game variables
    int player_x = 0, player_y = 0;
    int max_x = 0, max_y = 0;
    int ch = 0;

    // Set up obstacles and enemies
    vector<Obstacle> obstacles = { Obstacle(5, 5), Obstacle(10, 10), Obstacle(15, 15) };
    vector<Enemy> enemies = { Enemy(20, 20), Enemy(25, 25), Enemy(30, 30) };

    // Main game loop
    while (ch != 'q')
    {
        // Clear the screen
        clear();

        // Draw the player character
        mvprintw(player_y, player_x, "O");

        // Draw the obstacles
        for (Obstacle obstacle : obstacles)
        {
            mvprintw(obstacle.y, obstacle.x, "#");
            if (checkCollision(player_x, player_y, obstacle.x, obstacle.y))
            {
                // Game over
                mvprintw(max_y/2, max_x/2 - 5, "GAME OVER");
                refresh();
                getch();
                endwin();
                return 0;
            }
        }

        // Draw the enemies
        for (Enemy enemy : enemies)
        {
            mvprintw(enemy.y, enemy.x, "X");
            if (checkCollision(player_x, player_y, enemy.x, enemy.y))
            {
                // Game over
                mvprintw(max_y/2, max_x/2 - 5, "GAME OVER");
                refresh();
                getch();
                endwin();
                return 0;
            }
        }

        // Move the player character based on user input
        switch (ch)
        {
            case KEY_UP:
                if (player_y > 0)
                    player_y--;
                break;
            case KEY_DOWN:
                if (player_y < max_y - 1)
                    player_y++;
                break;
            case KEY_LEFT:
                if (player_x > 0)
                    player_x--;
                break;
            case KEY_RIGHT:
                if (player_x < max_x - 1)
                    player_x++;
                break;
        }

        // Get screen size
        getmaxyx(stdscr, max_y, max_x);

        // Refresh the screen
        refresh();

        // Get user input
        ch = getch();
    }

    // Clean up ncurses
    endwin();

    return 0;
}




~~~

This program builds on the previous example, adding obstacles and enemies to the game. The obstacles and enemies are stored in vectors of Obstacle and Enemy objects, respectively. The game loop draws the obstacles and enemies on the screen, checks for

( i think maybe it got a bit bored at this point as the text just stopped.)

