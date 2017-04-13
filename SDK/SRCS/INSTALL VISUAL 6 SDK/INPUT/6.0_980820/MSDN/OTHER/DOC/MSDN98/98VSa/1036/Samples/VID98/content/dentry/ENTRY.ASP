<%@ LANGUAGE=VBScript %>
<% ' VI 6.0 Scripting Object Model Enabled %>
<!--#include file="../_ScriptLibrary/pm.asp"-->
<% if StartPageProcessing() Then Response.End() %>
<FORM name=thisForm METHOD=post>
<HTML>
<SCRIPT LANGUAGE=JScript RUNAT=Server>
	function disable_opt(optX) {
		for (var i=0; i < optX.getCount(); i++)
			optX.getButton(i).disabled = true;
	}
</SCRIPT>
<BODY bgColor=#ffffff leftMargin=40 link=#500000 vLink=#505050>  
<FONT FACE="Verdana, Arial, Helvetica" SIZE=2>  
     
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B6FC3A14-F837-11D0-9CC8-006008058731" id=BrowseBtn style="LEFT: 0px; TOP: 0px">
	<PARAM NAME="_ExtentX" VALUE="2910">
	<PARAM NAME="_ExtentY" VALUE="714">
	<PARAM NAME="id" VALUE="BrowseBtn">
	<PARAM NAME="Caption" VALUE="Mode Parcourir">
	<PARAM NAME="Image" VALUE="">
	<PARAM NAME="AltText" VALUE="">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="Platform" VALUE="256">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<!--#INCLUDE FILE="../_ScriptLibrary/Button.ASP"-->
<script runat="server" language="JavaScript">
function _initBrowseBtn()
{
    BrowseBtn.value = 'Mode Parcourir';
    BrowseBtn.setStyle(0);
}
function _BrowseBtn_ctor()
{
   CreateButton('BrowseBtn', _initBrowseBtn, null);
}
</script>
<% BrowseBtn.display %>

<!--METADATA TYPE="DesignerControl" endspan-->
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B6FC3A14-F837-11D0-9CC8-006008058731" id=EditBtn style="LEFT: 0px; TOP: 0px">
	<PARAM NAME="_ExtentX" VALUE="2275">
	<PARAM NAME="_ExtentY" VALUE="714">
	<PARAM NAME="id" VALUE="EditBtn">
	<PARAM NAME="Caption" VALUE="Mode édition">
	<PARAM NAME="Image" VALUE="">
	<PARAM NAME="AltText" VALUE="">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="Platform" VALUE="256">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<script runat="server" language="JavaScript">
function _initEditBtn()
{
    EditBtn.value = 'Mode édition';
    EditBtn.setStyle(0);
}
function _EditBtn_ctor()
{
   CreateButton('EditBtn', _initEditBtn, null);
}
</script>
<% EditBtn.display %>

<!--METADATA TYPE="DesignerControl" endspan-->
<BR><BR>
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B6FC3A14-F837-11D0-9CC8-006008058731" id=InsertBtn style="LEFT: 0px; TOP: 0px">
	<PARAM NAME="_ExtentX" VALUE="1429">
	<PARAM NAME="_ExtentY" VALUE="714">
	<PARAM NAME="id" VALUE="InsertBtn">
	<PARAM NAME="Caption" VALUE="Insérer">
	<PARAM NAME="Image" VALUE="">
	<PARAM NAME="AltText" VALUE="">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="Platform" VALUE="256">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<script runat="server" language="JavaScript">
function _initInsertBtn()
{
    InsertBtn.value = 'Insérer';
    InsertBtn.setStyle(0);
}
function _InsertBtn_ctor()
{
   CreateButton('InsertBtn', _initInsertBtn, null);
}
</script>
<% InsertBtn.display %>

<!--METADATA TYPE="DesignerControl" endspan-->
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B6FC3A14-F837-11D0-9CC8-006008058731" id=DeleteBtn style="LEFT: 0px; TOP: 0px">
	<PARAM NAME="_ExtentX" VALUE="1640">
	<PARAM NAME="_ExtentY" VALUE="714">
	<PARAM NAME="id" VALUE="DeleteBtn">
	<PARAM NAME="Caption" VALUE="Supprimer">
	<PARAM NAME="Image" VALUE="">
	<PARAM NAME="AltText" VALUE="">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="Platform" VALUE="256">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<script runat="server" language="JavaScript">
function _initDeleteBtn()
{
    DeleteBtn.value = 'Supprimer';
    DeleteBtn.setStyle(0);
}
function _DeleteBtn_ctor()
{
   CreateButton('DeleteBtn', _initDeleteBtn, null);
}
</script>
<% DeleteBtn.display %>

<!--METADATA TYPE="DesignerControl" endspan-->
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B6FC3A14-F837-11D0-9CC8-006008058731" id=UpdateBtn style="LEFT: 0px; TOP: 0px">
	<PARAM NAME="_ExtentX" VALUE="1773">
	<PARAM NAME="_ExtentY" VALUE="714">
	<PARAM NAME="id" VALUE="UpdateBtn">
	<PARAM NAME="Caption" VALUE="Actualiser">
	<PARAM NAME="Image" VALUE="">
	<PARAM NAME="AltText" VALUE="">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="Platform" VALUE="256">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<script runat="server" language="JavaScript">
