<%@ LANGUAGE=VBScript %>
<% ' VI 6.0 Scripting Object Model Enabled %>
<!--#include file="../_ScriptLibrary/pm.asp"-->
<% if StartPageProcessing() Then Response.End() %>
<FORM name=thisForm METHOD=post>
<HTML>
<BODY bgColor=#ffffff leftMargin=40 link=#500000 vLink=#505050>
<FONT FACE="Verdana, Arial, Helvetica" SIZE=2>
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:9CF5D7C2-EC10-11D0-9862-0000F8027CA0" id=DTCRecordset1 
style="LEFT: 0px; TOP: 0px">
	<PARAM NAME="ExtentX" VALUE="12197">
	<PARAM NAME="ExtentY" VALUE="2090">
	<PARAM NAME="State" VALUE="(TCConn=\qGallery\q,TCDBObject=\qTables\q,TCDBObjectName=\qGuestBk\q,TCControlID_Unmatched=\qDTCRecordset1\q,TCPPConn=\qGallery\q,RCDBObject=\qRCDBObject\q,TCPPDBObject=\qTables\q,TCPPDBObjectName=\qGuestBk\q,TCCursorType=\q3\s-\sStatic\q,TCCursorLocation=\q3\s-\sUse\sclient-side\scursors\q,TCLockType=\q3\s-\sOptimistic\q,TCCacheSize_Unmatched=\q10\q,TCCommTimeout_Unmatched=\q10\q,CCPrepared=0,CCAllRecords=1,TCNRecords_Unmatched=\q10\q,TCODBCSyntax_Unmatched=\q\q,TCHTargetPlatform=\q\q,TCHTargetBrowser_Unmatched=\qServer\s(ASP)\q,TCTargetPlatform=\qInherit\sfrom\spage\q,RCCache=\qRCBookPage\q,CCOpen=1,GCParameters=(Rows=0))">
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
	cmdTmp.CommandText = '`GuestBk`';
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
<OBJECT classid="clsid:B6FC3A14-F837-11D0-9CC8-006008058731" height=27 id=btnView 
style="HEIGHT: 27px; LEFT: 0px; TOP: 0px; WIDTH: 113px" width=113>
	<PARAM NAME="_ExtentX" VALUE="4101">
	<PARAM NAME="_ExtentY" VALUE="714">
	<PARAM NAME="id" VALUE="btnView">
	<PARAM NAME="Caption" VALUE="Afficher le livre d\'or">
	<PARAM NAME="Image" VALUE="">
	<PARAM NAME="AltText" VALUE="">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="Platform" VALUE="256">
	<PARAM NAME="LocalPath" VALUE="../">
	
 </OBJECT>
-->
<!--#INCLUDE FILE="../_ScriptLibrary/Button.ASP"-->
<SCRIPT LANGUAGE=JavaScript RUNAT=Server>
function _initbtnView()
{
	btnView.value = 'Afficher le livre d\'or';
	btnView.setStyle(0);
}
function _btnView_ctor()
{
	CreateButton('btnView', _initbtnView, null);
}
</script>
<% btnView.display %>

<!--METADATA TYPE="DesignerControl" endspan-->
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B6FC3A14-F837-11D0-9CC8-006008058731" height=27 id=btnSign 
style="HEIGHT: 27px; LEFT: 0px; TOP: 0px; WIDTH: 111px" width=111>
	<PARAM NAME="_ExtentX" VALUE="3916">
	<PARAM NAME="_ExtentY" VALUE="714">
	<PARAM NAME="id" VALUE="btnSign">
	<PARAM NAME="Caption" VALUE="Signer le livre d\'or">
	<PARAM NAME="Image" VALUE="">
	<PARAM NAME="AltText" VALUE="">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="Platform" VALUE="256">
	<PARAM NAME="LocalPath" VALUE="../">
	
 </OBJECT>
-->
<SCRIPT LANGUAGE=JavaScript RUNAT=Server>
function _initbtnSign()
{
	btnSign.value = 'Signer le livre d\'or';
	btnSign.setStyle(0);
}
function _btnSign_ctor()
{
	CreateButton('btnSign', _initbtnSign, null);
}
</script>
<% btnSign.display %>

