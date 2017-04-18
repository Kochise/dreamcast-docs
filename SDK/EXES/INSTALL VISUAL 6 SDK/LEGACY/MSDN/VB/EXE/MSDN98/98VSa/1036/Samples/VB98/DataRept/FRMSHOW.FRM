VERSION 5.00
Object = "{831FDD16-0C5C-11d2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{6FBA474E-43AC-11CE-9A0E-00AA0062BB4C}#1.0#0"; "SYSINFO.OCX"
Begin VB.Form frmShowReport 
   Caption         =   "État"
   ClientHeight    =   2940
   ClientLeft      =   1335
   ClientTop       =   870
   ClientWidth     =   5130
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   ScaleHeight     =   2940
   ScaleWidth      =   5130
   Begin SysInfoLib.SysInfo sysInfo 
      Left            =   3960
      Top             =   720
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
   End
   Begin MSComCtlLib.Toolbar tlbReport 
      Align           =   1  'Align Top
      Height          =   630
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   5130
      _ExtentX        =   9049
      _ExtentY        =   1111
      ButtonWidth     =   1879
      ButtonHeight    =   953
      Appearance      =   1
      _Version        =   393216
      BeginProperty Buttons {66833FE8-8583-11D1-B16A-00C0F0283628} 
         NumButtons      =   4
         BeginProperty Button1 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Caption         =   "Afficher l'état"
            Description     =   "Affiche l'état"
            Object.ToolTipText     =   "Afficher l'état"
         EndProperty
         BeginProperty Button2 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Caption         =   "Exporter l'état"
            Description     =   "Exporte l'état"
            Object.ToolTipText     =   "Exporter l'état"
         EndProperty
         BeginProperty Button3 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Caption         =   "Modèles"
            Description     =   "Imprime les modèles"
            Object.ToolTipText     =   "Imprimer les modèles"
         EndProperty
         BeginProperty Button4 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Caption         =   "Quitter"
            Description     =   "Quitte le programme"
            Object.ToolTipText     =   "Quitter"
         EndProperty
      EndProperty
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&Fichier"
      Begin VB.Menu mnuShow 
         Caption         =   "&Afficher l'état"
      End
      Begin VB.Menu mnuExport 
         Caption         =   "Exporter l'état"
      End
      Begin VB.Menu mnuPrintReport 
         Caption         =   "&Imprimer l'état"
      End
      Begin VB.Menu mnuExit 
         Caption         =   "&Quitter"
      End
   End
End
Attribute VB_Name = "frmShowReport"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit



Private Sub mnuExit_Click()
    While rptNwind.AsyncCount > 0
        DoEvents
    Wend
    Unload rptNwind
    Unload frmShowReport
End Sub

Private Sub mnuExport_Click()
    ' Exporte un état. Le code affiche la boîte de dialogue Exporter l'état.
    ' L'ExportFormat est créé dans l'événement Initialize du Concepteur Data Report.
    
     rptNwind.ExportReport _
     FormatIndexOrKey:="DailyReport", _
     FileName:="C:\Temp\DailyRpt", _
     overwrite:=True, _
     showdialog:=True, _
     range:=rptRangeFromTo, _
     pagefrom:=1, _
     pageto:=3

End Sub

Private Sub mnuPrintReport_Click()
    rptNwind.PrintReport
End Sub

Private Sub mnuShow_Click()
    rptNwind.Show
End Sub

Private Sub tlbReport_ButtonClick(ByVal Button As MSComCtlLib.Button)
    Select Case Button.Caption
    Case "Afficher l'état"
        rptNwind.Show
    Case "Exporter l'état"
        mnuExport_Click
    Case "Modèles"
        ' Imprime tous les modèles.
        Dim i As Integer
        For i = 1 To rptNwind.ExportFormats.Count
            Debug.Print "MODÈLE " & i
            Debug.Print rptNwind.ExportFormats(i).Template
            Debug.Print ' Espace
        Next i
        MsgBox "Modèles imprimés "
    Case "Quitter"
        mnuExit_Click
    End Select
    
End Sub