function _initUpdateBtn()
{
    UpdateBtn.value = 'Actualiser';
    UpdateBtn.setStyle(0);
}
function _UpdateBtn_ctor()
{
   CreateButton('UpdateBtn', _initUpdateBtn, null);
}
</script>
<% UpdateBtn.display %>

<!--METADATA TYPE="DesignerControl" endspan-->
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B6FC3A14-F837-11D0-9CC8-006008058731" id=CancelBtn style="LEFT: 0px; TOP: 0px">
	<PARAM NAME="_ExtentX" VALUE="1693">
	<PARAM NAME="_ExtentY" VALUE="714">
	<PARAM NAME="id" VALUE="CancelBtn">
	<PARAM NAME="Caption" VALUE="Annuler">
	<PARAM NAME="Image" VALUE="">
	<PARAM NAME="AltText" VALUE="">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="Platform" VALUE="256">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<script runat="server" language="JavaScript">
function _initCancelBtn()
{
    CancelBtn.value = 'Annuler';
    CancelBtn.setStyle(0);
}
function _CancelBtn_ctor()
{
   CreateButton('CancelBtn', _initCancelBtn, null);
}
</script>
<% CancelBtn.display %>

<!--METADATA TYPE="DesignerControl" endspan-->
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:9CF5D7C2-EC10-11D0-9862-0000F8027CA0" id=DTCRecordset1 style="LEFT: 0px; TOP: 0px">
	<PARAM NAME="ExtentX" VALUE="12197">
	<PARAM NAME="ExtentY" VALUE="2090">
	<PARAM NAME="State" VALUE="(TCConn=\qGallery\q,TCDBObject=\qTables\q,TCDBObjectName=\qDEntry\q,TCControlID_Unmatched=\qDTCRecordset1\q,TCPPConn=\qGallery\q,RCDBObject=\qRCDBObject\q,TCPPDBObject=\qTables\q,TCPPDBObjectName=\qDEntry\q,TCCursorType=\q3\s-\sStatic\q,TCCursorLocation=\q3\s-\sUse\sclient-side\scursors\q,TCLockType=\q3\s-\sOptimistic\q,TCCacheSize_Unmatched=\q10\q,TCCommTimeout_Unmatched=\q10\q,CCPrepared=0,CCAllRecords=1,TCNRecords_Unmatched=\q10\q,TCODBCSyntax_Unmatched=\q\q,TCHTargetPlatform=\q\q,TCHTargetBrowser_Unmatched=\qServer\s(ASP)\q,TCTargetPlatform=\qInherit\sfrom\spage\q,RCCache=\qRCBookPage\q,CCOpen=1,GCParameters=(Rows=0))">
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
	cmdTmp.CommandText = '`DEntry`';
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

<TABLE>
<TR><TD ALIGN=Right>Pr&#233;nom :</TD>
<TD>
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B5F0E469-DC5F-11D0-9846-0000F8027CA0" height=25 id=Textbox1 
	style="HEIGHT: 25px; LEFT: 0px; TOP: 0px; WIDTH: 146px" width=146>
	<PARAM NAME="_ExtentX" VALUE="3863">
	<PARAM NAME="_ExtentY" VALUE="503">
	<PARAM NAME="id" VALUE="Textbox1">
	<PARAM NAME="ControlType" VALUE="0">
	<PARAM NAME="Lines" VALUE="3">
	<PARAM NAME="DataSource" VALUE="DTCRecordset1">
	<PARAM NAME="DataField" VALUE="FName">
	<PARAM NAME="Enabled" VALUE="-1">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="MaxChars" VALUE="20">
	<PARAM NAME="DisplayWidth" VALUE="24">
	<PARAM NAME="Platform" VALUE="0">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<!--#INCLUDE FILE="../_ScriptLibrary/TextBox.ASP"-->
<SCRIPT LANGUAGE=JavaScript RUNAT=Server>
function _initTextbox1()
{
	Textbox1.setStyle(TXT_TEXTBOX);
	Textbox1.setDataSource(DTCRecordset1);
	Textbox1.setDataField('FName');
	Textbox1.setMaxLength(20);
	Textbox1.setColumnCount(24);
}
function _Textbox1_ctor()
{
	CreateTextbox('Textbox1', _initTextbox1, null);
}
</script>
<% Textbox1.display %>

<!--METADATA TYPE="DesignerControl" endspan-->


</TD></TR>
<TR><TD ALIGN=Right>Nom :</TD>
<TD> 
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B5F0E469-DC5F-11D0-9846-0000F8027CA0" height=25 id=Textbox2 
	style="HEIGHT: 25px; LEFT: 0px; TOP: 0px; WIDTH: 146px" width=146>
	<PARAM NAME="_ExtentX" VALUE="3863">
	<PARAM NAME="_ExtentY" VALUE="503">
	<PARAM NAME="id" VALUE="Textbox2">
	<PARAM NAME="ControlType" VALUE="0">
	<PARAM NAME="Lines" VALUE="3">
	<PARAM NAME="DataSource" VALUE="DTCRecordset1">
	<PARAM NAME="DataField" VALUE="LName">
	<PARAM NAME="Enabled" VALUE="-1">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="MaxChars" VALUE="20">
	<PARAM NAME="DisplayWidth" VALUE="24">
	<PARAM NAME="Platform" VALUE="0">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<SCRIPT LANGUAGE=JavaScript RUNAT=Server>
