<HTML>
<HEAD>
<TITLE>Corporate Address Book</TITLE>
</HEAD>

<!--
	Purpose:	To provide a company directory search service for Web users.
	Written By:	Microsoft Data Access Group, Microsoft Corp.
	Date:		May, 1997
-->

<BODY BACKGROUND="Arcadia.gif" LANGUAGE="VBScript" >
<tr>
	<td align="center" width="40%">
        <table border="2" cellpadding="7" cellspacing="7">
            <tr>
                <td width="100%"><font color="#160B5A"><font
                size="4"><strong>Arcadia Bay Corporate Phone Directory</strong></font></font></td>
            </tr>
        </table>
        </td>
</tr>

<hr>
<h2><font color = "#160B5A">Search Parameters</h2>
<h5><font color = "#160B5A">Please enter one or more search patterns and press FIND to search.</h5>

<FONT COLOR = "#160B5A"><B>

<PRE> First Name     <INPUT NAME=SFirst SIZE=30> </PRE>

<PRE> Last Name      <INPUT NAME=SLast  SIZE=30> </PRE>

<PRE> Title          <INPUT NAME=STitle SIZE=30> </PRE>

<PRE> E-mail Alias   <INPUT NAME=SEmail SIZE=30> </PRE>

<!-- 
	Command button options:
	-----------------------
	Find		Submit a search request to the database.
	Clear		Clear the QBE fields (labor saving function only).
	Update Profile	Send updated "address profile" back to the database.
	Cancel Changes	Undo all changes since the last Update Profile.
-->

<INPUT TYPE=BUTTON NAME="Find" 		VALUE="Find">
<INPUT TYPE=BUTTON NAME="Clear" 	VALUE="Clear">
<INPUT TYPE=BUTTON NAME="Update" 	VALUE="Update Profile">
<INPUT TYPE=BUTTON NAME="Cancel" 	VALUE="Cancel Changes">

<hr>
<h2><font color = "#400040">Search Results</h2>
</B>
<br>

<!-- 
	This Sheridan DataGrid control (SGrid) are initialized to
	allow changes to the data - these changes will be saved
	to the database when the Update Profile button is pressed. 
-->

<Object CLASSID="clsid:AC05DC80-7DF1-11d0-839E-00A024A94B3A"
	CODEBASE="http://<%=Request.ServerVariables("SERVER_NAME")%>/MSADC/Samples/ssdatb32.cab"
	ID=GRID1 
        datasrc=#SControl 
        HEIGHT=125 
        WIDTH=495>
	<PARAM NAME="AllowAddNew"   VALUE="TRUE">
	<PARAM NAME="AllowDelete"   VALUE="TRUE">
	<PARAM NAME="AllowUpdate"   VALUE="TRUE">
	<PARAM NAME="BackColor"     VALUE="-2147483643">
	<PARAM NAME="BackColorOdd"  VALUE="-2147483643">
	<PARAM NAME="ForeColorEven" VALUE="0">
</OBJECT>

<br>
<br>
<INPUT TYPE=BUTTON NAME="First" 	VALUE="First">
<INPUT TYPE=BUTTON NAME="Prev" 		VALUE="Previous">
<INPUT TYPE=BUTTON NAME="Next"		VALUE="Next">
<INPUT TYPE=BUTTON NAME="Last"		VALUE="Last">
<hr>


<!-- Non-visual controls - AdvancedDataControl -->

<OBJECT classid="clsid:BD96C556-65A3-11D0-983A-00C04FC29E33"
	ID=SControl
	WIDTH=1 HEIGHT=1>
	<PARAM NAME="SERVER" VALUE="http://<%=Request.ServerVariables("SERVER_NAME")%>">
	<PARAM NAME="CONNECT" VALUE="dsn=ADCDemo;UID=ADCDemo;PWD=ADCDemo;">
</OBJECT>


<!-- VBS scripting for composing queries, updating profiles, and retrieving search results. -->

<SCRIPT LANGUAGE="VBScript">
'---- enum Values ----
Const adcExecSync = 1
Const adcExecAsync = 2

