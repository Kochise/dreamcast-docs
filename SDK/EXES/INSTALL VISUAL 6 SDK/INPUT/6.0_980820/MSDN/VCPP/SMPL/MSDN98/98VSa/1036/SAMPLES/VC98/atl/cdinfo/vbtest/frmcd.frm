VERSION 5.00
Object = "{A393BE4C-2FBD-11D0-B939-000000000000}#1.0#0"; "CDInfo.dll"
Begin VB.Form frmCD 
   Caption         =   "Audio CD"
   ClientHeight    =   7950
   ClientLeft      =   1800
   ClientTop       =   2055
   ClientWidth     =   5700
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   7950
   ScaleWidth      =   5700
   Begin VB.ListBox lstCD 
      Height          =   3375
      Left            =   840
      TabIndex        =   3
      Top             =   3840
      Width           =   3975
   End
   Begin VB.CommandButton cmdExit 
      Cancel          =   -1  'True
      Caption         =   "Exit"
      Height          =   615
      Left            =   3720
      TabIndex        =   2
      Top             =   1200
      Width           =   1575
   End
   Begin VB.CommandButton cmdRead 
      Caption         =   "Read CD"
      Default         =   -1  'True
      Height          =   615
      Left            =   3720
      TabIndex        =   1
      Top             =   360
      Width           =   1575
   End
   Begin CDINFOLibCtl.CCDInfo ctlCD 
      Height          =   2895
      Left            =   360
      OleObjectBlob   =   "frmCD.frx":0000
      TabIndex        =   0
      Top             =   360
      Width           =   2895
   End
End
Attribute VB_Name = "frmCD"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Function GetLength(ByVal nSeconds As Integer) As String
    Dim strLength As String
    strLength = Str(nSeconds \ 60)
    strLength = strLength + ":" + Format(nSeconds Mod 60, "0#")
    GetLength = strLength
End Function

Private Sub cmdExit_Click()
    End
End Sub

Private Sub cmdRead_Click()
    Dim nTracks As Integer, nTrack As Integer
    nTracks = ctlCD.Read
    lstCD.Clear
    If nTracks Then
        For nTrack = 1 To nTracks
            lstCD.AddItem "Track" + Str(nTrack) + Chr(9) + Chr(9) + GetLength(ctlCD.Length(nTrack))
        Next nTrack
    Else
        MsgBox "Couldn't read CD"
    End If
End Sub

Private Sub ctlCD_Click(ByVal nTrack As Integer)
'   This will cause the lstCD_Click event to fire and the Play method called
    lstCD.ListIndex = nTrack - 1
End Sub

Private Sub lstCD_Click()
    ctlCD.Play (lstCD.ListIndex + 1)
End Sub
