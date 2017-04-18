VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CNetGet"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit ' force variable declarations

' opens and initializes an internet connection
Private Declare Function InternetOpen Lib "wininet.dll" Alias "InternetOpenA" _
        (ByVal lpszAgent As String, ByVal dwAccessType As Long, ByVal lpszProxyName As String, _
         ByVal lpszProxyBypass As String, ByVal dwFlags As Long) As Long

' closes a internet connection or URL handle
Private Declare Function InternetCloseHandle Lib "wininet.dll" (ByVal hInet As Long) As Integer

' opens a URL
Private Declare Function InternetOpenUrl Lib "wininet.dll" Alias "InternetOpenUrlA" _
        (ByVal hInternetSession As Long, ByVal lpszUrl As String, ByVal lpszHeaders As String, _
         ByVal dwHeadersLength As Long, ByVal dwFlags As Long, ByVal dwContext As Long) As Long

' reads data from a URL
Private Declare Function InternetReadFile Lib "wininet.dll" _
        (ByVal hFile As Long, ByVal lpBuffer As String, ByVal dwNumberOfBytesToRead As Long, _
         lNumberOfBytesRead As Long) As Integer

Private Const INTERNET_OPEN_TYPE_PRECONFIG = 0   ' indicates to use config info from registry
Private Const INTERNET_FLAG_EXISITING_CONNECT = &H20000000
Private Const INTERNET_FLAG_RELOAD = &H80000000  ' read from wire even if locally cached
Private Const scTagDelimiter = """>?#"           ' default delimiter when scanning HTML
Private Const scBlankStr = ""                    ' blank string constant

Private hInternetSession    As Long     ' internet session handle
Private bInitialized        As Boolean  ' object initialization flag
Private hUrlFile            As Long     ' utl handle
Private sContents           As String   ' html page contents
Private sLastError          As String   ' last dll error buffer
Private sStatus             As String   ' object status buffer
Private objWindow           As Object   ' status message window
Private sUserAgent          As String   ' user agent in HTTP protocol

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : CheckError
' Purpose    : Sets the sLastError private variable
' Parameters : NA
' Return val : NA
' Algorithm  : Interrogates the LastDllError property of the Err object
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Sub CheckError()
Dim lLastErrorNo As Long
' Retrieve the LastDllError property of the Err object
lLastErrorNo = Err.LastDllError
If lLastErrorNo > 0 Then sLastError = TranslateErrorCode(lLastErrorNo)
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : Init
' Purpose    : Initializes instance of CNetGet object
' Parameters : Optional user agent string
' Return val : NA
' Algorithm  : Allocates session handle and initializes private class variables
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Sub Init(Optional vInUserAgent As Variant)
On Error Resume Next
If IsMissing(vInUserAgent) Then
    sUserAgent = App.EXEName
Else
    sUserAgent = vInUserAgent
End If
Term
hUrlFile = 0
sContents = scBlankStr
sLastError = scBlankStr
sStatus = scBlankStr
hInternetSession = InternetOpen(sUserAgent, INTERNET_OPEN_TYPE_PRECONFIG, vbNullString, vbNullString, 0)
bInitialized = CBool(hInternetSession)
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : ParseHTML
' Purpose    : Parses strings from the sContents private variable
' Parameters : Token to scan for, a collection to add to, and a delimiter string
' Return val : True or False
' Algorithm  : Finds token, scans until delimiter, then adds to collection
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Function ParseHTML(ByVal sToken As String, colItems As Collection, _
                                Optional ByVal vDelimiter As Variant) As Boolean
Dim lPosInStr As Long
Dim lEndPosInStr As Long
Dim lStartPos As Long
Dim iCounter As Integer
Dim iRetVal As Integer
Dim sAddItem As String
Dim sUseDelimiter As String
On Error Resume Next
Screen.MousePointer = vbHourglass
SetStatus "Parsing page..."
If Len(sContents) > Len(sToken) Then
    If IsMissing(vDelimiter) Then
        sUseDelimiter = scTagDelimiter
    Else
        sUseDelimiter = CStr(vDelimiter)
    End If
    lStartPos = 1
    lPosInStr = InStr(lStartPos, sContents, sToken, 1)
    While CBool(lPosInStr)
        iCounter = 0
        lPosInStr = lPosInStr + Len(sToken)
        Do
            iRetVal = InStr(1, sUseDelimiter, Mid$(sContents, lPosInStr + iCounter, 1), 1)
            iCounter = iCounter + 1
        Loop While Not CBool(iRetVal)
        sAddItem = StripChars(Mid$(sContents, lPosInStr, iCounter - 1))
        If Len(sAddItem) Then colItems.Add sAddItem, sAddItem
        lStartPos = lPosInStr + iCounter
        lPosInStr = InStr(lStartPos, sContents, sToken, 1)
    Wend
    ParseHTML = True
End If
SetStatus "Ready"
Screen.MousePointer = vbDefault
End Function

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : ReadUrl
' Purpose    : Retrieves contents from a given URL
' Parameters : String containing the URL to read
' Return val : Integer indicating success or failure
' Algorithm  : Calls the WinInet functions to retrieve the URL
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Function ReadUrl(ByVal sUrl As String, Optional vFileName As Variant) As Boolean
Dim sReadBuffer         As String * 2048 ' bytes to read from call to InternetReadFile
Dim lNumberOfBytesRead  As Long         ' bytes read from call to InternetReadFile
Dim lTotalBytesRead     As Long         ' total bytes read
Dim bDoLoop             As Boolean      ' return value from InternetReadFile
Dim bReadInternetFile   As Boolean
Dim bWriteToFile        As Boolean
On Error GoTo errReadUrl
Screen.MousePointer = vbHourglass
SetStatus "Opening: " & sUrl
If Not IsMissing(vFileName) Then
    Dim iFileNum As Integer
    iFileNum = FreeFile
    Open CStr(vFileName) For Binary As iFileNum
    bWriteToFile = True
End If
hUrlFile = InternetOpenUrl(hInternetSession, sUrl, vbNullString, 0, INTERNET_FLAG_EXISITING_CONNECT, 0)
If CBool(hUrlFile) Then
    sContents = scBlankStr
    bDoLoop = True
    While bDoLoop
        sReadBuffer = scBlankStr
        bDoLoop = InternetReadFile(hUrlFile, sReadBuffer, Len(sReadBuffer), lNumberOfBytesRead)
        If Not CBool(bDoLoop) Then CheckError
        lTotalBytesRead = lTotalBytesRead + lNumberOfBytesRead
        SetStatus "Reading Url: " & CStr(lTotalBytesRead) & " bytes read"
        If CBool(lNumberOfBytesRead) Then
            If bWriteToFile Then
                Put #iFileNum, , sReadBuffer
            Else
                sContents = sContents & Left$(sReadBuffer, lNumberOfBytesRead)
            End If
        Else
            bDoLoop = False
            bReadInternetFile = True
        End If
    Wend
    InternetCloseHandle (hUrlFile)
    If bWriteToFile Then Close
    ReadUrl = True
Else
    CheckError
End If
SetStatus "Ready"
Screen.MousePointer = vbDefault
Exit Function
errReadUrl:
sLastError = Error$(Err)
Screen.MousePointer = vbDefault
Exit Function
End Function

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : SetStatus
' Purpose    : Sets the private status member
' Parameters : Optional new status message
' Return val : NA
' Algorithm  : Sets to new status
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub SetStatus(sInStatus As String)
On Error Resume Next
objWindow = sInStatus
DoEvents
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : StripChars
' Purpose    : Removes linefeeds, etc.
' Parameters : String to process
' Return val : String without the unwanted characters
' Algorithm  : Iterates through the string and removes ascii values 9 - 13
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Function StripChars(ByVal sInput As String) As String
Dim iCounter    As Integer
Dim iAscValue   As Integer
Dim sOutPut     As String
On Error Resume Next
' Scan through source string and remove the following characters:
' 9  Horizontal Tab
' 10 Linefeed
' 11 Vertical Tab
' 12 Form Feed
' 13 Carriage Return
For iCounter = 1 To Len(sInput)
    iAscValue = Asc(Mid$(sInput, iCounter, 1))
    If Not (iAscValue >= 9 And iAscValue <= 13) Then sOutPut = sOutPut & Chr$(iAscValue)
Next iCounter
StripChars = sOutPut
End Function

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : Term
' Purpose    : Frees resources associated with instance of class
' Parameters : NA
' Return val : NA
' Algorithim : Closes the Internet session handle
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Sub Term()
On Error Resume Next
If InternetCloseHandle(hInternetSession) Then
    bInitialized = False
    SetStatus ("Ready")
Else
    CheckError
End If
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : TranslateErrorCode
' Purpose    : Provides message corresponding to DLL error codes
' Parameters : The DLL error code
' Return val : String containing message
' Algorithim : Selects the appropriate string
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Function TranslateErrorCode(ByVal lErrorCode As Long) As String
Select Case lErrorCode
    Case 12001: TranslateErrorCode = "No more handles could be generated at this time"
    Case 12002: TranslateErrorCode = "The request has timed out."
    Case 12003: TranslateErrorCode = "An extended error was returned from the server."
    Case 12004: TranslateErrorCode = "An internal error has occurred."
    Case 12005: TranslateErrorCode = "The URL is invalid."
    Case 12006: TranslateErrorCode = "The URL scheme could not be recognized, or is not supported."
    Case 12007: TranslateErrorCode = "The server name could not be resolved."
    Case 12008: TranslateErrorCode = "The requested protocol could not be located."
    Case 12009: TranslateErrorCode = "A request to InternetQueryOption or InternetSetOption specified an invalid option value."
    Case 12010: TranslateErrorCode = "The length of an option supplied to InternetQueryOption or InternetSetOption is incorrect for the type of option specified."
    Case 12011: TranslateErrorCode = "The request option can not be set, only queried. "
    Case 12012: TranslateErrorCode = "The Win32 Internet support is being shutdown or unloaded."
    Case 12013: TranslateErrorCode = "The request to connect and login to an FTP server could not be completed because the supplied user name is incorrect."
    Case 12014: TranslateErrorCode = "The request to connect and login to an FTP server could not be completed because the supplied password is incorrect. "
    Case 12015: TranslateErrorCode = "The request to connect to and login to an FTP server failed."
    Case 12016: TranslateErrorCode = "The requested operation is invalid. "
    Case 12017: TranslateErrorCode = "The operation was canceled, usually because the handle on which the request was operating was closed before the operation completed."
    Case 12018: TranslateErrorCode = "The type of handle supplied is incorrect for this operation."
    Case 12019: TranslateErrorCode = "The requested operation can not be carried out because the handle supplied is not in the correct state."
    Case 12020: TranslateErrorCode = "The request can not be made via a proxy."
    Case 12021: TranslateErrorCode = "A required registry value could not be located. "
    Case 12022: TranslateErrorCode = "A required registry value was located but is an incorrect type or has an invalid value."
    Case 12023: TranslateErrorCode = "Direct network access cannot be made at this time. "
    Case 12024: TranslateErrorCode = "An asynchronous request could not be made because a zero context value was supplied."
    Case 12025: TranslateErrorCode = "An asynchronous request could not be made because a callback function has not been set."
    Case 12026: TranslateErrorCode = "The required operation could not be completed because one or more requests are pending."
    Case 12027: TranslateErrorCode = "The format of the request is invalid."
    Case 12028: TranslateErrorCode = "The requested item could not be located."
    Case 12029: TranslateErrorCode = "The attempt to connect to the server failed."
    Case 12030: TranslateErrorCode = "The connection with the server has been terminated."
    Case 12031: TranslateErrorCode = "The connection with the server has been reset."
    Case 12036: TranslateErrorCode = "The request failed because the handle already exists."
    Case Else: TranslateErrorCode = "Error details not available."
End Select
End Function

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : SetStatusWindow
' Purpose    : Sets the status window property
' Parameters : Status Window object
' Return val : NA
' Algorithim : Sets the private status window variable
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Property Let SetStatusWindow(objStatusWindow As Object)
On Error Resume Next
Set objWindow = objStatusWindow
End Property

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : GetRawHTML
' Purpose    : Interface to the private html contents buffer
' Parameters : NA
' Return val : String with contents of URL
' Algorithim : Returns the contents of the private sContents variable
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Property Get GetRawHTML() As String
' Return a copy of the sContents buffer without any
' trailing or leading spaces.
GetRawHTML = Trim$(sContents)
End Property

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : GetLastError
' Purpose    : Interface to the private sLastError variable
' Parameters : NA
' Return val : String with contents of sLastError
' Algorithim : Returns the contents of the private sLastError variable
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Property Get GetLastError() As String
GetLastError = sLastError
End Property

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : SetUserAgent
' Purpose    : Allow specification of User Agent
' Parameters : User Agent to use
' Return val : NA
' Algorithim : Sets the private sUserAgent variable
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Property Let SetUserAgent(sInUserAgent As String)
If Len(sInUserAgent) > 0 Then sUserAgent = sInUserAgent
End Property

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : Class_Terminate
' Purpose    : Calls Term subroutine if Term sub not explicitly called
' Parameters : NA
' Return val : NA
' Algorithim : Calls Term sub when class is termintated
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub Class_Terminate()
Term
End Sub
