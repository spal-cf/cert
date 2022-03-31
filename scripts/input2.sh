#!/bin/bash
# Prompt the user for credentials
read -p 'Username: ' username 
read -sp 'Password: ' password
echo "Thanks, your creds are as follows: " $username " and " $password 
