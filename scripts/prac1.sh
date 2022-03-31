#!/bin/bash
wget www.megacorpone.com

grep -o '[^/,"]*\.megacorpone\.com' index.html | sort -u > list.txt

for url in $(cat list.txt); do host $url; done | grep "has address" | cut -d " " -f 4 | sort -u
