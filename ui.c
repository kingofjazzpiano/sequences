#include "vector.h"
#include "hash_map.h"


#define MENU_SIZE 6

// Menu Items
#define INIT 0
#define CHOOSE_SEQUENCE 1
#define INSERT 2
#define REMOVE 3
#define EXTRACT_UNIQUE_ELEMENTS 4
#define EXIT 5

#define SEQUENCES_MAX_AMOUNT 3


typedef struct {
	Vector *data;  // Array  of  Vectors
	int size;  // Fillng level
} Vector2D;


void print_menu(const char *menu[], int menu_size);

int menu_init(Vector2D *sequences, int *sequence_index);
int menu_choose_sequence(Vector2D *sequences, int *sequence_index);
int menu_insert(Vector2D *sequences, int *sequence_index);
int menu_remove(Vector2D *sequences, int *sequence_index);
int menu_extract_unique_elements(Vector2D *sequences, int *sequence_index);
int menu_exit(Vector2D *sequences, int *sequence_index);


int main(){
	const char *menu[MENU_SIZE] = {
		"INITIALIZE NEW SEQUENCE\n",
		"CHOOSE SEQUENCE\n",
		"INSERT TERM\n",
		"REMOVE TERM\n",
		"EXTRACT UNIQUE TERMS\n",
		"EXIT\n"
	};
	int (*menu_func[MENU_SIZE])(Vector2D *, int *) = {
		menu_init,
		menu_choose_sequence,
		menu_insert,
		menu_remove,
		menu_extract_unique_elements,
		menu_exit
	};
	Vector2D sequences;
	// TODO: calloc instead of malloc
	sequences.data = (Vector *)malloc(sizeof(Vector) * SEQUENCES_MAX_AMOUNT);
	if (NULL == sequences.data){
		return EXIT_FAILURE;
	}
	sequences.size = 0;
	int sequence_index = 0;
	int choice;
	int error;
	while(true){
		while (true){
			printf("\n");
			print_menu(menu, MENU_SIZE);
			if (sequences.size > 0){
				printf("Sequence <%d> is: ", sequence_index);
				assert(sequence_index >= 0 and sequence_index < SEQUENCES_MAX_AMOUNT);
				error = vector_print(sequences.data + sequence_index);
				assert(SUCCESS == error);
			}
			printf("What's your choice?\n");
			error = read_int(&choice, 0, MENU_SIZE - 1);
			if (EOF == error){
				menu_exit(&sequences, &sequence_index);
				return EXIT_FAILURE;
			}
			assert(SUCCESS == error);
			if (EXIT == choice){
				menu_exit(&sequences, &sequence_index);
				return EXIT_SUCCESS;
			}
			if (sequences.size > 0 or INIT == choice){
				break;
			}
			printf("You need to INITIALIZE NEW SEQUENCE first!\n");
			printf("Press Enter to continue...\n");
			while (getchar() != '\n');
		}
		if ( (INIT == choice or EXTRACT_UNIQUE_ELEMENTS == choice)
				and sequences.size >= SEQUENCES_MAX_AMOUNT){
			printf("Impossible to create new sequence.\n");
			printf("Press Enter to continue...\n");
			while (getchar() != '\n');
			continue;
		}
		assert(choice >= 0 and choice < MENU_SIZE);
		assert(sequence_index >= 0 and sequence_index < SEQUENCES_MAX_AMOUNT);
		error = menu_func[choice](&sequences, &sequence_index);
		if (EOF == error){
			menu_exit(&sequences, &sequence_index);
			return EXIT_FAILURE;
		}
		if (SUCCESS != error){
			print_error(error);
			continue;
		}
	}	
}


void print_menu(const char *menu[], const int menu_size){
	assert(NULL != menu);
	for (int i = 0; i < menu_size; i++){
		printf("%d %s", i, menu[i]);
	}
}


int menu_init(Vector2D *sequences, int *sequence_index){
	if (NULL == sequences or NULL == sequences -> data
			or NULL == sequence_index){
		return NULL_POINTER_ERROR;
	}
	assert(sequences -> size < SEQUENCES_MAX_AMOUNT);
	int size;
	printf("Enter size of sequence: ");
	int error = read_int(&size, 0, VECTOR_MAX_SIZE);
	if (EOF == error){
		return EOF;
	}
	assert(SUCCESS == error);
	printf("Enter a sequence:\n");
	error = vector_init(sequences -> data + sequences -> size, (size_t)size);
	// TODO: Очищать память сейчас
	if (SUCCESS != error){
		return error;
	}
	*sequence_index = sequences -> size;
	sequences -> size++;
	return SUCCESS;
}


int menu_choose_sequence(Vector2D *sequences, int *sequence_index){
	if (NULL == sequence_index){
		return NULL_POINTER_ERROR;
	}
	assert(sequences -> size > 0
			and sequences -> size <= SEQUENCES_MAX_AMOUNT);
	printf("Enter number of sequence [0 - %d]: ", sequences -> size - 1);
	int error = read_int(sequence_index, 0, sequences -> size - 1);
	if (EOF == error){
		return EOF;
	}
	return SUCCESS;
}


