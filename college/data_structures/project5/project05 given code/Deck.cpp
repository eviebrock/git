// COMP53 - Fall 2012 - Project 5
// Deck.cpp - Implementation of Deck class methods.
// Author: Michael Doherty

#include <ctime>    // for time() function
#include <cstdlib>  // for srand() and rand() functions
#include "Deck.h"

// CONSTRUCTOR

Deck::Deck()
{
    for (short c=0; c<52; c++)
        cards_in_deck.push_back(Card(c));
}

// ACCESSORS

short Deck::cardsRemaining()
{
    return cards_in_deck.size();
}

Card Deck::peek(short i)
{
    if ((i < 0) || (i>=cardsRemaining()))
        throw DeckException(string("peeking with invalid index"));
    return cards_in_deck[i];
}

// MODIFIERS

Card Deck::deal()
{
    if (cardsRemaining() == 0)
        throw DeckException(string("dealing from an empty deck"));
    Card card = cards_in_deck.back();
    cards_in_deck.pop_back();
    return card;
}

void Deck::shuffle()
{
    short count = cardsRemaining();
    srand(time(NULL));
    for (short i=0; i<100; i++)
    {
        short j = rand()%count;
        short k = rand()%count;
        if (j != k)
        {
            Card c = cards_in_deck[j];
            cards_in_deck[j] = cards_in_deck[k];
            cards_in_deck[k] = c;
        }
    }

}


