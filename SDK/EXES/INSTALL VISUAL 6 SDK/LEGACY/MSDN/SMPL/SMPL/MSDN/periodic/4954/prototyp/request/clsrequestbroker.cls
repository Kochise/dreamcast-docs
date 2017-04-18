VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "clsRequestBroker"
Attribute VB_Creatable = True
Attribute VB_Exposed = True
Option Explicit

'Private requirements reference
Private oRequirements As clsRequirements

Public Sub ReportList(asReportsIN() As String)
'Populates a request array for reports

    Dim iLoop As Integer
    Dim iUpperLimit As Integer
    
    iUpperLimit = UBound(asReports)
    ReDim asReportsIN(iUpperLimit)
    
    For iLoop = 0 To iUpperLimit
        asReportsIN(iLoop) = asReports(iLoop)
    Next iLoop

End Sub

Public Sub ReportRequest(oRequirementsIN As Object, oNotify As Object)
'Process the request for a report

    'Create a report object and class  (lest we think there is too much
    '   stuff going on for what we are doing, let us not forget that this
    '   is the beginning structure of the app seeing its way through the
    '   prototype stage)
    Dim oReportObject As Object
    Dim oReport As New clsReport
    
    'Create the Report requested
    Set oReportObject = CreateObject(oRequirementsIN.ReportObjectName & ".Report")
    
    'Request that the report be generated
    oReportObject.Request oRequirementsIN, oReport
    
    'Notify the client we are done and pass the results
    oNotify.SetFinished oReport.FileName

End Sub


Public Sub RequestRequirements(sReportName As String, oRequirementsOUT As Object)
'Build the requirements structure for the report requested by the client.  This
'   will be come a much more comprehensive structure for use by a client side
'   wizard.

    'Set the Requirements write-once properties
    oRequirements.ReportName = sReportName
    oRequirements.ReportObjectName = RemoveSpaces(sReportName)
    
    'Simple data structure population.  These will be stored in an odbc data
    '   base when the wizard is on the scene
    Select Case sReportName
        Case asReports(0)
            oRequirements.Caption = "No Data Required"
        Case asReports(1)
            oRequirements.Caption = "Person's Name"
    End Select

    Set oRequirementsOUT = oRequirements
    
End Sub


Private Sub Class_Initialize()

    'Instantiate here, not in declarations section, to avoid problems
    Set oRequirements = New clsRequirements
    
End Sub


