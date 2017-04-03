'''
Author: Conrad Lewin
Class: CS 372 @ Oregon State University
Date: 3/10/2017
Filename: ftclient.py
Description: The main program file used to run the client process
'''

import sys
import client as c

#constants representing the indices of each argument within argv
HOST = 1
PORT = 2
CMD = 3
DATA_PORT = 4
FILENAME = 5

#ensures a given port number is within a valid range
def __checkPort(port):
	if port >= 0 and port <= 65535:
		return True
		
	return False
		

#run the client program
def runClient():
	if len(sys.argv) < 5 or len(sys.argv) > 6:
		print 'Usage: python ftclient.py [SERVER HOST] [SERVER PORT] [COMMAND] [DATA PORT] <FILENAME>'
		sys.exit(1)
		
	#validate server and data port values
	if __checkPort(int(sys.argv[PORT])) == False or __checkPort(int(sys.argv[DATA_PORT])) == False:
		print 'Invalid port number. Port should be a number between 0 and 65535'
		sys.exit(1)
		
	#create client socket
	client = c.ClientSocket(sys.argv[HOST],int(sys.argv[PORT]))

	#connect to server
	if client.makeConnection():
		print 'Connection made with {0}'.format(client.host)
	else:
		print 'Unable to make connection. Goodbye.'
		client.sock.close()
		sys.exit(1)
	
	#send command argument
	if client.sendMsg(len(sys.argv[CMD]),sys.argv[CMD]) == False:
		print 'Unable to send message.'
		client.sock.close()
		sys.exit(1)
	
	#get command argument validation
	msg = client.recvMsg()
	if msg is None:
		print 'Unable to receive message.'
		client.sock.close()
		sys.exit(1)
	
	if msg != 'Valid command received.':
		print 'Message Recvd: {0}'.format(msg)
		client.sock.close()
		sys.exit(1)
		
	#send data port	
	if client.sendMsg(len(sys.argv[DATA_PORT]),sys.argv[DATA_PORT]) == False:
		print 'Unable to send message.'
		client.sock.close()
		sys.exit(1)
	
	#create data port socket
	dataSock = c.ClientSocket(sys.argv[HOST],int(sys.argv[DATA_PORT]))
	
	#connect to server data socket
	if dataSock.makeConnection() == True:
		print 'Data transfer connection made with {0} on port {1}'.format(dataSock.host,dataSock.port)
	else:
		print 'Unable to make data transfer connection. Goodbye.'
		dataSock.sock.close()
		client.sock.close()
		sys.exit(1)
		
	#handle command results
	if sys.argv[CMD] == '-l':
		#get directory listing
		msg = dataSock.recvMsg()
		
		#display listing
		if msg is not None:
			print "\nDirectory Listing\n------------------------"
			print '{0}'.format(msg.replace(' ','\n'))
		else:
			print 'Directory listing transfer error.'
	elif sys.argv[CMD] == '-g':
		try:
			#send filename
			if client.sendMsg(len(sys.argv[FILENAME]),sys.argv[FILENAME]) == False:
				print 'Unable to send message.'
				client.sock.close()
				dataSock.sock.close()
				sys.exit(1)
		except IndexError:
			print 'The -g command requires a filename. Usage: python ftclient.py [SERVER HOST] [SERVER PORT] [COMMAND] [DATA PORT] <FILENAME>'
			sys.exit(1)
		
		
		#get file size
		fileSize = 0
		msg = client.recvMsg()
		if msg is not None:
			try:
				fileSize = int(msg)
			except ValueError:
				print msg
				sys.exit(1)
		else:
			print 'File transfer error.'
			sys.exit(1)
		
		#get file
		if dataSock.recvFile(sys.argv[FILENAME],fileSize) == False:
			print 'File transfer error.'
		
		#print status of file transfer
		print 'File transfered sucessfully.'
		
	#close data and control connection
	dataSock.sock.close()
	client.sock.close()
	
#main	
if __name__ == "__main__":
	runClient()
