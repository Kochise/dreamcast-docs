Attribute VB_Name = "RepEng"
' ------------------------------------------------------------------------
' Copyright (c) 1998 by Microsoft Corporation, All Rights Reserved
'
' This software is provided as is without warranty of any kind.  The entire
' risk as to the results and performance of this software is assumed by the user.
' Microsoft disclaims all warranties, either express or implied, including but
' not limited, the implied warranties of merchantability, fitness for a
' particular purpose, title and noninfringement, with respect to this software.
' ------------------------------------------------------------------------
'$include 'odbcor_g.bi'
'$include 'odbext_g.bi'

' ------------------------------------------------------------------------
' This file contains a bunch of variant declarations for variables that
' represent object identifiers for repository Type Information Model objects.
'   (For more information about Type Information Model objects, see the
'    Repository Programmer's Guide in Visual Basic Books Online.)
' A pile of error number constants for repository specific errors are also defined.
'
' Two subroutines (DEFINE_OBJID and InitRepository) and one function (InitGuid)
' are also contained in this file.
' ------------------------------------------------------------------------
Public CLSID_RepositoryObject As Variant

' Repository Type Infomation Model Object IDs.
Public OBJID_ClassDef As Variant
Public OBJID_InterfaceDef As Variant
Public OBJID_CollectionDef As Variant
Public OBJID_MethodDef As Variant
Public OBJID_PropertyDef As Variant
Public OBJID_RelationshipDef As Variant
Public OBJID_ReposTypeLib As Variant
Public OBJID_ReposRoot As Variant

Public OBJID_IUnknown As Variant
Public OBJID_IDispatch As Variant
Public OBJID_IReposDispatch As Variant
Public OBJID_IReposTypeInfo As Variant
Public OBJID_IClassDef As Variant
Public OBJID_IInterfaceDef As Variant
Public OBJID_IInterfaceMember As Variant
Public OBJID_IPropertyDef As Variant
Public OBJID_ICollectionDef As Variant
Public OBJID_IRepositoryItem As Variant
Public OBJID_IRepositoryObject As Variant
Public OBJID_IRelationship As Variant
Public OBJID_IAnnotationalProps As Variant
Public OBJID_ISummaryInfo As Variant
Public OBJID_INamedObject As Variant
Public OBJID_IManageReposTypeLib As Variant
Public OBJID_IReposTypeLib As Variant
Public OBJID_IReposRoot As Variant

Public OBJID_RClassImplIface As Variant
Public OBJID_RIfaceInheritsFromIface As Variant
Public OBJID_RIfaceHasMembers As Variant
Public OBJID_RColContainsItems As Variant
Public OBJID_RContainerContextForReposTLBs As Variant
Public OBJID_RReposTLBScopeForReposTypeInfo As Variant

Public OBJID_Ifaces As Variant
Public OBJID_Classes As Variant
Public OBJID_Ancestor As Variant
Public OBJID_Descendants As Variant
Public OBJID_Members As Variant
Public OBJID_Iface As Variant
Public OBJID_CollectionItem As Variant
Public OBJID_Collection As Variant
Public OBJID_ReposTypeLibs As Variant
Public OBJID_ReposTLBContexts As Variant
Public OBJID_ReposTypeInfos As Variant
Public OBJID_ReposTypeLibScopes As Variant

Public OBJID_ReposRootObj As Variant
Public OBJID_ReposTIM As Variant

Public OBJID_IRepositoryObjectVersion As Variant
Public OBJID_IRepositoryObjectVersionedObject As Variant
Public OBJID_IVersionCol As Variant
Public OBJID_IVersionedRelship As Variant
Public OBJID_Workspace As Variant
Public OBJID_IWorkspace As Variant
Public OBJID_IWorkspaceItem As Variant
Public OBJID_IVersionAdminInfo As Variant
Public OBJID_VersionCreateTime As Variant
Public OBJID_VersionModifyTime As Variant
Public OBJID_CreateByUser As Variant
Public OBJID_ModifyByUser As Variant
Public OBJID_IWorkspaceContainer  As Variant
Public OBJID_RWksContainerContainsWorkspaces  As Variant
Public OBJID_ContainedWorkspaces  As Variant
Public OBJID_WorkspaceContainers  As Variant
 
Public OBJID_NULL As Variant

