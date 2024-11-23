#include <stdio.h>
#include <assert.h>

#include "vector.h"


void test_read_int();
void test_struct();
void test_init();
void test_insert();
void test_remove();
bool is_equal_vector(vector_t vector1, vector_t vector2);


int main(){
	// test_read_int();
	// test_struct();
	// test_init();
	// test_insert();
	// test_remove();

	vector_t vector;
	int error = vector_init(&vector, 0);
	printf("error=%d\n", error);
	error = vector_print(&vector);
	printf("error=%d\n", error);

	printf("vector.data_size=%zu\n", vector.data_size);	
	printf("vector.buffer_size=%zu\n", vector.buffer_size);

	size_t size = 100;
	for (size_t i = 0; i < size; i++){
		error = vector_insert(&vector, 0, i);
		assert(error == SUCCESS);
		error = vector_print(&vector);
		assert(error == SUCCESS);		

		printf("vector.data_size=%zu\n", vector.data_size);	
		printf("vector.buffer_size=%zu\n", vector.buffer_size);
	}
	
	printf("\nAll tests done!\n");
}


void test_insert2(){
	
}


void test_remove(){
	printf("Running %s...\n", __FUNCTION__);

	vector_t vector;
	size_t index = 0;
	size_t size = 10;
	printf("Enter %zu numbers:\n", size);

	int error = vector_init(&vector, size);
	assert(SUCCESS == error);
	assert(size == vector.data_size);
	assert(16 == vector.buffer_size);

	error = vector_print(&vector);
	assert(SUCCESS == error);
		
	printf("vector.buffer_size=%zu\n", vector.buffer_size);

	for(size_t i = 0; i < 4; i++){
		error = vector_remove(&vector, index);
		assert(SUCCESS == error);
		size--;
		assert(size == vector.data_size);
		assert(16 == vector.buffer_size);
	
		error = vector_print(&vector);
		assert(SUCCESS == error);
		
		printf("vector.buffer_size=%zu\n", vector.buffer_size);
	}
	error = vector_remove(&vector, index);
	assert(SUCCESS == error);
	size--;
	assert(size == vector.data_size); // size == 5
	assert(10 == vector.buffer_size);
	
	error = vector_print(&vector);
	assert(SUCCESS == error);

	printf("vector.buffer_size=%zu\n", vector.buffer_size);

	error = vector_remove(&vector, 5);
	assert(INDEX_IS_OUT_OF_RANGE_ERROR == error);
	
	error = vector_free(&vector); 
	assert(SUCCESS == error);
	
	printf("%s done\n", __FUNCTION__);
}


void test_insert(){
	printf("Running %s...\n", __FUNCTION__);

	int item = 777;
	
	vector_t vector;
	size_t size = 0;
	int error = vector_init(&vector, size);
	assert(SUCCESS == error);
	size_t position = 1;
	error = vector_insert(&vector, position, item);
	assert(INDEX_IS_OUT_OF_RANGE_ERROR == error);
	vector_free(&vector);
// 
	// size = 1;
	// printf("Enter 1 number:\n");
	// error = vector_init(&vector, size);
	// assert(SUCCESS == error);
	// assert(vector.data_size == 1);
	// assert(vector.buffer_size == 5);
	// vector_print(&vector);
	// position = 1;
	// printf("Insert %d to %zu index\n", item, position);
	// error = vector_insert(&vector, position, item);
	// assert(SUCCESS == error);
	// assert(vector.data_size == 2);
	// assert(vector.buffer_size == 5);
	// vector_print(&vector);
	// vector_free(&vector);
// 
	// size = 1;
	// printf("Enter 1 number:\n");
	// error = vector_init(&vector, size);
	// assert(SUCCESS == error);
	// assert(vector.data_size == 1);
	// assert(vector.buffer_size == 5);
	// vector_print(&vector);
	// position = 0;
	// printf("Insert %d to %zu index\n", item, position);
	// error = vector_insert(&vector, position, item);
	// assert(SUCCESS == error);
	// assert(vector.data_size == 2);
	// assert(vector.buffer_size == 5);
	// vector_print(&vector);
	// vector_free(&vector);

	size = 5;
	printf("Enter %zu number:\n", size);
	error = vector_init(&vector, size);
	assert(SUCCESS == error);
	assert(vector.data_size == 5);
	assert(vector.buffer_size == 10);
	vector_print(&vector);
	
	position = 0;
	printf("Insert %d to %zu index\n", item, position);
	error = vector_insert(&vector, position, item);
	assert(SUCCESS == error);
	assert(vector.data_size == 6);
	assert(vector.buffer_size == 10);
	vector_print(&vector);

	position = 6;
	printf("Insert %d to %zu index\n", item, position);
	error = vector_insert(&vector, position, item);
	assert(SUCCESS == error);
	assert(vector.data_size == 7);
	assert(vector.buffer_size == 10);
	vector_print(&vector);

	position = 6;
	printf("Insert %d to %zu index\n", item, position);
	error = vector_insert(&vector, position, item);
	assert(SUCCESS == error);
	assert(vector.data_size == 8);
	assert(vector.buffer_size == 10);
	vector_print(&vector);


	position = 0;
	printf("Insert %d to %zu index\n", item, position);
	error = vector_insert(&vector, position, item);
	assert(SUCCESS == error);
	assert(vector.data_size == 9);
	assert(vector.buffer_size == 10);
	vector_print(&vector);

	position = 4;
	printf("Insert %d to %zu index\n", item, position);
	error = vector_insert(&vector, position, item);
	assert(SUCCESS == error);
	assert(vector.data_size == 10);
	assert(vector.buffer_size == 10);
	vector_print(&vector);


	position = 10;
	printf("Insert %d to %zu index\n", item, position);
	error = vector_insert(&vector, position, item);
	assert(SUCCESS == error);
	assert(vector.data_size == 11);
	assert(vector.buffer_size == 16);
	vector_print(&vector);	
	
	vector_free(&vector);	
	printf("%s done\n", __FUNCTION__);		
}


