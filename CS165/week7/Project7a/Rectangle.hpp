/***********************************************************************************************************
** Author: Conrad Lewin
** Date: 11/6/2015
** Description: This base class provides the blueprint for a rectangle, providing functionality to
** calculate the rectangle's perimeter, area and to resize its dimensions.
**************************************************************************************************************/
#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

class Rectangle
{
private:
	double length;
	double width;

public:
	Rectangle(double l, double w); //constructor

	//setters
	void setLength(double l) { length = l; }
	void setWidth(double w)  { width = w;  }

	double area(); //calculates the area of a rectangle
	double perimeter(); //calculates the perimeter of a rectangle
};

#endif //RECTANGLE_HPP
