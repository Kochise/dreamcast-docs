<!--#include file="logon.inc"-->

<%
'This code was written by Tom Rizzo (thomriz@microsoft.com)

	Dim objAMSession

	' This should occur near the top of the script, before anything that may cause
	' any text to be emited to the browser.  If the user is not already authenticated, 
	' this function will return error 401 (Access denied) and prompt for credentials.
	BAuthenticateUser

	' This should occur at the top of the script as well.  If the AM session does not
	' exist and the URL does not contain server and mailbox data, a logon form will be
	' emited and returned for the user to fill out.
	CheckAMSession

	' After calling CheckAMSession, the AM session can be retrieved from 
	' Session("AMSession").  CheckAMSession may have failed to create a session, though,
	' so check whether objAMSession is Nothing and if so cleanup, inform the user, etc.
	Set objOMSession= Session( "AMSession")

	if objOMSession Is Nothing Then
		' CheckSession was unable to retrieve or create a session
		Response.Write( "GetAMSession returned nothing!<br>")
	End If


Set objmessage = objOMSession.Outbox.Messages.Add

' create the recipient
Set objonerecip = objmessage.Recipients.Add

'Retrieve the Email address from the previous HTML form
objonerecip.Name = Request.Form("Contact_Email")

'Resolve the name against the Exchange directory
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
<TITLE>Post Support Request</TITLE>
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
<FONT SIZE=6 FACE="ARIAL NARROW" COLOR="#800000">Support Request<BR>
<HR SIZE=4>
<FORM ACTION="/techdesk/posthelp.asp?" METHOD=POST>
<INPUT TYPE=SUBMIT NAME="Action" VALUE="Post Now!">
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



<FONT STYLE="ARIAL NARROW" SIZE=2><b>Please complete the following:</FONT>

<TABLE COLSPAN=15 CELLPADDING=5 CELLSPACING=0>

<TR bgcolor=663333>


<TD ALIGN=LEFT>
<FONT STYLE="ARIAL NARROW" COLOR="#ffffff" SIZE=1><b>Contact Email: </b></FONT>
</TD>
<TD ALIGN=LEFT>
<INPUT TYPE="Text" NAME="Contact_Email" value="<% Response.write Request.Form("Contact_Email") %>" SIZE=20 MAXLENGTH=20><P>
</TD>
<TD ALIGN=LEFT>
<FONT STYLE="ARIAL NARROW" COLOR="#ffffff" SIZE=1><b>Title: </b></FONT>
</TD>
<TD ALIGN=LEFT>
<INPUT TYPE="Text" NAME="Title" value="<% Response.write mytitle.Value %>" SIZE=20 MAXLENGTH=20><P>
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
<TD ALIGN=LEFT Colspan=3>
<INPUT TYPE="Number" NAME="Location" value="<% Response.Write myoffice.Value %>" SIZE=20 MAXLENGTH=20><P>
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
</SELECT>
</TD>

<TD ALIGN=LEFT>
<FONT STYLE="ARIAL NARROW" COLOR="#ffffff" SIZE=1><b>Priority: </b></FONT>
</TD>
<TD ALIGN=LEFT>
<SELECT NAME="Priority">
<OPTION VALUE=1>Normal
<OPTION VALUE=3>Low
<OPTION VALUE=2>High
</SELECT>
</TD>
</tr>



<TR bgcolor=663333>
<TD ALIGN=LEFT>
<FONT STYLE="ARIAL NARROW" COLOR="#ffffff" SIZE=1><b>Problem: </b></FONT>
</TD>
<TD ALIGN=LEFT colspan=5>
<INPUT TYPE="Text" NAME="Subject" VALUE="<%=szSubject%>" SIZE=100 MAXLENGTH=100><P>
</TD>
</tr>



</TABLE>

<FONT STYLE="ARIAL NARROW" SIZE=2><b>Description:</FONT>
<TEXTAREA NAME="Description" COLS=120 ROWS=12 WRAP=VIRTUAL></TEXTAREA><P>

<HR>
</FONT>


</FORM>

</TD>


<% REM Column Span Value %>
<% HTML_CS = 5 %>
<% HTML_INDENT = FALSE %>


</TABLE>

<% response.write request.form("Contact_Email") %>

</BODY>

</HTML>

