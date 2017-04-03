/**************************************************************************************************
** Program Filename: Q1.c
** Author: Conrad Lewin
** Date: 1/10/2016
** Description: Generates student ids and scores and then outputs that data along with the highest
** lowest and average scores
** Input:  A stuct student
** Output: All scores and ids as well as the highest lowest and average scores
***************************************************************************************************/

#include <stdio.h>
#include<stdlib.h>
#include<math.h>

struct student 
{
	int id;
	int score;
};

static const int NUM_STUDENTS = 10;

//---helper functions-------------------------------------------

/*********************************************************************
** Function: int getMinScore(struct student* students)
** Description: Finds the lowest score value in an array of student
** structs
** Parameters: students - pointer to a struct student or array of
** struct students
** Pre-Conditions: At least one struct student with valid score data
** Post-Conditions: Returns the lowest score in an array of student
** structs
*********************************************************************/
int getMinScore(struct student* students)
{
	int minScore = students[0].score; //initialize the smallest score to a default value

									  /*
									  ** loops through an array of struct students, comparing each score
									  ** against the current minimum and updating that minimum when
									  ** necessary.
									  **/
	for (int i = 1; i < NUM_STUDENTS; i++)
	{
		if (students[i].score < minScore)
		{
			minScore = students[i].score;
		}
	}

	return minScore;
}


/*********************************************************************
** Function: int getMaxScore(struct student* students)
** Description: Finds the highest score value in an array of student
** structs
** Parameters: students - pointer to a struct student or array of
** struct students
** Pre-Conditions: At least one struct student with valid score data
** Post-Conditions: Returns the highest score in an array of student
** structs
*********************************************************************/
int getMaxScore(struct student* students)
{
	int maxScore = students[0].score; //initialize highest score to a default value


									  /*
									  ** loops through an array of struct students, comparing each score
									  ** against the current maximum and updating that maximum when
									  ** necessary.
									  **/
	for (int i = 1; i < NUM_STUDENTS; i++)
	{
		if (students[i].score > maxScore)
		{
			maxScore = students[i].score;
		}
	}

	return maxScore;
}


/*********************************************************************
** Function: double getAverage(struct student* students)
** Description: Calculates the average score from the score data
** stored in an array of struct students
** Parameters: students - pointer to a struct student or array of
** struct students
** Pre-Conditions: At least one struct student with valid score data
** Post-Conditions: Returns the average score of all score data in
** an array of struct students
*********************************************************************/
double getAverage(struct student* students)
{
	int sum = 0; //initialize accumulator variable

				 /*
				 ** loops through an array of struct students, summing each struct's
				 ** score data before dividing by the number of structs in the array
				 ** in order to determine the average score
				 **/
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		sum += students[i].score;
	}

	return (double)sum / NUM_STUDENTS;

}


/*********************************************************************
** Function: void swap(struct student* myArray, int first, int second)
** Description: Swaps two struct students located in array with one
** another.
** Parameters: myArray - pointer to an array of struct students,
** arraySize - size of the array, first - an index in the array,
** second - another index in the array
** Pre-Conditions: An array of struct students with at least 2
** elements
** Post-Conditions: The element at the index indicated by first
** will have been swaped with the element at the index indicated
** by second unless either first, second or both are greater than
** or equal to arraySize or less than zero.
*********************************************************************/
void swap(struct student* myArray, int arraySize, int first, int second)
{
	if ((first >= 0 && first < arraySize) && (second >= 0 && second < arraySize))
	{
		struct student temp = myArray[first];
		myArray[first] = myArray[second];
		myArray[second] = temp;
	}
}

//---end helper functions-------------------------------------------


/*********************************************************************
** Function: struct student* allocate()
** Description: Allocates memory for a constant number of struct
** students
** Parameters: none
** Pre-Conditions: An unitiliazied pointer to a struct student
** Post-Conditions: A block of memory allocated for an array of struct
** students (the size of that array is defined by global constant
** NUM_STUDENTS). Returns the starting address of the allocated block
** of memory.
*********************************************************************/
struct student* allocate()
{
	struct student* students = malloc(NUM_STUDENTS * sizeof(struct student));

	return students;
}


/*********************************************************************
** Function: void generate(struct student* students)
** Description: Generates random ID and scores for a set number of
** students.
** Parameters: students - pointer to a struct student or array of
** struct students
** Pre-Conditions: A pointer to a struct student
** Post-Conditions: One or more struct students (depending on
** whether or not the pointer points to an array) with random IDs
** and scores.
*********************************************************************/
void generate(struct student* students)
{
	/*
	** loops through an array of struct students, assigning ordered ID
	** numbers and random scores.
	*/
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		students[i].id = i + 1;
		students[i].score = rand() % 101;
	}

	/*
	** loops through an array of struct students, swaping structs at
	** random indicies.
	*/
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		int index1 = rand() % NUM_STUDENTS;
		int index2 = rand() % NUM_STUDENTS;

		swap(students, NUM_STUDENTS, index1, index2);
	}
}


/*********************************************************************
** Function: void output(struct student* students)
** Description: Prints student IDs and scores
** Parameters: students -  a pointer to an array of struct students
** Pre-Conditions: A pointer to an arry of struct students
** Post-Conditions: Outputs student IDs and scores to screen
*********************************************************************/
void output(struct student* students)
{
	/*Outputs information about the ten students in the format:
	ID 1 Score 1
	ID 2 score 2
	ID 3 score 3
	...
	ID n score n*/
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		printf("%d %d\n", students[i].id, students[i].score);
	}
}


/*********************************************************************
** Function: void summary(struct student* students)
** Description: Outputs the lowest, highest and average student scores
** Parameters: students - pointer to a struct student or array of
** struct students
** Pre-Conditions: A pointer to a struct student
** Post-Conditions: Output of lowest, highest and average student scores
*********************************************************************/
void summary(struct student* students)
{
	printf("%d %d %f\n", getMinScore(students), getMaxScore(students), getAverage(students));
}


/*********************************************************************
** Function: void deallocate(struct student* stud)
** Description: Deallocates memory previously allocated for a number
** of struct students
** Parameters: stud - pointer to a struct student or array of
** struct students
** Pre-Conditions: A pointer to a struct student
** Post-Conditions: The memory dynamically assigned to the argument
** will be deallocated
*********************************************************************/
void deallocate(struct student* stud)
{
	/*
	** ensure the argument has a valid address before freeing up that memory
	** location
	*/
	if (stud != NULL)
	{
		free(stud);
	}
}


int main() {
	struct student* stud = NULL;

	stud = allocate();
	generate(stud);
	output(stud);
	summary(stud);
	deallocate(stud);

	return 0;
}