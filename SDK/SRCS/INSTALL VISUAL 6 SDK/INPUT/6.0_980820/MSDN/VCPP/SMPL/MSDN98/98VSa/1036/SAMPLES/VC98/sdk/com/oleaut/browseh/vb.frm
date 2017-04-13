VERSION 4.00
Begin VB.Form Form1 
   Appearance      =   0  'Flat
   BackColor       =   &H80000005&
   Caption         =   "Header file generator"
   ClientHeight    =   2010
   ClientLeft      =   4110
   ClientTop       =   2640
   ClientWidth     =   5370
   BeginProperty Font 
      name            =   "MS Sans Serif"
      charset         =   0
      weight          =   700
      size            =   8.25
      underline       =   0   'False
      italic          =   0   'False
      strikethrough   =   0   'False
   EndProperty
   ForeColor       =   &H80000008&
   Height          =   2415
   Left            =   4050
   LinkTopic       =   "Form1"
   ScaleHeight     =   2010
   ScaleWidth      =   5370
   Top             =   2295
   Width           =   5490
   Begin VB.CommandButton ChooseTypeLibrary 
      Caption         =   "Choose Type Library"
      Height          =   495
      Left            =   1560
      TabIndex        =   0
      Top             =   360
      Width           =   2415
   End
   Begin MSComDlg.CommonDialog SaveOutputDialog 
      Left            =   120
      Top             =   1080
      _Version        =   65536
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
      DialogTitle     =   "Save Output As"
      Filter          =   "(*.h)|*.h"
   End
   Begin MSComDlg.CommonDialog ChooseTlibDialog 
      Left            =   120
      Top             =   480
      _Version        =   65536
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
      DialogTitle     =   "Choose Type Library"
      Filter          =   "Type Libraries |*.tlb;*.olb;*.dll;*.exe"
   End
End
Attribute VB_Name = "Form1"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
'TYPEKIND constants
Const TKIND_ENUM = 0
Const TKIND_RECORD = 1
Const TKIND_MODULE = 2
Const TKIND_INTERFACE = 3
Const TKIND_DISPATCH = 4
Const TKIND_COCLASS = 5
Const TKIND_ALIAS = 6
Const TKIND_UNION = 7

'INVOKEKIND constants
Const INVOKE_FUNC = 1
Const INVOKE_PROPERTYGET = 2
Const INVOKE_PROPERTYPUT = 4
Const INVOKE_PROPERTYPUTREF = 8

'VARENUM constants
Const VT_I2 = 2
Const VT_I4 = 3
Const VT_R4 = 4
Const VT_R8 = 5
Const VT_CY = 6
Const VT_DATE = 7
Const VT_BSTR = 8
Const VT_DISPATCH = 9
Const VT_ERROR = 10
Const VT_BOOL = 11
Const VT_VARIANT = 12
Const VT_UNKNOWN = 13
Const VT_I1 = 16
Const VT_UI1 = 17
Const VT_UI2 = 18
Const VT_UI4 = 19
Const VT_I8 = 20
Const VT_UI8 = 21
Const VT_INT = 22
Const VT_UINT = 23
Const VT_VOID = 24
Const VT_HRESULT = 25
Const VT_PTR = 26
Const VT_SAFEARRAY = 27
Const VT_CARRAY = 28
Const VT_USERDEFINED = 29
Const VT_LPSTR = 30
Const VT_LPWSTR = 31

' TYPEFLAGS
Const TYPEFLAG_FDUAL = &H40


Private Sub ChooseTypeLibrary_Click()
Dim browser As Object
Dim tlib As Object
Dim tinfos As Object
Dim tinfo As Object
Dim funcs As Object
Dim func As Object
Dim params As Object
Dim param As Object
Dim element As Object
Dim elements As Object
Dim member As Object
Dim members As Object
Dim tinfoBase As Object

' Get name of input type library
On Error GoTo DialogCancel
ChooseTlibDialog.CancelError = True
ChooseTlibDialog.ShowOpen

' Create Browse Helper (BROWSEH sample)
Set browser = CreateObject("BrowseHelper.Browser")
Set tlib = browser.BrowseTypeLibrary(ChooseTlibDialog.filename)
Set tinfos = tlib.TypeInfos

