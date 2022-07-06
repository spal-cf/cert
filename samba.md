# SAMBA

## How do I recursively download a directory using smbclient?

```
smbclient \\\\10.11.1.231\\home
mask ""
recurse ON
prompt OFF
cd 'path\to\remote\dir'
lcd '~/path/to/download/to/'
mget *

```
### SMBMAP

`smbmap -u '' -p ''  -H 10.11.1.231 -R  'home'`

```
smbmap -H 10.10.10.100    # null session
smbmap -H 10.10.10.100 -R # recursive listing
smbmap -H 10.10.10.100 -d active.htb -u SVC_TGS -p GPPstillStandingStrong2k18

```

smbget -R smb://fileserver/directory


