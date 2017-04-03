/************************************************************************************************************
** Author: Conrad Lewin
** Date: 11/14/2015
** Description: This is a subclass of CustomerProject that provides the functionality to calculate the
** cost of a project done for a preferred customer.
************************************************************************************************************/
#ifndef PREFERRED_PROJECT
#define PREFERRED_PROJECT

#include "CustomerProject.hpp"

//subclass of CustomerProject
class PreferredProject :
	public CustomerProject
{
public:
	PreferredProject(double h, double m, double t); //constructor

	virtual double billAmount(); //calculates the cost of a project
};

#endif //PREFERRED_PROJECT