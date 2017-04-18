VERSION 4.00
Begin VB.Form FCppForVB 
   AutoRedraw      =   -1  'True
   Caption         =   "C++ For Visual Basic"
   ClientHeight    =   7836
   ClientLeft      =   1092
   ClientTop       =   1608
   ClientWidth     =   11088
   BeginProperty Font 
      name            =   "MS Sans Serif"
      charset         =   0
      weight          =   700
      size            =   7.8
      underline       =   0   'False
      italic          =   0   'False
      strikethrough   =   0   'False
   EndProperty
   Height          =   8160
   Icon            =   "Cpp4VB.frx":0000
   Left            =   1044
   LinkTopic       =   "Form1"
   ScaleHeight     =   7836
   ScaleWidth      =   11088
   Top             =   1332
   Width           =   11184
   Begin VB.CommandButton cmdFind 
      Caption         =   "String Find"
      Height          =   495
      Left            =   132
      TabIndex        =   11
      Top             =   5520
      Width           =   1335
   End
   Begin VB.CommandButton cmdExist 
      Caption         =   "Exist File"
      Height          =   495
      Left            =   132
      TabIndex        =   10
      Top             =   4920
      Width           =   1335
   End
   Begin VB.CommandButton cmdSA 
      Caption         =   "SAFEARRAY"
      Height          =   495
      Left            =   132
      TabIndex        =   9
      Top             =   3720
      Width           =   1335
   End
   Begin VB.CommandButton cmdBSTR 
      Caption         =   "BSTR"
      Height          =   495
      Left            =   132
      TabIndex        =   8
      Top             =   1920
      Width           =   1335
   End
   Begin VB.CommandButton cmdVariant 
      Caption         =   "Variant"
      Height          =   495
      Left            =   132
      TabIndex        =   7
      Top             =   2520
      Width           =   1335
   End
   Begin VB.CommandButton cmdArray 
      Caption         =   "Safe Array"
      Height          =   495
      Left            =   132
      TabIndex        =   6
      Top             =   3120
      Width           =   1335
   End
   Begin VB.CommandButton cmdParamArray 
      Caption         =   "ParamArray"
      Height          =   495
      Left            =   132
      TabIndex        =   5
      Top             =   4320
      Width           =   1335
   End
   Begin VB.CommandButton cmdBString 
      Caption         =   "BString"
      Height          =   495
      Left            =   132
      TabIndex        =   4
      Top             =   1320
      Width           =   1335
   End
   Begin VB.TextBox txtTest 
      BeginProperty Font 
         name            =   "Courier"
         charset         =   0
         weight          =   700
         size            =   9.6
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   6492
      Left            =   1560
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   3
      Top             =   108
      Width           =   9372
   End
   Begin VB.CommandButton cmdWin32 
      Caption         =   "Win32"
      Height          =   495
      Left            =   120
      TabIndex        =   2
      Top             =   720
      Width           =   1335
   End
   Begin VB.CommandButton cmdBits 
      Caption         =   "Bits"
      Height          =   495
      Left            =   132
      TabIndex        =   1
      Top             =   120
      Width           =   1335
   End
   Begin VB.CommandButton cmdExit 
      Caption         =   "Exit"
      Height          =   495
      Left            =   132
      TabIndex        =   0
      Top             =   6120
      Width           =   1335
   End
