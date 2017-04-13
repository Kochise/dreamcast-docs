/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Tue Feb 03 15:52:06 1998
 */
/* Compiler settings for D:\Samples\COM\acdual\server\Autoclik.odl:
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

#ifndef __ACDual_h__
#define __ACDual_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IAClick_FWD_DEFINED__
#define __IAClick_FWD_DEFINED__
typedef interface IAClick IAClick;
#endif 	/* __IAClick_FWD_DEFINED__ */


#ifndef __IDualAutoClickPoint_FWD_DEFINED__
#define __IDualAutoClickPoint_FWD_DEFINED__
typedef interface IDualAutoClickPoint IDualAutoClickPoint;
#endif 	/* __IDualAutoClickPoint_FWD_DEFINED__ */


#ifndef __IDualAClick_FWD_DEFINED__
#define __IDualAClick_FWD_DEFINED__
typedef interface IDualAClick IDualAClick;
#endif 	/* __IDualAClick_FWD_DEFINED__ */


#ifndef __Document_FWD_DEFINED__
#define __Document_FWD_DEFINED__

#ifdef __cplusplus
typedef class Document Document;
#else
typedef struct Document Document;
#endif /* __cplusplus */

#endif 	/* __Document_FWD_DEFINED__ */


#ifndef __IAutoClickPoint_FWD_DEFINED__
#define __IAutoClickPoint_FWD_DEFINED__
typedef interface IAutoClickPoint IAutoClickPoint;
#endif 	/* __IAutoClickPoint_FWD_DEFINED__ */


#ifndef __Point_FWD_DEFINED__
#define __Point_FWD_DEFINED__

#ifdef __cplusplus
typedef class Point Point;
#else
typedef struct Point Point;
#endif /* __cplusplus */

#endif 	/* __Point_FWD_DEFINED__ */


void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __ACDual_LIBRARY_DEFINED__
#define __ACDual_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: ACDual
 * at Tue Feb 03 15:52:06 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [version][uuid] */ 




DEFINE_GUID(LIBID_ACDual,0x4B115284,0x32F0,0x11cf,0xAC,0x85,0x44,0x45,0x53,0x54,0x00,0x00);

#ifndef __IAClick_DISPINTERFACE_DEFINED__
#define __IAClick_DISPINTERFACE_DEFINED__

/****************************************
 * Generated header for dispinterface: IAClick
 * at Tue Feb 03 15:52:06 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [uuid] */ 



