
# Linux Commands

### man

`man find`

`man -k compression`

`man -k passwd`

`man -k '^passwd$'`

`man 5 passwd`

`apropos compression`

## Finding Files
### locate
`updatedb`

`locate sbd.exe`

### which
`which sbd`

### find
#### All the files in entire FS with sbd in name

`find / -name sbd*`

#### All the files with sbd and identify file format

`find / -name sbd* -exec file {} \;`

identify any file (not directory) modified in the last day, NOT owned by the root user and execute ls -l on them

`sudo find / -type f ! -user root -mtime -1 -print -exec ls -l {} \;`


## Services in Kali

### SSH Service

#### Method 1
  `sudo service ssh start`

  `sudo service ssh stop`

#### Method 2
  `sudo systemctl start ssh`

  `sudo systemctl stop ssh`

#### Verfication
  `sudo netstat -antp | grep sshd`
  `sudo ss -antlp | grep sshd`

#### Enable
  `sudo systemctl enable ssh`


### Apache Service

#### Start and Stop

`sudo systemctl start pache2`
`sudo systemctl stop apache2`

#### Verification

`sudo ss -antlp | grep apache`

#### Enable

`sudo systemctl enable apache2`

To see a table of all available services,

`systemctl list-unit-files`


### Update and Upgrade and Install and Remove

```
sudo apt update

sudo apt upgrade metasploit-framework

apt-cache search pure-ftpd

apt show resource-agents

sudo apt install pure-ftpd

sudo apt remove --purge pure-ftpd

sudo dpkg -i man-db_2.7.0.2-5_amd64.deb
```


### Text Searching and Manipulation

sed
`echo "I need to try hard" | sed 's/hard/harder/'`

AWK
`echo "hello::there::friend" | awk -F "::" '{print $1, $3}'`

```
cat access.log | cut -d " " -f 1 | sort -u

cat access.log | cut -d " " -f 1 | sort | uniq -c | sort -urn

cat access.log | grep '208.68.234.99' | cut -d "\"" -f 2 | uniq -c

cat access.log | grep '208.68.234.99' | grep '/admin ' | sort -u

cat access.log|grep '208.68.234.99'| grep -v '/admin '

cat /etc/passwd | grep false | awk -F":" '{print "The user",$1,"home directory is",$6}'

sudo awk -F ':' '{if($NF=="/bin/false") {printf "The user %s home directory is %s\n", $1, $(NF-1)}}' /etc/passwd

```

#### Compile 32bit code
gcc -Wl,--hash-style=both -m32 -o 9542 9542.c
