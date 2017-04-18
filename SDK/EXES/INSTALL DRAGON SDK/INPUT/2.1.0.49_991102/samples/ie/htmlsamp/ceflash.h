/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Sep 30 18:36:28 1999
 */
/* Compiler settings for CEFlash.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __CEFlash_h__
#define __CEFlash_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IShockwaveFlash_FWD_DEFINED__
#define __IShockwaveFlash_FWD_DEFINED__
typedef interface IShockwaveFlash IShockwaveFlash;
#endif 	/* __IShockwaveFlash_FWD_DEFINED__ */


#ifndef __DShockwaveFlashEvents_FWD_DEFINED__
#define __DShockwaveFlashEvents_FWD_DEFINED__
typedef interface DShockwaveFlashEvents DShockwaveFlashEvents;
#endif 	/* __DShockwaveFlashEvents_FWD_DEFINED__ */


#ifndef __IDCFlashPlayer_FWD_DEFINED__
#define __IDCFlashPlayer_FWD_DEFINED__
typedef interface IDCFlashPlayer IDCFlashPlayer;
#endif 	/* __IDCFlashPlayer_FWD_DEFINED__ */


#ifndef __ShockwaveFlash_FWD_DEFINED__
#define __ShockwaveFlash_FWD_DEFINED__

#ifdef __cplusplus
typedef class ShockwaveFlash ShockwaveFlash;
#else
typedef struct ShockwaveFlash ShockwaveFlash;
#endif /* __cplusplus */

#endif 	/* __ShockwaveFlash_FWD_DEFINED__ */


#ifndef __FlashProp_FWD_DEFINED__
#define __FlashProp_FWD_DEFINED__

#ifdef __cplusplus
typedef class FlashProp FlashProp;
#else
typedef struct FlashProp FlashProp;
#endif /* __cplusplus */

#endif 	/* __FlashProp_FWD_DEFINED__ */


#ifndef __DCFlashPlayer_FWD_DEFINED__
#define __DCFlashPlayer_FWD_DEFINED__

#ifdef __cplusplus
typedef class DCFlashPlayer DCFlashPlayer;
#else
typedef struct DCFlashPlayer DCFlashPlayer;
#endif /* __cplusplus */

#endif 	/* __DCFlashPlayer_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __ShockwaveFlashObjects_LIBRARY_DEFINED__
#define __ShockwaveFlashObjects_LIBRARY_DEFINED__

/* library ShockwaveFlashObjects */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_ShockwaveFlashObjects;

#ifndef __IShockwaveFlash_INTERFACE_DEFINED__
#define __IShockwaveFlash_INTERFACE_DEFINED__

