VERSION 2.00
Begin Form login 
   BorderStyle     =   3  'Fixed Double
   Caption         =   "SQL Server Login"
   Height          =   2685
   Icon            =   0
   Left            =   1035
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2280
   ScaleWidth      =   6690
   Top             =   1020
   Width           =   6810
   Begin TextBox password_field 
      Height          =   375
      Left            =   1320
      TabIndex        =   5
      Text            =   "Text1"
      Top             =   1440
      Width           =   3495
   End
   Begin CommandButton CANCEL_BUTTON 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   495
      Left            =   5160
      TabIndex        =   7
      Top             =   840
      Width           =   1335
   End
   Begin TextBox login_id_field 
      Height          =   375
      Left            =   1320
      TabIndex        =   3
      Text            =   "Text1"
      Top             =   840
      Width           =   3495
   End
   Begin CommandButton OK_BUTTON 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   495
      Left            =   5160
      TabIndex        =   6
      Top             =   240
      Width           =   1335
   End
   Begin TextBox Server_name_field 
      Height          =   375
      Left            =   1320
      TabIndex        =   1
      Text            =   "Text1"
      Top             =   240
      Width           =   3495
   End
   Begin Label Label3 
      Caption         =   "&Password:"
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Top             =   1440
      Width           =   975
   End
   Begin Label Label2 
      Caption         =   "&Login ID:"
      Height          =   255
      Left            =   120
      TabIndex        =   2
      Top             =   840
      Width           =   975
   End
   Begin Label Label1 
      Caption         =   "&Server:"
      Height          =   255
      Left            =   120
      TabIndex        =   0
      Top             =   240
      Width           =   975
   End
End
'$INCLUDE: 'VBQUERY.BI'
'$INCLUDE: 'VBDSQL.BI'

Sub CANCEL_BUTTON_Click ()
    
    ExitApplication

End Sub

Sub Form_Load ()
    Server_name_field.Text = DefServer$
    Login_id_field.Text = DefLogin$
    PASSWORD_FIELD.Text = ""
    password$ = ""
End Sub

Sub OK_BUTTON_Click ()

Rem
Rem Get the server name, login Id, & password from the form
Rem

   Servername$ = Server_name_field.Text
   LoginID$ = Login_id_field.Text

Rem Note-- allow null servername becuase you might be running on the same
Rem machine as SQL Server.  Allow null userid because server might be running
Rem integrated security.

Rem Open select connection for browse mode:
Rem

    If LoginToServer() = FAIL Then
        PASSWORD_FIELD.Text = ""
        password$ = ""
        Exit Sub
    End If


Rem
Rem Now Open update connection for browse mode:
Rem Check to see if the connection is live, if so, then close it
Rem Set the max time to login to 30 seconds
Rem Open the new connection
Rem Change the caption of the application to reflect the server name and the database
Rem Set the max time we will wait for a SQL Server response
Rem

    If SqlUpdConn <> 0 Then SqlClose (SqlUpdConn)
    Status% = SqlSetLoginTime%(LoginTimeout)
    SqlUpdConn = SqlOpenConnection(Servername$, LoginID$, password$, ProgramName$, ProgramName$)
    If SqlUpdConn <> 0 Then
        DatabaseName$ = SqlName(SqlUpdConn)
        ChangePrimaryWindowCaption
        Result5 = SqlSetTime%(QueryTimeout)
    Else
        DatabaseName$ = ""
        Servername$ = ""
    End If
    
    Unload Login
End Sub

Sub password_field_KeyPress (keyascii As Integer)

Rem
Rem This will keep the key from being seen
Rem

'   if key pressed is a letter or a number, add it to password and show *

If (keyascii >= 48 And keyascii <= 57) Or (keyascii >= 65 And keyascii <= 90) Or (keyascii >= 97 And keyascii <= 122) Then
        password$ = password$ + Chr$(keyascii)
        keyascii = Asc("*")

ElseIf (keyascii = 8) Then   'if backspace
        If Len(password$) > 0 Then
        password$ = Left$(password$, Len(password$) - 1)
        End If
Else                        'if anything else, throw out
        keyascii = 0
        Beep
End If

End Sub

