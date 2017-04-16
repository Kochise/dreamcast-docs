VERSION 5.00
Object = "{65E121D4-0C60-11d2-A9FC-0000F8754DA1}#2.0#0"; "MSCHRT20.OCX"
Begin VB.Form frmChart 
   Caption         =   "Graphique des revenus"
   ClientHeight    =   5055
   ClientLeft      =   2085
   ClientTop       =   2085
   ClientWidth     =   8160
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   5055
   ScaleWidth      =   8160
   WhatsThisHelp   =   -1  'True
   Begin VB.Frame Frame1 
      Height          =   4935
      Left            =   120
      TabIndex        =   1
      Top             =   0
      Width           =   6615
      Begin MSChart20Lib.MSChart grfRevenue 
         Height          =   4575
         Left            =   120
         OleObjectBlob   =   "frmchart.frx":0000
         TabIndex        =   2
         Top             =   240
         Width           =   6375
      End
   End
   Begin VB.CommandButton cmdClose 
      Caption         =   "&Fermer"
      Default         =   -1  'True
      Height          =   420
      Left            =   6840
      TabIndex        =   0
      Top             =   120
      Width           =   1215
   End
End
Attribute VB_Name = "frmChart"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdClose_Click()
  Unload Me

End Sub

Private Sub Form_Load()
  
  SetGraphData
  
End Sub
Sub SetGraphData()
  Dim strGraphData As String
  Dim vGraphData As Variant
  Dim strSrchString As String * 1
  Dim lStart As Long
  Dim lEnd As Long
  Dim lstrLen As Long
  Dim i As Integer
  Dim j As Integer

  On Error GoTo SetGraphDataError
  Screen.MousePointer = vbHourglass

  ' Demande les résultats des règles d'entreprise.
  goStatusPanel.Text = "Extrait les données du graphique du composant serveur..."
  vGraphData = gobjServer.GetRevenue(CInt(Val(frmRevenue.frmSalesModel.Tag)), _
                                                                CCur(Val(frmRevenue.txtRevParm(0).Tag)), _
                                                                CCur(frmRevenue.txtRevParm(1).Text), _
                                                                CInt(frmRevenue.txtRevParm(2).Text), _
                                                                CLng(frmRevenue.txtRevParm(3).Text), _
                                                                CBool(frmRevenue.chkDiscount.Value), _
                                                                frmRevenue.cboBooks.Text)
 
  grfRevenue.RowCount = Val(frmRevenue.txtRevParm(2).Text)
  grfRevenue.ColumnCount = 2
  grfRevenue.AutoIncrement = True
  
  goStatusPanel.Text = "Dessine les données du graphique..."
  
  For j = 0 To UBound(vGraphData, 2)
    For i = 0 To UBound(vGraphData, 1)
      grfRevenue.Row = i + 1
      grfRevenue.RowLabel = CStr(i + 1)
      grfRevenue.Column = j + 1
      grfRevenue.Data = vGraphData(i, j)
    Next i
  Next j
 
  Screen.MousePointer = vbDefault
  Exit Sub

SetGraphDataError:
  Screen.MousePointer = vbDefault
  MsgBox Error$ & " - " & Str$(Err), vbExclamation, "Erreur dans la procédure SetGraphData"
  Exit Sub

End Sub

