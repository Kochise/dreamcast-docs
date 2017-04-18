VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "DSAddIn"
Attribute VB_Creatable = True
Attribute VB_Exposed = True
Attribute VB_Description = "VB4-authored Add-in"
Option Explicit
Dim m_cookie As Integer
Dim m_Commands As Commands

Public Property Get Description()
Attribute Description.VB_Description = "Illustrates a Developer Studio Add-in written with VB4"
    ' TODO: Enter the description for this object in the Object Browser
    '       (In the object browser, click this property and click Options...)
    '       The actual value of the Description property is unimportant.
    Description = ""
End Property
Public Function OnConnection(ByVal pApp As Object, ByVal bFirstTime As Boolean, ByVal dwCookie As Long) As Boolean
Attribute OnConnection.VB_Description = "OnConnection description"


    Set m_Commands = New Commands
    
    ' This stores the application object in m_Commands.  Since m_app
    '  is statically typed to be Application, all method and property
    '  accesses through it will use the dual interface of the
    '  Developer Studio Application object
    Set m_Commands.m_app = pApp
    
    m_cookie = dwCookie
    
    Dim instance As Long
    instance = App.hInstance
    m_Commands.m_app.SetAddInInfo instance, m_Commands, 1, 2, dwCookie
    
    ' For each command in m_Commands class module, we add a command
    '  to the DevStudio shell.  You may add new commands to m_Commands
    '  by adding new public subs (make sure they return nothing and
    '  take nothing as args), and then add them to the Developer Studio
    '  commands by adding a corresponding call below.
    ' The first argument is: CommandName (no spaces) & menu text &
    '  status bar prompt & tooltip.  Then are the implementation method
    '  name, toolbar button bitmap offset, and cookie.
    m_Commands.m_app.AddCommand "Vb4AddInCommand" & Chr(10) _
        & "Vb4AddIn Sample Command" & Chr(10) _
        & "Displays a message box" & Chr(10) _
        & "Vb4AddIn Command", _
        "Vb4AddInCommand", 0, dwCookie
    
    ' Add toolbar buttons only if this is the first time the add-in
    '  is being loaded.  Toolbar buttons are automatically remembered
    '  by Developer Studio from session to session, so we should only
    '  add the toolbar buttons once.
    If bFirstTime = True Then
        m_Commands.m_app.AddCommandBarButton dsGlyph, "Vb4AddInCommand", dwCookie
    End If
        
    OnConnection = True
End Function
Public Sub OnDisconnection(bLastTime As Boolean)
    Set m_Commands.m_app = Nothing
    Set m_Commands = Nothing
End Sub

