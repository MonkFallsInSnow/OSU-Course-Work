#define _CRT_SECURE_NO_WARNINGS //needed to compile using visual studio 2015
/**************************************************************************************************
** Program Filename: hashMap.c
** Author: Conrad Lewin
** Date: 3/4/2016
** Description: Provides an interface for a hash table.
***************************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "hashMap.h"


/*the first hashing function you can use*/
int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

/*the second hashing function you can use*/
int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; /*the difference between stringHash1 and stringHash2 is on this line*/
	return r;
}

/* initialize the supplied hashMap struct*/
void _initMap (struct hashMap * ht, int tableSize)
{
	int index;
	if(ht == NULL)
		return;
	ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
	ht->tableSize = tableSize;
	ht->count = 0;
	for(index = 0; index < tableSize; index++)
		ht->table[index] = NULL;
}

/* allocate memory and initialize a hash map*/
hashMap *createMap(int tableSize) {
	assert(tableSize > 0);
	hashMap *ht;
	ht = malloc(sizeof(hashMap));
	assert(ht != 0);
	_initMap(ht, tableSize);
	return ht;
}

/*
 Free all memory used by the buckets.
 Note: Before freeing up a hashLink, free the memory occupied by key and value
 */
void _freeMap (struct hashMap * ht)
{  
	assert(ht != NULL);

	//iterate through collection in each bucket, freeing each element of the hashLink
	for (int i = 0; i < ht->tableSize; i++)
	{
		hashLink* curLink = ht->table[i];

		while(curLink != NULL)
		{
			hashLink* nextLink = curLink->next;

			free(curLink->key);
			curLink->key = NULL;

			curLink->value = 0;

			free(curLink);
			curLink = nextLink;
		}
	}

	//free the hash table after all of its links have been released
	free(ht->table);
	ht->table = NULL;
}

/* Deallocate buckets and the hash map.*/
void deleteMap(hashMap *ht) {
	assert(ht!= 0);
	/* Free all memory used by the buckets */
	_freeMap(ht);
	/* free the hashMap struct */
	free(ht);
}

/* 
Resizes the hash table to be the size newTableSize 
*/
void _setTableSize(struct hashMap * ht, int newTableSize)
{
	assert(ht != NULL);
	const int MAX_WORD_LEN = 30;

	hashMap* tempMap = createMap(newTableSize); //create a temporary hash map twice the size of ht
	
	//copies each element in ht into the the temporary map
	for (int i = 0; i < ht->tableSize; i++)
	{
		hashLink* curLink = ht->table[i];

		while (curLink != NULL)
		{
			//create new addresses for each element in ht before inserting them into the temporary map
			char* k = malloc(sizeof(char) * MAX_WORD_LEN);
			strcpy(k, curLink->key);
			insertMap(tempMap, k, curLink->value);

			curLink = curLink->next;
		}
	}

	//free all the links and the table in ht before copying the properties from the temporary map into ht
	_freeMap(ht);
	ht->table = tempMap->table;
	ht->count = tempMap->count;
	ht->tableSize = tempMap->tableSize;

}

/*
 insert the following values into a hashLink, you must create this hashLink but
 only after you confirm that this key does not already exist in the table. For example, you
 cannot have two hashLinks for the word "taco".
 
 if a hashLink already exists in the table for the key provided you should
 replace that hashLink--this requires freeing up the old memory pointed by hashLink->value
 and then pointing hashLink->value to value v.
 
 also, you must monitor the load factor and resize when the load factor is greater than
 or equal LOAD_FACTOR_THRESHOLD (defined in hashMap.h).
 */
void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{  
	/*write this*/
	assert(ht != NULL);

	int hashCode;

	//choses a hashing function depenending on the value of the following preprocessor directive
	if (HASHING_FUNCTION == 1)
	{
		hashCode = stringHash1(k) % ht->tableSize; //get a hash code
	}
	else
	{
		hashCode = stringHash2(k) % ht->tableSize; //get a hash code
	}

	hashLink* curLink = ht->table[hashCode]; //set the current link to the index in hash table that matches the hash code
	
	//insert a new link into the hash table if the given key is not already in the table
	if (!containsKey(ht, k))
	{
		hashLink* newLink = malloc(sizeof(hashLink)); //create a new link

		//set this new link's key and value
		newLink->key = k;
		newLink->value = v;

		//insert the new link as the first element in bucket's collection
		newLink->next = ht->table[hashCode];
		ht->table[hashCode] = newLink;
		ht->count++;

		//get the load factor and resize the table if necessary
		float loadFactor = tableLoad(ht);
		if (loadFactor >= LOAD_FACTOR_THRESHOLD)
		{
			_setTableSize(ht, (ht->tableSize * 2) + 1); //only odd numbers are prime... though not guaranteed to be
		}
	}
	//otherwise, replace the value of the key already in the table with the the given value
	else
	{
		hashLink* curLink = ht->table[hashCode];  //get the first link in the relevant bucket

		//find the link with the given key in the bucket and replace its value
		while (curLink != NULL)
		{
			if(strcmp(curLink->key,k) == 0)
			{
				curLink->value = v;
			}

			curLink = curLink->next;
		}
	}	
}

