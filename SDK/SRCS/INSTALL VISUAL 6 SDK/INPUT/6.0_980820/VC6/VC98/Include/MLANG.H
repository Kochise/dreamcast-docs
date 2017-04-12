/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Thu Sep 11 10:59:43 1997
 */
/* Compiler settings for mlang.idl:
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

#ifndef __mlang_h__
#define __mlang_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IMLangStringBufW_FWD_DEFINED__
#define __IMLangStringBufW_FWD_DEFINED__
typedef interface IMLangStringBufW IMLangStringBufW;
#endif 	/* __IMLangStringBufW_FWD_DEFINED__ */


#ifndef __IMLangStringBufA_FWD_DEFINED__
#define __IMLangStringBufA_FWD_DEFINED__
typedef interface IMLangStringBufA IMLangStringBufA;
#endif 	/* __IMLangStringBufA_FWD_DEFINED__ */


#ifndef __IMLangString_FWD_DEFINED__
#define __IMLangString_FWD_DEFINED__
typedef interface IMLangString IMLangString;
#endif 	/* __IMLangString_FWD_DEFINED__ */


#ifndef __IMLangStringWStr_FWD_DEFINED__
#define __IMLangStringWStr_FWD_DEFINED__
typedef interface IMLangStringWStr IMLangStringWStr;
#endif 	/* __IMLangStringWStr_FWD_DEFINED__ */


#ifndef __IMLangStringAStr_FWD_DEFINED__
#define __IMLangStringAStr_FWD_DEFINED__
typedef interface IMLangStringAStr IMLangStringAStr;
#endif 	/* __IMLangStringAStr_FWD_DEFINED__ */


#ifndef __CMLangString_FWD_DEFINED__
#define __CMLangString_FWD_DEFINED__

#ifdef __cplusplus
typedef class CMLangString CMLangString;
#else
typedef struct CMLangString CMLangString;
#endif /* __cplusplus */

#endif 	/* __CMLangString_FWD_DEFINED__ */


#ifndef __IMLangLineBreakConsole_FWD_DEFINED__
#define __IMLangLineBreakConsole_FWD_DEFINED__
typedef interface IMLangLineBreakConsole IMLangLineBreakConsole;
#endif 	/* __IMLangLineBreakConsole_FWD_DEFINED__ */


#ifndef __IEnumCodePage_FWD_DEFINED__
#define __IEnumCodePage_FWD_DEFINED__
typedef interface IEnumCodePage IEnumCodePage;
#endif 	/* __IEnumCodePage_FWD_DEFINED__ */


#ifndef __IEnumRfc1766_FWD_DEFINED__
#define __IEnumRfc1766_FWD_DEFINED__
typedef interface IEnumRfc1766 IEnumRfc1766;
#endif 	/* __IEnumRfc1766_FWD_DEFINED__ */


#ifndef __IMLangConvertCharset_FWD_DEFINED__
#define __IMLangConvertCharset_FWD_DEFINED__
typedef interface IMLangConvertCharset IMLangConvertCharset;
#endif 	/* __IMLangConvertCharset_FWD_DEFINED__ */


#ifndef __CMLangConvertCharset_FWD_DEFINED__
#define __CMLangConvertCharset_FWD_DEFINED__

#ifdef __cplusplus
typedef class CMLangConvertCharset CMLangConvertCharset;
#else
typedef struct CMLangConvertCharset CMLangConvertCharset;
#endif /* __cplusplus */

#endif 	/* __CMLangConvertCharset_FWD_DEFINED__ */


#ifndef __IMultiLanguage_FWD_DEFINED__
#define __IMultiLanguage_FWD_DEFINED__
typedef interface IMultiLanguage IMultiLanguage;
#endif 	/* __IMultiLanguage_FWD_DEFINED__ */


#ifndef __IMLangCodePages_FWD_DEFINED__
#define __IMLangCodePages_FWD_DEFINED__
typedef interface IMLangCodePages IMLangCodePages;
#endif 	/* __IMLangCodePages_FWD_DEFINED__ */


#ifndef __IMLangFontLink_FWD_DEFINED__
#define __IMLangFontLink_FWD_DEFINED__
typedef interface IMLangFontLink IMLangFontLink;
#endif 	/* __IMLangFontLink_FWD_DEFINED__ */


#ifndef __CMultiLanguage_FWD_DEFINED__
#define __CMultiLanguage_FWD_DEFINED__

#ifdef __cplusplus
typedef class CMultiLanguage CMultiLanguage;
#else
typedef struct CMultiLanguage CMultiLanguage;
#endif /* __cplusplus */

#endif 	/* __CMultiLanguage_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL_itf_mlang_0000
 * at Thu Sep 11 10:59:43 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [local] */ 


//=--------------------------------------------------------------------------=
// MLang.h                                                                    
//=--------------------------------------------------------------------------=
// (C) Copyright 1995 - 1998 Microsoft Corporation.  All Rights Reserved.       
//                                                                            
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF        
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO        
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A             
// PARTICULAR PURPOSE.                                                        
//=--------------------------------------------------------------------------=
                                                                              
#pragma comment(lib,"uuid.lib")                                             
                                                                              
//----------------------------------------------------------------------------
// IMultiLanguage Interfaces.                                                 
                                                                              


extern RPC_IF_HANDLE __MIDL_itf_mlang_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_mlang_0000_v0_0_s_ifspec;


#ifndef __MultiLanguage_LIBRARY_DEFINED__
#define __MultiLanguage_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: MultiLanguage
 * at Thu Sep 11 10:59:43 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [version][lcid][helpstring][uuid] */ 


typedef 
enum tagMLSTR_FLAGS
    {	MLSTR_READ	= 1,
	MLSTR_WRITE	= 2
    }	MLSTR_FLAGS;


EXTERN_C const IID LIBID_MultiLanguage;

#ifndef __IMLangStringBufW_INTERFACE_DEFINED__
#define __IMLangStringBufW_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMLangStringBufW
 * at Thu Sep 11 10:59:43 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][unique][helpstring][uuid] */ 



EXTERN_C const IID IID_IMLangStringBufW;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D24ACD21-BA72-11D0-B188-00AA0038C969")
    IMLangStringBufW : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetStatus( 
            /* [out] */ long __RPC_FAR *plFlags,
            /* [out] */ long __RPC_FAR *pcchBuf) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LockBuf( 
            /* [in] */ long cchOffset,
            /* [in] */ long cchMaxLock,
            /* [size_is][size_is][out] */ WCHAR __RPC_FAR *__RPC_FAR *ppszBuf,
            /* [out] */ long __RPC_FAR *pcchBuf) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE UnlockBuf( 
            /* [size_is][in] */ const WCHAR __RPC_FAR *pszBuf,
            /* [in] */ long cchOffset,
            /* [in] */ long cchWrite) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ long cchOffset,
            /* [in] */ long cchMaxInsert,
            /* [out] */ long __RPC_FAR *pcchActual) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Delete( 
            /* [in] */ long cchOffset,
            /* [in] */ long cchDelete) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMLangStringBufWVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMLangStringBufW __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMLangStringBufW __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMLangStringBufW __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStatus )( 
            IMLangStringBufW __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *plFlags,
            /* [out] */ long __RPC_FAR *pcchBuf);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LockBuf )( 
            IMLangStringBufW __RPC_FAR * This,
            /* [in] */ long cchOffset,
            /* [in] */ long cchMaxLock,
            /* [size_is][size_is][out] */ WCHAR __RPC_FAR *__RPC_FAR *ppszBuf,
            /* [out] */ long __RPC_FAR *pcchBuf);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnlockBuf )( 
            IMLangStringBufW __RPC_FAR * This,
            /* [size_is][in] */ const WCHAR __RPC_FAR *pszBuf,
            /* [in] */ long cchOffset,
            /* [in] */ long cchWrite);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Insert )( 
            IMLangStringBufW __RPC_FAR * This,
            /* [in] */ long cchOffset,
            /* [in] */ long cchMaxInsert,
            /* [out] */ long __RPC_FAR *pcchActual);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            IMLangStringBufW __RPC_FAR * This,
            /* [in] */ long cchOffset,
            /* [in] */ long cchDelete);
        
        END_INTERFACE
    } IMLangStringBufWVtbl;

    interface IMLangStringBufW
    {
        CONST_VTBL struct IMLangStringBufWVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMLangStringBufW_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMLangStringBufW_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMLangStringBufW_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMLangStringBufW_GetStatus(This,plFlags,pcchBuf)	\
    (This)->lpVtbl -> GetStatus(This,plFlags,pcchBuf)

#define IMLangStringBufW_LockBuf(This,cchOffset,cchMaxLock,ppszBuf,pcchBuf)	\
    (This)->lpVtbl -> LockBuf(This,cchOffset,cchMaxLock,ppszBuf,pcchBuf)

#define IMLangStringBufW_UnlockBuf(This,pszBuf,cchOffset,cchWrite)	\
    (This)->lpVtbl -> UnlockBuf(This,pszBuf,cchOffset,cchWrite)

#define IMLangStringBufW_Insert(This,cchOffset,cchMaxInsert,pcchActual)	\
    (This)->lpVtbl -> Insert(This,cchOffset,cchMaxInsert,pcchActual)

#define IMLangStringBufW_Delete(This,cchOffset,cchDelete)	\
    (This)->lpVtbl -> Delete(This,cchOffset,cchDelete)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangStringBufW_GetStatus_Proxy( 
    IMLangStringBufW __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *plFlags,
    /* [out] */ long __RPC_FAR *pcchBuf);


void __RPC_STUB IMLangStringBufW_GetStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangStringBufW_LockBuf_Proxy( 
    IMLangStringBufW __RPC_FAR * This,
    /* [in] */ long cchOffset,
    /* [in] */ long cchMaxLock,
    /* [size_is][size_is][out] */ WCHAR __RPC_FAR *__RPC_FAR *ppszBuf,
    /* [out] */ long __RPC_FAR *pcchBuf);


void __RPC_STUB IMLangStringBufW_LockBuf_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangStringBufW_UnlockBuf_Proxy( 
    IMLangStringBufW __RPC_FAR * This,
    /* [size_is][in] */ const WCHAR __RPC_FAR *pszBuf,
    /* [in] */ long cchOffset,
    /* [in] */ long cchWrite);


void __RPC_STUB IMLangStringBufW_UnlockBuf_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangStringBufW_Insert_Proxy( 
    IMLangStringBufW __RPC_FAR * This,
    /* [in] */ long cchOffset,
    /* [in] */ long cchMaxInsert,
    /* [out] */ long __RPC_FAR *pcchActual);


void __RPC_STUB IMLangStringBufW_Insert_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangStringBufW_Delete_Proxy( 
    IMLangStringBufW __RPC_FAR * This,
    /* [in] */ long cchOffset,
    /* [in] */ long cchDelete);


void __RPC_STUB IMLangStringBufW_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMLangStringBufW_INTERFACE_DEFINED__ */


#ifndef __IMLangStringBufA_INTERFACE_DEFINED__
#define __IMLangStringBufA_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMLangStringBufA
 * at Thu Sep 11 10:59:43 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][unique][helpstring][uuid] */ 



