#include "unity/unity.h"
#include "../kernel/kernel.h"
#include "test_functional.h"
#include <float.h>

#ifdef PROFILING
#define PROFILE 1
#endif

void test_softmax(void) {
    float input[] = {1.0, 2.0, 3.0};
    float *output = softmax(input, 3);

    #ifndef PROFILE
    printf("RUNNING UNITY TEST\n");
    float sum = 0.0;

    // Check that the sum of the output is 1
    for (int i = 0; i < 3; i++) {
        sum += output[i];
    }

    TEST_ASSERT_FLOAT_WITHIN(1e-6, 1.0, sum);

    // Check that the maximum input corresponds to the maximum output
    int maxInputIndex = 0;
    int maxOutputIndex = 0;

    for (int i = 1; i < 3; i++) {
        if (input[i] > input[maxInputIndex]) {
            maxInputIndex = i;
        }
        if (output[i] > output[maxOutputIndex]) {
            maxOutputIndex = i;
        }
    }

    TEST_ASSERT_EQUAL_INT(maxInputIndex, maxOutputIndex);
    #endif

    // Cleanup
    free(output);
}

void test_softmax_long(void) {
    float input[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0,
                    8.0, 9.0, 10.0, 11.0, 12.0, 13.0,
                    14.0, 15.0, 16.0, 17.0, 18.0, 19.0,
                    20.0, 21.0, 22.0, 23.0, 24.0, 25.0};

    float *output = softmax(input, 25);

    #ifndef PROFILE
    printf("RUNNING UNITY TEST\n");
    float sum = 0.0;

    // Check that the sum of the output is 1
    for (int i = 0; i < 25; i++) {
        sum += output[i];
    }

    TEST_ASSERT_FLOAT_WITHIN(1e-6, 1.0, sum);

    // Check that the maximum input corresponds to the maximum output
    int maxInputIndex = 0;
    int maxOutputIndex = 0;

    for (int i = 1; i < 25; i++) {
        if (input[i] > input[maxInputIndex]) {
            maxInputIndex = i;
        }
        if (output[i] > output[maxOutputIndex]) {
            maxOutputIndex = i;
        }
    }

    TEST_ASSERT_EQUAL_INT(maxInputIndex, maxOutputIndex);
    #endif

    // Cleanup
    free(output);
}

void test_softmax_large(void) {
    // C floats cannot represent numbers larger than 2^127
    float input[] = {30.0, 40.0, 50.0};
    float *output = softmax(input, 3);

    #ifndef PROFILE
    printf("RUNNING UNITY TEST\n");
    float sum = 0.0;

    // Check that the sum of the output is 1
    for (int i = 0; i < 3; i++) {
        sum += output[i];
    }

    TEST_ASSERT_FLOAT_WITHIN(1e-6, 1.0, sum);

    // Check that the maximum input corresponds to the maximum output
    int maxInputIndex = 0;
    int maxOutputIndex = 0;

    for (int i = 1; i < 3; i++) {
        if (input[i] > input[maxInputIndex]) {
            maxInputIndex = i;
        }
        if (output[i] > output[maxOutputIndex]) {
            maxOutputIndex = i;
        }
    }

    TEST_ASSERT_EQUAL_INT(maxInputIndex, maxOutputIndex);
    #endif

    // Cleanup
    free(output);
}

void test_relu(void) {
    float inputs[] = {3.0f, 0.0f, -3.0f};
    float expected_outputs[] = {3.0f, 0.0f, 0.0f};
    int test_cases = sizeof(inputs)/sizeof(inputs[0]);

    for(int i = 0; i < test_cases; i++) {
        float output = relu(inputs[i]);
        #ifndef PROFILE
        printf("RUNNING UNITY TEST\n");
        TEST_ASSERT_FLOAT_WITHIN(1e-6, expected_outputs[i], output);
        #endif
    }
}

void test_relu_large(void) {
    float input[] = {FLT_MAX, -FLT_MIN};
    float expected_outputs[] = {FLT_MAX, -FLT_MIN};
    int test_cases = sizeof(input)/sizeof(input[0]);

    for(int i = 0; i < test_cases; i++) {
        float output = relu(input[i]);
        #ifndef PROFILE
        printf("RUNNING UNITY TEST\n");
        TEST_ASSERT_FLOAT_WITHIN(1e-6, expected_outputs[i], output);
        #endif
    }
}

void test_relu_large_neg(void) {
    float input[] = {FLT_MIN, -FLT_MAX};
    float expected_outputs[] = {0.0f, 0.0f};
    int test_cases = sizeof(input)/sizeof(input[0]);

    for(int i = 0; i < test_cases; i++) {
        float output = relu(input[i]);
        #ifndef PROFILE
        printf("RUNNING UNITY TEST\n");
        TEST_ASSERT_FLOAT_WITHIN(1e-6, expected_outputs[i], output);
        #endif
    }

}

// Add more test cases as needed