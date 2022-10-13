// *** Урок 9. Стеки, очереди и списки.

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>  // Для setlocale (LC_ALL, "")
#include <stdbool.h> // Для bool
#include <stdint.h>  // Для uint32_t

//#define DEBUG

/* 
 * 1.Описать очередь с приоритетным исключением
 */

typedef struct {
    int pr;
    int dat;
} tNode;

typedef struct {
    int SZ;
    tNode* arr;
    int tail;
    int items;
} tQueue;

// memory allocation
tQueue* makeQueue (tQueue* qPtr, const int SIZE) {

    qPtr        = (tQueue*) malloc (sizeof (tQueue));
    qPtr->arr   = (tNode*) calloc (SIZE, sizeof (tNode));
    qPtr->SZ    = SIZE;

    qPtr->tail  = 0;
    qPtr->items = 0;

    // for (int i = 0; i < SIZE; ++i)
    //     qPtr->arr [i] = NULL;

    // return
    return qPtr;
} // makeQueue

// garbage collection
void freeQueue (tQueue* qPtr) {
    free (qPtr->arr);
    free (qPtr);
} // freeQueue

// adding a node to the queue
bool insertNode (tQueue* qPtr, int pr, int dat) {

    if (qPtr->items >= qPtr->SZ) {
        puts ("Queue is full!");
        return false;
    }
    tNode node;
    node.pr  = pr;
    node.dat = dat;
    qPtr->arr [qPtr->tail++] = node;
    qPtr->items++;

    // return
    return true;
} // insertNode

// retrieving a node from a queue
int removeNode (tQueue* qPtr) {

    if (qPtr->items == 0) {
        puts ("Queue is empty\n");
        return -1;
    }

    // нахождение узла с наибольшим приоритетом
    int max = qPtr->arr [0].pr;
    int idx = 0;
    for (int i = 1; i < qPtr->items; ++i) {
        if (qPtr->arr [i].pr > max) {
            max = qPtr->arr [i].pr;
            idx = i;
        }
    }

    // для очереди с приоритетным исключением нет смысла хранить сохранять порядок элементов,
    //  поэтому переносим последний элемент на место извлекаемого
    tNode tmp = qPtr->arr [idx];
    int result = tmp.dat;
    qPtr->arr [idx] = qPtr->arr [--qPtr->tail];

    // имеет смысл при сохранении порядка элементов
    // while (idx < qPtr->items) {
    //    qPtr->arr [idx] = qPtr->arr[idx + 1];
    //    idx++;
    // }

    qPtr->items--;

    // return
    return result;
} // removeNode


/* 
 * 2.Реализовать перевод из десятичной в двоичную систему счисления с использованием стека.
 */

#define T uint32_t

typedef struct {
    int SZ;
    T* arr;
    int cursor;
} tStack;

// memory allocation
tStack* makeStack (tStack* sPtr, const int SIZE) {

    sPtr      = (tStack*) malloc (sizeof (tStack));
    sPtr->arr = (T*) calloc (SIZE, sizeof (T));
    sPtr->SZ  = SIZE;
    sPtr->cursor = -1;

    for (int i = 0; i < SIZE; ++i)
        sPtr->arr [i] = NULL;

    // return
    return sPtr;
} // makeStack

// garbage collection
void freeStack (tStack* sPtr) {
    free (sPtr->arr);
    free (sPtr);
} // freeStack

// pushStack
bool pushStack (tStack* sPtr, T data) {
    
    if (sPtr->cursor >= sPtr->SZ) {
        puts ("Stack overflow\n");
        return false;
    }
    // else
    sPtr->arr [++sPtr->cursor] = data;

    //return
    return true;
} // pushStack

// popStack
T popStack (tStack* sPtr) {

    if (sPtr->cursor <= -1) {
        puts ("Stack is empty\n");
        return -1;
    }
    // else
    // return
    return sPtr->arr [sPtr->cursor--];
} // popStack

// translation from the decimal number [num] system to a calculus system with a different base [notation].
bool dec2some (uint32_t num, const uint32_t notation, char* result)
{
    const char digs [] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    if (notation < 2 || notation > 36) {
        puts ("wrong notation!\n");
        return false;
    }
    tStack* st = makeStack (st, 100);
    // поразрядное помещение в стек (с требуемым основанием)
    while (num) {
        pushStack (st, num % notation);
        num /= notation;
    }
    // поразрадное извлечение из стека (начиная со старших разрядов)
    while (st->cursor > -1)
        sprintf (result, "%s%c", result, digs [popStack (st)]);

    // garbage collection
    freeStack (st);

    // return
    return true;
} // dec2some

// Функция, вызываемая при завершении работы
void endFunction (void)
{   
    // Вывод сообщения о завершении работы
    puts ("\nthe work is completed!");
}

// *** main
int main(void) {

    // Русский язык в консоли
    setlocale(LC_ALL, "");

    // Регистрация функции, которая будет вызвана, при нормальном завершении работы.
    if (atexit (endFunction)) {
        // Проверка регистрации функции endFunction
        puts ("post- function registration error!");
    }

    // Урок 9. Стеки, очереди и списки
    puts ("Lesson 9. Stacks, queues and Lists.\n");

    // Упражнение №1
    puts ("Exercise #1, queue with priority retrieving:");
    tQueue* q = makeQueue (q, 20);

    insertNode (q, 3, 3);
    insertNode (q, 4, 4);
    insertNode (q, 2, 2);
    insertNode (q, 0, 0);
    insertNode (q, 1, 1);
    printf ("%d ", removeNode (q));
    printf ("%d ", removeNode (q));
    printf ("%d ", removeNode (q));
    printf ("%d ", removeNode (q));
    printf ("%d ", removeNode (q));

    // garbage collection
    freeQueue (q);

    // Упражнение №2
    puts ("\n\nExercise #2, translation from the dec using a stack:");
    const int src = 61; // наглядно для HEX
    const int len = 35;
    char bin [len], hex [len];
    bin[0] = '\0', hex[0] = '\0';

    if (dec2some (src, 2, bin) == true &&
        dec2some (src, 16, hex)== true)
        printf ("DEC :%d   BIN :%s   HEX :%s\n", src, bin, hex);

    // return o.k.
    return EXIT_SUCCESS;
}