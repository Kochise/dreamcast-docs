VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Fields"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

'Internal variables
Private coFields As Collection
Public Sub Create(sKey As String)

    'Make the name the same as the key
    Dim cField As New Field
    cField.Name = sKey

    coFields.Add Item:=cField, Key:=sKey

End Sub
Public Function Item(vKey As Variant)

    Set Item = coFields.Item(vKey)
    
End Function
Public Function Count() As Integer
    
    Count = coFields.Count
    
End Function
Private Sub Class_Initialize()

    Set coFields = New Collection
    
End Sub
