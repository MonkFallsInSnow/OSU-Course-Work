#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define True 1
#define False 0
#define MAX_CONNECTIONS 6
#define MIN_CONNECTIONS 3
#define NAME_SIZE 15
#define MAX_ROOMS 7
#define ROOM_CHOICES 10
#define MAX_TYPES 3
#define START_ROOM 0
#define END_ROOM 6
#define CONNECTION_OFFSET 14
#define NAME_OFFSET 11
#define BUFFER_SIZE 50

void makeRoomDir(char* buffer);
void randomizeRooms(const char** roomNames, int size);
struct Room* createRoom(const char* name,const char* type);
void destroyRooms(struct Room** rooms,int size);
void generateDungeon(struct Room** rooms,int size,const char** rmNames);
void makeConnections(struct Room** rooms, int size);
int canConnect(struct Room* r1, struct Room* r2);
void createRoomFiles(const char* dir, struct Room** rooms, int size, int bufferSize);
void playGame(struct Room** rooms,const char* dir,int bufferSize);
int isValidRoom(struct Room* curRoom, const char* nextRoom);
struct Room* goToNextRoom(struct Room* curRoom, const char* nextRoom);


//stores location information for each room
struct Room
{
	char name[NAME_SIZE]; //room name
	struct Room* connections[MAX_CONNECTIONS]; //list of room connections
	int maxConnections; //max number of connections a room can have
	int connectionCount; //used to track the current number of connections made during makeConnections()
	char type[NAME_SIZE]; //room type (start,mid,end)
};


int main()
{
	srand(time(0));	

	int i;
	char roomDir[BUFFER_SIZE];
	const char* rmNames[] = {"Valhalla","Elysium","Kamadhatu","Tushita","Skyrim","Hades","Nod","Fantasia","Lordran","Westeros"};
	struct Room* rooms[MAX_ROOMS];
	
	makeRoomDir(roomDir); //makes a directory for room files
	randomizeRooms(rmNames,ROOM_CHOICES); //performs a Fisher-Yates shuffle on the array of room names
	generateDungeon(rooms,MAX_ROOMS,rmNames); //create the dungeon "layout"
	createRoomFiles(roomDir,rooms,MAX_ROOMS,BUFFER_SIZE); //save data for each room in corsponding files
	playGame(rooms,roomDir,BUFFER_SIZE); //play the game
	destroyRooms(rooms,MAX_ROOMS); //free memory used for each room
	exit(EXIT_SUCCESS); //exit program sucessfully
}


/* Description: This function makes a directory inside the current directory that will be used to store
 * several room files.
 * Parameters: buffer - a char array large enough to store the directory name
 * Output: an empty directory in the current working directory.
*/ 
void makeRoomDir(char* buffer)
{
	pid_t procId = getpid(); //get the current process id
	sprintf(buffer, "./lewinc.rooms.%ld", (long)procId); //copy the directory name into the given buffer
	int wasCreated = mkdir(buffer,0700); //create the directory

	//make sure the directory was created sucessfully before returning to main
	if(wasCreated < 0)
	{
		perror("Error");
		exit(EXIT_FAILURE);	
	}
}


/* Description: This function uses a Fisher-Yates shuffle to randomize a set of room names.
 * Parameters: roomNames - an array of names for each room, size - the size of the array
 * Output: all elements in the passed in array will be shuffled 
*/
void randomizeRooms(const char** roomNames,int size)
{
	//iterate through the array swapping roomNames[i] with some other random element
	int i;
	for (i = 0; i < size; i++)
	{
		int randIndex = rand() % size;
		const char* tempName = roomNames[i];
		roomNames[i] = roomNames[randIndex];
		roomNames[randIndex] = tempName;
	}
}


/* Description: This function initialize a room struct.
 * Parameters: name - the name of the room, type - the room type
 * Output: a pointer to a Room struct
*/
struct Room* createRoom(const char* name, const char* type)
{
	int i;
	struct Room* room = malloc(sizeof(struct Room)); //allocate space for a new Room
	assert(room != NULL);

