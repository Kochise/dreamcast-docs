' These constants and user defined types must be included
' in your app when you use the EZPRINT DLL.

' General Purpose Defines
Global Const TEXTLEN = 256
Global Const PO_TEXT = 0
Global Const PO_RECT = 1
Global Const PO_LINE = 2
Global Const PO_NEWPAGE = 4
Global Const PO_GRID = 5

' Object Attribute Flags
Global Const TEXT_NORMAL = &H0
Global Const TEXT_BOLD = &H1
Global Const TEXT_ITALIC = &H2
Global Const TEXT_UNDERLINED = &H4
Global Const TEXT_STRIKEOUT = &H8
Global Const TEXT_RECT = &H10
Global Const TEXT_LEFT = &H20
Global Const TEXT_RIGHT = &H40
Global Const TEXT_CENTER = &H80
Global Const TEXT_EXPANDTABS = &H100
Global Const TEXT_SINGLELINE = &H200
Global Const TEXT_NOCLIP = &H400

Global Const FILL_NONE = &H0
Global Const FILL_GRAY = &H1
Global Const FILL_LTGRAY = &H2
Global Const FILL_BLACK = &H4

Global Const PEN_SOLID = &H0
Global Const PEN_DOT = &H1
Global Const PEN_DASH = &H2
Global Const PEN_THIN = &H4
Global Const PEN_THICK = &H8
Global Const PEN_DASHDOT = &H10
Global Const PEN_DASHDOTDOT = &H20

' PrintStruct is the structure whose elements determine
' the object, location and attributes of the object on
' the page.
Type PrintStruct
    PrintObject As Integer
    TextFlags As Integer
    FillFlags As Integer
    PenFlags As Integer
    XOrg As Integer
    YOrg As Integer
    XExt As Integer
    YExt As Integer
    PointSize As Integer
    Text As String * TEXTLEN
End Type


' EZPRINT.DLL declarations
Declare Function PrintObject% Lib "EZPRINT.DLL" (PS As PrintStruct)
Declare Function StartDocument% Lib "EZPRINT.DLL" (ByVal hWnd As Integer, ByVal EnablePrintDlg As Integer)
Declare Function EndDocument% Lib "EZPRINT.DLL" (ByVal hWnd As Integer)

















