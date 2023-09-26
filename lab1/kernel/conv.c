#include "conv.h"

// Basic convolution operation
float ***convolution(float ***image,
                    int numChannels,
                    float ****kernel,
                    float *biasData,
                    int numFilters,
                    int inputSize,
                    int kernelSize
){

    if (image == NULL || kernel == NULL || biasData == NULL) {
        printf("Image, kernel, or bias is NULL.\n");
        return NULL;
    }

    if (kernelSize <= 0 || inputSize <= 0 || numChannels <= 0 || numFilters <= 0) {
        printf("Invalid input size.\n");
        return NULL;
    }

    if (kernelSize > inputSize) {
        printf("Kernel size cannot be larger than input size.\n");
        return NULL;
    }

    int outputSize = inputSize - kernelSize + 1;

    // Allocate memory for the convolution output
    float ***convOutput = malloc(numFilters * sizeof(*convOutput));
    for (int i = 0; i < numFilters; i++)
    {
        convOutput[i] = malloc(outputSize * sizeof(*convOutput[i]));
        for (int j = 0; j < outputSize; j++)
        {
            convOutput[i][j] = malloc(outputSize * sizeof(*convOutput[i][j]));
        }
    }

    for (int many=0; many < 1000; many++)
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
