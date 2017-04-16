VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CTDetOSP"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Private m_oAdmin As HDClient.CAdmin
Private m_oReq As HDClient.CRequest
' columns in m_reqArray
Private Enum ArrayCols
    PKId = 1
    DetDate = 2
    DetTypeId = 3
    DetailText = 4
End Enum
' m_reqArrayColumns
Private Const icArrayColumns = 5
' notification object provided by client
Private myEvent As OLEDBSimpleProviderListener
' data array
Private m_reqArray() As Variant

Implements OLEDBSimpleProvider

Friend Sub InitForReqId(ByVal lReqId As Long)
' Initialize m_reqArray

' This implementation allows the sample to run with reduced functionality without the other Helpdesk components
'InitWithDummyData (lReqId)

' This implementation uses Helpdesk API components and database
InitWithHelpdeskData (lReqId)

End Sub
Private Sub Class_Initialize()
Set m_oAdmin = New HDClient.CAdmin
' Initialize m_reqArray

' This implementation allows the sample to run with reduced functionality without the other Helpdesk components
'InitWithDummyData (0)

' This implementation uses Helpdesk API components and database
InitWithHelpdeskData (0)
End Sub

Private Sub Class_Terminate()
    Set m_oAdmin = Nothing
    Set myEvent = Nothing
End Sub
Function OLEDBSimpleProvider_getRowCount() As Long
    OLEDBSimpleProvider_getRowCount = UBound(m_reqArray, 1)
End Function
Function OLEDBSimpleProvider_getColumnCount() As Long
    OLEDBSimpleProvider_getColumnCount = UBound(m_reqArray, 2)
End Function
Function OLEDBSimpleProvider_getRWStatus(ByVal lRow As Long, ByVal lColumn As Long) As OSPRW
' All columns are read-write
    OLEDBSimpleProvider_getRWStatus = OSPRW.OSPRW_READWRITE
End Function
Sub OLEDBSimpleProvider_setVariant(ByVal lRow As Long, ByVal lColumn As Long, ByVal format As OSPFORMAT, ByVal vNewVal As Variant)
' update an element in the array

' reject out of bounds attempts
If lRow < 0 And lColumn < 0 And lRow > UBound(m_reqArray, 1) And lColumn > UBound(m_reqArray, 2) Then
    Exit Sub
End If

' general case update the array
Call myEvent.aboutToChangeCell(lRow, lColumn)
m_reqArray(lRow, lColumn) = vNewVal
Call myEvent.cellChanged(lRow, lColumn)

End Sub
Function OLEDBSimpleProvider_getVariant(ByVal lRow As Long, ByVal lColumn As Long, ByVal dataformat As OSPFORMAT) As Variant

' reject out of bounds requests
If lRow < 0 And lColumn < 0 And lRow > UBound(m_reqArray, 1) And lColumn > UBound(m_reqArray, 2) Then
    Exit Function
End If

' format and return data
Select Case dataformat
    Case OSPFORMAT.OSPFORMAT_RAW, OSPFORMAT.OSPFORMAT_DEFAULT:
        OLEDBSimpleProvider_getVariant = m_reqArray(lRow, lColumn)
    Case OSPFORMAT.OSPFORMAT_FORMATTED:
        OLEDBSimpleProvider_getVariant = format(m_reqArray(lRow, lColumn))
    Case OSPFORMAT.OSPFORMAT_HTML:
        OLEDBSimpleProvider_getVariant = m_reqArray(lRow, lColumn)
    Case Else
        OLEDBSimpleProvider_getVariant = m_reqArray(lRow, lColumn)
End Select

End Function
Function OLEDBSimpleProvider_find(ByVal lRowStart As Long, ByVal lColumn As Long, ByVal vVal As Variant, _
                                 ByVal findFlags As OSPFIND, ByVal compType As OSPCOMP) As Long
