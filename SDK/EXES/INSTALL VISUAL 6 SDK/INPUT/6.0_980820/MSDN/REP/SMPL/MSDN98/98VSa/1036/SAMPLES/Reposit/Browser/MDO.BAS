' ------------------------------------------------------------------------
'               Copyright (C) 1996 Microsoft Corporation
'
' You have a royalty-free right to use, modify, reproduce and distribute
' the Sample Application Files (and/or any modified version) in any way
' you find useful, provided that you agree that Microsoft has no warranty,
' obligations or liability for any Sample Application Files.
' ------------------------------------------------------------------------
Attribute VB_Name = "Mdo"
Attribute VB_Ext_KEY = "RepId" ,"55738E3C-B4C0-11CF-9122-00A0C905416D-0281"

Option Explicit

'
' Definitions for MDO
'

'New class definitions
 Public OBJID_ReposRoot As Variant
 
'// class definitions for Mdo TIM repository schema
 Public OBJID_MdoProject As Variant
 Public OBJID_MdoControl As Variant
 Public OBJID_MdoRelatedDocument As Variant
 Public OBJID_MdoVBForm As Variant
 Public OBJID_MdoMDIForm As Variant
 Public OBJID_MdoStdModule As Variant
 Public OBJID_MdoClassModule As Variant
 Public OBJID_MdoPropertyPage As Variant
 Public OBJID_MdoCustomBaseClass As Variant
 Public OBJID_MdoResourceFile As Variant
 Public OBJID_MdoMSForm As Variant
 Public OBJID_MdoUserControl As Variant
 Public OBJID_MdoDocObject As Variant
 Public OBJID_MdoTypeLib As Variant
 Public OBJID_MdoProjRef As Variant
    
'// instance ids
Public OBJID_mdoModel As Variant

'// New interfaces
Public OBJID_IMpoProjectItemContainer As Variant
Public OBJID_IMpoProjectItem As Variant

'// main repository interfaces
Public OBJID_IMdoModelItem As Variant
Public OBJID_IMdoGroupProject As Variant
'//Public OBJID_IMdoModel As Variant : deleted
Public OBJID_IMdoProject As Variant
Public OBJID_IMdoReference As Variant
Public OBJID_IMdoComponent As Variant
Public OBJID_IMdoControlContainer As Variant
Public OBJID_IMdoControl As Variant

'// New relships
Public OBJID_ProjectItemContainerContainsProjectItems As Variant

'// repository relationships
Public OBJID_mdoProjects As Variant
Public OBJID_mdoRoots As Variant

Public OBJID_mdoComponents As Variant
Public OBJID_mdoComponentProjects As Variant

Public OBJID_mdoReferences As Variant
Public OBJID_mdoReferenceProjects As Variant

Public OBJID_mdoControls As Variant
Public OBJID_mdoControlContainers As Variant


' property definitions
Public OBJID_PropName As Variant
Public OBJID_PropDescription As Variant
Public OBJID_PropFilename As Variant
Public OBJID_PropTimestamp As Variant
Public OBJID_PropIndex As Variant
Public OBJID_PropClassName As Variant
Public OBJID_PropProgID As Variant
Public OBJID_PropCtlDescription As Variant

Private Sub DEFINE_OBJID(ByRef id As Variant, uniquifier As Long, base() As Long)
    base(4) = uniquifier
    id = base
