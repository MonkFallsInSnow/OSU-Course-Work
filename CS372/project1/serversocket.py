'''
Author: Conrad Lewin
Class: CS 372 @ Oregon State University
Date: 2/9/2017
Filename: serversocket.py
Description: Class file the provides the blueprint for the chat server socket
'''

import sys
from socket import socket, AF_INET, SOCK_STREAM, error

BUFFER_SIZE = 500

class ServerSocket:
	#creates the socket
	def __init__(self,(host,port)):
		try:
			self.socket = socket(AF_INET,SOCK_STREAM)
			self.socket.bind((host,port))
			self.socket.listen(5)
		except error as e:
			print '{0} ({1})'.format(e,e.errno)
			sys.exit(1)
	
	#awaits a connection from a client, then initiates chat functionality
	def connect(self):
		while True:
			conn,addr = self.socket.accept()
			print 'Connection established with {0}'.format(addr)
			
			self.__chat(conn)
			
			conn.close()
			print 'Connection closed with {0}.'.format(addr)
	
	#sends an receives messages to and from the client respectively
	def __chat(self,conn):
		while(True):
			msg = conn.recv(BUFFER_SIZE)
			
			if '\quit' in msg:
				break
				
			print '{0}'.format(msg)
			
			msg = raw_input('Server> ')	
			conn.send('Server> {0}'.format(msg))
			
			if '\quit' in msg:
				break
		