<%@ LANGUAGE=VBScript %>
<% ' VI 6.0 Scripting Object Model Enabled %>
<!--#include file="../_ScriptLibrary/pm.asp"-->
<% if StartPageProcessing() Then Response.End() %>
<FORM name=thisForm METHOD=post>
<HTML>
<script LANGUAGE="JAVASCRIPT" RUNAT=Server>
	function DTCRecordset1_onafterupdate() {
		if (DTCRecordset1.isOpen()) {
			DTCRecordset1.close();
		}
		newSQL="SELECT * FROM Survey WHERE (Manager = '" + cboManager.getValue(cboManager.selectedIndex) + "') AND (Period = " + cboPeriod.getValue(cboPeriod.selectedIndex) + ")";
		DTCRecordset1.setSQLText(newSQL);
		DTCRecordset1.open();
	}
</script>

<BODY bgColor=#ffffff leftMargin=40 link=#500000 vLink=#505050>

<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:9CF5D7C2-EC10-11D0-9862-0000F8027CA0" id=DTCRecordset1 style="LEFT: 0px; TOP: 0px">
	<PARAM NAME="ExtentX" VALUE="12197">
	<PARAM NAME="ExtentY" VALUE="2090">
	<PARAM NAME="State" VALUE="(TCConn=\qGallery\q,TCDBObject=\qTables\q,TCDBObjectName=\qSurvey\q,TCControlID_Unmatched=\qDTCRecordset1\q,TCPPConn=\qGallery\q,RCDBObject=\qRCDBObject\q,TCPPDBObject=\qTables\q,TCPPDBObjectName=\qSurvey\q,TCCursorType=\q3\s-\sStatic\q,TCCursorLocation=\q3\s-\sUse\sclient-side\scursors\q,TCLockType=\q3\s-\sOptimistic\q,TCCacheSize_Unmatched=\q10\q,TCCommTimeout_Unmatched=\q10\q,CCPrepared=0,CCAllRecords=1,TCNRecords_Unmatched=\q10\q,TCODBCSyntax_Unmatched=\q\q,TCHTargetPlatform=\q\q,TCHTargetBrowser_Unmatched=\qServer\s(ASP)\q,TCTargetPlatform=\qInherit\sfrom\spage\q,RCCache=\qRCBookPage\q,CCOpen=1,GCParameters=(Rows=0))">
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
	cmdTmp.CommandText = '`Survey`';
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
<FONT FACE="Verdana, Arial, Helvetica" SIZE=2>
Donnez &#224; chacune des questions suivantes une note comprise entre 1 
et 5, 1 &#233;tant la note la plus basse et 5 la note la plus &#233;lev&#233;e.<BR>
<HR>

<TABLE>
<TR>
  <TD align=right><B>Directeur :</B></TD>
  <TD>
  <!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B5F0E450-DC5F-11D0-9846-0000F8027CA0" height=21 id=cboManager 
	style="HEIGHT: 21px; LEFT: 0px; TOP: 0px; WIDTH: 128px" width=128>
	<PARAM NAME="_ExtentX" VALUE="3387">
	<PARAM NAME="_ExtentY" VALUE="556">
	<PARAM NAME="id" VALUE="cboManager">
	<PARAM NAME="DataSource" VALUE="DTCRecordset1">
	<PARAM NAME="DataField" VALUE="Manager">
	<PARAM NAME="ControlStyle" VALUE="0">
	<PARAM NAME="Enabled" VALUE="-1">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="Platform" VALUE="0">
	<PARAM NAME="UsesStaticList" VALUE="-1">
	<PARAM NAME="CLSize" VALUE="5">
	<PARAM NAME="CLED0" VALUE="André Delfour">
	<PARAM NAME="CLEV0" VALUE="AndréDelfour">
	<PARAM NAME="CLED1" VALUE="Stephane Lamour">
	<PARAM NAME="CLEV1" VALUE="StephaneLamour">
	<PARAM NAME="CLED2" VALUE="Laure Calfont">
	<PARAM NAME="CLEV2" VALUE="LaureCalfont">
	<PARAM NAME="CLED3" VALUE="Jeanne Beauvoir">
	<PARAM NAME="CLEV3" VALUE="JeanneBeauvoir">
	<PARAM NAME="CLED4" VALUE="Robert Roy">
	<PARAM NAME="CLEV4" VALUE="RobertRoy">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<!--#INCLUDE FILE="../_ScriptLibrary/ListBox.ASP"-->
