VERSION 4.00
Begin VB.Form frmMachineGrpReport 
   Appearance      =   0  'Flat
   BackColor       =   &H80000005&
   Caption         =   "Machine Group Report"
   ClientHeight    =   4215
   ClientLeft      =   1560
   ClientTop       =   2610
   ClientWidth     =   8505
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
   Height          =   4620
   Icon            =   "MACHGRP.frx":0000
   Left            =   1500
   LinkTopic       =   "Form1"
   MDIChild        =   -1  'True
   ScaleHeight     =   4215
   ScaleWidth      =   8505
   Top             =   2265
   Width           =   8625
   Begin VB.CommandButton cmdSave 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Save"
      Height          =   315
      Left            =   480
      TabIndex        =   4
      TabStop         =   0   'False
      Top             =   2580
      Visible         =   0   'False
      Width           =   3735
   End
   Begin VB.CommandButton cmdSaveAs 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Save As"
      Height          =   315
      Left            =   480
      TabIndex        =   3
      TabStop         =   0   'False
      Top             =   2880
      Visible         =   0   'False
      Width           =   3735
   End
   Begin VB.CheckBox chkDirty 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Dirty Bit"
      ForeColor       =   &H80000008&
      Height          =   195
      Left            =   4440
      TabIndex        =   2
      TabStop         =   0   'False
      Top             =   3540
      Visible         =   0   'False
      Width           =   1155
   End
   Begin VB.CommandButton cmdPrintPreview 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Print Preview"
      Height          =   315
      Left            =   480
      TabIndex        =   1
      TabStop         =   0   'False
      Top             =   3480
      Visible         =   0   'False
      Width           =   3735
   End
   Begin VB.CommandButton cmdPrint 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Print"
      Height          =   315
      Left            =   480
      TabIndex        =   0
      TabStop         =   0   'False
      Top             =   3180
      Visible         =   0   'False
      Width           =   3735
   End
   Begin VB.CommandButton cmdAbort 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Abort"
      Height          =   315
      Left            =   4440
      TabIndex        =   7
      TabStop         =   0   'False
      Top             =   3180
      Visible         =   0   'False
      Width           =   3735
   End
   Begin VB.CommandButton cmdInitialize 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Initialize"
      Height          =   315
      Left            =   4440
      TabIndex        =   8
      TabStop         =   0   'False
      Top             =   2880
      Visible         =   0   'False
      Width           =   3735
   End
   Begin VB.CommandButton cmdExport 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Export"
      Height          =   315
      Left            =   4440
      TabIndex        =   6
      TabStop         =   0   'False
      Top             =   2580
      Visible         =   0   'False
      Width           =   3735
   End
   Begin Crystal.CrystalReport CrystalReport 
      Left            =   840
      Top             =   960
      _ExtentX        =   741
      _ExtentY        =   741
      _StockProps     =   0
      ReportFileName  =   ""
      Destination     =   0
      WindowLeft      =   100
      WindowTop       =   100
      WindowWidth     =   480
      WindowHeight    =   300
      WindowTitle     =   ""
      WindowBorderStyle=   2
      WindowControlBox=   -1  'True
      WindowMaxButton =   -1  'True
      WindowMinButton =   -1  'True
      CopiesToPrinter =   1
      PrintFileName   =   ""
      PrintFileType   =   2
      SelectionFormula=   ""
      GroupSelectionFormula=   ""
      Connect         =   ""
      UserName        =   ""
      ReportSource    =   0
      BoundReportHeading=   ""
      BoundReportFooter=   -1  'True
   End
   Begin MSComDlg.CommonDialog CommonDialog 
      Left            =   360
      Top             =   960
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
   End
   Begin MSOutl.Outline olnData 
      Height          =   750
      Left            =   2340
      TabIndex        =   9
      Top             =   240
      Width           =   1500
      _Version        =   65536
      _ExtentX        =   2646
      _ExtentY        =   1323
      _StockProps     =   77
      BorderStyle     =   0
      Style           =   5
   End
   Begin VB.Label lblFileSpec 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "File Specification"
      ForeColor       =   &H80000008&
      Height          =   195
      Left            =   5940
      TabIndex        =   5
      Top             =   3540
      Visible         =   0   'False
      Width           =   2175
   End
End
Attribute VB_Name = "frmMachineGrpReport"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

'//****************************************************************************
'//
'//  Copyright (c) 1995, Microsoft Corporation
'//
'//  File:  MACHGRP.FRM
'//
'//  History:
'//
'//      Gary Fuehrer, SEA   5/9/95      Created.
'//
'//****************************************************************************

