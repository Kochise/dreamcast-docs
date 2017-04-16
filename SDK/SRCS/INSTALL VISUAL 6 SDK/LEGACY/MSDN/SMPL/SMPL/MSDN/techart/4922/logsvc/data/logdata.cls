VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Service"
Attribute VB_Creatable = True
Attribute VB_Exposed = True
'VB Log Object - Trans - 06/95
'by Ken Bergmann
'
'Purpose:
'   This module contains the log object code for logging transaction events.
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
'Function Init () As Boolean
'Sub PostItem (ByVal sSQLText As String)
'Sub Term()
Option Explicit

'Pure SQL Dump
Private SQLLogging     As Boolean
Private SQLLogFNum     As Integer
Private SQLLogName     As String
Private SQLLogBack     As String
Private SQLLogSize     As Long

Private Sub Class_Initialize()
On Error Resume Next
SQLLogging = False
SQLLogName = "sql.log"
SQLLogBack = "sql.bak"
SQLLogSize = 4000
End Sub

Private Sub Class_Terminate()
On Error Resume Next
Term
End Sub

'Log Format String - Trans - 06/95
'by Ken Bergmann
'Purpose - Formats a log entry.
'Inputs - sText   String
'Outputs - String
Public Function FormatItem(ByVal sText As String) As String
On Error Resume Next
Dim sTemp As String * 35

LSet sTemp = Trim$(sText)
FormatItem = sTemp & " - "
End Function

'Log Open SQL - Trans - 06/95
'by Ken Bergmann
'Purpose - Opens the SQL log for append.
'Outputs - Boolean
Public Function Init() As Boolean
If SQLLogging Then
    On Error GoTo SQLopnerr
    'Try to open the file
    SQLLogFNum = FreeFile
    Open SQLLogName For Append As SQLLogFNum
    'If we are here, the log init'd okay
    Init = True
Else
    Init = True
End If
Exit Function

SQLopnerr:
    'Problem opening log file.
    Init = False
    Exit Function

End Function

'Log Close - Trans - 06/95
'by Ken Bergmann
'Purpose - Closes transaction log.
Public Sub Term()
On Error Resume Next
Close #SQLLogFNum
End Sub
'Log SQL String - Trans - 06/95
'by Ken Bergmann
'Purpose - Writes SQL Strings to the SQL log.
'Inputs - sSQLText    String
Public Sub PostItem(ByVal lQryNum As Long, ByVal sTrnText As String, ByVal sSQLText As String)
Dim bOnce As Boolean

bOnce = False
On Error GoTo SQLlogerr
If SQLLogging Then                                                'Are we logging in SQL file??
    If Len(sSQLText) > 0 Then                                     'If user text
        Print #SQLLogFNum, "/* " & FormatItem(sTrnText) & " */"    'print transaction descriptor
        Print #SQLLogFNum, sSQLText                               'print SQL text
    End If
    If LOF(SQLLogFNum) >= SQLLogSize Then                         'If the SQL log is too big
        Close SQLLogFNum                                          'Close the file
        On Error Resume Next                                      'Don't let this stop us
        Name SQLLogName As SQLLogBack                             'Back up the log
        On Error GoTo SQLlogerr                                   'Reenable the error handler
        SQLLogFNum = FreeFile
        Open SQLLogName For Output As SQLLogFNum                  'Reopen the log file
    End If
End If
Exit Sub

SQLlogerr:
    'There was some error writing to the file
    SQLLogFNum = FreeFile
    Open SQLLogName For Append As SQLLogFNum
    'Only retry once, then give up
    If Not bOnce Then bOnce = True: Resume
    SQLLogging = False
    Exit Sub

End Sub

Public Property Get BackUpFileName() As String
On Error Resume Next
BackUpFileName = Trim$(SQLLogBack)
End Property

Public Property Let BackUpFileName(ByVal sName As String)
On Error Resume Next
SQLLogBack = sName
End Property

Public Property Get Enabled() As Boolean
On Error Resume Next
Enabled = SQLLogging
End Property

Public Property Let Enabled(ByVal bLogging As Boolean)
On Error Resume Next
SQLLogging = bLogging
End Property

Public Property Get FileName() As String
On Error Resume Next
FileName = Trim$(SQLLogName)
End Property

Public Property Let FileName(ByVal sName As String)
On Error Resume Next
SQLLogName = sName
End Property

Public Property Get MaxBytes() As Long
On Error Resume Next
MaxBytes = SQLLogSize
End Property

Public Property Let MaxBytes(ByVal lSize As Long)
On Error Resume Next
SQLLogSize = lSize
End Property

