VERSION 4.00
Begin VB.Form frmRequest 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Request"
   ClientHeight    =   2985
   ClientLeft      =   8430
   ClientTop       =   10260
   ClientWidth     =   3675
   Height          =   3390
   Icon            =   "frmRequest.frx":0000
   Left            =   8370
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MDIChild        =   -1  'True
   MinButton       =   0   'False
   ScaleHeight     =   2985
   ScaleWidth      =   3675
   Top             =   9915
   Width           =   3795
   Begin VB.CommandButton btnRequestRequirements 
      Caption         =   "Request Requirements"
      Height          =   495
      Left            =   180
      TabIndex        =   6
      Top             =   2190
      Width           =   1800
   End
   Begin VB.CommandButton btnRequestReport 
      Caption         =   "Request Report"
      Height          =   495
      Left            =   2130
      TabIndex        =   5
      Top             =   2175
      Width           =   1305
   End
   Begin VB.Frame Frame2 
      Caption         =   "Report Specification"
      Height          =   1080
      Left            =   165
      TabIndex        =   2
      Top             =   945
      Width           =   3270
      Begin VB.TextBox txtDataRequired 
         Height          =   315
         Left            =   150
         TabIndex        =   3
         Top             =   585
         Width           =   2955
      End
      Begin VB.Label lblDataRequired 
         Caption         =   "Data Required"
         Height          =   315
         Left            =   150
         TabIndex        =   4
         Top             =   315
         Width           =   3060
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "Report"
      Height          =   765
      Left            =   150
      TabIndex        =   0
      Top             =   90
      Width           =   3300
      Begin VB.ComboBox cbolReports 
         Height          =   315
         Left            =   150
         Style           =   2  'Dropdown List
         TabIndex        =   1
         Top             =   270
         Width           =   3015
      End
   End
End
Attribute VB_Name = "frmRequest"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

'The list of reports is being passed to us from the Broker as
'   an array of strings.  It is probably not necessary for it to
'   have form level scope, but here it is for now.
Dim asReports() As String
'This is the Requirements object that is passed to us to set
'   our request for information environment locally.  In final
'   versions we would add its object library to the References
'   section and do an early binding dimming it as its class
Dim oRequirements As Object

Private Sub btnRequestReport_Click()

    'This is the call back class
    Dim oNotify As New clsNotify

    'Submit the filled requirements and the call back for processing
    oRequestBroker.ReportRequest oRequirements, oNotify
    
    'Wait for the processing to be completed
    Do While Not oNotify.Finished
        'For now we are synchronous so we wait.
        'In future versions we may allow the user to continue working
        '   in the application by using a do events.
        '   That way many reports could be submitted and the viewers
        '   would just start popping up as they completed.
    Loop

    'The report is done so load the viewer with the report
    Load frmViewer
    frmViewer.SourceDoc oNotify.Report

End Sub


Private Sub btnRequestRequirements_Click()

    'Get the request requirements object by telling the Broker what report we want
    oRequestBroker.RequestRequirements cbolReports.Text, oRequirements
    
    'The gathering of the requirements is way simple here.  A future version
    '   will have a structured meta information methodology that will allow
    '   a local engine to generate a wizard-like interface for requirements input.
    lblDataRequired.Caption = oRequirements.Caption

End Sub

Private Sub Form_Load()

    'Request the list of available reports for the Broker
    oRequestBroker.ReportList asReports()

    'Put the list of reports into the combo box
    Dim iLoop As Integer
    For iLoop = 0 To UBound(asReports)
        cbolReports.AddItem asReports(iLoop)
    Next iLoop

    'Display the request form
    Me.Show

End Sub

Private Sub txtDataRequired_Change()

    'When we put in required text, set the request object.  This is currently not
    '   used and will be implemented as a wizard with great flexibility
    oRequirements.Value = txtDataRequired

End Sub


