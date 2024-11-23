#include "vector.h"


static size_t get_new_buffer_size(size_t buffer_size){
	return buffer_size + (buffer_size >> 2) + 4;
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
	for (size_t i = 0; i < vector -> data_size; i++){
		printf("%d ", vector -> data[i]);
	}
	printf("\n");
	return SUCCESS;
}


int vector_init(vector_t *vector, size_t data_size){
	/**
	 * Initializes a vector_t structure with a specified data size and reads values into it.
	 *
	 * This function allocates memory for a `vector_t` structure,
	 * including memory for its `data` field, using amortized allocation.
	 * It uses `read_int()` to read values from stdin and populate the vector.
	 *
	 * @param vector : Pointer to a `vector_t` structure defined in vector.h.
	 *                 The function allocates memory for the structure and initializes it.
	 * @param data_size : The number of elements to be read from stdin and stored in the vector.
	 *
	 * @return 
	 *         SUCCESS (0) if the vector is successfully initialized,
	 *         and all values are read and stored.
	 *         An error code defined in vector.h if an error occurs.
	 *
	 * @note 
	 *       - The `data_size` specifies the initial level of data fullness.
	 *       - Memory for `data` is allocated with amortization: `buffer_size` is ~5/4 of `data_size`.
	 */
	if (NULL == vector){
		return NULL_POINTER_ERROR;
	}
	
	// buffer_size is approximately 5/4 of data_size
	vector -> buffer_size = get_new_buffer_size(data_size);
	
	vector -> data = (int *)malloc(sizeof(int) * vector -> buffer_size);
	if (NULL == vector -> data){
		return NOT_ENOUGH_MEMORY_ERROR;
	}
	vector -> data_size = data_size;

	for (size_t i = 0; i < data_size; i++){
		int error = read_int(vector -> data + i);
		if (SUCCESS != error){
			return error;
		}
	}
	
	return SUCCESS;
}


int vector_insert(vector_t *vector, size_t position, int item){
	if (NULL == vector or NULL == vector -> data){
		return NULL_POINTER_ERROR;
	}
	if (position > vector -> data_size){
		return INDEX_IS_OUT_OF_RANGE_ERROR;
	}
	assert(vector -> buffer_size >= vector -> data_size);
	int *new_data_place;
	size_t new_buffer_size;
	if (vector -> buffer_size == vector -> data_size){
		new_buffer_size = get_new_buffer_size(vector -> buffer_size);
		printf("new_buffer_size=%zu\n", new_buffer_size);
		new_data_place = (int *)realloc(vector -> data, new_buffer_size);
		if (NULL == new_data_place){
			return NOT_ENOUGH_MEMORY_ERROR;
		}
		vector -> data = new_data_place;
		vector -> buffer_size = new_buffer_size;
	}
	vector -> data_size += 1;
	assert(vector -> buffer_size >= vector -> data_size);
	
	for (size_t i = vector -> data_size - 1; i > position; i--){
		vector -> data[i] = vector -> data[i - 1];
	}
	vector -> data[position] = item;
	
	return SUCCESS;
}


int vector_remove(vector_t *vector, size_t index){
	if (NULL == vector or NULL == vector -> data){
		return NULL_POINTER_ERROR;
	}
	if (index >= vector -> data_size){
		return INDEX_IS_OUT_OF_RANGE_ERROR;
	}
	for (size_t i = index; i < vector -> data_size - 1; i++){
		vector -> data[i] = vector -> data[i + 1];
	}
	vector -> data_size -= 1;
	int *new_data_place;
	size_t new_buffer_size = get_new_buffer_size(vector -> data_size);
	if (get_new_buffer_size(new_buffer_size) <= vector -> buffer_size){
		new_data_place = (int *)realloc(vector -> data, new_buffer_size);
		if (NULL == new_data_place){
			return NOT_ENOUGH_MEMORY_ERROR;
		}
		vector -> buffer_size = new_buffer_size;	
	}
	return SUCCESS;
}


int vector_free(vector_t *vector){
	if (vector == NULL){
		return NULL_POINTER_ERROR;
	}
	vector -> data_size = 0;
	vector -> buffer_size = 0;
	free(vector -> data);
	return SUCCESS;
}

