VERSION 4.00
Begin VB.Form IntroRDO 
   Caption         =   "Introduction to RDO from MSDN Library"
   ClientHeight    =   6330
   ClientLeft      =   1485
   ClientTop       =   1695
   ClientWidth     =   8610
   Height          =   6735
   Icon            =   "IntroRDO.frx":0000
   Left            =   1425
   LinkTopic       =   "Form1"
   ScaleHeight     =   6330
   ScaleWidth      =   8610
   Top             =   1350
   Width           =   8730
   Begin VB.Frame Frame4 
      Caption         =   "Timing Results"
      Height          =   1695
      Left            =   3960
      TabIndex        =   23
      Top             =   4080
      Width           =   4215
      Begin VB.CommandButton pbViewLog 
         Caption         =   "&View Log File"
         Height          =   255
         Left            =   3000
         TabIndex        =   28
         Top             =   1320
         Width           =   1095
      End
      Begin VB.TextBox tbTimings 
         Height          =   285
         Left            =   1200
         TabIndex        =   27
         Text            =   "0"
         Top             =   1320
         Width           =   495
      End
      Begin VB.CheckBox cbLogToFile 
         Caption         =   "Log to File"
         Height          =   255
         Left            =   1800
         TabIndex        =   25
         Top             =   1320
         Width           =   1095
      End
      Begin VB.ListBox lstTimes 
         Height          =   1005
         Left            =   120
         TabIndex        =   24
         Top             =   240
         Width           =   3975
      End
      Begin VB.Label Label3 
         Caption         =   "Timing Cycles:"
         Height          =   255
         Left            =   120
         TabIndex        =   26
         Top             =   1320
         Width           =   1095
      End
   End
   Begin VB.Frame Frame3 
      Caption         =   "Results"
      Height          =   1695
      Left            =   0
      TabIndex        =   20
      Top             =   4080
      Width           =   3855
      Begin VB.ListBox LstListBox 
         Height          =   1200
         Left            =   120
         TabIndex        =   21
         Top             =   240
         Width           =   3615
      End
   End
   Begin VB.Frame Frame2 
      Caption         =   "Recordset Created"
      Height          =   2655
      Left            =   0
      TabIndex        =   14
      Top             =   1320
      Width           =   2535
      Begin VB.CommandButton PBResetoPTIONS 
         Caption         =   "&Reset Options"
         Height          =   255
         Left            =   360
         TabIndex        =   22
         Top             =   1920
         Width           =   1935
      End
      Begin VB.ComboBox lstLockType 
         Height          =   300
         Left            =   120
         Sorted          =   -1  'True
         Style           =   2  'Dropdown List
         TabIndex        =   19
         Top             =   2280
         Width           =   2175
      End
      Begin VB.ComboBox lstType 
         Height          =   300
         Left            =   120
         Sorted          =   -1  'True
         Style           =   2  'Dropdown List
         TabIndex        =   16
         Top             =   240
         Width           =   2175
      End
      Begin VB.ListBox lstOptions 
         Height          =   1005
         Left            =   120
         MultiSelect     =   2  'Extended
         Sorted          =   -1  'True
         TabIndex        =   15
         Top             =   720
         Width           =   2175
      End
   End
   Begin VB.Frame v 
      Caption         =   "Data Base Source"
      Height          =   1335
      Left            =   0
      TabIndex        =   3
      Top             =   0
      Width           =   8175
      Begin VB.ComboBox lstPrompt 
         Height          =   315
         Left            =   1320
         Sorted          =   -1  'True
         Style           =   2  'Dropdown List
         TabIndex        =   17
         Top             =   960
         Width           =   2655
      End
      Begin VB.CommandButton Command3 
         Caption         =   "&File"
         Height          =   255
         Left            =   4440
         TabIndex        =   13
         Top             =   240
         Width           =   975
      End
      Begin VB.OptionButton DBObject 
         Caption         =   "&RDO"
         Height          =   255
         Index           =   1
         Left            =   5520
         TabIndex        =   12
         Top             =   960
         Value           =   -1  'True
         Width           =   735
      End
      Begin VB.OptionButton DBObject 
         Caption         =   "&DAO"
         Height          =   255
         Index           =   0
         Left            =   5520
         TabIndex        =   11
         Top             =   720
         Width           =   735
      End
      Begin VB.CheckBox cbDBExclusive 
         Caption         =   "E&xclusive"
         Height          =   255
         Left            =   5520
         TabIndex        =   10
         Top             =   240
         Width           =   1095
      End
      Begin VB.CheckBox cbDBReadOnly 
         Caption         =   "Read &Only"
         Height          =   195
         Index           =   0
         Left            =   5520
         TabIndex        =   9
         Top             =   480
         Value           =   1  'Checked
         Width           =   1095
      End
      Begin VB.CommandButton Command2 
         Caption         =   "&ODBC"
         Height          =   255
         Left            =   4440
         TabIndex        =   8
         Top             =   600
         Width           =   975
      End
      Begin VB.TextBox DBConnect 
         Height          =   285
         Left            =   840
         TabIndex        =   6
         Text            =   "Text2"
         Top             =   600
         Width           =   3495
      End
      Begin VB.TextBox DBName 
         Height          =   285
         Left            =   840
         TabIndex        =   4
         Text            =   "Text2"
         Top             =   240
         Width           =   3495
      End
      Begin MSComDlg.CommonDialog CommonDialog1 
         Left            =   4800
         Top             =   720
         _Version        =   65536
         _ExtentX        =   847
         _ExtentY        =   847
         _StockProps     =   0
      End
      Begin VB.Label Label2 
         Caption         =   "Prompt (RDO)"
         Height          =   255
         Left            =   120
         TabIndex        =   18
         Top             =   960
         Width           =   1215
      End
      Begin VB.Label Label1 
         Caption         =   "Connect"
         Height          =   255
         Index           =   1
         Left            =   120
         TabIndex        =   7
         Top             =   600
         Width           =   1335
      End
      Begin VB.Label Label1 
         Caption         =   "Name"
         Height          =   255
         Index           =   0
         Left            =   120
         TabIndex        =   5
         Top             =   240
         Width           =   1335
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "Query "
      Height          =   2655
      Left            =   2640
      TabIndex        =   0
      Top             =   1320
      Width           =   5535
      Begin VB.CommandButton Command1 
         Caption         =   "E&xecute"
         Height          =   375
         Left            =   3960
         TabIndex        =   2
         Top             =   2160
         Width           =   1455
      End
      Begin VB.TextBox SQLText 
         Height          =   1815
         Left            =   120
         MultiLine       =   -1  'True
         ScrollBars      =   2  'Vertical
         TabIndex        =   1
         Top             =   240
         Width           =   5295
      End
   End
