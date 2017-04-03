/********************************************************************************
** Author: Conrad Lewin
** Date: 10/24/2015
** Description: The stringSort() function uses a selection sort to order an 
** array of strings in ascending order.
*********************************************************************************/
#include <string>

bool compareStrings(const std::string, const std::string); //helper function prototype

/*****************************************MAIN*****************************************************
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

void stringSort(std::string arr[], int arrSize);
bool compareStrings(std::string, std::string);

int main()
{
	const int SIZE = 11;
	string words[SIZE] = { "Zebra", "allegator", "bake", "Base", 
						   "Hostage", "PURPLE", "quarTZ", "PARAble",
						   "LITANY", "BeLt", "purple" };

	for (int i = 0; i < SIZE; i++)
	{
		cout << words[i] << " ";
	}

	cout << endl << endl;

	stringSort(words, SIZE);

	for (int i = 0; i < SIZE; i++)
	{
		cout << words[i] << " ";
	}

	cout << endl << endl;

	return 0;
}
******************************************END MAIN*****************************************************/

/*****************************************************************************************************
** Description: Main Function for this assignment. See the comment header at the top of this .cpp file
** for a description.
******************************************************************************************************/
void stringSort(std::string arr[], int arrSize)
{
	for (int startScan = 0; startScan < arrSize - 1; startScan++)
	{
		int minIndex = startScan; //assume the smallest value in the array is at the current index
		std::string initialMin = arr[minIndex]; //save a copy of that value
		
		for (int index = startScan + 1; index < arrSize; index++)
		{
			//compare the current minimum with the value at the current index, updating, if
			//necessary, the index that stores the smallest known value
			if (compareStrings(arr[index], arr[minIndex]))
			{
				minIndex = index;
			}
		}

		//swap the initial minimum with the new minimum
		arr[startScan] = arr[minIndex];
		arr[minIndex] = initialMin;
	}
}


/***********************************************************************************************************
** Description: Helper function. This function forces all characters in a set of two strings 
** to lowercase and then compares them using the built in compare() function.
************************************************************************************************************/
bool compareStrings(const std::string first, const std::string second)
{
	std::string lowerFirst = ""; //stores the lowercase equivalent of the first argument
	std::string lowerSecond = ""; //stores the lowercase equivalent of the second argument

	//loops through the first string argument converting each character to its lowercase equivalent
	for (int letter = 0; letter < first.size(); letter++)
	{
		lowerFirst += tolower(first[letter]);
	}

	//loops through the second string argument converting each character to its lowercase equivalent
	for (int letter = 0; letter < second.size(); letter++)
	{
		lowerSecond += tolower(second[letter]);
	}

	//compares the the two lowercase strings. if the first string is less than the 
	//the second, then return true otherwise return false
	if (lowerFirst.compare(lowerSecond) < 0)
	{
		return true;
	}

	return false;
}