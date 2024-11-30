#include "hash_map.h"


uint32_t hash(int32_t key, int hash_bit_size){
	/* Knuth's multiplicative method */
	assert(hash_bit_size >= 1 && hash_bit_size <= 32);
	return ((uint32_t)key * (uint32_t)2654435769) >> (32 - hash_bit_size);
}


// TODO: create hash_map_alloc(hash_map *map, unsigned capacity);

static int hash_map_resize(HashMap *map, int new_capacity_bit_size){
	/* Allocates new hash map and re-hash all keys */
	if (NULL == map or NULL == map -> nodes or NULL == map -> is_busy){
		return NULL_POINTER_ERROR;
	}
	assert(MIN_CAPACITY_BIT_SIZE <= new_capacity_bit_size
		   and 32 >= new_capacity_bit_size);

	unsigned new_capacity = (1 << new_capacity_bit_size);
	assert(new_capacity > map -> size);
	HashMapNode *new_nodes = (HashMapNode *)malloc(
							 sizeof(HashMapNode) * new_capacity);
	if (NULL == new_nodes){
		return NOT_ENOUGH_MEMORY_ERROR;
	}
	bool *new_is_busy = (bool *)calloc(new_capacity, sizeof(bool));
	if (NULL == new_is_busy){
		return NOT_ENOUGH_MEMORY_ERROR;
	}
	
	// Re-hash all keys
	for (unsigned i = 0; i < map -> capacity; i++){
		if (map -> is_busy[i]){
			unsigned new_index = hash(map -> nodes[i].key,
										  new_capacity_bit_size);
			assert(new_index < new_capacity);
			while (new_is_busy[new_index]){
				// TODO: Как отследить зацикливание, если все узлы заняты?
				new_index++;
				if (new_index == new_capacity){
					new_index = 0;
				}
			}
			new_is_busy[new_index] = true;
			new_nodes[new_index].key = map -> nodes[i].key;
			new_nodes[new_index].value = map -> nodes[i].value;
		}
	}
	
	free(map -> nodes);
	free(map -> is_busy);
	map -> nodes = new_nodes;
	map -> is_busy = new_is_busy;
	map -> capacity = new_capacity;
	map -> capacity_bit_size = new_capacity_bit_size;

	return SUCCESS;
}


int hash_map_init(HashMap *map){
	if (NULL == map){
		return NULL_POINTER_ERROR;
	}
	map -> size = 0;
	map -> capacity_bit_size = MIN_CAPACITY_BIT_SIZE;
	map -> capacity = (uint32_t)(1 << MIN_CAPACITY_BIT_SIZE);
	map -> nodes = (HashMapNode *)malloc(sizeof(HashMapNode) * map -> capacity);
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
	assert(i < map -> capacity);
	while (map -> is_busy[i]){
		// TODO: Как отследить зацикливание, если все узлы заняты?
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
	if (NULL == map or NULL == map -> nodes or NULL == map -> is_busy){
		return NULL_POINTER_ERROR;
	}
	bool has_key = false;
	uint32_t i = hash(key, map -> capacity_bit_size);
	assert(i < map -> capacity);
	while (map -> is_busy[i]){
		// TODO: Как отследить зацикливание, если все узлы заняты?
		if ((map -> nodes[i]).key == key){
			has_key = true;
			break;
		}
		i++;
		if (i == map -> capacity){
			i = 0;
		}
	}
	
	if (has_key){
		map -> is_busy[i] = true;
		map -> nodes[i].key = key;
		(map -> nodes)[i].value = value;
	}
	else {
		
	}
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


int hash_map_print(const HashMap *map){
	/* Print Hash Map <key: value> pairs */
	if (NULL == map or NULL == map -> nodes or NULL == map -> is_busy){
		return NULL_POINTER_ERROR;
	}
	for (unsigned i = 0; i < map -> capacity; i++){
		if (map -> is_busy[i]){
			printf("(%d: %d) ", (map -> nodes)[i].key,
							   (map -> nodes)[i].value);
		}
	}
	printf("\n");
	return SUCCESS;
}
