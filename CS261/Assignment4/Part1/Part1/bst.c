/**************************************************************************************************
** Program Filename: bst.c
** Author: Conrad Lewin
** Date: 2/14/2016
** Description: This file provides the implementation details of a binary search tree
***************************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "bst.h"
#include "structs.h"

struct Node 
{
	TYPE         val;
	struct Node *left;
	struct Node *right;
};

struct BSTree 
{
	struct Node *root;
	int          cnt;
};

/*----------------------------------------------------------------------------*/
/*
function to initialize the binary search tree.
param tree
pre: tree is not null
post:	tree size is 0
root is null
*/

void initBSTree(struct BSTree *tree)
{
	tree->cnt = 0;
	tree->root = 0;
}

/*
function to create a binary search tree.
param: none
pre: none
post: tree->count = 0
tree->root = 0;
*/

struct BSTree*  newBSTree()
{
	struct BSTree *tree = (struct BSTree *)malloc(sizeof(struct BSTree));
	assert(tree != 0);

	initBSTree(tree);
	return tree;
}

/*----------------------------------------------------------------------------*/
/*
function to free the nodes of a binary search tree
param: node  the root node of the tree to be freed
pre: none
post: node and all descendants are deallocated
*/

void _freeBST(struct Node *node)
{
	if (node != 0) 
	{
		_freeBST(node->left);
		_freeBST(node->right);
		free(node);
	}
}

/*
function to clear the nodes of a binary search tree
param: tree    a binary search tree
pre: tree ! = null
post: the nodes of the tree are deallocated
tree->root = 0;
tree->cnt = 0
*/
void clearBSTree(struct BSTree *tree)
{
	_freeBST(tree->root);
	tree->root = 0;
	tree->cnt = 0;
}

/*
function to deallocate a dynamically allocated binary search tree
param: tree   the binary search tree
pre: tree != null;
post: all nodes and the tree structure itself are deallocated.
*/
void deleteBSTree(struct BSTree *tree)
{
	clearBSTree(tree);
	free(tree);
}

/*----------------------------------------------------------------------------*/
/*
function to determine if  a binary search tree is empty.

param: tree    the binary search tree
pre:  tree is not null
*/
int isEmptyBSTree(struct BSTree *tree) { return (tree->cnt == 0); }

/*
function to determine the size of a binary search tree

param: tree    the binary search tree
pre:  tree is not null
*/
int sizeBSTree(struct BSTree *tree) { return tree->cnt; }

/*----------------------------------------------------------------------------*/
/*
recursive helper function to add a node to the binary search tree.
HINT: You have to use the compare() function to compare values.
param:  cur	the current root node
val	the value to be added to the binary search tree
pre:	val is not null
*/
struct Node *_addNode(struct Node *cur, TYPE val)
{
	assert(val != 0);

	//create a leaf node if current has no children
	if (cur == NULL)
	{
		struct Node* newNode = malloc(sizeof(struct Node));
		newNode->val = val;
		newNode->left = 0;
		newNode->right = 0;
		return newNode;
	}

	//compare the argument val with the data stored in the current node
	int compareValue = compare(val, cur->val);

	if (compareValue == -1) //if val is less than current node
	{
		cur->left = _addNode(cur->left, val);
	}
	else if (compareValue == 1 || compareValue == 0) //if val is greater than or equal current node
	{
		cur->right = _addNode(cur->right, val);
	}

	return cur;
}

/*
function to add a value to the binary search tree
param: tree   the binary search tree
val		the value to be added to the tree

pre:	tree is not null
val is not null
pose:  tree size increased by 1
tree now contains the value, val
*/
void addBSTree(struct BSTree *tree, TYPE val)
{
	tree->root = _addNode(tree->root, val);
	tree->cnt++;
}


/*
function to determine if the binary search tree contains a particular element
HINT: You have to use the compare() function to compare values.
param:	tree	the binary search tree
val		the value to search for in the tree
pre:	tree is not null
val is not null
post:	none
*/

/*----------------------------------------------------------------------------*/
int containsBSTree(struct BSTree *tree, TYPE val)
{
	assert(tree != NULL);
	assert(val != NULL);

	//set the current node to the root
	struct Node* curNode = tree->root;

	/* traverse the tree, comparing the data in each node against the argument val
	 * go to the left node if the argument data is less than the data in the currently examined node
	 * go to the right node if the argument data is greater than data in the currently examined node
	 * return true (1) if a node is found with the passed in data value
    */
	while (curNode != NULL)
	{
		switch (compare(val, curNode->val))
		{
			case -1: 
				curNode = curNode->left;
				break;
			case 0:
				return 1;
			case 1:
				curNode = curNode->right;
				break;
			default:
				break;
		}
	}

	return 0; //return false (0) if the data is not found
}

