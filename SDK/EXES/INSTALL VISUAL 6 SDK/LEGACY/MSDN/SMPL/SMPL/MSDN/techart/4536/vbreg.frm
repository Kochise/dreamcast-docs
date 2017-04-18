VERSION 4.00
Begin VB.Form VBREG 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "VB4 Registry Editor"
   ClientHeight    =   4290
   ClientLeft      =   1110
   ClientTop       =   1560
   ClientWidth     =   4290
   Height          =   4695
   Icon            =   "VBREG.frx":0000
   Left            =   1050
   LinkTopic       =   "VBREG"
   MaxButton       =   0   'False
   Picture         =   "VBREG.frx":030A
   ScaleHeight     =   4290
   ScaleWidth      =   4290
   Top             =   1215
   Width           =   4410
   Begin VB.CommandButton DEFAULTKEY 
      Caption         =   "Set Default Key"
      Height          =   375
      Left            =   360
      TabIndex        =   2
      Top             =   2160
      Width           =   3615
   End
   Begin VB.CommandButton KEYDELETE 
      Caption         =   "Delete Sub Key"
      Height          =   375
      Left            =   2280
      TabIndex        =   4
      Top             =   2640
      Width           =   1695
   End
   Begin VB.CommandButton DELETE 
      Caption         =   "Delete Value"
      Height          =   375
      Left            =   2280
      TabIndex        =   6
      Top             =   3120
      Width           =   1695
   End
   Begin VB.CommandButton NEWVALUE 
      Caption         =   "Create New Value"
      Height          =   375
      Left            =   360
      TabIndex        =   5
      Top             =   3120
      Width           =   1695
   End
   Begin VB.CommandButton ABOUT 
      Caption         =   "About"
      Height          =   375
      Left            =   360
      TabIndex        =   7
      Top             =   3600
      Width           =   1695
   End
   Begin VB.CommandButton EXIT 
      Caption         =   "Exit"
      Height          =   375
      Left            =   2280
      TabIndex        =   8
      Top             =   3600
      Width           =   1695
   End
   Begin VB.CommandButton CREATEKEY 
      Caption         =   "Create Sub Key"
      Height          =   375
      Left            =   360
      TabIndex        =   3
      Top             =   2640
      Width           =   1695
   End
   Begin VB.CommandButton GETVALUE 
      Caption         =   "Get Reg Value"
      Height          =   375
      Left            =   360
      TabIndex        =   0
      Top             =   1200
      Width           =   3615
   End
   Begin VB.CommandButton SETVALUE 
      Caption         =   "Set Reg Value"
      Height          =   375
      Left            =   360
      TabIndex        =   1
      Top             =   1680
      Width           =   3615
   End
End
Attribute VB_Name = "VBREG"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
'Global Variables
Public SubKey As String
Public hKey As Long
Public Create As Long
'Operation Flag Values
Public NOOPERATION As Integer
Public DELETEREGVALUE As Integer
Public DELETEREGKEY As Integer
Public GETREGVALUEDATA As Integer
Public SETREGVALUEDATA As Integer
'Operation Flag
Public CurrentOperation As Integer
Function CreateRegKey(NewSubKey As String) As Boolean

On Error GoTo ERROR_HANDLER

Dim phkResult As Long, lResult As Long, SA As SECURITY_ATTRIBUTES
    
  'Create key if it does not exist
  CreateRegKey = (RegCreateKeyEx(hKey, SubKey & NewSubKey, 0, "", REG_OPTION_NON_VOLATILE, _
                  KEY_ALL_ACCESS, SA, phkResult, Create) = ERROR_SUCCESS)

  'Close the key
  RegCloseKey phkResult
  Exit Function

ERROR_HANDLER:
  MsgBox "ERROR #" & Str$(Err) & " : " & Error & Chr(13) _
         & "Please exit and try again."
  CreateRegKey = False
  
End Function


Function GetRegValue(hKey As Long, lpszSubKey As String, szKey As String, _
                     szDefault As String) As Variant

On Error GoTo ERROR_HANDLER

