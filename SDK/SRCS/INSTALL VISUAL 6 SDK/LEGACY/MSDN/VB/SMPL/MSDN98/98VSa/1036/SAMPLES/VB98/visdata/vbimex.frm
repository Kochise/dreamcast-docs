VERSION 5.00
Begin VB.Form frmImpExp 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Importer/Exporter"
   ClientHeight    =   4905
   ClientLeft      =   2190
   ClientTop       =   1410
   ClientWidth     =   4725
   HelpContextID   =   2016092
   Icon            =   "VBIMEX.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4905
   ScaleWidth      =   4725
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  'CenterOwner
   Begin VB.CommandButton cmdClose 
      Cancel          =   -1  'True
      Caption         =   "&Fermer"
      Height          =   375
      Left            =   2400
      MaskColor       =   &H00000000&
      TabIndex        =   2
      Top             =   120
      Width           =   2055
   End
   Begin VB.CommandButton cmdExportSQL 
      Caption         =   "E&xporter les résultats SQL"
      Enabled         =   0   'False
      Height          =   375
      Left            =   2400
      MaskColor       =   &H00000000&
      TabIndex        =   4
      Top             =   600
      Width           =   2055
   End
   Begin VB.CommandButton cmdImport 
      Caption         =   "&Importer"
      Height          =   375
      Left            =   240
      MaskColor       =   &H00000000&
      TabIndex        =   1
      Top             =   120
      Width           =   2055
   End
   Begin VB.ListBox lstTables 
      Height          =   3765
      Left            =   120
      MultiSelect     =   2  'Extended
      TabIndex        =   0
      Top             =   1080
      Width           =   4470
   End
   Begin VB.CommandButton cmdExport 
      Caption         =   "&Exporter la ou les tables"
      Enabled         =   0   'False
      Height          =   375
      Left            =   240
      MaskColor       =   &H00000000&
      TabIndex        =   3
      Top             =   600
      Width           =   2055
   End
End
Attribute VB_Name = "frmImpExp"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
'>>>>>>>>>>>>>>>>>>>>>>>>
Const FORMCAPTION = "Importer/Exporter"
Const BUTTON1 = "&Importer"
Const BUTTON2 = "&Fermer"
Const BUTTON3 = "&Exporter la ou les tables"
Const BUTTON4 = "E&xporter les résultats SQL"
Const MSG1 = "Exporter"
Const MSG2 = "Importer"
Const MSG3 = "Exporter résultats SQL"
Const MSG4 = "Sélectionner un fichier"
'>>>>>>>>>>>>>>>>>>>>>>>>


Private Sub cmdClose_Click()
  Unload Me
End Sub

Private Sub cmdExport_Click()
  On Error GoTo ExpErr
  
  Dim i As Integer

  For i = 0 To lstTables.ListCount - 1
    If lstTables.Selected(i) Then
      frmDataType.Caption = MSG1 & " '" & lstTables.List(i) & "'"
      frmDataType.Show vbModal
      lstTables.Selected(i) = False
      If gnDataType <> gnDT_NONE Then
        If gnDataType <> gnDT_SQLDB Then
          SetCommDlg
          If Not (gnDataType = gnDT_MSACCESS Or gnDataType = gnDT_BTRIEVE) Then
            frmMDI.dlgCMD1.Flags = FileOpenConstants.cdlOFNHideReadOnly
          End If
          frmMDI.dlgCMD1.ShowSave
          If Len(frmMDI.dlgCMD1.FileName) > 0 Then
            Export (lstTables.List(i)), (frmMDI.dlgCMD1.FileName)
          End If
        Else
          Export (lstTables.List(i)), vbNullString
        End If
      End If
    End If
  Next

  cmdExport.Enabled = False

  Exit Sub

ExpErr:
  If Err = 32755 Then Exit Sub
  ShowError
End Sub

Private Sub cmdExportSQL_Click()
  On Error GoTo SQLExpErr
  
  Dim i As Integer

  frmDataType.Caption = MSG3
  frmDataType.Show vbModal
  If gnDataType <> gnDT_NONE Then
    If gnDataType <> gnDT_SQLDB Then
      SetCommDlg
      If Not (gnDataType = gnDT_MSACCESS Or gnDataType = gnDT_BTRIEVE) Then
        frmMDI.dlgCMD1.Flags = FileOpenConstants.cdlOFNHideReadOnly
      End If
      frmMDI.dlgCMD1.ShowSave
      If Len(frmMDI.dlgCMD1.FileName) > 0 Then
        Export vbNullString, (frmMDI.dlgCMD1.FileName)
      End If
    Else
      Export vbNullString, vbNullString
    End If
  End If

  Exit Sub

SQLExpErr:
  If Err = 32755 Then Exit Sub
  ShowError
End Sub

