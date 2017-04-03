/* **************************************************************************************
** Author: Conrad Lewin
** Date: 10/1/2015
** Description: A simple guess the number game.
***************************************************************************************/
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	int answer;
	int guess;
	int guessCount = 0;
	bool gameWon = false; //boolean flag that tracks whether or not the game has been won

	//get the number to be  guessed by the player
	cout << "Enter the number for the player to guess." << endl;
	cin >> answer;

	//prompt the player to guess the number
	cout << "Enter your guess." << endl;

	while (!gameWon) //while the player has failed to guess the number...
	{
		guessCount++; //track the number of guesses
		cin >> guess; //get the player's guess

		//Checks the player's guess against the game's answer and provide a hint or end the game loop.
		if (guess < answer)
		{
			cout << "Too low - try again." << endl;
		}
		else if (guess > answer)
		{
			cout << "Too high - try again." << endl;
		}
		else
		{
			gameWon = true;
		}
	}

	cout << "You guessed it in " << guessCount << " tries." << endl; //output the number of tries it took the player to get the right answer

	return 0;
}
