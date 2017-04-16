<HTML>

<TITLE>VB5 MultiThreaded Testing</TITLE>


<% 


   Dim objServer
   Dim vntResultSetArray
   Dim vntAverage  

   'Create the Object
    Set objServer = Server.CreateObject("IOSimulation.clsIOOp")


   'Initialize the Table for Logging or stop logging if Flag sent
    If (Request.QueryString("LogResults")="Start") Then
	objServer.SetLogFlag
    End If

    If (Request.QueryString("LogResults")="Stop") Then
	objServer.SetStopLogFlag
    End If
    
    'Simulate an I/O Bound request to a third tier server
    objServer.IOSleep 2000

    'Log the Machine and Elapsed Time of request
    objServer.LogMachineTime Request.QueryString("MachineName"), Request.QueryString("Time")

    'Let go of the server reference
    Set objServer = Nothing

%>

HTML Returned Correctly

<BR>
<BR>

</HTML>