<script runat="server" language="JavaScript">
function _cboManager_ctor()
{
    CreateListbox('cboManager', _initcboManager);
}
function _initcboManager()
{
   cboManager.addItem('André Delfour', 'AndréDelfour');
   cboManager.addItem('Stephane Lamour', 'StephaneLamour');
   cboManager.addItem('Laure Calfont', 'LaureCalfont');
   cboManager.addItem('Jeanne Beauvoir', 'Jeanne Beauvoir');
   cboManager.addItem('Robert Roy', 'RobertRoy');
   cboManager.setDataSource(DTCRecordset1);
   cboManager.setDataField('Manager');
}
</script>
<%cboManager.display%>

<!--METADATA TYPE="DesignerControl" endspan-->
  </TD>
</TR>
<TR>
  <TD><B>P&#233;riode examin&#233;e :</B></TD>
  <TD>
 <!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B5F0E450-DC5F-11D0-9846-0000F8027CA0" height=21 id=cboPeriod 
	style="HEIGHT: 21px; LEFT: 0px; TOP: 0px; WIDTH: 117px" width=117>
	<PARAM NAME="_ExtentX" VALUE="3493">
	<PARAM NAME="_ExtentY" VALUE="556">
	<PARAM NAME="id" VALUE="cboPeriod">
	<PARAM NAME="DataSource" VALUE="DTCRecordset1">
	<PARAM NAME="DataField" VALUE="Period">
	<PARAM NAME="ControlStyle" VALUE="0">
	<PARAM NAME="Enabled" VALUE="-1">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="Platform" VALUE="0">
	<PARAM NAME="UsesStaticList" VALUE="-1">
	<PARAM NAME="CLSize" VALUE="4">
	<PARAM NAME="CLED0" VALUE="Premier trimestre">
	<PARAM NAME="CLEV0" VALUE="1">
	<PARAM NAME="CLED1" VALUE="Deuxième trimestre">
	<PARAM NAME="CLEV1" VALUE="2">
	<PARAM NAME="CLED2" VALUE="Troisième trimestre">
	<PARAM NAME="CLEV2" VALUE="3">
	<PARAM NAME="CLED3" VALUE="Quatrième trimestre">
	<PARAM NAME="CLEV3" VALUE="4">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<SCRIPT LANGUAGE=JavaScript RUNAT=Server>
function _initcboPeriod()
{
	cboPeriod.addItem('Premier trimestre', '1');
	cboPeriod.addItem('Deuxième trimestre', '2');
	cboPeriod.addItem('Troisième trimestre', '3');
	cboPeriod.addItem('Quatrième trimestre', '4');
	cboPeriod.setDataSource(DTCRecordset1);
	cboPeriod.setDataField('Period');
}
function _cboPeriod_ctor()
{
	CreateListbox('cboPeriod', _initcboPeriod, null);
}
</script>
<% cboPeriod.display %>

<!--METADATA TYPE="DesignerControl" endspan-->
  </TD>
</TR>
</TABLE>

<TABLE width=100%>
<TR>
  <TH>Question</TH>
  <TH>1 <---> 5</TH>
