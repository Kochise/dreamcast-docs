VERSION 4.00
Begin VB.Form frmPickProperties 
   Appearance      =   0  'Flat
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Pick Machine Properties"
   ClientHeight    =   5085
   ClientLeft      =   1740
   ClientTop       =   4650
   ClientWidth     =   9930
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
   Height          =   5490
   Left            =   1680
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5085
   ScaleWidth      =   9930
   Top             =   4305
   Width           =   10050
   Begin VB.CommandButton cmdOk 
      Appearance      =   0  'Flat
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   8700
      TabIndex        =   13
      Top             =   120
      Width           =   1095
   End
   Begin VB.CommandButton cmdCancel 
      Appearance      =   0  'Flat
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Left            =   8700
      TabIndex        =   12
      Top             =   540
      Width           =   1095
   End
   Begin Threed.SSPanel pnlOutlineBackdrop 
      Height          =   4830
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   8475
      _Version        =   65536
      _ExtentX        =   14949
      _ExtentY        =   8520
      _StockProps     =   15
      Begin Threed.SSFrame frameProperties 
         Height          =   3990
         Left            =   480
         TabIndex        =   1
         Top             =   720
         Width           =   7815
         _Version        =   65536
         _ExtentX        =   13785
         _ExtentY        =   7038
         _StockProps     =   14
         ForeColor       =   0
         Enabled         =   0   'False
         Begin VB.CommandButton cmdRemove 
            Appearance      =   0  'Flat
            Caption         =   "&Remove >"
            Height          =   375
            Left            =   3330
            TabIndex        =   7
            Top             =   900
            Width           =   1035
         End
         Begin VB.CommandButton cmdAdd 
            Appearance      =   0  'Flat
            Caption         =   "< &Add"
            Height          =   375
            Left            =   3330
            TabIndex        =   6
            Top             =   480
            Width           =   1035
         End
         Begin Threed.SSPanel pnlDestFrame 
            Height          =   3390
            Left            =   180
            TabIndex        =   2
            Top             =   480
            Width           =   3075
            _Version        =   65536
            _ExtentX        =   5424
            _ExtentY        =   5980
            _StockProps     =   15
            BevelOuter      =   1
            Autosize        =   3
            Begin MSOutl.Outline olnDest 
               Height          =   3360
               Left            =   15
               TabIndex        =   3
               Top             =   15
               Width           =   3045
               _Version        =   65536
               _ExtentX        =   5371
               _ExtentY        =   5927
               _StockProps     =   77
               BackColor       =   -2147483643
               PathSeparator   =   "|"
               Style           =   1
            End
         End
         Begin Threed.SSPanel pnlSrceFrame 
            Height          =   3390
            Left            =   4440
            TabIndex        =   4
            Top             =   480
            Width           =   3255
            _Version        =   65536
            _ExtentX        =   5741
            _ExtentY        =   5980
            _StockProps     =   15
            BevelOuter      =   1
            Autosize        =   3
            Begin MSOutl.Outline olnSrce 
               Height          =   3360
               Left            =   15
               TabIndex        =   5
               Top             =   15
               Width           =   3225
               _Version        =   65536
               _ExtentX        =   5689
               _ExtentY        =   5927
               _StockProps     =   77
               BackColor       =   -2147483643
               PathSeparator   =   "|"
               Style           =   1
            End
         End
         Begin VB.Label lblDest 
            Appearance      =   0  'Flat
            AutoSize        =   -1  'True
            Caption         =   "&Don't include these properties"
            ForeColor       =   &H80000008&
            Height          =   195
            Left            =   4440
            TabIndex        =   9
            Top             =   240
            Width           =   2565
         End
         Begin VB.Label lblSrce 
            Appearance      =   0  'Flat
            AutoSize        =   -1  'True
            Caption         =   "&Include these properties"
            ForeColor       =   &H80000008&
            Height          =   195
            Left            =   240
            TabIndex        =   8
            Top             =   240
            Width           =   2070
         End
      End
      Begin Threed.SSOption optAllProperties 
         Height          =   195
         Left            =   240
         TabIndex        =   11
         Top             =   180
         Width           =   4215
         _Version        =   65536
         _ExtentX        =   7435
         _ExtentY        =   344
         _StockProps     =   78
         Caption         =   "Include all properties in report"
         Value           =   -1  'True
      End
      Begin Threed.SSOption optSelectProperties 
         Height          =   195
         Left            =   240
         TabIndex        =   10
         TabStop         =   0   'False
         Top             =   540
         Width           =   4335
         _Version        =   65536
         _ExtentX        =   7646
         _ExtentY        =   344
         _StockProps     =   78
         Caption         =   "Select properties in report"
      End
   End