/* interface IShockwaveFlash */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IShockwaveFlash;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D27CDB6C-AE6D-11cf-96B8-444553540000")
    IShockwaveFlash : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ReadyState( 
            /* [retval][out] */ long __RPC_FAR *thestate) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_TotalFrames( 
            /* [retval][out] */ long __RPC_FAR *numframes) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Playing( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *playing) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Playing( 
            /* [in] */ VARIANT_BOOL playing) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Quality( 
            /* [retval][out] */ int __RPC_FAR *quality) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Quality( 
            /* [in] */ int quality) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ScaleMode( 
            /* [retval][out] */ int __RPC_FAR *scale) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_ScaleMode( 
            /* [in] */ int scale) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_AlignMode( 
            /* [retval][out] */ int __RPC_FAR *align) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_AlignMode( 
            /* [in] */ int align) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_BackgroundColor( 
            /* [retval][out] */ long __RPC_FAR *color) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_BackgroundColor( 
            /* [in] */ long color) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Loop( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *loop) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Loop( 
            /* [in] */ VARIANT_BOOL loop) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Movie( 
            /* [retval][out] */ BSTR __RPC_FAR *path) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Movie( 
            /* [in] */ BSTR path) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_FrameNum( 
            /* [retval][out] */ long __RPC_FAR *framenum) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_FrameNum( 
            /* [in] */ long framenum) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetZoomRect( 
            /* [in] */ long left,
            /* [in] */ long top,
            /* [in] */ long right,
            /* [in] */ long bottom) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Zoom( 
            /* [in] */ int factor) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Pan( 
            /* [in] */ long x,
            /* [in] */ long y,
            /* [in] */ int mode) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Play( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Back( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Forward( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Rewind( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE StopPlay( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GotoFrame( 
            /* [in] */ long frameNum) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE CurrentFrame( 
            /* [retval][out] */ long __RPC_FAR *frameNum) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE IsPlaying( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *playing) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE PercentLoaded( 
            /* [retval][out] */ long __RPC_FAR *__MIDL_0016) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE FrameLoaded( 
            /* [in] */ long frameNum,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *loaded) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE FlashVersion( 
            /* [retval][out] */ long __RPC_FAR *version) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_WMode( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_WMode( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_SAlign( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_SAlign( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Menu( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Menu( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Base( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Base( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Scale( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Scale( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_DeviceFont( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_DeviceFont( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_EmbedMovie( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_EmbedMovie( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_BGColor( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_BGColor( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Quality2( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Quality2( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE LoadMovie( 
            /* [in] */ int layer,
            /* [in] */ BSTR url) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE TGotoFrame( 
            /* [in] */ BSTR target,
            /* [in] */ long frameNum) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE TGotoLabel( 
            /* [in] */ BSTR target,
            /* [in] */ BSTR label) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE TCurrentFrame( 
            /* [in] */ BSTR target,
            /* [retval][out] */ long __RPC_FAR *frameNum) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE TCurrentLabel( 
            /* [in] */ BSTR target,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE TPlay( 
            /* [in] */ BSTR target) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE TStopPlay( 
            /* [in] */ BSTR target) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetVariable( 
            /* [in] */ BSTR name,
            /* [in] */ BSTR value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetVariable( 
            /* [in] */ BSTR name,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE TSetProperty( 
            /* [in] */ BSTR target,
            /* [in] */ int property,
            /* [in] */ BSTR value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE TGetProperty( 
            /* [in] */ BSTR target,
            /* [in] */ int property,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE TCallFrame( 
            /* [in] */ BSTR target,
            /* [in] */ int frameNum) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE TCallLabel( 
            /* [in] */ BSTR target,
            /* [in] */ BSTR label) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE TSetPropertyNum( 
            /* [in] */ BSTR target,
            /* [in] */ int property,
            /* [in] */ double value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE TGetPropertyNum( 
            /* [in] */ BSTR target,
            /* [in] */ int property,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_SWRemote( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_SWRemote( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IShockwaveFlashVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IShockwaveFlash __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IShockwaveFlash __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReadyState )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *thestate);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TotalFrames )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *numframes);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Playing )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *playing);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Playing )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL playing);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Quality )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *quality);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Quality )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ int quality);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ScaleMode )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *scale);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ScaleMode )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ int scale);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AlignMode )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *align);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AlignMode )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ int align);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BackgroundColor )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *color);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BackgroundColor )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ long color);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Loop )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *loop);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Loop )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL loop);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Movie )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *path);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Movie )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ BSTR path);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FrameNum )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *framenum);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FrameNum )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ long framenum);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetZoomRect )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ long left,
            /* [in] */ long top,
            /* [in] */ long right,
            /* [in] */ long bottom);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Zoom )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ int factor);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Pan )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ long x,
            /* [in] */ long y,
            /* [in] */ int mode);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Play )( 
            IShockwaveFlash __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IShockwaveFlash __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Back )( 
            IShockwaveFlash __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Forward )( 
            IShockwaveFlash __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Rewind )( 
            IShockwaveFlash __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StopPlay )( 
            IShockwaveFlash __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GotoFrame )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ long frameNum);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CurrentFrame )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *frameNum);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsPlaying )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *playing);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PercentLoaded )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *__MIDL_0016);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FrameLoaded )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ long frameNum,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *loaded);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FlashVersion )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *version);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WMode )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WMode )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SAlign )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SAlign )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Menu )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Menu )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Base )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Base )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Scale )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Scale )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DeviceFont )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DeviceFont )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EmbedMovie )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EmbedMovie )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BGColor )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BGColor )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Quality2 )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Quality2 )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadMovie )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ int layer,
            /* [in] */ BSTR url);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TGotoFrame )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ BSTR target,
            /* [in] */ long frameNum);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TGotoLabel )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ BSTR target,
            /* [in] */ BSTR label);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TCurrentFrame )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ BSTR target,
            /* [retval][out] */ long __RPC_FAR *frameNum);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TCurrentLabel )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ BSTR target,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TPlay )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ BSTR target);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TStopPlay )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ BSTR target);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetVariable )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [in] */ BSTR value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVariable )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TSetProperty )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ BSTR target,
            /* [in] */ int property,
            /* [in] */ BSTR value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TGetProperty )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ BSTR target,
            /* [in] */ int property,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TCallFrame )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ BSTR target,
            /* [in] */ int frameNum);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TCallLabel )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ BSTR target,
            /* [in] */ BSTR label);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TSetPropertyNum )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ BSTR target,
            /* [in] */ int property,
            /* [in] */ double value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TGetPropertyNum )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ BSTR target,
            /* [in] */ int property,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SWRemote )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SWRemote )( 
            IShockwaveFlash __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } IShockwaveFlashVtbl;

    interface IShockwaveFlash
    {
        CONST_VTBL struct IShockwaveFlashVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IShockwaveFlash_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IShockwaveFlash_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IShockwaveFlash_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IShockwaveFlash_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IShockwaveFlash_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IShockwaveFlash_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IShockwaveFlash_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IShockwaveFlash_get_ReadyState(This,thestate)	\
    (This)->lpVtbl -> get_ReadyState(This,thestate)

#define IShockwaveFlash_get_TotalFrames(This,numframes)	\
    (This)->lpVtbl -> get_TotalFrames(This,numframes)

#define IShockwaveFlash_get_Playing(This,playing)	\
    (This)->lpVtbl -> get_Playing(This,playing)

#define IShockwaveFlash_put_Playing(This,playing)	\
    (This)->lpVtbl -> put_Playing(This,playing)

#define IShockwaveFlash_get_Quality(This,quality)	\
    (This)->lpVtbl -> get_Quality(This,quality)

#define IShockwaveFlash_put_Quality(This,quality)	\
    (This)->lpVtbl -> put_Quality(This,quality)

#define IShockwaveFlash_get_ScaleMode(This,scale)	\
    (This)->lpVtbl -> get_ScaleMode(This,scale)

#define IShockwaveFlash_put_ScaleMode(This,scale)	\
    (This)->lpVtbl -> put_ScaleMode(This,scale)

#define IShockwaveFlash_get_AlignMode(This,align)	\
    (This)->lpVtbl -> get_AlignMode(This,align)

#define IShockwaveFlash_put_AlignMode(This,align)	\
    (This)->lpVtbl -> put_AlignMode(This,align)

#define IShockwaveFlash_get_BackgroundColor(This,color)	\
    (This)->lpVtbl -> get_BackgroundColor(This,color)

#define IShockwaveFlash_put_BackgroundColor(This,color)	\
    (This)->lpVtbl -> put_BackgroundColor(This,color)

#define IShockwaveFlash_get_Loop(This,loop)	\
    (This)->lpVtbl -> get_Loop(This,loop)

#define IShockwaveFlash_put_Loop(This,loop)	\
    (This)->lpVtbl -> put_Loop(This,loop)

#define IShockwaveFlash_get_Movie(This,path)	\
    (This)->lpVtbl -> get_Movie(This,path)

#define IShockwaveFlash_put_Movie(This,path)	\
    (This)->lpVtbl -> put_Movie(This,path)

#define IShockwaveFlash_get_FrameNum(This,framenum)	\
    (This)->lpVtbl -> get_FrameNum(This,framenum)

#define IShockwaveFlash_put_FrameNum(This,framenum)	\
    (This)->lpVtbl -> put_FrameNum(This,framenum)

#define IShockwaveFlash_SetZoomRect(This,left,top,right,bottom)	\
    (This)->lpVtbl -> SetZoomRect(This,left,top,right,bottom)

#define IShockwaveFlash_Zoom(This,factor)	\
    (This)->lpVtbl -> Zoom(This,factor)

#define IShockwaveFlash_Pan(This,x,y,mode)	\
    (This)->lpVtbl -> Pan(This,x,y,mode)

#define IShockwaveFlash_Play(This)	\
    (This)->lpVtbl -> Play(This)

#define IShockwaveFlash_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IShockwaveFlash_Back(This)	\
    (This)->lpVtbl -> Back(This)

#define IShockwaveFlash_Forward(This)	\
    (This)->lpVtbl -> Forward(This)

#define IShockwaveFlash_Rewind(This)	\
    (This)->lpVtbl -> Rewind(This)

#define IShockwaveFlash_StopPlay(This)	\
    (This)->lpVtbl -> StopPlay(This)

#define IShockwaveFlash_GotoFrame(This,frameNum)	\
    (This)->lpVtbl -> GotoFrame(This,frameNum)

#define IShockwaveFlash_CurrentFrame(This,frameNum)	\
    (This)->lpVtbl -> CurrentFrame(This,frameNum)

#define IShockwaveFlash_IsPlaying(This,playing)	\
    (This)->lpVtbl -> IsPlaying(This,playing)

#define IShockwaveFlash_PercentLoaded(This,__MIDL_0016)	\
    (This)->lpVtbl -> PercentLoaded(This,__MIDL_0016)

#define IShockwaveFlash_FrameLoaded(This,frameNum,loaded)	\
    (This)->lpVtbl -> FrameLoaded(This,frameNum,loaded)

#define IShockwaveFlash_FlashVersion(This,version)	\
    (This)->lpVtbl -> FlashVersion(This,version)

#define IShockwaveFlash_get_WMode(This,pVal)	\
    (This)->lpVtbl -> get_WMode(This,pVal)

#define IShockwaveFlash_put_WMode(This,newVal)	\
    (This)->lpVtbl -> put_WMode(This,newVal)

#define IShockwaveFlash_get_SAlign(This,pVal)	\
    (This)->lpVtbl -> get_SAlign(This,pVal)

#define IShockwaveFlash_put_SAlign(This,newVal)	\
    (This)->lpVtbl -> put_SAlign(This,newVal)

#define IShockwaveFlash_get_Menu(This,pVal)	\
    (This)->lpVtbl -> get_Menu(This,pVal)

#define IShockwaveFlash_put_Menu(This,newVal)	\
    (This)->lpVtbl -> put_Menu(This,newVal)

#define IShockwaveFlash_get_Base(This,pVal)	\
    (This)->lpVtbl -> get_Base(This,pVal)

#define IShockwaveFlash_put_Base(This,newVal)	\
    (This)->lpVtbl -> put_Base(This,newVal)

#define IShockwaveFlash_get_Scale(This,pVal)	\
    (This)->lpVtbl -> get_Scale(This,pVal)

#define IShockwaveFlash_put_Scale(This,newVal)	\
    (This)->lpVtbl -> put_Scale(This,newVal)

#define IShockwaveFlash_get_DeviceFont(This,pVal)	\
    (This)->lpVtbl -> get_DeviceFont(This,pVal)

#define IShockwaveFlash_put_DeviceFont(This,newVal)	\
    (This)->lpVtbl -> put_DeviceFont(This,newVal)

#define IShockwaveFlash_get_EmbedMovie(This,pVal)	\
    (This)->lpVtbl -> get_EmbedMovie(This,pVal)

#define IShockwaveFlash_put_EmbedMovie(This,newVal)	\
    (This)->lpVtbl -> put_EmbedMovie(This,newVal)

#define IShockwaveFlash_get_BGColor(This,pVal)	\
    (This)->lpVtbl -> get_BGColor(This,pVal)

#define IShockwaveFlash_put_BGColor(This,newVal)	\
    (This)->lpVtbl -> put_BGColor(This,newVal)

#define IShockwaveFlash_get_Quality2(This,pVal)	\
    (This)->lpVtbl -> get_Quality2(This,pVal)

#define IShockwaveFlash_put_Quality2(This,newVal)	\
    (This)->lpVtbl -> put_Quality2(This,newVal)

#define IShockwaveFlash_LoadMovie(This,layer,url)	\
    (This)->lpVtbl -> LoadMovie(This,layer,url)

#define IShockwaveFlash_TGotoFrame(This,target,frameNum)	\
    (This)->lpVtbl -> TGotoFrame(This,target,frameNum)

#define IShockwaveFlash_TGotoLabel(This,target,label)	\
    (This)->lpVtbl -> TGotoLabel(This,target,label)

#define IShockwaveFlash_TCurrentFrame(This,target,frameNum)	\
    (This)->lpVtbl -> TCurrentFrame(This,target,frameNum)

#define IShockwaveFlash_TCurrentLabel(This,target,pVal)	\
    (This)->lpVtbl -> TCurrentLabel(This,target,pVal)

#define IShockwaveFlash_TPlay(This,target)	\
    (This)->lpVtbl -> TPlay(This,target)

#define IShockwaveFlash_TStopPlay(This,target)	\
    (This)->lpVtbl -> TStopPlay(This,target)

#define IShockwaveFlash_SetVariable(This,name,value)	\
    (This)->lpVtbl -> SetVariable(This,name,value)

#define IShockwaveFlash_GetVariable(This,name,pVal)	\
    (This)->lpVtbl -> GetVariable(This,name,pVal)

#define IShockwaveFlash_TSetProperty(This,target,property,value)	\
    (This)->lpVtbl -> TSetProperty(This,target,property,value)

#define IShockwaveFlash_TGetProperty(This,target,property,pVal)	\
    (This)->lpVtbl -> TGetProperty(This,target,property,pVal)

#define IShockwaveFlash_TCallFrame(This,target,frameNum)	\
    (This)->lpVtbl -> TCallFrame(This,target,frameNum)

#define IShockwaveFlash_TCallLabel(This,target,label)	\
    (This)->lpVtbl -> TCallLabel(This,target,label)

#define IShockwaveFlash_TSetPropertyNum(This,target,property,value)	\
    (This)->lpVtbl -> TSetPropertyNum(This,target,property,value)

#define IShockwaveFlash_TGetPropertyNum(This,target,property,pVal)	\
    (This)->lpVtbl -> TGetPropertyNum(This,target,property,pVal)

#define IShockwaveFlash_get_SWRemote(This,pVal)	\
    (This)->lpVtbl -> get_SWRemote(This,pVal)

#define IShockwaveFlash_put_SWRemote(This,newVal)	\
    (This)->lpVtbl -> put_SWRemote(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_get_ReadyState_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *thestate);


void __RPC_STUB IShockwaveFlash_get_ReadyState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_get_TotalFrames_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *numframes);


