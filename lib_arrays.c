#include "lib_arrays.h"

#define CHECK_MEM(ptr) do { \
    if (ptr == NULL) { \
        puts("memory allocation error!\nexecution aborted"); \
        abort(); \
        } \
} while(0)

// *** swap
void swapInt (int *a, int *b) {

    int t = *a;
    *a = *b;
    *b = t;
}

// *** fill arrays
void fillIntRandom (int* array, const int SIZE, const int BORDER) {

    srand (time (NULL));
    for (int i = 0; i < SIZE; ++i)
        *(array +i) = rand () % BORDER;
}

void fillIntRandom2D (int** array, const int ROWS, const int COLS, const int BORDER) {

    srand (time (NULL));
    /*for (int i = 0; i < ROWS; ++i)
        for (int j = 0; j < col; ++j)
            array [i][j] = rand () % border;*/

    // Вариант обхода одним указателем динамического двумерного массива
    int** ptr = (int**) array;
    int** end = (int**) array + ROWS;
    while (ptr != end) {
        // Конечный запредельный(!) адрес текущего(!) массива
        int* e = (int*)*ptr + COLS;
        for (int *i = *ptr; i != e; i++) {
            *i = rand () % BORDER;
        }
        // Смещение к следующему массиву
        ++ptr;
    }

}

// *** print arrays
void printIntArray (int* array, const int SIZE, const int OFFSET) {
    char format [7];

    sprintf (format, "%%%dd", OFFSET);
    for (int i = 0; i < SIZE; ++i) {
        printf (format, *(array +i));
        if (i != SIZE - 1)
            printf (",");
    }
    printf ("\n");
}

void printIntArray2D (int** array, const int ROWS, const int COLS, const int OFFSET) {
    char format [7];

    sprintf (format, "%%%dd", OFFSET);
    // Вариант обхода одним указателем динамического двумерного массива
    int** ptr = (int**) array;
    int** end = (int**) array + ROWS;
    while (ptr != end) {
        // Конечный запредельный(!) адрес текущего(!) массива
        int* e = (int*) *ptr + COLS;
        for (int *i = *ptr; i != e; i++) {
            printf (format, *i);
            if (i + 1 != e) printf (",");
        }
        // Смещение к следующему массиву
        ++ptr;
        printf ("\n");
    }
}

// *** memory allocation
int* makeIntArray (int* array, const int SIZE) {
    array = calloc (SIZE, sizeof (int));
    CHECK_MEM (array);
    // return
    return array;
}

int** makeIntArray2D (int** array, const int ROWS, const int COLS) {
    array = (int**) malloc (ROWS * sizeof (int*));
    CHECK_MEM (array);
    for (int i = 0; i < ROWS; ++i) {
        *(array +i) = (int*) malloc (COLS * sizeof (int));
        CHECK_MEM (array);
    }
    // return
    return array;
}

// *** Garbage collector
void freeArray2D (int** array, const int ROWS) {

    // Халява закончилась -(
    for (int i = 0; i < ROWS; i++)
        free ((int*)*(array + i));

    free (array);
}
