#include "matrix_ops.h"
#include <xmmintrin.h>
#include <emmintrin.h>
#include <pmmintrin.h>

float **matmul(float **A, float **B, int A_rows, int A_cols, int B_rows, int B_cols) {
    if (A_cols != B_rows) {
        printf("Matrix dimensions incompatible for multiplication.\n");
        return NULL;
    }

    float **C = (float **)malloc(A_rows * sizeof(float *));
    for (int i = 0; i < A_rows; i++) {
        C[i] = (float *)calloc(B_cols, sizeof(float));
    }

    // // Original Implementation
    // for (int i = 0; i < A_rows; i++) {
    //     for (int j = 0; j < B_cols; j++) {
    //         for (int k = 0; k < A_cols; k++) {
    //             C[i][j] += A[i][k] * B[k][j];
    //         }
    //     }
    // }

    /*******************************/
    /* Count non-zero elements in A /
    /*******************************/

    int non_zero = 0;
    for (int i = 0; i < A_rows; i++) {
        for (int j = 0; j < A_cols; j++) {
            if (A[i][j] != 0) {
                non_zero++;
            }
        }
    }

    /*******************************/
    /*** Create CSR format for A ***/
    /*******************************/
    int *A_row_ptr = (int *)malloc((A_rows + 1) * sizeof(int));
    int *A_col_idx = (int *)malloc(non_zero * sizeof(int));
    float *A_val = (float *)malloc(non_zero * sizeof(float));

    int nnz = 0;
    A_row_ptr[0] = 0;

    for (int i = 0; i < A_rows; i++) {
        for (int j = 0; j < A_cols; j++) {
            if (A[i][j] != 0) {
                A_val[nnz] = A[i][j];
                A_col_idx[nnz] = j;
                nnz++;
            }
        }
        A_row_ptr[i + 1] = nnz;
    }

    /*******************************/
    /* Count non-zero elements in B /
    /*******************************/

    non_zero = 0;
    for (int i = 0; i < B_rows; i++) {
        for (int j = 0; j < B_cols; j++) {
            if (B[i][j] != 0) {
                non_zero++;
            }
        }
    }

    /*******************************/
    /*** Create CSC format for B ***/
    /*******************************/
    int *B_col_ptr = (int *)malloc((B_cols + 1) * sizeof(int));
    int *B_row_idx = (int *)malloc(non_zero * sizeof(int));
    float *B_val = (float *)malloc(non_zero * sizeof(float));

    nnz = 0;
    B_col_ptr[0] = 0;

    for (int j = 0; j < B_cols; j++) {
        for (int i = 0; i < B_rows; i++) {
            if (B[i][j] != 0) {
                B_val[nnz] = B[i][j];
                B_row_idx[nnz] = i;
                nnz++;
            }
        }
        B_col_ptr[j + 1] = nnz;
    }

    /*******************************/
    /**** Compute matrix product ***/
    /*******************************/

    // CSR matrix multiplication
    for (int i = 0; i < A_rows; i++) {
        for (int j = 0; j < B_cols; j++) {
            C[i][j] = 0;
            // iterate over the row of A
            int row_start = A_row_ptr[i];
            int row_end = A_row_ptr[i + 1];
            int elem_in_A = row_start;

            // iterate over the column of B
            int col_start = B_col_ptr[j];
            int col_end = B_col_ptr[j + 1];
            int elem_in_B = col_start;

            // multiply the row of A with the column of B
            while (elem_in_A < row_end && elem_in_B < col_end) {
                int A_col = A_col_idx[elem_in_A];
                int B_row = B_row_idx[elem_in_B];

                if (A_col == B_row) {
                    C[i][j] += A_val[elem_in_A] * B_val[elem_in_B];
                    elem_in_A++;
                    elem_in_B++;
                } else if (A_col < B_row) {
                    elem_in_A++;
                } else {
                    elem_in_B++;
                }
            }
        }
    }

    return C;
}
