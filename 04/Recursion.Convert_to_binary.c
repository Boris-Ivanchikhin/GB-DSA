// 1.Реализовать функцию перевода чисел из десятичной системы в двоичную, используя рекурсию.

#define _CRT_SECURE_NO_WARNINGS // Для использования scanf

#include <stdio.h>
#include <stdlib.h> // Для exit () и atexit ()
#include <locale.h>

char *sBinResult = NULL;

// Функция, вызываемая при завершении работы
void endFunction (void)
{   
    // Не забыть почистить буфер (!)
    if (sBinResult != NULL) {
        free (sBinResult);
    }

    // Вывод сообщения о завершении работы
    puts ("the work is completed!");
}

// Функция ввода натурального числа
int getNatural () {
    unsigned value; 

    // Обработка ввода
    printf("enter a natural number: ");
    if (scanf("%u", &value) == 0 || !(value > 0)) {
        // fseek(stdin, 0, SEEK_END);
        printf("value input error!");
        exit (EXIT_FAILURE);
    }

    return value;
}

// Рекурсивное преобразование DEC->BIN
void covertToBin (const int number) {
    
    char *newResult = malloc(sizeof(*sBinResult) + 1);
    int binDigit =  number % 2;
    int nextLoop = number / 2;

    // Собираем строку из 0 и 1
    if (sBinResult != NULL) {
        sprintf (newResult, "%d%s", binDigit, sBinResult);
        free (sBinResult);
    } else {
        sprintf (newResult, "%d", binDigit);
    }
    
    // Строка-результат всегда в sBinResult
    sBinResult = newResult;
    
    // Собственно рекурсия при условии: number/2 > 0
    if (nextLoop) {
        covertToBin (nextLoop);
    }
}

// main ...
int main (void) {

    // Русский язык в консоли
    setlocale(LC_ALL, "");

    // Регистрация функции, которая будет вызвана, при нормальном завершении работы.
    if (atexit (endFunction)) {
        // Проверка регистрации функции endFunction
        puts ("function registration error!");
    }

    // Преобразование. Результат в sBinResult.
    covertToBin (getNatural ());

    // Результат
    puts (sBinResult);

    return EXIT_SUCCESS;
}