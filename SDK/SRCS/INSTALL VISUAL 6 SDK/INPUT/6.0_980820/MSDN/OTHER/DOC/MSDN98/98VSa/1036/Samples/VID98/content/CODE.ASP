

<SCRIPT LANGUAGE=VBScript RUNAT=Server>
 REM Retourne le chiffre minimum supérieur à 0
 REM Si les deux sont égaux à 0, retourne -1
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
 FUNCTION FindFileName (strInclude)
	 istart = Instr(1, strInclude, Chr(34), 1)
	 If istart = 0 Then
		FindFileName = ""
	 Else
		iend = Instr(istart + 1, strInclude, Chr(34), 1)
		FindFileName = Mid(strInclude, istart + 1, iend - istart - 1)
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

iPos = InStr(1, strLine, "<" & "!--", 1)
  If fMin(iTemp, iPos) = iPos Then
    iTemp = iPos
    fCheckLine = 5
  End If

 iPos = InStr(1, strLine, "--" & ">", 1)
  If fMin(iTemp, iPos) = iPos Then
    iTemp = iPos
    fCheckLine = 6
  End If

'  iPos = InStr(1, UCase(strLine), "#INCLUDE", 1)
'   If fMin(iTemp, iPos) = iPos Then
'    iTemp = iPos
'    fCheckLine = 7
'   End If

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

	Case 5
      iPos = InStr(1, strLine, "<" & "!--", 1)
      Call PrintHTML(Left(strLine, iPos - 1))
      Response.Write("<FONT COLOR=#008000>")
	  Response.Write("&lt;!--")
      strLine = Right(strLine, Len(strLine) - (iPos + 3))
      Call PrintLine(strLine, fCheckLine(strLine))

    Case 6
      iPos = InStr(1, strLine, "--" & ">", 1)
      Call PrintHTML(Left(strLine, iPos - 1))
      Response.Write("--&gt;")
      Response.Write("</FONT>")
      strLine = Right(strLine, Len(strLine) - (iPos + 2))
      Call PrintLine(strLine, fCheckLine(strLine))

'    Case 7
'	  If Instr(1, UCase(strLine), "VIRTUAL") Then
'		strSearch = "#INCLUDE VIRTUAL="
'	  Else
'		strSearch = "#INCLUDE FILE="
'	  End If
'     iPos = InStr(1, UCase(strLine), strSearch, 1)
'      Call PrintHTML(Left(strLine, iPos - 1))
'	  strFileName = FindFileName(strLine)
'	  strWrite = strSearch & Chr(34) & "<A HREF=" & Chr(34)
'      strWrite = strWrite & "code.asp?source="
'	  strWrite = strWrite & strFileName & Chr(34) & ">"
'	  strWrite = strWrite & strFileName & "</A>"
'	  Response.Write(strWrite)
'      strLine = Right(strLine, Len(strLine) - (iPos + Len(strSearch) + Len(strFileName)))
'      Call PrintLine(strLine, fCheckLine(strLine))

    Case Else
      Response.Write("ERREUR DANS LA FONCTION -- VEUILLEZ CONTACTER L'ADMIN.")
  End Select
 END SUB
</SCRIPT>

<HTML>
<HEAD><TITLE>Visualiser le fichier source de Active Server</TITLE></HEAD>
<BODY BGCOLOR=#FFFFFF>

<FONT FACE="Verdana, Arial, Helvetica" SIZE=2>
<%
	Dim strVirtualPath, strFilename
	strVirtualPath = Request("source")
	strFilename = Server.MapPath(strVirtualPath)
	
	Dim FileObject, oInStream, strOutput
	Set FileObject = Server.CreateObject("Scripting.FileSystemObject")
	Set oInStream = FileObject.OpenTextFile(strFilename, 1, 0, 0 )
   While NOT oInStream.AtEndOfStream
     strOutput = oInStream.ReadLine
      Call PrintLine(strOutput, fCheckLine(strOutput))
      Response.Write("<BR>")
    Wend
%>
</FONT>
</BODY>
</HTML>
