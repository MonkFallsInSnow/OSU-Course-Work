/************************************************************************************************************
** Author: Conrad Lewin
** Date: 11/14/2015
** Description: This is a subclass of CustomerProject that provides the functionality to calculate the
** cost of a project done for a regular customer.
************************************************************************************************************/
#ifndef REGULAR_PROJECT
#define REGULAR_PROJECT

#include "CustomerProject.hpp"

//subclass of CustomerProject
class RegularProject :
	public CustomerProject
{
public:
	RegularProject(double h, double m, double t); //constructor
	
	virtual double billAmount(); //calculates the cost of a project
};

#endif //REGULAR_PROJECT