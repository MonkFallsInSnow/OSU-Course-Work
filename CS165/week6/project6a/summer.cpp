/*********************************************************************************************************************
** Author: Conrad Lewin
** Date: 10/30/2015
** Description: This is a recursive function that gets the sum of each element in an array of doubles.
**********************************************************************************************************************/

/**********************************************************MAIN******************************************************
#include <iostream>

using std::cout;
using std::endl;

double summer(double arr[], int arrSize);

int main()
{
	const int SIZE = 5;
	double arr[SIZE] = { 1.0, 1.0, 1.0, 1.0, 1.0 };
	double sum = summer(arr, SIZE);
	for (int i = 0; i < SIZE; i++)
	{
		cout << arr[i];
		if (i != SIZE - 1)
		{
			cout << " + ";
		}
	}
	cout << sum << endl;
	return 0;
}
*********************************************************END MAIN*****************************************************/

double summer(double arr[], int arrSize)
{
	//base case
	//the integer that represents the size of the array is decremented with each function call
	if (arrSize == 0)
	{
		return 0.0;
	}

	//get an element in the array that has an index of the actual size of the array minus how many function calls
	//have been made prior to the current call.
	double sum = arr[arrSize - 1]; 

	//add the current call's sum to the value of sum in subsequent calls.
	return sum + summer(arr, arrSize - 1); 
}