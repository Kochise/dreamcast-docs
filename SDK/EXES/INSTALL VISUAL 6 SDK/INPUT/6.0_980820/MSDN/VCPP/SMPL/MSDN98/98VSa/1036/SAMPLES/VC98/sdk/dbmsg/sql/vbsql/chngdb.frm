VERSION 2.00
Begin Form CHNGDB 
   BackColor       =   &H00FFFFFF&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Change Database"
   ForeColor       =   &H00000000&
   Height          =   2160
   Left            =   2895
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1755
   ScaleWidth      =   5640
   Top             =   3150
   Width           =   5760
   Begin CommandButton CANCEL_BUTTON 
      BackColor       =   &H00C0C0C0&
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   480
      Left            =   3240
      TabIndex        =   3
      Top             =   1200
      Width           =   1320
   End
   Begin CommandButton OK_BUTTON 
      BackColor       =   &H00C0C0C0&
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   480
      Left            =   1080
      TabIndex        =   2
      Top             =   1200
      Width           =   1320
   End
   Begin ComboBox DBNAME_COMBO 
      BackColor       =   &H00FFFFFF&
      ForeColor       =   &H00000000&
      Height          =   300
      Left            =   2040
      TabIndex        =   1
      Text            =   "Combo1"
      Top             =   360
      Width           =   3240
   End
   Begin Label Label1 
      BackColor       =   &H00FFFFFF&
      Caption         =   "Database Name:"
      ForeColor       =   &H00000000&
      Height          =   240
      Left            =   240
      TabIndex        =   0
      Top             =   480
      Width           =   1560
   End
End
'$INCLUDE: 'VBQUERY.BI'
'$INCLUDE: 'VBDSQL.BI'

Sub CANCEL_BUTTON_Click ()
	Unload Chngdb
End Sub

Sub Form_Load ()
	Result% = GetDatabases(DBNAME_COMBO)
	If Result% = FAIL% Then Unload Chngdb
End Sub

Sub OK_BUTTON_Click ()
	
	newname$ = DBNAME_COMBO.Text
	If SqlUse(SqlConn, newname$) = SUCCEED% Then
		DatabaseName$ = DBNAME_COMBO.Text
		ChangePrimaryWindowCaption
		SqlStatus = SUCCEED
	Else
		SqlStatus = FAIL
	End If
	Unload Chngdb
End Sub

