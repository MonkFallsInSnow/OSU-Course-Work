//#define _CRT_SECURE_NO_WARNINGS ->needed for visual studio

/**************************************************************************************************
** Program Filename: main.c
** Author: Conrad Lewin
** Date: 2/23/2016
** Description: This program provides the user with a to do list application. The user is allowed
to add and remove items from the list, display the lists contents and load as well as save created 
** to do lists.
***************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "toDoList.h"


int main(int argc, const char * argv[])
{
	char cmd = ' ';
	DynArr* mainList = createDynArr(10);
	char filename[100]; //filename buffer
	FILE* file = NULL; //input/output file

	printf("\n\n** TO-DO LIST APPLICATION **\n\n");

	do
	{
		printf("Press:\n"
			"'l' to load to-do list from a file\n"
			"'s' to save to-do list to a file\n"
			"'a' to add a new task\n"
			"'g' to get the first task\n"
			"'r' to remove the first task\n"
			"'p' to print the list\n"
			"'e' to exit the program\n"
			);
		/* get input command (from the keyboard) */
		cmd = getchar();
		/* clear the trailing newline character */
		while (getchar() != '\n');

		switch (cmd)
		{
		case 'l':
		{
			//get filename
			printf("Enter filename: ");
			scanf("%s", filename);
			getchar();

			//if a file is already open, then close it
			if (file != NULL)
			{
				fclose(file);
			}

			file = fopen(filename, "r"); //open the file for reading

			if (file != NULL) //if the file was opened sucessfully...
			{
				//empty the main list
				if (!isEmptyDynArr(mainList))
				{
					int size = sizeDynArr(mainList);
					for (int i = 0; i < size; i++)
					{
						removeMinHeap(mainList, compare);
					}
				}

				//load the file and print a confirmation
				loadList(mainList, file); 
				printf("List has been loaded.\n\n");
			}
			else //otherwise print and error message
			{
				printf("Could not open file.\n\n");

			}
			break;
		}
		case 's':
		{
			//get filename
			printf("Enter filename: ");
			scanf("%s", filename);
			getchar();

			file = fopen(filename, "w"); //open the file for writing

			if (file != NULL) //if the file was opened sucessfully
			{
				//save the list and print a confirmation
				saveList(mainList, file);
				printf("List has been saved.\n\n");
			}
			else //otherwise print an error message
			{
				printf("Could not create file.\n\n");

			}
			break;
		}
		case 'a':
		{
			int priority; //stores the task priority
			char desc[100]; //sotres the task description

			//get the task description
			printf("Enter a brief description: ");
			fgets(desc, 100, stdin);
			desc[strcspn(desc, "\n")] = 0; //removes trailing newline character

			//get the task priority
			printf("Enter a task priority (0-999): ");
			scanf("%d", &priority);
			getchar();

			TYPE newTask = createTask(priority, desc); //create a new task
			addHeap(mainList, newTask, compare); //add that taks to the heap
			printf("The task '%s' has been added to your list.\n\n", desc); //print a confirmation
			break;
		}
		case 'g':
		{
			if (!isEmptyDynArr(mainList)) //make sure the list is not empty
			{
				struct Task* task = (struct Task*)getMinHeap(mainList); //get the value at the heap's root node
				printf("Your first task is: %s\n\n", task->description); //print the description of that value
			}
			else
			{
				printf("Your to-do list is empty!\n\n"); 
			}
			break;
		}
		case 'r':
		{
			if (!isEmptyDynArr(mainList)) //make sure the heap is not empty
			{
				struct Task* task = (struct Task*)getMinHeap(mainList); //get the value at the heap's root node
				printf("Your first task '%s' has been removed from the list.\n\n", task->description); //print the description of that value
				removeMinHeap(mainList, compare); //remove that value from the heap
				free(task);
				task = NULL;
				
			}
			else
			{
				printf("The list is empty.\n\n");
			}
			break;
		}
		case 'p':
		{
			if (!isEmptyDynArr(mainList)) //make sure the heap is not empty
			{
				printList(mainList); //then print the contents of the heap from highest to lowest priority
			}
			else
			{
				printf("The list is empty.\n\n");
			}
			break;
		}
		case 'e':
		{
			//if a file has been opened, then close that file
			if (file != NULL)
			{
				fclose(file);
			}
			break;
		}
		default:
			break;
		}
		/* Note: We have provided functions called printList(), saveList() and loadList() for you
		to use.  They can be found in toDoList.c */
	} while (cmd != 'e');
	/* delete the list */
	deleteDynArr(mainList);

	return 0;
}
