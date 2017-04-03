/**************************************************************************************************
** Program Filename: cirListDeque.c
** Author: Conrad Lewin
** Date: 1/23/2016
** Description: This file contains the interface for a deque as well as the
** necessary functionality for the underlying data structure, a circular doubly linked list, for 
** the aforementioned ADT.
***************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <float.h>
#include "cirListDeque.h"

/* Double Link Struture */
struct DLink 
{
	TYPE value;/* value of the link */
	struct DLink * next;/* pointer to the next link */
	struct DLink * prev;/* pointer to the previous link */
};

# define TYPE_SENTINEL_VALUE DBL_MAX 


/* ************************************************************************
Deque ADT based on Circularly-Doubly-Linked List WITH Sentinel
************************************************************************ */

struct cirListDeque 
{
	int size;/* number of links in the deque */
	struct DLink *Sentinel;	/* pointer to the sentinel */
};
/* internal functions prototypes */
struct DLink* _createLink(TYPE val);
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, TYPE v);
void _removeLink(struct cirListDeque *q, struct DLink *lnk);


/* ************************************************************************
Deque Functions
************************************************************************ */

/* Initialize deque.

param: 	q		pointer to the deque
pre:	q is not null
post:	q->Sentinel is allocated and q->size equals zero
*/
void _initCirListDeque(struct cirListDeque *q)
{
	assert(q != 0); //make sure q contains a valid address

	q->Sentinel = malloc(sizeof(struct DLink)); //create a new link

	//link the sentinel to itself
	q->Sentinel->next = q->Sentinel;
	q->Sentinel->prev = q->Sentinel;

	q->size = 0;
}

/*
create a new circular list deque

*/

struct cirListDeque *createCirListDeque()
{
	//create, initialize and return a new linked list
	struct cirListDeque *newCL = malloc(sizeof(struct cirListDeque));
	_initCirListDeque(newCL);
	return(newCL);
}


/* Create a link for a value.

param: 	val		the value to create a link for
pre:	none
post:	a link to store the value
*/
struct DLink * _createLink(TYPE val)
{
	struct DLink* newLink = malloc(sizeof(struct DLink)); //create a new link
	assert(newLink != 0);

	//give the new link a value and initialize its next and previous pointers to null
	newLink->value = val; 
	newLink->next = 0;
	newLink->prev = 0;

	return newLink;

}

/* Adds a link after another link

param: 	q		pointer to the deque
param: 	lnk		pointer to the existing link in the deque
param: 	v		value of the new link to be added after the existing link
pre:	q is not null
pre: 	lnk is not null
pre:	lnk is in the deque
post:	the new link is added into the deque after the existing link
*/
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, TYPE v)
{
	//make sure both struct parameters are not null
	assert(q != 0);
	assert(lnk != 0);

	struct DLink* newLink = _createLink(v); //create a new link

	//set the new link's next and previous pointers so that the new link is "positioned" after lnk
	newLink->next = lnk->next;
	lnk->next = newLink;
	newLink->prev = lnk;
	newLink->next->prev = newLink;
	
	q->size++; //update the number of elements in the list
}

/* Adds a link to the back of the deque

param: 	q		pointer to the deque
param: 	val		value for the link to be added
pre:	q is not null
post:	a link storing val is added to the back of the deque
*/
void addBackCirListDeque(struct cirListDeque *q, TYPE val)
{
	assert(q != 0); //make sure q is not null
	_addLinkAfter(q, q->Sentinel->prev, val); //add link to back of the deque (behind the sentinel)
}

/* Adds a link to the front of the deque

param: 	q		pointer to the deque
param: 	val		value for the link to be added
pre:	q is not null
post:	a link storing val is added to the front of the deque
*/
void addFrontCirListDeque(struct cirListDeque *q, TYPE val)
{
	assert(q != 0); //make sure q is not null
	_addLinkAfter(q, q->Sentinel, val); //add link to front of the deque (after the sentinel)
}

/* Get the value of the front of the deque

param: 	q		pointer to the deque
pre:	q is not null and q is not empty
post:	none
ret: 	value of the front of the deque
*/
TYPE frontCirListDeque(struct cirListDeque *q)
{
	//make sure q is not null and that the deque is not empty
	assert(q != 0);
	assert(!isEmptyCirListDeque(q));

	return q->Sentinel->next->value; //return the value at the front of the deque
}

