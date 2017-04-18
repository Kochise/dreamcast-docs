<%@ LANGUAGE=VBScript %>
<% ' VI 6.0 Scripting Object Model Enabled %>
<!--#include file="../_ScriptLibrary/pm.asp"-->
<% if StartPageProcessing() Then Response.End() %>
<FORM name=thisForm METHOD=post>
<HTML>
<BODY bgColor=#ffffff leftMargin=40 link=#500000 vLink=#505050>
<FONT FACE="Verdana, Arial, Helvetica" SIZE=2>
<SCRIPT LANGUAGE=javascript RUNAT = Server>
	function DTCRecordset1_onbeforeopen() {
		newSQL = "SELECT Products.* FROM Products WHERE (CategoryID = " + Request("cboProduct") + ") ORDER BY ProductName";
		DTCRecordset1.setSQLText(newSQL);
	}

	var WGdc=",";  var WGgc=" ";  var WGnc="(";  var WGcs="F";

	function FormatMoney(A,W) {
	   var N=Math.abs(Math.round(A*100));
	   var S=((N<10)?"00":((N<100)?"0":""))+N;
	   S=WGcs+((A<0)?WGnc:"")+WGgroup(S.substring(0,(S.length-2)))+WGdc+S.substring((S.length-2),S.length)+((A<0&&WGnc=="(")?")":"");
	   return (S.length>W)?"Plus de":S;
	}
	
	function WGgroup(S) {
		return (S.length<4)?S:(WGgroup(S.substring(0,S.length-3))+WGgc+S.substring(S.length-3,S.length));
	}
</SCRIPT>

<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:9CF5D7C2-EC10-11D0-9862-0000F8027CA0" id=DTCRecordset1 
style="LEFT: 0px; TOP: 0px">
	<PARAM NAME="ExtentX" VALUE="12197">
	<PARAM NAME="ExtentY" VALUE="2090">
	<PARAM NAME="State" VALUE="(TCConn=\qGallery\q,TCDBObject_Unmatched=\qSQL\sStatement\q,TCDBObjectName_Unmatched=\qSELECT\s*\sFROM\sProducts\sWHERE\sCategoryID\s=\s?\sORDER\sBY\sProductName\q,TCControlID_Unmatched=\qDTCRecordset1\q,TCPPConn=\qGallery\q,TCPPDBObject=\qTables\q,TCPPDBObjectName=\qProducts\q,RCDBObject=\qRCSQLStatement\q,TCSQLStatement_Unmatched=\qSELECT\s*\sFROM\sProducts\sWHERE\sCategoryID\s=\s?\sORDER\sBY\sProductName\q,TCCursorType=\q3\s-\sStatic\q,TCCursorLocation=\q3\s-\sUse\sclient-side\scursors\q,TCLockType=\q3\s-\sOptimistic\q,TCCacheSize_Unmatched=\q10\q,TCCommTimeout_Unmatched=\q10\q,CCPrepared=0,CCAllRecords=1,TCNRecords_Unmatched=\q10\q,TCODBCSyntax_Unmatched=\q\q,TCHTargetPlatform=\q\q,TCHTargetBrowser_Unmatched=\qServer\s(ASP)\q,TCTargetPlatform=\qInherit\sfrom\spage\q,RCCache=\qRCBookPage\q,CCOpen=1,GCParameters=(Rows=0))">
	<PARAM NAME="LocalPath" VALUE="../">
	
 </OBJECT>
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
	cmdTmp.CommandText = 'SELECT * FROM Products WHERE CategoryID = ? ORDER BY ProductName';
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
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:277FC3F2-E90F-11D0-B767-0000F81E081D" id=Grid1 
style="LEFT: 0px; TOP: 0px">
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
	<PARAM NAME="ColumnsNames" VALUE='"=""<A HREF=AddCart.asp?ProdID="" + [ProductID] + "">""+ [ProductName] + ""</A>""","=FormatMoney([UnitPrice],12)"'>
	<PARAM NAME="columnIndex" VALUE="0,1">
	<PARAM NAME="displayWidth" VALUE="79,68">
	<PARAM NAME="Coltype" VALUE="1,1">
	<PARAM NAME="formated" VALUE="0,1">
	<PARAM NAME="DisplayName" VALUE='"Product Name","Price"'>
	<PARAM NAME="DetailAlignment" VALUE=",1">
	<PARAM NAME="HeaderAlignment" VALUE=",0">
	<PARAM NAME="DetailBackColor" VALUE=",White">
	<PARAM NAME="HeaderBackColor" VALUE=",Gray">
	<PARAM NAME="HeaderFont" VALUE=",Arial">
	<PARAM NAME="HeaderFontColor" VALUE=",Black">
	<PARAM NAME="HeaderFontSize" VALUE=",3">
	<PARAM NAME="HeaderFontStyle" VALUE=",0">
	<PARAM NAME="DetailFont" VALUE=",Arial">
	<PARAM NAME="DetailFontColor" VALUE=",Black">
	<PARAM NAME="DetailFontSize" VALUE=",1">
	<PARAM NAME="DetailFontStyle" VALUE=",0">
	<PARAM NAME="ColumnCount" VALUE="2">
	<PARAM NAME="CurStyle" VALUE="Basic Navy">
	<PARAM NAME="TitleFont" VALUE="Arial">
	<PARAM NAME="titleFontSize" VALUE="3">
	<PARAM NAME="TitleFontColor" VALUE="0">
	<PARAM NAME="TitleBackColor" VALUE="8421504">
	<PARAM NAME="TitleFontStyle" VALUE="0">
	<PARAM NAME="TitleAlignment" VALUE="0">
	<PARAM NAME="RowFont" VALUE="Arial">
	<PARAM NAME="RowFontColor" VALUE="0">
	<PARAM NAME="RowFontStyle" VALUE="0">
	<PARAM NAME="RowFontSize" VALUE="1">
	<PARAM NAME="RowBackColor" VALUE="16777215">
	<PARAM NAME="RowAlignment" VALUE="0">
	<PARAM NAME="HighlightColor3D" VALUE="12632256">
	<PARAM NAME="ShadowColor3D" VALUE="8421504">
	<PARAM NAME="PageSize" VALUE="20">
	<PARAM NAME="MoveFirstCaption" VALUE="    |<    ">
	<PARAM NAME="MoveLastCaption" VALUE="    >|    ">
	<PARAM NAME="MovePrevCaption" VALUE="    <    ">
	<PARAM NAME="MoveNextCaption" VALUE="    >    ">
	<PARAM NAME="BorderSize" VALUE="4">
	<PARAM NAME="BorderColor" VALUE="268435455">
	<PARAM NAME="GridBackColor" VALUE="16777215">
	<PARAM NAME="AltRowBckgnd" VALUE="12632256">
	<PARAM NAME="CellSpacing" VALUE="1">
	<PARAM NAME="WidthSelectionMode" VALUE="1">
	<PARAM NAME="GridWidth" VALUE="304">
	<PARAM NAME="EnablePaging" VALUE="0">
	<PARAM NAME="ShowStatus" VALUE="-1">
	<PARAM NAME="StyleValue" VALUE="482285">
	<PARAM NAME="LocalPath" VALUE="../">
	
 </OBJECT>
