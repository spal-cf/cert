#! /usr/bin/python3

import re
import string

found = []
filename = "access_log.txt"
pattern = re.compile("[^/]*\.js", re.IGNORECASE)
with open(filename, "rt") as myfile:
    for line in myfile:
        finds = re.findall(pattern, line)
        for find in finds:
            if find not in found:
                found.append(find)

for find in sorted(found):
    print(find)
