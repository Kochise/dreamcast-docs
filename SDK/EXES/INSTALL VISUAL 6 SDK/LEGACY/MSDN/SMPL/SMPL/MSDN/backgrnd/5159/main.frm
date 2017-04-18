VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.1#0"; "COMCTL32.OCX"
Begin VB.Form frmMain 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Microsoft Repository"
   ClientHeight    =   5325
   ClientLeft      =   1545
   ClientTop       =   1845
   ClientWidth     =   7920
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5325
   ScaleWidth      =   7920
   ShowInTaskbar   =   0   'False
   Begin ComctlLib.TreeView tvwRepository 
      Height          =   5040
      Left            =   105
      TabIndex        =   0
      Top             =   135
      Width           =   7665
      _ExtentX        =   13520
      _ExtentY        =   8890
      _Version        =   327680
      Indentation     =   300
      LabelEdit       =   1
      LineStyle       =   1
      PathSeparator   =   "."
      Style           =   7
      ImageList       =   "imgSmallIcons"
      Appearance      =   1
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin ComctlLib.ImageList imgSmallIcons 
      Left            =   0
      Top             =   4725
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      _Version        =   327680
      BeginProperty Images {0713E8C2-850A-101B-AFC0-4210102A8DA7} 
         NumListImages   =   4
         BeginProperty ListImage1 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Main.frx":0000
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Main.frx":031A
            Key             =   ""
         EndProperty
         BeginProperty ListImage3 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Main.frx":0634
            Key             =   ""
         EndProperty
         BeginProperty ListImage4 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Main.frx":094E
            Key             =   "FolderClosed"
         EndProperty
      EndProperty
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

'<Private>--------------------------------------------
Private WorkingNode         As Node
Private RepositoryClass     As IRepository
'</Private>-------------------------------------------

Private Sub Form_Initialize()
    Set RepositoryClass = New IRepository
End Sub

Private Sub Form_Load()

    Me.Show
    Me.Refresh
    
    '---- this will start the ball rolling
    Call RepositoryClass.EnumRepository(tvwRepository)

End Sub

Private Sub Form_Terminate()
    Set RepositoryClass = Nothing
End Sub

Private Sub tvwRepository_BeforeLabelEdit(Cancel As Integer)

End Sub
