# CC = compiler to use
CC=g++

# CFLAGS = options passed to the compiler
CFLAGS=-c -Wall -std=c++0x
-std=c++11

all: postnet_sort

postnet_sort: postnet_sort.o
	$(CC) postnet_sort.o -o postnet_sort

postnet_sort.o: postnet_sort.cpp
	$(CC) $(CFLAGS) postnet_sort.cpp

clean:
	-rm -f postnet_sort.o
	-rm -f postnet_sort
	-rm -f Makefile~
	-rm -f postnet_sort.cpp~
	-rm -f zip_to_barcode~
	-rm -f output.txt~
