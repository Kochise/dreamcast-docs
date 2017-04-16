/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Thu Sep 11 10:59:24 1997
 */
/* Compiler settings for mimeinfo.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
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

#ifndef __mimeinfo_h__
#define __mimeinfo_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IMimeInfo_FWD_DEFINED__
#define __IMimeInfo_FWD_DEFINED__
typedef interface IMimeInfo IMimeInfo;
#endif 	/* __IMimeInfo_FWD_DEFINED__ */


/* header files for imported files */
#include "objidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL_itf_mimeinfo_0000
 * at Thu Sep 11 10:59:24 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [local] */ 


//=--------------------------------------------------------------------------=
// MimeInfo.h
//=--------------------------------------------------------------------------=
// (C) Copyright 1995 - 1998 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=

#pragma comment(lib,"uuid.lib")

//--------------------------------------------------------------------------
// IMimeInfo Interfaces.



extern RPC_IF_HANDLE __MIDL_itf_mimeinfo_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_mimeinfo_0000_v0_0_s_ifspec;

#ifndef __IMimeInfo_INTERFACE_DEFINED__
#define __IMimeInfo_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMimeInfo
 * at Thu Sep 11 10:59:24 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][uuid][object][local] */ 


typedef /* [unique] */ IMimeInfo __RPC_FAR *LPMIMEINFO;


EXTERN_C const IID IID_IMimeInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F77459A0-BF9A-11cf-BA4E-00C04FD70816")
    IMimeInfo : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetMimeCLSIDMapping( 
            /* [out] */ UINT __RPC_FAR *pcTypes,
            /* [out] */ LPCSTR __RPC_FAR *__RPC_FAR *ppszTypes,
            /* [out] */ CLSID __RPC_FAR *__RPC_FAR *ppclsID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMimeInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMimeInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMimeInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMimeInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMimeCLSIDMapping )( 
            IMimeInfo __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pcTypes,
            /* [out] */ LPCSTR __RPC_FAR *__RPC_FAR *ppszTypes,
            /* [out] */ CLSID __RPC_FAR *__RPC_FAR *ppclsID);
        
        END_INTERFACE
    } IMimeInfoVtbl;

    interface IMimeInfo
    {
        CONST_VTBL struct IMimeInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMimeInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMimeInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMimeInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMimeInfo_GetMimeCLSIDMapping(This,pcTypes,ppszTypes,ppclsID)	\
    (This)->lpVtbl -> GetMimeCLSIDMapping(This,pcTypes,ppszTypes,ppclsID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMimeInfo_GetMimeCLSIDMapping_Proxy( 
    IMimeInfo __RPC_FAR * This,
    /* [out] */ UINT __RPC_FAR *pcTypes,
    /* [out] */ LPCSTR __RPC_FAR *__RPC_FAR *ppszTypes,
    /* [out] */ CLSID __RPC_FAR *__RPC_FAR *ppclsID);


void __RPC_STUB IMimeInfo_GetMimeCLSIDMapping_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMimeInfo_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_mimeinfo_0074
 * at Thu Sep 11 10:59:24 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [local] */ 


#define SID_IMimeInfo IID_IMimeInfo


extern RPC_IF_HANDLE __MIDL_itf_mimeinfo_0074_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_mimeinfo_0074_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
