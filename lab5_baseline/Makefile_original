CC = gcc
CFLAGS = -I. -lm

HDF5_FLAGS = -I/usr/include/hdf5/serial -L/usr/lib/x86_64-linux-gnu/hdf5/serial -lhdf5
COMMON_HDRS = lab5.h ./utils/data_utils.h ./kernel/conv.h ./kernel/functional.h ./kernel/matrix_ops.h ./kernel/linear.h ./kernel/nn.h
COMMON_SRC = ./utils/data_utils.c ./kernel/conv.c ./kernel/functional.c ./kernel/matrix_ops.c ./kernel/linear.c ./kernel/nn.c

BINS = lab5

.PHONY: all
all: $(BINS)

.PHONY: lab5
lab5: lab5.c $(COMMON_HDRS)
	$(CC) -o $@ lab5.c $(COMMON_SRC) $(CFLAGS) $(HDF5_FLAGS)

.PHONY: clean
clean:
	rm -f $(BINS)