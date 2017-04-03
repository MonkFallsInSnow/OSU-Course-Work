#include "smallsh.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <regex.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>

#define CHILD 0
#define TRUE 1
#define FALSE 0
#define IS_OUTPUT 1
#define IS_INPUT 2
#define MAX_PIDS 50
#define MAX_CMD_LEN 2048


//global vars
pid_t fgPID = -1; //tracks current foreground pid
struct bgProc* bgProcs[MAX_PIDS]; //array of background pids

//stores information relevant to a background process
struct bgProc
{
	pid_t bgPID; //background pid
	int active; //tracks whether or not the process is still running or has terminated
	int status; //tracks the process's exit status
};


//helper function that saves a background process in an array that will be periodically examined to determine 
//which processes have completed
struct bgProc* saveProc(pid_t spawnpid)
{
	int saved = FALSE;
	int count = 0;

	//create a new background process container and initialize its data variables
	struct bgProc* proc = malloc(sizeof(struct bgProc));
	proc->bgPID = spawnpid;
	proc->active = TRUE;

	//search for an empty spot in the global array for background processes
	while(saved == FALSE)
	{
		if(bgProcs[count] == NULL) //if an empty spot is found
		{
			bgProcs[count] = proc; //save the process information
			saved = TRUE;
		}
		
		count++;
	}
	
	return proc;
}


//this function kills a foreground process and outputs the signal number that interrupted the process
void catchFgSignal(int sigNum)
{
	fprintf(stdout,"Process terminated by %d\n",sigNum);
	fflush(stdout);
	kill(fgPID,SIGKILL);
}


//this function executes whenever a child process terminates, but ignores all foreground processes.
//if the child is a background processes, then the relevant data variables are updated to reflect this
//change in state. 
void catchBgSignal(int sigNum)
{
	int exitStatus = 0;
	
	int i;
	for(i = 0; i < MAX_PIDS; i++) //iterate through the bgProcs array, searching for the pid of the process that just completed
	{
		if(bgProcs[i] != NULL)
		{
			pid_t pid = waitpid(bgProcs[i]->bgPID,&exitStatus,WNOHANG); //get the child pid
			
			if(pid > 0) //if a valid pid is found, that is the currently examined background process has terminated
			{
				bgProcs[i]->active = FALSE; //indicate that the process is no longer running
				bgProcs[i]->status = exitStatus; //save its exit status
				kill(bgProcs[i]->bgPID,SIGKILL); //kill the zombie
			}
		}		
	}
}


//this function serves as the main procedure that controls the various shell operations
void runShell()
{
	int exitStatus = 0; //process exit code
	
	int i;
	for(i = 0; i < MAX_PIDS; i++) //initialize the global array of background processes
	{
		bgProcs[i] = NULL;
	}

	while (1)
	{
		char* inputFile = NULL; //input file name
		char* outputFile = NULL; //output file name
		int isBackground = FALSE; //indicates whether or not a command invokes a background process

		//initialize the command buffer
		char buffer[MAX_CMD_LEN];
		memset(buffer, '\0', sizeof(buffer));

		fprintf(stdout, ": "); //print command prompt
		fflush(stdout);
		
		fgets(buffer,sizeof(buffer),stdin); //get user command
		
		//int comment = 0;
		//parse the user command so that it may be passed to exec() during the fork or trigger one of the built in commands
		char** command = parseCommand(buffer,strlen(buffer),&inputFile,&outputFile,&isBackground);
		
		if(command[0] == '\0') //reprompt the user for a command if nothing but the return key was pressed
		{
			continue;
		}
		else if (strcmp("exit", command[0]) == 0) //built in exit command
		{
			//free the command array and exit the shell
			free(command); 
			command = NULL;
			exitShell();
		}
		else if (strcmp("cd", command[0]) == 0) //built in cd command
		{
			changeDir(command[1]); //change the current working directory 
		}
		else if (strcmp("status", command[0]) == 0) //built in status command
		{
			printStatus(exitStatus); //display the exit status of the most recently terminated process
		}
		else //runs all non-built in commands
		{
			fflush(stdout); //flush the output buffer
			exitStatus = runCommand(command,inputFile,outputFile,isBackground); //run the user command and save its exit status
		}
		
		//free the memory associated with the command list to prepare for the next command
		if(command != NULL)
		{
			free(command);
			command = NULL;
		}

		//check the global array of background processes for those that have been terminated.
		//print out the pids of all terminated processes and free the associated structs
		for(i = 0; i < MAX_PIDS; i++)
		{
			if(bgProcs[i] != NULL && bgProcs[i]->active == FALSE)
			{
				fflush(stdout);
				fprintf(stdout,"Background process %d terminated. Exit status: %d\n",bgProcs[i]->bgPID,bgProcs[i]->status);
				fflush(stdout);
				free(bgProcs[i]);
				bgProcs[i] = NULL;
			}
		}
	}
}

