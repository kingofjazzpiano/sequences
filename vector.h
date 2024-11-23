#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <iso646.h>
#include <assert.h>

#define SUCCESS 0
#define NULL_POINTER_ERROR 1
#define NOT_ENOUGH_MEMORY_ERROR 2
#define INDEX_IS_OUT_OF_RANGE_ERROR 3

typedef struct {
	int *data;
	size_t data_size;
	size_t buffer_size;
} vector_t;

int read_int(int *value);
int vector_init(vector_t *vector, size_t data_size);
int vector_print(vector_t *vector);
int vector_insert(vector_t *vector, size_t position, int item);
int vector_remove(vector_t *vector, size_t index);
int vector_free(vector_t *vector);

#endif
