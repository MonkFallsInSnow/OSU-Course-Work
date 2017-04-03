import vertex
import edge
import linkedList
from math import sqrt,pow
from operator import attrgetter

#constants
X = 0
Y = 1

#defines a complete graph
#vertList = list of vertex objects that make up the graph
#edgeList = list of edge objects that connect vertices in the graph
#adjList = list of linked lists. the index of the list corresponds to a vertex id.
#the linked lists at each index represent the graph connectivity. all vertices and edges
#in the adjacency list are shallow copies of their counterparts
class Graph:
	def __init__(self):
		self.vertList = []
		self.edgeList = []
		self.adjList = []
		

	#-------------getters--------------------------------------------------------------------------

	#get vertex by id
	def getVertex(self,id):
		if int(id) >= 0 and int(id) <= len(self.vertList):
			return self.vertList[int(id)]
		else:
			return None

	#get edge by description (a tuple of two vertex objects)
	def getEdge(self,desc):
		v1 = desc[0]

		curVert = self.adjList[int(desc[0].getId())].firstLink
		while curVert != None:
			cur = curVert.getEdgeDesc()
			if cur == (desc[0],desc[1]) or cur == (desc[1],desc[0]):
				return curVert
			curVert = curVert.getNext()

		return None

	#get adjacency list
	def getAdjList(self):
		return self.adjList

	#get vertex list
	def getVertList(self):
		return self.vertList

	#get edge list
	def getEdgeList(self):
		return self.edgeList

	#--------end getters------------------------------------------------------------------------------------

	#creates a single graph vertex
	def addVertex(self,id,cords):
		vert = vertex.Vertex(id,cords)
		self.vertList.append(vert)

	#creates all edges for a complete graph
	def createEdges(self):
		for i in range(len(self.vertList)):
			v1 = self.vertList[i]
			cords1 = self.vertList[i].getCords()
			count = i + 1
			while count < len(self.vertList):
				v2 = self.vertList[count]
				cords2 = self.vertList[count].getCords()
				dist = self.getDistance(cords1,cords2)
				newEdge = edge.Edge((v1,v2),dist)
				self.edgeList.append(newEdge)
				count += 1

	#calculate edge weight
	#firstVert = cords (a tuple) of first vertex object
	#secondVert = cords (a tuple) of second vertex object
	def getDistance(self,firstVert, secondVert):
			x1 = firstVert[X]
			x2 = secondVert[X]
			y1 = firstVert[Y]
			y2 = secondVert[Y]
			dist = sqrt(pow(x1 - x2,2) +  pow(y1 - y2,2))
			return int(round(dist))

	#creates and adjaceny list for the graph
	def createAdjList(self):
		for vert in self.vertList:
			id = vert.getId()
			newList = linkedList.LinkedList()
			self.adjList.append(newList)
			for e in self.edgeList:
				edgeName = e.getEdgeDesc()
				if edgeName[0].getId() == id or edgeName[1].getId() == id:
					newList.addLink(e)

	#used in kruskalMST
	def __makeSets(self):
		for v in self.vertList:
			v.getSet().add(v.getId())
		
	def __joinSets(self,verts):
		newSet = verts[0].getSet().union(verts[1].getSet())
		
		for v in newSet:
			vert = self.getVertex(v)
			vert.setSet(newSet)

	#returns a minimum spanning tree
	#the mst is a list of edges in order of smallest to largest weight
	def kruskalMST(self):
		mstrSet = []
		self.__makeSets()
		sortedEdgeList = sorted(self.edgeList,key=attrgetter('weight'))
		for e in sortedEdgeList:
			verts = e.getEdgeDesc()
			if verts[0].getSet() != verts[1].getSet():
				if verts not in mstrSet:
					mstrSet.append(self.getEdge(verts))
				self.__joinSets(verts)
		return mstrSet

	
	def dfs(self,root):
		stack = []
		path = []
		#visited = []

		stack.append(root)
		
		while len(stack) != 0:
			vert = stack.pop()
			vert.visited = True
			path.append(vert)

			curEdge = self.adjList[int(vert.getId())].firstLink
			while curEdge != None:
				if curEdge.getEdgeDesc()[0].visited == False:
					stack.append(curEdge.getEdgeDesc()[0])
				elif curEdge.getEdgeDesc()[1].visited == False:
					stack.append(curEdge.getEdgeDesc()[1])
						

				curEdge = curEdge.getNext()

		return path


	def reset(self):
		for v in self.vertList:
			v.reset()
			