//
// Created by sean on 14/02/23.
//
// https://chat.openai.com/chat using prompt "generate a c++ program for a simple video game including obstacles and enemies"
//

#include <ncurses.h>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

// Define a struct for the enemy objects
struct Enemy {
    int x;
    int y;
    char symbol;
    int color_pair;
};

// Function prototypes
void moveEnemies(Enemy enemies[], int num_enemies, int player_x, int player_y);

int main() {
    // Initialize ncurses
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, true);
    start_color();
    srand(time(nullptr));

    // Define the player object
    int player_x = 10;
    int player_y = 10;
    char player_symbol = '@';
    int player_color_pair = 1;

    // Define the enemy objects
    int num_enemies = 5;
    Enemy enemies[num_enemies];
    for (int i = 0; i < num_enemies; i++) {
        enemies[i].x = rand() % 40;
        enemies[i].y = rand() % 20;
        enemies[i].symbol = 'E';
        enemies[i].color_pair = 2;
    }

    // Define color pairs
    init_pair(player_color_pair, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);

    // Start the game loop
    int ch = 0;
    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);
    while (ch != 'q') {
        // Clear the screen
        clear();

        // Draw the player
        attron(COLOR_PAIR(player_color_pair));
        mvaddch(player_y, player_x, player_symbol);
        attroff(COLOR_PAIR(player_color_pair));

        // Draw the enemies
        for (int i = 0; i < num_enemies; i++) {
            attron(COLOR_PAIR(enemies[i].color_pair));
            mvaddch(enemies[i].y, enemies[i].x, enemies[i].symbol);
            attroff(COLOR_PAIR(enemies[i].color_pair));
        }

        // Move the enemies
        moveEnemies(enemies, num_enemies, player_x, player_y);

        // Handle user input
        switch(ch) {
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

void moveEnemies(Enemy enemies[], int num_enemies, int player_x, int player_y) {
    for (int i = 0; i < num_enemies; i++) {
        // Calculate the distance between the enemy and the player
        int dist_x = player_x - enemies[i].x;
        int dist_y = player_y - enemies[i].y;
        int dist = sqrt(dist_x * dist_x + dist_y * dist_y);

        // If the enemy is close enough to the player, move it toward the player

        if (dist <= 5) {
        // Calculate the direction to move in
            int dir_x = 0;
            if (player_x > enemies[i].x)
                dir_x = 1;
            else if (player_x < enemies[i].x)
                dir_x = -1;
            
            int dir_y = 0;
            if (player_y > enemies[i].y)
                dir_y = 1;
            else if (player_y < enemies[i].y)
                dir_y = -1;

            // Move the enemy in the chosen direction
            if (enemies[i].x + dir_x >= 0 && enemies[i].x + dir_x < COLS)
                enemies[i].x += dir_x;
            if (enemies[i].y + dir_y >= 0 && enemies[i].y + dir_y < LINES)
                enemies[i].y += dir_y;
        }
    }
}