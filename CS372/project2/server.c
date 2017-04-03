/********************************************************
* Author: Conrad Lewin									*
* Class: CS 372 @ Oregon State University				*
* Date: 3/10/2017										*
* Filename: server.c								    *
* Description: This file contains all the functions		*
* needed to set up and run the ftp server.				*
********************************************************/

#include "server.h"

#define BUFFER_SIZE 5000
#define MAX_INT_SIZE 16

/*
This function creates a socket, binds it to the server and listens for a connection.
int port: port number the server will listen on
return: a server socket
*/
int createSocket(int port)
{
	//server info struct
    struct sockaddr_in serverAddress; 
	
	//create socket
	int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
	{
		return -1;
	}
	
	//clear server struct
    memset(&serverAddress, '\0', sizeof(serverAddress));

	//define server attributes
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port); 

	//set server options
	int optval = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);
	
	//bind socket to server
    if(bind(sock, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0)
	{
		return -1;
	}
	
	//listen for a connection
    if(listen(sock, 10) < 0)
	{
		return -1;
	}
	
	return sock;
}


/*
This function creates a connection between client and server.
int sock: the socket used to listen for connections
return: the client connection
*/
int makeConnection(int sock)
{
	//accept a connection request made by the client
	int client = accept(sock,NULL,NULL);
	if(client < 0)
	{
		close(client);
		return -1;
	}
	
	return client;
}


/*
This function receives a message from the client by getting the message size, 
confirming that size was received and then saving that message in a buffer.
int sock: the connection to which bytes should be received
char* buffer: array used to store the received message
return: the number of bytes received or -1 if an error occurred
*/
int recvMsg(int sock, char* buffer)
{
	int got, bytes, size;
	
	//get message size
	got = recv(sock,buffer,BUFFER_SIZE,0);
	if(got < 0) 
	{
		return -1;
	}
	
	//convert message size to int
	int msgLen = atoi(buffer);
	
	//flush buffer
	memset(buffer, '\0', BUFFER_SIZE);
	
	//confirm message size was received
	if(_confirm(sock) < 0)
	{
		perror("Unable to confirm.");
		exit(1);
	}
	
	got = 0;
	bytes = 0;
	
	//as long as the number of bytes received by the client are fewer than the total
	//size of the message, continue receiving bytes
	while(bytes < msgLen)
	{
		got = recv(sock,buffer,BUFFER_SIZE,0);
		if(got < 0) 
		{
			return -1;
		}

		bytes += got;
	}

	return got;
}


/*
This function sends a message to the client by first sending the message size, 
receiving confirmation that the size was received and then sending the content of
the message.
int sock: the connection to which bytes should be sent
char* buffer: array used to read the message to be sent
return: the number of bytes sent or -1 if an error occurred
*/
int sendMsg(int sock, char* buffer)
{	
	int sent, got, bytes;
	
	//get length of the message
	int msgLen = strlen(buffer);
	
	//convert message length to string
	char* temp = malloc(MAX_INT_SIZE);
    snprintf(temp, MAX_INT_SIZE, "%d\n", msgLen); 
	
	//send message size
	sent = send(sock,temp,MAX_INT_SIZE,0);
	if(sent < 0) 
	{
		return -1;
	}
	
	//flush temp buffer
	memset(temp, '\0', MAX_INT_SIZE);
	
	//get confirmation that the size was received by the client
	got = recv(sock,temp,sizeof(char),0);
	if(got < 0) 
	{
		return -1;
	}
	
	//send message stored in buffer for as long as their bytes to send
	bytes = 0;
	while(bytes < msgLen)
	{
		sent = send(sock,buffer,msgLen,0);
		if(sent < 0) 
		{
			return -1;
		}
		
		bytes += sent;
	}
	
	free(temp);
	
	return sent;
}


/*
This function gets a string representation of all files and directories in
the server's present working directory.
char* buffer: character array used to store the contents of the server's pwd
*/
void getDirectoryListing(char* buffer)
{	
	//flush buffer
	memset(buffer, '\0', BUFFER_SIZE);
	
	//http://stackoverflow.com/questions/4204666/how-to-list-files-in-a-directory-in-a-c-program
	DIR* listing;
	struct dirent* dir;
	
	//open the current working directory
	listing = opendir(".");
	
	//copy the contents of the directory into the buffer, then close the directory
	if(listing)
	{
		while ((dir = readdir(listing)) != NULL)
		{
			strncat(buffer,dir->d_name,strlen(dir->d_name));
			strncat(buffer," ",sizeof(char));
		}

		closedir(listing);
	}
	//--------------------------------------------------------------------------------------------
}


/*
This function sends a file to the client.
int sock: the connection on which the file should be sent
FILE* file: file to be sent to the client
return: 1 if file was sent successfully, otherwise return -1
*/
int sendFile(int sock, FILE* file)
{
	printf("sending file...\n");
	fflush(stdout);
	
	//buffer to store file contents
	char buffer[BUFFER_SIZE];
	memset(buffer, '\0', BUFFER_SIZE);
	
	//read the content of the file into the buffer
	//once the buffer is full, send the contents of the buffer to the client
	//continue this process until the entire file has been sent
	int bytes;
	while((bytes = fread(buffer,sizeof(char),BUFFER_SIZE,file)) > 0)
	{
		int sent = send(sock,buffer,BUFFER_SIZE,0);
		if(sent < 0)
		{
			return -1;
		}
	}

	return 1;
}


/*
This function kills any child processes spawned by the server
int sig: signal code
*/
void cleanUp(int sig)
{
	int status;
	pid_t pid;
	
	while((pid = waitpid(-1, &status, WNOHANG)) != -1)
	{
		kill(pid,SIGTERM);
	}
}


/*
This function sends a 1 byte confirmation message. Used whenever a message size is received by the server.
int sock: the connection on which to send the message
*/
int _confirm(int sock)
{
	char msg = '!';
	int sent = send(sock,&msg,sizeof(char),0);
	if(sent < 0)
	{
		return -1;
	}
	
	return 1;
}
