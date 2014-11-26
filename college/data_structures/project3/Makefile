# CC = compiler to use
CC=g++

# CFLAGS = options passed to the compiler
CFLAGS=-c -Wall -std=c++0x
-std=c++11

all: postfix_calc

postfix_calc: postfix_calc.o Scanner.o Token.o
	$(CC) -o postfix_calc postfix_calc.o Scanner.o Token.o

postfix_calc.o: postfix_calc.cpp Scanner.h Token.h
	$(CC) $(CFLAGS) postfix_calc.cpp

Scanner.o: Scanner.cpp Scanner.h
	$(CC) $(CFLAGS) Scanner.cpp

Token.o: Token.cpp Token.h
	$(CC) $(CFLAGS) Token.cpp

clean:
	-rm -f postfix_calc *.o *~
