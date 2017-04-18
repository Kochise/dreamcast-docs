VERSION 5.00
Begin VB.Form frmDataCtlProp 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Propriétés du contrôle Data"
   ClientHeight    =   5280
   ClientLeft      =   1740
   ClientTop       =   1695
   ClientWidth     =   5910
   BeginProperty Font 
      Name            =   "Tahoma"
      Size            =   8.25
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   HelpContextID   =   2016124
   Icon            =   "DCPROP.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5280
   ScaleWidth      =   5910
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  'CenterOwner
   Begin VB.PictureBox picCtlType 
      Appearance      =   0  'Flat
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   2760
      ScaleHeight     =   255
      ScaleWidth      =   2775
      TabIndex        =   38
      Top             =   4440
      Width           =   2775
      Begin VB.OptionButton optOLECtl 
         Caption         =   "OLE"
         Height          =   255
         Left            =   0
         MaskColor       =   &H00000000&
         TabIndex        =   40
         Top             =   0
         Width           =   735
      End
      Begin VB.OptionButton optPictureCtl 
         Caption         =   "PictureBox"
         Height          =   255
         Left            =   1080
         MaskColor       =   &H00000000&
         TabIndex        =   39
         Top             =   0
         Width           =   1215
      End
   End
   Begin VB.CheckBox chkForwardOnly 
      Caption         =   "ForwardOnly"
      Height          =   255
      Left            =   2040
      MaskColor       =   &H00000000&
      TabIndex        =   16
      Top             =   3000
      Width           =   1590
   End
   Begin VB.CheckBox chkFailOnError 
      Caption         =   "FailOnError"
      Height          =   255
      Left            =   840
      MaskColor       =   &H00000000&
      TabIndex        =   15
      Top             =   3000
      Width           =   1215
   End
   Begin VB.CheckBox chkSQLPassthrough 
      Caption         =   "SQLPassthru"
      Height          =   255
      Left            =   3240
      MaskColor       =   &H00000000&
      TabIndex        =   14
      Top             =   2760
      Width           =   1335
   End
   Begin VB.CheckBox chkConsistent 
      Caption         =   "Consistent"
      Height          =   255
      Left            =   2040
      MaskColor       =   &H00000000&
      TabIndex        =   13
      Top             =   2760
      Width           =   1095
   End
   Begin VB.CheckBox chkInconsistent 
      Caption         =   "Inconsistent"
      Height          =   255
      Left            =   840
      MaskColor       =   &H00000000&
      TabIndex        =   12
      Top             =   2760
      Width           =   1215
   End
   Begin VB.CheckBox chkAppendOnly 
      Caption         =   "AppendOnly"
      Height          =   255
      Left            =   4440
      MaskColor       =   &H00000000&
      TabIndex        =   11
      Top             =   2520
      Width           =   1215
   End
   Begin VB.CheckBox chkReadOnly 
      Caption         =   "ReadOnly"
      Height          =   255
      Left            =   3240
      MaskColor       =   &H00000000&
      TabIndex        =   10
      Top             =   2520
      Width           =   1095
   End
   Begin VB.CheckBox chkDenyRead 
      Caption         =   "DenyRead"
      Height          =   255
      Left            =   2040
      MaskColor       =   &H00000000&
      TabIndex        =   9
      Top             =   2520
      Width           =   1095
   End
   Begin VB.CheckBox chkDenyWrite 
      Caption         =   "DenyWrite"
      Height          =   255
      Left            =   840
      MaskColor       =   &H00000000&
      TabIndex        =   8
      Top             =   2520
      Width           =   1095
   End
   Begin VB.CheckBox chkDBReadOnly 
      Caption         =   "ReadOnly"
      Height          =   255
      Left            =   3000
      MaskColor       =   &H00000000&
      TabIndex        =   3
      Top             =   1080
      Width           =   1215
   End
   Begin VB.CheckBox chkExclusive 
      Caption         =   "Exclusive"
      Height          =   255
      Left            =   1080
      MaskColor       =   &H00000000&
      TabIndex        =   2
      Top             =   1080
      Width           =   1335
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "&Annuler"
      Height          =   375
      Left            =   3120
      MaskColor       =   &H00000000&
      TabIndex        =   23
      Top             =   4800
      Width           =   2295
   End
   Begin VB.CommandButton cmdRefresh 
      Caption         =   "A&ctualiser le contrôle Data"
      Height          =   375
      Left            =   360
      MaskColor       =   &H00000000&
      TabIndex        =   22
      Top             =   4800
      Width           =   2295
   End
   Begin VB.TextBox txtRecordSource 
      Height          =   285
      Left            =   1320
      TabIndex        =   4
      Top             =   1800
      Width           =   4455
   End
   Begin VB.TextBox txtConnect 
      Height          =   285
      Left            =   840
      TabIndex        =   1
      Top             =   720
      Width           =   4935
   End
   Begin VB.TextBox txtDatabaseName 
      Height          =   285
      Left            =   840
      TabIndex        =   0
      Top             =   360
      Width           =   4935
   End
   Begin VB.PictureBox picRSType 
      Appearance      =   0  'Flat
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   1680
      ScaleHeight     =   285
      ScaleWidth      =   4095
      TabIndex        =   29
      TabStop         =   0   'False
      Top             =   2160
      Width           =   4095
      Begin VB.OptionButton optRSType 
         Caption         =   "1 - Dynaset"
         Height          =   255
         Index           =   1
         Left            =   1200
         MaskColor       =   &H00000000&
         TabIndex        =   6
         Top             =   5
         Width           =   1335
      End
      Begin VB.OptionButton optRSType 
         Caption         =   "0 - Table"
         Height          =   255
         Index           =   0
         Left            =   20
         MaskColor       =   &H00000000&
         TabIndex        =   5
         Top             =   5
         Width           =   1215
      End
      Begin VB.OptionButton optRSType 
         Caption         =   "2 - Snapshot"
         Height          =   255
         Index           =   2
         Left            =   2640
         MaskColor       =   &H00000000&
         TabIndex        =   7
         Top             =   5
         Width           =   1455
      End
   End
   Begin VB.PictureBox picEOFAction 
      Appearance      =   0  'Flat
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   1320
      ScaleHeight     =   255
      ScaleWidth      =   3855
      TabIndex        =   27
      TabStop         =   0   'False
      Top             =   4080
      Width           =   3855
      Begin VB.OptionButton optEOFAction 
         Caption         =   "2 - AddNew"
         Height          =   255
         Index           =   2
         Left            =   2520
         MaskColor       =   &H00000000&
         TabIndex        =   21
         Top             =   0
         Width           =   1215
      End
      Begin VB.OptionButton optEOFAction 
         Caption         =   "0 - MoveLast"
         Height          =   255
         Index           =   0
         Left            =   0
         MaskColor       =   &H00000000&
         TabIndex        =   19
         Top             =   0
         Width           =   1335
      End
      Begin VB.OptionButton optEOFAction 
         Caption         =   "1 - EOF"
         Height          =   255
         Index           =   1
         Left            =   1440
         MaskColor       =   &H00000000&
         TabIndex        =   20
         Top             =   0
         Width           =   975
      End
   End
   Begin VB.PictureBox picBOFAction 
      Appearance      =   0  'Flat
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   1320
      ScaleHeight     =   255
      ScaleWidth      =   2535
      TabIndex        =   25
      TabStop         =   0   'False
      Top             =   3720
      Width           =   2535
      Begin VB.OptionButton optBOFAction 
         Caption         =   "1 - BOF"
         Height          =   255
         Index           =   1
         Left            =   1440
         MaskColor       =   &H00000000&
         TabIndex        =   18
         Top             =   0
         Width           =   975
      End
      Begin VB.OptionButton optBOFAction 
         Caption         =   "0 - MoveFirst"
         Height          =   255
         Index           =   0
         Left            =   0
         MaskColor       =   &H00000000&
         TabIndex        =   17
         Top             =   0
         Width           =   1335
      End
   End
   Begin VB.Label lblLabels 
      Caption         =   "Type de contrôle dépendant binaire:"
      Height          =   195
      Index           =   9
      Left            =   120
      TabIndex        =   37
      Top             =   4440
      Width           =   2640
   End
   Begin VB.Label lblLabels 
      Alignment       =   2  'Center
      Caption         =   "Propriétés du contrôle Data"
      Height          =   195
      Index           =   8
      Left            =   120
      TabIndex        =   36
      Top             =   3480
      Width           =   5655
   End
   Begin VB.Line Line1 
      BorderWidth     =   3
      Index           =   1
      X1              =   120
      X2              =   5760
      Y1              =   3360
      Y2              =   3360
   End
   Begin VB.Line Line1 
      BorderWidth     =   3
      Index           =   0
      X1              =   120
      X2              =   5760
      Y1              =   1440
      Y2              =   1440
   End
   Begin VB.Label lblLabels 
      Alignment       =   2  'Center
      Caption         =   "Propriétés du jeu d'enregistrements"
      Height          =   195
      Index           =   10
      Left            =   120
      TabIndex        =   35
      Top             =   1560
      Width           =   5655
   End
   Begin VB.Label lblLabels 
      Alignment       =   2  'Center
      Caption         =   "Propriétés de la base de données"
      Height          =   195
      Index           =   7
      Left            =   120
      TabIndex        =   34
      Top             =   45
      Width           =   5655
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "Options: "
      Height          =   195
      Index           =   6
      Left            =   120
      TabIndex        =   33
      Top             =   2520
      Width           =   660
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "RecordSource: "
      Height          =   195
      Index           =   5
      Left            =   120
      TabIndex        =   32
      Top             =   1800
      Width           =   1110
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "Connect: "
      Height          =   195
      Index           =   4
      Left            =   120
      TabIndex        =   31
      Top             =   720
      Width           =   705
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "Name: "
      Height          =   195
      Index           =   3
      Left            =   120
      TabIndex        =   30
      Top             =   360
      Width           =   510
   End
   Begin VB.Label lblLabels 
      AutoSize        =   -1  'True
      Caption         =   "RecordsetType: "
      Height          =   195
      Index           =   2
      Left            =   120
      TabIndex        =   28
      Top             =   2160
      Width           =   1200
   End
   Begin VB.Label lblLabels 
      Caption         =   "EOFAction: "
      Height          =   195
      Index           =   1
      Left            =   120
      TabIndex        =   26
      Top             =   4080
      Width           =   1215
   End
   Begin VB.Label lblLabels 
      Caption         =   "BOFAction: "
      Height          =   195
      Index           =   0
      Left            =   120
      TabIndex        =   24
      Top             =   3720
      Width           =   1095
   End
