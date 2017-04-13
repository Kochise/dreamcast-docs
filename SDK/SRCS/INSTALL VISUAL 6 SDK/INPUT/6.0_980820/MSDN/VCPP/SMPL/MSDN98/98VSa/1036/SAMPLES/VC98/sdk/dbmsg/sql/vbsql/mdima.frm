VERSION 2.00
Begin MDIForm MDIMa 
   Caption         =   "Demo ADBPubs"
   Height          =   4755
   Icon            =   MDIMA.FRX:0000
   Left            =   75
   LinkTopic       =   "MDIForm1"
   Top             =   555
   Width           =   7740
   WindowState     =   2  'Maximized
   Begin SSPanel panStatusbar 
      Align           =   2  'Align Bottom
      Alignment       =   2  'Left Justify - BOTTOM
      BackColor       =   &H00C0C0C0&
      BevelInner      =   2  'Raised
      BevelOuter      =   0  'None
      BorderWidth     =   0
      FontBold        =   0   'False
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      ForeColor       =   &H00000000&
      Height          =   420
      Left            =   0
      Outline         =   -1  'True
      TabIndex        =   8
      Top             =   3645
      Width           =   7620
      Begin SSPanel panInfo 
         Alignment       =   2  'Left Justify - BOTTOM
         AutoSize        =   3  'AutoSize Child To Panel
         BackColor       =   &H00C0C0C0&
         BevelInner      =   1  'Inset
         BevelOuter      =   0  'None
         BorderWidth     =   0
         Caption         =   " Server: [Not logged in]"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         ForeColor       =   &H00000000&
         Height          =   300
         Left            =   120
         TabIndex        =   11
         Top             =   60
         Width           =   12930
      End
      Begin VBSQL VBSQL1 
         Caption         =   "VBSQL1"
         Height          =   210
         Left            =   12555
         Top             =   105
         Visible         =   0   'False
         Width           =   525
      End
   End
   Begin SSPanel panToolbar 
      Align           =   1  'Align Top
      AutoSize        =   3  'AutoSize Child To Panel
      BackColor       =   &H00C0C0C0&
      BorderWidth     =   4
      ForeColor       =   &H00000000&
      Height          =   435
      Left            =   0
      Outline         =   -1  'True
      TabIndex        =   0
      Top             =   0
      Width           =   7620
      Begin CommandButton cmdUnloadActForms 
         Caption         =   "Unload Forms"
         Height          =   270
         Left            =   9570
         TabIndex        =   12
         Top             =   75
         Visible         =   0   'False
         Width           =   1455
      End
      Begin SSCommand cmdLogin 
         BevelWidth      =   1
         Font3D          =   1  'Raised w/light shading
         ForeColor       =   &H00000000&
         Height          =   345
         Left            =   8610
         Picture         =   MDIMA.FRX:0302
         TabIndex        =   10
         TabStop         =   0   'False
         Top             =   45
         Width           =   345
      End
      Begin SSCommand cmdLogout 
         BevelWidth      =   1
         Enabled         =   0   'False
         Font3D          =   1  'Raised w/light shading
         ForeColor       =   &H00000000&
         Height          =   345
         Left            =   9000
         Picture         =   MDIMA.FRX:0604
         TabIndex        =   9
         TabStop         =   0   'False
         Top             =   45
         Width           =   345
      End
      Begin SSCommand MainButton 
         BevelWidth      =   1
         Font3D          =   1  'Raised w/light shading
         ForeColor       =   &H00000000&
         Height          =   340
         Index           =   1
         Left            =   75
         Picture         =   MDIMA.FRX:0906
         TabIndex        =   7
         Top             =   45
         Width           =   340
      End
      Begin SSCommand MainButton 
         BevelWidth      =   1
         Font3D          =   1  'Raised w/light shading
         ForeColor       =   &H00000000&
         Height          =   340
         Index           =   2
         Left            =   465
         Picture         =   MDIMA.FRX:0A70
         TabIndex        =   6
         Top             =   45
         Width           =   340
      End
      Begin SSCommand MainButton 
         BevelWidth      =   1
         Font3D          =   1  'Raised w/light shading
         ForeColor       =   &H00000000&
         Height          =   340
         Index           =   3
         Left            =   855
         Picture         =   MDIMA.FRX:0BDA
         TabIndex        =   5
         Top             =   45
         Width           =   340
      End
      Begin SSCommand MainButton 
         BevelWidth      =   1
         Font3D          =   1  'Raised w/light shading
         ForeColor       =   &H00000000&
         Height          =   340
         Index           =   4
         Left            =   1380
         Picture         =   MDIMA.FRX:0D44
         TabIndex        =   4
         Top             =   45
         Width           =   340
      End
      Begin SSCommand MainButton 
         BevelWidth      =   1
         Font3D          =   1  'Raised w/light shading
         ForeColor       =   &H00000000&
         Height          =   340
         Index           =   5
         Left            =   1905
         Picture         =   MDIMA.FRX:0EAE
         TabIndex        =   3
         Top             =   45
         Width           =   340
      End
      Begin SSCommand MainButton 
         BevelWidth      =   1
         Font3D          =   1  'Raised w/light shading
         ForeColor       =   &H00000000&
         Height          =   340
         Index           =   6
         Left            =   2295
         Picture         =   MDIMA.FRX:1048
         TabIndex        =   2
         Top             =   45
         Width           =   340
      End
      Begin SSCommand MainButton 
         BevelWidth      =   1
         Font3D          =   1  'Raised w/light shading
         ForeColor       =   &H00000000&
         Height          =   340
         Index           =   7
         Left            =   2820
         Picture         =   MDIMA.FRX:11B2
         TabIndex        =   1
         Top             =   45
         Width           =   340
      End
   End
   Begin Menu MenFile 
      Caption         =   "&File"
      Begin Menu altLogin 
         Caption         =   "&Login"
         Shortcut        =   ^L
      End
      Begin Menu altLogout 
         Caption         =   "Log&out"
         Enabled         =   0   'False
      End
      Begin Menu altDummy 
         Caption         =   "-"
      End
      Begin Menu AltExit 
         Caption         =   "&Exit"
      End
   End
   Begin Menu MenForms 
      Caption         =   "F&orms"
      WindowList      =   -1  'True
      Begin Menu altAuthors 
         Caption         =   "&Authors"
         Enabled         =   0   'False
         Shortcut        =   ^A
      End
   End
   Begin Menu menHelp 
      Caption         =   "&Help"
      Begin Menu altContents 
         Caption         =   "&Contents"
      End
      Begin Menu altDummy2 
         Caption         =   "-"
      End
      Begin Menu altAbout 
         Caption         =   "&About..."
      End
   End
