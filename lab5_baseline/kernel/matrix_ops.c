#include "matrix_ops.h"
#include <xmmintrin.h>
#include <emmintrin.h>
#include <pmmintrin.h>
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


            // __m128 temp_vec = _mm_setzero_ps(); // Initialize vector accumulator

            // for (int k = 0; k < A_cols - 4; k += 4) {
            //     __m128 a_vec = _mm_loadu_ps(&A[i][k]); // Load 4 elements from A
            //     __m128 b_vec = _mm_setr_ps(B[k][j], B[k + 1][j], B[k + 2][j], B[k + 3][j]); // Set 4 corresponding elements from B
            //     temp_vec = _mm_add_ps(temp_vec, _mm_mul_ps(a_vec, b_vec)); // Multiply and accumulate
            // }

            // // Horizontal add to sum up the elements in the vector
            // temp_vec = _mm_hadd_ps(temp_vec, temp_vec);
            // temp_vec = _mm_hadd_ps(temp_vec, temp_vec);

            // // Store the result back into the matrix C
            // C[i][j] = _mm_cvtss_f32(temp_vec); // Extract the lower element as final result

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

    // // original matrix multiplication
    // for (int i = 0; i < A_rows; i++) {
    //     for (int j = 0; j < B_cols; j++) {
    //         for (int k = 0; k < A_cols; k++) {
    //             C[i][j] += A[i][k] * B[k][j];
    //         }
    //         // __m128 temp_vec = _mm_setzero_ps(); // Initialize vector accumulator

    //         // for (int k = 0; k < A_cols - 4; k += 4) {
    //         //     __m128 a_vec = _mm_loadu_ps(&A[i][k]); // Load 4 elements from A
    //         //     __m128 b_vec = _mm_setr_ps(B[k][j], B[k + 1][j], B[k + 2][j], B[k + 3][j]); // Set 4 corresponding elements from B
    //         //     temp_vec = _mm_add_ps(temp_vec, _mm_mul_ps(a_vec, b_vec)); // Multiply and accumulate
    //         // }

    //         // // Horizontal add to sum up the elements in the vector
    //         // temp_vec = _mm_hadd_ps(temp_vec, temp_vec);
    //         // temp_vec = _mm_hadd_ps(temp_vec, temp_vec);

    //         // // Store the result back into the matrix C
    //         // C[i][j] = _mm_cvtss_f32(temp_vec); // Extract the lower element as final result

    //     }
    // }

    int num_threads = 4;

    // create threads
    pthread_t threads[num_threads];
    thread_data data[num_threads];
    int rows_per_thread = (int)(A_rows / num_threads);

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

        pthread_create(&threads[i], NULL, multiply, (void *)&data[i]);
    }

    for (int i = 0; i < num_threads; i++) pthread_join(threads[i], NULL);

    // /*******************************/
    // /* Count non-zero elements in A /
    // /*******************************/

    // int non_zero = 0;
    // for (int i = 0; i < A_rows; i++) {
    //     for (int j = 0; j < A_cols; j++) {
    //         if (A[i][j] != 0) {
    //             non_zero++;
    //         }
    //     }
    // }

    // /*******************************/
    // /*** Create CSR format for A ***/
    // /*******************************/
    // int *A_row_ptr = (int *)malloc((A_rows + 1) * sizeof(int));
    // int *A_col_idx = (int *)malloc(non_zero * sizeof(int));
    // float *A_val = (float *)malloc(non_zero * sizeof(float));

    // int nnz = 0;
    // A_row_ptr[0] = 0;

    // for (int i = 0; i < A_rows; i++) {
    //     for (int j = 0; j < A_cols; j++) {
    //         if (A[i][j] != 0) {
    //             A_val[nnz] = A[i][j];
    //             A_col_idx[nnz] = j;
    //             nnz++;
    //         }
    //     }
    //     A_row_ptr[i + 1] = nnz;
    // }

    // /*******************************/
    // /* Count non-zero elements in B /
    // /*******************************/

    // non_zero = 0;
    // for (int i = 0; i < B_rows; i++) {
    //     for (int j = 0; j < B_cols; j++) {
    //         if (B[i][j] != 0) {
    //             non_zero++;
    //         }
    //     }
    // }

    // /*******************************/
    // /*** Create CSC format for B ***/
    // /*******************************/
    // int *B_col_ptr = (int *)malloc((B_cols + 1) * sizeof(int));
    // int *B_row_idx = (int *)malloc(non_zero * sizeof(int));
    // float *B_val = (float *)malloc(non_zero * sizeof(float));

    // nnz = 0;
    // B_col_ptr[0] = 0;

    // for (int j = 0; j < B_cols; j++) {
    //     for (int i = 0; i < B_rows; i++) {
    //         if (B[i][j] != 0) {
    //             B_val[nnz] = B[i][j];
    //             B_row_idx[nnz] = i;
    //             nnz++;
    //         }
    //     }
    //     B_col_ptr[j + 1] = nnz;
    // }

    // /*******************************/
    // /**** Compute matrix product ***/
    // /*******************************/

    // // CSR matrix multiplication
    // for (int i = 0; i < A_rows; i++) {
    //     for (int j = 0; j < B_cols; j++) {
    //         C[i][j] = 0;
    //         // iterate over the row of A
    //         int row_start = A_row_ptr[i];
    //         int row_end = A_row_ptr[i + 1];
    //         int elem_in_A = row_start;

    //         // iterate over the column of B
    //         int col_start = B_col_ptr[j];
    //         int col_end = B_col_ptr[j + 1];
    //         int elem_in_B = col_start;

    //         // multiply the row of A with the column of B
    //         while (elem_in_A < row_end && elem_in_B < col_end) {
    //             int A_col = A_col_idx[elem_in_A];
    //             int B_row = B_row_idx[elem_in_B];

    //             if (A_col == B_row) {
    //                 C[i][j] += A_val[elem_in_A] * B_val[elem_in_B];
    //                 elem_in_A++;
    //                 elem_in_B++;
    //             } else if (A_col < B_row) {
    //                 elem_in_A++;
    //             } else {
    //                 elem_in_B++;
    //             }
    //         }
    //     }
    // }

    // int block_size = 16;

    // for (int i = 0; i < A_rows; i += block_size) {
    //     for (int j = 0; j < B_cols; j += block_size) {
    //         // Initialize the output to zero
    //         for (int k = 0; k < B_rows; k += block_size) {
    //             // multiply inside the block
    //             for (int ii = i; ii < i + block_size && ii < A_rows; ii++) {
    //                 for (int kk = k; kk < k + block_size && kk < B_rows; kk++) {
    //                     for (int jj = j; jj < j + block_size && jj < B_cols; jj++) {
    //                         C[ii][jj] += (A[ii][kk] * B[kk][jj]);
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }

    return C;
}
