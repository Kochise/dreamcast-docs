Attribute VB_Name = "COM"
' Constants used with COM functions
Public Const CLSCTX_INPROC_SERVER As Long = 1

' A type to support UUIDs
Public Type GUID
    l As Long
    w1 As Integer
    w2 As Integer
    b1 As Byte
    b2 As Byte
    b3 As Byte
    b4 As Byte
    b5 As Byte
    b6 As Byte
    b7 As Byte
    b8 As Byte
End Type

' Standard COM interface IDs
Public IID_IUnknown As GUID

' Appliance COM object class IDs
Public CLSID_LightBulb As GUID

' Appliance COM interface IDs
Public IID_IDrawing As GUID

' COM functions from COMPOBJ.DLL (and also in VBSysDbg.Dll)
Public Declare Function CoCreateInstance Lib "vbsysdbg" (ByRef rclsid As GUID, ByVal pUnkOuter As Long, _
    ByVal dwContent As Long, ByRef riid As GUID, ByRef ppv As Long) As Long

' COM support functions in VBSysDbg
Public Declare Function comQueryInterface Lib "vbsysdbg" (ByVal punkObject As Long, ByRef riid As GUID, _
    ByRef ppv As Long) As Long
Public Declare Function comAddRef Lib "vbsysdbg" (ByVal punkObject As Long) As Long
Public Declare Function comRelease Lib "vbsysdbg" (ByVal punkObject As Long) As Long
Public Declare Function comCallStdMember0 Lib "vbsysdbg" (ByVal punkObject As Long, _
    ByVal dwIndex As Long) As Long
Public Declare Function comCallStdMember1 Lib "vbsysdbg" (ByVal punkObject As Long, _
    ByVal dwIndex As Long, ByVal dwArg1 As Long) As Long
Public Declare Function comCallStdMember2 Lib "vbsysdbg" (ByVal punkObject As Long, _
    ByVal dwIndex As Long, ByVal dwArg1 As Long, ByVal dwArg2 As Long) As Long
Public Declare Function comCallStdMember3 Lib "vbsysdbg" (ByVal punkObject As Long, _
    ByVal dwIndex As Long, ByVal dwArg1 As Long, ByVal dwArg2 As Long, ByVal dwArg3 As Long) _
    As Long
    

' Helper routine to initialize an OLE style GUID
Public Sub DefineOLEGuid(ByRef i As GUID, l As Long, w1 As Integer, w2 As Integer)
    i.l = l
    i.w1 = w1
    i.w2 = w2
    i.b1 = &HC0
    i.b2 = 0
    i.b3 = 0
    i.b4 = 0
    i.b5 = 0
    i.b6 = 0
    i.b7 = 0
    i.b8 = &H46
End Sub

' Helper routine to set up a GUID from its string representation
Public Sub DEFINE_GUID(ByRef cls As GUID, l As Long, w1 As Integer, w2 As Integer, _
                       b1 As Byte, b2 As Byte, b3 As Byte, b4 As Byte, _
                       b5 As Byte, b6 As Byte, b7 As Byte, b8 As Byte)
    cls.l = l
    cls.w1 = w1
    cls.w2 = w2
    cls.b1 = b1
    cls.b2 = b2
    cls.b3 = b3
    cls.b4 = b4
    cls.b5 = b5
    cls.b6 = b6
    cls.b7 = b7
    cls.b8 = b8
End Sub

' Helper routine to return a GUID as a string
Public Function GUID$(ByRef g As GUID)
    GUID$ = "{" + Hex(g.l) + "-" + Hex(g.w1) + "-" + Hex(g.w2) + "-" _
            + Hex(g.b1) + "-" + Hex(g.b2) + "-" + Hex(g.b3) + "-" + Hex(g.b4) + "-" _
            + Hex(g.b5) + "-" + Hex(g.b6) + "-" + Hex(g.b7) + "-" + Hex(g.b8) + "}"
End Function

' Appliance COM member functions
Public Function IDrawing_Draw(ByVal punkObject As Long, _
    ByVal hDC As Long, ByVal x As Long, ByVal y As Long) As Long
    IDrawing_Draw = comCallStdMember3(punkObject, 3, hDC, x, y)
End Function

Public Function IDrawing_SetPalette(ByVal punkObject As Long, ByVal hPal) As Long
    IDrawing_SetPalette = comCallStdMember1(punkObject, 4, hPal)
End Function

' Routine which must be called when the application is first started
' to set up all the UUID values
Public Sub InitCOMSupport()
    ' Set up the COM interface IDs
    Call DefineOLEGuid(IID_IUnknown, 0, 0, 0)
    
    ' Set up the Appliance COM object class IDs and interface IDs
    Call DEFINE_GUID(CLSID_LightBulb, &H3A015B30, &H41FC, &H11CE, &H9E, &HE5, 0, &HAA, 0, &H42, &H31, &HBF)
    Call DEFINE_GUID(IID_IDrawing, &H15038B10, &H3D3E, &H11CE, &H9E, &HE5, 0, &HAA, 0, &H42, &H31, &HBF)
End Sub




