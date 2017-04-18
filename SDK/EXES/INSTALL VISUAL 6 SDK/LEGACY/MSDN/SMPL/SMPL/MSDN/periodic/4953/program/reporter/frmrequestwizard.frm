VERSION 4.00
Begin VB.Form frmRequestWizard 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Request Wizard"
   ClientHeight    =   5085
   ClientLeft      =   10560
   ClientTop       =   8865
   ClientWidth     =   6570
   Height          =   5490
   Left            =   10500
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MDIChild        =   -1  'True
   MinButton       =   0   'False
   ScaleHeight     =   5085
   ScaleWidth      =   6570
   Top             =   8520
   Width           =   6690
   Begin Threed.SSPanel pnlFieldData 
      Height          =   4455
      Left            =   60
      TabIndex        =   2
      Top             =   60
      Width           =   6465
      _Version        =   65536
      _ExtentX        =   11404
      _ExtentY        =   7858
      _StockProps     =   15
      BackColor       =   12632256
      BevelOuter      =   1
      Begin VB.TextBox txtValue 
         Height          =   300
         Left            =   195
         TabIndex        =   9
         Top             =   1320
         Visible         =   0   'False
         Width           =   6075
      End
      Begin VB.Label lblFieldDescription 
         Caption         =   "Field Description"
         Height          =   285
         Left            =   300
         TabIndex        =   5
         Top             =   375
         Width           =   6060
      End
      Begin VB.Label lblFieldName 
         Caption         =   "Field Name"
         BeginProperty Font 
            name            =   "MS Sans Serif"
            charset         =   0
            weight          =   400
            size            =   13.5
            underline       =   0   'False
            italic          =   0   'False
            strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   120
         TabIndex        =   4
         Top             =   45
         Width           =   3570
      End
      Begin Threed.SSOption optFilterType 
         Height          =   195
         Index           =   0
         Left            =   120
         TabIndex        =   3
         Top             =   825
         Width           =   6210
         _Version        =   65536
         _ExtentX        =   10954
         _ExtentY        =   344
         _StockProps     =   78
         Caption         =   "Filter Type"
         Value           =   -1  'True
         Font3D          =   2
      End
   End
   Begin Threed.SSPanel pnlPickReport 
      Height          =   4350
      Left            =   45
      TabIndex        =   6
      Top             =   45
      Width           =   6465
      _Version        =   65536
      _ExtentX        =   11404
      _ExtentY        =   7673
      _StockProps     =   15
      BackColor       =   12632256
      BevelOuter      =   1
      Begin VB.ComboBox cbReportList 
         Height          =   3630
         Left            =   105
         Sorted          =   -1  'True
         Style           =   1  'Simple Combo
         TabIndex        =   8
         Top             =   555
         Width           =   6210
      End
      Begin VB.Label Label2 
         Alignment       =   2  'Center
         Caption         =   "Pick a Report"
         BeginProperty Font 
            name            =   "MS Sans Serif"
            charset         =   0
            weight          =   400
            size            =   13.5
            underline       =   0   'False
            italic          =   0   'False
            strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   120
         TabIndex        =   7
         Top             =   45
         Width           =   6240
      End
   End
   Begin ComctlLib.StatusBar sbMain 
      Align           =   2  'Align Bottom
      Height          =   300
      Left            =   0
      TabIndex        =   1
      Top             =   4545
      Width           =   6570
      _Version        =   65536
      _ExtentX        =   11589
      _ExtentY        =   529
      _StockProps     =   68
      AlignSet        =   -1  'True
      SimpleText      =   ""
      NumPanels       =   3
      i1              =   "frmRequestWizard.frx":0000
      i2              =   "frmRequestWizard.frx":010C
      i3              =   "frmRequestWizard.frx":024A
   End
   Begin ComctlLib.ProgressBar pbMain 
      Align           =   2  'Align Bottom
      Height          =   240
      Left            =   0
      TabIndex        =   0
      Top             =   4845
      Width           =   6570
      _Version        =   65536
      _ExtentX        =   11589
      _ExtentY        =   423
      _StockProps     =   192
      Appearance      =   1
      Max             =   2
      Min             =   1
   End
End
Attribute VB_Name = "frmRequestWizard"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

Private asReportsList() As String
'Private oMessage As Object 'Later change to type to get early binding
Private oMessage As New ReportBuildMessage
Private fiSelectedFilter As Integer
Private Sub CollectFieldData(iFieldNumber As Integer)
'Move collected interactions from visual and place in the message classes

    Dim oField As Object
    
    Set oField = oMessage.Fields.Item(iFieldNumber)
    oField.Value = txtValue.Text
    oField.SelectedFilter = optFilterType(fiSelectedFilter).Caption
    
    Dim iLoop As Integer
    For iLoop = 1 To oField.Filters.Count - 1
        Unload optFilterType(iLoop)
    Next iLoop

