/******************************************************************
** Author: Conrad Lewin
** Date: 10/01/2015
** Description: Asks the user for a filename and then outputs the 
** contents of that file, if it exists.
*******************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main()
{
	const string OUTPUT_FILENAME = "./sum.txt"; //the output filename specified by the homework guidelines

	std::ifstream inputFile;
	std::ofstream outputFile;

	string filename; //stores the user specified filename
	string fileText; //stores the text in the user specified file

	//get the filename
	cout << "Enter a filename." << endl;
	getline(cin,filename);

	//open the file to read
	inputFile.open(filename.c_str());

	//check for the existence of the file (if the file was opened successfully)
	if (inputFile)
	{
		int sum = 0; //accumulator variable used to calculate a sum

		//for as long as there is content in the file, read that content and get the sum of the integers that comprise that content
		while (inputFile >> fileText)
		{
			sum += atoi(fileText.c_str()); //converts the string representations of each number in the file to integers before adding them together
			
			//cout << fileText << endl;
		}

		inputFile.close(); //close the file being read

		outputFile.open(OUTPUT_FILENAME.c_str()); //open a file to write to

		outputFile << sum; //write the value of variable sum to the output file

		outputFile.close();	//close the file being written to
	}
	else //if the input file can't be found
	{
		cout << "Could not access file." << endl; //inform the user that the file doesn't exist
	}

	
	return 0;
}