EXTERN_C const IID IID_IMLangStringBufA;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D24ACD23-BA72-11D0-B188-00AA0038C969")
    IMLangStringBufA : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetStatus( 
            /* [out] */ long __RPC_FAR *plFlags,
            /* [out] */ long __RPC_FAR *pcchBuf) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LockBuf( 
            /* [in] */ long cchOffset,
            /* [in] */ long cchMaxLock,
            /* [size_is][size_is][out] */ CHAR __RPC_FAR *__RPC_FAR *ppszBuf,
            /* [out] */ long __RPC_FAR *pcchBuf) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE UnlockBuf( 
            /* [size_is][in] */ const CHAR __RPC_FAR *pszBuf,
            /* [in] */ long cchOffset,
            /* [in] */ long cchWrite) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ long cchOffset,
            /* [in] */ long cchMaxInsert,
            /* [out] */ long __RPC_FAR *pcchActual) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Delete( 
            /* [in] */ long cchOffset,
            /* [in] */ long cchDelete) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMLangStringBufAVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMLangStringBufA __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMLangStringBufA __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMLangStringBufA __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStatus )( 
            IMLangStringBufA __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *plFlags,
            /* [out] */ long __RPC_FAR *pcchBuf);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LockBuf )( 
            IMLangStringBufA __RPC_FAR * This,
            /* [in] */ long cchOffset,
            /* [in] */ long cchMaxLock,
            /* [size_is][size_is][out] */ CHAR __RPC_FAR *__RPC_FAR *ppszBuf,
            /* [out] */ long __RPC_FAR *pcchBuf);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnlockBuf )( 
            IMLangStringBufA __RPC_FAR * This,
            /* [size_is][in] */ const CHAR __RPC_FAR *pszBuf,
            /* [in] */ long cchOffset,
            /* [in] */ long cchWrite);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Insert )( 
            IMLangStringBufA __RPC_FAR * This,
            /* [in] */ long cchOffset,
            /* [in] */ long cchMaxInsert,
            /* [out] */ long __RPC_FAR *pcchActual);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            IMLangStringBufA __RPC_FAR * This,
            /* [in] */ long cchOffset,
            /* [in] */ long cchDelete);
        
        END_INTERFACE
    } IMLangStringBufAVtbl;

    interface IMLangStringBufA
    {
        CONST_VTBL struct IMLangStringBufAVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMLangStringBufA_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMLangStringBufA_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMLangStringBufA_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMLangStringBufA_GetStatus(This,plFlags,pcchBuf)	\
    (This)->lpVtbl -> GetStatus(This,plFlags,pcchBuf)

#define IMLangStringBufA_LockBuf(This,cchOffset,cchMaxLock,ppszBuf,pcchBuf)	\
    (This)->lpVtbl -> LockBuf(This,cchOffset,cchMaxLock,ppszBuf,pcchBuf)

#define IMLangStringBufA_UnlockBuf(This,pszBuf,cchOffset,cchWrite)	\
    (This)->lpVtbl -> UnlockBuf(This,pszBuf,cchOffset,cchWrite)

#define IMLangStringBufA_Insert(This,cchOffset,cchMaxInsert,pcchActual)	\
    (This)->lpVtbl -> Insert(This,cchOffset,cchMaxInsert,pcchActual)

#define IMLangStringBufA_Delete(This,cchOffset,cchDelete)	\
    (This)->lpVtbl -> Delete(This,cchOffset,cchDelete)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangStringBufA_GetStatus_Proxy( 
    IMLangStringBufA __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *plFlags,
    /* [out] */ long __RPC_FAR *pcchBuf);


void __RPC_STUB IMLangStringBufA_GetStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangStringBufA_LockBuf_Proxy( 
    IMLangStringBufA __RPC_FAR * This,
    /* [in] */ long cchOffset,
    /* [in] */ long cchMaxLock,
    /* [size_is][size_is][out] */ CHAR __RPC_FAR *__RPC_FAR *ppszBuf,
    /* [out] */ long __RPC_FAR *pcchBuf);


void __RPC_STUB IMLangStringBufA_LockBuf_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangStringBufA_UnlockBuf_Proxy( 
    IMLangStringBufA __RPC_FAR * This,
    /* [size_is][in] */ const CHAR __RPC_FAR *pszBuf,
    /* [in] */ long cchOffset,
    /* [in] */ long cchWrite);


void __RPC_STUB IMLangStringBufA_UnlockBuf_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangStringBufA_Insert_Proxy( 
    IMLangStringBufA __RPC_FAR * This,
    /* [in] */ long cchOffset,
    /* [in] */ long cchMaxInsert,
    /* [out] */ long __RPC_FAR *pcchActual);


void __RPC_STUB IMLangStringBufA_Insert_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangStringBufA_Delete_Proxy( 
    IMLangStringBufA __RPC_FAR * This,
    /* [in] */ long cchOffset,
    /* [in] */ long cchDelete);


void __RPC_STUB IMLangStringBufA_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMLangStringBufA_INTERFACE_DEFINED__ */


#ifndef __IMLangString_INTERFACE_DEFINED__
#define __IMLangString_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMLangString
 * at Thu Sep 11 10:59:43 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][unique][helpstring][uuid] */ 



EXTERN_C const IID IID_IMLangString;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C04D65CE-B70D-11D0-B188-00AA0038C969")
    IMLangString : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Sync( 
            /* [in] */ BOOL fNoAccess) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetLength( 
            /* [retval][out] */ long __RPC_FAR *plLen) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetMLStr( 
            /* [in] */ long lDestPos,
            /* [in] */ long lDestLen,
            /* [in] */ IUnknown __RPC_FAR *pSrcMLStr,
            /* [in] */ long lSrcPos,
            /* [in] */ long lSrcLen) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetMLStr( 
            /* [in] */ long lSrcPos,
            /* [in] */ long lSrcLen,
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ DWORD dwClsContext,
            /* [in] */ const IID __RPC_FAR *piid,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppDestMLStr,
            /* [out] */ long __RPC_FAR *plDestPos,
            /* [out] */ long __RPC_FAR *plDestLen) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMLangStringVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMLangString __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMLangString __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMLangString __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Sync )( 
            IMLangString __RPC_FAR * This,
            /* [in] */ BOOL fNoAccess);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLength )( 
            IMLangString __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plLen);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMLStr )( 
            IMLangString __RPC_FAR * This,
            /* [in] */ long lDestPos,
            /* [in] */ long lDestLen,
            /* [in] */ IUnknown __RPC_FAR *pSrcMLStr,
            /* [in] */ long lSrcPos,
            /* [in] */ long lSrcLen);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMLStr )( 
            IMLangString __RPC_FAR * This,
            /* [in] */ long lSrcPos,
            /* [in] */ long lSrcLen,
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ DWORD dwClsContext,
            /* [in] */ const IID __RPC_FAR *piid,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppDestMLStr,
            /* [out] */ long __RPC_FAR *plDestPos,
            /* [out] */ long __RPC_FAR *plDestLen);
        
        END_INTERFACE
    } IMLangStringVtbl;

    interface IMLangString
    {
        CONST_VTBL struct IMLangStringVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMLangString_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMLangString_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMLangString_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMLangString_Sync(This,fNoAccess)	\
    (This)->lpVtbl -> Sync(This,fNoAccess)

#define IMLangString_GetLength(This,plLen)	\
    (This)->lpVtbl -> GetLength(This,plLen)

#define IMLangString_SetMLStr(This,lDestPos,lDestLen,pSrcMLStr,lSrcPos,lSrcLen)	\
    (This)->lpVtbl -> SetMLStr(This,lDestPos,lDestLen,pSrcMLStr,lSrcPos,lSrcLen)

#define IMLangString_GetMLStr(This,lSrcPos,lSrcLen,pUnkOuter,dwClsContext,piid,ppDestMLStr,plDestPos,plDestLen)	\
    (This)->lpVtbl -> GetMLStr(This,lSrcPos,lSrcLen,pUnkOuter,dwClsContext,piid,ppDestMLStr,plDestPos,plDestLen)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangString_Sync_Proxy( 
    IMLangString __RPC_FAR * This,
    /* [in] */ BOOL fNoAccess);


void __RPC_STUB IMLangString_Sync_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangString_GetLength_Proxy( 
    IMLangString __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plLen);


void __RPC_STUB IMLangString_GetLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangString_SetMLStr_Proxy( 
    IMLangString __RPC_FAR * This,
    /* [in] */ long lDestPos,
    /* [in] */ long lDestLen,
    /* [in] */ IUnknown __RPC_FAR *pSrcMLStr,
    /* [in] */ long lSrcPos,
    /* [in] */ long lSrcLen);


void __RPC_STUB IMLangString_SetMLStr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangString_GetMLStr_Proxy( 
    IMLangString __RPC_FAR * This,
    /* [in] */ long lSrcPos,
    /* [in] */ long lSrcLen,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ DWORD dwClsContext,
    /* [in] */ const IID __RPC_FAR *piid,
    /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppDestMLStr,
    /* [out] */ long __RPC_FAR *plDestPos,
    /* [out] */ long __RPC_FAR *plDestLen);


void __RPC_STUB IMLangString_GetMLStr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMLangString_INTERFACE_DEFINED__ */


#ifndef __IMLangStringWStr_INTERFACE_DEFINED__
#define __IMLangStringWStr_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMLangStringWStr
 * at Thu Sep 11 10:59:43 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][unique][helpstring][uuid] */ 



