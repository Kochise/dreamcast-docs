<%

Dim iIndex

'retrieve account index from request query string
iIndex = Cint(Request.QueryString("iActNdx")) 

'set session account object to requested account
Set Session("m_oAccount") = Session("m_oBank").Accounts(iIndex)

'write account detail to interface
Response.Write("Account Number  - " & Session("m_oAccount").Number & "<br>")
Response.Write("Account Type  - " & Session("m_oAccount").TypeID & "<br>")
Response.Write("Account Balance - " & FormatCurrency(Session("m_oAccount").Balance) & "<br>")
Response.Write("<br>")
Response.Write("<a href=""detedt.asp?bNewAccount=0"">Edit</a><br>")
Response.Write("<a href=""detedt.asp?bNewAccount=1"">New</a><br>")

%>