//this function parses the command string the user input into the shell
char** parseCommand(char* command, int len, char** inputFile,char** outputFile, int* isBackground)
{
	int outputRedirect = FALSE; //flag that indicates whether output redirection is necessary
	int inputRedirect = FALSE; //flag that indicates whether input redirection is necessary
	
	int count = 0;
	char* delim = " \n"; //command string delimiters
	
	char** args; //array of command arguments prepared for the exec() command
	args = malloc(len * sizeof(char*));
	assert(args != NULL);

	int i;
	for (i = 0; i < len; i++) //initialize the array of command arguments to NULL
	{
		args[i] = NULL;
	}

	char* token = strtok(command, delim); //get the first token in the command string

	while (token != NULL) //while there are still tokens to be extracted from the command string
	{
		//regular expression that checks for the presence of a a comment symbol in the token
		regex_t regex;
		regcomp(&regex,"^#",0);
		int isComment = regexec(&regex,token,0,NULL,0);

		if(outputRedirect == TRUE) //the user desires output redirection
		{
			outputRedirect = FALSE;
			*outputFile = token; //save the file name that will replace stdout
		}
		else if(inputRedirect == TRUE) //the user desires input redirection
		{
			inputRedirect = FALSE;
			*inputFile = token; //save the file name that will replace stdin
		}
		else if(isComment == 0) //there is a comment in the command string
		{
			args[count] = '\0'; //ignore all characters after the comment symbol (including the comment symbol)
			break;
		}
		else if(strcmp(token,"<") == 0) //the input redirection symbol was found in the command string
		{
			inputRedirect = TRUE; //set the input redirection flag
		}
		else if(strcmp(token,">") == 0) //the output redirection symbol was found in the command string
		{
			outputRedirect = TRUE; //set the output redirection flag
		}
		else if(strcmp(token,"&") == 0) //the command string indicates a process should run in the background
		{
			*isBackground = TRUE; //set the background process flag
		}
		else //save the current token only if it is a valid unix command or a file name. ignore all redirection and background process symbols
		{
			args[count++] = token;
		}

		token = strtok(NULL, delim); //get the next token
	}

	return args; //return the modified command string as an array of "strings"
}


//kills all processes started or currently being run by the shell.
void exitShell()
{
	int i;
	//loop through the global array of background processes, killing any lingering processes and freeing all related structs
	for(i = 0; i < MAX_PIDS; i++) 
	{
		if(bgProcs[i] != NULL)
		{
			kill(bgProcs[i]->bgPID,SIGKILL);
			free(bgProcs[i]);
			bgProcs[i] = NULL;
		}
	}
	exit(EXIT_SUCCESS); //exit the shell
}


