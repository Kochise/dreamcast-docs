VERSION 4.00
Begin VB.Form SPLForm 
   Caption         =   "Demo of Schedule+ Programming Model (PM)"
   ClientHeight    =   6480
   ClientLeft      =   1080
   ClientTop       =   615
   ClientWidth     =   9660
   Height          =   7170
   Icon            =   "SPMForm.frx":0000
   Left            =   1020
   LinkTopic       =   "Form1"
   ScaleHeight     =   6480
   ScaleWidth      =   9660
   Top             =   -15
   Width           =   9780
   Begin VB.Frame frSPlus 
      Caption         =   "SPlus Application"
      Height          =   6255
      Left            =   0
      TabIndex        =   0
      Top             =   0
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
Dim KeyCounter As Long
Dim TreeCollection As New Collection

Private Sub Form_Load()
Move 0, 0, Screen.Width / 2, Screen.Height / 2
Visible = True

SchedulePlus_Init
OutlineSPlusApplication
End Sub

Sub OutlineSPlusApplication()
Dim NewItem As Object
RootKey = "K" & KeyCounter
treSPlus.Nodes.Add , , RootKey, "Application"
TreeCollection.Add Item:=SPlusApplication, Key:=RootKey
KeyCounter = KeyCounter + 1
NewKey = "K" & KeyCounter
treSPlus.Nodes.Add RootKey, tvwChild, NewKey, TypeName(scdSchedule) & ": " & scdSchedule.Name
TreeCollection.Add Item:=scdSchedule, Key:=NewKey
OutlineAddTables treSPlus, scdSchedule, NewKey
End Sub
Sub OutlineAddTables(OTL As Control, ScdItem As Object, ByVal ParentKey$)
'Design Issue: I have tables appearing even if there are no elements in them.
Dim tNode As Object
Screen.MousePointer = 11
If TypeName(ScdItem) = "Schedule" Then
    OutlineShowSchedule OTL, ScdItem, ParentKey$
'-----------------------------------Appointments
    KeyCounter = KeyCounter + 1: NewKey = "K" & KeyCounter
    Set tNode = OTL.Nodes.Add(ParentKey$, tvwChild, NewKey, "SingleAppointments:" & ScdItem.SingleAppointments.Rows & " Records")
    TreeCollection.Add ScdItem.SingleAppointments, NewKey
    tNode.EnsureVisible
    
    KeyCounter = KeyCounter + 1: NewKey = "K" & KeyCounter
     OTL.Nodes.Add ParentKey$, tvwChild, NewKey, "RecurringAppointments:" & ScdItem.RecurringAppointments.Rows & " Records"
    TreeCollection.Add ScdItem.RecurringAppointments, NewKey
    
    KeyCounter = KeyCounter + 1: NewKey = "K" & KeyCounter
    ScdItem.Appointments.SetRange StartDate:=Now - 365, EndDate:=Now + 365
    On Error Resume Next
    cnt% = ScdItem.Appointments.Rows
    On Error GoTo 0
    OTL.Nodes.Add ParentKey$, tvwChild, NewKey, "Appointments:" & cnt% & " Records"
    TreeCollection.Add ScdItem.Appointments, NewKey
'-----------------------------------Tasks
    KeyCounter = KeyCounter + 1: NewKey = "K" & KeyCounter
    OTL.Nodes.Add ParentKey$, tvwChild, NewKey, "SingleTasks:" & ScdItem.SingleTasks.Rows & " Records"
    TreeCollection.Add ScdItem.SingleTasks, NewKey
    
    KeyCounter = KeyCounter + 1: NewKey = "K" & KeyCounter
    OTL.Nodes.Add ParentKey$, tvwChild, NewKey, "RecurringTasks:" & ScdItem.RecurringTasks.Rows & " Records"
    TreeCollection.Add ScdItem.RecurringTasks, NewKey
    
    KeyCounter = KeyCounter + 1: NewKey = "K" & KeyCounter
    ScdItem.Tasks.SetRange StartDate:=Now - 365, EndDate:=Now + 365
    On Error Resume Next
    cnt% = ScdItem.Tasks.Rows
    On Error GoTo 0
    OTL.Nodes.Add ParentKey$, tvwChild, NewKey, "Tasks:" & cnt% & " Records"
    TreeCollection.Add ScdItem.Tasks, NewKey

    
