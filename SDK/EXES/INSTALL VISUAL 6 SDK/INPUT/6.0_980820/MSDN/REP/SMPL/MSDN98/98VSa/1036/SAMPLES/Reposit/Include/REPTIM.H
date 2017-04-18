// ------------------------------------------------------------------------
// Copyright (c) 1998 by Microsoft Corporation, All Rights Reserved
// 
// This software is provided as is without warranty of any kind.  The entire
// risk as to the results and performance of this software is assumed by the user.
// Microsoft disclaims all warranties, either express or implied, including but
// not limited, the implied warranties of merchantability, fitness for a
// particular purpose, title and noninfringement, with respect to this software.
// ------------------------------------------------------------------------
//*****************************************************************************
// REPTIM.H
//
// This module contains the declarations of the meta-meta model components.
// These can be used to browse the meta-meta model by ID, or might be required
// to create your own meta model in the Repository.
//
// Copyright (c) 1995-1998 by Microsoft Corporation, All Rights Reserved
//*****************************************************************************
#ifndef __REPTIM_H__
#define __REPTIM_H__

// The hard coded site IDs.
#define SITEID_METAMETA		0
#define SITEID_LOCAL		1

// Local ID definitions.
#define LCLID_FirstClassDefID		0
#define LCLID_ClassDef				0
#define LCLID_IfaceDef				1
#define LCLID_CollectionDef			2
#define LCLID_MethodDef				3
#define LCLID_PropDef				4
#define LCLID_RelshipDef			5
#define LCLID_ReposTypeLib			6
#define LCLID_ReposRoot				7
#define LCLID_LastClassDefID		7

#define LCLID_FirstIfaceDefID		8
#define LCLID_IUnknown				8
#define LCLID_IDispatch				9
#define LCLID_IReposDispatch		10
#define LCLID_IReposTypeInfo		11
#define LCLID_IClassDef				12
#define LCLID_IIfaceDef				13
#define LCLID_IIfaceMember			14
#define LCLID_IPropDef				15
#define LCLID_ICollectionDef		16
#define LCLID_IReposItem			17
#define LCLID_IReposObj				18
#define LCLID_IRelship				19
#define LCLID_IAnnotationalProps	20
#define LCLID_ISummaryInfo			21
#define LCLID_INamedObj				22
#define LCLID_IManageReposTypeLib	23
#define LCLID_IReposTypeLib			24
#define LCLID_IReposRoot			25
#define LCLID_LastIfaceDefID		25

#define LCLID_FirstRelshipDef					26
#define LCLID_RClassImplIface					26
#define LCLID_RIfaceInheritsFromIface			27
#define LCLID_RIfaceHasMembers					28
#define LCLID_RColContainsItems					29
#define LCLID_RContainerContextForReposTLBs		30
#define LCLID_RReposTLBScopeForReposTypeInfo	31
#define LCLID_LastRelshipDef					31

//Must define the roles in origin role followed immediately by destination role for each relationshipdef.
#define LCLID_FirstRoleDefID		32
#define LCLID_Ifaces				32
#define LCLID_Classes				33
#define LCLID_Ancestor				34
#define LCLID_Descendants			35
#define LCLID_Members				36
#define LCLID_Iface					37
#define LCLID_CollectionItem		38
#define LCLID_ItemInCollections		39
#define LCLID_ReposTypeLibs			40
#define LCLID_ReposTLBContexts		41
#define LCLID_ReposTypeInfos		42
#define LCLID_ReposTypeLibScopes	43
#define LCLID_LastRoleDefID			43

#define LCLID_ReposRootObj			44
#define LCLID_ReposTIM				45

#define LCLID_ClassID				46
#define LCLID_PropDescs				47
#define LCLID_InterfaceID			48
#define LCLID_TableName				49
#define LCLID_IfaceFlags			50
#define LCLID_DispID				51
#define LCLID_IfaceMemFlags			52
#define LCLID_RelshipTypeID			53
#define LCLID_ColFlags				54
#define LCLID_MinCount				55
#define LCLID_MaxCount				56
#define LCLID_IsOrigin				57
#define LCLID_ColumnName			58
#define LCLID_APIType				59
#define LCLID_SQLType				60
#define LCLID_SQLSize				61
#define LCLID_SQLScale				62
#define LCLID_PropFlags				63
#define LCLID_TypeLibID				64
#define LCLID_TypeID				65
#define LCLID_Comments				66
#define LCLID_ShortDesc				67
#define LCLID_ObjName				68

