VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CSysParm"
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

Private Const OBJNAME = "CSysParm"

'local variable(s) to hold property value(s)
Private mvarPKId As Long 'local copy
Private mvarChangedById As Long 'local copy
Private mvarParmTypeId As Long 'local copy
Private mvarChangeDate As Date 'local copy
Private mvarDesc As String 'local copy
Private mvarSysValue As String 'local copy

'=======================================================================
'Attribute:     Sets the system value for the system parameter.
'=======================================================================
Public Property Let SysValue(ByVal vData As String)
    mvarSysValue = vData
End Property

'=======================================================================
'Attribute:     Returns the system value for the system parameter.
'=======================================================================
Public Property Get SysValue() As String
    SysValue = mvarSysValue
End Property

'=======================================================================
'Attribute:     Sets the description for the system parameter.
'=======================================================================
Public Property Let Desc(ByVal vData As String)
    mvarDesc = vData
End Property

'=======================================================================
'Attribute:     Returns the description for the system parameter.
'=======================================================================
Public Property Get Desc() As String
    Desc = mvarDesc
End Property

'=======================================================================
'Attribute:     Sets the change date for the system parameter.
'=======================================================================
Public Property Let ChangeDate(ByVal vData As Date)
    mvarChangeDate = vData
End Property

'=======================================================================
'Attribute:     Returns the change date for the system parameter.
'=======================================================================
Public Property Get ChangeDate() As Date
    ChangeDate = mvarChangeDate
End Property

'=======================================================================
'Attribute:     Sets the parameter type identifier for the system parameter.
'=======================================================================
Public Property Let ParmTypeId(ByVal vData As Long)
    mvarParmTypeId = vData
End Property

'=======================================================================
'Attribute:     Returns the parameter type identifier for the system parameter.
'=======================================================================
Public Property Get ParmTypeId() As Long
    ParmTypeId = mvarParmTypeId
End Property

'=======================================================================
'Attribute:     Sets the changed by identifier for the system parameter.
'=======================================================================
Public Property Let ChangedById(ByVal vData As Long)
    mvarChangedById = vData
End Property

'=======================================================================
'Attribute:     Returns the changed by identifier for the system parameter.
'=======================================================================
Public Property Get ChangedById() As Long
    ChangedById = mvarChangedById
End Property

Public Sub Term()
End Sub

'=======================================================================
'Attribute:     Returns the PK identifier for the system parameter.
'=======================================================================
Public Property Get PKid() As Long
    PKid = mvarPKId
End Property

'=======================================================================
'Attribute:     Sets the PK identifier for the system parameter.
'=======================================================================
Public Property Let PKid(ByVal vData As Long)
    mvarPKId = vData
End Property
