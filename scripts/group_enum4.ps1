$domainObj = [System.DirectoryServices.ActiveDirectory.Domain]::GetCurrentDomain()
$PDC = ($domainObj.PdcRoleOwner).Name
$SearchString = "LDAP://"
$SearchString += $PDC + "/"
$DistinguishedName = "DC=$($domainObj.Name.Replace('.', ',DC='))"
$SearchString += $DistinguishedName
$Searcher = New-Object System.DirectoryServices.DirectorySearcher([ADSI]$SearchString)
$objDomain = New-Object System.DirectoryServices.DirectoryEntry
$Searcher.SearchRoot = $objDomain
$Searcher.filter="(objectClass=Group)"
$Result1 = $Searcher.FindAll()
Foreach($obj in $Result1)
{

	$Result2 = $obj.Properties.name
	Foreach($obj2 in $Result2)
	{
		#$String = "`r`n"
		#$String
		$obj2
		$Searcher.filter="(name=$obj2)"
		$Result3 = $Searcher.FindAll()
		Foreach($obj3 in $Result3)
		{
			$obj3.Properties.member
		}	
		Write-Host "------------------------"
	}
}
