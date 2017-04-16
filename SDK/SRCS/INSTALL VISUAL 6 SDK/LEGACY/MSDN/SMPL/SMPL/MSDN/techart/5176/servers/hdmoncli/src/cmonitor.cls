VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CMonitor"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Private m_cTraces As Collection
Private m_sSnapIDs() As String
Private m_cSnapShots As Collection
Private m_dFirst As Date
Private m_dLast As Date

Public Property Get Traces() As Collection
If m_cTraces Is Nothing Then
    Set m_cTraces = New Collection
End If
Set Traces = m_cTraces
End Property

Private Sub Class_Initialize()
InitTraces (icTotal)
End Sub

Public Function InitTraces(ByVal vDetailLevel As Variant) As Boolean
Dim oTrace As CTrace
Dim oHDAdmin As New CAdmin
Dim oPriority As CPriority
Dim oSkill As CSkill
Dim oStatus As CReqStatus
Dim sLevel As String

Set m_cTraces = New Collection
' Add trace for request total
If (vDetailLevel And icDetaillevel.icTotal) = icDetaillevel.icTotal Then
    Set oTrace = New CTrace
    sLevel = scReqTotEntity
    oTrace.level = sLevel
    oTrace.Description = scReqTotDesc
    m_cTraces.Add oTrace, sLevel
    Set oTrace = Nothing
    InitTraces = True
End If
' Add traces for priority
If (vDetailLevel And icDetaillevel.icPRIORITY) = icDetaillevel.icPRIORITY Then
    For Each oPriority In oHDAdmin.GetPriorities
        Set oTrace = New CTrace
        sLevel = scSubTotEntity & scPriority & scCol & oPriority.PKId
        oTrace.level = sLevel
        oTrace.Description = scReqSubPriority & oPriority.Desc
        m_cTraces.Add oTrace, sLevel
        Set oTrace = Nothing
    Next
    Set oPriority = Nothing
    InitTraces = True
End If
' Add traces for skill
If (vDetailLevel And icDetaillevel.icSKILL) = icDetaillevel.icSKILL Then
    For Each oSkill In oHDAdmin.GetSkills
        Set oTrace = New CTrace
        sLevel = scSubTotEntity & scSkill & scCol & oSkill.PKId
        oTrace.level = sLevel
        oTrace.Description = scReqSubSkill & oSkill.Desc
        m_cTraces.Add oTrace, sLevel
        Set oTrace = Nothing
    Next
    Set oSkill = Nothing
    InitTraces = True

End If
' Add traces for status
If (vDetailLevel And icDetaillevel.icStatus) = icDetaillevel.icStatus Then
    For Each oStatus In oHDAdmin.GetReqStatus
        Set oTrace = New CTrace
        sLevel = scSubTotEntity & scStatus & scCol & oStatus.PKId
        oTrace.level = sLevel
        oTrace.Description = scReqSubStatus & oStatus.Desc
        m_cTraces.Add oTrace, sLevel
        Set oTrace = Nothing
    Next
    Set oStatus = Nothing
    InitTraces = True
End If
End Function

Public Function CompletePeriodData(ByVal vStart, ByVal vDuration) As Boolean

CompletePeriodData = False
' Resolve display boundary dates
If CBoundDates(vStart, vDuration, m_dFirst, m_dLast) Then
' Build list of snapsots required for display
    If FillSnapList() Then
        If FillSnapcache() Then
            CompletePeriodData = True
        End If
    End If
' Retrieve any uncached snapshots
End If
End Function
Public Function GetFirstDate() As Date
Dim oTrans As New CTrans
Dim sData() As String
Dim sDate As String
Dim iIndex As Integer
On Error GoTo ErrGetFirstdate

If oTrans.GetSnapshotDate(icFIRST_DATE, sData) Then
    iIndex = UBound(sData, icTwoDim)
    sDate = sData(icZeroDim, iIndex)
GetFirstDate = CDate(sDate)
End If
Set oTrans = Nothing
Exit Function
ErrGetFirstdate:
On Error GoTo 0
Set oTrans = Nothing
Exit Function
End Function
Public Function GetLastDate() As Date
Dim oTrans As New CTrans
Dim sData() As String
Dim sDate As String
Dim iIndex As Integer
On Error GoTo ErrGetLastDate

If oTrans.GetSnapshotDate(icLAST_DATE, sData) Then
    iIndex = UBound(sData, icTwoDim)
    sDate = sData(icZeroDim, iIndex)
GetLastDate = CDate(sDate)
End If
Set oTrans = Nothing
Exit Function
ErrGetLastDate:
On Error GoTo 0
Set oTrans = Nothing
Exit Function
End Function
Public Function SetPoints(oTrace, ByVal vMin As Long, ByVal vMax As Long, ByVal xPix As Long, ByVal yPix As Long) As Variant
Dim oSnap As CSnapShot
Dim nPts
Dim sId As String
Dim lIndex As Long
Dim vTmp() As Variant
Dim xSnap As Long
Dim ySnap As Long
Dim lQty As Long

On Error GoTo ErrSetPoints
nPts = UBound(m_sSnapIDs, icTwoDim) + 1
ReDim vTmp(nPts * 2 - 1)
For lIndex = LBound(m_sSnapIDs, icTwoDim) To UBound(m_sSnapIDs, icTwoDim)
    sId = ItemPKId(m_sSnapIDs(0, lIndex))
    Set oSnap = m_cSnapShots(sId)
    xSnap = CLng(xPix * ((oSnap.SnapDate - m_dFirst) / (m_dLast - m_dFirst)))
    lQty = GetTraceQty(oTrace.level, oSnap.SnapData)
    ySnap = yPix - CLng(yPix * (lQty - vMin) / (vMax - vMin))
    vTmp(lIndex * 2) = xSnap
    vTmp(lIndex * 2 + 1) = ySnap
