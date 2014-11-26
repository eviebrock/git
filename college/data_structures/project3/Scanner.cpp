// COMP 53 Fall 2012 - Project 03
// You should not need to read or alter this file.
// Author: Michael Doherty

// Scanner.cpp

#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;
#include "Scanner.h"

// PUBLIC METHODS

Scanner::Scanner()
{
    input = NULL;
}

Scanner::~Scanner()
{
    // input should be NULL if we reach the destructor,
    // but check it anyway to be safe.
    if (input != NULL) delete [] input;
}

bool Scanner::nextToken(Token& token)
{
    if (tokens.empty()) return false;
    token = tokens.front();
    tokens.pop();
    return true;
}

void Scanner::processExpression(const string& s)
{
    char tokenstring[1000];
    if (input != NULL) delete [] input;
    input = new char[s.size()+1];
    strcpy(input, s.c_str());
    nxt = 0;
    skipWhitespace();
    while (input[nxt] != '\0')
    {
        getTokenString(tokenstring);
        if (!processTokenString(tokenstring))
        {
            cerr << "ERROR: Invalid token detected ... scanner aborted." << endl;
            eraseTokenQueue();
            break;
        }
        skipWhitespace();
    }
    delete [] input;
    input = NULL;
}

// PRIVATE UTILITY FUNCTIONS

void Scanner::skipWhitespace()
{
    while ((input[nxt] == ' ') ||
           (input[nxt] == '\t') ||
           (input[nxt] == '\n'))
        nxt++;
}

void Scanner::getTokenString(char* tokenstring)
{
    short j=0;
    while ((input[nxt] != ' ') && (input[nxt] != '\t') &&
           (input[nxt] != '\n') && (input[nxt] != '\0'))
        tokenstring[j++] = input[nxt++];
    tokenstring[j] = '\0';
}

bool Scanner::processTokenString(char* tokenstring)
{
    if (strlen(tokenstring) < 1)
        return false;
    if ((strlen(tokenstring) == 1) &&
        ((tokenstring[0] == '+') || (tokenstring[0] == '-') ||
         (tokenstring[0] == '*') || (tokenstring[0] == '/')))
    {
        Token token(tokenstring[0]);
        tokens.push(token);
        return true;
    }
    if (isValidNumber(tokenstring))
    {
        float v = atof(tokenstring);
        Token token(v);
        tokens.push(token);
        return true;
    }
    return false;
}

bool Scanner::isValidNumber(char* tokenstring)
{
    short count_decimals = 0;
    short i = 0;
    if (tokenstring[i] == '-') i++;
    while (tokenstring[i] != '\0')
    {
        if (tokenstring[i] == '.')
        {
            count_decimals++;
            if (count_decimals > 1) return false;
        }
        else if (!isdigit(tokenstring[i])) return false;
        i++;
    }
    return true;
}

void Scanner::eraseTokenQueue()
{
    while (!tokens.empty()) tokens.pop();
}
