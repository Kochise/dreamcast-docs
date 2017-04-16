//
// Copyright (C) Microsoft Corporation, 1997.  All rights reserved.
//

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.00.44 */
/* at Wed Sep 17 12:03:32 1997
 */
/* Compiler settings for msclus.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"
#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __msclus_h__
#define __msclus_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IClusterApplication_FWD_DEFINED__
#define __IClusterApplication_FWD_DEFINED__
typedef interface IClusterApplication IClusterApplication;
#endif 	/* __IClusterApplication_FWD_DEFINED__ */


#ifndef __ClusObjCollection_FWD_DEFINED__
#define __ClusObjCollection_FWD_DEFINED__
typedef interface ClusObjCollection ClusObjCollection;
#endif 	/* __ClusObjCollection_FWD_DEFINED__ */


#ifndef __DomainNames_FWD_DEFINED__
#define __DomainNames_FWD_DEFINED__
typedef interface DomainNames DomainNames;
#endif 	/* __DomainNames_FWD_DEFINED__ */


#ifndef __ClusterNames_FWD_DEFINED__
#define __ClusterNames_FWD_DEFINED__
typedef interface ClusterNames ClusterNames;
#endif 	/* __ClusterNames_FWD_DEFINED__ */


#ifndef __ClusRefObject_FWD_DEFINED__
#define __ClusRefObject_FWD_DEFINED__
typedef interface ClusRefObject ClusRefObject;
#endif 	/* __ClusRefObject_FWD_DEFINED__ */


#ifndef __ClusObj_FWD_DEFINED__
#define __ClusObj_FWD_DEFINED__
typedef interface ClusObj ClusObj;
#endif 	/* __ClusObj_FWD_DEFINED__ */


#ifndef __ICluster_FWD_DEFINED__
#define __ICluster_FWD_DEFINED__
typedef interface ICluster ICluster;
#endif 	/* __ICluster_FWD_DEFINED__ */


#ifndef __ClusNode_FWD_DEFINED__
#define __ClusNode_FWD_DEFINED__
typedef interface ClusNode ClusNode;
#endif 	/* __ClusNode_FWD_DEFINED__ */


#ifndef __ClusNodes_FWD_DEFINED__
#define __ClusNodes_FWD_DEFINED__
typedef interface ClusNodes ClusNodes;
#endif 	/* __ClusNodes_FWD_DEFINED__ */


#ifndef __ClusNetwork_FWD_DEFINED__
#define __ClusNetwork_FWD_DEFINED__
typedef interface ClusNetwork ClusNetwork;
#endif 	/* __ClusNetwork_FWD_DEFINED__ */


#ifndef __ClusNetworks_FWD_DEFINED__
#define __ClusNetworks_FWD_DEFINED__
typedef interface ClusNetworks ClusNetworks;
#endif 	/* __ClusNetworks_FWD_DEFINED__ */


#ifndef __ClusNetInterface_FWD_DEFINED__
#define __ClusNetInterface_FWD_DEFINED__
typedef interface ClusNetInterface ClusNetInterface;
#endif 	/* __ClusNetInterface_FWD_DEFINED__ */


#ifndef __ClusNetInterfaces_FWD_DEFINED__
#define __ClusNetInterfaces_FWD_DEFINED__
typedef interface ClusNetInterfaces ClusNetInterfaces;
#endif 	/* __ClusNetInterfaces_FWD_DEFINED__ */


#ifndef __ClusNodeNetInterfaces_FWD_DEFINED__
#define __ClusNodeNetInterfaces_FWD_DEFINED__
typedef interface ClusNodeNetInterfaces ClusNodeNetInterfaces;
#endif 	/* __ClusNodeNetInterfaces_FWD_DEFINED__ */


#ifndef __ClusNetworkNetInterfaces_FWD_DEFINED__
#define __ClusNetworkNetInterfaces_FWD_DEFINED__
typedef interface ClusNetworkNetInterfaces ClusNetworkNetInterfaces;
#endif 	/* __ClusNetworkNetInterfaces_FWD_DEFINED__ */


#ifndef __ClusResGroup_FWD_DEFINED__
#define __ClusResGroup_FWD_DEFINED__
typedef interface ClusResGroup ClusResGroup;
#endif 	/* __ClusResGroup_FWD_DEFINED__ */


#ifndef __ClusResGroups_FWD_DEFINED__
#define __ClusResGroups_FWD_DEFINED__
typedef interface ClusResGroups ClusResGroups;
#endif 	/* __ClusResGroups_FWD_DEFINED__ */


#ifndef __ClusResource_FWD_DEFINED__
#define __ClusResource_FWD_DEFINED__
typedef interface ClusResource ClusResource;
#endif 	/* __ClusResource_FWD_DEFINED__ */


#ifndef __ClusResDependencies_FWD_DEFINED__
#define __ClusResDependencies_FWD_DEFINED__
typedef interface ClusResDependencies ClusResDependencies;
#endif 	/* __ClusResDependencies_FWD_DEFINED__ */


#ifndef __ClusGroupResources_FWD_DEFINED__
#define __ClusGroupResources_FWD_DEFINED__
typedef interface ClusGroupResources ClusGroupResources;
#endif 	/* __ClusGroupResources_FWD_DEFINED__ */


#ifndef __ClusResTypeResources_FWD_DEFINED__
#define __ClusResTypeResources_FWD_DEFINED__
typedef interface ClusResTypeResources ClusResTypeResources;
#endif 	/* __ClusResTypeResources_FWD_DEFINED__ */


#ifndef __ClusResources_FWD_DEFINED__
#define __ClusResources_FWD_DEFINED__
typedef interface ClusResources ClusResources;
#endif 	/* __ClusResources_FWD_DEFINED__ */


#ifndef __ClusGroupOwners_FWD_DEFINED__
#define __ClusGroupOwners_FWD_DEFINED__
typedef interface ClusGroupOwners ClusGroupOwners;
#endif 	/* __ClusGroupOwners_FWD_DEFINED__ */


#ifndef __ClusResOwners_FWD_DEFINED__
#define __ClusResOwners_FWD_DEFINED__
typedef interface ClusResOwners ClusResOwners;
#endif 	/* __ClusResOwners_FWD_DEFINED__ */


#ifndef __ClusResType_FWD_DEFINED__
#define __ClusResType_FWD_DEFINED__
typedef interface ClusResType ClusResType;
#endif 	/* __ClusResType_FWD_DEFINED__ */


#ifndef __ClusResTypes_FWD_DEFINED__
#define __ClusResTypes_FWD_DEFINED__
typedef interface ClusResTypes ClusResTypes;
#endif 	/* __ClusResTypes_FWD_DEFINED__ */


#ifndef __ClusProperty_FWD_DEFINED__
#define __ClusProperty_FWD_DEFINED__
typedef interface ClusProperty ClusProperty;
#endif 	/* __ClusProperty_FWD_DEFINED__ */


#ifndef __ClusProperties_FWD_DEFINED__
#define __ClusProperties_FWD_DEFINED__
typedef interface ClusProperties ClusProperties;
#endif 	/* __ClusProperties_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL__intf_0000
 * at Wed Sep 17 12:03:32 1997
 * using MIDL 3.00.44
 ****************************************/
/* [local] */ 


#ifndef _CLUSTER_API_TYPES_
			/* size is 4 */
typedef struct _HCLUSTER __RPC_FAR *HCLUSTER;

			/* size is 4 */
typedef struct _HNODE __RPC_FAR *HNODE;

			/* size is 4 */
typedef struct _HRESOURCE __RPC_FAR *HRESOURCE;

			/* size is 4 */
typedef struct _HGROUP __RPC_FAR *HGROUP;

			/* size is 4 */
typedef struct _HRESTYPE __RPC_FAR *HRESTYPE;

			/* size is 4 */
typedef struct _HNETWORK __RPC_FAR *HNETWORK;

			/* size is 4 */
typedef struct _HNETINTERFACE __RPC_FAR *HNETINTERFACE;

			/* size is 4 */
typedef struct _HCHANGE __RPC_FAR *HCHANGE;

			/* size is 4 */
typedef struct _HCLUSENUM __RPC_FAR *HCLUSENUM;

			/* size is 4 */
typedef struct _HGROUPENUM __RPC_FAR *HGROUPENUM;

			/* size is 4 */
typedef struct _HRESENUM __RPC_FAR *HRESENUM;

			/* size is 4 */
typedef struct _HNETWORKENUM __RPC_FAR *HNETWORKENUM;

			/* size is 4 */
typedef struct _HNODEENUM __RPC_FAR *HNODEENUM;

			/* size is 2 */
typedef 
enum CLUSTER_QUORUM_TYPE
    {	OperationalQuorum	= 0,
	ModifyQuorum	= OperationalQuorum + 1
    }	CLUSTER_QUORUM_TYPE;

			/* size is 2 */
typedef 
enum CLUSTER_CHANGE
    {	CLUSTER_CHANGE_NODE_STATE	= 0x1,
	CLUSTER_CHANGE_NODE_DELETED	= 0x2,
	CLUSTER_CHANGE_NODE_ADDED	= 0x4,
	CLUSTER_CHANGE_NODE_PROPERTY	= 0x8,
	CLUSTER_CHANGE_REGISTRY_NAME	= 0x10,
	CLUSTER_CHANGE_REGISTRY_ATTRIBUTES	= 0x20,
	CLUSTER_CHANGE_REGISTRY_VALUE	= 0x40,
	CLUSTER_CHANGE_REGISTRY_SUBTREE	= 0x80,
	CLUSTER_CHANGE_RESOURCE_STATE	= 0x100,
	CLUSTER_CHANGE_RESOURCE_DELETED	= 0x200,
	CLUSTER_CHANGE_RESOURCE_ADDED	= 0x400,
	CLUSTER_CHANGE_RESOURCE_PROPERTY	= 0x800,
	CLUSTER_CHANGE_GROUP_STATE	= 0x1000,
	CLUSTER_CHANGE_GROUP_DELETED	= 0x2000,
	CLUSTER_CHANGE_GROUP_ADDED	= 0x4000,
	CLUSTER_CHANGE_GROUP_PROPERTY	= 0x8000,
	CLUSTER_CHANGE_RESOURCE_TYPE_DELETED	= 0x10000,
	CLUSTER_CHANGE_RESOURCE_TYPE_ADDED	= 0x20000,
	CLUSTER_CHANGE_NETWORK_STATE	= 0x100000,
	CLUSTER_CHANGE_NETWORK_DELETED	= 0x200000,
	CLUSTER_CHANGE_NETWORK_ADDED	= 0x400000,
	CLUSTER_CHANGE_NETWORK_PROPERTY	= 0x800000,
	CLUSTER_CHANGE_NETINTERFACE_STATE	= 0x1000000,
	CLUSTER_CHANGE_NETINTERFACE_DELETED	= 0x2000000,
	CLUSTER_CHANGE_NETINTERFACE_ADDED	= 0x4000000,
	CLUSTER_CHANGE_NETINTERFACE_PROPERTY	= 0x8000000,
	CLUSTER_CHANGE_QUORUM_STATE	= 0x10000000,
	CLUSTER_CHANGE_CLUSTER_STATE	= 0x20000000,
	CLUSTER_CHANGE_CLUSTER_PROPERTY	= 0x40000000,
	CLUSTER_CHANGE_HANDLE_CLOSE	= 0x80000000,
	CLUSTER_CHANGE_ALL	= CLUSTER_CHANGE_NODE_STATE | CLUSTER_CHANGE_NODE_DELETED | CLUSTER_CHANGE_NODE_ADDED | CLUSTER_CHANGE_NODE_PROPERTY | CLUSTER_CHANGE_REGISTRY_NAME | CLUSTER_CHANGE_REGISTRY_ATTRIBUTES | CLUSTER_CHANGE_REGISTRY_VALUE | CLUSTER_CHANGE_REGISTRY_SUBTREE | CLUSTER_CHANGE_RESOURCE_STATE | CLUSTER_CHANGE_RESOURCE_DELETED | CLUSTER_CHANGE_RESOURCE_ADDED | CLUSTER_CHANGE_RESOURCE_PROPERTY | CLUSTER_CHANGE_GROUP_STATE | CLUSTER_CHANGE_GROUP_DELETED | CLUSTER_CHANGE_GROUP_ADDED | CLUSTER_CHANGE_GROUP_PROPERTY | CLUSTER_CHANGE_RESOURCE_TYPE_DELETED | CLUSTER_CHANGE_RESOURCE_TYPE_ADDED | CLUSTER_CHANGE_NETWORK_STATE | CLUSTER_CHANGE_NETWORK_DELETED | CLUSTER_CHANGE_NETWORK_ADDED | CLUSTER_CHANGE_NETWORK_PROPERTY | CLUSTER_CHANGE_NETINTERFACE_STATE | CLUSTER_CHANGE_NETINTERFACE_DELETED | CLUSTER_CHANGE_NETINTERFACE_ADDED | CLUSTER_CHANGE_NETINTERFACE_PROPERTY | CLUSTER_CHANGE_QUORUM_STATE | CLUSTER_CHANGE_CLUSTER_STATE | CLUSTER_CHANGE_CLUSTER_PROPERTY | CLUSTER_CHANGE_HANDLE_CLOSE
    }	CLUSTER_CHANGE;

			/* size is 2 */
typedef 
enum CLUSTER_ENUM
    {	CLUSTER_ENUM_NODE	= 0x1,
	CLUSTER_ENUM_RESTYPE	= 0x2,
	CLUSTER_ENUM_RESOURCE	= 0x4,
	CLUSTER_ENUM_GROUP	= 0x8,
	CLUSTER_ENUM_NETWORK	= 0x10,
	CLUSTER_ENUM_NETINTERFACE	= 0x20,
	CLUSTER_ENUM_INTERNAL_NETWORK	= 0x80000000,
	CLUSTER_ENUM_ALL	= CLUSTER_ENUM_NODE | CLUSTER_ENUM_RESTYPE | CLUSTER_ENUM_RESOURCE | CLUSTER_ENUM_GROUP | CLUSTER_ENUM_NETWORK | CLUSTER_ENUM_NETINTERFACE
    }	CLUSTER_ENUM;

			/* size is 2 */
typedef 
enum CLUSTER_NODE_ENUM
    {	CLUSTER_NODE_ENUM_NETINTERFACES	= 0x1,
	CLUSTER_NODE_ENUM_ALL	= CLUSTER_NODE_ENUM_NETINTERFACES
    }	CLUSTER_NODE_ENUM;

			/* size is 2 */
typedef 
enum CLUSTER_NODE_STATE
    {	ClusterNodeStateUnknown	= -1,
	ClusterNodeUp	= ClusterNodeStateUnknown + 1,
	ClusterNodeDown	= ClusterNodeUp + 1,
	ClusterNodePaused	= ClusterNodeDown + 1,
	ClusterNodeJoining	= ClusterNodePaused + 1
    }	CLUSTER_NODE_STATE;

			/* size is 2 */
typedef 
enum CLUSTER_GROUP_ENUM
    {	CLUSTER_GROUP_ENUM_CONTAINS	= 0x1,
	CLUSTER_GROUP_ENUM_NODES	= 0x2,
	CLUSTER_GROUP_ENUM_ALL	= CLUSTER_GROUP_ENUM_CONTAINS | CLUSTER_GROUP_ENUM_NODES
    }	CLUSTER_GROUP_ENUM;

			/* size is 2 */
typedef 
enum CLUSTER_GROUP_STATE
    {	ClusterGroupStateUnknown	= -1,
	ClusterGroupOnline	= ClusterGroupStateUnknown + 1,
	ClusterGroupOffline	= ClusterGroupOnline + 1,
	ClusterGroupFailed	= ClusterGroupOffline + 1,
	ClusterGroupPartialOnline	= ClusterGroupFailed + 1
    }	CLUSTER_GROUP_STATE;

			/* size is 2 */
typedef 
enum CLUSTER_GROUP_AUTOFAILBACK_TYPE
    {	ClusterGroupPreventFailback	= 0,
	ClusterGroupAllowFailback	= ClusterGroupPreventFailback + 1,
	ClusterGroupFailbackTypeCount	= ClusterGroupAllowFailback + 1
    }	CLUSTER_GROUP_AUTOFAILBACK_TYPE;

			/* size is 2 */
typedef enum CLUSTER_GROUP_AUTOFAILBACK_TYPE CGAFT;

			/* size is 2 */
typedef 
enum CLUSTER_RESOURCE_STATE
    {	ClusterResourceStateUnknown	= -1,
	ClusterResourceInherited	= ClusterResourceStateUnknown + 1,
	ClusterResourceInitializing	= ClusterResourceInherited + 1,
	ClusterResourceOnline	= ClusterResourceInitializing + 1,
	ClusterResourceOffline	= ClusterResourceOnline + 1,
	ClusterResourceFailed	= ClusterResourceOffline + 1,
	ClusterResourcePending	= 128,
	ClusterResourceOnlinePending	= ClusterResourcePending + 1,
	ClusterResourceOfflinePending	= ClusterResourceOnlinePending + 1
    }	CLUSTER_RESOURCE_STATE;

			/* size is 2 */
typedef 
enum CLUSTER_RESOURCE_RESTART_ACTION
    {	ClusterResourceDontRestart	= 0,
	ClusterResourceRestartNoNotify	= ClusterResourceDontRestart + 1,
	ClusterResourceRestartNotify	= ClusterResourceRestartNoNotify + 1,
	ClusterResourceRestartActionCount	= ClusterResourceRestartNotify + 1
    }	CLUSTER_RESOURCE_RESTART_ACTION;

			/* size is 2 */
typedef enum CLUSTER_RESOURCE_RESTART_ACTION CRRA;

			/* size is 2 */
typedef 
enum CLUSTER_RESOURCE_CREATE_FLAGS
    {	CLUSTER_RESOURCE_SEPARATE_MONITOR	= 1,
	CLUSTER_RESOURCE_VALID_FLAGS	= CLUSTER_RESOURCE_SEPARATE_MONITOR
    }	CLUSTER_RESOURCE_CREATE_FLAGS;

			/* size is 2 */
typedef 
enum CLUSTER_PROPERTY_TYPE
    {	CLUSPROP_TYPE_ENDMARK	= 0,
	CLUSPROP_TYPE_LIST_VALUE	= CLUSPROP_TYPE_ENDMARK + 1,
	CLUSPROP_TYPE_RESCLASS	= CLUSPROP_TYPE_LIST_VALUE + 1,
	CLUSPROP_TYPE_RESERVED1	= CLUSPROP_TYPE_RESCLASS + 1,
	CLUSPROP_TYPE_NAME	= CLUSPROP_TYPE_RESERVED1 + 1,
	CLUSPROP_TYPE_SIGNATURE	= CLUSPROP_TYPE_NAME + 1,
	CLUSPROP_TYPE_SCSI_ADDRESS	= CLUSPROP_TYPE_SIGNATURE + 1,
	CLUSPROP_TYPE_DISK_NUMBER	= CLUSPROP_TYPE_SCSI_ADDRESS + 1,
	CLUSPROP_TYPE_PARTITION_INFO	= CLUSPROP_TYPE_DISK_NUMBER + 1,
	CLUSPROP_TYPE_FTSET_INFO	= CLUSPROP_TYPE_PARTITION_INFO + 1,
	CLUSPROP_TYPE_USER	= 32768
    }	CLUSTER_PROPERTY_TYPE;

			/* size is 2 */
typedef 
enum CLUSTER_PROPERTY_FORMAT
    {	CLUSPROP_FORMAT_UNKNOWN	= 0,
	CLUSPROP_FORMAT_BINARY	= CLUSPROP_FORMAT_UNKNOWN + 1,
	CLUSPROP_FORMAT_DWORD	= CLUSPROP_FORMAT_BINARY + 1,
	CLUSPROP_FORMAT_SZ	= CLUSPROP_FORMAT_DWORD + 1,
	CLUSPROP_FORMAT_EXPAND_SZ	= CLUSPROP_FORMAT_SZ + 1,
	CLUSPROP_FORMAT_MULTI_SZ	= CLUSPROP_FORMAT_EXPAND_SZ + 1,
	CLUSPROP_FORMAT_ULARGE_INTEGER	= CLUSPROP_FORMAT_MULTI_SZ + 1,
	CLUSPROP_FORMAT_USER	= 32768
    }	CLUSTER_PROPERTY_FORMAT;

			/* size is 2 */
