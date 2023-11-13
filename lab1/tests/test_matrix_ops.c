#include "unity/unity.h"
#include "../kernel/kernel.h"
#include "test_matrix_ops.h"
#include <stdio.h>

/**** HELPER FUNCTIONS ****/
void print_matrix(float **matrix, int rows, int cols) {
    printf("\n");
    for (int i=0; i < rows; i++) {
        printf("[");
        for (int j=0; j < cols; j++) {
            printf(" %f,", matrix[i][j]);
        }
        printf("]\n");
    }
}

float **malloc_matrix(int rows, int cols) {
    float** mat = (float**)malloc(rows * sizeof(float*));
    for (int i = 0; i < rows; i++) {
        mat[i] = (float*)malloc(cols * sizeof(float));
    }
    return mat;
}

float** generate_random_matrix(int rows, int cols) {
    float** mat = malloc_matrix(rows, cols);

    for (int i=0; i < rows; i++) {
        for (int j=0; j < cols; j++) {
            mat[i][j] = (float)rand()/(float)(RAND_MAX);
        }
    }
    return mat;
}

float **ans_20_20(void) {
    float result[20][20] =
        {{  9920.0,  19840.0,  29760.0,  39680.0,  49600.0,  59520.0,  69440.0,  79360.0,  89280.0,  99200.0, 109120.0, 119040.0, 128960.0, 138880.0, 148800.0, 158720.0, 168640.0, 178560.0, 188480.0, 198400.0},
        { 10385.0,  20770.0,  31155.0,  41540.0,  51925.0,  62310.0,  72695.0,  83080.0,  93465.0, 103850.0, 114235.0, 124620.0, 135005.0, 145390.0, 155775.0, 166160.0, 176545.0, 186930.0, 197315.0, 207700.0},
        { 10850.0,  21700.0,  32550.0,  43400.0,  54250.0,  65100.0,  75950.0,  86800.0,  97650.0, 108500.0, 119350.0, 130200.0, 141050.0, 151900.0, 162750.0, 173600.0, 184450.0, 195300.0, 206150.0, 217000.0},
        { 11315.0,  22630.0,  33945.0,  45260.0,  56575.0,  67890.0,  79205.0,  90520.0, 101835.0, 113150.0, 124465.0, 135780.0, 147095.0, 158410.0, 169725.0, 181040.0, 192355.0, 203670.0, 214985.0, 226300.0},
        { 11780.0,  23560.0,  35340.0,  47120.0,  58900.0,  70680.0,  82460.0,  94240.0, 106020.0, 117800.0, 129580.0, 141360.0, 153140.0, 164920.0, 176700.0, 188480.0, 200260.0, 212040.0, 223820.0, 235600.0},
        { 12245.0,  24490.0,  36735.0,  48980.0,  61225.0,  73470.0,  85715.0,  97960.0, 110205.0, 122450.0, 134695.0, 146940.0, 159185.0, 171430.0, 183675.0, 195920.0, 208165.0, 220410.0, 232655.0, 244900.0},
        { 12710.0,  25420.0,  38130.0,  50840.0,  63550.0,  76260.0,  88970.0, 101680.0, 114390.0, 127100.0, 139810.0, 152520.0, 165230.0, 177940.0, 190650.0, 203360.0, 216070.0, 228780.0, 241490.0, 254200.0},
        { 13175.0,  26350.0,  39525.0,  52700.0,  65875.0,  79050.0,  92225.0, 105400.0, 118575.0, 131750.0, 144925.0, 158100.0, 171275.0, 184450.0, 197625.0, 210800.0, 223975.0, 237150.0, 250325.0, 263500.0},
        { 13640.0,  27280.0,  40920.0,  54560.0,  68200.0,  81840.0,  95480.0, 109120.0, 122760.0, 136400.0, 150040.0, 163680.0, 177320.0, 190960.0, 204600.0, 218240.0, 231880.0, 245520.0, 259160.0, 272800.0},
        { 14105.0,  28210.0,  42315.0,  56420.0,  70525.0,  84630.0,  98735.0, 112840.0, 126945.0, 141050.0, 155155.0, 169260.0, 183365.0, 197470.0, 211575.0, 225680.0, 239785.0, 253890.0, 267995.0, 282100.0},
        { 14570.0,  29140.0,  43710.0,  58280.0,  72850.0,  87420.0, 101990.0, 116560.0, 131130.0, 145700.0, 160270.0, 174840.0, 189410.0, 203980.0, 218550.0, 233120.0, 247690.0, 262260.0, 276830.0, 291400.0},
        { 15035.0,  30070.0,  45105.0,  60140.0,  75175.0,  90210.0, 105245.0, 120280.0, 135315.0, 150350.0, 165385.0, 180420.0, 195455.0, 210490.0, 225525.0, 240560.0, 255595.0, 270630.0, 285665.0, 300700.0},
        { 15500.0,  31000.0,  46500.0,  62000.0,  77500.0,  93000.0, 108500.0, 124000.0, 139500.0, 155000.0, 170500.0, 186000.0, 201500.0, 217000.0, 232500.0, 248000.0, 263500.0, 279000.0, 294500.0, 310000.0},
        { 15965.0,  31930.0,  47895.0,  63860.0,  79825.0,  95790.0, 111755.0, 127720.0, 143685.0, 159650.0, 175615.0, 191580.0, 207545.0, 223510.0, 239475.0, 255440.0, 271405.0, 287370.0, 303335.0, 319300.0},
        { 16430.0,  32860.0,  49290.0,  65720.0,  82150.0,  98580.0, 115010.0, 131440.0, 147870.0, 164300.0, 180730.0, 197160.0, 213590.0, 230020.0, 246450.0, 262880.0, 279310.0, 295740.0, 312170.0, 328600.0},
        { 16895.0,  33790.0,  50685.0,  67580.0,  84475.0, 101370.0, 118265.0, 135160.0, 152055.0, 168950.0, 185845.0, 202740.0, 219635.0, 236530.0, 253425.0, 270320.0, 287215.0, 304110.0, 321005.0, 337900.0},
        { 17360.0,  34720.0,  52080.0,  69440.0,  86800.0, 104160.0, 121520.0, 138880.0, 156240.0, 173600.0, 190960.0, 208320.0, 225680.0, 243040.0, 260400.0, 277760.0, 295120.0, 312480.0, 329840.0, 347200.0},
        { 17825.0,  35650.0,  53475.0,  71300.0,  89125.0, 106950.0, 124775.0, 142600.0, 160425.0, 178250.0, 196075.0, 213900.0, 231725.0, 249550.0, 267375.0, 285200.0, 303025.0, 320850.0, 338675.0, 356500.0},
        { 18290.0,  36580.0,  54870.0,  73160.0,  91450.0, 109740.0, 128030.0, 146320.0, 164610.0, 182900.0, 201190.0, 219480.0, 237770.0, 256060.0, 274350.0, 292640.0, 310930.0, 329220.0, 347510.0, 365800.0},
        { 18755.0,  37510.0,  56265.0,  75020.0,  93775.0, 112530.0, 131285.0, 150040.0, 168795.0, 187550.0, 206305.0, 225060.0, 243815.0, 262570.0, 281325.0, 300080.0, 318835.0, 337590.0, 356345.0, 375100.0}};

    return result;
}

