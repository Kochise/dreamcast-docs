VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Report"
Attribute VB_Creatable = True
Attribute VB_Exposed = True
Option Explicit

Public Sub Request(oRequirementsIN As Object, oReportIN As Object)

    'Processing will take place here (I've the strong urge to say
    '   "This part is obvious and is left for the student to explore at home."
    '   Hee hee.  This will be the heart of the DataMart services in the
    '   coming articles.

    'Result File name ready for viewing
    oReportIN.SetFileName "REPORT1.XLS"

End Sub


