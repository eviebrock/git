// COMP53 - Fall 2012 - Project 5
// Author: Michael Doherty
/*
	The main controller for the game. It must maintain a deck of cards, 
	a dealer's hand and the player's hands. This object is responsible for 
	moving cards from the deck to the hands, controlling the flow of the 
	game (player and dealer turns), and determing the outcome of the game.
*/


#ifndef DECK_DOT_H
#define DECK_DOT_H

#include <vector>
#include "Card.h"
#include "BasicException.h"

using namespace std;

class DeckException : public BasicException
{
public:

    // DEFAULT CONSTRUCTOR
    DeckException()
    : BasicException(string("UNIDENTIFIED DeckException"))
    { }

    // CONSTRUCTOR WITH MESSAGE
    DeckException(const string& s)
    : BasicException(string("DeckException: ")+s)
    { }

};

class Deck
{
public:
    // CONSTRUCTOR
    Deck();

    // ACCESSORS
    short cardsRemaining();
    Card peek(short i);

    // MODIFIERS
    Card deal();
    void shuffle();

private:
    vector<Card> cards_in_deck;
};

#endif
