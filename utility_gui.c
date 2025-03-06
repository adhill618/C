#include "utility.h"
#include <stdlib.h> 


void move_up(int board[4][4]) {
    moveBoard(board, UP);
}

void move_down(int board[4][4]) {
    moveBoard(board, DOWN);
}

void move_left(int board[4][4]) {
    moveBoard(board, LEFT);
}

void move_right(int board[4][4]) {
    moveBoard(board, RIGHT);
}

void gameBoard(int array[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            array[i][j] = 0;
        }
    }

    placeRandomTile(array);  
    placeRandomTile(array);
}

void placeRandomTile(int board[4][4]) {
    int emptyCells = 0;
    int emptyPositions[4*4][2];

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) {
                emptyPositions[emptyCells][0] = i;
                emptyPositions[emptyCells][1] = j;
                emptyCells++;
            }
        }
    }

    if (emptyCells > 0) {
        int randomIndex = rand() % emptyCells;
        int row = emptyPositions[randomIndex][0];
        int col = emptyPositions[randomIndex][1];
        board[row][col] = (rand() % 2 + 1) * 2; 
    }
}

int gameOver(int board[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) return 0; 
            if (j < 4 - 1 && board[i][j] == board[i][j + 1]) return 0; 
            if (i < 4 - 1 && board[i][j] == board[i + 1][j]) return 0; 
        }
    }
    return 1; 
}

int moveBoard(int board[4][4], int direction) {
    int moved = 0;
    int temp[4];

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (direction == LEFT) temp[j] = board[i][j];
            if (direction == RIGHT) temp[j] = board[i][4 - 1 - j];
            if (direction == UP) temp[j] = board[j][i];
            if (direction == DOWN) temp[j] = board[4 - 1 - j][i];
        }

        moved |= shiftTiles(temp);  

        for (int j = 0; j < 4; j++) {
            if (direction == LEFT) board[i][j] = temp[j];
            if (direction == RIGHT) board[i][4 - 1 - j] = temp[j];
            if (direction == UP) board[j][i] = temp[j];
            if (direction == DOWN) board[4 - 1 - j][i] = temp[j];
        }
    }

    return moved;
}

int shiftTiles(int row[4]) {
    int moved = 0;
    int temp[4] = {0}, index = 0;

    for (int i = 0; i < 4; i++) {
        if (row[i] != 0) {
            temp[index++] = row[i];
        }
    }

    for (int i = 0; i < 3; i++) {
        if (temp[i] != 0 && temp[i] == temp[i + 1]) {
            temp[i] *= 2;
            temp[i + 1] = 0;
            moved = 1;
        }
    }

    index = 0;
    for (int i = 0; i < 4; i++) {
        if (temp[i] != 0) {
            row[index++] = temp[i];
        } else {
            row[index++] = 0;
        }
    }

    return moved;
}
