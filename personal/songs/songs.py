#!/usr/bin/env python3

import sys
from os import listdir, makedirs
from os.path import isfile, join, exists
from shutil import rmtree

def printList(songs):
	print("\n".join(songs))

def getSongs(inputDir):
	inputDir += "/testInput"
	onlyFiles = [f for f in listdir(inputDir) if isfile(join(inputDir, f))]
	
	return onlyFiles
	
def createOutputDir(outputDir):
	outputDir += "/testOutput"
	
	if not exists(outputDir):
		makedirs(outputDir)
		print("created dir")
	else:
		print("didnt create dir")

def cleanupOutputDir(outputDir):
	outputDir += "/testOutput"
	
	if exists(outputDir):
		rmtre(outputDir)
		print("removed dir")
	else:
		print("didnt remove dir")

def main():
	workingDirectory = "/home/eviebrock/git/personal/songs"
	songs = getSongs(workingDirectory)
	createOutputDir(workingDirectory)
	printList(songs)
	cleanupOutputDir(workingDirectory)
	

if __name__ == "__main__":
        sys.exit(main())
