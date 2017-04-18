'@doc
'------------>>>VISUAL BASIC DECLARATIONS FOR SAMPLES<<<------------------
'   For detailed information about these and other library routines,
'   please refer to the Microsoft Windows Software Development Kit
'   (Microsoft Windows SDK). To order the Microsoft Windows SDK, call
'   Microsoft Press, at 1-800-MSPRESS.
'   Some of the declarations in this module use a Type-Declaration
'   Character to specify the data type of a variable.  For more information
'   search on "Type Declaration Character" in help.
'------------------------------------------------------------------------------

'To ensure explicit declaration of variables, use the "Option
'Explicit" parameter. This is not necessary, but should be done
'for clarity and optimum performance.
Option Explicit

'Declaration for getting the Windows path.
Public Declare Function GetWindowsDirectoryA Lib "KERNEL32" (ByVal lpbuffer As String, ByVal nsize As Integer) As Long

'------------------>>>Delclarations for Registry functions<<<------------------
Public Const HKEY_CLASSES_ROOT As Long = &h80000000
Public Const HKEY_CURRENT_USER As Long = &h80000001
Public Const HKEY_LOCAL_MACHINE As Long = &h80000002
Public Const HKEY_USERS As Long = &h80000003

Public Const ERROR_SUCCESS As Long = 0
Public Const ERROR_FILE_NOT_FOUND As Long = 2
Public Const ERROR_INVALID_HANDLE As Long = 6
Public Const ERROR_NO_ACCESS As Long = 998

Public Const REG_SZ As Long = 1
Public Const REG_DWORD As Long = 4

Public Declare Function RegOpenKey& Lib "ADVAPI32" Alias "RegOpenKeyA" (ByVal hkeyOpen&, ByVal szSubKey$, ByRef hkeyResult&)
Public Declare Function RegCreateKey& Lib "ADVAPI32" Alias "RegCreateKeyA" (ByVal hkeyOpen&, ByVal szSubKey$, ByRef hkeyResult&)
Public Declare Function RegQuerySzValue& Lib "ADVAPI32" Alias "RegQueryValueExA" (ByVal hkey&, ByVal szValueName$, ByVal lReserved&, ByRef lType&, ByVal sValue$, ByRef lcbData&)
Public Declare Function RegQueryDwordValue& Lib "ADVAPI32" Alias "RegQueryValueExA" (ByVal hkey&, ByVal szValueName$, ByVal lReserved&, ByRef lType&, ByRef lValue&, ByRef lcbData&)
Public Declare Function RegQueryNullValue& Lib "ADVAPI32" Alias "RegQueryValueExA" (ByVal hkey&, ByVal szValueName$, ByVal lReserved&, ByRef lType&, ByVal vNull As Any, ByRef lcbData&)
Public Declare Function RegCloseKey& Lib "ADVAPI32" (ByVal hkey&)
Public Declare Function RegSetSzValue& Lib "ADVAPI32" Alias "RegSetValueExA" (ByVal hkey&, ByVal szValueName$, ByVal dwReserved&, ByVal lType&, ByVal sValue$, ByVal lcbData&)
Public Declare Function RegSetDwordValue& Lib "ADVAPI32" Alias "RegSetValueExA" (ByVal hkey&, ByVal szValueName$, ByVal dwReserved&, ByVal lType&, ByRef lValue&, ByVal lcbData&)
'------------------------------------------------------------------------

'@btype Example of User-Defined Type
Type MyType
    i as Integer  '@bfield An integer.
    s as String   '@bfield A string.

    ' @bfield A string without explicit type name.
    myString$

    ' @bfield An integer without explicit type name.
    myInt
End Type


'@bfunc Example of User-Defined Function
'@bparm Left
'@bparm Top
'@bparm Bottom
'@bparm Right
Public Function VB_Distance(X1 As Double, Y1 As Double, X2 As Double, Y2 As Double)
'   Call this function from any sheet or procedure.
'   Calculates and returns the distance between points.
    VB_Distance = Sqr((X2 - X1) ^ 2 + (Y2 - Y1) ^ 2)
End Function

'---------------->>> Win32 API and Registry Samples <<<--------------------
'   The samples in this section are intended for programmers who are
'   experienced users of Microsoft Excel, Windows, and/or Visual Basic.
'------------------------------------------------------------------------

'@bfunc  Example that calls GetWindowsDirectoryA
Function VB_GetWindowsDirectory() As String
'   This function returns the complete path to the Windows directory on
'   the machine it is called from.  The Windows directory is useful
'   for referring to files that are located along the Windows
'   path (an INI file, for example).
'   Call this function from any sheet or procedure.
    Dim Gwdvar As String, Gwdvar_Length As Integer
    Gwdvar = Space(255)    'reserves a space in memory for the results
'   Calls GetWindowsDirectoryA function (declared in the next module), which returns the length
'   of the Windows directory, and puts the actual text in the name "Gwdvar":
    Gwdvar_Length = GetWindowsDirectoryA(lpbuffer:=Gwdvar, nsize:=255)
    VB_GetWindowsDirectory = Left(Gwdvar, Gwdvar_Length)    'eliminates extra characters
    MsgBox VB_GetWindowsDirectory
End Function

