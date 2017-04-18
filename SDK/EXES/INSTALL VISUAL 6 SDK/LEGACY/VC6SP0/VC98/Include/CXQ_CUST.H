/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Tue Sep 09 20:17:54 1997
 */
/* Compiler settings for cxq_cust.idl:
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

#ifndef __cxq_cust_h__
#define __cxq_cust_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IH26XVideoEffects_FWD_DEFINED__
#define __IH26XVideoEffects_FWD_DEFINED__
typedef interface IH26XVideoEffects IH26XVideoEffects;
#endif 	/* __IH26XVideoEffects_FWD_DEFINED__ */


#ifndef __IH26XEncodeOptions_FWD_DEFINED__
#define __IH26XEncodeOptions_FWD_DEFINED__
typedef interface IH26XEncodeOptions IH26XEncodeOptions;
#endif 	/* __IH26XEncodeOptions_FWD_DEFINED__ */


#ifndef __IH26XSnapshot_FWD_DEFINED__
#define __IH26XSnapshot_FWD_DEFINED__
typedef interface IH26XSnapshot IH26XSnapshot;
#endif 	/* __IH26XSnapshot_FWD_DEFINED__ */


#ifndef __IH26XEncoderControl_FWD_DEFINED__
#define __IH26XEncoderControl_FWD_DEFINED__
typedef interface IH26XEncoderControl IH26XEncoderControl;
#endif 	/* __IH26XEncoderControl_FWD_DEFINED__ */


#ifndef __IH26XRTPControl_FWD_DEFINED__
#define __IH26XRTPControl_FWD_DEFINED__
typedef interface IH26XRTPControl IH26XRTPControl;
#endif 	/* __IH26XRTPControl_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IH26XVideoEffects_INTERFACE_DEFINED__
#define __IH26XVideoEffects_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IH26XVideoEffects
 * at Tue Sep 09 20:17:54 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][uuid] */ 


// STRUCTURES
typedef /* [public][public][public][public][public][public] */ 
enum __MIDL_IH26XVideoEffects_0001
    {	H26X_VE_UNDEFINED	= 0,
	H26X_VE_BRIGHTNESS	= H26X_VE_UNDEFINED + 1,
	H26X_VE_CONTRAST	= H26X_VE_BRIGHTNESS + 1,
	H26X_VE_SATURATION	= H26X_VE_CONTRAST + 1,
	H26X_VE_TINT	= H26X_VE_SATURATION + 1,
	H26X_VE_MIRROR	= H26X_VE_TINT + 1,
	H26X_VE_ASPECT_CORRECT	= H26X_VE_MIRROR + 1
    }	H26X_VIDEO_EFFECT;

typedef /* [public] */ struct  __MIDL_IH26XVideoEffects_0002
    {
    int iBrightness;
    int iSaturation;
    int iContrast;
    int iMirror;
    int iAspectCorrect;
    }	VIDEO_EFFECT_VALUES;

typedef struct __MIDL_IH26XVideoEffects_0002 __RPC_FAR *PTR_VIDEO_EFFECT_VALUES;

// METHODS

