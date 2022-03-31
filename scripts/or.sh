#!/bin/bash

# or example
if [ $USER == 'kali' ] || [ $HOSTNAME == 'pwn' ] 
then
    echo "One condition is true, this line is printed" 
else
    echo "You are out of luck!" 
fi
