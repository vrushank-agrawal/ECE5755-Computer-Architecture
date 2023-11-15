#ifndef TEST_MATRIX_OPS_H
#define TEST_MATRIX_OPS_H

float **malloc_matrix(int rows, int cols);
float **generate_random_matrix(int rows, int cols);
float **ans_20_20(void);
float **generate_sparse_matrix(int rows, int cols, float sparsity);
void cleanup_matrix(float** mat, int size);

void test_matmul_square_matrices(void);
void test_matmul(void);

#ifndef PROFILING
void test_matmul_large(void);
#else
void test_matmul_large(int threads, int fn);
#endif

#ifndef PROFILING
void test_matmul_random(void);
#else
void test_matmul_random(int threads, int size, int fn);
#endif

#ifndef PROFILING
void test_matmul_sparse(void);
#else
void test_matmul_sparse(int size, float sparsity);
#endif

#endif /* TEST_MATRIX_OPS_H */
