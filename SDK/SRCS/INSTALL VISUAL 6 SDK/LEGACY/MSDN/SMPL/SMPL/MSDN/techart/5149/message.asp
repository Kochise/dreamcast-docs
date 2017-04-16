<!DOCTYPE HTML PUBLIC "-//IETF//DTD HTML//EN">
<html>

<head>
<meta http-equiv="Content-Type"
content="text/html; charset=iso-8859-1">
<meta name="GENERATOR" content="Microsoft FrontPage 2.0">
<title>Techdesk Submitted Form</title>
</head>

<body>



<%

'This code was written by Tom Rizzo (thomriz@microsoft.com)

'get the users session object
Set objOMSession= Session( "AMSession")





'Create techdesk message and fill props
'Find the correct infostore


    Set objInfoStoresColl = objOMSession.InfoStores

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

	Set myrootfolder = objOMSession.GetFolder(bstrPublicRootID, objInfoStore.ID)
	Set myfoldercollect = myrootfolder.Folders
	Set recursefolder = myfoldercollect.GetFirst()
'Recurse it until we get the folder we are looking for
	While recursefolder.Name <> "Techdesk"
	  Set recursefolder = myfoldercollect.GetNext()
	Wend

    set objFolder = recursefolder

'Get the entry id for the message from the query string
    set objMessageID = Request.QueryString("entryid")
'Get the message by its id
    set oMessage = objOMSession.GetMessage(objMessageID, objInfoStore.ID)
'Set the message as read
    oMessage.Unread = FALSE
'Update the message in the folder
    oMessage.Update	

'Get the status of the message (done, open)
    set msgstatus = oMessage.Fields("Flag")

'Get the user who posted the message
    set objuser = oMessage.Fields("From User")
    
'Start the ADO Connection

Set Conn = Server.CreateObject("ADODB.Connection")
Conn.Open "techdesk"
Set RS = Conn.Execute("Select SystemChipType, SystemChipSpeed, SystemChipCount, SystemOS, SystemRAM FROM tblMachine WHERE Userid like '" & objuser & "';")
Set RSIP = Conn.Execute("Select CompName, IPAddress FROM tblNetwork WHERE Userid like '" & objuser & "';")
Set RSSoft = Conn.Execute("Select SoftwareName, SoftwareVersion FROM tblSoftware WHERE Userid like '" & objuser &"';")

'Add a message to the outbox in order to get directory information
Set objmessage = objOMSession.Outbox.Messages.Add

' create the recipient
Set objonerecip = objmessage.Recipients.Add

objonerecip.Name = oMessage.Fields("From User")

objonerecip.Resolve

'Get the address entry so we can pull out template info
Set myaddentry = objonerecip.AddressEntry

Set myfields = myaddentry.Fields
'The numbers in parens are the hardcoded ids for dept, name, etc.

Set mydept = myfields.Item(974651422)
set myname = myfields.Item(805371934)
set mytitle = myfields.Item(974585886)
set myworkphone = myfields.Item(973602846)
set myoffice = myfields.Item(974716958)





%>

<HTML>

<HEAD>
<TITLE>Retrieve Techdesk Request</TITLE>
<STYLE TYPE="text/css">
<!--
 	A:link {text-decoration: none}
  	A:visited {text-decoration: none}
	A:active {text-decoration: none}
-->
</STYLE>
</HEAD>

<BODY BACKGROUND="/AdvWorks/multimedia/images/back_sub.gif" LINK="#800000" VLINK="#008040"> 
<FONT FACE="MS SANS SERIF" SIZE=2>
<BGSOUND SRC="/AdvWorks/multimedia/sounds/windfin4.wav">


<TABLE WIDTH=600 BORDER=0>

<TR>
<TD>


<IMG SRC="/techdesk/outlook.GIF" ALIGN=RIGHT WIDTH=110 ALT="Space">

</TD>

<TD VALIGN=TOP ALIGN=LEFT COLSPAN=3><FONT SIZE=6>
<FONT SIZE=6 FACE="ARIAL NARROW" COLOR="#800000">Techdesk Request<BR>
<HR SIZE=4>
<FORM ACTION="/techdesk/resolved.asp?entryid=<%response.write objMessageID%>" METHOD=POST>
<INPUT TYPE=SUBMIT NAME="Action" VALUE="Resolved!">
<INPUT TYPE=SUBMIT NAME="Action" VALUE="Cancel">
</TD>
</TR>

<TR>
<TD ROWSPAN=7 VALIGN=TOP ALIGN=LEFT>
<A HREF="/AdvWorks/equipment/default.asp">
<IMG SRC="/AdvWorks/multimedia/images/icon_sub_equipment.GIF" ALIGN=CENTER BORDER=0 ALT="Equipment"></A><BR>

