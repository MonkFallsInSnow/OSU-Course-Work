from sys import argv,exit
import time

#constant
MICRO_SECONDS = 1000000


def changeslow(coins,amount):

	start = time.time()

	def mincoins(coinArr, amt):
		
		# create a list to hold amt of coins
		coinTally = [0 for c in coinArr]
		# start value used for comparison and check coin val
		coinTally[0] = amt                             
		for each in coinArr:
			# if the coin is less than or equal to the current amt
			if each <= amt: 
			# find amt to make change subtraction 1 of given coin                           
				temp = (mincoins(coinArr, amt - each)) 
				# add 1 of that coin each time you search for amount w/out it
				temp[coinArr.index(each)] += 1         
				# if the sum at the given level of all coins used is greater than
				# the brute force temp result found, temp result is now new smallest      
				if sum(coinTally) > sum(temp):             
					coinTally = temp                   
					bestSum = temp

		return coinTally
	
	minlist = mincoins(coins, amount)

	end = time.time() - start

	numCoins = sum(minlist)
	return ('Algorithm changeslow', minlist, numCoins, end)




def changegreedy(coins,amount):
	start = time.time()

	#find the largest coin denomination
	maxIndex = len(coins) - 1

	#initialize those variables that will contain solution data
	result = [0] * len(coins)
	numCoins = 0

	#while change can still be made
	while(amount > 0):
		#find the largest value that can be subtracted from the current amount
		#without creating a negative number
		if(coins[maxIndex] <= amount):
			#find out how many times that coin value goes into the amount
			#and subtract that integer quotient from the amount. 
			result[maxIndex] = amount // coins[maxIndex]
			amount -= coins[maxIndex] * result[maxIndex]
			numCoins += result[maxIndex]
		
		#consider a new largest coin value
		maxIndex -= 1
	
	end = (time.time() - start) * MICRO_SECONDS

	return ('Algorithm changegreedy', result, numCoins, end)



def changedp(coins,amount):
	start = time.time()
	
	minCoins = [0] * (amount + 1)
	coinsUsed = [0] * (amount + 1)
	numCoins = [0] * len(coins)
	
	for changeSubproblem in range(amount + 1):
	
		coinsNeeded = changeSubproblem
		if (changeSubproblem == 0):
			lastCoinUsed = 0
		else:
			lastCoinUsed = 1
			
		for coin in coins:
			if (coin <= changeSubproblem):
				if (1 + minCoins[changeSubproblem - coin] < coinsNeeded):
					coinsNeeded = 1 + minCoins[changeSubproblem - coin]
					lastCoinUsed = coin
		
		minCoins[changeSubproblem] = coinsNeeded
		coinsUsed[changeSubproblem] = lastCoinUsed
		
	coin = amount
	
	while coin > 0:
		coinUsed = coinsUsed[coin]
		numCoins[coins.index(coinUsed)] += 1
		coin -= coinUsed

	end = (time.time() - start) * MICRO_SECONDS
	
	return ('Algorithm dpchange', numCoins, minCoins[amount], end)



def main():

	print 'Making Change - Project 2'
	print '-------------------------'
	
	# parallel lists
	coinDenoms = []
	amounts = []
	
	print 'Reading input file...'
	
	#read the input file
	with open(argv[1],'r') as inputFile:
		lineCount = 1
		for line in inputFile:
			if(lineCount % 2 != 0):
				newstr = line.replace('[', '').replace(']', '')		
				if(newstr != '\n'):				
					coinDenoms.append(map(int,newstr.strip().split(',')))
			else:
				amnt = int(line)
				amounts.append(amnt)
			lineCount += 1

	print 'Data collected...'
	print 'Running algorithms...'

	#list of alogorithm results
	results = []
	
	#run tests for each algorithm
	for i in xrange(len(coinDenoms)):
		print 'Run ' + str(i+1) + ' of changeslow'
		results.append(changeslow(coinDenoms[i],amounts[i]))
		print 'Run ' + str(i+1) + ' of changgreedy'
		results.append(changegreedy(coinDenoms[i],amounts[i]))
		print 'Run ' + str(i+1) + ' of changedp'
		results.append(changedp(coinDenoms[i],amounts[i]))

	# create output file
	fd = argv[1].split('.txt')
	fd.append('change.txt')
	fileName = ''.join(str(elem) for elem in fd)
	
	print 'Writing results to ' + fileName + '...'

	#write results to output file
	with open(fileName,'w') as outputFile:
		for elem in results:
			outputFile.write(elem[0] + '\n')
			outputFile.write(str(elem[1]) + '\n')
			outputFile.write(str(elem[2]) + '\n')

	print 'Closing output file...'
	print 'End program...'




if __name__ == '__main__':
	try:
		arg = argv[1]
	except IndexError:
		print 'Usage: python coins.py <inputFile.txt>'
		exit(1)
	main()






