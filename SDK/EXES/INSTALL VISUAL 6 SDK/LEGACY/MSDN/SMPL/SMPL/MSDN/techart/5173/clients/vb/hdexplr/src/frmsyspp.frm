VERSION 5.00
Begin VB.Form frmSysProp 
   Caption         =   "HelpDesk System Properties"
   ClientHeight    =   1860
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   7350
   LinkTopic       =   "Form1"
   ScaleHeight     =   1860
   ScaleWidth      =   7350
   StartUpPosition =   1  'CenterOwner
   Begin VB.CommandButton btnAction 
      Caption         =   "Action"
      Height          =   372
      Left            =   6240
      TabIndex        =   11
      Top             =   720
      Width           =   972
   End
   Begin VB.CommandButton btnCancel 
      Cancel          =   -1  'True
      Caption         =   "&Cancel"
      Default         =   -1  'True
      Height          =   372
      Left            =   6240
      TabIndex        =   10
      Top             =   1200
      Width           =   972
   End
   Begin VB.TextBox txtChangeDate 
      Height          =   288
      Left            =   5520
      Locked          =   -1  'True
      TabIndex        =   9
      Top             =   120
      Width           =   1692
   End
   Begin VB.ComboBox cmbParmType 
      Height          =   288
      Left            =   1560
      TabIndex        =   7
      Top             =   600
      Width           =   1332
   End
   Begin VB.TextBox txtValue 
      Height          =   288
      Left            =   1560
      TabIndex        =   5
      Top             =   1320
      Width           =   3132
   End
   Begin VB.TextBox txtDescr 
      Height          =   288
      Left            =   1560
      TabIndex        =   3
      Top             =   960
      Width           =   3132
   End
   Begin VB.TextBox txtChangedBy 
      Height          =   288
      Left            =   1560
      Locked          =   -1  'True
      TabIndex        =   1
      Top             =   120
      Width           =   2772
   End
   Begin VB.Label Label5 
      Caption         =   "Changed on:"
      Height          =   252
      Left            =   4440
      TabIndex        =   8
      Top             =   120
      Width           =   972
   End
   Begin VB.Label Label4 
      Caption         =   "Parameter type:"
      Height          =   252
      Left            =   120
      TabIndex        =   6
      Top             =   600
      Width           =   1452
   End
   Begin VB.Label Label3 
      Caption         =   "Value:"
      Height          =   252
      Left            =   120
      TabIndex        =   4
      Top             =   1320
      Width           =   972
   End
   Begin VB.Label Label2 
      Caption         =   "Description:"
      Height          =   252
      Left            =   120
      TabIndex        =   2
      Top             =   960
      Width           =   972
   End
   Begin VB.Label Label1 
      Caption         =   "Changed By:"
      Height          =   252
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   972
   End
End
Attribute VB_Name = "frmSysProp"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
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

Private Const OBJNAME = "frmSysProp"

Public Sub SetParameters(ByVal iAction As SYSPARM_MAINTENANCE, Optional ByVal oSysParm As CSysParm)
Dim otechs As Collection
Dim oTech As CTech
Dim n As Integer

btnAction.Visible = True

Select Case iAction
Case SP_PROPERTY
    btnAction.Visible = False
    
    txtDescr.Locked = True
    txtChangeDate = Format$(oSysParm.ChangeDate, "Short Date")
    Set otechs = g_oTechAdmin.GetTechnicians
    txtChangedBy = "<Unknown>"
    For Each oTech In otechs
        If oTech.PKid = oSysParm.ChangedById Then
            txtChangedBy = oTech.Alias
            Exit For
        End If
    Next oTech
    Set otechs = Nothing
    txtDescr = oSysParm.Desc
    txtValue = oSysParm.SysValue
    
    cmbParmType.Text = LoadResString(icIDS_PH_SELECTFROMLIST)
    For n = 0 To cmbParmType.ListCount - 1
        If cmbParmType.ItemData(n) = oSysParm.ParmTypeId Then
            cmbParmType.Text = cmbParmType.List(n)
            Exit For
        End If
    Next n

Case SP_ADD
    btnAction.Caption = LoadResString(icIDS_BTN_ADDNEW)

Case SP_UPDATE
    btnAction.Caption = LoadResString(icIDS_BTN_UPDATE)

End Select

End Sub


Private Function InvokeError(ByVal ErrorID As RES_IDS, Optional ByVal ErrorMsg As String) As Boolean
Dim sMsg As String
Dim lErr As Long

    sMsg = Trim$(App.Title) & ":" & OBJNAME
    lErr = Err
    
    If ErrorID = 0 Then
        sMsg = sMsg & " " & ErrorMsg
    Else
        sMsg = sMsg & " " & LoadResString(ErrorID)
    End If
    
    If Err < vbObjectError Then
        lErr = lErr + vbObjectError
    End If
    
    Err.Raise lErr, sMsg, Err.Description
End Function





Private Sub btnCancel_Click()

    Unload Me

End Sub


Private Sub Form_Load()
    
Dim oSysParmType As CSysParmType
Dim cColl As Collection

Set cColl = g_oSysAdmin.GetSysParmTypes
For Each oSysParmType In cColl
    cmbParmType.AddItem oSysParmType.Desc
    cmbParmType.ItemData(cmbParmType.NewIndex) = oSysParmType.PKid
Next oSysParmType
Set cColl = Nothing
    
End Sub


