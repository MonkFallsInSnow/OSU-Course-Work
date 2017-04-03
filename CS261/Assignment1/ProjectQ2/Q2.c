/**************************************************************************************************
** Program Filename: Q2.c
** Author: Conrad Lewin
** Date: 1/10/2016
** Description: This program explores the difference between passing arguments by value and
** by reference
** Input:  Two pointers to ints and one int variable
** Output: Three int values
***************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

/*********************************************************************
** Function: int foo(int* a, int* b, int c)
** Description: Trivial function that performs vaious arithmetic
** calculations
** Parameters: a, b = pointers to ints, c - int variable
** Pre-Conditions: Three int variable declarations to achieve intended
** results
** Post-Conditions: The value stored at the address pointed to by
** a will be doubled, the value pointed to by b will be halfed, and
** the sum of these values will be returned
*********************************************************************/
int foo(int* a, int* b, int c)
{
	*a *= 2;	 //double the value pointed to by a
	*b /= 2;	 //half the value pointed to by b
	c = *a + *b; //get the sum of the modified a and b values

	return c;
}

int main()
{
	int x = 5;
	int y = 6;
	int z = 7;

	printf("%d %d %d\n", x, y, z);
	int result = foo(&x, &y, z);
	printf("%d\n", result);
	printf("%d %d %d\n", x, y, z);

	/*Is the return value different than the value of z?  Why?*/
	/*
	**Yes. While variables x and y are passed to foo() by reference, variable z is passed by value. Therefore,
	** a copy of z was passed to foo() and it was that copy that was changed rather than the actual value.
	*/

	return 0;
}