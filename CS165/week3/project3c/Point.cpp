/********************************************************************************************
** Author: Conrad Lewin
** Date: 10/09/2015
** Description: This class enumerates the characteristics of a point
** and allows for the calculation of distance between two points.
*********************************************************************************************/
#include "Point.hpp"

const double Point::DEFAULT_COORD = 0.0;

//default constructor
Point::Point()
{
	setXCoord(DEFAULT_COORD);
	setYCoord(DEFAULT_COORD);
}

//overloaded constructor
Point::Point(double xCoord, double yCoord)
{
	setXCoord(xCoord);
	setYCoord(yCoord);
}

/*****************************************************************************************
** Description: Uses the distance formula to calculate the distance between two
** points on a line.
******************************************************************************************/
double Point::distanceTo(const Point& p2)
{
	double distance = sqrt(pow((x - p2.getXCoord()), 2) + pow((y - p2.getYCoord()), 2));
	return distance;
}