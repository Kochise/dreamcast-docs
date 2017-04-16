VERSION 4.00
Begin VB.Form SAUForm 
   Caption         =   "Demo of Schedule+ Adds and Updates"
   ClientHeight    =   2985
   ClientLeft      =   1740
   ClientTop       =   1995
   ClientWidth     =   3840
   Height          =   3675
   Icon            =   "SAUForm.frx":0000
   KeyPreview      =   -1  'True
   Left            =   1680
   LinkTopic       =   "Form1"
   ScaleHeight     =   2985
   ScaleWidth      =   3840
   Top             =   1365
   Width           =   3960
   Begin VB.Frame frSPlus 
      Caption         =   "SPlus Application"
      Height          =   2775
      Left            =   120
      TabIndex        =   0
      Top             =   0
      Width           =   3495
      Begin ComctlLib.TreeView treSPlus 
         Height          =   2415
         Left            =   120
         TabIndex        =   1
         Top             =   240
         Width           =   2895
         _Version        =   65536
         _ExtentX        =   5106
         _ExtentY        =   4260
         _StockProps     =   196
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            name            =   "Arial"
            charset         =   0
            weight          =   400
            size            =   9
            underline       =   0   'False
            italic          =   0   'False
            strikethrough   =   0   'False
         EndProperty
         Appearance      =   1
         HideSelection   =   0   'False
         ImageList       =   "ImageList1"
         Indentation     =   317
         LabelEdit       =   1
         PathSeparator   =   "\"
         Style           =   7
      End
   End
   Begin ComctlLib.ImageList ImageList1 
      Left            =   120
      Top             =   720
      _Version        =   65536
      _ExtentX        =   1005
      _ExtentY        =   1005
      _StockProps     =   1
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      NumImages       =   7
      i1              =   "SAUForm.frx":030A
      i2              =   "SAUForm.frx":0805
      i3              =   "SAUForm.frx":0D00
      i4              =   "SAUForm.frx":11FB
      i5              =   "SAUForm.frx":16FA
      i6              =   "SAUForm.frx":1BF9
      i7              =   "SAUForm.frx":20F8
   End
   Begin VB.Menu mnuAbout 
      Caption         =   "&About"
   End
   Begin VB.Menu mnuEdit 
      Caption         =   "&Edit"
      Begin VB.Menu mnuAddItem 
         Caption         =   "&Add Item"
      End
      Begin VB.Menu mnuAddProperty 
         Caption         =   "&Add Property"
         Begin VB.Menu MnuProperty 
            Caption         =   "&Whatever"
            Index           =   0
         End
      End
      Begin VB.Menu mnuAddTable 
         Caption         =   "&Add Table"
         Begin VB.Menu mnuTables 
            Caption         =   "&What"
            Index           =   0
         End
      End
   End
   Begin VB.Menu mnuOptions 
      Caption         =   "&Options"
      Begin VB.Menu mnuItemTable 
         Caption         =   "&Expand Items with Tables"
      End
      Begin VB.Menu mnuTableProperty 
         Caption         =   "Expand &All Items"
      End
   End
End
Attribute VB_Name = "SAUForm"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Dim KeyCounter As Long
Dim TreeCollection As New Collection
Dim KeyLastTable$   'Last Table Selected
Dim KeyLastItem$    'Last Item Selected
'COnstants that are the first characters of the common key
'between TreeView and TreeCollection
Const Const_Table = "T"
Const Const_TableNoObject = "U"
Const Const_Item = "I"
Const Const_ItemNoObject = "H"
Const Const_Property = "P"
Const Const_Application = "A"
Const Const_Schedule = "S"

Private Sub Form_KeyDown(KeyCode As Integer, Shift As Integer)
'^D,DEL (46)
Select Case KeyCode
Case 17, 46 'Delete Selected Item: ^D
    Select Case Left(treSPlus.SelectedItem.Key, 1)
    Case Const_Property
         PropName$ = Left(treSPlus.SelectedItem.Text, InStr(treSPlus.SelectedItem.Text, ":") - 1)
         Set AnItem = TreeCollection(treSPlus.SelectedItem.Parent.Key)
         AnItem.DeleteProperties (PropName$)
         treSPlus.Nodes.Remove treSPlus.SelectedItem.Key
    Case Const_Item
        TreeCollection(treSPlus.SelectedItem.Parent.Key).DeleteItem treSPlus.SelectedItem.Text
        treSPlus.Nodes.Remove treSPlus.SelectedItem.Key
    Case Const_Table
        MsgBox "I leave this to you:-) - be very careful that no do not delete the wrong information!", 16
    End Select
