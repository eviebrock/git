// COMP53 - Fall 2012 - Project 5
// main.cpp - main controller for program
// Author: Erich Viebrock

#include <iostream>
#include "Hand.h"
#include "Deck.h"
#include "BasicException.h"
#include "Blackjack.h"

using namespace std;

int main()
{
	try
	{
		Deck deck;
		deck.shuffle();
		Blackjack blackjack;
		Hand dealer;
		Hand hand;
		blackjack.playGame(blackjack, deck, dealer);
	}

	catch (BasicException& exception)
	{
		cout << exception.getMessage() << endl;
	}
	
	return 0;
}
