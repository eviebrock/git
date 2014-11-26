// COMP53 - Fall 2012 - Project 5
// Deck.h - Definition of Deck class and DeckException class.
// Author: Michael Doherty

#ifndef DECK_DOT_H
#define DECK_DOT_H
#include <vector>
using namespace std;
#include "Card.h"
#include "BasicException.h"

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
