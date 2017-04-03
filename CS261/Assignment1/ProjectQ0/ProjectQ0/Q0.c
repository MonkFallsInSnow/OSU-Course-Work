/**************************************************************************************************
** Program Filename: Q0.c
** Author: Conrad Lewin
** Date: 1/10/2016
** Description: This program prints address and value information about a pointer to an int
** Input: An int value
** Output: Address and value an int and a pointer to an int
***************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

/*********************************************************************
** Function: void fooA(int* iptr)
** Description: This function prints address and value information
** about a given argument
** Parameters: iptr - a pointer to an int
** Pre-Conditions: The declaration of a valid integer variable
** Post-Conditions: Output of the address of iptr and the value
** as well as the address pointed to by iptr
*********************************************************************/
void fooA(int* iptr)
{
	printf("%d\n", *iptr); //print value pointed to by iptr
	printf("%p\n", iptr); //print the address pointed to by iptr
	printf("%p\n", &iptr); //print the address of iptr
}

int main()
{
	int x = 0;
	printf("%p\n", &x); //print the address of x
	fooA(&x);
	printf("%d\n", x); //print value of x

	return 0;
}