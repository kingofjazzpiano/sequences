#include "hash_map.h"


uint32_t hash(int32_t key, int hash_bit_size){
	/* Knuth's multiplicative method */
	assert(hash_bit_size >= 1 && hash_bit_size <= 31);
	return ((uint32_t)key * (uint32_t)2654435769) >> (32 - hash_bit_size);
}


int hash_map_init(HashMap *map){
	if (NULL == map){
		return NULL_POINTER_ERROR;
	}
	map -> size = 0;
	map -> capacity_bit_size = MIN_CAPACITY_BIT_SIZE;
	map -> capacity = (uint32_t)(1 << MIN_CAPACITY_BIT_SIZE);
	map -> nodes = (HashMapNode *)malloc(sizeof(HashMapNode)
												 * map -> capacity);
	if (NULL == map -> nodes){
		return NOT_ENOUGH_MEMORY_ERROR;
	}
	map -> is_busy = (bool *)calloc(map -> capacity, sizeof(bool));
	if (NULL == map -> is_busy){
		return NOT_ENOUGH_MEMORY_ERROR;
	}
	return SUCCESS;
}


int hash_map_has(HashMap *map, int key, bool *has_key){
	if (NULL == map or NULL == has_key or NULL == map -> nodes
			or NULL == map -> is_busy){
		return NULL_POINTER_ERROR;
	}
	uint32_t i = hash(key, map -> capacity_bit_size);
	while (map -> is_busy[i]){
		if ((map -> nodes[i]).key == key){
			*has_key = true;
			return SUCCESS;
		}
		i++;
		if (i == map -> capacity){
			i = 0;
		}
	}
	*has_key = false;
	return SUCCESS;
}


int hash_map_set(HashMap *map, int key, int value){
	/* Set value by given key */
	return SUCCESS;
}


int hash_map_get(const HashMap *map, int key, int *value){
	/* Get value by given key */
	return SUCCESS;
}


int hash_map_free(HashMap *map){
	if (NULL == map){
		return NULL_POINTER_ERROR;
	}
	map -> size = 0;
	map -> capacity_bit_size = 0;
	free(map -> nodes);
	free(map -> is_busy);
	return SUCCESS;
}
