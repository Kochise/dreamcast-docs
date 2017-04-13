/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Wed Feb 04 11:49:00 1998
 */
/* Compiler settings for .\ADOSamp.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __ADOSamp_h__
#define __ADOSamp_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IADOTier_FWD_DEFINED__
#define __IADOTier_FWD_DEFINED__
typedef interface IADOTier IADOTier;
#endif 	/* __IADOTier_FWD_DEFINED__ */


#ifndef __CADOTier_FWD_DEFINED__
#define __CADOTier_FWD_DEFINED__

#ifdef __cplusplus
typedef class CADOTier CADOTier;
#else
typedef struct CADOTier CADOTier;
#endif /* __cplusplus */

#endif 	/* __CADOTier_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL_itf_ADOSamp_0000
 * at Wed Feb 04 11:49:00 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [local] */ 



enum DataTypeEnum
    {	adEmpty	= 0,
	adTinyInt	= 16,
	adSmallInt	= 2,
	adInteger	= 3,
	adBigInt	= 20,
	adUnsignedTinyInt	= 17,
	adUnsignedSmallInt	= 18,
	adUnsignedInt	= 19,
	adUnsignedBigInt	= 21,
	adSingle	= 4,
	adDouble	= 5,
	adCurrency	= 6,
	adDecimal	= 14,
	adNumeric	= 131,
	adBoolean	= 11,
	adError	= 10,
	adUserDefined	= 132,
	adVariant	= 12,
	adIDispatch	= 9,
	adIUnknown	= 13,
	adGUID	= 72,
	adDate	= 7,
	adDBDate	= 133,
	adDBTime	= 134,
	adDBTimeStamp	= 135,
	adBSTR	= 8,
	adChar	= 129,
	adVarChar	= 200,
	adLongVarChar	= 201,
	adWChar	= 130,
	adVarWChar	= 202,
	adLongVarWChar	= 203,
	adBinary	= 128,
	adVarBinary	= 204,
	adLongVarBinary	= 205
    };

enum ParameterDirectionEnum
    {	adParamUnknown	= 0,
	adParamInput	= 1,
	adParamOutput	= 2,
	adParamInputOutput	= 3,
	adParamReturnValue	= 4
    };


extern RPC_IF_HANDLE __MIDL_itf_ADOSamp_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_ADOSamp_0000_v0_0_s_ifspec;

