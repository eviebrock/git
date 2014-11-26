#!/usr/bin/env python3

# Set script as executable via: chmod +x server.py
# Run via: ./server.py [-h] [--version] [--base BASE_DIR] [--port PORT]
# View in browser: http://localhost:<PORT>/<FILE>.html

import socket
import sys
import argparse

def main():
	
	parser = argparse.ArgumentParser()
	parser.add_argument("--version", action="version", version="HTTP Server 1.0", help="show program's version number and exit")
	parser.add_argument("--base", action="store", dest="base_dir", help="base directory containing website")
	parser.add_argument("--port", action="store", dest="port_num", help="port number to listen on")
	args = parser.parse_args()

	# Convert string to integer
	args.port_num = int(args.port_num)
		
	# Create TCP socket
	try:
		s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	except socket.error as msg:
		print("Error: could not create socket")
		print("Description: " + str(msg))
		sys.exit()

	# Bind to listening port
	try:
		host=''  # Bind to all interfaces
		s.bind((host,args.port_num))
	except socket.error as msg:
		print("Error: unable to bind on port %d" % port)
		print("Description: " + str(msg))
		sys.exit()

	# Listen
	try:
		backlog=10  # Number of incoming connections that can wait
			    # to be accept()'ed before being turned away
		s.listen(backlog)
	except socket.error as msg:
		print("Error: unable to listen()")
		print("Description: " + str(msg))
		sys.exit()    

	print("Listening socket bound to port %d" % args.port_num)

	while 1:
	
		# Accept an incoming request
		try:
			(client_s, client_addr) = s.accept()
			# If successful, we now have TWO sockets
			#  (1) The original listening socket, still active
			#  (2) The new socket connected to the client
		except socket.error as msg:
			print("Error: unable to accept()")
			print("Description: " + str(msg))
			sys.exit()

		print("Accepted incoming connection from client")
		print("Client IP, Port = %s" % str(client_addr))

		# Receive data
		try:
			buffer_size=4096
			raw_bytes = client_s.recv(buffer_size)
			
			print (str(raw_bytes))

			if len(raw_bytes) == 0:
				continue   # Restart the while loop
		except socket.error as msg:
			print("Error: unable to recv()")
			print("Description: " + str(msg))
			sys.exit()

		string_unicode = raw_bytes.decode('ascii')
		print("Received %d bytes from client" % len(raw_bytes))
		print("Message contents: %s" % string_unicode)

		request = string_unicode.split(' ') 	# Converts string into list of
							# sub strings separated by ' '

		if request[1] == "/":
			request[1] = "/index.html"
		filepath = args.base_dir + request[1]
		print(request[1])

		try:
			f = open(filepath, "rb")
			success = True;
		except OSError:
			success = False;

		if success:
			success_header = "HTTP/1.1 200 OK \r\n\r\n"
			raw_success_header = bytes(success_header, "ascii")
			success_header_sent = client_s.sendall(raw_success_header)
	
			raw_success_data = f.read()
			success_data_sent = client_s.sendall(raw_success_data)
		else:
			error_header = "HTTP/1.1 404 Not Found \r\n\r\n"
			raw_error_header = bytes(error_header,"ascii")
			error_header_sent = client_s.sendall(raw_error_header)

			error_data = "Page not found, idiot!"
			raw_error_data = bytes(error_data, "ascii")
			error_data_sent = client_s.sendall(raw_error_data)

		try:
			# Close client socket
			client_s.close()
		except server.error as msg:
			print("Error: unable to close() client socket")
			print("Description: " + str(msg))
			sys.exit()

	# End of while loop

	# Close server sockets
	try:
		#client_s.close()
		s.close()
	except socket.error as msg:
		print("Error: unable to close() server socket")
		print("Description: " + str(msg))
		sys.exit()

	print("Sockets closed, now exiting")

if __name__ == "__main__":
	sys.exit(main())
