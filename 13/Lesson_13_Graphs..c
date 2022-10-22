// *** Урок 13. Графы

#include <locale.h>  // Для setlocale (LC_ALL, "")
//#include <math.h>
//#include <time.h>
#include <stdbool.h> // Для bool

#include "../lib_arrays.h"

#define DEBUG

/*
 * 1.Реализовать обход графа в глубину с использованием стека.
 */

// getNextVertex
int getNextVertex (int* aGraph, bool* visited, const int numVertex, const int size) {
    // анализ строки матрицы [aGrapth] под номером [numVertex]
    for (int i = 0; i < size; i++) {
        // проверка связи
        int link = *(aGraph + numVertex*size + i);
        if (link == 1 && !(*(visited + i)))
            return i;
    }
    // return
    return -1;
} // getNextVertex

// dippingGraph
void dippingGraph (int* aGraph, const int size) {
    const int dec_a = 'a';
    OneLinkList* stack = makeOneLinkList (stack);
    // массив посещенных вершин
    bool visited [size];
    // стартовая вершина [=='a'] отмечается как посещенная
    visited [0] = true;
    printf ("vertex -> %c[1] ", dec_a);
    pushStack (stack, 0);

    while (stack->head) {
        // поиск следующего свободного перехода
        int numVertex = getNextVertex (aGraph, visited, stack->head->dat, size);
        // если свободного перехода нет, то вершина выталкивается из стека,
        //  т.е. происходит возврат на одну вершину назад
        if (numVertex == -1) {
            popStack (stack);
            continue;
        }
        // найден свободный переход
        visited [numVertex] = true;
        printf ("%c[%d] ", dec_a + numVertex, numVertex + 1);
        pushStack (stack, numVertex);
    } // while (stack->head) {
    printf ("\n");
    freeOneLinkList (stack);
} // dippingGraph

/*
 * 2.Моделируем робот поисковой системы. 
 *   Дан готовый простой граф с циклическими связями. 
 *   Нужно обойти этот граф двумя способами и подсчитать 
 *   количество ссылок на каждый из узлов графа (полустепень захода). 
 */

// вершина
typedef struct {
    char name;
    int  edges;
} Vertex;

// initVertex
void initVertex (Vertex* array, const int SIZE) {
    for (int i = 0; i < SIZE; ++i) {
        array [i].edges = 0;
        array [i].name  = 'a' + i;
    }
} // initVertex

// print Vertex
void printVertex (Vertex* array, const int SIZE) {
    for (int i = 0; i < SIZE; ++i) {
        printf (" %c->%d", array [i].name, array [i].edges);
        if (i != SIZE - 1)
            printf (",");
    }
    printf ("\n");
} // printVertex

// sorting (n decreasing order) an array of vertexes
void sortVertex (Vertex* array, const int SIZE) {
    Vertex temp;
    int i, pos;
    for (int i = 1; i < SIZE; ++i) {
        temp.name  = array[i].name;
        temp.edges = array[i].edges;
        pos = i - 1;
        while (pos >= 0 && array [pos].edges < temp.edges) {
            array [pos + 1].name  = array [pos].name;
            array [pos + 1].edges = array [pos].edges;
            pos--;
        }
        array [pos + 1].name  = temp.name;
        array [pos + 1].edges = temp.edges;
    }
} // sortVertex

/*
 * 2... 
 *   обход графа рекурсивной функцией (с подсчётом только смежных со стартовой вершин).
 */

int findVertex (Vertex* countLinks, const int size, int number, bool getFree) {
    char name = 'a' + number;
    int i;
    for (i = 0; (i < size) && (countLinks [i].name != '\0'); i++)
        if (countLinks [i].name == name)
            return i;
    // return
    return (getFree && i < size) ? i : -1;
} // findVertex

// setVisited
void setVisited (Vertex* countLinks, const int size, int number) {
    char name = 'a' + number;
    int i = findVertex (countLinks, size, number, true);
    if (i != -1) countLinks [i].name = name;
} // setVisited

// isVisited
bool isVisited (Vertex* countLinks, const int size, int number) {
    int i = findVertex (countLinks, size, number, false);
    return !(i == -1);
} // isVisited

 // add 1 edge to Vertex* (link increment)
