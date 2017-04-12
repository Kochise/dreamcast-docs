VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "COMCTL32.OCX"
Begin VB.Form MainForm 
   Caption         =   "MDO Projects - Sample Browser"
   ClientHeight    =   6225
   ClientLeft      =   1995
   ClientTop       =   1155
   ClientWidth     =   6855
   Icon            =   "browser.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   6225
   ScaleWidth      =   6855
   Begin VB.Frame Frame2 
      Height          =   855
      Left            =   120
      TabIndex        =   5
      Top             =   0
      Width           =   1095
      Begin VB.Image Image1 
         Height          =   615
         Left            =   360
         Top             =   240
         Width           =   735
      End
   End
   Begin VB.Frame Frame1 
      Height          =   855
      Left            =   1320
      TabIndex        =   1
      Top             =   0
      Width           =   5415
      Begin VB.CheckBox chkEnableEdit 
         Caption         =   "Enable e&dits"
         Height          =   255
         Left            =   3600
         TabIndex        =   6
         TabStop         =   0   'False
         ToolTipText     =   "Enables deleting and renaming Repository Objects"
         Top             =   480
         Width           =   1695
      End
      Begin VB.CheckBox chkShowIntID 
         Caption         =   "Show &IntID"
         Height          =   255
         Left            =   3600
         TabIndex        =   4
         TabStop         =   0   'False
         ToolTipText     =   "Shows the IntId of Repository Objects"
         Top             =   240
         Width           =   1575
      End
      Begin VB.CommandButton btnExit 
         Caption         =   "E&xit"
         Height          =   495
         Left            =   1920
         MaskColor       =   &H00000000&
         TabIndex        =   3
         TabStop         =   0   'False
         ToolTipText     =   "Quits the Sample Browser"
         Top             =   240
         Width           =   1215
      End
      Begin VB.CommandButton btnRefresh 
         Caption         =   "&Refresh"
         Height          =   495
         Left            =   360
         MaskColor       =   &H00000000&
         TabIndex        =   2
         TabStop         =   0   'False
         ToolTipText     =   "Refreshes the Projects display"
         Top             =   240
         Width           =   1095
      End
   End
   Begin ComctlLib.TreeView tvVBModel 
      Height          =   5175
      Left            =   120
      TabIndex        =   0
      Top             =   960
      Width           =   6615
      _ExtentX        =   11668
      _ExtentY        =   9128
      _Version        =   327682
      Indentation     =   353
      LineStyle       =   1
      Sorted          =   -1  'True
      Style           =   7
      ImageList       =   "ImageList1"
      Appearance      =   1
      MousePointer    =   1
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin ComctlLib.ImageList ImageList1 
      Left            =   5400
      Top             =   120
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   17
      ImageHeight     =   17
      MaskColor       =   16711935
      _Version        =   327682
      BeginProperty Images {0713E8C2-850A-101B-AFC0-4210102A8DA7} 
         NumListImages   =   13
         BeginProperty ListImage1 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "browser.frx":0442
            Key             =   "Closed"
         EndProperty
         BeginProperty ListImage2 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "browser.frx":05AC
            Key             =   "Open"
         EndProperty
         BeginProperty ListImage3 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "browser.frx":070A
            Key             =   "Project"
         EndProperty
         BeginProperty ListImage4 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "browser.frx":0868
            Key             =   "Reference"
         EndProperty
         BeginProperty ListImage5 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "browser.frx":09C6
            Key             =   "Form"
         EndProperty
         BeginProperty ListImage6 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "browser.frx":0B24
            Key             =   "Leaf"
         EndProperty
         BeginProperty ListImage7 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "browser.frx":0C82
            Key             =   "Control"
         EndProperty
         BeginProperty ListImage8 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "browser.frx":0DE0
            Key             =   ""
         EndProperty
         BeginProperty ListImage9 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "browser.frx":135A
            Key             =   ""
         EndProperty
         BeginProperty ListImage10 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "browser.frx":18D4
            Key             =   ""
         EndProperty
         BeginProperty ListImage11 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "browser.frx":1DFA
            Key             =   "Stop"
         EndProperty
         BeginProperty ListImage12 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "browser.frx":2114
            Key             =   "Go"
         EndProperty
         BeginProperty ListImage13 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "browser.frx":242E
            Key             =   ""
         EndProperty
      EndProperty
   End
