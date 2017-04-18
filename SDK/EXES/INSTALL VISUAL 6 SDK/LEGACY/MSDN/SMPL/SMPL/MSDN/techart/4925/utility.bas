Attribute VB_Name = "MUtility"
Option Explicit

'$ Uses DEBUG.BAS

''@B CopyMemory
Declare Sub CopyMemory Lib "KERNEL32" Alias "RtlMoveMemory" ( _
    lpvDest As Any, lpvSource As Any, ByVal cbCopy As Long)
''@E CopyMemory

''@B GetRefPtr
Declare Function GetRefPtr Lib "VBUTIL32" (lpVoid As Any) As Long
''@E GetRefPtr
''@B VarPtr
Declare Function VarPtr Lib "VB40032" (lpVoid As Any) As Long
''@E VarPtr


'         1         2         3         4         5         6         7         8
'12345678901234567890123456789012345678901234567890123456789012345678901234567890

Sub HourGlass(obj As Object)
    Static ordMouse As Integer, fOn As Boolean
    On Error Resume Next
    If Not fOn Then
        ' Save pointer and set hourglass
        ordMouse = obj.MousePointer
        obj.MousePointer = vbHourglass
        fOn = True
    Else
        ' Restore pointer
        obj.MousePointer = ordMouse
        fOn = False
    End If
    BugAssert Err = 0   ' Failure means illegal obj
End Sub

''@B IsArrayEmpty
Function IsArrayEmpty(va As Variant) As Boolean
    Dim v As Variant
    On Error Resume Next
    v = va(LBound(va))
    IsArrayEmpty = (Err <> 0)
End Function
''@E IsArrayEmpty

''@B HasShell
Function HasShell() As Boolean
    Dim dw As Long
    dw = GetVersion()
    If (dw And &HFF&) >= 4 Then
        HasShell = True
        ' Proves that operating system has shell, but not
        ' necessarily that it is installed. Some might argue
        ' that this function should check Registry under WinNT
        ' or SYSTEM.INI Shell= under Win95
    End If
End Function
''@E HasShell

' Set or clear iBitPos bit in iValue according to whether
' iTest expression is true.
''@B SetBit
Sub SetBit(ByVal iTest As Boolean, iValue As Integer, ByVal iBitPos As Integer)
    If iTest Then
        iValue = LoWord(iValue Or (2 ^ iBitPos))
    Else
        iValue = LoWord(iValue And Not (2 ^ iBitPos))
    End If
End Sub
''@E SetBit

Sub SetBitLong(ByVal iTest As Boolean, iValue As Long, ByVal iBitPos As Integer)
    If iTest Then
        iValue = iValue Or (2 ^ iBitPos)
    Else
        iValue = iValue And Not (2 ^ iBitPos)
    End If
End Sub

' Get state of iBitPos bit in iValue
''@B GetBit
Function GetBit(ByVal iValue As Long, ByVal iBitPos As Integer) As Boolean
    GetBit = iValue And (2 ^ iBitPos)
End Function
''@E GetBit

Function FmtHex(ByVal i As Long, ByVal iWidth As Integer) As String
    FmtHex = Right$(String$(iWidth, "0") & Hex$(i), iWidth)
End Function

Function FmtInt(ByVal iVal As Integer, ByVal iWidth As Integer, _
                Optional fRight As Variant) As String
    If IsMissing(fRight) Then fRight = False
    If fRight Then
        FmtInt = Left$(Trim$(Str$(iVal)) & Space$(iWidth), iWidth)
    Else
        ''@B FmtInt
        FmtInt = Right$(Space$(iWidth) & Trim$(Str$(iVal)), iWidth)
        ''@E FmtInt
    End If
End Function

Function FmtStr(s As String, ByVal iWidth As Integer, _
                Optional fRight As Variant) As String
    If IsMissing(fRight) Then fRight = True
    If fRight Then
        FmtStr = Left$(s & Space$(iWidth), iWidth)
    Else
        FmtStr = Right$(Space$(iWidth) & s, iWidth)
    End If
End Function

' Find the True option from a control array of OptionButton controls
Function GetOption(opts As Object) As Integer
    On Error GoTo GetOptionFail
    Dim opt As OptionButton
    For Each opt In opts
        If opt.Value Then
            GetOption = opt.Index
            Exit Function
        End If
    Next
