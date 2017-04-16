<%@ language=JavaScript %>
<% // VI 6.0 Scripting Object Model Enabled %>
<!--#include file="../_ScriptLibrary/pm.asp"-->
<% if (StartPageProcessing()) Response.End() %>
<FORM name=thisForm METHOD=post>

<SCRIPT LANGUAGE=JAVASCRIPT>
function JSValidate(strName,strEvent)
{	if (strName == 'Button1' || strName == 'TextBox1')
	{
		if (isNaN(thisForm.TextBox1.value))
		{
			alert('La zone de texte doit contenir un nombre.');
			thisForm.TextBox1.value=0;
			thisPage.cancelEvent = true;
		}
	}
}
function thisPage_onbeforeserverevent(strName,strEvent)
{
	JSValidate(strName,strEvent);
}
</SCRIPT>

<SCRIPT LANGUAGE=VBSCRIPT>
sub VBSValidate(strName,strEvent)
	if strName = "Button1" OR strName = "TextBox1" then
		if isNumeric(thisForm.TextBox1.value) = false then
			msgbox "VBS: La zone de texte doit contenir un nombre."
			thisPage.cancelEvent = true
		end if
	end if
end sub
</SCRIPT>

<SCRIPT LANGUAGE=JavaScript Runat=Server>
	function disable_opt(optX) {
		for (var i=0; i < optX.getCount(); i++)
			optX.getButton(i).disabled = true;
	}
</SCRIPT>

<SCRIPT RUNAT=SERVER LANGUAGE=JAVASCRIPT>
function thisPage_onenter()
{
	if (thisPage.firstEntered)
	{	// setup data first time only
		TextBox1.value = 0;
		ListBox1.addItem('rose',100);
		ListBox1.addItem('rouge',200);
		ListBox1.addItem('orange',300);
		ListBox1.addItem('jaune',400);
		ListBox1.addItem('vert',500);
		ListBox1.addItem('marron',600);
		ListBox1.addItem('bleu',700);
		ListBox1.addItem('bleu foncé',800);
		ListBox1.addItem('violet',900);
		ListBox1.addItem('noir',1000);
		ListBox1.selectedIndex = 0;
		OptionGroup1.addItem('rouge',200);
		OptionGroup1.addItem('orange',300);
		OptionGroup1.addItem('jaune',400);
		OptionGroup1.addItem('vert',500);
		OptionGroup1.addItem('bleu',700);
		OptionGroup1.addItem('violet',900);
		OptionGroup1.selectByIndex(0);
		disable_opt(OptionGroup1);
	}
}
function Button1_onclick()
{
	var n = Number(TextBox1.value);
	n += 1;
	TextBox1.value = n;
}
function Button2_onclick()
{
	ListBox1.selectedIndex += 1;
}
function RSNavBar1_onfirstclick()
{
	OptionGroup1.selectByIndex(0);
	Label1.setCaption(OptionGroup1.getCaption());
}
function RSNavBar1_onpreviousclick()
{
	OptionGroup1.selectByIndex(OptionGroup1.getSelectedIndex() - 1);
	Label1.setCaption(OptionGroup1.getCaption());
}
function RSNavBar1_onnextclick()
{
	OptionGroup1.selectByIndex(OptionGroup1.getSelectedIndex() + 1);
	Label1.setCaption(OptionGroup1.getCaption());
}
function RSNavBar1_onlastclick()
{
	OptionGroup1.selectByIndex(OptionGroup1.getCount() - 1);
	Label1.setCaption(OptionGroup1.getCaption());
}
function Button3_onclick()
{
	if (CheckBox1.getChecked())
	{
		CheckBox1.setChecked(false);
		CheckBox1.setCaption('Désactivé');
		Button3.value = 'Activer';
	}
	else
	{
		CheckBox1.setChecked(true);
		CheckBox1.setCaption('Activé');
		Button3.value = 'Désactiver';
	}
}
function TextBox1_onchange()
{
	var n = Number(TextBox1.value);
	n += 10;
	TextBox1.value = n;
}
function CheckBox1_onclick()
{
	if (CheckBox1.getChecked())
	{
		CheckBox1.setCaption('Activé');
		Button3.value = 'Désactiver';
	}
	else
	{
		CheckBox1.setCaption('Désactivé');
		Button3.value = 'Activer';
	}
}
function OptionGroup1_onchange()
{
	Label1.setCaption(OptionGroup1.getCaption());
}

