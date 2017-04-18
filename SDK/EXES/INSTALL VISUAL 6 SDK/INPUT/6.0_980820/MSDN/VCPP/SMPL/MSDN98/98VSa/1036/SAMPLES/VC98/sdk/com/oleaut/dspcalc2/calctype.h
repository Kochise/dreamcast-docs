/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 02:37:01 1998
 */
/* Compiler settings for calctype.odl:
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

#ifndef __calctype_h__
#define __calctype_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef ___ICalculator_FWD_DEFINED__
#define ___ICalculator_FWD_DEFINED__
typedef interface _ICalculator _ICalculator;
#endif 	/* ___ICalculator_FWD_DEFINED__ */


#ifndef ___DCalculator_FWD_DEFINED__
#define ___DCalculator_FWD_DEFINED__
typedef interface _DCalculator _DCalculator;
#endif 	/* ___DCalculator_FWD_DEFINED__ */


#ifndef __Calculator_FWD_DEFINED__
#define __Calculator_FWD_DEFINED__

#ifdef __cplusplus
typedef class Calculator Calculator;
#else
typedef struct Calculator Calculator;
#endif /* __cplusplus */

#endif 	/* __Calculator_FWD_DEFINED__ */


void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __DspCalc2_LIBRARY_DEFINED__
#define __DspCalc2_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: DspCalc2
 * at Mon Mar 30 02:37:01 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [version][lcid][helpstring][uuid] */ 


typedef 
enum operators
    {	OP_NONE	= 0,
	OP_PLUS	= OP_NONE + 1,
	OP_MINUS	= OP_PLUS + 1,
	OP_MULT	= OP_MINUS + 1,
	OP_DIV	= OP_MULT + 1
    }	OPERATORS;