End Select
End Sub

Private Sub Form_Load()
Move 0, 0, Screen.Width / 2, Screen.Height / 2
DefineFields
AddMenuCaptions
Visible = True
SchedulePlus_Init
OutlineSPlusApplication
End Sub

Sub OutlineSPlusApplication()
Dim NewItem As Object
RootKey = Const_Table & NewKey()
LastKey$ = AddObject(SPlusApplication, Const_Application)
LastKey$ = AddObject(scdSchedule, Const_Schedule, LastKey$)
OutlineAddTables scdSchedule, LastKey$
End Sub

Private Sub mnuAddItem_Click()
If vbYes = MsgBox("Please confirm that an item will be added to " & TreeCollection(KeyLastTable$).Name, vbYesNo, "Add Item") Then
    Set X = TreeCollection(KeyLastTable$).New
    X.Text = "New Item"
    X.Flush
    treSPlus_NodeClick treSPlus.Nodes(KeyLastTable$)
End If
End Sub

Private Sub mnuItemTable_Click()
mnuItemTable.Checked = Not mnuItemTable.Checked
End Sub

Private Sub MnuProperty_Click(Index As Integer)
NameIs$ = MnuProperty(Index).Caption
If Len(KeyLastItem$) > 0 Then
    SetPropertyValue NameIs$, TreeCollection(KeyLastItem$)
    ValueIs = TreeCollection(KeyLastItem$).GetProperty((NameIs$))
    PropKey$ = Const_Property + NewKey$()
    If Not IsError(ValueIs) Then
       treSPlus.Nodes.Add KeyLastItem$, tvwChild, PropKey$, NameIs$ & ":" & ValueIs & "[" & TypeName(ValueIs) & "]", "Property"
    End If
Else
    MsgBox "No Item object selected.", 64, "Cannot add Property"
End If
End Sub

Private Sub mnuTableProperty_Click()
 mnuTableProperty.Checked = Not mnuTableProperty.Checked
End Sub

Private Sub mnuTables_Click(Index As Integer)
If Len(KeyLastItem$) = 0 Then
    MsgBox "You must select an ITEM first": Exit Sub
End If
Set a = NameToTable(TreeCollection(KeyLastItem$), mnuTables(Index).Caption)
If TypeName(a) <> "Table" Then
    MsgBox "Adding " & mnuTables(Index).Caption & " ARE NOT SUPPORTED.", 16
    Exit Sub
Else
    Set X = a.New
End If
X.Text = Date$
X.Flush
'The TABLE is where we bring everything in.
'We could write a routine to expand a single item inste
treSPlus_NodeClick (treSPlus.Nodes(KeyLastItem$).Parent)
End Sub

Private Sub treSPlus_NodeClick(ByVal Node As Node)
Dim nodeObject As Object
Dim ATable As Object
'Make sure parent always exists in Tree Collection
If Left(Node.Key, 1) = Const_Application Then Exit Sub
Select Case Left(Node.Parent.Key, 1)
Case Const_ItemNoObject
       treSPlus_NodeClick Node.Parent
Case Const_Application
        Exit Sub
End Select

Select Case Left(Node.Key, 1)
Case Const_TableNoObject 'We must get object and add to collection.
    Set ATable = NameToTable(TreeCollection(Node.Parent.Key), Node.Text)
    If TypeName(ATable) <> "Table" Then
        Node.Image = "NoExpand"
    Else
        Node.Key = Const_Table + Mid$(Node.Key, 2)
        TreeCollection.Add Key:=Node.Key, Item:=ATable
        treSPlus_NodeClick Node 'Recursive for rest of processing
    End If