EXTERN_C const IID IID_IH26XVideoEffects;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("21555140-9C2B-11cf-90FA-00AA00A729EA")
    IH26XVideoEffects : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE getFactoryDefault( 
            /* [in] */ H26X_VIDEO_EFFECT veVideoEffect,
            /* [out] */ int __RPC_FAR *pinDefault) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE getFactoryLimits( 
            /* [in] */ H26X_VIDEO_EFFECT veVideoEffect,
            /* [out] */ int __RPC_FAR *pinLower,
            /* [out] */ int __RPC_FAR *pinUpper) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE getCurrent( 
            /* [in] */ H26X_VIDEO_EFFECT veVideoEffect,
            /* [out] */ int __RPC_FAR *pinValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE setCurrent( 
            /* [in] */ H26X_VIDEO_EFFECT veVideoEffect,
            /* [in] */ int inValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE resetCurrent( 
            /* [in] */ H26X_VIDEO_EFFECT veVideoEffect) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IH26XVideoEffectsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IH26XVideoEffects __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IH26XVideoEffects __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IH26XVideoEffects __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getFactoryDefault )( 
            IH26XVideoEffects __RPC_FAR * This,
            /* [in] */ H26X_VIDEO_EFFECT veVideoEffect,
            /* [out] */ int __RPC_FAR *pinDefault);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getFactoryLimits )( 
            IH26XVideoEffects __RPC_FAR * This,
            /* [in] */ H26X_VIDEO_EFFECT veVideoEffect,
            /* [out] */ int __RPC_FAR *pinLower,
            /* [out] */ int __RPC_FAR *pinUpper);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getCurrent )( 
            IH26XVideoEffects __RPC_FAR * This,
            /* [in] */ H26X_VIDEO_EFFECT veVideoEffect,
            /* [out] */ int __RPC_FAR *pinValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setCurrent )( 
            IH26XVideoEffects __RPC_FAR * This,
            /* [in] */ H26X_VIDEO_EFFECT veVideoEffect,
            /* [in] */ int inValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *resetCurrent )( 
            IH26XVideoEffects __RPC_FAR * This,
            /* [in] */ H26X_VIDEO_EFFECT veVideoEffect);
        
        END_INTERFACE
    } IH26XVideoEffectsVtbl;

    interface IH26XVideoEffects
    {
        CONST_VTBL struct IH26XVideoEffectsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IH26XVideoEffects_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IH26XVideoEffects_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IH26XVideoEffects_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IH26XVideoEffects_getFactoryDefault(This,veVideoEffect,pinDefault)	\
    (This)->lpVtbl -> getFactoryDefault(This,veVideoEffect,pinDefault)

#define IH26XVideoEffects_getFactoryLimits(This,veVideoEffect,pinLower,pinUpper)	\
    (This)->lpVtbl -> getFactoryLimits(This,veVideoEffect,pinLower,pinUpper)

#define IH26XVideoEffects_getCurrent(This,veVideoEffect,pinValue)	\
    (This)->lpVtbl -> getCurrent(This,veVideoEffect,pinValue)

#define IH26XVideoEffects_setCurrent(This,veVideoEffect,inValue)	\
    (This)->lpVtbl -> setCurrent(This,veVideoEffect,inValue)

#define IH26XVideoEffects_resetCurrent(This,veVideoEffect)	\
    (This)->lpVtbl -> resetCurrent(This,veVideoEffect)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IH26XVideoEffects_getFactoryDefault_Proxy( 
    IH26XVideoEffects __RPC_FAR * This,
    /* [in] */ H26X_VIDEO_EFFECT veVideoEffect,
    /* [out] */ int __RPC_FAR *pinDefault);


void __RPC_STUB IH26XVideoEffects_getFactoryDefault_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IH26XVideoEffects_getFactoryLimits_Proxy( 
    IH26XVideoEffects __RPC_FAR * This,
    /* [in] */ H26X_VIDEO_EFFECT veVideoEffect,
    /* [out] */ int __RPC_FAR *pinLower,
    /* [out] */ int __RPC_FAR *pinUpper);


void __RPC_STUB IH26XVideoEffects_getFactoryLimits_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IH26XVideoEffects_getCurrent_Proxy( 
    IH26XVideoEffects __RPC_FAR * This,
    /* [in] */ H26X_VIDEO_EFFECT veVideoEffect,
    /* [out] */ int __RPC_FAR *pinValue);


void __RPC_STUB IH26XVideoEffects_getCurrent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IH26XVideoEffects_setCurrent_Proxy( 
    IH26XVideoEffects __RPC_FAR * This,
    /* [in] */ H26X_VIDEO_EFFECT veVideoEffect,
    /* [in] */ int inValue);


void __RPC_STUB IH26XVideoEffects_setCurrent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IH26XVideoEffects_resetCurrent_Proxy( 
    IH26XVideoEffects __RPC_FAR * This,
    /* [in] */ H26X_VIDEO_EFFECT veVideoEffect);


void __RPC_STUB IH26XVideoEffects_resetCurrent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IH26XVideoEffects_INTERFACE_DEFINED__ */


#ifndef __IH26XEncodeOptions_INTERFACE_DEFINED__
#define __IH26XEncodeOptions_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IH26XEncodeOptions
 * at Tue Sep 09 20:17:54 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][uuid] */ 


// STRUCTURES
typedef /* [public] */ struct  __MIDL_IH26XEncodeOptions_0001
    {
    int bExtendedMV;
    int bPBFrames;
    int bAdvPrediction;
    }	ENCODE_OPTIONS_VALUES;

