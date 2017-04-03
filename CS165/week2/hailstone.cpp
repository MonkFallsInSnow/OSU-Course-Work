/*******************************************************************************************
** Author: Conrad Lewin
** Date: 10/1/2015
** Description: Performs the hailstone sequence and counts the number of steps to reach
** the first resulting 1.
********************************************************************************************/
/*#include <iostream>

using std::cout;
using std::endl; 

int hailstone(int);


int main() 
{
	cout << hailstone(3)<< endl;
	return 0;
}
*/
int hailstone(int num)
{
	int steps = 0; //tracks the number of steps taken to reach the first 1

	/* as long as the current number in the sequence is greater than one,
	** run the hailstone sequence and increment the number of steps
	*/
	while (num > 1) 
	{
		if (num % 2 == 0)
		{
			num /= 2;
		}
		else
		{
			num = (num * 3) + 1;
		}

		steps++;
	}

	return steps;
}
