VERSION 4.00
Begin VB.Form frmGenericReport 
   Appearance      =   0  'Flat
   BackColor       =   &H80000005&
   Caption         =   "Generic Report"
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
      TabIndex        =   6
      TabStop         =   0   'False
      Top             =   3300
      Visible         =   0   'False
      Width           =   3735
   End
   Begin Crystal.CrystalReport CrystalReport 
      Left            =   960
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
   Begin MSComDlg.CommonDialog CommonDialog 
      Left            =   480
      Top             =   360
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
      Left            =   1740
      TabIndex        =   5
      Top             =   1860
      Visible         =   0   'False
      Width           =   2175
   End
End
Attribute VB_Name = "frmGenericReport"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

'//****************************************************************************
'//
'//  Copyright (c) 1995, Microsoft Corporation
'//
'//  File:  GENERIC.FRM
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

Private Sub chkDirty_Click()
    UpdateCaption
End Sub

Private Sub cmdAbort_Click()
    'Handle user abort of current lengthy operation HERE
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

    'Export report code HERE
End Sub

Private Sub cmdInitialize_Click()
    If lblFileSpec > "" Then
        'Flag that we are in data reading mode
        'Initialize for File Open HERE
    Else
        'Flag that we are in gathering data mode
        'Initialize for File New HERE
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

        'Handle user printer settings HERE
    Else
        'Supply printer default settings HERE
    End If

    'Print document HERE
End Sub

Private Sub cmdPrintPreview_Click()
    'Print Preview document HERE
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

    NewFileSpec$ = GetSaveAsFileSpec$(lblFileSpec, "Xxxxx (*.XXX)|*.XXX|All Files (*.*)|*.*") 'HERE
    If NewFileSpec$ <= "" Then Exit Sub

    SaveDoc NewFileSpec$
End Sub

Private Sub Form_Load()
    chkDirty = False

    NewNumber% = InitReportNewNumber%
    hConnect& = InitReporthConnect&
    lblFileSpec = InitReportFileSpec$
    ReportTempSpec$ = InitReportTempSpec$
End Sub

Private Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)
    Dim Resp%, FileSpec$
    
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

    If WindowState = MINIMIZED Then Exit Sub

    If OldWidth <> Width Then
        
        OldWidth = Width
    End If

    If OldHeight <> Height Then
        
        OldHeight = Height
    End If
End Sub

Private Sub Form_Unload(Cancel As Integer)
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

Private Sub lblFileSpec_Change()
    UpdateCaption
End Sub

Private Sub SaveDoc(ByVal FileSpec$)
    Dim ReportSaved%, Resp%

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

    If ReportSaved% Then
        lblFileSpec = FileSpec$
        chkDirty = False
    End If
End Sub

Private Sub UpdateCaption()
    Dim NewCaption$

    If lblFileSpec > "" Then
        NewCaption$ = lblFileSpec
    Else: NewCaption$ = "New Generic Report " + CStr(NewNumber)
    End If

    If chkDirty Then NewCaption$ = NewCaption$ + "*"

    Caption = NewCaption$
End Sub

