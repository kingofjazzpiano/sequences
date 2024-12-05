
#include "hash_map.h"
#include "hash_map.c"
#include <stdio.h>

void test_hash_map_init();
void test_hash_map_resize();
void test_hash_map_set();
void test_hash_map_has();
void test_hash_map_get_value_pointer();


int main(){
	test_hash_map_init();
	test_hash_map_resize();
	test_hash_map_set();
	test_hash_map_has();
	test_hash_map_get_value_pointer();

	printf("\n%s DONE!!\n", __FILE__);
}


void test_hash_map_init(){
	printf("\nRun %s\n", __FUNCTION__);
	HashMap map;
	int error = hash_map_init(NULL);
	assert(NULL_POINTER_ERROR == error);
	error = hash_map_init(&map);
	assert(SUCCESS == error);
	assert(map.size == 0);
	assert(map.capacity_bit_size == MIN_CAPACITY_BIT_SIZE);
	for (size_t i = 0; i < (size_t)(1 << MIN_CAPACITY_BIT_SIZE); i++){
		assert(false == map.is_busy[i]);
	}
	
	error = hash_map_free(&map);
	assert(SUCCESS == error);
	
	printf("\n%s done!\n", __FUNCTION__);
}


void test_hash_map_resize(){
	printf("\nRun %s\n", __FUNCTION__);

	HashMap map;
	int error = hash_map_resize(NULL, MIN_CAPACITY_BIT_SIZE);
	assert(NULL_POINTER_ERROR == error);

	// hash_map_resize(&map, 0); // assertion fail

	error = hash_map_init(&map);
	assert(SUCCESS == error);
	assert(0 == map.size);

	int keys[3] = {101, 0, 17};
	for (int i = 0; i < 3; i++){
		uint32_t hash_code = hash(keys[i], MIN_CAPACITY_BIT_SIZE);
		map.is_busy[hash_code] = true;
		map.nodes[hash_code].key = keys[i];
		map.nodes[hash_code].value = keys[i] * keys[i];
	}
	map.size = 3;


	printf("Before: ");
	error = hash_map_print(&map);
	assert(SUCCESS == error);

	int new_capacity_bit_size = map.capacity_bit_size + 1;
	error = hash_map_resize(&map, new_capacity_bit_size);
	assert(SUCCESS == error);
	assert(3 == map.size);
	
	printf("After: ");
	error = hash_map_print(&map);
	assert(SUCCESS == error);

	assert(map.capacity_bit_size == new_capacity_bit_size);
	assert(map.capacity == (unsigned)(1 << new_capacity_bit_size));

	new_capacity_bit_size = map.capacity_bit_size - 1;
	error = hash_map_resize(&map, new_capacity_bit_size);
	assert(SUCCESS == error);
	assert(3 == map.size);

	printf("After: ");
	error = hash_map_print(&map);
	assert(SUCCESS == error);

	assert(map.capacity_bit_size == new_capacity_bit_size);
	assert(map.capacity == (unsigned)(1 << new_capacity_bit_size));	

	error = hash_map_free(&map);
	assert(SUCCESS == error);
	
	printf("\n%s done!\n", __FUNCTION__);	
}


void test_hash_map_set(){
	printf("\nRun %s\n", __FUNCTION__);


	// const int KEYS_SIZE = 20;
	// int keys[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
				  // 31, 37, 41, 43, 47, 53, 59, 61, 67};
	const int KEYS_SIZE = 25;
	int keys[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
				  31, 37, 41, 43, 47, 53, 59, 61, 67,
				  71, 73, 79, 83, 89, 97};
				  
	// printf("keys: ");
	// for (int i = 0; i < KEYS_SIZE; i++){
		// printf("%d ", keys[i]);
	// }
	// printf("\n");

	HashMap map;
	int error = hash_map_set(NULL, keys[2], keys[2] * keys[2]);
	assert(NULL_POINTER_ERROR == error);

	map.nodes = NULL;
	map.is_busy = NULL;
	error = hash_map_set(&map, keys[2], keys[2] * keys[2]);
	assert(NULL_POINTER_ERROR == error);
	
	error = hash_map_init(&map);
	assert(SUCCESS == error);

	for (int i = 0; i < KEYS_SIZE; i++){
		error = hash_map_set(&map, keys[i], keys[i] * keys[i]);
		assert(SUCCESS == error);
		
		// printf("map.size=%u\tmap.capacity=%u\tmap.capacity_bit_size=%d\n",
			   // map.size, map.capacity, map.capacity_bit_size);
		// error = hash_map_print(&map);
		// assert(SUCCESS == error);
		// printf("\n");
	}
	assert(KEYS_SIZE == (int)map.size);

	// printf("Newly hash map: ");
	// error = hash_map_print(&map);
	// assert(SUCCESS == error);
	
	error = hash_map_free(&map);
	assert(SUCCESS == error);
	
	printf("\n%s done!\n", __FUNCTION__);
}


