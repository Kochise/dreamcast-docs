VERSION 5.00
Object = "{C1A8AF28-1257-101B-8FB0-0020AF039CA3}#1.1#0"; "MCI32.OCX"
Begin VB.Form frmWave 
   BorderStyle     =   1  'Fixed Single
   ClientHeight    =   1380
   ClientLeft      =   1350
   ClientTop       =   4230
   ClientWidth     =   5715
   LinkMode        =   1  'Source
   LinkTopic       =   "Form4"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1380
   ScaleWidth      =   5715
   Begin VB.HScrollBar hsbWave 
      Height          =   255
      Left            =   240
      Max             =   100
      TabIndex        =   0
      Top             =   360
      Width           =   5295
   End
   Begin MCI.MMControl mciWave 
      Height          =   495
      Left            =   1080
      TabIndex        =   3
      Top             =   720
      Width           =   3540
      _ExtentX        =   6244
      _ExtentY        =   873
   End
   Begin VB.Label lblWaveSec 
      BeginProperty Font 
         Name            =   "Courier"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   4800
      TabIndex        =   2
      Top             =   0
      Width           =   735
   End
   Begin VB.Label lblWave 
      BeginProperty Font 
         Name            =   "Courier"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   360
      TabIndex        =   1
      Top             =   0
      Width           =   615
   End
   Begin VB.Menu AL_FILE 
      Caption         =   "&Fichier"
      Begin VB.Menu AI_OPEN 
         Caption         =   "&Ouvrir..."
      End
      Begin VB.Menu AI_SEPARATOR 
         Caption         =   "-"
      End
      Begin VB.Menu AI_EXIT 
         Caption         =   "&Quitter"
      End
   End
End
Attribute VB_Name = "frmWave"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Const conInterval = 50
Const conIntervalPlus = 55

Dim CurrentValue As Double

Private Sub AI_EXIT_Click()
    Unload frmWave
End Sub

Private Sub AI_OPEN_Click()
    Dim msec As Double

    ' Définit le nombre de millisecondes entre deux
    ' événements StatusUpdate successifs.
    mciWave.UpdateInterval = 0

    ' Affiche la boîte de dialogue Ouverture.
    frmOpenDlg.dlgOpenFile.FilterIndex = 1
    frmOpenDlg.dlgOpenFile.Flags = vbOFNReadOnly Or vbOFNFileMustExist
    frmOpenDlg.dlgOpenFile.CancelError = True
    frmOpenDlg.dlgOpenFile.filename = ""
    On Error Resume Next
    frmOpenDlg.dlgOpenFile.ShowOpen

    If Err <> 0 Then
        ' Aucun fichier sélectionné dans la boîte de dialogue Ouverture.
        Exit Sub
    End If

    ' Si le périphérique est ouvert, le ferme.
    If Not mciWave.Mode = vbMCIModeNotOpen Then
        mciWave.Command = "Close"
    End If

    ' Ouvre le périphérique avec le nouveau nom de fichier.
    mciWave.filename = frmOpenDlg.dlgOpenFile.filename
    On Error GoTo MCI_ERROR
    mciWave.Command = "Open"
    On Error GoTo 0
    Caption = DialogCaption + mciWave.filename
    
    ' Définit les étiquettes de temps de la feuille.
    mciWave.TimeFormat = vbMCIFormatMilliseconds
    lblWave.Caption = "0.0"
    msec = (CDbl(mciWave.Length) / 1000)
    lblWaveSec.Caption = Format$(msec, "0.00")

    ' Définit les valeurs du contrôle HScrollBar.
    hsbWave.value = 0
    CurrentValue = 0#
    Exit Sub

MCI_ERROR:
    DisplayErrorMessageBox
    Resume MCI_EXIT

MCI_EXIT:
    Unload frmWave
    
End Sub

Private Sub Form_Load()
    ' Force le contrôle multimédia MCI à finir avant de retourner
    ' à l'application.
    frmWave.mciWave.Wait = True
End Sub

Private Sub Form_Unload(Cancel As Integer)
    frmMCITest.Show
End Sub

Private Sub mciWave_PauseClick(Cancel As Integer)
    ' Définit le nombre de millisecondes entre deux
    ' événements StatusUpdate successifs.
    mciWave.UpdateInterval = 0
End Sub

Private Sub mciWave_PlayClick(Cancel As Integer)
    ' Définit le nombre de millisecondes entre deux
    ' événements StatusUpdate successifs.
    mciWave.UpdateInterval = conInterval
End Sub

Private Sub mciWave_PrevClick(Cancel As Integer)
    ' Définit le nombre de millisecondes entre deux
    ' événements StatusUpdate successifs.
    mciWave.UpdateInterval = 0
    
    ' Réinitialise les valeurs du contrôle HScrollBar.
    hsbWave.value = 0
    CurrentValue = 0#
    
    mciWave.Command = "Prev"
End Sub

Private Sub mciWave_StatusUpdate()
    Dim value As Integer

    ' Si le périphérique n'est pas en service, le réinitialise au début.
    If Not mciWave.Mode = vbMCIModePlay Then
        hsbWave.value = hsbWave.Max
        mciWave.UpdateInterval = 0
        Exit Sub
    End If
    
    ' Détermine la longueur de l'enregistrement qui a été joué.
    ' Définit pour le contrôle HScrollBar une valeur comprise
    ' entre 0 et 100.
    CurrentValue = CurrentValue + conIntervalPlus
    value = CInt((CurrentValue / mciWave.Length) * 100)
    
    If value > hsbWave.Max Then
        value = 100
    End If

    hsbWave.value = value
End Sub

