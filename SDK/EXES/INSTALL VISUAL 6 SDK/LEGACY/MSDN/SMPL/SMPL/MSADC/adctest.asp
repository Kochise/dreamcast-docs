<HTML>
<HEAD>
<TITLE>RDS Sample Query Page</TITLE>
</HEAD>
<BODY BACKGROUND="AddressBook/Arcadia.gif">
<CENTER>
<H1>Remote Data Service Sample Query Page</H1>

<BR>
<OBJECT ID="GRID" WIDTH=600 HEIGHT=200 Datasrc="#ADC"
 CODEBASE="http://<%=Request.ServerVariables("SERVER_NAME")%>/MSADC/Samples/ssdatb32.cab"
 CLASSID="CLSID:AC05DC80-7DF1-11d0-839E-00A024A94B3A">
	<PARAM NAME="_Version"	    VALUE="131072">
	<PARAM NAME="BackColor"     VALUE="-2147483643">
	<PARAM NAME="BackColorOdd"  VALUE="-2147483643">
	<PARAM NAME="ForeColorEven" VALUE="0">	
	<PARAM NAME="AllowAddNew"   VALUE="TRUE">
	<PARAM NAME="AllowDelete"   VALUE="TRUE">
	<PARAM NAME="AllowUpdate"   VALUE="TRUE">
</OBJECT>
<BR>

<BR>
<table>
  <tr><td>ADC Server:<td><INPUT NAME=Server SIZE=70>
  <tr><td>Connection:<td><INPUT NAME=Connect SIZE=70>
  <tr><td>Query:<td><INPUT NAME=SQL SIZE=70>
  <tr><td>Recordset Status:<td><INPUT TYPE=TEXT Name=RecordSetStat SIZE =30>
  <tr><td>Execute Option:<td><INPUT TYPE=TEXT Name=ExecOpt SIZE =30>
  </table>

<BR>
<INPUT TYPE=BUTTON NAME="Requery" VALUE="Run!">
<INPUT TYPE=BUTTON NAME="MoveFirst" VALUE="First">
<INPUT TYPE=BUTTON NAME="MovePrev" VALUE="Prev">
<INPUT TYPE=BUTTON NAME="MoveNext" VALUE="Next">
<INPUT TYPE=BUTTON NAME="MoveLast" VALUE="Last"> <BR><BR>
<INPUT TYPE=BUTTON NAME="Update" VALUE="Save Changes">
<INPUT TYPE=BUTTON NAME="Cancel" VALUE="Cancel Changes">
<BR><BR>
<INPUT TYPE=BUTTON NAME="Stop" VALUE="Cancel Query">
<INPUT TYPE=BUTTON NAME="Asynchoff" VALUE="Turn Asynch off">
<INPUT TYPE=BUTTON NAME="Asynchon" VALUE="Turn Asynch on">
</CENTER>

<OBJECT classid="clsid:BD96C556-65A3-11D0-983A-00C04FC29E33"
    ID=ADC HEIGHT=1 WIDTH = 1>
</OBJECT>

<SCRIPT LANGUAGE="VBScript">
'---- enum Values ----
Const adcExecSync = 1
Const adcExecAsync = 2

'---- enum Values ----
Const adcFetchUpFront = 1
Const adcFetchBackground = 2
Const adcFetchAsync = 3

'---- enum Values ----
Const adcStateClosed = &H00000000
Const adcStateOpen = &H00000001
Const adcStateConnecting = &H00000002
Const adcStateExecuting = &H00000004
Const adcStateFetching = &H00000008

'---- enum Values ----
Const adcReadyStateLoaded = 2
Const adcReadyStateInteractive = 3
Const adcReadyStateComplete = 4

SUB Window_OnFocus

	if window.navigator.appversion >= "4.0" and window.navigator.appname >= "Microsoft" then
		if window.navigator.cpuclass="Alpha" then
			nextpage = "adctesta.asp"
			window.navigate nextpage
		end if
	end if

END SUB

SUB Window_OnLoad

  Server.Value = "http://<%=Request.ServerVariables("SERVER_NAME")%>"
  Connect.Value = "DSN=AdvWorks"
  SQL.Value = "Select * from Products"

  Select case ADC.ExecuteOptions
    case adcExecSync: ExecOpt.Value = "Synchronous"
    case adcExecAsync: ExecOpt.Value = "Asynchronous"
  END Select

  Select case ADC.ReadyState
    case adcReadyStateLoaded: RecordSetStat.Value = "Loaded"
    case adcReadyStateInteractive: RecordSetStat.Value = "Interactive"
    case adcReadyStateComplete: RecordSetStat.Value = "Complete"
  END Select

END SUB