<!--METADATA TYPE="DesignerControl" endspan-->
<BR><BR>
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B5F0E460-DC5F-11D0-9846-0000F8027CA0" height=17 id=lblName 
style="HEIGHT: 17px; LEFT: 0px; TOP: 0px; WIDTH: 60px" width=60>
	<PARAM NAME="_ExtentX" VALUE="1614">
	<PARAM NAME="_ExtentY" VALUE="450">
	<PARAM NAME="id" VALUE="lblName">
	<PARAM NAME="DataSource" VALUE="">
	<PARAM NAME="DataField" VALUE="Votre Nom :">
	<PARAM NAME="FontFace" VALUE="">
	<PARAM NAME="FontSize" VALUE="">
	<PARAM NAME="FontColor" VALUE="">
	<PARAM NAME="FontBold" VALUE="0">
	<PARAM NAME="FontItalic" VALUE="0">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="FormatAsHTML" VALUE="0">
	<PARAM NAME="Platform" VALUE="256">
	<PARAM NAME="LocalPath" VALUE="../">
	
 </OBJECT>
-->
<!--#INCLUDE FILE="../_ScriptLibrary/Label.ASP"-->
<SCRIPT LANGUAGE=JavaScript RUNAT=Server>
function _initlblName()
{
	lblName.setCaption('Votre Nom :');
}
function _lblName_ctor()
{
	CreateLabel('lblName', _initlblName, null);
}
</script>
<% lblName.display %>

<!--METADATA TYPE="DesignerControl" endspan-->
<BR>
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B5F0E469-DC5F-11D0-9846-0000F8027CA0" height=19 id=txtName 
style="HEIGHT: 19px; LEFT: 0px; TOP: 0px; WIDTH: 120px" width=120>
	<PARAM NAME="_ExtentX" VALUE="3175">
	<PARAM NAME="_ExtentY" VALUE="503">
	<PARAM NAME="id" VALUE="txtName">
	<PARAM NAME="ControlType" VALUE="0">
	<PARAM NAME="Lines" VALUE="3">
	<PARAM NAME="DataSource" VALUE="DTCRecordset1">
	<PARAM NAME="DataField" VALUE="Name">
	<PARAM NAME="Enabled" VALUE="-1">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="MaxChars" VALUE="20">
	<PARAM NAME="DisplayWidth" VALUE="20">
	<PARAM NAME="Platform" VALUE="0">
	<PARAM NAME="LocalPath" VALUE="../">
	
 </OBJECT>
-->
<!--#INCLUDE FILE="../_ScriptLibrary/TextBox.ASP"-->
<SCRIPT LANGUAGE=JavaScript RUNAT=Server>
function _inittxtName()
{
	txtName.setStyle(TXT_TEXTBOX);
	txtName.setDataSource(DTCRecordset1);
	txtName.setDataField('Name');
	txtName.setMaxLength(20);
	txtName.setColumnCount(20);
}
function _txtName_ctor()
{
	CreateTextbox('txtName', _inittxtName, null);
}
</script>
<% txtName.display %>

<!--METADATA TYPE="DesignerControl" endspan-->
<BR>
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B5F0E460-DC5F-11D0-9846-0000F8027CA0" height=17 
id=lblComments style="HEIGHT: 17px; LEFT: 0px; TOP: 0px; WIDTH: 56px" width=56>
	<PARAM NAME="_ExtentX" VALUE="1535">
	<PARAM NAME="_ExtentY" VALUE="450">
	<PARAM NAME="id" VALUE="lblComments">
	<PARAM NAME="DataSource" VALUE="">
	<PARAM NAME="DataField" VALUE="Comments:">
	<PARAM NAME="FontFace" VALUE="">
	<PARAM NAME="FontSize" VALUE="">
	<PARAM NAME="FontColor" VALUE="">
	<PARAM NAME="FontBold" VALUE="0">
	<PARAM NAME="FontItalic" VALUE="0">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="FormatAsHTML" VALUE="0">
	<PARAM NAME="Platform" VALUE="256">
	<PARAM NAME="LocalPath" VALUE="../">
	
 </OBJECT>
