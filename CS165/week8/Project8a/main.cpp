#include "ShiftVec.hpp"
#include <iostream>
#include<string>

using std::cout;
using std::endl;

template<class T>
void displayVect(std::vector<T> v);

int main()
{
	std::vector<int> vect1; 
	vect1.push_back(23);
	vect1.push_back(2);
	vect1.push_back(17);
	vect1.push_back(12);
	vect1.push_back(4);

	std::vector<double> vect2;
	vect2.push_back(1.5);
	vect2.push_back(2.1);
	vect2.push_back(3.21);
	vect2.push_back(4.09);
	vect2.push_back(5.4);

	std::vector<std::string> vect3;
	vect3.push_back("ab");
	vect3.push_back("cd");
	vect3.push_back("ef");
	vect3.push_back("gh");
	vect3.push_back("ij");

	std::vector<bool> vect4;
	vect4.push_back(true);
	vect4.push_back(false);
	vect4.push_back(false);
	vect4.push_back(true);
	vect4.push_back(false);

	ShiftVec<int> intVect(vect1);
	ShiftVec<double> doubleVect(vect2);
	ShiftVec<std::string> stringVect(vect3);
	ShiftVec<bool> boolVect(vect4);

	//shift intVect right
	intVect.shiftRight(12);
	std::vector<int> intResult = intVect.getVec();
	cout << "Shift right 12 steps: ";
	displayVect(intResult);
	
	cout << endl << endl;

	//shift intVect left
	intVect.shiftLeft(2);
	intResult = intVect.getVec();
	cout << "Shift left 2 steps: ";
	displayVect(intResult);

	cout << endl << endl;

	//shift doubleVect right
	doubleVect.shiftRight(6);
	std::vector<double> doubleResult = doubleVect.getVec();
	cout << "Shift right 6 steps: ";
	displayVect(doubleResult);

	cout << endl << endl;

	//shift doubleVect left
	doubleVect.shiftLeft(2);
	doubleResult = doubleVect.getVec();
	cout << "Shift left 2 steps: ";
	displayVect(doubleResult);

	cout << endl << endl;

	//shift stringVect right
	stringVect.shiftRight(3);
	std::vector<std::string> stringResult = stringVect.getVec();
	cout << "Shift right 3 steps: ";
	displayVect(stringResult);

	cout << endl << endl;

	//shift stringVect left
	stringVect.shiftLeft(3);
	stringResult = stringVect.getVec();
	cout << "Shift left 3 steps: ";
	displayVect(stringResult);

	cout << endl << endl;

	//shift boolVect right
	boolVect.shiftRight(2);
	std::vector<bool> boolResult = boolVect.getVec();
	cout << "Shift right 2 steps: ";
	displayVect(boolResult);

	cout << endl << endl;

	//shift boolVect left
	boolVect.shiftLeft(6);
	boolResult = boolVect.getVec();
	cout << "Shift left 6 steps: ";
	displayVect(boolResult);

	cout << endl << endl;

	return 0;
}

template<class T>
void displayVect(std::vector<T> v)
{
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
}