End
Attribute VB_Name = "IntroRDO"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit
Const AccessDatabase$ = "D:\VB4\Biblio.mdb"
Const CountSQL$ = "Select count(*) AS Result from [All Titles] where Instr(Title,""and"")"
Sub LOCALRDA_Access(ByVal DBName$, ByVal SQLQuery$, Optional ByVal DBConnect, Optional ByVal ReadOnly)
Dim DB As rdo.rdoConnection
Dim Env As rdo.rdoEnvironment
Dim RS As rdo.rdoResultset
End Sub
Private Sub Command1_Click()
AddNewTime -2
If DBObject(0) Then
'    VB3_FillLstFromSQL LstListBox, (DBName), SQLText, DBConnect, ReadOnly, ThisRSType(), ThisRSOptions()
    DAO_FillLstFromSQL _
        LstControl:=LstListBox, _
        DBName:=DBName, _
        DBConnect:=DBConnect, _
        SQLQuery:=SQLText, _
        RSType:=This_RSType%(), _
        Options:=This_Options(), _
        Exclusive:=cbDBExclusive, _
        ReadOnly:=cbDBReadOnly, _
        cycles:=tbTimings
 ElseIf DBObject(1) Then
    RDO_FillLstFromSQL _
        LstControl:=LstListBox, _
        DBName:=DBName, _
        DBConnect:=DBConnect, _
        SQLQuery:=SQLText, _
        RSType:=This_RSType%(), _
        Options:=This_Options(), _
        LockType:=This_LockTYpe%(), _
        ReadOnly:=cbDBReadOnly, _
        cycles:=tbTimings
 Else
 End If
AddNewTime True
End Sub
Private Function This_LockTYpe%()
This_LockTYpe = lstLockType.ItemData(lstLockType.ListIndex)
End Function
Private Function This_RSType%()
This_RSType = lstType.ItemData(lstType.ListIndex)

End Function
Private Function This_Options()
Dim i%, Result%
For i% = 0 To lstOptions.ListCount - 1
    If lstOptions.Selected(i%) Then
        Result% = Result% + lstOptions.ItemData(i%)
    End If
Next i%
If Result% <> 0 Then This_Options = Result%

End Function
Function This_RDOPrompt%()
This_RDOPrompt% = lstPrompt.ItemData(lstPrompt.ListIndex)
End Function
Private Sub Command2_Click()
Dim ret&
DBConnect = "ODBC;"
ret& = Shell("ODBCAdm.exe", VBA.vbNormalFocus)
End Sub

Private Sub Command3_Click()
On Error GoTo File_Error
CommonDialog1.CancelError = True
CommonDialog1.filename = "*.mdb"
CommonDialog1.Flags = MSComDlg.cdlOFNFileMustExist _
    + MSComDlg.cdlOFNHideReadOnly _
    + MSComDlg.cdlOFNExplorer
CommonDialog1.Action = 1
DBName = CommonDialog1.filename
DBConnect = ""
File_Exit:
On Error GoTo 0
Exit Sub
File_Error:

