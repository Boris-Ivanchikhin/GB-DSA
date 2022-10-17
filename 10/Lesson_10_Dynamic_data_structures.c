// *** Урок 10. Динамические структуры данных

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>  // Для setlocale (LC_ALL, "")
#include <stdbool.h> // Для bool
#include <stdint.h>  // Для uint32_t
#include <string.h>  // Для strlen

// check script
#define CHECK_MEM(ptr) do { \
    if (ptr == NULL) { \
        puts("memory allocation error!\nexecution aborted"); \
        abort(); \
        } \
} while(0)

//#define DEBUG

/* 
 * 1.Написать программу, которая определяет, является ли введенная скобочная последовательность правильной. 
 *   Примеры правильных скобочных выражений: (), ([])(), {}(), ([{}]), 
 *   неправильных — )(, ())({), (, ])}), ([(]) для скобок [,(,{. 
 *   Например: (2+(2*2)) или [2/{5*(4+7)}]
 */

#define T char

typedef struct OneLinkNode {
    T dat;
    struct OneLinkNode *next;
} OneLinkNode;

typedef struct {
    OneLinkNode *head;
    uint32_t size;
} OneLinkList;

#define LIST_FOREACH(cur, list) \
    OneLinkNode* cur = list->head; \
    for (OneLinkNode* _node = list->head; \
        _node != NULL; \
        cur = _node = _node->next)

// memory allocation
OneLinkList* makeOneLinkList (OneLinkList* lPtr) {

    lPtr       = (OneLinkList*) malloc (sizeof (OneLinkList));
    CHECK_MEM(lPtr);
    lPtr->head = NULL;
    lPtr->size = 0;

    // return
    return lPtr;
} // makeOneLinkList

// garbage collection
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

// method push (as stack)
void pushOneLinkAsStack (OneLinkList *lPtr, T value) {

    OneLinkNode *newNode = (OneLinkNode*) malloc (sizeof (OneLinkNode));
    CHECK_MEM(lPtr);
    newNode->dat  = value;
    newNode->next = lPtr->head;
    // LIFO: ahead of the head
    lPtr->head = newNode;
    lPtr->size++;
} // pushOneLinkAsStack