EXTERN_C const IID IID_IMLangStringWStr;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C04D65D0-B70D-11D0-B188-00AA0038C969")
    IMLangStringWStr : public IMLangString
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetWStr( 
            /* [in] */ long lDestPos,
            /* [in] */ long lDestLen,
            /* [size_is][in] */ const WCHAR __RPC_FAR *pszSrc,
            /* [in] */ long cchSrc,
            /* [out] */ long __RPC_FAR *pcchActual,
            /* [out] */ long __RPC_FAR *plActualLen) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetStrBufW( 
            /* [in] */ long lDestPos,
            /* [in] */ long lDestLen,
            /* [in] */ IMLangStringBufW __RPC_FAR *pSrcBuf,
            /* [out] */ long __RPC_FAR *pcchActual,
            /* [out] */ long __RPC_FAR *plActualLen) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetWStr( 
            /* [in] */ long lSrcPos,
            /* [in] */ long lSrcLen,
            /* [size_is][out] */ WCHAR __RPC_FAR *pszDest,
            /* [in] */ long cchDest,
            /* [out] */ long __RPC_FAR *pcchActual,
            /* [out] */ long __RPC_FAR *plActualLen) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetStrBufW( 
            /* [in] */ long lSrcPos,
            /* [in] */ long lSrcMaxLen,
            /* [out] */ IMLangStringBufW __RPC_FAR *__RPC_FAR *ppDestBuf,
            /* [out] */ long __RPC_FAR *plDestLen) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LockWStr( 
            /* [in] */ long lSrcPos,
            /* [in] */ long lSrcLen,
            /* [in] */ long lFlags,
            /* [in] */ long cchRequest,
            /* [size_is][size_is][out] */ WCHAR __RPC_FAR *__RPC_FAR *ppszDest,
            /* [out] */ long __RPC_FAR *pcchDest,
            /* [out] */ long __RPC_FAR *plDestLen) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE UnlockWStr( 
            /* [size_is][in] */ const WCHAR __RPC_FAR *pszSrc,
            /* [in] */ long cchSrc,
            /* [out] */ long __RPC_FAR *pcchActual,
            /* [out] */ long __RPC_FAR *plActualLen) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetLocale( 
            /* [in] */ long lDestPos,
            /* [in] */ long lDestLen,
            /* [in] */ LCID locale) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetLocale( 
            /* [in] */ long lSrcPos,
            /* [in] */ long lSrcMaxLen,
            /* [out] */ LCID __RPC_FAR *plocale,
            /* [out] */ long __RPC_FAR *plLocalePos,
            /* [out] */ long __RPC_FAR *plLocaleLen) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMLangStringWStrVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMLangStringWStr __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMLangStringWStr __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMLangStringWStr __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Sync )( 
            IMLangStringWStr __RPC_FAR * This,
            /* [in] */ BOOL fNoAccess);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLength )( 
            IMLangStringWStr __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plLen);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMLStr )( 
            IMLangStringWStr __RPC_FAR * This,
            /* [in] */ long lDestPos,
            /* [in] */ long lDestLen,
            /* [in] */ IUnknown __RPC_FAR *pSrcMLStr,
            /* [in] */ long lSrcPos,
            /* [in] */ long lSrcLen);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMLStr )( 
            IMLangStringWStr __RPC_FAR * This,
            /* [in] */ long lSrcPos,
            /* [in] */ long lSrcLen,
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ DWORD dwClsContext,
            /* [in] */ const IID __RPC_FAR *piid,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppDestMLStr,
            /* [out] */ long __RPC_FAR *plDestPos,
            /* [out] */ long __RPC_FAR *plDestLen);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetWStr )( 
            IMLangStringWStr __RPC_FAR * This,
            /* [in] */ long lDestPos,
            /* [in] */ long lDestLen,
            /* [size_is][in] */ const WCHAR __RPC_FAR *pszSrc,
            /* [in] */ long cchSrc,
            /* [out] */ long __RPC_FAR *pcchActual,
            /* [out] */ long __RPC_FAR *plActualLen);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetStrBufW )( 
            IMLangStringWStr __RPC_FAR * This,
            /* [in] */ long lDestPos,
            /* [in] */ long lDestLen,
            /* [in] */ IMLangStringBufW __RPC_FAR *pSrcBuf,
            /* [out] */ long __RPC_FAR *pcchActual,
            /* [out] */ long __RPC_FAR *plActualLen);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetWStr )( 
            IMLangStringWStr __RPC_FAR * This,
            /* [in] */ long lSrcPos,
            /* [in] */ long lSrcLen,
            /* [size_is][out] */ WCHAR __RPC_FAR *pszDest,
            /* [in] */ long cchDest,
            /* [out] */ long __RPC_FAR *pcchActual,
            /* [out] */ long __RPC_FAR *plActualLen);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStrBufW )( 
            IMLangStringWStr __RPC_FAR * This,
            /* [in] */ long lSrcPos,
            /* [in] */ long lSrcMaxLen,
            /* [out] */ IMLangStringBufW __RPC_FAR *__RPC_FAR *ppDestBuf,
            /* [out] */ long __RPC_FAR *plDestLen);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LockWStr )( 
            IMLangStringWStr __RPC_FAR * This,
            /* [in] */ long lSrcPos,
            /* [in] */ long lSrcLen,
            /* [in] */ long lFlags,
            /* [in] */ long cchRequest,
            /* [size_is][size_is][out] */ WCHAR __RPC_FAR *__RPC_FAR *ppszDest,
            /* [out] */ long __RPC_FAR *pcchDest,
            /* [out] */ long __RPC_FAR *plDestLen);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnlockWStr )( 
            IMLangStringWStr __RPC_FAR * This,
            /* [size_is][in] */ const WCHAR __RPC_FAR *pszSrc,
            /* [in] */ long cchSrc,
            /* [out] */ long __RPC_FAR *pcchActual,
            /* [out] */ long __RPC_FAR *plActualLen);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetLocale )( 
            IMLangStringWStr __RPC_FAR * This,
            /* [in] */ long lDestPos,
            /* [in] */ long lDestLen,
            /* [in] */ LCID locale);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLocale )( 
            IMLangStringWStr __RPC_FAR * This,
            /* [in] */ long lSrcPos,
            /* [in] */ long lSrcMaxLen,
            /* [out] */ LCID __RPC_FAR *plocale,
            /* [out] */ long __RPC_FAR *plLocalePos,
            /* [out] */ long __RPC_FAR *plLocaleLen);
        
        END_INTERFACE
    } IMLangStringWStrVtbl;

    interface IMLangStringWStr
    {
        CONST_VTBL struct IMLangStringWStrVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMLangStringWStr_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMLangStringWStr_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMLangStringWStr_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMLangStringWStr_Sync(This,fNoAccess)	\
    (This)->lpVtbl -> Sync(This,fNoAccess)

#define IMLangStringWStr_GetLength(This,plLen)	\
    (This)->lpVtbl -> GetLength(This,plLen)

#define IMLangStringWStr_SetMLStr(This,lDestPos,lDestLen,pSrcMLStr,lSrcPos,lSrcLen)	\
    (This)->lpVtbl -> SetMLStr(This,lDestPos,lDestLen,pSrcMLStr,lSrcPos,lSrcLen)

#define IMLangStringWStr_GetMLStr(This,lSrcPos,lSrcLen,pUnkOuter,dwClsContext,piid,ppDestMLStr,plDestPos,plDestLen)	\
    (This)->lpVtbl -> GetMLStr(This,lSrcPos,lSrcLen,pUnkOuter,dwClsContext,piid,ppDestMLStr,plDestPos,plDestLen)


#define IMLangStringWStr_SetWStr(This,lDestPos,lDestLen,pszSrc,cchSrc,pcchActual,plActualLen)	\
    (This)->lpVtbl -> SetWStr(This,lDestPos,lDestLen,pszSrc,cchSrc,pcchActual,plActualLen)

#define IMLangStringWStr_SetStrBufW(This,lDestPos,lDestLen,pSrcBuf,pcchActual,plActualLen)	\
    (This)->lpVtbl -> SetStrBufW(This,lDestPos,lDestLen,pSrcBuf,pcchActual,plActualLen)

#define IMLangStringWStr_GetWStr(This,lSrcPos,lSrcLen,pszDest,cchDest,pcchActual,plActualLen)	\
    (This)->lpVtbl -> GetWStr(This,lSrcPos,lSrcLen,pszDest,cchDest,pcchActual,plActualLen)

#define IMLangStringWStr_GetStrBufW(This,lSrcPos,lSrcMaxLen,ppDestBuf,plDestLen)	\
    (This)->lpVtbl -> GetStrBufW(This,lSrcPos,lSrcMaxLen,ppDestBuf,plDestLen)

#define IMLangStringWStr_LockWStr(This,lSrcPos,lSrcLen,lFlags,cchRequest,ppszDest,pcchDest,plDestLen)	\
    (This)->lpVtbl -> LockWStr(This,lSrcPos,lSrcLen,lFlags,cchRequest,ppszDest,pcchDest,plDestLen)

#define IMLangStringWStr_UnlockWStr(This,pszSrc,cchSrc,pcchActual,plActualLen)	\
    (This)->lpVtbl -> UnlockWStr(This,pszSrc,cchSrc,pcchActual,plActualLen)

#define IMLangStringWStr_SetLocale(This,lDestPos,lDestLen,locale)	\
    (This)->lpVtbl -> SetLocale(This,lDestPos,lDestLen,locale)

#define IMLangStringWStr_GetLocale(This,lSrcPos,lSrcMaxLen,plocale,plLocalePos,plLocaleLen)	\
    (This)->lpVtbl -> GetLocale(This,lSrcPos,lSrcMaxLen,plocale,plLocalePos,plLocaleLen)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangStringWStr_SetWStr_Proxy( 
    IMLangStringWStr __RPC_FAR * This,
    /* [in] */ long lDestPos,
    /* [in] */ long lDestLen,
    /* [size_is][in] */ const WCHAR __RPC_FAR *pszSrc,
    /* [in] */ long cchSrc,
    /* [out] */ long __RPC_FAR *pcchActual,
    /* [out] */ long __RPC_FAR *plActualLen);


void __RPC_STUB IMLangStringWStr_SetWStr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangStringWStr_SetStrBufW_Proxy( 
    IMLangStringWStr __RPC_FAR * This,
    /* [in] */ long lDestPos,
    /* [in] */ long lDestLen,
    /* [in] */ IMLangStringBufW __RPC_FAR *pSrcBuf,
    /* [out] */ long __RPC_FAR *pcchActual,
    /* [out] */ long __RPC_FAR *plActualLen);


void __RPC_STUB IMLangStringWStr_SetStrBufW_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangStringWStr_GetWStr_Proxy( 
    IMLangStringWStr __RPC_FAR * This,
    /* [in] */ long lSrcPos,
    /* [in] */ long lSrcLen,
    /* [size_is][out] */ WCHAR __RPC_FAR *pszDest,
    /* [in] */ long cchDest,
    /* [out] */ long __RPC_FAR *pcchActual,
    /* [out] */ long __RPC_FAR *plActualLen);


void __RPC_STUB IMLangStringWStr_GetWStr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangStringWStr_GetStrBufW_Proxy( 
    IMLangStringWStr __RPC_FAR * This,
    /* [in] */ long lSrcPos,
    /* [in] */ long lSrcMaxLen,
    /* [out] */ IMLangStringBufW __RPC_FAR *__RPC_FAR *ppDestBuf,
    /* [out] */ long __RPC_FAR *plDestLen);


void __RPC_STUB IMLangStringWStr_GetStrBufW_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangStringWStr_LockWStr_Proxy( 
    IMLangStringWStr __RPC_FAR * This,
    /* [in] */ long lSrcPos,
    /* [in] */ long lSrcLen,
    /* [in] */ long lFlags,
    /* [in] */ long cchRequest,
    /* [size_is][size_is][out] */ WCHAR __RPC_FAR *__RPC_FAR *ppszDest,
    /* [out] */ long __RPC_FAR *pcchDest,
    /* [out] */ long __RPC_FAR *plDestLen);


void __RPC_STUB IMLangStringWStr_LockWStr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangStringWStr_UnlockWStr_Proxy( 
    IMLangStringWStr __RPC_FAR * This,
    /* [size_is][in] */ const WCHAR __RPC_FAR *pszSrc,
    /* [in] */ long cchSrc,
    /* [out] */ long __RPC_FAR *pcchActual,
    /* [out] */ long __RPC_FAR *plActualLen);


void __RPC_STUB IMLangStringWStr_UnlockWStr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangStringWStr_SetLocale_Proxy( 
    IMLangStringWStr __RPC_FAR * This,
    /* [in] */ long lDestPos,
    /* [in] */ long lDestLen,
    /* [in] */ LCID locale);


void __RPC_STUB IMLangStringWStr_SetLocale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangStringWStr_GetLocale_Proxy( 
    IMLangStringWStr __RPC_FAR * This,
    /* [in] */ long lSrcPos,
    /* [in] */ long lSrcMaxLen,
    /* [out] */ LCID __RPC_FAR *plocale,
    /* [out] */ long __RPC_FAR *plLocalePos,
    /* [out] */ long __RPC_FAR *plLocaleLen);


void __RPC_STUB IMLangStringWStr_GetLocale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMLangStringWStr_INTERFACE_DEFINED__ */


#ifndef __IMLangStringAStr_INTERFACE_DEFINED__
#define __IMLangStringAStr_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMLangStringAStr
 * at Thu Sep 11 10:59:43 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][unique][helpstring][uuid] */ 



