/************************************************************************************************************
** Author: Conrad Lewin
** Date: 11/14/2015
** Description: This is an abstract base class that serves as an interface for a derived class(es).
************************************************************************************************************/
#ifndef CUSTOMER_PROJECT
#define CUSTOMER_PROJECT

class CustomerProject //abstract base class
{
private:
	double hours;
	double materials;
	double transportation;

public:
	CustomerProject(double h, double m, double t); //constructor

	virtual double billAmount() = 0; //pure virtual function

	//getters
	double getHours() const			 { return hours;          }
	double getMaterials() const		 { return materials;	  }
	double getTransportation() const { return transportation; }

	//setters
	void setHours(double h)			 { hours = h;		   }
	void setMaterials(double m)		 { materials = m;	   }
	void setTransportation(double t) { transportation = t; }
};

#endif //CUSTOMER_PROJECT

/************************************************MAIN**********************************************************************
#include "PreferredProject.hpp"
#include "RegularProject.hpp"
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

int main()
{
	string line = "------------------------------";
	RegularProject project1(120.5, 500.75, 125);
	PreferredProject project2(120.25, 500.75, 125);
	PreferredProject project3(80.5, 320.75, 125);

	cout << "Project 1 - Regular Rate" << endl;
	cout << line << endl;
	cout << "Total Hours: " << project1.getHours() << endl;
	cout << "Material Costs: $" << project1.getMaterials() << endl;
	cout << "Transportation Costs: $" << project1.getTransportation() << endl;
	cout << "Cost: $" << project1.billAmount() << endl << endl;

	cout << "Project 2 - Prefered Rate" << endl;
	cout << line << endl;
	cout << "Total Hours: " << project2.getHours() << endl;
	cout << "Material Costs: $" << project2.getMaterials() << endl;
	cout << "Transportation Costs: $" << project2.getTransportation() << endl;
	cout << "Cost: $" << project2.billAmount() << endl << endl;

	cout << "Project 3 - Prefered Rate" << endl;
	cout << line << endl;
	cout << "Total Hours: " << project3.getHours() << endl;
	cout << "Material Costs: $" << project3.getMaterials() << endl;
	cout << "Transportation Costs: $" << project3.getTransportation() << endl;
	cout << "Cost: $" << project3.billAmount() << endl << endl;
}
*****************************************************END MAIN****************************************************/