void test_init(){
	printf("Running %s...\n", __FUNCTION__);
	vector_t vector;
	size_t size = 5;
	int error = vector_init(NULL, size);
	assert(NULL_POINTER_ERROR == error);

	size = 1000ull * 1000ull * 1000ull * 1000ull;
	error = vector_init(&vector, size);
	vector_free(&vector);
	assert(NOT_ENOUGH_MEMORY_ERROR == error);

	size = 0;
	error = vector_init(&vector, size);
	assert(SUCCESS == error);
	assert(size == vector.data_size);
	assert(4 == vector.buffer_size);
	vector_free(&vector);

	size = 1;
	printf("Enter 1 number:\n");
	error = vector_init(&vector, size);
	assert(SUCCESS == error);
	assert(size == vector.data_size);
	assert(5 == vector.buffer_size);
	vector_print(&vector);
	vector_free(&vector);

	size = 4;
	printf("Enter 4 numbers:\n");
	error = vector_init(&vector, size);
	assert(SUCCESS == error);
	assert(size == vector.data_size);
	assert(9 == vector.buffer_size);
	vector_print(&vector);
	vector_free(&vector);
		
	printf("%s done\n", __FUNCTION__);		
}

bool is_equal_vector(vector_t vector1, vector_t vector2){
	if (vector1.data_size != vector2.data_size){
		return false;
	}
	for (size_t i = 0; i < vector1.data_size; i++){
		if (vector1.data[i] != vector2.data[i]){
			return false;
		}
	}
	return true;
}

void test_struct(){
	printf("Running %s...\n", __FUNCTION__);
	vector_t *vector = (vector_t *)malloc(sizeof(vector_t));
	if (NULL == vector){
		perror("Not enough memory");
		exit(EXIT_FAILURE);
	}
	const size_t BUFFER_SIZE = (size_t)100;
	const size_t DATA_SIZE = (size_t)5;
	vector -> data = (int *)malloc(sizeof(int) * BUFFER_SIZE);
	if (NULL == vector -> data){
		perror("Not enough memory");
		exit(EXIT_FAILURE);
	}
	vector -> buffer_size = BUFFER_SIZE;
	vector -> data_size = DATA_SIZE;

	for (size_t i = 0; i < DATA_SIZE; i++){
		vector -> data[i] = (int)(i * i);
	}

	for (size_t i = 0; i < DATA_SIZE; i++){
		assert(vector -> data[i] == (int)(i * i));
	}

	assert(BUFFER_SIZE == vector -> buffer_size);
	assert(DATA_SIZE == vector -> data_size);
	printf("%s done\n", __FUNCTION__);		
}

// void test_read_int(){
	// printf("Running %s...\n", __FUNCTION__);
	// int n = 0;
	// 
	// int error = read_int(NULL, -1, -10);
	// assert(NULL_POINTER_ERROR == error);
	// 
	// error = read_int(&n, -1, -10);
	// assert(WRONG_LIMITS_ERROR == error);
	// 
	// printf("read_int(&n, 5, 5)\n");
	// error = read_int(&n, 5, 5);
	// assert(error == SUCCESS);
	// printf("n=%d\n", n);
// 
	// printf("read_int(&n, -15, 15)\n");
	// error = read_int(&n, -15, 15);
	// assert(error == SUCCESS);
	// printf("n=%d\n", n);
// 
	// printf("type letters like ajgkdfjhagl adgjag afdgalk\n");
	// printf("read_int(&n, -15, 15)\n");
	// error = read_int(&n, -15, 15);
	// assert(error == SUCCESS);
	// printf("n=%d\n", n);
	// printf("%s done\n", __FUNCTION__);
// }