End
Attribute VB_Name = "MainForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' ------------------------------------------------------------------------
'               Copyright (C) 1998 Microsoft Corporation
'
' You have a royalty-free right to use, modify, reproduce and distribute
' the Sample Application Files (and/or any modified version) in any way
' you find useful, provided that you agree that Microsoft has no warranty,
' obligations or liability for any Sample Application Files.
' ------------------------------------------------------------------------
Option Explicit
Private Declare Function GetWindowsDirectory Lib "kernel32" Alias "GetWindowsDirectoryA" (ByVal lpBuffer As String, ByVal nSize As Long) As Long
Public bPropsShow As Integer ' is the props window visible?

Dim m_KeyCode As Integer
Dim m_Shift As Integer
Dim iHMargin As Integer   ' width along sides of the tree view
Dim iVMargin As Integer   ' width along bottom of the tree view
Dim iTop As Integer       ' position of top of tree view
Dim sLastReference As String
Dim RepositoryPath As String
Dim Repository As Repository
Dim Root As RepositoryObject
Public OBJID_CCollectionDef As Variant

Private Sub btnExit_Click()
    Set Root = Nothing
    Set Repository = Nothing
    End
End Sub

Private Sub btnRefresh_Click()
    ShowStop
    RefreshInfo
    ShowGo
    tvVBModel.SetFocus
End Sub

Private Sub chkEnableEdit_Click()
    tvVBModel.SetFocus
End Sub

Private Sub chkShowIntID_Click()
    ShowStop
    RefreshInfo
    ShowGo
    tvVBModel.SetFocus
End Sub

Private Sub Form_Load()
    ' Initialize and open repository
    Call InitMdo
    
    ' Initialize the GUIDs
    Call InitRepository
    
    ' Find the path to the Windows directory.
    Dim wlen As Integer
    RepositoryPath = String(260, " ")
    wlen = GetWindowsDirectory(RepositoryPath, 255)
    RepositoryPath = Left(RepositoryPath, wlen) & "\msapps\repostry\repostry.mdb"

    ShowStop
        
    ' set up initial projects
    Dim NodX As Node
    
    ' clear nodes list
    tvVBModel.Nodes.Clear
    Set NodX = tvVBModel.Nodes.Add(, , "Projects", "Projects")
    NodX.Image = "Closed"
    NodX.ExpandedImage = "Open"
    NodX.Tag = "Projects"
    Set NodX = Nothing
    
    iTop = tvVBModel.Top
    iHMargin = (Width - tvVBModel.Width) / 2
    iVMargin = Height - tvVBModel.Height - tvVBModel.Top
    
    RefreshInfo
    ShowGo
End Sub

Private Sub Form_Resize()
    Dim tvWidth As Integer
    Dim tvHeight As Integer
    
    If Height < 400 Then ' minimized
        If bPropsShow Then frmPropsNew.Hide
    Else
        If bPropsShow Then frmPropsNew.Show
    End If
    
    tvWidth = Width - iHMargin * 2
    tvHeight = Height - iTop - iVMargin
    
    If (tvWidth > 0) Then tvVBModel.Width = tvWidth
    If (tvHeight > 0) Then tvVBModel.Height = tvHeight
    
End Sub

Private Sub Form_Unload(Cancel As Integer)
    Unload frmPropsNew
End Sub


Private Sub tvVBModel_AfterLabelEdit(Cancel As Integer, NewString As String)
    Dim obj As RepositoryObject
    Dim bTrans As Boolean
    
    On Error GoTo EditErr
    
    Set obj = Repository.object(tvVBModel.SelectedItem.Tag)
    Repository.Transaction.Begin
    bTrans = True
    obj.Name = NewString
    Repository.Transaction.Commit
    Exit Sub
    
EditErr:
    On Error GoTo EditExit
    If bTrans Then Repository.Transaction.Abort
EditExit:
    Cancel = True
    Exit Sub
End Sub

Private Sub tvVBModel_BeforeLabelEdit(Cancel As Integer)
    Dim obj As RepositoryObject
    
    If chkEnableEdit.Value <> 1 Then
        Cancel = True
        Exit Sub
    End If
    
    On Error GoTo EditErr
    
    ' See if there is a Repository object behind the node
    Set obj = Repository.object(tvVBModel.SelectedItem.Tag)
    Exit Sub
    
