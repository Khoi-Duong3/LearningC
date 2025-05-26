// The purpose of this file is to implement primary functions which are directly related to arithmetic operations library
// CODE: Include necessary libraries
#include <stdio.h>
#include <stdlib.h>
#include "myAO.h"

void freeMatrix(double **matrix, int rows);

double** allocateMatrix(int rows, int cols) {
    // CODE: allocate the memory of a matrix with rows*cols size
    // Make sure you program handle potential errors
    // For example, if the memory allocation fails in the middle of way, you must deallocate what was allocated so far before exit(1)
    int **matrix = NULL;
    matrix = malloc(rows * sizeof(*matrix));
    if (!matrix){
        perror("Failed to allocate array of pointers");
        return NULL;
    }

    for (int i = 0; i < rows; i++){
        matrix[i] = NULL;
    }

    for (int i = 0; i < rows; i++){
        matrix[i] = malloc(cols * sizeof *matrix[i]);
        if (!matrix[i]) {
            perror("Failed to allocate row");
            freeMatrix(matrix, rows);
        }
    }

    return matrix; // matrix is a pointer to pointer (2D array). 
}

void freeMatrix(double **matrix, int rows) {
    // CODE: free the memory for a given matrix
    if (!matrix){
        return;
    }

    for (int i = 0; i < rows; i++){
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
    // CODE: Implement the subtaction logic

    if (nA != nB || mA != mB){
        printf("Error: Matrix subtraction requires the same dimensions\n");
        return NULL;
    }
    double **C = allocateMatrix(nA, mA);

    for (int i = 0; i < nA; i++){
        for (int j = 0; j < mA; j++){
            C[i][j] = A[i][j] - B[i][j];
        }
    }

    return C;
}

// CODE: Implement multiplicationMatrices() function
double** multiplicationMatrices(double **A, double **B, int nA, int mA, int nB, int mB){
    if (mA != nB){
        printf("Error: Matrix multiplication requires the number of columns of A to be equal to the number of rows in B");
        return NULL;
    }

    double **C = allocateMatrix(nA, mB);
    for (int i = 0; i < nA; i++){
        for (int j = 0; j < mB; j++){
            C[i][j] = 0.0;
            for (int k = 0; k < nB; k++){
                C[i][j] += (A[i][k] * B[k][j]);
            }
        }
    }
    return C;
}


// CODE: Implement transposeMatrices() function
double** transposeMatrices(double **A, int nA, int mA){
    double **B = allocateMatrix(mA, nA);
    if (!B){
        perror("Memory allocation failed");
        return NULL;
    }

    for (int i = 0; i < nA; i++){
        for (int j = 0; j < mA; j++){
            B[j][i] = A[i][j];
        }
    }
    return B;
}

// CODE: Implement SolveAxB() function