Case Const_Table  'We have an Table. To refresh we must delete and then add :-(
    mnuAddTable.Enabled = False
    mnuAddItem.Enabled = True
    mnuAddProperty.Enabled = False

      While Node.Children > 0
        'We do not remove children of children. These are automatically handled.
        Select Case Left(Node.Child.Key, 1)
            Case Const_Table, Const_Item
                TreeCollection.Remove Node.Child.Key
        End Select
        treSPlus.Nodes.Remove Node.Child.Index
      Wend
      OutlineShowItems TreeCollection(Node.Key), Node.Key
    On Error Resume Next 'Errors may occur for Events,Appointments,Tasks if Rows=0
    Node.Text = TreeCollection(Node.Key).Name & ":" & TreeCollection(Node.Key).Rows
    On Error GoTo 0
    KeyLastTable$ = Node.Key
Case Const_Item
    KeyLastItem$ = Node.Key
    KeyLastTable$ = Node.Parent.Key
    mnuAddTable.Enabled = True
    mnuAddItem.Enabled = False
    mnuAddProperty.Enabled = True

Case Const_ItemNoObject
    mnuAddTable.Enabled = True
    mnuAddItem.Enabled = False
    mnuAddProperty.Enabled = True
    'Change Key to show Object is in Collection
    Node.Key = Const_Item & Mid$(Node.Key, 2)
    'Add to Collection
    TreeCollection.Add TreeCollection.Item(Node.Parent.Key).Item(Node.Text), _
            Node.Key
    'Change the image to show a Sun
    Node.Image = "Item"
    KeyLastItem$ = Node.Key
    KeyLastTable$ = Node.Parent.Parent.Key
Case Const_Property 'We have a Property thus EDIT
    mnuAddTable.Enabled = True
    mnuAddItem.Enabled = False
    mnuAddProperty.Enabled = True
    NameIs$ = Left(Node.Text, InStr(Node.Text, ":") - 1)
    SetPropertyValue AnItem:=TreeCollection(Node.Parent.Key), NameIs:=NameIs$
    'We must put (()) around variables in this call [BUG]
    ValueIs = TreeCollection(Node.Parent.Key).GetProperty((NameIs$))
    If Not IsError(ValueIs) Then
        Node.Text = NameIs$ & ":" & ValueIs & "(" & TypeName(ValueIs) & ")"
    Else
        TreeSPLUS.Node.Remove Node.Key
    End If
    On Error Resume Next
    
    KeyLastItem$ = Node.Parent.Key
    KeyLastTable$ = Node.Parent.Parent.Key
Case Else
    mnuAddTable.Enabled = False
    mnuAddItem.Enabled = False
    mnuAddProperty.Enabled = False

End Select
Node.Selected = True
On Error GoTo 0
Exit Sub
reportError:
MsgBox Err.Description & "[" & Err.Number & "]", 16, "Node Click"
fError% = True
Resume Next
End Sub


Sub OutlineAddTables(ScdItem As Object, ByVal ParentKey$)
'Design Issue: I have tables appearing even if there are no elements in them.
Dim tNode As Object
Screen.MousePointer = 11
If TypeName(ScdItem) = "Schedule" Then
    OutlineShowSchedule ScdItem, ParentKey$
'-----------------------------------Appointments
    AddObject ScdItem.SingleAppointments, Const_Table, ParentKey$
    AddObject ScdItem.RecurringAppointments, Const_Table, ParentKey$
    ScdItem.Appointments.SetRange StartDate:=Now - 365, EndDate:=Now + 365
    AddObject ScdItem.Appointments, Const_Table, ParentKey$
'-----------------------------------Tasks
    AddObject ScdItem.SingleTasks, Const_Table, ParentKey$
    AddObject ScdItem.RecurringTasks, Const_Table, ParentKey$
    ScdItem.Tasks.SetRange StartDate:=Now - 365, EndDate:=Now + 365
    AddObject ScdItem.Tasks, Const_Table, ParentKey$
'-----------------------------------Events
    AddObject ScdItem.SingleTasks, Const_Table, ParentKey$
    AddObject ScdItem.RecurringTasks, Const_Table, ParentKey$
    ScdItem.Events.SetRange StartDate:=Now - 365, EndDate:=Now + 365
    AddObject ScdItem.Tasks, Const_Table, ParentKey$
