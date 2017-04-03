#ifndef SMALLSH_H
#define SMALLSH_H

struct bgProc* saveProc(int spawnpid); //saves information about a background process
void catchFgSignal(int sigNum); //catches interrupt signals sent to foreground processes
void catchBgSignal(int sigNum); //catches child terminations signals sent by background processes
void runShell(); //runs the shell
char** parseCommand(char* command, int len,char** inputFile,char** outputFile,int* isBackground); //parses the user input command
void exitShell(); //exits the shell
void changeDir(char* path); //changes the current working directory
void printStatus(int exitStatus); //prints the exit status of the most recently terminated process
int runCommand(char** args,char* inputFile,char* outputFile,int isBackground); //executes the user command

#endif