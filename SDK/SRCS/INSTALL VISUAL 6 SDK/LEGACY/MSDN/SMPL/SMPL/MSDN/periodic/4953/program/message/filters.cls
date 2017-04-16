VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Filters"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

'Internal variables
Private coFilters As Collection
Public Sub Create(sKey As String)

    'Make the Name the same as the key
    Dim cFilter As New Filter
    cFilter.Name = sKey

    coFilters.Add Item:=cFilter, Key:=sKey

End Sub
Public Function Item(vKey As Variant)

    Set Item = coFilters.Item(vKey)
    
End Function
Public Function Count() As Integer
    
    Count = coFilters.Count
    
End Function

Private Sub Class_Initialize()

    Set coFilters = New Collection
    
End Sub

