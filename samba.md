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

