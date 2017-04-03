#include "Box.hpp"
#include <iostream>

using std::cout;
using std::endl;

void boxSort(Box box[], int arrSize);

int main()
{
	const int SIZE = 5;
	Box volumes[SIZE];

	Box b1(3, 4, 5);
	Box b2(1, 2, 3);
	Box b3(8, 1, 3);
	Box b4;
	Box b5(1, 2, 3);

	volumes[0] = b1;
	volumes[1] = b2;
	volumes[2] = b3;
	volumes[3] = b4;
	volumes[4] = b5;

	for (int i = 0; i < SIZE; i++)
	{
		cout << volumes[i].getVolume() << endl;
	}

	cout << endl;
	boxSort(volumes, SIZE);

	for (int i = 0; i < SIZE; i++)
	{
		cout << volumes[i].getVolume() << endl;
	}
}
