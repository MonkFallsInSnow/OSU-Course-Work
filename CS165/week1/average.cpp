/****************************************************************
 * Author: Conrad Lewin
 * Date: 9/25/2015
 * Description: Calculates the average of five numbers.
 * *************************************************************/

#include<iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	const int TOTAL_NUMS = 5; //max amount of numbers to average
	float num1, num2, num3, num4, num5,avg;
        
	//get and store numbers input by the user
	cout << "Please enter five numbers." << endl;
	cin >> num1;
	cin >> num2;
	cin >> num3;
	cin >> num4;
	cin >> num5;
	        
	avg = (num1 + num2 + num3 + num4 + num5) / TOTAL_NUMS; //calculate average

	cout << "The average of those numbers is: " << endl << avg << endl; //output the average

	return 0;
}
