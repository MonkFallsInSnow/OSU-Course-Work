/**************************************************************************************************
** Program Filename: dynamicArray.c
** Author: Conrad Lewin
** Date: 1/18/2016
** Description: Defines several functions for a dynamic array that will power both stack and bag
** interfaces
***************************************************************************************************/
#include <assert.h>
#include <stdlib.h>
#include "dynArray.h"

struct DynArr
{
	TYPE *data;		/* pointer to the data array */
	int size;		/* Number of elements in the array */
	int capacity;	/* capacity ofthe array */
};

//---helper functions--------------------------------------------------

/****************************************************************************************
** Function: int findElement(DynArr* v, TYPE val)
** Description: Performs a linear search for given element in a dynamic array
** Parameters: v - pointer to a dynamic array, val - and element of type TYPE
** Pre-Conditions: v is not null
** Post-Conditions: returns the index of the found element or -1 if the element was not
** found
********************************************************************************************/
int findElement(DynArr* v, TYPE val)
{
	assert(v != 0);
	assert(!isEmptyDynArr(v));

	int size = sizeDynArr(v);

	for (int i = 0; i < size; i++)
	{
		if (v->data[i] == val)
		{
			return i;
		}
	}

	return -1;
}

//---end helper functions------------------------------------------------


/* ************************************************************************
Dynamic Array Functions
************************************************************************ */

/* Initialize (including allocation of data array) dynamic array.

param: 	v		pointer to the dynamic array
param:	cap 	capacity of the dynamic array
pre:	v is not null
post:	internal data array can hold cap elements
post:	v->data is not null
*/
void initDynArr(DynArr *v, int capacity)
{
	assert(capacity > 0);
	assert(v != 0);
	v->data = (TYPE *)malloc(sizeof(TYPE) * capacity);
	assert(v->data != 0);
	v->size = 0;
	v->capacity = capacity;
}

/* Allocate and initialize dynamic array.

param:	cap 	desired capacity for the dyn array
pre:	none
post:	none
ret:	a non-null pointer to a dynArr of cap capacity
and 0 elements in it.
*/
DynArr* newDynArr(int cap)
{
	assert(cap > 0);
	DynArr *r = (DynArr *)malloc(sizeof(DynArr));
	assert(r != 0);
	initDynArr(r, cap);
	return r;
}

/* Deallocate data array in dynamic array.

param: 	v		pointer to the dynamic array
pre:	none
post:	d.data points to null
post:	size and capacity are 0
post:	the memory used by v->data is freed
*/
void freeDynArr(DynArr *v)
{
	if (v->data != 0)
	{
		free(v->data); 	/* free the space on the heap */
		v->data = 0;   	/* make it point to null */
	}
	v->size = 0;
	v->capacity = 0;
}

/* Deallocate data array and the dynamic array ure.

param: 	v		pointer to the dynamic array
pre:	none
post:	the memory used by v->data is freed
post:	the memory used by d is freed
*/
void deleteDynArr(DynArr *v)
{
	freeDynArr(v);
	free(v);
}

/* Resizes the underlying array to be the size cap

param: 	v		pointer to the dynamic array
param:	cap		the new desired capacity
pre:	v is not null
post:	v has capacity newCap
*/
void _dynArrSetCapacity(DynArr *v, int newCap)
{
	assert(v != 0);
	assert(newCap > v->capacity);

	DynArr* temp = newDynArr(newCap); //create a new array
	int size = sizeDynArr(v);	//get the size of the array

	//copy elements from old array into new array
	for (int i = 0; i < size; i++)
	{
		addDynArr(temp, v->data[i]);
	}

	freeDynArr(v); //deallocate memory tied to old array
	*v = *temp; //replace old array with new array by overwriting the original structure
	free(temp); //deallocate memory tied to the temporary struct
}

/* Get the size of the dynamic array

param: 	v		pointer to the dynamic array
pre:	v is not null
post:	none
ret:	the size of the dynamic array
*/
int sizeDynArr(DynArr *v)
{
	return v->size;
}

/* 	Adds an element to the end of the dynamic array

param: 	v		pointer to the dynamic array
param:	val		the value to add to the end of the dynamic array
pre:	the dynArry is not null
post:	size increases by 1
post:	if reached capacity, capacity is doubled
post:	val is in the last utilized position in the array
*/
void addDynArr(DynArr *v, TYPE val)
{
	assert(v != 0);

	int currentSize = sizeDynArr(v); //get size of the array

    //resize the array if its full
	if (currentSize == v->capacity)
	{
		int newCapacity = v->capacity * 2;
		_dynArrSetCapacity(v, newCapacity);
	}

	v->data[currentSize] = val; //add element to the array
	v->size++; //update the number of elements in the array
}

/*	Get an element from the dynamic array from a specified position

param: 	v		pointer to the dynamic array
param:	pos		integer index to get the element from
pre:	v is not null
pre:	v is not empty
pre:	pos < size of the dyn array and >= 0
post:	no changes to the dyn Array
ret:	value stored at index pos
*/

