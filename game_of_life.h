#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 80
#define HEIGHT 25

void runGame(int **current, int **next, int *speed_level, int *iteration);
int isAnyoneAlive(const int *field);
int countNeighbors(const int *field, int r, int c);
int stateTick(int **current, int **next, int *iteration);
void drawBoard(int *current, int speed_level, int iteration, const char *msg);
int handleInputDelay(int *speed_level, int **current, int *iteration, int *game_active);
