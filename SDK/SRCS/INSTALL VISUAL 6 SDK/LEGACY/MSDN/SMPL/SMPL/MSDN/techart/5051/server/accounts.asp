<%
Dim iIndex
Dim sBuff

Response.Write("<strong>Accounts</strong>")
Response.Write("<hr>")
If Not Session("m_oBank") Is Nothing Then
    If Not Session("m_obank").Accounts Is Nothing Then
        For iIndex = 1 to Session("m_oBank").Accounts.Count
            Set oAcct = Session("m_oBank").Accounts(iIndex)
            sBuff = "<a href=""detact.asp" & "?iActNdx=" & Cstr(iIndex) & """ target=""acctdet"" >"
            sBuff = sBuff & oAcct.Number & "</a><br>" 
            Response.Write(sBuff)
        Next
    End If
End If
Set oAcct = Nothing
%>
