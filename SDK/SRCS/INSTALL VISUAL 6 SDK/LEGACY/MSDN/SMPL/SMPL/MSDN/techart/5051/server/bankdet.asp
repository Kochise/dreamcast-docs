<%
    Dim iIndex
    Dim cPos
    Dim cNeg
    Dim oAcct
    Dim sBuff
    
    On Error resume Next
    
    'get the bank id from the QueryString and set the session bank object
    iIndex = Cint(Request.QueryString("iBankNdx")) 
    Set Session("m_oBank") = Session("m_oAdmin").Banks(iIndex)

    'walk the bank accounts to total balance
    For iIndex = 1 to Session("m_oBank").Accounts.Count
        Set oAcct = Session("m_oBank").Accounts(iIndex)
        If oAcct.Balance > 0 Then
            cPos = cPos + oAcct.Balance
        Else
            cNeg = cNeg + oAcct.Balance
        End If
    Next
    Set oAcct = Nothing

    'write bank detail to frame
    Response.Write("Bank    - " & Session("m_oBank").Name & "<br>")
    Response.Write("Code    - " & Session("m_oBank").Code & "<br>")
    Response.Write("Address - " & Session("m_oBank").Address1 & "<br>")
    Response.Write("          " & Session("m_oBank").Address2 & "<br>")
    Response.Write("City    - " & Session("m_oBank").City & "<br>")
    Response.Write("Type    - " & Session("m_oBank").TypeId & "<br>")
    Response.Write("Credits - " & FormatCurrency(cPos) & "<br>")
    Response.Write("Debits  - " & FormatCurrency(cNeg) & "<br>")
    Response.Write("Net Val - " & FormatCurrency(cPos + cNeg) & "<br>")
  
    'The following code refreshes the accounts and account detail frames using client-side script.
    'Omit it to refresh these frames manually and maintain compatibility with non-script browsers
    sBuff = "<SCRIPT Language=""VbScript""> "
    sBuff = sBuff & "top.accounts.location.href = ""accounts.asp"" "
    sBuff= sBuff & "</SCRIPT>"
    Response.Write(sBuff)
    sBuff = "<SCRIPT Language=""VbSCript""> "
    sBuff = sBuff & "top.acctdet.location.href = ""empty.asp"" "
    sBuff= sBuff & "</SCRIPT>"
    Response.Write(sBuff)

%>
