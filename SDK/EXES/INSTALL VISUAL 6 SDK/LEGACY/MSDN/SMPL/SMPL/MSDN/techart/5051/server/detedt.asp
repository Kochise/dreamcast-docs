<%
Dim sBuff

'retrieve new account flag from session object
Session("bNewAccount") = cBool(Request.QueryString("bNewAccount"))

'create an editing form for the account
Response.Write("<form name = ""account"" method=""post"" action=""commit.asp"" >")
Response.Write("Account Number<br>")
sBuff = "<input type=text Name=""AcctNumber"" "
If Not(Session("bNewAccount")) Then
    sBuff = sBuff & "value=""" & Session("m_oAccount").Number & """"
End If
sBuff = sBuff & "><br>"
Response.Write(sBuff)
Response.Write("Account Type<br>")
sBuff = "<input type=text Name=""AcctTypeId"" "
If Not(Session("bNewAccount")) Then
    sBuff = sBuff & "value=""" & Session("m_oAccount").TypeID & """"
End If
sBuff = sBuff & "><br>"
Response.Write(sBuff)
Response.Write("<br>")
Response.Write("<input type=submit value=""Commit"" >")
Response.Write("</form>")

%>