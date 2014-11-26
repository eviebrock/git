#!/usr/bin/env python3

# Set script as executable via: chmod +x midterm.py
# Run via: ./midterm.py [--url=<Remote Directory] [--file=<Local File>]
# Example: ./midterm.py --url=http://a.b.c.d/dir/x.jpg --file=x.jpg
#	Result: 'x.jpg' is placed inside '/dir' on server a.b.c.d

import socket
import sys
import argparse
import os

def main():
	
	parser = argparse.ArgumentParser()
	parser.add_argument("--url", action="store", dest="remote_dir", help="remote directory to push file")
	parser.add_argument("--file", action="store", dest="local_file", help="local file on disk")
	args = parser.parse_args()

	ip = args.remote_dir.split('/')
	# (ip[2])	--->	# 10.10.206.93
	# (ip[3])	--->	# students
	# (ip[4])	--->	# eviebroc
	# (ip[5])	--->	# file

	port = 80
	base_dir = "/home/erich/ecpe177/midterm/upload/"
	filepath = base_dir + args.local_file
	destination = ip[3] + "/" + ip[4] + "/" + ip [5]
	print (destination)

	filepath = base_dir + args.local_file
	print (filepath)

	# Create TCP socket
	try:
		s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	except socket.error as msg:
		print("Error: could not create socket")
		print("Description: " + str(msg))
		sys.exit()
	
	print("Connecting to server at " + ip[2] + " on port " + str(port))

	# Connect to server
	try:
		s.connect((ip[2] , port))
		print("Connection established")
	except socket.error as msg:
		print("Error: Could not open connection")
		print("Description: " + str(msg))
		sys.exit()

	try:
		f = open(filepath, "rb")
		success = True;
	except OSError:
		success = False;

	if success:
		success_request = "PUT /%s HTTP/1.1 \r\n" % destination
		success_host = "Host: %s \r\n" % ip[2]
		success_content_length = "Content-Length: %d \r\n" % os.path.getsize(filepath)
		success_user_agent = "User-Agent: 177 Midterm Exam \r\n"
		success_expect = "Expect: 100-Continue \r\n\r\n"
		print (success_request)
		print (success_host)
		print (success_content_length)
		print (success_user_agent)
		print (success_expect)

		raw_success_request = bytes(success_request, "ascii")
		raw_success_host = bytes(success_host, "ascii")
		raw_success_content_length = bytes(success_content_length, "ascii")
		raw_success_user_agent = bytes(success_user_agent, "ascii")
		raw_success_expect = bytes(success_expect, "ascii")

		success_request_sent = s.sendall(raw_success_request)
		success_host_sent = s.sendall(raw_success_host)
		success_content_length_sent = s.sendall(raw_success_content_length)
		success_user_agent_sent = s.sendall(raw_success_user_agent)
		success_expect_sent = s.sendall(raw_success_expect)

	else:
		print ("Could not open file")

	try:
		# recv() request response
		raw_bytes = s.recv(4096)
	except socket.error as msg:
		print("Error: unable to recv()")
		print("Description: " + str(msg))
		sys.exit()

	str_raw_bytes = str(raw_bytes)
	
	print (str_raw_bytes)

	if (str_raw_bytes.find("HTTP/1.1 100 Continue")):
		# Send data
		raw_success_data = f.read()
		success_data_sent = s.sendall(raw_success_data)
	else:
		print ("Server is not OK with PUT request")

	try:
		# recv() data response
		raw_bytes = s.recv(4096)
	except socket.error as msg:
		print("Error: unable to recv()")
		print("Description: " + str(msg))
		sys.exit()
			
	str_raw_bytes = str(raw_bytes)
	
	if (str_raw_bytes.find("HTTP/1.1 201 Created")):
		print ("File was uploaded to server")
	elif (str_raw_bytes.find("HTTP/1.1 204 No Content")):
		print ("File has already been uploaded to server")
	
	if (str_raw_bytes.find("\r\n\r\n") != -1):
		print ("End of server data response")

	# Close socket
	try:
		s.close()
	except socket.error as msg:
		print("Error: unable to close() socket")
		print("Description: " + str(msg))
		sys.exit()

	print("Sockets closed, now exiting")

if __name__ == "__main__":
	sys.exit(main())
