#ifndef HASH_TABLE_H
#define HASH_TABLE_H


#include <assert.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <iso646.h>

#define SUCCESS 0
#define NULL_POINTER_ERROR 1
#define NOT_ENOUGH_MEMORY_ERROR 2
#define KEY_DOES_NOT_EXIST_ERROR 3
//#define INDEX_IS_OUT_OF_RANGE_ERROR 3 // TODO: delete line

// Amount of bits of minimal hash map size
#define MIN_CAPACITY_BIT_SIZE 4


// Hash Map entry
typedef struct {
	int key;
	int value;
} HashMapNode;

typedef struct {
	HashMapNode *nodes;  // Array of nodes of length capacity
	bool *is_busy;  // Araay of bools of length capacity
	uint32_t size;  // Filling level
	uint32_t capacity;  // Size of buffer measured in nodes
	int capacity_bit_size;  // Bits amount of capacity
} HashMap;


uint32_t hash(int32_t key, int hash_bits_amount);
int hash_map_init(HashMap *map);
int hash_map_has(HashMap *map, int key, bool *has_key);
int hash_map_set(HashMap *map, int key, int value);
int hash_map_get(const HashMap *map, int key, int *value);
int hash_map_free(HashMap *map);


#endif