DEFINE_GUID(DIID_IAClick,0x4B115280,0x32F0,0x11cf,0xAC,0x85,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("4B115280-32F0-11cf-AC85-444553540000")
    IAClick : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IAClickVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAClick __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAClick __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAClick __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAClick __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAClick __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAClick __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAClick __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IAClickVtbl;

    interface IAClick
    {
        CONST_VTBL struct IAClickVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAClick_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAClick_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAClick_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAClick_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAClick_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAClick_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAClick_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IAClick_DISPINTERFACE_DEFINED__ */


#ifndef __IDualAutoClickPoint_INTERFACE_DEFINED__
#define __IDualAutoClickPoint_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDualAutoClickPoint
 * at Tue Feb 03 15:52:06 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [object][dual][oleautomation][uuid] */ 



DEFINE_GUID(IID_IDualAutoClickPoint,0x0BDD0E80,0x0DD7,0x11cf,0xBB,0xA8,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0BDD0E80-0DD7-11cf-BBA8-444553540000")
    IDualAutoClickPoint : public IDispatch
    {
    public:
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_x( 
            /* [in] */ short newX) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_x( 
            /* [retval][out] */ short __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_y( 
            /* [in] */ short newY) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_y( 
            /* [retval][out] */ short __RPC_FAR *retval) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDualAutoClickPointVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDualAutoClickPoint __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDualAutoClickPoint __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDualAutoClickPoint __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IDualAutoClickPoint __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IDualAutoClickPoint __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IDualAutoClickPoint __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IDualAutoClickPoint __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_x )( 
            IDualAutoClickPoint __RPC_FAR * This,
            /* [in] */ short newX);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_x )( 
            IDualAutoClickPoint __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_y )( 
            IDualAutoClickPoint __RPC_FAR * This,
            /* [in] */ short newY);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_y )( 
            IDualAutoClickPoint __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *retval);
        
        END_INTERFACE
    } IDualAutoClickPointVtbl;

    interface IDualAutoClickPoint
    {
        CONST_VTBL struct IDualAutoClickPointVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDualAutoClickPoint_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDualAutoClickPoint_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDualAutoClickPoint_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDualAutoClickPoint_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDualAutoClickPoint_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDualAutoClickPoint_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDualAutoClickPoint_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDualAutoClickPoint_put_x(This,newX)	\
    (This)->lpVtbl -> put_x(This,newX)

#define IDualAutoClickPoint_get_x(This,retval)	\
    (This)->lpVtbl -> get_x(This,retval)

#define IDualAutoClickPoint_put_y(This,newY)	\
    (This)->lpVtbl -> put_y(This,newY)

#define IDualAutoClickPoint_get_y(This,retval)	\
    (This)->lpVtbl -> get_y(This,retval)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propput] */ HRESULT STDMETHODCALLTYPE IDualAutoClickPoint_put_x_Proxy( 
    IDualAutoClickPoint __RPC_FAR * This,
    /* [in] */ short newX);


void __RPC_STUB IDualAutoClickPoint_put_x_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IDualAutoClickPoint_get_x_Proxy( 
    IDualAutoClickPoint __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *retval);


void __RPC_STUB IDualAutoClickPoint_get_x_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IDualAutoClickPoint_put_y_Proxy( 
    IDualAutoClickPoint __RPC_FAR * This,
    /* [in] */ short newY);


void __RPC_STUB IDualAutoClickPoint_put_y_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IDualAutoClickPoint_get_y_Proxy( 
    IDualAutoClickPoint __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *retval);


void __RPC_STUB IDualAutoClickPoint_get_y_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDualAutoClickPoint_INTERFACE_DEFINED__ */


#ifndef __IDualAClick_INTERFACE_DEFINED__
#define __IDualAClick_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDualAClick
 * at Tue Feb 03 15:52:06 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [object][dual][oleautomation][uuid] */ 



DEFINE_GUID(IID_IDualAClick,0x0BDD0E81,0x0DD7,0x11cf,0xBB,0xA8,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0BDD0E81-0DD7-11cf-BBA8-444553540000")
    IDualAClick : public IDispatch
    {
    public:
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_text( 
            /* [in] */ BSTR newText) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_text( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_x( 
            /* [in] */ short newX) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_x( 
            /* [retval][out] */ short __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_y( 
            /* [in] */ short newY) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_y( 
            /* [retval][out] */ short __RPC_FAR *retval) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Position( 
            /* [in] */ IDualAutoClickPoint __RPC_FAR *newPosition) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Position( 
            /* [retval][out] */ IDualAutoClickPoint __RPC_FAR *__RPC_FAR *retval) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE RefreshWindow( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetAllProps( 
            /* [in] */ short x,
            /* [in] */ short y,
            /* [in] */ BSTR text) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ShowWindow( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE TestError( 
            /* [in] */ short wCode) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDualAClickVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDualAClick __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDualAClick __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDualAClick __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IDualAClick __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IDualAClick __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IDualAClick __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IDualAClick __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_text )( 
            IDualAClick __RPC_FAR * This,
            /* [in] */ BSTR newText);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_text )( 
            IDualAClick __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_x )( 
            IDualAClick __RPC_FAR * This,
            /* [in] */ short newX);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_x )( 
            IDualAClick __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_y )( 
            IDualAClick __RPC_FAR * This,
            /* [in] */ short newY);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_y )( 
            IDualAClick __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *retval);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Position )( 
            IDualAClick __RPC_FAR * This,
            /* [in] */ IDualAutoClickPoint __RPC_FAR *newPosition);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Position )( 
            IDualAClick __RPC_FAR * This,
            /* [retval][out] */ IDualAutoClickPoint __RPC_FAR *__RPC_FAR *retval);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RefreshWindow )( 
            IDualAClick __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAllProps )( 
            IDualAClick __RPC_FAR * This,
            /* [in] */ short x,
            /* [in] */ short y,
            /* [in] */ BSTR text);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowWindow )( 
            IDualAClick __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TestError )( 
            IDualAClick __RPC_FAR * This,
            /* [in] */ short wCode);
        
        END_INTERFACE
    } IDualAClickVtbl;

    interface IDualAClick
    {
        CONST_VTBL struct IDualAClickVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDualAClick_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDualAClick_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDualAClick_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDualAClick_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDualAClick_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDualAClick_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDualAClick_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDualAClick_put_text(This,newText)	\
    (This)->lpVtbl -> put_text(This,newText)

#define IDualAClick_get_text(This,retval)	\
    (This)->lpVtbl -> get_text(This,retval)

#define IDualAClick_put_x(This,newX)	\
    (This)->lpVtbl -> put_x(This,newX)

#define IDualAClick_get_x(This,retval)	\
    (This)->lpVtbl -> get_x(This,retval)

#define IDualAClick_put_y(This,newY)	\
    (This)->lpVtbl -> put_y(This,newY)

#define IDualAClick_get_y(This,retval)	\
    (This)->lpVtbl -> get_y(This,retval)

#define IDualAClick_put_Position(This,newPosition)	\
    (This)->lpVtbl -> put_Position(This,newPosition)

#define IDualAClick_get_Position(This,retval)	\
    (This)->lpVtbl -> get_Position(This,retval)

#define IDualAClick_RefreshWindow(This)	\
    (This)->lpVtbl -> RefreshWindow(This)

#define IDualAClick_SetAllProps(This,x,y,text)	\
    (This)->lpVtbl -> SetAllProps(This,x,y,text)

#define IDualAClick_ShowWindow(This)	\
    (This)->lpVtbl -> ShowWindow(This)

#define IDualAClick_TestError(This,wCode)	\
    (This)->lpVtbl -> TestError(This,wCode)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propput] */ HRESULT STDMETHODCALLTYPE IDualAClick_put_text_Proxy( 
    IDualAClick __RPC_FAR * This,
    /* [in] */ BSTR newText);


