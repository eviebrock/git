// Erich Viebrock
// e_viebrock@u.pacific.edu
// Source code file for Blackjack class implementations
/*
	The main controller for the game. It must maintain a deck of cards, 
	a dealer's hand and the player's hands. This object is responsible for 
	moving cards from the deck to the hands, controlling the flow of the 
	game (player and dealer turns), and determing the outcome of the game.
*/

#include <iostream>

#include "Blackjack.h"
#include "Deck.h"
#include "Hand.h"

using namespace std;

Blackjack::Blackjack()
{
	cout << "********************************************************************************" << endl;
	cout << "|                                                                              |" << endl;
	cout << "|                                  Blackjack                                   |" << endl;
	cout << "|                                                                              |" << endl;
	cout << "********************************************************************************" << endl;
}

void Blackjack::addDealer(Deck& deck, Hand& dealer)
{
	dealer.addCard(deck);
	dealer.addCard(deck);
}

void Blackjack::addPlayer(Deck& deck)
{
	cout << "How many players would like to play? (1-6)" << endl;
	cout << "Players: ";
	numPlayers = 0;
	cin >> numPlayers;
	while (numPlayers > 6 || numPlayers < 1)
	{
		cout << "Error: Invalid number of players." << endl;
		cout << "How many players would like to play? (1-6)" << endl;
		cout << "Players: ";
		cin >> numPlayers;
	}
	
	for (int i=0; i<numPlayers; i++)
	{
		Hand hand;
		hand.addCard(deck);
		hand.addCard(deck);
		players.push_back(hand);
	}
}

void Blackjack::printInitialDHand(Hand& dealer)
{	
	cout << "\nDealer: ";
	cout << dealer.cards_in_hand[0];
	cout << " ??" << endl;
}

void Blackjack::printDHand(Hand& dealer)
{	
	cout << "\nDealer: ";
	dealer.printHand();
	cout << endl;
	//dealer.getScore();
}

void Blackjack::printHands()
{	
	int j = 0;
	for (int i=0; i<numPlayers; i++)
	{
		j = i+1;
		cout << "Player " << j << ": ";
		players[i].printHand();
		cout << endl;
	}
}

void Blackjack::playGame(Blackjack& blackjack, Deck& deck, Hand& dealer)
{
	blackjack.addDealer(deck, dealer);
	blackjack.addPlayer(deck);
	int j;
	if (dealer.getScore() == 21)
	{
		blackjack.endGame(blackjack, dealer);
	}
	else
	{
		for (int i=0; i<numPlayers; i++)
		{
			blackjack.printInitialDHand(dealer);
			blackjack.printHands();
			j = i+1;
			cout << "Player " << j << "'s turn: (h)it or (s)tay? ";
			cin >> hitStay;
			while(hitStay != 's' && hitStay != 'h')
			{
				cout << "Invalid input." << endl;
				cout << "Player " << j << "'s turn: (h)it or (s)tay? ";
				cin >> hitStay;
			}
			while(hitStay == 'h')
			{
				players[i].addCard(deck);
				if (players[i].getScore() > 21)
				{
					/*
					for (int k=0; k<hand.handSize(); k++)
					{
						if (cards_in_hand[k].getRank() == ACE)
						{
							hand.aceSubtract();
						}
					}
					*/
					blackjack.printInitialDHand(dealer);
					blackjack.printHands();
					cout << "Player " << j << " busted." << endl;
					break;
				}
				else
				{
					blackjack.printInitialDHand(dealer);
					blackjack.printHands();
					cout << "Player " << j << "'s turn: (h)it or (s)tay? ";
					cin >> hitStay;
				}
			}

		}
		while (dealer.getScore() < 17)
		{
			dealer.addCard(deck);
			blackjack.printDHand(dealer);
			blackjack.printHands();
			cout << "Dealer hits." << endl;
		}
		blackjack.printDHand(dealer);
		blackjack.printHands();
		cout << "Dealer stays." << endl;
		blackjack.endGame(blackjack, dealer);
		blackjack.announceWinner(blackjack, dealer);
	}
}

void Blackjack::endGame(Blackjack& blackjack, Hand& dealer)
{
	cout << "\nDealer: ";
	dealer.printHand();
	cout << " = " << dealer.getScore();
	for (int i=0; i<numPlayers; i++)
	{
		cout << "\nPlayer " << i+1 << ": ";
		players[i].printHand();
		cout << " = " << players[i].getScore();
	}
	cout << endl;
}

void Blackjack::announceWinner(Blackjack& blackjack, Hand& dealer)
{
	bool push = false;
	bool dealerLose = false;
	
	if (dealer.getScore() <= 21)
	{
		for (unsigned int i=0; i<players.size(); i++)
		{
			if ((dealer.getScore() < players[i].getScore()) && players[i].getScore() <= 21)
			{
				dealerLose = true;
				break;
			}
			else if (dealer.getScore() == players[i].getScore())
			{
				push = true;
			}
		}
		cout << endl;
		if (!dealerLose && !push)
		{
			cout << "Dealer wins!" << endl;
			break;
		}
		else if (!dealerLose && push)
		{
			cout << "Push!" << endl;
			break;
		}
	}
	else
	{
		for (unsigned int j=0; (j<players.size()-1); j++)
		{
			if (players[j].getScore() > 21)
			{
				players[j].setScore(0);
			}
			for (unsigned int k=1; (k<players.size()-1); k++)
			{
				if (players[k].getScore() > 21)
				{
					players[k].setScore(0);
				}
				else if (players[j].getScore() > players[k].getScore())
				{
					players[k].setScore(0);
				}
				else if (players[j].getScore() < players[k].getScore())
				{
					players[j].setScore(0);
				}
				else
				{
					// Player scores are equal,
					// do nothing
				}
			}
		}
		cout << endl;
		for (unsigned int l=0; (l<players.size()-1); l++)
		{
			if (players[l].getScore() > 0)
			{
				cout << "Player " << l+1 << " wins!" << endl;
			}
		}
	}
	
}