<TR>
  <TD><FONT size=2>Mon directeur comprend parfaitement tous les probl&#232;mes et les 
            complications que je rencontre dans mon travail.</FONT></TD>
  <TD>
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B5F0E45D-DC5F-11D0-9846-0000F8027CA0" height=31 id=Q1 style="HEIGHT: 31px; LEFT: 0px; TOP: 0px; WIDTH: 221px" 
	width=221>
	<PARAM NAME="_ExtentX" VALUE="5847">
	<PARAM NAME="_ExtentY" VALUE="820">
	<PARAM NAME="id" VALUE="Q1">
	<PARAM NAME="DataSource" VALUE="DTCRecordset1">
	<PARAM NAME="DataField" VALUE="Q1">
	<PARAM NAME="ControlStyle" VALUE="1">
	<PARAM NAME="BType" VALUE="0">
	<PARAM NAME="Enabled" VALUE="-1">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="Platform" VALUE="0">
	<PARAM NAME="UsesStaticList" VALUE="-1">
	<PARAM NAME="CLSize" VALUE="5">
	<PARAM NAME="CLED1" VALUE="">
	<PARAM NAME="CLEV1" VALUE="1">
	<PARAM NAME="CLED2" VALUE="">
	<PARAM NAME="CLEV2" VALUE="2">
	<PARAM NAME="CLED3" VALUE="">
	<PARAM NAME="CLEV3" VALUE="3">
	<PARAM NAME="CLED4" VALUE="">
	<PARAM NAME="CLEV4" VALUE="4">
	<PARAM NAME="CLED5" VALUE="">
	<PARAM NAME="CLEV5" VALUE="5">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<!--#INCLUDE FILE="../_ScriptLibrary/OptionGrp.ASP"-->
<script runat="server" language="JavaScript">
function _initQ1()
{
   Q1.addItem('', '1');
   Q1.addItem('', '2');
   Q1.addItem('', '3');
   Q1.addItem('', '4');
   Q1.addItem('', '5');
   Q1.setDataSource(DTCRecordset1);
   Q1.setDataField('Q1');
   Q1.setAlignment(1);
}
function _Q1_ctor()
{
   CreateOptionGroup('Q1', _initQ1, null);
}
</script>
<% Q1.display %>

<!--METADATA TYPE="DesignerControl" endspan-->
</TD>
</TR>
<TR>
  <TD><FONT size=2>Mon directeur 
            m'aide &#224; r&#233;soudre les probl&#232;mes complexes que je rencontre.</FONT></TD>
  <TD>
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B5F0E45D-DC5F-11D0-9846-0000F8027CA0" height=31 id=Q2 style="HEIGHT: 31px; LEFT: 0px; TOP: 0px; WIDTH: 221px" 
	width=221>
	<PARAM NAME="_ExtentX" VALUE="5847">
	<PARAM NAME="_ExtentY" VALUE="820">
	<PARAM NAME="id" VALUE="Q2">
	<PARAM NAME="DataSource" VALUE="DTCRecordset1">
	<PARAM NAME="DataField" VALUE="Q2">
	<PARAM NAME="ControlStyle" VALUE="1">
	<PARAM NAME="BType" VALUE="0">
	<PARAM NAME="Enabled" VALUE="-1">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="Platform" VALUE="0">
	<PARAM NAME="UsesStaticList" VALUE="-1">
	<PARAM NAME="CLSize" VALUE="5">
	<PARAM NAME="CLED1" VALUE="">
	<PARAM NAME="CLEV1" VALUE="1">
	<PARAM NAME="CLED2" VALUE="">
	<PARAM NAME="CLEV2" VALUE="2">
	<PARAM NAME="CLED3" VALUE="">
	<PARAM NAME="CLEV3" VALUE="3">
	<PARAM NAME="CLED4" VALUE="">
	<PARAM NAME="CLEV4" VALUE="4">
	<PARAM NAME="CLED5" VALUE="">
	<PARAM NAME="CLEV5" VALUE="5">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<script runat="server" language="JavaScript">
function _initQ2()
{
   Q2.addItem('', '1');
   Q2.addItem('', '2');
   Q2.addItem('', '3');
   Q2.addItem('', '4');
   Q2.addItem('', '5');
   Q2.setDataSource(DTCRecordset1);
   Q2.setDataField('Q2');
   Q2.setAlignment(1);
}
function _Q2_ctor()
{
   CreateOptionGroup('Q2', _initQ2, null);
}
</script>
<% Q2.display %>