#define LCLID_RelshipTgtName		69

#define LCLID_ImplementsOptions		70

#define LCLID_NULL					0xffffffff

// Internal ID definitions.
const INTID INTID_ClassDef			=	{SITEID_METAMETA, LCLID_ClassDef};
const INTID INTID_IfaceDef			=	{SITEID_METAMETA, LCLID_IfaceDef};
const INTID INTID_CollectionDef		=	{SITEID_METAMETA, LCLID_CollectionDef};
const INTID INTID_MethodDef			=	{SITEID_METAMETA, LCLID_MethodDef};
const INTID INTID_PropDef			=	{SITEID_METAMETA, LCLID_PropDef};
const INTID INTID_RelshipDef		=	{SITEID_METAMETA, LCLID_RelshipDef};
const INTID INTID_ReposTypeLib		=	{SITEID_METAMETA, LCLID_ReposTypeLib};
const INTID INTID_ReposRoot			=	{SITEID_METAMETA, LCLID_ReposRoot};

const INTID INTID_IUnknown			=	{SITEID_METAMETA, LCLID_IUnknown};
const INTID INTID_IDispatch			=	{SITEID_METAMETA, LCLID_IDispatch};
const INTID INTID_IReposDispatch	=	{SITEID_METAMETA, LCLID_IReposDispatch};
const INTID INTID_IReposTypeInfo	=	{SITEID_METAMETA, LCLID_IReposTypeInfo};
const INTID INTID_IClassDef			=	{SITEID_METAMETA, LCLID_IClassDef};
const INTID INTID_IIfaceDef			=	{SITEID_METAMETA, LCLID_IIfaceDef};
const INTID INTID_IIfaceMember		=	{SITEID_METAMETA, LCLID_IIfaceMember};
const INTID INTID_IPropDef			=	{SITEID_METAMETA, LCLID_IPropDef};
const INTID INTID_ICollectionDef	=	{SITEID_METAMETA, LCLID_ICollectionDef};
const INTID INTID_IReposItem		=	{SITEID_METAMETA, LCLID_IReposItem};
const INTID INTID_IReposObj			=	{SITEID_METAMETA, LCLID_IReposObj};
const INTID INTID_IRelship			=	{SITEID_METAMETA, LCLID_IRelship};
const INTID INTID_IAnnotationalProps=	{SITEID_METAMETA, LCLID_IAnnotationalProps};
const INTID INTID_ISummaryInfo		=	{SITEID_METAMETA, LCLID_ISummaryInfo};
const INTID INTID_INamedObj			=	{SITEID_METAMETA, LCLID_INamedObj};
const INTID INTID_IManageReposTypeLib=	{SITEID_METAMETA, LCLID_IManageReposTypeLib};
const INTID INTID_IReposTypeLib		=	{SITEID_METAMETA, LCLID_IReposTypeLib};
const INTID INTID_IReposRoot		=	{SITEID_METAMETA, LCLID_IReposRoot};

const INTID INTID_RClassImplIface				=	{SITEID_METAMETA, LCLID_RClassImplIface};
const INTID INTID_RIfaceInheritsFromIface		=	{SITEID_METAMETA, LCLID_RIfaceInheritsFromIface};
const INTID INTID_RIfaceHasMembers				=	{SITEID_METAMETA, LCLID_RIfaceHasMembers};
const INTID INTID_RColContainsItems				=	{SITEID_METAMETA, LCLID_RColContainsItems};
const INTID INTID_RContainerContextForReposTLBs	=	{SITEID_METAMETA, LCLID_RContainerContextForReposTLBs};
const INTID INTID_RReposTLBScopeForReposTypeInfo=	{SITEID_METAMETA, LCLID_RReposTLBScopeForReposTypeInfo};

