<%@ LANGUAGE="VBSCRIPT" %>

<%If InStr(Request.ServerVariables("HTTP_User_Agent"),"MSIE 4") = 0 then%>
Cet exemple requiert Microsoft Internet Explorer version 4.0 ou ultérieure.
<%Else%>
<FRAMESET ROWS="90,*" FRAMESPACING=0>
	<FRAME NAME=Header SRC=IE4.htm SCROLLING=None NORESIZE FRAMEBORDER=0>
	<FRAME NAME=IE4Main SRC=Main.htm SCROLLING=Auto NORESIZE FRAMEBORDER=0>
</FRAMESET>
<%End If%>