typedef 
enum CLUSTER_PROPERTY_SYNTAX
    {	CLUSPROP_SYNTAX_ENDMARK	= ( DWORD  )(CLUSPROP_TYPE_ENDMARK << 16 | CLUSPROP_FORMAT_UNKNOWN),
	CLUSPROP_SYNTAX_NAME	= ( DWORD  )(CLUSPROP_TYPE_NAME << 16 | CLUSPROP_FORMAT_SZ),
	CLUSPROP_SYNTAX_RESCLASS	= ( DWORD  )(CLUSPROP_TYPE_RESCLASS << 16 | CLUSPROP_FORMAT_DWORD),
	CLUSPROP_SYNTAX_LIST_VALUE_SZ	= ( DWORD  )(CLUSPROP_TYPE_LIST_VALUE << 16 | CLUSPROP_FORMAT_SZ),
	CLUSPROP_SYNTAX_LIST_VALUE_EXPAND_SZ	= ( DWORD  )(CLUSPROP_TYPE_LIST_VALUE << 16 | CLUSPROP_FORMAT_EXPAND_SZ),
	CLUSPROP_SYNTAX_LIST_VALUE_DWORD	= ( DWORD  )(CLUSPROP_TYPE_LIST_VALUE << 16 | CLUSPROP_FORMAT_DWORD),
	CLUSPROP_SYNTAX_LIST_VALUE_BINARY	= ( DWORD  )(CLUSPROP_TYPE_LIST_VALUE << 16 | CLUSPROP_FORMAT_BINARY),
	CLUSPROP_SYNTAX_LIST_VALUE_MULTI_SZ	= ( DWORD  )(CLUSPROP_TYPE_LIST_VALUE << 16 | CLUSPROP_FORMAT_MULTI_SZ),
	CLUSPROP_SYNTAX_DISK_SIGNATURE	= ( DWORD  )(CLUSPROP_TYPE_SIGNATURE << 16 | CLUSPROP_FORMAT_DWORD),
	CLUSPROP_SYNTAX_SCSI_ADDRESS	= ( DWORD  )(CLUSPROP_TYPE_SCSI_ADDRESS << 16 | CLUSPROP_FORMAT_DWORD),
	CLUSPROP_SYNTAX_DISK_NUMBER	= ( DWORD  )(CLUSPROP_TYPE_DISK_NUMBER << 16 | CLUSPROP_FORMAT_DWORD),
	CLUSPROP_SYNTAX_PARTITION_INFO	= ( DWORD  )(CLUSPROP_TYPE_PARTITION_INFO << 16 | CLUSPROP_FORMAT_BINARY),
	CLUSPROP_SYNTAX_FTSET_INFO	= ( DWORD  )(CLUSPROP_TYPE_FTSET_INFO << 16 | CLUSPROP_FORMAT_BINARY)
    }	;

			/* size is 2 */
typedef 
enum CLUSTER_CONTROL_OBJECT
    {	CLUS_OBJECT_INVALID	= 0,
	CLUS_OBJECT_RESOURCE	= CLUS_OBJECT_INVALID + 1,
	CLUS_OBJECT_RESOURCE_TYPE	= CLUS_OBJECT_RESOURCE + 1,
	CLUS_OBJECT_GROUP	= CLUS_OBJECT_RESOURCE_TYPE + 1,
	CLUS_OBJECT_NODE	= CLUS_OBJECT_GROUP + 1,
	CLUS_OBJECT_NETWORK	= CLUS_OBJECT_NODE + 1,
	CLUS_OBJECT_NETINTERFACE	= CLUS_OBJECT_NETWORK + 1,
	CLUS_OBJECT_USER	= 128
    }	CLUSTER_CONTROL_OBJECT;

			/* size is 2 */
typedef 
enum CLCTL_CODES
    {	CLCTL_UNKNOWN	= 0 << 0 | 0 + 0 << 2 | 0 << 22,
	CLCTL_GET_CHARACTERISTICS	= 0x1 << 0 | 0 + 1 << 2 | 0 << 22,
	CLCTL_GET_FLAGS	= 0x1 << 0 | 0 + 2 << 2 | 0 << 22,
	CLCTL_GET_CLASS_INFO	= 0x1 << 0 | 0 + 3 << 2 | 0 << 22,
	CLCTL_GET_REQUIRED_DEPENDENCIES	= 0x1 << 0 | 0 + 4 << 2 | 0 << 22,
	CLCTL_GET_NAME	= 0x1 << 0 | 0 + 10 << 2 | 0 << 22,
	CLCTL_GET_RESOURCE_TYPE	= 0x1 << 0 | 0 + 11 << 2 | 0 << 22,
	CLCTL_GET_NODE	= 0x1 << 0 | 0 + 12 << 2 | 0 << 22,
	CLCTL_GET_NETWORK	= 0x1 << 0 | 0 + 13 << 2 | 0 << 22,
	CLCTL_GET_ID	= 0x1 << 0 | 0 + 14 << 2 | 0 << 22,
	CLCTL_ENUM_COMMON_PROPERTIES	= 0x1 << 0 | 0 + 20 << 2 | 0 << 22,
	CLCTL_GET_RO_COMMON_PROPERTIES	= 0x1 << 0 | 0 + 21 << 2 | 0 << 22,
	CLCTL_GET_COMMON_PROPERTIES	= 0x1 << 0 | 0 + 22 << 2 | 0 << 22,
	CLCTL_SET_COMMON_PROPERTIES	= 0x2 << 0 | 0 + 23 << 2 | 0x1 << 22,
	CLCTL_VALIDATE_COMMON_PROPERTIES	= 0x1 << 0 | 0 + 24 << 2 | 0 << 22,
	CLCTL_ENUM_PRIVATE_PROPERTIES	= 0x1 << 0 | 0 + 30 << 2 | 0 << 22,
	CLCTL_GET_RO_PRIVATE_PROPERTIES	= 0x1 << 0 | 0 + 31 << 2 | 0 << 22,
	CLCTL_GET_PRIVATE_PROPERTIES	= 0x1 << 0 | 0 + 32 << 2 | 0 << 22,
	CLCTL_SET_PRIVATE_PROPERTIES	= 0x2 << 0 | 0 + 33 << 2 | 0x1 << 22,
	CLCTL_VALIDATE_PRIVATE_PROPERTIES	= 0x1 << 0 | 0 + 34 << 2 | 0 << 22,
	CLCTL_ADD_REGISTRY_CHECKPOINT	= 0x2 << 0 | 0 + 40 << 2 | 0x1 << 22,
	CLCTL_DELETE_REGISTRY_CHECKPOINT	= 0x2 << 0 | 0 + 41 << 2 | 0x1 << 22,
	CLCTL_GET_REGISTRY_CHECKPOINTS	= 0x1 << 0 | 0 + 42 << 2 | 0 << 22,
	CLCTL_GET_LOADBAL_PROCESS_LIST	= 0x1 << 0 | 0 + 50 << 2 | 0 << 22,
	CLCTL_STORAGE_GET_DISK_INFO	= 0x1 << 0 | 0 + 100 << 2 | 0 << 22,
	CLCTL_STORAGE_GET_AVAILABLE_DISKS	= 0x1 << 0 | 0 + 101 << 2 | 0 << 22,
	CLCTL_STORAGE_IS_PATH_VALID	= 0x1 << 0 | 0 + 102 << 2 | 0 << 22,
	CLCTL_STORAGE_GET_ALL_AVAILABLE_DISKS	= 0x1 << 0 | 0 + 103 << 2 | 0 << 22 | 1 << 23,
	CLCTL_DELETE	= 0x2 << 0 | 1 << 20 | 0 + 1 << 2 | 0x1 << 22,
	CLCTL_INSTALL_NODE	= 0x2 << 0 | 1 << 20 | 0 + 2 << 2 | 0x1 << 22,
	CLCTL_EVICT_NODE	= 0x2 << 0 | 1 << 20 | 0 + 3 << 2 | 0x1 << 22,
	CLCTL_ADD_DEPENDENCY	= 0x2 << 0 | 1 << 20 | 0 + 4 << 2 | 0x1 << 22,
	CLCTL_REMOVE_DEPENDENCY	= 0x2 << 0 | 1 << 20 | 0 + 5 << 2 | 0x1 << 22,
	CLCTL_ADD_OWNER	= 0x2 << 0 | 1 << 20 | 0 + 6 << 2 | 0x1 << 22,
	CLCTL_REMOVE_OWNER	= 0x2 << 0 | 1 << 20 | 0 + 7 << 2 | 0x1 << 22,
	CLCTL_SET_NAME	= 0x2 << 0 | 1 << 20 | 0 + 9 << 2 | 0x1 << 22,
	CLCTL_CLUSTER_NAME_CHANGED	= 0x2 << 0 | 1 << 20 | 0 + 10 << 2 | 0x1 << 22
    }	CLCTL_CODES;

			/* size is 2 */
typedef 
enum CLUSCTL_RESOURCE_CODES
    {	CLUSCTL_RESOURCE_UNKNOWN	= CLUS_OBJECT_RESOURCE << 24 | CLCTL_UNKNOWN,
	CLUSCTL_RESOURCE_GET_CHARACTERISTICS	= CLUS_OBJECT_RESOURCE << 24 | CLCTL_GET_CHARACTERISTICS,
	CLUSCTL_RESOURCE_GET_FLAGS	= CLUS_OBJECT_RESOURCE << 24 | CLCTL_GET_FLAGS,
	CLUSCTL_RESOURCE_GET_CLASS_INFO	= CLUS_OBJECT_RESOURCE << 24 | CLCTL_GET_CLASS_INFO,
	CLUSCTL_RESOURCE_GET_REQUIRED_DEPENDENCIES	= CLUS_OBJECT_RESOURCE << 24 | CLCTL_GET_REQUIRED_DEPENDENCIES,
	CLUSCTL_RESOURCE_GET_NAME	= CLUS_OBJECT_RESOURCE << 24 | CLCTL_GET_NAME,
	CLUSCTL_RESOURCE_GET_ID	= CLUS_OBJECT_RESOURCE << 24 | CLCTL_GET_ID,
	CLUSCTL_RESOURCE_GET_RESOURCE_TYPE	= CLUS_OBJECT_RESOURCE << 24 | CLCTL_GET_RESOURCE_TYPE,
	CLUSCTL_RESOURCE_ENUM_COMMON_PROPERTIES	= CLUS_OBJECT_RESOURCE << 24 | CLCTL_ENUM_COMMON_PROPERTIES,
	CLUSCTL_RESOURCE_GET_RO_COMMON_PROPERTIES	= CLUS_OBJECT_RESOURCE << 24 | CLCTL_GET_RO_COMMON_PROPERTIES,
	CLUSCTL_RESOURCE_GET_COMMON_PROPERTIES	= CLUS_OBJECT_RESOURCE << 24 | CLCTL_GET_COMMON_PROPERTIES,
	CLUSCTL_RESOURCE_SET_COMMON_PROPERTIES	= CLUS_OBJECT_RESOURCE << 24 | CLCTL_SET_COMMON_PROPERTIES,
	CLUSCTL_RESOURCE_VALIDATE_COMMON_PROPERTIES	= CLUS_OBJECT_RESOURCE << 24 | CLCTL_VALIDATE_COMMON_PROPERTIES,
	CLUSCTL_RESOURCE_ENUM_PRIVATE_PROPERTIES	= CLUS_OBJECT_RESOURCE << 24 | CLCTL_ENUM_PRIVATE_PROPERTIES,
	CLUSCTL_RESOURCE_GET_RO_PRIVATE_PROPERTIES	= CLUS_OBJECT_RESOURCE << 24 | CLCTL_GET_RO_PRIVATE_PROPERTIES,
	CLUSCTL_RESOURCE_GET_PRIVATE_PROPERTIES	= CLUS_OBJECT_RESOURCE << 24 | CLCTL_GET_PRIVATE_PROPERTIES,
	CLUSCTL_RESOURCE_SET_PRIVATE_PROPERTIES	= CLUS_OBJECT_RESOURCE << 24 | CLCTL_SET_PRIVATE_PROPERTIES,
	CLUSCTL_RESOURCE_VALIDATE_PRIVATE_PROPERTIES	= CLUS_OBJECT_RESOURCE << 24 | CLCTL_VALIDATE_PRIVATE_PROPERTIES,
	CLUSCTL_RESOURCE_ADD_REGISTRY_CHECKPOINT	= CLUS_OBJECT_RESOURCE << 24 | CLCTL_ADD_REGISTRY_CHECKPOINT,
	CLUSCTL_RESOURCE_DELETE_REGISTRY_CHECKPOINT	= CLUS_OBJECT_RESOURCE << 24 | CLCTL_DELETE_REGISTRY_CHECKPOINT,
	CLUSCTL_RESOURCE_GET_REGISTRY_CHECKPOINTS	= CLUS_OBJECT_RESOURCE << 24 | CLCTL_GET_REGISTRY_CHECKPOINTS,
	CLUSCTL_RESOURCE_GET_LOADBAL_PROCESS_LIST	= CLUS_OBJECT_RESOURCE << 24 | CLCTL_GET_LOADBAL_PROCESS_LIST,
	CLUSCTL_RESOURCE_STORAGE_GET_DISK_INFO	= CLUS_OBJECT_RESOURCE << 24 | CLCTL_STORAGE_GET_DISK_INFO,
	CLUSCTL_RESOURCE_STORAGE_IS_PATH_VALID	= CLUS_OBJECT_RESOURCE << 24 | CLCTL_STORAGE_IS_PATH_VALID,
	CLUSCTL_RESOURCE_DELETE	= CLUS_OBJECT_RESOURCE << 24 | CLCTL_DELETE,
	CLUSCTL_RESOURCE_INSTALL_NODE	= CLUS_OBJECT_RESOURCE << 24 | CLCTL_INSTALL_NODE,
	CLUSCTL_RESOURCE_EVICT_NODE	= CLUS_OBJECT_RESOURCE << 24 | CLCTL_EVICT_NODE,
	CLUSCTL_RESOURCE_ADD_DEPENDENCY	= CLUS_OBJECT_RESOURCE << 24 | CLCTL_ADD_DEPENDENCY,
	CLUSCTL_RESOURCE_REMOVE_DEPENDENCY	= CLUS_OBJECT_RESOURCE << 24 | CLCTL_REMOVE_DEPENDENCY,
	CLUSCTL_RESOURCE_ADD_OWNER	= CLUS_OBJECT_RESOURCE << 24 | CLCTL_ADD_OWNER,
	CLUSCTL_RESOURCE_REMOVE_OWNER	= CLUS_OBJECT_RESOURCE << 24 | CLCTL_REMOVE_OWNER,
	CLUSCTL_RESOURCE_SET_NAME	= CLUS_OBJECT_RESOURCE << 24 | CLCTL_SET_NAME,
	CLUSCTL_RESOURCE_CLUSTER_NAME_CHANGED	= CLUS_OBJECT_RESOURCE << 24 | CLCTL_CLUSTER_NAME_CHANGED
    }	CLUSCTL_RESOURCE_CODES;

			/* size is 2 */
typedef 
enum CLUSCTL_RESOURCE_TYPE_CODES
    {	CLUSCTL_RESOURCE_TYPE_UNKNOWN	= CLUS_OBJECT_RESOURCE_TYPE << 24 | CLCTL_UNKNOWN,
	CLUSCTL_RESOURCE_TYPE_GET_CHARACTERISTICS	= CLUS_OBJECT_RESOURCE_TYPE << 24 | CLCTL_GET_CHARACTERISTICS,
	CLUSCTL_RESOURCE_TYPE_GET_FLAGS	= CLUS_OBJECT_RESOURCE_TYPE << 24 | CLCTL_GET_FLAGS,
	CLUSCTL_RESOURCE_TYPE_GET_CLASS_INFO	= CLUS_OBJECT_RESOURCE_TYPE << 24 | CLCTL_GET_CLASS_INFO,
	CLUSCTL_RESOURCE_TYPE_GET_REQUIRED_DEPENDENCIES	= CLUS_OBJECT_RESOURCE_TYPE << 24 | CLCTL_GET_REQUIRED_DEPENDENCIES,
	CLUSCTL_RESOURCE_TYPE_ENUM_COMMON_PROPERTIES	= CLUS_OBJECT_RESOURCE_TYPE << 24 | CLCTL_ENUM_COMMON_PROPERTIES,
	CLUSCTL_RESOURCE_TYPE_GET_RO_COMMON_PROPERTIES	= CLUS_OBJECT_RESOURCE_TYPE << 24 | CLCTL_GET_RO_COMMON_PROPERTIES,
	CLUSCTL_RESOURCE_TYPE_GET_COMMON_PROPERTIES	= CLUS_OBJECT_RESOURCE_TYPE << 24 | CLCTL_GET_COMMON_PROPERTIES,
	CLUSCTL_RESOURCE_TYPE_VALIDATE_COMMON_PROPERTIES	= CLUS_OBJECT_RESOURCE_TYPE << 24 | CLCTL_VALIDATE_COMMON_PROPERTIES,
	CLUSCTL_RESOURCE_TYPE_SET_COMMON_PROPERTIES	= CLUS_OBJECT_RESOURCE_TYPE << 24 | CLCTL_SET_COMMON_PROPERTIES,
	CLUSCTL_RESOURCE_TYPE_ENUM_PRIVATE_PROPERTIES	= CLUS_OBJECT_RESOURCE_TYPE << 24 | CLCTL_ENUM_PRIVATE_PROPERTIES,
	CLUSCTL_RESOURCE_TYPE_GET_RO_PRIVATE_PROPERTIES	= CLUS_OBJECT_RESOURCE_TYPE << 24 | CLCTL_GET_RO_PRIVATE_PROPERTIES,
	CLUSCTL_RESOURCE_TYPE_GET_PRIVATE_PROPERTIES	= CLUS_OBJECT_RESOURCE_TYPE << 24 | CLCTL_GET_PRIVATE_PROPERTIES,
	CLUSCTL_RESOURCE_TYPE_SET_PRIVATE_PROPERTIES	= CLUS_OBJECT_RESOURCE_TYPE << 24 | CLCTL_SET_PRIVATE_PROPERTIES,
	CLUSCTL_RESOURCE_TYPE_VALIDATE_PRIVATE_PROPERTIES	= CLUS_OBJECT_RESOURCE_TYPE << 24 | CLCTL_VALIDATE_PRIVATE_PROPERTIES,
	CLUSCTL_RESOURCE_TYPE_GET_REGISTRY_CHECKPOINTS	= CLUS_OBJECT_RESOURCE_TYPE << 24 | CLCTL_GET_REGISTRY_CHECKPOINTS,
	CLUSCTL_RESOURCE_TYPE_STORAGE_GET_AVAILABLE_DISKS	= CLUS_OBJECT_RESOURCE_TYPE << 24 | CLCTL_STORAGE_GET_AVAILABLE_DISKS,
	CLUSCTL_RESOURCE_TYPE_INSTALL_NODE	= CLUS_OBJECT_RESOURCE_TYPE << 24 | CLCTL_INSTALL_NODE,
	CLUSCTL_RESOURCE_TYPE_EVICT_NODE	= CLUS_OBJECT_RESOURCE_TYPE << 24 | CLCTL_EVICT_NODE
    }	CLUSCTL_RESOURCE_TYPE_CODES;

			/* size is 2 */
typedef 
enum CLUSCTL_GROUP_CODES
    {	CLUSCTL_GROUP_UNKNOWN	= CLUS_OBJECT_GROUP << 24 | CLCTL_UNKNOWN,
	CLUSCTL_GROUP_GET_CHARACTERISTICS	= CLUS_OBJECT_GROUP << 24 | CLCTL_GET_CHARACTERISTICS,
	CLUSCTL_GROUP_GET_FLAGS	= CLUS_OBJECT_GROUP << 24 | CLCTL_GET_FLAGS,
	CLUSCTL_GROUP_GET_NAME	= CLUS_OBJECT_GROUP << 24 | CLCTL_GET_NAME,
	CLUSCTL_GROUP_GET_ID	= CLUS_OBJECT_GROUP << 24 | CLCTL_GET_ID,
	CLUSCTL_GROUP_ENUM_COMMON_PROPERTIES	= CLUS_OBJECT_GROUP << 24 | CLCTL_ENUM_COMMON_PROPERTIES,
	CLUSCTL_GROUP_GET_RO_COMMON_PROPERTIES	= CLUS_OBJECT_GROUP << 24 | CLCTL_GET_RO_COMMON_PROPERTIES,
	CLUSCTL_GROUP_GET_COMMON_PROPERTIES	= CLUS_OBJECT_GROUP << 24 | CLCTL_GET_COMMON_PROPERTIES,
	CLUSCTL_GROUP_SET_COMMON_PROPERTIES	= CLUS_OBJECT_GROUP << 24 | CLCTL_SET_COMMON_PROPERTIES,
	CLUSCTL_GROUP_VALIDATE_COMMON_PROPERTIES	= CLUS_OBJECT_GROUP << 24 | CLCTL_VALIDATE_COMMON_PROPERTIES,
	CLUSCTL_GROUP_ENUM_PRIVATE_PROPERTIES	= CLUS_OBJECT_GROUP << 24 | CLCTL_ENUM_PRIVATE_PROPERTIES,
	CLUSCTL_GROUP_GET_RO_PRIVATE_PROPERTIES	= CLUS_OBJECT_GROUP << 24 | CLCTL_GET_RO_PRIVATE_PROPERTIES,
	CLUSCTL_GROUP_GET_PRIVATE_PROPERTIES	= CLUS_OBJECT_GROUP << 24 | CLCTL_GET_PRIVATE_PROPERTIES,
	CLUSCTL_GROUP_SET_PRIVATE_PROPERTIES	= CLUS_OBJECT_GROUP << 24 | CLCTL_SET_PRIVATE_PROPERTIES,
	CLUSCTL_GROUP_VALIDATE_PRIVATE_PROPERTIES	= CLUS_OBJECT_GROUP << 24 | CLCTL_VALIDATE_PRIVATE_PROPERTIES
    }	CLUSCTL_GROUP_CODES;

			/* size is 2 */