const INTID INTID_Ifaces			=	{SITEID_METAMETA, LCLID_Ifaces};
const INTID INTID_Classes			=	{SITEID_METAMETA, LCLID_Classes};
const INTID INTID_Ancestor			=	{SITEID_METAMETA, LCLID_Ancestor};
const INTID INTID_Descendants		=	{SITEID_METAMETA, LCLID_Descendants};
const INTID INTID_Members			=	{SITEID_METAMETA, LCLID_Members};
const INTID INTID_Iface				=	{SITEID_METAMETA, LCLID_Iface};
const INTID INTID_CollectionItem	=	{SITEID_METAMETA, LCLID_CollectionItem};
const INTID INTID_ItemInCollections	=	{SITEID_METAMETA, LCLID_ItemInCollections};
const INTID INTID_ReposTypeLibs		=	{SITEID_METAMETA, LCLID_ReposTypeLibs};
const INTID INTID_ReposTLBContexts	=	{SITEID_METAMETA, LCLID_ReposTLBContexts};
const INTID INTID_ReposTypeInfos	=	{SITEID_METAMETA, LCLID_ReposTypeInfos};
const INTID INTID_ReposTypeLibScopes=	{SITEID_METAMETA, LCLID_ReposTypeLibScopes};

const INTID INTID_ReposRootObj		=	{SITEID_METAMETA, LCLID_ReposRootObj};
const INTID INTID_ReposTIM			=	{SITEID_METAMETA, LCLID_ReposTIM};

const INTID INTID_ClassID			=	{SITEID_METAMETA, LCLID_ClassID};
const INTID INTID_PropDescs			=	{SITEID_METAMETA, LCLID_PropDescs};
const INTID INTID_InterfaceID		=	{SITEID_METAMETA, LCLID_InterfaceID};
const INTID INTID_TableName			=	{SITEID_METAMETA, LCLID_TableName};
const INTID INTID_IfaceFlags		=	{SITEID_METAMETA, LCLID_IfaceFlags};
const INTID INTID_DispID			=	{SITEID_METAMETA, LCLID_DispID};
const INTID INTID_IfaceMemFlags		=	{SITEID_METAMETA, LCLID_IfaceMemFlags};
const INTID INTID_RelshipTypeID		=	{SITEID_METAMETA, LCLID_RelshipTypeID};
const INTID INTID_ColFlags			=	{SITEID_METAMETA, LCLID_ColFlags};
const INTID INTID_MinCount			=	{SITEID_METAMETA, LCLID_MinCount};
const INTID INTID_MaxCount			=	{SITEID_METAMETA, LCLID_MaxCount};
const INTID INTID_IsOrigin			=	{SITEID_METAMETA, LCLID_IsOrigin};
const INTID INTID_ColumnName		=	{SITEID_METAMETA, LCLID_ColumnName};
const INTID INTID_APIType			=	{SITEID_METAMETA, LCLID_APIType};
const INTID INTID_SQLType			=	{SITEID_METAMETA, LCLID_SQLType};
const INTID INTID_SQLSize			=	{SITEID_METAMETA, LCLID_SQLSize};
const INTID INTID_SQLScale			=	{SITEID_METAMETA, LCLID_SQLScale};
const INTID INTID_PropFlags			=	{SITEID_METAMETA, LCLID_PropFlags};
const INTID INTID_TypeLibID			=	{SITEID_METAMETA, LCLID_TypeLibID};
const INTID INTID_TypeID			=	{SITEID_METAMETA, LCLID_TypeID};
const INTID INTID_Comments			=	{SITEID_METAMETA, LCLID_Comments};
const INTID INTID_ShortDesc			=	{SITEID_METAMETA, LCLID_ShortDesc};
const INTID INTID_ObjName			=	{SITEID_METAMETA, LCLID_ObjName};

const INTID INTID_RelshipTgtName	=	{SITEID_METAMETA, LCLID_RelshipTgtName};

const INTID INTID_ImplementsOptions	=	{SITEID_METAMETA, LCLID_ImplementsOptions};

const INTID INTID_NULL				=	{SITEID_METAMETA, LCLID_NULL};


