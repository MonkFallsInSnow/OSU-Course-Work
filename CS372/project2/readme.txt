Conrad Lewin
Project 2
CS 372


Setup
======================================================================================================
Use the provided makefile to compile ftserver.c with the following command: 
	$ make

This will create an executable file called ftserver.

To remove the created executable, use this command: 
	$ make clean

ftclient.py does not require compilation


Usage
======================================================================================================
On the server, run the following command: 
	$ ftserver [port number]

On the client, run the following command: 
	$ python ftclient.py [SERVER HOST] [SERVER PORT] [COMMAND] [DATA PORT] <FILENAME>

ftserver will listen for connections on a given [port number], forking a new process for each
connection made.

ftclient.py will attempt to connect to a server identified by [SERVER HOST] on a given [port number].


Valid Client Commands
======================================================================================================
The -l command will direct the server to return a listing of all files and directories in
the server's current working directory.

The -g command will direct the server to return a file specified by the <FILENAME> argument. This file
will be saved in the client's current working directory. If a file with the given file name already
exists, then the user will be asked if they wish to overwrite the file. Electing to overwrite the file
will replace the file on the client sharing the name of the file returned by the server. Choosing the
option not to overwrite the file will present the user with a second prompt asking them to choose a
different file name. This dialog will loop as long as the user chooses not to overwrite and enters a file 
name present in the client's current working directory. 


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

C Socket Programming for Linux with a Server and Client Example Code
http://www.thegeekstuff.com/2011/12/c-socket-programming/?utm_source=feedburner

Linux Programmer's Manual FORK(2)
http://man7.org/linux/man-pages/man2/fork.2.html

Linux man page - waitpid(2)
https://linux.die.net/man/2/waitpid

Tracking the death of a child process
http://stackoverflow.com/questions/2377811/tracking-the-death-of-a-child-process

How to list files in a directory in a C program?
http://stackoverflow.com/questions/4204666/how-to-list-files-in-a-directory-in-a-c-program



Testing
======================================================================================================
This program was tested in the following manner:

1) connect to the OSU flip server from my local machine
2) open a second session to the flip server
3) run ftserver  
4) run ftclient.py with -l command
5) run ftclient.py with -g command

Connections where sometimes made on two different instances of flip. This was done by using one of the
two sessions to ssh into either flip1, flip2, or flip3.

For the -g command, several file types and lengths were requested for transfer to the client. These
include the following:

1) a short text file (15 bytes)
2) a medium sized text file (7,107 bytes)
3) a long text file (18,085 bytes)
4) a .pdf file (157000 bytes)
5) a .bin file (785000 bytes)
6) a .mp4 file (131 megabytes)


Extra Credit
==========================================================================================================
1) Works on two different instances of flip
2) Server forks a process for each connection made
3) Both text and binary files can be transferred from server to client