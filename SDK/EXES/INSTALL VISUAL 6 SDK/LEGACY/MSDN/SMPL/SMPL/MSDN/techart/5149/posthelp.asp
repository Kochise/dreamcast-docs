<!DOCTYPE HTML PUBLIC "-//IETF//DTD HTML//EN">
<html>

<head>
<meta http-equiv="Content-Type"
content="text/html; charset=iso-8859-1">
<meta name="GENERATOR" content="Microsoft FrontPage 2.0">
<title>Techdesk Submit Form</title>
</head>

<body>



<%

'This code was written by Tom Rizzo (thomriz@microsoft.com)

'Get the users session object
Set objOMSession= Session( "AMSession")


'Create techdesk message and fill props
'Find the correct infostore


    Set objInfoStoresColl = objOMSession.InfoStores


    iInfostorescollindex = 1
    Set objInfoStore = objInfoStoresColl.Item(iInfostorescollindex)
    While objInfoStore.Name <> "Public Folders"  
       If iInfostorescollindex < objInfoStoresColl.Count Then
       iInfostorescollindex = iInfostorescollindex + 1
    End If

    

    Set objInfoStore = objInfoStoresColl.Item(iInfostorescollindex)
   Wend


'This is the entryid for the Root public folder
        bstrPublicRootID = objInfoStore.Fields.Item( &H66310102 ).Value

	Set myrootfolder = objOMSession.GetFolder(bstrPublicRootID, objInfoStore.ID)
'Now get the folders collection below the root
	Set myfoldercollect = myrootfolder.Folders
	Set recursefolder = myfoldercollect.GetFirst()
'Recurse it until we get the folder we are looking for
	While recursefolder.Name <> "Techdesk"
	  Set recursefolder = myfoldercollect.GetNext()
	Wend



'Add a new message to the public folder
    Set oMessage = recursefolder.Messages.Add 

 'Set the message properties

    oMessage.Subject = Request("Subject")
    oMessage.Sent = True    
    oMessage.Unread = True
    oMessage.TimeSent = Now
    oMessage.TimeReceived = Now
    oMessage.Type = "IPM.Task.Help Request"
    oMessage.Importance = Request("Priority")
    oMessage.Fields.Add "From User", 8, Request.Form("Contact_Email")
    oMessage.Fields.Add "Description", 8, Request("Description")
    oMessage.Fields.Add "Problem Type", 8, Request("Type")
    oMessage.Fields.Add "Product", 8, Request("Product")
    oMessage.Fields.Add "Phone", 8, Request("Phone")
    oMessage.Fields.Add "User Location", 8, Request("Location")
    oMessage.Fields.Add "Flag", 8, "Opened"
    


    'Set the conversation properties
    oMessage.ConversationTopic = oMessage.Subject
    
'Post the message

  oMessage.Submitted = FALSE
  oMessage.Update 
  	
    Set oMessage = Nothing

  	 
%>






<HTML>

<HEAD>
<TITLE>Post Tech Request</TITLE>
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
<IMG SRC="/AdvWorks/multimedia/images/spacer.GIF" ALIGN=RIGHT WIDTH=110 ALT="Space">

<IMG SRC="/techdesk/outlook.GIF" ALIGN=RIGHT WIDTH=110 ALT="Space">

</TD>

<TD VALIGN=TOP ALIGN=LEFT COLSPAN=3><FONT SIZE=6>
<FONT SIZE=6 FACE="ARIAL NARROW" COLOR="#800000">Thank you for submitting your techdesk request!<BR>
<HR SIZE=4>
<a href="/techdesk/email.asp">Return to techdesk submit form</a>
<P>
<a href="/techdesk/render.asp">Browse current techdesk tickets</a>
</BODY>

</HTML>

