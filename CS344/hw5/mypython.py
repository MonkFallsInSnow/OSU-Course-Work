from __future__ import print_function
from random import seed,randint

def createFiles(numFiles):
	'''Creates a given number of files containing
	a random string of 10 lowercase letters'''
	
	#constants
	LETTER_A = 97
	LETTER_Z = 122
	MAX_LETTERS = 10

	#empty list that will store file names
	fileList = []

	#random seed
	seed()

	#create files
	for i in range(0,numFiles):
		#create a file name and add that to the list
		fileList.append('file' + str(i + 1) + '.txt')

		#create a file with this name
		myFile = open(fileList[i],'w')

		#will store the file's contents
		string = ''
		
		#generate 10 random numbers between 97 and 122,
		#convert them to their ASCII equivalents and
		#append them to the content string
		for j in range(0,MAX_LETTERS):
			string += chr(randint(LETTER_A,LETTER_Z))
	
		#appened a newline to the content string
		string += '\n'

		#write the string to the file, then close the file
		myFile.write(string)
		myFile.close()

	#return the list of file names
	return fileList


def getText(fileName):
	'''Reads the contents of a given file and 
	returns that text'''
	
	#open the given file for reading
	aFile = open(fileName,'r')

	#read the contents of the file, then close the file
	text = aFile.read()
	aFile.close()

	#return the content read from the file
	return text


def randMult():
	'''Generates 2 numbers between 1 and 47 then
	multiplies them, returning a tuple of the following
	form (num1,num2,product)'''

	#constants
	MIN = 1
	MAX = 47
	
	#random seed
	seed()

	#random numbers within the given range used in the
	#subsequent multiplication operation
	num1 = randint(MIN,MAX + 1)
	num2 = randint(MIN,MAX + 1)
	product = num1 * num2

	#return a tuple containing all the data used in the 
	#multiplication operation
	return (num1,num2,product)

#create 3 files containg a random string
fileList = createFiles(3)

#print the contents of each file
for curFile in fileList:
	print(curFile,'contents:', getText(curFile))

#multiply two random numbers together and get teh resulting tuple
result = randMult()

#print the contents of this tuple
print(result[0],'*',result[1],'=',result[2])
