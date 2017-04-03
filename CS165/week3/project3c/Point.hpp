/********************************************************************************************
** Author: Conrad Lewin
** Date: 10/09/2015
** Description: This class ennumerates the characteristics of a point
** and allows for the calculation of distance between two points.
*********************************************************************************************/
#ifndef POINT_HPP
#define POINT_HPP

#include <cmath>

class Point
{
private:
	static const double DEFAULT_COORD; //default coordinate value
	double x;
	double y;

public:
	//constructors
	Point();
	Point(double xCoord, double yCoord);

	//getters and setters
	void setXCoord(double coord) { x = coord; }
	void setYCoord(double coord) { y = coord; }
	double getXCoord() const     { return x; }
	double getYCoord() const     { return y; }

	double distanceTo(const Point&); //calculates the distance between two points
};

#endif //POINT_H