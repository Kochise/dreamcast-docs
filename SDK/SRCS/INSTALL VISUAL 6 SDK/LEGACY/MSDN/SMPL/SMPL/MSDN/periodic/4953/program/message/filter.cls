VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Filter"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
'This class contains information on the filter
'   type in question
'Later a rule property can be added that will
'   be used to more precisely validate data entry
Option Explicit

'Internal variables
Private sName As String
Private sDescription As String
Public Property Get Name() As String

    Name = sName
    
End Property

Public Property Let Name(sNewValue As String)

    sName = sNewValue
    
End Property

Public Property Get Description() As String

    Description = sDescription
    
End Property

Public Property Let Description(sNewValue As String)

    sDescription = sNewValue
    
End Property

