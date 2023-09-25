#include <tests/tests.h>
#include <stdio.h>
#include <stdlib.h>

void setUp(void) {
    /* Code here will run before each test */
}

void tearDown(void) {
    /* Code here will run after each test */
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        printf("Usage: ./main <fn_num> <test_num>\n");
        printf("<fn_num> are: 1 (conv), 2 (relu), 3 (linear), 4 (matmul), 5 (softmax)\n");
        printf("<test_num> are: 1, 2, 3\n");
        return 1;
    }

    int fn_num = atoi(argv[1]);
    int test_num = atoi(argv[2]);

    if (fn_num == 1) {
        if (test_num == 1) {
            test_conv_slides();
        } else if (test_num == 2) {
            test_conv_slides2();
        } else if (test_num == 3) {
            test_conv_slides3();
        } else {
            printf("Invalid test number\n");
            return 1;
        }
    } else if (fn_num == 2) {
        if (test_num == 1) {
            test_relu();
        } else if (test_num == 2) {
            test_relu_large();
        } else if (test_num == 3) {
            test_relu_large_neg();
        } else {
            printf("Invalid test number\n");
            return 1;
        }
    } else
    if (fn_num == 3) {
        if (test_num == 1) {
            test_linear();
        } else if (test_num == 2) {
            test_linear_very_large();
        } else if (test_num == 3) {
            test_linear_very_large_very_long();
        } else {
            printf("Invalid test number\n");
            return 1;
        }
    } else if (fn_num == 4) {
        if (test_num == 1) {
            test_matmul_square_matrices();
        } else if (test_num == 2) {
        } else if (test_num == 3) {
        } else {
            printf("Invalid test number\n");
            return 1;
        }
    } else if (fn_num == 5) {
        if (test_num == 1) {
            test_softmax();
        } else if (test_num == 2) {
            test_softmax_large();
        } else if (test_num == 3) {
            test_softmax_long();
        } else {
            printf("Invalid test number\n");
            return 1;
        }
    } else {
        printf("Invalid function number\n");
        return 1;
    }

    return 0;
}