// Dispatch IDs
#define DISPID_Ifaces				LCLID_Ifaces
#define DISPID_Classes				LCLID_Classes
#define DISPID_Ancestor				LCLID_Ancestor
#define DISPID_Descendants			LCLID_Descendants
#define DISPID_Members				LCLID_Members
#define DISPID_Iface				LCLID_Iface
#define DISPID_CollectionItem		LCLID_CollectionItem
#define DISPID_ItemInCollections	LCLID_ItemInCollections
#define DISPID_ReposTypeLibs		LCLID_ReposTypeLibs
#define DISPID_ReposTLBContexts		LCLID_ReposTLBContexts
#define DISPID_ReposTypeInfos		LCLID_ReposTypeInfos
#define DISPID_ReposTypeLibScopes	LCLID_ReposTypeLibScopes

#define DISPID_ClassID				DISPID_VALUE
#define DISPID_PropDescs			LCLID_PropDescs
#define DISPID_InterfaceID			DISPID_VALUE
#define DISPID_TableName			LCLID_TableName
#define DISPID_IfaceFlags			LCLID_IfaceFlags
#define DISPID_DispID				LCLID_DispID
#define DISPID_IfaceMemFlags		LCLID_IfaceMemFlags
#define DISPID_RelshipTypeID		LCLID_RelshipTypeID
#define DISPID_ColFlags				LCLID_ColFlags
#define DISPID_MinCount				LCLID_MinCount
#define DISPID_MaxCount				LCLID_MaxCount
#define DISPID_IsOrigin				LCLID_IsOrigin
#define DISPID_ColumnName			LCLID_ColumnName
#define DISPID_APIType				LCLID_APIType
#define DISPID_SQLType				LCLID_SQLType
#define DISPID_SQLSize				LCLID_SQLSize
#define DISPID_SQLScale				LCLID_SQLScale
#define DISPID_PropFlags			LCLID_PropFlags
#define DISPID_TypeLibID			LCLID_TypeLibID
#define DISPID_TypeID				LCLID_TypeID
#define DISPID_Comments				LCLID_Comments
#define DISPID_ShortDesc			LCLID_ShortDesc
#define DISPID_ObjName				LCLID_ObjName

#define DISPID_RelshipTgtName		LCLID_RelshipTgtName
#define DISPID_ImplementsOptions	LCLID_ImplementsOptions


// {90591B0C-24F7-11cf-920A-00AA00A1EB95}
DEFINE_GUID(MetaMetaGuid, 
0x90591b0c, 0x24f7, 0x11cf, 0x92, 0xa, 0x0, 0xaa, 0x0, 0xa1, 0xeb, 0x95);

#define METAMETA_GUID { 0x90591b0c, 0x24f7, 0x11cf, 0x92, 0xa, 0x0, 0xaa, 0x0, 0xa1, 0xeb, 0x95 }

// Object ID definitions.
DEFINE_OBJID(OBJID_ClassDef, LCLID_ClassDef, METAMETA_GUID);
DEFINE_OBJID(OBJID_InterfaceDef, LCLID_IfaceDef, METAMETA_GUID);
DEFINE_OBJID(OBJID_CollectionDef, LCLID_CollectionDef, METAMETA_GUID);
DEFINE_OBJID(OBJID_MethodDef, LCLID_MethodDef, METAMETA_GUID);
DEFINE_OBJID(OBJID_PropertyDef, LCLID_PropDef, METAMETA_GUID);
DEFINE_OBJID(OBJID_RelationshipDef, LCLID_RelshipDef, METAMETA_GUID);
DEFINE_OBJID(OBJID_ReposTypeLib, LCLID_ReposTypeLib, METAMETA_GUID);
DEFINE_OBJID(OBJID_ReposRoot, LCLID_ReposRoot, METAMETA_GUID);

