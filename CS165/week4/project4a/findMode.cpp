/********************************************************************************
** Author: Conrad Lewin
** Date: 10/15/2015
** Description: The findMode() function examines the contents of an int array, counting
** the frequency of each unique value and then returning a vector of the 
** mode or modes therein.
**********************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;

int findMaxFrequency(int arr[], int arrSize);
std::vector<int> findMode(int arr[], int arrSize);

int main()
{
	int const SIZE = 10;
	int arr1[SIZE] = { 2, 1, 3, 5, 4, 0, 7, 8, 6, 9 };
	int arr2[SIZE] = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 };
	int arr3[SIZE] = { 9, 4, 9, 9, 8, 4, 0, 9, 2, 3 };
	int arr4[SIZE] = { 4, 4, 1, 3, 3, 1, 1, 4, 3, 5 };

	std::vector<int> mode1 = findMode(arr1, SIZE);
	std::vector<int> mode2 = findMode(arr2, SIZE);
	std::vector<int> mode3 = findMode(arr3, SIZE);
	std::vector<int> mode4 = findMode(arr4, SIZE);

	for (int i = 0; i < mode1.size(); i++)
	{
		cout << mode1[i] << " ";
	}

	cout << endl;

	for (int i = 0; i < mode2.size(); i++)
	{
		cout << mode2[i] << " ";
	}

	cout << endl;

	for (int i = 0; i < mode3.size(); i++)
	{
		cout << mode3[i] << " ";
	}

	cout << endl;

	for (int i = 0; i < mode4.size(); i++)
	{
		cout << mode4[i] << " ";
	}

	cout << endl;
	return 0;
}

/*********************************************************************************************
** Description: The primary function for this assignment. See the first comment header for a
** full description.
**********************************************************************************************/
std::vector<int> findMode(int arr[], int arrSize)
{
	int count = 0; //tracks the index of a unique value in the set
	std::vector<int> modes;
	int max = findMaxFrequency(arr, arrSize); //get the highest frequency of values

	//count each unique value in the set and compare that count with the max frequency, adding
	//the most frequently occuring values to the modes vector
	for (int i = 0; i < arrSize; i = count)
	{
		int current = arr[i]; //get the currently examined value (bypassing the duplicates of the previously examined value)
		int freq = 0;

		//count the number of duplicates
		while (current == arr[count])
		{
			freq++;
			count++;
		}

		//compare current's frequency to the max frequency, adding current 
		//to the modes vector if its frequency is high enough
		if (freq == max)
		{
			modes.push_back(current);
		}
	}

	return modes;
}

/****************************************************************************************
Description: Finds the largest number of duplicates in an array.
*****************************************************************************************/
int findMaxFrequency(int arr[], int arrSize)
{
	int count = 0; //tracks the index of a unique value in the set
	int max = 0;

	std::sort(arr, arr + arrSize); //sort the array

	//count the number of times a each value is duplicated within the array, getting
	//the highest rate of duplication
	for (int i = 0; i < arrSize; i = count)
	{
		int current = arr[i]; //get the currently examined value (bypassing the duplicates of the previously examined value)
		int freq = 0;

		//count the number of duplicates
		while (current == arr[count])
		{
			freq++;
			count++;
		}

		//compare each frequency with the current max, adjusting the max when necessary
		if (freq > max)
		{
			max = freq;
		}
	}

	return max;
}