Dim hConnect&
Dim ReportTempSpec$
Dim NewNumber%
Dim db As Database
Dim dbt As Database

Dim MachineGroupID$
Dim PropertyList$()
Dim PropertyCount%
Dim bFilterProperties%

'Some relavent names for the outline control pictures
Const MSOUTLINE_PICTURE_GROUP = MSOUTLINE_PICTURE_CLOSED
Const MSOUTLINE_PICTURE_MACHINE = MSOUTLINE_PICTURE_OPEN
Const MSOUTLINE_PICTURE_PROPERTY = MSOUTLINE_PICTURE_LEAF

'State flags
Dim bGetData%  'If True, getting machine data from SMS.
Dim bReadData% 'If True, reading machine data from file.

Private Sub chkDirty_Click()
    UpdateCaption
End Sub

Private Sub cmdAbort_Click()
    'Handle user abort of current lengthy operation
    If bGetData% Then
        If MsgBox("Do you want to stop gathering machine data?" + Chr$(10) + Chr$(10) + "Click Yes to abort, No to continue.", MB_YESNO + MB_ICONQUESTION, Caption) = IDYES Then
            bGetData% = False
        End If
    ElseIf bReadData% Then
        If MsgBox("Do you want to stop reading machine data?" + Chr$(10) + Chr$(10) + "Click Yes to abort, No to continue.", MB_YESNO + MB_ICONQUESTION, Caption) = IDYES Then
            bReadData% = False
        End If
    End If
End Sub

Private Sub cmdExport_Click()
    Dim FileSpec$, nPos%, Resp%, FileKilled%

    'Build suggested file spec
    If lblFileSpec > "" Then
        nPos% = InStr(lblFileSpec, ".") - 1
        If nPos% < 0 Then nPos% = Len(lblFileSpec)
        FileSpec$ = left$(lblFileSpec, nPos) + ".TXT"
    Else: FileSpec$ = "*.TXT"
    End If

    'Get from the user the print file name
    FileSpec$ = GetSaveAsFileSpec$(FileSpec$, "ASCII Text (*.TXT) |*.TXT |All Files (*.*) |*.*")
    If FileSpec$ <= "" Then Exit Sub

    'See if we need to delete existing file
    '(Crystal Reports can't overwrite an existing file)
    If Dir$(FileSpec$) > "" Then
        FileKilled% = 0
        Do
            On Error Resume Next
            Kill FileSpec
            If Err > 0 Then
                Resp% = MsgBox("An error occured writing to file " + FileSpec$ + ":" + Chr$(10) + Error$ + Chr$(10) + Chr$(10) + "Do you want to try again?", MB_RETRYCANCEL Or MB_ICONQUESTION, Caption)
                If Resp% = IDCANCEL Then Exit Sub
            Else: FileKilled% = True
            End If
        Loop Until FileKilled%
    End If

    'Set the print file name and type
    CrystalReport.PrintFileName = CommonDialog.filename
    CrystalReport.PrintFileType = 2 'ASCII text

    'Export report code
    PrintDoc CRW_PRINT_TO_FILE
End Sub

Private Sub cmdInitialize_Click()
    If lblFileSpec > "" Then
        'Flag that we are in data reading mode
        bReadData% = True
        ReadMachineData -1
        bReadData% = False
    Else
        'Flag that we are in gathering data mode
        bGetData% = True
        GetMachineGroups
        bGetData% = False
    End If
End Sub

Private Sub cmdPrint_Click()
    'See if we need the print dialog
    If gbNeedPrintDialog% = True Then
        'Put up the print dialog
        CommonDialog.Flags = PD_NOSELECTION Or PD_NOPAGENUMS Or PD_HIDEPRINTTOFILE
        CommonDialog.Copies = 1
        CommonDialog.CancelError = True
        On Error Resume Next
        CommonDialog.Action = DLG_PRINT
        If Err = CDERR_CANCEL Then Exit Sub
        If Err > 0 Then
            MsgBox "An unexpected error occured:" + Chr$(10) + Chr$(10) + Error$, MB_OK Or MB_ICONEXCLAMATION, Caption
            Exit Sub
        End If
        On Error GoTo 0

        'Handle user printer settings
        CrystalReport.CopiesToPrinter = CommonDialog.Copies
    Else
        'Supply printer default settings
        CrystalReport.CopiesToPrinter = 1
    End If

    'Print document
    PrintDoc CRW_PRINT_TO_PRINTER
End Sub

