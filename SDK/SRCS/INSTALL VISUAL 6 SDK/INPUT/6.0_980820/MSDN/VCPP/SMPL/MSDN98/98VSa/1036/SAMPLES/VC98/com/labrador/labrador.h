/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Thu Apr 02 17:47:49 1998
 */
/* Compiler settings for Labrador.idl:
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

#ifndef __Labrador_h__
#define __Labrador_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IMammal_FWD_DEFINED__
#define __IMammal_FWD_DEFINED__
typedef interface IMammal IMammal;
#endif 	/* __IMammal_FWD_DEFINED__ */


#ifndef __IDog_FWD_DEFINED__
#define __IDog_FWD_DEFINED__
typedef interface IDog IDog;
#endif 	/* __IDog_FWD_DEFINED__ */


#ifndef __Labrador_FWD_DEFINED__
#define __Labrador_FWD_DEFINED__

#ifdef __cplusplus
typedef class Labrador Labrador;
#else
typedef struct Labrador Labrador;
#endif /* __cplusplus */

#endif 	/* __Labrador_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "oaidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL_itf_Labrador_0000
 * at Thu Apr 02 17:47:49 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [local] */ 


typedef USHORT __RPC_FAR MY_BSTR[ 32 ];



extern RPC_IF_HANDLE __MIDL_itf_Labrador_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_Labrador_0000_v0_0_s_ifspec;

#ifndef __IMammal_INTERFACE_DEFINED__
#define __IMammal_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMammal
 * at Thu Apr 02 17:47:49 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][helpstring][uuid][object] */ 



EXTERN_C const IID IID_IMammal;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62A33E85-932A-11CF-B056-00A0C90348FA")
    IMammal : public IUnknown
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetSpeciesName( 
            /* [out] */ MY_BSTR p) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE IsAlive( 
            /* [out] */ BOOL __RPC_FAR *pBool) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMammalVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMammal __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMammal __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMammal __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSpeciesName )( 
            IMammal __RPC_FAR * This,
            /* [out] */ MY_BSTR p);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsAlive )( 
            IMammal __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *pBool);
        
        END_INTERFACE
    } IMammalVtbl;

    interface IMammal
    {
        CONST_VTBL struct IMammalVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMammal_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMammal_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMammal_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMammal_GetSpeciesName(This,p)	\
    (This)->lpVtbl -> GetSpeciesName(This,p)

#define IMammal_IsAlive(This,pBool)	\
    (This)->lpVtbl -> IsAlive(This,pBool)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id] */ HRESULT STDMETHODCALLTYPE IMammal_GetSpeciesName_Proxy( 
    IMammal __RPC_FAR * This,
    /* [out] */ MY_BSTR p);


void __RPC_STUB IMammal_GetSpeciesName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IMammal_IsAlive_Proxy( 
    IMammal __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *pBool);


void __RPC_STUB IMammal_IsAlive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMammal_INTERFACE_DEFINED__ */


#ifndef __IDog_INTERFACE_DEFINED__
#define __IDog_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDog
 * at Thu Apr 02 17:47:49 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][helpstring][uuid][object] */ 



EXTERN_C const IID IID_IDog;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62A33E86-932A-11CF-B056-00A0C90348FA")
    IDog : public IUnknown
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetPetName( 
            /* [out] */ MY_BSTR p) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetPetName( 
            /* [in] */ MY_BSTR p) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE IsBarking( 
            /* [out] */ BOOL __RPC_FAR *pBool) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDogVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDog __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDog __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDog __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPetName )( 
            IDog __RPC_FAR * This,
            /* [out] */ MY_BSTR p);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPetName )( 
            IDog __RPC_FAR * This,
            /* [in] */ MY_BSTR p);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsBarking )( 
            IDog __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *pBool);
        
        END_INTERFACE
    } IDogVtbl;

    interface IDog
    {
        CONST_VTBL struct IDogVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDog_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDog_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDog_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDog_GetPetName(This,p)	\
    (This)->lpVtbl -> GetPetName(This,p)

#define IDog_SetPetName(This,p)	\
    (This)->lpVtbl -> SetPetName(This,p)

#define IDog_IsBarking(This,pBool)	\
    (This)->lpVtbl -> IsBarking(This,pBool)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id] */ HRESULT STDMETHODCALLTYPE IDog_GetPetName_Proxy( 
    IDog __RPC_FAR * This,
    /* [out] */ MY_BSTR p);


void __RPC_STUB IDog_GetPetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IDog_SetPetName_Proxy( 
    IDog __RPC_FAR * This,
    /* [in] */ MY_BSTR p);


void __RPC_STUB IDog_SetPetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IDog_IsBarking_Proxy( 
    IDog __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *pBool);


void __RPC_STUB IDog_IsBarking_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDog_INTERFACE_DEFINED__ */



#ifndef __LABRADORLib_LIBRARY_DEFINED__
#define __LABRADORLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: LABRADORLib
 * at Thu Apr 02 17:47:49 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_LABRADORLib;

EXTERN_C const CLSID CLSID_Labrador;

#ifdef __cplusplus

class DECLSPEC_UUID("62A33E89-932A-11CF-B056-00A0C90348FA")
Labrador;
#endif
#endif /* __LABRADORLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
