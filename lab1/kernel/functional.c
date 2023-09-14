#include "functional.h"

float relu(float x)
{
    /**** YOUR CODE HERE ****/
}

void applyRelu(float *input, int inputSize)
{
    for (int i = 0; i < inputSize; i++)
    {
        input[i] = relu(input[i]);
    }
}

float *softmax(float *input, int inputSize)
{
    float *softmaxOutput = malloc(inputSize * sizeof(*softmaxOutput));

    /**** YOUR CODE HERE ****/

    return softmaxOutput;
}