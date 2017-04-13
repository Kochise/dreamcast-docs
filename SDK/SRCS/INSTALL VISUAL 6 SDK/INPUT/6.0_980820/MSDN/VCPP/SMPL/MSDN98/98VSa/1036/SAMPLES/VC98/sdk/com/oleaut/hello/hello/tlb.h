/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 02:37:13 1998
 */
/* Compiler settings for hello.odl:
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

#ifndef __tlb_h__
#define __tlb_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IHello_FWD_DEFINED__
#define __IHello_FWD_DEFINED__
typedef interface IHello IHello;
#endif 	/* __IHello_FWD_DEFINED__ */


#ifndef __Hello_FWD_DEFINED__
#define __Hello_FWD_DEFINED__

#ifdef __cplusplus
typedef class Hello Hello;
#else
typedef struct Hello Hello;
#endif /* __cplusplus */

#endif 	/* __Hello_FWD_DEFINED__ */


void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __Hello_LIBRARY_DEFINED__
#define __Hello_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: Hello
 * at Mon Mar 30 02:37:13 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [version][helpstring][uuid] */ 



DEFINE_GUID(LIBID_Hello,0xF37C8060,0x4AD5,0x101B,0xB8,0x26,0x00,0xDD,0x01,0x10,0x3D,0xE1);

#ifndef __IHello_INTERFACE_DEFINED__
#define __IHello_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IHello
 * at Mon Mar 30 02:37:13 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [object][dual][oleautomation][helpstring][uuid] */ 



DEFINE_GUID(IID_IHello,0xF37C8062,0x4AD5,0x101B,0xB8,0x26,0x00,0xDD,0x01,0x10,0x3D,0xE1);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F37C8062-4AD5-101B-B826-00DD01103DE1")
    IHello : public IDispatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ IHello __RPC_FAR *__RPC_FAR *retval) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_FullName( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IHello __RPC_FAR *__RPC_FAR *retval) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Visible( 
            /* [in] */ VARIANT_BOOL VisibleFlag) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Visible( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Quit( void) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_HelloMessage( 
            /* [in] */ BSTR Message) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_HelloMessage( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SayHello( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IHelloVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IHello __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IHello __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IHello __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IHello __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IHello __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IHello __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IHello __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            IHello __RPC_FAR * This,
            /* [retval][out] */ IHello __RPC_FAR *__RPC_FAR *retval);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FullName )( 
            IHello __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IHello __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IHello __RPC_FAR * This,
            /* [retval][out] */ IHello __RPC_FAR *__RPC_FAR *retval);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Visible )( 
            IHello __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL VisibleFlag);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Visible )( 
            IHello __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Quit )( 
            IHello __RPC_FAR * This);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HelloMessage )( 
            IHello __RPC_FAR * This,
            /* [in] */ BSTR Message);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HelloMessage )( 
            IHello __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SayHello )( 
            IHello __RPC_FAR * This);
        
        END_INTERFACE
    } IHelloVtbl;

    interface IHello
    {
        CONST_VTBL struct IHelloVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHello_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IHello_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IHello_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IHello_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IHello_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IHello_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IHello_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IHello_get_Application(This,retval)	\
    (This)->lpVtbl -> get_Application(This,retval)

#define IHello_get_FullName(This,retval)	\
    (This)->lpVtbl -> get_FullName(This,retval)

#define IHello_get_Name(This,retval)	\
    (This)->lpVtbl -> get_Name(This,retval)

#define IHello_get_Parent(This,retval)	\
    (This)->lpVtbl -> get_Parent(This,retval)

#define IHello_put_Visible(This,VisibleFlag)	\
    (This)->lpVtbl -> put_Visible(This,VisibleFlag)

#define IHello_get_Visible(This,retval)	\
    (This)->lpVtbl -> get_Visible(This,retval)

#define IHello_Quit(This)	\
    (This)->lpVtbl -> Quit(This)

#define IHello_put_HelloMessage(This,Message)	\
    (This)->lpVtbl -> put_HelloMessage(This,Message)

#define IHello_get_HelloMessage(This,retval)	\
    (This)->lpVtbl -> get_HelloMessage(This,retval)

#define IHello_SayHello(This)	\
    (This)->lpVtbl -> SayHello(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IHello_get_Application_Proxy( 
    IHello __RPC_FAR * This,
    /* [retval][out] */ IHello __RPC_FAR *__RPC_FAR *retval);


void __RPC_STUB IHello_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IHello_get_FullName_Proxy( 
    IHello __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IHello_get_FullName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IHello_get_Name_Proxy( 
    IHello __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IHello_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IHello_get_Parent_Proxy( 
    IHello __RPC_FAR * This,
    /* [retval][out] */ IHello __RPC_FAR *__RPC_FAR *retval);


void __RPC_STUB IHello_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IHello_put_Visible_Proxy( 
    IHello __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL VisibleFlag);


void __RPC_STUB IHello_put_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IHello_get_Visible_Proxy( 
    IHello __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval);


void __RPC_STUB IHello_get_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IHello_Quit_Proxy( 
    IHello __RPC_FAR * This);


void __RPC_STUB IHello_Quit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IHello_put_HelloMessage_Proxy( 
    IHello __RPC_FAR * This,
    /* [in] */ BSTR Message);


void __RPC_STUB IHello_put_HelloMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IHello_get_HelloMessage_Proxy( 
    IHello __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IHello_get_HelloMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IHello_SayHello_Proxy( 
    IHello __RPC_FAR * This);


void __RPC_STUB IHello_SayHello_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IHello_INTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_Hello,0xF37C8061,0x4AD5,0x101B,0xB8,0x26,0x00,0xDD,0x01,0x10,0x3D,0xE1);

#ifdef __cplusplus

class DECLSPEC_UUID("F37C8061-4AD5-101B-B826-00DD01103DE1")
Hello;
#endif
#endif /* __Hello_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
