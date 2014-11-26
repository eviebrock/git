#!/usr/bin/env python3

import argparse
import configparser
import socket
import select
import sys
import threading

import chatProtocol

def main():
	# Setup program configuration (from arguments)
	parser = argparse.ArgumentParser(description='Chat server *tester* for COMP/ECPE 177')
	parser.add_argument('--version', action='version', version='%(prog)s 1.0')
	parser.add_argument('--config', action='store', dest='config_file', help='Config file to use', default='config.ini')
	args = parser.parse_args()

	print("Running Chat server tester")
	print("Configuration file: %s" % args.config_file)
	print("---")

	# Setup program configuration (from file)
	config = configparser.ConfigParser()
	files_read = config.read(args.config_file)
	if len(files_read) != 1:
		print("ERROR: Config file '%s' not found" % args.config_file)
		exit()
	server_hostname = config['DEFAULT']['server-hostname']
	server_port = int(config['DEFAULT']['server-port'])
	num_clients = int(config['DEFAULT']['num-clients'])

	print("Chat server to test: %s:%d" % (server_hostname, server_port))
	print("Number of fake clients to use: %d" % num_clients)

	threads=[]    
	i=1
	while(i <= num_clients):
		if(str(i) in config):
			username = config[str(i)]['username']
			input_file = config[str(i)]['input-file']
			output_file = config[str(i)]['output-file']
			print("---User %d---" % i)
			print("Username: %s" % username)
			print("Input file: %s" % input_file)
			print("Output file: %s" % output_file)

			# ----------------------
			# Student work:
			#   You might want to launch your client threads here...
			# ----------------------

			c = Client(server_hostname, server_port, username, input_file, output_file)
			c.daemon=True
			threads.append(c)

			# ----------------------
			# XXXX STUDENT WORK XXXX
			#t = testThread(server_hostname, server_port,
			#               username, input_file, output_file)
			#t.daemon=True
			#threads.append(t)
			# XXXX STUDENT WORK XXXX
			# ----------------------
		else:
			print("ERROR: No config section found for fake user #%d" % i)
			exit()
		i=i+1

	# --------------------------------------------
	# Student work:
	# (1) Create a thread for each fake user specified in config file
	#     Note that the code above already parses the input file for you
	# (2) In each thread:
	#       (a) Open the input file and output file
	#       (b) Connect to the chat server being tested
	#       (c) Send a JOIN message to server
	#       (d) Send many TEXT messages, one per line in input file
	#           At the same time, also receive responses from
	#           server and save to output file
	#       (e) Send a LEAVE message to server
	#       (f) Close connection to the chat server being tested
	#       (g) Exit thread
	# (3) Exit program only all threads have exited
	# --------------------------------------------


	# ----------------------
	# XXXX STUDENT WORK XXXX
	# Start the client threads all at once
	# (so they start closer to the same point in time)
	for c in threads:
		c.start()

	# Wait for the client threads to complete before exiting main thread
	for c in threads:
		c.join()

	print("Exiting test program")
	# XXXX STUDENT WORK XXXX
	# ----------------------

class Client(threading.Thread):
	def __init__(self, server_hostname, server_port, username, input_file, output_file):
		threading.Thread.__init__(self)
		self.server_hostname = server_hostname
		self.server_port = server_port
		self.username = username
		self.input_file = input_file
		self.output_file = output_file
		self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		self.protocol = chatProtocol.chatProtocol()
		
	def run(self):
		print ("Starting Client thread for user %s" % self.username)
		
		# Open input file
		try:
			fIn = open(self.input_file, 'r')
			print ("Opened input file")
		except IOError as message:
			print("ERROR: Unable to open input file %s" % self.input_file)
			return

		# Open output file
		try:
			fOut = open(self.output_file, 'w')
			print ("Opened output file")
		except IOError as message:
			print("ERROR: Unable to open output file %s" % self.output_file)
			return
		
		# Connect to server
		try:
			address = (self.server_hostname, self.server_port)
			self.s.connect(address)
		except socket.error as message:
			print("ERROR: Unable to connect to server %s:%d" % (self.server_hostname, self.server_port))
			print(message)
			sys.exit()
		
		# Build and send JOIN message
		raw_bytes = self.protocol.buildJoin(self.username)
		#print (raw_bytes)
		self.s.sendall(raw_bytes)
		
		# Buid and send TEXT messages
		# Switch from sendall() to recv()
		# on each pass of while() loop
		i = 1
		self.s.settimeout(5)
		while (1):
			if i % 2 == 0:
				print ("Client sending")
				line = fIn.readline()
				if (line is ""):
					print ("At end of .txt file")
				else:
					#print ("%s" % line)
					raw_bytes = self.protocol.buildText(self.username, line)
					#print (raw_bytes)
					self.s.sendall(raw_bytes)
			
			else:
				try:
					print ("Client receiving")
					raw_bytes = self.s.recv(4096)
					string_unicode = raw_bytes.decode('ascii')
					split = string_unicode.split('\r\n')
					if split[0].find("TEXT") != -1:
						username = split[2][10:]
						text = split[4]
						print ("%s: %s\n" % (username, text))
						fOut.write("%s: %s\n" % (username, text))
				except socket.timeout:
					print ("Recv() timed out!")
					break
				except socket.error as msg:
					print("Error: unable to recv()")
					print("Description: " + str(msg))
					sys.exit()
		
			i = i + 1
		
		# Build and send LEAVE message
		raw_bytes = self.protocol.buildLeave(self.username)
		#print (raw_bytes)
		self.s.sendall(raw_bytes)
		
		# Close connection to server
		self.s.close()
		
		print ("Closing .txt files")
		fIn.close()
		fOut.close()
		
		print ("Stopping Client thread for user %s" % self.username)
		return

if __name__ == "__main__":
	sys.exit(main())
