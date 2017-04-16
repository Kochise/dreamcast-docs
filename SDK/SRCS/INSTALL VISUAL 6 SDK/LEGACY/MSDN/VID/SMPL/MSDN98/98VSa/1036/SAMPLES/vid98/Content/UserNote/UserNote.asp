<%@ LANGUAGE=VBScript %>
<% ' VI 6.0 Scripting Object Model Enabled %>
<!--#include file="../_ScriptLibrary/pm.asp"-->
<% if StartPageProcessing() Then Response.End() %>
<FORM name=thisForm METHOD=post>
<HTML>
<BODY bgColor=#ffffff leftMargin=40 link=#500000 vLink=#505050>

<FONT FACE="Verdana, Arial, Helvetica" SIZE=2>

<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:9CF5D7C2-EC10-11D0-9862-0000F8027CA0" id=DTCRecordset1 style="LEFT: 0px; TOP: 0px">
	<PARAM NAME="ExtentX" VALUE="12197">
	<PARAM NAME="ExtentY" VALUE="2090">
	<PARAM NAME="State" VALUE="(TCConn=\qGallery\q,TCDBObject=\qTables\q,TCDBObjectName=\qUserNote\q,TCControlID_Unmatched=\qDTCRecordset1\q,TCPPConn=\qGallery\q,RCDBObject=\qRCDBObject\q,TCPPDBObject=\qTables\q,TCPPDBObjectName=\qUserNote\q,TCSQLStatement_Unmatched=\qSelect\s*\sfrom\sUserNote\q,TCCursorType=\q3\s-\sStatic\q,TCCursorLocation=\q3\s-\sUse\sclient-side\scursors\q,TCLockType=\q3\s-\sOptimistic\q,TCCacheSize_Unmatched=\q10\q,TCCommTimeout_Unmatched=\q10\q,CCPrepared=0,CCAllRecords=1,TCNRecords_Unmatched=\q10\q,TCODBCSyntax_Unmatched=\q\q,TCHTargetPlatform=\q\q,TCHTargetBrowser_Unmatched=\qServer\s(ASP)\q,TCTargetPlatform=\qInherit\sfrom\spage\q,RCCache=\qRCBookPage\q,CCOpen=1,GCParameters=(Rows=0))">
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
	cmdTmp.CommandType = 2;
	cmdTmp.CommandTimeout = 10;
	cmdTmp.CommandText = '`UserNote`';
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
</SCRIPT>

<!--METADATA TYPE="DesignerControl" endspan-->

<SCRIPT LANGUAGE=javascript RUNAT=Server>
	function DTCRecordset1_onbeforeopen() {
		newSQL = "Select * FROM UserNote WHERE (TO = '" + Request.ServerVariables("AUTH_USER") + "')";
		DTCRecordset1.setSQLText(newSQL);
	}
