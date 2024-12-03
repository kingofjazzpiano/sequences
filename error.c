#include "error.h"


void print_error(int error){
	/* Prints an error message based on errors defined in error.h */
	
	/*
	 * General errors
	 */
	if (SUCCESS == error){
		// No error
	}
	else if (NULL_POINTER_ERROR == error){
		printf("%s\n", "NULL POINTER ERROR");
	}
	else if (NOT_ENOUGH_MEMORY_ERROR == error){
		printf("%s\n", "NOT ENOUGH MEMORY ERROR");
	}

	/*
	 * Vector specific errors
	 */
	else if (INDEX_IS_OUT_OF_RANGE_ERROR == error){
		printf("%s\n", "INDEX IS OUT OF RANGE ERROR");
	}

	/*
	 * HashMap specific errors
	 */
	else if (KEY_DOES_NOT_EXIST_ERROR == error){
		printf("%s\n", "KEY DOES NOT EXIST ERROR");
	}

	/*
	 * Other error
	 */
	else if (WRONG_LIMITS_ERROR == error){
		printf("%s\n", "WRONG LIMITS ERROR");
	}

	/*
	 * None of the above
	 */
	else {
		printf("%s\n", "UNKNOWN ERROR");
	}
}
