<HTML>
<HEAD>
<TITLE> Automatically Getting Data through the DataControl </TITLE>
</HEAD>

<BODY BACKGROUND="/MSADC/Samples/Addressbook/Arcadia.gif">

<CENTER><H1> Automatically Getting Data through <BR> the Data Control </H1></CENTER>

<!--
	Purpose:     To demonstrate the default query scenario calling the ADC to populate a bound control.
	Written By:  Microsoft Data Access Group, Microsoft Corporation
	Date:        April, 1997
-->

<CENTER>
<Table Border=1><TR><TD ALIGN=CENTER ><FONT SIZE=2 Color="#008080">
<B>Bound Data Grid</B></TD><TR
><TD>

<!--  Sheridan DataBound Grid Control, ID=GRID -->

<OBJECT CLASSID="CLSID:AC05DC80-7DF1-11d0-839E-00A024A94B3A"
	CODEBASE="http://<%=Request.ServerVariables("SERVER_NAME")%>/MSADC/Samples/ssdatb32.cab"
	ID="GRID"
	datasrc="#ADC"
	WIDTH=600 HEIGHT=150>
        <PARAM NAME="AllowAddNew"   VALUE="TRUE">
	<PARAM NAME="AllowDelete"   VALUE="TRUE">
	<PARAM NAME="AllowUpdate"   VALUE="TRUE">	
	<PARAM NAME="_Version"	    VALUE="131072">
	<PARAM NAME="BackColor"     VALUE="-2147483643">
	<PARAM NAME="BackColorOdd"  VALUE="-2147483643">
	<PARAM NAME="ForeColorEven" VALUE="0">
</OBJECT>
</Table>

<!-- Input Information Area -->
<table>
<tr><td>Server:<td><INPUT NAME="Server" SIZE=70>
<tr><td>Connection:<td><INPUT NAME="Connect" SIZE=70>
<tr><td>Query:<td><INPUT NAME="Query" SIZE=70>
</table>

<!-- Buttons to select data source and populate visible data controls -->

<INPUT TYPE=BUTTON NAME="Run" VALUE="Run">
<INPUT TYPE=BUTTON NAME="AccessQuery" VALUE="Fill Access Query Info">
<INPUT TYPE=BUTTON NAME="SQLQuery" VALUE="Fill SQL Server Query Info">
<HR>
<INPUT TYPE=BUTTON NAME="MoveFirst" VALUE="First">
<INPUT TYPE=BUTTON NAME="MovePrev" VALUE="Previous">
<INPUT TYPE=BUTTON NAME="MoveNext" VALUE="Next">
<INPUT TYPE=BUTTON NAME="MoveLast" VALUE="Last">
<INPUT TYPE=BUTTON NAME="Submit" VALUE="Submit Changes">
<INPUT TYPE=BUTTON NAME="Cancel" VALUE="Cancel Changes">
</CENTER>

<!- RDS.Data Control ID ADC->
<OBJECT classid="clsid:BD96C556-65A3-11D0-983A-00C04FC29E33"
	ID=ADC 
	HEIGHT=1 WIDTH=1>
</OBJECT>

<SCRIPT LANGUAGE="VBScript">
Option Explicit
'---- enum Values ----
Const adcExecSync = 1
Const adcExecAsync = 2

'---- enum Values ----
Const adcFetchUpFront = 1
Const adcFetchBackground = 2
Const adcFetchAsync = 3

'Populate Data Source and Query text boxes with initial data.
SUB Window_OnLoad
	'Change the asynchronous options such that execution is synchronous
	'and Fetching can occur in the background
	ADC.ExecuteOptions = adcExecSync
	ADC.FetchOptions = adcFetchBackground

	Server.Value = "http://<%=Request.ServerVariables("SERVER_NAME")%>"
   	Connect.Value = "DSN=AdvWorks"
   	Query.Value = "Select * from Products"
End Sub

'Populate Query box with Microsoft Access Query.
SUB AccessQuery_OnClick
   	Connect.Value = "DSN=AdvWorks"
   	Query.Value = "Select * from Products"
End Sub

'Populate Query box with SQL Server Query.
SUB SQLQuery_OnClick
   	Connect.Value = "DSN=pubs;uid=sa;pwd=;"
   	Query.Value = "Select * from Authors"
End Sub

SUB Run_OnClick
	'Set the connection properties on the ADC object

	ADC.Server = Server.Value
    	ADC.Connect = Connect.Value
    	ADC.SQL = Query.Value

	'Get the data specified
        ADC.Refresh		

  	'Optional command specific to the Sheridan Grid to ensure display of the correct data
	Grid.Rebind

End Sub

'Change active Record
SUB MoveFirst_OnClick
	ADC.Recordset.MoveFirst
END SUB

SUB MoveNext_OnClick
On Error Resume Next
	ADC.Recordset.MoveNext
	IF ERR.Number <> 0 THEN
		ADC.Recordset.MoveLast  'If already at end of recordset stay at end.
	END IF
END SUB

SUB MovePrev_OnClick
	On Error Resume Next
	ADC.Recordset.MovePrevious
	IF ERR.Number <> 0 THEN
		ADC.Recordset.MoveFirst  'If already at start of recordset stay at top.
	END IF
END SUB

SUB MoveLast_OnClick
	ADC.Recordset.MoveLast
END SUB


SUB Submit_OnClick
	'Send changes to data source
	ADC.SubmitChanges

	'Pull fresh data
	ADC.Refresh
	
	'Optional command specific to the Sheridan Grid to ensure display of the correct data
	Grid.Rebind

End Sub

SUB Cancel_OnClick
	'Cancel the changes made to the data and resore
	ADC.CancelUpdate
	'Pull fresh data
	ADC.Refresh

	'Optional command specific to the Sheridan Grid to ensure display of the correct data
	Grid.Rebind
End Sub

</SCRIPT>

<!-- Link to View Source -->

<TABLE BORDER=3><TR><TD><!--#include file="srcform.inc"--></TABLE>
<Center>This site powered by the Microsoft Data Access Components.</Center>

</BODY>
</HTML>