Private Sub cmdPrintPreview_Click()
    'Print Preview document
    PrintDoc CRW_PRINT_TO_WINDOW
End Sub

Private Sub cmdSave_Click()
    'See if we need to do a Save or a Save As
    If lblFileSpec > "" Then
        SaveDoc lblFileSpec
    Else: cmdSaveAs_Click
    End If
End Sub

Private Sub cmdSaveAs_Click()
    Dim NewFileSpec$

    NewFileSpec$ = GetSaveAsFileSpec$(lblFileSpec, "Access 1.0 (*.MDB) |*.MDB |All Files (*.*) |*.*")
    If NewFileSpec$ <= "" Then Exit Sub

    SaveDoc NewFileSpec$
End Sub

Private Sub Form_Load()
    Dim i%

    'Position outline control (will be resized in Form Resize)
    olnData.left = 0
    olnData.top = 0

    chkDirty = False

    'Get local copy of parameters
    MachineGroupID$ = InitMachineGroupID$
    NewNumber% = InitReportNewNumber%
    hConnect& = InitReporthConnect&
    lblFileSpec = InitReportFileSpec$
    ReportTempSpec$ = InitReportTempSpec$
    bFilterProperties% = InitMachineGroupIsFiltered%
    PropertyCount% = InitMachineGroupPropertyCount%
    ReDim PropertyList$(0 To PropertyCount%)
    For i% = 0 To PropertyCount% - 1
        PropertyList$(i%) = InitMachineGroupProperties$(i%)
    Next i%

    Set dbt = OpenDatabase(ReportTempSpec$, True)
    If lblFileSpec > "" Then Set db = OpenDatabase(lblFileSpec, True, True)
End Sub

Private Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)
    Dim Resp%, FileSpec$

    'Make sure we're not in the middle of something
    If bGetData% Or bReadData% Then
        cmdAbort_Click
        Cancel = True
        Exit Sub
    End If

    'Give the user a chance to save document
    If chkDirty Then
        Resp% = MsgBox("This report has been modified. Save data before closing?", MB_YESNOCANCEL Or MB_ICONQUESTION, Caption)
        If Resp% = IDYES Then
            cmdSave_Click
            If chkDirty Then Cancel = True
        ElseIf Resp% = IDCANCEL Then: Cancel = True
        End If
    End If
End Sub

Private Sub Form_Resize()
    Static OldWidth, OldHeight
    Dim r As Rect, HBorderPixels%, VBorderPixels%

    'See if we're minimized
    If WindowState = MINIMIZED Then Exit Sub

    'Get client size of form (already in pixels, I find)
    GetClientRect hwnd, r
    HBorderPixels% = Width / X_PIX_SIZE - r.right
    VBorderPixels% = Height / Y_PIX_SIZE - r.bottom

    If OldWidth <> Width And Width - X_PIX_SIZE * HBorderPixels% > olnData.left Then
        olnData.Width = Width - X_PIX_SIZE * HBorderPixels% - olnData.left

        OldWidth = Width
    End If

    If OldHeight <> Height And Height - Y_PIX_SIZE * VBorderPixels% > olnData.top Then
        olnData.Height = Height - Y_PIX_SIZE * VBorderPixels% - olnData.top

        OldHeight = Height
    End If
End Sub

Private Sub Form_Unload(Cancel As Integer)
    dbt.Close
    If Not db Is Nothing Then db.Close

    'Kill temp file
    On Error Resume Next
    Kill ReportTempSpec$
    On Error GoTo 0

    FreeReportWindow Me
End Sub

Private Function GetAttributeValue%(db As Database, sScalar As SCALAR, GroupID&, MachineID&, PropertyID&, PropertyIndex%)
    Dim Attrib As AttributeRec, AttributeID&
    Dim lRet&

    'Add item to database
    AttributeID& = AddAttribute&(db, sScalar.pszName, "")
    If AttributeID& > 0 Then
        'Insert entry into database
        Attrib.MachineGroupID& = GroupID&
        Attrib.MachineID& = MachineID&
        Attrib.PropertyID& = PropertyID&
        Attrib.PropertyNum% = PropertyIndex%
        Attrib.AttributeID& = AttributeID&
        Attrib.Value$ = MakeNiceForCrystalReports$(sScalar.pszValue)
        If InsertAttribute&(db, Attrib) = 1 Then
            GetAttributeValue% = IDOK
        Else: GetAttributeValue% = MsgBox("Database Error:" + Chr$(10) + Chr$(10) + Error$, MB_ICONEXCLAMATION + MB_ABORTRETRYIGNORE, Caption)
        End If
    Else: GetAttributeValue% = MsgBox("Database Error:" + Chr$(10) + Chr$(10) + Error$, MB_ICONEXCLAMATION + MB_ABORTRETRYIGNORE, Caption)
    End If
