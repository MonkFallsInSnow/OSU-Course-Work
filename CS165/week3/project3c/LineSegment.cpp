/********************************************************************************************
** Author: Conrad Lewin
** Date: 10/09/2015
** Description: This class provides a blueprint for the structure of a line segment
** and allows for the calculation of that line's slope and length.
*********************************************************************************************/
#include "LineSegment.hpp"

//default constructor
LineSegment::LineSegment()
{
	Point p1;
	Point p2;

	setEnd1(p1);
	setEnd2(p2);
}

//overloaded constructor
LineSegment::LineSegment(const Point& p1, const Point& p2)
{
	setEnd1(p1);
	setEnd2(p2);
}

/********************************************************************************************
** Description: Calls the Point class's distanceTo() function get get the distance 
** between two points on a line.
*********************************************************************************************/
double LineSegment::length()
{
	double distance = endPoint1.distanceTo(endPoint2);
	return distance;
}

/********************************************************************************************
** Description: Uses the slope formula to calculate the slope of a line
*********************************************************************************************/
double LineSegment::slope()
{
	double slope = (endPoint1.getYCoord() - endPoint2.getYCoord()) / (endPoint1.getXCoord() - endPoint2.getXCoord());
	return slope;
}
