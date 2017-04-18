VERSION 4.00
Begin VB.MDIForm frmBrowser 
   Appearance      =   0  'Flat
   BackColor       =   &H8000000C&
   Caption         =   "SMS Browser"
   ClientHeight    =   4725
   ClientLeft      =   1995
   ClientTop       =   1785
   ClientWidth     =   7935
   Height          =   5415
   Icon            =   "BROWSER.frx":0000
   Left            =   1935
   LinkTopic       =   "Form1"
   Top             =   1155
   Width           =   8055
   Begin VB.PictureBox picFormBackdrop 
      Align           =   1  'Align Top
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
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
      Height          =   4335
      Left            =   0
      ScaleHeight     =   4335
      ScaleWidth      =   7935
      TabIndex        =   4
      TabStop         =   0   'False
      Top             =   0
      Width           =   7935
      Begin VB.PictureBox picSeperator 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
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
         Height          =   4215
         Left            =   3420
         MousePointer    =   9  'Size W E
         ScaleHeight     =   4185
         ScaleWidth      =   45
         TabIndex        =   5
         TabStop         =   0   'False
         Top             =   0
         Width           =   75
      End
      Begin VB.PictureBox picRightView 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         BorderStyle     =   0  'None
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
         Height          =   3495
         Left            =   3480
         ScaleHeight     =   3495
         ScaleWidth      =   3735
         TabIndex        =   7
         TabStop         =   0   'False
         Top             =   0
         Width           =   3735
         Begin Threed.SSPanel pnlInfoHeader 
            Height          =   255
            Left            =   0
            TabIndex        =   2
            Top             =   0
            Width           =   2895
            _Version        =   65536
            _ExtentX        =   5106
            _ExtentY        =   450
            _StockProps     =   15
            Caption         =   "&Object Information"
            BackColor       =   -2147483633
            BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
               name            =   "MS Sans Serif"
               charset         =   0
               weight          =   700
               size            =   8.25
               underline       =   0   'False
               italic          =   0   'False
               strikethrough   =   0   'False
            EndProperty
            BevelWidth      =   2
            BorderWidth     =   0
            Autosize        =   3
         End
         Begin VB.ListBox lstObjectInfo 
            Appearance      =   0  'Flat
            BeginProperty Font 
               name            =   "MS Sans Serif"
               charset         =   0
               weight          =   700
               size            =   8.25
               underline       =   0   'False
               italic          =   0   'False
               strikethrough   =   0   'False
            EndProperty
            Height          =   3150
            Left            =   0
            TabIndex        =   3
            Top             =   240
            Width           =   2865
         End
      End
      Begin VB.PictureBox picLeftView 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         BorderStyle     =   0  'None
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
         Height          =   4095
         Left            =   0
         ScaleHeight     =   4095
         ScaleWidth      =   3075
         TabIndex        =   6
         TabStop         =   0   'False
         Top             =   0
         Width           =   3075
         Begin Threed.SSPanel pnlContainerHeader 
            Height          =   255
            Left            =   0
            TabIndex        =   0
            Top             =   0
            Width           =   2175
            _Version        =   65536
            _ExtentX        =   3836
            _ExtentY        =   450
            _StockProps     =   15
            Caption         =   "&Container"
            BackColor       =   -2147483633
            BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
               name            =   "MS Sans Serif"
               charset         =   0
               weight          =   700
               size            =   8.25
               underline       =   0   'False
               italic          =   0   'False
               strikethrough   =   0   'False
            EndProperty
            BevelWidth      =   2
            BorderWidth     =   0
            Autosize        =   3
         End
         Begin MSOutl.Outline olnContainer 
            Height          =   2715
            Left            =   0
            TabIndex        =   1
            Top             =   240
            Width           =   2175
            _Version        =   65536
            _ExtentX        =   3836
            _ExtentY        =   4789
            _StockProps     =   77
            ForeColor       =   -2147483630
            BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
               name            =   "MS Sans Serif"
               charset         =   0
               weight          =   700
               size            =   8.25
               underline       =   0   'False
               italic          =   0   'False
               strikethrough   =   0   'False
            EndProperty
            BorderStyle     =   0
            PicturePlus     =   "BROWSER.frx":030A
            PictureMinus    =   "BROWSER.frx":047C
            PictureLeaf     =   "BROWSER.frx":05EE
            PictureOpen     =   "BROWSER.frx":0760
            PictureClosed   =   "BROWSER.frx":08D2
         End
      End
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&File"
      Begin VB.Menu mnuFileNewContainer 
         Caption         =   "New &Container"
      End
      Begin VB.Menu mnuFileExit 
         Caption         =   "&Exit"
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "&Help"
      Begin VB.Menu mnuHelpAbout 
         Caption         =   "&About..."
      End
   End
