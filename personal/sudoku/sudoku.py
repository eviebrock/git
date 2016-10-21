#!/usr/bin/env python3

import sys

def initializeBoard():
	board = []
	
	for i in range(1, 10):
		column = []
		for j in range(1, 10):
			column.append(j)
		board.append(column)
		
	return board

def drawBoard(board):
	for i in range(9):
		for j in range(9):
			if j+1 % 3 == 0:
				print("|", end="")
			else:
				print(board[i][j], end="")
		print()

def main():
	gameBoard = initializeBoard()
	drawBoard(gameBoard)

if __name__ == "__main__":
	sys.exit(main())
