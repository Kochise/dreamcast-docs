/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 02:37:23 1998
 */
/* Compiler settings for lines.odl:
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

#ifndef __IPoint_FWD_DEFINED__
#define __IPoint_FWD_DEFINED__
typedef interface IPoint IPoint;
#endif 	/* __IPoint_FWD_DEFINED__ */


#ifndef __ILine_FWD_DEFINED__
#define __ILine_FWD_DEFINED__
typedef interface ILine ILine;
#endif 	/* __ILine_FWD_DEFINED__ */


#ifndef __ILines_FWD_DEFINED__
#define __ILines_FWD_DEFINED__
typedef interface ILines ILines;
#endif 	/* __ILines_FWD_DEFINED__ */


#ifndef __IPoints_FWD_DEFINED__
#define __IPoints_FWD_DEFINED__
typedef interface IPoints IPoints;
#endif 	/* __IPoints_FWD_DEFINED__ */


#ifndef __IPane_FWD_DEFINED__
#define __IPane_FWD_DEFINED__
typedef interface IPane IPane;
#endif 	/* __IPane_FWD_DEFINED__ */


#ifndef __IApplication_FWD_DEFINED__
#define __IApplication_FWD_DEFINED__
typedef interface IApplication IApplication;
#endif 	/* __IApplication_FWD_DEFINED__ */


#ifndef __Lines_FWD_DEFINED__
#define __Lines_FWD_DEFINED__

#ifdef __cplusplus
typedef class Lines Lines;
#else
typedef struct Lines Lines;
#endif /* __cplusplus */

#endif 	/* __Lines_FWD_DEFINED__ */


void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __Lines_LIBRARY_DEFINED__
#define __Lines_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: Lines
 * at Mon Mar 30 02:37:23 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [version][helpstring][uuid] */ 



DEFINE_GUID(LIBID_Lines,0x3C591B20,0x1F13,0x101B,0xB8,0x26,0x00,0xDD,0x01,0x10,0x3D,0xE1);

#ifndef __IPoint_INTERFACE_DEFINED__
#define __IPoint_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IPoint
 * at Mon Mar 30 02:37:23 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [object][dual][oleautomation][helpstring][uuid] */ 



