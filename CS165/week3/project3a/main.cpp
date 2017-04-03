#include "Box.hpp"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	Box box1;
	Box box2(7.5, 5.25, 8.1);
	Box box3(5, -1, -8);

	double volume1 = box1.getVolume();
	double volume2 = box2.getVolume();
	double volume3 = box3.getVolume();
	double surfaceArea1 = box1.getSurfaceArea();
	double surfaceArea2 = box2.getSurfaceArea();
	double surfaceArea3 = box3.getSurfaceArea();

	cout << "Box 1 volume: " << volume1 << endl;
	cout << "Box 2 volume: " << volume2 << endl;
	cout << "Box 3 volume: " << volume3 << endl << endl;

	cout << "Box 1 surface area: " << surfaceArea1 << endl;
	cout << "Box 2 surface area: " << surfaceArea2 << endl;
	cout << "Box 3 surface area: " << surfaceArea3 << endl;

	return 0;
}