#ifndef TEST_MATRIX_OPS_H
#define TEST_MATRIX_OPS_H

float **generate_random_sq_matrix(int size);
void cleanup_matrix(float** mat, int size);

void test_matmul_square_matrices_random(void);
void test_matmul_square_matrices(void);
void test_matmul_incompatible_dimensions(void);

#endif /* TEST_MATRIX_OPS_H */