SUB ADC_OnReadyStateChange
  'Fires every time that ADC.ReadyState changes
  Select case ADC.ReadyState
    case adcReadyStateLoaded: RecordSetStat.Value = "Loaded"
    case adcReadyStateInteractive: RecordSetStat.Value = "Interactive"
    case adcReadyStateComplete: RecordSetStat.Value = "Complete"
  END Select
END SUB

SUB ADC_OnDataSetChanged
  'Fires after execution is done

END SUB

SUB ADC_OnDataSetComplete
 'Fires after fetching is complete

END SUB

sub Move (strDirection)
  'Custom sub to handle Asyncronous fetching
  'Asynchronous fetching allows you to cancel in the middle of fetching a large
  'recordset
  if ADC.Recordset.State = adcStateClosed then
    if ADC.ReadyState = adcReadyStateComplete then
      msgbox "Query results failed to arrive, please rerun query synchronously and check for errors."
    end if
    if ADC.ReadyState = adcReadyStateLoaded then
      msgbox "Query results have not yet arrived"	
    end if
  else
    if ADC.Recordset.State = adcStateOpen Then	
      on error resume next
      select case strDirection
        Case "First"
          ADC.Recordset.MoveFirst
        Case "Next"
          ADC.Recordset.MoveNext
        Case "Last"
          ADC.Recordset.MoveLast
        Case "Prev"
          ADC.Recordset.MovePrevious
       end select
      IF ERR.Number <> 0 then
        if Err.Number = 3021 THEN
          if ADC.Recordset.BOF then
            ADC.Recordset.MoveFirst  'If already at start of recordset stay at top.
          else 
            ADC.Recordset.MoveLast   'If already at end of recordset stay at bottom.
          END IF
        else 
          msgbox "Unexpected error in Move actions. " & Err.Description
        END IF
      end if
    else
      msgbox "The state is unexpected, an error has occurred"   'Very General error msg. 
    end if
  end if
End Sub

SUB MoveFirst_OnClick
  'Call to Custom Sub, Move, to handle attempts to move the record pointer during asynch fetches
  move "First"
END SUB

SUB MoveNext_OnClick
  'Call to Custom Sub, Move, to handle attempts to move the record pointer during asynch fetches
  Move "Next"
END SUB

SUB MovePrev_OnClick
  'Call to Custom Sub, Move, to handle attempts to move the record pointer during asynch fetches
  Move "Prev"
END SUB

SUB MoveLast_OnClick
  'Call to Custom Sub, Move, to handle attempts to move the record pointer during asynch fetches
  Move "Last"
END SUB

'Submits edits made and pulls a clean copy of the new data.
SUB Update_OnClick
  If ADC.ReadyState <> adcReadyStateLoaded then
    ADC.SubmitChanges
    ADC.Refresh
		
    'Optional command specific to the Sheridan Grid to ensure display of the correct data
    Grid.Rebind

  Else
    MsgBox "Query results still arriving, Please wait"
  End if
    
END SUB

'Cancel edits and restores original values.
SUB Cancel_OnClick
  if ADC.ReadyState <> adcReadyStateLoaded then
     ADC.CancelUpdate
    
    'Optional command specific to the Sheridan Grid to ensure display of the correct data
    Grid.Rebind

  Else
    MsgBox "Query results still arriving, Please wait"
  End if

END SUB

SUB Requery_OnClick
  If ADC.ReadyState <> adcReadyStateComplete then
    MsgBox "Query results still arriving, Please wait"
  Else
    ADC.Server = Server.Value
     ADC.Connect = Connect.Value
    ADC.SQL = SQL.Value

    ADC.Refresh
    
    'Optional command specific to the Sheridan Grid to ensure display of the correct data
    Grid.Rebind

  End if

END SUB

SUB Stop_OnClick
  'If an asychronous query is taking too long to execute you can use this to cancel the query
  ADC.Cancel

END SUB

SUB Asynchoff_OnClick
  'In cases where there are problems querying the database you may need to switch to synchronous mode
  'in order to get the error
  ADC.ExecuteOptions = adcExecSync
  ADC.FetchOptions = adcFetchBackground
  Select case ADC.ExecuteOptions
    case adcExecSync: ExecOpt.Value = "Synchronous"
    case adcExecAsync: ExecOpt.Value = "Asynchronous"
  END Select


END SUB

SUB Asynchon_OnClick
  'In cases where there are problems querying the database you may need to switch to synchronous mode
  'in order to get the error
  ADC.ExecuteOptions = adcExecAsync
  ADC.FetchOptions = adcFetchAsync
  Select case ADC.ExecuteOptions
    case adcExecSync: ExecOpt.Value = "Synchronous"
    case adcExecAsync: ExecOpt.Value = "Asynchronous"
  END Select

END SUB

</SCRIPT>
</BODY>
</HTML>