EXTERN_C const IID IID_IMLangStringAStr;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C04D65D2-B70D-11D0-B188-00AA0038C969")
    IMLangStringAStr : public IMLangString
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetAStr( 
            /* [in] */ long lDestPos,
            /* [in] */ long lDestLen,
            /* [in] */ UINT uCodePage,
            /* [size_is][in] */ const CHAR __RPC_FAR *pszSrc,
            /* [in] */ long cchSrc,
            /* [out] */ long __RPC_FAR *pcchActual,
            /* [out] */ long __RPC_FAR *plActualLen) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetStrBufA( 
            /* [in] */ long lDestPos,
            /* [in] */ long lDestLen,
            /* [in] */ UINT uCodePage,
            /* [in] */ IMLangStringBufA __RPC_FAR *pSrcBuf,
            /* [out] */ long __RPC_FAR *pcchActual,
            /* [out] */ long __RPC_FAR *plActualLen) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetAStr( 
            /* [in] */ long lSrcPos,
            /* [in] */ long lSrcLen,
            /* [in] */ UINT uCodePageIn,
            /* [out] */ UINT __RPC_FAR *puCodePageOut,
            /* [size_is][out] */ CHAR __RPC_FAR *pszDest,
            /* [in] */ long cchDest,
            /* [out] */ long __RPC_FAR *pcchActual,
            /* [out] */ long __RPC_FAR *plActualLen) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetStrBufA( 
            /* [in] */ long lSrcPos,
            /* [in] */ long lSrcMaxLen,
            /* [out] */ UINT __RPC_FAR *puDestCodePage,
            /* [out] */ IMLangStringBufA __RPC_FAR *__RPC_FAR *ppDestBuf,
            /* [out] */ long __RPC_FAR *plDestLen) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LockAStr( 
            /* [in] */ long lSrcPos,
            /* [in] */ long lSrcLen,
            /* [in] */ long lFlags,
            /* [in] */ UINT uCodePageIn,
            /* [in] */ long cchRequest,
            /* [out] */ UINT __RPC_FAR *puCodePageOut,
            /* [size_is][size_is][out] */ CHAR __RPC_FAR *__RPC_FAR *ppszDest,
            /* [out] */ long __RPC_FAR *pcchDest,
            /* [out] */ long __RPC_FAR *plDestLen) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE UnlockAStr( 
            /* [size_is][in] */ const CHAR __RPC_FAR *pszSrc,
            /* [in] */ long cchSrc,
            /* [out] */ long __RPC_FAR *pcchActual,
            /* [out] */ long __RPC_FAR *plActualLen) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetLocale( 
            /* [in] */ long lDestPos,
            /* [in] */ long lDestLen,
            /* [in] */ LCID locale) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetLocale( 
            /* [in] */ long lSrcPos,
            /* [in] */ long lSrcMaxLen,
            /* [out] */ LCID __RPC_FAR *plocale,
            /* [out] */ long __RPC_FAR *plLocalePos,
            /* [out] */ long __RPC_FAR *plLocaleLen) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMLangStringAStrVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMLangStringAStr __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMLangStringAStr __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMLangStringAStr __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Sync )( 
            IMLangStringAStr __RPC_FAR * This,
            /* [in] */ BOOL fNoAccess);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLength )( 
            IMLangStringAStr __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plLen);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMLStr )( 
            IMLangStringAStr __RPC_FAR * This,
            /* [in] */ long lDestPos,
            /* [in] */ long lDestLen,
            /* [in] */ IUnknown __RPC_FAR *pSrcMLStr,
            /* [in] */ long lSrcPos,
            /* [in] */ long lSrcLen);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMLStr )( 
            IMLangStringAStr __RPC_FAR * This,
            /* [in] */ long lSrcPos,
            /* [in] */ long lSrcLen,
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ DWORD dwClsContext,
            /* [in] */ const IID __RPC_FAR *piid,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppDestMLStr,
            /* [out] */ long __RPC_FAR *plDestPos,
            /* [out] */ long __RPC_FAR *plDestLen);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAStr )( 
            IMLangStringAStr __RPC_FAR * This,
            /* [in] */ long lDestPos,
            /* [in] */ long lDestLen,
            /* [in] */ UINT uCodePage,
            /* [size_is][in] */ const CHAR __RPC_FAR *pszSrc,
            /* [in] */ long cchSrc,
            /* [out] */ long __RPC_FAR *pcchActual,
            /* [out] */ long __RPC_FAR *plActualLen);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetStrBufA )( 
            IMLangStringAStr __RPC_FAR * This,
            /* [in] */ long lDestPos,
            /* [in] */ long lDestLen,
            /* [in] */ UINT uCodePage,
            /* [in] */ IMLangStringBufA __RPC_FAR *pSrcBuf,
            /* [out] */ long __RPC_FAR *pcchActual,
            /* [out] */ long __RPC_FAR *plActualLen);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAStr )( 
            IMLangStringAStr __RPC_FAR * This,
            /* [in] */ long lSrcPos,
            /* [in] */ long lSrcLen,
            /* [in] */ UINT uCodePageIn,
            /* [out] */ UINT __RPC_FAR *puCodePageOut,
            /* [size_is][out] */ CHAR __RPC_FAR *pszDest,
            /* [in] */ long cchDest,
            /* [out] */ long __RPC_FAR *pcchActual,
            /* [out] */ long __RPC_FAR *plActualLen);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStrBufA )( 
            IMLangStringAStr __RPC_FAR * This,
            /* [in] */ long lSrcPos,
            /* [in] */ long lSrcMaxLen,
            /* [out] */ UINT __RPC_FAR *puDestCodePage,
            /* [out] */ IMLangStringBufA __RPC_FAR *__RPC_FAR *ppDestBuf,
            /* [out] */ long __RPC_FAR *plDestLen);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LockAStr )( 
            IMLangStringAStr __RPC_FAR * This,
            /* [in] */ long lSrcPos,
            /* [in] */ long lSrcLen,
            /* [in] */ long lFlags,
            /* [in] */ UINT uCodePageIn,
            /* [in] */ long cchRequest,
            /* [out] */ UINT __RPC_FAR *puCodePageOut,
            /* [size_is][size_is][out] */ CHAR __RPC_FAR *__RPC_FAR *ppszDest,
            /* [out] */ long __RPC_FAR *pcchDest,
            /* [out] */ long __RPC_FAR *plDestLen);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnlockAStr )( 
            IMLangStringAStr __RPC_FAR * This,
            /* [size_is][in] */ const CHAR __RPC_FAR *pszSrc,
            /* [in] */ long cchSrc,
            /* [out] */ long __RPC_FAR *pcchActual,
            /* [out] */ long __RPC_FAR *plActualLen);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetLocale )( 
            IMLangStringAStr __RPC_FAR * This,
            /* [in] */ long lDestPos,
            /* [in] */ long lDestLen,
            /* [in] */ LCID locale);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLocale )( 
            IMLangStringAStr __RPC_FAR * This,
            /* [in] */ long lSrcPos,
            /* [in] */ long lSrcMaxLen,
            /* [out] */ LCID __RPC_FAR *plocale,
            /* [out] */ long __RPC_FAR *plLocalePos,
            /* [out] */ long __RPC_FAR *plLocaleLen);
        
        END_INTERFACE
    } IMLangStringAStrVtbl;

    interface IMLangStringAStr
    {
        CONST_VTBL struct IMLangStringAStrVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMLangStringAStr_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMLangStringAStr_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMLangStringAStr_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMLangStringAStr_Sync(This,fNoAccess)	\
    (This)->lpVtbl -> Sync(This,fNoAccess)

#define IMLangStringAStr_GetLength(This,plLen)	\
    (This)->lpVtbl -> GetLength(This,plLen)

#define IMLangStringAStr_SetMLStr(This,lDestPos,lDestLen,pSrcMLStr,lSrcPos,lSrcLen)	\
    (This)->lpVtbl -> SetMLStr(This,lDestPos,lDestLen,pSrcMLStr,lSrcPos,lSrcLen)

#define IMLangStringAStr_GetMLStr(This,lSrcPos,lSrcLen,pUnkOuter,dwClsContext,piid,ppDestMLStr,plDestPos,plDestLen)	\
    (This)->lpVtbl -> GetMLStr(This,lSrcPos,lSrcLen,pUnkOuter,dwClsContext,piid,ppDestMLStr,plDestPos,plDestLen)


#define IMLangStringAStr_SetAStr(This,lDestPos,lDestLen,uCodePage,pszSrc,cchSrc,pcchActual,plActualLen)	\
    (This)->lpVtbl -> SetAStr(This,lDestPos,lDestLen,uCodePage,pszSrc,cchSrc,pcchActual,plActualLen)

#define IMLangStringAStr_SetStrBufA(This,lDestPos,lDestLen,uCodePage,pSrcBuf,pcchActual,plActualLen)	\
    (This)->lpVtbl -> SetStrBufA(This,lDestPos,lDestLen,uCodePage,pSrcBuf,pcchActual,plActualLen)

#define IMLangStringAStr_GetAStr(This,lSrcPos,lSrcLen,uCodePageIn,puCodePageOut,pszDest,cchDest,pcchActual,plActualLen)	\
    (This)->lpVtbl -> GetAStr(This,lSrcPos,lSrcLen,uCodePageIn,puCodePageOut,pszDest,cchDest,pcchActual,plActualLen)

#define IMLangStringAStr_GetStrBufA(This,lSrcPos,lSrcMaxLen,puDestCodePage,ppDestBuf,plDestLen)	\
    (This)->lpVtbl -> GetStrBufA(This,lSrcPos,lSrcMaxLen,puDestCodePage,ppDestBuf,plDestLen)

#define IMLangStringAStr_LockAStr(This,lSrcPos,lSrcLen,lFlags,uCodePageIn,cchRequest,puCodePageOut,ppszDest,pcchDest,plDestLen)	\
    (This)->lpVtbl -> LockAStr(This,lSrcPos,lSrcLen,lFlags,uCodePageIn,cchRequest,puCodePageOut,ppszDest,pcchDest,plDestLen)

#define IMLangStringAStr_UnlockAStr(This,pszSrc,cchSrc,pcchActual,plActualLen)	\
    (This)->lpVtbl -> UnlockAStr(This,pszSrc,cchSrc,pcchActual,plActualLen)

#define IMLangStringAStr_SetLocale(This,lDestPos,lDestLen,locale)	\
    (This)->lpVtbl -> SetLocale(This,lDestPos,lDestLen,locale)

#define IMLangStringAStr_GetLocale(This,lSrcPos,lSrcMaxLen,plocale,plLocalePos,plLocaleLen)	\
    (This)->lpVtbl -> GetLocale(This,lSrcPos,lSrcMaxLen,plocale,plLocalePos,plLocaleLen)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangStringAStr_SetAStr_Proxy( 
    IMLangStringAStr __RPC_FAR * This,
    /* [in] */ long lDestPos,
    /* [in] */ long lDestLen,
    /* [in] */ UINT uCodePage,
    /* [size_is][in] */ const CHAR __RPC_FAR *pszSrc,
    /* [in] */ long cchSrc,
    /* [out] */ long __RPC_FAR *pcchActual,
    /* [out] */ long __RPC_FAR *plActualLen);


void __RPC_STUB IMLangStringAStr_SetAStr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangStringAStr_SetStrBufA_Proxy( 
    IMLangStringAStr __RPC_FAR * This,
    /* [in] */ long lDestPos,
    /* [in] */ long lDestLen,
    /* [in] */ UINT uCodePage,
    /* [in] */ IMLangStringBufA __RPC_FAR *pSrcBuf,
    /* [out] */ long __RPC_FAR *pcchActual,
    /* [out] */ long __RPC_FAR *plActualLen);


void __RPC_STUB IMLangStringAStr_SetStrBufA_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangStringAStr_GetAStr_Proxy( 
    IMLangStringAStr __RPC_FAR * This,
    /* [in] */ long lSrcPos,
    /* [in] */ long lSrcLen,
    /* [in] */ UINT uCodePageIn,
    /* [out] */ UINT __RPC_FAR *puCodePageOut,
    /* [size_is][out] */ CHAR __RPC_FAR *pszDest,
    /* [in] */ long cchDest,
    /* [out] */ long __RPC_FAR *pcchActual,
    /* [out] */ long __RPC_FAR *plActualLen);


void __RPC_STUB IMLangStringAStr_GetAStr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangStringAStr_GetStrBufA_Proxy( 
    IMLangStringAStr __RPC_FAR * This,
    /* [in] */ long lSrcPos,
    /* [in] */ long lSrcMaxLen,
    /* [out] */ UINT __RPC_FAR *puDestCodePage,
    /* [out] */ IMLangStringBufA __RPC_FAR *__RPC_FAR *ppDestBuf,
    /* [out] */ long __RPC_FAR *plDestLen);


void __RPC_STUB IMLangStringAStr_GetStrBufA_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangStringAStr_LockAStr_Proxy( 
    IMLangStringAStr __RPC_FAR * This,
    /* [in] */ long lSrcPos,
    /* [in] */ long lSrcLen,
    /* [in] */ long lFlags,
    /* [in] */ UINT uCodePageIn,
    /* [in] */ long cchRequest,
    /* [out] */ UINT __RPC_FAR *puCodePageOut,
    /* [size_is][size_is][out] */ CHAR __RPC_FAR *__RPC_FAR *ppszDest,
    /* [out] */ long __RPC_FAR *pcchDest,
    /* [out] */ long __RPC_FAR *plDestLen);


void __RPC_STUB IMLangStringAStr_LockAStr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangStringAStr_UnlockAStr_Proxy( 
    IMLangStringAStr __RPC_FAR * This,
    /* [size_is][in] */ const CHAR __RPC_FAR *pszSrc,
    /* [in] */ long cchSrc,
    /* [out] */ long __RPC_FAR *pcchActual,
    /* [out] */ long __RPC_FAR *plActualLen);


void __RPC_STUB IMLangStringAStr_UnlockAStr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangStringAStr_SetLocale_Proxy( 
    IMLangStringAStr __RPC_FAR * This,
    /* [in] */ long lDestPos,
    /* [in] */ long lDestLen,
    /* [in] */ LCID locale);


void __RPC_STUB IMLangStringAStr_SetLocale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangStringAStr_GetLocale_Proxy( 
    IMLangStringAStr __RPC_FAR * This,
    /* [in] */ long lSrcPos,
    /* [in] */ long lSrcMaxLen,
    /* [out] */ LCID __RPC_FAR *plocale,
    /* [out] */ long __RPC_FAR *plLocalePos,
    /* [out] */ long __RPC_FAR *plLocaleLen);


void __RPC_STUB IMLangStringAStr_GetLocale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMLangStringAStr_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CMLangString;

#ifdef __cplusplus

class DECLSPEC_UUID("C04D65CF-B70D-11D0-B188-00AA0038C969")
CMLangString;
#endif

#ifndef __IMLangLineBreakConsole_INTERFACE_DEFINED__
#define __IMLangLineBreakConsole_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMLangLineBreakConsole
 * at Thu Sep 11 10:59:43 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][unique][helpstring][uuid] */ 



