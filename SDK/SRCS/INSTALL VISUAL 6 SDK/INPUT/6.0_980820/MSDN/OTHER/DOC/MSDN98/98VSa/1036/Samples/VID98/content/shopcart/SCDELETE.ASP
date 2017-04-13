<%@ LANGUAGE=VBScript %>
<% ' VI 6.0 Scripting Object Model Enabled %>
<!--#include file="../_ScriptLibrary/pm.asp"-->
<% if StartPageProcessing() Then Response.End() %>
<FORM name=thisForm METHOD=post>
<HTML>
<BODY>
<SCRIPT LANGUAGE=javascript RUNAT=Server>
	function DTCRecordset1_onbeforeopen() {
		newSQL = "SELECT * FROM ShopCart WHERE (SessionID = '" + Session.SessionID + "') AND (ProductID = " + Request('ProdID') + ")";
		DTCRecordset1.setSQLText(newSQL);
	}
	
	function DTCRecordset1_ondatasetcomplete() {
		DTCRecordset1.deleteRecord();
		response.Redirect("ViewCart.asp");
	}
</SCRIPT>
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:9CF5D7C2-EC10-11D0-9862-0000F8027CA0" id=DTCRecordset1 style="LEFT: 0px; TOP: 0px">
	<PARAM NAME="ExtentX" VALUE="12197">
	<PARAM NAME="ExtentY" VALUE="2090">
	<PARAM NAME="State" VALUE="(TCConn=\qGallery\q,TCDBObject_Unmatched=\qSQL\sStatement\q,TCDBObjectName_Unmatched=\qSelect\s*\sfrom\sShopCart\r\n\q,TCControlID_Unmatched=\qDTCRecordset1\q,TCPPConn=\qGallery\q,TCPPDBObject=\qTables\q,TCPPDBObjectName=\qCounter\q,RCDBObject=\qRCSQLStatement\q,TCSQLStatement_Unmatched=\qSelect\s*\sfrom\sShopCart\r\n\q,TCCursorType=\q3\s-\sStatic\q,TCCursorLocation=\q3\s-\sUse\sclient-side\scursors\q,TCLockType=\q3\s-\sOptimistic\q,TCCacheSize_Unmatched=\q10\q,TCCommTimeout_Unmatched=\q10\q,CCPrepared=0,CCAllRecords=1,TCNRecords_Unmatched=\q10\q,TCODBCSyntax_Unmatched=\q\q,TCHTargetPlatform=\q\q,TCHTargetBrowser_Unmatched=\qServer\s(ASP)\q,TCTargetPlatform=\qInherit\sfrom\spage\q,RCCache=\qRCBookPage\q,CCOpen=1,GCParameters=(Rows=0))">
	<PARAM NAME="RelativePath" VALUE="../"></OBJECT>
-->
<!--#INCLUDE FILE="../_ScriptLibrary/Recordset.ASP"-->
<script language="JavaScript" runat="server">
function _initDTCRecordset1()
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
	cmdTmp.CommandType = 1;
	cmdTmp.CommandTimeout = 10;
	cmdTmp.CommandText = 'Sélectionner * dans Chariot des courses';
	rsTmp.CacheSize = 10;
	rsTmp.CursorType = 3;
	rsTmp.CursorLocation = 3;
	rsTmp.LockType = 3;
	DTCRecordset1.setRecordSource(rsTmp);
	DTCRecordset1.open();
	if (thisPage.getState('pb_DTCRecordset1') != null)
		DTCRecordset1.setBookmark(thisPage.getState('pb_DTCRecordset1'));
}
function _DTCRecordset1_ctor()
{
	CreateRecordset('DTCRecordset1', _initDTCRecordset1, null);
}
function _DTCRecordset1_dtor()
{
	DTCRecordset1._preserveState();
	thisPage.setState('pb_DTCRecordset1', DTCRecordset1.getBookmark());
}
</script>

<!--METADATA TYPE="DesignerControl" endspan-->
</BODY>
<% ' VI 6.0 Scripting Object Model Enabled %>
<% EndPageProcessing() %>
</FORM>
</HTML>
