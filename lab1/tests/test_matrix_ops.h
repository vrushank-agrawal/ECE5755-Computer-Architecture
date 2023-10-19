#ifndef TEST_MATRIX_OPS_H
#define TEST_MATRIX_OPS_H

float **malloc_matrix(int rows, int cols);
float **generate_random_matrix(int rows, int cols);
float **ans_20_20(void);
float **generate_sparse_matrix(int rows, int cols, float sparsity);
void cleanup_matrix(float** mat, int size);

void test_matmul_square_matrices(void);
void test_matmul(void);
// void test_matmul_large(void);
void test_matmul_large(int block_size, int fn);
// void test_matmul_random(void);
void test_matmul_random(int block_size, int fn);
void test_matmul_incompatible_dimensions(void);

#ifndef PROFILING
void test_matmul_sparse(void);
#else
void test_matmul_sparse(int size, float sparsity);
#endif

#endif /* TEST_MATRIX_OPS_H */
