'©1994 Microsoft Corporation
'Microsoft Developers Network Unsupported Tools
' Email: MSDN@Microsoft.com
' See LICENSE for Redistribution Rights
'------------------------------
'Declarations for NATIVEVB.DLL
'Native VB Functions

'Performance Timing
'For Windows 3.0 and 3.1 --may not be available in NT
Declare Function Stopwatch_time Lib "NATIVEVB.DLL" () As Long
Declare Sub STopWatch_Reset Lib "NATIVEVB.DLL" ()
'For Windows 3.1 and above
Declare Function timegettime Lib "MMSYSTEM.DLL" () As Long

'Ini Functions
'-------=------
'Win Ini
Declare Function vbGetWinIni Lib "NATIVEVB.DLL" (ByVal Section$, ByVal KeyWord$) As String
Declare Function vbGetWinIniSection Lib "NATIVEVB.DLL" (ByVal Section$) As String
Declare Sub PutWinIni Lib "NATIVEVB.DLL" (ByVal Section$, ByVal Entry$, ByVal IniValue$)
Declare Sub DelWinIni Lib "NATIVEVB.DLL" (ByVal Section$, ByVal Entry$)
Declare Sub DelWinIniSection Lib "NATIVEVB.DLL" (ByVal Section$)
Declare Sub FlushWinIni Lib "NATIVEVB.DLL" ()
'Other Ini's
Declare Function vbGetIni Lib "NATIVEVB.DLL" (ByVal Section$, ByVal KeyWord$, ByVal fILEnAME$) As String
Declare Function vbGetIniSection Lib "NATIVEVB.DLL" (ByVal Section$, ByVal fILEnAME$) As String
Declare Sub PutIni Lib "NATIVEVB.DLL" (ByVal Section$, ByVal Entry$, ByVal IniValue$, ByVal fILEnAME$)
Declare Sub DelIni Lib "NATIVEVB.DLL" (ByVal Section$, ByVal Entry$, ByVal fILEnAME$)
Declare Sub DelIniSection Lib "NATIVEVB.DLL" (ByVal Section$, ByVal fILEnAME$)
Declare Sub FlushIni Lib "NATIVEVB.DLL" (ByVal fILEnAME$)

'VerStamp Info
Declare Function HasVerInfo Lib "NATIVEVB.DLL" (ByVal fILEnAME$) As Integer

'Constants for GetVerInfo function
Global Const VSI_ALL = 0  'Gets 1-8 as one tab delimited string
Global Const VSI_CompanyName = 1
Global Const VSI_FileDescription = 2
Global Const VSI_FileVersion = 3
Global Const VSI_InternalName = 4
Global Const VSI_LegalCopyright = 5
Global Const VSI_LegalTrademarks = 6
Global Const VSI_ProductName = 7
Global Const VSI_ProductVersion = 8
Global Const VSI_InternalFileVersion = 9
Global Const VSI_InternalProductVersion = 10
Global Const VSI_InternalFileFlags = 11
Global Const VSI_InternalOSType = 12
Global Const VSI_InternalFileType = 13
Global Const VSI_InternalFileSubType = 14
Global Const VSI_InternalLanguage = 15

Declare Function vbGetVerInfo Lib "NATIVEVB.DLL" (ByVal fILEnAME$, ByVal InfoItem%) As String

'Net work information
Global Const WSI_Path2Net = 0
Global Const WSI_ComputerName = 1
Global Const WSI_UserName = 2
Global Const WSI_WorkGroup = 3
Global Const WSI_Version = 4
Global Const WSI_MaxTimeInactiveConnection = 5
Global Const WSI_MaxTimeInactiveSearch = 6
Global Const WSI_Server = 7

Declare Function vbWorkStationInfo Lib "NATIVEVB.DLL" (ByVal InfoItem%) As String
Declare Function VBAddConnection Lib "NATIVEVB.DLL" (ByVal Drv$, ByVal UNCPath$, ByVal Pwd$) As String
Declare Function vbGetConnection Lib "NATIVEVB.DLL" (ByVal Drv$) As String
Declare Function NetPrinterDialog Lib "NATIVEVB.DLL" () As Integer
Declare Function NetDriveDialog Lib "NATIVEVB.DLL" () As Integer

' Windows System information
Declare Function vbWindir Lib "NATIVEVB.DLL" () As String
Declare Function vbSysDir Lib "NATIVEVB.DLL" () As String


Global Const WI_x87 = 0
Global Const WI_CPU = 1
Global Const WI_WinMode = 2 'Including Win Nt
Global Const WI_Emulation = 3
Global Const WI_SysRes = 4
Global Const WI_GDIRes = 5
Global Const WI_UserRes = 6
Global Const WI_FreeSpace = 7
Global Const WI_WinVer = 8
Global Const WI_DosVer = 9
Declare Function vbWinInfo Lib "NATIVEVB.DLL" (ByVal indx%) As String
Declare Function vbGetKeyboardState Lib "NATIVEVB.DLL" () As String
Declare Function vbInKey Lib "NATIVEVB.DLL" () As String

Declare Function vbGetTempDrive Lib "NATIVEVB.DLL" () As String
Declare Function vbGetTempfILEnAME Lib "NATIVEVB.DLL" () As String
Declare Function vbnEXTfREEdRIVE Lib "NATIVEVB.DLL" () As String

'File Information
Global Const fI_fILEpATH = 1
Global Const fI_FixedDrive = 2
Global Const fI_Size = 3
Global Const fI_OnDrive = 4
Global Const fI_DateTime = 5 'VB has FileDateTime
Global Const fI_Attributes = 6 'VB has FileDateTime
Declare Function vbfILEiNFO Lib "NATIVEVB.DLL" (ByVal fILEnAME$, ByVal iTEM%) As String

' Drive Information
Global Const DI_Type = 1
Global Const DI_TotalSize = 2
Global Const DI_FreeSpace = 3
Declare Function vbDriveInfo Lib "NATIVEVB.DLL" (ByVal Drv$, ByVal iTEM%) As String

'Demo String Functions
Declare Function vbCountNulls Lib "NATIVEVB.DLL" (Buffer$) As Integer
Declare Function vbAlltrim Lib "NATIVEVB.DLL" (ByVal Buffer$) As String
Declare Function vbChangeChar Lib "NATIVEVB.DLL" (ByVal Buffer$, ByVal Fromchar$, ByVal ToChar$) As String

' Summary Info From OLE
Global Const SI_ALL = 0  'Gets all as one string tab delimited (Max 4096 Bytes!)
Global Const SI_Title = 1
Global Const SI_Subject = 2
Global Const SI_Author = 3
Global Const SI_KeyWords = 4
Global Const SI_Comments = 5
Global Const SI_Template = 6
Global Const SI_LastAuthor = 7
Global Const SI_RevNumber = 8

Global Const SI_EditTime = 9
Global Const SI_LastPrinted = 10
Global Const SI_Create_Date = 11
Global Const SI_LastSave_Date = 12

Global Const SI_PageCount = 13
Global Const SI_WordCount = 14
Global Const SI_CharCount = 15
Global Const SI_ThumbNail = 16'Not Implemented -- To ClipBoard

Global Const SI_AppName = 17
Global Const SI_Security = 18

Declare Function vbSummaryInfo Lib "NATIVEVB.DLL" (ByVal fILEnAME$, ByVal iTEM%) As String
Declare Function vbHasSummaryInfo Lib "NATIVEVB.DLL" (ByVal fILEnAME$) As String


