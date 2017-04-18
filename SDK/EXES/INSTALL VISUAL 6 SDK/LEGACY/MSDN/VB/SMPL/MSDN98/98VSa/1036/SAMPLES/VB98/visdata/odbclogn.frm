VERSION 5.00
Begin VB.Form frmODBCLogon 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Ouvrir une source de données ODBC"
   ClientHeight    =   3195
   ClientLeft      =   2850
   ClientTop       =   1755
   ClientWidth     =   5355
   ControlBox      =   0   'False
   BeginProperty Font 
      Name            =   "Tahoma"
      Size            =   8.25
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   HelpContextID   =   2016138
   Icon            =   "ODBCLogn.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3195
   ScaleWidth      =   5355
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton cmdRegister 
      Caption         =   "I&nscrire"
      Height          =   450
      Left            =   240
      MaskColor       =   &H00000000&
      TabIndex        =   15
      Top             =   2655
      Width           =   1440
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Annuler"
      Height          =   450
      Left            =   3795
      MaskColor       =   &H00000000&
      TabIndex        =   13
      Top             =   2655
      Width           =   1260
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "&OK"
      Default         =   -1  'True
      Height          =   450
      Left            =   2115
      MaskColor       =   &H00000000&
      TabIndex        =   12
      Top             =   2655
      Width           =   1260
   End
   Begin VB.Frame fraConnection 
      Caption         =   "Valeurs de connexion"
      Height          =   2415
      Left            =   105
      TabIndex        =   14
      Top             =   105
      Width           =   5070
      Begin VB.TextBox txtUID 
         Height          =   300
         Left            =   1440
         TabIndex        =   3
         Top             =   600
         Width           =   3435
      End
      Begin VB.TextBox txtPWD 
         Height          =   300
         IMEMode         =   3  'DISABLE
         Left            =   1440
         PasswordChar    =   "*"
         TabIndex        =   5
         Top             =   930
         Width           =   3435
      End
      Begin VB.TextBox txtDatabase 
         Height          =   300
         Left            =   1440
         TabIndex        =   7
         Top             =   1260
         Width           =   3435
      End
      Begin VB.ComboBox cboDSNList 
         Height          =   315
         ItemData        =   "ODBCLogn.frx":000C
         Left            =   1440
         List            =   "ODBCLogn.frx":000E
         Sorted          =   -1  'True
         TabIndex        =   1
         Text            =   "È"
         Top             =   240
         Width           =   3420
      End
      Begin VB.TextBox txtServer 
         Enabled         =   0   'False
         Height          =   330
         Left            =   1440
         TabIndex        =   11
         Top             =   1935
         Width           =   3435
      End
      Begin VB.ComboBox cboDrivers 
         Enabled         =   0   'False
         Height          =   315
         ItemData        =   "ODBCLogn.frx":0010
         Left            =   1440
         List            =   "ODBCLogn.frx":0012
         Sorted          =   -1  'True
         Style           =   2  'Dropdown List
         TabIndex        =   9
         Top             =   1590
         Width           =   3435
      End
      Begin VB.Label lblLabels 
         AutoSize        =   -1  'True
         Caption         =   "&DSN:"
         Height          =   195
         Index           =   0
         Left            =   135
         TabIndex        =   0
         Top             =   285
         Width           =   360
      End
      Begin VB.Label lblLabels 
         AutoSize        =   -1  'True
         Caption         =   "&ID:"
         Height          =   195
         Index           =   1
         Left            =   135
         TabIndex        =   2
         Top             =   630
         Width           =   225
      End
      Begin VB.Label lblLabels 
         AutoSize        =   -1  'True
         Caption         =   "&Mot de passe:"
         Height          =   195
         Index           =   2
         Left            =   135
         TabIndex        =   4
         Top             =   975
         Width           =   1170
      End
      Begin VB.Label lblLabels 
         AutoSize        =   -1  'True
         Caption         =   "&Base de données:"
         Height          =   195
         Index           =   3
         Left            =   135
         TabIndex        =   6
         Top             =   1320
         Width           =   1275
      End
      Begin VB.Label lblLabels 
         AutoSize        =   -1  'True
         Caption         =   "&Pilote:"
         Enabled         =   0   'False
         Height          =   195
         Index           =   4
         Left            =   135
         TabIndex        =   8
         Top             =   1665
         Width           =   495
      End
      Begin VB.Label lblLabels 
         AutoSize        =   -1  'True
         Caption         =   "&Serveur:"
         Enabled         =   0   'False
         Height          =   195
         Index           =   5
         Left            =   135
         TabIndex        =   10
         Top             =   2010
         Width           =   540
      End
   End
