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

