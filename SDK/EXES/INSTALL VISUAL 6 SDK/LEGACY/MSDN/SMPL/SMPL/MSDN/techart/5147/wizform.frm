VERSION 5.00
Begin {C62A69F0-16DC-11CE-9E98-00AA00574A4F} WizForm 
   Caption         =   "Sample Wizard - Step 1 of 4"
   ClientHeight    =   5100
   ClientLeft      =   45
   ClientTop       =   390
   ClientWidth     =   7800
   OleObjectBlob   =   "WizForm.frx":0000
   StartUpPosition =   1  'CenterOwner
End
Attribute VB_Name = "WizForm"
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub cmdBack_Click()
    If iCurrentPage <> 0 Then
        iPreviousPage = iCurrentPage
        WizForm.mpgWizardPage.Value = iCurrentPage - 1
    End If
End Sub

Private Sub cmdNext_Click()
    If iCurrentPage < 4 Then
        iPreviousPage = iCurrentPage
        WizForm.mpgWizardPage.Value = iCurrentPage + 1
    End If
End Sub

Private Sub cmdCancel_Click()
    If bVis Then oTheBalloon.Close
    Assistant.EndWizard WizardID:=lwizID, varfSuccess:=False
    Unload WizForm
End Sub

Private Sub cmdFinish_Click()
    If bVis Then oTheBalloon.Close
    ' end the session and unload the wizard
    Assistant.EndWizard WizardID:=lwizID, varfSuccess:=True
    Unload WizForm
End Sub

Private Sub MpgWizardPage_Change()
    With WizForm
        iCurrentPage = .mpgWizardPage.Value

        If bVis Then
            oTheBalloon.Close
            oTheBalloon.Text = strArray(iCurrentPage)
            oTheBalloon.Show
        End If
    
        .Caption = strCaption(iCurrentPage)
    
        'deselect current flow chart marker
        .Controls(strSHP_MAP & iPreviousPage).BackColor = COLOR_DARKGREY
        .Controls(strLBL_MAP & iPreviousPage).FontBold = False
         
        'select new flow chart marker
        .Controls(strSHP_MAP & iCurrentPage).BackColor = COLOR_GREEN
        .Controls(strLBL_MAP & iCurrentPage).FontBold = True
    
        Select Case iCurrentPage
            Case 0
                .cmdBack.Enabled = False
                .cmdNext.Enabled = True
            Case 1, 2, 3
                .cmdBack.Enabled = True
                .cmdNext.Enabled = True
            Case 4
                .cmdBack.Enabled = True
                .cmdNext.Enabled = False
        End Select
    End With
End Sub

Private Sub lblMap0_Click()
    iPreviousPage = iCurrentPage
    WizForm.mpgWizardPage.Value = 0
End Sub

Private Sub lblMap1_Click()
    iPreviousPage = iCurrentPage
    WizForm.mpgWizardPage.Value = 1
End Sub

Private Sub lblMap2_Click()
    iPreviousPage = iCurrentPage
    WizForm.mpgWizardPage.Value = 2
End Sub

Private Sub lblMap3_Click()
    iPreviousPage = iCurrentPage
    WizForm.mpgWizardPage.Value = 3
End Sub

Private Sub lblMap4_Click()
    iPreviousPage = iCurrentPage
    WizForm.mpgWizardPage.Value = 4
End Sub

Private Sub shpMap0_Click()
    iPreviousPage = iCurrentPage
    WizForm.mpgWizardPage.Value = 0
End Sub

Private Sub shpMap1_Click()
    iPreviousPage = iCurrentPage
    WizForm.mpgWizardPage.Value = 1
End Sub

Private Sub shpMap2_Click()
    iPreviousPage = iCurrentPage
    WizForm.mpgWizardPage.Value = 2
End Sub

Private Sub shpMap3_Click()
    iPreviousPage = iCurrentPage
    WizForm.mpgWizardPage.Value = 3
End Sub

Private Sub shpMap4_Click()
    iPreviousPage = iCurrentPage
    WizForm.mpgWizardPage.Value = 4
End Sub

Private Sub tglAssistant_Click()
    ' assistant isn’t running, exit the procedure
    If lwizID = 0 Then Exit Sub
         
    ' exit sub if Click event was triggered by WizCallback routine
    If bExitTglEvent Then
        bExitTglEvent = False
        Exit Sub
    End If

    ' help is inactive (not showing). user pressed toggle button to make help appear
    If lprefState = msoWizardActInactive Then
        If tglAssistant.Value Then
            bExitTglEvent = True
            tglAssistant.Value = False
        End If
        Assistant.ActivateWizard WizardID:=lwizID, Act:=msoWizardActActive
    ' help is active (showing). user pressed toggle button to dismiss help
    ElseIf lprefState = msoWizardActActive Then
        Assistant.ActivateWizard WizardID:=lwizID, Act:=msoWizardActInactive
    End If
End Sub

Private Sub UserForm_QueryClose(Cancel As Integer, CloseMode As Integer)
    If (CloseMode = vbFormControlMenu) Then
        Call cmdCancel_Click
    End If
End Sub
