#include <stdio.h>

//#include "Game.h"
//#include "Solver.h"

int welcome()
{
	int gameType;

	printf ("\033[H\033[J");
	printf (" --------------------\n");
	printf ("|                    |\n");
	printf ("|       Sudoku       |\n");
	printf ("|                    |\n");
	printf (" --------------------\n");
	
	printf ("\n");
	printf ("What would you like to do?\n");
	printf ("\n");
	printf ("1. Play Sudoku\n");
	printf ("2. Solve Sudoku\n");
	printf ("\n");
	printf ("Choice: ");
	scanf ("%d", &gameType);
	printf ("\n");
	return gameType;
}

void display(int gameBoard[9][9])
{
	int i;
	int j;
	printf("\n\n");
	for (i=0; i<9; i++)
	{
		for (j=0; j<9; j++)
		{
			if (j == 2 || j == 5 || j == 8)
			{
				printf ("%d   ", gameBoard[i][j]);
			}
			else
			{
				printf ("%d : ", gameBoard[i][j]);
			}
		}
		if (i == 2 || i == 5 || i == 8)
		{
			printf ("\n\n");
		}
		else
		{
			printf ("\n---------   ---------   ---------\n");
		}
		
	}
}



int main()
{
	int gameType;
	do {
		gameType = welcome();
	} while (gameType != 1 && gameType != 2);
	
	if (gameType == 1)
	{
		printf ("User selected to play Sudoku.");
	}
	else
	{
		printf ("User selected to solve Sudoku.");
	}
	
	int gameBoard[9][9] = { {1, 2, 3, 1, 2, 3, 1, 2, 3}, 
				{4, 5, 6, 4, 5, 6, 4, 5, 6},
				{7, 8, 9, 7, 8, 9, 7, 8, 9},
				{1, 2, 3, 1, 2, 3, 1, 2, 3}, 
				{4, 5, 6, 4, 5, 6, 4, 5, 6},
				{7, 8, 9, 7, 8, 9, 7, 8, 9},
				{1, 2, 3, 1, 2, 3, 1, 2, 3}, 
				{4, 5, 6, 4, 5, 6, 4, 5, 6},
				{7, 8, 9, 7, 8, 9, 7, 8, 9} };
	display(gameBoard);
	return 0;
}