<!--METADATA TYPE="DesignerControl" endspan-->
</TD>
</TR>
<TR>
  <TD><FONT size=2>Mon
            directeur m'aide &#224; fixer des objectifs clairs.</FONT></TD>
  <TD>
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B5F0E45D-DC5F-11D0-9846-0000F8027CA0" height=31 id=Q3 style="HEIGHT: 31px; LEFT: 0px; TOP: 0px; WIDTH: 221px" 
	width=221>
	<PARAM NAME="_ExtentX" VALUE="5847">
	<PARAM NAME="_ExtentY" VALUE="820">
	<PARAM NAME="id" VALUE="Q3">
	<PARAM NAME="DataSource" VALUE="DTCRecordset1">
	<PARAM NAME="DataField" VALUE="Q3">
	<PARAM NAME="ControlStyle" VALUE="1">
	<PARAM NAME="BType" VALUE="0">
	<PARAM NAME="Enabled" VALUE="-1">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="Platform" VALUE="0">
	<PARAM NAME="UsesStaticList" VALUE="-1">
	<PARAM NAME="CLSize" VALUE="5">
	<PARAM NAME="CLED1" VALUE="">
	<PARAM NAME="CLEV1" VALUE="1">
	<PARAM NAME="CLED2" VALUE="">
	<PARAM NAME="CLEV2" VALUE="2">
	<PARAM NAME="CLED3" VALUE="">
	<PARAM NAME="CLEV3" VALUE="3">
	<PARAM NAME="CLED4" VALUE="">
	<PARAM NAME="CLEV4" VALUE="4">
	<PARAM NAME="CLED5" VALUE="">
	<PARAM NAME="CLEV5" VALUE="5">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<script runat="server" language="JavaScript">
function _initQ3()
{
   Q3.addItem('', '1');
   Q3.addItem('', '2');
   Q3.addItem('', '3');
   Q3.addItem('', '4');
   Q3.addItem('', '5');
   Q3.setDataSource(DTCRecordset1);
   Q3.setDataField('Q3');
   Q3.setAlignment(1);
}
function _Q3_ctor()
{
   CreateOptionGroup('Q3', _initQ3, null);
}
</script>
<% Q3.display %>

<!--METADATA TYPE="DesignerControl" endspan-->
</TD>
</TR>
<TR>
  <TD><FONT size=2>Mon 
            directeur m'aide &#224; d&#233;terminer les priorit&#233;s de mon travail.</FONT></TD>
  <TD>
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B5F0E45D-DC5F-11D0-9846-0000F8027CA0" height=31 id=Q4 style="HEIGHT: 31px; LEFT: 0px; TOP: 0px; WIDTH: 221px" 
	width=221>
	<PARAM NAME="_ExtentX" VALUE="5847">
	<PARAM NAME="_ExtentY" VALUE="820">
	<PARAM NAME="id" VALUE="Q4">
	<PARAM NAME="DataSource" VALUE="DTCRecordset1">
	<PARAM NAME="DataField" VALUE="Q4">
	<PARAM NAME="ControlStyle" VALUE="1">
	<PARAM NAME="BType" VALUE="0">
	<PARAM NAME="Enabled" VALUE="-1">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="Platform" VALUE="0">
	<PARAM NAME="UsesStaticList" VALUE="-1">
	<PARAM NAME="CLSize" VALUE="5">
	<PARAM NAME="CLED1" VALUE="">
	<PARAM NAME="CLEV1" VALUE="1">
	<PARAM NAME="CLED2" VALUE="">
	<PARAM NAME="CLEV2" VALUE="2">
	<PARAM NAME="CLED3" VALUE="">
	<PARAM NAME="CLEV3" VALUE="3">
	<PARAM NAME="CLED4" VALUE="">
	<PARAM NAME="CLEV4" VALUE="4">
	<PARAM NAME="CLED5" VALUE="">
	<PARAM NAME="CLEV5" VALUE="5">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<script runat="server" language="JavaScript">
function _initQ4()
{
   Q4.addItem('', '1');
   Q4.addItem('', '2');
   Q4.addItem('', '3');
   Q4.addItem('', '4');
   Q4.addItem('', '5');
   Q4.setDataSource(DTCRecordset1);
   Q4.setDataField('Q4');
   Q4.setAlignment(1);
}
function _Q4_ctor()
{
   CreateOptionGroup('Q4', _initQ4, null);
}
</script>
<% Q4.display %>

