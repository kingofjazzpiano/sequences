#include "vector.h"


static size_t get_new_capacity(size_t capacity){
	return capacity + (capacity >> 2) + 4;
}


int read_int(int *value){
	if (NULL == value){
		return NULL_POINTER_ERROR;
	}
	while (true){
        int scanf_returns = scanf("%d", value);
        if (scanf_returns == EOF){
            fprintf(stderr, "\nInterrupted by user\n");
            return EOF;
        }
        while (getchar() != '\n'); // Clear buffer
        if (scanf_returns == 0){
             fprintf(stderr, "Only numbers are allowed!\n");
        }
        else if (scanf_returns == 1){
            return SUCCESS;  // Valid input here
        }
	}
}


int vector_print(vector_t *vector){
	if (NULL == vector or NULL == vector -> data){
		return NULL_POINTER_ERROR;
	}
	for (size_t i = 0; i < vector -> size; i++){
		printf("%d ", vector -> data[i]);
	}
	printf("\n");
	return SUCCESS;
}


int vector_init(vector_t *vector, size_t size){
	/**
	 * Initializes a vector_t structure with a specified data size and reads values into it.
	 *
	 * This function allocates memory for a `vector_t` structure,
	 * including memory for its `data` field, using amortized allocation.
	 * It uses `read_int()` to read values from stdin and populate the vector.
	 *
	 * @param vector : Pointer to a `vector_t` structure defined in vector.h.
	 *                 The function allocates memory for the structure and initializes it.
	 * @param size : The number of elements to be read from stdin and stored in the vector.
	 *
	 * @return 
	 *         SUCCESS (0) if the vector is successfully initialized,
	 *         and all values are read and stored.
	 *         An error code defined in vector.h if an error occurs.
	 *
	 * @note 
	 *       - The `size` specifies the initial level of data fullness.
	 *       - Memory for `data` is allocated with amortization: `capacity` is ~5/4 of `size`.
	 */
	if (NULL == vector){
		return NULL_POINTER_ERROR;
	}
	
	// capacity is approximately 5/4 of size
	vector -> capacity = get_new_capacity(size);
	
	vector -> data = (int *)malloc(sizeof(int) * vector -> capacity);
	if (NULL == vector -> data){
		return NOT_ENOUGH_MEMORY_ERROR;
	}
	vector -> size = size;

	for (size_t i = 0; i < size; i++){
		int error = read_int(vector -> data + i);
		int free_error;
		if (SUCCESS != error){
			free_error = vector_free(vector);
			assert(SUCCESS == free_error);
			return error;
		}
	}
	printf("vector -> size=%zu\n", vector -> size);	
	return SUCCESS;
}


int vector_insert(vector_t *vector, size_t position, int item){
	if (NULL == vector or NULL == vector -> data){
		return NULL_POINTER_ERROR;
	}
	if (position > vector -> size){
		return INDEX_IS_OUT_OF_RANGE_ERROR;
	}
	assert(vector -> capacity >= vector -> size);
	int *new_data_place;
	size_t new_capacity;
	if (vector -> capacity == vector -> size){
		new_capacity = get_new_capacity(vector -> capacity);
		new_data_place = (int *)realloc(vector -> data, sizeof(int) * new_capacity);
		if (NULL == new_data_place){
			return NOT_ENOUGH_MEMORY_ERROR;
		}
		vector -> data = new_data_place;
		vector -> capacity = new_capacity;
	}
	vector -> size += 1;
	assert(vector -> capacity >= vector -> size);
	
	for (size_t i = vector -> size - 1; i > position; i--){
		vector -> data[i] = vector -> data[i - 1];
	}
	vector -> data[position] = item;
	
	return SUCCESS;
}


int vector_remove(vector_t *vector, size_t index){
	if (NULL == vector or NULL == vector -> data){
		return NULL_POINTER_ERROR;
	}
	assert(vector -> capacity >= vector -> size);
	if (index >= vector -> size){
		return INDEX_IS_OUT_OF_RANGE_ERROR;
	}
	for (size_t i = index; i < vector -> size - 1; i++){
		vector -> data[i] = vector -> data[i + 1];
	}
	vector -> size -= 1;
	int *new_data_place;
	size_t new_capacity = get_new_capacity(vector -> size);
	if (get_new_capacity(new_capacity) <= vector -> capacity){
		new_data_place = (int *)realloc(vector -> data, sizeof(int) * new_capacity);
		if (NULL == new_data_place){
			return NOT_ENOUGH_MEMORY_ERROR;
		}
		vector -> data = new_data_place;
		vector -> capacity = new_capacity;	
	}
	assert(vector -> capacity >= vector -> size);
	return SUCCESS;
}


int vector_free(vector_t *vector){
	if (vector == NULL){
		return NULL_POINTER_ERROR;
	}
	vector -> size = 0;
	vector -> capacity = 0;
	free(vector -> data);
	return SUCCESS;
}

