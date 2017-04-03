The programs in this project use Python 2.7.5.
https://www.python.org/

There are two programs included in this project:
1) coins.py
2) testCoins.py

coins.py
----------------------------
The purpose of this program is to make change for a given amount. This program takes as argument a .txt file containing a list of coin values on one line followed by an integer amount the user wishes to make change for using the values on the previous line. The input file should take on the following form:

[1,2,5,7]
21
[1,5,10,25]
50

In this case, change will be made for an amount of 21 using the [1,2,5,7] coin system and change for 50 will be made using the system [1,5,10,25].

During execution, coins.py will run a brute force, greedy and dynamic programming algorithm on each amount in the input file. The results of each algorithm, namely the number of coins and the which coins were used, will be written to a <inputFileName>change.txt.

Note that the brute force algorithm is extremely inefficient and will not perform with large inputs. It is recommended that amount values in the input file do not exceed 65.

To run this program, navigate to the file's location and type this command into the shell or command prompt:

python coins.py <inputFile.txt>


testCoins.py
----------------------------
The purpose of this program is test the brute force, greedy and dynamic programming algorithms on several different amounts using various coin systems. This program takes two command line arguments, a MIN and a MAX. These arguments will set the bounds for a range of amounts. For example if MIN = 2000 and MAX = 2200, then each algorithm will make change for amounts in the interval [2000,2200]. Note, that if testing the brute force algorithm, the user should either limit the value of MAX to 27 in order to achieve a reasonable execution time.

At the start of execution, a menu will be displayed listing the available algorithms. The user should then input either 1, 2, or 3 to select an algorithm and run a set of three tests.

Test 1 will make change using the coin system [1,5,10,25] on a range of amounts ranging from MIN to MAX with a scale factor of 5. The results this test will be written to a <[slowTest | greedyTest | dpTest]>_Q4.csv file. 

Test 2 will make change using the coin systems [1,2,6,12,24,48,60] and [1,6,13,37,150] on a range of amounts ranging from MIN to MAX with a scale factor of 1. The results this test will be written to a <[slowTest | greedyTest | dpTest]>_Q5.csv file. 

Test 3 will make change using the coin system [1,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32] on a range of amounts ranging from MIN to MAX with a scale factor of 1. The results this test will be written to a <[slowTest | greedyTest | dpTest]>_Q6.csv file. 

To run this program, make sure both coins.py and testCoins.py are in the same location. Then navigate to the this location and type this command into the shell or command prompt:

python testCoins.py <MIN> <MAX>