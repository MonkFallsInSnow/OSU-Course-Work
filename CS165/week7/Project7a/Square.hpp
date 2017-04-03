/***********************************************************************************************************
** Author: Conrad Lewin
** Date: 11/6/2015
** Description: This derived class makes use of parent class functions to define the blueprint for a 
**square, providing functionality to calculate its perimeter, area and to resize its dimensions.
**************************************************************************************************************/
#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "Rectangle.hpp"

//subclass of superclass Rectangle
class Square :
	public Rectangle
{
public:
	Square(double len); //constructor

	//setters
	void setLength(double l);
	void setWidth(double w);
};

#endif // SQUARE_HPP