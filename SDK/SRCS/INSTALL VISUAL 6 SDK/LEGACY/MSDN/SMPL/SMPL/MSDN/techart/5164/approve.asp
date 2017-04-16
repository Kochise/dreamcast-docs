<%
Session("EntryID") = Request.QueryString("entryid")
Session("Approver") = Request.QueryString("Approver")
Response.Redirect "approve1.asp"
%>
