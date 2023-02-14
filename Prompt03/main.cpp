//
// Created by sean on 14/02/23.
//
// https://chat.openai.com/chat using prompt "generate a c++ program for a simple video game including obstacles and enemies"
//


#include <iostream>
#include <vector>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>

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

// Function to move enemies randomly
void moveEnemies(vector<Enemy>& enemies, int max_x, int max_y)
{
    for (Enemy& enemy : enemies)
    {
        int dx = rand() % 3 - 1;
        int dy = rand() % 3 - 1;
        if (enemy.x + dx >= 0 && enemy.x + dx < max_x)
            enemy.x += dx;
        if (enemy.y + dy >= 0 && enemy.y + dy < max_y)
            enemy.y += dy;
    }
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

    keypad(stdscr, TRUE);       // sb added this to make it work



    srand(time(NULL));  // Seed the random number generator

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

        // Draw the enemies and move them randomly
        moveEnemies(enemies, max_x, max_y);
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

    // Refresh the screen
    refresh();

    // Get the maximum x and y coordinates of the screen
    getmaxyx(stdscr, max_y, max_x);

    // Wait for user input or a short time delay
    ch = getch();
    napms(50);
}

// Clean up ncurses
endwin();

return 0;

}


