#ifndef TREE_H
#define TREE_H

#define TRUE  1
#define FALSE 0

#include "TreeData.h"

struct AVLTree;
//struct TreeNode;

struct AVLTree* createTree();
void addNode(struct AVLTree* tree, TYPE val);

#endif // TREE_H