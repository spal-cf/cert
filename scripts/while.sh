#!/bin/bash
# while loop example
counter=1
while [ $counter -lt 10 ] 
do
    echo "10.11.1.$counter"
    ((counter++)) 
done

