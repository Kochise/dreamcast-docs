VERSION 4.00
Begin VB.Form frmMachineReport 
   Appearance      =   0  'Flat
   BackColor       =   &H80000005&
   Caption         =   "Machine Report"
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
   Icon            =   "MACHINE.frx":0000
   Left            =   1500
   LinkTopic       =   "Form1"
   MDIChild        =   -1  'True
   ScaleHeight     =   4215
   ScaleWidth      =   8505
   Top             =   2265
   Width           =   8625
   Begin VB.PictureBox picSeperator 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   2475
      Left            =   4200
      MousePointer    =   9  'Size W E
      ScaleHeight     =   2445
      ScaleWidth      =   45
      TabIndex        =   12
      Top             =   -15
      Width           =   75
   End
   Begin VB.PictureBox picRightView 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   2535
      Left            =   4275
      ScaleHeight     =   2535
      ScaleWidth      =   4200
      TabIndex        =   9
      Top             =   0
      Width           =   4200
      Begin Threed.SSPanel pnlTableHeader 
         Height          =   270
         Left            =   0
         TabIndex        =   11
         Top             =   0
         Width           =   1500
         _Version        =   65536
         _ExtentX        =   2646
         _ExtentY        =   476
         _StockProps     =   15
         Caption         =   "Table Header"
         BackColor       =   -2147483633
         BevelWidth      =   2
         BorderWidth     =   0
      End
      Begin MSGrid.Grid grdTable 
         Height          =   750
         Left            =   0
         TabIndex        =   10
         Top             =   240
         Width           =   1500
         _Version        =   65536
         _ExtentX        =   2646
         _ExtentY        =   1323
         _StockProps     =   77
         BorderStyle     =   0
         FixedCols       =   0
      End
   End
   Begin VB.PictureBox picLeftView 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   2535
      Left            =   0
      ScaleHeight     =   2535
      ScaleWidth      =   4215
      TabIndex        =   13
      Top             =   0
      Width           =   4215
      Begin Threed.SSPanel pnlPropertyHeader 
         Height          =   270
         Left            =   0
         TabIndex        =   15
         Top             =   0
         Width           =   1500
         _Version        =   65536
         _ExtentX        =   2646
         _ExtentY        =   476
         _StockProps     =   15
         Caption         =   "Properties"
         BackColor       =   -2147483633
         BevelWidth      =   2
         BorderWidth     =   0
      End
      Begin MSOutl.Outline olnData 
         Height          =   750
         Left            =   0
         TabIndex        =   14
         Top             =   240
         Width           =   1500
         _Version        =   65536
         _ExtentX        =   2646
         _ExtentY        =   1323
         _StockProps     =   77
         BorderStyle     =   0
         Style           =   5
      End
   End
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
      Left            =   0
      Top             =   3120
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
      Left            =   0
      Top             =   2640
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
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
Attribute VB_Name = "frmMachineReport"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

'//****************************************************************************
'//
'//  Copyright (c) 1995, Microsoft Corporation
'//
'//  File:  MACHINE.FRM
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

'Current machine name and ID
Dim Machine As IDLookupRec

'Currently selected item
Dim SelectedProperty%

'Some relavent names for the outline control pictures
Const MSOUTLINE_PICTURE_MACHINE = MSOUTLINE_PICTURE_CLOSED
Const MSOUTLINE_PICTURE_PROPERTY = MSOUTLINE_PICTURE_OPEN

'Seperator dragging state and cursor offset
Dim SeperatorDragging%
Dim SeperatorDragOffset%

'State flags
Dim bReadData% 'If True, reading property data from file.

Private Sub chkDirty_Click()
    UpdateCaption
End Sub

