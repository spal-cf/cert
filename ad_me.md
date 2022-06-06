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