<!--METADATA TYPE="DesignerControl" endspan-->
</TD>
</TR>
<TR>
  <TD><FONT size=2>Mon 
            directeur d&#233;finit des objectifs clairs pour notre groupe de travail.</FONT></TD>
  <TD>
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B5F0E45D-DC5F-11D0-9846-0000F8027CA0" height=31 id=Q5 style="HEIGHT: 31px; LEFT: 0px; TOP: 0px; WIDTH: 221px" 
	width=221>
	<PARAM NAME="_ExtentX" VALUE="5847">
	<PARAM NAME="_ExtentY" VALUE="820">
	<PARAM NAME="id" VALUE="Q5">
	<PARAM NAME="DataSource" VALUE="DTCRecordset1">
	<PARAM NAME="DataField" VALUE="Q5">
	<PARAM NAME="ControlStyle" VALUE="1">
	<PARAM NAME="BType" VALUE="0">
	<PARAM NAME="Enabled" VALUE="-1">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="Platform" VALUE="0">
	<PARAM NAME="UsesStaticList" VALUE="-1">
	<PARAM NAME="CLSize" VALUE="5">
	<PARAM NAME="CLED1" VALUE="">
	<PARAM NAME="CLEV1" VALUE="1">
	<PARAM NAME="CLED2" VALUE="">
	<PARAM NAME="CLEV2" VALUE="2">
	<PARAM NAME="CLED3" VALUE="">
	<PARAM NAME="CLEV3" VALUE="3">
	<PARAM NAME="CLED4" VALUE="">
	<PARAM NAME="CLEV4" VALUE="4">
	<PARAM NAME="CLED5" VALUE="">
	<PARAM NAME="CLEV5" VALUE="5">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<script runat="server" language="JavaScript">
function _initQ5()
{
   Q5.addItem('', '1');
   Q5.addItem('', '2');
   Q5.addItem('', '3');
   Q5.addItem('', '4');
   Q5.addItem('', '5');
   Q5.setDataSource(DTCRecordset1);
   Q5.setDataField('Q5');
   Q5.setAlignment(1);
}
function _Q5_ctor()
{
   CreateOptionGroup('Q5', _initQ5, null);
}
</script>
<% Q5.display %>

<!--METADATA TYPE="DesignerControl" endspan-->
</TD>
</TR>
</TABLE>

<BR>
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B6FC3A14-F837-11D0-9CC8-006008058731" height=27 id=Button1 style="HEIGHT: 27px; LEFT: 0px; TOP: 0px; WIDTH: 52px" 
	width=52>
	<PARAM NAME="_ExtentX" VALUE="1931">
	<PARAM NAME="_ExtentY" VALUE="714">
	<PARAM NAME="id" VALUE="Button1">
	<PARAM NAME="Caption" VALUE="Envoyer">
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
	Button1.value = 'Envoyer';
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
	<PARAM NAME="State" VALUE="(txtName_Unmatched=\qFormManager1\q,txtNewMode_Unmatched=\q\q,grFormMode=(Rows=2,Row1=(txtMode_Unmatched=\qSurvey\q),Row2=(txtMode_Unmatched=\qResults\q)),txtDefaultMode=\qSurvey\q,grMasterMode=(Rows=5,Row1=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qDTCRecordset1\q,txtProperty_Unmatched=\qaddRecord\q,txtValue_Unmatched=\q()\q),Row2=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qGrid1\q,txtProperty_Unmatched=\qhide\q,txtValue_Unmatched=\q()\q),Row3=(txtName_Unmatched=\q2\q,txtControl_Unmatched=\qButton1\q,txtProperty_Unmatched=\qdisabled\q,txtValue_Unmatched=\qtrue\q),Row4=(txtName_Unmatched=\q2\q,txtControl_Unmatched=\qLabel1\q,txtProperty_Unmatched=\qshow\q,txtValue_Unmatched=\q()\q),Row5=(txtName_Unmatched=\q2\q,txtControl_Unmatched=\qGrid1\q,txtProperty_Unmatched=\qshow\q,txtValue_Unmatched=\q()\q)),grTransitions=(Rows=1,Row1=(txtCurrentMode=\qSurvey\q,txtObject=\qButton1\q,txtEvent=\qonclick\q,txtNextMode=\qResults\q)),grMasterStep=(Rows=1,Row1=(txtName_Unmatched=\q1\q,txtControl_Unmatched=\qDTCRecordset1\q,txtAction_Unmatched=\qupdateRecord\q,txtValue_Unmatched=\q()\q)))"></OBJECT>