</SCRIPT>

<HTML>
<BODY bgColor=#ffffff leftMargin=40 link=#500000 vLink=#505050>
<FONT FACE="Verdana, Arial, Helvetica" SIZE=2>
<%=RunHtm%>
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B6FC3A14-F837-11D0-9CC8-006008058731" id=Button1 style="LEFT: 0px; TOP: 0px">
	<PARAM NAME="_ExtentX" VALUE="3995">
	<PARAM NAME="_ExtentY" VALUE="714">
	<PARAM NAME="id" VALUE="Button1">
	<PARAM NAME="Caption" VALUE="Incrémenter la Zone de texte">
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
    Button1.value = 'Incrémenter la Zone de texte';
    Button1.setStyle(0);
}
function _Button1_ctor()
{
   CreateButton('Button1', _initButton1, null);
}
</script>
<% Button1.display(); %>

<!--METADATA TYPE="DesignerControl" endspan-->
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B5F0E469-DC5F-11D0-9846-0000F8027CA0" height=25 id=TextBox1 
	style="HEIGHT: 25px; LEFT: 0px; TOP: 0px; WIDTH: 209px" width=209>
	<PARAM NAME="_ExtentX" VALUE="5530">
	<PARAM NAME="_ExtentY" VALUE="503">
	<PARAM NAME="id" VALUE="TextBox1">
	<PARAM NAME="ControlType" VALUE="0">
	<PARAM NAME="Lines" VALUE="3">
	<PARAM NAME="DataSource" VALUE="">
	<PARAM NAME="DataField" VALUE="">
	<PARAM NAME="Enabled" VALUE="-1">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="MaxChars" VALUE="10">
	<PARAM NAME="DisplayWidth" VALUE="34">
	<PARAM NAME="Platform" VALUE="256">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<!--#INCLUDE FILE="../_ScriptLibrary/TextBox.ASP"-->
<script runat="server" language="JavaScript">
function _initTextBox1()
{
   TextBox1.setStyle(TXT_TEXTBOX);
   TextBox1.setMaxLength(10);
   TextBox1.setColumnCount(14);
}
function _TextBox1_ctor()
{
   CreateTextbox('TextBox1', _initTextBox1, null);
}
</script>
<% TextBox1.display(); %>

<!--METADATA TYPE="DesignerControl" endspan-->


<BR><BR>
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B6FC3A14-F837-11D0-9CC8-006008058731" id=Button2 style="LEFT: 0px; TOP: 0px">
	<PARAM NAME="_ExtentX" VALUE="4022">
	<PARAM NAME="_ExtentY" VALUE="714">
	<PARAM NAME="id" VALUE="Button2">
	<PARAM NAME="Caption" VALUE="Incrémenter la Sélection">
	<PARAM NAME="Image" VALUE="">
	<PARAM NAME="AltText" VALUE="">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="Platform" VALUE="256">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<script runat="server" language="JavaScript">
function _initButton2()
{
    Button2.value = 'Incrémenter la Sélection';
    Button2.setStyle(0);
}
function _Button2_ctor()
{
   CreateButton('Button2', _initButton2, null);
}
</script>
<% Button2.display(); %>

