// Erich Viebrock
// e_viebrock@u.pacific.edu
// Header file for Blackjack class
/*
	The main controller for the game. It must maintain a deck of cards, 
	a dealer's hand and the player's hands. This object is responsible for 
	moving cards from the deck to the hands, controlling the flow of the 
	game (player and dealer turns), and determing the outcome of the game.
*/

#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <vector>
#include "Hand.h"
#include "BasicException.h"
#include "Deck.h"

using namespace std;

class Blackjack : public Hand
{
public:
	Blackjack();
	void addDealer(Deck& deck, Hand& dealer);
	void addPlayer(Deck& deck);
	void printInitialDHand(Hand& dealer);
	void printDHand(Hand& dealer);
	void printHands();
	void playGame(Blackjack& blackjack, Deck& deck, Hand& dealer);
	void endGame(Blackjack& blackjack, Hand& dealer);
	void announceWinner(Blackjack& blackjack, Hand& dealer);

	vector<Hand> players;
	int numPlayers;
	char hitStay;
};

#endif
