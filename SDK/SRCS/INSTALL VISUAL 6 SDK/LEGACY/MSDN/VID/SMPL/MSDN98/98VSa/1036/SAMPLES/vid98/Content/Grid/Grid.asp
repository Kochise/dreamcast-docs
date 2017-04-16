<%@ LANGUAGE=VBScript %>
<% ' VI 6.0 Scripting Object Model Enabled %>
<!--#include file="../_ScriptLibrary/pm.asp"-->
<% if StartPageProcessing() Then Response.End() %>
<FORM name=thisForm METHOD=post>
<HTML>
<HEAD>
<META NAME="GENERATOR" Content="Microsoft Visual Studio 6.0">
<SCRIPT LANGUAGE=JScript RUNAT=Server>
	function AlertIsVisible() {
		x="<"
		response.write(x + "SCRIPT Language=JavaScript>");
		if (Grid1.isVisible()) {
			response.write("alert('Contrôle Grid visible');");
		}
		else {
			response.write("alert('Contrôle Grid invisible');");
		}
		response.write(x + "/SCRIPT>");
	}
</SCRIPT>
</HEAD>
<BODY bgColor=#ffffff leftMargin=40 link=#500000 vLink=#505050>
<FONT FACE="Verdana, Arial, Helvetica" SIZE=2>
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:9CF5D7C2-EC10-11D0-9862-0000F8027CA0" id=DTCRecordset1 
style="LEFT: 0px; TOP: 0px">
	<PARAM NAME="ExtentX" VALUE="12197">
	<PARAM NAME="ExtentY" VALUE="2090">
	<PARAM NAME="State" VALUE="(TCConn=\qGallery\q,TCDBObject=\qTables\q,TCDBObjectName=\qProducts\q,TCControlID_Unmatched=\qDTCRecordset1\q,TCPPConn=\qGallery\q,RCDBObject=\qRCDBObject\q,TCPPDBObject=\qTables\q,TCPPDBObjectName=\qProducts\q,TCCursorType=\q3\s-\sStatic\q,TCCursorLocation=\q3\s-\sUse\sclient-side\scursors\q,TCLockType=\q3\s-\sOptimistic\q,TCCacheSize_Unmatched=\q10\q,TCCommTimeout_Unmatched=\q10\q,CCPrepared=0,CCAllRecords=1,TCNRecords_Unmatched=\q10\q,TCODBCSyntax_Unmatched=\q\q,TCHTargetPlatform=\q\q,TCHTargetBrowser_Unmatched=\qServer\s(ASP)\q,TCTargetPlatform=\qInherit\sfrom\spage\q,RCCache=\qRCBookPage\q,CCOpen=1,GCParameters=(Rows=0))">
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
	cmdTmp.CommandType = 2;
	cmdTmp.CommandTimeout = 10;
	cmdTmp.CommandText = '`Products`';
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
style="LEFT: 0px; TOP: 0px" VIEWASTEXT>
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
	<PARAM NAME="EnableRowNav" VALUE="-1">
	<PARAM NAME="HiliteColor" VALUE="Yellow">
	<PARAM NAME="RecNavBarHasNextButton" VALUE="-1">
	<PARAM NAME="RecNavBarHasPrevButton" VALUE="-1">
	<PARAM NAME="RecNavBarNextText" VALUE="   >   ">
	<PARAM NAME="RecNavBarPrevText" VALUE="   <   ">
	<PARAM NAME="ColumnsNames" VALUE='"ProductID","ProductName","QuantityPerUnit","UnitPrice"'>
	<PARAM NAME="columnIndex" VALUE="0,1,2,3">
	<PARAM NAME="displayWidth" VALUE="71,68,68,68">
	<PARAM NAME="Coltype" VALUE="1,1,1,1">
	<PARAM NAME="formated" VALUE="0,0,0,0">
	<PARAM NAME="DisplayName" VALUE='"ProductID","ProductName","QuantityPerUnit","UnitPrice"'>
	<PARAM NAME="DetailAlignment" VALUE=",,,">
	<PARAM NAME="HeaderAlignment" VALUE=",,,">
	<PARAM NAME="DetailBackColor" VALUE=",,,">
	<PARAM NAME="HeaderBackColor" VALUE=",,,">
	<PARAM NAME="HeaderFont" VALUE=",,,">
	<PARAM NAME="HeaderFontColor" VALUE=",,,">
	<PARAM NAME="HeaderFontSize" VALUE=",,,">
	<PARAM NAME="HeaderFontStyle" VALUE=",,,">
	<PARAM NAME="DetailFont" VALUE=",,,">
	<PARAM NAME="DetailFontColor" VALUE=",,,">
	<PARAM NAME="DetailFontSize" VALUE=",,,">
	<PARAM NAME="DetailFontStyle" VALUE=",,,">
	<PARAM NAME="ColumnCount" VALUE="4">
	<PARAM NAME="CurStyle" VALUE="Basic Navy">
	<PARAM NAME="TitleFont" VALUE="Arial">
	<PARAM NAME="titleFontSize" VALUE="4">
	<PARAM NAME="TitleFontColor" VALUE="0">
	<PARAM NAME="TitleBackColor" VALUE="8421504">
	<PARAM NAME="TitleFontStyle" VALUE="1">
	<PARAM NAME="TitleAlignment" VALUE="0">
	<PARAM NAME="RowFont" VALUE="Arial">
	<PARAM NAME="RowFontColor" VALUE="0">
	<PARAM NAME="RowFontStyle" VALUE="0">
	<PARAM NAME="RowFontSize" VALUE="2">
	<PARAM NAME="RowBackColor" VALUE="16777215">
	<PARAM NAME="RowAlignment" VALUE="0">
	<PARAM NAME="HighlightColor3D" VALUE="12632256">
	<PARAM NAME="ShadowColor3D" VALUE="8421504">
	<PARAM NAME="PageSize" VALUE="10">
	<PARAM NAME="MoveFirstCaption" VALUE="    |<    ">
	<PARAM NAME="MoveLastCaption" VALUE="    >|    ">
	<PARAM NAME="MovePrevCaption" VALUE="    <<    ">
	<PARAM NAME="MoveNextCaption" VALUE="    >>    ">
	<PARAM NAME="BorderSize" VALUE="4">
	<PARAM NAME="BorderColor" VALUE="268435455">
	<PARAM NAME="GridBackColor" VALUE="16777215">
	<PARAM NAME="AltRowBckgnd" VALUE="268435455">
	<PARAM NAME="CellSpacing" VALUE="1">
	<PARAM NAME="WidthSelectionMode" VALUE="2">
	<PARAM NAME="GridWidth" VALUE="109">
	<PARAM NAME="EnablePaging" VALUE="-1">
	<PARAM NAME="ShowStatus" VALUE="-1">
	<PARAM NAME="StyleValue" VALUE="465869">
	<PARAM NAME="LocalPath" VALUE="../">
	
 
