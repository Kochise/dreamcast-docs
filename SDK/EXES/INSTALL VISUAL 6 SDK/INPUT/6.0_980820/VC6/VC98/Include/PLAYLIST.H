/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.02.88 */
/* at Thu Nov 13 19:28:41 1997
 */
/* Compiler settings for playlist.idl:
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

#ifndef __playlist_h__
#define __playlist_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IAMPlayListItem_FWD_DEFINED__
#define __IAMPlayListItem_FWD_DEFINED__
typedef interface IAMPlayListItem IAMPlayListItem;
#endif 	/* __IAMPlayListItem_FWD_DEFINED__ */


#ifndef __IAMPlayList_FWD_DEFINED__
#define __IAMPlayList_FWD_DEFINED__
typedef interface IAMPlayList IAMPlayList;
#endif 	/* __IAMPlayList_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "strmif.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL_itf_playlist_0000
 * at Thu Nov 13 19:28:41 1997
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 


EXTERN_GUID(IID_IAMPlayListItem,0x56a868ff,0x0ad4,0x11ce,0xb0,0xa3,0x0,0x20,0xaf,0x0b,0xa7,0x70);

enum AMPlayListItemFlags
    {	AMPLAYLISTITEM_CANSKIP	= 0x1,
	AMPLAYLISTITEM_CANBIND	= 0x2
    };


extern RPC_IF_HANDLE __MIDL_itf_playlist_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_playlist_0000_v0_0_s_ifspec;

