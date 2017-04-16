VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CSnapshot"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Private Const OBJNAME = "CSnapshot"
Private Const scConnect = "helpdesk"    'name of the DSN, ASSUMES TRUSTED CONNECTION!
Private Const scExecute = "Execute "
Private Const scSysSnapshot = "pcSnap_Stat"
Private Const scInsertSnapshot = "pcIns_Snapshot"

Private Const scLeftDelim = "<"
Private Const scRightDelim = ">"
Private Const scValueDiv = ":"
Private Const scDetailEntity = "D"
Private Const scSubTotEntity = "S"
Private Const scReqTotEntity = "T"
Private Const scCount = "c"
Private Const scDate = "d"
Private Const scPriority = "p"
Private Const scSkill = "i"
Private Const scStatus = "u"

' Structure for data returned by scSysSnapshot
Private Enum icSnapReq
    icReqDate = 0
    icReqPriorityId = 1
    icReqSkillId = 2
    icReqStatusId = 3
End Enum



Public Function SysSnapshot()
' Take a snapshot of the system
#If bUseMTS Then
    Dim oCtxt       As MTxAS.ObjectContext
#End If
Dim oExec       As DBExec.CExec
Dim sData()     As String
Dim sQry        As String
Dim sSnap       As String

SysSnapshot = False

'Build query string
sQry = scExecute & scSysSnapshot

#If bUseMTS Then
    'create object context
    Set oCtxt = GetObjectContext()
    'new instance of CExec class under MTS
    Set oExec = oCtxt.CreateInstance("DBExec.CExec")
#Else
    Set oExec = New DBExec.CExec
#End If

'Call the method on the CExec class
If oExec.ExecFillArray(scConnect, sQry, sData) Then
    If PackSnapData(sData, sSnap) Then
        sQry = scExecute & scInsertSnapshot
        sQry = sQry & " @SnapData = " & scSQ & sSnap & scSQ
        If oExec.ExecQuery(scConnect, sQry) Then
            SysSnapshot = True
        End If
    End If
End If

Set oExec = Nothing             'clear the class

#If bUseMTS Then
    oCtxt.SetComplete
    Set oCtxt = Nothing
#End If

End Function
Private Function PackSnapData(ByVal sData, sSnap) As Boolean
Dim colSums       As New Collection
Dim oSum          As CSumEntity
Dim lIndex        As Long
Dim lReqCount     As Long
Dim lPriority     As Long
Dim lSkill        As Long
Dim lStatus       As Long
Dim sBuf          As String
Dim sDate         As String
Dim sEty          As String
Dim sKey          As String

On Error GoTo ErrPackSnapData

lReqCount = 0
' Gather detail and summary data for all requests in snapshot
For lIndex = LBound(sData, icTwoDim) To UBound(sData, icTwoDim)
    sDate = CDate(sData(icSnapReq.icReqDate, lIndex))
    lPriority = CLng(sData(icSnapReq.icReqPriorityId, lIndex))
    lSkill = CLng(sData(icSnapReq.icReqSkillId, lIndex))
    lStatus = CLng(sData(icSnapReq.icReqStatusId, lIndex))
    
    ' Increment Request total
    lReqCount = lReqCount + 1
    
    ' Increment Priority sub total
    sKey = scPriority & scValueDiv & lPriority
    Set oSum = Nothing
    On Error Resume Next
    Set oSum = colSums(sKey)
    On Error GoTo ErrPackSnapData
    If oSum Is Nothing Then
        Set oSum = New CSumEntity
        oSum.Key = sKey
        oSum.Count = 1
        colSums.Add oSum, sKey
    Else
        oSum.Count = oSum.Count + 1
        Set oSum = Nothing
    End If
    
    ' Increment Skill sub total
    sKey = scSkill & scValueDiv & lSkill
    Set oSum = Nothing
    On Error Resume Next
    Set oSum = colSums(sKey)
    On Error GoTo ErrPackSnapData
    If oSum Is Nothing Then
        Set oSum = New CSumEntity
        oSum.Key = sKey
        oSum.Count = 1
        colSums.Add oSum, sKey
    Else
        oSum.Count = oSum.Count + 1
        Set oSum = Nothing
    End If
    
    ' Increment Status sub total
    sKey = scStatus & scValueDiv & lStatus
    Set oSum = Nothing
    On Error Resume Next
    Set oSum = colSums(sKey)
    On Error GoTo ErrPackSnapData
    If oSum Is Nothing Then
        Set oSum = New CSumEntity
        oSum.Key = sKey
        oSum.Count = 1
        colSums.Add oSum, sKey
    Else
        oSum.Count = oSum.Count + 1
        Set oSum = Nothing
    End If
    
    ' Build the detail entity for this request
    sEty = scLeftDelim _
        & scDetailEntity _
        & scDate & scValueDiv & sDate _
        & scPriority & scValueDiv & CStr(lPriority) _
        & scSkill & scValueDiv & CStr(lSkill) _
        & scStatus & scValueDiv & CStr(lStatus) _
        & scRightDelim
    ' Add detail entity to the buffer
    sBuf = sBuf & sEty
Next lIndex

' Build sub total entities and add to buffer
For Each oSum In colSums
    sEty = scLeftDelim _
        & scSubTotEntity _
        & oSum.Key _
        & scCount & scValueDiv & CStr(oSum.Count) _
        & scRightDelim
    sBuf = sEty & sBuf
Next

' Build total entity and add to buffer
sEty = scLeftDelim _
    & scReqTotEntity _
    & scCount & scValueDiv & CStr(lReqCount) _
    & scRightDelim
sBuf = sEty & sBuf

' Temporary work around for t-sql VarChar(255) parameter type
sSnap = Left$(sBuf, 255)

PackSnapData = True
Exit Function

ErrPackSnapData:
MsgBox (Error$)
Resume

End Function