/*
helper function to find the left most child of a node
return the value of the left most child of cur
param: cur		the current node
pre:	cur is not null
post: none
*/

/*----------------------------------------------------------------------------*/
TYPE _leftMost(struct Node *cur)
{
	assert(cur != NULL);

	while (cur->left != NULL)
	{
		cur = cur->left;
	}

	return cur->val;
}


/*
recursive helper function to remove the left most child of a node
HINT: this function returns cur if its left child is NOT NULL. Otherwise,
it returns the right child of cur and free cur.

Note:  If you do this iteratively, the above hint does not apply.

param: cur	the current node
pre:	cur is not null
post:	the left most node of cur is not in the tree
*/
/*----------------------------------------------------------------------------*/
struct Node *_removeLeftMost(struct Node *cur)
{
	assert(cur != NULL);
	
	/* if the current node has a left child set the current node to that child 
	 * and rebuild the tree when the recursive call returns
	*/
	if (cur->left != NULL)
	{
		cur->left = _removeLeftMost(cur->left);
		return cur;
	}

	//get the right child of the leaf node and replace the child of its parent with this right child 
	struct Node* rightChild = cur->right;
	free(cur);
	return rightChild;
}
/*
recursive helper function to remove a node from the tree
HINT: You have to use the compare() function to compare values.
param:	cur	the current node
val	the value to be removed from the tree
pre:	val is in the tree
cur is not null
val is not null
*/
/*----------------------------------------------------------------------------*/
struct Node *_removeNode(struct Node *cur, TYPE val)
{
	//compare the current node data with the argument val
	int compareVal = compare(val, cur->val);

	/* traverse the tree searching for a node that contains the data passed to the function.
	 * if a suitable node is found, then find the current node's successor node and rebuild the tree,
	 * replacing the node to be removed with the successor
	*/
	if (compareVal == 0)
	{
		if (cur->right == NULL)
		{
			return cur->left;
		}
		else
		{
			cur->val = _leftMost(cur->right);
			_removeLeftMost(cur->right);
			
		}
	}
	else
	{
		if (compareVal == -1)
		{
			cur->left = _removeNode(cur->left, val);
		}
		else
		{
			cur->right = _removeNode(cur->right, val);
		}
	}

	return cur;
}
/*
function to remove a value from the binary search tree
param: tree   the binary search tree
val		the value to be removed from the tree
pre:	tree is not null
val is not null
val is in the tree
pose:	tree size is reduced by 1
*/
void removeBSTree(struct BSTree *tree, TYPE val)
{
	if (containsBSTree(tree, val)) {
		tree->root = _removeNode(tree->root, val);
		tree->cnt--;
	}
}

/*----------------------------------------------------------------------------*/

/* The following is used only for debugging, set to "#if 0" when used
in other applications */
#if 1
#include <stdio.h>

/*----------------------------------------------------------------------------*/
void printNode(struct Node *cur) {
	if (cur == 0) return;
	printf("(");
	printNode(cur->left);
	/*Call print_type which prints the value of the TYPE*/
	print_type(cur->val);
	printNode(cur->right);
	printf(")");
}

void printTree(struct BSTree *tree) {
	if (tree == 0) return;
	printNode(tree->root);
}
/*----------------------------------------------------------------------------*/

#endif


#if 1
/************************************************************************************************************************
from here to the end of this file are a set of fucntions for testing the fucntions of the BST - This is also provided in a
separate file .
***************************************************************************************************************************/
/*
function to built a Binary Search Tree (BST) by adding numbers in this specific order
the graph is empty to start: 50, 13, 110 , 10

*/
struct BSTree *buildBSTTree() {
	/*     50
	13  110
	10
	*/
	struct BSTree *tree = newBSTree();

	/*Create value of the type of data that you want to store*/
	struct data *myData1 = (struct data *) malloc(sizeof(struct data));
	struct data *myData2 = (struct data *) malloc(sizeof(struct data));
	struct data *myData3 = (struct data *) malloc(sizeof(struct data));
	struct data *myData4 = (struct data *) malloc(sizeof(struct data));

	myData1->number = 50;
	myData1->name = "rooty";
	myData2->number = 13;
	myData2->name = "lefty";
	myData3->number = 110;
	myData3->name = "righty";
	myData4->number = 10;
	myData4->name = "lefty of lefty";

	/*add the values to BST*/
	addBSTree(tree, myData1);
	addBSTree(tree, myData2);
	addBSTree(tree, myData3);
	addBSTree(tree, myData4);

	return tree;
}

/*
function to print the result of a test function
param: predicate:  the result of the test
nameTestFunction : the name of the function that has been tested
message

*/
void printTestResult(int predicate, char *nameTestFunction, char *message) {
	if (predicate)
		printf("%s(): PASS %s\n", nameTestFunction, message);
	else
		printf("%s(): FAIL %s\n", nameTestFunction, message);
}

