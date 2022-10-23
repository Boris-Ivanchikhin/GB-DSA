#ifndef LIB_ARRAYS_H
#define LIB_ARRAYS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>  // Для uint32_t
#include <time.h>
//#include <stdbool.h>
//#include <stdarg.h>

// * swap
void swapInt (int *a, int *b);

// * fill arrays
void fillIntRandom (int* array, const int SIZE, const int BORDER);
void fillIntRandom2D (int** array, const int ROWS, const int COLS, const int BORDER);

// * print arrays
void printIntArray (int* array, const int SIZE, const int OFFSET);
void printIntArray2D (int** array, const int ROWS, const int COLS, const int OFFSET);

// * memory allocation
int* makeIntArray (int* array, const int SIZE);
int** makeIntArray2D (int** array, const int ROWS, const int COLS);

// * Garbage collector
void freeArray2D (int** array, const int ROWS);

// * Clear array
void clearArray (int* iArray, const int size);

// * Lists/Stacks

#define T char

// * OneLinkNode
typedef struct OneLinkNode {
    T dat;
    struct OneLinkNode *next;
} OneLinkNode;

// * OneLinkNode
typedef struct {
    OneLinkNode *head;
    uint32_t size;
} OneLinkList;

// * LIST_FOREACH
#define LIST_FOREACH(cur, list) \
    OneLinkNode* cur = list->head; \
    for (OneLinkNode* _node = (OneLinkNode*)list->head; \
        _node != NULL; \
        cur = _node = _node->next)

// * memory allocation
OneLinkList* makeOneLinkList (OneLinkList* lPtr);

// * garbage collection
void freeOneLinkList (OneLinkList* lPtr);

// * method push (as stack)
void pushStack (OneLinkList *lPtr, T value);

// * method pop (as stack)
T popStack (OneLinkList *lPtr);

// * print list
void printOneLinkList (OneLinkList *lPtr);

// * copyOneLinkList
void copyOneLinkList (OneLinkList* _Destination, OneLinkList* _Source);

// * method find
OneLinkNode* findOneLinkList (OneLinkList *lPtr, T value);

// * method delete
void delOneLinkList (OneLinkList *lPtr, T value);

// * TwoLinkNode
typedef struct TwoLinkNode {
    T dat;
    struct TwoLinkNode *next;
    struct TwoLinkNode *prev;
} TwoLinkNode;

typedef struct {
    struct TwoLinkNode *head;
    struct TwoLinkNode *tail;
    uint32_t size;
} TwoLinkList;

// * memory allocation
TwoLinkList* makeTwoLinkList (TwoLinkList* lPtr);

// * method enqueue
void enqueue (TwoLinkList* lPtr, T value);

// * method dequeue
T dequeue (TwoLinkList *lPtr);

// * method find
TwoLinkNode* findTwoLinkList (TwoLinkList *lPtr, T value);

#endif // LIB_ARRAYS_H