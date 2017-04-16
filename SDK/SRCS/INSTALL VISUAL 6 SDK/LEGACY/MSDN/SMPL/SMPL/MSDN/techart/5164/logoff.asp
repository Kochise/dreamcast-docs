<%
'<!--Copyright (c) Microsoft Corporation 1993-1997. All rights reserved.-->
%>
<!DOCTYPE HTML PUBLIC "-//IETF//DTD HTML 3.2//EN"> 
<HTML>
<HEAD>
</HEAD>
<BODY>

Abandoning Denali session.  This will logoff AM session.<br><br>

<% 
' This will trigger Session_OnEnd in global.asa.  It would also be possible
' to explicitly logoff here and set all Session objects to Nothing
    Session.Abandon 
%>

<a href="logon.asp">Logon.asp</a>

</BODY>
</HTML>
