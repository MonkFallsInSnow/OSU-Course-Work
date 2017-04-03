#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

//----structs---------------------------------------------------------------------------------
struct AVLTree
{
	struct TreeNode* root;
	int count;
};

struct TreeNode
{
	int height;
	struct BasicData* data;
	struct TreeNode* leftChild;
	struct TreeNode* rightChild;
};
//----end structs------------------------------------------------------------------------------


//----internal function prototypes---------------------------------------------------------------
void _initTree(struct AVLTree* tree);
struct TreeNode* _addNode(struct TreeNode* current, TYPE val);
int _getHeight(struct TreeNode* current);
void _setHeight(struct TreeNode* current);
struct TreeNode* _rotateLeft(struct TreeNode* current);
struct TreeNode* _rotateRight(struct TreeNode* current);
struct TreeNode* _balance(struct TreeNode* current);
//----end internal function prototypes------------------------------------------------------------


//---------internal helper functions-----------------------------------------------------------
void _initTree(struct AVLTree* tree)
{
	tree->root = NULL;
	tree->count = 0;
}

struct TreeNode* _addNode(struct TreeNode* current, TYPE val)
{
	if (current == NULL)
	{
		struct TreeNode* newNode = malloc(sizeof(struct TreeNode));
		assert(newNode != NULL);

		newNode->data = val;
		newNode->leftChild = newNode->rightChild = NULL;
		newNode->height = 0;
		return newNode;
	}

	if (compareNodes(val, current->data) < 0)
	{
		current->leftChild = _addNode(current->leftChild, val);
	}
	else
	{
		current->rightChild = _addNode(current->rightChild, val);
	}

	return _balance(current);
}

int _getHeight(struct TreeNode* current)
{
	if (current != NULL)
	{
		return current->height;
	}

	return -1;
}

void _setHeight(struct TreeNode* current)
{
	int rightHeight = _getHeight(current->rightChild);
	int leftHeight = _getHeight(current->leftChild);

	if (leftHeight < rightHeight)
	{
		current->height = rightHeight + 1;
	}
	else
	{
		current->height = leftHeight + 1;
	}

}

int _getBalanceFactor(struct TreeNode* current)
{
	return _getHeight(current->leftChild) - _getHeight(current->rightChild); //if negative, then heavy on the right
}

struct TreeNode* _rotateLeft(struct TreeNode* current)
{
	struct TreeNode* newRoot = current->rightChild;
	current->rightChild = newRoot->leftChild;
	newRoot->leftChild = current;
	return newRoot;
}

struct TreeNode* _rotateRight(struct TreeNode* current)
{
	struct TreeNode* newRoot = current->leftChild;
	current->leftChild = newRoot->rightChild;
	newRoot->rightChild = current;
	return newRoot;
}

struct TreeNode* _balance(struct TreeNode* current)
{
	int balanceFactor = _getBalanceFactor(current);

	if (balanceFactor < -1) //heavy on the right
	{
		if (_getBalanceFactor(current->rightChild) > 0)
		{
			current->rightChild = _rotateRight(current->rightChild);
		}
		
		return _rotateLeft(current);
	}
	else if (balanceFactor > 1) //heavy on the left
	{
		if (_getBalanceFactor(current->leftChild) < 0)
		{
			current->leftChild = _rotateLeft(current->leftChild);
		}

		return _rotateRight(current);
	}
	_setHeight(current);
	return current;
}
//------end internal helper functions----------------------------------------------------------


//-------AVL Tree Interface------------------------------------------------------------------
struct AVLTree* createTree()
{
	struct AVLTree* tree = malloc(sizeof(struct AVLTree));
	assert(tree != NULL);

	_initTree(tree);
	return tree;
}

void addNode(struct AVLTree* tree, TYPE val)
{
	tree->root = _addNode(tree->root, val);
	tree->count++;
}


/* Rotation Notes:
 * if a tree is unbalanced on the right, then rotate left.
 * if a tree is unbalanced on the left, then rotate right.
 * if a tree is heavy on the left and that child is heavy on the right, then rotate left-right
 * if a tree is heavy on the right and that child is heavy on the left, then rotate right-left
*/