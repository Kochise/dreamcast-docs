<%
Dim iIndex
Dim sBuff

Response.Write("<strong>Banks</strong>")
Response.Write("<hr>")
Session("m_oAdmin").FillListbanks
For iIndex = 1 To Session("m_oAdmin").Banks.Count
    sBuff = "<a href=""bankdet.asp" & "?iBankNdx=" & Cstr(iIndex) & """ target=""bankdet"" >"
    sBuff = sBuff & Session("m_oAdmin").Banks(iIndex).Name & "</a><br>" 
    Response.Write(sBuff)
Next
%>