DEFINE_OBJID(OBJID_IUnknown, LCLID_IUnknown, METAMETA_GUID);
DEFINE_OBJID(OBJID_IDispatch, LCLID_IDispatch, METAMETA_GUID);
DEFINE_OBJID(OBJID_IReposDispatch, LCLID_IReposDispatch, METAMETA_GUID);
DEFINE_OBJID(OBJID_IReposTypeInfo, LCLID_IReposTypeInfo, METAMETA_GUID);
DEFINE_OBJID(OBJID_IClassDef, LCLID_IClassDef, METAMETA_GUID);
DEFINE_OBJID(OBJID_IInterfaceDef, LCLID_IIfaceDef, METAMETA_GUID);
DEFINE_OBJID(OBJID_IInterfaceMember, LCLID_IIfaceMember, METAMETA_GUID);
DEFINE_OBJID(OBJID_IPropertyDef, LCLID_IPropDef, METAMETA_GUID);
DEFINE_OBJID(OBJID_ICollectionDef, LCLID_ICollectionDef, METAMETA_GUID);
DEFINE_OBJID(OBJID_IRepositoryItem, LCLID_IReposItem, METAMETA_GUID);
DEFINE_OBJID(OBJID_IRepositoryObject, LCLID_IReposObj, METAMETA_GUID);
DEFINE_OBJID(OBJID_IRelationship, LCLID_IRelship, METAMETA_GUID);
DEFINE_OBJID(OBJID_IAnnotationalProps, LCLID_IAnnotationalProps, METAMETA_GUID);
DEFINE_OBJID(OBJID_ISummaryInfo, LCLID_ISummaryInfo, METAMETA_GUID);
DEFINE_OBJID(OBJID_INamedObject, LCLID_INamedObj, METAMETA_GUID);
DEFINE_OBJID(OBJID_IManageReposTypeLib, LCLID_IManageReposTypeLib, METAMETA_GUID);
DEFINE_OBJID(OBJID_IReposTypeLib, LCLID_IReposTypeLib, METAMETA_GUID);
DEFINE_OBJID(OBJID_IReposRoot, LCLID_IReposRoot, METAMETA_GUID);

DEFINE_OBJID(OBJID_RClassImplIface, LCLID_RClassImplIface, METAMETA_GUID);
DEFINE_OBJID(OBJID_RIfaceInheritsFromIface, LCLID_RIfaceInheritsFromIface, METAMETA_GUID);
DEFINE_OBJID(OBJID_RIfaceHasMembers, LCLID_RIfaceHasMembers, METAMETA_GUID);
DEFINE_OBJID(OBJID_RColContainsItems, LCLID_RColContainsItems, METAMETA_GUID);
DEFINE_OBJID(OBJID_RContainerContextForReposTLBs, LCLID_RContainerContextForReposTLBs, METAMETA_GUID);
DEFINE_OBJID(OBJID_RReposTLBScopeForReposTypeInfo, LCLID_RReposTLBScopeForReposTypeInfo, METAMETA_GUID);

DEFINE_OBJID(OBJID_Ifaces, LCLID_Ifaces, METAMETA_GUID);
DEFINE_OBJID(OBJID_Classes, LCLID_Classes, METAMETA_GUID);
DEFINE_OBJID(OBJID_Ancestor, LCLID_Ancestor, METAMETA_GUID);
DEFINE_OBJID(OBJID_Descendants, LCLID_Descendants, METAMETA_GUID);
DEFINE_OBJID(OBJID_Members, LCLID_Members, METAMETA_GUID);
DEFINE_OBJID(OBJID_Iface, LCLID_Iface, METAMETA_GUID);
DEFINE_OBJID(OBJID_CollectionItem, LCLID_CollectionItem, METAMETA_GUID);
DEFINE_OBJID(OBJID_ItemInCollections, LCLID_ItemInCollections, METAMETA_GUID);
DEFINE_OBJID(OBJID_ReposTypeLibs, LCLID_ReposTypeLibs, METAMETA_GUID);
DEFINE_OBJID(OBJID_ReposTLBContexts, LCLID_ReposTLBContexts, METAMETA_GUID);
DEFINE_OBJID(OBJID_ReposTypeInfos, LCLID_ReposTypeInfos, METAMETA_GUID);
DEFINE_OBJID(OBJID_ReposTypeLibScopes, LCLID_ReposTypeLibScopes, METAMETA_GUID);

