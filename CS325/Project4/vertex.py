#defines a vertex object
#id = city id (string).
#cords = tuple of integers representing x and y coordinates
#set = integer id used in Kruskal's algorithm to define sets of vertices
#visited = boolean that indicates whether or not a vertex has been visited

class Vertex:
	def __init__(self,name,pos):
		self.id = name
		self.cords = pos
		self.set = set()
		self.visited = False

	def getId(self):
		return self.id

	def getCords(self):
		return self.cords

	def getSet(self):
		return self.set

	def setSet(self,s):
		self.set = s

	#resets a single vertex (only the mutable data)
	def reset(self):
		self.set = None
		self.visited = False

	