Resume File_Exit
End Sub

Private Sub DBObject_Click(Index As Integer)
Select Case Index
Case 0 'DAO
    lstPrompt.Enabled = False
    lstLockType.Enabled = False
    lstType.Clear
    lstType.AddItem "dbOpenTable"
    lstType.ItemData(lstType.NewIndex) = dbOpenTable
    lstType.AddItem "dbOpenSnapShot"
    lstType.ItemData(lstType.NewIndex) = dbOpenSnapshot
    lstType.AddItem "dbOpenDynaset"
    lstType.ItemData(lstType.NewIndex) = dbOpenDynaset
    lstType.ListIndex = 0
    lstOptions.Clear
    lstOptions.AddItem "dbSeeChanges"
    lstOptions.ItemData(lstOptions.NewIndex) = dao.dbSeeChanges
    lstOptions.AddItem "dbDenyWrite"
    lstOptions.ItemData(lstOptions.NewIndex) = dao.dbDenyWrite
    lstOptions.AddItem "dbForwardOnly"
    lstOptions.ItemData(lstOptions.NewIndex) = dao.dbForwardOnly
    lstOptions.AddItem "dbDenyRead"
    lstOptions.ItemData(lstOptions.NewIndex) = dao.dbDenyRead
    lstOptions.AddItem "dbAppendOnly"
    lstOptions.ItemData(lstOptions.NewIndex) = dao.dbAppendOnly
    lstOptions.AddItem "dbConsistent "
    lstOptions.ItemData(lstOptions.NewIndex) = dao.dbConsistent
    lstOptions.AddItem "dbInconsistent"
    lstOptions.ItemData(lstOptions.NewIndex) = dao.dbInconsistent
    lstOptions.AddItem "dbReadOnly"
    lstOptions.ItemData(lstOptions.NewIndex) = dao.dbReadOnly
    lstOptions.AddItem "dbSQLPassThrough"
    lstOptions.ItemData(lstOptions.NewIndex) = dao.dbSQLPassThrough

Case Else 'RDO
    lstPrompt.Enabled = True
    lstLockType.Enabled = True
    lstType.Clear
    lstType.AddItem "rdOpenKeyset"
    lstType.ItemData(lstType.NewIndex) = rdo.rdOpenKeyset
    lstType.AddItem "rdOpenStatic"
    lstType.ItemData(lstType.NewIndex) = rdo.rdOpenStatic
    lstType.AddItem "rdOpenDynamic"
    lstType.ItemData(lstType.NewIndex) = rdo.rdOpenDynamic
    lstType.AddItem "rdOpenForwardOnly"
    lstType.ItemData(lstType.NewIndex) = rdo.rdOpenForwardOnly

    lstType.ListIndex = 0
    lstOptions.Clear
    lstOptions.AddItem "rdAsyncEnable"
    lstOptions.ItemData(lstOptions.NewIndex) = rdAsyncEnable
    lstType.ListIndex = 0
End Select

End Sub

Private Sub Form_Load()
'Startup loads:
DBObject(0).Value = True
SQLText = "Select * from Authors;"
DBName = "Pubs"
DBConnect = "ODBC;Userid=sa;Password=;"

lstPrompt.Clear
lstPrompt.AddItem "rdDriverNoPrompt"
lstPrompt.ItemData(lstPrompt.NewIndex) = rdo.rdDriverNoPrompt
lstPrompt.AddItem "rdDriverPrompt"
lstPrompt.ItemData(lstPrompt.NewIndex) = rdo.rdDriverPrompt
lstPrompt.AddItem "rdDriverComplete"
lstPrompt.ItemData(lstPrompt.NewIndex) = rdo.rdDriverComplete
lstPrompt.AddItem "rdDriverComplete"
lstPrompt.ItemData(lstPrompt.NewIndex) = rdo.rdDriverCompleteRequired
lstPrompt.ListIndex = 0

lstLockType.Clear
lstLockType.AddItem "rdConcurLock"
lstLockType.ItemData(lstLockType.NewIndex) = rdo.rdConcurLock
lstLockType.AddItem "rdConcurReadOnly"
lstLockType.ItemData(lstLockType.NewIndex) = rdo.rdConcurReadOnly
lstLockType.AddItem "rdConcurRowver"
lstLockType.ItemData(lstLockType.NewIndex) = rdo.rdConcurRowver
lstLockType.AddItem "rdConcurValues"
lstLockType.ItemData(lstLockType.NewIndex) = rdo.rdConcurValues
lstLockType.ListIndex = 1 'Default
End Sub

Private Sub PBResetoPTIONS_Click()
Dim i%
For i% = 0 To lstOptions.ListCount - 1
    lstOptions.Selected(i%) = False
Next i%

End Sub

Private Sub pbViewLog_Click()
Dim rc&
rc& = Shell("Notepad IntroRDO.log", vbMaximizedFocus)
End Sub