Next

SetPoints = vTmp

Exit Function

ErrSetPoints:
Exit Function

End Function
Private Function CBoundDates(vStart, vDuration, dFirst, dLast) As Boolean
dFirst = CDate(vStart)
Select Case vDuration
    Case scHour
        dLast = DateAdd(scHour, 1, dFirst)
        CBoundDates = True
    Case scDay
        dLast = DateAdd(scDay, 1, dFirst)
        CBoundDates = True
    Case scWeek
        dLast = DateAdd(scWeek, 1, dFirst)
        CBoundDates = True
    Case scMonth
        dLast = DateAdd(scMonth, 1, dFirst)
        CBoundDates = True
    Case scYear
        dLast = DateAdd(scYear, 1, dFirst)
        CBoundDates = True
End Select
End Function
Private Function FillSnapList() As Boolean
    Dim oTrans As New CTrans
    On Error GoTo ErrFillSnapList
    FillSnapList = False
    ReDim m_sSnapIDs(0)
    If oTrans.GetSnapshotIDs(m_dFirst, m_dLast, m_sSnapIDs) Then
        FillSnapList = True
    End If
    Set oTrans = Nothing
    Exit Function
ErrFillSnapList:
    On Error GoTo 0
    Set oTrans = Nothing
End Function
Private Function FillSnapcache() As Boolean
' Insure that snapshots listed in m_sSnaps are in m_cSnapShots.
    Dim lFirst As Long
    Dim lLast As Long
 ' Determine range of IDs not in cache
FillSnapcache = False
If GetMissingRange(lFirst, lLast) Then
' FillSnapshotRange()
    If FillMissingRange(lFirst, lLast) Then
        FillSnapcache = True
    End If
End If
FillSnapcache = True
End Function
Private Function GetMissingRange(lFirst, lLast) As Boolean
' Determine the minimum range of snapshot records required to complete cache for range
Dim oSnap As CSnapShot
Dim lLowNdx As Long
Dim lHighNdx As Long
Dim lIndex As Long
Dim sId As String

GetMissingRange = False
lLowNdx = LBound(m_sSnapIDs, icTwoDim)
lHighNdx = UBound(m_sSnapIDs, icTwoDim)
' Test for case where cache is empty
If m_cSnapShots Is Nothing Then
    lFirst = lLowNdx
    lLast = lHighNdx
    GetMissingRange = True
    Exit Function
End If
' Find first missing snapshot starting from lLowNdx
For lIndex = LBound(m_sSnapIDs, icTwoDim) To UBound(m_sSnapIDs, icTwoDim)
     Set oSnap = Nothing
     sId = ItemPKId(m_sSnapIDs(0, lIndex))
     On Error Resume Next
     Set oSnap = m_cSnapShots(sId)
     On Error GoTo 0
     If oSnap Is Nothing Then
     ' Id not in collection so return True and save lLowNdx
        GetMissingRange = True
        lLowNdx = lIndex
        Exit For
     End If
Next lIndex
' Find first missing snapshot starting from lHighNdx
For lIndex = UBound(m_sSnapIDs, icTwoDim) To LBound(m_sSnapIDs, icTwoDim) Step -1
     Set oSnap = Nothing
     sId = ItemPKId(m_sSnapIDs(0, lIndex))
     On Error Resume Next
     Set oSnap = m_cSnapShots(sId)
     On Error GoTo 0
     If oSnap Is Nothing Then
     ' Id not in collection so return True and save lLowNdx
        GetMissingRange = True
        lHighNdx = lIndex
        Exit For
     End If
Next lIndex
Set oSnap = Nothing
' Return missing range
lFirst = lLowNdx
lLast = lHighNdx
End Function
Private Function FillMissingRange(ByVal lFirst As Long, ByVal lLast As Long) As Boolean
    Dim oSnap As CSnapShot
    Dim oTrans As New CTrans
    Dim sData() As String
    Dim lFirstId As Long
    Dim lLastId As Long
    Dim lIndex As Long
    
    On Error GoTo ErrFillMissingRange
    FillMissingRange = False
    lFirstId = (m_sSnapIDs(0, lFirst))
    lLastId = (m_sSnapIDs(0, lLast))
    If oTrans.GetSnapshotRange(sData, lFirstId, lLastId) Then
' Init m_colSnapshots if necessary
        If m_cSnapShots Is Nothing Then
            Set m_cSnapShots = New Collection
        End If
        For lIndex = LBound(sData, icTwoDim) To UBound(sData, icTwoDim)
             sId = ItemPKId(sData(0, lIndex))
             Set oSnap = New CSnapShot
             oSnap.PKId = CLng(sData(0, lIndex))
             oSnap.SnapDate = CDate(sData(1, lIndex))
             oSnap.SnapData = sData(2, lIndex)
             On Error Resume Next
             m_cSnapShots.Add oSnap, sId
             On Error GoTo 0
             Set oSnap = Nothing
        Next lIndex

        FillMissingRange = True
    End If
    Set oTrans = Nothing
    Exit Function
ErrFillMissingRange:
    On Error GoTo 0
    Set oTrans = Nothing
End Function
Private Function GetTraceQty(sLevel, sSnapDat) As Long
Dim lTag1 As Long
Dim lTag2 As Long
Dim lPos As Long
Dim sTag As String
lTag1 = InStr(sSnapDat, "<" & sLevel)
lTag2 = InStr(lTag1, sSnapDat, ">")
sTag = Mid$(sSnapDat, lTag1, lTag2 - lTag1)
lPos = InStr(sTag, "c:")
GetTraceQty = CLng(Val(Mid$(sTag, lPos + 2)))
End Function