End
Attribute VB_Name = "frmBrowser"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

Dim ghConnect&
Dim gContainerCount&

'Seperator dragging state and cursor offset
Dim SeperatorDragging%
Dim SeperatorDragOffset%

Private Function ConvertTimetToDateTime(timet&) As Double
    Dim dtimet As Double
    
    If timet < 0 Then
        dtimet = CDbl(&H7FFFFFFF) + 1 + (timet Or &H7FFFFFFF)
    Else: dtimet = CDbl(timet)
    End If
    ConvertTimetToDateTime = CVDate("1 Jan 1970") + dtimet / 86400
End Function

Private Function GetScalarTypeName$(scType As SCALARTYPE)
    Select Case scType.enum
        Case SCALAR_STRING.enum
            GetScalarTypeName$ = "String"
        Case SCALAR_INT.enum
            GetScalarTypeName$ = "Number"
        Case SCALAR_TIME.enum
            GetScalarTypeName$ = "DateTime"
        Case SCALAR_BINARY.enum
            GetScalarTypeName$ = "Binary"
    End Select
End Function

Private Sub MDIForm_Load()
    Dim SqlConnectParams As SQL_CONNECT_PARAMS

    'Get the size of one pixel size in twips
    GetPixelSizeInTwips Me, X_PIX_SIZE, Y_PIX_SIZE

    'Login to SMS
    If DBLogin%(SqlConnectParams, ghConnect&) = False Then
        'User canceled, so quit application
        Unload Me
        Exit Sub
    End If

    'Position Left View and controls (will be resized later)
    picLeftView.left = 0
    picLeftView.top = 0
        pnlContainerHeader.left = 0
        pnlContainerHeader.top = 0
        olnContainer.left = 0
        olnContainer.top = pnlContainerHeader.Height
    picLeftView.Width = 2000

    'Position View Seperator (will be resized later)
    picSeperator.left = picLeftView.Width
    picSeperator.top = -Y_PIX_SIZE

    'Position Right View and controls (will be resized later)
    picRightView.left = picSeperator.left + picSeperator.Width
    picRightView.top = 0
        pnlInfoHeader.left = 0
        pnlInfoHeader.top = 0
        lstObjectInfo.left = -X_PIX_SIZE
        lstObjectInfo.top = pnlInfoHeader.Height - Y_PIX_SIZE

    olnContainer.AddItem "SMS Containers", 0
    olnContainer.Indent(0) = 1
    olnContainer.ItemData(0) = AddOutlineEntry&(T_ROOTOBJECT, 0, 0, True)
    olnContainer.ListIndex = 0

End Sub

Private Sub MDIForm_Resize()
    Static OldHeight
    Dim r As Rect, VBorderPixels%

    'See if we're minimized
    If WindowState = MINIMIZED Then Exit Sub

    'Get client size of form (already in pixels, I find)
    GetClientRect hwnd, r
    VBorderPixels% = Height / Y_PIX_SIZE - r.bottom

    If OldHeight <> Height Then
        picFormBackdrop.Height = Height - Y_PIX_SIZE * VBorderPixels% - picFormBackdrop.top

        OldHeight = Height
    End If