EXTERN_C const IID IID_IMLangLineBreakConsole;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F5BE2EE1-BFD7-11D0-B188-00AA0038C969")
    IMLangLineBreakConsole : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE BreakLineML( 
            /* [in] */ IMLangString __RPC_FAR *pSrcMLStr,
            /* [in] */ long lSrcPos,
            /* [in] */ long lSrcLen,
            /* [in] */ long cMinColumns,
            /* [in] */ long cMaxColumns,
            /* [out] */ long __RPC_FAR *plLineLen,
            /* [out] */ long __RPC_FAR *plSkipLen) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE BreakLineW( 
            /* [in] */ LCID locale,
            /* [size_is][in] */ const WCHAR __RPC_FAR *pszSrc,
            /* [in] */ long cchSrc,
            /* [in] */ long cMaxColumns,
            /* [out] */ long __RPC_FAR *pcchLine,
            /* [out] */ long __RPC_FAR *pcchSkip) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE BreakLineA( 
            /* [in] */ LCID locale,
            /* [in] */ UINT uCodePage,
            /* [size_is][in] */ const CHAR __RPC_FAR *pszSrc,
            /* [in] */ long cchSrc,
            /* [in] */ long cMaxColumns,
            /* [out] */ long __RPC_FAR *pcchLine,
            /* [out] */ long __RPC_FAR *pcchSkip) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMLangLineBreakConsoleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMLangLineBreakConsole __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMLangLineBreakConsole __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMLangLineBreakConsole __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BreakLineML )( 
            IMLangLineBreakConsole __RPC_FAR * This,
            /* [in] */ IMLangString __RPC_FAR *pSrcMLStr,
            /* [in] */ long lSrcPos,
            /* [in] */ long lSrcLen,
            /* [in] */ long cMinColumns,
            /* [in] */ long cMaxColumns,
            /* [out] */ long __RPC_FAR *plLineLen,
            /* [out] */ long __RPC_FAR *plSkipLen);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BreakLineW )( 
            IMLangLineBreakConsole __RPC_FAR * This,
            /* [in] */ LCID locale,
            /* [size_is][in] */ const WCHAR __RPC_FAR *pszSrc,
            /* [in] */ long cchSrc,
            /* [in] */ long cMaxColumns,
            /* [out] */ long __RPC_FAR *pcchLine,
            /* [out] */ long __RPC_FAR *pcchSkip);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BreakLineA )( 
            IMLangLineBreakConsole __RPC_FAR * This,
            /* [in] */ LCID locale,
            /* [in] */ UINT uCodePage,
            /* [size_is][in] */ const CHAR __RPC_FAR *pszSrc,
            /* [in] */ long cchSrc,
            /* [in] */ long cMaxColumns,
            /* [out] */ long __RPC_FAR *pcchLine,
            /* [out] */ long __RPC_FAR *pcchSkip);
        
        END_INTERFACE
    } IMLangLineBreakConsoleVtbl;

    interface IMLangLineBreakConsole
    {
        CONST_VTBL struct IMLangLineBreakConsoleVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMLangLineBreakConsole_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMLangLineBreakConsole_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMLangLineBreakConsole_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMLangLineBreakConsole_BreakLineML(This,pSrcMLStr,lSrcPos,lSrcLen,cMinColumns,cMaxColumns,plLineLen,plSkipLen)	\
    (This)->lpVtbl -> BreakLineML(This,pSrcMLStr,lSrcPos,lSrcLen,cMinColumns,cMaxColumns,plLineLen,plSkipLen)

#define IMLangLineBreakConsole_BreakLineW(This,locale,pszSrc,cchSrc,cMaxColumns,pcchLine,pcchSkip)	\
    (This)->lpVtbl -> BreakLineW(This,locale,pszSrc,cchSrc,cMaxColumns,pcchLine,pcchSkip)

#define IMLangLineBreakConsole_BreakLineA(This,locale,uCodePage,pszSrc,cchSrc,cMaxColumns,pcchLine,pcchSkip)	\
    (This)->lpVtbl -> BreakLineA(This,locale,uCodePage,pszSrc,cchSrc,cMaxColumns,pcchLine,pcchSkip)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangLineBreakConsole_BreakLineML_Proxy( 
    IMLangLineBreakConsole __RPC_FAR * This,
    /* [in] */ IMLangString __RPC_FAR *pSrcMLStr,
    /* [in] */ long lSrcPos,
    /* [in] */ long lSrcLen,
    /* [in] */ long cMinColumns,
    /* [in] */ long cMaxColumns,
    /* [out] */ long __RPC_FAR *plLineLen,
    /* [out] */ long __RPC_FAR *plSkipLen);


void __RPC_STUB IMLangLineBreakConsole_BreakLineML_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangLineBreakConsole_BreakLineW_Proxy( 
    IMLangLineBreakConsole __RPC_FAR * This,
    /* [in] */ LCID locale,
    /* [size_is][in] */ const WCHAR __RPC_FAR *pszSrc,
    /* [in] */ long cchSrc,
    /* [in] */ long cMaxColumns,
    /* [out] */ long __RPC_FAR *pcchLine,
    /* [out] */ long __RPC_FAR *pcchSkip);


void __RPC_STUB IMLangLineBreakConsole_BreakLineW_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangLineBreakConsole_BreakLineA_Proxy( 
    IMLangLineBreakConsole __RPC_FAR * This,
    /* [in] */ LCID locale,
    /* [in] */ UINT uCodePage,
    /* [size_is][in] */ const CHAR __RPC_FAR *pszSrc,
    /* [in] */ long cchSrc,
    /* [in] */ long cMaxColumns,
    /* [out] */ long __RPC_FAR *pcchLine,
    /* [out] */ long __RPC_FAR *pcchSkip);


void __RPC_STUB IMLangLineBreakConsole_BreakLineA_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMLangLineBreakConsole_INTERFACE_DEFINED__ */


#ifndef __IEnumCodePage_INTERFACE_DEFINED__
#define __IEnumCodePage_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IEnumCodePage
 * at Thu Sep 11 10:59:43 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][uuid][object] */ 


#define	MAX_MIMECP_NAME	( 64 )

#define	MAX_MIMECSET_NAME	( 50 )

#define	MAX_MIMEFACE_NAME	( 32 )

typedef 
enum tagMIMECONTF
    {	MIMECONTF_MAILNEWS	= 0x1,
	MIMECONTF_BROWSER	= 0x2,
	MIMECONTF_MINIMAL	= 0x4,
	MIMECONTF_SAVABLE_MAILNEWS	= 0x100,
	MIMECONTF_SAVABLE_BROWSER	= 0x200,
	MIMECONTF_PRIVCONVERTER	= 0x10000,
	MIMECONTF_VALID	= 0x20000
    }	MIMECONTF;

typedef struct  tagMIMECPINFO
    {
    DWORD dwFlags;
    UINT uiCodePage;
    UINT uiFamilyCodePage;
    WCHAR wszDescription[ 64 ];
    WCHAR wszWebCharset[ 50 ];
    WCHAR wszHeaderCharset[ 50 ];
    WCHAR wszBodyCharset[ 50 ];
    WCHAR wszFixedWidthFont[ 32 ];
    WCHAR wszProportionalFont[ 32 ];
    BYTE bGDICharset;
    }	MIMECPINFO;

typedef struct tagMIMECPINFO __RPC_FAR *PMIMECPINFO;

typedef struct  tagMIMECSETINFO
    {
    UINT uiCodePage;
    UINT uiInternetEncoding;
    WCHAR wszCharset[ 50 ];
    }	MIMECSETINFO;

typedef struct tagMIMECSETINFO __RPC_FAR *PMIMECSETINFO;

typedef /* [unique] */ IEnumCodePage __RPC_FAR *LPENUMCODEPAGE;