/* Get the value of the back of the deque

param: 	q		pointer to the deque
pre:	q is not null and q is not empty
post:	none
ret: 	value of the back of the deque
*/
TYPE backCirListDeque(struct cirListDeque *q)
{
	//make sure q is not null and that the deque is not empty
	assert(q != 0);
	assert(!isEmptyCirListDeque(q));

	return q->Sentinel->prev->value; //return the value at the back of the deque
}

/* Remove a link from the deque

param: 	q		pointer to the deque
param: 	lnk		pointer to the link to be removed
pre:	q is not null and q is not empty
post:	the link is removed from the deque
*/
void _removeLink(struct cirListDeque *q, struct DLink *lnk)
{
	//make sure q is not null
	assert(q != 0);

	if (!isEmptyCirListDeque(q))
	{

		//reorganize the link pointers belonging to the links that flank lnk to bypass lnk
		lnk->prev->next = lnk->next;
		lnk->next->prev = lnk->prev;

		//deallocate the memory reserved for lnk
		free(lnk);
		lnk = 0;

		q->size--; //update the size of the list
	}
}

/* Remove the front of the deque

param: 	q		pointer to the deque
pre:	q is not null and q is not empty
post:	the front is removed from the deque
*/
void removeFrontCirListDeque(struct cirListDeque *q) 
{
	//make sure q is not null
	assert(q != 0);

	if (!isEmptyCirListDeque(q))
	{
		_removeLink(q, q->Sentinel->next); //remove link from the front of the deque
	}
}


/* Remove the back of the deque

param: 	q		pointer to the deque
pre:	q is not null and q is not empty
post:	the back is removed from the deque
*/
void removeBackCirListDeque(struct cirListDeque *q)
{
	//make sure q is not null
	assert(q != 0);

	if (!isEmptyCirListDeque(q))
	{
		_removeLink(q, q->Sentinel->prev); //remove link from the back of the deque
	}
}

/* De-allocate all links of the deque

param: 	q		pointer to the deque
pre:	none
post:	All links (including Sentinel) are de-allocated
*/
void freeCirListDeque(struct cirListDeque *q)
{
	//make sure q is not null
	assert(q != 0);

	struct DLink* curLink = q->Sentinel->next; //get the first link in the list (not the sentinel)

	//iterate through the list, removing all of its links
	while (!isEmptyCirListDeque(q))
	{
		struct DLink* temp = curLink->next; //save the link after the current link

		_removeLink(q, curLink); //remove the current link
		curLink = temp;	//update the current link
	}

	//deallocate the memory reserved for list's sentinel
	free(q->Sentinel);
	q->Sentinel = 0;
}

/* Check whether the deque is empty

param: 	q		pointer to the deque
pre:	q is not null
ret: 	1 if the deque is empty. Otherwise, 0.
*/
int isEmptyCirListDeque(struct cirListDeque *q) 
{
	assert(q != 0);

	if (q->size > 0)
	{
		return 0;
	}

	return 1;
}

/* Print the links in the deque from front to back

param: 	q		pointer to the deque
pre:	q is not null and q is not empty
post: 	the links in the deque are printed from front to back
*/
void printCirListDeque(struct cirListDeque *q)
{
	assert(q != 0);

	if (!isEmptyCirListDeque(q))
	{
		for (struct DLink* link = q->Sentinel->next; link != q->Sentinel; link = link->next)
		{
			printf(TYPE_FORMAT " ", link->value);
		}
	}
}

/* Reverse the deque

param: 	q		pointer to the deque
pre:	q is not null and q is not empty
post: 	the deque is reversed
*/
void reverseCirListDeque(struct cirListDeque *q)
{
	//make sure q is not null
	assert(q != 0);

	if (!isEmptyCirListDeque(q))
	{

		//swap the addresses stored in the sentinel's next and previous pointers
		struct DLink* temp = q->Sentinel->next;
		q->Sentinel->next = q->Sentinel->prev;
		q->Sentinel->prev = temp;

		//loop through the list, swapping the addresses stored in the current link's next and previous pointers
		for (struct DLink* link = q->Sentinel->next; link != q->Sentinel; link = link->next)
		{
			temp = link->next;
			link->next = link->prev;
			link->prev = temp;
		}
	}
}
