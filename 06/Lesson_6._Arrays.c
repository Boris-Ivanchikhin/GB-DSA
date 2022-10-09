// *** Урок 6. Массивы. Упражнение №1

#include <locale.h>  // Для setlocale (LC_ALL, "")
#include <stdbool.h> // Для bool
#include <math.h>
#include "../lib_arrays.h"

/* 
* 1.Реализовать пузырьковую сортировку двумерного массива например, 
*   массив 1,9,2 5,7,6 4,3,8 должен на выходе стать 1,2,3 4,5,6 7,8,9.
*/
void bubbleSort2D (int** array, const int ROWS, const int COLS) {
    bool sorted = false;

    while (sorted != true) {
        // сдвиги очередных элементов в правильную позицию
        sorted = true;        
        // сдвиг элемента массива в правильную позицию
        for (int i = 0; i < ROWS ; i++){
            for (int j = 0; j < COLS; j++) {
                //  последний элемент во всем массиве
                if (i == ROWS - 1 && j == COLS - 1) {
                    continue;
                }
                // сравнение текущего и следующего элементов
                int *ptrCur =  *(array + i)+ j;
                int *ptrNxt = (j ==   COLS - 1) ?
                               *(array + i + 1) : // первый элемент следующей строки     [i+1] [0]
                               *(array + i)+ j + 1; // следующий элемент текущей строки   [i] [j+1]
                if (*ptrCur >  *ptrNxt) {
                    swapInt (ptrCur, ptrNxt);
                    sorted = false;
                }
            }
        }
    }
}

/*
* 3.Алгоритм Трабба-Прадо-Кнута:
*   a. запросить у пользователя 11 чисел и записать их в последовательность;
*   b. инвертировать последовательность;
*   c. для каждого элемента последовательности П произвести вычисление
*      по формуле sqrt(fabs(Х)) + 5 * pow(Х, 3) и если результат вычислений 
*      превышает 400 - проинформировать пользователя. 
*
* https://en.wikipedia.org/wiki/TPK_algorithm
*/
void TrabbPardoKnuth_Algorithm () {
    const int count = 11;
    int *array = makeIntArray (array, 11);

    // не хочется вводить все это ручками
    fillIntRandom (array, count, 10);
    printIntArray (array, count, 3);
    printf ("\n");
    // в обратном порядке
    for (int i = count - 1; i >= 0; --i)
    {
        int value = *(array + i);
        double y = sqrt (fabs (value)) + 5 * pow (value, 3);
        if (y > 400.0)
            printf ("%3d [%02d]: too large\n", value, i + 1);
        else
            printf ("%3d [%02d]: %f\n", value, i + 1, y);
    }
    free (array);
}

// Функция, вызываемая при завершении работы
void endFunction (void)
{   
    // Вывод сообщения о завершении работы
    puts ("\nthe work is completed!");
}

// main
int main(void) {

    // Русский язык в консоли
    setlocale(LC_ALL, "");

    // Регистрация функции, которая будет вызвана, при нормальном завершении работы.
    if (atexit (endFunction)) {
        // Проверка регистрации функции endFunction
        puts ("post- function registration error!");
    }

    // Массив 3x4
    const int rows = 3;
    const int cols = 4;

    // Урок 6. Массивы. Упражнение №1
    int **array1 = makeIntArray2D (array1, rows, cols);
    fillIntRandom2D (array1, rows, cols, 50);
    puts ("Lesson 6. Arrays. Exercise #1\n");
    printIntArray2D (array1, rows, cols, 5);

    bubbleSort2D (array1, rows, cols);
    puts ("\nbubble sorting of a two-dimensional array:\n");
    printIntArray2D (array1, rows, cols, 5);

    // Урок 6. Массивы. Упражнение №3
    puts ("\nLesson 6. Arrays. Exercise #3\n");
    TrabbPardoKnuth_Algorithm ();

    freeArray2D (array1, rows);

    // return o.k.
    return EXIT_SUCCESS;
}