EXTERN_C const IID IID_IEnumCodePage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("275c23e3-3747-11d0-9fea-00aa003f8646")
    IEnumCodePage : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumCodePage __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ PMIMECPINFO rgelt,
            /* [out] */ ULONG __RPC_FAR *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumCodePageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEnumCodePage __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEnumCodePage __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEnumCodePage __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            IEnumCodePage __RPC_FAR * This,
            /* [out] */ IEnumCodePage __RPC_FAR *__RPC_FAR *ppEnum);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IEnumCodePage __RPC_FAR * This,
            /* [in] */ ULONG celt,
            /* [out] */ PMIMECPINFO rgelt,
            /* [out] */ ULONG __RPC_FAR *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IEnumCodePage __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Skip )( 
            IEnumCodePage __RPC_FAR * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumCodePageVtbl;

    interface IEnumCodePage
    {
        CONST_VTBL struct IEnumCodePageVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumCodePage_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumCodePage_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumCodePage_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumCodePage_Clone(This,ppEnum)	\
    (This)->lpVtbl -> Clone(This,ppEnum)

#define IEnumCodePage_Next(This,celt,rgelt,pceltFetched)	\
    (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched)

#define IEnumCodePage_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumCodePage_Skip(This,celt)	\
    (This)->lpVtbl -> Skip(This,celt)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumCodePage_Clone_Proxy( 
    IEnumCodePage __RPC_FAR * This,
    /* [out] */ IEnumCodePage __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IEnumCodePage_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumCodePage_Next_Proxy( 
    IEnumCodePage __RPC_FAR * This,
    /* [in] */ ULONG celt,
    /* [out] */ PMIMECPINFO rgelt,
    /* [out] */ ULONG __RPC_FAR *pceltFetched);


void __RPC_STUB IEnumCodePage_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumCodePage_Reset_Proxy( 
    IEnumCodePage __RPC_FAR * This);


void __RPC_STUB IEnumCodePage_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumCodePage_Skip_Proxy( 
    IEnumCodePage __RPC_FAR * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IEnumCodePage_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumCodePage_INTERFACE_DEFINED__ */


#ifndef __IEnumRfc1766_INTERFACE_DEFINED__
#define __IEnumRfc1766_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IEnumRfc1766
 * at Thu Sep 11 10:59:43 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][uuid][object] */ 


#define	MAX_RFC1766_NAME	( 6 )

#define	MAX_LOCALE_NAME	( 32 )

typedef struct  tagRFC1766INFO
    {
    LCID lcid;
    WCHAR wszRfc1766[ 6 ];
    WCHAR wszLocaleName[ 32 ];
    }	RFC1766INFO;

typedef struct tagRFC1766INFO __RPC_FAR *PRFC1766INFO;

typedef /* [unique] */ IEnumRfc1766 __RPC_FAR *LPENUMRFC1766;


EXTERN_C const IID IID_IEnumRfc1766;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3dc39d1d-c030-11d0-b81b-00c04fc9b31f")
    IEnumRfc1766 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumRfc1766 __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ PRFC1766INFO rgelt,
            /* [out] */ ULONG __RPC_FAR *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumRfc1766Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEnumRfc1766 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEnumRfc1766 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEnumRfc1766 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            IEnumRfc1766 __RPC_FAR * This,
            /* [out] */ IEnumRfc1766 __RPC_FAR *__RPC_FAR *ppEnum);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IEnumRfc1766 __RPC_FAR * This,
            /* [in] */ ULONG celt,
            /* [out] */ PRFC1766INFO rgelt,
            /* [out] */ ULONG __RPC_FAR *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IEnumRfc1766 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Skip )( 
            IEnumRfc1766 __RPC_FAR * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumRfc1766Vtbl;

    interface IEnumRfc1766
    {
        CONST_VTBL struct IEnumRfc1766Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumRfc1766_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumRfc1766_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumRfc1766_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumRfc1766_Clone(This,ppEnum)	\
    (This)->lpVtbl -> Clone(This,ppEnum)

#define IEnumRfc1766_Next(This,celt,rgelt,pceltFetched)	\
    (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched)

#define IEnumRfc1766_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumRfc1766_Skip(This,celt)	\
    (This)->lpVtbl -> Skip(This,celt)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumRfc1766_Clone_Proxy( 
    IEnumRfc1766 __RPC_FAR * This,
    /* [out] */ IEnumRfc1766 __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IEnumRfc1766_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumRfc1766_Next_Proxy( 
    IEnumRfc1766 __RPC_FAR * This,
    /* [in] */ ULONG celt,
    /* [out] */ PRFC1766INFO rgelt,
    /* [out] */ ULONG __RPC_FAR *pceltFetched);


void __RPC_STUB IEnumRfc1766_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumRfc1766_Reset_Proxy( 
    IEnumRfc1766 __RPC_FAR * This);


void __RPC_STUB IEnumRfc1766_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumRfc1766_Skip_Proxy( 
    IEnumRfc1766 __RPC_FAR * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IEnumRfc1766_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumRfc1766_INTERFACE_DEFINED__ */


#ifndef __IMLangConvertCharset_INTERFACE_DEFINED__
#define __IMLangConvertCharset_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMLangConvertCharset
 * at Thu Sep 11 10:59:43 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][uuid][object] */ 


typedef 
enum tagMLCONVCHARF
    {	MLCONVCHARF_AUTODETECT	= 1,
	MLCONVCHARF_ENTITIZE	= 2
    }	MLCONVCHAR;

typedef /* [unique] */ IMLangConvertCharset __RPC_FAR *LPMLANGCONVERTCHARSET;


EXTERN_C const IID IID_IMLangConvertCharset;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("d66d6f98-cdaa-11d0-b822-00c04fc9b31f")
    IMLangConvertCharset : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ UINT uiSrcCodePage,
            /* [in] */ UINT uiDstCodePage,
            /* [in] */ DWORD dwProperty) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSourceCodePage( 
            /* [out] */ UINT __RPC_FAR *puiSrcCodePage) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDestinationCodePage( 
            /* [out] */ UINT __RPC_FAR *puiDstCodePage) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetProperty( 
            /* [out] */ DWORD __RPC_FAR *pdwProperty) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DoConversion( 
            /* [in] */ BYTE __RPC_FAR *pSrcStr,
            /* [out][in] */ UINT __RPC_FAR *pcSrcSize,
            /* [in] */ BYTE __RPC_FAR *pDstStr,
            /* [out][in] */ UINT __RPC_FAR *pcDstSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DoConversionToUnicode( 
            /* [in] */ CHAR __RPC_FAR *pSrcStr,
            /* [out][in] */ UINT __RPC_FAR *pcSrcSize,
            /* [in] */ WCHAR __RPC_FAR *pDstStr,
            /* [out][in] */ UINT __RPC_FAR *pcDstSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DoConversionFromUnicode( 
            /* [in] */ WCHAR __RPC_FAR *pSrcStr,
            /* [out][in] */ UINT __RPC_FAR *pcSrcSize,
            /* [in] */ CHAR __RPC_FAR *pDstStr,
            /* [out][in] */ UINT __RPC_FAR *pcDstSize) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMLangConvertCharsetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMLangConvertCharset __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMLangConvertCharset __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMLangConvertCharset __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IMLangConvertCharset __RPC_FAR * This,
            /* [in] */ UINT uiSrcCodePage,
            /* [in] */ UINT uiDstCodePage,
            /* [in] */ DWORD dwProperty);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSourceCodePage )( 
            IMLangConvertCharset __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *puiSrcCodePage);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDestinationCodePage )( 
            IMLangConvertCharset __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *puiDstCodePage);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetProperty )( 
            IMLangConvertCharset __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *pdwProperty);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DoConversion )( 
            IMLangConvertCharset __RPC_FAR * This,
            /* [in] */ BYTE __RPC_FAR *pSrcStr,
            /* [out][in] */ UINT __RPC_FAR *pcSrcSize,
            /* [in] */ BYTE __RPC_FAR *pDstStr,
            /* [out][in] */ UINT __RPC_FAR *pcDstSize);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DoConversionToUnicode )( 
            IMLangConvertCharset __RPC_FAR * This,
            /* [in] */ CHAR __RPC_FAR *pSrcStr,
            /* [out][in] */ UINT __RPC_FAR *pcSrcSize,
            /* [in] */ WCHAR __RPC_FAR *pDstStr,
            /* [out][in] */ UINT __RPC_FAR *pcDstSize);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DoConversionFromUnicode )( 
            IMLangConvertCharset __RPC_FAR * This,
            /* [in] */ WCHAR __RPC_FAR *pSrcStr,
            /* [out][in] */ UINT __RPC_FAR *pcSrcSize,
            /* [in] */ CHAR __RPC_FAR *pDstStr,
            /* [out][in] */ UINT __RPC_FAR *pcDstSize);
        
        END_INTERFACE
    } IMLangConvertCharsetVtbl;

    interface IMLangConvertCharset
    {
        CONST_VTBL struct IMLangConvertCharsetVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMLangConvertCharset_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMLangConvertCharset_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMLangConvertCharset_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMLangConvertCharset_Initialize(This,uiSrcCodePage,uiDstCodePage,dwProperty)	\
    (This)->lpVtbl -> Initialize(This,uiSrcCodePage,uiDstCodePage,dwProperty)

#define IMLangConvertCharset_GetSourceCodePage(This,puiSrcCodePage)	\
    (This)->lpVtbl -> GetSourceCodePage(This,puiSrcCodePage)

#define IMLangConvertCharset_GetDestinationCodePage(This,puiDstCodePage)	\
    (This)->lpVtbl -> GetDestinationCodePage(This,puiDstCodePage)

#define IMLangConvertCharset_GetProperty(This,pdwProperty)	\
    (This)->lpVtbl -> GetProperty(This,pdwProperty)

#define IMLangConvertCharset_DoConversion(This,pSrcStr,pcSrcSize,pDstStr,pcDstSize)	\
    (This)->lpVtbl -> DoConversion(This,pSrcStr,pcSrcSize,pDstStr,pcDstSize)

#define IMLangConvertCharset_DoConversionToUnicode(This,pSrcStr,pcSrcSize,pDstStr,pcDstSize)	\
    (This)->lpVtbl -> DoConversionToUnicode(This,pSrcStr,pcSrcSize,pDstStr,pcDstSize)

#define IMLangConvertCharset_DoConversionFromUnicode(This,pSrcStr,pcSrcSize,pDstStr,pcDstSize)	\
    (This)->lpVtbl -> DoConversionFromUnicode(This,pSrcStr,pcSrcSize,pDstStr,pcDstSize)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMLangConvertCharset_Initialize_Proxy( 
    IMLangConvertCharset __RPC_FAR * This,
    /* [in] */ UINT uiSrcCodePage,
    /* [in] */ UINT uiDstCodePage,
    /* [in] */ DWORD dwProperty);


void __RPC_STUB IMLangConvertCharset_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMLangConvertCharset_GetSourceCodePage_Proxy( 
    IMLangConvertCharset __RPC_FAR * This,
    /* [out] */ UINT __RPC_FAR *puiSrcCodePage);


void __RPC_STUB IMLangConvertCharset_GetSourceCodePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMLangConvertCharset_GetDestinationCodePage_Proxy( 
    IMLangConvertCharset __RPC_FAR * This,
    /* [out] */ UINT __RPC_FAR *puiDstCodePage);


void __RPC_STUB IMLangConvertCharset_GetDestinationCodePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMLangConvertCharset_GetProperty_Proxy( 
    IMLangConvertCharset __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *pdwProperty);


void __RPC_STUB IMLangConvertCharset_GetProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMLangConvertCharset_DoConversion_Proxy( 
    IMLangConvertCharset __RPC_FAR * This,
    /* [in] */ BYTE __RPC_FAR *pSrcStr,
    /* [out][in] */ UINT __RPC_FAR *pcSrcSize,
    /* [in] */ BYTE __RPC_FAR *pDstStr,
    /* [out][in] */ UINT __RPC_FAR *pcDstSize);


void __RPC_STUB IMLangConvertCharset_DoConversion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMLangConvertCharset_DoConversionToUnicode_Proxy( 
    IMLangConvertCharset __RPC_FAR * This,
    /* [in] */ CHAR __RPC_FAR *pSrcStr,
    /* [out][in] */ UINT __RPC_FAR *pcSrcSize,
    /* [in] */ WCHAR __RPC_FAR *pDstStr,
    /* [out][in] */ UINT __RPC_FAR *pcDstSize);


void __RPC_STUB IMLangConvertCharset_DoConversionToUnicode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMLangConvertCharset_DoConversionFromUnicode_Proxy( 
    IMLangConvertCharset __RPC_FAR * This,
    /* [in] */ WCHAR __RPC_FAR *pSrcStr,
    /* [out][in] */ UINT __RPC_FAR *pcSrcSize,
    /* [in] */ CHAR __RPC_FAR *pDstStr,
    /* [out][in] */ UINT __RPC_FAR *pcDstSize);


void __RPC_STUB IMLangConvertCharset_DoConversionFromUnicode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMLangConvertCharset_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CMLangConvertCharset;

#ifdef __cplusplus

class DECLSPEC_UUID("d66d6f99-cdaa-11d0-b822-00c04fc9b31f")
CMLangConvertCharset;
#endif

#ifndef __IMultiLanguage_INTERFACE_DEFINED__
#define __IMultiLanguage_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMultiLanguage
 * at Thu Sep 11 10:59:43 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][uuid][object] */ 


typedef /* [unique] */ IMultiLanguage __RPC_FAR *LPMULTILANGUAGE;