#ifndef __IAMPlayListItem_INTERFACE_DEFINED__
#define __IAMPlayListItem_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAMPlayListItem
 * at Thu Nov 13 19:28:41 1997
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IAMPlayListItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("56a868ff-0ad4-11ce-b03a-0020af0ba770")
    IAMPlayListItem : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetFlags( 
            /* [out] */ DWORD __RPC_FAR *pdwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSourceCount( 
            /* [out] */ DWORD __RPC_FAR *pdwSources) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSourceURL( 
            /* [in] */ DWORD dwSourceIndex,
            /* [out] */ BSTR __RPC_FAR *pbstrURL) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSourceStart( 
            /* [in] */ DWORD dwSourceIndex,
            /* [out] */ REFERENCE_TIME __RPC_FAR *prtStart) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSourceDuration( 
            /* [in] */ DWORD dwSourceIndex,
            /* [out] */ REFERENCE_TIME __RPC_FAR *prtDuration) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSourceStartMarker( 
            /* [in] */ DWORD dwSourceIndex,
            /* [out] */ DWORD __RPC_FAR *pdwMarker) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSourceEndMarker( 
            /* [in] */ DWORD dwSourceIndex,
            /* [out] */ DWORD __RPC_FAR *pdwMarker) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSourceStartMarkerName( 
            /* [in] */ DWORD dwSourceIndex,
            /* [out] */ BSTR __RPC_FAR *pbstrStartMarker) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSourceEndMarkerName( 
            /* [in] */ DWORD dwSourceIndex,
            /* [out] */ BSTR __RPC_FAR *pbstrEndMarker) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMPlayListItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAMPlayListItem __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAMPlayListItem __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAMPlayListItem __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFlags )( 
            IAMPlayListItem __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *pdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSourceCount )( 
            IAMPlayListItem __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *pdwSources);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSourceURL )( 
            IAMPlayListItem __RPC_FAR * This,
            /* [in] */ DWORD dwSourceIndex,
            /* [out] */ BSTR __RPC_FAR *pbstrURL);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSourceStart )( 
            IAMPlayListItem __RPC_FAR * This,
            /* [in] */ DWORD dwSourceIndex,
            /* [out] */ REFERENCE_TIME __RPC_FAR *prtStart);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSourceDuration )( 
            IAMPlayListItem __RPC_FAR * This,
            /* [in] */ DWORD dwSourceIndex,
            /* [out] */ REFERENCE_TIME __RPC_FAR *prtDuration);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSourceStartMarker )( 
            IAMPlayListItem __RPC_FAR * This,
            /* [in] */ DWORD dwSourceIndex,
            /* [out] */ DWORD __RPC_FAR *pdwMarker);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSourceEndMarker )( 
            IAMPlayListItem __RPC_FAR * This,
            /* [in] */ DWORD dwSourceIndex,
            /* [out] */ DWORD __RPC_FAR *pdwMarker);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSourceStartMarkerName )( 
            IAMPlayListItem __RPC_FAR * This,
            /* [in] */ DWORD dwSourceIndex,
            /* [out] */ BSTR __RPC_FAR *pbstrStartMarker);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSourceEndMarkerName )( 
            IAMPlayListItem __RPC_FAR * This,
            /* [in] */ DWORD dwSourceIndex,
            /* [out] */ BSTR __RPC_FAR *pbstrEndMarker);
        
        END_INTERFACE
    } IAMPlayListItemVtbl;

    interface IAMPlayListItem
    {
        CONST_VTBL struct IAMPlayListItemVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMPlayListItem_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMPlayListItem_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMPlayListItem_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMPlayListItem_GetFlags(This,pdwFlags)	\
    (This)->lpVtbl -> GetFlags(This,pdwFlags)

#define IAMPlayListItem_GetSourceCount(This,pdwSources)	\
    (This)->lpVtbl -> GetSourceCount(This,pdwSources)

#define IAMPlayListItem_GetSourceURL(This,dwSourceIndex,pbstrURL)	\
    (This)->lpVtbl -> GetSourceURL(This,dwSourceIndex,pbstrURL)

#define IAMPlayListItem_GetSourceStart(This,dwSourceIndex,prtStart)	\
    (This)->lpVtbl -> GetSourceStart(This,dwSourceIndex,prtStart)

#define IAMPlayListItem_GetSourceDuration(This,dwSourceIndex,prtDuration)	\
    (This)->lpVtbl -> GetSourceDuration(This,dwSourceIndex,prtDuration)

#define IAMPlayListItem_GetSourceStartMarker(This,dwSourceIndex,pdwMarker)	\
    (This)->lpVtbl -> GetSourceStartMarker(This,dwSourceIndex,pdwMarker)

#define IAMPlayListItem_GetSourceEndMarker(This,dwSourceIndex,pdwMarker)	\
    (This)->lpVtbl -> GetSourceEndMarker(This,dwSourceIndex,pdwMarker)

#define IAMPlayListItem_GetSourceStartMarkerName(This,dwSourceIndex,pbstrStartMarker)	\
    (This)->lpVtbl -> GetSourceStartMarkerName(This,dwSourceIndex,pbstrStartMarker)

#define IAMPlayListItem_GetSourceEndMarkerName(This,dwSourceIndex,pbstrEndMarker)	\
    (This)->lpVtbl -> GetSourceEndMarkerName(This,dwSourceIndex,pbstrEndMarker)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMPlayListItem_GetFlags_Proxy( 
    IAMPlayListItem __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *pdwFlags);


void __RPC_STUB IAMPlayListItem_GetFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMPlayListItem_GetSourceCount_Proxy( 
    IAMPlayListItem __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *pdwSources);


void __RPC_STUB IAMPlayListItem_GetSourceCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMPlayListItem_GetSourceURL_Proxy( 
    IAMPlayListItem __RPC_FAR * This,
    /* [in] */ DWORD dwSourceIndex,
    /* [out] */ BSTR __RPC_FAR *pbstrURL);


void __RPC_STUB IAMPlayListItem_GetSourceURL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMPlayListItem_GetSourceStart_Proxy( 
    IAMPlayListItem __RPC_FAR * This,
    /* [in] */ DWORD dwSourceIndex,
    /* [out] */ REFERENCE_TIME __RPC_FAR *prtStart);


void __RPC_STUB IAMPlayListItem_GetSourceStart_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMPlayListItem_GetSourceDuration_Proxy( 
    IAMPlayListItem __RPC_FAR * This,
    /* [in] */ DWORD dwSourceIndex,
    /* [out] */ REFERENCE_TIME __RPC_FAR *prtDuration);


void __RPC_STUB IAMPlayListItem_GetSourceDuration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMPlayListItem_GetSourceStartMarker_Proxy( 
    IAMPlayListItem __RPC_FAR * This,
    /* [in] */ DWORD dwSourceIndex,
    /* [out] */ DWORD __RPC_FAR *pdwMarker);


void __RPC_STUB IAMPlayListItem_GetSourceStartMarker_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMPlayListItem_GetSourceEndMarker_Proxy( 
    IAMPlayListItem __RPC_FAR * This,
    /* [in] */ DWORD dwSourceIndex,
    /* [out] */ DWORD __RPC_FAR *pdwMarker);


void __RPC_STUB IAMPlayListItem_GetSourceEndMarker_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMPlayListItem_GetSourceStartMarkerName_Proxy( 
    IAMPlayListItem __RPC_FAR * This,
    /* [in] */ DWORD dwSourceIndex,
    /* [out] */ BSTR __RPC_FAR *pbstrStartMarker);


void __RPC_STUB IAMPlayListItem_GetSourceStartMarkerName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMPlayListItem_GetSourceEndMarkerName_Proxy( 
    IAMPlayListItem __RPC_FAR * This,
    /* [in] */ DWORD dwSourceIndex,
    /* [out] */ BSTR __RPC_FAR *pbstrEndMarker);


void __RPC_STUB IAMPlayListItem_GetSourceEndMarkerName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMPlayListItem_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_playlist_0227
 * at Thu Nov 13 19:28:41 1997
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 



enum AMPlayListFlags
    {	AMPLAYLISTITEM_STARTINSCANMODE	= 0x1
    };
EXTERN_GUID(IID_IAMPlayList,0x56a868fe,0x0ad4,0x11ce,0xb0,0xa3,0x0,0x20,0xaf,0x0b,0xa7,0x70);


extern RPC_IF_HANDLE __MIDL_itf_playlist_0227_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_playlist_0227_v0_0_s_ifspec;

#ifndef __IAMPlayList_INTERFACE_DEFINED__
#define __IAMPlayList_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAMPlayList
 * at Thu Nov 13 19:28:41 1997
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IAMPlayList;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("56a868fe-0ad4-11ce-b03a-0020af0ba770")
    IAMPlayList : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetFlags( 
            /* [out] */ DWORD __RPC_FAR *pdwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetItemCount( 
            /* [out] */ DWORD __RPC_FAR *pdwItems) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetItem( 
            /* [in] */ DWORD dwItemIndex,
            /* [out] */ IAMPlayListItem __RPC_FAR *__RPC_FAR *ppItem) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRepeatInfo( 
            /* [out] */ DWORD __RPC_FAR *pdwRepeatCount,
            /* [out] */ DWORD __RPC_FAR *pdwRepeatStart,
            /* [out] */ DWORD __RPC_FAR *pdwRepeatEnd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetScanDuration( 
            /* [out] */ REFERENCE_TIME __RPC_FAR *prtScanDuration) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMPlayListVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAMPlayList __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAMPlayList __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAMPlayList __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFlags )( 
            IAMPlayList __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *pdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetItemCount )( 
            IAMPlayList __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *pdwItems);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetItem )( 
            IAMPlayList __RPC_FAR * This,
            /* [in] */ DWORD dwItemIndex,
            /* [out] */ IAMPlayListItem __RPC_FAR *__RPC_FAR *ppItem);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRepeatInfo )( 
            IAMPlayList __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *pdwRepeatCount,
            /* [out] */ DWORD __RPC_FAR *pdwRepeatStart,
            /* [out] */ DWORD __RPC_FAR *pdwRepeatEnd);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetScanDuration )( 
            IAMPlayList __RPC_FAR * This,
            /* [out] */ REFERENCE_TIME __RPC_FAR *prtScanDuration);
        
        END_INTERFACE
    } IAMPlayListVtbl;

    interface IAMPlayList
    {
        CONST_VTBL struct IAMPlayListVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMPlayList_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMPlayList_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMPlayList_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMPlayList_GetFlags(This,pdwFlags)	\
    (This)->lpVtbl -> GetFlags(This,pdwFlags)

#define IAMPlayList_GetItemCount(This,pdwItems)	\
    (This)->lpVtbl -> GetItemCount(This,pdwItems)

#define IAMPlayList_GetItem(This,dwItemIndex,ppItem)	\
    (This)->lpVtbl -> GetItem(This,dwItemIndex,ppItem)

#define IAMPlayList_GetRepeatInfo(This,pdwRepeatCount,pdwRepeatStart,pdwRepeatEnd)	\
    (This)->lpVtbl -> GetRepeatInfo(This,pdwRepeatCount,pdwRepeatStart,pdwRepeatEnd)

#define IAMPlayList_GetScanDuration(This,prtScanDuration)	\
    (This)->lpVtbl -> GetScanDuration(This,prtScanDuration)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMPlayList_GetFlags_Proxy( 
    IAMPlayList __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *pdwFlags);


void __RPC_STUB IAMPlayList_GetFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMPlayList_GetItemCount_Proxy( 
    IAMPlayList __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *pdwItems);


void __RPC_STUB IAMPlayList_GetItemCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMPlayList_GetItem_Proxy( 
    IAMPlayList __RPC_FAR * This,
    /* [in] */ DWORD dwItemIndex,
    /* [out] */ IAMPlayListItem __RPC_FAR *__RPC_FAR *ppItem);


void __RPC_STUB IAMPlayList_GetItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMPlayList_GetRepeatInfo_Proxy( 
    IAMPlayList __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *pdwRepeatCount,
    /* [out] */ DWORD __RPC_FAR *pdwRepeatStart,
    /* [out] */ DWORD __RPC_FAR *pdwRepeatEnd);


void __RPC_STUB IAMPlayList_GetRepeatInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMPlayList_GetScanDuration_Proxy( 
    IAMPlayList __RPC_FAR * This,
    /* [out] */ REFERENCE_TIME __RPC_FAR *prtScanDuration);


void __RPC_STUB IAMPlayList_GetScanDuration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMPlayList_INTERFACE_DEFINED__ */


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
