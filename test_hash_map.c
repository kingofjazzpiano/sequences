#include <stdio.h>

#include "hash_map.h"
#include "hash_map.c"

void test_hash_map_init();
void test_hash_map_resize();
void test_hash_map_get();
void test_hash_map_set();
void test_hash_map_has();


int main(){
	test_hash_map_init();
	test_hash_map_resize();
	// test_hash_map_set();
	// test_hash_map_has();

	printf("\n%s done\n", __FILE__);
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

	int keys[3] = {101, 0, 17};
	for (int i = 0; i < 3; i++){
		uint32_t hash_code = hash(keys[i], MIN_CAPACITY_BIT_SIZE);
		map.is_busy[hash_code] = true;
		map.nodes[hash_code].key = keys[i];
		map.nodes[hash_code].value = keys[i] * keys[i];
	}

	printf("Before: ");
	error = hash_map_print(&map);
	assert(SUCCESS == error);

	int new_capacity_bit_size = map.capacity_bit_size + 1;
	error = hash_map_resize(&map, new_capacity_bit_size);
	assert(SUCCESS == error);
	
	printf("After: ");
	error = hash_map_print(&map);
	assert(SUCCESS == error);

	assert(map.capacity_bit_size == new_capacity_bit_size);
	assert(map.capacity == (unsigned)(1 << new_capacity_bit_size));

	new_capacity_bit_size = map.capacity_bit_size - 1;
	error = hash_map_resize(&map, new_capacity_bit_size);
	assert(SUCCESS == error);

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

	int keys[3] = {101, 0, 17};
	HashMap map;
	int error = hash_map_set(NULL, keys[2], keys[2] * keys[2]);
	assert(NULL_POINTER_ERROR == error);

	map.nodes = NULL;
	map.is_busy = NULL;
	error = hash_map_set(&map, keys[2], keys[2] * keys[2]);
	assert(NULL_POINTER_ERROR == error);
	
	error = hash_map_init(&map);
	assert(SUCCESS == error);

	for (size_t i = 0; i < 3; i++){
		error = hash_map_set(&map, keys[i], keys[i] * keys[i]);
		assert(SUCCESS == error);
	}
	assert(3 == map.size);

	error = hash_map_print(&map);
	assert(SUCCESS == error);
	
	error = hash_map_free(&map);
	assert(SUCCESS == error);
	
	printf("\n%s done!\n", __FUNCTION__);
}


void test_hash_map_has(){
	printf("\nRun %s\n", __FUNCTION__);

	int key = 777;
	bool has_key;
	HashMap map;
	int error = hash_map_has(NULL, key, &has_key);
	assert(NULL_POINTER_ERROR == error);

	error = hash_map_has(&map, key, NULL);
	assert(NULL_POINTER_ERROR == error);

	map.nodes = NULL;
	map.is_busy = NULL;
	error = hash_map_has(&map, key, &has_key);
	assert(NULL_POINTER_ERROR == error);

	printf("\n%s done!\n", __FUNCTION__);
}


void test_hash_map_get(){
	printf("\nRun %s\n", __FUNCTION__);

	HashMap map;
	int error = hash_map_init(&map);
	assert(SUCCESS == error);

	int key = 13;
	int value = -999;
	error = hash_map_get(NULL, key, &value);
	assert(NULL_POINTER_ERROR == error);
	error = hash_map_get(&map, key, NULL);
	assert(NULL_POINTER_ERROR == error);
	error = hash_map_get(&map, key, &value);
	assert(SUCCESS == error);
	assert(0 == value);

	printf("\n%s done!\n", __FUNCTION__);
}
