#include "vector.h"


#define INIT 1
#define INSERT 2
#define REMOVE 3
#define EXTRACT_UNIQUE_ELEMENTS 4
#define EXIT 5

#define MENU_SIZE 6
#define ERROR_AMOUNT 4


void print_menu(const char *menu[], size_t menu_size);


int main(){
	const char *menu[MENU_SIZE] = {
		NULL,  // No zero menu item
		"INIT\n",
		"INSERT\n",
		"REMOVE\n",
		"EXTRACT UNIQUE ELEMENTS\n",
		"EXIT\n"
	};
	// Error messages corresponds to error codes defined in vector.h 
	const char *error_message[ERROR_AMOUNT] = {
		NULL,  // 0 is SUCCESS. No need to print
		"NULL POINTER ERROR\n",
		"NOT ENOUGH MEMORY\n",
		"INDEX IS OUT OF RANGE\n"
	};
	vector_t vector;
	int size;
	int choice;
	int item;
	int index;
	int error;
	bool is_vector_exist = false;
	while(true){
		print_menu(menu, MENU_SIZE);
		printf("What's your choice?\n");
		error = read_int(&choice);
		if (EOF == error){
			if (is_vector_exist){
				error = vector_free(&vector);
				assert(SUCCESS == error);
			}
			return EXIT_FAILURE;
		}
		assert(SUCCESS == error);
		if (INIT == choice){
			if (is_vector_exist){
				error = vector_free(&vector);
				assert(SUCCESS == error);
			}
			printf("Enter size of sequence: ");
			while (true){
				error = read_int(&size);
				if (EOF == error){
					return EXIT_FAILURE;
				}
				assert(SUCCESS == error);
				if (size >= 0){
					break;
				}
				printf("Size shoud be non negative!\n");
			}
			
			printf("Enter a sequence:\n");
			error = vector_init(&vector, (size_t)size);
			if (SUCCESS != error){
				printf("%s", error_message[error]);
				continue;
			}
			is_vector_exist = true;
		}
		else if (INSERT == choice){
			if (not is_vector_exist){
				printf("You need to INIT first!\n\n");
				continue;
			}
			printf("Enter number to insert: ");
			error = read_int(&item);
			if (EOF == error){
				error = vector_free(&vector);
				assert(SUCCESS == error);
				return EXIT_FAILURE;
			}
			assert(SUCCESS == error);	
			printf("Enter index to insert [0 - %zu]: ", vector.size);
			error = read_int(&index);
			if (EOF == error){
				error = vector_free(&vector);
				assert(SUCCESS == error);
				return EXIT_FAILURE;
			}
			assert(SUCCESS == error);
			error = vector_insert(&vector, (size_t)index, item);
			if (SUCCESS != error){
				printf("%s", error_message[error]);
				continue;
			}
			assert(SUCCESS == error);
		}
		else if (REMOVE == choice){
			if (not is_vector_exist){
				printf("You need to INIT first!\n\n");
				continue;
			}
			printf("Enter index to remove: ");
			error = read_int(&index);
			assert(SUCCESS == error);			
			error = vector_remove(&vector, (size_t)index);
			assert(SUCCESS == error);
		}
		else if (EXIT == choice){
			if (is_vector_exist){
				error = vector_free(&vector);
				assert(SUCCESS == error);
			}
			return 0;
		}
		else {
			printf("Wrong choice! Try again.\n");
			continue;
		}
		printf("Sequence is: ");
		error = vector_print(&vector);
		assert(SUCCESS == error);
		printf("\n");
	}	
}


void print_menu(const char *menu[], size_t menu_size){
	assert(NULL != menu);
	for (size_t i = 1; i < menu_size; i++){
		printf("%zu %s", i, menu[i]);
	}
}
