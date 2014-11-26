// COMP53 - Fall 2012 - Project 5
// Card.cpp - Implementation of Card class methods and operators.
// Author: Michael Doherty

#include <iostream>
using namespace std;
#include "Card.h"

// CONSTRUCTORS

Card::Card()
: rank(ACE), suit(SPADES)
{ }

Card::Card(short _number)
: rank(CardRank((_number%13)+1)), suit(CardSuit((_number/13)+1))
{ }

Card::Card(CardRank _rank, CardSuit _suit)
: rank(_rank), suit(_suit)
{ }

Card::Card(const Card& _other)
: rank(_other.rank), suit(_other.suit)
{ }

// ACCESSORS

CardRank Card::getRank() { return rank; }

CardSuit Card::getSuit() { return suit; }

short Card::getValue()
{
    if (rank <= TEN) return short(rank);
    return 10;
}

// OPERATORS

Card& Card::operator=(const Card& rhs)
{
    rank = rhs.rank;
    suit = rhs.suit;
    return (*this);
}

bool Card::operator==(const Card& rhs) { return (rank==rhs.rank) && (suit==rhs.suit); }

bool Card::operator!=(const Card& rhs) { return !((*this) == rhs); }

ostream& operator<<(ostream& out, const Card& card)
{
    switch (card.rank)
    {
        case ACE:   out << "A"; break;
        case TWO:   out << "2"; break;
        case THREE: out << "3"; break;
        case FOUR:  out << "4"; break;
        case FIVE:  out << "5"; break;
        case SIX:   out << "6"; break;
        case SEVEN: out << "7"; break;
        case EIGHT: out << "8"; break;
        case NINE:  out << "9"; break;
        case TEN:   out << "10"; break;
        case JACK:  out << "J"; break;
        case QUEEN: out << "Q"; break;
        case KING:  out << "K"; break;
    }
    switch (card.suit)
    {
        case SPADES:   out << "S"; break;
        case DIAMONDS: out << "D"; break;
        case CLUBS:    out << "C"; break;
        case HEARTS:   out << "H"; break;
    }
    return out;
}
