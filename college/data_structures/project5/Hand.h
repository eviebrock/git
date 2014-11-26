// Erich Viebrock
// e_viebrock@u.pacific.edu
// Header file for Hand class
/*
	A collection of cards held by the players or dealer. There must be a 
	method to add a	card to a hand. It must be possible to iterate through 
	the cards in the hand for display. There must be a method for 
	determining the score of a hand.
*/

#ifndef HAND_H
#define HAND_H

#include <vector>
#include "Deck.h"
#include "BasicException.h"
#include "Card.h"

using namespace std;

class HandException : public BasicException
{
public:

	// DEFAULT CONSTRUCTOR
	HandException()
	: BasicException(string("UNIDENTIFIED HandException"))
	{ }

	// CONSTRUCTOR WITH MESSAGE
	HandException(const string& s)
	: BasicException(string("HandException: ")+s)
	{ }

};

class Hand
{
public:
	// CONSTRUCTOR
	Hand();

	void addCard(Deck& deck);
	void setScore(int x);
	int getScore();
	void aceSubtract();
	int handSize();
	void printHand();

	vector<Card> cards_in_hand;
	int score;
};

#endif
