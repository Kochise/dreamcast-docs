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

'local variable(s) to hold property value(s)
Private mvarPKId As Long 'local copy
Private mvarChangedById As Long 'local copy
Private mvarParmTypeId As Long 'local copy
Private mvarChangeDate As Date 'local copy
Private mvarDesc As String 'local copy
Private mvarSysValue As String 'local copy

Public Property Let SysValue(ByVal vData As String)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.SysValue = 5
    mvarSysValue = vData
End Property


Public Property Get SysValue() As String
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.SysValue
    SysValue = mvarSysValue
End Property



Public Property Let Desc(ByVal vData As String)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.Desc = 5
    mvarDesc = vData
End Property


Public Property Get Desc() As String
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.Desc
    Desc = mvarDesc
End Property



Public Property Let ChangeDate(ByVal vData As Date)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.ChangeDate = 5
    mvarChangeDate = vData
End Property


Public Property Get ChangeDate() As Date
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.ChangeDate
    ChangeDate = mvarChangeDate
End Property



Public Property Let ParmTypeId(ByVal vData As Long)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.ParmTypeId = 5
    mvarParmTypeId = vData
End Property


Public Property Get ParmTypeId() As Long
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.ParmTypeId
    ParmTypeId = mvarParmTypeId
End Property



Public Property Let ChangedById(ByVal vData As Long)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.ChangedById = 5
    mvarChangedById = vData
End Property


Public Property Get ChangedById() As Long
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.ChangedById
    ChangedById = mvarChangedById
End Property

Public Sub Term()
End Sub


Public Property Get PKid() As Long
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.PKid
    PKid = mvarPKId
End Property

Public Property Let PKid(ByVal vData As Long)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.PKId = 5
    mvarPKId = vData
End Property
