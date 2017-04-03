/********************************************************
* Author: Conrad Lewin									*
* Class: CS 372 @ Oregon State University				*
* Date: 2/9/2017										*
* Filename: chatclient.c								*
* Description: A client program used to connect to a	*
* server in order to exchange short messages.			*
********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define HANDLE_SIZE 11
#define BUFFER_SIZE 501

int _createSocket();
void _setHandle(char* buffer);
int _sendMsg(int sock, char* buffer, int len);
int makeConnection(int* sockfd, struct sockaddr_in address, char* host, char* portno);
void chat(int sock);

int main(int argc, char *argv[])
{
	//socket vars
	int socket;
	char* port;
	char* hostname;
	struct sockaddr_in serverAddress;
	
	//ensure all command line arguments are present
	if(argc != 3)
	{
		fprintf(stderr,"Usage: chatclient <hostname> <port>\n");
		exit(1);
	}
	
	//save the host and port the client wishes to connect to
	hostname = argv[1];
	port = argv[2];
	
	//clear sockaddr_in struct
	memset(&serverAddress, '0', sizeof(serverAddress));
	
	//create a socket and connect to the server
	int status = makeConnection(&socket,serverAddress,hostname,port);
	
	//inform the user if a connection was successfully established
	if(status > 0)
	{
		printf("Connection established!\n");
		chat(socket);
	}
	else
	{
		fprintf(stderr,"Unable to connect. Goodbye.");
		exit(1);
	}

	return 0;
}

//creates a socket for the client to send and receive data
//returns the created socket
int _createSocket(struct addrinfo* res)
{
	int soc = socket(res->ai_family, res->ai_socktype,res->ai_protocol);
	if(socket < 0)
		perror("Unable to create socket");
	
	return soc;
}

//prints a welcome message and saves the user's chat handle in a buffer
//only HANDLE_SIZE number of characters will be saved in the buffer
void _setHandle(char* buffer)
{	
	printf("\n================Chatterbox================\n");
	printf("Welcome! Let's get you a handle (only 10 characters will be saved).\n");
	
	printf("Enter a handle: ");
	fgets(buffer,HANDLE_SIZE,stdin);
}

//sends a message to the server. if the message contains the string "\quit", 
//then the socket is closed and program exits.
//returns the number of bytes sent
int _sendMsg(int sock, char* buffer, int len)
{		
	int sent = send(sock,buffer,len,0);
	if (sent < 0) 
	{
		perror("Unable to send message");
		exit(1);
	}
	
	buffer[sent] = '\0';
	char* substring = strstr(buffer,"\\quit");
	
	if(substring)
	{
		close(sock);
		printf("Connection closed. Goodbye.\n");
		exit(0);
	}
	
	return sent;
}

//receives a message from the server. if the message contains the string "\quit", 
//then the socket is closed and program exits.
//returns the number of bytes received
int _recvMsg(int sock, char* buffer, int len)
{
	int got = recv(sock,buffer,len,0);
	if (got < 0) 
	{
		perror("Unable to receive message");
		exit(1);
	}
	
	buffer[got] = '\0';
	
	char* substring = strstr(buffer,"\\quit");
	if(substring)
	{
		close(sock);
		printf("Connection closed. Goodbye.\n");
		exit(0);
	}
	
	return got;
}

//establishes a socket connection with a server on a particular port as specified in the command line arguments.
//returns 1 if a connection was made, otherwise returns -1
int makeConnection(int* sockfd, struct sockaddr_in address, char* host, char* portno)
{	
	int status;
	struct addrinfo hints;
	struct addrinfo *serverInfo, *link;
	
	//define and verify socket characteristics
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	
	status = getaddrinfo(host,portno,&hints,&serverInfo);
	if(status != 0)
	{
		fprintf(stderr,"getaddrinfo error: %s\n", gai_strerror(status));
		return -1;
	}
	
	//find the server and make a connection
	for(link = serverInfo; link != NULL; link = link->ai_next)
	{
		*sockfd = _createSocket(link);
		if(*sockfd < 0)
		{
			continue;
		}
		
		if(connect(*sockfd, link->ai_addr, link->ai_addrlen) < 0)
		{
			perror("Unable to connect");
			continue;
		}
		
		break;
	}
	
	//quit if a no connection could be made
	if(link == NULL)
	{
		return -1;
	}

	//free the struct
	freeaddrinfo(serverInfo);
	
	//indicate a successful connection was made
	return 1;
}

//facilitates the exchange of message between client and server from the client's perspective
void chat(int sock)
{
	char buffer[BUFFER_SIZE];
	char handle[HANDLE_SIZE];
	char msg [BUFFER_SIZE + HANDLE_SIZE];
	
	//clear buffers
	memset(handle,'\0',sizeof(handle));
	memset(buffer,'\0',sizeof(buffer));
	
	//set client's handle
	_setHandle(handle);
	
	//replace the newline character at the end of the handle with a null character
	int len = strlen(handle) - 1;
	if(handle[len] == '\n')
	{
		handle[len] = '\0';
	}
	
	printf("Nice to meet you %s. Start talking!\nRemember, \"Brevity is the soul of wit.\" (only 500 characters per message)\n\n",handle);
	
	//for as long as the \quit command is neither sent or received
	while(1)
	{		
		//prepare the message buffer and print the user's handle
		msg[0] = '\0';
		printf("%s> ",handle);
		
		//get the user's message
		fgets(buffer,BUFFER_SIZE-1,stdin);
		
		//prepend the user's handle to the message received by fgets() 
		strcat(msg,handle);
		strcat(msg,"> ");
		strcat(msg,buffer);
		
		//send the message to the server and reset he buffer
		_sendMsg(sock,msg,strlen(msg)-1);
		memset(buffer,'\0',sizeof(buffer));
		
		//receive the message from the server, print that message and then clear the buffer
		_recvMsg(sock,buffer,BUFFER_SIZE);
		printf("%s\n",buffer);
		memset(buffer,'\0',sizeof(buffer));	
	}
}