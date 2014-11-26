#!/usr/bin/env python3

# Set script as executable via: chmod +x client.py
# Run via: ./client.py [-h] [--version] [--target] [--port] [--username]

import socket
import sys
import argparse
import threading
import signal
import os
import tkinter
import time
import queue
from tkinter.scrolledtext import ScrolledText
from tkinter.filedialog import askopenfilename

global s_data
global client_active

if not sys.version_info[:2] == (3,3):
	print ("Error: need Python 3.3 to run program")
	sys.exit(1)

# self.ui_top.after(200, fun_name) ---> 200 ms for every function call
	# Run this inside the callback
	# to reregiser
	
class Client_Send(threading.Thread):
	def __init__(self, args, q_send, b):
		threading.Thread.__init__(self)
		self.args = args	
		self.q_send = q_send
		self.b = b

	def run(self):
		print ("Starting client send thread")
		
		global s_data
		global client_active
		client_active = True;
		
		# Create TCP socket
		try:
			s_data = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		except socket.error as msg:
			print("Error: could not create socket")
			print("Description: " + str(msg))
			sys.exit()

		# Connect to server
		try:
			s_data.connect((self.args.target , self.args.port_num))
		except socket.error as msg:
			print("Error: Could not open connection")
			print("Description: " + str(msg))
			sys.exit()
		
		# Wait for client to connect to server,
		# and update global variable 's_data'
		self.b.wait()
		
		# JOIN
		'''
		CHAT/1.0 JOIN\r\n
		Username: shafer\r\n
		\r\n
		'''
		username_header = "Username: %s" % self.args.username
		join = "CHAT/1.0 JOIN" + "\r\n" + username_header + "\r\n\r\n"
		raw_join = bytes(join, "ascii")
		
		try:
			join_sent = s_data.sendall(raw_join)
		except socket.error as msg:
			print("Error: sendall() failed")
			print("Description: " + str(msg))
			sys.exit()
		
		while client_active:
		
			# TEXT
			'''
			CHAT/1.0 TEXT\r\n
			Username: shafer\r\n
			Msg-len: 22\r\n
			\r\n
			My first chat message!
			'''
			#print ("Beginning client_active while loop...")
			try:
				ui_text = self.q_send.get(timeout=1)
			except queue.Empty:
				continue
			
			msg_len_header = "Msg-len: %d" % ui_text.__len__()
			text = "CHAT/1.0 TEXT" + "\r\n" + username_header + "\r\n" + msg_len_header + "\r\n\r\n" + ui_text
			raw_text = bytes(text, "ascii")

			try:
				text_sent = s_data.sendall(raw_text)
			#except socket.timeout:
			#	continue
			except socket.error as msg:
				print("Error: sendall() failed")
				print("Description: " + str(msg))
				sys.exit()
		
		# LEAVE
		'''
		CHAT/1.0 LEAVE\r\n
		Username: shafer\r\n
		\r\n
		'''
		
		leave = "CHAT/1.0 LEAVE" + "\r\n" + username_header + "\r\n\r\n"
		raw_leave = bytes(leave, "ascii")
		
		try:
			leave_sent = s_data.sendall(raw_leave)
		except socket.error as msg:
			print("Error: sendall() failed")
			print("Description: " + str(msg))
			sys.exit()

		return

class Client_Receive(threading.Thread):
	def __init__(self, args, q_receive_join, q_receive_text, q_receive_leave, b):
		threading.Thread.__init__(self)
		self.args = args
		self.q_receive_join = q_receive_join
		self.q_receive_text = q_receive_text
		self.q_receive_leave = q_receive_leave
		self.b = b

	def run(self):
		print ("Starting client receive thread")
		
		global s_data
		
		# Wait for client to connect to server,
		# and update global variable 's_data'
		self.b.wait()
		
		while client_active:
			try:
				raw_response = s_data.recv(4096)
			except socket.error as msg:
				print("Error: unable to recv()")
				print("Description: " + str(msg))
				sys.exit()
					
			server_response = raw_response.decode('ascii')
			
			print ("Server response is...%s" % server_response)
			
			response_split = server_response.split('\r\n')
				
			if response_split[0].find("CHAT/1.0") != -1:	
					
				if response_split[0].find("JOIN") != -1:
					username = response_split[1][10:]
					self.q_receive_join.put(username)
			
				elif response_split[0].find("TEXT") != -1:
					username = response_split[1][10:]
					text = response_split[4]
					self.q_receive_text.put((username, text))

				elif response_split[0].find("LEAVE") != -1:
					username = response_split[1][10:]
					self.q_receive_leave.put(username)
					
				else:
					print ("Missing 'JOIN', 'LEAVE', or 'TEXT' header!")
				
			else:
				print ("Missing CHAT/1.0 header!")
	
		print ("Exiting client receive thread")
		
		return				
					
