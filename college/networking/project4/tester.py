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
global packets_sent
global udp_packets_received

if not sys.version_info[:2] == (3,3):
	print ("Error: need Python 3.3 to run program")
	sys.exit(1)

def signal_handler(signal, frame):
        global ctrl_c
        ctrl_c = True
        sys.exit(0)
        
signal.signal(signal.SIGINT, signal_handler)

class Server_Control(threading.Thread):
	def __init__(self, args):
		threading.Thread.__init__(self)
		self.args = args
	def run(self):
		global ctrl_c
		global running
		global udp_packets_received
		ctrl_c = False
		#running = True
		target = self.args.target
		port_num_ctrl = 5678
		port_num_data = 8765
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
			s_listen.bind((host,port_num_ctrl))
		except socket.error as msg:
			print("Error: unable to bind on port %d" % port_num_ctrl)
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

			# Receive request
			try:
				client_request = s_ctrl.recv(4096)
				if len(client_request) != 3:
					print ("Invalid client request!")
					continue   # Restart the while loop
			except socket.error as msg:
				print("Error: unable to recv()")
				print("Description: " + str(msg))
				s_ctrl.close()
				continue
			
			(protocol_version, test_request, test) = struct.unpack('!BBB', client_request)
						
			if ctrl_c:
				sys.exit()

			d = Server_Data(test, port_num_data, target)
			d.start()

			# Send reply
			try:
				reply = struct.pack('!BBH', protocol_version, test_reply, port_num_data)
				server_reply = s_ctrl.sendall(reply)
			except socket.error as msg:
				print("Error: sendall() failed")
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
			except socket.error as msg:
				print("Error: unable to recv()")
				print("Description: " + str(msg))
				sys.exit()
		
			if ctrl_c:
				sys.exit()
			
			if test == 0x03 or test == 0x04:
				try:
					d.exit()
				except:
					# Used to catch exception thrown for forcibly closing thread
					print ("Data thread closing")
			else:
				# Wait for server data thread to finish
				d.join()
		
			# Send results
			try:
				if test == 0x03 or test == 0x04:
					packets_received = udp_packets_received
				results = struct.pack('!BBQ', protocol_version, test_results, packets_received)
				server_results = s_ctrl.sendall(results)
			except socket.error as msg:
				print("Error: sendall() failed")
				print("Description: " + str(msg))
				sys.exit()
				
			if ctrl_c:
				sys.exit()
		
		# Close thread
		return

class Server_Data(threading.Thread):
	def __init__(self, test, port_num_data, target):
		threading.Thread.__init__(self)
		self.test = test
		self.port_num_data = port_num_data
		self.target = target
	def run(self):
		print ("Data thread opening")
		# Loop while client has not exited yet
		global ctrl_c
		global running
		global udp_packets_received
		udp_packets_received = 0
		running = True;
		client_sending = True;
				
		# Create TCP or UDP socket
		try:
			if (self.test == 0x01 or self.test == 0x02):
				s_listen = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
			else:
				s_data = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
			
			if (self.test == 0x01 or self.test == 0x02):
				s_listen.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR,1)
			else:
				s_data.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR,1)

		except socket.error as msg:
			print("Error: could not create socket")
			print("Description: " + str(msg))
			sys.exit()

		if (self.test == 0x02):
			s_listen.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)

		# Bind to listening port
		try:
			host=''  # Bind to all interfaces
			if (self.test == 0x01 or self.test == 0x02):
				s_listen.bind((host, self.port_num_data))
			else:
				s_data.bind((host, self.port_num_data))
		except socket.error as msg:
			print("Error: unable to bind on port %d" % self.port_num_data)
			print("Description: " + str(msg))
			sys.exit()

		if (self.test == 0x01 or self.test == 0x02):
			# Listen
			try:
				backlog=10  # Number of incoming connections that can wait
					    # to be accept()'ed before being turned away
				s_listen.listen(backlog)
			except socket.error as msg:
				print("Error: unable to listen()")
				print("Description: " + str(msg))
				sys.exit()

		if (self.test == 0x01 or self.test == 0x02):
			s_listen.settimeout(1)
		else:
			s_data.settimeout(1)
		
		while(running):
			if ctrl_c:
				print ("\nExiting server")
				sys.exit()
			# Accept an incoming request
			if (self.test == 0x01 or self.test == 0x02):
				try:
					(s_data, client_addr) = s_listen.accept()
				except socket.timeout:
					return
				except socket.error as msg:
					print("Error: unable to accept()")
					print("Description: " + str(msg))
					sys.exit()

			if ctrl_c:
				sys.exit()

			s_data.settimeout(45)
			
			# Receive TCP or UDP data
			while client_sending:
				# TCP stream
				if (self.test == 0x01):
					try:
						client_data = s_data.recv(65536)
					except socket.timeout:
						s_data.close()
						return
					except socket.error as msg:
						print("Error: unable to recv()")
						print("Description: " + str(msg))
						s_data.close()
						continue
					if len(client_data) == 0:
						client_sending = False;	

				# TCP round robin
				elif (self.test == 0x02):
					try:
						client_data = s_data.recv(1)
					except socket.timeout:
						s_data.close()
						return
					except socket.error as msg:
						print("Error: unable to recv()")
						print("Description: " + str(msg))
						s_data.close()
						continue
					if len(client_data) == 0:
						client_sending = False;
					else:
						try:
							client_data_response = s_data.sendall(client_data)
						except socket.error as msg:
							print("Error: sendall() failed")
							print("Description: " + str(msg))
							sys.exit()

				# UDP stream
				elif (self.test == 0x03):
					try:
						client_data, addr = s_data.recvfrom(1472)
					except socket.timeout:
						s_data.close()
						return
					except socket.error as msg:
						print("Error: unable to recvfrom()")
						print("Description: " + str(msg))
						s_data.close()
						continue
					udp_packets_received = udp_packets_received + len(client_data)
					if len(client_data) == 0:
						client_sending = False;

				# UDP round robin
				else:
					try:
						client_data, addr = s_data.recvfrom(1)
					except socket.timeout:
						s_data.close()
						return
					except socket.error as msg:
						print("Error: unable to recvfrom()")
						print("Description: " + str(msg))
						s_data.close()
						continue
					udp_packets_received = udp_packets_received + len(client_data)
					if len(client_data) > 0:
						try:
							client_data_response = s_data.sendto(client_data, (addr[0], addr[1]))
						except socket.error as msg:
							print("Error: sendto() failed")
							print("Description: " + str(msg))
							sys.exit()
					else:
						client_sending = False;		
			if ctrl_c:
				sys.exit()
			
		print ("Data thread closing")
		# Close thread
		return