' Get name of output header file
On Error GoTo DialogCancel
SaveOutputDialog.CancelError = True
SaveOutputDialog.ShowSave
Open SaveOutputDialog.filename For Output As 1

Print #1, "DEFINE_GUID(LIBID_"; tlib.Name; ","; FormatGUID(tlib.GUIDAsString); ");"
Print #1,

' Enumerate typeinfos in the type library
For i = 0 To tinfos.Count - 1
  Set tinfo = tinfos.Item(i)
  
  ' Output header file contents depending on the TYPEKIND of the typeinfo
  Select Case tinfo.TypeInfoKind
     Case TKIND_ENUM     'Enum
        Print #1, "typedef enum{"
        Set elements = tinfo.elements
        For j = 0 To elements.Count - 1
            Set element = elements.Item(j)
            Print #1, Tab(1); element.Name; " = "; element.Value;
            If j < elements.Count - 1 Then
                    Print #1, ",";
            End If
        Next j
        Print #1,
        Print #1, "} "; tinfo.Name; ";"
        
    Case TKIND_RECORD     'Struct
        Print #1, "typedef struct{"
        Set members = tinfo.members
        For j = 0 To members.Count - 1
            Set member = members.Item(j)
            Print #1, Tab(1); TypeToString(member.Type); " "; member.Name; ";"
        Next j
        Print #1, "} "; tinfo.Name; ";"
        
    Case TKIND_UNION     'Union
        Print #1, "typedef union{"
        Set members = tinfo.members
        For j = 0 To members.Count - 1
            Set member = members.Item(j)
            Print #1, Tab(1); TypeToString(member.Type); " "; member.Name; ";"
        Next j
        Print #1, "} "; tinfo.Name; ";"
        
     Case TKIND_INTERFACE     'Interface
        Print #1, "DEFINE_GUID(IID_"; tinfo.Name; ","; FormatGUID(tinfo.GUIDAsString); ");"
        On Error Resume Next
        Set tinfoBase = tinfo.BaseInterface
        If Err.Number > 0 Then 'If there is no base interface
           Print #1, "DECLARE_INTERFACE("; tinfo.Name; ")"
        Else
           Print #1, "DECLARE_INTERFACE_("; tinfo.Name; ", "; tinfoBase.Name; ")"
        End If
        Print #1, "{"
        
        ' Output the functions in the interface
        Set funcs = tinfo.Functions
        For j = 0 To funcs.Count - 1
            Set func = funcs.Item(j)
            Print #1, Tab(2); "STDMETHOD_("; TypeToString(func.ReturnType); ", ";
            Select Case func.InvocationKind
                Case INVOKE_PROPERTYGET
                   Print #1, "get_";
                Case INVOKE_PROPERTYPUT
                   Print #1, "put_";
                Case INVOKE_PROPERTYPUTREF
                   Print #1, "putref_";
            End Select
            Set params = func.Parameters
            If params.Count = 0 Then
               Print #1, func.Name; ")(THIS";
            Else
              Print #1, func.Name; ")(THIS_ ";
            End If
            
            ' Ouput the parameters of the function
            For k = 0 To params.Count - 1
                Set param = params.Item(k)
                Print #1, TypeToString(param.Type); " ";
                Print #1, param.Name;
                If k < params.Count - 1 Then
                    Print #1, ", ";
                End If
            Next k
            Print #1, ") PURE;";
            Print #1,
        Next j
        Print #1, "};"
        
    Case TKIND_DISPATCH 'dispinterface or dual interface
        TypeFlags = tinfo.TypeFlags()
        ' Check if this is the dispinterface component of
        ' a dual interface. If so get the interface component of the dual interface
        If TypeFlags And TYPEFLAG_FDUAL Then
            Set tinfo = tinfo.Interface
            Set tinfoBase = tinfo.BaseInterface
            Print #1, "DEFINE_GUID(IID_"; tinfo.Name; ","; FormatGUID(tinfo.GUIDAsString); ");"
            Print #1, "DECLARE_INTERFACE_("; tinfo.Name; ", "; tinfoBase.Name; ")"
            Print #1, "{"
            
            ' Output the functions in the interface
            Set funcs = tinfo.Functions
            For j = 0 To funcs.Count - 1
                Set func = funcs.Item(j)
                Print #1, Tab(2); "STDMETHOD_("; TypeToString(func.ReturnType); ", ";
                Select Case func.InvocationKind
                    Case INVOKE_PROPERTYGET
                       Print #1, "get_";
                    Case INVOKE_PROPERTYPUT
                       Print #1, "put_";
                    Case INVOKE_PROPERTYPUTREF
                      Print #1, "putref_";
                End Select
                Set params = func.Parameters
                If params.Count = 0 Then
                    Print #1, func.Name; ")(THIS";
                Else
                     Print #1, func.Name; ")(THIS_ ";
                End If
                
                ' Ouput the parameters of the function
                For k = 0 To params.Count - 1
                    Set param = params.Item(k)
                    Print #1, TypeToString(param.Type); " ";
                    Print #1, param.Name;
                    If k < params.Count - 1 Then
                        Print #1, ", ";
                    End If
                Next k
                Print #1, ") PURE;";
                Print #1,
            Next j
            Print #1, "};"
        End If
        
    Case TKIND_ALIAS     'Alias
        Print #1, "typedef "; TypeToString(tinfo.BaseType); " "; tinfo.Name; ";"
        
    Case TKIND_COCLASS  'CoClass
         Print #1, "DEFINE_GUID(CLSID_"; tinfo.Name; ","; FormatGUID(tinfo.GUIDAsString); ");"

  End Select
  Print #1,
