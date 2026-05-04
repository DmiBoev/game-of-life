#include "playlive.h"

int main() {
    int *f1 = (int *)calloc(WIDTH * HEIGHT, sizeof(int));
    int *f2 = (int *)calloc(WIDTH * HEIGHT, sizeof(int));

    int speed = 10;
    int iter = 0;
    int status = 1;

    if (f1 == NULL || f2 == NULL) {
        status = 0;
    }

    if (status) {
        int cells_read = 0;
        for (int i = 0; i < HEIGHT * WIDTH; i++) {
            if (scanf("%1d", &f1[i]) == 1) {
                cells_read++;
            }
        }
        if (cells_read == 0) {
            fprintf(stderr, "Error. No File.\n");
            status = 0;
        }
    }

    if (status) {
        if (freopen("/dev/tty", "r", stdin) != NULL) {
            initscr();
            noecho();
            cbreak();
            keypad(stdscr, TRUE);
            curs_set(0);
            runGame(&f1, &f2, &speed, &iter);

            endwin();
        } else {
            fprintf(stderr, "Error. No open terminal.\n");
            status = 0;
        }
    }

    if (f1 != NULL) free(f1);
    if (f2 != NULL) free(f2);

    return status ? 0 : 1;
}

int handleInputDelay(int *speed_level, int **current, int *iteration, int *game_active) {
    int elapsed = 0;
    int targetDelay = 2100 - (*speed_level * 100);

    while (elapsed < targetDelay && *game_active) {
        int ch = getch();
        if (ch != ERR) {
            if (ch == ' ') {
                *game_active = 0;
            } else if ((ch == 'a' || ch == 'A') && *speed_level < 20) {
                (*speed_level)++;
            } else if ((ch == 'z' || ch == 'Z') && *speed_level > 1) {
                (*speed_level)--;
            }

            if (*game_active) {
                targetDelay = 2100 - (*speed_level * 100);
                drawBoard(*current, *speed_level, *iteration, "A/Z: Speed | SPACE: Exit");
            }
        }
        if (*game_active) {
            napms(10);
            elapsed += 10;
        }
    }
    return *game_active;
}

void runGame(int **current, int **next, int *speed_level, int *iteration) {
    int game_active = 1;
    nodelay(stdscr, TRUE);

    while (game_active) {
        drawBoard(*current, *speed_level, *iteration, "A/Z: Speed | SPACE: Exit");

        if (!isAnyoneAlive(*current)) {
            drawBoard(*current, *speed_level, *iteration, "ALL DEAD. PRESS ANY KEY.");
            timeout(-1);
            getch();
            game_active = 0;
        }

        if (game_active) {
            handleInputDelay(speed_level, current, iteration, &game_active);
        }

        if (game_active) {
            if (!stateTick(current, next, iteration)) {
                drawBoard(*current, *speed_level, *iteration, "STABILIZED. PRESS ANY KEY.");
                timeout(-1);
                getch();
                game_active = 0;
            }
        }
    }
}

int isAnyoneAlive(const int *field) {
    for (int i = 0; i < HEIGHT * WIDTH; i++)
        if (field[i]) return 1;
    return 0;
}

int countNeighbors(const int *field, int r, int c) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i != 0 || j != 0) {
                int row = (r + i + HEIGHT) % HEIGHT;
                int col = (c + j + WIDTH) % WIDTH;
                count += field[row * WIDTH + col];
            }
        }
    }
    return count;
}

int stateTick(int **current, int **next, int *iteration) {
    int changed = 0;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int n = countNeighbors(*current, i, j);
            int alive = (*current)[i * WIDTH + j];
            int res = (alive && (n == 2 || n == 3)) || (!alive && n == 3);

            if (res != alive) changed = 1;
            (*next)[i * WIDTH + j] = res;
        }
    }
    int *temp = *current;
    *current = *next;
    *next = temp;
    (*iteration)++;
    return changed;
}

void drawBoard(int *current, int speed_level, int iteration, const char *msg) {
    erase();
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            mvaddch(i, j, current[i * WIDTH + j] ? '@' : '.');
        }
    }
    mvprintw(HEIGHT, 0, "Iter: %d | Speed: [%d/20] | %s", iteration, speed_level, msg);
    refresh();
}
