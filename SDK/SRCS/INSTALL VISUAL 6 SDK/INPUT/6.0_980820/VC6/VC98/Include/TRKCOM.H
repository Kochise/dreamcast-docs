/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Thu Sep 11 18:12:06 1997
 */
/* Compiler settings for trkcom.idl:
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

#ifndef __trkcom_h__
#define __trkcom_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ITrackFile_FWD_DEFINED__
#define __ITrackFile_FWD_DEFINED__
typedef interface ITrackFile ITrackFile;
#endif 	/* __ITrackFile_FWD_DEFINED__ */


#ifndef __ITrackStorage_FWD_DEFINED__
#define __ITrackStorage_FWD_DEFINED__
typedef interface ITrackStorage ITrackStorage;
#endif 	/* __ITrackStorage_FWD_DEFINED__ */


#ifndef __ITrackFileRestricted_FWD_DEFINED__
#define __ITrackFileRestricted_FWD_DEFINED__
typedef interface ITrackFileRestricted ITrackFileRestricted;
#endif 	/* __ITrackFileRestricted_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL_itf_trkcom_0000
 * at Thu Sep 11 18:12:06 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [local] */ 


EXTERN_C const CLSID CLSID_TrackFile; // {8790c947-a30b-11d0-8cab-00c04fd90f85}


extern RPC_IF_HANDLE __MIDL_itf_trkcom_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE Stub__MIDL_itf_trkcom_0000_v0_0_s_ifspec;

#ifndef __ITrackFile_INTERFACE_DEFINED__
#define __ITrackFile_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITrackFile
 * at Thu Sep 11 18:12:06 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [version][unique][object][uuid][local] */ 