void cleanup_matrix(float** mat, int row_size) {
    for (int i=0; i < row_size; i++) {
        free(mat[i]);
    }
    free(mat);
}

float **generate_sparse_matrix(int rows, int cols, float sparsity) {
    // Generate a random matrix
    float** mat = malloc_matrix(rows, cols);

    for (int i=0; i < rows; i++) {
        for (int j=0; j < cols; j++) {
            float r = (float)rand()/(float)(RAND_MAX);
            if (r < sparsity) {
                mat[i][j] = 0;
            } else {
                mat[i][j] = r;
            }
        }
    }
    return mat;
}

/************************/
/**** MAIN FUNCTIONS ****/
/************************/

void test_matmul_square_matrices(void)
{
    /**** YOUR CODE HERE ****/
    float **A = malloc_matrix(2, 2);
    float **B = malloc_matrix(2, 2);

    for (int j=0; j < 2; j++) {
        for (int k=0; k < 2; k++) {
            A[j][k] = (j+1) + (k+1);
            B[j][k] = (j+1) * (k+1);
        }
    }

    float **C = matmul_blocking((float **)A, (float **)B, 2, 2, 2, 2, -1);
    C = matmul((float **)A, (float **)B, 2, 2, 2, 2);
    // print_matrix(C, 2, 2);

    #ifndef PROFILING
    printf("RUNNING UNITY TEST\n");
    float Ans[][2] = {{8, 16}, {11, 22}};
    for (int i=0; i < 2; i++) {
        for (int j=0; j < 2; j++) {
            UNITY_TEST_ASSERT_FLOAT_WITHIN(0.0001, Ans[i][j], C[i][j], __LINE__, "Wrong sum");
            TEST_ASSERT_EQUAL_INT(sizeof(C[i][j]), sizeof(float));
        }
    }
    #endif

    // Cleanup
    cleanup_matrix(A, 2);
    cleanup_matrix(B, 2);
    cleanup_matrix(C, 2);
}

void test_matmul(void) {
    // Setup
    float **A = malloc_matrix(2, 3);
    float **B = malloc_matrix(3, 2);

    for (int j=0; j < 2; j++) {
        for (int k=0; k < 3; k++) {
            A[j][k] = (j+1) + (k+1);
            B[k][j] = (j+1) * (k+1);
        }
    }

    // Run function under test
    // float **C = matmul(A, B, 2, 3, 3, 2);
    float **C = matmul_blocking(A, B, 2, 3, 3, 2, -1);
    print_matrix(C, 2, 2);

    // Check expectations
    #ifndef PROFILING
    printf("RUNNING UNITY TEST\n");
    float Ans[][2] = {{20.0, 40.0}, {26.0, 52.0}};
    for (int i=0; i < 2; i++) {
        for (int j=0; j < 2; j++) {
            UNITY_TEST_ASSERT_FLOAT_WITHIN(0.0001, Ans[i][j], C[i][j], __LINE__, "Wrong sum");
            TEST_ASSERT_EQUAL_INT(sizeof(C[i][j]), sizeof(float));
        }
    }
    #endif

    // Cleanup
    cleanup_matrix(A, 2);
    cleanup_matrix(B, 3);
    cleanup_matrix(C, 2);
}

