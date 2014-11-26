// COMP53 - Fall 2012 - Project 5
// Card.h - Definition of Card class.
// Author: Michael Doherty

#ifndef CARD_DOT_H
#define CARD_DOT_H
#include <fstream>
using namespace std;

enum CardRank { ACE=1, TWO, THREE, FOUR, FIVE, SIX, SEVEN,
                EIGHT, NINE, TEN, JACK, QUEEN, KING };
enum CardSuit { CLUBS=1, DIAMONDS, SPADES, HEARTS };

class Card
{
public:
    // CONSTRUCTORS
    Card();
    Card(short _number);
    Card(CardRank _rank, CardSuit _suit);
    Card(const Card& _other);

    // ACCESSORS
    CardRank getRank();
    CardSuit getSuit();
    short getValue();

    // OPERATORS
    Card& operator=(const Card& rhs);
    bool operator==(const Card& rhs);
    bool operator!=(const Card& rhs);
    friend ostream& operator<<(ostream& out, const Card& card);

private:
    CardRank rank;
    CardSuit suit;
};

#endif
