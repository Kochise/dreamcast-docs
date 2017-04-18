VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CMReqOSP"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Private m_oAdmin As HDClient.CAdmin
Private m_oTech As HDClient.CTech

' state of description field
Private Enum DescState
    Collapsed = 0
    Expanded = 1
End Enum
Private Enum RowMethod
    icToggle = 0
    icExpand = 1
End Enum
' columns in m_reqArray
Private Enum ArrayCols
    PKId = 1
    Priority = 2
    Status = 3
    RequestDate = 4
    Description = 5
    Description_State = 6
    Description_Dat = 7
End Enum
' m_reqArrayColumns
Private Const icArrayColumns = 8
' notification object provided by client
Private myEvent As OLEDBSimpleProviderListener
' data array
Private m_reqArray() As Variant

Implements OLEDBSimpleProvider

Friend Function Admin() As HDClient.CAdmin
    Set Admin = m_oAdmin
End Function
Friend Function Tech() As HDClient.CTech
    Set Tech = m_oTech
End Function
Friend Sub ExpandDetail(ByVal lPKId As Long, ByVal sUIFile As String)
Dim lRow As Long
For lRow = LBound(m_reqArray) + 1 To UBound(m_reqArray)
    If m_reqArray(lRow, ArrayCols.PKId) = lPKId Then
        Call myEvent.aboutToChangeCell(lRow, ArrayCols.Description)
        GenDetail lRow, icExpand, sUIFile
        Call myEvent.cellChanged(lRow, ArrayCols.Description)
        Exit For
    End If
Next
End Sub
Friend Sub RefreshRequest(ByVal lPKId As Long)
Dim lRow As Long
For lRow = LBound(m_reqArray) + 1 To UBound(m_reqArray)
    If m_reqArray(lRow, ArrayCols.PKId) = lPKId Then
        RefreshRow lRow
        Exit For
    End If
Next
End Sub
Friend Sub ToggleDetail(ByVal lPKId As Long, ByVal sUIFile As String)
Dim lRow As Long
For lRow = LBound(m_reqArray) + 1 To UBound(m_reqArray)
    If m_reqArray(lRow, ArrayCols.PKId) = lPKId Then
        Call myEvent.aboutToChangeCell(lRow, ArrayCols.Description)
        GenDetail lRow, icToggle, sUIFile
        Call myEvent.cellChanged(lRow, ArrayCols.Description)
        Exit For
    End If
Next
End Sub
Private Sub Class_Initialize()
Set m_oAdmin = New HDClient.CAdmin

' Initialize m_reqArray
' This implementation allows the sample to run with reduced functionality without the other Helpdesk components
'InitWithDummyData
' This implementation uses Helpdesk API components and database
InitWithHelpdeskData
End Sub
Private Sub Class_Terminate()
    Set m_oTech = Nothing
    Set m_oAdmin = Nothing
    Set myEvent = Nothing