function _initTextbox2()
{
	Textbox2.setStyle(TXT_TEXTBOX);
	Textbox2.setDataSource(DTCRecordset1);
	Textbox2.setDataField('LName');
	Textbox2.setMaxLength(20);
	Textbox2.setColumnCount(24);
}
function _Textbox2_ctor()
{
	CreateTextbox('Textbox2', _initTextbox2, null);
}
</script>
<% Textbox2.display %>

<!--METADATA TYPE="DesignerControl" endspan-->
</TD></TR>
<TR><TD ALIGN=Right>Adresse :</TD>
<TD>
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B5F0E469-DC5F-11D0-9846-0000F8027CA0" height=25 id=Textbox3 
	style="HEIGHT: 25px; LEFT: 0px; TOP: 0px; WIDTH: 146px" width=146>
	<PARAM NAME="_ExtentX" VALUE="3863">
	<PARAM NAME="_ExtentY" VALUE="503">
	<PARAM NAME="id" VALUE="Textbox3">
	<PARAM NAME="ControlType" VALUE="0">
	<PARAM NAME="Lines" VALUE="3">
	<PARAM NAME="DataSource" VALUE="DTCRecordset1">
	<PARAM NAME="DataField" VALUE="Address">
	<PARAM NAME="Enabled" VALUE="-1">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="MaxChars" VALUE="20">
	<PARAM NAME="DisplayWidth" VALUE="24">
	<PARAM NAME="Platform" VALUE="0">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<SCRIPT LANGUAGE=JavaScript RUNAT=Server>
function _initTextbox3()
{
	Textbox3.setStyle(TXT_TEXTBOX);
	Textbox3.setDataSource(DTCRecordset1);
	Textbox3.setDataField('Address');
	Textbox3.setMaxLength(20);
	Textbox3.setColumnCount(24);
}
function _Textbox3_ctor()
{
	CreateTextbox('Textbox3', _initTextbox3, null);
}
</script>
<% Textbox3.display %>

<!--METADATA TYPE="DesignerControl" endspan-->
</TD></TR>
<TR><TD ALIGN=Right>Ville :</TD>
<TD>
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B5F0E469-DC5F-11D0-9846-0000F8027CA0" height=25 id=Textbox4 
	style="HEIGHT: 25px; LEFT: 0px; TOP: 0px; WIDTH: 146px" width=146>
	<PARAM NAME="_ExtentX" VALUE="3863">
	<PARAM NAME="_ExtentY" VALUE="503">
	<PARAM NAME="id" VALUE="Textbox4">
	<PARAM NAME="ControlType" VALUE="0">
	<PARAM NAME="Lines" VALUE="3">
	<PARAM NAME="DataSource" VALUE="DTCRecordset1">
	<PARAM NAME="DataField" VALUE="City">
	<PARAM NAME="Enabled" VALUE="-1">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="MaxChars" VALUE="20">
	<PARAM NAME="DisplayWidth" VALUE="24">
	<PARAM NAME="Platform" VALUE="0">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<SCRIPT LANGUAGE=JavaScript RUNAT=Server>
function _initTextbox4()
{
	Textbox4.setStyle(TXT_TEXTBOX);
	Textbox4.setDataSource(DTCRecordset1);
	Textbox4.setDataField('City');
	Textbox4.setMaxLength(20);
	Textbox4.setColumnCount(24);
}
function _Textbox4_ctor()
{
	CreateTextbox('Textbox4', _initTextbox4, null);
}
</script>
<% Textbox4.display %>

<!--METADATA TYPE="DesignerControl" endspan-->
</TD></TR>
<TR><TD ALIGN=Right>Pays :</TD>
<TD>
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B5F0E469-DC5F-11D0-9846-0000F8027CA0" height=25 id=Textbox5 
	style="HEIGHT: 25px; LEFT: 0px; TOP: 0px; WIDTH: 146px" width=146>
	<PARAM NAME="_ExtentX" VALUE="3863">
	<PARAM NAME="_ExtentY" VALUE="503">
	<PARAM NAME="id" VALUE="Textbox5">
	<PARAM NAME="ControlType" VALUE="0">
	<PARAM NAME="Lines" VALUE="3">
	<PARAM NAME="DataSource" VALUE="DTCRecordset1">
	<PARAM NAME="DataField" VALUE="State">
	<PARAM NAME="Enabled" VALUE="-1">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="MaxChars" VALUE="20">
	<PARAM NAME="DisplayWidth" VALUE="24">
	<PARAM NAME="Platform" VALUE="0">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<SCRIPT LANGUAGE=JavaScript RUNAT=Server>
function _initTextbox5()
{
	Textbox5.setStyle(TXT_TEXTBOX);
	Textbox5.setDataSource(DTCRecordset1);
	Textbox5.setDataField('State');
	Textbox5.setMaxLength(20);
	Textbox5.setColumnCount(24);
}
function _Textbox5_ctor()
{
	CreateTextbox('Textbox5', _initTextbox5, null);
}
</script>
<% Textbox5.display %>

