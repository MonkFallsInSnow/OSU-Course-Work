#include "TreeData.h"

Data* createData(int n, char* label)
{
	Data* data = malloc(sizeof(Data));
	data->name = label;
	data->num = n;
}

int compareNodes(TYPE left, TYPE right)
{
	Data* newLeft = (Data*)left;
	Data* newRight = (Data*)right;

	if (newLeft->num < newRight->num)
	{
		return -1;
	}
	else if (newLeft->num > newRight->num)
	{
		return 1;
	}

	return 0;
}