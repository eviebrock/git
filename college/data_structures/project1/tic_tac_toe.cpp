/*
	Erich Viebrock
	e_viebrock@u.pacific.edu
	September 1, 2012
	Compiler: Visual Studio 2008
	Description: This game emulates Tic-Tac-Toe between a human and computer.
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void printBoard(char gameBoard[][3])
{
	//loop to put array into tic tac toe format
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			cout << gameBoard[row][col];
			if (col != 2)
			{
				cout << "|";
			}
		}
		if (row != 2)
		{
			cout << "\n-+-+-" << endl;
		}
	}
	cout << endl;
}

void humanInput(char gameBoard[][3])
{
	int humanMove;
	cout << "Move: ";
	cin >> humanMove;

	//invalid user input
	while (humanMove <= 0 || humanMove >= 10)
	{
		cout << "Sorry, that move isn't on the board. Try again." << endl;
		cout << endl;
		printBoard(gameBoard);
		cout << "Move: ";
		cin >> humanMove;
	}

	//checks valid move, if valid marks X
	if (humanMove == 1 && gameBoard[0][0] == '1')
	{
		gameBoard[0][0] = 'X';
	}
	else if (humanMove == 2 && gameBoard[0][1] == '2')
	{
		gameBoard[0][1] = 'X';
	}
	else if (humanMove == 3 && gameBoard[0][2] == '3')
	{
		gameBoard[0][2] = 'X';
	}
	else if (humanMove == 4 && gameBoard[1][0] == '4')
	{
		gameBoard[1][0] = 'X';
	}
	else if (humanMove == 5 && gameBoard[1][1] == '5')
	{
		gameBoard[1][1] = 'X';
	}
	else if (humanMove == 6 && gameBoard[1][2] == '6')
	{
		gameBoard[1][2] = 'X';
	}
	else if (humanMove == 7 && gameBoard[2][0] == '7')
	{
		gameBoard[2][0] = 'X';
	}
	else if (humanMove == 8 && gameBoard[2][1] == '8')
	{
		gameBoard[2][1] = 'X';
	}
	else if (humanMove == 9 && gameBoard[2][2] == '9')
	{
		gameBoard[2][2] = 'X';
	}
	//space already taken
	else
	{
		cout << "Sorry, that space is already taken. Try again." << endl;
		cout << endl;
		printBoard(gameBoard);
		humanInput(gameBoard);
	}
}

void computerInput(char gameBoard[][3])
{
	/* 
		ai offense
	*/
	//top row
	if (gameBoard[0][0] == 'O' && gameBoard[0][1] == 'O' && gameBoard[0][2] == '3')
	{
		gameBoard[0][2] = 'O';
	}
	else if (gameBoard[0][1] == 'O' && gameBoard[0][2] == 'O' && gameBoard[0][0] == '1')
	{
		gameBoard[0][0] = 'O';
	}
	else if (gameBoard[0][0] == 'O' && gameBoard[0][2] == 'O' && gameBoard[0][1] == '2')
	{
		gameBoard[0][1] = 'O';
	}
	//middle row
	else if (gameBoard[1][0] == 'O' && gameBoard[1][1] == 'O' && gameBoard[1][2] == '6')
	{
		gameBoard[1][2] = 'O';
	}
	else if (gameBoard[1][1] == 'O' && gameBoard[1][2] == 'O' && gameBoard[1][0] == '4')
	{
		gameBoard[1][0] = 'O';
	}
	else if (gameBoard[1][0] == 'O' && gameBoard[1][2] == 'O' && gameBoard[1][1] == '5')
	{
		gameBoard[1][1] = 'O';
	}
	//bottom row
	else if (gameBoard[2][0] == 'O' && gameBoard[2][1] == 'O' && gameBoard[2][2] == '9')
	{
		gameBoard[2][2] = 'O';
	}
	else if (gameBoard[2][1] == 'O' && gameBoard[2][2] == 'O' && gameBoard[2][0] == '7')
	{
		gameBoard[2][0] = 'O';
	}
	else if (gameBoard[2][0] == 'O' && gameBoard[2][2] == 'O' && gameBoard[2][1] == '8')
	{
		gameBoard[2][1] = 'O';
	}
	//left column
	else if (gameBoard[0][0] == 'O' && gameBoard[1][0] == 'O' && gameBoard[2][0] == '7')
	{
		gameBoard[2][0] = 'O';
	}
	else if (gameBoard[1][0] == 'O' && gameBoard[2][0] == 'O' && gameBoard[0][0] == '1')
	{
		gameBoard[0][0] = 'O';
	}
	else if (gameBoard[0][0] == 'O' && gameBoard[2][0] == 'O' && gameBoard[1][0] == '4')
	{
		gameBoard[1][0] = 'O';
	}
	//middle column
	else if (gameBoard[0][1] == 'O' && gameBoard[1][1] == 'O' && gameBoard[2][1] == '8')
	{
		gameBoard[2][1] = 'O';
	}
	else if (gameBoard[1][1] == 'O' && gameBoard[2][1] == 'O' && gameBoard[0][1] == '2')
	{
		gameBoard[0][1] = 'O';
	}
	else if (gameBoard[0][1] == 'O' && gameBoard[2][1] == 'O' && gameBoard[1][1] == '5')
	{
		gameBoard[1][1] = 'O';
	}
	//right column
	else if (gameBoard[0][2] == 'O' && gameBoard[1][2] == 'O' && gameBoard[2][2] == '9')
	{
		gameBoard[2][2] = 'O';
	}
	else if (gameBoard[1][2] == 'O' && gameBoard[2][2] == 'O' && gameBoard[0][2] == '3')
	{
		gameBoard[0][2] = 'O';
	}
	else if (gameBoard[0][2] == 'O' && gameBoard[2][2] == 'O' && gameBoard[1][2] == '6')
	{
		gameBoard[1][2] = 'O';
	}
	//bottom left top right diagonal
	else if (gameBoard[2][0] == 'O' && gameBoard[1][1] == 'O' && gameBoard[0][2] == '3')
	{
		gameBoard[0][2] = 'O';
	}
	else if (gameBoard[1][1] == 'O' && gameBoard[0][2] == 'O' && gameBoard[2][0] == '7')
	{
		gameBoard[2][0] = 'O';
	}
	else if (gameBoard[2][0] == 'O' && gameBoard[0][2] == 'O' && gameBoard[1][1] == '5')
	{
		gameBoard[1][1] = 'O';
	}
	//top left bottom right diagonal
	else if (gameBoard[0][0] == 'O' && gameBoard[1][1] == 'O' && gameBoard[2][2] == '9')
	{
		gameBoard[2][2] = 'O';
	}
	else if (gameBoard[1][1] == 'O' && gameBoard[2][2] == 'O' && gameBoard[0][0] == '1')
	{
		gameBoard[0][0] = 'O';
	}
	else if (gameBoard[0][0] == 'O' && gameBoard[2][2] == 'O' && gameBoard[1][1] == '5')
	{
		gameBoard[1][1] = 'O';
	}	
	/* 
		ai defense
	*/
	//comp takes middle square if open
	else if (gameBoard[1][1] == '5')
	{
		gameBoard[1][1] = 'O';
	}
	//top row
	else if (gameBoard[0][0] == 'X' && gameBoard[0][1] == 'X' && gameBoard[0][2] == '3')
	{
		gameBoard[0][2] = 'O';
	}
	else if (gameBoard[0][1] == 'X' && gameBoard[0][2] == 'X' && gameBoard[0][0] == '1')
	{
		gameBoard[0][0] = 'O';
	}
	else if (gameBoard[0][0] == 'X' && gameBoard[0][2] == 'X' && gameBoard[0][1] == '2')
	{
		gameBoard[0][1] = 'O';
	}
	//middle row
	else if (gameBoard[1][0] == 'X' && gameBoard[1][1] == 'X' && gameBoard[1][2] == '6')
	{
		gameBoard[1][2] = 'O';
	}
	else if (gameBoard[1][1] == 'X' && gameBoard[1][2] == 'X' && gameBoard[1][0] == '4')
	{
		gameBoard[1][0] = 'O';
	}
	else if (gameBoard[1][0] == 'X' && gameBoard[1][2] == 'X' && gameBoard[1][1] == '5')
	{
		gameBoard[1][1] = 'O';
	}
	//bottom row
	else if (gameBoard[2][0] == 'X' && gameBoard[2][1] == 'X' && gameBoard[2][2] == '9')
	{
		gameBoard[2][2] = 'O';
	}
	else if (gameBoard[2][1] == 'X' && gameBoard[2][2] == 'X' && gameBoard[2][0] == '7')
	{
		gameBoard[2][0] = 'O';
	}
	else if (gameBoard[2][0] == 'X' && gameBoard[2][2] == 'X' && gameBoard[2][1] == '8')
	{
		gameBoard[2][1] = 'O';
	}
	//left column
	else if (gameBoard[0][0] == 'X' && gameBoard[1][0] == 'X' && gameBoard[2][0] == '7')
	{
		gameBoard[2][0] = 'O';
	}
	else if (gameBoard[1][0] == 'X' && gameBoard[2][0] == 'X' && gameBoard[0][0] == '1')
	{
		gameBoard[0][0] = 'O';
	}
	else if (gameBoard[0][0] == 'X' && gameBoard[2][0] == 'X' && gameBoard[1][0] == '4')
	{
		gameBoard[1][0] = 'O';
	}
	//middle column
	else if (gameBoard[0][1] == 'X' && gameBoard[1][1] == 'X' && gameBoard[2][1] == '8')
	{
		gameBoard[2][1] = 'O';
	}
	else if (gameBoard[1][1] == 'X' && gameBoard[2][1] == 'X' && gameBoard[0][1] == '2')
	{
		gameBoard[0][1] = 'O';
	}
	else if (gameBoard[0][1] == 'X' && gameBoard[2][1] == 'X' && gameBoard[1][1] == '5')
	{
		gameBoard[1][1] = 'O';
	}
	//right column
	else if (gameBoard[0][2] == 'X' && gameBoard[1][2] == 'X' && gameBoard[2][2] == '9')
	{
		gameBoard[2][2] = 'O';
	}
	else if (gameBoard[1][2] == 'X' && gameBoard[2][2] == 'X' && gameBoard[0][2] == '3')
	{
		gameBoard[0][2] = 'O';
	}
	else if (gameBoard[0][2] == 'X' && gameBoard[2][2] == 'X' && gameBoard[1][2] == '6')
	{
		gameBoard[1][2] = 'O';
	}
	//bottom left top right diagonal
	else if (gameBoard[2][0] == 'X' && gameBoard[1][1] == 'X' && gameBoard[0][2] == '3')
	{
		gameBoard[0][2] = 'O';
	}
	else if (gameBoard[1][1] == 'X' && gameBoard[0][2] == 'X' && gameBoard[2][0] == '7')
	{
		gameBoard[2][0] = 'O';
	}
	else if (gameBoard[2][0] == 'X' && gameBoard[0][2] == 'X' && gameBoard[1][1] == '5')
	{
		gameBoard[1][1] = 'O';
	}
	//top left bottom right diagonal
	else if (gameBoard[0][0] == 'X' && gameBoard[1][1] == 'X' && gameBoard[2][2] == '9')
	{
		gameBoard[2][2] = 'O';
	}
	else if (gameBoard[1][1] == 'X' && gameBoard[2][2] == 'X' && gameBoard[0][0] == '1')
	{
		gameBoard[0][0] = 'O';
	}
	else if (gameBoard[0][0] == 'X' && gameBoard[2][2] == 'X' && gameBoard[1][1] == '5')
	{
		gameBoard[1][1] = 'O';
	}	
	//random space generator
	else
	{
		int randRow;
		int randCol;
		do {
			srand(time(NULL)); //random num generator from class 9/5
			randRow = rand() % 3;
			randCol = rand() % 3;
		} while (gameBoard[randRow][randCol] == 'X' || gameBoard[randRow][randCol] == 'O');
		gameBoard[randRow][randCol] = 'O';
	}
}

