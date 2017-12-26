//This file is a console executable of BullsCows game. It implements user interaction. For gameplay see FBullsCowsGame class.

#include <iostream>
#include <string>
#include "FBullsCowsGame.h"

using FText = std::string;
using int32 = int;
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;

int32 main()
{
	do
	{
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain() == true);

	return 0;
}


void PrintIntro()
{
	//prints the intro to the game
	std::cout << "Welcome to Bulls and Cows game!\n";
	std::cout << "Try and guess a word from " << BCGame.GetHiddenWordLength() << " letters.\n";
	return;
}
void PlayGame()
{	
	BCGame.Reset();
	//lets player make a guess and prints it back, repeated MaxTries times
	int32 MaxTries = BCGame.GetMaxTries();

	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= BCGame.GetMaxTries())
	{
		FText Guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n";
		
	}
	PrintGameSummary();
}
FText GetValidGuess()
{
	//gets guess from the player
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_status;
	
	do {
		std::cout << "\nTry " << BCGame.GetCurrentTry() << ". Enter your guess: ";
		getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		
		switch (Status)
		{
		case EGuessStatus::Not_isogram:
			std::cout << "Not an isogram!\n";
			break;
		case EGuessStatus::Not_lowercase:
			std::cout << "Not lowercase!\n";
			break;
		case EGuessStatus::Wrong_length:
			std::cout << "Wrong length! Please enter a " << BCGame.GetHiddenWordLength() << " word\n" ;
			break;
		default:
			break;
		}
		//std::cout << std::endl;
	} while (Status != EGuessStatus::OK);

	return Guess;
}
bool AskToPlayAgain()
{
	FText Response = "";
	std::cout << "Play again with same hidden word?(y/n)\n";
	getline(std::cin, Response);
	std::cout << std::endl;
	return (Response[0] == 'y') || (Response[0] == 'Y');
}
void PrintGameSummary() {
	if (BCGame.IsGameWon()){
		std::cout << "\nCongrats! You guessed right and WON!\n";
	}
	else {
		std::cout << "\nYou lost. Get better luck next time!\n";
	}
}
