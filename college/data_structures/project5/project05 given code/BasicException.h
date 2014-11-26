// COMP53 - Fall 2012 - Project 5
// Exception.h - Definition of BasicException.
// Author: Michael Doherty

#ifndef BASICEXCEPTION_DOT_H
#define BASICEXCEPTION_DOT_H
#include <string>
using namespace std;

class BasicException
{
public:

    // DEFAULT CONSTRUCTOR
    BasicException()
    : msg(string("UNIDENTIFIED EXCEPTION"))
    { }

    // CONSTRUCTOR WITH MESSAGE
    BasicException(const string& s)
    : msg(s)
    { }

    // ACCESSOR
    string getMessage() { return msg; }

private:
    string msg;
};

#endif