GetOptionFail:
    GetOption = -1
End Function

' Set indexed option to True and return index of previous True option
Function SetOption(opts As Object, iTarget As Integer) As Integer
    ' Assume no option set True
    SetOption = -1
    On Error GoTo SetOptionFail
    Dim opt As OptionButton
    For Each opt In opts
        ' Save last True value for return
        If opt.Value Then SetOption = opt.Index
        ' Set new value
        opt.Value = (opt.Index = iTarget)
    Next
SetOptionFail:
End Function

' Make sure path ends in a backslash
Function NormalizePath(sPath As String) As String
    NormalizePath = sPath
    If Right$(sPath, 1) <> "\" Then NormalizePath = sPath & "\"
End Function

Function FileExist(sSpec As String) As Integer
    On Error Resume Next
    Call FileLen(sSpec)
    FileExist = (Err = 0)
End Function

Function GetExtPos(sSpec As String) As Integer
    Dim iLast As Integer, iExt As Integer
    iLast = Len(sSpec)
    
    ' Parse backward to find extension or base
    For iExt = iLast + 1 To 1 Step -1
        Select Case Mid$(sSpec, iExt, 1)
        Case "."
            ' First . from right is extension start
            Exit For
        Case "\"
            ' First \ from right is base start
            iExt = iLast + 1
            Exit For
        End Select
    Next

    ' Negative return indicates no extension, but this
    ' is base so callers don't have to reparse.
    GetExtPos = iExt
End Function


''@B GetFileText
Function GetFileText(sFileName As String, _
                     Optional vErr As Variant) As String
    Dim nFile As Integer, CFile As Long, sText As String
    On Error GoTo GetFileTextError
    nFile = FreeFile
    'Open sFileName For Input As nFile ' Don't do this!!!
    ' Let others read but not write
    Open sFileName For Binary Access Read Lock Write As nFile
    sText = Input$(LOF(nFile), nFile)
    Close nFile
    GetFileText = sText
    Exit Function
    
GetFileTextError:
    vErr = Err
End Function
''@E GetFileText

Function GetRandom(iLo As Integer, iHi As Integer) As Integer
    GetRandom = Int(iLo + (Rnd * (iHi - iLo + 1)))
End Function

Function HexDumpS(s As String, Optional vTwoColumn As Variant) As String
    Dim ab() As Byte
    ab = StrToStrB(s)
    HexDumpS = HexDump(ab, vTwoColumn)
End Function

Function HexDumpB(s As String, Optional vTwoColumn As Variant) As String
    Dim ab() As Byte
    ab = s
    HexDumpB = HexDump(ab, vTwoColumn)
End Function

Function HexDump(ab() As Byte, Optional vTwoColumn As Variant) As String
    Dim i As Integer, sDump As String, sAscii As String
    Dim iColumn As Integer, iCur As Integer, sCur As String
    Dim sLine As String
    If IsMissing(vTwoColumn) Then vTwoColumn = True
    iColumn = 8
    If vTwoColumn Then iColumn = 16
    For i = LBound(ab) To UBound(ab)
        ' Get current character
        iCur = ab(i)
        sCur = Chr$(iCur)

        ' Append its hex value
        sLine = sLine & Right$("0" & Hex$(iCur), 2) & " "

        ' Append its ASCII value or dot
        If iCur >= 32 And iCur < 127 Then
            sAscii = sAscii & sCur
        Else
            sAscii = sAscii & "."
        End If

        ' Append ASCII to dump and wrap every paragraph
        If (i + 1) Mod 8 = 0 Then sLine = sLine & " "
        If (i + 1) Mod iColumn = 0 Then
            sLine = sLine & " " & sAscii & sCrLf
            sDump = sDump & sLine
            sAscii = sEmpty
            sLine = sEmpty
        End If
    Next
    If (i + 1) Mod iColumn Then
        If vTwoColumn Then
            sLine = Left$(sLine & Space$(53), 53) & sAscii
        Else
            sLine = Left$(sLine & Space$(26), 26) & sAscii
        End If
        sDump = sDump & sLine
    End If
    HexDump = sDump

End Function

''@B StrToStrB
Function StrToStrB(ByVal s As String) As String
    StrToStrB = StrConv(s, vbFromUnicode)
