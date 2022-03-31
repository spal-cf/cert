#!/bin/bash
# while loop example 2
counter=1
while [ $counter -le 10 ] 
do
    echo "10.11.1.$counter"
    ((counter++)) 
done
