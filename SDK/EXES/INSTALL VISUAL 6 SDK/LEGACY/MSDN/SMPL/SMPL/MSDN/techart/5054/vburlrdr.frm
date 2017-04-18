VERSION 5.00
Begin VB.Form MainForm 
   Caption         =   "URL Reader"
   ClientHeight    =   2796
   ClientLeft      =   4200
   ClientTop       =   3864
   ClientWidth     =   3744
   LinkTopic       =   "Form1"
   ScaleHeight     =   2796
   ScaleWidth      =   3744
   Begin VB.TextBox OutputFilespec 
      Height          =   372
      Left            =   960
      TabIndex        =   6
      Text            =   "c:\mscom.txt"
      Top             =   600
      Width           =   2532
   End
   Begin VB.TextBox URLSpec 
      Height          =   372
      Left            =   960
      TabIndex        =   4
      Text            =   "http://www.microsoft.com/"
      Top             =   120
      Width           =   2532
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Exit"
      Height          =   372
      Left            =   2640
      TabIndex        =   2
      Top             =   2280
      Width           =   972
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Read URL"
      Default         =   -1  'True
      Height          =   372
      Left            =   120
      TabIndex        =   0
      Top             =   2280
      Width           =   972
   End
   Begin VB.Label ActionMsg 
      Alignment       =   2  'Center
      BorderStyle     =   1  'Fixed Single
      Height          =   372
      Left            =   120
      TabIndex        =   7
      Top             =   1080
      Width           =   3492
   End
   Begin VB.Label Label2 
      Caption         =   "Outut Filespec"
      Height          =   372
      Left            =   120
      TabIndex        =   5
      Top             =   600
      Width           =   732
      WordWrap        =   -1  'True
   End
   Begin VB.Label Label1 
      Caption         =   "URL to read"
      Height          =   372
      Left            =   120
      TabIndex        =   3
      Top             =   120
      Width           =   732
      WordWrap        =   -1  'True
   End
   Begin VB.Label Status 
      Alignment       =   2  'Center
      BorderStyle     =   1  'Fixed Single
      Height          =   372
      Left            =   120
      TabIndex        =   1
      Top             =   1560
      Width           =   3492
   End
End
Attribute VB_Name = "MainForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim VBUrlReaderClass As UrlTools
Attribute VBUrlReaderClass.VB_VarHelpID = -1

Private Sub Command1_Click()

    Dim iCount As Long
    
    Set VBUrlReaderClass = New UrlTools
    
    ActionMsg = "Reading URL on separate thread"
    DoEvents
    
    VBUrlReaderClass.Read URLSpec, OutputFilespec
    
    ActionMsg = "URL being read on separate thread"
    DoEvents
    
    ActionMsg = "Performing simutaneous calculations"
    DoEvents
    
    iCount = 0
    bFinished = False
    Do While Not bFinished
        Status = Sqr(iCount)
        DoEvents
        iCount = iCount + 1
    Loop
    
    ActionMsg = "Event occured...stopping calculcations"
    DoEvents

End Sub

Private Sub Command2_Click()
    
    Set VBUrlReaderClass = Nothing
    bFinished = True
    Unload Me
    End

End Sub
