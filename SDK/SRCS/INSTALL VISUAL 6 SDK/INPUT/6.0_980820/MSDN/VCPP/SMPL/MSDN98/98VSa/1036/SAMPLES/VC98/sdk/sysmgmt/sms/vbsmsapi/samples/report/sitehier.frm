VERSION 4.00
Begin VB.Form frmSiteHierarchyReport 
   Appearance      =   0  'Flat
   BackColor       =   &H80000005&
   Caption         =   "Site Hierarchy Report"
   ClientHeight    =   4350
   ClientLeft      =   1860
   ClientTop       =   2580
   ClientWidth     =   4530
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
   Height          =   4755
   Icon            =   "SITEHIER.frx":0000
   Left            =   1800
   LinkTopic       =   "Form1"
   MDIChild        =   -1  'True
   ScaleHeight     =   4350
   ScaleWidth      =   4530
   Top             =   2235
   Width           =   4650
   Begin VB.CommandButton cmdSave 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Save"
      Height          =   315
      Left            =   420
      TabIndex        =   4
      TabStop         =   0   'False
      Top             =   2100
      Visible         =   0   'False
      Width           =   3735
   End
   Begin VB.CommandButton cmdSaveAs 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Save As"
      Height          =   315
      Left            =   420
      TabIndex        =   3
      TabStop         =   0   'False
      Top             =   2400
      Visible         =   0   'False
      Width           =   3735
   End
   Begin VB.CheckBox chkDirty 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Dirty Bit"
      ForeColor       =   &H80000008&
      Height          =   195
      Left            =   420
      TabIndex        =   2
      TabStop         =   0   'False
      Top             =   1860
      Visible         =   0   'False
      Width           =   1155
   End
   Begin VB.CommandButton cmdPrintPreview 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Print Preview"
      Height          =   315
      Left            =   420
      TabIndex        =   1
      TabStop         =   0   'False
      Top             =   3000
      Visible         =   0   'False
      Width           =   3735
   End
   Begin VB.CommandButton cmdPrint 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Print"
      Height          =   315
      Left            =   420
      TabIndex        =   0
      TabStop         =   0   'False
      Top             =   2700
      Visible         =   0   'False
      Width           =   3735
   End
   Begin VB.CommandButton cmdAbort 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Abort"
      Height          =   315
      Left            =   420
      TabIndex        =   7
      TabStop         =   0   'False
      Top             =   3900
      Visible         =   0   'False
      Width           =   3735
   End
   Begin VB.CommandButton cmdInitialize 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Initialize"
      Height          =   315
      Left            =   420
      TabIndex        =   8
      TabStop         =   0   'False
      Top             =   3600
      Visible         =   0   'False
      Width           =   3735
   End
   Begin VB.CommandButton cmdExport 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Export"
      Height          =   315
      Left            =   420
      TabIndex        =   9
      TabStop         =   0   'False
      Top             =   3300
      Visible         =   0   'False
      Width           =   3735
   End
   Begin MSComDlg.CommonDialog CommonDialog 
      Left            =   2400
      Top             =   360
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
   End
   Begin Crystal.CrystalReport CrystalReport 
      Left            =   2880
      Top             =   360
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
   Begin MSOutl.Outline olnData 
      Height          =   750
      Left            =   420
      TabIndex        =   6
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
      Left            =   1740
      TabIndex        =   5
      Top             =   1860
      Visible         =   0   'False
      Width           =   2175
   End
End
Attribute VB_Name = "frmSiteHierarchyReport"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

'//****************************************************************************
'//
'//  Copyright (c) 1995, Microsoft Corporation
'//
'//  File:  SITEHIER.FRM
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

'Some relavent names for the outline control pictures
Const MSOUTLINE_PICTURE_ROOT = SITEHIERTYPE_ROOT
Const MSOUTLINE_PICTURE_SITE = SITEHIERTYPE_SITE
Const MSOUTLINE_PICTURE_DOMAIN = SITEHIERTYPE_DOMAIN

'State flags
Dim bGetData%  'If True, getting site data from SMS.
Dim bReadData% 'If True, reading site data from file.

Private Sub chkDirty_Click()
    UpdateCaption
End Sub

