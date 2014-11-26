#!/usr/bin/env python3

# Set script as executable via: chmod +x tester.py
# Run via: ./tester.py [-h] [--version] [--test] [--target] [--time] [--client] [--server]

import socket
import sys
import argparse
import threading
import struct
import time
import signal

global running
global ctrl_c

# use to pack data:
#	packed_data = struct.pack('bbb', var1, var2, var3)

# use to unpack data:
#	(var1, var2, var3) = unpack('bbb', packed_data)

if not sys.version_info[:2] == (3,3):
	print ("Error: need Python 3.3 to run program")
	sys.exit(1)
else:
	print ("Using Python 3.3 to run program") 

def signal_handler(signal, frame):
        global ctrl_c
        ctrl_c = True
        #print ("\n")
        sys.exit(0)
        
signal.signal(signal.SIGINT, signal_handler)

class Server_Control(threading.Thread):
	def __init__(self):
		threading.Thread.__init__(self)
		
	def run(self):
		global ctrl_c
		global running
		ctrl_c = False
		running = True
		port_num = 5678
		protocol_version = 0x01
		test_reply = 0x02
		test_results = 0x04
		packets_received = 0x00
		
		# Create TCP socket
		try:
			s_listen = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
			s_listen.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR,1)
		except socket.error as msg:
			print("Error: could not create socket")
			print("Description: " + str(msg))
			sys.exit()

		# Bind to listening port
		try:
			host=''  # Bind to all interfaces
			s_listen.bind((host,port_num))
		except socket.error as msg:
			print("Error: unable to bind on port %d" % port_num)
			print("Description: " + str(msg))
			sys.exit()

		# Listen
		try:
			backlog=10  # Number of incoming connections that can wait
				    # to be accept()'ed before being turned away
			s_listen.listen(backlog)
		except socket.error as msg:
			print("Error: unable to listen()")
			print("Description: " + str(msg))
			sys.exit()    

		print("Listening socket bound to port %d" % port_num)

		print("Waiting for client to connect...")
		s_listen.settimeout(1)
	
		while(1):
			if ctrl_c:
				print ("\nExiting server")
				sys.exit()
			
			# Accept an incoming request
			try:
				(s_ctrl, client_addr) = s_listen.accept()
			except socket.timeout:
				continue
			except socket.error as msg:
				print("Error: unable to accept()")
				print("Description: " + str(msg))
				sys.exit()

			if ctrl_c:
				sys.exit()

			s_ctrl.settimeout(45)

			# Receive request
			try:
				client_request = s_ctrl.recv(4096)
				if len(client_request) != 3:
					print ("Invalid client request!")
					continue   # Restart the while loop
			except socket.timeout:
				print ("Request message timed out!")
				s_ctrl.close()
				continue
			except socket.error as msg:
				print("Error: unable to recv()")
				print("Description: " + str(msg))
				s_ctrl.close()
				continue
				
			if ctrl_c:
				sys.exit()

			d = Server_Data()
			d.start()

			# Send reply
			try:
				reply = struct.pack('!BBH', protocol_version, test_reply, port_num)
				server_reply = s_ctrl.sendall(reply)
			except socket.error as msg:
				print("Error: send() failed")
				print("Description: " + str(msg))
				sys.exit()

			if ctrl_c:
				sys.exit()

			# Receive done
			try:
				client_done = s_ctrl.recv(4096)
				if len(client_done) != 2:
					print ("Invalid client done!")
					continue   # Restart the while loop
				else:
					# Stop the server data thread
					running = False;
			except socket.timeout:
				print ("Done message timed out!")
				s_ctrl.close()
				continue
			except socket.error as msg:
				print("Error: unable to recv()")
				print("Description: " + str(msg))
				sys.exit()
		
			if ctrl_c:
				sys.exit()
		
			# Wait for server data thread to finish
			d.join()
		
			# Send results
			try:
				results = struct.pack('!BBQ', protocol_version, test_results, packets_received)
				server_results = s_ctrl.sendall(results)
			except socket.error as msg:
				print("Error: send() failed")
				print("Description: " + str(msg))
				sys.exit()
				
			if ctrl_c:
				sys.exit()
		
		# Close thread
		return

class Server_Data(threading.Thread):
	def __init__(self):
		threading.Thread.__init__(self)
	def run(self):
		print ("Data thread opening")
		# Loop while client has not exited yet
		global ctrl_c
		global running
		while(running):
			if ctrl_c:
				sys.exit()
			time.sleep(1)
		print ("Data thread closing")
		# Close thread
		return

