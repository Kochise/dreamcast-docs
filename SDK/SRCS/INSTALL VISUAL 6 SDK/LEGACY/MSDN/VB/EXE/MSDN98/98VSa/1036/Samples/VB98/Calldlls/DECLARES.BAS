Attribute VB_Name = "Module1"
Option Explicit
Dim WinVersion As Integer, SoundAvailable As Integer
Public VisibleFrame As Frame
 
Public Const TWIPS = 1
Public Const PIXELS = 3
Public Const RES_INFO = 2
Public Const MINIMIZED = 1

Type MYVERSION
    lMajorVersion As Long
    lMinorVersion As Long
    lExtraInfo As Long
End Type

Type OSVERSIONINFO
        dwOSVersionInfoSize As Long
        dwMajorVersion As Long
        dwMinorVersion As Long
        dwBuildNumber As Long
        dwPlatformId As Long
        szCSDVersion As String * 128      ' Chaîne de maintenance destinée à un usage PSS
End Type

Type Rect
    Left As Integer
    Top As Integer
    Right As Integer
    Bottom As Integer
End Type

Public Type SystemInfo
    dwOemId As Long
    dwPageSize As Long
    lpMinimumApplicationAddress As Long
    lpMaximumApplicationAddress As Long
    dwActiveProcessorMask As Long
    dwNumberOfProcessors As Long
    dwProcessorType As Long
    dwAllocationGranularity As Long
    dwReserved As Long
End Type

Public Type MEMORYSTATUS
    dwLength As Long
    dwMemoryLoad As Long
    dwTotalPhys As Long
    dwAvailPhys As Long
    dwTotalPageFile As Long
    dwAvailPageFile As Long
    dwTotalVirtual As Long
    dwAvailVirtual As Long
End Type

Declare Function GetWindowsDirectory Lib "kernel32" Alias "GetWindowsDirectoryA" (ByVal lpBuffer As String, ByVal nSize As Long) As Long
Declare Sub GetSystemInfo Lib "kernel32" (lpSystemInfo As SystemInfo)
Declare Sub GlobalMemoryStatus Lib "kernel32" (lpBuffer As MEMORYSTATUS)
Declare Function GetVersionEx Lib "kernel32" Alias "GetVersionExA" (ByRef lpVersionInformation As OSVERSIONINFO) As Long
Declare Function GetSystemMetrics Lib "User32" (ByVal nIndex As Long) As Long
Declare Function GetDeviceCaps Lib "GDI32" (ByVal hDC As Long, ByVal nIndex As Long) As Long
Declare Function TrackPopupMenu Lib "User32" (ByVal hMenu As Long, ByVal wFlags As Long, ByVal X As Long, ByVal Y As Long, ByVal nReserved As Long, ByVal hWnd As Long, lpReserved As Any) As Long
Declare Function GetMenu Lib "User32" (ByVal hWnd As Long) As Long
Declare Function GetSubMenu Lib "User32" (ByVal hMenu As Long, ByVal nPos As Long) As Long
Declare Function GetDesktopWindow Lib "User32" () As Long
Declare Function GetDC Lib "User32" (ByVal hWnd As Long) As Long
Declare Function ReleaseDC Lib "User32" (ByVal hWnd As Long, ByVal hDC As Long) As Long
Declare Function BitBlt Lib "GDI32" (ByVal hDestDC As Long, ByVal X As Long, ByVal Y As Long, ByVal nWidth As Long, ByVal nHeight As Long, ByVal hSrcDC As Long, ByVal XSrc As Long, ByVal YSrc As Long, ByVal dwRop As Long) As Long
Declare Sub SetWindowPos Lib "User32" (ByVal hWnd As Long, ByVal hWndInsertAfter As Long, ByVal X As Long, ByVal Y As Long, ByVal cx As Long, ByVal cy As Long, ByVal wFlags As Long)
Declare Function GetPrivateProfileString Lib "kernel32" Alias "GetPrivateProfileStringA" (ByVal lpApplicationName As String, lpKeyName As Any, ByVal lpDefault As String, ByVal lpRetunedString As String, ByVal nSize As Long, ByVal lpFileName As String) As Long
Declare Function GetProfileString Lib "kernel32" Alias "GetProfileStringA" (ByVal lpAppName As String, lpKeyName As Any, ByVal lpDefault As String, ByVal lpReturnedString As String, ByVal nSize As Long) As Long
Declare Function waveOutGetNumDevs Lib "winmm" () As Long
Declare Function GetSystemDirectory Lib "kernel32" Alias "GetSystemDirectoryA" (ByVal lpBuffer As String, ByVal nSize As Long) As Long
Declare Function sndPlaySound Lib "winmm" Alias "sndPlaySoundA" (ByVal lpszSoundName As String, ByVal uFlags As Long) As Long

