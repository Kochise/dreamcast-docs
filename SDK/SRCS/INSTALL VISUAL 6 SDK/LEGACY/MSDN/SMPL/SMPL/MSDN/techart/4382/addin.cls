VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "AddIn"
Attribute VB_Creatable = True
Attribute VB_Exposed = True
Option Explicit
'IMPORTANT: Instancing must be Multiuse
'REFERENCES: Visual Basic Development Environment must be [X]
Private ThisInstance As VBIDE.Application 'One PER VBIDE!
'OBJECT is SLOWER
Dim MenuItems() As String, hMenuLine() As Long
Dim AddinMenuLine() As VBIDE.MenuLine
Private Sub Initialize()
MsgBox "Initialize is NEVER called in an Addin"
End Sub
Public Sub ConnectAddIn(VBInstance As Object)
    Set ThisInstance = VBInstance
    'Menu Items
    AddMenu
    ShowProjectFiles frmAddInMgr.Filelist
    frmAddInMgr.Visible = True
End Sub
Public Sub DisconnectAddIn(mode As Integer)
Dim i%
For i% = LBound(MenuItems) To UBound(MenuItems)
    If hMenuLine(i%) <> 0 Then 'ROBUSTNESS CODE
        AddinMenuLine(i%).DisconnectEvents hMenuLine(i%)
    End If
    ThisInstance.AddInMenu.MenuItems.Remove AddinMenuLine(i%)
Next i%
Unload frmAddInMgr
End Sub
Private Sub AddMenu()
Const MenuItem_Count = 2 'CHANGE ME
ReDim MenuItems(1 To MenuItem_Count)
ReDim hMenuLine(1 To MenuItem_Count)
ReDim AddinMenuLine(1 To MenuItem_Count)
Dim i%
MenuItems(1) = "Addin AA"
MenuItems(2) = "Addin B"
For i% = LBound(MenuItems) To UBound(MenuItems)
    If Len(MenuItems(i%)) > 0 Then
       Set AddinMenuLine(i%) = ThisInstance.AddInMenu.MenuItems.Add(MenuItems(i%))
       'WARNING: with  'AddinMenuLine(i%).ConnectEvents Me' menu item CANNOT be Removed.
       hMenuLine(i%) = AddinMenuLine(i%).ConnectEvents(Me)
    End If
Next i%
End Sub
Public Sub AfterClick()
MsgBox "Not Implemented"
    ShowProjectFiles frmAddInMgr.Filelist
End Sub
Private Sub ShowProjectFiles(ctlListBox As Control)
Dim i%
Dim Prj As ProjectTemplate, Cmp As Component
Set Prj = ThisInstance.ActiveProject
ctlListBox.Clear
For i% = 0 To Prj.Components.Count - 1
    ctlListBox.AddItem Prj.Components(i%).Name
    Set Cmp = Prj.Components(i%)
    Debug.Print Cmp.Name
Next i%
Dim O As Object

End Sub




