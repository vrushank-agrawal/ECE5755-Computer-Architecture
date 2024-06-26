#include "matrix_ops.h"
#include <stdio.h>
#include <time.h>

#ifndef BLOCK_SIZE
#define BLOCK_SIZE 16
#endif

float **matmul(float **A, float **B, int A_rows, int A_cols, int B_rows, int B_cols) {
    if (A_cols != B_rows) {
        printf("Matrix dimensions incompatible for multiplication.\n");
        return NULL;
    }

    float **C = (float **)malloc(A_rows * sizeof(float *));
    for (int i = 0; i < A_rows; i++) {
        C[i] = (float *)malloc(B_cols * sizeof(float));
    }

    int iter = 1;
    if (A_rows == 20) iter = 10000;
    if (A_rows == 100) iter = 100;
    clock_t start, end;
    start = clock();

    /**** YOUR CODE HERE ****/
    for (int many=0; many < iter; many++)
        for (int i=0; i < A_rows; i++) {
            for (int j=0; j < B_cols; j++) {
                C[i][j] = 0;
                for (int k=0; k < B_rows; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }

    end = clock();
    double run_time = (double)(end - start);
    double cpu_time = (run_time) / CLOCKS_PER_SEC;

    printf("A: %i x %i\nB: %i x %i\n", A_rows, A_cols, B_rows, B_cols);
    printf("Matmul CPU time used: %f seconds\n", cpu_time);

    return C;
}

float **matmul_blocking(float **A,
                        float **B,
                        int A_rows,
                        int A_cols,
                        int B_rows,
                        int B_cols,
                        int block
){
    if (A_cols != B_rows) {
        printf("Matrix dimensions incompatible for multiplication.\n");
        return NULL;
    }

    if (A == NULL || B == NULL){
        printf("Matrices are null.\n");
        return NULL;
    }

    // Initialize output to zero
    float **C = (float **)malloc(A_rows * sizeof(float *));
    for (int i = 0; i < A_rows; i++) {
        C[i] = (float *)malloc(B_cols * sizeof(float));
        for (int j=0; j < B_cols; j++){
            C[i][j] = 0;
        }
    }

    int block_size;
    if (block != -1) block_size = block;
    else block_size = 1;
    printf("block_size = %i\n", block_size);

    int iter = 1;
    if (A_rows == 20) iter = 10000;
    if (A_rows == 100) iter = 100;
    clock_t start, end;
    start = clock();

    for (int many=0; many < iter; many++) {
        // // initialize to zero
        if (iter > 1) {
            for (int i = 0; i < A_rows; i++) {
                for (int j = 0; j < B_cols; j++) {
                    C[i][j] = 0;
                }
            }
        }

        for (int i = 0; i < A_rows; i += block_size) {
            for (int j = 0; j < B_cols; j += block_size) {
                // Initialize the output to zero
                for (int k = 0; k < B_rows; k += block_size) {
                    // multiply inside the block
                    for (int ii = i; ii < i + block_size && ii < A_rows; ii++) {
                        for (int kk = k; kk < k + block_size && kk < B_rows; kk++) {
                            for (int jj = j; jj < j + block_size && jj < B_cols; jj++) {
                                // printf("i: %i, %f, j: %i, %f\n", ii, A[ii][kk], jj, B[kk][jj]);
                                C[ii][jj] += (A[ii][kk] * B[kk][jj]);
                            }
                        }
                    }
                }
            }
        }
    }

    end = clock();
    double run_time = (double)(end - start);
    double cpu_time = (run_time) / CLOCKS_PER_SEC;

    printf("A: %i x %i\nB: %i x %i\n", A_rows, A_cols, B_rows, B_cols);
    printf("Matmul Blocking CPU time used: %f seconds\n", cpu_time);

    return C;
}


float **matmul_sparse(float **A,
                    float **B,
                    int A_rows,
                    int A_cols,
                    int B_rows,
                    int B_cols
){

    if (A_cols != B_rows) {
        printf("Matrix dimensions incompatible for multiplication.\n");
        return NULL;
    }

    if (A == NULL || B == NULL){
        printf("Matrices are null.\n");
        return NULL;
    }

    // Initialize output to zero
    float **result = (float **)malloc(A_rows * sizeof(float *));
    for (int i = 0; i < A_rows; i++) {
        result[i] = (float *)malloc(B_cols * sizeof(float));
        for (int j=0; j < B_cols; j++){
            result[i][j] = 0;
        }
    }

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
    printf("non_zero A: %i\n", non_zero);

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
    printf("non_zero B: %i\n", non_zero);

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
    clock_t start, end;
    start = clock();

    int iter = 1;
    if (A_rows == 20) iter = 10000;
    if (A_rows == 100) iter = 100;

    printf("iterations: %i\n", iter);

    // CSR matrix multiplication
    for (int many=0; many < iter; many++) {
        for (int i = 0; i < A_rows; i++) {
            for (int j = 0; j < B_cols; j++) {
                result[i][j] = 0;
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
                        result[i][j] += A_val[elem_in_A] * B_val[elem_in_B];
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
    }

    end = clock();

    double run_time = (double)(end - start);
    double cpu_time = (run_time) / CLOCKS_PER_SEC;

    printf("A: %i x %i\nB: %i x %i\n", A_rows, A_cols, B_rows, B_cols);
    printf("Matmul Sparse CPU time used: %f seconds\n", cpu_time);

    return result;
}

