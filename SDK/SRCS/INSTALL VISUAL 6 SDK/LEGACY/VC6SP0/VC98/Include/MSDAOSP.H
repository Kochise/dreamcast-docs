/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.01.75 */
/* at Fri Oct 24 09:46:14 1997
 */
/* Compiler settings for msdaosp.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"

#ifndef __msdaosp_h__
#define __msdaosp_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __DataSourceObject_FWD_DEFINED__
#define __DataSourceObject_FWD_DEFINED__
typedef interface DataSourceObject DataSourceObject;
#endif 	/* __DataSourceObject_FWD_DEFINED__ */


void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL_itf_msdaosp_0000
 * at Fri Oct 24 09:46:14 1997
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


#include "msdatsrc.h"
#include "simpdata.h"
#ifdef DBINITCONSTANTS
extern const GUID CLSID_MSDAOSP		= {0xdfc8bdc0,0xe378,0x11d0,{0x9b,0x30,0x0,0x80,0xc7,0xe9,0xfe,0x95}};
extern const GUID DBPROPSET_PWROWSET = {0xe6e478db,0xf226,0x11d0,{0x94,0xee,0x0,0xc0,0x4f,0xb6,0x6a,0x50}};
#else  // !DBINITCONSTANTS
extern const GUID CLSID_MSDAOSP;
extern const GUID DBPROPSET_PWROWSET;
#endif // DBINITCONSTANTS
#define PWPROP_OSPVALUE			2


extern RPC_IF_HANDLE __MIDL_itf_msdaosp_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_msdaosp_0000_v0_0_s_ifspec;


#ifndef __MSDAOSPT_LIBRARY_DEFINED__
#define __MSDAOSPT_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: MSDAOSPT
 * at Fri Oct 24 09:46:14 1997
 * using MIDL 3.01.75
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_MSDAOSPT;

#ifndef __DataSourceObject_DISPINTERFACE_DEFINED__
#define __DataSourceObject_DISPINTERFACE_DEFINED__

/****************************************
 * Generated header for dispinterface: DataSourceObject
 * at Fri Oct 24 09:46:14 1997
 * using MIDL 3.01.75
 ****************************************/
/* [uuid] */ 



EXTERN_C const IID DIID_DataSourceObject;

#if defined(__cplusplus) && !defined(CINTERFACE)

    interface DECLSPEC_UUID("0ae9a4e4-18d4-11d1-b3b3-00aa00c1a924")
    DataSourceObject : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct DataSourceObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            DataSourceObject __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            DataSourceObject __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            DataSourceObject __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            DataSourceObject __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            DataSourceObject __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            DataSourceObject __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            DataSourceObject __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } DataSourceObjectVtbl;

    interface DataSourceObject
    {
        CONST_VTBL struct DataSourceObjectVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define DataSourceObject_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define DataSourceObject_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define DataSourceObject_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define DataSourceObject_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define DataSourceObject_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define DataSourceObject_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define DataSourceObject_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __DataSourceObject_DISPINTERFACE_DEFINED__ */

#endif /* __MSDAOSPT_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
