VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Connect"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Attribute VB_Description = "Expert Agent"
Option Explicit

'---- interface to the VBIDE system

Implements IDTExtensibility

'<Public>-----------------------------------------------
Public FormDisplayed            As Boolean
Public VBInstance               As VBIDE.VBE
Public WithEvents MenuHandler   As CommandBarEvents '---- command bar event handler
Attribute MenuHandler.VB_VarHelpID = -1
'</Public>----------------------------------------------

'<Private>----------------------------------------------
Dim mcbMenuCommandBar           As Office.CommandBarControl
'</Private>---------------------------------------------

Public Sub Hide()
    
    On Error Resume Next
    
    FormDisplayed = False
    frmAddIn.Hide
   
End Sub

Public Sub Show()
  
    On Error Resume Next
    
    '---- set some properties and show it
    With frmAddIn
        Set .VBInstance = VBInstance
        Set .ThisConnection = Me
        .Show
    End With
    
    FormDisplayed = True
   
End Sub

'------------------------------------------------------
' this method adds the Add-In to VB
'------------------------------------------------------
Private Sub IDTExtensibility_OnConnection(ByVal VBInst As Object, ByVal ConnectMode As vbext_ConnectMode, ByVal AddInInst As VBIDE.AddIn, Custom() As Variant)
    
    On Error GoTo error_handler
    
    '---- save the vb instance
    Set VBInstance = VBInst
    
    If ConnectMode = vbext_cm_External Then
        '---- Used by the wizard toolbar to start this wizard
        Me.Show
    Else
        Set mcbMenuCommandBar = AddToAddInCommandBar("Expert Agent")
        '---- sink the event
        Set Me.MenuHandler = VBInst.Events.CommandBarEvents(mcbMenuCommandBar)
    End If
  
    Exit Sub
    
error_handler:
    
    MsgBox Err.Description
    
End Sub

'------------------------------------------------------
' this method removes the Add-In from VB
'------------------------------------------------------
Private Sub IDTExtensibility_OnDisconnection(ByVal RemoveMode As vbext_DisconnectMode, Custom() As Variant)
    
    On Error Resume Next
    
    '---- delete the command bar entry
    mcbMenuCommandBar.Delete
    
    Unload frmAddIn
    Set frmAddIn = Nothing
    Unload frmPatternFinder
    Set frmPatternFinder = Nothing

End Sub

Private Sub IDTExtensibility_OnStartupComplete(Custom() As Variant)
    '<Stub>
End Sub

Private Sub IDTExtensibility_OnAddInsUpdate(Custom() As Variant)
    '<Stub>
End Sub

'------------------------------------------------------
' this event fires when the menu is clicked in the IDE
'------------------------------------------------------
Private Sub MenuHandler_Click(ByVal CommandBarControl As Object, Handled As Boolean, CancelDefault As Boolean)
    Me.Show
End Sub

Function AddToAddInCommandBar(sCaption As String) As Office.CommandBarControl
    Dim cbMenuCommandBar    As Office.CommandBarControl  '---- command bar object
    Dim cbMenu              As Object
  
    On Error GoTo AddToAddInCommandBarErr
    
    '---- see if we can find the Add-Ins menu
    Set cbMenu = VBInstance.CommandBars("Add-Ins")
    If (cbMenu Is Nothing) Then
        '---- not available so we fail
        Exit Function
    End If
    
    '---- add it to the command bar
    Set cbMenuCommandBar = cbMenu.Controls.Add(1)
    
    '---- set the caption
    cbMenuCommandBar.Caption = sCaption
    
    Set AddToAddInCommandBar = cbMenuCommandBar
    
    Exit Function
    
AddToAddInCommandBarErr:

End Function