EXTERN_C const IID IID_IMultiLanguage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("275c23e1-3747-11d0-9fea-00aa003f8646")
    IMultiLanguage : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetNumberOfCodePageInfo( 
            /* [out] */ UINT __RPC_FAR *pcCodePage) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCodePageInfo( 
            /* [in] */ UINT uiCodePage,
            /* [out] */ PMIMECPINFO pCodePageInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFamilyCodePage( 
            /* [in] */ UINT uiCodePage,
            /* [out] */ UINT __RPC_FAR *puiFamilyCodePage) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumCodePages( 
            /* [in] */ DWORD grfFlags,
            /* [out] */ IEnumCodePage __RPC_FAR *__RPC_FAR *ppEnumCodePage) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCharsetInfo( 
            /* [in] */ BSTR Charset,
            /* [out] */ PMIMECSETINFO pCharsetInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsConvertible( 
            /* [in] */ DWORD dwSrcEncoding,
            /* [in] */ DWORD dwDstEncoding) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ConvertString( 
            /* [out][in] */ DWORD __RPC_FAR *pdwMode,
            /* [in] */ DWORD dwSrcEncoding,
            /* [in] */ DWORD dwDstEncoding,
            /* [in] */ BYTE __RPC_FAR *pSrcStr,
            /* [out][in] */ UINT __RPC_FAR *pcSrcSize,
            /* [in] */ BYTE __RPC_FAR *pDstStr,
            /* [out][in] */ UINT __RPC_FAR *pcDstSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ConvertStringToUnicode( 
            /* [out][in] */ DWORD __RPC_FAR *pdwMode,
            /* [in] */ DWORD dwEncoding,
            /* [in] */ CHAR __RPC_FAR *pSrcStr,
            /* [out][in] */ UINT __RPC_FAR *pcSrcSize,
            /* [in] */ WCHAR __RPC_FAR *pDstStr,
            /* [out][in] */ UINT __RPC_FAR *pcDstSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ConvertStringFromUnicode( 
            /* [out][in] */ DWORD __RPC_FAR *pdwMode,
            /* [in] */ DWORD dwEncoding,
            /* [in] */ WCHAR __RPC_FAR *pSrcStr,
            /* [out][in] */ UINT __RPC_FAR *pcSrcSize,
            /* [in] */ CHAR __RPC_FAR *pDstStr,
            /* [out][in] */ UINT __RPC_FAR *pcDstSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ConvertStringReset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRfc1766FromLcid( 
            /* [in] */ LCID Locale,
            /* [out] */ BSTR __RPC_FAR *pbstrRfc1766) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLcidFromRfc1766( 
            /* [out] */ LCID __RPC_FAR *pLocale,
            /* [in] */ BSTR bstrRfc1766) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumRfc1766( 
            /* [out] */ IEnumRfc1766 __RPC_FAR *__RPC_FAR *ppEnumRfc1766) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRfc1766Info( 
            /* [in] */ LCID Locale,
            /* [out] */ PRFC1766INFO pRfc1766Info) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateConvertCharset( 
            /* [in] */ UINT uiSrcCodePage,
            /* [in] */ UINT uiDstCodePage,
            /* [in] */ DWORD dwProperty,
            /* [out] */ IMLangConvertCharset __RPC_FAR *__RPC_FAR *ppMLangConvertCharset) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMultiLanguageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMultiLanguage __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMultiLanguage __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMultiLanguage __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNumberOfCodePageInfo )( 
            IMultiLanguage __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pcCodePage);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCodePageInfo )( 
            IMultiLanguage __RPC_FAR * This,
            /* [in] */ UINT uiCodePage,
            /* [out] */ PMIMECPINFO pCodePageInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFamilyCodePage )( 
            IMultiLanguage __RPC_FAR * This,
            /* [in] */ UINT uiCodePage,
            /* [out] */ UINT __RPC_FAR *puiFamilyCodePage);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumCodePages )( 
            IMultiLanguage __RPC_FAR * This,
            /* [in] */ DWORD grfFlags,
            /* [out] */ IEnumCodePage __RPC_FAR *__RPC_FAR *ppEnumCodePage);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCharsetInfo )( 
            IMultiLanguage __RPC_FAR * This,
            /* [in] */ BSTR Charset,
            /* [out] */ PMIMECSETINFO pCharsetInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsConvertible )( 
            IMultiLanguage __RPC_FAR * This,
            /* [in] */ DWORD dwSrcEncoding,
            /* [in] */ DWORD dwDstEncoding);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConvertString )( 
            IMultiLanguage __RPC_FAR * This,
            /* [out][in] */ DWORD __RPC_FAR *pdwMode,
            /* [in] */ DWORD dwSrcEncoding,
            /* [in] */ DWORD dwDstEncoding,
            /* [in] */ BYTE __RPC_FAR *pSrcStr,
            /* [out][in] */ UINT __RPC_FAR *pcSrcSize,
            /* [in] */ BYTE __RPC_FAR *pDstStr,
            /* [out][in] */ UINT __RPC_FAR *pcDstSize);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConvertStringToUnicode )( 
            IMultiLanguage __RPC_FAR * This,
            /* [out][in] */ DWORD __RPC_FAR *pdwMode,
            /* [in] */ DWORD dwEncoding,
            /* [in] */ CHAR __RPC_FAR *pSrcStr,
            /* [out][in] */ UINT __RPC_FAR *pcSrcSize,
            /* [in] */ WCHAR __RPC_FAR *pDstStr,
            /* [out][in] */ UINT __RPC_FAR *pcDstSize);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConvertStringFromUnicode )( 
            IMultiLanguage __RPC_FAR * This,
            /* [out][in] */ DWORD __RPC_FAR *pdwMode,
            /* [in] */ DWORD dwEncoding,
            /* [in] */ WCHAR __RPC_FAR *pSrcStr,
            /* [out][in] */ UINT __RPC_FAR *pcSrcSize,
            /* [in] */ CHAR __RPC_FAR *pDstStr,
            /* [out][in] */ UINT __RPC_FAR *pcDstSize);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConvertStringReset )( 
            IMultiLanguage __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRfc1766FromLcid )( 
            IMultiLanguage __RPC_FAR * This,
            /* [in] */ LCID Locale,
            /* [out] */ BSTR __RPC_FAR *pbstrRfc1766);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLcidFromRfc1766 )( 
            IMultiLanguage __RPC_FAR * This,
            /* [out] */ LCID __RPC_FAR *pLocale,
            /* [in] */ BSTR bstrRfc1766);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumRfc1766 )( 
            IMultiLanguage __RPC_FAR * This,
            /* [out] */ IEnumRfc1766 __RPC_FAR *__RPC_FAR *ppEnumRfc1766);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRfc1766Info )( 
            IMultiLanguage __RPC_FAR * This,
            /* [in] */ LCID Locale,
            /* [out] */ PRFC1766INFO pRfc1766Info);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateConvertCharset )( 
            IMultiLanguage __RPC_FAR * This,
            /* [in] */ UINT uiSrcCodePage,
            /* [in] */ UINT uiDstCodePage,
            /* [in] */ DWORD dwProperty,
            /* [out] */ IMLangConvertCharset __RPC_FAR *__RPC_FAR *ppMLangConvertCharset);
        
        END_INTERFACE
    } IMultiLanguageVtbl;

    interface IMultiLanguage
    {
        CONST_VTBL struct IMultiLanguageVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMultiLanguage_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMultiLanguage_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMultiLanguage_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMultiLanguage_GetNumberOfCodePageInfo(This,pcCodePage)	\
    (This)->lpVtbl -> GetNumberOfCodePageInfo(This,pcCodePage)

#define IMultiLanguage_GetCodePageInfo(This,uiCodePage,pCodePageInfo)	\
    (This)->lpVtbl -> GetCodePageInfo(This,uiCodePage,pCodePageInfo)

#define IMultiLanguage_GetFamilyCodePage(This,uiCodePage,puiFamilyCodePage)	\
    (This)->lpVtbl -> GetFamilyCodePage(This,uiCodePage,puiFamilyCodePage)

#define IMultiLanguage_EnumCodePages(This,grfFlags,ppEnumCodePage)	\
    (This)->lpVtbl -> EnumCodePages(This,grfFlags,ppEnumCodePage)

#define IMultiLanguage_GetCharsetInfo(This,Charset,pCharsetInfo)	\
    (This)->lpVtbl -> GetCharsetInfo(This,Charset,pCharsetInfo)

#define IMultiLanguage_IsConvertible(This,dwSrcEncoding,dwDstEncoding)	\
    (This)->lpVtbl -> IsConvertible(This,dwSrcEncoding,dwDstEncoding)

#define IMultiLanguage_ConvertString(This,pdwMode,dwSrcEncoding,dwDstEncoding,pSrcStr,pcSrcSize,pDstStr,pcDstSize)	\
    (This)->lpVtbl -> ConvertString(This,pdwMode,dwSrcEncoding,dwDstEncoding,pSrcStr,pcSrcSize,pDstStr,pcDstSize)

#define IMultiLanguage_ConvertStringToUnicode(This,pdwMode,dwEncoding,pSrcStr,pcSrcSize,pDstStr,pcDstSize)	\
    (This)->lpVtbl -> ConvertStringToUnicode(This,pdwMode,dwEncoding,pSrcStr,pcSrcSize,pDstStr,pcDstSize)

#define IMultiLanguage_ConvertStringFromUnicode(This,pdwMode,dwEncoding,pSrcStr,pcSrcSize,pDstStr,pcDstSize)	\
    (This)->lpVtbl -> ConvertStringFromUnicode(This,pdwMode,dwEncoding,pSrcStr,pcSrcSize,pDstStr,pcDstSize)

#define IMultiLanguage_ConvertStringReset(This)	\
    (This)->lpVtbl -> ConvertStringReset(This)

#define IMultiLanguage_GetRfc1766FromLcid(This,Locale,pbstrRfc1766)	\
    (This)->lpVtbl -> GetRfc1766FromLcid(This,Locale,pbstrRfc1766)

#define IMultiLanguage_GetLcidFromRfc1766(This,pLocale,bstrRfc1766)	\
    (This)->lpVtbl -> GetLcidFromRfc1766(This,pLocale,bstrRfc1766)

#define IMultiLanguage_EnumRfc1766(This,ppEnumRfc1766)	\
    (This)->lpVtbl -> EnumRfc1766(This,ppEnumRfc1766)

#define IMultiLanguage_GetRfc1766Info(This,Locale,pRfc1766Info)	\
    (This)->lpVtbl -> GetRfc1766Info(This,Locale,pRfc1766Info)

#define IMultiLanguage_CreateConvertCharset(This,uiSrcCodePage,uiDstCodePage,dwProperty,ppMLangConvertCharset)	\
    (This)->lpVtbl -> CreateConvertCharset(This,uiSrcCodePage,uiDstCodePage,dwProperty,ppMLangConvertCharset)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMultiLanguage_GetNumberOfCodePageInfo_Proxy( 
    IMultiLanguage __RPC_FAR * This,
    /* [out] */ UINT __RPC_FAR *pcCodePage);


void __RPC_STUB IMultiLanguage_GetNumberOfCodePageInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMultiLanguage_GetCodePageInfo_Proxy( 
    IMultiLanguage __RPC_FAR * This,
    /* [in] */ UINT uiCodePage,
    /* [out] */ PMIMECPINFO pCodePageInfo);


void __RPC_STUB IMultiLanguage_GetCodePageInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMultiLanguage_GetFamilyCodePage_Proxy( 
    IMultiLanguage __RPC_FAR * This,
    /* [in] */ UINT uiCodePage,
    /* [out] */ UINT __RPC_FAR *puiFamilyCodePage);


void __RPC_STUB IMultiLanguage_GetFamilyCodePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMultiLanguage_EnumCodePages_Proxy( 
    IMultiLanguage __RPC_FAR * This,
    /* [in] */ DWORD grfFlags,
    /* [out] */ IEnumCodePage __RPC_FAR *__RPC_FAR *ppEnumCodePage);


void __RPC_STUB IMultiLanguage_EnumCodePages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMultiLanguage_GetCharsetInfo_Proxy( 
    IMultiLanguage __RPC_FAR * This,
    /* [in] */ BSTR Charset,
    /* [out] */ PMIMECSETINFO pCharsetInfo);


void __RPC_STUB IMultiLanguage_GetCharsetInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMultiLanguage_IsConvertible_Proxy( 
    IMultiLanguage __RPC_FAR * This,
    /* [in] */ DWORD dwSrcEncoding,
    /* [in] */ DWORD dwDstEncoding);


void __RPC_STUB IMultiLanguage_IsConvertible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMultiLanguage_ConvertString_Proxy( 
    IMultiLanguage __RPC_FAR * This,
    /* [out][in] */ DWORD __RPC_FAR *pdwMode,
    /* [in] */ DWORD dwSrcEncoding,
    /* [in] */ DWORD dwDstEncoding,
    /* [in] */ BYTE __RPC_FAR *pSrcStr,
    /* [out][in] */ UINT __RPC_FAR *pcSrcSize,
    /* [in] */ BYTE __RPC_FAR *pDstStr,
    /* [out][in] */ UINT __RPC_FAR *pcDstSize);


void __RPC_STUB IMultiLanguage_ConvertString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMultiLanguage_ConvertStringToUnicode_Proxy( 
    IMultiLanguage __RPC_FAR * This,
    /* [out][in] */ DWORD __RPC_FAR *pdwMode,
    /* [in] */ DWORD dwEncoding,
    /* [in] */ CHAR __RPC_FAR *pSrcStr,
    /* [out][in] */ UINT __RPC_FAR *pcSrcSize,
    /* [in] */ WCHAR __RPC_FAR *pDstStr,
    /* [out][in] */ UINT __RPC_FAR *pcDstSize);


void __RPC_STUB IMultiLanguage_ConvertStringToUnicode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMultiLanguage_ConvertStringFromUnicode_Proxy( 
    IMultiLanguage __RPC_FAR * This,
    /* [out][in] */ DWORD __RPC_FAR *pdwMode,
    /* [in] */ DWORD dwEncoding,
    /* [in] */ WCHAR __RPC_FAR *pSrcStr,
    /* [out][in] */ UINT __RPC_FAR *pcSrcSize,
    /* [in] */ CHAR __RPC_FAR *pDstStr,
    /* [out][in] */ UINT __RPC_FAR *pcDstSize);


void __RPC_STUB IMultiLanguage_ConvertStringFromUnicode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMultiLanguage_ConvertStringReset_Proxy( 
    IMultiLanguage __RPC_FAR * This);


void __RPC_STUB IMultiLanguage_ConvertStringReset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMultiLanguage_GetRfc1766FromLcid_Proxy( 
    IMultiLanguage __RPC_FAR * This,
    /* [in] */ LCID Locale,
    /* [out] */ BSTR __RPC_FAR *pbstrRfc1766);


void __RPC_STUB IMultiLanguage_GetRfc1766FromLcid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMultiLanguage_GetLcidFromRfc1766_Proxy( 
    IMultiLanguage __RPC_FAR * This,
    /* [out] */ LCID __RPC_FAR *pLocale,
    /* [in] */ BSTR bstrRfc1766);


void __RPC_STUB IMultiLanguage_GetLcidFromRfc1766_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMultiLanguage_EnumRfc1766_Proxy( 
    IMultiLanguage __RPC_FAR * This,
    /* [out] */ IEnumRfc1766 __RPC_FAR *__RPC_FAR *ppEnumRfc1766);


void __RPC_STUB IMultiLanguage_EnumRfc1766_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMultiLanguage_GetRfc1766Info_Proxy( 
    IMultiLanguage __RPC_FAR * This,
    /* [in] */ LCID Locale,
    /* [out] */ PRFC1766INFO pRfc1766Info);


void __RPC_STUB IMultiLanguage_GetRfc1766Info_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMultiLanguage_CreateConvertCharset_Proxy( 
    IMultiLanguage __RPC_FAR * This,
    /* [in] */ UINT uiSrcCodePage,
    /* [in] */ UINT uiDstCodePage,
    /* [in] */ DWORD dwProperty,
    /* [out] */ IMLangConvertCharset __RPC_FAR *__RPC_FAR *ppMLangConvertCharset);


void __RPC_STUB IMultiLanguage_CreateConvertCharset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMultiLanguage_INTERFACE_DEFINED__ */


#ifndef __IMLangCodePages_INTERFACE_DEFINED__
#define __IMLangCodePages_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMLangCodePages
 * at Thu Sep 11 10:59:43 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][unique][helpstring][uuid] */ 


typedef /* [unique] */ IMLangCodePages __RPC_FAR *PMLANGCODEPAGES;