typedef 
enum CLUSCTL_NODE_CODES
    {	CLUSCTL_NODE_UNKNOWN	= CLUS_OBJECT_NODE << 24 | CLCTL_UNKNOWN,
	CLUSCTL_NODE_GET_CHARACTERISTICS	= CLUS_OBJECT_NODE << 24 | CLCTL_GET_CHARACTERISTICS,
	CLUSCTL_NODE_GET_FLAGS	= CLUS_OBJECT_NODE << 24 | CLCTL_GET_FLAGS,
	CLUSCTL_NODE_GET_NAME	= CLUS_OBJECT_NODE << 24 | CLCTL_GET_NAME,
	CLUSCTL_NODE_GET_ID	= CLUS_OBJECT_NODE << 24 | CLCTL_GET_ID,
	CLUSCTL_NODE_ENUM_COMMON_PROPERTIES	= CLUS_OBJECT_NODE << 24 | CLCTL_ENUM_COMMON_PROPERTIES,
	CLUSCTL_NODE_GET_RO_COMMON_PROPERTIES	= CLUS_OBJECT_NODE << 24 | CLCTL_GET_RO_COMMON_PROPERTIES,
	CLUSCTL_NODE_GET_COMMON_PROPERTIES	= CLUS_OBJECT_NODE << 24 | CLCTL_GET_COMMON_PROPERTIES,
	CLUSCTL_NODE_SET_COMMON_PROPERTIES	= CLUS_OBJECT_NODE << 24 | CLCTL_SET_COMMON_PROPERTIES,
	CLUSCTL_NODE_VALIDATE_COMMON_PROPERTIES	= CLUS_OBJECT_NODE << 24 | CLCTL_VALIDATE_COMMON_PROPERTIES,
	CLUSCTL_NODE_ENUM_PRIVATE_PROPERTIES	= CLUS_OBJECT_NODE << 24 | CLCTL_ENUM_PRIVATE_PROPERTIES,
	CLUSCTL_NODE_GET_RO_PRIVATE_PROPERTIES	= CLUS_OBJECT_NODE << 24 | CLCTL_GET_RO_PRIVATE_PROPERTIES,
	CLUSCTL_NODE_GET_PRIVATE_PROPERTIES	= CLUS_OBJECT_NODE << 24 | CLCTL_GET_PRIVATE_PROPERTIES,
	CLUSCTL_NODE_SET_PRIVATE_PROPERTIES	= CLUS_OBJECT_NODE << 24 | CLCTL_SET_PRIVATE_PROPERTIES,
	CLUSCTL_NODE_VALIDATE_PRIVATE_PROPERTIES	= CLUS_OBJECT_NODE << 24 | CLCTL_VALIDATE_PRIVATE_PROPERTIES
    }	CLUSCTL_NODE_CODES;

			/* size is 2 */
typedef 
enum CLUSCTL_NETWORK_CODES
    {	CLUSCTL_NETWORK_UNKNOWN	= CLUS_OBJECT_NETWORK << 24 | CLCTL_UNKNOWN,
	CLUSCTL_NETWORK_GET_CHARACTERISTICS	= CLUS_OBJECT_NETWORK << 24 | CLCTL_GET_CHARACTERISTICS,
	CLUSCTL_NETWORK_GET_FLAGS	= CLUS_OBJECT_NETWORK << 24 | CLCTL_GET_FLAGS,
	CLUSCTL_NETWORK_GET_NAME	= CLUS_OBJECT_NETWORK << 24 | CLCTL_GET_NAME,
	CLUSCTL_NETWORK_GET_ID	= CLUS_OBJECT_NETWORK << 24 | CLCTL_GET_ID,
	CLUSCTL_NETWORK_ENUM_COMMON_PROPERTIES	= CLUS_OBJECT_NETWORK << 24 | CLCTL_ENUM_COMMON_PROPERTIES,
	CLUSCTL_NETWORK_GET_RO_COMMON_PROPERTIES	= CLUS_OBJECT_NETWORK << 24 | CLCTL_GET_RO_COMMON_PROPERTIES,
	CLUSCTL_NETWORK_GET_COMMON_PROPERTIES	= CLUS_OBJECT_NETWORK << 24 | CLCTL_GET_COMMON_PROPERTIES,
	CLUSCTL_NETWORK_SET_COMMON_PROPERTIES	= CLUS_OBJECT_NETWORK << 24 | CLCTL_SET_COMMON_PROPERTIES,
	CLUSCTL_NETWORK_VALIDATE_COMMON_PROPERTIES	= CLUS_OBJECT_NETWORK << 24 | CLCTL_VALIDATE_COMMON_PROPERTIES,
	CLUSCTL_NETWORK_ENUM_PRIVATE_PROPERTIES	= CLUS_OBJECT_NETWORK << 24 | CLCTL_ENUM_PRIVATE_PROPERTIES,
	CLUSCTL_NETWORK_GET_RO_PRIVATE_PROPERTIES	= CLUS_OBJECT_NETWORK << 24 | CLCTL_GET_RO_PRIVATE_PROPERTIES,
	CLUSCTL_NETWORK_GET_PRIVATE_PROPERTIES	= CLUS_OBJECT_NETWORK << 24 | CLCTL_GET_PRIVATE_PROPERTIES,
	CLUSCTL_NETWORK_SET_PRIVATE_PROPERTIES	= CLUS_OBJECT_NETWORK << 24 | CLCTL_SET_PRIVATE_PROPERTIES,
	CLUSCTL_NETWORK_VALIDATE_PRIVATE_PROPERTIES	= CLUS_OBJECT_NETWORK << 24 | CLCTL_VALIDATE_PRIVATE_PROPERTIES
    }	CLUSCTL_NETWORK_CODES;

			/* size is 2 */
typedef 
enum CLUSCTL_NETINTERFACE_CODES
    {	CLUSCTL_NETINTERFACE_UNKNOWN	= CLUS_OBJECT_NETINTERFACE << 24 | CLCTL_UNKNOWN,
	CLUSCTL_NETINTERFACE_GET_CHARACTERISTICS	= CLUS_OBJECT_NETINTERFACE << 24 | CLCTL_GET_CHARACTERISTICS,
	CLUSCTL_NETINTERFACE_GET_FLAGS	= CLUS_OBJECT_NETINTERFACE << 24 | CLCTL_GET_FLAGS,
	CLUSCTL_NETINTERFACE_GET_NAME	= CLUS_OBJECT_NETINTERFACE << 24 | CLCTL_GET_NAME,
	CLUSCTL_NETINTERFACE_GET_ID	= CLUS_OBJECT_NETINTERFACE << 24 | CLCTL_GET_ID,
	CLUSCTL_NETINTERFACE_GET_NODE	= CLUS_OBJECT_NETINTERFACE << 24 | CLCTL_GET_NODE,
	CLUSCTL_NETINTERFACE_GET_NETWORK	= CLUS_OBJECT_NETINTERFACE << 24 | CLCTL_GET_NETWORK,
	CLUSCTL_NETINTERFACE_ENUM_COMMON_PROPERTIES	= CLUS_OBJECT_NETINTERFACE << 24 | CLCTL_ENUM_COMMON_PROPERTIES,
	CLUSCTL_NETINTERFACE_GET_RO_COMMON_PROPERTIES	= CLUS_OBJECT_NETINTERFACE << 24 | CLCTL_GET_RO_COMMON_PROPERTIES,
	CLUSCTL_NETINTERFACE_GET_COMMON_PROPERTIES	= CLUS_OBJECT_NETINTERFACE << 24 | CLCTL_GET_COMMON_PROPERTIES,
	CLUSCTL_NETINTERFACE_SET_COMMON_PROPERTIES	= CLUS_OBJECT_NETINTERFACE << 24 | CLCTL_SET_COMMON_PROPERTIES,
	CLUSCTL_NETINTERFACE_VALIDATE_COMMON_PROPERTIES	= CLUS_OBJECT_NETINTERFACE << 24 | CLCTL_VALIDATE_COMMON_PROPERTIES,
	CLUSCTL_NETINTERFACE_ENUM_PRIVATE_PROPERTIES	= CLUS_OBJECT_NETINTERFACE << 24 | CLCTL_ENUM_PRIVATE_PROPERTIES,
	CLUSCTL_NETINTERFACE_GET_RO_PRIVATE_PROPERTIES	= CLUS_OBJECT_NETINTERFACE << 24 | CLCTL_GET_RO_PRIVATE_PROPERTIES,
	CLUSCTL_NETINTERFACE_GET_PRIVATE_PROPERTIES	= CLUS_OBJECT_NETINTERFACE << 24 | CLCTL_GET_PRIVATE_PROPERTIES,
	CLUSCTL_NETINTERFACE_SET_PRIVATE_PROPERTIES	= CLUS_OBJECT_NETINTERFACE << 24 | CLCTL_SET_PRIVATE_PROPERTIES,
	CLUSCTL_NETINTERFACE_VALIDATE_PRIVATE_PROPERTIES	= CLUS_OBJECT_NETINTERFACE << 24 | CLCTL_VALIDATE_PRIVATE_PROPERTIES
    }	CLUSCTL_NETINTERFACE_CODES;

			/* size is 2 */
typedef 
enum CLUSTER_RESOURCE_CLASS
    {	CLUS_RESCLASS_UNKNOWN	= 0,
	CLUS_RESCLASS_STORAGE	= CLUS_RESCLASS_UNKNOWN + 1,
	CLUS_RESCLASS_USER	= 32768
    }	CLUSTER_RESOURCE_CLASS;

			/* size is 2 */
typedef 
enum CLUS_RESSUBCLASS
    {	CLUS_RESSUBCLASS_SHARED	= 0x80000000
    }	CLUS_RESSUBCLASS;

			/* size is 2 */
typedef 
enum CLUS_CHARACTERISTICS
    {	CLUS_CHAR_UNKNOWN	= 0,
	CLUS_CHAR_QUORUM	= 0x1,
	CLUS_CHAR_DELETE_REQUIRES_ALL_NODES	= 0x2
    }	CLUS_CHARACTERISTICS;

			/* size is 2 */
typedef 
enum CLUS_FLAGS
    {	CLUS_FLAG_CORE	= 0x1
    }	CLUS_FLAGS;

			/* size is 2 */
typedef 
enum CLUSPROP_PIFLAGS
    {	CLUSPROP_PIFLAG_STICKY	= 0x1,
	CLUSPROP_PIFLAG_REMOVABLE	= 0x2,
	CLUSPROP_PIFLAG_USABLE	= 0x4
    }	CLUSPROP_PIFLAGS;

			/* size is 2 */
typedef 
enum CLUSTER_RESOURCE_ENUM
    {	CLUSTER_RESOURCE_ENUM_DEPENDS	= 0x1,
	CLUSTER_RESOURCE_ENUM_PROVIDES	= 0x2,
	CLUSTER_RESOURCE_ENUM_NODES	= 0x4,
	CLUSTER_RESOURCE_ENUM_ALL	= CLUSTER_RESOURCE_ENUM_DEPENDS | CLUSTER_RESOURCE_ENUM_PROVIDES | CLUSTER_RESOURCE_ENUM_NODES
    }	CLUSTER_RESOURCE_ENUM;

			/* size is 2 */
typedef 
enum CLUSTER_NETWORK_ENUM
    {	CLUSTER_NETWORK_ENUM_NETINTERFACES	= 0x1,
	CLUSTER_NETWORK_ENUM_ALL	= CLUSTER_NETWORK_ENUM_NETINTERFACES
    }	CLUSTER_NETWORK_ENUM;

			/* size is 2 */
typedef 
enum CLUSTER_NETWORK_STATE
    {	ClusterNetworkStateUnknown	= -1,
	ClusterNetworkUnavailable	= ClusterNetworkStateUnknown + 1,
	ClusterNetworkDown	= ClusterNetworkUnavailable + 1,
	ClusterNetworkPartitioned	= ClusterNetworkDown + 1,
	ClusterNetworkUp	= ClusterNetworkPartitioned + 1
    }	CLUSTER_NETWORK_STATE;

			/* size is 2 */
typedef 
enum CLUSTER_NETWORK_ROLE
    {	ClusterNetworkRoleNone	= 0,
	ClusterNetworkRoleInternalUse	= 0x1,
	ClusterNetworkRoleClientAccess	= 0x2,
	ClusterNetworkRoleInternalAndClient	= 0x3
    }	CLUSTER_NETWORK_ROLE;

			/* size is 2 */
typedef 
enum CLUSTER_NETINTERFACE_STATE
    {	ClusterNetInterfaceStateUnknown	= -1,
	ClusterNetInterfaceUnavailable	= ClusterNetInterfaceStateUnknown + 1,
	ClusterNetInterfaceFailed	= ClusterNetInterfaceUnavailable + 1,
	ClusterNetInterfaceUnreachable	= ClusterNetInterfaceFailed + 1,
	ClusterNetInterfaceUp	= ClusterNetInterfaceUnreachable + 1
    }	CLUSTER_NETINTERFACE_STATE;

#define _CLUSTER_API_TYPES_
#endif // _CLUSTER_API_TYPES_
			/* size is 0 */

			/* size is 0 */

			/* size is 0 */

			/* size is 0 */

			/* size is 0 */

			/* size is 0 */

			/* size is 0 */

			/* size is 0 */

			/* size is 0 */

			/* size is 0 */

			/* size is 0 */

			/* size is 0 */

			/* size is 0 */

			/* size is 0 */

			/* size is 0 */

			/* size is 0 */

			/* size is 0 */

			/* size is 0 */

			/* size is 0 */

			/* size is 0 */

			/* size is 0 */

			/* size is 0 */

			/* size is 0 */

			/* size is 0 */

			/* size is 0 */

			/* size is 0 */

			/* size is 0 */

			/* size is 0 */



extern RPC_IF_HANDLE __MIDL__intf_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL__intf_0000_v0_0_s_ifspec;

#ifndef __IClusterApplication_INTERFACE_DEFINED__
#define __IClusterApplication_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IClusterApplication
 * at Wed Sep 17 12:03:32 1997
 * using MIDL 3.00.44
 ****************************************/
/* [unique][hidden][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IClusterApplication;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IClusterApplication : public IDispatch
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_DomainNames( 
            /* [retval][out] */ DomainNames __RPC_FAR *__RPC_FAR *ppDomains) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ClusterNames( 
            /* [in] */ BSTR bstrDomainName,
            /* [retval][out] */ ClusterNames __RPC_FAR *__RPC_FAR *ppClusters) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OpenCluster( 
            /* [in] */ BSTR bstrClusterName,
            /* [retval][out] */ ICluster __RPC_FAR *__RPC_FAR *pCluster) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IClusterApplicationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IClusterApplication __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IClusterApplication __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IClusterApplication __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IClusterApplication __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IClusterApplication __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IClusterApplication __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IClusterApplication __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DomainNames )( 
            IClusterApplication __RPC_FAR * This,
            /* [retval][out] */ DomainNames __RPC_FAR *__RPC_FAR *ppDomains);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ClusterNames )( 
            IClusterApplication __RPC_FAR * This,
            /* [in] */ BSTR bstrDomainName,
            /* [retval][out] */ ClusterNames __RPC_FAR *__RPC_FAR *ppClusters);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenCluster )( 
            IClusterApplication __RPC_FAR * This,
            /* [in] */ BSTR bstrClusterName,
            /* [retval][out] */ ICluster __RPC_FAR *__RPC_FAR *pCluster);
        
        END_INTERFACE
    } IClusterApplicationVtbl;

    interface IClusterApplication
    {
        CONST_VTBL struct IClusterApplicationVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IClusterApplication_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IClusterApplication_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IClusterApplication_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IClusterApplication_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IClusterApplication_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IClusterApplication_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IClusterApplication_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IClusterApplication_get_DomainNames(This,ppDomains)	\
    (This)->lpVtbl -> get_DomainNames(This,ppDomains)

#define IClusterApplication_get_ClusterNames(This,bstrDomainName,ppClusters)	\
    (This)->lpVtbl -> get_ClusterNames(This,bstrDomainName,ppClusters)

#define IClusterApplication_OpenCluster(This,bstrClusterName,pCluster)	\
    (This)->lpVtbl -> OpenCluster(This,bstrClusterName,pCluster)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IClusterApplication_get_DomainNames_Proxy( 
    IClusterApplication __RPC_FAR * This,
    /* [retval][out] */ DomainNames __RPC_FAR *__RPC_FAR *ppDomains);


void __RPC_STUB IClusterApplication_get_DomainNames_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IClusterApplication_get_ClusterNames_Proxy( 
    IClusterApplication __RPC_FAR * This,
    /* [in] */ BSTR bstrDomainName,
    /* [retval][out] */ ClusterNames __RPC_FAR *__RPC_FAR *ppClusters);


void __RPC_STUB IClusterApplication_get_ClusterNames_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IClusterApplication_OpenCluster_Proxy( 
    IClusterApplication __RPC_FAR * This,
    /* [in] */ BSTR bstrClusterName,
    /* [retval][out] */ ICluster __RPC_FAR *__RPC_FAR *pCluster);


void __RPC_STUB IClusterApplication_OpenCluster_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IClusterApplication_INTERFACE_DEFINED__ */


#ifndef __ClusObjCollection_INTERFACE_DEFINED__
#define __ClusObjCollection_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ClusObjCollection
 * at Wed Sep 17 12:03:32 1997
 * using MIDL 3.00.44
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ClusObjCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface ClusObjCollection : public IDispatch
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ LONG __RPC_FAR *pnCount) = 0;
        
        virtual /* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ClusObjCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ClusObjCollection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ClusObjCollection __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ClusObjCollection __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ClusObjCollection __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ClusObjCollection __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ClusObjCollection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ClusObjCollection __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ClusObjCollection __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pnCount);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ClusObjCollection __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            ClusObjCollection __RPC_FAR * This);
        
        END_INTERFACE
    } ClusObjCollectionVtbl;

    interface ClusObjCollection
    {
        CONST_VTBL struct ClusObjCollectionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ClusObjCollection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ClusObjCollection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ClusObjCollection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ClusObjCollection_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ClusObjCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ClusObjCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ClusObjCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ClusObjCollection_get_Count(This,pnCount)	\
    (This)->lpVtbl -> get_Count(This,pnCount)

#define ClusObjCollection_get__NewEnum(This,retval)	\
    (This)->lpVtbl -> get__NewEnum(This,retval)

#define ClusObjCollection_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE ClusObjCollection_get_Count_Proxy( 
    ClusObjCollection __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pnCount);


void __RPC_STUB ClusObjCollection_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE ClusObjCollection_get__NewEnum_Proxy( 
    ClusObjCollection __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval);


void __RPC_STUB ClusObjCollection_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ClusObjCollection_Refresh_Proxy( 
    ClusObjCollection __RPC_FAR * This);


void __RPC_STUB ClusObjCollection_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ClusObjCollection_INTERFACE_DEFINED__ */


