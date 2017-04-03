#include "linkedList.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
	struct linkedList* deque = createLinkedList();
	struct linkedList* bag = createLinkedList();
	printf("Removing front and back element...\n");
	removeFrontList(deque);
	removeBackList(deque);
	_printList(deque);
	printf("Adding items to front of deque...\n");
	addFrontList(deque, 10);
	addFrontList(deque, 20);
	addFrontList(deque, 30);
	addFrontList(deque, 40);
	addFrontList(deque, 50);
	_printList(deque);

	printf("\nAdding items to back of deque...\n");
	addBackList(deque, 1);
	addBackList(deque, 2);
	addBackList(deque, 3);
	addBackList(deque, 4);
	addBackList(deque, 5);
	_printList(deque);

	printf("\nFront of deque: %d Back of deque: %d\n", frontList(deque), backList(deque));

	printf("Removing front and back element...\n");
	removeFrontList(deque);
	removeBackList(deque);
	_printList(deque);

	printf("\nFront of deque: %d Back of deque: %d\n", frontList(deque), backList(deque));

	printf("Adding items to bag...\n");
	addList(bag, 20);
	addList(bag, 15);
	addList(bag, 30);
	addList(bag, 140);
	addList(bag, 13);
	_printList(bag);

	if (containsList(bag, 30))
	{
		printf("\n30 is in the bag.\n");
	}
	else
	{
		printf("\n30 is not in the bag.\n");
	}

	if (containsList(bag, 10))
	{
		printf("\n10 is in the bag.\n");
	}
	else
	{
		printf("\n10 is not in the bag.\n");
	}

	printf("Removing 30 from bag...\n");
	removeList(bag,30);
	_printList(bag);
	
	if (containsList(bag, 30))
	{
		printf("\n30 is in the bag.\n");
	}
	else
	{
		printf("\n30 is not in the bag.\n");
	}

	return 0;
}