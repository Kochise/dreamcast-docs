VERSION 4.00
Begin VB.MDIForm frmMDIReport 
   Appearance      =   0  'Flat
   BackColor       =   &H8000000C&
   Caption         =   "SMS Report"
   ClientHeight    =   5445
   ClientLeft      =   1350
   ClientTop       =   1935
   ClientWidth     =   8520
   Height          =   6135
   Icon            =   "MDIREPRT.frx":0000
   Left            =   1290
   LinkTopic       =   "Form1"
   Top             =   1305
   Width           =   8640
   Begin Threed.SSPanel pnlStatusBar 
      Align           =   2  'Align Bottom
      Height          =   405
      Left            =   0
      TabIndex        =   0
      Top             =   5040
      Width           =   8520
      _Version        =   65536
      _ExtentX        =   15028
      _ExtentY        =   714
      _StockProps     =   15
      BackColor       =   -2147483633
      BevelInner      =   1
      Alignment       =   1
      Autosize        =   3
      Begin VB.Label lblStatusBar 
         Appearance      =   0  'Flat
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
         Height          =   225
         Left            =   75
         TabIndex        =   1
         Top             =   75
         Width           =   8370
      End
   End
   Begin ComctlLib.ImageList imgToolBar 
      Left            =   2040
      Top             =   -120
      _Version        =   65536
      _ExtentX        =   1005
      _ExtentY        =   1005
      _StockProps     =   1
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   8421376
      NumImages       =   5
      i1              =   "MDIREPRT.frx":030A
      i2              =   "MDIREPRT.frx":04C1
      i3              =   "MDIREPRT.frx":0678
      i4              =   "MDIREPRT.frx":082F
      i5              =   "MDIREPRT.frx":09E6
   End
   Begin ComctlLib.Toolbar tlbToolbar 
      Align           =   1  'Align Top
      Height          =   405
      Left            =   0
      TabIndex        =   2
      Top             =   0
      Width           =   8520
      _Version        =   65536
      _ExtentX        =   15028
      _ExtentY        =   714
      _StockProps     =   96
      BorderStyle     =   1
      ImageList       =   "imgToolBar"
      MouseIcon       =   "MDIREPRT.frx":0B9D
      ButtonWidth     =   609
      AllowCustomize  =   0   'False
      NumButtons      =   5
      i1              =   "MDIREPRT.frx":0BB9
      i2              =   "MDIREPRT.frx":0D60
      i3              =   "MDIREPRT.frx":0F07
      i4              =   "MDIREPRT.frx":10AE
      i5              =   "MDIREPRT.frx":1259
      AlignSet        =   -1  'True
   End
   Begin MSComDlg.CommonDialog CommonDialog 
      Left            =   1320
      Top             =   2280
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&File"
      Begin VB.Menu mnuFileNew 
         Caption         =   "&New..."
         Shortcut        =   ^N
      End
      Begin VB.Menu mnuFileOpen 
         Caption         =   "&Open..."
         Shortcut        =   ^O
      End
      Begin VB.Menu mnuFileSave 
         Caption         =   "&Save..."
         Shortcut        =   ^S
      End
      Begin VB.Menu mnuFileSaveAs 
         Caption         =   "Save &As..."
         Shortcut        =   {F12}
      End
      Begin VB.Menu mnuFileSeperator0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFilePrintPreview 
         Caption         =   "Print Pre&view"
      End
      Begin VB.Menu mnuFilePrint 
         Caption         =   "&Print..."
         Shortcut        =   ^P
      End
      Begin VB.Menu mnuFileExport 
         Caption         =   "&Export..."
      End
      Begin VB.Menu mnuFileSeperator1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileExit 
         Caption         =   "E&xit"
      End
   End
   Begin VB.Menu mnuWindow 
      Caption         =   "&Window"
      WindowList      =   -1  'True
      Begin VB.Menu mnuWindowCascade 
         Caption         =   "&Cascade"
         Shortcut        =   {F5}
      End
      Begin VB.Menu mnuWindowArrangeIcons 
         Caption         =   "&Arrange Icons"
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "&Help"
      Begin VB.Menu mnuHelpAbout 
         Caption         =   "&About SMS Report..."
      End
   End
