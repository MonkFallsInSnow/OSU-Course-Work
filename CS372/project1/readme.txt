Conrad Lewin
Project 1
CS 372


Setup
======================================================================================================
Use the provided makefile to compile chatclient.c with the following command: 
	$ make

This will create an executable file called chatclient.

To remove the created executable, use this command: 
	$ make clean

chatserve.py does not require compilation


Usage
======================================================================================================
On the server, run the following command: 
	$ python chatserve.py <port number>

On the client, run the following command: 
	$ chatclient <hostname> <port number>

chatserve.py will listen for connections on a given <port number>.
chatclient will attempt to connect to a server identified by <hostname> on a given <port number>.

Once the client has connected to the server, the user will be asked to enter a handle. This handle
should be no longer than 10 characters. After a handle is decided upon, the client will be asked to
send a text message to the server. These messages should be no longer than 500 characters. The server
will then receive this message and will be given the chance to respond. Either the server or the client
can terminate the connection by sending the \quit command in their message. This will terminate the
connection and end execution of the program on the client, while the server will continue to listen
for subsequent connections until and interrupt signal is received (Ctrl-C).


Resources
======================================================================================================
Beej's Guide to Network Programming: Using Internet Sockets
http://beej.us/guide/bgnet/output/html/singlepage/bgnet.html

Socket Programming HOWTO
https://docs.python.org/2/howto/sockets.html#creating-a-socket

Python Network Programming
https://www.tutorialspoint.com/python/python_networking.htm

17.2. socket — Low-level networking interface
https://docs.python.org/2/library/socket.html


Testing
======================================================================================================
This program was tested in the following manner:

1) connect to the OSU flip server from my local machine
2) open a second session to the flip server
3) run chatserve.py 
4) run chatclient
5) exchange messages between hosts

Connections where sometimes made on two different instances of flip. This was done by using one of the
two sessions to ssh into either flip1, flip2, or flip3