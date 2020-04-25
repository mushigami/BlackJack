//============================================================================
// Name        : Blackjack.cpp
// Author      : Samet
// Version     : v1.0
// Copyright   : Free
// Description : BlackJack in C++, Ansi-style
//============================================================================

/*
Game BlackJack:
The game is played with cards that can be shown as below.

Dealer	|	Player
-----	|	------
J X		|	K 3 5

As first trial card suits won't be used. And the cards used won't be tracked.
First both dealer and the player will get two cards.
Then player will be asked to either [H]it or [S]tand.
After player gets as many cards as he wants Dealer will reveal his card, 
and hit until it reaches 17. 

If the player has Ace and ten-point card, he does Blackjack(wins unless dealer also has blackjack)
If the dealer exceeds the 21, player wins,
If the player exceeds 21, he loses(busts).
If the player's cards' value in total more than dealer's, he wins(without busting).
Otherwise he loses

Lastly if the player and the dealer has the same sum or both have blackjack 
then it's a draw(except blackjack)

General:
- Deck
- Players
- Table

Deck:
- 13 different types of cards(no suit atm)

Player:
- Name
- Type(only AI atm)
- Cards (Struct Card, Struct Rank(later)

Table:
- A struct with where card is a subgroup.


TDD:
Step-1
------
main
{
	ShowInstructions();
	do
	{
		PlayGame(Player);
	}while(WantToPlayAgain);
}

Step-2
------
PlayGame(Player)
{
do{
	InitializePlayer()
	InitializeDealer()
	StartDeal() //Dealer has one card hidden. Player gets two cards
	DrawTable()
	do{
		AskHitOrStand()

		}while(!IsInputValid);
	UpdateTable()
	DrawTable() // to show again if there's a winner
	CheckResult()
}while(!IsGameOver())

DisplayResult()
}

*/

#include <iostream>
#include <cstring>
#include <cctype>
#include <ctime>
#include "Utils.h"

using namespace std;

enum
{
	MAX_PLAYER_CARDS = 15,
	PLAYER_NAME_SIZE = 8,
	TOTAL_CARDS = 52,
};
enum CardRank
{
	RANK_UNDEFINED=0,
	RANK_2,
	RANK_3,
	RANK_4,
	RANK_5,
	RANK_6,
	RANK_7,
	RANK_8,
	RANK_9,
	RANK_10,
	RANK_JACK,
	RANK_QUEEN,
	RANK_KING,
	RANK_ACE,
	MAX_RANK,
	
};

enum CardSuit
{
	SUIT_UNDEFINED=0,
	SUIT_CLUB,
	SUIT_DIAMOND,
	SUIT_SPADE,
	SUIT_HEART,
	MAX_SUIT,
};

struct Card
{
	CardRank rank{};
	CardSuit suit{};

};

struct Deck
{
	Card totalCards[TOTAL_CARDS];
};


struct Player
{
	Card playerCards[MAX_PLAYER_CARDS]{};
	char playerName[PLAYER_NAME_SIZE];
	bool hasBlackJack{ false };
	bool hasWon{ false };
};

bool operator==(const Card &card1, const Card &card2)
{
	return(card1.rank == card2.rank && card1.suit == card2.suit);
}


const int IGNORE_CHARS = 256;
const char * INPUT_ERROR_STRING = "Input error! Please try again.";

void ShowInstructions();
void InitializeDeck(Deck &deck);
void InitializePlayer(Player &player, const char * playerName);
void PrintCard(const Card &card);
void PrintDeck(const Deck &deck);
//void StartDeal(Deck &deck, Player &player, Player &dealer);
void PlayGame(Player &player, Player &dealer);
bool IsGameOver();
char AskHitOrStand();
void DrawAllCards(Card drawnCards[], int playerCards);
void DealCards(Player &player, Player &dealer, Card drawnCards[], int numberOfDrawnCards);
bool WantToPlayAgain();
void DisplayResult();


int main()
{

	srand(time(NULL));

	Player player;
	Player dealer;

	InitializePlayer(player, "Player1");
	InitializePlayer(dealer, "Dealer");

	do
	{
		PlayGame(player, dealer);
	} while (WantToPlayAgain());

	WaitForKeyPress();
	return 0;
}

void ShowInstructions()
{
	cout << "\t~BlackJack~" << endl << endl;
	cout << "Welcome to game of BlackJack!\nPlease find the instructions below!\n" << endl;

	cout << "INSTRUCTIONS:" << endl;
	cout << "-Dealer will get two cards, one faced down. Player will get two face-up cards" << endl;
	cout << "-Player has to choose either to [H]it or [S]tand." << endl;
	cout << "-Player will be dealt cards until it Stands" << endl;
	cout << "-If player busts dealer wins automatically. If not:" << endl;
	cout << "-After player finishes its round dealer will draw cards until reaches or exceeds 17" << endl;
	cout << "-If dealer busts, player wins." << endl;
	cout << "-Otherwise higher hand wins." << endl;
	cout << "-An Ace and a 10-point card constitutes a BlackJack(gives additional bonus)" << endl;

	cout << endl << endl;
	cout << "Dealer\t\t" << "Player" << endl;
	cout << "------\t\t" << "------" << endl;
	cout << "J_C X_X\t\t" << "5_H 3_S" << endl;
	cout << "\n\n\nPlease press [H] for Hit and [S] for Stand" << endl<<endl;

}