typedef struct __MIDL_IH26XEncodeOptions_0001 __RPC_FAR *PTR_ENCODE_OPTIONS_VALUES;

// METHODS

EXTERN_C const IID IID_IH26XEncodeOptions;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("65698D40-282D-11d0-8800-444553540000")
    IH26XEncodeOptions : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE get_EncodeOptions( 
            /* [out] */ PTR_ENCODE_OPTIONS_VALUES pOptionValues) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_EncodeOptionsDefault( 
            /* [out] */ PTR_ENCODE_OPTIONS_VALUES pOptionValues) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE set_EncodeOptions( 
            /* [in] */ PTR_ENCODE_OPTIONS_VALUES pOptionValues) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IH26XEncodeOptionsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IH26XEncodeOptions __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IH26XEncodeOptions __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IH26XEncodeOptions __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EncodeOptions )( 
            IH26XEncodeOptions __RPC_FAR * This,
            /* [out] */ PTR_ENCODE_OPTIONS_VALUES pOptionValues);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EncodeOptionsDefault )( 
            IH26XEncodeOptions __RPC_FAR * This,
            /* [out] */ PTR_ENCODE_OPTIONS_VALUES pOptionValues);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *set_EncodeOptions )( 
            IH26XEncodeOptions __RPC_FAR * This,
            /* [in] */ PTR_ENCODE_OPTIONS_VALUES pOptionValues);
        
        END_INTERFACE
    } IH26XEncodeOptionsVtbl;

    interface IH26XEncodeOptions
    {
        CONST_VTBL struct IH26XEncodeOptionsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IH26XEncodeOptions_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IH26XEncodeOptions_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IH26XEncodeOptions_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IH26XEncodeOptions_get_EncodeOptions(This,pOptionValues)	\
    (This)->lpVtbl -> get_EncodeOptions(This,pOptionValues)

#define IH26XEncodeOptions_get_EncodeOptionsDefault(This,pOptionValues)	\
    (This)->lpVtbl -> get_EncodeOptionsDefault(This,pOptionValues)

#define IH26XEncodeOptions_set_EncodeOptions(This,pOptionValues)	\
    (This)->lpVtbl -> set_EncodeOptions(This,pOptionValues)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IH26XEncodeOptions_get_EncodeOptions_Proxy( 
    IH26XEncodeOptions __RPC_FAR * This,
    /* [out] */ PTR_ENCODE_OPTIONS_VALUES pOptionValues);


void __RPC_STUB IH26XEncodeOptions_get_EncodeOptions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IH26XEncodeOptions_get_EncodeOptionsDefault_Proxy( 
    IH26XEncodeOptions __RPC_FAR * This,
    /* [out] */ PTR_ENCODE_OPTIONS_VALUES pOptionValues);


void __RPC_STUB IH26XEncodeOptions_get_EncodeOptionsDefault_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IH26XEncodeOptions_set_EncodeOptions_Proxy( 
    IH26XEncodeOptions __RPC_FAR * This,
    /* [in] */ PTR_ENCODE_OPTIONS_VALUES pOptionValues);


void __RPC_STUB IH26XEncodeOptions_set_EncodeOptions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IH26XEncodeOptions_INTERFACE_DEFINED__ */


#ifndef __IH26XSnapshot_INTERFACE_DEFINED__
#define __IH26XSnapshot_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IH26XSnapshot
 * at Tue Sep 09 20:17:54 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][uuid] */ 


#ifndef _WINGDI_
// STRUCTURES
typedef struct  __MIDL_IH26XSnapshot_0001
    {
    DWORD biSize;
    LONG biWidth;
    LONG biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG biXPelsPerMeter;
    LONG biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
    }	__RPC_FAR *LPBITMAPINFOHEADER;

#endif
// METHODS