End
Attribute VB_Name = "FCppForVB"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdArray_Click()
    Dim aiInOut() As Integer
    ReDim Preserve aiInOut(1 To 8) As Integer
    Dim asOut() As String
    Dim va As Variant, i As Integer, s As String
    s = "Before:" & sCrLf & _
         "aiInOut(" & LBound(aiInOut) & " To " & UBound(aiInOut, 1) & ") As " & _
                      TypeName(aiInOut(LBound(aiInOut))) & sCrLf
    For i = LBound(aiInOut) To UBound(aiInOut)
        aiInOut(i) = i * i
        s = s & CStr(aiInOut(i)) & " "
    Next
    s = s & sCrLf
    BugMessage s
    va = TestSafeArray(aiInOut(), asOut())
    s = s & "After:" & sCrLf & _
         "aiInOut(" & LBound(aiInOut) & " To " & UBound(aiInOut) & ") As " & _
                      TypeName(aiInOut(LBound(aiInOut))) & sCrLf
    For i = LBound(aiInOut) To UBound(aiInOut)
        s = s & CStr(aiInOut(i)) & " "
    Next
    s = s & sCrLf
    s = s & "asOut(" & LBound(asOut()) & " To " & UBound(asOut()) & ") As " & _
            TypeName(asOut(LBound(asOut))) & sCrLf
    For i = LBound(asOut) To UBound(asOut)
        s = s & CStr(asOut(i)) & " "
    Next
    s = s & sCrLf
    s = s & "va(" & LBound(va) & " To " & UBound(va) & ") As " & _
            TypeName(va(LBound(va))) & sCrLf
    For i = LBound(va) To UBound(va)
        s = s & CStr(va(i)) & " "
    Next
    BugMessage s
    txtTest = s
End Sub

Private Sub cmdBSTR_Click()
    ' Must test in C++ debugger
    TestBStr
    Dim sIn As String, sInOut As String, sOut As String, sRet As String
    Dim s As String
    sIn = "Send me in"
    sInOut = "I'm in and out"
    s = s & "Before: " & sCrLf & _
            "   In parameter: " & sIn & sCrLf & _
            "   In/Out parameter: " & sInOut & sCrLf & _
            "   Out parameter: N/A" & sCrLf & _
            "   Return value: " & sRet & sCrLf
    sRet = TestBStrArgs(sIn, sInOut, sOut)
    s = s & "After: " & sCrLf & _
            "   In parameter: " & sIn & sCrLf & _
            "   In/Out parameter: " & sInOut & sCrLf & _
            "   Out parameter: " & sOut & sCrLf & _
            "   Return value: " & sRet & sCrLf
    txtTest = s
End Sub

Private Sub cmdBString_Click()
    Dim sIn As String, sInOut As String, sOut As String, sRet As String
    Dim s As String
    sIn = "Send me in"
    sInOut = "I'm going in..."
    s = s & "Before: " & sCrLf & _
            "   In parameter: " & sIn & sCrLf & _
            "   In/Out parameter: " & sInOut & sCrLf & _
            "   Out parameter: " & sOut & sCrLf & _
            "   Return value: " & sRet & sCrLf
    sRet = TestString(sIn, sInOut, sOut)
    s = s & "After: " & sCrLf & _
            "   In parameter: " & sIn & sCrLf & _
            "   In/Out parameter: " & sInOut & sCrLf & _
            "   Out parameter: " & sOut & sCrLf & _
            "   Return value: " & sRet & sCrLf
    BugMessage s
    txtTest = s
End Sub

Private Sub cmdExist_Click()

    Dim sName As String, s As String
    ' Test ExistFile
    s = "Test ExistFile" & sCrLf & sCrLf
    sName = Environ$("COMSPEC")
    s = s & "File " & sName & " exists: " & ExistFile(sName) & sCrLf
    sName = "nosuch.txt"
    s = s & "File " & sName & " exists: " & ExistFile(sName) & sCrLf
    txtTest = s
End Sub