End
Attribute VB_Name = "frmPickProperties"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

'//****************************************************************************
'//
'//  Copyright (c) 1995, Microsoft Corporation
'//
'//  File:  PICKPROP.FRM
'//
'//  History:
'//
'//      Gary Fuehrer, SEA   5/9/95      Created.
'//
'//****************************************************************************

Dim OldMousePointer%
Dim CallingForm As Form

Dim hConnect&
Dim MachineGroupID$

'State flag and Arrays
Dim bGetData%  'If True, getting machine Attributes from SMS.
Dim PropertyList$()
Dim PropertyCount%

'Some relavent names for the outline control pictures
Const MSOUTLINE_PICTURE_GROUP = MSOUTLINE_PICTURE_CLOSED
Const MSOUTLINE_PICTURE_MACHINE = MSOUTLINE_PICTURE_OPEN

Private Sub AddPropertyToOutline(Property$, oln As Outline, ByVal PropertyData&)
    Dim Pos1%, Pos2%, PropertyCategory$, PropertyVersion$, PropertyName$
    Dim ListIndex%, Found%

    'Property Name not available. Use part of Property ID string.
    Pos1% = InStr(Property$, "|")
    Pos2% = InStr(Pos1% + 1, Property$, "|")
    If Pos1% <= 0 Or Pos2% <= 0 Then Exit Sub
    PropertyCategory$ = LCase$(left$(Property$, Pos1% - 1))
    PropertyVersion$ = LCase$(Mid$(Property$, Pos2% + 1))
    PropertyName$ = LCase$(Mid$(Property$, Pos1% + 1, Pos2% - Pos1% - 1))

    'Find category
    Found% = False
    For ListIndex% = 0 To oln.ListCount - 1
        If oln.Indent(ListIndex%) <= 1 Then
            If oln.List(ListIndex%) = PropertyCategory$ Then
                Found% = True
                Exit For
            End If
        End If
    Next ListIndex%
    If Not Found% Then
        'Add a new category item
        oln.AddItem PropertyCategory$, ListIndex%
        oln.Indent(ListIndex%) = 1
        oln.PictureType(ListIndex) = MSOUTLINE_PICTURE_CLOSED
        oln.ItemData(ListIndex%) = -1
    End If

    'Find Property
    Found% = False
    For ListIndex% = ListIndex% + 1 To oln.ListCount - 1
        If oln.Indent(ListIndex%) <= 2 Then
            If oln.Indent(ListIndex%) <= 1 Then Exit For
            If oln.List(ListIndex%) = PropertyName$ Then
                Found% = True
                Exit For
            End If
        End If
    Next ListIndex%
    If Not Found% Then
        'Add a new version item
        oln.AddItem PropertyName$, ListIndex%
        oln.Indent(ListIndex%) = 2
        oln.PictureType(ListIndex) = MSOUTLINE_PICTURE_LEAF
        oln.ItemData(ListIndex%) = PropertyData&

        oln.Refresh
    End If
End Sub

Private Sub cmdAdd_Click()
    Dim ListIndex%, Indent%

    ListIndex% = olnSrce.ListIndex
    If ListIndex% < 0 Then Exit Sub
    Indent% = olnSrce.Indent(ListIndex%)

    'Add selection
    If olnSrce.ItemData(ListIndex%) >= 0 Then
        AddPropertyToOutline PropertyList$(olnSrce.ItemData(ListIndex%)), olnDest, olnSrce.ItemData(ListIndex%)
    End If

    'Add children of selection
    Do While ListIndex% + 1 < olnSrce.ListCount
        ListIndex% = ListIndex% + 1
        If olnSrce.Indent(ListIndex%) > Indent% Then
            If olnSrce.ItemData(ListIndex%) >= 0 Then
                AddPropertyToOutline PropertyList$(olnSrce.ItemData(ListIndex%)), olnDest, olnSrce.ItemData(ListIndex%)
            End If
        Else: Exit Do
        End If
    Loop