End Function

Private Function GetItemID%(Attrib As AttributeRec, ByVal ListIndex%)
    Dim Indent%

    'Default return value 0 (nothing at list index)
    GetItemID% = 0
    If ListIndex% < 0 Or ListIndex% >= olnData.ListCount Then Exit Function

    Indent% = olnData.Indent(ListIndex%)
    GetItemID% = Indent% + 1

    If Indent% > 0 Then
        Attrib.MachineID = olnData.ItemData(ListIndex%)
        Do
            ListIndex% = ListIndex% - 1
        Loop Until olnData.Indent(ListIndex%) < Indent%
        Indent% = Indent% - 1
    End If

    Attrib.MachineGroupID = olnData.ItemData(ListIndex%)
End Function

Private Sub GetMachineGroups()
    Dim hContainer&, hSubFolder&, hFilter&
    Dim sScalar As SCALAR, sToken As TOKEN
    Dim lRet&, Resp%, PropertyIndex%

    lRet& = SmsOpenContainer&(C_MACHINEGROUP, hConnect&, hContainer&)
    If lRet& <> SMS_OK Then
        MsgBox "SMS Error:" + Chr$(10) + Chr$(10) + SMSError$(lRet&), MB_ICONEXCLAMATION + MB_OK, Caption
        Exit Sub
    End If

    'See if we need to filter certain properties
    If bFilterProperties% And PropertyCount% > 0 Then
        'Create a machine property filter
        lRet& = SmsCreateFilter&(GROUP_FILTER, hConnect&, hFilter)
        If lRet& <> SMS_OK Then
            MsgBox "SMS Error:" + Chr$(10) + Chr$(10) + SMSError$(lRet&), MB_ICONEXCLAMATION + MB_OK, Caption
            GoTo GetMachineGroupsCleanup
        End If

        'Add the desired properties into the filter as tokens
        sToken.szName = "GroupClass"
        sToken.dwOp = QOP_STR_EQ
        For PropertyIndex% = 0 To PropertyCount% - 1
            sToken.szValue = PropertyList$(PropertyIndex%)
            lRet& = SmsAddToken&(hFilter, OP_OR, sToken, AT_END)
            If lRet& <> SMS_OK Then
                MsgBox "SMS Error:" + Chr$(10) + Chr$(10) + SMSError$(lRet&), MB_ICONEXCLAMATION + MB_OK, Caption
                GoTo GetMachineGroupsCleanup
            End If
        Next PropertyIndex%

        'Set the property filter into the machine group container
        lRet& = SmsSetFilter&(hContainer&, hFilter&)
        If lRet& <> SMS_OK Then
            MsgBox "SMS Error:" + Chr$(10) + Chr$(10) + SMSError$(lRet&), MB_ICONEXCLAMATION + MB_OK, Caption
            GoTo GetMachineGroupsCleanup
        End If
    End If

    'Populate the machine group container
    lRet& = SmsPopulate&(hContainer&, POP_SYNC, ByVal 0&)
    If lRet& <> SMS_OK And lRet& <> SMS_EMPTY Then
        MsgBox "SMS Error:" + Chr$(10) + Chr$(10) + SMSError$(lRet&), MB_ICONEXCLAMATION + MB_OK, Caption
        GoTo GetMachineGroupsCleanup
    End If

    'List the machine groups in this container
    Resp% = IDOK
    lRet& = SmsGetNextFolder&(hContainer&, F_ANY, hSubFolder&)
    Do While lRet& = SMS_OK
        'Get subfolders
        Resp% = GetMachines%(dbt, hSubFolder&, CInt(olnData.ListCount))

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
            Case IDRETRY
                lRet& = SMS_OK
        End Select
    Loop
    If lRet& <> SMS_NO_MORE_DATA Then
        MsgBox "SMS Error:" + Chr$(10) + Chr$(10) + SMSError$(lRet&), MB_ICONEXCLAMATION + MB_OK, Caption
    End If
        
GetMachineGroupsCleanup:
    If hFilter Then lRet& = SmsCloseFilter&(hFilter&)
    lRet& = SmsCloseContainer&(hContainer&)
    chkDirty = CHECKED
End Sub