Dim phkResult As Long, lResult As Long, szBuffer As String, lBuffSize As Long

  'Create Buffer
  szBuffer = Space(255)
  lBuffSize = Len(szBuffer)
  
  'Open the key
  RegOpenKeyEx hKey, lpszSubKey, 0, 1, phkResult

  'Query the value
  lResult = RegQueryValueEx(phkResult, szKey, 0, 0, szBuffer, lBuffSize)

  'Close the key
  RegCloseKey phkResult

  'Return obtained value
  If lResult = ERROR_SUCCESS Then
    GetRegValue = Left(szBuffer, lBuffSize - 1)
  Else
    GetRegValue = szDefault
  End If
  Exit Function

ERROR_HANDLER:
  MsgBox "ERROR #" & Str$(Err) & " : " & Error & Chr(13) _
         & "Please exit and try again."
  GetRegValue = ""

End Function

Function SetRegValue(hKey As Long, lpszSubKey As String, ByVal sSetValue As String, _
                     ByVal sValue As String) As Boolean

On Error GoTo ERROR_HANDLER
 
Dim phkResult As Long, lResult As Long, SA As SECURITY_ATTRIBUTES
'Note: This function will create the key or value if it doesn't exist.
  
  'Open or Create the key
  RegCreateKeyEx hKey, lpszSubKey, 0, "", REG_OPTION_NON_VOLATILE, _
                 KEY_ALL_ACCESS, SA, phkResult, Create

  lResult = RegSetValueEx(phkResult, sSetValue, 0, REG_SZ, sValue, _
                          CLng(Len(sValue) + 1))
    
  'Close the key
  RegCloseKey phkResult

  'Return SetRegValue Result
  SetRegValue = (lResult = ERROR_SUCCESS)
  Exit Function

ERROR_HANDLER:
  MsgBox "ERROR #" & Str$(Err) & " : " & Error & Chr(13) _
         & "Please exit and try again."
  SetRegValue = False

End Function


Private Sub ABOUT_Click()

  'About VBREG Sample Program
  MsgBox "Microsoft VB4 Registry Editor" & Chr(13) & _
         "Sample Application Program" & Chr(13) & _
         "By Roger Wynn", vbInformation

End Sub

Private Sub CREATEKEY_Click()

On Error GoTo ERROR_HANDLER

Dim Reply As String

  'Get Name for new key from user
  Reply = InputBox("Enter New SubKey Desired:" & Chr(13) & _
                   "Under " & SubKey)
  If Reply = "" Then
    Exit Sub
  End If

  'Make sure the new key is in the form "key\"
  If Mid(Reply, 1, 1) = "\" Then
    Reply = Mid(Reply, 2, Len(Reply))
  End If
  
  If Reply = "" Then
    MsgBox "Unable to Create Key."
    Exit Sub
  End If

  If Mid(Reply, Len(Reply), 1) <> "\" Then
    Reply = Reply & "\"
  End If
  
  'Create the new key
  If CreateRegKey(Reply) Then
    If MsgBox("Would you like to use" & Chr(13) & SubKey & Reply & _
              Chr(13) & "as the default SubKey?", vbYesNo) = vbYes Then
      'Set new key as default if user wishes
      SubKey = SubKey & Reply
    End If
  Else
    MsgBox "Unable to Create Key."
  End If
  Exit Sub

ERROR_HANDLER:
  MsgBox "ERROR #" & Str$(Err) & " : " & Error & Chr(13) _
         & "Please exit and try again."

End Sub


Private Sub DEFAULTKEY_Click()

On Error GoTo ERROR_HANDLER

Dim NewKey As String, phkResult As Long

  'Get Registry SubKey from user
  NewKey = InputBox("Enter SubKey Desired:", , SubKey)

  'Exit if user chose Cancel or entered an empty string
  If NewKey = "" Then
    Exit Sub
  End If

  'See if the new Registry SubKey given exists
  If RegOpenKeyEx(hKey, NewKey, 0, 1, phkResult) <> ERROR_SUCCESS Then
    MsgBox "A Valid SubKey is needed to continue." & Chr(13) & _
           "Changes Cancelled."
    Exit Sub
  End If

  'Close given SubKey
  RegCloseKey phkResult

  'Set the new default SubKey
  SubKey = NewKey
  
  'Add a "\" to end of SubKey if one was not given. This makes
  '  concatination of subkeys easier later.
  If Mid(SubKey, Len(SubKey), 1) <> "\" Then
    SubKey = SubKey & "\"
  End If
  Exit Sub
  
