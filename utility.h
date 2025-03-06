#ifndef UTILITY_H
#define UTILITY_H

#define GRID_SIZE 4
#define LEFT  0
#define RIGHT 1
#define UP    2
#define DOWN  3

void move_up(int board[4][4]);
void move_down(int board[4][4]);
void move_left(int board[4][4]);
void move_right(int board[4][4]);

void gameBoard(int array[4][4]);
void placeRandomTile(int array[4][4]);
int moveBoard(int array[4][4], int direction);
int gameOver(int array[4][4]);
int shiftTiles(int row[4]);

extern void (*move_functions[4])(int board[4][4]);

#endif // UTILITY_H