EditErr:
    ' If there's an error, there's no repository object. Don't edit.
    Cancel = True
    Exit Sub
End Sub

Private Sub tvVBModel_KeyDown(KeyCode As Integer, Shift As Integer)
    ' Save keypresses.  On keyup, check that it is the same key.
    ' Prevents things like interpreting the F5 used to run the program
    ' as an extra Refresh.  Also prevents multiple deletes from holding
    ' the key down.
    m_KeyCode = KeyCode
    m_Shift = Shift
End Sub

Private Sub tvVBModel_KeyUp(KeyCode As Integer, Shift As Integer)
    Dim obj As RepositoryObject
    Dim bTrans As Boolean
    
    ' Is the key released the last one pressed?
    If KeyCode <> m_KeyCode Or Shift <> m_Shift Then
        Exit Sub
    End If
    
    On Error GoTo DelErr
    
    If KeyCode = vbKeyDelete Then
        If chkEnableEdit.Value <> 1 Then Exit Sub
        ShowStop
        Set obj = Repository.object(tvVBModel.SelectedItem.Tag)
        Repository.Transaction.Begin
        bTrans = True
        obj.Delete
        Repository.Transaction.Commit
        tvVBModel.Nodes.Remove (tvVBModel.SelectedItem.Index)
        ShowGo
        Exit Sub
    End If
    
    If KeyCode = vbKeyF2 Then
        If chkEnableEdit.Value <> 1 Then Exit Sub
        tvVBModel.StartLabelEdit
        Exit Sub
    End If
    
    If KeyCode = vbKeyF5 Then
        ShowStop
        RefreshInfo
        ShowGo
        Exit Sub
    End If
    
    ShowGo
    Exit Sub
DelErr:
    On Error GoTo DelExit
    If bTrans Then Repository.Transaction.Abort
DelExit:
    ShowGo
    Exit Sub
End Sub

Private Sub tvVBModel_MouseUp(Button As Integer, Shift As Integer, x As Single, Y As Single)
    ' we want to display a menu on a mouse up on the right mouse button
    Dim NodX As Node
    Dim obj As RepositoryObject

    On Error GoTo btnerr

    ' if this was a right click
    If Button = vbRightButton Then
        ' prepare the form to show properties
        frmPropsNew.Show
        frmPropsNew.lstProps.Clear
        
        ' get the object and show its properties
        Set NodX = tvVBModel.HitTest(x, Y)
        Set obj = Repository.object(NodX.Tag)
        Call ShowObjectProps(obj, "")
    End If
    Exit Sub
btnerr:
    Resume Next
End Sub

Public Sub RefreshInfo()
    Dim i As Integer, j As Integer, k As Integer
    Dim MyProject As RepositoryObject
    Dim sProjectKey As String
    Dim NodX, NodLeaf As Node
    Dim details As RepositoryObject
    Dim id As String
    Dim Projects As Object
    Dim Name As String
    Dim namep As Variant
    Dim typ As Variant
    Dim mdoProject As Object
        
    ' Get around cache latency across processes
    Set Repository = Nothing
    Set Root = Nothing
    Set Repository = New Repository
    Set Root = Repository.Open()
    
    Set Projects = Root("IMpoProjectItemContainer").Contents
    If Projects.Count > 0 Then
        Load frmRefresh
        frmRefresh.Steps = Projects.Count + 1
        frmRefresh.Report ("loading projects ...")
        frmRefresh.Show
    End If

    ' clear nodes list
    tvVBModel.Nodes.Clear
    Set NodX = tvVBModel.Nodes.Add(, , "Projects", "Projects")
    NodX.Image = "Closed"
    NodX.ExpandedImage = "Open"
    NodX.Tag = "Projects"
    Set NodX = Nothing

    ' get project details
    i = 0
    For Each MyProject In Projects
        i = i + 1
        Name = "ProjectX"
        namep = MyProject.Name
        If Not IsNull(namep) Then
            Name = namep
        End If
        Name = IntId(MyProject) + Name
        frmRefresh.Report ("Loading project [" & Name & "]")
        sProjectKey = "PRJ" + Str$(i)
        
        ' add "projects" node
        
        Set NodX = tvVBModel.Nodes.Add("Projects", tvwChild, sProjectKey, Name)
        NodX.Image = "Project"
        NodX.Tag = MyProject.ObjectID
        Set NodX = Nothing
                
        ' Check if this project is an MDO project.
        On Error GoTo SkipProject
        Set mdoProject = MyProject("IMdoProject")
        On Error GoTo 0
        GoTo AddProject
