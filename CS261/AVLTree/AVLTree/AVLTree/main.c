#include "tree.h"
#include "TreeData.h"
#include <stdio.h>

int main()
{
	Data* d1 = createData(30, "root");
	Data* d2 = createData(10, "root-right");
	Data* d3 = createData(20, "root-right-right");
	Data* d4 = createData(5, "root-right-right-right");

	struct AVLTree* myTree = createTree();
	addNode(myTree, d1);
	addNode(myTree, d2);
	addNode(myTree, d3);
	addNode(myTree, d4);
	getchar();
}