Private Sub cmdAbort_Click()
    'Handle user abort of current lengthy operation
    If bReadData% Then
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
    'Size the grid columns
    If picRightView.Width > grdTable.ColWidth(0) + X_PIX_SIZE Then
        grdTable.ColWidth(1) = picRightView.Width - grdTable.ColWidth(0) - X_PIX_SIZE
    End If

    If GetMachine%(dbt, Machine) Then
        'Add a root item to represent this machine
        olnData.AddItem Machine.StrName$, 0
        olnData.Indent(0) = 0
        olnData.PictureType(0) = MSOUTLINE_PICTURE_MACHINE
        olnData.ItemData(0) = Machine.ID&

        'Flag that we are in data reading mode
        bReadData% = True
        ReadMachineProperties 0
        bReadData% = False
    
        'Select the first property item
        If olnData.ListCount > 1 Then olnData.ListIndex = SelectedProperty%
        olnData_Click
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
    Dim i%, ImgTop%, TestTop%, NoMoreProperties%

    chkDirty = False

    NewNumber% = InitReportNewNumber%
    hConnect& = InitReporthConnect&
    lblFileSpec = InitReportFileSpec$
    ReportTempSpec$ = InitReportTempSpec$

    'Position Left View and controls (will be resized later)
    picLeftView.left = 0
    picLeftView.top = 0
        pnlPropertyHeader.left = 0
        pnlPropertyHeader.top = 0
        olnData.left = 0
        olnData.top = pnlPropertyHeader.Height
    picLeftView.Width = 3000

    'Position View Seperator (will be resized later)
    picSeperator.left = picLeftView.Width
    picSeperator.top = -Y_PIX_SIZE
    
    'Position Right View and controls (will be resized later)
    picRightView.left = picSeperator.left + picSeperator.Width
    picRightView.top = 0
        pnlTableHeader.left = 0
        pnlTableHeader.top = 0
        grdTable.left = 0
        grdTable.top = pnlTableHeader.Height
        grdTable.ColWidth(0) = 2500

    'Set column header captions
    grdTable.Col = 0
    grdTable.Row = 0
    grdTable.Text = "Attribute"
    grdTable.Col = 1
    grdTable.Row = 0
    grdTable.Text = "Value"

    Set dbt = OpenDatabase(ReportTempSpec$, True)
    If lblFileSpec > "" Then Set db = OpenDatabase(lblFileSpec, True, True)

    SelectedProperty% = 1
End Sub

Private Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)
    Dim Resp%, FileSpec$
    
    'Make sure we're not in the middle of something
    If bReadData% Then
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
    Static OldWidth, OldHeight, OldSepLeft%
    Dim r As Rect, HBorderPixels%, VBorderPixels%

    'See if we're minimized
    If WindowState = MINIMIZED Then Exit Sub

    'Get client size of form (already in pixels, I find)
    GetClientRect hwnd, r
    HBorderPixels% = Width / X_PIX_SIZE - r.right
    VBorderPixels% = Height / Y_PIX_SIZE - r.bottom
    
    If (OldWidth <> Width Or OldSepLeft <> picSeperator.left) And Width - X_PIX_SIZE * HBorderPixels% > picRightView.left Then
        picRightView.Width = Width - X_PIX_SIZE * HBorderPixels% - picRightView.left

        OldWidth = Width
    End If

    If OldHeight <> Height And Height - Y_PIX_SIZE * VBorderPixels% > picLeftView.top Then
        picLeftView.Height = Height - Y_PIX_SIZE * VBorderPixels% - picLeftView.top
        picRightView.Height = Height - Y_PIX_SIZE * VBorderPixels% - picRightView.top
        picSeperator.Height = Height - Y_PIX_SIZE * VBorderPixels% - picSeperator.top + Y_PIX_SIZE

        OldHeight = Height
        OldSepLeft = picSeperator.left
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

Private Function GetItemID%(Attrib As AttributeRec, ByVal ListIndex%)
    'Default return value 0 (nothing at list index)
    GetItemID% = 0
    If ListIndex% < 1 Or ListIndex% >= olnData.ListCount Then Exit Function

    Attrib.PropertyID = olnData.ItemData(ListIndex%)
    GetItemID% = 1
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
    SetSelectedProperty olnData.ListIndex
End Sub

Private Sub olnData_Expand(ListIndex As Integer)
    olnData.ListIndex = ListIndex
    olnData.Refresh
    olnData_Click
End Sub

Private Sub olnData_PictureClick(ListIndex As Integer)
    olnData.ListIndex = ListIndex
    olnData.Refresh
    olnData_Click
End Sub

Private Sub picLeftView_Resize()
    Static OldWidth, OldHeight

    If OldWidth <> picLeftView.Width Then
        pnlPropertyHeader.Width = picLeftView.Width
        olnData.Width = picLeftView.Width

        OldWidth = picLeftView.Width
    End If

    If OldHeight <> picLeftView.Height Then
        olnData.Height = picLeftView.Height - olnData.top

        OldHeight = picLeftView.Height
    End If
End Sub

Private Sub picRightView_Resize()
    Static OldWidth, OldHeight
        
    If OldWidth <> picRightView.Width Then
        pnlTableHeader.Width = picRightView.Width
        grdTable.Width = picRightView.Width

        OldWidth = picRightView.Width
    End If

    If OldHeight <> picRightView.Height And picRightView.Height > pnlTableHeader.Height Then
        grdTable.Height = picRightView.Height - grdTable.top

        OldWidth = picRightView.Width
    End If
End Sub

Private Sub picSeperator_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
    If Button And LEFT_BUTTON Then
        SeperatorDragging% = True
        SeperatorDragOffset% = X
    End If