Private Function GetMachineProperties%(db As Database, ByVal hFolder&, ParentListIndex%, GroupID&)
    Dim hSubFolder&, TypeName$, FolderType&
    Dim sScalar As SCALAR, MachineID&, Machine$, MachineName$
    Dim ListIndex%, bGetDataOld%, PropertyIndex%
    Dim lRet&, Resp%, Index%, OldStatBarMsg$

    'Default return value IDOK (Entry added)
    GetMachineProperties% = IDOK

    'Location of next item to add to outline control
    ListIndex% = olnData.ListCount

    'Get this folder's type (expect Machine)
    lRet& = SmsGetFolderType&(hFolder&, FolderType&, TypeName$)
    If lRet& <> SMS_OK Then
        GetMachineProperties% = MsgBox("SMS Error:" + Chr$(10) + Chr$(10) + SMSError$(lRet&), MB_ICONEXCLAMATION + MB_ABORTRETRYIGNORE, Caption)
        Exit Function
    End If

    Select Case TypeName$
        Case "Machine"
            lRet& = SmsGetFolderID&(hFolder&, Machine$)
            If lRet& <> SMS_OK Then
                GetMachineProperties% = MsgBox("SMS Error:" + Chr$(10) + Chr$(10) + SMSError$(lRet&), MB_ICONEXCLAMATION + MB_ABORTRETRYIGNORE, Caption)
                Exit Function
            End If

            'Machine Name not available. Use Machine ID string
            MachineName$ = Machine$

        Case Else
            Exit Function
    End Select

    DoEvents

    'Check to see if the user wants to cancel
    If bGetData% Then
        'Add item to database
        MachineID& = AddMachine&(db, Machine$, MachineName$)
        If MachineID& > 0 Then
            'Add item to outline control
            olnData.AddItem MachineName$, ListIndex%
            olnData.Indent(ListIndex%) = 1
            olnData.PictureType(ListIndex%) = MSOUTLINE_PICTURE_MACHINE
            olnData.ItemData(ListIndex%) = MachineID&
            If olnData.IsItemVisible(ParentListIndex%) And Not olnData.Expand(ParentListIndex%) Then
                olnData.Expand(ParentListIndex%) = True
            End If
            If olnData.ListIndex = ListIndex% - 1 Then
                olnData.ListIndex = ListIndex%
            End If
            olnData.Refresh
            Resp% = IDOK
        Else: Resp% = MsgBox("Database Error:" + Chr$(10) + Chr$(10) + Error$, MB_ICONEXCLAMATION + MB_ABORTRETRYIGNORE, Caption)
        End If
    Else: Resp% = IDABORT
    End If

    'Preserve current status bar message
    OldStatBarMsg$ = GetStatBarMsg$()

    'Make sure everything is OK and get first subfolder
    If Resp% = IDOK Then
        lRet& = SmsGetNextFolder&(hFolder&, F_ANY, hSubFolder&)
    Else: lRet& = SMS_NO_MORE_DATA
    End If

    'List the properties in this machine folder
    PropertyIndex% = 0
    Do While lRet& = SMS_OK
        'Get subfolders
        Resp% = GetPropertyAttributes%(db, hSubFolder&, ListIndex%, GroupID&, MachineID&, PropertyIndex%)

        'See if user canceled
        If Not bGetData% Then Resp% = IDABORT

        'Check the user response
        Select Case Resp%
            Case IDOK, IDIGNORE
                lRet& = SmsCloseFolder&(hSubFolder&)
                lRet& = SmsGetNextFolder&(hFolder&, F_ANY, hSubFolder&)
                PropertyIndex% = PropertyIndex% + 1
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

    'Restore status bar message and menu caption
    SetStatBarMsg OldStatBarMsg$

    'Set the return value (either IDABORT or IDOK)
    GetMachineProperties% = Resp%
End Function

