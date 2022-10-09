#ifndef LIB_ARRAYS_H
#define LIB_ARRAYS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <stdbool.h>
//#include <stdarg.h>

// *** swap
void swapInt (int *a, int *b);

// *** fill arrays
void fillIntRandom (int* array, const int SIZE, const int BORDER);
void fillIntRandom2D (int** array, const int ROWS, const int COLS, const int BORDER);

// *** print arrays
void printIntArray (int* array, const int SIZE, const int OFFSET);
void printIntArray2D (int** array, const int ROWS, const int COLS, const int OFFSET);

// *** memory allocation
int* makeIntArray (int* array, const int SIZE);
int** makeIntArray2D (int** array, const int ROWS, const int COLS);

// *** Garbage collector
void freeArray2D (int** array, const int ROWS);

#endif // LIB_ARRAYS_H