void __RPC_STUB IShockwaveFlash_get_TotalFrames_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_get_Playing_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *playing);


void __RPC_STUB IShockwaveFlash_get_Playing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_put_Playing_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL playing);


void __RPC_STUB IShockwaveFlash_put_Playing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_get_Quality_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *quality);


void __RPC_STUB IShockwaveFlash_get_Quality_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_put_Quality_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [in] */ int quality);


void __RPC_STUB IShockwaveFlash_put_Quality_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_get_ScaleMode_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *scale);


void __RPC_STUB IShockwaveFlash_get_ScaleMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_put_ScaleMode_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [in] */ int scale);


void __RPC_STUB IShockwaveFlash_put_ScaleMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_get_AlignMode_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *align);


void __RPC_STUB IShockwaveFlash_get_AlignMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_put_AlignMode_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [in] */ int align);


void __RPC_STUB IShockwaveFlash_put_AlignMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_get_BackgroundColor_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *color);


void __RPC_STUB IShockwaveFlash_get_BackgroundColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_put_BackgroundColor_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [in] */ long color);


void __RPC_STUB IShockwaveFlash_put_BackgroundColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_get_Loop_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *loop);


void __RPC_STUB IShockwaveFlash_get_Loop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_put_Loop_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL loop);


void __RPC_STUB IShockwaveFlash_put_Loop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_get_Movie_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *path);