-->
<SCRIPT LANGUAGE=JavaScript RUNAT=Server>
function _initlblComments()
{
	lblComments.setCaption('Commentaires :');
}
function _lblComments_ctor()
{
	CreateLabel('lblComments', _initlblComments, null);
}
</script>
<% lblComments.display %>

<!--METADATA TYPE="DesignerControl" endspan-->
<BR>
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B5F0E469-DC5F-11D0-9846-0000F8027CA0" height=65 
id=txtComments style="HEIGHT: 65px; LEFT: 0px; TOP: 0px; WIDTH: 300px" 
width=300>
	<PARAM NAME="_ExtentX" VALUE="7938">
	<PARAM NAME="_ExtentY" VALUE="1720">
	<PARAM NAME="id" VALUE="txtComments">
	<PARAM NAME="ControlType" VALUE="1">
	<PARAM NAME="Lines" VALUE="5">
	<PARAM NAME="DataSource" VALUE="DTCRecordset1">
	<PARAM NAME="DataField" VALUE="Comment">
	<PARAM NAME="Enabled" VALUE="-1">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="MaxChars" VALUE="256">
	<PARAM NAME="DisplayWidth" VALUE="50">
	<PARAM NAME="Platform" VALUE="0">
	<PARAM NAME="LocalPath" VALUE="../">
	
 </OBJECT>
-->
<SCRIPT LANGUAGE=JavaScript RUNAT=Server>
function _inittxtComments()
{
	txtComments.setStyle(TXT_TEXTAREA);
	txtComments.setDataSource(DTCRecordset1);
	txtComments.setDataField('Comment');
	txtComments.setRowCount(5);
	txtComments.setColumnCount(50);
}
function _txtComments_ctor()
{
	CreateTextbox('txtComments', _inittxtComments, null);
}
</script>
<% txtComments.display %>

<!--METADATA TYPE="DesignerControl" endspan-->

<BR>
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B6FC3A14-F837-11D0-9CC8-006008058731" height=27 id=btnSave 
style="HEIGHT: 27px; LEFT: 0px; TOP: 0px; WIDTH: 43px" width=43>
	<PARAM NAME="_ExtentX" VALUE="1376">
	<PARAM NAME="_ExtentY" VALUE="714">
	<PARAM NAME="id" VALUE="btnSave">
	<PARAM NAME="Caption" VALUE="Save">
	<PARAM NAME="Image" VALUE="">
	<PARAM NAME="AltText" VALUE="">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="Platform" VALUE="256">
	<PARAM NAME="LocalPath" VALUE="../">
	
 </OBJECT>
-->
<SCRIPT LANGUAGE=JavaScript RUNAT=Server>
function _initbtnSave()
{
	btnSave.value = 'Sauvegarder';
	btnSave.setStyle(0);
}
function _btnSave_ctor()
{
	CreateButton('btnSave', _initbtnSave, null);
}
</script>
<% btnSave.display %>

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
	<PARAM NAME="AdvTableTag" VALUE="">
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
	<PARAM NAME="ColumnsNames" VALUE='"Nom","Commentaire"'>
	<PARAM NAME="columnIndex" VALUE="0,1">
	<PARAM NAME="displayWidth" VALUE="68,241">
	<PARAM NAME="Coltype" VALUE="1,1">
	<PARAM NAME="formated" VALUE="0,0">
	<PARAM NAME="DisplayName" VALUE='"Nom","Commentaires"'>
	<PARAM NAME="DetailAlignment" VALUE=",">
	<PARAM NAME="HeaderAlignment" VALUE=",">
	<PARAM NAME="DetailBackColor" VALUE=",">
	<PARAM NAME="HeaderBackColor" VALUE=",">
	<PARAM NAME="HeaderFont" VALUE=",">
	<PARAM NAME="HeaderFontColor" VALUE=",">
	<PARAM NAME="HeaderFontSize" VALUE=",">
	<PARAM NAME="HeaderFontStyle" VALUE=",">
	<PARAM NAME="DetailFont" VALUE=",">
	<PARAM NAME="DetailFontColor" VALUE=",">
	<PARAM NAME="DetailFontSize" VALUE=",">
	<PARAM NAME="DetailFontStyle" VALUE=",">
	<PARAM NAME="ColumnCount" VALUE="2">
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
	<PARAM NAME="PageSize" VALUE="10">
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
	<PARAM NAME="LocalPath" VALUE="../">
	
 
