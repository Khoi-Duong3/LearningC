// The purpose of this file is to implement primary functions which are directly related to arithmetic operations library
// CODE: Include necessary libraries
#include <stdio.h>
#include <stdlib.h>
#include "myAO.h"
#include <math.h>

#define EPSILON 1e-12

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

double **augmentMatrix(double **A, double *B, int nA, int mA){

    double **augmented = allocateMatrix(nA, (mA+1));
    if (!augmented){
        perror("Failed to allocate memory");
        return NULL;
    }

    for (int i = 0; i < nA; i++){
        for (int j = 0; j < mA; j++){
            augmented[i][j] = A[i][j];
        }
        augmented[i][mA] = B[i];
    }

    return augmented;
}

int gaussianElimination(double **Augmented, int nA, int mA){
    int rank = 0;

    // The size of the augmented matrix is nA x (mA + 1). mA here just covers the original A matrix.
    
    for (int col = 0; col < mA; col++) {
        // 1) Find best pivot in rows [rank..nA-1]
        int pivot = rank;
        for (int r = rank + 1; r < nA; r++) {
            if (fabs(Augmented[r][col]) > fabs(Augmented[pivot][col]))
                pivot = r;
        }

        // 2) If pivot is “zero,” skip this column, we use epsilon here to avoid dealing with very small numbers
        if (fabs(Augmented[pivot][col]) < EPSILON)
            continue;

        // 3) Swap pivot row into place (row = rank)
        if (pivot != rank) {
            double *temp = Augmented[rank];
            Augmented[rank] = Augmented[pivot];
            Augmented[pivot] = temp;
        }

        // 4) Normalize pivot row so Augmented[rank][col] == 1
        double diag = Augmented[rank][col];
        for (int c = col; c <= mA; c++) {
            Augmented[rank][c] /= diag;
        }

        // 5) Eliminate below
        for (int r = rank + 1; r < nA; r++) {
            double factor = Augmented[r][col];
            for (int c = col; c <= mA; c++) {
                // Since we have already normalized the pivot row therefore the number/coefficient at Augmented[rank][c] = 1. So the factor is whatever number is below it multiplied by 1
                // Then we just subtract by this number which is making it subtract itself resulting in 0 which clears out that spot in the matrix
                Augmented[r][c] -= factor * Augmented[rank][c];
            }
        }

        rank++;  
    }

    return rank;
}

int backSubstitution(double **Augmented, int nA, int mA, double *x){
    for (int i = nA - 1; i >= 0; i--){
        double sum = Augmented[i][mA];
        for (int j = i + 1; j < mA; j++){
            sum -= Augmented[i][j] * x[j];
        }
        // Check if one of our pivots are 0, if it is then it's doomed we messed up but this should never happen unless the matrix has no solutions
        if (fabs(Augmented[i][i]) < EPSILON){
            return 1;
        }
        x[i] = sum / Augmented[i][i];
    }

    return 0;
}

// CODE: Implement SolveAxB() function
double* solveSLE(double **A, double *B, int nA, int mA){

    double **augmentedMatrix = augmentMatrix(A, B, nA, mA);
    if (!augmentedMatrix){
        perror("Failed to allocate matrix");
        return NULL;
    }

    int rank = gaussianElimination(augmentedMatrix, nA, mA);

    for (int i = rank; i < nA; i++) {
        double lhs = 0;
        for (int j = 0; j < mA; j++)
            lhs += fabs(augmentedMatrix[i][j]);
        if (lhs < EPSILON && fabs(augmentedMatrix[i][mA]) > EPSILON) {
            fprintf(stderr, "No solution (inconsistent system)\n");
            freeMatrix(augmentedMatrix, nA);
            return NULL;
        }
    }

    if (rank < mA){
        fprintf(stderr, "Infinitely many solutions");
    }

    double *xVector = malloc(mA * sizeof(*xVector));
    if (!xVector){
        perror("Failed to allocate memory");
        freeMatrix(augmentedMatrix, nA);
        return NULL;
    }
    
    int backsubSuccess = backSubstitution(augmentedMatrix, nA, mA, xVector);
    if (!backsubSuccess){
        fprintf(stderr, "Error during back‐substitution\n");
        free(xVector);
        freeMatrix(augmentedMatrix, nA);
        return NULL;
    }

    freeMatrix(augmentedMatrix, nA);
    return xVector;
}