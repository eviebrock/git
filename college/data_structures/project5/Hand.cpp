// Erich Viebrock
// e_viebrock@u.pacific.edu
// Source code file for Hand class implementations
/*
	A collection of cards held by the players or dealer. There must be a 
	method to add a	card to a hand. It must be possible to iterate through 
	the cards in the hand for display. There must be a method for 
	determining the score of a hand.
*/

#include <iostream>
#include "Hand.h"

using namespace std;

Hand::Hand()
{
	score = 0;
}

int Hand::handSize()
{
    return cards_in_hand.size();
}

void Hand::addCard(Deck& deck)
{
	cards_in_hand.push_back(deck.deal());
	if (cards_in_hand[handSize()-1].getRank() == ACE)
		score += 11;
	else if (cards_in_hand[handSize()-1].getRank() == TWO)
		score += 2;
	else if (cards_in_hand[handSize()-1].getRank() == THREE)
		score += 3;
	else if (cards_in_hand[handSize()-1].getRank() == FOUR)
		score += 4;
	else if (cards_in_hand[handSize()-1].getRank() == FIVE)
		score += 5;
	else if (cards_in_hand[handSize()-1].getRank() == SIX)
		score += 6;
	else if (cards_in_hand[handSize()-1].getRank() == SEVEN)
		score += 7;
	else if (cards_in_hand[handSize()-1].getRank() == EIGHT)
		score += 8;
	else if (cards_in_hand[handSize()-1].getRank() == NINE)
		score += 9;
	else if (cards_in_hand[handSize()-1].getRank() == TEN)
		score += 10;
	else if (cards_in_hand[handSize()-1].getRank() == JACK)
		score += 10;
	else if (cards_in_hand[handSize()-1].getRank() == QUEEN)
		score += 10;
	else if (cards_in_hand[handSize()-1].getRank() == KING)
		score += 10;
	else
		cout << "couldn't access array to compute score" << endl;
}

void Hand::aceSubtract()
{
	score -= 10;
}

void Hand::printHand()
{
	for (int i=0; (i<handSize()); i++)
	{
		cout << cards_in_hand[i] << " ";
	}
}

void Hand::setScore(int x)
{
	score = x;
}

int Hand::getScore()
{
	return score;
}
