/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 03:35:16 1998
 */
/* Compiler settings for micars.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, app_config, c_ext
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

#ifndef __micars_h__
#define __micars_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ICar_FWD_DEFINED__
#define __ICar_FWD_DEFINED__
typedef interface ICar ICar;
#endif 	/* __ICar_FWD_DEFINED__ */


#ifndef __IUtility_FWD_DEFINED__
#define __IUtility_FWD_DEFINED__
typedef interface IUtility IUtility;
#endif 	/* __IUtility_FWD_DEFINED__ */


#ifndef __ICruise_FWD_DEFINED__
#define __ICruise_FWD_DEFINED__
typedef interface ICruise ICruise;
#endif 	/* __ICruise_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ICar_INTERFACE_DEFINED__
#define __ICar_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ICar
 * at Mon Mar 30 03:35:16 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [object][uuid] */ 



EXTERN_C const IID IID_ICar;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0002da00-0000-0000-c000-000000000046")
    ICar : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Shift( 
            /* [in] */ short nGear) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clutch( 
            /* [in] */ short nEngaged) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Speed( 
            /* [in] */ short nMph) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Steer( 
            /* [in] */ short nAngle) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICarVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICar __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICar __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICar __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Shift )( 
            ICar __RPC_FAR * This,
            /* [in] */ short nGear);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clutch )( 
            ICar __RPC_FAR * This,
            /* [in] */ short nEngaged);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Speed )( 
            ICar __RPC_FAR * This,
            /* [in] */ short nMph);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Steer )( 
            ICar __RPC_FAR * This,
            /* [in] */ short nAngle);
        
        END_INTERFACE
    } ICarVtbl;

    interface ICar
    {
        CONST_VTBL struct ICarVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICar_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICar_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICar_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICar_Shift(This,nGear)	\
    (This)->lpVtbl -> Shift(This,nGear)

#define ICar_Clutch(This,nEngaged)	\
    (This)->lpVtbl -> Clutch(This,nEngaged)

#define ICar_Speed(This,nMph)	\
    (This)->lpVtbl -> Speed(This,nMph)

#define ICar_Steer(This,nAngle)	\
    (This)->lpVtbl -> Steer(This,nAngle)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICar_Shift_Proxy( 
    ICar __RPC_FAR * This,
    /* [in] */ short nGear);


void __RPC_STUB ICar_Shift_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICar_Clutch_Proxy( 
    ICar __RPC_FAR * This,
    /* [in] */ short nEngaged);


void __RPC_STUB ICar_Clutch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICar_Speed_Proxy( 
    ICar __RPC_FAR * This,
    /* [in] */ short nMph);


void __RPC_STUB ICar_Speed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICar_Steer_Proxy( 
    ICar __RPC_FAR * This,
    /* [in] */ short nAngle);


void __RPC_STUB ICar_Steer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICar_INTERFACE_DEFINED__ */


#ifndef __IUtility_INTERFACE_DEFINED__
#define __IUtility_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IUtility
 * at Mon Mar 30 03:35:16 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [object][uuid] */ 



EXTERN_C const IID IID_IUtility;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0002da01-0000-0000-c000-000000000046")
    IUtility : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Offroad( 
            /* [in] */ short nGear) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Winch( 
            /* [in] */ short nRpm) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IUtilityVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IUtility __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IUtility __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IUtility __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Offroad )( 
            IUtility __RPC_FAR * This,
            /* [in] */ short nGear);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Winch )( 
            IUtility __RPC_FAR * This,
            /* [in] */ short nRpm);
        
        END_INTERFACE
    } IUtilityVtbl;

    interface IUtility
    {
        CONST_VTBL struct IUtilityVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUtility_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IUtility_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IUtility_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IUtility_Offroad(This,nGear)	\
    (This)->lpVtbl -> Offroad(This,nGear)

#define IUtility_Winch(This,nRpm)	\
    (This)->lpVtbl -> Winch(This,nRpm)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IUtility_Offroad_Proxy( 
    IUtility __RPC_FAR * This,
    /* [in] */ short nGear);


void __RPC_STUB IUtility_Offroad_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IUtility_Winch_Proxy( 
    IUtility __RPC_FAR * This,
    /* [in] */ short nRpm);


void __RPC_STUB IUtility_Winch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IUtility_INTERFACE_DEFINED__ */


#ifndef __ICruise_INTERFACE_DEFINED__
#define __ICruise_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ICruise
 * at Mon Mar 30 03:35:16 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [object][uuid] */ 



EXTERN_C const IID IID_ICruise;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0002da02-0000-0000-c000-000000000046")
    ICruise : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Engage( 
            /* [in] */ BOOL bOnOff) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Adjust( 
            /* [in] */ BOOL bUpDown) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICruiseVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICruise __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICruise __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICruise __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Engage )( 
            ICruise __RPC_FAR * This,
            /* [in] */ BOOL bOnOff);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Adjust )( 
            ICruise __RPC_FAR * This,
            /* [in] */ BOOL bUpDown);
        
        END_INTERFACE
    } ICruiseVtbl;

    interface ICruise
    {
        CONST_VTBL struct ICruiseVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICruise_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICruise_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICruise_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICruise_Engage(This,bOnOff)	\
    (This)->lpVtbl -> Engage(This,bOnOff)

#define ICruise_Adjust(This,bUpDown)	\
    (This)->lpVtbl -> Adjust(This,bUpDown)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICruise_Engage_Proxy( 
    ICruise __RPC_FAR * This,
    /* [in] */ BOOL bOnOff);


void __RPC_STUB ICruise_Engage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICruise_Adjust_Proxy( 
    ICruise __RPC_FAR * This,
    /* [in] */ BOOL bUpDown);


void __RPC_STUB ICruise_Adjust_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICruise_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