EXTERN_C const IID IID_IMLangCodePages;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("359F3443-BD4A-11D0-B188-00AA0038C969")
    IMLangCodePages : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCharCodePages( 
            /* [in] */ WCHAR chSrc,
            /* [out] */ DWORD __RPC_FAR *pdwCodePages) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetStrCodePages( 
            /* [size_is][in] */ const WCHAR __RPC_FAR *pszSrc,
            /* [in] */ long cchSrc,
            /* [in] */ DWORD dwPriorityCodePages,
            /* [out] */ DWORD __RPC_FAR *pdwCodePages,
            /* [out] */ long __RPC_FAR *pcchCodePages) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CodePageToCodePages( 
            /* [in] */ UINT uCodePage,
            /* [out] */ DWORD __RPC_FAR *pdwCodePages) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CodePagesToCodePage( 
            /* [in] */ DWORD dwCodePages,
            /* [in] */ UINT uDefaultCodePage,
            /* [out] */ UINT __RPC_FAR *puCodePage) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMLangCodePagesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMLangCodePages __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMLangCodePages __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMLangCodePages __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCharCodePages )( 
            IMLangCodePages __RPC_FAR * This,
            /* [in] */ WCHAR chSrc,
            /* [out] */ DWORD __RPC_FAR *pdwCodePages);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStrCodePages )( 
            IMLangCodePages __RPC_FAR * This,
            /* [size_is][in] */ const WCHAR __RPC_FAR *pszSrc,
            /* [in] */ long cchSrc,
            /* [in] */ DWORD dwPriorityCodePages,
            /* [out] */ DWORD __RPC_FAR *pdwCodePages,
            /* [out] */ long __RPC_FAR *pcchCodePages);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CodePageToCodePages )( 
            IMLangCodePages __RPC_FAR * This,
            /* [in] */ UINT uCodePage,
            /* [out] */ DWORD __RPC_FAR *pdwCodePages);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CodePagesToCodePage )( 
            IMLangCodePages __RPC_FAR * This,
            /* [in] */ DWORD dwCodePages,
            /* [in] */ UINT uDefaultCodePage,
            /* [out] */ UINT __RPC_FAR *puCodePage);
        
        END_INTERFACE
    } IMLangCodePagesVtbl;

    interface IMLangCodePages
    {
        CONST_VTBL struct IMLangCodePagesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMLangCodePages_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMLangCodePages_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMLangCodePages_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMLangCodePages_GetCharCodePages(This,chSrc,pdwCodePages)	\
    (This)->lpVtbl -> GetCharCodePages(This,chSrc,pdwCodePages)

#define IMLangCodePages_GetStrCodePages(This,pszSrc,cchSrc,dwPriorityCodePages,pdwCodePages,pcchCodePages)	\
    (This)->lpVtbl -> GetStrCodePages(This,pszSrc,cchSrc,dwPriorityCodePages,pdwCodePages,pcchCodePages)

#define IMLangCodePages_CodePageToCodePages(This,uCodePage,pdwCodePages)	\
    (This)->lpVtbl -> CodePageToCodePages(This,uCodePage,pdwCodePages)

#define IMLangCodePages_CodePagesToCodePage(This,dwCodePages,uDefaultCodePage,puCodePage)	\
    (This)->lpVtbl -> CodePagesToCodePage(This,dwCodePages,uDefaultCodePage,puCodePage)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangCodePages_GetCharCodePages_Proxy( 
    IMLangCodePages __RPC_FAR * This,
    /* [in] */ WCHAR chSrc,
    /* [out] */ DWORD __RPC_FAR *pdwCodePages);


void __RPC_STUB IMLangCodePages_GetCharCodePages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangCodePages_GetStrCodePages_Proxy( 
    IMLangCodePages __RPC_FAR * This,
    /* [size_is][in] */ const WCHAR __RPC_FAR *pszSrc,
    /* [in] */ long cchSrc,
    /* [in] */ DWORD dwPriorityCodePages,
    /* [out] */ DWORD __RPC_FAR *pdwCodePages,
    /* [out] */ long __RPC_FAR *pcchCodePages);


void __RPC_STUB IMLangCodePages_GetStrCodePages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangCodePages_CodePageToCodePages_Proxy( 
    IMLangCodePages __RPC_FAR * This,
    /* [in] */ UINT uCodePage,
    /* [out] */ DWORD __RPC_FAR *pdwCodePages);


void __RPC_STUB IMLangCodePages_CodePageToCodePages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangCodePages_CodePagesToCodePage_Proxy( 
    IMLangCodePages __RPC_FAR * This,
    /* [in] */ DWORD dwCodePages,
    /* [in] */ UINT uDefaultCodePage,
    /* [out] */ UINT __RPC_FAR *puCodePage);


void __RPC_STUB IMLangCodePages_CodePagesToCodePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMLangCodePages_INTERFACE_DEFINED__ */


#ifndef __IMLangFontLink_INTERFACE_DEFINED__
#define __IMLangFontLink_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMLangFontLink
 * at Thu Sep 11 10:59:43 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][unique][helpstring][uuid] */ 


typedef /* [unique] */ IMLangFontLink __RPC_FAR *PMLANGFONTLINK;


EXTERN_C const IID IID_IMLangFontLink;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("359F3441-BD4A-11D0-B188-00AA0038C969")
    IMLangFontLink : public IMLangCodePages
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetFontCodePages( 
            /* [in] */ HDC hDC,
            /* [in] */ HFONT hFont,
            /* [out] */ DWORD __RPC_FAR *pdwCodePages) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE MapFont( 
            /* [in] */ HDC hDC,
            /* [in] */ DWORD dwCodePages,
            /* [in] */ HFONT hSrcFont,
            /* [out] */ HFONT __RPC_FAR *phDestFont) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReleaseFont( 
            /* [in] */ HFONT hFont) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ResetFontMapping( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMLangFontLinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMLangFontLink __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMLangFontLink __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMLangFontLink __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCharCodePages )( 
            IMLangFontLink __RPC_FAR * This,
            /* [in] */ WCHAR chSrc,
            /* [out] */ DWORD __RPC_FAR *pdwCodePages);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStrCodePages )( 
            IMLangFontLink __RPC_FAR * This,
            /* [size_is][in] */ const WCHAR __RPC_FAR *pszSrc,
            /* [in] */ long cchSrc,
            /* [in] */ DWORD dwPriorityCodePages,
            /* [out] */ DWORD __RPC_FAR *pdwCodePages,
            /* [out] */ long __RPC_FAR *pcchCodePages);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CodePageToCodePages )( 
            IMLangFontLink __RPC_FAR * This,
            /* [in] */ UINT uCodePage,
            /* [out] */ DWORD __RPC_FAR *pdwCodePages);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CodePagesToCodePage )( 
            IMLangFontLink __RPC_FAR * This,
            /* [in] */ DWORD dwCodePages,
            /* [in] */ UINT uDefaultCodePage,
            /* [out] */ UINT __RPC_FAR *puCodePage);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFontCodePages )( 
            IMLangFontLink __RPC_FAR * This,
            /* [in] */ HDC hDC,
            /* [in] */ HFONT hFont,
            /* [out] */ DWORD __RPC_FAR *pdwCodePages);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MapFont )( 
            IMLangFontLink __RPC_FAR * This,
            /* [in] */ HDC hDC,
            /* [in] */ DWORD dwCodePages,
            /* [in] */ HFONT hSrcFont,
            /* [out] */ HFONT __RPC_FAR *phDestFont);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReleaseFont )( 
            IMLangFontLink __RPC_FAR * This,
            /* [in] */ HFONT hFont);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetFontMapping )( 
            IMLangFontLink __RPC_FAR * This);
        
        END_INTERFACE
    } IMLangFontLinkVtbl;

    interface IMLangFontLink
    {
        CONST_VTBL struct IMLangFontLinkVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMLangFontLink_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMLangFontLink_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMLangFontLink_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMLangFontLink_GetCharCodePages(This,chSrc,pdwCodePages)	\
    (This)->lpVtbl -> GetCharCodePages(This,chSrc,pdwCodePages)

#define IMLangFontLink_GetStrCodePages(This,pszSrc,cchSrc,dwPriorityCodePages,pdwCodePages,pcchCodePages)	\
    (This)->lpVtbl -> GetStrCodePages(This,pszSrc,cchSrc,dwPriorityCodePages,pdwCodePages,pcchCodePages)

#define IMLangFontLink_CodePageToCodePages(This,uCodePage,pdwCodePages)	\
    (This)->lpVtbl -> CodePageToCodePages(This,uCodePage,pdwCodePages)

#define IMLangFontLink_CodePagesToCodePage(This,dwCodePages,uDefaultCodePage,puCodePage)	\
    (This)->lpVtbl -> CodePagesToCodePage(This,dwCodePages,uDefaultCodePage,puCodePage)


#define IMLangFontLink_GetFontCodePages(This,hDC,hFont,pdwCodePages)	\
    (This)->lpVtbl -> GetFontCodePages(This,hDC,hFont,pdwCodePages)

#define IMLangFontLink_MapFont(This,hDC,dwCodePages,hSrcFont,phDestFont)	\
    (This)->lpVtbl -> MapFont(This,hDC,dwCodePages,hSrcFont,phDestFont)

#define IMLangFontLink_ReleaseFont(This,hFont)	\
    (This)->lpVtbl -> ReleaseFont(This,hFont)

#define IMLangFontLink_ResetFontMapping(This)	\
    (This)->lpVtbl -> ResetFontMapping(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangFontLink_GetFontCodePages_Proxy( 
    IMLangFontLink __RPC_FAR * This,
    /* [in] */ HDC hDC,
    /* [in] */ HFONT hFont,
    /* [out] */ DWORD __RPC_FAR *pdwCodePages);


void __RPC_STUB IMLangFontLink_GetFontCodePages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangFontLink_MapFont_Proxy( 
    IMLangFontLink __RPC_FAR * This,
    /* [in] */ HDC hDC,
    /* [in] */ DWORD dwCodePages,
    /* [in] */ HFONT hSrcFont,
    /* [out] */ HFONT __RPC_FAR *phDestFont);


void __RPC_STUB IMLangFontLink_MapFont_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangFontLink_ReleaseFont_Proxy( 
    IMLangFontLink __RPC_FAR * This,
    /* [in] */ HFONT hFont);


void __RPC_STUB IMLangFontLink_ReleaseFont_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMLangFontLink_ResetFontMapping_Proxy( 
    IMLangFontLink __RPC_FAR * This);


void __RPC_STUB IMLangFontLink_ResetFontMapping_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMLangFontLink_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CMultiLanguage;

#ifdef __cplusplus

class DECLSPEC_UUID("275c23e2-3747-11d0-9fea-00aa003f8646")
CMultiLanguage;
#endif
#endif /* __MultiLanguage_LIBRARY_DEFINED__ */

/****************************************
 * Generated header for interface: __MIDL_itf_mlang_0106
 * at Thu Sep 11 10:59:43 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [local] */ 


#ifndef _MLANG_H_API_DEF_                                                     
#define _MLANG_H_API_DEF_                                                     
                                                                              
// APIs prototypes                                                            
STDAPI LcidToRfc1766A(LCID Locale, LPSTR pszRfc1766, int iMaxLength);         
STDAPI LcidToRfc1766W(LCID Locale, LPWSTR pszRfc1766, int nChar);             
#ifdef UNICODE                                                                
#define LcidToRfc1766        LcidToRfc1766W                                   
#else                                                                         
#define LcidToRfc1766        LcidToRfc1766A                                   
#endif                                                                        
STDAPI Rfc1766ToLcidA(LCID *pLocale, LPCSTR pszRfc1766);                      
STDAPI Rfc1766ToLcidW(LCID *pLocale, LPCWSTR pszRfc1766);                     
#ifdef UNICODE                                                                
#define Rfc1766ToLcid        Rfc1766ToLcidW                                   
#else                                                                         
#define Rfc1766ToLcid        Rfc1766ToLcidA                                   
#endif                                                                        
                                                                              
STDAPI IsConvertINetStringAvailable(DWORD dwSrcEncoding, DWORD dwDstEncoding);
STDAPI ConvertINetString(LPDWORD lpdwMode, DWORD dwSrcEncoding, DWORD dwDstEncoding, LPCSTR lpSrcStr, LPINT lpnSrcSize, LPSTR lpDstStr, LPINT lpnDstSize);   
STDAPI ConvertINetMultiByteToUnicode(LPDWORD lpdwMode, DWORD dwEncoding, LPCSTR lpSrcStr, LPINT lpnMultiCharCount, LPWSTR lpDstStr, LPINT lpnWideCharCount); 
STDAPI ConvertINetUnicodeToMultiByte(LPDWORD lpdwMode, DWORD dwEncoding, LPCWSTR lpSrcStr, LPINT lpnWideCharCount, LPSTR lpDstStr, LPINT lpnMultiCharCount); 
                                                                              
#endif // _MLANG_H_API_DEF_                                                   


extern RPC_IF_HANDLE __MIDL_itf_mlang_0106_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_mlang_0106_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