Private Sub cmdFind_Click()
    Dim sTarget As String, sFind As String, s As String, i As Long, vPos As Variant
    sTarget = "A string In a String in a String in a string."
    vPos = 1
    s = s & sTarget & sCrLf
      s = s & "12345678901234567890123456789012345678901234567890" & sCrLf
    i = InStr(sTarget, "S")
    s = s & "i = InStr(sTarget, ""S"")              ' Found at position: " & i & sCrLf
    i = InStrR(sTarget, "S")
    s = s & "i = InStrR(sTarget, ""S"")             ' Found at position: " & i & sCrLf
    ' InStr can't use default position if Compare argument given
    i = InStr(1, sTarget, "S", 1)
    s = s & "i = InStr(1, sTarget, ""S"", 1)        ' Found at position: " & i & sCrLf
    ' InStrR can use default position if Compare argument given
    i = InStrR(sTarget, "S", 1)
    s = s & "i = InStrR(sTarget, ""S"", 1)          ' Found at position: " & i & sCrLf
    i = InStr(5, sTarget, "S", 1)
    s = s & "i = InStr(5, sTarget, ""S"", 1)        ' Found at position: " & i & sCrLf
    i = InStrR(42, sTarget, "S", 1)
    s = s & "i = InStrR(42, sTarget, ""S"", 1)      ' Found at position: " & i & sCrLf
    i = InStrR(sTarget, "Z")
    s = s & "i = InStrR(sTarget, ""Z"")             ' Found at position: " & i & sCrLf
    i = InStr(sTarget, "String")
    s = s & "i = InStr(sTarget, ""String"")         ' Found at position: " & i & sCrLf
    i = InStrR(sTarget, "String")
    s = s & "i = InStrR(sTarget, ""String"")        ' Found at position: " & i & sCrLf
    ' InStr can't use default position if Compare argument given
    i = InStr(1, sTarget, "String", 1)
    s = s & "i = InStr(1, sTarget, ""String"", 1)   ' Found at position: " & i & sCrLf
    ' InStrR can use default position if Compare argument given
    i = InStrR(sTarget, "String", 1)
    s = s & "i = InStrR(sTarget, ""String"", 1)     ' Found at position: " & i & sCrLf
    i = InStr(5, sTarget, "string", 1)
    s = s & "i = InStr(5, sTarget, ""string"", 1)   ' Found at position: " & i & sCrLf
    i = InStrR(42, sTarget, "String", 1)
    s = s & "i = InStrR(42, sTarget, ""String"", 1) ' Found at position: " & i & sCrLf
    i = InStrR(sTarget, "Ztring")
    s = s & "i = InStrR(sTarget, ""Ztring"")        ' Found at position: " & i & sCrLf
   
    txtTest = s
    
End Sub

Private Sub cmdParamArray_Click()
    Dim s As String
    s = s & "AddEmUp(7, 9.4, ""24"")  = "
    s = s & AddEmUp(7, 9.4, "24") & sCrLf
    s = s & "AddEmUp(, 9.4, , ""24"") = "
    s = s & AddEmUp(, 9.4, , "24") & sCrLf
    s = s & "AddEmUp(7, ""24"")       = "
    s = s & AddEmUp(7, "24") & sCrLf
    BugMessage s
    txtTest = s
End Sub

Private Sub cmdSA_Click()
    Dim va As Variant
    Dim aiInOut() As Integer
    ReDim Preserve aiInOut(1 To 4, 1 To 4) As Integer
    Dim asOut() As String
    Dim x As Integer, y As Integer, s As String
    s = s & "Before:" & sCrLf & _
            "aiInOut(" & LBound(aiInOut) & " To " & UBound(aiInOut, 1) & ", " & _
                         LBound(aiInOut, 2) & " To " & UBound(aiInOut, 2) & ") As " & _
                         TypeName(aiInOut(LBound(aiInOut, 1), LBound(aiInOut, 2))) & sCrLf
    For x = LBound(aiInOut, 1) To UBound(aiInOut, 1)
        For y = LBound(aiInOut, 2) To UBound(aiInOut, 2)
            aiInOut(x, y) = x * y
            s = s & CStr(aiInOut(x, y)) & " "
        Next
        s = s & sCrLf
    Next
    BugMessage s
    va = TestSA(aiInOut(), asOut())
    s = s & "After:" & sCrLf & _
            "aiInOut(" & LBound(aiInOut, 1) & " To " & UBound(aiInOut, 1) & ", " & _
                         LBound(aiInOut, 2) & " To " & UBound(aiInOut, 2) & ") As " & _
                         TypeName(aiInOut(LBound(aiInOut, 1), LBound(aiInOut, 2))) & sCrLf
    For x = LBound(aiInOut, 1) To UBound(aiInOut, 1)
        For y = LBound(aiInOut, 2) To UBound(aiInOut, 2)
            s = s & CStr(aiInOut(x, y)) & " "
        Next
        s = s & sCrLf
    Next
    s = s & "asOut(" & LBound(asOut()) & " To " & UBound(asOut()) & ") As " & _
            TypeName(asOut(LBound(asOut))) & sCrLf
    For x = LBound(asOut) To UBound(asOut)
        s = s & CStr(asOut(x)) & " "
    Next
    s = s & sCrLf
    s = s & "va(" & LBound(va) & " To " & UBound(va) & ") As " & _
            TypeName(va(LBound(va))) & sCrLf
    For x = LBound(va) To UBound(va)
        s = s & CStr(va(x)) & " "
    Next
    BugMessage s
    txtTest = s
    