SkipProject:
        On Error GoTo 0
        Resume NextProject

        ' Add references
AddProject:
        If MyProject("IMdoProject").mdoReferences.Count Then
            Set NodX = tvVBModel.Nodes.Add(sProjectKey, tvwChild, sProjectKey + "References", "References")
            NodX.Image = "Closed"
            NodX.ExpandedImage = "Open"
            NodX.Tag = "References"

            Dim MyReference As RepositoryObject

            For Each MyReference In MyProject("IMdoProject").mdoReferences
                Name = "ReferenceX"
                Name = MyReference.Name
                Name = IntId(MyReference) + Name
                Set NodLeaf = tvVBModel.Nodes.Add(NodX.Index, tvwChild, , Name)
                NodLeaf.Image = "Reference"
                NodLeaf.Tag = MyReference.ObjectID
                Set NodLeaf = Nothing
            Next ' MyReference
            
            Set NodX = Nothing
            Set MyReference = Nothing
        End If

        ' Add components
        If MyProject("IMdoProject").mdoComponents.Count Then
            Set NodX = tvVBModel.Nodes.Add(sProjectKey, tvwChild, sProjectKey + "Components", "Components")
            NodX.Image = "Closed"
            NodX.ExpandedImage = "Open"
            NodX.Tag = "Components"
            
            Dim MyComponent As RepositoryObject
            
            For Each MyComponent In MyProject("IMdoProject").mdoComponents
                Name = "ComponentX"
                Name = MyComponent.Name
                Name = IntId(MyComponent) + Name
                Set NodLeaf = tvVBModel.Nodes.Add(NodX.Index, tvwChild, , Name)
                NodLeaf.Tag = MyComponent.ObjectID
               
                ' special behavior for form-ish controls
                If AddControls(MyComponent, NodLeaf) Then
                    NodLeaf.Image = "Form"
                Else
                   NodLeaf.Image = "Leaf"
                End If
        
               Set NodLeaf = Nothing
               Set MyComponent = Nothing
            Next ' MyComponent
            
        End If
        
NextProject:
        frmRefresh.StepIt
    Next ' MyProject
    
    frmRefresh.Report ("Done")
    frmRefresh.StepIt
    
    Set NodX = Nothing
    
    tvVBModel.Nodes(1).Expanded = True
    
    Exit Sub
    
End Sub

Private Function AddControls(ReposContainer As RepositoryObject, tvContainer As Node) As Boolean
    Dim NodX As Node
    Dim NodLeaf As Node
    Dim NodControls As Node
    Dim MyControl As RepositoryObject
    Dim b As Boolean
    Dim Name As String
    Dim k As Integer
    
    On Error GoTo ControlError
    
    ' populate controls collection
    If ReposContainer("IMdoControlContainer").mdoControls.Count <= 0 Then
        AddControls = False
        Exit Function
    End If
    
    Set NodControls = tvVBModel.Nodes.Add(tvContainer.Index, tvwChild, , "Controls")
    NodControls.Image = "Closed"
    NodControls.ExpandedImage = "Open"
    
    For Each MyControl In ReposContainer("IMdoControlContainer").mdoControls
        Name = "ControlX"
        Name = MyControl.Name
        If MyControl("IMdoControl").Index > -1 Then
             Name = Name & "(" & MyControl("IMdoControl").Index & ")"
        End If
        Name = Name & " (" & MyControl("IMdoControl").ProgId & ")"
        Name = IntId(MyControl) + Name
        Set NodLeaf = tvVBModel.Nodes.Add(NodControls.Index, tvwChild, , Name)
        NodLeaf.Image = "Control"
        NodLeaf.Tag = MyControl.ObjectID
        
        ' get any sub-controls
        b = AddControls(MyControl, NodLeaf)
        
        Set NodLeaf = Nothing
        Set MyControl = Nothing
    Next ' MyControl
    
    Set NodControls = Nothing
    AddControls = True
    Exit Function
    
ControlError:
    AddControls = False
    Exit Function
End Function

