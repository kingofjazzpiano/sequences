#ifndef VECTOR_H
#define VECTOR_H


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <iso646.h>
#include <assert.h>

#include "error.h"


typedef struct {
	int *data;
	size_t size;
	size_t capacity;
} vector_t;


int read_int(int *value);
int vector_init(vector_t *vector, size_t size);
int vector_print(vector_t *vector);
int vector_insert(vector_t *vector, size_t position, int item);
int vector_remove(vector_t *vector, size_t index);
int vector_free(vector_t *vector);


#endif  // VECTOR_H
