// COMP53 - Fall 2012 - Project 5
// project05.cpp - test program for Card and Deck class.
// Author: Michael Doherty

#include <iostream>
using namespace std;
#include "Deck.h"
#include "BasicException.h"

int main()
{
    Deck deck;
    short i;

    try
    {
        cout << "original deck:" << endl;
        for (i=0; i<deck.cardsRemaining(); i++)
            cout << deck.peek(i) << " ";

        deck.shuffle();

        cout << "shuffled deck:" << endl;
        for (i=0; i<deck.cardsRemaining(); i++)
            cout << deck.peek(i) << " ";
    }
    catch (BasicException& exception)
    {
        cout << exception.getMessage() << endl;
    }

    return 0;
}