</OBJECT>
-->
<!--#INCLUDE FILE="../_ScriptLibrary/Button.ASP"-->
<!--#INCLUDE FILE="../_ScriptLibrary/RSNavBar.ASP"-->
<!--#INCLUDE FILE="../_ScriptLibrary/DataGrid.ASP"-->
<SCRIPT LANGUAGE=JavaScript RUNAT=Server>
function _initGrid1()
{
Grid1.pageSize = 10;
Grid1.setDataSource(DTCRecordset1);
Grid1.tableAttributes = 'align=center cellpadding=2  cellspacing=1 cols=4 rules=ALL nowrap';
Grid1.headerAttributes = '   bgcolor=Gray align=Left nowrap';
Grid1.headerWidth[0] = '';
Grid1.headerWidth[1] = '';
Grid1.headerWidth[2] = '';
Grid1.headerWidth[3] = '';
Grid1.headerFormat = '<Font face="Arial" size=4 color=Black> <b>';
Grid1.colHeader[0] = '\'ProductID\'';
Grid1.colHeader[1] = '\'ProductName\'';
Grid1.colHeader[2] = '\'QuantityPerUnit\'';
Grid1.colHeader[3] = '\'UnitPrice\'';
Grid1.rowAttributes[0] = '  bgcolor = White align=Left nowrap ';
Grid1.rowFormat[0] = ' <Font face="Arial" size=2 color=Black >';
Grid1.colAttributes[0] = ' ';
Grid1.colFormat[0] = '<Font Size=2 Face="Arial" Color=Black >';
Grid1.colData[0] = 'DTCRecordset1.fields.getValue(\'ProductID\')';
Grid1.colAttributes[1] = ' ';
Grid1.colFormat[1] = '<Font Size=2 Face="Arial" Color=Black >';
Grid1.colData[1] = 'DTCRecordset1.fields.getValue(\'ProductName\')';
Grid1.colAttributes[2] = ' ';
Grid1.colFormat[2] = '<Font Size=2 Face="Arial" Color=Black >';
Grid1.colData[2] = 'DTCRecordset1.fields.getValue(\'QuantityPerUnit\')';
Grid1.colAttributes[3] = ' ';
Grid1.colFormat[3] = '<Font Size=2 Face="Arial" Color=Black >';
Grid1.colData[3] = 'DTCRecordset1.fields.getValue(\'UnitPrice\')';
Grid1.navbarAlignment = 'Left';
var objPageNavbar = Grid1.showPageNavbar(170,1);
objPageNavbar.getButton(0).value = '    |<    ';
objPageNavbar.getButton(1).value = '    <<    ';
objPageNavbar.getButton(2).value = '    >>    ';
objPageNavbar.getButton(3).value = '    >|    ';
Grid1.hasPageNumber = true;
Grid1.hiliteAttributes = ' bgcolor=Yellow';
var objRecNavbar = Grid1.showRecordNavbar(40,1);
objRecNavbar.getButton(1).value = '   <   ';
objRecNavbar.getButton(2).value = '   >   ';
}
function _Grid1_ctor()
{
	CreateDataGrid('Grid1',_initGrid1);
}
</SCRIPT>

