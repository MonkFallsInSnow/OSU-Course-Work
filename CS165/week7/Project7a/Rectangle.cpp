/***********************************************************************************************************
** Author: Conrad Lewin
** Date: 11/6/2015
** Description: This base class provides the blueprint for a rectangle, providing functionality to
** calculate its perimeter, area and to resize its dimensions.
**************************************************************************************************************/
#include "Rectangle.hpp"

//constructor
Rectangle::Rectangle(double l, double w)
{
	setLength(l);
	setWidth(w);
}


/*************************************************************************************************
** Description: This function calculates the area of a rectangle.
***************************************************************************************************/
double Rectangle::area()
{
	return length * width;
}


/*************************************************************************************************
** Description: This function calculates the perimeter of a rectangle.
***************************************************************************************************/
double Rectangle::perimeter()
{
	return (2 * length) + (2 * width);
}