End Function
''@E StrToStrB

''@B StrBToStr
Function StrBToStr(ByVal s As String) As String
    StrBToStr = StrConv(s, vbUnicode)
End Function
''@E StrBToStr

Function StrZToStr(s As String) As String
    Dim i As Integer
    i = InStr(s, sNullChr)
    If i Then
        StrZToStr = Left$(s, InStr(s, sNullChr) - 1)
    Else
        StrZToStr = s
    End If
End Function

Sub SaveFileStr(sFile As String, sContent As String)
    Dim nFile As Integer
    nFile = FreeFile
    Open sFile For Output Access Write Lock Write As nFile
    Print #nFile, sContent;
    Close nFile
End Sub

Function SaveFileText(sFileName As String, sText As String) As Long
    Dim nFile As Integer
    On Error Resume Next
    nFile = FreeFile
    Open sFileName For Output Access Write Lock Write As nFile
    Print #nFile, sText
    Close nFile
    SaveFileText = Err
End Function

#If 0 Then
' This wretched function should be replaced with C version
' that uses Boyer-Moore or some other sophisticated
' string search algorithm
Function InStrR(iPos As Integer, sSrc As String, _
                sWhat As Variant, ordType As Integer) As Integer

    Dim i As Integer, c As Integer
    InStrR = 0
    c = Len(sWhat)
    For i = iPos To 1 Step -1
        If StrComp(Mid$(sSrc, i, c), sWhat, ordType) = 0 Then
            InStrR = i
            Exit Function
        End If
    Next

End Function
#End If

Function Swap(i As Integer)
    Dim iHi As Integer, iLo As Integer
    iHi = i And &HFF
    If iHi <= 127 Then
        iHi = iHi * 256
    Else
        iHi = -iHi * 256
    End If
    iLo = i / 256
    Swap = iLo Or iHi
End Function

Function IsSet(v As Variant) As Boolean
    IsSet = IsObject(v)
    If IsSet Then IsSet = Not (v Is Nothing)
End Function

''@B VBGetLogicalDrives
Function VBGetLogicalDrives() As String

    Dim f32  As Long, i As Integer, s As String
    f32 = GetLogicalDrives()
    For i = 0 To 25
        s = s & IIf(f32 And 1, "+", "-")
        f32 = RShiftDWord(f32, 1)
    Next
    VBGetLogicalDrives = s
    
End Function
''@E VBGetLogicalDrives

Function ErrorBox(e As Object) As Integer
    Dim s As String
    s = s & "Number: " & e.Number & sCrLf
    s = s & "Description: " & e.Description & sCrLf
    s = s & "Source: " & e.Source & sCrLf
    ErrorBox = MsgBox(s)
End Function

''@B InsertChar
Sub InsertChar(sTarget As String, sChar As String, iPos As Integer)
    BugAssert Len(sChar) = 1        ' Accept characters only
    BugAssert iPos <= Len(sTarget)  ' Don't insert beyond end
    Mid$(sTarget, iPos, 1) = sChar  ' Do work
End Sub
''@E InsertChar

Function LineWrap(sText As String, cMax As Integer)
    Dim s As String, i As Integer, iLast As Integer, c As Integer
    c = Len(sText)
    i = 1
    Do While c
        iLast = i
        i = i + cMax
        Do While Mid$(sText, i, 1) <> sSpace
            i = i - 1
        Loop
        s = s & Mid$(sText, iLast, i - iLast) & sCrLf & "   "
        i = i + 1
    Loop
    LineWrap = s
End Function

''@B Among
' Pascal:    if ch in ['a', 'f', 'g'] then
' Basic:     If Among(ch, "a", "f", "g") Then
Function Among(vTarget As Variant, _
               ParamArray a() As Variant) As Boolean
    Among = True        ' Assume found
    Dim v As Variant
    For Each v In a()
        If v = vTarget Then Exit Function
    Next
    Among = False
End Function
''@E Among

''@B CommitFile
#If Win32 = False Then
Function CommitFile(nFile As Integer) As Boolean
    Dim hFile As Integer
    hFile = FileAttr(nFile, 2)  ' Convert file number to file handle
    ' Commit file to disk
    CommitFile = FlushFileBuffers(hFile)
End Function
#End If
''@E CommitFile

