VERSION 1.0 CLASS
BEGIN
  MultiUse = 0   'False
END
Attribute VB_Name = "Notify"
Attribute VB_Creatable = True
Attribute VB_Exposed = True
Option Explicit


Public Sub AlertMessage(szMessage As String)
 'NOTE:  This is an example of an innappropriate way to handle
 ' errors when dealing with callbacks from an OLE server.
 ' If there is more than one client application
 ' connected to the server, the other clients
 ' will be blocked until
 ' the message box is OK'd by the client that
 ' received this function callback.
 ' A better implementation would be to use this
 ' function to set a LastError variable and return
 ' immediately.  Then upon receiving an error
 ' result from the server, the client could simply
 ' expose the last error using it's own call to
 ' the msgbox function without blocking any other
 ' clients.....
 
    MsgBox szMessage
    
End Sub

Public Sub ShutDown(nSeconds As Variant)
    Register.Timer1.Interval = nSeconds * 1000
    Register.Timer1.Enabled = True
End Sub

Public Function Refresh(vTypeUpdate As Variant, vValues As Variant)

    Register.lblError = ""
    
    Select Case vTypeUpdate
        Case 0 ' error case
            gszLastError = vValues
        Case 1 ' update room
            With Register
                .grdRooms.Col = 0
                .grdRooms.Row = vValues(0)
                .grdRooms.TEXT = vValues(1)
                .grdRooms.Col = 1
                .grdRooms.TEXT = vValues(2)
                .grdRooms.Col = 2
                .grdRooms.TEXT = vValues(3)
            End With
        Refresh = 0
    End Select
    

End Function
