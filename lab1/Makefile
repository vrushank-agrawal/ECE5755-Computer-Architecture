CC = gcc
CFLAGS = -I. -lm -lpthread

DEBUG =
BLOCK_SIZE ?= 1
NUM_THREADS ?= 4

HDF5_FLAGS = -I/usr/include/hdf5/serial -L/usr/lib/x86_64-linux-gnu/hdf5/serial -lhdf5
COMMON_HDRS = ./utils/data_utils.h ./kernel/conv.h ./kernel/functional.h ./kernel/matrix_ops.h ./kernel/linear.h
COMMON_SRC = ./utils/data_utils.c ./kernel/conv.c ./kernel/functional.c ./kernel/matrix_ops.c ./kernel/linear.c
PROFILE_TEST_FILES = $(wildcard ./tests/test_*.c)

# Unity test framework
UNITY_FILES = ./tests/unity/unity.c
TEST_FILES = $(wildcard ./tests/*.c)
TEST_EXECUTABLES = $(patsubst %.c,%,$(TEST_FILES))

.PHONY: test
test: all_tests

.PHONY: main
main: main.c $(PROFILE_TEST_FILES) $(COMMON_SRC) $(COMMON_HDRS)
	$(CC) -o main main.c $(PROFILE_TEST_FILES) $(UNITY_FILES) $(COMMON_SRC) $(COMMON_HDRS) $(HDF5_FLAGS) $(CFLAGS) -DPROFILING

.PHONY: all_tests
all_tests:
	$(CC) -o tests/$@ $(TEST_FILES) $(UNITY_FILES) $(COMMON_SRC) $(CFLAGS) $(HDF5_FLAGS) $(DEBUG) -DBLOCK_SIZE=$(BLOCK_SIZE) -DNUM_THREADS=$(NUM_THREADS)
	./tests/$@

.PHONY: clean
clean:
	rm -f $(TEST_EXECUTABLES) main