/*
fucntion to test each node of the BST and their children

*/
void testAddNode() {
	struct BSTree *tree = newBSTree();

	struct data myData1, myData2, myData3, myData4;

	myData1.number = 50;
	myData1.name = "rooty";
	addBSTree(tree, &myData1);
	//check the root node
	if (compare(tree->root->val, (TYPE *)&myData1) != 0) {
		printf("addNode() test: FAIL to insert 50 as root\n");
		return;
	}
	//check the tree->cnt value after adding a node to the tree
	else if (tree->cnt != 1) {
		printf("addNode() test: FAIL to increase count when inserting 50 as root\n");
		return;
	}
	else printf("addNode() test: PASS when adding 50 as root\n");


	myData2.number = 13;
	myData2.name = "lefty";
	addBSTree(tree, &myData2);

	//check the position of the second element that is added to the BST tree
	if (compare(tree->root->left->val, (TYPE *)&myData2) != 0) {
		printf("addNode() test: FAIL to insert 13 as left child of root\n");
		return;
	}
	else if (tree->cnt != 2) {
		printf("addNode() test: FAIL to increase count when inserting 13 as left of root\n");
		return;
	}
	else printf("addNode() test: PASS when adding 13 as left of root\n");


	myData3.number = 110;
	myData3.name = "righty";
	addBSTree(tree, &myData3);

	//check the position of the third element that is added to the BST tree    
	if (compare(tree->root->right->val, (TYPE *)&myData3) != 0) {
		printf("addNode() test: FAIL to insert 110 as right child of root\n");
		return;
	}
	else if (tree->cnt != 3) {
		printf("addNode() test: FAIL to increase count when inserting 110 as right of root\n");
		return;
	}
	else printf("addNode() test: PASS when adding 110 as right of root\n");


	myData4.number = 10;
	myData4.name = "righty of lefty";
	addBSTree(tree, &myData4);

	//check the position of the fourth element that is added to the BST tree
	if (compare(tree->root->left->left->val, (TYPE *)&myData4) != 0) {
		printf("addNode() test: FAIL to insert 10 as left child of left of root\n");
		return;
	}
	else if (tree->cnt != 4) {
		printf("addNode() test: FAIL to increase count when inserting 10 as left of left of root\n");
		return;
	}
	else printf("addNode() test: PASS when adding 10 as left of left of root\n");
}

/*
fucntion to test that the BST contains the elements that we added to it

*/
void testContainsBSTree() {
	struct BSTree *tree = buildBSTTree();

	struct data myData1, myData2, myData3, myData4, myData5;

	myData1.number = 50;
	myData1.name = "rooty";
	myData2.number = 13;
	myData2.name = "lefty";
	myData3.number = 110;
	myData3.name = "righty";
	myData4.number = 10;
	myData4.name = "lefty of lefty";
	myData5.number = 111;
	myData5.name = "not in tree";

	printTestResult(containsBSTree(tree, &myData1), "containsBSTree", "when test containing 50 as root");

	printTestResult(containsBSTree(tree, &myData2), "containsBSTree", "when test containing 13 as left of root");

	printTestResult(containsBSTree(tree, &myData3), "containsBSTree", "when test containing 110 as right of root");

	printTestResult(containsBSTree(tree, &myData4), "containsBSTree", "when test containing 10 as left of left of root");

	//check containsBSTree fucntion when the tree does not contain a node    
	printTestResult(!containsBSTree(tree, &myData5), "containsBSTree", "when test containing 111, which is not in the tree");

}

/*
fucntion to test the left_Most_element

*/
void testLeftMost() {
	struct BSTree *tree = buildBSTTree();

	struct data myData3, myData4;

	myData3.number = 110;
	myData3.name = "righty";
	myData4.number = 10;
	myData4.name = "lefty of lefty";

	printTestResult(compare(_leftMost(tree->root), &myData4) == 0, "_leftMost", "left most of root");

	printTestResult(compare(_leftMost(tree->root->left), &myData4) == 0, "_leftMost", "left most of left of root");

	printTestResult(compare(_leftMost(tree->root->left->left), &myData4) == 0, "_leftMost", "left most of left of left of root");

	printTestResult(compare(_leftMost(tree->root->right), &myData3) == 0, "_leftMost", "left most of right of root");

}

void testRemoveLeftMost() {
	struct BSTree *tree = buildBSTTree();
	struct Node *cur;

	cur = _removeLeftMost(tree->root);

	printTestResult(cur == tree->root, "_removeLeftMost", "removing leftmost of root 1st try");

	cur = _removeLeftMost(tree->root->right);
	printTestResult(cur == NULL, "_removeLeftMost", "removing leftmost of right of root 1st try");

	cur = _removeLeftMost(tree->root);
	printTestResult(cur == tree->root, "_removeLeftMost", "removing leftmost of root 2st try");
}

