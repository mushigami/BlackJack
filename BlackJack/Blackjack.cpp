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
After player gets as many cards as he wants Dealer will reveal his vard, 
and hit until it reaches 17. 

If the player has Ace and ten-point card, he wins
If the dealer exceeds the 21, player wins,
If the player exceeds 21, he loses(busts).
If the player's cards' value in total more than dealer's, he wins.
Otherwise he loses

Lastly if the player and the dealer has the same sum or both have blackjack 
then it's a draw(except blackjack)

General:
- Deck
- Players
- Table

Deck:
- 13 different types of cards(no suit atm)
- x


*/