End If
If TypeName(ScdItem) = "Item" Or TypeName(ScdItem) = "Schedule" Then
    AddObject ScdItem.Roles, Const_Table, ParentKey$
    AddObject ScdItem.Contacts, Const_Table, ParentKey$
    AddObject ScdItem.Projects, Const_Table, ParentKey$
    AddObject ScdItem.AccessControls, Const_Table, ParentKey$
    AddObject ScdItem.AlarmsToRIng, Const_Table, ParentKey$
    AddObject ScdItem.DeletedItems, Const_Table, ParentKey$
    AddObject ScdItem.Attendees, Const_Table, ParentKey$
    AddObject ScdItem.Exceptions, Const_Table, ParentKey$
End If

Screen.MousePointer = 0
End Sub
Sub OutlineShowItems(ScdTable As Table, ByVal ParentKey$)
Dim arrData As Variant
MousePointer = 11
'Check that we are not adding duplicates
If treSPlus.Nodes(ParentKey$).Children > 0 Then MsgBox "Unexpected Error - Children found": Exit Sub
On Error GoTo NoExpand:
ScdTable.Reset
On Error GoTo 0
I% = 0
On Error Resume Next
' If no rows -> skip
' if error -> no rows -> skip
Clipcnt% = ScdTable.Rows
On Error GoTo 0
While Not ScdTable.IsEndOfTable And Clipcnt% > 0
    If ScdTable.Rows - I% > 100 Then
        Clipcnt% = 100
    Else
        Clipcnt% = ScdTable.Rows - I%
    End If
    arrData = Array(Clipcnt% - 1, nFieldNames)
    I% = I% + Clipcnt%
    'ItemID is FIRST since it always exists and will be needed for other activities
    'Only 31 fields allowed in version used for this sample. Docs and Typelib appear in error
    arrData = ScdTable.GetRows(Clipcnt%, "ItemId", _
    FieldNames$(1), FieldNames$(2), FieldNames$(3), FieldNames$(4), FieldNames$(5), FieldNames$(6), _
    FieldNames$(7), FieldNames$(8), FieldNames$(9), FieldNames$(10), FieldNames$(11), FieldNames$(12), _
    FieldNames$(13), FieldNames$(14), FieldNames$(15), FieldNames$(16), FieldNames$(17), FieldNames$(18), _
    FieldNames$(19), FieldNames$(20), FieldNames$(21), FieldNames$(13), FieldNames$(14), FieldNames$(15), _
    FieldNames$(16), FieldNames$(17), FieldNames$(18), FieldNames$(19), FieldNames$(20), FieldNames$(21), _
    FieldNames$(22), FieldNames$(23), FieldNames$(24), FieldNames$(25), FieldNames$(26), FieldNames$(27), _
    FieldNames$(28), FieldNames$(29), FieldNames$(30))
'    On Error Resume Next
    For r% = 0 To Clipcnt% - 1
        rp& = rp& + 1 'RowPosition
        ItemKey$ = "H" & ParentKey$ & "-" & rp&
        Select Case Left(ItemKey$, 1)
        Case Const_ItemNoObject
            treSPlus.Nodes.Add ParentKey$, tvwChild, ItemKey$, arrData(r%, 0), "Missing"
        Case Else
            treSPlus.Nodes.Add ParentKey$, tvwChild, ItemKey$, arrData(r%, 0), "Item"
        End Select
        For c% = LBound(FieldNames) To UBound(FieldNames)
            If Not IsError(arrData(r%, c%)) Then

                If InStr(QuickSearch, "|" & FieldNames(c%) & "|") > 0 Then
                    Set childTable = treSPlus.Nodes.Add(ItemKey$, tvwChild, Const_TableNoObject & NewKey(), FieldNames$(c%) & ":", "Table")
                    If mnuItemTable.Checked Then childTable.EnsureVisible
                Else
                    Set childProperty = treSPlus.Nodes.Add(ItemKey$, tvwChild, Const_Property & NewKey(), FieldNames$(c%) & ":" & arrData(r%, c%) & "[" & TypeName(arrData(r%, c%)) & "]", "Property")
                    If mnuTableProperty.Checked Then childProperty.EnsureVisible
                End If
            End If
        Next c%
    Next r%
    On Error GoTo 0