class clientUI():
	def __init__(self, args, q_send, q_receive_join, q_receive_text, q_receive_leave, b):
		self.first_click = True;
		self.args = args
		self.q_send = q_send
		self.q_receive_join = q_receive_join
		self.q_receive_text = q_receive_text
		self.q_receive_leave = q_receive_leave
		self.b = b
		
	def start(self):
		print("Starting clientUI...")
		self.initDisplay()
		self.ui_messages.insert(tkinter.END, "%s has joined the chat room...\n" % self.args.username)
		self.ui_input.insert(tkinter.END, "<Enter message>")

		self.ui_top.after(100, self.receiveMsg)

		# This call to mainloop() is blocking and will last for the lifetime
		# of the GUI.
		self.ui_top.mainloop()

		# Should only get here after destroy() is called on ui_top
		print("Stopping clientUI...")

	def initDisplay(self):
		self.ui_top = tkinter.Tk()
		self.ui_top.wm_title("Chat Room 1.0 - %s" % self.args.username)
		self.ui_top.resizable('1','1')
		self.ui_top.protocol("WM_DELETE_WINDOW", self.eventDeleteDisplay)

		self.ui_messages = ScrolledText(
			master=self.ui_top,
			wrap=tkinter.WORD,
			width=50,  # In chars
			height=25)  # In chars     

		self.ui_input = tkinter.Text(
			master=self.ui_top,
			wrap=tkinter.WORD,
			width=50,
			height=4)
        
		# Bind the button-1 click of the Entry to the handler
		self.ui_input.bind('<Button-1>', self.eventInputClick)
        
        	#self.ui_top.after(200, receiveMsg)
        
		self.ui_button_send = tkinter.Button(
			master=self.ui_top,
			text="Send",
			command=self.sendMsg)

		# Compute display position for all objects
		self.ui_messages.pack(side=tkinter.TOP, fill=tkinter.BOTH)
		self.ui_input.pack(side=tkinter.TOP, fill=tkinter.BOTH)
		self.ui_button_send.pack(side=tkinter.LEFT)

	# SEND button pressed
	def sendMsg(self):
		# Get user input (minus newline character at end)
		msg = self.ui_input.get("0.0", tkinter.END+"-1c")
		if len(msg) > 0:
			self.q_send.put(msg)
			print("UI: Got text: '%s'" % msg)

			# Add this data to the message window
			self.ui_messages.insert(tkinter.INSERT, "%s: %s\n" % (self.args.username, msg))
			self.ui_messages.yview(tkinter.END)  # Auto-scrolling

			# Clean out input field for new data
			self.ui_input.delete("0.0", tkinter.END)

	# Receive messages from other clients
	def receiveMsg(self):
		#print ("Inside receiveMsg")
		try:
			username_join = self.q_receive_join.get(block=False)
			join_msg = True;
		except queue.Empty:
			join_msg = False;
			
		try:
			username_text, text = self.q_receive_text.get(block=False)
			text_msg = True;
		except queue.Empty:
			text_msg = False;
		
		try:
			username_leave = self.q_receive_leave.get(block=False)
			leave_msg = True;
		except queue.Empty:
			leave_msg = False;
		
		if join_msg:
			self.ui_messages.insert(tkinter.INSERT, "%s has joined the chat room...\n" % username_join)
			self.ui_messages.yview(tkinter.END)  # Auto-scrolling
			
		elif text_msg:
			self.ui_messages.insert(tkinter.INSERT, "%s: %s\n" % (username_text, text))
			self.ui_messages.yview(tkinter.END)  # Auto-scrolling
		
		elif leave_msg: 
			self.ui_messages.insert(tkinter.INSERT, "%s has left the chat room...\n" % username_leave)
			self.ui_messages.yview(tkinter.END)  # Auto-scrolling
			
		self.ui_top.after(100, self.receiveMsg)

	# FILE button pressed
	def sendFile(self):
		file = askopenfilename()

		if(len(file) > 0 and os.path.isfile(file)):
			print("UI: Selected file: %s" % file)
		else:
			print("UI: File operation canceled")

	# Event handler - User closed program via window manager or CTRL-C
	def eventDeleteDisplay(self):
		print("UI: Closing")
		global client_active
		client_active = False;
		
		# Continuing closing window now
		self.ui_top.destroy()

	# Event handler - User clicked inside the "ui_input" field
	def eventInputClick(self, event):
		if(self.first_click):
			# If this is the first time the user clicked,
			# clear out the tutorial message currently in the box.
			# Otherwise, ignore it.
			self.ui_input.delete("0.0", tkinter.END)
			self.first_click = False;

def main():
	parser = argparse.ArgumentParser()
	parser.add_argument("--version", action="version", version="Chat Room Client 1.0", help="show program's version number")
	parser.add_argument("--target", action="store", dest="target", help="IP or hostname of the server to connect to")
	parser.add_argument("--port", action="store", dest="port_num", help="Port number of the server to connect to")
	parser.add_argument("--username", action="store", dest="username", help="Username the client will use when communicating with the server")
	
	args = parser.parse_args()

	# Set default values if unspecified by user
	if (str(args.target) == "None"):
		args.target = "localhost"
	if (str(args.port_num) == "None"):
		args.port_num = 8765
	if (str(args.username) == "None"):
		print ("Missing username!")
		sys.exit()
	
	args.port_num = int(args.port_num)
	
	q_receive_join = queue.Queue()
	q_receive_text = queue.Queue()
	q_receive_leave = queue.Queue()
	q_send = queue.Queue()
	b = threading.Barrier(2)
	s = Client_Send(args, q_send, b)
	r = Client_Receive(args, q_receive_join, q_receive_text, q_receive_leave, b)
	ui = clientUI(args, q_send, q_receive_join, q_receive_text, q_receive_leave, b)

	try:
		s.start()
	except KeyboardInterrupt:
		print ("Exiting client send thread")
		#sys.exit()
		
	try:
		r.start()
	except KeyboardInterrupt:
		print ("Exiting client receive thread")
		#sys.exit()
	
	# Run the UI, and capture CTRL-C to terminate
	try:
		ui.start()
	except KeyboardInterrupt:
		print("Exiting client UI")
		ui.eventDeleteDisplay()
		
	print ("Exiting client program")
	
if __name__ == "__main__":
	sys.exit(main())
