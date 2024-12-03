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


typedef struct {
	Vector *data;  // Array  of  Vectors
	size_t size;  // Fillng level
} Vector2D;


void print_menu(const char *menu[], size_t menu_size);

int menu_init(Vector2D sequences);
int menu_choose_sequence(Vector2D sequences);
int menu_insert(Vector2D sequences);
int menu_remove(Vector2D sequences);
int menu_extract_unique_elements(Vector2D sequences);
int menu_exit(Vector2D sequences);


int main(){
	const char *menu[MENU_SIZE] = {
		"INITIALIZE NEW SEQUENCE\n",
		"CHOOSE SEQUENCE\n",
		"INSERT TERM\n",
		"REMOVE TERM\n",
		"EXTRACT UNIQUE TERMS\n",
		"EXIT\n"
	};
	int (*menu_func[MENU_SIZE])(Vector2D) = {
		menu_init,
		menu_choose_sequence,
		menu_insert,
		menu_remove,
		menu_extract_unique_elements,
		menu_exit
	};
	Vector2D sequences = {NULL, 0};
	size_t sequence_index;
	int choice;
	int error;
	while(true){
		while (true){
			printf("\n");
			print_menu(menu, MENU_SIZE);
			printf("What's your choice?\n");
			error = read_int(&choice, 0, MENU_SIZE - 1);
			if (EOF == error){
				menu_exit(sequences);
				return EXIT_FAILURE;
			}
			assert(SUCCESS == error);
			if (EXIT == choice){
				menu_exit(sequences);
				return EXIT_SUCCESS;
			}
			if (sequences.size > 0 or INIT == choice){
				break;
			}
			printf("You need to INITIALIZE NEW SEQUENCE first!\n");
			printf("Press Enter to continue...\n");
			while (getchar() != '\n');
		}
		error = menu_func[choice](sequences);
		if (EOF == error){
			menu_exit(sequences);
			return EXIT_FAILURE;
		}
		if (SUCCESS != error){
			print_error(error);
			printf("Press Enter to continue...\n");
			while (getchar() != '\n');
		}
		printf("Sequence %zu is: ", sequence_index);
		error = vector_print(sequences.data + sequence_index);
		assert(SUCCESS == error);
	}	
}


void print_menu(const char *menu[], const size_t menu_size){
	assert(NULL != menu);
	for (size_t i = 0; i < menu_size; i++){
		printf("%zu %s", i, menu[i]);
	}
}


int menu_init(Vector *vector, int *sequences_size){
	int size;
	int error;
	if (*is_vector_exist){
		error = vector_free(vector);
		assert(SUCCESS == error);
	}
	printf("Enter size of sequence: ");
	error = read_int(&size, 0, VECTOR_MAX_SIZE);
	if (EOF == error){
		return EOF;
	}
	assert(SUCCESS == error);
	
	printf("Enter a sequence:\n");
	error = vector_init(vector, (size_t)size);
	if (SUCCESS != error){
		return error;
	}
	*is_vector_exist = true;
	return SUCCESS;
}


int menu_choose_sequence(Vector2D sequences){
	return SUCCESS;
}


int menu_insert(Vector2D sequences){
	if (not *is_vector_exist){
		return SUCCESS;
	}
	printf("Enter number to insert: ");
	int item;
	int index;
	int error = read_int(&item, INT_MIN, INT_MAX);
	if (EOF == error){
		return EOF;
	}
	assert(SUCCESS == error);	
	printf("Enter index to insert [0 - %zu]: ", vector -> size);
	error = read_int(&index, 0, (int)vector -> size);
	if (EOF == error){
		return EOF;
	}
	assert(SUCCESS == error);
	error = vector_insert(vector, (size_t)index, item);
	if (SUCCESS != error){
		return error;
	}
	return SUCCESS;
}


int menu_remove(Vector2D sequences){
	if (not *is_vector_exist){
		return SUCCESS;
	}
	if (0 == vector -> size){
		printf("The sequence is empty. Nothing to remove\n");
		printf("Press Enter to continue...\n");
		while (getchar() != '\n');
		return SUCCESS;
	}
	printf("Enter index to remove [0 - %zu]: ", vector -> size - 1);
	int index;
	int error = read_int(&index, 0, (int)vector -> size - 1);
	if (EOF == error){
		return EOF;
	}
	assert(SUCCESS == error);
	error = vector_remove(vector, (size_t)index);
	if (SUCCESS != error){
		return error;
	}
	return SUCCESS;
}


int menu_extract_unique_elements(Vector2D sequences){
	return SUCCESS;
}


int menu_exit(Vector2D sequences){
	int error;
	for (size_t i = 0; i < sequences.size; i++){
		error = vector_free(sequences.data + i);
		assert(SUCCESS == error);
	}
	return SUCCESS;
}