End Sub

Private Sub cmdVariant_Click()
    Dim vRet As Variant, vIn As Variant, vInOut As Variant, vOut As Variant
    Dim s As String, sIn As String
    Dim obj As Object
    txtTest = "Send me in"
    vIn = cmdWin32
    vIn = "Send me in"
    sIn = "Send me in"
    vInOut = "I'm going in..."
    s = s & "Before: " & sCrLf & _
            "   In parameter: " & vIn & sCrLf & _
            "   In/Out parameter: " & vInOut & sCrLf & _
            "   Out parameter: " & vOut & sCrLf & _
            "   Return value: " & vRet & sCrLf
    vRet = TestVariant(sIn, vInOut, vOut)
    s = s & "After: " & sCrLf & _
            "   In parameter: " & vIn & sCrLf & _
            "   In/Out parameter: " & vInOut & sCrLf & _
            "   Out parameter: " & vOut & sCrLf & _
            "   Return value: " & vRet & sCrLf
    BugMessage s
    txtTest = s
End Sub

Private Sub cmdBits_Click()
    Dim dw As Long, w As Integer, r As Single, d As Double
    Dim c As Currency, s As String, i As Integer
    Dim pl As Long, PI As Long, pr As Long, pd As Long
    Dim pc As Long, ps As Long, psz As Long
    Dim sOutput As String
    sOutput = ""

    w = &HABCD
    w = &HFFFF
    dw = &HFEDCBA98
    dw = &HFFFF0000
    r = 1.23456789
    d = 9.87654321
    c = 999.99
    s = "Test"

    Dim bHi As Integer, bLo As Integer
    Dim wHi As Integer, wLo As Integer
    Dim wPack  As Integer, dwPack  As Long
    Dim wRShift As Integer, wLShift As Integer
    Dim dwRShift As Long, dwLShift As Long

    sOutput = "VB Versions" & sCrLf
    bLo = LoByte(w)
    sOutput = sOutput & "Low byte of word (" & Hex$(w) & "): " & Hex$(bLo) & sCrLf
    bHi = HiByte(w)
    sOutput = sOutput & "High byte of word (" & Hex$(w) & "): " & Hex$(bHi) & sCrLf
    wPack = MakeWord(bLo, bHi)
    sOutput = sOutput & "Packed hi/lo bytes of word: " & Hex$(wPack) & sCrLf
    wLo = LoWord(dw)
    sOutput = sOutput & "Low Word of DWord (" & Hex$(dw) & "): " & Hex$(wLo) & sCrLf
    wHi = HiWord(dw)
    sOutput = sOutput & "High Word of DWord (" & Hex$(dw) & "): " & Hex$(wHi) & sCrLf
    dwPack = MakeDWord(wHi, wLo)
    sOutput = sOutput & "Packed hi/lo Word of DWord: " & Hex$(dwPack) & sCrLf

    
    sOutput = sOutput & "Word shifted right" & sCrLf
    For i = 0 To 15
        sOutput = sOutput & Hex$(RShiftWord(w, i)) & "  "
    Next
    sOutput = sOutput & sCrLf
    sOutput = sOutput & "Word shifted left" & sCrLf
    For i = 0 To 15
        sOutput = sOutput & Hex$(LShiftWord(w, i)) & "  "
    Next
    sOutput = sOutput & sCrLf
    sOutput = sOutput & "DWord shifted right C" & sCrLf
    For i = 0 To 31
        sOutput = sOutput & Hex$(RShiftDWord(dw, i)) & "  "
    Next
    sOutput = sOutput & sCrLf
    sOutput = sOutput & "DWord shifted left C" & sCrLf
    For i = 0 To 31
        sOutput = sOutput & Hex$(LShiftDWord(dw, i)) & "  "
    Next
    sOutput = sOutput & sCrLf
    txtTest.Text = sOutput