<!--METADATA TYPE="DesignerControl" endspan-->
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B5F0E450-DC5F-11D0-9846-0000F8027CA0" id=ListBox1 style="LEFT: 0px; TOP: 0px">
	<PARAM NAME="_ExtentX" VALUE="2037">
	<PARAM NAME="_ExtentY" VALUE="556">
	<PARAM NAME="id" VALUE="ListBox1">
	<PARAM NAME="DataSource" VALUE="">
	<PARAM NAME="DataField" VALUE="">
	<PARAM NAME="ControlStyle" VALUE="0">
	<PARAM NAME="Enabled" VALUE="-1">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="Platform" VALUE="256">
	<PARAM NAME="UsesStaticList" VALUE="0">
	<PARAM NAME="RowSource" VALUE="">
	<PARAM NAME="BoundColumn" VALUE="">
	<PARAM NAME="ListField" VALUE="">
	<PARAM NAME="LookupPlatform" VALUE="2">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<!--#INCLUDE FILE="../_ScriptLibrary/ListBox.ASP"-->
<script runat="server" language="JavaScript">
function _ListBox1_ctor()
{
   CreateListbox('ListBox1', null, null);
}
</script>
<% ListBox1.display(); %>

<!--METADATA TYPE="DesignerControl" endspan-->


<BR><BR>
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B6FC3A14-F837-11D0-9CC8-006008058731" id=Button3 style="LEFT: 0px; TOP: 0px">
	<PARAM NAME="_ExtentX" VALUE="1561">
	<PARAM NAME="_ExtentY" VALUE="714">
	<PARAM NAME="id" VALUE="Button3">
	<PARAM NAME="Caption" VALUE="Activer">
	<PARAM NAME="Image" VALUE="">
	<PARAM NAME="AltText" VALUE="">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="Platform" VALUE="256">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<script runat="server" language="JavaScript">
function _initButton3()
{
    Button3.value = 'Activer';
    Button3.setStyle(0);
}
function _Button3_ctor()
{
   CreateButton('Button3', _initButton3, null);
}
</script>
<% Button3.display(); %>

<!--METADATA TYPE="DesignerControl" endspan-->
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B5F0E46C-DC5F-11D0-9846-0000F8027CA0" height=23 id=CheckBox1 
	style="HEIGHT: 23px; LEFT: 0px; TOP: 0px; WIDTH: 98px" width=98>
	<PARAM NAME="_ExtentX" VALUE="2514">
	<PARAM NAME="_ExtentY" VALUE="714">
	<PARAM NAME="id" VALUE="CheckBox1">
	<PARAM NAME="Caption" VALUE="désactivé">
	<PARAM NAME="DataSource" VALUE="">
	<PARAM NAME="DataField" VALUE="">
	<PARAM NAME="Enabled" VALUE="-1">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="Platform" VALUE="256">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<!--#INCLUDE FILE="../_ScriptLibrary/CheckBox.ASP"-->
<script runat="server" language="JavaScript">
function _initCheckBox1()
{
   CheckBox1.setCaption('Désactivé');
}
function _CheckBox1_ctor()
{
   CreateCheckbox('CheckBox1', _initCheckBox1, null);
}
</script>
<% CheckBox1.display(); %>

<!--METADATA TYPE="DesignerControl" endspan-->


<BR><BR>
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:58F3D268-FEDF-11D0-9C7F-0060081840F3" height=32 id=RSNavBar1 
	style="HEIGHT: 32px; LEFT: 0px; TOP: 0px; WIDTH: 142px" width=142>
	<PARAM NAME="_ExtentX" VALUE="4075">
	<PARAM NAME="_ExtentY" VALUE="714">
	<PARAM NAME="id" VALUE="RSNavBar1">
	<PARAM NAME="Platform" VALUE="256">
	<PARAM NAME="DataSource" VALUE="">
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
<script runat="server" language="JavaScript">
function _initRSNavBar1()
{
    RSNavBar1.setAlignment(1);
    RSNavBar1.setButtonStyles(170);
    RSNavBar1.updateOnMove = false;
    RSNavBar1.getButton(0).value = ' |< ';
    RSNavBar1.getButton(1).value = '  <  ';
    RSNavBar1.getButton(2).value = '  >  ';
    RSNavBar1.getButton(3).value = ' >| ';
}
function _RSNavBar1_ctor()
{
   CreateRecordsetNavbar('RSNavBar1', _initRSNavBar1, null);
}
</script>
<% RSNavBar1.display(); %>

