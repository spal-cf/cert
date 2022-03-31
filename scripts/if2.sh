#!/bin/bash
# if statement example 2
read -p "What is your age: " age
if test $age -lt 16 
then
    echo "You might need parental permission to take this course!" 
fi
