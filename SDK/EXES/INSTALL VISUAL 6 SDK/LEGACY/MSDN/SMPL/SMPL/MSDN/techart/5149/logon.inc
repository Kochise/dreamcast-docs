<%
' logon.inc.  VBScript methods to create and check an ActiveMessaging session

'============================
' ReportError
' 
'============================
Function ReportError( bstrContext)

	ReportError= False

	If Err.Number <> 0 Then
		Response.Write( "Error: " & bstrContext & " : " & Err.Number & ": " & Err.Description & "<br>")
		Err.Clear
		ReportError= True
	End If

End Function


'============================
' AuthenticateUser
' Ensures user is authenticated
' Note that this implies that Basic authentication is enabled on the IIS server
'============================
Public Function BAuthenticateUser
	On Error Resume Next
'	Response.Write( "In BAuthenticateUser<br>")

	BAuthenticateUser = False

	bstrAT = Request.ServerVariables("AUTH_TYPE")


    If InStr(1, "_BasicNTLM", bstrAT, vbTextCompare) < 2 Then
		Response.Buffer = TRUE
		Response.Status = ("401 Unauthorized")
		Response.AddHeader "WWW.Authenticate", "Basic"
		Response.End
	Else
		BAuthenticateUser = True
	End If

End Function


'============================
' CheckAMSession
' 
' Checks for and returns the AM session in the Sesion object.  If not found,
' calls NoSession().
' Call this before emiting any HTML or any redirects, authentication, etc. may not work.
' Returns: True if session exists or can be created
'============================
Public Function CheckAMSession()
	On Error Resume Next
'	Response.Write( "In GetSession<br>")

	Dim amSession

	CheckAMSession= False

	Set amSession= Session( "AMSession")

	If amSession Is Nothing Then
		NoSession
		amSession= Session( "AMSession")
	End If

	If Not amSession Is Nothing Then
		CheckAMSession= true
	End If		

End Function


'============================
' NoSession
' 
' Called when the AM session can not be found.  Either creates a session or gets
' more info from the user.  Returns only if the session was created.
' 
'============================
Sub NoSession()
	On Error Resume Next

	Dim bstrMailbox
	Dim bstrServer
	Dim bstrProfileInfo
	Dim objAMSession1
	Dim objRenderApp
	Dim objInbox

	bstrServer = "tomexdemo"
	bstrMailbox = Request.Form("Contact_Email")
	' must be authenticated to sucessfully logon
	BAuthenticateUser

	Err.Clear
	Set objAMSession1 = Server.CreateObject("MAPI.Session")

	If Not ReportError( "create MAPI.Session") Then

		set objRenderApp = Application( "RenderApplication" )

		' Construct the ActiveMessaging profile from server and mailbox name
		bstrProfileInfo = bstrServer + vbLF + bstrMailbox

		Err.Clear
		objAMSession1.Logon "", "", False, True, 0, True, bstrProfileInfo 

		If Not ReportError( "ActiveMessaging Logon") Then
		' To ensure that we are really logged on, we need to try retrieving
		' some data.
			Err.Clear
			Set objInbox = objAMSession1.Inbox

			If ReportError( "Get Inbox") Then
			' The logon is no good.  We'll do a little cleanup here.
				objAMSession1.Logoff
				Set objAMSession1 = Nothing
			End If

			' This will be retrieved back up in CheckSession
			' Note that if the logon failed this is set to 'Nothing'
			Set Session("AMSession") = objAMSession1

			' Need this to recreate the proper security context in Session_OnEnd
			Session("hImp") = objRenderApp.ImpID

 		End If    'objAMSession1.Logon
	End If   'Server.CreateObject()

End Sub

'==============================
' GetConfig
'
' Finds a server and mailbox name to use to login with.  This sample returns
' a form to the user requesting the information.  By replacing this subroutine,
' the data could come from anywhere else (a database, hardcoded, etc.)
'==============================
Sub GetConfig( byRef bstrServer, byRef bstrMailbox)

	bstrMailbox= Request.QueryString( "Mailbox")
	bstrServer = Request.QueryString( "Server")
	if bstrMailbox = "" or bstrServer= "" Then 
		' we need to get information from the user.  This is either the first time
		' through, or maybe the session timed out
		Response.Write("<html><head><title> AM authenticated logon page </title></head>")
		Response.Write("<body><FORM METHOD=GET WINDOW=_self><TABLE>")
		
		Response.Write("<tr><td>Please enter your email name:</td><td><input TYPE=TEXT SIZE=20 NAME=""Mailbox""></td></tr>")
		Response.Write("</TABLE><P><INPUT TYPE=""SUBMIT"" VALUE=""OK""><INPUT TYPE=""RESET"" VALUE=""Reset""></FORM>")
		' nothing after the next line will be executed
		Response.End
	End If

End Sub

%>