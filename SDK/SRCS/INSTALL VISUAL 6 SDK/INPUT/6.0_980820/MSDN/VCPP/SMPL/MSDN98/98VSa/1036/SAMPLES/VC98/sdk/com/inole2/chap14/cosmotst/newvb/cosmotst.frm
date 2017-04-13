VERSION 4.00
Begin VB.Form Form1 
   Caption         =   "Test Cosmo"
   ClientHeight    =   3000
   ClientLeft      =   9420
   ClientTop       =   1500
   ClientWidth     =   4800
   BeginProperty Font 
      name            =   "MS Sans Serif"
      charset         =   1
      weight          =   700
      size            =   7.8
      underline       =   0   'False
      italic          =   0   'False
      strikethrough   =   0   'False
   EndProperty
   Height          =   3348
   Left            =   9384
   LinkTopic       =   "Form1"
   ScaleHeight     =   3000
   ScaleWidth      =   4800
   Top             =   1188
   Width           =   4872
   Begin VB.CommandButton CreateFigure 
      Caption         =   "C&reate Figure"
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   1
         weight          =   700
         size            =   7.8
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   120
      TabIndex        =   9
      Top             =   2280
      Width           =   1455
   End
   Begin VB.CommandButton ReleaseFigure 
      Caption         =   "Release F&igure"
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   1
         weight          =   700
         size            =   7.8
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   3240
      TabIndex        =   8
      Top             =   1560
      Width           =   1455
   End
   Begin VB.CommandButton TestFigure 
      Caption         =   "Test Fi&gure"
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   1
         weight          =   700
         size            =   7.8
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   1680
      TabIndex        =   7
      Top             =   1560
      Width           =   1455
   End
   Begin VB.CommandButton GetFigure 
      Caption         =   "Get &Figure"
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   1
         weight          =   700
         size            =   7.8
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   120
      TabIndex        =   6
      Top             =   1560
      Width           =   1455
   End
   Begin VB.CommandButton GetCollection 
      Caption         =   "&Get Collection"
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   1
         weight          =   700
         size            =   7.8
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   120
      TabIndex        =   5
      Top             =   840
      Width           =   1455
   End
   Begin VB.CommandButton ReleaseCollection 
      Caption         =   "Release C&oll."
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   1
         weight          =   700
         size            =   7.8
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   3240
      TabIndex        =   4
      Top             =   840
      Width           =   1455
   End
   Begin VB.CommandButton TestCollection 
      Caption         =   "Test &Collection"
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   1
         weight          =   700
         size            =   7.8
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   1680
      TabIndex        =   3
      Top             =   840
      Width           =   1455
   End
   Begin VB.CommandButton QuitApp 
      Caption         =   "&Quit App"
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   1
         weight          =   700
         size            =   7.8
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   3240
      TabIndex        =   2
      Top             =   120
      Width           =   1455
   End
   Begin VB.CommandButton CreateApp 
      Caption         =   "&Create App"
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   1
         weight          =   700
         size            =   7.8
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   120
      TabIndex        =   1
      Top             =   120
      Width           =   1455
   End
   Begin VB.CommandButton TestApp 
      Caption         =   "&Test App"
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   1
         weight          =   700
         size            =   7.8
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   1680
      TabIndex        =   0
      Top             =   120
      Width           =   1455
   End
End
Attribute VB_Name = "Form1"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Dim Cosmo As Object
Dim Figures As Object
Dim CosmoFigure As Object
Dim fCreatedObject As Integer

Private Sub CreateApp_Click()
    Set Cosmo = CreateObject("Cosmo.Application.2")
    CreateApp.Enabled = False
    QuitApp.Enabled = True
    TestApp.Enabled = True

    CreateFigure.Enabled = False
    GetCollection.Enabled = True

    fCreatedObject = False
End Sub

Private Sub CreateFigure_Click()
    Set CosmoFigure = CreateObject("Cosmo.Figure.2")

    CreateApp.Enabled = False
    QuitApp.Enabled = False
    TestApp.Enabled = False

    GetCollection.Enabled = False
    TestCollection.Enabled = False
    GetFigure.Enabled = False
    ReleaseCollection.Enabled = False

    CreateFigure.Enabled = False
    TestFigure.Enabled = True
    ReleaseFigure.Enabled = True

    fCreatedObject = True

    CosmoFigure.Application.Visible = True
End Sub

Private Sub Form_Load()
    QuitApp.Enabled = False
    TestApp.Enabled = False
    GetCollection.Enabled = False
    TestCollection.Enabled = False
    ReleaseCollection.Enabled = False

    GetFigure.Enabled = False
    TestFigure.Enabled = False
    ReleaseFigure.Enabled = False

    fCreatedObject = False
End Sub

Private Sub GetCollection_Click()
    Set Figures = Cosmo.Figures
    
    GetCollection.Enabled = False
    TestCollection.Enabled = True
    ReleaseCollection.Enabled = True

    GetFigure.Enabled = True
End Sub

Private Sub GetFigure_Click()
    Set CosmoFigure = Figures.Add
    
    CreateFigure.Enabled = False
    GetFigure.Enabled = False
    TestFigure.Enabled = True
    ReleaseFigure.Enabled = True
End Sub

