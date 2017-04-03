/**************************************************************************************************
** Program Filename: Q4.c
** Author: Conrad Lewin
** Date: 1/10/2016
** Description: This program generates student data, sorts and prints that data
** Input: An array of struct students
** Output: A sorted array of struct students
***************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct student
{
	int id;
	int score;
};

//---helper functions----------------------------------------------

/*********************************************************************
** Function: void swap(struct student* myArray, int first, int second)
** Description: Swaps two struct student items with one another.
** Parameters: myArray - pointer to a struct student, first - the value
** at this index will be swapped with second, second - the index at
** this value will be swapped with first
** Pre-Conditions: An initialized pointer to an int (should be an array)
** and the indices of the values the client wishes to swap
** Post-Conditions: The array argument passed to this function will
** modify that array so that the element at index first is now at
** index second and vice versa
*********************************************************************/
void swap(struct student* myArray, int first, int second)
{
	struct student temp = myArray[first];
	myArray[first] = myArray[second];
	myArray[second] = temp;
}


/**************************************************************************
** Function: int partition(struct student* myArray, int start, int end)
** Description: Partitions an array into two sub arrays in which
** a value designated at the pivot serves as the line that divides
** these two arrays. All elements less than the pivot will be in indices
** to the left of the pivot's index, while all elements greater than the
** pivot value will be stored to the right of pivot's index.
** Parameters:  myArray - pointer to a struct student(an array), start - indicates
** the first element in the array/sub array, end - indicates the last
** value in the array/sub array which is reserved as the index of the
** pivot.
** Pre-Conditions: An initialized pointer to a struct student (should be an array)
** and the indices pointing to the begining and end of the array/sub array
** Post-Conditions: The array passed as an argument to this function will
** be modified in the manner stated in the description. The final position
** of the pivot after the partitioning will be returned for use in the
** quicksort() function described below.
****************************************************************************/
int partition(struct student* myArray, int start, int end)
{
	int pivot = myArray[end].score; //chose a pivot value
	int wall = start; //initialize the line that divides the sub array to the first element in the array

					  /*
					  ** loop through the array starting at the pivot wall and ending at the pivot. if the current element
					  ** is less than the value of the pivot, then swap the current element with the element located at the
					  ** pivot wall. increment the position of the wall. This places all elements less than the pivot to the
					  ** left of the pivot wall and all items larger than the pivot to the right.
					  */
	for (int current = wall; current < end; current++)
	{
		if (myArray[current].score < pivot)
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
** Function: void quickSort(struct student* myArray, int start, int end)
** Description: Sorts a struct student array at O(n log n) under favorable
** conditions and O(n^2) under unfavorable conditions (if the array
** is already sorted)
** Parameters: myArray - pointer to a struct student(an array), start - indicates
** the first element in the array/sub array, end - indicates the last
** value in the array/sub array which is reserved as the index of the
** pivot.
** Pre-Conditions: This function should be called with start = 0 and
** end = the size of the array - 1
** Post-Conditions: The array passed as an argument to the function
** will be sorted
*********************************************************************/
void quickSort(struct student* myArray, int start, int end)
{
	if (start < end)
	{
		int pivotPos = partition(myArray, start, end);
		quickSort(myArray, start, pivotPos - 1); //partition and sort the sub array to the left of the pivot
		quickSort(myArray, pivotPos + 1, end); //partition and sort the sub array to the right of the pivot
	}

}


/*********************************************************************
** Function: void generateData(struct student* students, int numStudents)
** Description: Generates random id numbers from 1 to 10
** Parameters: students - pointer to an array of structs containing
** data about students, numStudents - int that stores the number of
** students in the array of structs
** Pre-Conditions: An array of struct students and the number of
** elements in this array
** Post-Conditions: All structs in the array passed as argument will
** contain random scores and IDs
*********************************************************************/
void generateData(struct student* students, int numStudents)
{
	/*
	** loops through an array of struct students, assigning ordered ID
	** numbers and random scores.
	*/
	for (int i = 0; i < numStudents; i++)
	{
		students[i].id = i + 1;
		students[i].score = rand() % 100;
	}

	/*
	** loops through an array of struct students, swaping structs at
	** random indicies.
	*/
	for (int i = 0; i < numStudents; i++)
	{
		int index1 = rand() % 10;
		int index2 = rand() % 10;
		swap(students, index1, index2);
	}
}


/*********************************************************************
** Function: void printData(struct student* students, int numStudents)
** Description: Prints student IDs and scores
** Parameters: students - a pointer to an array of struct students,
** numStudents - size of the array
** Pre-Conditions: A pointer to an arry of struct students
** Post-Conditions: Outputs student IDs and scores to screen
*********************************************************************/
void printData(struct student* students, int numStudents)
{
	/*Outputs information about the ten students in the format:
	ID 1 Score 1
	ID 2 score 2
	ID 3 score 3
	...
	ID n score n*/
	for (int i = 0; i < numStudents; i++)
	{
		printf("%d %d\n", students[i].id, students[i].score);
	}
}

//---end helper functions---------------------------------------------------------------

/*********************************************************************
** Function: void sort(struct student* students, int n)
** Description: Sorts an array of integers (function wrapped around
** quicksort())
** Parameters: students - pointer to a struct student (should be an array),
** n - the number of elements in the array
** Pre-Conditions: An initialized pointer to a struct student
** (should be an array) and the size of that array
** Post-Conditions: The array passed as an argument to the function
** will be sorted
*********************************************************************/
void sort(struct student* students, int n)
{
	quickSort(students, 0, n - 1);
}

int main()
{

	int n = 10; //number of students

	struct student* students = malloc(sizeof(struct student) * n); //allocate memory for an array of students

	generateData(students, n); //fill the array with data

	printData(students, n); //output that data
	printf("\n");

	quickSort(students, 0, n - 1); //sort the student data

	printData(students, n); //output the sorted data

	return 0;
}