<HTML>
<HEAD>
<TITLE> Manually Getting Data through a Custom Business Object </TITLE>
</HEAD>

<BODY BACKGROUND="/MSADC/Samples/Addressbook/Arcadia.gif">

<CENTER><H1> Manually Getting Data through <BR> a Custom Business Object </H1></CENTER>

<!--
	Purpose:     To demonstrate using a custom business object
	Written By:  Microsoft Data Access Group, Microsoft Corporation
	Date:        April, 1997
-->
 
<CENTER>
<Table Border=1><TR><TD ALIGN=CENTER ><FONT SIZE=2 Color="#008080">
<B>UnBound TextBox<B></TD><TD ALIGN=CENTER ><FONT SIZE=2 Color="#008080">
<B>Bound Data Grid</B></TD><TR><TD>

<!-- 
	This is included as an example of how you can use data 
	with and unbound control.  If you have the extension FM20.DLL
	on your client machine you can uncomment the associated code.
-->
<!-- Unbound List Box within FM20.DLL, ID=List1 -->
<!--
<OBJECT CLASSID="CLSID:8BD21D20-EC42-11CE-9E0D-00AA006002F3"
	ID="List1"
	WIDTH=108 HEIGHT=100>
</OBJECT>
-->

<TD>

<!--  Sheridan DataBound Grid Control, ID=GRID -->

<Object CLASSID="clsid:AC05DC80-7DF1-11d0-839E-00A024A94B3A"
	CODEBASE="http://<%=Request.ServerVariables("SERVER_NAME")%>/MSADC/Samples/ssdatb32.cab"
	ID=GRID
	datasrc=#ADC
        WIDTH=550 HEIGHT=100>
	<PARAM NAME="AllowAddNew"   VALUE="TRUE">
	<PARAM NAME="AllowDelete"   VALUE="TRUE">
	<PARAM NAME="AllowUpdate"   VALUE="TRUE">
	<PARAM NAME="BackColor"     VALUE="-2147483643">
	<PARAM NAME="BackColorOdd"  VALUE="-2147483643">
	<PARAM NAME="ForeColorEven" VALUE="0">
</OBJECT>

</Table>

<!--  RDS.DataSpace object, ID=ADS  -->
<OBJECT CLASSID="CLSID:BD96C556-65A3-11D0-983A-00C04FC29E36"
	ID="ADS"
	WIDTH=1 HEIGHT=1>
</OBJECT>

<!-- RDS.DataControl object, ID=ADC  -->
<OBJECT classid="clsid:BD96C556-65A3-11D0-983A-00C04FC29E33"
    	ID="ADC"
	HEIGHT=1 WIDTH = 1>
</OBJECT>

<!-- Input Information Area -->
<TABLE BORDER=1>
	<TR><TD WIDTH=150><FONT SIZE=2 Color="#008080"><B>Server:</B> 
	<TD><INPUT SIZE=70 NAME="Server"> 

 	<TR><TD WIDTH=150><FONT SIZE=2 Color="#008080"><B>Connection:</B>
   	<TD><INPUT SIZE=70 NAME="Connect"> 
                                                       
   	<TR><TD WIDTH=150><FONT SIZE=2 Color="#008080"><B>Query:</B>
   	<TD><INPUT SIZE=70 NAME="Query">                                           
</TABLE>
<HR>

<!-- Buttons to select data source and populate visible data controls -->

<INPUT TYPE=BUTTON NAME="BusObjTest" VALUE="Test Business Object">
<INPUT TYPE=BUTTON NAME="Run" VALUE="Run">
<INPUT TYPE=BUTTON NAME="AccessQuery" VALUE="Fill Access Query Info">
<INPUT TYPE=BUTTON NAME="SQLQuery" VALUE="Fill SQL Server Query Info">
</Table>

<!-- Buttons for Navigation in data grid  -->
<HR>
<INPUT TYPE=BUTTON NAME="MoveFirst" VALUE="First">
<INPUT TYPE=BUTTON NAME="MovePrev" VALUE="Previous">
<INPUT TYPE=BUTTON NAME="MoveNext" VALUE="Next">
<INPUT TYPE=BUTTON NAME="MoveLast" VALUE="Last">
<INPUT TYPE=BUTTON NAME="Submit" VALUE="Submit Changes">
<INPUT TYPE=BUTTON NAME="Cancel" VALUE="Cancel Changes">
</CENTER><P>


<SCRIPT LANGUAGE="VBScript">
Option Explicit
'---- enum Values ----
Const adcExecSync = 1
Const adcExecAsync = 2

'---- enum Values ----
Const adcFetchUpFront = 1
Const adcFetchBackground = 2
Const adcFetchAsync = 3

Dim BObj
Dim ADOR

Sub Window_OnLoad
	'Change the asynchronous options such that execution is synchronous
	'and Fetching can occur in the background
	ADC.ExecuteOptions = adcExecSync
	ADC.FetchOptions = adcFetchBackground

	'Populate Data Source and Query text boxes with initial data.
	Server.Value = "http://<%=Request.ServerVariables("SERVER_NAME")%>"
    	Connect.Value = "DSN=AdvWorks"
 	Query.Value = "Select * from Products"

	'Use CreateObject method of ADS to load custom business object
	Set BObj = ADS.CreateObject("VbBusObj.VbBusObjCls", Server.Value)
End Sub

Sub BusObjTest_OnClick
	'Uses function in custom business object for self-test                               
 	 MsgBox BObj.Test()
End Sub

'Populate Query box with Microsoft Access Query.
Sub AccessQuery_OnClick
	Connect.Value = "DSN=AdvWorks"
	Query.Value = "Select * from Products"	
End Sub

'Populate Query box with SQL Server Query.
Sub SQLQuery_OnClick
  	Connect.Value = "DSN=Pubs;UID=SA;PWD=;"
  	Query.Value = "Select * from Authors"
End Sub

'Get data and populate controls
Sub Run_OnClick
	'Get the Recordset
  	Set ADOR = BObj.GetRecordset(Connect.Value,Query.Value)

	'Populate UnBound List Box
	' The following code could be uncommented if you have FM20.DLL
	'List1.Clear		'Clear the list box.
	'While Not ADOR.EOF
  	'  List1.AddItem ADOR(0).Value
	'  ADOR.MoveNext
	'WEnd

	'Populate Bound Data Grid by assigning recordset to the ADC
	Set ADC.SourceRecordset = ADOR
	
	'Optional command specific to the Sheridan Grid to ensure display of the correct data
	Grid.Rebind

End Sub

'Change active Record
Sub MoveFirst_OnClick
	ADC.Recordset.MoveFirst
End Sub

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

Sub MoveLast_OnClick
	ADC.Recordset.MoveLast
End Sub

SUB Submit_OnClick
	'Set properties on the ADC
	ADC.SERVER = Server.Value
	ADC.CONNECT = Connect.Value 
	ADC.SQL = Query.Value
	
	'Send changes to data source via the ADC
	ADC.SubmitChanges

	'Pull fresh data
	ADC.Refresh
	
	'Optional command specific to the Sheridan Grid to ensure display of the correct data
	Grid.Rebind

End Sub

SUB Cancel_OnClick
	'Set properties on the ADC
	ADC.SERVER = Server.Value
	ADC.CONNECT = Connect.Value 
	ADC.SQL = Query.Value
	
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