<%	Grid1.display %>


<!--METADATA TYPE="DesignerControl" endspan-->
<BR>
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B6FC3A14-F837-11D0-9CC8-006008058731" height=27 id=btnHide style="HEIGHT: 27px; LEFT: 0px; TOP: 0px; WIDTH: 49px" 
	width=49>
	<PARAM NAME="_ExtentX" VALUE="2011">
	<PARAM NAME="_ExtentY" VALUE="714">
	<PARAM NAME="id" VALUE="btnHide">
	<PARAM NAME="Caption" VALUE="Masquer">
	<PARAM NAME="Image" VALUE="">
	<PARAM NAME="AltText" VALUE="">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="Platform" VALUE="256">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<SCRIPT LANGUAGE=JavaScript RUNAT=Server>
function _initbtnHide()
{
	btnHide.value = 'Masquer';
	btnHide.setStyle(0);
}
function _btnHide_ctor()
{
	CreateButton('btnHide', _initbtnHide, null);
}
</script>
<% btnHide.display %>

<!--METADATA TYPE="DesignerControl" endspan-->
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B6FC3A14-F837-11D0-9CC8-006008058731" height=27 id=btnShow style="HEIGHT: 27px; LEFT: 0px; TOP: 0px; WIDTH: 53px" 
	width=53>
	<PARAM NAME="_ExtentX" VALUE="1799">
	<PARAM NAME="_ExtentY" VALUE="714">
	<PARAM NAME="id" VALUE="btnShow">
	<PARAM NAME="Caption" VALUE="Afficher">
	<PARAM NAME="Image" VALUE="">
	<PARAM NAME="AltText" VALUE="">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="Platform" VALUE="256">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<SCRIPT LANGUAGE=JavaScript RUNAT=Server>
function _initbtnShow()
{
	btnShow.value = 'Afficher';
	btnShow.setStyle(0);
}
function _btnShow_ctor()
{
	CreateButton('btnShow', _initbtnShow, null);
}
</script>
<% btnShow.display %>

<!--METADATA TYPE="DesignerControl" endspan-->
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B6FC3A14-F837-11D0-9CC8-006008058731" height=27 id=btnIsVisible 
	style="HEIGHT: 27px; LEFT: 0px; TOP: 0px; WIDTH: 76px" width=76>
	<PARAM NAME="_ExtentX" VALUE="2355">
	<PARAM NAME="_ExtentY" VALUE="714">
	<PARAM NAME="id" VALUE="btnIsVisible">
	<PARAM NAME="Caption" VALUE="est Visible">
	<PARAM NAME="Image" VALUE="">
	<PARAM NAME="AltText" VALUE="">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="Platform" VALUE="256">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<SCRIPT LANGUAGE=JavaScript RUNAT=Server>
