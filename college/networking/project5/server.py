#!/usr/bin/env python3

# Set script as executable via: chmod +x server.py
# Run via: ./server.py [-h] [--version] [--port]

import socket
import sys
import argparse
import threading
import signal
import queue

import time

if not sys.version_info[:2] == (3,3):
	print ("Error: need Python 3.3 to run program")
	sys.exit(1)

global ctrl_c

def signal_handler(signal, frame):
        global ctrl_c
        ctrl_c = True
        sys.exit(0)

class Server_Receive(threading.Thread):
	def __init__(self, client_s, args, q):
		threading.Thread.__init__(self)
		self.client_s = client_s
		self.args = args
		self.q = q

	def run(self):
		print ("Starting server receive thread")
		
		global ctrl_c
		ctrl_c = False;
		client_active = True;
		self.client_s.settimeout(1)
		
		while client_active:
			
			if ctrl_c:
				sys.exit()	
		
			try:
				raw_bytes = self.client_s.recv(4096)
			except socket.timeout:
				continue
			except socket.error as msg:
				print("Error: unable to recv()")
				print("Description: " + str(msg))
				sys.exit()
				
			if str(raw_bytes).find("LEAVE") != -1:
				client_active = False;
			
			self.q.put((raw_bytes, self.client_s))
				
		try:
			# Close client socket
			self.client_s.close()
		except server.error as msg:
			print("Error: unable to close() client socket")
			print("Description: " + str(msg))
		print ("Exiting server receive thread")
		return

class Server_Send(threading.Thread):
	def __init__(self, args, q):
		threading.Thread.__init__(self)
		self.args = args
		self.q = q

	def run(self):
		print ("Starting server send thread")
		
		global ctrl_c
		ctrl_c = False;
		socket_list = []
		
		while 1:
		
			if ctrl_c:
				sys.exit()
		
			try:
				raw_bytes, client_s = self.q.get(timeout=1)
			except:
				continue
			
			client_msg = raw_bytes.decode('ascii')
			msg_split = client_msg.split('\r\n')
					
			if msg_split[0].find("JOIN") != -1:
				username = msg_split[1][10:]
				socket_list.append((username, client_s))
			
			elif msg_split[0].find("TEXT") != -1:
				username = msg_split[1][10:]

			elif msg_split[0].find("LEAVE") != -1:
				username = msg_split[1][10:]
				socket_list.remove((username, client_s))
			
			for data in socket_list:
			
				if data[0] != username:
					try:
						raw_bytes_sent = data[1].sendall(raw_bytes)
					except socket.error as msg:
						print("Error: sendall() failed")
						print("Description: " + str(msg))
				
		print ("Exiting server send thread")
		return
		
def main():
	parser = argparse.ArgumentParser()
	parser.add_argument("--version", action="version", version="Chat Room Server 1.0", help="show program's version number")
	parser.add_argument("--port", action="store", dest="port_num", help="port number to listen on")

	args = parser.parse_args()
	global ctrl_c
	ctrl_c = False;
	if (str(args.port_num) == "None"):
		args.port_num = 8765
	args.port_num = int(args.port_num)
	
	q = queue.Queue()		
	send = Server_Send(args, q)
	
	send.start()
	
	# Create TCP socket
	try:
		s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR,1)
	except socket.error as msg:
		print("Error: could not create socket")
		print("Description: " + str(msg))
		sys.exit()

	# Bind to listening port
	try:
		host=''  # Bind to all interfaces
		s.bind((host,args.port_num))
	except socket.error as msg:
		print("Error: unable to bind on port %d" % args.port_num)
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

	s.settimeout(1)
	print("Listening socket bound to port %d" % args.port_num)

	while 1:
		if ctrl_c:
			sys.exit()
		
		# Accept an incoming request
		try:
			(client_s, client_addr) = s.accept()
		except socket.timeout:
			continue
		except socket.error as msg:
			print("Error: unable to accept()")
			print("Description: " + str(msg))
			sys.exit()
			
		if ctrl_c:
			sys.exit()	
		
		print("Accepted incoming connection from client")
		print("Client IP, Port = %s" % str(client_addr))
		
		if ctrl_c:
			sys.exit()
		
		receive = Server_Receive(client_s, args, q)
		receive.start()
		
		if ctrl_c:
			sys.exit()
	
	send.join()
	receive.join()
		
	# Close server socket
	try:
		s.close()
	except socket.error as msg:
		print("Error: unable to close() server socket")
		print("Description: " + str(msg))
		sys.exit()
	
if __name__ == "__main__":
	sys.exit(main())
