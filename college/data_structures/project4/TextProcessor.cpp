// COMP 53 Fall 2012 - Project 03
// You should not need to read or alter this file.
// Author: Michael Doherty

// TextProcessor.cpp

// Version 2 - Oct 19 - Corrections for compatability
//             with Visual Studio's string index checks.

#include <cstring>
#include <cstdlib>
#include <fstream>
using namespace std;
#include "TextProcessor.h"

// PUBLIC METHODS

bool TextProcessor::processText(const string& filename, list<string>& words)
{
    ifstream input_stream;
    input_stream.open(filename.c_str());
    if (!input_stream) return false;
    words.clear();
    while (true)
    {
        getline(input_stream, input_line);
        if (!input_stream) return true;
        if ((input_line.length()<1) || (input_line[0] == '#')) continue;
        nxt = 0;
        skipWhitespace();
        while (nxt < input_line.length())
        {
            string word;
            getNextWord(word);
            cleanWord(word);
            convertToLowerCase(word);
            words.push_back(word);
            skipWhitespace();
        }
    }
}

// PRIVATE UTILITY FUNCTIONS
#include <iostream>
using namespace std;
void TextProcessor::skipWhitespace()
{
    while ((nxt < input_line.length()) &&
		   ((input_line[nxt] == ' ') ||
            (input_line[nxt] == '\t') ||
            (input_line[nxt] == '\n')))
        nxt++;
}

void TextProcessor::getNextWord(string& word)
{
    word = "";
    while ((nxt < input_line.length()) &&
		   (input_line[nxt] != ' ') &&
		   (input_line[nxt] != '\t') &&
           (input_line[nxt] != '\n'))
        word += input_line[nxt++];
}

void TextProcessor::cleanWord(string& word)
{
    string cut_chars = " .,()[]\n\r\t\v";
    word.erase( word.find_last_not_of( cut_chars ) + 1 );
    word.erase( 0, word.find_first_not_of( cut_chars ) );
}

void TextProcessor::convertToLowerCase(string& word)
{
    for (unsigned short i=0; i<word.length(); i++)
        if ((word[i]>='A') && (word[i]<='Z'))
            word[i] = word[i]-('A'-'a');
}
