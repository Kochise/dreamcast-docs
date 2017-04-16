VERSION 5.00
Begin VB.Form frmPassThru 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Composant PassThrough"
   ClientHeight    =   660
   ClientLeft      =   5145
   ClientTop       =   3555
   ClientWidth     =   5190
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   660
   ScaleWidth      =   5190
   Begin VB.Label Label1 
      Caption         =   "Composant appelé:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   315
      Left            =   30
      TabIndex        =   1
      Top             =   120
      Width           =   2505
   End
   Begin VB.Label labSvrProgID 
      Caption         =   "labSvrProgID"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   2520
      TabIndex        =   0
      Top             =   120
      Width           =   2535
   End
End
Attribute VB_Name = "frmPassThru"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Form_Load()

#If gbDEBUG Then       ' Code de débogage. Utilisé pour tester sans client externe.
  Dim objPassThruSvr As Object
  Dim objSvr As Object
  Dim bSvrCreated As Integer
  Dim bSuccess As Integer
  On Error GoTo flErr

  Set objPassThruSvr = CreateObject("PassThruProj.PassThruClass")
  bSvrCreated = True
  Set objSvr = objPassThruSvr.RunServer("HelloProj.HelloClass", bSuccess)
  If bSuccess Then MsgBox objSvr.SayHello    ' Indique uniquement lorsque la connexion fonctionne.
  GoTo flExit
  
flErr:
  Resume flExit
  
flExit:
  If bSuccess Then Set objSvr = Nothing
  If bSvrCreated Then Set objPassThruSvr = Nothing
#End If

End Sub

