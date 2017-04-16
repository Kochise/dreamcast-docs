VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "clsRequirements"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

'Internal property values
Private sReportName As String
Private sRequirementCaption As String
Private sRequirementValue As String
Private sReportObjectName As String
Public Property Get ReportName()

    ReportName = sReportName

End Property

Public Property Let ReportName(vNewValue As Variant)

    'Only let it be set once
    If sReportName <> "" Then Exit Property
    
    sReportName = vNewValue

End Property


Public Property Get ReportObjectName()

    ReportObjectName = sReportObjectName

End Property

Public Property Let ReportObjectName(vNewValue As Variant)

    'Only let it be set once
    If sReportObjectName <> "" Then Exit Property
    
    sReportObjectName = vNewValue

End Property


Public Property Get Caption()

    Caption = sRequirementCaption

End Property

Public Property Let Caption(vNewValue)

    sRequirementCaption = vNewValue

End Property

Public Property Get Value()

    Value = sRequirementValue
    
End Property

Public Property Let Value(vNewValue)

    sRequirementValue = vNewValue
    
End Property
