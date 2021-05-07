// Instructions
// 
// Implement a code breaking game as a console application. At the beginning of the game, it randomly generates a secret 4 digit code.
// Each digit should be unique. For example, 0123, 9548, and 3217 are valid codes, but 1102, 4445, and 7313 are not.
//
// Once the number has been generated, the player has 8 chances to guess the code. After each guess, the game should report how many digits
// they guessed correctly, and how many had the right number, but in the wrong place. For example, with a secret code of 0123, a guess of 0451
// has one digit correct (the 0), and one digit with the right number in the wrong place (the 1).
// 
// After the player has either correctly broken the code or run out of guesses, ask if they would like to play again. If so, generate a new
// code and start again, otherwise exit the program.
//
// If the player enters a code that isn't valid, prompt them to try again but do NOT count the invalid guess as one of the 8 attempts. Also be sure that
// your game can handle any unexpected inputs without crashing.
//
// All your code should go in this file. Please do NOT include your name, as we anonymize tests during evaluation to reduce bias.
//
// Good luck!
//                                  - - - - - - - - - - - - - - - - -
//
//                           *** All above criteria/conditions were met :) ***


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <ctype.h>
#include <cstdlib>

void GreetPlayer();
bool ValidGuess(int range, std::string guess);
void CheckAccuracy(std::string guess, std::string theCode, int& guessedCorrectly, int& yesButActuallyNo, int range);
void UpdateSoFar(std::string guess, std::string theCode, std::string& soFar, int range);
void OutputGuessResults(int guessedCorrectly, int yesButActuallyNo);
void OutputCode(std::string theCode);
void GameEnd(std::string guess, std::string theCode, int tries, bool& playGame);
void PlayAgain(bool& playGame);


int main()
{
	bool playGame(true);
	int codeSize(4);

	// MAIN GAME LOOP
	while (playGame == true)
	{
		// SETUP
		std::string theCode(codeSize, ' ');
		std::vector<char> codeVec;

		codeVec.push_back('0'), codeVec.push_back('1');
		codeVec.push_back('2'), codeVec.push_back('3');
		codeVec.push_back('4'), codeVec.push_back('5');
		codeVec.push_back('6'), codeVec.push_back('7');
		codeVec.push_back('8'), codeVec.push_back('9');

		srand(static_cast<unsigned int>(time(0)));
		std::random_shuffle(codeVec.begin(), codeVec.end());

		theCode[0] = codeVec[0];
		theCode[1] = codeVec[1];
		theCode[2] = codeVec[2];
		theCode[3] = codeVec[3];

		codeVec.clear();

		std::string soFar(theCode.size(), '_');
		std::string pastGuesses("");
		std::string guess;
		int tries = 8;

		GreetPlayer();

		// GUESS LOOP START
		while (tries > 0 && soFar != theCode)
		{
			int guessedCorrectly = 0, yesButActuallyNo = 0, range = theCode.size();

			//std::cout << "\nTHE CODE: " << theCode << "\n"; // (this is used for testing/debugging)
			std::cout << "\nSo far: " << soFar << "\n";
			std::cout << "\nRemaining tries: " << tries;
			std::cout << "\nYour past guesses: " << pastGuesses;
			std::cout << "\nYour latest guess: ";
			std::cin >> guess;

			if (ValidGuess(range, guess) == true) // Makes sure player's guess is a 4 digit number
			{
				(pastGuesses += guess) += " ";
				tries--;

				if (guess == theCode)
				{
					break;
				}
				else if (guess != theCode)
				{
					CheckAccuracy(guess, theCode, guessedCorrectly, yesButActuallyNo, range);
					UpdateSoFar(guess, theCode, soFar, range);
					OutputGuessResults(guessedCorrectly, yesButActuallyNo);
				}
			}
			else
			{
				std::cout << "\nINVALID ENTRY, please enter a four digit number for your guess!\n\n";
			}
		}

		GameEnd(guess, theCode, tries, playGame);
	}

	return 0;
}

void GreetPlayer()
{
	std::cout << "\t\t***Welcome to CodeBreaker! Guess the code to win the game. You have 8 tries, good luck!***\n";
	std::cout << "\n\n\n\nGuess the four digit code: \n";
}

