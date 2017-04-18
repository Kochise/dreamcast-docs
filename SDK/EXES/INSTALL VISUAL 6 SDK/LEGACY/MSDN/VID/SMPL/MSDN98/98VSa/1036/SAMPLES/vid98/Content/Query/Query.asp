<%@ LANGUAGE=VBScript %>
<% ' VI 6.0 Scripting Object Model Enabled %>
<!--#include file="../_ScriptLibrary/pm.asp"-->
<% if StartPageProcessing() Then Response.End() %>
<FORM name=thisForm METHOD=post>
<HTML>
<BODY bgColor=#ffffff leftMargin=40 link=#500000 vLink=#505050>
<FONT FACE="Verdana, Arial, Helvetica" SIZE=2>
<P>
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B5F0E450-DC5F-11D0-9846-0000F8027CA0" height=21 id=Listbox1 
style="HEIGHT: 21px; LEFT: 10px; TOP: 35px; WIDTH: 117px" width=117><PARAM NAME="_ExtentX" VALUE="3096"><PARAM NAME="_ExtentY" VALUE="556"><PARAM NAME="id" VALUE="Listbox1"><PARAM NAME="DataSource" VALUE=""><PARAM NAME="DataField" VALUE=""><PARAM NAME="ControlStyle" VALUE="0"><PARAM NAME="Enabled" VALUE="-1"><PARAM NAME="Visible" VALUE="-1"><PARAM NAME="Platform" VALUE="256"><PARAM NAME="UsesStaticList" VALUE="-1"><PARAM NAME="CLSize" VALUE="11"><PARAM NAME="CLED0" VALUE="Customer ID"><PARAM NAME="CLEV0" VALUE="CustomerID"><PARAM NAME="CLED1" VALUE="Company Name"><PARAM NAME="CLEV1" VALUE="CompanyName"><PARAM NAME="CLED2" VALUE="Contact Name"><PARAM NAME="CLEV2" VALUE="ContactName"><PARAM NAME="CLED3" VALUE="Contact Title"><PARAM NAME="CLEV3" VALUE="ContactTitle"><PARAM NAME="CLED4" VALUE="Address"><PARAM NAME="CLEV4" VALUE="Address"><PARAM NAME="CLED5" VALUE="City"><PARAM NAME="CLEV5" VALUE="City"><PARAM NAME="CLED6" VALUE="Region"><PARAM NAME="CLEV6" VALUE="Region"><PARAM NAME="CLED7" VALUE="Postal Code"><PARAM NAME="CLEV7" VALUE="PostalCode"><PARAM NAME="CLED8" VALUE="Country"><PARAM NAME="CLEV8" VALUE="Country"><PARAM NAME="CLED9" VALUE="Phone"><PARAM NAME="CLEV9" VALUE="Phone"><PARAM NAME="CLED10" VALUE="Fax"><PARAM NAME="CLEV10" VALUE="Fax"><PARAM NAME="LocalPath" VALUE="../">
 
</OBJECT>
-->
<!--#INCLUDE FILE="../_ScriptLibrary/ListBox.ASP"-->
<script runat="server" language="JavaScript">
function _Listbox1_ctor()
{
    CreateListbox('Listbox1', _initListbox1);
}
function _initListbox1()
{
   Listbox1.addItem('ID client', 'CustomerID');
   Listbox1.addItem('Société', 'CompanyName');
   Listbox1.addItem('Contact', 'ContactName');
   Listbox1.addItem('Fonction du contact', 'ContactTitle');
   Listbox1.addItem('Adresse', 'Address');
   Listbox1.addItem('Ville', 'City');
   Listbox1.addItem('Région', 'Region');
   Listbox1.addItem('Code postal', 'PostalCode');
   Listbox1.addItem('Pays', 'Country');
   Listbox1.addItem('Téléphone', 'Phone');
   Listbox1.addItem('Télécopie', 'Fax');
}
</script>
<%Listbox1.display%>