Private Sub cmdAbort_Click()
    'Handle user abort of current lengthy operation
    If bGetData% Then
        If MsgBox("Do you want to stop gathering site data?" + Chr$(10) + Chr$(10) + "Click Yes to abort, No to continue.", MB_YESNO + MB_ICONQUESTION, Caption) = IDYES Then
            bGetData% = False
        End If
    ElseIf bReadData% Then
        If MsgBox("Do you want to stop reading site data?" + Chr$(10) + Chr$(10) + "Click Yes to abort, No to continue.", MB_YESNO + MB_ICONQUESTION, Caption) = IDYES Then
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
        ReadSiteData "", -1
        bReadData% = False
    Else
        'Flag that we are in gathering data mode
        bGetData% = True
        GetSiteData
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

        'Handle user settings
        CrystalReport.CopiesToPrinter = CommonDialog.Copies
    Else
        'Supply default settings
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
    'Position outline control (will be resized in Form Resize)
    olnData.left = 0
    olnData.top = 0

    chkDirty = False

    NewNumber% = InitReportNewNumber%
    hConnect& = InitReporthConnect&
    lblFileSpec = InitReportFileSpec$
    ReportTempSpec$ = InitReportTempSpec$

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

Private Sub GetSiteData()
    Dim hContainer&, hSubFolder&, ItemNum&, RootSite As SiteRec
    Dim sScalar As SCALAR
    Dim lRet&, Resp%

    'Reset item number
    ItemNum& = 0

    lRet& = SmsOpenContainer&(C_SITE, hConnect&, hContainer&)
    If lRet& <> SMS_OK Then
        MsgBox "SMS Error:" + Chr$(10) + Chr$(10) + SMSError$(lRet&), MB_ICONEXCLAMATION + MB_OK, Caption
        Exit Sub
    End If

    lRet& = SmsPopulate&(hContainer&, POP_SYNC, ByVal 0&)
    If lRet& <> SMS_OK And lRet& <> SMS_EMPTY Then
        MsgBox "SMS Error:" + Chr$(10) + Chr$(10) + SMSError$(lRet&), MB_ICONEXCLAMATION + MB_OK, Caption
        GoTo GetSiteDataCleanup
    End If

    'List the root sites in this container
    Resp% = IDOK
    lRet& = SmsGetNextFolder&(hContainer&, F_ANY, hSubFolder&)
    Do While lRet& = SMS_OK
        'Get this site's depth
        lRet& = SmsGetScalarByName&(hSubFolder&, "Depth", sScalar)
        If lRet& <> SMS_OK Then
            Resp% = MsgBox("SMS Error:" + Chr$(10) + Chr$(10) + SMSError$(lRet&), MB_ICONEXCLAMATION + MB_ABORTRETRYIGNORE, Caption)
        Else
            'Only recurse from top level Site (Depth = 0)
            If sScalar.dwValue& <> 0 Then
                Resp% = IDOK
            Else
                'Get subfolders recursively
                Resp% = GetSiteDataRecursive%(dbt, hSubFolder&, CInt(olnData.ListCount), RootSite, ItemNum&)

                'See if the user canceled
                If Not bGetData% Then Resp% = IDABORT
            End If
        End If

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

GetSiteDataCleanup:
    lRet& = SmsCloseContainer&(hContainer&)
    chkDirty = CHECKED
End Sub

