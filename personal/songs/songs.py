#!/usr/bin/env python3

import sys
from os import listdir, makedirs
from os.path import isfile, join, exists
from shutil import rmtree

#import tkinter
import tkinter
from tkinter import *

def printList(songs):
	for i in range(len(songs)):
		print(songs[i])
		#print("\n".join(songs))

def createSongPairList(inputDir):
	inputDir += "/testInput"
	originalSongs = [f for f in listdir(inputDir) if isfile(join(inputDir, f))]
	songPairList = []
	for i in range(len(originalSongs)):
		songPairList.append([originalSongs[i], originalSongs[i]])
	
	return songPairList
	
def createOutputDir(outputDir):
	outputDir += "/testOutput"

	if not exists(outputDir):
		makedirs(outputDir)

def trimTrackNumber(songs):
	for i in range(len(songs)):
		words = songs[i][1].split(' ')
		try:
			float(words[0])
			del words[0]
		except ValueError:
			pass

		songs[i][1] = ' '.join(words)
		
def shortenFeat(songs):
	for i in range(len(songs)):
		if ("Feat." in songs[i][1]):
			songs[i][1] = songs[i][1].replace("Feat.", "Ft.")
		elif ("Feat" in songs[i][1]):
			songs[i][1] = songs[i][1].replace("Feat", "Ft.")
		elif ("feat." in songs[i][1]):
			songs[i][1] = songs[i][1].replace("feat.", "Ft.")
		elif ("Ft" in songs[i][1] and "Ft." not in songs[i][1]):
			songs[i][1] = songs[i][1].replace("Ft", "Ft.")
		elif ("ft." in songs[i][1]):
			songs[i][1] = songs[i][1].replace("ft.", "Ft.")
		
def removeAmpFromFtArtists(songs):
	for i in range(len(songs)):
		pass

def buildSongComparisonString(songs):
	songDiff = ""
	for i in range(len(songs)):
		songDiff += (songs[i][0] + "\t" + songs[i][1] + "\n")

	return songDiff

def promptUser(songs):
	myString = buildSongComparisonString(songs)
		
	top = Tk()
	top.minsize(width=600, height=400)
	window = Frame(top, width=600, height=400)
	window.grid()
	for i in range(len(songs)):
		Message(window, text=songs[i][0]).grid(row=i, column=0, columnspan=10)
		#Message(window, text=songs[i][1]).grid(row=i, column=11, columnspan=10)
	top.mainloop()

def cleanupOutputDir(outputDir):
	outputDir += "/testOutput"
	
	if exists(outputDir):
		rmtree(outputDir)

def main():
	workingDirectory = "/home/eviebrock/git/personal/songs"
	songs = createSongPairList(workingDirectory)
	createOutputDir(workingDirectory)
	trimTrackNumber(songs)
	shortenFeat(songs)
	#removeAmpFromFtArtists(songs)
	printList(songs)
	print()
	
	promptUser(songs)
	cleanupOutputDir(workingDirectory)
	

if __name__ == "__main__":
        sys.exit(main())