'@bsub Sets and Retrieves values from the Registry
Sub ExcelRegistryExamples()
    Dim v As String  'Result Variable
    
    'TO RETRIEVE AN XL SETTING:
    'Function RegGetXLValue(szSection$, szKey$, Value As Variant) As Variant
    'v = RegGetXLValue("TestKey", "TestValue")
    'Example1:
    v = RegGetXLValue("Microsoft Excel", "User") 'Returns Username as a string.
    MsgBox v
    
    'TO MODIFY AN XL SETTING:
    'Function RegSetXLValue(szSection$, szKey$, Value As Variant) As Variant
    'Example1:
    v = RegSetXLValue("Microsoft Excel", "Font", "Arial,10") 'sets the font to "Arial 10"
    'Example2:
    v = RegSetXLValue("Microsoft Excel", "User", "Bob") 'sets the user name to Bob
End Sub


'------------------------>>>Excel Registry Functions<<<--------------------------------
'   The functions below are called by the Excel Registry Examples above
'--------------------------------------------------------------------------------------
'@bfunc Get XL value from registry
'@bparm Section name
'@bparm Key name
'@bparm Default value if key is missing
'@rdesc Registry value

Function RegGetXLValue(szSection$, szKey$, Optional vDefaultValue As Variant) As Variant
    On Error GoTo lbl_Error
    If IsMissing(vDefaultValue) Then vDefaultValue = CVErr(xlErrNA)
    Dim hkey&, lResult&, lcbValue&, szValue$, lValue&, hkeyXL7&, lType&
    lResult& = RegOpenKey&(HKEY_CURRENT_USER, "Software\Microsoft\Excel\7.0\" & szSection$, hkeyXL7&)
    If lResult& <> ERROR_SUCCESS Then
        RegGetXLValue = vDefaultValue
        Exit Function
    End If
    lResult& = RegQueryNullValue&(hkeyXL7&, szKey$, 0&, lType&, 0&, lcbValue&)
    If lResult& <> ERROR_SUCCESS Then
        RegGetXLValue = vDefaultValue
        Exit Function
    End If
    If lType& = REG_SZ Then
        szValue$ = String$(lcbValue&, " ")
        lResult& = RegQuerySzValue&(hkeyXL7&, szKey$, 0&, lType&, szValue$, lcbValue&)
        If lResult& <> ERROR_SUCCESS Then
            RegGetXLValue = vDefaultValue
            Exit Function
        End If
        RegGetXLValue = Left$(szValue$, lcbValue& - 1)
    ElseIf lType& = REG_DWORD Then
        lValue& = 0
        lResult& = RegQueryDwordValue&(hkeyXL7&, szKey$, 0&, lType&, lValue&, lcbValue&)
        If lResult& <> ERROR_SUCCESS Then
            RegGetXLValue = vDefaultValue
            Exit Function
        End If
        RegGetXLValue = lValue&
    End If
    lResult& = RegCloseKey&(hkeyXL7&)
    If lResult& <> ERROR_SUCCESS Then
        RegGetXLValue = vDefaultValue
        Exit Function
    End If
    Exit Function
lbl_Error:
    RegGetXLValue = vDefaultValue
End Function

'@bfunc Put XL value to registry
'@bparm Section name
'@bparm Key name
'@bparm Value to set
'@rdesc Error code, if any

Function RegSetXLValue(szSection$, szKey$, Value As Variant) As Variant
    Dim hkey&, lResult&, lcbValue&, szValue$, lValue&, hkeyXL7&, lType&
    
    ' Open XL7 registry key, create if it doesn't already exist
    lResult& = RegCreateKey&(HKEY_CURRENT_USER, "Software\Microsoft\Excel\7.0\" & szSection$, hkeyXL7&)
    If lResult& <> ERROR_SUCCESS Then
        RegSetXLValue = CVErr(xlErrNA)
        Exit Function
    End If
    
    ' Coerce value to either REG_SZ or REG_DWORD
    If TypeName(Value) = "String" Then
        lType& = REG_SZ
        Value = Value & Chr$(0)
        lcbValue& = Len(Value)
        lResult& = RegSetSzValue&(hkeyXL7&, szKey$, 0&, lType&, CStr(Value), lcbValue&)
     ElseIf TypeName(Value) = "Integer" Or TypeName(Value) = "Long" Then
        lType& = REG_DWORD
        lcbValue& = 4
        lValue& = CLng(Value)
        lResult& = RegSetDwordValue&(hkeyXL7&, szKey$, 0&, lType&, lValue&, lcbValue&)
    Else
        Value = CStr(Value)
        lType& = REG_SZ
        Value = Value & Chr$(10)
        lcbValue& = Len(Value)
        lResult& = RegSetSzValue&(hkeyXL7&, szKey$, 0&, lType&, CStr(Value), lcbValue&)
    End If
        
    If lResult& <> ERROR_SUCCESS Then
        RegSetXLValue = CVErr(xlErrNA)
        Exit Function
    End If
    
    ' Close the XL7 reg key
    lResult& = RegCloseKey&(hkeyXL7&)
    If lResult& <> ERROR_SUCCESS Then
        RegSetXLValue = False
        Exit Function
    End If
End Function