-->
<!--#INCLUDE FILE="../_ScriptLibrary/Button.ASP"-->
<!--#INCLUDE FILE="../_ScriptLibrary/RSNavBar.ASP"-->
<!--#INCLUDE FILE="../_ScriptLibrary/DataGrid.ASP"-->
<SCRIPT LANGUAGE=JavaScript RUNAT=Server>
function _initGrid1()
{
Grid1.pageSize = 0;
Grid1.setDataSource(DTCRecordset1);
Grid1.tableAttributes = 'align=center cellpadding=2  cellspacing=1 cols=2 rules=ALL';
Grid1.headerAttributes = '   bgcolor=Gray align=Left';
Grid1.headerWidth[0] = '';
Grid1.headerWidth[1] = '';
Grid1.headerFormat = '<Font face="Arial" size=3 color=Black> ';
Grid1.colHeader[0] = '\'Nom de produit\'';
Grid1.colHeader[1] = '\'Prix\'';
Grid1.rowAttributes[0] = '  bgcolor = White align=Left';
Grid1.rowAttributes[1] = '  bgcolor = Silver align=Left';
Grid1.rowFormat[0] = ' <Font face="Arial" size=1 color=Black >';
Grid1.colAttributes[0] = ' ';
Grid1.colFormat[0] = '<Font Size=1 Face="Arial" Color=Black >';
Grid1.colData[0] = '"<A HREF=AddCart.asp?ProdID=" + DTCRecordset1.fields.getValue(\'ProductID\') + ">"+ DTCRecordset1.fields.getValue(\'ProductName\') + "</A>"';
Grid1.colAttributes[1] = '  bgcolor=White align=Right';
Grid1.colFormat[1] = '<Font Size=1 Face="Arial" Color=Black >';
Grid1.colData[1] = 'FormatMoney(DTCRecordset1.fields.getValue(\'UnitPrice\'),12)';
}
function _Grid1_ctor()
{
	CreateDataGrid('Grid1',_initGrid1);
}
</SCRIPT>

<%	Grid1.display %>


<!--METADATA TYPE="DesignerControl" endspan-->
</FONT>
</BODY>
<% ' VI 6.0 Scripting Object Model Enabled %>
<% EndPageProcessing() %>
</FORM>
</HTML>
