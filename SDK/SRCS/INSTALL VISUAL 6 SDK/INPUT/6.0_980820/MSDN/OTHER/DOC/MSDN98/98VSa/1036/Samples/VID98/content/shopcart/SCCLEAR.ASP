<%@ LANGUAGE=VBScript %>
<% ' Modèle d'objet script VI 6.0 activé %>
<!--#include file="../_ScriptLibrary/pm.asp"-->
<% if StartPageProcessing() Then Response.End() %>
<FORM name=thisForm METHOD=post>
<HTML>
<BODY>
<SCRIPT LANGUAGE=javascript RUNAT=Server>
	function DTCRecordset1_onbeforeopen() {
		newSQL = "SELECT * FROM ShopCart WHERE (SessionID = '" + Session.SessionID + "')";
		DTCRecordset1.setSQLText(newSQL);
	}
</SCRIPT>

<SCRIPT LANGUAGE=VBscript RUNAT=Server>
	Sub DTCRecordset1_ondatasetcomplete()
		Do while not DTCRecordset1.EOF
			DTCRecordset1.deleteRecord()
			DTCRecordset1.moveNext()
		Loop
		response.Redirect("SCMain.htm")
	End Sub
</SCRIPT>

<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:9CF5D7C2-EC10-11D0-9862-0000F8027CA0" id=DTCRecordset1 style="LEFT: 0px; TOP: 0px">
	<PARAM NAME="ExtentX" VALUE="12197">
	<PARAM NAME="ExtentY" VALUE="2090">
	<PARAM NAME="State" VALUE="(TCConn=\qGallery\q,TCDBObject_Unmatched=\qSQL\sStatement\q,TCDBObjectName_Unmatched=\qSelect\s*\sfrom\sShopCart\q,TCControlID_Unmatched=\qDTCRecordset1\q,TCPPConn=\qGallery\q,TCPPDBObject=\qTables\q,TCPPDBObjectName=\qShopCart\q,RCDBObject=\qRCSQLStatement\q,TCSQLStatement_Unmatched=\qSelect\s*\sfrom\sShopCart\q,TCCursorType=\q3\s-\sStatic\q,TCCursorLocation=\q3\s-\sUse\sclient-side\scursors\q,TCLockType=\q3\s-\sOptimistic\q,TCCacheSize_Unmatched=\q10\q,TCCommTimeout_Unmatched=\q10\q,CCPrepared=0,CCAllRecords=1,TCNRecords_Unmatched=\q10\q,TCODBCSyntax_Unmatched=\q\q,TCHTargetPlatform=\q\q,TCHTargetBrowser_Unmatched=\qServer\s(ASP)\q,TCTargetPlatform=\qInherit\sfrom\spage\q,RCCache=\qRCNoCache\q,CCOpen=1,GCParameters=(Rows=0))">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<!--#INCLUDE FILE="../_ScriptLibrary/Recordset.ASP"-->
<SCRIPT LANGUAGE="JavaScript" RUNAT="server">
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
	cmdTmp.CommandText = 'Select * from ShopCart';
	rsTmp.CacheSize = 10;
	rsTmp.CursorType = 3;
	rsTmp.CursorLocation = 3;
	rsTmp.LockType = 3;
	DTCRecordset1.setRecordSource(rsTmp);
	DTCRecordset1.open();
}
function _DTCRecordset1_ctor()
{
	CreateRecordset('DTCRecordset1', _initDTCRecordset1, null);
}
</SCRIPT>

<!--METADATA TYPE="DesignerControl" endspan-->
</BODY>
<% ' Modèle d'objet script VI 6.0 activé %>
<% EndPageProcessing() %>
</FORM>
</HTML>
