#include "matrix_ops.h"
#include <xmmintrin.h>
#include <emmintrin.h>
#include <pthread.h>

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


float **matmul(float **A, float **B, int A_rows, int A_cols, int B_rows, int B_cols) {
    if (A_cols != B_rows) {
        printf("Matrix dimensions incompatible for multiplication.\n");
        return NULL;
    }

    float **C = (float **)malloc(A_rows * sizeof(float *));
    for (int i = 0; i < A_rows; i++) {
        C[i] = (float *)calloc(B_cols, sizeof(float));
    }

    // original matrix multiplication
    for (int i = 0; i < A_rows; i++) {
        for (int j = 0; j < B_cols; j++) {
            for (int k = 0; k < A_cols; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // int num_threads = 8;

    // // create threads
    // pthread_t threads[num_threads];
    // thread_data data[num_threads];
    // int rows_per_thread = (int)(A_rows / num_threads);

    // for (int i = 0; i < num_threads; i++) {
    //     data[i].tid = i;

    //     data[i].start_row = i * rows_per_thread;
    //     data[i].end_row = (i + 1) * rows_per_thread;
    //     data[i].A_cols = A_cols;
    //     data[i].B_cols = B_cols;
    //     data[i].A_rows = A_rows;

    //     data[i].A = A;
    //     data[i].B = B;
    //     data[i].C = C;

    //     if (i == num_threads - 1) {
    //         data[i].end_row = A_rows;
    //     }

    //     pthread_create(&threads[i], NULL, multiply, (void *)&data[i]);
    // }

    // for (int i = 0; i < num_threads; i++) pthread_join(threads[i], NULL);

    return C;
}