EXTERN_C const IID IID_IH26XSnapshot;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3CB194A0-10AA-11d0-8800-444553540000")
    IH26XSnapshot : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE getBitmapInfoHeader( 
            /* [out] */ LPBITMAPINFOHEADER lpBmi) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE getSnapshot( 
            /* [in] */ LPBITMAPINFOHEADER lpBmi,
            /* [out] */ unsigned char __RPC_FAR *pvBuffer,
            /* [in] */ DWORD dwTimeout) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IH26XSnapshotVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IH26XSnapshot __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IH26XSnapshot __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IH26XSnapshot __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getBitmapInfoHeader )( 
            IH26XSnapshot __RPC_FAR * This,
            /* [out] */ LPBITMAPINFOHEADER lpBmi);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getSnapshot )( 
            IH26XSnapshot __RPC_FAR * This,
            /* [in] */ LPBITMAPINFOHEADER lpBmi,
            /* [out] */ unsigned char __RPC_FAR *pvBuffer,
            /* [in] */ DWORD dwTimeout);
        
        END_INTERFACE
    } IH26XSnapshotVtbl;

    interface IH26XSnapshot
    {
        CONST_VTBL struct IH26XSnapshotVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IH26XSnapshot_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IH26XSnapshot_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IH26XSnapshot_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IH26XSnapshot_getBitmapInfoHeader(This,lpBmi)	\
    (This)->lpVtbl -> getBitmapInfoHeader(This,lpBmi)

#define IH26XSnapshot_getSnapshot(This,lpBmi,pvBuffer,dwTimeout)	\
    (This)->lpVtbl -> getSnapshot(This,lpBmi,pvBuffer,dwTimeout)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IH26XSnapshot_getBitmapInfoHeader_Proxy( 
    IH26XSnapshot __RPC_FAR * This,
    /* [out] */ LPBITMAPINFOHEADER lpBmi);


void __RPC_STUB IH26XSnapshot_getBitmapInfoHeader_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IH26XSnapshot_getSnapshot_Proxy( 
    IH26XSnapshot __RPC_FAR * This,
    /* [in] */ LPBITMAPINFOHEADER lpBmi,
    /* [out] */ unsigned char __RPC_FAR *pvBuffer,
    /* [in] */ DWORD dwTimeout);


void __RPC_STUB IH26XSnapshot_getSnapshot_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IH26XSnapshot_INTERFACE_DEFINED__ */


#ifndef __IH26XEncoderControl_INTERFACE_DEFINED__
#define __IH26XEncoderControl_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IH26XEncoderControl
 * at Tue Sep 09 20:17:54 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][uuid] */ 


// STRUCTURES
typedef /* [public] */ struct  __MIDL_IH26XEncoderControl_0001
    {
    DWORD dwTargetFrameSize;
    BOOL bFrameSizeBRC;
    BOOL bSendKey;
    DWORD dwQuality;
    DWORD dwFrameRate;
    DWORD dwDataRate;
    DWORD dwScale;
    DWORD dwWidth;
    DWORD dwKeyFrameInterval;
    }	ENC_CMP_DATA;

typedef struct __MIDL_IH26XEncoderControl_0001 __RPC_FAR *PTR_ENC_CMP_DATA;

// METHODS

