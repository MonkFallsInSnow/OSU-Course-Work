/********************************************************************
 * Author: Conrad Lewin
 * Date: 9/25/2015
 * Description: Converts a temperature in Celsisus to Fahrenheit.
 * ******************************************************************/

#include<iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	float tempCelsisus, tempFahrenheit;
        
	//gets a temperature in Celsius 
	cout << "Please enter a Celsius temperature." << endl; 
	cin >> tempCelsisus;

	tempFahrenheit = ((9.0 / 5.0) * tempCelsisus) + 32; //conversion formula. converts Celsisus to Farenheit

	//outputs the temperature in Fahrenheit
	cout << "The equivalent Fahrenheit temperature is:" << endl;
	cout << tempFahrenheit << endl;

	return 0;
}
