#!/usr/bin/python3
import socket
import sys
if len(sys.argv) != 2:
    print ("Usage: vrfy.py <file name containing users>")
    sys.exit(0)

users_file = sys.argv[1]

# Create a Socket
s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# Connect to the Server
connect=s.connect(('10.11.1.231',25))
# Receive the banner
banner=s.recv(1024)
print ("Banner: ", banner)
with open(users_file) as ufile:
    for user in ufile:
        print ("User: ", user)
        # VRFY a user
        s.send(('VRFY ' + user.strip() + '\r\n').encode())
        result=s.recv(1024)
        print ("Result: ", result)
# Close the socket
s.close()