class Client_Control(threading.Thread):
	def __init__(self, args):
		threading.Thread.__init__(self)
		self.args = args		

	def run(self):
		global ctrl_c
		global packets_sent
		global packets_received
		ctrl_c = False
		port_num = 5678
		protocol_version = 0x01
		test_request = 0x01
		test_done = 0x03
		run_time = self.args.time
		test = self.args.test
		target = self.args.target
		timeout = self.args.time + 10

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

		s_ctrl.settimeout(timeout)

		# Connect to server
		try:
			s_ctrl.connect((self.args.target , port_num))
		except socket.error as msg:
			print("Error: Could not open connection")
			print("Description: " + str(msg))
			sys.exit()
		except socket.timeout:
			print ("Connection to server timed out!")
			return

		if ctrl_c:
			print ("\nExiting client")
			sys.exit()

		# Send request
		try:
			request = struct.pack('!BBB', protocol_version, test_request, self.args.test)
			client_request = s_ctrl.sendall(request)
		except socket.error as msg:
			print("Error: sendall() failed")
			print("Description: " + str(msg))
			sys.exit()
		except socket.timeout:
			print ("Client request timed out!")
			return

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
		except socket.timeout:
			print ("Server reply timed out!")
			return
		
		(protocol_version, test_reply, port_num_data) = struct.unpack('!BBH', server_reply)
		
		# Launch client data thread
		d = Client_Data(run_time, test, target, port_num_data)
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
			print("Error: sendall() failed")
			print("Description: " + str(msg))
			sys.exit()
		except socket.timeout:
			print ("Client done timed out!")
			return

		if ctrl_c:
			print ("\nExiting client")
			sys.exit()

		# Receive results
		try:
			server_results = s_ctrl.recv(4096)
			if len(server_results) != 10:
					print ("Invalid server results!")
					# do something
			if self.args.test == 0x03 or self.args.test == 0x04:
				(protocol_version, test_results, packets_received) = struct.unpack('!BBQ', server_results)
		except socket.error as msg:
			print("Error: unable to recv()")
			print("Description: " + str(msg))
			sys.exit()
		except socket.timeout:
			print ("Server results timed out!")
			return
		
		if ctrl_c:
			print ("\nExiting client")
			sys.exit()	
		
		# TCP stream
		if self.args.test == 0x01:
			mbps = int((packets_sent)/(self.args.time*8388608))
			print ("Bandwidth: %d Mbps" % mbps)
		
		# TCP round robin
		elif self.args.test == 0x02:
			latency = int(packets_received/self.args.time)
			print ("Latency: %d packets/second" % latency)
			
		# UDP stream
		elif self.args.test == 0x03:
			mbps = int((packets_received)/(self.args.time*8388608))
			print ("Bandwidth: %d Mbps" % mbps)
			packet_loss = ((packets_sent-(packets_received*1472))/packets_sent)*100
			print ("Packet loss: %f%%" % packet_loss)
			
		# UDP round robin
		else:
			latency = int(packets_received/self.args.time)
			packet_loss = ((packets_sent-packets_received)/packets_sent)*100
			print ("Latency: %d packets/second" % latency)
			print ("Packet loss: %f%%" % packet_loss)
			
			
				
		# Close thread
		return

