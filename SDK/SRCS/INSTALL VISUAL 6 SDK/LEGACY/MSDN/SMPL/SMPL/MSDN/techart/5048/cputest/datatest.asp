<HTML>

<TITLE>VB5 MultiThreaded Testing</TITLE>


<% 


   Dim objServer
   Dim vntResultSetArray
   Dim vntAverage  

   'Create the Object
    Set objServer = Server.CreateObject("DBTest.clsDatabaseOp")


   'Initialize the Table for Logging or stop logging if Flag sent
    If (Request.QueryString("LogResults")="Start") Then
	objServer.SetLogFlag
    End If

    If (Request.QueryString("LogResults")="Stop") Then
	objServer.SetStopLogFlag
    End If

   'Retrieve the data into an array
    vntResultSetArray = objServer.GetData("Select UnitPrice, Quantity From [Order Details]") 
    
    'Have the server calculate the average 
    vntAverage = objServer.CalculatePriceQuantityAverage(vntResultSetArray)

    'Log the Machine and Elapsed Time of request
    objServer.LogMachineTime Request.QueryString("MachineName"), Request.QueryString("Time")

    'Let go of the server reference
    Set objServer = Nothing

%>

 <% = Request.QueryString("LogResults") %>

Average [Unit Price]/Quantity Factor = <% = vntAverage %> 

<BR>
<BR>

</HTML>