EXTERN_C const IID IID_IH26XEncoderControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F9B78AA1-EA12-11cf-9FEC-00AA00A59F69")
    IH26XEncoderControl : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE get_EncodeCompression( 
            /* [out] */ PTR_ENC_CMP_DATA pData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_EncodeCompressionDefault( 
            /* [out] */ PTR_ENC_CMP_DATA pData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE set_EncodeCompression( 
            /* [in] */ PTR_ENC_CMP_DATA pData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IH26XEncoderControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IH26XEncoderControl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IH26XEncoderControl __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IH26XEncoderControl __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EncodeCompression )( 
            IH26XEncoderControl __RPC_FAR * This,
            /* [out] */ PTR_ENC_CMP_DATA pData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EncodeCompressionDefault )( 
            IH26XEncoderControl __RPC_FAR * This,
            /* [out] */ PTR_ENC_CMP_DATA pData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *set_EncodeCompression )( 
            IH26XEncoderControl __RPC_FAR * This,
            /* [in] */ PTR_ENC_CMP_DATA pData);
        
        END_INTERFACE
    } IH26XEncoderControlVtbl;

    interface IH26XEncoderControl
    {
        CONST_VTBL struct IH26XEncoderControlVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IH26XEncoderControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IH26XEncoderControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IH26XEncoderControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IH26XEncoderControl_get_EncodeCompression(This,pData)	\
    (This)->lpVtbl -> get_EncodeCompression(This,pData)

#define IH26XEncoderControl_get_EncodeCompressionDefault(This,pData)	\
    (This)->lpVtbl -> get_EncodeCompressionDefault(This,pData)

#define IH26XEncoderControl_set_EncodeCompression(This,pData)	\
    (This)->lpVtbl -> set_EncodeCompression(This,pData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IH26XEncoderControl_get_EncodeCompression_Proxy( 
    IH26XEncoderControl __RPC_FAR * This,
    /* [out] */ PTR_ENC_CMP_DATA pData);


void __RPC_STUB IH26XEncoderControl_get_EncodeCompression_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IH26XEncoderControl_get_EncodeCompressionDefault_Proxy( 
    IH26XEncoderControl __RPC_FAR * This,
    /* [out] */ PTR_ENC_CMP_DATA pData);


void __RPC_STUB IH26XEncoderControl_get_EncodeCompressionDefault_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IH26XEncoderControl_set_EncodeCompression_Proxy( 
    IH26XEncoderControl __RPC_FAR * This,
    /* [in] */ PTR_ENC_CMP_DATA pData);


void __RPC_STUB IH26XEncoderControl_set_EncodeCompression_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IH26XEncoderControl_INTERFACE_DEFINED__ */


#ifndef __IH26XRTPControl_INTERFACE_DEFINED__
#define __IH26XRTPControl_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IH26XRTPControl
 * at Tue Sep 09 20:17:54 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][uuid] */ 


// STRUCTURES
typedef /* [public] */ struct  __MIDL_IH26XRTPControl_0001
    {
    BOOL bRTPHeader;
    DWORD dwPacketSize;
    DWORD dwPacketLoss;
    }	ENC_RTP_DATA;

typedef struct __MIDL_IH26XRTPControl_0001 __RPC_FAR *PTR_ENC_RTP_DATA;

// METHODS

EXTERN_C const IID IID_IH26XRTPControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1FC3F2C0-2BFD-11d0-8800-444553540000")
    IH26XRTPControl : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE get_RTPCompression( 
            /* [out] */ PTR_ENC_RTP_DATA pData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_RTPCompressionDefault( 
            /* [out] */ PTR_ENC_RTP_DATA pData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE set_RTPCompression( 
            /* [in] */ PTR_ENC_RTP_DATA pData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IH26XRTPControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IH26XRTPControl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IH26XRTPControl __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IH26XRTPControl __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RTPCompression )( 
            IH26XRTPControl __RPC_FAR * This,
            /* [out] */ PTR_ENC_RTP_DATA pData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RTPCompressionDefault )( 
            IH26XRTPControl __RPC_FAR * This,
            /* [out] */ PTR_ENC_RTP_DATA pData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *set_RTPCompression )( 
            IH26XRTPControl __RPC_FAR * This,
            /* [in] */ PTR_ENC_RTP_DATA pData);
        
        END_INTERFACE
    } IH26XRTPControlVtbl;

    interface IH26XRTPControl
    {
        CONST_VTBL struct IH26XRTPControlVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IH26XRTPControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IH26XRTPControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IH26XRTPControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IH26XRTPControl_get_RTPCompression(This,pData)	\
    (This)->lpVtbl -> get_RTPCompression(This,pData)

#define IH26XRTPControl_get_RTPCompressionDefault(This,pData)	\
    (This)->lpVtbl -> get_RTPCompressionDefault(This,pData)

#define IH26XRTPControl_set_RTPCompression(This,pData)	\
    (This)->lpVtbl -> set_RTPCompression(This,pData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IH26XRTPControl_get_RTPCompression_Proxy( 
    IH26XRTPControl __RPC_FAR * This,
    /* [out] */ PTR_ENC_RTP_DATA pData);


void __RPC_STUB IH26XRTPControl_get_RTPCompression_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IH26XRTPControl_get_RTPCompressionDefault_Proxy( 
    IH26XRTPControl __RPC_FAR * This,
    /* [out] */ PTR_ENC_RTP_DATA pData);


void __RPC_STUB IH26XRTPControl_get_RTPCompressionDefault_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IH26XRTPControl_set_RTPCompression_Proxy( 
    IH26XRTPControl __RPC_FAR * This,
    /* [in] */ PTR_ENC_RTP_DATA pData);


void __RPC_STUB IH26XRTPControl_set_RTPCompression_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IH26XRTPControl_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
