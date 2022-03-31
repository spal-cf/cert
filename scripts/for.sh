#!/bin/bash

for ip in $(seq 1 5); do echo 10.11.1.$ip; done
for ip in {6..10}; do echo 10.11.1.$ip; done
