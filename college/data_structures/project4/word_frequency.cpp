// COMP 53 Fall 2012 - Project 04
// Author: Erich Viebrock
// Compiler: g++
//
// Project04-main.cpp
// Your code should be contained in this file.

#include <iostream>
#include <string>
#include <list>
#include "TextProcessor.h"
using namespace std;

const string filename("project04-input.txt");

// Data type class for node information storage
class WordFreq
{
public:
	string word; // Store word
	long freq; // Store frequency of word
};

// Compares frequency of two nodes, used for sort function
bool compare(WordFreq i, WordFreq j)
{
	return (i.freq > j.freq);
}

int main()
{
	// Creates mylist object, of the list class, which uses WordFreq class 
	// as the data type
	list<WordFreq> mylist;

	list<string> word_list;
	TextProcessor text_proc;
	if (!text_proc.processText(filename, word_list))
	{
		cerr << "ERROR: cannot open file " << filename << endl;
		return(1);
	}

	list<string>::iterator iter = word_list.begin();
	
	while (iter != word_list.end())
	{
		// Create an iterator to iterate through mylist object of nodes
		list<WordFreq>::iterator myiter = mylist.begin();
		//loop to run iterator through mylist objects of nodes
		while (myiter != mylist.end())
		{
			//compares word on txt with word in node
			//if true, increment frequency
			if (*iter == myiter -> word)
			{
				myiter -> freq++;
				break;
			}
			// Increment iterator by 1, run through loop until at 
			// end of linked list
			myiter++;
		}
		//case for word without a node
		if (myiter == mylist.end())
		{
			// Pushes an object of WordFreq class into node, 
			// includes word and word frequency
			WordFreq wf;
			// Sets word to whatever string iter points to
			wf.word = *iter;
			// Sets initial frequency to 1
			wf.freq = 1;
			// Pushes newly created node to the front of list
			mylist.push_front(wf);
		}
		// Increment the iterator to next word in text file
		iter++;
	}
	// Sorts nodes via compare function, which compares frequencies
	mylist.sort(compare);
	
	// Create a new iterator to increment through sorted list
	list<WordFreq>::iterator sortiter = mylist.begin();
	
	// Skip first element of the list, seems to be including spaces
	// as entries
	sortiter++;
	
	// Output loop, continues while not at the end of the list
	while (sortiter != mylist.end())
	{
		// Prints word and frequency of node
		cout << sortiter -> word << " " << sortiter -> freq << endl;
		// Iterate to next node in sorted list
		sortiter++;
	}
	return 0;
}
/*
the 37
of 27
a 14
matter 10
dark 10
and 9
in 8
to 8
is 8
cluster 7
from 6
j0717 5
macs 5
researchers 5
galaxy 5
filament 5
map 4
massive 4
telescope 4
that 4
astronomers 4
images 3
study 3
for 3
this 3
space 3
hubble 3
be 3
cosmic 3
at 3
3d 3
first 3
abell 2
filament's 2
along 2
as 2
core 2
mass 2
view 2
image 2
said 2
ebeling 2
thus 2
earlier 2
our 2
earth 2
light-years 2
around 2
million 2
60 2
out 2
strands 2
one 2
filaments 2
these 2
seen 2
clusters 2
strings 2
with 2
on 2
it 2
gravitational 2
its 2
structure 2
have 2
society 1
astronomical 1
royal 1
notices 1
monthly 1
issue 1
1 1
nov 1
appear 1
will 1
predicted 1
had 1
theorists 1
than 1
more 1
even 1
contain 1
might 1
then 1
other 1
representative 1
if 1
extreme 1
size 1
sheer 1
length 1
sight 1
line 1
almost 1
back 1
stretches 1
found 1
team 1
223 1
222 1
two 1
between 1
year 1
made 1
was 1
section 1
identification 1
say 1
allowed 1
telescopes 1
ground-based 1
observations 1
additional 1
extending 1
string 1
into 1
distortions 1
convert 1
able 1
were 1
background 1
galaxies 1
distort 1
path 1
crooked 1
travel 1
through 1
passing 1
light 1
causing 1
them 1
time 1
warp 1
including 1
objects 1
holds 1
relativity 1
theory 1
general 1
einstein's 1
albert 1
extent 1
techniques 1
lensing 1
used 1
also 1
they 1
canada-france-hawaii 1
subaru 1
japan's 1
well 1
analyzed 1
fellow 1
his 1
left 1
extends 1
visibly 1
blue 1
here 1
shown 1
region 1
surrounding 1
revealed 1
location 1
separate 1
18 1
combination 1
field 1
large 1
hubble's 1
shows 1
enormous 1
16 1
oct 1
tuesday 1
statement 1
manoa 1
hawaii 1
university 1
harald 1
researcher 1
web," 1
detailed 1
target 1
prime 1
growing 1
actively 1
knew 1
we 1
work 1
"from 1
billion 1
5.4 1
about 1
yet 1
largest 1
strand 1
light-year 1
sought 1
elusive 1
probe 1
managed 1
using 1
but 1
observe 1
difficult 1
are 1
directly 1
cannot 1
since 1
giant 1
intersecting 1
mostly 1
long 1
web 1
tangled 1
like 1
structured 1
thought 1
universe 1
surroundings 1
has 1
effects 1
by 1
detected 1
only 1
can 1
invisible 1
an 1
gigantic 1
look 1
their 1
taken 1
*/