void testRemoveNode() {
	struct BSTree *tree = buildBSTTree();
	struct Node *cur;
	struct data myData1, myData2, myData3, myData4;

	myData1.number = 50;
	myData1.name = "rooty";
	myData2.number = 13;
	myData2.name = "lefty";
	myData3.number = 110;
	myData3.name = "righty";
	myData4.number = 10;
	myData4.name = "lefty of lefty";

	_removeNode(tree->root, &myData4);
	printTestResult(compare(tree->root->val, &myData1) == 0 && tree->root->left->left == NULL, "_removeNode", "remove left of left of root 1st try");

	_removeNode(tree->root, &myData3);
	printTestResult(compare(tree->root->val, &myData1) == 0 && tree->root->right == NULL, "_removeNode", "remove right of root 2st try");

	_removeNode(tree->root, &myData2);
	printTestResult(compare(tree->root->val, &myData1) == 0 && tree->root->left == 0, "_removeNode", "remove right of root 3st try");

	cur = _removeNode(tree->root, &myData1);
	printTestResult(cur == NULL, "_removeNode", "remove right of root 4st try");
}

/*

Main function for testing different fucntions of the Assignment#4.

*/

int main(int argc, char *argv[]) {

	//After implementing your code, please uncommnet the following calls to the test functions and test your code 

	testAddNode();

	printf("\n");
	testContainsBSTree();

	printf("\n");
	testLeftMost();

	printf("\n");
	testRemoveLeftMost();

	printf("\n");
	testRemoveNode();

	return 0;


}

#endif

/* my test
int main()
{
	printf("Creating tree...\n");
	struct BSTree* tree = newBSTree();

	struct data* d0 = malloc(sizeof(struct data));
	struct data* d1 = malloc(sizeof(struct data));
	struct data* d2 = malloc(sizeof(struct data));
	struct data* d3 = malloc(sizeof(struct data));
	struct data* d4 = malloc(sizeof(struct data));
	struct data* d5 = malloc(sizeof(struct data));
	struct data* d6 = malloc(sizeof(struct data));
	struct data* d7 = malloc(sizeof(struct data));
	struct data* d8 = malloc(sizeof(struct data));
	struct data* d9 = malloc(sizeof(struct data));
	struct data* d10 = malloc(sizeof(struct data));

	d0->name = "n/a";
	d0->number = -1;

	d1->name = "root";
	d1->number = 50;

	d2->name = "root-left";
	d2->number = 30;

	d3->name = "root-left-left";
	d3->number = 20;

	d4->name = "root-left-right";
	d4->number = 40;

	d5->name = "root-left-right-left";
	d5->number = 35;

	d6->name = "root-right";
	d6->number = 100;

	d7->name = "root-right-left";
	d7->number = 80;

	d8->name = "root-right-right";
	d8->number = 110;

	d9->name = "root-right-right-left";
	d9->number = 105;

	d10->name = "root-right-right-left-left";
	d10->number = 104;

	printf("Checking empty tree for a value...\n");
	if (containsBSTree(tree, d3))
		printf("%d is in the tree.\n", d3->number);
	else
		printf("%d is not in the tree.\n", d3->number);

	printf("Adding nodes to tree...\n");
	addBSTree(tree, d1);
	addBSTree(tree, d2);
	addBSTree(tree, d3);
	addBSTree(tree, d4);
	addBSTree(tree, d5);
	addBSTree(tree, d6);
	addBSTree(tree, d7);
	addBSTree(tree, d8);
	addBSTree(tree, d9);
	addBSTree(tree, d10);

	printTree(tree);
	printf("\n");

	if (containsBSTree(tree, d3))
		printf("%d is in the tree.\n", d3->number);
	else
		printf("%d is not in the tree.\n", d3->number);

	if (containsBSTree(tree, d3))
		printf("%d is in the tree.\n", d7->number);
	else
		printf("%d is not in the tree.\n", d7->number);

	if (containsBSTree(tree, d0))
		printf("%d is in the tree.\n", d0->number);
	else
		printf("%d is not in the tree.\n", d0->number);

	printf("The leftmost node: %d\n", *((int*)_leftMost(tree->root)));

	printf("Removing leftmost nodes...\n");
	_removeLeftMost(tree->root);
	printTree(tree);
	printf("\n");

	printf("Removing node of value 30...\n");
	removeBSTree(tree, d2);
	printTree(tree);
	printf("\n");
	printf("Removing node of value 100...\n");
	removeBSTree(tree, d6);
	printTree(tree);
	printf("\n");
	printf("Removing node of value 80...\n");
	removeBSTree(tree, d7);
	printTree(tree);
	printf("\n");
	printf("Removing node of value 110...\n");
	removeBSTree(tree, d8);
	printTree(tree);
	printf("\n");
}
*/