</OBJECT>
-->
<!--#INCLUDE FILE="../_ScriptLibrary/RSNavBar.ASP"-->
<!--#INCLUDE FILE="../_ScriptLibrary/DataGrid.ASP"-->
<SCRIPT LANGUAGE=JavaScript RUNAT=Server>
function _initGrid1()
{
Grid1.pageSize = 0;
Grid1.setDataSource(DTCRecordset1);
Grid1.tableAttributes = ' cellpadding=2  cellspacing=0 bordercolor=#cccccc bgcolor=White border=1 cols=2 rules=ALL';
Grid1.headerAttributes = '   bgcolor=#003468 align=Left';
Grid1.headerWidth[0] = '';
Grid1.headerWidth[1] = '';
Grid1.headerFormat = '<Font face="Arial" size=4 color=White> <b>';
Grid1.colHeader[0] = '\'Nom\'';
Grid1.colHeader[1] = '\'Commentaire\'';
Grid1.rowAttributes[0] = '  bgcolor = White align=Left bordercolor=#cccccc';
Grid1.rowAttributes[1] = '  bgcolor = Silver align=Left bordercolor=#cccccc';
Grid1.rowFormat[0] = ' <Font face="Arial" size=2 color=Black >';
Grid1.colAttributes[0] = ' ';
Grid1.colFormat[0] = '<Font Size=2 Face="Arial" Color=Black >';
Grid1.colData[0] = 'DTCRecordset1.fields.getValue(\'Name\')';
Grid1.colAttributes[1] = ' ';
Grid1.colFormat[1] = '<Font Size=2 Face="Arial" Color=Black >';
Grid1.colData[1] = 'DTCRecordset1.fields.getValue(\'Comment\')';
}
function _Grid1_ctor()
{
	CreateDataGrid('Grid1',_initGrid1);
}
</SCRIPT>

<%	Grid1.display %>


