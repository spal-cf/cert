$domainObj = [System.DirectoryServices.ActiveDirectory.Domain]::GetCurrentDomain() 
$PDC = ($domainObj.PdcRoleOwner).Name
$SearchString = "LDAP://"
$SearchString += $PDC + "/"
$DistinguishedName = "DC=$($domainObj.Name.Replace('.', ',DC='))"
$SearchString += $DistinguishedName
$Searcher = New-Object System.DirectoryServices.DirectorySearcher([ADSI]$SearchString) 
$objDomain = New-Object System.DirectoryServices.DirectoryEntry
$Searcher.SearchRoot = $objDomain
#$Searcher.filter="samAccountType=805306368" 
# $Searcher.filter="name=Jeff_Admin"
# $Searcher.filter="serviceprincipalname=*http*"
$Searcher.filter="serviceprincipalname=*corp.com*"
$Result = $Searcher.FindAll()

Foreach($obj in $Result)
{
    Foreach($prop in $obj.Properties)
    {

        $SPN_initial = $prop.serviceprincipalname
        $SPN = $SPN_initial.split("/")[1].split(":")[0]
        Write-Host ""
        Write-Host "Sam Account Name : [+]" $prop.samaccountname 
        Write-Host "Service Principal Name : [+]" $SPN_initial 

        If ($SPN_initial -like "*.com") {
            nslookup $SPN
        }
    }  
    Write-Host "--------------------------------------------------------"
}
