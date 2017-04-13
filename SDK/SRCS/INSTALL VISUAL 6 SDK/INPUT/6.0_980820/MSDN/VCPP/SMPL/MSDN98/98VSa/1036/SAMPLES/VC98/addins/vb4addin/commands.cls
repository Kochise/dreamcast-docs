VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Commands"
Attribute VB_Creatable = False
Attribute VB_Exposed = True
Public m_app As Application

Public Sub Vb4AddInCommand()
    m_app.EnableModeless False
    MsgBox "Vb4AddInCommand called!"
    m_app.EnableModeless True

    ' TODO: In this and all other commands you may manipulate the Developer
    '  Studio objects, by starting with the Application object, stored
    '  in m_app.

End Sub