<!--METADATA TYPE="DesignerControl" endspan-->
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:CEB04D01-0445-11D1-BB81-006097C553C8" id=FormManager1 
style="LEFT: 0px; TOP: 0px">
	<PARAM NAME="ExtentX" VALUE="4233">
	<PARAM NAME="ExtentY" VALUE="609">
	<PARAM NAME="State" VALUE="(txtName_Unmatched=\qFormManager1\q,txtNewMode_Unmatched=\q\q,grFormMode=(Rows=2,Row1=(txtMode_Unmatched=\qView\q),Row2=(txtMode_Unmatched=\qSign\q)),txtDefaultMode=\qView\q,grMasterMode=(Rows=16,Row1=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qbtnSave\q,txtProperty_Unmatched=\qhide\q,txtValue_Unmatched=\q()\q),Row2=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qbtnSign\q,txtProperty_Unmatched=\qdisabled\q,txtValue_Unmatched=\qfalse\q),Row3=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qbtnView\q,txtProperty_Unmatched=\qdisabled\q,txtValue_Unmatched=\qtrue\q),Row4=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qtxtComments\q,txtProperty_Unmatched=\qhide\q,txtValue_Unmatched=\q()\q),Row5=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qtxtName\q,txtProperty_Unmatched=\qhide\q,txtValue_Unmatched=\q()\q),Row6=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qlblComments\q,txtProperty_Unmatched=\qhide\q,txtValue_Unmatched=\q()\q),Row7=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qlblName\q,txtProperty_Unmatched=\qhide\q,txtValue_Unmatched=\q()\q),Row8=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qGrid1\q,txtProperty_Unmatched=\qshow\q,txtValue_Unmatched=\q()\q),Row9=(txtName_Unmatched=\q2\q,txtControl_Unmatched=\qbtnSign\q,txtProperty_Unmatched=\qdisabled\q,txtValue_Unmatched=\qtrue\q),Row10=(txtName_Unmatched=\q2\q,txtControl_Unmatched=\qbtnSave\q,txtProperty_Unmatched=\qshow\q,txtValue_Unmatched=\q()\q),Row11=(txtName_Unmatched=\q2\q,txtControl_Unmatched=\qbtnView\q,txtProperty_Unmatched=\qdisabled\q,txtValue_Unmatched=\qfalse\q),Row12=(txtName_Unmatched=\q2\q,txtControl_Unmatched=\qtxtComments\q,txtProperty_Unmatched=\qshow\q,txtValue_Unmatched=\q()\q),Row13=(txtName_Unmatched=\q2\q,txtControl_Unmatched=\qtxtName\q,txtProperty_Unmatched=\qshow\q,txtValue_Unmatched=\q()\q),Row14=(txtName_Unmatched=\q2\q,txtControl_Unmatched=\qlblComments\q,txtProperty_Unmatched=\qshow\q,txtValue_Unmatched=\q()\q),Row15=(txtName_Unmatched=\q2\q,txtControl_Unmatched=\qlblName\q,txtProperty_Unmatched=\qshow\q,txtValue_Unmatched=\q()\q),Row16=(txtName_Unmatched=\q2\q,txtControl_Unmatched=\qGrid1\q,txtProperty_Unmatched=\qhide\q,txtValue_Unmatched=\q()\q)),grTransitions=(Rows=3,Row1=(txtCurrentMode=\qSign\q,txtObject=\qbtnView\q,txtEvent=\qonclick\q,txtNextMode=\qView\q),Row2=(txtCurrentMode=\qView\q,txtObject=\qbtnSign\q,txtEvent=\qonclick\q,txtNextMode=\qSign\q),Row3=(txtCurrentMode=\qSign\q,txtObject=\qbtnSave\q,txtEvent=\qonclick\q,txtNextMode=\qView\q)),grMasterStep=(Rows=3,Row1=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qDTCRecordset1\q,txtAction_Unmatched=\qcancelUpdate\q,txtValue_Unmatched=\q()\q),Row2=(txtName_Unmatched=\q2\q,txtControl_Unmatched=\qDTCRecordset1\q,txtAction_Unmatched=\qaddRecord\q,txtValue_Unmatched=\q()\q),Row3=(txtName_Unmatched=\q3\q,txtControl_Unmatched=\qDTCRecordset1\q,txtAction_Unmatched=\qupdateRecord\q,txtValue_Unmatched=\q()\q)))">
	
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
		_FormManager1_SetMode("View");
	btnView.advise("onclick", "_FormManager1_btnView_onclick()");
	btnSign.advise("onclick", "_FormManager1_btnSign_onclick()");
	btnSave.advise("onclick", "_FormManager1_btnSave_onclick()");
}
function _FormManager1_SetMode(formmode)
{
	thisPage.setState("FormManager1_formmode", formmode);
	if (formmode == "View")
	{
		btnSave.hide();
		btnSign.disabled = false;
		btnView.disabled = true;
		txtComments.hide();
		txtName.hide();
		lblComments.hide();
		lblName.hide();
		Grid1.show();
	}
	if (formmode == "Sign")
	{
		btnSign.disabled = true;
		btnSave.show();
		btnView.disabled = false;
		txtComments.show();
		txtName.show();
		lblComments.show();
		lblName.show();
		Grid1.hide();
	}
}
function _FormManager1_btnView_onclick()
{
	if (thisPage.getState("FormManager1_formmode") == "Sign")
	{
		DTCRecordset1.cancelUpdate();
		_FormManager1_SetMode("View");
	}
	else _FormManager1_SetMode(thisPage.getState("FormManager1_formmode"))
}
function _FormManager1_btnSign_onclick()
{
	if (thisPage.getState("FormManager1_formmode") == "View")
	{
		DTCRecordset1.addRecord();
		_FormManager1_SetMode("Sign");
	}
	else _FormManager1_SetMode(thisPage.getState("FormManager1_formmode"))
}
function _FormManager1_btnSave_onclick()
{
	if (thisPage.getState("FormManager1_formmode") == "Sign")
	{
		DTCRecordset1.updateRecord();
		_FormManager1_SetMode("View");
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
