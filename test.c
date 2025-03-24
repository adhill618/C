#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "myAO.h"
#include "utility.h"

int main(int argc, char *argv[]) {
    if (argc < 5) {
        printf("Usage: %s <operation> <rowsA> <colsA> [rowsB] [colsB] <print_flag>\n", argv[0]);
        return 1;
    }

    char op = argv[1][0];
    int nA = atoi(argv[2]);
    int mA = atoi(argv[3]);
    int nB = (argc > 5) ? atoi(argv[4]) : 0;
    int mB = (argc > 6) ? atoi(argv[5]) : 0;
    int print_flag = atoi(argv[argc - 1]);

  
    srand(42);

    
    double **A = allocateMatrix(nA, mA);
    fillRandom(A, nA, mA);

    double **B = NULL;
    if (op != 'T') {
        B = allocateMatrix(nB, mB);
        fillRandom(B, nB, mB);
    }

    if (print_flag) {
        printf("Matrix A:\n");
        printMatrix(A, nA, mA);
        if (B) {
            printf("Matrix B:\n");
            printMatrix(B, nB, mB);
        }
    }

    
    double **result = NULL;
    if (op == '+') {
        result = addMatrices(A, B, nA, mA, nB, mB);
    } else if (op == '-') {
        result = subtractMatrices(A, B, nA, mA, nB, mB);
    } else if (op == '*') {
        result = multiplyMatrices(A, B, nA, mA, nB, mB);
    } else if (op == 'T') {
        result = transposeMatrix(A, nA, mA);
    } else if (op == 'S') {
        double *solution = solveAxB(A, B[0], nA);
        if (solution) {
            printf("Solution Vector:\n");
            for (int i = 0; i < nA; i++) {
                printf("%6.2f\n", solution[i]);
            }
            free(solution);
        }
    } else {
        printf("Error: Invalid operation '%c'.\n", op);
    }

    if (print_flag && result) {
        printf("Result:\n");
        if (op == 'T') printMatrix(result, mA, nA);
        else printMatrix(result, nA, mB);
    }

   
    freeMatrix(A, nA);
    if (B) freeMatrix(B, nB);
    if (result) freeMatrix(result, (op == 'T') ? mA : nA);

    return 0;
}
