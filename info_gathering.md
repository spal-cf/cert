# Info Gathering
The more info we have, the more likely of success

## Passive Info Gathering
* 1st phase of pentesting
* Consists of using publicly available information

### Target servers/websites

* How well is the website designed?
* How clean is the code?

### Google Search

* All the sites
`site:"example.com"`

* Remove any related to www
`site:"example.com" -site:"www.example.com"`

* Search for pdf file in site bayshorenetworks.com, excluding any related to www
`site:"bayshorenetworks.com"  -site:"www.bayshorenetworks.com" filetype:pdf`

* Search for Powerpoint files with exact term
`site:"example.com" filetype:ppt "penetation testing"`

`site:"bayshorenetworks.com"  -site:"www.bayshorenetworks.com" filetype:pdf penetration testing`

### Google Hacking
* Single out specific pages with this in title
`intitle:"VNC viewer for Java"`

* Example - Webcam
`inurl:"/control/userimage.html"`

* Specific host authentication signature - PHP
`inurl:php? intext:CHARACTER_SETS,COLLATIONS intitle:phpmyadmin`

* Searching for compromised machines for known PHP vuln
`intitle:"-N3t" filetype:php undetectable`

### GHDB "Google Hacking Database"
http://www.exploit-db.com/google-dorks/

### Email Harvesting

`theharvester -d cisco.com -b google >google.txt`
`theharvester -d cisco.com -l 10 -b bing >bing.txt`

## Active Info Gathering

### DNS Enumeration

* Discover nameservers for a domain

`host -t ns magacorpone.com`

* Discover mail servers for a domain

`host -t mx megacorpone.com`

* Find IP address for server

`host www.megacorpone.com`

### Forward DNS Lookup
Determine IPs of hostnames
* Common host names
  * www, ftp, mail, owa, proxy,router, admin, www2, firewall, mx, pop3

forward.sh
```bash
#!/bin/bash

for name in $(cat list.txt); do
  host $name.megacorpone.com | grep "has address" | cut -d" " -f1,4
done
```

### Reverse DNS Lookup

Try to get hostnames for list of IPs

reverse.sh
```bash
#!/bin/bash

for ip in $(seq 72 91); do
  host 38.100.193.$ip | grep "megacorp" | cut -d" " -f1,5
done
```

### DNS Zone Transfers

DNS zone transfer, also sometimes known by the inducing DNS query type AXFR, is a type of DNS transaction. It is one of the many mechanisms available for administrators to replicate DNS databases across a set of DNS servers.

A zone transfer uses the Transmission Control Protocol (TCP) for transport, and takes the form of a client–server transaction. The client requesting a zone transfer may be a slave server or secondary server, requesting data from a master server, sometimes called a primary server. The portion of the database that is replicated is a zone.

The data contained in a DNS zone may be sensitive from an operational security aspect. This is because information such as server hostnames may become public knowledge, which can be used to discover information about an organization and even provide a larger attack surface.

* Basically, anyone asking for a copy can get one

`host -t ns megacorpone.com`
* To get a list of DNS servers

`host -l megacorpone.com ns1.megacorpone.com`

* If fail, will say "Transfer failed"
* If success, will provide ip/hostname of all related hosts

`host -t ns megacorpone.com | cut -d" " -f4`
* parse just the DNS hostnames

`for server in $(host -t ns megacorpone.com | cut -d" " -f4); do host -l megacorpone.com $server; done`

axfr.sh

```bash
#!/bin/bash
# Simple Zone Transfer Bash Script
# $1 is the first argument given after the bash Script
# Check if argument was given, if not, print usage

if [ -z "$1" ]; then
  echo "[*] Simple Zone transfer script"
  echo "[*] Usage    : $0 <domain name> "
  exit 0
fi

# If argument was given, identify the DNS servers for the domain.
# For each of these servers, attempt a zone transfer

for server in $(host -t ns $1 | cut -d" " -f4); do
  host -l $1 $server | grep "has address"
done
```

#### Additional tools

##### dnsenum

`dnsenum --dnsserver 8.8.4.4 --enum -f list.txt --noreverse --subfile out.txt megacorpone.com`
`dnsenum zonetransfer.me`

##### dnsrecon

`dnsrecon -d megacorpone.com -n 8.8.4.4 -t std -a --xml recon.xml`
`dnsrecon -d megacorpone.com -t axfr`
`dnsrecon -d megacorpone.com -D ~/list.txt -t brt`

### Port Scanning

#### TCP Connect Scan
* relives on 3-way TCP handshake mechanism

In Wireshark,
1. Pick capture interface
2. Capture filter: `host $IP`
3. Disable Name Resolution on MAC and transport name fields
4. Using netcat, `nc -nvv -w 1 -z $IP $PORT_RANGE`

SYN > RST = connection refused/closed
SYN, SYN ACK, FIN = open port

#### SYN Scanning
* Involves sending SYN packets without sending FIN
* Often bypasses firewalls
  * no longer that effective

#### UDP Scanning
* stateless

For UDP ports, use -u with netcat
`nc -unvv -w 1 -z $IP $PORT_RANGE`
* If closed, ICMP unreachable message is sent back. ICMP messages might be blocked by firewall. So udp scan not very reliable.
* If open, nothing is sent back

#### Network Implication
* Be aware of type and amount of traffic generated in Network Scanning

### Nmap

`nmap -h` Help page

/usr/share/nmap-services - contains port names/transport protocols and probability
### masscan

