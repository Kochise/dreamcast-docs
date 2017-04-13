/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 02:35:28 1998
 */
/* Compiler settings for MyProp.Idl:
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

#ifndef __MyProp_h__
#define __MyProp_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IMyProperties_FWD_DEFINED__
#define __IMyProperties_FWD_DEFINED__
typedef interface IMyProperties IMyProperties;
#endif 	/* __IMyProperties_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL_itf_MyProp_0000
 * at Mon Mar 30 02:35:28 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [local] */ 


DEFINE_GUID(CLSID_SecureObject, 0x28f64ee0, 0x4656, 0x11cf, 0x81, 0x10, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71);
DEFINE_GUID(CLSID_SecureObjectService, 0x28f64ee2, 0x4656, 0x11cf, 0x81, 0x10, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71);
DEFINE_GUID(IID_IMyProperties, 0x28f64ee1, 0x4656, 0x11cf, 0x81, 0x10, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71);


extern RPC_IF_HANDLE __MIDL_itf_MyProp_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_MyProp_0000_v0_0_s_ifspec;

#ifndef __IMyProperties_INTERFACE_DEFINED__
#define __IMyProperties_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMyProperties
 * at Mon Mar 30 02:35:28 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [uuid][object] */ 


typedef /* [unique] */ IMyProperties __RPC_FAR *LPMYPROPERTIES;


EXTERN_C const IID IID_IMyProperties;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("28f64ee1-4656-11cf-8110-00aa00389b71")
    IMyProperties : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetColor( 
            /* [out] */ COLORREF __RPC_FAR *pcr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PutColor( 
            /* [in] */ COLORREF cr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetUserName( 
            /* [out][in] */ WCHAR __RPC_FAR szUserName[ 20 ]) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PutUserName( 
            /* [in] */ WCHAR __RPC_FAR szUserName[ 20 ]) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMyPropertiesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMyProperties __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMyProperties __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMyProperties __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetColor )( 
            IMyProperties __RPC_FAR * This,
            /* [out] */ COLORREF __RPC_FAR *pcr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutColor )( 
            IMyProperties __RPC_FAR * This,
            /* [in] */ COLORREF cr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetUserName )( 
            IMyProperties __RPC_FAR * This,
            /* [out][in] */ WCHAR __RPC_FAR szUserName[ 20 ]);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutUserName )( 
            IMyProperties __RPC_FAR * This,
            /* [in] */ WCHAR __RPC_FAR szUserName[ 20 ]);
        
        END_INTERFACE
    } IMyPropertiesVtbl;

    interface IMyProperties
    {
        CONST_VTBL struct IMyPropertiesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMyProperties_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMyProperties_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMyProperties_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMyProperties_GetColor(This,pcr)	\
    (This)->lpVtbl -> GetColor(This,pcr)

#define IMyProperties_PutColor(This,cr)	\
    (This)->lpVtbl -> PutColor(This,cr)

#define IMyProperties_GetUserName(This,szUserName)	\
    (This)->lpVtbl -> GetUserName(This,szUserName)

#define IMyProperties_PutUserName(This,szUserName)	\
    (This)->lpVtbl -> PutUserName(This,szUserName)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMyProperties_GetColor_Proxy( 
    IMyProperties __RPC_FAR * This,
    /* [out] */ COLORREF __RPC_FAR *pcr);


void __RPC_STUB IMyProperties_GetColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMyProperties_PutColor_Proxy( 
    IMyProperties __RPC_FAR * This,
    /* [in] */ COLORREF cr);


void __RPC_STUB IMyProperties_PutColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMyProperties_GetUserName_Proxy( 
    IMyProperties __RPC_FAR * This,
    /* [out][in] */ WCHAR __RPC_FAR szUserName[ 20 ]);


void __RPC_STUB IMyProperties_GetUserName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMyProperties_PutUserName_Proxy( 
    IMyProperties __RPC_FAR * This,
    /* [in] */ WCHAR __RPC_FAR szUserName[ 20 ]);


void __RPC_STUB IMyProperties_PutUserName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMyProperties_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
