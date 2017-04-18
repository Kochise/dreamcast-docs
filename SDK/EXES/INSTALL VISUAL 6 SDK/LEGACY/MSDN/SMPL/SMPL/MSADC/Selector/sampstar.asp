
<HTML>
<HEAD>
<TITLE>ADC Sample Selector</TITLE></HEAD>
<BODY BACKGROUND="/MSADC/Samples/AddressBook/Arcadia.gif">
<CENTER><H1> Sample Selector </H1></Center>
<Bold>Select a Client and Middle Tier to view a sample using that combination.</Bold>
<BR><Center>
<TABLE BORDER=2 CELLPADDING="5" CELLSPACING="5">
<TR>
<TD ALIGN="CENTER"><B><FONT COLOR="#800040">Client Tier</FONT></B></TD>
<TD ALIGN="CENTER"><B><FONT COLOR="#800040">Middle Tier</FONT></B></TD>
<TD ALIGN="CENTER"><B><FONT COLOR="#800040">Data Tier</FONT></B></TD>
</TR>

<TR>  <!-- These first two options are enabled as the default. -->
<TD ALIGN="LEFT"><INPUT TYPE="RADIO" NAME="optClient" CHECKED OnClick="SetCT('IEVBS')"> VBScript in Internet Explorer</TD>
<TD ALIGN="LEFT"><Input Type="RADIO" Name="optMiddleTier" CHECKED OnClick="SetMT('ADC')"> ADF Automatically</TD>
<TD ALIGN="CENTER" Width="150"><B><FONT COLOR="#008080">Chose Query Type On Sample Page</FONT></B></TD>
</TR>

<TR>
<TD ALIGN="LEFT"><INPUT TYPE="RADIO" NAME="optClient" OnClick="SetCT('VBC')"> Visual Basic</TD>
<TD ALIGN="LEFT"><INPUT TYPE="RADIO" Name="optMiddleTier" OnClick="SetMT('ADF')"> AdvancedDataFactory</TD>
</TR>

<TR>
<TD ALIGN="CENTER"></TD>
<TD ALIGN="LEFT"><Input Type="RADIO" Name="optMiddleTier" OnClick="SetMT('VBBO')"> Custom Visual Basic Business Object</TD>
<TR>
<TD ALIGN="CENTER"></TD>

</TABLE>

<BR>
<INPUT TYPE=BUTTON VALUE="GO see the Sample" NAME="GetSample">
<INPUT NAME="txtResult" SIZE="70" VALUE="The Advanced Data Control in the basic coding scenario from Internet Explorer">

</CENTER>

<SCRIPT LANGUAGE="VBScript">

Dim ClientTierSel
Dim MiddleTierSel

'Initialize starting selection values.
ClientTierSel = "IEVBS"
MiddleTierSel = "ADC"

'Reset Client Tier selection.
Sub SetCT(NewCT)	
	ClientTierSel = NewCT
	Call ShowStatus
End Sub

'Reset Middle Tier selection.
Sub SetMT(NewMT)
	MiddleTierSel = NewMT 
	Call ShowStatus
End Sub

'Update message based on Client and Middle Tier selections.
Sub ShowStatus()
	'IE client selections
	If ClientTierSel = "IEVBS" And MiddleTierSel = "ADC" Then 
		txtResult.Value= "The Advanced Data Control in the basic coding scenario from Internet Explorer"
	ElseIf ClientTierSel = "IEVBS" And MiddleTierSel = "ADF" Then
		txtResult.Value= "The Advanced Data Factory being called manually to get data"
	ElseIf ClientTierSel = "IEVBS" And MiddleTierSel = "VBBO" Then	
		txtResult.Value= "A Custom Business Object called from the ADC in Internet Explorer"
	End If

	'VB client selections
	If ClientTierSel = "VBC" And MiddleTierSel <> "VBBO" Then
		txtResult.Value= "The Advanced Data Factory being called from a Visual Basic client"
	ElseIf	ClientTierSel = "VBC" And MiddleTierSel = "VBBO" Then
		txtResult.Value= "A Custom Business Object called from a Visual Basic client"
	End If
End Sub

'Determine which sample page to call based on RADIO button settings.
Sub GetSample_OnClick
	'IE client selections
	If ClientTierSel = "IEVBS" And MiddleTierSel = "ADC" Then
		Window.location.href = "Client/IE/ADCAuto.asp"
	ElseIf ClientTierSel = "IEVBS" And MiddleTierSel = "ADF" Then
		Window.location.href ="Client/IE/ADCtoADF.asp"
	ElseIf ClientTierSel = "IEVBS"  And MiddleTierSel = "VBBO" Then
		Window.location.href ="Client/IE/ADCtoVB.asp"
	End If

	'VB client selections
	If ClientTierSel = "VBC" And MiddleTierSel <> "VBBO" Then
			Window.Open("Client/VB/VBtoADF/Setup/VBtoADF.htm")
	ElseIf ClientTierSel = "VBC" And MiddleTierSel = "VBBO" Then
			Window.Open("Client/VB/VBtoVB/Setup/VBtoVB.htm")
	End If		
End Sub

</SCRIPT>
</BODY>
</HTML>
