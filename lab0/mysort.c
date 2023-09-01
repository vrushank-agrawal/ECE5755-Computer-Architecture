#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void merge(int* array, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = array[left + i];
    for (int j = 0; j < n2; j++) R[j] = array[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) array[k++] = L[i++];
        else array[k++] = R[j++];
    }

    while (i < n1) array[k++] = L[i++];
    while (j < n2) array[k++] = R[j++];
}

void mergeSort(int* array, int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(array, left, mid);
    mergeSort(array, mid+1, right);
    merge(array, left, mid, right);
}

// void merge(
int *mysort(int *input, int n) {
    /***** YOUR CODE HERE *****/
    mergeSort(input, 0, n-1);
    return input;
}

// verify() checks that the array is sorted
// DO NOT call verify() when profiling your code
int verify(int *input, int n) {
    for (int i = 1; i < n; i++) {
        assert(input[i] >= input[i-1]);
    }
    printf("array is correctly sorted \n");
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: ./mysort <input_size> <input_file>\n");
        return 1;
    }
    int n = atoi(argv[1]);
    int *input = (int *) malloc(sizeof(int)*n);
    int *output; // you will need to allocate memory for output if not sorting in place
    FILE *fp = fopen(argv[2], "r");

    for (int i = 0; i < n; i++) {
        fscanf(fp, "%d,", &input[i] );
    }

    output = mysort(input, n);

    verify(output, n ); // keep this line commented out when profiling

    free(input);
    return 0;
}