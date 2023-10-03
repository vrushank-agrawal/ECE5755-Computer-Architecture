#include "matrix_ops.h"
#include <stdio.h>
#include <time.h>

#ifndef BLOCK_SIZE
#define BLOCK_SIZE 1
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

    /**** YOUR CODE HERE ****/
    for (int many=0; many < 100000; many++)
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

float **matmul_blocking(float **A,
                        float **B,
                        int A_rows,
                        int A_cols,
                        int B_rows,
                        int B_cols,
                        int block
                        )
{
    if (A_cols != B_rows) {
        printf("Matrix dimensions incompatible for multiplication.\n");
        return NULL;
    }

    if (A == NULL || B == NULL){
        printf("Matrices are null.\n");
        return NULL;
    }

    float **C = (float **)malloc(A_rows * sizeof(float *));
    for (int i = 0; i < A_rows; i++) {
        C[i] = (float *)malloc(B_cols * sizeof(float));
    }

    int block_size;
    if (block != -1)
        block_size = block;
    else
        block_size = BLOCK_SIZE;
    printf("block_size = %i\n", block_size);

    int iter = 1;
    clock_t start, end;
    start = clock();

    for (int many=0; many < iter; many++) {
        for (int i=0; i < A_rows; i++) {
            for (int j=0; j < B_cols; j++){
                C[i][j] = 0;
            }
        }
        for (int i = 0; i < A_rows; i += block_size) {
            for (int j = 0; j < B_cols; j += block_size) {
                // Initialize the output to zero
                for (int k = 0; k < B_rows; k += block_size) {
                    // multiply inside the block
                    for (int ii = i; ii < i + block_size && ii < A_rows; ii++) {
                        for (int jj = j; jj < j + block_size && jj < B_cols; jj++) {
                            for (int kk = k; kk < k + block_size && kk < B_rows; kk++) {
                                // printf("i=%f, j=%f\n", A[ii][kk], B[kk][jj]);
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

    printf("Run time: %f micro_seconds\n", run_time);
    printf("CPU time used: %f seconds\n", cpu_time);

    return C;
}