<!--METADATA TYPE="DesignerControl" endspan-->
 <!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B5F0E450-DC5F-11D0-9846-0000F8027CA0" height=21 id=Listbox2 
	style="HEIGHT: 21px; LEFT: 10px; TOP: 56px; WIDTH: 96px" width=96>
	<PARAM NAME="_ExtentX" VALUE="2540">
	<PARAM NAME="_ExtentY" VALUE="556">
	<PARAM NAME="id" VALUE="Listbox2">
	<PARAM NAME="DataSource" VALUE="">
	<PARAM NAME="DataField" VALUE="">
	<PARAM NAME="ControlStyle" VALUE="0">
	<PARAM NAME="Enabled" VALUE="-1">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="Platform" VALUE="256">
	<PARAM NAME="UsesStaticList" VALUE="-1">
	<PARAM NAME="CLSize" VALUE="2">
	<PARAM NAME="CLED0" VALUE="Contains">
	<PARAM NAME="CLEV0" VALUE="Contains">
	<PARAM NAME="CLED1" VALUE="Begins with">
	<PARAM NAME="CLEV1" VALUE="Begins">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<script runat="server" language="JavaScript">
function _Listbox2_ctor()
{
    CreateListbox('Listbox2', _initListbox2);
}
function _initListbox2()
{
   Listbox2.addItem('Contient', 'Contains');
   Listbox2.addItem('Commençant par', 'Begins');
}
</script>
<%Listbox2.display%>

<!--METADATA TYPE="DesignerControl" endspan-->
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B5F0E469-DC5F-11D0-9846-0000F8027CA0" id=Textbox1 
style="LEFT: 0px; TOP: 0px"><PARAM NAME="_ExtentX" VALUE="3175"><PARAM NAME="_ExtentY" VALUE="503"><PARAM NAME="id" VALUE="Textbox1"><PARAM NAME="ControlType" VALUE="0"><PARAM NAME="Lines" VALUE="3"><PARAM NAME="DataSource" VALUE=""><PARAM NAME="DataField" VALUE=""><PARAM NAME="Enabled" VALUE="-1"><PARAM NAME="Visible" VALUE="-1"><PARAM NAME="MaxChars" VALUE="20"><PARAM NAME="DisplayWidth" VALUE="20"><PARAM NAME="Platform" VALUE="256"><PARAM NAME="LocalPath" VALUE="../">
 </OBJECT>
-->
<!--#INCLUDE FILE="../_ScriptLibrary/TextBox.ASP"-->
<script runat="server" language="JavaScript">
function _Textbox1_ctor()
{
    CreateTextbox('Textbox1', _initTextbox1);
}
function _initTextbox1()
{
   Textbox1.setMaxLength(20);
   Textbox1.setColumnCount(20);
}
</script>
<%Textbox1.display%>

<!--METADATA TYPE="DesignerControl" endspan-->
 
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B6FC3A14-F837-11D0-9CC8-006008058731" height=27 id=Button1 style="HEIGHT: 27px; LEFT: 0px; TOP: 0px; WIDTH: 54px" 
	width=54>
	<PARAM NAME="_ExtentX" VALUE="2540">
	<PARAM NAME="_ExtentY" VALUE="714">
	<PARAM NAME="id" VALUE="Button1">
	<PARAM NAME="Caption" VALUE="Rechercher">
	<PARAM NAME="Image" VALUE="">
	<PARAM NAME="AltText" VALUE="">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="Platform" VALUE="256">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<!--#INCLUDE FILE="../_ScriptLibrary/Button.ASP"-->
<SCRIPT LANGUAGE=JavaScript RUNAT=Server>
function _initButton1()
{
	Button1.value = 'Rechercher';
	Button1.setStyle(0);
}
function _Button1_ctor()
{
	CreateButton('Button1', _initButton1, null);
}
</script>
<% Button1.display %>

