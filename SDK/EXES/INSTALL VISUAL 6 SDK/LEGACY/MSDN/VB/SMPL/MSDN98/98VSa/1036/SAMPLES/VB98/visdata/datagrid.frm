VERSION 5.00
Object = "{CDE57A40-8B86-11D0-B3C6-00A0C90AEA82}#1.0#0"; "MSDatGrd.Ocx"
Object = "{67397AA1-7FB1-11D0-B148-00A0C922E820}#6.0#0"; "MSADODC.OCX"
Begin VB.Form frmDataGrid 
   Caption         =   "Grille de données"
   ClientHeight    =   6105
   ClientLeft      =   3780
   ClientTop       =   2250
   ClientWidth     =   6810
   HelpContextID   =   2016191
   Icon            =   "DATAGRID.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MDIChild        =   -1  'True
   ScaleHeight     =   6105
   ScaleWidth      =   6810
   ShowInTaskbar   =   0   'False
   Tag             =   "Recordset"
   Begin MSAdodcLib.Adodc datDataCtl 
      Align           =   2  'Align Bottom
      Height          =   330
      Left            =   0
      Top             =   5775
      Width           =   6810
      _ExtentX        =   12012
      _ExtentY        =   582
      ConnectMode     =   0
      CursorLocation  =   3
      IsolationLevel  =   -1
      ConnectionTimeout=   15
      CommandTimeout  =   30
      CursorType      =   3
      LockType        =   3
      CommandType     =   8
      CursorOptions   =   0
      CacheSize       =   50
      MaxRecords      =   0
      BOFAction       =   0
      EOFAction       =   0
      ConnectStringType=   1
      Appearance      =   1
      BackColor       =   -2147483643
      ForeColor       =   -2147483640
      Orientation     =   0
      Enabled         =   -1
      Connect         =   ""
      OLEDBString     =   ""
      OLEDBFile       =   ""
      DataSourceName  =   ""
      OtherAttributes =   ""
      UserName        =   ""
      Password        =   ""
      RecordSource    =   ""
      Caption         =   ""
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      _Version        =   393216
   End
   Begin MSDataGridLib.DataGrid grdDataGrid 
      Align           =   1  'Align Top
      Bindings        =   "DATAGRID.frx":014A
      Height          =   4695
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   6810
      _ExtentX        =   12012
      _ExtentY        =   8281
      _Version        =   393216
      HeadLines       =   1
      RowHeight       =   15
      AllowAddNew     =   -1  'True
      AllowDelete     =   -1  'True
      BeginProperty HeadFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ColumnCount     =   2
      BeginProperty Column00 
         DataField       =   ""
         Caption         =   ""
         BeginProperty DataFormat {6D835690-900B-11D0-9484-00A0C91110ED} 
            Type            =   0
            Format          =   ""
            HaveTrueFalseNull=   0
            FirstDayOfWeek  =   0
            FirstWeekOfYear =   0
            LCID            =   1024
         EndProperty
      EndProperty
      BeginProperty Column01 
         DataField       =   ""
         Caption         =   ""
         BeginProperty DataFormat {6D835690-900B-11D0-9484-00A0C91110ED} 
            Type            =   0
            Format          =   ""
            HaveTrueFalseNull=   0
            FirstDayOfWeek  =   0
            FirstWeekOfYear =   0
            LCID            =   1024
         EndProperty
      EndProperty
      SplitCount      =   1
      BeginProperty Split0 
         BeginProperty Column00 
         EndProperty
         BeginProperty Column01 
         EndProperty
      EndProperty
   End
End
Attribute VB_Name = "frmDataGrid"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
'>>>>>>>>>>>>>>>>>>>>>>>>
Const MSG8 = "Effacer la ligne en cours?"
'>>>>>>>>>>>>>>>>>>>>>>>>

Public mrsFormRecordset As ADODB.Recordset

Private Sub Form_KeyUp(KeyCode As Integer, Shift As Integer)
  If KeyCode = vbKeyF1 And Shift = 0 Then
    DisplayTopic 2016191
  End If
End Sub

Private Sub Form_Load()
  On Error GoTo LoadErr
  
  datDataCtl.Caption = Caption
  
  ' mrsFormRecordset est une variable de type Public de niveau module
  ' qui doit être définie avant l'affichage de cette feuille.
  Set datDataCtl.Recordset = mrsFormRecordset
  
  Me.Width = 5865
  Me.Height = 5070
  
  Exit Sub

LoadErr:
  MsgBox "Erreur:" & Err & " " & Error$
  Unload Me

End Sub

Private Sub Form_Resize()
  On Error Resume Next
  If Me.WindowState <> vbMinimized Then
    grdDataGrid.Height = Me.ScaleHeight - (datDataCtl.Height + 135)
  End If
End Sub

Private Sub grdDataGrid_BeforeDelete(Cancel As Integer)
  If MsgBox(MSG8, vbYesNo + vbQuestion) <> vbYes Then
    Cancel = True
  End If
End Sub

