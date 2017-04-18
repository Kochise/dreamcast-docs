<% @LANGUAGE="VBSCRIPT" %>
<HTML>
<HEAD> 
</HEAD>
<%
	' GetPrefixValue is a helper function which removes the 
	' document name from a fully-qualified URL
	Function GetPrefixValue
		Dim strFullPath, strLastChar
		strFullPath = "http://"
		strFullPath = strFullPath & Request.ServerVariables("SERVER_NAME")
		strFullPath = strFullPath & Request.ServerVariables("PATH_INFO")
		' now str has a value like: "http://servname/exair/freqflyer/default.asp"
		' we need to cut off the "/default.asp" part
		strLastChar = ""
		Do Until strLastChar = "/"
			strLastChar = right(strFullPath, 1)
			strFullPath = left(strFullPath, len(strFullPath) - 1)	
		Loop
		GetPrefixValue = strFullPath
	End Function
%>
<BODY bgColor=#ffffff leftMargin=40 link=#500000 vLink=#505050>
<BASEFONT FACE="VERDANA, ARIAL, HELVETICA" SIZE=2>
		<APPLET
			CODE=CoolHeadLines.class
			NAME=CoolHeadLines
			CODEBASE=Applets
			WIDTH=190
			HEIGHT=76>

			<PARAM NAME=BackColor VALUE="255 255 255">
			<PARAM NAME=TextColor VALUE="0 0 0">
			<PARAM NAME=HiliteTextColor VALUE="60 179 113">
			<PARAM NAME=ScrollDelay VALUE=10>
			<PARAM NAME=MessageDelay VALUE=4>	
	  		<PARAM NAME=URLPrefix VALUE="<%=GetPrefixValue()%>">

			'Build up the list of headlines
			<PARAM NAME=Text0 VALUE="Entr&#233;e des donn&#233;es">
			<PARAM NAME=URL0 VALUE="../Sample.asp?SampID=1">
			<PARAM NAME=Text1 VALUE="Citation du jour">
			<PARAM NAME=URL1 VALUE="../Sample.asp?SampID=2">
			<PARAM NAME=Text2 VALUE="Grille d&#233;pendante des donn&#233;es">
			<PARAM NAME=URL2 VALUE="../Sample.asp?SampID=3">
			<PARAM NAME=Text3 VALUE="Requ&#234;te personnalis&#233;e">
			<PARAM NAME=URL3 VALUE="../Sample.asp?SampID=4">
			<PARAM NAME=Text4 VALUE="Pr&#233;f&#233;rences de l'utilisateur">
			<PARAM NAME=URL4 VALUE="../Sample.asp?SampID=5">
			<PARAM NAME=Text5 VALUE="Compteur d'acc&#232;s">
			<PARAM NAME=URL5 VALUE="../Sample.asp?SampID=6">
			<PARAM NAME=Text6 VALUE="Enqu&#234;te">
			<PARAM NAME=URL6 VALUE="../Sample.asp?SampID=7">
			<PARAM NAME=Text7 VALUE="Utilisation des contr&#244;les">
			<PARAM NAME=URL7 VALUE="../Sample.asp?SampID=8">
			<PARAM NAME=Text8 VALUE="Chariot des courses">
			<PARAM NAME=URL8 VALUE="../Sample.asp?SampID=9">
			<PARAM NAME=Text9 VALUE="Notification de l'utilisateur">
			<PARAM NAME=URL9 VALUE="../Sample.asp?SampID=10">
			<PARAM NAME=Text10 VALUE="Livre d'or">
			<PARAM NAME=URL10 VALUE="../Sample.asp?SampID=12">
			<PARAM NAME=Text11 VALUE="Transitions et filtres">
			<PARAM NAME=URL11 VALUE="../Sample.asp?SampID=13">
			<PARAM NAME=Text12 VALUE="Chronologie">
			<PARAM NAME=URL12 VALUE="../Sample.asp?SampID=18">
			<PARAM NAME=Text13 VALUE="Publicit&#233; al&#233;atoire">
			<PARAM NAME=URL13 VALUE="../Sample.asp?SampID=15">
			<PARAM NAME=Text14 VALUE="Utilisation des th&#232;mes">
			<PARAM NAME=URL14 VALUE="../Sample.asp?SampID=16">
			<PARAM NAME=Text15 VALUE="Multim&#233;dia">
			<PARAM NAME=URL15 VALUE="../Sample.asp?SampID=17">
			<PARAM NAME=NumItems VALUE=16>
		</APPLET>
<BR>
Cette applet affiche les noms des autres exemples disponibles dans la Galerie. Pour plus 
d'informations sur un exemple particulier, cliquez sur le titre correspondant.
</BODY>
</HTML>