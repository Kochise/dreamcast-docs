/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.01.75 */
/* at Fri May 30 13:49:02 1997
 */
/* Compiler settings for msdatsrc.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"

#ifndef __msdatsrc_h__
#define __msdatsrc_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __DataSourceListener_FWD_DEFINED__
#define __DataSourceListener_FWD_DEFINED__
typedef interface DataSourceListener DataSourceListener;
#endif 	/* __DataSourceListener_FWD_DEFINED__ */


#ifndef __DataSource_FWD_DEFINED__
#define __DataSource_FWD_DEFINED__
typedef interface DataSource DataSource;
#endif 	/* __DataSource_FWD_DEFINED__ */


void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL_itf_msdatsrc_0000
 * at Fri May 30 13:49:02 1997
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


// For non-VC5 compilers
#if _MSC_VER >= 1100
#define DECLSPEC_UUID(x)	__declspec(uuid(x))
#else
#define DECLSPEC_UUID(x)
#endif

// C/C++ interface names
#define IDataSource		DataSource
#define IDataSourceListener	DataSourceListener

// Component category guids
EXTERN_C const IID CATID_DataSource;
EXTERN_C const IID CATID_DataConsumer;


extern RPC_IF_HANDLE __MIDL_itf_msdatsrc_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_msdatsrc_0000_v0_0_s_ifspec;


#ifndef __MSDATASRC_LIBRARY_DEFINED__
#define __MSDATASRC_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: MSDATASRC
 * at Fri May 30 13:49:02 1997
 * using MIDL 3.01.75
 ****************************************/
/* [helpstring][version][uuid] */ 


typedef /* [uuid] */ BSTR DataMember;


EXTERN_C const IID LIBID_MSDATASRC;

#ifndef __DataSourceListener_INTERFACE_DEFINED__
#define __DataSourceListener_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: DataSourceListener
 * at Fri May 30 13:49:02 1997
 * using MIDL 3.01.75
 ****************************************/
/* [object][hidden][uuid] */ 



EXTERN_C const IID IID_DataSourceListener;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("7c0ffab2-cd84-11d0-949a-00a0c91110ed")
    DataSourceListener : public IUnknown
    {
    public:
        virtual /* [hidden] */ HRESULT STDMETHODCALLTYPE dataMemberChanged( 
            /* [in] */ DataMember bstrDM) = 0;
        
        virtual /* [hidden] */ HRESULT STDMETHODCALLTYPE dataMemberAdded( 
            /* [in] */ DataMember bstrDM) = 0;
        
        virtual /* [hidden] */ HRESULT STDMETHODCALLTYPE dataMemberRemoved( 
            /* [in] */ DataMember bstrDM) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct DataSourceListenerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            DataSourceListener __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            DataSourceListener __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            DataSourceListener __RPC_FAR * This);
        
        /* [hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *dataMemberChanged )( 
            DataSourceListener __RPC_FAR * This,
            /* [in] */ DataMember bstrDM);
        
        /* [hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *dataMemberAdded )( 
            DataSourceListener __RPC_FAR * This,
            /* [in] */ DataMember bstrDM);
        
        /* [hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *dataMemberRemoved )( 
            DataSourceListener __RPC_FAR * This,
            /* [in] */ DataMember bstrDM);
        
        END_INTERFACE
    } DataSourceListenerVtbl;

    interface DataSourceListener
    {
        CONST_VTBL struct DataSourceListenerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define DataSourceListener_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define DataSourceListener_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define DataSourceListener_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define DataSourceListener_dataMemberChanged(This,bstrDM)	\
    (This)->lpVtbl -> dataMemberChanged(This,bstrDM)

#define DataSourceListener_dataMemberAdded(This,bstrDM)	\
    (This)->lpVtbl -> dataMemberAdded(This,bstrDM)

#define DataSourceListener_dataMemberRemoved(This,bstrDM)	\
    (This)->lpVtbl -> dataMemberRemoved(This,bstrDM)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [hidden] */ HRESULT STDMETHODCALLTYPE DataSourceListener_dataMemberChanged_Proxy( 
    DataSourceListener __RPC_FAR * This,
    /* [in] */ DataMember bstrDM);


void __RPC_STUB DataSourceListener_dataMemberChanged_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden] */ HRESULT STDMETHODCALLTYPE DataSourceListener_dataMemberAdded_Proxy( 
    DataSourceListener __RPC_FAR * This,
    /* [in] */ DataMember bstrDM);


void __RPC_STUB DataSourceListener_dataMemberAdded_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden] */ HRESULT STDMETHODCALLTYPE DataSourceListener_dataMemberRemoved_Proxy( 
    DataSourceListener __RPC_FAR * This,
    /* [in] */ DataMember bstrDM);


void __RPC_STUB DataSourceListener_dataMemberRemoved_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __DataSourceListener_INTERFACE_DEFINED__ */


