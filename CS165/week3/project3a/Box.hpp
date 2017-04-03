/******************************************************************************
** Author: Conrad Lewin
** Date: 10/08/1984
** Description: Header file for a class Box. This class is used to define 
** the dimensions of a box and calculate both its surface area and volume.
*********************************************************************************/
#ifndef BOX_HPP
#define BOX_HPP
class Box
{
private:
	static const double DEFAULT_DIMENSION; //default valued used in the default constructor

	//dimensions of the box
	double height;
	double width;
	double length;

public:
	Box();
	Box(double h, double w, double l);

	//setters
	void setHeight(double h) { height = h; }
	void setWidth(double w)  { width = w;  }
	void setLength(double l) { length = l; }

	double getVolume(); //gets volume of the box
	double getSurfaceArea(); //gets surface area of the box
};

#endif //BOX_HPP