Public Const VER_PLATFORM_WIN32s = 0
Public Const VER_PLATFORM_WIN32_WINDOWS = 1
Public Const VER_PLATFORM_WIN32_NT = 2

Public Const WF_CPU286 = &H2&
Public Const WF_CPU386 = &H4&
Public Const WF_CPU486 = &H8&
Public Const WF_STANDARD = &H10&
Public Const WF_ENHANCED = &H20&
Public Const WF_80x87 = &H400&

Public Const SM_MOUSEPRESENT = 19

Public Const GFSR_SYSTEMRESOURCES = &H0
Public Const GFSR_GDIRESOURCES = &H1
Public Const GFSR_USERRESOURCES = &H2

Public Const MF_POPUP = &H10
Public Const MF_BYPOSITION = &H400
Public Const MF_SEPARATOR = &H800

Public Const SRCCOPY = &HCC0020
Public Const SRCERASE = &H440328
Public Const SRCINVERT = &H660046
Public Const SRCAND = &H8800C6

Public Const HWND_TOPMOST = -1
Public Const HWND_NOTOPMOST = -2
Public Const SWP_NOACTIVATE = &H10
Public Const SWP_SHOWWINDOW = &H40


Function DeviceColors(hDC As Long) As Single
Const PLANES = 14
Const BITSPIXEL = 12
    DeviceColors = 2 ^ (GetDeviceCaps(hDC, PLANES) * GetDeviceCaps(hDC, BITSPIXEL))
End Function

Function GetSysIni(section, key)
Dim retVal As String, AppName As String, worked As Integer
    retVal = String$(255, 0)
    worked = GetPrivateProfileString(section, key, "", retVal, Len(retVal), "System.ini")
    If worked = 0 Then
        GetSysIni = "inconnu(e)"
    Else
        GetSysIni = Left(retVal, InStr(retVal, Chr(0)) - 1)
    End If
End Function

Function GetWinIni(section, key)
Dim retVal As String, AppName As String, worked As Integer
    retVal = String$(255, 0)
    worked = GetProfileString(section, key, "", retVal, Len(retVal))
    If worked = 0 Then
        GetWinIni = "inconnu(e)"
    Else
        GetWinIni = Left(retVal, InStr(retVal, Chr(0)) - 1)
    End If
End Function

Function SystemDirectory() As String
Dim WinPath As String
    WinPath = String(145, Chr(0))
    SystemDirectory = Left(WinPath, GetSystemDirectory(WinPath, 145))
End Function

Function WindowsDirectory() As String
Dim WinPath As String
    WinPath = String(145, Chr(0))
    WindowsDirectory = Left(WinPath, GetWindowsDirectory(WinPath, 145))
End Function

Function WindowsVersion() As MYVERSION
Dim myOS As OSVERSIONINFO, WinVer As MYVERSION
Dim lResult As Long

    myOS.dwOSVersionInfoSize = Len(myOS)    ' Doit être 148.
    
    lResult = GetVersionEx(myOS)
        
    ' Remplit le type utilisateur avec les informations appropriées.
    WinVer.lMajorVersion = myOS.dwMajorVersion
    WinVer.lMinorVersion = myOS.dwMinorVersion
    WinVer.lExtraInfo = myOS.dwPlatformId
    
    WindowsVersion = WinVer

End Function

