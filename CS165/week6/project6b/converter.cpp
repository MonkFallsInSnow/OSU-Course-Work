/***********************************************************************************************************************
** Author: Conrad Lewin
** Date: 10/30/2015
** Description: This file contains two functions that convert decimals to binary and vice versa.
************************************************************************************************************************/

/***************************************************************MAIN***************************************************
#include <iostream>
#include <string>
#include <iomanip>

using std::cout;
using std::endl;

int binToDec(std::string num);
std::string decToBin(int num);

int main()
{
	std::string binNum1 = "111";
	std::string binNum2 = "00000";
	std::string binNum3 = "1101010";
	std::string binNum4 = "101110";
	std::string binNum5 = "0";
	std::string binNum6 = "1";

	int decNum1 = 0;
	int decNum2 = 1;
	int decNum3 = 114;
	int decNum4 = 3431;
	int decNum5 = 68;
	int decNum6 = 5;

	cout << "Binary: " << binNum1 << "  Decimal: " << binToDec(binNum1) << endl;
	cout << "Binary: " << binNum2 << "  Decimal: " << binToDec(binNum2) << endl;
	cout << "Binary: " << binNum3 << "  Decimal: " << binToDec(binNum3) << endl;
	cout << "Binary: " << binNum4 << "  Decimal: " << binToDec(binNum4) << endl;
	cout << "Binary: " << binNum5 << "  Decimal: " << binToDec(binNum5) << endl;
	cout << "Binary: " << binNum6 << "  Decimal: " << binToDec(binNum6) << endl;
	cout << endl;
	cout << "Decimal: " << decNum1 << "  Binary: " << decToBin(decNum1) << endl;
	cout << "Decimal: " << decNum2 << "  Binary: " << decToBin(decNum2) << endl;
	cout << "Decimal: " << decNum3 << "  Binary: " << decToBin(decNum3) << endl;
	cout << "Decimal: " << decNum4 << "  Binary: " << decToBin(decNum4) << endl;
	cout << "Decimal: " << decNum5 << "  Binary: " << decToBin(decNum5) << endl;
	cout << "Decimal: " << decNum6 << "  Binary: " << decToBin(decNum6) << endl << endl;
}
*************************************************************END MAIN************************************************************/

#include <string>
#include <cmath>

int binToDecRec(std::string num, int index);
std::string decToBinRec(int num, bool isZero);

/******************************************************************************************************************
** Description: Calls a recursive helper function to convert a binary representation of an integer to a decimal.
*******************************************************************************************************************/
int binToDec(std::string num)
{
	//calls the recursive version of this function
	return binToDecRec(num, 0);
}

/******************************************************************************************************************
** Description: Recursive helper function that converts the binary representation of an integer to a decimal.
*******************************************************************************************************************/
int binToDecRec(std::string num, int index)
{
	int digit;

	//base case - return 0 once all character's in the string have been examined
	if (index == num.size())
	{
		return 0;
	}

	//converts the first character in the string to an int
	switch (num[index])
	{
	case '0':
		digit = 0;
		break;
	case '1':
		digit = 1;
		break;
	default:
		break;
	}

	//multiply the current digit by a power of 2. Because the string is read from left to right and binary digits
	//are read from right to left, the powers of 2 are determined from largest to smallest 
	int value = digit * static_cast<int>(pow(2, num.size() - (++index )));

	//add the int stored in the current call's value variable to the int stored in value of a subsequent call
	return value + binToDecRec(num, index);

}

/******************************************************************************************************************
** Description: Calls a recursive helper function that converts a decimal representation of an integer to binary.
*******************************************************************************************************************/
std::string decToBin(int num)
{
	//calls the recursive version of this function
	return decToBinRec(num,true);
}

/******************************************************************************************************************
** Description: Recursive helper function that converts the binary representation of an integer to a decimal.
*******************************************************************************************************************/
std::string decToBinRec(int num, bool isZero)
{
	std::string digit;

	//base case
	if (num == 0)
	{
		if (isZero)
			return "0";
		else
			return "";
	}

	//get the remainder produced when num is divided by 2
	int remainder = num % 2;

	//convert the int value stored in variable remainder to a string
	switch (remainder)
	{
	case 0:
		digit = "0";
		break;
	case 1:
		digit = "1";
		break;
	default:
		break;
	}

	//divide the argument by 2 and have the function call itself with the quotient
	std::string value = decToBinRec(num / 2, false);


	//concatenate the string returned by the current call with the string returned by subsequent calls
	return value + digit;
}