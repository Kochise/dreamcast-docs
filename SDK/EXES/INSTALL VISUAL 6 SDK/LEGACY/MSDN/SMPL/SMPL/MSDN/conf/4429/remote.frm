VERSION 2.00
Begin Form Form1 
   Caption         =   "Remote Host"
   ClientHeight    =   2325
   ClientLeft      =   270
   ClientTop       =   570
   ClientWidth     =   7365
   Height          =   2730
   Icon            =   REMOTE.FRX:0000
   Left            =   210
   LinkTopic       =   "Form1"
   ScaleHeight     =   2325
   ScaleWidth      =   7365
   Top             =   225
   Width           =   7485
   Begin CheckBox ZipMDB 
      Caption         =   "Zip Data"
      Height          =   255
      Left            =   4200
      TabIndex        =   7
      Top             =   720
      Width           =   3015
   End
   Begin TextBox Query 
      Height          =   975
      Left            =   1080
      MultiLine       =   -1  'True
      TabIndex        =   3
      Text            =   "SELECT * FROM Publishers"
      Top             =   1080
      Width           =   6135
   End
   Begin TextBox MDBName 
      Enabled         =   0   'False
      Height          =   285
      Left            =   1080
      TabIndex        =   2
      Text            =   "demo1.mdb"
      Top             =   720
      Width           =   2535
   End
   Begin TextBox TableName 
      Enabled         =   0   'False
      Height          =   285
      Left            =   1080
      TabIndex        =   1
      Text            =   "Table 2"
      Top             =   240
      Width           =   2535
   End
   Begin CommandButton Command1 
      Caption         =   "&Submit to C:\RASREQUEST"
      Height          =   495
      Left            =   4200
      TabIndex        =   0
      Top             =   120
      Width           =   3015
   End
   Begin Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "Query"
      Height          =   195
      Index           =   2
      Left            =   0
      TabIndex        =   6
      Top             =   1200
      Width           =   510
   End
   Begin Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "MDBName"
      Height          =   195
      Index           =   1
      Left            =   0
      TabIndex        =   5
      Top             =   720
      Width           =   900
   End
   Begin Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "Table Name"
      Height          =   195
      Index           =   0
      Left            =   0
      TabIndex        =   4
      Top             =   240
      Width           =   1035
   End
End
Dim QryNo%, ZipName$
Const RASQuery$ = "C:\RASQUERY"
'Dim Returns()

Sub Command1_Click ()
QryNo% = QryNo% + 1
RQST$ = RASQuery$ + "\KEN" + Format(QryNo%, "0") + ".QRY"

MDBName = "KEN" + Format(QryNo%, "0") + ".MDB"
TableName = "Table " + Format(QryNo%, "0")
If zIPmdb Then
    ZipName$ = "ZIP" + Format$(QryNo%, "0") + ".ZIP"
Else
    ZipName$ = ""
End If
fno = FreeFile
Open RQST$ For Output As #fno
Print #fno, "<" + MDBName.Text
Print #fno, "=" + TableName.Text
Print #fno, ">" + UCase(Query.Text)
If zIPmdb <> 0 Then
Print #fno, "@" + ZipName$
End If
Close #fno

ReDim Returns(QryNo%) As New frmReturns
SetInformation Returns(QryNo%), RQST$, MDBName.Text, TableName
Returns(QryNo%).Visible = True
End Sub

Sub Form_Unload (Cancel As Integer)
End
End Sub

Sub SetInformation (Frm As Form, ByVal QueryFile$, ByVal MDBFile$, ByVal TableName$)
On Error Resume Next
Frm.Tag = QueryFile$
Frm.MDBName = MDBFile$
Frm.TableName = TableName
Frm.ZipName = ZipName$
End Sub