End Sub

Private Sub MDIForm_Unload(Cancel As Integer)
    Dim lRet&, ListIndex%

    Me.Hide

    Do While olnContainer.ListCount
        olnContainer.Expand(0) = False
        FreeOutlineEntry olnContainer.ItemData(0)
        olnContainer.RemoveItem 0
    Loop

    DBLogout ghConnect&
End Sub

Private Sub mnuFileExit_Click()
    Unload Me
End Sub

Private Sub mnuFileNewContainer_Click()
    Dim ContainerName$, ContainerTag&, FolderInfo As FOLDER_INFO
    Dim ListIndex%, lRet&

    If NewContainer%(ghConnect&, ContainerName$, ContainerTag&) Then
        lRet& = SmsDescribeFolder&(T_CONTAINER, ContainerTag&, FolderInfo)
        If (lRet& <> SMS_OK) Then GoTo mnuFileNewContainerClickErr
    
        ListIndex% = olnContainer.ListCount
        olnContainer.AddItem ContainerName$ + " (" + FolderInfo.pszTag + ")", ListIndex%
        olnContainer.Indent(ListIndex%) = 2
        olnContainer.ItemData(ListIndex%) = AddOutlineEntry&(T_CONTAINER, ContainerTag&, 0&, True)
        olnContainer.PictureType(ListIndex%) = MSOUTLINE_PICTURE_CLOSED
        If Not olnContainer.Expand(0) Then olnContainer.Expand(0) = True
    End If

    Exit Sub

mnuFileNewContainerClickErr:
    MsgBox "mnuFileNewContainer_Click: Unexpected error", MB_OK, Me.Caption
End Sub

Private Sub mnuHelpAbout_Click()
    Dim Info$

    Info$ = "SMS Browser" + Chr$(10) + Chr$(10) + "A Microsoft SMS SDK sample application"
    Info$ = Info$ + Chr$(10) + "written in Microsoft Visual Basic 3.0 Professional Edition that"
    Info$ = Info$ + Chr$(10) + "demonstrates the Visual Basic Wrapper DLL for SMS API."

    SmsAbout "About SMS Browser", Info$
End Sub