Private Function GetMachines%(db As Database, ByVal hFolder&, ParentListIndex%)
    Dim hSubFolder&, TypeName$, FolderType&
    Dim sScalar As SCALAR, GroupID&, Group$, GroupName$
    Dim ListIndex%, bGetDataOld%
    Dim lRet&, Resp%, Index%

    'Default return value IDOK (Entry added)
    GetMachines% = IDOK

    'Location of next item to add to outline control
    ListIndex% = olnData.ListCount

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

            lRet& = SmsGetScalarByName&(hFolder&, "Name", sScalar)
            If lRet& <> SMS_OK Then
                GetMachines% = MsgBox("SMS Error:" + Chr$(10) + Chr$(10) + SMSError$(lRet&), MB_ICONEXCLAMATION + MB_ABORTRETRYIGNORE, Caption)
                Exit Function
            End If
            GroupName$ = sScalar.pszValue

            'See if this is the choosen group
            If Group$ <> MachineGroupID$ Then Exit Function

        Case Else
            Exit Function
    End Select

    DoEvents

    'Check to see if the user wants to cancel
    If bGetData% Then
        'Add item to database
        GroupID& = AddMachineGroup&(db, Group$, GroupName$)
        If GroupID& > 0 Then
            'Add item to outline control
            olnData.AddItem GroupName$, ListIndex%
            olnData.Indent(ListIndex%) = 0
            olnData.PictureType(ListIndex%) = MSOUTLINE_PICTURE_GROUP
            olnData.ItemData(ListIndex%) = GroupID&
            If olnData.IsItemVisible(ParentListIndex%) And Not olnData.Expand(ParentListIndex%) Then
                olnData.Expand(ParentListIndex%) = True
            End If
            If olnData.ListIndex = ListIndex% - 1 Then
                olnData.ListIndex = ListIndex%
            End If
            olnData.Refresh
            Resp% = IDOK
        Else: Resp% = MsgBox("Database Error:" + Chr$(10) + Chr$(10) + Error$, MB_ICONEXCLAMATION + MB_ABORTRETRYIGNORE, Caption)
        End If
    Else: Resp% = IDABORT
    End If

    'Make sure everything is OK and get first subfolder
    If Resp% = IDOK Then
        lRet& = SmsGetNextFolder&(hFolder&, F_ANY, hSubFolder&)
    Else: lRet& = SMS_NO_MORE_DATA
    End If

    'List the machines in this machine group folder
    Do While lRet& = SMS_OK
        'Get subfolders
        Resp% = GetMachineProperties%(db, hSubFolder&, ListIndex%, GroupID&)

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

    'If we're done with the item, collapse it
    If Resp% = IDOK Then
        If (olnData.ListIndex <= ListIndex% Or olnData.ListIndex = olnData.ListCount - 1) And olnData.HasSubItems(ListIndex%) Then
            'Preserve flag and allow Collapse to remove nodes
            bGetDataOld% = bGetData%
            bGetData% = False

            'Collapse the site now that its done
            olnData_Collapse ListIndex%

            'Restore flag
            bGetData% = bGetDataOld%
        End If
    End If

    'Set the return value (either IDABORT or IDOK)
    GetMachines% = Resp%
End Function

Private Function GetPropertyAttributes%(db As Database, ByVal hFolder&, ParentListIndex%, GroupID&, MachineID&, PropertyIndex%)
    Dim TypeName$, FolderType&
    Dim sScalar As SCALAR, PropertyID&, Property$, PropertyName$
    Dim ListIndex%, bGetDataOld%
    Dim Pos1%, Pos2%
    Dim lRet&, Resp%, Index%

    'Default return value IDOK (Entry added)
    GetPropertyAttributes% = IDOK

    'Location of next item to add to outline control
    ListIndex% = olnData.ListCount

    'Get this folder's type (expect Group)
    lRet& = SmsGetFolderType&(hFolder&, FolderType&, TypeName$)
    If lRet& <> SMS_OK Then
        GetPropertyAttributes% = MsgBox("SMS Error:" + Chr$(10) + Chr$(10) + SMSError$(lRet&), MB_ICONEXCLAMATION + MB_ABORTRETRYIGNORE, Caption)
        Exit Function
    End If

    Select Case TypeName$
        Case "Group"
            lRet& = SmsGetFolderID&(hFolder&, Property$)
            If lRet& <> SMS_OK Then
                GetPropertyAttributes% = MsgBox("SMS Error:" + Chr$(10) + Chr$(10) + SMSError$(lRet&), MB_ICONEXCLAMATION + MB_ABORTRETRYIGNORE, Caption)
                Exit Function
            End If

            'Property Name not available. Use part of Property ID string.
            Pos1% = InStr(Property$, "|")
            Pos2% = InStr(Pos1% + 1, Property$, "|")
            If Pos2% <= 0 Then Pos2% = Len(Property$)
            PropertyName$ = LCase$(Mid$(Property$, Pos1% + 1, Pos2% - Pos1% - 1))

        Case Else
            Exit Function
    End Select

    DoEvents

    'Check to see if the user wants to cancel
    If bGetData% Then
        'Add item to database
        PropertyID& = AddProperty&(db, Property$, PropertyName$)
        If PropertyID& > 0 Then
            SetStatBarMsg olnData.List(ParentListIndex%) + " " + PropertyName$
            Resp% = IDOK
        Else: Resp% = MsgBox("Database Error:" + Chr$(10) + Chr$(10) + Error$, MB_ICONEXCLAMATION + MB_ABORTRETRYIGNORE, Caption)
        End If
    Else: Resp% = IDABORT
    End If

    'Make sure everything is OK and get first subfolder
    If Resp% = IDOK Then
        lRet& = SmsGetNextScalar&(hFolder&, sScalar)
    Else: lRet& = SMS_NO_MORE_DATA
    End If

    'List the attributes in this property folder
    Do While lRet& = SMS_OK
        'Get Scalar
        Resp% = GetAttributeValue%(db, sScalar, GroupID&, MachineID&, PropertyID&, PropertyIndex%)

        'See if user canceled
        If Not bGetData% Then Resp% = IDABORT

        'Check the user response
        Select Case Resp%
            Case IDOK, IDIGNORE
                lRet& = SmsGetNextScalar&(hFolder&, sScalar)
                Resp% = IDOK
            Case IDABORT
                lRet& = SMS_NO_MORE_DATA
            Case IDRETRY
                lRet& = SMS_OK
        End Select
    Loop
    If lRet& <> SMS_NO_MORE_DATA Then
        MsgBox "SMS Error:" + Chr$(10) + Chr$(10) + SMSError$(lRet&), MB_ICONEXCLAMATION + MB_OK, Caption
    End If

    'Set the return value (either IDABORT or IDOK)
    GetPropertyAttributes% = Resp%