DEFINE_GUID(IID_IPoint,0x3C591B25,0x1F13,0x101B,0xB8,0x26,0x00,0xDD,0x01,0x10,0x3D,0xE1);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3C591B25-1F13-101B-B826-00DD01103DE1")
    IPoint : public IDispatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_x( 
            /* [retval][out] */ int __RPC_FAR *retval) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_x( 
            /* [in] */ int Value) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_y( 
            /* [retval][out] */ int __RPC_FAR *retval) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_y( 
            /* [in] */ int Value) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPointVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPoint __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPoint __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPoint __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPoint __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPoint __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPoint __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPoint __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_x )( 
            IPoint __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *retval);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_x )( 
            IPoint __RPC_FAR * This,
            /* [in] */ int Value);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_y )( 
            IPoint __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *retval);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_y )( 
            IPoint __RPC_FAR * This,
            /* [in] */ int Value);
        
        END_INTERFACE
    } IPointVtbl;

    interface IPoint
    {
        CONST_VTBL struct IPointVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPoint_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPoint_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPoint_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPoint_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPoint_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPoint_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPoint_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPoint_get_x(This,retval)	\
    (This)->lpVtbl -> get_x(This,retval)

#define IPoint_put_x(This,Value)	\
    (This)->lpVtbl -> put_x(This,Value)

#define IPoint_get_y(This,retval)	\
    (This)->lpVtbl -> get_y(This,retval)

#define IPoint_put_y(This,Value)	\
    (This)->lpVtbl -> put_y(This,Value)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPoint_get_x_Proxy( 
    IPoint __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *retval);


void __RPC_STUB IPoint_get_x_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPoint_put_x_Proxy( 
    IPoint __RPC_FAR * This,
    /* [in] */ int Value);


void __RPC_STUB IPoint_put_x_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPoint_get_y_Proxy( 
    IPoint __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *retval);


void __RPC_STUB IPoint_get_y_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IPoint_put_y_Proxy( 
    IPoint __RPC_FAR * This,
    /* [in] */ int Value);


void __RPC_STUB IPoint_put_y_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPoint_INTERFACE_DEFINED__ */


#ifndef __ILine_INTERFACE_DEFINED__
#define __ILine_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ILine
 * at Mon Mar 30 02:37:23 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [object][dual][oleautomation][helpstring][uuid] */ 



DEFINE_GUID(IID_ILine,0x3C591B24,0x1F13,0x101B,0xB8,0x26,0x00,0xDD,0x01,0x10,0x3D,0xE1);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3C591B24-1F13-101B-B826-00DD01103DE1")
    ILine : public IDispatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Color( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Color( 
            /* [in] */ long rgb) = 0;
        
        virtual /* [id][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndPoint( 
            /* [retval][out] */ IPoint __RPC_FAR *__RPC_FAR *retval) = 0;
        
        virtual /* [id][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_EndPoint( 
            /* [in] */ IPoint __RPC_FAR *Point) = 0;
        
        virtual /* [id][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StartPoint( 
            /* [retval][out] */ IPoint __RPC_FAR *__RPC_FAR *retval) = 0;
        
        virtual /* [id][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_StartPoint( 
            /* [in] */ IPoint __RPC_FAR *Point) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Thickness( 
            /* [retval][out] */ int __RPC_FAR *retval) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Thickness( 
            /* [in] */ int Value) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILineVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ILine __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ILine __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ILine __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ILine __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ILine __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ILine __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ILine __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Color )( 
            ILine __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Color )( 
            ILine __RPC_FAR * This,
            /* [in] */ long rgb);
        
        /* [id][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EndPoint )( 
            ILine __RPC_FAR * This,
            /* [retval][out] */ IPoint __RPC_FAR *__RPC_FAR *retval);
        
        /* [id][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *putref_EndPoint )( 
            ILine __RPC_FAR * This,
            /* [in] */ IPoint __RPC_FAR *Point);
        
        /* [id][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StartPoint )( 
            ILine __RPC_FAR * This,
            /* [retval][out] */ IPoint __RPC_FAR *__RPC_FAR *retval);
        
        /* [id][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *putref_StartPoint )( 
            ILine __RPC_FAR * This,
            /* [in] */ IPoint __RPC_FAR *Point);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Thickness )( 
            ILine __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *retval);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Thickness )( 
            ILine __RPC_FAR * This,
            /* [in] */ int Value);
        
        END_INTERFACE
    } ILineVtbl;

    interface ILine
    {
        CONST_VTBL struct ILineVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILine_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILine_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILine_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILine_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ILine_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ILine_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ILine_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ILine_get_Color(This,retval)	\
    (This)->lpVtbl -> get_Color(This,retval)

#define ILine_put_Color(This,rgb)	\
    (This)->lpVtbl -> put_Color(This,rgb)

#define ILine_get_EndPoint(This,retval)	\
    (This)->lpVtbl -> get_EndPoint(This,retval)

#define ILine_putref_EndPoint(This,Point)	\
    (This)->lpVtbl -> putref_EndPoint(This,Point)

#define ILine_get_StartPoint(This,retval)	\
    (This)->lpVtbl -> get_StartPoint(This,retval)

#define ILine_putref_StartPoint(This,Point)	\
    (This)->lpVtbl -> putref_StartPoint(This,Point)

#define ILine_get_Thickness(This,retval)	\
    (This)->lpVtbl -> get_Thickness(This,retval)

#define ILine_put_Thickness(This,Value)	\
    (This)->lpVtbl -> put_Thickness(This,Value)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ILine_get_Color_Proxy( 
    ILine __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB ILine_get_Color_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE ILine_put_Color_Proxy( 
    ILine __RPC_FAR * This,
    /* [in] */ long rgb);


void __RPC_STUB ILine_put_Color_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][helpstring][propget] */ HRESULT STDMETHODCALLTYPE ILine_get_EndPoint_Proxy( 
    ILine __RPC_FAR * This,
    /* [retval][out] */ IPoint __RPC_FAR *__RPC_FAR *retval);


void __RPC_STUB ILine_get_EndPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE ILine_putref_EndPoint_Proxy( 
    ILine __RPC_FAR * This,
    /* [in] */ IPoint __RPC_FAR *Point);


void __RPC_STUB ILine_putref_EndPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][helpstring][propget] */ HRESULT STDMETHODCALLTYPE ILine_get_StartPoint_Proxy( 
    ILine __RPC_FAR * This,
    /* [retval][out] */ IPoint __RPC_FAR *__RPC_FAR *retval);


void __RPC_STUB ILine_get_StartPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE ILine_putref_StartPoint_Proxy( 
    ILine __RPC_FAR * This,
    /* [in] */ IPoint __RPC_FAR *Point);


void __RPC_STUB ILine_putref_StartPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ILine_get_Thickness_Proxy( 
    ILine __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *retval);


void __RPC_STUB ILine_get_Thickness_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE ILine_put_Thickness_Proxy( 
    ILine __RPC_FAR * This,
    /* [in] */ int Value);