Wend
MousePointer = 0
If treSPlus.Nodes(ParentKey$).Children = 0 Then MsgBox "There are no children"
SHOWExit:
MousePointer = 0
On Error GoTo 0
Exit Sub
NoExpand:
MsgBox ScdTable.Name & " can not be expanded." & Err.Description, 16, "Error"
Resume SHOWExit
End Sub


Private Sub Form_Resize()
If WindowState <> 1 Then
    On Error Resume Next
    frSPlus.Move 0, 0, ScaleWidth, ScaleHeight
    treSPlus.Move treSPlus.Left, treSPlus.Top, ScaleWidth - 2 * treSPlus.Left, ScaleHeight - 2 * treSPlus.Top
    On Error GoTo 0
End If
End Sub

Private Sub mnuAbout_Click()
MsgBox "Demo code from MSDN Library CD.", 64, "KenL@Microsoft.com"
End Sub

Sub OutlineShowSchedule(ScdItem As Schedule, ByVal ParentKey$)
'This procedure has been setup to show Schedule properties
Dim arrData As Variant
Const nFieldNames = 10
Dim SFieldNames$(0 To 10)
If treSPlus.Nodes(ParentKey$).Children > 0 Then Exit Sub

If TypeName(ScdItem) <> "Item" And TypeName(ScdItem) <> "Schedule" Then Exit Sub
On Error GoTo 0
    arrData = Array(1, nFieldNames)
    'We must put variables in () to get byval passed *** BUG WORKAROUND
    arrData = ScdItem.GetProperties((SFieldNames$(0)), _
        (SFieldNames$(1)), (SFieldNames$(2)), (SFieldNames$(3)), _
        (SFieldNames$(4)), (SFieldNames$(5)), (SFieldNames$(6)), _
        (SFieldNames$(7)), (SFieldNames$(8)), (SFieldNames$(9)), _
        (SFieldNames$(10)))
'All the elements are properties
'Arrays and Tables are skipped for teaching purposes
        For c% = LBound(SFieldNames) To UBound(SFieldNames)
            If Not IsError(arrData(0, c%)) Then
                treSPlus.Nodes.Add ParentKey$, tvwChild, , FieldNames$(c%) & ":" & arrData(0, c%) & "[" & TypeName(arrData(0, c%)) & "]", "Property"
            End If
        Next c%
    On Error GoTo 0
End Sub
Private Sub AddMenuCaptions()
Dim I As Integer
' Add items to Caption
For I = 0 To 12
If I > 0 Then
   Load MnuProperty(I)
   MnuProperty(I).Visible = True
End If
   MnuProperty(I).Caption = FieldNames(I + 1)
Next I

For I = LBound(TableNames$) To UBound(TableNames$)
If I > 0 Then
   Load mnuTables(I)
   mnuTables(I).Visible = True
End If
   mnuTables(I).Caption = TableNames(I)
Next I
End Sub

Function AddObject(AnObject As Object, ByVal AnType$, Optional ParentKey)
AnKey$ = AnType$ & NewKey()
If IsMissing(ParentKey) Then
    treSPlus.Nodes.Add , , AnKey$, TypeName(AnObject), TypeName(AnObject)
    TreeCollection.Add Item:=AnObject, Key:=AnKey$
Else
    Select Case AnType$
    Case Const_Table
        Set AnItem = treSPlus.Nodes.Add(ParentKey, tvwChild, AnKey$, AnObject.Name, TypeName(AnObject))
        AnItem.EnsureVisible
    Case Const_Schedule
        treSPlus.Nodes.Add ParentKey, tvwChild, AnKey$, TypeName(AnObject) & ":" & AnObject.Name, TypeName(AnObject)
    Case Else
        treSPlus.Nodes.Add ParentKey, tvwChild, AnKey$, TypeName(AnObject), TypeName(AnObject)
    End Select
TreeCollection.Add Item:=AnObject, Key:=AnKey$
End If
AddObject = AnKey$
End Function