Private Function GetSiteDataRecursive%(db As Database, ByVal hFolder&, ParentListIndex%, ParentSite As SiteRec, ItemNum&)
    Dim hSubFolder&, FolderType&
    Dim sScalar As SCALAR
    Dim Site As SiteRec
    Dim ListIndex%, bGetDataOld%
    Dim lRet&, Resp%

    'Default return value IDOK (Entry added)
    GetSiteDataRecursive% = IDOK

    'Location of next item to add to outline control
    ListIndex% = olnData.ListCount

    'Get this folder's type (site or domain)
    lRet& = SmsGetFolderType&(hFolder&, FolderType&, Site.TypeName$)
    If lRet& <> SMS_OK Then
        GetSiteDataRecursive% = MsgBox("SMS Error:" + Chr$(10) + Chr$(10) + SMSError$(lRet&), MB_ICONEXCLAMATION + MB_ABORTRETRYIGNORE, Caption)
        Exit Function
    End If

    Select Case Site.TypeName$
        Case "Domain"
            lRet& = SmsGetScalarByName&(hFolder&, "Site code", sScalar)
            If lRet& <> SMS_OK Then
                GetSiteDataRecursive% = MsgBox("SMS Error:" + Chr$(10) + Chr$(10) + SMSError$(lRet&), MB_ICONEXCLAMATION + MB_ABORTRETRYIGNORE, Caption)
                Exit Function
            End If
            Site.Parent$ = sScalar.pszValue
            
            lRet& = SmsGetFolderID&(hFolder&, Site.Name$)
            If lRet& <> SMS_OK Then
                GetSiteDataRecursive% = MsgBox("SMS Error:" + Chr$(10) + Chr$(10) + SMSError$(lRet&), MB_ICONEXCLAMATION + MB_ABORTRETRYIGNORE, Caption)
                Exit Function
            End If
            Site.Name$ = Site.Name$

            Site.Code$ = ""
            Site.Type% = SITEHIERTYPE_DOMAIN
            Site.Depth% = ParentSite.Depth% + 1

            ParentSite.ItemNum& = ParentSite.ItemNum& + 1
            Site.ItemNum& = ParentSite.ItemNum&

        Case "Site"
            lRet& = SmsGetFolderID&(hFolder&, Site.Code$)
            If lRet& <> SMS_OK Then
                GetSiteDataRecursive% = MsgBox("SMS Error:" + Chr$(10) + Chr$(10) + SMSError$(lRet&), MB_ICONEXCLAMATION + MB_ABORTRETRYIGNORE, Caption)
                Exit Function
            End If

            lRet& = SmsGetScalarByName&(hFolder&, "Parent site", sScalar)
            If lRet& <> SMS_OK Then
                GetSiteDataRecursive% = MsgBox("SMS Error:" + Chr$(10) + Chr$(10) + SMSError$(lRet&), MB_ICONEXCLAMATION + MB_ABORTRETRYIGNORE, Caption)
                Exit Function
            End If
            Site.Parent$ = sScalar.pszValue

            lRet& = SmsGetScalarByName&(hFolder&, "Depth", sScalar)
            If lRet& <> SMS_OK Then
                GetSiteDataRecursive% = MsgBox("SMS Error:" + Chr$(10) + Chr$(10) + SMSError$(lRet&), MB_ICONEXCLAMATION + MB_ABORTRETRYIGNORE, Caption)
                Exit Function
            End If
            Site.Depth = sScalar.dwValue&

            lRet& = SmsGetScalarByName&(hFolder&, "Site name", sScalar)
            If lRet& <> SMS_OK Then
                GetSiteDataRecursive% = MsgBox("SMS Error:" + Chr$(10) + Chr$(10) + SMSError$(lRet&), MB_ICONEXCLAMATION + MB_ABORTRETRYIGNORE, Caption)
                Exit Function
            End If
            Site.Name$ = sScalar.pszValue

            lRet& = SmsGetScalarByName&(hFolder&, "Site type", sScalar)
            If lRet& <> SMS_OK Then
                GetSiteDataRecursive% = MsgBox("SMS Error:" + Chr$(10) + Chr$(10) + SMSError$(lRet&), MB_ICONEXCLAMATION + MB_ABORTRETRYIGNORE, Caption)
                Exit Function
            End If
            Site.TypeName$ = sScalar.pszValue + " " + Site.TypeName$

            If Site.Parent$ > "" Then
                Site.Type% = SITEHIERTYPE_SITE
            Else: Site.Type% = SITEHIERTYPE_ROOT
            End If

            Site.ItemNum& = ItemNum&
            ItemNum& = ItemNum& + &H10000

        Case Else
            Exit Function
    End Select

    DoEvents

    'Check to see if the user wants to cancel
    If bGetData% Then
        'Add item to database
        If InsertSite&(db, Site) = 1 Then
            'Add item to outline control
            olnData.AddItem Site.Name$, ListIndex%
            olnData.Indent(ListIndex%) = Site.Depth%
            olnData.PictureType(ListIndex%) = Site.Type%
            olnData.ItemData(ListIndex%) = Site.ItemNum&
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
    If Site.Type% <> SITEHIERTYPE_DOMAIN And Resp% = IDOK Then
        lRet& = SmsGetNextFolder&(hFolder&, F_ANY, hSubFolder&)
    Else: lRet& = SMS_NO_MORE_DATA
    End If

    'List the sub-folders in this folder
    Do While lRet& = SMS_OK
        'Get subfolders recursively
        Resp% = GetSiteDataRecursive%(db, hSubFolder&, ListIndex%, Site, ItemNum&)

        'See if user canceled
        If Not bGetData% Then Resp% = IDABORT

        'Check the user response
        Select Case Resp%
            Case IDOK, IDIGNORE
                lRet& = SmsCloseFolder&(hSubFolder&)
                lRet& = SmsGetNextFolder&(hFolder&, F_ANY, hSubFolder&)
                Resp% = IDOK
            Case IDABORT
                lRet& = SmsCloseFolder&(hFolder&)
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
    GetSiteDataRecursive% = Resp%
