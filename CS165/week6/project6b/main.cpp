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
	cout << "Decimal: " << decNum6 << "  Binary: " << decToBin(decNum6) << endl;
	cout << endl;	
}