End Sub

Private Sub picSeperator_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
    Dim OldLeft%

    If SeperatorDragging% And X <> OldLeft% And picSeperator.left + X - SeperatorDragOffset% > 0 Then
        picSeperator.left = picSeperator.left + X - SeperatorDragOffset%
        picLeftView.Width = picSeperator.left
        picRightView.left = picSeperator.left + picSeperator.Width
        Form_Resize
    End If
End Sub

Private Sub picSeperator_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
    If Button And LEFT_BUTTON Then
        SeperatorDragging% = False
    End If
End Sub

Private Sub PrintDoc(Destination%)
    CrystalReport.WindowTitle = Caption
    CrystalReport.Destination = Destination%
    CrystalReport.WindowParentHandle = 0
    CrystalReport.DataFiles(0) = ReportTempSpec$
    CrystalReport.ReportFileName = App.Path + "\MACHPROP.RPT"

    'Print the report
    CrystalReport.Action = 1
End Sub

Private Sub ReadMachineProperties(ParentListIndex%)
    Dim ListIndex%, TooMany%, DBError%, bFirstAttribute%, FirstAttributeID&
    Dim Attrib As AttributeRec, IDLookup As IDLookupRec

    Attrib.PropertyID = olnData.ItemData(ParentListIndex%)
    TooMany = False
    Select Case GetItemID%(Attrib, ParentListIndex%)
        Case 0 'Empty list: Get all machine properties
            If QueryProperties%(dbt, Attrib) = False Then
                MsgBox "Error accessing database"
                Exit Sub
            End If

            ListIndex% = ParentListIndex% + 1
            Do While FetchProperties%(IDLookup, Not bReadData% Or TooMany%, DBError%)
                If DBError% Then
                    MsgBox "Error accessing database"
                    Exit Sub
                ElseIf olnData.ListCount >= MAX_OUTLINE_ENTRIES Then
                    TooMany% = True
                Else
                    olnData.AddItem IDLookup.StrName$, ListIndex%
                    olnData.Indent(ListIndex%) = 1
                    olnData.PictureType(ListIndex%) = MSOUTLINE_PICTURE_PROPERTY
                    olnData.ItemData(ListIndex%) = IDLookup.ID&
                    ListIndex% = ListIndex% + 1

                    'DoEvents 'Turned off because its too slow!
                              'Turn back on to check for user cancel
                End If
            Loop
        Case 1 'Machine Property: Update table
            If QueryAttributes%(dbt, Attrib) = False Then
                MsgBox "Error accessing database"
                Exit Sub
            End If

            ListIndex% = 1
            bFirstAttribute% = True
            Do While FetchAttributes%(IDLookup, Not bReadData% Or TooMany%, DBError%)
                If DBError% Then
                    MsgBox "Error accessing database"
                    Exit Sub
                ElseIf olnData.ListCount >= MAX_OUTLINE_ENTRIES Then
                    TooMany% = True
                Else
                    If bFirstAttribute% Then
                        FirstAttributeID& = IDLookup.ID&
                        bFirstAttribute% = False
                    ElseIf IDLookup.ID& = FirstAttributeID& Then
                        'Add a blank entry to separate repeating section
                        grdTable.AddItem Chr$(9), ListIndex%
                        ListIndex% = ListIndex% + 1
                    End If

                    grdTable.AddItem IDLookup.StrID$ + Chr$(9) + IDLookup.StrName$, ListIndex%
                    ListIndex% = ListIndex% + 1

                    'DoEvents 'Turned off because its too slow!
                              'Turn back on to check for user cancel
                End If
            Loop
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

Private Sub SetSelectedProperty(ByVal Index%)
    Static Initialized%

    'Prevent re-entrancy
    If bReadData% Then Exit Sub

    'Don't re-select if its already selected
    If Initialized% And SelectedProperty% = Index% Or Index% < 1 Then Exit Sub
    Initialized% = True

    'Set the table header caption
    pnlTableHeader.Caption = olnData.List(Index%)

    'Clear out the table
    Do While grdTable.Rows > 2
        grdTable.RemoveItem 1
    Loop

    'Update the table
    bReadData% = True
    ReadMachineProperties Index%
    bReadData% = False

    'Preserve the current selection
    SelectedProperty% = Index%
End Sub

Private Sub UpdateCaption()
    Dim NewCaption$

    If lblFileSpec > "" Then
        NewCaption$ = lblFileSpec
    Else: NewCaption$ = "New Machine Report " + CStr(NewNumber)
    End If

    If chkDirty Then NewCaption$ = NewCaption$ + "*"

    Caption = NewCaption$
End Sub

