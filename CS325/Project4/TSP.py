import graph
from operator import itemgetter
from sys import argv,exit

#constants
CITY_ID = 0
X = 1
Y = 2

#------------------------------------------Euclidean TSP------------------------------------------------------------ 

def formSubgraph(gPrime,subGraph,treeEdges):
	for v in gPrime.getVertList():
		subGraph.vertList.append(v)

	for e in treeEdges:
		subGraph.edgeList.append(e)

	subGraph.createAdjList()

#not done
def getPath(g,tree):
	path = []
	for root in tree:
		v1 = root.getEdgeDesc()[0]
		v2 = root.getEdgeDesc()[1]
		for e in tree:
			return

	return path

#not done
def makeTour(g,path):
	weight = 0
	path.append(path[0])

	for i in range(len(path) - 1):
		weight += g.getDistance(path[i].getCords(),path[i+1].getCords())

	path.pop()
	tour = {'name':'Euclidean TSP','len':weight,'certificate':tuple(path)} 

	return tour

def euclideanTSP(theMap):
	minWeight = float('inf')
	optimal = None
	mst = theMap.kruskalMST()
	subGraph = graph.Graph()
	formSubgraph(theMap,subGraph,mst)

	for i in range(len(subGraph.vertList)):
		path = subGraph.dfs(subGraph.vertList[i])
		tour = makeTour(subGraph,path)
		if tour['len'] < minWeight:
			optimal = tour
			minWeight = tour['len']
		subGraph.reset()
	return optimal

#----------------------------------------End Euclidean TSP------------------------------------------------------------


def vladTSP():
	tour = {'name':'Vlad TSP','len':float('inf'),'certificate':(0,0,0)} #example output
	return tour

def charlesTSP():
	tour = {'name':'Charles TSP','len':float('inf'),'certificate':(0,0,0)} #example output
	return tour

def main():
	results = []
	theMap = graph.Graph()

	print('Creating graph...')
	with open(argv[1],'r') as inputFile:
		for line in inputFile:
			temp = line.split()
			theMap.addVertex(temp[CITY_ID],(int(temp[X]),int(temp[Y])))

	#create graph
	theMap.createEdges()
	theMap.createAdjList()

	#run Conrad's aglorithm
	print('Running Euclidean TSP...')
	tour = euclideanTSP(theMap)
	results.append(tour)
	theMap.reset()
	print('done...' + '\n')

	#run Vlad's algorithm
	print('Running Vlad\'s TSP...')
	tour = vladTSP() #adjust parameter list
	results.append(tour)
	print('done...' + '\n')

	#run Charles's algorithm
	print('Running Charles\'s TSP...')
	tour = charlesTSP() #adjust parameter list
	results.append(tour)
	print('done...' + '\n')

	print('Finding "optimal" solution...')
	optimal = sorted(results,key=itemgetter('len'))[0]

	print(optimal['name'] + ' produced optimal solution...' + '\n')

	print('Creating output file...')
	fd = argv[1].split()
	fd.append('.tour')
	fileName = ''.join(str(elem) for elem in fd)
	
	print('Writing result to ' + fileName + '...')

	with open(fileName, 'w') as outputFile:
		outputFile.write(str(optimal['len']) + '\n')
		cert = optimal['certificate']
		for c in cert:
			outputFile.write(c.getId() + '\n')

	print('End program...')

	return			






if __name__ == '__main__':
	try:
		arg = argv[1]
	except IndexError:
		print('Usage: python tsp.py <inputFile.txt>')
		exit(1)
	main()