<!--METADATA TYPE="DesignerControl" endspan-->
</TD></TR>
<TR><TD ALIGN=Right>Code Postal :</TD>
<TD>
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B5F0E469-DC5F-11D0-9846-0000F8027CA0" height=25 id=Textbox6 
	style="HEIGHT: 25px; LEFT: 0px; TOP: 0px; WIDTH: 146px" width=146>
	<PARAM NAME="_ExtentX" VALUE="3863">
	<PARAM NAME="_ExtentY" VALUE="503">
	<PARAM NAME="id" VALUE="Textbox6">
	<PARAM NAME="ControlType" VALUE="0">
	<PARAM NAME="Lines" VALUE="3">
	<PARAM NAME="DataSource" VALUE="DTCRecordset1">
	<PARAM NAME="DataField" VALUE="Zip">
	<PARAM NAME="Enabled" VALUE="-1">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="MaxChars" VALUE="20">
	<PARAM NAME="DisplayWidth" VALUE="24">
	<PARAM NAME="Platform" VALUE="0">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<SCRIPT LANGUAGE=JavaScript RUNAT=Server>
function _initTextbox6()
{
	Textbox6.setStyle(TXT_TEXTBOX);
	Textbox6.setDataSource(DTCRecordset1);
	Textbox6.setDataField('Zip');
	Textbox6.setMaxLength(20);
	Textbox6.setColumnCount(24);
}
function _Textbox6_ctor()
{
	CreateTextbox('Textbox6', _initTextbox6, null);
}
</script>
<% Textbox6.display %>

<!--METADATA TYPE="DesignerControl" endspan-->
</TD></TR>
<TR><TD ALIGN=Right>Sexe :</TD>
<TD>
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B5F0E45D-DC5F-11D0-9846-0000F8027CA0" height=31 id=OptionGroup1 
	style="HEIGHT: 31px; LEFT: 10px; TOP: 389px; WIDTH: 152px" width=152>
	<PARAM NAME="_ExtentX" VALUE="4022">
	<PARAM NAME="_ExtentY" VALUE="820">
	<PARAM NAME="id" VALUE="OptionGroup1">
	<PARAM NAME="DataSource" VALUE="DTCRecordset1">
	<PARAM NAME="DataField" VALUE="Sex">
	<PARAM NAME="ControlStyle" VALUE="1">
	<PARAM NAME="BType" VALUE="0">
	<PARAM NAME="Enabled" VALUE="-1">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="Platform" VALUE="0">
	<PARAM NAME="UsesStaticList" VALUE="-1">
	<PARAM NAME="CLSize" VALUE="2">
	<PARAM NAME="CLED1" VALUE="Homme">
	<PARAM NAME="CLEV1" VALUE="1">
	<PARAM NAME="CLED2" VALUE="Femme">
	<PARAM NAME="CLEV2" VALUE="0">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<!--#INCLUDE FILE="../_ScriptLibrary/OptionGrp.ASP"-->
<script runat="server" language="JavaScript">
function _initOptionGroup1()
{
   OptionGroup1.addItem('Homme', '1');
   OptionGroup1.addItem('Femme', '0');
   OptionGroup1.setDataSource(DTCRecordset1);
   OptionGroup1.setDataField('Sex');
   OptionGroup1.setAlignment(1);
}
function _OptionGroup1_ctor()
{
   CreateOptionGroup('OptionGroup1', _initOptionGroup1, null);
}
</script>
<% OptionGroup1.display %>

<!--METADATA TYPE="DesignerControl" endspan-->
</TD></TR>
<TR><TD ALIGN=Right>Revenu :</TD>
<TD>
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B5F0E450-DC5F-11D0-9846-0000F8027CA0" height=24 id=Listbox1 
	style="HEIGHT: 24px; LEFT: 0px; TOP: 0px; WIDTH: 157px" width=157>
	<PARAM NAME="_ExtentX" VALUE="3466">
	<PARAM NAME="_ExtentY" VALUE="556">
	<PARAM NAME="id" VALUE="Listbox1">
	<PARAM NAME="DataSource" VALUE="DTCRecordset1">
	<PARAM NAME="DataField" VALUE="Income">
	<PARAM NAME="ControlStyle" VALUE="0">
	<PARAM NAME="Enabled" VALUE="-1">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="Platform" VALUE="0">
	<PARAM NAME="UsesStaticList" VALUE="-1">
	<PARAM NAME="CLSize" VALUE="6">
	<PARAM NAME="CLED1" VALUE="F 15 000 - F 20 000">
	<PARAM NAME="CLEV1" VALUE="15_20">
	<PARAM NAME="CLED2" VALUE="F 20 000 - F 30 000">
	<PARAM NAME="CLEV2" VALUE="20_30">
	<PARAM NAME="CLED3" VALUE="F 30 000 - F 40 000">
	<PARAM NAME="CLEV3" VALUE="30_40">
	<PARAM NAME="CLED4" VALUE="F 40 000 - F 60 000">
	<PARAM NAME="CLEV4" VALUE="40_60">
	<PARAM NAME="CLED5" VALUE="Plus de F 60 000">
	<PARAM NAME="CLEV5" VALUE="60_up">
	<PARAM NAME="CLED6" VALUE="">
	<PARAM NAME="CLEV6" VALUE="">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<!--#INCLUDE FILE="../_ScriptLibrary/ListBox.ASP"-->
