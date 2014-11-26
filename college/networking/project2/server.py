#!/usr/bin/env python3

# Set script as executable via: chmod +x server.py
# Run via: ./server.py [-h] [--version] [--base BASE_DIR] [--port PORT]
# View in browser: http://localhost:<PORT>/<FILE>.html

import socket
import sys
import argparse
import threading
import select		# <--- is this needed?
import datetime		# <--- is this needed?
import time		# <--- is this needed?
import os
import mimetypes
import datetime

interrupt = False

class Client(threading.Thread):
	def __init__(self, client_s, args):
		threading.Thread.__init__(self)
		self.client_s = client_s
		self.args = args

	def run(self):
		client_request = True;
		while client_request:
			# Receive data
			try:
				# Decrease receive_buffer, loop on recv
				receive_buffer=4096
				raw_bytes = self.client_s.recv(receive_buffer)
				if len(raw_bytes) > 0:
					if self.args.verbose:
						print ("Received %d bytes from client" % len(raw_bytes))
					raw_bytes_str = str(raw_bytes)
					if self.args.verbose:
							print ("Client request is...")
							# Notice only one request is sent, even with a 4096 byte buffer. 
							# Pipelining was also enabled with the command:
							# 	google-chrome --enable-http-pipelining
							print (raw_bytes_str)
					if (raw_bytes_str.find("HEAD") == -1):
						head = False;
					else:
						head = True;
					if (raw_bytes_str.find("\r\n\r\n") == -1):
						read = False;
						#pipeline = raw_bytes_str.split("\r\n\r\n", 1)
						#print (pipeline[0])
						#print (pipeline[1])
					else:
						read = True;
					while read:
						raw_bytes = self.client_s.recv(receive_buffer)
						if len(raw_bytes) > 0:
							if self.args.verbose:
								print ("Received %d bytes from client" % len(raw_bytes))
							raw_bytes_str = str(raw_bytes)
							if (raw_bytes_str.find("\r\n\r\n") == -1):
								read = False;
								if self.args.verbose:
									print ("Client request is...")
									print (raw_bytes_str)
							else:
								read = True;
						else:
							client_request = False;
				else:
					client_request = False;
			except socket.error as msg:
				if self.args.verbose:
					print("Error: unable to recv()")
					print("Description: " + str(msg))
				sys.exit()

			string_unicode = raw_bytes.decode('ascii')
			if self.args.verbose:
				print("Received %d bytes from client" % len(raw_bytes))
				print("Message contents: %s" % string_unicode)

			request = string_unicode.split(' ') 	# Converts string into list of
								# sub strings separated by ' '
			if (client_request):
				if request[1] == "/":
					request[1] = "/index.html"
				filepath = self.args.base_dir + request[1]
		
				try:
					f = open(filepath, "rb")
					success = True;
				except OSError:
					success = False;

				if success:
					content_type, encoding = mimetypes.guess_type(request[1])
					last_modified = os.path.getmtime(filepath)

					success_status = "HTTP/1.1 200 OK \r\n"
					success_date = "Date: %s \r\n" % datetime.date.today()
					success_server = "Host: localhost \r\n"
					success_content_length = "Content-Length: %d \r\n" % os.path.getsize(filepath)
					success_content_type = "Content-Type: %s \r\n" % content_type
					success_last_modified = "Last Modified: %s \r\n" % datetime.datetime.fromtimestamp(last_modified)
					success_expires = "Expires: %s \r\n\r\n" % (datetime.datetime.now() + datetime.timedelta(hours=12))

					raw_success_status = bytes(success_status, "ascii")
					raw_success_date = bytes(success_date, "ascii")
					raw_success_server = bytes(success_server, "ascii")
					raw_success_content_length = bytes(success_content_length, "ascii")
					raw_success_content_type = bytes(success_content_type, "ascii")
					raw_success_last_modified = bytes(success_last_modified, "ascii")
					raw_success_expires = bytes(success_expires, "ascii")

					success_status_sent = self.client_s.sendall(raw_success_status)
					success_date_sent = self.client_s.sendall(raw_success_date)
					success_server_sent = self.client_s.sendall(raw_success_server)
					success_content_length_sent = self.client_s.sendall(raw_success_content_length)
					success_content_type_sent = self.client_s.sendall(raw_success_content_type)
					success_last_modified_sent = self.client_s.sendall(raw_success_last_modified)
					success_expires_sent = self.client_s.sendall(raw_success_expires)

					if head == 0:

						# read 64kB at a time, rather than reading the whole file at once
						read_buffer = 65536
						send = True;
						while send:
							raw_success_data = f.read(read_buffer)
							success_data_sent = self.client_s.sendall(raw_success_data)
							if self.args.verbose:
								print ("Sent %d bytes to client" % len(raw_success_data))
							if (raw_success_data):
								send = True;
							else:
								send = False;

				else:
					error_header = "HTTP/1.1 404 Not Found \r\n\r\n"
					raw_error_header = bytes(error_header,"ascii")
					error_header_sent = self.client_s.sendall(raw_error_header)

					error_data = "Page not found, idiot!"
					raw_error_data = bytes(error_data, "ascii")
					error_data_sent = self.client_s.sendall(raw_error_data)
		try:
			# Close client socket
			self.client_s.close()
			if self.args.verbose:
				print("Closed client socket")
		except server.error as msg:
			if self.args.verbose:
				print("Error: unable to close() client socket")
				print("Description: " + str(msg))
			sys.exit()

