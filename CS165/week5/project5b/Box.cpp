/******************************************************************************
** Author: Conrad Lewin
** Date: 10/08/1984
** Description: Header file for a class Box. This class is used to define
** the dimensions of a box and calculate both its surface area and volume.
*********************************************************************************/
#include "Box.hpp"

const double Box::DEFAULT_DIMENSION = 1.0;

//default constructor
Box::Box()
{
	setHeight(DEFAULT_DIMENSION);
	setWidth(DEFAULT_DIMENSION);
	setLength(DEFAULT_DIMENSION);
}

//overloaded constructor
Box::Box(double h, double w, double len)
{
	//checks for a valid dimension, before initializing the height, width and length of the box.
	//if the dimension passed to the constructor is invalid, then a default value is applied to the
	//relevant variable
	if (h > 0)
	{
		setHeight(h);
	}
	else
	{
		setHeight(DEFAULT_DIMENSION);
	}

	if (w > 0)
	{
		setWidth(w);
	}
	else
	{
		setWidth(DEFAULT_DIMENSION);
	}

	if (len > 0)
	{
		setLength(len);
	}
	else
	{
		setLength(DEFAULT_DIMENSION);
	}
}

/*******************************************************************************
** Description: Calculates the volume of a right rectangular prism.
********************************************************************************/
double Box::getVolume()
{
	double volume = length * width * height;
	return volume;
}

/*********************************************************************************
** Description: Calculates the surface area of a right rectangular prism.
**********************************************************************************/
double Box::getSurfaceArea()
{
	double surfaceArea = 2 * ((length * width) + (height * length) + (height * width));
	return surfaceArea;
}
