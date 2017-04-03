/********************************************************
* Author: Conrad Lewin									*
* Class: CS 372 @ Oregon State University				*
* Date: 3/10/2017										*
* Filename: ftserver.c								    *
* Description: This file contains the logic to start up *
* the server and handle any requests it may receive		*
* from the client.										*
********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "server.h"

#define BUFFER_SIZE 5000
#define MAX_INT_SIZE 16

void getMsgWrapper(int sock, char* buffer);
void sendMsgWrapper(int sock, char* buffer);
void sendCmdValidationMsg(int sock, char* buffer, char* msg);

int main(int argc, char *argv[])
{
	//http://stackoverflow.com/questions/2377811/tracking-the-death-of-a-child-process
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = cleanUp;
	sigaction(SIGCHLD, &sa, NULL);
	//---------------------------------------------------------------------------------
	
	int serverSock;
	int port;
	char buffer[BUFFER_SIZE];
	
	//ensure the correct number of arguments were passed on the command line
	if(argc != 2)
	{
		printf("Usage: ftserver [port]\n");
		exit(1);
	}
	
	//get the port number and create a socket (starts the server)
	port = atoi(argv[1]);
	serverSock = createSocket(port);
	
	//print the status of the server 
	if(serverSock < 0)
	{
		printf("Unable to start server.\n");
	}
	else
	{
		char host[1024];
		gethostname(host,sizeof(host));
		
		printf("Server (%s) started. Awaiting connection on port %d.\n", host, port);
	}
	
	//await connections and handle requests until a terminating signal is received
	while(1)
	{
		//make a connection with the client
		int conn = makeConnection(serverSock);
		if(conn < 0)
		{
			printf("Connection to client was either terminated or in error. Awaiting new connection.\n");
		}
		else
		{
			//print connection status
			printf("Connection established.\n");
			fflush(stdout);
			
			//fork a process
			pid_t pid = fork();

			if(pid < 0)
			{
				perror("Unable to fork process.\n");
				exit(1);
			}
			else if(pid == 0) //child process
			{
				int dataSock, dataConn;
				char cmd1[] = "-l";
				char cmd2[] = "-g";
				
				//get command
				getMsgWrapper(conn,buffer);
				
				//handle -l command
				if(strcmp(cmd1,buffer) == 0) 
				{
					//send command validation
					char msg[] = "Valid command received.";
					sendCmdValidationMsg(conn,buffer,msg);
					
					//get data port
					getMsgWrapper(conn,buffer);
					
					//create new data transfer connection
					dataSock = createSocket(atoi(buffer));
					dataConn = makeConnection(dataSock);
					
					//send directory listing
					getDirectoryListing(buffer);
					sendMsgWrapper(dataConn,buffer);
					printf("Directory listing sent.");
					fflush(stdout);
					
					//close data connection
					close(dataSock);
				}
				//handle -g command
				else if(strcmp(cmd2,buffer) == 0) 
				{
					//send command validation
					char msg[] = "Valid command received.";
					sendCmdValidationMsg(conn,buffer,msg);
					
					//get data port
					getMsgWrapper(conn,buffer);
					
					//create new data transfer connection
					dataSock = createSocket(atoi(buffer));
					dataConn = makeConnection(dataSock);
			
					//get filename
					getMsgWrapper(conn,buffer);
					
					//open file (if exists)
					FILE* file = fopen(buffer,"rb");
					if(file != NULL)
					{
						//get total file size
						fseek(file,0,SEEK_END);
						int fileSize = ftell(file);
						fseek(file,0,SEEK_SET);
						
						//send total file size
						snprintf(buffer, BUFFER_SIZE, "%d", fileSize); 
						sendMsgWrapper(conn,buffer);
						
						//print file transfer status
						if(sendFile(dataConn,file) < 0)
						{
							printf("File transfer error.\n");
						}
						
						printf("File transfer successful.\n");	

						//close file
						fclose(file);
					}
					else
					{
						printf("Request received for non-existent file.\n");
						fflush(stdout);
						
						//send an error message if the file does not exist or could not be opened
						memset(buffer, '\0', BUFFER_SIZE);
						strcpy(buffer,"Unable to retrieve file. Check filename and try again.");
						sendMsgWrapper(conn,buffer);
					}	
					
					//close data connection
					close(dataSock);
				}
				else
				{
					//send error message to client
					char msg[] = "Invalid command given. Command must be either -l or -g.";
					sendCmdValidationMsg(conn,buffer,msg);
				}
			}
			
			//parent process
			
		}	
	}
	
	//close connection
	close(serverSock);
	return 0;
}


//A wrapper function for recvMsg() that displays an error message when necessary
void getMsgWrapper(int sock,char* buffer)
{
	memset(buffer, '\0', BUFFER_SIZE);
	
	int bytesRcvd = recvMsg(sock,buffer);
	if(bytesRcvd < 0)
	{
		perror("Unable to receive message\n");
		exit(1);
	}
}

//A wrapper function for sendMsg() that displays an error message when necessary
void sendMsgWrapper(int sock,char* buffer)
{
	int bytesSent = sendMsg(sock,buffer);
	if(bytesSent < 0)
	{
		perror("Unable to send message\n");
		exit(1);
	}

	memset(buffer, '\0', BUFFER_SIZE);
}

//This function uses sendMsgWrapper() to inform the client of whether or not a valid command was sent
void sendCmdValidationMsg(int sock, char* buffer, char* msg)
{
	memset(buffer, '\0', BUFFER_SIZE);
	strcpy(buffer,msg);
	sendMsgWrapper(sock,buffer);
}
