/******************************************************************************
** Author: Conrad Lewin
** Date: 10/1/2015
** Description: This program examines a set of integers input by the user
** and finds the smallest and largest number in the set.
*******************************************************************************/
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	int numsToEnter;
	int num;
	int min = 0;
	int max = 0;

	//get the size of the set of integers to examine
	cout << "How many integers would you like to enter ?" << endl;
	cin >> numsToEnter;
 
	if (numsToEnter > 0) //makes sure the size of the set is at least 1
	{
		for(int i = 0; i < numsToEnter; i++) //as long as there is space available in the set...
		{
			//get first number in the set and initialize the minimum and maximum values in the set with this number
			if (i == 0)
			{
				
				cout << "Please enter " << numsToEnter << " integers." << endl;
				cin >> num;

				min = num;
				max = num;
			}
			else
			{
				cin >> num; //get the next number to be entered into the set

				//then compare that number to the current minimum or maximum and, if necessary, reassign either the minimum or the maximum
				if (num <= min)
				{
					min = num;
				}
				else if (num > max)
				{
					max = num;
				}
			}
		}
	}

	//output the minimum and maximum values
	cout << "min: " << min << endl;
	cout << "max: " << max << endl;

	return 0;
}