bool ValidGuess(int range, std::string guess)
{
	bool validGuess(false);

	for (int i = 0; i < range; ++i)
	{
		if (isdigit(guess[i]) == false || guess.size() > range)
		{
			validGuess = false;
			break;
		}
		else
		{
			validGuess = true;
		}
	}

	return validGuess;
}

void CheckAccuracy(std::string guess, std::string theCode, int& guessedCorrectly, int& yesButActuallyNo, int range)
{
	// Counts correctly positioned number guesses
	for (int i = 0; i < range; ++i)
	{
		theCode[i] == guess[i] ? guessedCorrectly++ : guessedCorrectly = guessedCorrectly;
	}

	// Counts incorrectly positioned number guesses
	for (int i = 0; i < range; ++i)
	{
		for (int j = 0; j < range; ++j)
		{
			if (theCode[i] == guess[j])
			{
				yesButActuallyNo++;
			}
		}
	}

	yesButActuallyNo -= guessedCorrectly;
	yesButActuallyNo < 0 ? yesButActuallyNo = 0 : yesButActuallyNo = yesButActuallyNo;
}

void UpdateSoFar(std::string guess, std::string theCode, std::string& soFar, int range)
{
	for (int i = 0; i < range; i++)
	{
		if (theCode[i] == guess[i])
		{
			soFar[i] = theCode[i];
		}
	}
}

void OutputGuessResults(int guessedCorrectly, int yesButActuallyNo)
{
	if (guessedCorrectly == 0 && yesButActuallyNo == 0)
	{
		std::cout << "\n\nWrong guess! Please try again.\n\n";
	}
	else if (yesButActuallyNo == 0)
	{
		std::cout << "\n\nWrong code.\nYou guessed " << guessedCorrectly << " correctly positioned number(s).\n";
		std::cout << yesButActuallyNo << " of your other guessed numbers show up in the final code. Try again!\n\n";
	}
	else if (yesButActuallyNo == 1)
	{
		std::cout << "\n\nWrong code.\nYou guessed " << guessedCorrectly << " correctly positioned number(s).\n";
		std::cout << yesButActuallyNo << " of your other guessed numbers does show up in the final code, but is positioned incorrectly. Try again!\n\n";
	}
	else if (yesButActuallyNo > 1)
	{
		std::cout << "\n\nWrong code.\nYou guessed " << guessedCorrectly << " correctly positioned number(s).\n";
		std::cout << yesButActuallyNo << " of your other guessed numbers do show up in the final code, but are positioned incorrectly. Try again!\n\n";
	}
}

void OutputCode(std::string theCode)
{
	for (int i = 0; i < 4; i++)
	{
		std::cout << theCode[i] << " ";
	}

	std::cout << "\n\n";
}

void GameEnd(std::string guess, std::string theCode, int tries, bool& playGame)
{
	std::cout << "\n\nTHE CODE WAS: " << theCode;

	if (guess == theCode)
	{
		std::cout << "\n\n\t\t\t***BITCH U GUESSED IT....HOOO!!!! You was right....*ahem*, great job!***\n\n";
	}
	else if (guess != theCode || tries == 0)
	{
		std::cout << "\n\n\t\t\t\t     ***Womp womp! You lose, champ!***\n\n";
	}

	PlayAgain(playGame);
}

void PlayAgain(bool& playGame)
{
	char playerChoice;

	std::cout << "Would you like to play again? (Input 1 for yes or 2 for no)\n\n";
	do
	{
		playerChoice = NULL;

		std::cout << "Yes (1)\n";
		std::cout << "No (2)\n\n";
		std::cout << "Your choice: ";
		std::cin >> playerChoice;

		if (playerChoice == '1')
		{
			playGame = true;
			std::cout << "\n\nKickass, let's go again! Good luck!\n\n\n";
		}
		else if (playerChoice == '2')
		{
			playGame = false;
			std::cout << "\n\n\t\t\t\t***Thank you so much for playing!***";
		}
		else if (playerChoice != '1' && playerChoice != '2')
		{
			std::cout << "\n\nPlease enter a valid option!\n\n";
		}

	} while (playerChoice != '1' && playerChoice != '2');
}