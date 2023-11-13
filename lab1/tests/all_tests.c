#include "unity/unity.h"
#include "test_conv.h"
#include "test_functional.h"
#include "test_linear.h"
#include "test_matrix_ops.h"

#ifndef BLOCK_SIZE
#define BLOCK_SIZE 1
#endif

// NOTE: all tests are self-contained so no need to call setUp or tearDown

void setUp(void) {
    /* Code here will run before each test */
}

void tearDown(void) {
    /* Code here will run after each test */
}

int main(void) {
    UNITY_BEGIN();

    // Test conv
    // RUN_TEST(test_conv_slides);
    // RUN_TEST(test_conv_slides2);
    // RUN_TEST(test_conv_slides3);
    // RUN_TEST(test_image_null);
    // RUN_TEST(test_bias_null);
    // RUN_TEST(test_kernel_null);
    // RUN_TEST(test_random_conv);

    // Test functional
    // RUN_TEST(test_softmax);
    // RUN_TEST(test_softmax_large);
    // RUN_TEST(test_softmax_long);
    // RUN_TEST(test_relu);
    // RUN_TEST(test_relu_large);
    // RUN_TEST(test_relu_large_neg);

    // Test linear
    // RUN_TEST(test_linear);
    // RUN_TEST(test_linear_very_large);
    // RUN_TEST(test_linear_very_large_very_long);
    // RUN_TEST(test_linear_empty_input);
    // RUN_TEST(test_linear_empty_weights);
    // RUN_TEST(test_linear_empty_biases);
    // RUN_TEST(test_linear_random_values);

    // Test matrix_ops
    // RUN_TEST(test_matmul_square_matrices);
    // RUN_TEST(test_matmul);
    RUN_TEST(test_matmul_large);
    // RUN_TEST(test_matmul_random);
    // RUN_TEST(test_matmul_incompatible_dimensions);
    // RUN_TEST(test_matmul_sparse);

    return UNITY_END();
}
