<%@ LANGUAGE=VBScript %>
<% ' VI 6.0 Scripting Object Model Enabled %>
<!--#include file="../_ScriptLibrary/pm.asp"-->
<% if StartPageProcessing() Then Response.End() %>
<FORM name=thisForm METHOD=post>
<HTML>
<BODY bgColor=#ffffff leftMargin=40 link=#500000 vLink=#505050>
<FONT FACE="Verdana, Arial, Helvetica" SIZE=2>
<Script Language=JavaScript>
	function Validate(){
		if (isNaN(document.AddCart.intQTY.value)){
			alert("La quantité doit être une valeur numérique.")
			return false;
		} 
		return true;
	}
</Script>
<SCRIPT LANGUAGE=javascript RUNAT=Server>
	var intQuantity=1
	
	function DTCRecordset1_onbeforeopen() {
		newSQL = "SELECT * FROM ShopCart WHERE (SessionID = '" + Session.SessionID + "') AND (ProductID = " + Request('ProdID') + ")";
		DTCRecordset1.setSQLText(newSQL);
	}

	function DTCRecordset1_ondatasetcomplete() {
		if (DTCRecordset1.getCount() == 1) {
			intQuantity = DTCRecordset1.fields.getValue("Qty");
			InCart = true;
		}
		DTCRecordset2.open();
	}

	function DTCRecordset2_onbeforeopen() {
		newSQL = "SELECT * FROM Products WHERE (ProductID = " + Request('ProdID') + ")";
		DTCRecordset2.setSQLText(newSQL);
	}
	
</SCRIPT>
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:9CF5D7C2-EC10-11D0-9862-0000F8027CA0" id=DTCRecordset2 style="LEFT: 0px; TOP: 0px">
	<PARAM NAME="ExtentX" VALUE="12197">
	<PARAM NAME="ExtentY" VALUE="2090">
	<PARAM NAME="State" VALUE="(TCConn=\qGallery\q,TCDBObject_Unmatched=\qSQL\sStatement\q,TCDBObjectName_Unmatched=\qSelect\s*\sfrom\sProducts\q,TCControlID_Unmatched=\qDTCRecordset2\q,TCPPConn=\qGallery\q,TCPPDBObject=\qTables\q,TCPPDBObjectName=\qCounter\q,RCDBObject=\qRCSQLStatement\q,TCSQLStatement_Unmatched=\qSelect\s*\sfrom\sProducts\q,TCCursorType=\q3\s-\sStatic\q,TCCursorLocation=\q3\s-\sUse\sclient-side\scursors\q,TCLockType=\q3\s-\sOptimistic\q,TCCacheSize_Unmatched=\q10\q,TCCommTimeout_Unmatched=\q10\q,CCPrepared=0,CCAllRecords=1,TCNRecords_Unmatched=\q10\q,TCODBCSyntax_Unmatched=\q\q,TCHTargetPlatform=\q\q,TCHTargetBrowser_Unmatched=\qServer\s(ASP)\q,TCTargetPlatform=\qInherit\sfrom\spage\q,RCCache=\qRCBookPage\q,CCOpen=0,GCParameters=(Rows=0))">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<!--#INCLUDE FILE="../_ScriptLibrary/Recordset.ASP"-->
<SCRIPT LANGUAGE="JavaScript" RUNAT="server">
function _initDTCRecordset2()
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
	cmdTmp.CommandText = 'Select * from Products';
	rsTmp.CacheSize = 10;
	rsTmp.CursorType = 3;
	rsTmp.CursorLocation = 3;
	rsTmp.LockType = 3;
	DTCRecordset2.setRecordSource(rsTmp);
	if (thisPage.getState('pb_DTCRecordset2') != null)
		DTCRecordset2.setBookmark(thisPage.getState('pb_DTCRecordset2'));
}
function _DTCRecordset2_ctor()
{
	CreateRecordset('DTCRecordset2', _initDTCRecordset2, null);
}
function _DTCRecordset2_dtor()
{
	DTCRecordset2._preserveState();
	thisPage.setState('pb_DTCRecordset2', DTCRecordset2.getBookmark());
}
</SCRIPT>

<!--METADATA TYPE="DesignerControl" endspan-->
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:9CF5D7C2-EC10-11D0-9862-0000F8027CA0" id=DTCRecordset1 style="LEFT: 0px; TOP: 0px">
	<PARAM NAME="ExtentX" VALUE="12197">
	<PARAM NAME="ExtentY" VALUE="2090">
	<PARAM NAME="State" VALUE="(TCConn=\qGallery\q,TCDBObject_Unmatched=\qSQL\sStatement\q,TCDBObjectName_Unmatched=\qSelect\s*\sfrom\sShopCart\q,TCControlID_Unmatched=\qDTCRecordset1\q,TCPPConn=\qGallery\q,TCPPDBObject=\qTables\q,TCPPDBObjectName=\qCounter\q,RCDBObject=\qRCSQLStatement\q,TCSQLStatement_Unmatched=\qSelect\s*\sfrom\sShopCart\q,TCCursorType=\q3\s-\sStatic\q,TCCursorLocation=\q3\s-\sUse\sclient-side\scursors\q,TCLockType=\q3\s-\sOptimistic\q,TCCacheSize_Unmatched=\q10\q,TCCommTimeout_Unmatched=\q10\q,CCPrepared=0,CCAllRecords=1,TCNRecords_Unmatched=\q10\q,TCODBCSyntax_Unmatched=\q\q,TCHTargetPlatform=\q\q,TCHTargetBrowser_Unmatched=\qServer\s(ASP)\q,TCTargetPlatform=\qInherit\sfrom\spage\q,RCCache=\qRCBookPage\q,CCOpen=1,GCParameters=(Rows=0))">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
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
<% ' VI 6.0 Scripting Object Model Enabled %>
<% EndPageProcessing() %>
</FORM>
<form NAME="AddCart" ACTION="SCUpdate.asp" METHOD="Post" onsubmit="return Validate()">
	Vous avez sélectionné <b><%= DTCRecordset2.fields.getValue("ProductName") %></b>.<br>
	Chaque unité contient <%= DTCRecordset2.fields.getValue("QuantityPerUnit") %>, pour <%= FormatCurrency(DTCRecordset2.fields.getValue("UnitPrice"),2) %>.<br>
<%If InCart then%>
	Vous en avez actuellement <b><%=intQuantity%></b> dans votre chariot.<br>
	Veuillez entrer la nouvelle quantit&#233; : <input NAME="intQTY" TYPE="Text" VALUE="<%=intQuantity%>" SIZE="5"><br>
	<input TYPE="Hidden" NAME="InCart" VALUE="1">
<%Else%>
	Unités à commander : <input NAME="intQTY" TYPE="Text" VALUE="<%=intQuantity%>" SIZE="5"><br>
	<input TYPE="Hidden" NAME="InCart" VALUE="0">
<%End If%>
	<input TYPE="Hidden" NAME="ProdName" VALUE="<%= DTCRecordset2.fields.getValue("ProductName") %>">
	<input TYPE="Hidden" NAME="ProdID" VALUE="<%= DTCRecordset2.fields.getValue("ProductID") %>">
	<input TYPE="Hidden" NAME="Price" VALUE="<%= DTCRecordset2.fields.getValue("UnitPrice") %>">
	<input TYPE="Submit" id=Submit1 name=Submit1 Value="Ajouter au  Chariot">
</form>
</FONT>
</BODY>
</HTML>
