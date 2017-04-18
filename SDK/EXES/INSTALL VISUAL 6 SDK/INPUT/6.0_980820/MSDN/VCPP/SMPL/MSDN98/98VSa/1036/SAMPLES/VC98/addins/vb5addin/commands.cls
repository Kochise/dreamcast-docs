VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Commands"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Public WithEvents m_app As Application
Attribute m_app.VB_VarHelpID = -1
Public WithEvents m_debugger As Debugger
Attribute m_debugger.VB_VarHelpID = -1

Option Explicit

Public Sub Vb5AddInCommand()
    
    m_app.EnableModeless False
    MsgBox "Vb5AddInCommand called!"
    m_app.EnableModeless True

    ' TODO: In this and all other commands you may manipulate the Developer
    '  Studio objects, by starting with the Application object, stored
    '  in m_app.

End Sub

Private Sub m_app_BeforeApplicationShutDown()
    m_app.PrintToOutputWindow "VB5AddIn received BeforeApplicationShutDown event"
End Sub

Private Sub m_app_BeforeBuildStart()
    m_app.PrintToOutputWindow "VB5AddIn received BeforeBuildStart event"
End Sub

Private Sub m_app_BeforeDocumentClose(ByVal theDocument As Object)
    m_app.PrintToOutputWindow "VB5AddIn received BeforeDocumentClose(" & theDocument & ") event"

End Sub

Private Sub m_app_BuildFinish(ByVal nNumErrors As Long, ByVal nNumWarnings As Long)
    m_app.PrintToOutputWindow "VB5AddIn received BuildFinish(" & nNumErrors & ", " & nNumWarnings & ") event"

End Sub

Private Sub m_app_DocumentOpen(ByVal theDocument As Object)
    m_app.PrintToOutputWindow "VB5AddIn received DocumentOpen(" & theDocument & ") event"

End Sub

Private Sub m_app_DocumentSave(ByVal theDocument As Object)
    m_app.PrintToOutputWindow "VB5AddIn received DocumentSave(" & theDocument & ") event"

End Sub

Private Sub m_app_NewDocument(ByVal theDocument As Object)
    m_app.PrintToOutputWindow "VB5AddIn received NewDocument(" & theDocument & ") event"
End Sub

Private Sub m_app_NewWorkspace()
    m_app.PrintToOutputWindow "VB5AddIn received NewWorkspace event"
End Sub

Private Sub m_app_WindowActivate(ByVal theWindow As Object)
    m_app.PrintToOutputWindow "VB5AddIn received WindowActivate(" & theWindow & ") event"
End Sub

Private Sub m_app_WindowDeactivate(ByVal theWindow As Object)
    m_app.PrintToOutputWindow "VB5AddIn received WindowDeactivate(" & theWindow & ") event"
End Sub

Private Sub m_app_WorkspaceClose()
    m_app.PrintToOutputWindow "VB5AddIn received WorkspaceClose event"
End Sub

Private Sub m_app_WorkspaceOpen()
    m_app.PrintToOutputWindow "VB5AddIn received WorkspaceOpen event"
End Sub

Private Sub m_debugger_BreakpointHit(ByVal pBreakpoint As Object)
    m_app.PrintToOutputWindow "VB5AddIn received BreakpointHit event"
End Sub