End
Attribute VB_Name = "frmMDIReport"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

'//****************************************************************************
'//
'//  Copyright (c) 1995, Microsoft Corporation
'//
'//  File:  MDIREPRT.FRM
'//
'//  History:
'//
'//      Gary Fuehrer, SEA   5/9/95      Created.
'//
'//****************************************************************************

Dim hConnect&
Dim FileNewMenuCaption$
Dim FileNewToolTip$
Private Function GetReportType%(ByVal FileSpec$)
    Dim db As Database, i%

    'Default return value UNKNOWN_REPORT (Failed)
    GetReportType% = UNKNOWN_REPORT
    
    'Open the database file
    On Error Resume Next
    Set db = OpenDatabase(FileSpec$, True, True)
    If Err > 0 Then Exit Function
    On Error GoTo 0

    For i% = 0 To db.TableDefs.Count - 1
        Select Case db.TableDefs(i%).Name
            Case "Site Hierarchy"
                GetReportType% = SITE_HIERARCHY_REPORT
            Case "Generic"
                GetReportType% = GENERIC_REPORT
            Case "MachineGroupID"
                GetReportType% = MACHINE_GROUP_REPORT
            Case "MachineID"
                GetReportType% = MACHINE_REPORT
            'Case "GenericTableName"
            '    GetReportType% = GENERIC_REPORT
        End Select
    Next i%

    db.Close
End Function

Private Sub MDIForm_Load()
    'Get the size of one pixel size in twips
    GetPixelSizeInTwips Me, X_PIX_SIZE, Y_PIX_SIZE

    'Initially, File New menu is a way to login to SMS
    FileNewMenuCaption$ = mnuFileNew.Caption
    FileNewToolTip$ = tlbToolbar.Buttons(1).ToolTipText
    mnuFileNew.Caption = "&Login to SMS..."
    tlbToolbar.Buttons(1).ToolTipText = "Login to SMS"

    'Login to SMS
    hConnect& = 0
    mnuFileNew_Click

    'Initialize the status bar
    SetCurrentStatusBar lblStatusBar
    SetStatBarMsg ""
End Sub

Private Sub MDIForm_Resize()
    lblStatusBar.Width = pnlStatusBar.Width - lblStatusBar.left * 2
End Sub


Private Sub MDIForm_Unload(Cancel As Integer)
    DBLogout hConnect&
End Sub

Private Sub mnuFileExit_Click()
    Unload Me
End Sub

Private Sub mnuFileExport_Click()
    Dim OldStatBarMsg$
    
    If Not ActiveForm Is Nothing Then
        'Turn on wait cursor and set status bar
        MousePointer = HOURGLASS
        OldStatBarMsg$ = GetStatBarMsg$()
        SetStatBarMsg "Exporting Report..."

        'Call Print Preview method of active document
        ActiveForm.cmdExport = True

        'Restore status bar message and mouse pointer
        SetStatBarMsg OldStatBarMsg$
        MousePointer = NORMAL
    End If
End Sub