function _initbtnIsVisible()
{
	btnIsVisible.value = 'est Visible';
	btnIsVisible.setStyle(0);
}
function _btnIsVisible_ctor()
{
	CreateButton('btnIsVisible', _initbtnIsVisible, null);
}
</script>
<% btnIsVisible.display %>

<!--METADATA TYPE="DesignerControl" endspan-->
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B6FC3A14-F837-11D0-9CC8-006008058731" height=27 id=btnbindAllColumns 
	style="HEIGHT: 27px; LEFT: 0px; TOP: 0px; WIDTH: 123px" width=123>
	<PARAM NAME="_ExtentX" VALUE="4128">
	<PARAM NAME="_ExtentY" VALUE="714">
	<PARAM NAME="id" VALUE="btnbindAllColumns">
	<PARAM NAME="Caption" VALUE="Toutes les colonnes">
	<PARAM NAME="Image" VALUE="">
	<PARAM NAME="AltText" VALUE="">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="Platform" VALUE="256">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<SCRIPT LANGUAGE=JavaScript RUNAT=Server>
function _initbtnbindAllColumns()
{
	btnbindAllColumns.value = 'Toutes les colonnes';
	btnbindAllColumns.setStyle(0);
}
function _btnbindAllColumns_ctor()
{
	CreateButton('btnbindAllColumns', _initbtnbindAllColumns, null);
}
</script>
<% btnbindAllColumns.display %>

<!--METADATA TYPE="DesignerControl" endspan-->
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:CEB04D01-0445-11D1-BB81-006097C553C8" id=FormManager1 
style="LEFT: 0px; TOP: 0px">
	<PARAM NAME="ExtentX" VALUE="4233">
	<PARAM NAME="ExtentY" VALUE="609">
	<PARAM NAME="State" VALUE="(txtName_Unmatched=\qFormManager1\q,txtNewMode_Unmatched=\qGrid\q,grFormMode=(Rows=2,Row1=(txtMode_Unmatched=\qHide\q),Row2=(txtMode_Unmatched=\qShow\q)),txtDefaultMode=\qShow\q,grMasterMode=(Rows=6,Row1=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qbtnShow\q,txtProperty_Unmatched=\qdisabled\q,txtValue_Unmatched=\qfalse\q),Row2=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qbtnHide\q,txtProperty_Unmatched=\qdisabled\q,txtValue_Unmatched=\qtrue\q),Row3=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qbtnbindAllColumns\q,txtProperty_Unmatched=\qdisabled\q,txtValue_Unmatched=\qtrue\q),Row4=(txtName_Unmatched=\q2\q,txtControl_Unmatched=\qbtnShow\q,txtProperty_Unmatched=\qdisabled\q,txtValue_Unmatched=\qtrue\q),Row5=(txtName_Unmatched=\q2\q,txtControl_Unmatched=\qbtnHide\q,txtProperty_Unmatched=\qdisabled\q,txtValue_Unmatched=\qfalse\q),Row6=(txtName_Unmatched=\q2\q,txtControl_Unmatched=\qbtnbindAllColumns\q,txtProperty_Unmatched=\qdisabled\q,txtValue_Unmatched=\qfalse\q)),grTransitions=(Rows=5,Row1=(txtCurrentMode=\qShow\q,txtObject=\qbtnHide\q,txtEvent=\qonclick\q,txtNextMode=\qHide\q),Row2=(txtCurrentMode=\qHide\q,txtObject=\qbtnShow\q,txtEvent=\qonclick\q,txtNextMode=\qShow\q),Row3=(txtCurrentMode=\qShow\q,txtObject=\qbtnbindAllColumns\q,txtEvent=\qonclick\q,txtNextMode=\qShow\q),Row4=(txtCurrentMode=\qShow\q,txtObject=\qbtnIsVisible\q,txtEvent=\qonclick\q,txtNextMode=\qShow\q),Row5=(txtCurrentMode=\qHide\q,txtObject=\qbtnIsVisible\q,txtEvent=\qonclick\q,txtNextMode=\qHide\q)),grMasterStep=(Rows=9,Row1=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qGrid1\q,txtAction_Unmatched=\qhide\q,txtValue_Unmatched=\q()\q),Row2=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qbtnHide\q,txtAction_Unmatched=\qdisabled\q,txtValue_Unmatched=\qtrue\q),Row3=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qbtnShow\q,txtAction_Unmatched=\qdisabled\q,txtValue_Unmatched=\qfalse\q),Row4=(txtName_Unmatched=\q2\q,txtControl_Unmatched=\qGrid1\q,txtAction_Unmatched=\qshow\q,txtValue_Unmatched=\q()\q),Row5=(txtName_Unmatched=\q2\q,txtControl_Unmatched=\qbtnShow\q,txtAction_Unmatched=\qdisabled\q,txtValue_Unmatched=\qtrue\q),Row6=(txtName_Unmatched=\q2\q,txtControl_Unmatched=\qbtnHide\q,txtAction_Unmatched=\qdisabled\q,txtValue_Unmatched=\qfalse\q),Row7=(txtName_Unmatched=\q3\q,txtControl_Unmatched=\qGrid1\q,txtAction_Unmatched=\qbindAllColumns\q,txtValue_Unmatched=\q()\q),Row8=(txtName_Unmatched=\q4\q,txtControl_Unmatched=\q\q,txtAction_Unmatched=\qAlertIsVisible\q,txtValue_Unmatched=\q()\q),Row9=(txtName_Unmatched=\q5\q,txtControl_Unmatched=\q\q,txtAction_Unmatched=\qAlertIsVisible\q,txtValue_Unmatched=\q()\q)))">
	
 </OBJECT>
