#ifndef ERROR_H
#define ERROR_H


#include <stdio.h>


// General errors [0 - 99]
#define SUCCESS 0
#define NULL_POINTER_ERROR 1
#define NOT_ENOUGH_MEMORY_ERROR 2


// Vector specific errors [100 - 199]
#define INDEX_IS_OUT_OF_RANGE_ERROR 100


// HashMap specific errors [200 - 299]
#define KEY_DOES_NOT_EXIST_ERROR 200


void print_error(int error);


#endif  // ERRORR_H
