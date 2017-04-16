VERSION 2.00
Begin Form Form1 
   BackColor       =   &H00C0C0C0&
   Caption         =   "Host Agent"
   ClientHeight    =   2685
   ClientLeft      =   780
   ClientTop       =   1965
   ClientWidth     =   5700
   Height          =   3090
   Icon            =   HOST.FRX:0000
   Left            =   720
   LinkTopic       =   "Form1"
   ScaleHeight     =   2685
   ScaleWidth      =   5700
   Top             =   1620
   Width           =   5820
   Begin HScrollBar HScroll1 
      Height          =   255
      Left            =   3120
      Min             =   300
      TabIndex        =   7
      Top             =   1080
      Value           =   1000
      Width           =   2415
   End
   Begin ComboBox Queries 
      Height          =   300
      Left            =   0
      Style           =   2  'Dropdown List
      TabIndex        =   6
      Top             =   0
      Width           =   5415
   End
   Begin TextBox Query 
      Height          =   975
      Left            =   120
      MultiLine       =   -1  'True
      TabIndex        =   3
      Top             =   1680
      Width           =   5415
   End
   Begin Frame Frame1 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Signals to Monitor"
      Height          =   1095
      Left            =   120
      TabIndex        =   0
      Top             =   240
      Width           =   2775
      Begin CheckBox Check1 
         BackColor       =   &H00C0C0C0&
         Caption         =   "MAPI Agent"
         Height          =   255
         Left            =   120
         TabIndex        =   2
         Top             =   720
         Width           =   1815
      End
      Begin CheckBox cbRASAgent 
         BackColor       =   &H00C0C0C0&
         Caption         =   "RAS Agent: C:\Newquery"
         Height          =   255
         Left            =   120
         TabIndex        =   1
         Top             =   360
         Width           =   2535
      End
   End
   Begin Timer Timer1 
      Interval        =   1000
      Left            =   5280
      Top             =   1320
   End
   Begin Label Label1 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Fast -----------------------Slow"
      Height          =   195
      Index           =   1
      Left            =   3120
      TabIndex        =   5
      Top             =   840
      Width           =   2220
   End
   Begin Image HeartBeat 
      Height          =   480
      Left            =   3840
      Picture         =   HOST.FRX:0302
      Top             =   240
      Width           =   480
   End
   Begin Label Label1 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Current Query"
      Height          =   195
      Index           =   0
      Left            =   120
      TabIndex        =   4
      Top             =   1440
      Width           =   1185
   End
End
Const Incoming$ = "C:\RASQUERY"
Const Outgoing$ = "C:\RAS_RET"

Sub Form_Load ()
On Error Resume Next
MkDir Incoming$
MkDir Outgoing$
cbRASAgent.Caption = "RAS Agent: " + Incoming$
On Error GoTo 0
End Sub

Sub HScroll1_Change ()
Timer1.Interval = HSCROll1
End Sub

Sub ProcessQuery (ByVal Fname$)
Dim DB As database, OutDB  As database
Const DB_LANG_GENERAL = ";LANGID=0x0809;CP=1252;COUNTRY=0"
If Dir(App.Path + "\Host.MDB") = "" Then
    MsgBox "This application must run in the same directort as HOST.MDB"
    Exit Sub
End If
Set DB = OpenDatabase(App.Path + "\Host.MDB")
'On Error Resume Next
Queries.AddItem "[" + Format(FileDateTime(Fname$), "YYMMDD HHNNSS") + "] " + Fname$, 0
Queries.ListIndex = 0
If Dir$(Fname$) = "" Or Fname = "" Then Exit Sub


fno = FreeFile
Open Fname$ For Input As #fno
While Not EOF(fno)
    Line Input #fno, A$
    If Left$(A$, 1) = "<" Then Outfile$ = Mid$(A$, 2)
    If Left$(A$, 7) = ">SELECT" Then Query = Mid$(A$, 2)
    If Left$(A$, 1) = "=" Then TableName$ = Mid$(A$, 2)
    If Left$(A$, 1) = "@" Then ZipName$ = Mid$(A$, 2)
    If Left$(A$, 1) = "!" Then GoSub ExecuteQuery
Wend
Close fno
GoSub ExecuteQuery

    If Len(ZipName$) > 0 Then
        fbatch = FreeFile
        Batchfile$ = Outgoing$ + "\ZIPMDB.BAT"
        ZipName$ = Outgoing$ + "\" + ZipName$
        Open Batchfile$ For Output As #fbatch
            Print #fbatch, "PKZIP -m " + ZipName$ + " " + OutPath$
            Print #fbatch, "DEL " + Batchfile$
        Close fbatch
        If Shell(Batchfile$, 3) Then
            While Dir$(Batchfile$) <> ""
                DoEvents
            Wend
        End If
    End If

Kill Fname$  'Remove File to signal completion
On Error GoTo 0
Exit Sub

ExecuteQuery:
On Error GoTo 0
'Validate parameters
FromAt% = InStr(Query, " FROM ")
OutPath$ = Outgoing$ + "\" + Outfile$
If FromAt% = 0 Then
    Query = "" 'Invalid Format
Else
    Query = Left$(Query, FromAt%) + " Into [" + TableName$ + "] In '" + OutPath$ + "' " + Mid$(Query, FromAt%)
End If

If Len(Outfile$) > 0 And Len(Query) > 0 And Len(TableName$) > 0 Then
    If Dir$(OutPath$) = "" Then
        Set OutDB = CreateDatabase(OutPath$, DB_LANG_GENERAL)
        OutDB.Close
    End If
    On Error Resume Next
    DB.Execute Query
    On Error GoTo 0
End If
Return
End Sub

Sub ProcessQueue ()
'Only the RAS check is done
'MAPI could drop the files in the same location
'to serve as a signal
If cbRASAgent.Value <> 0 Then 'Check RAS
    A$ = Dir$(Incoming$ + "\*.QRY")
    While Len(A$) > 0
        NextA$ = Dir$
        ProcessQuery Incoming$ + "\" + A$
        A$ = NextA$
    Wend
End If
End Sub

Sub Timer1_Timer ()
Static Active%
HeartBeat.Visible = Not HeartBeat.Visible
If Active% Then Exit Sub
Active% = True
ProcessQueue
Active% = False
End Sub

