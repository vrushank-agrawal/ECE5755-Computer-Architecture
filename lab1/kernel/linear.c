#include "linear.h"

float *linear(float *input, float **weights, float *biases, int inputSize, int outputSize)
{
    // Check for empty input
    if (input == NULL || inputSize == 0 || outputSize == 0 || weights == NULL || biases == NULL)
    {
        return NULL;
    }

    float *output = malloc(outputSize * sizeof(*output));

    /**** YOUR CODE HERE ****/
    for (int many=0; many < 100; many++)
        for (int i=0; i < outputSize; i++) {
            output[i] = biases[i];
            for (int j=0; j < inputSize; j++) {
                output[i] += input[j] * weights[j][i];
            }
        }

    return output;
}
