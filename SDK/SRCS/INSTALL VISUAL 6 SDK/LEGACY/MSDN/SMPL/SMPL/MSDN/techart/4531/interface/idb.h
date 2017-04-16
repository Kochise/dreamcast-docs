/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 2.00.0102 */
/* at Wed Oct 18 18:02:19 1995
 */
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"
#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __idb_h__
#define __idb_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IDB_FWD_DEFINED__
#define __IDB_FWD_DEFINED__
typedef interface IDB IDB;
#endif 	/* __IDB_FWD_DEFINED__ */


#ifndef __IDBAccess_FWD_DEFINED__
#define __IDBAccess_FWD_DEFINED__
typedef interface IDBAccess IDBAccess;
#endif 	/* __IDBAccess_FWD_DEFINED__ */


#ifndef __IDBManage_FWD_DEFINED__
#define __IDBManage_FWD_DEFINED__
typedef interface IDBManage IDBManage;
#endif 	/* __IDBManage_FWD_DEFINED__ */


#ifndef __IDBInfo_FWD_DEFINED__
#define __IDBInfo_FWD_DEFINED__
typedef interface IDBInfo IDBInfo;
#endif 	/* __IDBInfo_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "refshort.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IDB_INTERFACE_DEFINED__
#define __IDB_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDB
 * at Wed Oct 18 18:02:19 1995
 * using MIDL 2.00.0102
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IDB;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IDB : public IUnknown
    {
    public:
        virtual HRESULT __stdcall Read( 
            /* [in] */ short nTable,
            /* [in] */ short nRow,
            /* [size_is][out] */ LPWSTR lpszData) = 0;
        
        virtual HRESULT __stdcall Write( 
            /* [in] */ short nTable,
            /* [in] */ short nRow,
            /* [in] */ LPCWSTR lpszData) = 0;
        
        virtual HRESULT __stdcall Create( 
            /* [out] */ REFSHORT nTable,
            /* [in] */ LPCWSTR lpszName) = 0;
        
        virtual HRESULT __stdcall Delete( 
            /* [in] */ short nTable) = 0;
        
        virtual HRESULT __stdcall GetNumTables( 
            /* [out] */ REFSHORT nNumTables) = 0;
        
        virtual HRESULT __stdcall GetTableName( 
            /* [in] */ short nTable,
            /* [size_is][out] */ LPWSTR lpszName) = 0;
        
        virtual HRESULT __stdcall GetNumRows( 
            /* [in] */ short nTable,
            /* [out] */ REFSHORT nRows) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDBVtbl
    {
        
        HRESULT ( __stdcall __RPC_FAR *QueryInterface )( 
            IDB __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( __stdcall __RPC_FAR *AddRef )( 
            IDB __RPC_FAR * This);
        
        ULONG ( __stdcall __RPC_FAR *Release )( 
            IDB __RPC_FAR * This);
        
        HRESULT ( __stdcall __RPC_FAR *Read )( 
            IDB __RPC_FAR * This,
            /* [in] */ short nTable,
            /* [in] */ short nRow,
            /* [size_is][out] */ LPWSTR lpszData);
        
        HRESULT ( __stdcall __RPC_FAR *Write )( 
            IDB __RPC_FAR * This,
            /* [in] */ short nTable,
            /* [in] */ short nRow,
            /* [in] */ LPCWSTR lpszData);
        
        HRESULT ( __stdcall __RPC_FAR *Create )( 
            IDB __RPC_FAR * This,
            /* [out] */ REFSHORT nTable,
            /* [in] */ LPCWSTR lpszName);
        
        HRESULT ( __stdcall __RPC_FAR *Delete )( 
            IDB __RPC_FAR * This,
            /* [in] */ short nTable);
        
        HRESULT ( __stdcall __RPC_FAR *GetNumTables )( 
            IDB __RPC_FAR * This,
            /* [out] */ REFSHORT nNumTables);
        
        HRESULT ( __stdcall __RPC_FAR *GetTableName )( 
            IDB __RPC_FAR * This,
            /* [in] */ short nTable,
            /* [size_is][out] */ LPWSTR lpszName);
        
        HRESULT ( __stdcall __RPC_FAR *GetNumRows )( 
            IDB __RPC_FAR * This,
            /* [in] */ short nTable,
            /* [out] */ REFSHORT nRows);
        
    } IDBVtbl;

    interface IDB
    {
        CONST_VTBL struct IDBVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDB_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDB_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDB_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDB_Read(This,nTable,nRow,lpszData)	\
    (This)->lpVtbl -> Read(This,nTable,nRow,lpszData)

#define IDB_Write(This,nTable,nRow,lpszData)	\
    (This)->lpVtbl -> Write(This,nTable,nRow,lpszData)

#define IDB_Create(This,nTable,lpszName)	\
    (This)->lpVtbl -> Create(This,nTable,lpszName)

#define IDB_Delete(This,nTable)	\
    (This)->lpVtbl -> Delete(This,nTable)

#define IDB_GetNumTables(This,nNumTables)	\
    (This)->lpVtbl -> GetNumTables(This,nNumTables)

#define IDB_GetTableName(This,nTable,lpszName)	\
    (This)->lpVtbl -> GetTableName(This,nTable,lpszName)

#define IDB_GetNumRows(This,nTable,nRows)	\
    (This)->lpVtbl -> GetNumRows(This,nTable,nRows)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT __stdcall IDB_Read_Proxy( 
    IDB __RPC_FAR * This,
    /* [in] */ short nTable,
    /* [in] */ short nRow,
    /* [size_is][out] */ LPWSTR lpszData);


void __RPC_STUB IDB_Read_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT __stdcall IDB_Write_Proxy( 
    IDB __RPC_FAR * This,
    /* [in] */ short nTable,
    /* [in] */ short nRow,
    /* [in] */ LPCWSTR lpszData);


void __RPC_STUB IDB_Write_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT __stdcall IDB_Create_Proxy( 
    IDB __RPC_FAR * This,
    /* [out] */ REFSHORT nTable,
    /* [in] */ LPCWSTR lpszName);


void __RPC_STUB IDB_Create_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT __stdcall IDB_Delete_Proxy( 
    IDB __RPC_FAR * This,
    /* [in] */ short nTable);


void __RPC_STUB IDB_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT __stdcall IDB_GetNumTables_Proxy( 
    IDB __RPC_FAR * This,
    /* [out] */ REFSHORT nNumTables);


void __RPC_STUB IDB_GetNumTables_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT __stdcall IDB_GetTableName_Proxy( 
    IDB __RPC_FAR * This,
    /* [in] */ short nTable,
    /* [size_is][out] */ LPWSTR lpszName);


void __RPC_STUB IDB_GetTableName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT __stdcall IDB_GetNumRows_Proxy( 
    IDB __RPC_FAR * This,
    /* [in] */ short nTable,
    /* [out] */ REFSHORT nRows);


void __RPC_STUB IDB_GetNumRows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDB_INTERFACE_DEFINED__ */


#ifndef __IDBAccess_INTERFACE_DEFINED__
#define __IDBAccess_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDBAccess
 * at Wed Oct 18 18:02:19 1995
 * using MIDL 2.00.0102
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IDBAccess;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IDBAccess : public IUnknown
    {
    public:
        virtual HRESULT __stdcall Read( 
            /* [in] */ short nTable,
            /* [in] */ short nRow,
            /* [size_is][out] */ LPWSTR lpszData) = 0;
        
        virtual HRESULT __stdcall Write( 
            /* [in] */ short nTable,
            /* [in] */ short nRow,
            /* [in] */ LPCWSTR lpszData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDBAccessVtbl
    {
        
        HRESULT ( __stdcall __RPC_FAR *QueryInterface )( 
            IDBAccess __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( __stdcall __RPC_FAR *AddRef )( 
            IDBAccess __RPC_FAR * This);
        
        ULONG ( __stdcall __RPC_FAR *Release )( 
            IDBAccess __RPC_FAR * This);
        
        HRESULT ( __stdcall __RPC_FAR *Read )( 
            IDBAccess __RPC_FAR * This,
            /* [in] */ short nTable,
            /* [in] */ short nRow,
            /* [size_is][out] */ LPWSTR lpszData);
        
        HRESULT ( __stdcall __RPC_FAR *Write )( 
            IDBAccess __RPC_FAR * This,
            /* [in] */ short nTable,
            /* [in] */ short nRow,
            /* [in] */ LPCWSTR lpszData);
        
    } IDBAccessVtbl;

    interface IDBAccess
    {
        CONST_VTBL struct IDBAccessVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDBAccess_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDBAccess_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDBAccess_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDBAccess_Read(This,nTable,nRow,lpszData)	\
    (This)->lpVtbl -> Read(This,nTable,nRow,lpszData)

#define IDBAccess_Write(This,nTable,nRow,lpszData)	\
    (This)->lpVtbl -> Write(This,nTable,nRow,lpszData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT __stdcall IDBAccess_Read_Proxy( 
    IDBAccess __RPC_FAR * This,
    /* [in] */ short nTable,
    /* [in] */ short nRow,
    /* [size_is][out] */ LPWSTR lpszData);


void __RPC_STUB IDBAccess_Read_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT __stdcall IDBAccess_Write_Proxy( 
    IDBAccess __RPC_FAR * This,
    /* [in] */ short nTable,
    /* [in] */ short nRow,
    /* [in] */ LPCWSTR lpszData);


void __RPC_STUB IDBAccess_Write_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDBAccess_INTERFACE_DEFINED__ */


#ifndef __IDBManage_INTERFACE_DEFINED__
#define __IDBManage_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDBManage
 * at Wed Oct 18 18:02:19 1995
 * using MIDL 2.00.0102
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IDBManage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IDBManage : public IUnknown
    {
    public:
        virtual HRESULT __stdcall Create( 
            /* [out] */ REFSHORT nTable,
            /* [in] */ LPCWSTR lpszName) = 0;
        
        virtual HRESULT __stdcall Delete( 
            /* [in] */ short nTable) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDBManageVtbl
    {
        
        HRESULT ( __stdcall __RPC_FAR *QueryInterface )( 
            IDBManage __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( __stdcall __RPC_FAR *AddRef )( 
            IDBManage __RPC_FAR * This);
        
        ULONG ( __stdcall __RPC_FAR *Release )( 
            IDBManage __RPC_FAR * This);
        
        HRESULT ( __stdcall __RPC_FAR *Create )( 
            IDBManage __RPC_FAR * This,
            /* [out] */ REFSHORT nTable,
            /* [in] */ LPCWSTR lpszName);
        
        HRESULT ( __stdcall __RPC_FAR *Delete )( 
            IDBManage __RPC_FAR * This,
            /* [in] */ short nTable);
        
    } IDBManageVtbl;

    interface IDBManage
    {
        CONST_VTBL struct IDBManageVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDBManage_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDBManage_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDBManage_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDBManage_Create(This,nTable,lpszName)	\
    (This)->lpVtbl -> Create(This,nTable,lpszName)

#define IDBManage_Delete(This,nTable)	\
    (This)->lpVtbl -> Delete(This,nTable)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT __stdcall IDBManage_Create_Proxy( 
    IDBManage __RPC_FAR * This,
    /* [out] */ REFSHORT nTable,
    /* [in] */ LPCWSTR lpszName);


void __RPC_STUB IDBManage_Create_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT __stdcall IDBManage_Delete_Proxy( 
    IDBManage __RPC_FAR * This,
    /* [in] */ short nTable);


void __RPC_STUB IDBManage_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDBManage_INTERFACE_DEFINED__ */


#ifndef __IDBInfo_INTERFACE_DEFINED__
#define __IDBInfo_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDBInfo
 * at Wed Oct 18 18:02:19 1995
 * using MIDL 2.00.0102
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IDBInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IDBInfo : public IUnknown
    {
    public:
        virtual HRESULT __stdcall GetNumTables( 
            /* [out] */ REFSHORT nNumTables) = 0;
        
        virtual HRESULT __stdcall GetTableName( 
            /* [in] */ short nTable,
            /* [size_is][out] */ LPWSTR lpszName) = 0;
        
        virtual HRESULT __stdcall GetNumRows( 
            /* [in] */ short nTable,
            /* [out] */ REFSHORT nRows) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDBInfoVtbl
    {
        
        HRESULT ( __stdcall __RPC_FAR *QueryInterface )( 
            IDBInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( __stdcall __RPC_FAR *AddRef )( 
            IDBInfo __RPC_FAR * This);
        
        ULONG ( __stdcall __RPC_FAR *Release )( 
            IDBInfo __RPC_FAR * This);
        
        HRESULT ( __stdcall __RPC_FAR *GetNumTables )( 
            IDBInfo __RPC_FAR * This,
            /* [out] */ REFSHORT nNumTables);
        
        HRESULT ( __stdcall __RPC_FAR *GetTableName )( 
            IDBInfo __RPC_FAR * This,
            /* [in] */ short nTable,
            /* [size_is][out] */ LPWSTR lpszName);
        
        HRESULT ( __stdcall __RPC_FAR *GetNumRows )( 
            IDBInfo __RPC_FAR * This,
            /* [in] */ short nTable,
            /* [out] */ REFSHORT nRows);
        
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


#define IDBInfo_GetNumTables(This,nNumTables)	\
    (This)->lpVtbl -> GetNumTables(This,nNumTables)

#define IDBInfo_GetTableName(This,nTable,lpszName)	\
    (This)->lpVtbl -> GetTableName(This,nTable,lpszName)

#define IDBInfo_GetNumRows(This,nTable,nRows)	\
    (This)->lpVtbl -> GetNumRows(This,nTable,nRows)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT __stdcall IDBInfo_GetNumTables_Proxy( 
    IDBInfo __RPC_FAR * This,
    /* [out] */ REFSHORT nNumTables);


void __RPC_STUB IDBInfo_GetNumTables_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT __stdcall IDBInfo_GetTableName_Proxy( 
    IDBInfo __RPC_FAR * This,
    /* [in] */ short nTable,
    /* [size_is][out] */ LPWSTR lpszName);


void __RPC_STUB IDBInfo_GetTableName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT __stdcall IDBInfo_GetNumRows_Proxy( 
    IDBInfo __RPC_FAR * This,
    /* [in] */ short nTable,
    /* [out] */ REFSHORT nRows);


void __RPC_STUB IDBInfo_GetNumRows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDBInfo_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
