/*******************************************************************
 * Author: Conrad Lewin
 * Date: 9/25/2015
 * Description: Accepts an amount of cents less than a dollar and
 * outputs the fewest number of coins needed to equal the user 
 * specified amount.
 * *****************************************************************/

#include<iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	//constant values that represent the different coin values
	const int QUARTER_VALUE = 25;
	const int DIME_VALUE = 10;
	const int NICKEL_VALUE = 5;
	const int PENNY_VALUE = 1;

	int cents, quarters, dimes, nickels, pennies;

	//get the amount of cents
	cout << "Please enter an amount in cents less than a dollar." << endl;
	cin >> cents;

	quarters = cents / QUARTER_VALUE; //get the max number of quarters 
	cents -= QUARTER_VALUE * quarters; //modify the amount of cents to reflect the deduction of quarters from the amount 

	dimes = cents / DIME_VALUE; //get the max number of dimes
	cents -= DIME_VALUE * dimes; //modify the amount of cents to reflect the deduction of dimes from the amount

	nickels = cents / NICKEL_VALUE; //get the max number of nickels
	cents -= NICKEL_VALUE * nickels; //modify the amount of cents to reflect the deduction of nickels from the amount

	pennies = cents / PENNY_VALUE; //get the max number of pennies. the remaining amount

	//output the number of quarters, dimes, nickels and pennies that comprise the original amount of cents
	cout << "Your change will be:" << endl;
	cout << "Q: " << quarters	   << endl;
	cout << "D: " << dimes		   << endl;
	cout << "N: " << nickels	   << endl;
	cout << "P: " << pennies	   << endl;

	return 0;
}
