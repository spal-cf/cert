### Windows
```
whoami
net user student
net user
hostname
systeminfo | findstr /B /C:"OS Name" /C:"OS Version" /C:"System Type"
tasklist /SVC
ipconfig /all
route -print
netstat -ano
netsh advfirewall show currentprofile
netsh advfirewall firewall show rule name=all
schtasks /query /fo LIST /v
wmic product get name, version, vendor
wmic qfe get Caption, Description, HotFixID, InstalledOn
accesschk.exe -uws "Everyone" "C:\Program Files"
Get-ChildItem "C:\Program Files" - Recurse | Get-ACL | ?{$_.AccessToString -match "Everyone\sAllow\s\sModify"}
find / -writable -type d 2>/dev/null

```

### Linux
```
whoami
id
cat /etc/passwd
cat /etc/issue
cat /etc/*-release
uname -a
ps aux
ip a
/sbin/route
ss -anp
iptables
iptables-save
iptables-restore
ls -lah /etc/cron*
cat /etc/crontab
dpkg -l

```
