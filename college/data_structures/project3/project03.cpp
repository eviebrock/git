// COMP 53 Fall 2012 - Project 03
// Author:

// project03.cpp

#include <iostream>
using namespace std;
#include "Scanner.h"

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
            printToken(token);
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
