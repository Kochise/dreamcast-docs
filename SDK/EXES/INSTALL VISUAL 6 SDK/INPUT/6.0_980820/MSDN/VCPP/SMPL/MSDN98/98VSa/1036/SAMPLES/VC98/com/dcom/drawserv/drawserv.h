/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Wed Feb 11 11:54:06 1998
 */
/* Compiler settings for DrawServ.idl:
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

#ifndef __DrawServ_h__
#define __DrawServ_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IDrawServ_FWD_DEFINED__
#define __IDrawServ_FWD_DEFINED__
typedef interface IDrawServ IDrawServ;
#endif 	/* __IDrawServ_FWD_DEFINED__ */


#ifndef __CDrawServ_FWD_DEFINED__
#define __CDrawServ_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDrawServ CDrawServ;
#else
typedef struct CDrawServ CDrawServ;
#endif /* __cplusplus */

#endif 	/* __CDrawServ_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IDrawServ_INTERFACE_DEFINED__
#define __IDrawServ_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDrawServ
 * at Wed Feb 11 11:54:06 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IDrawServ;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("330E9E75-DF48-11CF-8E2C-00A0C90DC94B")
    IDrawServ : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Draw( 
            /* [in] */ long x1,
            /* [in] */ long y1,
            /* [in] */ long x2,
            /* [in] */ long y2,
            /* [in] */ unsigned long col) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDrawServVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDrawServ __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDrawServ __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDrawServ __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IDrawServ __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IDrawServ __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IDrawServ __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IDrawServ __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Draw )( 
            IDrawServ __RPC_FAR * This,
            /* [in] */ long x1,
            /* [in] */ long y1,
            /* [in] */ long x2,
            /* [in] */ long y2,
            /* [in] */ unsigned long col);
        
        END_INTERFACE
    } IDrawServVtbl;

    interface IDrawServ
    {
        CONST_VTBL struct IDrawServVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDrawServ_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDrawServ_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDrawServ_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDrawServ_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDrawServ_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDrawServ_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDrawServ_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDrawServ_Draw(This,x1,y1,x2,y2,col)	\
    (This)->lpVtbl -> Draw(This,x1,y1,x2,y2,col)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDrawServ_Draw_Proxy( 
    IDrawServ __RPC_FAR * This,
    /* [in] */ long x1,
    /* [in] */ long y1,
    /* [in] */ long x2,
    /* [in] */ long y2,
    /* [in] */ unsigned long col);


void __RPC_STUB IDrawServ_Draw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDrawServ_INTERFACE_DEFINED__ */



#ifndef __DRAWSERVLib_LIBRARY_DEFINED__
#define __DRAWSERVLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: DRAWSERVLib
 * at Wed Feb 11 11:54:06 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_DRAWSERVLib;

EXTERN_C const CLSID CLSID_CDrawServ;

#ifdef __cplusplus

class DECLSPEC_UUID("330E9E79-DF48-11CF-8E2C-00A0C90DC94B")
CDrawServ;
#endif
#endif /* __DRAWSERVLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
