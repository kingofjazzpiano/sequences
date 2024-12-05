#include <stdio.h>

#include "hash_map.h"


int main(){
	size_t data_size = 100ull;
	unsigned hash_table_bit_size = 7u;

	size_t hash_table_size = 1 << hash_table_bit_size;
	unsigned *collisions = (unsigned *)calloc(hash_table_size, sizeof(unsigned));
	if (NULL == collisions){
		perror("Something went wrong");
		return EXIT_FAILURE;
	}
	
	for (size_t i = 0; i < data_size; i++){
		int key = i;
		unsigned hash_code = hash(key, hash_table_bit_size);
		printf("%u ", hash_code); // Visual check
		collisions[hash_code]++;
	}
	printf("\n");

	for (size_t i = 0; i < hash_table_size; i++){
		printf("%zu %u\t", i, collisions[i]);
	}

	printf("sizeof(bool)=%zu\n", sizeof(bool));

	printf("\n%s done!\n", __FILE__);
}
