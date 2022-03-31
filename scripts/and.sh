#!/bin/bash 
# and example

if [ $USER == 'kali' ] && [ $HOSTNAME == 'kali' ] 
then
    echo "Multiple statements are true!" 
else
    echo "Not much to see here..." 
fi

user2=$(whoami)
grep $user2 /etc/passwd && echo "$user2 found!" || echo "$user2 not found!"