End Function

Private Sub lblFileSpec_Change()
    UpdateCaption
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
    Dim Site As SiteRec
    Static bExpanded%

    'Prevent infinite recursion
    If bExpanded% Then Exit Sub

    If Not bReadData% Then
        If Not olnData.HasSubItems(ListIndex) Then
            'Find the info on the node to expand
            Site.ItemNum& = olnData.ItemData(ListIndex)
            If FindSite(dbt, Site) <> 1 Then
                MsgBox "Unexpected error trying to expand site:" + Chr$(10) + Chr$(10) + Error$, MB_OK + MB_ICONEXCLAMATION, Caption
                Exit Sub
            Else: If Site.Type = SITEHIERTYPE_DOMAIN Then Exit Sub
            End If
    
            'Read the sites children from the data file
            bReadData% = True
            ReadSiteData Site.Code$, ListIndex
            bReadData% = False
        End If

        'Expand the node to show children
        If olnData.HasSubItems(ListIndex) Then
            bExpanded% = True
            olnData.Expand(ListIndex%) = True
            bExpanded% = False
        End If
    End If
End Sub

Private Sub olnData_PictureClick(ListIndex As Integer)
    olnData.ListIndex = ListIndex
End Sub

Private Sub olnData_PictureDblClick(ListIndex As Integer)
    olnData.ListIndex = ListIndex
    olnData_DblClick
End Sub

Private Sub PrintDoc(Destination%)
    CrystalReport.WindowTitle = Caption
    CrystalReport.Destination = Destination%
    CrystalReport.WindowParentHandle = 0
    CrystalReport.DataFiles(0) = ReportTempSpec$
    CrystalReport.ReportFileName = App.Path + "\SITEHIER.RPT"

    'Print the report
    CrystalReport.Action = 1
End Sub

Private Sub ReadSiteData(Parent$, ParentListIndex%)
    Dim ListIndex%, TooMany%, DBError%
    Dim Site As SiteRec

    'Select all children of Parent$ sites
    Site.Parent$ = Parent$
    Site.Code$ = ""
    If QuerySite%(dbt, Site) = False Then
        MsgBox "Error accessing database"
        Exit Sub
    End If

    TooMany% = False
    ListIndex% = ParentListIndex% + 1
    Do While FetchSite%(Site, Not bReadData% Or TooMany%, DBError%)
        If DBError% Then
            MsgBox "Error accessing database"
            Exit Sub
        ElseIf olnData.ListCount >= MAX_OUTLINE_ENTRIES Then
            TooMany% = True
        Else
            olnData.AddItem Site.Name$, ListIndex%
            olnData.Indent(ListIndex%) = Site.Depth%
            olnData.PictureType(ListIndex%) = Site.Type%
            olnData.ItemData(ListIndex%) = Site.ItemNum&
            ListIndex% = ListIndex% + 1

            'DoEvents 'Turned off because its too slow!
                      'Turn back on to check for user cancel
        End If
    Loop

    If TooMany% Then
        MsgBox "No more sites and domains can be displayed in this window until some are collapsed."
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
            If Resp% = IDCANCEL Then Exit Sub
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
    Else: NewCaption$ = "New Site Hierarchy Report " + CStr(NewNumber)
    End If

    If chkDirty Then NewCaption$ = NewCaption$ + "*"

    Caption = NewCaption$
End Sub

