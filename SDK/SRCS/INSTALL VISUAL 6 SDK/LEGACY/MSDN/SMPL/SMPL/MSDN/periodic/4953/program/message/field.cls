VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Field"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

'External handles
Public Filters As Filters

'Internal variables
Private sName As String
Private bAString As Boolean
Private sDescription As String
Private bRequired As Boolean
Private iSize As Integer
Private vValue As Variant
Private sSelectedFilter As String

Private Sub Class_Initialize()

    Set Filters = New Filters
    
End Sub
Public Property Get AString() As Boolean
'AString because String is a reserved word.

    AString = bAString
    
End Property

Public Property Let AString(bNewValue As Boolean)

    bAString = bNewValue
    
End Property

Public Property Get Description() As String

    Description = sDescription
    
End Property

Public Property Let Description(sNewValue As String)

    sDescription = sNewValue
    
End Property

Public Property Get Required() As Boolean

    Required = bRequired
    
End Property

Public Property Let Required(bNewValue As Boolean)

    bRequired = bNewValue
    
End Property

Public Property Get Size() As Integer

    Size = iSize
    
End Property

Public Property Let Size(iNewValue As Integer)

    iSize = iNewValue
    
End Property

Public Property Get Value() As Variant

    Value = vValue

End Property

Public Property Let Value(vNewValue As Variant)

    vValue = vNewValue

End Property

Public Property Get SelectedFilter() As String

    SelectedFilter = sSelectedFilter
    
End Property

Public Property Let SelectedFilter(sNewValue As String)

    sSelectedFilter = sNewValue
    
End Property

Public Property Get Name() As String

    Name = sName
    
End Property

Public Property Let Name(sNewValue As String)

    sName = sNewValue
    
End Property

