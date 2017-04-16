<HTML>
<HEAD>
<TITLE>RDS Sample Query Page</TITLE>
</HEAD>
<BODY BACKGROUND="../Addressbook/Arcadia.gif" BGCOLOR="ffffff" TEXT="000000" LINK="000080" LANGUAGE="VBS" onload = "Init">
<CENTER>
<H1>Remote Data Service Sample Query Page</H1>
<BR>

<!-- Tutorial: Data Bound Grid Control -->

<!-- Tutorial: HTML Controls to Get Recordsets -->

<!-- Tutorial: HTML Controls to Navigate the Recordset and Run the Query -->

<!-- Tutorial: AdvancedDataControl Object -->


<SCRIPT LANGUAGE= "VBScript">
SUB Window_OnLoad
	Server.Value = "http://<%=Request.ServerVariables("SERVER_NAME")%>"
	Connect.Value = "DSN=AdvWorks"
	SQL.Value = "Select * from Products"

	SControl.ExecuteOptions = adcExecSync
	SControl.FetchOptions = adcFetchBackground
	
END SUB


' Tutorial: Move Through the Displayed Recordset 

' Tutorial: Send a Query to the Database 

' Tutorial - Submit Changes to the Database

</SCRIPT>
</BODY>
</HTML>
