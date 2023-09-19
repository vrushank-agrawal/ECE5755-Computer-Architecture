#include "unity/unity.h"
#include "../kernel/kernel.h"
#include "../utils/data_utils.h"
#include "test_conv.h"

#ifdef DEBUG
#define DEBUG_MODE 1
#endif

/***************************/
/***** HELPER FUNCTIONS ****/
/***************************/

void print_output(float ***output, int numFilters, int outputSize)
{
    // print the output
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

float ***malloc_output(int numFilters, int outputSize)
{
    float ***output = malloc(numFilters * sizeof(*output));
    for (int i=0; i < numFilters; i++) {
        output[i] = malloc(outputSize * sizeof(*output[i]));
        for (int j=0; j < outputSize; j++) {
            output[i][j] = malloc(outputSize * sizeof(*output[i][j]));
        }
    }
    return output;
}

/**********************/
/***** SLIDE DATA *****/
/**********************/

void set_first_image_channel(float ***image, int inputSize) {
    int value = 0;
    for (int j=0; j < inputSize; j++) {
        for (int k=0; k < inputSize; k++) {
            image[0][j][k] = value++;
        }
    }
}

float ***get_image_from_slide(int numChannels, int inputSize) {
    float ***image = malloc_image(numChannels, inputSize);
    set_first_image_channel(image, inputSize);
    return image;
}

float ***get_image_from_slide2(int numChannels, int inputSize) {
    float ***image = malloc_image(numChannels, inputSize);
    set_first_image_channel(image, inputSize);
    int value = 1;
    for (int j = 0; j < 4; j++) {
        for (int k = 0; k < 4; k++) {
            image[1][j][k] = value;
            if (k%2 == 1) value+=2;
        }
    }
    return image;
}

float ****get_kernel_from_slide(int numFilters, int numChannels, int kernelSize)
{
    float ****kernels = malloc_kernel(numFilters, numChannels, kernelSize);
    for (int k=0; k < numFilters; k++)
        for (int j=0; j < numChannels; j++)
            for (int i=0; i < 4; i++)
                kernels[k][j][i%2][i/2] = j+1;
    return kernels;
}

float ***get_expected_output_from_slides(int numFilters, int outputSize)
{
    float ***expectedOutput = malloc_output(numFilters, outputSize);
    for (int i=0; i < numFilters; i++) {
        expectedOutput[i][0][0] = 12;
        expectedOutput[i][0][1] = 16;
        expectedOutput[i][0][2] = 20;
        expectedOutput[i][1][0] = 28;
        expectedOutput[i][1][1] = 32;
        expectedOutput[i][1][2] = 36;
        expectedOutput[i][2][0] = 44;
        expectedOutput[i][2][1] = 48;
        expectedOutput[i][2][2] = 52;
    }
    return expectedOutput;
}

float ***get_expected_output_from_slides2(int numFilters, int outputSize)
{
    float ***expectedOutput = get_expected_output_from_slides(numFilters, outputSize);
    for (int i=0; i < numFilters; i++) {
        for (int row=0; row < outputSize; row++) {
            for (int col=0; col < outputSize; col++) {
                expectedOutput[i][row][col] *= 3;
            }
        }
    }
    return expectedOutput;
}

/******** Random Generator ********/

float ***get_image_values(int numChannels, int inputSize) {
    float ***image = malloc_image(numChannels, inputSize);
    for (int i=0; i < numChannels; i++) {
        for (int j=0; j < inputSize; j++) {
            for (int k=0; k < inputSize; k++) {
                image[i][j][k] = (float)rand();
            }
        }
    }
    return image;
}

float ****get_kernel_values(int numFilters, int numChannels, int kernelSize) {
    float ****kernel = malloc_kernel(numFilters, numChannels, kernelSize);
    for (int i=0; i < numFilters; i++) {
        for (int j=0; j < numChannels; j++) {
            for (int k=0; k < kernelSize; k++) {
                for (int l=0; l < kernelSize; l++) {
                    kernel[i][j][k][l] = (float)rand();
                }
            }
        }
    }
    return kernel;
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
    // Check that the output is correct
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
    free(convOutput);
}

void test_conv_slides2(void)
{
    int numChannels = 2;
    int numFilters = 1;
    int inputSize = 4;
    int kernelSize = 2;
    int outputSize = inputSize - kernelSize + 1;

    // get the image values
    float ***image = get_image_from_slide2(numChannels, inputSize);

    #ifdef DEBUG_MODE
    printf("Image:\n");
    print_output(image, numChannels, inputSize);
    #endif

    // get the kernel values
    float ****kernels = get_kernel_from_slide(numFilters, numChannels, kernelSize);

    #ifdef DEBUG_MODE
    printf("Kernels:\n");
    for (int i=0; i < numFilters; i++) {
        printf("Kernel filter %d:\n", i);
        print_output(kernels[i], numChannels, kernelSize);
    }
    #endif

    // get the bias value
    float *biasData = malloc(outputSize * sizeof(*biasData));
    for (int i=0; i < numFilters; i++) biasData[i] = 2;

    // get the expected output
    float ***expectedOutput = get_expected_output_from_slides2(numFilters, outputSize);

    #ifdef DEBUG_MODE
    printf("Expected Output:\n");
    print_output(expectedOutput, numFilters, outputSize);
    #endif

    // Run the convolution
    float ***convOutput = convolution(image, numChannels, kernels, biasData, numFilters, inputSize, kernelSize);

    #ifdef DEBUG_MODE
    printf("Conv Output:\n");
    print_output(convOutput, numFilters, outputSize);
    #endif

    // Check that the output is not NULL
    TEST_ASSERT_NOT_NULL(convOutput);
    // Check that the output is correct
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
    free(convOutput);
}

void test_conv_slides3(void)
{
    int numChannels = 2;
    int numFilters = 2;
    int inputSize = 4;
    int kernelSize = 2;
    int outputSize = inputSize - kernelSize + 1;

    // get the image values
    float ***image = get_image_from_slide2(numChannels, inputSize);

    #ifdef DEBUG_MODE
    printf("Image:\n");
    print_output(image, numChannels, inputSize);
    #endif

    // get the kernel values
    float ****kernels = get_kernel_from_slide(numFilters, numChannels, kernelSize);

    #ifdef DEBUG_MODE
    printf("Kernels:\n");
    for (int i=0; i < numFilters; i++) {
        printf("Kernel filter %d:\n", i);
        print_output(kernels[i], numChannels, kernelSize);
    }
    #endif

    // get the bias value
    float *biasData = malloc(outputSize * sizeof(*biasData));
    for (int i=0; i < numFilters; i++) biasData[i] = 2;

    // get the expected output
    float ***expectedOutput = get_expected_output_from_slides2(numFilters, outputSize);

    #ifdef DEBUG_MODE
    printf("Expected Output:\n");
    print_output(expectedOutput, numFilters, outputSize);
    #endif

    // Run the convolution
    float ***convOutput = convolution(image, numChannels, kernels, biasData, numFilters, inputSize, kernelSize);

    #ifdef DEBUG_MODE
    printf("Conv Output:\n");
    print_output(convOutput, numFilters, outputSize);
    #endif

    // Check that the output is not NULL
    TEST_ASSERT_NOT_NULL(convOutput);
    // Check that the output is correct
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
    free(convOutput);
}

/****** TEST RANDOM *******/

float ***expected_convolution(float ***image, int numChannels, float ****kernel, float *biasData, int numFilters, int inputSize, int kernelSize)
{
    int outputSize = inputSize - kernelSize + 1;

    // Allocate memory for the convolution output
    float ***convOutput = malloc(numFilters * sizeof(*convOutput));
    for (int i = 0; i < numFilters; i++){
        convOutput[i] = malloc(outputSize * sizeof(*convOutput[i]));
        for (int j = 0; j < outputSize; j++){
            convOutput[i][j] = malloc(outputSize * sizeof(*convOutput[i][j]));
        }
    }

    // Perform the convolution operation
    for (int i=0; i < numFilters; i++) {
        for (int row=0; row < outputSize; row++) {
            for (int col=0; col < outputSize; col++) {
                // add the bias
                convOutput[i][row][col] = biasData[i];
                for (int channel=0; channel < numChannels; channel++) {
                    for (int krow=0; krow < kernelSize; krow++) {
                        for (int kcol=0; kcol < kernelSize; kcol++) {
                            convOutput[i][row][col] += image[channel][row+krow][col+kcol] * kernel[i][channel][kcol][krow];
                        }
                    }
                }
            }
        }
    }

    return convOutput;
}


void test_random_conv(void)
{

    int random_tests = 0;
    for (int filter=3; filter < 5; filter++)
    {
        for (int channel=1; channel < 3; channel++)
        {
            for (int inputSize=5; inputSize < 28; inputSize+=3)
            {
                for (int kernelSize=2; kernelSize < 4; kernelSize++)
                {
                    int outputSize = inputSize - kernelSize + 1;

                    // get the image values
                    float ***image = get_image_values(channel, inputSize);
                    // get the kernel values
                    float ****kernels = get_kernel_values(filter, channel, kernelSize);
                    // get the bias value
                    float *biasData = malloc(filter * sizeof(*biasData));
                    for (int i=0; i < filter; i++) biasData[i] = i;
                    // get the expected output
                    float ***expectedOutput = expected_convolution(image, channel, kernels, biasData, filter, inputSize, kernelSize);

                    // Run the convolution
                    float ***convOutput = convolution(image, channel, kernels, biasData, filter, inputSize, kernelSize);

                    // Check that the output is not NULL
                    TEST_ASSERT_NOT_NULL(convOutput);
                    // Check that the output is correct
                    for (int i=0; i < filter; i++) {
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
                    free(convOutput);

                    random_tests++;
                }
            }
        }
    }

    printf("\nNumber of random tests: %d\n", random_tests);
}