
#include <stdio.h>
#include "myAO.h"
#include <stdlib.h>


double** allocateMatrix(int rows, int cols) {
    double **matrix = (double**) malloc(rows * sizeof(double*));
    if (!matrix) {
        printf("Error: Memory allocation failed for matrix rows.\n");
        exit(1);
    }

    for (int i = 0; i < rows; i++) {
        matrix[i] = (double*) malloc(cols * sizeof(double));
        if (!matrix[i]) {
            printf("Error: Memory allocation failed for matrix columns.\n");
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            exit(1);
        }
    }
    return matrix; 
}

void freeMatrix(double **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}



double** addMatrices(double **A, double **B, int nA, int mA, int nB, int mB) {
    if (nA != nB || mA != mB) {
        printf("Error: Matrix addition requires same dimensions.\n");
        return NULL;
    }

    double **C = allocateMatrix(nA, mA);
    for (int i = 0; i < nA; i++)
        for (int j = 0; j < mA; j++)
            C[i][j] = A[i][j] + B[i][j];

    return C;
}

double** subtractMatrices(double **A, double **B, int nA, int mA, int nB, int mB) {
        if (nA != nB || mA != mB) {
        printf("Error: Matrix addition requires same dimensions.\n");
        return NULL;
    }

    double **C = allocateMatrix(nA, mA);
    for (int i = 0; i < nA; i++)
        for (int j = 0; j < mA; j++)
            C[i][j] = A[i][j] - B[i][j];

    return C;

}

double** multiplyMatrices(double **A, double **B, int nA, int mA, int nB, int mB) {
    if (mA != nB) {
        printf("Error: Matrix multiplication requires first matrix columns to match second matrix rows.\n");
        return NULL;
    }

    double **C = allocateMatrix(nA, mB);

    for (int i = 0; i < nA; i++) {
        for (int j = 0; j < mB; j++) {
            C[i][j] = 0; 
            for (int k = 0; k < mA; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}


double** transposeMatrix(double **A, int nA, int mA){
    double **C = allocateMatrix(mA, nA);
    for(int i = 0; i<nA; i++)
        for(int j = 0; j<mA; j++)
            C[i][j] = A[j][i];
    return C; 



}



double* solveAxB(double **A, double *B, int n) {
    double *x = (double*) malloc(n * sizeof(double));
    if (!x) {
        printf("Error: Memory allocation failed for solution vector.\n");
        exit(1);
    }


    for (int i = 0; i < n; i++) {
        double diag = A[i][i];
        if (diag == 0) {
            printf("Error: Singular matrix detected. Cannot solve.\n");
            free(x);
            return NULL;
        }
        for (int j = 0; j < n; j++) {
            A[i][j] /= diag;
        }
        B[i] /= diag;

        
        for (int k = 0; k < n; k++) {
            if (k != i) {
                double factor = A[k][i];
                for (int j = 0; j < n; j++) {
                    A[k][j] -= factor * A[i][j];
                }
                B[k] -= factor * B[i];
            }
        }
    }

   
    for (int i = 0; i < n; i++) {
        x[i] = B[i];
    }

    return x;
}

