#ifndef MYAO_H
#define MYAO_H


double** allocateMatrix(int rows, int cols);
void freeMatrix(double **matrix, int rows);

double** addMatrices(double **A, double **B, int nA, int mA, int nB, int mB);
double** subtractMatrices(double **A, double **B, int nA, int mA, int nB, int mB);
double** multiplyMatrices(double **A, double **B, int nA, int mA, int nB, int mB); 
double** transposeMatrix(double **A, int nA, int mA); 
double* solveAxB(double **A, double *B, int n);




#endif