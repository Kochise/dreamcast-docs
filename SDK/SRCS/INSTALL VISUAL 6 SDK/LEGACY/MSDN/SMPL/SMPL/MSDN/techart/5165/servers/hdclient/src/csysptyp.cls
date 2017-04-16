VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CSysParmType"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit
'Copyright (C) 1998 Microsoft Corporation
'All rights reserved.
'
'THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER
'EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
'MERCHANTIBILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
'
'Date         - 01/05/98
'Authors      - Robert Coleridge, Fred Pace, Steve Kirk
'

Private m_sDesc As String
Private m_lPKId As Long
Private m_sCode As String
Public Property Get Desc() As String
Desc = m_sDesc
End Property
Friend Property Let Desc(ByVal sNewValue As String)
m_sDesc = sNewValue
End Property
Public Property Get PKid() As Long
PKid = m_lPKId
End Property
Friend Property Let PKid(ByVal lNewValue As Long)
m_lPKId = lNewValue
End Property
Public Property Get Code() As String
Code = m_sCode
End Property
Friend Property Let Code(ByVal sNewValue As String)
m_sCode = sNewValue
End Property


