// *** Урок 7. Сложные сортировки массивов

#include <locale.h>  // Для setlocale (LC_ALL, "")
#include <math.h>    // Для pow
#include <string.h>  // Для memcpy
#include "../lib_arrays.h"

#define DEBUG

// Сотрировка вставками
void sortInserts (int *array, const int FIRST, const int LAST) {
    int temp, pos, i;

    for (i = FIRST + 1; i <= LAST; i++) {
        temp = *(array + i);
        pos  = i - 1;
        while (pos >= FIRST && *(array + pos) > temp) {
            *(array + pos + 1) = *(array + pos);
            pos =  pos - 1;
        }
        *(array + pos + 1) = temp;
    }
}

// Получение медианы отрезка массива
int getMedian (int *array, const int FIRST, const int LAST) {

    // Сравнение медианы с первым элементов
    int middle =  (FIRST + LAST) / 2;
    int minValue  = (*(array + FIRST) > *(array + middle)) ? *(array + middle) : *(array + FIRST);
    int maxValue  = (*(array + FIRST) > *(array + middle)) ? *(array + FIRST)  : *(array + middle);

    // Коррекция значения медианы относитально значения array [LAST]
    int result;
    if (minValue > *(array + LAST)) result = minValue;
    else if (*(array + LAST) > maxValue) result = maxValue;
    else result = *(array + LAST);

    // Возврат индекса найденной медианы
    if (result == *(array + FIRST)) return FIRST;
    else if (result == *(array + middle)) return middle;
    // else... т.е. явный return
    return LAST;
}

/* 
 * 1.Описать в коде улучшенный алгоритм быстрой сортировки.
 */

void quickSortPlus (int* array, const int FIRST, const int LAST) {
    int const LIMIT = 10;

    // Если размер сортируемой части <= LIMIT, то большого смысла продолжать рекурсию нет.
    // Применяется сортировка вставками -> без использования рекурсии.
    if (LAST - FIRST <= 10) {
        sortInserts (array, FIRST, LAST);
        return;
    }

    // Иначе используется простой quick sort
    int med = getMedian (array, FIRST, LAST);
    swapInt (array + med, array + (FIRST + LAST) / 2);
    int i   = FIRST, j = LAST;
    int value = *(array + (FIRST + LAST) / 2);
    do {
        while (*(array + i) < value) i++;
        while (*(array + j) > value) j--;
        if (i <= j) {
            swapInt (array + i, array + j);
            i++; j--;
            }
    } while (i <= j);

    quickSortPlus (array, i, LAST);
    quickSortPlus (array, FIRST, j);
}

/* 
 * 2.Сортировать в массиве целых положительных чисел только чётные числа, 
 *   нечётные оставив на своих местах при помощи алгоритма блочной сортировки, 
 *   то есть массив вида [0 2 8 3 4 6 5 9 8 2 7 3] превратить в [0 2 2 3 4 4 5 9 8 8 7 3]
 */
void bucketSort (int array[], const int SIZE) {
    const int max = SIZE;
    const int BUCKETS = 10;

    // use bucket[x][max] to hold the current count
    int bucket [BUCKETS][max + 1];

    // init bucket counters
    for (int x = 0; x < BUCKETS; x++) bucket [x][max] = 0;

    // main loop for each digit position
    for (int digit = 1; digit <= (int)pow (BUCKETS, BUCKETS-1); digit *= 10) {
        
        // array to bucket
        for (int i = 0; i < max; i++) {
            // get the digit 0-9
            int dig = (array [i] / digit) % 10;
#ifdef DEBUG
            if (array [i] % 2 == 0) {
                // add to bucket and increment count
                int counter = bucket [dig][max];
                bucket [dig][counter] = array [i];
                counter++;
                bucket [dig][max] = counter;
                array [i] = -1;
            }
#else
            if (array [i] % 2 == 0) {
                // .. alternative entry
                bucket[dig][bucket[dig][max]++] = array [i];
                array [i] = -1;
            }
#endif
        }
        // bucket to array
        int idx = 0;
        for (int x = 0; x < BUCKETS; x++) {
            for (int y = 0;  y < bucket [x][max]; y++) {
                while (array [idx] != -1) idx++;
                array [idx++] = bucket [x][y];
            }
            // reset the internal bucket counters
            bucket [x][max] = 0;
        }
    }
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

    const int SZ = 25;
    int* array1 = makeIntArray (array1, SZ);// Для упражнения №1
    int* array2 = makeIntArray (array2, SZ);// Для упражнения №2
    fillIntRandom (array1, SZ, 40);
    memcpy (array2, array1, SZ * sizeof (int));

    // Урок 7. Сложные сортировки массивов. Упражнение №1
    puts ("Lesson 7. Sorting arrays.\n");
    printIntArray (array1, SZ, 3);
    quickSortPlus (array1, 0, SZ - 1);
    puts ("\nExercise #1; qsort+:");
    printIntArray (array1, SZ, 3);
    // Урок 7. Сложные сортировки массивов. Упражнение №2
    puts ("\nExercise #2; bucket sort:");
    bucketSort (array2, SZ);
    printIntArray (array2, SZ, 3);

    // garbage collection
    free (array1);
    free (array2);

    // return o.k.
    return EXIT_SUCCESS;
}