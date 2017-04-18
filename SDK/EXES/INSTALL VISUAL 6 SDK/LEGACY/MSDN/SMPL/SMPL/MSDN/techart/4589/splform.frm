VERSION 4.00
Begin VB.Form SPLForm 
   Caption         =   "Demo of SPL Type Library"
   ClientHeight    =   6480
   ClientLeft      =   1080
   ClientTop       =   615
   ClientWidth     =   9660
   Height          =   7170
   Icon            =   "SPLForm.frx":0000
   Left            =   1020
   LinkTopic       =   "Form1"
   ScaleHeight     =   6480
   ScaleWidth      =   9660
   Top             =   -15
   Width           =   9780
   Begin VB.Frame frSPlus 
      Caption         =   "SPlus Application"
      Height          =   6255
      Left            =   960
      TabIndex        =   0
      Top             =   120
      Width           =   8775
      Begin ComctlLib.TreeView treSPlus 
         Height          =   6015
         Left            =   120
         TabIndex        =   1
         Top             =   240
         Width           =   9495
         _Version        =   65536
         _ExtentX        =   16748
         _ExtentY        =   10610
         _StockProps     =   196
         Appearance      =   1
         ImageList       =   ""
         LabelEdit       =   1
         PathSeparator   =   "\"
         Style           =   7
      End
   End
   Begin VB.Menu mnuAbout 
      Caption         =   "&About"
   End
End
Attribute VB_Name = "SPLForm"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
'This is used with the TreeView control to connect the objects with the items using a common key
Dim TreeCollection As New Collection
Private Sub Form_Load()
Screen.MousePointer = vbArrowHourglass
Move 0, 0, Screen.Width / 2, Screen.Height / 2
Visible = True

'The following procedures take several seconds
SchedulePlus_Init
Visible = True
OutlineSPlusApplication
Screen.MousePointer = vbDefault
End Sub

Private Sub TreeView1_BeforeLabelEdit(Cancel As Integer)

End Sub
Sub OutlineSPlusApplication()
treSPlus.Nodes.Add , , "SPLUSAPPLICATION", "Application"
TreeCollection.Add Item:=SPlusApplication, Key:="SPLUSAPPLICATION"
treSPlus.Nodes.Add "SPLUSAPPLICATION", tvwChild, , _
    "LoggedOn: " & SPlusApplication.LoggedOn

TreeCollection.Add scdSchedule, "A"
treSPlus.Nodes.Add "SPLUSAPPLICATION", tvwChild, "A", _
    TypeName(scdSchedule) & ": " & scdSchedule.Name

OutlineAddTables treSPlus, scdSchedule, "A"
End Sub
Sub OutlineAddTables(OTL As Control, ScdItem As Object, ByVal ParentKey$)
If OTL.Nodes(ParentKey$).Children > 0 Then
    Exit Sub 'Control already populated
End If
Screen.MousePointer = 11
If TypeName(ScdItem) = "Item" Or TypeName(ScdItem) = "Schedule" Then
    OTL.Nodes.Add ParentKey$, tvwChild, "P_" & ParentKey$, "Properties"
    For p% = 0 To ScdItem.Properties - 1
        If TypeName(ScdItem.Properties(p%)) = "Table" Then
            TableKey = ParentKey$ & p%
            Set TblNode = OTL.Nodes.Add(ParentKey$, tvwChild, _
                TableKey, "Table: " & ScdItem.Properties(p%).Name)
            TblNode.EnsureVisible
            TreeCollection.Add ScdItem.Properties(p%), TableKey
        End If
    Next p%
End If
Screen.MousePointer = 0
End Sub
Sub OutlineShowItems(OTL As Control, ScdTable As Table, ByVal ParentKey$)
If OTL.Nodes(ParentKey$).Children > 0 Then
    Exit Sub 'Control already populated
End If
If TypeName(ScdTable) <> "Table" Then Exit Sub
ScdTable.Reset
i% = 0
While Not ScdTable.IsEndOfTable
    NewKey$ = ParentKey$ & i%
    Set NewNode = OTL.Nodes.Add(ParentKey$, tvwChild, NewKey$, "Item " & ScdTable.Item.Name & i%)
    NewNode.EnsureVisible
    TreeCollection.Add ScdTable.Item, NewKey$
    i% = i% + 1
    ScdTable.Skip
Wend
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

Private Sub treSPlus_NodeClick(ByVal Node As Node)
Select Case Left(Node.Text, 4)
    Case "Tabl"
        OutlineShowItems treSPlus, TreeCollection.Item(Node.Key), Node.Key
    Case "Item"
        OutlineAddTables treSPlus, TreeCollection.Item(Node.Key), Node.Key
    Case "Prop"
        OutlineAddProperties treSPlus, TreeCollection.Item(Node.Parent.Key), Node.Key
End Select
End Sub
Sub OutlineAddProperties(OTL As Control, ScdItem As Object, ByVal ParentKey$)
If OTL.Nodes(ParentKey$).Children > 0 Then
    Exit Sub 'Control already populated
End If
Screen.MousePointer = 11
On Error Resume Next
If TypeName(ScdItem) = "Item" Or TypeName(ScdItem) = "Schedule" Then
    For p% = 0 To ScdItem.Properties - 1
        If TypeName(ScdItem.Properties(p%)) = "Property" Then
            PropKey$ = ParentKey$ & p%
            Set TblNode = OTL.Nodes.Add(ParentKey$, tvwChild, _
                PropKey$, ScdItem.Properties(p%).Name)
            TreeCollection.Add ScdItem.Properties(p%), PropKey$ 'Optional
            TblNode.EnsureVisible
            OTL.Nodes.Add PropKey$, tvwChild, , _
                "ChangeNumber: " & ScdItem.Properties(p%).ChangeNumber
            OTL.Nodes.Add PropKey$, tvwChild, , _
                "Class: " & ScdItem.Properties(p%).Class
            OTL.Nodes.Add PropKey$, tvwChild, , _
                "Count: " & ScdItem.Properties(p%).Count
            OTL.Nodes.Add PropKey$, tvwChild, , _
                "Name: " & ScdItem.Properties(p%).Name 'Nothing
            If ScdItem.Properties(p%).Count > 1 Then
                ValueParent = PropKey$ & "V"
                Set PropNode = OTL.Notes.Add(PropKey$, _
                    tvwChild, ValueParent, _
                    " Value" & vbTab & ScdItem.Properties(p%).Value)
                For i% = 0 To ScdItem.Properties(p%).Count - 1
                    OTL.Notes.Add ValueParent, tvwChild, , _
                    "Value(" & i% & ")" & vbTab & ScdItem.Properties(p%).Value
                Next i%
            Else
                    OTL.Nodes.Add PropKey$, tvwChild, , _
                    "Value: " & ScdItem.Properties(p%).Value
            End If

            TreeCollection.Add ScdItem.Properties(p%), PropKey$
        End If
    Next p%
End If
On Error GoTo 0
Screen.MousePointer = 0
End Sub

