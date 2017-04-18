VERSION 2.00
Begin Form Perf1 
   BackColor       =   &H00C0C0C0&
   Caption         =   "Please WAIT...."
   ClientHeight    =   1470
   ClientLeft      =   6000
   ClientTop       =   2940
   ClientWidth     =   3090
   Height          =   1875
   Left            =   5940
   LinkTopic       =   "Form2"
   ScaleHeight     =   1470
   ScaleWidth      =   3090
   Top             =   2595
   Width           =   3210
   Begin Init Init1 
      Application     =   ""
      Filename        =   ""
      Height          =   420
      Left            =   240
      Parameter       =   ""
      Top             =   360
      Value           =   ""
      Width           =   420
   End
End
Dim TimeData(0 To 2, 0 To 100)         As Long
Dim Ent$(0 To 100)
Declare Function GetPrivateProfileString Lib "Kernel" (ByVal lpApplicationName As String, lpKeyName As Any, ByVal lpDefault As String, ByVal lpReturnedString As String, ByVal nSize As Integer, ByVal lpFileName As String) As Integer

Sub Form_Load ()
Dim i As Integer, b    As Integer, j As Integer
Section$ = "TEST"
visible = True
Refresh
FileIni$ = "C:\TEST.INI"
For i = 0 To 100
    Ent$(i) = Format(i, "0")
    PutIni Section$, Ent$(i), Ent$(i), FileIni$
Next i
Init1.Application = "Test"
For b = 0 To 1
For i = 0 To 2 'Method
For j = 0 To 100
    
    Select Case i
    Case 0
        Buffer$ = String(128, " ")
        rc% = GetPrivateProfileString(Section$, Ent$(j), "", Buffer$, 4096, FileIni$)
        A$ = Left$(Buffer$, rc%)
    Case 1
        A$ = vbGetIni(Section$, Ent$(j), FileIni$)
    Case 2
       Init1.Parameter = Ent$(j)
       A$ = Init1.Value
    End Select
    If b = 1 Then TimeData(i, j) = STOPWATCH_Time()
Next j
Next i
Next b
T$ = Chr$(9)
fno = FreeFile
Open App.Path + "\Perf1.TXT" For Output As #1
For j = 1 To 100
    Print #fno, TimeData(0, j) - TimeData(0, j - 1); T$, TimeData(1, j) - TimeData(1, j - 1); T$, TimeData(2, j) - TimeData(2, j - 1)
Next j
Close
rc% = Shell("Notepad " + App.Path + "\Perf1.TXT", 3)
MsgBox "Timing complete"
End
End Sub

