echo $domainObj = [System.DirectoryServices.ActiveDirectory.Domain]::GetCurrentDomain() > ldp.ps1 
echo $PDC = ($domainObj.PdcRoleOwner).Name >> ldp.ps1
echo $SearchString = "LDAP://" >> ldp.ps1
echo $SearchString += $PDC + "/" >> ldp.ps1
echo $DistinguishedName = "DC=$($domainObj.Name.Replace('.', ',DC='))" >> ldp.ps1
echo $SearchString += $DistinguishedName >> ldp.ps1
echo $SearchString >> ldp.ps1
echo $Searcher = New-Object System.DirectoryServices.DirectorySearcher([ADSI]$SearchString) >> ldp.ps1
echo $objDomain = New-Object System.DirectoryServices.DirectoryEntry >> ldp.ps1
echo $Searcher.SearchRoot = $objDomain >> ldp.ps1
echo $Searcher.filter="samAccountType=805306368" >> ldp.ps1
echo $Searcher.FindAll() >> ldp.ps1