Private Sub mnuFileNew_Click()
    Dim SqlConnectParams As SQL_CONNECT_PARAMS
    Dim ErrStr$, OldMenuCaption$, OldStatBarMsg$
    Dim ReportType%
    Static Windex%

    'Check for reentrancy
    If Windex% > 0 Then
        ReportWindow(Windex%).cmdAbort = True
        Exit Sub
    End If

    'Check for user needing to log in first
    If hConnect& = 0 Then
        'Indicate in status bar what's going on
        OldStatBarMsg$ = GetStatBarMsg$()
        SetStatBarMsg "Login to SMS..."

        'Let user try to log in to SMS
        If DBLogin%(SqlConnectParams, hConnect&) Then
            mnuFileNew.Caption = FileNewMenuCaption$
            tlbToolbar.Buttons(1).ToolTipText = FileNewToolTip$
        End If

        'Restore status bar message and quit
        SetStatBarMsg OldStatBarMsg$
        Exit Sub
    End If

    'Get from user what kind of report to create
    If Not NewReport%(ReportType%) Then Exit Sub

    'Provide a mechanism for user to cancel
    OldMenuCaption$ = mnuFileNew.Caption
    mnuFileNew.Caption = "&Abort New Report..."

    'Indicate in status bar what's going on
    OldStatBarMsg$ = GetStatBarMsg$()
    SetStatBarMsg "Creating Report..."

    'Create new document window of selected type
    Select Case ReportType%
        Case SITE_HIERARCHY_REPORT
            Windex% = NewSiteHierarchyReportWindow%(hConnect&, "", ErrStr$)
        Case MACHINE_GROUP_REPORT
            Windex% = NewMachineGrpReportWindow%(hConnect&, "", ErrStr$)
        Case GENERIC_REPORT
            Windex% = NewGenericReportWindow%(hConnect&, "", ErrStr$)
    End Select

    'If window created OK then initialize it
    If Windex% <= 0 Then
        'If zero, report error, else user canceled
        If Windex% = 0 Then
            MsgBox "Error creating a new report:" + Chr$(10) + Chr$(10) + ErrStr$, MB_OK Or MB_ICONEXCLAMATION, Screen.ActiveForm.Caption
        End If
    Else: ReportWindow(Windex%).cmdInitialize = True
    End If

    'Restore status bar message and menu caption
    SetStatBarMsg OldStatBarMsg$
    mnuFileNew.Caption = OldMenuCaption$
    Windex% = 0
End Sub

Private Sub mnuFileOpen_Click()
    Dim ErrStr$, OldMenuCaption$, OldStatBarMsg$
    Dim dbSrce As Database, Attrib As AttributeRec 'Dummy arguements
    Dim ReportType%
    Static Windex%
    
    'Check for reentrancy
    If Windex% > 0 Then
        ReportWindow(Windex%).cmdAbort = True
        Exit Sub
    End If

    CommonDialog.CancelError = True
    CommonDialog.filename = ""
    'Supply file types for all possible reports HERE
    CommonDialog.Filter = "Microsoft Access Database (*.mdb)|*.mdb|All Files (*.*)|*.*"
    CommonDialog.FilterIndex = 1
    CommonDialog.Flags = OFN_PATHMUSTEXIST Or OFN_FILEMUSTEXIST Or OFN_HIDEREADONLY
    On Error Resume Next
    CommonDialog.Action = DLG_FILE_OPEN
    If Err = CDERR_CANCEL Then Exit Sub
    If Err > 0 Then
        MsgBox "An unexpected error occured:" + Chr$(10) + Chr$(10) + Error$, MB_OK Or MB_ICONEXCLAMATION, Caption
        Exit Sub
    End If
    On Error GoTo 0

    ReportType% = GetReportType%(CommonDialog.filename)
    If ReportType% <= UNKNOWN_REPORT Then
        MsgBox "The file " + CommonDialog.filename + " is not an SMS report file.", MB_OK, Caption
        Exit Sub
    End If

    'Provide a mechanism for user to cancel
    OldMenuCaption$ = mnuFileNew.Caption
    mnuFileNew.Caption = "&Abort Open Report..."

    'Indicate in status bar what's going on
    OldStatBarMsg$ = GetStatBarMsg$()
    SetStatBarMsg "Opening Report..."

    'Create new document window of selected type
    Select Case ReportType%
        Case SITE_HIERARCHY_REPORT
            Windex% = NewSiteHierarchyReportWindow%(hConnect&, CommonDialog.filename, ErrStr$)
        Case MACHINE_GROUP_REPORT
            Windex% = NewMachineGrpReportWindow%(hConnect&, CommonDialog.filename, ErrStr$)
        Case MACHINE_REPORT
            Windex% = NewMachineReportWindow%(hConnect&, CommonDialog.filename, dbSrce, Attrib, ErrStr$)
        Case GENERIC_REPORT
            Windex% = NewGenericReportWindow%(hConnect&, CommonDialog.filename, ErrStr$)
    End Select

    'If window created OK then initialize it
    If Windex% <= 0 Then
        MsgBox "Error opening report " + CommonDialog.filename + ":" + Chr$(10) + Chr$(10) + ErrStr$, MB_OK Or MB_ICONEXCLAMATION, Screen.ActiveForm.Caption
    Else: ReportWindow(Windex%).cmdInitialize = True
    End If

    'Restore status bar message and menu caption
    SetStatBarMsg OldStatBarMsg$
    mnuFileNew.Caption = OldMenuCaption$
    Windex% = 0
