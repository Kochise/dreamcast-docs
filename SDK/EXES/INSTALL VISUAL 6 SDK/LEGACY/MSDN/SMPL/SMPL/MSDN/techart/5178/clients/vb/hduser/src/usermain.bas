Attribute VB_Name = "basMain"
'Copyright (C) 1998 Microsoft Corporation
'All rights reserved.
'
'THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER
'EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
'MERCHANTIBILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
'
'Date         - 01/05/98
'Author       - Venu Yerra
'
Option Explicit
'=======================================================================
'   HelpDesk project - Visual Basic Client
'   Microsoft Corporation
'   Date : 14 October 1997
'   Synopsis :  This is public BAS for constants to be used in User client
'
'=======================================================================

'public objects
Public g_oAdmin      As HDClient.CAdmin
Public g_sEAlias     As String
Public g_lLocationId As Long
Public g_lPriorityId As Long


'Enumeration to be used in place of numbers
Enum NumberSys
    icNumberZero = 0
    icNumberOne = 1
    icNumberTwo = 2
End Enum
Sub Main()

    g_lLocationId = -1
    g_lPriorityId = -1

    frmUserReq.Show vbModal
    End
    
End Sub


