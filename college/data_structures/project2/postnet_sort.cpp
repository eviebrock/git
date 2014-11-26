/*
	Erich Viebrock
	e_viebrock@u.pacific.edu
	September 20th, 2012
	Compiler: g++
	This program converts between zip codes and barcodes,
	and outputs the result in a text file.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

class PostNet
{
public:
	void readData(const char* filename);
	void decodeZip();
	void decodeBar();
	void convertToInt();
	void sortZip();
	void convertToString();
	void writeData(const char* filename);
private:
	vector<string> bNums;
	vector<string> zNums;
	vector<int> allNums;
	vector<string> allStrings;
	vector<string> allCodes;
};

void PostNet::readData(const char* filename)
{
	ifstream input;
	input.open(filename);
	if (!input)
	{
		cout << "Could not open :(" << filename << endl;
		return;
	}
	
	char line[1000];
	//cout << endl;
	while (true)
	{
		// get the next full line from the input file
		input.getline(line, 1000);
		// if the line starts with 'e', we're finished
		if (line[0] == 'e')
		{
			break;
		}
		// if the line starts with 'b', rest of line is a bar code
		else if (line[0] == 'b')
		{
			bNums.push_back(&(line[2]));
		}
		// if the line starts with 'z', rest of line is a zip code
		else if (line[0] == 'z')
		{
			zNums.push_back(&(line[2]));
		}
		// error check – shouldn’t happen on a well-formed
		// input file
		else
		{
			cout << "invalid line: " << line << endl;
		}
	}
	input.close();
}

void PostNet::decodeZip()
{
	string tmpZip;
	string tmpBar;
	for (unsigned int i=0; i<allStrings.size(); i++)
	{
		tmpZip = allStrings[i];
		while (tmpZip.length() < 5)
		{
			tmpZip = "0" + tmpZip;
		}
		tmpBar.append("1");		
		for (int j=0; j<5; j++)
		{
			if ((tmpZip[j] == '0'))
			{
				tmpBar.append("11000");
			}
			else if ((tmpZip[j] == '1'))
			{
				tmpBar.append("00011");
			}
			else if ((tmpZip[j] == '2'))
			{
				tmpBar.append("00101");
			}
			else if ((tmpZip[j] == '3'))
			{
				tmpBar.append("00110");
			}
			else if ((tmpZip[j] == '4'))
			{
				tmpBar.append("01001");
			}
			else if ((tmpZip[j] == '5'))
			{
				tmpBar.append("01010");
			}
			else if ((tmpZip[j] == '6'))
			{
				tmpBar.append("01100");
			}
			else if ((tmpZip[j] == '7'))
			{
				tmpBar.append("10001");
			}
			else if ((tmpZip[j] == '8'))
			{
				tmpBar.append("10010");
			}
			else if ((tmpZip[j] == '9'))
			{
				tmpBar.append("10100");
			}
			else
			{
				cout << "invalid char: " << tmpZip[j] << endl;
			}
		}
		tmpBar.append("1");
		allCodes.push_back(tmpZip + " " + tmpBar);
		tmpBar.clear();
	}
}

void PostNet::decodeBar()
{
	string tmpZip;
	string tmpBar;
	for (unsigned int i=0; i<bNums.size(); i++)
	{
		tmpBar = bNums[i];
		int n = 1;
		for (int j=0; j<5; j++)
		{
			if ((tmpBar[n] == '1' && tmpBar[n+1] == '1' && 
			tmpBar[n+2] == '0' && tmpBar[n+3] == '0' && 
			tmpBar[n+4] == '0' ))
				tmpZip.append("0");
			else if ((tmpBar[n] == '0' && tmpBar[n+1] == '0' && 
			tmpBar[n+2] == '0' && tmpBar[n+3] == '1' && 
			tmpBar[n+4] == '1' ))
				tmpZip.append("1");
			else if ((tmpBar[n] == '0' && tmpBar[n+1] == '0' && 
			tmpBar[n+2] == '1' && tmpBar[n+3] == '0' && 
			tmpBar[n+4] == '1' ))
				tmpZip.append("2");
			else if ((tmpBar[n] == '0' && tmpBar[n+1] == '0' && 
			tmpBar[n+2] == '1' && tmpBar[n+3] == '1' && 
			tmpBar[n+4] == '0' ))
				tmpZip.append("3");
			else if ((tmpBar[n] == '0' && tmpBar[n+1] == '1' && 
			tmpBar[n+2] == '0' && tmpBar[n+3] == '0' && 
			tmpBar[n+4] == '1' ))
				tmpZip.append("4");
			else if ((tmpBar[n] == '0' && tmpBar[n+1] == '1' && 
			tmpBar[n+2] == '0' && tmpBar[n+3] == '1' && 
			tmpBar[n+4] == '0' ))
				tmpZip.append("5");
			else if ((tmpBar[n] == '0' && tmpBar[n+1] == '1' && 
			tmpBar[n+2] == '1' && tmpBar[n+3] == '0' && 
			tmpBar[n+4] == '0' ))
				tmpZip.append("6");
			else if ((tmpBar[n] == '1' && tmpBar[n+1] == '0' && 
			tmpBar[n+2] == '0' && tmpBar[n+3] == '0' && 
			tmpBar[n+4] == '1' ))
				tmpZip.append("7");
			else if ((tmpBar[n] == '1' && tmpBar[n+1] == '0' && 
			tmpBar[n+2] == '0' && tmpBar[n+3] == '1' && 
			tmpBar[n+4] == '0' ))
				tmpZip.append("8");
			else if ((tmpBar[n] == '1' && tmpBar[n+1] == '0' && 
			tmpBar[n+2] == '1' && tmpBar[n+3] == '0' && 
			tmpBar[n+4] == '0' ))
				tmpZip.append("9");
			else
			{
				cout << "invalid char set: ";
				cout << tmpBar[n];
				cout << tmpBar[n+1];
				cout << tmpBar[n+2];
				cout << tmpBar[n+3];
				cout << tmpBar[n+4] << endl;
			}
			n = n + 5;
		}
		zNums.push_back(tmpZip);
		tmpZip.clear();
	}
}

void PostNet::convertToInt()
{
	for (unsigned int i=0; i<zNums.size(); i++)
	{
		string tmpString = zNums[i];
		int tmpInt = atoi(tmpString.c_str());
		allNums.push_back(tmpInt);
	}	
}

void PostNet::sortZip()
{
	sort(allNums.begin(), allNums.end());
}

//convert back to string to handle zip codes with leading zeros
void PostNet::convertToString()
{
	for (unsigned int i=0; i<zNums.size(); i++)
	{
		allStrings.push_back(to_string(allNums[i]));
	}
}

void PostNet::writeData(const char* filename)
{
	ofstream output;
	output.open(filename);
	if (!output)
	{
		cout << "Could not open :(" << filename << endl;
		return;
	}
	
	for (unsigned int i=0; i<allCodes.size(); i++)
	{
		output << allCodes[i];
		output << endl;
	}	
}

int main()
{
	const char* inputFile = "project02input.txt";
	const char* outputFile = "output.txt";
	PostNet postnet;
	postnet.readData(inputFile);
	postnet.decodeBar();
	postnet.convertToInt();
	postnet.sortZip();
	postnet.convertToString();
	postnet.decodeZip();
	postnet.writeData(outputFile);
	return 0;
}
