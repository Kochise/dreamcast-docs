<HTML>
<HEAD>
<TITLE>Corporate Address Book</TITLE>
</HEAD>

<!--
	Purpose:	To provide a company directory search service for Web users.
	Written By:	Microsoft Advanced Data Connector Team, Microsoft Corp.
	Date:		April, 1997
-->

<BODY BACKGROUND="Arcadia.gif">
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

<OBJECT CLASSID="clsid:BC496AE0-9B4E-11CE-A6D5-0000C0BE9395" 
	ID=Grid1
	CODEBASE="HTTP://<%=Request.ServerVariables("SERVER_NAME")%>/MSADC/Samples/ssdatb32.cab"  
	HEIGHT= 125
	Width = 495>
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

<OBJECT CLASSID="clsid:9381D8F2-0288-11d0-9501-00AA00B911A5"
	ID="SControl"
	CODEBASE="HTTP://<%=Request.ServerVariables("SERVER_NAME")%>/MSADC/msadc11.cab#version=1,1,0,0"  
	WIDTH=1 HEIGHT=1>
	<PARAM NAME="BINDINGS" VALUE="Grid1;">
	<PARAM NAME="Connect" VALUE="DSN=ADCDEMO;UID=adcdemo;PWD=adcdemo;">
	<PARAM NAME="Server" VALUE="http://<%=Request.ServerVariables("SERVER_NAME")%>">
</OBJECT>


<!-- VBS scripting for composing queries, updating profiles, and retrieving search results. -->

<SCRIPT LANGUAGE="VBScript">

Dim myQuery

SUB Window_OnLoad
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

	myQuery = "Select FirstName, LastName, Title, Email, Building, Room, Phone from Employee"

	'Check QBE fields and compose a dynamic SQL query.

	IF (SFirst.Value <> "") THEN
		myQuery = myQuery + " where FirstName like '" + SFirst.Value + "%'"
	END IF

	IF (SLast.Value <> "") THEN
		myQuery = myQuery + " where LastName like '" + SLast.Value + "%'"
	END IF

	IF (STitle.Value <> "") THEN
		myQuery = myQuery + " where Title like '" + STitle.Value + "%'"
	END IF

	IF (SEmail.Value <> "") THEN
		myQuery = myQuery + " where Email like '" + SEmail.Value + "%'"
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
  	SControl.MoveFirst
END SUB

'Move to the next record from the current position in the bound recordset.

SUB Next_OnClick
	On Error Resume Next
	SControl.MoveNext
	IF ERR.Number <> 0 THEN
		SControl.Recordset.MoveLast  'If already at end of recordset stay at end.
	END IF
END SUB

'Move to the previous record from the current position in the bound recordset.

SUB Prev_OnClick
	On Error Resume Next
	SControl.MovePrevious
	IF ERR.Number <> 0 THEN
		SControl.Recordset.MoveFirst  'If already at start of recordset stay at top.
	END IF
END SUB

'Move to the last record in the bound recordset.

SUB Last_OnClick
  	SControl.MoveLast
END SUB

'Submits edits made and pull a clean copy of the new data.

SUB Update_OnClick
  	SControl.SubmitChanges
	SControl.Refresh 

	'Optional command specific to the Sheridan Grid to ensure display of the correct data
	Grid1.Rebind
END SUB

'Cancel edits and restores original values.

SUB Cancel_OnClick
  	SControl.CancelUpdate
	SControl.Refresh

	'Optional command specific to the Sheridan Grid to ensure display of the correct data
	Grid1.Rebind
END SUB

</SCRIPT>

<BR>
<font color = "#400040">This site powered by Microsoft Advanced Data Connector. </font>
</BODY>
</HTML>