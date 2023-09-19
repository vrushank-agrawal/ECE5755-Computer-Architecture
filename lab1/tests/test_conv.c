#include "unity/unity.h"
#include "../kernel/kernel.h"
#include "../utils/data_utils.h"
#include "test_conv.h"

/***************************/
/***** HELPER FUNCTIONS ****/
/***************************/

void print_output(float ***output, int numFilters, int outputSize)
{
    // print the output
    printf("Output:\n");
    for (int i=0; i < numFilters; i++) {
        for (int row=0; row < outputSize; row++) {
            for (int col=0; col < outputSize; col++) {
                printf("%f ", output[i][row][col]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

/***************************/
/********** MALLOC *********/
/***************************/

float ***malloc_image(int numChannels, int inputSize)
{
    float ***image = malloc(numChannels * sizeof(*image));
    for (int i=0; i < numChannels; i++) {
        image[i] = malloc(inputSize * sizeof(*image[i]));
        for (int j=0; j < inputSize; j++) {
            image[i][j] = malloc(inputSize * sizeof(*image[i][j]));
        }
    }
    return image;
}

float ****malloc_kernel(int numFilters, int numChannels, int kernelSize)
{
    float ****kernels = malloc(numFilters * sizeof(*kernels));
    for (int i=0; i < numFilters; i++) {
        kernels[i] = malloc(numChannels * sizeof(*kernels[i]));
        for (int j=0; j < numChannels; j++) {
            kernels[i][j] = malloc(kernelSize * sizeof(*kernels[i][j]));
            for (int k=0; k < kernelSize; k++) {
                kernels[i][j][k] = malloc(kernelSize * sizeof(*kernels[i][j][k]));
            }
        }
    }
    return kernels;
}

/**********************/
/***** SLIDE DATA *****/
/**********************/

float ***get_image_from_slide(int numChannels, int inputSize) {
    float ***image = malloc_image(numChannels, inputSize);
    int value = 0;
    for (int j = 0; j < 4; j++) {
        for (int k = 0; k < 4; k++) {
            image[0][j][k] = value++;
        }
    }
    return image;
}

float ****get_kernel_from_slide(int numFilters, int numChannels, int kernelSize)
{
    float ****kernels = malloc_kernel(numFilters, numChannels, kernelSize);

    for (int i=0; i < 4; i++)
        kernels[0][0][i%2][i/2] = 1;

    return kernels;
}

float ***get_expected_output_from_slides(int numFilters, int outputSize)
{
    float ***expectedOutput = malloc(numFilters * sizeof(*expectedOutput));
    for (int i=0; i < numFilters; i++) {
        expectedOutput[i] = malloc(outputSize * sizeof(*expectedOutput[i]));
        for (int j=0; j < outputSize; j++) {
            expectedOutput[i][j] = malloc(outputSize * sizeof(*expectedOutput[i][j]));
        }
    }

    expectedOutput[0][0][0] = 12;
    expectedOutput[0][0][1] = 16;
    expectedOutput[0][0][2] = 20;
    expectedOutput[0][1][0] = 28;
    expectedOutput[0][1][1] = 32;
    expectedOutput[0][1][2] = 36;
    expectedOutput[0][2][0] = 44;
    expectedOutput[0][2][1] = 48;
    expectedOutput[0][2][2] = 52;

    return expectedOutput;
}

void get_image_values(float ***image, int inputSize) {
    for (int i=0; i < 3; i++) {
        for (int j=0; j < inputSize; j++) {
            for (int k=0; k < inputSize; k++) {
                image[i][j][k] = i + j + k;
            }
        }
    }
}

void get_kernel_values(float ****kernel, int numFilters, int numChannels, int kernelSize) {
    for (int i=0; i < numFilters; i++) {
        for (int j=0; j < numChannels; j++) {
            for (int k=0; k < kernelSize; k++) {
                for (int l=0; l < kernelSize; l++) {
                    kernel[i][j][k][l] = i + j + k + l;
                }
            }
        }
    }
}

/***************************/
/********** TESTS **********/
/***************************/

/******* TEST NULL ********/

void test_image_null(void)
{
    int numChannels = 1;
    int numFilters = 1;
    int inputSize = 4;
    int kernelSize = 2;
    int outputSize = inputSize - kernelSize + 1;

    // get the image values
    float ***image = NULL;
    // get the kernel values
    float ****kernels = get_kernel_from_slide(numFilters, numChannels, kernelSize);
    // get the bias value
    float *biasData = malloc(outputSize * sizeof(*biasData));
    for (int i=0; i < numFilters; i++) biasData[i] = 2;
    // get the expected output
    float ***expectedOutput = get_expected_output_from_slides(numFilters, outputSize);

    // Run the convolution
    float ***convOutput = convolution(image, numChannels, kernels, biasData, numFilters, inputSize, kernelSize);

    // Check that the output is NULL
    TEST_ASSERT_NULL(convOutput);

    free(biasData);
    free(kernels);
    free(expectedOutput);
}

void test_bias_null(void)
{
    int numChannels = 1;
    int numFilters = 1;
    int inputSize = 4;
    int kernelSize = 2;
    int outputSize = inputSize - kernelSize + 1;

    // get the image values
    float ***image = get_image_from_slide(numChannels, inputSize);
    // get the kernel values
    float ****kernels = get_kernel_from_slide(numFilters, numChannels, kernelSize);
    // get the bias value
    float *biasData = NULL;
    // get the expected output
    float ***expectedOutput = get_expected_output_from_slides(numFilters, outputSize);

    // Run the convolution
    float ***convOutput = convolution(image, numChannels, kernels, biasData, numFilters, inputSize, kernelSize);

    // Check that the output is NULL
    TEST_ASSERT_NULL(convOutput);

    free(kernels);
    free(image);
    free(expectedOutput);
}

void test_kernel_null(void)
{
    int numChannels = 1;
    int numFilters = 1;
    int inputSize = 4;
    int kernelSize = 2;
    int outputSize = inputSize - kernelSize + 1;

    // get the image values
    float ***image = get_image_from_slide(numChannels, inputSize);
    // get the kernel values
    float ****kernels = NULL;
    // get the bias value
    float *biasData = malloc(outputSize * sizeof(*biasData));
    for (int i=0; i < numFilters; i++) biasData[i] = 2;
    // get the expected output
    float ***expectedOutput = get_expected_output_from_slides(numFilters, outputSize);

    // Run the convolution
    float ***convOutput = convolution(image, numChannels, kernels, biasData, numFilters, inputSize, kernelSize);

    // Check that the output is NULL
    TEST_ASSERT_NULL(convOutput);

    free(biasData);
    free(image);
    free(expectedOutput);
}


/******* TEST SLIDES ********/


void test_conv_slides(void)
{
    int numChannels = 1;
    int numFilters = 1;
    int inputSize = 4;
    int kernelSize = 2;
    int outputSize = inputSize - kernelSize + 1;

    // get the image values
    float ***image = get_image_from_slide(numChannels, inputSize);
    // get the kernel values
    float ****kernels = get_kernel_from_slide(numFilters, numChannels, kernelSize);
    // get the bias value
    float *biasData = malloc(outputSize * sizeof(*biasData));
    for (int i=0; i < numFilters; i++) biasData[i] = 2;
    // get the expected output
    float ***expectedOutput = get_expected_output_from_slides(numFilters, outputSize);

    // Run the convolution
    float ***convOutput = convolution(image, numChannels, kernels, biasData, numFilters, inputSize, kernelSize);

    // Check that the output is not NULL
    TEST_ASSERT_NOT_NULL(convOutput);

    for (int i=0; i < numFilters; i++) {
        for (int row=0; row < outputSize; row++) {
            for (int col=0; col < outputSize; col++) {
                TEST_ASSERT_FLOAT_WITHIN(0.0001, expectedOutput[i][row][col], convOutput[i][row][col]);
            }
        }
    }

    free(biasData);
    free(kernels);
    free(image);
    free(expectedOutput);
}

void test_conv(void)
{
    int numChannels = 3;
    int numFilters = 1;
    int inputSize = 3;
    int kernelSize = 3;
    int outputSize = inputSize - kernelSize + 1;

    // get the image values
    float ***image = malloc(sizeof(*image));
    for (int i=0; i < numChannels; i++) {
        image[i] = malloc(inputSize * sizeof(*image[i]));
        for (int j=0; j < inputSize; j++) {
            image[i][j] = malloc(inputSize * sizeof(*image[i][j]));
        }
    }
    get_image_values(image, inputSize);

    // get the kernel values
    float ****kernels = malloc(numFilters * sizeof(*kernels));
    for (int i=0; i < numFilters; i++) {
        kernels[i] = malloc(numChannels * sizeof(*kernels[i]));
        for (int j=0; j < numChannels; j++) {
            kernels[i][j] = malloc(kernelSize * sizeof(*kernels[i][j]));
            for (int k=0; k < kernelSize; k++) {
                kernels[i][j][k] = malloc(kernelSize * sizeof(*kernels[i][j][k]));
            }
        }
    }
    get_kernel_values(kernels, numFilters, numChannels, kernelSize);

    // get the bias value
    float *biasData = malloc(outputSize * sizeof(*biasData));
    for (int i=0; i < numFilters; i++) {
        biasData[i] = i;
    }

    float expectedOutput[1][1][1] = {
        {{  0.0 }}
    };

    float ***convOutput = convolution(image, numChannels, kernels, biasData, numFilters, inputSize, kernelSize);

    // Check that the output is not NULL
    TEST_ASSERT_NOT_NULL(convOutput);

    for (int i=0; i < numFilters; i++) {
        for (int row=0; row < outputSize; row++) {
            for (int col=0; col < outputSize; col++) {
                TEST_ASSERT_FLOAT_WITHIN(0.0001, expectedOutput[i][row][col], convOutput[i][row][col]);
            }
        }
    }


    free(biasData);
    free(kernels);
    free(image);
}

/****** TEST RANDOM *******/
