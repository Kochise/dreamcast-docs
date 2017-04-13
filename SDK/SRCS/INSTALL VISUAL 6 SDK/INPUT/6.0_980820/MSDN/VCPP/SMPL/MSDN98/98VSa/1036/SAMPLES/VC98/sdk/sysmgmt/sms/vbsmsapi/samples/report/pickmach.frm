VERSION 4.00
Begin VB.Form frmPickMachineGroups 
   Appearance      =   0  'Flat
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Pick Machine Group for Report"
   ClientHeight    =   4125
   ClientLeft      =   1740
   ClientTop       =   4650
   ClientWidth     =   5115
   BeginProperty Font 
      name            =   "MS Sans Serif"
      charset         =   1
      weight          =   700
      size            =   8.25
      underline       =   0   'False
      italic          =   0   'False
      strikethrough   =   0   'False
   EndProperty
   ForeColor       =   &H80000008&
   Height          =   4530
   Left            =   1680
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4125
   ScaleWidth      =   5115
   Top             =   4305
   Width           =   5235
   Begin VB.CommandButton cmdOk 
      Appearance      =   0  'Flat
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   3900
      TabIndex        =   5
      Top             =   120
      Width           =   1095
   End
   Begin VB.CommandButton cmdCancel 
      Appearance      =   0  'Flat
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Left            =   3900
      TabIndex        =   4
      Top             =   540
      Width           =   1095
   End
   Begin Threed.SSPanel pnlOutlineBackdrop 
      Height          =   3870
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   3615
      _Version        =   65536
      _ExtentX        =   6376
      _ExtentY        =   6826
      _StockProps     =   15
      Begin Threed.SSPanel pnlSrceFrame 
         Height          =   3390
         Left            =   240
         TabIndex        =   1
         Top             =   360
         Width           =   3255
         _Version        =   65536
         _ExtentX        =   5741
         _ExtentY        =   5980
         _StockProps     =   15
         BevelOuter      =   1
         Autosize        =   3
         Begin MSOutl.Outline olnData 
            Height          =   3360
            Left            =   15
            TabIndex        =   2
            Top             =   15
            Width           =   3225
            _Version        =   65536
            _ExtentX        =   5689
            _ExtentY        =   5927
            _StockProps     =   77
            BackColor       =   -2147483643
            Style           =   1
         End
      End
      Begin VB.Label Label1 
         Appearance      =   0  'Flat
         AutoSize        =   -1  'True
         Caption         =   "&Report on machines in:"
         ForeColor       =   &H80000008&
         Height          =   195
         Left            =   240
         TabIndex        =   3
         Top             =   120
         Width           =   1980
      End
   End
End
Attribute VB_Name = "frmPickMachineGroups"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

'//****************************************************************************
'//
'//  Copyright (c) 1995, Microsoft Corporation
'//
'//  File:  PICKMACH.FRM
'//
'//  History:
'//
'//      Gary Fuehrer, SEA   5/9/95      Created.
'//
'//****************************************************************************

Dim OldMousePointer%
Dim CallingForm As Form

Dim hConnect&
Dim db As Database

'State flags
Dim bGetMachineGroupData%  'If True, getting machine group data from SMS.
Dim MachineGroupID$()

'Some relavent names for the outline control pictures
Const MSOUTLINE_PICTURE_GROUP = MSOUTLINE_PICTURE_CLOSED
Const MSOUTLINE_PICTURE_MACHINE = MSOUTLINE_PICTURE_OPEN

Private Sub cmdCancel_Click()
    Unload Me
End Sub

Private Sub cmdOk_Click()
    If olnData.ListIndex >= 0 Then
        'Return list of group selected
        MachineGroupPicked$ = MachineGroupID$(olnData.ItemData(olnData.ListIndex))

        'Set to login success
        PickMachineGroupsUserCanceled% = False
    End If

    Unload Me
End Sub

Private Sub Form_Activate()
    bGetMachineGroupData% = True
    GetMachineGroups
    If bGetMachineGroupData% Then
        bGetMachineGroupData% = False
    Else: Unload Me
    End If
End Sub

Private Sub Form_Load()
    Dim NewLeft%, NewTop%
    
    'Save the old mouse pointer
    Set CallingForm = Screen.ActiveForm
    OldMousePointer% = CallingForm.MousePointer
    
    'Turn on normal pointer
    MousePointer = NORMAL
    
    'Center form on calling form
    NewLeft% = CallingForm.left + (CallingForm.Width - Width) / 2
    If NewLeft% + Width > Screen.Width Then NewLeft% = Screen.Width - Width
    If NewLeft% < 0 Then NewLeft% = 0
    NewTop% = CallingForm.top + (CallingForm.Height - Height) / 2
    If NewTop% + Height > Screen.Height Then NewTop% = Screen.Height - Height
    If NewTop% < 0 Then NewTop% = 0
    left = NewLeft%
    top = NewTop%

    'Copy parameters locally
    hConnect& = PickMachineGroupshConnect&
    Set db = PickMachineGroupsDB

    'Set default to be user canceled
    PickMachineGroupsUserCanceled% = True
