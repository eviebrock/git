# CC = compiler to use
CC=g++

# CFLAGS = options passed to the compiler
CFLAGS=-c -Wall -std=c++0x
-std=c++11

all: word_frequency

word_frequency: word_frequency.o TextProcessor.o
	$(CC) -o word_frequency word_frequency.o TextProcessor.o

word_frequency.o: word_frequency.cpp TextProcessor.h
	$(CC) $(CFLAGS) word_frequency.cpp

TextProcessor.o: TextProcessor.cpp TextProcessor.h
	$(CC) $(CFLAGS) TextProcessor.cpp

clean:
	-rm -f word_frequency *.o *~
