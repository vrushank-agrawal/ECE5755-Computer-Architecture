#include "unity/unity.h"
#include "../kernel/kernel.h"
#include "test_linear.h"
#include <tests/test_matrix_ops.h>

#ifdef PROFILING
#define PROFILE 1
#endif

/******** HELPER FUNCTIONS ********/

float* generate_random_vector(int size) {
    float *vec = (float *)malloc(size * sizeof(float));

    for (int i = 0; i < size; i++) {
        vec[i] = (float)rand() / (float)(RAND_MAX / 100);
    }
    return vec;
}

/***********************************/
/******** MAIN FUNCTIONS ********/
/***********************************/

void test_linear(void) {

    float input[] = {1.0, 2.0, 3.0};
    int inputSize = 3;

    float **weights = (float **)malloc(3 * sizeof(float *));
    for (int i = 0; i < 3; i++) {
        weights[i] = (float *)malloc(2 * sizeof(float));
    }
    weights[0][0] = 0.1;
    weights[0][1] = 0.2;
    weights[1][0] = 0.3;
    weights[1][1] = 0.4;
    weights[2][0] = 0.5;
    weights[2][1] = 0.6;

    float biases[] = {0.7, 0.8};
    int outputSize = 2;
    float *output = linear(input, weights, biases, inputSize, outputSize);

    #ifndef PROFILE
    printf("RUNNING UNITY TEST\n");
    float expectedOutput[] = {2.9, 3.6};

    TEST_ASSERT_NOT_NULL(output);
    for (int i = 0; i < outputSize; i++) {
        TEST_ASSERT_FLOAT_WITHIN(1e-6, expectedOutput[i], output[i]);
    }
    #endif

    // Cleanup
    free(output);
    free(weights);
}

void test_linear_very_large(void) {
    float input[5000];
    for (int i = 0; i < 5000; i++) {
        input[i] = i;
    }

    float **weights = (float **)malloc(5000 * sizeof(float *));
    for (int i = 0; i < 5000; i++) {
        weights[i] = (float *)malloc(5000 * sizeof(float));
        for (int j = 0; j < 1; j++) {
            weights[i][j] = 1;
        }
    }

    float biases[] = {0};

    float *output = linear(input, weights, biases, 5000, 1);

    #ifndef PROFILE
    printf("RUNNING UNITY TEST\n");
    TEST_ASSERT_NOT_NULL(output);

    for (int i = 0; i < 1; i++) {
        TEST_ASSERT_FLOAT_WITHIN(1e-6, 12497500, output[i]);
    }
    #endif

    // Cleanup
    free(output);
    free(weights);
}


void test_linear_very_large_very_long(void) {
    float input[5000];
    for (int i = 0; i < 5000; i++) {
        input[i] = i;
    }

    float **weights = (float **)malloc(5000 * sizeof(float *));
    for (int i = 0; i < 5000; i++) {
        weights[i] = (float *)malloc(5000 * sizeof(float));
        for (int j = 0; j < 5000; j++) {
            weights[i][j] = 1;
        }
    }

    float biases[5000];
    for (int i = 0; i < 5000; i++) {
        biases[i] = 1000;
    }

    float *output = linear(input, weights, biases, 5000, 5000);

    #ifndef PROFILE
    printf("RUNNING UNITY TEST\n");
    TEST_ASSERT_NOT_NULL(output);

    for (int i = 0; i < 5000; i++) {
        TEST_ASSERT_FLOAT_WITHIN(1e-6, 12498500, output[i]);
    }
    #endif

    // Cleanup
    free(output);
    free(weights);
}

void test_linear_empty_input(void) {

    float *output = linear(NULL, NULL, NULL, 0, 0);
    #ifndef PROFILE
    TEST_ASSERT_NULL(output);
    #endif
}

void test_linear_empty_weights(void) {

    float input[] = {1.0, 2.0, 3.0};
    int inputSize = 3;
    float **weights = NULL;
    float biases[] = {0.7, 0.8};
    int outputSize = 2;

    float *output = linear(input, weights, biases, inputSize, outputSize);
    #ifndef PROFILE
    TEST_ASSERT_NULL(output);
    #endif
}

void test_linear_empty_biases(void) {

    float input[] = {1.0, 2.0, 3.0};
    int inputSize = 3;
    float weights[][2] = {{0.1, 0.2}, {0.3, 0.4}, {0.5, 0.6}};
    float *biases = NULL;
    int outputSize = 2;

    float *output = linear(input, (float **)weights, biases, inputSize, outputSize);
    #ifndef PROFILE
    TEST_ASSERT_NULL(output);
    #endif
}

void test_linear_random_values(void) {

    int tests = 0;
    for (int i = 1; i < 10; i++) {
        for (int a = 0; a < 5; a++) {
            float *input = generate_random_vector(i);
            float **weights = generate_random_matrix(i, i);
            float *biases = generate_random_vector(i);
            float *output = linear(input, weights, biases, i, i);

            #ifndef PROFILE
            for (int j = 0; j < i; j++) {
                float sum = biases[j];
                for (int k = 0; k < i; k++) {
                    sum += input[k] * weights[k][j];
                }
                TEST_ASSERT_FLOAT_WITHIN(0.0001, sum, output[j]);
            }
            #endif
            // Cleanup
            free(input);
            cleanup_matrix(weights, i);
            free(biases);
            free(output);
            tests++;
        }
    }
    printf("Ran %d random tests\n", tests);
}