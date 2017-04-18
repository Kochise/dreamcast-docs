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
 	
IntHotel = CInt(Request.Form("Hotel"))
IntMeals = CInt(Request.Form("Meals"))
IntAirfare = CInt(Request.Form("Airfare"))
IntRentalcar = CInt(Request.Form("Rentalcar"))
Total = IntHotel + IntMeals + IntAirfare + IntRentalcar

set newExpenseReport = AMSession.outbox.messages.add
set mynewrecipient = newExpenseReport.recipients.add
mynewrecipient.Name = "Expense Reports"
mynewrecipient.resolve
set newSenderName = AMSession.CurrentUser
newExpenseReport.subject = "New Expense Report from " & newSenderName.Name & " " & Now()
newExpenseReport.text = "The total value of this report was " & Total
newExpenseReport.Fields.Add "Hotel",8,Request.Form("Hotel")
newExpenseReport.Fields.Add "Meals",8,Request.Form("Meals")
newExpenseReport.Fields.Add "Airfare",8,Request.Form("Airfare")
newExpenseReport.Fields.Add "Rentalcar",8,Request.Form("RentalCar")
newExpenseReport.Fields.Add "Total",8,Total
newExpenseReport.Fields.Add "Status",8,"Submitted"
newExpenseReport.Fields.Add "StatusInt",8,1 'Submitted, 2 Awaiting Approval, 3 Approved, 4 Rejected
newExpenseReport.Fields.Add "Approver",8,newSenderName.Manager.Name
newExpenseReport.send
	
' set ExpenseFolder = AMSession.GetFolder("000000001A447390AA6611CD9BC800AA002FC45A0300349215488BE6D011AB5A0060973FA69900000000001A0000",AMInfostores.Item(AMInfostorecount).ID)
' set ExpenseFolderMsgs = ExpenseFolder.Messages
' set newExpenseReport = ExpenseFolderMsgs.Add
' newExpenseReport.Subject = "New Expense Report"
' newExpenseReport.Type = "IPM.Post"
' newExpenseReport.Timesent = Now()
' newExpenseReport.Timereceived = Now()
' newExpenseReport.Fields.Add "Hotel",8,Request.Form("Hotel")
' newExpenseReport.Fields.Add "Meals",8,Request.Form("Meals")
' newExpenseReport.Fields.Add "Airfare",8,Request.Form("Airfare")
' newExpenseReport.Fields.Add "Rentalcar",8,Request.Form("RentalCar")
' newExpenseReport.Fields.Add "Fromuser",8,"Administrator"
' IntHotel = CInt(Request.Form("Hotel"))
' IntMeals = CInt(Request.Form("Meals"))
' IntAirfare = CInt(Request.Form("Airfare"))
' IntRentalcar = CInt(Request.Form("Rentalcar"))
' Total = IntHotel + IntMeals + IntAirfare + IntRentalcar
' newExpenseReport.ConversationTopic = "New Expense Report"
' newExpenseReport.Submitted = False
' newExpenseReport.Unread = True
' newExpenseReport.Sent = True
'newExpenseReport.Update

%>

<head>
<meta http-equiv="Content-Type"
content="text/html; charset=iso-8859-1">
<meta name="GENERATOR" content="Microsoft FrontPage 2.0">
<title>Expense Report Submit Page</title>
</head>

<body bgcolor="#FFFFFF">
<p><font size="6" face="Arial Black">Your Expense Report has been submitted</font></p>
<hr>
Your total amount for the Expense Report was <b>$<% response.write Total%></b>
<P>
<a href="checksta.asp">Click here to check the status of your expense reports.</a>
</body>
</html>
