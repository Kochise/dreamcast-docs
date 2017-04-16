VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Server"
Attribute VB_Creatable = True
Attribute VB_Exposed = True
Option Explicit

Public Function Connect(oNotify As Object)
    Dim vResult As Variant

 'This function collects the client notification
 'object into an array, then uses the RefreshClient
 'function to send updates on all the room objects
 'to the connected client....
 
    If gnActiveClients >= MAX_CLIENTS Then
        Connect = False
        Exit Function
    End If
    
    Set gCliList(gnActiveClients) = oNotify
    gnActiveClients = gnActiveClients + 1
    RoomSvr.lblActiveClients.Caption = gnActiveClients
    vResult = RefreshClient(oNotify)
    Connect = True
    
End Function

Public Function Disconnect(oNotify As Object)
    Dim nCnt, nItem As Integer
    Dim oTest As Object

 'determine the ordinal value of the specified client
    For nCnt = 0 To gnActiveClients - 1
        Set oTest = gCliList(nCnt)
        If gCliList(nCnt) Is oNotify Then
            nItem = nCnt
            Exit For
        End If
    Next nCnt
    

 'shift the objects down in the client array of objects
    For nCnt = nItem To gnActiveClients - 2 'ensure you don't exceed array size
        Set gCliList(nCnt) = gCliList(nCnt + 1)
    Next nCnt
    
    gnActiveClients = gnActiveClients - 1
    RoomSvr.lblActiveClients.Caption = gnActiveClients
    
    Disconnect = True
    
    
End Function

Public Function GetTotalRooms() As Variant
    GetTotalRooms = gnNumRooms

End Function


Public Sub RefreshAll()
    Dim vResult As Variant
    Dim nCnt As Integer
    
    For nCnt = 0 To gnActiveClients - 1
        vResult = RefreshClient(gCliList(nCnt))
    Next nCnt
    
End Sub

Public Function RefreshClient(objClient As Object)
    Dim vResult As Variant
    Dim nCnt As Integer
    
    For nCnt = 0 To gnNumRooms - 1
        vResult = gRoomList(nCnt).RefreshClient(objClient)
    Next nCnt

    RefreshClient = True

End Function

Public Function Rooms(nItem As Integer) As Object
    Set Rooms = gRoomList(nItem)
    
End Function

Public Function RefreshClientItem(oRoom As Object)
    Dim vResult As Variant
    Dim nCnt As Integer

    For nCnt = 0 To gnActiveClients - 1
        vResult = oRoom.RefreshClient(gCliList(nCnt))
    Next nCnt

End Function
