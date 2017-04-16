VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Broker"
Attribute VB_Creatable = True
Attribute VB_Exposed = True
Option Explicit
Public Sub GetReportsList(asReportList() As String)
'Test Harness/Stub for Reporter to develop against.

    ReDim asReportList(0) As String
    asReportList(0) = "How much are we paying for an Employee..."
    
End Sub
Public Sub GetReportDescription(sName As String, oMessage As ReportBuildMessage)
'Test Harness/Stub for Reporter to develop against.

    PopulateDummyData oMessage
    
End Sub
Private Sub PopulateDummyData(oMessage As ReportBuildMessage)
'Test Harness/Stub for Reporter to develop against.

    With oMessage
        .Header.ReportName = "The Test Report"
        .Header.ReportID = 819
        
        .Fields.Create "Employee"
            With .Fields.Item("Employee")
                .Name = "Employee"
                .AString = True
                .Description = "Employee's Name"
                .Required = True
                .Size = 35
                .Value = ""
                .SelectedFilter = "= (Equal)"
                .Filters.Create "= (Equal)"
                    With .Filters.Item("= (Equal)")
                        .Name = "= (Equal)"
                        .Description = "A Value that is Equal to the entered value."
                    End With
                .Filters.Create "Like"
                    With .Filters.Item("Like")
                        .Name = "Like"
                        .Description = "A Value that is similar to the entered value.  Wild cards can be used."
                    End With
            End With
        
        .Fields.Create "Total Yearly Compensation"
            With .Fields.Item("Total Yearly Compensation")
                .Name = "Total Yearly Compensation"
                .AString = True
                .Description = "The amount that the Employee receives in a year as total compensation"
                .Required = False
                .Size = 6
                .Value = "25000"
                .SelectedFilter = ""
                .Filters.Create "= (Equal)"
                    With .Filters.Item("= (Equal)")
                        .Name = "= (Equal)"
                        .Description = "A Value that is Equal to the entered value."
                    End With
                .Filters.Create "< (Less Than)"
                    With .Filters.Item("< (Less Than)")
                        .Name = "< (Less Than)"
                        .Description = "A Value that is Less Than the entered value."
                    End With
                .Filters.Create "> (Greater Than)"
                    With .Filters.Item("> (Greater Than)")
                        .Name = "> (Greater Than)"
                        .Description = "A Value that is Greater Than the entered value."
                    End With
            End With
            
        .Fields.Create "Job Description"
            With .Fields.Item("Job Description")
                .Name = "Job Description"
                .AString = True
                .Description = "Employee's Name"
                .Required = True
                .Size = 255
                .Value = "Building machines that go PIIING!"
                .SelectedFilter = "Like"
                .Filters.Create "= (Equal)"
                    With .Filters.Item("= (Equal)")
                        .Name = "= (Equal)"
                        .Description = "A Value that is Equal to the entered value."
                    End With
                .Filters.Create "Like"
                    With .Filters.Item("Like")
                        .Name = "Like"
                        .Description = "A Value that is similar to the entered value.  Wild cards can be used."
                    End With
            End With
    End With

End Sub

