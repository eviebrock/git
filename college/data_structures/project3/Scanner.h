// COMP 53 Fall 2012 - Project 03
// You should not need to alter this file.
// See the assignment statement for detailed
//    interface method descriptions.
// Author: Michael Doherty

// Scanner.h

#ifndef SCANNER_DOT_H
#define SCANNER_DOT_H

#include <string>
#include <queue>
using namespace std;
#include "Token.h"

class Scanner
{
public:
    Scanner();
    ~Scanner();
    void processExpression(const string& s);
    bool nextToken(Token& token);

private:
    queue<Token> tokens;
    char* input;
    short nxt;
    void skipWhitespace();
    void getTokenString(char* tokenstring);
    bool processTokenString(char* tokenstring);
    bool isValidNumber(char* tokenstring);
    void eraseTokenQueue();
};

#endif