End Sub

Private Sub cmdWin32_Click()

    Dim i As Integer, s As String, sVal As String
    Dim sName As String, sFullName As String
    Dim c As Long, f As Boolean
    Dim iDir As Long, iBase As Long, iExt As Long
    Dim vDir As Variant, vBase As Variant, vExt As Variant
       
    ''@B SearchDirs2
    vDir = Environ$("INCLUDE")
    'sFullName = SearchDirs("WINDOWS.H", , vDir)
    sFullName = SearchDirs("WINDOWS.H", , Environ$("INCLUDE"))
    'sFullName = SearchDirs("WINDOWS.H", , Environ("INCLUDE"))
    ''@E SearchDirs2
    If sFullName <> sEmpty Then
        s = s & "File found in: " & sFullName & sCrLf
    Else
        s = s & "File not found" & sCrLf
    End If
    
   
    sName = "nosuch.txt"
    ' Test GetFullPathName
    s = s & sCrLf & "Test GetFullPathName" & sCrLf & sCrLf
    ''@B GetFullPathName
    Dim sBase As String, pBase As Long
    sFullName = String$(cMaxPath, 0)
    c = GetFullPathName(sName, cMaxPath, sFullName, pBase)
    sFullName = Left$(sFullName, c)
    If c Then
        s = s & "Full name: " & sFullName & sCrLf
    ''@E GetFullPathName
#If Win32 = 0 Then
        ' Fails 32-bit because pointer is to temporary Unicode string
        sBase = String$(20, 0)
        Call lstrcpyFromLp(sBase, pBase)
        sBase = StrZToStr(sBase)
        s = s & "Name: " & sBase & sCrLf
#End If
    End If
 
    s = s & sCrLf & "Test GetFullPath with invalid argument" & sCrLf & sCrLf
    sFullName = GetFullPath("", vBase, vExt, vDir)
    If sFullName = sEmpty Then
        s = s & "Failed: Error " & Err.LastDllError & sCrLf
    Else
        s = s & "File: " & sFullName & sCrLf
    End If

    ''@B GetFullPath
    s = s & sCrLf & "Test GetFullPath with all optional arguments" & sCrLf & sCrLf
    sFullName = GetFullPath(sName, vBase, vExt, vDir)
    If sFullName <> sEmpty Then
        s = s & "Relative file: " & sName & sCrLf
        s = s & "Full name: " & sFullName & sCrLf
        s = s & "File: " & Mid$(sFullName, vBase) & sCrLf
        s = s & "Extension: " & Mid$(sFullName, vExt) & sCrLf
        s = s & "Base name: " & Mid$(sFullName, vBase, _
                                     vExt - vBase) & sCrLf
        s = s & "Drive: " & Left$(sFullName, vDir - 1) & sCrLf
        s = s & "Directory: " & Mid$(sFullName, vDir, _
                                     vBase - vDir) & sCrLf
        s = s & "Path: " & Left$(sFullName, vBase - 1) & sCrLf
    Else
        s = s & "Invalid name: " & sName
    End If
    ''@E GetFullPath
    
    s = s & sCrLf & "Test GetFullPath with some optional arguments" & sCrLf & sCrLf
    sFullName = GetFullPath(sName, vBase, vExt)
    If sFullName <> sEmpty Then
        s = s & "Relative file: " & sName & sCrLf
        s = s & "Full name: " & sFullName & sCrLf
        s = s & "File: " & Mid$(sFullName, vBase) & sCrLf
        s = s & "Extension: " & Mid$(sFullName, vExt) & sCrLf
        s = s & "Base name: " & Mid$(sFullName, vBase, _
                                     vExt - vBase) & sCrLf
        s = s & "Path: " & Left$(sFullName, vBase - 1) & sCrLf
    Else
        s = s & "Invalid name: " & sName
    End If
    
    s = s & sCrLf & "Test GetFullPath with no optional arguments" & sCrLf & sCrLf
    sFullName = GetFullPath(sName)
    If sFullName <> sEmpty Then
        s = s & "Relative file: " & sName & sCrLf
        s = s & "Full name: " & sFullName & sCrLf
    Else
        s = s & "Invalid name: " & sName
    End If

    ' Test SearchPath
    s = s & sCrLf & "Test SearchPath" & sCrLf & sCrLf
    sName = "vb.hlp"
    sFullName = String$(cMaxPath, 0)
    i = SearchPath(vbNullString, sName, vbNullString, cMaxPath, sFullName, pBase)
    sFullName = Left$(sFullName, i)
    If i Then
        s = s & "File " & sName & " found in: " & sFullName & sCrLf
