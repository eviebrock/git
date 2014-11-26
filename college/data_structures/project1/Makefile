# CC = compiler to use
CC=g++

# CFLAGS = options passed to the compiler
CFLAGS=-c -Wall

all: tic_tac_toe

tic_tac_toe: tic_tac_toe.o
	$(CC) tic_tac_toe.o -o tic_tac_toe

tic_tac_toe.o: tic_tac_toe.cpp
	$(CC) $(CFLAGS) tic_tac_toe.cpp

clean:
	-rm -f tic_tac_toe.o
	-rm -f tic_tac_toe
