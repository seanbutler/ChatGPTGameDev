#include <ncurses.h>
#include <cstdlib>
#include <vector>

using namespace std;

// Define the dimensions of the screen and the cave
const int _LINES = 25;
const int _COLS = 80;
const int CAVE_HEIGHT = 20;
const int CAVE_WIDTH = 60;

// Define a struct for enemy objects
struct Enemy {
    int x;
    int y;
};

int main() {
    // Initialize ncurses
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);
    start_color();

    // Define the color pairs to use for the cave and objects
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);

    // Draw the cave background
    attron(COLOR_PAIR(1));
    for (int i = 0; i < _LINES; i++) {
        for (int j = 0; j < _COLS; j++) {
            if (i < CAVE_HEIGHT || i >= _LINES - CAVE_HEIGHT || j < (_COLS - CAVE_WIDTH) / 2 || j >= (_COLS + CAVE_WIDTH) / 2) {
                mvaddch(i, j, ' ');
            } else {
                mvaddch(i, j, '.');
            }
        }
    }

    // Draw the walls to enclose the player and enemies
    attron(COLOR_PAIR(3));
    for (int i = 0; i < CAVE_HEIGHT; i++) {
        mvaddch(i, (_COLS - CAVE_WIDTH) / 2, '|');
        mvaddch(i, (_COLS + CAVE_WIDTH) / 2 - 1, '|');
    }
    for (int i = 0; i < CAVE_WIDTH; i++) {
        mvaddch(CAVE_HEIGHT, (_COLS - CAVE_WIDTH) / 2 + i, '-');
        mvaddch(_LINES - CAVE_HEIGHT - 1, (_COLS - CAVE_WIDTH) / 2 + i, '-');
    }

    // Initialize the player and enemies
    int player_x = _COLS / 2;
    int player_y = _LINES / 2;
    vector<Enemy> enemies = {{_COLS / 4, _LINES / 4}, {3 * _COLS / 4, _LINES / 4}, {_COLS / 4, 3 * _LINES / 4}, {3 * _COLS / 4, 3 * _LINES / 4}};

    // Game loop
    while (true) {
        // Clear the previous player position and draw the new one
        mvaddch(player_y, player_x, ' ');
        attron(COLOR_PAIR(4));
        mvaddch(player_y, player_x, '@');

        // Clear the previous enemy positions and draw the new ones
        for (int i = 0; i < enemies.size(); i++) {
            mvaddch(enemies[i].y, enemies[i].x, ' ');
            attron(COLOR_PAIR(2));
            mvaddch(enemies[i].y, enemies[i].x, 'E');
        }

        // Get player input
        int ch = getch();
        switch (ch) {
            case KEY_UP:
                if (player_y > CAVE_HEIGHT)
                    player_y--;
                break;

            case KEY_DOWN:
                if (player_y < _LINES - CAVE_HEIGHT - 1)
                    player_y++;
                break;
            case KEY_LEFT:
                if (player_x > (_COLS - CAVE_WIDTH) / 2)
                    player_x--;
                break;
            case KEY_RIGHT:
                if (player_x < (_COLS + CAVE_WIDTH) / 2 - 1)
                    player_x++;
                break;
            case 'q':
            case 'Q':
                endwin();
                return 0;
        }

        // Move the enemies toward the player
        for (int i = 0; i < enemies.size(); i++) {
            if (enemies[i].x < player_x) {
                enemies[i].x++;
            } else if (enemies[i].x > player_x) {
                enemies[i].x--;
            }
            if (enemies[i].y < player_y) {
                enemies[i].y++;
            } else if (enemies[i].y > player_y) {
                enemies[i].y--;
            }
        }

        // Check for collisions between the player and enemies
        for (int i = 0; i < enemies.size(); i++) {
            if (enemies[i].x == player_x && enemies[i].y == player_y) {
                endwin();
                return 0;
            }
        }

        // Refresh the screen
        refresh();
    }
}


