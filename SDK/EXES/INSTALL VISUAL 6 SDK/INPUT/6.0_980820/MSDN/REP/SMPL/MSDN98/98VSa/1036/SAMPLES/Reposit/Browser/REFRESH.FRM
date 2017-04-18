VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.1#0"; "comctl32.ocx"
Begin VB.Form frmRefresh 
   Caption         =   "Loading ..."
   ClientHeight    =   1725
   ClientLeft      =   2880
   ClientTop       =   5505
   ClientWidth     =   5970
   LinkTopic       =   "Form2"
   ScaleHeight     =   1725
   ScaleWidth      =   5970
   Begin ComctlLib.ProgressBar pbLoading 
      Height          =   495
      Left            =   360
      TabIndex        =   1
      Top             =   1080
      Width           =   5295
      _ExtentX        =   9340
      _ExtentY        =   873
   End
   Begin VB.Label lblMessage 
      Height          =   735
      Left            =   240
      TabIndex        =   0
      Top             =   240
      Width           =   5535
   End
End
Attribute VB_Name = "frmRefresh"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Form_Load()
    pbLoading.Value = 0
End Sub

Public Property Let Steps(i As Integer)
    pbLoading.Max = i
    pbLoading.Value = 0
End Property

Public Sub StepIt()
    pbLoading.Value = pbLoading.Value + 1
    
    If pbLoading.Value = pbLoading.Max Then
        Unload Me
    End If
End Sub

Public Sub Report(msg As String)
    lblMessage.Caption = msg
    lblMessage.Refresh
End Sub

