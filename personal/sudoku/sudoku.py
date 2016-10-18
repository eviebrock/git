#!/usr/bin/env python3

import sys

def initializeBoard():
	pass

def drawBoard():
	pass

def main():
	w, h = 9, 9
	Matrix = [[x for x in range(w)] for y in range(h)] 
	print(Matrix[0][0])
	print(Matrix[0][1])
	print(Matrix[0][2])
	print(Matrix[0][0])
	print(Matrix[1][0])
	print(Matrix[2][0])

if __name__ == "__main__":
	sys.exit(main())