' not supported
OLEDBSimpleProvider_find = 0
End Function
Function OLEDBSimpleProvider_insertRows(ByVal lRow As Long, ByVal cRows As Long) As Long
' not supported
OLEDBSimpleProvider_insertRows = 0
End Function
Function OLEDBSimpleProvider_deleteRows(ByVal lRow As Long, ByVal cRows As Long) As Long
' not supported
OLEDBSimpleProvider_deleteRows = 0
End Function
Function OLEDBSimpleProvider_getLocale() As String
OLEDBSimpleProvider_getLocale = ""
End Function
Sub OLEDBSimpleProvider_addOLEDBSimpleProviderListener(ByVal istdeEvent As OLEDBSimpleProviderListener)
' set client notification object
If Not myEvent Is Nothing Then
    Set myEvent = Nothing
End If
Set myEvent = istdeEvent
End Sub
Sub OLEDBSimpleProvider_removeOLEDBSimpleProviderListener(ByVal istdeEvent As OLEDBSimpleProviderListener)
' release client notification object
Set myEvent = Nothing
End Sub
Function OLEDBSimpleProvider_isAsync() As Long
' this is a synchronous provider
OLEDBSimpleProvider_isAsync = 0
End Function
Function OLEDBSimpleProvider_getEstimatedRows() As Long
OLEDBSimpleProvider_getEstimatedRows = -1
End Function
Sub OLEDBSimpleProvider_stopTransfer()
End Sub
Private Sub InitWithHelpdeskData(ByVal lReqId As Long)
' Populate m_reqArray with dummy data
Dim oReqDet As HDClient.CReqDetail
Dim lRow As Long
Dim lRows As Long

If lReqId > 0 Then
    Set m_oReq = New HDClient.CRequest
    m_oReq.PKId = lReqId
    lRows = m_oReq.Details.Count
    Call myEvent.aboutToInsertRows(1, lRows)
' initialize the array
    ReDim m_reqArray(lRows, icArrayColumns) As Variant
Else
' initialize the array
    ReDim m_reqArray(0, icArrayColumns) As Variant
End If

' Supply column names
lRow = 0
m_reqArray(lRow, ArrayCols.PKId) = "PKid"
m_reqArray(lRow, ArrayCols.DetDate) = "Date"
m_reqArray(lRow, ArrayCols.DetTypeId) = "Type"
m_reqArray(lRow, ArrayCols.DetailText) = "MsgText"
    
If lRows > 0 Then
    For lRow = 1 To lRows
        Set oReqDet = m_oReq.Details(lRow)
        m_reqArray(lRow, ArrayCols.PKId) = CStr(oReqDet.PKIdEx)
        m_reqArray(lRow, ArrayCols.DetDate) = oReqDet.DetDate
        m_reqArray(lRow, ArrayCols.DetTypeId) = CStr(oReqDet.DetTypeId)
        m_reqArray(lRow, ArrayCols.DetailText) = oReqDet.DetailText
    Next
    Call myEvent.insertedRows(1, lRows)
    Set oReqDet = Nothing
End If
End Sub
Private Sub InitWithDummyData(ByVal lReqId As Long)
' Populate m_reqArray with dummy data
Dim lRow As Long
Dim lRows As Long

lRows = 0
If lReqId > 0 Then
    lRows = 5
    Call myEvent.aboutToInsertRows(1, lRows)
' initialize the array
    ReDim m_reqArray(lRows, icArrayColumns) As Variant
Else
' initialize the array
    ReDim m_reqArray(0, icArrayColumns) As Variant
End If

' Supply column names
lRow = 0
m_reqArray(lRow, ArrayCols.PKId) = "PKid"
m_reqArray(lRow, ArrayCols.DetDate) = "Date"
m_reqArray(lRow, ArrayCols.DetTypeId) = "Type"
m_reqArray(lRow, ArrayCols.DetailText) = "MsgText"
    
If lRows > 0 Then
    For lRow = 1 To lRows
        m_reqArray(lRow, ArrayCols.PKId) = CStr(lRow)
        m_reqArray(lRow, ArrayCols.DetDate) = CDate("11/6/97")
        m_reqArray(lRow, ArrayCols.DetTypeId) = "Type"
        m_reqArray(lRow, ArrayCols.DetailText) = "ppp" & lRow
    Next
    Call myEvent.insertedRows(1, 5)
End If

End Sub