'-----------------------------------Events
    KeyCounter = KeyCounter + 1: NewKey = "K" & KeyCounter
    OTL.Nodes.Add ParentKey$, tvwChild, NewKey, "SingleEvents:" & ScdItem.SingleEvents.Rows & " Records"
    TreeCollection.Add ScdItem.SingleEvents, NewKey
    
    KeyCounter = KeyCounter + 1: NewKey = "K" & KeyCounter
    OTL.Nodes.Add ParentKey$, tvwChild, NewKey, "RecurringEvents:" & ScdItem.RecurringEvents.Rows & " Records"
    TreeCollection.Add ScdItem.RecurringEvents, NewKey
    
    KeyCounter = KeyCounter + 1: NewKey = "K" & KeyCounter
    ScdItem.Events.SetRange StartDate:=Now - 365, EndDate:=Now + 365
    On Error Resume Next
    cnt% = ScdItem.Events.Rows
    On Error GoTo 0
    OTL.Nodes.Add ParentKey$, tvwChild, NewKey, "Events:" & cnt% & " Records"
    TreeCollection.Add ScdItem.Events, NewKey

End If
If TypeName(ScdItem) = "Item" Or TypeName(ScdItem) = "Schedule" Then
    KeyCounter = KeyCounter + 1: NewKey = "K" & KeyCounter
    OTL.Nodes.Add ParentKey$, tvwChild, NewKey, "Roles:" & ScdItem.Roles.Rows & " Records"
    TreeCollection.Add ScdItem.Roles, NewKey
    
    KeyCounter = KeyCounter + 1: NewKey = "K" & KeyCounter
    OTL.Nodes.Add ParentKey$, tvwChild, NewKey, "Contacts:" & ScdItem.Contacts.Rows & " Records"
    TreeCollection.Add ScdItem.Contacts, NewKey
    KeyCounter = KeyCounter + 1: NewKey = "K" & KeyCounter
    OTL.Nodes.Add ParentKey$, tvwChild, NewKey, "Projects:" & ScdItem.Projects.Rows & " Records"
    TreeCollection.Add ScdItem.Projects, NewKey
    
    KeyCounter = KeyCounter + 1: NewKey = "K" & KeyCounter
    OTL.Nodes.Add ParentKey$, tvwChild, NewKey, "AccessControls:" & ScdItem.AccessControls.Rows & " Records"
    TreeCollection.Add ScdItem.AccessControls, NewKey

    KeyCounter = KeyCounter + 1: NewKey = "K" & KeyCounter
    OTL.Nodes.Add ParentKey$, tvwChild, NewKey, "AlarmsToRing:" & ScdItem.AlarmsToRing.Rows & " Records"
    TreeCollection.Add ScdItem.AlarmsToRing, NewKey

    KeyCounter = KeyCounter + 1: NewKey = "K" & KeyCounter
    OTL.Nodes.Add ParentKey$, tvwChild, NewKey, "DeletedItems:" & ScdItem.DeletedItems.Rows & " Records"
    TreeCollection.Add ScdItem.DeletedItems, NewKey

    KeyCounter = KeyCounter + 1: NewKey = "K" & KeyCounter
    OTL.Nodes.Add ParentKey$, tvwChild, NewKey, "Attendees:" & ScdItem.Attendees.Rows & " Records"
    TreeCollection.Add ScdItem.Attendees, NewKey

    KeyCounter = KeyCounter + 1: NewKey = "K" & KeyCounter
    OTL.Nodes.Add ParentKey$, tvwChild, NewKey, "Exceptions:" & ScdItem.Exceptions.Rows & " Records"
    TreeCollection.Add ScdItem.Exceptions, NewKey

End If

