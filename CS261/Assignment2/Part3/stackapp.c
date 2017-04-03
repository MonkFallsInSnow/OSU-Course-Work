/**************************************************************************************************
** Program Filename: stackapp.c
** Author: Conrad Lewin
** Date: 1/18/2016
** Description: This program uses a stack to determine whether a string consisting of various
** braces is balanced or not
** Input: A string
** Output: A string indicating whether or not the input string contains a balanced number of
** braces
***************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "dynArray.h"

int DEFAULT_SIZE = 10; //starting size of the stack's underlying data structure (a dynamic array)

//---helper functions----------------------------------------------

/****************************************************************************************
** Function: int _isOpenBracket(char s)
** Description: Internal function that checks the given input for an opening brace
** Parameters: s - a character taken from a string
** Post-Conditions: returns 1 (true) if the given character is an opening brace, otherwise
** returns 0 (false)
********************************************************************************************/
int _isOpenBracket(char s)
{
	switch (s)
	{
		case '(':
		case '{':
		case '[':
			return 1;
			break;
		default:
			break;
	}

	return 0;
}


/****************************************************************************************
** Function: int _isCloseBracket(char s)
** Description: Internal function that checks the given input for a closing brace
** Parameters: s - a character taken from a string
** Post-Conditions: returns 1 (true) if the given character is a closing brace, otherwise
** returns 0 (false)
********************************************************************************************/
int _isCloseBracket(char s)
{
	switch (s)
	{
	case ')':
	case '}':
	case ']':
		return 1;
		break;
	default:
		break;
	}

	return 0;
}

//---end helper functions----------------------------------------


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
param: 	s pointer to a string
pre: s is not null
*/
char nextChar(char* s)
{
	static int i = -1;
	char c;
	++i;
	c = *(s + i);
	if (c == '\0')
		return '\0';
	else
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
param: 	s pointer to a string
pre: s is not null
post:
*/
int isBalanced(char* s)
{
	DynArr* stack = newDynArr(DEFAULT_SIZE); //create a stack

	char bracket; //tracks bracket types
	char element; //tracks the current element in the given string

	//perform this loop until the end of the string is reached
	do
	{
		element = nextChar(s); //get the next element in the string

		//check the element to determine whether it is a closing or opening brace
		if (_isOpenBracket(element))
		{
			pushDynArr(stack, element); //push an opening brace onto the stack
		}
		else if (_isCloseBracket(element))
		{
			if (!isEmptyDynArr(stack)) //make sure the stack is not empty
			{
				bracket = topDynArr(stack); //check the top of the stack

				//make sure the brace at the top of the stack matches the right closing brace
				if ((bracket == '(' && element != ')') ||
					(bracket == '{' && element != '}') ||
					(bracket == '[' && element != ']'))
				{
					element = '\0'; //indicate the end the loop if the braces are mismatched
				}
				else
				{
					popDynArr(stack); //pop the top element off of the stack if the braces match
				}
			}
			else
			{
				/* 
				** if the stack is empty when a closing brace is encountered in the string, 
				** then free the stack and exit the function, indicating that the string was not balanced
				*/
				free(stack); 
				return 0;
			}
		}

	} while (element != '\0');

	/*
	** if the stack still has elements after the end of the string has been reached, 
	** then free the stack and exit the function, indicating that the string was not balanced 
	*/
	if (sizeDynArr(stack) > 0)
	{
		free(stack);
		return 0;
	}

	//otherwise, free the stack and exit the function, indicating that the string is balanced 
	free(stack);
	return 1;
}

int main(int argc, char* argv[]) 
{
	char* s = argv[1];
	int res;

	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n", s);
	else
		printf("The string %s is not balanced\n", s);
		
	return 0;
}

