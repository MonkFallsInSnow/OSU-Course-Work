The following programs use python version 2.7.1
maxSubArray.py
testData.py

1) maxSubArray.py - uses the MSS_Problems.txt file as input for each algorithm to be tested
To run this program, make sure there is a file of bracket enclosed and comma separated whole numbers in the same directory
as the maxSubArray.py program. Multiple arrays should be placed each on its own line. Here is an example of a single line: [1, 2, -2, -5, 4, 6].
Once connected to the flip server, navigate to the directory that contains both MSS_Problems.txt and maxSubArray.py, and then type this command 
into the shell prompt: 

python maxSubArray.py

This will run the program and write the resulting output into a file called MSS_Results.txt.

2) testData.py - creates 10 sets of randomly generated arrays as input.
To run this program, make sure that both maxSubArray.py and testData.py are in the same directory. Then type this command into the shell prompt:

python testData.py

The user will then be asked to choose the algorithm they wish to test. After this choice has been made, another prompt will ask the user to enter the desired 
array size common to the first set of arrays. They will then be asked to enter a scale factor. This value will increase the array size of each successively 
created set of arrays by that factor. For example, if the max size for the arrays in the first set is 10 and the scale factor is 5, then the next set of arrays
will all have a size of 15, the next set will have arrays of size 20 and so on. The output for this program is appended to a file called dataAlgo#.csv, where the
# represents the number of the algorithm being tested. Since the data is appended to a file, if there is no such file by that name, then it will create it and write
the output to it, however, if the program is run a second time on the same algorithm it will append these results to the results already in the file. If this is undesired,
make sure to delete the appropriate file before running the test script on the same algorithm a second time.