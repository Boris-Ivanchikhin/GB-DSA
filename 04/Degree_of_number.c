// 2.Реализовать функцию возведения числа [a] в степень [b]:
//      - Рекурсивно;
//      - Рекурсивно, используя свойство чётности степени (то есть, если степень, 
//          в которую нужно возвести число, чётная, основание возводится в квадрат, а показатель делится на два, 
//          а если степень нечётная - результат умножается на основание, а показатель уменьшается на единицу).

#define _CRT_SECURE_NO_WARNINGS // Для использования scanf

#include <stdio.h>
#include <stdlib.h> // Для exit () и atexit ()
#include <locale.h>
#include <time.h>   // Для clock_t, clock(), CLOCKS_PER_SEC и т.д.

// Функция, вызываемая при завершении работы
void endFunction (void)
{   
    // Вывод сообщения о завершении работы
    puts ("\nthe work is completed!");
}

// Функция ввода [double] X и [long] N
void getNumbers (double *x, long *n) {

    // Обработка ввода
    printf("enter the numbers [double] X and [long] N: ");
    if (scanf ("%lf %ld", x, n) != 2) {
        // fseek(stdin, 0, SEEK_END);
        puts ("value input error!");
        exit (EXIT_FAILURE);
    }
}

/* 
    Степень числа: простая рекурсия
*/
double stdDegree (double x, long n) {

    if (n == 0) return 1.0;
    if (n <  0) return 1.0 / (x * stdDegree (1.0 / x, n + 1));

    return x * stdDegree (x, n - 1);
}

/*
    Степень числа: оптимизированная рекурсия
*/
double smartDegree (double x, long n) {

    if (n == 0) return 1.0;
    if (n <  0) return smartDegree (1.0 / x, -n);
    if (n %  2) return x * smartDegree (x, n - 1);

    return smartDegree (x * x, n / 2);
}

// main ...
int main (void) {
    double x, res, time_spent = 0.0;
    long n;

    // Русский язык в консоли
    setlocale(LC_ALL, "");

    // Регистрация функции, которая будет вызвана, при нормальном завершении работы.
    if (atexit (endFunction)) {
        // Проверка регистрации функции endFunction
        puts ("post- function registration error!");
    }

    // Ввод
    getNumbers (&x, &n);

    clock_t start, end;

    // Простая рекурсия
    start = clock ();
    res   = stdDegree (x, n);
    end   = clock ();

    printf("\nsimple recursion: %16.16lf\n", res);
    printf("execution time: %fms.\n", (double)(end - start));

    // Оптимизированная рекурсия
    start = clock ();
    res   = smartDegree (x, n);
    end   = clock ();

    printf("\nsmart recursion: %16.16lf\n", res);
    printf("execution time: %fms.\n", (double)(end - start));

    return EXIT_SUCCESS;
}