int menu_insert(Vector2D *sequences, int *sequence_index){
	if (NULL == sequences or NULL == sequences -> data
			or NULL == sequence_index){
		return NULL_POINTER_ERROR;
	}
	assert(sequences -> size > 0);
	assert(*sequence_index < sequences -> size);
	printf("Enter number to insert: ");
	int item;
	int index;
	int error = read_int(&item, INT_MIN, INT_MAX);
	if (EOF == error){
		return EOF;
	}
	assert(SUCCESS == error);	
	printf("Enter index to insert [0 - %zu]: ",
			sequences -> data[*sequence_index].size);
	error = read_int(&index, 0, sequences -> data[*sequence_index].size);
	if (EOF == error){
		return EOF;
	}
	assert(SUCCESS == error);
	error = vector_insert(sequences -> data + *sequence_index,
						  (size_t)index, item);
	if (SUCCESS != error){
		return error;
	}
	return SUCCESS;
}


int menu_remove(Vector2D *sequences, int *sequence_index){
	if (NULL == sequences or NULL == sequences -> data
			or NULL == sequence_index){
		return NULL_POINTER_ERROR;
	}
	assert(sequences -> size > 0
			and sequences -> size <= SEQUENCES_MAX_AMOUNT);
	assert(*sequence_index < sequences -> size);
	if (0 == sequences -> data[*sequence_index].size){
		printf("The sequence is empty. Nothing to remove\n");
		printf("Press Enter to continue...\n");
		while (getchar() != '\n');
		return SUCCESS;
	}
	printf("Enter index to remove [0 - %zu]: ",
			sequences -> data[*sequence_index].size - 1);
	int index;
	int error = read_int(&index, 0,
					(int)(sequences -> data[*sequence_index].size) - 1);
	if (EOF == error){
		return EOF;
	}
	assert(SUCCESS == error);
	error = vector_remove(sequences -> data
							+ *sequence_index, (size_t)index);
	if (error){
		return error;
	}
	return SUCCESS;
}


int menu_extract_unique_elements(Vector2D *sequences, int *sequence_index){
	if (NULL == sequences or NULL == sequences -> data
			or NULL == sequence_index){
		return NULL_POINTER_ERROR;
	}
	assert(sequences -> size > 0
			and sequences -> size < SEQUENCES_MAX_AMOUNT);
	assert(*sequence_index < sequences -> size);
	HashMap map;
	// TODO: Когда очищать память при ошибке?
	int error = hash_map_init(&map);
	if (error){
		return error;
	}
	for (size_t i = 0; i < sequences -> data[*sequence_index].size; i++){
		int key = sequences -> data[*sequence_index].data[i];
		int *count = NULL;
		bool has_key;
		error = hash_map_has(&map, key, &has_key);
		if (error){
			return error;
		}
		if (has_key){
			error = hash_map_get_value_pointer(&map, key, &count);
			if (error){
				return error;
			}
			(*count)++;
		}
		else {
			error = hash_map_set(&map, key, 1);  // Set 1 to counter
			if (error){
				return error;
			}
		}
	}
	// Creation of empty Vector
	error = vector_init(sequences -> data + sequences -> size, 0);
	if (error){
		// TODO: Когда очищать память при ошибке?
		return error;
	}
	size_t i = 0;
	while (i < sequences -> data[*sequence_index].size){
		int key = sequences -> data[*sequence_index].data[i];
		int *count = NULL;
		// All keys exist here
		int error = hash_map_get_value_pointer(&map, key, &count);
		if (error){
			return error;
		}
		if (*count == 1){
			error = vector_insert(sequences -> data + sequences -> size,
						sequences -> data[sequences -> size].size, key);
			if (error){
				return error;
			}
			error = vector_remove(sequences -> data + *sequence_index, i);
			if (error){
				return error;
			}
		}
		else if (*count > 1){
			i++;
			continue;
		}
		else {
			error = hash_map_free(&map);
			assert(SUCCESS == error);
			printf("IMPOSIBLE. FIX THAT: %s\n", __FUNCTION__);
			return -1;
		}
	}
	*sequence_index = sequences -> size;
	sequences -> size++;
	error = hash_map_free(&map);
	assert(SUCCESS == error);
	return SUCCESS;
}


int menu_exit(Vector2D *sequences, int *sequence_index){
	if (NULL == sequences or NULL == sequences -> data){
		return NULL_POINTER_ERROR;
	}
	for (int i = 0; i < sequences -> size; i++){
		int error = vector_free(sequences -> data + i);
		assert(SUCCESS == error);
	}
	free(sequences -> data);
	sequences -> data = NULL;
	return SUCCESS;
}