End Sub
Private Sub GenDetail(ByVal lRow As Long, ByVal iMethod As RowMethod, ByVal UIFile As String)
' Generates contents of description column
Dim sHTML
If (iMethod = icExpand) Or (m_reqArray(lRow, ArrayCols.Description_State) = DescState.Collapsed) Then
' put html for detail interface in description column
    sHTML = sHTML & "<object height=200 width=100%  "
    sHTML = sHTML & "type=""text/x-scriptlet"" data=""" & UIFile & """ >"
    sHTML = sHTML & "</object>"
    m_reqArray(lRow, ArrayCols.Description) = sHTML
    m_reqArray(lRow, ArrayCols.Description_State) = DescState.Expanded
Else
' put only request description in description column
    m_reqArray(lRow, ArrayCols.Description) = m_reqArray(lRow, ArrayCols.Description_Dat)
    m_reqArray(lRow, ArrayCols.Description_State) = DescState.Collapsed
End If
End Sub
Private Sub RefreshRow(ByVal lRow As Long)
' Refresh contents of Row
Dim oReq As New HDClient.CRequest
'Get request object for row
oReq.PKId = m_reqArray(lRow, ArrayCols.PKId)

Call myEvent.aboutToChangeCell(lRow, ArrayCols.Status)
m_reqArray(lRow, ArrayCols.Status) _
    = m_oAdmin.GetReqStatus(m_oAdmin.Format_ItemPKId(oReq.StatusId)).Code
Call myEvent.cellChanged(lRow, ArrayCols.Status)

Call myEvent.aboutToChangeCell(lRow, ArrayCols.Description)
If m_reqArray(lRow, ArrayCols.Description_State) = DescState.Collapsed Then
    m_reqArray(lRow, ArrayCols.Description) = oReq.Desc
End If
Call myEvent.cellChanged(lRow, ArrayCols.Description)

' Clean up
Set oReq = Nothing

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
Private Sub InitWithHelpdeskData()
Dim oReq As HDClient.CRequest
Dim sUser As String
Dim lRow As Long

' initialize the array
 ReDim m_reqArray(0, icArrayColumns)
' get user log in name
sUser = sGetUserName
' populate a HelpDesk technician object
Set m_oTech = m_oAdmin.GetTechByAlias(sUser)
' populate array with technician's requests
ReDim m_reqArray(m_oTech.Requests.Count, icArrayColumns)
' Supply column names
lRow = 0
m_reqArray(lRow, ArrayCols.PKId) = "PKid"
m_reqArray(lRow, ArrayCols.Priority) = "Priority"
m_reqArray(lRow, ArrayCols.Status) = "Status"
m_reqArray(lRow, ArrayCols.RequestDate) = "Request Date"
m_reqArray(lRow, ArrayCols.Description) = "Description"
m_reqArray(lRow, ArrayCols.Description_State) = "Description_State"
m_reqArray(lRow, ArrayCols.Description_Dat) = "Description_Dat"

For Each oReq In m_oTech.Requests
    lRow = lRow + 1
    m_reqArray(lRow, ArrayCols.PKId) = oReq.PKId
    m_reqArray(lRow, ArrayCols.Priority) _
        = m_oAdmin.GetPriorities(m_oAdmin.Format_ItemPKId(oReq.PriorityId)).Code
    m_reqArray(lRow, ArrayCols.Status) _
        = m_oAdmin.GetReqStatus(m_oAdmin.Format_ItemPKId(oReq.StatusId)).Code
    m_reqArray(lRow, ArrayCols.RequestDate) = oReq.ReqDate
    m_reqArray(lRow, ArrayCols.Description) = oReq.Desc
    m_reqArray(lRow, ArrayCols.Description_State) = DescState.Collapsed
    m_reqArray(lRow, ArrayCols.Description_Dat) = oReq.Desc
Next
' Clean up
Set oReq = Nothing

End Sub
Private Sub InitWithDummyData()
' Populate m_reqArray with dummy data
Dim lRow

' initialize the array
ReDim m_reqArray(25, icArrayColumns) As Variant
    
lRow = 0
m_reqArray(lRow, ArrayCols.PKId) = "PKid"
m_reqArray(lRow, ArrayCols.Priority) = "Priority"
m_reqArray(lRow, ArrayCols.Status) = "Status"
m_reqArray(lRow, ArrayCols.RequestDate) = "Request Date"
m_reqArray(lRow, ArrayCols.Description) = "Description"
m_reqArray(lRow, ArrayCols.Description_State) = "Description_State"
m_reqArray(lRow, ArrayCols.Description_Dat) = "Description_Dat"

lRow = 1
m_reqArray(lRow, ArrayCols.PKId) = "4"
m_reqArray(lRow, ArrayCols.Priority) = "low"
m_reqArray(lRow, ArrayCols.Status) = "Unclaimed"
m_reqArray(lRow, ArrayCols.RequestDate) = CDate("11/6/97")
m_reqArray(lRow, ArrayCols.Description) = "Unable to find web sites outside LAN"
m_reqArray(lRow, ArrayCols.Description_State) = DescState.Collapsed
m_reqArray(lRow, ArrayCols.Description_Dat) = "Unable to find web sites outside LAN"

lRow = 2
m_reqArray(lRow, ArrayCols.PKId) = "5"
m_reqArray(lRow, ArrayCols.Priority) = "med"
m_reqArray(lRow, ArrayCols.Status) = "In prog"
m_reqArray(lRow, ArrayCols.RequestDate) = CDate("11/6/97")
m_reqArray(lRow, ArrayCols.Description) = "Unable to connect to network"
m_reqArray(lRow, ArrayCols.Description_State) = DescState.Collapsed
m_reqArray(lRow, ArrayCols.Description_Dat) = "Unable to connect to network"

lRow = 3
m_reqArray(lRow, ArrayCols.PKId) = "7"
m_reqArray(lRow, ArrayCols.Priority) = "high"
m_reqArray(lRow, ArrayCols.Status) = "In prog"
m_reqArray(lRow, ArrayCols.RequestDate) = CDate("11/4/97")
m_reqArray(lRow, ArrayCols.Description) = "Unable to chat"
m_reqArray(lRow, ArrayCols.Description_State) = DescState.Collapsed
m_reqArray(lRow, ArrayCols.Description_Dat) = "Unable to chat"

lRow = 4
m_reqArray(lRow, ArrayCols.PKId) = "8"
m_reqArray(lRow, ArrayCols.Priority) = "low"
m_reqArray(lRow, ArrayCols.Status) = "In prog"
m_reqArray(lRow, ArrayCols.RequestDate) = CDate("11/4/97")
m_reqArray(lRow, ArrayCols.Description) = "Unable to see print queue"
m_reqArray(lRow, ArrayCols.Description_State) = DescState.Collapsed
m_reqArray(lRow, ArrayCols.Description_Dat) = "Unable to see print queue"

lRow = 5
m_reqArray(lRow, ArrayCols.PKId) = "9"
m_reqArray(lRow, ArrayCols.Priority) = "med"
m_reqArray(lRow, ArrayCols.Status) = "Res pending"
m_reqArray(lRow, ArrayCols.RequestDate) = CDate("11/3/97")
m_reqArray(lRow, ArrayCols.Description) = "Unable to boot"
m_reqArray(lRow, ArrayCols.Description_State) = DescState.Collapsed
m_reqArray(lRow, ArrayCols.Description_Dat) = "Unable to boot"
 
lRow = 6
m_reqArray(lRow, ArrayCols.PKId) = "11"
m_reqArray(lRow, ArrayCols.Priority) = "high"
m_reqArray(lRow, ArrayCols.Status) = "Unclaimed"
m_reqArray(lRow, ArrayCols.RequestDate) = CDate("11/1/97")
m_reqArray(lRow, ArrayCols.Description) = "Chat freezes"
m_reqArray(lRow, ArrayCols.Description_State) = DescState.Collapsed
m_reqArray(lRow, ArrayCols.Description_Dat) = "Chat freezes"
  
lRow = 7
m_reqArray(lRow, ArrayCols.PKId) = "15"
m_reqArray(lRow, ArrayCols.Priority) = "high"
m_reqArray(lRow, ArrayCols.Status) = "Unclaimed"
m_reqArray(lRow, ArrayCols.RequestDate) = CDate("11/1/97")
m_reqArray(lRow, ArrayCols.Description) = "No LAN access"
m_reqArray(lRow, ArrayCols.Description_State) = DescState.Collapsed
m_reqArray(lRow, ArrayCols.Description_Dat) = "No LAN access"
  
lRow = 8
m_reqArray(lRow, ArrayCols.PKId) = "17"
m_reqArray(lRow, ArrayCols.Priority) = "high"
m_reqArray(lRow, ArrayCols.Status) = "Unclaimed"
m_reqArray(lRow, ArrayCols.RequestDate) = CDate("11/1/97")
m_reqArray(lRow, ArrayCols.Description) = "Proxy problem"
m_reqArray(lRow, ArrayCols.Description_State) = DescState.Collapsed
m_reqArray(lRow, ArrayCols.Description_Dat) = "Proxy problem"

lRow = 9
m_reqArray(lRow, ArrayCols.PKId) = "18"
m_reqArray(lRow, ArrayCols.Priority) = "high"
m_reqArray(lRow, ArrayCols.Status) = "Unclaimed"
m_reqArray(lRow, ArrayCols.RequestDate) = CDate("11/2/97")
m_reqArray(lRow, ArrayCols.Description) = "SQL access problem"
m_reqArray(lRow, ArrayCols.Description_State) = DescState.Collapsed
m_reqArray(lRow, ArrayCols.Description_Dat) = "SQL access problem"

lRow = 10
m_reqArray(lRow, ArrayCols.PKId) = "19"
m_reqArray(lRow, ArrayCols.Priority) = "high"
m_reqArray(lRow, ArrayCols.Status) = "Unclaimed"
m_reqArray(lRow, ArrayCols.RequestDate) = CDate("11/2/97")
m_reqArray(lRow, ArrayCols.Description) = "Disk full"
m_reqArray(lRow, ArrayCols.Description_State) = DescState.Collapsed
m_reqArray(lRow, ArrayCols.Description_Dat) = "Disk full"
  
lRow = 11
m_reqArray(lRow, ArrayCols.PKId) = "20"
m_reqArray(lRow, ArrayCols.Priority) = "high"
m_reqArray(lRow, ArrayCols.Status) = "In prog"
m_reqArray(lRow, ArrayCols.RequestDate) = CDate("11/2/97")
m_reqArray(lRow, ArrayCols.Description) = "Display dim"
m_reqArray(lRow, ArrayCols.Description_State) = DescState.Collapsed
m_reqArray(lRow, ArrayCols.Description_Dat) = "Display dim"

lRow = 12
m_reqArray(lRow, ArrayCols.PKId) = "21"
m_reqArray(lRow, ArrayCols.Priority) = "med"
m_reqArray(lRow, ArrayCols.Status) = "Unclaimed"
m_reqArray(lRow, ArrayCols.RequestDate) = CDate("11/3/97")
m_reqArray(lRow, ArrayCols.Description) = "Mouse slips"
m_reqArray(lRow, ArrayCols.Description_State) = DescState.Collapsed
m_reqArray(lRow, ArrayCols.Description_Dat) = "Mouse slips"

lRow = 13
m_reqArray(lRow, ArrayCols.PKId) = "22"
m_reqArray(lRow, ArrayCols.Priority) = "high"
m_reqArray(lRow, ArrayCols.Status) = "Unclaimed"
m_reqArray(lRow, ArrayCols.RequestDate) = CDate("11/3/97")
m_reqArray(lRow, ArrayCols.Description) = "Cannot reconfigure desktop"
m_reqArray(lRow, ArrayCols.Description_State) = DescState.Collapsed
m_reqArray(lRow, ArrayCols.Description_Dat) = "Cannot reconfigure desktop"

lRow = 14
m_reqArray(lRow, ArrayCols.PKId) = "23"
m_reqArray(lRow, ArrayCols.Priority) = "high"
m_reqArray(lRow, ArrayCols.Status) = "Unclaimed"
m_reqArray(lRow, ArrayCols.RequestDate) = CDate("11/1/97")
m_reqArray(lRow, ArrayCols.Description) = "Mouse freezes"
m_reqArray(lRow, ArrayCols.Description_State) = DescState.Collapsed
m_reqArray(lRow, ArrayCols.Description_Dat) = "Mouse freezes"

lRow = 15
m_reqArray(lRow, ArrayCols.PKId) = "25"
m_reqArray(lRow, ArrayCols.Priority) = "med"
m_reqArray(lRow, ArrayCols.Status) = "Unclaimed"
m_reqArray(lRow, ArrayCols.RequestDate) = CDate("11/4/97")
m_reqArray(lRow, ArrayCols.Description) = "Display refresh slow"
m_reqArray(lRow, ArrayCols.Description_State) = DescState.Collapsed
m_reqArray(lRow, ArrayCols.Description_Dat) = "Display refresh slow"

lRow = 16
m_reqArray(lRow, ArrayCols.PKId) = "30"
m_reqArray(lRow, ArrayCols.Priority) = "high"
m_reqArray(lRow, ArrayCols.Status) = "Unclaimed"
m_reqArray(lRow, ArrayCols.RequestDate) = CDate("11/4/97")
m_reqArray(lRow, ArrayCols.Description) = "No Audio"
m_reqArray(lRow, ArrayCols.Description_State) = DescState.Collapsed
m_reqArray(lRow, ArrayCols.Description_Dat) = "No Audio"

lRow = 17
m_reqArray(lRow, ArrayCols.PKId) = "32"
m_reqArray(lRow, ArrayCols.Priority) = "low"
m_reqArray(lRow, ArrayCols.Status) = "Unclaimed"
m_reqArray(lRow, ArrayCols.RequestDate) = CDate("11/4/97")
m_reqArray(lRow, ArrayCols.Description) = "Video locks"
m_reqArray(lRow, ArrayCols.Description_State) = DescState.Collapsed
m_reqArray(lRow, ArrayCols.Description_Dat) = "Video locks"

lRow = 18
m_reqArray(lRow, ArrayCols.PKId) = "33"
m_reqArray(lRow, ArrayCols.Priority) = "med"
m_reqArray(lRow, ArrayCols.Status) = "Unclaimed"
m_reqArray(lRow, ArrayCols.RequestDate) = CDate("11/3/97")
m_reqArray(lRow, ArrayCols.Description) = "Fan sound"
m_reqArray(lRow, ArrayCols.Description_State) = DescState.Collapsed
m_reqArray(lRow, ArrayCols.Description_Dat) = "Fan sound"

lRow = 19
m_reqArray(lRow, ArrayCols.PKId) = "40"
m_reqArray(lRow, ArrayCols.Priority) = "high"
m_reqArray(lRow, ArrayCols.Status) = "Unclaimed"
m_reqArray(lRow, ArrayCols.RequestDate) = CDate("11/2/97")
m_reqArray(lRow, ArrayCols.Description) = "CD not working"
m_reqArray(lRow, ArrayCols.Description_State) = DescState.Collapsed
m_reqArray(lRow, ArrayCols.Description_Dat) = "CD not working"

lRow = 20
m_reqArray(lRow, ArrayCols.PKId) = "41"
m_reqArray(lRow, ArrayCols.Priority) = "low"
m_reqArray(lRow, ArrayCols.Status) = "Unclaimed"
m_reqArray(lRow, ArrayCols.RequestDate) = CDate("11/2/97")
m_reqArray(lRow, ArrayCols.Description) = "Install graphics system"
m_reqArray(lRow, ArrayCols.Description_State) = DescState.Collapsed
m_reqArray(lRow, ArrayCols.Description_Dat) = "Install graphics system"

lRow = 21
m_reqArray(lRow, ArrayCols.PKId) = "46"
m_reqArray(lRow, ArrayCols.Priority) = "low"
m_reqArray(lRow, ArrayCols.Status) = "Unclaimed"
m_reqArray(lRow, ArrayCols.RequestDate) = CDate("11/2/97")
m_reqArray(lRow, ArrayCols.Description) = "Install modem"
m_reqArray(lRow, ArrayCols.Description_State) = DescState.Collapsed
m_reqArray(lRow, ArrayCols.Description_Dat) = "Install modem"

lRow = 22
m_reqArray(lRow, ArrayCols.PKId) = "47"
m_reqArray(lRow, ArrayCols.Priority) = "low"
m_reqArray(lRow, ArrayCols.Status) = "Unclaimed"
m_reqArray(lRow, ArrayCols.RequestDate) = CDate("11/6/97")
m_reqArray(lRow, ArrayCols.Description) = "Display refresh slow"
m_reqArray(lRow, ArrayCols.Description_State) = DescState.Collapsed
m_reqArray(lRow, ArrayCols.Description_Dat) = "Display refresh slow"

lRow = 23
m_reqArray(lRow, ArrayCols.PKId) = "48"
m_reqArray(lRow, ArrayCols.Priority) = "med"
m_reqArray(lRow, ArrayCols.Status) = "Claimed"
m_reqArray(lRow, ArrayCols.RequestDate) = CDate("11/6/97")
m_reqArray(lRow, ArrayCols.Description) = "Unable to connect to network"
m_reqArray(lRow, ArrayCols.Description_State) = DescState.Collapsed
m_reqArray(lRow, ArrayCols.Description_Dat) = "Unable to connect to network"

lRow = 24
m_reqArray(lRow, ArrayCols.PKId) = "49"
m_reqArray(lRow, ArrayCols.Priority) = "high"
m_reqArray(lRow, ArrayCols.Status) = "In prog"
m_reqArray(lRow, ArrayCols.RequestDate) = CDate("11/4/97")
m_reqArray(lRow, ArrayCols.Description) = "Unable to chat"
m_reqArray(lRow, ArrayCols.Description_State) = DescState.Collapsed
m_reqArray(lRow, ArrayCols.Description_Dat) = "Unable to chat"

lRow = 25
m_reqArray(lRow, ArrayCols.PKId) = "50"
m_reqArray(lRow, ArrayCols.Priority) = "low"
m_reqArray(lRow, ArrayCols.Status) = "In prog"
m_reqArray(lRow, ArrayCols.RequestDate) = CDate("11/4/97")
m_reqArray(lRow, ArrayCols.Description) = "Cannot find favorites"
m_reqArray(lRow, ArrayCols.Description_State) = DescState.Collapsed
m_reqArray(lRow, ArrayCols.Description_Dat) = "Cannot find favorites"

End Sub
