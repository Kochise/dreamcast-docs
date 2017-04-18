VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "AccessReport"
Attribute VB_Creatable = True
Attribute VB_Exposed = True
Option Explicit
Private AccessApp   As Access.Application
Private sDBName     As String
Public fPhaseTwo    As Boolean
Private sCurrentRep As String
Public Property Get DBName() As String
DBName = sDBName
End Property
Public Property Let DBName(ByVal sVal As String)
sDBName = sVal
End Property

Public Function GetReport(ByVal sRepName As String) As Object
frmMain.StatusSet "Retrieving report..."
sCurrentRep = sRepName
AccessApp.DoCmd.OpenReport sCurrentRep, acPreview
Set GetReport = AccessApp.Reports(sCurrentRep)
frmMain.StatusReset
End Function

Public Function InitializeAccess(ByVal sDBName As String) As Boolean
On Error GoTo errExit
frmMain.StatusSet "Initializing Access Application..."
Set AccessApp = New Access.Application

AccessApp.OpenCurrentDatabase sDBName
InitializeAccess = True
frmMain.StatusReset
Exit Function

errExit:
    InitializeAccess = False
    frmMain.StatusReset
    Exit Function
    
End Function

Public Function ReportList() As Variant
Dim sTemp() As String
Dim dcTemp As Document
Dim dbTemp As Database
Dim iIndex As Integer

frmMain.StatusSet "Building Reports List..."
Set dbTemp = AccessApp.CurrentDb
ReDim sTemp(dbTemp.Containers("Reports").Documents.Count - 1) As String
iIndex = 0
For Each dcTemp In dbTemp.Containers("Reports").Documents
    sTemp(iIndex) = dcTemp.Name
    iIndex = iIndex + 1
Next dcTemp
frmMain.StatusSet "Returning Reports List..."
ReportList = sTemp
frmMain.StatusReset
End Function

Public Sub PrintReport(Optional fAsync As Variant)
If IsMissing(fAsync) Then
    ReportPrint
Else
    If fAsync Then
        fPhaseTwo = False
        frmMain!tmMain.Enabled = True
    Else
        ReportPrint
    End If
End If
End Sub

Private Sub ReportPrint()
On Error Resume Next
fPhaseTwo = False
frmMain!tmMain.Enabled = False
frmMain.StatusSet "Printing report..."
AccessApp.DoCmd.OpenReport sCurrentRep
frmMain.StatusReset
End Sub

Public Sub TerminateAccess()
On Error Resume Next
AccessApp.Quit acExit
Set AccessApp = Nothing
Unload frmMain
End Sub
Private Sub Class_Initialize()
frmMain.Show
Set frmMain.objWork = Me
End Sub
