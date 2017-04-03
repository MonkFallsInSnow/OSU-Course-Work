'''
Author: Conrad Lewin
Class: CS 372 @ Oregon State University
Date: 3/10/2017
Filename: client.py
Description: This class file defines the blueprint for an ftp client socket connection
'''

import os,errno
import socket

class ClientSocket(object):
	#constructor - creates socket and saves both host and port
	def __init__(self,host,port):
		self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		self.host = host
		self.port = port
		self.MAX_MSG_SIZE = 16
		
		
	#this function makes a connection between the server host and the client on a given port.
	#return true if the connection was successful and false if unsuccessful
	def makeConnection(self):
		try:
			self.sock.connect((self.host,self.port))
		except socket.error as e:
			print 'Error {0}: {1}'.format(e.errno,os.strerror(e.errno))
			return False
			
		return True
	
	
	#this function receives a confirmation message from the server indicating 
	#the size of the message to be sent by the client was received.
	#return true if the confirmation was received successfully and false if unsuccessful
	def __getConfirmation(self):
		rcvd = self.sock.recv(self.MAX_MSG_SIZE)
		
		if rcvd is None:
			return False
			
		return True
	

	#this function sends a confirmation message to the server indicating 
	#the size of the message to be sent by the server was received
	#return true if the confirmation was sent successfully and false if unsuccessful
	def __sendConfirmation(self):
		sent = self.sock.send('!')

		if sent <= 0:
			return False
			
		return True
	
	
	#this function sends the size of a message to be sent from client to server
	#return true if the size was sent/confirmed successfully and false if unsuccessful
	def __sendSize(self,size):
		sent = self.sock.send(str(size))
		
		if sent == 0:
			return False
			
		return self.__getConfirmation()
	
	
	#this function receives the size of a message sent by the server to the client
	#return the size of the message or -1 if an error occurred
	def __getSize(self):
		rcvd = self.sock.recv(self.MAX_MSG_SIZE)
		
		if rcvd is not None:
			#get position of terminating char
			pos = rcvd.index('\0')

			#strip off terminating char
			rcvd = rcvd[:pos] 
			
			#convert size received as string to an int
			return int(rcvd)
			
		return -1
	
	
	#this function sends a message to the server
	#return true if the message was sent successfully or false if unsuccessful
	def sendMsg(self,size,msg):
		#send the size of the message to the server
		if self.__sendSize(size) == True:
			#https://docs.python.org/2/howto/sockets.html#socket-howto
			bytes = 0
			
			#send the message for as long as there are bytes to send
			while bytes < size:
				sent = self.sock.send(msg[bytes:])

				if sent == 0:
					return False
					
				bytes = bytes + sent
			#---------------------------------------------------------
			
			return True
		else:
			return False
	

	
	#this function receives a message from the server
	#return the message if in fact the message was received, otherwise return None
	def recvMsg(self):
		#get size of the message to be received
		size = self.__getSize()
		
		#ensure a valid size was received
		if size <= 0:
			return None
		
		#confirm the message size was received, then receive the message sent by the server
		if self.__sendConfirmation() == True:
			msg = self.sock.recv(size)
			return msg
		else:
			return None
	

	#this function receives a file from the server
	#returns true if the file was received successfully and false if unsuccessful
	def recvFile(self,name,size):
		msg = ''
		
		#receive file bytes for as long as there are bytes to receive
		while len(msg) < size:
			temp = self.sock.recv(size - len(msg))
			
			if temp is None:
				return False
			
			msg += temp
		
		#prompt user to overwrite or rename the file if it already exists on the client
		if os.path.isfile(name):
			print 'File already exists!'
			while True:
				input = raw_input('Overwrite? (y/n) ')
				if input.lower() == 'n':
					name = raw_input('Save file as: ')
					if os.path.isfile(name):
						print 'That file already exists!'
						continue
					break;
				elif input.lower() == 'y':
					break;
			
		#save the file to the client's present working directoy
		with open(name,'wb') as file:
			file.write(msg)
			
		return True
				