DEFINE_GUID(LIBID_DspCalc2,0x00020470,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#ifndef ___ICalculator_INTERFACE_DEFINED__
#define ___ICalculator_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: _ICalculator
 * at Mon Mar 30 02:37:01 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [object][helpstring][uuid] */ 



DEFINE_GUID(IID__ICalculator,0x00020441,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("00020441-0000-0000-C000-000000000046")
    _ICalculator : public IUnknown
    {
    public:
        virtual /* [propput] */ void STDMETHODCALLTYPE put_Accum( 
            /* [in] */ long l) = 0;
        
        virtual /* [helpstring][propget] */ long STDMETHODCALLTYPE get_Accum( void) = 0;
        
        virtual /* [propput] */ void STDMETHODCALLTYPE put_Opnd( 
            /* [in] */ long l) = 0;
        
        virtual /* [propget] */ long STDMETHODCALLTYPE get_Opnd( void) = 0;
        
        virtual /* [propput] */ void STDMETHODCALLTYPE put_Op( 
            /* [in] */ OPERATORS op) = 0;
        
        virtual /* [propget] */ OPERATORS STDMETHODCALLTYPE get_Op( void) = 0;
        
        virtual VARIANT_BOOL STDMETHODCALLTYPE Eval( void) = 0;
        
        virtual void STDMETHODCALLTYPE DCClear( void) = 0;
        
        virtual void STDMETHODCALLTYPE Display( void) = 0;
        
        virtual void STDMETHODCALLTYPE Quit( void) = 0;
        
        virtual /* [vararg] */ VARIANT_BOOL STDMETHODCALLTYPE Button( 
            /* [in] */ SAFEARRAY __RPC_FAR * psa) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct _ICalculatorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _ICalculator __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _ICalculator __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _ICalculator __RPC_FAR * This);
        
        /* [propput] */ void ( STDMETHODCALLTYPE __RPC_FAR *put_Accum )( 
            _ICalculator __RPC_FAR * This,
            /* [in] */ long l);
        
        /* [helpstring][propget] */ long ( STDMETHODCALLTYPE __RPC_FAR *get_Accum )( 
            _ICalculator __RPC_FAR * This);
        
        /* [propput] */ void ( STDMETHODCALLTYPE __RPC_FAR *put_Opnd )( 
            _ICalculator __RPC_FAR * This,
            /* [in] */ long l);
        
        /* [propget] */ long ( STDMETHODCALLTYPE __RPC_FAR *get_Opnd )( 
            _ICalculator __RPC_FAR * This);
        
        /* [propput] */ void ( STDMETHODCALLTYPE __RPC_FAR *put_Op )( 
            _ICalculator __RPC_FAR * This,
            /* [in] */ OPERATORS op);
        
        /* [propget] */ OPERATORS ( STDMETHODCALLTYPE __RPC_FAR *get_Op )( 
            _ICalculator __RPC_FAR * This);
        
        VARIANT_BOOL ( STDMETHODCALLTYPE __RPC_FAR *Eval )( 
            _ICalculator __RPC_FAR * This);
        
        void ( STDMETHODCALLTYPE __RPC_FAR *DCClear )( 
            _ICalculator __RPC_FAR * This);
        
        void ( STDMETHODCALLTYPE __RPC_FAR *Display )( 
            _ICalculator __RPC_FAR * This);
        
        void ( STDMETHODCALLTYPE __RPC_FAR *Quit )( 
            _ICalculator __RPC_FAR * This);
        
        /* [vararg] */ VARIANT_BOOL ( STDMETHODCALLTYPE __RPC_FAR *Button )( 
            _ICalculator __RPC_FAR * This,
            /* [in] */ SAFEARRAY __RPC_FAR * psa);
        
        END_INTERFACE
    } _ICalculatorVtbl;

    interface _ICalculator
    {
        CONST_VTBL struct _ICalculatorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ICalculator_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _ICalculator_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _ICalculator_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _ICalculator_put_Accum(This,l)	\
    (This)->lpVtbl -> put_Accum(This,l)

#define _ICalculator_get_Accum(This)	\
    (This)->lpVtbl -> get_Accum(This)

#define _ICalculator_put_Opnd(This,l)	\
    (This)->lpVtbl -> put_Opnd(This,l)

#define _ICalculator_get_Opnd(This)	\
    (This)->lpVtbl -> get_Opnd(This)

#define _ICalculator_put_Op(This,op)	\
    (This)->lpVtbl -> put_Op(This,op)

#define _ICalculator_get_Op(This)	\
    (This)->lpVtbl -> get_Op(This)

#define _ICalculator_Eval(This)	\
    (This)->lpVtbl -> Eval(This)

#define _ICalculator_DCClear(This)	\
    (This)->lpVtbl -> DCClear(This)

#define _ICalculator_Display(This)	\
    (This)->lpVtbl -> Display(This)

#define _ICalculator_Quit(This)	\
    (This)->lpVtbl -> Quit(This)

#define _ICalculator_Button(This,psa)	\
    (This)->lpVtbl -> Button(This,psa)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propput] */ void STDMETHODCALLTYPE _ICalculator_put_Accum_Proxy( 
    _ICalculator __RPC_FAR * This,
    /* [in] */ long l);


void __RPC_STUB _ICalculator_put_Accum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ long STDMETHODCALLTYPE _ICalculator_get_Accum_Proxy( 
    _ICalculator __RPC_FAR * This);


void __RPC_STUB _ICalculator_get_Accum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ void STDMETHODCALLTYPE _ICalculator_put_Opnd_Proxy( 
    _ICalculator __RPC_FAR * This,
    /* [in] */ long l);


void __RPC_STUB _ICalculator_put_Opnd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ long STDMETHODCALLTYPE _ICalculator_get_Opnd_Proxy( 
    _ICalculator __RPC_FAR * This);


void __RPC_STUB _ICalculator_get_Opnd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ void STDMETHODCALLTYPE _ICalculator_put_Op_Proxy( 
    _ICalculator __RPC_FAR * This,
    /* [in] */ OPERATORS op);


void __RPC_STUB _ICalculator_put_Op_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ OPERATORS STDMETHODCALLTYPE _ICalculator_get_Op_Proxy( 
    _ICalculator __RPC_FAR * This);


void __RPC_STUB _ICalculator_get_Op_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


VARIANT_BOOL STDMETHODCALLTYPE _ICalculator_Eval_Proxy( 
    _ICalculator __RPC_FAR * This);


void __RPC_STUB _ICalculator_Eval_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


void STDMETHODCALLTYPE _ICalculator_DCClear_Proxy( 
    _ICalculator __RPC_FAR * This);


void __RPC_STUB _ICalculator_DCClear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


void STDMETHODCALLTYPE _ICalculator_Display_Proxy( 
    _ICalculator __RPC_FAR * This);


void __RPC_STUB _ICalculator_Display_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


void STDMETHODCALLTYPE _ICalculator_Quit_Proxy( 
    _ICalculator __RPC_FAR * This);


void __RPC_STUB _ICalculator_Quit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [vararg] */ VARIANT_BOOL STDMETHODCALLTYPE _ICalculator_Button_Proxy( 
    _ICalculator __RPC_FAR * This,
    /* [in] */ SAFEARRAY __RPC_FAR * psa);


void __RPC_STUB _ICalculator_Button_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* ___ICalculator_INTERFACE_DEFINED__ */


#ifndef ___DCalculator_DISPINTERFACE_DEFINED__
#define ___DCalculator_DISPINTERFACE_DEFINED__

/****************************************
 * Generated header for dispinterface: _DCalculator
 * at Mon Mar 30 02:37:01 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [helpstring][uuid] */ 



DEFINE_GUID(DIID__DCalculator,0x00020442,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("00020442-0000-0000-C000-000000000046")
    _DCalculator : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DCalculatorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _DCalculator __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _DCalculator __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _DCalculator __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _DCalculator __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _DCalculator __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _DCalculator __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _DCalculator __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _DCalculatorVtbl;

    interface _DCalculator
    {
        CONST_VTBL struct _DCalculatorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DCalculator_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DCalculator_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DCalculator_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DCalculator_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DCalculator_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DCalculator_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DCalculator_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DCalculator_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_Calculator,0x00020469,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#ifdef __cplusplus

class DECLSPEC_UUID("00020469-0000-0000-C000-000000000046")
Calculator;
#endif
#endif /* __DspCalc2_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
