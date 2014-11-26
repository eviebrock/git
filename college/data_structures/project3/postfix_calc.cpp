// COMP 53 Fall 2012 - Project 03
// Author: Erich Viebrock
// Date: October 15th, 2012
// Compiler: g++

// project03.cpp

#include <iostream>
#include "Scanner.h"
#include "Token.h"

using namespace std;

// Print a representation of a token
// on the console (cout)
void printToken(Token& token);

// Get one line from an input stream and store
// it in the parameter line.
void getInputLine(istream& input, string& line);

int main()
{
	Scanner scanner;
	string input;
	Token token;
	while (true)
	{
		float stack[100]; //stack is limited to 100 elements
		int size = 0; //initialize size to 0
		
		// get a line of input from keyboard
		cout << "Expression: ";
		getInputLine(cin, input);

		// a line with no content means quit
		if (input.size() < 1) break;

		// give input line to scanner for processing
		cout << "scanning [" << input << "]" << endl;
		scanner.processExpression(input);

		// extract tokens and print them
		while (scanner.nextToken(token))
		{
			printToken(token);
			//if token is a value, push on stack array
			if(token.isValue())
			{
				stack[size] = token.getValue();
				size++;
			}
			//if token is an operator, apply operator to last two elements on stack array
			else if(token.isOperator())
			{
				//check for too many operators
				if(size < 2)
				{
					cout << "Invalid input." << endl;
					main();
				}
				//functions for different operators
				if(token.getOperator() == '+')
				{
					stack[size-2] = stack[size-2] + stack[size-1];
				}
				else if(token.getOperator() == '-')
				{
					stack[size-2] = stack[size-2] - stack[size-1];
				}
				else if(token.getOperator() == '*')
				{
					stack[size-2] = stack[size-2] * stack[size-1];
				}
				else
				{
					stack[size-2] = stack[size-2] / stack[size-1];
				}
				//decrease size for indexing, doesn't change actual size of array
				size--;
			}
		}
		//if there is more than one element left in array, not enough operators were used
		if(size != 1)
		{
			cout << "Invalid input." << endl;
			main();
		}
		//output final answer
		cout << "Answer: " << stack[size-1] << endl;
	}
	return 0;
}

void printToken(Token& token)
{
	if (token.isOperator())
		cout << "Oper: " << token.getOperator() << endl;
	else
		cout << "Value: " << token.getValue() << endl;
}

void getInputLine(istream& input, string& line)
{
	char s[1000];
	input.getline(s, 1000);
	line = string(s);
}
