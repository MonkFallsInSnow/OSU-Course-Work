/************************************************************************************************************
** Author: Conrad Lewin
** Date: 11/14/2015
** Description: This is an abstract base class that serves as an interface for a derived class(es).
************************************************************************************************************/
#include "CustomerProject.hpp"

//base class constructor
CustomerProject::CustomerProject(double h, double m, double t)
{
	setHours(h);
	setMaterials(m);
	setTransportation(t);
}