Private Sub QuitApp_Click()
    'You can use either Quit method or set the
    'object variable to "Nothing" to destroy the
    'object and terminate the application
    Cosmo.Quit
    Set Cosmo = Nothing

    GetCollection.Enabled = False

    CreateApp.Enabled = True
    QuitApp.Enabled = False
    TestApp.Enabled = False
    CreateFigure.Enabled = True
End Sub

Private Sub ReleaseCollection_Click()
    Set Figures = Nothing
    GetCollection.Enabled = True
    TestCollection.Enabled = False
    ReleaseCollection.Enabled = False

    GetFigure.Enabled = False
End Sub

Private Sub ReleaseFigure_Click()
    CosmoFigure.Close (True)
    Set CosmoFigure = Nothing
    
    If (fCreatedObject) Then
        CreateFigure.Enabled = True
    Else
        GetFigure.Enabled = True
    End If

    TestFigure.Enabled = False
    ReleaseFigure.Enabled = False
End Sub

Private Sub TestApp_Click()
    Dim Copy As Object

    'Show the window and hide it to show position
    Cosmo.Visible = True
    Cosmo.Visible = False
    
    'Move and resize the window and show it again
    Cosmo.Left = 35
    Cosmo.Top = 35
    Cosmo.Width = 450
    Cosmo.Height = 450

    Cosmo.Visible = True
    
    Debug.Print "Left=" + Str$(Cosmo.Left)
    Debug.Print "Top=" + Str$(Cosmo.Top)
    Debug.Print "Width=" + Str$(Cosmo.Width)
    Debug.Print "Height=" + Str$(Cosmo.Height)

    Debug.Print "Status Bar=" + Cosmo.StatusBar
    Cosmo.StatusBar = "This is a string from VB"
    Debug.Print "Status Bar=" + Cosmo.StatusBar

    Debug.Print "FullName=" + Cosmo.FullName
    Debug.Print "Name=" + Cosmo.Name
    Debug.Print "Path=" + Cosmo.Path
    Debug.Print "Caption=" + Cosmo.Caption

    Set Copy = Cosmo    'Should get 'Appication' property
    Debug.Print Copy.Name
    Set Copy = Nothing  'Just calls Release, no shutdown
End Sub

Private Sub TestCollection_Click()
    Dim Fig1 As Object
    Dim Fig2 As Object
    Dim Fig3 As Object
    Dim Fig4 As Object
    Dim FiguresCopy As Object

    Set Fig1 = Figures.Open("c:\inole\chap14\cosmotst\newvb\samp1.cos")
    Fig1.Visible = True

    Set Fig2 = Figures.Add
    Fig2.Visible = True

    Set Fig3 = Figures.Open("c:\inole\chap14\cosmotst\newvb\samp2.cos")
    Fig3.Visible = True

    Debug.Print "Figures.Application=" + Figures.Application.Caption
    Debug.Print "Figures.Parent=" + Figures.Parent.Name

    cFigs = Figures.Count
    Debug.Print "Number of Figures=" + Str$(cFigs)
    
    Set FiguresCopy = Figures
    Set Fig4 = FiguresCopy.Item("c:\inole\chap14\cosmotst\newvb\samp1.cos")
    Debug.Print "Item from pathname: " + Fig4.Name
    Set Fig4 = Nothing
    Set FiguresCopy = Nothing

    'Closes all documents, rendering Fig1, 2, and 3 invalid
    Figures.Close
End Sub

Private Sub TestFigure_Click()
    Dim FigTemp As Object
    
    CosmoFigure.Visible = True
    CosmoFigure.Left = 10
    CosmoFigure.Width = 300
    CosmoFigure.Top = 10
    CosmoFigure.Height = 320

    CosmoFigure.Visible = False
    CosmoFigure.Visible = True

    CosmoFigure.AddPoint 2000, 2000
    CosmoFigure.AddPoint 30000, 30000
    CosmoFigure.AddPoint 30000, 2000
    CosmoFigure.AddPoint 2000, 30000
    CosmoFigure.AddPoint 14880, 7522
    CosmoFigure.AddPoint 25463, 7823
    CosmoFigure.AddPoint 3241, 21894
    CosmoFigure.RemovePoint

    CosmoFigure.BackColor = RGB(0, 0, 255)
    CosmoFigure.LineColor = RGB(255, 255, 255)

    Debug.Print CosmoFigure.BackColor
    Debug.Print CosmoFigure.LineColor
    Debug.Print CosmoFigure.LineStyle

    CosmoFigure.LineStyle = 3

    CosmoFigure.Cut
    CosmoFigure.Paste

    Set FigTemp = CosmoFigure.Application.Figures.Add
    FigTemp.Visible = True
    FigTemp.Activate
    CosmoFigure.Activate
    CosmoFigure.Copy
    FigTemp.Activate
    FigTemp.Paste
    FigTemp.Close (False)
    Set FigTemp = Nothing

    CosmoFigure.Activate
    CosmoFigure.SaveAs ("c:\temp\temp.cos")
    CosmoFigure.RemovePoint
    CosmoFigure.RevertToSaved
    CosmoFigure.LineStyle = 0
    CosmoFigure.Save

    CosmoFigure.RemovePoint
    CosmoFigure.RemovePoint
    CosmoFigure.RemovePoint

    CosmoFigure.Import ("c:\inole\chap14\cosmotst\newvb\samp1.cos")

    Set FigTemp = CosmoFigure.Application.ActiveFigure
    Debug.Print "Cosmo.ActiveFigure=" + FigTemp.Name
    Set FigTemp = Nothing
End Sub