DEFINE_OBJID(OBJID_ReposRootObj, LCLID_ReposRootObj, METAMETA_GUID);
DEFINE_OBJID(OBJID_ReposTIM, LCLID_ReposTIM, METAMETA_GUID);

DEFINE_OBJID(OBJID_ClassID, LCLID_ClassID, METAMETA_GUID);
DEFINE_OBJID(OBJID_PropDescs, LCLID_PropDescs, METAMETA_GUID);
DEFINE_OBJID(OBJID_InterfaceID, LCLID_InterfaceID, METAMETA_GUID);
DEFINE_OBJID(OBJID_TableName, LCLID_TableName, METAMETA_GUID);
DEFINE_OBJID(OBJID_InterfaceFlags, LCLID_IfaceFlags, METAMETA_GUID);
DEFINE_OBJID(OBJID_DispID, LCLID_DispID, METAMETA_GUID);
DEFINE_OBJID(OBJID_InterfaceMemberFlags, LCLID_IfaceMemFlags, METAMETA_GUID);
DEFINE_OBJID(OBJID_RelshipTypeID, LCLID_RelshipTypeID, METAMETA_GUID); //@todo: I'd rather not have this.
DEFINE_OBJID(OBJID_CollectionFlags, LCLID_ColFlags, METAMETA_GUID);
DEFINE_OBJID(OBJID_MinCount, LCLID_MinCount, METAMETA_GUID);
DEFINE_OBJID(OBJID_MaxCount, LCLID_MaxCount, METAMETA_GUID);
DEFINE_OBJID(OBJID_IsOrigin, LCLID_IsOrigin, METAMETA_GUID);
DEFINE_OBJID(OBJID_ColumnName, LCLID_ColumnName, METAMETA_GUID);
DEFINE_OBJID(OBJID_APIType, LCLID_APIType, METAMETA_GUID);
DEFINE_OBJID(OBJID_SQLType, LCLID_SQLType, METAMETA_GUID);
DEFINE_OBJID(OBJID_SQLSize, LCLID_SQLSize, METAMETA_GUID);
DEFINE_OBJID(OBJID_SQLScale, LCLID_SQLScale, METAMETA_GUID);
DEFINE_OBJID(OBJID_TypeLibID, LCLID_TypeLibID, METAMETA_GUID);
DEFINE_OBJID(OBJID_TypeID, LCLID_TypeID, METAMETA_GUID);
DEFINE_OBJID(OBJID_Comments, LCLID_Comments, METAMETA_GUID);
DEFINE_OBJID(OBJID_ShortDescription, LCLID_ShortDesc, METAMETA_GUID);
DEFINE_OBJID(OBJID_ObjectName, LCLID_ObjName, METAMETA_GUID);

DEFINE_OBJID(OBJID_RelationshipTgtName, LCLID_RelshipTgtName, METAMETA_GUID);

DEFINE_OBJID(OBJID_ImplementsOptions, LCLID_ImplementsOptions, METAMETA_GUID);

DEFINE_OBJID(OBJID_NULL, LCLID_NULL, METAMETA_GUID);

// Cardinality definition constants.
const unsigned short CARD_NOLIMIT = 0xffff;	// No cardinality limit.

// V2 Definitions

// Local ID definitions
#define LCLID_IReposVersion			71
#define LCLID_IVersionCol			72
#define LCLID_IVersionedRelship		73

#define LCLID_Workspace				74

#define	LCLID_IWorkspace			75
#define	LCLID_IWorkspaceItem		76

#define LCLID_IVersionAdminInfo		77

#define LCLID_VersionCreateTime		78
#define LCLID_VersionModifyTime		79
#define LCLID_CreateByUser			80
#define LCLID_ModifyByUser			81

#define LCLID_IWorkspaceContainer	82

#define LCLID_RWksContainerContainsWorkspaces	83

#define LCLID_ContainedWorkspaces	84
#define LCLID_WorkspaceContainers	85

#define LCLID_LastMetaMetaID		85

// Internal ID definitions.
const INTID	INTID_IReposVersion		= {SITEID_METAMETA, LCLID_IReposVersion};
const INTID	INTID_IVersionCol		= {SITEID_METAMETA, LCLID_IVersionCol};
const INTID	INTID_IVersionedRelship	= {SITEID_METAMETA, LCLID_IVersionedRelship};

