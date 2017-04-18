<%
Server.ScriptTimeout=600
Response.Buffer=True
Response.Expires=0

If (VarType(Application("~WC~WebClassManager")) = 0) Then
	Application.Lock
	If (VarType(Application("~WC~WebClassManager")) = 0) Then
		Set Application("~WC~WebClassManager") = CreateObject("WebClassRuntime.WebClassManager")
	End If
	Application.UnLock
End If

Application("~WC~WebClassManager").ProcessNoStateWebClass "wcDemo.wbcls1", _
		Server, _
		Application, _
		Session, _
		Request, _
		Response
%>
