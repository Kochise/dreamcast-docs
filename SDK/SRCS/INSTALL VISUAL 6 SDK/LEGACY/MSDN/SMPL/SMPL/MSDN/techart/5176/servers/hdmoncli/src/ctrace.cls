VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CTrace"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Private m_SGObject As Object
Private m_ColorBehavior As Object
Private m_Level
Private m_Description
Private m_Highlighted
Private m_ColorRed
Private m_ColorGreen
Private m_ColorBlue
Private m_LineWidth

Public Property Get SGObject() As Object
Set SGObject = m_SGObject
End Property

Public Property Set SGObject(ByVal oNewObject As Object)
Set m_SGObject = oNewObject
End Property

Public Property Get ColorBehavior() As Object
Set ColorBehavior = m_ColorBehavior
End Property

Public Property Set ColorBehavior(ByVal oNewObject As Object)
Set m_ColorBehavior = oNewObject
End Property

Public Property Get level() As Variant
level = m_Level
End Property

Public Property Let level(ByVal vNewValue As Variant)
m_Level = vNewValue
End Property

Public Property Get Description() As Variant
Description = m_Description
End Property

Public Property Let Description(ByVal vNewValue As Variant)
m_Description = vNewValue
End Property

Public Property Get Red() As Variant
Red = m_ColorRed
End Property

Public Property Let Red(ByVal vNewValue As Variant)
m_ColorRed = vNewValue
End Property

Public Property Get Green() As Variant
Green = m_ColorGreen
End Property

Public Property Let Green(ByVal vNewValue As Variant)
m_ColorGreen = vNewValue
End Property

Public Property Get Blue() As Variant
Blue = m_ColorBlue
End Property

Public Property Let Blue(ByVal vNewValue As Variant)
m_ColorBlue = vNewValue
End Property

Public Property Get LineWidth() As Variant
LineWidth = m_LineWidth
End Property

Public Property Let LineWidth(ByVal vNewValue As Variant)
m_LineWidth = vNewValue
End Property