void test_matmul_large(void)
// void test_matmul_large(int block_size, int fn)
{
    // Setup
    float **A = malloc_matrix(20, 30);
    float **B = malloc_matrix(30, 20);

    for (int j=0; j < 20; j++) {
        for (int k=0; k < 30; k++) {
            A[j][k] = (j+1) + (k+1);
            B[k][j] = (j+1) * (k+1);
        }
    }

    float **C;
    C = matmul_multithread(A, B, 20, 30, 30, 20);
    printf("rows = %i, cols = %i, threads = %i\n", 20, 20, NUM_THREADS);

    #ifdef DEBUG
    print_matrix(C, 20, 20);
    #endif

    // Check expectations
    #ifndef PROFILING
    printf("RUNNING UNITY TEST\n");
    for (int i=0; i < 20; i++) {
        for (int j=0; j < 20; j++) {
            float sum = 0;
            for (int k=0; k < 30; k++) {
                sum += A[i][k] * B[k][j];
            }
            UNITY_TEST_ASSERT_FLOAT_WITHIN(0.0001, sum, C[i][j], __LINE__, "Wrong sum");
            TEST_ASSERT_EQUAL_INT(sizeof(C[i][j]), sizeof(float));
        }
    }
    #endif

    // Cleanup
    cleanup_matrix(A, 20);
    cleanup_matrix(B, 30);
    cleanup_matrix(C, 20);
}

void test_matmul_random(void)
// void test_matmul_random(int block_size, int fn)
{
    /**** YOUR CODE HERE ****/
    int i = 1000;
    int a = 1005;
    float **A = generate_random_matrix(i, a);
    float **B = generate_random_matrix(a, i);
    float **C;

    C = matmul_multithread(A, B, i, a, a, i);
    printf("rows = %i, cols = %i, threads = %i\n", i, i, NUM_THREADS);

    #ifndef PROFILING
    printf("RUNNING UNITY TEST\n");
    for (int j=0; j < i; j++) {
        for (int k=0; k < i; k++) {
            float sum = 0;
            for (int l=0; l < a; l++) {
                sum += A[j][l] * B[l][k];
            }
            UNITY_TEST_ASSERT_FLOAT_WITHIN(0.0001, sum, C[j][k], __LINE__, "Wrong sum");
            TEST_ASSERT_EQUAL_INT(sizeof(C[j][k]), sizeof(float));
        }
    }
    #endif

    // Cleanup
    cleanup_matrix(A, i);
    cleanup_matrix(B, a);
    cleanup_matrix(C, i);
}

void test_matmul_incompatible_dimensions(void)
{
    // Setup
    float **A = malloc_matrix(2, 3);
    float **B = malloc_matrix(2, 2);

    // Run function under test
    float **C = matmul_blocking(A, B, 2, 3, 2, 2, -1);

    // Check expectations
    UNITY_TEST_ASSERT_NULL(C, __LINE__, "Expected NULL!");

    // Cleanup
    cleanup_matrix(A, 2);
    cleanup_matrix(B, 2);
}

#ifndef PROFILING
void test_matmul_sparse (void)
#else
void test_matmul_sparse(int size, float sparse)
#endif
{
    int rows = 10;
    int cols = 11;
    float sparsity = 0.9;

    #ifdef PROFILING
    sparsity = sparse;
    if (size == 0) {
        rows = 20;
        cols = 30;
    } else if (size == 1) {
        rows = 100;
        cols = 100;
    } else {
        rows = 1000;
        cols = 1005;
    }
    #endif

    printf("rows = %i, cols = %i, sparsity = %f\n", rows, cols, sparsity);

    float **A = generate_sparse_matrix(rows, cols, sparsity);
    float **B = generate_sparse_matrix(cols, rows, sparsity);

    float **C = matmul_sparse(A, B, rows, cols, cols, rows);

    #ifndef PROFILING
    printf("RUNNING SPARSE MATRIX UNITY TEST\n");
    for (int j=0; j < rows; j++) {
        for (int k=0; k < rows; k++) {
            float sum = 0;
            for (int l=0; l < cols; l++) {
                sum += A[j][l] * B[l][k];
            }
            UNITY_TEST_ASSERT_FLOAT_WITHIN(0.0001, sum, C[j][k], __LINE__, "Wrong sum");
            TEST_ASSERT_EQUAL_INT(sizeof(C[j][k]), sizeof(float));
        }
    }
    #endif

    // Cleanup
    cleanup_matrix(A, rows);
    cleanup_matrix(B, cols);
    cleanup_matrix(C, rows);
}