<!--METADATA TYPE="DesignerControl" endspan-->
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:CEB04D01-0445-11D1-BB81-006097C553C8" id=FormManager1 style="LEFT: 0px; TOP: 0px">
	<PARAM NAME="ExtentX" VALUE="4233">
	<PARAM NAME="ExtentY" VALUE="609">
	<PARAM NAME="State" VALUE="(txtName_Unmatched=\qFormManager1\q,txtNewMode_Unmatched=\q\q,grFormMode=(Rows=1,Row1=(txtMode_Unmatched=\qTest\q)),txtDefaultMode=\qTest\q,grMasterMode=(Rows=1,Row1=(txtName_Unmatched=\q1\q)),grTransitions=(Rows=1,Row1=(txtCurrentMode=\qTest\q,txtObject=\qButton1\q,txtEvent=\qonclick\q,txtNextMode=\qTest\q)),grMasterStep=(Rows=1,Row1=(txtName_Unmatched=\q1\q)))"></OBJECT>
-->
<SCRIPT RUNAT=SERVER LANGUAGE="JavaScript">
function _FormManager1_ctor()
{
	thisPage.advise(PAGE_ONINIT, _FormManager1_init);
}
function _FormManager1_init()
{
	if (thisPage.getState("FormManager1_formmode") == null)
		_FormManager1_SetMode("Test");
	Button1.advise("onclick", "_FormManager1_Button1_onclick()");
}
function _FormManager1_SetMode(formmode)
{
	thisPage.setState("FormManager1_formmode", formmode);
	if (formmode == "Test")
	{
	}
}
function _FormManager1_Button1_onclick()
{
	if (thisPage.getState("FormManager1_formmode") == "Test")
	{
		_FormManager1_SetMode("Test");
	}
	else _FormManager1_SetMode(thisPage.getState("FormManager1_formmode"))
}
</SCRIPT>


<!--METADATA TYPE="DesignerControl" endspan-->
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:9CF5D7C2-EC10-11D0-9862-0000F8027CA0" id=Recordset1 style="LEFT: 0px; TOP: 0px">
	<PARAM NAME="ExtentX" VALUE="12197">
	<PARAM NAME="ExtentY" VALUE="2090">
	<PARAM NAME="State" VALUE="(TCConn=\qGallery\q,TCDBObject_Unmatched=\qSQL\sStatement\q,TCDBObjectName_Unmatched=\qSELECT\s*\sFROM\sCustomers\q,TCControlID_Unmatched=\qRecordset1\q,TCPPConn=\qGallery\q,TCPPDBObject=\qTables\q,TCPPDBObjectName=\qCounter\q,RCDBObject=\qRCSQLStatement\q,TCSQLStatement_Unmatched=\qSELECT\s*\sFROM\sCustomers\q,TCCursorType=\q3\s-\sStatic\q,TCCursorLocation=\q3\s-\sUse\sclient-side\scursors\q,TCLockType=\q3\s-\sOptimistic\q,TCCacheSize_Unmatched=\q10\q,TCCommTimeout_Unmatched=\q10\q,CCPrepared=0,CCAllRecords=1,TCNRecords_Unmatched=\q10\q,TCODBCSyntax_Unmatched=\q\q,TCHTargetPlatform=\q\q,TCHTargetBrowser_Unmatched=\qServer\s(ASP)\q,TCTargetPlatform=\qInherit\sfrom\spage\q,RCCache=\qRCBookPage\q,CCOpen=0,GCParameters=(Rows=0))">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<!--#INCLUDE FILE="../_ScriptLibrary/Recordset.ASP"-->
