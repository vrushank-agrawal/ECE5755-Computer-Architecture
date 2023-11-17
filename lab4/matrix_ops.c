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
    if (A_rows == 20) iter = 100000;
    else if (A_rows == 100) iter = 1000;
    else if (A_rows == 500) iter = 10;
    else if (A_rows == 5) iter = 100000;
    else if (A_rows == 105) iter = 100;
    else if (A_rows == 1000) iter = 100;
    clock_t start, end;
    start = clock();

    /**** YOUR CODE HERE ****/
    for (int many=0; many < iter; many++)
        for (int i=0; i < A_rows; i++) {
            for (int j=0; j < B_cols; j++) {
                float temp = 0;
                for (int k=0; k < B_rows; k++) {
                    temp += A[i][k] * B[k][j];
                }
                C[i][j] = temp;
            }
        }

    end = clock();
    double run_time = (double)(end - start);
    double cpu_time = (run_time) / CLOCKS_PER_SEC;

    printf("A: %i x %i\nB: %i x %i\n", A_rows, A_cols, B_rows, B_cols);
    printf("Matmul CPU time used: %f seconds\n", cpu_time);

    return C;
}


/***************************************************************/
/**************************     LAB4      **********************/
/***************************************************************/

#include <pthread.h>
#include <sys/time.h>

void *multiply(void *arg) {
    thread_data *data = (thread_data *)arg;
    int start = data->start_row;
    int end = data->end_row;
    int B_cols = data->B_cols;
    int A_cols = data->A_cols;
    int A_rows = data->A_rows;
    float **A = data->A;
    float **B = data->B;
    float **C = data->C;

    int iter = 1;
    if (A_rows == 20) iter = 100000;
    else if (A_rows == 100) iter = 1000;
    else if (A_rows == 500) iter = 10;
    else if (A_rows == 5) iter = 100000;
    else if (A_rows == 105) iter = 100;
    else if (A_rows == 1000) iter = 100;

    if (data->tid == 0) printf("Number of iterations: %i\n", iter);

    for (int many=0; many < iter; many++)
        for (int i = start; i < end; i++) {
            for (int j = 0; j < B_cols; j++) {
                float temp = 0;
                for (int k = 0; k < A_cols; k++) {
                    temp += A[i][k] * B[k][j];
                }
                C[i][j] = temp;
            }
        }

    pthread_exit(NULL);
}

float **matmul_multithread(
    float **A,
    float **B,
    int A_rows,
    int A_cols,
    int B_rows,
    int B_cols,
    int num_threads)
{
    if (A_cols != B_rows) {
        printf("Matrix dimensions incompatible for multiplication.\n");
        return NULL;
    }

    if (A == NULL || B == NULL){
        printf("Matrices are null.\n");
        return NULL;
    }

    printf("\nENTERING MULTITHREAD\n");
    // Initialize output to zero
    float **C = (float **)malloc(A_rows * sizeof(float *));
    for (int i = 0; i < A_rows; i++) {
        C[i] = (float *)malloc(B_cols * sizeof(float));
        for (int j=0; j < B_cols; j++){
            C[i][j] = 0;
        }
    }

    // create threads
    pthread_t threads[num_threads];
    thread_data data[num_threads];
    int rows_per_thread = (int)(A_rows / num_threads);

    struct timeval start_time, end_time;
    clock_t start, end;
    start = clock();
    gettimeofday(&start_time, NULL);

    for (int i = 0; i < num_threads; i++) {
        data[i].tid = i;

        data[i].start_row = i * rows_per_thread;
        data[i].end_row = (i + 1) * rows_per_thread;
        data[i].A_cols = A_cols;
        data[i].B_cols = B_cols;
        data[i].A_rows = A_rows;

        data[i].A = A;
        data[i].B = B;
        data[i].C = C;

        if (i == num_threads - 1) {
            data[i].end_row = A_rows;
        }

        // printf("thread %i: %i - %i\n", i, data[i].start_row, data[i].end_row);

        pthread_create(&threads[i], NULL, multiply, (void *)&data[i]);
    }

    for (int i = 0; i < num_threads; i++) pthread_join(threads[i], NULL);

    gettimeofday(&end_time, NULL);
    end = clock();
    double run_time = (double)(end_time.tv_sec - start_time.tv_sec) + (double)(end_time.tv_usec - start_time.tv_usec) / 1000000;

    printf("A: %i x %i\nB: %i x %i\n", A_rows, A_cols, B_rows, B_cols);
    printf("Actual run time used: %f seconds\n", run_time);
    printf("Total thread time used: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    printf("Potential actual thread time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC / num_threads);

    return C;
}
