/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.01.75 */
/* at Tue Apr 28 11:55:07 1998
 */
/* Compiler settings for idl\oledb.idl:
    Oicf (OptLev=i2), W1, Zp2, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"
#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __oledb_h__
#define __oledb_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IAccessor_FWD_DEFINED__
#define __IAccessor_FWD_DEFINED__
typedef interface IAccessor IAccessor;
#endif 	/* __IAccessor_FWD_DEFINED__ */


#ifndef __IRowset_FWD_DEFINED__
#define __IRowset_FWD_DEFINED__
typedef interface IRowset IRowset;
#endif 	/* __IRowset_FWD_DEFINED__ */


#ifndef __IRowsetInfo_FWD_DEFINED__
#define __IRowsetInfo_FWD_DEFINED__
typedef interface IRowsetInfo IRowsetInfo;
#endif 	/* __IRowsetInfo_FWD_DEFINED__ */


#ifndef __IRowsetLocate_FWD_DEFINED__
#define __IRowsetLocate_FWD_DEFINED__
typedef interface IRowsetLocate IRowsetLocate;
#endif 	/* __IRowsetLocate_FWD_DEFINED__ */


#ifndef __IRowsetResynch_FWD_DEFINED__
#define __IRowsetResynch_FWD_DEFINED__
typedef interface IRowsetResynch IRowsetResynch;
#endif 	/* __IRowsetResynch_FWD_DEFINED__ */


#ifndef __IRowsetScroll_FWD_DEFINED__
#define __IRowsetScroll_FWD_DEFINED__
typedef interface IRowsetScroll IRowsetScroll;
#endif 	/* __IRowsetScroll_FWD_DEFINED__ */


#ifndef __IChapteredRowset_FWD_DEFINED__
#define __IChapteredRowset_FWD_DEFINED__
typedef interface IChapteredRowset IChapteredRowset;
#endif 	/* __IChapteredRowset_FWD_DEFINED__ */


#ifndef __IRowsetFind_FWD_DEFINED__
#define __IRowsetFind_FWD_DEFINED__
typedef interface IRowsetFind IRowsetFind;
#endif 	/* __IRowsetFind_FWD_DEFINED__ */


#ifndef __IRowPosition_FWD_DEFINED__
#define __IRowPosition_FWD_DEFINED__
typedef interface IRowPosition IRowPosition;
#endif 	/* __IRowPosition_FWD_DEFINED__ */


#ifndef __IRowPositionChange_FWD_DEFINED__
#define __IRowPositionChange_FWD_DEFINED__
typedef interface IRowPositionChange IRowPositionChange;
#endif 	/* __IRowPositionChange_FWD_DEFINED__ */


#ifndef __IViewRowset_FWD_DEFINED__
#define __IViewRowset_FWD_DEFINED__
typedef interface IViewRowset IViewRowset;
#endif 	/* __IViewRowset_FWD_DEFINED__ */


#ifndef __IViewChapter_FWD_DEFINED__
#define __IViewChapter_FWD_DEFINED__
typedef interface IViewChapter IViewChapter;
#endif 	/* __IViewChapter_FWD_DEFINED__ */


#ifndef __IViewSort_FWD_DEFINED__
#define __IViewSort_FWD_DEFINED__
typedef interface IViewSort IViewSort;
#endif 	/* __IViewSort_FWD_DEFINED__ */


#ifndef __IViewFilter_FWD_DEFINED__
#define __IViewFilter_FWD_DEFINED__
typedef interface IViewFilter IViewFilter;
#endif 	/* __IViewFilter_FWD_DEFINED__ */


#ifndef __IRowsetView_FWD_DEFINED__
#define __IRowsetView_FWD_DEFINED__
typedef interface IRowsetView IRowsetView;
#endif 	/* __IRowsetView_FWD_DEFINED__ */


#ifndef __IRowsetExactScroll_FWD_DEFINED__
#define __IRowsetExactScroll_FWD_DEFINED__
typedef interface IRowsetExactScroll IRowsetExactScroll;
#endif 	/* __IRowsetExactScroll_FWD_DEFINED__ */


#ifndef __IRowsetChange_FWD_DEFINED__
#define __IRowsetChange_FWD_DEFINED__
typedef interface IRowsetChange IRowsetChange;
#endif 	/* __IRowsetChange_FWD_DEFINED__ */


#ifndef __IRowsetUpdate_FWD_DEFINED__
#define __IRowsetUpdate_FWD_DEFINED__
typedef interface IRowsetUpdate IRowsetUpdate;
#endif 	/* __IRowsetUpdate_FWD_DEFINED__ */


#ifndef __IRowsetNextRowset_FWD_DEFINED__
#define __IRowsetNextRowset_FWD_DEFINED__
typedef interface IRowsetNextRowset IRowsetNextRowset;
#endif 	/* __IRowsetNextRowset_FWD_DEFINED__ */


#ifndef __IRowsetIdentity_FWD_DEFINED__
#define __IRowsetIdentity_FWD_DEFINED__
typedef interface IRowsetIdentity IRowsetIdentity;
#endif 	/* __IRowsetIdentity_FWD_DEFINED__ */


#ifndef __IRowsetNewRowAfter_FWD_DEFINED__
#define __IRowsetNewRowAfter_FWD_DEFINED__
typedef interface IRowsetNewRowAfter IRowsetNewRowAfter;
#endif 	/* __IRowsetNewRowAfter_FWD_DEFINED__ */


#ifndef __IRowsetWithParameters_FWD_DEFINED__
#define __IRowsetWithParameters_FWD_DEFINED__
typedef interface IRowsetWithParameters IRowsetWithParameters;
#endif 	/* __IRowsetWithParameters_FWD_DEFINED__ */


#ifndef __IRowsetAsynch_FWD_DEFINED__
#define __IRowsetAsynch_FWD_DEFINED__
typedef interface IRowsetAsynch IRowsetAsynch;
#endif 	/* __IRowsetAsynch_FWD_DEFINED__ */


#ifndef __IRowsetKeys_FWD_DEFINED__
#define __IRowsetKeys_FWD_DEFINED__
typedef interface IRowsetKeys IRowsetKeys;
#endif 	/* __IRowsetKeys_FWD_DEFINED__ */


#ifndef __IRowsetNotify_FWD_DEFINED__
#define __IRowsetNotify_FWD_DEFINED__
typedef interface IRowsetNotify IRowsetNotify;
#endif 	/* __IRowsetNotify_FWD_DEFINED__ */


#ifndef __IRowsetIndex_FWD_DEFINED__
#define __IRowsetIndex_FWD_DEFINED__
typedef interface IRowsetIndex IRowsetIndex;
#endif 	/* __IRowsetIndex_FWD_DEFINED__ */


#ifndef __IRowsetWatchAll_FWD_DEFINED__
#define __IRowsetWatchAll_FWD_DEFINED__
typedef interface IRowsetWatchAll IRowsetWatchAll;
#endif 	/* __IRowsetWatchAll_FWD_DEFINED__ */


#ifndef __IRowsetWatchNotify_FWD_DEFINED__
#define __IRowsetWatchNotify_FWD_DEFINED__
typedef interface IRowsetWatchNotify IRowsetWatchNotify;
#endif 	/* __IRowsetWatchNotify_FWD_DEFINED__ */


#ifndef __IRowsetWatchRegion_FWD_DEFINED__
#define __IRowsetWatchRegion_FWD_DEFINED__
typedef interface IRowsetWatchRegion IRowsetWatchRegion;
#endif 	/* __IRowsetWatchRegion_FWD_DEFINED__ */


#ifndef __IRowsetCopyRows_FWD_DEFINED__
#define __IRowsetCopyRows_FWD_DEFINED__
typedef interface IRowsetCopyRows IRowsetCopyRows;
#endif 	/* __IRowsetCopyRows_FWD_DEFINED__ */


#ifndef __IReadData_FWD_DEFINED__
#define __IReadData_FWD_DEFINED__
typedef interface IReadData IReadData;
#endif 	/* __IReadData_FWD_DEFINED__ */


#ifndef __ICommand_FWD_DEFINED__
#define __ICommand_FWD_DEFINED__
typedef interface ICommand ICommand;
#endif 	/* __ICommand_FWD_DEFINED__ */


#ifndef __IMultipleResults_FWD_DEFINED__
#define __IMultipleResults_FWD_DEFINED__
typedef interface IMultipleResults IMultipleResults;
#endif 	/* __IMultipleResults_FWD_DEFINED__ */


#ifndef __IConvertType_FWD_DEFINED__
#define __IConvertType_FWD_DEFINED__
typedef interface IConvertType IConvertType;
#endif 	/* __IConvertType_FWD_DEFINED__ */


#ifndef __ICommandCost_FWD_DEFINED__
#define __ICommandCost_FWD_DEFINED__
typedef interface ICommandCost ICommandCost;
#endif 	/* __ICommandCost_FWD_DEFINED__ */


#ifndef __ICommandPrepare_FWD_DEFINED__
#define __ICommandPrepare_FWD_DEFINED__
typedef interface ICommandPrepare ICommandPrepare;
#endif 	/* __ICommandPrepare_FWD_DEFINED__ */


#ifndef __ICommandProperties_FWD_DEFINED__
#define __ICommandProperties_FWD_DEFINED__
typedef interface ICommandProperties ICommandProperties;
#endif 	/* __ICommandProperties_FWD_DEFINED__ */


#ifndef __ICommandText_FWD_DEFINED__
#define __ICommandText_FWD_DEFINED__
typedef interface ICommandText ICommandText;
#endif 	/* __ICommandText_FWD_DEFINED__ */


#ifndef __ICommandTree_FWD_DEFINED__
#define __ICommandTree_FWD_DEFINED__
typedef interface ICommandTree ICommandTree;
#endif 	/* __ICommandTree_FWD_DEFINED__ */


#ifndef __ICommandValidate_FWD_DEFINED__
#define __ICommandValidate_FWD_DEFINED__
typedef interface ICommandValidate ICommandValidate;
#endif 	/* __ICommandValidate_FWD_DEFINED__ */


#ifndef __ICommandWithParameters_FWD_DEFINED__
#define __ICommandWithParameters_FWD_DEFINED__
typedef interface ICommandWithParameters ICommandWithParameters;
#endif 	/* __ICommandWithParameters_FWD_DEFINED__ */


#ifndef __IQuery_FWD_DEFINED__
#define __IQuery_FWD_DEFINED__
typedef interface IQuery IQuery;
#endif 	/* __IQuery_FWD_DEFINED__ */


#ifndef __IColumnsRowset_FWD_DEFINED__
#define __IColumnsRowset_FWD_DEFINED__
typedef interface IColumnsRowset IColumnsRowset;
#endif 	/* __IColumnsRowset_FWD_DEFINED__ */


#ifndef __IColumnsInfo_FWD_DEFINED__
#define __IColumnsInfo_FWD_DEFINED__
typedef interface IColumnsInfo IColumnsInfo;
#endif 	/* __IColumnsInfo_FWD_DEFINED__ */


#ifndef __IDBCreateCommand_FWD_DEFINED__
#define __IDBCreateCommand_FWD_DEFINED__
typedef interface IDBCreateCommand IDBCreateCommand;
#endif 	/* __IDBCreateCommand_FWD_DEFINED__ */


#ifndef __IDBCreateSession_FWD_DEFINED__
#define __IDBCreateSession_FWD_DEFINED__
typedef interface IDBCreateSession IDBCreateSession;
#endif 	/* __IDBCreateSession_FWD_DEFINED__ */


#ifndef __ISourcesRowset_FWD_DEFINED__
#define __ISourcesRowset_FWD_DEFINED__
typedef interface ISourcesRowset ISourcesRowset;
#endif 	/* __ISourcesRowset_FWD_DEFINED__ */


#ifndef __IDBProperties_FWD_DEFINED__
#define __IDBProperties_FWD_DEFINED__
typedef interface IDBProperties IDBProperties;
#endif 	/* __IDBProperties_FWD_DEFINED__ */


#ifndef __IDBInitialize_FWD_DEFINED__
#define __IDBInitialize_FWD_DEFINED__
typedef interface IDBInitialize IDBInitialize;
#endif 	/* __IDBInitialize_FWD_DEFINED__ */


#ifndef __IDBInfo_FWD_DEFINED__
#define __IDBInfo_FWD_DEFINED__
typedef interface IDBInfo IDBInfo;
#endif 	/* __IDBInfo_FWD_DEFINED__ */


#ifndef __IDBDataSourceAdmin_FWD_DEFINED__
#define __IDBDataSourceAdmin_FWD_DEFINED__
typedef interface IDBDataSourceAdmin IDBDataSourceAdmin;
#endif 	/* __IDBDataSourceAdmin_FWD_DEFINED__ */


#ifndef __IDBAsynchNotify_FWD_DEFINED__
#define __IDBAsynchNotify_FWD_DEFINED__
typedef interface IDBAsynchNotify IDBAsynchNotify;
#endif 	/* __IDBAsynchNotify_FWD_DEFINED__ */


#ifndef __IDBAsynchStatus_FWD_DEFINED__
#define __IDBAsynchStatus_FWD_DEFINED__
typedef interface IDBAsynchStatus IDBAsynchStatus;
#endif 	/* __IDBAsynchStatus_FWD_DEFINED__ */


#ifndef __ISessionProperties_FWD_DEFINED__
#define __ISessionProperties_FWD_DEFINED__
typedef interface ISessionProperties ISessionProperties;
#endif 	/* __ISessionProperties_FWD_DEFINED__ */


#ifndef __IIndexDefinition_FWD_DEFINED__
#define __IIndexDefinition_FWD_DEFINED__
typedef interface IIndexDefinition IIndexDefinition;
#endif 	/* __IIndexDefinition_FWD_DEFINED__ */


#ifndef __ITableDefinition_FWD_DEFINED__
#define __ITableDefinition_FWD_DEFINED__
typedef interface ITableDefinition ITableDefinition;
#endif 	/* __ITableDefinition_FWD_DEFINED__ */


#ifndef __IOpenRowset_FWD_DEFINED__
#define __IOpenRowset_FWD_DEFINED__
typedef interface IOpenRowset IOpenRowset;
#endif 	/* __IOpenRowset_FWD_DEFINED__ */


#ifndef __ITableRename_FWD_DEFINED__
#define __ITableRename_FWD_DEFINED__
typedef interface ITableRename ITableRename;
#endif 	/* __ITableRename_FWD_DEFINED__ */


#ifndef __IDBSchemaCommand_FWD_DEFINED__
#define __IDBSchemaCommand_FWD_DEFINED__
typedef interface IDBSchemaCommand IDBSchemaCommand;
#endif 	/* __IDBSchemaCommand_FWD_DEFINED__ */


#ifndef __IDBSchemaRowset_FWD_DEFINED__
#define __IDBSchemaRowset_FWD_DEFINED__
typedef interface IDBSchemaRowset IDBSchemaRowset;
#endif 	/* __IDBSchemaRowset_FWD_DEFINED__ */


#ifndef __IProvideMoniker_FWD_DEFINED__
#define __IProvideMoniker_FWD_DEFINED__
typedef interface IProvideMoniker IProvideMoniker;
#endif 	/* __IProvideMoniker_FWD_DEFINED__ */


#ifndef __IMDDataset_FWD_DEFINED__
#define __IMDDataset_FWD_DEFINED__
typedef interface IMDDataset IMDDataset;
#endif 	/* __IMDDataset_FWD_DEFINED__ */


#ifndef __IMDFind_FWD_DEFINED__
#define __IMDFind_FWD_DEFINED__
typedef interface IMDFind IMDFind;
#endif 	/* __IMDFind_FWD_DEFINED__ */


#ifndef __IMDRangeRowset_FWD_DEFINED__
#define __IMDRangeRowset_FWD_DEFINED__
typedef interface IMDRangeRowset IMDRangeRowset;
#endif 	/* __IMDRangeRowset_FWD_DEFINED__ */


#ifndef __IAlterTable_FWD_DEFINED__
#define __IAlterTable_FWD_DEFINED__
typedef interface IAlterTable IAlterTable;
#endif 	/* __IAlterTable_FWD_DEFINED__ */


#ifndef __IAlterIndex_FWD_DEFINED__
#define __IAlterIndex_FWD_DEFINED__
typedef interface IAlterIndex IAlterIndex;
#endif 	/* __IAlterIndex_FWD_DEFINED__ */


#ifndef __IRowsetChapterMember_FWD_DEFINED__
#define __IRowsetChapterMember_FWD_DEFINED__
typedef interface IRowsetChapterMember IRowsetChapterMember;
#endif 	/* __IRowsetChapterMember_FWD_DEFINED__ */


#ifndef __ICommandPersist_FWD_DEFINED__
#define __ICommandPersist_FWD_DEFINED__
typedef interface ICommandPersist ICommandPersist;
#endif 	/* __ICommandPersist_FWD_DEFINED__ */


#ifndef __IRowsetRefresh_FWD_DEFINED__
#define __IRowsetRefresh_FWD_DEFINED__
typedef interface IRowsetRefresh IRowsetRefresh;
#endif 	/* __IRowsetRefresh_FWD_DEFINED__ */


#ifndef __IParentRowset_FWD_DEFINED__
#define __IParentRowset_FWD_DEFINED__
typedef interface IParentRowset IParentRowset;
#endif 	/* __IParentRowset_FWD_DEFINED__ */


#ifndef __IErrorRecords_FWD_DEFINED__
#define __IErrorRecords_FWD_DEFINED__
typedef interface IErrorRecords IErrorRecords;
#endif 	/* __IErrorRecords_FWD_DEFINED__ */


#ifndef __IErrorLookup_FWD_DEFINED__
#define __IErrorLookup_FWD_DEFINED__
typedef interface IErrorLookup IErrorLookup;
#endif 	/* __IErrorLookup_FWD_DEFINED__ */


#ifndef __ISQLErrorInfo_FWD_DEFINED__
#define __ISQLErrorInfo_FWD_DEFINED__
typedef interface ISQLErrorInfo ISQLErrorInfo;
#endif 	/* __ISQLErrorInfo_FWD_DEFINED__ */


#ifndef __IGetDataSource_FWD_DEFINED__
#define __IGetDataSource_FWD_DEFINED__
typedef interface IGetDataSource IGetDataSource;
#endif 	/* __IGetDataSource_FWD_DEFINED__ */


#ifndef __ITransactionLocal_FWD_DEFINED__
#define __ITransactionLocal_FWD_DEFINED__
typedef interface ITransactionLocal ITransactionLocal;
#endif 	/* __ITransactionLocal_FWD_DEFINED__ */


#ifndef __ITransactionJoin_FWD_DEFINED__
#define __ITransactionJoin_FWD_DEFINED__
typedef interface ITransactionJoin ITransactionJoin;
#endif 	/* __ITransactionJoin_FWD_DEFINED__ */


#ifndef __ITransactionObject_FWD_DEFINED__
#define __ITransactionObject_FWD_DEFINED__
typedef interface ITransactionObject ITransactionObject;
#endif 	/* __ITransactionObject_FWD_DEFINED__ */


#ifndef __ITrusteeAdmin_FWD_DEFINED__
#define __ITrusteeAdmin_FWD_DEFINED__
typedef interface ITrusteeAdmin ITrusteeAdmin;
#endif 	/* __ITrusteeAdmin_FWD_DEFINED__ */


#ifndef __ITrusteeGroupAdmin_FWD_DEFINED__
#define __ITrusteeGroupAdmin_FWD_DEFINED__
typedef interface ITrusteeGroupAdmin ITrusteeGroupAdmin;
#endif 	/* __ITrusteeGroupAdmin_FWD_DEFINED__ */


#ifndef __IObjectAccessControl_FWD_DEFINED__
#define __IObjectAccessControl_FWD_DEFINED__
typedef interface IObjectAccessControl IObjectAccessControl;
#endif 	/* __IObjectAccessControl_FWD_DEFINED__ */


#ifndef __ISecurityInfo_FWD_DEFINED__
#define __ISecurityInfo_FWD_DEFINED__
typedef interface ISecurityInfo ISecurityInfo;
#endif 	/* __ISecurityInfo_FWD_DEFINED__ */


/* header files for imported files */
#include "wtypes.h"
#include "oaidl.h"
#include "transact.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL_itf_oledb_0000
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


//+---------------------------------------------------------------------------
//
//  Microsoft OLE DB
//  Copyright (C) Microsoft Corporation, 1994 - 1998.
//
//----------------------------------------------------------------------------

#include <pshpack2.h>	// 2-byte structure packing

//
// OLEDBVER
//	OLE DB version number is 2.0 (0x0200); to force a particular version,
//	#define OLEDBVER as required before including this file.
//

// If OLEDBVER is not defined, assume version 2.0
#ifndef OLEDBVER
#define OLEDBVER 0x0200
#endif


extern RPC_IF_HANDLE __MIDL_itf_oledb_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_oledb_0000_v0_0_s_ifspec;

#ifndef __DBStructureDefinitions_INTERFACE_DEFINED__
#define __DBStructureDefinitions_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: DBStructureDefinitions
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [auto_handle][unique][uuid] */ 


#ifndef UNALIGNED
#if defined(_MIPS_) || defined(_ALPHA_) || defined(_PPC_)
#define UNALIGNED __unaligned
#else
#define UNALIGNED
#endif
#endif //UNALIGNED
#undef OLEDBDECLSPEC
#if _MSC_VER >= 1100
#define OLEDBDECLSPEC __declspec(selectany)
#else
#define OLEDBDECLSPEC 
#endif //_MSC_VER
typedef DWORD DBKIND;


enum DBKINDENUM
    {	DBKIND_GUID_NAME	= 0,
	DBKIND_GUID_PROPID	= DBKIND_GUID_NAME + 1,
	DBKIND_NAME	= DBKIND_GUID_PROPID + 1,
	DBKIND_PGUID_NAME	= DBKIND_NAME + 1,
	DBKIND_PGUID_PROPID	= DBKIND_PGUID_NAME + 1,
	DBKIND_PROPID	= DBKIND_PGUID_PROPID + 1,
	DBKIND_GUID	= DBKIND_PROPID + 1
    };
typedef struct  tagDBID
    {
    /* [switch_is][switch_type] */ union 
        {
        /* [case()] */ GUID guid;
        /* [case()] */ GUID __RPC_FAR *pguid;
        /* [default] */  /* Empty union arm */ 
        }	uGuid;
    DBKIND eKind;
    /* [switch_is][switch_type] */ union 
        {
        /* [case()] */ LPOLESTR pwszName;
        /* [case()] */ ULONG ulPropid;
        /* [default] */  /* Empty union arm */ 
        }	uName;
    }	DBID;

typedef struct  tagDB_NUMERIC
    {
    BYTE precision;
    BYTE scale;
    BYTE sign;
    BYTE val[ 16 ];
    }	DB_NUMERIC;

#ifndef _ULONGLONG_
typedef hyper LONGLONG;

typedef MIDL_uhyper ULONGLONG;

typedef LONGLONG __RPC_FAR *PLONGLONG;

typedef ULONGLONG __RPC_FAR *PULONGLONG;

#endif // _ULONGLONG_
#ifndef DECIMAL_NEG
#ifndef DECIMAL_SETZERO
typedef struct tagDEC {
    USHORT wReserved;
    union {
        struct {
            BYTE scale;
            BYTE sign;
        };
        USHORT signscale;
    };
    ULONG Hi32;
    union {
        struct {
#ifdef _MAC
            ULONG Mid32;
            ULONG Lo32;
#else
            ULONG Lo32;
            ULONG Mid32;
#endif
        };
        ULONGLONG Lo64;
    };
} DECIMAL;
#define DECIMAL_NEG ((BYTE)0x80)
#define DECIMAL_SETZERO(dec) {(dec).Lo64 = 0; (dec).Hi32 = 0; (dec).signscale = 0;}
#endif // DECIMAL_SETZERO
#endif // DECIMAL_NEG
typedef struct  tagDBVECTOR
    {
    ULONG size;
    /* [size_is] */ void __RPC_FAR *ptr;
    }	DBVECTOR;

typedef struct  tagDBDATE
    {
    SHORT year;
    USHORT month;
    USHORT day;
    }	DBDATE;

typedef struct  tagDBTIME
    {
    USHORT hour;
    USHORT minute;
    USHORT second;
    }	DBTIME;

typedef struct  tagDBTIMESTAMP
    {
    SHORT year;
    USHORT month;
    USHORT day;
    USHORT hour;
    USHORT minute;
    USHORT second;
    ULONG fraction;
    }	DBTIMESTAMP;

//@@@+ V2.0
#if( OLEDBVER >= 0x0200 )
#if !defined(_WINBASE_) && !defined(_FILETIME_)
#define _FILETIME_
typedef struct _FILETIME {
		DWORD dwLowDateTime;
		DWORD dwHighDateTime;
     }	FILETIME;
#endif // !_FILETIME
typedef struct  tagDBFILETIME
    {
    DWORD dwLowDateTime;
    DWORD dwHighDateTime;
    }	DBFILETIME;

typedef signed char SBYTE;

typedef struct  tagDB_VARNUMERIC
    {
    BYTE precision;
    SBYTE scale;
    BYTE sign;
    BYTE val[ 1 ];
    }	DB_VARNUMERIC;

#endif // OLEDBVER >= 0x0200
//@@@- V2.0
//@@@+ V2.1
#if( OLEDBVER >= 0x0210 )
typedef struct  _SEC_OBJECT_ELEMENT
    {
    GUID guidObjectType;
    DBID ObjectID;
    }	SEC_OBJECT_ELEMENT;

typedef struct  _SEC_OBJECT
    {
    DWORD cObjects;
    /* [size_is] */ SEC_OBJECT_ELEMENT __RPC_FAR *prgObjects;
    }	SEC_OBJECT;

#endif // OLEDBVER >= 0x0210
//@@@- V2.1
typedef WORD DBTYPE;


enum DBTYPEENUM
    {	DBTYPE_EMPTY	= 0,
	DBTYPE_NULL	= 1,
	DBTYPE_I2	= 2,
	DBTYPE_I4	= 3,
	DBTYPE_R4	= 4,
	DBTYPE_R8	= 5,
	DBTYPE_CY	= 6,
	DBTYPE_DATE	= 7,
	DBTYPE_BSTR	= 8,
	DBTYPE_IDISPATCH	= 9,
	DBTYPE_ERROR	= 10,
	DBTYPE_BOOL	= 11,
	DBTYPE_VARIANT	= 12,
	DBTYPE_IUNKNOWN	= 13,
	DBTYPE_DECIMAL	= 14,
	DBTYPE_UI1	= 17,
	DBTYPE_ARRAY	= 0x2000,
	DBTYPE_BYREF	= 0x4000,
	DBTYPE_I1	= 16,
	DBTYPE_UI2	= 18,
	DBTYPE_UI4	= 19,
	DBTYPE_I8	= 20,
	DBTYPE_UI8	= 21,
	DBTYPE_GUID	= 72,
	DBTYPE_VECTOR	= 0x1000,
	DBTYPE_RESERVED	= 0x8000,
	DBTYPE_BYTES	= 128,
	DBTYPE_STR	= 129,
	DBTYPE_WSTR	= 130,
	DBTYPE_NUMERIC	= 131,
	DBTYPE_UDT	= 132,
	DBTYPE_DBDATE	= 133,
	DBTYPE_DBTIME	= 134,
	DBTYPE_DBTIMESTAMP	= 135
    };
//@@@+ V1.5
#if( OLEDBVER >= 0x0150 )

enum DBTYPEENUM15
    {	DBTYPE_HCHAPTER	= 136
    };
#endif // OLEDBVER >= 0x0150
//@@@- V1.5
//@@@+ V2.0
#if( OLEDBVER >= 0x0200 )

enum DBTYPEENUM20
    {	DBTYPE_FILETIME	= 64,
	DBTYPE_DBFILETIME	= 137,
	DBTYPE_PROPVARIANT	= 138,
	DBTYPE_VARNUMERIC	= 139
    };
#endif // OLEDBVER >= 0x0200
//@@@- V2.0
typedef DWORD DBPART;


enum DBPARTENUM
    {	DBPART_INVALID	= 0,
	DBPART_VALUE	= 0x1,
	DBPART_LENGTH	= 0x2,
	DBPART_STATUS	= 0x4
    };
typedef DWORD DBPARAMIO;


enum DBPARAMIOENUM
    {	DBPARAMIO_NOTPARAM	= 0,
	DBPARAMIO_INPUT	= 0x1,
	DBPARAMIO_OUTPUT	= 0x2
    };
//@@@+ V1.5
#if( OLEDBVER >= 0x0150 )
typedef DWORD DBBINDFLAG;


enum DBBINDFLAGENUM
    {	DBBINDFLAG_HTML	= 0x1
    };
#endif // OLEDBVER >= 0x0150
//@@@- V1.5
typedef DWORD DBMEMOWNER;


enum DBMEMOWNERENUM
    {	DBMEMOWNER_CLIENTOWNED	= 0,
	DBMEMOWNER_PROVIDEROWNED	= 0x1
    };
typedef struct  tagDBOBJECT
    {
    DWORD dwFlags;
    IID iid;
    }	DBOBJECT;

typedef DWORD DBSTATUS;


enum DBSTATUSENUM
    {	DBSTATUS_S_OK	= 0,
	DBSTATUS_E_BADACCESSOR	= 1,
	DBSTATUS_E_CANTCONVERTVALUE	= 2,
	DBSTATUS_S_ISNULL	= 3,
	DBSTATUS_S_TRUNCATED	= 4,
	DBSTATUS_E_SIGNMISMATCH	= 5,
	DBSTATUS_E_DATAOVERFLOW	= 6,
	DBSTATUS_E_CANTCREATE	= 7,
	DBSTATUS_E_UNAVAILABLE	= 8,
	DBSTATUS_E_PERMISSIONDENIED	= 9,
	DBSTATUS_E_INTEGRITYVIOLATION	= 10,
	DBSTATUS_E_SCHEMAVIOLATION	= 11,
	DBSTATUS_E_BADSTATUS	= 12,
	DBSTATUS_S_DEFAULT	= 13
    };
//@@@+ V2.0
#if( OLEDBVER >= 0x0200 )

enum DBSTATUSENUM20
    {	MDSTATUS_S_CELLEMPTY	= 14,
	DBSTATUS_S_IGNORE	= 15
    };
#endif // OLEDBVER >= 0x0200
//@@@- V2.0
typedef struct  tagDBBINDEXT
    {
    /* [size_is] */ BYTE __RPC_FAR *pExtension;
    ULONG ulExtension;
    }	DBBINDEXT;

typedef struct  tagDBBINDING
    {
    ULONG iOrdinal;
    ULONG obValue;
    ULONG obLength;
    ULONG obStatus;
    ITypeInfo __RPC_FAR *pTypeInfo;
    DBOBJECT __RPC_FAR *pObject;
    DBBINDEXT __RPC_FAR *pBindExt;
    DBPART dwPart;
    DBMEMOWNER dwMemOwner;
    DBPARAMIO eParamIO;
    ULONG cbMaxLen;
    DWORD dwFlags;
    DBTYPE wType;
    BYTE bPrecision;
    BYTE bScale;
    }	DBBINDING;

typedef DWORD DBROWSTATUS;


enum DBROWSTATUSENUM
    {	DBROWSTATUS_S_OK	= 0,
	DBROWSTATUS_S_MULTIPLECHANGES	= 2,
	DBROWSTATUS_S_PENDINGCHANGES	= 3,
	DBROWSTATUS_E_CANCELED	= 4,
	DBROWSTATUS_E_CANTRELEASE	= 6,
	DBROWSTATUS_E_CONCURRENCYVIOLATION	= 7,
	DBROWSTATUS_E_DELETED	= 8,
	DBROWSTATUS_E_PENDINGINSERT	= 9,
	DBROWSTATUS_E_NEWLYINSERTED	= 10,
	DBROWSTATUS_E_INTEGRITYVIOLATION	= 11,
	DBROWSTATUS_E_INVALID	= 12,
	DBROWSTATUS_E_MAXPENDCHANGESEXCEEDED	= 13,
	DBROWSTATUS_E_OBJECTOPEN	= 14,
	DBROWSTATUS_E_OUTOFMEMORY	= 15,
	DBROWSTATUS_E_PERMISSIONDENIED	= 16,
	DBROWSTATUS_E_LIMITREACHED	= 17,
	DBROWSTATUS_E_SCHEMAVIOLATION	= 18,
	DBROWSTATUS_E_FAIL	= 19
    };
//@@@+ V2.0
#if( OLEDBVER >= 0x0200 )

enum DBROWSTATUSENUM20
    {	DBROWSTATUS_S_NOCHANGE	= 20
    };
#endif // OLEDBVER >= 0x0200
//@@@- V2.0
typedef ULONG HACCESSOR;

#define DB_NULL_HACCESSOR 0x00 // deprecated; use DB_INVALID_HACCESSOR instead
#define DB_INVALID_HACCESSOR 0x00
typedef ULONG HROW;

#define DB_NULL_HROW 0x00
typedef ULONG HWATCHREGION;

#define DBWATCHREGION_NULL NULL
typedef ULONG HCHAPTER;

#define DB_NULL_HCHAPTER 0x00
#define DB_INVALID_HCHAPTER 0x00	// deprecated; use DB_NULL_HCHAPTER instead
typedef struct  tagDBFAILUREINFO
    {
    HROW hRow;
    ULONG iColumn;
    HRESULT failure;
    }	DBFAILUREINFO;

typedef DWORD DBCOLUMNFLAGS;


enum DBCOLUMNFLAGSENUM
    {	DBCOLUMNFLAGS_ISBOOKMARK	= 0x1,
	DBCOLUMNFLAGS_MAYDEFER	= 0x2,
	DBCOLUMNFLAGS_WRITE	= 0x4,
	DBCOLUMNFLAGS_WRITEUNKNOWN	= 0x8,
	DBCOLUMNFLAGS_ISFIXEDLENGTH	= 0x10,
	DBCOLUMNFLAGS_ISNULLABLE	= 0x20,
	DBCOLUMNFLAGS_MAYBENULL	= 0x40,
	DBCOLUMNFLAGS_ISLONG	= 0x80,
	DBCOLUMNFLAGS_ISROWID	= 0x100,
	DBCOLUMNFLAGS_ISROWVER	= 0x200,
	DBCOLUMNFLAGS_CACHEDEFERRED	= 0x1000
    };
//@@@+ V2.0
#if( OLEDBVER >= 0x0200 )

enum DBCOLUMNFLAGSENUM20
    {	DBCOLUMNFLAGS_SCALEISNEGATIVE	= 0x4000,
	DBCOLUMNFLAGS_KEYCOLUMN	= 0x8000
    };
#endif // OLEDBVER >= 0x0200
//@@@- V2.0
//@@@+ V1.5
#if( OLEDBVER >= 0x0150 )

enum DBCOLUMNFLAGS15ENUM
    {	DBCOLUMNFLAGS_ISCHAPTER	= 0x2000
    };
#endif // OLEDBVER >= 0x0150
//@@@- V1.5
typedef struct  tagDBCOLUMNINFO
    {
    LPOLESTR pwszName;
    ITypeInfo __RPC_FAR *pTypeInfo;
    ULONG iOrdinal;
    DBCOLUMNFLAGS dwFlags;
    ULONG ulColumnSize;
    DBTYPE wType;
    BYTE bPrecision;
    BYTE bScale;
    DBID columnid;
    }	DBCOLUMNINFO;

typedef 
enum tagDBBOOKMARK
    {	DBBMK_INVALID	= 0,
	DBBMK_FIRST	= DBBMK_INVALID + 1,
	DBBMK_LAST	= DBBMK_FIRST + 1
    }	DBBOOKMARK;

#define STD_BOOKMARKLENGTH 1
#ifdef __cplusplus
inline BOOL IsEqualGUIDBase(const GUID &rguid1, const GUID &rguid2)
{ return !memcmp(&(rguid1.Data2), &(rguid2.Data2), sizeof(GUID) - sizeof(rguid1.Data1)); }
#else // !__cplusplus
#define IsEqualGuidBase(rguid1, rguid2) (!memcmp(&((rguid1).Data2), &((rguid2).Data2), sizeof(GUID) - sizeof((rguid1).Data1)))
#endif // __cplusplus
#define DB_INVALIDCOLUMN ULONG_MAX
#define DBCIDGUID   {0x0C733A81L,0x2A1C,0x11CE,{0xAD,0xE5,0x00,0xAA,0x00,0x44,0x77,0x3D}}
#define DB_NULLGUID {0x00000000L,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}}
#ifdef DBINITCONSTANTS
extern const OLEDBDECLSPEC DBID DB_NULLID                      = {DB_NULLGUID, 0, (LPOLESTR)0};
extern const OLEDBDECLSPEC DBID DBCOLUMN_IDNAME                = {DBCIDGUID, DBKIND_GUID_PROPID, (LPOLESTR)2};
extern const OLEDBDECLSPEC DBID DBCOLUMN_NAME                  = {DBCIDGUID, DBKIND_GUID_PROPID, (LPOLESTR)3};
extern const OLEDBDECLSPEC DBID DBCOLUMN_NUMBER                = {DBCIDGUID, DBKIND_GUID_PROPID, (LPOLESTR)4};
extern const OLEDBDECLSPEC DBID DBCOLUMN_TYPE                  = {DBCIDGUID, DBKIND_GUID_PROPID, (LPOLESTR)5};
extern const OLEDBDECLSPEC DBID DBCOLUMN_PRECISION             = {DBCIDGUID, DBKIND_GUID_PROPID, (LPOLESTR)7};
extern const OLEDBDECLSPEC DBID DBCOLUMN_SCALE                 = {DBCIDGUID, DBKIND_GUID_PROPID, (LPOLESTR)8};
extern const OLEDBDECLSPEC DBID DBCOLUMN_FLAGS                 = {DBCIDGUID, DBKIND_GUID_PROPID, (LPOLESTR)9};
extern const OLEDBDECLSPEC DBID DBCOLUMN_BASECOLUMNNAME        = {DBCIDGUID, DBKIND_GUID_PROPID, (LPOLESTR)10};
extern const OLEDBDECLSPEC DBID DBCOLUMN_BASETABLENAME         = {DBCIDGUID, DBKIND_GUID_PROPID, (LPOLESTR)11};
extern const OLEDBDECLSPEC DBID DBCOLUMN_COLLATINGSEQUENCE     = {DBCIDGUID, DBKIND_GUID_PROPID, (LPOLESTR)12};
extern const OLEDBDECLSPEC DBID DBCOLUMN_COMPUTEMODE           = {DBCIDGUID, DBKIND_GUID_PROPID, (LPOLESTR)13};
extern const OLEDBDECLSPEC DBID DBCOLUMN_DEFAULTVALUE          = {DBCIDGUID, DBKIND_GUID_PROPID, (LPOLESTR)14};
extern const OLEDBDECLSPEC DBID DBCOLUMN_DOMAINNAME            = {DBCIDGUID, DBKIND_GUID_PROPID, (LPOLESTR)15};
extern const OLEDBDECLSPEC DBID DBCOLUMN_HASDEFAULT            = {DBCIDGUID, DBKIND_GUID_PROPID, (LPOLESTR)16};
extern const OLEDBDECLSPEC DBID DBCOLUMN_ISAUTOINCREMENT       = {DBCIDGUID, DBKIND_GUID_PROPID, (LPOLESTR)17};
extern const OLEDBDECLSPEC DBID DBCOLUMN_ISCASESENSITIVE       = {DBCIDGUID, DBKIND_GUID_PROPID, (LPOLESTR)18};
extern const OLEDBDECLSPEC DBID DBCOLUMN_ISSEARCHABLE          = {DBCIDGUID, DBKIND_GUID_PROPID, (LPOLESTR)20};
extern const OLEDBDECLSPEC DBID DBCOLUMN_ISUNIQUE              = {DBCIDGUID, DBKIND_GUID_PROPID, (LPOLESTR)21};
extern const OLEDBDECLSPEC DBID DBCOLUMN_BASECATALOGNAME       = {DBCIDGUID, DBKIND_GUID_PROPID, (LPOLESTR)23};
extern const OLEDBDECLSPEC DBID DBCOLUMN_BASESCHEMANAME        = {DBCIDGUID, DBKIND_GUID_PROPID, (LPOLESTR)24};
extern const OLEDBDECLSPEC DBID DBCOLUMN_GUID                  = {DBCIDGUID, DBKIND_GUID_PROPID, (LPOLESTR)29};
extern const OLEDBDECLSPEC DBID DBCOLUMN_PROPID                = {DBCIDGUID, DBKIND_GUID_PROPID, (LPOLESTR)30};
extern const OLEDBDECLSPEC DBID DBCOLUMN_TYPEINFO              = {DBCIDGUID, DBKIND_GUID_PROPID, (LPOLESTR)31};
extern const OLEDBDECLSPEC DBID DBCOLUMN_DOMAINCATALOG         = {DBCIDGUID, DBKIND_GUID_PROPID, (LPOLESTR)32};
extern const OLEDBDECLSPEC DBID DBCOLUMN_DOMAINSCHEMA          = {DBCIDGUID, DBKIND_GUID_PROPID, (LPOLESTR)33};
extern const OLEDBDECLSPEC DBID DBCOLUMN_DATETIMEPRECISION     = {DBCIDGUID, DBKIND_GUID_PROPID, (LPOLESTR)34};
extern const OLEDBDECLSPEC DBID DBCOLUMN_NUMERICPRECISIONRADIX = {DBCIDGUID, DBKIND_GUID_PROPID, (LPOLESTR)35};
extern const OLEDBDECLSPEC DBID DBCOLUMN_OCTETLENGTH           = {DBCIDGUID, DBKIND_GUID_PROPID, (LPOLESTR)36};
extern const OLEDBDECLSPEC DBID DBCOLUMN_COLUMNSIZE            = {DBCIDGUID, DBKIND_GUID_PROPID, (LPOLESTR)37};
extern const OLEDBDECLSPEC DBID DBCOLUMN_CLSID                 = {DBCIDGUID, DBKIND_GUID_PROPID, (LPOLESTR)38};
//@@@+ V1.5
#if( OLEDBVER >= 0x0150 )
extern const OLEDBDECLSPEC DBID DBCOLUMN_MAYSORT               = {DBCIDGUID, DBKIND_GUID_PROPID, (LPOLESTR)39};
#endif // OLEDBVER >= 0x0150
//@@@- V1.5
#else // !DBINITCONSTANTS
extern const DBID DB_NULLID;
extern const DBID DBCOLUMN_IDNAME;
extern const DBID DBCOLUMN_NAME;
extern const DBID DBCOLUMN_NUMBER;
extern const DBID DBCOLUMN_TYPE;
extern const DBID DBCOLUMN_PRECISION;
extern const DBID DBCOLUMN_SCALE;
extern const DBID DBCOLUMN_FLAGS;
extern const DBID DBCOLUMN_BASECOLUMNNAME;
extern const DBID DBCOLUMN_BASETABLENAME;
extern const DBID DBCOLUMN_COLLATINGSEQUENCE;
extern const DBID DBCOLUMN_COMPUTEMODE;
extern const DBID DBCOLUMN_DEFAULTVALUE;
extern const DBID DBCOLUMN_DOMAINNAME;
extern const DBID DBCOLUMN_HASDEFAULT;
extern const DBID DBCOLUMN_ISAUTOINCREMENT;
extern const DBID DBCOLUMN_ISCASESENSITIVE;
extern const DBID DBCOLUMN_ISSEARCHABLE;
extern const DBID DBCOLUMN_ISUNIQUE;
extern const DBID DBCOLUMN_BASECATALOGNAME;
extern const DBID DBCOLUMN_BASESCHEMANAME;
extern const DBID DBCOLUMN_GUID;
extern const DBID DBCOLUMN_PROPID;
extern const DBID DBCOLUMN_TYPEINFO;
extern const DBID DBCOLUMN_DOMAINCATALOG;
extern const DBID DBCOLUMN_DOMAINSCHEMA;
extern const DBID DBCOLUMN_DATETIMEPRECISION;
extern const DBID DBCOLUMN_NUMERICPRECISIONRADIX;
extern const DBID DBCOLUMN_OCTETLENGTH;
extern const DBID DBCOLUMN_COLUMNSIZE;
extern const DBID DBCOLUMN_CLSID;
//@@@+ V1.5
#if( OLEDBVER >= 0x0150 )
extern const DBID DBCOLUMN_MAYSORT;
#endif // OLEDBVER >= 0x0150
//@@@- V1.5
#endif // DBINITCONSTANTS
#ifdef DBINITCONSTANTS
//@@@+ V2.0
#if( OLEDBVER >= 0x0200 )
extern const OLEDBDECLSPEC GUID DBSCHEMA_TABLES_INFO                   = {0xc8b522e0,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID MDGUID_MDX                             = {0xa07cccd0,0x8148,0x11d0,{0x87,0xbb,0x00,0xc0,0x4f,0xc3,0x39,0x42}};
extern const OLEDBDECLSPEC GUID DBGUID_MDX                             = {0xa07cccd0,0x8148,0x11d0,{0x87,0xbb,0x00,0xc0,0x4f,0xc3,0x39,0x42}};
extern const OLEDBDECLSPEC GUID MDSCHEMA_CUBES                         = {0xc8b522d8,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID MDSCHEMA_DIMENSIONS                    = {0xc8b522d9,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID MDSCHEMA_HIERARCHIES                   = {0xc8b522da,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID MDSCHEMA_LEVELS                        = {0xc8b522db,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID MDSCHEMA_MEASURES                      = {0xc8b522dc,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID MDSCHEMA_PROPERTIES                    = {0xc8b522dd,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID MDSCHEMA_MEMBERS                       = {0xc8b522de,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC DBID DBCOLUMN_BASETABLEVERSION				= {DBCIDGUID, DBKIND_GUID_PROPID, (LPOLESTR)40};
extern const OLEDBDECLSPEC DBID DBCOLUMN_KEYCOLUMN						= {DBCIDGUID, DBKIND_GUID_PROPID, (LPOLESTR)41};
#endif // OLEDBVER >= 0x0200
//@@@- V2.0
//@@@+ V2.1
#if( OLEDBVER >= 0x0210 )
extern const OLEDBDECLSPEC GUID DBPROPSET_TRUSTEE						= {0xc8b522e1,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBOBJECT_TABLE 						= {0xc8b522e2,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBOBJECT_COLUMN 						= {0xc8b522e4,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBOBJECT_DATABASE						= {0xc8b522e5,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBOBJECT_PROCEDURE 					= {0xc8b522e6,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBOBJECT_VIEW	 						= {0xc8b522e7,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBOBJECT_SCHEMA						= {0xc8b522e8,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBOBJECT_DOMAIN	 					= {0xc8b522e9,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBOBJECT_COLLATION 					= {0xc8b522ea,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBOBJECT_TRUSTEE	 					= {0xc8b522eb,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBOBJECT_SCHEMAROWSET					= {0xc8b522ec,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBOBJECT_CHARACTERSET	 				= {0xc8b522ed,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBOBJECT_TRANSLATION 					= {0xc8b522ee,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
#endif // OLEDBVER >= 0x0210
//@@@- V2.1
//@@@+ V2.5
#if( OLEDBVER >= 0x0250 )
extern const OLEDBDECLSPEC GUID DB_PROPERTY_CHECK_OPTION               = {0xc8b5220b,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DB_PROPERTY_CONSTRAINT_CHECK_DEFERRED  = {0xc8b521f0,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DB_PROPERTY_DROP_CASCADE               = {0xc8b521f3,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DB_PROPERTY_UNIQUE                     = {0xc8b521f5,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DB_PROPERTY_ON_COMMIT_PRESERVE_ROWS    = {0xc8b52230,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DB_PROPERTY_PRIMARY                    = {0xc8b521fc,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DB_PROPERTY_CLUSTERED                  = {0xc8b521ff,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DB_PROPERTY_NONCLUSTERED               = {0xc8b52200,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DB_PROPERTY_BTREE                      = {0xc8b52201,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DB_PROPERTY_HASH                       = {0xc8b52202,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DB_PROPERTY_FILLFACTOR                 = {0xc8b52203,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DB_PROPERTY_INITIALSIZE                = {0xc8b52204,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DB_PROPERTY_DISALLOWNULL               = {0xc8b52205,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DB_PROPERTY_IGNORENULL                 = {0xc8b52206,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DB_PROPERTY_IGNOREANYNULL              = {0xc8b52207,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DB_PROPERTY_SORTBOOKMARKS              = {0xc8b52208,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DB_PROPERTY_AUTOMATICUPDATE            = {0xc8b52209,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DB_PROPERTY_EXPLICITUPDATE             = {0xc8b5220a,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBGUID_LIKE_SQL                        = {0xc8b521f6,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBGUID_LIKE_DOS                        = {0xc8b521f7,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBGUID_LIKE_OFS                        = {0xc8b521f8,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBGUID_LIKE_MAPI                       = {0xc8b521f9,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
#endif // OLEDBVER >= 0x0250
//@@@- V2.5
extern const OLEDBDECLSPEC GUID DBSCHEMA_ASSERTIONS                    = {0xc8b52210,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBSCHEMA_CATALOGS                      = {0xc8b52211,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBSCHEMA_CHARACTER_SETS                = {0xc8b52212,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBSCHEMA_COLLATIONS                    = {0xc8b52213,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBSCHEMA_COLUMNS                       = {0xc8b52214,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBSCHEMA_CHECK_CONSTRAINTS             = {0xc8b52215,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBSCHEMA_CONSTRAINT_COLUMN_USAGE       = {0xc8b52216,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBSCHEMA_CONSTRAINT_TABLE_USAGE        = {0xc8b52217,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBSCHEMA_KEY_COLUMN_USAGE              = {0xc8b52218,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBSCHEMA_REFERENTIAL_CONSTRAINTS       = {0xc8b52219,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBSCHEMA_TABLE_CONSTRAINTS             = {0xc8b5221a,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBSCHEMA_COLUMN_DOMAIN_USAGE           = {0xc8b5221b,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBSCHEMA_INDEXES                       = {0xc8b5221e,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBSCHEMA_COLUMN_PRIVILEGES             = {0xc8b52221,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBSCHEMA_TABLE_PRIVILEGES              = {0xc8b52222,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBSCHEMA_USAGE_PRIVILEGES              = {0xc8b52223,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBSCHEMA_PROCEDURES                    = {0xc8b52224,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBSCHEMA_SCHEMATA                      = {0xc8b52225,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBSCHEMA_SQL_LANGUAGES                 = {0xc8b52226,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBSCHEMA_STATISTICS                    = {0xc8b52227,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBSCHEMA_TABLES                        = {0xc8b52229,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBSCHEMA_TRANSLATIONS                  = {0xc8b5222a,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBSCHEMA_PROVIDER_TYPES                = {0xc8b5222c,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBSCHEMA_VIEWS                         = {0xc8b5222d,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBSCHEMA_VIEW_COLUMN_USAGE             = {0xc8b5222e,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBSCHEMA_VIEW_TABLE_USAGE              = {0xc8b5222f,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBSCHEMA_PROCEDURE_PARAMETERS          = {0xc8b522b8,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBSCHEMA_FOREIGN_KEYS                  = {0xc8b522c4,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBSCHEMA_PRIMARY_KEYS                  = {0xc8b522c5,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBSCHEMA_PROCEDURE_COLUMNS             = {0xc8b522c9,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBCOL_SELFCOLUMNS                      = {0xc8b52231,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBCOL_SPECIALCOL                       = {0xc8b52232,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID PSGUID_QUERY                           = {0x49691c90,0x7e17,0x101a,{0xa9,0x1c,0x08,0x00,0x2b,0x2e,0xcd,0xa9}};
extern const OLEDBDECLSPEC GUID DBPROPSET_COLUMN                       = {0xc8b522b9,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBPROPSET_DATASOURCE                   = {0xc8b522ba,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBPROPSET_DATASOURCEINFO               = {0xc8b522bb,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBPROPSET_DBINIT                       = {0xc8b522bc,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBPROPSET_INDEX                        = {0xc8b522bd,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBPROPSET_ROWSET                       = {0xc8b522be,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBPROPSET_TABLE                        = {0xc8b522bf,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBPROPSET_DATASOURCEALL                = {0xc8b522c0,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBPROPSET_DATASOURCEINFOALL            = {0xc8b522c1,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBPROPSET_ROWSETALL                    = {0xc8b522c2,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBPROPSET_SESSION                      = {0xc8b522c6,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBPROPSET_SESSIONALL                   = {0xc8b522c7,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBPROPSET_DBINITALL                    = {0xc8b522ca,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBPROPSET_PROPERTIESINERROR            = {0xc8b522d4,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
//@@@+ V1.5
#if( OLEDBVER >= 0x0150 )
extern const OLEDBDECLSPEC GUID DBPROPSET_VIEW                         = {0xc8b522df,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
#endif // OLEDBVER >= 0x0150
//@@@- V1.5
// DBGUID_DBSQL is deprecated; use DBGUID_DEFAULT instead
extern const OLEDBDECLSPEC  GUID DBGUID_DBSQL                           = {0xc8b521fb,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBGUID_DEFAULT                         = {0xc8b521fb,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
extern const OLEDBDECLSPEC GUID DBGUID_SQL                             = {0xc8b522d7,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};
#else // !DBINITCONSTANTS
//@@@+ V2.0
#if( OLEDBVER >= 0x0200 )
extern const GUID DBSCHEMA_TABLES_INFO;
extern const GUID MDGUID_MDX;
extern const GUID DBGUID_MDX;
extern const GUID MDSCHEMA_CUBES;
extern const GUID MDSCHEMA_DIMENSIONS;
extern const GUID MDSCHEMA_HIERARCHIES;
extern const GUID MDSCHEMA_LEVELS;
extern const GUID MDSCHEMA_MEASURES;
extern const GUID MDSCHEMA_PROPERTIES;
extern const GUID MDSCHEMA_MEMBERS;
extern const DBID DBCOLUMN_BASETABLEVERSION;
extern const DBID DBCOLUMN_KEYCOLUMN;
#endif // OLEDBVER >= 0x0200
//@@@- V2.0
//@@@+ V2.1
#if( OLEDBVER >= 0x0210 )
extern const GUID DBPROPSET_TRUSTEE;
extern const GUID DBOBJECT_TABLE;
extern const GUID DBOBJECT_COLUMN;
extern const GUID DBOBJECT_DATABASE;
extern const GUID DBOBJECT_PROCEDURE;
extern const GUID DBOBJECT_VIEW;
extern const GUID DBOBJECT_SCHEMA;
extern const GUID DBOBJECT_DOMAIN;
extern const GUID DBOBJECT_COLLATION;
extern const GUID DBOBJECT_TRUSTEE;
extern const GUID DBOBJECT_SCHEMAROWSET;
extern const GUID DBOBJECT_CHARACTERSET;
extern const GUID DBOBJECT_TRANSLATION;
#endif // OLEDBVER >= 0x0210
//@@@- V2.1
//@@@+ V2.5
#if( OLEDBVER >= 0x0250 )
extern const GUID DB_PROPERTY_CHECK_OPTION;
extern const GUID DB_PROPERTY_CONSTRAINT_CHECK_DEFERRED;
extern const GUID DB_PROPERTY_DROP_CASCADE;
extern const GUID DB_PROPERTY_ON_COMMIT_PRESERVE_ROWS;
extern const GUID DB_PROPERTY_UNIQUE;
extern const GUID DB_PROPERTY_PRIMARY;
extern const GUID DB_PROPERTY_CLUSTERED;
extern const GUID DB_PROPERTY_NONCLUSTERED;
extern const GUID DB_PROPERTY_BTREE;
extern const GUID DB_PROPERTY_HASH;
extern const GUID DB_PROPERTY_FILLFACTOR;
extern const GUID DB_PROPERTY_INITIALSIZE;
extern const GUID DB_PROPERTY_DISALLOWNULL;
extern const GUID DB_PROPERTY_IGNORENULL;
extern const GUID DB_PROPERTY_IGNOREANYNULL;
extern const GUID DB_PROPERTY_SORTBOOKMARKS;
extern const GUID DB_PROPERTY_AUTOMATICUPDATE;
extern const GUID DB_PROPERTY_EXPLICITUPDATE;
extern const GUID DBGUID_LIKE_SQL;
extern const GUID DBGUID_LIKE_DOS;
extern const GUID DBGUID_LIKE_OFS;
extern const GUID DBGUID_LIKE_MAPI;
#endif // OLEDBVER >= 0x0250
//@@@- V2.5
extern const GUID DBSCHEMA_ASSERTIONS;
extern const GUID DBSCHEMA_CATALOGS;
extern const GUID DBSCHEMA_CHARACTER_SETS;
extern const GUID DBSCHEMA_COLLATIONS;
extern const GUID DBSCHEMA_COLUMNS;
extern const GUID DBSCHEMA_CHECK_CONSTRAINTS;
extern const GUID DBSCHEMA_CONSTRAINT_COLUMN_USAGE;
extern const GUID DBSCHEMA_CONSTRAINT_TABLE_USAGE;
extern const GUID DBSCHEMA_KEY_COLUMN_USAGE;
extern const GUID DBSCHEMA_REFERENTIAL_CONSTRAINTS;
extern const GUID DBSCHEMA_TABLE_CONSTRAINTS;
extern const GUID DBSCHEMA_COLUMN_DOMAIN_USAGE;
extern const GUID DBSCHEMA_INDEXES;
extern const GUID DBSCHEMA_COLUMN_PRIVILEGES;
extern const GUID DBSCHEMA_TABLE_PRIVILEGES;
extern const GUID DBSCHEMA_USAGE_PRIVILEGES;
extern const GUID DBSCHEMA_PROCEDURES;
extern const GUID DBSCHEMA_SCHEMATA;
extern const GUID DBSCHEMA_SQL_LANGUAGES;
extern const GUID DBSCHEMA_STATISTICS;
extern const GUID DBSCHEMA_TABLES;
extern const GUID DBSCHEMA_TRANSLATIONS;
extern const GUID DBSCHEMA_PROVIDER_TYPES;
extern const GUID DBSCHEMA_VIEWS;
extern const GUID DBSCHEMA_VIEW_COLUMN_USAGE;
extern const GUID DBSCHEMA_VIEW_TABLE_USAGE;
extern const GUID DBSCHEMA_PROCEDURE_PARAMETERS;
extern const GUID DBSCHEMA_FOREIGN_KEYS;
extern const GUID DBSCHEMA_PRIMARY_KEYS;
extern const GUID DBSCHEMA_PROCEDURE_COLUMNS;
extern const GUID DBCOL_SELFCOLUMNS;
extern const GUID DBCOL_SPECIALCOL;
extern const GUID PSGUID_QUERY;
extern const GUID DBPROPSET_COLUMN;
extern const GUID DBPROPSET_DATASOURCE;
extern const GUID DBPROPSET_DATASOURCEINFO;
extern const GUID DBPROPSET_DBINIT;
extern const GUID DBPROPSET_INDEX;
extern const GUID DBPROPSET_ROWSET;
extern const GUID DBPROPSET_TABLE;
extern const GUID DBPROPSET_DATASOURCEALL;
extern const GUID DBPROPSET_DATASOURCEINFOALL;
extern const GUID DBPROPSET_ROWSETALL;
extern const GUID DBPROPSET_SESSION;
extern const GUID DBPROPSET_SESSIONALL;
extern const GUID DBPROPSET_DBINITALL;
extern const GUID DBPROPSET_PROPERTIESINERROR;
//@@@+ V1.5
#if( OLEDBVER >= 0x0150 )
extern const GUID DBPROPSET_VIEW;
#endif // OLEDBVER >= 0x0150
//@@@- V1.5
// DBGUID_DBSQL is deprecated; use DBGUID_DEFAULT instead
extern const GUID DBGUID_DBSQL;
extern const GUID DBGUID_DEFAULT;
extern const GUID DBGUID_SQL;
#endif // DBINITCONSTANTS

enum DBPROPENUM
    {	DBPROP_ABORTPRESERVE	= 0x2L,
	DBPROP_ACTIVESESSIONS	= 0x3L,
	DBPROP_APPENDONLY	= 0xbbL,
	DBPROP_ASYNCTXNABORT	= 0xa8L,
	DBPROP_ASYNCTXNCOMMIT	= 0x4L,
	DBPROP_AUTH_CACHE_AUTHINFO	= 0x5L,
	DBPROP_AUTH_ENCRYPT_PASSWORD	= 0x6L,
	DBPROP_AUTH_INTEGRATED	= 0x7L,
	DBPROP_AUTH_MASK_PASSWORD	= 0x8L,
	DBPROP_AUTH_PASSWORD	= 0x9L,
	DBPROP_AUTH_PERSIST_ENCRYPTED	= 0xaL,
	DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO	= 0xbL,
	DBPROP_AUTH_USERID	= 0xcL,
	DBPROP_BLOCKINGSTORAGEOBJECTS	= 0xdL,
	DBPROP_BOOKMARKS	= 0xeL,
	DBPROP_BOOKMARKSKIPPED	= 0xfL,
	DBPROP_BOOKMARKTYPE	= 0x10L,
	DBPROP_BYREFACCESSORS	= 0x78L,
	DBPROP_CACHEDEFERRED	= 0x11L,
	DBPROP_CANFETCHBACKWARDS	= 0x12L,
	DBPROP_CANHOLDROWS	= 0x13L,
	DBPROP_CANSCROLLBACKWARDS	= 0x15L,
	DBPROP_CATALOGLOCATION	= 0x16L,
	DBPROP_CATALOGTERM	= 0x17L,
	DBPROP_CATALOGUSAGE	= 0x18L,
	DBPROP_CHANGEINSERTEDROWS	= 0xbcL,
	DBPROP_COL_AUTOINCREMENT	= 0x1aL,
	DBPROP_COL_DEFAULT	= 0x1bL,
	DBPROP_COL_DESCRIPTION	= 0x1cL,
	DBPROP_COL_FIXEDLENGTH	= 0xa7L,
	DBPROP_COL_NULLABLE	= 0x1dL,
	DBPROP_COL_PRIMARYKEY	= 0x1eL,
	DBPROP_COL_UNIQUE	= 0x1fL,
	DBPROP_COLUMNDEFINITION	= 0x20L,
	DBPROP_COLUMNRESTRICT	= 0x21L,
	DBPROP_COMMANDTIMEOUT	= 0x22L,
	DBPROP_COMMITPRESERVE	= 0x23L,
	DBPROP_CONCATNULLBEHAVIOR	= 0x24L,
	DBPROP_CURRENTCATALOG	= 0x25L,
	DBPROP_DATASOURCENAME	= 0x26L,
	DBPROP_DATASOURCEREADONLY	= 0x27L,
	DBPROP_DBMSNAME	= 0x28L,
	DBPROP_DBMSVER	= 0x29L,
	DBPROP_DEFERRED	= 0x2aL,
	DBPROP_DELAYSTORAGEOBJECTS	= 0x2bL,
	DBPROP_DSOTHREADMODEL	= 0xa9L,
	DBPROP_GROUPBY	= 0x2cL,
	DBPROP_HETEROGENEOUSTABLES	= 0x2dL,
	DBPROP_IAccessor	= 0x79L,
	DBPROP_IColumnsInfo	= 0x7aL,
	DBPROP_IColumnsRowset	= 0x7bL,
	DBPROP_IConnectionPointContainer	= 0x7cL,
	DBPROP_IConvertType	= 0xc2L,
	DBPROP_IRowset	= 0x7eL,
	DBPROP_IRowsetChange	= 0x7fL,
	DBPROP_IRowsetIdentity	= 0x80L,
	DBPROP_IRowsetIndex	= 0x9fL,
	DBPROP_IRowsetInfo	= 0x81L,
	DBPROP_IRowsetLocate	= 0x82L,
	DBPROP_IRowsetResynch	= 0x84L,
	DBPROP_IRowsetScroll	= 0x85L,
	DBPROP_IRowsetUpdate	= 0x86L,
	DBPROP_ISupportErrorInfo	= 0x87L,
	DBPROP_ILockBytes	= 0x88L,
	DBPROP_ISequentialStream	= 0x89L,
	DBPROP_IStorage	= 0x8aL,
	DBPROP_IStream	= 0x8bL,
	DBPROP_IDENTIFIERCASE	= 0x2eL,
	DBPROP_IMMOBILEROWS	= 0x2fL,
	DBPROP_INDEX_AUTOUPDATE	= 0x30L,
	DBPROP_INDEX_CLUSTERED	= 0x31L,
	DBPROP_INDEX_FILLFACTOR	= 0x32L,
	DBPROP_INDEX_INITIALSIZE	= 0x33L,
	DBPROP_INDEX_NULLCOLLATION	= 0x34L,
	DBPROP_INDEX_NULLS	= 0x35L,
	DBPROP_INDEX_PRIMARYKEY	= 0x36L,
	DBPROP_INDEX_SORTBOOKMARKS	= 0x37L,
	DBPROP_INDEX_TEMPINDEX	= 0xa3L,
	DBPROP_INDEX_TYPE	= 0x38L,
	DBPROP_INDEX_UNIQUE	= 0x39L,
	DBPROP_INIT_DATASOURCE	= 0x3bL,
	DBPROP_INIT_HWND	= 0x3cL,
	DBPROP_INIT_IMPERSONATION_LEVEL	= 0x3dL,
	DBPROP_INIT_LCID	= 0xbaL,
	DBPROP_INIT_LOCATION	= 0x3eL,
	DBPROP_INIT_MODE	= 0x3fL,
	DBPROP_INIT_PROMPT	= 0x40L,
	DBPROP_INIT_PROTECTION_LEVEL	= 0x41L,
	DBPROP_INIT_PROVIDERSTRING	= 0xa0L,
	DBPROP_INIT_TIMEOUT	= 0x42L,
	DBPROP_LITERALBOOKMARKS	= 0x43L,
	DBPROP_LITERALIDENTITY	= 0x44L,
	DBPROP_MARSHALLABLE	= 0xc5L,
	DBPROP_MAXINDEXSIZE	= 0x46L,
	DBPROP_MAXOPENROWS	= 0x47L,
	DBPROP_MAXPENDINGROWS	= 0x48L,
	DBPROP_MAXROWS	= 0x49L,
	DBPROP_MAXROWSIZE	= 0x4aL,
	DBPROP_MAXROWSIZEINCLUDESBLOB	= 0x4bL,
	DBPROP_MAXTABLESINSELECT	= 0x4cL,
	DBPROP_MAYWRITECOLUMN	= 0x4dL,
	DBPROP_MEMORYUSAGE	= 0x4eL,
	DBPROP_MULTIPLEPARAMSETS	= 0xbfL,
	DBPROP_MULTIPLERESULTS	= 0xc4L,
	DBPROP_MULTIPLESTORAGEOBJECTS	= 0x50L,
	DBPROP_MULTITABLEUPDATE	= 0x51L,
	DBPROP_NOTIFICATIONGRANULARITY	= 0xc6L,
	DBPROP_NOTIFICATIONPHASES	= 0x52L,
	DBPROP_NOTIFYCOLUMNSET	= 0xabL,
	DBPROP_NOTIFYROWDELETE	= 0xadL,
	DBPROP_NOTIFYROWFIRSTCHANGE	= 0xaeL,
	DBPROP_NOTIFYROWINSERT	= 0xafL,
	DBPROP_NOTIFYROWRESYNCH	= 0xb1L,
	DBPROP_NOTIFYROWSETCHANGED	= 0xd3L,
	DBPROP_NOTIFYROWSETRELEASE	= 0xb2L,
	DBPROP_NOTIFYROWSETFETCHPOSITIONCHANGE	= 0xb3L,
	DBPROP_NOTIFYROWUNDOCHANGE	= 0xb4L,
	DBPROP_NOTIFYROWUNDODELETE	= 0xb5L,
	DBPROP_NOTIFYROWUNDOINSERT	= 0xb6L,
	DBPROP_NOTIFYROWUPDATE	= 0xb7L,
	DBPROP_NULLCOLLATION	= 0x53L,
	DBPROP_OLEOBJECTS	= 0x54L,
	DBPROP_ORDERBYCOLUMNSINSELECT	= 0x55L,
	DBPROP_ORDEREDBOOKMARKS	= 0x56L,
	DBPROP_OTHERINSERT	= 0x57L,
	DBPROP_OTHERUPDATEDELETE	= 0x58L,
	DBPROP_OUTPUTPARAMETERAVAILABILITY	= 0xb8L,
	DBPROP_OWNINSERT	= 0x59L,
	DBPROP_OWNUPDATEDELETE	= 0x5aL,
	DBPROP_PERSISTENTIDTYPE	= 0xb9L,
	DBPROP_PREPAREABORTBEHAVIOR	= 0x5bL,
	DBPROP_PREPARECOMMITBEHAVIOR	= 0x5cL,
	DBPROP_PROCEDURETERM	= 0x5dL,
	DBPROP_PROVIDERNAME	= 0x60L,
	DBPROP_PROVIDEROLEDBVER	= 0x61L,
	DBPROP_PROVIDERVER	= 0x62L,
	DBPROP_QUICKRESTART	= 0x63L,
	DBPROP_QUOTEDIDENTIFIERCASE	= 0x64L,
	DBPROP_REENTRANTEVENTS	= 0x65L,
	DBPROP_REMOVEDELETED	= 0x66L,
	DBPROP_REPORTMULTIPLECHANGES	= 0x67L,
	DBPROP_RETURNPENDINGINSERTS	= 0xbdL,
	DBPROP_ROWRESTRICT	= 0x68L,
	DBPROP_ROWSETCONVERSIONSONCOMMAND	= 0xc0L,
	DBPROP_ROWTHREADMODEL	= 0x69L,
	DBPROP_SCHEMATERM	= 0x6aL,
	DBPROP_SCHEMAUSAGE	= 0x6bL,
	DBPROP_SERVERCURSOR	= 0x6cL,
	DBPROP_SESS_AUTOCOMMITISOLEVELS	= 0xbeL,
	DBPROP_SQLSUPPORT	= 0x6dL,
	DBPROP_STRONGIDENTITY	= 0x77L,
	DBPROP_STRUCTUREDSTORAGE	= 0x6fL,
	DBPROP_SUBQUERIES	= 0x70L,
	DBPROP_SUPPORTEDTXNDDL	= 0xa1L,
	DBPROP_SUPPORTEDTXNISOLEVELS	= 0x71L,
	DBPROP_SUPPORTEDTXNISORETAIN	= 0x72L,
	DBPROP_TABLETERM	= 0x73L,
	DBPROP_TBL_TEMPTABLE	= 0x8cL,
	DBPROP_TRANSACTEDOBJECT	= 0x74L,
	DBPROP_UPDATABILITY	= 0x75L,
	DBPROP_USERNAME	= 0x76L
    };
//@@@+ V1.5
#if( OLEDBVER >= 0x0150 )

enum DBPROPENUM15
    {	DBPROP_FILTEROPS	= 0xd0L,
	DBPROP_FILTERCOMPAREOPS	= 0xd1L,
	DBPROP_FINDCOMPAREOPS	= 0xd2L,
	DBPROP_IChapteredRowset	= 0xcaL,
	DBPROP_IDBAsynchStatus	= 0xcbL,
	DBPROP_IRowsetFind	= 0xccL,
	DBPROP_IRowsetView	= 0xd4L,
	DBPROP_IViewChapter	= 0xd5L,
	DBPROP_IViewFilter	= 0xd6L,
	DBPROP_IViewRowset	= 0xd7L,
	DBPROP_IViewSort	= 0xd8L,
	DBPROP_INIT_ASYNCH	= 0xc8L,
	DBPROP_MAXOPENCHAPTERS	= 0xc7L,
	DBPROP_MAXORSINFILTER	= 0xcdL,
	DBPROP_MAXSORTCOLUMNS	= 0xceL,
	DBPROP_ROWSET_ASYNCH	= 0xc9L,
	DBPROP_SORTONINDEX	= 0xcfL
    };
#endif // OLEDBVER >= 0x0150
//@@@- V1.5
//@@@+ V2.0
#if( OLEDBVER >= 0x0200 )
#define DBPROP_PROVIDERFILENAME DBPROP_PROVIDERNAME
#define DBPROP_SERVER_NAME DBPROP_SERVERNAME

enum DBPROPENUM20
    {	DBPROP_IMultipleResults	= 0xd9L,
	DBPROP_DATASOURCE_TYPE	= 0xfbL,
	MDPROP_AXES	= 0xfcL,
	MDPROP_FLATTENING_SUPPORT	= 0xfdL,
	MDPROP_MDX_JOINCUBES	= 0xfeL,
	MDPROP_NAMED_LEVELS	= 0xffL,
	MDPROP_RANGEROWSET	= 0x100L,
	MDPROP_MDX_SLICER	= 0xdaL,
	MDPROP_MDX_CUBEQUALIFICATION	= 0xdbL,
	MDPROP_MDX_OUTERREFERENCE	= 0xdcL,
	MDPROP_MDX_QUERYBYPROPERTY	= 0xddL,
	MDPROP_MDX_CASESUPPORT	= 0xdeL,
	MDPROP_MDX_STRING_COMPOP	= 0xe0L,
	MDPROP_MDX_DESCFLAGS	= 0xe1L,
	MDPROP_MDX_SET_FUNCTIONS	= 0xe2L,
	MDPROP_MDX_MEMBER_FUNCTIONS	= 0xe3L,
	MDPROP_MDX_NUMERIC_FUNCTIONS	= 0xe4L,
	MDPROP_MDX_FORMULAS	= 0xe5L,
	MDPROP_MDX_AGGREGATECELL_UPDATE	= 0xe6L,
	DBPROP_ACCESSORDER	= 0xe7L,
	DBPROP_BOOKMARKINFO	= 0xe8L,
	DBPROP_INIT_CATALOG	= 0xe9L,
	DBPROP_ROW_BULKOPS	= 0xeaL,
	DBPROP_PROVIDERFRIENDLYNAME	= 0xebL,
	DBPROP_LOCKMODE	= 0xecL,
	DBPROP_MULTIPLECONNECTIONS	= 0xedL,
	DBPROP_UNIQUEROWS	= 0xeeL,
	DBPROP_SERVERDATAONINSERT	= 0xefL,
	DBPROP_STORAGEFLAGS	= 0xf0L,
	DBPROP_CONNECTIONSTATUS	= 0xf4L,
	DBPROP_ALTERCOLUMN	= 0xf5L,
	DBPROP_COLUMNLCID	= 0xf6L,
	DBPROP_RESETDATASOURCE	= 0xf7L,
	DBPROP_INIT_OLEDBSERVICES	= 0xf8L,
	DBPROP_IRowsetRefresh	= 0xf9L,
	DBPROP_SERVERNAME	= 0xfaL,
	DBPROP_IParentRowset	= 0x101L,
	DBPROP_HIDDENCOLUMNS	= 0x102L,
	DBPROP_PROVIDERMEMORY	= 0x103L,
	DBPROP_CLIENTCURSOR	= 0x104L
    };
#endif // OLEDBVER >= 0x0200
//@@@- V2.0
//@@@+ V2.1
#if( OLEDBVER >= 0x0210 )

enum DBPROPENUM21
    {	DBPROP_TRUSTEE_USERNAME	= 0xf1L,
	DBPROP_TRUSTEE_AUTHENTICATION	= 0xf2L,
	DBPROP_TRUSTEE_NEWAUTHENTICATION	= 0xf3L
    };
#endif // OLEDBVER >= 0x0210
//@@@- V2.1
//@@@+ V2.5
#if( OLEDBVER >= 0x0250 )

enum DBPROPENUM25
    {	DBPROP_ICommandCost	= 0x8dL,
	DBPROP_ICommandTree	= 0x8eL,
	DBPROP_ICommandValidate	= 0x8fL,
	DBPROP_IDBSchemaCommand	= 0x90L,
	DBPROP_IProvideMoniker	= 0x7dL,
	DBPROP_IQuery	= 0x92L,
	DBPROP_IReadData	= 0x93L,
	DBPROP_IRowsetAsynch	= 0x94L,
	DBPROP_IRowsetCopyRows	= 0x95L,
	DBPROP_IRowsetKeys	= 0x97L,
	DBPROP_IRowsetNewRowAfter	= 0x98L,
	DBPROP_IRowsetNextRowset	= 0x99L,
	DBPROP_IRowsetWatchAll	= 0x9bL,
	DBPROP_IRowsetWatchNotify	= 0x9cL,
	DBPROP_IRowsetWatchRegion	= 0x9dL,
	DBPROP_IRowsetWithParameters	= 0x9eL
    };
#endif // OLEDBVER >= 0x0250
//@@@- V2.5
//@@@+ deprecated
#ifdef deprecated

enum DBPROPENUMDEPRECATED
    {	DBPROP_IRowsetExactScroll	= 0x9aL
    };
#endif // deprecated
//@@@- deprecated
#define DBPROPVAL_BMK_NUMERIC							 0x00000001L
#define DBPROPVAL_BMK_KEY								 0x00000002L
#define DBPROPVAL_CL_START                                0x00000001L
#define DBPROPVAL_CL_END                                  0x00000002L
#define DBPROPVAL_CU_DML_STATEMENTS						 0x00000001L
#define DBPROPVAL_CU_TABLE_DEFINITION					 0x00000002L
#define DBPROPVAL_CU_INDEX_DEFINITION					 0x00000004L
#define DBPROPVAL_CU_PRIVILEGE_DEFINITION				 0x00000008L
#define DBPROPVAL_CD_NOTNULL								 0x00000001L
#define DBPROPVAL_CB_NULL								 0x00000001L
#define DBPROPVAL_CB_NON_NULL							 0x00000002L
#define DBPROPVAL_FU_NOT_SUPPORTED						 0x00000001L
#define DBPROPVAL_FU_COLUMN								 0x00000002L
#define DBPROPVAL_FU_TABLE								 0x00000004L
#define DBPROPVAL_FU_CATALOG								 0x00000008L
#define DBPROPVAL_GB_NOT_SUPPORTED						 0x00000001L
#define DBPROPVAL_GB_EQUALS_SELECT						 0x00000002L
#define DBPROPVAL_GB_CONTAINS_SELECT						 0x00000004L
#define DBPROPVAL_GB_NO_RELATION							 0x00000008L
#define DBPROPVAL_HT_DIFFERENT_CATALOGS					 0x00000001L
#define DBPROPVAL_HT_DIFFERENT_PROVIDERS					 0x00000002L
#define DBPROPVAL_IC_UPPER								 0x00000001L
#define DBPROPVAL_IC_LOWER								 0x00000002L
#define DBPROPVAL_IC_SENSITIVE							 0x00000004L
#define DBPROPVAL_IC_MIXED								 0x00000008L
//@@@+ deprecated
#ifdef deprecated
#define DBPROPVAL_LM_NONE								 0x00000001L
#define DBPROPVAL_LM_READ								 0x00000002L
#define DBPROPVAL_LM_INTENT								 0x00000004L
#define DBPROPVAL_LM_RITE								 0x00000008L
#endif // deprecated
//@@@- deprecated
#define DBPROPVAL_NP_OKTODO								 0x00000001L
#define DBPROPVAL_NP_ABOUTTODO							 0x00000002L
#define DBPROPVAL_NP_SYNCHAFTER							 0x00000004L
#define DBPROPVAL_NP_FAILEDTODO							 0x00000008L
#define DBPROPVAL_NP_DIDEVENT							 0x00000010L
#define DBPROPVAL_NC_END									 0x00000001L
#define DBPROPVAL_NC_HIGH								 0x00000002L
#define DBPROPVAL_NC_LOW									 0x00000004L
#define DBPROPVAL_NC_START								 0x00000008L
#define DBPROPVAL_OO_BLOB								 0x00000001L
#define DBPROPVAL_OO_IPERSIST							 0x00000002L
#define DBPROPVAL_CB_DELETE								 0x00000001L
#define DBPROPVAL_CB_PRESERVE							 0x00000002L
#define DBPROPVAL_SU_DML_STATEMENTS						 0x00000001L
#define DBPROPVAL_SU_TABLE_DEFINITION					 0x00000002L
#define DBPROPVAL_SU_INDEX_DEFINITION					 0x00000004L
#define DBPROPVAL_SU_PRIVILEGE_DEFINITION				 0x00000008L
#define DBPROPVAL_SQ_CORRELATEDSUBQUERIES				 0x00000001L
#define DBPROPVAL_SQ_COMPARISON							 0x00000002L
#define DBPROPVAL_SQ_EXISTS								 0x00000004L
#define DBPROPVAL_SQ_IN									 0x00000008L
#define DBPROPVAL_SQ_QUANTIFIED							 0x00000010L
#define DBPROPVAL_SS_ISEQUENTIALSTREAM					 0x00000001L
#define DBPROPVAL_SS_ISTREAM								 0x00000002L
#define DBPROPVAL_SS_ISTORAGE							 0x00000004L
#define DBPROPVAL_SS_ILOCKBYTES							 0x00000008L
#define DBPROPVAL_TI_CHAOS								 0x00000010L
#define DBPROPVAL_TI_READUNCOMMITTED						 0x00000100L
#define DBPROPVAL_TI_BROWSE								 0x00000100L
#define DBPROPVAL_TI_CURSORSTABILITY						 0x00001000L
#define DBPROPVAL_TI_READCOMMITTED						 0x00001000L
#define DBPROPVAL_TI_REPEATABLEREAD						 0x00010000L
#define DBPROPVAL_TI_SERIALIZABLE						 0x00100000L
#define DBPROPVAL_TI_ISOLATED							 0x00100000L
#define DBPROPVAL_TR_COMMIT_DC							 0x00000001L
#define DBPROPVAL_TR_COMMIT								 0x00000002L
#define DBPROPVAL_TR_COMMIT_NO							 0x00000004L
#define DBPROPVAL_TR_ABORT_DC							 0x00000008L
#define DBPROPVAL_TR_ABORT								 0x00000010L
#define DBPROPVAL_TR_ABORT_NO							 0x00000020L
#define DBPROPVAL_TR_DONTCARE							 0x00000040L
#define DBPROPVAL_TR_BOTH								 0x00000080L
#define DBPROPVAL_TR_NONE								 0x00000100L
#define DBPROPVAL_TR_OPTIMISTIC							 0x00000200L
#define DBPROPVAL_RT_FREETHREAD							 0x00000001L
#define DBPROPVAL_RT_APTMTTHREAD							 0x00000002L
#define DBPROPVAL_RT_SINGLETHREAD						 0x00000004L
#define DBPROPVAL_UP_CHANGE								 0x00000001L
#define DBPROPVAL_UP_DELETE								 0x00000002L
#define DBPROPVAL_UP_INSERT								 0x00000004L
#define DBPROPVAL_SQL_NONE								 0x00000000L
#define DBPROPVAL_SQL_ODBC_MINIMUM						 0x00000001L
#define DBPROPVAL_SQL_ODBC_CORE							 0x00000002L
#define DBPROPVAL_SQL_ODBC_EXTENDED						 0x00000004L
#define DBPROPVAL_SQL_ANSI89_IEF							 0x00000008L
#define DBPROPVAL_SQL_ANSI92_ENTRY						 0x00000010L
#define DBPROPVAL_SQL_FIPS_TRANSITIONAL					 0x00000020L
#define DBPROPVAL_SQL_ANSI92_INTERMEDIATE				 0x00000040L
#define DBPROPVAL_SQL_ANSI92_FULL						 0x00000080L
#define DBPROPVAL_SQL_ESCAPECLAUSES						 0x00000100L
#define DBPROPVAL_IT_BTREE                                0x00000001L
#define DBPROPVAL_IT_HASH                                 0x00000002L
#define DBPROPVAL_IT_CONTENT                              0x00000003L
#define DBPROPVAL_IT_OTHER                                0x00000004L
#define DBPROPVAL_IN_DISALLOWNULL                         0x00000001L
#define DBPROPVAL_IN_IGNORENULL                           0x00000002L
#define DBPROPVAL_IN_IGNOREANYNULL                        0x00000004L
#define DBPROPVAL_TC_NONE                                 0x00000000L
#define DBPROPVAL_TC_DML                                  0x00000001L
#define DBPROPVAL_TC_DDL_COMMIT                           0x00000002L
#define DBPROPVAL_TC_DDL_IGNORE                           0x00000004L
#define DBPROPVAL_TC_ALL                                  0x00000008L
#define DBPROPVAL_NP_OKTODO                               0x00000001L
#define DBPROPVAL_NP_ABOUTTODO                            0x00000002L
#define DBPROPVAL_NP_SYNCHAFTER                           0x00000004L
#define DBPROPVAL_OA_NOTSUPPORTED                         0x00000001L
#define DBPROPVAL_OA_ATEXECUTE                            0x00000002L
#define DBPROPVAL_OA_ATROWRELEASE                         0x00000004L
#define DBPROPVAL_MR_NOTSUPPORTED                         0x00000000L
#define DBPROPVAL_MR_SUPPORTED                            0x00000001L
#define DBPROPVAL_MR_CONCURRENT                           0x00000002L
#define DBPROPVAL_PT_GUID_NAME                            0x00000001L
#define DBPROPVAL_PT_GUID_PROPID                          0x00000002L
#define DBPROPVAL_PT_NAME                                 0x00000004L
#define DBPROPVAL_PT_GUID                                 0x00000008L
#define DBPROPVAL_PT_PROPID								 0x00000010L
#define DBPROPVAL_PT_PGUID_NAME                           0x00000020L
#define DBPROPVAL_PT_PGUID_PROPID						 0x00000040L
#define DBPROPVAL_NT_SINGLEROW                            0x00000001L
#define DBPROPVAL_NT_MULTIPLEROWS                         0x00000002L
//@@@+ V1.5
#if( OLEDBVER >= 0x0150 )
#define DBPROPVAL_ASYNCH_INITIALIZE                       0x00000001L
#define DBPROPVAL_ASYNCH_SEQUENTIALPOPULATION             0x00000002L
#define DBPROPVAL_ASYNCH_RANDOMPOPULATION                 0x00000004L
#define DBPROPVAL_OP_EQUAL                                0x00000001L
#define DBPROPVAL_OP_RELATIVE                             0x00000002L
#define DBPROPVAL_OP_STRING                               0x00000004L
#define DBPROPVAL_CO_EQUALITY                             0x00000001L
#define DBPROPVAL_CO_STRING                               0x00000002L
#define DBPROPVAL_CO_CASESENSITIVE                        0x00000004L
#define DBPROPVAL_CO_CASEINSENSITIVE                      0x00000008L
#endif // OLEDBVER >= 0x0150
//@@@- V1.5
//@@@+ V2.0
#if( OLEDBVER >= 0x0200 )
#define DBPROPVAL_CO_CONTAINS		                     0x00000010L
#define DBPROPVAL_CO_BEGINSWITH		                     0x00000020L
#define DBPROPVAL_ASYNCH_BACKGROUNDPOPULATION	0x00000008L
#define DBPROPVAL_ASYNCH_PREPOPULATE				0x00000010L
#define DBPROPVAL_ASYNCH_POPULATEONDEMAND		0x00000020L
#define DBPROPVAL_LM_NONE								 0x00000001L
#define DBPROPVAL_LM_SINGLEROW							 0x00000002L
#define DBPROPVAL_SQL_SUBMINIMUM 						 0x00000200L
#define DBPROPVAL_DST_TDP                                 0x00000001L
#define DBPROPVAL_DST_MDP                                 0x00000002L
#define DBPROPVAL_DST_TDPANDMDP                           0x00000003L
#define MDPROPVAL_AU_UNSUPPORTED                          0x00000000L
#define MDPROPVAL_AU_UNCHANGED                            0x00000001L
#define MDPROPVAL_AU_UNKNOWN                              0x00000002L
#define MDPROPVAL_MF_WITH_CALCMEMBERS                     0x00000001L
#define MDPROPVAL_MF_WITH_NAMEDSETS                       0x00000002L
#define MDPROPVAL_MF_CREATE_CALCMEMBERS                   0x00000004L
#define MDPROPVAL_MF_CREATE_NAMEDSETS                     0x00000008L
#define MDPROPVAL_MF_SCOPE_SESSION						 0x00000010L
#define MDPROPVAL_MF_SCOPE_GLOBAL                         0x00000020L
#define MDPROPVAL_MMF_COUSIN                              0x00000001L
#define MDPROPVAL_MMF_PARALLELPERIOD                      0x00000002L
#define MDPROPVAL_MMF_OPENINGPERIOD                       0x00000004L
#define MDPROPVAL_MMF_CLOSINGPERIOD                       0x00000008L
#define MDPROPVAL_MNF_MEDIAN								0x00000001L
#define MDPROPVAL_MNF_VAR								0x00000002L
#define MDPROPVAL_MNF_STDDEV								0x00000004L
#define MDPROPVAL_MNF_RANK								0x00000008L
#define MDPROPVAL_MNF_AGGREGATE							0x00000010L
#define MDPROPVAL_MNF_COVARIANCE							0x00000020L
#define MDPROPVAL_MNF_CORRELATION						0x00000040L
#define MDPROPVAL_MNF_LINREGSLOPE						0x00000080L
#define MDPROPVAL_MNF_LINREGVARIANCE						0x00000100L
#define MDPROPVAL_MNF_LINREG2							0x00000200L
#define MDPROPVAL_MNF_LINREGPOINT						0x00000400L
#define MDPROPVAL_MNF_DRILLDOWNLEVEL						0x00000800L
#define MDPROPVAL_MNF_DRILLDOWNMEMBERTOP					0x00001000L
#define MDPROPVAL_MNF_DRILLDOWNMEMBERBOTTOM				0x00002000L
#define MDPROPVAL_MNF_DRILLDOWNLEVELTOP					0x00004000L
#define MDPROPVAL_MNF_DRILLDOWNLEVELBOTTOM				0x00008000L
#define MDPROPVAL_MNF_DRILLUPMEMBER						0x00010000L
#define MDPROPVAL_MNF_DRILLUPLEVEL						0x00020000L
#define MDPROPVAL_MMF_COUSIN								0x00000001L
#define MDPROPVAL_MMF_PARALLELPERIOD						0x00000002L
#define MDPROPVAL_MMF_OPENINGPERIOD						0x00000004L
#define MDPROPVAL_MMF_CLOSINGPERIOD						0x00000008L
#define MDPROPVAL_MSF_TOPPERCENT							0x00000001L
#define MDPROPVAL_MSF_BOTTOMPERCENT						0x00000002L
#define MDPROPVAL_MSF_TOPSUM								0x00000004L
#define MDPROPVAL_MSF_BOTTOMSUM							0x00000008L
#define MDPROPVAL_MSF_PERIODSTODATE						0x00000010L
#define MDPROPVAL_MSF_LASTPERIODS						0x00000020L
#define MDPROPVAL_MSF_YTD								0x00000040L
#define MDPROPVAL_MSF_QTD								0x00000080L
#define MDPROPVAL_MSF_MTD								0x00000100L
#define MDPROPVAL_MSF_WTD								0x00000200L
#define MDPROPVAL_MSF_DRILLDOWNMEMBBER					0x00000400L
#define MDPROPVAL_MSF_DRILLDOWNLEVEL						0x00000800L
#define MDPROPVAL_MSF_DRILLDOWNMEMBERTOP					0x00001000L
#define MDPROPVAL_MSF_DRILLDOWNMEMBERBOTTOM				0x00002000L
#define MDPROPVAL_MSF_DRILLDOWNLEVELTOP					0x00004000L
#define MDPROPVAL_MSF_DRILLDOWNLEVELBOTTOM				0x00008000L
#define MDPROPVAL_MSF_DRILLUPMEMBER						0x00010000L
#define MDPROPVAL_MSF_DRILLUPLEVEL						0x00020000L
#define MDPROPVAL_MSF_TOGGLEDRILLSTATE					0x00040000L
// values for MDPROP_MDX_DESCFLAGS
#define MDPROPVAL_MD_SELF								0x00000001L
#define MDPROPVAL_MD_BEFORE								0x00000002L
#define MDPROPVAL_MD_AFTER								0x00000004L
// values for MDPROP_MDX_STRING_COMPOP
#define MDPROPVAL_MSC_LESSTHAN							0x00000001L
#define MDPROPVAL_MSC_GREATERTHAN						0x00000002L
#define MDPROPVAL_MSC_LESSTHANEQUAL						0x00000004L
#define MDPROPVAL_MSC_GREATERTHANEQUAL					0x00000008L
#define MDPROPVAL_MC_SINGLECASE							0x00000001L
#define MDPROPVAL_MC_SEARCHEDCASE						0x00000002L
#define MDPROPVAL_MOQ_OUTERREFERENCE						0x00000001L
#define MDPROPVAL_MOQ_DATASOURCE_CUBE					0x00000001L
#define MDPROPVAL_MOQ_CATALOG_CUBE						0x00000002L
#define MDPROPVAL_MOQ_SCHEMA_CUBE						0x00000004L
#define MDPROPVAL_MOQ_CUBE_DIM							0x00000008L
#define MDPROPVAL_MOQ_DIM_HIER							0x00000010L
#define MDPROPVAL_MOQ_DIMHIER_LEVEL						0x00000020L
#define MDPROPVAL_MOQ_LEVEL_MEMBER						0x00000040L
#define MDPROPVAL_MOQ_MEMBER_MEMBER						0x00000080L
#define MDPROPVAL_FS_FULL_SUPPORT						0x00000001L
#define MDPROPVAL_FS_GENERATED_COLUMN					0x00000002L
#define MDPROPVAL_FS_GENERATED_DIMENSION					0x00000003L
#define MDPROPVAL_FS_NO_SUPPORT							0x00000004L
#define MDPROPVAL_NL_NAMEDLEVELS							0x00000001L
#define MDPROPVAL_NL_NUMBEREDLEVELS						0x00000002L
#define MDPROPVAL_MJC_SINGLECUBE							0x00000001L
#define MDPROPVAL_MJC_MULTICUBES							0x00000002L
#define MDPROPVAL_MJC_IMPLICITCUBE						0x00000004L
#define MDPROPVAL_RR_NORANGEROWSET						0x00000001L
#define MDPROPVAL_RR_READONLY							0x00000002L
#define MDPROPVAL_RR_UPDATE								0x00000004L
#define MDPROPVAL_MS_MULTIPLETUPLES						0x00000001L
#define MDPROPVAL_MS_SINGLETUPLE						0x00000002L
#define DBPROPVAL_AO_SEQUENTIAL							0x00000000L
#define DBPROPVAL_AO_SEQUENTIALSTORAGEOBJECTS			0x00000001L
#define DBPROPVAL_AO_RANDOM								0x00000002L
#define DBPROPVAL_BD_ROWSET								0x00000000L
#define DBPROPVAL_BD_INTRANSACTION						0x00000001L
#define DBPROPVAL_BD_XTRANSACTION						0x00000002L
#define DBPROPVAL_BD_REORGANIZATION						0x00000003L
#define BMK_DURABILITY_ROWSET							DBPROPVAL_BD_ROWSET
#define BMK_DURABILITY_INTRANSACTION						DBPROPVAL_BD_INTRANSACTION
#define BMK_DURABILITY_XTRANSACTION						DBPROPVAL_BD_XTRANSACTION
#define BMK_DURABILITY_REORGANIZATION					DBPROPVAL_BD_REORGANIZATION
#define DBPROPVAL_BO_NOLOG								0x00000000L
#define DBPROPVAL_BO_NOINDEXUPDATE						0x00000001L
#define DBPROPVAL_BO_REFINTEGRITY						0x00000002L
#if !defined(_WINBASE_)
#define OF_READ             0x00000000
#define OF_WRITE            0x00000001
#define OF_READWRITE        0x00000002
#define OF_SHARE_COMPAT     0x00000000
#define OF_SHARE_EXCLUSIVE  0x00000010
#define OF_SHARE_DENY_WRITE 0x00000020
#define OF_SHARE_DENY_READ  0x00000030
#define OF_SHARE_DENY_NONE  0x00000040
#define OF_PARSE            0x00000100
#define OF_DELETE           0x00000200
#define OF_VERIFY           0x00000400
#define OF_CANCEL           0x00000800
#define OF_CREATE           0x00001000
#define OF_PROMPT           0x00002000
#define OF_EXIST            0x00004000
#define OF_REOPEN           0x00008000
#endif // !_WINBASE_
#define DBPROPVAL_STGM_READ					= OF_READ
#define DBPROPVAL_STGM_WRITE					= OF_WRITE
#define DBPROPVAL_STGM_READWRITE				= OF_READWRITE
#define DBPROPVAL_STGM_SHARE_DENY_NONE		= OF_SHARE_DENY_NONE
#define DBPROPVAL_STGM_SHARE_DENY_READ		= OF_SHARE_DENY_READ
#define DBPROPVAL_STGM_SHARE_DENY_WRITE		= OF_SHARE_DENY_WRITE
#define DBPROPVAL_STGM_SHARE_EXCLUSIVE		= OF_SHARE_EXCLUSIVE
#define DBPROPVAL_STGM_DIRECT				0x00010000
#define DBPROPVAL_STGM_TRANSACTED			0x00020000
#define DBPROPVAL_STGM_CREATE				= OF_CREATE
#define DBPROPVAL_STGM_CONVERT				0x00040000
#define DBPROPVAL_STGM_FAILIFTHERE			0x00080000
#define DBPROPVAL_STGM_PRIORITY				0x00100000
#define DBPROPVAL_STGM_DELETEONRELEASE		0x00200000
#define DBPROPVAL_GB_COLLATE 				0x00000010L
#define DBPROPVAL_CS_UNINITIALIZED			0x00000000L
#define DBPROPVAL_CS_INITIALIZED				0x00000001L
#define DBPROPVAL_CS_COMMUNICATIONFAILURE	0x00000002L
#define DBPROPVAL_RD_RESETALL		0xffffffffL
#define DBPROPVAL_OS_RESOURCEPOOLING	0x00000001L
#define DBPROPVAL_OS_TXNENLISTMENT	0x00000002L
#define DBPROPVAL_OS_CLIENTCURSOR    0x00000004L
#define DBPROPVAL_OS_ENABLEALL		0xffffffffL
#define DBPROPVAL_BI_CROSSROWSET		0x00000001L
#endif // OLEDBVER >= 0x0200
//@@@- V2.0
#define DB_IMP_LEVEL_ANONYMOUS       0x00
#define DB_IMP_LEVEL_IDENTIFY        0x01
#define DB_IMP_LEVEL_IMPERSONATE     0x02
#define DB_IMP_LEVEL_DELEGATE        0x03
#define DBPROMPT_PROMPT              0x01
#define DBPROMPT_COMPLETE            0x02
#define DBPROMPT_COMPLETEREQUIRED    0x03
#define DBPROMPT_NOPROMPT            0x04
#define DB_PROT_LEVEL_NONE           0x00
#define DB_PROT_LEVEL_CONNECT        0x01
#define DB_PROT_LEVEL_CALL           0x02
#define DB_PROT_LEVEL_PKT            0x03
#define DB_PROT_LEVEL_PKT_INTEGRITY  0x04
#define DB_PROT_LEVEL_PKT_PRIVACY    0x05
#define DB_MODE_READ                 0x01
#define DB_MODE_WRITE                0x02
#define DB_MODE_READWRITE            0x03
#define DB_MODE_SHARE_DENY_READ      0x04
#define DB_MODE_SHARE_DENY_WRITE     0x08
#define DB_MODE_SHARE_EXCLUSIVE		0x0c
#define DB_MODE_SHARE_DENY_NONE		0x10
#define DBCOMPUTEMODE_COMPUTED       0x01
#define DBCOMPUTEMODE_DYNAMIC        0x02
#define DBCOMPUTEMODE_NOTCOMPUTED    0x03
#define DBPROPVAL_DF_INITIALLY_DEFERRED      0x01
#define DBPROPVAL_DF_INITIALLY_IMMEDIATE     0x02
#define DBPROPVAL_DF_NOT_DEFERRABLE		    0x03
//@@@+ V2.5
#if( OLEDBVER >= 0x0250 )
typedef WORD DBCOMMANDOP;


enum DBCOMMANDOPENUM
    {	DBOP_scalar_constant	= 0,
	DBOP_DEFAULT	= DBOP_scalar_constant + 1,
	DBOP_NULL	= DBOP_DEFAULT + 1,
	DBOP_bookmark_name	= DBOP_NULL + 1,
	DBOP_catalog_name	= DBOP_bookmark_name + 1,
	DBOP_column_name	= DBOP_catalog_name + 1,
	DBOP_schema_name	= DBOP_column_name + 1,
	DBOP_outall_name	= DBOP_schema_name + 1,
	DBOP_qualifier_name	= DBOP_outall_name + 1,
	DBOP_qualified_column_name	= DBOP_qualifier_name + 1,
	DBOP_table_name	= DBOP_qualified_column_name + 1,
	DBOP_nested_table_name	= DBOP_table_name + 1,
	DBOP_nested_column_name	= DBOP_nested_table_name + 1,
	DBOP_row	= DBOP_nested_column_name + 1,
	DBOP_table	= DBOP_row + 1,
	DBOP_sort	= DBOP_table + 1,
	DBOP_distinct	= DBOP_sort + 1,
	DBOP_distinct_order_preserving	= DBOP_distinct + 1,
	DBOP_alias	= DBOP_distinct_order_preserving + 1,
	DBOP_cross_join	= DBOP_alias + 1,
	DBOP_union_join	= DBOP_cross_join + 1,
	DBOP_inner_join	= DBOP_union_join + 1,
	DBOP_left_semi_join	= DBOP_inner_join + 1,
	DBOP_right_semi_join	= DBOP_left_semi_join + 1,
	DBOP_left_anti_semi_join	= DBOP_right_semi_join + 1,
	DBOP_right_anti_semi_join	= DBOP_left_anti_semi_join + 1,
	DBOP_left_outer_join	= DBOP_right_anti_semi_join + 1,
	DBOP_right_outer_join	= DBOP_left_outer_join + 1,
	DBOP_full_outer_join	= DBOP_right_outer_join + 1,
	DBOP_natural_join	= DBOP_full_outer_join + 1,
	DBOP_natural_left_outer_join	= DBOP_natural_join + 1,
	DBOP_natural_right_outer_join	= DBOP_natural_left_outer_join + 1,
	DBOP_natural_full_outer_join	= DBOP_natural_right_outer_join + 1,
	DBOP_set_intersection	= DBOP_natural_full_outer_join + 1,
	DBOP_set_union	= DBOP_set_intersection + 1,
	DBOP_set_left_difference	= DBOP_set_union + 1,
	DBOP_set_right_difference	= DBOP_set_left_difference + 1,
	DBOP_set_anti_difference	= DBOP_set_right_difference + 1,
	DBOP_bag_intersection	= DBOP_set_anti_difference + 1,
	DBOP_bag_union	= DBOP_bag_intersection + 1,
	DBOP_bag_left_difference	= DBOP_bag_union + 1,
	DBOP_bag_right_difference	= DBOP_bag_left_difference + 1,
	DBOP_bag_anti_difference	= DBOP_bag_right_difference + 1,
	DBOP_division	= DBOP_bag_anti_difference + 1,
	DBOP_relative_sampling	= DBOP_division + 1,
	DBOP_absolute_sampling	= DBOP_relative_sampling + 1,
	DBOP_transitive_closure	= DBOP_absolute_sampling + 1,
	DBOP_recursive_union	= DBOP_transitive_closure + 1,
	DBOP_aggregate	= DBOP_recursive_union + 1,
	DBOP_remote_table	= DBOP_aggregate + 1,
	DBOP_select	= DBOP_remote_table + 1,
	DBOP_order_preserving_select	= DBOP_select + 1,
	DBOP_project	= DBOP_order_preserving_select + 1,
	DBOP_project_order_preserving	= DBOP_project + 1,
	DBOP_top	= DBOP_project_order_preserving + 1,
	DBOP_top_percent	= DBOP_top + 1,
	DBOP_top_plus_ties	= DBOP_top_percent + 1,
	DBOP_top_percent_plus_ties	= DBOP_top_plus_ties + 1,
	DBOP_rank	= DBOP_top_percent_plus_ties + 1,
	DBOP_rank_ties_equally	= DBOP_rank + 1,
	DBOP_rank_ties_equally_and_skip	= DBOP_rank_ties_equally + 1,
	DBOP_navigate	= DBOP_rank_ties_equally_and_skip + 1,
	DBOP_nesting	= DBOP_navigate + 1,
	DBOP_unnesting	= DBOP_nesting + 1,
	DBOP_nested_apply	= DBOP_unnesting + 1,
	DBOP_cross_tab	= DBOP_nested_apply + 1,
	DBOP_is_NULL	= DBOP_cross_tab + 1,
	DBOP_is_NOT_NULL	= DBOP_is_NULL + 1,
	DBOP_equal	= DBOP_is_NOT_NULL + 1,
	DBOP_not_equal	= DBOP_equal + 1,
	DBOP_less	= DBOP_not_equal + 1,
	DBOP_less_equal	= DBOP_less + 1,
	DBOP_greater	= DBOP_less_equal + 1,
	DBOP_greater_equal	= DBOP_greater + 1,
	DBOP_equal_all	= DBOP_greater_equal + 1,
	DBOP_not_equal_all	= DBOP_equal_all + 1,
	DBOP_less_all	= DBOP_not_equal_all + 1,
	DBOP_less_equal_all	= DBOP_less_all + 1,
	DBOP_greater_all	= DBOP_less_equal_all + 1,
	DBOP_greater_equal_all	= DBOP_greater_all + 1,
	DBOP_equal_any	= DBOP_greater_equal_all + 1,
	DBOP_not_equal_any	= DBOP_equal_any + 1,
	DBOP_less_any	= DBOP_not_equal_any + 1,
	DBOP_less_equal_any	= DBOP_less_any + 1,
	DBOP_greater_any	= DBOP_less_equal_any + 1,
	DBOP_greater_equal_any	= DBOP_greater_any + 1,
	DBOP_anybits	= DBOP_greater_equal_any + 1,
	DBOP_allbits	= DBOP_anybits + 1,
	DBOP_anybits_any	= DBOP_allbits + 1,
	DBOP_allbits_any	= DBOP_anybits_any + 1,
	DBOP_anybits_all	= DBOP_allbits_any + 1,
	DBOP_allbits_all	= DBOP_anybits_all + 1,
	DBOP_between	= DBOP_allbits_all + 1,
	DBOP_between_unordered	= DBOP_between + 1,
	DBOP_match	= DBOP_between_unordered + 1,
	DBOP_match_unique	= DBOP_match + 1,
	DBOP_match_partial	= DBOP_match_unique + 1,
	DBOP_match_partial_unique	= DBOP_match_partial + 1,
	DBOP_match_full	= DBOP_match_partial_unique + 1,
	DBOP_match_full_unique	= DBOP_match_full + 1,
	DBOP_scalar_parameter	= DBOP_match_full_unique + 1,
	DBOP_scalar_function	= DBOP_scalar_parameter + 1,
	DBOP_plus	= DBOP_scalar_function + 1,
	DBOP_minus	= DBOP_plus + 1,
	DBOP_times	= DBOP_minus + 1,
	DBOP_over	= DBOP_times + 1,
	DBOP_div	= DBOP_over + 1,
	DBOP_modulo	= DBOP_div + 1,
	DBOP_power	= DBOP_modulo + 1,
	DBOP_like	= DBOP_power + 1,
	DBOP_sounds_like	= DBOP_like + 1,
	DBOP_like_any	= DBOP_sounds_like + 1,
	DBOP_like_all	= DBOP_like_any + 1,
	DBOP_is_INVALID	= DBOP_like_all + 1,
	DBOP_is_TRUE	= DBOP_is_INVALID + 1,
	DBOP_is_FALSE	= DBOP_is_TRUE + 1,
	DBOP_and	= DBOP_is_FALSE + 1,
	DBOP_or	= DBOP_and + 1,
	DBOP_xor	= DBOP_or + 1,
	DBOP_equivalent	= DBOP_xor + 1,
	DBOP_not	= DBOP_equivalent + 1,
	DBOP_implies	= DBOP_not + 1,
	DBOP_overlaps	= DBOP_implies + 1,
	DBOP_case_condition	= DBOP_overlaps + 1,
	DBOP_case_value	= DBOP_case_condition + 1,
	DBOP_nullif	= DBOP_case_value + 1,
	DBOP_cast	= DBOP_nullif + 1,
	DBOP_coalesce	= DBOP_cast + 1,
	DBOP_position	= DBOP_coalesce + 1,
	DBOP_extract	= DBOP_position + 1,
	DBOP_char_length	= DBOP_extract + 1,
	DBOP_octet_length	= DBOP_char_length + 1,
	DBOP_bit_length	= DBOP_octet_length + 1,
	DBOP_substring	= DBOP_bit_length + 1,
	DBOP_upper	= DBOP_substring + 1,
	DBOP_lower	= DBOP_upper + 1,
	DBOP_trim	= DBOP_lower + 1,
	DBOP_translate	= DBOP_trim + 1,
	DBOP_convert	= DBOP_translate + 1,
	DBOP_string_concat	= DBOP_convert + 1,
	DBOP_current_date	= DBOP_string_concat + 1,
	DBOP_current_time	= DBOP_current_date + 1,
	DBOP_current_timestamp	= DBOP_current_time + 1,
	DBOP_content_select	= DBOP_current_timestamp + 1,
	DBOP_content	= DBOP_content_select + 1,
	DBOP_content_freetext	= DBOP_content + 1,
	DBOP_content_proximity	= DBOP_content_freetext + 1,
	DBOP_content_vector_or	= DBOP_content_proximity + 1,
	DBOP_delete	= DBOP_content_vector_or + 1,
	DBOP_update	= DBOP_delete + 1,
	DBOP_insert	= DBOP_update + 1,
	DBOP_min	= DBOP_insert + 1,
	DBOP_max	= DBOP_min + 1,
	DBOP_count	= DBOP_max + 1,
	DBOP_sum	= DBOP_count + 1,
	DBOP_avg	= DBOP_sum + 1,
	DBOP_any_sample	= DBOP_avg + 1,
	DBOP_stddev	= DBOP_any_sample + 1,
	DBOP_stddev_pop	= DBOP_stddev + 1,
	DBOP_var	= DBOP_stddev_pop + 1,
	DBOP_var_pop	= DBOP_var + 1,
	DBOP_first	= DBOP_var_pop + 1,
	DBOP_last	= DBOP_first + 1,
	DBOP_in	= DBOP_last + 1,
	DBOP_exists	= DBOP_in + 1,
	DBOP_unique	= DBOP_exists + 1,
	DBOP_subset	= DBOP_unique + 1,
	DBOP_proper_subset	= DBOP_subset + 1,
	DBOP_superset	= DBOP_proper_subset + 1,
	DBOP_proper_superset	= DBOP_superset + 1,
	DBOP_disjoint	= DBOP_proper_superset + 1,
	DBOP_pass_through	= DBOP_disjoint + 1,
	DBOP_defined_by_GUID	= DBOP_pass_through + 1,
	DBOP_text_command	= DBOP_defined_by_GUID + 1,
	DBOP_SQL_select	= DBOP_text_command + 1,
	DBOP_prior_command_tree	= DBOP_SQL_select + 1,
	DBOP_add_columns	= DBOP_prior_command_tree + 1,
	DBOP_column_list_anchor	= DBOP_add_columns + 1,
	DBOP_column_list_element	= DBOP_column_list_anchor + 1,
	DBOP_command_list_anchor	= DBOP_column_list_element + 1,
	DBOP_command_list_element	= DBOP_command_list_anchor + 1,
	DBOP_from_list_anchor	= DBOP_command_list_element + 1,
	DBOP_from_list_element	= DBOP_from_list_anchor + 1,
	DBOP_project_list_anchor	= DBOP_from_list_element + 1,
	DBOP_project_list_element	= DBOP_project_list_anchor + 1,
	DBOP_row_list_anchor	= DBOP_project_list_element + 1,
	DBOP_row_list_element	= DBOP_row_list_anchor + 1,
	DBOP_scalar_list_anchor	= DBOP_row_list_element + 1,
	DBOP_scalar_list_element	= DBOP_scalar_list_anchor + 1,
	DBOP_set_list_anchor	= DBOP_scalar_list_element + 1,
	DBOP_set_list_element	= DBOP_set_list_anchor + 1,
	DBOP_sort_list_anchor	= DBOP_set_list_element + 1,
	DBOP_sort_list_element	= DBOP_sort_list_anchor + 1,
	DBOP_alter_character_set	= DBOP_sort_list_element + 1,
	DBOP_alter_collation	= DBOP_alter_character_set + 1,
	DBOP_alter_domain	= DBOP_alter_collation + 1,
	DBOP_alter_index	= DBOP_alter_domain + 1,
	DBOP_alter_procedure	= DBOP_alter_index + 1,
	DBOP_alter_schema	= DBOP_alter_procedure + 1,
	DBOP_alter_table	= DBOP_alter_schema + 1,
	DBOP_alter_trigger	= DBOP_alter_table + 1,
	DBOP_alter_view	= DBOP_alter_trigger + 1,
	DBOP_coldef_list_anchor	= DBOP_alter_view + 1,
	DBOP_coldef_list_element	= DBOP_coldef_list_anchor + 1,
	DBOP_create_assertion	= DBOP_coldef_list_element + 1,
	DBOP_create_character_set	= DBOP_create_assertion + 1,
	DBOP_create_collation	= DBOP_create_character_set + 1,
	DBOP_create_domain	= DBOP_create_collation + 1,
	DBOP_create_index	= DBOP_create_domain + 1,
	DBOP_create_procedure	= DBOP_create_index + 1,
	DBOP_create_schema	= DBOP_create_procedure + 1,
	DBOP_create_synonym	= DBOP_create_schema + 1,
	DBOP_create_table	= DBOP_create_synonym + 1,
	DBOP_create_temporary_table	= DBOP_create_table + 1,
	DBOP_create_translation	= DBOP_create_temporary_table + 1,
	DBOP_create_trigger	= DBOP_create_translation + 1,
	DBOP_create_view	= DBOP_create_trigger + 1,
	DBOP_drop_assertion	= DBOP_create_view + 1,
	DBOP_drop_character_set	= DBOP_drop_assertion + 1,
	DBOP_drop_collation	= DBOP_drop_character_set + 1,
	DBOP_drop_domain	= DBOP_drop_collation + 1,
	DBOP_drop_index	= DBOP_drop_domain + 1,
	DBOP_drop_procedure	= DBOP_drop_index + 1,
	DBOP_drop_schema	= DBOP_drop_procedure + 1,
	DBOP_drop_synonym	= DBOP_drop_schema + 1,
	DBOP_drop_table	= DBOP_drop_synonym + 1,
	DBOP_drop_translation	= DBOP_drop_table + 1,
	DBOP_drop_trigger	= DBOP_drop_translation + 1,
	DBOP_drop_view	= DBOP_drop_trigger + 1,
	DBOP_foreign_key	= DBOP_drop_view + 1,
	DBOP_grant_privileges	= DBOP_foreign_key + 1,
	DBOP_index_list_anchor	= DBOP_grant_privileges + 1,
	DBOP_index_list_element	= DBOP_index_list_anchor + 1,
	DBOP_primary_key	= DBOP_index_list_element + 1,
	DBOP_property_list_anchor	= DBOP_primary_key + 1,
	DBOP_property_list_element	= DBOP_property_list_anchor + 1,
	DBOP_referenced_table	= DBOP_property_list_element + 1,
	DBOP_rename_object	= DBOP_referenced_table + 1,
	DBOP_revoke_privileges	= DBOP_rename_object + 1,
	DBOP_schema_authorization	= DBOP_revoke_privileges + 1,
	DBOP_unique_key	= DBOP_schema_authorization + 1
    };
#endif // OLEDBVER >= 0x0250
//@@@- V2.5
typedef struct  tagDBPARAMS
    {
    void __RPC_FAR *pData;
    ULONG cParamSets;
    HACCESSOR hAccessor;
    }	DBPARAMS;

typedef DWORD DBPARAMFLAGS;


enum DBPARAMFLAGSENUM
    {	DBPARAMFLAGS_ISINPUT	= 0x1,
	DBPARAMFLAGS_ISOUTPUT	= 0x2,
	DBPARAMFLAGS_ISSIGNED	= 0x10,
	DBPARAMFLAGS_ISNULLABLE	= 0x40,
	DBPARAMFLAGS_ISLONG	= 0x80
    };
//@@@+ V2.0
#if( OLEDBVER >= 0x0200 )

enum DBPARAMFLAGSENUM20
    {	DBPARAMFLAGS_SCALEISNEGATIVE	= 0x100
    };
#endif // OLEDBVER >= 0x0200
//@@@- V2.0
typedef struct  tagDBPARAMINFO
    {
    DBPARAMFLAGS dwFlags;
    ULONG iOrdinal;
    LPOLESTR pwszName;
    ITypeInfo __RPC_FAR *pTypeInfo;
    ULONG ulParamSize;
    DBTYPE wType;
    BYTE bPrecision;
    BYTE bScale;
    }	DBPARAMINFO;

typedef DWORD DBPROPID;

typedef struct  tagDBPROPIDSET
    {
    /* [size_is] */ DBPROPID __RPC_FAR *rgPropertyIDs;
    ULONG cPropertyIDs;
    GUID guidPropertySet;
    }	DBPROPIDSET;

typedef DWORD DBPROPFLAGS;


enum DBPROPFLAGSENUM
    {	DBPROPFLAGS_NOTSUPPORTED	= 0,
	DBPROPFLAGS_COLUMN	= 0x1,
	DBPROPFLAGS_DATASOURCE	= 0x2,
	DBPROPFLAGS_DATASOURCECREATE	= 0x4,
	DBPROPFLAGS_DATASOURCEINFO	= 0x8,
	DBPROPFLAGS_DBINIT	= 0x10,
	DBPROPFLAGS_INDEX	= 0x20,
	DBPROPFLAGS_ROWSET	= 0x40,
	DBPROPFLAGS_TABLE	= 0x80,
	DBPROPFLAGS_COLUMNOK	= 0x100,
	DBPROPFLAGS_READ	= 0x200,
	DBPROPFLAGS_WRITE	= 0x400,
	DBPROPFLAGS_REQUIRED	= 0x800,
	DBPROPFLAGS_SESSION	= 0x1000
    };
//@@@+ V2.1
#if( OLEDBVER >= 0x0210 )

enum DBPROPFLAGSENUM21
    {	DBPROPFLAGS_TRUSTEE	= 0x2000
    };
#endif // OLEDBVER >= 0x0210
//@@@- V2.1
typedef struct  tagDBPROPINFO
    {
    LPOLESTR pwszDescription;
    DBPROPID dwPropertyID;
    DBPROPFLAGS dwFlags;
    VARTYPE vtType;
    VARIANT vValues;
    }	DBPROPINFO;

#if 0 
//DBPROPINFO is an unaligned structure. MIDL workaround. 42212352
typedef DBPROPINFO __RPC_FAR *PDBPROPINFO;

#else
typedef DBPROPINFO UNALIGNED __RPC_FAR * PDBPROPINFO;
#endif
typedef struct  tagDBPROPINFOSET
    {
    /* [size_is] */ PDBPROPINFO rgPropertyInfos;
    ULONG cPropertyInfos;
    GUID guidPropertySet;
    }	DBPROPINFOSET;

typedef DWORD DBPROPOPTIONS;

// DBPROPOPTIONS_SETIFCHEAP is deprecated; use DBPROPOPTIONS_OPTIONAL instead.

enum DBPROPOPTIONSENUM
    {	DBPROPOPTIONS_REQUIRED	= 0,
	DBPROPOPTIONS_SETIFCHEAP	= 0x1,
	DBPROPOPTIONS_OPTIONAL	= 0x1
    };
typedef DWORD DBPROPSTATUS;


enum DBPROPSTATUSENUM
    {	DBPROPSTATUS_OK	= 0,
	DBPROPSTATUS_NOTSUPPORTED	= 1,
	DBPROPSTATUS_BADVALUE	= 2,
	DBPROPSTATUS_BADOPTION	= 3,
	DBPROPSTATUS_BADCOLUMN	= 4,
	DBPROPSTATUS_NOTALLSETTABLE	= 5,
	DBPROPSTATUS_NOTSETTABLE	= 6,
	DBPROPSTATUS_NOTSET	= 7,
	DBPROPSTATUS_CONFLICTING	= 8
    };
//@@@+ V2.1
#if( OLEDBVER >= 0x0210 )

enum DBPROPSTATUSENUM21
    {	DBPROPSTATUS_NOTAVAILAVLE	= 9
    };
#endif // OLEDBVER >= 0x0210
//@@@- V2.1
typedef struct  tagDBPROP
    {
    DBPROPID dwPropertyID;
    DBPROPOPTIONS dwOptions;
    DBPROPSTATUS dwStatus;
    DBID colid;
    VARIANT vValue;
    }	DBPROP;

typedef struct  tagDBPROPSET
    {
    /* [size_is] */ DBPROP __RPC_FAR *rgProperties;
    ULONG cProperties;
    GUID guidPropertySet;
    }	DBPROPSET;

#define DBPARAMTYPE_INPUT			0x01
#define DBPARAMTYPE_INPUTOUTPUT		0x02
#define DBPARAMTYPE_OUTPUT			0x03
#define DBPARAMTYPE_RETURNVALUE		0x04
#define DB_PT_UNKNOWN				0x01
#define DB_PT_PROCEDURE				0x02
#define DB_PT_FUNCTION				0x03
#define DB_REMOTE					0x01
#define DB_LOCAL_SHARED				0x02
#define DB_LOCAL_EXCLUSIVE			0x03
#define DB_COLLATION_ASC				0x01
#define DB_COLLATION_DESC			0x02
#define DB_UNSEARCHABLE				0x01
#define DB_LIKE_ONLY					0x02
#define DB_ALL_EXCEPT_LIKE			0x03
#define DB_SEARCHABLE				0x04
//@@@+ V2.0
#if( OLEDBVER >= 0x0200 )
#define MDTREEOP_CHILDREN            0x01
#define MDTREEOP_SIBLINGS            0x02
#define MDTREEOP_PARENT              0x04
#define MDTREEOP_SELF                0x08
#define MDTREEOP_DESCENDANTS         0x10
#define MDTREEOP_ANCESTORS			0x20
#define MD_DIMTYPE_UNKNOWN           0x00
#define MD_DIMTYPE_TIME              0x01
#define MD_DIMTYPE_MEASURE           0x02
#define MD_DIMTYPE_OTHER             0x03
#define MDLEVEL_TYPE_UNKNOWN         0x0000
#define MDLEVEL_TYPE_REGULAR         0x0000
#define MDLEVEL_TYPE_ALL             0x0001
#define MDLEVEL_TYPE_CALCULATED      0x0002
#define MDLEVEL_TYPE_TIME            0x0004
#define MDLEVEL_TYPE_RESERVED1       0x0008
#define MDLEVEL_TYPE_TIME_YEARS      0x0014
#define MDLEVEL_TYPE_TIME_HALF_YEAR  0x0024
#define MDLEVEL_TYPE_TIME_QUARTERS   0x0044
#define MDLEVEL_TYPE_TIME_MONTHS     0x0084
#define MDLEVEL_TYPE_TIME_WEEKS      0x0104
#define MDLEVEL_TYPE_TIME_DAYS       0x0204
#define MDLEVEL_TYPE_TIME_HOURS      0x0304
#define MDLEVEL_TYPE_TIME_MINUTES    0x0404
#define MDLEVEL_TYPE_TIME_SECONDS    0x0804
#define MDLEVEL_TYPE_TIME_UNDEFINED  0x1004
#define MDMEASURE_AGGR_UNKNOWN       0x00
#define MDMEASURE_AGGR_SUM           0x01
#define MDMEASURE_AGGR_COUNT         0x02
#define MDMEASURE_AGGR_MIN           0x03
#define MDMEASURE_AGGR_MAX           0x04
#define MDMEASURE_AGGR_AVG           0x05
#define MDMEASURE_AGGR_VAR           0x06
#define MDMEASURE_AGGR_STD           0x07
#define MDMEASURE_AGGR_CALCULATED    0x7f
#define MDPROP_MEMBER                0x01
#define MDPROP_CELL                  0x02
#define MDMEMBER_TYPE_UNKNOWN        0x00
#define MDMEMBER_TYPE_REGULAR        0x01
#define MDMEMBER_TYPE_ALL            0x02
#define MDMEMBER_TYPE_MEASURE        0x03
#define MDMEMBER_TYPE_FORMULA        0x04
#define MDMEMBER_TYPE_RESERVE1       0x05
#define MDMEMBER_TYPE_RESERVE2       0x06
#define MDMEMBER_TYPE_RESERVE3       0x07
#define MDMEMBER_TYPE_RESERVE4       0x08
#define MDDISPINFO_DRILLED_DOWN				0x00010000
#define MDDISPINFO_PARENT_SAME_AS_PREV		0x00020000
#endif // OLEDBVER >= 0x0200
//@@@- V2.0
typedef DWORD DBINDEX_COL_ORDER;


enum DBINDEX_COL_ORDERENUM
    {	DBINDEX_COL_ORDER_ASC	= 0,
	DBINDEX_COL_ORDER_DESC	= DBINDEX_COL_ORDER_ASC + 1
    };
typedef struct  tagDBINDEXCOLUMNDESC
    {
    DBID __RPC_FAR *pColumnID;
    DBINDEX_COL_ORDER eIndexColOrder;
    }	DBINDEXCOLUMNDESC;

typedef struct  tagDBCOLUMNDESC
    {
    LPOLESTR pwszTypeName;
    ITypeInfo __RPC_FAR *pTypeInfo;
    /* [size_is] */ DBPROPSET __RPC_FAR *rgPropertySets;
    CLSID __RPC_FAR *pclsid;
    ULONG cPropertySets;
    ULONG ulColumnSize;
    DBID dbcid;
    DBTYPE wType;
    BYTE bPrecision;
    BYTE bScale;
    }	DBCOLUMNDESC;

//@@@+ V2.0
#if( OLEDBVER >= 0x0200 )
typedef DWORD DBCOLUMNDESCFLAGS;


enum DBCOLUMNDESCFLAGSENUM
    {	DBCOLUMNDESCFLAGS_TYPENAME	= 0x1,
	DBCOLUMNDESCFLAGS_ITYPEINFO	= 0x2,
	DBCOLUMNDESCFLAGS_PROPERTIES	= 0x4,
	DBCOLUMNDESCFLAGS_CLSID	= 0x8,
	DBCOLUMNDESCFLAGS_COLSIZE	= 0x10,
	DBCOLUMNDESCFLAGS_DBCID	= 0x20,
	DBCOLUMNDESCFLAGS_WTYPE	= 0x40,
	DBCOLUMNDESCFLAGS_PRECISION	= 0x80,
	DBCOLUMNDESCFLAGS_SCALE	= 0x100
    };
#endif // OLEDBVER >= 0x0200
//@@@- V2.0
typedef DWORD DBEVENTPHASE;


enum DBEVENTPHASEENUM
    {	DBEVENTPHASE_OKTODO	= 0,
	DBEVENTPHASE_ABOUTTODO	= DBEVENTPHASE_OKTODO + 1,
	DBEVENTPHASE_SYNCHAFTER	= DBEVENTPHASE_ABOUTTODO + 1,
	DBEVENTPHASE_FAILEDTODO	= DBEVENTPHASE_SYNCHAFTER + 1,
	DBEVENTPHASE_DIDEVENT	= DBEVENTPHASE_FAILEDTODO + 1
    };
typedef DWORD DBREASON;


enum DBREASONENUM
    {	DBREASON_ROWSET_FETCHPOSITIONCHANGE	= 0,
	DBREASON_ROWSET_RELEASE	= DBREASON_ROWSET_FETCHPOSITIONCHANGE + 1,
	DBREASON_COLUMN_SET	= DBREASON_ROWSET_RELEASE + 1,
	DBREASON_COLUMN_RECALCULATED	= DBREASON_COLUMN_SET + 1,
	DBREASON_ROW_ACTIVATE	= DBREASON_COLUMN_RECALCULATED + 1,
	DBREASON_ROW_RELEASE	= DBREASON_ROW_ACTIVATE + 1,
	DBREASON_ROW_DELETE	= DBREASON_ROW_RELEASE + 1,
	DBREASON_ROW_FIRSTCHANGE	= DBREASON_ROW_DELETE + 1,
	DBREASON_ROW_INSERT	= DBREASON_ROW_FIRSTCHANGE + 1,
	DBREASON_ROW_RESYNCH	= DBREASON_ROW_INSERT + 1,
	DBREASON_ROW_UNDOCHANGE	= DBREASON_ROW_RESYNCH + 1,
	DBREASON_ROW_UNDOINSERT	= DBREASON_ROW_UNDOCHANGE + 1,
	DBREASON_ROW_UNDODELETE	= DBREASON_ROW_UNDOINSERT + 1,
	DBREASON_ROW_UPDATE	= DBREASON_ROW_UNDODELETE + 1,
	DBREASON_ROWSET_CHANGED	= DBREASON_ROW_UPDATE + 1
    };
//@@@+ V1.5
#if( OLEDBVER >= 0x0150 )

enum DBREASONENUM15
    {	DBREASON_ROWPOSITION_CHANGED	= DBREASON_ROWSET_CHANGED + 1,
	DBREASON_ROWPOSITION_CHAPTERCHANGED	= DBREASON_ROWPOSITION_CHANGED + 1,
	DBREASON_ROWPOSITION_CLEARED	= DBREASON_ROWPOSITION_CHAPTERCHANGED + 1,
	DBREASON_ROW_ASYNCHINSERT	= DBREASON_ROWPOSITION_CLEARED + 1
    };
#endif // OLEDBVER >= 0x0150
//@@@- V1.5
//@@@+ V2.5
#if( OLEDBVER >= 0x0250 )

enum DBREASONENUM25
    {	DBREASON_ROWSET_ROWSADDED	= DBREASON_ROW_ASYNCHINSERT + 1,
	DBREASON_ROWSET_POPULATIONCOMPLETE	= DBREASON_ROWSET_ROWSADDED + 1,
	DBREASON_ROWSET_POPULATIONSTOPPED	= DBREASON_ROWSET_POPULATIONCOMPLETE + 1
    };
#endif // OLEDBVER >= 0x0250
//@@@- V2.5
//@@@+ V1.5
#if( OLEDBVER >= 0x0150 )
typedef DWORD DBCOMPAREOP;


enum DBCOMPAREOPSENUM
    {	DBCOMPAREOPS_LT	= 0,
	DBCOMPAREOPS_LE	= 1,
	DBCOMPAREOPS_EQ	= 2,
	DBCOMPAREOPS_GE	= 3,
	DBCOMPAREOPS_GT	= 4,
	DBCOMPAREOPS_BEGINSWITH	= 5,
	DBCOMPAREOPS_CONTAINS	= 6,
	DBCOMPAREOPS_NE	= 7,
	DBCOMPAREOPS_IGNORE	= 8,
	DBCOMPAREOPS_CASESENSITIVE	= 0x1000,
	DBCOMPAREOPS_CASEINSENSITIVE	= 0x2000
    };
//@@@+ V2.0
#if( OLEDBVER >= 0x0200 )

enum DBCOMPAREOPSENUM20
    {	DBCOMPAREOPS_NOTBEGINSWITH	= 9,
	DBCOMPAREOPS_NOTCONTAINS	= 10
    };
#endif // OLEDBVER >= 0x0200
//@@@- V2.0
typedef DWORD DBASYNCHOP;


enum DBASYNCHOPENUM
    {	DBASYNCHOP_OPEN	= 0
    };
typedef DWORD DBASYNCHPHASE;


enum DBASYNCHPHASEENUM
    {	DBASYNCHPHASE_INITIALIZATION	= 0,
	DBASYNCHPHASE_POPULATION	= DBASYNCHPHASE_INITIALIZATION + 1,
	DBASYNCHPHASE_COMPLETE	= DBASYNCHPHASE_POPULATION + 1,
	DBASYNCHPHASE_CANCELED	= DBASYNCHPHASE_COMPLETE + 1
    };
#define DB_COUNTUNAVAILABLE -1
#endif // OLEDBVER >= 0x0150
//@@@- V1.5
typedef DWORD DBSORT;


enum DBSORTENUM
    {	DBSORT_ASCENDING	= 0,
	DBSORT_DESCENDING	= DBSORT_ASCENDING + 1
    };
//@@@+ V2.0
#if( OLEDBVER >= 0x0200 )
#define MDFF_BOLD                    0x01
#define MDFF_ITALIC                  0x02
#define MDFF_UNDERLINE               0x04
#define MDFF_STRIKEOUT               0x08
typedef struct  tagMDAXISINFO
    {
    ULONG cbSize;
    ULONG iAxis;
    ULONG cDimensions;
    ULONG cCoordinates;
    ULONG __RPC_FAR *rgcColumns;
    LPOLESTR __RPC_FAR *rgpwszDimensionNames;
    }	MDAXISINFO;

#define PMDAXISINFO_GETAT(rgAxisInfo, iAxis) ((MDAXISINFO *)(((BYTE *)(rgAxisInfo)) +((iAxis) * (rgAxisInfo)[0].cbSize)))
#define MDAXISINFO_GETAT(rgAxisInfo, iAxis) (*PMDAXISINFO_GETAT((rgAxisInfo), (iAxis)))
#define MDAXIS_COLUMNS               0x00000000
#define MDAXIS_ROWS                  0x00000001
#define MDAXIS_PAGES                 0x00000002
#define MDAXIS_SECTIONS              0x00000003
#define MDAXIS_CHAPTERS              0x00000004
#define MDAXIS_SLICERS               0xffffffff
#endif // OLEDBVER >= 0x0200
//@@@- V2.0


extern RPC_IF_HANDLE DBStructureDefinitions_v0_0_c_ifspec;
extern RPC_IF_HANDLE DBStructureDefinitions_v0_0_s_ifspec;
#endif /* __DBStructureDefinitions_INTERFACE_DEFINED__ */

#ifndef __IAccessor_INTERFACE_DEFINED__
#define __IAccessor_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAccessor
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 


typedef DWORD DBACCESSORFLAGS;


enum DBACCESSORFLAGSENUM
    {	DBACCESSOR_INVALID	= 0,
	DBACCESSOR_PASSBYREF	= 0x1,
	DBACCESSOR_ROWDATA	= 0x2,
	DBACCESSOR_PARAMETERDATA	= 0x4,
	DBACCESSOR_OPTIMIZED	= 0x8
    };
//@@@+ V2.5
#if( OLEDBVER >= 0x0250 )

enum DBACCESSORFLAGSENUM25
    {	DBACCESSOR_INHERITED	= 0x10
    };
#endif // OLEDBVER >= 0x0250
//@@@- V2.5
typedef DWORD DBBINDSTATUS;


enum DBBINDSTATUSENUM
    {	DBBINDSTATUS_OK	= 0,
	DBBINDSTATUS_BADORDINAL	= 1,
	DBBINDSTATUS_UNSUPPORTEDCONVERSION	= 2,
	DBBINDSTATUS_BADBINDINFO	= 3,
	DBBINDSTATUS_BADSTORAGEFLAGS	= 4,
	DBBINDSTATUS_NOINTERFACE	= 5,
	DBBINDSTATUS_MULTIPLESTORAGE	= 6
    };

EXTERN_C const IID IID_IAccessor;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a8c-2a1c-11ce-ade5-00aa0044773d")
    IAccessor : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE AddRefAccessor( 
            /* [in] */ HACCESSOR hAccessor,
            /* [unique][out][in] */ ULONG __RPC_FAR *pcRefCount) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE CreateAccessor( 
            /* [in] */ DBACCESSORFLAGS dwAccessorFlags,
            /* [in] */ ULONG cBindings,
            /* [size_is][in] */ const DBBINDING __RPC_FAR rgBindings[  ],
            /* [in] */ ULONG cbRowSize,
            /* [out] */ HACCESSOR __RPC_FAR *phAccessor,
            /* [size_is][out] */ DBBINDSTATUS __RPC_FAR rgStatus[  ]) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetBindings( 
            /* [in] */ HACCESSOR hAccessor,
            /* [out] */ DBACCESSORFLAGS __RPC_FAR *pdwAccessorFlags,
            /* [out][in] */ ULONG __RPC_FAR *pcBindings,
            /* [size_is][size_is][out] */ DBBINDING __RPC_FAR *__RPC_FAR *prgBindings) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE ReleaseAccessor( 
            /* [in] */ HACCESSOR hAccessor,
            /* [unique][out][in] */ ULONG __RPC_FAR *pcRefCount) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAccessorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAccessor __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAccessor __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAccessor __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddRefAccessor )( 
            IAccessor __RPC_FAR * This,
            /* [in] */ HACCESSOR hAccessor,
            /* [unique][out][in] */ ULONG __RPC_FAR *pcRefCount);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateAccessor )( 
            IAccessor __RPC_FAR * This,
            /* [in] */ DBACCESSORFLAGS dwAccessorFlags,
            /* [in] */ ULONG cBindings,
            /* [size_is][in] */ const DBBINDING __RPC_FAR rgBindings[  ],
            /* [in] */ ULONG cbRowSize,
            /* [out] */ HACCESSOR __RPC_FAR *phAccessor,
            /* [size_is][out] */ DBBINDSTATUS __RPC_FAR rgStatus[  ]);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBindings )( 
            IAccessor __RPC_FAR * This,
            /* [in] */ HACCESSOR hAccessor,
            /* [out] */ DBACCESSORFLAGS __RPC_FAR *pdwAccessorFlags,
            /* [out][in] */ ULONG __RPC_FAR *pcBindings,
            /* [size_is][size_is][out] */ DBBINDING __RPC_FAR *__RPC_FAR *prgBindings);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReleaseAccessor )( 
            IAccessor __RPC_FAR * This,
            /* [in] */ HACCESSOR hAccessor,
            /* [unique][out][in] */ ULONG __RPC_FAR *pcRefCount);
        
        END_INTERFACE
    } IAccessorVtbl;

    interface IAccessor
    {
        CONST_VTBL struct IAccessorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAccessor_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAccessor_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAccessor_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAccessor_AddRefAccessor(This,hAccessor,pcRefCount)	\
    (This)->lpVtbl -> AddRefAccessor(This,hAccessor,pcRefCount)

#define IAccessor_CreateAccessor(This,dwAccessorFlags,cBindings,rgBindings,cbRowSize,phAccessor,rgStatus)	\
    (This)->lpVtbl -> CreateAccessor(This,dwAccessorFlags,cBindings,rgBindings,cbRowSize,phAccessor,rgStatus)

#define IAccessor_GetBindings(This,hAccessor,pdwAccessorFlags,pcBindings,prgBindings)	\
    (This)->lpVtbl -> GetBindings(This,hAccessor,pdwAccessorFlags,pcBindings,prgBindings)

#define IAccessor_ReleaseAccessor(This,hAccessor,pcRefCount)	\
    (This)->lpVtbl -> ReleaseAccessor(This,hAccessor,pcRefCount)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE IAccessor_RemoteAddRefAccessor_Proxy( 
    IAccessor __RPC_FAR * This,
    /* [in] */ HACCESSOR hAccessor,
    /* [unique][out][in] */ ULONG __RPC_FAR *pcRefCount,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IAccessor_RemoteAddRefAccessor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IAccessor_RemoteCreateAccessor_Proxy( 
    IAccessor __RPC_FAR * This,
    /* [in] */ DBACCESSORFLAGS dwAccessorFlags,
    /* [in] */ ULONG cBindings,
    /* [size_is][unique][in] */ DBBINDING __RPC_FAR *rgBindings,
    /* [in] */ ULONG cbRowSize,
    /* [out] */ HACCESSOR __RPC_FAR *phAccessor,
    /* [size_is][unique][out][in] */ DBBINDSTATUS __RPC_FAR *rgStatus,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IAccessor_RemoteCreateAccessor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IAccessor_RemoteGetBindings_Proxy( 
    IAccessor __RPC_FAR * This,
    /* [in] */ HACCESSOR hAccessor,
    /* [out] */ DBACCESSORFLAGS __RPC_FAR *pdwAccessorFlags,
    /* [out][in] */ ULONG __RPC_FAR *pcBindings,
    /* [size_is][size_is][out] */ DBBINDING __RPC_FAR *__RPC_FAR *prgBindings,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IAccessor_RemoteGetBindings_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IAccessor_RemoteReleaseAccessor_Proxy( 
    IAccessor __RPC_FAR * This,
    /* [in] */ HACCESSOR hAccessor,
    /* [unique][out][in] */ ULONG __RPC_FAR *pcRefCount,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IAccessor_RemoteReleaseAccessor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAccessor_INTERFACE_DEFINED__ */


#ifndef __IRowset_INTERFACE_DEFINED__
#define __IRowset_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRowset
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object][local] */ 


typedef DWORD DBROWOPTIONS;


EXTERN_C const IID IID_IRowset;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a7c-2a1c-11ce-ade5-00aa0044773d")
    IRowset : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE AddRefRows( 
            /* [in] */ ULONG cRows,
            /* [size_is][in] */ const HROW __RPC_FAR rghRows[  ],
            /* [size_is][out] */ ULONG __RPC_FAR rgRefCounts[  ],
            /* [size_is][out] */ DBROWSTATUS __RPC_FAR rgRowStatus[  ]) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetData( 
            /* [in] */ HROW hRow,
            /* [in] */ HACCESSOR hAccessor,
            /* [out] */ void __RPC_FAR *pData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetNextRows( 
            /* [in] */ HCHAPTER hReserved,
            /* [in] */ LONG lRowsOffset,
            /* [in] */ LONG cRows,
            /* [out] */ ULONG __RPC_FAR *pcRowsObtained,
            /* [size_is][size_is][out] */ HROW __RPC_FAR *__RPC_FAR *prghRows) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReleaseRows( 
            /* [in] */ ULONG cRows,
            /* [size_is][in] */ const HROW __RPC_FAR rghRows[  ],
            /* [size_is][in] */ DBROWOPTIONS __RPC_FAR rgRowOptions[  ],
            /* [size_is][out] */ ULONG __RPC_FAR rgRefCounts[  ],
            /* [size_is][out] */ DBROWSTATUS __RPC_FAR rgRowStatus[  ]) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RestartPosition( 
            /* [in] */ HCHAPTER hReserved) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRowsetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRowset __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRowset __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRowset __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddRefRows )( 
            IRowset __RPC_FAR * This,
            /* [in] */ ULONG cRows,
            /* [size_is][in] */ const HROW __RPC_FAR rghRows[  ],
            /* [size_is][out] */ ULONG __RPC_FAR rgRefCounts[  ],
            /* [size_is][out] */ DBROWSTATUS __RPC_FAR rgRowStatus[  ]);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetData )( 
            IRowset __RPC_FAR * This,
            /* [in] */ HROW hRow,
            /* [in] */ HACCESSOR hAccessor,
            /* [out] */ void __RPC_FAR *pData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextRows )( 
            IRowset __RPC_FAR * This,
            /* [in] */ HCHAPTER hReserved,
            /* [in] */ LONG lRowsOffset,
            /* [in] */ LONG cRows,
            /* [out] */ ULONG __RPC_FAR *pcRowsObtained,
            /* [size_is][size_is][out] */ HROW __RPC_FAR *__RPC_FAR *prghRows);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReleaseRows )( 
            IRowset __RPC_FAR * This,
            /* [in] */ ULONG cRows,
            /* [size_is][in] */ const HROW __RPC_FAR rghRows[  ],
            /* [size_is][in] */ DBROWOPTIONS __RPC_FAR rgRowOptions[  ],
            /* [size_is][out] */ ULONG __RPC_FAR rgRefCounts[  ],
            /* [size_is][out] */ DBROWSTATUS __RPC_FAR rgRowStatus[  ]);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RestartPosition )( 
            IRowset __RPC_FAR * This,
            /* [in] */ HCHAPTER hReserved);
        
        END_INTERFACE
    } IRowsetVtbl;

    interface IRowset
    {
        CONST_VTBL struct IRowsetVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRowset_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRowset_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRowset_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRowset_AddRefRows(This,cRows,rghRows,rgRefCounts,rgRowStatus)	\
    (This)->lpVtbl -> AddRefRows(This,cRows,rghRows,rgRefCounts,rgRowStatus)

#define IRowset_GetData(This,hRow,hAccessor,pData)	\
    (This)->lpVtbl -> GetData(This,hRow,hAccessor,pData)

#define IRowset_GetNextRows(This,hReserved,lRowsOffset,cRows,pcRowsObtained,prghRows)	\
    (This)->lpVtbl -> GetNextRows(This,hReserved,lRowsOffset,cRows,pcRowsObtained,prghRows)

#define IRowset_ReleaseRows(This,cRows,rghRows,rgRowOptions,rgRefCounts,rgRowStatus)	\
    (This)->lpVtbl -> ReleaseRows(This,cRows,rghRows,rgRowOptions,rgRefCounts,rgRowStatus)

#define IRowset_RestartPosition(This,hReserved)	\
    (This)->lpVtbl -> RestartPosition(This,hReserved)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRowset_AddRefRows_Proxy( 
    IRowset __RPC_FAR * This,
    /* [in] */ ULONG cRows,
    /* [size_is][in] */ const HROW __RPC_FAR rghRows[  ],
    /* [size_is][out] */ ULONG __RPC_FAR rgRefCounts[  ],
    /* [size_is][out] */ DBROWSTATUS __RPC_FAR rgRowStatus[  ]);


void __RPC_STUB IRowset_AddRefRows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRowset_GetData_Proxy( 
    IRowset __RPC_FAR * This,
    /* [in] */ HROW hRow,
    /* [in] */ HACCESSOR hAccessor,
    /* [out] */ void __RPC_FAR *pData);


void __RPC_STUB IRowset_GetData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRowset_GetNextRows_Proxy( 
    IRowset __RPC_FAR * This,
    /* [in] */ HCHAPTER hReserved,
    /* [in] */ LONG lRowsOffset,
    /* [in] */ LONG cRows,
    /* [out] */ ULONG __RPC_FAR *pcRowsObtained,
    /* [size_is][size_is][out] */ HROW __RPC_FAR *__RPC_FAR *prghRows);


void __RPC_STUB IRowset_GetNextRows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRowset_ReleaseRows_Proxy( 
    IRowset __RPC_FAR * This,
    /* [in] */ ULONG cRows,
    /* [size_is][in] */ const HROW __RPC_FAR rghRows[  ],
    /* [size_is][in] */ DBROWOPTIONS __RPC_FAR rgRowOptions[  ],
    /* [size_is][out] */ ULONG __RPC_FAR rgRefCounts[  ],
    /* [size_is][out] */ DBROWSTATUS __RPC_FAR rgRowStatus[  ]);


void __RPC_STUB IRowset_ReleaseRows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRowset_RestartPosition_Proxy( 
    IRowset __RPC_FAR * This,
    /* [in] */ HCHAPTER hReserved);


void __RPC_STUB IRowset_RestartPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRowset_INTERFACE_DEFINED__ */


#ifndef __IRowsetInfo_INTERFACE_DEFINED__
#define __IRowsetInfo_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRowsetInfo
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IRowsetInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a55-2a1c-11ce-ade5-00aa0044773d")
    IRowsetInfo : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetProperties( 
            /* [in] */ const ULONG cPropertyIDSets,
            /* [size_is][in] */ const DBPROPIDSET __RPC_FAR rgPropertyIDSets[  ],
            /* [out][in] */ ULONG __RPC_FAR *pcPropertySets,
            /* [size_is][size_is][out] */ DBPROPSET __RPC_FAR *__RPC_FAR *prgPropertySets) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetReferencedRowset( 
            /* [in] */ ULONG iOrdinal,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppReferencedRowset) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetSpecification( 
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppSpecification) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRowsetInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRowsetInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRowsetInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRowsetInfo __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetProperties )( 
            IRowsetInfo __RPC_FAR * This,
            /* [in] */ const ULONG cPropertyIDSets,
            /* [size_is][in] */ const DBPROPIDSET __RPC_FAR rgPropertyIDSets[  ],
            /* [out][in] */ ULONG __RPC_FAR *pcPropertySets,
            /* [size_is][size_is][out] */ DBPROPSET __RPC_FAR *__RPC_FAR *prgPropertySets);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetReferencedRowset )( 
            IRowsetInfo __RPC_FAR * This,
            /* [in] */ ULONG iOrdinal,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppReferencedRowset);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSpecification )( 
            IRowsetInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppSpecification);
        
        END_INTERFACE
    } IRowsetInfoVtbl;

    interface IRowsetInfo
    {
        CONST_VTBL struct IRowsetInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRowsetInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRowsetInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRowsetInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRowsetInfo_GetProperties(This,cPropertyIDSets,rgPropertyIDSets,pcPropertySets,prgPropertySets)	\
    (This)->lpVtbl -> GetProperties(This,cPropertyIDSets,rgPropertyIDSets,pcPropertySets,prgPropertySets)

#define IRowsetInfo_GetReferencedRowset(This,iOrdinal,riid,ppReferencedRowset)	\
    (This)->lpVtbl -> GetReferencedRowset(This,iOrdinal,riid,ppReferencedRowset)

#define IRowsetInfo_GetSpecification(This,riid,ppSpecification)	\
    (This)->lpVtbl -> GetSpecification(This,riid,ppSpecification)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE IRowsetInfo_RemoteGetProperties_Proxy( 
    IRowsetInfo __RPC_FAR * This,
    /* [in] */ ULONG cPropertyIDSets,
    /* [size_is][unique][in] */ const DBPROPIDSET __RPC_FAR *rgPropertyIDSets,
    /* [out][in] */ ULONG __RPC_FAR *pcPropertySets,
    /* [size_is][size_is][out] */ DBPROPSET __RPC_FAR *__RPC_FAR *prgPropertySets,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IRowsetInfo_RemoteGetProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IRowsetInfo_RemoteGetReferencedRowset_Proxy( 
    IRowsetInfo __RPC_FAR * This,
    /* [in] */ ULONG iOrdinal,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppReferencedRowset,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IRowsetInfo_RemoteGetReferencedRowset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IRowsetInfo_RemoteGetSpecification_Proxy( 
    IRowsetInfo __RPC_FAR * This,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppSpecification,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IRowsetInfo_RemoteGetSpecification_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRowsetInfo_INTERFACE_DEFINED__ */


#ifndef __IRowsetLocate_INTERFACE_DEFINED__
#define __IRowsetLocate_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRowsetLocate
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object][local] */ 


typedef DWORD DBCOMPARE;


enum DBCOMPAREENUM
    {	DBCOMPARE_LT	= 0,
	DBCOMPARE_EQ	= DBCOMPARE_LT + 1,
	DBCOMPARE_GT	= DBCOMPARE_EQ + 1,
	DBCOMPARE_NE	= DBCOMPARE_GT + 1,
	DBCOMPARE_NOTCOMPARABLE	= DBCOMPARE_NE + 1
    };

EXTERN_C const IID IID_IRowsetLocate;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a7d-2a1c-11ce-ade5-00aa0044773d")
    IRowsetLocate : public IRowset
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Compare( 
            /* [in] */ HCHAPTER hReserved,
            /* [in] */ ULONG cbBookmark1,
            /* [size_is][in] */ const BYTE __RPC_FAR *pBookmark1,
            /* [in] */ ULONG cbBookmark2,
            /* [size_is][in] */ const BYTE __RPC_FAR *pBookmark2,
            /* [out] */ DBCOMPARE __RPC_FAR *pComparison) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRowsAt( 
            /* [in] */ HWATCHREGION hReserved1,
            /* [in] */ HCHAPTER hReserved2,
            /* [in] */ ULONG cbBookmark,
            /* [size_is][in] */ const BYTE __RPC_FAR *pBookmark,
            /* [in] */ LONG lRowsOffset,
            /* [in] */ LONG cRows,
            /* [out] */ ULONG __RPC_FAR *pcRowsObtained,
            /* [size_is][size_is][out] */ HROW __RPC_FAR *__RPC_FAR *prghRows) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRowsByBookmark( 
            /* [in] */ HCHAPTER hReserved,
            /* [in] */ ULONG cRows,
            /* [size_is][in] */ const ULONG __RPC_FAR rgcbBookmarks[  ],
            /* [size_is][in] */ const BYTE __RPC_FAR *__RPC_FAR rgpBookmarks[  ],
            /* [size_is][out] */ HROW __RPC_FAR rghRows[  ],
            /* [size_is][out] */ DBROWSTATUS __RPC_FAR rgRowStatus[  ]) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Hash( 
            /* [in] */ HCHAPTER hReserved,
            /* [in] */ ULONG cBookmarks,
            /* [size_is][in] */ const ULONG __RPC_FAR rgcbBookmarks[  ],
            /* [size_is][in] */ const BYTE __RPC_FAR *__RPC_FAR rgpBookmarks[  ],
            /* [size_is][out] */ DWORD __RPC_FAR rgHashedValues[  ],
            /* [size_is][out] */ DBROWSTATUS __RPC_FAR rgBookmarkStatus[  ]) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRowsetLocateVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRowsetLocate __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRowsetLocate __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRowsetLocate __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddRefRows )( 
            IRowsetLocate __RPC_FAR * This,
            /* [in] */ ULONG cRows,
            /* [size_is][in] */ const HROW __RPC_FAR rghRows[  ],
            /* [size_is][out] */ ULONG __RPC_FAR rgRefCounts[  ],
            /* [size_is][out] */ DBROWSTATUS __RPC_FAR rgRowStatus[  ]);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetData )( 
            IRowsetLocate __RPC_FAR * This,
            /* [in] */ HROW hRow,
            /* [in] */ HACCESSOR hAccessor,
            /* [out] */ void __RPC_FAR *pData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextRows )( 
            IRowsetLocate __RPC_FAR * This,
            /* [in] */ HCHAPTER hReserved,
            /* [in] */ LONG lRowsOffset,
            /* [in] */ LONG cRows,
            /* [out] */ ULONG __RPC_FAR *pcRowsObtained,
            /* [size_is][size_is][out] */ HROW __RPC_FAR *__RPC_FAR *prghRows);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReleaseRows )( 
            IRowsetLocate __RPC_FAR * This,
            /* [in] */ ULONG cRows,
            /* [size_is][in] */ const HROW __RPC_FAR rghRows[  ],
            /* [size_is][in] */ DBROWOPTIONS __RPC_FAR rgRowOptions[  ],
            /* [size_is][out] */ ULONG __RPC_FAR rgRefCounts[  ],
            /* [size_is][out] */ DBROWSTATUS __RPC_FAR rgRowStatus[  ]);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RestartPosition )( 
            IRowsetLocate __RPC_FAR * This,
            /* [in] */ HCHAPTER hReserved);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Compare )( 
            IRowsetLocate __RPC_FAR * This,
            /* [in] */ HCHAPTER hReserved,
            /* [in] */ ULONG cbBookmark1,
            /* [size_is][in] */ const BYTE __RPC_FAR *pBookmark1,
            /* [in] */ ULONG cbBookmark2,
            /* [size_is][in] */ const BYTE __RPC_FAR *pBookmark2,
            /* [out] */ DBCOMPARE __RPC_FAR *pComparison);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRowsAt )( 
            IRowsetLocate __RPC_FAR * This,
            /* [in] */ HWATCHREGION hReserved1,
            /* [in] */ HCHAPTER hReserved2,
            /* [in] */ ULONG cbBookmark,
            /* [size_is][in] */ const BYTE __RPC_FAR *pBookmark,
            /* [in] */ LONG lRowsOffset,
            /* [in] */ LONG cRows,
            /* [out] */ ULONG __RPC_FAR *pcRowsObtained,
            /* [size_is][size_is][out] */ HROW __RPC_FAR *__RPC_FAR *prghRows);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRowsByBookmark )( 
            IRowsetLocate __RPC_FAR * This,
            /* [in] */ HCHAPTER hReserved,
            /* [in] */ ULONG cRows,
            /* [size_is][in] */ const ULONG __RPC_FAR rgcbBookmarks[  ],
            /* [size_is][in] */ const BYTE __RPC_FAR *__RPC_FAR rgpBookmarks[  ],
            /* [size_is][out] */ HROW __RPC_FAR rghRows[  ],
            /* [size_is][out] */ DBROWSTATUS __RPC_FAR rgRowStatus[  ]);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Hash )( 
            IRowsetLocate __RPC_FAR * This,
            /* [in] */ HCHAPTER hReserved,
            /* [in] */ ULONG cBookmarks,
            /* [size_is][in] */ const ULONG __RPC_FAR rgcbBookmarks[  ],
            /* [size_is][in] */ const BYTE __RPC_FAR *__RPC_FAR rgpBookmarks[  ],
            /* [size_is][out] */ DWORD __RPC_FAR rgHashedValues[  ],
            /* [size_is][out] */ DBROWSTATUS __RPC_FAR rgBookmarkStatus[  ]);
        
        END_INTERFACE
    } IRowsetLocateVtbl;

    interface IRowsetLocate
    {
        CONST_VTBL struct IRowsetLocateVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRowsetLocate_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRowsetLocate_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRowsetLocate_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRowsetLocate_AddRefRows(This,cRows,rghRows,rgRefCounts,rgRowStatus)	\
    (This)->lpVtbl -> AddRefRows(This,cRows,rghRows,rgRefCounts,rgRowStatus)

#define IRowsetLocate_GetData(This,hRow,hAccessor,pData)	\
    (This)->lpVtbl -> GetData(This,hRow,hAccessor,pData)

#define IRowsetLocate_GetNextRows(This,hReserved,lRowsOffset,cRows,pcRowsObtained,prghRows)	\
    (This)->lpVtbl -> GetNextRows(This,hReserved,lRowsOffset,cRows,pcRowsObtained,prghRows)

#define IRowsetLocate_ReleaseRows(This,cRows,rghRows,rgRowOptions,rgRefCounts,rgRowStatus)	\
    (This)->lpVtbl -> ReleaseRows(This,cRows,rghRows,rgRowOptions,rgRefCounts,rgRowStatus)

#define IRowsetLocate_RestartPosition(This,hReserved)	\
    (This)->lpVtbl -> RestartPosition(This,hReserved)


#define IRowsetLocate_Compare(This,hReserved,cbBookmark1,pBookmark1,cbBookmark2,pBookmark2,pComparison)	\
    (This)->lpVtbl -> Compare(This,hReserved,cbBookmark1,pBookmark1,cbBookmark2,pBookmark2,pComparison)

#define IRowsetLocate_GetRowsAt(This,hReserved1,hReserved2,cbBookmark,pBookmark,lRowsOffset,cRows,pcRowsObtained,prghRows)	\
    (This)->lpVtbl -> GetRowsAt(This,hReserved1,hReserved2,cbBookmark,pBookmark,lRowsOffset,cRows,pcRowsObtained,prghRows)

#define IRowsetLocate_GetRowsByBookmark(This,hReserved,cRows,rgcbBookmarks,rgpBookmarks,rghRows,rgRowStatus)	\
    (This)->lpVtbl -> GetRowsByBookmark(This,hReserved,cRows,rgcbBookmarks,rgpBookmarks,rghRows,rgRowStatus)

#define IRowsetLocate_Hash(This,hReserved,cBookmarks,rgcbBookmarks,rgpBookmarks,rgHashedValues,rgBookmarkStatus)	\
    (This)->lpVtbl -> Hash(This,hReserved,cBookmarks,rgcbBookmarks,rgpBookmarks,rgHashedValues,rgBookmarkStatus)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRowsetLocate_Compare_Proxy( 
    IRowsetLocate __RPC_FAR * This,
    /* [in] */ HCHAPTER hReserved,
    /* [in] */ ULONG cbBookmark1,
    /* [size_is][in] */ const BYTE __RPC_FAR *pBookmark1,
    /* [in] */ ULONG cbBookmark2,
    /* [size_is][in] */ const BYTE __RPC_FAR *pBookmark2,
    /* [out] */ DBCOMPARE __RPC_FAR *pComparison);


void __RPC_STUB IRowsetLocate_Compare_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRowsetLocate_GetRowsAt_Proxy( 
    IRowsetLocate __RPC_FAR * This,
    /* [in] */ HWATCHREGION hReserved1,
    /* [in] */ HCHAPTER hReserved2,
    /* [in] */ ULONG cbBookmark,
    /* [size_is][in] */ const BYTE __RPC_FAR *pBookmark,
    /* [in] */ LONG lRowsOffset,
    /* [in] */ LONG cRows,
    /* [out] */ ULONG __RPC_FAR *pcRowsObtained,
    /* [size_is][size_is][out] */ HROW __RPC_FAR *__RPC_FAR *prghRows);


void __RPC_STUB IRowsetLocate_GetRowsAt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRowsetLocate_GetRowsByBookmark_Proxy( 
    IRowsetLocate __RPC_FAR * This,
    /* [in] */ HCHAPTER hReserved,
    /* [in] */ ULONG cRows,
    /* [size_is][in] */ const ULONG __RPC_FAR rgcbBookmarks[  ],
    /* [size_is][in] */ const BYTE __RPC_FAR *__RPC_FAR rgpBookmarks[  ],
    /* [size_is][out] */ HROW __RPC_FAR rghRows[  ],
    /* [size_is][out] */ DBROWSTATUS __RPC_FAR rgRowStatus[  ]);


void __RPC_STUB IRowsetLocate_GetRowsByBookmark_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRowsetLocate_Hash_Proxy( 
    IRowsetLocate __RPC_FAR * This,
    /* [in] */ HCHAPTER hReserved,
    /* [in] */ ULONG cBookmarks,
    /* [size_is][in] */ const ULONG __RPC_FAR rgcbBookmarks[  ],
    /* [size_is][in] */ const BYTE __RPC_FAR *__RPC_FAR rgpBookmarks[  ],
    /* [size_is][out] */ DWORD __RPC_FAR rgHashedValues[  ],
    /* [size_is][out] */ DBROWSTATUS __RPC_FAR rgBookmarkStatus[  ]);


void __RPC_STUB IRowsetLocate_Hash_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRowsetLocate_INTERFACE_DEFINED__ */


#ifndef __IRowsetResynch_INTERFACE_DEFINED__
#define __IRowsetResynch_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRowsetResynch
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object][local] */ 



EXTERN_C const IID IID_IRowsetResynch;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a84-2a1c-11ce-ade5-00aa0044773d")
    IRowsetResynch : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetVisibleData( 
            /* [in] */ HROW hRow,
            /* [in] */ HACCESSOR hAccessor,
            /* [out] */ void __RPC_FAR *pData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ResynchRows( 
            /* [in] */ ULONG cRows,
            /* [size_is][in] */ const HROW __RPC_FAR rghRows[  ],
            /* [out] */ ULONG __RPC_FAR *pcRowsResynched,
            /* [size_is][size_is][out] */ HROW __RPC_FAR *__RPC_FAR *prghRowsResynched,
            /* [size_is][size_is][out] */ DBROWSTATUS __RPC_FAR *__RPC_FAR *prgRowStatus) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRowsetResynchVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRowsetResynch __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRowsetResynch __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRowsetResynch __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVisibleData )( 
            IRowsetResynch __RPC_FAR * This,
            /* [in] */ HROW hRow,
            /* [in] */ HACCESSOR hAccessor,
            /* [out] */ void __RPC_FAR *pData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResynchRows )( 
            IRowsetResynch __RPC_FAR * This,
            /* [in] */ ULONG cRows,
            /* [size_is][in] */ const HROW __RPC_FAR rghRows[  ],
            /* [out] */ ULONG __RPC_FAR *pcRowsResynched,
            /* [size_is][size_is][out] */ HROW __RPC_FAR *__RPC_FAR *prghRowsResynched,
            /* [size_is][size_is][out] */ DBROWSTATUS __RPC_FAR *__RPC_FAR *prgRowStatus);
        
        END_INTERFACE
    } IRowsetResynchVtbl;

    interface IRowsetResynch
    {
        CONST_VTBL struct IRowsetResynchVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRowsetResynch_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRowsetResynch_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRowsetResynch_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRowsetResynch_GetVisibleData(This,hRow,hAccessor,pData)	\
    (This)->lpVtbl -> GetVisibleData(This,hRow,hAccessor,pData)

#define IRowsetResynch_ResynchRows(This,cRows,rghRows,pcRowsResynched,prghRowsResynched,prgRowStatus)	\
    (This)->lpVtbl -> ResynchRows(This,cRows,rghRows,pcRowsResynched,prghRowsResynched,prgRowStatus)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRowsetResynch_GetVisibleData_Proxy( 
    IRowsetResynch __RPC_FAR * This,
    /* [in] */ HROW hRow,
    /* [in] */ HACCESSOR hAccessor,
    /* [out] */ void __RPC_FAR *pData);


void __RPC_STUB IRowsetResynch_GetVisibleData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRowsetResynch_ResynchRows_Proxy( 
    IRowsetResynch __RPC_FAR * This,
    /* [in] */ ULONG cRows,
    /* [size_is][in] */ const HROW __RPC_FAR rghRows[  ],
    /* [out] */ ULONG __RPC_FAR *pcRowsResynched,
    /* [size_is][size_is][out] */ HROW __RPC_FAR *__RPC_FAR *prghRowsResynched,
    /* [size_is][size_is][out] */ DBROWSTATUS __RPC_FAR *__RPC_FAR *prgRowStatus);


void __RPC_STUB IRowsetResynch_ResynchRows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRowsetResynch_INTERFACE_DEFINED__ */


#ifndef __IRowsetScroll_INTERFACE_DEFINED__
#define __IRowsetScroll_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRowsetScroll
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object][local] */ 



EXTERN_C const IID IID_IRowsetScroll;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a7e-2a1c-11ce-ade5-00aa0044773d")
    IRowsetScroll : public IRowsetLocate
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetApproximatePosition( 
            /* [in] */ HCHAPTER hReserved,
            /* [in] */ ULONG cbBookmark,
            /* [size_is][in] */ const BYTE __RPC_FAR *pBookmark,
            /* [out] */ ULONG __RPC_FAR *pulPosition,
            /* [out] */ ULONG __RPC_FAR *pcRows) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRowsAtRatio( 
            /* [in] */ HWATCHREGION hReserved1,
            /* [in] */ HCHAPTER hReserved2,
            /* [in] */ ULONG ulNumerator,
            /* [in] */ ULONG ulDenominator,
            /* [in] */ LONG cRows,
            /* [out] */ ULONG __RPC_FAR *pcRowsObtained,
            /* [size_is][size_is][out] */ HROW __RPC_FAR *__RPC_FAR *prghRows) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRowsetScrollVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRowsetScroll __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRowsetScroll __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRowsetScroll __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddRefRows )( 
            IRowsetScroll __RPC_FAR * This,
            /* [in] */ ULONG cRows,
            /* [size_is][in] */ const HROW __RPC_FAR rghRows[  ],
            /* [size_is][out] */ ULONG __RPC_FAR rgRefCounts[  ],
            /* [size_is][out] */ DBROWSTATUS __RPC_FAR rgRowStatus[  ]);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetData )( 
            IRowsetScroll __RPC_FAR * This,
            /* [in] */ HROW hRow,
            /* [in] */ HACCESSOR hAccessor,
            /* [out] */ void __RPC_FAR *pData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextRows )( 
            IRowsetScroll __RPC_FAR * This,
            /* [in] */ HCHAPTER hReserved,
            /* [in] */ LONG lRowsOffset,
            /* [in] */ LONG cRows,
            /* [out] */ ULONG __RPC_FAR *pcRowsObtained,
            /* [size_is][size_is][out] */ HROW __RPC_FAR *__RPC_FAR *prghRows);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReleaseRows )( 
            IRowsetScroll __RPC_FAR * This,
            /* [in] */ ULONG cRows,
            /* [size_is][in] */ const HROW __RPC_FAR rghRows[  ],
            /* [size_is][in] */ DBROWOPTIONS __RPC_FAR rgRowOptions[  ],
            /* [size_is][out] */ ULONG __RPC_FAR rgRefCounts[  ],
            /* [size_is][out] */ DBROWSTATUS __RPC_FAR rgRowStatus[  ]);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RestartPosition )( 
            IRowsetScroll __RPC_FAR * This,
            /* [in] */ HCHAPTER hReserved);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Compare )( 
            IRowsetScroll __RPC_FAR * This,
            /* [in] */ HCHAPTER hReserved,
            /* [in] */ ULONG cbBookmark1,
            /* [size_is][in] */ const BYTE __RPC_FAR *pBookmark1,
            /* [in] */ ULONG cbBookmark2,
            /* [size_is][in] */ const BYTE __RPC_FAR *pBookmark2,
            /* [out] */ DBCOMPARE __RPC_FAR *pComparison);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRowsAt )( 
            IRowsetScroll __RPC_FAR * This,
            /* [in] */ HWATCHREGION hReserved1,
            /* [in] */ HCHAPTER hReserved2,
            /* [in] */ ULONG cbBookmark,
            /* [size_is][in] */ const BYTE __RPC_FAR *pBookmark,
            /* [in] */ LONG lRowsOffset,
            /* [in] */ LONG cRows,
            /* [out] */ ULONG __RPC_FAR *pcRowsObtained,
            /* [size_is][size_is][out] */ HROW __RPC_FAR *__RPC_FAR *prghRows);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRowsByBookmark )( 
            IRowsetScroll __RPC_FAR * This,
            /* [in] */ HCHAPTER hReserved,
            /* [in] */ ULONG cRows,
            /* [size_is][in] */ const ULONG __RPC_FAR rgcbBookmarks[  ],
            /* [size_is][in] */ const BYTE __RPC_FAR *__RPC_FAR rgpBookmarks[  ],
            /* [size_is][out] */ HROW __RPC_FAR rghRows[  ],
            /* [size_is][out] */ DBROWSTATUS __RPC_FAR rgRowStatus[  ]);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Hash )( 
            IRowsetScroll __RPC_FAR * This,
            /* [in] */ HCHAPTER hReserved,
            /* [in] */ ULONG cBookmarks,
            /* [size_is][in] */ const ULONG __RPC_FAR rgcbBookmarks[  ],
            /* [size_is][in] */ const BYTE __RPC_FAR *__RPC_FAR rgpBookmarks[  ],
            /* [size_is][out] */ DWORD __RPC_FAR rgHashedValues[  ],
            /* [size_is][out] */ DBROWSTATUS __RPC_FAR rgBookmarkStatus[  ]);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetApproximatePosition )( 
            IRowsetScroll __RPC_FAR * This,
            /* [in] */ HCHAPTER hReserved,
            /* [in] */ ULONG cbBookmark,
            /* [size_is][in] */ const BYTE __RPC_FAR *pBookmark,
            /* [out] */ ULONG __RPC_FAR *pulPosition,
            /* [out] */ ULONG __RPC_FAR *pcRows);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRowsAtRatio )( 
            IRowsetScroll __RPC_FAR * This,
            /* [in] */ HWATCHREGION hReserved1,
            /* [in] */ HCHAPTER hReserved2,
            /* [in] */ ULONG ulNumerator,
            /* [in] */ ULONG ulDenominator,
            /* [in] */ LONG cRows,
            /* [out] */ ULONG __RPC_FAR *pcRowsObtained,
            /* [size_is][size_is][out] */ HROW __RPC_FAR *__RPC_FAR *prghRows);
        
        END_INTERFACE
    } IRowsetScrollVtbl;

    interface IRowsetScroll
    {
        CONST_VTBL struct IRowsetScrollVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRowsetScroll_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRowsetScroll_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRowsetScroll_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRowsetScroll_AddRefRows(This,cRows,rghRows,rgRefCounts,rgRowStatus)	\
    (This)->lpVtbl -> AddRefRows(This,cRows,rghRows,rgRefCounts,rgRowStatus)

#define IRowsetScroll_GetData(This,hRow,hAccessor,pData)	\
    (This)->lpVtbl -> GetData(This,hRow,hAccessor,pData)

#define IRowsetScroll_GetNextRows(This,hReserved,lRowsOffset,cRows,pcRowsObtained,prghRows)	\
    (This)->lpVtbl -> GetNextRows(This,hReserved,lRowsOffset,cRows,pcRowsObtained,prghRows)

#define IRowsetScroll_ReleaseRows(This,cRows,rghRows,rgRowOptions,rgRefCounts,rgRowStatus)	\
    (This)->lpVtbl -> ReleaseRows(This,cRows,rghRows,rgRowOptions,rgRefCounts,rgRowStatus)

#define IRowsetScroll_RestartPosition(This,hReserved)	\
    (This)->lpVtbl -> RestartPosition(This,hReserved)


#define IRowsetScroll_Compare(This,hReserved,cbBookmark1,pBookmark1,cbBookmark2,pBookmark2,pComparison)	\
    (This)->lpVtbl -> Compare(This,hReserved,cbBookmark1,pBookmark1,cbBookmark2,pBookmark2,pComparison)

#define IRowsetScroll_GetRowsAt(This,hReserved1,hReserved2,cbBookmark,pBookmark,lRowsOffset,cRows,pcRowsObtained,prghRows)	\
    (This)->lpVtbl -> GetRowsAt(This,hReserved1,hReserved2,cbBookmark,pBookmark,lRowsOffset,cRows,pcRowsObtained,prghRows)

#define IRowsetScroll_GetRowsByBookmark(This,hReserved,cRows,rgcbBookmarks,rgpBookmarks,rghRows,rgRowStatus)	\
    (This)->lpVtbl -> GetRowsByBookmark(This,hReserved,cRows,rgcbBookmarks,rgpBookmarks,rghRows,rgRowStatus)

#define IRowsetScroll_Hash(This,hReserved,cBookmarks,rgcbBookmarks,rgpBookmarks,rgHashedValues,rgBookmarkStatus)	\
    (This)->lpVtbl -> Hash(This,hReserved,cBookmarks,rgcbBookmarks,rgpBookmarks,rgHashedValues,rgBookmarkStatus)


#define IRowsetScroll_GetApproximatePosition(This,hReserved,cbBookmark,pBookmark,pulPosition,pcRows)	\
    (This)->lpVtbl -> GetApproximatePosition(This,hReserved,cbBookmark,pBookmark,pulPosition,pcRows)

#define IRowsetScroll_GetRowsAtRatio(This,hReserved1,hReserved2,ulNumerator,ulDenominator,cRows,pcRowsObtained,prghRows)	\
    (This)->lpVtbl -> GetRowsAtRatio(This,hReserved1,hReserved2,ulNumerator,ulDenominator,cRows,pcRowsObtained,prghRows)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRowsetScroll_GetApproximatePosition_Proxy( 
    IRowsetScroll __RPC_FAR * This,
    /* [in] */ HCHAPTER hReserved,
    /* [in] */ ULONG cbBookmark,
    /* [size_is][in] */ const BYTE __RPC_FAR *pBookmark,
    /* [out] */ ULONG __RPC_FAR *pulPosition,
    /* [out] */ ULONG __RPC_FAR *pcRows);


void __RPC_STUB IRowsetScroll_GetApproximatePosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRowsetScroll_GetRowsAtRatio_Proxy( 
    IRowsetScroll __RPC_FAR * This,
    /* [in] */ HWATCHREGION hReserved1,
    /* [in] */ HCHAPTER hReserved2,
    /* [in] */ ULONG ulNumerator,
    /* [in] */ ULONG ulDenominator,
    /* [in] */ LONG cRows,
    /* [out] */ ULONG __RPC_FAR *pcRowsObtained,
    /* [size_is][size_is][out] */ HROW __RPC_FAR *__RPC_FAR *prghRows);


void __RPC_STUB IRowsetScroll_GetRowsAtRatio_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRowsetScroll_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_oledb_0078
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


//@@@+ V1.5
#if( OLEDBVER >= 0x0150 )


extern RPC_IF_HANDLE __MIDL_itf_oledb_0078_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_oledb_0078_v0_0_s_ifspec;

#ifndef __IChapteredRowset_INTERFACE_DEFINED__
#define __IChapteredRowset_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IChapteredRowset
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IChapteredRowset;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a93-2a1c-11ce-ade5-00aa0044773d")
    IChapteredRowset : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE AddRefChapter( 
            /* [in] */ HCHAPTER hChapter,
            /* [out] */ ULONG __RPC_FAR *pcRefCount) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE ReleaseChapter( 
            /* [in] */ HCHAPTER hChapter,
            /* [out] */ ULONG __RPC_FAR *pcRefCount) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IChapteredRowsetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IChapteredRowset __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IChapteredRowset __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IChapteredRowset __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddRefChapter )( 
            IChapteredRowset __RPC_FAR * This,
            /* [in] */ HCHAPTER hChapter,
            /* [out] */ ULONG __RPC_FAR *pcRefCount);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReleaseChapter )( 
            IChapteredRowset __RPC_FAR * This,
            /* [in] */ HCHAPTER hChapter,
            /* [out] */ ULONG __RPC_FAR *pcRefCount);
        
        END_INTERFACE
    } IChapteredRowsetVtbl;

    interface IChapteredRowset
    {
        CONST_VTBL struct IChapteredRowsetVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IChapteredRowset_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IChapteredRowset_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IChapteredRowset_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IChapteredRowset_AddRefChapter(This,hChapter,pcRefCount)	\
    (This)->lpVtbl -> AddRefChapter(This,hChapter,pcRefCount)

#define IChapteredRowset_ReleaseChapter(This,hChapter,pcRefCount)	\
    (This)->lpVtbl -> ReleaseChapter(This,hChapter,pcRefCount)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE IChapteredRowset_RemoteAddRefChapter_Proxy( 
    IChapteredRowset __RPC_FAR * This,
    /* [in] */ HCHAPTER hChapter,
    /* [out] */ ULONG __RPC_FAR *pcRefCount,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IChapteredRowset_RemoteAddRefChapter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IChapteredRowset_RemoteReleaseChapter_Proxy( 
    IChapteredRowset __RPC_FAR * This,
    /* [in] */ HCHAPTER hChapter,
    /* [out] */ ULONG __RPC_FAR *pcRefCount,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IChapteredRowset_RemoteReleaseChapter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IChapteredRowset_INTERFACE_DEFINED__ */


#ifndef __IRowsetFind_INTERFACE_DEFINED__
#define __IRowsetFind_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRowsetFind
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object][local] */ 



EXTERN_C const IID IID_IRowsetFind;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a9d-2a1c-11ce-ade5-00aa0044773d")
    IRowsetFind : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE FindNextRow( 
            /* [in] */ HCHAPTER hChapter,
            /* [in] */ HACCESSOR hAccessor,
            /* [in] */ void __RPC_FAR *pFindValue,
            /* [in] */ DBCOMPAREOP CompareOp,
            /* [in] */ ULONG cbBookmark,
            /* [size_is][in] */ const BYTE __RPC_FAR *pBookmark,
            /* [in] */ LONG lRowsOffset,
            /* [in] */ LONG cRows,
            /* [out][in] */ ULONG __RPC_FAR *pcRowsObtained,
            /* [size_is][size_is][out] */ HROW __RPC_FAR *__RPC_FAR *prghRows) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRowsetFindVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRowsetFind __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRowsetFind __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRowsetFind __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindNextRow )( 
            IRowsetFind __RPC_FAR * This,
            /* [in] */ HCHAPTER hChapter,
            /* [in] */ HACCESSOR hAccessor,
            /* [in] */ void __RPC_FAR *pFindValue,
            /* [in] */ DBCOMPAREOP CompareOp,
            /* [in] */ ULONG cbBookmark,
            /* [size_is][in] */ const BYTE __RPC_FAR *pBookmark,
            /* [in] */ LONG lRowsOffset,
            /* [in] */ LONG cRows,
            /* [out][in] */ ULONG __RPC_FAR *pcRowsObtained,
            /* [size_is][size_is][out] */ HROW __RPC_FAR *__RPC_FAR *prghRows);
        
        END_INTERFACE
    } IRowsetFindVtbl;

    interface IRowsetFind
    {
        CONST_VTBL struct IRowsetFindVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRowsetFind_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRowsetFind_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRowsetFind_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRowsetFind_FindNextRow(This,hChapter,hAccessor,pFindValue,CompareOp,cbBookmark,pBookmark,lRowsOffset,cRows,pcRowsObtained,prghRows)	\
    (This)->lpVtbl -> FindNextRow(This,hChapter,hAccessor,pFindValue,CompareOp,cbBookmark,pBookmark,lRowsOffset,cRows,pcRowsObtained,prghRows)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRowsetFind_FindNextRow_Proxy( 
    IRowsetFind __RPC_FAR * This,
    /* [in] */ HCHAPTER hChapter,
    /* [in] */ HACCESSOR hAccessor,
    /* [in] */ void __RPC_FAR *pFindValue,
    /* [in] */ DBCOMPAREOP CompareOp,
    /* [in] */ ULONG cbBookmark,
    /* [size_is][in] */ const BYTE __RPC_FAR *pBookmark,
    /* [in] */ LONG lRowsOffset,
    /* [in] */ LONG cRows,
    /* [out][in] */ ULONG __RPC_FAR *pcRowsObtained,
    /* [size_is][size_is][out] */ HROW __RPC_FAR *__RPC_FAR *prghRows);


void __RPC_STUB IRowsetFind_FindNextRow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRowsetFind_INTERFACE_DEFINED__ */


#ifndef __IRowPosition_INTERFACE_DEFINED__
#define __IRowPosition_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRowPosition
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 


typedef DWORD DBPOSITIONFLAGS;


enum DBPOSITIONFLAGSENUM
    {	DBPOSITION_OK	= 0,
	DBPOSITION_NOROW	= DBPOSITION_OK + 1,
	DBPOSITION_BOF	= DBPOSITION_NOROW + 1,
	DBPOSITION_EOF	= DBPOSITION_BOF + 1
    };

EXTERN_C const IID IID_IRowPosition;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a94-2a1c-11ce-ade5-00aa0044773d")
    IRowPosition : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE ClearRowPosition( void) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetRowPosition( 
            /* [out] */ HCHAPTER __RPC_FAR *phChapter,
            /* [out] */ HROW __RPC_FAR *phRow,
            /* [out] */ DBPOSITIONFLAGS __RPC_FAR *pdwPositionFlags) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetRowset( 
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ IUnknown __RPC_FAR *pRowset) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE SetRowPosition( 
            /* [in] */ HCHAPTER hChapter,
            /* [in] */ HROW hRow,
            /* [in] */ DBPOSITIONFLAGS dwPositionFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRowPositionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRowPosition __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRowPosition __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRowPosition __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ClearRowPosition )( 
            IRowPosition __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRowPosition )( 
            IRowPosition __RPC_FAR * This,
            /* [out] */ HCHAPTER __RPC_FAR *phChapter,
            /* [out] */ HROW __RPC_FAR *phRow,
            /* [out] */ DBPOSITIONFLAGS __RPC_FAR *pdwPositionFlags);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRowset )( 
            IRowPosition __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IRowPosition __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pRowset);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetRowPosition )( 
            IRowPosition __RPC_FAR * This,
            /* [in] */ HCHAPTER hChapter,
            /* [in] */ HROW hRow,
            /* [in] */ DBPOSITIONFLAGS dwPositionFlags);
        
        END_INTERFACE
    } IRowPositionVtbl;

    interface IRowPosition
    {
        CONST_VTBL struct IRowPositionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRowPosition_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRowPosition_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRowPosition_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRowPosition_ClearRowPosition(This)	\
    (This)->lpVtbl -> ClearRowPosition(This)

#define IRowPosition_GetRowPosition(This,phChapter,phRow,pdwPositionFlags)	\
    (This)->lpVtbl -> GetRowPosition(This,phChapter,phRow,pdwPositionFlags)

#define IRowPosition_GetRowset(This,riid,ppRowset)	\
    (This)->lpVtbl -> GetRowset(This,riid,ppRowset)

#define IRowPosition_Initialize(This,pRowset)	\
    (This)->lpVtbl -> Initialize(This,pRowset)

#define IRowPosition_SetRowPosition(This,hChapter,hRow,dwPositionFlags)	\
    (This)->lpVtbl -> SetRowPosition(This,hChapter,hRow,dwPositionFlags)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE IRowPosition_RemoteClearRowPosition_Proxy( 
    IRowPosition __RPC_FAR * This,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IRowPosition_RemoteClearRowPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IRowPosition_RemoteGetRowPosition_Proxy( 
    IRowPosition __RPC_FAR * This,
    /* [out] */ HCHAPTER __RPC_FAR *phChapter,
    /* [out] */ HROW __RPC_FAR *phRow,
    /* [out] */ DBPOSITIONFLAGS __RPC_FAR *pdwPositionFlags,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IRowPosition_RemoteGetRowPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IRowPosition_RemoteGetRowset_Proxy( 
    IRowPosition __RPC_FAR * This,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IRowPosition_RemoteGetRowset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IRowPosition_RemoteInitialize_Proxy( 
    IRowPosition __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pRowset,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IRowPosition_RemoteInitialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IRowPosition_RemoteSetRowPosition_Proxy( 
    IRowPosition __RPC_FAR * This,
    /* [in] */ HCHAPTER hChapter,
    /* [in] */ HROW hRow,
    /* [in] */ DBPOSITIONFLAGS dwPositionFlags,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IRowPosition_RemoteSetRowPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRowPosition_INTERFACE_DEFINED__ */


#ifndef __IRowPositionChange_INTERFACE_DEFINED__
#define __IRowPositionChange_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRowPositionChange
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IRowPositionChange;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0997a571-126e-11d0-9f8a-00a0c9a0631e")
    IRowPositionChange : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE OnRowPositionChange( 
            /* [in] */ DBREASON eReason,
            /* [in] */ DBEVENTPHASE ePhase,
            /* [in] */ BOOL fCantDeny) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRowPositionChangeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRowPositionChange __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRowPositionChange __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRowPositionChange __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnRowPositionChange )( 
            IRowPositionChange __RPC_FAR * This,
            /* [in] */ DBREASON eReason,
            /* [in] */ DBEVENTPHASE ePhase,
            /* [in] */ BOOL fCantDeny);
        
        END_INTERFACE
    } IRowPositionChangeVtbl;

    interface IRowPositionChange
    {
        CONST_VTBL struct IRowPositionChangeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRowPositionChange_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRowPositionChange_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRowPositionChange_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRowPositionChange_OnRowPositionChange(This,eReason,ePhase,fCantDeny)	\
    (This)->lpVtbl -> OnRowPositionChange(This,eReason,ePhase,fCantDeny)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE IRowPositionChange_RemoteOnRowPositionChange_Proxy( 
    IRowPositionChange __RPC_FAR * This,
    /* [in] */ DBREASON eReason,
    /* [in] */ DBEVENTPHASE ePhase,
    /* [in] */ BOOL fCantDeny,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IRowPositionChange_RemoteOnRowPositionChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRowPositionChange_INTERFACE_DEFINED__ */


#ifndef __IViewRowset_INTERFACE_DEFINED__
#define __IViewRowset_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IViewRowset
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IViewRowset;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a97-2a1c-11ce-ade5-00aa0044773d")
    IViewRowset : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetSpecification( 
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppObject) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE OpenViewRowset( 
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IViewRowsetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IViewRowset __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IViewRowset __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IViewRowset __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSpecification )( 
            IViewRowset __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppObject);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenViewRowset )( 
            IViewRowset __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset);
        
        END_INTERFACE
    } IViewRowsetVtbl;

    interface IViewRowset
    {
        CONST_VTBL struct IViewRowsetVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IViewRowset_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IViewRowset_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IViewRowset_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IViewRowset_GetSpecification(This,riid,ppObject)	\
    (This)->lpVtbl -> GetSpecification(This,riid,ppObject)

#define IViewRowset_OpenViewRowset(This,pUnkOuter,riid,ppRowset)	\
    (This)->lpVtbl -> OpenViewRowset(This,pUnkOuter,riid,ppRowset)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE IViewRowset_RemoteGetSpecification_Proxy( 
    IViewRowset __RPC_FAR * This,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppObject,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IViewRowset_RemoteGetSpecification_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IViewRowset_RemoteOpenViewRowset_Proxy( 
    IViewRowset __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IViewRowset_RemoteOpenViewRowset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IViewRowset_INTERFACE_DEFINED__ */


#ifndef __IViewChapter_INTERFACE_DEFINED__
#define __IViewChapter_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IViewChapter
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IViewChapter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a98-2a1c-11ce-ade5-00aa0044773d")
    IViewChapter : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetSpecification( 
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE OpenViewChapter( 
            /* [in] */ HCHAPTER hSource,
            /* [out] */ HCHAPTER __RPC_FAR *phViewChapter) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IViewChapterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IViewChapter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IViewChapter __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IViewChapter __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSpecification )( 
            IViewChapter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenViewChapter )( 
            IViewChapter __RPC_FAR * This,
            /* [in] */ HCHAPTER hSource,
            /* [out] */ HCHAPTER __RPC_FAR *phViewChapter);
        
        END_INTERFACE
    } IViewChapterVtbl;

    interface IViewChapter
    {
        CONST_VTBL struct IViewChapterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IViewChapter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IViewChapter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IViewChapter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IViewChapter_GetSpecification(This,riid,ppRowset)	\
    (This)->lpVtbl -> GetSpecification(This,riid,ppRowset)

#define IViewChapter_OpenViewChapter(This,hSource,phViewChapter)	\
    (This)->lpVtbl -> OpenViewChapter(This,hSource,phViewChapter)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE IViewChapter_RemoteGetSpecification_Proxy( 
    IViewChapter __RPC_FAR * This,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IViewChapter_RemoteGetSpecification_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IViewChapter_RemoteOpenViewChapter_Proxy( 
    IViewChapter __RPC_FAR * This,
    /* [in] */ HCHAPTER hSource,
    /* [out] */ HCHAPTER __RPC_FAR *phViewChapter,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IViewChapter_RemoteOpenViewChapter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IViewChapter_INTERFACE_DEFINED__ */


#ifndef __IViewSort_INTERFACE_DEFINED__
#define __IViewSort_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IViewSort
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IViewSort;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a9a-2a1c-11ce-ade5-00aa0044773d")
    IViewSort : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetSortOrder( 
            /* [out] */ ULONG __RPC_FAR *pcValues,
            /* [out] */ ULONG __RPC_FAR *__RPC_FAR prgColumns[  ],
            /* [out] */ DBSORT __RPC_FAR *__RPC_FAR prgOrders[  ]) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE SetSortOrder( 
            /* [in] */ ULONG cValues,
            /* [size_is][in] */ const ULONG __RPC_FAR rgColumns[  ],
            /* [size_is][in] */ const DBSORT __RPC_FAR rgOrders[  ]) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IViewSortVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IViewSort __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IViewSort __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IViewSort __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSortOrder )( 
            IViewSort __RPC_FAR * This,
            /* [out] */ ULONG __RPC_FAR *pcValues,
            /* [out] */ ULONG __RPC_FAR *__RPC_FAR prgColumns[  ],
            /* [out] */ DBSORT __RPC_FAR *__RPC_FAR prgOrders[  ]);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSortOrder )( 
            IViewSort __RPC_FAR * This,
            /* [in] */ ULONG cValues,
            /* [size_is][in] */ const ULONG __RPC_FAR rgColumns[  ],
            /* [size_is][in] */ const DBSORT __RPC_FAR rgOrders[  ]);
        
        END_INTERFACE
    } IViewSortVtbl;

    interface IViewSort
    {
        CONST_VTBL struct IViewSortVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IViewSort_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IViewSort_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IViewSort_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IViewSort_GetSortOrder(This,pcValues,prgColumns,prgOrders)	\
    (This)->lpVtbl -> GetSortOrder(This,pcValues,prgColumns,prgOrders)

#define IViewSort_SetSortOrder(This,cValues,rgColumns,rgOrders)	\
    (This)->lpVtbl -> SetSortOrder(This,cValues,rgColumns,rgOrders)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE IViewSort_RemoteGetSortOrder_Proxy( 
    IViewSort __RPC_FAR * This,
    /* [out][in] */ ULONG __RPC_FAR *pcValues,
    /* [size_is][size_is][out] */ ULONG __RPC_FAR *__RPC_FAR *prgColumns,
    /* [size_is][size_is][out] */ ULONG __RPC_FAR *__RPC_FAR *prgOrders,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IViewSort_RemoteGetSortOrder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IViewSort_RemoteSetSortOrder_Proxy( 
    IViewSort __RPC_FAR * This,
    /* [in] */ ULONG cValues,
    /* [size_is][in] */ const ULONG __RPC_FAR *rgColumns,
    /* [size_is][in] */ const DBSORT __RPC_FAR *rgOrders,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IViewSort_RemoteSetSortOrder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IViewSort_INTERFACE_DEFINED__ */


#ifndef __IViewFilter_INTERFACE_DEFINED__
#define __IViewFilter_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IViewFilter
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IViewFilter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a9b-2a1c-11ce-ade5-00aa0044773d")
    IViewFilter : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetFilter( 
            /* [in] */ HACCESSOR hAccessor,
            /* [out] */ ULONG __RPC_FAR *pcRows,
            /* [out] */ DBCOMPAREOP __RPC_FAR *__RPC_FAR pCompareOps[  ],
            /* [out] */ void __RPC_FAR *pCriteriaData) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetFilterBindings( 
            /* [out] */ ULONG __RPC_FAR *pcBindings,
            /* [out] */ DBBINDING __RPC_FAR *__RPC_FAR *prgBindings) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE SetFilter( 
            /* [in] */ HACCESSOR hAccessor,
            /* [in] */ ULONG cRows,
            /* [in] */ DBCOMPAREOP __RPC_FAR CompareOps[  ],
            /* [in] */ void __RPC_FAR *pCriteriaData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IViewFilterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IViewFilter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IViewFilter __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IViewFilter __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFilter )( 
            IViewFilter __RPC_FAR * This,
            /* [in] */ HACCESSOR hAccessor,
            /* [out] */ ULONG __RPC_FAR *pcRows,
            /* [out] */ DBCOMPAREOP __RPC_FAR *__RPC_FAR pCompareOps[  ],
            /* [out] */ void __RPC_FAR *pCriteriaData);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFilterBindings )( 
            IViewFilter __RPC_FAR * This,
            /* [out] */ ULONG __RPC_FAR *pcBindings,
            /* [out] */ DBBINDING __RPC_FAR *__RPC_FAR *prgBindings);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetFilter )( 
            IViewFilter __RPC_FAR * This,
            /* [in] */ HACCESSOR hAccessor,
            /* [in] */ ULONG cRows,
            /* [in] */ DBCOMPAREOP __RPC_FAR CompareOps[  ],
            /* [in] */ void __RPC_FAR *pCriteriaData);
        
        END_INTERFACE
    } IViewFilterVtbl;

    interface IViewFilter
    {
        CONST_VTBL struct IViewFilterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IViewFilter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IViewFilter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IViewFilter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IViewFilter_GetFilter(This,hAccessor,pcRows,pCompareOps,pCriteriaData)	\
    (This)->lpVtbl -> GetFilter(This,hAccessor,pcRows,pCompareOps,pCriteriaData)

#define IViewFilter_GetFilterBindings(This,pcBindings,prgBindings)	\
    (This)->lpVtbl -> GetFilterBindings(This,pcBindings,prgBindings)

#define IViewFilter_SetFilter(This,hAccessor,cRows,CompareOps,pCriteriaData)	\
    (This)->lpVtbl -> SetFilter(This,hAccessor,cRows,CompareOps,pCriteriaData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [local] */ HRESULT STDMETHODCALLTYPE IViewFilter_GetFilter_Proxy( 
    IViewFilter __RPC_FAR * This,
    /* [in] */ HACCESSOR hAccessor,
    /* [out] */ ULONG __RPC_FAR *pcRows,
    /* [out] */ DBCOMPAREOP __RPC_FAR *__RPC_FAR pCompareOps[  ],
    /* [out] */ void __RPC_FAR *pCriteriaData);


void __RPC_STUB IViewFilter_GetFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IViewFilter_RemoteGetFilterBindings_Proxy( 
    IViewFilter __RPC_FAR * This,
    /* [out][in] */ ULONG __RPC_FAR *pcBindings,
    /* [size_is][size_is][out] */ DBBINDING __RPC_FAR *__RPC_FAR *prgBindings,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IViewFilter_RemoteGetFilterBindings_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [local] */ HRESULT STDMETHODCALLTYPE IViewFilter_SetFilter_Proxy( 
    IViewFilter __RPC_FAR * This,
    /* [in] */ HACCESSOR hAccessor,
    /* [in] */ ULONG cRows,
    /* [in] */ DBCOMPAREOP __RPC_FAR CompareOps[  ],
    /* [in] */ void __RPC_FAR *pCriteriaData);


void __RPC_STUB IViewFilter_SetFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IViewFilter_INTERFACE_DEFINED__ */


#ifndef __IRowsetView_INTERFACE_DEFINED__
#define __IRowsetView_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRowsetView
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IRowsetView;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a99-2a1c-11ce-ade5-00aa0044773d")
    IRowsetView : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE CreateView( 
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppView) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetView( 
            /* [in] */ HCHAPTER hChapter,
            /* [in] */ REFIID riid,
            /* [out] */ HCHAPTER __RPC_FAR *phChapterSource,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppView) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRowsetViewVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRowsetView __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRowsetView __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRowsetView __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateView )( 
            IRowsetView __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppView);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetView )( 
            IRowsetView __RPC_FAR * This,
            /* [in] */ HCHAPTER hChapter,
            /* [in] */ REFIID riid,
            /* [out] */ HCHAPTER __RPC_FAR *phChapterSource,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppView);
        
        END_INTERFACE
    } IRowsetViewVtbl;

    interface IRowsetView
    {
        CONST_VTBL struct IRowsetViewVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRowsetView_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRowsetView_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRowsetView_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRowsetView_CreateView(This,pUnkOuter,riid,ppView)	\
    (This)->lpVtbl -> CreateView(This,pUnkOuter,riid,ppView)

#define IRowsetView_GetView(This,hChapter,riid,phChapterSource,ppView)	\
    (This)->lpVtbl -> GetView(This,hChapter,riid,phChapterSource,ppView)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE IRowsetView_RemoteCreateView_Proxy( 
    IRowsetView __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppView,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IRowsetView_RemoteCreateView_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IRowsetView_RemoteGetView_Proxy( 
    IRowsetView __RPC_FAR * This,
    /* [in] */ HCHAPTER hChapter,
    /* [in] */ REFIID riid,
    /* [out] */ HCHAPTER __RPC_FAR *phChapterSource,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppView,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IRowsetView_RemoteGetView_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRowsetView_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_oledb_0087
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


#endif // OLEDBVER >= 0x0150
//@@@- V1.5
//@@@+ deprecated
#ifdef deprecated


extern RPC_IF_HANDLE __MIDL_itf_oledb_0087_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_oledb_0087_v0_0_s_ifspec;

#ifndef __IRowsetExactScroll_INTERFACE_DEFINED__
#define __IRowsetExactScroll_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRowsetExactScroll
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object][local] */ 



EXTERN_C const IID IID_IRowsetExactScroll;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a7f-2a1c-11ce-ade5-00aa0044773d")
    IRowsetExactScroll : public IRowsetScroll
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetExactPosition( 
            /* [in] */ HCHAPTER hChapter,
            /* [in] */ ULONG cbBookmark,
            /* [size_is][in] */ const BYTE __RPC_FAR *pBookmark,
            /* [out] */ ULONG __RPC_FAR *pulPosition,
            /* [out] */ ULONG __RPC_FAR *pcRows) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRowsetExactScrollVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRowsetExactScroll __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRowsetExactScroll __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRowsetExactScroll __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddRefRows )( 
            IRowsetExactScroll __RPC_FAR * This,
            /* [in] */ ULONG cRows,
            /* [size_is][in] */ const HROW __RPC_FAR rghRows[  ],
            /* [size_is][out] */ ULONG __RPC_FAR rgRefCounts[  ],
            /* [size_is][out] */ DBROWSTATUS __RPC_FAR rgRowStatus[  ]);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetData )( 
            IRowsetExactScroll __RPC_FAR * This,
            /* [in] */ HROW hRow,
            /* [in] */ HACCESSOR hAccessor,
            /* [out] */ void __RPC_FAR *pData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextRows )( 
            IRowsetExactScroll __RPC_FAR * This,
            /* [in] */ HCHAPTER hReserved,
            /* [in] */ LONG lRowsOffset,
            /* [in] */ LONG cRows,
            /* [out] */ ULONG __RPC_FAR *pcRowsObtained,
            /* [size_is][size_is][out] */ HROW __RPC_FAR *__RPC_FAR *prghRows);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReleaseRows )( 
            IRowsetExactScroll __RPC_FAR * This,
            /* [in] */ ULONG cRows,
            /* [size_is][in] */ const HROW __RPC_FAR rghRows[  ],
            /* [size_is][in] */ DBROWOPTIONS __RPC_FAR rgRowOptions[  ],
            /* [size_is][out] */ ULONG __RPC_FAR rgRefCounts[  ],
            /* [size_is][out] */ DBROWSTATUS __RPC_FAR rgRowStatus[  ]);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RestartPosition )( 
            IRowsetExactScroll __RPC_FAR * This,
            /* [in] */ HCHAPTER hReserved);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Compare )( 
            IRowsetExactScroll __RPC_FAR * This,
            /* [in] */ HCHAPTER hReserved,
            /* [in] */ ULONG cbBookmark1,
            /* [size_is][in] */ const BYTE __RPC_FAR *pBookmark1,
            /* [in] */ ULONG cbBookmark2,
            /* [size_is][in] */ const BYTE __RPC_FAR *pBookmark2,
            /* [out] */ DBCOMPARE __RPC_FAR *pComparison);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRowsAt )( 
            IRowsetExactScroll __RPC_FAR * This,
            /* [in] */ HWATCHREGION hReserved1,
            /* [in] */ HCHAPTER hReserved2,
            /* [in] */ ULONG cbBookmark,
            /* [size_is][in] */ const BYTE __RPC_FAR *pBookmark,
            /* [in] */ LONG lRowsOffset,
            /* [in] */ LONG cRows,
            /* [out] */ ULONG __RPC_FAR *pcRowsObtained,
            /* [size_is][size_is][out] */ HROW __RPC_FAR *__RPC_FAR *prghRows);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRowsByBookmark )( 
            IRowsetExactScroll __RPC_FAR * This,
            /* [in] */ HCHAPTER hReserved,
            /* [in] */ ULONG cRows,
            /* [size_is][in] */ const ULONG __RPC_FAR rgcbBookmarks[  ],
            /* [size_is][in] */ const BYTE __RPC_FAR *__RPC_FAR rgpBookmarks[  ],
            /* [size_is][out] */ HROW __RPC_FAR rghRows[  ],
            /* [size_is][out] */ DBROWSTATUS __RPC_FAR rgRowStatus[  ]);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Hash )( 
            IRowsetExactScroll __RPC_FAR * This,
            /* [in] */ HCHAPTER hReserved,
            /* [in] */ ULONG cBookmarks,
            /* [size_is][in] */ const ULONG __RPC_FAR rgcbBookmarks[  ],
            /* [size_is][in] */ const BYTE __RPC_FAR *__RPC_FAR rgpBookmarks[  ],
            /* [size_is][out] */ DWORD __RPC_FAR rgHashedValues[  ],
            /* [size_is][out] */ DBROWSTATUS __RPC_FAR rgBookmarkStatus[  ]);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetApproximatePosition )( 
            IRowsetExactScroll __RPC_FAR * This,
            /* [in] */ HCHAPTER hReserved,
            /* [in] */ ULONG cbBookmark,
            /* [size_is][in] */ const BYTE __RPC_FAR *pBookmark,
            /* [out] */ ULONG __RPC_FAR *pulPosition,
            /* [out] */ ULONG __RPC_FAR *pcRows);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRowsAtRatio )( 
            IRowsetExactScroll __RPC_FAR * This,
            /* [in] */ HWATCHREGION hReserved1,
            /* [in] */ HCHAPTER hReserved2,
            /* [in] */ ULONG ulNumerator,
            /* [in] */ ULONG ulDenominator,
            /* [in] */ LONG cRows,
            /* [out] */ ULONG __RPC_FAR *pcRowsObtained,
            /* [size_is][size_is][out] */ HROW __RPC_FAR *__RPC_FAR *prghRows);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetExactPosition )( 
            IRowsetExactScroll __RPC_FAR * This,
            /* [in] */ HCHAPTER hChapter,
            /* [in] */ ULONG cbBookmark,
            /* [size_is][in] */ const BYTE __RPC_FAR *pBookmark,
            /* [out] */ ULONG __RPC_FAR *pulPosition,
            /* [out] */ ULONG __RPC_FAR *pcRows);
        
        END_INTERFACE
    } IRowsetExactScrollVtbl;

    interface IRowsetExactScroll
    {
        CONST_VTBL struct IRowsetExactScrollVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRowsetExactScroll_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRowsetExactScroll_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRowsetExactScroll_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRowsetExactScroll_AddRefRows(This,cRows,rghRows,rgRefCounts,rgRowStatus)	\
    (This)->lpVtbl -> AddRefRows(This,cRows,rghRows,rgRefCounts,rgRowStatus)

#define IRowsetExactScroll_GetData(This,hRow,hAccessor,pData)	\
    (This)->lpVtbl -> GetData(This,hRow,hAccessor,pData)

#define IRowsetExactScroll_GetNextRows(This,hReserved,lRowsOffset,cRows,pcRowsObtained,prghRows)	\
    (This)->lpVtbl -> GetNextRows(This,hReserved,lRowsOffset,cRows,pcRowsObtained,prghRows)

#define IRowsetExactScroll_ReleaseRows(This,cRows,rghRows,rgRowOptions,rgRefCounts,rgRowStatus)	\
    (This)->lpVtbl -> ReleaseRows(This,cRows,rghRows,rgRowOptions,rgRefCounts,rgRowStatus)

#define IRowsetExactScroll_RestartPosition(This,hReserved)	\
    (This)->lpVtbl -> RestartPosition(This,hReserved)


#define IRowsetExactScroll_Compare(This,hReserved,cbBookmark1,pBookmark1,cbBookmark2,pBookmark2,pComparison)	\
    (This)->lpVtbl -> Compare(This,hReserved,cbBookmark1,pBookmark1,cbBookmark2,pBookmark2,pComparison)

#define IRowsetExactScroll_GetRowsAt(This,hReserved1,hReserved2,cbBookmark,pBookmark,lRowsOffset,cRows,pcRowsObtained,prghRows)	\
    (This)->lpVtbl -> GetRowsAt(This,hReserved1,hReserved2,cbBookmark,pBookmark,lRowsOffset,cRows,pcRowsObtained,prghRows)

#define IRowsetExactScroll_GetRowsByBookmark(This,hReserved,cRows,rgcbBookmarks,rgpBookmarks,rghRows,rgRowStatus)	\
    (This)->lpVtbl -> GetRowsByBookmark(This,hReserved,cRows,rgcbBookmarks,rgpBookmarks,rghRows,rgRowStatus)

#define IRowsetExactScroll_Hash(This,hReserved,cBookmarks,rgcbBookmarks,rgpBookmarks,rgHashedValues,rgBookmarkStatus)	\
    (This)->lpVtbl -> Hash(This,hReserved,cBookmarks,rgcbBookmarks,rgpBookmarks,rgHashedValues,rgBookmarkStatus)


#define IRowsetExactScroll_GetApproximatePosition(This,hReserved,cbBookmark,pBookmark,pulPosition,pcRows)	\
    (This)->lpVtbl -> GetApproximatePosition(This,hReserved,cbBookmark,pBookmark,pulPosition,pcRows)

#define IRowsetExactScroll_GetRowsAtRatio(This,hReserved1,hReserved2,ulNumerator,ulDenominator,cRows,pcRowsObtained,prghRows)	\
    (This)->lpVtbl -> GetRowsAtRatio(This,hReserved1,hReserved2,ulNumerator,ulDenominator,cRows,pcRowsObtained,prghRows)


#define IRowsetExactScroll_GetExactPosition(This,hChapter,cbBookmark,pBookmark,pulPosition,pcRows)	\
    (This)->lpVtbl -> GetExactPosition(This,hChapter,cbBookmark,pBookmark,pulPosition,pcRows)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRowsetExactScroll_GetExactPosition_Proxy( 
    IRowsetExactScroll __RPC_FAR * This,
    /* [in] */ HCHAPTER hChapter,
    /* [in] */ ULONG cbBookmark,
    /* [size_is][in] */ const BYTE __RPC_FAR *pBookmark,
    /* [out] */ ULONG __RPC_FAR *pulPosition,
    /* [out] */ ULONG __RPC_FAR *pcRows);


void __RPC_STUB IRowsetExactScroll_GetExactPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRowsetExactScroll_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_oledb_0088
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


#endif // deprecated
//@@@- deprecated


extern RPC_IF_HANDLE __MIDL_itf_oledb_0088_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_oledb_0088_v0_0_s_ifspec;

#ifndef __IRowsetChange_INTERFACE_DEFINED__
#define __IRowsetChange_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRowsetChange
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object][local] */ 



EXTERN_C const IID IID_IRowsetChange;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a05-2a1c-11ce-ade5-00aa0044773d")
    IRowsetChange : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE DeleteRows( 
            /* [in] */ HCHAPTER hReserved,
            /* [in] */ ULONG cRows,
            /* [size_is][in] */ const HROW __RPC_FAR rghRows[  ],
            /* [size_is][out] */ DBROWSTATUS __RPC_FAR rgRowStatus[  ]) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetData( 
            /* [in] */ HROW hRow,
            /* [in] */ HACCESSOR hAccessor,
            /* [in] */ void __RPC_FAR *pData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InsertRow( 
            /* [in] */ HCHAPTER hReserved,
            /* [in] */ HACCESSOR hAccessor,
            /* [in] */ void __RPC_FAR *pData,
            /* [out] */ HROW __RPC_FAR *phRow) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRowsetChangeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRowsetChange __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRowsetChange __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRowsetChange __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteRows )( 
            IRowsetChange __RPC_FAR * This,
            /* [in] */ HCHAPTER hReserved,
            /* [in] */ ULONG cRows,
            /* [size_is][in] */ const HROW __RPC_FAR rghRows[  ],
            /* [size_is][out] */ DBROWSTATUS __RPC_FAR rgRowStatus[  ]);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetData )( 
            IRowsetChange __RPC_FAR * This,
            /* [in] */ HROW hRow,
            /* [in] */ HACCESSOR hAccessor,
            /* [in] */ void __RPC_FAR *pData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InsertRow )( 
            IRowsetChange __RPC_FAR * This,
            /* [in] */ HCHAPTER hReserved,
            /* [in] */ HACCESSOR hAccessor,
            /* [in] */ void __RPC_FAR *pData,
            /* [out] */ HROW __RPC_FAR *phRow);
        
        END_INTERFACE
    } IRowsetChangeVtbl;

    interface IRowsetChange
    {
        CONST_VTBL struct IRowsetChangeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRowsetChange_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRowsetChange_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRowsetChange_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRowsetChange_DeleteRows(This,hReserved,cRows,rghRows,rgRowStatus)	\
    (This)->lpVtbl -> DeleteRows(This,hReserved,cRows,rghRows,rgRowStatus)

#define IRowsetChange_SetData(This,hRow,hAccessor,pData)	\
    (This)->lpVtbl -> SetData(This,hRow,hAccessor,pData)

#define IRowsetChange_InsertRow(This,hReserved,hAccessor,pData,phRow)	\
    (This)->lpVtbl -> InsertRow(This,hReserved,hAccessor,pData,phRow)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRowsetChange_DeleteRows_Proxy( 
    IRowsetChange __RPC_FAR * This,
    /* [in] */ HCHAPTER hReserved,
    /* [in] */ ULONG cRows,
    /* [size_is][in] */ const HROW __RPC_FAR rghRows[  ],
    /* [size_is][out] */ DBROWSTATUS __RPC_FAR rgRowStatus[  ]);


void __RPC_STUB IRowsetChange_DeleteRows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRowsetChange_SetData_Proxy( 
    IRowsetChange __RPC_FAR * This,
    /* [in] */ HROW hRow,
    /* [in] */ HACCESSOR hAccessor,
    /* [in] */ void __RPC_FAR *pData);


void __RPC_STUB IRowsetChange_SetData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRowsetChange_InsertRow_Proxy( 
    IRowsetChange __RPC_FAR * This,
    /* [in] */ HCHAPTER hReserved,
    /* [in] */ HACCESSOR hAccessor,
    /* [in] */ void __RPC_FAR *pData,
    /* [out] */ HROW __RPC_FAR *phRow);


void __RPC_STUB IRowsetChange_InsertRow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRowsetChange_INTERFACE_DEFINED__ */


#ifndef __IRowsetUpdate_INTERFACE_DEFINED__
#define __IRowsetUpdate_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRowsetUpdate
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object][local] */ 


typedef DWORD DBPENDINGSTATUS;


enum DBPENDINGSTATUSENUM
    {	DBPENDINGSTATUS_NEW	= 0x1,
	DBPENDINGSTATUS_CHANGED	= 0x2,
	DBPENDINGSTATUS_DELETED	= 0x4,
	DBPENDINGSTATUS_UNCHANGED	= 0x8,
	DBPENDINGSTATUS_INVALIDROW	= 0x10
    };

EXTERN_C const IID IID_IRowsetUpdate;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a6d-2a1c-11ce-ade5-00aa0044773d")
    IRowsetUpdate : public IRowsetChange
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetOriginalData( 
            /* [in] */ HROW hRow,
            /* [in] */ HACCESSOR hAccessor,
            /* [out] */ void __RPC_FAR *pData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPendingRows( 
            /* [in] */ HCHAPTER hReserved,
            /* [in] */ DBPENDINGSTATUS dwRowStatus,
            /* [out][in] */ ULONG __RPC_FAR *pcPendingRows,
            /* [size_is][size_is][out] */ HROW __RPC_FAR *__RPC_FAR *prgPendingRows,
            /* [size_is][size_is][out] */ DBPENDINGSTATUS __RPC_FAR *__RPC_FAR *prgPendingStatus) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRowStatus( 
            /* [in] */ HCHAPTER hReserved,
            /* [in] */ ULONG cRows,
            /* [size_is][in] */ const HROW __RPC_FAR rghRows[  ],
            /* [size_is][out] */ DBPENDINGSTATUS __RPC_FAR rgPendingStatus[  ]) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Undo( 
            /* [in] */ HCHAPTER hReserved,
            /* [in] */ ULONG cRows,
            /* [size_is][in] */ const HROW __RPC_FAR rghRows[  ],
            /* [out][in] */ ULONG __RPC_FAR *pcRowsUndone,
            /* [size_is][size_is][out] */ HROW __RPC_FAR *__RPC_FAR *prgRowsUndone,
            /* [size_is][size_is][out] */ DBROWSTATUS __RPC_FAR *__RPC_FAR *prgRowStatus) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Update( 
            /* [in] */ HCHAPTER hReserved,
            /* [in] */ ULONG cRows,
            /* [size_is][in] */ const HROW __RPC_FAR rghRows[  ],
            /* [out][in] */ ULONG __RPC_FAR *pcRows,
            /* [size_is][size_is][out] */ HROW __RPC_FAR *__RPC_FAR *prgRows,
            /* [size_is][size_is][out] */ DBROWSTATUS __RPC_FAR *__RPC_FAR *prgRowStatus) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRowsetUpdateVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRowsetUpdate __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRowsetUpdate __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRowsetUpdate __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteRows )( 
            IRowsetUpdate __RPC_FAR * This,
            /* [in] */ HCHAPTER hReserved,
            /* [in] */ ULONG cRows,
            /* [size_is][in] */ const HROW __RPC_FAR rghRows[  ],
            /* [size_is][out] */ DBROWSTATUS __RPC_FAR rgRowStatus[  ]);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetData )( 
            IRowsetUpdate __RPC_FAR * This,
            /* [in] */ HROW hRow,
            /* [in] */ HACCESSOR hAccessor,
            /* [in] */ void __RPC_FAR *pData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InsertRow )( 
            IRowsetUpdate __RPC_FAR * This,
            /* [in] */ HCHAPTER hReserved,
            /* [in] */ HACCESSOR hAccessor,
            /* [in] */ void __RPC_FAR *pData,
            /* [out] */ HROW __RPC_FAR *phRow);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOriginalData )( 
            IRowsetUpdate __RPC_FAR * This,
            /* [in] */ HROW hRow,
            /* [in] */ HACCESSOR hAccessor,
            /* [out] */ void __RPC_FAR *pData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPendingRows )( 
            IRowsetUpdate __RPC_FAR * This,
            /* [in] */ HCHAPTER hReserved,
            /* [in] */ DBPENDINGSTATUS dwRowStatus,
            /* [out][in] */ ULONG __RPC_FAR *pcPendingRows,
            /* [size_is][size_is][out] */ HROW __RPC_FAR *__RPC_FAR *prgPendingRows,
            /* [size_is][size_is][out] */ DBPENDINGSTATUS __RPC_FAR *__RPC_FAR *prgPendingStatus);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRowStatus )( 
            IRowsetUpdate __RPC_FAR * This,
            /* [in] */ HCHAPTER hReserved,
            /* [in] */ ULONG cRows,
            /* [size_is][in] */ const HROW __RPC_FAR rghRows[  ],
            /* [size_is][out] */ DBPENDINGSTATUS __RPC_FAR rgPendingStatus[  ]);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Undo )( 
            IRowsetUpdate __RPC_FAR * This,
            /* [in] */ HCHAPTER hReserved,
            /* [in] */ ULONG cRows,
            /* [size_is][in] */ const HROW __RPC_FAR rghRows[  ],
            /* [out][in] */ ULONG __RPC_FAR *pcRowsUndone,
            /* [size_is][size_is][out] */ HROW __RPC_FAR *__RPC_FAR *prgRowsUndone,
            /* [size_is][size_is][out] */ DBROWSTATUS __RPC_FAR *__RPC_FAR *prgRowStatus);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Update )( 
            IRowsetUpdate __RPC_FAR * This,
            /* [in] */ HCHAPTER hReserved,
            /* [in] */ ULONG cRows,
            /* [size_is][in] */ const HROW __RPC_FAR rghRows[  ],
            /* [out][in] */ ULONG __RPC_FAR *pcRows,
            /* [size_is][size_is][out] */ HROW __RPC_FAR *__RPC_FAR *prgRows,
            /* [size_is][size_is][out] */ DBROWSTATUS __RPC_FAR *__RPC_FAR *prgRowStatus);
        
        END_INTERFACE
    } IRowsetUpdateVtbl;

    interface IRowsetUpdate
    {
        CONST_VTBL struct IRowsetUpdateVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRowsetUpdate_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRowsetUpdate_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRowsetUpdate_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRowsetUpdate_DeleteRows(This,hReserved,cRows,rghRows,rgRowStatus)	\
    (This)->lpVtbl -> DeleteRows(This,hReserved,cRows,rghRows,rgRowStatus)

#define IRowsetUpdate_SetData(This,hRow,hAccessor,pData)	\
    (This)->lpVtbl -> SetData(This,hRow,hAccessor,pData)

#define IRowsetUpdate_InsertRow(This,hReserved,hAccessor,pData,phRow)	\
    (This)->lpVtbl -> InsertRow(This,hReserved,hAccessor,pData,phRow)


#define IRowsetUpdate_GetOriginalData(This,hRow,hAccessor,pData)	\
    (This)->lpVtbl -> GetOriginalData(This,hRow,hAccessor,pData)

#define IRowsetUpdate_GetPendingRows(This,hReserved,dwRowStatus,pcPendingRows,prgPendingRows,prgPendingStatus)	\
    (This)->lpVtbl -> GetPendingRows(This,hReserved,dwRowStatus,pcPendingRows,prgPendingRows,prgPendingStatus)

#define IRowsetUpdate_GetRowStatus(This,hReserved,cRows,rghRows,rgPendingStatus)	\
    (This)->lpVtbl -> GetRowStatus(This,hReserved,cRows,rghRows,rgPendingStatus)

#define IRowsetUpdate_Undo(This,hReserved,cRows,rghRows,pcRowsUndone,prgRowsUndone,prgRowStatus)	\
    (This)->lpVtbl -> Undo(This,hReserved,cRows,rghRows,pcRowsUndone,prgRowsUndone,prgRowStatus)

#define IRowsetUpdate_Update(This,hReserved,cRows,rghRows,pcRows,prgRows,prgRowStatus)	\
    (This)->lpVtbl -> Update(This,hReserved,cRows,rghRows,pcRows,prgRows,prgRowStatus)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRowsetUpdate_GetOriginalData_Proxy( 
    IRowsetUpdate __RPC_FAR * This,
    /* [in] */ HROW hRow,
    /* [in] */ HACCESSOR hAccessor,
    /* [out] */ void __RPC_FAR *pData);


void __RPC_STUB IRowsetUpdate_GetOriginalData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRowsetUpdate_GetPendingRows_Proxy( 
    IRowsetUpdate __RPC_FAR * This,
    /* [in] */ HCHAPTER hReserved,
    /* [in] */ DBPENDINGSTATUS dwRowStatus,
    /* [out][in] */ ULONG __RPC_FAR *pcPendingRows,
    /* [size_is][size_is][out] */ HROW __RPC_FAR *__RPC_FAR *prgPendingRows,
    /* [size_is][size_is][out] */ DBPENDINGSTATUS __RPC_FAR *__RPC_FAR *prgPendingStatus);


void __RPC_STUB IRowsetUpdate_GetPendingRows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRowsetUpdate_GetRowStatus_Proxy( 
    IRowsetUpdate __RPC_FAR * This,
    /* [in] */ HCHAPTER hReserved,
    /* [in] */ ULONG cRows,
    /* [size_is][in] */ const HROW __RPC_FAR rghRows[  ],
    /* [size_is][out] */ DBPENDINGSTATUS __RPC_FAR rgPendingStatus[  ]);


void __RPC_STUB IRowsetUpdate_GetRowStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRowsetUpdate_Undo_Proxy( 
    IRowsetUpdate __RPC_FAR * This,
    /* [in] */ HCHAPTER hReserved,
    /* [in] */ ULONG cRows,
    /* [size_is][in] */ const HROW __RPC_FAR rghRows[  ],
    /* [out][in] */ ULONG __RPC_FAR *pcRowsUndone,
    /* [size_is][size_is][out] */ HROW __RPC_FAR *__RPC_FAR *prgRowsUndone,
    /* [size_is][size_is][out] */ DBROWSTATUS __RPC_FAR *__RPC_FAR *prgRowStatus);


void __RPC_STUB IRowsetUpdate_Undo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRowsetUpdate_Update_Proxy( 
    IRowsetUpdate __RPC_FAR * This,
    /* [in] */ HCHAPTER hReserved,
    /* [in] */ ULONG cRows,
    /* [size_is][in] */ const HROW __RPC_FAR rghRows[  ],
    /* [out][in] */ ULONG __RPC_FAR *pcRows,
    /* [size_is][size_is][out] */ HROW __RPC_FAR *__RPC_FAR *prgRows,
    /* [size_is][size_is][out] */ DBROWSTATUS __RPC_FAR *__RPC_FAR *prgRowStatus);


void __RPC_STUB IRowsetUpdate_Update_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRowsetUpdate_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_oledb_0090
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


//@@@+ V2.5
#if( OLEDBVER >= 0x0250 )


extern RPC_IF_HANDLE __MIDL_itf_oledb_0090_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_oledb_0090_v0_0_s_ifspec;

#ifndef __IRowsetNextRowset_INTERFACE_DEFINED__
#define __IRowsetNextRowset_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRowsetNextRowset
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object][local] */ 



EXTERN_C const IID IID_IRowsetNextRowset;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a72-2a1c-11ce-ade5-00aa0044773d")
    IRowsetNextRowset : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetNextRowset( 
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppNextRowset) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRowsetNextRowsetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRowsetNextRowset __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRowsetNextRowset __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRowsetNextRowset __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextRowset )( 
            IRowsetNextRowset __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppNextRowset);
        
        END_INTERFACE
    } IRowsetNextRowsetVtbl;

    interface IRowsetNextRowset
    {
        CONST_VTBL struct IRowsetNextRowsetVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRowsetNextRowset_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRowsetNextRowset_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRowsetNextRowset_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRowsetNextRowset_GetNextRowset(This,pUnkOuter,riid,ppNextRowset)	\
    (This)->lpVtbl -> GetNextRowset(This,pUnkOuter,riid,ppNextRowset)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRowsetNextRowset_GetNextRowset_Proxy( 
    IRowsetNextRowset __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppNextRowset);


void __RPC_STUB IRowsetNextRowset_GetNextRowset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRowsetNextRowset_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_oledb_0091
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


#endif // OLEDBVER >= 0x0250
//@@@- V2.5


extern RPC_IF_HANDLE __MIDL_itf_oledb_0091_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_oledb_0091_v0_0_s_ifspec;

#ifndef __IRowsetIdentity_INTERFACE_DEFINED__
#define __IRowsetIdentity_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRowsetIdentity
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IRowsetIdentity;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a09-2a1c-11ce-ade5-00aa0044773d")
    IRowsetIdentity : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE IsSameRow( 
            /* [in] */ HROW hThisRow,
            /* [in] */ HROW hThatRow) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRowsetIdentityVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRowsetIdentity __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRowsetIdentity __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRowsetIdentity __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsSameRow )( 
            IRowsetIdentity __RPC_FAR * This,
            /* [in] */ HROW hThisRow,
            /* [in] */ HROW hThatRow);
        
        END_INTERFACE
    } IRowsetIdentityVtbl;

    interface IRowsetIdentity
    {
        CONST_VTBL struct IRowsetIdentityVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRowsetIdentity_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRowsetIdentity_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRowsetIdentity_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRowsetIdentity_IsSameRow(This,hThisRow,hThatRow)	\
    (This)->lpVtbl -> IsSameRow(This,hThisRow,hThatRow)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE IRowsetIdentity_RemoteIsSameRow_Proxy( 
    IRowsetIdentity __RPC_FAR * This,
    /* [in] */ HROW hThisRow,
    /* [in] */ HROW hThatRow,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IRowsetIdentity_RemoteIsSameRow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRowsetIdentity_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_oledb_0092
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


//@@@+ V2.5
#if( OLEDBVER >= 0x0250 )


extern RPC_IF_HANDLE __MIDL_itf_oledb_0092_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_oledb_0092_v0_0_s_ifspec;

#ifndef __IRowsetNewRowAfter_INTERFACE_DEFINED__
#define __IRowsetNewRowAfter_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRowsetNewRowAfter
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object][local] */ 



EXTERN_C const IID IID_IRowsetNewRowAfter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a71-2a1c-11ce-ade5-00aa0044773d")
    IRowsetNewRowAfter : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetNewDataAfter( 
            /* [in] */ HCHAPTER hChapter,
            /* [in] */ ULONG cbbmPrevious,
            /* [size_is][in] */ const BYTE __RPC_FAR *pbmPrevious,
            /* [in] */ HACCESSOR hAccessor,
            /* [in] */ BYTE __RPC_FAR *pData,
            /* [out] */ HROW __RPC_FAR *phRow) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRowsetNewRowAfterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRowsetNewRowAfter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRowsetNewRowAfter __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRowsetNewRowAfter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetNewDataAfter )( 
            IRowsetNewRowAfter __RPC_FAR * This,
            /* [in] */ HCHAPTER hChapter,
            /* [in] */ ULONG cbbmPrevious,
            /* [size_is][in] */ const BYTE __RPC_FAR *pbmPrevious,
            /* [in] */ HACCESSOR hAccessor,
            /* [in] */ BYTE __RPC_FAR *pData,
            /* [out] */ HROW __RPC_FAR *phRow);
        
        END_INTERFACE
    } IRowsetNewRowAfterVtbl;

    interface IRowsetNewRowAfter
    {
        CONST_VTBL struct IRowsetNewRowAfterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRowsetNewRowAfter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRowsetNewRowAfter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRowsetNewRowAfter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRowsetNewRowAfter_SetNewDataAfter(This,hChapter,cbbmPrevious,pbmPrevious,hAccessor,pData,phRow)	\
    (This)->lpVtbl -> SetNewDataAfter(This,hChapter,cbbmPrevious,pbmPrevious,hAccessor,pData,phRow)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRowsetNewRowAfter_SetNewDataAfter_Proxy( 
    IRowsetNewRowAfter __RPC_FAR * This,
    /* [in] */ HCHAPTER hChapter,
    /* [in] */ ULONG cbbmPrevious,
    /* [size_is][in] */ const BYTE __RPC_FAR *pbmPrevious,
    /* [in] */ HACCESSOR hAccessor,
    /* [in] */ BYTE __RPC_FAR *pData,
    /* [out] */ HROW __RPC_FAR *phRow);


void __RPC_STUB IRowsetNewRowAfter_SetNewDataAfter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRowsetNewRowAfter_INTERFACE_DEFINED__ */


#ifndef __IRowsetWithParameters_INTERFACE_DEFINED__
#define __IRowsetWithParameters_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRowsetWithParameters
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object][local] */ 



EXTERN_C const IID IID_IRowsetWithParameters;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a6e-2a1c-11ce-ade5-00aa0044773d")
    IRowsetWithParameters : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetParameterInfo( 
            /* [out][in] */ ULONG __RPC_FAR *pcParams,
            /* [size_is][size_is][out] */ DBPARAMINFO __RPC_FAR *__RPC_FAR *prgParamInfo,
            /* [out] */ OLECHAR __RPC_FAR *__RPC_FAR *ppNamesBuffer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Requery( 
            /* [in] */ DBPARAMS __RPC_FAR *pParams,
            /* [out] */ ULONG __RPC_FAR *pulErrorParam,
            /* [out] */ HCHAPTER __RPC_FAR *phReserved) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRowsetWithParametersVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRowsetWithParameters __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRowsetWithParameters __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRowsetWithParameters __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetParameterInfo )( 
            IRowsetWithParameters __RPC_FAR * This,
            /* [out][in] */ ULONG __RPC_FAR *pcParams,
            /* [size_is][size_is][out] */ DBPARAMINFO __RPC_FAR *__RPC_FAR *prgParamInfo,
            /* [out] */ OLECHAR __RPC_FAR *__RPC_FAR *ppNamesBuffer);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Requery )( 
            IRowsetWithParameters __RPC_FAR * This,
            /* [in] */ DBPARAMS __RPC_FAR *pParams,
            /* [out] */ ULONG __RPC_FAR *pulErrorParam,
            /* [out] */ HCHAPTER __RPC_FAR *phReserved);
        
        END_INTERFACE
    } IRowsetWithParametersVtbl;

    interface IRowsetWithParameters
    {
        CONST_VTBL struct IRowsetWithParametersVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRowsetWithParameters_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRowsetWithParameters_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRowsetWithParameters_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRowsetWithParameters_GetParameterInfo(This,pcParams,prgParamInfo,ppNamesBuffer)	\
    (This)->lpVtbl -> GetParameterInfo(This,pcParams,prgParamInfo,ppNamesBuffer)

#define IRowsetWithParameters_Requery(This,pParams,pulErrorParam,phReserved)	\
    (This)->lpVtbl -> Requery(This,pParams,pulErrorParam,phReserved)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRowsetWithParameters_GetParameterInfo_Proxy( 
    IRowsetWithParameters __RPC_FAR * This,
    /* [out][in] */ ULONG __RPC_FAR *pcParams,
    /* [size_is][size_is][out] */ DBPARAMINFO __RPC_FAR *__RPC_FAR *prgParamInfo,
    /* [out] */ OLECHAR __RPC_FAR *__RPC_FAR *ppNamesBuffer);


void __RPC_STUB IRowsetWithParameters_GetParameterInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRowsetWithParameters_Requery_Proxy( 
    IRowsetWithParameters __RPC_FAR * This,
    /* [in] */ DBPARAMS __RPC_FAR *pParams,
    /* [out] */ ULONG __RPC_FAR *pulErrorParam,
    /* [out] */ HCHAPTER __RPC_FAR *phReserved);


void __RPC_STUB IRowsetWithParameters_Requery_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRowsetWithParameters_INTERFACE_DEFINED__ */


#ifndef __IRowsetAsynch_INTERFACE_DEFINED__
#define __IRowsetAsynch_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRowsetAsynch
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object][local] */ 



EXTERN_C const IID IID_IRowsetAsynch;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a0f-2a1c-11ce-ade5-00aa0044773d")
    IRowsetAsynch : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE RatioFinished( 
            /* [out] */ ULONG __RPC_FAR *pulDenominator,
            /* [out] */ ULONG __RPC_FAR *pulNumerator,
            /* [out] */ ULONG __RPC_FAR *pcRows,
            /* [out] */ BOOL __RPC_FAR *pfNewRows) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRowsetAsynchVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRowsetAsynch __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRowsetAsynch __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRowsetAsynch __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RatioFinished )( 
            IRowsetAsynch __RPC_FAR * This,
            /* [out] */ ULONG __RPC_FAR *pulDenominator,
            /* [out] */ ULONG __RPC_FAR *pulNumerator,
            /* [out] */ ULONG __RPC_FAR *pcRows,
            /* [out] */ BOOL __RPC_FAR *pfNewRows);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IRowsetAsynch __RPC_FAR * This);
        
        END_INTERFACE
    } IRowsetAsynchVtbl;

    interface IRowsetAsynch
    {
        CONST_VTBL struct IRowsetAsynchVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRowsetAsynch_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRowsetAsynch_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRowsetAsynch_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRowsetAsynch_RatioFinished(This,pulDenominator,pulNumerator,pcRows,pfNewRows)	\
    (This)->lpVtbl -> RatioFinished(This,pulDenominator,pulNumerator,pcRows,pfNewRows)

#define IRowsetAsynch_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRowsetAsynch_RatioFinished_Proxy( 
    IRowsetAsynch __RPC_FAR * This,
    /* [out] */ ULONG __RPC_FAR *pulDenominator,
    /* [out] */ ULONG __RPC_FAR *pulNumerator,
    /* [out] */ ULONG __RPC_FAR *pcRows,
    /* [out] */ BOOL __RPC_FAR *pfNewRows);


void __RPC_STUB IRowsetAsynch_RatioFinished_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRowsetAsynch_Stop_Proxy( 
    IRowsetAsynch __RPC_FAR * This);


void __RPC_STUB IRowsetAsynch_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRowsetAsynch_INTERFACE_DEFINED__ */


#ifndef __IRowsetKeys_INTERFACE_DEFINED__
#define __IRowsetKeys_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRowsetKeys
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object][local] */ 



EXTERN_C const IID IID_IRowsetKeys;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a12-2a1c-11ce-ade5-00aa0044773d")
    IRowsetKeys : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ListKeys( 
            /* [out][in] */ ULONG __RPC_FAR *pcColumns,
            /* [size_is][size_is][out] */ ULONG __RPC_FAR *__RPC_FAR *prgColumns) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRowsetKeysVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRowsetKeys __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRowsetKeys __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRowsetKeys __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ListKeys )( 
            IRowsetKeys __RPC_FAR * This,
            /* [out][in] */ ULONG __RPC_FAR *pcColumns,
            /* [size_is][size_is][out] */ ULONG __RPC_FAR *__RPC_FAR *prgColumns);
        
        END_INTERFACE
    } IRowsetKeysVtbl;

    interface IRowsetKeys
    {
        CONST_VTBL struct IRowsetKeysVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRowsetKeys_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRowsetKeys_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRowsetKeys_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRowsetKeys_ListKeys(This,pcColumns,prgColumns)	\
    (This)->lpVtbl -> ListKeys(This,pcColumns,prgColumns)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRowsetKeys_ListKeys_Proxy( 
    IRowsetKeys __RPC_FAR * This,
    /* [out][in] */ ULONG __RPC_FAR *pcColumns,
    /* [size_is][size_is][out] */ ULONG __RPC_FAR *__RPC_FAR *prgColumns);


void __RPC_STUB IRowsetKeys_ListKeys_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRowsetKeys_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_oledb_0096
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


#endif // OLEDBVER >= 0x0250
//@@@- V2.5


extern RPC_IF_HANDLE __MIDL_itf_oledb_0096_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_oledb_0096_v0_0_s_ifspec;

#ifndef __IRowsetNotify_INTERFACE_DEFINED__
#define __IRowsetNotify_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRowsetNotify
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IRowsetNotify;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a83-2a1c-11ce-ade5-00aa0044773d")
    IRowsetNotify : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE OnFieldChange( 
            /* [in] */ IRowset __RPC_FAR *pRowset,
            /* [in] */ HROW hRow,
            /* [in] */ ULONG cColumns,
            /* [size_is][in] */ ULONG __RPC_FAR rgColumns[  ],
            /* [in] */ DBREASON eReason,
            /* [in] */ DBEVENTPHASE ePhase,
            /* [in] */ BOOL fCantDeny) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE OnRowChange( 
            /* [in] */ IRowset __RPC_FAR *pRowset,
            /* [in] */ ULONG cRows,
            /* [size_is][in] */ const HROW __RPC_FAR rghRows[  ],
            /* [in] */ DBREASON eReason,
            /* [in] */ DBEVENTPHASE ePhase,
            /* [in] */ BOOL fCantDeny) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE OnRowsetChange( 
            /* [in] */ IRowset __RPC_FAR *pRowset,
            /* [in] */ DBREASON eReason,
            /* [in] */ DBEVENTPHASE ePhase,
            /* [in] */ BOOL fCantDeny) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRowsetNotifyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRowsetNotify __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRowsetNotify __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRowsetNotify __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnFieldChange )( 
            IRowsetNotify __RPC_FAR * This,
            /* [in] */ IRowset __RPC_FAR *pRowset,
            /* [in] */ HROW hRow,
            /* [in] */ ULONG cColumns,
            /* [size_is][in] */ ULONG __RPC_FAR rgColumns[  ],
            /* [in] */ DBREASON eReason,
            /* [in] */ DBEVENTPHASE ePhase,
            /* [in] */ BOOL fCantDeny);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnRowChange )( 
            IRowsetNotify __RPC_FAR * This,
            /* [in] */ IRowset __RPC_FAR *pRowset,
            /* [in] */ ULONG cRows,
            /* [size_is][in] */ const HROW __RPC_FAR rghRows[  ],
            /* [in] */ DBREASON eReason,
            /* [in] */ DBEVENTPHASE ePhase,
            /* [in] */ BOOL fCantDeny);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnRowsetChange )( 
            IRowsetNotify __RPC_FAR * This,
            /* [in] */ IRowset __RPC_FAR *pRowset,
            /* [in] */ DBREASON eReason,
            /* [in] */ DBEVENTPHASE ePhase,
            /* [in] */ BOOL fCantDeny);
        
        END_INTERFACE
    } IRowsetNotifyVtbl;

    interface IRowsetNotify
    {
        CONST_VTBL struct IRowsetNotifyVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRowsetNotify_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRowsetNotify_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRowsetNotify_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRowsetNotify_OnFieldChange(This,pRowset,hRow,cColumns,rgColumns,eReason,ePhase,fCantDeny)	\
    (This)->lpVtbl -> OnFieldChange(This,pRowset,hRow,cColumns,rgColumns,eReason,ePhase,fCantDeny)

#define IRowsetNotify_OnRowChange(This,pRowset,cRows,rghRows,eReason,ePhase,fCantDeny)	\
    (This)->lpVtbl -> OnRowChange(This,pRowset,cRows,rghRows,eReason,ePhase,fCantDeny)

#define IRowsetNotify_OnRowsetChange(This,pRowset,eReason,ePhase,fCantDeny)	\
    (This)->lpVtbl -> OnRowsetChange(This,pRowset,eReason,ePhase,fCantDeny)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE IRowsetNotify_RemoteOnFieldChange_Proxy( 
    IRowsetNotify __RPC_FAR * This,
    /* [in] */ IRowset __RPC_FAR *pRowset,
    /* [in] */ HROW hRow,
    /* [in] */ ULONG cColumns,
    /* [size_is][in] */ ULONG __RPC_FAR *rgColumns,
    /* [in] */ DBREASON eReason,
    /* [in] */ DBEVENTPHASE ePhase,
    /* [in] */ BOOL fCantDeny,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IRowsetNotify_RemoteOnFieldChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IRowsetNotify_RemoteOnRowChange_Proxy( 
    IRowsetNotify __RPC_FAR * This,
    /* [in] */ IRowset __RPC_FAR *pRowset,
    /* [in] */ ULONG cRows,
    /* [size_is][in] */ const HROW __RPC_FAR *rghRows,
    /* [in] */ DBREASON eReason,
    /* [in] */ DBEVENTPHASE ePhase,
    /* [in] */ BOOL fCantDeny,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IRowsetNotify_RemoteOnRowChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IRowsetNotify_RemoteOnRowsetChange_Proxy( 
    IRowsetNotify __RPC_FAR * This,
    /* [in] */ IRowset __RPC_FAR *pRowset,
    /* [in] */ DBREASON eReason,
    /* [in] */ DBEVENTPHASE ePhase,
    /* [in] */ BOOL fCantDeny,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IRowsetNotify_RemoteOnRowsetChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRowsetNotify_INTERFACE_DEFINED__ */


#ifndef __IRowsetIndex_INTERFACE_DEFINED__
#define __IRowsetIndex_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRowsetIndex
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object][local] */ 


typedef DWORD DBSEEK;


enum DBSEEKENUM
    {	DBSEEK_INVALID	= 0,
	DBSEEK_FIRSTEQ	= 0x1,
	DBSEEK_LASTEQ	= 0x2,
	DBSEEK_GE	= 0x4,
	DBSEEK_GT	= 0x8,
	DBSEEK_LE	= 0x10,
	DBSEEK_LT	= 0x20
    };
typedef DWORD DBRANGE;


enum DBRANGEENUM
    {	DBRANGE_INCLUSIVESTART	= 0,
	DBRANGE_INCLUSIVEEND	= 0,
	DBRANGE_EXCLUSIVESTART	= 0x1,
	DBRANGE_EXCLUSIVEEND	= 0x2,
	DBRANGE_EXCLUDENULLS	= 0x4,
	DBRANGE_PREFIX	= 0x8,
	DBRANGE_MATCH	= 0x10
    };
//@@@+ V2.0
#if( OLEDBVER >= 0x0200 )

enum DBRANGEENUM20
    {	DBRANGE_MATCH_N_SHIFT	= 0x18,
	DBRANGE_MATCH_N_MASK	= 0xff
    };
#endif // OLEDBVER >= 0x0200
//@@@- V2.0

EXTERN_C const IID IID_IRowsetIndex;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a82-2a1c-11ce-ade5-00aa0044773d")
    IRowsetIndex : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetIndexInfo( 
            /* [out][in] */ ULONG __RPC_FAR *pcKeyColumns,
            /* [size_is][size_is][out] */ DBINDEXCOLUMNDESC __RPC_FAR *__RPC_FAR *prgIndexColumnDesc,
            /* [out][in] */ ULONG __RPC_FAR *pcIndexProperties,
            /* [size_is][size_is][out] */ DBPROPSET __RPC_FAR *__RPC_FAR *prgIndexProperties) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Seek( 
            /* [in] */ HACCESSOR hAccessor,
            /* [in] */ ULONG cKeyValues,
            /* [in] */ void __RPC_FAR *pData,
            /* [in] */ DBSEEK dwSeekOptions) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetRange( 
            /* [in] */ HACCESSOR hAccessor,
            /* [in] */ ULONG cStartKeyColumns,
            /* [in] */ void __RPC_FAR *pStartData,
            /* [in] */ ULONG cEndKeyColumns,
            /* [in] */ void __RPC_FAR *pEndData,
            /* [in] */ DBRANGE dwRangeOptions) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRowsetIndexVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRowsetIndex __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRowsetIndex __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRowsetIndex __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIndexInfo )( 
            IRowsetIndex __RPC_FAR * This,
            /* [out][in] */ ULONG __RPC_FAR *pcKeyColumns,
            /* [size_is][size_is][out] */ DBINDEXCOLUMNDESC __RPC_FAR *__RPC_FAR *prgIndexColumnDesc,
            /* [out][in] */ ULONG __RPC_FAR *pcIndexProperties,
            /* [size_is][size_is][out] */ DBPROPSET __RPC_FAR *__RPC_FAR *prgIndexProperties);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Seek )( 
            IRowsetIndex __RPC_FAR * This,
            /* [in] */ HACCESSOR hAccessor,
            /* [in] */ ULONG cKeyValues,
            /* [in] */ void __RPC_FAR *pData,
            /* [in] */ DBSEEK dwSeekOptions);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetRange )( 
            IRowsetIndex __RPC_FAR * This,
            /* [in] */ HACCESSOR hAccessor,
            /* [in] */ ULONG cStartKeyColumns,
            /* [in] */ void __RPC_FAR *pStartData,
            /* [in] */ ULONG cEndKeyColumns,
            /* [in] */ void __RPC_FAR *pEndData,
            /* [in] */ DBRANGE dwRangeOptions);
        
        END_INTERFACE
    } IRowsetIndexVtbl;

    interface IRowsetIndex
    {
        CONST_VTBL struct IRowsetIndexVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRowsetIndex_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRowsetIndex_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRowsetIndex_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRowsetIndex_GetIndexInfo(This,pcKeyColumns,prgIndexColumnDesc,pcIndexProperties,prgIndexProperties)	\
    (This)->lpVtbl -> GetIndexInfo(This,pcKeyColumns,prgIndexColumnDesc,pcIndexProperties,prgIndexProperties)

#define IRowsetIndex_Seek(This,hAccessor,cKeyValues,pData,dwSeekOptions)	\
    (This)->lpVtbl -> Seek(This,hAccessor,cKeyValues,pData,dwSeekOptions)

#define IRowsetIndex_SetRange(This,hAccessor,cStartKeyColumns,pStartData,cEndKeyColumns,pEndData,dwRangeOptions)	\
    (This)->lpVtbl -> SetRange(This,hAccessor,cStartKeyColumns,pStartData,cEndKeyColumns,pEndData,dwRangeOptions)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRowsetIndex_GetIndexInfo_Proxy( 
    IRowsetIndex __RPC_FAR * This,
    /* [out][in] */ ULONG __RPC_FAR *pcKeyColumns,
    /* [size_is][size_is][out] */ DBINDEXCOLUMNDESC __RPC_FAR *__RPC_FAR *prgIndexColumnDesc,
    /* [out][in] */ ULONG __RPC_FAR *pcIndexProperties,
    /* [size_is][size_is][out] */ DBPROPSET __RPC_FAR *__RPC_FAR *prgIndexProperties);


void __RPC_STUB IRowsetIndex_GetIndexInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRowsetIndex_Seek_Proxy( 
    IRowsetIndex __RPC_FAR * This,
    /* [in] */ HACCESSOR hAccessor,
    /* [in] */ ULONG cKeyValues,
    /* [in] */ void __RPC_FAR *pData,
    /* [in] */ DBSEEK dwSeekOptions);


void __RPC_STUB IRowsetIndex_Seek_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRowsetIndex_SetRange_Proxy( 
    IRowsetIndex __RPC_FAR * This,
    /* [in] */ HACCESSOR hAccessor,
    /* [in] */ ULONG cStartKeyColumns,
    /* [in] */ void __RPC_FAR *pStartData,
    /* [in] */ ULONG cEndKeyColumns,
    /* [in] */ void __RPC_FAR *pEndData,
    /* [in] */ DBRANGE dwRangeOptions);


void __RPC_STUB IRowsetIndex_SetRange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRowsetIndex_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_oledb_0098
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


//@@@+ V2.5
#if( OLEDBVER >= 0x0250 )


extern RPC_IF_HANDLE __MIDL_itf_oledb_0098_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_oledb_0098_v0_0_s_ifspec;

#ifndef __IRowsetWatchAll_INTERFACE_DEFINED__
#define __IRowsetWatchAll_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRowsetWatchAll
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object][local] */ 



EXTERN_C const IID IID_IRowsetWatchAll;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a73-2a1c-11ce-ade5-00aa0044773d")
    IRowsetWatchAll : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Acknowledge( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Start( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StopWatching( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRowsetWatchAllVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRowsetWatchAll __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRowsetWatchAll __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRowsetWatchAll __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Acknowledge )( 
            IRowsetWatchAll __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Start )( 
            IRowsetWatchAll __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StopWatching )( 
            IRowsetWatchAll __RPC_FAR * This);
        
        END_INTERFACE
    } IRowsetWatchAllVtbl;

    interface IRowsetWatchAll
    {
        CONST_VTBL struct IRowsetWatchAllVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRowsetWatchAll_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRowsetWatchAll_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRowsetWatchAll_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRowsetWatchAll_Acknowledge(This)	\
    (This)->lpVtbl -> Acknowledge(This)

#define IRowsetWatchAll_Start(This)	\
    (This)->lpVtbl -> Start(This)

#define IRowsetWatchAll_StopWatching(This)	\
    (This)->lpVtbl -> StopWatching(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRowsetWatchAll_Acknowledge_Proxy( 
    IRowsetWatchAll __RPC_FAR * This);


void __RPC_STUB IRowsetWatchAll_Acknowledge_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRowsetWatchAll_Start_Proxy( 
    IRowsetWatchAll __RPC_FAR * This);


void __RPC_STUB IRowsetWatchAll_Start_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRowsetWatchAll_StopWatching_Proxy( 
    IRowsetWatchAll __RPC_FAR * This);


void __RPC_STUB IRowsetWatchAll_StopWatching_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRowsetWatchAll_INTERFACE_DEFINED__ */


#ifndef __IRowsetWatchNotify_INTERFACE_DEFINED__
#define __IRowsetWatchNotify_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRowsetWatchNotify
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object][local] */ 


typedef DWORD DBWATCHNOTIFY;


enum DBWATCHNOTIFYENUM
    {	DBWATCHNOTIFY_ROWSCHANGED	= 1,
	DBWATCHNOTIFY_QUERYDONE	= 2,
	DBWATCHNOTIFY_QUERYREEXECUTED	= 3
    };

EXTERN_C const IID IID_IRowsetWatchNotify;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a44-2a1c-11ce-ade5-00aa0044773d")
    IRowsetWatchNotify : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnChange( 
            /* [in] */ IRowset __RPC_FAR *pRowset,
            /* [in] */ DBWATCHNOTIFY eChangeReason) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRowsetWatchNotifyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRowsetWatchNotify __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRowsetWatchNotify __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRowsetWatchNotify __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnChange )( 
            IRowsetWatchNotify __RPC_FAR * This,
            /* [in] */ IRowset __RPC_FAR *pRowset,
            /* [in] */ DBWATCHNOTIFY eChangeReason);
        
        END_INTERFACE
    } IRowsetWatchNotifyVtbl;

    interface IRowsetWatchNotify
    {
        CONST_VTBL struct IRowsetWatchNotifyVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRowsetWatchNotify_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRowsetWatchNotify_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRowsetWatchNotify_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRowsetWatchNotify_OnChange(This,pRowset,eChangeReason)	\
    (This)->lpVtbl -> OnChange(This,pRowset,eChangeReason)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRowsetWatchNotify_OnChange_Proxy( 
    IRowsetWatchNotify __RPC_FAR * This,
    /* [in] */ IRowset __RPC_FAR *pRowset,
    /* [in] */ DBWATCHNOTIFY eChangeReason);


void __RPC_STUB IRowsetWatchNotify_OnChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRowsetWatchNotify_INTERFACE_DEFINED__ */


#ifndef __IRowsetWatchRegion_INTERFACE_DEFINED__
#define __IRowsetWatchRegion_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRowsetWatchRegion
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object][local] */ 


typedef DWORD DBWATCHMODE;


enum DBWATCHMODEENUM
    {	DBWATCHMODE_ALL	= 0x1,
	DBWATCHMODE_EXTEND	= 0x2,
	DBWATCHMODE_MOVE	= 0x4,
	DBWATCHMODE_COUNT	= 0x8
    };
typedef DWORD DBROWCHANGEKIND;


enum DBROWCHANGEKINDENUM
    {	DBROWCHANGEKIND_INSERT	= 0,
	DBROWCHANGEKIND_DELETE	= DBROWCHANGEKIND_INSERT + 1,
	DBROWCHANGEKIND_UPDATE	= DBROWCHANGEKIND_DELETE + 1,
	DBROWCHANGEKIND_COUNT	= DBROWCHANGEKIND_UPDATE + 1
    };
typedef struct  tagDBROWWATCHRANGE
    {
    HWATCHREGION hRegion;
    DBROWCHANGEKIND eChangeKind;
    HROW hRow;
    ULONG iRow;
    }	DBROWWATCHCHANGE;


EXTERN_C const IID IID_IRowsetWatchRegion;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a45-2a1c-11ce-ade5-00aa0044773d")
    IRowsetWatchRegion : public IRowsetWatchAll
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CreateWatchRegion( 
            /* [in] */ DBWATCHMODE dwWatchMode,
            /* [out] */ HWATCHREGION __RPC_FAR *phRegion) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ChangeWatchMode( 
            /* [in] */ HWATCHREGION hRegion,
            /* [in] */ DBWATCHMODE dwWatchMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DeleteWatchRegion( 
            /* [in] */ HWATCHREGION hRegion) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetWatchRegionInfo( 
            /* [in] */ HWATCHREGION hRegion,
            /* [out] */ DBWATCHMODE __RPC_FAR *pdwWatchMode,
            /* [out] */ HCHAPTER __RPC_FAR *phChapter,
            /* [out][in] */ ULONG __RPC_FAR *pcbBookmark,
            /* [size_is][size_is][out] */ BYTE __RPC_FAR *__RPC_FAR *ppBookmark,
            /* [out] */ LONG __RPC_FAR *pcRows) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Refresh( 
            /* [out][in] */ ULONG __RPC_FAR *pcChangesObtained,
            /* [size_is][size_is][out] */ DBROWWATCHCHANGE __RPC_FAR *__RPC_FAR *prgChanges) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ShrinkWatchRegion( 
            /* [in] */ HWATCHREGION hRegion,
            /* [in] */ HCHAPTER hChapter,
            /* [in] */ ULONG cbBookmark,
            /* [size_is][in] */ BYTE __RPC_FAR *pBookmark,
            /* [in] */ LONG cRows) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRowsetWatchRegionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRowsetWatchRegion __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRowsetWatchRegion __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRowsetWatchRegion __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Acknowledge )( 
            IRowsetWatchRegion __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Start )( 
            IRowsetWatchRegion __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StopWatching )( 
            IRowsetWatchRegion __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateWatchRegion )( 
            IRowsetWatchRegion __RPC_FAR * This,
            /* [in] */ DBWATCHMODE dwWatchMode,
            /* [out] */ HWATCHREGION __RPC_FAR *phRegion);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ChangeWatchMode )( 
            IRowsetWatchRegion __RPC_FAR * This,
            /* [in] */ HWATCHREGION hRegion,
            /* [in] */ DBWATCHMODE dwWatchMode);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteWatchRegion )( 
            IRowsetWatchRegion __RPC_FAR * This,
            /* [in] */ HWATCHREGION hRegion);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetWatchRegionInfo )( 
            IRowsetWatchRegion __RPC_FAR * This,
            /* [in] */ HWATCHREGION hRegion,
            /* [out] */ DBWATCHMODE __RPC_FAR *pdwWatchMode,
            /* [out] */ HCHAPTER __RPC_FAR *phChapter,
            /* [out][in] */ ULONG __RPC_FAR *pcbBookmark,
            /* [size_is][size_is][out] */ BYTE __RPC_FAR *__RPC_FAR *ppBookmark,
            /* [out] */ LONG __RPC_FAR *pcRows);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IRowsetWatchRegion __RPC_FAR * This,
            /* [out][in] */ ULONG __RPC_FAR *pcChangesObtained,
            /* [size_is][size_is][out] */ DBROWWATCHCHANGE __RPC_FAR *__RPC_FAR *prgChanges);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShrinkWatchRegion )( 
            IRowsetWatchRegion __RPC_FAR * This,
            /* [in] */ HWATCHREGION hRegion,
            /* [in] */ HCHAPTER hChapter,
            /* [in] */ ULONG cbBookmark,
            /* [size_is][in] */ BYTE __RPC_FAR *pBookmark,
            /* [in] */ LONG cRows);
        
        END_INTERFACE
    } IRowsetWatchRegionVtbl;

    interface IRowsetWatchRegion
    {
        CONST_VTBL struct IRowsetWatchRegionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRowsetWatchRegion_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRowsetWatchRegion_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRowsetWatchRegion_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRowsetWatchRegion_Acknowledge(This)	\
    (This)->lpVtbl -> Acknowledge(This)

#define IRowsetWatchRegion_Start(This)	\
    (This)->lpVtbl -> Start(This)

#define IRowsetWatchRegion_StopWatching(This)	\
    (This)->lpVtbl -> StopWatching(This)


#define IRowsetWatchRegion_CreateWatchRegion(This,dwWatchMode,phRegion)	\
    (This)->lpVtbl -> CreateWatchRegion(This,dwWatchMode,phRegion)

#define IRowsetWatchRegion_ChangeWatchMode(This,hRegion,dwWatchMode)	\
    (This)->lpVtbl -> ChangeWatchMode(This,hRegion,dwWatchMode)

#define IRowsetWatchRegion_DeleteWatchRegion(This,hRegion)	\
    (This)->lpVtbl -> DeleteWatchRegion(This,hRegion)

#define IRowsetWatchRegion_GetWatchRegionInfo(This,hRegion,pdwWatchMode,phChapter,pcbBookmark,ppBookmark,pcRows)	\
    (This)->lpVtbl -> GetWatchRegionInfo(This,hRegion,pdwWatchMode,phChapter,pcbBookmark,ppBookmark,pcRows)

#define IRowsetWatchRegion_Refresh(This,pcChangesObtained,prgChanges)	\
    (This)->lpVtbl -> Refresh(This,pcChangesObtained,prgChanges)

#define IRowsetWatchRegion_ShrinkWatchRegion(This,hRegion,hChapter,cbBookmark,pBookmark,cRows)	\
    (This)->lpVtbl -> ShrinkWatchRegion(This,hRegion,hChapter,cbBookmark,pBookmark,cRows)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRowsetWatchRegion_CreateWatchRegion_Proxy( 
    IRowsetWatchRegion __RPC_FAR * This,
    /* [in] */ DBWATCHMODE dwWatchMode,
    /* [out] */ HWATCHREGION __RPC_FAR *phRegion);


void __RPC_STUB IRowsetWatchRegion_CreateWatchRegion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRowsetWatchRegion_ChangeWatchMode_Proxy( 
    IRowsetWatchRegion __RPC_FAR * This,
    /* [in] */ HWATCHREGION hRegion,
    /* [in] */ DBWATCHMODE dwWatchMode);


void __RPC_STUB IRowsetWatchRegion_ChangeWatchMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRowsetWatchRegion_DeleteWatchRegion_Proxy( 
    IRowsetWatchRegion __RPC_FAR * This,
    /* [in] */ HWATCHREGION hRegion);


void __RPC_STUB IRowsetWatchRegion_DeleteWatchRegion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRowsetWatchRegion_GetWatchRegionInfo_Proxy( 
    IRowsetWatchRegion __RPC_FAR * This,
    /* [in] */ HWATCHREGION hRegion,
    /* [out] */ DBWATCHMODE __RPC_FAR *pdwWatchMode,
    /* [out] */ HCHAPTER __RPC_FAR *phChapter,
    /* [out][in] */ ULONG __RPC_FAR *pcbBookmark,
    /* [size_is][size_is][out] */ BYTE __RPC_FAR *__RPC_FAR *ppBookmark,
    /* [out] */ LONG __RPC_FAR *pcRows);


void __RPC_STUB IRowsetWatchRegion_GetWatchRegionInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRowsetWatchRegion_Refresh_Proxy( 
    IRowsetWatchRegion __RPC_FAR * This,
    /* [out][in] */ ULONG __RPC_FAR *pcChangesObtained,
    /* [size_is][size_is][out] */ DBROWWATCHCHANGE __RPC_FAR *__RPC_FAR *prgChanges);


void __RPC_STUB IRowsetWatchRegion_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRowsetWatchRegion_ShrinkWatchRegion_Proxy( 
    IRowsetWatchRegion __RPC_FAR * This,
    /* [in] */ HWATCHREGION hRegion,
    /* [in] */ HCHAPTER hChapter,
    /* [in] */ ULONG cbBookmark,
    /* [size_is][in] */ BYTE __RPC_FAR *pBookmark,
    /* [in] */ LONG cRows);


void __RPC_STUB IRowsetWatchRegion_ShrinkWatchRegion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRowsetWatchRegion_INTERFACE_DEFINED__ */


#ifndef __IRowsetCopyRows_INTERFACE_DEFINED__
#define __IRowsetCopyRows_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRowsetCopyRows
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object][local] */ 


typedef WORD HSOURCE;


EXTERN_C const IID IID_IRowsetCopyRows;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a6b-2a1c-11ce-ade5-00aa0044773d")
    IRowsetCopyRows : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CloseSource( 
            /* [in] */ HSOURCE hSourceID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CopyByHROWS( 
            /* [in] */ HSOURCE hSourceID,
            /* [in] */ HCHAPTER hReserved,
            /* [in] */ LONG cRows,
            /* [size_is][in] */ const HROW __RPC_FAR rghRows[  ],
            /* [in] */ ULONG bFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CopyRows( 
            /* [in] */ HSOURCE hSourceID,
            /* [in] */ HCHAPTER hReserved,
            /* [in] */ LONG cRows,
            /* [in] */ ULONG bFlags,
            /* [out] */ ULONG __RPC_FAR *pcRowsCopied) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DefineSource( 
            /* [in] */ const IRowset __RPC_FAR *pRowsetSource,
            /* [in] */ const ULONG cColIds,
            /* [size_is][in] */ const LONG __RPC_FAR rgSourceColumns[  ],
            /* [size_is][in] */ const LONG __RPC_FAR rgTargetColumns[  ],
            /* [out] */ HSOURCE __RPC_FAR *phSourceID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRowsetCopyRowsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRowsetCopyRows __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRowsetCopyRows __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRowsetCopyRows __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CloseSource )( 
            IRowsetCopyRows __RPC_FAR * This,
            /* [in] */ HSOURCE hSourceID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CopyByHROWS )( 
            IRowsetCopyRows __RPC_FAR * This,
            /* [in] */ HSOURCE hSourceID,
            /* [in] */ HCHAPTER hReserved,
            /* [in] */ LONG cRows,
            /* [size_is][in] */ const HROW __RPC_FAR rghRows[  ],
            /* [in] */ ULONG bFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CopyRows )( 
            IRowsetCopyRows __RPC_FAR * This,
            /* [in] */ HSOURCE hSourceID,
            /* [in] */ HCHAPTER hReserved,
            /* [in] */ LONG cRows,
            /* [in] */ ULONG bFlags,
            /* [out] */ ULONG __RPC_FAR *pcRowsCopied);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DefineSource )( 
            IRowsetCopyRows __RPC_FAR * This,
            /* [in] */ const IRowset __RPC_FAR *pRowsetSource,
            /* [in] */ const ULONG cColIds,
            /* [size_is][in] */ const LONG __RPC_FAR rgSourceColumns[  ],
            /* [size_is][in] */ const LONG __RPC_FAR rgTargetColumns[  ],
            /* [out] */ HSOURCE __RPC_FAR *phSourceID);
        
        END_INTERFACE
    } IRowsetCopyRowsVtbl;

    interface IRowsetCopyRows
    {
        CONST_VTBL struct IRowsetCopyRowsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRowsetCopyRows_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRowsetCopyRows_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRowsetCopyRows_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRowsetCopyRows_CloseSource(This,hSourceID)	\
    (This)->lpVtbl -> CloseSource(This,hSourceID)

#define IRowsetCopyRows_CopyByHROWS(This,hSourceID,hReserved,cRows,rghRows,bFlags)	\
    (This)->lpVtbl -> CopyByHROWS(This,hSourceID,hReserved,cRows,rghRows,bFlags)

#define IRowsetCopyRows_CopyRows(This,hSourceID,hReserved,cRows,bFlags,pcRowsCopied)	\
    (This)->lpVtbl -> CopyRows(This,hSourceID,hReserved,cRows,bFlags,pcRowsCopied)

#define IRowsetCopyRows_DefineSource(This,pRowsetSource,cColIds,rgSourceColumns,rgTargetColumns,phSourceID)	\
    (This)->lpVtbl -> DefineSource(This,pRowsetSource,cColIds,rgSourceColumns,rgTargetColumns,phSourceID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRowsetCopyRows_CloseSource_Proxy( 
    IRowsetCopyRows __RPC_FAR * This,
    /* [in] */ HSOURCE hSourceID);


void __RPC_STUB IRowsetCopyRows_CloseSource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRowsetCopyRows_CopyByHROWS_Proxy( 
    IRowsetCopyRows __RPC_FAR * This,
    /* [in] */ HSOURCE hSourceID,
    /* [in] */ HCHAPTER hReserved,
    /* [in] */ LONG cRows,
    /* [size_is][in] */ const HROW __RPC_FAR rghRows[  ],
    /* [in] */ ULONG bFlags);


void __RPC_STUB IRowsetCopyRows_CopyByHROWS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRowsetCopyRows_CopyRows_Proxy( 
    IRowsetCopyRows __RPC_FAR * This,
    /* [in] */ HSOURCE hSourceID,
    /* [in] */ HCHAPTER hReserved,
    /* [in] */ LONG cRows,
    /* [in] */ ULONG bFlags,
    /* [out] */ ULONG __RPC_FAR *pcRowsCopied);


void __RPC_STUB IRowsetCopyRows_CopyRows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRowsetCopyRows_DefineSource_Proxy( 
    IRowsetCopyRows __RPC_FAR * This,
    /* [in] */ const IRowset __RPC_FAR *pRowsetSource,
    /* [in] */ const ULONG cColIds,
    /* [size_is][in] */ const LONG __RPC_FAR rgSourceColumns[  ],
    /* [size_is][in] */ const LONG __RPC_FAR rgTargetColumns[  ],
    /* [out] */ HSOURCE __RPC_FAR *phSourceID);


void __RPC_STUB IRowsetCopyRows_DefineSource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRowsetCopyRows_INTERFACE_DEFINED__ */


#ifndef __IReadData_INTERFACE_DEFINED__
#define __IReadData_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IReadData
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object][local] */ 



EXTERN_C const IID IID_IReadData;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a6a-2a1c-11ce-ade5-00aa0044773d")
    IReadData : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ReadData( 
            /* [in] */ HCHAPTER hChapter,
            /* [in] */ ULONG cbBookmark,
            /* [size_is][in] */ const BYTE __RPC_FAR *pBookmark,
            /* [in] */ LONG lRowsOffset,
            /* [in] */ HACCESSOR hAccessor,
            /* [in] */ LONG cRows,
            /* [out] */ ULONG __RPC_FAR *pcRowsObtained,
            /* [out][in] */ BYTE __RPC_FAR *__RPC_FAR *ppFixedData,
            /* [out][in] */ ULONG __RPC_FAR *pcbVariableTotal,
            /* [out][in] */ BYTE __RPC_FAR *__RPC_FAR *ppVariableData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReleaseChapter( 
            /* [in] */ HCHAPTER hChapter) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IReadDataVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IReadData __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IReadData __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IReadData __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReadData )( 
            IReadData __RPC_FAR * This,
            /* [in] */ HCHAPTER hChapter,
            /* [in] */ ULONG cbBookmark,
            /* [size_is][in] */ const BYTE __RPC_FAR *pBookmark,
            /* [in] */ LONG lRowsOffset,
            /* [in] */ HACCESSOR hAccessor,
            /* [in] */ LONG cRows,
            /* [out] */ ULONG __RPC_FAR *pcRowsObtained,
            /* [out][in] */ BYTE __RPC_FAR *__RPC_FAR *ppFixedData,
            /* [out][in] */ ULONG __RPC_FAR *pcbVariableTotal,
            /* [out][in] */ BYTE __RPC_FAR *__RPC_FAR *ppVariableData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReleaseChapter )( 
            IReadData __RPC_FAR * This,
            /* [in] */ HCHAPTER hChapter);
        
        END_INTERFACE
    } IReadDataVtbl;

    interface IReadData
    {
        CONST_VTBL struct IReadDataVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IReadData_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IReadData_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IReadData_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IReadData_ReadData(This,hChapter,cbBookmark,pBookmark,lRowsOffset,hAccessor,cRows,pcRowsObtained,ppFixedData,pcbVariableTotal,ppVariableData)	\
    (This)->lpVtbl -> ReadData(This,hChapter,cbBookmark,pBookmark,lRowsOffset,hAccessor,cRows,pcRowsObtained,ppFixedData,pcbVariableTotal,ppVariableData)

#define IReadData_ReleaseChapter(This,hChapter)	\
    (This)->lpVtbl -> ReleaseChapter(This,hChapter)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IReadData_ReadData_Proxy( 
    IReadData __RPC_FAR * This,
    /* [in] */ HCHAPTER hChapter,
    /* [in] */ ULONG cbBookmark,
    /* [size_is][in] */ const BYTE __RPC_FAR *pBookmark,
    /* [in] */ LONG lRowsOffset,
    /* [in] */ HACCESSOR hAccessor,
    /* [in] */ LONG cRows,
    /* [out] */ ULONG __RPC_FAR *pcRowsObtained,
    /* [out][in] */ BYTE __RPC_FAR *__RPC_FAR *ppFixedData,
    /* [out][in] */ ULONG __RPC_FAR *pcbVariableTotal,
    /* [out][in] */ BYTE __RPC_FAR *__RPC_FAR *ppVariableData);


void __RPC_STUB IReadData_ReadData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IReadData_ReleaseChapter_Proxy( 
    IReadData __RPC_FAR * This,
    /* [in] */ HCHAPTER hChapter);


void __RPC_STUB IReadData_ReleaseChapter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IReadData_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_oledb_0103
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


#endif // OLEDBVER >= 0x0250
//@@@- V2.5


extern RPC_IF_HANDLE __MIDL_itf_oledb_0103_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_oledb_0103_v0_0_s_ifspec;

#ifndef __ICommand_INTERFACE_DEFINED__
#define __ICommand_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ICommand
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_ICommand;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a63-2a1c-11ce-ade5-00aa0044773d")
    ICommand : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE Cancel( void) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE Execute( 
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ REFIID riid,
            /* [out][in] */ DBPARAMS __RPC_FAR *pParams,
            /* [out] */ LONG __RPC_FAR *pcRowsAffected,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetDBSession( 
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppSession) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICommandVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICommand __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICommand __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICommand __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Cancel )( 
            ICommand __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Execute )( 
            ICommand __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ REFIID riid,
            /* [out][in] */ DBPARAMS __RPC_FAR *pParams,
            /* [out] */ LONG __RPC_FAR *pcRowsAffected,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDBSession )( 
            ICommand __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppSession);
        
        END_INTERFACE
    } ICommandVtbl;

    interface ICommand
    {
        CONST_VTBL struct ICommandVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICommand_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICommand_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICommand_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICommand_Cancel(This)	\
    (This)->lpVtbl -> Cancel(This)

#define ICommand_Execute(This,pUnkOuter,riid,pParams,pcRowsAffected,ppRowset)	\
    (This)->lpVtbl -> Execute(This,pUnkOuter,riid,pParams,pcRowsAffected,ppRowset)

#define ICommand_GetDBSession(This,riid,ppSession)	\
    (This)->lpVtbl -> GetDBSession(This,riid,ppSession)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE ICommand_RemoteCancel_Proxy( 
    ICommand __RPC_FAR * This,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB ICommand_RemoteCancel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE ICommand_RemoteExecute_Proxy( 
    ICommand __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ REFIID riid,
    /* [in] */ HACCESSOR hAccessor,
    /* [in] */ ULONG cParamSets,
    /* [in] */ ULONG cbData,
    /* [size_is][unique][out][in] */ BYTE __RPC_FAR *pbData,
    /* [unique][out][in] */ LONG __RPC_FAR *pcRowsAffected,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB ICommand_RemoteExecute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE ICommand_RemoteGetDBSession_Proxy( 
    ICommand __RPC_FAR * This,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppSession,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB ICommand_RemoteGetDBSession_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICommand_INTERFACE_DEFINED__ */


#ifndef __IMultipleResults_INTERFACE_DEFINED__
#define __IMultipleResults_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMultipleResults
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IMultipleResults;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a90-2a1c-11ce-ade5-00aa0044773d")
    IMultipleResults : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetResult( 
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ LONG reserved,
            /* [in] */ REFIID riid,
            /* [out] */ LONG __RPC_FAR *pcRowsAffected,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMultipleResultsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMultipleResults __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMultipleResults __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMultipleResults __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetResult )( 
            IMultipleResults __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ LONG reserved,
            /* [in] */ REFIID riid,
            /* [out] */ LONG __RPC_FAR *pcRowsAffected,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset);
        
        END_INTERFACE
    } IMultipleResultsVtbl;

    interface IMultipleResults
    {
        CONST_VTBL struct IMultipleResultsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMultipleResults_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMultipleResults_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMultipleResults_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMultipleResults_GetResult(This,pUnkOuter,reserved,riid,pcRowsAffected,ppRowset)	\
    (This)->lpVtbl -> GetResult(This,pUnkOuter,reserved,riid,pcRowsAffected,ppRowset)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE IMultipleResults_RemoteGetResult_Proxy( 
    IMultipleResults __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ LONG reserved,
    /* [in] */ REFIID riid,
    /* [unique][out][in] */ LONG __RPC_FAR *pcRowsAffected,
    /* [iid_is][unique][out][in] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IMultipleResults_RemoteGetResult_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMultipleResults_INTERFACE_DEFINED__ */


#ifndef __IConvertType_INTERFACE_DEFINED__
#define __IConvertType_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IConvertType
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 


typedef DWORD DBCONVERTFLAGS;


enum DBCONVERTFLAGSENUM
    {	DBCONVERTFLAGS_COLUMN	= 0,
	DBCONVERTFLAGS_PARAMETER	= 0x1
    };
//@@@+ V2.0
#if( OLEDBVER >= 0x0200 )

enum DBCONVERTFLAGSENUM20
    {	DBCONVERTFLAGS_ISLONG	= 0x2,
	DBCONVERTFLAGS_ISFIXEDLENGTH	= 0x4,
	DBCONVERTFLAGS_FROMVARIANT	= 0x8
    };
#endif // OLEDBVER >= 0x0200
//@@@- V2.0

EXTERN_C const IID IID_IConvertType;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a88-2a1c-11ce-ade5-00aa0044773d")
    IConvertType : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE CanConvert( 
            /* [in] */ DBTYPE wFromType,
            /* [in] */ DBTYPE wToType,
            /* [in] */ DBCONVERTFLAGS dwConvertFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IConvertTypeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IConvertType __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IConvertType __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IConvertType __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CanConvert )( 
            IConvertType __RPC_FAR * This,
            /* [in] */ DBTYPE wFromType,
            /* [in] */ DBTYPE wToType,
            /* [in] */ DBCONVERTFLAGS dwConvertFlags);
        
        END_INTERFACE
    } IConvertTypeVtbl;

    interface IConvertType
    {
        CONST_VTBL struct IConvertTypeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IConvertType_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IConvertType_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IConvertType_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IConvertType_CanConvert(This,wFromType,wToType,dwConvertFlags)	\
    (This)->lpVtbl -> CanConvert(This,wFromType,wToType,dwConvertFlags)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE IConvertType_RemoteCanConvert_Proxy( 
    IConvertType __RPC_FAR * This,
    /* [in] */ DBTYPE wFromType,
    /* [in] */ DBTYPE wToType,
    /* [in] */ DBCONVERTFLAGS dwConvertFlags,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IConvertType_RemoteCanConvert_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IConvertType_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_oledb_0106
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


//@@@+ V2.5
#if( OLEDBVER >= 0x0250 )


extern RPC_IF_HANDLE __MIDL_itf_oledb_0106_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_oledb_0106_v0_0_s_ifspec;

#ifndef __ICommandCost_INTERFACE_DEFINED__
#define __ICommandCost_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ICommandCost
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object][local] */ 


typedef DWORD DBRESOURCEKIND;


enum DBRESOURCEKINDENUM
    {	DBRESOURCE_INVALID	= 0,
	DBRESOURCE_TOTAL	= 1,
	DBRESOURCE_CPU	= 2,
	DBRESOURCE_MEMORY	= 3,
	DBRESOURCE_DISK	= 4,
	DBRESOURCE_NETWORK	= 5,
	DBRESOURCE_RESPONSE	= 6,
	DBRESOURCE_ROWS	= 7,
	DBRESOURCE_OTHER	= 8
    };
typedef DWORD DBCOSTUNIT;


enum DBCOSTUNITENUM
    {	DBUNIT_INVALID	= 0,
	DBUNIT_WEIGHT	= 0x1,
	DBUNIT_PERCENT	= 0x2,
	DBUNIT_MAXIMUM	= 0x4,
	DBUNIT_MINIMUM	= 0x8,
	DBUNIT_MICRO_SECOND	= 0x10,
	DBUNIT_MILLI_SECOND	= 0x20,
	DBUNIT_SECOND	= 0x40,
	DBUNIT_MINUTE	= 0x80,
	DBUNIT_HOUR	= 0x100,
	DBUNIT_BYTE	= 0x200,
	DBUNIT_KILO_BYTE	= 0x400,
	DBUNIT_MEGA_BYTE	= 0x800,
	DBUNIT_GIGA_BYTE	= 0x1000,
	DBUNIT_NUM_MSGS	= 0x2000,
	DBUNIT_NUM_LOCKS	= 0x4000,
	DBUNIT_NUM_ROWS	= 0x8000,
	DBUNIT_OTHER	= 0x10000
    };
typedef struct  tagDBCOST
    {
    DBRESOURCEKIND eKind;
    DBCOSTUNIT dwUnits;
    LONG lValue;
    }	DBCOST;

typedef DWORD DBEXECLIMITS;


enum DBEXECLIMITSENUM
    {	DBEXECLIMITS_ABORT	= 1,
	DBEXECLIMITS_STOP	= 2,
	DBEXECLIMITS_SUSPEND	= 3
    };

EXTERN_C const IID IID_ICommandCost;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a4e-2a1c-11ce-ade5-00aa0044773d")
    ICommandCost : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetAccumulatedCost( 
            /* [in] */ LPCOLESTR pwszRowsetName,
            /* [out][in] */ ULONG __RPC_FAR *pcCostLimits,
            /* [size_is][size_is][out] */ DBCOST __RPC_FAR *__RPC_FAR *prgCostLimits) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCostEstimate( 
            /* [in] */ LPCOLESTR pwszRowsetName,
            /* [out] */ ULONG __RPC_FAR *pcCostEstimates,
            /* [out] */ DBCOST __RPC_FAR *prgCostEstimates) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCostGoals( 
            /* [in] */ LPCOLESTR pwszRowsetName,
            /* [out] */ ULONG __RPC_FAR *pcCostGoals,
            /* [out] */ DBCOST __RPC_FAR *prgCostGoals) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCostLimits( 
            /* [in] */ LPCOLESTR pwszRowsetName,
            /* [out] */ ULONG __RPC_FAR *pcCostLimits,
            /* [out] */ DBCOST __RPC_FAR *prgCostLimits) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetCostGoals( 
            /* [in] */ LPCOLESTR pwszRowsetName,
            /* [in] */ ULONG cCostGoals,
            /* [size_is][in] */ const DBCOST __RPC_FAR rgCostGoals[  ]) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetCostLimits( 
            /* [in] */ LPCOLESTR pwszRowsetName,
            /* [in] */ ULONG cCostLimits,
            /* [in] */ DBCOST __RPC_FAR *prgCostLimits,
            /* [in] */ DBEXECLIMITS dwExecutionFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICommandCostVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICommandCost __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICommandCost __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICommandCost __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAccumulatedCost )( 
            ICommandCost __RPC_FAR * This,
            /* [in] */ LPCOLESTR pwszRowsetName,
            /* [out][in] */ ULONG __RPC_FAR *pcCostLimits,
            /* [size_is][size_is][out] */ DBCOST __RPC_FAR *__RPC_FAR *prgCostLimits);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCostEstimate )( 
            ICommandCost __RPC_FAR * This,
            /* [in] */ LPCOLESTR pwszRowsetName,
            /* [out] */ ULONG __RPC_FAR *pcCostEstimates,
            /* [out] */ DBCOST __RPC_FAR *prgCostEstimates);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCostGoals )( 
            ICommandCost __RPC_FAR * This,
            /* [in] */ LPCOLESTR pwszRowsetName,
            /* [out] */ ULONG __RPC_FAR *pcCostGoals,
            /* [out] */ DBCOST __RPC_FAR *prgCostGoals);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCostLimits )( 
            ICommandCost __RPC_FAR * This,
            /* [in] */ LPCOLESTR pwszRowsetName,
            /* [out] */ ULONG __RPC_FAR *pcCostLimits,
            /* [out] */ DBCOST __RPC_FAR *prgCostLimits);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCostGoals )( 
            ICommandCost __RPC_FAR * This,
            /* [in] */ LPCOLESTR pwszRowsetName,
            /* [in] */ ULONG cCostGoals,
            /* [size_is][in] */ const DBCOST __RPC_FAR rgCostGoals[  ]);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCostLimits )( 
            ICommandCost __RPC_FAR * This,
            /* [in] */ LPCOLESTR pwszRowsetName,
            /* [in] */ ULONG cCostLimits,
            /* [in] */ DBCOST __RPC_FAR *prgCostLimits,
            /* [in] */ DBEXECLIMITS dwExecutionFlags);
        
        END_INTERFACE
    } ICommandCostVtbl;

    interface ICommandCost
    {
        CONST_VTBL struct ICommandCostVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICommandCost_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICommandCost_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICommandCost_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICommandCost_GetAccumulatedCost(This,pwszRowsetName,pcCostLimits,prgCostLimits)	\
    (This)->lpVtbl -> GetAccumulatedCost(This,pwszRowsetName,pcCostLimits,prgCostLimits)

#define ICommandCost_GetCostEstimate(This,pwszRowsetName,pcCostEstimates,prgCostEstimates)	\
    (This)->lpVtbl -> GetCostEstimate(This,pwszRowsetName,pcCostEstimates,prgCostEstimates)

#define ICommandCost_GetCostGoals(This,pwszRowsetName,pcCostGoals,prgCostGoals)	\
    (This)->lpVtbl -> GetCostGoals(This,pwszRowsetName,pcCostGoals,prgCostGoals)

#define ICommandCost_GetCostLimits(This,pwszRowsetName,pcCostLimits,prgCostLimits)	\
    (This)->lpVtbl -> GetCostLimits(This,pwszRowsetName,pcCostLimits,prgCostLimits)

#define ICommandCost_SetCostGoals(This,pwszRowsetName,cCostGoals,rgCostGoals)	\
    (This)->lpVtbl -> SetCostGoals(This,pwszRowsetName,cCostGoals,rgCostGoals)

#define ICommandCost_SetCostLimits(This,pwszRowsetName,cCostLimits,prgCostLimits,dwExecutionFlags)	\
    (This)->lpVtbl -> SetCostLimits(This,pwszRowsetName,cCostLimits,prgCostLimits,dwExecutionFlags)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICommandCost_GetAccumulatedCost_Proxy( 
    ICommandCost __RPC_FAR * This,
    /* [in] */ LPCOLESTR pwszRowsetName,
    /* [out][in] */ ULONG __RPC_FAR *pcCostLimits,
    /* [size_is][size_is][out] */ DBCOST __RPC_FAR *__RPC_FAR *prgCostLimits);


void __RPC_STUB ICommandCost_GetAccumulatedCost_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICommandCost_GetCostEstimate_Proxy( 
    ICommandCost __RPC_FAR * This,
    /* [in] */ LPCOLESTR pwszRowsetName,
    /* [out] */ ULONG __RPC_FAR *pcCostEstimates,
    /* [out] */ DBCOST __RPC_FAR *prgCostEstimates);


void __RPC_STUB ICommandCost_GetCostEstimate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICommandCost_GetCostGoals_Proxy( 
    ICommandCost __RPC_FAR * This,
    /* [in] */ LPCOLESTR pwszRowsetName,
    /* [out] */ ULONG __RPC_FAR *pcCostGoals,
    /* [out] */ DBCOST __RPC_FAR *prgCostGoals);


void __RPC_STUB ICommandCost_GetCostGoals_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICommandCost_GetCostLimits_Proxy( 
    ICommandCost __RPC_FAR * This,
    /* [in] */ LPCOLESTR pwszRowsetName,
    /* [out] */ ULONG __RPC_FAR *pcCostLimits,
    /* [out] */ DBCOST __RPC_FAR *prgCostLimits);


void __RPC_STUB ICommandCost_GetCostLimits_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICommandCost_SetCostGoals_Proxy( 
    ICommandCost __RPC_FAR * This,
    /* [in] */ LPCOLESTR pwszRowsetName,
    /* [in] */ ULONG cCostGoals,
    /* [size_is][in] */ const DBCOST __RPC_FAR rgCostGoals[  ]);


void __RPC_STUB ICommandCost_SetCostGoals_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICommandCost_SetCostLimits_Proxy( 
    ICommandCost __RPC_FAR * This,
    /* [in] */ LPCOLESTR pwszRowsetName,
    /* [in] */ ULONG cCostLimits,
    /* [in] */ DBCOST __RPC_FAR *prgCostLimits,
    /* [in] */ DBEXECLIMITS dwExecutionFlags);


void __RPC_STUB ICommandCost_SetCostLimits_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICommandCost_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_oledb_0107
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


#endif // OLEDBVER >= 0x0250
//@@@- V2.5


extern RPC_IF_HANDLE __MIDL_itf_oledb_0107_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_oledb_0107_v0_0_s_ifspec;

#ifndef __ICommandPrepare_INTERFACE_DEFINED__
#define __ICommandPrepare_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ICommandPrepare
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_ICommandPrepare;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a26-2a1c-11ce-ade5-00aa0044773d")
    ICommandPrepare : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE Prepare( 
            /* [in] */ ULONG cExpectedRuns) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE Unprepare( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICommandPrepareVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICommandPrepare __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICommandPrepare __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICommandPrepare __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Prepare )( 
            ICommandPrepare __RPC_FAR * This,
            /* [in] */ ULONG cExpectedRuns);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Unprepare )( 
            ICommandPrepare __RPC_FAR * This);
        
        END_INTERFACE
    } ICommandPrepareVtbl;

    interface ICommandPrepare
    {
        CONST_VTBL struct ICommandPrepareVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICommandPrepare_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICommandPrepare_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICommandPrepare_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICommandPrepare_Prepare(This,cExpectedRuns)	\
    (This)->lpVtbl -> Prepare(This,cExpectedRuns)

#define ICommandPrepare_Unprepare(This)	\
    (This)->lpVtbl -> Unprepare(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE ICommandPrepare_RemotePrepare_Proxy( 
    ICommandPrepare __RPC_FAR * This,
    /* [in] */ ULONG cExpectedRuns,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB ICommandPrepare_RemotePrepare_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE ICommandPrepare_RemoteUnprepare_Proxy( 
    ICommandPrepare __RPC_FAR * This,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB ICommandPrepare_RemoteUnprepare_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICommandPrepare_INTERFACE_DEFINED__ */


#ifndef __ICommandProperties_INTERFACE_DEFINED__
#define __ICommandProperties_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ICommandProperties
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_ICommandProperties;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a79-2a1c-11ce-ade5-00aa0044773d")
    ICommandProperties : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetProperties( 
            /* [in] */ const ULONG cPropertyIDSets,
            /* [size_is][in] */ const DBPROPIDSET __RPC_FAR rgPropertyIDSets[  ],
            /* [out][in] */ ULONG __RPC_FAR *pcPropertySets,
            /* [size_is][size_is][out] */ DBPROPSET __RPC_FAR *__RPC_FAR *prgPropertySets) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE SetProperties( 
            /* [in] */ ULONG cPropertySets,
            /* [size_is][unique][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ]) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICommandPropertiesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICommandProperties __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICommandProperties __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICommandProperties __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetProperties )( 
            ICommandProperties __RPC_FAR * This,
            /* [in] */ const ULONG cPropertyIDSets,
            /* [size_is][in] */ const DBPROPIDSET __RPC_FAR rgPropertyIDSets[  ],
            /* [out][in] */ ULONG __RPC_FAR *pcPropertySets,
            /* [size_is][size_is][out] */ DBPROPSET __RPC_FAR *__RPC_FAR *prgPropertySets);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetProperties )( 
            ICommandProperties __RPC_FAR * This,
            /* [in] */ ULONG cPropertySets,
            /* [size_is][unique][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ]);
        
        END_INTERFACE
    } ICommandPropertiesVtbl;

    interface ICommandProperties
    {
        CONST_VTBL struct ICommandPropertiesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICommandProperties_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICommandProperties_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICommandProperties_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICommandProperties_GetProperties(This,cPropertyIDSets,rgPropertyIDSets,pcPropertySets,prgPropertySets)	\
    (This)->lpVtbl -> GetProperties(This,cPropertyIDSets,rgPropertyIDSets,pcPropertySets,prgPropertySets)

#define ICommandProperties_SetProperties(This,cPropertySets,rgPropertySets)	\
    (This)->lpVtbl -> SetProperties(This,cPropertySets,rgPropertySets)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE ICommandProperties_RemoteGetProperties_Proxy( 
    ICommandProperties __RPC_FAR * This,
    /* [in] */ const ULONG cPropertyIDSets,
    /* [size_is][unique][in] */ const DBPROPIDSET __RPC_FAR *rgPropertyIDSets,
    /* [out][in] */ ULONG __RPC_FAR *pcPropertySets,
    /* [size_is][size_is][out] */ DBPROPSET __RPC_FAR *__RPC_FAR *prgPropertySets,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB ICommandProperties_RemoteGetProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE ICommandProperties_RemoteSetProperties_Proxy( 
    ICommandProperties __RPC_FAR * This,
    /* [in] */ ULONG cPropertySets,
    /* [size_is][unique][in] */ DBPROPSET __RPC_FAR *rgPropertySets,
    /* [in] */ ULONG cTotalProps,
    /* [size_is][out] */ DBPROPSTATUS __RPC_FAR *rgPropStatus,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB ICommandProperties_RemoteSetProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICommandProperties_INTERFACE_DEFINED__ */


#ifndef __ICommandText_INTERFACE_DEFINED__
#define __ICommandText_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ICommandText
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_ICommandText;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a27-2a1c-11ce-ade5-00aa0044773d")
    ICommandText : public ICommand
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetCommandText( 
            /* [out][in] */ GUID __RPC_FAR *pguidDialect,
            /* [out] */ LPOLESTR __RPC_FAR *ppwszCommand) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE SetCommandText( 
            /* [in] */ REFGUID rguidDialect,
            /* [unique][in] */ LPCOLESTR pwszCommand) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICommandTextVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICommandText __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICommandText __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICommandText __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Cancel )( 
            ICommandText __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Execute )( 
            ICommandText __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ REFIID riid,
            /* [out][in] */ DBPARAMS __RPC_FAR *pParams,
            /* [out] */ LONG __RPC_FAR *pcRowsAffected,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDBSession )( 
            ICommandText __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppSession);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCommandText )( 
            ICommandText __RPC_FAR * This,
            /* [out][in] */ GUID __RPC_FAR *pguidDialect,
            /* [out] */ LPOLESTR __RPC_FAR *ppwszCommand);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCommandText )( 
            ICommandText __RPC_FAR * This,
            /* [in] */ REFGUID rguidDialect,
            /* [unique][in] */ LPCOLESTR pwszCommand);
        
        END_INTERFACE
    } ICommandTextVtbl;

    interface ICommandText
    {
        CONST_VTBL struct ICommandTextVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICommandText_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICommandText_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICommandText_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICommandText_Cancel(This)	\
    (This)->lpVtbl -> Cancel(This)

#define ICommandText_Execute(This,pUnkOuter,riid,pParams,pcRowsAffected,ppRowset)	\
    (This)->lpVtbl -> Execute(This,pUnkOuter,riid,pParams,pcRowsAffected,ppRowset)

#define ICommandText_GetDBSession(This,riid,ppSession)	\
    (This)->lpVtbl -> GetDBSession(This,riid,ppSession)


#define ICommandText_GetCommandText(This,pguidDialect,ppwszCommand)	\
    (This)->lpVtbl -> GetCommandText(This,pguidDialect,ppwszCommand)

#define ICommandText_SetCommandText(This,rguidDialect,pwszCommand)	\
    (This)->lpVtbl -> SetCommandText(This,rguidDialect,pwszCommand)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE ICommandText_RemoteGetCommandText_Proxy( 
    ICommandText __RPC_FAR * This,
    /* [unique][out][in] */ GUID __RPC_FAR *pguidDialect,
    /* [out] */ LPOLESTR __RPC_FAR *ppwszCommand,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB ICommandText_RemoteGetCommandText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE ICommandText_RemoteSetCommandText_Proxy( 
    ICommandText __RPC_FAR * This,
    /* [in] */ REFGUID rguidDialect,
    /* [unique][in] */ LPCOLESTR pwszCommand,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB ICommandText_RemoteSetCommandText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICommandText_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_oledb_0110
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


//@@@+ V2.5
#if( OLEDBVER >= 0x0250 )


extern RPC_IF_HANDLE __MIDL_itf_oledb_0110_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_oledb_0110_v0_0_s_ifspec;

#ifndef __ICommandTree_INTERFACE_DEFINED__
#define __ICommandTree_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ICommandTree
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object][local] */ 


typedef DWORD DBCOMMANDREUSE;


enum DBCOMMANDREUSEENUM
    {	DBCOMMANDREUSE_NONE	= 0,
	DBCOMMANDREUSE_PROPERTIES	= 0x1,
	DBCOMMANDREUSE_PARAMETERS	= 0x2
    };
typedef DWORD DBVALUEKIND;


enum DBVALUEKINDENUM
    {	DBVALUEKIND_BYGUID	= 256,
	DBVALUEKIND_COLDESC	= DBVALUEKIND_BYGUID + 1,
	DBVALUEKIND_ID	= DBVALUEKIND_COLDESC + 1,
	DBVALUEKIND_CONTENT	= DBVALUEKIND_ID + 1,
	DBVALUEKIND_CONTENTVECTOR	= DBVALUEKIND_CONTENT + 1,
	DBVALUEKIND_GROUPINFO	= DBVALUEKIND_CONTENTVECTOR + 1,
	DBVALUEKIND_PARAMETER	= DBVALUEKIND_GROUPINFO + 1,
	DBVALUEKIND_PROPERTY	= DBVALUEKIND_PARAMETER + 1,
	DBVALUEKIND_SETFUNC	= DBVALUEKIND_PROPERTY + 1,
	DBVALUEKIND_SORTINFO	= DBVALUEKIND_SETFUNC + 1,
	DBVALUEKIND_TEXT	= DBVALUEKIND_SORTINFO + 1,
	DBVALUEKIND_COMMAND	= DBVALUEKIND_TEXT + 1,
	DBVALUEKIND_MONIKER	= DBVALUEKIND_COMMAND + 1,
	DBVALUEKIND_ROWSET	= DBVALUEKIND_MONIKER + 1,
	DBVALUEKIND_LIKE	= DBVALUEKIND_ROWSET + 1,
	DBVALUEKIND_CONTENTPROXIMITY	= DBVALUEKIND_LIKE + 1,
	DBVALUEKIND_IDISPATCH	= 9,
	DBVALUEKIND_IUNKNOWN	= 13,
	DBVALUEKIND_EMPTY	= 0,
	DBVALUEKIND_NULL	= 1,
	DBVALUEKIND_I2	= 2,
	DBVALUEKIND_I4	= 3,
	DBVALUEKIND_R4	= 4,
	DBVALUEKIND_R8	= 5,
	DBVALUEKIND_CY	= 6,
	DBVALUEKIND_DATE	= 7,
	DBVALUEKIND_BSTR	= 8,
	DBVALUEKIND_ERROR	= 10,
	DBVALUEKIND_BOOL	= 11,
	DBVALUEKIND_VARIANT	= 12,
	DBVALUEKIND_VECTOR	= 0x1000,
	DBVALUEKIND_ARRAY	= 0x2000,
	DBVALUEKIND_BYREF	= 0x4000,
	DBVALUEKIND_I1	= 16,
	DBVALUEKIND_UI1	= 17,
	DBVALUEKIND_UI2	= 18,
	DBVALUEKIND_UI4	= DBVALUEKIND_UI2 + 1,
	DBVALUEKIND_I8	= DBVALUEKIND_UI4 + 1,
	DBVALUEKIND_UI8	= DBVALUEKIND_I8 + 1,
	DBVALUEKIND_GUID	= 72,
	DBVALUEKIND_BYTES	= 128,
	DBVALUEKIND_STR	= 129,
	DBVALUEKIND_WSTR	= 130,
	DBVALUEKIND_NUMERIC	= 131,
	DBVALUEKIND_DBDATE	= 133,
	DBVALUEKIND_DBTIME	= 134,
	DBVALUEKIND_DBTIMESTAMP	= 135
    };
typedef struct  tagDBBYGUID
    {
    /* [size_is] */ BYTE __RPC_FAR *pbInfo;
    ULONG cbInfo;
    GUID guid;
    }	DBBYGUID;

#define GENERATE_METHOD_EXACT	( 0 )
#define GENERATE_METHOD_PREFIX	( 1 )
#define GENERATE_METHOD_INFLECT	( 2 )
typedef struct  tagDBCONTENT
    {
    LPOLESTR pwszPhrase;
    DWORD dwGenerateMethod;
    LONG lWeight;
    LCID lcid;
    }	DBCONTENT;

#define PROPID_QUERY_RANKVECTOR	( 0x2 )
#define PROPID_QUERY_RANK		( 0x3 )
#define PROPID_QUERY_HITCOUNT	( 0x4 )
#define PROPID_QUERY_ALL			( 0x6 )
#define PROPID_STG_CONTENTS		( 0x13 )
#define VECTOR_RANK_MIN		( 0 )
#define VECTOR_RANK_MAX		( 1 )
#define VECTOR_RANK_INNER	( 2 )
#define VECTOR_RANK_DICE		( 3 )
#define VECTOR_RANK_JACCARD	( 4 )
typedef struct  tagDBCONTENTVECTOR
    {
    LONG lWeight;
    DWORD dwRankingMethod;
    }	DBCONTENTVECTOR;

typedef struct  tagDBGROUPINFO
    {
    LCID lcid;
    }	DBGROUPINFO;

typedef struct  tagDBPARAMETER
    {
    LPOLESTR pwszName;
    ITypeInfo __RPC_FAR *pTypeInfo;
    DB_NUMERIC __RPC_FAR *pNum;
    ULONG cbMaxLength;
    DBPARAMFLAGS dwFlags;
    DBTYPE wType;
    }	DBPARAMETER;

#define DBSETFUNC_NONE		0x0
#define DBSETFUNC_ALL		0x1
#define DBSETFUNC_DISTINCT	0x2
typedef struct  tagDBSETFUNC
    {
    DWORD dwSetQuantifier;
    }	DBSETFUNC;

typedef struct  tagDBSORTINFO
    {
    BOOL fDesc;
    LCID lcid;
    }	DBSORTINFO;

typedef struct  tagDBTEXT
    {
    LPOLESTR pwszText;
    ULONG ulErrorLocator;
    ULONG ulTokenLength;
    GUID guidDialect;
    }	DBTEXT;

typedef struct  tagDBLIKE
    {
    LONG lWeight;
    GUID guidDialect;
    }	DBLIKE;

#define PROXIMITY_UNIT_WORD           ( 0 )
#define PROXIMITY_UNIT_SENTENCE       ( 1 )
#define PROXIMITY_UNIT_PARAGRAPH      ( 2 )
#define PROXIMITY_UNIT_CHAPTER        ( 3 )
typedef struct  tagDBCONTENTPROXIMITY
    {
    DWORD dwProximityUnit;
    ULONG ulProximityDistance;
    LONG lWeight;
    }	DBCONTENTPROXIMITY;

typedef struct  tagDBCOMMANDTREE
    {
    DBCOMMANDOP op;
    WORD wKind;
    struct tagDBCOMMANDTREE __RPC_FAR *pctFirstChild;
    struct tagDBCOMMANDTREE __RPC_FAR *pctNextSibling;
    /* [switch_is][switch_type] */ union 
        {
        /* [case()] */ BOOL fValue;
        /* [case()] */ unsigned char uchValue;
        /* [case()] */ signed char schValue;
        /* [case()] */ unsigned short usValue;
        /* [case()] */ short sValue;
        /* [case()] */ LPOLESTR pwszValue;
        /* [case()] */ LONG lValue;
        /* [case()] */ ULONG ulValue;
        /* [case()] */ float flValue;
        /* [case()] */ double dblValue;
        /* [case()] */ CY cyValue;
        /* [case()] */ DATE dateValue;
        /* [case()] */ DBDATE dbdateValue;
        /* [case()] */ DBTIME dbtimeValue;
        /* [case()] */ SCODE scodeValue;
        /* [case()] */ hyper llValue;
        /* [case()] */ MIDL_uhyper ullValue;
        /* [case()] */ BSTR __RPC_FAR *pbstrValue;
        /* [case()] */ ICommand __RPC_FAR *pCommand;
        /* [case()] */ IDispatch __RPC_FAR *pDispatch;
        /* [case()] */ IMoniker __RPC_FAR *pMoniker;
        /* [case()] */ IRowset __RPC_FAR *pRowset;
        /* [case()] */ IUnknown __RPC_FAR *pUnknown;
        /* [case()] */ DBBYGUID __RPC_FAR *pdbbygdValue;
        /* [case()] */ DBCOLUMNDESC __RPC_FAR *pcoldescValue;
        /* [case()] */ DBID __RPC_FAR *pdbidValue;
        /* [case()] */ DBLIKE __RPC_FAR *pdblikeValue;
        /* [case()] */ DBCONTENT __RPC_FAR *pdbcntntValue;
        /* [case()] */ DBCONTENTVECTOR __RPC_FAR *pdbcntntvcValue;
        /* [case()] */ DBCONTENTPROXIMITY __RPC_FAR *pdbcntntproxValue;
        /* [case()] */ DBGROUPINFO __RPC_FAR *pdbgrpinfValue;
        /* [case()] */ DBPARAMETER __RPC_FAR *pdbparamValue;
        /* [case()] */ DBPROPSET __RPC_FAR *pdbpropValue;
        /* [case()] */ DBSETFUNC __RPC_FAR *pdbstfncValue;
        /* [case()] */ DBSORTINFO __RPC_FAR *pdbsrtinfValue;
        /* [case()] */ DBTEXT __RPC_FAR *pdbtxtValue;
        /* [case()] */ DBVECTOR __RPC_FAR *pdbvectorValue;
        /* [case()] */ SAFEARRAY __RPC_FAR *parrayValue;
        /* [case()] */ VARIANT __RPC_FAR *pvarValue;
        /* [case()] */ GUID __RPC_FAR *pGuid;
        /* [case()] */ BYTE __RPC_FAR *pbValue;
        /* [case()] */ char __RPC_FAR *pzValue;
        /* [case()] */ DB_NUMERIC __RPC_FAR *pdbnValue;
        /* [case()] */ DBTIMESTAMP __RPC_FAR *pdbtsValue;
        /* [case()] */ void __RPC_FAR *pvValue;
        }	value;
    HRESULT hrError;
    }	DBCOMMANDTREE;


EXTERN_C const IID IID_ICommandTree;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a87-2a1c-11ce-ade5-00aa0044773d")
    ICommandTree : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE FindErrorNodes( 
            /* [in] */ const DBCOMMANDTREE __RPC_FAR *pRoot,
            /* [out] */ ULONG __RPC_FAR *pcErrorNodes,
            /* [out] */ DBCOMMANDTREE __RPC_FAR *__RPC_FAR *__RPC_FAR *prgErrorNodes) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FreeCommandTree( 
            /* [in] */ DBCOMMANDTREE __RPC_FAR *__RPC_FAR *ppRoot) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCommandTree( 
            /* [out] */ DBCOMMANDTREE __RPC_FAR *__RPC_FAR *ppRoot) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetCommandTree( 
            /* [in] */ DBCOMMANDTREE __RPC_FAR *__RPC_FAR *ppRoot,
            /* [in] */ DBCOMMANDREUSE dwCommandReuse,
            /* [in] */ BOOL fCopy) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICommandTreeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICommandTree __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICommandTree __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICommandTree __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindErrorNodes )( 
            ICommandTree __RPC_FAR * This,
            /* [in] */ const DBCOMMANDTREE __RPC_FAR *pRoot,
            /* [out] */ ULONG __RPC_FAR *pcErrorNodes,
            /* [out] */ DBCOMMANDTREE __RPC_FAR *__RPC_FAR *__RPC_FAR *prgErrorNodes);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FreeCommandTree )( 
            ICommandTree __RPC_FAR * This,
            /* [in] */ DBCOMMANDTREE __RPC_FAR *__RPC_FAR *ppRoot);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCommandTree )( 
            ICommandTree __RPC_FAR * This,
            /* [out] */ DBCOMMANDTREE __RPC_FAR *__RPC_FAR *ppRoot);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCommandTree )( 
            ICommandTree __RPC_FAR * This,
            /* [in] */ DBCOMMANDTREE __RPC_FAR *__RPC_FAR *ppRoot,
            /* [in] */ DBCOMMANDREUSE dwCommandReuse,
            /* [in] */ BOOL fCopy);
        
        END_INTERFACE
    } ICommandTreeVtbl;

    interface ICommandTree
    {
        CONST_VTBL struct ICommandTreeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICommandTree_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICommandTree_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICommandTree_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICommandTree_FindErrorNodes(This,pRoot,pcErrorNodes,prgErrorNodes)	\
    (This)->lpVtbl -> FindErrorNodes(This,pRoot,pcErrorNodes,prgErrorNodes)

#define ICommandTree_FreeCommandTree(This,ppRoot)	\
    (This)->lpVtbl -> FreeCommandTree(This,ppRoot)

#define ICommandTree_GetCommandTree(This,ppRoot)	\
    (This)->lpVtbl -> GetCommandTree(This,ppRoot)

#define ICommandTree_SetCommandTree(This,ppRoot,dwCommandReuse,fCopy)	\
    (This)->lpVtbl -> SetCommandTree(This,ppRoot,dwCommandReuse,fCopy)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICommandTree_FindErrorNodes_Proxy( 
    ICommandTree __RPC_FAR * This,
    /* [in] */ const DBCOMMANDTREE __RPC_FAR *pRoot,
    /* [out] */ ULONG __RPC_FAR *pcErrorNodes,
    /* [out] */ DBCOMMANDTREE __RPC_FAR *__RPC_FAR *__RPC_FAR *prgErrorNodes);


void __RPC_STUB ICommandTree_FindErrorNodes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICommandTree_FreeCommandTree_Proxy( 
    ICommandTree __RPC_FAR * This,
    /* [in] */ DBCOMMANDTREE __RPC_FAR *__RPC_FAR *ppRoot);


void __RPC_STUB ICommandTree_FreeCommandTree_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICommandTree_GetCommandTree_Proxy( 
    ICommandTree __RPC_FAR * This,
    /* [out] */ DBCOMMANDTREE __RPC_FAR *__RPC_FAR *ppRoot);


void __RPC_STUB ICommandTree_GetCommandTree_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICommandTree_SetCommandTree_Proxy( 
    ICommandTree __RPC_FAR * This,
    /* [in] */ DBCOMMANDTREE __RPC_FAR *__RPC_FAR *ppRoot,
    /* [in] */ DBCOMMANDREUSE dwCommandReuse,
    /* [in] */ BOOL fCopy);


void __RPC_STUB ICommandTree_SetCommandTree_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICommandTree_INTERFACE_DEFINED__ */


#ifndef __ICommandValidate_INTERFACE_DEFINED__
#define __ICommandValidate_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ICommandValidate
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object][local] */ 



EXTERN_C const IID IID_ICommandValidate;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a18-2a1c-11ce-ade5-00aa0044773d")
    ICommandValidate : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ValidateCompletely( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ValidateSyntax( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICommandValidateVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICommandValidate __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICommandValidate __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICommandValidate __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ValidateCompletely )( 
            ICommandValidate __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ValidateSyntax )( 
            ICommandValidate __RPC_FAR * This);
        
        END_INTERFACE
    } ICommandValidateVtbl;

    interface ICommandValidate
    {
        CONST_VTBL struct ICommandValidateVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICommandValidate_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICommandValidate_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICommandValidate_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICommandValidate_ValidateCompletely(This)	\
    (This)->lpVtbl -> ValidateCompletely(This)

#define ICommandValidate_ValidateSyntax(This)	\
    (This)->lpVtbl -> ValidateSyntax(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICommandValidate_ValidateCompletely_Proxy( 
    ICommandValidate __RPC_FAR * This);


void __RPC_STUB ICommandValidate_ValidateCompletely_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICommandValidate_ValidateSyntax_Proxy( 
    ICommandValidate __RPC_FAR * This);


void __RPC_STUB ICommandValidate_ValidateSyntax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICommandValidate_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_oledb_0112
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


#endif // OLEDBVER >= 0x0250
//@@@- V2.5


extern RPC_IF_HANDLE __MIDL_itf_oledb_0112_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_oledb_0112_v0_0_s_ifspec;

#ifndef __ICommandWithParameters_INTERFACE_DEFINED__
#define __ICommandWithParameters_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ICommandWithParameters
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 


typedef struct  tagDBPARAMBINDINFO
    {
    LPOLESTR pwszDataSourceType;
    LPOLESTR pwszName;
    ULONG ulParamSize;
    DBPARAMFLAGS dwFlags;
    BYTE bPrecision;
    BYTE bScale;
    }	DBPARAMBINDINFO;


EXTERN_C const IID IID_ICommandWithParameters;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a64-2a1c-11ce-ade5-00aa0044773d")
    ICommandWithParameters : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetParameterInfo( 
            /* [out][in] */ ULONG __RPC_FAR *pcParams,
            /* [size_is][size_is][out] */ DBPARAMINFO __RPC_FAR *__RPC_FAR *prgParamInfo,
            /* [out] */ OLECHAR __RPC_FAR *__RPC_FAR *ppNamesBuffer) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE MapParameterNames( 
            /* [in] */ ULONG cParamNames,
            /* [size_is][in] */ const OLECHAR __RPC_FAR *__RPC_FAR rgParamNames[  ],
            /* [size_is][out] */ LONG __RPC_FAR rgParamOrdinals[  ]) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE SetParameterInfo( 
            /* [in] */ ULONG cParams,
            /* [size_is][unique][in] */ const ULONG __RPC_FAR rgParamOrdinals[  ],
            /* [size_is][unique][in] */ const DBPARAMBINDINFO __RPC_FAR rgParamBindInfo[  ]) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICommandWithParametersVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICommandWithParameters __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICommandWithParameters __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICommandWithParameters __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetParameterInfo )( 
            ICommandWithParameters __RPC_FAR * This,
            /* [out][in] */ ULONG __RPC_FAR *pcParams,
            /* [size_is][size_is][out] */ DBPARAMINFO __RPC_FAR *__RPC_FAR *prgParamInfo,
            /* [out] */ OLECHAR __RPC_FAR *__RPC_FAR *ppNamesBuffer);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MapParameterNames )( 
            ICommandWithParameters __RPC_FAR * This,
            /* [in] */ ULONG cParamNames,
            /* [size_is][in] */ const OLECHAR __RPC_FAR *__RPC_FAR rgParamNames[  ],
            /* [size_is][out] */ LONG __RPC_FAR rgParamOrdinals[  ]);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetParameterInfo )( 
            ICommandWithParameters __RPC_FAR * This,
            /* [in] */ ULONG cParams,
            /* [size_is][unique][in] */ const ULONG __RPC_FAR rgParamOrdinals[  ],
            /* [size_is][unique][in] */ const DBPARAMBINDINFO __RPC_FAR rgParamBindInfo[  ]);
        
        END_INTERFACE
    } ICommandWithParametersVtbl;

    interface ICommandWithParameters
    {
        CONST_VTBL struct ICommandWithParametersVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICommandWithParameters_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICommandWithParameters_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICommandWithParameters_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICommandWithParameters_GetParameterInfo(This,pcParams,prgParamInfo,ppNamesBuffer)	\
    (This)->lpVtbl -> GetParameterInfo(This,pcParams,prgParamInfo,ppNamesBuffer)

#define ICommandWithParameters_MapParameterNames(This,cParamNames,rgParamNames,rgParamOrdinals)	\
    (This)->lpVtbl -> MapParameterNames(This,cParamNames,rgParamNames,rgParamOrdinals)

#define ICommandWithParameters_SetParameterInfo(This,cParams,rgParamOrdinals,rgParamBindInfo)	\
    (This)->lpVtbl -> SetParameterInfo(This,cParams,rgParamOrdinals,rgParamBindInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE ICommandWithParameters_RemoteGetParameterInfo_Proxy( 
    ICommandWithParameters __RPC_FAR * This,
    /* [out][in] */ ULONG __RPC_FAR *pcParams,
    /* [size_is][size_is][out] */ DBPARAMINFO __RPC_FAR *__RPC_FAR *prgParamInfo,
    /* [size_is][size_is][out] */ ULONG __RPC_FAR *__RPC_FAR *prgNameOffsets,
    /* [out][in] */ ULONG __RPC_FAR *pcbNamesBuffer,
    /* [size_is][size_is][unique][out][in] */ OLECHAR __RPC_FAR *__RPC_FAR *ppNamesBuffer,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB ICommandWithParameters_RemoteGetParameterInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE ICommandWithParameters_RemoteMapParameterNames_Proxy( 
    ICommandWithParameters __RPC_FAR * This,
    /* [in] */ ULONG cParamNames,
    /* [size_is][in] */ LPCOLESTR __RPC_FAR *rgParamNames,
    /* [size_is][out] */ LONG __RPC_FAR *rgParamOrdinals,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB ICommandWithParameters_RemoteMapParameterNames_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE ICommandWithParameters_RemoteSetParameterInfo_Proxy( 
    ICommandWithParameters __RPC_FAR * This,
    /* [in] */ ULONG cParams,
    /* [size_is][unique][in] */ const ULONG __RPC_FAR *rgParamOrdinals,
    /* [size_is][unique][in] */ const DBPARAMBINDINFO __RPC_FAR *rgParamBindInfo,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB ICommandWithParameters_RemoteSetParameterInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICommandWithParameters_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_oledb_0113
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


//@@@+ V2.5
#if( OLEDBVER >= 0x0250 )


extern RPC_IF_HANDLE __MIDL_itf_oledb_0113_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_oledb_0113_v0_0_s_ifspec;

#ifndef __IQuery_INTERFACE_DEFINED__
#define __IQuery_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IQuery
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object][local] */ 



EXTERN_C const IID IID_IQuery;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a51-2a1c-11ce-ade5-00aa0044773d")
    IQuery : public ICommandTree
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE AddPostProcessing( 
            /* [in] */ DBCOMMANDTREE __RPC_FAR *__RPC_FAR *ppRoot,
            /* [in] */ BOOL fCopy) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCardinalityEstimate( 
            /* [out] */ ULONG __RPC_FAR *pulCardinality) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IQueryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IQuery __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IQuery __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IQuery __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindErrorNodes )( 
            IQuery __RPC_FAR * This,
            /* [in] */ const DBCOMMANDTREE __RPC_FAR *pRoot,
            /* [out] */ ULONG __RPC_FAR *pcErrorNodes,
            /* [out] */ DBCOMMANDTREE __RPC_FAR *__RPC_FAR *__RPC_FAR *prgErrorNodes);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FreeCommandTree )( 
            IQuery __RPC_FAR * This,
            /* [in] */ DBCOMMANDTREE __RPC_FAR *__RPC_FAR *ppRoot);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCommandTree )( 
            IQuery __RPC_FAR * This,
            /* [out] */ DBCOMMANDTREE __RPC_FAR *__RPC_FAR *ppRoot);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCommandTree )( 
            IQuery __RPC_FAR * This,
            /* [in] */ DBCOMMANDTREE __RPC_FAR *__RPC_FAR *ppRoot,
            /* [in] */ DBCOMMANDREUSE dwCommandReuse,
            /* [in] */ BOOL fCopy);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddPostProcessing )( 
            IQuery __RPC_FAR * This,
            /* [in] */ DBCOMMANDTREE __RPC_FAR *__RPC_FAR *ppRoot,
            /* [in] */ BOOL fCopy);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCardinalityEstimate )( 
            IQuery __RPC_FAR * This,
            /* [out] */ ULONG __RPC_FAR *pulCardinality);
        
        END_INTERFACE
    } IQueryVtbl;

    interface IQuery
    {
        CONST_VTBL struct IQueryVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IQuery_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IQuery_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IQuery_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IQuery_FindErrorNodes(This,pRoot,pcErrorNodes,prgErrorNodes)	\
    (This)->lpVtbl -> FindErrorNodes(This,pRoot,pcErrorNodes,prgErrorNodes)

#define IQuery_FreeCommandTree(This,ppRoot)	\
    (This)->lpVtbl -> FreeCommandTree(This,ppRoot)

#define IQuery_GetCommandTree(This,ppRoot)	\
    (This)->lpVtbl -> GetCommandTree(This,ppRoot)

#define IQuery_SetCommandTree(This,ppRoot,dwCommandReuse,fCopy)	\
    (This)->lpVtbl -> SetCommandTree(This,ppRoot,dwCommandReuse,fCopy)


#define IQuery_AddPostProcessing(This,ppRoot,fCopy)	\
    (This)->lpVtbl -> AddPostProcessing(This,ppRoot,fCopy)

#define IQuery_GetCardinalityEstimate(This,pulCardinality)	\
    (This)->lpVtbl -> GetCardinalityEstimate(This,pulCardinality)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IQuery_AddPostProcessing_Proxy( 
    IQuery __RPC_FAR * This,
    /* [in] */ DBCOMMANDTREE __RPC_FAR *__RPC_FAR *ppRoot,
    /* [in] */ BOOL fCopy);


void __RPC_STUB IQuery_AddPostProcessing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IQuery_GetCardinalityEstimate_Proxy( 
    IQuery __RPC_FAR * This,
    /* [out] */ ULONG __RPC_FAR *pulCardinality);


void __RPC_STUB IQuery_GetCardinalityEstimate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IQuery_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_oledb_0114
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


#endif // OLEDBVER >= 0x0250
//@@@- V2.5


extern RPC_IF_HANDLE __MIDL_itf_oledb_0114_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_oledb_0114_v0_0_s_ifspec;

#ifndef __IColumnsRowset_INTERFACE_DEFINED__
#define __IColumnsRowset_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IColumnsRowset
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IColumnsRowset;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a10-2a1c-11ce-ade5-00aa0044773d")
    IColumnsRowset : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetAvailableColumns( 
            /* [out][in] */ ULONG __RPC_FAR *pcOptColumns,
            /* [size_is][size_is][out] */ DBID __RPC_FAR *__RPC_FAR *prgOptColumns) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetColumnsRowset( 
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ ULONG cOptColumns,
            /* [size_is][in] */ const DBID __RPC_FAR rgOptColumns[  ],
            /* [in] */ REFIID riid,
            /* [in] */ ULONG cPropertySets,
            /* [size_is][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ],
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppColRowset) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IColumnsRowsetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IColumnsRowset __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IColumnsRowset __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IColumnsRowset __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAvailableColumns )( 
            IColumnsRowset __RPC_FAR * This,
            /* [out][in] */ ULONG __RPC_FAR *pcOptColumns,
            /* [size_is][size_is][out] */ DBID __RPC_FAR *__RPC_FAR *prgOptColumns);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetColumnsRowset )( 
            IColumnsRowset __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ ULONG cOptColumns,
            /* [size_is][in] */ const DBID __RPC_FAR rgOptColumns[  ],
            /* [in] */ REFIID riid,
            /* [in] */ ULONG cPropertySets,
            /* [size_is][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ],
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppColRowset);
        
        END_INTERFACE
    } IColumnsRowsetVtbl;

    interface IColumnsRowset
    {
        CONST_VTBL struct IColumnsRowsetVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IColumnsRowset_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IColumnsRowset_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IColumnsRowset_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IColumnsRowset_GetAvailableColumns(This,pcOptColumns,prgOptColumns)	\
    (This)->lpVtbl -> GetAvailableColumns(This,pcOptColumns,prgOptColumns)

#define IColumnsRowset_GetColumnsRowset(This,pUnkOuter,cOptColumns,rgOptColumns,riid,cPropertySets,rgPropertySets,ppColRowset)	\
    (This)->lpVtbl -> GetColumnsRowset(This,pUnkOuter,cOptColumns,rgOptColumns,riid,cPropertySets,rgPropertySets,ppColRowset)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE IColumnsRowset_RemoteGetAvailableColumns_Proxy( 
    IColumnsRowset __RPC_FAR * This,
    /* [out][in] */ ULONG __RPC_FAR *pcOptColumns,
    /* [size_is][size_is][out] */ DBID __RPC_FAR *__RPC_FAR *prgOptColumns,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IColumnsRowset_RemoteGetAvailableColumns_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IColumnsRowset_RemoteGetColumnsRowset_Proxy( 
    IColumnsRowset __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ ULONG cOptColumns,
    /* [size_is][unique][in] */ const DBID __RPC_FAR *rgOptColumns,
    /* [in] */ REFIID riid,
    /* [in] */ ULONG cPropertySets,
    /* [size_is][unique][in] */ DBPROPSET __RPC_FAR *rgPropertySets,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppColRowset,
    /* [in] */ ULONG cTotalProps,
    /* [size_is][out] */ DBPROPSTATUS __RPC_FAR *rgPropStatus,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IColumnsRowset_RemoteGetColumnsRowset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IColumnsRowset_INTERFACE_DEFINED__ */


#ifndef __IColumnsInfo_INTERFACE_DEFINED__
#define __IColumnsInfo_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IColumnsInfo
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IColumnsInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a11-2a1c-11ce-ade5-00aa0044773d")
    IColumnsInfo : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetColumnInfo( 
            /* [out][in] */ ULONG __RPC_FAR *pcColumns,
            /* [size_is][size_is][out] */ DBCOLUMNINFO __RPC_FAR *__RPC_FAR *prgInfo,
            /* [out] */ OLECHAR __RPC_FAR *__RPC_FAR *ppStringsBuffer) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE MapColumnIDs( 
            /* [in] */ ULONG cColumnIDs,
            /* [size_is][in] */ const DBID __RPC_FAR rgColumnIDs[  ],
            /* [size_is][out] */ ULONG __RPC_FAR rgColumns[  ]) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IColumnsInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IColumnsInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IColumnsInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IColumnsInfo __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetColumnInfo )( 
            IColumnsInfo __RPC_FAR * This,
            /* [out][in] */ ULONG __RPC_FAR *pcColumns,
            /* [size_is][size_is][out] */ DBCOLUMNINFO __RPC_FAR *__RPC_FAR *prgInfo,
            /* [out] */ OLECHAR __RPC_FAR *__RPC_FAR *ppStringsBuffer);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MapColumnIDs )( 
            IColumnsInfo __RPC_FAR * This,
            /* [in] */ ULONG cColumnIDs,
            /* [size_is][in] */ const DBID __RPC_FAR rgColumnIDs[  ],
            /* [size_is][out] */ ULONG __RPC_FAR rgColumns[  ]);
        
        END_INTERFACE
    } IColumnsInfoVtbl;

    interface IColumnsInfo
    {
        CONST_VTBL struct IColumnsInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IColumnsInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IColumnsInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IColumnsInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IColumnsInfo_GetColumnInfo(This,pcColumns,prgInfo,ppStringsBuffer)	\
    (This)->lpVtbl -> GetColumnInfo(This,pcColumns,prgInfo,ppStringsBuffer)

#define IColumnsInfo_MapColumnIDs(This,cColumnIDs,rgColumnIDs,rgColumns)	\
    (This)->lpVtbl -> MapColumnIDs(This,cColumnIDs,rgColumnIDs,rgColumns)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE IColumnsInfo_RemoteGetColumnInfo_Proxy( 
    IColumnsInfo __RPC_FAR * This,
    /* [out][in] */ ULONG __RPC_FAR *pcColumns,
    /* [size_is][size_is][out] */ DBCOLUMNINFO __RPC_FAR *__RPC_FAR *prgInfo,
    /* [size_is][size_is][out] */ ULONG __RPC_FAR *__RPC_FAR *prgNameOffsets,
    /* [size_is][size_is][out] */ ULONG __RPC_FAR *__RPC_FAR *prgcolumnidOffsets,
    /* [out][in] */ ULONG __RPC_FAR *pcbStringsBuffer,
    /* [size_is][size_is][unique][out][in] */ OLECHAR __RPC_FAR *__RPC_FAR *ppStringsBuffer,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IColumnsInfo_RemoteGetColumnInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IColumnsInfo_RemoteMapColumnIDs_Proxy( 
    IColumnsInfo __RPC_FAR * This,
    /* [in] */ ULONG cColumnIDs,
    /* [size_is][in] */ const DBID __RPC_FAR *rgColumnIDs,
    /* [size_is][out] */ ULONG __RPC_FAR *rgColumns,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IColumnsInfo_RemoteMapColumnIDs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IColumnsInfo_INTERFACE_DEFINED__ */


#ifndef __IDBCreateCommand_INTERFACE_DEFINED__
#define __IDBCreateCommand_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDBCreateCommand
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IDBCreateCommand;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a1d-2a1c-11ce-ade5-00aa0044773d")
    IDBCreateCommand : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE CreateCommand( 
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppCommand) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDBCreateCommandVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDBCreateCommand __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDBCreateCommand __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDBCreateCommand __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateCommand )( 
            IDBCreateCommand __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppCommand);
        
        END_INTERFACE
    } IDBCreateCommandVtbl;

    interface IDBCreateCommand
    {
        CONST_VTBL struct IDBCreateCommandVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDBCreateCommand_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDBCreateCommand_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDBCreateCommand_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDBCreateCommand_CreateCommand(This,pUnkOuter,riid,ppCommand)	\
    (This)->lpVtbl -> CreateCommand(This,pUnkOuter,riid,ppCommand)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBCreateCommand_RemoteCreateCommand_Proxy( 
    IDBCreateCommand __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppCommand,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IDBCreateCommand_RemoteCreateCommand_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDBCreateCommand_INTERFACE_DEFINED__ */


#ifndef __IDBCreateSession_INTERFACE_DEFINED__
#define __IDBCreateSession_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDBCreateSession
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IDBCreateSession;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a5d-2a1c-11ce-ade5-00aa0044773d")
    IDBCreateSession : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE CreateSession( 
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppDBSession) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDBCreateSessionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDBCreateSession __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDBCreateSession __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDBCreateSession __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateSession )( 
            IDBCreateSession __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppDBSession);
        
        END_INTERFACE
    } IDBCreateSessionVtbl;

    interface IDBCreateSession
    {
        CONST_VTBL struct IDBCreateSessionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDBCreateSession_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDBCreateSession_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDBCreateSession_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDBCreateSession_CreateSession(This,pUnkOuter,riid,ppDBSession)	\
    (This)->lpVtbl -> CreateSession(This,pUnkOuter,riid,ppDBSession)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBCreateSession_RemoteCreateSession_Proxy( 
    IDBCreateSession __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppDBSession,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IDBCreateSession_RemoteCreateSession_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDBCreateSession_INTERFACE_DEFINED__ */


#ifndef __ISourcesRowset_INTERFACE_DEFINED__
#define __ISourcesRowset_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ISourcesRowset
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 


typedef DWORD DBSOURCETYPE;


enum DBSOURCETYPEENUM
    {	DBSOURCETYPE_DATASOURCE	= 1,
	DBSOURCETYPE_ENUMERATOR	= 2
    };
//@@@+ V2.0
#if( OLEDBVER >= 0x0200 )

enum DBSOURCETYPEENUM20
    {	DBSOURCETYPE_DATASOURCE_TDP	= 1,
	DBSOURCETYPE_DATASOURCE_MDP	= 3
    };
#endif // OLEDBVER >= 0x0200
//@@@- V2.0

EXTERN_C const IID IID_ISourcesRowset;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a1e-2a1c-11ce-ade5-00aa0044773d")
    ISourcesRowset : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetSourcesRowset( 
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ REFIID riid,
            /* [in] */ ULONG cPropertySets,
            /* [size_is][unique][out][in] */ DBPROPSET __RPC_FAR rgProperties[  ],
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppSourcesRowset) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISourcesRowsetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISourcesRowset __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISourcesRowset __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISourcesRowset __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSourcesRowset )( 
            ISourcesRowset __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ REFIID riid,
            /* [in] */ ULONG cPropertySets,
            /* [size_is][unique][out][in] */ DBPROPSET __RPC_FAR rgProperties[  ],
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppSourcesRowset);
        
        END_INTERFACE
    } ISourcesRowsetVtbl;

    interface ISourcesRowset
    {
        CONST_VTBL struct ISourcesRowsetVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISourcesRowset_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISourcesRowset_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISourcesRowset_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISourcesRowset_GetSourcesRowset(This,pUnkOuter,riid,cPropertySets,rgProperties,ppSourcesRowset)	\
    (This)->lpVtbl -> GetSourcesRowset(This,pUnkOuter,riid,cPropertySets,rgProperties,ppSourcesRowset)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE ISourcesRowset_RemoteGetSourcesRowset_Proxy( 
    ISourcesRowset __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ REFIID riid,
    /* [in] */ ULONG cPropertySets,
    /* [size_is][unique][in] */ DBPROPSET __RPC_FAR *rgProperties,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppSourcesRowset,
    /* [in] */ ULONG cTotalProps,
    /* [size_is][out] */ DBPROPSTATUS __RPC_FAR *rgPropStatus,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB ISourcesRowset_RemoteGetSourcesRowset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISourcesRowset_INTERFACE_DEFINED__ */


#ifndef __IDBProperties_INTERFACE_DEFINED__
#define __IDBProperties_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDBProperties
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IDBProperties;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a8a-2a1c-11ce-ade5-00aa0044773d")
    IDBProperties : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetProperties( 
            /* [in] */ ULONG cPropertyIDSets,
            /* [size_is][in] */ const DBPROPIDSET __RPC_FAR rgPropertyIDSets[  ],
            /* [out][in] */ ULONG __RPC_FAR *pcPropertySets,
            /* [size_is][size_is][out] */ DBPROPSET __RPC_FAR *__RPC_FAR *prgPropertySets) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetPropertyInfo( 
            /* [in] */ ULONG cPropertyIDSets,
            /* [size_is][in] */ const DBPROPIDSET __RPC_FAR rgPropertyIDSets[  ],
            /* [out][in] */ ULONG __RPC_FAR *pcPropertyInfoSets,
            /* [size_is][size_is][out] */ DBPROPINFOSET __RPC_FAR *__RPC_FAR *prgPropertyInfoSets,
            /* [out] */ OLECHAR __RPC_FAR *__RPC_FAR *ppDescBuffer) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE SetProperties( 
            /* [in] */ ULONG cPropertySets,
            /* [size_is][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ]) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDBPropertiesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDBProperties __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDBProperties __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDBProperties __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetProperties )( 
            IDBProperties __RPC_FAR * This,
            /* [in] */ ULONG cPropertyIDSets,
            /* [size_is][in] */ const DBPROPIDSET __RPC_FAR rgPropertyIDSets[  ],
            /* [out][in] */ ULONG __RPC_FAR *pcPropertySets,
            /* [size_is][size_is][out] */ DBPROPSET __RPC_FAR *__RPC_FAR *prgPropertySets);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPropertyInfo )( 
            IDBProperties __RPC_FAR * This,
            /* [in] */ ULONG cPropertyIDSets,
            /* [size_is][in] */ const DBPROPIDSET __RPC_FAR rgPropertyIDSets[  ],
            /* [out][in] */ ULONG __RPC_FAR *pcPropertyInfoSets,
            /* [size_is][size_is][out] */ DBPROPINFOSET __RPC_FAR *__RPC_FAR *prgPropertyInfoSets,
            /* [out] */ OLECHAR __RPC_FAR *__RPC_FAR *ppDescBuffer);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetProperties )( 
            IDBProperties __RPC_FAR * This,
            /* [in] */ ULONG cPropertySets,
            /* [size_is][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ]);
        
        END_INTERFACE
    } IDBPropertiesVtbl;

    interface IDBProperties
    {
        CONST_VTBL struct IDBPropertiesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDBProperties_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDBProperties_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDBProperties_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDBProperties_GetProperties(This,cPropertyIDSets,rgPropertyIDSets,pcPropertySets,prgPropertySets)	\
    (This)->lpVtbl -> GetProperties(This,cPropertyIDSets,rgPropertyIDSets,pcPropertySets,prgPropertySets)

#define IDBProperties_GetPropertyInfo(This,cPropertyIDSets,rgPropertyIDSets,pcPropertyInfoSets,prgPropertyInfoSets,ppDescBuffer)	\
    (This)->lpVtbl -> GetPropertyInfo(This,cPropertyIDSets,rgPropertyIDSets,pcPropertyInfoSets,prgPropertyInfoSets,ppDescBuffer)

#define IDBProperties_SetProperties(This,cPropertySets,rgPropertySets)	\
    (This)->lpVtbl -> SetProperties(This,cPropertySets,rgPropertySets)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBProperties_RemoteGetProperties_Proxy( 
    IDBProperties __RPC_FAR * This,
    /* [in] */ ULONG cPropertyIDSets,
    /* [size_is][unique][in] */ const DBPROPIDSET __RPC_FAR *rgPropertyIDSets,
    /* [out][in] */ ULONG __RPC_FAR *pcPropertySets,
    /* [size_is][size_is][out] */ DBPROPSET __RPC_FAR *__RPC_FAR *prgPropertySets,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IDBProperties_RemoteGetProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBProperties_RemoteGetPropertyInfo_Proxy( 
    IDBProperties __RPC_FAR * This,
    /* [in] */ ULONG cPropertyIDSets,
    /* [size_is][unique][in] */ const DBPROPIDSET __RPC_FAR *rgPropertyIDSets,
    /* [out][in] */ ULONG __RPC_FAR *pcPropertyInfoSets,
    /* [size_is][size_is][out] */ DBPROPINFOSET __RPC_FAR *__RPC_FAR *prgPropertyInfoSets,
    /* [out][in] */ ULONG __RPC_FAR *pcOffsets,
    /* [size_is][size_is][out] */ ULONG __RPC_FAR *__RPC_FAR *prgDescOffsets,
    /* [out][in] */ ULONG __RPC_FAR *pcbDescBuffer,
    /* [size_is][size_is][unique][out][in] */ OLECHAR __RPC_FAR *__RPC_FAR *ppDescBuffer,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IDBProperties_RemoteGetPropertyInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBProperties_RemoteSetProperties_Proxy( 
    IDBProperties __RPC_FAR * This,
    /* [in] */ ULONG cPropertySets,
    /* [size_is][unique][in] */ DBPROPSET __RPC_FAR *rgPropertySets,
    /* [in] */ ULONG cTotalProps,
    /* [size_is][out] */ DBPROPSTATUS __RPC_FAR *rgPropStatus,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IDBProperties_RemoteSetProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDBProperties_INTERFACE_DEFINED__ */


#ifndef __IDBInitialize_INTERFACE_DEFINED__
#define __IDBInitialize_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDBInitialize
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IDBInitialize;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a8b-2a1c-11ce-ade5-00aa0044773d")
    IDBInitialize : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE Initialize( void) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE Uninitialize( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDBInitializeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDBInitialize __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDBInitialize __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDBInitialize __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IDBInitialize __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Uninitialize )( 
            IDBInitialize __RPC_FAR * This);
        
        END_INTERFACE
    } IDBInitializeVtbl;

    interface IDBInitialize
    {
        CONST_VTBL struct IDBInitializeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDBInitialize_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDBInitialize_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDBInitialize_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDBInitialize_Initialize(This)	\
    (This)->lpVtbl -> Initialize(This)

#define IDBInitialize_Uninitialize(This)	\
    (This)->lpVtbl -> Uninitialize(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBInitialize_RemoteInitialize_Proxy( 
    IDBInitialize __RPC_FAR * This,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IDBInitialize_RemoteInitialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBInitialize_RemoteUninitialize_Proxy( 
    IDBInitialize __RPC_FAR * This,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IDBInitialize_RemoteUninitialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDBInitialize_INTERFACE_DEFINED__ */


#ifndef __IDBInfo_INTERFACE_DEFINED__
#define __IDBInfo_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDBInfo
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 


typedef DWORD DBLITERAL;


enum DBLITERALENUM
    {	DBLITERAL_INVALID	= 0,
	DBLITERAL_BINARY_LITERAL	= 1,
	DBLITERAL_CATALOG_NAME	= 2,
	DBLITERAL_CATALOG_SEPARATOR	= 3,
	DBLITERAL_CHAR_LITERAL	= 4,
	DBLITERAL_COLUMN_ALIAS	= 5,
	DBLITERAL_COLUMN_NAME	= 6,
	DBLITERAL_CORRELATION_NAME	= 7,
	DBLITERAL_CURSOR_NAME	= 8,
	DBLITERAL_ESCAPE_PERCENT	= 9,
	DBLITERAL_ESCAPE_UNDERSCORE	= 10,
	DBLITERAL_INDEX_NAME	= 11,
	DBLITERAL_LIKE_PERCENT	= 12,
	DBLITERAL_LIKE_UNDERSCORE	= 13,
	DBLITERAL_PROCEDURE_NAME	= 14,
	DBLITERAL_QUOTE	= 15,
	DBLITERAL_SCHEMA_NAME	= 16,
	DBLITERAL_TABLE_NAME	= 17,
	DBLITERAL_TEXT_COMMAND	= 18,
	DBLITERAL_USER_NAME	= 19,
	DBLITERAL_VIEW_NAME	= 20
    };
//@@@+ V2.0
#if( OLEDBVER >= 0x0200 )
#define DBLITERAL_QUOTE_PREFIX DBLITERAL_QUOTE

enum DBLITERALENUM20
    {	DBLITERAL_CUBE_NAME	= 21,
	DBLITERAL_DIMENSION_NAME	= 22,
	DBLITERAL_HIERARCHY_NAME	= 23,
	DBLITERAL_LEVEL_NAME	= 24,
	DBLITERAL_MEMBER_NAME	= 25,
	DBLITERAL_PROPERTY_NAME	= 26,
	DBLITERAL_SCHEMA_SEPARATOR	= 27,
	DBLITERAL_QUOTE_SUFFIX	= 28
    };
#endif // OLEDBVER >= 0x0200
//@@@- V2.0
typedef struct  tagDBLITERALINFO
    {
    LPOLESTR pwszLiteralValue;
    LPOLESTR pwszInvalidChars;
    LPOLESTR pwszInvalidStartingChars;
    DBLITERAL lt;
    BOOL fSupported;
    ULONG cchMaxLen;
    }	DBLITERALINFO;


EXTERN_C const IID IID_IDBInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a89-2a1c-11ce-ade5-00aa0044773d")
    IDBInfo : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetKeywords( 
            /* [out] */ LPOLESTR __RPC_FAR *ppwszKeywords) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetLiteralInfo( 
            /* [in] */ ULONG cLiterals,
            /* [size_is][in] */ const DBLITERAL __RPC_FAR rgLiterals[  ],
            /* [out][in] */ ULONG __RPC_FAR *pcLiteralInfo,
            /* [size_is][size_is][out] */ DBLITERALINFO __RPC_FAR *__RPC_FAR *prgLiteralInfo,
            /* [out] */ OLECHAR __RPC_FAR *__RPC_FAR *ppCharBuffer) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDBInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDBInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDBInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDBInfo __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetKeywords )( 
            IDBInfo __RPC_FAR * This,
            /* [out] */ LPOLESTR __RPC_FAR *ppwszKeywords);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLiteralInfo )( 
            IDBInfo __RPC_FAR * This,
            /* [in] */ ULONG cLiterals,
            /* [size_is][in] */ const DBLITERAL __RPC_FAR rgLiterals[  ],
            /* [out][in] */ ULONG __RPC_FAR *pcLiteralInfo,
            /* [size_is][size_is][out] */ DBLITERALINFO __RPC_FAR *__RPC_FAR *prgLiteralInfo,
            /* [out] */ OLECHAR __RPC_FAR *__RPC_FAR *ppCharBuffer);
        
        END_INTERFACE
    } IDBInfoVtbl;

    interface IDBInfo
    {
        CONST_VTBL struct IDBInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDBInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDBInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDBInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDBInfo_GetKeywords(This,ppwszKeywords)	\
    (This)->lpVtbl -> GetKeywords(This,ppwszKeywords)

#define IDBInfo_GetLiteralInfo(This,cLiterals,rgLiterals,pcLiteralInfo,prgLiteralInfo,ppCharBuffer)	\
    (This)->lpVtbl -> GetLiteralInfo(This,cLiterals,rgLiterals,pcLiteralInfo,prgLiteralInfo,ppCharBuffer)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBInfo_RemoteGetKeywords_Proxy( 
    IDBInfo __RPC_FAR * This,
    /* [unique][out][in] */ LPOLESTR __RPC_FAR *ppwszKeywords,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IDBInfo_RemoteGetKeywords_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBInfo_RemoteGetLiteralInfo_Proxy( 
    IDBInfo __RPC_FAR * This,
    /* [in] */ ULONG cLiterals,
    /* [size_is][unique][in] */ const DBLITERAL __RPC_FAR *rgLiterals,
    /* [out][in] */ ULONG __RPC_FAR *pcLiteralInfo,
    /* [size_is][size_is][out] */ DBLITERALINFO __RPC_FAR *__RPC_FAR *prgLiteralInfo,
    /* [size_is][size_is][out] */ ULONG __RPC_FAR *__RPC_FAR *prgLVOffsets,
    /* [size_is][size_is][out] */ ULONG __RPC_FAR *__RPC_FAR *prgICOffsets,
    /* [size_is][size_is][out] */ ULONG __RPC_FAR *__RPC_FAR *prgISCOffsets,
    /* [out][in] */ ULONG __RPC_FAR *pcbCharBuffer,
    /* [size_is][size_is][unique][out][in] */ OLECHAR __RPC_FAR *__RPC_FAR *ppCharBuffer,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IDBInfo_RemoteGetLiteralInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDBInfo_INTERFACE_DEFINED__ */


#ifndef __IDBDataSourceAdmin_INTERFACE_DEFINED__
#define __IDBDataSourceAdmin_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDBDataSourceAdmin
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IDBDataSourceAdmin;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a7a-2a1c-11ce-ade5-00aa0044773d")
    IDBDataSourceAdmin : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE CreateDataSource( 
            /* [in] */ ULONG cPropertySets,
            /* [size_is][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ],
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppDBSession) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE DestroyDataSource( void) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetCreationProperties( 
            /* [in] */ ULONG cPropertyIDSets,
            /* [size_is][in] */ const DBPROPIDSET __RPC_FAR rgPropertyIDSets[  ],
            /* [out][in] */ ULONG __RPC_FAR *pcPropertyInfoSets,
            /* [size_is][size_is][out] */ DBPROPINFOSET __RPC_FAR *__RPC_FAR *prgPropertyInfoSets,
            /* [out] */ OLECHAR __RPC_FAR *__RPC_FAR *ppDescBuffer) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE ModifyDataSource( 
            /* [in] */ ULONG cPropertySets,
            /* [size_is][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ]) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDBDataSourceAdminVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDBDataSourceAdmin __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDBDataSourceAdmin __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDBDataSourceAdmin __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateDataSource )( 
            IDBDataSourceAdmin __RPC_FAR * This,
            /* [in] */ ULONG cPropertySets,
            /* [size_is][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ],
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppDBSession);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DestroyDataSource )( 
            IDBDataSourceAdmin __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCreationProperties )( 
            IDBDataSourceAdmin __RPC_FAR * This,
            /* [in] */ ULONG cPropertyIDSets,
            /* [size_is][in] */ const DBPROPIDSET __RPC_FAR rgPropertyIDSets[  ],
            /* [out][in] */ ULONG __RPC_FAR *pcPropertyInfoSets,
            /* [size_is][size_is][out] */ DBPROPINFOSET __RPC_FAR *__RPC_FAR *prgPropertyInfoSets,
            /* [out] */ OLECHAR __RPC_FAR *__RPC_FAR *ppDescBuffer);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ModifyDataSource )( 
            IDBDataSourceAdmin __RPC_FAR * This,
            /* [in] */ ULONG cPropertySets,
            /* [size_is][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ]);
        
        END_INTERFACE
    } IDBDataSourceAdminVtbl;

    interface IDBDataSourceAdmin
    {
        CONST_VTBL struct IDBDataSourceAdminVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDBDataSourceAdmin_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDBDataSourceAdmin_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDBDataSourceAdmin_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDBDataSourceAdmin_CreateDataSource(This,cPropertySets,rgPropertySets,pUnkOuter,riid,ppDBSession)	\
    (This)->lpVtbl -> CreateDataSource(This,cPropertySets,rgPropertySets,pUnkOuter,riid,ppDBSession)

#define IDBDataSourceAdmin_DestroyDataSource(This)	\
    (This)->lpVtbl -> DestroyDataSource(This)

#define IDBDataSourceAdmin_GetCreationProperties(This,cPropertyIDSets,rgPropertyIDSets,pcPropertyInfoSets,prgPropertyInfoSets,ppDescBuffer)	\
    (This)->lpVtbl -> GetCreationProperties(This,cPropertyIDSets,rgPropertyIDSets,pcPropertyInfoSets,prgPropertyInfoSets,ppDescBuffer)

#define IDBDataSourceAdmin_ModifyDataSource(This,cPropertySets,rgPropertySets)	\
    (This)->lpVtbl -> ModifyDataSource(This,cPropertySets,rgPropertySets)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBDataSourceAdmin_RemoteCreateDataSource_Proxy( 
    IDBDataSourceAdmin __RPC_FAR * This,
    /* [in] */ ULONG cPropertySets,
    /* [size_is][unique][in] */ DBPROPSET __RPC_FAR *rgPropertySets,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ REFIID riid,
    /* [iid_is][unique][out][in] */ IUnknown __RPC_FAR *__RPC_FAR *ppDBSession,
    /* [in] */ ULONG cTotalProps,
    /* [size_is][out] */ DBPROPSTATUS __RPC_FAR *rgPropStatus,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IDBDataSourceAdmin_RemoteCreateDataSource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBDataSourceAdmin_RemoteDestroyDataSource_Proxy( 
    IDBDataSourceAdmin __RPC_FAR * This,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IDBDataSourceAdmin_RemoteDestroyDataSource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBDataSourceAdmin_RemoteGetCreationProperties_Proxy( 
    IDBDataSourceAdmin __RPC_FAR * This,
    /* [in] */ ULONG cPropertyIDSets,
    /* [size_is][unique][in] */ const DBPROPIDSET __RPC_FAR *rgPropertyIDSets,
    /* [out][in] */ ULONG __RPC_FAR *pcPropertyInfoSets,
    /* [size_is][size_is][out] */ DBPROPINFOSET __RPC_FAR *__RPC_FAR *prgPropertyInfoSets,
    /* [out][in] */ ULONG __RPC_FAR *pcOffsets,
    /* [size_is][size_is][out] */ ULONG __RPC_FAR *__RPC_FAR *prgDescOffsets,
    /* [out][in] */ ULONG __RPC_FAR *pcbDescBuffer,
    /* [size_is][size_is][unique][out][in] */ OLECHAR __RPC_FAR *__RPC_FAR *ppDescBuffer,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IDBDataSourceAdmin_RemoteGetCreationProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBDataSourceAdmin_RemoteModifyDataSource_Proxy( 
    IDBDataSourceAdmin __RPC_FAR * This,
    /* [in] */ ULONG cPropertySets,
    /* [size_is][in] */ DBPROPSET __RPC_FAR *rgPropertySets,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IDBDataSourceAdmin_RemoteModifyDataSource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDBDataSourceAdmin_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_oledb_0123
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


//@@@+ V1.5
#if( OLEDBVER >= 0x0150 )


extern RPC_IF_HANDLE __MIDL_itf_oledb_0123_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_oledb_0123_v0_0_s_ifspec;

#ifndef __IDBAsynchNotify_INTERFACE_DEFINED__
#define __IDBAsynchNotify_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDBAsynchNotify
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IDBAsynchNotify;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a96-2a1c-11ce-ade5-00aa0044773d")
    IDBAsynchNotify : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE OnLowResource( 
            /* [in] */ DWORD dwReserved) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE OnProgress( 
            /* [in] */ HCHAPTER hChapter,
            /* [in] */ DBASYNCHOP eOperation,
            /* [in] */ ULONG ulProgress,
            /* [in] */ ULONG ulProgressMax,
            /* [in] */ DBASYNCHPHASE eAsynchPhase,
            /* [in] */ LPOLESTR pwszStatusText) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE OnStop( 
            /* [in] */ HCHAPTER hChapter,
            /* [in] */ DBASYNCHOP eOperation,
            /* [in] */ HRESULT hrStatus,
            /* [in] */ LPOLESTR pwszStatusText) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDBAsynchNotifyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDBAsynchNotify __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDBAsynchNotify __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDBAsynchNotify __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnLowResource )( 
            IDBAsynchNotify __RPC_FAR * This,
            /* [in] */ DWORD dwReserved);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnProgress )( 
            IDBAsynchNotify __RPC_FAR * This,
            /* [in] */ HCHAPTER hChapter,
            /* [in] */ DBASYNCHOP eOperation,
            /* [in] */ ULONG ulProgress,
            /* [in] */ ULONG ulProgressMax,
            /* [in] */ DBASYNCHPHASE eAsynchPhase,
            /* [in] */ LPOLESTR pwszStatusText);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnStop )( 
            IDBAsynchNotify __RPC_FAR * This,
            /* [in] */ HCHAPTER hChapter,
            /* [in] */ DBASYNCHOP eOperation,
            /* [in] */ HRESULT hrStatus,
            /* [in] */ LPOLESTR pwszStatusText);
        
        END_INTERFACE
    } IDBAsynchNotifyVtbl;

    interface IDBAsynchNotify
    {
        CONST_VTBL struct IDBAsynchNotifyVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDBAsynchNotify_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDBAsynchNotify_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDBAsynchNotify_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDBAsynchNotify_OnLowResource(This,dwReserved)	\
    (This)->lpVtbl -> OnLowResource(This,dwReserved)

#define IDBAsynchNotify_OnProgress(This,hChapter,eOperation,ulProgress,ulProgressMax,eAsynchPhase,pwszStatusText)	\
    (This)->lpVtbl -> OnProgress(This,hChapter,eOperation,ulProgress,ulProgressMax,eAsynchPhase,pwszStatusText)

#define IDBAsynchNotify_OnStop(This,hChapter,eOperation,hrStatus,pwszStatusText)	\
    (This)->lpVtbl -> OnStop(This,hChapter,eOperation,hrStatus,pwszStatusText)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBAsynchNotify_RemoteOnLowResource_Proxy( 
    IDBAsynchNotify __RPC_FAR * This,
    /* [in] */ DWORD dwReserved,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IDBAsynchNotify_RemoteOnLowResource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBAsynchNotify_RemoteOnProgress_Proxy( 
    IDBAsynchNotify __RPC_FAR * This,
    /* [in] */ HCHAPTER hChapter,
    /* [in] */ DBASYNCHOP eOperation,
    /* [in] */ ULONG ulProgress,
    /* [in] */ ULONG ulProgressMax,
    /* [in] */ DBASYNCHPHASE eAsynchPhase,
    /* [in] */ LPOLESTR pwszStatusText,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IDBAsynchNotify_RemoteOnProgress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBAsynchNotify_RemoteOnStop_Proxy( 
    IDBAsynchNotify __RPC_FAR * This,
    /* [in] */ HCHAPTER hChapter,
    /* [in] */ DBASYNCHOP eOperation,
    /* [in] */ HRESULT hrStatus,
    /* [in] */ LPOLESTR pwszStatusText,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IDBAsynchNotify_RemoteOnStop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDBAsynchNotify_INTERFACE_DEFINED__ */


#ifndef __IDBAsynchStatus_INTERFACE_DEFINED__
#define __IDBAsynchStatus_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDBAsynchStatus
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IDBAsynchStatus;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a95-2a1c-11ce-ade5-00aa0044773d")
    IDBAsynchStatus : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE Abort( 
            /* [in] */ HCHAPTER hChapter,
            /* [in] */ DBASYNCHOP eOperation) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetStatus( 
            /* [in] */ HCHAPTER hChapter,
            /* [in] */ DBASYNCHOP eOperation,
            /* [out] */ ULONG __RPC_FAR *pulProgress,
            /* [out] */ ULONG __RPC_FAR *pulProgressMax,
            /* [out] */ DBASYNCHPHASE __RPC_FAR *peAsynchPhase,
            /* [out] */ LPOLESTR __RPC_FAR *ppwszStatusText) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDBAsynchStatusVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDBAsynchStatus __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDBAsynchStatus __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDBAsynchStatus __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Abort )( 
            IDBAsynchStatus __RPC_FAR * This,
            /* [in] */ HCHAPTER hChapter,
            /* [in] */ DBASYNCHOP eOperation);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStatus )( 
            IDBAsynchStatus __RPC_FAR * This,
            /* [in] */ HCHAPTER hChapter,
            /* [in] */ DBASYNCHOP eOperation,
            /* [out] */ ULONG __RPC_FAR *pulProgress,
            /* [out] */ ULONG __RPC_FAR *pulProgressMax,
            /* [out] */ DBASYNCHPHASE __RPC_FAR *peAsynchPhase,
            /* [out] */ LPOLESTR __RPC_FAR *ppwszStatusText);
        
        END_INTERFACE
    } IDBAsynchStatusVtbl;

    interface IDBAsynchStatus
    {
        CONST_VTBL struct IDBAsynchStatusVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDBAsynchStatus_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDBAsynchStatus_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDBAsynchStatus_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDBAsynchStatus_Abort(This,hChapter,eOperation)	\
    (This)->lpVtbl -> Abort(This,hChapter,eOperation)

#define IDBAsynchStatus_GetStatus(This,hChapter,eOperation,pulProgress,pulProgressMax,peAsynchPhase,ppwszStatusText)	\
    (This)->lpVtbl -> GetStatus(This,hChapter,eOperation,pulProgress,pulProgressMax,peAsynchPhase,ppwszStatusText)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBAsynchStatus_RemoteAbort_Proxy( 
    IDBAsynchStatus __RPC_FAR * This,
    /* [in] */ HCHAPTER hChapter,
    /* [in] */ DBASYNCHOP eOperation,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IDBAsynchStatus_RemoteAbort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBAsynchStatus_RemoteGetStatus_Proxy( 
    IDBAsynchStatus __RPC_FAR * This,
    /* [in] */ HCHAPTER hChapter,
    /* [in] */ DBASYNCHOP eOperation,
    /* [out] */ ULONG __RPC_FAR *pulProgress,
    /* [out] */ ULONG __RPC_FAR *pulProgressMax,
    /* [out] */ DBASYNCHPHASE __RPC_FAR *peAsynchPhase,
    /* [out] */ LPOLESTR __RPC_FAR *ppwszStatusText,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IDBAsynchStatus_RemoteGetStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDBAsynchStatus_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_oledb_0125
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


#endif // OLEDBVER >= 0x0150
//@@@- V1.5


extern RPC_IF_HANDLE __MIDL_itf_oledb_0125_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_oledb_0125_v0_0_s_ifspec;

#ifndef __ISessionProperties_INTERFACE_DEFINED__
#define __ISessionProperties_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ISessionProperties
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_ISessionProperties;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a85-2a1c-11ce-ade5-00aa0044773d")
    ISessionProperties : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetProperties( 
            /* [in] */ ULONG cPropertyIDSets,
            /* [size_is][in] */ const DBPROPIDSET __RPC_FAR rgPropertyIDSets[  ],
            /* [out][in] */ ULONG __RPC_FAR *pcPropertySets,
            /* [size_is][size_is][out] */ DBPROPSET __RPC_FAR *__RPC_FAR *prgPropertySets) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE SetProperties( 
            /* [in] */ ULONG cPropertySets,
            /* [size_is][unique][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ]) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISessionPropertiesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISessionProperties __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISessionProperties __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISessionProperties __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetProperties )( 
            ISessionProperties __RPC_FAR * This,
            /* [in] */ ULONG cPropertyIDSets,
            /* [size_is][in] */ const DBPROPIDSET __RPC_FAR rgPropertyIDSets[  ],
            /* [out][in] */ ULONG __RPC_FAR *pcPropertySets,
            /* [size_is][size_is][out] */ DBPROPSET __RPC_FAR *__RPC_FAR *prgPropertySets);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetProperties )( 
            ISessionProperties __RPC_FAR * This,
            /* [in] */ ULONG cPropertySets,
            /* [size_is][unique][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ]);
        
        END_INTERFACE
    } ISessionPropertiesVtbl;

    interface ISessionProperties
    {
        CONST_VTBL struct ISessionPropertiesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISessionProperties_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISessionProperties_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISessionProperties_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISessionProperties_GetProperties(This,cPropertyIDSets,rgPropertyIDSets,pcPropertySets,prgPropertySets)	\
    (This)->lpVtbl -> GetProperties(This,cPropertyIDSets,rgPropertyIDSets,pcPropertySets,prgPropertySets)

#define ISessionProperties_SetProperties(This,cPropertySets,rgPropertySets)	\
    (This)->lpVtbl -> SetProperties(This,cPropertySets,rgPropertySets)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE ISessionProperties_RemoteGetProperties_Proxy( 
    ISessionProperties __RPC_FAR * This,
    /* [in] */ ULONG cPropertyIDSets,
    /* [size_is][unique][in] */ const DBPROPIDSET __RPC_FAR *rgPropertyIDSets,
    /* [out][in] */ ULONG __RPC_FAR *pcPropertySets,
    /* [size_is][size_is][out] */ DBPROPSET __RPC_FAR *__RPC_FAR *prgPropertySets,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB ISessionProperties_RemoteGetProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE ISessionProperties_RemoteSetProperties_Proxy( 
    ISessionProperties __RPC_FAR * This,
    /* [in] */ ULONG cPropertySets,
    /* [size_is][unique][in] */ DBPROPSET __RPC_FAR *rgPropertySets,
    /* [in] */ ULONG cTotalProps,
    /* [size_is][out] */ DBPROPSTATUS __RPC_FAR *rgPropStatus,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB ISessionProperties_RemoteSetProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISessionProperties_INTERFACE_DEFINED__ */


#ifndef __IIndexDefinition_INTERFACE_DEFINED__
#define __IIndexDefinition_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IIndexDefinition
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IIndexDefinition;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a68-2a1c-11ce-ade5-00aa0044773d")
    IIndexDefinition : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE CreateIndex( 
            /* [in] */ DBID __RPC_FAR *pTableID,
            /* [in] */ DBID __RPC_FAR *pIndexID,
            /* [in] */ ULONG cIndexColumnDescs,
            /* [size_is][in] */ const DBINDEXCOLUMNDESC __RPC_FAR rgIndexColumnDescs[  ],
            /* [in] */ ULONG cPropertySets,
            /* [size_is][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ],
            /* [out] */ DBID __RPC_FAR *__RPC_FAR *ppIndexID) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE DropIndex( 
            /* [unique][in] */ DBID __RPC_FAR *pTableID,
            /* [unique][in] */ DBID __RPC_FAR *pIndexID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IIndexDefinitionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IIndexDefinition __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IIndexDefinition __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IIndexDefinition __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateIndex )( 
            IIndexDefinition __RPC_FAR * This,
            /* [in] */ DBID __RPC_FAR *pTableID,
            /* [in] */ DBID __RPC_FAR *pIndexID,
            /* [in] */ ULONG cIndexColumnDescs,
            /* [size_is][in] */ const DBINDEXCOLUMNDESC __RPC_FAR rgIndexColumnDescs[  ],
            /* [in] */ ULONG cPropertySets,
            /* [size_is][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ],
            /* [out] */ DBID __RPC_FAR *__RPC_FAR *ppIndexID);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DropIndex )( 
            IIndexDefinition __RPC_FAR * This,
            /* [unique][in] */ DBID __RPC_FAR *pTableID,
            /* [unique][in] */ DBID __RPC_FAR *pIndexID);
        
        END_INTERFACE
    } IIndexDefinitionVtbl;

    interface IIndexDefinition
    {
        CONST_VTBL struct IIndexDefinitionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIndexDefinition_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IIndexDefinition_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IIndexDefinition_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IIndexDefinition_CreateIndex(This,pTableID,pIndexID,cIndexColumnDescs,rgIndexColumnDescs,cPropertySets,rgPropertySets,ppIndexID)	\
    (This)->lpVtbl -> CreateIndex(This,pTableID,pIndexID,cIndexColumnDescs,rgIndexColumnDescs,cPropertySets,rgPropertySets,ppIndexID)

#define IIndexDefinition_DropIndex(This,pTableID,pIndexID)	\
    (This)->lpVtbl -> DropIndex(This,pTableID,pIndexID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE IIndexDefinition_RemoteCreateIndex_Proxy( 
    IIndexDefinition __RPC_FAR * This,
    /* [in] */ DBID __RPC_FAR *pTableID,
    /* [unique][in] */ DBID __RPC_FAR *pIndexID,
    /* [in] */ ULONG cIndexColumnDescs,
    /* [size_is][in] */ const DBINDEXCOLUMNDESC __RPC_FAR *rgIndexColumnDescs,
    /* [in] */ ULONG cPropertySets,
    /* [size_is][unique][in] */ DBPROPSET __RPC_FAR *rgPropertySets,
    /* [unique][out][in] */ DBID __RPC_FAR *__RPC_FAR *ppIndexID,
    /* [in] */ ULONG cTotalProps,
    /* [size_is][out] */ DBPROPSTATUS __RPC_FAR *rgPropStatus,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IIndexDefinition_RemoteCreateIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IIndexDefinition_RemoteDropIndex_Proxy( 
    IIndexDefinition __RPC_FAR * This,
    /* [unique][in] */ DBID __RPC_FAR *pTableID,
    /* [unique][in] */ DBID __RPC_FAR *pIndexID,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IIndexDefinition_RemoteDropIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IIndexDefinition_INTERFACE_DEFINED__ */


#ifndef __ITableDefinition_INTERFACE_DEFINED__
#define __ITableDefinition_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITableDefinition
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_ITableDefinition;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a86-2a1c-11ce-ade5-00aa0044773d")
    ITableDefinition : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE CreateTable( 
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ DBID __RPC_FAR *pTableID,
            /* [in] */ ULONG cColumnDescs,
            /* [size_is][in] */ const DBCOLUMNDESC __RPC_FAR rgColumnDescs[  ],
            /* [in] */ REFIID riid,
            /* [in] */ ULONG cPropertySets,
            /* [size_is][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ],
            /* [out] */ DBID __RPC_FAR *__RPC_FAR *ppTableID,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE DropTable( 
            /* [unique][in] */ DBID __RPC_FAR *pTableID) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE AddColumn( 
            /* [in] */ DBID __RPC_FAR *pTableID,
            /* [out][in] */ DBCOLUMNDESC __RPC_FAR *pColumnDesc,
            /* [out] */ DBID __RPC_FAR *__RPC_FAR *ppColumnID) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE DropColumn( 
            /* [unique][in] */ DBID __RPC_FAR *pTableID,
            /* [unique][in] */ DBID __RPC_FAR *pColumnID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITableDefinitionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITableDefinition __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITableDefinition __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITableDefinition __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateTable )( 
            ITableDefinition __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ DBID __RPC_FAR *pTableID,
            /* [in] */ ULONG cColumnDescs,
            /* [size_is][in] */ const DBCOLUMNDESC __RPC_FAR rgColumnDescs[  ],
            /* [in] */ REFIID riid,
            /* [in] */ ULONG cPropertySets,
            /* [size_is][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ],
            /* [out] */ DBID __RPC_FAR *__RPC_FAR *ppTableID,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DropTable )( 
            ITableDefinition __RPC_FAR * This,
            /* [unique][in] */ DBID __RPC_FAR *pTableID);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddColumn )( 
            ITableDefinition __RPC_FAR * This,
            /* [in] */ DBID __RPC_FAR *pTableID,
            /* [out][in] */ DBCOLUMNDESC __RPC_FAR *pColumnDesc,
            /* [out] */ DBID __RPC_FAR *__RPC_FAR *ppColumnID);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DropColumn )( 
            ITableDefinition __RPC_FAR * This,
            /* [unique][in] */ DBID __RPC_FAR *pTableID,
            /* [unique][in] */ DBID __RPC_FAR *pColumnID);
        
        END_INTERFACE
    } ITableDefinitionVtbl;

    interface ITableDefinition
    {
        CONST_VTBL struct ITableDefinitionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITableDefinition_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITableDefinition_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITableDefinition_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITableDefinition_CreateTable(This,pUnkOuter,pTableID,cColumnDescs,rgColumnDescs,riid,cPropertySets,rgPropertySets,ppTableID,ppRowset)	\
    (This)->lpVtbl -> CreateTable(This,pUnkOuter,pTableID,cColumnDescs,rgColumnDescs,riid,cPropertySets,rgPropertySets,ppTableID,ppRowset)

#define ITableDefinition_DropTable(This,pTableID)	\
    (This)->lpVtbl -> DropTable(This,pTableID)

#define ITableDefinition_AddColumn(This,pTableID,pColumnDesc,ppColumnID)	\
    (This)->lpVtbl -> AddColumn(This,pTableID,pColumnDesc,ppColumnID)

#define ITableDefinition_DropColumn(This,pTableID,pColumnID)	\
    (This)->lpVtbl -> DropColumn(This,pTableID,pColumnID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE ITableDefinition_RemoteCreateTable_Proxy( 
    ITableDefinition __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [unique][in] */ DBID __RPC_FAR *pTableID,
    /* [in] */ ULONG cColumnDescs,
    /* [size_is][in] */ const DBCOLUMNDESC __RPC_FAR *rgColumnDescs,
    /* [in] */ REFIID riid,
    /* [in] */ ULONG cPropertySets,
    /* [size_is][unique][out][in] */ DBPROPSET __RPC_FAR *rgPropertySets,
    /* [unique][out][in] */ DBID __RPC_FAR *__RPC_FAR *ppTableID,
    /* [iid_is][unique][out][in] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset,
    /* [in] */ ULONG cTotalProps,
    /* [size_is][out] */ DBPROPSTATUS __RPC_FAR *rgPropStatus,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB ITableDefinition_RemoteCreateTable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE ITableDefinition_RemoteDropTable_Proxy( 
    ITableDefinition __RPC_FAR * This,
    /* [unique][in] */ DBID __RPC_FAR *pTableID,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB ITableDefinition_RemoteDropTable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE ITableDefinition_RemoteAddColumn_Proxy( 
    ITableDefinition __RPC_FAR * This,
    /* [in] */ DBID __RPC_FAR *pTableID,
    /* [out][in] */ DBCOLUMNDESC __RPC_FAR *pColumnDesc,
    /* [unique][out][in] */ DBID __RPC_FAR *__RPC_FAR *ppColumnID,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB ITableDefinition_RemoteAddColumn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE ITableDefinition_RemoteDropColumn_Proxy( 
    ITableDefinition __RPC_FAR * This,
    /* [unique][in] */ DBID __RPC_FAR *pTableID,
    /* [unique][in] */ DBID __RPC_FAR *pColumnID,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB ITableDefinition_RemoteDropColumn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITableDefinition_INTERFACE_DEFINED__ */


#ifndef __IOpenRowset_INTERFACE_DEFINED__
#define __IOpenRowset_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IOpenRowset
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IOpenRowset;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a69-2a1c-11ce-ade5-00aa0044773d")
    IOpenRowset : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE OpenRowset( 
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [unique][in] */ DBID __RPC_FAR *pTableID,
            /* [unique][in] */ DBID __RPC_FAR *pIndexID,
            /* [in] */ REFIID riid,
            /* [in] */ ULONG cPropertySets,
            /* [size_is][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ],
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IOpenRowsetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IOpenRowset __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IOpenRowset __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IOpenRowset __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenRowset )( 
            IOpenRowset __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [unique][in] */ DBID __RPC_FAR *pTableID,
            /* [unique][in] */ DBID __RPC_FAR *pIndexID,
            /* [in] */ REFIID riid,
            /* [in] */ ULONG cPropertySets,
            /* [size_is][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ],
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset);
        
        END_INTERFACE
    } IOpenRowsetVtbl;

    interface IOpenRowset
    {
        CONST_VTBL struct IOpenRowsetVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IOpenRowset_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IOpenRowset_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IOpenRowset_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IOpenRowset_OpenRowset(This,pUnkOuter,pTableID,pIndexID,riid,cPropertySets,rgPropertySets,ppRowset)	\
    (This)->lpVtbl -> OpenRowset(This,pUnkOuter,pTableID,pIndexID,riid,cPropertySets,rgPropertySets,ppRowset)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE IOpenRowset_RemoteOpenRowset_Proxy( 
    IOpenRowset __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [unique][in] */ DBID __RPC_FAR *pTableID,
    /* [unique][in] */ DBID __RPC_FAR *pIndexID,
    /* [in] */ REFIID riid,
    /* [in] */ ULONG cPropertySets,
    /* [size_is][unique][in] */ DBPROPSET __RPC_FAR *rgPropertySets,
    /* [iid_is][unique][out][in] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset,
    /* [in] */ ULONG cTotalProps,
    /* [size_is][out] */ DBPROPSTATUS __RPC_FAR *rgPropStatus,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IOpenRowset_RemoteOpenRowset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IOpenRowset_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_oledb_0129
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


//@@@+ V2.5
#if( OLEDBVER >= 0x0250 )


extern RPC_IF_HANDLE __MIDL_itf_oledb_0129_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_oledb_0129_v0_0_s_ifspec;

#ifndef __ITableRename_INTERFACE_DEFINED__
#define __ITableRename_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITableRename
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object][local] */ 



EXTERN_C const IID IID_ITableRename;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a77-2a1c-11ce-ade5-00aa0044773d")
    ITableRename : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE RenameColumn( 
            /* [in] */ DBID __RPC_FAR *pTableId,
            /* [in] */ DBID __RPC_FAR *pOldColumnId,
            /* [in] */ DBID __RPC_FAR *pNewColumnId) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RenameTable( 
            /* [in] */ DBID __RPC_FAR *pOldTableId,
            /* [in] */ DBID __RPC_FAR *pOldIndexId,
            /* [in] */ DBID __RPC_FAR *pNewTableId,
            /* [in] */ DBID __RPC_FAR *pNewIndexId) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITableRenameVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITableRename __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITableRename __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITableRename __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RenameColumn )( 
            ITableRename __RPC_FAR * This,
            /* [in] */ DBID __RPC_FAR *pTableId,
            /* [in] */ DBID __RPC_FAR *pOldColumnId,
            /* [in] */ DBID __RPC_FAR *pNewColumnId);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RenameTable )( 
            ITableRename __RPC_FAR * This,
            /* [in] */ DBID __RPC_FAR *pOldTableId,
            /* [in] */ DBID __RPC_FAR *pOldIndexId,
            /* [in] */ DBID __RPC_FAR *pNewTableId,
            /* [in] */ DBID __RPC_FAR *pNewIndexId);
        
        END_INTERFACE
    } ITableRenameVtbl;

    interface ITableRename
    {
        CONST_VTBL struct ITableRenameVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITableRename_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITableRename_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITableRename_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITableRename_RenameColumn(This,pTableId,pOldColumnId,pNewColumnId)	\
    (This)->lpVtbl -> RenameColumn(This,pTableId,pOldColumnId,pNewColumnId)

#define ITableRename_RenameTable(This,pOldTableId,pOldIndexId,pNewTableId,pNewIndexId)	\
    (This)->lpVtbl -> RenameTable(This,pOldTableId,pOldIndexId,pNewTableId,pNewIndexId)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ITableRename_RenameColumn_Proxy( 
    ITableRename __RPC_FAR * This,
    /* [in] */ DBID __RPC_FAR *pTableId,
    /* [in] */ DBID __RPC_FAR *pOldColumnId,
    /* [in] */ DBID __RPC_FAR *pNewColumnId);


void __RPC_STUB ITableRename_RenameColumn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITableRename_RenameTable_Proxy( 
    ITableRename __RPC_FAR * This,
    /* [in] */ DBID __RPC_FAR *pOldTableId,
    /* [in] */ DBID __RPC_FAR *pOldIndexId,
    /* [in] */ DBID __RPC_FAR *pNewTableId,
    /* [in] */ DBID __RPC_FAR *pNewIndexId);


void __RPC_STUB ITableRename_RenameTable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITableRename_INTERFACE_DEFINED__ */


#ifndef __IDBSchemaCommand_INTERFACE_DEFINED__
#define __IDBSchemaCommand_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDBSchemaCommand
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object][local] */ 



EXTERN_C const IID IID_IDBSchemaCommand;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a50-2a1c-11ce-ade5-00aa0044773d")
    IDBSchemaCommand : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetCommand( 
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ REFGUID rguidSchema,
            /* [out] */ ICommand __RPC_FAR *__RPC_FAR *ppCommand) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSchemas( 
            /* [out][in] */ ULONG __RPC_FAR *pcSchemas,
            /* [size_is][size_is][out] */ GUID __RPC_FAR *__RPC_FAR *prgSchemas) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDBSchemaCommandVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDBSchemaCommand __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDBSchemaCommand __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDBSchemaCommand __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCommand )( 
            IDBSchemaCommand __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ REFGUID rguidSchema,
            /* [out] */ ICommand __RPC_FAR *__RPC_FAR *ppCommand);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSchemas )( 
            IDBSchemaCommand __RPC_FAR * This,
            /* [out][in] */ ULONG __RPC_FAR *pcSchemas,
            /* [size_is][size_is][out] */ GUID __RPC_FAR *__RPC_FAR *prgSchemas);
        
        END_INTERFACE
    } IDBSchemaCommandVtbl;

    interface IDBSchemaCommand
    {
        CONST_VTBL struct IDBSchemaCommandVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDBSchemaCommand_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDBSchemaCommand_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDBSchemaCommand_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDBSchemaCommand_GetCommand(This,pUnkOuter,rguidSchema,ppCommand)	\
    (This)->lpVtbl -> GetCommand(This,pUnkOuter,rguidSchema,ppCommand)

#define IDBSchemaCommand_GetSchemas(This,pcSchemas,prgSchemas)	\
    (This)->lpVtbl -> GetSchemas(This,pcSchemas,prgSchemas)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDBSchemaCommand_GetCommand_Proxy( 
    IDBSchemaCommand __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ REFGUID rguidSchema,
    /* [out] */ ICommand __RPC_FAR *__RPC_FAR *ppCommand);


void __RPC_STUB IDBSchemaCommand_GetCommand_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDBSchemaCommand_GetSchemas_Proxy( 
    IDBSchemaCommand __RPC_FAR * This,
    /* [out][in] */ ULONG __RPC_FAR *pcSchemas,
    /* [size_is][size_is][out] */ GUID __RPC_FAR *__RPC_FAR *prgSchemas);


void __RPC_STUB IDBSchemaCommand_GetSchemas_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDBSchemaCommand_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_oledb_0131
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


#endif // OLEDBVER >= 0x0250
//@@@- V2.5


extern RPC_IF_HANDLE __MIDL_itf_oledb_0131_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_oledb_0131_v0_0_s_ifspec;

#ifndef __IDBSchemaRowset_INTERFACE_DEFINED__
#define __IDBSchemaRowset_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDBSchemaRowset
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 


#define CRESTRICTIONS_DBSCHEMA_ASSERTIONS                      3
#define CRESTRICTIONS_DBSCHEMA_CATALOGS                        1
#define CRESTRICTIONS_DBSCHEMA_CHARACTER_SETS                  3
#define CRESTRICTIONS_DBSCHEMA_COLLATIONS                      3
#define CRESTRICTIONS_DBSCHEMA_COLUMNS                         4
#define CRESTRICTIONS_DBSCHEMA_CHECK_CONSTRAINTS               3
#define CRESTRICTIONS_DBSCHEMA_CONSTRAINT_COLUMN_USAGE         4
#define CRESTRICTIONS_DBSCHEMA_CONSTRAINT_TABLE_USAGE          3
#define CRESTRICTIONS_DBSCHEMA_KEY_COLUMN_USAGE                7
#define CRESTRICTIONS_DBSCHEMA_REFERENTIAL_CONSTRAINTS         3
#define CRESTRICTIONS_DBSCHEMA_TABLE_CONSTRAINTS               7
#define CRESTRICTIONS_DBSCHEMA_COLUMN_DOMAIN_USAGE             4
#define CRESTRICTIONS_DBSCHEMA_INDEXES                         5
#define CRESTRICTIONS_DBSCHEMA_OBJECT_ACTIONS                  1
#define CRESTRICTIONS_DBSCHEMA_OBJECTS                         1
#define CRESTRICTIONS_DBSCHEMA_COLUMN_PRIVILEGES               6
#define CRESTRICTIONS_DBSCHEMA_TABLE_PRIVILEGES                5
#define CRESTRICTIONS_DBSCHEMA_USAGE_PRIVILEGES                6
#define CRESTRICTIONS_DBSCHEMA_PROCEDURES                      4
#define CRESTRICTIONS_DBSCHEMA_SCHEMATA                        3
#define CRESTRICTIONS_DBSCHEMA_SQL_LANGUAGES                   0
#define CRESTRICTIONS_DBSCHEMA_STATISTICS                      3
#define CRESTRICTIONS_DBSCHEMA_TABLES                          4
#define CRESTRICTIONS_DBSCHEMA_TRANSLATIONS                    3
#define CRESTRICTIONS_DBSCHEMA_PROVIDER_TYPES                  2
#define CRESTRICTIONS_DBSCHEMA_VIEWS                           3
#define CRESTRICTIONS_DBSCHEMA_VIEW_COLUMN_USAGE               3
#define CRESTRICTIONS_DBSCHEMA_VIEW_TABLE_USAGE                3
#define CRESTRICTIONS_DBSCHEMA_PROCEDURE_PARAMETERS            4
#define CRESTRICTIONS_DBSCHEMA_FOREIGN_KEYS                    6
#define CRESTRICTIONS_DBSCHEMA_PRIMARY_KEYS                    3
#define CRESTRICTIONS_DBSCHEMA_PROCEDURE_COLUMNS               4
//@@@+ V2.0
#if( OLEDBVER >= 0x0200 )
#define CRESTRICTIONS_DBSCHEMA_TABLES_INFO                     4
#define CRESTRICTIONS_MDSCHEMA_CUBES                           3
#define CRESTRICTIONS_MDSCHEMA_DIMENSIONS                      5
#define CRESTRICTIONS_MDSCHEMA_HIERARCHIES                     6
#define CRESTRICTIONS_MDSCHEMA_LEVELS                          7
#define CRESTRICTIONS_MDSCHEMA_MEASURES                        5
#define CRESTRICTIONS_MDSCHEMA_PROPERTIES                      9
#define CRESTRICTIONS_MDSCHEMA_MEMBERS                         12
#endif // OLEDBVER >= 0x0200
//@@@- V2.0

EXTERN_C const IID IID_IDBSchemaRowset;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a7b-2a1c-11ce-ade5-00aa0044773d")
    IDBSchemaRowset : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetRowset( 
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ REFGUID rguidSchema,
            /* [in] */ ULONG cRestrictions,
            /* [size_is][in] */ const VARIANT __RPC_FAR rgRestrictions[  ],
            /* [in] */ REFIID riid,
            /* [in] */ ULONG cPropertySets,
            /* [size_is][unique][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ],
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetSchemas( 
            /* [out][in] */ ULONG __RPC_FAR *pcSchemas,
            /* [size_is][size_is][out] */ GUID __RPC_FAR *__RPC_FAR *prgSchemas,
            /* [size_is][size_is][out] */ ULONG __RPC_FAR *__RPC_FAR *prgRestrictionSupport) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDBSchemaRowsetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDBSchemaRowset __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDBSchemaRowset __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDBSchemaRowset __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRowset )( 
            IDBSchemaRowset __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ REFGUID rguidSchema,
            /* [in] */ ULONG cRestrictions,
            /* [size_is][in] */ const VARIANT __RPC_FAR rgRestrictions[  ],
            /* [in] */ REFIID riid,
            /* [in] */ ULONG cPropertySets,
            /* [size_is][unique][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ],
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSchemas )( 
            IDBSchemaRowset __RPC_FAR * This,
            /* [out][in] */ ULONG __RPC_FAR *pcSchemas,
            /* [size_is][size_is][out] */ GUID __RPC_FAR *__RPC_FAR *prgSchemas,
            /* [size_is][size_is][out] */ ULONG __RPC_FAR *__RPC_FAR *prgRestrictionSupport);
        
        END_INTERFACE
    } IDBSchemaRowsetVtbl;

    interface IDBSchemaRowset
    {
        CONST_VTBL struct IDBSchemaRowsetVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDBSchemaRowset_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDBSchemaRowset_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDBSchemaRowset_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDBSchemaRowset_GetRowset(This,pUnkOuter,rguidSchema,cRestrictions,rgRestrictions,riid,cPropertySets,rgPropertySets,ppRowset)	\
    (This)->lpVtbl -> GetRowset(This,pUnkOuter,rguidSchema,cRestrictions,rgRestrictions,riid,cPropertySets,rgPropertySets,ppRowset)

#define IDBSchemaRowset_GetSchemas(This,pcSchemas,prgSchemas,prgRestrictionSupport)	\
    (This)->lpVtbl -> GetSchemas(This,pcSchemas,prgSchemas,prgRestrictionSupport)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBSchemaRowset_RemoteGetRowset_Proxy( 
    IDBSchemaRowset __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ REFGUID rguidSchema,
    /* [in] */ ULONG cRestrictions,
    /* [size_is][unique][in] */ const VARIANT __RPC_FAR *rgRestrictions,
    /* [in] */ REFIID riid,
    /* [in] */ ULONG cPropertySets,
    /* [size_is][unique][in] */ DBPROPSET __RPC_FAR *rgPropertySets,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset,
    /* [in] */ ULONG cTotalProps,
    /* [size_is][out] */ DBPROPSTATUS __RPC_FAR *rgPropStatus,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IDBSchemaRowset_RemoteGetRowset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBSchemaRowset_RemoteGetSchemas_Proxy( 
    IDBSchemaRowset __RPC_FAR * This,
    /* [out][in] */ ULONG __RPC_FAR *pcSchemas,
    /* [size_is][size_is][out] */ GUID __RPC_FAR *__RPC_FAR *prgSchemas,
    /* [size_is][size_is][out] */ ULONG __RPC_FAR *__RPC_FAR *prgRestrictionSupport,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IDBSchemaRowset_RemoteGetSchemas_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDBSchemaRowset_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_oledb_0132
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


//@@@+ V2.5
#if( OLEDBVER >= 0x0250 )


extern RPC_IF_HANDLE __MIDL_itf_oledb_0132_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_oledb_0132_v0_0_s_ifspec;

#ifndef __IProvideMoniker_INTERFACE_DEFINED__
#define __IProvideMoniker_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IProvideMoniker
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object][local] */ 



EXTERN_C const IID IID_IProvideMoniker;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a4d-2a1c-11ce-ade5-00aa0044773d")
    IProvideMoniker : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetMoniker( 
            /* [out] */ IMoniker __RPC_FAR *__RPC_FAR *ppIMoniker) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IProvideMonikerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IProvideMoniker __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IProvideMoniker __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IProvideMoniker __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMoniker )( 
            IProvideMoniker __RPC_FAR * This,
            /* [out] */ IMoniker __RPC_FAR *__RPC_FAR *ppIMoniker);
        
        END_INTERFACE
    } IProvideMonikerVtbl;

    interface IProvideMoniker
    {
        CONST_VTBL struct IProvideMonikerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProvideMoniker_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IProvideMoniker_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IProvideMoniker_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IProvideMoniker_GetMoniker(This,ppIMoniker)	\
    (This)->lpVtbl -> GetMoniker(This,ppIMoniker)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IProvideMoniker_GetMoniker_Proxy( 
    IProvideMoniker __RPC_FAR * This,
    /* [out] */ IMoniker __RPC_FAR *__RPC_FAR *ppIMoniker);


void __RPC_STUB IProvideMoniker_GetMoniker_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IProvideMoniker_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_oledb_0133
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


#endif // OLEDBVER >= 0x0250
//@@@- V2.5
//@@@+ V2.0
#if( OLEDBVER >= 0x0200 )


extern RPC_IF_HANDLE __MIDL_itf_oledb_0133_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_oledb_0133_v0_0_s_ifspec;

#ifndef __IMDDataset_INTERFACE_DEFINED__
#define __IMDDataset_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMDDataset
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object][local] */ 



EXTERN_C const IID IID_IMDDataset;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("a07cccd1-8148-11d0-87bb-00c04fc33942")
    IMDDataset : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE FreeAxisInfo( 
            /* [in] */ ULONG cAxes,
            /* [size_is][in] */ MDAXISINFO __RPC_FAR *rgAxisInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAxisInfo( 
            /* [out][in] */ ULONG __RPC_FAR *pcAxes,
            /* [size_is][size_is][out] */ MDAXISINFO __RPC_FAR *__RPC_FAR *prgAxisInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAxisRowset( 
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ ULONG iAxis,
            /* [in] */ REFIID riid,
            /* [in] */ ULONG cPropertySets,
            /* [size_is][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ],
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCellData( 
            /* [in] */ HACCESSOR hAccessor,
            /* [in] */ ULONG ulStartCell,
            /* [in] */ ULONG ulEndCell,
            /* [out] */ void __RPC_FAR *pData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSpecification( 
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppSpecification) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMDDatasetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMDDataset __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMDDataset __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMDDataset __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FreeAxisInfo )( 
            IMDDataset __RPC_FAR * This,
            /* [in] */ ULONG cAxes,
            /* [size_is][in] */ MDAXISINFO __RPC_FAR *rgAxisInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAxisInfo )( 
            IMDDataset __RPC_FAR * This,
            /* [out][in] */ ULONG __RPC_FAR *pcAxes,
            /* [size_is][size_is][out] */ MDAXISINFO __RPC_FAR *__RPC_FAR *prgAxisInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAxisRowset )( 
            IMDDataset __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ ULONG iAxis,
            /* [in] */ REFIID riid,
            /* [in] */ ULONG cPropertySets,
            /* [size_is][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ],
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCellData )( 
            IMDDataset __RPC_FAR * This,
            /* [in] */ HACCESSOR hAccessor,
            /* [in] */ ULONG ulStartCell,
            /* [in] */ ULONG ulEndCell,
            /* [out] */ void __RPC_FAR *pData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSpecification )( 
            IMDDataset __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppSpecification);
        
        END_INTERFACE
    } IMDDatasetVtbl;

    interface IMDDataset
    {
        CONST_VTBL struct IMDDatasetVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMDDataset_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMDDataset_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMDDataset_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMDDataset_FreeAxisInfo(This,cAxes,rgAxisInfo)	\
    (This)->lpVtbl -> FreeAxisInfo(This,cAxes,rgAxisInfo)

#define IMDDataset_GetAxisInfo(This,pcAxes,prgAxisInfo)	\
    (This)->lpVtbl -> GetAxisInfo(This,pcAxes,prgAxisInfo)

#define IMDDataset_GetAxisRowset(This,pUnkOuter,iAxis,riid,cPropertySets,rgPropertySets,ppRowset)	\
    (This)->lpVtbl -> GetAxisRowset(This,pUnkOuter,iAxis,riid,cPropertySets,rgPropertySets,ppRowset)

#define IMDDataset_GetCellData(This,hAccessor,ulStartCell,ulEndCell,pData)	\
    (This)->lpVtbl -> GetCellData(This,hAccessor,ulStartCell,ulEndCell,pData)

#define IMDDataset_GetSpecification(This,riid,ppSpecification)	\
    (This)->lpVtbl -> GetSpecification(This,riid,ppSpecification)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMDDataset_FreeAxisInfo_Proxy( 
    IMDDataset __RPC_FAR * This,
    /* [in] */ ULONG cAxes,
    /* [size_is][in] */ MDAXISINFO __RPC_FAR *rgAxisInfo);


void __RPC_STUB IMDDataset_FreeAxisInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMDDataset_GetAxisInfo_Proxy( 
    IMDDataset __RPC_FAR * This,
    /* [out][in] */ ULONG __RPC_FAR *pcAxes,
    /* [size_is][size_is][out] */ MDAXISINFO __RPC_FAR *__RPC_FAR *prgAxisInfo);


void __RPC_STUB IMDDataset_GetAxisInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMDDataset_GetAxisRowset_Proxy( 
    IMDDataset __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ ULONG iAxis,
    /* [in] */ REFIID riid,
    /* [in] */ ULONG cPropertySets,
    /* [size_is][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ],
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset);


void __RPC_STUB IMDDataset_GetAxisRowset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMDDataset_GetCellData_Proxy( 
    IMDDataset __RPC_FAR * This,
    /* [in] */ HACCESSOR hAccessor,
    /* [in] */ ULONG ulStartCell,
    /* [in] */ ULONG ulEndCell,
    /* [out] */ void __RPC_FAR *pData);


void __RPC_STUB IMDDataset_GetCellData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMDDataset_GetSpecification_Proxy( 
    IMDDataset __RPC_FAR * This,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppSpecification);


void __RPC_STUB IMDDataset_GetSpecification_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMDDataset_INTERFACE_DEFINED__ */


#ifndef __IMDFind_INTERFACE_DEFINED__
#define __IMDFind_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMDFind
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object][local] */ 



EXTERN_C const IID IID_IMDFind;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("a07cccd2-8148-11d0-87bb-00c04fc33942")
    IMDFind : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE FindCell( 
            /* [in] */ ULONG ulStartingOrdinal,
            /* [in] */ ULONG cMembers,
            /* [size_is][in] */ LPCOLESTR __RPC_FAR *rgpwszMember,
            /* [out] */ ULONG __RPC_FAR *pulCellOrdinal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FindTuple( 
            /* [in] */ ULONG ulAxisIdentifier,
            /* [in] */ ULONG ulStartingOrdinal,
            /* [in] */ ULONG cMembers,
            /* [size_is][in] */ LPCOLESTR __RPC_FAR *rgpwszMember,
            /* [out] */ ULONG __RPC_FAR *pulTupleOrdinal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMDFindVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMDFind __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMDFind __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMDFind __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindCell )( 
            IMDFind __RPC_FAR * This,
            /* [in] */ ULONG ulStartingOrdinal,
            /* [in] */ ULONG cMembers,
            /* [size_is][in] */ LPCOLESTR __RPC_FAR *rgpwszMember,
            /* [out] */ ULONG __RPC_FAR *pulCellOrdinal);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindTuple )( 
            IMDFind __RPC_FAR * This,
            /* [in] */ ULONG ulAxisIdentifier,
            /* [in] */ ULONG ulStartingOrdinal,
            /* [in] */ ULONG cMembers,
            /* [size_is][in] */ LPCOLESTR __RPC_FAR *rgpwszMember,
            /* [out] */ ULONG __RPC_FAR *pulTupleOrdinal);
        
        END_INTERFACE
    } IMDFindVtbl;

    interface IMDFind
    {
        CONST_VTBL struct IMDFindVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMDFind_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMDFind_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMDFind_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMDFind_FindCell(This,ulStartingOrdinal,cMembers,rgpwszMember,pulCellOrdinal)	\
    (This)->lpVtbl -> FindCell(This,ulStartingOrdinal,cMembers,rgpwszMember,pulCellOrdinal)

#define IMDFind_FindTuple(This,ulAxisIdentifier,ulStartingOrdinal,cMembers,rgpwszMember,pulTupleOrdinal)	\
    (This)->lpVtbl -> FindTuple(This,ulAxisIdentifier,ulStartingOrdinal,cMembers,rgpwszMember,pulTupleOrdinal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMDFind_FindCell_Proxy( 
    IMDFind __RPC_FAR * This,
    /* [in] */ ULONG ulStartingOrdinal,
    /* [in] */ ULONG cMembers,
    /* [size_is][in] */ LPCOLESTR __RPC_FAR *rgpwszMember,
    /* [out] */ ULONG __RPC_FAR *pulCellOrdinal);


void __RPC_STUB IMDFind_FindCell_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMDFind_FindTuple_Proxy( 
    IMDFind __RPC_FAR * This,
    /* [in] */ ULONG ulAxisIdentifier,
    /* [in] */ ULONG ulStartingOrdinal,
    /* [in] */ ULONG cMembers,
    /* [size_is][in] */ LPCOLESTR __RPC_FAR *rgpwszMember,
    /* [out] */ ULONG __RPC_FAR *pulTupleOrdinal);


void __RPC_STUB IMDFind_FindTuple_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMDFind_INTERFACE_DEFINED__ */


#ifndef __IMDRangeRowset_INTERFACE_DEFINED__
#define __IMDRangeRowset_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMDRangeRowset
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object][local] */ 



EXTERN_C const IID IID_IMDRangeRowset;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733aa0-2a1c-11ce-ade5-00aa0044773d")
    IMDRangeRowset : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetRangeRowset( 
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ ULONG ulStartCell,
            /* [in] */ ULONG ulEndCell,
            /* [in] */ REFIID riid,
            /* [in] */ ULONG cPropertySets,
            /* [size_is][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ],
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMDRangeRowsetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMDRangeRowset __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMDRangeRowset __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMDRangeRowset __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRangeRowset )( 
            IMDRangeRowset __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ ULONG ulStartCell,
            /* [in] */ ULONG ulEndCell,
            /* [in] */ REFIID riid,
            /* [in] */ ULONG cPropertySets,
            /* [size_is][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ],
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset);
        
        END_INTERFACE
    } IMDRangeRowsetVtbl;

    interface IMDRangeRowset
    {
        CONST_VTBL struct IMDRangeRowsetVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMDRangeRowset_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMDRangeRowset_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMDRangeRowset_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMDRangeRowset_GetRangeRowset(This,pUnkOuter,ulStartCell,ulEndCell,riid,cPropertySets,rgPropertySets,ppRowset)	\
    (This)->lpVtbl -> GetRangeRowset(This,pUnkOuter,ulStartCell,ulEndCell,riid,cPropertySets,rgPropertySets,ppRowset)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMDRangeRowset_GetRangeRowset_Proxy( 
    IMDRangeRowset __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ ULONG ulStartCell,
    /* [in] */ ULONG ulEndCell,
    /* [in] */ REFIID riid,
    /* [in] */ ULONG cPropertySets,
    /* [size_is][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ],
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset);


void __RPC_STUB IMDRangeRowset_GetRangeRowset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMDRangeRowset_INTERFACE_DEFINED__ */


#ifndef __IAlterTable_INTERFACE_DEFINED__
#define __IAlterTable_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAlterTable
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object][local] */ 



EXTERN_C const IID IID_IAlterTable;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733aa5-2a1c-11ce-ade5-00aa0044773d")
    IAlterTable : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE AlterColumn( 
            /* [in] */ DBID __RPC_FAR *pTableId,
            /* [in] */ DBID __RPC_FAR *pColumnId,
            /* [in] */ DBCOLUMNDESCFLAGS ColumnDescFlags,
            /* [in] */ DBCOLUMNDESC __RPC_FAR *pColumnDesc) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AlterTable( 
            /* [in] */ DBID __RPC_FAR *pTableId,
            /* [in] */ DBID __RPC_FAR *pNewTableId,
            /* [in] */ ULONG cPropertySets,
            /* [size_is][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ]) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAlterTableVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAlterTable __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAlterTable __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAlterTable __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AlterColumn )( 
            IAlterTable __RPC_FAR * This,
            /* [in] */ DBID __RPC_FAR *pTableId,
            /* [in] */ DBID __RPC_FAR *pColumnId,
            /* [in] */ DBCOLUMNDESCFLAGS ColumnDescFlags,
            /* [in] */ DBCOLUMNDESC __RPC_FAR *pColumnDesc);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AlterTable )( 
            IAlterTable __RPC_FAR * This,
            /* [in] */ DBID __RPC_FAR *pTableId,
            /* [in] */ DBID __RPC_FAR *pNewTableId,
            /* [in] */ ULONG cPropertySets,
            /* [size_is][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ]);
        
        END_INTERFACE
    } IAlterTableVtbl;

    interface IAlterTable
    {
        CONST_VTBL struct IAlterTableVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAlterTable_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAlterTable_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAlterTable_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAlterTable_AlterColumn(This,pTableId,pColumnId,ColumnDescFlags,pColumnDesc)	\
    (This)->lpVtbl -> AlterColumn(This,pTableId,pColumnId,ColumnDescFlags,pColumnDesc)

#define IAlterTable_AlterTable(This,pTableId,pNewTableId,cPropertySets,rgPropertySets)	\
    (This)->lpVtbl -> AlterTable(This,pTableId,pNewTableId,cPropertySets,rgPropertySets)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAlterTable_AlterColumn_Proxy( 
    IAlterTable __RPC_FAR * This,
    /* [in] */ DBID __RPC_FAR *pTableId,
    /* [in] */ DBID __RPC_FAR *pColumnId,
    /* [in] */ DBCOLUMNDESCFLAGS ColumnDescFlags,
    /* [in] */ DBCOLUMNDESC __RPC_FAR *pColumnDesc);


void __RPC_STUB IAlterTable_AlterColumn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAlterTable_AlterTable_Proxy( 
    IAlterTable __RPC_FAR * This,
    /* [in] */ DBID __RPC_FAR *pTableId,
    /* [in] */ DBID __RPC_FAR *pNewTableId,
    /* [in] */ ULONG cPropertySets,
    /* [size_is][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ]);


void __RPC_STUB IAlterTable_AlterTable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAlterTable_INTERFACE_DEFINED__ */


#ifndef __IAlterIndex_INTERFACE_DEFINED__
#define __IAlterIndex_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAlterIndex
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object][local] */ 



EXTERN_C const IID IID_IAlterIndex;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733aa6-2a1c-11ce-ade5-00aa0044773d")
    IAlterIndex : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE AlterIndex( 
            /* [in] */ DBID __RPC_FAR *pTableId,
            /* [in] */ DBID __RPC_FAR *pIndexId,
            /* [in] */ DBID __RPC_FAR *pNewIndexId,
            /* [in] */ ULONG cPropertySets,
            /* [size_is][out][in] */ DBPROPSET __RPC_FAR rgPropertySet[  ]) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAlterIndexVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAlterIndex __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAlterIndex __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAlterIndex __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AlterIndex )( 
            IAlterIndex __RPC_FAR * This,
            /* [in] */ DBID __RPC_FAR *pTableId,
            /* [in] */ DBID __RPC_FAR *pIndexId,
            /* [in] */ DBID __RPC_FAR *pNewIndexId,
            /* [in] */ ULONG cPropertySets,
            /* [size_is][out][in] */ DBPROPSET __RPC_FAR rgPropertySet[  ]);
        
        END_INTERFACE
    } IAlterIndexVtbl;

    interface IAlterIndex
    {
        CONST_VTBL struct IAlterIndexVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAlterIndex_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAlterIndex_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAlterIndex_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAlterIndex_AlterIndex(This,pTableId,pIndexId,pNewIndexId,cPropertySets,rgPropertySet)	\
    (This)->lpVtbl -> AlterIndex(This,pTableId,pIndexId,pNewIndexId,cPropertySets,rgPropertySet)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAlterIndex_AlterIndex_Proxy( 
    IAlterIndex __RPC_FAR * This,
    /* [in] */ DBID __RPC_FAR *pTableId,
    /* [in] */ DBID __RPC_FAR *pIndexId,
    /* [in] */ DBID __RPC_FAR *pNewIndexId,
    /* [in] */ ULONG cPropertySets,
    /* [size_is][out][in] */ DBPROPSET __RPC_FAR rgPropertySet[  ]);


void __RPC_STUB IAlterIndex_AlterIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAlterIndex_INTERFACE_DEFINED__ */


#ifndef __IRowsetChapterMember_INTERFACE_DEFINED__
#define __IRowsetChapterMember_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRowsetChapterMember
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object][local] */ 



EXTERN_C const IID IID_IRowsetChapterMember;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733aa8-2a1c-11ce-ade5-00aa0044773d")
    IRowsetChapterMember : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE IsRowInChapter( 
            /* [in] */ HCHAPTER hChapter,
            /* [in] */ HROW hRow) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRowsetChapterMemberVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRowsetChapterMember __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRowsetChapterMember __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRowsetChapterMember __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsRowInChapter )( 
            IRowsetChapterMember __RPC_FAR * This,
            /* [in] */ HCHAPTER hChapter,
            /* [in] */ HROW hRow);
        
        END_INTERFACE
    } IRowsetChapterMemberVtbl;

    interface IRowsetChapterMember
    {
        CONST_VTBL struct IRowsetChapterMemberVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRowsetChapterMember_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRowsetChapterMember_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRowsetChapterMember_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRowsetChapterMember_IsRowInChapter(This,hChapter,hRow)	\
    (This)->lpVtbl -> IsRowInChapter(This,hChapter,hRow)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRowsetChapterMember_IsRowInChapter_Proxy( 
    IRowsetChapterMember __RPC_FAR * This,
    /* [in] */ HCHAPTER hChapter,
    /* [in] */ HROW hRow);


void __RPC_STUB IRowsetChapterMember_IsRowInChapter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRowsetChapterMember_INTERFACE_DEFINED__ */


#ifndef __ICommandPersist_INTERFACE_DEFINED__
#define __ICommandPersist_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ICommandPersist
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object][local] */ 


typedef DWORD DBCOMMANDPERSISTFLAG;


enum DBCOMMANDPERSISTFLAGENUM
    {	DBCOMMANDPERSISTFLAG_NOSAVE	= 0x1
    };

EXTERN_C const IID IID_ICommandPersist;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733aa7-2a1c-11ce-ade5-00aa0044773d")
    ICommandPersist : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE DeleteCommand( 
            /* [in] */ DBID __RPC_FAR *pCommandID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentCommand( 
            /* [out] */ DBID __RPC_FAR *__RPC_FAR *ppCommandID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LoadCommand( 
            /* [in] */ DBID __RPC_FAR *pCommandID,
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SaveCommand( 
            /* [in] */ DBID __RPC_FAR *pCommandID,
            /* [in] */ DWORD dwFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICommandPersistVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICommandPersist __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICommandPersist __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICommandPersist __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteCommand )( 
            ICommandPersist __RPC_FAR * This,
            /* [in] */ DBID __RPC_FAR *pCommandID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCurrentCommand )( 
            ICommandPersist __RPC_FAR * This,
            /* [out] */ DBID __RPC_FAR *__RPC_FAR *ppCommandID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadCommand )( 
            ICommandPersist __RPC_FAR * This,
            /* [in] */ DBID __RPC_FAR *pCommandID,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SaveCommand )( 
            ICommandPersist __RPC_FAR * This,
            /* [in] */ DBID __RPC_FAR *pCommandID,
            /* [in] */ DWORD dwFlags);
        
        END_INTERFACE
    } ICommandPersistVtbl;

    interface ICommandPersist
    {
        CONST_VTBL struct ICommandPersistVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICommandPersist_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICommandPersist_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICommandPersist_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICommandPersist_DeleteCommand(This,pCommandID)	\
    (This)->lpVtbl -> DeleteCommand(This,pCommandID)

#define ICommandPersist_GetCurrentCommand(This,ppCommandID)	\
    (This)->lpVtbl -> GetCurrentCommand(This,ppCommandID)

#define ICommandPersist_LoadCommand(This,pCommandID,dwFlags)	\
    (This)->lpVtbl -> LoadCommand(This,pCommandID,dwFlags)

#define ICommandPersist_SaveCommand(This,pCommandID,dwFlags)	\
    (This)->lpVtbl -> SaveCommand(This,pCommandID,dwFlags)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICommandPersist_DeleteCommand_Proxy( 
    ICommandPersist __RPC_FAR * This,
    /* [in] */ DBID __RPC_FAR *pCommandID);


void __RPC_STUB ICommandPersist_DeleteCommand_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICommandPersist_GetCurrentCommand_Proxy( 
    ICommandPersist __RPC_FAR * This,
    /* [out] */ DBID __RPC_FAR *__RPC_FAR *ppCommandID);


void __RPC_STUB ICommandPersist_GetCurrentCommand_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICommandPersist_LoadCommand_Proxy( 
    ICommandPersist __RPC_FAR * This,
    /* [in] */ DBID __RPC_FAR *pCommandID,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB ICommandPersist_LoadCommand_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICommandPersist_SaveCommand_Proxy( 
    ICommandPersist __RPC_FAR * This,
    /* [in] */ DBID __RPC_FAR *pCommandID,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB ICommandPersist_SaveCommand_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICommandPersist_INTERFACE_DEFINED__ */


#ifndef __IRowsetRefresh_INTERFACE_DEFINED__
#define __IRowsetRefresh_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRowsetRefresh
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object][local] */ 



EXTERN_C const IID IID_IRowsetRefresh;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733aa9-2a1c-11ce-ade5-00aa0044773d")
    IRowsetRefresh : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE RefreshVisibleData( 
            /* [in] */ HCHAPTER hChapter,
            /* [in] */ ULONG cRows,
            /* [in] */ const HROW __RPC_FAR rghRows[  ],
            /* [in] */ BOOL fOverWrite,
            /* [out] */ ULONG __RPC_FAR *pcRowsRefreshed,
            /* [out] */ HROW __RPC_FAR *__RPC_FAR *prghRowsRefreshed,
            /* [out] */ DBROWSTATUS __RPC_FAR *__RPC_FAR *prgRowStatus) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLastVisibleData( 
            /* [in] */ HROW hRow,
            /* [in] */ HACCESSOR hAccessor,
            /* [out] */ void __RPC_FAR *pData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRowsetRefreshVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRowsetRefresh __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRowsetRefresh __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRowsetRefresh __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RefreshVisibleData )( 
            IRowsetRefresh __RPC_FAR * This,
            /* [in] */ HCHAPTER hChapter,
            /* [in] */ ULONG cRows,
            /* [in] */ const HROW __RPC_FAR rghRows[  ],
            /* [in] */ BOOL fOverWrite,
            /* [out] */ ULONG __RPC_FAR *pcRowsRefreshed,
            /* [out] */ HROW __RPC_FAR *__RPC_FAR *prghRowsRefreshed,
            /* [out] */ DBROWSTATUS __RPC_FAR *__RPC_FAR *prgRowStatus);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLastVisibleData )( 
            IRowsetRefresh __RPC_FAR * This,
            /* [in] */ HROW hRow,
            /* [in] */ HACCESSOR hAccessor,
            /* [out] */ void __RPC_FAR *pData);
        
        END_INTERFACE
    } IRowsetRefreshVtbl;

    interface IRowsetRefresh
    {
        CONST_VTBL struct IRowsetRefreshVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRowsetRefresh_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRowsetRefresh_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRowsetRefresh_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRowsetRefresh_RefreshVisibleData(This,hChapter,cRows,rghRows,fOverWrite,pcRowsRefreshed,prghRowsRefreshed,prgRowStatus)	\
    (This)->lpVtbl -> RefreshVisibleData(This,hChapter,cRows,rghRows,fOverWrite,pcRowsRefreshed,prghRowsRefreshed,prgRowStatus)

#define IRowsetRefresh_GetLastVisibleData(This,hRow,hAccessor,pData)	\
    (This)->lpVtbl -> GetLastVisibleData(This,hRow,hAccessor,pData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRowsetRefresh_RefreshVisibleData_Proxy( 
    IRowsetRefresh __RPC_FAR * This,
    /* [in] */ HCHAPTER hChapter,
    /* [in] */ ULONG cRows,
    /* [in] */ const HROW __RPC_FAR rghRows[  ],
    /* [in] */ BOOL fOverWrite,
    /* [out] */ ULONG __RPC_FAR *pcRowsRefreshed,
    /* [out] */ HROW __RPC_FAR *__RPC_FAR *prghRowsRefreshed,
    /* [out] */ DBROWSTATUS __RPC_FAR *__RPC_FAR *prgRowStatus);


void __RPC_STUB IRowsetRefresh_RefreshVisibleData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRowsetRefresh_GetLastVisibleData_Proxy( 
    IRowsetRefresh __RPC_FAR * This,
    /* [in] */ HROW hRow,
    /* [in] */ HACCESSOR hAccessor,
    /* [out] */ void __RPC_FAR *pData);


void __RPC_STUB IRowsetRefresh_GetLastVisibleData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRowsetRefresh_INTERFACE_DEFINED__ */


#ifndef __IParentRowset_INTERFACE_DEFINED__
#define __IParentRowset_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IParentRowset
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object][local] */ 



EXTERN_C const IID IID_IParentRowset;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733aaa-2a1c-11ce-ade5-00aa0044773d")
    IParentRowset : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetChildRowset( 
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ ULONG iOrdinal,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IParentRowsetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IParentRowset __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IParentRowset __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IParentRowset __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetChildRowset )( 
            IParentRowset __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ ULONG iOrdinal,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset);
        
        END_INTERFACE
    } IParentRowsetVtbl;

    interface IParentRowset
    {
        CONST_VTBL struct IParentRowsetVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IParentRowset_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IParentRowset_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IParentRowset_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IParentRowset_GetChildRowset(This,pUnkOuter,iOrdinal,riid,ppRowset)	\
    (This)->lpVtbl -> GetChildRowset(This,pUnkOuter,iOrdinal,riid,ppRowset)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IParentRowset_GetChildRowset_Proxy( 
    IParentRowset __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ ULONG iOrdinal,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset);


void __RPC_STUB IParentRowset_GetChildRowset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IParentRowset_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_oledb_0142
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


#endif // OLEDBVER >= 0x0200
//@@@- V2.0


extern RPC_IF_HANDLE __MIDL_itf_oledb_0142_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_oledb_0142_v0_0_s_ifspec;

#ifndef __IErrorRecords_INTERFACE_DEFINED__
#define __IErrorRecords_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IErrorRecords
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 


#define IDENTIFIER_SDK_MASK	0xF0000000
#define IDENTIFIER_SDK_ERROR	0x10000000
typedef struct  tagERRORINFO
    {
    HRESULT hrError;
    DWORD dwMinor;
    CLSID clsid;
    IID iid;
    DISPID dispid;
    }	ERRORINFO;


EXTERN_C const IID IID_IErrorRecords;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a67-2a1c-11ce-ade5-00aa0044773d")
    IErrorRecords : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE AddErrorRecord( 
            /* [in] */ ERRORINFO __RPC_FAR *pErrorInfo,
            /* [in] */ DWORD dwLookupID,
            /* [in] */ DISPPARAMS __RPC_FAR *pdispparams,
            /* [in] */ IUnknown __RPC_FAR *punkCustomError,
            /* [in] */ DWORD dwDynamicErrorID) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetBasicErrorInfo( 
            /* [in] */ ULONG ulRecordNum,
            /* [out] */ ERRORINFO __RPC_FAR *pErrorInfo) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetCustomErrorObject( 
            /* [in] */ ULONG ulRecordNum,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppObject) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetErrorInfo( 
            /* [in] */ ULONG ulRecordNum,
            /* [in] */ LCID lcid,
            /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfo) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetErrorParameters( 
            /* [in] */ ULONG ulRecordNum,
            /* [out] */ DISPPARAMS __RPC_FAR *pdispparams) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetRecordCount( 
            /* [out] */ ULONG __RPC_FAR *pcRecords) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IErrorRecordsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IErrorRecords __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IErrorRecords __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IErrorRecords __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddErrorRecord )( 
            IErrorRecords __RPC_FAR * This,
            /* [in] */ ERRORINFO __RPC_FAR *pErrorInfo,
            /* [in] */ DWORD dwLookupID,
            /* [in] */ DISPPARAMS __RPC_FAR *pdispparams,
            /* [in] */ IUnknown __RPC_FAR *punkCustomError,
            /* [in] */ DWORD dwDynamicErrorID);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBasicErrorInfo )( 
            IErrorRecords __RPC_FAR * This,
            /* [in] */ ULONG ulRecordNum,
            /* [out] */ ERRORINFO __RPC_FAR *pErrorInfo);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCustomErrorObject )( 
            IErrorRecords __RPC_FAR * This,
            /* [in] */ ULONG ulRecordNum,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppObject);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetErrorInfo )( 
            IErrorRecords __RPC_FAR * This,
            /* [in] */ ULONG ulRecordNum,
            /* [in] */ LCID lcid,
            /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfo);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetErrorParameters )( 
            IErrorRecords __RPC_FAR * This,
            /* [in] */ ULONG ulRecordNum,
            /* [out] */ DISPPARAMS __RPC_FAR *pdispparams);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRecordCount )( 
            IErrorRecords __RPC_FAR * This,
            /* [out] */ ULONG __RPC_FAR *pcRecords);
        
        END_INTERFACE
    } IErrorRecordsVtbl;

    interface IErrorRecords
    {
        CONST_VTBL struct IErrorRecordsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IErrorRecords_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IErrorRecords_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IErrorRecords_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IErrorRecords_AddErrorRecord(This,pErrorInfo,dwLookupID,pdispparams,punkCustomError,dwDynamicErrorID)	\
    (This)->lpVtbl -> AddErrorRecord(This,pErrorInfo,dwLookupID,pdispparams,punkCustomError,dwDynamicErrorID)

#define IErrorRecords_GetBasicErrorInfo(This,ulRecordNum,pErrorInfo)	\
    (This)->lpVtbl -> GetBasicErrorInfo(This,ulRecordNum,pErrorInfo)

#define IErrorRecords_GetCustomErrorObject(This,ulRecordNum,riid,ppObject)	\
    (This)->lpVtbl -> GetCustomErrorObject(This,ulRecordNum,riid,ppObject)

#define IErrorRecords_GetErrorInfo(This,ulRecordNum,lcid,ppErrorInfo)	\
    (This)->lpVtbl -> GetErrorInfo(This,ulRecordNum,lcid,ppErrorInfo)

#define IErrorRecords_GetErrorParameters(This,ulRecordNum,pdispparams)	\
    (This)->lpVtbl -> GetErrorParameters(This,ulRecordNum,pdispparams)

#define IErrorRecords_GetRecordCount(This,pcRecords)	\
    (This)->lpVtbl -> GetRecordCount(This,pcRecords)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE IErrorRecords_RemoteAddErrorRecord_Proxy( 
    IErrorRecords __RPC_FAR * This,
    /* [in] */ ERRORINFO __RPC_FAR *pErrorInfo,
    /* [in] */ DWORD dwLookupID,
    /* [in] */ DISPPARAMS __RPC_FAR *pdispparams,
    /* [in] */ IUnknown __RPC_FAR *punkCustomError,
    /* [in] */ DWORD dwDynamicErrorID,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IErrorRecords_RemoteAddErrorRecord_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IErrorRecords_RemoteGetBasicErrorInfo_Proxy( 
    IErrorRecords __RPC_FAR * This,
    /* [in] */ ULONG ulRecordNum,
    /* [out] */ ERRORINFO __RPC_FAR *pErrorInfo,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IErrorRecords_RemoteGetBasicErrorInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IErrorRecords_RemoteGetCustomErrorObject_Proxy( 
    IErrorRecords __RPC_FAR * This,
    /* [in] */ ULONG ulRecordNum,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppObject,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IErrorRecords_RemoteGetCustomErrorObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IErrorRecords_RemoteGetErrorInfo_Proxy( 
    IErrorRecords __RPC_FAR * This,
    /* [in] */ ULONG ulRecordNum,
    /* [in] */ LCID lcid,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfo,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IErrorRecords_RemoteGetErrorInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IErrorRecords_RemoteGetErrorParameters_Proxy( 
    IErrorRecords __RPC_FAR * This,
    /* [in] */ ULONG ulRecordNum,
    /* [out] */ DISPPARAMS __RPC_FAR *pdispparams,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IErrorRecords_RemoteGetErrorParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IErrorRecords_RemoteGetRecordCount_Proxy( 
    IErrorRecords __RPC_FAR * This,
    /* [out] */ ULONG __RPC_FAR *pcRecords,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IErrorRecords_RemoteGetRecordCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IErrorRecords_INTERFACE_DEFINED__ */


#ifndef __IErrorLookup_INTERFACE_DEFINED__
#define __IErrorLookup_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IErrorLookup
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IErrorLookup;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a66-2a1c-11ce-ade5-00aa0044773d")
    IErrorLookup : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetErrorDescription( 
            /* [in] */ HRESULT hrError,
            /* [in] */ DWORD dwLookupID,
            /* [in] */ DISPPARAMS __RPC_FAR *pdispparams,
            /* [in] */ LCID lcid,
            /* [out] */ BSTR __RPC_FAR *pbstrSource,
            /* [out] */ BSTR __RPC_FAR *pbstrDescription) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetHelpInfo( 
            /* [in] */ HRESULT hrError,
            /* [in] */ DWORD dwLookupID,
            /* [in] */ LCID lcid,
            /* [out] */ BSTR __RPC_FAR *pbstrHelpFile,
            /* [out] */ DWORD __RPC_FAR *pdwHelpContext) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE ReleaseErrors( 
            /* [in] */ const DWORD dwDynamicErrorID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IErrorLookupVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IErrorLookup __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IErrorLookup __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IErrorLookup __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetErrorDescription )( 
            IErrorLookup __RPC_FAR * This,
            /* [in] */ HRESULT hrError,
            /* [in] */ DWORD dwLookupID,
            /* [in] */ DISPPARAMS __RPC_FAR *pdispparams,
            /* [in] */ LCID lcid,
            /* [out] */ BSTR __RPC_FAR *pbstrSource,
            /* [out] */ BSTR __RPC_FAR *pbstrDescription);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetHelpInfo )( 
            IErrorLookup __RPC_FAR * This,
            /* [in] */ HRESULT hrError,
            /* [in] */ DWORD dwLookupID,
            /* [in] */ LCID lcid,
            /* [out] */ BSTR __RPC_FAR *pbstrHelpFile,
            /* [out] */ DWORD __RPC_FAR *pdwHelpContext);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReleaseErrors )( 
            IErrorLookup __RPC_FAR * This,
            /* [in] */ const DWORD dwDynamicErrorID);
        
        END_INTERFACE
    } IErrorLookupVtbl;

    interface IErrorLookup
    {
        CONST_VTBL struct IErrorLookupVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IErrorLookup_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IErrorLookup_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IErrorLookup_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IErrorLookup_GetErrorDescription(This,hrError,dwLookupID,pdispparams,lcid,pbstrSource,pbstrDescription)	\
    (This)->lpVtbl -> GetErrorDescription(This,hrError,dwLookupID,pdispparams,lcid,pbstrSource,pbstrDescription)

#define IErrorLookup_GetHelpInfo(This,hrError,dwLookupID,lcid,pbstrHelpFile,pdwHelpContext)	\
    (This)->lpVtbl -> GetHelpInfo(This,hrError,dwLookupID,lcid,pbstrHelpFile,pdwHelpContext)

#define IErrorLookup_ReleaseErrors(This,dwDynamicErrorID)	\
    (This)->lpVtbl -> ReleaseErrors(This,dwDynamicErrorID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE IErrorLookup_RemoteGetErrorDescription_Proxy( 
    IErrorLookup __RPC_FAR * This,
    /* [in] */ HRESULT hrError,
    /* [in] */ DWORD dwLookupID,
    /* [in] */ DISPPARAMS __RPC_FAR *pdispparams,
    /* [in] */ LCID lcid,
    /* [out] */ BSTR __RPC_FAR *pbstrSource,
    /* [out] */ BSTR __RPC_FAR *pbstrDescription,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IErrorLookup_RemoteGetErrorDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IErrorLookup_RemoteGetHelpInfo_Proxy( 
    IErrorLookup __RPC_FAR * This,
    /* [in] */ HRESULT hrError,
    /* [in] */ DWORD dwLookupID,
    /* [in] */ LCID lcid,
    /* [out] */ BSTR __RPC_FAR *pbstrHelpFile,
    /* [out] */ DWORD __RPC_FAR *pdwHelpContext,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IErrorLookup_RemoteGetHelpInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IErrorLookup_RemoteReleaseErrors_Proxy( 
    IErrorLookup __RPC_FAR * This,
    /* [in] */ const DWORD dwDynamicErrorID,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IErrorLookup_RemoteReleaseErrors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IErrorLookup_INTERFACE_DEFINED__ */


#ifndef __ISQLErrorInfo_INTERFACE_DEFINED__
#define __ISQLErrorInfo_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ISQLErrorInfo
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_ISQLErrorInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a74-2a1c-11ce-ade5-00aa0044773d")
    ISQLErrorInfo : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetSQLInfo( 
            /* [out] */ BSTR __RPC_FAR *pbstrSQLState,
            /* [out] */ LONG __RPC_FAR *plNativeError) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISQLErrorInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISQLErrorInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISQLErrorInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISQLErrorInfo __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSQLInfo )( 
            ISQLErrorInfo __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pbstrSQLState,
            /* [out] */ LONG __RPC_FAR *plNativeError);
        
        END_INTERFACE
    } ISQLErrorInfoVtbl;

    interface ISQLErrorInfo
    {
        CONST_VTBL struct ISQLErrorInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISQLErrorInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISQLErrorInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISQLErrorInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISQLErrorInfo_GetSQLInfo(This,pbstrSQLState,plNativeError)	\
    (This)->lpVtbl -> GetSQLInfo(This,pbstrSQLState,plNativeError)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE ISQLErrorInfo_RemoteGetSQLInfo_Proxy( 
    ISQLErrorInfo __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pbstrSQLState,
    /* [out] */ LONG __RPC_FAR *plNativeError,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB ISQLErrorInfo_RemoteGetSQLInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISQLErrorInfo_INTERFACE_DEFINED__ */


#ifndef __IGetDataSource_INTERFACE_DEFINED__
#define __IGetDataSource_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IGetDataSource
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IGetDataSource;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a75-2a1c-11ce-ade5-00aa0044773d")
    IGetDataSource : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetDataSource( 
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppDataSource) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGetDataSourceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IGetDataSource __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IGetDataSource __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IGetDataSource __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDataSource )( 
            IGetDataSource __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppDataSource);
        
        END_INTERFACE
    } IGetDataSourceVtbl;

    interface IGetDataSource
    {
        CONST_VTBL struct IGetDataSourceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGetDataSource_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGetDataSource_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGetDataSource_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGetDataSource_GetDataSource(This,riid,ppDataSource)	\
    (This)->lpVtbl -> GetDataSource(This,riid,ppDataSource)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE IGetDataSource_RemoteGetDataSource_Proxy( 
    IGetDataSource __RPC_FAR * This,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppDataSource,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB IGetDataSource_RemoteGetDataSource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IGetDataSource_INTERFACE_DEFINED__ */


#ifndef __ITransactionLocal_INTERFACE_DEFINED__
#define __ITransactionLocal_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITransactionLocal
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_ITransactionLocal;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a5f-2a1c-11ce-ade5-00aa0044773d")
    ITransactionLocal : public ITransaction
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetOptionsObject( 
            /* [out] */ ITransactionOptions __RPC_FAR *__RPC_FAR *ppOptions) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StartTransaction( 
            /* [in] */ ISOLEVEL isoLevel,
            /* [in] */ ULONG isoFlags,
            /* [in] */ ITransactionOptions __RPC_FAR *pOtherOptions,
            /* [out] */ ULONG __RPC_FAR *pulTransactionLevel) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITransactionLocalVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITransactionLocal __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITransactionLocal __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITransactionLocal __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Commit )( 
            ITransactionLocal __RPC_FAR * This,
            /* [in] */ BOOL fRetaining,
            /* [in] */ DWORD grfTC,
            /* [in] */ DWORD grfRM);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Abort )( 
            ITransactionLocal __RPC_FAR * This,
            /* [unique][in] */ BOID __RPC_FAR *pboidReason,
            /* [in] */ BOOL fRetaining,
            /* [in] */ BOOL fAsync);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTransactionInfo )( 
            ITransactionLocal __RPC_FAR * This,
            /* [out] */ XACTTRANSINFO __RPC_FAR *pinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOptionsObject )( 
            ITransactionLocal __RPC_FAR * This,
            /* [out] */ ITransactionOptions __RPC_FAR *__RPC_FAR *ppOptions);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartTransaction )( 
            ITransactionLocal __RPC_FAR * This,
            /* [in] */ ISOLEVEL isoLevel,
            /* [in] */ ULONG isoFlags,
            /* [in] */ ITransactionOptions __RPC_FAR *pOtherOptions,
            /* [out] */ ULONG __RPC_FAR *pulTransactionLevel);
        
        END_INTERFACE
    } ITransactionLocalVtbl;

    interface ITransactionLocal
    {
        CONST_VTBL struct ITransactionLocalVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITransactionLocal_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITransactionLocal_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITransactionLocal_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITransactionLocal_Commit(This,fRetaining,grfTC,grfRM)	\
    (This)->lpVtbl -> Commit(This,fRetaining,grfTC,grfRM)

#define ITransactionLocal_Abort(This,pboidReason,fRetaining,fAsync)	\
    (This)->lpVtbl -> Abort(This,pboidReason,fRetaining,fAsync)

#define ITransactionLocal_GetTransactionInfo(This,pinfo)	\
    (This)->lpVtbl -> GetTransactionInfo(This,pinfo)


#define ITransactionLocal_GetOptionsObject(This,ppOptions)	\
    (This)->lpVtbl -> GetOptionsObject(This,ppOptions)

#define ITransactionLocal_StartTransaction(This,isoLevel,isoFlags,pOtherOptions,pulTransactionLevel)	\
    (This)->lpVtbl -> StartTransaction(This,isoLevel,isoFlags,pOtherOptions,pulTransactionLevel)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ITransactionLocal_GetOptionsObject_Proxy( 
    ITransactionLocal __RPC_FAR * This,
    /* [out] */ ITransactionOptions __RPC_FAR *__RPC_FAR *ppOptions);


void __RPC_STUB ITransactionLocal_GetOptionsObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITransactionLocal_StartTransaction_Proxy( 
    ITransactionLocal __RPC_FAR * This,
    /* [in] */ ISOLEVEL isoLevel,
    /* [in] */ ULONG isoFlags,
    /* [in] */ ITransactionOptions __RPC_FAR *pOtherOptions,
    /* [out] */ ULONG __RPC_FAR *pulTransactionLevel);


void __RPC_STUB ITransactionLocal_StartTransaction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITransactionLocal_INTERFACE_DEFINED__ */


#ifndef __ITransactionJoin_INTERFACE_DEFINED__
#define __ITransactionJoin_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITransactionJoin
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_ITransactionJoin;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a5e-2a1c-11ce-ade5-00aa0044773d")
    ITransactionJoin : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetOptionsObject( 
            /* [out] */ ITransactionOptions __RPC_FAR *__RPC_FAR *ppOptions) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE JoinTransaction( 
            /* [in] */ IUnknown __RPC_FAR *punkTransactionCoord,
            /* [in] */ ISOLEVEL isoLevel,
            /* [in] */ ULONG isoFlags,
            /* [in] */ ITransactionOptions __RPC_FAR *pOtherOptions) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITransactionJoinVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITransactionJoin __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITransactionJoin __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITransactionJoin __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOptionsObject )( 
            ITransactionJoin __RPC_FAR * This,
            /* [out] */ ITransactionOptions __RPC_FAR *__RPC_FAR *ppOptions);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *JoinTransaction )( 
            ITransactionJoin __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *punkTransactionCoord,
            /* [in] */ ISOLEVEL isoLevel,
            /* [in] */ ULONG isoFlags,
            /* [in] */ ITransactionOptions __RPC_FAR *pOtherOptions);
        
        END_INTERFACE
    } ITransactionJoinVtbl;

    interface ITransactionJoin
    {
        CONST_VTBL struct ITransactionJoinVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITransactionJoin_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITransactionJoin_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITransactionJoin_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITransactionJoin_GetOptionsObject(This,ppOptions)	\
    (This)->lpVtbl -> GetOptionsObject(This,ppOptions)

#define ITransactionJoin_JoinTransaction(This,punkTransactionCoord,isoLevel,isoFlags,pOtherOptions)	\
    (This)->lpVtbl -> JoinTransaction(This,punkTransactionCoord,isoLevel,isoFlags,pOtherOptions)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE ITransactionJoin_RemoteGetOptionsObject_Proxy( 
    ITransactionJoin __RPC_FAR * This,
    /* [out] */ ITransactionOptions __RPC_FAR *__RPC_FAR *ppOptions,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB ITransactionJoin_RemoteGetOptionsObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE ITransactionJoin_RemoteJoinTransaction_Proxy( 
    ITransactionJoin __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *punkTransactionCoord,
    /* [in] */ ISOLEVEL isoLevel,
    /* [in] */ ULONG isoFlags,
    /* [in] */ ITransactionOptions __RPC_FAR *pOtherOptions,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB ITransactionJoin_RemoteJoinTransaction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITransactionJoin_INTERFACE_DEFINED__ */


#ifndef __ITransactionObject_INTERFACE_DEFINED__
#define __ITransactionObject_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITransactionObject
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_ITransactionObject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733a60-2a1c-11ce-ade5-00aa0044773d")
    ITransactionObject : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetTransactionObject( 
            /* [in] */ ULONG ulTransactionLevel,
            /* [out] */ ITransaction __RPC_FAR *__RPC_FAR *ppTransactionObject) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITransactionObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITransactionObject __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITransactionObject __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITransactionObject __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTransactionObject )( 
            ITransactionObject __RPC_FAR * This,
            /* [in] */ ULONG ulTransactionLevel,
            /* [out] */ ITransaction __RPC_FAR *__RPC_FAR *ppTransactionObject);
        
        END_INTERFACE
    } ITransactionObjectVtbl;

    interface ITransactionObject
    {
        CONST_VTBL struct ITransactionObjectVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITransactionObject_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITransactionObject_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITransactionObject_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITransactionObject_GetTransactionObject(This,ulTransactionLevel,ppTransactionObject)	\
    (This)->lpVtbl -> GetTransactionObject(This,ulTransactionLevel,ppTransactionObject)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE ITransactionObject_RemoteGetTransactionObject_Proxy( 
    ITransactionObject __RPC_FAR * This,
    /* [in] */ ULONG ulTransactionLevel,
    /* [out] */ ITransaction __RPC_FAR *__RPC_FAR *ppTransactionObject,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);


void __RPC_STUB ITransactionObject_RemoteGetTransactionObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITransactionObject_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_oledb_0156
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


//@@@+ V2.1
#if( OLEDBVER >= 0x0210 )
#if 0  // to get around a MIDL limitation
typedef 
enum _TRUSTEE_TYPE
    {	TRUSTEE_IS_UNKNOWN	= 0,
	TRUSTEE_IS_USER	= TRUSTEE_IS_UNKNOWN + 1,
	TRUSTEE_IS_GROUP	= TRUSTEE_IS_USER + 1
    }	TRUSTEE_TYPE;

typedef 
enum _TRUSTEE_FORM
    {	TRUSTEE_IS_SID	= 0,
	TRUSTEE_IS_NAME	= TRUSTEE_IS_SID + 1
    }	TRUSTEE_FORM;

typedef 
enum _MULTIPLE_TRUSTEE_OPERATION
    {	NO_MULTIPLE_TRUSTEE	= 0,
	TRUSTEE_IS_IMPERSONATE	= NO_MULTIPLE_TRUSTEE + 1
    }	MULTIPLE_TRUSTEE_OPERATION;

typedef struct _TRUSTEE_A __RPC_FAR *PTRUSTEE_A;

typedef struct _TRUSTEE_W __RPC_FAR *PTRUSTEE_W;

typedef struct  _TRUSTEE_W
    {
    PTRUSTEE_W pMultipleTrustee;
    MULTIPLE_TRUSTEE_OPERATION MultipleTrusteeOperation;
    TRUSTEE_FORM TrusteeForm;
    TRUSTEE_TYPE TrusteeType;
    LPWSTR ptstrName;
    }	TRUSTEE_W;

typedef struct  _TRUSTEE_A
    {
    PTRUSTEE_A pMultipleTrustee;
    MULTIPLE_TRUSTEE_OPERATION MultipleTrusteeOperation;
    TRUSTEE_FORM TrusteeForm;
    TRUSTEE_TYPE TrusteeType;
    LPSTR ptstrName;
    }	TRUSTEE_A;

typedef 
enum _ACCESS_MODE
    {	NOT_USED_ACCESS	= 0,
	GRANT_ACCESS	= NOT_USED_ACCESS + 1,
	SET_ACCESS	= GRANT_ACCESS + 1,
	DENY_ACCESS	= SET_ACCESS + 1,
	REVOKE_ACCESS	= DENY_ACCESS + 1,
	SET_AUDIT_SUCCESS	= REVOKE_ACCESS + 1,
	SET_AUDIT_FAILURE	= SET_AUDIT_SUCCESS + 1
    }	ACCESS_MODE;

typedef 
enum _SE_OBJECT_TYPE
    {	SE_UNKNOWN_OBJECT_TYPE	= 0,
	SE_FILE_OBJECT	= SE_UNKNOWN_OBJECT_TYPE + 1,
	SE_SERVICE	= SE_FILE_OBJECT + 1,
	SE_PRINTER	= SE_SERVICE + 1,
	SE_REGISTRY_KEY	= SE_PRINTER + 1,
	SE_LMSHARE	= SE_REGISTRY_KEY + 1,
	SE_KERNEL_OBJECT	= SE_LMSHARE + 1,
	SE_WINDOW_OBJECT	= SE_KERNEL_OBJECT + 1
    }	SE_OBJECT_TYPE;

typedef struct  _EXPLICIT_ACCESS_W
    {
    DWORD grfAccessPermissions;
    ACCESS_MODE grfAccessMode;
    DWORD grfInheritance;
    TRUSTEE_W Trustee;
    }	EXPLICIT_ACCESS_W;

typedef struct _EXPLICIT_ACCESS_W __RPC_FAR *PEXPLICIT_ACCESS_W;

typedef struct  _EXPLICIT_ACCESS_A
    {
    DWORD grfAccessPermissions;
    ACCESS_MODE grfAccessMode;
    DWORD grfInheritance;
    TRUSTEE_A Trustee;
    }	EXPLICIT_ACCESS_A;

typedef struct _EXPLICIT_ACCESS_A __RPC_FAR *PEXPLICIT_ACCESS_A;

#else
#include <accctrl.h>
#endif


extern RPC_IF_HANDLE __MIDL_itf_oledb_0156_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_oledb_0156_v0_0_s_ifspec;

#ifndef __ITrusteeAdmin_INTERFACE_DEFINED__
#define __ITrusteeAdmin_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITrusteeAdmin
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object][local] */ 



EXTERN_C const IID IID_ITrusteeAdmin;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733aa1-2a1c-11ce-ade5-00aa0044773d")
    ITrusteeAdmin : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CompareTrustees( 
            /* [in] */ TRUSTEE_W __RPC_FAR *pTrustee1,
            /* [in] */ TRUSTEE_W __RPC_FAR *pTrustee2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateTrustee( 
            /* [in] */ TRUSTEE_W __RPC_FAR *pTrustee,
            /* [in] */ ULONG cPropertySets,
            /* [size_is][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ]) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DeleteTrustee( 
            /* [in] */ TRUSTEE_W __RPC_FAR *pTrustee) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetTrusteeProperties( 
            /* [in] */ TRUSTEE_W __RPC_FAR *pTrustee,
            /* [in] */ ULONG cPropertySets,
            /* [size_is][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ]) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTrusteeProperties( 
            /* [in] */ TRUSTEE_W __RPC_FAR *pTrustee,
            /* [in] */ const ULONG cPropertyIDSets,
            /* [size_is][in] */ const DBPROPIDSET __RPC_FAR rgPropertyIDSets[  ],
            /* [out][in] */ ULONG __RPC_FAR *pcPropertySets,
            /* [size_is][size_is][out] */ DBPROPSET __RPC_FAR *__RPC_FAR *prgPropertySets) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITrusteeAdminVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITrusteeAdmin __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITrusteeAdmin __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITrusteeAdmin __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CompareTrustees )( 
            ITrusteeAdmin __RPC_FAR * This,
            /* [in] */ TRUSTEE_W __RPC_FAR *pTrustee1,
            /* [in] */ TRUSTEE_W __RPC_FAR *pTrustee2);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateTrustee )( 
            ITrusteeAdmin __RPC_FAR * This,
            /* [in] */ TRUSTEE_W __RPC_FAR *pTrustee,
            /* [in] */ ULONG cPropertySets,
            /* [size_is][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ]);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteTrustee )( 
            ITrusteeAdmin __RPC_FAR * This,
            /* [in] */ TRUSTEE_W __RPC_FAR *pTrustee);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTrusteeProperties )( 
            ITrusteeAdmin __RPC_FAR * This,
            /* [in] */ TRUSTEE_W __RPC_FAR *pTrustee,
            /* [in] */ ULONG cPropertySets,
            /* [size_is][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ]);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTrusteeProperties )( 
            ITrusteeAdmin __RPC_FAR * This,
            /* [in] */ TRUSTEE_W __RPC_FAR *pTrustee,
            /* [in] */ const ULONG cPropertyIDSets,
            /* [size_is][in] */ const DBPROPIDSET __RPC_FAR rgPropertyIDSets[  ],
            /* [out][in] */ ULONG __RPC_FAR *pcPropertySets,
            /* [size_is][size_is][out] */ DBPROPSET __RPC_FAR *__RPC_FAR *prgPropertySets);
        
        END_INTERFACE
    } ITrusteeAdminVtbl;

    interface ITrusteeAdmin
    {
        CONST_VTBL struct ITrusteeAdminVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITrusteeAdmin_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITrusteeAdmin_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITrusteeAdmin_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITrusteeAdmin_CompareTrustees(This,pTrustee1,pTrustee2)	\
    (This)->lpVtbl -> CompareTrustees(This,pTrustee1,pTrustee2)

#define ITrusteeAdmin_CreateTrustee(This,pTrustee,cPropertySets,rgPropertySets)	\
    (This)->lpVtbl -> CreateTrustee(This,pTrustee,cPropertySets,rgPropertySets)

#define ITrusteeAdmin_DeleteTrustee(This,pTrustee)	\
    (This)->lpVtbl -> DeleteTrustee(This,pTrustee)

#define ITrusteeAdmin_SetTrusteeProperties(This,pTrustee,cPropertySets,rgPropertySets)	\
    (This)->lpVtbl -> SetTrusteeProperties(This,pTrustee,cPropertySets,rgPropertySets)

#define ITrusteeAdmin_GetTrusteeProperties(This,pTrustee,cPropertyIDSets,rgPropertyIDSets,pcPropertySets,prgPropertySets)	\
    (This)->lpVtbl -> GetTrusteeProperties(This,pTrustee,cPropertyIDSets,rgPropertyIDSets,pcPropertySets,prgPropertySets)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ITrusteeAdmin_CompareTrustees_Proxy( 
    ITrusteeAdmin __RPC_FAR * This,
    /* [in] */ TRUSTEE_W __RPC_FAR *pTrustee1,
    /* [in] */ TRUSTEE_W __RPC_FAR *pTrustee2);


void __RPC_STUB ITrusteeAdmin_CompareTrustees_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITrusteeAdmin_CreateTrustee_Proxy( 
    ITrusteeAdmin __RPC_FAR * This,
    /* [in] */ TRUSTEE_W __RPC_FAR *pTrustee,
    /* [in] */ ULONG cPropertySets,
    /* [size_is][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ]);


void __RPC_STUB ITrusteeAdmin_CreateTrustee_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITrusteeAdmin_DeleteTrustee_Proxy( 
    ITrusteeAdmin __RPC_FAR * This,
    /* [in] */ TRUSTEE_W __RPC_FAR *pTrustee);


void __RPC_STUB ITrusteeAdmin_DeleteTrustee_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITrusteeAdmin_SetTrusteeProperties_Proxy( 
    ITrusteeAdmin __RPC_FAR * This,
    /* [in] */ TRUSTEE_W __RPC_FAR *pTrustee,
    /* [in] */ ULONG cPropertySets,
    /* [size_is][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ]);


void __RPC_STUB ITrusteeAdmin_SetTrusteeProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITrusteeAdmin_GetTrusteeProperties_Proxy( 
    ITrusteeAdmin __RPC_FAR * This,
    /* [in] */ TRUSTEE_W __RPC_FAR *pTrustee,
    /* [in] */ const ULONG cPropertyIDSets,
    /* [size_is][in] */ const DBPROPIDSET __RPC_FAR rgPropertyIDSets[  ],
    /* [out][in] */ ULONG __RPC_FAR *pcPropertySets,
    /* [size_is][size_is][out] */ DBPROPSET __RPC_FAR *__RPC_FAR *prgPropertySets);


void __RPC_STUB ITrusteeAdmin_GetTrusteeProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITrusteeAdmin_INTERFACE_DEFINED__ */


#ifndef __ITrusteeGroupAdmin_INTERFACE_DEFINED__
#define __ITrusteeGroupAdmin_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITrusteeGroupAdmin
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object][local] */ 



EXTERN_C const IID IID_ITrusteeGroupAdmin;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733aa2-2a1c-11ce-ade5-00aa0044773d")
    ITrusteeGroupAdmin : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE AddMember( 
            /* [in] */ TRUSTEE_W __RPC_FAR *pMembershipTrustee,
            /* [in] */ TRUSTEE_W __RPC_FAR *pMemberTrustee) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DeleteMember( 
            /* [in] */ TRUSTEE_W __RPC_FAR *pMembershipTrustee,
            /* [in] */ TRUSTEE_W __RPC_FAR *pMemberTrustee) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsMember( 
            /* [in] */ TRUSTEE_W __RPC_FAR *pMembershipTrustee,
            /* [in] */ TRUSTEE_W __RPC_FAR *pMemberTrustee,
            /* [out] */ BOOL __RPC_FAR *pfStatus) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMembers( 
            /* [in] */ TRUSTEE_W __RPC_FAR *pMembershipTrustee,
            /* [out] */ ULONG __RPC_FAR *pcMembers,
            /* [out] */ TRUSTEE_W __RPC_FAR *__RPC_FAR *prgMembers) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMemberships( 
            /* [in] */ TRUSTEE_W __RPC_FAR *pTrustee,
            /* [out] */ ULONG __RPC_FAR *pcMemberships,
            /* [out] */ TRUSTEE_W __RPC_FAR *__RPC_FAR *prgMemberships) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITrusteeGroupAdminVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITrusteeGroupAdmin __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITrusteeGroupAdmin __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITrusteeGroupAdmin __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddMember )( 
            ITrusteeGroupAdmin __RPC_FAR * This,
            /* [in] */ TRUSTEE_W __RPC_FAR *pMembershipTrustee,
            /* [in] */ TRUSTEE_W __RPC_FAR *pMemberTrustee);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMember )( 
            ITrusteeGroupAdmin __RPC_FAR * This,
            /* [in] */ TRUSTEE_W __RPC_FAR *pMembershipTrustee,
            /* [in] */ TRUSTEE_W __RPC_FAR *pMemberTrustee);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsMember )( 
            ITrusteeGroupAdmin __RPC_FAR * This,
            /* [in] */ TRUSTEE_W __RPC_FAR *pMembershipTrustee,
            /* [in] */ TRUSTEE_W __RPC_FAR *pMemberTrustee,
            /* [out] */ BOOL __RPC_FAR *pfStatus);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMembers )( 
            ITrusteeGroupAdmin __RPC_FAR * This,
            /* [in] */ TRUSTEE_W __RPC_FAR *pMembershipTrustee,
            /* [out] */ ULONG __RPC_FAR *pcMembers,
            /* [out] */ TRUSTEE_W __RPC_FAR *__RPC_FAR *prgMembers);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMemberships )( 
            ITrusteeGroupAdmin __RPC_FAR * This,
            /* [in] */ TRUSTEE_W __RPC_FAR *pTrustee,
            /* [out] */ ULONG __RPC_FAR *pcMemberships,
            /* [out] */ TRUSTEE_W __RPC_FAR *__RPC_FAR *prgMemberships);
        
        END_INTERFACE
    } ITrusteeGroupAdminVtbl;

    interface ITrusteeGroupAdmin
    {
        CONST_VTBL struct ITrusteeGroupAdminVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITrusteeGroupAdmin_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITrusteeGroupAdmin_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITrusteeGroupAdmin_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITrusteeGroupAdmin_AddMember(This,pMembershipTrustee,pMemberTrustee)	\
    (This)->lpVtbl -> AddMember(This,pMembershipTrustee,pMemberTrustee)

#define ITrusteeGroupAdmin_DeleteMember(This,pMembershipTrustee,pMemberTrustee)	\
    (This)->lpVtbl -> DeleteMember(This,pMembershipTrustee,pMemberTrustee)

#define ITrusteeGroupAdmin_IsMember(This,pMembershipTrustee,pMemberTrustee,pfStatus)	\
    (This)->lpVtbl -> IsMember(This,pMembershipTrustee,pMemberTrustee,pfStatus)

#define ITrusteeGroupAdmin_GetMembers(This,pMembershipTrustee,pcMembers,prgMembers)	\
    (This)->lpVtbl -> GetMembers(This,pMembershipTrustee,pcMembers,prgMembers)

#define ITrusteeGroupAdmin_GetMemberships(This,pTrustee,pcMemberships,prgMemberships)	\
    (This)->lpVtbl -> GetMemberships(This,pTrustee,pcMemberships,prgMemberships)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ITrusteeGroupAdmin_AddMember_Proxy( 
    ITrusteeGroupAdmin __RPC_FAR * This,
    /* [in] */ TRUSTEE_W __RPC_FAR *pMembershipTrustee,
    /* [in] */ TRUSTEE_W __RPC_FAR *pMemberTrustee);


void __RPC_STUB ITrusteeGroupAdmin_AddMember_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITrusteeGroupAdmin_DeleteMember_Proxy( 
    ITrusteeGroupAdmin __RPC_FAR * This,
    /* [in] */ TRUSTEE_W __RPC_FAR *pMembershipTrustee,
    /* [in] */ TRUSTEE_W __RPC_FAR *pMemberTrustee);


void __RPC_STUB ITrusteeGroupAdmin_DeleteMember_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITrusteeGroupAdmin_IsMember_Proxy( 
    ITrusteeGroupAdmin __RPC_FAR * This,
    /* [in] */ TRUSTEE_W __RPC_FAR *pMembershipTrustee,
    /* [in] */ TRUSTEE_W __RPC_FAR *pMemberTrustee,
    /* [out] */ BOOL __RPC_FAR *pfStatus);


void __RPC_STUB ITrusteeGroupAdmin_IsMember_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITrusteeGroupAdmin_GetMembers_Proxy( 
    ITrusteeGroupAdmin __RPC_FAR * This,
    /* [in] */ TRUSTEE_W __RPC_FAR *pMembershipTrustee,
    /* [out] */ ULONG __RPC_FAR *pcMembers,
    /* [out] */ TRUSTEE_W __RPC_FAR *__RPC_FAR *prgMembers);


void __RPC_STUB ITrusteeGroupAdmin_GetMembers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITrusteeGroupAdmin_GetMemberships_Proxy( 
    ITrusteeGroupAdmin __RPC_FAR * This,
    /* [in] */ TRUSTEE_W __RPC_FAR *pTrustee,
    /* [out] */ ULONG __RPC_FAR *pcMemberships,
    /* [out] */ TRUSTEE_W __RPC_FAR *__RPC_FAR *prgMemberships);


void __RPC_STUB ITrusteeGroupAdmin_GetMemberships_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITrusteeGroupAdmin_INTERFACE_DEFINED__ */


#ifndef __IObjectAccessControl_INTERFACE_DEFINED__
#define __IObjectAccessControl_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IObjectAccessControl
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object][local] */ 



EXTERN_C const IID IID_IObjectAccessControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733aa3-2a1c-11ce-ade5-00aa0044773d")
    IObjectAccessControl : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetObjectAccessRights( 
            /* [in] */ SEC_OBJECT __RPC_FAR *pObject,
            /* [out][in] */ ULONG __RPC_FAR *pcAccessEntries,
            /* [out][in] */ EXPLICIT_ACCESS_W __RPC_FAR *__RPC_FAR *prgAccessEntries) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetObjectOwner( 
            /* [in] */ SEC_OBJECT __RPC_FAR *pObject,
            /* [out] */ TRUSTEE_W __RPC_FAR *__RPC_FAR *ppOwner) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsObjectAccessAllowed( 
            /* [in] */ SEC_OBJECT __RPC_FAR *pObject,
            /* [in] */ EXPLICIT_ACCESS_W __RPC_FAR *pAccessEntry,
            /* [out] */ BOOL __RPC_FAR *pfResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetObjectAccessRights( 
            /* [in] */ SEC_OBJECT __RPC_FAR *pObject,
            /* [in] */ ULONG cAccessEntries,
            /* [out][in] */ EXPLICIT_ACCESS_W __RPC_FAR *prgAccessEntries) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetObjectOwner( 
            /* [in] */ SEC_OBJECT __RPC_FAR *pObject,
            /* [in] */ TRUSTEE_W __RPC_FAR *pOwner) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IObjectAccessControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IObjectAccessControl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IObjectAccessControl __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IObjectAccessControl __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetObjectAccessRights )( 
            IObjectAccessControl __RPC_FAR * This,
            /* [in] */ SEC_OBJECT __RPC_FAR *pObject,
            /* [out][in] */ ULONG __RPC_FAR *pcAccessEntries,
            /* [out][in] */ EXPLICIT_ACCESS_W __RPC_FAR *__RPC_FAR *prgAccessEntries);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetObjectOwner )( 
            IObjectAccessControl __RPC_FAR * This,
            /* [in] */ SEC_OBJECT __RPC_FAR *pObject,
            /* [out] */ TRUSTEE_W __RPC_FAR *__RPC_FAR *ppOwner);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsObjectAccessAllowed )( 
            IObjectAccessControl __RPC_FAR * This,
            /* [in] */ SEC_OBJECT __RPC_FAR *pObject,
            /* [in] */ EXPLICIT_ACCESS_W __RPC_FAR *pAccessEntry,
            /* [out] */ BOOL __RPC_FAR *pfResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetObjectAccessRights )( 
            IObjectAccessControl __RPC_FAR * This,
            /* [in] */ SEC_OBJECT __RPC_FAR *pObject,
            /* [in] */ ULONG cAccessEntries,
            /* [out][in] */ EXPLICIT_ACCESS_W __RPC_FAR *prgAccessEntries);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetObjectOwner )( 
            IObjectAccessControl __RPC_FAR * This,
            /* [in] */ SEC_OBJECT __RPC_FAR *pObject,
            /* [in] */ TRUSTEE_W __RPC_FAR *pOwner);
        
        END_INTERFACE
    } IObjectAccessControlVtbl;

    interface IObjectAccessControl
    {
        CONST_VTBL struct IObjectAccessControlVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IObjectAccessControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IObjectAccessControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IObjectAccessControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IObjectAccessControl_GetObjectAccessRights(This,pObject,pcAccessEntries,prgAccessEntries)	\
    (This)->lpVtbl -> GetObjectAccessRights(This,pObject,pcAccessEntries,prgAccessEntries)

#define IObjectAccessControl_GetObjectOwner(This,pObject,ppOwner)	\
    (This)->lpVtbl -> GetObjectOwner(This,pObject,ppOwner)

#define IObjectAccessControl_IsObjectAccessAllowed(This,pObject,pAccessEntry,pfResult)	\
    (This)->lpVtbl -> IsObjectAccessAllowed(This,pObject,pAccessEntry,pfResult)

#define IObjectAccessControl_SetObjectAccessRights(This,pObject,cAccessEntries,prgAccessEntries)	\
    (This)->lpVtbl -> SetObjectAccessRights(This,pObject,cAccessEntries,prgAccessEntries)

#define IObjectAccessControl_SetObjectOwner(This,pObject,pOwner)	\
    (This)->lpVtbl -> SetObjectOwner(This,pObject,pOwner)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IObjectAccessControl_GetObjectAccessRights_Proxy( 
    IObjectAccessControl __RPC_FAR * This,
    /* [in] */ SEC_OBJECT __RPC_FAR *pObject,
    /* [out][in] */ ULONG __RPC_FAR *pcAccessEntries,
    /* [out][in] */ EXPLICIT_ACCESS_W __RPC_FAR *__RPC_FAR *prgAccessEntries);


void __RPC_STUB IObjectAccessControl_GetObjectAccessRights_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IObjectAccessControl_GetObjectOwner_Proxy( 
    IObjectAccessControl __RPC_FAR * This,
    /* [in] */ SEC_OBJECT __RPC_FAR *pObject,
    /* [out] */ TRUSTEE_W __RPC_FAR *__RPC_FAR *ppOwner);


void __RPC_STUB IObjectAccessControl_GetObjectOwner_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IObjectAccessControl_IsObjectAccessAllowed_Proxy( 
    IObjectAccessControl __RPC_FAR * This,
    /* [in] */ SEC_OBJECT __RPC_FAR *pObject,
    /* [in] */ EXPLICIT_ACCESS_W __RPC_FAR *pAccessEntry,
    /* [out] */ BOOL __RPC_FAR *pfResult);


void __RPC_STUB IObjectAccessControl_IsObjectAccessAllowed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IObjectAccessControl_SetObjectAccessRights_Proxy( 
    IObjectAccessControl __RPC_FAR * This,
    /* [in] */ SEC_OBJECT __RPC_FAR *pObject,
    /* [in] */ ULONG cAccessEntries,
    /* [out][in] */ EXPLICIT_ACCESS_W __RPC_FAR *prgAccessEntries);


void __RPC_STUB IObjectAccessControl_SetObjectAccessRights_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IObjectAccessControl_SetObjectOwner_Proxy( 
    IObjectAccessControl __RPC_FAR * This,
    /* [in] */ SEC_OBJECT __RPC_FAR *pObject,
    /* [in] */ TRUSTEE_W __RPC_FAR *pOwner);


void __RPC_STUB IObjectAccessControl_SetObjectOwner_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IObjectAccessControl_INTERFACE_DEFINED__ */


#ifndef __ISecurityInfo_INTERFACE_DEFINED__
#define __ISecurityInfo_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ISecurityInfo
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][uuid][object][local] */ 


//@@@+ V2.1
#if( OLEDBVER >= 0x0210 )
typedef DWORD ACCESS_MASK;


enum ACCESS_MASKENUM
    {	PERM_DESIGN	= 0x800L,
	PERM_WITHGRANT	= 0x1000L,
	PERM_REFERENCE	= 0x2000L,
	PERM_CREATE	= 0x4000L,
	PERM_INSERT	= 0x8000L,
	PERM_DELETE	= 0x10000L,
	PERM_MAXIMUM_ALLOWED	= 0x2000000L,
	PERM_ALL	= 0x10000000L,
	PERM_EXECUTE	= 0x20000000L,
	PERM_READ	= 0x80000000L,
	PERM_UPDATE	= 0x40000000L
    };
#endif // OLEDBVER >= 0x0210
//@@@- V2.1

EXTERN_C const IID IID_ISecurityInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0c733aa4-2a1c-11ce-ade5-00aa0044773d")
    ISecurityInfo : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetCurrentTrustee( 
            /* [out] */ TRUSTEE_W __RPC_FAR *__RPC_FAR *ppTrustee) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetObjectTypes( 
            /* [out] */ ULONG __RPC_FAR *cObjectTypes,
            /* [out] */ GUID __RPC_FAR *__RPC_FAR *rgObjectTypes) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPermissions( 
            /* [in] */ GUID ObjectType,
            /* [out] */ ACCESS_MASK __RPC_FAR *pPermissions) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISecurityInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISecurityInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISecurityInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISecurityInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCurrentTrustee )( 
            ISecurityInfo __RPC_FAR * This,
            /* [out] */ TRUSTEE_W __RPC_FAR *__RPC_FAR *ppTrustee);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetObjectTypes )( 
            ISecurityInfo __RPC_FAR * This,
            /* [out] */ ULONG __RPC_FAR *cObjectTypes,
            /* [out] */ GUID __RPC_FAR *__RPC_FAR *rgObjectTypes);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPermissions )( 
            ISecurityInfo __RPC_FAR * This,
            /* [in] */ GUID ObjectType,
            /* [out] */ ACCESS_MASK __RPC_FAR *pPermissions);
        
        END_INTERFACE
    } ISecurityInfoVtbl;

    interface ISecurityInfo
    {
        CONST_VTBL struct ISecurityInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISecurityInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISecurityInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISecurityInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISecurityInfo_GetCurrentTrustee(This,ppTrustee)	\
    (This)->lpVtbl -> GetCurrentTrustee(This,ppTrustee)

#define ISecurityInfo_GetObjectTypes(This,cObjectTypes,rgObjectTypes)	\
    (This)->lpVtbl -> GetObjectTypes(This,cObjectTypes,rgObjectTypes)

#define ISecurityInfo_GetPermissions(This,ObjectType,pPermissions)	\
    (This)->lpVtbl -> GetPermissions(This,ObjectType,pPermissions)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISecurityInfo_GetCurrentTrustee_Proxy( 
    ISecurityInfo __RPC_FAR * This,
    /* [out] */ TRUSTEE_W __RPC_FAR *__RPC_FAR *ppTrustee);


void __RPC_STUB ISecurityInfo_GetCurrentTrustee_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISecurityInfo_GetObjectTypes_Proxy( 
    ISecurityInfo __RPC_FAR * This,
    /* [out] */ ULONG __RPC_FAR *cObjectTypes,
    /* [out] */ GUID __RPC_FAR *__RPC_FAR *rgObjectTypes);


void __RPC_STUB ISecurityInfo_GetObjectTypes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISecurityInfo_GetPermissions_Proxy( 
    ISecurityInfo __RPC_FAR * This,
    /* [in] */ GUID ObjectType,
    /* [out] */ ACCESS_MASK __RPC_FAR *pPermissions);


void __RPC_STUB ISecurityInfo_GetPermissions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISecurityInfo_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_oledb_0160
 * at Tue Apr 28 11:55:07 1998
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


#endif // OLEDBVER >= 0x0210
//@@@- V2.1
//
// IID values
//

// IID_IAccessor				= {0x0c733a8c,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IRowset					= {0x0c733a7c,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IRowsetInfo				= {0x0c733a55,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IRowsetLocate			= {0x0c733a7d,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IRowsetResynch			= {0x0c733a84,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IRowsetScroll			= {0x0c733a7e,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IRowsetChange			= {0x0c733a05,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IRowsetUpdate			= {0x0c733a6d,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IRowsetIdentity			= {0x0c733a09,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IRowsetNotify			= {0x0c733a83,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IRowsetIndex				= {0x0c733a82,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_ICommand					= {0x0c733a63,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IMultipleResults			= {0x0c733a90,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IConvertType				= {0x0c733a88,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_ICommandPrepare			= {0x0c733a26,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_ICommandProperties		= {0x0c733a79,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_ICommandText				= {0x0c733a27,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_ICommandWithParameters	= {0x0c733a64,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IColumnsRowset			= {0x0c733a10,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IColumnsInfo				= {0x0c733a11,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IDBCreateCommand			= {0x0c733a1d,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IDBCreateSession			= {0x0c733a5d,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_ISourcesRowset			= {0x0c733a1e,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IDBProperties			= {0x0c733a8a,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IDBInitialize			= {0x0c733a8b,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IDBInfo					= {0x0c733a89,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IDBDataSourceAdmin		= {0x0c733a7a,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_ISessionProperties		= {0x0c733a85,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IIndexDefinition			= {0x0c733a68,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_ITableDefinition			= {0x0c733a86,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IOpenRowset				= {0x0c733a69,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IDBSchemaRowset			= {0x0c733a7b,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IErrorRecords			= {0x0c733a67,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IErrorLookup				= {0x0c733a66,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_ISQLErrorInfo			= {0x0c733a74,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IGetDataSource			= {0x0c733a75,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_ITransactionLocal		= {0x0c733a5f,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_ITransactionJoin			= {0x0c733a5e,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_ITransactionObject		= {0x0c733a60,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
//@@@+ V1.5
#if( OLEDBVER >= 0x0150 )
//IID_IChapteredRowset			= {0x0c733a93,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
//IID_IDBAsynchNotify			= {0x0c733a96,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
//IID_IDBAsynchStatus			= {0x0c733a95,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
//IID_IRowsetFind				= {0x0c733a9d,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
//IID_IRowPosition				= {0x0c733a94,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
//IID_IRowPositionChange		= {0x0997a571,0x126e,0x11d0,{0x9f,0x8a,0x00,0xa0,0xc9,0xa0,0x63,0x1e}}
//IID_IViewRowset				= {0x0c733a97,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
//IID_IViewChapter				= {0x0c733a98,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
//IID_IViewSort					= {0x0c733a9a,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
//IID_IViewFilter				= {0x0c733a9b,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
//IID_IRowsetView				= {0x0c733a99,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
#endif // OLEDBVER >= 0x0150
//@@@- V1.5
//@@@+ V2.0
#if( OLEDBVER >= 0x0200 )
// IID_IMDDataset				= {0xa07cccd1,0x8148,0x11d0,{0x87,0xbb,0x00,0xc0,0x4f,0xc3,0x39,0x42}}
// IID_IMDFind					= {0xa07cccd2,0x8148,0x11d0,{0x87,0xbb,0x00,0xc0,0x4f,0xc3,0x39,0x42}}
// IID_IMDRangeRowset			= {0x0c733aa0,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IAlterTable				= {0x0c733aa5,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IAlterIndex				= {0x0c733aa6,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_ICommandPersist			= {0x0c733aa7,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IRowsetChapterMember		= {0x0c733aa8,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IRowsetRefresh			= {0x0c733aa9,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IParentRowset				= {0x0c733aaa,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
#endif // OLEDBVER >= 0x0200
//@@@- V2.0
//@@@+ V2.1
#if( OLEDBVER >= 0x0210 )
// IID_ITrusteeAdmin				= {0c733aa1,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_ITrusteeGroupAdmin		= {0c733aa2,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IObjectAccessControl		= {0c733aa3,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_ISecurityInfo				= {0c733aa4,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
#endif // OLEDBVER >= 0x0210
//@@@- V2.1
//@@@+ V2.5
#if( OLEDBVER >= 0x0250 )
// IID_IRowsetExactScroll		= {0x0c733a7f,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IRowsetNextRowset			= {0x0c733a72,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IRowsetNewRowAfter		= {0x0c733a71,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IRowsetWithParameters	= {0x0c733a6e,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IRowsetFind				= {0x0c733a0d,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IRowsetAsynch			= {0x0c733a0f,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IRowsetKeys				= {0x0c733a12,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IRowsetWatchAll			= {0x0c733a73,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IRowsetWatchNotify		= {0x0c733a44,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IRowsetWatchRegion		= {0x0c733a45,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IRowsetCopyRows			= {0x0c733a6b,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IReadData				= {0x0c733a6a,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_ICommandCost				= {0x0c733a4e,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_ICommandTree				= {0x0c733a87,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_ICommandValidate			= {0x0c733a18,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IQuery					= {0x0c733a51,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_ITableRename				= {0x0c733a77,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IDBSchemaCommand			= {0x0c733a50,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
// IID_IProvideMoniker			= {0x0c733a4d,0x2a1c,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}}
#endif // OLEDBVER >= 0x0250
//@@@- V2.5
#include <poppack.h>	// restore original structure packing


extern RPC_IF_HANDLE __MIDL_itf_oledb_0160_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_oledb_0160_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* [local] */ HRESULT STDMETHODCALLTYPE IAccessor_AddRefAccessor_Proxy( 
    IAccessor __RPC_FAR * This,
    /* [in] */ HACCESSOR hAccessor,
    /* [unique][out][in] */ ULONG __RPC_FAR *pcRefCount);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IAccessor_AddRefAccessor_Stub( 
    IAccessor __RPC_FAR * This,
    /* [in] */ HACCESSOR hAccessor,
    /* [unique][out][in] */ ULONG __RPC_FAR *pcRefCount,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IAccessor_CreateAccessor_Proxy( 
    IAccessor __RPC_FAR * This,
    /* [in] */ DBACCESSORFLAGS dwAccessorFlags,
    /* [in] */ ULONG cBindings,
    /* [size_is][in] */ const DBBINDING __RPC_FAR rgBindings[  ],
    /* [in] */ ULONG cbRowSize,
    /* [out] */ HACCESSOR __RPC_FAR *phAccessor,
    /* [size_is][out] */ DBBINDSTATUS __RPC_FAR rgStatus[  ]);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IAccessor_CreateAccessor_Stub( 
    IAccessor __RPC_FAR * This,
    /* [in] */ DBACCESSORFLAGS dwAccessorFlags,
    /* [in] */ ULONG cBindings,
    /* [size_is][unique][in] */ DBBINDING __RPC_FAR *rgBindings,
    /* [in] */ ULONG cbRowSize,
    /* [out] */ HACCESSOR __RPC_FAR *phAccessor,
    /* [size_is][unique][out][in] */ DBBINDSTATUS __RPC_FAR *rgStatus,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IAccessor_GetBindings_Proxy( 
    IAccessor __RPC_FAR * This,
    /* [in] */ HACCESSOR hAccessor,
    /* [out] */ DBACCESSORFLAGS __RPC_FAR *pdwAccessorFlags,
    /* [out][in] */ ULONG __RPC_FAR *pcBindings,
    /* [size_is][size_is][out] */ DBBINDING __RPC_FAR *__RPC_FAR *prgBindings);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IAccessor_GetBindings_Stub( 
    IAccessor __RPC_FAR * This,
    /* [in] */ HACCESSOR hAccessor,
    /* [out] */ DBACCESSORFLAGS __RPC_FAR *pdwAccessorFlags,
    /* [out][in] */ ULONG __RPC_FAR *pcBindings,
    /* [size_is][size_is][out] */ DBBINDING __RPC_FAR *__RPC_FAR *prgBindings,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IAccessor_ReleaseAccessor_Proxy( 
    IAccessor __RPC_FAR * This,
    /* [in] */ HACCESSOR hAccessor,
    /* [unique][out][in] */ ULONG __RPC_FAR *pcRefCount);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IAccessor_ReleaseAccessor_Stub( 
    IAccessor __RPC_FAR * This,
    /* [in] */ HACCESSOR hAccessor,
    /* [unique][out][in] */ ULONG __RPC_FAR *pcRefCount,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IRowsetInfo_GetProperties_Proxy( 
    IRowsetInfo __RPC_FAR * This,
    /* [in] */ const ULONG cPropertyIDSets,
    /* [size_is][in] */ const DBPROPIDSET __RPC_FAR rgPropertyIDSets[  ],
    /* [out][in] */ ULONG __RPC_FAR *pcPropertySets,
    /* [size_is][size_is][out] */ DBPROPSET __RPC_FAR *__RPC_FAR *prgPropertySets);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IRowsetInfo_GetProperties_Stub( 
    IRowsetInfo __RPC_FAR * This,
    /* [in] */ ULONG cPropertyIDSets,
    /* [size_is][unique][in] */ const DBPROPIDSET __RPC_FAR *rgPropertyIDSets,
    /* [out][in] */ ULONG __RPC_FAR *pcPropertySets,
    /* [size_is][size_is][out] */ DBPROPSET __RPC_FAR *__RPC_FAR *prgPropertySets,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IRowsetInfo_GetReferencedRowset_Proxy( 
    IRowsetInfo __RPC_FAR * This,
    /* [in] */ ULONG iOrdinal,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppReferencedRowset);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IRowsetInfo_GetReferencedRowset_Stub( 
    IRowsetInfo __RPC_FAR * This,
    /* [in] */ ULONG iOrdinal,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppReferencedRowset,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IRowsetInfo_GetSpecification_Proxy( 
    IRowsetInfo __RPC_FAR * This,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppSpecification);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IRowsetInfo_GetSpecification_Stub( 
    IRowsetInfo __RPC_FAR * This,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppSpecification,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IChapteredRowset_AddRefChapter_Proxy( 
    IChapteredRowset __RPC_FAR * This,
    /* [in] */ HCHAPTER hChapter,
    /* [out] */ ULONG __RPC_FAR *pcRefCount);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IChapteredRowset_AddRefChapter_Stub( 
    IChapteredRowset __RPC_FAR * This,
    /* [in] */ HCHAPTER hChapter,
    /* [out] */ ULONG __RPC_FAR *pcRefCount,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IChapteredRowset_ReleaseChapter_Proxy( 
    IChapteredRowset __RPC_FAR * This,
    /* [in] */ HCHAPTER hChapter,
    /* [out] */ ULONG __RPC_FAR *pcRefCount);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IChapteredRowset_ReleaseChapter_Stub( 
    IChapteredRowset __RPC_FAR * This,
    /* [in] */ HCHAPTER hChapter,
    /* [out] */ ULONG __RPC_FAR *pcRefCount,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IRowPosition_ClearRowPosition_Proxy( 
    IRowPosition __RPC_FAR * This);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IRowPosition_ClearRowPosition_Stub( 
    IRowPosition __RPC_FAR * This,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IRowPosition_GetRowPosition_Proxy( 
    IRowPosition __RPC_FAR * This,
    /* [out] */ HCHAPTER __RPC_FAR *phChapter,
    /* [out] */ HROW __RPC_FAR *phRow,
    /* [out] */ DBPOSITIONFLAGS __RPC_FAR *pdwPositionFlags);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IRowPosition_GetRowPosition_Stub( 
    IRowPosition __RPC_FAR * This,
    /* [out] */ HCHAPTER __RPC_FAR *phChapter,
    /* [out] */ HROW __RPC_FAR *phRow,
    /* [out] */ DBPOSITIONFLAGS __RPC_FAR *pdwPositionFlags,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IRowPosition_GetRowset_Proxy( 
    IRowPosition __RPC_FAR * This,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IRowPosition_GetRowset_Stub( 
    IRowPosition __RPC_FAR * This,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IRowPosition_Initialize_Proxy( 
    IRowPosition __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pRowset);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IRowPosition_Initialize_Stub( 
    IRowPosition __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pRowset,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IRowPosition_SetRowPosition_Proxy( 
    IRowPosition __RPC_FAR * This,
    /* [in] */ HCHAPTER hChapter,
    /* [in] */ HROW hRow,
    /* [in] */ DBPOSITIONFLAGS dwPositionFlags);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IRowPosition_SetRowPosition_Stub( 
    IRowPosition __RPC_FAR * This,
    /* [in] */ HCHAPTER hChapter,
    /* [in] */ HROW hRow,
    /* [in] */ DBPOSITIONFLAGS dwPositionFlags,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IRowPositionChange_OnRowPositionChange_Proxy( 
    IRowPositionChange __RPC_FAR * This,
    /* [in] */ DBREASON eReason,
    /* [in] */ DBEVENTPHASE ePhase,
    /* [in] */ BOOL fCantDeny);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IRowPositionChange_OnRowPositionChange_Stub( 
    IRowPositionChange __RPC_FAR * This,
    /* [in] */ DBREASON eReason,
    /* [in] */ DBEVENTPHASE ePhase,
    /* [in] */ BOOL fCantDeny,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IViewRowset_GetSpecification_Proxy( 
    IViewRowset __RPC_FAR * This,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppObject);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IViewRowset_GetSpecification_Stub( 
    IViewRowset __RPC_FAR * This,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppObject,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IViewRowset_OpenViewRowset_Proxy( 
    IViewRowset __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IViewRowset_OpenViewRowset_Stub( 
    IViewRowset __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IViewChapter_GetSpecification_Proxy( 
    IViewChapter __RPC_FAR * This,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IViewChapter_GetSpecification_Stub( 
    IViewChapter __RPC_FAR * This,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IViewChapter_OpenViewChapter_Proxy( 
    IViewChapter __RPC_FAR * This,
    /* [in] */ HCHAPTER hSource,
    /* [out] */ HCHAPTER __RPC_FAR *phViewChapter);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IViewChapter_OpenViewChapter_Stub( 
    IViewChapter __RPC_FAR * This,
    /* [in] */ HCHAPTER hSource,
    /* [out] */ HCHAPTER __RPC_FAR *phViewChapter,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IViewSort_GetSortOrder_Proxy( 
    IViewSort __RPC_FAR * This,
    /* [out] */ ULONG __RPC_FAR *pcValues,
    /* [out] */ ULONG __RPC_FAR *__RPC_FAR prgColumns[  ],
    /* [out] */ DBSORT __RPC_FAR *__RPC_FAR prgOrders[  ]);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IViewSort_GetSortOrder_Stub( 
    IViewSort __RPC_FAR * This,
    /* [out][in] */ ULONG __RPC_FAR *pcValues,
    /* [size_is][size_is][out] */ ULONG __RPC_FAR *__RPC_FAR *prgColumns,
    /* [size_is][size_is][out] */ ULONG __RPC_FAR *__RPC_FAR *prgOrders,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IViewSort_SetSortOrder_Proxy( 
    IViewSort __RPC_FAR * This,
    /* [in] */ ULONG cValues,
    /* [size_is][in] */ const ULONG __RPC_FAR rgColumns[  ],
    /* [size_is][in] */ const DBSORT __RPC_FAR rgOrders[  ]);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IViewSort_SetSortOrder_Stub( 
    IViewSort __RPC_FAR * This,
    /* [in] */ ULONG cValues,
    /* [size_is][in] */ const ULONG __RPC_FAR *rgColumns,
    /* [size_is][in] */ const DBSORT __RPC_FAR *rgOrders,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IViewFilter_GetFilterBindings_Proxy( 
    IViewFilter __RPC_FAR * This,
    /* [out] */ ULONG __RPC_FAR *pcBindings,
    /* [out] */ DBBINDING __RPC_FAR *__RPC_FAR *prgBindings);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IViewFilter_GetFilterBindings_Stub( 
    IViewFilter __RPC_FAR * This,
    /* [out][in] */ ULONG __RPC_FAR *pcBindings,
    /* [size_is][size_is][out] */ DBBINDING __RPC_FAR *__RPC_FAR *prgBindings,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IRowsetView_CreateView_Proxy( 
    IRowsetView __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppView);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IRowsetView_CreateView_Stub( 
    IRowsetView __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppView,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IRowsetView_GetView_Proxy( 
    IRowsetView __RPC_FAR * This,
    /* [in] */ HCHAPTER hChapter,
    /* [in] */ REFIID riid,
    /* [out] */ HCHAPTER __RPC_FAR *phChapterSource,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppView);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IRowsetView_GetView_Stub( 
    IRowsetView __RPC_FAR * This,
    /* [in] */ HCHAPTER hChapter,
    /* [in] */ REFIID riid,
    /* [out] */ HCHAPTER __RPC_FAR *phChapterSource,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppView,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IRowsetIdentity_IsSameRow_Proxy( 
    IRowsetIdentity __RPC_FAR * This,
    /* [in] */ HROW hThisRow,
    /* [in] */ HROW hThatRow);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IRowsetIdentity_IsSameRow_Stub( 
    IRowsetIdentity __RPC_FAR * This,
    /* [in] */ HROW hThisRow,
    /* [in] */ HROW hThatRow,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IRowsetNotify_OnFieldChange_Proxy( 
    IRowsetNotify __RPC_FAR * This,
    /* [in] */ IRowset __RPC_FAR *pRowset,
    /* [in] */ HROW hRow,
    /* [in] */ ULONG cColumns,
    /* [size_is][in] */ ULONG __RPC_FAR rgColumns[  ],
    /* [in] */ DBREASON eReason,
    /* [in] */ DBEVENTPHASE ePhase,
    /* [in] */ BOOL fCantDeny);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IRowsetNotify_OnFieldChange_Stub( 
    IRowsetNotify __RPC_FAR * This,
    /* [in] */ IRowset __RPC_FAR *pRowset,
    /* [in] */ HROW hRow,
    /* [in] */ ULONG cColumns,
    /* [size_is][in] */ ULONG __RPC_FAR *rgColumns,
    /* [in] */ DBREASON eReason,
    /* [in] */ DBEVENTPHASE ePhase,
    /* [in] */ BOOL fCantDeny,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IRowsetNotify_OnRowChange_Proxy( 
    IRowsetNotify __RPC_FAR * This,
    /* [in] */ IRowset __RPC_FAR *pRowset,
    /* [in] */ ULONG cRows,
    /* [size_is][in] */ const HROW __RPC_FAR rghRows[  ],
    /* [in] */ DBREASON eReason,
    /* [in] */ DBEVENTPHASE ePhase,
    /* [in] */ BOOL fCantDeny);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IRowsetNotify_OnRowChange_Stub( 
    IRowsetNotify __RPC_FAR * This,
    /* [in] */ IRowset __RPC_FAR *pRowset,
    /* [in] */ ULONG cRows,
    /* [size_is][in] */ const HROW __RPC_FAR *rghRows,
    /* [in] */ DBREASON eReason,
    /* [in] */ DBEVENTPHASE ePhase,
    /* [in] */ BOOL fCantDeny,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IRowsetNotify_OnRowsetChange_Proxy( 
    IRowsetNotify __RPC_FAR * This,
    /* [in] */ IRowset __RPC_FAR *pRowset,
    /* [in] */ DBREASON eReason,
    /* [in] */ DBEVENTPHASE ePhase,
    /* [in] */ BOOL fCantDeny);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IRowsetNotify_OnRowsetChange_Stub( 
    IRowsetNotify __RPC_FAR * This,
    /* [in] */ IRowset __RPC_FAR *pRowset,
    /* [in] */ DBREASON eReason,
    /* [in] */ DBEVENTPHASE ePhase,
    /* [in] */ BOOL fCantDeny,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE ICommand_Cancel_Proxy( 
    ICommand __RPC_FAR * This);


/* [call_as] */ HRESULT STDMETHODCALLTYPE ICommand_Cancel_Stub( 
    ICommand __RPC_FAR * This,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE ICommand_Execute_Proxy( 
    ICommand __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ REFIID riid,
    /* [out][in] */ DBPARAMS __RPC_FAR *pParams,
    /* [out] */ LONG __RPC_FAR *pcRowsAffected,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset);


/* [call_as] */ HRESULT STDMETHODCALLTYPE ICommand_Execute_Stub( 
    ICommand __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ REFIID riid,
    /* [in] */ HACCESSOR hAccessor,
    /* [in] */ ULONG cParamSets,
    /* [in] */ ULONG cbData,
    /* [size_is][unique][out][in] */ BYTE __RPC_FAR *pbData,
    /* [unique][out][in] */ LONG __RPC_FAR *pcRowsAffected,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE ICommand_GetDBSession_Proxy( 
    ICommand __RPC_FAR * This,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppSession);


/* [call_as] */ HRESULT STDMETHODCALLTYPE ICommand_GetDBSession_Stub( 
    ICommand __RPC_FAR * This,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppSession,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IMultipleResults_GetResult_Proxy( 
    IMultipleResults __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ LONG reserved,
    /* [in] */ REFIID riid,
    /* [out] */ LONG __RPC_FAR *pcRowsAffected,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IMultipleResults_GetResult_Stub( 
    IMultipleResults __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ LONG reserved,
    /* [in] */ REFIID riid,
    /* [unique][out][in] */ LONG __RPC_FAR *pcRowsAffected,
    /* [iid_is][unique][out][in] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IConvertType_CanConvert_Proxy( 
    IConvertType __RPC_FAR * This,
    /* [in] */ DBTYPE wFromType,
    /* [in] */ DBTYPE wToType,
    /* [in] */ DBCONVERTFLAGS dwConvertFlags);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IConvertType_CanConvert_Stub( 
    IConvertType __RPC_FAR * This,
    /* [in] */ DBTYPE wFromType,
    /* [in] */ DBTYPE wToType,
    /* [in] */ DBCONVERTFLAGS dwConvertFlags,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE ICommandPrepare_Prepare_Proxy( 
    ICommandPrepare __RPC_FAR * This,
    /* [in] */ ULONG cExpectedRuns);


/* [call_as] */ HRESULT STDMETHODCALLTYPE ICommandPrepare_Prepare_Stub( 
    ICommandPrepare __RPC_FAR * This,
    /* [in] */ ULONG cExpectedRuns,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE ICommandPrepare_Unprepare_Proxy( 
    ICommandPrepare __RPC_FAR * This);


/* [call_as] */ HRESULT STDMETHODCALLTYPE ICommandPrepare_Unprepare_Stub( 
    ICommandPrepare __RPC_FAR * This,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE ICommandProperties_GetProperties_Proxy( 
    ICommandProperties __RPC_FAR * This,
    /* [in] */ const ULONG cPropertyIDSets,
    /* [size_is][in] */ const DBPROPIDSET __RPC_FAR rgPropertyIDSets[  ],
    /* [out][in] */ ULONG __RPC_FAR *pcPropertySets,
    /* [size_is][size_is][out] */ DBPROPSET __RPC_FAR *__RPC_FAR *prgPropertySets);


/* [call_as] */ HRESULT STDMETHODCALLTYPE ICommandProperties_GetProperties_Stub( 
    ICommandProperties __RPC_FAR * This,
    /* [in] */ const ULONG cPropertyIDSets,
    /* [size_is][unique][in] */ const DBPROPIDSET __RPC_FAR *rgPropertyIDSets,
    /* [out][in] */ ULONG __RPC_FAR *pcPropertySets,
    /* [size_is][size_is][out] */ DBPROPSET __RPC_FAR *__RPC_FAR *prgPropertySets,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE ICommandProperties_SetProperties_Proxy( 
    ICommandProperties __RPC_FAR * This,
    /* [in] */ ULONG cPropertySets,
    /* [size_is][unique][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ]);


/* [call_as] */ HRESULT STDMETHODCALLTYPE ICommandProperties_SetProperties_Stub( 
    ICommandProperties __RPC_FAR * This,
    /* [in] */ ULONG cPropertySets,
    /* [size_is][unique][in] */ DBPROPSET __RPC_FAR *rgPropertySets,
    /* [in] */ ULONG cTotalProps,
    /* [size_is][out] */ DBPROPSTATUS __RPC_FAR *rgPropStatus,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE ICommandText_GetCommandText_Proxy( 
    ICommandText __RPC_FAR * This,
    /* [out][in] */ GUID __RPC_FAR *pguidDialect,
    /* [out] */ LPOLESTR __RPC_FAR *ppwszCommand);


/* [call_as] */ HRESULT STDMETHODCALLTYPE ICommandText_GetCommandText_Stub( 
    ICommandText __RPC_FAR * This,
    /* [unique][out][in] */ GUID __RPC_FAR *pguidDialect,
    /* [out] */ LPOLESTR __RPC_FAR *ppwszCommand,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE ICommandText_SetCommandText_Proxy( 
    ICommandText __RPC_FAR * This,
    /* [in] */ REFGUID rguidDialect,
    /* [unique][in] */ LPCOLESTR pwszCommand);


/* [call_as] */ HRESULT STDMETHODCALLTYPE ICommandText_SetCommandText_Stub( 
    ICommandText __RPC_FAR * This,
    /* [in] */ REFGUID rguidDialect,
    /* [unique][in] */ LPCOLESTR pwszCommand,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE ICommandWithParameters_GetParameterInfo_Proxy( 
    ICommandWithParameters __RPC_FAR * This,
    /* [out][in] */ ULONG __RPC_FAR *pcParams,
    /* [size_is][size_is][out] */ DBPARAMINFO __RPC_FAR *__RPC_FAR *prgParamInfo,
    /* [out] */ OLECHAR __RPC_FAR *__RPC_FAR *ppNamesBuffer);


/* [call_as] */ HRESULT STDMETHODCALLTYPE ICommandWithParameters_GetParameterInfo_Stub( 
    ICommandWithParameters __RPC_FAR * This,
    /* [out][in] */ ULONG __RPC_FAR *pcParams,
    /* [size_is][size_is][out] */ DBPARAMINFO __RPC_FAR *__RPC_FAR *prgParamInfo,
    /* [size_is][size_is][out] */ ULONG __RPC_FAR *__RPC_FAR *prgNameOffsets,
    /* [out][in] */ ULONG __RPC_FAR *pcbNamesBuffer,
    /* [size_is][size_is][unique][out][in] */ OLECHAR __RPC_FAR *__RPC_FAR *ppNamesBuffer,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE ICommandWithParameters_MapParameterNames_Proxy( 
    ICommandWithParameters __RPC_FAR * This,
    /* [in] */ ULONG cParamNames,
    /* [size_is][in] */ const OLECHAR __RPC_FAR *__RPC_FAR rgParamNames[  ],
    /* [size_is][out] */ LONG __RPC_FAR rgParamOrdinals[  ]);


/* [call_as] */ HRESULT STDMETHODCALLTYPE ICommandWithParameters_MapParameterNames_Stub( 
    ICommandWithParameters __RPC_FAR * This,
    /* [in] */ ULONG cParamNames,
    /* [size_is][in] */ LPCOLESTR __RPC_FAR *rgParamNames,
    /* [size_is][out] */ LONG __RPC_FAR *rgParamOrdinals,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE ICommandWithParameters_SetParameterInfo_Proxy( 
    ICommandWithParameters __RPC_FAR * This,
    /* [in] */ ULONG cParams,
    /* [size_is][unique][in] */ const ULONG __RPC_FAR rgParamOrdinals[  ],
    /* [size_is][unique][in] */ const DBPARAMBINDINFO __RPC_FAR rgParamBindInfo[  ]);


/* [call_as] */ HRESULT STDMETHODCALLTYPE ICommandWithParameters_SetParameterInfo_Stub( 
    ICommandWithParameters __RPC_FAR * This,
    /* [in] */ ULONG cParams,
    /* [size_is][unique][in] */ const ULONG __RPC_FAR *rgParamOrdinals,
    /* [size_is][unique][in] */ const DBPARAMBINDINFO __RPC_FAR *rgParamBindInfo,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IColumnsRowset_GetAvailableColumns_Proxy( 
    IColumnsRowset __RPC_FAR * This,
    /* [out][in] */ ULONG __RPC_FAR *pcOptColumns,
    /* [size_is][size_is][out] */ DBID __RPC_FAR *__RPC_FAR *prgOptColumns);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IColumnsRowset_GetAvailableColumns_Stub( 
    IColumnsRowset __RPC_FAR * This,
    /* [out][in] */ ULONG __RPC_FAR *pcOptColumns,
    /* [size_is][size_is][out] */ DBID __RPC_FAR *__RPC_FAR *prgOptColumns,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IColumnsRowset_GetColumnsRowset_Proxy( 
    IColumnsRowset __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ ULONG cOptColumns,
    /* [size_is][in] */ const DBID __RPC_FAR rgOptColumns[  ],
    /* [in] */ REFIID riid,
    /* [in] */ ULONG cPropertySets,
    /* [size_is][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ],
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppColRowset);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IColumnsRowset_GetColumnsRowset_Stub( 
    IColumnsRowset __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ ULONG cOptColumns,
    /* [size_is][unique][in] */ const DBID __RPC_FAR *rgOptColumns,
    /* [in] */ REFIID riid,
    /* [in] */ ULONG cPropertySets,
    /* [size_is][unique][in] */ DBPROPSET __RPC_FAR *rgPropertySets,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppColRowset,
    /* [in] */ ULONG cTotalProps,
    /* [size_is][out] */ DBPROPSTATUS __RPC_FAR *rgPropStatus,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IColumnsInfo_GetColumnInfo_Proxy( 
    IColumnsInfo __RPC_FAR * This,
    /* [out][in] */ ULONG __RPC_FAR *pcColumns,
    /* [size_is][size_is][out] */ DBCOLUMNINFO __RPC_FAR *__RPC_FAR *prgInfo,
    /* [out] */ OLECHAR __RPC_FAR *__RPC_FAR *ppStringsBuffer);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IColumnsInfo_GetColumnInfo_Stub( 
    IColumnsInfo __RPC_FAR * This,
    /* [out][in] */ ULONG __RPC_FAR *pcColumns,
    /* [size_is][size_is][out] */ DBCOLUMNINFO __RPC_FAR *__RPC_FAR *prgInfo,
    /* [size_is][size_is][out] */ ULONG __RPC_FAR *__RPC_FAR *prgNameOffsets,
    /* [size_is][size_is][out] */ ULONG __RPC_FAR *__RPC_FAR *prgcolumnidOffsets,
    /* [out][in] */ ULONG __RPC_FAR *pcbStringsBuffer,
    /* [size_is][size_is][unique][out][in] */ OLECHAR __RPC_FAR *__RPC_FAR *ppStringsBuffer,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IColumnsInfo_MapColumnIDs_Proxy( 
    IColumnsInfo __RPC_FAR * This,
    /* [in] */ ULONG cColumnIDs,
    /* [size_is][in] */ const DBID __RPC_FAR rgColumnIDs[  ],
    /* [size_is][out] */ ULONG __RPC_FAR rgColumns[  ]);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IColumnsInfo_MapColumnIDs_Stub( 
    IColumnsInfo __RPC_FAR * This,
    /* [in] */ ULONG cColumnIDs,
    /* [size_is][in] */ const DBID __RPC_FAR *rgColumnIDs,
    /* [size_is][out] */ ULONG __RPC_FAR *rgColumns,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IDBCreateCommand_CreateCommand_Proxy( 
    IDBCreateCommand __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppCommand);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBCreateCommand_CreateCommand_Stub( 
    IDBCreateCommand __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppCommand,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IDBCreateSession_CreateSession_Proxy( 
    IDBCreateSession __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppDBSession);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBCreateSession_CreateSession_Stub( 
    IDBCreateSession __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppDBSession,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE ISourcesRowset_GetSourcesRowset_Proxy( 
    ISourcesRowset __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ REFIID riid,
    /* [in] */ ULONG cPropertySets,
    /* [size_is][unique][out][in] */ DBPROPSET __RPC_FAR rgProperties[  ],
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppSourcesRowset);


/* [call_as] */ HRESULT STDMETHODCALLTYPE ISourcesRowset_GetSourcesRowset_Stub( 
    ISourcesRowset __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ REFIID riid,
    /* [in] */ ULONG cPropertySets,
    /* [size_is][unique][in] */ DBPROPSET __RPC_FAR *rgProperties,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppSourcesRowset,
    /* [in] */ ULONG cTotalProps,
    /* [size_is][out] */ DBPROPSTATUS __RPC_FAR *rgPropStatus,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IDBProperties_GetProperties_Proxy( 
    IDBProperties __RPC_FAR * This,
    /* [in] */ ULONG cPropertyIDSets,
    /* [size_is][in] */ const DBPROPIDSET __RPC_FAR rgPropertyIDSets[  ],
    /* [out][in] */ ULONG __RPC_FAR *pcPropertySets,
    /* [size_is][size_is][out] */ DBPROPSET __RPC_FAR *__RPC_FAR *prgPropertySets);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBProperties_GetProperties_Stub( 
    IDBProperties __RPC_FAR * This,
    /* [in] */ ULONG cPropertyIDSets,
    /* [size_is][unique][in] */ const DBPROPIDSET __RPC_FAR *rgPropertyIDSets,
    /* [out][in] */ ULONG __RPC_FAR *pcPropertySets,
    /* [size_is][size_is][out] */ DBPROPSET __RPC_FAR *__RPC_FAR *prgPropertySets,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IDBProperties_GetPropertyInfo_Proxy( 
    IDBProperties __RPC_FAR * This,
    /* [in] */ ULONG cPropertyIDSets,
    /* [size_is][in] */ const DBPROPIDSET __RPC_FAR rgPropertyIDSets[  ],
    /* [out][in] */ ULONG __RPC_FAR *pcPropertyInfoSets,
    /* [size_is][size_is][out] */ DBPROPINFOSET __RPC_FAR *__RPC_FAR *prgPropertyInfoSets,
    /* [out] */ OLECHAR __RPC_FAR *__RPC_FAR *ppDescBuffer);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBProperties_GetPropertyInfo_Stub( 
    IDBProperties __RPC_FAR * This,
    /* [in] */ ULONG cPropertyIDSets,
    /* [size_is][unique][in] */ const DBPROPIDSET __RPC_FAR *rgPropertyIDSets,
    /* [out][in] */ ULONG __RPC_FAR *pcPropertyInfoSets,
    /* [size_is][size_is][out] */ DBPROPINFOSET __RPC_FAR *__RPC_FAR *prgPropertyInfoSets,
    /* [out][in] */ ULONG __RPC_FAR *pcOffsets,
    /* [size_is][size_is][out] */ ULONG __RPC_FAR *__RPC_FAR *prgDescOffsets,
    /* [out][in] */ ULONG __RPC_FAR *pcbDescBuffer,
    /* [size_is][size_is][unique][out][in] */ OLECHAR __RPC_FAR *__RPC_FAR *ppDescBuffer,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IDBProperties_SetProperties_Proxy( 
    IDBProperties __RPC_FAR * This,
    /* [in] */ ULONG cPropertySets,
    /* [size_is][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ]);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBProperties_SetProperties_Stub( 
    IDBProperties __RPC_FAR * This,
    /* [in] */ ULONG cPropertySets,
    /* [size_is][unique][in] */ DBPROPSET __RPC_FAR *rgPropertySets,
    /* [in] */ ULONG cTotalProps,
    /* [size_is][out] */ DBPROPSTATUS __RPC_FAR *rgPropStatus,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IDBInitialize_Initialize_Proxy( 
    IDBInitialize __RPC_FAR * This);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBInitialize_Initialize_Stub( 
    IDBInitialize __RPC_FAR * This,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IDBInitialize_Uninitialize_Proxy( 
    IDBInitialize __RPC_FAR * This);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBInitialize_Uninitialize_Stub( 
    IDBInitialize __RPC_FAR * This,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IDBInfo_GetKeywords_Proxy( 
    IDBInfo __RPC_FAR * This,
    /* [out] */ LPOLESTR __RPC_FAR *ppwszKeywords);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBInfo_GetKeywords_Stub( 
    IDBInfo __RPC_FAR * This,
    /* [unique][out][in] */ LPOLESTR __RPC_FAR *ppwszKeywords,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IDBInfo_GetLiteralInfo_Proxy( 
    IDBInfo __RPC_FAR * This,
    /* [in] */ ULONG cLiterals,
    /* [size_is][in] */ const DBLITERAL __RPC_FAR rgLiterals[  ],
    /* [out][in] */ ULONG __RPC_FAR *pcLiteralInfo,
    /* [size_is][size_is][out] */ DBLITERALINFO __RPC_FAR *__RPC_FAR *prgLiteralInfo,
    /* [out] */ OLECHAR __RPC_FAR *__RPC_FAR *ppCharBuffer);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBInfo_GetLiteralInfo_Stub( 
    IDBInfo __RPC_FAR * This,
    /* [in] */ ULONG cLiterals,
    /* [size_is][unique][in] */ const DBLITERAL __RPC_FAR *rgLiterals,
    /* [out][in] */ ULONG __RPC_FAR *pcLiteralInfo,
    /* [size_is][size_is][out] */ DBLITERALINFO __RPC_FAR *__RPC_FAR *prgLiteralInfo,
    /* [size_is][size_is][out] */ ULONG __RPC_FAR *__RPC_FAR *prgLVOffsets,
    /* [size_is][size_is][out] */ ULONG __RPC_FAR *__RPC_FAR *prgICOffsets,
    /* [size_is][size_is][out] */ ULONG __RPC_FAR *__RPC_FAR *prgISCOffsets,
    /* [out][in] */ ULONG __RPC_FAR *pcbCharBuffer,
    /* [size_is][size_is][unique][out][in] */ OLECHAR __RPC_FAR *__RPC_FAR *ppCharBuffer,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IDBDataSourceAdmin_CreateDataSource_Proxy( 
    IDBDataSourceAdmin __RPC_FAR * This,
    /* [in] */ ULONG cPropertySets,
    /* [size_is][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ],
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppDBSession);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBDataSourceAdmin_CreateDataSource_Stub( 
    IDBDataSourceAdmin __RPC_FAR * This,
    /* [in] */ ULONG cPropertySets,
    /* [size_is][unique][in] */ DBPROPSET __RPC_FAR *rgPropertySets,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ REFIID riid,
    /* [iid_is][unique][out][in] */ IUnknown __RPC_FAR *__RPC_FAR *ppDBSession,
    /* [in] */ ULONG cTotalProps,
    /* [size_is][out] */ DBPROPSTATUS __RPC_FAR *rgPropStatus,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IDBDataSourceAdmin_DestroyDataSource_Proxy( 
    IDBDataSourceAdmin __RPC_FAR * This);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBDataSourceAdmin_DestroyDataSource_Stub( 
    IDBDataSourceAdmin __RPC_FAR * This,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IDBDataSourceAdmin_GetCreationProperties_Proxy( 
    IDBDataSourceAdmin __RPC_FAR * This,
    /* [in] */ ULONG cPropertyIDSets,
    /* [size_is][in] */ const DBPROPIDSET __RPC_FAR rgPropertyIDSets[  ],
    /* [out][in] */ ULONG __RPC_FAR *pcPropertyInfoSets,
    /* [size_is][size_is][out] */ DBPROPINFOSET __RPC_FAR *__RPC_FAR *prgPropertyInfoSets,
    /* [out] */ OLECHAR __RPC_FAR *__RPC_FAR *ppDescBuffer);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBDataSourceAdmin_GetCreationProperties_Stub( 
    IDBDataSourceAdmin __RPC_FAR * This,
    /* [in] */ ULONG cPropertyIDSets,
    /* [size_is][unique][in] */ const DBPROPIDSET __RPC_FAR *rgPropertyIDSets,
    /* [out][in] */ ULONG __RPC_FAR *pcPropertyInfoSets,
    /* [size_is][size_is][out] */ DBPROPINFOSET __RPC_FAR *__RPC_FAR *prgPropertyInfoSets,
    /* [out][in] */ ULONG __RPC_FAR *pcOffsets,
    /* [size_is][size_is][out] */ ULONG __RPC_FAR *__RPC_FAR *prgDescOffsets,
    /* [out][in] */ ULONG __RPC_FAR *pcbDescBuffer,
    /* [size_is][size_is][unique][out][in] */ OLECHAR __RPC_FAR *__RPC_FAR *ppDescBuffer,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IDBDataSourceAdmin_ModifyDataSource_Proxy( 
    IDBDataSourceAdmin __RPC_FAR * This,
    /* [in] */ ULONG cPropertySets,
    /* [size_is][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ]);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBDataSourceAdmin_ModifyDataSource_Stub( 
    IDBDataSourceAdmin __RPC_FAR * This,
    /* [in] */ ULONG cPropertySets,
    /* [size_is][in] */ DBPROPSET __RPC_FAR *rgPropertySets,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IDBAsynchNotify_OnLowResource_Proxy( 
    IDBAsynchNotify __RPC_FAR * This,
    /* [in] */ DWORD dwReserved);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBAsynchNotify_OnLowResource_Stub( 
    IDBAsynchNotify __RPC_FAR * This,
    /* [in] */ DWORD dwReserved,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IDBAsynchNotify_OnProgress_Proxy( 
    IDBAsynchNotify __RPC_FAR * This,
    /* [in] */ HCHAPTER hChapter,
    /* [in] */ DBASYNCHOP eOperation,
    /* [in] */ ULONG ulProgress,
    /* [in] */ ULONG ulProgressMax,
    /* [in] */ DBASYNCHPHASE eAsynchPhase,
    /* [in] */ LPOLESTR pwszStatusText);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBAsynchNotify_OnProgress_Stub( 
    IDBAsynchNotify __RPC_FAR * This,
    /* [in] */ HCHAPTER hChapter,
    /* [in] */ DBASYNCHOP eOperation,
    /* [in] */ ULONG ulProgress,
    /* [in] */ ULONG ulProgressMax,
    /* [in] */ DBASYNCHPHASE eAsynchPhase,
    /* [in] */ LPOLESTR pwszStatusText,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IDBAsynchNotify_OnStop_Proxy( 
    IDBAsynchNotify __RPC_FAR * This,
    /* [in] */ HCHAPTER hChapter,
    /* [in] */ DBASYNCHOP eOperation,
    /* [in] */ HRESULT hrStatus,
    /* [in] */ LPOLESTR pwszStatusText);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBAsynchNotify_OnStop_Stub( 
    IDBAsynchNotify __RPC_FAR * This,
    /* [in] */ HCHAPTER hChapter,
    /* [in] */ DBASYNCHOP eOperation,
    /* [in] */ HRESULT hrStatus,
    /* [in] */ LPOLESTR pwszStatusText,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IDBAsynchStatus_Abort_Proxy( 
    IDBAsynchStatus __RPC_FAR * This,
    /* [in] */ HCHAPTER hChapter,
    /* [in] */ DBASYNCHOP eOperation);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBAsynchStatus_Abort_Stub( 
    IDBAsynchStatus __RPC_FAR * This,
    /* [in] */ HCHAPTER hChapter,
    /* [in] */ DBASYNCHOP eOperation,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IDBAsynchStatus_GetStatus_Proxy( 
    IDBAsynchStatus __RPC_FAR * This,
    /* [in] */ HCHAPTER hChapter,
    /* [in] */ DBASYNCHOP eOperation,
    /* [out] */ ULONG __RPC_FAR *pulProgress,
    /* [out] */ ULONG __RPC_FAR *pulProgressMax,
    /* [out] */ DBASYNCHPHASE __RPC_FAR *peAsynchPhase,
    /* [out] */ LPOLESTR __RPC_FAR *ppwszStatusText);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBAsynchStatus_GetStatus_Stub( 
    IDBAsynchStatus __RPC_FAR * This,
    /* [in] */ HCHAPTER hChapter,
    /* [in] */ DBASYNCHOP eOperation,
    /* [out] */ ULONG __RPC_FAR *pulProgress,
    /* [out] */ ULONG __RPC_FAR *pulProgressMax,
    /* [out] */ DBASYNCHPHASE __RPC_FAR *peAsynchPhase,
    /* [out] */ LPOLESTR __RPC_FAR *ppwszStatusText,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE ISessionProperties_GetProperties_Proxy( 
    ISessionProperties __RPC_FAR * This,
    /* [in] */ ULONG cPropertyIDSets,
    /* [size_is][in] */ const DBPROPIDSET __RPC_FAR rgPropertyIDSets[  ],
    /* [out][in] */ ULONG __RPC_FAR *pcPropertySets,
    /* [size_is][size_is][out] */ DBPROPSET __RPC_FAR *__RPC_FAR *prgPropertySets);


/* [call_as] */ HRESULT STDMETHODCALLTYPE ISessionProperties_GetProperties_Stub( 
    ISessionProperties __RPC_FAR * This,
    /* [in] */ ULONG cPropertyIDSets,
    /* [size_is][unique][in] */ const DBPROPIDSET __RPC_FAR *rgPropertyIDSets,
    /* [out][in] */ ULONG __RPC_FAR *pcPropertySets,
    /* [size_is][size_is][out] */ DBPROPSET __RPC_FAR *__RPC_FAR *prgPropertySets,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE ISessionProperties_SetProperties_Proxy( 
    ISessionProperties __RPC_FAR * This,
    /* [in] */ ULONG cPropertySets,
    /* [size_is][unique][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ]);


/* [call_as] */ HRESULT STDMETHODCALLTYPE ISessionProperties_SetProperties_Stub( 
    ISessionProperties __RPC_FAR * This,
    /* [in] */ ULONG cPropertySets,
    /* [size_is][unique][in] */ DBPROPSET __RPC_FAR *rgPropertySets,
    /* [in] */ ULONG cTotalProps,
    /* [size_is][out] */ DBPROPSTATUS __RPC_FAR *rgPropStatus,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IIndexDefinition_CreateIndex_Proxy( 
    IIndexDefinition __RPC_FAR * This,
    /* [in] */ DBID __RPC_FAR *pTableID,
    /* [in] */ DBID __RPC_FAR *pIndexID,
    /* [in] */ ULONG cIndexColumnDescs,
    /* [size_is][in] */ const DBINDEXCOLUMNDESC __RPC_FAR rgIndexColumnDescs[  ],
    /* [in] */ ULONG cPropertySets,
    /* [size_is][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ],
    /* [out] */ DBID __RPC_FAR *__RPC_FAR *ppIndexID);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IIndexDefinition_CreateIndex_Stub( 
    IIndexDefinition __RPC_FAR * This,
    /* [in] */ DBID __RPC_FAR *pTableID,
    /* [unique][in] */ DBID __RPC_FAR *pIndexID,
    /* [in] */ ULONG cIndexColumnDescs,
    /* [size_is][in] */ const DBINDEXCOLUMNDESC __RPC_FAR *rgIndexColumnDescs,
    /* [in] */ ULONG cPropertySets,
    /* [size_is][unique][in] */ DBPROPSET __RPC_FAR *rgPropertySets,
    /* [unique][out][in] */ DBID __RPC_FAR *__RPC_FAR *ppIndexID,
    /* [in] */ ULONG cTotalProps,
    /* [size_is][out] */ DBPROPSTATUS __RPC_FAR *rgPropStatus,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IIndexDefinition_DropIndex_Proxy( 
    IIndexDefinition __RPC_FAR * This,
    /* [unique][in] */ DBID __RPC_FAR *pTableID,
    /* [unique][in] */ DBID __RPC_FAR *pIndexID);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IIndexDefinition_DropIndex_Stub( 
    IIndexDefinition __RPC_FAR * This,
    /* [unique][in] */ DBID __RPC_FAR *pTableID,
    /* [unique][in] */ DBID __RPC_FAR *pIndexID,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE ITableDefinition_CreateTable_Proxy( 
    ITableDefinition __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ DBID __RPC_FAR *pTableID,
    /* [in] */ ULONG cColumnDescs,
    /* [size_is][in] */ const DBCOLUMNDESC __RPC_FAR rgColumnDescs[  ],
    /* [in] */ REFIID riid,
    /* [in] */ ULONG cPropertySets,
    /* [size_is][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ],
    /* [out] */ DBID __RPC_FAR *__RPC_FAR *ppTableID,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset);


/* [call_as] */ HRESULT STDMETHODCALLTYPE ITableDefinition_CreateTable_Stub( 
    ITableDefinition __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [unique][in] */ DBID __RPC_FAR *pTableID,
    /* [in] */ ULONG cColumnDescs,
    /* [size_is][in] */ const DBCOLUMNDESC __RPC_FAR *rgColumnDescs,
    /* [in] */ REFIID riid,
    /* [in] */ ULONG cPropertySets,
    /* [size_is][unique][out][in] */ DBPROPSET __RPC_FAR *rgPropertySets,
    /* [unique][out][in] */ DBID __RPC_FAR *__RPC_FAR *ppTableID,
    /* [iid_is][unique][out][in] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset,
    /* [in] */ ULONG cTotalProps,
    /* [size_is][out] */ DBPROPSTATUS __RPC_FAR *rgPropStatus,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE ITableDefinition_DropTable_Proxy( 
    ITableDefinition __RPC_FAR * This,
    /* [unique][in] */ DBID __RPC_FAR *pTableID);


/* [call_as] */ HRESULT STDMETHODCALLTYPE ITableDefinition_DropTable_Stub( 
    ITableDefinition __RPC_FAR * This,
    /* [unique][in] */ DBID __RPC_FAR *pTableID,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE ITableDefinition_AddColumn_Proxy( 
    ITableDefinition __RPC_FAR * This,
    /* [in] */ DBID __RPC_FAR *pTableID,
    /* [out][in] */ DBCOLUMNDESC __RPC_FAR *pColumnDesc,
    /* [out] */ DBID __RPC_FAR *__RPC_FAR *ppColumnID);


/* [call_as] */ HRESULT STDMETHODCALLTYPE ITableDefinition_AddColumn_Stub( 
    ITableDefinition __RPC_FAR * This,
    /* [in] */ DBID __RPC_FAR *pTableID,
    /* [out][in] */ DBCOLUMNDESC __RPC_FAR *pColumnDesc,
    /* [unique][out][in] */ DBID __RPC_FAR *__RPC_FAR *ppColumnID,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE ITableDefinition_DropColumn_Proxy( 
    ITableDefinition __RPC_FAR * This,
    /* [unique][in] */ DBID __RPC_FAR *pTableID,
    /* [unique][in] */ DBID __RPC_FAR *pColumnID);


/* [call_as] */ HRESULT STDMETHODCALLTYPE ITableDefinition_DropColumn_Stub( 
    ITableDefinition __RPC_FAR * This,
    /* [unique][in] */ DBID __RPC_FAR *pTableID,
    /* [unique][in] */ DBID __RPC_FAR *pColumnID,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IOpenRowset_OpenRowset_Proxy( 
    IOpenRowset __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [unique][in] */ DBID __RPC_FAR *pTableID,
    /* [unique][in] */ DBID __RPC_FAR *pIndexID,
    /* [in] */ REFIID riid,
    /* [in] */ ULONG cPropertySets,
    /* [size_is][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ],
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IOpenRowset_OpenRowset_Stub( 
    IOpenRowset __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [unique][in] */ DBID __RPC_FAR *pTableID,
    /* [unique][in] */ DBID __RPC_FAR *pIndexID,
    /* [in] */ REFIID riid,
    /* [in] */ ULONG cPropertySets,
    /* [size_is][unique][in] */ DBPROPSET __RPC_FAR *rgPropertySets,
    /* [iid_is][unique][out][in] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset,
    /* [in] */ ULONG cTotalProps,
    /* [size_is][out] */ DBPROPSTATUS __RPC_FAR *rgPropStatus,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IDBSchemaRowset_GetRowset_Proxy( 
    IDBSchemaRowset __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ REFGUID rguidSchema,
    /* [in] */ ULONG cRestrictions,
    /* [size_is][in] */ const VARIANT __RPC_FAR rgRestrictions[  ],
    /* [in] */ REFIID riid,
    /* [in] */ ULONG cPropertySets,
    /* [size_is][unique][out][in] */ DBPROPSET __RPC_FAR rgPropertySets[  ],
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBSchemaRowset_GetRowset_Stub( 
    IDBSchemaRowset __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ REFGUID rguidSchema,
    /* [in] */ ULONG cRestrictions,
    /* [size_is][unique][in] */ const VARIANT __RPC_FAR *rgRestrictions,
    /* [in] */ REFIID riid,
    /* [in] */ ULONG cPropertySets,
    /* [size_is][unique][in] */ DBPROPSET __RPC_FAR *rgPropertySets,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset,
    /* [in] */ ULONG cTotalProps,
    /* [size_is][out] */ DBPROPSTATUS __RPC_FAR *rgPropStatus,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IDBSchemaRowset_GetSchemas_Proxy( 
    IDBSchemaRowset __RPC_FAR * This,
    /* [out][in] */ ULONG __RPC_FAR *pcSchemas,
    /* [size_is][size_is][out] */ GUID __RPC_FAR *__RPC_FAR *prgSchemas,
    /* [size_is][size_is][out] */ ULONG __RPC_FAR *__RPC_FAR *prgRestrictionSupport);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IDBSchemaRowset_GetSchemas_Stub( 
    IDBSchemaRowset __RPC_FAR * This,
    /* [out][in] */ ULONG __RPC_FAR *pcSchemas,
    /* [size_is][size_is][out] */ GUID __RPC_FAR *__RPC_FAR *prgSchemas,
    /* [size_is][size_is][out] */ ULONG __RPC_FAR *__RPC_FAR *prgRestrictionSupport,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IErrorRecords_AddErrorRecord_Proxy( 
    IErrorRecords __RPC_FAR * This,
    /* [in] */ ERRORINFO __RPC_FAR *pErrorInfo,
    /* [in] */ DWORD dwLookupID,
    /* [in] */ DISPPARAMS __RPC_FAR *pdispparams,
    /* [in] */ IUnknown __RPC_FAR *punkCustomError,
    /* [in] */ DWORD dwDynamicErrorID);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IErrorRecords_AddErrorRecord_Stub( 
    IErrorRecords __RPC_FAR * This,
    /* [in] */ ERRORINFO __RPC_FAR *pErrorInfo,
    /* [in] */ DWORD dwLookupID,
    /* [in] */ DISPPARAMS __RPC_FAR *pdispparams,
    /* [in] */ IUnknown __RPC_FAR *punkCustomError,
    /* [in] */ DWORD dwDynamicErrorID,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IErrorRecords_GetBasicErrorInfo_Proxy( 
    IErrorRecords __RPC_FAR * This,
    /* [in] */ ULONG ulRecordNum,
    /* [out] */ ERRORINFO __RPC_FAR *pErrorInfo);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IErrorRecords_GetBasicErrorInfo_Stub( 
    IErrorRecords __RPC_FAR * This,
    /* [in] */ ULONG ulRecordNum,
    /* [out] */ ERRORINFO __RPC_FAR *pErrorInfo,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IErrorRecords_GetCustomErrorObject_Proxy( 
    IErrorRecords __RPC_FAR * This,
    /* [in] */ ULONG ulRecordNum,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppObject);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IErrorRecords_GetCustomErrorObject_Stub( 
    IErrorRecords __RPC_FAR * This,
    /* [in] */ ULONG ulRecordNum,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppObject,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IErrorRecords_GetErrorInfo_Proxy( 
    IErrorRecords __RPC_FAR * This,
    /* [in] */ ULONG ulRecordNum,
    /* [in] */ LCID lcid,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfo);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IErrorRecords_GetErrorInfo_Stub( 
    IErrorRecords __RPC_FAR * This,
    /* [in] */ ULONG ulRecordNum,
    /* [in] */ LCID lcid,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfo,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IErrorRecords_GetErrorParameters_Proxy( 
    IErrorRecords __RPC_FAR * This,
    /* [in] */ ULONG ulRecordNum,
    /* [out] */ DISPPARAMS __RPC_FAR *pdispparams);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IErrorRecords_GetErrorParameters_Stub( 
    IErrorRecords __RPC_FAR * This,
    /* [in] */ ULONG ulRecordNum,
    /* [out] */ DISPPARAMS __RPC_FAR *pdispparams,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IErrorRecords_GetRecordCount_Proxy( 
    IErrorRecords __RPC_FAR * This,
    /* [out] */ ULONG __RPC_FAR *pcRecords);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IErrorRecords_GetRecordCount_Stub( 
    IErrorRecords __RPC_FAR * This,
    /* [out] */ ULONG __RPC_FAR *pcRecords,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IErrorLookup_GetErrorDescription_Proxy( 
    IErrorLookup __RPC_FAR * This,
    /* [in] */ HRESULT hrError,
    /* [in] */ DWORD dwLookupID,
    /* [in] */ DISPPARAMS __RPC_FAR *pdispparams,
    /* [in] */ LCID lcid,
    /* [out] */ BSTR __RPC_FAR *pbstrSource,
    /* [out] */ BSTR __RPC_FAR *pbstrDescription);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IErrorLookup_GetErrorDescription_Stub( 
    IErrorLookup __RPC_FAR * This,
    /* [in] */ HRESULT hrError,
    /* [in] */ DWORD dwLookupID,
    /* [in] */ DISPPARAMS __RPC_FAR *pdispparams,
    /* [in] */ LCID lcid,
    /* [out] */ BSTR __RPC_FAR *pbstrSource,
    /* [out] */ BSTR __RPC_FAR *pbstrDescription,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IErrorLookup_GetHelpInfo_Proxy( 
    IErrorLookup __RPC_FAR * This,
    /* [in] */ HRESULT hrError,
    /* [in] */ DWORD dwLookupID,
    /* [in] */ LCID lcid,
    /* [out] */ BSTR __RPC_FAR *pbstrHelpFile,
    /* [out] */ DWORD __RPC_FAR *pdwHelpContext);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IErrorLookup_GetHelpInfo_Stub( 
    IErrorLookup __RPC_FAR * This,
    /* [in] */ HRESULT hrError,
    /* [in] */ DWORD dwLookupID,
    /* [in] */ LCID lcid,
    /* [out] */ BSTR __RPC_FAR *pbstrHelpFile,
    /* [out] */ DWORD __RPC_FAR *pdwHelpContext,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IErrorLookup_ReleaseErrors_Proxy( 
    IErrorLookup __RPC_FAR * This,
    /* [in] */ const DWORD dwDynamicErrorID);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IErrorLookup_ReleaseErrors_Stub( 
    IErrorLookup __RPC_FAR * This,
    /* [in] */ const DWORD dwDynamicErrorID,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE ISQLErrorInfo_GetSQLInfo_Proxy( 
    ISQLErrorInfo __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pbstrSQLState,
    /* [out] */ LONG __RPC_FAR *plNativeError);


/* [call_as] */ HRESULT STDMETHODCALLTYPE ISQLErrorInfo_GetSQLInfo_Stub( 
    ISQLErrorInfo __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pbstrSQLState,
    /* [out] */ LONG __RPC_FAR *plNativeError,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE IGetDataSource_GetDataSource_Proxy( 
    IGetDataSource __RPC_FAR * This,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppDataSource);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IGetDataSource_GetDataSource_Stub( 
    IGetDataSource __RPC_FAR * This,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppDataSource,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE ITransactionJoin_GetOptionsObject_Proxy( 
    ITransactionJoin __RPC_FAR * This,
    /* [out] */ ITransactionOptions __RPC_FAR *__RPC_FAR *ppOptions);


/* [call_as] */ HRESULT STDMETHODCALLTYPE ITransactionJoin_GetOptionsObject_Stub( 
    ITransactionJoin __RPC_FAR * This,
    /* [out] */ ITransactionOptions __RPC_FAR *__RPC_FAR *ppOptions,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE ITransactionJoin_JoinTransaction_Proxy( 
    ITransactionJoin __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *punkTransactionCoord,
    /* [in] */ ISOLEVEL isoLevel,
    /* [in] */ ULONG isoFlags,
    /* [in] */ ITransactionOptions __RPC_FAR *pOtherOptions);


/* [call_as] */ HRESULT STDMETHODCALLTYPE ITransactionJoin_JoinTransaction_Stub( 
    ITransactionJoin __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *punkTransactionCoord,
    /* [in] */ ISOLEVEL isoLevel,
    /* [in] */ ULONG isoFlags,
    /* [in] */ ITransactionOptions __RPC_FAR *pOtherOptions,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);

/* [local] */ HRESULT STDMETHODCALLTYPE ITransactionObject_GetTransactionObject_Proxy( 
    ITransactionObject __RPC_FAR * This,
    /* [in] */ ULONG ulTransactionLevel,
    /* [out] */ ITransaction __RPC_FAR *__RPC_FAR *ppTransactionObject);


/* [call_as] */ HRESULT STDMETHODCALLTYPE ITransactionObject_GetTransactionObject_Stub( 
    ITransactionObject __RPC_FAR * This,
    /* [in] */ ULONG ulTransactionLevel,
    /* [out] */ ITransaction __RPC_FAR *__RPC_FAR *ppTransactionObject,
    /* [out] */ IErrorInfo __RPC_FAR *__RPC_FAR *ppErrorInfoRem);



/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