void __RPC_STUB ILine_put_Thickness_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILine_INTERFACE_DEFINED__ */


#ifndef __ILines_INTERFACE_DEFINED__
#define __ILines_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ILines
 * at Mon Mar 30 02:37:23 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [object][dual][oleautomation][helpstring][uuid] */ 



DEFINE_GUID(IID_ILines,0x3C591B26,0x1F13,0x101B,0xB8,0x26,0x00,0xDD,0x01,0x10,0x3D,0xE1);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3C591B26-1F13-101B-B826-00DD01103DE1")
    ILines : public IDispatch
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ILine __RPC_FAR *NewLine) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long Index,
            /* [retval][out] */ ILine __RPC_FAR *__RPC_FAR *retval) = 0;
        
        virtual /* [id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long Index) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILinesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ILines __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ILines __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ILines __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ILines __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ILines __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ILines __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ILines __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            ILines __RPC_FAR * This,
            /* [in] */ ILine __RPC_FAR *NewLine);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ILines __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ILines __RPC_FAR * This,
            /* [in] */ long Index,
            /* [retval][out] */ ILine __RPC_FAR *__RPC_FAR *retval);
        
        /* [id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ILines __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            ILines __RPC_FAR * This,
            /* [in] */ long Index);
        
        END_INTERFACE
    } ILinesVtbl;

    interface ILines
    {
        CONST_VTBL struct ILinesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILines_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILines_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILines_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILines_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ILines_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ILines_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ILines_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ILines_Add(This,NewLine)	\
    (This)->lpVtbl -> Add(This,NewLine)

#define ILines_get_Count(This,retval)	\
    (This)->lpVtbl -> get_Count(This,retval)

#define ILines_get_Item(This,Index,retval)	\
    (This)->lpVtbl -> get_Item(This,Index,retval)

#define ILines_get__NewEnum(This,retval)	\
    (This)->lpVtbl -> get__NewEnum(This,retval)

#define ILines_Remove(This,Index)	\
    (This)->lpVtbl -> Remove(This,Index)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILines_Add_Proxy( 
    ILines __RPC_FAR * This,
    /* [in] */ ILine __RPC_FAR *NewLine);


void __RPC_STUB ILines_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ILines_get_Count_Proxy( 
    ILines __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB ILines_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILines_get_Item_Proxy( 
    ILines __RPC_FAR * This,
    /* [in] */ long Index,
    /* [retval][out] */ ILine __RPC_FAR *__RPC_FAR *retval);


void __RPC_STUB ILines_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][restricted][propget] */ HRESULT STDMETHODCALLTYPE ILines_get__NewEnum_Proxy( 
    ILines __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval);


void __RPC_STUB ILines_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILines_Remove_Proxy( 
    ILines __RPC_FAR * This,
    /* [in] */ long Index);


void __RPC_STUB ILines_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILines_INTERFACE_DEFINED__ */


#ifndef __IPoints_INTERFACE_DEFINED__
#define __IPoints_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IPoints
 * at Mon Mar 30 02:37:23 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [object][dual][oleautomation][helpstring][uuid] */ 



DEFINE_GUID(IID_IPoints,0x3C591B27,0x1F13,0x101B,0xB8,0x26,0x00,0xDD,0x01,0x10,0x3D,0xE1);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3C591B27-1F13-101B-B826-00DD01103DE1")
    IPoints : public IDispatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *retval) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long Index,
            /* [retval][out] */ IPoint __RPC_FAR *__RPC_FAR *retval) = 0;
        
        virtual /* [id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPointsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPoints __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPoints __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPoints __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPoints __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPoints __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPoints __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPoints __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IPoints __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *retval);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            IPoints __RPC_FAR * This,
            /* [in] */ long Index,
            /* [retval][out] */ IPoint __RPC_FAR *__RPC_FAR *retval);
        
        /* [id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IPoints __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval);
        
        END_INTERFACE
    } IPointsVtbl;

    interface IPoints
    {
        CONST_VTBL struct IPointsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPoints_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPoints_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPoints_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPoints_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPoints_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPoints_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPoints_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPoints_get_Count(This,retval)	\
    (This)->lpVtbl -> get_Count(This,retval)

#define IPoints_get_Item(This,Index,retval)	\
    (This)->lpVtbl -> get_Item(This,Index,retval)

#define IPoints_get__NewEnum(This,retval)	\
    (This)->lpVtbl -> get__NewEnum(This,retval)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPoints_get_Count_Proxy( 
    IPoints __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *retval);


void __RPC_STUB IPoints_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPoints_get_Item_Proxy( 
    IPoints __RPC_FAR * This,
    /* [in] */ long Index,
    /* [retval][out] */ IPoint __RPC_FAR *__RPC_FAR *retval);