#If Win32 = 0 Then
        ' Fails 32-bit because pointer is to temporary Unicode string
        sBase = String$(20, 0)
        Call lstrcpyFromLp(sBase, pBase)
        sBase = StrZToStr(sBase)
        s = s & "Name: " & sBase & sCrLf
#End If
    Else
        s = s & "File " & sName & " not found" & sCrLf
    End If
    
    s = s & sCrLf & "Test SearchDirs" & sCrLf & sCrLf
    ''@B SearchDirs1
    sName = "vb.hlp"
    sFullName = SearchDirs(sName, sEmpty, sEmpty, vBase, vExt, vDir)
    If sFullName <> sEmpty Then
        s = s & "Found file " & sName
        s = s & " in " & sFullName & sCrLf
        s = s & "File: " & Mid$(sFullName, vBase) & sCrLf
        s = s & "Extension: " & Mid$(sFullName, vExt) & sCrLf
        s = s & "Base name: " & Mid$(sFullName, vBase, _
                                     vExt - vBase) & sCrLf
        s = s & "Drive: " & Left$(sFullName, vDir - 1) & sCrLf
        s = s & "Directory: " & Mid$(sFullName, vDir, _
                                     vBase - vDir) & sCrLf
        s = s & "Path: " & Left$(sFullName, vBase - 1) & sCrLf
    Else
        s = s & "File " & sName & " not found" & sCrLf
    End If
    ''@E SearchDirs1

    sName = "hardcore.frm"
    sFullName = SearchDirs(sName, Empty, Empty)
    If sFullName <> sEmpty Then
        s = s & "File " & sName & " found in: " & sFullName & sCrLf
    Else
        s = s & "File " & sName & " not found" & sCrLf
    End If
    
    sName = "calc.exe"
    sFullName = SearchDirs(sName)
    If sFullName <> sEmpty Then
        s = s & "File " & sName & " found in: " & sFullName & sCrLf
    Else
        s = s & "File " & sName & " not found" & sCrLf
    End If
    
    sName = "gdi.exe"
    sFullName = SearchDirs(sName)
    If sFullName <> sEmpty Then
        s = s & "File " & sName & " found in: " & sFullName & sCrLf
    Else
        s = s & "File " & sName & " not found" & sCrLf
    End If

    sName = "find.exe"
    sFullName = SearchDirs(sName)
    If sFullName <> sEmpty Then
        s = s & "File " & sName & " found in: " & sFullName & sCrLf
    Else
        s = s & "File " & sName & " not found" & sCrLf
    End If

    ''@B SearchDirs2
    vDir = Environ$("INCLUDE")
    sFullName = SearchDirs("WINDOWS.H", , vDir)
    sFullName = SearchDirs("WINDOWS.H", , Environ$("INCLUDE"))
    sFullName = SearchDirs("WINDOWS.H", , Environ("INCLUDE"))
    ''@E SearchDirs2
    If sFullName <> sEmpty Then
        s = s & "File found in: " & sFullName & sCrLf
    Else
        s = s & "File not found" & sCrLf
    End If
    
    ''@B SearchDirs3
    sName = "DEBUG.BAS"
    sFullName = SearchDirs(sName, ".")
    ''@E SearchDirs3
    If sFullName <> sEmpty Then
        s = s & "File found in: " & sFullName & sCrLf
    Else
        s = s & "File " & sName & " not found" & sCrLf
    End If
    
    ''@B SearchDirs4
    sName = "EDIT"
    Dim asExts(1 To 4) As String
    asExts(1) = ".EXE": asExts(2) = ".COM"
    asExts(3) = ".BAT": asExts(4) = ".PIF"
    For i = 1 To 4
        sFullName = SearchDirs(sName, asExts(i))
        If sFullName <> sEmpty Then Exit For
    Next
    ''@E SearchDirs4
    If sFullName <> sEmpty Then
        s = s & "File found in: " & sFullName & sCrLf
    Else
        s = s & "File " & sName & " not found" & sCrLf
    End If

    ' Test GetDiskFreeSpace and GetDriveType
    s = s & sCrLf & "Test GetDiskFreeSpace and GetDriveType" & sCrLf & sCrLf
    Dim iSectors As Long, iBytes As Long
    Dim iFree As Long, iTotal As Long
    Dim rFree As Double, rTotal As Double
    sName = "%:\"
    Dim sTab As String
    For i = 1 To 26
        sVal = Chr$(i + Asc("A") - 1)
        Mid$(sName, 1, 1) = sVal

        ''@B CallGetDriveType
        c = GetDriveType(sName)
        s = s & "Disk " & sVal & " type: "
        s = s & Choose(c + 1, "Unknown", "Invalid", "Floppy ", _
                              "Hard   ", "Network", "CD-ROM ", "RAM    ")
        ''@E CallGetDriveType

        ''@B CallGetDiskFreeSpace
        f = GetDiskFreeSpace(sName, iSectors, iBytes, iFree, iTotal)
        rFree = iSectors * iBytes * CDbl(iFree)
        rTotal = iSectors * iBytes * CDbl(iTotal)
        If f Then
            s = s & " with " & Format$(rFree, "#,###,###,##0")
            s = s & " free from " & Format$(rTotal, "#,###,###,##0") & sCrLf
        ''@E CallGetDiskFreeSpace
        Else
            s = s & sCrLf
        End If
    Next
    ' txtTest.Text = s

    ' Test GetTempPath and GetTempFileName
    s = s & sCrLf & "Test GetTempPath and GetTempFileName" & sCrLf & sCrLf
    c = cMaxPath
    sFullName = String$(c, 0)
    c = GetTempPath(c, sFullName)
    sFullName = Left$(sFullName, c)
    s = s & "Temp Path: " & sFullName & sCrLf
    ''@B GetTempFileName
    sFullName = String$(cMaxPath, 0)
    Call GetTempFileName(".", "HC", 0, sFullName)
    sFullName = Left$(sFullName, InStr(sFullName, sNullChr) - 1)
    ''@E GetTempFileName
    s = s & "Temp File: " & sFullName & sCrLf
    
    s = s & sCrLf & "Test GetTempFile and GetTempDir" & sCrLf & sCrLf
     ''@B GetTempFile1
    ' Get temp file for current directory
    sFullName = GetTempFile(".", "HC")
    ''@E GetTempFile1
    s = s & "Temp file in current directory: " & sFullName & sCrLf
    ''@B GetTempFile2
    ' Get temp file for TEMP directory
    sFullName = GetTempFile(GetTempDir(), "HC")
    ''@E GetTempFile2
    s = s & "Temp file in TEMP directory: " & sFullName & sCrLf

   ' Test GetLogicalDrives
    s = s & sCrLf & "Test GetLogicalDrives" & sCrLf & sCrLf
    sVal = VBGetLogicalDrives()
    s = s & "Drives    ABCDEFGHIJKLMNOPQRSTUVWXYZ" & sCrLf
    s = s & "Drives    " & sVal & sCrLf

    On Error Resume Next
    Kill "~HC*.tmp"
    Kill "HC*.tmp"
    On Error GoTo 0
    
    BugMessage s
    txtTest.Text = s
    
End Sub

Private Sub cmdExit_Click()
    Unload Me
End Sub