Private Sub olnContainer_Click()
    Dim SelEntry As OutlineEntryData
    Static NextScalar As SCALAR, FilterInfo As FILTER_INFO
    Dim Filters() As FILTER_INFO, FilterCount&
    Dim FolderInfo As FOLDER_INFO, SubInfo As FOLDER_INFO, FolderTag&, FolderTagName$
    Dim SMSAPIVersion$, Text$
    Dim i%, j%, Row%, ListIndex%, DateTime#, lRet&, FilterIndex%, lFilterCount&
    ReDim FolderTags&(0), FilterTags&(0), Scalars(0)

    lstObjectInfo.Clear
    Row% = 0

    ListIndex% = olnContainer.ListIndex
    GetOutlineEntry olnContainer.ItemData(ListIndex%), SelEntry
    If SelEntry.Type.enum = T_ROOTOBJECT.enum Then
        'Display the SMSAPI version string
        lRet& = SmsAPIVer&(SMSAPIVersion$)
        If (lRet& <> SMS_OK) Then GoTo olnContainerClickErr
        
        lstObjectInfo.AddItem SMSAPIVersion$, Row%
        Row% = Row% + 1
    
    ElseIf SelEntry.Type.enum = T_CONTAINER.enum Then
        'Get info on selected container
        lRet& = SmsDescribeFolder&(T_CONTAINER, SelEntry.Tag&, FolderInfo)
        If (lRet& <> SMS_OK) Then GoTo olnContainerClickErr

        lstObjectInfo.AddItem FolderInfo.pszTag, Row%
        Row% = Row% + 1

        lstObjectInfo.AddItem Chr$(9) + "Folder Types:", Row%
        Row% = Row% + 1

        For i% = Row% To FolderInfo.ctFolders - 1 + Row%
            lRet& = SmsDescribeFolder&(T_FOLDER, FolderInfo.FolderTags&(i% - Row%), SubInfo)
            If (lRet& <> SMS_OK) Then GoTo olnContainerClickErr

            lstObjectInfo.AddItem Chr$(9) + Chr$(9) + SubInfo.pszTag, Row%
        Next i%
        Row% = Row% + FolderInfo.ctFolders

        lstObjectInfo.AddItem Chr$(9) + "Filter Types:", Row%
        Row% = Row% + 1

        lRet& = SmsEnumFilters(Filters, FilterCount&)
        If (lRet& <> SMS_OK) Then GoTo olnContainerClickErr
        For i% = Row% To FolderInfo.ctFilters - 1 + Row%
            lstObjectInfo.AddItem Chr$(9) + Chr$(9) + Filters(FolderInfo.FilterTags(i% - Row%) - 1).szTag, Row%
        Next i%
        Row% = Row% + FolderInfo.ctFilters

    ElseIf SelEntry.Type.enum = T_FOLDER.enum Then
        'Get info on selected Folder
        lRet& = SmsDescribeFolder&(T_FOLDER, SelEntry.Tag&, FolderInfo)
        If (lRet& <> SMS_OK) Then GoTo olnContainerClickErr

        lstObjectInfo.AddItem FolderInfo.pszTag, Row%
        Row% = Row% + 1

        lstObjectInfo.AddItem Chr$(9) + "Folder Types:", Row%
        Row% = Row% + 1

        For i% = Row% To FolderInfo.ctFolders - 1 + Row%
            lRet& = SmsDescribeFolder&(T_FOLDER, FolderInfo.FolderTags&(i% - Row%), SubInfo)
            If (lRet& <> SMS_OK) Then GoTo olnContainerClickErr

            lstObjectInfo.AddItem Chr$(9) + Chr$(9) + SubInfo.pszTag, Row%
        Next i%
        Row% = Row% + FolderInfo.ctFolders

        'Get list of possible scalar types
        lstObjectInfo.AddItem Chr$(9) + "Scalar Types:", Row%
        Row% = Row% + 1

        For i% = Row% To FolderInfo.ctScalars - 1 + Row%
            lstObjectInfo.AddItem Chr$(9) + Chr$(9) + FolderInfo.Scalars(i% - Row%).szName, Row%
        Next i%
        Row% = Row% + FolderInfo.ctScalars

    ElseIf SelEntry.Type.enum = T_SCALAR.enum Then
        lRet& = SmsRewind&(SelEntry.Handle&, RW_ALL)
        If lRet& <> SMS_OK Then GoTo olnContainerClickErr

        lRet& = SmsGetNextScalar&(SelEntry.Handle&, NextScalar)
        Do While lRet& = SMS_OK
            If olnContainer.List(ListIndex%) = NextScalar.pszName$ + " (" + GetScalarTypeName$(NextScalar.scType) + ")" Then
                lstObjectInfo.AddItem GetScalarTypeName$(NextScalar.scType), Row%
                Row% = Row% + 1
                lstObjectInfo.AddItem Chr$(9) + "Value:", Row%
                Row% = Row% + 1
                Select Case NextScalar.scType.enum
                    Case SCALAR_STRING.enum
                        lstObjectInfo.AddItem Chr$(9) + Chr$(9) + CStr(NextScalar.pszValue), Row%
                        Row% = Row% + 1
                    Case SCALAR_INT.enum
                        lstObjectInfo.AddItem Chr$(9) + Chr$(9) + CStr(NextScalar.dwValue), Row%
                        Row% = Row% + 1
                        If NextScalar.bStringEquivalence Then
                            lstObjectInfo.AddItem Chr$(9) + "String Equivalent:", Row%
                            Row% = Row% + 1
                            lstObjectInfo.AddItem Chr$(9) + Chr$(9) + NextScalar.pszValue, Row%
                            Row% = Row% + 1
                        End If
                    Case SCALAR_TIME.enum
                        DateTime# = ConvertTimetToDateTime(NextScalar.tValue)
                        If IsDate(CVDate(DateTime#)) Then
                            lstObjectInfo.AddItem Chr$(9) + Chr$(9) + Format$(DateTime#, "ddd mmm dd yyyy hh:mm:ss") + " GMT", Row%
                        Else: lstObjectInfo.AddItem Chr$(9) + Chr$(9) + "<invalid date time>", Row%
                        End If
                        Row% = Row% + 1
                        If NextScalar.bStringEquivalence Then
                            lstObjectInfo.AddItem Chr$(9) + "String Equivalent:", Row%
                            Row% = Row% + 1
                            lstObjectInfo.AddItem Chr$(9) + Chr$(9) + NextScalar.pszValue, Row%
                            Row% = Row% + 1
                        End If
                    Case SCALAR_BINARY.enum
                        For i% = 0 To NextScalar.dwLen - 1 Step 16
                            If (i% = &H100 And NextScalar.dwLen > &H110) Then
                                i% = (NextScalar.dwLen - 1) And &HFFFFFFF0
                                lstObjectInfo.AddItem Chr$(9) + ":", Row%
                                Row% = Row% + 1
                            End If
                            Text$ = Hex$(i%)
                            Text$ = String$(8 - Len(Text$), "0") + Text$ + " "
                            For j% = 0 To 15
                                If (i% + j% >= NextScalar.dwLen) Then
                                    Text$ = Text$ + ""
                                Else: Text$ = Text$ + " " + String$((NextScalar.pValue(i% + j%) > 15) + 1, "0") + Hex$(NextScalar.pValue(i% + j%))
                                End If
                            Next j%
                            lstObjectInfo.AddItem Chr$(9) + Text$, Row%
                            Row% = Row% + 1
                        Next i%
                    Case Else
                        GoTo olnContainerClickErr
                End Select
                lRet& = SMS_NO_MORE_DATA
                Exit Do
            End If
            lRet& = SmsGetNextScalar&(SelEntry.Handle&, NextScalar)
        Loop
        If lRet& <> SMS_NO_MORE_DATA Then GoTo olnContainerClickErr
    
    Else: GoTo olnContainerClickErr
    End If
    
    Exit Sub

olnContainerClickErr:
    MsgBox "olnContainerClick:"
End Sub

Private Sub olnContainer_Collapse(ListIndex%)
    Dim SelEntry As OutlineEntryData, DelEntry As OutlineEntryData
    Dim NextListIndex%, FreeEntry%, lRet&
    Static DepthOfRecursion%

    DepthOfRecursion% = DepthOfRecursion% + 1

    NextListIndex% = ListIndex% + 1
    Do While NextListIndex% < olnContainer.ListCount
        If olnContainer.Indent(NextListIndex%) <= olnContainer.Indent(ListIndex%) Then Exit Do
        olnContainer.Expand(NextListIndex%) = False

        FreeEntry% = False
        GetOutlineEntry olnContainer.ItemData(NextListIndex%), DelEntry
        If DelEntry.Type.enum = T_ROOTOBJECT.enum Then
            'Nothing to do
        
        ElseIf DelEntry.Type.enum = T_CONTAINER.enum Then
            If DelEntry.Handle& <> 0 Then
                lRet& = SmsCloseContainer&(DelEntry.Handle&)
                If (lRet& <> SMS_OK) Then GoSub olnContainerCollapseErr

                DelEntry.Handle& = 0
                DelEntry.RetrieveData% = True
                SetOutlineEntry olnContainer.ItemData(NextListIndex%), DelEntry
            End If

        ElseIf DelEntry.Type.enum = T_FOLDER.enum Then
            If DelEntry.Handle& <> 0 Then
                lRet& = SmsCloseFolder&(DelEntry.Handle&)
            End If
            If (lRet& <> SMS_OK) Then GoSub olnContainerCollapseErr
            FreeEntry% = True

        ElseIf DelEntry.Type.enum = T_SCALAR.enum Then
            FreeEntry% = True

        Else: GoTo olnContainerCollapseErr
        End If
    
        If FreeEntry% Then
            FreeOutlineEntry olnContainer.ItemData(NextListIndex%)
            olnContainer.RemoveItem NextListIndex%
        Else
            NextListIndex% = NextListIndex% + 1
        End If
    Loop

    GetOutlineEntry olnContainer.ItemData(ListIndex%), SelEntry
    If SelEntry.RetrieveData% = False Then
        SelEntry.RetrieveData% = True
        SetOutlineEntry olnContainer.ItemData(ListIndex%), SelEntry
    End If

    If olnContainer.PictureType(ListIndex%) = MSOUTLINE_PICTURE_OPEN Then
        olnContainer.PictureType(ListIndex%) = MSOUTLINE_PICTURE_CLOSED
    End If

    DepthOfRecursion% = DepthOfRecursion% - 1
    If DepthOfRecursion% = 0 Then
        olnContainer.ListIndex = ListIndex%
        olnContainer_Click
    End If

    Exit Sub
    
olnContainerCollapseErr:
    MsgBox "Unexpected error collapsing item " + CStr(ListIndex%), MB_ICONEXCLAMATION, Me.Caption
    DepthOfRecursion% = DepthOfRecursion% - 1
    Return
End Sub

Private Sub olnContainer_DblClick()
    olnContainer.Expand(olnContainer.ListIndex) = Not olnContainer.Expand(olnContainer.ListIndex)
End Sub

Private Sub olnContainer_Expand(ListIndex%)
    Dim SelEntry As OutlineEntryData
    Dim FolderInfo As FOLDER_INFO, NextScalar As SCALAR
    Dim hSubFolder&, SubFolderType&, SubFolderTypeName$
    Dim SubFolderID$
    Dim i%, OldMousePointer%, lRet&

    GetOutlineEntry olnContainer.ItemData(ListIndex%), SelEntry
    If SelEntry.RetrieveData% Then
        'Put up the wait cursor
        OldMousePointer = MousePointer
        MousePointer = HOURGLASS
        
        If SelEntry.Type.enum = T_ROOTOBJECT.enum Then
            'Nothing to do
        
        ElseIf SelEntry.Type.enum = T_CONTAINER.enum Then
            'Rewind or open/fill the container
            If SelEntry.Handle& <> 0& Then
                lRet& = SmsRewind&(SelEntry.Handle&, RW_ALL)
                If lRet& <> SMS_OK Then GoTo olnContainerExpandErr
            Else
                lRet& = SmsOpenContainer&(SelEntry.Tag&, ghConnect&, SelEntry.Handle&)
                If lRet& <> SMS_OK Then GoTo olnContainerExpandErr
    
                lRet& = SmsPopulate&(SelEntry.Handle&, POP_SYNC, ByVal 0&)
                If lRet& <> SMS_OK And lRet& <> SMS_EMPTY Then GoTo olnContainerExpandErr
            End If

            'List the folders in this container
            i% = 1
            lRet& = SmsGetNextFolder&(SelEntry.Handle&, F_ANY, hSubFolder&)
            Do While lRet& = SMS_OK
                lRet& = SmsGetFolderID&(hSubFolder&, SubFolderID$)
                If lRet& <> SMS_OK Then GoTo olnContainerExpandErr

                lRet& = SmsGetFolderType&(hSubFolder&, SubFolderType&, SubFolderTypeName$)
                If lRet& <> SMS_OK Then GoTo olnContainerExpandErr

                If SelEntry.Tag = C_SITE Then
                    'Only list top level Site folders (Depth = 0)
                    lRet& = SmsGetScalarByName&(hSubFolder&, "Depth", NextScalar)
                    If lRet& <> SMS_OK Then GoTo olnContainerExpandErr
                Else
                    'List all sub folders
                    NextScalar.dwValue = 0
                End If
                
                If NextScalar.dwValue = 0 Then
                    olnContainer.AddItem SubFolderID$ + " (" + SubFolderTypeName$ + ")", ListIndex% + i%
                    olnContainer.Indent(ListIndex% + i%) = olnContainer.Indent(ListIndex%) + 1
                    olnContainer.ItemData(ListIndex% + i%) = AddOutlineEntry(T_FOLDER, SubFolderType&, hSubFolder&, True)
                    olnContainer.PictureType(ListIndex% + i%) = MSOUTLINE_PICTURE_CLOSED
                Else
                    lRet& = SmsCloseFolder&(hSubFolder&)
                End If

                lRet& = SmsGetNextFolder&(SelEntry.Handle&, F_ANY, hSubFolder&)
                i% = i% + 1
            Loop
            If lRet& <> SMS_NO_MORE_DATA Then GoTo olnContainerExpandErr
    
        ElseIf SelEntry.Type.enum = T_FOLDER.enum Then
            If SelEntry.Handle& = 0& Then
                GoTo olnContainerExpandErr
            Else
                lRet& = SmsRewind&(SelEntry.Handle&, RW_ALL)
                If lRet& <> SMS_OK Then GoTo olnContainerExpandErr
            End If
            
            'First list the sub-folders in this folder
            i% = 1
            lRet& = SmsGetNextFolder&(SelEntry.Handle&, F_ANY, hSubFolder&)
            Do While lRet& = SMS_OK
                lRet& = SmsGetFolderID&(hSubFolder&, SubFolderID$)
                If lRet& <> SMS_OK Then GoTo olnContainerExpandErr

                lRet& = SmsGetFolderType&(hSubFolder&, SubFolderType&, SubFolderTypeName$)
                If lRet& <> SMS_OK Then GoTo olnContainerExpandErr

                olnContainer.AddItem SubFolderID$ + " (" + SubFolderTypeName$ + ")", ListIndex% + i%
                olnContainer.Indent(ListIndex% + i%) = olnContainer.Indent(ListIndex%) + 1
                olnContainer.ItemData(ListIndex% + i%) = AddOutlineEntry(T_FOLDER, SubFolderType&, hSubFolder&, True)
                olnContainer.PictureType(ListIndex% + i%) = MSOUTLINE_PICTURE_CLOSED
                
                lRet& = SmsGetNextFolder&(SelEntry.Handle&, F_ANY, hSubFolder&)
                i% = i% + 1
            Loop
            If lRet& <> SMS_NO_MORE_DATA Then GoTo olnContainerExpandErr
            
            'Next list the scalars in this folder
            lRet& = SmsGetNextScalar&(SelEntry.Handle&, NextScalar)
            Do While lRet& = SMS_OK
                olnContainer.AddItem NextScalar.pszName$ + " (" + GetScalarTypeName$(NextScalar.scType) + ")", ListIndex% + i%
                olnContainer.Indent(ListIndex% + i%) = olnContainer.Indent(ListIndex%) + 1
                olnContainer.ItemData(ListIndex% + i%) = AddOutlineEntry(T_SCALAR, NextScalar.scType.enum, SelEntry.Handle&, True)
                olnContainer.PictureType(ListIndex% + i%) = MSOUTLINE_PICTURE_LEAF
            
                lRet& = SmsGetNextScalar&(SelEntry.Handle&, NextScalar)
                i% = i% + 1
            Loop
            If lRet& <> SMS_NO_MORE_DATA Then GoTo olnContainerExpandErr
    
        ElseIf SelEntry.Type.enum = T_SCALAR.enum Then
            'Nothing to do
        
        Else: GoTo olnContainerExpandErr
        End If
    
        SelEntry.RetrieveData% = False
        SetOutlineEntry olnContainer.ItemData(ListIndex%), SelEntry
        olnContainer.Expand(ListIndex%) = True
        
        'Restore the mouse pointer
        MousePointer = OldMousePointer%
    Else

        If olnContainer.PictureType(ListIndex%) = MSOUTLINE_PICTURE_CLOSED Then
            olnContainer.PictureType(ListIndex%) = MSOUTLINE_PICTURE_OPEN
        ElseIf olnContainer.PictureType(ListIndex%) = MSOUTLINE_PICTURE_OPEN Then
            olnContainer.Expand(ListIndex%) = False
        End If

        olnContainer.ListIndex = ListIndex%
        olnContainer_Click
    End If

    Exit Sub

olnContainerExpandErr:
    MsgBox "olnContainer_Expand: Unexpected error"
        
    'Restore the mouse pointer
    MousePointer = OldMousePointer%
End Sub

Private Sub olnContainer_PictureClick(ListIndex As Integer)
    olnContainer.ListIndex = ListIndex
    olnContainer_Click
End Sub

Private Sub olnContainer_PictureDblClick(ListIndex As Integer)
    olnContainer_PictureClick ListIndex
    olnContainer_DblClick
End Sub

Private Sub picFormBackdrop_Resize()
    Static OldWidth, OldHeight, OldSepLeft%

    If (OldWidth <> picFormBackdrop.Width Or OldSepLeft <> picSeperator.left) And picFormBackdrop.Width > picRightView.left Then
        picRightView.Width = picFormBackdrop.Width - picRightView.left

        OldWidth = picFormBackdrop.Width
    End If

    If OldHeight <> picFormBackdrop.Height And picFormBackdrop.Height > picLeftView.top Then
        picLeftView.Height = picFormBackdrop.Height - picLeftView.top
        picRightView.Height = picFormBackdrop.Height - picRightView.top
        picSeperator.Height = picFormBackdrop.Height - picSeperator.top + Y_PIX_SIZE

        OldHeight = picFormBackdrop.Height
        OldSepLeft = picSeperator.left
    End If
End Sub

Private Sub picLeftView_Resize()
    Static OldWidth, OldHeight

    If OldWidth <> picLeftView.Width Then
        pnlContainerHeader.Width = picLeftView.Width
        olnContainer.Width = picLeftView.Width

        OldWidth = picLeftView.Width
    End If

    If OldHeight <> picLeftView.Height And picLeftView.Height > olnContainer.top Then
        olnContainer.Height = picLeftView.Height - olnContainer.top

        OldHeight = picLeftView.Height
    End If
End Sub

Private Sub picRightView_Resize()
    Static OldWidth, OldHeight, lItemHeight&
        
    If OldWidth <> picRightView.Width Then
        pnlInfoHeader.Width = picRightView.Width
        lstObjectInfo.Width = picRightView.Width - lstObjectInfo.left + X_PIX_SIZE

        OldWidth = picLeftView.Width
    End If

    If OldHeight <> picRightView.Height And picRightView.Height > pnlInfoHeader.Height Then
        lItemHeight& = SendMessage(lstObjectInfo.hwnd, LB_GETITEMHEIGHT, 0, 0)
        lstObjectInfo.Height = picRightView.Height - lstObjectInfo.top + lItemHeight& * Y_PIX_SIZE

        OldWidth = picLeftView.Width
    End If
End Sub

Private Sub picSeperator_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
    If Button And LEFT_BUTTON Then
        SeperatorDragging% = True
        SeperatorDragOffset% = x
    End If
End Sub

Private Sub picSeperator_MouseMove(Button As Integer, Shift As Integer, x As Single, y As Single)
    Dim OldLeft%

    If SeperatorDragging% And x <> OldLeft% And picSeperator.left + x - SeperatorDragOffset% > 0 Then
        picSeperator.left = picSeperator.left + x - SeperatorDragOffset%
        picLeftView.Width = picSeperator.left
        picRightView.left = picSeperator.left + picSeperator.Width
        picFormBackdrop_Resize
    End If
End Sub

Private Sub picSeperator_MouseUp(Button As Integer, Shift As Integer, x As Single, y As Single)
    If Button And LEFT_BUTTON Then
        SeperatorDragging% = False
    End If
End Sub

