VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Service"
Attribute VB_Creatable = True
Attribute VB_Exposed = True
'VB Log Object - Event - 06/95
'by Ken Bergmann
'
'Purpose:
'   This module contains the log object code for logging informational events.
'   These interfaces may be used by any object through the sysCon.
'
'Modification Log:
'   When    Who     What
'   ----------------------------------------------------------------------------
'   06/95   kenbe   Original Creation
'
'Usage Notes:
'   This module supports the SysCon Object, etc.
'
'Procedures:
'Function FormatItem(ByVal sText As String) As String
'Function Init() As Boolean
'Sub PostItem (ByVal sInfText As String)
'Sub Term()
Option Explicit

'Informational Messages
Private InfLogging     As Boolean
Private InfLogFNum     As Integer
Private InfLogName     As String
Private InfLogBack     As String
Private InfLogSize     As Long

Private Sub Class_Initialize()
On Error Resume Next
InfLogging = False
InfLogName = "inf.log"
InfLogBack = "inf.bak"
InfLogSize = 4000
End Sub

Private Sub Class_Terminate()
On Error Resume Next
Term
End Sub

'Log Close - Event - 06/95
'by Ken Bergmann
'Purpose - Closes the event log.
Public Sub Term()
On Error Resume Next
Close #InfLogFNum
End Sub

'Log Format String - Event - 06/95
'by Ken Bergmann
'Purpose - Formats a log entry .
'Inputs - sText   String
'Outputs - String
Public Function FormatItem(ByVal sText As String) As String
On Error Resume Next
Dim sTemp As String * 35

LSet sTemp = Trim$(sText)
FormatItem = sTemp & " - "
End Function

'Log Open - Event - 06/95
'by Ken Bergmann
'Purpose - Opens the information log for append.
'Outputs - Boolean
Public Function Init() As Boolean
'Set up log objects info log
If InfLogging Then
    On Error GoTo infopnerr
    'Try to open the file
    InfLogFNum = FreeFile
    Open InfLogName For Append As InfLogFNum
    'If we are here, the log init'd okay
    Init = True
Else
    Init = True
End If
Exit Function

infopnerr:
    'Problem opening log file.
    Init = False
    Exit Function

End Function

'Log Information - Event - 06/95
'by Ken Bergmann
'Purpose - Writes information strings to the information log.
'Inputs - sInfText    String
Public Sub PostItem(ByVal lEvtNum As Long, ByVal sEvtText As String, ByVal sInfText As String)
Dim bOnce As Boolean

bOnce = False
On Error GoTo inflogerr
If InfLogging Then                                                          'Are we logging in inf file??
    If Len(sInfText) > 0 Then                                               'If user text
        Print #InfLogFNum, FormatItem(Format$(Now, "dd mmm yy hh:mm:ss"));   'print timestamp
        Print #InfLogFNum, FormatItem(sEvtText);                             'print the Event Descriptor
        Print #InfLogFNum, sInfText                                         'print user text
    End If
    If LOF(InfLogFNum) >= InfLogSize Then                                       'If the inf log is too big
        Close InfLogFNum                                                        'Close the file
        On Error Resume Next                                                    'Don't let this stop us
        Name InfLogName As InfLogBack                                           'Back up the log
        On Error GoTo inflogerr                                                 'Reenable the error handler
        InfLogFNum = FreeFile
        Open InfLogName For Output As InfLogFNum                                'Reopen the log file
    End If
End If
Exit Sub

inflogerr:
    'There was some error writing to the file
    InfLogFNum = FreeFile
    Open InfLogName For Append As InfLogFNum
    'Only retry once, then give up
    If Not bOnce Then bOnce = True: Resume
    InfLogging = False
    Exit Sub

End Sub

Public Property Get BackUpFileName() As String
On Error Resume Next
BackUpFileName = Trim$(InfLogBack)
End Property

Public Property Let BackUpFileName(ByVal sName As String)
On Error Resume Next
InfLogBack = sName
End Property

Public Property Get Enabled() As Boolean
On Error Resume Next
Enabled = InfLogging
End Property

Public Property Let Enabled(ByVal bLogging As Boolean)
On Error Resume Next
InfLogging = bLogging
End Property

Public Property Get FileName() As String
On Error Resume Next
FileName = Trim$(InfLogName)
End Property

Public Property Let FileName(ByVal sName As String)
On Error Resume Next
InfLogName = sName
End Property

Public Property Get MaxBytes() As Long
On Error Resume Next
MaxBytes = InfLogSize
End Property

Public Property Let MaxBytes(ByVal lSize As Long)
On Error Resume Next
InfLogSize = lSize
End Property


