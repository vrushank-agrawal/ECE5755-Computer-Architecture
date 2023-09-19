#ifndef TEST_CONV_H
#define TEST_CONV_H

void print_output(float ***output, int numFilters, int outputSize);

float ***malloc_image(int numChannels, int inputSize);
float ****malloc_kernel(int numFilters, int numChannels, int kernelSize);
float ***get_image_from_slide(int numChannels, int inputSize);
float ****get_kernel_from_slide(int numFilters, int numChannels, int kernelSize);
float ***get_expected_output_from_slides(int numFilters, int outputSize);

void get_image_values(float ***image, int inputSize);
void get_kernel_values(float ****kernel, int numFilters, int numChannels, int kernelSize);

void test_conv_null(void);
void test_bias_null(void);
void test_kernel_null(void);

void test_conv_slides(void);
void test_conv(void);

#endif // TEST_CONV_H