End Sub
Sub InitMdo()
    Dim GUID_VBTIM(0 To 4) As Long
    '#define GUID_VBTIM      { 0xa541d2e2, 0x6c7d, 0x11cf, 0xa7, 0x42, 0x0, 0xa0, 0xd1, 0x0, 0x2, 0xa3 }
    GUID_VBTIM(0) = &HA541D2E2
    GUID_VBTIM(1) = &H11CF6C7D
    GUID_VBTIM(2) = &HA00042A7
    GUID_VBTIM(3) = &HA30200D1
    
    '// main class definitions for VBTIM repository schema
    Call DEFINE_OBJID(OBJID_MdoProject, 1, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_MdoControl, 3, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_MdoRelatedDocument, 4, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_MdoVBForm, 5, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_MdoMDIForm, 7, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_MdoStdModule, 8, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_MdoClassModule, 9, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_MdoPropertyPage, 11, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_MdoCustomBaseClass, 12, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_MdoResourceFile, 13, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_MdoMSForm, 14, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_MdoUserControl, 15, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_MdoDocObject, 16, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_MdoTypeLib, 17, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_MdoProjRef, 18, GUID_VBTIM)

    '// New classes
    Call DEFINE_OBJID(OBJID_ReposRoot, 1019, GUID_VBTIM)
    
    '// instance ids
    Call DEFINE_OBJID(OBJID_mdoModel, 99, GUID_VBTIM)
    
    '// main repository interfaces
    Call DEFINE_OBJID(OBJID_IMdoModelItem, 20, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_IMdoGroupProject, 21, GUID_VBTIM)
 '//   Call DEFINE_OBJID(OBJID_IMdoModel, 22, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_IMdoProject, 23, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_IMdoReference, 24, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_IMdoComponent, 25, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_IMdoControlContainer, 26, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_IMdoControl, 27, GUID_VBTIM)
    '//New interfaces
    Call DEFINE_OBJID(OBJID_IMpoProjectItemContainer, 1028, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_IMpoProjectItem, 1029, GUID_VBTIM)
   
    '// repository relationships
    Call DEFINE_OBJID(OBJID_mdoProjects, 32, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_mdoRoots, 33, GUID_VBTIM)
    
    Call DEFINE_OBJID(OBJID_mdoComponents, 34, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_mdoComponentProjects, 35, GUID_VBTIM)
    
    Call DEFINE_OBJID(OBJID_mdoReferences, 36, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_mdoReferenceProjects, 37, GUID_VBTIM)
    
    Call DEFINE_OBJID(OBJID_mdoControls, 38, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_mdoControlContainers, 39, GUID_VBTIM)
    '// New relship
    Call DEFINE_OBJID(OBJID_ProjectItemContainerContainsProjectItems, 1040, GUID_VBTIM)
    
    '// property ids for properties in repository
    Const DISPID_ROOTPROJS = 53
    Const DISPID_PROJCOMPS = 54
    Const DISPID_PROJREFS = 55
    Const DISPID_CONTROLS = 56
    
    Const DISPID_NAME = 101
    Const DISPID_DESCRIPTION = 102
    Const DISPID_FILENAME = 103
    Const DISPID_TIMESTAMP = 104
    Const DISPID_INDEX = 111
    Const DISPID_CLASSNAME = 112
    Const DISPID_PROGID = 113
    Const DISPID_CTLDESCRIPTION = 114
    
    Call DEFINE_OBJID(OBJID_PropName, DISPID_NAME, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_PropDescription, DISPID_DESCRIPTION, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_PropFilename, DISPID_FILENAME, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_PropTimestamp, DISPID_TIMESTAMP, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_PropIndex, DISPID_INDEX, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_PropClassName, DISPID_CLASSNAME, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_PropProgID, DISPID_PROGID, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_PropCtlDescription, DISPID_CTLDESCRIPTION, GUID_VBTIM)

End Sub

Public Function MatchObjid(x As Variant, a As Variant, _
    Optional b As Variant, Optional c As Variant, Optional d As Variant, _
    Optional e As Variant, Optional f As Variant, Optional g As Variant) As Integer

    Dim i As Integer
    Dim match As Integer
    
    match = True
    MatchObjid = True ' assume a match, and correct at the end
    
    If MatchOneObjid(x, a) Then Exit Function
    
    If Not IsMissing(b) Then If MatchOneObjid(x, b) Then Exit Function
    If Not IsMissing(c) Then If MatchOneObjid(x, c) Then Exit Function
    If Not IsMissing(d) Then If MatchOneObjid(x, d) Then Exit Function
    If Not IsMissing(e) Then If MatchOneObjid(x, e) Then Exit Function
    If Not IsMissing(f) Then If MatchOneObjid(x, f) Then Exit Function
    If Not IsMissing(g) Then If MatchOneObjid(x, g) Then Exit Function
    
    
    ' didn't get a match
    MatchObjid = False
    Exit Function
End Function


Private Function MatchOneObjid(a As Variant, b As Variant) As Integer
    Dim i As Integer
    For i = LBound(a) To UBound(a)
        If a(i) <> b(i) Then
            MatchOneObjid = False
            Exit Function
        End If
    Next
    MatchOneObjid = True
End Function

Public Function ObjidToString(ObjId As Variant) As String
    Dim rslt As String
    Dim i As Integer
    For i = LBound(ObjId) To UBound(ObjId)
        rslt = rslt & Str$(ObjId(i)) & " "
    Next
    ObjidToString = rslt
End Function

Public Function StringToObjid(ByVal ObjId As String) As Variant
    Dim rslt As Variant
    Dim i As Integer
    Dim l As Long
    Dim ix As Integer
    Dim ls As String
    
    For i = 0 To 4
        LTrim$ (ObjId)
        ix = InStr(ObjId, " ")
        ls = Left$(ObjId, ix)
    Next i
End Function