void test_hash_map_has(){
	printf("\nRun %s\n", __FUNCTION__);

	int key = 777;
	bool has_key = true;
	HashMap map;
	int error = hash_map_has(NULL, key, &has_key);
	assert(NULL_POINTER_ERROR == error);

	error = hash_map_has(&map, key, NULL);
	assert(NULL_POINTER_ERROR == error);

	map.nodes = NULL;
	map.is_busy = NULL;
	error = hash_map_has(&map, key, &has_key);
	assert(NULL_POINTER_ERROR == error);

	const int KEYS_SIZE = 25;
	int keys[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
				  31, 37, 41, 43, 47, 53, 59, 61, 67,
				  71, 73, 79, 83, 89, 97};
				  
	printf("keys: ");
	for (int i = 0; i < KEYS_SIZE; i++){
		printf("%d ", keys[i]);
	}
	printf("\n");

	error = hash_map_init(&map);
	assert(SUCCESS == error);
	assert(map.size == 0);
	assert(MIN_CAPACITY_BIT_SIZE == map.capacity_bit_size);
	assert((1 << MIN_CAPACITY_BIT_SIZE) == map.capacity);

	for (int i = 0; i < KEYS_SIZE; i++){
		error = hash_map_set(&map, keys[i], keys[i] * keys[i]);
		assert(SUCCESS == error);
	}
	assert(KEYS_SIZE == (int)map.size);

	error = hash_map_has(&map, -1, &has_key);
	assert(SUCCESS == error);
	assert(false == has_key);

	error = hash_map_has(&map, -3, &has_key);
	assert(SUCCESS == error);
	assert(false == has_key);
	
	error = hash_map_has(&map, -80, &has_key);
	assert(SUCCESS == error);
	assert(false == has_key);

	error = hash_map_has(&map, 0, &has_key);
	assert(SUCCESS == error);
	assert(false == has_key);

	error = hash_map_has(&map, 1, &has_key);
	assert(SUCCESS == error);
	assert(false == has_key);

	error = hash_map_has(&map, keys[0], &has_key);
	assert(SUCCESS == error);
	assert(true == has_key);

	error = hash_map_has(&map, keys[1], &has_key);
	assert(SUCCESS == error);
	assert(true == has_key);

	error = hash_map_has(&map, keys[KEYS_SIZE - 1], &has_key);
	assert(SUCCESS == error);
	assert(true == has_key);

	error = hash_map_free(&map);
	assert(SUCCESS == error);

	printf("\n%s done!\n", __FUNCTION__);
}

void test_hash_map_get_value_pointer(){
	printf("\nRun %s\n", __FUNCTION__);

	HashMap map;
	int error = hash_map_init(&map);
	assert(SUCCESS == error);

	int key = 13;
	int *value = NULL;
	error = hash_map_get_value_pointer(NULL, key, &value);
	assert(NULL_POINTER_ERROR == error);
	error = hash_map_get_value_pointer(&map, key, NULL);
	assert(NULL_POINTER_ERROR == error);
	
	error = hash_map_get_value_pointer(&map, key, &value);
	assert(KEY_DOES_NOT_EXIST_ERROR == error);
	assert(NULL == value);

	printf("Before set: ");
	error = hash_map_print(&map);
	assert(SUCCESS == error);
	
	error = hash_map_set(&map, key, key * key);
	assert(SUCCESS == error);

	printf("After (13: 169) setted: ");
	error = hash_map_print(&map);
	assert(SUCCESS == error);
	
	error = hash_map_get_value_pointer(&map, key, &value);
	assert(SUCCESS == error);

	*value += 1;
	assert(170 == *value);

	printf("After *value += 1 setted: ");
	error = hash_map_print(&map);
	assert(SUCCESS == error);
	
	error = hash_map_free(&map);
	assert(SUCCESS == error); 

	printf("\n%s done!\n", __FUNCTION__);
}