void __RPC_STUB IPoints_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][restricted][propget] */ HRESULT STDMETHODCALLTYPE IPoints_get__NewEnum_Proxy( 
    IPoints __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *retval);


void __RPC_STUB IPoints_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPoints_INTERFACE_DEFINED__ */


#ifndef __IPane_INTERFACE_DEFINED__
#define __IPane_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IPane
 * at Mon Mar 30 02:37:23 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [object][dual][oleautomation][helpstring][uuid] */ 



DEFINE_GUID(IID_IPane,0x3C591B23,0x1F13,0x101B,0xB8,0x26,0x00,0xDD,0x01,0x10,0x3D,0xE1);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3C591B23-1F13-101B-B826-00DD01103DE1")
    IPane : public IDispatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Lines( 
            /* [retval][out] */ ILines __RPC_FAR *__RPC_FAR *retval) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Points( 
            /* [retval][out] */ IPoints __RPC_FAR *__RPC_FAR *retval) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MaxX( 
            /* [retval][out] */ int __RPC_FAR *retval) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MaxY( 
            /* [retval][out] */ int __RPC_FAR *retval) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPaneVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPane __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPane __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPane __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPane __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPane __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPane __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPane __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Lines )( 
            IPane __RPC_FAR * This,
            /* [retval][out] */ ILines __RPC_FAR *__RPC_FAR *retval);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Points )( 
            IPane __RPC_FAR * This,
            /* [retval][out] */ IPoints __RPC_FAR *__RPC_FAR *retval);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MaxX )( 
            IPane __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *retval);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MaxY )( 
            IPane __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *retval);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clear )( 
            IPane __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IPane __RPC_FAR * This);
        
        END_INTERFACE
    } IPaneVtbl;

    interface IPane
    {
        CONST_VTBL struct IPaneVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPane_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPane_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPane_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPane_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPane_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPane_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPane_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPane_get_Lines(This,retval)	\
    (This)->lpVtbl -> get_Lines(This,retval)

#define IPane_get_Points(This,retval)	\
    (This)->lpVtbl -> get_Points(This,retval)

#define IPane_get_MaxX(This,retval)	\
    (This)->lpVtbl -> get_MaxX(This,retval)

#define IPane_get_MaxY(This,retval)	\
    (This)->lpVtbl -> get_MaxY(This,retval)

#define IPane_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#define IPane_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPane_get_Lines_Proxy( 
    IPane __RPC_FAR * This,
    /* [retval][out] */ ILines __RPC_FAR *__RPC_FAR *retval);


void __RPC_STUB IPane_get_Lines_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPane_get_Points_Proxy( 
    IPane __RPC_FAR * This,
    /* [retval][out] */ IPoints __RPC_FAR *__RPC_FAR *retval);


void __RPC_STUB IPane_get_Points_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPane_get_MaxX_Proxy( 
    IPane __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *retval);


void __RPC_STUB IPane_get_MaxX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IPane_get_MaxY_Proxy( 
    IPane __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *retval);


void __RPC_STUB IPane_get_MaxY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPane_Clear_Proxy( 
    IPane __RPC_FAR * This);


void __RPC_STUB IPane_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPane_Refresh_Proxy( 
    IPane __RPC_FAR * This);


void __RPC_STUB IPane_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPane_INTERFACE_DEFINED__ */


#ifndef __IApplication_INTERFACE_DEFINED__
#define __IApplication_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IApplication
 * at Mon Mar 30 02:37:23 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [object][dual][oleautomation][helpstring][uuid] */ 