End
Attribute VB_Name = "frmODBCLogon"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
'>>>>>>>>>>>>>>>>>>>>>>>>
Const FORMCAPTION = "Ouvrir une source de données ODBC"
Const BUTTON1 = "&OK"
Const BUTTON2 = "&Annuler"
Const BUTTON3 = "&Inscrire"
Const FRAME1 = "Valeurs de connexion:"
Const Label1 = "&DSN:"
Const Label2 = "&UID:"
Const LABEL3 = "&Mot de passe:"
Const LABEL4 = "&Base de données:"
Const LABEL5 = "&Pilote:"
Const LABEL6 = "&Serveur:"
Const MSG1 = "Entrer les paramètres de connexion ODBC"
Const MSG2 = "Ouverture de la base de données ODBC"
Const MSG3 = "Entrer le nom de pilote du fichier ODBCINST.INI"
Const MSG4 = "Nom du pilote"
Const MSG5 = "Cette source de données n'a pas été enregistrée; une tentative va être faite!"
Const MSG7 = "Paramètre(s) non valide(s); essayez de nouveau!"
Const MSG8 = "Le délai d'attente de la requête n'a pas pu être défini; la valeur par défaut sera utilisée!"
Const MSG9 = "L'inscription de la source de données a réussi; poursuivre l'ouverture."
Const MSG10 = "Veuillez entrer un DSN!"
Const MSG11 = "Veuillez sélectionner un pilote!"
Const MSG12 = "Vous devez d'abord fermer!"
'>>>>>>>>>>>>>>>>>>>>>>>>

Dim mbBeenLoaded As Integer
Public DBOpened As Boolean

Private Declare Function SQLDataSources Lib "ODBC32.DLL" (ByVal henv&, ByVal fDirection%, ByVal szDSN$, ByVal cbDSNMax%, pcbDSN%, ByVal szDescription$, ByVal cbDescriptionMax%, pcbDescription%) As Integer
Private Declare Function SQLAllocEnv% Lib "ODBC32.DLL" (env&)
Const SQL_SUCCESS As Long = 0
Const SQL_FETCH_NEXT As Long = 1


Private Sub cboDSNList_Change()
  If Len(cboDSNList.Text) = 0 Or cboDSNList.Text = "(Aucun)" Then
    txtServer.Enabled = True
    cboDrivers.Enabled = True
    lblLabels(4).Enabled = True
    lblLabels(5).Enabled = True
  Else
    txtServer.Enabled = False
    cboDrivers.Enabled = False
    lblLabels(4).Enabled = False
    lblLabels(5).Enabled = False
  End If
End Sub

Private Sub cmdCancel_Click()
  gbDBOpenFlag = False
  gsDBName = vbNullString
  DBOpened = False
  Me.Hide
End Sub

Private Sub cmdOK_Click()
  On Error GoTo cmdOK_ClickErr

  Dim sConnect As String
  Dim dbTemp As Database

  MsgBar MSG2, True

  If frmMDI.mnuPOpenOnStartup.Checked Then
    Me.Refresh
  End If
  
  Screen.MousePointer = vbHourglass
  
  If Len(cboDSNList.Text) > 0 Then
    sConnect = "ODBC;DSN=" & cboDSNList.Text & ";"
  Else
    sConnect = "ODBC;Driver={" & cboDrivers.Text & "};"
    sConnect = sConnect & "Server=" & txtServer.Text & ";"
  End If
  
  sConnect = sConnect & "UID=" & txtUID.Text & ";"
  sConnect = sConnect & "PWD=" & txtPWD.Text & ";"
  If Len(txtDatabase.Text) > 0 Then
    sConnect = sConnect & "Database=" & txtDatabase.Text & ";"
  End If
  
  Set dbTemp = gwsMainWS.OpenDatabase("", 0, 0, sConnect)
  
  If gbDBOpenFlag Then
    CloseCurrentDB
    If gbDBOpenFlag Then
      Beep
      MsgBox MSG12, 48
      Me.Hide
      Exit Sub
    End If
  End If

  ' a réussi
  DBOpened = True
  ' Enregistre les valeurs.
  gsODBCDatasource = cboDSNList.Text
  gsDBName = gsODBCDatasource
  gsODBCDatabase = txtDatabase.Text
  gsODBCUserName = txtUID.Text
  gsODBCPassword = txtPWD.Text
  gsODBCDriver = cboDrivers.Text
  gsODBCServer = txtServer.Text
  gsDataType = gsSQLDB

  Set gdbCurrentDB = dbTemp
  GetODBCConnectParts gdbCurrentDB.Connect

  cboDSNList.Text = gsODBCDatasource
  txtDatabase.Text = gsODBCDatabase
  txtUID.Text = gsODBCUserName
  txtPWD.Text = gsODBCPassword

  frmMDI.Caption = "Gestionnaire de données:" & gsDBName & "." & gsODBCDatabase
  gdbCurrentDB.QueryTimeout = glQueryTimeout

  gbDBOpenFlag = True
  AddMRU

  Screen.MousePointer = vbDefault
  Me.Hide
   
  Exit Sub

