VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Classes liées aux données"
   ClientHeight    =   1815
   ClientLeft      =   1665
   ClientTop       =   1545
   ClientWidth     =   3420
   LinkTopic       =   "Form1"
   ScaleHeight     =   1815
   ScaleWidth      =   3420
   Begin VB.CommandButton cmdCycle 
      Caption         =   "Cycle"
      Height          =   375
      Left            =   1200
      TabIndex        =   1
      Top             =   1200
      Width           =   1095
   End
   Begin VB.TextBox txtConsumer 
      Height          =   375
      Left            =   840
      TabIndex        =   0
      Top             =   360
      Width           =   1815
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private objSource As MySource
Private objBindingCollection As BindingCollection
Private objConsumer As MyConsumer

Private Sub cmdCycle_Click()
    ' Appele la méthode Cycle de la source de données.
    objSource.Cycle
End Sub


Private Sub Form_Load()
    Set objSource = New MySource
    Set objBindingCollection = New BindingCollection
    Set objConsumer = New MyConsumer
    
    ' Affecte la classe source à la propriété DataSource
    ' de la collection Binding.
    Set objBindingCollection.DataSource = objSource
    ' Ajoute une liaison.
    objBindingCollection.Add txtConsumer, "Text", "Directory"
    objBindingCollection.Add objConsumer, "DirName", "Directory"
End Sub
