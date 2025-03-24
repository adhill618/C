
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void fillRandom(double **matrix, int rows, int cols) {
    srand(42);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            matrix[i][j] = (rand() % 21) - 10; 
}

void printMatrix(double **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%6.2f ", matrix[i][j]);
        printf("\n");
    }
    printf("\n");
}


