#include "unity/unity.h"
#include "../kernel/kernel.h"
#include "test_matrix_ops.h"

/**** HELPER FUNCTIONS ****/
float** malloc_matrix(int rows, int cols) {
    float** mat = (float**)malloc(rows * sizeof(float*));
    for (int i = 0; i < rows; i++) {
        mat[i] = (float*)malloc(cols * sizeof(float));
    }
    return mat;
}

float** generate_random_sq_matrix(int size) {
    float** mat = malloc_matrix(size, size);

    for (int i=0; i < size; i++) {
        for (int j=0; j < size; j++) {
            mat[i][j] = (float)rand()/(float)(RAND_MAX/100);
        }
    }
    return mat;
}

void cleanup_matrix(float** mat, int row_size) {
    for (int i=0; i < row_size; i++) {
        free(mat[i]);
    }
    free(mat);
}

/************************/
/**** MAIN FUNCTIONS ****/
/************************/

void test_matmul_square_matrices(void)
{
    /**** YOUR CODE HERE ****/
    float **A = malloc_matrix(2, 2);
    float **B = malloc_matrix(2, 2);

    for (int j=0; j < 2; j++) {
        for (int k=0; k < 2; k++) {
            A[j][k] = (j+1) + (k+1);
            B[j][k] = (j+1) * (k+1);
        }
    }

    float Ans[][2] = {{8, 16}, {11, 22}};
    float **C = matmul((float **)A, (float **)B, 2, 2, 2, 2);

    for (int i=0; i < 2; i++) {
        for (int j=0; j < 2; j++) {
            UNITY_TEST_ASSERT_FLOAT_WITHIN(0.0001, Ans[i][j], C[i][j], __LINE__, "Wrong sum");
            TEST_ASSERT_EQUAL_INT(sizeof(C[i][j]), sizeof(float));
        }
    }

    // Cleanup
    cleanup_matrix(A, 2);
    cleanup_matrix(B, 2);
    cleanup_matrix(C, 2);
}

void test_matmul_square_matrices_random(void)
{
    /**** YOUR CODE HERE ****/
    for (int i=1; i < 10; i++)
    {
        for (int a=0; a < 5; a++)
        {
            float **A = generate_random_sq_matrix(i);
            float **B = generate_random_sq_matrix(i);
            float **C = matmul(A, B, i, i, i, i);

            for (int j=0; j < i; j++) {
                for (int k=0; k < i; k++) {
                    float sum = 0;
                    for (int l=0; l < i; l++) {
                        sum += A[j][l] * B[l][k];
                    }
                    UNITY_TEST_ASSERT_FLOAT_WITHIN(0.0001, sum, C[j][k], __LINE__, "Wrong sum");
                    TEST_ASSERT_EQUAL_INT(sizeof(C[j][k]), sizeof(float));
                }
            }

            // Cleanup
            cleanup_matrix(A, i);
            cleanup_matrix(B, i);
            cleanup_matrix(C, i);
        }
    }
}

void test_matmul_incompatible_dimensions(void)
{
    // Setup
    float **A = malloc_matrix(2, 3);
    float **B = malloc_matrix(2, 2);

    // Run function under test
    float **C = matmul(A, B, 2, 3, 2, 2);

    // Check expectations
    UNITY_TEST_ASSERT_NULL(C, __LINE__, "Expected NULL!");

    // Cleanup
    cleanup_matrix(A, 2);
    cleanup_matrix(B, 2);
}