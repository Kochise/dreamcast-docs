<%

Dim sNewNumber
Dim lNewType
Dim Result
        
'create a new account object if NewAccount flag is set
If Session("bNewAccount") Then
    Set Session("m_oAccount") = Server.CreateObject("BankSrv.CAccount")
    Set Session("m_oAccount").Admin = Session("m_oAdmin")
    Set Session("m_oAccount").bank = Session("m_obank")
End if
 
'get account number from interface
sNewNumber = Cstr(Request.Form("AcctNumber"))
Session("m_oAccount").Number = sNewNumber
     
'get account typeid from interface
lNewType = CLng(request.Form("AcctTypeId"))
Session("m_oAccount").TypeID = lNewType
    
'insert or update via data services based on NewAccount flag
If Session("bNewAccount") Then
    Result = Session("m_oAdmin").Insert(, Session("m_oAccount"))     
Else
    Result = Session("m_oAdmin").Update(, Session("m_oAccount"))
End If

'write return value from transaction to interface
Response.Write(CStr(Result))

%>