EXTERN_C const IID IID_ITrackFile;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8790c948-a30b-11d0-8cab-00c04fd90f85")
    ITrackFile : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CreateFromPath( 
            /* [string][in] */ const OLECHAR __RPC_FAR *poszPath) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Resolve( 
            /* [out][in] */ DWORD __RPC_FAR *pcbPath,
            /* [string][size_is][out] */ OLECHAR __RPC_FAR *poszPath,
            /* [in] */ DWORD dwMillisecondTimeout) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Open( 
            /* [out][in] */ DWORD __RPC_FAR *pcbPathHint,
            /* [string][size_is][out][in] */ OLECHAR __RPC_FAR *poszPathHint,
            /* [in] */ DWORD dwMillisecondTimeout,
            /* [in] */ DWORD dwDesiredAccess,
            /* [in] */ DWORD dwShareMode,
            /* [in] */ DWORD dwFlags,
            /* [out] */ HANDLE __RPC_FAR *phFile) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITrackFileVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITrackFile __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITrackFile __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITrackFile __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateFromPath )( 
            ITrackFile __RPC_FAR * This,
            /* [string][in] */ const OLECHAR __RPC_FAR *poszPath);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Resolve )( 
            ITrackFile __RPC_FAR * This,
            /* [out][in] */ DWORD __RPC_FAR *pcbPath,
            /* [string][size_is][out] */ OLECHAR __RPC_FAR *poszPath,
            /* [in] */ DWORD dwMillisecondTimeout);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Open )( 
            ITrackFile __RPC_FAR * This,
            /* [out][in] */ DWORD __RPC_FAR *pcbPathHint,
            /* [string][size_is][out][in] */ OLECHAR __RPC_FAR *poszPathHint,
            /* [in] */ DWORD dwMillisecondTimeout,
            /* [in] */ DWORD dwDesiredAccess,
            /* [in] */ DWORD dwShareMode,
            /* [in] */ DWORD dwFlags,
            /* [out] */ HANDLE __RPC_FAR *phFile);
        
        END_INTERFACE
    } ITrackFileVtbl;

    interface ITrackFile
    {
        CONST_VTBL struct ITrackFileVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITrackFile_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITrackFile_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITrackFile_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITrackFile_CreateFromPath(This,poszPath)	\
    (This)->lpVtbl -> CreateFromPath(This,poszPath)

#define ITrackFile_Resolve(This,pcbPath,poszPath,dwMillisecondTimeout)	\
    (This)->lpVtbl -> Resolve(This,pcbPath,poszPath,dwMillisecondTimeout)

#define ITrackFile_Open(This,pcbPathHint,poszPathHint,dwMillisecondTimeout,dwDesiredAccess,dwShareMode,dwFlags,phFile)	\
    (This)->lpVtbl -> Open(This,pcbPathHint,poszPathHint,dwMillisecondTimeout,dwDesiredAccess,dwShareMode,dwFlags,phFile)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ITrackFile_CreateFromPath_Proxy( 
    ITrackFile __RPC_FAR * This,
    /* [string][in] */ const OLECHAR __RPC_FAR *poszPath);


void __RPC_STUB ITrackFile_CreateFromPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITrackFile_Resolve_Proxy( 
    ITrackFile __RPC_FAR * This,
    /* [out][in] */ DWORD __RPC_FAR *pcbPath,
    /* [string][size_is][out] */ OLECHAR __RPC_FAR *poszPath,
    /* [in] */ DWORD dwMillisecondTimeout);


void __RPC_STUB ITrackFile_Resolve_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITrackFile_Open_Proxy( 
    ITrackFile __RPC_FAR * This,
    /* [out][in] */ DWORD __RPC_FAR *pcbPathHint,
    /* [string][size_is][out][in] */ OLECHAR __RPC_FAR *poszPathHint,
    /* [in] */ DWORD dwMillisecondTimeout,
    /* [in] */ DWORD dwDesiredAccess,
    /* [in] */ DWORD dwShareMode,
    /* [in] */ DWORD dwFlags,
    /* [out] */ HANDLE __RPC_FAR *phFile);


void __RPC_STUB ITrackFile_Open_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITrackFile_INTERFACE_DEFINED__ */


#ifndef __ITrackStorage_INTERFACE_DEFINED__
#define __ITrackStorage_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITrackStorage
 * at Thu Sep 11 18:12:06 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [version][unique][object][uuid] */ 



EXTERN_C const IID IID_ITrackStorage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8790c94a-a30b-11d0-8cab-00c04fd90f85")
    ITrackStorage : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CreateFromPath( 
            /* [string][in] */ const OLECHAR __RPC_FAR *poszPath) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Resolve( 
            /* [out][in] */ DWORD __RPC_FAR *pcbPath,
            /* [string][size_is][out] */ OLECHAR __RPC_FAR *poszPath,
            /* [in] */ DWORD dwMillisecondTimeout) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OpenStorageEx( 
            /* [out][in] */ DWORD __RPC_FAR *pcbPathHint,
            /* [string][size_is][out][in] */ OLECHAR __RPC_FAR *poszPathHint,
            /* [in] */ DWORD dwMillisecondTimeout,
            /* [in] */ DWORD grfMode,
            /* [in] */ DWORD stgfmt,
            /* [in] */ DWORD grfAttrs,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppObjectOpen) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITrackStorageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITrackStorage __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITrackStorage __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITrackStorage __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateFromPath )( 
            ITrackStorage __RPC_FAR * This,
            /* [string][in] */ const OLECHAR __RPC_FAR *poszPath);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Resolve )( 
            ITrackStorage __RPC_FAR * This,
            /* [out][in] */ DWORD __RPC_FAR *pcbPath,
            /* [string][size_is][out] */ OLECHAR __RPC_FAR *poszPath,
            /* [in] */ DWORD dwMillisecondTimeout);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenStorageEx )( 
            ITrackStorage __RPC_FAR * This,
            /* [out][in] */ DWORD __RPC_FAR *pcbPathHint,
            /* [string][size_is][out][in] */ OLECHAR __RPC_FAR *poszPathHint,
            /* [in] */ DWORD dwMillisecondTimeout,
            /* [in] */ DWORD grfMode,
            /* [in] */ DWORD stgfmt,
            /* [in] */ DWORD grfAttrs,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppObjectOpen);
        
        END_INTERFACE
    } ITrackStorageVtbl;

    interface ITrackStorage
    {
        CONST_VTBL struct ITrackStorageVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITrackStorage_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITrackStorage_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITrackStorage_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITrackStorage_CreateFromPath(This,poszPath)	\
    (This)->lpVtbl -> CreateFromPath(This,poszPath)

#define ITrackStorage_Resolve(This,pcbPath,poszPath,dwMillisecondTimeout)	\
    (This)->lpVtbl -> Resolve(This,pcbPath,poszPath,dwMillisecondTimeout)

#define ITrackStorage_OpenStorageEx(This,pcbPathHint,poszPathHint,dwMillisecondTimeout,grfMode,stgfmt,grfAttrs,riid,ppObjectOpen)	\
    (This)->lpVtbl -> OpenStorageEx(This,pcbPathHint,poszPathHint,dwMillisecondTimeout,grfMode,stgfmt,grfAttrs,riid,ppObjectOpen)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ITrackStorage_CreateFromPath_Proxy( 
    ITrackStorage __RPC_FAR * This,
    /* [string][in] */ const OLECHAR __RPC_FAR *poszPath);


void __RPC_STUB ITrackStorage_CreateFromPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITrackStorage_Resolve_Proxy( 
    ITrackStorage __RPC_FAR * This,
    /* [out][in] */ DWORD __RPC_FAR *pcbPath,
    /* [string][size_is][out] */ OLECHAR __RPC_FAR *poszPath,
    /* [in] */ DWORD dwMillisecondTimeout);


void __RPC_STUB ITrackStorage_Resolve_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITrackStorage_OpenStorageEx_Proxy( 
    ITrackStorage __RPC_FAR * This,
    /* [out][in] */ DWORD __RPC_FAR *pcbPathHint,
    /* [string][size_is][out][in] */ OLECHAR __RPC_FAR *poszPathHint,
    /* [in] */ DWORD dwMillisecondTimeout,
    /* [in] */ DWORD grfMode,
    /* [in] */ DWORD stgfmt,
    /* [in] */ DWORD grfAttrs,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppObjectOpen);


void __RPC_STUB ITrackStorage_OpenStorageEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITrackStorage_INTERFACE_DEFINED__ */


#ifndef __ITrackFileRestricted_INTERFACE_DEFINED__
#define __ITrackFileRestricted_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITrackFileRestricted
 * at Thu Sep 11 18:12:06 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [version][unique][object][uuid][local] */ 



// Reserved flags
typedef 
enum _TrkMendRestrictions
    {	TRK_MEND_DEFAULT	= 0,
	TRK_MEND_LAST_ONLY	= 1,
	TRK_MEND_DONT_USE_LOG	= 2,
	TRK_MEND_DONT_USE_DC	= 4,
	TRK_MEND_SEARCH_ALL_VOLUMES	= 8
    }	TrkMendRestrictions;


EXTERN_C const IID IID_ITrackFileRestricted;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8790c949-a30b-11d0-8cab-00c04fd90f85")
    ITrackFileRestricted : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CreateFromPath( 
            /* [string][in] */ const OLECHAR __RPC_FAR *poszPath) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Resolve( 
            /* [out][in] */ DWORD __RPC_FAR *pcbPath,
            /* [string][size_is][out] */ OLECHAR __RPC_FAR *poszPath,
            /* [in] */ DWORD dwMillisecondTimeout,
            /* [in] */ TrkMendRestrictions Restrictions) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Open( 
            /* [out][in] */ DWORD __RPC_FAR *pcbPathHint,
            /* [string][size_is][out][in] */ OLECHAR __RPC_FAR *poszPathHint,
            /* [in] */ DWORD dwMillisecondTimeout,
            /* [in] */ DWORD dwDesiredAccess,
            /* [in] */ DWORD dwShareMode,
            /* [in] */ DWORD dwFlags,
            /* [out] */ HANDLE __RPC_FAR *phFile) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITrackFileRestrictedVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITrackFileRestricted __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITrackFileRestricted __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITrackFileRestricted __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateFromPath )( 
            ITrackFileRestricted __RPC_FAR * This,
            /* [string][in] */ const OLECHAR __RPC_FAR *poszPath);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Resolve )( 
            ITrackFileRestricted __RPC_FAR * This,
            /* [out][in] */ DWORD __RPC_FAR *pcbPath,
            /* [string][size_is][out] */ OLECHAR __RPC_FAR *poszPath,
            /* [in] */ DWORD dwMillisecondTimeout,
            /* [in] */ TrkMendRestrictions Restrictions);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Open )( 
            ITrackFileRestricted __RPC_FAR * This,
            /* [out][in] */ DWORD __RPC_FAR *pcbPathHint,
            /* [string][size_is][out][in] */ OLECHAR __RPC_FAR *poszPathHint,
            /* [in] */ DWORD dwMillisecondTimeout,
            /* [in] */ DWORD dwDesiredAccess,
            /* [in] */ DWORD dwShareMode,
            /* [in] */ DWORD dwFlags,
            /* [out] */ HANDLE __RPC_FAR *phFile);
        
        END_INTERFACE
    } ITrackFileRestrictedVtbl;

    interface ITrackFileRestricted
    {
        CONST_VTBL struct ITrackFileRestrictedVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITrackFileRestricted_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITrackFileRestricted_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITrackFileRestricted_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITrackFileRestricted_CreateFromPath(This,poszPath)	\
    (This)->lpVtbl -> CreateFromPath(This,poszPath)

#define ITrackFileRestricted_Resolve(This,pcbPath,poszPath,dwMillisecondTimeout,Restrictions)	\
    (This)->lpVtbl -> Resolve(This,pcbPath,poszPath,dwMillisecondTimeout,Restrictions)

#define ITrackFileRestricted_Open(This,pcbPathHint,poszPathHint,dwMillisecondTimeout,dwDesiredAccess,dwShareMode,dwFlags,phFile)	\
    (This)->lpVtbl -> Open(This,pcbPathHint,poszPathHint,dwMillisecondTimeout,dwDesiredAccess,dwShareMode,dwFlags,phFile)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ITrackFileRestricted_CreateFromPath_Proxy( 
    ITrackFileRestricted __RPC_FAR * This,
    /* [string][in] */ const OLECHAR __RPC_FAR *poszPath);


void __RPC_STUB ITrackFileRestricted_CreateFromPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITrackFileRestricted_Resolve_Proxy( 
    ITrackFileRestricted __RPC_FAR * This,
    /* [out][in] */ DWORD __RPC_FAR *pcbPath,
    /* [string][size_is][out] */ OLECHAR __RPC_FAR *poszPath,
    /* [in] */ DWORD dwMillisecondTimeout,
    /* [in] */ TrkMendRestrictions Restrictions);


void __RPC_STUB ITrackFileRestricted_Resolve_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITrackFileRestricted_Open_Proxy( 
    ITrackFileRestricted __RPC_FAR * This,
    /* [out][in] */ DWORD __RPC_FAR *pcbPathHint,
    /* [string][size_is][out][in] */ OLECHAR __RPC_FAR *poszPathHint,
    /* [in] */ DWORD dwMillisecondTimeout,
    /* [in] */ DWORD dwDesiredAccess,
    /* [in] */ DWORD dwShareMode,
    /* [in] */ DWORD dwFlags,
    /* [out] */ HANDLE __RPC_FAR *phFile);


void __RPC_STUB ITrackFileRestricted_Open_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITrackFileRestricted_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
