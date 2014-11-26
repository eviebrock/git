#!/usr/bin/python3
import sys

if len(sys.argv) == 3:
	print ('Argument 1: ', sys.argv[1])
	print ('Argument 2: ', sys.argv[2])
	onestring = sys.argv[1] + sys.argv[2]
	print ('Argument 1 & 2 concatenated: ', onestring)
else:
	sys.exit()

numbers = ['1', '2', '3', '4', '5', '6', '7', '8', '9', '10']
fo = open("numbers.txt", "w")
for number in numbers:
	fo.write(number)
fo.close()
