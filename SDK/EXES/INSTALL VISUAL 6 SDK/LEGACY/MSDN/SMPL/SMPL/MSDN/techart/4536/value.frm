VERSION 4.00
Begin VB.Form VALUE 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Choose Value"
   ClientHeight    =   5280
   ClientLeft      =   2685
   ClientTop       =   1815
   ClientWidth     =   2655
   ControlBox      =   0   'False
   Height          =   5685
   Icon            =   "VALUE.frx":0000
   Left            =   2625
   LinkTopic       =   "VALUE"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5280
   ScaleWidth      =   2655
   Top             =   1470
   Width           =   2775
   Begin VB.CommandButton CANCEL 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   120
      TabIndex        =   2
      Top             =   4800
      Width           =   2415
   End
   Begin VB.CommandButton OK 
      Caption         =   "OK"
      Height          =   375
      Left            =   120
      TabIndex        =   1
      Top             =   4320
      Width           =   2415
   End
   Begin VB.ListBox ValueList 
      Height          =   4125
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   2415
   End
End
Attribute VB_Name = "VALUE"
Attribute VB_Creatable = False
Attribute VB_Exposed = False

Function GetType(TypeNumber As Long) As String

  'Change Registry Type long value to a string
  Select Case TypeNumber
    Case REG_SZ
      GetType = "REG_SZ"
    Case REG_DWORD
      GetType = "REG_DWORD"
    Case REG_BINARY
      GetType = "REG_BINARY"
    Case REG_DWORD_LITTLE_ENDIAN
      GetType = "REG_DWORD_LITTLE_ENDIAN"
    Case REG_DWORD_BIG_ENDIAN
      GetType = "REG_DWORD_BIG_ENDIAN"
    Case REG_EXPAND_SZ
      GetType = "REG_EXPAND_SZ"
    Case REG_LINK
      GetType = "REG_LINK"
    Case REG_MULTI_SZ
      GetType = "REG_MULTI_SZ"
    Case REG_NONE
      GetType = "REG_NONE"
    Case REG_RESOURCE_LIST
      GetType = "REG_RESOURCE_LIST"
    Case Else
      GetType = "UNKNOWN"
  End Select

End Function

Function GetValueStr(RegEntry As String) As String
Dim ValueStr As String, Index As Integer, CurrentChar As String

  'Initilize local variables
  ValueStr = ""
  CurrentChar = ""
  Index = 1

  'Get characters before first ":" in string
  While CurrentChar <> ":"
    ValueStr = ValueStr & CurrentChar
    CurrentChar = Mid(RegEntry, Index, 1)
    Index = Index + 1
  Wend

  'Return value before first ":" in RegEntry
  GetValueStr = ValueStr
  
End Function

Function LoadValueList(LoadKey As Boolean) As Boolean

On Error GoTo ERROR_HANDLER

Dim lResult As Long, Index As Long, dwReserved As Long, szBuffer As String, _
    lBuffSize As Long, szBuffer2 As String, lBuffSize2 As Long, phkResult As Long, _
    SA As SECURITY_ATTRIBUTES, lType As Long, FT As FILETIME

  'Initilize local variables
  Index = 0
  dwReserved = 0
  ValueList.Clear

  If LoadKey Then 'Enumerate SubKeys
    'Open the key
    lResult = RegCreateKeyEx(VBREG.hKey, VBREG.SubKey, 0, "", REG_OPTION_NON_VOLATILE, _
                             KEY_ALL_ACCESS, SA, phkResult, VBREG.Create)

    'Loop for each subkey found
    While lResult = ERROR_SUCCESS
    
      'Set buffer space
      szBuffer = Space(255)
      lBuffSize = Len(szBuffer)
      szBuffer2 = Space(255)
      lBuffSize2 = Len(szBuffer2)
      
      'Get next key
      lResult = RegEnumKeyEx(phkResult, Index, szBuffer, lBuffSize, _
                             dwReserved, szBuffer2, lBuffSize2, FT)

      'If found a new key, add it to the list
      If lResult = ERROR_SUCCESS Then
        ValueList.AddItem Left(szBuffer, lBuffSize) & ":" & _
                          Left(szBuffer2, lBuffSize2)
      End If
      Index = Index + 1
    Wend
    
  Else ' Enumerate Values
  
    'Open the key
    lResult = RegOpenKeyEx(VBREG.hKey, VBREG.SubKey, 0, 1, phkResult)
    
    'Loop for each value found
    While lResult = ERROR_SUCCESS

      'Set buffer space
      szBuffer = Space(255)
      lBuffSize = Len(szBuffer)
      szBuffer2 = Space(255)
      lBuffSize2 = Len(szBuffer2)
      
      'Get next value
      lResult = RegEnumValue(phkResult, Index, szBuffer, lBuffSize, _
                             dwReserved, lType, szBuffer2, lBuffSize2)
      
      'If found a new value, add it to the list
      If lResult = ERROR_SUCCESS Then
        If VBREG.CurrentOperation <> VBREG.GETREGVALUEDATA Then
          ValueList.AddItem Left(szBuffer, lBuffSize) & ":" & GetType(lType) _
                            & ":" & Left(szBuffer2, lBuffSize2 - 1)
        Else
          'Don't list the value if it is not desired
          ValueList.AddItem Left(szBuffer, lBuffSize) & ":" & GetType(lType)
        End If
      End If
      Index = Index + 1
    Wend
  End If
  
  'Close the key
  RegCloseKey phkResult

  'Return true if enmerated all values
  LoadValueList = (lResult = ERROR_NO_MORE_ITEMS)
  Exit Function

