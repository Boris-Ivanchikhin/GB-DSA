#ifndef LIB_TREES_H
#define LIB_TREES_H

#include <stdio.h>
#include <stdlib.h>

#define T int

typedef struct BinTreeNode {
    T key;
    struct BinTreeNode *left;
    struct BinTreeNode *right;
} BinTreeNode;

void printBinTree (BinTreeNode* root);
BinTreeNode* insBinTree (BinTreeNode* tPtr, int data);
void freeBinTree (BinTreeNode* tPtr);

#endif // LIB_TREES_H