<!--METADATA TYPE="DesignerControl" endspan-->
&nbsp;&nbsp;&nbsp;
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B5F0E460-DC5F-11D0-9846-0000F8027CA0" height=23 id=Label1 style="HEIGHT: 23px; LEFT: 0px; TOP: 0px; WIDTH: 40px" 
	width=40>
	<PARAM NAME="_ExtentX" VALUE="1111">
	<PARAM NAME="_ExtentY" VALUE="609">
	<PARAM NAME="id" VALUE="Label1">
	<PARAM NAME="DataSource" VALUE="">
	<PARAM NAME="DataField" VALUE="Couleur">
	<PARAM NAME="FontFace" VALUE="">
	<PARAM NAME="FontSize" VALUE="3">
	<PARAM NAME="FontColor" VALUE="">
	<PARAM NAME="FontBold" VALUE="0">
	<PARAM NAME="FontItalic" VALUE="0">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="FormatAsHTML" VALUE="0">
	<PARAM NAME="Platform" VALUE="256">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<!--#INCLUDE FILE="../_ScriptLibrary/Label.ASP"-->
<FONT SIZE="3">
<script runat="server" language="JavaScript">
function _initLabel1()
{
   Label1.setCaption('Couleur');
}
function _Label1_ctor()
{
   CreateLabel('Label1', _initLabel1, null);
}
</script>
<% Label1.display(); %>
</FONT>

<!--METADATA TYPE="DesignerControl" endspan-->

<BR><BR>
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:B5F0E45D-DC5F-11D0-9846-0000F8027CA0" height=31 id=OptionGroup1 
	style="HEIGHT: 31px; LEFT: 0px; TOP: 0px; WIDTH: 88px" width=88>
	<PARAM NAME="_ExtentX" VALUE="2328">
	<PARAM NAME="_ExtentY" VALUE="820">
	<PARAM NAME="id" VALUE="OptionGroup1">
	<PARAM NAME="DataSource" VALUE="">
	<PARAM NAME="DataField" VALUE="">
	<PARAM NAME="ControlStyle" VALUE="1">
	<PARAM NAME="BType" VALUE="0">
	<PARAM NAME="Enabled" VALUE="0">
	<PARAM NAME="Visible" VALUE="-1">
	<PARAM NAME="Platform" VALUE="256">
	<PARAM NAME="UsesStaticList" VALUE="0">
	<PARAM NAME="RowSource" VALUE="">
	<PARAM NAME="BoundColumn" VALUE="">
	<PARAM NAME="ListField" VALUE="">
	<PARAM NAME="LookupPlatform" VALUE="2">
	<PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<!--#INCLUDE FILE="../_ScriptLibrary/OptionGrp.ASP"-->
<script runat="server" language="JavaScript">
function _initOptionGroup1()
{
   for(var i=0; i < OptionGroup1.getCount(); i++)
       OptionGroup1.getButton(i).disabled = true;
   OptionGroup1.setAlignment(1);
}
function _OptionGroup1_ctor()
{
   CreateOptionGroup('OptionGroup1', _initOptionGroup1, null);
}
</script>
<% OptionGroup1.display(); %>

<!--METADATA TYPE="DesignerControl" endspan-->
<BR><BR>
<SCRIPT LANGUAGE=VBScript RUNAT=Server>
	If InStr(Request.ServerVariables("HTTP_User_Agent"),"MSIE 4") <> 0 then
		RunHtm="<A HREF=dtctest.htm>Ex&#233;cuter la version HTM</A><BR><BR>"
	Else
		RunHtm=""
	End If
</SCRIPT>
</FONT>
</BODY>
<% // VI 6.0 Scripting Object Model Enabled %>
<% EndPageProcessing() %>
</FORM>
</HTML>