<A HREF="/AdvWorks/excursions/default.asp">
<IMG SRC="/AdvWorks/multimedia/images/icon_sub_excursions.GIF" ALIGN=CENTER BORDER=0 ALT="Membership and Excursions"></A><BR>

<A HREF="/AdvWorks/resources/default.asp">
<IMG SRC="/AdvWorks/multimedia/images/icon_sub_resources.GIF" ALIGN=CENTER BORDER=0 ALT="Resources"></A><BR>

<A HREF="/AdvWorks/internal/default.asp">
<IMG SRC="/AdvWorks/multimedia/images/icon_sub_internal.GIF" ALIGN=CENTER BORDER=0 ALT="Internal"></A><BR>

<A HREF="/AdvWorks/default.asp">
<IMG SRC="/AdvWorks/multimedia/images/icon_sub_home.GIF" ALIGN=CENTER BORDER=0 ALT="Home"></A><BR>

</TD>

<TD ROWSPAN=4 ALIGN=RIGHT VALIGN=TOP>
<TD>
<TR>
<IMG SRC="/AdvWorks/multimedia/images/spacer.gif" WIDTH=120 HEIGHT=350 ALIGN=RIGHT ALT="Space">



<FONT STYLE="ARIAL NARROW" SIZE=2><b>Please review the following:</FONT>

<TABLE COLSPAN=15 CELLPADDING=5 CELLSPACING=0>

<TR bgcolor=663333>


<TD ALIGN=LEFT>
<FONT STYLE="ARIAL NARROW" COLOR="#ffffff" SIZE=1><b>Contact Email: </b></FONT>
</TD>
<TD ALIGN=LEFT>
<INPUT TYPE="Text" NAME="Contact_Email" value="<%=oMessage.Fields("From User")%>" SIZE=20 MAXLENGTH=20><P>
</TD>
<TD ALIGN=LEFT>
<FONT STYLE="ARIAL NARROW" COLOR="#ffffff" SIZE=1><b>Title: </b></FONT>
</TD>
<TD ALIGN=LEFT>
<INPUT TYPE="Text" NAME="Title" value="<%=mytitle.Value %>" SIZE=20 MAXLENGTH=20><P>
</TD>

<TD ALIGN=LEFT>
<FONT STYLE="ARIAL NARROW" COLOR="#ffffff" SIZE=1><b>Department: </b></FONT>
</TD>
<TD ALIGN=LEFT>
<INPUT TYPE="Text" NAME="Department" value="<% Response.write mydept.Value %>" SIZE=20 MAXLENGTH=20><P>
</TD>


</tr>

<TR bgcolor=663333>

<TD ALIGN=LEFT>
<FONT STYLE="ARIAL NARROW" COLOR="#ffffff" SIZE=1><b>Phone Number: </b></FONT>
</TD>
<TD ALIGN=LEFT>
<INPUT TYPE="Number" NAME="Phone" Value="<% Response.Write myworkphone.Value %>" SIZE=10 MAXLENGTH=10><P>
</TD>

<TD ALIGN=LEFT>
<FONT STYLE="ARIAL NARROW" COLOR="#ffffff" SIZE=1><b>User Location: </b></FONT>
</TD>
<TD ALIGN=LEFT>
<INPUT TYPE="Number" NAME="Location" value="<% Response.Write myoffice.Value %>" SIZE=20 MAXLENGTH=20><P>
</TD>

<TD ALIGN=LEFT>
<FONT STYLE="ARIAL NARROW" COLOR="#ffffff" SIZE=1><b>Status: </b></FONT>
</TD>
<TD ALIGN=LEFT>
<INPUT TYPE="Text" NAME="Status" value="<% Response.write msgstatus.Value %>" SIZE=20 MAXLENGTH=20><P>
</TD>



</tr>

<TR bgcolor=663333>

<TD ALIGN=LEFT>
<FONT STYLE="ARIAL NARROW" COLOR="#ffffff" SIZE=1><b>System Processor: </b></FONT>
</TD>
<TD ALIGN=LEFT>
<INPUT TYPE="Text" NAME="Sysprocessor" value="<%=rs(2)%>&nbsp;<%=rs(0)%>&nbsp;<%=rs(1)%> MHz" SIZE=20 MAXLENGTH=20><P>
</TD>

<TD ALIGN=LEFT>
<FONT STYLE="ARIAL NARROW" COLOR="#ffffff" SIZE=1><b>System Ram: </b></FONT>
</TD>
<TD ALIGN=LEFT>
<INPUT TYPE="Text" NAME="RAM" value="<%=rs(4)%> Megs" SIZE=12 MAXLENGTH=12><P>
</TD>