-->
<SCRIPT RUNAT=SERVER LANGUAGE="JavaScript">
function _FormManager1_ctor()
{
	thisPage.advise(PAGE_ONINIT, _FormManager1_init);
}
function _FormManager1_init()
{
	if (thisPage.getState("FormManager1_formmode") == null)
		_FormManager1_SetMode("Show");
	btnHide.advise("onclick", "_FormManager1_btnHide_onclick()");
	btnShow.advise("onclick", "_FormManager1_btnShow_onclick()");
	btnbindAllColumns.advise("onclick", "_FormManager1_btnbindAllColumns_onclick()");
	btnIsVisible.advise("onclick", "_FormManager1_btnIsVisible_onclick()");
}
function _FormManager1_SetMode(formmode)
{
	thisPage.setState("FormManager1_formmode", formmode);
	if (formmode == "Hide")
	{
		btnShow.disabled = false;
		btnHide.disabled = true;
		btnbindAllColumns.disabled = true;
	}
	if (formmode == "Show")
	{
		btnShow.disabled = true;
		btnHide.disabled = false;
		btnbindAllColumns.disabled = false;
	}
}
function _FormManager1_btnHide_onclick()
{
	if (thisPage.getState("FormManager1_formmode") == "Show")
	{
		Grid1.hide();
		btnHide.disabled = true;
		btnShow.disabled = false;
		_FormManager1_SetMode("Hide");
	}
	else _FormManager1_SetMode(thisPage.getState("FormManager1_formmode"))
}
function _FormManager1_btnShow_onclick()
{
	if (thisPage.getState("FormManager1_formmode") == "Hide")
	{
		Grid1.show();
		btnShow.disabled = true;
		btnHide.disabled = false;
		_FormManager1_SetMode("Show");
	}
	else _FormManager1_SetMode(thisPage.getState("FormManager1_formmode"))
}
function _FormManager1_btnbindAllColumns_onclick()
{
	if (thisPage.getState("FormManager1_formmode") == "Show")
	{
		Grid1.bindAllColumns();
		_FormManager1_SetMode("Show");
	}
	else _FormManager1_SetMode(thisPage.getState("FormManager1_formmode"))
}
function _FormManager1_btnIsVisible_onclick()
{
	if (thisPage.getState("FormManager1_formmode") == "Show")
	{
		AlertIsVisible();
		_FormManager1_SetMode("Show");
	}
	else if (thisPage.getState("FormManager1_formmode") == "Hide")
	{
		AlertIsVisible();
		_FormManager1_SetMode("Hide");
	}
	else _FormManager1_SetMode(thisPage.getState("FormManager1_formmode"))
}
</SCRIPT>


<!--METADATA TYPE="DesignerControl" endspan-->
</FONT>
</BODY>
<% ' VI 6.0 Scripting Object Model Enabled %>
<% EndPageProcessing() %>
</FORM>
</HTML>
