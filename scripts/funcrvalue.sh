#!/bin/bash
# function return value example
return_me() {
echo "Oh hello there, I'm returning a random value!"
return $RANDOM 
}
return_me
echo "The previous function returned a value of $?"
