/************************************************************************************************************
** Author: Conrad Lewin
** Date: 11/14/2015
** Description: This is a subclass of CustomerProject that provides the functionality to calculate the
** cost of a project done for a preferred customer.
************************************************************************************************************/
#include "PreferredProject.hpp"

//constructor - calls base class constructor
PreferredProject::PreferredProject(double h, double m, double t) : CustomerProject(h, m, t)
{
}

/*************************************************************************************
** Description: This is a virtual function that calculates the cost of a preffered
** customer project.
**************************************************************************************/
double PreferredProject::billAmount()
{
	const double MAX_HOURS = 100.0; //max billable hours

	double numHours = getHours(); //get hours worked
	
	//if the project took less than 100 hours then charge the normal rate, otherwise stop charging the customer after 100 hours
	double hoursCost = numHours >= MAX_HOURS ? hoursCost = 100 * 80.0 : numHours * 80.0; 

	double matCost = getMaterials() * 0.85; //get the cost of materials

	double transCost = getTransportation() * 0.9; //get the cost of transportation

	return hoursCost + matCost + transCost; //return the total cost of the project

}
