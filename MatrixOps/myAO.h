#ifndef MYAO_H
#define MYAO_H

// IMPORTANT: allocateMatrix() and freeMatrix() are not limited to our test case, and they must be here rather than utility.h
// results still need memory allocation and de-allocation, making these functions primary components of your library.
double** allocateMatrix(int rows, int cols);
void freeMatrix(double **matrix, int rows);

double** addMatrices(double **A, double **B, int nA, int mA, int nB, int mB);
double** subtractMatrices(double **A, double **B, int nA, int mA, int nB, int mB);
double** transposeMatrices(double **A, int nA, int mA);
double* solveSLE(double **A, double *B, int nA, int mA);
// CODE: include ONLY the declaration of primary functions

double determinant(double **A, int nA, int mA);
#endif 