void __RPC_STUB IShockwaveFlash_get_Movie_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_put_Movie_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [in] */ BSTR path);


void __RPC_STUB IShockwaveFlash_put_Movie_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_get_FrameNum_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *framenum);


void __RPC_STUB IShockwaveFlash_get_FrameNum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_put_FrameNum_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [in] */ long framenum);


void __RPC_STUB IShockwaveFlash_put_FrameNum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_SetZoomRect_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [in] */ long left,
    /* [in] */ long top,
    /* [in] */ long right,
    /* [in] */ long bottom);


void __RPC_STUB IShockwaveFlash_SetZoomRect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_Zoom_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [in] */ int factor);


void __RPC_STUB IShockwaveFlash_Zoom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_Pan_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [in] */ long x,
    /* [in] */ long y,
    /* [in] */ int mode);


void __RPC_STUB IShockwaveFlash_Pan_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_Play_Proxy( 
    IShockwaveFlash __RPC_FAR * This);


void __RPC_STUB IShockwaveFlash_Play_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_Stop_Proxy( 
    IShockwaveFlash __RPC_FAR * This);


void __RPC_STUB IShockwaveFlash_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_Back_Proxy( 
    IShockwaveFlash __RPC_FAR * This);


void __RPC_STUB IShockwaveFlash_Back_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_Forward_Proxy( 
    IShockwaveFlash __RPC_FAR * This);


