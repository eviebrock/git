// COMP 53 Fall 2012 - Project 03
// Author:
//
// Project04-main.cpp
// Your code should be contained in this file.

#include <iostream>
#include <string>
#include <list>
using namespace std;
#include "TextProcessor.h"

const string filename("project04-input.txt");

int main()
{
    list<string> word_list;
    TextProcessor text_proc;
    if (!text_proc.processText(filename, word_list))
    {
        cerr << "ERROR: cannot open file " << filename << endl;
        return(1);
    }

    // Replace this loop with your code
    list<string>::iterator iter = word_list.begin();
    while (iter != word_list.end())
    {
        cout << *iter << endl;
        iter++;
    }

    return 0;
}