End Sub

Private Sub DisplayFieldData(iFieldNumber As Integer)
'Move message classes information into the visual controls

    Dim oField As Object
    Dim iFilters As Integer
    Dim iFoundFilter As Integer
    
    Set oField = oMessage.Fields.Item(iFieldNumber)
    iFoundFilter = 0

    lblFieldName.Caption = oField.Name
    lblFieldDescription.Caption = oField.Description
    
    iFilters = oField.Filters.Count
    
    Dim iLoop As Integer
    For iLoop = 1 To iFilters
        If iLoop > 1 Then
            Load optFilterType(iLoop - 1)
            optFilterType(iLoop - 1).Top = optFilterType(iLoop - 2).Top + optFilterType(iLoop - 2).Height + 100
            optFilterType(iLoop - 1).Visible = True
        End If
        optFilterType(iLoop - 1).Caption = oField.Filters.Item(iLoop).Name
        If oField.Filters.Item(iLoop).Name = oField.SelectedFilter Then
            iFoundFilter = iLoop - 1
        End If
    Next iLoop
    
    optFilterType(iFoundFilter).Value = True
    
    txtValue.Top = optFilterType(iLoop - 2).Top + optFilterType(iLoop - 2).Height + 300
    txtValue.Visible = True
    txtValue.Left = optFilterType(iLoop - 2).Left
    txtValue.Text = oField.Value
    
End Sub

Private Sub LoadReportList()
'Display the report list

    'Set Back off initially
    sbMain.Panels.Item(2).Visible = False
        
    oRequestBroker.GetReportsList asReportsList
    Dim iLoop As Integer
    For iLoop = 0 To UBound(asReportsList)
        cbReportList.AddItem asReportsList(iLoop)
    Next iLoop

End Sub

Private Sub cbReportList_KeyPress(KeyAscii As Integer)
'Ignore all input

    KeyAscii = 0

End Sub


Private Sub Form_Load()

    'Initialize
    fiSelectedFilter = 0
    pnlFieldData.Visible = False
    
    'Set progress bar to the first count
    'Assume at least two forms
    pbMain.Max = 2
    pbMain.Value = 1
    
    'Load ReportList
    LoadReportList

End Sub


Private Sub optFilterType_Click(Index As Integer, Value As Integer)
'Display helpful text

    'To Keep track what we've selected
    fiSelectedFilter = Index
    
    sbMain.Font.Size = 8
    sbMain.Panels.Item(1).Text = oMessage.Fields.Item(lblFieldName.Caption).Filters.Item(Index + 1).Description

End Sub


Private Sub sbMain_PanelClick(ByVal Panel As Panel)
'Handle interaction with the status bar

    Select Case Panel.Index
        'Back button
        Case 2
            'Display button action
            Panel.Bevel = 1
            DoEvents
            Sleep 250
            Panel.Bevel = 2
            
            'Collect Field Data
            CollectFieldData pbMain.Value - 1
            
            'Move, use pb as locator
            pbMain.Value = pbMain.Value - 1
            
            'Turn Back off if we just entered the first screen
            If pbMain.Value = 1 Then
                Panel.Visible = False
                pnlFieldData.Visible = False
                pnlPickReport.Visible = True
            End If
            
            'If pbMain.Value > 1 then
            If pbMain.Value > 1 Then
                DisplayFieldData pbMain.Value - 1
            End If

            'Change Finish to Next on backing off last screen
            If pbMain.Value = pbMain.Max - 1 Then
                sbMain.Panels.Item(3).Text = "Next >>"
            End If
            
            'We are in the fields
            If pbMain.Value > 1 Then
                  
            End If
        'Forward button
        Case 3
            'Display button action
            Panel.Bevel = 1
            DoEvents
            Sleep 250
            Panel.Bevel = 2
    
            'Finished
            If pbMain.Value = pbMain.Max Then
                Exit Sub
            End If
                    
            'Collect Field Data
            If pbMain.Value > 1 Then
                CollectFieldData pbMain.Value - 1
            End If
            
            'Turn Back on if we just left the first screen
            If pbMain.Value = 1 Then
                If cbReportList.Text = "" Then
                    Exit Sub
                Else
                    Set oMessage = Nothing
                    oRequestBroker.GetReportDescription cbReportList.Text, oMessage
                    pbMain.Max = oMessage.Fields.Count + 1
                End If
                sbMain.Panels.Item(2).Visible = True
                pnlPickReport.Visible = False
                pnlFieldData.Visible = True
            End If
             
            'Move, use pb as locator
            pbMain.Value = pbMain.Value + 1
           
            'If pbMain.Value > 1 then
            DisplayFieldData pbMain.Value - 1
            
            'Change Next to Finish on entereing last screen
            If pbMain.Value = pbMain.Max Then
                sbMain.Panels.Item(3).Text = "Finished"
            End If
            
    End Select

End Sub