void __RPC_STUB IDualAClick_put_text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IDualAClick_get_text_Proxy( 
    IDualAClick __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IDualAClick_get_text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IDualAClick_put_x_Proxy( 
    IDualAClick __RPC_FAR * This,
    /* [in] */ short newX);


void __RPC_STUB IDualAClick_put_x_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IDualAClick_get_x_Proxy( 
    IDualAClick __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *retval);


void __RPC_STUB IDualAClick_get_x_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IDualAClick_put_y_Proxy( 
    IDualAClick __RPC_FAR * This,
    /* [in] */ short newY);


void __RPC_STUB IDualAClick_put_y_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IDualAClick_get_y_Proxy( 
    IDualAClick __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *retval);


void __RPC_STUB IDualAClick_get_y_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IDualAClick_put_Position_Proxy( 
    IDualAClick __RPC_FAR * This,
    /* [in] */ IDualAutoClickPoint __RPC_FAR *newPosition);


void __RPC_STUB IDualAClick_put_Position_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IDualAClick_get_Position_Proxy( 
    IDualAClick __RPC_FAR * This,
    /* [retval][out] */ IDualAutoClickPoint __RPC_FAR *__RPC_FAR *retval);


void __RPC_STUB IDualAClick_get_Position_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IDualAClick_RefreshWindow_Proxy( 
    IDualAClick __RPC_FAR * This);


void __RPC_STUB IDualAClick_RefreshWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IDualAClick_SetAllProps_Proxy( 
    IDualAClick __RPC_FAR * This,
    /* [in] */ short x,
    /* [in] */ short y,
    /* [in] */ BSTR text);


void __RPC_STUB IDualAClick_SetAllProps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IDualAClick_ShowWindow_Proxy( 
    IDualAClick __RPC_FAR * This);


void __RPC_STUB IDualAClick_ShowWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IDualAClick_TestError_Proxy( 
    IDualAClick __RPC_FAR * This,
    /* [in] */ short wCode);


void __RPC_STUB IDualAClick_TestError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDualAClick_INTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_Document,0x4B115281,0x32F0,0x11cf,0xAC,0x85,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("4B115281-32F0-11cf-AC85-444553540000")
Document;
#endif

#ifndef __IAutoClickPoint_DISPINTERFACE_DEFINED__
#define __IAutoClickPoint_DISPINTERFACE_DEFINED__

/****************************************
 * Generated header for dispinterface: IAutoClickPoint
 * at Tue Feb 03 15:52:06 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [uuid] */ 



DEFINE_GUID(DIID_IAutoClickPoint,0x4B115283,0x32F0,0x11cf,0xAC,0x85,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("4B115283-32F0-11cf-AC85-444553540000")
    IAutoClickPoint : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IAutoClickPointVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAutoClickPoint __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAutoClickPoint __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAutoClickPoint __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAutoClickPoint __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAutoClickPoint __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAutoClickPoint __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAutoClickPoint __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IAutoClickPointVtbl;

    interface IAutoClickPoint
    {
        CONST_VTBL struct IAutoClickPointVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAutoClickPoint_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAutoClickPoint_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAutoClickPoint_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAutoClickPoint_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAutoClickPoint_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAutoClickPoint_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAutoClickPoint_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IAutoClickPoint_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_Point,0x4B115285,0x32F0,0x11cf,0xAC,0x85,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("4B115285-32F0-11cf-AC85-444553540000")
Point;
#endif
#endif /* __ACDual_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