End Sub

Private Sub mnuFilePrint_Click()
    Dim OldStatBarMsg$
    
    If Not ActiveForm Is Nothing Then
        'Turn on wait cursor and set status bar
        MousePointer = HOURGLASS
        OldStatBarMsg$ = GetStatBarMsg$()
        SetStatBarMsg "Printing Report..."

        'Set flag for needing print dialog
        gbNeedPrintDialog% = True

        'Call Print method of active document
        ActiveForm.cmdPrint = True

        'Restore status bar message and mouse pointer
        SetStatBarMsg OldStatBarMsg$
        MousePointer = NORMAL
    End If
End Sub

Private Sub mnuFilePrintPreview_Click()
    Dim OldStatBarMsg$
    
    If Not ActiveForm Is Nothing Then
        'Turn on wait cursor and set status bar
        MousePointer = HOURGLASS
        OldStatBarMsg$ = GetStatBarMsg$()
        SetStatBarMsg "Previewing Report..."

        'Call Print Preview method of active document
        ActiveForm.cmdPrintPreview = True

        'Restore status bar message and mouse pointer
        SetStatBarMsg OldStatBarMsg$
        MousePointer = NORMAL
    End If
End Sub

Private Sub mnuFileSave_Click()
    Dim OldStatBarMsg$
    
    If Not ActiveForm Is Nothing Then
        MousePointer = HOURGLASS
        OldStatBarMsg$ = GetStatBarMsg$()
        SetStatBarMsg "Saving Report..."
        
        ActiveForm.cmdSave = True
        
        SetStatBarMsg OldStatBarMsg$
        MousePointer = NORMAL
    End If
End Sub

Private Sub mnuFileSaveAs_Click()
    Dim OldStatBarMsg$
    
    If Not ActiveForm Is Nothing Then
        MousePointer = HOURGLASS
        OldStatBarMsg$ = GetStatBarMsg$()
        SetStatBarMsg "Saving Report..."
        
        ActiveForm.cmdSaveAs = True
        
        SetStatBarMsg OldStatBarMsg$
        MousePointer = NORMAL
    End If
End Sub

Private Sub mnuHelpAbout_Click()
    Dim Info$

    Info$ = "SMS Report" + Chr$(10) + Chr$(10) + "A Microsoft SMS SDK sample application"
    Info$ = Info$ + Chr$(10) + "written in Microsoft Visual Basic 3.0 Professional Edition that"
    Info$ = Info$ + Chr$(10) + "demonstrates the Visual Basic Wrapper DLL for SMS API."

    SmsAbout "About SMS Report", Info$
End Sub

Private Sub mnuWindowArrangeIcons_Click()
    Arrange ARRANGE_ICONS
End Sub

Private Sub mnuWindowCascade_Click()
    Arrange CASCADE
End Sub


Private Sub tlbToolbar_ButtonClick(ByVal Button As Button)
    Select Case Button.Index
    Case 1
        mnuFileNew_Click
    Case 2
        mnuFileOpen_Click
    Case 3
        mnuFileSave_Click
    Case 4
        'Indicate to document that no Pring dialog is needed
        'This flag is reset by mnuFilePrint_Click()
        gbNeedPrintDialog% = False

        mnuFilePrint_Click
    Case 5
        mnuFilePrintPreview_Click
    End Select
End Sub

