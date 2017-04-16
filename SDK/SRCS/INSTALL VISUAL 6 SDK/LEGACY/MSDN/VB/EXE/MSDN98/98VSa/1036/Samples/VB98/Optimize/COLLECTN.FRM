VERSION 5.00
Object = "{831FDD16-0C5C-11d2-A9FC-0000F8754DA1}#1.1#0"; "COMCTL32.OCX"
Begin VB.Form frmCollection 
   Caption         =   "Collections"
   ClientHeight    =   5940
   ClientLeft      =   4320
   ClientTop       =   1755
   ClientWidth     =   5955
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   5940
   ScaleWidth      =   5955
   Begin VB.CommandButton cmdType 
      Caption         =   "Instruction For Next"
      Height          =   450
      HelpContextID   =   1
      Index           =   6
      Left            =   120
      TabIndex        =   8
      Top             =   4980
      Width           =   2415
   End
   Begin VB.CommandButton cmdType 
      Caption         =   "Instruction For Each"
      Height          =   450
      Index           =   5
      Left            =   120
      TabIndex        =   7
      Top             =   4485
      Width           =   2415
   End
   Begin VB.TextBox txtLoopCount 
      Height          =   320
      Index           =   2
      Left            =   4725
      TabIndex        =   9
      Text            =   "2000"
      Top             =   4050
      Width           =   1150
   End
   Begin VB.CommandButton cmdType 
      Caption         =   "Extraction par index"
      Height          =   450
      HelpContextID   =   1
      Index           =   4
      Left            =   120
      TabIndex        =   5
      Top             =   3255
      Width           =   2415
   End
   Begin VB.CommandButton cmdType 
      Caption         =   "Extraction par clé"
      Height          =   450
      Index           =   3
      Left            =   120
      TabIndex        =   4
      Top             =   2760
      Width           =   2415
   End
   Begin VB.TextBox txtLoopCount 
      Height          =   320
      Index           =   1
      Left            =   4725
      TabIndex        =   6
      Text            =   "2000"
      Top             =   2325
      Width           =   1150
   End
   Begin VB.CommandButton cmdType 
      Caption         =   "Ajoute après"
      Height          =   450
      HelpContextID   =   1
      Index           =   2
      Left            =   120
      TabIndex        =   2
      Top             =   1500
      Width           =   2415
   End
   Begin VB.TextBox txtLoopCount 
      Height          =   320
      Index           =   0
      Left            =   4725
      TabIndex        =   3
      Text            =   "1000"
      Top             =   75
      Width           =   1150
   End
   Begin VB.CommandButton cmdType 
      Caption         =   "Ajoute un élément"
      Height          =   450
      Index           =   0
      Left            =   120
      TabIndex        =   0
      Top             =   510
      Width           =   2415
   End
   Begin VB.CommandButton cmdType 
      Caption         =   "Ajoute avant"
      Height          =   450
      HelpContextID   =   1
      Index           =   1
      Left            =   120
      TabIndex        =   1
      Top             =   1005
      Width           =   2415
   End
   Begin MSComCtlLib.ProgressBar ProgBar 
      Height          =   195
      Left            =   2880
      TabIndex        =   21
      Top             =   5745
      Width           =   2700
      _ExtentX        =   4763
      _ExtentY        =   344
      _Version        =   327680
      Appearance      =   1
      MouseIcon       =   "Collectn.frx":0000
   End
   Begin MSComCtlLib.StatusBar StatusBar 
      Align           =   2  'Align Bottom
      Height          =   270
      Left            =   0
      TabIndex        =   20
      Top             =   5670
      Width           =   5955
      _ExtentX        =   10504
      _ExtentY        =   476
      SimpleText      =   ""
      _Version        =   327680
      BeginProperty Panels {0713E89E-850A-101B-AFC0-4210102A8DA7} 
         NumPanels       =   2
         BeginProperty Panel1 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Object.Width           =   4939
            MinWidth        =   4939
            TextSave        =   ""
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
         BeginProperty Panel2 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Object.Width           =   4904
            MinWidth        =   4904
            TextSave        =   ""
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
      EndProperty
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      MouseIcon       =   "Collectn.frx":001C
   End
   Begin VB.Label lblResult 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BackStyle       =   0  'Transparent
      Caption         =   "0,00 sec."
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   6
      Left            =   4725
      TabIndex        =   19
      Top             =   5085
      Width           =   1155
   End
   Begin VB.Label lblResult 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BackStyle       =   0  'Transparent
      Caption         =   "0,00 sec."
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   5
      Left            =   4725
      TabIndex        =   18
      Top             =   4590
      Width           =   1155
   End
   Begin VB.Label lblTitle 
      Appearance      =   0  'Flat
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFFF&
      BackStyle       =   0  'Transparent
      Caption         =   "Instructions For Each et For Next"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   300
      Index           =   2
      Left            =   135
      TabIndex        =   17
      Top             =   4050
      Width           =   4020
   End
   Begin VB.Line Line1 
      BorderColor     =   &H00808080&
      Index           =   0
      X1              =   0
      X2              =   7335
      Y1              =   3900
      Y2              =   3900
   End
   Begin VB.Label lblResult 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BackStyle       =   0  'Transparent
      Caption         =   "0,00 sec."
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   4
      Left            =   4725
      TabIndex        =   16
      Top             =   3360
      Width           =   1155
   End
   Begin VB.Label lblResult 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BackStyle       =   0  'Transparent
      Caption         =   "0,00 sec."
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   3
      Left            =   4725
      TabIndex        =   15
      Top             =   2865
      Width           =   1155
   End
   Begin VB.Label lblTitle 
      Appearance      =   0  'Flat
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFFF&
      BackStyle       =   0  'Transparent
      Caption         =   "Extraction d'éléments des collections"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   300
      Index           =   1
      Left            =   135
      TabIndex        =   14
      Top             =   2325
      Width           =   4470
   End
   Begin VB.Line Line1 
      BorderColor     =   &H00808080&
      Index           =   3
      X1              =   0
      X2              =   7335
      Y1              =   2175
      Y2              =   2175
   End
   Begin VB.Label lblResult 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BackStyle       =   0  'Transparent
      Caption         =   "0,00 sec."
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   2
      Left            =   4725
      TabIndex        =   13
      Top             =   1605
      Width           =   1155
   End
   Begin VB.Label lblTitle 
      Appearance      =   0  'Flat
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFFF&
      BackStyle       =   0  'Transparent
      Caption         =   "Ajout d'éléments aux collections"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   300
      Index           =   0
      Left            =   135
      TabIndex        =   12
      Top             =   75
      Width           =   3315
   End
   Begin VB.Label lblResult 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BackStyle       =   0  'Transparent
      Caption         =   "0,00 sec."
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   0
      Left            =   4725
      TabIndex        =   11
      Top             =   615
      Width           =   1155
   End
   Begin VB.Label lblResult 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BackStyle       =   0  'Transparent
      Caption         =   "0,00 sec."
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   1
      Left            =   4725
      TabIndex        =   10
      Top             =   1110
      Width           =   1155
   End
   Begin VB.Line Line1 
      BorderColor     =   &H00FFFFFF&
      BorderWidth     =   2
      Index           =   2
      X1              =   15
      X2              =   7350
      Y1              =   2190
      Y2              =   2175
   End
   Begin VB.Line Line1 
      BorderColor     =   &H00FFFFFF&
      BorderWidth     =   2
      Index           =   1
      X1              =   15
      X2              =   7350
      Y1              =   3915
      Y2              =   3900
   End
