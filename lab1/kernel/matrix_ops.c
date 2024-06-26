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
    else if (A_rows == 10) iter = 1000;
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


/***************************************************************/
/**************************     LAB2      **********************/
/***************************************************************/
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


/***************************************************************/
/**************************     LAB3      **********************/
/***************************************************************/
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
    else if (A_rows == 10) iter = 1000;

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
    gettimeofday(&start_time, NULL);
    start = clock();

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


/***************************************************************/
/**************************     LAB5      **********************/
/***************************************************************/

#include <xmmintrin.h>
#include <emmintrin.h>
// #include <x86intrin.h>

float** simd_matmul(float **A, float **B, int A_rows, int A_cols, int B_rows, int B_cols) {

    if (A_cols != B_rows) {
        printf("Matrix dimensions incompatible for multiplication.\n");
        return NULL;
    }

    float **C = (float **)malloc(A_rows * sizeof(float *));
    for (int i = 0; i < A_rows; i++) {
        C[i] = (float *)malloc(B_cols * sizeof(float));
    }

    clock_t start, end;
    start = clock();

    double a[A_rows][A_cols] __attribute__((aligned(16)));
    double b[B_rows][B_cols] __attribute__((aligned(16)));
    double c[A_rows][B_cols] __attribute__((aligned(16)));

    for (int i = 0; i < A_rows; i++) {
        for (int j = 0; j < A_cols; j++) {
            a[i][j] = A[i][j];
        }
    }

    for (int i = 0; i < B_rows; i++) {
        for (int j = 0; j < B_cols; j++) {
            b[i][j] = B[i][j];
        }
    }



    int block_size = 16;

    for (int i = 0; i < A_rows; i += block_size) {
        for (int j = 0; j < B_cols; j += block_size) {
            // Initialize the output to zero
            for (int k = 0; k < B_rows; k += block_size) {
                // multiply inside the block
                for (int ii = i; ii < i + block_size && ii < A_rows; ii++) {
                    for (int kk = k; kk < k + block_size && kk < B_rows; kk++) {
                        for (int jj = j; jj < j + block_size && jj < B_cols; jj++) {

                            __m128d result = _mm_loadu_pd(&c[ii][jj]);
                            __m128d a_line  = _mm_loadu_pd(&a[ii][kk]);
                            __m128d b_line0 = _mm_loadu_pd(&b[kk][jj+0]);
                            __m128d b_line1 = _mm_loadu_pd(&b[kk][jj+1]);
                            __m128d b_line2 = _mm_loadu_pd(&b[kk][jj+2]);
                            __m128d b_line3 = _mm_loadu_pd(&b[kk][jj+3]);

                            result = _mm_add_pd(result, _mm_mul_pd(_mm_shuffle_pd(a_line, a_line, 0x00), b_line0));
                            result = _mm_add_pd(result, _mm_mul_pd(_mm_shuffle_pd(a_line, a_line, 0x55), b_line1));
                            result = _mm_add_pd(result, _mm_mul_pd(_mm_shuffle_pd(a_line, a_line, 0xaa), b_line2));
                            result = _mm_add_pd(result, _mm_mul_pd(_mm_shuffle_pd(a_line, a_line, 0xff), b_line3));

                            _mm_store_pd(&c[ii][jj],result);

                            // C[ii][jj] += (A[ii][kk] * B[kk][jj]);
                        }
                    }
                }
            }
        }
    }

    // for (int i = 0; i < A_rows; i++) {
    //     for (int j = 0; j < B_cols; j++) {
    //         __m128 sum = _mm_setzero_ps();
    //         for (int k = 0; k < A_cols; k += 4) {
    //             __m128 a = _mm_loadu_ps(&A[i][k]);
    //             __m128 b = _mm_loadu_ps(&B[k][j]);
    //             sum = _mm_add_ps(sum, _mm_mul_ps(a, b));
    //         }

    //         float *sum_arr = (float *)&sum;

    //         C[i][j] = sum_arr[0] + sum_arr[1] + sum_arr[2] + sum_arr[3];

    //         for (int k = A_cols - (A_cols % 4); k < A_cols; k++) {
    //             C[i][j] += A[i][k] * B[k][j];
    //         }

    //     }
    // }

    end = clock();
    double run_time = (double)(end - start);
    double cpu_time = (run_time) / CLOCKS_PER_SEC;

    printf("A: %i x %i\nB: %i x %i\n", A_rows, A_cols, B_rows, B_cols);
    printf("Matmul SIMD CPU time used: %f seconds\n", cpu_time);

    return C;
}
