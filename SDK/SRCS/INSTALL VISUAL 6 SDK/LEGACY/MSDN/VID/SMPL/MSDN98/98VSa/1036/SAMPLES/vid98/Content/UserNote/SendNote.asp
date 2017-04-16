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
	<PARAM NAME="State" VALUE="(TCConn=\qGallery\q,TCDBObject=\qTables\q,TCDBObjectName=\qUserNote\q,TCControlID_Unmatched=\qDTCRecordset1\q,TCPPConn=\qGallery\q,RCDBObject=\qRCDBObject\q,TCPPDBObject=\qTables\q,TCPPDBObjectName=\qUserNote\q,TCCursorType=\q3\s-\sStatic\q,TCCursorLocation=\q3\s-\sUse\sclient-side\scursors\q,TCLockType=\q3\s-\sOptimistic\q,TCCacheSize_Unmatched=\q10\q,TCCommTimeout_Unmatched=\q10\q,CCPrepared=0,CCAllRecords=1,TCNRecords_Unmatched=\q10\q,TCODBCSyntax_Unmatched=\q\q,TCHTargetPlatform=\q\q,TCHTargetBrowser_Unmatched=\qServer\s(ASP)\q,TCTargetPlatform=\qInherit\sfrom\spage\q,RCCache=\qRCBookPage\q,CCOpen=1,GCParameters=(Rows=0))">
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
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B5F0E469-DC5F-11D0-9846-0000F8027CA0" height=19 id=txtFROM style="HEIGHT: 19px; LEFT: 0px; TOP: 0px; WIDTH: 120px" 
	width=120>
	<PARAM NAME="_ExtentX" VALUE="3175">
	<PARAM NAME="_ExtentY" VALUE="503">
	<PARAM NAME="id" VALUE="txtFROM">
	<PARAM NAME="ControlType" VALUE="0">
	<PARAM NAME="Lines" VALUE="3">
	<PARAM NAME="DataSource" VALUE="DTCRecordset1">
	<PARAM NAME="DataField" VALUE="From">
	<PARAM NAME="Enabled" VALUE="-1">
	<PARAM NAME="Visible" VALUE="0">
	<PARAM NAME="MaxChars" VALUE="20">
	<PARAM NAME="DisplayWidth" VALUE="20">
	<PARAM NAME="Platform" VALUE="0">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<!--#INCLUDE FILE="../_ScriptLibrary/TextBox.ASP"-->
<script runat="server" language="JavaScript">
function _inittxtFROM()
{
   txtFROM.setStyle(TXT_TEXTBOX);
   txtFROM.setDataSource(DTCRecordset1);
   txtFROM.setDataField('From');
   txtFROM.hide();
   txtFROM.setMaxLength(20);
   txtFROM.setColumnCount(20);
}
function _txtFROM_ctor()
{
   CreateTextbox('txtFROM', _inittxtFROM, null);
}
</script>
<% txtFROM.display %>

<!--METADATA TYPE="DesignerControl" endspan-->
&#192; : 
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B5F0E469-DC5F-11D0-9846-0000F8027CA0" height=19 id=txtTO style="HEIGHT: 19px; LEFT: 0px; TOP: 0px; WIDTH: 120px" 
	width=120>
	<PARAM NAME="_ExtentX" VALUE="3175">
	<PARAM NAME="_ExtentY" VALUE="503">
	<PARAM NAME="id" VALUE="txtTO">
	<PARAM NAME="ControlType" VALUE="0">
	<PARAM NAME="Lines" VALUE="3">
	<PARAM NAME="DataSource" VALUE="DTCRecordset1">
	<PARAM NAME="DataField" VALUE="To">
	<PARAM NAME="Enabled" VALUE="-1">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="MaxChars" VALUE="20">
	<PARAM NAME="DisplayWidth" VALUE="20">
	<PARAM NAME="Platform" VALUE="0">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<script runat="server" language="JavaScript">
function _inittxtTO()
{
   txtTO.setStyle(TXT_TEXTBOX);
   txtTO.setDataSource(DTCRecordset1);
   txtTO.setDataField('To');
   txtTO.setMaxLength(20);
   txtTO.setColumnCount(20);
}
function _txtTO_ctor()
{
   CreateTextbox('txtTO', _inittxtTO, null);
}
</script>
<% txtTO.display %>

<!--METADATA TYPE="DesignerControl" endspan-->
<BR>
MESSAGE :<BR>
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B5F0E469-DC5F-11D0-9846-0000F8027CA0" height=65 id=txtMessage 
	style="HEIGHT: 65px; LEFT: 0px; TOP: 0px; WIDTH: 180px" width=180>
	<PARAM NAME="_ExtentX" VALUE="4763">
	<PARAM NAME="_ExtentY" VALUE="1720">
	<PARAM NAME="id" VALUE="txtMessage">
	<PARAM NAME="ControlType" VALUE="1">
	<PARAM NAME="Lines" VALUE="5">
	<PARAM NAME="DataSource" VALUE="DTCRecordset1">
	<PARAM NAME="DataField" VALUE="Message">
	<PARAM NAME="Enabled" VALUE="-1">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="MaxChars" VALUE="255">
	<PARAM NAME="DisplayWidth" VALUE="30">
	<PARAM NAME="Platform" VALUE="0">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<script runat="server" language="JavaScript">
