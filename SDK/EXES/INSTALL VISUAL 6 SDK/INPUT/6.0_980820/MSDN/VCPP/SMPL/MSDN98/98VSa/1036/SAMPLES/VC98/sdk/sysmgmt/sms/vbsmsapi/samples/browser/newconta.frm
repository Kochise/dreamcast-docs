VERSION 4.00
Begin VB.Form frmNewContainer 
   Appearance      =   0  'Flat
   BackColor       =   &H80000005&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "New Container"
   ClientHeight    =   1995
   ClientLeft      =   2055
   ClientTop       =   1935
   ClientWidth     =   5670
   ControlBox      =   0   'False
   BeginProperty Font 
      name            =   "MS Sans Serif"
      charset         =   0
      weight          =   700
      size            =   8.25
      underline       =   0   'False
      italic          =   0   'False
      strikethrough   =   0   'False
   EndProperty
   ForeColor       =   &H80000008&
   Height          =   2400
   Left            =   1995
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1995
   ScaleWidth      =   5670
   Top             =   1590
   Width           =   5790
   Begin Threed.SSPanel pnlDialogBackdrop 
      Height          =   1995
      Left            =   0
      TabIndex        =   8
      Top             =   0
      Width           =   5655
      _Version        =   65536
      _ExtentX        =   9975
      _ExtentY        =   3519
      _StockProps     =   15
      BackColor       =   -2147483633
      Begin Threed.SSPanel pnlTextBoxBackdrop 
         Height          =   1635
         Left            =   240
         TabIndex        =   9
         Top             =   180
         Width           =   3915
         _Version        =   65536
         _ExtentX        =   6906
         _ExtentY        =   2884
         _StockProps     =   15
         BackColor       =   -2147483633
         Begin Threed.SSPanel pnlContainerType 
            Height          =   375
            Left            =   120
            TabIndex        =   1
            Top             =   420
            Width           =   3495
            _Version        =   65536
            _ExtentX        =   6165
            _ExtentY        =   661
            _StockProps     =   15
            BackColor       =   -2147483633
            BevelOuter      =   1
            Begin VB.ComboBox cboContainerType 
               Appearance      =   0  'Flat
               Height          =   300
               Left            =   30
               TabIndex        =   2
               Top             =   30
               Width           =   3435
            End
         End
         Begin Threed.SSPanel pnlContainerName 
            Height          =   315
            Left            =   120
            TabIndex        =   4
            Top             =   1080
            Width           =   3495
            _Version        =   65536
            _ExtentX        =   6165
            _ExtentY        =   556
            _StockProps     =   15
            BackColor       =   -2147483633
            BevelOuter      =   1
            Begin VB.TextBox txtContainerName 
               Appearance      =   0  'Flat
               BorderStyle     =   0  'None
               Height          =   255
               Left            =   30
               MaxLength       =   32
               TabIndex        =   5
               Top             =   30
               Width           =   3435
            End
         End
         Begin VB.Label lblContainerType 
            Appearance      =   0  'Flat
            Caption         =   "&Type of new container:"
            ForeColor       =   &H80000008&
            Height          =   195
            Left            =   120
            TabIndex        =   0
            Top             =   180
            Width           =   1980
         End
         Begin VB.Label lblContainerName 
            Appearance      =   0  'Flat
            Caption         =   "&Name of new container:"
            ForeColor       =   &H80000008&
            Height          =   195
            Left            =   120
            TabIndex        =   3
            Top             =   840
            Width           =   2040
         End
      End
      Begin VB.CommandButton cmdOk 
         Appearance      =   0  'Flat
         Caption         =   "OK"
         Default         =   -1  'True
         Height          =   375
         Left            =   4320
         TabIndex        =   6
         Top             =   180
         Width           =   1095
      End
      Begin VB.CommandButton cmdCancel 
         Appearance      =   0  'Flat
         Cancel          =   -1  'True
         Caption         =   "Cancel"
         Height          =   375
         Left            =   4320
         TabIndex        =   7
         Top             =   600
         Width           =   1095
      End
   End
End
Attribute VB_Name = "frmNewContainer"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

Dim OldMousePointer%
Dim CallingForm As Form

Private Sub cmdCancel_Click()
    Unload Me
End Sub

Private Sub cmdOk_Click()
    NewContaName$ = txtContainerName
    NewContaTag& = cboContainerType.ItemData(cboContainerType.ListIndex)

    NewContaUserCanceled% = False
    Unload Me
End Sub

Private Sub Form_Load()
    Dim NewLeft%, NewTop%, i%, Count&, lRet&
    Dim FolderInfos() As FOLDER_INFO

    'Save the old mouse pointer
    Set CallingForm = Screen.ActiveForm
    OldMousePointer% = CallingForm.MousePointer
    
    'Turn on normal pointer
    Me.MousePointer = NORMAL
    
    'Center form on calling form
    NewLeft% = CallingForm.left + (CallingForm.Width - Width) / 2
    If NewLeft% + Width > Screen.Width Then NewLeft% = Screen.Width - Width
    If NewLeft% < 0 Then NewLeft% = 0
    NewTop% = CallingForm.top + (CallingForm.Height - Height) / 2
    If NewTop% + Height > Screen.Height Then NewTop% = Screen.Height - Height
    If NewTop% < 0 Then NewTop% = 0
    left = NewLeft%
    top = NewTop%
    
    'Set default to be user canceled
    NewContaUserCanceled% = True
    
    'Enumerate containers
    lRet& = SmsEnumContainers&(FolderInfos, Count&)
    If (lRet& <> SMS_OK) Then GoTo FormLoadErr

    'Add each container to the dropdown list box
    For i% = 0 To CInt(Count&) - 1
        cboContainerType.AddItem FolderInfos(i%).pszTag, i%
        cboContainerType.ItemData(i%) = FolderInfos(i%).dwTag
    Next i%
    cboContainerType.ListIndex = 0

    Exit Sub

FormLoadErr:
    MsgBox "FormLoadErr: Unexpected error", MB_OK, Me.Caption
End Sub

Private Sub Form_Unload(Cancel As Integer)
    'Replace mouse pointer
    CallingForm.MousePointer = OldMousePointer%
End Sub

