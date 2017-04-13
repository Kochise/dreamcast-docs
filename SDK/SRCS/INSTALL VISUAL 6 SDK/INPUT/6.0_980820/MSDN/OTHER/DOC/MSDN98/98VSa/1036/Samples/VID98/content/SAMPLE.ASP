<%
Select Case Request("SampID")
	Case 1
		Sample="DEntryA.htm"
	Case 2
		Sample="QuoteA.htm"
	Case 3
		Sample="GridA.htm"
	Case 4
		Sample="QueryA.htm"
	Case 5
		Sample="PrefA.htm"
	Case 6
		Sample="CounterA.htm"
	Case 7
		Sample="SurveyA.htm"
	Case 8
		Sample="ControlA.htm"
	Case 9
		Sample="ShopCrtA.htm"
	Case 10
		Sample="UserNtA.htm"
	Case 11
		Sample="EmailA.htm"
	Case 12
		Sample="GuestBkA.htm"
	Case 13
		Sample="IE4A.htm"
	Case 14
		Sample="AppletA.htm"
	Case 15
		Sample="RandAdA.htm"
	Case 16
		Sample="ThemeA.htm"
	Case 17
		Sample="MMediaA.htm"
	Case 18
		Sample="TimeLnA.htm"
End Select
%>

<FRAMESET ROWS=175,* FRAMEBORDER=0 FRAMESPACING=0>
	<FRAME NAME=SampHdr SRC=SampHdr.asp?SampID=<%=Request("SampID")%> SCROLLING=Off>
	<FRAME NAME=SampMain SRC=<%=Sample%> SCROLLING=Auto>
</FRAMESET>