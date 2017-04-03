/*********************************************************************************************************
** Author: Conrad Lewin
** Date: 11/6/2015
** Description: This class explores the use of operator overloading and copy constructors.
***********************************************************************************************************/
#include "MyInteger.hpp"
#include <iostream>

//constructor
MyInteger::MyInteger(int x)
{
	//allocate memory for an int and assign it the value of the argument
	pInteger = new int; 
	*pInteger = x; 
}

//copy constructor
MyInteger::MyInteger(const MyInteger &obj)
{
	//allocate memory for an int and assign it the value pointed to by the argument's pInteger member.
	pInteger = new int;
	*pInteger = *obj.pInteger;

}

//destructor
MyInteger::~MyInteger()
{
	delete pInteger;
}


/***********************************************************************************************************
** Description: The function overloads the assignment operator in order to assign the value pointed to
** by the right hand operand to the left hand operand.
************************************************************************************************************/
MyInteger MyInteger::operator=(const MyInteger &right)
{
	delete pInteger; //deallocate memory the calling object uses to store an int

	//allocate memory for an int and assign it the value pointed to by the argument's pInteger member.
	pInteger = new int;
	*pInteger = *right.pInteger;

	return *this; //return the calling object
}
