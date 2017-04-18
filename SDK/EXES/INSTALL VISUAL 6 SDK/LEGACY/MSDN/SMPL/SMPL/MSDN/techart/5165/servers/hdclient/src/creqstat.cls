VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CReqStatus"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Attribute VB_Ext_KEY = "SavedWithClassBuilder" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
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
Option Explicit

Private Const OBJNAME = "CReqStatus"

Dim m_sDesc As String
Dim m_lPKId As Long
Dim m_sCode As String

'=======================================================================
'Attribute:     Returns the description for the request status object.
'=======================================================================
Public Property Get Desc() As String
Desc = m_sDesc
End Property

'=======================================================================
'Attribute:     Sets the description for the request status object.
'=======================================================================
Public Property Let Desc(ByVal sNewValue As String)
m_sDesc = sNewValue
End Property

'=======================================================================
'Attribute:     Returns the PK identifier for the request status object.
'=======================================================================
Public Property Get PKId() As Long
PKId = m_lPKId
End Property

'=======================================================================
'Attribute:     Sets the PK identifier for the request status object.
'=======================================================================
Public Property Let PKId(ByVal lNewValue As Long)
m_lPKId = lNewValue
End Property

'=======================================================================
'Attribute:     Returns the code for the request status object.
'=======================================================================
Public Property Get Code() As String
Code = m_sCode
End Property

'=======================================================================
'Attribute:     Sets the code for the request status object.
'=======================================================================
Public Property Let Code(ByVal sNewValue As String)
m_sCode = sNewValue
End Property