End

Sub altAbout_Click ()
'
' Show the About box
'

    fAbout.Show MODAL

End Sub

Sub altAuthors_click ()
'
' Open the Authors form
' The menu in the Authors form allows opening
' of several simultaneous instances of the Authors form
'

    screen.MousePointer = 11
    fAuthors.Show
    screen.MousePointer = 0

End Sub

Sub altContents_Click ()
Dim X%, lHelpPath As String
'
' Activate the help system
'
    
    lHelpPath = App.Path + "\pubs1.hlp"
    X% = WinHelp(MDIMA.hWnd, lHelpPath, HELP_INDEX, 0)

End Sub

Sub altExit_Click ()
'
' Exit the application
'
    Unload Me       ' Unload the MDI form and so exit the app.
    ' Better then end, since unload will call
    ' the MDIForm_Unload procedure

End Sub

Sub altLogin_Click ()
'
' Call the log in procedure
'

    ' Auto press the cmdLogin push button if it is enabled:
    If cmdLogin.Enabled Then
        cmdLogin.Value = True
    Else
        Beep
    End If
    
End Sub

Sub altLogout_Click ()
'
' Call the log out procedure
'

    ' Auto press the cmdLogout push button if it is enabled:
    If cmdLogout.Enabled Then
        cmdLogout.Value = True
    Else
        Beep
    End If

End Sub

Sub cmdLogin_Click ()
'
' Show the login form
'

    fLogin.Show

End Sub