End Sub

Private Sub cmdCancel_Click()
    Unload Me
End Sub

Private Sub cmdOk_Click()
    Dim ListIndex%

    PickPropertiesCount% = 0

    PickPropertiesIsFiltered% = optSelectProperties.Value
    If PickPropertiesIsFiltered% Then
        'Return list of properties picked
        ReDim PickPropertiesList$(0 To olnDest.ListCount)
        For ListIndex% = 0 To olnDest.ListCount - 1
            If olnDest.Indent(ListIndex%) = 2 Then
                PickPropertiesList$(PickPropertiesCount%) = PropertyList$(olnDest.ItemData(ListIndex%))
                PickPropertiesCount% = PickPropertiesCount% + 1
            End If
        Next ListIndex%
    End If

    'User didn't cancel
    PickPropertiesUserCanceled% = False
    Unload Me
End Sub

Private Sub cmdRemove_Click()
    Dim ListIndex%, Indent%

    ListIndex% = olnDest.ListIndex
    If ListIndex% < 0 Then Exit Sub
    Indent% = olnDest.Indent(ListIndex%)

    'Remove selection
    olnDest.RemoveItem ListIndex%

    'Remove children of selection
    Do While ListIndex% < olnDest.ListCount
        If olnDest.Indent(ListIndex%) > Indent% Then
            olnDest.RemoveItem ListIndex%
        Else: Exit Do
        End If
    Loop
End Sub

Private Sub Form_Activate()
    bGetData% = True
    GetMachineGroups
    If bGetData% Then
        bGetData% = False
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
    hConnect& = PickPropertieshConnect&
    MachineGroupID$ = PickPropertiesMachineGroupID$

    'Set default to be user canceled
    PickPropertiesUserCanceled% = True
End Sub

Private Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)
    If bGetData% Then
        bGetData% = False
        Cancel = True
        Exit Sub
    End If
End Sub

Private Sub Form_Unload(Cancel As Integer)
    'Replace mouse pointer
    CallingForm.MousePointer = OldMousePointer%
End Sub

Private Sub GetMachineGroups()
    Dim hContainer&, hSubFolder&
    Dim lRet&, Resp%

    ReDim PropertyList$(0 To 0)
    PropertyCount% = 0

    lRet& = SmsOpenContainer&(C_MACHINEGROUP, hConnect&, hContainer&)
    If lRet& <> SMS_OK Then
        MsgBox "SMS Error:" + Chr$(10) + Chr$(10) + SMSError$(lRet&), MB_ICONEXCLAMATION + MB_OK, Caption
        Exit Sub
    End If

    lRet& = SmsPopulate&(hContainer&, POP_SYNC, ByVal 0&)
    If lRet& <> SMS_OK And lRet& <> SMS_EMPTY Then
        MsgBox "SMS Error:" + Chr$(10) + Chr$(10) + SMSError$(lRet&), MB_ICONEXCLAMATION + MB_OK, Caption
        GoTo GetMachineGroupsQuit
    End If

    'List the machine groups in this container
    Resp% = IDOK
    lRet& = SmsGetNextFolder&(hContainer&, F_ANY, hSubFolder&)
    Do While lRet& = SMS_OK
        'Get subfolders
        Resp% = GetMachines%(hSubFolder&)

        'See if the user canceled
        If Not bGetData% Then Resp% = IDABORT

        'Check the user response
        Select Case Resp%
            Case IDOK, IDIGNORE
                lRet& = SmsCloseFolder&(hSubFolder&)
                lRet& = SmsGetNextFolder&(hContainer&, F_ANY, hSubFolder&)
                Resp% = IDOK
            Case IDABORT
                lRet& = SmsCloseFolder&(hSubFolder&)
                lRet& = SMS_NO_MORE_DATA
        End Select
    Loop
    If lRet& <> SMS_NO_MORE_DATA Then
        MsgBox "SMS Error:" + Chr$(10) + Chr$(10) + SMSError$(lRet&), MB_ICONEXCLAMATION + MB_OK, Caption
    End If

