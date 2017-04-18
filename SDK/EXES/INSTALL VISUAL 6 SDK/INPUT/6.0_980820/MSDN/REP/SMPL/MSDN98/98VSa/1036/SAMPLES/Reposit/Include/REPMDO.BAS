Attribute VB_Name = "Mdo"
' ------------------------------------------------------------------------
'               Copyright (C) 1998 Microsoft Corporation
'
' You have a royalty-free right to use, modify, reproduce and distribute
' the Sample Application Files (and/or any modified version) in any way
' you find useful, provided that you agree that Microsoft has no warranty,
' obligations or liability for any Sample Application Files.
' ------------------------------------------------------------------------
Option Explicit

'
' Definitions for MPO
'

 '// MPO relationships
 Public OBJID_Contents As Variant
 Public OBJID_Containers As Variant

 '// MPO Interfaces
 Public OBJID_IMpoProjectItemContainer As Variant
 Public OBJID_IMpoProjectItem As Variant

'
' Definitions for MDO
'

'// class definitions for Mdo TIM repository schema
 Public OBJID_MdoProject As Variant
 Public OBJID_MdoControl As Variant
 Public OBJID_MdoRelatedDocument As Variant
 Public OBJID_MdoVBForm As Variant
 Public OBJID_MdoMDIForm As Variant
 Public OBJID_MdoStdModule As Variant
 Public OBJID_MdoClassModule As Variant
 Public OBJID_MdoPropertyPage As Variant
 Public OBJID_MdoDesigner As Variant
 Public OBJID_MdoResourceFile As Variant
 Public OBJID_MdoMSForm As Variant
 Public OBJID_MdoUserControl As Variant
 Public OBJID_MdoUserDocument As Variant
 Public OBJID_MdoTypeLibRef As Variant
 Public OBJID_MdoProjectRef As Variant
 Public OBJID_MdoISVControl As Variant
    
'// instance ids
Public OBJID_mdoModel As Variant

    
'// main repository interfaces
Public OBJID_IMdoModelItem As Variant
Public OBJID_IMdoGroupProject As Variant
Public OBJID_IMdoProject As Variant
Public OBJID_IMdoReference As Variant
Public OBJID_IMdoComponent As Variant
Public OBJID_IMdoControlContainer As Variant
Public OBJID_IMdoControl As Variant
Public OBJID_IMdoISVControl As Variant
Public OBJID_IMdoControlUsage As Variant


'// repository relationships
Public OBJID_mdoComponents As Variant
Public OBJID_mdoComponentProjects As Variant

Public OBJID_mdoReferences As Variant
Public OBJID_mdoReferenceProjects As Variant

Public OBJID_mdoControls As Variant
Public OBJID_mdoControlContainers As Variant

Public OBJID_mdoISVControls As Variant
Public OBJID_mdoControlUsage As Variant


' property definitions
Public OBJID_PropDescription As Variant
Public OBJID_PropFilename As Variant
Public OBJID_PropTimestamp As Variant
Public OBJID_PropProjectName As Variant
Public OBJID_PropIndex As Variant
Public OBJID_PropClassName As Variant
Public OBJID_PropProgID As Variant
Public OBJID_PropCtlDescription As Variant

Private Sub DEFINE_OBJID(ByRef id As Variant, uniquifier As Long, base() As Long)
    base(4) = uniquifier
    id = base
End Sub

Sub InitMdo()
        Dim GUID_MPO(0 To 4) As Long
        '#define GUID_MPO       { 0xb037cb3, 0x170e, 0x11d0, 0x90, 0xac, 0x0, 0xa0, 0xc9, 0x13, 0xf7, 0xc7 }
        GUID_MPO(0) = &HB037CB3
        GUID_MPO(1) = &H11D0170E
        GUID_MPO(2) = &HA000AC90
        GUID_MPO(3) = &HC7F713C9

        '// mpo definitions
        Call DEFINE_OBJID(OBJID_Contents, 72, GUID_MPO)
        Call DEFINE_OBJID(OBJID_Containers, 73, GUID_MPO)
        Call DEFINE_OBJID(OBJID_IMpoProjectItemContainer, 74, GUID_MPO)
        Call DEFINE_OBJID(OBJID_IMpoProjectItem, 75, GUID_MPO)
    
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
    Call DEFINE_OBJID(OBJID_MdoDesigner, 12, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_MdoResourceFile, 13, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_MdoMSForm, 14, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_MdoUserControl, 15, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_MdoUserDocument, 16, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_MdoTypeLibRef, 17, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_MdoProjectRef, 18, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_MdoISVControl, 19, GUID_VBTIM)

    '// instance ids
    'Call DEFINE_OBJID(OBJID_mdoModel, 99, GUID_VBTIM)
    
    '// main repository interfaces
    Call DEFINE_OBJID(OBJID_IMdoModelItem, 20, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_IMdoGroupProject, 21, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_IMdoProject, 23, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_IMdoReference, 24, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_IMdoComponent, 25, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_IMdoControlContainer, 26, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_IMdoControl, 27, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_IMdoISVControl, 28, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_IMdoControlUsage, 29, GUID_VBTIM)
    
    '// repository relationships
    Call DEFINE_OBJID(OBJID_mdoComponents, 34, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_mdoComponentProjects, 35, GUID_VBTIM)
    
    Call DEFINE_OBJID(OBJID_mdoReferences, 36, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_mdoReferenceProjects, 37, GUID_VBTIM)
    
    Call DEFINE_OBJID(OBJID_mdoControls, 38, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_mdoControlContainers, 39, GUID_VBTIM)
    
    Call DEFINE_OBJID(OBJID_mdoISVControls, 40, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_mdoControlUsage, 41, GUID_VBTIM)


    '// dispatch ids for collections in repository
    Const DISPID_Components = 52
    Const DISPID_ComponentProject = 53

    Const DISPID_References = 54
    Const DISPID_ReferenceProject = 55

    Const DISPID_Controls = 56
    Const DISPID_ControlContainer = 57

    Const DISPID_ISVControls = 58
    Const DISPID_ISVUsage = 59

    '// property ids for properties in repository
    Const DISPID_PropDescription = 102
    Const DISPID_PropFileName = 103
    Const DISPID_PropTimestamp = 104
    Const DISPID_PropProjectName = 105
    Const DISPID_PropIndex = 111
    Const DISPID_PropClassName = 112
    Const DISPID_PropProgId = 113
    Const DISPID_PropCtlDescription = 114
    
    Call DEFINE_OBJID(OBJID_PropDescription, DISPID_PropDescription, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_PropFilename, DISPID_PropFileName, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_PropTimestamp, DISPID_PropTimestamp, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_PropProjectName, DISPID_PropProjectName, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_PropIndex, DISPID_PropIndex, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_PropClassName, DISPID_PropClassName, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_PropProgID, DISPID_PropProgId, GUID_VBTIM)
    Call DEFINE_OBJID(OBJID_PropCtlDescription, DISPID_PropCtlDescription, GUID_VBTIM)

End Sub
