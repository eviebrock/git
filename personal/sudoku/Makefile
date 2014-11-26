# CC = compiler to use
CC=gcc

# CFLAGS = options passed to the compiler
CFLAGS=-c -Wall #-std=c++0x
#-std=c++11

all: main

sudoku: sudoku.o Game.o Solver.o
	$(CC) -o sudoku sudoku.o Game.o Solver.o
	
sudoku.o: sudoku.c Game.h Solver.h
	$(CC) $(CFLAGS) sudoku.c
	
Game.o: Game.c Game.h
	$(CC) $(CFLAGS) Game.c

Solver.o: Solver.c Solver.h
	$(CC) $(CFLAGS) Solver.c

clean:
	-rm -f sudoku *.o *~
