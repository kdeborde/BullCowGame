#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;
void PrintIntro();
void PrintGameRules();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
FBullCowGame BCGame;
void PrintGameSummary();

int main()
{
	PrintGameRules();
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);
	return 0;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n\n";
	std::cout << "Your hidden word starts with the letter: " << BCGame.ReturnHiddenWord().at(0) << "\n\n";
	
	// is not won and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
		std::cout << std::endl;
	}
	PrintGameSummary();
	return;
}

void PrintGameRules()
{
	std::cout << "This is the bulls and cows game.\n";
	std::cout << "Do you need to learn how to play?(y/n): ";
	FText Response = "";
	std::getline(std::cin, Response);

	if (Response[0] == 'y' || Response[0] == 'Y')
	{
		std::cout << "\nOK, here's how to play:\n\n";
		std::cout << " An isogram is a word that does not have repeating letters.\n";
		std::cout << " In order to win the game, you must guess the isogram.\n";
		std::cout << " After each guess, you will be given the number of \"bulls\" and \"cows\".\n";
		std::cout << " If you get a \"Bull\", it means you have guessed a correct letter in the correct position.\n";
		std::cout << " If you get a \"Cow\", it means the letter is in the secret word, but you put it in the wrong position.\n";
		std::cout << " The number of letters and first letter of the word will be provided to you.\n";
		std::cout << " Good Luck!\n\n";
		std::cout << "Press enter to play...";
		std::string MoveOn;
		std::getline(std::cin, MoveOn);
		std::cout << "\n\n";
	}
	else
	{
		return;
	}
}

void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << std::endl;
	return;
}

// get a guess from a player and print it back
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of "  << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);
		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter a word with all lowercase letters\n\n";
			break;
		default:
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK);
	return Guess;
}

bool AskToPlayAgain()
{
	//BCGame.ReturnHiddenWord();
	std::cout << "Do you want to play agian with a new hidden word(y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE - YOU WIN!\n";
	}
	else
	{
		std::cout << "Better luck next time.\n\nYour hidden word was: " << BCGame.ReturnHiddenWord() << "\n\n";
	}
}