bool checkEndGame(bool& gameOn, char gameBoard[][3])
{
	//human winning cases
	if (gameBoard[0][0] == 'X' && gameBoard[0][1] == 'X' && gameBoard [0][2] == 'X') //top row
	{
		gameOn = false;
		cout << endl;
		printBoard(gameBoard);
		cout << "You win!" << endl;
	}
	else if (gameBoard[1][0] == 'X' && gameBoard[1][1] == 'X' && gameBoard [1][2] == 'X') //middle row
	{
		gameOn = false;
		cout << endl;
		printBoard(gameBoard);
		cout << "You win!" << endl;
	}
	else if (gameBoard[2][0] == 'X' && gameBoard[2][1] == 'X' && gameBoard [2][2] == 'X') //bottom row
	{
		gameOn = false;
		cout << endl;
		printBoard(gameBoard);
		cout << "You win!" << endl;
	}
	else if (gameBoard[0][0] == 'X' && gameBoard[1][0] == 'X' && gameBoard [2][0] == 'X') //left column
	{
		gameOn = false;
		cout << endl;
		printBoard(gameBoard);
		cout << "You win!" << endl;
	}
	else if (gameBoard[0][1] == 'X' && gameBoard[1][1] == 'X' && gameBoard [2][1] == 'X') //middle column
	{
		gameOn = false;
		cout << endl;
		printBoard(gameBoard);
		cout << "You win!" << endl;
	}
	else if (gameBoard[0][2] == 'X' && gameBoard[1][2] == 'X' && gameBoard [2][2] == 'X') //right column
	{
		gameOn = false;
		cout << endl;
		printBoard(gameBoard);
		cout << "You win!" << endl;
	}
	else if (gameBoard[0][0] == 'X' && gameBoard[1][1] == 'X' && gameBoard [2][2] == 'X') //left diagonal
	{
		gameOn = false;
		cout << endl;
		printBoard(gameBoard);
		cout << "You win!" << endl;
	}
	else if (gameBoard[0][2] == 'X' && gameBoard[1][1] == 'X' && gameBoard [2][0] == 'X') //right diagonal
	{
		gameOn = false;
		cout << endl;
		printBoard(gameBoard);
		cout << "You win!" << endl;
	}
	//computer winning cases
	else if (gameBoard[0][0] == 'O' && gameBoard[0][1] == 'O' && gameBoard [0][2] == 'O') //top row
	{
		gameOn = false;
		cout << endl;
		printBoard(gameBoard);
		cout << "You lose!" << endl;
	}
	else if (gameBoard[1][0] == 'O' && gameBoard[1][1] == 'O' && gameBoard [1][2] == 'O') //middle row
	{
		gameOn = false;
		cout << endl;
		printBoard(gameBoard);
		cout << "You lose!" << endl;
	}
	else if (gameBoard[2][0] == 'O' && gameBoard[2][1] == 'O' && gameBoard [2][2] == 'O') //bottom row
	{
		gameOn = false;
		cout << endl;
		printBoard(gameBoard);
		cout << "You lose!" << endl;
	}
	else if (gameBoard[0][0] == 'O' && gameBoard[1][0] == 'O' && gameBoard [2][0] == 'O') //left column
	{
		gameOn = false;
		cout << endl;
		printBoard(gameBoard);
		cout << "You lose!" << endl;
	}
	else if (gameBoard[0][1] == 'O' && gameBoard[1][1] == 'O' && gameBoard [2][1] == 'O') //middle column
	{
		gameOn = false;
		cout << endl;
		printBoard(gameBoard);
		cout << "You lose!" << endl;
	}
	else if (gameBoard[0][2] == 'O' && gameBoard[1][2] == 'O' && gameBoard [2][2] == 'O') //right column
	{
		gameOn = false;
		cout << endl;
		printBoard(gameBoard);
		cout << "You lose!" << endl;
	}
	else if (gameBoard[0][0] == 'O' && gameBoard[1][1] == 'O' && gameBoard [2][2] == 'O') //left diagonal
	{
		gameOn = false;
		cout << endl;
		printBoard(gameBoard);
		cout << "You lose!" << endl;
	}
	else if (gameBoard[0][2] == 'O' && gameBoard[1][1] == 'O' && gameBoard [2][0] == 'O') //right diagonal
	{
		gameOn = false;
		cout << endl;
		printBoard(gameBoard);
		cout << "You lose!" << endl;
	}
	//stalemate
	else if (gameBoard[0][0] != '1' && gameBoard[0][1] != '2' && gameBoard[0][2] != '3' &&
			 gameBoard[1][0] != '4' && gameBoard[1][1] != '5' && gameBoard[1][2] != '6' &&
			 gameBoard[2][0] != '7' && gameBoard[2][1] != '8' && gameBoard[2][2] != '9')
	{
		gameOn = false;
		cout << endl;
		printBoard(gameBoard);
		cout << "Stalemate!" << endl;
	}
	else
	{
		gameOn = true;
	}
	return gameOn;
}

int main()
{
	//board initialization
	char gameBoard[3][3] = { {'1', '2', '3'},
							 {'4', '5', '6'},
							 {'7', '8', '9'} };
	bool gameOn = true;
	//main game loop
	printBoard(gameBoard);
	do {
		humanInput(gameBoard);
		checkEndGame(gameOn, gameBoard);
		if (gameOn == false)
		{
			break;
		}
		computerInput(gameBoard);
		checkEndGame(gameOn, gameBoard);
		if (gameOn == false)
		{
			break;
		}
		cout << endl;
		printBoard(gameBoard);
	} while (gameOn);
	cout << endl;
	char choice;
	cout << "Play again? (Y/N)" << endl;
	cout << "Choice: ";
	cin >> choice;
	while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n')
	{
		cout << "Sorry, that input is invalid." << endl;
		cout << endl;
		cout << "Play again? (Y/N)" << endl;
		cout << "Choice: ";
		cin >> choice;
	}
	if (choice == 'Y' || choice == 'y')
	{
		cout << endl;
		main();
	}
	return 0;
}
