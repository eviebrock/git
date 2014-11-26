/*
	Erich Viebrock
	e_viebrock@u.pacific.edu
	September 20th, 2012
	Compiler: Visual Studio 2008
	This program converts between zip codes and barcodes, and outputs the result in a text file.
*/

#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;


class PostNet
{
private:
	//variables
public:
	//functions
	
	//short readData("project02input.txt", data, 1000);
	short readWrite(char* filename, char codes[], short capacity);
	void setZip();
	void setBar();
	void getZip();
	void getBar();
};

//short PostNet::readData(char* filename, char codes[], short capacity) //parameters??? PostNet codes[]
short PostNet::readWrite(char* filename, char codes[], short capacity) //parameters??? PostNet codes[]
{
	ofstream output;
	output.open("output.txt");

    short size = 0; //???
	ifstream input; //declare input object
	input.open(filename); //open project02input.txt
	//prompt if can't open file
	if (!input)
	{
		cout << "Could not open " << filename << endl;
		return 0;
	}

	char line[1000]; //max size for line
	char b[28]; //barcode size
	char z[6]; //zipcode size
	while (true)
	{
		//get the next full line from the input file
		input.getline(line, 1000);
		//if the line starts with 'e', we're finished
		if (line[0] == 'e')
		{
			break;
		}
		//if the line starts with 'b', rest of the line is a bar code
		else if (line[0] == 'b')
		{
			//copy bar code into local array b
			strcpy(b, &(line[2]));
			//build an object and copy it into your array at index position size and increment the size [for loop?]
			//YOUR CODE HERE
			size++;			
			char tempZipArray[1000];
			//first five digits of barcode
			if (b[1] == '1' && b[2] == '1' && b[3] == '0' && b[4] == '0' && b[5] == '0')
			{
				tempZipArray[0] = '0';
			}
			else if (b[1] == '0' && b[2] == '0' && b[3] == '0' && b[4] == '1' && b[5] == '1')
			{
				tempZipArray[0] = '1';
			}
			else if (b[1] == '0' && b[2] == '0' && b[3] == '1' && b[4] == '0' && b[5] == '1')
			{
				tempZipArray[0] = '2';
			}
			else if (b[1] == '0' && b[2] == '0' && b[3] == '1' && b[4] == '1' && b[5] == '0')
			{
				tempZipArray[0] = '3';
			}
			else if (b[1] == '0' && b[2] == '1' && b[3] == '0' && b[4] == '0' && b[5] == '1')
			{
				tempZipArray[0] = '4';
			}
			else if (b[1] == '0' && b[2] == '1' && b[3] == '0' && b[4] == '1' && b[5] == '0')
			{
				tempZipArray[0] = '5';
			}
			else if (b[1] == '0' && b[2] == '1' && b[3] == '1' && b[4] == '0' && b[5] == '0')
			{
				tempZipArray[0] = '6';
			}
			else if (b[1] == '1' && b[2] == '0' && b[3] == '0' && b[4] == '0' && b[5] == '1')
			{
				tempZipArray[0] = '7';
			}
			else if (b[1] == '1' && b[2] == '0' && b[3] == '0' && b[4] == '1' && b[5] == '0')
			{
				tempZipArray[0] = '8';
			}
			else if (b[1] == '1' && b[2] == '0' && b[3] == '1' && b[4] == '0' && b[5] == '0')
			{
				tempZipArray[0] = '9';
			}
			//second five digits of barcode
			if (b[6] == '1' && b[7] == '1' && b[8] == '0' && b[9] == '0' && b[10] == '0')
			{
				tempZipArray[1] = '0';
			}
			else if (b[6] == '0' && b[7] == '0' && b[8] == '0' && b[9] == '1' && b[10] == '1')
			{
				tempZipArray[1] = '1';
			}
			else if (b[6] == '0' && b[7] == '0' && b[8] == '1' && b[9] == '0' && b[10] == '1')
			{
				tempZipArray[1] = '2';
			}
			else if (b[6] == '0' && b[7] == '0' && b[8] == '1' && b[9] == '1' && b[10] == '0')
			{
				tempZipArray[1] = '3';
			}
			else if (b[6] == '0' && b[7] == '1' && b[8] == '0' && b[9] == '0' && b[10] == '1')
			{
				tempZipArray[1] = '4';
			}
			else if (b[6] == '0' && b[7] == '1' && b[8] == '0' && b[9] == '1' && b[10] == '0')
			{
				tempZipArray[1] = '5';
			}
			else if (b[6] == '0' && b[7] == '1' && b[8] == '1' && b[9] == '0' && b[10] == '0')
			{
				tempZipArray[1] = '6';
			}
			else if (b[6] == '1' && b[7] == '0' && b[8] == '0' && b[9] == '0' && b[10] == '1')
			{
				tempZipArray[1] = '7';
			}
			else if (b[6] == '1' && b[7] == '0' && b[8] == '0' && b[9] == '1' && b[10] == '0')
			{
				tempZipArray[1] = '8';
			}
			else if (b[6] == '1' && b[7] == '0' && b[8] == '1' && b[9] == '0' && b[10] == '0')
			{
				tempZipArray[1] = '9';
			}
			//third five digits of barcode
			if (b[11] == '1' && b[12] == '1' && b[13] == '0' && b[14] == '0' && b[15] == '0')
			{
				tempZipArray[2] = '0';
			}
			else if (b[11] == '0' && b[12] == '0' && b[13] == '0' && b[14] == '1' && b[15] == '1')
			{
				tempZipArray[2] = '1';
			}
			else if (b[11] == '0' && b[12] == '0' && b[13] == '1' && b[14] == '0' && b[15] == '1')
			{
				tempZipArray[2] = '2';
			}
			else if (b[11] == '0' && b[12] == '0' && b[13] == '1' && b[14] == '1' && b[15] == '0')
			{
				tempZipArray[2] = '3';
			}
			else if (b[11] == '0' && b[12] == '1' && b[13] == '0' && b[14] == '0' && b[15] == '1')
			{
				tempZipArray[2] = '4';
			}
			else if (b[11] == '0' && b[12] == '1' && b[13] == '0' && b[14] == '1' && b[15] == '0')
			{
				tempZipArray[2] = '5';
			}
			else if (b[11] == '0' && b[12] == '1' && b[13] == '1' && b[14] == '0' && b[15] == '0')
			{
				tempZipArray[2] = '6';
			}
			else if (b[11] == '1' && b[12] == '0' && b[13] == '0' && b[14] == '0' && b[15] == '1')
			{
				tempZipArray[2] = '7';
			}
			else if (b[11] == '1' && b[12] == '0' && b[13] == '0' && b[14] == '1' && b[15] == '0')
			{
				tempZipArray[2] = '8';
			}
			else if (b[11] == '1' && b[12] == '0' && b[13] == '1' && b[14] == '0' && b[15] == '0')
			{
				tempZipArray[2] = '9';
			}
			//fourth five digits of barcode
			if (b[16] == '1' && b[17] == '1' && b[18] == '0' && b[19] == '0' && b[20] == '0')
			{
				tempZipArray[3] = '0';
			}
			else if (b[16] == '0' && b[17] == '0' && b[18] == '0' && b[19] == '1' && b[20] == '1')
			{
				tempZipArray[3] = '1';
			}
			else if (b[16] == '0' && b[17] == '0' && b[18] == '1' && b[19] == '0' && b[20] == '1')
			{
				tempZipArray[3] = '2';
			}
			else if (b[16] == '0' && b[17] == '0' && b[18] == '1' && b[19] == '1' && b[20] == '0')
			{
				tempZipArray[3] = '3';
			}
			else if (b[16] == '0' && b[17] == '1' && b[18] == '0' && b[19] == '0' && b[20] == '1')
			{
				tempZipArray[3] = '4';
			}
			else if (b[16] == '0' && b[17] == '1' && b[18] == '0' && b[19] == '1' && b[20] == '0')
			{
				tempZipArray[3] = '5';
			}
			else if (b[16] == '0' && b[17] == '1' && b[18] == '1' && b[19] == '0' && b[20] == '0')
			{
				tempZipArray[3] = '6';
			}
			else if (b[16] == '1' && b[17] == '0' && b[18] == '0' && b[19] == '0' && b[20] == '1')
			{
				tempZipArray[3] = '7';
			}
			else if (b[16] == '1' && b[17] == '0' && b[18] == '0' && b[19] == '1' && b[20] == '0')
			{
				tempZipArray[3] = '8';
			}
			else if (b[16] == '1' && b[17] == '0' && b[18] == '1' && b[19] == '0' && b[20] == '0')
			{
				tempZipArray[3] = '9';
			}
			//fifth five digits of barcode
			if (b[21] == '1' && b[22] == '1' && b[23] == '0' && b[24] == '0' && b[25] == '0')
			{
				tempZipArray[4] = '0';
			}
			else if (b[21] == '0' && b[22] == '0' && b[23] == '0' && b[24] == '1' && b[25] == '1')
			{
				tempZipArray[4] = '1';
			}
			else if (b[21] == '0' && b[22] == '0' && b[23] == '1' && b[24] == '0' && b[25] == '1')
			{
				tempZipArray[4] = '2';
			}
			else if (b[21] == '0' && b[22] == '0' && b[23] == '1' && b[24] == '1' && b[25] == '0')
			{
				tempZipArray[4] = '3';
			}
			else if (b[21] == '0' && b[22] == '1' && b[23] == '0' && b[24] == '0' && b[25] == '1')
			{
				tempZipArray[4] = '4';
			}
			else if (b[21] == '0' && b[22] == '1' && b[23] == '0' && b[24] == '1' && b[25] == '0')
			{
				tempZipArray[4] = '5';
			}
			else if (b[21] == '0' && b[22] == '1' && b[23] == '1' && b[24] == '0' && b[25] == '0')
			{
				tempZipArray[4] = '6';
			}
			else if (b[21] == '1' && b[22] == '0' && b[23] == '0' && b[24] == '0' && b[25] == '1')
			{
				tempZipArray[4] = '7';
			}
			else if (b[21] == '1' && b[22] == '0' && b[23] == '0' && b[24] == '1' && b[25] == '0')
			{
				tempZipArray[4] = '8';
			}
			else if (b[21] == '1' && b[21] == '0' && b[22] == '1' && b[23] == '0' && b[24] == '0')
			{
				tempZipArray[4] = '9';
			}
			//output temporary zip code array to text file
			for (int i = 0; i < 5; i++)
			{
				output << tempZipArray[i];
			}
			output << " ";
			output << "1";
			//output bar code array to text file
			for (int j = 0; j < 25; j++)
			{
				output << b[j];
			}
			output << "1";
			output << endl;
		}
		//if the line starts with 'z', rest of the line is a zip code
		else if (line[0] == 'z')
		{
			//copy zip code into local array z
			strcpy(z, &(line[2]));
			//build an object and copy it into your array at index position size and increment the size [for loop?]
			//YOUR CODE HERE
			size++;
			char tempBarArray[1000];
			//first zipcode element decoder
			if (z[0] == '0')
			{
				tempBarArray[0] = '1';
				tempBarArray[1] = '1';
				tempBarArray[2] = '0';
				tempBarArray[3] = '0';
				tempBarArray[4] = '0';
			}
			else if (z[0] == '1')
			{
				tempBarArray[0] = '0';
				tempBarArray[1] = '0';
				tempBarArray[2] = '0';
				tempBarArray[3] = '1';
				tempBarArray[4] = '1';
			}
			else if (z[0] == '2')
			{
				tempBarArray[0] = '0';
				tempBarArray[1] = '0';
				tempBarArray[2] = '1';
				tempBarArray[3] = '0';
				tempBarArray[4] = '1';
			}
			else if (z[0] == '3')
			{
				tempBarArray[0] = '0';
				tempBarArray[1] = '0';
				tempBarArray[2] = '1';
				tempBarArray[3] = '1';
				tempBarArray[4] = '0';
			}
			else if (z[0] == '4')
			{
				tempBarArray[0] = '0';
				tempBarArray[1] = '1';
				tempBarArray[2] = '0';
				tempBarArray[3] = '0';
				tempBarArray[4] = '1';
			}
			else if (z[0] == '5')
			{
				tempBarArray[0] = '0';
				tempBarArray[1] = '1';
				tempBarArray[2] = '0';
				tempBarArray[3] = '1';
				tempBarArray[4] = '0';
			}
			else if (z[0] == '6')
			{
				tempBarArray[0] = '0';
				tempBarArray[1] = '1';
				tempBarArray[2] = '1';
				tempBarArray[3] = '0';
				tempBarArray[4] = '0';
			}
			else if (z[0] == '7')
			{
				tempBarArray[0] = '1';
				tempBarArray[1] = '0';
				tempBarArray[2] = '0';
				tempBarArray[3] = '0';
				tempBarArray[4] = '1';
			}
			else if (z[0] == '8')
			{
				tempBarArray[0] = '1';
				tempBarArray[1] = '0';
				tempBarArray[2] = '0';
				tempBarArray[3] = '1';
				tempBarArray[4] = '0';
			}
			else if (z[0] == '9')
			{
				tempBarArray[0] = '1';
				tempBarArray[1] = '0';
				tempBarArray[2] = '1';
				tempBarArray[3] = '0';
				tempBarArray[4] = '0';
			}
			else
			{
				cout << "Incorrect zipcode format at line " << line << endl;
			}
			//second zipcode element decoder
			if (z[1] == '0')
			{
				tempBarArray[5] = '1';
				tempBarArray[6] = '1';
				tempBarArray[7] = '0';
				tempBarArray[8] = '0';
				tempBarArray[9] = '0';
			}
			else if (z[1] == '1')
			{
				tempBarArray[5] = '0';
				tempBarArray[6] = '0';
				tempBarArray[7] = '0';
				tempBarArray[8] = '1';
				tempBarArray[9] = '1';
			}
			else if (z[1] == '2')
			{
				tempBarArray[5] = '0';
				tempBarArray[6] = '0';
				tempBarArray[7] = '1';
				tempBarArray[8] = '0';
				tempBarArray[9] = '1';
			}
			else if (z[1] == '3')
			{
				tempBarArray[5] = '0';
				tempBarArray[6] = '0';
				tempBarArray[7] = '1';
				tempBarArray[8] = '1';
				tempBarArray[9] = '0';
			}
			else if (z[1] == '4')
			{
				tempBarArray[5] = '0';
				tempBarArray[6] = '1';
				tempBarArray[7] = '0';
				tempBarArray[8] = '0';
				tempBarArray[9] = '1';
			}
			else if (z[1] == '5')
			{
				tempBarArray[5] = '0';
				tempBarArray[6] = '1';
				tempBarArray[7] = '0';
				tempBarArray[8] = '1';
				tempBarArray[9] = '0';
			}
			else if (z[1] == '6')
			{
				tempBarArray[5] = '0';
				tempBarArray[6] = '1';
				tempBarArray[7] = '1';
				tempBarArray[8] = '0';
				tempBarArray[9] = '0';
			}
			else if (z[1] == '7')
			{
				tempBarArray[5] = '1';
				tempBarArray[6] = '0';
				tempBarArray[7] = '0';
				tempBarArray[8] = '0';
				tempBarArray[9] = '1';
			}
			else if (z[1] == '8')
			{
				tempBarArray[5] = '1';
				tempBarArray[6] = '0';
				tempBarArray[7] = '0';
				tempBarArray[8] = '1';
				tempBarArray[9] = '0';
			}
			else if (z[1] == '9')
			{
				tempBarArray[5] = '1';
				tempBarArray[6] = '0';
				tempBarArray[7] = '1';
				tempBarArray[8] = '0';
				tempBarArray[9] = '0';
			}
			else
			{
				cout << "Incorrect zipcode format at line " << line << endl;
			}
			//third zipcode element decoder
			if (z[2] == '0')
			{
				tempBarArray[10] = '1';
				tempBarArray[11] = '1';
				tempBarArray[12] = '0';
				tempBarArray[13] = '0';
				tempBarArray[14] = '0';
			}
			else if (z[2] == '1')
			{
				tempBarArray[10] = '0';
				tempBarArray[11] = '0';
				tempBarArray[12] = '0';
				tempBarArray[13] = '1';
				tempBarArray[14] = '1';
			}
			else if (z[2] == '2')
			{
				tempBarArray[10] = '0';
				tempBarArray[11] = '0';
				tempBarArray[12] = '1';
				tempBarArray[13] = '0';
				tempBarArray[14] = '1';
			}
			else if (z[2] == '3')
			{
				tempBarArray[10] = '0';
				tempBarArray[11] = '0';
				tempBarArray[12] = '1';
				tempBarArray[13] = '1';
				tempBarArray[14] = '0';
			}
			else if (z[2] == '4')
			{
				tempBarArray[10] = '0';
				tempBarArray[11] = '1';
				tempBarArray[12] = '0';
				tempBarArray[13] = '0';
				tempBarArray[14] = '1';
			}
			else if (z[2] == '5')
			{
				tempBarArray[10] = '0';
				tempBarArray[11] = '1';
				tempBarArray[12] = '0';
				tempBarArray[13] = '1';
				tempBarArray[14] = '0';
			}
			else if (z[2] == '6')
			{
				tempBarArray[10] = '0';
				tempBarArray[11] = '1';
				tempBarArray[12] = '1';
				tempBarArray[13] = '0';
				tempBarArray[14] = '0';
			}
			else if (z[2] == '7')
			{
				tempBarArray[10] = '1';
				tempBarArray[11] = '0';
				tempBarArray[12] = '0';
				tempBarArray[13] = '0';
				tempBarArray[14] = '1';
			}
			else if (z[2] == '8')
			{
				tempBarArray[10] = '1';
				tempBarArray[11] = '0';
				tempBarArray[12] = '0';
				tempBarArray[13] = '1';
				tempBarArray[14] = '0';
			}
			else if (z[2] == '9')
			{
				tempBarArray[10] = '1';
				tempBarArray[11] = '0';
				tempBarArray[12] = '1';
				tempBarArray[13] = '0';
				tempBarArray[14] = '0';
			}
			else
			{
				cout << "Incorrect zipcode format at line " << line << endl;
			}
			//fourth zipcode element decoder
			if (z[3] == '0')
			{
				tempBarArray[15] = '1';
				tempBarArray[16] = '1';
				tempBarArray[17] = '0';
				tempBarArray[18] = '0';
				tempBarArray[19] = '0';
			}
			else if (z[3] == '1')
			{
				tempBarArray[15] = '0';
				tempBarArray[16] = '0';
				tempBarArray[17] = '0';
				tempBarArray[18] = '1';
				tempBarArray[19] = '1';
			}
			else if (z[3] == '2')
			{
				tempBarArray[15] = '0';
				tempBarArray[16] = '0';
				tempBarArray[17] = '1';
				tempBarArray[18] = '0';
				tempBarArray[19] = '1';
			}
			else if (z[3] == '3')
			{
				tempBarArray[15] = '0';
				tempBarArray[16] = '0';
				tempBarArray[17] = '1';
				tempBarArray[18] = '1';
				tempBarArray[19] = '0';
			}
			else if (z[3] == '4')
			{
				tempBarArray[15] = '0';
				tempBarArray[16] = '1';
				tempBarArray[17] = '0';
				tempBarArray[18] = '0';
				tempBarArray[19] = '1';
			}
			else if (z[3] == '5')
			{
				tempBarArray[15] = '0';
				tempBarArray[16] = '1';
				tempBarArray[17] = '0';
				tempBarArray[18] = '1';
				tempBarArray[19] = '0';
			}
			else if (z[3] == '6')
			{
				tempBarArray[15] = '0';
				tempBarArray[16] = '1';
				tempBarArray[17] = '1';
				tempBarArray[18] = '0';
				tempBarArray[19] = '0';
			}
			else if (z[3] == '7')
			{
				tempBarArray[15] = '1';
				tempBarArray[16] = '0';
				tempBarArray[17] = '0';
				tempBarArray[18] = '0';
				tempBarArray[19] = '1';
			}
			else if (z[3] == '8')
			{
				tempBarArray[15] = '1';
				tempBarArray[16] = '0';
				tempBarArray[17] = '0';
				tempBarArray[18] = '1';
				tempBarArray[19] = '0';
			}
			else if (z[3] == '9')
			{
				tempBarArray[15] = '1';
				tempBarArray[16] = '0';
				tempBarArray[17] = '1';
				tempBarArray[18] = '0';
				tempBarArray[19] = '0';
			}
			else
			{
				cout << "Incorrect zipcode format at line " << line << endl;
			}
			//fifth zipcode element decoder
			if (z[4] == '0')
			{
				tempBarArray[20] = '1';
				tempBarArray[21] = '1';
				tempBarArray[22] = '0';
				tempBarArray[23] = '0';
				tempBarArray[24] = '0';
			}
			else if (z[4] == '1')
			{
				tempBarArray[20] = '0';
				tempBarArray[21] = '0';
				tempBarArray[22] = '0';
				tempBarArray[23] = '1';
				tempBarArray[24] = '1';
			}
			else if (z[4] == '2')
			{
				tempBarArray[20] = '0';
				tempBarArray[21] = '0';
				tempBarArray[22] = '1';
				tempBarArray[23] = '0';
				tempBarArray[24] = '1';
			}
			else if (z[4] == '3')
			{
				tempBarArray[20] = '0';
				tempBarArray[21] = '0';
				tempBarArray[22] = '1';
				tempBarArray[23] = '1';
				tempBarArray[24] = '0';
			}
			else if (z[4] == '4')
			{
				tempBarArray[20] = '0';
				tempBarArray[21] = '1';
				tempBarArray[22] = '0';
				tempBarArray[23] = '0';
				tempBarArray[24] = '1';
			}
			else if (z[4] == '5')
			{
				tempBarArray[20] = '0';
				tempBarArray[21] = '1';
				tempBarArray[22] = '0';
				tempBarArray[23] = '1';
				tempBarArray[24] = '0';
			}
			else if (z[4] == '6')
			{
				tempBarArray[20] = '0';
				tempBarArray[21] = '1';
				tempBarArray[22] = '1';
				tempBarArray[23] = '0';
				tempBarArray[24] = '0';
			}
			else if (z[4] == '7')
			{
				tempBarArray[20] = '1';
				tempBarArray[21] = '0';
				tempBarArray[22] = '0';
				tempBarArray[23] = '0';
				tempBarArray[24] = '1';
			}
			else if (z[4] == '8')
			{
				tempBarArray[20] = '1';
				tempBarArray[21] = '0';
				tempBarArray[22] = '0';
				tempBarArray[23] = '1';
				tempBarArray[24] = '0';
			}
			else if (z[4] == '9')
			{
				tempBarArray[20] = '1';
				tempBarArray[21] = '0';
				tempBarArray[22] = '1';
				tempBarArray[23] = '0';
				tempBarArray[24] = '0';
			}
			else
			{
				cout << "Incorrect zipcode format at line " << line << endl;
			}
			//output zip code array to text file
			for (int i = 0; i < 5; i++)
			{
				output << z[i];
			}
			output << " ";
			output << "1";
			//output temporary bar code array to text file
			for (int j = 0; j < 25; j++)
			{
				output << tempBarArray[j];
			}
			output << "1";
			output << endl;
		}
		else
		{
			//error check - shouldn't happen on a well-formed input file
			cout << "Invalid line: " << line << endl;
		}
		//check the capacity to prevent overflows:
		if (size == capacity)
		{
			cout << "Array is full. " << endl;
			break;
		}
	}
	input.close();
	output.close();
	return size;
}

/*
// selection sort based on zip code order
void sort(PostNet codes[], short capacity)
{
	for (unsigned short i=0; i<c.size(); i++)
	{
		// look for the smallest zip code in remaining elements
		long min = c[i].getNumericZip();
		unsigned short min_i = i;
		for (unsigned short j = i+1; j<c.size(); j++)
		{
			if (c[j].getNumericZip() < min)
			{
				min = c[j].getNumericZip();
				min_i = j;
			}
		}
		// move the object with the smallest zip code to the front of the remaining elements
		if (min_i != i)
		{
			PostNet tmp = c[i];
			c[i] = c[min_i];
			c[min_i] = tmp;
		}
	}
}
*/

void PostNet::setZip()
{
	
}
void PostNet::setBar()
{
	
}
void PostNet::getZip()
{

}
void PostNet::getBar()
{

}

int main()
{
	char data[1000];
	short size;
	PostNet onlyOneObject;
	onlyOneObject.readWrite("project02input.txt", data, 1000);
	PostNet zipcode;
	zipcode.setZip();
	zipcode.getZip();
	PostNet barcode;
	barcode.setBar();
	barcode.getBar();
	return 0;
}