Public Const EREP_BADPARAMS = &H80041000
Public Const EREP_BADNAME = &H80041001
Public Const EREP_BADDRIVER = &H80041002
Public Const EREP_BADERROR = &H80041003
Public Const EREP_BUFFER_OVERFLOW = &H80041004
Public Const EREP_NOROWSFOUND = &H80041011
Public Const EREP_ODBC_CERROR = &H80041012
Public Const EREP_ODBC_MDBNOTFOUND = &H80041013
Public Const EREP_NEED_DATA = &H80041014
Public Const EREP_ODBC_UNKNOWNDRIVER = &H80041015
Public Const EREP_ODBC_CREATEFAILED = &H80041016
Public Const EREP_ODBC_WARNINGS = &H41017
Public Const EREP_STILL_EXECUTING = &H80041018
Public Const EREP_ODBC_NOTCAPABLE = &H80041019
Public Const EREP_DB_EXISTS = &H80041030
Public Const EREP_DB_NOTCONNECTED = &H80041031
Public Const EREP_DB_ALREADYCONNECTED = &H80041032
Public Const EREP_DB_DBMSONETHREAD = &H80041033
Public Const EREP_DB_CORRUPT = &H80041034
Public Const EREP_DB_NOSCHEMA = &H80041035
Public Const EREP_DB_DBMSOLD = &H80041036
Public Const EREP_DB_READONLY = &H80041037
Public Const EREP_DB_INCOMPATIBLEVERSION = &H80041038
Public Const EREP_TXN_NOTXNACTIVE = &H80041041
Public Const EREP_TXN_AUTOABORT = &H80041042
Public Const EREP_TXN_TOOMANY = &H80041043
Public Const EREP_TXN_TIMEOUT = &H80041044
Public Const EREP_TXN_NODATA = &H80041045
Public Const EREP_TXN_NOSETINTXN = &H80041046
Public Const EREP_TXN_OBJABORTED = &H80041047
Public Const EREP_TXN_COLABORTED = &H80041048
Public Const EREP_REPOS_CACHEFULL = &H80041070
Public Const EREP_REPOS_NONEXTDISPID = &H80041071
Public Const EREP_RELSHIP_EXISTS = &H80041100
Public Const EREP_RELSHIP_INVALID_PAIR = &H80041101
Public Const EREP_RELSHIP_NOTFOUND = &H80041102
Public Const EREP_RELSHIP_ORGONLY = &H80041105
Public Const EREP_RELSHIP_OUTOFDATE = &H80041106
Public Const EREP_RELSHIP_INVALIDFLAGS = &H80041107
Public Const EREP_RELSHIP_NAMEINVALID = &H80041108
Public Const EREP_RELSHIP_DUPENAME = &H80041109
Public Const EREP_RELSHIP_NONNAMINGCOL = &H80041110
Public Const EREP_TYPE_TABLEMISMATCH = &H80041120
Public Const EREP_TYPE_COLMISMATCH = &H80041121
Public Const EREP_TYPE_NOTNULLABLE = &H80041122
Public Const EREP_TYPE_MULTIDEFIFACES = &H80041123
Public Const EREP_TYPE_INVERTEDNOTALLOWED = &H80041124
Public Const EREP_TYPE_INVALIDSCALE = &H80041125
Public Const EREP_TYPE_BADTABLENAME = &H80041126
Public Const EREP_LOCK_TIMEOUT = &H80041200
Public Const EREP_QRY_BADCOLUMNS = &H80041250
Public Const EREP_OBJ_NOTINITIALIZED = &H80041300
Public Const EREP_OBJ_NOTFOUND = &H80041301
Public Const EREP_OBJ_NONAMINGRELSHIP = &H80041302
Public Const EREP_OBJ_EXISTS = &H80041303
Public Const EREP_VERSION_NOTFOUND = &H80041304
Public Const EREP_PROP_MISMATCH = &H80041400
Public Const EREP_PROP_SETINVALID = &H80041401
Public Const SREP_PROP_TRUNCATION = &H41402
Public Const EREP_PROP_CANTSETREPTIM = &H80041403
Public Const EREP_PROP_READONLY = &H80041404
Public Const EREP_PROP_NOTEXISTS = &H80041405
Public Const EREP_TIM_INVALIDFLAGS = &H80041500
Public Const EREP_TIM_FLAGSDEST = &H80041501
Public Const EREP_TIM_RELTYPEINVALID = &H80041502
Public Const EREP_TIM_CTYPEINVALID = &H80041503
Public Const EREP_TIM_TOOMANYCOLS = &H80041504
Public Const EREP_TIM_SQLTYPEINVALID = &H80041505

