#include "functional.h"
#include <math.h>

float relu(float x)
{
    return (x > 0.) ? x : 0.;
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

    float d = 0.;
    for (int i=0; i < inputSize; i++)
        d += expf(input[i]);

    for (int i=0; i < inputSize; i++)
        softmaxOutput[i] = expf(input[i]) / d;

    return softmaxOutput;
}