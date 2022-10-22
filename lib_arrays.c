#include "lib_arrays.h"

#define CHECK_MEM(ptr) do { \
    if (ptr == NULL) { \
        puts("memory allocation error!\nexecution aborted"); \
        abort(); \
        } \
} while(0)

// * swap
void swapInt (int *a, int *b) {

    int t = *a;
    *a = *b;
    *b = t;
}

// * fill arrays
void fillIntRandom (int* array, const int SIZE, const int BORDER) {

    srand (time (NULL));
    for (int i = 0; i < SIZE; ++i)
        *(array +i) = rand () % BORDER;
}

// * fillIntRandom2D
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

} // fillIntRandom2D

// * print array
void printIntArray (int* array, const int SIZE, const int OFFSET) {
    char format [7];

    sprintf (format, "%%%dd", OFFSET);
    for (int i = 0; i < SIZE; ++i) {
        printf (format, *(array +i));
        if (i != SIZE - 1)
            printf (",");
    }
    printf ("\n");
} // printIntArray

// * print array 2D
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
} // printIntArray2D

// * memory allocation
int* makeIntArray (int* array, const int SIZE) {
    array = calloc (SIZE, sizeof (int));
    CHECK_MEM (array);
    // return
    return array;
} // makeIntArray

// * memory allocation
int** makeIntArray2D (int** array, const int ROWS, const int COLS) {
    array = (int**) malloc (ROWS * sizeof (int*));
    CHECK_MEM (array);
    for (int i = 0; i < ROWS; ++i) {
        *(array +i) = (int*) malloc (COLS * sizeof (int));
        CHECK_MEM (array);
    }
    // return
    return array;
} // makeIntArray2D

// * Garbage collector
void freeArray2D (int** array, const int ROWS) {

    // Халява закончилась -(
    for (int i = 0; i < ROWS; i++)
        free ((int*)*(array + i));

    free (array);
} // freeArray2D

// * Clear array
void clearArray (int* iArray, const int size) {
    for (int i=0; i < size; ++i)
        iArray [i] = 0;
} // clearArray

// * memory allocation
OneLinkList* makeOneLinkList (OneLinkList* lPtr) {

    lPtr       = (OneLinkList*) malloc (sizeof (OneLinkList));
    CHECK_MEM(lPtr);
    lPtr->head = NULL;
    lPtr->size = 0;

    // return
    return lPtr;
} // makeOneLinkList

// * garbage collection
void freeOneLinkList (OneLinkList* lPtr) {

    while (lPtr != NULL && lPtr->head != NULL) {
        OneLinkNode* tmp = lPtr->head;
        lPtr->head = tmp->next;
        free (tmp);
        // lPtr->size--; смысла уже нет
    }
    if (lPtr != NULL)
        free (lPtr);
} // freeOneLinkList

// * method push (as stack)
void pushStack (OneLinkList *lPtr, T value) {

    OneLinkNode *newNode = (OneLinkNode*) malloc (sizeof (OneLinkNode));
    CHECK_MEM(lPtr);
    newNode->dat  = value;
    newNode->next = lPtr->head;
    // LIFO: ahead of the head
    lPtr->head = newNode;
    lPtr->size++;
} // pushOneLinkAsStack

// * method pop (as stack)
T popStack (OneLinkList *lPtr) {

    if (lPtr->size <= 0) {
        printf("stack is empty!\n");
        return -1;
    }
    // LIFO: head
    OneLinkNode *hNode = lPtr->head;
    T value    = hNode->dat;
    lPtr->head = hNode->next;
    lPtr->size--;
    // garbage collection
    free (hNode);
    // return
    return value;
} // popOneLinkAsStack

// * print list
void printOneLinkList (OneLinkList *lPtr) {

    if (lPtr->head == NULL)
        printf("[]");

    LIST_FOREACH(cur, lPtr) {
        printf("[%c]", cur->dat);
    }

    printf (" Size: %d \n", lPtr->size);
} // printOneLinkList

