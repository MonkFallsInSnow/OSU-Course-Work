/**************************************************************************************************
** Program Filename: linkedList.c
** Author: Conrad Lewin
** Date: 1/22/2016
** Description: This file contains the interface for both a bag and a deque as well as the
** necessary functionality for the underlying data structure, a doubly linked list with both front
** and back sentinels, for the aforementioned ADTs.
***************************************************************************************************/
#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

/* Double Link*/
struct DLink
{
	TYPE value;
	struct DLink * next;
	struct DLink * prev;
};

/* Double Linked List with Head and Tail Sentinels  */

struct linkedList
{
	int size;
	struct DLink *firstLink;
	struct DLink *lastLink;
};

/*
initList
param: lst the linkedList
pre: lst is not null
post: lst size is 0
*/

void _initList(struct linkedList* lst)
{
	assert(lst != 0); //make sure lst contains a valid address

	lst->firstLink = malloc(sizeof(struct DLink)); //create a front sentinel
	assert(lst->firstLink != 0); //ensure the allocation was sucessful

	lst->lastLink = malloc(sizeof(struct DLink)); //create a back sentinel
	assert(lst->lastLink != 0); //ensure the allocation was sucessful

	lst->firstLink->next = lst->lastLink; //link the front sentinel to the last sentinel
	lst->firstLink->prev = 0;

	lst->lastLink->next = 0;
	lst->lastLink->prev = lst->firstLink; //link the back sentinel to the front sentinel

	lst->size = 0; //initialize the size of the list
}

/*
createList
param: none
pre: none
post: firstLink and lastLink reference sentinels
*/

struct linkedList *createLinkedList()
{
	struct linkedList *newList = malloc(sizeof(struct linkedList)); //create a new list
	_initList(newList); //initialize the list
	return(newList);
}

/*
_addLinkBeforeBefore
param: lst the linkedList
param: l the  link to add before
param: v the value to add
pre: lst is not null
pre: l is not null
post: lst is not empty
*/

/* Adds Before the provided link, l */

void _addLinkBefore(struct linkedList *lst, struct DLink *l, TYPE v)
{
	//ensure the pointer parameters contain valid addresses
	assert(lst != 0);
	assert(l != 0);

	struct DLink* newLink = malloc(sizeof(struct DLink)); //create a new link
	newLink->value = v; //give the new link a value

	//insert the new link between l and the link that comes before l
	newLink->prev = l->prev;
	l->prev->next = newLink;
	newLink->next = l;
	l->prev = newLink;

	lst->size++; //update the size of the list

}


/*
addFrontList
param: lst the linkedList
param: e the element to be added
pre: lst is not null
post: lst is not empty, increased size by 1
*/

void addFrontList(struct linkedList *lst, TYPE e)
{
	assert(lst != 0); //make sure lst contains a valid address

	_addLinkBefore(lst, lst->firstLink->next, e); //add link to the front of the list
}

/*
addBackList
param: lst the linkedList
param: e the element to be added
pre: lst is not null
post: lst is not empty, increased size by 1
*/

void addBackList(struct linkedList *lst, TYPE e)
{
	assert(lst != 0); //make sure lst contains a valid address

	_addLinkBefore(lst, lst->lastLink, e); //add link to the back of the list
}

/*
frontList
param: lst the linkedList
pre: lst is not null
pre: lst is not empty
post: none
*/

TYPE frontList(struct linkedList *lst)
{
	//ensure the pointer parameters contain valid addresses
	assert(lst != 0);
	assert(!isEmptyList(lst));

	return lst->firstLink->next->value; //get value data from the first complete link in the list
}

/*
backList
param: lst the linkedList
pre: lst is not null
pre: lst is not empty
post: lst is not empty
*/

TYPE backList(struct linkedList *lst)
{
	//ensure the pointer parameters contain valid addresses
	assert(lst != 0);
	assert(!isEmptyList(lst));

	return lst->lastLink->prev->value; //get value data from the last complete link in the list
}

