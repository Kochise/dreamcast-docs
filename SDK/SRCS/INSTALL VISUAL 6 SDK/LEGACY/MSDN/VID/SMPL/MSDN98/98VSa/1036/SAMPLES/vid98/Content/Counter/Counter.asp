<%@ LANGUAGE=VBScript %>
<% ' Modèle d'objet script VI 6.0 activé %>
<!--#include file="../_ScriptLibrary/pm.asp"-->
<% if StartPageProcessing() Then Response.End() %>
<FORM name=thisForm METHOD=post>
<HTML>
<HEAD>
<META NAME="GENERATOR" Content="Microsoft Visual Studio 6.0">
<META HTTP-EQUIV="Content-Type" content="text/html">
</HEAD>
<BODY bgColor=#ffffff leftMargin=40 link=#500000 vLink=#505050>
<FONT FACE="Verdana, Arial, Helvetica" SIZE=2>

<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:9CF5D7C2-EC10-11D0-9862-0000F8027CA0" id=CounterRecordset style="LEFT: 0px; TOP: 0px">
	<PARAM NAME="ExtentX" VALUE="12197">
	<PARAM NAME="ExtentY" VALUE="2090">
	<PARAM NAME="State" VALUE="(TCConn=\qGallery\q,TCDBObject=\qTables\q,TCDBObjectName=\qCounter\q,TCControlID_Unmatched=\qCounterRecordset\q,TCPPConn=\qGallery\q,RCDBObject=\qRCDBObject\q,TCPPDBObject=\qTables\q,TCPPDBObjectName=\qCounter\q,TCCursorType=\q3\s-\sStatic\q,TCCursorLocation=\q3\s-\sUse\sclient-side\scursors\q,TCLockType=\q3\s-\sOptimistic\q,TCCacheSize_Unmatched=\q10\q,TCCommTimeout_Unmatched=\q10\q,CCPrepared=0,CCAllRecords=1,TCNRecords_Unmatched=\q10\q,TCODBCSyntax_Unmatched=\q\q,TCHTargetPlatform=\q\q,TCHTargetBrowser_Unmatched=\qServer\s(ASP)\q,TCTargetPlatform=\qInherit\sfrom\spage\q,RCCache=\qRCBookPage\q,CCOpen=1,GCParameters=(Rows=0))">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<!--#INCLUDE FILE="../_ScriptLibrary/Recordset.ASP"-->
<SCRIPT LANGUAGE="JavaScript" RUNAT="server">
function _initCounterRecordset()
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
	cmdTmp.CommandText = '`Counter`';
	rsTmp.CacheSize = 10;
	rsTmp.CursorType = 3;
	rsTmp.CursorLocation = 3;
	rsTmp.LockType = 3;
	CounterRecordset.setRecordSource(rsTmp);
	CounterRecordset.open();
	if (thisPage.getState('pb_CounterRecordset') != null)
		CounterRecordset.setBookmark(thisPage.getState('pb_CounterRecordset'));
}
function _CounterRecordset_ctor()
{
	CreateRecordset('CounterRecordset', _initCounterRecordset, null);
}
function _CounterRecordset_dtor()
{
	CounterRecordset._preserveState();
	thisPage.setState('pb_CounterRecordset', CounterRecordset.getBookmark());
}
</SCRIPT>

<!--METADATA TYPE="DesignerControl" endspan-->

<SCRIPT LANGUAGE=javascript RUNAT=Server>
	function CounterRecordset_ondatasetcomplete(){
		fieldsArray = new Array("Remote_Host","Path_Info","HTTP_User_Agent");
		valuesArray = new Array(Request.ServerVariables("Remote_Addr"), Request.ServerVariables("Path_Info"), Request.ServerVariables("HTTP_User_Agent"));
		CounterRecordset.addImmediate(fieldsArray, valuesArray);
	}
</SCRIPT>

Vous &#234;tes le visiteur 
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B5F0E460-DC5F-11D0-9846-0000F8027CA0" height=17 id=Label1 style="HEIGHT: 17px; LEFT: 0px; TOP: 0px; WIDTH: 177px" 
	width=177>
	<PARAM NAME="_ExtentX" VALUE="4895">
	<PARAM NAME="_ExtentY" VALUE="450">
	<PARAM NAME="id" VALUE="Label1">
	<PARAM NAME="DataSource" VALUE="CounterRecordset">
	<PARAM NAME="DataField" VALUE="=CounterRecordset.getCount()">
	<PARAM NAME="FontFace" VALUE="">
	<PARAM NAME="FontSize" VALUE="">
	<PARAM NAME="FontColor" VALUE="">
	<PARAM NAME="FontBold" VALUE="-1">
	<PARAM NAME="FontItalic" VALUE="0">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="FormatAsHTML" VALUE="0">
	<PARAM NAME="Platform" VALUE="0">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<!--#INCLUDE FILE="../_ScriptLibrary/Label.ASP"-->
<B>
<script runat="server" language="JavaScript">
function _initLabel1()
{
   CounterRecordset.advise(RS_ONROWENTER, 'objFields = CounterRecordset.fields;Label1.setCaption(CounterRecordset.getCount());');
}
function _Label1_ctor()
{
   CreateLabel('Label1', _initLabel1, null);
}
</script>
<% Label1.display %>
</B>

<!--METADATA TYPE="DesignerControl" endspan-->
sur cette page Web.
</FONT>
</BODY>
<% ' Modèle d'objet script VI 6.0 activé %>
<% EndPageProcessing() %>
</FORM>
</HTML>
