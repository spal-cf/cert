
=====================================================
===Nmap===
nmap -sT -sV -A -p- $IP > scan1
nmap -p- --script=vuln $IP > scan2
###HTTP-Methods
nmap --script http-methods --script-args http-methods.url-path='/website' <target>
=====================================================
===WPScan & SSL
wpscan --url $URL --disable-tls-checks --enumerate p --enumerate t --enumerate u -v

===WPScan Brute Forcing
wpscan --url $URL --disable-tls-checks -U users -P /usr/share/wordlists/rockyou.txt -v
=====================================================
===Nikto with SSL and Evasion
nikto --host $IP -ssl -evasion 1
=====================================================
===dns recon
dnsrecon -d domain.com
=====================================================

===gobuster directory
gobuster dir -u $URL -w /usr/share/seclists/Discovery/Web-Content/raft-medium-directories.txt -l -k -t 30

===gobuster files
gobuster dir -u $URL -w /usr/share/seclists/Discovery/Web-Content/raft-medium-files.txt -l -k -t 30

===gobuster for subdomain
gobuster dns -d domain.com -w /usr/share/seclists/Discovery/DNS/subdomains-top1million-110000.txt -t 30

=====================================================
===Extract IPs from text file
grep -o '[0-9]\{1,3\}\.[0-9]\{1,3\}\.[0-9]\{1,3\}\.[0-9]\{1,3\}' file.txt
=====================================================

===Wfuzz Files
wfuzz -c -z file,/usr/share/dirb/wordlists/common.txt --hc 404 https://10.11.1.237/FUZZ
wfuzz -c -z file,/usr/share/seclists/Discovery/Web-Content/raft-medium-files.txt --hc 404 $URL/FUZZ

===Wfuzz directories
wfuzz -c -z file,/usr/share/seclists/Discovery/Web-Content/raft-medium-directories.txt --hc 404 $URL/FUZZ/

===Wfuzz with post data
wfuzz -u http://target-ip/path/index.php?action=authenticate -d 'username=admin&password=FUZZ' -w /usr/share/wordlists/rockyou.txt
============================================================
ps auxww | grep -i root --color=auto


dirb
============
dirb http://10.11.1.133/ -X .php,.asp -o dirb-4.txt