	//initialize each struct property will relevant values
	strncpy(room->name,name,sizeof(room->name));
	strncpy(room->type,type,sizeof(room->type));
	room->maxConnections = MIN_CONNECTIONS;
	room->connectionCount = 0;

	//initialze all elements in the room's connection list to NULL
	for(i = 0; i < MAX_CONNECTIONS; i++)
	{
		room->connections[i] = NULL;
	}

	return room;
}


/* Description: This function frees the memory allocated for each struct Room.
 * Parameters: rooms - an array of pointers to struct Rooms, size - the size of the array
 * Output: all elements in the rooms array will be NULL
*/
void destroyRooms(struct Room** rooms,int size)
{
	//iterate through the array, freeing memory associated with each room
	int i;
	for(i = 0; i < size; i++)
	{
		if(rooms[i] != NULL)
		{
			free(rooms[i]);
			rooms[i] = NULL;
		}
	}
}


/* Description: This function creates a a random dungeon layout.
 * Parameters: rooms - an empty array of pointers to struct Rooms, size - the size of the array, rmNames - an array of possible room names
 * Output: the rooms array will be filled with pointers to initialized Room structs
*/
void generateDungeon(struct Room** rooms,int size,const char** rmNames)
{
	//for each spot in the rooms array, create a room, then store it at index i
	int i;
	for(i = 0; i < size; i++)
	{
		if(i == 0)//when creating the first room, mark it as the start room
		{
			rooms[i] = createRoom(rmNames[i],"START_ROOM");
		}
		else if(i == size - 1) //when createing the last room, makr it as the end room
		{
			rooms[i] = createRoom(rmNames[i],"END_ROOM");
		}
		else //create all other rooms as mid rooms
		{
			rooms[i] = createRoom(rmNames[i],"MID_ROOM");
		}
	}	
	
	makeConnections(rooms,MAX_ROOMS); //make random room connections
}


/* Description: This function connects each room to some other room, creating a simple dungeon layout
 * Parameters: rooms - an array of pointers to Room structs, size - the size of the array
 * Output: each Room struct in the rooms array will have their connections lists populated with valid connections 
*/
void makeConnections(struct Room** rooms,int size)
{
	int i;
	int j;

	//iterate through the rooms array, searching for and making valid room connections for each room
	for (i = 0; i < size; i++)
	{	
		//make connections equal to the max connections a given room i can have	
		for (j = rooms[i]->connectionCount; j < rooms[i]->maxConnections; j++)
		{
			struct Room* nextRoom = rooms[rand() % size]; //select a random room from the rooms array

			//make sure this randomly selected room can be connected to rooms[i], otherwise, select another random room
			while (!canConnect(rooms[i], nextRoom))
			{
				nextRoom = rooms[rand() % size];
			}

			//after selecting a valid connection, connect those rooms to one another
			rooms[i]->connections[rooms[i]->connectionCount++] = nextRoom;
			nextRoom->connections[nextRoom->connectionCount++] = rooms[i];
		}

	}
}


/* Description: This function determines whether or not two rooms can be connected to one another
 * Parameters: r1 - the first room, r2 - a second room
 * Output: a "boolean" value indicated whether or not the given rooms may be connected
*/
int canConnect(struct Room* r1, struct Room* r2)
{
	int i;

	//if both rooms have the same name, then they are considered to be the same room and cannot be connected
	if (strcmp(r1->name, r2->name) == 0)
	{
		return False;
	}
	else
	{
		//iterate through r1's list of connections
		for (i = 0; i < r1->connectionCount; i++)
		{
			//if r2's name matches a name in r1's connection list, then that connections has already been made
			//and cannot be made again
			if (strcmp(r1->connections[i]->name, r2->name) == 0)
			{
				return False;
			}
		}
	}

	//if r2 is not the same as r1 and its not already connected to r1, then make sure r2 has connection space left
	if (r2->connectionCount == r2->maxConnections)
	{
		//since all rooms start with a max connections count of 3, we can increase this number until the true 
		//connection maxium is reach (6). so, if r2 has fewer than 6 connections, then increase the number of
		//connections it currently can field before returning true.
		if (r2->connectionCount + 1 <= MAX_CONNECTIONS)
		{
			r2->maxConnections++;
		}
		else
		{
			return False;
		}
	}

	return True;
}


