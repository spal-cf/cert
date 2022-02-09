echo $domainObj = [System.DirectoryServices.ActiveDirectory.Domain]::GetCurrentDomain() > ldp2.ps1
echo $PDC = ($domainObj.PdcRoleOwner).Name >> ldp2.ps1
echo $SearchString = "LDAP://" >> ldp2.ps1
echo $SearchString += $PDC + "/" >> ldp2.ps1
echo $DistinguishedName = "DC=$($domainObj.Name.Replace('.', ',DC='))" >> ldp2.ps1
echo $SearchString += $DistinguishedName >> ldp2.ps1
echo $Searcher = New-Object System.DirectoryServices.DirectorySearcher([ADSI]$SearchString) >> ldp2.ps1
echo $objDomain = New-Object System.DirectoryServices.DirectoryEntry >> ldp2.ps1
echo $Searcher.SearchRoot = $objDomain >> ldp2.ps1
echo $Searcher.filter="serviceprincipalname=*sql*" >> ldp2.ps1
echo $Result = $Searcher.FindAll() >> ldp2.ps1
echo Foreach($obj in $Result) >> ldp2.ps1
echo { >> ldp2.ps1
echo     Foreach($prop in $obj.Properties) >> ldp2.ps1
echo     { >> ldp2.ps1
echo         $prop >> ldp2.ps1
echo     } >> ldp2.ps1
echo } >> ldp2.ps1