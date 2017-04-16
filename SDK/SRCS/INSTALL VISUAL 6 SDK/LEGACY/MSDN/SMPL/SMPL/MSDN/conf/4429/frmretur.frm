VERSION 2.00
Begin Form frmReturns 
   AutoRedraw      =   -1  'True
   Caption         =   "Results Pending"
   ClientHeight    =   2985
   ClientLeft      =   1980
   ClientTop       =   3540
   ClientWidth     =   3375
   Height          =   3390
   Icon            =   FRMRETUR.FRX:0000
   Left            =   1920
   LinkTopic       =   "Form2"
   ScaleHeight     =   2985
   ScaleWidth      =   3375
   Top             =   3195
   Width           =   3495
   Begin Data Data1 
      Caption         =   "Data1"
      Connect         =   ""
      DatabaseName    =   ""
      Exclusive       =   0   'False
      Height          =   270
      Left            =   0
      Options         =   0
      ReadOnly        =   0   'False
      RecordSource    =   "Table 1"
      Top             =   0
      Visible         =   0   'False
      Width           =   3375
   End
   Begin Timer Timer1 
      Interval        =   1000
      Left            =   2880
      Top             =   240
   End
   Begin Label ZipName 
      Caption         =   "ZipName"
      Height          =   255
      Left            =   1320
      TabIndex        =   4
      Top             =   360
      Visible         =   0   'False
      Width           =   1455
   End
   Begin Label FieldValue 
      AutoSize        =   -1  'True
      Caption         =   "FieldValue"
      DataSource      =   "Data1"
      Height          =   195
      Index           =   0
      Left            =   960
      TabIndex        =   3
      Top             =   720
      Visible         =   0   'False
      Width           =   900
   End
   Begin Label FieldName 
      AutoSize        =   -1  'True
      Caption         =   "FieldName"
      Height          =   195
      Index           =   0
      Left            =   0
      TabIndex        =   2
      Top             =   720
      Visible         =   0   'False
      Width           =   900
   End
   Begin Label MDBName 
      AutoSize        =   -1  'True
      Caption         =   "MDBName"
      Height          =   195
      Left            =   0
      TabIndex        =   1
      Top             =   480
      Visible         =   0   'False
      Width           =   900
   End
   Begin Label TableName 
      AutoSize        =   -1  'True
      Caption         =   "TableName"
      Height          =   195
      Left            =   0
      TabIndex        =   0
      Top             =   240
      Visible         =   0   'False
      Width           =   975
   End
End
Dim RequestFile$, MDBFile$
Dim QryNo%
Const RASQuery$ = "C:\RASQUERY"
Const RASResults$ = "C:\RAS_RET\"

Sub CopyFile ()
BatchFile$ = App.Path + "\" + Left$(MDBName, InStr(MDBName, ".")) + "Bat"
fno = FreeFile
Open BatchFile$ For Output As #fno
If Len(ZipName) > 0 Then
    Print #fno, "COPY " + RASResults$ + ZipName + " " + App.Path + "\" + ZipName
Else
    Print #fno, "COPY " + RASResults$ + MDBName + " " + App.Path + "\" + MDBName
End If
If Len(ZipName) > 0 Then
    Print #fno, "CHDIR " + App.Path
    Print #fno, "PKUNZIP " + App.Path + "\" + ZipName
    Print #fno, "DEL " + RASResults$ + ZipName
Else
    Print #fno, "DEL " + RASResults$ + MDBName
End If
Print #fno, "DEL " + BatchFile$
Close #fno
If Shell(BatchFile$, 6) Then
    While Dir(BatchFile$) <> ""
	DoEvents
    Wend
End If
End Sub

Sub ParseTag ()
Tabidx% = InStr(Tag, Chr$(9))
RequestFile$ = Left$(Tag, Tabidx% - 1)
MDBFile$ = Left$(Tag, Tabidx% + 1)
End Sub

Sub SetResults (ByVal MDBFile$)
Dim DB As Database
tABLENAME.Visible = True
MDBName.Visible = True
If Dir(MDBFile$) = "" Then
    MsgBox "Query failed -- NO FILE RETURNED"
    Exit Sub
End If

Data1.Visible = True
Data1.DatabaseName = MDBFile$
Data1.RecordSource = tABLENAME
Data1.Refresh
Set DB = OpenDatabase(MDBFile$)

For I = 0 To Data1.Database.TableDefs(tABLENAME).Fields.Count - 1
    If I > 0 Then
	Load FieldName(I): Load FieldValue(I)
	FieldName(I).Top = FieldName(I - 1).Top + FieldName(I - 1).Height
	FieldValue(I).Top = FieldValue(I - 1).Top + FieldValue(I - 1).Height
	End If
    FieldName(I) = Data1.Database.TableDefs(tABLENAME).Fields(I).Name
    FieldValue(I).DataField = FieldName(I).Caption
    FieldValue(I).Left = FieldName(I).Left + FieldName(I).Width
    FieldValue(I).ForeColor = RGB(255, 0, 0)
    FieldValue(I).Visible = True
    FieldName(I).Visible = True
Next I


End Sub

Sub Timer1_Timer ()
If Dir(Tag) = "" Then
    Caption = "Receiving Results"
    CopyFile
    SetResults App.Path + "\" + MDBName
    Timer1.Enabled = False
    Caption = "Results Back"
End If
End Sub

