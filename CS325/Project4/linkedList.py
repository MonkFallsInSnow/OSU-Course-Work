import edge
import copy

#very basic linked list blueprint
class LinkedList:
	def __init__(self):
		self.firstLink = None

	def isEmpty():
		return self.firstLink == None

	def addLink(self,e):
		e.setNext(self.firstLink)
		self.firstLink = copy.copy(e)
		