'---- V2 Errors
Public Const EREP_VM_CANTSETFROZEN = &H80041600
Public Const EREP_VM_MERGETOFROZEN = &H80041601
Public Const EREP_VM_MERGEFROMUNFROZEN = &H80041602
Public Const EREP_VM_UNFROZENVERSION = &H80041603
Public Const EREP_VM_FROZENVERSION = &H80041604
Public Const EREP_VM_CHECKEDOUTVERSION = &H80041605
Public Const EREP_VM_DUPBRANCHID = &H80041606
Public Const EREP_VM_SUCCESSOREXISTS = &H80041607

Public Const EREP_REL_ORGFROZEN = &H80041700
Public Const EREP_REL_ORGCLONE = &H80041701
Public Const EREP_REL_NONSEQONLY = &H80041702
Public Const EREP_REL_ORGPIN = &H80041703
Public Const EREP_REL_NOTPINNED = &H80041704

Public Const EREP_WKS_ITEMEXISTS = &H80041800
Public Const EREP_WKS_ITEMNOTEXISTS = &H80041801
Public Const EREP_WKS_NOTWORKSPACEITEM = &H80041802
Public Const EREP_WKS_ITEMNOTCHECKEDOUT = &H80041803

Public Const EREP_VCOL_VERSIONNOTMEMBER = &H80041900
Public Const EREP_VCOL_INVALIDOP = &H80041901

Public Const EREP_COL_NOTSEQUENCED = &H80041950

' ------------------------------------------------------------------------
' This function just stuffs the 16 byte values that you pass in into a
' contiguous GUID variant.
' ------------------------------------------------------------------------
Function InitGuid(a As Byte, b As Byte, c As Byte, d As Byte, _
e As Byte, f As Byte, g As Byte, h As Byte, _
i As Byte, j As Byte, k As Byte, l As Byte, _
m As Byte, n As Byte, o As Byte, p As Byte) As Variant

Dim Guid(0 To 15) As Byte

Guid(0) = a
Guid(1) = b
Guid(2) = c
Guid(3) = d
Guid(4) = e
Guid(5) = f
Guid(6) = g
Guid(7) = h
Guid(8) = i
Guid(9) = j
Guid(10) = k
Guid(11) = l
Guid(12) = m
Guid(13) = n
Guid(14) = o
Guid(15) = p

InitGuid = Guid
End Function

' ------------------------------------------------------------------------
' This subroutine sets up an object identifier with the unique value that
' you pass in placed in the correct part of the object identifier.
' ------------------------------------------------------------------------
Sub DEFINE_OBJID(ByRef id As Variant, uniquifier As Long, base() As Long)
    base(4) = uniquifier
    id = base
End Sub

' ------------------------------------------------------------------------
' This subroutine initializes all of the object identifiers for Type Information
' Model definition objects to their correct values.
' ------------------------------------------------------------------------
Sub InitRepository()

Dim ObjID(0 To 4) As Long

CLSID_RepositoryObject = InitGuid(&HFB, &H70, &H22, &H6E, &H99, &HF7, &HCF, &H11, &H92, &H27, 0, &HAA, 0, &HA1, &HEB, &H95)

' Set up the guid portion of the object IDs.
ObjID(0) = &H90591B0C
ObjID(1) = &H11CF24F7
ObjID(2) = &HAA000A92
ObjID(3) = &H95EBA100

Call DEFINE_OBJID(OBJID_ClassDef, 0, ObjID)
Call DEFINE_OBJID(OBJID_InterfaceDef, 1, ObjID)
Call DEFINE_OBJID(OBJID_CollectionDef, 2, ObjID)
Call DEFINE_OBJID(OBJID_MethodDef, 3, ObjID)
Call DEFINE_OBJID(OBJID_PropertyDef, 4, ObjID)
Call DEFINE_OBJID(OBJID_RelationshipDef, 5, ObjID)
Call DEFINE_OBJID(OBJID_ReposTypeLib, 6, ObjID)
Call DEFINE_OBJID(OBJID_ReposRoot, 7, ObjID)

