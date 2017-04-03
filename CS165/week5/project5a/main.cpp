#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

void stringSort(std::string arr[], int arrSize);

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