GetMachineGroupsQuit:
    lRet& = SmsCloseContainer&(hContainer&)
End Sub

Private Function GetMachineProperties%(ByVal hFolder&)
    Dim hSubFolder&, TypeName$, FolderType&
    Dim lRet&, Resp%

    'Default return value IDOK (Entry added)
    GetMachineProperties% = IDOK

    'Get this folder's type (expect Machine)
    lRet& = SmsGetFolderType&(hFolder&, FolderType&, TypeName$)
    If lRet& <> SMS_OK Then
        GetMachineProperties% = MsgBox("SMS Error:" + Chr$(10) + Chr$(10) + SMSError$(lRet&), MB_ICONEXCLAMATION + MB_ABORTRETRYIGNORE, Caption)
        Exit Function
    End If

    Select Case TypeName$
        Case "Machine"

        Case Else
            Exit Function
    End Select

    'List the properties in this machine folder
    Resp% = IDOK
    lRet& = SmsGetNextFolder&(hFolder&, F_ANY, hSubFolder&)
    Do While lRet& = SMS_OK
        'Get subfolders
        Resp% = GetProperty%(hSubFolder&)

        'See if user canceled
        If Not bGetData% Then Resp% = IDABORT

        'Check the user response
        Select Case Resp%
            Case IDOK, IDIGNORE
                lRet& = SmsCloseFolder&(hSubFolder&)
                lRet& = SmsGetNextFolder&(hFolder&, F_ANY, hSubFolder&)
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

    'Set the return value (either IDABORT or IDOK)
    GetMachineProperties% = Resp%
End Function

Private Function GetMachines%(hFolder&)
    Dim hSubFolder&, TypeName$, FolderType&, Group$
    Dim lRet&, Resp%

    'Default return value IDOK (Entry added)
    GetMachines% = IDOK

    'Get this folder's type (expect Machine Group)
    lRet& = SmsGetFolderType&(hFolder&, FolderType&, TypeName$)
    If lRet& <> SMS_OK Then
        GetMachines% = MsgBox("SMS Error:" + Chr$(10) + Chr$(10) + SMSError$(lRet&), MB_ICONEXCLAMATION + MB_ABORTRETRYIGNORE, Caption)
        Exit Function
    End If

    Select Case TypeName$
        Case "Machine Group"
            lRet& = SmsGetFolderID&(hFolder&, Group$)
            If lRet& <> SMS_OK Then
                GetMachines% = MsgBox("SMS Error:" + Chr$(10) + Chr$(10) + SMSError$(lRet&), MB_ICONEXCLAMATION + MB_ABORTRETRYIGNORE, Caption)
                Exit Function
            End If

            'See if this is the choosen group
            If Group$ <> MachineGroupID$ Then Exit Function

        Case Else
            Exit Function
    End Select

    'List the machine groups in this container
    Resp% = IDOK
    lRet& = SmsGetNextFolder&(hFolder&, F_ANY, hSubFolder&)
    Do While lRet& = SMS_OK
        'Get subfolders
        Resp% = GetMachineProperties%(hSubFolder&)

        'See if the user canceled
        If Not bGetData% Then Resp% = IDABORT

        'Check the user response
        Select Case Resp%
            Case IDOK, IDIGNORE
                lRet& = SmsCloseFolder&(hSubFolder&)
                lRet& = SmsGetNextFolder&(hFolder&, F_ANY, hSubFolder&)
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

    'Set the return value (either IDABORT or IDOK)
    GetMachines% = Resp%
End Function

