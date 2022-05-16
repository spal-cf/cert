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
mountvol

powershell -> driverquery.exe /v /fo csv | ConvertFrom-CSV | Select-Object
‘Display Name’, ‘Start Mode’, Path

Get-WmiObject Win32_PnPSignedDriver | Select-Object DeviceName, DriverVersion, Manufacturer | Where-Object {$_.DeviceName -like "*VMware*"}

reg query HKEY_CURRENT_USER\Software\Policies\Microsoft\Windows\Installer

reg query HKEY_LOCAL_MACHINE\Software\Policies\Microsoft\Windows\Installer


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
mount
cat /etc/fstab
/bin/lsblk
lsmod
/sbin/modinfo libata

find / -perm -u=s -type f 2>/dev/null

```
