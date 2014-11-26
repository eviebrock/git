// COMP 53 Fall 2012 - Project 03
// You should not need to alter this file.
// See the assignment statement for detailed
//    interface method descriptions.
// Author: Michael Doherty


// Token.h

#ifndef TOKEN_DOT_H
#define TOKEN_DOT_H

class Token {
public:
    // access methods
    bool isOperator();
    bool isValue();
    float getValue();
    char getOperator();

    // constructors and assignment operator
    Token();
    Token(char _operator);
    Token(float _value);
    Token(const Token& _other);
    Token& operator=(const Token &rhs);

private:
    char oper;
    float val;
    bool is_oper;
};

#endif
