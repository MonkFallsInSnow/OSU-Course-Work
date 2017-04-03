/*****************************************************************************
** Author: Conrad Lewin
** Date: 11/14/2015
** Description: This is a template class that takes a generic vector and
** and provides an interface with which to shift the elements of that vector
** left or right.
*********************************************************************************/
#include "ShiftVec.hpp"
#include <string>

//constructor
template<class T>
ShiftVec<T>::ShiftVec(std::vector<T> vect)
{
	this->vect = vect;
}

/********************************************************************************
** Description: Shifts the elements of the vector member variable a client
** specified number of steps to the right. Elements that have reached the end
** of the vector will wrap around to the front.
*********************************************************************************/
template<class T>
void ShiftVec<T>::shiftRight(int steps)
{
	const int FRONT = 0; //marks the beginning of the vector
	const int BACK = vect.size() - 1; //marks the end of the vector
	T temp; //generic temp variable 

	//base case
	if (steps == 0)
		return;

	temp = vect[BACK]; //saves a copy of the last element in the vector

	//starts at the second to last element in the vector, pushing the current element into
	//the index ahead of it
	for (int i = vect.size() - 2; i >= 0; i--)
	{
		vect[i + 1] = vect[i];
	}

	//*start = temp; //assigns a saved copy of the last element to the first element in the vector
	vect[FRONT] = temp;
	shiftRight(steps - 1); //recursive call to continue shifting elements
}

/********************************************************************************
** Description: Shifts the elements of the vector member variable a client
** specified number of steps to the left. Elements that have reached the front
** of the vector will wrap around to the back.
*********************************************************************************/
template<class T>
void ShiftVec<T>::shiftLeft(int steps)
{
	const int FRONT = 0; //marks the beginning of the vector
	const int BACK = vect.size() - 1; //marks the end of the vector
	T temp; //generic temp variable

	//base case
	if (steps == 0)
		return;

	temp = vect[FRONT];
	//loops through the vector, pushing the current element into
	//the index ahead of it
	for (int i = 0; i < vect.size() - 1; i++)
	{
		vect[i] = vect[i + 1];
	}

	vect[BACK] = temp; //assigns a saved copy of the first element to the last element in the vector
	shiftLeft(steps - 1); //recursive call to continue shifting elements
}

template class ShiftVec<int>;
template class ShiftVec<double>;
template class ShiftVec<bool>;
template class ShiftVec<std::string>;
