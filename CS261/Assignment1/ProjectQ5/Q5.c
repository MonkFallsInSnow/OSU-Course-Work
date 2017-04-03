#define _CRT_SECURE_NO_WARNINGS //remove before submission

/**************************************************************************************************
** Program Filename: Q5.c
** Author: Conrad Lewin
** Date: 1/10/2016
** Description: This program gets a word from the user and converts that word to display sticky caps
** Input: A word from the user
** Output: The given word in sticky caps
***************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>


/*********************************************************************
** Function: char toUpperCase(char ch)
** Description: Converts a given char to uppercase. Assumes the given
** char is in lowercase
** Parameters: ch - a char
** Pre-Conditions: An initialized char variable. The char should be
** lowercase
** Post-Conditions: The uppercase representation of the given char
*********************************************************************/
char toUpperCase(char ch)
{
	return ch - 'a' + 'A';
}

/*********************************************************************
** Function: char toLowerCase(char ch)
** Description: Converts a given char to lowercase. Assumes the given
** char is in uppercase
** Parameters: ch - a char
** Pre-Conditions: An initialized char variable. The char should be
** uppercase
** Post-Conditions: The lowercase representation of the given char
*********************************************************************/
char toLowerCase(char ch)
{
	return ch - 'A' + 'a';
}


/*********************************************************************
** Function: void sticky(char* word)
** Description: Loops through a character arrray, changing chars at
** even indicies to uppercase and chars at odd indicies to lowercase
** Parameters: word - pointer to a char (should be an array)
** Pre-Conditions: An array of chars
** Post-Conditions: The given array of chars will be modified with
** sticky caps
*********************************************************************/
void sticky(char* word)
{
	int index = 0;

	/*
	** loops through the char array until the null character is reached. at
	** even indices, the case of the current char is checked. if lowercase
	** the char is converted to uppercase, otherwise it is left alone. at
	** odd indices the case of the current char is checked. if uppercase
	** the char is converted to lowercase, otherwise it is left alone.
	*/
	while (word[index] != '\0')
	{
		if (index % 2 == 0)
		{
			if (word[index] >= 'a' && word[index] <= 'z')
			{
				word[index] = toUpperCase(word[index]);
			}
		}
		else
		{
			if (word[index] >= 'A' && word[index] <= 'Z')
			{
				word[index] = toLowerCase(word[index]);
			}
		}
		index++;
	}
}

int main()
{
	char word[100];
	printf("Enter a word: ");
	scanf("%s", word); //get a word from the user
	sticky(word); //convert that word to use stick caps
	printf("%s\n", word); //print the given word

	return 0;
}