//this function changes the current working directory
void changeDir(char* path)
{
	int dir;

	if (path == NULL) //if no path is passed to the function, that is if the command is merely cd
	{
		dir = chdir(getenv("HOME")); //then change the current working directory to the home directory
		
		if(dir == -1)
		{
			perror("Error:");
			return;
		}	
	}
	else //otherwise, change the current directory to the path indicated by the argument
	{
		dir = chdir(path);
		
		if(dir == -1) //print an error if the given directory is invalid
		{
			perror("Error:");
			return;
		}	
	}
}


//this function displays the exit status of the most recently terminated process
void printStatus(int exitStatus)
{
	fprintf(stdout,"exit value %d\n",exitStatus);
	fflush(stdout);
}


//this function creates child processes to run the user input commands
int runCommand(char** args,char* inputFile,char* outputFile,int isBackground)
{
	int status;
	int savedStdOut = dup(STDOUT_FILENO); //saves a copy of the stdout file descriptor
	int savedStdIn = dup(STDIN_FILENO); //saves a copy of the stdin file descriptor
	
	//make sure the dup() function worked
	if(savedStdOut == -1 || savedStdIn == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}

	pid_t spawnpid = fork(); //fork the process

	if(spawnpid == CHILD) //if in the child
	{
		//set default file descriptors
		int inputFD = -1; 
		int outputFD = -1;

		//if planning to run a background process
		if(isBackground == TRUE)
		{
			if(outputFile == NULL) //if there is no output redirection
			{
				//prepares output to be written to /dev/null
				outputFD = open("/dev/null",O_WRONLY); 
				if(outputFD == -1)
				{
					perror("Error");
					exit(EXIT_FAILURE);
				}

				dup2(outputFD,STDOUT_FILENO);
				close(outputFD);
			}

			if(inputFile == NULL) //if there is no input redirection
			{
				//prepares input to be taken from /dev/null
				inputFD = open("/dev/null",O_RDONLY);
				if(inputFD == -1)
				{
					perror("Error");
					exit(EXIT_FAILURE);
				}

				dup2(inputFD,STDIN_FILENO);
				close(inputFD);
			}
		}
		else //if planning to run a foreground process
		{
			if(outputFile != NULL) //if the command string indicated a need for output redirection
			{
				//open an existing file (truncate it) or create a new one to serve as a temporary stdout
				outputFD = open(outputFile,O_WRONLY | O_TRUNC | O_CREAT,0777); 
				if(outputFD == -1)
				{
					perror("Error");
					exit(EXIT_FAILURE);
				}

				dup2(outputFD,STDOUT_FILENO);
				close(outputFD);
			}

			if(inputFile != NULL) //if the command string indicated a need for input redirection
			{
				//open an existing file to serve as a temporary stdin stream
				inputFD = open(inputFile,O_RDONLY,0777);
				if(inputFD == -1)
				{
					perror("Error");
					exit(EXIT_FAILURE);
				}

				dup2(inputFD,STDIN_FILENO);
				close(inputFD);
			}
		}
		
		execvp(args[0],args); //execute the user input command
		
		perror("Error");
		exit(EXIT_FAILURE);
	}
	else if(spawnpid > CHILD) //if in the parent
	{
		pid_t exitpid;
		
		if(isBackground == TRUE) //if child is a background process
		{
			struct bgProc* proc = saveProc(spawnpid); //save the child's pid to the global array
			
			fprintf(stdout,"Process %d has started in the background.\n",spawnpid); //output that the process has begun executing
			fflush(stdout);
		}
		else //if child is a foreground process
		{
			fgPID = spawnpid; //save the child's pid
			exitpid = waitpid(spawnpid,&status,0); //wait for the child to terminate before the parent resumes execution
		}

		//reset stdin to its default value
		if(inputFile != NULL)
		{
			dup2(savedStdIn,STDIN_FILENO);
		}

		//reset stdout to its default value
		if(outputFile != NULL)
		{
			dup2(savedStdOut,STDOUT_FILENO);
		}

		fflush(stdout);
		return WEXITSTATUS(status); //return the child's exit status
	}
	else
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
}