`sudo masscan -p80 10.11.1.0/24 --rate=1000 -e tap0 --router-ip 10.11.0.1
`
#### Traffic Accountability

iptables-counters.sh
```bash
#!/bin/bash

# reset all counters and iptables rules
iptables -Z && iptables -F
# measure incoming traffic to some ip
iptables -I INPUT 1 -s $SOME_IP -j ACCEPT
# measure outgoing traffic to some ip
iptables -I OUTPUT -d $SOME_IP -j ACCEPT
```

1. Run the iptables-counters.sh
2. `nmap $SOME_IP`
* by default, will run tcp syn scan
3. `iptables -vn -L`
* will reveal the amount of traffic generated

#### Network sweeping
ICMP sweep

`nmap -sn $IP_RANGE`

-o to create a grep-able output to a file

`nmap -sn $IP_RANGE -oG ping-sweep-nmap`

Specify a port

`nmap -p 80 $IP_RANGE -oG port80open`

TCP Connect Scan for 20 most common ports

`nmap -sT --top-ports 20 $IP_RANGE -oG top-port-sweep.txt`

#### Nmap OS Discovery and Banner Enumeration

Banner grabbing
* enumerated service versions

`nmap -A $IP`

#### Nmap NSE Scripts
* Nmap scripting engine
/usr/share/nmap/scripts

#### Nmap script help
`nmap --script-help dns-zone-transfer`
`sudo nmap --script vuln 10.11.1.10`

### SMB Enumeration

Only display results with open SMB ports

`nmap -p 139,445 $IP_RANGE --open`

`nmap -v -p 139, 445 --script=smb-os-discovery 10.11.1.227`

`nmap -v -p 139,445 --script=smb-vuln-ms08-067 --script-args=unsafe=1 10.11.1.5`

#### nbtscan

`nbtscan $IP_RANGE`
* can list logged in users and hostnames

#### SMB Null sessions
* to allow unauthenticated users to find out info about the machines
* Windows XP, NT, 2000 has it on by default



`rpcclient -U "" $IP`
* Explore a remote smb service with an empty username/password

`rpcclient $> srvinfo`
* Allows further info on Windows version


`rpcclient $> enumdomusers`
* Get a list of users


`rpcclient $> getdompwinfo`
* Get password info (not the password)

#### enum4linux
* runs various smb enumeration procedures

`enum4linux -v $IP`
* full list of usernames, shares, policies, and more

#### Nmap SMB NSE scripts

`ls -l /usr/share/nmap/scripts/ | grep smb`

`nmap -p 139,445 --script smb-enum-users $IP`
* enumerated SMB usernames

`nmap -p 139,445 --script smb-check-vulns --script-args=unsafe=1 $IP`
* checks for vulns

### SMTP enumeration
* under certain misconfigurations, info can be gathered
* VRFY & EXPN
  * divulge info on users

`nc -nv $IP 25`
* replies with a Banner
`VRFY bob`
* will return 250 if user is on system, otherwise of 550

#### VRFY script
1. create a list of users
2. `for user in $(cat users.txt); do echo VRFY $user | nc -nv -w 1 $IP 25 2>/dev/null | grep ^"250"; done`

##### Python port of VRFY script
vrfy.py
```python
#!/usr/bin/python

import socket
import sys

if len(sys.argv) != 2:
  print "Usage: vrfy.py <username>"
  sys.exit(0)

s=socket.socket(socket.AF_INET, socket.SOCK_STREAM) # Create a Socket
connect=s.connect(('$IP', 25)) # Connect to the server
banner=s.recv(1024) # Receive the banner
print banner
s.send('VRFY ' + sys.argv[1] + '\r\n') # VRFY a user
result=s.recv(1024)
print result
s.close() # Close the socket
```

### SNMP Enumeration
* based on UDP
  * susceptible to ICMP

#### SNMP MiB
* port 161


`nmap -sU --open -p 161 $IP_RANGE --open`
* -U scans UDP

onesixtyone

`onesixty one -c COMMUNITY_STRINGS.txt -i IPs.txt`

#### SNMPWalk
* need community string

`snmpwalk -c public -v1 $IP`
* too much info

`snmpwalk -c public -v1 $IP 1.3.6.1.2.1.25.4.2.1.2`
* searches for running programs (see community string specified)

#### Enumerating Windows Users

`snmpwalk -c public -v1 10.11.1.14 1.3.6.1.4.1.77.1.2.25`

#### Enumerating Running Windows Processes

`snmpwalk -c public -v1 10.11.1.73 1.3.6.1.2.1.25.4.2.1.2`

#### Enumerating Open TCP Ports

`snmpwalk -c public -v1 10.11.1.14 1.3.6.1.2.1.6.13.1.3`

#### Enumerating Installed Software

`snmpwalk -c public -v1 10.11.1.50 1.3.6.1.2.1.25.6.3.1.2`


#### Other snmp tools
* snmpenum
* snmp-check

### NFS Enumeration

Scan NFS shares

`nmap -v -p 111 10.11.1.1-254`

`nmap -sV -p 111 --script=rpcinfo 10.11.1.1-254`

```
kali@kali:~$ mkdir home
kali@kali:~$ sudo mount -o nolock 10.11.1.72:/home ~/home/
kali@kali:~$ cd home/ && ls 
jenny joe45 john marcus ryuu

sudo adduser pwn

sudo sed -i -e 's/1001/1014/g' /etc/passwd

```