ERROR_HANDLER:
  MsgBox "ERROR #" & Str$(Err) & " : " & Error & Chr(13) _
         & "Please exit and try again."

End Sub

Private Sub DELETE_Click()

  If Not VALUE.LoadValueList(False) Then
    MsgBox "Unable to load Values."
  Else
    CurrentOperation = DELETEREGVALUE
    VBREG.Enabled = False
    VALUE.Visible = True
  End If

End Sub

Private Sub EXIT_Click()

  End
  
End Sub

Private Sub Form_Load()

On Error GoTo ERROR_HANDLER

Dim phkResult As Long, SA As SECURITY_ATTRIBUTES

  'Initilize some public variables
  'Operation flag values
  NOOPERATION = 0
  DELETEREGVALUE = 1
  DELETEREGKEY = 2
  GETREGVALUEDATA = 3
  SETREGVALUEDATA = 4
  'Operation flag
  CurrentOperation = NOOPERATION

  'Registry key we want to use
  hKey = HKEY_LOCAL_MACHINE
  
  'Get Registry SubKey from user
  SubKey = InputBox("Enter SubKey Desired:", , "SOFTWARE\MICROSOFT\VBREG\")

  'Exit if user chose Cancel or entered an empty string
  If SubKey = "" Then
    MsgBox "Must choose a default SubKey." & Chr(13) & _
           "VBREG will now abort."
    End
  End If
  
  If StrComp(SubKey, "SOFTWARE\MICROSOFT\VBREG\", 1) = 0 Then
    
    'Create default SubKey if it does not exist
    If RegCreateKeyEx(hKey, SubKey, 0, "", REG_OPTION_NON_VOLATILE, _
      KEY_ALL_ACCESS, SA, phkResult, Create) <> ERROR_SUCCESS Then
        MsgBox "Unable to Create/Open SubKey." & Chr(13) & _
               "VBREG will now abort."
        End
    End If
    
    'Close default SubKey
    RegCloseKey phkResult
    
  Else
  
    'See if Registry SubKey given exists
    If RegOpenKeyEx(hKey, SubKey, 0, 1, phkResult) <> ERROR_SUCCESS Then
      MsgBox "A Valid SubKey is needed to continue." & Chr(13) & _
             "VBREG will now abort."
      End
    End If
    
    'Close given SubKey
    RegCloseKey phkResult
  End If

  'Add a "\" to end of SubKey if one was not given. This makes
  '  concatination of subkeys easier later.
  If Mid(SubKey, Len(SubKey), 1) <> "\" Then
    SubKey = SubKey & "\"
  End If
  Exit Sub

ERROR_HANDLER:
  MsgBox "ERROR #" & Str$(Err) & " : " & Error & Chr(13) _
         & "Please exit and try again."

End Sub

Private Sub GETVALUE_Click()
Dim Reply As String

  CurrentOperation = GETREGVALUEDATA
  If Not VALUE.LoadValueList(False) Then
    MsgBox "Unable to load Values."
    CurrentOperation = NOOPERATION
  Else
    VBREG.Enabled = False
    VALUE.Visible = True
  End If

End Sub

Private Sub KEYDELETE_Click()

  If Not VALUE.LoadValueList(True) Then
    MsgBox "Unable to load Keys."
  Else
    CurrentOperation = DELETEREGKEY
    VBREG.Enabled = False
    VALUE.Visible = True
  End If

End Sub

Private Sub NEWVALUE_Click()
Dim Reply1 As String, Reply2 As String

  Reply1 = InputBox("Enter New Value Desired:" & Chr(13) & "Under " & SubKey)
  If Reply1 = "" Then
    Exit Sub
  End If

  Reply2 = InputBox("Enter Value Desired:" & Chr(13) & "Under " _
                    & SubKey & Chr(13) & "Then " & Reply1)
  If Reply2 = "" Then
    Exit Sub
  End If

  If Not SetRegValue(hKey, SubKey, Reply1, Reply2) Then
    MsgBox "Unable to set value."
  End If

End Sub

Private Sub SETVALUE_Click()

  CurrentOperation = SETREGVALUEDATA
  If Not VALUE.LoadValueList(False) Then
    MsgBox "Unable to load Values."
    CurrentOperation = NOOPERATION
  Else
    VBREG.Enabled = False
    VALUE.Visible = True
  End If

End Sub


