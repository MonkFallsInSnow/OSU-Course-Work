/****************************************************************************************************************
** Author: Conrad Lewin
** Date: 10/24/2015
** Description: This function uses the bubble sort to order an array of Box objects in descending order.
*****************************************************************************************************************/

/*****************************************************MAIN***************************************************************
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
/*****************************************************END MAIN***************************************************************/

#include "Box.hpp"

void boxSort(Box box[], int arrSize)
{
	//countdown from the last element in the array. because the smallest value
	//will "bubble" up on each pass toward the end of the array there is no need to recheck those elements
	for (int count = arrSize - 1; count >= 0; count--) 
	{
		//loop through the array, examining only those values that have not yet been sorted 
		for (int index = 0; index < count; index++)
		{
			//compare the volume of adjacent Box objects, swapping the smaller volume with the larger
			if (box[index].getVolume() < box[index + 1].getVolume())
			{
				Box temp = box[index];
				box[index] = box[index + 1];
				box[index + 1] = temp;
			}
		}
	}
}

