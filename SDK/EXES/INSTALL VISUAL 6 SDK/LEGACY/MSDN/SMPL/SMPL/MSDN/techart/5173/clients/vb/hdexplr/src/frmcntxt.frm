VERSION 5.00
Begin VB.Form frmContext 
   BorderStyle     =   0  'None
   ClientHeight    =   600
   ClientLeft      =   120
   ClientTop       =   405
   ClientWidth     =   7395
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   NegotiateMenus  =   0   'False
   ScaleHeight     =   600
   ScaleWidth      =   7395
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.Menu mnu_lv_Location 
      Caption         =   "Location"
      Begin VB.Menu mnu_lv_location_Update 
         Caption         =   "&Update location"
      End
   End
   Begin VB.Menu mnu_lv_Skill 
      Caption         =   "Skill"
      Begin VB.Menu mnu_lv_Skill_Update 
         Caption         =   "&Update skill"
      End
   End
   Begin VB.Menu mnu_lv_Priority 
      Caption         =   "Priority"
      Begin VB.Menu mnu_lv_Priority_Update 
         Caption         =   "&Update priority"
      End
   End
   Begin VB.Menu mnu_lv_Technician 
      Caption         =   "Technician"
      Begin VB.Menu mnu_lv_Technician_Properties 
         Caption         =   "&Properties"
      End
      Begin VB.Menu mnu_lv_Technician_Sep1 
         Caption         =   "-"
      End
      Begin VB.Menu mnu_lv_Technician_Delete 
         Caption         =   "&Delete technician"
      End
      Begin VB.Menu mnu_lv_Technician_Update 
         Caption         =   "&Update technician"
      End
      Begin VB.Menu mnu_lv_Technician_Sep2 
         Caption         =   "-"
      End
      Begin VB.Menu mnu_lv_Technician_Requests 
         Caption         =   "&Requests"
      End
   End
   Begin VB.Menu mnu_lv_SysParm 
      Caption         =   "System"
      Begin VB.Menu mnu_lv_SysParm_Properties 
         Caption         =   "&Properties"
      End
      Begin VB.Menu mnu_lv_SysParm_Sep1 
         Caption         =   "-"
      End
      Begin VB.Menu mnu_lv_SysParm_Update 
         Caption         =   "&Update"
      End
   End
   Begin VB.Menu mnu_lv_AddMenu 
      Caption         =   "AddMenu"
      Begin VB.Menu mnu_lv_AddMenu_AddNew 
         Caption         =   "&Add new"
      End
   End
End
Attribute VB_Name = "frmContext"
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
Dim m_Selected_Context As CONTEXT_MENUS

Private Sub Form_Load()
    m_Selected_Context = 0
End Sub

Public Property Get Selected_Context() As CONTEXT_MENUS
    Selected_Context = m_Selected_Context
End Property

Public Property Let Selected_Context(iValue As CONTEXT_MENUS)
    m_Selected_Context = iValue
End Property
Private Sub mnu_lv_AddMenu_AddNew_Click()
    m_Selected_Context = CM_ADDMENU_ADDNEW
End Sub

Private Sub mnu_lv_Location_Update_Click()
    m_Selected_Context = CM_DOMAIN_UPDATE
End Sub

Private Sub mnu_lv_Priority_Update_Click()
    m_Selected_Context = CM_DOMAIN_UPDATE
End Sub

Private Sub mnu_lv_Skill_Update_Click()
    m_Selected_Context = CM_DOMAIN_UPDATE
End Sub

Private Sub mnu_lv_SysParm_Properties_Click()
    m_Selected_Context = CM_SYSTEM_SYSPARM_PROPERTIES
End Sub

Private Sub mnu_lv_Technician_Delete_Click()
    m_Selected_Context = CM_TECHNICIAN_DELETE
End Sub

Private Sub mnu_lv_Technician_Properties_Click()
    m_Selected_Context = CM_TECHNICIAN_PROPERTIES
End Sub

Private Sub mnu_lv_Technician_Requests_Click()
    m_Selected_Context = CM_TECHNICIAN_REQUESTS
End Sub


Private Sub mnu_lv_Technician_Update_Click()
    m_Selected_Context = CM_TECHNICIAN_UPDATE
End Sub