void __RPC_STUB IShockwaveFlash_Forward_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_Rewind_Proxy( 
    IShockwaveFlash __RPC_FAR * This);


void __RPC_STUB IShockwaveFlash_Rewind_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_StopPlay_Proxy( 
    IShockwaveFlash __RPC_FAR * This);


void __RPC_STUB IShockwaveFlash_StopPlay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_GotoFrame_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [in] */ long frameNum);


void __RPC_STUB IShockwaveFlash_GotoFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_CurrentFrame_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *frameNum);


void __RPC_STUB IShockwaveFlash_CurrentFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_IsPlaying_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *playing);


void __RPC_STUB IShockwaveFlash_IsPlaying_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_PercentLoaded_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *__MIDL_0016);


void __RPC_STUB IShockwaveFlash_PercentLoaded_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_FrameLoaded_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [in] */ long frameNum,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *loaded);


void __RPC_STUB IShockwaveFlash_FrameLoaded_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_FlashVersion_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *version);


void __RPC_STUB IShockwaveFlash_FlashVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_get_WMode_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IShockwaveFlash_get_WMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_put_WMode_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IShockwaveFlash_put_WMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_get_SAlign_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IShockwaveFlash_get_SAlign_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_put_SAlign_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IShockwaveFlash_put_SAlign_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_get_Menu_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IShockwaveFlash_get_Menu_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_put_Menu_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IShockwaveFlash_put_Menu_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_get_Base_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IShockwaveFlash_get_Base_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_put_Base_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IShockwaveFlash_put_Base_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_get_Scale_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IShockwaveFlash_get_Scale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_put_Scale_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IShockwaveFlash_put_Scale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_get_DeviceFont_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IShockwaveFlash_get_DeviceFont_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_put_DeviceFont_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IShockwaveFlash_put_DeviceFont_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_get_EmbedMovie_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IShockwaveFlash_get_EmbedMovie_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_put_EmbedMovie_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IShockwaveFlash_put_EmbedMovie_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_get_BGColor_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IShockwaveFlash_get_BGColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_put_BGColor_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IShockwaveFlash_put_BGColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_get_Quality2_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IShockwaveFlash_get_Quality2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_put_Quality2_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IShockwaveFlash_put_Quality2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_LoadMovie_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [in] */ int layer,
    /* [in] */ BSTR url);


