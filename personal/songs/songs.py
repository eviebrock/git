#!/usr/bin/env python3

import sys
from os import listdir, makedirs
from os.path import isfile, join, exists
from shutil import rmtree

#import tkinter
import tkinter
from tkinter import *
from tkinter import messagebox

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
		ftIndex = songs[i][1].find("Ft.")
		if ftIndex != -1:
			closeIndex = songs[i][1].find(")", ftIndex)
			if closeIndex != -1:
				ampIndex = songs[i][1].find("&", ftIndex, closeIndex)
				if ampIndex != -1 and songs[i][1][ampIndex-1] == ' ' and songs[i][1][ampIndex+1]:
					songs[i][1] = songs[i][1].replace(" & ", ", ")
					
				
def editCallBack():
	tkinter.messagebox.showinfo("Edit", "Put text to edit box here")
	
def revertCallBack():
	tkinter.messagebox.showinfo("Revert", "Put text to revert box here")

def saveCallBack():
	tkinter.messagebox.showinfo("Save", "Gotta overwrite da files")

def promptUser(songs):
	#myString = buildSongComparisonString(songs)
		
	top = Tk()
	#top.minsize(width=600, height=100)
	window = Frame(top, width=600, height=400, bg="red", bd=50)
	window.grid()
	Label(window, text="FIRST", bd=5, relief=RAISED).grid(row=0, column=0)
	Label(window, text="SECOND", bd=5, relief=RAISED).grid(row=0, column=1)
	for i in range(len(songs)):
		Label(window, text=songs[i][0], bd=5).grid(row=i+1, column=0, sticky=W)
		Label(window, text=songs[i][1], bd=5).grid(row=i+1, column=1, sticky=W)
		Button(window, text="edit", command=editCallBack).grid(row=i+1, column=2)
		Button(window, text="keep original", command=revertCallBack).grid(row=i+1, column=3)
	Button(window, text="save changes", command=saveCallBack, bd=5).grid(row=len(songs)+1, columnspan=4)
		
	top.mainloop()

def testGui(songs):
	root = Tk()
	frame = Frame(root)
	frame.pack()

	bottomframe = Frame(root)
	bottomframe.pack( side = BOTTOM )

	redbutton = Message(frame, text="Redasf;akjf;asjkdf;askljfa;lsjkfa;sdjf", fg="red")
	redbutton.pack( side = LEFT)

	greenbutton = Button(frame, text="Brown", fg="brown")
	greenbutton.pack( side = LEFT )

	bluebutton = Button(frame, text="Blue", fg="blue")
	bluebutton.pack( side = LEFT )

	blackbutton = Button(bottomframe, text="Black", fg="black")
	blackbutton.pack( side = BOTTOM)

	root.mainloop()

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
	removeAmpFromFtArtists(songs)
	printList(songs)
	print()
	
	promptUser(songs)
	#testGui(songs)
	cleanupOutputDir(workingDirectory)
	

if __name__ == "__main__":
        sys.exit(main())
