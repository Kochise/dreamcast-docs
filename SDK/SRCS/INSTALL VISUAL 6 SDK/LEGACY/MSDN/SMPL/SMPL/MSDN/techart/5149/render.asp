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


'Get the users Session object

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
    
	'Create Rendering Application
        set objRenderApp = Server.CreateObject("AMHTML.Application")
	'Create Container Renderer id=3

        Set objrenderer = objRenderApp.CreateRenderer(3)

	'Set oMsgCol equal to the objext collection

	Set oMsgCol = objFolder.Messages
	
	'Set the datasource for the rendering object to the techdesk public folder
	objrenderer.DataSource = oMsgCol


	'Get the requested view from the query string
	requestedview = Request.QueryString("view")

	'Get the folder views collection
	set objviews = objrenderer.views	
	'If there is no selected view, set it to techdesk view created in Outlook
	
	if requestedview = "" then 
             requestedview = "Techdesk"
	end if
	'Search the view collection until you find the view
	i=1
	While objviews.item(i).Name <> requestedview
		i=i+1
	Wend
	set objview = objviews.Item(i)
	set objcolumns = objview.Columns
	


	set objcolumn = objcolumns.Item(3)
	'Change the column renderer so it renders the subject field as an ahref with
	'the entry id of the message
	objcolumn.RenderUsing = "<a href='/techdesk/message.asp?entryid=%obj%'>%value%</a>" 
		
	
	
	
	
	
	'Set the current view equal to the view just selected
	objrenderer.CurrentView = objview
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


