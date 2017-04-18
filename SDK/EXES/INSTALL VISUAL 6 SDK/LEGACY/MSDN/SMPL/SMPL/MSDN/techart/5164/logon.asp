<!--#include file="logon.inc"-->
<%
' Copyright (c) Microsoft Corporation 1993-1997. All rights reserved.
On Error Resume Next
Dim objAMSession

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

Set objAMSession= Session( "AMSession")
if objAMSession Is Nothing Then

' CheckSession was unable to retrieve or create a session

Response.Write( "GetAMSession returned nothing!<br>")
End If
%>

<!DOCTYPE HTML PUBLIC "-//IETF//DTD HTML 3.2//EN"> 
<HTML>
<HEAD>
<title>Expense Report Home Page</title>
</head>
<body bgcolor="#FFFFFF">
<p><font size="6" face="Arial Black">Expense Report Intranet Application</font></p>
<hr>
Please select one of the following links:
<p>
<a href="expense.asp">Submit a new expense report</a>
<P>
<a href="checksta.asp">Check the status of my expense reports</a>
</body>
</html>

