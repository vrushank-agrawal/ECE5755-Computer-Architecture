#include "matrix_ops.h"

float **matmul(float **A, float **B, int A_rows, int A_cols, int B_rows, int B_cols) {
    if (A_cols != B_rows) {
        printf("Matrix dimensions incompatible for multiplication.\n");
        return NULL;
    }

    float **C = (float **)malloc(A_rows * sizeof(float *));
    for (int i = 0; i < A_rows; i++) {
        C[i] = (float *)malloc(B_cols * sizeof(float));
    }

    /**** YOUR CODE HERE ****/
    for (int i=0; i < A_rows; i++) {
        for (int j=0; j < B_cols; j++) {
            C[i][j] = 0;
            for (int k=0; k < B_rows; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}