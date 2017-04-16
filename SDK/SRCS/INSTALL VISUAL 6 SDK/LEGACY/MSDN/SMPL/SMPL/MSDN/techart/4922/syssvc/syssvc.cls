VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Services"
Attribute VB_Creatable = True
Attribute VB_Exposed = True
Option Explicit

Public Logs     As LayerLogAll.Services
Public LogEvt   As LayerLogInformation.Service
Public LogErr   As LayerLogError.Service
Public LogTrn   As LayerLogDatabase.Service

Public ErrSvc   As LayerError.Service
Public DcnSvc   As LayerDatabase.Service
Public RegSvc   As LayerRegistry.Service

Private sbSys   As Object
Private pbSys   As Object

Public Function Init(sbApp As Object, pbApp As Object) As Boolean
On Error GoTo initerr
Set RegSvc = New LayerRegistry.Service

Set Logs = New LayerLogAll.Services
Set LogErr = Logs.Error
Set LogEvt = Logs.Event
Set LogTrn = Logs.Trans

Set ErrSvc = New LayerError.Service

LogErr.Enabled = True
LogErr.filename = "err.log"
LogErr.BackUpFileName = "err.bak"
LogErr.MaxBytes = 3000

Set ErrSvc.LogErr = Logs

If Not ErrSvc.Init Then
    Init = False
    Exit Function
End If

LogEvt.Enabled = True
LogEvt.filename = "inf.log"
LogEvt.BackUpFileName = "inf.bak"
LogEvt.MaxBytes = 3000
If Not LogEvt.Init Then
    ErrSvc.Raise False, -9, "Could not open informational log.", "Could not open informational log."
    Init = False
    Exit Function
End If

Set ErrSvc.LogEvt = Logs

LogTrn.Enabled = True
LogTrn.filename = "sql.log"
LogTrn.BackUpFileName = "sql.bak"
LogTrn.MaxBytes = 3000
If Not LogTrn.Init Then
    ErrSvc.Raise False, -9, "Could not open transaction log.", "Could not open transaction log."
    Init = False
    Exit Function
End If

Set DcnSvc = New LayerDatabase.Service

Set sbSys = sbApp
Set pbSys = pbApp

Init = True
Exit Function

initerr:
    Init = False
    Exit Function

End Function

Public Function ObjectInit(objRef, ByVal sClassName As String) As Boolean
On Error GoTo initobjerr
ObjectInit = False
LogEvt.PostItem 60, "Creating object of class - ", sClassName
Set objRef = CreateObject(sClassName)
LogEvt.PostItem 61, "Successfully created - ", sClassName
If Not objRef.Init(Me) Then
    ObjectInit = True
    LogEvt.PostItem 62, "Successfully initialized object of class - ", sClassName
Else
    ErrSvc.Raise False, -34, "There was an error initializing object.", "There was an error initializing object."
End If
Exit Function

initobjerr:
    ErrSvc.Raise False, -33, Error$, "There was an error creating object of class - " & sClassName & vbCRLF & "Contact your System Administrator."
    Exit Function
    
End Function

Public Sub ObjectTerm(objRef)
On Error Resume Next
LogEvt.PostItem 70, "Deleting object reference - ", TypeName(objRef)
objRef.Term
Set objRef = Nothing
End Sub

Public Sub PercentReset()
On Error Resume Next
pbSys.Visible = False
pbSys.Value = pbSys.Min
DoEvents
End Sub

Public Sub PercentSet(ByVal iVal As Integer)
On Error Resume Next
pbSys.Visible = True
pbSys.Value = iVal
DoEvents
End Sub

Public Sub StatusReset()
On Error Resume Next
sbSys.Panels("STATUS").Text = STR_STS_REDY
sbSys.Refresh
PercentReset
DoEvents
End Sub

Public Sub StatusSet(ByVal sText As String)
On Error Resume Next
sbSys.Panels("STATUS").Text = sText
sbSys.Refresh
DoEvents
End Sub

Public Sub Term()
On Error Resume Next
Dim iIndex As Integer

Set RegSvc = Nothing

DcnSvc.Term
Set DcnSvc = Nothing

ErrSvc.Term
Set ErrSvc = Nothing

Set LogErr = Nothing
Set LogEvt = Nothing
Set LogTrn = Nothing

Set Logs.Error = Nothing
Set Logs.Event = Nothing
Set Logs.Trans = Nothing
Set Logs = Nothing

Set sbSys = Nothing
Set pbSys = Nothing
End Sub

Private Sub Class_Initialize()
On Error Resume Next
App.TaskVisible = False
End Sub

Private Sub Class_Terminate()
On Error Resume Next
Term
End Sub


