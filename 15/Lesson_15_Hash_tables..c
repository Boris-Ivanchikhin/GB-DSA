// *** Урок 15. Хеш-таблицы

#include <locale.h>  // Для setlocale (LC_ALL, "")
//#include <math.h>
//#include <time.h>
//#include <stdbool.h> // Для bool

#include "../lib_arrays.h"

//#define DEBUG

/*
 * 1.Реализовать простейшую хеш-функцию. 
 *   На вход функции подается строка, на выходе сумма кодов символов.
 */

// Hash sum
unsigned int hashSum (const char* str) {
    unsigned int hash = 0, c = 0;
    while (c = (unsigned char) *str++) hash += c;
    return hash;
} // hashSum

// Hash FAQ6
unsigned int HashFAQ6 (const char * str) {
    unsigned int hash = 0;
    for (; *str; str++)
    {
        hash += (unsigned char)(*str);
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
} // HashFAQ6

// Hash Rot13
unsigned int HashRot13 (const char * str) {
    unsigned int hash = 0;
    for (; *str; str++)
    {
        hash += (unsigned char)(*str);
        hash -= (hash << 13) | (hash >> 19);
    }
    return hash;
} // HashRot13

// Hash Ly
unsigned int HashLy (const char * str) {
    unsigned int hash = 0;
    for (; *str; str++)
        hash = (hash * 1664525) + (unsigned char)(*str) + 1013904223;
    return hash;
} // HashLy

// Hash Rs
unsigned int HashRs (const char * str) {
    static const unsigned int b = 378551;
    unsigned int a = 63689, hash = 0;
    for (; *str; str++)
    {
        hash = hash * a + (unsigned char)(*str);
        a *= b;
    }
    return hash;
} // HashRs

/*
 * 2.Имеются монеты номиналом 50, 10, 5, 2, 1 коп. 
 *   Напишите функцию которая минимальным количеством монет наберет сумму 98 коп. 
 *   Для решения задачи используйте “жадный” алгоритм.
 */

int* calcCounts (int* coins, const int size, int sum) {
    int* counts = malloc (size * sizeof (int));
    clearArray (counts, size);
    int purpose = 0;
    for (int i  = 0; i < size; ++i) {
        int coin= coins [i];
        while (purpose  <  sum) {
            if (purpose +  coin <= sum) {
                purpose += coin;
                counts [i]++;
            }
            else break;
        }
    }
    // return
    return (sum == purpose) ? counts : NULL;
} // calcCounts

#define HT_SIZE 10

// hash
int hash (T value) {
    return value % HT_SIZE;
} // hash

// Insert
void htInsert (OneLinkList* hashTable [], T value) {
    int htIndex = hash (value);
    if (htIndex < HT_SIZE)
        pushStack (hashTable [htIndex], value);
} // htInsert

// Print
void htPrint (OneLinkList* hashTable []) {
    for (int i = 0; i < HT_SIZE; ++i)
        printOneLinkList (hashTable [i]);
    printf ("\n");
} // htPrint

// Функция, вызываемая при завершении работы
void endFunction (void)
{
    // Вывод сообщения о завершении работы
    puts ("\nthe work is completed!");
}

// main
int main (void) {

    // Русский язык в консоли
    setlocale (LC_ALL, "");

    // Регистрация функции, которая будет вызвана, при нормальном завершении работы.
    if (atexit (endFunction)) {
        // Проверка регистрации функции endFunction
        puts ("post- function registration error!");
    }

    // Урок 15. Хеш-таблицы
    puts ("Lesson 15. Hash tables.\n");

    // Хэш таблица
    puts ("Demo:");
    OneLinkList* hashTable [HT_SIZE];
    for (int i = 0; i < HT_SIZE; i++)
        hashTable [i] = makeOneLinkList (hashTable [i]);

    // Демо работы хэш-таблицы
    for (int i = 'a'; i <= 'a'+25; i++)
        htInsert (hashTable, (T) i);
    htPrint (hashTable);

    // garbage collection
    for (int i = 0; i < HT_SIZE; i++)
        freeOneLinkList (hashTable [i]);

    // Упражнение №1
    puts  ("\nExercise #1: implementation of the simplest hash functions.\n");
    const char* Demo = "hash-func";
    printf ("Hash (+) for \"%s\"     -> %u\n", Demo, hashSum (Demo));
    printf ("Hash (FAQ6) for \"%s\"  -> %u\n", Demo, HashFAQ6 (Demo));
    printf ("Hash (Rot13) for \"%s\" -> %u\n", Demo, HashRot13 (Demo));
    printf ("Hash (Ly) for \"%s\"    -> %u\n", Demo, HashLy (Demo));
    printf ("Hash (Rs) for \"%s\"    -> %u\n", Demo, HashRs (Demo));

    // Упражнение №2
    puts  ("\nExercise #2: demo of the “greedy” algorithm.\n");
    int coins [] = {50, 10, 5, 2, 1}, sum = 98;
    printf ("Coins: ");
    printIntArray (coins, 5, 2);
    printf ("Purpose: %d\n", sum);

    int*counts = calcCounts (coins, 5, sum);
    if (counts) {
        for (int i = 0; i < 5; i++) {
            if (counts [i])
                printf ("%2d -> %2d pieces\n", coins [i], counts [i]);
        }
    } else
        puts ("the goal cannot be achieved");

    // return o.k.
    return EXIT_SUCCESS;
} // main
