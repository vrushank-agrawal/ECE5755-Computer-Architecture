#ifndef TEST_MATRIX_OPS_H
#define TEST_MATRIX_OPS_H

float **malloc_matrix(int rows, int cols);
float **generate_random_matrix(int rows, int cols);
float **ans_20_20(void);
void cleanup_matrix(float** mat, int size);

void test_matmul_square_matrices(void);
void test_matmul(void);
// void test_matmul_large(void);
void test_matmul_large(int block_size, int fn);
// void test_matmul_random(void);
void test_matmul_random(int block_size, int fn);
void test_matmul_incompatible_dimensions(void);
void test_matmul_sparse(void);

#endif /* TEST_MATRIX_OPS_H */
