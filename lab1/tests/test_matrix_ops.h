#ifndef TEST_MATRIX_OPS_H
#define TEST_MATRIX_OPS_H

float **malloc_matrix(int rows, int cols);
float **generate_random_sq_matrix(int size);
float **ans_20_20(void);
void cleanup_matrix(float** mat, int size);

void test_matmul_square_matrices(void);
void test_matmul(void);
void test_matmul_large(void);
void test_matmul_square_matrices_random(void);
void test_matmul_incompatible_dimensions(void);

#endif /* TEST_MATRIX_OPS_H */
