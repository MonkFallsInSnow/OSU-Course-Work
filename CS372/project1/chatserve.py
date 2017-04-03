'''
Author: Conrad Lewin
Class: CS 372 @ Oregon State University
Date: 2/9/2017
Filename: chatserve.py
Description: Starts up a chat server
'''

import serversocket
import socket,sys

def runServer():
	#ensure the correct number of arguments are given on the command line
	if len(sys.argv) != 2:
		print 'Usage python chatserve.py <port number>'
		sys.exit(1)
	
	host = socket.gethostname() 					#get the server's host name
	port = int(sys.argv[1]) 						#save the port that will accept client connetions
	soc = serversocket.ServerSocket((host,port)) 	#create the socket
	
	print 'Socket created on {0}. Listening for a connection on port {1}'.format(host,port)

	#await a connection and exchange messages with the client
	soc.connect()

if __name__ == "__main__":
	runServer()