void InitializePlayer(Player &player, const char * playerName)
{
	if (playerName != nullptr && strlen(playerName) > 0)
	{
		strcpy(player.playerName, playerName);
	}
	player.hasBlackJack = false;
	player.hasWon = false;

}

void InitializeDeck(Deck &deck)
{
	int card{ 0 };
	for (int i = 1; i < MAX_RANK; i++)
	{
		for (int j = 1;j < MAX_SUIT; j++)
		{
			deck.totalCards[card].rank = static_cast<CardRank>(i);
			deck.totalCards[card].suit = static_cast<CardSuit>(j);
			card++;
		}
	}
}

void PlayGame(Player &player, Player &dealer)
{

	ClearScreen();
	ShowInstructions();

	Deck deck{};
	InitializeDeck(deck);
	//PrintDeck(deck);

	Card drawnCards[MAX_PLAYER_CARDS];
	DrawAllCards(drawnCards, MAX_PLAYER_CARDS);

	for (int i = 0; i < MAX_PLAYER_CARDS; i++)
	{
		PrintCard(drawnCards[i]);
	}
	char hitOrStand{};
	DealCards(player, dealer, drawnCards, MAX_PLAYER_CARDS);
	
	do{
		//ShowTable();
		hitOrStand = AskHitOrStand();

	}while(!IsGameOver());
	
	DisplayResult();

}

Card DrawCard()
{
	Card newCard;
	newCard.rank = static_cast<CardRank>(rand() % (MAX_RANK-1) + 1);
	newCard.suit = static_cast<CardSuit>(rand() % (MAX_SUIT-1) + 1);
	
	return newCard;

}

void DrawAllCards(Card drawnCards[], int numberOfDrawnCards )
{
	int i = 0;
	while (i < numberOfDrawnCards)
	{
		Card newCard;
		newCard = DrawCard();
		if (drawnCards[i] == newCard)
		{
			drawnCards[i].rank = RANK_UNDEFINED;
			drawnCards[i].suit = SUIT_UNDEFINED;
		}
		else
		{
			drawnCards[i] = newCard;
			i++;
		}
	}
}

void DealCards(Player &player, Player &dealer, Card drawnCards[], int numberOfDrawnCards)
{
	// To deal firs two cards of the player and the dealer
	int i = 0;
	player.playerCards[i] = drawnCards[i];
	dealer.playerCards[i] = drawnCards[i+1];
	player.playerCards[i+1] = drawnCards[i+2];
	dealer.playerCards[i+1] = drawnCards[i+3];
	
}
bool IsGameOver()
{
	return true;
}

void PrintDeck(const Deck &deck)
{
	for (int i = 0; i <TOTAL_CARDS; i++)
	{
			PrintCard(deck.totalCards[i]);
	}
}

char AskHitOrStand()
{
	const char validInput[2] = { 'h', 's' };
	
	return GetCharacter("Do you [H]it or [S]tand? ", "Wrong input. Please press [H] or [S]! ", validInput, 2 , CC_LOWER_CASE);
}

void PrintCard(const Card &card)
{
	switch (card.rank)
	{
	case CardRank::RANK_2:
		std::cout << '2';
		break;
	case CardRank::RANK_3:
		std::cout << '3';
		break;
	case CardRank::RANK_4:
		std::cout << '4';
		break;
	case CardRank::RANK_5:
		std::cout << '5';
		break;
	case CardRank::RANK_6:
		std::cout << '6';
		break;
	case CardRank::RANK_7:
		std::cout << '7';
		break;
	case CardRank::RANK_8:
		std::cout << '8';
		break;
	case CardRank::RANK_9:
		std::cout << '9';
		break;
	case CardRank::RANK_10:
		std::cout << 'T';
		break;
	case CardRank::RANK_JACK:
		std::cout << 'J';
		break;
	case CardRank::RANK_QUEEN:
		std::cout << 'Q';
		break;
	case CardRank::RANK_KING:
		std::cout << 'K';
		break;
	case CardRank::RANK_ACE:
		std::cout << 'A';
		break;
	case CardRank::MAX_RANK:
		std::cout <<"MAX";
		break;
	default:
		std::cout << '?';
		break;
	}

	switch (card.suit)
	{
	case CardSuit::SUIT_CLUB:
		std::cout <<"_"<< 'C' <<" ";
		break;
	case CardSuit::SUIT_DIAMOND:
		std::cout << "_" << 'D' << " ";
		break;
	case CardSuit::SUIT_HEART:
		std::cout << "_" << 'H' << " ";
		break;
	case CardSuit::SUIT_SPADE:
		std::cout << "_" << 'S' << " ";
		break;
	case CardSuit::MAX_SUIT:
		std::cout <<"MAX";
		break;
	default:
		std::cout << "_" << '?' << " ";
		break;
	}
}

bool WantToPlayAgain()
{
	char input;

	const char validInput[2] = { 'y', 'n' };

	input = GetCharacter("\nWould you like to play again? (y/n): ", INPUT_ERROR_STRING, validInput, 2, CC_LOWER_CASE);

	return input == 'y';
}

void DisplayResult()
{
	cout << "Result"<<endl;
}
