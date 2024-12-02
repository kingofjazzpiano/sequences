#include "vector.h"


#define INIT 0
#define CHOOSE_SEQUENCE 1
#define INSERT 2
#define REMOVE 3
#define EXTRACT_UNIQUE_ELEMENTS 4
#define EXIT 5

#define MENU_SIZE 6


void print_menu(const char *menu[], size_t menu_size);

void menu_exit(vector_t *vector, bool is_vector_exist);
int menu_init(vector_t *vector, bool *is_vector_exist);
int menu_insert(vector_t *vector, bool *is_vector_exist);
int menu_remove(vector_t *vector, bool *is_vector_exist);


int (*menu_func[MENU_SIZE])(vector_t *, bool *) = {
	menu_init,
	NULL,
	menu_insert,
	menu_remove,
	NULL,
	NULL
};


int main(){
	const char *menu[MENU_SIZE] = {
		"INITIALIZE NEW SEQUENCE\n",
		"CHOOSE SEQUENCE\n",
		"INSERT TERM\n",
		"REMOVE TERM\n",
		"EXTRACT UNIQUE TERMS\n",
		"EXIT\n"
	};
	vector_t vector;
	int choice;
	int error;
	bool is_vector_exist = false;
	while(true){
		while (true){
			printf("\n");
			print_menu(menu, MENU_SIZE);
			printf("What's your choice?\n");
			error = read_int(&choice);
			if (EOF == error){
				menu_exit(&vector, is_vector_exist);
				return EXIT_FAILURE;
			}
			assert(SUCCESS == error);
			if (EXIT == choice){
				menu_exit(&vector, is_vector_exist);
				return EXIT_SUCCESS;
			}
			if (choice < 0 or choice >= MENU_SIZE){
				printf("Wrong choice! Try again.\n");
				continue;
			}
			if (is_vector_exist or INIT == choice){
				break;
			}
			printf("You need to INITIALIZE NEW SEQUENCE first!\n");
		}
		error = menu_func[choice](&vector, &is_vector_exist);
		if (EOF == error){
			menu_exit(&vector, is_vector_exist);
			return EXIT_FAILURE;
		}
		if (SUCCESS != error){
			print_error(error);
		}
		printf("Sequence is: ");
		error = vector_print(&vector);
		assert(SUCCESS == error);
	}	
}


void print_menu(const char *menu[], size_t menu_size){
	assert(NULL != menu);
	for (size_t i = 0; i < menu_size; i++){
		printf("%zu %s", i, menu[i]);
	}
}


int menu_init(vector_t *vector, bool *is_vector_exist){
	int size;
	int error;
	if (*is_vector_exist){
		error = vector_free(vector);
		assert(SUCCESS == error);
	}
	printf("Enter size of sequence: ");
	while (true){
		error = read_int(&size);
		if (EOF == error){
			return EOF;
		}
		assert(SUCCESS == error);
		if (size >= 0){
			break;
		}
		printf("Size shoud be non negative!\n");
	}
	
	printf("Enter a sequence:\n");
	error = vector_init(vector, (size_t)size);
	if (SUCCESS != error){
		return error;
	}
	*is_vector_exist = true;
	return SUCCESS;
}


int menu_insert(vector_t *vector, bool *is_vector_exist){
	if (not *is_vector_exist){
		return SUCCESS;
	}
	printf("Enter number to insert: ");
	int item;
	int index;
	int error = read_int(&item);
	if (EOF == error){
		return EOF;
	}
	assert(SUCCESS == error);	
	printf("Enter index to insert [0 - %zu]: ", vector -> size);
	error = read_int(&index);
	if (EOF == error){
		return EOF;
	}
	assert(SUCCESS == error);
	error = vector_insert(vector, (size_t)index, item);

}


int menu_remove(vector_t *vector, bool *is_vector_exist){
	if (not *is_vector_exist){
		return SUCCESS;
	}
	printf("Enter index to remove: ");
	int index;
	int error = read_int(&index);
	if (EOF == error){
		return EOF;
	}
	assert(SUCCESS == error);
	printf("Enter index to remove [0 - %zu]: ", vector -> size);
	error = vector_remove(vector, (size_t)index);
	if (SUCCESS != error){
		return error;
	}
	return SUCCESS;
}


void menu_exit(vector_t *vector, bool is_vector_exist){
	int error;
	if (is_vector_exist){
		error = vector_free(vector);
		assert(SUCCESS == error);
	}
}