<TD ALIGN=LEFT>
<FONT STYLE="ARIAL NARROW" COLOR="#ffffff" SIZE=1><b>System OS: </b></FONT>
</TD>
<TD ALIGN=LEFT>
<INPUT TYPE="Text" NAME="OS" value="<%=rs(3)%>" SIZE=23 MAXLENGTH=23><P>
</TD>
</TR>


<TR bgcolor=663333>


<TD ALIGN=LEFT>
<FONT STYLE="ARIAL NARROW" COLOR="#ffffff" SIZE=1><b>Computer Name: </b></FONT>
</TD>
<TD ALIGN=LEFT>
<INPUT TYPE="Text" NAME="Compname" value="<%=rsIP(0)%>" SIZE=12 MAXLENGTH=12><P>
</TD>

<TD ALIGN=LEFT>
<FONT STYLE="ARIAL NARROW" COLOR="#ffffff" SIZE=1><b>IP Address: </b></FONT>
</TD>
<TD ALIGN=LEFT>
<INPUT TYPE="Text" NAME="IP" value="<%=rsIP(1)%>" SIZE=12 MAXLENGTH=12><P>
</TD>


<TD ALIGN=LEFT>
<FONT STYLE="ARIAL NARROW" COLOR="#ffffff" SIZE=1><b>Installed Software: </b></FONT>
</TD>
<TD ALIGN=LEFT>
<INPUT TYPE="Text" NAME="Soft" value="<%=rsSoft(0)%> Ver. <%=rsSoft(1)%>" SIZE=23 MAXLENGTH=23><P>
</TD>


</tr>

<TR bgcolor=663333>

<TD ALIGN=LEFT>
<FONT STYLE="ARIAL NARROW" COLOR="#ffffff" SIZE=1><b>Problem Type: </b></FONT>
</TD>
<TD ALIGN=LEFT>
<SELECT NAME="Type">
<OPTION>Software
<OPTION>Hardware
<OPTION>Network
<OPTION>Internet
<OPTION>Remote
<OPTION>ISDN
<OPTION>Tip
<OPTION SELECTED><%=oMessage.Fields("Problem Type")%>
</SELECT>
<P>
</TD>



<TD ALIGN=LEFT>
<FONT STYLE="ARIAL NARROW" COLOR="#ffffff" SIZE=1><b>Product: </b></FONT>
</TD>
<TD ALIGN=LEFT>
<SELECT NAME="Product">
<OPTION>Word
<OPTION>Excel
<OPTION>Outlook
<OPTION>Internet Explorer
<OPTION>Windows NT
<OPTION>Windows 95
<OPTION>Exchange
<OPTION SELECTED><%=oMessage.Fields("Product")%>
</SELECT>
</TD>

<TD ALIGN=LEFT>
<FONT STYLE="ARIAL NARROW" COLOR="#ffffff" SIZE=1><b>Priority: </b></FONT>
</TD>
<TD ALIGN=LEFT>
<SELECT NAME="Priority">
<% Select Case oMessage.Importance
	Case 1 
	        response.write "<OPTION SELECTED VALUE=1>Normal"
		response.write "<OPTION VALUE=3>Low"
		response.write "<OPTION VALUE=2>High"
		response.write "</SELECT>"
	Case 2
		response.write "<OPTION VALUE=1>Normal"
		response.write "<OPTION VALUE=3>Low"
		response.write "<OPTION SELECTED VALUE=2>High"
		response.write "</SELECT>"
	Case 3 
		response.write "<OPTION VALUE=1>Normal"
		response.write "<OPTION SELECTED VALUE=3>Low"
		response.write "<OPTION VALUE=2>High"
		response.write "</SELECT>"
End Select %>

		

</TD>
</tr>



<TR bgcolor=663333>
<TD ALIGN=LEFT>
<FONT STYLE="ARIAL NARROW" COLOR="#ffffff" SIZE=1><b>Problem: </b></FONT>
</TD>
<TD ALIGN=LEFT colspan=5>
<INPUT TYPE="Text" NAME="Subject" VALUE="<%=oMessage.Subject%>" SIZE=100 MAXLENGTH=100><P>
</TD>
</tr>



</TABLE>

<FONT STYLE="ARIAL NARROW" SIZE=2><b>Description:</FONT>
<TEXTAREA NAME="Description"  COLS=120 ROWS=12 WRAP=VIRTUAL><%=oMessage.Fields("Description")%></TEXTAREA><P>

<HR>
</FONT>


</FORM>



 

</TD>


<% REM Column Span Value %>
<% HTML_CS = 5 %>
<% HTML_INDENT = FALSE %>


</TABLE>




</BODY>

</HTML>

