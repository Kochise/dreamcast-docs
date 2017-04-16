<!--#include file="logon.inc"-->
<%
' Copyright (c) Microsoft Corporation 1993-1997. All rights reserved.
On Error Resume Next
Dim AMSession
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
%>

<head>
<meta http-equiv="Content-Type"
content="text/html; charset=iso-8859-1">
<meta name="GENERATOR" content="Microsoft FrontPage 2.0">
<title>Expense Report Home Page</title>
</head>

<body bgcolor="#FFFFFF">
<p><font size="6" face="Arial Black">Expense Reporting Form</font></p>
<hr>
<p><font color="#000000" face="Arial">Please fill in the form
below. <strong>Please note:</strong> Any expense reports that are
over $5,000 will be routed to your manager for approval.<br>
<br>
</font></p>

<form action="submit.asp" method="POST">
    <table border="0">
        <tr>
            <td><font size="5"><strong>Airfare:</strong></font></td>
            <td><input type="text" size="20" name="Airfare"></td>
        </tr>
        <tr>
            <td><font size="5"><strong>Rental Car:</strong></font></td>
            <td><input type="text" size="20" name="RentalCar"></td>
        </tr>
        <tr>
            <td><font size="5"><strong>Hotel:</strong></font></td>
            <td><input type="text" size="20" name="Hotel"></td>
        </tr>
        <tr>
            <td><font size="5"><strong>Meals:</strong></font></td>
            <td><input type="text" size="20" name="Meals"></td>
        </tr>
        <tr>
            <td><input type="submit" name="Submit" value="Submit"></td>
            <td><input type="reset" name="Reset" value="Reset"></td>
        </tr>
    </table>
</form>

<p>&nbsp;</p>

</body>
</html>