#ifndef __DataSource_INTERFACE_DEFINED__
#define __DataSource_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: DataSource
 * at Fri May 30 13:49:02 1997
 * using MIDL 3.01.75
 ****************************************/
/* [object][uuid] */ 



EXTERN_C const IID IID_DataSource;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("7c0ffab3-cd84-11d0-949a-00a0c91110ed")
    DataSource : public IUnknown
    {
    public:
        virtual /* [restricted][hidden] */ HRESULT STDMETHODCALLTYPE getDataMember( 
            /* [in] */ DataMember bstrDM,
            /* [in] */ REFIID riid,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk) = 0;
        
        virtual /* [hidden] */ HRESULT STDMETHODCALLTYPE getDataMemberName( 
            /* [in] */ long lIndex,
            /* [retval][out] */ DataMember __RPC_FAR *pbstrDM) = 0;
        
        virtual /* [hidden] */ HRESULT STDMETHODCALLTYPE getDataMemberCount( 
            /* [retval][out] */ long __RPC_FAR *plCount) = 0;
        
        virtual /* [hidden] */ HRESULT STDMETHODCALLTYPE addDataSourceListener( 
            /* [in] */ DataSourceListener __RPC_FAR *pDSL) = 0;
        
        virtual /* [hidden] */ HRESULT STDMETHODCALLTYPE removeDataSourceListener( 
            /* [in] */ DataSourceListener __RPC_FAR *pDSL) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct DataSourceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            DataSource __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            DataSource __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            DataSource __RPC_FAR * This);
        
        /* [restricted][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getDataMember )( 
            DataSource __RPC_FAR * This,
            /* [in] */ DataMember bstrDM,
            /* [in] */ REFIID riid,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);
        
        /* [hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getDataMemberName )( 
            DataSource __RPC_FAR * This,
            /* [in] */ long lIndex,
            /* [retval][out] */ DataMember __RPC_FAR *pbstrDM);
        
        /* [hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getDataMemberCount )( 
            DataSource __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plCount);
        
        /* [hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *addDataSourceListener )( 
            DataSource __RPC_FAR * This,
            /* [in] */ DataSourceListener __RPC_FAR *pDSL);
        
        /* [hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeDataSourceListener )( 
            DataSource __RPC_FAR * This,
            /* [in] */ DataSourceListener __RPC_FAR *pDSL);
        
        END_INTERFACE
    } DataSourceVtbl;

    interface DataSource
    {
        CONST_VTBL struct DataSourceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define DataSource_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define DataSource_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define DataSource_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define DataSource_getDataMember(This,bstrDM,riid,ppunk)	\
    (This)->lpVtbl -> getDataMember(This,bstrDM,riid,ppunk)

#define DataSource_getDataMemberName(This,lIndex,pbstrDM)	\
    (This)->lpVtbl -> getDataMemberName(This,lIndex,pbstrDM)

#define DataSource_getDataMemberCount(This,plCount)	\
    (This)->lpVtbl -> getDataMemberCount(This,plCount)

#define DataSource_addDataSourceListener(This,pDSL)	\
    (This)->lpVtbl -> addDataSourceListener(This,pDSL)

#define DataSource_removeDataSourceListener(This,pDSL)	\
    (This)->lpVtbl -> removeDataSourceListener(This,pDSL)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [restricted][hidden] */ HRESULT STDMETHODCALLTYPE DataSource_getDataMember_Proxy( 
    DataSource __RPC_FAR * This,
    /* [in] */ DataMember bstrDM,
    /* [in] */ REFIID riid,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);


void __RPC_STUB DataSource_getDataMember_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden] */ HRESULT STDMETHODCALLTYPE DataSource_getDataMemberName_Proxy( 
    DataSource __RPC_FAR * This,
    /* [in] */ long lIndex,
    /* [retval][out] */ DataMember __RPC_FAR *pbstrDM);


void __RPC_STUB DataSource_getDataMemberName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden] */ HRESULT STDMETHODCALLTYPE DataSource_getDataMemberCount_Proxy( 
    DataSource __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plCount);


void __RPC_STUB DataSource_getDataMemberCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden] */ HRESULT STDMETHODCALLTYPE DataSource_addDataSourceListener_Proxy( 
    DataSource __RPC_FAR * This,
    /* [in] */ DataSourceListener __RPC_FAR *pDSL);


void __RPC_STUB DataSource_addDataSourceListener_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden] */ HRESULT STDMETHODCALLTYPE DataSource_removeDataSourceListener_Proxy( 
    DataSource __RPC_FAR * This,
    /* [in] */ DataSourceListener __RPC_FAR *pDSL);


void __RPC_STUB DataSource_removeDataSourceListener_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __DataSource_INTERFACE_DEFINED__ */

#endif /* __MSDATASRC_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
