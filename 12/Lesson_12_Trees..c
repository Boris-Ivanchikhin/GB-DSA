// *** Урок 12. Деревья

#include <locale.h>  // Для setlocale (LC_ALL, "")
#include <math.h>
#include <time.h>
#include <stdbool.h> // Для bool

#include "../lib_trees.h"

#define DEBUG

/*
 * 1.Написать функцию проверяющую является ли переданное в неё бинарное дерево сбалансированным
 *    и написать программу, которая:
 *   - создаст 50 деревьев по 10'000 узлов и заполнит узлы случайными целочисленными значениями;
 *   - рассчитает, какой процент из созданных деревьев является сбалансированными.
 */

#define TREES 50
#define TREES_SZ 10000

// fillBinTree
void fillBinTree (BinTreeNode* tPtr, const int count) {
    for (int i = 0; i < count; ++i)
        insBinTree (tPtr, rand () % 1000);
} // fillBinTree

// heightTree
int heightTree (BinTreeNode *tPtr) {
    if (tPtr == NULL)
        return 0;
    int hLeft = 0, hRight = 0;
    if (tPtr->left  != NULL) hLeft  = heightTree (tPtr->left);
    if (tPtr->right != NULL) hRight = heightTree (tPtr->right);
    // return
#ifdef DEBUG
    int res = 1 + ((hLeft > hRight) ? hLeft : hRight);
    return res;
#else
    return 1 + (hLeft > hRight) ? hLeft : hRight;
#endif
} // heightTree

// проверяет является ли переданное в неё бинарное дерево сбалансированным
bool checkBalanceTree (BinTreeNode *tPtr) {
#ifdef DEBUG
    int hLeft  = heightTree (tPtr->left),
        hRight = heightTree (tPtr->right);
    int hDelta = hLeft - hRight;
#else
    int hDelta = heightTree (tPtr->left) - heightTree (tPtr->right);
#endif
    return abs (hDelta) <= 1;// ? true : false);
} // checkBalanceTree

/*
 * 2. Написать рекурсивную функцию бинарного поиска в дереве хранящемся в узлах, а не в массиве.
 */

BinTreeNode* findNodeInTree (BinTreeNode *tPtr, int data) {
    BinTreeNode* res = NULL;

    if (tPtr == NULL || tPtr->key == data)
        res = tPtr;
    else if (data < tPtr->key)
        return findNodeInTree (tPtr->left, data);
    else
        return findNodeInTree (tPtr->right, data);
    // return
    return res;
} // findNodeInTree

// Функция, вызываемая при завершении работы
void endFunction (void)
{
    // Вывод сообщения о завершении работы
    puts ("\nthe work is completed!");
} // endFunction

// main
int main (void) {

    // Русский язык в консоли
    setlocale (LC_ALL, "");

    // Регистрация функции, которая будет вызвана, при нормальном завершении работы.
    if (atexit (endFunction)) {
        // Проверка регистрации функции endFunction
        puts ("post- function registration error!");
    }

    // Урок 12. Деревья.
    puts ("Lesson 12. Trees.\n");

    // Упражнение №1
    puts  ("Exercise #1: check the balancing of binary trees.");
    int isBalanced = 0;
    srand (time (NULL));
    BinTreeNode* trees [TREES];
    for (int i = 0; i < TREES; ++i) {
        BinTreeNode *root = insBinTree (NULL, rand () % 500);
        trees [i] = root;
        fillBinTree (root, TREES_SZ);
        isBalanced += (checkBalanceTree (root) == true) ? 1 : 0;
    }
    printf ("total trees: %d, balanced: %d [%d%%]\n\n", TREES, isBalanced, isBalanced * 100 / TREES);

    // Упражнение №2
    puts  ("Exercise #2: binary search function.");
    int value = rand () % 1000;
    printf ("the value %d was %s found in the tree.\n", value, 
            findNodeInTree (trees [0], value) == NULL ? "NOT" : "");
    value = -1;
    printf ("the value %d was %s found in the tree.\n", value, 
            findNodeInTree (trees [1], value) == NULL ? "NOT" : "");

    // garbage collection
    for (int i = 0; i < TREES; ++i)
        freeBinTree (trees [i]);

    // return o.k.
    return EXIT_SUCCESS;
} // main
