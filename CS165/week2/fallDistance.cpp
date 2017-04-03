/***********************************************************************************
** Author: Conrad Lewin
** Date: 10/1/2015
** Description: Calculates how far an object falls (on Earth) within a certain 
** amount of time.
************************************************************************************/
/*
#include <iostream>

using std::cout; 
using std::endl;

double fallDistance(double);

int main()
{
	cout << fallDistance(3.0) << endl;
	return 0;
}
*/
double fallDistance(double time)
{
	const double GRAVITY = 9.8; //the influence of gravity
	double distance = 0.5 * GRAVITY * (time * time); //the falling distance formula
	return distance; //returns the distance fallen
}