// * method find
OneLinkNode* findOneLinkList (OneLinkList *lPtr, T value) {
    if (!lPtr || !lPtr->head)
        return NULL;
    // перебор элементов списка
    LIST_FOREACH(cur, lPtr) {
        if (cur->dat == value)
            return (OneLinkNode*) cur;
        }
    // return
    return NULL;
}

// * copyOneLinkList
void copyOneLinkList (OneLinkList* _Destination, OneLinkList* _Source) {
    OneLinkNode *tmp, *prev;

    // Очистка приемника
    while (_Destination != NULL && _Destination->head != NULL) {
        tmp = _Destination->head;
        _Destination->head = tmp->next;
        free (tmp);        
    }
    _Destination->size = 0;

    if (_Source->head == NULL)
        return;
    
    // перебор элементов _Source
    LIST_FOREACH(cur, _Source) {
        if (_Source->head == cur) {
            pushStack (_Destination, cur->dat);
            prev = _Destination->head;
            continue;
        }
          // добавление нового узла в _Destination
        tmp = (OneLinkNode*) malloc (sizeof (OneLinkNode));
        tmp->dat = cur->dat;
        tmp->next = NULL;
        prev->next = tmp;
        _Destination->size++;
        // обновление ссылки на предыдущий узел
        prev = tmp;
    }
} // copyOneLinkList

// * memory allocation
TwoLinkList* makeTwoLinkList (TwoLinkList* lPtr) {

    lPtr       = (TwoLinkList*) malloc (sizeof (TwoLinkList));
    CHECK_MEM(lPtr);
    lPtr->head = NULL;
    lPtr->tail = NULL;
    lPtr->size = 0;

    // return
    return lPtr;
} // makeTwoLinkList

// * garbage collection
void freeTwoLinkList (TwoLinkList* lPtr) {

    while (lPtr != NULL && lPtr->head != NULL) {
        TwoLinkNode* tmp = lPtr->head;
        lPtr->head = tmp->next;
        //lPtr->head->prev = NULL; смысла уже нет
        free (tmp);
        //lPtr->size--; смысла уже нет
    }
    if (lPtr != NULL)
        free (lPtr);
} // freeTwoLinkList

// * method enqueue
void enqueue (TwoLinkList* lPtr, T value) {
    // новый TwoLinkNode
    TwoLinkNode *newNode = (TwoLinkNode*) malloc (sizeof (TwoLinkNode));
    CHECK_MEM(newNode);
    newNode->dat  = value;
    newNode->next = NULL;
    newNode->prev = lPtr->tail;
    // установка next для текущего tail, т.е. добавление в хвост
    if (lPtr->tail != NULL) {
        lPtr->tail->next = newNode;
    }
    // установка head, если список пуст
    if (lPtr->head == NULL) {
        lPtr->head = newNode;
    }
    // установка текущего tail, т.е. добавление в хвост
    lPtr->tail = newNode;
    lPtr->size++;
} // enqueue

// * method dequeue
T dequeue (TwoLinkList *lPtr) {

    if (lPtr->size <= 0) {
        printf ("queue is empty \n");
        return -1;
    }
    // FIFO: head
    TwoLinkNode* hNode = lPtr->head;
    T value    = hNode->dat;
    lPtr->head = hNode->next;
    // обнуление prev у нового элемента head (начало очереди)
    if (lPtr->head)
        lPtr->head->prev = NULL;
    // если извлекаемый элемент был хвостом очереди
    if (hNode == lPtr->tail)
        lPtr->tail = NULL;
    // декремент кол-ва элементов очереди
    lPtr->size--;
    // garbage collection
    free (hNode);
    // return
    return value;
} // dequeue

// * method find
TwoLinkNode* findTwoLinkList (TwoLinkList *lPtr, T value) {
    if (!lPtr || !lPtr->head)
        return NULL;
    // перебор элементов списка
    LIST_FOREACH(cur, lPtr) {
        if (cur->dat == value)
            return (TwoLinkNode*) cur;
        }
    // return
    return NULL;
} // findTwoLinkList