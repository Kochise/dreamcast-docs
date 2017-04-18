VERSION 5.00
Object = "{5E9E78A0-531B-11CF-91F6-C2863C385E30}#1.0#0"; "MSFLXGRD.OCX"
Begin VB.Form Form1 
   Caption         =   "Produits"
   ClientHeight    =   5715
   ClientLeft      =   1665
   ClientTop       =   1545
   ClientWidth     =   6585
   LinkTopic       =   "Form1"
   ScaleHeight     =   5715
   ScaleWidth      =   6585
   Begin VB.CommandButton Command2 
      Caption         =   "Quitter"
      Height          =   375
      Left            =   5160
      TabIndex        =   3
      Top             =   5160
      Width           =   1215
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Effacer"
      Height          =   375
      Left            =   3480
      TabIndex        =   2
      Top             =   5160
      Width           =   1215
   End
   Begin VB.Data Data1 
      Caption         =   "Data1"
      Connect         =   "Access"
      DatabaseName    =   "C:\Program Files\Microsoft Visual Studio\VB98\Nwind.mdb"
      DefaultCursorType=   0  'DefaultCursor
      DefaultType     =   2  'UseODBC
      Exclusive       =   0   'False
      Height          =   375
      Left            =   240
      Options         =   0
      ReadOnly        =   0   'False
      RecordsetType   =   1  'Dynaset
      RecordSource    =   "Produits"
      Top             =   4440
      Width           =   6135
   End
   Begin VB.ListBox List1 
      Height          =   1230
      Left            =   240
      TabIndex        =   1
      Top             =   3000
      Width           =   6015
   End
   Begin MSFlexGridLib.MSFlexGrid MSFlexGrid1 
      Bindings        =   "Form1.frx":0000
      Height          =   2535
      Left            =   240
      TabIndex        =   0
      Top             =   240
      Width           =   6015
      _ExtentX        =   10610
      _ExtentY        =   4471
      _Version        =   393216
      AllowUserResizing=   1
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Command1_Click()
    List1.Clear         ' Efface le contenu du contrôle ListBox.
End Sub

Private Sub Command2_Click()
    Unload Form1
    End                 ' Termine l'application.
End Sub

Private Sub Data1_Reposition()
    Data1.Caption = Data1.Recordset("Nom du Produit")
End Sub

Private Sub MSFlexGrid1_DblClick()
    List1.AddItem MSFlexGrid1.Text
End Sub