Next i

Close #1
MsgBox SaveOutputDialog.filename + " has been generated", , "Header File Generator"
DialogCancel:   'User cancelled the dialog
End Sub

' Convert a type to a string
Private Function TypeToString(typeObj As Object) As String
  Dim s As String
  Dim p As Object
  Dim u As Object

  t = typeObj.Type
  Select Case t
     Case VT_I2
         s = "short"
     Case VT_I4
         s = "long"
     Case VT_R4
         s = "float"
     Case VT_R8
         s = "double"
     Case VT_CY
         s = "CURRENCY"
     Case VT_DATE
         s = "DATE"
     Case VT_BSTR
         s = "BSTR"
     Case VT_DISPATCH
         s = "IDispatch FAR*"
     Case VT_ERROR
         s = "SCODE"
     Case VT_BOOL
         s = "VARIANT_BOOL"
     Case VT_VARIANT
         s = "VARIANT"
     Case VT_UNKNOWN
         s = "IUnknown FAR*"
     Case VT_I1
         s = "char"
     Case VT_UI1
         s = "unsigned char"
     Case VT_UI2
         s = "unsigned short"
     Case VT_UI4
         s = "unsigned long"
     Case VT_I8
         s = "64-bit int"
     Case VT_UI8
         s = "unsigned 64-bit int"
     Case VT_INT
         s = "int"
     Case VT_UINT
         s = "unsigned int"
     Case VT_VOID
         s = "void"
     Case VT_HRESULT
         s = "HRESULT"
     Case VT_PTR
         Set p = typeObj.PointerDesc
         s = TypeToString(p) + " FAR*"
     Case VT_SAFEARRAY
         s = "SAFEARRAY FAR*"
     Case VT_USERDEFINED
         Set u = typeObj.UserDefinedDesc
         s = u.Name
     Case VT_LPSTR
         s = "char FAR*"
     Case VT_LPWSTR
         s = "WCHAR FAR*"
         
  End Select
  If t And &H2000 Then
     s = "SAFEARRAY(" + s + ")"
  End If
  TypeToString = s
End Function

'Return a formatted GUID
Private Function FormatGUID(guid As String) As String

s1 = "0x" + Mid(guid, 2, 8) + "L,"
s2 = "0x" + Mid(guid, 11, 4) + "," + "0x" + Mid(guid, 16, 4) + ","
s3 = "0x" + Mid(guid, 21, 2) + "," + "0x" + Mid(guid, 23, 2) + ","
s4 = "0x" + Mid(guid, 26, 2) + "," + "0x" + Mid(guid, 28, 2) + ","
s5 = "0x" + Mid(guid, 30, 2) + "," + "0x" + Mid(guid, 32, 2) + ","
s6 = "0x" + Mid(guid, 34, 2) + "," + "0x" + Mid(guid, 36, 2)

FormatGUID = s1 + s2 + s3 + s4 + s5 + s6
End Function

