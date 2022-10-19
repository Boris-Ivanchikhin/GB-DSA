#include "lib_trees.h"

// * check script
#define CHECK_MEM(ptr) do { \
    if (ptr == NULL) { \
        puts("memory allocation error!\nexecution aborted"); \
        abort(); \
        } \
} while(0)

// * print tree
void printBinTree (BinTreeNode *root) {
    if (root) {
        printf ("%d", root->key);
        if (root->left || root->right) {
            printf ("(");
            if (root->left)
                printBinTree (root->left);
            else
                printf ("NULL");
            printf (",");
            if (root->right)
                printBinTree(root->right);
            else
                printf ("NULL");
            printf (")");
        }
    }
} // printBinTree

// * insert BinTreeNode
BinTreeNode* insBinTree (BinTreeNode *tPtr, int data) {
    BinTreeNode *newNode;
    newNode        = (BinTreeNode*) malloc (sizeof (BinTreeNode));
    CHECK_MEM(newNode);
    newNode->key   = data;
    // Вставка прозводится на место листа дерева
    newNode->left  = NULL;
    newNode->right = NULL;
    // Ссылка на текущий узел при поиске
    // Ссылка на родителя текущего узла
    BinTreeNode *current = tPtr, *parent  = tPtr;
    // Если переданный узел пустой, то корнем дерева станет новый узел
    if (tPtr == NULL)
        return newNode;
    // else
    while (current->key != data) {
        // Родительской ссылке присваивается ссылка на текущий узел
        parent = current;
        // Если ключ в текущем узле больше искомого,
        //  то текущий узел нужно переключить в левого наследника
        if (current->key > data) {
            current = current->left;
            // Если после переключения текущего узла не существует,
            //  то сюда возможно добавить наследника (листовой элемент)
            if (current == NULL) {
                parent->left = newNode;
                break; //return t;
            }
        } else {
        // Если ключ в текущем узле меньше искомого,
        //  то текущий узел нужно переключить в правого наследника
            current = current->right;
            // Если после переключения текущего узла не существует,
            //  то сюда возможно добавить наследника (листовой элемент)
            if (current == NULL) {
                parent->right = newNode;
                break; //return t;
            }
        }
    }
    // return
    return tPtr;
} // insBinTree

// * garbage collector
void freeBinTree (BinTreeNode* tPtr) {
    if (tPtr == NULL) return;
    if (tPtr->left)   freeBinTree (tPtr->left);
    if (tPtr->right)  freeBinTree (tPtr->right);
    free (tPtr);
} // freeBinTree
