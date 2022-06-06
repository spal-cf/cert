#### rinetd

```
/etc/rinetd.conf

# bindadress bindport connectaddress connectport
0.0.0.0     80        142.250.64.100     80

sudo service rinetd restart

ss - antp | grep "80"

```
#### SSH tunneling

##### Local port forwarding

```
ssh -N -L [bind_address:]port:host:hostport [username@address]

sudo ssh -N -L 0.0.0.0:445:192.168.1.110:445 student@10.11.0.128

```
#### samba access over tunnel

```
edit /etc/samba/smb.conf
add following at the end:

# min protocol = SMB2

[global]

client min protocol = NT1
server min protocol = NT1

then save. restart the service.

sudo /etc/init.d/smbd restart

smbclient -L 127.0.0.1 -U Administrator
```

##### Remote port forwarding

```
ssh -N -R [bind_address:]port:host:hostport [username@address]

ssh -N -R 10.11.0.4:2221:127.0.0.1:3306 kali@10.11.0.4

ss -antp | grep "2221"

sudo nmap -sS -sV 127.0.0.1 -p 2221

```

#### SSH tunneling
```
ssh -N -D <address to bind to>:<port to bind to> <username>@<SSH server address>

sudo ssh -N -D 127.0.0.1:8080 student@10.11.0.128

```

#### PLINK.EXE - Remote port forward

```
plink.exe -ssh -l kali -pw ilak -R 10.11.0.4:1234:127.0.0.1:3306 10.11.0.4

cmd.exe /c echo y | C:\Tools\port_redirection_and_tunneling\plink.exe -ssh -l kali -pw ilak -R 10.11.0.4:1234:127.0.0.1:3306 10.11.0.4


```
 
#### NETSH - Local port forward

Forwarding traffic on port 4455 on windows 10 to port 445 on windows 16


```
netsh interface portproxy add v4tov4 listenport=4455 listenaddress=10.11.0.22 connectport=445 connectaddress=192.168.1.110

```

allow inbound traffic on port 4455

```
netsh advfirewall firewall add rule name="forward_port_rule" protocol=TCP dir=in localip=10.11.0.22 localport=4455 action=allow

```
In /etc/samba/smb.conf add following line

```
min protocol = SMB2
```

sudo /etc/init.d/smbd restart

From kali:

```
smbclient -L 10.11.0.22 --port=4455 --user=Administrator

sudo mkdir /mnt/win10_share
sudo mount -t cifs -o port=4455 //10.11.0.22/Data -o username=Administrator,password=Qwerty09! /mnt/win10_share

ls -l /mnt/win10_share/
```

#### HTTP Tunnel

Local port forward from linux client to windows 2016 server in internal network

Executing on linux client
```
ssh -L 0.0.0.0:8888:172.16.175.5:3389 student@127.0.0.1

ss -antp | grep "8888"

hts --forward-port localhost:8888 1234

ps aux | grep hts

ss -antp | grep "1234"
```

Executing on kali

```
htc --forward-port 8080 192.168.175.44:1234 

ps aux | hrep htc

ss -antp | grep "8080"
```