Private Function GetProperty%(ByVal hFolder&)
    Dim TypeName$, FolderType&
    Dim Property$
    Dim lRet&, Resp%, Index%

    'Default return value IDOK (Entry added)
    GetProperty% = IDOK

    'Get this folder's type (expect Group)
    lRet& = SmsGetFolderType&(hFolder&, FolderType&, TypeName$)
    If lRet& <> SMS_OK Then
        GetProperty% = MsgBox("SMS Error:" + Chr$(10) + Chr$(10) + SMSError$(lRet&), MB_ICONEXCLAMATION + MB_ABORTRETRYIGNORE, Caption)
        Exit Function
    End If

    Select Case TypeName$
        Case "Group"
            lRet& = SmsGetFolderID&(hFolder&, Property$)

            If lRet& <> SMS_OK Then
                GetProperty% = MsgBox("SMS Error:" + Chr$(10) + Chr$(10) + SMSError$(lRet&), MB_ICONEXCLAMATION + MB_ABORTRETRYIGNORE, Caption)
                Exit Function
            End If
        Case Else
            Exit Function
    End Select

    DoEvents

    If bGetData% Then
        'Add item to outline
        AddPropertyToOutline Property$, olnSrce, PropertyCount%

        'Add to property list
        If UBound(PropertyList$) >= PropertyCount% Then ReDim Preserve PropertyList$(0 To PropertyCount% + 32)
        PropertyList$(PropertyCount%) = Property$
        PropertyCount% = PropertyCount% + 1

        Resp% = IDOK
    Else: Resp% = IDABORT
    End If

    'Set the return value (either IDABORT or IDOK)
    GetProperty% = Resp%
End Function

Private Sub olnDest_Click()
    '
End Sub

Private Sub olnDest_Collapse(ListIndex As Integer)
    If olnDest.PictureType(ListIndex) = MSOUTLINE_PICTURE_OPEN Then
        olnDest.PictureType(ListIndex) = MSOUTLINE_PICTURE_CLOSED
    End If
End Sub

Private Sub olnDest_DblClick()
    olnDest.Expand(olnDest.ListIndex) = Not olnDest.Expand(olnDest.ListIndex)
End Sub

Private Sub olnDest_Expand(ListIndex As Integer)
    If olnDest.Indent(ListIndex) <= 1 Then
        If olnDest.Expand(ListIndex) Then
            olnDest.PictureType(ListIndex) = MSOUTLINE_PICTURE_OPEN
        Else: olnDest.PictureType(ListIndex) = MSOUTLINE_PICTURE_CLOSED
        End If
    End If
End Sub

Private Sub olnDest_PictureClick(ListIndex As Integer)
    olnDest.ListIndex = ListIndex
    olnDest_Click
End Sub

Private Sub olnDest_PictureDblClick(ListIndex As Integer)
    olnDest_PictureClick ListIndex
    olnDest_DblClick
End Sub

Private Sub olnSrce_Click()
    '
End Sub

Private Sub olnSrce_Collapse(ListIndex As Integer)
    If olnSrce.PictureType(ListIndex) = MSOUTLINE_PICTURE_OPEN Then
        olnSrce.PictureType(ListIndex) = MSOUTLINE_PICTURE_CLOSED
    End If
End Sub

Private Sub olnSrce_DblClick()
    olnSrce.Expand(olnSrce.ListIndex) = Not olnSrce.Expand(olnSrce.ListIndex)
End Sub

Private Sub olnSrce_Expand(ListIndex As Integer)
    If olnSrce.Indent(ListIndex) <= 1 Then
        If olnSrce.Expand(ListIndex) Then
            olnSrce.PictureType(ListIndex) = MSOUTLINE_PICTURE_OPEN
        Else: olnSrce.PictureType(ListIndex) = MSOUTLINE_PICTURE_CLOSED
        End If
    End If
End Sub

Private Sub olnSrce_PictureClick(ListIndex As Integer)
    olnSrce.ListIndex = ListIndex
    olnSrce_Click
End Sub

Private Sub olnSrce_PictureDblClick(ListIndex As Integer)
    olnSrce_PictureClick ListIndex
    olnSrce_DblClick
End Sub

Private Sub optAllProperties_Click(Value As Integer)
    frameProperties.Enabled = Not Value
End Sub

Private Sub optSelectProperties_Click(Value As Integer)
    frameProperties.Enabled = Value
End Sub

