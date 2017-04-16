VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Service"
Attribute VB_Creatable = True
Attribute VB_Exposed = True
'VB Component - Error Object - 06/95
'by Ken Bergmann
'
'Application Error Object
'
'Purpose:
'   This module contains the error object code. These interfaces provide generic
'   error capture and reporting and is used by all layers.
'
'Modification Log:
'   When    Who     What
'   ----------------------------------------------------------------------------
'   9/94    kenbe   Original Creation
'
'Usage Notes:
'   This module relies on the Log Object for error logging.
'   First set the Log object reference
'   Then call init.
'   Use the Logging property to see if logging is being done.
'
'Procedures:
'Function Init() as Boolean
'Sub Display (ByVal iType As Integer, ByVal sPrefix As String, ByVal sSuffix As String)
'Function Query (ByVal iType As Integer, ByVal sPrefix As String, ByVal sSuffix As String) As Integer
'Sub Localize ()
'Sub Raise (ByVal fLocalize As Integer, ByVal lErrNum As Long, ByVal sErrText As String, ByVal sUsrText As String)
'Sub Term()
Option Explicit

Private objLogErr   As LayerLogError.Service
Private objLogEvt   As LayerLogInformation.Service
Private objRes      As LayerErrorResource.Resource

Private DoLogErr    As Boolean
Private DoLogEvt    As Boolean

Private Title   As String
Private ErrNum  As Long
Private UsrNum  As Long
Private ErrText As String
Private UsrText As String
Private DefText As String

Public Property Get DefaultText() As String
On Error Resume Next
DefaultText = Trim$(DefText)
End Property

Public Property Let DefaultText(ByVal sText As String)
On Error Resume Next
DefText = Trim$(sText)
End Property

Public Property Let DisplayTitle(ByVal sText As String)
On Error Resume Next
Title = Trim$(sText)
End Property

Public Property Set LogErr(objSysLog As LayerLogAll.Services)
On Error GoTo leterrhnderr
Set objLogErr = objSysLog.Error
Exit Property

leterrhnderr:
    Err.Raise vbObjectError + Err.Number, "LayerError.Service"
    Exit Property
    
End Property

Public Property Set LogEvt(objSysLog As LayerLogAll.Services)
On Error GoTo letinfhnderr
Set objLogEvt = objSysLog.Event
Exit Property

letinfhnderr:
    Err.Raise vbObjectError + Err.Number, "LayerError.Service"
    Exit Property
    
End Property

Public Function Init() As Boolean
On Error GoTo initerr
If objLogErr.Init Then
    DoLogErr = True
    Init = True
Else
    DoLogErr = False
    Init = False
End If
On Error Resume Next
Set objRes = New LayerErrorResource.Resource
Exit Function

initerr:
    DoLogErr = False
    Init = False
    Exit Function
    
End Function

Public Property Get Logging() As Boolean
On Error Resume Next
Logging = DoLogErr
End Property

'Set Error - Error Object - 06/95
'by Ken Bergmann
'Purpose - Sets the current error information
'Inputs - fLocalize       Integer
'         lErrNum         Long
'         sErrText        String
'         sUsrText        String
'Calls - Localize
'        objLogErr.PostItem
'        objLogEvt.PostItem
Public Sub Raise(ByVal fLocalize As Integer, ByVal lErrNum As Long, ByVal sErrText As String, ByVal sUsrText As String)
On Error Resume Next
'Fill in the information
ErrNum = lErrNum
If fLocalize Then
    Localize
Else
    'If no user text, substitute default text
    If Len(sUsrText) Then
        UsrText = Trim$(sUsrText)
    Else
        UsrText = DefText
    End If
    'If no text, substitute default text
    If Len(sErrText) Then
        ErrText = Trim$(sErrText)
    Else
        ErrText = UsrText
    End If
End If

If DoLogErr Then
    'Call the log object to record the errors
    objLogErr.PostItem ErrNum, ErrText, UsrText
    If DoLogEvt Then objLogEvt.PostItem ErrNum, ErrText, UsrText
