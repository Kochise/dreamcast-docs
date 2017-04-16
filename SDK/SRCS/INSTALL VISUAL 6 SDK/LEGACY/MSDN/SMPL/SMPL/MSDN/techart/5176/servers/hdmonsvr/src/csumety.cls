VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CSumEntity"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True

Private m_Key As String
Private m_Count

Public Property Get Key() As String
Key = m_Key
End Property

Public Property Let Key(ByVal sNewValue As String)
m_Key = sNewValue
End Property

Public Property Get Count() As Long
Count = m_Count
End Property

Public Property Let Count(ByVal lNewValue As Long)
m_Count = lNewValue
End Property