#ifndef __IADOTier_INTERFACE_DEFINED__
#define __IADOTier_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IADOTier
 * at Wed Feb 04 11:49:00 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IADOTier;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7A319993-48C0-11D0-AE70-00C04FD7D06E")
    IADOTier : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Open( 
            /* [in] */ BSTR source,
            /* [in] */ BSTR user,
            /* [in] */ BSTR pwd) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenRecordset( 
            /* [in] */ VARIANT query) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CloseRecordset( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ExecuteConnection( 
            /* [in] */ BSTR query,
            /* [in] */ VARIANT_BOOL bChangeRec) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ExecuteCommand( 
            /* [in] */ VARIANT_BOOL bStoredProcedure,
            /* [in] */ VARIANT_BOOL bChangeRec) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CommandText( 
            /* [retval][out] */ BSTR __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CommandText( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AppendParameter( 
            /* [in] */ enum DataTypeEnum type,
            /* [in] */ VARIANT value,
            /* [in] */ enum ParameterDirectionEnum where,
            /* [in] */ long size) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Update( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Delete( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Field( 
            /* [in] */ VARIANT idx,
            /* [retval][out] */ VARIANT __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Field( 
            /* [in] */ VARIANT idx,
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FieldCount( 
            /* [retval][out] */ long __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE First( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Next( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Last( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Prev( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EOF( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BOF( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ParamQuery( 
            /* [in] */ BSTR query,
            /* [in] */ long idx1,
            /* [in] */ BSTR idx2,
            /* [in] */ BSTR idx3) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CallStoredProc( 
            /* [in] */ long idx1,
            /* [in] */ BSTR idx2,
            /* [in] */ BSTR idx3) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StoredProc( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ChangeParameter( 
            /* [in] */ long idx,
            /* [in] */ enum DataTypeEnum type,
            /* [in] */ VARIANT value,
            /* [in] */ enum ParameterDirectionEnum where,
            /* [in] */ long size) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Requery( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ADORelease( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Empty( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *bEmpty) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADOTierVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADOTier __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADOTier __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADOTier __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADOTier __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADOTier __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADOTier __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADOTier __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Open )( 
            IADOTier __RPC_FAR * This,
            /* [in] */ BSTR source,
            /* [in] */ BSTR user,
            /* [in] */ BSTR pwd);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenRecordset )( 
            IADOTier __RPC_FAR * This,
            /* [in] */ VARIANT query);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CloseRecordset )( 
            IADOTier __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ExecuteConnection )( 
            IADOTier __RPC_FAR * This,
            /* [in] */ BSTR query,
            /* [in] */ VARIANT_BOOL bChangeRec);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ExecuteCommand )( 
            IADOTier __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL bStoredProcedure,
            /* [in] */ VARIANT_BOOL bChangeRec);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CommandText )( 
            IADOTier __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CommandText )( 
            IADOTier __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AppendParameter )( 
            IADOTier __RPC_FAR * This,
            /* [in] */ enum DataTypeEnum type,
            /* [in] */ VARIANT value,
            /* [in] */ enum ParameterDirectionEnum where,
            /* [in] */ long size);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Update )( 
            IADOTier __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            IADOTier __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Field )( 
            IADOTier __RPC_FAR * This,
            /* [in] */ VARIANT idx,
            /* [retval][out] */ VARIANT __RPC_FAR *newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Field )( 
            IADOTier __RPC_FAR * This,
            /* [in] */ VARIANT idx,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FieldCount )( 
            IADOTier __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Close )( 
            IADOTier __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *First )( 
            IADOTier __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IADOTier __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Last )( 
            IADOTier __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Prev )( 
            IADOTier __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EOF )( 
            IADOTier __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BOF )( 
            IADOTier __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ParamQuery )( 
            IADOTier __RPC_FAR * This,
            /* [in] */ BSTR query,
            /* [in] */ long idx1,
            /* [in] */ BSTR idx2,
            /* [in] */ BSTR idx3);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CallStoredProc )( 
            IADOTier __RPC_FAR * This,
            /* [in] */ long idx1,
            /* [in] */ BSTR idx2,
            /* [in] */ BSTR idx3);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_StoredProc )( 
            IADOTier __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ChangeParameter )( 
            IADOTier __RPC_FAR * This,
            /* [in] */ long idx,
            /* [in] */ enum DataTypeEnum type,
            /* [in] */ VARIANT value,
            /* [in] */ enum ParameterDirectionEnum where,
            /* [in] */ long size);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Requery )( 
            IADOTier __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ADORelease )( 
            IADOTier __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Empty )( 
            IADOTier __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *bEmpty);
        
        END_INTERFACE
    } IADOTierVtbl;

    interface IADOTier
    {
        CONST_VTBL struct IADOTierVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADOTier_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADOTier_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADOTier_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADOTier_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADOTier_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADOTier_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADOTier_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADOTier_Open(This,source,user,pwd)	\
    (This)->lpVtbl -> Open(This,source,user,pwd)

#define IADOTier_OpenRecordset(This,query)	\
    (This)->lpVtbl -> OpenRecordset(This,query)

#define IADOTier_CloseRecordset(This)	\
    (This)->lpVtbl -> CloseRecordset(This)

#define IADOTier_ExecuteConnection(This,query,bChangeRec)	\
    (This)->lpVtbl -> ExecuteConnection(This,query,bChangeRec)

#define IADOTier_ExecuteCommand(This,bStoredProcedure,bChangeRec)	\
    (This)->lpVtbl -> ExecuteCommand(This,bStoredProcedure,bChangeRec)

#define IADOTier_get_CommandText(This,newVal)	\
    (This)->lpVtbl -> get_CommandText(This,newVal)

#define IADOTier_put_CommandText(This,newVal)	\
    (This)->lpVtbl -> put_CommandText(This,newVal)

#define IADOTier_AppendParameter(This,type,value,where,size)	\
    (This)->lpVtbl -> AppendParameter(This,type,value,where,size)

#define IADOTier_Update(This)	\
    (This)->lpVtbl -> Update(This)

#define IADOTier_Delete(This)	\
    (This)->lpVtbl -> Delete(This)

#define IADOTier_get_Field(This,idx,newVal)	\
    (This)->lpVtbl -> get_Field(This,idx,newVal)

#define IADOTier_put_Field(This,idx,newVal)	\
    (This)->lpVtbl -> put_Field(This,idx,newVal)

#define IADOTier_get_FieldCount(This,newVal)	\
    (This)->lpVtbl -> get_FieldCount(This,newVal)

#define IADOTier_Close(This)	\
    (This)->lpVtbl -> Close(This)

#define IADOTier_First(This)	\
    (This)->lpVtbl -> First(This)

#define IADOTier_Next(This)	\
    (This)->lpVtbl -> Next(This)

#define IADOTier_Last(This)	\
    (This)->lpVtbl -> Last(This)

#define IADOTier_Prev(This)	\
    (This)->lpVtbl -> Prev(This)

#define IADOTier_get_EOF(This,newVal)	\
    (This)->lpVtbl -> get_EOF(This,newVal)

#define IADOTier_get_BOF(This,newVal)	\
    (This)->lpVtbl -> get_BOF(This,newVal)

#define IADOTier_ParamQuery(This,query,idx1,idx2,idx3)	\
    (This)->lpVtbl -> ParamQuery(This,query,idx1,idx2,idx3)

#define IADOTier_CallStoredProc(This,idx1,idx2,idx3)	\
    (This)->lpVtbl -> CallStoredProc(This,idx1,idx2,idx3)

#define IADOTier_put_StoredProc(This,newVal)	\
    (This)->lpVtbl -> put_StoredProc(This,newVal)

#define IADOTier_ChangeParameter(This,idx,type,value,where,size)	\
    (This)->lpVtbl -> ChangeParameter(This,idx,type,value,where,size)

#define IADOTier_Requery(This)	\
    (This)->lpVtbl -> Requery(This)

#define IADOTier_ADORelease(This)	\
    (This)->lpVtbl -> ADORelease(This)

#define IADOTier_get_Empty(This,bEmpty)	\
    (This)->lpVtbl -> get_Empty(This,bEmpty)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADOTier_Open_Proxy( 
    IADOTier __RPC_FAR * This,
    /* [in] */ BSTR source,
    /* [in] */ BSTR user,
    /* [in] */ BSTR pwd);


void __RPC_STUB IADOTier_Open_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADOTier_OpenRecordset_Proxy( 
    IADOTier __RPC_FAR * This,
    /* [in] */ VARIANT query);


void __RPC_STUB IADOTier_OpenRecordset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADOTier_CloseRecordset_Proxy( 
    IADOTier __RPC_FAR * This);


void __RPC_STUB IADOTier_CloseRecordset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADOTier_ExecuteConnection_Proxy( 
    IADOTier __RPC_FAR * This,
    /* [in] */ BSTR query,
    /* [in] */ VARIANT_BOOL bChangeRec);


void __RPC_STUB IADOTier_ExecuteConnection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADOTier_ExecuteCommand_Proxy( 
    IADOTier __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL bStoredProcedure,
    /* [in] */ VARIANT_BOOL bChangeRec);


void __RPC_STUB IADOTier_ExecuteCommand_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IADOTier_get_CommandText_Proxy( 
    IADOTier __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *newVal);


void __RPC_STUB IADOTier_get_CommandText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IADOTier_put_CommandText_Proxy( 
    IADOTier __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IADOTier_put_CommandText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADOTier_AppendParameter_Proxy( 
    IADOTier __RPC_FAR * This,
    /* [in] */ enum DataTypeEnum type,
    /* [in] */ VARIANT value,
    /* [in] */ enum ParameterDirectionEnum where,
    /* [in] */ long size);


void __RPC_STUB IADOTier_AppendParameter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADOTier_Update_Proxy( 
    IADOTier __RPC_FAR * This);


void __RPC_STUB IADOTier_Update_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADOTier_Delete_Proxy( 
    IADOTier __RPC_FAR * This);


void __RPC_STUB IADOTier_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IADOTier_get_Field_Proxy( 
    IADOTier __RPC_FAR * This,
    /* [in] */ VARIANT idx,
    /* [retval][out] */ VARIANT __RPC_FAR *newVal);


void __RPC_STUB IADOTier_get_Field_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IADOTier_put_Field_Proxy( 
    IADOTier __RPC_FAR * This,
    /* [in] */ VARIANT idx,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IADOTier_put_Field_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IADOTier_get_FieldCount_Proxy( 
    IADOTier __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *newVal);


void __RPC_STUB IADOTier_get_FieldCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADOTier_Close_Proxy( 
    IADOTier __RPC_FAR * This);


void __RPC_STUB IADOTier_Close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADOTier_First_Proxy( 
    IADOTier __RPC_FAR * This);


void __RPC_STUB IADOTier_First_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADOTier_Next_Proxy( 
    IADOTier __RPC_FAR * This);


void __RPC_STUB IADOTier_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADOTier_Last_Proxy( 
    IADOTier __RPC_FAR * This);


void __RPC_STUB IADOTier_Last_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADOTier_Prev_Proxy( 
    IADOTier __RPC_FAR * This);


void __RPC_STUB IADOTier_Prev_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IADOTier_get_EOF_Proxy( 
    IADOTier __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *newVal);


void __RPC_STUB IADOTier_get_EOF_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IADOTier_get_BOF_Proxy( 
    IADOTier __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *newVal);


void __RPC_STUB IADOTier_get_BOF_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADOTier_ParamQuery_Proxy( 
    IADOTier __RPC_FAR * This,
    /* [in] */ BSTR query,
    /* [in] */ long idx1,
    /* [in] */ BSTR idx2,
    /* [in] */ BSTR idx3);


void __RPC_STUB IADOTier_ParamQuery_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADOTier_CallStoredProc_Proxy( 
    IADOTier __RPC_FAR * This,
    /* [in] */ long idx1,
    /* [in] */ BSTR idx2,
    /* [in] */ BSTR idx3);


void __RPC_STUB IADOTier_CallStoredProc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IADOTier_put_StoredProc_Proxy( 
    IADOTier __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IADOTier_put_StoredProc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADOTier_ChangeParameter_Proxy( 
    IADOTier __RPC_FAR * This,
    /* [in] */ long idx,
    /* [in] */ enum DataTypeEnum type,
    /* [in] */ VARIANT value,
    /* [in] */ enum ParameterDirectionEnum where,
    /* [in] */ long size);


void __RPC_STUB IADOTier_ChangeParameter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADOTier_Requery_Proxy( 
    IADOTier __RPC_FAR * This);


void __RPC_STUB IADOTier_Requery_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADOTier_ADORelease_Proxy( 
    IADOTier __RPC_FAR * This);


void __RPC_STUB IADOTier_ADORelease_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IADOTier_get_Empty_Proxy( 
    IADOTier __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *bEmpty);


void __RPC_STUB IADOTier_get_Empty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADOTier_INTERFACE_DEFINED__ */



#ifndef __ADOSAMPLib_LIBRARY_DEFINED__
#define __ADOSAMPLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: ADOSAMPLib
 * at Wed Feb 04 11:49:00 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_ADOSAMPLib;

EXTERN_C const CLSID CLSID_CADOTier;

#ifdef __cplusplus

class DECLSPEC_UUID("7A319997-48C0-11D0-AE70-00C04FD7D06E")
CADOTier;
#endif
#endif /* __ADOSAMPLib_LIBRARY_DEFINED__ */

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
