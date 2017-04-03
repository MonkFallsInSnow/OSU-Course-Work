/****************************************************************************************************
** Author: Conrad Lewin
** Date: 10/1/2015
** Description: Sorts a small set of integers in ascending order
*****************************************************************************************************/
/*
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

void smallSort(int&, int&, int&);
void initialSort(int&, int&);

int main() //main function should be removed or commented out before submitting to TEACH
{
	int a = 14;
	int b = -90;
	int c = 2;
	smallSort(a, b, c);
	cout << a << ", " << b << ", " << c << endl;
	return 0;
}
*/
void smallSort(int& num1, int& num2, int& num3)
{
	int temp; //used to temporarily save values

	initialSort(num1,num2);

	//compare the second and third numbers in the set
	if (num2 > num3)
	{
		//if second number is greater than the third, then swap the numbers
		temp = num2;
		num2 = num3;
		num3 = temp;

		initialSort(num1,num2);
	}
}

/***************************************************************************
** Description: Helper function used by smallSort(). Compares the first 
** and second numbers in the set. This operation is done twice, so this
** function was created.
*****************************************************************************/
void initialSort(int &num1, int &num2)
{
	int temp; //used to temporarily save values

	//if first number is greater than the second, then swap the numbers
	if (num1 > num2)
	{
		temp = num1;
		num1 = num2;
		num2 = temp;
	}
}