Call DEFINE_OBJID(OBJID_IUnknown, 8, ObjID)
Call DEFINE_OBJID(OBJID_IDispatch, 9, ObjID)
Call DEFINE_OBJID(OBJID_IReposDispatch, 10, ObjID)
Call DEFINE_OBJID(OBJID_IReposTypeInfo, 11, ObjID)
Call DEFINE_OBJID(OBJID_IClassDef, 12, ObjID)
Call DEFINE_OBJID(OBJID_IInterfaceDef, 13, ObjID)
Call DEFINE_OBJID(OBJID_IInterfaceMember, 14, ObjID)
Call DEFINE_OBJID(OBJID_IPropertyDef, 15, ObjID)
Call DEFINE_OBJID(OBJID_ICollectionDef, 16, ObjID)
Call DEFINE_OBJID(OBJID_IRepositoryItem, 17, ObjID)
Call DEFINE_OBJID(OBJID_IRepositoryObject, 18, ObjID)
Call DEFINE_OBJID(OBJID_IRelationship, 19, ObjID)
Call DEFINE_OBJID(OBJID_IAnnotationalProps, 20, ObjID)
Call DEFINE_OBJID(OBJID_ISummaryInfo, 21, ObjID)
Call DEFINE_OBJID(OBJID_INamedObject, 22, ObjID)
Call DEFINE_OBJID(OBJID_IManageReposTypeLib, 23, ObjID)
Call DEFINE_OBJID(OBJID_IReposTypeLib, 24, ObjID)
Call DEFINE_OBJID(OBJID_IReposRoot, 25, ObjID)

Call DEFINE_OBJID(OBJID_RClassImplIface, 26, ObjID)
Call DEFINE_OBJID(OBJID_RIfaceInheritsFromIface, 27, ObjID)
Call DEFINE_OBJID(OBJID_RIfaceHasMembers, 28, ObjID)
Call DEFINE_OBJID(OBJID_RColContainsItems, 29, ObjID)
Call DEFINE_OBJID(OBJID_RContainerContextForReposTLBs, 30, ObjID)
Call DEFINE_OBJID(OBJID_RReposTLBScopeForReposTypeInfo, 31, ObjID)

Call DEFINE_OBJID(OBJID_Ifaces, 32, ObjID)
Call DEFINE_OBJID(OBJID_Classes, 33, ObjID)
Call DEFINE_OBJID(OBJID_Ancestor, 34, ObjID)
Call DEFINE_OBJID(OBJID_Descendants, 35, ObjID)
Call DEFINE_OBJID(OBJID_Members, 36, ObjID)
Call DEFINE_OBJID(OBJID_Iface, 37, ObjID)
Call DEFINE_OBJID(OBJID_CollectionItem, 38, ObjID)
Call DEFINE_OBJID(OBJID_Collection, 39, ObjID)
Call DEFINE_OBJID(OBJID_ReposTypeLibs, 40, ObjID)
Call DEFINE_OBJID(OBJID_ReposTLBContexts, 41, ObjID)
Call DEFINE_OBJID(OBJID_ReposTypeInfos, 42, ObjID)
Call DEFINE_OBJID(OBJID_ReposTypeLibScopes, 43, ObjID)

Call DEFINE_OBJID(OBJID_ReposRootObj, 44, ObjID)
Call DEFINE_OBJID(OBJID_ReposTIM, 45, ObjID)

Call DEFINE_OBJID(OBJID_IRepositoryObjectVersion, 71, ObjID)
Call DEFINE_OBJID(OBJID_IVersionCol, 72, ObjID)
Call DEFINE_OBJID(OBJID_IVersionedRelship, 73, ObjID)
Call DEFINE_OBJID(OBJID_Workspace, 74, ObjID)
Call DEFINE_OBJID(OBJID_IWorkspace, 75, ObjID)
Call DEFINE_OBJID(OBJID_IWorkspaceItem, 76, ObjID)
Call DEFINE_OBJID(OBJID_IVersionAdminInfo, 77, ObjID)
Call DEFINE_OBJID(OBJID_VersionCreateTime, 78, ObjID)
Call DEFINE_OBJID(OBJID_VersionModifyTime, 79, ObjID)
Call DEFINE_OBJID(OBJID_CreateByUser, 80, ObjID)
Call DEFINE_OBJID(OBJID_ModifyByUser, 81, ObjID)
Call DEFINE_OBJID(OBJID_IWorkspaceContainer, 82, ObjID)
Call DEFINE_OBJID(OBJID_RWksContainerContainsWorkspaces, 83, ObjID)
Call DEFINE_OBJID(OBJID_ContainedWorkspaces, 84, ObjID)
Call DEFINE_OBJID(OBJID_WorkspaceContainers, 85, ObjID)

Call DEFINE_OBJID(OBJID_NULL, &HFFFFFFFF, ObjID)
Call DEFINE_OBJID(EXTVERSIONID_NULL, &HFFFFFFFF, ObjID)
End Sub

