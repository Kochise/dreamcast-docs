<%@ LANGUAGE=VBScript %>
<% ' Modèle d'objet script VI 6.0 activé %>
<!--#include file="../_ScriptLibrary/pm.asp"-->
<% if StartPageProcessing() Then Response.End() %>
<FORM name=thisForm METHOD=post>
<HTML>
<BODY bgColor=#ffffff leftMargin=40 link=#500000 vLink=#505050>
<FONT FACE="Verdana, Arial, Helvetica" SIZE=2>

<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:9CF5D7C2-EC10-11D0-9862-0000F8027CA0" id=QuoteRecordset style="LEFT: 0px; TOP: 0px">
	<PARAM NAME="ExtentX" VALUE="12197">
	<PARAM NAME="ExtentY" VALUE="2090">
	<PARAM NAME="State" VALUE="(TCConn=\qGallery\q,TCDBObject=\qTables\q,TCDBObjectName=\qQuote\q,TCControlID_Unmatched=\qQuoteRecordset\q,TCPPConn=\qGallery\q,RCDBObject=\qRCDBObject\q,TCPPDBObject=\qTables\q,TCPPDBObjectName=\qQuote\q,TCCursorType=\q3\s-\sStatic\q,TCCursorLocation=\q3\s-\sUse\sclient-side\scursors\q,TCLockType=\q3\s-\sOptimistic\q,TCCacheSize_Unmatched=\q10\q,TCCommTimeout_Unmatched=\q10\q,CCPrepared=0,CCAllRecords=1,TCNRecords_Unmatched=\q10\q,TCODBCSyntax_Unmatched=\q\q,TCHTargetPlatform=\q\q,TCHTargetBrowser_Unmatched=\qServer\s(ASP)\q,TCTargetPlatform=\qInherit\sfrom\spage\q,RCCache=\qRCBookPage\q,CCOpen=1,GCParameters=(Rows=0))">
	<PARAM NAME="RelativePath" VALUE="../"></OBJECT>
-->
<!--#INCLUDE FILE="../_ScriptLibrary/Recordset.ASP"-->
<script language="JavaScript" runat="server">
function _initQuoteRecordset()
{
	var DBConn = Server.CreateObject('ADODB.Connection');
	DBConn.ConnectionTimeout = Application('Gallery_ConnectionTimeout');
	DBConn.CommandTimeout = Application('Gallery_CommandTimeout');
	DBConn.CursorLocation = Application('Gallery_CursorLocation');
	DBConn.Open(Application('Gallery_ConnectionString'), Application('Gallery_RuntimeUserName'), Application('Gallery_RuntimePassword'));
	var cmdTmp = Server.CreateObject('ADODB.Command');
	var rsTmp = Server.CreateObject('ADODB.Recordset');
	cmdTmp.ActiveConnection = DBConn;
	rsTmp.Source = cmdTmp;
	cmdTmp.CommandType = 2;
	cmdTmp.CommandTimeout = 10;
	cmdTmp.CommandText = '`Quote`';
	rsTmp.CacheSize = 10;
	rsTmp.CursorType = 3;
	rsTmp.CursorLocation = 3;
	rsTmp.LockType = 3;
	QuoteRecordset.setRecordSource(rsTmp);
	QuoteRecordset.open();
	if (thisPage.getState('pb_QuoteRecordset') != null)
		QuoteRecordset.setBookmark(thisPage.getState('pb_QuoteRecordset'));
}
function _QuoteRecordset_ctor()
{
	CreateRecordset('QuoteRecordset', _initQuoteRecordset, null);
}
function _QuoteRecordset_dtor()
{
	QuoteRecordset._preserveState();
	thisPage.setState('pb_QuoteRecordset', QuoteRecordset.getBookmark());
}
</script>

<!--METADATA TYPE="DesignerControl" endspan-->
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B5F0E460-DC5F-11D0-9846-0000F8027CA0" height=17 id=txtQuote 
	style="HEIGHT: 17px; LEFT: 0px; TOP: 0px; WIDTH: 33px" width=33>
	<PARAM NAME="_ExtentX" VALUE="900">
	<PARAM NAME="_ExtentY" VALUE="450">
	<PARAM NAME="id" VALUE="txtQuote">
	<PARAM NAME="DataSource" VALUE="QuoteRecordset">
	<PARAM NAME="DataField" VALUE="Quote">
	<PARAM NAME="FontFace" VALUE="">
	<PARAM NAME="FontSize" VALUE="">
	<PARAM NAME="FontColor" VALUE="">
	<PARAM NAME="FontBold" VALUE="0">
	<PARAM NAME="FontItalic" VALUE="0">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="FormatAsHTML" VALUE="0">
	<PARAM NAME="Platform" VALUE="0">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<!--#INCLUDE FILE="../_ScriptLibrary/Label.ASP"-->
<script runat="server" language="JavaScript">
function _inittxtQuote()
{
   txtQuote.setDataSource(QuoteRecordset);
   txtQuote.setDataField('Quote');
}
function _txtQuote_ctor()
{
   CreateLabel('txtQuote', _inittxtQuote, null);
}
</script>
<% txtQuote.display %>

<!--METADATA TYPE="DesignerControl" endspan-->
<br>
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B5F0E460-DC5F-11D0-9846-0000F8027CA0" height=17 id=txtAuthor 
	style="HEIGHT: 17px; LEFT: 0px; TOP: 0px; WIDTH: 41px" width=41>
	<PARAM NAME="_ExtentX" VALUE="979">
	<PARAM NAME="_ExtentY" VALUE="450">
	<PARAM NAME="id" VALUE="txtAuthor">
	<PARAM NAME="DataSource" VALUE="QuoteRecordset">
	<PARAM NAME="DataField" VALUE="Author">
	<PARAM NAME="FontFace" VALUE="">
	<PARAM NAME="FontSize" VALUE="">
	<PARAM NAME="FontColor" VALUE="Navy">
	<PARAM NAME="FontBold" VALUE="0">
	<PARAM NAME="FontItalic" VALUE="-1">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="FormatAsHTML" VALUE="0">
	<PARAM NAME="Platform" VALUE="0">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<FONT COLOR="Navy"><I>
<script runat="server" language="JavaScript">
function _inittxtAuthor()
{
   txtAuthor.setDataSource(QuoteRecordset);
   txtAuthor.setDataField('Author');
}
function _txtAuthor_ctor()
{
   CreateLabel('txtAuthor', _inittxtAuthor, null);
}
</script>
<% txtAuthor.display %>
</FONT></I>

<!--METADATA TYPE="DesignerControl" endspan-->
<BR><BR>

<SCRIPT LANGUAGE=vbscript RUNAT=Server>
	Sub QuoteRecordset_ondatasetcomplete()
		Randomize()
		intQuote = Int((QuoteRecordset.getCount()) * Rnd + 1)
		QuoteRecordset.moveAbsolute(intQuote)
	End sub
</SCRIPT>
<A HREF="javascript:location.href='quote.asp'">Actualiser la page</A>

</FONT>
</BODY>
<% ' Modèle d'objet script VI 6.0 activé %>
<% EndPageProcessing() %>
</FORM>
</HTML>