End If
End Sub

'Localize - Error Object - 06/95
'by Ken Bergmann
'Purpose - Allows the application to introduce code
'          to localize errors from external source.
Sub Localize()
On Error Resume Next
objRes.Localize ErrNum, UsrText
End Sub

'Error Display w/ Return - Error Object - 06/95
'by Ken Bergmann
'Purpose - Displays errors stored in the Error Object.
'          Returns the choice of the buttons they chose.
'Inputs - iType       Integer
'         sPrefix     String
'         sSuffix     String
'Outputs - Integer
Function Query(ByVal iType As Integer, ByVal sPrefix As String, ByVal sSuffix As String) As Integer
Dim sMsgText As String

On Error Resume Next
'Clean up strings
sPrefix = Trim$(sPrefix)
sSuffix = Trim$(sSuffix)
If Len(sPrefix) Then sMsgText = sPrefix                                     'Prefix??
If Len(UsrText) Then                                                        'User Text??
    sMsgText = sMsgText & Chr$(13) & Chr$(10) & UsrText                     'Use User Text
Else
    If Len(ErrText) Then                                                    'Raw Text??
        sMsgText = sMsgText & Chr$(13) & Chr$(10) & ErrText                 'Use Raw Text
    Else
        sMsgText = sMsgText & Chr$(13) & Chr$(10) & DefText                 'Use Default Text
    End If
End If
If Len(sSuffix) Then sMsgText = sMsgText & Chr$(13) & Chr$(10) & sSuffix    'Suffix??
'Reset MousePointer
Screen.MousePointer = vbDefault
'Show the text
Query = MsgBox(sMsgText, iType, Title)
End Function

'Error Display - Error Object - 06/95
'by Ken Bergmann
'Purpose - Displays errors stored in the error object.
'Inputs - iType       Integer
'         sPrefix     String
'         sSuffix     String
Public Sub Display(ByVal iType As Integer, ByVal sPrefix As String, ByVal sSuffix As String)
Dim sMsgText As String

On Error Resume Next
'Clean up strings
sPrefix = Trim$(sPrefix)
sSuffix = Trim$(sSuffix)
If Len(sPrefix) Then sMsgText = sPrefix                                     'Prefix??
If Len(UsrText) Then                                                        'User Text??
    sMsgText = sMsgText & Chr$(13) & Chr$(10) & UsrText                     'Use User Text
Else
    If Len(ErrText) Then                                                    'Raw Text??
        sMsgText = sMsgText & Chr$(13) & Chr$(10) & ErrText                 'Use Raw Text
    Else
        sMsgText = sMsgText & Chr$(13) & Chr$(10) & DefText                 'Use Default Text
    End If
End If
If Len(sSuffix) Then sMsgText = sMsgText & Chr$(13) & Chr$(10) & sSuffix    'Suffix??

'Reset MousePointer
Screen.MousePointer = vbDefault
'Show the text
MsgBox sMsgText, iType, Title
End Sub

Public Property Get DisplayTitle() As String
On Error Resume Next
DisplayTitle = Trim$(Title)
End Property

Public Property Get LastErrNum() As Long
On Error Resume Next
LastErrNum = ErrNum
End Property

Public Property Get LastErrText() As String
On Error Resume Next
LastErrText = ""
If Len(UsrText) Then                                     'User Text??
    LastErrText = Trim$(UsrText)                            'Use User Text
Else
    If Len(ErrText) Then
        LastErrText = "An Unidentified error has occured."
    Else
        LastErrText = Trim$(ErrText)   'Use Raw Text
    End If
End If
End Property

Public Property Get LastUsrNum() As Long
On Error Resume Next
LastUsrNum = UsrNum
End Property

Public Property Let LastUsrNum(ByVal lErr As Long)
On Error Resume Next
UsrNum = lErr
End Property

Public Sub Term()
On Error Resume Next
Set objLogErr = Nothing
Set objLogEvt = Nothing
Set objRes    = Nothing
End Sub