Private Sub ShowObjectProps(obj As RepositoryObject, indent As String)
    ' we want to display a menu on a mouse up on the right mouse button
    Dim NodX As Node
    Dim TypeID As Variant
    Dim ObjType As ClassDef
    Dim Ifaces As IRelationshipCol
    Dim RIface As IRelationship
    Dim Iface As RepositoryObject
    Dim Props As IRelationshipCol
    Dim RProp As IRelationship
    Dim Prop As RepositoryObject
    Dim IfaceName As String
    Dim PropName As String
    Dim PropString As String

    Dim PropVal As Variant
    Dim TmpObj As Object
 
    On Error GoTo PropError
    
    TypeID = obj.Type
    frmPropsNew.Caption = obj.Name + " - Properties"
    
    Set ObjType = Repository.object(TypeID)
    Set Ifaces = ObjType.Interfaces
    For Each RIface In Ifaces
        IfaceName = RIface.Name
        If (IfaceName = "") Then IfaceName = "(" + RIface.Target.Name + ")"
        frmPropsNew.lstProps.AddItem indent & "Interface: " & IfaceName
        Set Props = RIface.Target("IInterfaceDef").Members
        For Each RProp In Props
            Set Prop = RProp.Target
            PropName = RProp.Name
            If SameOBJID(Prop.Type, OBJID_CollectionDef) Then
                frmPropsNew.lstProps.AddItem indent & "  Collection: " & PropName
            Else
                ' Get the property indirectly through the interface.  This will allow
                '  getting properties on non-default interfaces
                PropString = "<<error>>"
                Set TmpObj = obj(RIface.Target.Name)
                PropVal = TmpObj.Properties(RProp.Target.Name).Value
                If (IfaceName = "(IRepositoryObject)" And PropName = "TypeID") Then
                    PropString = IntIdToStr(PropVal)
                Else
                    If IsNull(PropVal) Then
                        PropString = "(NULL)"
                    Else
                        PropString = PropVal
                    End If
                End If
                frmPropsNew.lstProps.AddItem indent & "  Property: " & RProp.Name & " = " & PropString
            End If
        Next
    Next
    Exit Sub
    
PropError:
    Resume Next
End Sub

Private Sub ShowStop()
    Image1.Picture = ImageList1.ListImages("Stop").Picture '.ListImages("Stop").Picture
    Image1.Refresh
    btnRefresh.Enabled = False
    btnExit.Enabled = False
    chkShowIntID.Enabled = False
    chkEnableEdit.Enabled = False
    MousePointer = 11 ' wait
    tvVBModel.MousePointer = 11 ' wait
End Sub

Private Sub ShowGo()
    Image1.Picture = ImageList1.ListImages("Go").Picture '.ListImages("Go").Picture
    Image1.Refresh
    btnRefresh.Enabled = True
    btnExit.Enabled = True
    chkShowIntID.Enabled = True
    chkEnableEdit.Enabled = True
    MousePointer = 1 ' default
    tvVBModel.MousePointer = 1 ' arrow
End Sub

' are two objids equal?
Private Function SameOBJID(ID1 As Variant, ID2 As Variant) As Integer
    Dim i As Integer
    
    For i = LBound(ID1) To UBound(ID1)
        If ID1(i) <> ID2(i) Then
            SameOBJID = False
            Exit Function
        End If
    Next
    SameOBJID = True
End Function

' get the intid of an object, and convert it to a hex string
Private Function IntId(obj As RepositoryObject) As String
    Dim rslt As String
    Dim i As Integer
    Dim x
    
    If (chkShowIntID.Value = 0) Then Exit Function
    
    On Error GoTo interr:
    x = obj.InternalID
    
    IntId = IntIdToStr(x) + ": "
    
    Exit Function

interr:
    IntId = "InternalID error "
    Exit Function
End Function

' convert an intid to a hex string
Private Function IntIdToStr(id As Variant) As String
    Dim rslt As String
    Dim tmp As String
    Dim i As Integer
    Dim x
    
    On Error GoTo converr:
    
    rslt = ""
    For i = 3 To 0 Step -1
        tmp = Hex$(id(i))
        While Len(tmp) < 2
            tmp = "0" & tmp
        Wend
        rslt = rslt + tmp
    Next i
    For i = 7 To 4 Step -1
        tmp = Hex$(id(i))
        While Len(tmp) < 2
            tmp = "0" & tmp
        Wend
        rslt = rslt + tmp
    Next i
    IntIdToStr = rslt
    Exit Function

converr:
    IntIdToStr = "<<Conversion error>>"
    Exit Function
End Function


