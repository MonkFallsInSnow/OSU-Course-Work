/*#define _CRT_SECURE_NO_WARNINGS //needed to compile using visual studio 2015*/

/**************************************************************************************************
** Program Filename: spellcheck.c
** Author: Conrad Lewin
** Date: 3/4/2016
** Description: Loads the contents of a dictionary file into a hash table and then asks a user
** to enter a word. If that word is found in the hash table, the user is informed that the word
** was spelled correctly, otherwise the user is informed that he/she misspelled the word.
***************************************************************************************************/
//#define EXTRA_CREDIT
#ifdef EXTRA_CREDIT

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "hashMap.h"

/*
the getWord function takes a FILE pointer and returns you a string which was
the next word in the in the file. words are defined (by this function) to be
characters or numbers seperated by periods, spaces, or newlines.

when there are no more words in the input file this function will return NULL.

this function will malloc some memory for the char* it returns. it is your job
to free this memory when you no longer need it.
*/
char* getWord(FILE *file);

/*
Load the contents of file into hashmap ht
*/
void loadDictionary(FILE* file, struct hashMap* ht);

int main(int argc, const char * argv[]) {
	clock_t timer;
	int tableSize = 1000;
	struct hashMap* hashTable = createMap(tableSize);
	timer = clock();
	//initMap(hashTable, tableSize); no longer in header

	FILE* dictionary = fopen("dictionary.txt", "r"); //open the dicitionary file for reading

	loadDictionary(dictionary, hashTable);
	timer = clock() - timer;
	printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);

	char* word = (char*)malloc(256 * sizeof(char));
	int quit = 0;
	while (!quit) {
		printf("Enter a word: "); //prompt to enter a word
		scanf("%s", word); //read the given input

						   //if the input value can be found in the hash table, then it was spelled correctly
		if (!containsKey(hashTable, word))
		{
			printf("%s is spelled wrong.\n", word);
		}
		else
		{
			printf("%s is spelled correctly.\n", word);
		}

		/* Don't remove this. It is used for grading*/
		if (strcmp(word, "quit") == 0)
			quit = !quit;
	}
	free(word);

	return 0;
}

/* Loads the contents of a text file into a hash table.
* Recieves a file from the user.
* The file must have been opened before calling this function and
* will close the file once its entire contents have been loaded into the table.
*/
void loadDictionary(FILE* file, struct hashMap* ht)
{
	if (file != NULL) //make sure a valid file was passed to the function
	{
		//while there is still content in the file to read, get the next word and insert it into the hash table
		while (!feof(file))
		{
			char* word = getWord(file);

			if (word != NULL)
			{
				insertMap(ht, word, 0);
			}
		}

		fclose(file); //close the given file
	}
	else
	{
		fprintf(stderr, "Could not open file."); //print an error message if the given file could not be opened
	}
}

void printValue(ValueType v) {
	printf("Value:%d", v);
}

char* getWord(FILE *file)
{
	int length = 0;
	int maxLength = 30;
	char character;

	char* word = (char*)malloc(sizeof(char) * maxLength);
	assert(word != NULL);

	while ((character = fgetc(file)) != EOF)
	{
		if ((length + 1) > maxLength)
		{
			maxLength *= 2;
			word = (char*)realloc(word, maxLength);
		}
		if ((character >= '0' && character <= '9') || /*is a number*/
			(character >= 'A' && character <= 'Z') || /*or an uppercase letter*/
			(character >= 'a' && character <= 'z') || /*or a lowercase letter*/
			(character == 39)) /*or is an apostrophy*/
		{
			word[length] = character;
			length++;
		}
		else if (length > 0)
			break;
	}

	if (length == 0)
	{
		free(word);
		return NULL;
	}
	word[length] = '\0';
	return word;
}

#endif