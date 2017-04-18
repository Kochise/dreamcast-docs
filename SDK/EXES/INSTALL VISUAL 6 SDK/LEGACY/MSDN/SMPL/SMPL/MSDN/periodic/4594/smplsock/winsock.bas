Attribute VB_Name = "WinSock"
'--------------------------------------------------------
' WINSOCK.BAS
'   This file contains Declares for some of the more
'   popular Windows Socket functions.


Global sock As Long ' Our own personal socket!
Global port As Integer

Global iCurrAction As Integer
Global iCurrMsg As Long
Global gParsing As Boolean

Global Const TASK_CONNECT = 1
Global Const TASK_GETHDR = 2
Global Const TASK_GETGRP = 3

Global Const SOCKET_ERROR = -1
Global Const FD_READ = &H1
Global Const FD_WRITE = &H2
Global Const FD_OOB = &H4
Global Const FD_ACCEPT = &H8
Global Const FD_CONNECT = &H10
Global Const FD_CLOSE = &H20

#If Win16 Then
Declare Function oBind Lib "winsock.dll" Alias "bind" (ByVal s As Integer, Addr As sockaddr_in, ByVal namelen As Integer) As Integer
Declare Function htonl Lib "winsock.dll" (ByVal a As Long) As Long
Declare Function inet_addr Lib "winsock.dll" (ByVal s As String) As Long
Declare Function inet_ntoa Lib "winsock.dll" (ByVal inn As Long) As Long
Declare Function ntohl Lib "winsock.dll" (ByVal a As Long) As Long
Declare Function oSocket Lib "winsock.dll" Alias "socket" (ByVal af As Integer, ByVal typesock As Integer, ByVal protocol As Integer) As Integer
Declare Function htons Lib "winsock.dll" (ByVal a As Integer) As Integer
Declare Function ntohs Lib "winsock.dll" (ByVal a As Integer) As Integer
Declare Function oConnect Lib "winsock.dll" Alias "connect" (ByVal sock As Integer, sockstruct As sockaddr_in, ByVal structlen As Integer) As Integer
Declare Function send Lib "winsock.dll" (ByVal sock As Integer, ByVal msg As String, ByVal msglen As Integer, ByVal flag As Integer) As Integer
Declare Function recv Lib "winsock.dll" (ByVal sock As Integer, ByVal msg As String, ByVal msglen As Integer, ByVal flag As Integer) As Integer
Declare Function getsockname Lib "winsock.dll" (ByVal s As Integer, Addr As Any, ByVal namelen As Integer) As Integer
Declare Function getservbyname Lib "winsock.dll" (ByVal nm As String, ByVal proto As String) As Long

Declare Function WSAStartup Lib "winsock.dll" (ByVal a As Integer, b As WSAdata_type) As Integer
Declare Function WSACleanup Lib "winsock.dll" () As Integer
Declare Function WSAGetLastError Lib "winsock.dll" () As Integer

Declare Function lstrcpyn Lib "kernel" (ByVal lpszString1 As Any, ByVal lpszString2 As Long, ByVal cChars As Integer) As String
Declare Sub hmemcpy Lib "kernel" (hpvDest As Any, hpvSource As Any, ByVal cbCopy As Long)

#Else
'Declare Function oBind Lib "wsock32.dll" Alias "bind" (ByVal s As Integer, Addr As sockaddr_in, ByVal namelen As Integer) As Integer
Declare Function htonl Lib "wsock32.dll" (ByVal a As Long) As Long
Declare Function inet_addr Lib "wsock32.dll" (ByVal s As String) As Long
Declare Function inet_ntoa Lib "wsock32.dll" (ByVal inn As Long) As Long
Declare Function ntohl Lib "wsock32.dll" (ByVal a As Long) As Long
Declare Function oSocket Lib "wsock32.dll" Alias "socket" (ByVal af As Integer, ByVal typesock As Integer, ByVal protocol As Integer) As Integer
Declare Function htons Lib "wsock32.dll" (ByVal a As Integer) As Integer
Declare Function ntohs Lib "wsock32.dll" (ByVal a As Integer) As Integer
'Declare Function oConnect Lib "wsock32.dll" Alias "connect" (ByVal sock As Integer, sockstruct As sockaddr_in, ByVal structlen As Integer) As Integer
Declare Function send Lib "wsock32.dll" (ByVal sock As Integer, ByVal msg As String, ByVal msglen As Integer, ByVal flag As Integer) As Integer
Declare Function recv Lib "wsock32.dll" (ByVal sock As Integer, ByVal msg As String, ByVal msglen As Integer, ByVal flag As Integer) As Integer

'Declare Function getsockname Lib "wsock32.dll" (ByVal s As Integer, Addr As sockaddr_in, ByVal namelen As Integer) As Integer
Declare Function ogetservbyname Lib "wsock32.dll" Alias "getservbyname" (ByVal nm As String, ByVal proto As String) As Long
Declare Function gethostname Lib "wsock32.dll" (ByVal s As String, ByVal l As Integer) As Integer
Declare Function gethostbyname Lib "wsock32.dll" (ByVal s As String) As Long

'Declare Function WSAStartup Lib "wsock32.dll" (ByVal a As Integer, b As WSAdata_type) As Integer
Declare Function WSACleanup Lib "wsock32.dll" () As Integer
Declare Function WSAGetLastError Lib "wsock32.dll" () As Integer
Declare Function WSAAsyncGetHostByName Lib "wsock32.dll" (ByVal hWnd As Integer, ByVal wMsg As Integer, ByVal name As String, ByVal buf As String, ByVal buflen As Integer) As Integer

Declare Function lstrcpyn Lib "kernel32" Alias "lstrcpynA" (ByVal lpString1 As Any, ByVal lpString2 As Long, ByVal iMaxLength As Long) As Long
Declare Sub hmemcpy Lib "kernel32" (hpvDest As Any, hpvSource As Any, ByVal cbCopy As Long)

#End If

