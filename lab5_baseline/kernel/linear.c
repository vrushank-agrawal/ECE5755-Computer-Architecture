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
		// _mm_set_ps1 creates a vector (sum) with all four elements set to biases[i].
		__m128 sum = _mm_set_ps1(biases[i]);

		for (int j = 0; j < inputSize; j += 4)
		{
			// Load 4 adjacent weights from the weights matrix for the current output element.
			// _mm_loadu_ps loads 4 float values from the address &weights[i][j] into weightVec.
			__m128 weightVec = _mm_loadu_ps(&weights[i][j]);

			// Load 4 elements from the input vector.
			// _mm_loadu_ps loads 4 float values from the address &input[j] into inputVec.
			__m128 inputVec = _mm_loadu_ps(&input[j]);

			// Perform element-wise multiplication of the weight vector and input vector.
			// _mm_mul_ps multiplies corresponding elements from weightVec and inputVec,
			// storing the results in mult.
			__m128 mult = _mm_mul_ps(weightVec, inputVec);

			// Accumulate the results in the sum vector.
			// _mm_add_ps performs element-wise addition between sum and mult,
			// storing the results back in sum.
			sum = _mm_add_ps(sum, mult);
		}

		// Perform horizontal addition across the sum vector to compute the total sum.
		// _mm_hadd_ps performs pairwise addition across elements of sum and stores the
		// results back in sum. This is done twice to accumulate all four elements into one.
		sum = _mm_hadd_ps(sum, sum);
		sum = _mm_hadd_ps(sum, sum);

		// Store the final accumulated sum into the output array.
		// _mm_store_ss stores the lowest element of sum into output[i].
		_mm_store_ss(&output[i], sum);
	}
	
	return output;
}
