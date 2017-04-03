#include <iostream>

using std::cout;
using std::endl;

double summer(double arr[], int arrSize);

int main()
{
	const int SIZE = 5;
	double arr[SIZE] = { 1.0, 0.5, 0.5, 2.5, 0.0 };
	double sum = summer(arr, SIZE);

	for (int i = 0; i < SIZE; i++)
	{
		cout << arr[i];
		if (i != SIZE - 1)
		{
			cout << " + ";
		}
	}

	cout << " = " << sum << endl;
	return 0;
}