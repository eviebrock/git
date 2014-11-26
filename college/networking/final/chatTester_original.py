#!/usr/bin/env python3

import argparse
import configparser
import socket
import select
import sys
import threading

def main():
    # Setup program configuration (from arguments)
    parser = argparse.ArgumentParser(description='Chat server *tester* for COMP/ECPE 1777')
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



    print("Exiting test program")


if __name__ == "__main__":
    sys.exit(main())