<SCRIPT LANGUAGE="JavaScript" RUNAT="server">
function _initRecordset1()
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
	cmdTmp.CommandText = 'SELECT * FROM Customers';
	rsTmp.CacheSize = 10;
	rsTmp.CursorType = 3;
	rsTmp.CursorLocation = 3;
	rsTmp.LockType = 3;
	Recordset1.setRecordSource(rsTmp);
	if (thisPage.getState('pb_Recordset1') != null)
		Recordset1.setBookmark(thisPage.getState('pb_Recordset1'));
}
function _Recordset1_ctor()
{
	CreateRecordset('Recordset1', _initRecordset1, null);
}
function _Recordset1_dtor()
{
	Recordset1._preserveState();
	thisPage.setState('pb_Recordset1', Recordset1.getBookmark());
}
</SCRIPT>

<!--METADATA TYPE="DesignerControl" endspan-->
</P>
<SCRIPT LANGUAGE=javascript RUNAT=Server>
	function Button1_onclick() {
		if (Listbox2.getValue(Listbox2.selectedIndex) == "Contains") {
			newSQL = "Select * FROM Customers WHERE (" + Listbox1.getValue(Listbox1.selectedIndex) + " LIKE '%" + Textbox1.value + "%')";
		}	
		else {
			newSQL = "Select * FROM Customers WHERE (" + Listbox1.getValue(Listbox1.selectedIndex) + " LIKE '" + Textbox1.value + "%')";
		}		
		if (Recordset1.isOpen()) {
			Recordset1.close();
		}
		Recordset1.setSQLText(newSQL);
		Recordset1.open();
	}
</SCRIPT>

<P>
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:277FC3F2-E90F-11D0-B767-0000F81E081D" id=Grid1 style="LEFT: 0px; TOP: 0px">
	<PARAM NAME="_ExtentX" VALUE="8043">
	<PARAM NAME="_ExtentY" VALUE="3889">
	<PARAM NAME="DataConnection" VALUE="">
	<PARAM NAME="SourceType" VALUE="">
	<PARAM NAME="Recordset" VALUE="Recordset1">
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
	<PARAM NAME="ColumnsNames" VALUE='"CustomerID","CompanyName","ContactName","ContactTitle","Address","City","Region","PostalCode","Country","Phone","Fax"'>
	<PARAM NAME="columnIndex" VALUE="0,1,2,3,4,5,6,7,8,9,10">
	<PARAM NAME="displayWidth" VALUE="68,68,68,64,68,68,68,68,68,68,68">
	<PARAM NAME="Coltype" VALUE="1,1,1,1,1,1,1,1,1,1,1">
	<PARAM NAME="formated" VALUE="0,0,0,0,0,0,0,0,0,0,0">
	<PARAM NAME="DisplayName" VALUE='"Customer ID","Company Name","Contact Name","Contact Title","Address","City","Region","Postal Code","Country","Phone","Fax"'>
	<PARAM NAME="DetailAlignment" VALUE=",,,,,,,,,,">
	<PARAM NAME="HeaderAlignment" VALUE=",,,,,,,,,,">
	<PARAM NAME="DetailBackColor" VALUE=",,,,,,,,,,">
	<PARAM NAME="HeaderBackColor" VALUE=",,,,,,,,,,">
	<PARAM NAME="HeaderFont" VALUE=",,,,,,,,,,">
	<PARAM NAME="HeaderFontColor" VALUE=",,,,,,,,,,">
	<PARAM NAME="HeaderFontSize" VALUE=",,,,,,,,,,">
	<PARAM NAME="HeaderFontStyle" VALUE=",,,,,,,,,,">
	<PARAM NAME="DetailFont" VALUE=",,,,,,,,,,">
	<PARAM NAME="DetailFontColor" VALUE=",,,,,,,,,,">
	<PARAM NAME="DetailFontSize" VALUE=",,,,,,,,,,">
	<PARAM NAME="DetailFontStyle" VALUE=",,,,,,,,,,">
	<PARAM NAME="ColumnCount" VALUE="11">
	<PARAM NAME="CurStyle" VALUE="Teal Titles 3D">
	<PARAM NAME="TitleFont" VALUE="Arial">
	<PARAM NAME="titleFontSize" VALUE="2">
	<PARAM NAME="TitleFontColor" VALUE="0">
	<PARAM NAME="TitleBackColor" VALUE="32896">
	<PARAM NAME="TitleFontStyle" VALUE="0">
	<PARAM NAME="TitleAlignment" VALUE="0">
	<PARAM NAME="RowFont" VALUE="Arial">
	<PARAM NAME="RowFontColor" VALUE="0">
	<PARAM NAME="RowFontStyle" VALUE="0">
	<PARAM NAME="RowFontSize" VALUE="1">
	<PARAM NAME="RowBackColor" VALUE="12632256">
	<PARAM NAME="RowAlignment" VALUE="0">
	<PARAM NAME="HighlightColor3D" VALUE="0">
	<PARAM NAME="ShadowColor3D" VALUE="16777215">
	<PARAM NAME="PageSize" VALUE="10">
	<PARAM NAME="MoveFirstCaption" VALUE="    |<    ">
	<PARAM NAME="MoveLastCaption" VALUE="    >|    ">
	<PARAM NAME="MovePrevCaption" VALUE="    <    ">
	<PARAM NAME="MoveNextCaption" VALUE="    >    ">
	<PARAM NAME="BorderSize" VALUE="3">
	<PARAM NAME="BorderColor" VALUE="16777215">
	<PARAM NAME="GridBackColor" VALUE="12632256">
	<PARAM NAME="AltRowBckgnd" VALUE="268435455">
	<PARAM NAME="CellSpacing" VALUE="1">
	<PARAM NAME="WidthSelectionMode" VALUE="1">
	<PARAM NAME="GridWidth" VALUE="304">
	<PARAM NAME="EnablePaging" VALUE="-1">
	<PARAM NAME="ShowStatus" VALUE="-1">
	<PARAM NAME="StyleValue" VALUE="472013">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<!--#INCLUDE FILE="../_ScriptLibrary/RSNavBar.ASP"-->
