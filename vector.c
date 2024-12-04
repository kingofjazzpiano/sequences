#include "vector.h"


static size_t get_new_capacity(size_t capacity){
	return capacity + (capacity >> 2) + 4;
}

int read_int(int *value, const int lower_limit, const int upper_limit){
	/**
	 * Reads an integer value from stdin and validates it against specified limits.
	 *
	 * @param value : Pointer to the location where the read integer value will be stored.
	 * @param lower_limit : The inclusive lower bound for the valid input range.
	 * @param upper_limit : The inclusive upper bound for the valid input range.
	 *
	 * @return
	 *         SUCCESS (0) if the input is successfully read and within the specified range.
	 *         EOF if end-of-file (Ctrl+D) is encountered.
	 *         An error code defined in vector.h if an error occurs.
	 *
	 * @note
	 *       The `lower_limit` must be less than or equal to `upper_limit`.
	 *       If this condition is violated, the function will return WRONG_LIMITS_ERROR.
	 */
	if (NULL == value){
		return NULL_POINTER_ERROR;
	}
	if (lower_limit > upper_limit){
		return WRONG_LIMITS_ERROR;
	}
	while (true){
		int scanf_returns = scanf("%d", value);
		if (scanf_returns == EOF){
		    printf("\nInterrupted by user\n");
		    return EOF;
		}
		while (getchar() != '\n'); // Clear buffer
		if (scanf_returns == 0){
		     printf("Only numbers are allowed!\n");
		}
		if (scanf_returns == 1
		                and (*value < lower_limit or *value > upper_limit)){
		    printf("Value is out of range!\n");
		    printf("Enter value in range [%d - %d]\n", lower_limit, upper_limit);
		}
		else if (scanf_returns == 1){
		    return SUCCESS;  // Valid input here
		}
		printf("Try again: ");
	}
}


int vector_print(Vector *vector){
	if (NULL == vector or NULL == vector -> data){
		return NULL_POINTER_ERROR;
	}
	if (0 == vector -> size){
		printf("Empty Sequence\n");
		return SUCCESS;
	}
	for (size_t i = 0; i < vector -> size; i++){
		printf("%d ", vector -> data[i]);
	}
	printf("\n");
	return SUCCESS;
}


int vector_init(Vector *vector, size_t size){
	/**
	 * Initializes a Vector structure with a specified data size and reads values into it.
	 *
	 * This function allocates memory for a `Vector` structure,
	 * including memory for its `data` field, using amortized allocation.
	 * It uses `read_int()` to read values from stdin and populate the vector.
	 *
	 * @param vector : Pointer to a `Vector` structure defined in vector.h.
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
		int error = read_int(vector -> data + i, INT_MIN, INT_MAX);
		int free_error;
		if (SUCCESS != error){
			free_error = vector_free(vector);
			assert(SUCCESS == free_error);
			return error;
		}
	}
	return SUCCESS;
}


int vector_insert(Vector *vector, size_t position, int item){
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
		new_data_place = (int *)realloc(vector -> data, sizeof(int) 
										* new_capacity);
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


int vector_remove(Vector *vector, size_t index){
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


int vector_free(Vector *vector){
	if (vector == NULL){
		return NULL_POINTER_ERROR;
	}
	vector -> size = 0;
	vector -> capacity = 0;
	free(vector -> data);
	vector -> data = NULL;
	return SUCCESS;
}