TYPE getDynArr(DynArr *v, int pos)
{
	assert(v != 0);

	int size = sizeDynArr(v); //get the size of the array

	assert(size > 0); //make sure the array is not empty
	assert(pos >= 0 && pos < size); //make sure the given index is valid

	return v->data[pos];
}

/*	Put an item into the dynamic array at the specified location,
overwriting the element that was there

param: 	v		pointer to the dynamic array
param:	pos		the index to put the value into
param:	val		the value to insert
pre:	v is not null
pre:	v is not empty
pre:	pos >= 0 and pos < size of the array
post:	index pos contains new value, val
*/
void putDynArr(DynArr *v, int pos, TYPE val)
{
	assert(v != 0);
	int size = sizeDynArr(v); //get the size of the array

	assert(size > 0); //make sure the array is not empty
	assert(pos >= 0 && pos < size); //make sure the given index is valid

	v->data[pos] = val; //insert the given element at the specified index
}

/*	Swap two specified elements in the dynamic array

param: 	v		pointer to the dynamic array
param:	i,j		the elements to be swapped
pre:	v is not null
pre:	v is not empty
pre:	i, j >= 0 and i,j < size of the dynamic array
post:	index i now holds the value at j and index j now holds the value at i
*/
void swapDynArr(DynArr *v, int i, int  j)
{
	assert(v != 0);
	int size = sizeDynArr(v); //get the size of the array

	assert(size > 0); //make sure array is not empty

	//make sure the given index values are valid
	assert(i >= 0 && i < size);
	assert(j >= 0 && j < size);

	//swap the elements located at the give indices
	TYPE temp = v->data[i];
	v->data[i] = v->data[j];
	v->data[j] = temp;
}

/*	Remove the element at the specified location from the array,
shifts other elements back one to fill the gap

param: 	v		pointer to the dynamic array
param:	idx		location of element to remove
pre:	v is not null
pre:	v is not empty
pre:	idx < size and idx >= 0
post:	the element at idx is removed
post:	the elements past idx are moved back one
*/
void removeAtDynArr(DynArr *v, int idx)
{
	assert(v != 0);
	int size = sizeDynArr(v); //get the size of the array

	assert(size > 0); //make sure the array is not empty
	assert(idx >= 0 && idx < size); //make sure the given index is valid

	/*
	** overwrite the element at the given index by shifting all elements to the right of
	** the index to the left on space.
	*/
	for (int i = idx; i < size - 1; i++)
	{
		v->data[i] = v->data[i + 1];
	}

	v->size--; //update the size of the array
}



/* ************************************************************************
Stack Interface Functions
************************************************************************ */

/*	Returns boolean (encoded in an int) demonstrating whether or not the
dynamic array stack has an item on it.

param:	v		pointer to the dynamic array
pre:	the dynArr is not null
post:	none
ret:	1 if empty, otherwise 0
*/
int isEmptyDynArr(DynArr *v)
{
	assert(v != 0);

	if (sizeDynArr(v) > 0)
	{
		return 0;
	}

	return 1;
}

/* 	Push an element onto the top of the stack

param:	v		pointer to the dynamic array
param:	val		the value to push onto the stack
pre:	v is not null
post:	size increases by 1
if reached capacity, capacity is doubled
val is on the top of the stack
*/
void pushDynArr(DynArr *v, TYPE val)
{
	addDynArr(v, val);
}

/*	Returns the element at the top of the stack

param:	v		pointer to the dynamic array
pre:	v is not null
pre:	v is not empty
post:	no changes to the stack
*/
TYPE topDynArr(DynArr *v)
{
	assert(v != 0);
	assert(!isEmptyDynArr(v)); //make sure the array is not empty

	return v->data[sizeDynArr(v) - 1]; //return element at the top of the stack
}

/* Removes the element on top of the stack

param:	v		pointer to the dynamic array
pre:	v is not null
pre:	v is not empty
post:	size is decremented by 1
the top has been removed
*/
void popDynArr(DynArr *v)
{
	assert(v != 0);
	assert(!isEmptyDynArr(v));

	removeAtDynArr(v, sizeDynArr(v) - 1);
}

/* ************************************************************************
Bag Interface Functions
************************************************************************ */

/*	Returns boolean (encoded as an int) demonstrating whether or not
the specified value is in the collection
true = 1
false = 0

param:	v		pointer to the dynamic array
param:	val		the value to look for in the bag
pre:	v is not null
pre:	v is not empty
post:	no changes to the bag
*/
int containsDynArr(DynArr *v, TYPE val)
{
	assert(v != 0);
	assert(!isEmptyDynArr(v));

	if (findElement(v, val) != -1)
	{
		return 1;
	}

	return 0;
}

/*	Removes the first occurrence of the specified value from the collection
if it occurs

param:	v		pointer to the dynamic array
param:	val		the value to remove from the array
pre:	v is not null
pre:	v is not empty
post:	val has been removed
post:	size of the bag is reduced by 1
*/
void removeDynArr(DynArr *v, TYPE val)
{
	assert(v != 0);
	assert(!isEmptyDynArr(v));

	int index = findElement(v, val); //find the given element in the bag

	//remove that element from the bag if possible
	if (index != -1)
	{
		removeAtDynArr(v, index);
	}
}

