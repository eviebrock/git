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

def trimTrackNumber(songs):
	for i in range(len(songs)):
		words = songs[i].split(' ')
		try:
			float(words[0])
			del words[0]
		except ValueError:
			pass

		songs[i] = ' '.join(words)
		
def shortenFeat(songs):
	for i in range(len(songs)):
		words = songs[i].split(' ')
		for j in range(len(words)):
			if ("Feat" in words[j]):
				words[j] = words[j].replace("Feat", "Ft")
		songs[i] = ' '.join(words)

def cleanupOutputDir(outputDir):
	outputDir += "/testOutput"
	
	if exists(outputDir):
		rmtree(outputDir)

def main():
	workingDirectory = "/home/eviebrock/git/personal/songs"
	songs = getSongs(workingDirectory)
	createOutputDir(workingDirectory)
	printList(songs)
	print()
	trimTrackNumber(songs)
	shortenFeat(songs)
	printList(songs)
	print()
	cleanupOutputDir(workingDirectory)
	

if __name__ == "__main__":
        sys.exit(main())