<SCRIPT LANGUAGE=JavaScript RUNAT=Server>
function _initListbox1()
{
	Listbox1.addItem('F 15 000 - F 20 000', '15_20');
	Listbox1.addItem('F 20 000 - F 30 000', '20_30');
	Listbox1.addItem('F 30 000 - F 40 000', '30_40');
	Listbox1.addItem('F 40 000 - F 60 000', '40_60');
	Listbox1.addItem('plus de F 60 000', '60_up');
	Listbox1.addItem('', '');
	Listbox1.setDataSource(DTCRecordset1);
	Listbox1.setDataField('Income');
}
function _Listbox1_ctor()
{
	CreateListbox('Listbox1', _initListbox1, null);
}
</script>
<% Listbox1.display %>

<!--METADATA TYPE="DesignerControl" endspan-->
</TD></TR>
<TR><TD></TD><TD>
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B5F0E46C-DC5F-11D0-9846-0000F8027CA0" height=23 id=Checkbox1 
	style="HEIGHT: 23px; LEFT: 0px; TOP: 0px; WIDTH: 224px" width=224>
	<PARAM NAME="_ExtentX" VALUE="5265">
	<PARAM NAME="_ExtentY" VALUE="714">
	<PARAM NAME="id" VALUE="Checkbox1">
	<PARAM NAME="Caption" VALUE="Oui, je possède un ordinateur personnel.">
	<PARAM NAME="DataSource" VALUE="DTCRecordset1">
	<PARAM NAME="DataField" VALUE="PC">
	<PARAM NAME="Enabled" VALUE="-1">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="Platform" VALUE="0">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<!--#INCLUDE FILE="../_ScriptLibrary/CheckBox.ASP"-->
<script runat="server" language="JavaScript">
function _initCheckbox1()
{
   Checkbox1.setDataSource(DTCRecordset1);
   Checkbox1.setDataField('PC');
   Checkbox1.setCaption('Oui, je possède un ordinateur personnel.');
}
function _Checkbox1_ctor()
{
   CreateCheckbox('Checkbox1', _initCheckbox1, null);
}
</script>
<% Checkbox1.display %>

<!--METADATA TYPE="DesignerControl" endspan-->
</TD></TR>
</TABLE>

<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:58F3D268-FEDF-11D0-9C7F-0060081840F3" height=32 id=RecordsetNavbar1 
	style="HEIGHT: 32px; LEFT: 0px; TOP: 0px; WIDTH: 142px" width=142>
	<PARAM NAME="_ExtentX" VALUE="4075">
	<PARAM NAME="_ExtentY" VALUE="714">
	<PARAM NAME="id" VALUE="RecordsetNavbar1">
	<PARAM NAME="Platform" VALUE="0">
	<PARAM NAME="DataSource" VALUE="DTCRecordset1">
	<PARAM NAME="UpdateOnMove" VALUE="0">
	<PARAM NAME="FirstCaption" VALUE=" |< ">
	<PARAM NAME="MoveFirst" VALUE="-1">
	<PARAM NAME="FirstImage" VALUE="0">
	<PARAM NAME="PrevCaption" VALUE="  <  ">
	<PARAM NAME="MovePrev" VALUE="-1">
	<PARAM NAME="PrevImage" VALUE="0">
	<PARAM NAME="NextCaption" VALUE="  >  ">
	<PARAM NAME="MoveNext" VALUE="-1">
	<PARAM NAME="NextImage" VALUE="0">
	<PARAM NAME="LastCaption" VALUE=" >| ">
	<PARAM NAME="MoveLast" VALUE="-1">
	<PARAM NAME="LastImage" VALUE="0">
	<PARAM NAME="Alignment" VALUE="1">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<!--#INCLUDE FILE="../_ScriptLibrary/RSNavBar.ASP"-->
<SCRIPT LANGUAGE=JavaScript RUNAT=Server>
function _initRecordsetNavbar1()
{
	RecordsetNavbar1.setAlignment(1);
	RecordsetNavbar1.setButtonStyles(170);
	RecordsetNavbar1.updateOnMove = false;
	RecordsetNavbar1.setDataSource(DTCRecordset1);
	RecordsetNavbar1.getButton(0).value = ' |< ';
	RecordsetNavbar1.getButton(1).value = '  <  ';
	RecordsetNavbar1.getButton(2).value = '  >  ';
	RecordsetNavbar1.getButton(3).value = ' >| ';
}
function _RecordsetNavbar1_ctor()
{
	CreateRecordsetNavbar('RecordsetNavbar1', _initRecordsetNavbar1, null);
}
</script>
<% RecordsetNavbar1.display %>

