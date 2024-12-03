#ifndef VECTOR_H
#define VECTOR_H


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <iso646.h>
#include <assert.h>
#include <limits.h>

#include "error.h"


#define VECTOR_MAX_SIZE 1000 * 1000 * 1000 // Billion


typedef struct {
	int *data;
	size_t size;
	size_t capacity;
} Vector;


int read_int(int *value, const int lower_limit, const int upper_limit);
int vector_init(Vector *vector, size_t size);
int vector_print(Vector *vector);
int vector_insert(Vector *vector, size_t position, int item);
int vector_remove(Vector *vector, size_t index);
int vector_free(Vector *vector);


#endif  // VECTOR_H
