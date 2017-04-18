VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Service"
Attribute VB_Creatable = True
Attribute VB_Exposed = True
'VB Log Object - Error - 06/95
'by Ken Bergmann
'
'Purpose:
'   This module contains the log object code for logging error events.
'   These interfaces may be used by any object through the sysCon.
'
'Modification Log:
'   When    Who     What
'   ----------------------------------------------------------------------------
'   06/95   kenbe   Original Creation
'
'Usage Notes:
'   This module supports the Error Object, etc.
'
'Procedures:
'Function Init() As Boolean
'Sub PostItem(ByVal lErrNum As Long, ByVal sErrText As String, ByVal sUsrText As String)
'Sub Term()
Option Explicit

'Technical Errors
Private ErrLogging     As Boolean
Private ErrLogFNum     As Integer
Private ErrLogName     As String
Private ErrLogBack     As String
Private ErrLogSize     As Long

Public Property Get BackUpFileName() As String
On Error Resume Next
BackUpFileName = Trim$(ErrLogBack)
End Property

Public Property Let BackUpFileName(ByVal sName As String)
On Error Resume Next
ErrLogBack = sName
End Property

Public Property Get Enabled() As Boolean
On Error Resume Next
Enabled = ErrLogging
End Property

Public Property Let Enabled(ByVal iLogging As Boolean)
On Error Resume Next
ErrLogging = iLogging
End Property

Public Property Get FileName() As String
On Error Resume Next
FileName = Trim$(ErrLogName)
End Property

Public Property Let FileName(ByVal sName As String)
On Error Resume Next
ErrLogName = sName
End Property

Public Property Get MaxBytes() As Long
On Error Resume Next
MaxBytes = ErrLogSize
End Property

Public Property Let MaxBytes(ByVal lSize As Long)
On Error Resume Next
ErrLogSize = lSize
End Property

'Log Open - Error - Error - 06/95
'by Ken Bergmann
'Purpose - Opens the error log for append.
'Outputs - Boolean
Public Function Init() As Boolean
If ErrLogging Then
    On Error GoTo erropnerr
    'Try to open the file
    ErrLogFNum = FreeFile
    Open ErrLogName For Append As ErrLogFNum
    'If we are here, the log init'd okay
    Init = True
Else
    Init = True
End If
Exit Function

erropnerr:
    'Problem opening log file.
    Init = False
    Exit Function

End Function

'Log Close - Error - 06/95
'by Ken Bergmann
'Purpose - Closes the log file.
Public Sub Term()
On Error Resume Next
Close #ErrLogFNum
End Sub

'Log Error - Error - 06/95
'by Ken Bergmann
'Purpose -Writes an error string to the error log file.
'Inputs - lErrNum     Long
'         sErrText    String
'         sUsrText    String
'Calls - Log_Inf
Public Sub PostItem(ByVal lErrNum As Long, ByVal sErrText As String, ByVal sUsrText As String)
Dim bOnce As Boolean

bOnce = False
On Error GoTo errlogerr
If ErrLogging Then                                                  'Are we logging in error file??
    If Len(sErrText) > 0 Then                                       'If error text
        Print #ErrLogFNum, Format$(Now, "dd mmm yy hh:mm:ss - ");   'print timestamp
        Print #ErrLogFNum, Format$(lErrNum, "00000") & " - ";       'print error num
        Print #ErrLogFNum, sErrText & " ; " & sUsrText              'print error text
    End If
    If LOF(ErrLogFNum) >= ErrLogSize Then                               'If the err log is too big
        Close ErrLogFNum                                                'Close the file
        On Error Resume Next                                            'Don't let this stop us
        Name ErrLogName As ErrLogBack                                   'Back up the log
        On Error GoTo errlogerr                                         'Reenable the error handler
        ErrLogFNum = FreeFile
        Open ErrLogName For Output As ErrLogFNum                        'Reopen the log file
    End If
End If
Exit Sub

errlogerr:
    'There was some error writing to the file
    ErrLogFNum = FreeFile
    Open ErrLogName For Append As ErrLogFNum
    'Only retry once, then give up
    If Not bOnce Then bOnce = True: Resume
    ErrLogging = False
    Exit Sub
    
End Sub

Private Sub Class_Initialize()
On Error Resume Next
ErrLogging = False
ErrLogName = "err.log"
ErrLogBack = "err.bak"
ErrLogSize = 4000
End Sub

Private Sub Class_Terminate()
On Error Resume Next
Term
End Sub

