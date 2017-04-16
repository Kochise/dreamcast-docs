VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form frmOpenDlg 
   Caption         =   "Ouvrir fichier"
   ClientHeight    =   2535
   ClientLeft      =   1080
   ClientTop       =   1485
   ClientWidth     =   2865
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   2535
   ScaleWidth      =   2865
   Begin MSComDlg.CommonDialog dlgOpenFile 
      Left            =   1680
      Top             =   1200
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      FilterIndex     =   570
      FontSize        =   8.49728e-19
   End
End
Attribute VB_Name = "frmOpenDlg"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub Form_Load()

End Sub