-->
<SCRIPT RUNAT=SERVER LANGUAGE="JavaScript">
function _FormManager1_ctor()
{
	thisPage.advise(PAGE_ONINIT, _FormManager1_init);
}
function _FormManager1_init()
{
	if (thisPage.getState("FormManager1_formmode") == null)
		_FormManager1_SetMode("Survey");
	Button1.advise("onclick", "_FormManager1_Button1_onclick()");
}
function _FormManager1_SetMode(formmode)
{
	thisPage.setState("FormManager1_formmode", formmode);
	if (formmode == "Survey")
	{
		DTCRecordset1.addRecord();
		Grid1.hide();
	}
	if (formmode == "Results")
	{
		Button1.disabled = true;
		Label1.show();
		Grid1.show();
	}
}
function _FormManager1_Button1_onclick()
{
	if (thisPage.getState("FormManager1_formmode") == "Survey")
	{
		DTCRecordset1.updateRecord();
		_FormManager1_SetMode("Results");
	}
	else _FormManager1_SetMode(thisPage.getState("FormManager1_formmode"))
}
</SCRIPT>


<!--METADATA TYPE="DesignerControl" endspan-->
<BR>
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B5F0E460-DC5F-11D0-9846-0000F8027CA0" height=17 id=Label1 style="HEIGHT: 17px; LEFT: 0px; TOP: 0px; WIDTH: 228px" 
	width=228>
	<PARAM NAME="_ExtentX" VALUE="7488">
	<PARAM NAME="_ExtentY" VALUE="450">
	<PARAM NAME="id" VALUE="Label1">
	<PARAM NAME="DataSource" VALUE="">
	<PARAM NAME="DataField" VALUE="Voici les résultats de cette enquête et d\'autres enquêtes :">
	<PARAM NAME="FontFace" VALUE="">
	<PARAM NAME="FontSize" VALUE="">
	<PARAM NAME="FontColor" VALUE="">
	<PARAM NAME="FontBold" VALUE="0">
	<PARAM NAME="FontItalic" VALUE="0">
	<PARAM NAME="Visible" VALUE="0">
	<PARAM NAME="FormatAsHTML" VALUE="0">
	<PARAM NAME="Platform" VALUE="256">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<!--#INCLUDE FILE="../_ScriptLibrary/Label.ASP"-->
<SCRIPT LANGUAGE=JavaScript RUNAT=Server>
function _initLabel1()
{
	Label1.hide();
	Label1.setCaption('Voici les résultats de cette enquête et d\'autres enquêtes :');
}
function _Label1_ctor()
{
	CreateLabel('Label1', _initLabel1, null);
}
</script>
<% Label1.display %>

<!--METADATA TYPE="DesignerControl" endspan-->
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
	<PARAM NAME="ColumnsNames" VALUE='"Manager","Period","Q1","Q2","Q3","Q4","Q5"'>
	<PARAM NAME="columnIndex" VALUE="0,1,2,3,4,5,6">
	<PARAM NAME="displayWidth" VALUE="68,68,68,68,68,68,68">
	<PARAM NAME="Coltype" VALUE="1,1,1,1,1,1,1">
	<PARAM NAME="formated" VALUE="0,0,0,0,0,0,0">
	<PARAM NAME="DisplayName" VALUE='"Manager","Period","Q1","Q2","Q3","Q4","Q5"'>
	<PARAM NAME="DetailAlignment" VALUE=",,,,,,">
	<PARAM NAME="HeaderAlignment" VALUE=",,,,,,">
	<PARAM NAME="DetailBackColor" VALUE=",,,,,,">
	<PARAM NAME="HeaderBackColor" VALUE=",,,,,,">
	<PARAM NAME="HeaderFont" VALUE=",,,,,,">
	<PARAM NAME="HeaderFontColor" VALUE=",,,,,,">
	<PARAM NAME="HeaderFontSize" VALUE=",,,,,,">
	<PARAM NAME="HeaderFontStyle" VALUE=",,,,,,">
	<PARAM NAME="DetailFont" VALUE=",,,,,,">
	<PARAM NAME="DetailFontColor" VALUE=",,,,,,">
	<PARAM NAME="DetailFontSize" VALUE=",,,,,,">
	<PARAM NAME="DetailFontStyle" VALUE=",,,,,,">
	<PARAM NAME="ColumnCount" VALUE="7">
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
	<PARAM NAME="StyleValue" VALUE="453613">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<!--#INCLUDE FILE="../_ScriptLibrary/RSNavBar.ASP"-->
