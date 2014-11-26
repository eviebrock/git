#!/usr/bin/python3

# Usage:
#  ./download.py <URL-TO-DOWNLOAD>
#
# Example URLs:
#  http://www.google.com/images/srpr/logo3w.png
#  http://imgsrc.hubblesite.org/hu/db/images/hs-2006-01-a-800_wallpaper.jpg
#  http://www.hdscreenwallpapers.com/download/rockets-nasa-apollo-1280x800.jpg
#  http://imgsrc.hubblesite.org/hu/db/images/hs-2010-13-a-2560x1024_wallpaper.jpg
#  http://ut-images.s3.amazonaws.com/wp-content/uploads/2009/09/SED_wall_1920x1200.jpg

import string
import socket
import sys
import os
from subprocess import call
from urllib.parse import urlparse

# Size of receive buffer.
# Maximum number of bytes to get from network in one recv() call
max_recv = 64*1024

# ******************************************
# STUDENT WORK:
#  (1) Test input arguments to program - correct number provided?
#      Tip: http://www.tutorialspoint.com/python/python_command_line_arguments.htm
#      Exit if the required URL is not provided.
#  (2) Split URL into "host", "path", and "filename" variables.
#      http://www.google.com/images/srpr/logo3w.png
#      * host=www.google.com
#      * path=/images/srpr
#      * file=logo3w.png
#      Tip: Look into urlparse() in Python: 
#           http://docs.python.org/3.1/library/urllib.parse.html
#      Tip: Look into basename() and dirname() in Python
#           http://docs.python.org/3.3/library/os.path.html
#  (3) Provide a "port" variable with the correct HTTP port
#       (integer number, not a string)
# ******************************************

# Test input arguments to program
if len(sys.argv) != 2:
	sys.exit()

# Split URL into "host", "path", and "filename" variables.
o = urlparse(sys.argv[1])
host = o.netloc
path = os.path.dirname(o.path)
filename = os.path.basename(o.path)

# Provide a "port" variable with the correct HTTP port
port = 80

# *****************************
# END OF STUDENT WORK
# *****************************

print("Preparing to download object from http://", host + path + filename)
print()

# *****************************
# STUDENT WORK: 
#  (4) Build the HTTP request string in the variable "full_request".
#      This is client request to the server.
#      Requirements:
#        HTTP 1.1
#        Use the Host header
#        Request the connection be closed after response sent.
#
#      Many ways in python to concatenate strings:
#       http://www.skymind.com/~ocrow/python_string/
#
#      Tip: What is the important sequence of characters that
#      must be provided at the end of the HTTP client request
#      to the server? (otherwise, the server won't begin processing)
# *****************************

get = "GET "
http = " HTTP/1.1\nHost: "
slash = "/"
connect = "\nConnection: close"
car_ret = "\n\n"

full_request = get + path + slash + filename + http + host + connect + car_ret

# *****************************
# END OF STUDENT WORK
# *****************************

print("Connecting to", host + ", port " + str(port))
print("Request to send to server:")
print("-------------------")
print(full_request)
print("-------------------")

# Connect to remote host
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((host,port))

# Send request to remote host
# The sendALL function ensures that *all* bytes of
# the request are sent, even if it takes multiple attempts.
# Since Python strings are unicode, we have to convert them
# to raw ASCII bytes before giving them to the socket.
s.sendall(bytes(full_request,'ascii'))

# Receive *everything* the remote host sends us, even if it
# takes several calls to receive in chunks of up to 64kB. 
# The connection:close in the HTTP request asks the server 
# to close the connection  after sending the full file. 
# Otherwise, this will hang.
#
# WARNING: This implementation concatenates the server 
# response into one huge string in memory. This is a LAZY
# approach that will fail if, for example, we use this program
# to download a 10GB file from the server. A better approach
# would be to download a chunk of data (say, 64kB), save it to disk,
# and repeat. 
print("Receiving response from server")
response = s.recv(max_recv)
full_response = response
print("Got", len(response), 'bytes from recv()')  # How many bytes did we get?

# Loop until we get 0 bytes from recv(), indicating server sent
# the entire object and then closed the socket when finished
while len(response) != 0:
    response = s.recv(max_recv)
    full_response = full_response + response
    print("Got", len(response), 'bytes from recv()')  # How many bytes did we get?

# Close socket - done with network
s.close()

# Split the response into two parts:
# 1.) The part before the \r\n\r\n sequence - the HEADER
# 2.) The part after the \r\n\r\n sequence - the DATA
# Note that, because we are splitting a "byte array",
# we need the search item to also be a byte array,
(header,data) = full_response.split(bytes("\r\n\r\n",'ascii'), 1)

# Convert the header from a byte array (that happens
# to be a string) to a native python string
header = header.decode('ascii')

print("Header from server (omitting data):")
print("-------------------")
print(header)
print("-------------------")

# DON'T print the data! It is binary - not human readable!
#print "Data: " + data

# *****************************
# STUDENT WORK: 
#  (5) Create a "saved_filename" variable that has the
#      path/filename on disk to save the file. 
#      /tmp/<filename> would be perfect for this.
#  (6) Open a binary file for writing
#  (7) Save the data to disk
#      (You only want the data, *not* the headers from the web server)
#  (8) Close the file
# *****************************

saved_filename = "/tmp/" + filename
print (saved_filename)
fo = open(saved_filename, "w+b")
fo.write(data)
fo.close()

# *****************************
# END OF STUDENT WORK
# *****************************

# Assuming you downloaded an image, display image on screen
call(["eog", saved_filename])