</SCRIPT>
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:277FC3F2-E90F-11D0-B767-0000F81E081D" id=Grid1 style="LEFT: 0px; TOP: 0px">
	<PARAM NAME="_ExtentX" VALUE="8043">
	<PARAM NAME="_ExtentY" VALUE="3889">
	<PARAM NAME="DataConnection" VALUE="">
	<PARAM NAME="SourceType" VALUE="">
	<PARAM NAME="Recordset" VALUE="DTCRecordset1">
	<PARAM NAME="CtrlName" VALUE="Grid1">
	<PARAM NAME="UseAdvancedOnly" VALUE="0">
	<PARAM NAME="AdvAddToStyles" VALUE="-1">
	<PARAM NAME="AdvTableTag" VALUE="align=center">
	<PARAM NAME="AdvHeaderRowTag" VALUE="">
	<PARAM NAME="AdvHeaderCellTag" VALUE="">
	<PARAM NAME="AdvDetailRowTag" VALUE="">
	<PARAM NAME="AdvDetailCellTag" VALUE="">
	<PARAM NAME="ScriptLanguage" VALUE="1">
	<PARAM NAME="ScriptingPlatform" VALUE="0">
	<PARAM NAME="EnableRowNav" VALUE="0">
	<PARAM NAME="HiliteColor" VALUE="">
	<PARAM NAME="RecNavBarHasNextButton" VALUE="-1">
	<PARAM NAME="RecNavBarHasPrevButton" VALUE="-1">
	<PARAM NAME="RecNavBarNextText" VALUE="   >   ">
	<PARAM NAME="RecNavBarPrevText" VALUE="   <   ">
	<PARAM NAME="ColumnsNames" VALUE='"De","Message","=""<A HREF=DelNote.asp?ID="" + [ID] + "">Delete</A>"""'>
	<PARAM NAME="columnIndex" VALUE="0,1,2">
	<PARAM NAME="displayWidth" VALUE="68,68,68">
	<PARAM NAME="Coltype" VALUE="1,1,1">
	<PARAM NAME="formated" VALUE="0,0,0">
	<PARAM NAME="DisplayName" VALUE="De","Message","Supprimer">
	<PARAM NAME="DetailAlignment" VALUE=",,">
	<PARAM NAME="HeaderAlignment" VALUE=",,">
	<PARAM NAME="DetailBackColor" VALUE=",,">
	<PARAM NAME="HeaderBackColor" VALUE=",,">
	<PARAM NAME="HeaderFont" VALUE=",,">
	<PARAM NAME="HeaderFontColor" VALUE=",,">
	<PARAM NAME="HeaderFontSize" VALUE=",,">
	<PARAM NAME="HeaderFontStyle" VALUE=",,">
	<PARAM NAME="DetailFont" VALUE=",,">
	<PARAM NAME="DetailFontColor" VALUE=",,">
	<PARAM NAME="DetailFontSize" VALUE=",,">
	<PARAM NAME="DetailFontStyle" VALUE=",,">
	<PARAM NAME="ColumnCount" VALUE="3">
	<PARAM NAME="CurStyle" VALUE="Basic Navy">
	<PARAM NAME="TitleFont" VALUE="Arial">
	<PARAM NAME="titleFontSize" VALUE="4">
	<PARAM NAME="TitleFontColor" VALUE="16777215">
	<PARAM NAME="TitleBackColor" VALUE="13416">
	<PARAM NAME="TitleFontStyle" VALUE="1">
	<PARAM NAME="TitleAlignment" VALUE="0">
	<PARAM NAME="RowFont" VALUE="Arial">
	<PARAM NAME="RowFontColor" VALUE="0">
	<PARAM NAME="RowFontStyle" VALUE="0">
	<PARAM NAME="RowFontSize" VALUE="2">
	<PARAM NAME="RowBackColor" VALUE="16777215">
	<PARAM NAME="RowAlignment" VALUE="0">
	<PARAM NAME="HighlightColor3D" VALUE="268435455">
	<PARAM NAME="ShadowColor3D" VALUE="268435455">
	<PARAM NAME="PageSize" VALUE="20">
	<PARAM NAME="MoveFirstCaption" VALUE="    |<    ">
	<PARAM NAME="MoveLastCaption" VALUE="    >|    ">
	<PARAM NAME="MovePrevCaption" VALUE="    <    ">
	<PARAM NAME="MoveNextCaption" VALUE="    >    ">
	<PARAM NAME="BorderSize" VALUE="1">
	<PARAM NAME="BorderColor" VALUE="13421772">
	<PARAM NAME="GridBackColor" VALUE="16777215">
	<PARAM NAME="AltRowBckgnd" VALUE="12632256">
	<PARAM NAME="CellSpacing" VALUE="0">
	<PARAM NAME="WidthSelectionMode" VALUE="1">
	<PARAM NAME="GridWidth" VALUE="304">
	<PARAM NAME="EnablePaging" VALUE="0">
	<PARAM NAME="ShowStatus" VALUE="-1">
	<PARAM NAME="StyleValue" VALUE="445421">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<!--#INCLUDE FILE="../_ScriptLibrary/Button.ASP"-->
<!--#INCLUDE FILE="../_ScriptLibrary/RSNavBar.ASP"-->
<!--#INCLUDE FILE="../_ScriptLibrary/DataGrid.ASP"-->
<SCRIPT LANGUAGE=JavaScript RUNAT=Server>
function _initGrid1()
{
Grid1.pageSize = 0;
Grid1.setDataSource(DTCRecordset1);
Grid1.tableAttributes = 'align=center cellpadding=2  cellspacing=0 bordercolor=#cccccc bgcolor=White border=1 cols=3 rules=ALL';
Grid1.headerAttributes = '   bgcolor=#003468 align=Left';
Grid1.headerWidth[0] = '';
Grid1.headerWidth[1] = '';
Grid1.headerWidth[2] = '';
Grid1.headerFormat = '<Font face="Arial" size=4 color=White> <b>';
Grid1.colHeader[0] = '\'Expéditeur\'';
Grid1.colHeader[1] = '\'Message\'';
Grid1.colHeader[2] = '\'Supprimer\'';
Grid1.rowAttributes[0] = '  bgcolor = White align=Left bordercolor=#cccccc';
Grid1.rowAttributes[1] = '  bgcolor = Silver align=Left bordercolor=#cccccc';
Grid1.rowFormat[0] = ' <Font face="Arial" size=2 color=Black >';
Grid1.colAttributes[0] = ' ';
Grid1.colFormat[0] = '<Font Size=2 Face="Arial" Color=Black >';
Grid1.colData[0] = 'DTCRecordset1.fields.getValue(\'From\')';
Grid1.colAttributes[1] = ' ';
Grid1.colFormat[1] = '<Font Size=2 Face="Arial" Color=Black >';
Grid1.colData[1] = 'DTCRecordset1.fields.getValue(\'Message\')';
Grid1.colAttributes[2] = ' ';
Grid1.colFormat[2] = '<Font Size=2 Face="Arial" Color=Black >';
Grid1.colData[2] = '"<A HREF=DelNote.asp?ID=" + DTCRecordset1.fields.getValue(\'ID\') + ">Supprimer</A>"';
}
function _Grid1_ctor()
{
	CreateDataGrid('Grid1',_initGrid1);
}
</SCRIPT>

<%	Grid1.display %>


<!--METADATA TYPE="DesignerControl" endspan-->
<BR><BR>
<A HREF=SendNote.asp>Envoi de Message</A>
</FONT>
</BODY>
<% ' VI 6.0 Scripting Object Model Enabled %>
<% EndPageProcessing() %>
</FORM>
</HTML>
