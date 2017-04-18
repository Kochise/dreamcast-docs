VERSION 4.00
Begin VB.Form VBDBForm 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "VBDB"
   ClientHeight    =   4368
   ClientLeft      =   1188
   ClientTop       =   1356
   ClientWidth     =   8316
   Height          =   4692
   Icon            =   "vbdbform.frx":0000
   Left            =   1140
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   ScaleHeight     =   364
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   693
   Top             =   1080
   Width           =   8412
   Begin VB.Frame FrameOpt 
      Caption         =   "Options"
      Height          =   975
      Left            =   4560
      TabIndex        =   24
      Top             =   120
      Width           =   3615
      Begin VB.OptionButton OptRead 
         Caption         =   "Read+Write"
         Enabled         =   0   'False
         Height          =   255
         Index           =   1
         Left            =   240
         TabIndex        =   27
         Top             =   600
         Width           =   1215
      End
      Begin VB.OptionButton OptRead 
         Caption         =   "Read Only"
         Enabled         =   0   'False
         Height          =   255
         Index           =   0
         Left            =   240
         TabIndex        =   26
         Top             =   360
         Value           =   -1  'True
         Width           =   1095
      End
      Begin VB.TextBox Iterations 
         Alignment       =   1  'Right Justify
         Enabled         =   0   'False
         Height          =   285
         Left            =   2760
         TabIndex        =   25
         Text            =   "3"
         Top             =   360
         Width           =   495
      End
      Begin VB.Label LabIteration 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         Caption         =   "Iterations:"
         Enabled         =   0   'False
         Height          =   195
         Left            =   1920
         TabIndex        =   28
         Top             =   360
         Width           =   690
      End
   End
   Begin VB.CommandButton ComTest 
      Caption         =   "Begin Test"
      Enabled         =   0   'False
      Height          =   495
      Left            =   5760
      TabIndex        =   21
      Top             =   3720
      Width           =   1335
   End
   Begin VB.Frame FrameTD 
      Caption         =   "Select Target Data"
      Enabled         =   0   'False
      Height          =   2055
      Left            =   120
      TabIndex        =   16
      Top             =   2160
      Width           =   4095
      Begin VB.ListBox ListTB 
         Enabled         =   0   'False
         Height          =   1200
         Left            =   240
         TabIndex        =   18
         Top             =   600
         Width           =   1572
      End
      Begin VB.ListBox ListFld 
         Enabled         =   0   'False
         Height          =   1200
         Left            =   2280
         TabIndex        =   17
         Top             =   600
         Width           =   1572
      End
      Begin VB.Label LabTable 
         AutoSize        =   -1  'True
         Caption         =   "Tables:"
         Enabled         =   0   'False
         Height          =   195
         Left            =   240
         TabIndex        =   20
         Top             =   360
         Width           =   525
      End
      Begin VB.Label LabField 
         AutoSize        =   -1  'True
         Caption         =   "Fields:"
         Enabled         =   0   'False
         Height          =   195
         Left            =   2280
         TabIndex        =   19
         Top             =   360
         Width           =   450
      End
   End
   Begin VB.Frame Frame2 
      Caption         =   "Enter Database Connection Information:"
      Height          =   1815
      Left            =   120
      TabIndex        =   12
      Top             =   120
      Width           =   4095
      Begin VB.CommandButton ComConnect 
         Caption         =   "&Connect"
         Default         =   -1  'True
         Enabled         =   0   'False
         Height          =   375
         Left            =   2760
         TabIndex        =   4
         Top             =   360
         Width           =   1095
      End
      Begin VB.TextBox TxtDSN 
         Height          =   285
         Left            =   720
         TabIndex        =   1
         Top             =   480
         Width           =   1815
      End
      Begin VB.TextBox TxtUID 
         Height          =   285
         Left            =   720
         TabIndex        =   2
         Top             =   840
         Width           =   1815
      End
      Begin VB.TextBox TxtPWD 
         Height          =   285
         Left            =   720
         TabIndex        =   3
         Top             =   1200
         Width           =   1815
      End
      Begin VB.Label LabDSN 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         Caption         =   "DSN:"
         Height          =   195
         Left            =   240
         TabIndex        =   15
         Top             =   480
         Width           =   390
      End
      Begin VB.Label LabUID 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         Caption         =   "UID:"
         Height          =   195
         Left            =   240
         TabIndex        =   14
         Top             =   840
         Width           =   330
      End
      Begin VB.Label LabPWD 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         Caption         =   "PWD:"
         Height          =   195
         Left            =   240
         TabIndex        =   13
         Top             =   1200
         Width           =   435
      End
   End
   Begin VB.Frame FrameResult 
      Caption         =   "Timing Results"
      Enabled         =   0   'False
      Height          =   2175
      Left            =   4560
      TabIndex        =   0
      Top             =   1320
      Width           =   3615
      Begin VB.TextBox TxtDAO 
         BackColor       =   &H00C0C0C0&
         Enabled         =   0   'False
         Height          =   285
         Left            =   1680
         Locked          =   -1  'True
         TabIndex        =   7
         Top             =   480
         Width           =   1335
      End
      Begin VB.TextBox TxtRDO 
         BackColor       =   &H00C0C0C0&
         Enabled         =   0   'False
         Height          =   285
         Left            =   1680
         Locked          =   -1  'True
         TabIndex        =   6
         Top             =   840
         Width           =   1335
      End
      Begin VB.TextBox TxtODBC 
         BackColor       =   &H00C0C0C0&
         Enabled         =   0   'False
         Height          =   285
         Left            =   1680
         Locked          =   -1  'True
         TabIndex        =   5
         Top             =   1200
         Width           =   1335
      End
      Begin VB.Label LabCount 
         Height          =   255
         Left            =   1800
         TabIndex        =   23
         Top             =   1800
         Width           =   495
      End
      Begin VB.Label LabMsg 
         Height          =   255
         Left            =   240
         TabIndex        =   22
         Top             =   1800
         Width           =   1455
      End
      Begin VB.Label LabDAO 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         Caption         =   "Testing DAO"
         Enabled         =   0   'False
         Height          =   195
         Left            =   600
         TabIndex        =   11
         Top             =   480
         Width           =   915
      End
      Begin VB.Label LabRDO 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         Caption         =   "Testing RDO"
         Enabled         =   0   'False
         Height          =   195
         Left            =   600
         TabIndex        =   10
         Top             =   840
         Width           =   930
      End
      Begin VB.Label LabODBC 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         Caption         =   "Testing ODBC API"
         Enabled         =   0   'False
         Height          =   195
         Left            =   240
         TabIndex        =   9
         Top             =   1200
         Width           =   1320
      End
      Begin VB.Label LabRPS 
         AutoSize        =   -1  'True
         Caption         =   "Records Per Second"
         Enabled         =   0   'False
         Height          =   195
         Left            =   1680
         TabIndex        =   8
         Top             =   240
         Width           =   1605
      End
   End
