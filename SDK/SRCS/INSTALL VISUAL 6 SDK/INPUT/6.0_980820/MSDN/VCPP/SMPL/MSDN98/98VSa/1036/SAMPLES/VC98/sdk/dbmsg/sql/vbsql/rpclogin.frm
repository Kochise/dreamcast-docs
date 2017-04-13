VERSION 2.00
Begin Form login 
   BackColor       =   &H00FFFFFF&
   BorderStyle     =   3  'Fixed Double
   Caption         =   "SQL Server Login"
   ForeColor       =   &H00000000&
   Height          =   2640
   Left            =   975
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2235
   ScaleWidth      =   6720
   Top             =   2055
   Width           =   6840
   Begin CommandButton LIST_BUTTON 
      Caption         =   "List Servers..."
      Height          =   495
      Left            =   5160
      TabIndex        =   8
      Top             =   840
      Width           =   1335
   End
   Begin TextBox password_field 
      BackColor       =   &H00FFFFFF&
      ForeColor       =   &H00000000&
      Height          =   375
      Left            =   1320
      PasswordChar    =   "*"
      TabIndex        =   5
      Text            =   "Text1"
      Top             =   1440
      Width           =   3480
   End
   Begin CommandButton CANCEL_BUTTON 
      BackColor       =   &H00C0C0C0&
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   480
      Left            =   5160
      TabIndex        =   7
      Top             =   1440
      Width           =   1320
   End
   Begin TextBox login_id_field 
      BackColor       =   &H00FFFFFF&
      ForeColor       =   &H00000000&
      Height          =   375
      Left            =   1320
      TabIndex        =   3
      Text            =   "Text1"
      Top             =   840
      Width           =   3480
   End
   Begin CommandButton OK_BUTTON 
      BackColor       =   &H00C0C0C0&
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   480
      Left            =   5160
      TabIndex        =   6
      Top             =   240
      Width           =   1320
   End
   Begin TextBox Server_name_field 
      BackColor       =   &H00FFFFFF&
      ForeColor       =   &H00000000&
      Height          =   375
      Left            =   1320
      TabIndex        =   1
      Text            =   "Text1"
      Top             =   240
      Width           =   3480
   End
   Begin Label Label3 
      BackColor       =   &H00FFFFFF&
      Caption         =   "&Password:"
      ForeColor       =   &H00000000&
      Height          =   240
      Left            =   120
      TabIndex        =   4
      Top             =   1560
      Width           =   960
   End
   Begin Label Label2 
      BackColor       =   &H00FFFFFF&
      Caption         =   "&Login ID:"
      ForeColor       =   &H00000000&
      Height          =   240
      Left            =   120
      TabIndex        =   2
      Top             =   960
      Width           =   960
   End
   Begin Label Label1 
      BackColor       =   &H00FFFFFF&
      Caption         =   "&Server:"
      ForeColor       =   &H00000000&
      Height          =   240
      Left            =   120
      TabIndex        =   0
      Top             =   360
      Width           =   960
   End
End
'$INCLUDE: 'VBQUERY.BI'
'$INCLUDE: 'VBDSQL.BI'

Sub CANCEL_BUTTON_Click ()
 Unload Login
End Sub

Sub Form_Load ()
	Server_name_field.Text = DefServer$
	Login_id_field.Text = DefLogin$
	Password_field.Text = ""
End Sub

Sub LIST_BUTTON_Click ()
NL$ = Chr$(13) + Chr$(10)
nullchar$ = Chr$(0)

'  First look for locally defined servers in Win.ini
serverlist$ = Space(1000)
retcode% = SqlServerEnum(LOCSEARCH%, serverlist$, numservers%)
If retcode% <> ENUMSUCCESS% Then
    msg$ = "SQLServerEnum for LOCSEARCH failed, return code " + Str$(retcode%) + NL$
Else
    'parse out the names
    msg$ = "Locally defined servers: " + NL$
    work$ = serverlist$
    scount = 0
    While Len(work$) > 0
	nullcharpos% = InStr(work$, nullchar$)
	If nullcharpos% <> 0 Then
	      srvname$ = Left$(work$, nullcharpos% - 1)
	    If Len(srvname$) <> 0 Then
		scount = scount + 1
		msg$ = msg$ + "Server" + Str$(scount) + ": '" + srvname$ + "'" + NL$
		work$ = Right$(work$, Len(work$) - nullcharpos%)
	    Else
		work$ = ""
	    End If
	End If
		
    Wend
    msg$ = msg$ + NL$
End If

'Now look for servers announced on the network
serverlist$ = Space(1000)
retcode% = SqlServerEnum(NETSEARCH%, serverlist$, numservers%)
If retcode% <> ENUMSUCCESS% Then
    msg$ = msg$ + "SQLServerEnum for NETSEARCH failed, return code " + Str$(retcode%) + NL$
Else
    'parse out the names
    msg$ = msg$ + "Network defined servers: " + NL$
    work$ = serverlist$
    scount = 0
    While Len(work$) > 0
	nullcharpos% = InStr(work$, nullchar$)
	If nullcharpos% <> 0 Then
	      srvname$ = Left$(work$, nullcharpos% - 1)
	    If Len(srvname$) <> 0 Then
		scount = scount + 1
		msg$ = msg$ + "Server" + Str$(scount) + ": '" + srvname$ + "'" + NL$
		work$ = Right$(work$, Len(work$) - nullcharpos%)
	    Else
		work$ = ""
	    End If
	End If
		
    Wend
    msg$ = msg$ + NL$
End If

MsgBox msg$, 0, "Search for Servers"


End Sub

Sub OK_BUTTON_Click ()

Rem
Rem Get the server name, login Id, & password from the form
Rem

   Servername$ = Server_name_field.Text
   LoginID$ = Login_id_field.Text
   Password$ = Password_field.Text

	If Servername$ = "" Then
		MsgBox "Must supply a server name"
		Exit Sub
	End If
	If LoginID$ = "" Then
		MsgBox "Must supply a login id"
		Exit Sub
	End If

Rem
Rem Connect to the server
Rem

	If LoginToServer() = SUCCEED Then Unload Login

End Sub