Screen.MousePointer = 0
End Sub
Sub OutlineShowItems(OTL As Control, ScdTable As Table, ByVal ParentKey$)
Dim arrData As Variant
Const nFieldNames = 30
Dim FieldNames$(1 To nFieldNames)
If OTL.Nodes(ParentKey$).Children > 0 Then Exit Sub
FieldNames$(1) = "CreatorName"
FieldNames$(2) = "Text"
FieldNames$(3) = "Start"
FieldNames$(4) = "End"
FieldNames$(5) = "AccessActual"
FieldNames$(6) = "ChangeNumber"
FieldNames$(7) = "LastModified"
FieldNames$(8) = "BusyType"
FieldNames$(9) = "AlarmAmountOriginal"
FieldNames$(10) = "AlarmTypeUnitOriginal"
FieldNames$(11) = "AlarmTypeUnit"
FieldNames$(12) = "AlarmAmount"
FieldNames$(13) = "Notify"
FieldNames$(14) = "Ring"
FieldNames$(15) = "Goal"
FieldNames$(16) = "Contacts"
FieldNames$(17) = "AccessControls"
FieldNames$(18) = "AlarmsToRing"
FieldNames$(19) = "SingleAppointments"
FieldNames$(20) = "RecurringAppointments"
FieldNames$(21) = "Appointments"
FieldNames$(22) = "SingleTasks"
FieldNames$(23) = "RecurringTasks"
FieldNames$(24) = "Tasks"
FieldNames$(25) = "SingleEvents"
FieldNames$(26) = "RecurringEvents"
FieldNames$(27) = "Events"
FieldNames$(28) = "DeletedItems"
FieldNames$(29) = "Projects"
FieldNames$(30) = "Goals"



If TypeName(ScdTable) <> "Table" Then Exit Sub
ScdTable.Reset
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
        ItemKey$ = "I" & ParentKey$ & "-" & rp&
        OTL.Nodes.Add ParentKey$, tvwChild, ItemKey$, arrData(r%, 0)
        For c% = LBound(FieldNames) To UBound(FieldNames)
            If Not IsError(arrData(r%, c%)) Then
                OTL.Nodes.Add ItemKey$, tvwChild, , FieldNames$(c%) & ":" & arrData(r%, c%) & "[" & TypeName(arrData(r%, c%)) & "]"
            End If
        Next c%
    Next r%
    On Error GoTo 0
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
Dim nodeObject As Object
If Left(Node.Key, 1) = "K" Then 'we have an object in TreeCollection
        If TypeName(TreeCollection.Item(Node.Key)) = "Table" Then OutlineShowItems treSPlus, TreeCollection.Item(Node.Key), Node.Key
End If
End Sub

Sub OutlineShowSchedule(OTL As Control, ScdItem As Schedule, ByVal ParentKey$)
'This procedure has been setup to show Schedule properties
Dim arrData As Variant
Const nFieldNames = 10
Dim FieldNames$(0 To nFieldNames)
If OTL.Nodes(ParentKey$).Children > 0 Then Exit Sub
FieldNames$(0) = "ScheduleID"
FieldNames$(1) = "DayEndsAt"
FieldNames$(2) = "DayStartsAt"
FieldNames$(3) = "Name"
FieldNames$(4) = "WeekStartOn"
FieldNames$(5) = "UserEntryID"
FieldNames$(6) = "Ranges"
FieldNames$(7) = "DelegateName"
FieldNames$(8) = "SoundDefault"
FieldNames$(9) = "SoundLevel"
' Next field is to demonstrate that data items are NOT returned
'not an Property object
FieldNames$(10) = "Visible" 'This always exists
If TypeName(ScdItem) <> "Item" And TypeName(ScdItem) <> "Schedule" Then Exit Sub
On Error GoTo 0
    arrData = Array(1, nFieldNames)
    'We must put variables in () to get byval passed *** BUG WORKAROUND
    arrData = ScdItem.GetProperties((FieldNames$(0)), _
        (FieldNames$(1)), (FieldNames$(2)), (FieldNames$(3)), _
        (FieldNames$(4)), (FieldNames$(5)), (FieldNames$(6)), _
        (FieldNames$(7)), (FieldNames$(8)), (FieldNames$(9)), _
        (FieldNames$(10)))
'    On Error Resume Next
        For c% = LBound(FieldNames) To UBound(FieldNames)
            If Not IsError(arrData(0, c%)) Then
                OTL.Nodes.Add ParentKey$, tvwChild, , FieldNames$(c%) & ":" & arrData(0, c%) & "[" & TypeName(arrData(0, c%)) & "]"
            End If
        Next c%
    On Error GoTo 0
End Sub


