/**************************************************************************************************
** Program Filename: Q3.c
** Author: Conrad Lewin
** Date: 1/10/2016
** Description: This program fills an array of integers with values, sorts and prints those
** values
** Input: An unsorted array of integers
** Output: A sorted array of integers
***************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//---helper functions------------------------------------

/*********************************************************************
** Function: void fillArray(int* myArray, int arraySize)
** Description: Populates an array of ints with random values
** Parameters: myArray - pointer to an int(an array), arraySize - size
** of the array
** Pre-Conditions: An initialized pointer to an int (should be an array)
** and the size of that array
** Post-Conditions: An array filled with random values
*********************************************************************/
void fillArray(int* myArray, int arraySize)
{
	/*
	** loops through the array, placing a random int value at the
	** current index
	*/
	for (int i = 0; i < arraySize; i++)
	{
		myArray[i] = rand();
	}
}


/*********************************************************************
** Function: void printArray(int* myArray, int arraySize)
** Description: Prints the given int array to the screen
** Parameters: myArray - pointer to an int(an array), arraySize - size
** of the array
** Pre-Conditions: An initialized pointer to an int (an array)
** and the size of that array
** Post-Conditions: A line or several lines (depending on arraySize)
** of random int values printed to the screen
*********************************************************************/
void printArray(int* myArray, int arraySize)
{
	/*
	** loops through the array, printing the value stored at the
	** current index
	*/
	for (int i = 0; i < arraySize; i++)
	{
		printf("%d ", myArray[i]);
	}

	printf("\n");
}


/*********************************************************************
** Function: void swap(int* myArray, int first, int second)
** Description: Swaps two elements in an array with one another
** Parameters: myArray - pointer to an int(an array), first - the value
** at this index will be swapped with second, second - the index at
** this value will be swapped with first
** Pre-Conditions: An initialized pointer to an int (should be an array)
** and the indices of the values the client wishes to swap
** Post-Conditions: The array argument passed to this function will
** modify that array so that the element at index first is now at
** index second and vice versa
*********************************************************************/
void swap(int* myArray, int first, int second)
{
	int temp = myArray[first]; //save a copy of the element stored at first
	myArray[first] = myArray[second]; //overwrite the element stored at first with the element at second
	myArray[second] = temp; //overwrite the element stored at second with the copy of the element previously in first
}


/**************************************************************************
** Function: int partition(int* myArray, int start, int end)
** Description: Partitions an array into two sub arrays in which
** a value designated at the pivot serves as the line that divides
** these two arrays. All elements less than the pivot will be in indices
** to the left of the pivot's index, while all elements greater than the
** pivot value will be stored to the right of pivot's index.
** Parameters:  myArray - pointer to an int(an array), start - indicates
** the first element in the array/sub array, end - indicates the last
** value in the array/sub array which is reserved as the index of the
** pivot.
** Pre-Conditions: An initialized pointer to an int (should be an array)
** and the indices pointing to the begining and end of the array/sub array
** Post-Conditions: The array passed as an argument to this function will
** be modified in the manner stated in the description. The final position
** of the pivot after the partitioning will be returned for use in the
** quicksort() function described below.
****************************************************************************/
int partition(int* myArray, int start, int end)
{
	int pivot = myArray[end]; //chose a pivot value
	int wall = start; //initialize the line that divides the sub array to the first element in the array

					  /*
					  ** loop through the array starting at the pivot wall and ending at the pivot. if the current element
					  ** is less than the value of the pivot, then swap the current element with the element located at the
					  ** pivot wall. increment the position of the wall. This places all elements less than the pivot to the
					  ** left of the pivot wall and all items larger than the pivot to the right.
					  */
	for (int current = wall; current < end; current++)
	{
		if (myArray[current] < pivot)
		{
			swap(myArray, current, wall);
			wall++;
		}
	}

	//swap the pivot with the element at the wall. the pivot is now sorted and serves to divide the sub arrays
	swap(myArray, end, wall);

	return wall;
}


/*********************************************************************
** Function: void quickSort(int* myArray, int start, int end)
** Description: Sorts an array of ints at O(n log n) under favorable
** conditions and O(n^2) under unfavorable conditions (if the array
** is already sorted)
** Parameters: myArray - pointer to an int(an array), start - indicates
** the first element in the array/sub array, end - indicates the last
** value in the array/sub array which is reserved as the index of the
** pivot.
** Pre-Conditions: This function should be called with start = 0 and
** end = the size of the array - 1
** Post-Conditions: The array passed as an argument to the function
** will be sorted
*********************************************************************/
void quickSort(int* myArray, int start, int end)
{
	if (start < end)
	{
		int pivotPos = partition(myArray, start, end);
		quickSort(myArray, start, pivotPos - 1); //partition and sort the sub array to the left of the pivot
		quickSort(myArray, pivotPos + 1, end); //partition and sort the sub array to the right of the pivot
	}

}

//---end helper functions---------------------------------


/*********************************************************************
** Function: void sort(int* number, int n)
** Description: Sorts an array of integers (function wrapped around
** quicksort())
** Parameters: number - pointer to an int (should be an array), n - the
** number of elements in the array
** Pre-Conditions: An initialized pointer to an int (should be an array)
** and the size of that array
** Post-Conditions: The array passed as an argument to the function
** will be sorted
*********************************************************************/
void sort(int* number, int n)
{
	quickSort(number, 0, n - 1);
}

int main()
{
	int n = 20;

	int* numbers = malloc(sizeof(int) * n); //allocate memory for the an array of ints with n elements

	fillArray(numbers, n); //populate the array with values
	printArray(numbers, n); //print the contents of the array
	sort(numbers, n); //sort the contents of the array
	printArray(numbers, n); //print the sorted contents of the array
	free(numbers); //deallocate the memory allocated for the array

	return 0;
}