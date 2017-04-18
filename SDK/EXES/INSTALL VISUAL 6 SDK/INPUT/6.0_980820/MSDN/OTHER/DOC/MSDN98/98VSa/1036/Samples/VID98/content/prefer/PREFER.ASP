<%@ LANGUAGE="VBSCRIPT" %>

<%
'	************************************************
'	After the form posts back to this ASP, the
'	values are written to a cookie.
'	************************************************
If Len(Request("BGColor")) > 0 then
	Response.Cookies("BGColor") = Request("BGColor")
	Response.Cookies("FGColor") = Request("FGColor")
End If

'	************************************************
'	If this ASP has not been run before, there will
'	not be any cookies saved.  The index values for
'	the drop-down select boxes are set to zero.
'	************************************************
If Request.Cookies("intBGColor") = "" then
	intBG = 0
	intFG = 0
Else
	intBG = Request.Cookies("intBGColor")
	intFG = Request.Cookies("intFGColor")
End If

%>

<script LANGUAGE="Javascript">
/*	
	************************************************
	This function is used to set the color of the 
	drop-down select boxes. The values are retrieved
	from a cookie stored on the client machine.
	************************************************
*/
	function setcolor() {
		document.Pref.BGColor.selectedIndex = <%=intBG%>;
		document.Pref.FGColor.selectedIndex = <%=intFG%>;
	}

/*	
	************************************************
	This function is used to write the index value
	of the drop-down select boxes into a cookie.  
	************************************************
*/

	function writecookie() {
		document.cookie = "intBGColor" + "=" + document.Pref.BGColor.selectedIndex;
		document.cookie = "intFGColor" + "=" + document.Pref.FGColor.selectedIndex;
	}

</script>

<html>
<!-- Sets the background color of the window to the value stored in a cookie -->
<BODY leftMargin=40 link=#500000 vLink=#505050 BGCOLOR="<%= Request.Cookies("BGColor")%>" ONLOAD="setcolor()">

<!-- Sets the font color to the value stored in a cookie -->
<font FACE="Verdana, Arial, Helvetica" COLOR="<%=Request.Cookies("FGColor")%>">

<!-- This form posts to this same ASP to reload based on selected values -->
<form NAME="Pref" ACTION="Prefer.asp" METHOD="Post" ONSUBMIT="writecookie()">
<table CELLSPACING="0" BORDER="1">
<tr>
  <td BGCOLOR="White"><font SIZE="2" FACE="Arial, Helvetica, Verdana">Fond :</font></td>
  <td BGCOLOR="White">
	<select NAME="BGColor">
	  <option VALUE="AQUA">BLEU CLAIR
	  <option VALUE="BLACK">NOIR
	  <option VALUE="BLUE">BLEU
	  <option VALUE="FUCHSIA">FUCHSIA
	  <option VALUE="GRAY">GRIS
	  <option VALUE="GREEN">VERT
	  <option VALUE="LIME">CITRON VERT
	  <option VALUE="MAROON">MARRON
	  <option VALUE="NAVY">BLEU FONCÉ
	  <option VALUE="OLIVE">OLIVE
	  <option VALUE="PURPLE">VIOLET
	  <option VALUE="RED">ROUGE
	  <option VALUE="SILVER">ARGENT
	  <option VALUE="TEAL">BLEU-VÉRITÉ
	  <option VALUE="WHITE">BLANC
	  <option VALUE="YELLOW">JAUNE
	</select>
  </td>
</tr>

<tr>
  <td BGCOLOR="White"><font SIZE="2" FACE="Arial, Helvetica, Verdana">Texte :</font></td>
  <td BGCOLOR="White">
    <select NAME="FGColor">
	  <option VALUE="AQUA">BLEU CLAIR
	  <option VALUE="BLACK">NOIR
	  <option VALUE="BLUE">BLEU
	  <option VALUE="FUCHSIA">FUCHSIA
	  <option VALUE="GRAY">GRIS
	  <option VALUE="GREEN">VERT
	  <option VALUE="LIME">CITRON VERT
	  <option VALUE="MAROON">MARRON
	  <option VALUE="NAVY">BLEU FONCÉ
	  <option VALUE="OLIVE">OLIVE
	  <option VALUE="PURPLE">VIOLET
	  <option VALUE="RED">ROUGE
	  <option VALUE="SILVER">ARGENT
	  <option VALUE="TEAL">BLEU-VÉRITÉ
	  <option VALUE="WHITE">BLANC
	  <option VALUE="YELLOW">JAUNE
    </select>
  </td>
</tr>
<tr>
 <td COLSPAN="2" BGCOLOR="White" ALIGN="Center"><input TYPE="Submit" VALUE="Définir">
 </td>
</tr>
</table>
</form>

Exemple de texte illustrant la couleur.

<br><br>

</font>
</body>
</html>
