/********************************************************************************************
** Author: Conrad Lewin
** Date: 10/09/2015
** Description: This class provides a blueprint for the structure of a line segment
** and allows for the calculation of that line's slope and length.
*********************************************************************************************/
#ifndef LINE_SEGMENT_HPP
#define LINE_SEGMENT_HPP

#include "Point.hpp"

class LineSegment
{
private:
	Point endPoint1;
	Point endPoint2;

public:
	//default constructor
	LineSegment();
	
	//overloaded constructor
	LineSegment(const Point& p1, const Point& p2);

	//getters and setters
	void setEnd1(const Point& p) { endPoint1 = p;    }
	void setEnd2(const Point& p) { endPoint2 = p;    }
	Point getEnd1() const        { return endPoint1; }
	Point getEnd2() const        { return endPoint2; }

	double length(); //calculates the distance between 2 points on a line
	double slope(); //calculates the slope of a line
};

#endif //LINE_SEGMENT_HPP