/*
 this returns the value (which is void*) stored in a hashLink specified by the key k.
 
 if the user supplies the key "taco" you should find taco in the hashTable, then
 return the value member of the hashLink that represents taco.
 
 if the supplied key is not in the hashtable return NULL.
 */
ValueType* atMap (struct hashMap * ht, KeyType k)
{ 
	assert(ht != NULL);

	int hashCode;

	//choses a hashing function depenending on the value of the following preprocessor directive
	if (HASHING_FUNCTION == 1)
	{
		hashCode = stringHash1(k) % ht->tableSize; //get the hash code
	}
	else
	{
		hashCode = stringHash2(k) % ht->tableSize; //get the hash code
	}

	hashLink* curLink = ht->table[hashCode]; //set the current link to the index in hash table that matches the hash code

	//find the link in the bucket with the given key. If found return the address of its value
	while (curLink != NULL)
	{
		if (strcmp(curLink->key, k) == 0)
		{
			return &(curLink->value);
		}

		curLink = curLink->next;
	}

	return NULL;
}

/*
 a simple yes/no if the key is in the hashtable. 
 0 is no, all other values are yes.
 */
int containsKey (struct hashMap * ht, KeyType k)
{  
	int hashCode;

	//choses a hashing function depenending on the value of the following preprocessor directive
	if (HASHING_FUNCTION == 1)
	{
		hashCode = stringHash1(k) % ht->tableSize; //get the hash code
	}
	else
	{
		hashCode = stringHash2(k) % ht->tableSize; //get the hash code
	}

	hashLink* curLink = ht->table[hashCode]; //set the current link to the index in hash table that matches the hash code

	//find the link in the bucket with the given key, returning 1 (true) if found
	while (curLink != NULL)
	{
		if (strcmp(curLink->key, k) == 0)
		{
			return 1;
		}

		curLink = curLink->next;
	}

	return 0;
}

/*
 find the hashlink for the supplied key and remove it, also freeing the memory
 for that hashlink. it is not an error to be unable to find the hashlink, if it
 cannot be found do nothing (or print a message) but do not use an assert which
 will end your program.
 */
void removeKey (struct hashMap * ht, KeyType k)
{  	
	assert(ht != 0);

	int hashCode;

	//choses a hashing function depenending on the value of the following preprocessor directive
	if (HASHING_FUNCTION == 1)
	{
		hashCode = stringHash1(k) % ht->tableSize; //get the hash code
	}
	else
	{
		hashCode = stringHash2(k) % ht->tableSize; //get the hash code
	}

	hashLink* curLink = ht->table[hashCode]; //set the current link to the index in hash table that matches the hash code
	hashLink* previous = NULL; //initialize the previous link to null

	//find the link in the bucket with the given key then remove it from the table
	while (curLink != NULL)
	{
		if (strcmp(curLink->key, k) == 0)
		{
			/* if the link is the first link in the collection then set the first link in the collection 
			 * to the second link in the collection (or null if there is no second link)
			 */
			if (previous == NULL)
			{
				ht->table[hashCode] = curLink->next;
			}
			//otherwise, connect the previous link to the current link's next
			else
			{
				previous->next = curLink->next;
			}

			//free the found link and update the number of elements in the table 
			free(curLink);
			ht->count--;
			return;
		}

		//update the current and previous links
		previous = curLink;
		curLink = curLink->next;
	}

	printf("Key is not in the table."); //print a message indicating the key was not found
}

/*
 returns the number of hashLinks in the table
 */
int size (struct hashMap *ht)
{  
	assert(ht != NULL);

	return ht->count;
	
}

/*
 returns the number of buckets in the table
 */
int capacity(struct hashMap *ht)
{  
	assert(ht != NULL);

	return ht->tableSize;
}

/*
 returns the number of empty buckets in the table, these are buckets which have
 no hashlinks hanging off of them.
 */
int emptyBuckets(struct hashMap *ht)
{  
	assert(ht != NULL);
	
	int count = 0; //tracks the number of empty buckets
	
	//iterate through the table searching for buckets with null values
	for (int i = 0; i < capacity(ht); i++)
	{
		if (ht->table[i] == NULL)
		{
			count++;
		}
	}

	return count;
}

/*
 returns the ratio of: (number of hashlinks) / (number of buckets)
 
 this value can range anywhere from zero (an empty table) to more then 1, which
 would mean that there are more hashlinks then buckets (but remember hashlinks
 are like linked list nodes so they can hang from each other)
 */
float tableLoad(struct hashMap *ht)
{  
	assert(ht != NULL);

	return (float)ht->count / ht->tableSize;
}

void printMap (struct hashMap * ht)
{
	int i;
	struct hashLink *temp;	
	for(i = 0;i < capacity(ht); i++){
		temp = ht->table[i];
		if(temp != 0) {		
			printf("\nBucket Index %d -> ", i);		
		}
		while(temp != 0){			
			printf("Key:%s|", temp->key);
			printValue(temp->value);
			printf(" -> ");
			temp=temp->next;			
		}		
	}
}