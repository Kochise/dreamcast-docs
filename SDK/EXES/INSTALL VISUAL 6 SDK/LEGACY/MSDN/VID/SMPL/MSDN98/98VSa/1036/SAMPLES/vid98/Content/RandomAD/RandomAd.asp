<%@ LANGUAGE="VBSCRIPT" %>

<html>
<head>

</head>
<BODY bgColor=#ffffff leftMargin=40 link=#500000 vLink=#505050>

<%Set ad = Server.CreateObject("MSWC.AdRotator")%>

<%= ad.GetAdvertisement("RandomAd.txt") %>  
<br><br>
<FONT FACE="Verdana, Arial, Helvetica" SIZE=2>
<a HREF="javascript:location.href='RandomAd.asp'">Actualiser la page</a>
<br><br>
</font>

</body>
</html>
