#ifndef TREE_DATA_H
#define TREE_DATA_H

#define TYPE void*

typedef struct BasicData
{
	int num;
	char* name;
}Data;

Data* createData(int n, char* label);
int compareNodes(TYPE left, TYPE right);

#endif //TREE_DATA_H