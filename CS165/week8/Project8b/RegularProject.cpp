/************************************************************************************************************
** Author: Conrad Lewin
** Date: 11/14/2015
** Description: This is a subclass of CustomerProject that provides the functionality to calculate the
** cost of a project done for a regular customer.
************************************************************************************************************/
#include "RegularProject.hpp"

//constructor - calls base class constructor
RegularProject::RegularProject(double h, double m, double t) : CustomerProject(h, m, t)
{
}

/*************************************************************************************
** Description: This is a virtual function that calculates the cost of a regular
** customer project.
**************************************************************************************/
double RegularProject::billAmount()
{
	return (80.0 * getHours()) + getMaterials() + getTransportation(); //return the total cost of the project
}
