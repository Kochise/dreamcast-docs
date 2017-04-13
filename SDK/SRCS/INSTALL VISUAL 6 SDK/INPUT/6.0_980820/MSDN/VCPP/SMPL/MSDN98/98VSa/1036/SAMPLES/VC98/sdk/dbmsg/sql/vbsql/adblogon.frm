VERSION 2.00
Begin Form fLogin 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   3  'Fixed Double
   Caption         =   "Logon to SQL Server"
   ControlBox      =   0   'False
   ForeColor       =   &H00C0C0C0&
   Height          =   2850
   Left            =   2100
   LinkMode        =   1  'Source
   LinkTopic       =   "Form2"
   MaxButton       =   0   'False
   MDIChild        =   -1  'True
   MinButton       =   0   'False
   ScaleHeight     =   2445
   ScaleWidth      =   3480
   Top             =   1875
   Width           =   3600
   Begin SSPanel Panel3D4 
      AutoSize        =   3  'AutoSize Child To Panel
      BackColor       =   &H00C0C0C0&
      BevelInner      =   1  'Inset
      BevelOuter      =   0  'None
      BorderWidth     =   0
      Font3D          =   0  'None
      ForeColor       =   &H00000000&
      Height          =   330
      Left            =   1110
      TabIndex        =   12
      Top             =   1410
      Width           =   2145
      Begin TextBox txtDatabase 
         BackColor       =   &H00FFFFFF&
         ForeColor       =   &H00000000&
         Height          =   300
         Left            =   15
         TabIndex        =   13
         Top             =   15
         Width           =   2115
      End
   End
   Begin SSPanel Panel3D3 
      AutoSize        =   3  'AutoSize Child To Panel
      BackColor       =   &H00C0C0C0&
      BevelInner      =   1  'Inset
      BevelOuter      =   0  'None
      BorderWidth     =   0
      Font3D          =   0  'None
      ForeColor       =   &H00000000&
      Height          =   330
      Left            =   1110
      TabIndex        =   10
      Top             =   975
      Width           =   2145
      Begin TextBox txtPassword 
         BackColor       =   &H00FFFFFF&
         ForeColor       =   &H00000000&
         Height          =   300
         Left            =   15
         PasswordChar    =   "*"
         TabIndex        =   11
         Top             =   15
         Width           =   2115
      End
   End
   Begin SSPanel Panel3D2 
      AutoSize        =   3  'AutoSize Child To Panel
      BackColor       =   &H00C0C0C0&
      BevelInner      =   1  'Inset
      BevelOuter      =   0  'None
      BorderWidth     =   0
      Font3D          =   0  'None
      ForeColor       =   &H00000000&
      Height          =   330
      Left            =   1110
      TabIndex        =   8
      Top             =   555
      Width           =   2145
      Begin TextBox txtLoginId 
         BackColor       =   &H00FFFFFF&
         Height          =   300
         Left            =   15
         TabIndex        =   9
         Top             =   15
         Width           =   2115
      End
   End
   Begin SSPanel Panel3D1 
      AutoSize        =   3  'AutoSize Child To Panel
      BackColor       =   &H00C0C0C0&
      BevelInner      =   1  'Inset
      BevelOuter      =   0  'None
      BorderWidth     =   0
      Font3D          =   0  'None
      ForeColor       =   &H00000000&
      Height          =   330
      Left            =   1110
      TabIndex        =   6
      Top             =   135
      Width           =   2145
      Begin ComboBox cboServer 
         BackColor       =   &H00FFFFFF&
         Height          =   300
         Left            =   15
         TabIndex        =   7
         Text            =   "Combo1"
         Top             =   15
         Width           =   2115
      End
   End
   Begin CommandButton cmdLogin 
      Caption         =   "&Login"
      Default         =   -1  'True
      Height          =   390
      Left            =   225
      TabIndex        =   0
      Top             =   1920
      Width           =   1335
   End
   Begin CommandButton cmdCancel 
      Caption         =   "&Cancel"
      Height          =   390
      Left            =   1875
      TabIndex        =   2
      Top             =   1920
      Width           =   1335
   End
   Begin Label lblLogin 
      AutoSize        =   -1  'True
      BackColor       =   &H00C0C0C0&
      Caption         =   "Database"
      Height          =   195
      Index           =   3
      Left            =   165
      TabIndex        =   5
      Top             =   1515
      Width           =   825
   End
   Begin Label lblLogin 
      AutoSize        =   -1  'True
      BackColor       =   &H00C0C0C0&
      Caption         =   "Password"
      Height          =   195
      Index           =   2
      Left            =   165
      TabIndex        =   4
      Top             =   1080
      Width           =   825
   End
   Begin Label lblLogin 
      AutoSize        =   -1  'True
      BackColor       =   &H00C0C0C0&
      Caption         =   "Login Id"
      Height          =   195
      Index           =   0
      Left            =   165
      TabIndex        =   3
      Top             =   660
      Width           =   705
   End
   Begin Label lblLogin 
      AutoSize        =   -1  'True
      BackColor       =   &H00C0C0C0&
      Caption         =   "Server"
      Height          =   195
      Index           =   1
      Left            =   165
      TabIndex        =   1
      Top             =   255
      Width           =   570
   End