// method pop (as stack)
T popOneLinkAsStack (OneLinkList *lPtr) {

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

// print list
void printOneLinkList (OneLinkList *lPtr) {

    if (lPtr->head == NULL)
        printf("[]");

    LIST_FOREACH(cur, lPtr) {
        printf("[%c]", cur->dat);
    }

    printf (" Size: %d \n", lPtr->size);
}

// check the correctness of the expression with braces
bool bracesCheck (char* expression, char *error) {

    char
        openBrackets [] = "({[", 
        closBrackets [] = ")}]";
    OneLinkList *stack = makeOneLinkList (stack);

    int index = 0;
    while (expression [index] != '\0') {
        // Строка анализируется слева - направо. 
        //  При нахождении открывающей скобки -> соответсвующая ей закрывающая скобка помещается в стек.
        for (int i = 0; i < strlen (openBrackets); ++i) {
            if (expression [index] == openBrackets [i])
                pushOneLinkAsStack (stack, closBrackets [i]);
        }
        // Теперь, если найдена закрывающая скобка, то ровно такая же скобка должна быть извлечена из стека!
        for (int i = 0; i < strlen (closBrackets); ++i) {
            if (expression [index] == closBrackets [i]) {
                if ((stack->size == 0) || (expression [index] != popOneLinkAsStack (stack))) {
                    sprintf (error, "symbol \"%c\" is required, position %d", openBrackets [i], index + 1);
                    freeOneLinkList (stack);
                    return false;
                }
            }
        }
        index++;
    } // while (expression [index] != '\0')

    // Все открывающиеся скобки должны были закрыться
    if (stack->size > 0) {
        sprintf (error, "probably a symbol \"%c\" is required", popOneLinkAsStack (stack));
        freeOneLinkList (stack);
        return false;
    }

    // return o.k.
    return true;
} // bracesCheck


/* 
 * 2.Создать функцию, копирующую односвязный список (без удаления первого списка).
 */

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
            pushOneLinkAsStack (_Destination, cur->dat);
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


/* 
 * 3.Реализуйте алгоритм, который определяет, отсортирован ли связный список.
 */

bool listSorted (OneLinkList *lPtr) {
    bool fDecreasing = true, fIncreasing = true;

    if (lPtr->size <= 1)
        return true;

    // перебор элементов списка
    LIST_FOREACH(cur, lPtr) {
        // последний элемент
        if (cur->next == NULL)
            break;
        // текущий меньше следующего
        fDecreasing = (cur->dat < cur->next->dat) ? false : fDecreasing;
        // текущий больше следующего
        fIncreasing = (cur->dat > cur->next->dat) ? false : fIncreasing;
        // уже известно что список НЕ отсортирован по обоим критериям
        if (!fDecreasing && !fIncreasing)
            return false;
        }
    // return
    return fDecreasing || fIncreasing;
}


// Функция, вызываемая при завершении работы
void endFunction (void)
{   
    // Вывод сообщения о завершении работы
    puts ("\nthe work is completed!");
}

// *** main
int main (void) {

    // Русский язык в консоли
    setlocale(LC_ALL, "");

    // Регистрация функции, которая будет вызвана, при нормальном завершении работы.
    if (atexit (endFunction)) {
        // Проверка регистрации функции endFunction
        puts ("post- function registration error!");
    }

    // Урок 10. Динамические структуры данных
    puts ("Lesson 10. Dynamic data structures.\n");

    // Упражнение №1
    puts ("Exercise #1, check the correctness of the expression:\n");
    char err [100];
    char *str1 = "([])()", *str2 = "{}()",    *str3 = "([{}])", 
         *str4 = "())({)", *str5 = "(, ])})", *str6 = "([(])",
         *str7 = "{ ( [ {} [] () ] ( }",      *str8 = "[2 / {5 * (4 + 7)}]";

    printf("src: \"%s\" -> res: %s.\n", str1, bracesCheck (str1, err) ? "ok" : err);
    printf("src: \"%s\" -> res: %s.\n", str2, bracesCheck (str2, err) ? "ok" : err);
    printf("src: \"%s\" -> res: %s.\n", str3, bracesCheck (str3, err) ? "ok" : err);
    printf("src: \"%s\" -> res: %s.\n", str4, bracesCheck (str4, err) ? "ok" : err);
    printf("src: \"%s\" -> res: %s.\n", str5, bracesCheck (str5, err) ? "ok" : err);
    printf("src: \"%s\" -> res: %s.\n", str6, bracesCheck (str6, err) ? "ok" : err);
    printf("src: \"%s\" -> res: %s.\n", str7, bracesCheck (str7, err) ? "ok" : err);
    printf("src: \"%s\" -> res: %s.\n", str8, bracesCheck (str8, err) ? "ok" : err);

    // Упражнение №2
    puts ("\nExercise #2,\n\
    create a function that copies a singly linked list\n\
    (without deleting the source list):\n");

    OneLinkList* src = makeOneLinkList (src);
    for (int charCode = 106; charCode >= 97; --charCode)
        pushOneLinkAsStack (src, (char) charCode);
    printf ("Src -> ");
    printOneLinkList (src);

    OneLinkList* dst = makeOneLinkList (dst);
    copyOneLinkList (dst, src);
    printf ("Dst -> ");
    printOneLinkList (dst);

    // Упражнение №3
    puts ("\nExercise #3, determine whether the linked list is sorted:");
    
    printf ("\nList1 -> ");
    printOneLinkList (src);
    printf ("list1 is %s.\n", listSorted (src) ? "sorted" : "not sorted");
    
    pushOneLinkAsStack (src, 'z');
    printf ("\nList2 -> ");
    printOneLinkList (src);
    printf ("list2 is %s.\n", listSorted (src) ? "sorted" : "not sorted");

    // garbage collection
    freeOneLinkList (src);
    freeOneLinkList (dst);

    // return o.k.
    return EXIT_SUCCESS;
}