<!--#INCLUDE FILE="../_ScriptLibrary/DataGrid.ASP"-->
<SCRIPT LANGUAGE=JavaScript RUNAT=Server>
function _initGrid1()
{
Grid1.pageSize = 10;
Grid1.setDataSource(Recordset1);
Grid1.tableAttributes = 'align=center cellpadding=2  cellspacing=1 bordercolordark=White bordercolorlight=Black bgcolor=Silver border=3 cols=11 rules=ALL WIDTH=304 nowrap';
Grid1.headerAttributes = '   bgcolor=Teal align=Left nowrap';
Grid1.headerWidth[0] = ' WIDTH=68';
Grid1.headerWidth[1] = ' WIDTH=68';
Grid1.headerWidth[2] = ' WIDTH=68';
Grid1.headerWidth[3] = ' WIDTH=68';
Grid1.headerWidth[4] = ' WIDTH=68';
Grid1.headerWidth[5] = ' WIDTH=68';
Grid1.headerWidth[6] = ' WIDTH=68';
Grid1.headerWidth[7] = ' WIDTH=68';
Grid1.headerWidth[8] = ' WIDTH=68';
Grid1.headerWidth[9] = ' WIDTH=68';
Grid1.headerWidth[10] = ' WIDTH=68';
Grid1.headerFormat = '<Font face="Arial" size=2 color=Black> ';
Grid1.colHeader[0] = '\'ID client\'';
Grid1.colHeader[1] = '\'Société\'';
Grid1.colHeader[2] = '\'Contact\'';
Grid1.colHeader[3] = '\'Fonction du contact\'';
Grid1.colHeader[4] = '\'Addresse\'';
Grid1.colHeader[5] = '\'Ville\'';
Grid1.colHeader[6] = '\'Région\'';
Grid1.colHeader[7] = '\'Code postal\'';
Grid1.colHeader[8] = '\'Pays\'';
Grid1.colHeader[9] = '\'Téléphone\'';
Grid1.colHeader[10] = '\'Télécopie\'';
Grid1.rowAttributes[0] = '  bgcolor = Silver align=Left nowrap  bordercolordark=White bordercolorlight=Black';
Grid1.rowFormat[0] = ' <Font face="Arial" size=1 color=Black >';
Grid1.colAttributes[0] = '  WIDTH=68';
Grid1.colFormat[0] = '<Font Size=1 Face="Arial" Color=Black >';
Grid1.colData[0] = 'Recordset1.fields.getValue(\'CustomerID\')';
Grid1.colAttributes[1] = '  WIDTH=68';
Grid1.colFormat[1] = '<Font Size=1 Face="Arial" Color=Black >';
Grid1.colData[1] = 'Recordset1.fields.getValue(\'CompanyName\')';
Grid1.colAttributes[2] = '  WIDTH=68';
Grid1.colFormat[2] = '<Font Size=1 Face="Arial" Color=Black >';
Grid1.colData[2] = 'Recordset1.fields.getValue(\'ContactName\')';
Grid1.colAttributes[3] = '  WIDTH=64';
Grid1.colFormat[3] = '<Font Size=1 Face="Arial" Color=Black >';
Grid1.colData[3] = 'Recordset1.fields.getValue(\'ContactTitle\')';
Grid1.colAttributes[4] = '  WIDTH=68';
Grid1.colFormat[4] = '<Font Size=1 Face="Arial" Color=Black >';
Grid1.colData[4] = 'Recordset1.fields.getValue(\'Address\')';
Grid1.colAttributes[5] = '  WIDTH=68';
Grid1.colFormat[5] = '<Font Size=1 Face="Arial" Color=Black >';
Grid1.colData[5] = 'Recordset1.fields.getValue(\'City\')';
Grid1.colAttributes[6] = '  WIDTH=68';
Grid1.colFormat[6] = '<Font Size=1 Face="Arial" Color=Black >';
Grid1.colData[6] = 'Recordset1.fields.getValue(\'Region\')';
Grid1.colAttributes[7] = '  WIDTH=68';
Grid1.colFormat[7] = '<Font Size=1 Face="Arial" Color=Black >';
Grid1.colData[7] = 'Recordset1.fields.getValue(\'PostalCode\')';
Grid1.colAttributes[8] = '  WIDTH=68';
Grid1.colFormat[8] = '<Font Size=1 Face="Arial" Color=Black >';
Grid1.colData[8] = 'Recordset1.fields.getValue(\'Country\')';
Grid1.colAttributes[9] = '  WIDTH=68';
Grid1.colFormat[9] = '<Font Size=1 Face="Arial" Color=Black >';
Grid1.colData[9] = 'Recordset1.fields.getValue(\'Phone\')';
Grid1.colAttributes[10] = '  WIDTH=68';
Grid1.colFormat[10] = '<Font Size=1 Face="Arial" Color=Black >';
Grid1.colData[10] = 'Recordset1.fields.getValue(\'Fax\')';
Grid1.navbarAlignment = 'Left';
var objPageNavbar = Grid1.showPageNavbar(170,1);
objPageNavbar.getButton(0).value = '    |<    ';
objPageNavbar.getButton(1).value = '    <    ';
objPageNavbar.getButton(2).value = '    >    ';
objPageNavbar.getButton(3).value = '    >|    ';
Grid1.hasPageNumber = true;
}
function _Grid1_ctor()
{
	CreateDataGrid('Grid1',_initGrid1);
}
</SCRIPT>

<%	Grid1.display %>


<!--METADATA TYPE="DesignerControl" endspan-->
</P>
</FONT>
</BODY>
<% ' VI 6.0 Scripting Object Model Enabled %>
<% EndPageProcessing() %>
</FORM>
</HTML>
