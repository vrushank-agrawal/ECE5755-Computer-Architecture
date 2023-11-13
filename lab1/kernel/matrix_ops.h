#ifndef MATRIX_OPS_H
#define MATRIX_OPS_H

#include <stdio.h>
#include <stdlib.h>

float **matmul(float **A, float **B, int A_rows, int A_cols, int B_rows, int B_cols);
float **matmul_blocking(float **A, float **B, int A_rows, int A_cols, int B_rows, int B_cols, int block_size);
float **matmul_sparse(float **A, float **B, int A_rows, int A_cols, int B_rows, int B_cols);

typedef struct {
    int tid;

    int start_row;
    int end_row;
    int B_cols;
    int A_cols;
    int A_rows;

    float **A;
    float **B;
    float **C;
} thread_data;

void *multiply(void *arg);
float **matmul_multithread(float **A, float **B, int A_rows, int A_cols, int B_rows, int B_cols, int num_threads);
#endif /* MATRIX_OPS_H */