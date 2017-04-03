/***********************************************************************************************************
** Author: Conrad Lewin
** Date: 11/6/2015
** Description: This derived class makes use of parent class functions to define the blueprint for a
**square, providing functionality to calculate its perimeter, area and to resize its dimensions.
**************************************************************************************************************/
#include "Square.hpp"

//derived class constructor that calls the base class constructor
Square::Square(double len) : Rectangle(len, len)
{
}


/*************************************************************************************************
** Description: This function calls base class mutators to assign a value to the 
** inhereted length and width member variables.
***************************************************************************************************/
void Square::setLength(double l)
{
	Rectangle::setLength(l);
	Rectangle::setWidth(l);
}


/*************************************************************************************************
** Description: This function calls base class mutators to assign a value to the
** inhereted length and width member variables.
***************************************************************************************************/
void Square::setWidth(double w)
{
	Rectangle::setLength(w);
	Rectangle::setWidth(w);
}