#ifndef __DomainNames_INTERFACE_DEFINED__
#define __DomainNames_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: DomainNames
 * at Wed Sep 17 12:03:32 1997
 * using MIDL 3.00.44
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_DomainNames;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DomainNames : public ClusObjCollection
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ LONG nIndex,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrDomainName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct DomainNamesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            DomainNames __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            DomainNames __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            DomainNames __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            DomainNames __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            DomainNames __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            DomainNames __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            DomainNames __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            DomainNames __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pnCount);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            DomainNames __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            DomainNames __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            DomainNames __RPC_FAR * This,
            /* [in] */ LONG nIndex,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrDomainName);
        
        END_INTERFACE
    } DomainNamesVtbl;

    interface DomainNames
    {
        CONST_VTBL struct DomainNamesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define DomainNames_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define DomainNames_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define DomainNames_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define DomainNames_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define DomainNames_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define DomainNames_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define DomainNames_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define DomainNames_get_Count(This,pnCount)	\
    (This)->lpVtbl -> get_Count(This,pnCount)

#define DomainNames_get__NewEnum(This,retval)	\
    (This)->lpVtbl -> get__NewEnum(This,retval)

#define DomainNames_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)


#define DomainNames_get_Item(This,nIndex,pbstrDomainName)	\
    (This)->lpVtbl -> get_Item(This,nIndex,pbstrDomainName)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE DomainNames_get_Item_Proxy( 
    DomainNames __RPC_FAR * This,
    /* [in] */ LONG nIndex,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrDomainName);


void __RPC_STUB DomainNames_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __DomainNames_INTERFACE_DEFINED__ */


#ifndef __ClusterNames_INTERFACE_DEFINED__
#define __ClusterNames_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ClusterNames
 * at Wed Sep 17 12:03:32 1997
 * using MIDL 3.00.44
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ClusterNames;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface ClusterNames : public ClusObjCollection
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ LONG nIndex,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrClusterName) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_DomainName( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrDomainName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ClusterNamesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ClusterNames __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ClusterNames __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ClusterNames __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ClusterNames __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ClusterNames __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ClusterNames __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ClusterNames __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ClusterNames __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pnCount);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ClusterNames __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            ClusterNames __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ClusterNames __RPC_FAR * This,
            /* [in] */ LONG nIndex,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrClusterName);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DomainName )( 
            ClusterNames __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrDomainName);
        
        END_INTERFACE
    } ClusterNamesVtbl;

    interface ClusterNames
    {
        CONST_VTBL struct ClusterNamesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ClusterNames_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ClusterNames_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ClusterNames_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ClusterNames_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ClusterNames_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ClusterNames_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ClusterNames_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ClusterNames_get_Count(This,pnCount)	\
    (This)->lpVtbl -> get_Count(This,pnCount)

#define ClusterNames_get__NewEnum(This,retval)	\
    (This)->lpVtbl -> get__NewEnum(This,retval)

#define ClusterNames_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)


#define ClusterNames_get_Item(This,nIndex,pbstrClusterName)	\
    (This)->lpVtbl -> get_Item(This,nIndex,pbstrClusterName)

#define ClusterNames_get_DomainName(This,pbstrDomainName)	\
    (This)->lpVtbl -> get_DomainName(This,pbstrDomainName)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ClusterNames_get_Item_Proxy( 
    ClusterNames __RPC_FAR * This,
    /* [in] */ LONG nIndex,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrClusterName);


void __RPC_STUB ClusterNames_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ClusterNames_get_DomainName_Proxy( 
    ClusterNames __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrDomainName);


void __RPC_STUB ClusterNames_get_DomainName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ClusterNames_INTERFACE_DEFINED__ */


#ifndef __ClusRefObject_INTERFACE_DEFINED__
#define __ClusRefObject_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ClusRefObject
 * at Wed Sep 17 12:03:32 1997
 * using MIDL 3.00.44
 ****************************************/
/* [unique][hidden][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ClusRefObject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface ClusRefObject : public IDispatch
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Handle( 
            /* [retval][out] */ LONG __RPC_FAR *phandle) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ClusRefObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ClusRefObject __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ClusRefObject __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ClusRefObject __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ClusRefObject __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ClusRefObject __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ClusRefObject __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ClusRefObject __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Handle )( 
            ClusRefObject __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *phandle);
        
        END_INTERFACE
    } ClusRefObjectVtbl;

    interface ClusRefObject
    {
        CONST_VTBL struct ClusRefObjectVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ClusRefObject_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ClusRefObject_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ClusRefObject_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ClusRefObject_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ClusRefObject_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ClusRefObject_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ClusRefObject_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ClusRefObject_get_Handle(This,phandle)	\
    (This)->lpVtbl -> get_Handle(This,phandle)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE ClusRefObject_get_Handle_Proxy( 
    ClusRefObject __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *phandle);


void __RPC_STUB ClusRefObject_get_Handle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ClusRefObject_INTERFACE_DEFINED__ */


#ifndef __ClusObj_INTERFACE_DEFINED__
#define __ClusObj_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ClusObj
 * at Wed Sep 17 12:03:32 1997
 * using MIDL 3.00.44
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ClusObj;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface ClusObj : public IDispatch
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CommonProperties( 
            /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_PrivateProperties( 
            /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CommonROProperties( 
            /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_PrivateROProperties( 
            /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ClusObjVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ClusObj __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ClusObj __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ClusObj __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ClusObj __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ClusObj __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ClusObj __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ClusObj __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            ClusObj __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CommonProperties )( 
            ClusObj __RPC_FAR * This,
            /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PrivateProperties )( 
            ClusObj __RPC_FAR * This,
            /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CommonROProperties )( 
            ClusObj __RPC_FAR * This,
            /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PrivateROProperties )( 
            ClusObj __RPC_FAR * This,
            /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties);
        
        END_INTERFACE
    } ClusObjVtbl;

    interface ClusObj
    {
        CONST_VTBL struct ClusObjVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ClusObj_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ClusObj_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ClusObj_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ClusObj_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ClusObj_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ClusObj_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ClusObj_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ClusObj_get_Name(This,pbstrName)	\
    (This)->lpVtbl -> get_Name(This,pbstrName)

#define ClusObj_get_CommonProperties(This,ppProperties)	\
    (This)->lpVtbl -> get_CommonProperties(This,ppProperties)

#define ClusObj_get_PrivateProperties(This,ppProperties)	\
    (This)->lpVtbl -> get_PrivateProperties(This,ppProperties)

#define ClusObj_get_CommonROProperties(This,ppProperties)	\
    (This)->lpVtbl -> get_CommonROProperties(This,ppProperties)

#define ClusObj_get_PrivateROProperties(This,ppProperties)	\
    (This)->lpVtbl -> get_PrivateROProperties(This,ppProperties)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE ClusObj_get_Name_Proxy( 
    ClusObj __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrName);


void __RPC_STUB ClusObj_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ClusObj_get_CommonProperties_Proxy( 
    ClusObj __RPC_FAR * This,
    /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties);


void __RPC_STUB ClusObj_get_CommonProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ClusObj_get_PrivateProperties_Proxy( 
    ClusObj __RPC_FAR * This,
    /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties);


void __RPC_STUB ClusObj_get_PrivateProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ClusObj_get_CommonROProperties_Proxy( 
    ClusObj __RPC_FAR * This,
    /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties);


void __RPC_STUB ClusObj_get_CommonROProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ClusObj_get_PrivateROProperties_Proxy( 
    ClusObj __RPC_FAR * This,
    /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties);


void __RPC_STUB ClusObj_get_PrivateROProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ClusObj_INTERFACE_DEFINED__ */


#ifndef __ICluster_INTERFACE_DEFINED__
#define __ICluster_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ICluster
 * at Wed Sep 17 12:03:32 1997
 * using MIDL 3.00.44
 ****************************************/
/* [unique][hidden][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ICluster;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface ICluster : public ClusObj
    {
    public:
        virtual /* [hidden][propget] */ HRESULT STDMETHODCALLTYPE get_Handle( 
            /* [retval][out] */ LONG __RPC_FAR *phandle) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Open( 
            /* [in] */ BSTR bstrClusterName) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR bstrClusterName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetVersion( 
            /* [out] */ BSTR __RPC_FAR *pbstrClusterName,
            /* [out] */ SHORT __RPC_FAR *MajorVersion,
            /* [out] */ SHORT __RPC_FAR *MinorVersion,
            /* [out] */ SHORT __RPC_FAR *BuildNumber,
            /* [out] */ BSTR __RPC_FAR *pbstrVendorId,
            /* [out] */ BSTR __RPC_FAR *pbstrCSDVersion) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_QuorumResource( 
            /* [in] */ ClusResource __RPC_FAR *pClusterResource) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_QuorumResource( 
            /* [retval][out] */ ClusResource __RPC_FAR *__RPC_FAR *pClusterResource) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetQuorumInfo( 
            /* [in] */ BSTR DevicePath,
            /* [in] */ LONG nLogSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetQuorumInfo( 
            /* [out] */ BSTR __RPC_FAR *DevicePath,
            /* [out] */ LONG __RPC_FAR *pLogSize) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Nodes( 
            /* [retval][out] */ ClusNodes __RPC_FAR *__RPC_FAR *ppClusterNodes) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ResourceGroups( 
            /* [retval][out] */ ClusResGroups __RPC_FAR *__RPC_FAR *ppClusterResourceGroups) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Resources( 
            /* [retval][out] */ ClusResources __RPC_FAR *__RPC_FAR *ppClusterResources) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ResourceTypes( 
            /* [retval][out] */ ClusResTypes __RPC_FAR *__RPC_FAR *ppResourceTypes) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Networks( 
            /* [retval][out] */ ClusNetworks __RPC_FAR *__RPC_FAR *ppNetworks) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_NetInterfaces( 
            /* [retval][out] */ ClusNetInterfaces __RPC_FAR *__RPC_FAR *ppNetInterfaces) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IClusterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICluster __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICluster __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICluster __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICluster __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICluster __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICluster __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICluster __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            ICluster __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CommonProperties )( 
            ICluster __RPC_FAR * This,
            /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PrivateProperties )( 
            ICluster __RPC_FAR * This,
            /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CommonROProperties )( 
            ICluster __RPC_FAR * This,
            /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PrivateROProperties )( 
            ICluster __RPC_FAR * This,
            /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties);
        
        /* [hidden][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Handle )( 
            ICluster __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *phandle);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Open )( 
            ICluster __RPC_FAR * This,
            /* [in] */ BSTR bstrClusterName);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            ICluster __RPC_FAR * This,
            /* [in] */ BSTR bstrClusterName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVersion )( 
            ICluster __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pbstrClusterName,
            /* [out] */ SHORT __RPC_FAR *MajorVersion,
            /* [out] */ SHORT __RPC_FAR *MinorVersion,
            /* [out] */ SHORT __RPC_FAR *BuildNumber,
            /* [out] */ BSTR __RPC_FAR *pbstrVendorId,
            /* [out] */ BSTR __RPC_FAR *pbstrCSDVersion);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_QuorumResource )( 
            ICluster __RPC_FAR * This,
            /* [in] */ ClusResource __RPC_FAR *pClusterResource);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_QuorumResource )( 
            ICluster __RPC_FAR * This,
            /* [retval][out] */ ClusResource __RPC_FAR *__RPC_FAR *pClusterResource);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetQuorumInfo )( 
            ICluster __RPC_FAR * This,
            /* [in] */ BSTR DevicePath,
            /* [in] */ LONG nLogSize);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetQuorumInfo )( 
            ICluster __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *DevicePath,
            /* [out] */ LONG __RPC_FAR *pLogSize);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Nodes )( 
            ICluster __RPC_FAR * This,
            /* [retval][out] */ ClusNodes __RPC_FAR *__RPC_FAR *ppClusterNodes);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ResourceGroups )( 
            ICluster __RPC_FAR * This,
            /* [retval][out] */ ClusResGroups __RPC_FAR *__RPC_FAR *ppClusterResourceGroups);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Resources )( 
            ICluster __RPC_FAR * This,
            /* [retval][out] */ ClusResources __RPC_FAR *__RPC_FAR *ppClusterResources);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ResourceTypes )( 
            ICluster __RPC_FAR * This,
            /* [retval][out] */ ClusResTypes __RPC_FAR *__RPC_FAR *ppResourceTypes);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Networks )( 
            ICluster __RPC_FAR * This,
            /* [retval][out] */ ClusNetworks __RPC_FAR *__RPC_FAR *ppNetworks);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NetInterfaces )( 
            ICluster __RPC_FAR * This,
            /* [retval][out] */ ClusNetInterfaces __RPC_FAR *__RPC_FAR *ppNetInterfaces);
        
        END_INTERFACE
    } IClusterVtbl;

    interface ICluster
    {
        CONST_VTBL struct IClusterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICluster_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICluster_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICluster_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICluster_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICluster_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICluster_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICluster_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICluster_get_Name(This,pbstrName)	\
    (This)->lpVtbl -> get_Name(This,pbstrName)

#define ICluster_get_CommonProperties(This,ppProperties)	\
    (This)->lpVtbl -> get_CommonProperties(This,ppProperties)

#define ICluster_get_PrivateProperties(This,ppProperties)	\
    (This)->lpVtbl -> get_PrivateProperties(This,ppProperties)

#define ICluster_get_CommonROProperties(This,ppProperties)	\
    (This)->lpVtbl -> get_CommonROProperties(This,ppProperties)

#define ICluster_get_PrivateROProperties(This,ppProperties)	\
    (This)->lpVtbl -> get_PrivateROProperties(This,ppProperties)


#define ICluster_get_Handle(This,phandle)	\
    (This)->lpVtbl -> get_Handle(This,phandle)

#define ICluster_Open(This,bstrClusterName)	\
    (This)->lpVtbl -> Open(This,bstrClusterName)

#define ICluster_put_Name(This,bstrClusterName)	\
    (This)->lpVtbl -> put_Name(This,bstrClusterName)

#define ICluster_GetVersion(This,pbstrClusterName,MajorVersion,MinorVersion,BuildNumber,pbstrVendorId,pbstrCSDVersion)	\
    (This)->lpVtbl -> GetVersion(This,pbstrClusterName,MajorVersion,MinorVersion,BuildNumber,pbstrVendorId,pbstrCSDVersion)

#define ICluster_put_QuorumResource(This,pClusterResource)	\
    (This)->lpVtbl -> put_QuorumResource(This,pClusterResource)

#define ICluster_get_QuorumResource(This,pClusterResource)	\
    (This)->lpVtbl -> get_QuorumResource(This,pClusterResource)

#define ICluster_SetQuorumInfo(This,DevicePath,nLogSize)	\
    (This)->lpVtbl -> SetQuorumInfo(This,DevicePath,nLogSize)

#define ICluster_GetQuorumInfo(This,DevicePath,pLogSize)	\
    (This)->lpVtbl -> GetQuorumInfo(This,DevicePath,pLogSize)

#define ICluster_get_Nodes(This,ppClusterNodes)	\
    (This)->lpVtbl -> get_Nodes(This,ppClusterNodes)

#define ICluster_get_ResourceGroups(This,ppClusterResourceGroups)	\
    (This)->lpVtbl -> get_ResourceGroups(This,ppClusterResourceGroups)

#define ICluster_get_Resources(This,ppClusterResources)	\
    (This)->lpVtbl -> get_Resources(This,ppClusterResources)

#define ICluster_get_ResourceTypes(This,ppResourceTypes)	\
    (This)->lpVtbl -> get_ResourceTypes(This,ppResourceTypes)

#define ICluster_get_Networks(This,ppNetworks)	\
    (This)->lpVtbl -> get_Networks(This,ppNetworks)

#define ICluster_get_NetInterfaces(This,ppNetInterfaces)	\
    (This)->lpVtbl -> get_NetInterfaces(This,ppNetInterfaces)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [hidden][propget] */ HRESULT STDMETHODCALLTYPE ICluster_get_Handle_Proxy( 
    ICluster __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *phandle);


void __RPC_STUB ICluster_get_Handle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICluster_Open_Proxy( 
    ICluster __RPC_FAR * This,
    /* [in] */ BSTR bstrClusterName);


void __RPC_STUB ICluster_Open_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE ICluster_put_Name_Proxy( 
    ICluster __RPC_FAR * This,
    /* [in] */ BSTR bstrClusterName);


void __RPC_STUB ICluster_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICluster_GetVersion_Proxy( 
    ICluster __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pbstrClusterName,
    /* [out] */ SHORT __RPC_FAR *MajorVersion,
    /* [out] */ SHORT __RPC_FAR *MinorVersion,
    /* [out] */ SHORT __RPC_FAR *BuildNumber,
    /* [out] */ BSTR __RPC_FAR *pbstrVendorId,
    /* [out] */ BSTR __RPC_FAR *pbstrCSDVersion);


void __RPC_STUB ICluster_GetVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE ICluster_put_QuorumResource_Proxy( 
    ICluster __RPC_FAR * This,
    /* [in] */ ClusResource __RPC_FAR *pClusterResource);


void __RPC_STUB ICluster_put_QuorumResource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ICluster_get_QuorumResource_Proxy( 
    ICluster __RPC_FAR * This,
    /* [retval][out] */ ClusResource __RPC_FAR *__RPC_FAR *pClusterResource);


void __RPC_STUB ICluster_get_QuorumResource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICluster_SetQuorumInfo_Proxy( 
    ICluster __RPC_FAR * This,
    /* [in] */ BSTR DevicePath,
    /* [in] */ LONG nLogSize);


void __RPC_STUB ICluster_SetQuorumInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICluster_GetQuorumInfo_Proxy( 
    ICluster __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *DevicePath,
    /* [out] */ LONG __RPC_FAR *pLogSize);


void __RPC_STUB ICluster_GetQuorumInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ICluster_get_Nodes_Proxy( 
    ICluster __RPC_FAR * This,
    /* [retval][out] */ ClusNodes __RPC_FAR *__RPC_FAR *ppClusterNodes);


void __RPC_STUB ICluster_get_Nodes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ICluster_get_ResourceGroups_Proxy( 
    ICluster __RPC_FAR * This,
    /* [retval][out] */ ClusResGroups __RPC_FAR *__RPC_FAR *ppClusterResourceGroups);


void __RPC_STUB ICluster_get_ResourceGroups_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ICluster_get_Resources_Proxy( 
    ICluster __RPC_FAR * This,
    /* [retval][out] */ ClusResources __RPC_FAR *__RPC_FAR *ppClusterResources);


void __RPC_STUB ICluster_get_Resources_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ICluster_get_ResourceTypes_Proxy( 
    ICluster __RPC_FAR * This,
    /* [retval][out] */ ClusResTypes __RPC_FAR *__RPC_FAR *ppResourceTypes);


void __RPC_STUB ICluster_get_ResourceTypes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ICluster_get_Networks_Proxy( 
    ICluster __RPC_FAR * This,
    /* [retval][out] */ ClusNetworks __RPC_FAR *__RPC_FAR *ppNetworks);


void __RPC_STUB ICluster_get_Networks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ICluster_get_NetInterfaces_Proxy( 
    ICluster __RPC_FAR * This,
    /* [retval][out] */ ClusNetInterfaces __RPC_FAR *__RPC_FAR *ppNetInterfaces);


void __RPC_STUB ICluster_get_NetInterfaces_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICluster_INTERFACE_DEFINED__ */


#ifndef __ClusNode_INTERFACE_DEFINED__
#define __ClusNode_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ClusNode
 * at Wed Sep 17 12:03:32 1997
 * using MIDL 3.00.44
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ClusNode;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface ClusNode : public ClusObj
    {
    public:
        virtual /* [hidden][propget] */ HRESULT STDMETHODCALLTYPE get_Handle( 
            /* [retval][out] */ LONG __RPC_FAR *phandle) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_NodeID( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrNodeID) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_State( 
            /* [retval][out] */ CLUSTER_NODE_STATE __RPC_FAR *dwState) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Pause( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Resume( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Evict( void) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ResourceGroups( 
            /* [retval][out] */ ClusResGroups __RPC_FAR *__RPC_FAR *ppResourceGroups) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Cluster( 
            /* [retval][out] */ ICluster __RPC_FAR *__RPC_FAR *ppCluster) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_NetInterfaces( 
            /* [retval][out] */ ClusNodeNetInterfaces __RPC_FAR *__RPC_FAR *ppClusNetInterfaces) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ClusNodeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ClusNode __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ClusNode __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ClusNode __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ClusNode __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ClusNode __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ClusNode __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ClusNode __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            ClusNode __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CommonProperties )( 
            ClusNode __RPC_FAR * This,
            /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PrivateProperties )( 
            ClusNode __RPC_FAR * This,
            /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CommonROProperties )( 
            ClusNode __RPC_FAR * This,
            /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PrivateROProperties )( 
            ClusNode __RPC_FAR * This,
            /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties);
        
        /* [hidden][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Handle )( 
            ClusNode __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *phandle);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NodeID )( 
            ClusNode __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrNodeID);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_State )( 
            ClusNode __RPC_FAR * This,
            /* [retval][out] */ CLUSTER_NODE_STATE __RPC_FAR *dwState);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Pause )( 
            ClusNode __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Resume )( 
            ClusNode __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Evict )( 
            ClusNode __RPC_FAR * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ResourceGroups )( 
            ClusNode __RPC_FAR * This,
            /* [retval][out] */ ClusResGroups __RPC_FAR *__RPC_FAR *ppResourceGroups);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Cluster )( 
            ClusNode __RPC_FAR * This,
            /* [retval][out] */ ICluster __RPC_FAR *__RPC_FAR *ppCluster);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NetInterfaces )( 
            ClusNode __RPC_FAR * This,
            /* [retval][out] */ ClusNodeNetInterfaces __RPC_FAR *__RPC_FAR *ppClusNetInterfaces);
        
        END_INTERFACE
    } ClusNodeVtbl;

    interface ClusNode
    {
        CONST_VTBL struct ClusNodeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ClusNode_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ClusNode_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ClusNode_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ClusNode_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ClusNode_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ClusNode_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ClusNode_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ClusNode_get_Name(This,pbstrName)	\
    (This)->lpVtbl -> get_Name(This,pbstrName)

#define ClusNode_get_CommonProperties(This,ppProperties)	\
    (This)->lpVtbl -> get_CommonProperties(This,ppProperties)

#define ClusNode_get_PrivateProperties(This,ppProperties)	\
    (This)->lpVtbl -> get_PrivateProperties(This,ppProperties)

#define ClusNode_get_CommonROProperties(This,ppProperties)	\
    (This)->lpVtbl -> get_CommonROProperties(This,ppProperties)

#define ClusNode_get_PrivateROProperties(This,ppProperties)	\
    (This)->lpVtbl -> get_PrivateROProperties(This,ppProperties)


#define ClusNode_get_Handle(This,phandle)	\
    (This)->lpVtbl -> get_Handle(This,phandle)

#define ClusNode_get_NodeID(This,pbstrNodeID)	\
    (This)->lpVtbl -> get_NodeID(This,pbstrNodeID)

#define ClusNode_get_State(This,dwState)	\
    (This)->lpVtbl -> get_State(This,dwState)

#define ClusNode_Pause(This)	\
    (This)->lpVtbl -> Pause(This)

#define ClusNode_Resume(This)	\
    (This)->lpVtbl -> Resume(This)

#define ClusNode_Evict(This)	\
    (This)->lpVtbl -> Evict(This)

#define ClusNode_get_ResourceGroups(This,ppResourceGroups)	\
    (This)->lpVtbl -> get_ResourceGroups(This,ppResourceGroups)

#define ClusNode_get_Cluster(This,ppCluster)	\
    (This)->lpVtbl -> get_Cluster(This,ppCluster)

#define ClusNode_get_NetInterfaces(This,ppClusNetInterfaces)	\
    (This)->lpVtbl -> get_NetInterfaces(This,ppClusNetInterfaces)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [hidden][propget] */ HRESULT STDMETHODCALLTYPE ClusNode_get_Handle_Proxy( 
    ClusNode __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *phandle);


void __RPC_STUB ClusNode_get_Handle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ClusNode_get_NodeID_Proxy( 
    ClusNode __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrNodeID);


void __RPC_STUB ClusNode_get_NodeID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ClusNode_get_State_Proxy( 
    ClusNode __RPC_FAR * This,
    /* [retval][out] */ CLUSTER_NODE_STATE __RPC_FAR *dwState);


void __RPC_STUB ClusNode_get_State_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ClusNode_Pause_Proxy( 
    ClusNode __RPC_FAR * This);


void __RPC_STUB ClusNode_Pause_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ClusNode_Resume_Proxy( 
    ClusNode __RPC_FAR * This);


void __RPC_STUB ClusNode_Resume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ClusNode_Evict_Proxy( 
    ClusNode __RPC_FAR * This);


void __RPC_STUB ClusNode_Evict_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ClusNode_get_ResourceGroups_Proxy( 
    ClusNode __RPC_FAR * This,
    /* [retval][out] */ ClusResGroups __RPC_FAR *__RPC_FAR *ppResourceGroups);


void __RPC_STUB ClusNode_get_ResourceGroups_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ClusNode_get_Cluster_Proxy( 
    ClusNode __RPC_FAR * This,
    /* [retval][out] */ ICluster __RPC_FAR *__RPC_FAR *ppCluster);


void __RPC_STUB ClusNode_get_Cluster_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ClusNode_get_NetInterfaces_Proxy( 
    ClusNode __RPC_FAR * This,
    /* [retval][out] */ ClusNodeNetInterfaces __RPC_FAR *__RPC_FAR *ppClusNetInterfaces);


void __RPC_STUB ClusNode_get_NetInterfaces_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ClusNode_INTERFACE_DEFINED__ */


#ifndef __ClusNodes_INTERFACE_DEFINED__
#define __ClusNodes_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ClusNodes
 * at Wed Sep 17 12:03:32 1997
 * using MIDL 3.00.44
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ClusNodes;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface ClusNodes : public ClusObjCollection
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT varIndex,
            /* [retval][out] */ ClusNode __RPC_FAR *__RPC_FAR *ppClusNode) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ClusNodesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ClusNodes __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ClusNodes __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ClusNodes __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ClusNodes __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ClusNodes __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ClusNodes __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ClusNodes __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ClusNodes __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pnCount);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ClusNodes __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            ClusNodes __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ClusNodes __RPC_FAR * This,
            /* [in] */ VARIANT varIndex,
            /* [retval][out] */ ClusNode __RPC_FAR *__RPC_FAR *ppClusNode);
        
        END_INTERFACE
    } ClusNodesVtbl;

    interface ClusNodes
    {
        CONST_VTBL struct ClusNodesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ClusNodes_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ClusNodes_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ClusNodes_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ClusNodes_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ClusNodes_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ClusNodes_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ClusNodes_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ClusNodes_get_Count(This,pnCount)	\
    (This)->lpVtbl -> get_Count(This,pnCount)

#define ClusNodes_get__NewEnum(This,retval)	\
    (This)->lpVtbl -> get__NewEnum(This,retval)

#define ClusNodes_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)


#define ClusNodes_get_Item(This,varIndex,ppClusNode)	\
    (This)->lpVtbl -> get_Item(This,varIndex,ppClusNode)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ClusNodes_get_Item_Proxy( 
    ClusNodes __RPC_FAR * This,
    /* [in] */ VARIANT varIndex,
    /* [retval][out] */ ClusNode __RPC_FAR *__RPC_FAR *ppClusNode);


void __RPC_STUB ClusNodes_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ClusNodes_INTERFACE_DEFINED__ */


#ifndef __ClusNetwork_INTERFACE_DEFINED__
#define __ClusNetwork_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ClusNetwork
 * at Wed Sep 17 12:03:32 1997
 * using MIDL 3.00.44
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ClusNetwork;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface ClusNetwork : public ClusObj
    {
    public:
        virtual /* [hidden][propget] */ HRESULT STDMETHODCALLTYPE get_Handle( 
            /* [retval][out] */ LONG __RPC_FAR *phandle) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR bstrNetworkName) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_NetworkID( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrNetworkID) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_State( 
            /* [retval][out] */ CLUSTER_NETWORK_STATE __RPC_FAR *dwState) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_NetInterfaces( 
            /* [retval][out] */ ClusNetworkNetInterfaces __RPC_FAR *__RPC_FAR *ppClusNetInterfaces) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Cluster( 
            /* [retval][out] */ ICluster __RPC_FAR *__RPC_FAR *ppCluster) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ClusNetworkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ClusNetwork __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ClusNetwork __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ClusNetwork __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ClusNetwork __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ClusNetwork __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ClusNetwork __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ClusNetwork __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            ClusNetwork __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CommonProperties )( 
            ClusNetwork __RPC_FAR * This,
            /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PrivateProperties )( 
            ClusNetwork __RPC_FAR * This,
            /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CommonROProperties )( 
            ClusNetwork __RPC_FAR * This,
            /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PrivateROProperties )( 
            ClusNetwork __RPC_FAR * This,
            /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties);
        
        /* [hidden][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Handle )( 
            ClusNetwork __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *phandle);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            ClusNetwork __RPC_FAR * This,
            /* [in] */ BSTR bstrNetworkName);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NetworkID )( 
            ClusNetwork __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrNetworkID);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_State )( 
            ClusNetwork __RPC_FAR * This,
            /* [retval][out] */ CLUSTER_NETWORK_STATE __RPC_FAR *dwState);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NetInterfaces )( 
            ClusNetwork __RPC_FAR * This,
            /* [retval][out] */ ClusNetworkNetInterfaces __RPC_FAR *__RPC_FAR *ppClusNetInterfaces);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Cluster )( 
            ClusNetwork __RPC_FAR * This,
            /* [retval][out] */ ICluster __RPC_FAR *__RPC_FAR *ppCluster);
        
        END_INTERFACE
    } ClusNetworkVtbl;

    interface ClusNetwork
    {
        CONST_VTBL struct ClusNetworkVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ClusNetwork_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ClusNetwork_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ClusNetwork_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ClusNetwork_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ClusNetwork_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ClusNetwork_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ClusNetwork_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ClusNetwork_get_Name(This,pbstrName)	\
    (This)->lpVtbl -> get_Name(This,pbstrName)

#define ClusNetwork_get_CommonProperties(This,ppProperties)	\
    (This)->lpVtbl -> get_CommonProperties(This,ppProperties)

#define ClusNetwork_get_PrivateProperties(This,ppProperties)	\
    (This)->lpVtbl -> get_PrivateProperties(This,ppProperties)

#define ClusNetwork_get_CommonROProperties(This,ppProperties)	\
    (This)->lpVtbl -> get_CommonROProperties(This,ppProperties)

#define ClusNetwork_get_PrivateROProperties(This,ppProperties)	\
    (This)->lpVtbl -> get_PrivateROProperties(This,ppProperties)


#define ClusNetwork_get_Handle(This,phandle)	\
    (This)->lpVtbl -> get_Handle(This,phandle)

#define ClusNetwork_put_Name(This,bstrNetworkName)	\
    (This)->lpVtbl -> put_Name(This,bstrNetworkName)

#define ClusNetwork_get_NetworkID(This,pbstrNetworkID)	\
    (This)->lpVtbl -> get_NetworkID(This,pbstrNetworkID)

#define ClusNetwork_get_State(This,dwState)	\
    (This)->lpVtbl -> get_State(This,dwState)

#define ClusNetwork_get_NetInterfaces(This,ppClusNetInterfaces)	\
    (This)->lpVtbl -> get_NetInterfaces(This,ppClusNetInterfaces)

#define ClusNetwork_get_Cluster(This,ppCluster)	\
    (This)->lpVtbl -> get_Cluster(This,ppCluster)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [hidden][propget] */ HRESULT STDMETHODCALLTYPE ClusNetwork_get_Handle_Proxy( 
    ClusNetwork __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *phandle);


void __RPC_STUB ClusNetwork_get_Handle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE ClusNetwork_put_Name_Proxy( 
    ClusNetwork __RPC_FAR * This,
    /* [in] */ BSTR bstrNetworkName);


void __RPC_STUB ClusNetwork_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ClusNetwork_get_NetworkID_Proxy( 
    ClusNetwork __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrNetworkID);


void __RPC_STUB ClusNetwork_get_NetworkID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ClusNetwork_get_State_Proxy( 
    ClusNetwork __RPC_FAR * This,
    /* [retval][out] */ CLUSTER_NETWORK_STATE __RPC_FAR *dwState);


void __RPC_STUB ClusNetwork_get_State_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ClusNetwork_get_NetInterfaces_Proxy( 
    ClusNetwork __RPC_FAR * This,
    /* [retval][out] */ ClusNetworkNetInterfaces __RPC_FAR *__RPC_FAR *ppClusNetInterfaces);


void __RPC_STUB ClusNetwork_get_NetInterfaces_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ClusNetwork_get_Cluster_Proxy( 
    ClusNetwork __RPC_FAR * This,
    /* [retval][out] */ ICluster __RPC_FAR *__RPC_FAR *ppCluster);


void __RPC_STUB ClusNetwork_get_Cluster_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ClusNetwork_INTERFACE_DEFINED__ */


#ifndef __ClusNetworks_INTERFACE_DEFINED__
#define __ClusNetworks_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ClusNetworks
 * at Wed Sep 17 12:03:32 1997
 * using MIDL 3.00.44
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ClusNetworks;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface ClusNetworks : public ClusObjCollection
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT varIndex,
            /* [retval][out] */ ClusNetwork __RPC_FAR *__RPC_FAR *ppClusNetwork) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ClusNetworksVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ClusNetworks __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ClusNetworks __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ClusNetworks __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ClusNetworks __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ClusNetworks __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ClusNetworks __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ClusNetworks __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ClusNetworks __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pnCount);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ClusNetworks __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            ClusNetworks __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ClusNetworks __RPC_FAR * This,
            /* [in] */ VARIANT varIndex,
            /* [retval][out] */ ClusNetwork __RPC_FAR *__RPC_FAR *ppClusNetwork);
        
        END_INTERFACE
    } ClusNetworksVtbl;

    interface ClusNetworks
    {
        CONST_VTBL struct ClusNetworksVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ClusNetworks_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ClusNetworks_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ClusNetworks_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ClusNetworks_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ClusNetworks_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ClusNetworks_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ClusNetworks_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ClusNetworks_get_Count(This,pnCount)	\
    (This)->lpVtbl -> get_Count(This,pnCount)

#define ClusNetworks_get__NewEnum(This,retval)	\
    (This)->lpVtbl -> get__NewEnum(This,retval)

#define ClusNetworks_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)


#define ClusNetworks_get_Item(This,varIndex,ppClusNetwork)	\
    (This)->lpVtbl -> get_Item(This,varIndex,ppClusNetwork)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ClusNetworks_get_Item_Proxy( 
    ClusNetworks __RPC_FAR * This,
    /* [in] */ VARIANT varIndex,
    /* [retval][out] */ ClusNetwork __RPC_FAR *__RPC_FAR *ppClusNetwork);


void __RPC_STUB ClusNetworks_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ClusNetworks_INTERFACE_DEFINED__ */


#ifndef __ClusNetInterface_INTERFACE_DEFINED__
#define __ClusNetInterface_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ClusNetInterface
 * at Wed Sep 17 12:03:32 1997
 * using MIDL 3.00.44
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ClusNetInterface;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface ClusNetInterface : public ClusObj
    {
    public:
        virtual /* [hidden][propget] */ HRESULT STDMETHODCALLTYPE get_Handle( 
            /* [retval][out] */ LONG __RPC_FAR *phandle) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_State( 
            /* [retval][out] */ CLUSTER_NETINTERFACE_STATE __RPC_FAR *dwState) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Cluster( 
            /* [retval][out] */ ICluster __RPC_FAR *__RPC_FAR *ppCluster) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ClusNetInterfaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ClusNetInterface __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ClusNetInterface __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ClusNetInterface __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ClusNetInterface __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ClusNetInterface __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ClusNetInterface __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ClusNetInterface __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            ClusNetInterface __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CommonProperties )( 
            ClusNetInterface __RPC_FAR * This,
            /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PrivateProperties )( 
            ClusNetInterface __RPC_FAR * This,
            /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CommonROProperties )( 
            ClusNetInterface __RPC_FAR * This,
            /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PrivateROProperties )( 
            ClusNetInterface __RPC_FAR * This,
            /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties);
        
        /* [hidden][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Handle )( 
            ClusNetInterface __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *phandle);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_State )( 
            ClusNetInterface __RPC_FAR * This,
            /* [retval][out] */ CLUSTER_NETINTERFACE_STATE __RPC_FAR *dwState);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Cluster )( 
            ClusNetInterface __RPC_FAR * This,
            /* [retval][out] */ ICluster __RPC_FAR *__RPC_FAR *ppCluster);
        
        END_INTERFACE
    } ClusNetInterfaceVtbl;

    interface ClusNetInterface
    {
        CONST_VTBL struct ClusNetInterfaceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ClusNetInterface_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ClusNetInterface_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ClusNetInterface_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ClusNetInterface_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ClusNetInterface_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ClusNetInterface_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ClusNetInterface_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ClusNetInterface_get_Name(This,pbstrName)	\
    (This)->lpVtbl -> get_Name(This,pbstrName)

#define ClusNetInterface_get_CommonProperties(This,ppProperties)	\
    (This)->lpVtbl -> get_CommonProperties(This,ppProperties)

#define ClusNetInterface_get_PrivateProperties(This,ppProperties)	\
    (This)->lpVtbl -> get_PrivateProperties(This,ppProperties)

#define ClusNetInterface_get_CommonROProperties(This,ppProperties)	\
    (This)->lpVtbl -> get_CommonROProperties(This,ppProperties)

#define ClusNetInterface_get_PrivateROProperties(This,ppProperties)	\
    (This)->lpVtbl -> get_PrivateROProperties(This,ppProperties)


#define ClusNetInterface_get_Handle(This,phandle)	\
    (This)->lpVtbl -> get_Handle(This,phandle)

#define ClusNetInterface_get_State(This,dwState)	\
    (This)->lpVtbl -> get_State(This,dwState)

#define ClusNetInterface_get_Cluster(This,ppCluster)	\
    (This)->lpVtbl -> get_Cluster(This,ppCluster)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [hidden][propget] */ HRESULT STDMETHODCALLTYPE ClusNetInterface_get_Handle_Proxy( 
    ClusNetInterface __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *phandle);


void __RPC_STUB ClusNetInterface_get_Handle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ClusNetInterface_get_State_Proxy( 
    ClusNetInterface __RPC_FAR * This,
    /* [retval][out] */ CLUSTER_NETINTERFACE_STATE __RPC_FAR *dwState);


void __RPC_STUB ClusNetInterface_get_State_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ClusNetInterface_get_Cluster_Proxy( 
    ClusNetInterface __RPC_FAR * This,
    /* [retval][out] */ ICluster __RPC_FAR *__RPC_FAR *ppCluster);


void __RPC_STUB ClusNetInterface_get_Cluster_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ClusNetInterface_INTERFACE_DEFINED__ */


#ifndef __ClusNetInterfaces_INTERFACE_DEFINED__
#define __ClusNetInterfaces_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ClusNetInterfaces
 * at Wed Sep 17 12:03:32 1997
 * using MIDL 3.00.44
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ClusNetInterfaces;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface ClusNetInterfaces : public ClusObjCollection
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT varIndex,
            /* [retval][out] */ ClusNetInterface __RPC_FAR *__RPC_FAR *ppClusNetInterface) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ClusNetInterfacesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ClusNetInterfaces __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ClusNetInterfaces __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ClusNetInterfaces __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ClusNetInterfaces __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ClusNetInterfaces __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ClusNetInterfaces __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ClusNetInterfaces __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ClusNetInterfaces __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pnCount);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ClusNetInterfaces __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            ClusNetInterfaces __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ClusNetInterfaces __RPC_FAR * This,
            /* [in] */ VARIANT varIndex,
            /* [retval][out] */ ClusNetInterface __RPC_FAR *__RPC_FAR *ppClusNetInterface);
        
        END_INTERFACE
    } ClusNetInterfacesVtbl;

    interface ClusNetInterfaces
    {
        CONST_VTBL struct ClusNetInterfacesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ClusNetInterfaces_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ClusNetInterfaces_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ClusNetInterfaces_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ClusNetInterfaces_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ClusNetInterfaces_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ClusNetInterfaces_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ClusNetInterfaces_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ClusNetInterfaces_get_Count(This,pnCount)	\
    (This)->lpVtbl -> get_Count(This,pnCount)

#define ClusNetInterfaces_get__NewEnum(This,retval)	\
    (This)->lpVtbl -> get__NewEnum(This,retval)

#define ClusNetInterfaces_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)


#define ClusNetInterfaces_get_Item(This,varIndex,ppClusNetInterface)	\
    (This)->lpVtbl -> get_Item(This,varIndex,ppClusNetInterface)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ClusNetInterfaces_get_Item_Proxy( 
    ClusNetInterfaces __RPC_FAR * This,
    /* [in] */ VARIANT varIndex,
    /* [retval][out] */ ClusNetInterface __RPC_FAR *__RPC_FAR *ppClusNetInterface);


void __RPC_STUB ClusNetInterfaces_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ClusNetInterfaces_INTERFACE_DEFINED__ */


#ifndef __ClusNodeNetInterfaces_INTERFACE_DEFINED__
#define __ClusNodeNetInterfaces_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ClusNodeNetInterfaces
 * at Wed Sep 17 12:03:32 1997
 * using MIDL 3.00.44
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ClusNodeNetInterfaces;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface ClusNodeNetInterfaces : public ClusObjCollection
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT varIndex,
            /* [retval][out] */ ClusNetInterface __RPC_FAR *__RPC_FAR *ppClusNetInterface) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ClusNodeNetInterfacesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ClusNodeNetInterfaces __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ClusNodeNetInterfaces __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ClusNodeNetInterfaces __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ClusNodeNetInterfaces __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ClusNodeNetInterfaces __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ClusNodeNetInterfaces __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ClusNodeNetInterfaces __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ClusNodeNetInterfaces __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pnCount);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ClusNodeNetInterfaces __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            ClusNodeNetInterfaces __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ClusNodeNetInterfaces __RPC_FAR * This,
            /* [in] */ VARIANT varIndex,
            /* [retval][out] */ ClusNetInterface __RPC_FAR *__RPC_FAR *ppClusNetInterface);
        
        END_INTERFACE
    } ClusNodeNetInterfacesVtbl;

    interface ClusNodeNetInterfaces
    {
        CONST_VTBL struct ClusNodeNetInterfacesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ClusNodeNetInterfaces_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ClusNodeNetInterfaces_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ClusNodeNetInterfaces_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ClusNodeNetInterfaces_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ClusNodeNetInterfaces_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ClusNodeNetInterfaces_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ClusNodeNetInterfaces_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ClusNodeNetInterfaces_get_Count(This,pnCount)	\
    (This)->lpVtbl -> get_Count(This,pnCount)

#define ClusNodeNetInterfaces_get__NewEnum(This,retval)	\
    (This)->lpVtbl -> get__NewEnum(This,retval)

#define ClusNodeNetInterfaces_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)


#define ClusNodeNetInterfaces_get_Item(This,varIndex,ppClusNetInterface)	\
    (This)->lpVtbl -> get_Item(This,varIndex,ppClusNetInterface)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ClusNodeNetInterfaces_get_Item_Proxy( 
    ClusNodeNetInterfaces __RPC_FAR * This,
    /* [in] */ VARIANT varIndex,
    /* [retval][out] */ ClusNetInterface __RPC_FAR *__RPC_FAR *ppClusNetInterface);


void __RPC_STUB ClusNodeNetInterfaces_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ClusNodeNetInterfaces_INTERFACE_DEFINED__ */


#ifndef __ClusNetworkNetInterfaces_INTERFACE_DEFINED__
#define __ClusNetworkNetInterfaces_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ClusNetworkNetInterfaces
 * at Wed Sep 17 12:03:32 1997
 * using MIDL 3.00.44
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ClusNetworkNetInterfaces;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface ClusNetworkNetInterfaces : public ClusObjCollection
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT varIndex,
            /* [retval][out] */ ClusNetInterface __RPC_FAR *__RPC_FAR *ppClusNetInterface) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ClusNetworkNetInterfacesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ClusNetworkNetInterfaces __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ClusNetworkNetInterfaces __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ClusNetworkNetInterfaces __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ClusNetworkNetInterfaces __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ClusNetworkNetInterfaces __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ClusNetworkNetInterfaces __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ClusNetworkNetInterfaces __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ClusNetworkNetInterfaces __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pnCount);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ClusNetworkNetInterfaces __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            ClusNetworkNetInterfaces __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ClusNetworkNetInterfaces __RPC_FAR * This,
            /* [in] */ VARIANT varIndex,
            /* [retval][out] */ ClusNetInterface __RPC_FAR *__RPC_FAR *ppClusNetInterface);
        
        END_INTERFACE
    } ClusNetworkNetInterfacesVtbl;

    interface ClusNetworkNetInterfaces
    {
        CONST_VTBL struct ClusNetworkNetInterfacesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ClusNetworkNetInterfaces_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ClusNetworkNetInterfaces_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ClusNetworkNetInterfaces_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ClusNetworkNetInterfaces_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ClusNetworkNetInterfaces_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ClusNetworkNetInterfaces_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ClusNetworkNetInterfaces_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ClusNetworkNetInterfaces_get_Count(This,pnCount)	\
    (This)->lpVtbl -> get_Count(This,pnCount)

#define ClusNetworkNetInterfaces_get__NewEnum(This,retval)	\
    (This)->lpVtbl -> get__NewEnum(This,retval)

#define ClusNetworkNetInterfaces_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)


#define ClusNetworkNetInterfaces_get_Item(This,varIndex,ppClusNetInterface)	\
    (This)->lpVtbl -> get_Item(This,varIndex,ppClusNetInterface)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ClusNetworkNetInterfaces_get_Item_Proxy( 
    ClusNetworkNetInterfaces __RPC_FAR * This,
    /* [in] */ VARIANT varIndex,
    /* [retval][out] */ ClusNetInterface __RPC_FAR *__RPC_FAR *ppClusNetInterface);


void __RPC_STUB ClusNetworkNetInterfaces_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ClusNetworkNetInterfaces_INTERFACE_DEFINED__ */


#ifndef __ClusResGroup_INTERFACE_DEFINED__
#define __ClusResGroup_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ClusResGroup
 * at Wed Sep 17 12:03:32 1997
 * using MIDL 3.00.44
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ClusResGroup;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface ClusResGroup : public ClusObj
    {
    public:
        virtual /* [hidden][propget] */ HRESULT STDMETHODCALLTYPE get_Handle( 
            /* [retval][out] */ LONG __RPC_FAR *phandle) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR bstrGroupName) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_State( 
            /* [retval][out] */ CLUSTER_GROUP_STATE __RPC_FAR *dwState) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_OwnerNode( 
            /* [retval][out] */ ClusNode __RPC_FAR *__RPC_FAR *ppOwnerNode) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Resources( 
            /* [retval][out] */ ClusGroupResources __RPC_FAR *__RPC_FAR *ppClusterGroupResources) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_PreferredOwnerNodes( 
            /* [retval][out] */ ClusGroupOwners __RPC_FAR *__RPC_FAR *ppOwnerNodes) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPreferredOwnerNodes( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Delete( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Online( 
            /* [in] */ LONG nTimeout,
            /* [optional][in] */ ClusNode __RPC_FAR *pDestinationNode,
            /* [retval][out] */ LONG __RPC_FAR *bPending) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Move( 
            /* [in] */ LONG nTimeout,
            /* [optional][in] */ ClusNode __RPC_FAR *pDestinationNode,
            /* [retval][out] */ LONG __RPC_FAR *bPending) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Offline( 
            /* [in] */ LONG nTimeout,
            /* [retval][out] */ LONG __RPC_FAR *bPending) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Cluster( 
            /* [retval][out] */ ICluster __RPC_FAR *__RPC_FAR *ppCluster) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ClusResGroupVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ClusResGroup __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ClusResGroup __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ClusResGroup __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ClusResGroup __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ClusResGroup __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ClusResGroup __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ClusResGroup __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            ClusResGroup __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CommonProperties )( 
            ClusResGroup __RPC_FAR * This,
            /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PrivateProperties )( 
            ClusResGroup __RPC_FAR * This,
            /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CommonROProperties )( 
            ClusResGroup __RPC_FAR * This,
            /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PrivateROProperties )( 
            ClusResGroup __RPC_FAR * This,
            /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties);
        
        /* [hidden][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Handle )( 
            ClusResGroup __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *phandle);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            ClusResGroup __RPC_FAR * This,
            /* [in] */ BSTR bstrGroupName);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_State )( 
            ClusResGroup __RPC_FAR * This,
            /* [retval][out] */ CLUSTER_GROUP_STATE __RPC_FAR *dwState);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OwnerNode )( 
            ClusResGroup __RPC_FAR * This,
            /* [retval][out] */ ClusNode __RPC_FAR *__RPC_FAR *ppOwnerNode);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Resources )( 
            ClusResGroup __RPC_FAR * This,
            /* [retval][out] */ ClusGroupResources __RPC_FAR *__RPC_FAR *ppClusterGroupResources);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PreferredOwnerNodes )( 
            ClusResGroup __RPC_FAR * This,
            /* [retval][out] */ ClusGroupOwners __RPC_FAR *__RPC_FAR *ppOwnerNodes);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPreferredOwnerNodes )( 
            ClusResGroup __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            ClusResGroup __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Online )( 
            ClusResGroup __RPC_FAR * This,
            /* [in] */ LONG nTimeout,
            /* [optional][in] */ ClusNode __RPC_FAR *pDestinationNode,
            /* [retval][out] */ LONG __RPC_FAR *bPending);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Move )( 
            ClusResGroup __RPC_FAR * This,
            /* [in] */ LONG nTimeout,
            /* [optional][in] */ ClusNode __RPC_FAR *pDestinationNode,
            /* [retval][out] */ LONG __RPC_FAR *bPending);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Offline )( 
            ClusResGroup __RPC_FAR * This,
            /* [in] */ LONG nTimeout,
            /* [retval][out] */ LONG __RPC_FAR *bPending);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Cluster )( 
            ClusResGroup __RPC_FAR * This,
            /* [retval][out] */ ICluster __RPC_FAR *__RPC_FAR *ppCluster);
        
        END_INTERFACE
    } ClusResGroupVtbl;

    interface ClusResGroup
    {
        CONST_VTBL struct ClusResGroupVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ClusResGroup_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ClusResGroup_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ClusResGroup_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ClusResGroup_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ClusResGroup_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ClusResGroup_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ClusResGroup_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ClusResGroup_get_Name(This,pbstrName)	\
    (This)->lpVtbl -> get_Name(This,pbstrName)

#define ClusResGroup_get_CommonProperties(This,ppProperties)	\
    (This)->lpVtbl -> get_CommonProperties(This,ppProperties)

#define ClusResGroup_get_PrivateProperties(This,ppProperties)	\
    (This)->lpVtbl -> get_PrivateProperties(This,ppProperties)

#define ClusResGroup_get_CommonROProperties(This,ppProperties)	\
    (This)->lpVtbl -> get_CommonROProperties(This,ppProperties)

#define ClusResGroup_get_PrivateROProperties(This,ppProperties)	\
    (This)->lpVtbl -> get_PrivateROProperties(This,ppProperties)


#define ClusResGroup_get_Handle(This,phandle)	\
    (This)->lpVtbl -> get_Handle(This,phandle)

#define ClusResGroup_put_Name(This,bstrGroupName)	\
    (This)->lpVtbl -> put_Name(This,bstrGroupName)

#define ClusResGroup_get_State(This,dwState)	\
    (This)->lpVtbl -> get_State(This,dwState)

#define ClusResGroup_get_OwnerNode(This,ppOwnerNode)	\
    (This)->lpVtbl -> get_OwnerNode(This,ppOwnerNode)

#define ClusResGroup_get_Resources(This,ppClusterGroupResources)	\
    (This)->lpVtbl -> get_Resources(This,ppClusterGroupResources)

#define ClusResGroup_get_PreferredOwnerNodes(This,ppOwnerNodes)	\
    (This)->lpVtbl -> get_PreferredOwnerNodes(This,ppOwnerNodes)

#define ClusResGroup_SetPreferredOwnerNodes(This)	\
    (This)->lpVtbl -> SetPreferredOwnerNodes(This)

#define ClusResGroup_Delete(This)	\
    (This)->lpVtbl -> Delete(This)

#define ClusResGroup_Online(This,nTimeout,pDestinationNode,bPending)	\
    (This)->lpVtbl -> Online(This,nTimeout,pDestinationNode,bPending)

#define ClusResGroup_Move(This,nTimeout,pDestinationNode,bPending)	\
    (This)->lpVtbl -> Move(This,nTimeout,pDestinationNode,bPending)

#define ClusResGroup_Offline(This,nTimeout,bPending)	\
    (This)->lpVtbl -> Offline(This,nTimeout,bPending)

#define ClusResGroup_get_Cluster(This,ppCluster)	\
    (This)->lpVtbl -> get_Cluster(This,ppCluster)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [hidden][propget] */ HRESULT STDMETHODCALLTYPE ClusResGroup_get_Handle_Proxy( 
    ClusResGroup __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *phandle);


void __RPC_STUB ClusResGroup_get_Handle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE ClusResGroup_put_Name_Proxy( 
    ClusResGroup __RPC_FAR * This,
    /* [in] */ BSTR bstrGroupName);


void __RPC_STUB ClusResGroup_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ClusResGroup_get_State_Proxy( 
    ClusResGroup __RPC_FAR * This,
    /* [retval][out] */ CLUSTER_GROUP_STATE __RPC_FAR *dwState);


void __RPC_STUB ClusResGroup_get_State_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ClusResGroup_get_OwnerNode_Proxy( 
    ClusResGroup __RPC_FAR * This,
    /* [retval][out] */ ClusNode __RPC_FAR *__RPC_FAR *ppOwnerNode);


void __RPC_STUB ClusResGroup_get_OwnerNode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ClusResGroup_get_Resources_Proxy( 
    ClusResGroup __RPC_FAR * This,
    /* [retval][out] */ ClusGroupResources __RPC_FAR *__RPC_FAR *ppClusterGroupResources);


void __RPC_STUB ClusResGroup_get_Resources_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ClusResGroup_get_PreferredOwnerNodes_Proxy( 
    ClusResGroup __RPC_FAR * This,
    /* [retval][out] */ ClusGroupOwners __RPC_FAR *__RPC_FAR *ppOwnerNodes);


void __RPC_STUB ClusResGroup_get_PreferredOwnerNodes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ClusResGroup_SetPreferredOwnerNodes_Proxy( 
    ClusResGroup __RPC_FAR * This);


void __RPC_STUB ClusResGroup_SetPreferredOwnerNodes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ClusResGroup_Delete_Proxy( 
    ClusResGroup __RPC_FAR * This);


void __RPC_STUB ClusResGroup_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ClusResGroup_Online_Proxy( 
    ClusResGroup __RPC_FAR * This,
    /* [in] */ LONG nTimeout,
    /* [optional][in] */ ClusNode __RPC_FAR *pDestinationNode,
    /* [retval][out] */ LONG __RPC_FAR *bPending);


void __RPC_STUB ClusResGroup_Online_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ClusResGroup_Move_Proxy( 
    ClusResGroup __RPC_FAR * This,
    /* [in] */ LONG nTimeout,
    /* [optional][in] */ ClusNode __RPC_FAR *pDestinationNode,
    /* [retval][out] */ LONG __RPC_FAR *bPending);


void __RPC_STUB ClusResGroup_Move_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ClusResGroup_Offline_Proxy( 
    ClusResGroup __RPC_FAR * This,
    /* [in] */ LONG nTimeout,
    /* [retval][out] */ LONG __RPC_FAR *bPending);


void __RPC_STUB ClusResGroup_Offline_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ClusResGroup_get_Cluster_Proxy( 
    ClusResGroup __RPC_FAR * This,
    /* [retval][out] */ ICluster __RPC_FAR *__RPC_FAR *ppCluster);


void __RPC_STUB ClusResGroup_get_Cluster_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ClusResGroup_INTERFACE_DEFINED__ */


#ifndef __ClusResGroups_INTERFACE_DEFINED__
#define __ClusResGroups_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ClusResGroups
 * at Wed Sep 17 12:03:32 1997
 * using MIDL 3.00.44
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ClusResGroups;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface ClusResGroups : public ClusObjCollection
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT varIndex,
            /* [retval][out] */ ClusResGroup __RPC_FAR *__RPC_FAR *ppClusResGroup) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateItem( 
            /* [in] */ BSTR bstrResourceGroupName,
            /* [retval][out] */ ClusResGroup __RPC_FAR *__RPC_FAR *ppResourceGroup) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeleteItem( 
            /* [in] */ VARIANT varIndex) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ClusResGroupsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ClusResGroups __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ClusResGroups __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ClusResGroups __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ClusResGroups __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ClusResGroups __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ClusResGroups __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ClusResGroups __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ClusResGroups __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pnCount);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ClusResGroups __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            ClusResGroups __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ClusResGroups __RPC_FAR * This,
            /* [in] */ VARIANT varIndex,
            /* [retval][out] */ ClusResGroup __RPC_FAR *__RPC_FAR *ppClusResGroup);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateItem )( 
            ClusResGroups __RPC_FAR * This,
            /* [in] */ BSTR bstrResourceGroupName,
            /* [retval][out] */ ClusResGroup __RPC_FAR *__RPC_FAR *ppResourceGroup);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteItem )( 
            ClusResGroups __RPC_FAR * This,
            /* [in] */ VARIANT varIndex);
        
        END_INTERFACE
    } ClusResGroupsVtbl;

    interface ClusResGroups
    {
        CONST_VTBL struct ClusResGroupsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ClusResGroups_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ClusResGroups_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ClusResGroups_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ClusResGroups_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ClusResGroups_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ClusResGroups_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ClusResGroups_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ClusResGroups_get_Count(This,pnCount)	\
    (This)->lpVtbl -> get_Count(This,pnCount)

#define ClusResGroups_get__NewEnum(This,retval)	\
    (This)->lpVtbl -> get__NewEnum(This,retval)

#define ClusResGroups_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)


#define ClusResGroups_get_Item(This,varIndex,ppClusResGroup)	\
    (This)->lpVtbl -> get_Item(This,varIndex,ppClusResGroup)

#define ClusResGroups_CreateItem(This,bstrResourceGroupName,ppResourceGroup)	\
    (This)->lpVtbl -> CreateItem(This,bstrResourceGroupName,ppResourceGroup)

#define ClusResGroups_DeleteItem(This,varIndex)	\
    (This)->lpVtbl -> DeleteItem(This,varIndex)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ClusResGroups_get_Item_Proxy( 
    ClusResGroups __RPC_FAR * This,
    /* [in] */ VARIANT varIndex,
    /* [retval][out] */ ClusResGroup __RPC_FAR *__RPC_FAR *ppClusResGroup);


void __RPC_STUB ClusResGroups_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ClusResGroups_CreateItem_Proxy( 
    ClusResGroups __RPC_FAR * This,
    /* [in] */ BSTR bstrResourceGroupName,
    /* [retval][out] */ ClusResGroup __RPC_FAR *__RPC_FAR *ppResourceGroup);


void __RPC_STUB ClusResGroups_CreateItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ClusResGroups_DeleteItem_Proxy( 
    ClusResGroups __RPC_FAR * This,
    /* [in] */ VARIANT varIndex);


void __RPC_STUB ClusResGroups_DeleteItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ClusResGroups_INTERFACE_DEFINED__ */


#ifndef __ClusResource_INTERFACE_DEFINED__
#define __ClusResource_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ClusResource
 * at Wed Sep 17 12:03:32 1997
 * using MIDL 3.00.44
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ClusResource;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface ClusResource : public ClusObj
    {
    public:
        virtual /* [hidden][propget] */ HRESULT STDMETHODCALLTYPE get_Handle( 
            /* [retval][out] */ LONG __RPC_FAR *phandle) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR bstrResourceName) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_State( 
            /* [retval][out] */ CLUSTER_RESOURCE_STATE __RPC_FAR *dwState) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE BecomeQuorumResource( 
            /* [in] */ BSTR bstrDevicePath,
            /* [in] */ LONG lMaxLogSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Delete( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Fail( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Online( 
            LONG nTimeout,
            LONG __RPC_FAR *bPending) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Offline( 
            LONG nTimeout,
            LONG __RPC_FAR *bPending) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ChangeResourceGroup( 
            /* [in] */ ClusResGroup __RPC_FAR *pResourceGroup) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddResourceNode( 
            /* [in] */ ClusNode __RPC_FAR *pNode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RemoveResourceNode( 
            /* [in] */ ClusNode __RPC_FAR *pNode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CanResourceBeDependent( 
            /* [in] */ ClusResource __RPC_FAR *pResource,
            /* [retval][out] */ BOOL __RPC_FAR *bDependent) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_PossibleOwnerNodes( 
            /* [retval][out] */ ClusResOwners __RPC_FAR *__RPC_FAR *ppNodes) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Dependencies( 
            /* [retval][out] */ ClusResDependencies __RPC_FAR *__RPC_FAR *ppResDependencies) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Group( 
            /* [retval][out] */ ClusResGroup __RPC_FAR *__RPC_FAR *ppResGroup) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_OwnerNode( 
            /* [retval][out] */ ClusNode __RPC_FAR *__RPC_FAR *ppNode) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Cluster( 
            /* [retval][out] */ ICluster __RPC_FAR *__RPC_FAR *ppCluster) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ClusResourceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ClusResource __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ClusResource __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ClusResource __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ClusResource __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ClusResource __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ClusResource __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ClusResource __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            ClusResource __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CommonProperties )( 
            ClusResource __RPC_FAR * This,
            /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PrivateProperties )( 
            ClusResource __RPC_FAR * This,
            /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CommonROProperties )( 
            ClusResource __RPC_FAR * This,
            /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PrivateROProperties )( 
            ClusResource __RPC_FAR * This,
            /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties);
        
        /* [hidden][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Handle )( 
            ClusResource __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *phandle);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            ClusResource __RPC_FAR * This,
            /* [in] */ BSTR bstrResourceName);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_State )( 
            ClusResource __RPC_FAR * This,
            /* [retval][out] */ CLUSTER_RESOURCE_STATE __RPC_FAR *dwState);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BecomeQuorumResource )( 
            ClusResource __RPC_FAR * This,
            /* [in] */ BSTR bstrDevicePath,
            /* [in] */ LONG lMaxLogSize);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            ClusResource __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Fail )( 
            ClusResource __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Online )( 
            ClusResource __RPC_FAR * This,
            LONG nTimeout,
            LONG __RPC_FAR *bPending);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Offline )( 
            ClusResource __RPC_FAR * This,
            LONG nTimeout,
            LONG __RPC_FAR *bPending);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ChangeResourceGroup )( 
            ClusResource __RPC_FAR * This,
            /* [in] */ ClusResGroup __RPC_FAR *pResourceGroup);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddResourceNode )( 
            ClusResource __RPC_FAR * This,
            /* [in] */ ClusNode __RPC_FAR *pNode);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveResourceNode )( 
            ClusResource __RPC_FAR * This,
            /* [in] */ ClusNode __RPC_FAR *pNode);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CanResourceBeDependent )( 
            ClusResource __RPC_FAR * This,
            /* [in] */ ClusResource __RPC_FAR *pResource,
            /* [retval][out] */ BOOL __RPC_FAR *bDependent);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PossibleOwnerNodes )( 
            ClusResource __RPC_FAR * This,
            /* [retval][out] */ ClusResOwners __RPC_FAR *__RPC_FAR *ppNodes);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Dependencies )( 
            ClusResource __RPC_FAR * This,
            /* [retval][out] */ ClusResDependencies __RPC_FAR *__RPC_FAR *ppResDependencies);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Group )( 
            ClusResource __RPC_FAR * This,
            /* [retval][out] */ ClusResGroup __RPC_FAR *__RPC_FAR *ppResGroup);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OwnerNode )( 
            ClusResource __RPC_FAR * This,
            /* [retval][out] */ ClusNode __RPC_FAR *__RPC_FAR *ppNode);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Cluster )( 
            ClusResource __RPC_FAR * This,
            /* [retval][out] */ ICluster __RPC_FAR *__RPC_FAR *ppCluster);
        
        END_INTERFACE
    } ClusResourceVtbl;

    interface ClusResource
    {
        CONST_VTBL struct ClusResourceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ClusResource_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ClusResource_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ClusResource_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ClusResource_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ClusResource_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ClusResource_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ClusResource_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ClusResource_get_Name(This,pbstrName)	\
    (This)->lpVtbl -> get_Name(This,pbstrName)

#define ClusResource_get_CommonProperties(This,ppProperties)	\
    (This)->lpVtbl -> get_CommonProperties(This,ppProperties)

#define ClusResource_get_PrivateProperties(This,ppProperties)	\
    (This)->lpVtbl -> get_PrivateProperties(This,ppProperties)

#define ClusResource_get_CommonROProperties(This,ppProperties)	\
    (This)->lpVtbl -> get_CommonROProperties(This,ppProperties)

#define ClusResource_get_PrivateROProperties(This,ppProperties)	\
    (This)->lpVtbl -> get_PrivateROProperties(This,ppProperties)


#define ClusResource_get_Handle(This,phandle)	\
    (This)->lpVtbl -> get_Handle(This,phandle)

#define ClusResource_put_Name(This,bstrResourceName)	\
    (This)->lpVtbl -> put_Name(This,bstrResourceName)

#define ClusResource_get_State(This,dwState)	\
    (This)->lpVtbl -> get_State(This,dwState)

#define ClusResource_BecomeQuorumResource(This,bstrDevicePath,lMaxLogSize)	\
    (This)->lpVtbl -> BecomeQuorumResource(This,bstrDevicePath,lMaxLogSize)

#define ClusResource_Delete(This)	\
    (This)->lpVtbl -> Delete(This)

#define ClusResource_Fail(This)	\
    (This)->lpVtbl -> Fail(This)

#define ClusResource_Online(This,nTimeout,bPending)	\
    (This)->lpVtbl -> Online(This,nTimeout,bPending)

#define ClusResource_Offline(This,nTimeout,bPending)	\
    (This)->lpVtbl -> Offline(This,nTimeout,bPending)

#define ClusResource_ChangeResourceGroup(This,pResourceGroup)	\
    (This)->lpVtbl -> ChangeResourceGroup(This,pResourceGroup)

#define ClusResource_AddResourceNode(This,pNode)	\
    (This)->lpVtbl -> AddResourceNode(This,pNode)

#define ClusResource_RemoveResourceNode(This,pNode)	\
    (This)->lpVtbl -> RemoveResourceNode(This,pNode)

#define ClusResource_CanResourceBeDependent(This,pResource,bDependent)	\
    (This)->lpVtbl -> CanResourceBeDependent(This,pResource,bDependent)

#define ClusResource_get_PossibleOwnerNodes(This,ppNodes)	\
    (This)->lpVtbl -> get_PossibleOwnerNodes(This,ppNodes)

#define ClusResource_get_Dependencies(This,ppResDependencies)	\
    (This)->lpVtbl -> get_Dependencies(This,ppResDependencies)

#define ClusResource_get_Group(This,ppResGroup)	\
    (This)->lpVtbl -> get_Group(This,ppResGroup)

#define ClusResource_get_OwnerNode(This,ppNode)	\
    (This)->lpVtbl -> get_OwnerNode(This,ppNode)

#define ClusResource_get_Cluster(This,ppCluster)	\
    (This)->lpVtbl -> get_Cluster(This,ppCluster)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [hidden][propget] */ HRESULT STDMETHODCALLTYPE ClusResource_get_Handle_Proxy( 
    ClusResource __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *phandle);


void __RPC_STUB ClusResource_get_Handle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE ClusResource_put_Name_Proxy( 
    ClusResource __RPC_FAR * This,
    /* [in] */ BSTR bstrResourceName);


void __RPC_STUB ClusResource_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ClusResource_get_State_Proxy( 
    ClusResource __RPC_FAR * This,
    /* [retval][out] */ CLUSTER_RESOURCE_STATE __RPC_FAR *dwState);


void __RPC_STUB ClusResource_get_State_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ClusResource_BecomeQuorumResource_Proxy( 
    ClusResource __RPC_FAR * This,
    /* [in] */ BSTR bstrDevicePath,
    /* [in] */ LONG lMaxLogSize);


void __RPC_STUB ClusResource_BecomeQuorumResource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ClusResource_Delete_Proxy( 
    ClusResource __RPC_FAR * This);


void __RPC_STUB ClusResource_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ClusResource_Fail_Proxy( 
    ClusResource __RPC_FAR * This);


void __RPC_STUB ClusResource_Fail_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ClusResource_Online_Proxy( 
    ClusResource __RPC_FAR * This,
    LONG nTimeout,
    LONG __RPC_FAR *bPending);


void __RPC_STUB ClusResource_Online_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ClusResource_Offline_Proxy( 
    ClusResource __RPC_FAR * This,
    LONG nTimeout,
    LONG __RPC_FAR *bPending);


void __RPC_STUB ClusResource_Offline_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ClusResource_ChangeResourceGroup_Proxy( 
    ClusResource __RPC_FAR * This,
    /* [in] */ ClusResGroup __RPC_FAR *pResourceGroup);


void __RPC_STUB ClusResource_ChangeResourceGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ClusResource_AddResourceNode_Proxy( 
    ClusResource __RPC_FAR * This,
    /* [in] */ ClusNode __RPC_FAR *pNode);


void __RPC_STUB ClusResource_AddResourceNode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ClusResource_RemoveResourceNode_Proxy( 
    ClusResource __RPC_FAR * This,
    /* [in] */ ClusNode __RPC_FAR *pNode);


void __RPC_STUB ClusResource_RemoveResourceNode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ClusResource_CanResourceBeDependent_Proxy( 
    ClusResource __RPC_FAR * This,
    /* [in] */ ClusResource __RPC_FAR *pResource,
    /* [retval][out] */ BOOL __RPC_FAR *bDependent);


void __RPC_STUB ClusResource_CanResourceBeDependent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ClusResource_get_PossibleOwnerNodes_Proxy( 
    ClusResource __RPC_FAR * This,
    /* [retval][out] */ ClusResOwners __RPC_FAR *__RPC_FAR *ppNodes);


void __RPC_STUB ClusResource_get_PossibleOwnerNodes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ClusResource_get_Dependencies_Proxy( 
    ClusResource __RPC_FAR * This,
    /* [retval][out] */ ClusResDependencies __RPC_FAR *__RPC_FAR *ppResDependencies);


void __RPC_STUB ClusResource_get_Dependencies_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ClusResource_get_Group_Proxy( 
    ClusResource __RPC_FAR * This,
    /* [retval][out] */ ClusResGroup __RPC_FAR *__RPC_FAR *ppResGroup);


void __RPC_STUB ClusResource_get_Group_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ClusResource_get_OwnerNode_Proxy( 
    ClusResource __RPC_FAR * This,
    /* [retval][out] */ ClusNode __RPC_FAR *__RPC_FAR *ppNode);


void __RPC_STUB ClusResource_get_OwnerNode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ClusResource_get_Cluster_Proxy( 
    ClusResource __RPC_FAR * This,
    /* [retval][out] */ ICluster __RPC_FAR *__RPC_FAR *ppCluster);


void __RPC_STUB ClusResource_get_Cluster_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ClusResource_INTERFACE_DEFINED__ */


#ifndef __ClusResDependencies_INTERFACE_DEFINED__
#define __ClusResDependencies_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ClusResDependencies
 * at Wed Sep 17 12:03:32 1997
 * using MIDL 3.00.44
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ClusResDependencies;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface ClusResDependencies : public ClusObjCollection
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT varIndex,
            /* [retval][out] */ ClusResource __RPC_FAR *__RPC_FAR *ppClusResource) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateItem( 
            /* [in] */ BSTR bstrResourceName,
            /* [in] */ BSTR bstrResourceType,
            /* [in] */ BSTR bstrGroupName,
            /* [in] */ CLUSTER_RESOURCE_CREATE_FLAGS dwFlags,
            /* [retval][out] */ ClusResource __RPC_FAR *__RPC_FAR *ppClusterResource) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeleteItem( 
            /* [in] */ VARIANT varIndex) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddItem( 
            /* [in] */ ClusResource __RPC_FAR *pResource) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RemoveItem( 
            /* [in] */ VARIANT varIndex) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ClusResDependenciesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ClusResDependencies __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ClusResDependencies __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ClusResDependencies __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ClusResDependencies __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ClusResDependencies __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ClusResDependencies __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ClusResDependencies __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ClusResDependencies __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pnCount);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ClusResDependencies __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            ClusResDependencies __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ClusResDependencies __RPC_FAR * This,
            /* [in] */ VARIANT varIndex,
            /* [retval][out] */ ClusResource __RPC_FAR *__RPC_FAR *ppClusResource);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateItem )( 
            ClusResDependencies __RPC_FAR * This,
            /* [in] */ BSTR bstrResourceName,
            /* [in] */ BSTR bstrResourceType,
            /* [in] */ BSTR bstrGroupName,
            /* [in] */ CLUSTER_RESOURCE_CREATE_FLAGS dwFlags,
            /* [retval][out] */ ClusResource __RPC_FAR *__RPC_FAR *ppClusterResource);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteItem )( 
            ClusResDependencies __RPC_FAR * This,
            /* [in] */ VARIANT varIndex);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddItem )( 
            ClusResDependencies __RPC_FAR * This,
            /* [in] */ ClusResource __RPC_FAR *pResource);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveItem )( 
            ClusResDependencies __RPC_FAR * This,
            /* [in] */ VARIANT varIndex);
        
        END_INTERFACE
    } ClusResDependenciesVtbl;

    interface ClusResDependencies
    {
        CONST_VTBL struct ClusResDependenciesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ClusResDependencies_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ClusResDependencies_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ClusResDependencies_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ClusResDependencies_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ClusResDependencies_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ClusResDependencies_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ClusResDependencies_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ClusResDependencies_get_Count(This,pnCount)	\
    (This)->lpVtbl -> get_Count(This,pnCount)

#define ClusResDependencies_get__NewEnum(This,retval)	\
    (This)->lpVtbl -> get__NewEnum(This,retval)

#define ClusResDependencies_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)


#define ClusResDependencies_get_Item(This,varIndex,ppClusResource)	\
    (This)->lpVtbl -> get_Item(This,varIndex,ppClusResource)

#define ClusResDependencies_CreateItem(This,bstrResourceName,bstrResourceType,bstrGroupName,dwFlags,ppClusterResource)	\
    (This)->lpVtbl -> CreateItem(This,bstrResourceName,bstrResourceType,bstrGroupName,dwFlags,ppClusterResource)

#define ClusResDependencies_DeleteItem(This,varIndex)	\
    (This)->lpVtbl -> DeleteItem(This,varIndex)

#define ClusResDependencies_AddItem(This,pResource)	\
    (This)->lpVtbl -> AddItem(This,pResource)

#define ClusResDependencies_RemoveItem(This,varIndex)	\
    (This)->lpVtbl -> RemoveItem(This,varIndex)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ClusResDependencies_get_Item_Proxy( 
    ClusResDependencies __RPC_FAR * This,
    /* [in] */ VARIANT varIndex,
    /* [retval][out] */ ClusResource __RPC_FAR *__RPC_FAR *ppClusResource);


void __RPC_STUB ClusResDependencies_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ClusResDependencies_CreateItem_Proxy( 
    ClusResDependencies __RPC_FAR * This,
    /* [in] */ BSTR bstrResourceName,
    /* [in] */ BSTR bstrResourceType,
    /* [in] */ BSTR bstrGroupName,
    /* [in] */ CLUSTER_RESOURCE_CREATE_FLAGS dwFlags,
    /* [retval][out] */ ClusResource __RPC_FAR *__RPC_FAR *ppClusterResource);


void __RPC_STUB ClusResDependencies_CreateItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ClusResDependencies_DeleteItem_Proxy( 
    ClusResDependencies __RPC_FAR * This,
    /* [in] */ VARIANT varIndex);


void __RPC_STUB ClusResDependencies_DeleteItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ClusResDependencies_AddItem_Proxy( 
    ClusResDependencies __RPC_FAR * This,
    /* [in] */ ClusResource __RPC_FAR *pResource);


void __RPC_STUB ClusResDependencies_AddItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ClusResDependencies_RemoveItem_Proxy( 
    ClusResDependencies __RPC_FAR * This,
    /* [in] */ VARIANT varIndex);


void __RPC_STUB ClusResDependencies_RemoveItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ClusResDependencies_INTERFACE_DEFINED__ */


#ifndef __ClusGroupResources_INTERFACE_DEFINED__
#define __ClusGroupResources_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ClusGroupResources
 * at Wed Sep 17 12:03:32 1997
 * using MIDL 3.00.44
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ClusGroupResources;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface ClusGroupResources : public ClusObjCollection
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT varIndex,
            /* [retval][out] */ ClusResource __RPC_FAR *__RPC_FAR *ppClusResource) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateItem( 
            /* [in] */ BSTR bstrResourceName,
            /* [in] */ BSTR bstrResourceType,
            /* [in] */ CLUSTER_RESOURCE_CREATE_FLAGS dwFlags,
            /* [retval][out] */ ClusResource __RPC_FAR *__RPC_FAR *ppClusterResource) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeleteItem( 
            /* [in] */ VARIANT varIndex) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ClusGroupResourcesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ClusGroupResources __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ClusGroupResources __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ClusGroupResources __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ClusGroupResources __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ClusGroupResources __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ClusGroupResources __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ClusGroupResources __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ClusGroupResources __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pnCount);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ClusGroupResources __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            ClusGroupResources __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ClusGroupResources __RPC_FAR * This,
            /* [in] */ VARIANT varIndex,
            /* [retval][out] */ ClusResource __RPC_FAR *__RPC_FAR *ppClusResource);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateItem )( 
            ClusGroupResources __RPC_FAR * This,
            /* [in] */ BSTR bstrResourceName,
            /* [in] */ BSTR bstrResourceType,
            /* [in] */ CLUSTER_RESOURCE_CREATE_FLAGS dwFlags,
            /* [retval][out] */ ClusResource __RPC_FAR *__RPC_FAR *ppClusterResource);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteItem )( 
            ClusGroupResources __RPC_FAR * This,
            /* [in] */ VARIANT varIndex);
        
        END_INTERFACE
    } ClusGroupResourcesVtbl;

    interface ClusGroupResources
    {
        CONST_VTBL struct ClusGroupResourcesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ClusGroupResources_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ClusGroupResources_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ClusGroupResources_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ClusGroupResources_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ClusGroupResources_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ClusGroupResources_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ClusGroupResources_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ClusGroupResources_get_Count(This,pnCount)	\
    (This)->lpVtbl -> get_Count(This,pnCount)

#define ClusGroupResources_get__NewEnum(This,retval)	\
    (This)->lpVtbl -> get__NewEnum(This,retval)

#define ClusGroupResources_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)


#define ClusGroupResources_get_Item(This,varIndex,ppClusResource)	\
    (This)->lpVtbl -> get_Item(This,varIndex,ppClusResource)

#define ClusGroupResources_CreateItem(This,bstrResourceName,bstrResourceType,dwFlags,ppClusterResource)	\
    (This)->lpVtbl -> CreateItem(This,bstrResourceName,bstrResourceType,dwFlags,ppClusterResource)

#define ClusGroupResources_DeleteItem(This,varIndex)	\
    (This)->lpVtbl -> DeleteItem(This,varIndex)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ClusGroupResources_get_Item_Proxy( 
    ClusGroupResources __RPC_FAR * This,
    /* [in] */ VARIANT varIndex,
    /* [retval][out] */ ClusResource __RPC_FAR *__RPC_FAR *ppClusResource);


void __RPC_STUB ClusGroupResources_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ClusGroupResources_CreateItem_Proxy( 
    ClusGroupResources __RPC_FAR * This,
    /* [in] */ BSTR bstrResourceName,
    /* [in] */ BSTR bstrResourceType,
    /* [in] */ CLUSTER_RESOURCE_CREATE_FLAGS dwFlags,
    /* [retval][out] */ ClusResource __RPC_FAR *__RPC_FAR *ppClusterResource);


void __RPC_STUB ClusGroupResources_CreateItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ClusGroupResources_DeleteItem_Proxy( 
    ClusGroupResources __RPC_FAR * This,
    /* [in] */ VARIANT varIndex);


void __RPC_STUB ClusGroupResources_DeleteItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ClusGroupResources_INTERFACE_DEFINED__ */


#ifndef __ClusResTypeResources_INTERFACE_DEFINED__
#define __ClusResTypeResources_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ClusResTypeResources
 * at Wed Sep 17 12:03:32 1997
 * using MIDL 3.00.44
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ClusResTypeResources;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface ClusResTypeResources : public ClusObjCollection
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT varIndex,
            /* [retval][out] */ ClusResource __RPC_FAR *__RPC_FAR *ppClusResource) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateItem( 
            /* [in] */ BSTR bstrResourceName,
            /* [in] */ BSTR bstrGroupName,
            /* [in] */ CLUSTER_RESOURCE_CREATE_FLAGS dwFlags,
            /* [retval][out] */ ClusResource __RPC_FAR *__RPC_FAR *ppClusterResource) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeleteItem( 
            /* [in] */ VARIANT varIndex) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ClusResTypeResourcesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ClusResTypeResources __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ClusResTypeResources __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ClusResTypeResources __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ClusResTypeResources __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ClusResTypeResources __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ClusResTypeResources __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ClusResTypeResources __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ClusResTypeResources __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pnCount);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ClusResTypeResources __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            ClusResTypeResources __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ClusResTypeResources __RPC_FAR * This,
            /* [in] */ VARIANT varIndex,
            /* [retval][out] */ ClusResource __RPC_FAR *__RPC_FAR *ppClusResource);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateItem )( 
            ClusResTypeResources __RPC_FAR * This,
            /* [in] */ BSTR bstrResourceName,
            /* [in] */ BSTR bstrGroupName,
            /* [in] */ CLUSTER_RESOURCE_CREATE_FLAGS dwFlags,
            /* [retval][out] */ ClusResource __RPC_FAR *__RPC_FAR *ppClusterResource);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteItem )( 
            ClusResTypeResources __RPC_FAR * This,
            /* [in] */ VARIANT varIndex);
        
        END_INTERFACE
    } ClusResTypeResourcesVtbl;

    interface ClusResTypeResources
    {
        CONST_VTBL struct ClusResTypeResourcesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ClusResTypeResources_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ClusResTypeResources_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ClusResTypeResources_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ClusResTypeResources_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ClusResTypeResources_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ClusResTypeResources_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ClusResTypeResources_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ClusResTypeResources_get_Count(This,pnCount)	\
    (This)->lpVtbl -> get_Count(This,pnCount)

#define ClusResTypeResources_get__NewEnum(This,retval)	\
    (This)->lpVtbl -> get__NewEnum(This,retval)

#define ClusResTypeResources_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)


#define ClusResTypeResources_get_Item(This,varIndex,ppClusResource)	\
    (This)->lpVtbl -> get_Item(This,varIndex,ppClusResource)

#define ClusResTypeResources_CreateItem(This,bstrResourceName,bstrGroupName,dwFlags,ppClusterResource)	\
    (This)->lpVtbl -> CreateItem(This,bstrResourceName,bstrGroupName,dwFlags,ppClusterResource)

#define ClusResTypeResources_DeleteItem(This,varIndex)	\
    (This)->lpVtbl -> DeleteItem(This,varIndex)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ClusResTypeResources_get_Item_Proxy( 
    ClusResTypeResources __RPC_FAR * This,
    /* [in] */ VARIANT varIndex,
    /* [retval][out] */ ClusResource __RPC_FAR *__RPC_FAR *ppClusResource);


void __RPC_STUB ClusResTypeResources_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ClusResTypeResources_CreateItem_Proxy( 
    ClusResTypeResources __RPC_FAR * This,
    /* [in] */ BSTR bstrResourceName,
    /* [in] */ BSTR bstrGroupName,
    /* [in] */ CLUSTER_RESOURCE_CREATE_FLAGS dwFlags,
    /* [retval][out] */ ClusResource __RPC_FAR *__RPC_FAR *ppClusterResource);


void __RPC_STUB ClusResTypeResources_CreateItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ClusResTypeResources_DeleteItem_Proxy( 
    ClusResTypeResources __RPC_FAR * This,
    /* [in] */ VARIANT varIndex);


void __RPC_STUB ClusResTypeResources_DeleteItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ClusResTypeResources_INTERFACE_DEFINED__ */


#ifndef __ClusResources_INTERFACE_DEFINED__
#define __ClusResources_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ClusResources
 * at Wed Sep 17 12:03:32 1997
 * using MIDL 3.00.44
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ClusResources;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface ClusResources : public ClusObjCollection
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT varIndex,
            /* [retval][out] */ ClusResource __RPC_FAR *__RPC_FAR *ppClusResource) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateItem( 
            /* [in] */ BSTR bstrResourceName,
            /* [in] */ BSTR bstrResourceType,
            /* [in] */ BSTR bstrGroupName,
            /* [in] */ CLUSTER_RESOURCE_CREATE_FLAGS dwFlags,
            /* [retval][out] */ ClusResource __RPC_FAR *__RPC_FAR *ppClusterResource) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeleteItem( 
            /* [in] */ VARIANT varIndex) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ClusResourcesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ClusResources __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ClusResources __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ClusResources __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ClusResources __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ClusResources __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ClusResources __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ClusResources __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ClusResources __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pnCount);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ClusResources __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            ClusResources __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ClusResources __RPC_FAR * This,
            /* [in] */ VARIANT varIndex,
            /* [retval][out] */ ClusResource __RPC_FAR *__RPC_FAR *ppClusResource);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateItem )( 
            ClusResources __RPC_FAR * This,
            /* [in] */ BSTR bstrResourceName,
            /* [in] */ BSTR bstrResourceType,
            /* [in] */ BSTR bstrGroupName,
            /* [in] */ CLUSTER_RESOURCE_CREATE_FLAGS dwFlags,
            /* [retval][out] */ ClusResource __RPC_FAR *__RPC_FAR *ppClusterResource);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteItem )( 
            ClusResources __RPC_FAR * This,
            /* [in] */ VARIANT varIndex);
        
        END_INTERFACE
    } ClusResourcesVtbl;

    interface ClusResources
    {
        CONST_VTBL struct ClusResourcesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ClusResources_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ClusResources_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ClusResources_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ClusResources_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ClusResources_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ClusResources_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ClusResources_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ClusResources_get_Count(This,pnCount)	\
    (This)->lpVtbl -> get_Count(This,pnCount)

#define ClusResources_get__NewEnum(This,retval)	\
    (This)->lpVtbl -> get__NewEnum(This,retval)

#define ClusResources_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)


#define ClusResources_get_Item(This,varIndex,ppClusResource)	\
    (This)->lpVtbl -> get_Item(This,varIndex,ppClusResource)

#define ClusResources_CreateItem(This,bstrResourceName,bstrResourceType,bstrGroupName,dwFlags,ppClusterResource)	\
    (This)->lpVtbl -> CreateItem(This,bstrResourceName,bstrResourceType,bstrGroupName,dwFlags,ppClusterResource)

#define ClusResources_DeleteItem(This,varIndex)	\
    (This)->lpVtbl -> DeleteItem(This,varIndex)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ClusResources_get_Item_Proxy( 
    ClusResources __RPC_FAR * This,
    /* [in] */ VARIANT varIndex,
    /* [retval][out] */ ClusResource __RPC_FAR *__RPC_FAR *ppClusResource);


void __RPC_STUB ClusResources_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ClusResources_CreateItem_Proxy( 
    ClusResources __RPC_FAR * This,
    /* [in] */ BSTR bstrResourceName,
    /* [in] */ BSTR bstrResourceType,
    /* [in] */ BSTR bstrGroupName,
    /* [in] */ CLUSTER_RESOURCE_CREATE_FLAGS dwFlags,
    /* [retval][out] */ ClusResource __RPC_FAR *__RPC_FAR *ppClusterResource);


void __RPC_STUB ClusResources_CreateItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ClusResources_DeleteItem_Proxy( 
    ClusResources __RPC_FAR * This,
    /* [in] */ VARIANT varIndex);


void __RPC_STUB ClusResources_DeleteItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ClusResources_INTERFACE_DEFINED__ */


#ifndef __ClusGroupOwners_INTERFACE_DEFINED__
#define __ClusGroupOwners_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ClusGroupOwners
 * at Wed Sep 17 12:03:32 1997
 * using MIDL 3.00.44
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ClusGroupOwners;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface ClusGroupOwners : public ClusObjCollection
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT varIndex,
            /* [retval][out] */ ClusNode __RPC_FAR *__RPC_FAR *ppClusNode) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE InsertItem( 
            /* [in] */ ClusNode __RPC_FAR *pClusNode,
            /* [optional][in] */ LONG nPosition) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RemoveItem( 
            /* [in] */ VARIANT varIndex) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Modified( 
            /* [retval][out] */ boolean __RPC_FAR *flag) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ClusGroupOwnersVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ClusGroupOwners __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ClusGroupOwners __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ClusGroupOwners __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ClusGroupOwners __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ClusGroupOwners __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ClusGroupOwners __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ClusGroupOwners __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ClusGroupOwners __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pnCount);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ClusGroupOwners __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            ClusGroupOwners __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ClusGroupOwners __RPC_FAR * This,
            /* [in] */ VARIANT varIndex,
            /* [retval][out] */ ClusNode __RPC_FAR *__RPC_FAR *ppClusNode);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InsertItem )( 
            ClusGroupOwners __RPC_FAR * This,
            /* [in] */ ClusNode __RPC_FAR *pClusNode,
            /* [optional][in] */ LONG nPosition);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveItem )( 
            ClusGroupOwners __RPC_FAR * This,
            /* [in] */ VARIANT varIndex);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Modified )( 
            ClusGroupOwners __RPC_FAR * This,
            /* [retval][out] */ boolean __RPC_FAR *flag);
        
        END_INTERFACE
    } ClusGroupOwnersVtbl;

    interface ClusGroupOwners
    {
        CONST_VTBL struct ClusGroupOwnersVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ClusGroupOwners_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ClusGroupOwners_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ClusGroupOwners_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ClusGroupOwners_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ClusGroupOwners_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ClusGroupOwners_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ClusGroupOwners_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ClusGroupOwners_get_Count(This,pnCount)	\
    (This)->lpVtbl -> get_Count(This,pnCount)

#define ClusGroupOwners_get__NewEnum(This,retval)	\
    (This)->lpVtbl -> get__NewEnum(This,retval)

#define ClusGroupOwners_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)


#define ClusGroupOwners_get_Item(This,varIndex,ppClusNode)	\
    (This)->lpVtbl -> get_Item(This,varIndex,ppClusNode)

#define ClusGroupOwners_InsertItem(This,pClusNode,nPosition)	\
    (This)->lpVtbl -> InsertItem(This,pClusNode,nPosition)

#define ClusGroupOwners_RemoveItem(This,varIndex)	\
    (This)->lpVtbl -> RemoveItem(This,varIndex)

#define ClusGroupOwners_get_Modified(This,flag)	\
    (This)->lpVtbl -> get_Modified(This,flag)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ClusGroupOwners_get_Item_Proxy( 
    ClusGroupOwners __RPC_FAR * This,
    /* [in] */ VARIANT varIndex,
    /* [retval][out] */ ClusNode __RPC_FAR *__RPC_FAR *ppClusNode);


void __RPC_STUB ClusGroupOwners_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ClusGroupOwners_InsertItem_Proxy( 
    ClusGroupOwners __RPC_FAR * This,
    /* [in] */ ClusNode __RPC_FAR *pClusNode,
    /* [optional][in] */ LONG nPosition);


void __RPC_STUB ClusGroupOwners_InsertItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ClusGroupOwners_RemoveItem_Proxy( 
    ClusGroupOwners __RPC_FAR * This,
    /* [in] */ VARIANT varIndex);


void __RPC_STUB ClusGroupOwners_RemoveItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ClusGroupOwners_get_Modified_Proxy( 
    ClusGroupOwners __RPC_FAR * This,
    /* [retval][out] */ boolean __RPC_FAR *flag);


void __RPC_STUB ClusGroupOwners_get_Modified_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ClusGroupOwners_INTERFACE_DEFINED__ */


#ifndef __ClusResOwners_INTERFACE_DEFINED__
#define __ClusResOwners_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ClusResOwners
 * at Wed Sep 17 12:03:32 1997
 * using MIDL 3.00.44
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ClusResOwners;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface ClusResOwners : public ClusObjCollection
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT varIndex,
            /* [retval][out] */ ClusNode __RPC_FAR *__RPC_FAR *ppClusNode) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddItem( 
            /* [in] */ ClusNode __RPC_FAR *pNode) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RemoveItem( 
            /* [in] */ VARIANT varIndex) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Modified( 
            /* [retval][out] */ boolean __RPC_FAR *pbflag) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ClusResOwnersVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ClusResOwners __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ClusResOwners __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ClusResOwners __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ClusResOwners __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ClusResOwners __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ClusResOwners __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ClusResOwners __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ClusResOwners __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pnCount);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ClusResOwners __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            ClusResOwners __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ClusResOwners __RPC_FAR * This,
            /* [in] */ VARIANT varIndex,
            /* [retval][out] */ ClusNode __RPC_FAR *__RPC_FAR *ppClusNode);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddItem )( 
            ClusResOwners __RPC_FAR * This,
            /* [in] */ ClusNode __RPC_FAR *pNode);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveItem )( 
            ClusResOwners __RPC_FAR * This,
            /* [in] */ VARIANT varIndex);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Modified )( 
            ClusResOwners __RPC_FAR * This,
            /* [retval][out] */ boolean __RPC_FAR *pbflag);
        
        END_INTERFACE
    } ClusResOwnersVtbl;

    interface ClusResOwners
    {
        CONST_VTBL struct ClusResOwnersVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ClusResOwners_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ClusResOwners_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ClusResOwners_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ClusResOwners_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ClusResOwners_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ClusResOwners_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ClusResOwners_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ClusResOwners_get_Count(This,pnCount)	\
    (This)->lpVtbl -> get_Count(This,pnCount)

#define ClusResOwners_get__NewEnum(This,retval)	\
    (This)->lpVtbl -> get__NewEnum(This,retval)

#define ClusResOwners_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)


#define ClusResOwners_get_Item(This,varIndex,ppClusNode)	\
    (This)->lpVtbl -> get_Item(This,varIndex,ppClusNode)

#define ClusResOwners_AddItem(This,pNode)	\
    (This)->lpVtbl -> AddItem(This,pNode)

#define ClusResOwners_RemoveItem(This,varIndex)	\
    (This)->lpVtbl -> RemoveItem(This,varIndex)

#define ClusResOwners_get_Modified(This,pbflag)	\
    (This)->lpVtbl -> get_Modified(This,pbflag)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ClusResOwners_get_Item_Proxy( 
    ClusResOwners __RPC_FAR * This,
    /* [in] */ VARIANT varIndex,
    /* [retval][out] */ ClusNode __RPC_FAR *__RPC_FAR *ppClusNode);


void __RPC_STUB ClusResOwners_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ClusResOwners_AddItem_Proxy( 
    ClusResOwners __RPC_FAR * This,
    /* [in] */ ClusNode __RPC_FAR *pNode);


void __RPC_STUB ClusResOwners_AddItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ClusResOwners_RemoveItem_Proxy( 
    ClusResOwners __RPC_FAR * This,
    /* [in] */ VARIANT varIndex);


void __RPC_STUB ClusResOwners_RemoveItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ClusResOwners_get_Modified_Proxy( 
    ClusResOwners __RPC_FAR * This,
    /* [retval][out] */ boolean __RPC_FAR *pbflag);


void __RPC_STUB ClusResOwners_get_Modified_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ClusResOwners_INTERFACE_DEFINED__ */


#ifndef __ClusResType_INTERFACE_DEFINED__
#define __ClusResType_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ClusResType
 * at Wed Sep 17 12:03:32 1997
 * using MIDL 3.00.44
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ClusResType;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface ClusResType : public ClusObj
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Delete( void) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Cluster( 
            /* [retval][out] */ ICluster __RPC_FAR *__RPC_FAR *ppCluster) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Resources( 
            /* [retval][out] */ ClusResTypeResources __RPC_FAR *__RPC_FAR *ppClusterResTypeResources) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ClusResTypeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ClusResType __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ClusResType __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ClusResType __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ClusResType __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ClusResType __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ClusResType __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ClusResType __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            ClusResType __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CommonProperties )( 
            ClusResType __RPC_FAR * This,
            /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PrivateProperties )( 
            ClusResType __RPC_FAR * This,
            /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CommonROProperties )( 
            ClusResType __RPC_FAR * This,
            /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PrivateROProperties )( 
            ClusResType __RPC_FAR * This,
            /* [retval][out] */ ClusProperties __RPC_FAR *__RPC_FAR *ppProperties);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            ClusResType __RPC_FAR * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Cluster )( 
            ClusResType __RPC_FAR * This,
            /* [retval][out] */ ICluster __RPC_FAR *__RPC_FAR *ppCluster);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Resources )( 
            ClusResType __RPC_FAR * This,
            /* [retval][out] */ ClusResTypeResources __RPC_FAR *__RPC_FAR *ppClusterResTypeResources);
        
        END_INTERFACE
    } ClusResTypeVtbl;

    interface ClusResType
    {
        CONST_VTBL struct ClusResTypeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ClusResType_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ClusResType_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ClusResType_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ClusResType_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ClusResType_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ClusResType_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ClusResType_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ClusResType_get_Name(This,pbstrName)	\
    (This)->lpVtbl -> get_Name(This,pbstrName)

#define ClusResType_get_CommonProperties(This,ppProperties)	\
    (This)->lpVtbl -> get_CommonProperties(This,ppProperties)

#define ClusResType_get_PrivateProperties(This,ppProperties)	\
    (This)->lpVtbl -> get_PrivateProperties(This,ppProperties)

#define ClusResType_get_CommonROProperties(This,ppProperties)	\
    (This)->lpVtbl -> get_CommonROProperties(This,ppProperties)

#define ClusResType_get_PrivateROProperties(This,ppProperties)	\
    (This)->lpVtbl -> get_PrivateROProperties(This,ppProperties)


#define ClusResType_Delete(This)	\
    (This)->lpVtbl -> Delete(This)

#define ClusResType_get_Cluster(This,ppCluster)	\
    (This)->lpVtbl -> get_Cluster(This,ppCluster)

#define ClusResType_get_Resources(This,ppClusterResTypeResources)	\
    (This)->lpVtbl -> get_Resources(This,ppClusterResTypeResources)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ClusResType_Delete_Proxy( 
    ClusResType __RPC_FAR * This);


void __RPC_STUB ClusResType_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ClusResType_get_Cluster_Proxy( 
    ClusResType __RPC_FAR * This,
    /* [retval][out] */ ICluster __RPC_FAR *__RPC_FAR *ppCluster);


void __RPC_STUB ClusResType_get_Cluster_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ClusResType_get_Resources_Proxy( 
    ClusResType __RPC_FAR * This,
    /* [retval][out] */ ClusResTypeResources __RPC_FAR *__RPC_FAR *ppClusterResTypeResources);


void __RPC_STUB ClusResType_get_Resources_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ClusResType_INTERFACE_DEFINED__ */


#ifndef __ClusResTypes_INTERFACE_DEFINED__
#define __ClusResTypes_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ClusResTypes
 * at Wed Sep 17 12:03:32 1997
 * using MIDL 3.00.44
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ClusResTypes;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface ClusResTypes : public ClusObjCollection
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT varIndex,
            /* [retval][out] */ ClusResType __RPC_FAR *__RPC_FAR *ppClusResType) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateItem( 
            /* [in] */ BSTR bstrResourceTypeName,
            /* [in] */ BSTR bstrDisplayName,
            /* [in] */ BSTR bstrResourceTypeDll,
            /* [in] */ LONG dwLooksAlivePollInterval,
            /* [in] */ LONG dwIsAlivePollInterval,
            /* [retval][out] */ ClusResType __RPC_FAR *__RPC_FAR *ppResourceType) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeleteItem( 
            /* [in] */ VARIANT varIndex) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ClusResTypesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ClusResTypes __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ClusResTypes __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ClusResTypes __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ClusResTypes __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ClusResTypes __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ClusResTypes __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ClusResTypes __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ClusResTypes __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pnCount);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ClusResTypes __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            ClusResTypes __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ClusResTypes __RPC_FAR * This,
            /* [in] */ VARIANT varIndex,
            /* [retval][out] */ ClusResType __RPC_FAR *__RPC_FAR *ppClusResType);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateItem )( 
            ClusResTypes __RPC_FAR * This,
            /* [in] */ BSTR bstrResourceTypeName,
            /* [in] */ BSTR bstrDisplayName,
            /* [in] */ BSTR bstrResourceTypeDll,
            /* [in] */ LONG dwLooksAlivePollInterval,
            /* [in] */ LONG dwIsAlivePollInterval,
            /* [retval][out] */ ClusResType __RPC_FAR *__RPC_FAR *ppResourceType);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteItem )( 
            ClusResTypes __RPC_FAR * This,
            /* [in] */ VARIANT varIndex);
        
        END_INTERFACE
    } ClusResTypesVtbl;

    interface ClusResTypes
    {
        CONST_VTBL struct ClusResTypesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ClusResTypes_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ClusResTypes_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ClusResTypes_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ClusResTypes_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ClusResTypes_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ClusResTypes_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ClusResTypes_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ClusResTypes_get_Count(This,pnCount)	\
    (This)->lpVtbl -> get_Count(This,pnCount)

#define ClusResTypes_get__NewEnum(This,retval)	\
    (This)->lpVtbl -> get__NewEnum(This,retval)

#define ClusResTypes_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)


#define ClusResTypes_get_Item(This,varIndex,ppClusResType)	\
    (This)->lpVtbl -> get_Item(This,varIndex,ppClusResType)

#define ClusResTypes_CreateItem(This,bstrResourceTypeName,bstrDisplayName,bstrResourceTypeDll,dwLooksAlivePollInterval,dwIsAlivePollInterval,ppResourceType)	\
    (This)->lpVtbl -> CreateItem(This,bstrResourceTypeName,bstrDisplayName,bstrResourceTypeDll,dwLooksAlivePollInterval,dwIsAlivePollInterval,ppResourceType)

#define ClusResTypes_DeleteItem(This,varIndex)	\
    (This)->lpVtbl -> DeleteItem(This,varIndex)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ClusResTypes_get_Item_Proxy( 
    ClusResTypes __RPC_FAR * This,
    /* [in] */ VARIANT varIndex,
    /* [retval][out] */ ClusResType __RPC_FAR *__RPC_FAR *ppClusResType);


void __RPC_STUB ClusResTypes_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ClusResTypes_CreateItem_Proxy( 
    ClusResTypes __RPC_FAR * This,
    /* [in] */ BSTR bstrResourceTypeName,
    /* [in] */ BSTR bstrDisplayName,
    /* [in] */ BSTR bstrResourceTypeDll,
    /* [in] */ LONG dwLooksAlivePollInterval,
    /* [in] */ LONG dwIsAlivePollInterval,
    /* [retval][out] */ ClusResType __RPC_FAR *__RPC_FAR *ppResourceType);


void __RPC_STUB ClusResTypes_CreateItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ClusResTypes_DeleteItem_Proxy( 
    ClusResTypes __RPC_FAR * This,
    /* [in] */ VARIANT varIndex);


void __RPC_STUB ClusResTypes_DeleteItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ClusResTypes_INTERFACE_DEFINED__ */


#ifndef __ClusProperty_INTERFACE_DEFINED__
#define __ClusProperty_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ClusProperty
 * at Wed Sep 17 12:03:32 1997
 * using MIDL 3.00.44
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ClusProperty;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface ClusProperty : public IDispatch
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [retval][out] */ VARIANT __RPC_FAR *pvarValue) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Value( 
            /* [in] */ VARIANT varValue) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ClusPropertyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ClusProperty __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ClusProperty __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ClusProperty __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ClusProperty __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ClusProperty __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ClusProperty __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ClusProperty __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            ClusProperty __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Value )( 
            ClusProperty __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarValue);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Value )( 
            ClusProperty __RPC_FAR * This,
            /* [in] */ VARIANT varValue);
        
        END_INTERFACE
    } ClusPropertyVtbl;

    interface ClusProperty
    {
        CONST_VTBL struct ClusPropertyVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ClusProperty_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ClusProperty_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ClusProperty_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ClusProperty_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ClusProperty_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ClusProperty_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ClusProperty_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ClusProperty_get_Name(This,pbstrName)	\
    (This)->lpVtbl -> get_Name(This,pbstrName)

#define ClusProperty_get_Value(This,pvarValue)	\
    (This)->lpVtbl -> get_Value(This,pvarValue)

#define ClusProperty_put_Value(This,varValue)	\
    (This)->lpVtbl -> put_Value(This,varValue)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE ClusProperty_get_Name_Proxy( 
    ClusProperty __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrName);


void __RPC_STUB ClusProperty_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ClusProperty_get_Value_Proxy( 
    ClusProperty __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pvarValue);


void __RPC_STUB ClusProperty_get_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE ClusProperty_put_Value_Proxy( 
    ClusProperty __RPC_FAR * This,
    /* [in] */ VARIANT varValue);


void __RPC_STUB ClusProperty_put_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ClusProperty_INTERFACE_DEFINED__ */


#ifndef __ClusProperties_INTERFACE_DEFINED__
#define __ClusProperties_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ClusProperties
 * at Wed Sep 17 12:03:32 1997
 * using MIDL 3.00.44
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ClusProperties;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface ClusProperties : public ClusObjCollection
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT varIndex,
            /* [retval][out] */ ClusProperty __RPC_FAR *__RPC_FAR *ppClusProperty) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT varValue,
            /* [retval][out] */ ClusProperty __RPC_FAR *__RPC_FAR *pProperty) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT varIndex) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SaveChanges( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ClusPropertiesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ClusProperties __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ClusProperties __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ClusProperties __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ClusProperties __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ClusProperties __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ClusProperties __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ClusProperties __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ClusProperties __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pnCount);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ClusProperties __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            ClusProperties __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ClusProperties __RPC_FAR * This,
            /* [in] */ VARIANT varIndex,
            /* [retval][out] */ ClusProperty __RPC_FAR *__RPC_FAR *ppClusProperty);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            ClusProperties __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT varValue,
            /* [retval][out] */ ClusProperty __RPC_FAR *__RPC_FAR *pProperty);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            ClusProperties __RPC_FAR * This,
            /* [in] */ VARIANT varIndex);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SaveChanges )( 
            ClusProperties __RPC_FAR * This);
        
        END_INTERFACE
    } ClusPropertiesVtbl;

    interface ClusProperties
    {
        CONST_VTBL struct ClusPropertiesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ClusProperties_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ClusProperties_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ClusProperties_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ClusProperties_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ClusProperties_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ClusProperties_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ClusProperties_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ClusProperties_get_Count(This,pnCount)	\
    (This)->lpVtbl -> get_Count(This,pnCount)

#define ClusProperties_get__NewEnum(This,retval)	\
    (This)->lpVtbl -> get__NewEnum(This,retval)

#define ClusProperties_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)


#define ClusProperties_get_Item(This,varIndex,ppClusProperty)	\
    (This)->lpVtbl -> get_Item(This,varIndex,ppClusProperty)

#define ClusProperties_Add(This,bstrName,varValue,pProperty)	\
    (This)->lpVtbl -> Add(This,bstrName,varValue,pProperty)

#define ClusProperties_Remove(This,varIndex)	\
    (This)->lpVtbl -> Remove(This,varIndex)

#define ClusProperties_SaveChanges(This)	\
    (This)->lpVtbl -> SaveChanges(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ClusProperties_get_Item_Proxy( 
    ClusProperties __RPC_FAR * This,
    /* [in] */ VARIANT varIndex,
    /* [retval][out] */ ClusProperty __RPC_FAR *__RPC_FAR *ppClusProperty);


void __RPC_STUB ClusProperties_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ClusProperties_Add_Proxy( 
    ClusProperties __RPC_FAR * This,
    /* [in] */ BSTR bstrName,
    /* [in] */ VARIANT varValue,
    /* [retval][out] */ ClusProperty __RPC_FAR *__RPC_FAR *pProperty);


void __RPC_STUB ClusProperties_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ClusProperties_Remove_Proxy( 
    ClusProperties __RPC_FAR * This,
    /* [in] */ VARIANT varIndex);


void __RPC_STUB ClusProperties_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ClusProperties_SaveChanges_Proxy( 
    ClusProperties __RPC_FAR * This);


void __RPC_STUB ClusProperties_SaveChanges_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ClusProperties_INTERFACE_DEFINED__ */



#ifndef __MSClusterLib_LIBRARY_DEFINED__
#define __MSClusterLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: MSClusterLib
 * at Wed Sep 17 12:03:32 1997
 * using MIDL 3.00.44
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_MSClusterLib;

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_Application;

class Application;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_Cluster;

class Cluster;
#endif
#endif /* __MSClusterLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