Sub cmdLogout_Click ()
'
' Log out from SQL Server and do neccessary maintaneance
'

    ' Set caption of panel to show "not logged in":
    panInfo.Caption = " Server: [Not logged in]"

    SqlExit             ' close all connections to SQL Server
    
    ' Press invisible push button to unload all active forms:
    cmdUnloadActForms.Value = True
    
    ' Disable objects inappropriate when not logged in:
    altAuthors.Enabled = False
    altLogout.Enabled = False
    cmdLogout.Enabled = False

End Sub

Sub cmdUnloadActForms_Click ()
'
' Unload all forms.
' Normally called when logging out.
' Thus no qualified info will be shown on the screen
' after the user with permissions has logged out
'

On Error GoTo cmdActFormError

    ' In a loop: unload all forms:
    Do
        ' Unload the active form; make another active:
        Unload ActiveForm
    Loop

cmdActFormExit:
    Exit Sub

cmdActFormError:
    ' Presume no more active forms; go to exit:
    Resume cmdActFormExit:

End Sub

Sub MainButton_Click (index As Integer)
'
' The main buttons are organized as a button array,
' where each button has a corresponding button in
' each (or most) forms. When the users click on a
' button in the MDI form tool bar the corresponding
' button in the active form will be automatically
' clicked if it is enabled. Each form will have its
' own specialized procedure connected to each separate
' button. If you will, study the MainButton procedure
' in the authors form.
'
' This technique could be claimed to offer some sort
' of polymorphism to the app.
'
On Error GoTo MainButtonError

    If ActiveForm.MainButton(index).Enabled Then
        ActiveForm.MainButton(index).Value = True
    Else
        Beep
    End If

MainButtonExit:
    Exit Sub

MainButtonError:

    Beep
    Resume MainButtonExit

End Sub

Sub MDIForm_Load ()
'
' Set up the MDI form for processing.
' Call the log in procedure
'

    ' Set global variable AppName$ for log in purposes
    AppName$ = "Demo Authors 1"              'Global variable
    
    ' Initialize the global variable NEWLINE$
    NEWLINE$ = Chr$(13) + Chr$(10)
    
    ' When global variable ShowSQL is set to false
    ' SQL statements will not be shown. Set to true
    ' by means of the Option menu.
    ShowSQL = False

    ' Setting the width of the Info Panel
    SetPanelWidth

    'Initialize VBSQL before log in:
    msg$ = SQLInit$()
    If msg$ = "" Then
        Beep
        MsgBox "Couldn't initialize VBSQL. Sorry. Must terminate.", 16
        End
    End If
    
    fLogin.Show         ' Open login form

End Sub

Sub MDIForm_Resize ()

    SetPanelWidth

End Sub

Sub MDIForm_Unload (Cancel As Integer)
'
' Clean up any connection with SQL Server and close
' the help system, then exit the application (End).
'

Dim X%

    SqlExit
    SqlWinExit
    X% = WinHelp(MDIMA.hWnd, "pubs1.hlp", HELP_QUIT, 0)
    End

End Sub

Sub SetPanelWidth ()
Dim lWidth As Integer

    lWidth = MDIMA.Width - 350
    If lWidth >= 5500 Then panInfo.Width = MDIMA.Width - 350

End Sub

Sub VBSQL1_Error (SqlConn As Integer, Severity As Integer, ErrorNum As Integer, ErrorStr As String, RetCode As Integer)
'
' Minimal error management.
' Show the severity of the error, the error number
' and the error message in a message box.

Dim lMsg$

    lMsg$ = "Severity: " & Severity & Chr$(13) + Chr$(13)
    lMsg$ = lMsg$ + Str$(ErrorNum) + " " + ErrorStr + Chr$(13) + Chr$(13)
    MsgBox lMsg$, 16, "SQL-Error"

End Sub

Sub VBSQL1_Message (SqlConn As Integer, Message As Long, State As Integer, Severity As Integer, MsgStr As String)
'
' Minimal SQL Server message management.
' Filter out very trivial messages (5701 and 5703)
' Show the others with message number and message
' string in a message box.
'
    If Message <> 5701 And Message <> 5703 Then
        MsgBox "MSG: " + Str$(Message) + ": " + MsgStr, 0, "SQL Message"
    End If
    
End Sub