class Client_Data(threading.Thread):
	def __init__(self, run_time, test, target, port_num_data):
		threading.Thread.__init__(self)
		self.run_time = run_time
		self.test = test
		self.target = target
		self.port_num_data = port_num_data
	def run(self):
		print ("Data thread opening")
		
		global ctrl_c
		global packets_sent
		global packets_received
		udp_total = 0
		total = 0
		packets_sent = 0
		packets_received = 0
		ctrl_c = False
		
		
		if ctrl_c:
			print ("\nExiting client")
			sys.exit()

		# Create TCP or UDP socket
		try:
			if (self.test == 0x01 or self.test == 0x02):
				s_data = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
			else:
				s_data = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		except socket.error as msg:
			print("Error: could not create socket")
			print("Description: " + str(msg))
			sys.exit()
			
		if (self.test == 0x02):
			s_data.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)
			
		if ctrl_c:
			print ("\nExiting client")
			sys.exit()

		# Connect to server
		if (self.test == 0x01 or self.test == 0x02):
			try:
				s_data.connect((self.target , self.port_num_data))
			except socket.error as msg:
				print("Error: Could not open connection")
				print("Description: " + str(msg))
				sys.exit()

		if ctrl_c:
			print ("\nExiting client")
			sys.exit()
		
		# TCP stream
		if (self.test == 0x01):
			start_time = time.time()
			while ((time.time()-start_time) < self.run_time):
				try:
					tcp_stream = s_data.sendall(bytes(65536))
				except socket.error as msg:
					print("Error: sendall() failed")
					print("Description: " + str(msg))
					sys.exit()
				if ctrl_c:
					print ("\nExiting client")
					sys.exit()
				packets_sent = packets_sent + 65536
		
		# TCP round robin
		elif (self.test == 0x02):
			s_data.settimeout(45)
			start_time = time.time()
			while ((time.time()-start_time) < self.run_time):
				try:
					tcp_rr = s_data.sendall(bytes(1))
				except socket.error as msg:
					print("Error: sendall() failed")
					print("Description: " + str(msg))
					sys.exit()
				try:
					client_data_response = s_data.recv(1)
				except socket.error as msg:
					print("Error: unable to recv()")
					print("Description: " + str(msg))
					sys.exit()
				except socket.timeout:
					s_data.close()
					return					
				if len(client_data_response) > 0:
					packets_received = packets_received + 1
				if ctrl_c:
					print ("\nExiting client")
					sys.exit()
		# UDP stream
		elif (self.test == 0x03):
			start_time = time.time()
			while ((time.time()-start_time) < self.run_time):
				try:
					udp_stream = s_data.sendto(bytes(1472), (self.target, self.port_num_data))
				except socket.error as msg:
					print("Error: sendto() failed")
					print("Description: " + str(msg))
					sys.exit()
				if ctrl_c:
					print ("\nExiting client")
					sys.exit()
				packets_sent = packets_sent + 1472
		
		# UDP round robin
		else:
			start_time = time.time()
			while ((time.time()-start_time) < self.run_time):
				try:
					udp_rr = s_data.sendto(bytes(1), (self.target, self.port_num_data))
					packets_sent = packets_sent + 1
				except socket.error as msg:
					print("Error: sendall() failed")
					print("Description: " + str(msg))
					sys.exit()
				try:
					client_data, addr = s_data.recvfrom(1)
					if len(client_data) > 0:
						packets_received = packets_received + 1
				except socket.error as msg:
					print("Error: unable to recvfrom()")
					print("Description: " + str(msg))
					sys.exit()
				if ctrl_c:
					print ("\nExiting client")
					sys.exit()
								
		if ctrl_c:
			sys.exit()
		print ("Data thread closing")
		# Close thread
		return

def main():
	parser = argparse.ArgumentParser()
	parser.add_argument("--version", action="version", version="Network Tester 2.0", help="show program's version number")
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
		c = Server_Control(args)
		c.start()	
	c.join()

if __name__ == "__main__":
	sys.exit(main())