ERROR_HANDLER:
  MsgBox "ERROR #" & Str$(Err) & " : " & Error & Chr(13) _
         & "Please exit and try again."
  LoadValueList = False

End Function

Private Sub Cancel_Click()

  VBREG.CurrentOperation = VBREG.NOOPERATION
  VALUE.Visible = False
  VBREG.Enabled = True
  VBREG.Show
  
End Sub


Private Sub OK_Click()

On Error GoTo ERROR_HANDLER

Dim Reply As String, phkResult As Long, SA As SECURITY_ATTRIBUTES

  'Cancel if no value was chosen
  If ValueList.Text = "" Then
    Cancel_Click
    Exit Sub
  End If

  Select Case VBREG.CurrentOperation
    Case VBREG.GETREGVALUEDATA
      'Use RegQueryValue to get the value
      MsgBox "The Value of" & Chr(13) & GetValueStr(ValueList.Text) & _
             " is:" & Chr(13) & VBREG.GetRegValue(VBREG.hKey, VBREG.SubKey, _
             GetValueStr(ValueList.Text), "Not Found")

    Case VBREG.DELETEREGVALUE
      'Open current SubKey
      RegCreateKeyEx VBREG.hKey, VBREG.SubKey, 0, "", REG_OPTION_NON_VOLATILE, _
                     KEY_ALL_ACCESS, SA, phkResult, VBREG.Create

      'Delete SubKey value specified
      If RegDeleteValue(phkResult, GetValueStr(ValueList.Text)) = ERROR_SUCCESS Then
        MsgBox "Value Deleted"
      Else
        MsgBox "Cannot Delete Value"
      End If
   
     'Close the current SubKey
      RegCloseKey phkResult

    Case VBREG.DELETEREGKEY
      'Open current SubKey
      RegCreateKeyEx VBREG.hKey, VBREG.SubKey, 0, "", REG_OPTION_NON_VOLATILE, _
                     KEY_ALL_ACCESS, SA, phkResult, VBREG.Create
      
      'Delete SubKey specified
      If RegDeleteKey(phkResult, GetValueStr(ValueList.Text)) = ERROR_SUCCESS Then
        MsgBox "SubKey Deleted"
      Else
       'Close the current SubKey
        RegCloseKey phkResult
        MsgBox "Cannot Delete SubKey"
      End If

    Case Else 'VBREG.SETREGVALUEDATA
      'Get data value desired by the user
      Reply = InputBox("Enter Value Desired:" & Chr(13) & "Under " _
                        & VBREG.SubKey & Chr(13) & "Then " & GetValueStr(ValueList.Text))
      If Reply = "" Then
        Cancel_Click
        Exit Sub
      End If

      'Set the new value
      If Not VBREG.SetRegValue(VBREG.hKey, VBREG.SubKey, _
                   GetValueStr(ValueList.Text), Reply) Then
        MsgBox "Unable to set value."
      End If
  
  End Select

  'Set focus back to main form
  Cancel_Click
  Exit Sub

ERROR_HANDLER:
  MsgBox "ERROR #" & Str$(Err) & " : " & Error & Chr(13) _
         & "Please exit and try again."
  Cancel_Click

End Sub


Private Sub ValueList_DblClick()
  
  OK_Click

End Sub