End
Attribute VB_Name = "frmCollection"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdType_Click(Index As Integer)
  Dim MyCollection As New Collection
  Dim iCounter As Integer
  Dim dStart As Double, dFinish As Double
  Dim sAnswer As String
  Dim pnlStatus As Panel
  Dim vItem As Variant
  
  Set pnlStatus = frmCollection.StatusBar.Panels(1)
  
  Screen.MousePointer = vbHourglass
  
  dStart = Timer
  Select Case Index
    Case 0  ' Ajoute.
      For iCounter = 0 To Val(txtLoopCount(0).Text) Step 3
        MyCollection.Add Item:=CStr(iCounter), Key:=CStr(iCounter)
        MyCollection.Add Item:=CStr(iCounter + 400), Key:=CStr(iCounter + 1)
        MyCollection.Add Item:=CStr(iCounter + 800), Key:=CStr(iCounter + 2)
      Next iCounter
    
    Case 1 ' Ajoute avant.
      MyCollection.Add Item:=CStr(1), Key:=CStr(1)
      For iCounter = 2 To Val(txtLoopCount(0).Text) Step 3
        MyCollection.Add Item:=CStr(iCounter), Key:=CStr(iCounter), Before:=CStr(iCounter - 1)
        MyCollection.Add Item:=CStr(iCounter + 400), Key:=CStr(iCounter + 1), Before:=CStr(iCounter)
        MyCollection.Add Item:=CStr(iCounter + 800), Key:=CStr(iCounter + 2), Before:=CStr(iCounter)
      Next iCounter
    
    Case 2 ' Ajoute après.
      MyCollection.Add Item:=CStr(1), Key:=CStr(1)
      For iCounter = 2 To Val(txtLoopCount(0).Text) Step 3
        MyCollection.Add Item:=CStr(iCounter), Key:=CStr(iCounter), After:=CStr(iCounter - 1)
        MyCollection.Add Item:=CStr(iCounter + 400), Key:=CStr(iCounter + 1), After:=CStr(iCounter)
        MyCollection.Add Item:=CStr(iCounter + 800), Key:=CStr(iCounter + 2), After:=CStr(iCounter)
      Next iCounter
  
    Case 3  ' Extraction par clé.
      pnlStatus.Text = "Construction de la collection..."
      StatusBar.Refresh
      ProgBar.Max = Val(txtLoopCount(1).Text)
      ' Ajoute d'abord des éléments à la collection.
      For iCounter = 1 To Val(txtLoopCount(1).Text)
        If iCounter Mod 10 = 0 Then ProgBar.Value = iCounter
        MyCollection.Add Item:=CStr(iCounter), Key:=CStr(iCounter)
      Next iCounter
      
      pnlStatus.Text = "Extraction des éléments..."
      StatusBar.Refresh
      dStart = Timer
      For iCounter = MyCollection.Count To 1 Step -1
        sAnswer = MyCollection(CStr(iCounter))
      Next iCounter
      
    Case 4  ' Extraction par index.
      pnlStatus.Text = "Construction de la collection..."
      StatusBar.Refresh
      ProgBar.Max = Val(txtLoopCount(1).Text)
      ' Ajoute d'abord des éléments à la collection.
      For iCounter = 1 To Val(txtLoopCount(1).Text)
        If iCounter Mod 10 = 0 Then ProgBar.Value = iCounter
        MyCollection.Add Item:=CStr(iCounter), Key:=CStr(iCounter)
      Next iCounter
      
      pnlStatus.Text = "Extraction des éléments..."
      StatusBar.Refresh
      dStart = Timer
      For iCounter = MyCollection.Count To 1 Step -1
        sAnswer = MyCollection(iCounter)
      Next iCounter
    
    Case 5  ' Instruction For Each
      pnlStatus.Text = "Construction de la collection..."
      StatusBar.Refresh
      ProgBar.Max = Val(txtLoopCount(2).Text)
      
      For iCounter = 1 To Val(txtLoopCount(2).Text)
        If iCounter Mod 10 = 0 Then ProgBar.Value = iCounter
        MyCollection.Add Item:=CStr(iCounter), Key:=CStr(iCounter)
      Next iCounter
      
      pnlStatus.Text = "Extraction des éléments..."
      StatusBar.Refresh
      
      dStart = Timer
      For Each vItem In MyCollection
        sAnswer = MyCollection(vItem)
      Next vItem
    
    Case 6  ' Instruction For Next
      pnlStatus.Text = "Construction de la collection..."
      StatusBar.Refresh
      ProgBar.Max = Val(txtLoopCount(2).Text)
      
      For iCounter = 1 To Val(txtLoopCount(2).Text)
        If iCounter Mod 10 = 0 Then ProgBar.Value = iCounter
        MyCollection.Add Item:=CStr(iCounter), Key:=CStr(iCounter)
      Next iCounter
      
      pnlStatus.Text = "Itération de la collection..."
      StatusBar.Refresh
      
      dStart = Timer
      For iCounter = 1 To MyCollection.Count
        sAnswer = MyCollection(iCounter)
      Next iCounter
      
  End Select
  
  dFinish = Timer
  Set MyCollection = Nothing
  lblResult(Index).Caption = Format$(dFinish - dStart, "00.00") & " sec."
  pnlStatus.Text = ""
  ProgBar.Value = 0
  Screen.MousePointer = vbDefault

End Sub

Private Sub Form_Load()
  PosForm Me
End Sub


