#include "unity/unity.h"
#include "../kernel/kernel.h"
#include "../utils/data_utils.h"
#include "test_conv.h"

/**** HELPER FUNCTIONS ****/
/**** YOUR CODE HERE ****/

void test_conv(void)
{
    /**** YOUR CODE HERE ****/
    int numChannels = 3;
    int numFilters = 8;
    // float ****images = loadImages("", 1000, numChannels);
    // float ****kernels = loadKernels("", numFilters, numChannels);
    // float *biasData = loadBiases("", numFilters);
    int inputSize = 28;
    int kernelSize = 3;

    float ****convOutput = malloc(numFilters * sizeof(*convOutput));

    for (int i=0; i < 1000; i++) {
        float convOutput[i] = convolution(images, numChannels, kernels, biasData, numFilters, inputSize, kernelSize);
    }

    // Check that the output is not NULL
    TEST_ASSERT_NOT_NULL(convOutput);

    // Check that the output is the correct size
    int outputSize = inputSize - kernelSize + 1;
    TEST_ASSERT_EQUAL_INT(outputSize, 26);

    // Check that the output is correct
    // float ***expectedOutput = ;

    for (int i=0; i < numFilters; i++) {
        for (int row=0; row < outputSize; row++) {
            for (int col=0; col < outputSize; col++) {
                TEST_ASSERT_FLOAT_WITHIN(0.0001, expectedOutput[i][row][col], convOutput[i][row][col]);
            }
        }
    }

    destroyImages(images, 1000, numChannels);

}

