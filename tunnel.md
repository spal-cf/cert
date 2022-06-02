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