End

Sub cmdCancel_Click ()
    
    Unload Me
    
End Sub

Sub cmdLogin_Click ()
Dim Channel%
On Error GoTo LoginError

    screen.MousePointer = 11
    Server$ = cboServer.Text
    LoginId$ = txtLoginId.Text
    Password$ = txtPassword.Text
    Database$ = txtDatabase.Text
    WorkSta$ = ""
    Res% = SQLSetLogintime(30)
    Res% = SQLSettime(30)

    Channel% = Logon%(Server$, LoginId$, Password$, WorkSta$, AppName$)

    If (Channel% = FAIL%) Then
        Beep
        txtPassword.SetFocus
    Else
        Results% = SqlUse(Channel%, Database$)
        If (Results% = FAIL%) Then
            Beep
            MsgBox "Could not access database " + Database$
            GoTo LoginError
        Else
            MDIMA.altAuthors.Enabled = True
            MDIMA.altLogout.Enabled = True
            MDIMA.cmdLogout.Enabled = True

            ' Get info on who is logged in for panel display:
            Res% = SQLComm(Channel%, "select User_Name()")
            If Res% = SUCCEED% Then
                Res% = SQLNextRow(Channel%)
                If REGROW Then
                    SQLUser$ = SQLData(Channel%, 1)
                Else
                    SQLUser$ = ""
                End If
            Else
                SQLUser$ = ""
            End If
            Sqlclose (Channel%)

            'Save login info in local log file for next time:
            Open "c:\adbpubs.log" For Output As #1
            Print #1, Server$
            Print #1, Database$
            Print #1, LoginId$
            Close #1
            screen.MousePointer = 0
            MDIMA.cmdUnloadActForms.Value = True
        End If
    End If

LoginExit:
    SetLoginInfo Server$, LoginId$, Database$, SQLUser$
    screen.MousePointer = 0
    Exit Sub

LoginError:
    Resume Next

End Sub

Sub Form_Load ()
Dim Srvr$, Db$, Usr$
    
On Error GoTo FormLoadError

    cboServer.Text = ""
    txtLoginId.Text = ""
    txtPassword.Text = ""
    txtDatabase.Text = ""
    Me.Width = 3600
    Me.Height = 2850
    Me.Top = screen.Height / 2 - Me.Height / 2 - 710
    Me.Left = screen.Width / 2 - Me.Width / 2
    Open "c:\adbpubs.log" For Input As #1
    Input #1, Srvr$
    Input #1, Db$
    Input #1, Usr$
    Close #1
    cboServer.Text = Srvr$
    txtDatabase.Text = Db$
    txtLoginId.Text = Usr$
    Me.Show
    If Len(RTrim$(cboServer.Text)) Then txtPassword.SetFocus
    
FormLoadExit:
    Exit Sub

FormLoadError:
    Resume FormLoadExit

End Sub

Sub SetLoginInfo (pServer$, pLoginId$, pDatabase$, pUser$)
Dim lInfo$

    lInfo$ = " Server: " + pServer$
    lInfo$ = lInfo$ + "    Login: " + pLoginId$
    lInfo$ = lInfo$ + "    Database: " + pDatabase$
    lInfo$ = lInfo$ + "    User: " + pUser$
    MDIMA.panInfo.Caption = lInfo$

End Sub

Sub txtDatabase_GotFocus ()

    txtDatabase.SelStart = 0
    txtDatabase.SelLength = Len(txtDatabase.Text)

End Sub

Sub txtLoginId_GotFocus ()

    txtLoginId.SelStart = 0
    txtLoginId.SelLength = Len(txtLoginId.Text)

End Sub

Sub txtPassword_GotFocus ()
 
    txtPassword.SelStart = 0
    txtPassword.SelLength = Len(txtPassword.Text)

End Sub