void __RPC_STUB IShockwaveFlash_LoadMovie_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_TGotoFrame_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [in] */ BSTR target,
    /* [in] */ long frameNum);


void __RPC_STUB IShockwaveFlash_TGotoFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_TGotoLabel_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [in] */ BSTR target,
    /* [in] */ BSTR label);


void __RPC_STUB IShockwaveFlash_TGotoLabel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_TCurrentFrame_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [in] */ BSTR target,
    /* [retval][out] */ long __RPC_FAR *frameNum);


void __RPC_STUB IShockwaveFlash_TCurrentFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_TCurrentLabel_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [in] */ BSTR target,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IShockwaveFlash_TCurrentLabel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_TPlay_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [in] */ BSTR target);


void __RPC_STUB IShockwaveFlash_TPlay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_TStopPlay_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [in] */ BSTR target);


void __RPC_STUB IShockwaveFlash_TStopPlay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_SetVariable_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [in] */ BSTR value);


void __RPC_STUB IShockwaveFlash_SetVariable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_GetVariable_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IShockwaveFlash_GetVariable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_TSetProperty_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [in] */ BSTR target,
    /* [in] */ int property,
    /* [in] */ BSTR value);


void __RPC_STUB IShockwaveFlash_TSetProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_TGetProperty_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [in] */ BSTR target,
    /* [in] */ int property,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IShockwaveFlash_TGetProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_TCallFrame_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [in] */ BSTR target,
    /* [in] */ int frameNum);