DEFINE_GUID(IID_IApplication,0x3C591B22,0x1F13,0x101B,0xB8,0x26,0x00,0xDD,0x01,0x10,0x3D,0xE1);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3C591B22-1F13-101B-B826-00DD01103DE1")
    IApplication : public IDispatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ IApplication __RPC_FAR *__RPC_FAR *retval) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_FullName( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *retval) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IApplication __RPC_FAR *__RPC_FAR *retval) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Visible( 
            /* [in] */ VARIANT_BOOL VisibleFlag) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Visible( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Quit( void) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Pane( 
            /* [retval][out] */ IPane __RPC_FAR *__RPC_FAR *retval) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateLine( 
            /* [retval][out] */ ILine __RPC_FAR *__RPC_FAR *retval) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreatePoint( 
            /* [retval][out] */ IPoint __RPC_FAR *__RPC_FAR *retval) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IApplicationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IApplication __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IApplication __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IApplication __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IApplication __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IApplication __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IApplication __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IApplication __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            IApplication __RPC_FAR * This,
            /* [retval][out] */ IApplication __RPC_FAR *__RPC_FAR *retval);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FullName )( 
            IApplication __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IApplication __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IApplication __RPC_FAR * This,
            /* [retval][out] */ IApplication __RPC_FAR *__RPC_FAR *retval);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Visible )( 
            IApplication __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL VisibleFlag);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Visible )( 
            IApplication __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Quit )( 
            IApplication __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Pane )( 
            IApplication __RPC_FAR * This,
            /* [retval][out] */ IPane __RPC_FAR *__RPC_FAR *retval);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateLine )( 
            IApplication __RPC_FAR * This,
            /* [retval][out] */ ILine __RPC_FAR *__RPC_FAR *retval);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreatePoint )( 
            IApplication __RPC_FAR * This,
            /* [retval][out] */ IPoint __RPC_FAR *__RPC_FAR *retval);
        
        END_INTERFACE
    } IApplicationVtbl;

    interface IApplication
    {
        CONST_VTBL struct IApplicationVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApplication_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IApplication_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IApplication_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IApplication_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IApplication_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IApplication_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IApplication_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IApplication_get_Application(This,retval)	\
    (This)->lpVtbl -> get_Application(This,retval)

#define IApplication_get_FullName(This,retval)	\
    (This)->lpVtbl -> get_FullName(This,retval)

#define IApplication_get_Name(This,retval)	\
    (This)->lpVtbl -> get_Name(This,retval)

#define IApplication_get_Parent(This,retval)	\
    (This)->lpVtbl -> get_Parent(This,retval)

#define IApplication_put_Visible(This,VisibleFlag)	\
    (This)->lpVtbl -> put_Visible(This,VisibleFlag)

#define IApplication_get_Visible(This,retval)	\
    (This)->lpVtbl -> get_Visible(This,retval)

#define IApplication_Quit(This)	\
    (This)->lpVtbl -> Quit(This)

#define IApplication_get_Pane(This,retval)	\
    (This)->lpVtbl -> get_Pane(This,retval)

#define IApplication_CreateLine(This,retval)	\
    (This)->lpVtbl -> CreateLine(This,retval)

#define IApplication_CreatePoint(This,retval)	\
    (This)->lpVtbl -> CreatePoint(This,retval)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApplication_get_Application_Proxy( 
    IApplication __RPC_FAR * This,
    /* [retval][out] */ IApplication __RPC_FAR *__RPC_FAR *retval);


void __RPC_STUB IApplication_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApplication_get_FullName_Proxy( 
    IApplication __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IApplication_get_FullName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IApplication_get_Name_Proxy( 
    IApplication __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *retval);


void __RPC_STUB IApplication_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApplication_get_Parent_Proxy( 
    IApplication __RPC_FAR * This,
    /* [retval][out] */ IApplication __RPC_FAR *__RPC_FAR *retval);


void __RPC_STUB IApplication_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IApplication_put_Visible_Proxy( 
    IApplication __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL VisibleFlag);


void __RPC_STUB IApplication_put_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApplication_get_Visible_Proxy( 
    IApplication __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *retval);


void __RPC_STUB IApplication_get_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IApplication_Quit_Proxy( 
    IApplication __RPC_FAR * This);


void __RPC_STUB IApplication_Quit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IApplication_get_Pane_Proxy( 
    IApplication __RPC_FAR * This,
    /* [retval][out] */ IPane __RPC_FAR *__RPC_FAR *retval);


void __RPC_STUB IApplication_get_Pane_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IApplication_CreateLine_Proxy( 
    IApplication __RPC_FAR * This,
    /* [retval][out] */ ILine __RPC_FAR *__RPC_FAR *retval);


void __RPC_STUB IApplication_CreateLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IApplication_CreatePoint_Proxy( 
    IApplication __RPC_FAR * This,
    /* [retval][out] */ IPoint __RPC_FAR *__RPC_FAR *retval);


void __RPC_STUB IApplication_CreatePoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IApplication_INTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_Lines,0x3C591B21,0x1F13,0x101B,0xB8,0x26,0x00,0xDD,0x01,0x10,0x3D,0xE1);

#ifdef __cplusplus

class DECLSPEC_UUID("3C591B21-1F13-101B-B826-00DD01103DE1")
Lines;
#endif
#endif /* __Lines_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
