Attribute VB_Name = "MainModule"
Option Explicit

'<Constant>-----------------------------------------------------
Public Const xagSystemID    As Long = 109657
'</Constant>----------------------------------------------------

'<Public>-------------------------------------------------------
Public SystemName           As String
'</Public>------------------------------------------------------

Public Sub Main()
    Dim ShowTips    As Boolean
    Dim LogErrors   As Boolean
    Dim ButtonText  As Boolean
    Dim ExtraHelp   As Boolean

    SystemName = "Test Expert Agent Add-In Example"

    '---- get the options
    frmOptions.Show vbModal
    If (Not frmOptions.PressedOK) Then Exit Sub
    ShowTips = (frmOptions.optShowTips = vbChecked)
    LogErrors = (frmOptions.optLogErrors = vbChecked)
    ButtonText = (frmOptions.optButtonText = vbChecked)
    ExtraHelp = (frmOptions.optExtraHelp = vbChecked)

End Sub

Public Sub CenterForm(ThisForm As Form)
'---------------------------------------------------
'<Purpose> centers a form on the screen
'---------------------------------------------------

    ThisForm.Move (Screen.Width / 2) - (ThisForm.Width / 2), (Screen.Height / 2) - (ThisForm.Height / 2)

End Sub

Public Sub NotDone()
'---------------------------------------------------
'<Purpose> generic message for incomplete procs
'---------------------------------------------------
    
    MsgBox LoadResString(resmsgNotDone), vbOKOnly + vbInformation, LoadResString(resappName)

End Sub

Public Sub SetEdit(ThisTextBox As TextBox)
'---------------------------------------------------------------
'<Purpose> selects all the text in a TextBox
'---------------------------------------------------------------

    ThisTextBox.SelStart = 0
    ThisTextBox.SelLength = Len(ThisTextBox)
    
End Sub