<!--#INCLUDE FILE="../_ScriptLibrary/DataGrid.ASP"-->
<SCRIPT LANGUAGE=JavaScript RUNAT=Server>
function _initGrid1()
{
Grid1.pageSize = 0;
Grid1.setDataSource(DTCRecordset1);
Grid1.tableAttributes = 'align=center cellpadding=2  cellspacing=0 bordercolor=#cccccc bgcolor=White border=1 cols=7 rules=ALL WIDTH=304';
Grid1.headerAttributes = '   bgcolor=#003468 align=Left';
Grid1.headerWidth[0] = ' WIDTH=68';
Grid1.headerWidth[1] = ' WIDTH=68';
Grid1.headerWidth[2] = ' WIDTH=68';
Grid1.headerWidth[3] = ' WIDTH=68';
Grid1.headerWidth[4] = ' WIDTH=68';
Grid1.headerWidth[5] = ' WIDTH=68';
Grid1.headerWidth[6] = ' WIDTH=68';
Grid1.headerFormat = '<Font face="Arial" size=4 color=White> <b>';
Grid1.colHeader[0] = '\'Directeur\'';
Grid1.colHeader[1] = '\'Période\'';
Grid1.colHeader[2] = '\'T1\'';
Grid1.colHeader[3] = '\'T2\'';
Grid1.colHeader[4] = '\'T3\'';
Grid1.colHeader[5] = '\'T4\'';
Grid1.colHeader[6] = '\'T5\'';
Grid1.rowAttributes[0] = '  bgcolor = White align=Left bordercolor=#cccccc';
Grid1.rowAttributes[1] = '  bgcolor = Silver align=Left bordercolor=#cccccc';
Grid1.rowFormat[0] = ' <Font face="Arial" size=2 color=Black >';
Grid1.colAttributes[0] = '  WIDTH=68';
Grid1.colFormat[0] = '<Font Size=2 Face="Arial" Color=Black >';
Grid1.colData[0] = 'DTCRecordset1.fields.getValue(\'Manager\')';
Grid1.colAttributes[1] = '  WIDTH=68';
Grid1.colFormat[1] = '<Font Size=2 Face="Arial" Color=Black >';
Grid1.colData[1] = 'DTCRecordset1.fields.getValue(\'Period\')';
Grid1.colAttributes[2] = '  WIDTH=68';
Grid1.colFormat[2] = '<Font Size=2 Face="Arial" Color=Black >';
Grid1.colData[2] = 'DTCRecordset1.fields.getValue(\'Q1\')';
Grid1.colAttributes[3] = '  WIDTH=68';
Grid1.colFormat[3] = '<Font Size=2 Face="Arial" Color=Black >';
Grid1.colData[3] = 'DTCRecordset1.fields.getValue(\'Q2\')';
Grid1.colAttributes[4] = '  WIDTH=68';
Grid1.colFormat[4] = '<Font Size=2 Face="Arial" Color=Black >';
Grid1.colData[4] = 'DTCRecordset1.fields.getValue(\'Q3\')';
Grid1.colAttributes[5] = '  WIDTH=68';
Grid1.colFormat[5] = '<Font Size=2 Face="Arial" Color=Black >';
Grid1.colData[5] = 'DTCRecordset1.fields.getValue(\'Q4\')';
Grid1.colAttributes[6] = '  WIDTH=68';
Grid1.colFormat[6] = '<Font Size=2 Face="Arial" Color=Black >';
Grid1.colData[6] = 'DTCRecordset1.fields.getValue(\'Q5\')';
}
function _Grid1_ctor()
{
	CreateDataGrid('Grid1',_initGrid1);
}
</SCRIPT>

<%	Grid1.display %>


<!--METADATA TYPE="DesignerControl" endspan-->
<BR>
</FONT>

</BODY>
<% ' VI 6.0 Scripting Object Model Enabled %>
<% EndPageProcessing() %>
</FORM>
</HTML>