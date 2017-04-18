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


'Step 1 - Log in to Exchange using a MAPI Session

	Set objOMSession = Server.CreateObject("MAPI.Session")

	bstrProfileInfo = "dec101" & chr(10) & "testuser"
'			   ^^^^^^^^^ Your server   ^^^^^^ Username

		objOMSession.Logon "", "", False, True, 0, True, bstrProfileInfo 

'Step 1 and 1/2
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

'Step 2 find the correct information store for the message

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


'Step 3 find the correct folder in the information store

        bstrPublicRootID = objInfoStore.Fields.Item( &H66310102 ).Value

	Set myrootfolder = objOMSession.GetFolder(bstrPublicRootID, objInfoStore.ID)
	Set myfoldercollect = myrootfolder.Folders
	Set recursefolder = myfoldercollect.GetFirst()
'Recurse it until we get the folder we are looking for
	While recursefolder.Name <> "Techdesk"
	  Set recursefolder = myfoldercollect.GetNext()
	Wend
	set objFolder = recursefolder
    

'Step 4 Create Rendering Application

        set objRenderApp = Server.CreateObject("AMHTML.Application")
	'Create Container Renderer id=3

        Set objrenderer = objRenderApp.CreateRenderer(3)

	'Set oMsgCol equal to the objext collection

	Set oMsgCol = objFolder.Messages
	
	'Set the datasource for the rendering object to the techdesk public folder
	objrenderer.DataSource = oMsgCol

'Step 5 Get the views collection of the folder
	set objviews = objrenderer.views	


'Step 6 Set the correct view on the Folder
	set objview = objviews.Item("Techdesk")

'Step 7 Get the columns of the view
	set objcolumns = objview.Columns



'Step 8 Change the 3rd column so that it renders as an href

	set objcolumn = objcolumns.Item(3)
	'Change the column renderer so it renders the subject field as an ahref with
	'the entry id of the message
	objcolumn.RenderUsing = "<a href='/techdesk/message.asp?entryid=%obj%'>%value%</a>" 
		
	
	
	
	
	
'Step 9 Set the current view equal to the view just selected
	objrenderer.CurrentView = objview

'Step 10 Render the object
%>


<HTML>


<FONT FACE="MS SANS SERIF" SIZE=2>
<Table>
<TR>
<TD>
<FORM ACTION="/techdesk/render.asp?view=Techdesk" METHOD=POST>
<INPUT TYPE=SUBMIT NAME="Techdesk" VALUE="View by Date">
</Form>
</TD>
<TD>
<FORM ACTION="/techdesk/render.asp?view=From" METHOD=POST>
<INPUT TYPE=SUBMIT NAME="From" VALUE="View by Customer">
</Form>
</TD>
<TD>
<FORM ACTION="/techdesk/render.asp?view=Status" METHOD=POST>
<INPUT TYPE=SUBMIT NAME="Status" VALUE="View by Status">
</Form>
</TD>
</TR>
</Table>
<table border="0" width="65%">
    <tr>
        <td><% objRenderer.Render 1,0,0,Response %></td>
    </tr>
</table>

</Body>
</HTML>