class Client_Control(threading.Thread):
	def __init__(self, args):
		threading.Thread.__init__(self)
		self.args = args		

	def run(self):
		global ctrl_c
		ctrl_c = False
		port_num = 5678
		protocol_version = 0x01
		test_request = 0x01
		test_done = 0x03

		if ctrl_c:
			print ("\nExiting client")
			sys.exit()

		# Create TCP socket
		try:
			s_ctrl = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		except socket.error as msg:
			print("Error: could not create socket")
			print("Description: " + str(msg))
			sys.exit()
			
		if ctrl_c:
			print ("\nExiting client")
			sys.exit()

		# Connect to server
		try:
			s_ctrl.connect((self.args.target , port_num))
			print("Connection established")
		except socket.error as msg:
			print("Error: Could not open connection")
			print("Description: " + str(msg))
			sys.exit()

		if ctrl_c:
			print ("\nExiting client")
			sys.exit()

		# Send request
		try:
			request = struct.pack('!BBB', protocol_version, test_request, self.args.test)
			client_request = s_ctrl.sendall(request)
		except socket.error as msg:
			print("Error: send() failed")
			print("Description: " + str(msg))
			sys.exit()

		if ctrl_c:
			print ("\nExiting client")
			sys.exit()

		# Receive reply
		try:
			server_reply = s_ctrl.recv(4096)
			if len(server_reply) != 4:
					print ("Invalid server reply!")
					# do something
		except socket.error as msg:
			print("Error: unable to recv()")
			print("Description: " + str(msg))
			sys.exit()

		# Launch client data thread
		pause = self.args.time
		d = Client_Data(pause)
		d.start()
		d.join()  # Wait till finished
		
		if ctrl_c:
			print ("\nExiting client")
			sys.exit()
		
		# Send done
		try:
			done = struct.pack('!BB', protocol_version, test_done)
			client_done = s_ctrl.sendall(done)
		except socket.error as msg:
			print("Error: send() failed")
			print("Description: " + str(msg))
			sys.exit()

		if ctrl_c:
			print ("\nExiting client")
			sys.exit()

		# Receive results
		try:
			server_results = s_ctrl.recv(4096)
			if len(server_results) != 10:
					print ("Invalid server results!")
					# do something
		except socket.error as msg:
			print("Error: unable to recv()")
			print("Description: " + str(msg))
			sys.exit()
			
		if ctrl_c:
			print ("\nExiting client")
			sys.exit()	
		
		# Close thread
		return

class Client_Data(threading.Thread):
	def __init__(self, pause):
		threading.Thread.__init__(self)
		self.pause = pause
	def run(self):
		print ("Data thread opening")
		print ("Waiting for %d seconds..." % self.pause)
		if ctrl_c:
			sys.exit()
		time.sleep(self.pause)
		if ctrl_c:
			sys.exit()
		print ("Data thread closing")
		# Close thread
		return

def main():
	parser = argparse.ArgumentParser()
	parser.add_argument("--version", action="version", version="Network Tester 1.0", help="show program's version number")
	parser.add_argument("--test", action="store", dest="test", help="test modes: TCP_STREAM, TCP_RR, UDP_STREAM, and UDP_RR")
	parser.add_argument("--target", action="store", dest="target", help="specifies the IP or hostname the client contacts to run the test")
	parser.add_argument("--time", action="store", dest="time", help="specifies the duration of the test in seconds")
	parser.add_argument("--client", action="store_true", dest="client", help="configures the tester to act as a client")
	parser.add_argument("--server", action="store_true", dest="server", help="configures the tester to act as a server")

	args = parser.parse_args()

	# Set default values if unspecified by user
	if (str(args.test) == "None"):
		args.test = "TCP_STREAM"
	if (str(args.target) == "None"):
		args.target = "localhost"
	if (str(args.time) == "None"):
		args.time = 30

	args.time = int(args.time)

	if args.test == "TCP_STREAM":
		args.test = int(0x01)
	elif args.test == "TCP_RR":
		args.test = int(0x02)
	elif args.test == "UDP_STREAM":
		args.test = int(0x03)
	else:
		args.test = int(0x04)

	if args.client:
		c = Client_Control(args)
		c.start()		
	else:
		c = Server_Control()
		c.start()	
	c.join()
	print("All threads done - now exiting")

if __name__ == "__main__":
	sys.exit(main())
