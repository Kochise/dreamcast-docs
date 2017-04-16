<SCRIPT LANGUAGE=VBScript RUNAT=Server>

 REM *************** NOTICE ****************
 REM * This file may only be used to view  *
 REM * source code of .asp files in the    *
 REM * AdvWorks or ASP Sample directory.   *	
 REM * If you wish to change the security  *
 REM * on this, modify or remove this      *
 REM * function.                           *
 REM ***************************************

 FUNCTION fValidPath (ByVal strPath)
  If InStr(1, strPath, "/Msadc/", 1) Then
    fValidPath = 1
  Else
    fValidPath = 0
  End If
 END FUNCTION
</SCRIPT>

<SCRIPT LANGUAGE=VBScript RUNAT=Server>
 REM Returns the minimum number greater than 0
 REM If both are 0, returns -1
 FUNCTION fMin (iNum1, iNum2)
  If iNum1 = 0 AND iNum2 = 0 Then
    fMin = -1
  ElseIf iNum2 = 0 Then
    fMin = iNum1
  ElseIf iNum1 = 0 Then
    fMin = iNum2
  ElseIf iNum1 < iNum2 Then
    fMin = iNum1
  Else 
    fMin = iNum2
  End If
 END FUNCTION
</SCRIPT>

<SCRIPT LANGUAGE=VBScript RUNAT=Server>
 FUNCTION fCheckLine (ByVal strLine)

  fCheckLine = 0
  iTemp = 0

  iPos = InStr(strLine, "<" & "%")
  If fMin(iTemp, iPos) = iPos Then
    iTemp = iPos
    fCheckLine = 1
  End If
  
  iPos = InStr(strLine, "%" & ">")
  If fMin(iTemp, iPos) = iPos Then
    iTemp = iPos
    fCheckLine = 2
  End If

  iPos = InStr(1, strLine, "<" & "SCRIPT", 1)
  If fMin(iTemp, iPos) = iPos Then
    iTemp = iPos
    fCheckLine = 3
  End If

  iPos = InStr(1, strLine, "<" & "/SCRIPT", 1)
  If fMin(iTemp, iPos) = iPos Then
    iTemp = iPos
    fCheckLine = 4
  End If

 END FUNCTION
</SCRIPT>

<SCRIPT LANGUAGE=VBScript RUNAT=Server>
SUB PrintHTML (ByVal strLine)
	iSpaces = Len(strLine) - Len(LTrim(strLine))
	i = 1
	While Mid(Strline, i, 1) = Chr(9)
		iSpaces = iSpaces + 5
		i = i + 1
	Wend
  If iSpaces > 0 Then
    For i = 1 to iSpaces
      Response.Write("&nbsp;")
    Next
  End If
  iPos = InStr(strLine, "<")
  If iPos Then
    Response.Write(Left(strLine, iPos - 1))
    Response.Write("&lt;")
    strLine = Right(strLine, Len(strLine) - iPos)
    Call PrintHTML(strLine)
  Else
    Response.Write(strLine)
  End If
 END SUB
</SCRIPT>
	
<SCRIPT LANGUAGE=VBScript RUNAT=Server>
 SUB PrintLine (ByVal strLine, iFlag)
  Select Case iFlag
    Case 0
      Call PrintHTML(strLine)
    Case 1
      iPos = InStr(strLine, "<" & "%")
      Call PrintHTML(Left(strLine, iPos - 1))
      Response.Write("<FONT COLOR=#ff0000>")
      Response.Write("&lt;%")
      strLine = Right(strLine, Len(strLine) - (iPos + 1))
      Call PrintLine(strLine, fCheckLine(strLine))
    Case 2
      iPos = InStr(strLine, "%" & ">")
      Call PrintHTML(Left(strLine, iPos -1))
      Response.Write("%&gt;")
      Response.Write("</FONT>")
      strLine = Right(strLine, Len(strLine) - (iPos + 1))
      Call PrintLine(strLine, fCheckLine(strLine))
    Case 3
      iPos = InStr(1, strLine, "<" & "SCRIPT", 1)
      Call PrintHTML(Left(strLine, iPos - 1))
      Response.Write("<FONT COLOR=#0000ff>")
      Response.Write("&lt;SCRIPT")
      strLine = Right(strLine, Len(strLine) - (iPos + 6))
      Call PrintLine(strLine, fCheckLine(strLine))
    Case 4
      iPos = InStr(1, strLine, "<" & "/SCRIPT>", 1)
      Call PrintHTML(Left(strLine, iPos - 1))
      Response.Write("&lt;/SCRIPT&gt;")
      Response.Write("</FONT>")
      strLine = Right(strLine, Len(strLine) - (iPos + 8))
      Call PrintLine(strLine, fCheckLine(strLine))
    Case Else
      Response.Write("FUNCTION ERROR -- PLEASE CONTACT ADMIN.")
  End Select
 END SUB
</SCRIPT>

<% strVirtualPath = Request("source") %>

<HTML>
<HEAD><TITLE>View Active Server Page Source</TITLE></HEAD>
<BODY BGCOLOR=#FFFFFF>
<FONT FACE="Verdana, Arial, Helvetica" SIZE=6>
<TABLE>
<TR>
<TD><IMG SRC="/Msadc/Samples/Selector/asp.gif" WIDTH=200 HEIGHT=93 BORDER=0 ALT="Active Server Page logo"></TD>
<TD><FONT FACE="Verdana, Arial, Helvetica" SIZE=6>View ASP Source</FONT></TD>
</TR>
</TABLE>
<FONT FACE="Verdana, Arial, Helvetica" SIZE=2>
Go Back to <a href="<%=strVirtualPath%>"><%=strVirtualPath%></A>
<BR>
<hr>
<%
If fValidPath(strVirtualPath) Then
	strFilename = Server.MapPath(strVirtualPath)
	Set FileObject = Server.CreateObject("Scripting.FileSystemObject")
	Set oInStream = FileObject.OpenTextFile (strFilename, 1, FALSE )
    While NOT oInStream.AtEndOfStream
      strOutput = oInStream.ReadLine
      Call PrintLine(strOutput, fCheckLine(strOutput))
      Response.Write("<BR>")
    Wend
  Else
    Response.Write("<H1>View Active Server Page Source-- Access Denied</H1>")
  End If  
%>

</BODY>
</HTML>