function _inittxtMessage()
{
   txtMessage.setStyle(TXT_TEXTAREA);
   txtMessage.setDataSource(DTCRecordset1);
   txtMessage.setDataField('Message');
   txtMessage.setRowCount(5);
   txtMessage.setColumnCount(30);
}
function _txtMessage_ctor()
{
   CreateTextbox('txtMessage', _inittxtMessage, null);
}
</script>
<% txtMessage.display %>

<!--METADATA TYPE="DesignerControl" endspan-->
<BR>
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B6FC3A14-F837-11D0-9CC8-006008058731" height=27 id=Button1 style="HEIGHT: 27px; LEFT: 0px; TOP: 0px; WIDTH: 103px" 
	width=103>
	<PARAM NAME="_ExtentX" VALUE="3175">
	<PARAM NAME="_ExtentY" VALUE="714">
	<PARAM NAME="id" VALUE="Button1">
	<PARAM NAME="Caption" VALUE="Save Message">
	<PARAM NAME="Image" VALUE="">
	<PARAM NAME="AltText" VALUE="">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="Platform" VALUE="256">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<!--#INCLUDE FILE="../_ScriptLibrary/Button.ASP"-->
<script runat="server" language="JavaScript">
function _initButton1()
{
    Button1.value = 'Enregistrer le message';
    Button1.setStyle(0);
}
function _Button1_ctor()
{
   CreateButton('Button1', _initButton1, null);
}
</script>
<% Button1.display %>

<!--METADATA TYPE="DesignerControl" endspan-->
<BR>
REMARQUE : Lors de la saisie de l'adresse n'oubliez pas d'entrer
le nom du domaine ainsi que celui de l'utilisateur (ex : NomDomaine\NomUtilisateur)<BR>
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:CEB04D01-0445-11D1-BB81-006097C553C8" id=FormManager1 style="LEFT: 0px; TOP: 0px">
	<PARAM NAME="ExtentX" VALUE="4233">
	<PARAM NAME="ExtentY" VALUE="609">
	<PARAM NAME="State" VALUE="(txtName_Unmatched=\qFormManager1\q,txtNewMode_Unmatched=\q\q,grFormMode=(Rows=1,Row1=(txtMode_Unmatched=\qSend\q)),txtDefaultMode=\qSend\q,grMasterMode=(Rows=1,Row1=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qDTCRecordset1\q,txtProperty_Unmatched=\qaddRecord\q,txtValue_Unmatched=\q()\q)),grTransitions=(Rows=1,Row1=(txtCurrentMode=\qSend\q,txtObject=\qButton1\q,txtEvent=\qonclick\q,txtNextMode=\qSend\q)),grMasterStep=(Rows=2,Row1=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qtxtFROM\q,txtAction_Unmatched=\qvalue\q,txtValue_Unmatched=\qRequest.ServerVariables(\q\qAUTH_USER\q\q)\q),Row2=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qDTCRecordset1\q,txtAction_Unmatched=\qupdateRecord\q,txtValue_Unmatched=\q()\q)))"></OBJECT>
-->
<SCRIPT RUNAT=SERVER LANGUAGE="JavaScript">
function _FormManager1_ctor()
{
	thisPage.advise(PAGE_ONINIT, _FormManager1_init);
}
function _FormManager1_init()
{
	if (thisPage.getState("FormManager1_formmode") == null)
		_FormManager1_SetMode("Send");
	Button1.advise("onclick", "_FormManager1_Button1_onclick()");
}
function _FormManager1_SetMode(formmode)
{
	thisPage.setState("FormManager1_formmode", formmode);
	if (formmode == "Send")
	{
		DTCRecordset1.addRecord();
	}
}
function _FormManager1_Button1_onclick()
{
	if (thisPage.getState("FormManager1_formmode") == "Send")
	{
		txtFROM.value = Request.ServerVariables("AUTH_USER");
		DTCRecordset1.updateRecord();
		_FormManager1_SetMode("Send");
	}
	else _FormManager1_SetMode(thisPage.getState("FormManager1_formmode"))
}
</SCRIPT>


<!--METADATA TYPE="DesignerControl" endspan-->
<A HREF=UserNote.asp>Afficher les messages</A>
</FONT>
</BODY>
<% ' VI 6.0 Scripting Object Model Enabled %>
<% EndPageProcessing() %>
</FORM>
</HTML>
