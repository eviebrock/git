// COMP 53 Fall 2012 - Project 04
// You should not need to alter this file.
// Author: Michael Doherty

// TextProcessor.h

// Usage:
// Create a TextProcessor instance.
// Call TextProcessor::processText() and pass it the name of the text file to read,
//   and a list<string> object to receive the parsed words.
//
//   The processText function will return true if it is successful in opening
//   the text file and false if it cannot open the text file.
//
//   The list of strings will be cleared before words are added to it.
//   The words in the list of strings will be in the same order
//   that they appear in the text file.
//   All leading and trailing punctuation is removed from the words.
//   All letters are converted to lower case.
//   Numbers are treated as words.
//   Lines beginning with a # are treated as comments and are not processed.
//
#ifndef TEXTPROCESSOR_DOT_H
#define TEXTPROCESSOR_DOT_H

#include <string>
#include <list>
using namespace std;

class TextProcessor
{
public:
    TextProcessor() { }
    ~TextProcessor() { }
    bool processText(const string& filename, list<string>& words);

private:
    string input_line;
    unsigned short nxt;
    void skipWhitespace();
    void getNextWord(string& word);
    void cleanWord(string& word);
    void convertToLowerCase(string& word);
};

#endif