Private Sub cmdImport_Click()
  On Error GoTo ImpErr

  frmDataType.Caption = MSG2
  frmDataType.Show vbModal

  If gnDataType = gnDT_NONE Then Exit Sub
  
  If gnDataType <> gnDT_SQLDB Then
    SetCommDlg
    frmMDI.dlgCMD1.ShowOpen
    If Len(frmMDI.dlgCMD1.FileName) > 0 Then
      If gnDataType = gnDT_MSACCESS Or gnDataType = gnDT_BTRIEVE Then
        If gnDataType = gnDT_MSACCESS Then
          Set gImpDB = gwsMainWS.OpenDatabase(frmMDI.dlgCMD1.FileName)
        ElseIf gnDataType = gnDT_EXCEL50 Or gnDataType = gnDT_EXCEL40 Or gnDataType = gnDT_EXCEL30 Then
          ' Excel 5.0 est utilisable pour tous les fichiers Excel:
          ' le fichier ISAM reconnaît la version à partir du
          ' fichier même et non de la chaîne de connexion.
          Set gImpDB = gwsMainWS.OpenDatabase(frmMDI.dlgCMD1.FileName, 0, 0, gsEXCEL50)
        Else
          Set gImpDB = gwsMainWS.OpenDatabase(frmMDI.dlgCMD1.FileName, 0, 0, gsBTRIEVE)
        End If
        If gImpDB Is Nothing Then Exit Sub
        frmImpTbls.lblLabel1.Caption = frmImpTbls.lblLabel1 & gImpDB.Name
        frmImpTbls.Show vbModal
      Else
        Import (frmMDI.dlgCMD1.FileName)
        While Len(frmMDI.dlgCMD1.FileName) > 0
          frmMDI.dlgCMD1.FileName = vbNullString
          frmMDI.dlgCMD1.ShowOpen
          Import (frmMDI.dlgCMD1.FileName)
        Wend
      End If
    End If
  Else
    Set gImpDB = gwsMainWS.OpenDatabase(vbNullString, 0, 0, "odbc;")
    If gImpDB Is Nothing Then Exit Sub
    frmImpTbls.lblLabel1.Caption = frmImpTbls.lblLabel1.Caption & gImpDB.Name
    frmImpTbls.Show vbModal
  End If
  
  Screen.MousePointer = vbDefault
  Exit Sub

ImpErr:
  If Err <> 32755 Then
    ShowError
  Else
    Screen.MousePointer = vbDefault
  End If
End Sub

Private Sub lstTables_Click()
  cmdExport.Enabled = True
End Sub

Private Sub lstTables_DblClick()
  Call cmdExport_Click
End Sub

Private Sub Form_KeyUp(KeyCode As Integer, Shift As Integer)
  If KeyCode = vbKeyF1 And Shift = 0 Then
    DisplayTopic 2016092
  End If
End Sub

Private Sub Form_Load()
  Me.Caption = FORMCAPTION
  cmdImport.Caption = BUTTON1
  cmdClose.Caption = BUTTON2
  cmdExport.Caption = BUTTON3
  cmdExportSQL.Caption = BUTTON4
  
  If UCase(Mid(frmSQL.txtSQLStatement, 1, 7)) = "SELECT " Then
    cmdExportSQL.Enabled = True
  End If
  GetTableList frmImpExp.lstTables, False, False, True
  
  MsgBar vbNullString, False
End Sub

Private Sub Form_Resize()
  If WindowState <> 2 Then
    lstTables.Width = Width - 340
    Refresh
  End If
End Sub

Private Sub Form_Unload(Cancel As Integer)
  Unload frmDataType
End Sub

Private Sub SetCommDlg()
   With frmMDI.dlgCMD1
     .DialogTitle = MSG4
     Select Case gnDataType
       Case gnDT_MSACCESS
         .Filter = "Microsoft Access (*.mdb)|*.mdb|Tous les fichiers (*.*)|*.*"
         .DialogTitle = "Sélectionnez la base de données Microsoft Access"
         .Flags = FileOpenConstants.cdlOFNHideReadOnly
       Case gnDT_PARADOX3X, gnDT_PARADOX4X
         .Filter = "Paradox (*.db)|*.db"
         .Flags = FileOpenConstants.cdlOFNOverwritePrompt Or FileOpenConstants.cdlOFNHideReadOnly
       Case gnDT_FOXPRO26, gnDT_FOXPRO25, gnDT_FOXPRO20, gnDT_DBASEIV, gnDT_DBASEIII
         .Filter = "Xbase (*.dbf)|*.dbf"
         .Flags = FileOpenConstants.cdlOFNOverwritePrompt Or FileOpenConstants.cdlOFNHideReadOnly
       Case gnDT_BTRIEVE
         .Filter = "Btrieve (FILE.DDF)|FILE.DDF"
         .Flags = FileOpenConstants.cdlOFNHideReadOnly
       Case gnDT_EXCEL50, gnDT_EXCEL40, gnDT_EXCEL30
         .Filter = "Excel (*.xls)|*.xls"
         .Flags = FileOpenConstants.cdlOFNOverwritePrompt Or FileOpenConstants.cdlOFNHideReadOnly
       Case gnDT_TEXTFILE
         .Filter = "Fichiers texte (*.txt)|*.txt|Tous les fichiers (*.*)|*.*"
         .DialogTitle = "Sélectionnez le fichier texte"
         .Flags = FileOpenConstants.cdlOFNOverwritePrompt Or FileOpenConstants.cdlOFNHideReadOnly
     End Select

     .FilterIndex = 1
     .FileName = vbNullString
     .CancelError = True
  End With
End Sub