End Sub

Private Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)
    If bGetMachineGroupData% Then
        bGetMachineGroupData% = False
        Cancel = True
        Exit Sub
    End If
End Sub

Private Sub Form_Unload(Cancel As Integer)
    'Replace mouse pointer
    CallingForm.MousePointer = OldMousePointer%
End Sub

Private Sub GetMachineGroups()
    Dim hContainer&, hSubFolder&, FolderType&, TypeName$
    Dim sScalar As SCALAR, GroupID$, GroupName$
    Dim lRet&, Resp%, ListIndex%

    'Reset list index
    ListIndex% = 0
    ReDim MachineGroupID$(0 To 0)

    lRet& = SmsOpenContainer&(C_MACHINEGROUP, hConnect&, hContainer&)
    If lRet& <> SMS_OK Then
        MsgBox "SMS Error:" + Chr$(10) + Chr$(10) + SMSError$(lRet&), MB_ICONEXCLAMATION + MB_OK, Caption
        Exit Sub
    End If

    lRet& = SmsPopulate&(hContainer&, POP_SYNC, ByVal 0&)
    If lRet& <> SMS_OK And lRet& <> SMS_EMPTY Then
        MsgBox "SMS Error:" + Chr$(10) + Chr$(10) + SMSError$(lRet&), MB_ICONEXCLAMATION + MB_OK, Caption
        GoTo GetMachineGroupsCleanup
    End If

    'List the machine groups in this container
    Resp% = IDOK
    lRet& = SmsGetNextFolder&(hContainer&, F_ANY, hSubFolder&)
    Do While lRet& = SMS_OK
        'Get this folder's type (expect Machine Group)
        lRet& = SmsGetFolderType&(hSubFolder&, FolderType&, TypeName$)
        If lRet& <> SMS_OK Or TypeName <> "Machine Group" Then
            If lRet& <> SMS_OK Then Resp% = MsgBox("SMS Error:" + Chr$(10) + Chr$(10) + SMSError$(lRet&), MB_ICONEXCLAMATION + MB_ABORTRETRYIGNORE, Caption)
            GoTo GetMachineGroupsCont
        End If

        'Get this folder's ID
        lRet& = SmsGetFolderID&(hSubFolder&, GroupID$)
        If lRet& <> SMS_OK Then
            Resp% = MsgBox("SMS Error:" + Chr$(10) + Chr$(10) + SMSError$(lRet&), MB_ICONEXCLAMATION + MB_ABORTRETRYIGNORE, Caption)
            GoTo GetMachineGroupsCont
        End If

        'Get this group's name
        lRet& = SmsGetScalarByName&(hSubFolder&, "Name", sScalar)
        If lRet& <> SMS_OK Then
            Resp% = MsgBox("SMS Error:" + Chr$(10) + Chr$(10) + SMSError$(lRet&), MB_ICONEXCLAMATION + MB_ABORTRETRYIGNORE, Caption)
            GoTo GetMachineGroupsCont
        End If
        GroupName$ = sScalar.pszValue

        DoEvents

        'Check to see if the user wants to cancel
        If bGetMachineGroupData% Then
            'Add item to outline control and array
            olnData.AddItem GroupName$, ListIndex%
            olnData.Indent(ListIndex%) = 1
            olnData.PictureType(ListIndex%) = MSOUTLINE_PICTURE_GROUP
            olnData.ItemData(ListIndex%) = ListIndex%

            'Add GroupID to the array
            If ListIndex% >= UBound(MachineGroupID$, 1) Then ReDim Preserve MachineGroupID$(0 To ListIndex% + 32)
            MachineGroupID$(ListIndex%) = GroupID$

            ListIndex% = ListIndex% + 1
            Resp% = IDOK
        Else: Resp% = IDABORT
        End If

GetMachineGroupsCont:
        'Check the user response
        Select Case Resp%
            Case IDOK, IDIGNORE
                lRet& = SmsCloseFolder&(hSubFolder&)
                lRet& = SmsGetNextFolder&(hContainer&, F_ANY, hSubFolder&)
                Resp% = IDOK
            Case IDABORT
                lRet& = SmsCloseFolder&(hSubFolder&)
                lRet& = SMS_NO_MORE_DATA
            Case IDRETRY
                lRet& = SMS_OK
        End Select
    Loop
    If lRet& <> SMS_NO_MORE_DATA Then
        MsgBox "SMS Error:" + Chr$(10) + Chr$(10) + SMSError$(lRet&), MB_ICONEXCLAMATION + MB_OK, Caption
    End If
        
GetMachineGroupsCleanup:
    lRet& = SmsCloseContainer&(hContainer&)
End Sub

Private Sub olnData_DblClick()
    cmdOk_Click
End Sub