const INTID	INTID_Workspace			= {SITEID_METAMETA, LCLID_Workspace};

const INTID	INTID_IWorkspaceItem	= {SITEID_METAMETA,	LCLID_IWorkspaceItem};
const INTID	INTID_IWorkspace		= {SITEID_METAMETA, LCLID_IWorkspace};

const INTID INTID_IVersionAdminInfo	= {SITEID_METAMETA, LCLID_IVersionAdminInfo};

const INTID INTID_VersionCreateTime	= {SITEID_METAMETA, LCLID_VersionCreateTime};
const INTID INTID_VersionModifyTime	= {SITEID_METAMETA, LCLID_VersionModifyTime};
const INTID INTID_CreateByUser		= {SITEID_METAMETA, LCLID_CreateByUser};
const INTID INTID_ModifyByUser		= {SITEID_METAMETA, LCLID_ModifyByUser};

const INTID INTID_IWorkspaceContainer	= {SITEID_METAMETA, LCLID_IWorkspaceContainer};

const INTID INTID_RWksContainerContainsWorkspaces	= {SITEID_METAMETA, LCLID_RWksContainerContainsWorkspaces};

const INTID INTID_ContainedWorkspaces	= {SITEID_METAMETA, LCLID_ContainedWorkspaces};
const INTID INTID_WorkspaceContainers	= {SITEID_METAMETA, LCLID_WorkspaceContainers};

// DispatchID definitions.
#define DISPID_VersionCreateTime	LCLID_VersionCreateTime
#define DISPID_VersionModifyTime	LCLID_VersionModifyTime
#define DISPID_CreateByUser			LCLID_CreateByUser
#define DISPID_ModifyByUser			LCLID_ModifyByUser

#define DISPID_ContainedWorkspaces	LCLID_ContainedWorkspaces
#define DISPID_WorkspaceContainers	LCLID_WorkspaceContainers

// Object ID definitions.
DEFINE_OBJID(OBJID_IReposVersion, LCLID_IReposVersion, METAMETA_GUID);
DEFINE_OBJID(OBJID_IVersionCol, LCLID_IVersionCol, METAMETA_GUID);
DEFINE_OBJID(OBJID_IVersionedRelship, LCLID_IVersionedRelship, METAMETA_GUID);

DEFINE_OBJID(OBJID_Workspace, LCLID_Workspace, METAMETA_GUID);

DEFINE_OBJID(OBJID_IWorkspaceItem, LCLID_IWorkspaceItem, METAMETA_GUID);
DEFINE_OBJID(OBJID_IWorkspace,     LCLID_IWorkspace,     METAMETA_GUID);

DEFINE_OBJID(OBJID_IVersionAdminInfo, LCLID_IVersionAdminInfo, METAMETA_GUID);

DEFINE_OBJID(OBJID_VersionCreateTime, LCLID_VersionCreateTime, METAMETA_GUID);
DEFINE_OBJID(OBJID_VersionModifyTime, LCLID_VersionModifyTime, METAMETA_GUID);
DEFINE_OBJID(OBJID_CreateByUser, LCLID_CreateByUser, METAMETA_GUID);
DEFINE_OBJID(OBJID_ModifyByUser, LCLID_ModifyByUser, METAMETA_GUID);

DEFINE_OBJID(OBJID_IWorkspaceContainer, LCLID_IWorkspaceContainer, METAMETA_GUID);

DEFINE_OBJID(OBJID_RWksContainerContainsWorkspaces, LCLID_RWksContainerContainsWorkspaces, METAMETA_GUID);
DEFINE_OBJID(OBJID_ContainedWorkspaces, LCLID_ContainedWorkspaces, METAMETA_GUID);
DEFINE_OBJID(OBJID_WorkspaceContainers, LCLID_WorkspaceContainers, METAMETA_GUID);

// To be used as a parameter for CreateVersion.
DEFINE_OBJID(EXTVERSIONID_NULL, LCLID_NULL, METAMETA_GUID);

#endif // __REPTIM_H__
