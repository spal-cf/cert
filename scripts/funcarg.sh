#!/bin/bash
# passing arguments to functions

pass_arg() {
echo "Today's random number is: $1" 
}


pass_arg $RANDOM