/* Description: This function writes certain properties of a struct Room to a file in the rooms directory. The
 * properties written to file are the rooms name, list of connections and type. 
 * Parameters: dir - directory in which to create files, rooms - array of pointers to Room structs, size - size of
 * the array, bufferSize - size of the buffer that will hold the file's name
 * Output: a number of txt files equal to the number of rooms in the rooms array containing the aforemention room data
*/
void createRoomFiles(const char* dir, struct Room** rooms, int size, int bufferSize)
{
  	int i;
	int j;
	char fileName[bufferSize];

	//iterate through the rooms array, create files for each room
	for(i = 0; i < size; i++)
	{
		//create a file in the rooms diretory named after the ith room's name
		sprintf(fileName, "%s/%s.txt",dir,rooms[i]->name);	
		FILE* file = fopen(fileName,"w");
		
		//if that file was successfully created, then write the ith room's name, list of connections
		//and type to this file before closing it.
		if(file != NULL)
		{
			fprintf(file,"ROOM NAME: %s\n",rooms[i]->name);

			for(j = 0; j < rooms[i]->maxConnections; j++)
			{
				fprintf(file,"Connection %d: %s\n",(j+1),rooms[i]->connections[j]->name);
			}	

			fprintf(file,"ROOM TYPE: %s\n",rooms[i]->type);
			fclose(file);
		}
		else //if the file was not created, then print an error message and exit the program.
		{
			fprintf(stderr,"Could not create %s",fileName);
			exit(EXIT_FAILURE);
		}

		memset(fileName,'\0',sizeof(fileName)); //clear out the file name buffer before assigning it a new name on the next iteration
	}
}


/* Description: This functions searches an array of room connections matching an existing room name to a user input room name. 
 * Parameter: curRoom - a pointer to a Room struct, nextRoom - a user input room name
 * Output: a "boolean" value indicating whether the user input name matches a room in the rooms array
*/ 
int isValidRoom(struct Room* curRoom, const char* nextRoom)
{
	assert(curRoom != NULL);

	//iterate through the current room's list of connections
	int i;
	for (i = 0; i < curRoom->maxConnections; i++)
	{
		//return true if nextRoom matches a room name in curRoom's list of connections
		if (strcmp(nextRoom, curRoom->connections[i]->name) == 0)
		{
			return True;
		}
	}

	//otherwise, print an error message and return false
	printf("\nHUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN.\n\n");
	return False;
}


/* Description: This function captures the next room the player will move to. isValidRoom() should
 * be called before using this function
 * Parameters: curRoom - a pointer to a Room struct, nextRoom - a user input room name
 * Output: a pointer to a Room struct indicating the next room the player will travel to.
*/
struct Room* goToNextRoom(struct Room* curRoom, const char* nextRoom)
{
	assert(curRoom != NULL);

	//iterate through curRoom's list of connections
	int i;
	for (i = 0; i < curRoom->maxConnections; i++)
	{
		//if nextRoom is a valid connection, then return a pointer to a Room struct matching the name
		//given by nextRoom
		if (strcmp(nextRoom, curRoom->connections[i]->name) == 0)
		{
			return curRoom->connections[i];
		}
	}

	//otherwise, return NULL. not entirely necessary since isValidRoom() should be called before this method
	return NULL;
}


