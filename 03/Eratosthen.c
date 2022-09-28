// Решето Эратосфена - алгоритм определения простых чисел
// Оптимизированный вариант

#define _CRT_SECURE_NO_WARNINGS // для использования scanf

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (void) {

    // указатель на массив
    int *array, count, value;

    // число
    unsigned number; 

    // русский язык в консоли
    setlocale(LC_ALL, "");

    // обработка ввода
    printf("enter a positive number: ");
    if (scanf("%u", &number) == 0 || !(number > 0)) {
        // fseek(stdin, 0, SEEK_END);
        printf("value input error");
        return EXIT_FAILURE;
    }

    array = malloc((number + 1) * sizeof(int));
    // заполение, начиная с 0
    for (count = 0; count <= number; count++) {
        array [count] = count;
        printf("%i ", array [count]);
    }
    
    // Вторым элеиентом является единица, которую не считют простым числом, 
    //  поэтому обнуляем значение
    array [1] = 0;
    // Начинаем с 3-го элемента
    count = 2;
    // Сравнение имеет смысл ДО квадратного корня из number
    while ((double) count < sqrt (number)) {
        // Если значение ячейки до этого не было обнулено,
        //  то в этой ячейке содержится просто число.
        if (array[count] != 0) {
            // первое кратное ему вычислем как квадрат значения
            value = count * count;
            while (value <= number) {
                // это число составное, поэтому меняем его на 0
                array [value] = 0;
                // переходим к следующему числу, которое кратно count,
                //  т.е. оно на count больше
                value += count;
            }
        }
    count +=1;
    }

    // Результат
    printf("\n");
    for (count = 0; count <= number; count++) {
        if (array [count])
            printf ("%i ", array [count]);
    }

    // главное -> не забыть (!)
    free(array);

    return EXIT_SUCCESS;
}