<!--METADATA TYPE="DesignerControl" endspan-->
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:CEB04D01-0445-11D1-BB81-006097C553C8" id=FormManager1 style="LEFT: 0px; TOP: 0px">
	<PARAM NAME="ExtentX" VALUE="4233">
	<PARAM NAME="ExtentY" VALUE="609">
	<PARAM NAME="State" VALUE="(txtName_Unmatched=\qFormManager1\q,txtNewMode_Unmatched=\q\q,grFormMode=(Rows=3,Row1=(txtMode_Unmatched=\qEdit\q),Row2=(txtMode_Unmatched=\qBrowse\q),Row3=(txtMode_Unmatched=\qInsert\q)),txtDefaultMode=\qBrowse\q,grMasterMode=(Rows=44,Row1=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qBrowseBtn\q,txtProperty_Unmatched=\qdisabled\q,txtValue_Unmatched=\qfalse\q),Row2=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qEditBtn\q,txtProperty_Unmatched=\qdisabled\q,txtValue_Unmatched=\qtrue\q),Row3=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qDeleteBtn\q,txtProperty_Unmatched=\qshow\q,txtValue_Unmatched=\q()\q),Row4=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qDeleteBtn\q,txtProperty_Unmatched=\qdisabled\q,txtValue_Unmatched=\qfalse\q),Row5=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qInsertBtn\q,txtProperty_Unmatched=\qshow\q,txtValue_Unmatched=\q()\q),Row6=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qInsertBtn\q,txtProperty_Unmatched=\qdisabled\q,txtValue_Unmatched=\qfalse\q),Row7=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qUpdateBtn\q,txtProperty_Unmatched=\qshow\q,txtValue_Unmatched=\q()\q),Row8=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qCancelBtn\q,txtProperty_Unmatched=\qshow\q,txtValue_Unmatched=\q()\q),Row9=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qTextbox1\q,txtProperty_Unmatched=\qdisabled\q,txtValue_Unmatched=\qfalse\q),Row10=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qTextbox2\q,txtProperty_Unmatched=\qdisabled\q,txtValue_Unmatched=\qfalse\q),Row11=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qTextbox3\q,txtProperty_Unmatched=\qdisabled\q,txtValue_Unmatched=\qfalse\q),Row12=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qTextbox4\q,txtProperty_Unmatched=\qdisabled\q,txtValue_Unmatched=\qfalse\q),Row13=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qTextbox5\q,txtProperty_Unmatched=\qdisabled\q,txtValue_Unmatched=\qfalse\q),Row14=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qTextbox6\q,txtProperty_Unmatched=\qdisabled\q,txtValue_Unmatched=\qfalse\q),Row15=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qCheckbox1\q,txtProperty_Unmatched=\qdisabled\q,txtValue_Unmatched=\qfalse\q),Row16=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qListbox1\q,txtProperty_Unmatched=\qdisabled\q,txtValue_Unmatched=\qfalse\q),Row17=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qRecordsetNavbar1\q,txtProperty_Unmatched=\qhide\q,txtValue_Unmatched=\q()\q),Row18=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qOptionGroup1.getButton(0)\q,txtProperty_Unmatched=\qdisabled\q,txtValue_Unmatched=\qfalse\q),Row19=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qOptionGroup1.getButton(1)\q,txtProperty_Unmatched=\qdisabled\q,txtValue_Unmatched=\qfalse\q),Row20=(txtName_Unmatched=\q2\q,txtControl_Unmatched=\qBrowseBtn\q,txtProperty_Unmatched=\qdisabled\q,txtValue_Unmatched=\qtrue\q),Row21=(txtName_Unmatched=\q2\q,txtControl_Unmatched=\qEditBtn\q,txtProperty_Unmatched=\qdisabled\q,txtValue_Unmatched=\qfalse\q),Row22=(txtName_Unmatched=\q2\q,txtControl_Unmatched=\qInsertBtn\q,txtProperty_Unmatched=\qhide\q,txtValue_Unmatched=\q()\q),Row23=(txtName_Unmatched=\q2\q,txtControl_Unmatched=\qDeleteBtn\q,txtProperty_Unmatched=\qhide\q,txtValue_Unmatched=\q()\q),Row24=(txtName_Unmatched=\q2\q,txtControl_Unmatched=\qUpdateBtn\q,txtProperty_Unmatched=\qhide\q,txtValue_Unmatched=\q()\q),Row25=(txtName_Unmatched=\q2\q,txtControl_Unmatched=\qCancelBtn\q,txtProperty_Unmatched=\qhide\q,txtValue_Unmatched=\q()\q),Row26=(txtName_Unmatched=\q2\q,txtControl_Unmatched=\qTextbox1\q,txtProperty_Unmatched=\qdisabled\q,txtValue_Unmatched=\qtrue\q),Row27=(txtName_Unmatched=\q2\q,txtControl_Unmatched=\qTextbox2\q,txtProperty_Unmatched=\qdisabled\q,txtValue_Unmatched=\qtrue\q),Row28=(txtName_Unmatched=\q2\q,txtControl_Unmatched=\qTextbox3\q,txtProperty_Unmatched=\qdisabled\q,txtValue_Unmatched=\qtrue\q),Row29=(txtName_Unmatched=\q2\q,txtControl_Unmatched=\qTextbox4\q,txtProperty_Unmatched=\qdisabled\q,txtValue_Unmatched=\qtrue\q),Row30=(txtName_Unmatched=\q2\q,txtControl_Unmatched=\qTextbox5\q,txtProperty_Unmatched=\qdisabled\q,txtValue_Unmatched=\qtrue\q),Row31=(txtName_Unmatched=\q2\q,txtControl_Unmatched=\qTextbox6\q,txtProperty_Unmatched=\qdisabled\q,txtValue_Unmatched=\qtrue\q),Row32=(txtName_Unmatched=\q2\q,txtControl_Unmatched=\qCheckbox1\q,txtProperty_Unmatched=\qdisabled\q,txtValue_Unmatched=\qtrue\q),Row33=(txtName_Unmatched=\q2\q,txtControl_Unmatched=\qListbox1\q,txtProperty_Unmatched=\qdisabled\q,txtValue_Unmatched=\qtrue\q),Row34=(txtName_Unmatched=\q2\q,txtControl_Unmatched=\qRecordsetNavbar1\q,txtProperty_Unmatched=\qshow\q,txtValue_Unmatched=\q()\q),Row35=(txtName_Unmatched=\q2\q,txtControl_Unmatched=\q\q,txtProperty_Unmatched=\qdisable_opt\q,txtValue_Unmatched=\q(OptionGroup1)\q),Row36=(txtName_Unmatched=\q3\q,txtControl_Unmatched=\qDeleteBtn\q,txtProperty_Unmatched=\qdisabled\q,txtValue_Unmatched=\qtrue\q),Row37=(txtName_Unmatched=\q3\q,txtControl_Unmatched=\qBrowseBtn\q,txtProperty_Unmatched=\qdisabled\q,txtValue_Unmatched=\qtrue\q),Row38=(txtName_Unmatched=\q3\q,txtControl_Unmatched=\qInsertBtn\q,txtProperty_Unmatched=\qdisabled\q,txtValue_Unmatched=\qtrue\q),Row39=(txtName_Unmatched=\q3\q,txtControl_Unmatched=\qTextbox1\q,txtProperty_Unmatched=\qvalue\q,txtValue_Unmatched=\q\q\q\q\q\q),Row40=(txtName_Unmatched=\q3\q,txtControl_Unmatched=\qTextbox2\q,txtProperty_Unmatched=\qvalue\q,txtValue_Unmatched=\q\q\q\q\q\q),Row41=(txtName_Unmatched=\q3\q,txtControl_Unmatched=\qTextbox3\q,txtProperty_Unmatched=\qvalue\q,txtValue_Unmatched=\q\q\q\q\q\q),Row42=(txtName_Unmatched=\q3\q,txtControl_Unmatched=\qTextbox4\q,txtProperty_Unmatched=\qvalue\q,txtValue_Unmatched=\q\q\q\q\q\q),Row43=(txtName_Unmatched=\q3\q,txtControl_Unmatched=\qTextbox5\q,txtProperty_Unmatched=\qvalue\q,txtValue_Unmatched=\q\q\q\q\q\q),Row44=(txtName_Unmatched=\q3\q,txtControl_Unmatched=\qTextbox6\q,txtProperty_Unmatched=\qvalue\q,txtValue_Unmatched=\q\q\q\q\q\q)),grTransitions=(Rows=7,Row1=(txtCurrentMode=\qEdit\q,txtObject=\qUpdateBtn\q,txtEvent=\qonclick\q,txtNextMode=\qEdit\q),Row2=(txtCurrentMode=\qEdit\q,txtObject=\qDeleteBtn\q,txtEvent=\qonclick\q,txtNextMode=\qEdit\q),Row3=(txtCurrentMode=\qEdit\q,txtObject=\qInsertBtn\q,txtEvent=\qonclick\q,txtNextMode=\qInsert\q),Row4=(txtCurrentMode=\qBrowse\q,txtObject=\qEditBtn\q,txtEvent=\qonclick\q,txtNextMode=\qEdit\q),Row5=(txtCurrentMode=\qEdit\q,txtObject=\qBrowseBtn\q,txtEvent=\qonclick\q,txtNextMode=\qBrowse\q),Row6=(txtCurrentMode=\qInsert\q,txtObject=\qCancelBtn\q,txtEvent=\qonclick\q,txtNextMode=\qBrowse\q),Row7=(txtCurrentMode=\qInsert\q,txtObject=\qUpdateBtn\q,txtEvent=\qonclick\q,txtNextMode=\qEdit\q)),grMasterStep=(Rows=9,Row1=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qDTCRecordset1\q,txtAction_Unmatched=\qupdateRecord\q,txtValue_Unmatched=\q()\q),Row2=(txtName_Unmatched=\q2\q,txtControl_Unmatched=\qDTCRecordset1\q,txtAction_Unmatched=\qdeleteRecord\q,txtValue_Unmatched=\q()\q),Row3=(txtName_Unmatched=\q2\q,txtControl_Unmatched=\qDTCRecordset1\q,txtAction_Unmatched=\qmoveFirst\q,txtValue_Unmatched=\q()\q),Row4=(txtName_Unmatched=\q3\q,txtControl_Unmatched=\qDTCRecordset1\q,txtAction_Unmatched=\qaddRecord\q,txtValue_Unmatched=\q()\q),Row5=(txtName_Unmatched=\q3\q,txtControl_Unmatched=\qDTCRecordset1\q,txtAction_Unmatched=\qmoveLast\q,txtValue_Unmatched=\q()\q),Row6=(txtName_Unmatched=\q4\q),Row7=(txtName_Unmatched=\q5\q),Row8=(txtName_Unmatched=\q6\q,txtControl_Unmatched=\qDTCRecordset1\q,txtAction_Unmatched=\qcancelUpdate\q,txtValue_Unmatched=\q()\q),Row9=(txtName_Unmatched=\q7\q,txtControl_Unmatched=\qDTCRecordset1\q,txtAction_Unmatched=\qupdateRecord\q,txtValue_Unmatched=\q()\q)))"></OBJECT>