bool addEdges (Vertex* countLinks, const int size, int number) {
    int i = findVertex (countLinks, size, number, false);
    if (i == -1) return false;
    countLinks [i].edges++;
    // return
    return true;
} // addEdges

// recursive function to traverse a graph [in width]
void traverseByRec (int* aGraph, 
                    const int size,
                    Vertex* countLinks, 
                    TwoLinkList* queue,
                    int start)
{
    // 1.поиск смежных вершин, подсчет рёбер
    // 2.добавление в очередь для подсчёта их рёбер
    for (int next = 0; next < size; ++next) {
        int link = *(aGraph + start * size + next);
        if (link) {
            addEdges (countLinks, size, start);
            if (!isVisited (countLinks, size, next)) {
                setVisited (countLinks, size, next);
                enqueue (queue, next);
            }
        }
    }
    // 3.переход к следующей вершине в очереди
    if (queue->size > 0)
        traverseByRec (aGraph, size, countLinks, queue, dequeue (queue));
} // traverseByRec

// required to run recursive function
Vertex* startTraverseByRec (int* aGraph, const int size) {

    // массив Vertex'ов для подсчёта полустепеней захода
    Vertex* countLinks = (Vertex*) malloc (size * sizeof (Vertex));
    for (int i =0; i < size; ++i) {
        countLinks [i].edges = 0;
        countLinks [i].name  = '\0';
    }
    // стартовая вершина отмечается как пройденная
    setVisited (countLinks, size, 0);
    // очередь вершин для обхода
    TwoLinkList* queue = makeTwoLinkList (queue);
    // запуск рекурсии
    traverseByRec (aGraph, size, countLinks, queue,  0);
    // добавлние в итоговый результат вершин, в которые не удалось перейти
    for (int i = 0; i < size; i++) {
        if (findVertex (countLinks, size, i, false) == -1) {
            int j = findVertex (countLinks, size, i, true);
            countLinks [j].name = 'a' + i;
        }
    }
    // garbage collection
    freeTwoLinkList (queue);
    // return
    return countLinks;
} // startTraverseByRec

/*
 * 2... 
 *   обход графа по матрице смежности (с подсчётом всех вершин графа).
 *   В конце обхода вывести два получившихся списка всех узлов в порядке 
 *   уменьшения количества ссылок на них.
 */
Vertex* traverseByMatrix (int* aGraph, const int size) {
    Vertex* countLinks = (Vertex*) malloc (size * sizeof (Vertex));
    initVertex (countLinks, size);
    // полный обход матрицы смежности
    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            int value = *(aGraph + row*size + col);
            if (value && row != col)
                countLinks [row].edges++;
        }
    }
    // return
    return countLinks;
} // traverseByMatrix

#define G_SIZE 14

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

    // Урок 13. Графы
    puts ("Lesson 13. Graphs.\n");

    // Матрица смежности
    int aGraph [G_SIZE][G_SIZE] = 
        {   {0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
            {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
            {0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
            {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0},
            {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1},
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}};

    puts ("The adjacency matrix of a graph:");
    for (int i =0; i < G_SIZE; ++i)
        printIntArray (&aGraph [i], G_SIZE, 2);
    // Упражнение №1
    puts  ("\nExercise #1: traversing a graph in depth using a stack.");
    dippingGraph (&aGraph, G_SIZE);

    // Упражнение №2
    puts  ("\nExercise #2: simulation of a search engine robot.");
    
    printf ("1.by a recursive func:");
    Vertex* countLinks1 = startTraverseByRec (&aGraph, G_SIZE);
    printVertex (countLinks1, G_SIZE);
    sortVertex  (countLinks1, G_SIZE);
    printf ("        after sorting:");
    printVertex (countLinks1, G_SIZE);

    printf ("2.by adjacency matrix:");
    Vertex* countLinks2 = traverseByMatrix (&aGraph, G_SIZE);
    printVertex (countLinks2, G_SIZE);
    sortVertex  (countLinks2, G_SIZE);
    printf ("        after sorting:");
    printVertex (countLinks2, G_SIZE);

    // garbage collection
    free (countLinks1);
    free (countLinks2);

    // return o.k.
    return EXIT_SUCCESS;
} // main
