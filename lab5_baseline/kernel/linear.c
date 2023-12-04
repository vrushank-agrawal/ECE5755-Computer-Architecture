#include <xmmintrin.h> // SSE intrinsics
#include <emmintrin.h> // SSE2 intrinsics
#include <pmmintrin.h> // SSE3 intrinsics
#include "linear.h"

float *linear(float *input, float **weights, float *biases, int inputSize, int outputSize)
{
	// Check for empty input
	if (input == NULL || inputSize == 0 || outputSize == 0)
	{
		return NULL;
	}

	float *output = malloc(outputSize * sizeof(*output));

	// Original Implementation
	// for (int i = 0; i < outputSize; i++)
	// {
	//   output[i] = biases[i];
	//   for (int j = 0; j < inputSize; j++)
	//   {
	//     output[i] += weights[i][j] * input[j];
	//   }
	// }

	for (int i = 0; i < outputSize; i++)
	{
		// Initialize sum with the bias for the current output element.
		__m128 sum = _mm_set_ps1(biases[i]);
		for (int j = 0; j < inputSize; j += 4)
		{
			// Load 4 adjacent weights from the weights matrix.
			__m128 weightVec = _mm_loadu_ps(&weights[i][j]);

			// Load 4 elements from the input vector.
			__m128 inputVec = _mm_loadu_ps(&input[j]);

			// Perform element-wise multiplication of the weight vector and input vector.
			__m128 mult = _mm_mul_ps(weightVec, inputVec);

			// Accumulate the results in the sum vector.
			sum = _mm_add_ps(sum, mult);
		}

		// Perform horizontal addition to compute total
		// sum by accumulating all four elements into one.
		sum = _mm_hadd_ps(sum, sum);
		sum = _mm_hadd_ps(sum, sum);


		// Store the final accumulated sum
		_mm_store_ss(&output[i], sum);
	}

	return output;
}
