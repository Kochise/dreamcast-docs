VERSION 5.00
Begin VB.Form frmClient 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   " Interface Client"
   ClientHeight    =   1485
   ClientLeft      =   2775
   ClientTop       =   2865
   ClientWidth     =   3255
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   1485
   ScaleWidth      =   3255
   Begin VB.CommandButton cmdClose 
      Caption         =   "Fermer"
      Default         =   -1  'True
      Height          =   300
      Left            =   285
      TabIndex        =   0
      Top             =   1020
      Width           =   1050
   End
   Begin VB.CommandButton cmdUpdate 
      Caption         =   "Mettre à jour"
      Height          =   300
      Left            =   1740
      TabIndex        =   1
      Top             =   1020
      Width           =   1050
   End
   Begin VB.Label labTime 
      BackColor       =   &H00C0C0C0&
      Caption         =   "labTime"
      Height          =   210
      Left            =   2325
      TabIndex        =   5
      Top             =   225
      Width           =   840
   End
   Begin VB.Label labDate 
      BackColor       =   &H00C0C0C0&
      Caption         =   "labDate"
      Height          =   210
      Left            =   720
      TabIndex        =   4
      Top             =   225
      Width           =   840
   End
   Begin VB.Label lab1 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Heure:"
      Height          =   270
      Index           =   1
      Left            =   1725
      TabIndex        =   3
      Top             =   225
      Width           =   570
   End
   Begin VB.Label lab1 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Date:"
      Height          =   270
      Index           =   0
      Left            =   255
      TabIndex        =   2
      Top             =   225
      Width           =   465
   End
End
Attribute VB_Name = "frmClient"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub cmdClose_Click()
  Unload frmClient
End Sub

Private Sub cmdUpdate_Click()
Dim objInterface As Object
Dim objServer As Object
On Error GoTo cuError

' Utilise une interface indirecte pour maintenir l'intégrité
' des instances des classes du projet.
Set objInterface = CreateObject("InterfaceProj.ServerInterface")

Set objServer = objInterface.objGetClassInstance("InterfaceDateClass")
labDate.Caption = objServer.GetDate

Set objServer = Nothing
Set objServer = objInterface.objGetClassInstance("InterfaceTimeClass")
labTime.Caption = objServer.GetTime

GoTo cuExit

cuError:
MsgBox Error$
Resume cuExit

cuExit:
Set objServer = Nothing
Set objInterface = Nothing
End Sub

Private Sub Form_Load()
  cmdUpdate_Click
End Sub

