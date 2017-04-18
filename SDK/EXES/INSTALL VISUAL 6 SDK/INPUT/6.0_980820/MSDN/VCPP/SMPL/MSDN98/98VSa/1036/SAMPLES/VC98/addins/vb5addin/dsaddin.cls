VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "DSAddIn"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Attribute VB_Description = "VB5-authored Add-in"
Option Explicit

Dim m_cookie As Integer
Dim m_Commands As Commands

Implements IDSAddIn
Public Property Get Description()
Attribute Description.VB_Description = "Illustrates a Developer Studio Add-in written with VB5"
    ' TODO: Enter the description for this object in the Object Browser
    '       (In the object browser, right-click this property and choose Properties)
    '       The actual value of the Description property is unimportant.
    Description = ""
End Property

Private Function IDSAddIn_OnConnection(ByVal pApp As DSSharedObjects.IApplication, ByVal bFirstTime As Boolean, ByVal dwCookie As Long) As Boolean

    Set m_Commands = New Commands
    
    ' This stores the application & debugger objects in m_Commands.  Since
    '  m_app & m_debugger are statically typed to be Application and Debugger, all
    '  method and property accesses through them will use the dual interfaces of the
    '  Developer Studio Application and Debugger objects
    ' Since m_app & m_debugger are also declared "WithEvents", these assignments will
    '  cause any event handlers in m_Commands to be connected to
    '  the Developer Studio Application and Debugger events.
    Set m_Commands.m_app = pApp
    Set m_Commands.m_debugger = pApp.Debugger
    
    m_cookie = dwCookie
    
    Dim instance As Long
    instance = App.hInstance
    m_Commands.m_app.SetAddInInfo instance, m_Commands, 1, 2, dwCookie
    
    ' For each command in m_Commands class module, we add a command
    '  to the DevStudio shell.  You may add new commands to m_Commands
    '  by adding new public subs (make sure they have no return values and
    '  or arguments), and then add them to the Developer Studio
    '  commands by adding a corresponding call below.
    ' The first argument is: CommandName (no spaces) & menu text &
    '  status bar prompt & tooltip.  Then are the implementation method
    '  name, toolbar button bitmap offset, and cookie.
    m_Commands.m_app.AddCommand "Vb5AddInCommand" & Chr(10) _
        & "Vb5AddIn Sample Command" & Chr(10) _
        & "Displays a message box" & Chr(10) _
        & "Vb5AddIn Command", _
        "Vb5AddInCommand", 0, dwCookie
        
    ' Add toolbar buttons only if this is the first time the add-in
    '  is being loaded.  Toolbar buttons are automatically remembered
    '  by Developer Studio from session to session, so we should only
    '  add the toolbar buttons once.
    If bFirstTime = True Then
        m_Commands.m_app.AddCommandBarButton dsGlyph, "Vb5AddInCommand", dwCookie
    End If
        
    IDSAddIn_OnConnection = True
End Function

Private Sub IDSAddIn_OnDisconnection(ByVal bLastTime As Boolean)
    Set m_Commands.m_app = Nothing
    Set m_Commands.m_debugger = Nothing
    Set m_Commands = Nothing
End Sub