End
Attribute VB_Name = "VBDBForm"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit
Dim DSN As String, UID As String, PWD As String
Dim connect As String

Private Sub ComConnect_Click()
If TxtUID.Text = "" Then TxtUID.Text = "SA"
ComConnect.Enabled = False
VBDBForm.MousePointer = 11
DoEvents  ' to displau the default UID immediately
connect = "ODBC;" & "DSN=" & Trim(DSN) & ";" & "UID=" & _
    IIf(Len(Trim(UID)) > 0, Trim(UID), "SA") & ";" & "PWD=" & Trim(PWD) & ";"
On Error GoTo ErrorInvalidData
Set MyDb = DBEngine.Workspaces(0).OpenDatabase(" ", False, False, connect)
LabTable.Enabled = True
listtb.Enabled = True
listTable ""
listfld.Clear
FrameTD.Enabled = True

VBDBForm.MousePointer = 0
Exit Sub
ErrorInvalidData:
ComConnect.Enabled = True
VBDBForm.MousePointer = 0
MsgBox "Could not locate: " & vbCrLf & "DSN = " & DSN & vbCrLf & _
    "UID = " & IIf(Len(Trim(UID)) > 0, Trim(UID), "SA") & vbCrLf & "PWD = " & PWD, vbOKOnly, "Error!"
TxtDSN.SetFocus
End Sub

Private Sub ComTest_Click()
labdao.Enabled = True
labrdo.Enabled = True
labodbc.Enabled = True
FrameResult.Enabled = True
labRPS.Enabled = True
TxtDAO.Enabled = True
TxtRDO.Enabled = True
TxtODBC.Enabled = True
DoEvents
ComTest.Enabled = False
VBDBForm.MousePointer = 11
ComputeRPS IIf(OPtread(0), True, False), Iterations, DataName, TableName, FieldName, FieldType, connect
VBDBForm.MousePointer = 0
ComTest.Enabled = True
End Sub

Private Sub TxtDSN_Change()
ComConnect.Enabled = Len(TxtDSN.Text) > 0
FrameTD.Enabled = False
frameOpt.Enabled = False
VBDBForm.TxtDAO.Text = Format(0, "0.####")
VBDBForm.TxtRDO.Text = Format(0, "0.####")
VBDBForm.TxtODBC.Text = Format(0, "0.####")
FrameResult.Enabled = False
DSN = TxtDSN.Text
End Sub

Private Sub TxtPWD_Change()
PWD = IIf(Len(Trim(TxtPWD.Text)) > 0, TxtPWD.Text, "")
End Sub

Private Sub TxtUID_Change()
UID = IIf(Len(Trim(TxtUID.Text)) > 0, TxtUID.Text, "SA")
End Sub

Sub listTb_Click()
Dim tdstring As String
Dim i As Integer
VBDBForm.MousePointer = 11
LabField.Enabled = True
listfld.Enabled = True
tdstring = IIf(VBDBForm.listtb.ListIndex > -1, _
    listtb.List(VBDBForm.listtb.ListIndex), "")
Dim l As Integer
l = InStr(tdstring, "*")
If l > 2 Then tdstring = Left(tdstring, l - 2)
listTable tdstring
VBDBForm.MousePointer = 0
TableName = tdstring
End Sub

Private Sub ListFld_Click()
Dim fldString As String
Dim TmpType As String
again:
fldString = IIf(listfld.ListIndex > -1, _
listfld.List(listfld.ListIndex), "")
TmpType = fldString  'save field value
fldString = Left(fldString, Len(fldString) - 14)
TmpType = Right(TmpType, 11)
FieldName = fldString
FieldType = TmpType
If Trim(TmpType) <> "Text" Then
    ComTest.Enabled = False
    MsgBox "Only Text Field is supported "
    Exit Sub
End If
VBDBForm.OPtread(0).Enabled = True
VBDBForm.OPtread(1).Enabled = True
LabIteration.Enabled = True
Iterations.Enabled = True
ComTest.Enabled = True
frameOpt.Enabled = True
DataName = MyDb.Name
'MyDb.Close
ComTest.Enabled = True
End Sub


