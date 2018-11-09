#include "FBullCowGame.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()
#include <map>
#define TMap std::map

// forward declaration of function
int GenerateRandomNumber();

// default constructor
FBullCowGame::FBullCowGame() 
{ 
	Reset();
}

int32 FBullCowGame::GetCurrentTry() const 
{ 
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const 
{ 
	return MyHiddenWord.length(); 
}

bool FBullCowGame::IsGameWon() const 
{ 
	return bGameIsWon;
}

int32 FBullCowGame::GetMaxTries() const 
{
	TMap<int32, int32> WordLengthToMaxTries{ {4,10}, {5,15}, {6,20}, {7,30} };
	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	// if guess isn't isogram, return error
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	// if guess isn't all lowercase, return error
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	// if guess isn't correct length return error
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	else
		return EGuessStatus::OK;
	// otherwise, return OK
}

void FBullCowGame::Reset()
{
	MyCurrentTry = 1;
	GenerateHiddenWord();
	bGameIsWon = false;
	return;
}

//Recieves a VALID guess, and increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

	for (int32 MyHWChar = 0; MyHWChar < WordLength; MyHWChar++)
	{
		// compare letters against the hidden word.
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			// if they match, increment bulls if they're in the same place 
			if(Guess[GChar] == MyHiddenWord[MyHWChar])
			{
				if (MyHWChar == GChar)
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1) { return true; }
	TMap<char, bool> LetterSeen;
	for (auto Letter : Word)
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter])
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}

void FBullCowGame::GenerateHiddenWord()
{
	FString TempWord;
	int32 NumOfLines = 0;
	int32 RandomWordGenNumber = GenerateRandomNumber();
	std::ofstream OutputFile("Answer.txt");
	std::ifstream AvailableIsograms;
	AvailableIsograms.open("isograms.txt");
	if (AvailableIsograms.is_open())
	{
		while (std::getline(AvailableIsograms, TempWord))
		{
			++NumOfLines;
			if (NumOfLines == RandomWordGenNumber)
			{
				MyHiddenWord = TempWord;
			}
		}
	}
	else
	{
		std::cout << "\nFile did not open!\n\n";
	}
}

FString FBullCowGame::ReturnHiddenWord()
{
	return MyHiddenWord;
}

int32 GenerateRandomNumber()
{
	int GeneratedNumber;
	
	srand((int32)time(0));
	int32 RandomNumGen = (rand() % 100);
	for (int32 i = 0; i < RandomNumGen; i++)
	{
		GeneratedNumber = (rand() % RAND_MAX);
	}
	return GeneratedNumber;
}
