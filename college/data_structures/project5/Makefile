# CC = compiler to use
CC=g++

# CFLAGS = options passed to the compiler
CFLAGS=-c -Wall -std=c++0x
-std=c++11

all: main

main: main.o Card.o Deck.o Hand.o Blackjack.o
	$(CC) -o main main.o Card.o Deck.o Hand.o Blackjack.o

main.o: main.cpp Card.h Deck.h Hand.h Blackjack.h
	$(CC) $(CFLAGS) main.cpp

Card.o: Card.cpp Card.h
	$(CC) $(CFLAGS) Card.cpp

Deck.o: Deck.cpp Deck.h
	$(CC) $(CFLAGS) Deck.cpp

Hand.o: Hand.cpp Hand.h
	$(CC) $(CFLAGS) Hand.cpp
	
Blackjack.o: Blackjack.cpp Blackjack.h
	$(CC) $(CFLAGS) Blackjack.cpp

clean:
	-rm -f main *.o *~