/* Description: This function runs the game loop.
 * Parameters: rooms - an array of pointers to Room structs, dir - the directory that houses room files, bufferSize -
 * size of the buffer used for room names, room file names and the victory path file name
 * Output: none
*/
void playGame(struct Room** rooms,const char* dir,int bufferSize)
{
	char rmBuffer[bufferSize]; //stores the name of the player's current location as well as the room he/she wishes to travel to
	char fileName[bufferSize]; //stores the file name associated with the player's current location
	char pathFileName[bufferSize]; //stores the file name of player's path to the end room
	//char nextRoom[bufferSize]; //stores the name of the next room the player wishes to travel to

	int steps = 0; //the number of steps the player took to reach the end room
	struct Room* curRoom = rooms[START_ROOM]; //initializes the player's current room to the starting room
	
	//create a read/write file that will record the player's path to the end room
	sprintf(pathFileName,"%s/victoryPath.txt",dir); 
	FILE* pathFile = fopen(pathFileName,"w+");
	
	//make sure the victory path file was created successfully before starting the game loop
	if(pathFile != NULL)
	{
		//run the game loop as long as the player has not yet reached the end room
		while (curRoom != rooms[END_ROOM])
		{	
			//clear all buffers (except pathFileName)
			memset(rmBuffer, '\0', sizeof(rmBuffer));
			memset(fileName, '\0', sizeof(fileName));
			//memset(nextRoom, '\0', sizeof(nextRoom));

			//get the file associated with the player's current location
			sprintf(fileName, "%s/%s.txt",dir,curRoom->name);
			FILE* file = fopen(fileName, "r");
			
			if (file != NULL) //make sure this file was opened successfully
			{
				do
				{
					
					int readOffset = NAME_OFFSET; //used to offset the file pointer past the room name header

					fseek(file, readOffset, SEEK_CUR); //move the file pointer to the room name
					fread(rmBuffer, strlen(curRoom->name) + 1, 1, file); //read the room name from the file

					//print the "UI"
					printf("CURRENT LOCATION: %s", rmBuffer);
					printf("POSSIBLE CONNECTIONS: ");

					memset(rmBuffer, '\0', sizeof(rmBuffer)); //clear the room name buffer in preparation for storing connection names
					readOffset = CONNECTION_OFFSET; //used to offset the file pointer past connection headers

					//iterate through all but the last connections tied to current room
					int i;
					for (i = 0; i < curRoom->maxConnections - 1; i++)
					{
						fseek(file, readOffset, SEEK_CUR); //move the file pointer to the ith connection
						fread(rmBuffer, strlen(curRoom->connections[i]->name), 1, file); //read the name of that connection into rmBuffer
						fseek(file, 1, SEEK_CUR);//pass over the newline character
						printf("%s, ", rmBuffer); //print the connection name to screen
						memset(rmBuffer, '\0', sizeof(rmBuffer)); //clear the room name buffer
					}

					//read the current room's last connection and print it to screen followed by a period and a newline character
					fseek(file, readOffset, SEEK_CUR);
					fread(rmBuffer, strlen(curRoom->connections[curRoom->maxConnections - 1]->name), 1, file);
					printf("%s.\n", rmBuffer);

					memset(rmBuffer, '\0', sizeof(rmBuffer)); //clear the room name buffer

					//rewind the file in case the user inputs and invalid connection name and the current room data needs to be reprinted
					rewind(file); 

					//get the room the plahyer wants to move to
					printf("WHERE TO? > ");
					scanf("%s", rmBuffer);
				}while (!isValidRoom(curRoom, rmBuffer)); //make sure the user input a valid room name

				fclose(file); //close the file associated with player's current location
				curRoom = goToNextRoom(curRoom,rmBuffer); //get the next room the player will traverse

				printf("\n");
				fprintf(pathFile,"%s\n",curRoom->name); //update the list of rooms the player has moved through
				steps++; //increment the number of steps
			
			}
			else //print an error message if a room file could not be opened and exit the program
			{
				fprintf(stderr, "Could not open %s\n", fileName);
				exit(EXIT_FAILURE);
			}
		}

		//informs the user that he/she has found the end room and how many steps it took to get there
		printf("YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\nYOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n",steps);
		
		rewind(pathFile); //move the victory path's file pointer to the beginning of the file so that the whole file can be read
		int ch = getc(pathFile); //get the first character in this file
		
		//read the entire victory path file
		while(ch != EOF)
		{
			printf("%c",ch);
			ch = getc(pathFile);
			
		}
		
		//close the victory path file then delete it
		fclose(pathFile);
		remove(pathFileName);

	}
	else //print an error message and exit the program if the victory path file was not created/opened successfully
	{
		fprintf(stderr, "Could not open %s\n", pathFileName);
		exit(EXIT_FAILURE);
	}
}
