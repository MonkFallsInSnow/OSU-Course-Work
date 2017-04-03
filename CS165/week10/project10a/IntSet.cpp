/******************************************************************************************************
** Author: Conrad Lewin
** Date: 11/29/2015
** Description: This class provides the blueprint for a mathematical set of integers. Functionality
** includes searching the set for an element, adding/removing elements and calculating unions,
** intersections and differences between 2 or more sets.
**********************************************************************************************************/
#include "IntSet.hpp"

//constructor
IntSet::IntSet(int size)
{
	if (size <= 0) //force a set size of 1 if a set of size 0 is created
	{
		maxSize = 1;
	}
	else //otherwise assign the set's capacity
	{
		maxSize = size;
	}

	set = new int[maxSize]; //allocate space for the set
	numElements = 0; //initialize the number of elements
}

//copy constructor
IntSet::IntSet(const IntSet& obj)
{
	maxSize = obj.maxSize; //copy the capacity of the argument's set
	set = new int[maxSize]; //allocate space for a set of integers
	numElements = 0; //initialize the number of elements

	for (int i = 0; i < obj.size(); i++) //copy all element from the argument's set into a new set
	{
		add(obj.set[i]);
	}
}

//destructor
IntSet::~IntSet()
{
	delete[] set; //destroy the set
}


/*********************************************************************************************************
** Description: Standard binary search that returns the index in which an element in an array is
** found.
**********************************************************************************************************/
int IntSet::binarySearch(int key) const
{
	int maxIndex = size() - 1;
	int minIndex = 0;
	int searchIndex = maxIndex / 2;

	while (minIndex <= maxIndex)
	{
		if (set[searchIndex] == key)
		{
			return searchIndex;
		}
		else if (key > set[searchIndex])
		{
			minIndex = searchIndex + 1;
		}
		else if (set[searchIndex] > key)
		{
			maxIndex = searchIndex - 1;
		}

		searchIndex = (maxIndex + minIndex) / 2;
	}

	return -1;
}

/******************************************************************************************************
** Description: Checks the number of elements in a set and returns a flag that indicates whether or
** not the set is empty.
*******************************************************************************************************/
bool IntSet::isEmpty() const
{
	if (size() == 0)
	{
		return true;
	}

	return false;
}


/*********************************************************************************************************
** Description: Searches the set for a user specified element and returns a flag indicating whether
** or not the element was found.
***********************************************************************************************************/
bool IntSet::contains(int key) const
{
	if (!isEmpty()) //check for an empty set before performing the search
	{
		int pos = binarySearch(key); //get the position of the element

		if (pos != -1) //if a valid position was returned by the binary search then indicate the element was found
		{
			return true;
		}
	}

	return false; //otherwise indicate the element was not found
}


/**********************************************************************************************************
** Description: Adds an element to the set. If the set is at capacity, this function will create a new
** array twice the size of the original and copies all elements in the original array into the new array.
***********************************************************************************************************/
void IntSet::add(int key)
{
	if (!contains(key)) //check for a duplicate element already present in the set
	{
		if (size() == maxSize) //if the set is at capacity
		{
			maxSize *= 2; //double the capacity of the set
			int* newSet = new int[maxSize]; //create a new set with this new capacity

			for (int i = 0; i < size(); i++) //copy all elements from the original set to this new set
			{
				newSet[i] = set[i];
			}

			newSet[numElements++] = key; //add the given element to the set
			delete[] set; //delete the original set
			set = newSet; //assign the new set to take the place of the old set
		}
		else //otherwise, if the set is not at capacity
		{
			set[size()] = key;  //add the element to the set
			numElements++; //update the number of elements in the set
		}
	}
	
	if (size() > 1) //if there is more than one element in the set, then sort the set
	{
		std::sort(set, set + size());
	}

	return;
}


/*********************************************************************************************************
** Description: Searches the set for the given element and removes it from the set.
**********************************************************************************************************/
void IntSet::remove(int key)
{
	if (!isEmpty()) //check for an empty set
	{
		int pos = binarySearch(key); //get the position of the element marked for removal

		if (pos != -1) //if that element is in the set
		{
			for (int i = pos; i < size(); i++) //overwrite that element by shifting all other elements indexed after it to the left one space
			{
				set[i] = set[i + 1];
			}

			numElements--; //update the number of elements
		}
	}
	return;
}


/*********************************************************************************************************
** Description: Calculates the union of two or more sets, returning the set that represents that union.
**********************************************************************************************************/
IntSet IntSet::getUnion(const IntSet& obj) const
{
	IntSet unionSet = *this; //initialize a new set with the elements of the calling set

	for (int i = 0; i < obj.size(); i++) //loop through the set given as an argument
	{
		if (!unionSet.contains(obj.set[i])) //if the current element is not already in the union set...
		{
			unionSet.add(obj.set[i]); //add that element to the union set
		}
	}

	return unionSet; //return the union
}


/*********************************************************************************************************
** Description: Calculates the intersection of two or more sets, returning the set that represents 
** that intersection.
**********************************************************************************************************/
IntSet IntSet::getIntersection(const IntSet& obj) const
{
	IntSet interSet;

	for (int i = 0; i < obj.size(); i++) //loop through the set given as an argument
	{
		if (this->contains(obj.set[i])) //if the calling set contains the argument's current element...
		{
			interSet.add(obj.set[i]); //add that element to the intersection set
		}
	}
	
	return interSet; //return the intersection
}


/*********************************************************************************************************
** Description: Calculates the difference of two or more sets, returning the set that represents 
** that difference.
**********************************************************************************************************/
IntSet IntSet::getDifference(const IntSet& obj) const
{
	IntSet diffSet = *this; //initialize a new set with the elements of the calling set

	for (int i = 0; i < obj.size(); i++) //loop through the set given as an argument
	{
		if (diffSet.contains(obj.set[i])) //if the current element is in the difference set...
		{
			diffSet.remove(obj.set[i]); //then remove that element from the difference set
		}
	}

	return diffSet; //return the difference set
}


/*******************************************************************************************************
** Description: Overloads the assignment operator, allowing the user to copy all the elements
** in one set into another using the assignment operator.
********************************************************************************************************/
IntSet& IntSet::operator=(const IntSet& right)
{
	delete[] set; //delete the set in the left hand operand
	set = NULL;

	maxSize = right.maxSize; //copy the right hand operand's set capacity into the left hand operand
	set = new int[maxSize]; //create a new set with this adjusted capacity in the left hand operand

	for (int i = 0; i < right.size(); i++) //copy each element in the right hand operand into the left hand operand
	{
		add(right.set[i]);
	}

	numElements = right.size(); //update the number of element in the left hand operand

	return *this;
}


/******************************************************************************************************************
** Description: Overloads the equality operator, allowing the user to compare two sets in order to determine
** whether or not both sets have identical elements.
*******************************************************************************************************************/
bool IntSet::operator==(const IntSet& right)
{
	if (!this->isEmpty() && !right.isEmpty()) //checks the number of elements in each set, if neither is empty...
	{
		for (int i = 0; i < size(); i++) //loop through the calling object's set
		{
			if (set[i] != right.set[i]) //check the element at the current index in both sets (both sets are guaranteed to be ordered.)
			{
				return false; //return false as soon as a mismatch is found
			}
		}
		
		return true; //otherwise return true, indicating that the sets are equal
	}
	else if (this->isEmpty() && right.isEmpty()) //if both are empty, then return a flag indicating the sets are equal
	{
		return true;
	}

	return false; //if one set is empty and the other is not, return a flag indicating the sets are unequal
}
