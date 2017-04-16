Attribute VB_Name = "Module1"
Public iCurrentPage As Integer
Public iPreviousPage As Integer
Public strCaption(4) As String

'used for visited page's shape
Public Const COLOR_DARKGREY As Long = &H808080
'used for active page
Public Const COLOR_GREEN As Long = vbGreen

'prefix to the box names in the flow chart
Public Const strSHP_MAP As String = "shpMap"
'prefix to the label names in the flow chart
Public Const strLBL_MAP As String = "lblMap"

'assistant related variables
Public lwizID As Long, lprefState As Long
Public oTheBalloon As Balloon
Public bExitTglEvent As Boolean, bVis As Boolean
Public strArray(4) As String

Public Sub InitWizard()
    lwizID = 0
    lprefState = 0
    bExitTglEvent = False
    bVis = False
    
    'record user preference in the lprefState variable
    If Assistant.AssistWithWizards = True Then
        lprefState = msoWizardActActive
    Else
        lprefState = msoWizardActInactive
    End If

    'create standard balloon
    Set oTheBalloon = Assistant.NewBalloon
    With oTheBalloon
        .Heading = "Here's some help..."
        .Mode = msoModeModeless
        .Button = msoButtonSetNone
    End With

    'fill the message array
    Call fillArray

    'start the session and assign the returned value
    lwizID = Assistant.StartWizard(On:=lprefState, Callback:="wizCallback", PrivateX:=1)

    iCurrentPage = 0
    
    'caption strings for WizForm
    strCaption(0) = "Sample Wizard - Step 1 of 4"
    strCaption(1) = "Sample Wizard - Step 2 of 4"
    strCaption(2) = "Sample Wizard - Step 3 of 4"
    strCaption(3) = "Sample Wizard - Step 4 of 4"
    strCaption(4) = "Sample Wizard - Steps 1-4 are complete"

    With WizForm
        .mpgWizardPage.Value = 0
        .txtEmail.SetFocus
        .Show
    End With
End Sub

Private Sub cmdCancel_Click()
    Unload WizForm
End Sub

Private Sub cmdFinish_Click()
    Unload WizForm
End Sub

Private Sub WizForm_QueryClose(Cancel As Integer, CloseMode As Integer)
    If (CloseMode = vbFormControlMenu) Then
        Call cmdCancel_Click
    End If
End Sub

Private Sub fillArray()
    strArray(0) = "Type your e-mail name in the space provided. " & _
        "If you don't know your e-mail name, contact " & _
        "your system administrator."

    strArray(1) = "Select a color from the list provided by " & _
        "clicking the button next to the color choice."

    strArray(2) = "Type your full name and and mailing address " & _
        "in the space provided."

    strArray(3) = "All of the following personal items will be " & _
        "included. Please clear the box next to the " & _
        "items you don't want included."

    strArray(4) = "To change any settings, click Back."
End Sub

Private Sub wizCallback(lButton, lpriv)
    Select Case lButton
        Case msoWizardMsgLocalStateOff
            lprefState = msoWizardActInactive
            If bVis Then
                oTheBalloon.Close
                bVis = False
            End If
            If WizForm.tglAssistant.Value Then
                bExitTglEvent = True
                WizForm.tglAssistant.Value = False
            End If
            
        Case msoWizardMsgShowHelp
            lprefState = msoWizardActActive
            If bVis Then
                Exit Sub
            Else
                oTheBalloon.Text = strArray(iCurrentPage)
                oTheBalloon.Show
                bVis = True
            End If
            If Not (WizForm.tglAssistant.Value) Then
                bExitTglEvent = True
                WizForm.tglAssistant.Value = True
            End If
    End Select
End Sub

