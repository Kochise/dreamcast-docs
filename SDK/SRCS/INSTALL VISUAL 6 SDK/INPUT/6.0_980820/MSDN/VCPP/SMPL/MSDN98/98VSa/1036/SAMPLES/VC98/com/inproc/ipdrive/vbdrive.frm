VERSION 5.00
Begin VB.Form Form1 
   Appearance      =   0  'Flat
   BackColor       =   &H80000005&
   Caption         =   "InProc Driver"
   ClientHeight    =   2100
   ClientLeft      =   255
   ClientTop       =   5955
   ClientWidth     =   5310
   BeginProperty Font 
      Name            =   "MS Sans Serif"
      Size            =   8.25
      Charset         =   0
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   ForeColor       =   &H80000008&
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   2100
   ScaleWidth      =   5310
   Begin VB.CommandButton Remove 
      Appearance      =   0  'Flat
      Caption         =   "&Remove"
      Height          =   375
      Left            =   3600
      TabIndex        =   8
      Top             =   1200
      Width           =   1335
   End
   Begin VB.CommandButton Add 
      Appearance      =   0  'Flat
      Caption         =   "&Add"
      Height          =   375
      Left            =   3600
      TabIndex        =   7
      Top             =   720
      Width           =   1335
   End
   Begin VB.CommandButton Lookup 
      Appearance      =   0  'Flat
      Caption         =   "&Lookup"
      Height          =   375
      Left            =   3600
      TabIndex        =   6
      Top             =   240
      Width           =   1335
   End
   Begin VB.TextBox MapTo 
      Appearance      =   0  'Flat
      Height          =   285
      Left            =   840
      TabIndex        =   1
      Top             =   720
      Width           =   2055
   End
   Begin VB.TextBox MapFrom 
      Appearance      =   0  'Flat
      Height          =   285
      Left            =   840
      TabIndex        =   0
      Top             =   240
      Width           =   2055
   End
   Begin VB.Label MapCount 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   960
      TabIndex        =   5
      Top             =   1320
      Width           =   1935
   End
   Begin VB.Label Label3 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Count:"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   240
      TabIndex        =   4
      Top             =   1320
      Width           =   615
   End
   Begin VB.Label Label2 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "&To:"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   240
      TabIndex        =   3
      Top             =   720
      Width           =   495
   End
   Begin VB.Label Label1 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "&From:"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   240
      TabIndex        =   2
      Top             =   240
      Width           =   615
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim map As Object

Private Sub Add_Click()
    map.SetAt MapFrom.Text, MapTo.Text
    Lookup_Click
    MapCount.Caption = map.Count
End Sub

Private Sub Form_Load()
    Set map = CreateObject("mfc.inproc.varmap")
End Sub

Private Sub Form_Unload(Cancel As Integer)
    Set map = Nothing
End Sub

Private Sub Lookup_Click()
    temp = map.Item(MapFrom.Text)
    MapTo.Text = temp
End Sub

Private Sub Remove_Click()
    map.RemoveKey MapFrom.Text
    MapTo.Text = "<nothing>"
    MapCount.Caption = map.Count
End Sub