End
Attribute VB_Name = "frmDataCtlProp"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
    '>>>>>>>>>>>>>>>>>>>>>>>>
    Const FORMCAPTION = "Propriétés du contrôle Data"
    Const BUTTON1 = "A&ctualiser le contrôle Data"
    Const BUTTON2 = "&Annuler"
    Const Label1 = "Propriétés de la base de données"
    Const Label2 = "Propriétés du jeu d'enregistrements"
    Const LABEL3 = "Propriétés du contrôle Data"
    Const LABEL4 = "Type de contrôle dépendant binaire:"
    
    '>>>>>>>>>>>>>>>>>>>>>>>>


Sub cmdCancel_Click()
  Set gDataCtlObj = Nothing
  Unload Me
End Sub

Sub cmdRefresh_Click()
  On Error GoTo RefErr

  gbSettingDataCtl = True
  gDataCtlObj.DatabaseName = txtDatabaseName.Text
  gDataCtlObj.Connect = txtConnect.Text
  gDataCtlObj.Exclusive = IIf(chkExclusive.Value = vbUnchecked, 0, -1)
  gDataCtlObj.ReadOnly = IIf(chkDBReadOnly.Value = vbUnchecked, 0, -1)
  
  gDataCtlObj.RecordSource = txtRecordSource.Text
  If optRSType(0).Value Then
    gDataCtlObj.RecordsetType = 0
  ElseIf optRSType(1).Value Then
    gDataCtlObj.RecordsetType = 1
  Else
    gDataCtlObj.RecordsetType = 2
  End If
  
  gDataCtlObj.Options = 0
  ' Définit les options sélectionnées.
  If chkDenyWrite.Value = vbChecked Then
    gDataCtlObj.Options = gDataCtlObj.Options Or dbDenyWrite
  End If
  If chkDenyRead.Value = vbChecked Then
    gDataCtlObj.Options = gDataCtlObj.Options Or dbDenyRead
  End If
  If chkReadOnly.Value = vbChecked Then
    gDataCtlObj.Options = gDataCtlObj.Options Or dbReadOnly
  End If
  If chkAppendOnly.Value = vbChecked Then
    gDataCtlObj.Options = gDataCtlObj.Options Or dbAppendOnly
  End If
  If chkInconsistent.Value = vbChecked Then
    gDataCtlObj.Options = gDataCtlObj.Options Or dbInconsistent
  End If
  If chkConsistent.Value = vbChecked Then
    gDataCtlObj.Options = gDataCtlObj.Options Or dbConsistent
  End If
  If chkSQLPassthrough.Value = vbChecked Then
    gDataCtlObj.Options = gDataCtlObj.Options Or dbSQLPassThrough
  End If
  If chkFailOnError.Value = vbChecked Then
    gDataCtlObj.Options = gDataCtlObj.Options Or dbFailOnError
  End If
  If chkForwardOnly.Value = vbChecked Then
    gDataCtlObj.Options = gDataCtlObj.Options Or dbForwardOnly
  End If

  If optBOFAction(0).Value Then
    gDataCtlObj.BOFAction = 0
  Else
    gDataCtlObj.BOFAction = 1
  End If
  If optEOFAction(0).Value Then
    gDataCtlObj.EOFAction = 0
  ElseIf optEOFAction(1).Value Then
    gDataCtlObj.EOFAction = 1
  Else
    gDataCtlObj.EOFAction = 2
  End If

  gDataCtlObj.Tag = IIf(optOLECtl.Value, "OLE", "PIC")
  
  Unload Me
  Exit Sub
  
