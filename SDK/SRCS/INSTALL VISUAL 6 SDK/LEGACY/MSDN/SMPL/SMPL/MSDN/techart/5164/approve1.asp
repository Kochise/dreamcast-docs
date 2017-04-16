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

' Have to set the FolderID or it won't work.

    bstrPublicRootID = objInfoStore.Fields.Item( &H66310102 ).Value

    Set myrootfolder = AMSession.GetFolder(bstrPublicRootID, objInfoStore.ID)
    Set myfoldercollect = myrootfolder.Folders
    Set recursefolder = myfoldercollect.GetFirst()
' Recurse it until we get the folder we are looking for
    While recursefolder.Name <> "Expense Reports"
        Set recursefolder = myfoldercollect.GetNext()
    Wend
    set objFolder = recursefolder

' Get the entry id for the message from the query string
    objMessageID = Session("EntryID")
' Get the message by its id
    set oMessage = AMSession.GetMessage(objMessageID, objInfoStore.ID)


' Get the Fields of the report
    set Meals = oMessage.Fields("Meals")
    set Hotel = oMessage.Fields("Hotel")
    set Airfare = oMessage.Fields("Airfare")
    set RentalCar = oMessage.Fields("Rentalcar")
    set Total = oMessage.Fields("Total")
    set Status = oMessage.Fields("Status")
    set StatusInt = oMessage.Fields("StatusInt")
' Get the user who posted the message
    set addentry = oMessage.Sender

' Need to parse out the ? from the approver field and replace with a &

    Approver = Session("Approver")
	
    HTMLApprover = Replace(Approver," ","+")
%>

<head>
<meta http-equiv="Content-Type"
content="text/html; charset=iso-8859-1">
<meta name="GENERATOR" content="Microsoft FrontPage 2.0">
<title>Expense Report Approve Page</title>
</head>

<body bgcolor="#FFFFFF">

<% 	if StatusInt = 3 then 'Were already approved
%>

<p><font size="6" face="Arial Black">This Expense Report has already been approved.</font></p>
<hr>
The expense report was: <B><% =Status%></B><P>

<% elseif StatusInt = 4 then 'were already rejected
%>
<p><font size="6" face="Arial Black">This Expense Report has already been rejected.</font></p>
<hr>
The expense report was: <B><% =Status%></B><P>

<% else %>
<p><font size="6" face="Arial Black">This Expense Report needs your approval.</font></p>

<hr>
Please review the following expense report and approve or reject it.<P>

<form action="finalapp.asp?entryid=<%=objMessageID%>&Approver=<%=HTMLApprover%>" method="POST">
    <table border="0">
        <tr>
            <td><font size="5"><strong>Submitted by:</strong></font></td>
            <td><B><%=addentry.Name%></b></td>
        </tr>
        <tr>
            <td><font size="5"><strong>Status:</strong></font></td>
            <td><%=Status%></td>
        </tr>


        <tr>
            <td><font size="5"><strong>Airfare:</strong></font></td>
            <td><%=Airfare%></td>
        </tr>
        <tr>
            <td><font size="5"><strong>Rental Car:</strong></font></td>
            <td><%=RentalCar%></td>
        </tr>
        <tr>
            <td><font size="5"><strong>Hotel:</strong></font></td>
            <td><%=Hotel%></td>
        </tr>
        <tr>
            <td><font size="5"><strong>Meals:</strong></font></td>
            <td><% =Meals%></td>
        </tr>
        <HR>
	<tr>
            <td><font size="5"><strong>Total:</strong></font></td>
            <td><B><I><%=Total%></i></b></td>
        </tr>
        <tr>
            <td><input type="submit" name="Approve" value="Approve"></td>
            <td><input type="submit" name="Reject" value="Reject"></td>
        </tr>
    </table>
</form>

<% end if %>

</body>
</html>
