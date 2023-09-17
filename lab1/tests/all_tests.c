#include "unity/unity.h"
#include "test_conv.h"
#include "test_functional.h"
#include "test_linear.h"
#include "test_matrix_ops.h"

void setUp(void) {
    /* Code here will run before each test */
}

void tearDown(void) {
    /* Code here will run after each test */
}

int main(void) {
    UNITY_BEGIN();

    // Test conv
    RUN_TEST(test_conv);

    // Test functional
    RUN_TEST(test_softmax);
    RUN_TEST(test_relu);

    // Test linear
    RUN_TEST(test_linear);
    RUN_TEST(test_linear_empty_input);
    RUN_TEST(test_linear_empty_weights);
    RUN_TEST(test_linear_empty_biases);

    // Test matrix_ops
    RUN_TEST(test_matmul_square_matrices);
    RUN_TEST(test_matmul_square_matrices_random);
    RUN_TEST(test_matmul_incompatible_dimensions);

    return UNITY_END();
}