End Function

Private Function GetSaveAsFileSpec$(ByVal InitFileSpec$, Filter$)
    'Default return value empty (User canceled)
    GetSaveAsFileSpec$ = ""

    CommonDialog.CancelError = True
    CommonDialog.filename = InitFileSpec$
    CommonDialog.Filter = Filter$
    CommonDialog.FilterIndex = 1
    CommonDialog.Flags = OFN_OVERWRITEPROMPT Or OFN_PATHMUSTEXIST Or OFN_HIDEREADONLY
    On Error Resume Next
    CommonDialog.Action = DLG_FILE_SAVE
    If Err = CDERR_CANCEL Then Exit Function
    If Err > 0 Then
        MsgBox "An unexpected error occured:" + Chr$(10) + Error$, MB_OK Or MB_ICONEXCLAMATION, Caption
        Exit Function
    End If
    On Error GoTo 0

    GetSaveAsFileSpec$ = CommonDialog.filename
End Function

Private Sub lblFileSpec_Change()
    UpdateCaption
End Sub

Private Sub olnData_Click()
    '
End Sub

Private Sub olnData_Collapse(ListIndex As Integer)
    If Not bGetData% And Not bReadData% Then
        Do While olnData.HasSubItems(ListIndex%)
            olnData_Collapse ListIndex% + 1
            olnData.RemoveItem ListIndex% + 1
        Loop
    End If
End Sub

Private Sub olnData_DblClick()
    If olnData.HasSubItems(olnData.ListIndex) Then
        olnData_Collapse CInt(olnData.ListIndex)
    Else: olnData_Expand CInt(olnData.ListIndex)
    End If
End Sub

Private Sub olnData_Expand(ListIndex As Integer)
    Dim Attrib As AttributeRec
    Static bExpanded%

    'Prevent infinite recursion
    If bExpanded% Then Exit Sub

    If Not bReadData% Then
        If Not olnData.HasSubItems(ListIndex) Then
            bReadData% = True
            ReadMachineData ListIndex
            bReadData% = False
        End If

        'Expand the node to show children
        If olnData.HasSubItems(ListIndex) Then
            bExpanded% = True
            olnData.Expand(ListIndex) = True
            bExpanded% = False
        End If
    End If
End Sub

Private Sub olnData_PictureClick(ListIndex As Integer)
    olnData.ListIndex = ListIndex
    olnData.Refresh
    olnData_Click
End Sub

Private Sub olnData_PictureDblClick(ListIndex As Integer)
    olnData_PictureClick ListIndex
    olnData_DblClick
End Sub

Private Sub PrintDoc(Destination%)
    CrystalReport.WindowTitle = Caption
    CrystalReport.Destination = Destination%
    CrystalReport.WindowParentHandle = 0
    CrystalReport.DataFiles(0) = ReportTempSpec$
    CrystalReport.ReportFileName = App.Path + "\MACHGRP.RPT"

    'Print the report
    CrystalReport.Action = 1
End Sub

