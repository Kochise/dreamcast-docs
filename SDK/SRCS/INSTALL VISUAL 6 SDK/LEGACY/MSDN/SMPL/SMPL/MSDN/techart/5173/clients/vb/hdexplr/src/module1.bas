Attribute VB_Name = "basMain"
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
Private Const OBJNAME = "basMain"

Private Declare Function GetUserName Lib "advapi32.dll" Alias "GetUserNameA" (ByVal lpbuffer As String, nSize As Long) As Long

Type TagStruct
    sTag As String
    sValue As String
End Type

Global Const LISTVIEW_BUTTON = 11

Public Enum DOMAIN_MAINTENANCE
    DM_ADD = 1
    DM_DELETE = 2
    DM_UPDATE = 3
End Enum

Public Enum SYSPARM_MAINTENANCE
    SP_PROPERTY = 1
    SP_ADD = 2
    SP_UPDATE = 3
End Enum

Public Enum TECH_MAINTENANCE
    TECH_ADD = 1
    TECH_DELETE = 2
    TECH_UPDATE = 3
End Enum

Public Enum CONTEXT_MENUS
    CM_NOTHING_SELECTED = 0
    CM_ADDMENU_ADDNEW = 11
    CM_DOMAIN_ADD = 21
    CM_DOMAIN_UPDATE = 22
    CM_TECHNICIAN_ADD = 31
    CM_TECHNICIAN_DELETE = 32
    CM_TECHNICIAN_UPDATE = 33
    CM_TECHNICIAN_PROPERTIES = 34
    CM_TECHNICIAN_REQUESTS = 35
    CM_SYSTEM_SYSPARM_PROPERTIES = 41
End Enum

Public g_frmMainForm As frmMain
Public g_oTechAdmin As hdclient.CAdmin
Public g_oSysAdmin As hdadmin.CAdmin
Public g_oHDExt As hdextlib.CHDExt

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

Sub Main()
    Dim sBuffer As String
    Dim lSize As Long
    Dim sUser As String
    Dim cTags As Collection
    Dim n As Integer
    Dim bResult As Boolean

    'instantiate Extension library
    Set g_oHDExt = New hdextlib.CHDExt
    
    'get user name
    sBuffer = Space$(255)
    lSize = Len(sBuffer)
    Call GetUserName(sBuffer, lSize)
    If lSize > 0 Then
        sUser = Left$(sBuffer, lSize - 1)
    Else
        MsgBox LoadResString(icIDS_ERR_INVALIDUSERNAME)
        End
    End If
    
    'Adjust splash screen and show it
    frmSplash.Show
    frmSplash.Refresh
    DoEvents

    'initialize for logged-in user. If valid then do main screen, else fail
    bResult = basMain.Initialize(sUser, False)
    If Not bResult Then
        Set cTags = New Collection
        cTags.Add sUser, "USER"
        n = MsgBox(g_oHDExt.ReplaceTags(LoadResString(icIDS_ADDADMINTECH), cTags), vbYesNo)
        Set cTags = Nothing
        If n = vbYes Then
            bResult = basMain.Initialize(sUser, True)
        End If
    End If
    
    If bResult Then
        Set g_frmMainForm = New frmMain
        g_frmMainForm.FillInitialList
        Load g_frmMainForm
        Unload frmSplash
        g_frmMainForm.Show
    Else
        Unload frmSplash
        End
    End If
    
End Sub

Public Function Initialize(ByVal sUser As String, ByVal bForceAddUser As Boolean) As Boolean
Dim oTech As CTech
Dim bResult As Boolean
Dim cSkills As Collection
Dim oSkill As CSkill
Dim cLocs As Collection
Dim oLoc As CLocation

bResult = False

'get data for this technician
Set g_oTechAdmin = New hdclient.CAdmin
Set oTech = g_oTechAdmin.GetTechByAlias(sUser)

'if we can't find the tech and we are not forcing our way in
If oTech Is Nothing And Not bForceAddUser Then
    Set g_oTechAdmin = Nothing
Else
    'init for this user
    bResult = g_oTechAdmin.Init(sUser, icTECH_LOGGED_IN)
    
    'if found the set for success and exit
    If bResult Then
        Set g_oSysAdmin = New hdadmin.CAdmin
        Set oTech = Nothing
        Initialize = True
    Else
        'if forcing our way in
        If bForceAddUser Then
            'create new technician
            Set g_oSysAdmin = New hdadmin.CAdmin
            
            Set oTech = Nothing
            Set oTech = New CTech
            
            oTech.Alias = sUser
            
            oTech.LocationId = 0
            Set cLocs = g_oTechAdmin.GetLocations
            For Each oLoc In cLocs
                If Trim(UCase(oLoc.Code)) = Trim(UCase(LoadResString(icIDS_INITIALADMINLOCATION))) Then
                    oTech.LocationId = oLoc.PKid
                    Exit For
                End If
            Next oLoc
            Set cLocs = Nothing
            
            oTech.SkillId = 0
            Set cSkills = g_oTechAdmin.GetSkills
            For Each oSkill In cSkills
                If Trim(UCase(oSkill.Code)) = Trim(UCase(LoadResString(icIDS_INITIALADMINSKILL))) Then
                    oTech.SkillId = oSkill.PKid
                    Exit For
                End If
            Next oSkill
            Set cSkills = Nothing
            
            If oTech.LocationId And oTech.SkillId Then
                'insert new technician
                g_oSysAdmin.Insert oTech:=oTech
                Set oTech = Nothing
                
                'and try to init again
                bResult = g_oTechAdmin.Init(sUser, icTECH_LOGGED_IN)
            End If
        Else
            Set g_oTechAdmin = Nothing
        End If
    End If
    
    Initialize = bResult
End If

End Function

Public Sub Terminate()
    
    g_oSysAdmin.Term
    Set g_oSysAdmin = Nothing
    
    g_oTechAdmin.Term
    Set g_oTechAdmin = Nothing
    
    Set g_oHDExt = Nothing

End Sub
