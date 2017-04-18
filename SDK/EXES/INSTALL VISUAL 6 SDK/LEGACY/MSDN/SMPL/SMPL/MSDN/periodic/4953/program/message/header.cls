VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Header"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

'External Handles
Private sReportID As String
Private sReportName As String
Public Property Get ReportID() As String
    
    ReportID = sReportID
    
End Property

Public Property Let ReportID(sNewValue As String)

    sReportID = sNewValue
    
End Property
Public Property Get ReportName() As String

    ReportName = sReportName
    
End Property

Public Property Let ReportName(sNewValue As String)

    sReportName = sNewValue
    
End Property