Private Sub ReadMachineData(ParentListIndex%)
    Dim ListIndex%, TooMany%, DBError%
    Dim Attrib As AttributeRec, IDLookup As IDLookupRec
    Dim Windex%, OldStatBarMsg$, ErrStr$

    TooMany = False
    Select Case GetItemID%(Attrib, ParentListIndex%)
        Case 0 'Empty list: Get all machine groups
            If GetMachineGroup%(dbt, IDLookup) = False Then
                MsgBox "Error accessing database"
                Exit Sub
            End If

            ListIndex% = ParentListIndex% + 1
            If DBError% Then
                MsgBox "Error accessing database"
                Exit Sub
            ElseIf olnData.ListCount >= MAX_OUTLINE_ENTRIES Then
                TooMany% = True
            Else
                olnData.AddItem IDLookup.StrName$, ListIndex%
                olnData.Indent(ListIndex%) = 0
                olnData.PictureType(ListIndex%) = MSOUTLINE_PICTURE_GROUP
                olnData.ItemData(ListIndex%) = IDLookup.ID&
                ListIndex% = ListIndex% + 1
        
                'DoEvents 'Turned off because its too slow!
                            'Turn back on to check for user cancel
            End If
        Case 1 'Machine Group: Get machines in group
            If QueryMachines%(dbt, Attrib) = False Then
                MsgBox "Error accessing database"
                Exit Sub
            End If

            ListIndex% = ParentListIndex% + 1
            Do While FetchMachines%(IDLookup, Not bReadData% Or TooMany%, DBError%)
                If DBError% Then
                    MsgBox "Error accessing database"
                    Exit Sub
                ElseIf olnData.ListCount >= MAX_OUTLINE_ENTRIES Then
                    TooMany% = True
                Else
                    olnData.AddItem IDLookup.StrName$, ListIndex%
                    olnData.Indent(ListIndex%) = 1
                    olnData.PictureType(ListIndex%) = MSOUTLINE_PICTURE_MACHINE
                    olnData.ItemData(ListIndex%) = IDLookup.ID&
                    ListIndex% = ListIndex% + 1
            
                    'DoEvents 'Turned off because its too slow!
                              'Turn back on to check for user cancel
                End If
            Loop
        Case 2 'Machine: Get properties of machine
            'Indicate in status bar what's going on
            OldStatBarMsg$ = GetStatBarMsg$()
            SetStatBarMsg "Opening Machine Properties..."

            'Create new document window
            Windex% = NewMachineReportWindow%(hConnect&, "", dbt, Attrib, ErrStr$)

            'If window created OK then initialize it
            If Windex% <= 0 Then
                MsgBox "Error opening machine properties " + CommonDialog.filename + ":" + Chr$(10) + Chr$(10) + ErrStr$, MB_OK Or MB_ICONEXCLAMATION, Screen.ActiveForm.Caption
            Else: ReportWindow(Windex%).cmdInitialize = True
            End If
        
            'Restore status bar message and menu caption
            SetStatBarMsg OldStatBarMsg$
            Windex% = 0
    End Select

    If TooMany% Then
        MsgBox "No more machines and properties can be displayed in this window until some are collapsed."
    End If
End Sub

Private Sub SaveDoc(ByVal FileSpec$)
    Dim ReportSaved%, Resp%

    'Temporarily close the database and temp database
    dbt.Close
    If Not db Is Nothing Then db.Close

    ReportSaved% = False
    Do
        On Error Resume Next
        FileCopy ReportTempSpec$, FileSpec$
        If Err > 0 Then
            Resp% = MsgBox("An error occured trying to save " + FileSpec$ + ":" + Chr$(10) + Error$ + Chr$(10) + Chr$(10) + "Do you want to try again?", MB_OKCANCEL Or MB_ICONQUESTION, Caption)
            If Resp% = IDCANCEL Then Exit Do
        Else: ReportSaved% = True
        End If
    Loop Until ReportSaved%

    'Re-open the database and temp database
    Set dbt = OpenDatabase(ReportTempSpec$, True)
    Set db = OpenDatabase(FileSpec$, True, True)

    If ReportSaved% Then
        lblFileSpec = FileSpec$
        chkDirty = False
    End If
End Sub

Private Sub UpdateCaption()
    Dim NewCaption$

    If lblFileSpec > "" Then
        NewCaption$ = lblFileSpec
    Else: NewCaption$ = "New Machine Group Report " + CStr(NewNumber)
    End If

    If chkDirty Then NewCaption$ = NewCaption$ + "*"

    Caption = NewCaption$
End Sub