cmdOK_ClickErr:
  Screen.MousePointer = vbDefault
  gbDBOpenFlag = False
  If Len(cboDSNList.Text) > 0 Then
    If InStr(1, Error, "La connexion à la base de données ODBC à '" & cboDSNList.Text & "' a échoué") > 0 Then
      Beep
      MsgBox MSG5, 48
      txtDatabase.Text = vbNullString
      txtUID.Text = vbNullString
      txtPWD.Text = vbNullString
      If RegisterDB((cboDSNList.Text)) Then
        MsgBox MSG9, 48
      End If
    ElseIf InStr(1, Error, "Échec de la connexion") > 0 Then
      Beep
      MsgBox MSG7, 48
    ElseIf InStr(1, Error, "Propriété QueryTimeout") > 0 Then
      If glQueryTimeout <> 5 Then
        Beep
        MsgBox MSG8, 48
      End If
      Resume Next
    Else
      ShowError
    End If
  End If
  
  MsgBar MSG1, False
  If Err = 3059 Then
    Unload Me
  End If

End Sub

Private Sub cmdRegister_Click()
  On Error GoTo cmdRegister_ClickErr
  
  If Len(cboDSNList.Text) = 0 Then
    MsgBox MSG10, vbInformation, Me.Caption
    Exit Sub
  End If
  If Len(cboDrivers.Text) = 0 Then
    MsgBox MSG11, vbInformation, Me.Caption
    Exit Sub
  End If
  
  ' Essaie de l'inscrire.
  DBEngine.RegisterDatabase cboDSNList.Text, cboDrivers.Text, False, vbNullString

  MsgBox MSG9, vbInformation
  
  Exit Sub
cmdRegister_ClickErr:
  ShowError
End Sub

Private Sub Form_KeyUp(KeyCode As Integer, Shift As Integer)
  If KeyCode = vbKeyF1 And Shift = 0 Then
    DisplayTopic 2016138
  End If
End Sub

Private Sub Form_Load()
  Dim i As Integer

  Me.Caption = FORMCAPTION
  cmdOK.Caption = BUTTON1
  cmdCancel.Caption = BUTTON2
  cmdRegister.Caption = BUTTON3
  fraConnection.Caption = FRAME1
  lblLabels(0).Caption = Label1
  lblLabels(1).Caption = Label2
  lblLabels(2).Caption = LABEL3
  lblLabels(3).Caption = LABEL4
  lblLabels(4).Caption = LABEL5
  lblLabels(5).Caption = LABEL6
  GetDSNsAndDrivers

  MsgBar MSG1, False
  
  cboDSNList.Text = gsODBCDatasource
  txtDatabase.Text = gsODBCDatabase
  txtUID.Text = gsODBCUserName
  txtPWD.Text = gsODBCPassword
  If Len(gsODBCDriver) > 0 Then
    For i = 0 To cboDrivers.ListCount - 1
      If cboDrivers.List(i) = gsODBCDriver Then
        cboDrivers.ListIndex = i
        Exit For
      End If
    Next
  End If
  txtServer.Text = gsODBCServer

  mbBeenLoaded = True
End Sub

Private Sub cboDSNList_Click()
  cboDSNList_Change
End Sub

Sub GetDSNsAndDrivers()
  On Error Resume Next
  
  Dim i As Integer
  Dim sDSNItem As String * 1024
  Dim sDRVItem As String * 1024
  Dim sDSN As String
  Dim sDRV As String
  Dim iDSNLen As Integer
  Dim iDRVLen As Integer
  Dim lHenv As Long     ' Pointeur d'environnement.

  cboDSNList.AddItem "(None)"

  ' lit les DSNs
  If SQLAllocEnv(lHenv) <> -1 Then
    Do Until i <> SQL_SUCCESS
      sDSNItem = Space(1024)
      sDRVItem = Space(1024)
      i = SQLDataSources(lHenv, SQL_FETCH_NEXT, sDSNItem, 1024, iDSNLen, sDRVItem, 1024, iDRVLen)
      sDSN = VBA.Left(sDSNItem, iDSNLen)
      sDRV = VBA.Left(sDRVItem, iDRVLen)
        
      If sDSN <> Space(iDSNLen) Then
        cboDSNList.AddItem sDSN
        cboDrivers.AddItem sDRV
      End If
    Loop
  End If
  ' Supprime les doublons
  If cboDSNList.ListCount > 0 Then
    With cboDrivers
      If .ListCount > 1 Then
        i = 0
        While i < .ListCount
          If .List(i) = .List(i + 1) Then
            .RemoveItem (i)
          Else
            i = i + 1
          End If
        Wend
      End If
    End With
  End If
  cboDSNList.ListIndex = 0
  
End Sub

Private Sub Form_Unload(Cancel As Integer)
  MsgBar vbNullString, False
End Sub

Private Function RegisterDB(rsDatasource As String) As Integer
   On Error GoTo RDBErr

   Dim sDriver As String

   sDriver = InputBox(MSG3, MSG4, gsDEFAULT_DRIVER)
   If sDriver <> gsDEFAULT_DRIVER Then
     DBEngine.RegisterDatabase rsDatasource, sDriver, False, vbNullString
   Else
     DBEngine.RegisterDatabase rsDatasource, sDriver, True, vbNullString
   End If

   RegisterDB = True
   Exit Function

RDBErr:
   RegisterDB = False
   
End Function
