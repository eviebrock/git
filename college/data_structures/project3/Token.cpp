// COMP 53 Fall 2012 - Project 03
// You should not need to read or alter this file.
// Author: Michael Doherty

// Token.cpp

#include "Token.h"

// ACCESS METHODS

bool Token::isOperator()
{
    return is_oper;
}

bool Token::isValue()
{
    return !is_oper;
}

float Token::getValue()
{
    return val;
}

char Token::getOperator()
{
    return oper;
}

// CONSTRUCTORS AND ASSIGNMENT OPERATOR

Token::Token()
{
    is_oper = false;
    val = 0.0f;
}

Token::Token(char _operator)
{
    is_oper = true;
    oper = _operator;
}

Token::Token(float _value)
{
    is_oper = false;
    val = _value;
}

Token::Token(const Token& _other)
{
    is_oper = _other.is_oper;
    oper = _other.oper;
    val = _other.val;
}

Token& Token::operator=(const Token &rhs)
{
    is_oper = rhs.is_oper;
    oper = rhs.oper;
    val = rhs.val;
    return *this;
}
