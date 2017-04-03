/******************************************************************************************************
** Author: Conrad Lewin
** Date: 11/29/2015
** Description: This class provides the blueprint for a mathematical set of integers. Functionality
** includes searching the set for an element, adding/removing elements and calculating unions,
** intersections and differences between 2 or more sets.
**********************************************************************************************************/

#ifndef INT_SET_H
#define INT_SET_H

#include <algorithm>

class IntSet
{
private:
	int* set;
	int maxSize;
	int numElements;
	int binarySearch(int) const;

public:
	IntSet(int size = 10);
	IntSet(const IntSet&);
	~IntSet();

	//member functions
	int size() const { return numElements; } //get the number of elements in the set
	bool isEmpty() const; //checks for an empty set
	bool contains(int) const; //checks for a particular element in the set
	void add(int); //adds an element to the set
	void remove(int); //removes an element from the set
	IntSet getUnion(const IntSet&) const; //calculates the union of 2 or more sets
	IntSet getIntersection(const IntSet&) const; //calculates the intersection of 2 or more sets
	IntSet getDifference(const IntSet&) const; //calculates the difference of 2 or more sets

	//overloaded operators
	IntSet& operator=(const IntSet&);
	bool operator==(const IntSet&);
};

#endif //INT_SET_H