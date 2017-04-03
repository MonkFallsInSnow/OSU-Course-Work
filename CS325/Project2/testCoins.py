import coins as p2
from sys import argv,exit
from csv import writer


#constants
CHANGE = 1
NUM_COINS = 2
TIME = 3
NUM_DENOM = 0
AVG_TIME = 1

try:
	MIN = int(argv[1])
	MAX = int(argv[2])

except IndexError:
	print 'Usage: python testCoins.py <MIN> <MAX>'
	exit(1)
except ValueError:
	print 'Usage: python testCoins.py <MIN> <MAX>'
	exit(1)

#performs a simple cursory test the user can review while waiting for the largest
#tests to be completed
def baseTest(algo):
	#list of algorithm results
	result = []

	#coin systems
	denom1 = [1,2,4,8]
	denom2 = [1,3,7,12]

	#amounts to make change for
	amnt1 = 15
	amnt2 = 29
	amnt3 = 31

	#run tests
	result.append(algo(denom1,amnt1))
	result.append(algo(denom2,amnt2))
	result.append(algo(denom2,amnt3))

	#display test results
	print 'Base Test'
	print '---------'

	print 'Coins: ' + str(denom1) + '\n' + 'Amount: ' + str(amnt1) + '\n' + 'Change: ' + str(result[0][CHANGE]) \
		+ '\n' + 'Number of Coins: ' + str(result[0][NUM_COINS]) + '\n'

	print 'Coins: ' + str(denom2) + '\n' + 'Amount: ' + str(amnt2) + '\n' + 'Change: ' + str(result[1][CHANGE]) \
		+ '\n' + 'Number of Coins: ' + str(result[1][NUM_COINS]) + '\n'

	print 'Coins: ' + str(denom2) + '\n' + 'Amount: ' + str(amnt3) + '\n' + 'Change: ' + str(result[2][CHANGE]) \
		+ '\n' + 'Number of Coins: ' + str(result[2][NUM_COINS]) + '\n'



def test1(algo,outputFile):
	result = []
	sumTime = 0
	avgTime = 0

	#coin system
	denom = [1,5,10,25]

	#list of amounts to make change for
	amnt = list(xrange(MIN,MAX + 1,5))

	#run algorithm on each amount
	for i in xrange(len(amnt)):
		result.append(algo(denom,amnt[i]))

	#write results to a csv file
	with open(outputFile,'w') as dataFile:
		csvFile = writer(dataFile)
		csvFile.writerow(['Amount','Num Coins','Time'])

		for i in xrange(len(result)):
			csvFile.writerow([amnt[i],result[i][NUM_COINS],result[i][TIME]])
			sumTime += result[i][TIME]

	#calculate the average run time
	avgTime = sumTime / len(result)

	return (len(denom),avgTime)



def test2(algo,outputFile):
	result1 = []
	result2 = []
	data = []
	sumTime = 0
	avgTime = 0

	#coin systems
	denom1 = [1, 2, 6, 12, 24, 48, 60]
	denom2 = [1, 6, 13, 37, 150]

	#list of amounts to make change for
	amnt = list(xrange(MIN,MAX + 1))

	#run algorithm on each amount using both coin systems
	for i in xrange(len(amnt)):
		result1.append(algo(denom1,amnt[i]))
		result2.append(algo(denom2,amnt[i]))

	#write results to a csv file
	with open(outputFile,'w') as dataFile:
		csvFile = writer(dataFile)

		csvFile.writerow(['Coins',denom1])
		csvFile.writerow(['Amount','Num Coins','Time'])

		for i in xrange(len(result1)):
			csvFile.writerow([amnt[i],result1[i][NUM_COINS],result1[i][TIME]])
			sumTime += result1[i][TIME]
		
		avgTime = sumTime / len(result1)
		data.append((len(denom1),avgTime))
		sumTime = 0

		csvFile.writerow([])
		csvFile.writerow(['Coins',denom2])
		csvFile.writerow(['Amount','Num Coins','Time'])

		for i in xrange(len(result2)):
			csvFile.writerow([amnt[i],result2[i][NUM_COINS],result2[i][TIME]])
			sumTime += result2[i][TIME]
		
		avgTime = sumTime / len(result2)
		data.append((len(denom2),avgTime))

	return data