void __RPC_STUB IShockwaveFlash_TCallFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_TCallLabel_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [in] */ BSTR target,
    /* [in] */ BSTR label);


void __RPC_STUB IShockwaveFlash_TCallLabel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_TSetPropertyNum_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [in] */ BSTR target,
    /* [in] */ int property,
    /* [in] */ double value);


void __RPC_STUB IShockwaveFlash_TSetPropertyNum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_TGetPropertyNum_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [in] */ BSTR target,
    /* [in] */ int property,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IShockwaveFlash_TGetPropertyNum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_get_SWRemote_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IShockwaveFlash_get_SWRemote_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IShockwaveFlash_put_SWRemote_Proxy( 
    IShockwaveFlash __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IShockwaveFlash_put_SWRemote_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IShockwaveFlash_INTERFACE_DEFINED__ */


#ifndef __DShockwaveFlashEvents_DISPINTERFACE_DEFINED__
#define __DShockwaveFlashEvents_DISPINTERFACE_DEFINED__

/* dispinterface DShockwaveFlashEvents */
/* [hidden][helpstring][uuid] */ 


EXTERN_C const IID DIID_DShockwaveFlashEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("D27CDB6D-AE6D-11cf-96B8-444553540000")
    DShockwaveFlashEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct DShockwaveFlashEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            DShockwaveFlashEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            DShockwaveFlashEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            DShockwaveFlashEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            DShockwaveFlashEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            DShockwaveFlashEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            DShockwaveFlashEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            DShockwaveFlashEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } DShockwaveFlashEventsVtbl;

    interface DShockwaveFlashEvents
    {
        CONST_VTBL struct DShockwaveFlashEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define DShockwaveFlashEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define DShockwaveFlashEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define DShockwaveFlashEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define DShockwaveFlashEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define DShockwaveFlashEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define DShockwaveFlashEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define DShockwaveFlashEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __DShockwaveFlashEvents_DISPINTERFACE_DEFINED__ */


#ifndef __IDCFlashPlayer_INTERFACE_DEFINED__
#define __IDCFlashPlayer_INTERFACE_DEFINED__

/* interface IDCFlashPlayer */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IDCFlashPlayer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3526D8A5-6FAF-11D3-B31A-00105A29E72B")
    IDCFlashPlayer : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetDirectSound( 
            /* [in] */ IUnknown __RPC_FAR *pDS) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE MouseDown( 
            /* [in] */ int x,
            /* [in] */ int y) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE MouseMove( 
            /* [in] */ int x,
            /* [in] */ int y) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE MouseUp( 
            /* [in] */ int x,
            /* [in] */ int y) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Idle( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDCFlashPlayerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDCFlashPlayer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDCFlashPlayer __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDCFlashPlayer __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IDCFlashPlayer __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IDCFlashPlayer __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IDCFlashPlayer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IDCFlashPlayer __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetDirectSound )( 
            IDCFlashPlayer __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pDS);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MouseDown )( 
            IDCFlashPlayer __RPC_FAR * This,
            /* [in] */ int x,
            /* [in] */ int y);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MouseMove )( 
            IDCFlashPlayer __RPC_FAR * This,
            /* [in] */ int x,
            /* [in] */ int y);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MouseUp )( 
            IDCFlashPlayer __RPC_FAR * This,
            /* [in] */ int x,
            /* [in] */ int y);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Idle )( 
            IDCFlashPlayer __RPC_FAR * This);
        
        END_INTERFACE
    } IDCFlashPlayerVtbl;

    interface IDCFlashPlayer
    {
        CONST_VTBL struct IDCFlashPlayerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDCFlashPlayer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDCFlashPlayer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDCFlashPlayer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDCFlashPlayer_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDCFlashPlayer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDCFlashPlayer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDCFlashPlayer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDCFlashPlayer_SetDirectSound(This,pDS)	\
    (This)->lpVtbl -> SetDirectSound(This,pDS)

#define IDCFlashPlayer_MouseDown(This,x,y)	\
    (This)->lpVtbl -> MouseDown(This,x,y)

#define IDCFlashPlayer_MouseMove(This,x,y)	\
    (This)->lpVtbl -> MouseMove(This,x,y)

#define IDCFlashPlayer_MouseUp(This,x,y)	\
    (This)->lpVtbl -> MouseUp(This,x,y)

#define IDCFlashPlayer_Idle(This)	\
    (This)->lpVtbl -> Idle(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id] */ HRESULT STDMETHODCALLTYPE IDCFlashPlayer_SetDirectSound_Proxy( 
    IDCFlashPlayer __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pDS);


void __RPC_STUB IDCFlashPlayer_SetDirectSound_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IDCFlashPlayer_MouseDown_Proxy( 
    IDCFlashPlayer __RPC_FAR * This,
    /* [in] */ int x,
    /* [in] */ int y);


void __RPC_STUB IDCFlashPlayer_MouseDown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IDCFlashPlayer_MouseMove_Proxy( 
    IDCFlashPlayer __RPC_FAR * This,
    /* [in] */ int x,
    /* [in] */ int y);


void __RPC_STUB IDCFlashPlayer_MouseMove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IDCFlashPlayer_MouseUp_Proxy( 
    IDCFlashPlayer __RPC_FAR * This,
    /* [in] */ int x,
    /* [in] */ int y);


void __RPC_STUB IDCFlashPlayer_MouseUp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IDCFlashPlayer_Idle_Proxy( 
    IDCFlashPlayer __RPC_FAR * This);


void __RPC_STUB IDCFlashPlayer_Idle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDCFlashPlayer_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ShockwaveFlash;

#ifdef __cplusplus

class DECLSPEC_UUID("D27CDB6E-AE6D-11cf-96B8-444553540000")
ShockwaveFlash;
#endif

EXTERN_C const CLSID CLSID_FlashProp;

#ifdef __cplusplus

class DECLSPEC_UUID("1171A62F-05D2-11D1-83FC-00A0C9089C5A")
FlashProp;
#endif

EXTERN_C const CLSID CLSID_DCFlashPlayer;

#ifdef __cplusplus

class DECLSPEC_UUID("3526D8A6-6FAF-11D3-B31A-00105A29E72B")
DCFlashPlayer;
#endif
#endif /* __ShockwaveFlashObjects_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
