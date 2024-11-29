#include <stdio.h>

#include "hash_map.h"

void test_hash_map_init();
void test_hash_map_get();
void test_hash_map_has();


int main(){
	test_hash_map_init();

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


void test_hash_map_has(){
	printf("\nRun %s\n", __FUNCTION__);

	HashMap map;
	
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
