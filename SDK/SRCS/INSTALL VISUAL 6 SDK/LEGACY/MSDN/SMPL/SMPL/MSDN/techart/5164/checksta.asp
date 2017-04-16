<!--#include file="logon.inc"-->
<%
' Copyright (c) Microsoft Corporation 1993-1997. All rights reserved.
Dim AMSession
On Error Resume Next

' This should occur at the top of the script.  If the AM session does not
' exist and the URL does not contain server and mailbox data, a logon form will be
' emited and returned for the user to fill out.
CheckAMSession

' This should occur near the top of the script as well, before anything that may cause
' any text to be emited to the browser.  If the user is not already authenticated, 
' this function will return error 401 (Access denied) and prompt for credentials.
BAuthenticateUser

' After calling CheckAMSession, the AM session can be retrieved from 
' Session("AMSession").  CheckAMSession may have failed to create a session, though,
' so check whether objAMSession is Nothing and if so cleanup, inform the user, etc.
Set AMSession= Session( "AMSession")

if AMSession Is Nothing Then
' CheckSession was unable to retrieve or create a session
    Response.Write( "GetAMSession returned nothing!<br>")
End If
	
Mailbox = Session("Mailbox")

Set objInfoStoresColl = AMSession.InfoStores

If objInfoStoresColl Is Nothing Then
End If
If 0 = objInfoStoresColl.Count Then
End If

iInfostorescollindex = 1
Set objInfoStore = objInfoStoresColl.Item(iInfostorescollindex)
If objInfoStore Is Nothing Then
    Response.Write "error, cannot get this InfoStore object"
End If

While objInfoStore.Name <> "Public Folders"  
   
    If iInfostorescollindex < objInfoStoresColl.Count Then
        iInfostorescollindex = iInfostorescollindex + 1
    End If    
    
    Set objInfoStore = objInfoStoresColl.Item(iInfostorescollindex)
Wend

'Have to set the FolderID or it won't work.
bstrPublicRootID = objInfoStore.Fields.Item( &H66310102 ).Value
Set myrootfolder = AMSession.GetFolder(bstrPublicRootID, objInfoStore.ID)
Set myfoldercollect = myrootfolder.Folders
Set recursefolder = myfoldercollect.GetFirst()
'Recurse it until we get the folder we are looking for
While recursefolder.Name <> "Expense Reports"
     Set recursefolder = myfoldercollect.GetNext()
Wend
set objFolder = recursefolder

'Time for some message recursion fun
'Get the messages

set oMessages = objFolder.Messages

'Lets get the count and blast through them all to see who owns and status
%>


<head>
<meta http-equiv="Content-Type"
content="text/html; charset=iso-8859-1">
<meta name="GENERATOR" content="Microsoft FrontPage 2.0">
<title>Expense Report Status Page</title>
</head>

<body bgcolor="#FFFFFF">

<p><font size="6" face="Arial Black">Your Expense Report status page</font></p>

<hr>
<table border="0">
    <tr>
<%
for i = 1 to oMessages.count
    set oMessage = oMessages.Item(i)
'check the owner, who submitted the message
    set whosent = oMessage.Sender
    CurrentApprover = oMessage.Fields("Approver")

    if whosent.Name = AMSession.CurrentUser then
        Status = oMessage.Fields("Status")
        StatusInt = oMessage.Fields("StatusInt")
        Total = oMessage.Fields("Total")
        TimeSent = oMessage.TimeSent
' Write them out
        if StatusInt = 1 then
            response.write "<TD><img src='mail6c.gif'></TD>"
        end if
        if StatusInt = 2 then
            response.write "<TD><img src='yellowli.gif'></TD>"
        end if
        if StatusInt = 3 then
            response.write "<TD><img src='greenlig.gif'></TD>"
        end if
        if StatusInt = 4 then
            response.write "<TD><img src='stopsml.gif'></TD>"
        end if
        response.write "<TD> Current Status: </TD><TD><B>" & Status
        response.write "</B></TD>"
        response.write "<TD> Time Submitted: </TD><TD><B>" & TimeSent
        response.write "</B></TD>"
        response.write "<TD> Total: </TD><TD><B>" & Total
        response.write "</B></TD></TR>"		
    end if
next
%>

</table>
</body>
</html>