/*
_removeLink
param: lst the linkedList
param: l the link to be removed
pre: lst is not null
pre: l is not null
post: lst size is reduced by 1
*/

void _removeLink(struct linkedList *lst, struct DLink *l)
{
	//ensure the pointer parameters contain valid addresses
	assert(lst != 0);
	assert(l != 0);

	//redirect the link pointers from the links that come directly before and after l to pass over l
	l->prev->next = l->next;
	l->next->prev = l->prev;

	//deallocate memory for l
	free(l);
	l = 0;

	lst->size--; //update list size
}

/*
removeFrontList
param: lst the linkedList
pre:lst is not null
pre: lst is not empty
post: size is reduced by 1
*/

void removeFrontList(struct linkedList *lst)
{
	assert(lst != 0); //make sure lst contains a valid address
	assert(!isEmptyList(lst)); //make sure the list is not empty

	_removeLink(lst, lst->firstLink->next); //remove link from the front of the list
}

/*
removeBackList
param: lst the linkedList
pre: lst is not null
pre:lst is not empty
post: size reduced by 1
*/

void removeBackList(struct linkedList *lst)
{
	assert(lst != 0); //make sure lst contains a valid address
	assert(!isEmptyList(lst)); //make sure the list is not empty

	_removeLink(lst, lst->lastLink->prev); //remove link from the back of the list
}

/*
isEmptyList
param: lst the linkedList
pre: lst is not null
post: none
*/

int isEmptyList(struct linkedList *lst)
{
	assert(lst != 0);

	if (lst->size > 0)
	{
		return 0;
	}

	return 1;
}


/* Function to print list
Pre: lst is not null
*/
void _printList(struct linkedList* lst)
{
	assert(lst != 0); //make sure lst contains a valid address

	//loop through the list, printing each link's value data
	if (!isEmptyList(lst))
	{
		for (struct DLink* link = lst->firstLink->next; link != lst->lastLink; link = link->next)
		{
			printf(TYPE_FORMAT " ", link->value);
		}
	}
}

/*
Add an item to the bag
param: 	lst		pointer to the bag
param: 	v		value to be added
pre:	lst is not null
post:	a link storing val is added to the bag
*/
void addList(struct linkedList *lst, TYPE v)
{
	assert(lst != 0); //make sure lst contains a valid address
	addBackList(lst, v); //add link to the bag (adds item to the back of the underlying list)
}

/*	Returns boolean (encoded as an int) demonstrating whether or not
the specified value is in the collection
true = 1
false = 0

param:	lst		pointer to the bag
param:	e		the value to look for in the bag
pre:	lst is not null
pre:	lst is not empty
post:	no changes to the bag
*/
int containsList(struct linkedList *lst, TYPE e)
{
	assert(lst != 0); //make sure lst contains a valid address
	assert(!isEmptyList(lst)); //make sure the list is not empty

	struct DLink* curLink = lst->firstLink->next; //get the first complete link in the list

	//perform a linear search of the list for the given value, returning an int indicating whether or not the value was found
	while (curLink != lst->lastLink)
	{
		if (curLink->value == e)
		{
			return 1;
		}

		curLink = curLink->next;
	}

	return 0;
}

/*	Removes the first occurrence of the specified value from the collection
if it occurs

param:	lst		pointer to the bag
param:	e		the value to be removed from the bag
pre:	lst is not null
pre:	lst is not empty
post:	e has been removed
post:	size of the bag is reduced by 1
*/
void removeList(struct linkedList *lst, TYPE e)
{
	assert(lst != 0); //make sure lst contains a valid address
	assert(!isEmptyList(lst)); //make sure the list is not empty

	struct DLink* curLink = lst->firstLink->next; //get first complete link in the list
	int valFound = 0; //tracks whether or not the given value has been found

	//perform a linear search for the given value and, if found, removes the containing link
	while (curLink != lst->lastLink && !valFound)
	{
		if (curLink->value == e)
		{
			_removeLink(lst, curLink);
			valFound = 1;
		}

		curLink = curLink->next;
	}
}