# Graceful shutdown handler
#def signal_handler(signum, frame):
#    global interrupted
#    interrupt = True

def main():
	
	parser = argparse.ArgumentParser()
	parser.add_argument("--version", action="version", version="HTTP Server 2.0", help="show program's version number and exit")
	parser.add_argument("--base", action="store", dest="base_dir", help="base directory containing website")
	parser.add_argument("--port", action="store", dest="port_num", help="port number to listen on")
	parser.add_argument("--verbose", action="store_true", dest="verbose", help="enable debugging output to be printed to the console")

	args = parser.parse_args()

	# Convert string to integer
	args.port_num = int(args.port_num)

	# Graceful shutdown handler
	def NewExceptHook(type, value, traceback):
		if type == KeyboardInterrupt:
			c.daemon = True
			c.join()
			print("Exiting")
		else:
			OriginalExceptHook(type, value, traceback)
	sys.excepthook = NewExceptHook
	
	# Create TCP socket
	try:
		s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	except socket.error as msg:
		if args.verbose:
			print("Error: could not create socket")
			print("Description: " + str(msg))
		sys.exit()

	# Bind to listening port
	try:
		host=''  # Bind to all interfaces
		s.bind((host,args.port_num))
	except socket.error as msg:
		if args.verbose:
			print("Error: unable to bind on port %d" % port)
			print("Description: " + str(msg))
		sys.exit()

	# Listen
	try:
		backlog=10  # Number of incoming connections that can wait
			    # to be accept()'ed before being turned away
		s.listen(backlog)
	except socket.error as msg:
		if args.verbose:
			print("Error: unable to listen()")
			print("Description: " + str(msg))
		sys.exit()    

	if args.verbose:
		print("Listening socket bound to port %d" % args.port_num)

	while 1:
	
		# Accept an incoming request
		try:
			(client_s, client_addr) = s.accept()
			# If successful, we now have TWO sockets
			#  (1) The original listening socket, still active
			#  (2) The new socket connected to the client
		except socket.error as msg:
			if args.verbose:
				print("Error: unable to accept()")
				print("Description: " + str(msg))
			sys.exit()
		if args.verbose:
			print("Accepted incoming connection from client")
			print("Client IP, Port = %s" % str(client_addr))

		# Start client thread
		c = Client(client_s, args)
		c.start()

	# Close server sockets
	try:
		s.close()
	except socket.error as msg:
		if args.verbose:
			print("Error: unable to close() server socket")
			print("Description: " + str(msg))
		sys.exit()
	if args.verbose:
		print("Sockets closed, now exiting")

if __name__ == "__main__":
	sys.exit(main())
