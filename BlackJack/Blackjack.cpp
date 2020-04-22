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

const int IGNORE_CHARS = 256;
const char * INPUT_ERROR_STRING = "Input error! Please try again.";

void ShowInstructions();
void InitializeDealer(Deck &deck);
void InitializePlayer(Player &player, const char * playerName);
void PrintCard(const Card &card);
void PrintDeck(const Deck &deck);
void StartDeal(Deck &deck, Player &player, Player &dealer);
void PlayGame(Player &player);
bool IsGameOver();

int main()
{

	srand(time(NULL));

	Player player{};

	InitializePlayer(player, "Player1");

	do
	{
		PlayGame(player);
	} while (WantToPlayAgain());

	WaitForKeyPress();
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
		strcpy_s(player.playerName, playerName);
	}
	player.hasBlackJack = false;
	player.hasWon = false;

}

void InitializeDealer(Deck &deck)
{
	int card{ 0 };
	for (int i = 0; i < MAX_RANK; i++)
	{
		for (int j = 0;j < MAX_SUIT; j++)
		{
			deck.totalCards[card].rank = static_cast<CardRank>(i);
			deck.totalCards[card].suit = static_cast<CardSuit>(j);
			card++;
		}
	}
}

void PlayGame()
{

	ClearScreen();
	ShowInstructions();

	Deck deck{};
	InitializeDealer(deck);
	PrintDeck(deck);

	int drawnCards[MAX_PLAYER_CARDS]{ 0 };
	do
	{

	} while (!IsGameOver());
}

int* DrawCards()
{
	int drawnCards[MAX_PLAYER_CARDS]{ 0 };
	for (int i = 0; i < MAX_PLAYER_CARDS; i++)
	{
		drawnCards[i] = -1; // initialize all elements to -1.
	}

	do
	{
	drawnCards[i] = rand() % MAX_PLAYER_CARDS
	}
	while(!IsValidDraw)
	for (int i = 0; i < 4; i++)
	{
		player.playerCards[i] = rand() % BOARD_SIZE
	}

	guess.row = rand() % BOARD_SIZE;
	guess.col = rand() % BOARD_SIZE;
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
	default:
		std::cout << "_" << '?' << " ";
		break;
	}
}