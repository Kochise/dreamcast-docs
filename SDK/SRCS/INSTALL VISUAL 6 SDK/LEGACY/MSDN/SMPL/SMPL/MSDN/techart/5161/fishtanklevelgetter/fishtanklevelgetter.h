/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.01.75 */
/* at Mon Jul 14 09:24:35 1997
 */
/* Compiler settings for FishTankLevelGetter.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"
#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __FishTankLevelGetter_h__
#define __FishTankLevelGetter_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ILevelGetter_FWD_DEFINED__
#define __ILevelGetter_FWD_DEFINED__
typedef interface ILevelGetter ILevelGetter;
#endif 	/* __ILevelGetter_FWD_DEFINED__ */


#ifndef __LevelGetter_FWD_DEFINED__
#define __LevelGetter_FWD_DEFINED__

#ifdef __cplusplus
typedef class LevelGetter LevelGetter;
#else
typedef struct LevelGetter LevelGetter;
#endif /* __cplusplus */

#endif 	/* __LevelGetter_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ILevelGetter_INTERFACE_DEFINED__
#define __ILevelGetter_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ILevelGetter
 * at Mon Jul 14 09:24:35 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][uuid][object] */ 



EXTERN_C const IID IID_ILevelGetter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("7F0DFAA2-F56D-11D0-A980-0020182A7050")
    ILevelGetter : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetLowestPossibleSafeLevel( 
            /* [retval][out] */ long __RPC_FAR *plLowestSafeLevel) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetHighestPossibleSafeLevel( 
            /* [retval][out] */ long __RPC_FAR *plHighestSafeLevel) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentLevel( 
            /* [retval][out] */ long __RPC_FAR *plCurrentLevel) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTextMessage( 
            /* [retval][out] */ BSTR __RPC_FAR *ppbstrMessage) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILevelGetterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ILevelGetter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ILevelGetter __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ILevelGetter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLowestPossibleSafeLevel )( 
            ILevelGetter __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plLowestSafeLevel);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetHighestPossibleSafeLevel )( 
            ILevelGetter __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plHighestSafeLevel);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCurrentLevel )( 
            ILevelGetter __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plCurrentLevel);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTextMessage )( 
            ILevelGetter __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ppbstrMessage);
        
        END_INTERFACE
    } ILevelGetterVtbl;

    interface ILevelGetter
    {
        CONST_VTBL struct ILevelGetterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILevelGetter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILevelGetter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILevelGetter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILevelGetter_GetLowestPossibleSafeLevel(This,plLowestSafeLevel)	\
    (This)->lpVtbl -> GetLowestPossibleSafeLevel(This,plLowestSafeLevel)

#define ILevelGetter_GetHighestPossibleSafeLevel(This,plHighestSafeLevel)	\
    (This)->lpVtbl -> GetHighestPossibleSafeLevel(This,plHighestSafeLevel)

#define ILevelGetter_GetCurrentLevel(This,plCurrentLevel)	\
    (This)->lpVtbl -> GetCurrentLevel(This,plCurrentLevel)

#define ILevelGetter_GetTextMessage(This,ppbstrMessage)	\
    (This)->lpVtbl -> GetTextMessage(This,ppbstrMessage)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ILevelGetter_GetLowestPossibleSafeLevel_Proxy( 
    ILevelGetter __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plLowestSafeLevel);


void __RPC_STUB ILevelGetter_GetLowestPossibleSafeLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ILevelGetter_GetHighestPossibleSafeLevel_Proxy( 
    ILevelGetter __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plHighestSafeLevel);


void __RPC_STUB ILevelGetter_GetHighestPossibleSafeLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ILevelGetter_GetCurrentLevel_Proxy( 
    ILevelGetter __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plCurrentLevel);


void __RPC_STUB ILevelGetter_GetCurrentLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ILevelGetter_GetTextMessage_Proxy( 
    ILevelGetter __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ppbstrMessage);


void __RPC_STUB ILevelGetter_GetTextMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILevelGetter_INTERFACE_DEFINED__ */



#ifndef __FISHTANKLEVELGETTERLib_LIBRARY_DEFINED__
#define __FISHTANKLEVELGETTERLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: FISHTANKLEVELGETTERLib
 * at Mon Jul 14 09:24:35 1997
 * using MIDL 3.01.75
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_FISHTANKLEVELGETTERLib;

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_LevelGetter;

class DECLSPEC_UUID("7F0DFAA3-F56D-11D0-A980-0020182A7050")
LevelGetter;
#endif
#endif /* __FISHTANKLEVELGETTERLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