'---- enum Values ----
Const adcFetchUpFront = 1
Const adcFetchBackground = 2
Const adcFetchAsync = 3

Dim myQuery

SUB Window_OnLoad
	'Chnage the asynchronous options such that execution is synchronous
	'and Fetching can occur in the background
	SControl.ExecuteOptions = adcExecSync
	SControl.FetchOptions = adcFetchBackground
	
	Grid1.CAPTION = "Arcadia Bay Corporate Phone Directory"

	'Initialize data grid with column names only.
	SControl.SQL = "Select FirstName, LastName, Title, Email, Building, Room, Phone from Employee where 2 < 1"
	SControl.Refresh

END SUB

'Implement "Clear" button - clears all of the QBE fields in preparation for a new "Find."

SUB Clear_OnClick
	SFirst.Value=""
	SLast.Value=""
	STitle.Value=""
	SEmail.Value=""
END SUB


'Implement "Find" button - composes a dynamic SQL query to be processed by the database and returns matching records to be bound to the SGrid object.

SUB Find_OnClick

	myQuery = "Select FirstName, LastName, Title, Type, Email, ManagerEmail, Building, Room, Phone from Employee"
	Filtered = False
	'Check QBE fields and compose a dynamic SQL query.

	IF (SFirst.Value <> "") THEN
		myQuery = myQuery + " where FirstName like '" + SFirst.Value + "%'"
		Filtered = True
	END IF

	IF (SLast.Value <> "") THEN
		IF Filtered THEN
			myQuery = myQuery + " and LastName like '" + SLast.Value + "%'"
		ELSE
			myQuery = myQuery + " where LastName like '" + SLast.Value + "%'"
			Filtered = True
		END IF
	END IF

	IF (STitle.Value <> "") THEN
		IF Filtered THEN
			myQuery = myQuery + " and Title like '" + STitle.Value + "%'"
		ELSE
			myQuery = myQuery + " where Title like '" + STitle.Value + "%'"
			Filtered = True
		END IF
	END IF

	IF (SEmail.Value <> "") THEN
		IF Filtered THEN
			myQuery = myQuery + " and Email like '" + SEmail.Value + "%'"
		ELSE
			myQuery = myQuery + " where Email like '" + SEmail.Value + "%'"
			Filtered = True
		END IF
	END IF

	'Set the new query and then refresh the SControl so that the new results are displayed.

	SControl.SQL = myQuery
	SControl.Refresh

	'Optional command specific to the Sheridan Grid to ensure display of the correct data
	Grid1.Rebind
	
END SUB

'Navigation subroutines - based on currency changes to AdvancedDataControl (SControl).

'Move to the first record in the bound recordset.

SUB First_OnClick
  	SControl.Recordset.MoveFirst
END SUB

'Move to the next record from the current position in the bound recordset.

SUB Next_OnClick
	On Error Resume Next
	SControl.Recordset.MoveNext
	IF ERR.Number <> 0 THEN
		SControl.Recordset.MoveLast  'If already at end of recordset stay at end.
	END IF
END SUB

'Move to the previous record from the current position in the bound recordset.

SUB Prev_OnClick
	On Error Resume Next
	SControl.Recordset.MovePrevious
	IF ERR.Number <> 0 THEN
		SControl.Recordset.MoveFirst  'If already at start of recordset stay at top.
	END IF
END SUB

'Move to the last record in the bound recordset.

SUB Last_OnClick
  	SControl.Recordset.MoveLast
END SUB

'Submits edits made and pull a clean copy of the new data.

SUB Update_OnClick
  	SControl.SubmitChanges
	SControl.Refresh        ' A Refresh is not required in RDS 2.0 after a SubmitChanges, but it ensures fresh data.

	'Optional command specific to the Sheridan Grid to ensure display of the correct data
	Grid1.Rebind
END SUB

'Cancel edits and restores original values.

SUB Cancel_OnClick
  	SControl.CancelUpdate

	'Optional command specific to the Sheridan Grid to ensure display of the correct data
	Grid1.Rebind
END SUB

</SCRIPT>

<BR>
<font color = "#400040">This site powered by the Microsoft Data Access Components. </font>
</BODY>
</HTML>
