Attribute VB_Name = "modMain"
Option Explicit

'List of reports that is returned on client request
'   Future versions will be served up from the database on request.
'   No BAD global structures like this.
Public asReports() As String

Sub Main()

    'Populate the reports list
    ReDim asReports(1) As String
    
    asReports(0) = "All People"
    asReports(1) = "Person"

End Sub



Public Function RemoveSpaces(sString As String)
'A function that I use to turn report names into the object
'   names so that it may be used in the createobject statement
'   when a user requests a report.  Future versions will contain
'   a translation table in an odbc data cache.

    Dim iLoop As Integer
    Dim sExamineCharacter As String
    Dim sResultString As String
    
    For iLoop = 1 To Len(sString)
        sExamineCharacter = Mid(sString, iLoop, 1)
        If sExamineCharacter <> " " Then
            sResultString = sResultString & sExamineCharacter
        End If
    Next iLoop
    
    RemoveSpaces = sResultString

End Function


