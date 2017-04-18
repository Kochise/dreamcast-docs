Attribute VB_Name = "basGlobal"
'Copyright (C) 1998 Microsoft Corporation
'All rights reserved.
'
'THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER
'EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
'MERCHANTIBILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
'
'Date    - 02/01/98
'Authors - Robert Coleridge, Steve Kirk, Fred Pace, Kevin Marzec, Dale Smith
'
Public Const scSpace = " "
Public Const scSpaceCommaSpace = " , "
Public Const scSQ = "'"
Public Const scZeroStr = " 0 "
Public Const scOutput = " output"

'This enumeration represents the differenct dimensions of an array
Public Enum enumArrayOffsets
    icZeroDim = 0
    icOneDim = 1
    icTwoDim = 2
    icThreeDim = 3
    icFourDim = 4
    icFiveDim = 5
    icSixDim = 6
End Enum
Public Function ItemPKId(ByVal iPKid As Integer) As String
    ItemPKId = "ID=" & CStr(iPKid)
End Function

