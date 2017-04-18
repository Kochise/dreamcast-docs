<!DOCTYPE HTML PUBLIC "-//IETF//DTD HTML//EN">
<html>

<head>
<meta http-equiv="Content-Type"
content="text/html; charset=iso-8859-1">
<meta name="GENERATOR" content="Microsoft FrontPage 2.0">
<title>Techdesk Resolved Form</title>
</head>

<body>



<%

'This code was written by Tom Rizzo (thomriz@microsoft.com)
'FYI, the message boxes will not work.  This is for debugging the code only

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
    set objMessageID = Request.QueryString("entryid")
    set oMessage = objOMSession.GetMessage(objMessageID, objInfoStore.ID)
'Set the message as read
    set msgstatus = oMessage.Fields("Flag")
    msgstatusid = msgstatus.ID
    oMessage.Fields(msgstatusid) = "Done"
    oMessage.Update

'Send a resolved message to the user stating that their problem was resolved
    Set objNewMsg = objOMSession.outbox.messages.add
    objNewMsg.Text = "Your problem: " & oMessage.Subject & " was resolved on " & Now & chr(10) & _
	chr(10) & "Please see the techdesk FAQ at http://tomexdemo/faq/ for commonly asked questions." 
    objNewMsg.Subject = "Resolved: " & oMessage.Subject      
    Set objonerecip = objNewMsg.recipients.add
    objonerecip.Name = oMessage.Fields("From User")
    objonerecip.Resolve   
'Update the message and send it without showing a dialog box
    objNewMsg.Update 
    objNewMsg.Send showDialog=False 

%>

<HTML>
<META HTTP-EQUIV="REFRESH" CONTENT="0; URL=/techdesk/render.asp?">

<!-- The techdesk page is located at	-->
<!-- email.asp.  Please make a note of it for future	-->
<!-- reference.						-->

</HTML>