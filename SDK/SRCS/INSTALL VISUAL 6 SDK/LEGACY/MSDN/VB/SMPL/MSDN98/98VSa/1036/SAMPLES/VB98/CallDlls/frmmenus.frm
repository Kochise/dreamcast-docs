VERSION 5.00
Begin VB.Form frmMenus 
   Caption         =   "Form2"
   ClientHeight    =   2430
   ClientLeft      =   4845
   ClientTop       =   5640
   ClientWidth     =   5175
   BeginProperty Font 
      Name            =   "MS Sans Serif"
      Size            =   8.25
      Charset         =   0
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form2"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   2430
   ScaleWidth      =   5175
   Begin VB.Menu mnuBar 
      Caption         =   "Sons"
      Index           =   1
      Begin VB.Menu mnuSounds 
         Caption         =   "(pas de son)"
         Enabled         =   0   'False
         Index           =   0
      End
   End
   Begin VB.Menu mnuBar 
      Caption         =   "Informations système"
      Index           =   2
      Begin VB.Menu mnuSysInfo 
         Caption         =   "&Windows"
         Index           =   0
      End
      Begin VB.Menu mnuSysInfo 
         Caption         =   "&Processeur"
         Index           =   1
      End
      Begin VB.Menu mnuSysInfo 
         Caption         =   "&Vidéo"
         Index           =   2
      End
      Begin VB.Menu mnuSysInfo 
         Caption         =   "&Général"
         Index           =   3
      End
      Begin VB.Menu mnuSysInfo 
         Caption         =   "-"
         Index           =   4
      End
      Begin VB.Menu mnuSysInfo 
         Caption         =   "Toujours au-dessus"
         Index           =   5
      End
   End
End
Attribute VB_Name = "frmMenus"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Form_Load()
Dim WinPath As String, SoundFile As String, i As Integer
    WinPath = WindowsDirectory()
    
    ' \*.wav peut être remplacé par Windows\Media\*.wav pour Win95
    SoundFile = Dir(WinPath & "\*.wav")
    If waveOutGetNumDevs() = 0 Then
        ' Pas d'unité de son disponible
        mnuSounds(0).Caption = "Pas de carte son disponible pour les fichiers .wav "
    ElseIf SoundFile = "" Then
        ' Aucun fichier son dans le dossier Windows.
        Exit Sub
    Else
        mnuSounds(0).Caption = Left(SoundFile, InStr(1, SoundFile, ".") - 1)
        mnuSounds(0).Enabled = True
        i = 1
        Do
            SoundFile = Dir
            If SoundFile = "" Then Exit Do
            Load mnuSounds(i)
            mnuSounds(i).Caption = Left(SoundFile, InStr(1, SoundFile, ".") - 1)
            i = i + 1
        Loop
    End If
End Sub

Private Sub mnuSounds_Click(Index As Integer)
Dim R As Integer
Const SYNC = 1
    R = sndPlaySound(ByVal CStr(WindowsDirectory() & "\" & mnuSounds(Index).Caption & ".wav"), SYNC)
End Sub

Private Sub mnuSysInfo_Click(Index As Integer)
Static iPrevious As Integer
    
    If Index <> 5 Then
        
        If VisibleFrame Is Nothing Then
            frmCallDlls.fraInfo(0).Visible = False
        Else
            VisibleFrame.Visible = False
        End If
        frmCallDlls.fraInfo(Index + 1).Visible = True
        Set VisibleFrame = frmCallDlls.fraInfo(Index + 1)
    Else
        mnuSysInfo(Index).Checked = Not mnuSysInfo(Index).Checked
        
        If mnuSysInfo(Index).Checked Then
           SetWindowPos frmCallDlls.hWnd, HWND_TOPMOST, frmCallDlls.Left / 15, _
                        frmCallDlls.Top / 15, frmCallDlls.Width / 15, _
                        frmCallDlls.Height / 15, SWP_NOACTIVATE Or SWP_SHOWWINDOW
        Else
           SetWindowPos frmCallDlls.hWnd, HWND_NOTOPMOST, frmCallDlls.Left / 15, _
                        frmCallDlls.Top / 15, frmCallDlls.Width / 15, _
                        frmCallDlls.Height / 15, SWP_NOACTIVATE Or SWP_SHOWWINDOW
        End If
    End If
    If Index = 3 Then
        frmCallDlls.fraInfo(4).Visible = False
    End If

End Sub