RefErr:
  gbSettingDataCtl = False
  ShowError
End Sub

Private Sub Form_KeyUp(KeyCode As Integer, Shift As Integer)
  If KeyCode = vbKeyF1 And Shift = 0 Then
    DisplayTopic 2016124
  End If
End Sub

Sub Form_Load()

  Me.Caption = FORMCAPTION
  cmdRefresh.Caption = BUTTON1
  cmdCancel.Caption = BUTTON2
  lblLabels(7).Caption = Label1
  lblLabels(10).Caption = Label2
  lblLabels(8).Caption = LABEL3
  lblLabels(9).Caption = LABEL4
  

  txtDatabaseName.Text = gDataCtlObj.DatabaseName
  txtConnect.Text = gDataCtlObj.Connect
  chkExclusive.Value = IIf(gDataCtlObj.Exclusive, 1, 0)
  chkDBReadOnly.Value = IIf(gDataCtlObj.ReadOnly, 1, 0)
  
  txtRecordSource.Text = gDataCtlObj.RecordSource
  optRSType(gDataCtlObj.RecordsetType).Value = True
  If (gDataCtlObj.Options And dbDenyWrite) = dbDenyWrite Then
    chkDenyWrite.Value = vbChecked
  End If
  If (gDataCtlObj.Options And dbDenyRead) = dbDenyRead Then
    chkDenyRead.Value = vbChecked
  End If
  If (gDataCtlObj.Options And dbReadOnly) = dbReadOnly Then
    chkReadOnly.Value = vbChecked
  End If
  If (gDataCtlObj.Options And dbAppendOnly) = dbAppendOnly Then
    chkAppendOnly.Value = vbChecked
  End If
  If (gDataCtlObj.Options And dbInconsistent) = dbInconsistent Then
    chkInconsistent.Value = vbChecked
  End If
  If (gDataCtlObj.Options And dbConsistent) = dbConsistent Then
    chkConsistent.Value = vbChecked
  End If
  If (gDataCtlObj.Options And dbSQLPassThrough) = dbSQLPassThrough Then
    chkSQLPassthrough.Value = vbChecked
  End If
  If (gDataCtlObj.Options And dbFailOnError) = dbFailOnError Then
    chkFailOnError.Value = vbChecked
  End If
  If (gDataCtlObj.Options And dbForwardOnly) = dbForwardOnly Then
    chkForwardOnly.Value = vbChecked
  End If

  optBOFAction(gDataCtlObj.BOFAction).Value = True
  optEOFAction(gDataCtlObj.EOFAction).Value = True
  
  optOLECtl.Value = IIf(gDataCtlObj.Tag = "OLE", True, False)
  
  Screen.MousePointer = vbDefault
End Sub