def test3(algo,outputFile):
	result = []
	sumTime = 0
	avgTime = 0

	#coin system
	denom = [1, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32]
	
	#list of amounts
	amnt = list(xrange(MIN,MAX + 1))

	#run algorithm on each amount
	for i in xrange(len(amnt)):
		result.append(algo(denom,amnt[i]))

	#write resutls to a csv file
	with open(outputFile,'w') as dataFile:
		csvFile = writer(dataFile)
		csvFile.writerow(['Amount','Num Coins','Time'])

		for i in xrange(len(result)):
			csvFile.writerow([amnt[i],result[i][NUM_COINS],result[i][TIME]])
			sumTime += result[i][TIME]
		
		avgTime = sumTime / len(result)

	return (len(denom),avgTime)



def main():
	data = []
	valid = False
	auxTestFile = ''

	#display program menu and get valid input
	while(valid == False):
		print '1) Brute Force Algorithm'
		print '2) Greedy Algorithm'
		print '3) Dynamic Algorithm'
		print ''

		func = int(raw_input('Enter the number of the algorithm you wish to test: '))

		if(func >= 1 and func <= 3):
			valid = True 
		else:
			print 'Invalid entry. Enter a number between 1 and 3.\n'

	#run all test on an algorithm selected by the user
	if(func == 1):
		auxTestFile = 'slowTest_Q8.csv'
		baseTest(p2.changeslow)
		print 'Running test 1...'
		data.append(test1(p2.changeslow,'slowTest_Q4.csv'))
		print 'Running test 2...'
		data.append(test2(p2.changeslow,'slowTest_Q5.csv'))
		print 'Running test 3...'
		data.append(test3(p2.changeslow,'slowTest_Q6.csv'))
	elif(func == 2):
		auxTestFile = 'greedyTest_Q8.csv'
		baseTest(p2.changegreedy)
		print 'Running test 1...'
		data.append(test1(p2.changegreedy,'greedyTest_Q4.csv'))
		print 'Running test 2...'
		data.append(test2(p2.changegreedy,'greedyTest_Q5.csv'))
		print 'Running test 3...'
		data.append(test3(p2.changegreedy,'greedyTest_Q6.csv'))
	elif(func == 3):
		auxTestFile = 'dpTest_Q8.csv'
		baseTest(p2.changedp)
		print 'Running test 1...'
		data.append(test1(p2.changedp,'dpTest_Q4.csv'))
		print 'Running test 2...'
		data.append(test2(p2.changedp,'dpTest_Q5.csv'))
		print 'Running test 3...'
		data.append(test3(p2.changedp,'dpTest_Q6.csv'))

	print 'All tests have been completed...'
	print 'Writing average run times as a function of coin denominations...'
	
	#write average runtimes as a function of the number of denominations to a csv file
	with open(auxTestFile,'w') as auxTest:
		csvFile = writer(auxTest)

		csvFile.writerow(['Num Denominations','Avg Run Time'])
		
		for i in xrange(len(data)):
			if(isinstance(data[i],list)):
				csvFile.writerow([data[i][0][NUM_DENOM],data[i][0][AVG_TIME]])
				csvFile.writerow([data[i][1][NUM_DENOM],data[i][1][AVG_TIME]])
			else:
				csvFile.writerow([data[i][NUM_DENOM],data[i][AVG_TIME]])

	print 'All tests have been written to csv files in the current directory.'
	print 'End program...'





if __name__ == '__main__':
	
	numArgs = len(argv)
	
	if(numArgs > 3 or int(argv[1]) > int(argv[2])):
		print 'Usage: python testCoins.py <MIN> <MAX>'
		exit(1)	
	
	main()
	