Function GetLabel(sRoot As String) As String
    GetLabel = Dir$(sRoot & "*.*", vbVolume)
End Function

Function GetFileBase(sFile As String) As String
    Dim vBase As Variant, vExt As Variant, s As String
    If sFile = sEmpty Then Exit Function
    s = GetFullPath(sFile, vBase, vExt)
    If Mid$(s, vExt, 1) = "." Then
        GetFileBase = Mid$(s, vBase, vExt - vBase)
    Else
        GetFileBase = Mid$(s, vBase)
    End If
End Function

Function GetFileBaseExt(sFile As String) As String
    Dim vBase As Variant, s As String
    If sFile = sEmpty Then Exit Function
    s = GetFullPath(sFile, vBase)
    GetFileBaseExt = Mid$(s, vBase)
End Function

Function GetFileExt(sFile As String) As String
    Dim vExt As Variant, s As String
    If sFile = sEmpty Then Exit Function
    s = GetFullPath(sFile, , vExt)
    If Mid$(s, vExt, 1) = "." Then GetFileExt = Mid$(s, vExt)
End Function

Function GetFileDir(sFile As String) As String
    Dim vBase As Variant, s As String
    If sFile = sEmpty Then Exit Function
    s = GetFullPath(sFile, vBase)
    GetFileDir = Left$(s, vBase - 1)
End Function

Function GetFileFullSpec(sFile As String) As String
    Dim s As String
    If sFile = sEmpty Then Exit Function
    s = GetFullPath(sFile)
    GetFileFullSpec = s
End Function

Function SearchForExe(sName As String) As String
    Dim sSpec As String, asExt(1 To 5) As String, i As Integer
    asExt(1) = ".EXE": asExt(2) = ".COM": asExt(3) = ".PIF":
    asExt(4) = ".BAT": asExt(5) = ".CMD"
    For i = 1 To 4
        sSpec = SearchDirs(sName, asExt(i))
        If sSpec <> sEmpty Then Exit For
    Next
    SearchForExe = sSpec
End Function

Function IsExe() As Boolean
    Dim sExe  As String, c ' As SysInt
    sExe = String$(255, 0)
    c = GetModuleFileName(App.hInstance, sExe, 255)
    sExe = Left$(sExe, c)
    IsExe = (UCase$(Right$(sExe, 8)) <> "VB32.EXE")
End Function

''@B RightBottom
Function XRight(obj As Object) As Single
    XRight = obj.Left + obj.Width
End Function

Function YBottom(obj As Object) As Single
    YBottom = obj.Top + obj.Height
End Function
''@E RightBottom

''@B FilterText
Function FilterText(rfilt As Object) As Integer
    ' FilterText = 0 (assume success)
    
    ' Target can be another file or replacement of current file
    Dim sTarget As String, fReplace As Boolean
    sTarget = rfilt.TargetFile
    If sTarget = sEmpty Or sTarget = rfilt.SourceFile Then
        sTarget = GetTempFile(".", "FLT")
        fReplace = True
    End If
    
    ' Open input file
    On Error GoTo FilterTextError1
    Dim nIn As Integer, nOut As Integer
    nIn = FreeFile
    Open rfilt.SourceFile For Input Access Read Lock Write As #nIn

    ' Open target output file
    Dim sLine As String, iLine As Long
    On Error GoTo FilterTextError2
    nOut = FreeFile
    Open sTarget For Output Access Write Lock Read Write As #nOut

    ' Filter each line
    On Error GoTo FilterTextError3
    Do Until EOF(nIn)
        Line Input #nIn, sLine
        iLine = iLine + 1
        If Not rfilt.DoFilter(sLine, iLine) Then Exit Function
        Print #nOut, sLine
    Loop
    
    ' Close files
    On Error GoTo FilterTextError1
    Close nIn
    Close nOut
    If fReplace Then
        ' Destroy old file and replace it with new one
        Kill rfilt.SourceFile
        On Error Resume Next   ' No more errors allowed
        Name sTarget As rfilt.SourceFile
        ' If this fails, you're in trouble
        BugAssert Err = 0
    End If
    Exit Function
        
FilterTextError3:
    Close nOut
FilterTextError2:
    Close nIn
FilterTextError1:
    FilterText = Err
End Function
''@E FilterText
'