-->
<SCRIPT RUNAT=SERVER LANGUAGE="JavaScript">
function _FormManager1_ctor()
{
	thisPage.advise(PAGE_ONINIT, _FormManager1_init);
}
function _FormManager1_init()
{
	if (thisPage.getState("FormManager1_formmode") == null)
		_FormManager1_SetMode("Browse");
	UpdateBtn.advise("onclick", "_FormManager1_UpdateBtn_onclick()");
	DeleteBtn.advise("onclick", "_FormManager1_DeleteBtn_onclick()");
	InsertBtn.advise("onclick", "_FormManager1_InsertBtn_onclick()");
	EditBtn.advise("onclick", "_FormManager1_EditBtn_onclick()");
	BrowseBtn.advise("onclick", "_FormManager1_BrowseBtn_onclick()");
	CancelBtn.advise("onclick", "_FormManager1_CancelBtn_onclick()");
}
function _FormManager1_SetMode(formmode)
{
	thisPage.setState("FormManager1_formmode", formmode);
	if (formmode == "Edit")
	{
		BrowseBtn.disabled = false;
		EditBtn.disabled = true;
		DeleteBtn.show();
		DeleteBtn.disabled = false;
		InsertBtn.show();
		InsertBtn.disabled = false;
		UpdateBtn.show();
		CancelBtn.show();
		Textbox1.disabled = false;
		Textbox2.disabled = false;
		Textbox3.disabled = false;
		Textbox4.disabled = false;
		Textbox5.disabled = false;
		Textbox6.disabled = false;
		Checkbox1.disabled = false;
		Listbox1.disabled = false;
		RecordsetNavbar1.hide();
		OptionGroup1.getButton(0).disabled = false;
		OptionGroup1.getButton(1).disabled = false;
	}
	if (formmode == "Browse")
	{
		BrowseBtn.disabled = true;
		EditBtn.disabled = false;
		InsertBtn.hide();
		DeleteBtn.hide();
		UpdateBtn.hide();
		CancelBtn.hide();
		Textbox1.disabled = true;
		Textbox2.disabled = true;
		Textbox3.disabled = true;
		Textbox4.disabled = true;
		Textbox5.disabled = true;
		Textbox6.disabled = true;
		Checkbox1.disabled = true;
		Listbox1.disabled = true;
		RecordsetNavbar1.show();
		disable_opt(OptionGroup1);
	}
	if (formmode == "Insert")
	{
		DeleteBtn.disabled = true;
		BrowseBtn.disabled = true;
		InsertBtn.disabled = true;
		Textbox1.value = "";
		Textbox2.value = "";
		Textbox3.value = "";
		Textbox4.value = "";
		Textbox5.value = "";
		Textbox6.value = "";
	}
}
function _FormManager1_UpdateBtn_onclick()
{
	if (thisPage.getState("FormManager1_formmode") == "Edit")
	{
		DTCRecordset1.updateRecord();
		_FormManager1_SetMode("Edit");
	}
	else if (thisPage.getState("FormManager1_formmode") == "Insert")
	{
		DTCRecordset1.updateRecord();
		_FormManager1_SetMode("Edit");
	}
	else _FormManager1_SetMode(thisPage.getState("FormManager1_formmode"))
}
function _FormManager1_DeleteBtn_onclick()
{
	if (thisPage.getState("FormManager1_formmode") == "Edit")
	{
		DTCRecordset1.deleteRecord();
		DTCRecordset1.moveFirst();
		_FormManager1_SetMode("Edit");
	}
	else _FormManager1_SetMode(thisPage.getState("FormManager1_formmode"))
}
function _FormManager1_InsertBtn_onclick()
{
	if (thisPage.getState("FormManager1_formmode") == "Edit")
	{
		DTCRecordset1.addRecord();
		DTCRecordset1.moveLast();
		_FormManager1_SetMode("Insert");
	}
	else _FormManager1_SetMode(thisPage.getState("FormManager1_formmode"))
}
function _FormManager1_EditBtn_onclick()
{
	if (thisPage.getState("FormManager1_formmode") == "Browse")
	{
		_FormManager1_SetMode("Edit");
	}
	else _FormManager1_SetMode(thisPage.getState("FormManager1_formmode"))
}
function _FormManager1_BrowseBtn_onclick()
{
	if (thisPage.getState("FormManager1_formmode") == "Edit")
	{
		_FormManager1_SetMode("Browse");
	}
	else _FormManager1_SetMode(thisPage.getState("FormManager1_formmode"))
}
function _FormManager1_CancelBtn_onclick()
{
	if (thisPage.getState("FormManager1_formmode") == "Insert")
	{
		DTCRecordset1.cancelUpdate();
		_FormManager1_SetMode("Browse");
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
