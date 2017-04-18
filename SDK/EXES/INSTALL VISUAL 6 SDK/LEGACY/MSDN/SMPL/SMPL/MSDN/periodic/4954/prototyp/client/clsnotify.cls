VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "clsNotify"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

'Our internal variables are private.  They are set by properties and methods
Private bFinished As Boolean
Private sReport As String
Public Function SetFinished(sReportIN As String) As Boolean
    
    'This is the function that the Broker calls to let us know
    '   it is finished and what the report is
    sReport = sReportIN
    bFinished = True

End Function


Private Sub Class_Initialize()

    'When the class is instantiated we set default values
    bFinished = False

End Sub



Public Property Get Finished()

    'This is the property that we keep checking to see if
    '   the Broker is done.
    Finished = bFinished

End Property



Public Property Get Report()
    
    'This is the property that the Request generation form
    '   will call after finish is set to get the report name
    Report = sReport
    
End Property


