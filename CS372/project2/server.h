/********************************************************
* Author: Conrad Lewin									*
* Class: CS 372 @ Oregon State University				*
* Date: 3/10/2017										*
* Filename: server.h								    *
* Description: This file contains all the function		*
* prototypes and header files needed for server.c.		*
********************************************************/

#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdint.h>
#include <signal.h>
#include <dirent.h>

int createSocket(int port);
int makeConnection(int sock);
int recvMsg(int sock, char* buffer);
int sendMsg(int sock, char* buffer);
void getDirectoryListing(char* buffer);
int sendFile(int sock, FILE* file);
void cleanUp(int sig);
int _confirm(int sock);

#endif
