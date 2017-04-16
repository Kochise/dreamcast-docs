/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.02.88 */
/* at Tue Nov 11 05:16:35 1997
 */
/* Compiler settings for ..\danim.idl:
    Oicf (OptLev=i2), W0, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )

#ifndef __danim_h__
#define __danim_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IDAViewSite_FWD_DEFINED__
#define __IDAViewSite_FWD_DEFINED__
typedef interface IDAViewSite IDAViewSite;
#endif 	/* __IDAViewSite_FWD_DEFINED__ */


#ifndef __IDAView_FWD_DEFINED__
#define __IDAView_FWD_DEFINED__
typedef interface IDAView IDAView;
#endif 	/* __IDAView_FWD_DEFINED__ */


#ifndef __IDABehavior_FWD_DEFINED__
#define __IDABehavior_FWD_DEFINED__
typedef interface IDABehavior IDABehavior;
#endif 	/* __IDABehavior_FWD_DEFINED__ */


#ifndef __IDANumber_FWD_DEFINED__
#define __IDANumber_FWD_DEFINED__
typedef interface IDANumber IDANumber;
#endif 	/* __IDANumber_FWD_DEFINED__ */


#ifndef __IDABvrHook_FWD_DEFINED__
#define __IDABvrHook_FWD_DEFINED__
typedef interface IDABvrHook IDABvrHook;
#endif 	/* __IDABvrHook_FWD_DEFINED__ */


#ifndef __IDADrawingSurface_FWD_DEFINED__
#define __IDADrawingSurface_FWD_DEFINED__
typedef interface IDADrawingSurface IDADrawingSurface;
#endif 	/* __IDADrawingSurface_FWD_DEFINED__ */


#ifndef __IDAPickableResult_FWD_DEFINED__
#define __IDAPickableResult_FWD_DEFINED__
typedef interface IDAPickableResult IDAPickableResult;
#endif 	/* __IDAPickableResult_FWD_DEFINED__ */


#ifndef __DABehavior_FWD_DEFINED__
#define __DABehavior_FWD_DEFINED__

#ifdef __cplusplus
typedef class DABehavior DABehavior;
#else
typedef struct DABehavior DABehavior;
#endif /* __cplusplus */

#endif 	/* __DABehavior_FWD_DEFINED__ */


#ifndef __IDAUntilNotifier_FWD_DEFINED__
#define __IDAUntilNotifier_FWD_DEFINED__
typedef interface IDAUntilNotifier IDAUntilNotifier;
#endif 	/* __IDAUntilNotifier_FWD_DEFINED__ */


#ifndef __IDABoolean_FWD_DEFINED__
#define __IDABoolean_FWD_DEFINED__
typedef interface IDABoolean IDABoolean;
#endif 	/* __IDABoolean_FWD_DEFINED__ */


#ifndef __IDACamera_FWD_DEFINED__
#define __IDACamera_FWD_DEFINED__
typedef interface IDACamera IDACamera;
#endif 	/* __IDACamera_FWD_DEFINED__ */


#ifndef __IDAColor_FWD_DEFINED__
#define __IDAColor_FWD_DEFINED__
typedef interface IDAColor IDAColor;
#endif 	/* __IDAColor_FWD_DEFINED__ */


#ifndef __IDAGeometry_FWD_DEFINED__
#define __IDAGeometry_FWD_DEFINED__
typedef interface IDAGeometry IDAGeometry;
#endif 	/* __IDAGeometry_FWD_DEFINED__ */


#ifndef __IDAImage_FWD_DEFINED__
#define __IDAImage_FWD_DEFINED__
typedef interface IDAImage IDAImage;
#endif 	/* __IDAImage_FWD_DEFINED__ */


#ifndef __IDAMatte_FWD_DEFINED__
#define __IDAMatte_FWD_DEFINED__
typedef interface IDAMatte IDAMatte;
#endif 	/* __IDAMatte_FWD_DEFINED__ */


#ifndef __IDAMicrophone_FWD_DEFINED__
#define __IDAMicrophone_FWD_DEFINED__
typedef interface IDAMicrophone IDAMicrophone;
#endif 	/* __IDAMicrophone_FWD_DEFINED__ */


#ifndef __IDAMontage_FWD_DEFINED__
#define __IDAMontage_FWD_DEFINED__
typedef interface IDAMontage IDAMontage;
#endif 	/* __IDAMontage_FWD_DEFINED__ */


#ifndef __IDAPath2_FWD_DEFINED__
#define __IDAPath2_FWD_DEFINED__
typedef interface IDAPath2 IDAPath2;
#endif 	/* __IDAPath2_FWD_DEFINED__ */


#ifndef __IDAPoint2_FWD_DEFINED__
#define __IDAPoint2_FWD_DEFINED__
typedef interface IDAPoint2 IDAPoint2;
#endif 	/* __IDAPoint2_FWD_DEFINED__ */


#ifndef __IDAPoint3_FWD_DEFINED__
#define __IDAPoint3_FWD_DEFINED__
typedef interface IDAPoint3 IDAPoint3;
#endif 	/* __IDAPoint3_FWD_DEFINED__ */


#ifndef __IDASound_FWD_DEFINED__
#define __IDASound_FWD_DEFINED__
typedef interface IDASound IDASound;
#endif 	/* __IDASound_FWD_DEFINED__ */


#ifndef __IDAString_FWD_DEFINED__
#define __IDAString_FWD_DEFINED__
typedef interface IDAString IDAString;
#endif 	/* __IDAString_FWD_DEFINED__ */


#ifndef __IDATransform2_FWD_DEFINED__
#define __IDATransform2_FWD_DEFINED__
typedef interface IDATransform2 IDATransform2;
#endif 	/* __IDATransform2_FWD_DEFINED__ */


#ifndef __IDATransform3_FWD_DEFINED__
#define __IDATransform3_FWD_DEFINED__
typedef interface IDATransform3 IDATransform3;
#endif 	/* __IDATransform3_FWD_DEFINED__ */


#ifndef __IDAVector2_FWD_DEFINED__
#define __IDAVector2_FWD_DEFINED__
typedef interface IDAVector2 IDAVector2;
#endif 	/* __IDAVector2_FWD_DEFINED__ */


#ifndef __IDAVector3_FWD_DEFINED__
#define __IDAVector3_FWD_DEFINED__
typedef interface IDAVector3 IDAVector3;
#endif 	/* __IDAVector3_FWD_DEFINED__ */


#ifndef __IDAFontStyle_FWD_DEFINED__
#define __IDAFontStyle_FWD_DEFINED__
typedef interface IDAFontStyle IDAFontStyle;
#endif 	/* __IDAFontStyle_FWD_DEFINED__ */


#ifndef __IDALineStyle_FWD_DEFINED__
#define __IDALineStyle_FWD_DEFINED__
typedef interface IDALineStyle IDALineStyle;
#endif 	/* __IDALineStyle_FWD_DEFINED__ */


#ifndef __IDAEndStyle_FWD_DEFINED__
#define __IDAEndStyle_FWD_DEFINED__
typedef interface IDAEndStyle IDAEndStyle;
#endif 	/* __IDAEndStyle_FWD_DEFINED__ */


#ifndef __IDAJoinStyle_FWD_DEFINED__
#define __IDAJoinStyle_FWD_DEFINED__
typedef interface IDAJoinStyle IDAJoinStyle;
#endif 	/* __IDAJoinStyle_FWD_DEFINED__ */


#ifndef __IDADashStyle_FWD_DEFINED__
#define __IDADashStyle_FWD_DEFINED__
typedef interface IDADashStyle IDADashStyle;
#endif 	/* __IDADashStyle_FWD_DEFINED__ */


#ifndef __IDABbox2_FWD_DEFINED__
#define __IDABbox2_FWD_DEFINED__
typedef interface IDABbox2 IDABbox2;
#endif 	/* __IDABbox2_FWD_DEFINED__ */


#ifndef __IDABbox3_FWD_DEFINED__
#define __IDABbox3_FWD_DEFINED__
typedef interface IDABbox3 IDABbox3;
#endif 	/* __IDABbox3_FWD_DEFINED__ */


#ifndef __IDAPair_FWD_DEFINED__
#define __IDAPair_FWD_DEFINED__
typedef interface IDAPair IDAPair;
#endif 	/* __IDAPair_FWD_DEFINED__ */


#ifndef __IDAEvent_FWD_DEFINED__
#define __IDAEvent_FWD_DEFINED__
typedef interface IDAEvent IDAEvent;
#endif 	/* __IDAEvent_FWD_DEFINED__ */


#ifndef __IDAArray_FWD_DEFINED__
#define __IDAArray_FWD_DEFINED__
typedef interface IDAArray IDAArray;
#endif 	/* __IDAArray_FWD_DEFINED__ */


#ifndef __IDATuple_FWD_DEFINED__
#define __IDATuple_FWD_DEFINED__
typedef interface IDATuple IDATuple;
#endif 	/* __IDATuple_FWD_DEFINED__ */


#ifndef __IDAUserData_FWD_DEFINED__
#define __IDAUserData_FWD_DEFINED__
typedef interface IDAUserData IDAUserData;
#endif 	/* __IDAUserData_FWD_DEFINED__ */


#ifndef __DABoolean_FWD_DEFINED__
#define __DABoolean_FWD_DEFINED__

#ifdef __cplusplus
typedef class DABoolean DABoolean;
#else
typedef struct DABoolean DABoolean;
#endif /* __cplusplus */

#endif 	/* __DABoolean_FWD_DEFINED__ */


#ifndef __DACamera_FWD_DEFINED__
#define __DACamera_FWD_DEFINED__

#ifdef __cplusplus
typedef class DACamera DACamera;
#else
typedef struct DACamera DACamera;
#endif /* __cplusplus */

#endif 	/* __DACamera_FWD_DEFINED__ */


#ifndef __DAColor_FWD_DEFINED__
#define __DAColor_FWD_DEFINED__

#ifdef __cplusplus
typedef class DAColor DAColor;
#else
typedef struct DAColor DAColor;
#endif /* __cplusplus */

#endif 	/* __DAColor_FWD_DEFINED__ */


#ifndef __DAGeometry_FWD_DEFINED__
#define __DAGeometry_FWD_DEFINED__

#ifdef __cplusplus
typedef class DAGeometry DAGeometry;
#else
typedef struct DAGeometry DAGeometry;
#endif /* __cplusplus */

#endif 	/* __DAGeometry_FWD_DEFINED__ */


#ifndef __DAImage_FWD_DEFINED__
#define __DAImage_FWD_DEFINED__

#ifdef __cplusplus
typedef class DAImage DAImage;
#else
typedef struct DAImage DAImage;
#endif /* __cplusplus */

#endif 	/* __DAImage_FWD_DEFINED__ */


#ifndef __DAMatte_FWD_DEFINED__
#define __DAMatte_FWD_DEFINED__

#ifdef __cplusplus
typedef class DAMatte DAMatte;
#else
typedef struct DAMatte DAMatte;
#endif /* __cplusplus */

#endif 	/* __DAMatte_FWD_DEFINED__ */


#ifndef __DAMicrophone_FWD_DEFINED__
#define __DAMicrophone_FWD_DEFINED__

#ifdef __cplusplus
typedef class DAMicrophone DAMicrophone;
#else
typedef struct DAMicrophone DAMicrophone;
#endif /* __cplusplus */

#endif 	/* __DAMicrophone_FWD_DEFINED__ */


#ifndef __DAMontage_FWD_DEFINED__
#define __DAMontage_FWD_DEFINED__

#ifdef __cplusplus
typedef class DAMontage DAMontage;
#else
typedef struct DAMontage DAMontage;
#endif /* __cplusplus */

#endif 	/* __DAMontage_FWD_DEFINED__ */


#ifndef __DANumber_FWD_DEFINED__
#define __DANumber_FWD_DEFINED__

#ifdef __cplusplus
typedef class DANumber DANumber;
#else
typedef struct DANumber DANumber;
#endif /* __cplusplus */

#endif 	/* __DANumber_FWD_DEFINED__ */


#ifndef __DAPath2_FWD_DEFINED__
#define __DAPath2_FWD_DEFINED__

#ifdef __cplusplus
typedef class DAPath2 DAPath2;
#else
typedef struct DAPath2 DAPath2;
#endif /* __cplusplus */

#endif 	/* __DAPath2_FWD_DEFINED__ */


#ifndef __DAPoint2_FWD_DEFINED__
#define __DAPoint2_FWD_DEFINED__

#ifdef __cplusplus
typedef class DAPoint2 DAPoint2;
#else
typedef struct DAPoint2 DAPoint2;
#endif /* __cplusplus */

#endif 	/* __DAPoint2_FWD_DEFINED__ */


#ifndef __DAPoint3_FWD_DEFINED__
#define __DAPoint3_FWD_DEFINED__

#ifdef __cplusplus
typedef class DAPoint3 DAPoint3;
#else
typedef struct DAPoint3 DAPoint3;
#endif /* __cplusplus */

#endif 	/* __DAPoint3_FWD_DEFINED__ */


#ifndef __DASound_FWD_DEFINED__
#define __DASound_FWD_DEFINED__

#ifdef __cplusplus
typedef class DASound DASound;
#else
typedef struct DASound DASound;
#endif /* __cplusplus */

#endif 	/* __DASound_FWD_DEFINED__ */


#ifndef __DAString_FWD_DEFINED__
#define __DAString_FWD_DEFINED__

#ifdef __cplusplus
typedef class DAString DAString;
#else
typedef struct DAString DAString;
#endif /* __cplusplus */

#endif 	/* __DAString_FWD_DEFINED__ */


#ifndef __DATransform2_FWD_DEFINED__
#define __DATransform2_FWD_DEFINED__

#ifdef __cplusplus
typedef class DATransform2 DATransform2;
#else
typedef struct DATransform2 DATransform2;
#endif /* __cplusplus */

#endif 	/* __DATransform2_FWD_DEFINED__ */


#ifndef __DATransform3_FWD_DEFINED__
#define __DATransform3_FWD_DEFINED__

#ifdef __cplusplus
typedef class DATransform3 DATransform3;
#else
typedef struct DATransform3 DATransform3;
#endif /* __cplusplus */

#endif 	/* __DATransform3_FWD_DEFINED__ */


#ifndef __DAVector2_FWD_DEFINED__
#define __DAVector2_FWD_DEFINED__

#ifdef __cplusplus
typedef class DAVector2 DAVector2;
#else
typedef struct DAVector2 DAVector2;
#endif /* __cplusplus */

#endif 	/* __DAVector2_FWD_DEFINED__ */


#ifndef __DAVector3_FWD_DEFINED__
#define __DAVector3_FWD_DEFINED__

#ifdef __cplusplus
typedef class DAVector3 DAVector3;
#else
typedef struct DAVector3 DAVector3;
#endif /* __cplusplus */

#endif 	/* __DAVector3_FWD_DEFINED__ */


#ifndef __DAFontStyle_FWD_DEFINED__
#define __DAFontStyle_FWD_DEFINED__

#ifdef __cplusplus
typedef class DAFontStyle DAFontStyle;
#else
typedef struct DAFontStyle DAFontStyle;
#endif /* __cplusplus */

#endif 	/* __DAFontStyle_FWD_DEFINED__ */


#ifndef __DALineStyle_FWD_DEFINED__
#define __DALineStyle_FWD_DEFINED__

#ifdef __cplusplus
typedef class DALineStyle DALineStyle;
#else
typedef struct DALineStyle DALineStyle;
#endif /* __cplusplus */

#endif 	/* __DALineStyle_FWD_DEFINED__ */


#ifndef __DAEndStyle_FWD_DEFINED__
#define __DAEndStyle_FWD_DEFINED__

#ifdef __cplusplus
typedef class DAEndStyle DAEndStyle;
#else
typedef struct DAEndStyle DAEndStyle;
#endif /* __cplusplus */

#endif 	/* __DAEndStyle_FWD_DEFINED__ */


#ifndef __DAJoinStyle_FWD_DEFINED__
#define __DAJoinStyle_FWD_DEFINED__

#ifdef __cplusplus
typedef class DAJoinStyle DAJoinStyle;
#else
typedef struct DAJoinStyle DAJoinStyle;
#endif /* __cplusplus */

#endif 	/* __DAJoinStyle_FWD_DEFINED__ */


#ifndef __DADashStyle_FWD_DEFINED__
#define __DADashStyle_FWD_DEFINED__

#ifdef __cplusplus
typedef class DADashStyle DADashStyle;
#else
typedef struct DADashStyle DADashStyle;
#endif /* __cplusplus */

#endif 	/* __DADashStyle_FWD_DEFINED__ */


#ifndef __DABbox2_FWD_DEFINED__
#define __DABbox2_FWD_DEFINED__

#ifdef __cplusplus
typedef class DABbox2 DABbox2;
#else
typedef struct DABbox2 DABbox2;
#endif /* __cplusplus */

#endif 	/* __DABbox2_FWD_DEFINED__ */


#ifndef __DABbox3_FWD_DEFINED__
#define __DABbox3_FWD_DEFINED__

#ifdef __cplusplus
typedef class DABbox3 DABbox3;
#else
typedef struct DABbox3 DABbox3;
#endif /* __cplusplus */

#endif 	/* __DABbox3_FWD_DEFINED__ */


#ifndef __DAPair_FWD_DEFINED__
#define __DAPair_FWD_DEFINED__

#ifdef __cplusplus
typedef class DAPair DAPair;
#else
typedef struct DAPair DAPair;
#endif /* __cplusplus */

#endif 	/* __DAPair_FWD_DEFINED__ */


#ifndef __DAEvent_FWD_DEFINED__
#define __DAEvent_FWD_DEFINED__

#ifdef __cplusplus
typedef class DAEvent DAEvent;
#else
typedef struct DAEvent DAEvent;
#endif /* __cplusplus */

#endif 	/* __DAEvent_FWD_DEFINED__ */


#ifndef __DAArray_FWD_DEFINED__
#define __DAArray_FWD_DEFINED__

#ifdef __cplusplus
typedef class DAArray DAArray;
#else
typedef struct DAArray DAArray;
#endif /* __cplusplus */

#endif 	/* __DAArray_FWD_DEFINED__ */


#ifndef __DATuple_FWD_DEFINED__
#define __DATuple_FWD_DEFINED__

#ifdef __cplusplus
typedef class DATuple DATuple;
#else
typedef struct DATuple DATuple;
#endif /* __cplusplus */

#endif 	/* __DATuple_FWD_DEFINED__ */


#ifndef __DAUserData_FWD_DEFINED__
#define __DAUserData_FWD_DEFINED__

#ifdef __cplusplus
typedef class DAUserData DAUserData;
#else
typedef struct DAUserData DAUserData;
#endif /* __cplusplus */

#endif 	/* __DAUserData_FWD_DEFINED__ */


#ifndef __IDAPreferences_FWD_DEFINED__
#define __IDAPreferences_FWD_DEFINED__
typedef interface IDAPreferences IDAPreferences;
#endif 	/* __IDAPreferences_FWD_DEFINED__ */


#ifndef __DAView_FWD_DEFINED__
#define __DAView_FWD_DEFINED__

#ifdef __cplusplus
typedef class DAView DAView;
#else
typedef struct DAView DAView;
#endif /* __cplusplus */

#endif 	/* __DAView_FWD_DEFINED__ */


#ifndef __IDASite_FWD_DEFINED__
#define __IDASite_FWD_DEFINED__
typedef interface IDASite IDASite;
#endif 	/* __IDASite_FWD_DEFINED__ */


#ifndef __IDAImportationResult_FWD_DEFINED__
#define __IDAImportationResult_FWD_DEFINED__
typedef interface IDAImportationResult IDAImportationResult;
#endif 	/* __IDAImportationResult_FWD_DEFINED__ */


#ifndef __DAImportationResult_FWD_DEFINED__
#define __DAImportationResult_FWD_DEFINED__

#ifdef __cplusplus
typedef class DAImportationResult DAImportationResult;
#else
typedef struct DAImportationResult DAImportationResult;
#endif /* __cplusplus */

#endif 	/* __DAImportationResult_FWD_DEFINED__ */


#ifndef __DAPickableResult_FWD_DEFINED__
#define __DAPickableResult_FWD_DEFINED__

#ifdef __cplusplus
typedef class DAPickableResult DAPickableResult;
#else
typedef struct DAPickableResult DAPickableResult;
#endif /* __cplusplus */

#endif 	/* __DAPickableResult_FWD_DEFINED__ */


#ifndef __IDAStatics_FWD_DEFINED__
#define __IDAStatics_FWD_DEFINED__
typedef interface IDAStatics IDAStatics;
#endif 	/* __IDAStatics_FWD_DEFINED__ */


#ifndef __DAStatics_FWD_DEFINED__
#define __DAStatics_FWD_DEFINED__

#ifdef __cplusplus
typedef class DAStatics DAStatics;
#else
typedef struct DAStatics DAStatics;
#endif /* __cplusplus */

#endif 	/* __DAStatics_FWD_DEFINED__ */


#ifndef __IDAViewerControl_FWD_DEFINED__
#define __IDAViewerControl_FWD_DEFINED__
typedef interface IDAViewerControl IDAViewerControl;
#endif 	/* __IDAViewerControl_FWD_DEFINED__ */


#ifndef __IDAViewerControlWindowed_FWD_DEFINED__
#define __IDAViewerControlWindowed_FWD_DEFINED__
typedef interface IDAViewerControlWindowed IDAViewerControlWindowed;
#endif 	/* __IDAViewerControlWindowed_FWD_DEFINED__ */


#ifndef __DAViewerControl_FWD_DEFINED__
#define __DAViewerControl_FWD_DEFINED__

#ifdef __cplusplus
typedef class DAViewerControl DAViewerControl;
#else
typedef struct DAViewerControl DAViewerControl;
#endif /* __cplusplus */

#endif 	/* __DAViewerControl_FWD_DEFINED__ */


#ifndef __DAViewerControlWindowed_FWD_DEFINED__
#define __DAViewerControlWindowed_FWD_DEFINED__

#ifdef __cplusplus
typedef class DAViewerControlWindowed DAViewerControlWindowed;
#else
typedef struct DAViewerControlWindowed DAViewerControlWindowed;
#endif /* __cplusplus */

#endif 	/* __DAViewerControlWindowed_FWD_DEFINED__ */


/* header files for imported files */
#include "ocmm.h"
#include "effect.h"
#include "servprov.h"


/****************************************
 * Generated header for interface: __MIDL_itf_danim_0000
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 


    typedef interface IDABehavior IDABehavior;
    typedef interface IDANumber IDANumber;
    typedef interface IDABvrHook IDABvrHook;
typedef IDAPickableResult *PickableResultPtr;





#ifndef __DirectAnimation_LIBRARY_DEFINED__
#define __DirectAnimation_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: DirectAnimation
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [version][lcid][helpstring][uuid] */ 











    typedef interface IDABoolean IDABoolean;

    typedef interface IDACamera IDACamera;

    typedef interface IDAColor IDAColor;

    typedef interface IDAGeometry IDAGeometry;

    typedef interface IDAImage IDAImage;

    typedef interface IDAMatte IDAMatte;

    typedef interface IDAMicrophone IDAMicrophone;

    typedef interface IDAMontage IDAMontage;

    typedef interface IDANumber IDANumber;

    typedef interface IDAPath2 IDAPath2;

    typedef interface IDAPoint2 IDAPoint2;

    typedef interface IDAPoint3 IDAPoint3;

    typedef interface IDASound IDASound;

    typedef interface IDAString IDAString;

    typedef interface IDATransform2 IDATransform2;

    typedef interface IDATransform3 IDATransform3;

    typedef interface IDAVector2 IDAVector2;

    typedef interface IDAVector3 IDAVector3;

    typedef interface IDAFontStyle IDAFontStyle;

    typedef interface IDALineStyle IDALineStyle;

    typedef interface IDAEndStyle IDAEndStyle;

    typedef interface IDAJoinStyle IDAJoinStyle;

    typedef interface IDADashStyle IDADashStyle;

    typedef interface IDABbox2 IDABbox2;

    typedef interface IDABbox3 IDABbox3;

    typedef interface IDAPair IDAPair;

    typedef interface IDAEvent IDAEvent;

    typedef interface IDAArray IDAArray;

    typedef interface IDATuple IDATuple;

    typedef interface IDAUserData IDAUserData;
typedef /* [public][public][public] */ 
enum __MIDL___MIDL_itf_danim_0151_0001
    {	DAEmpty	= 0,
	DASolid	= 1,
	DADash	= 2
    }	DA_DASH_STYLE;

typedef /* [public][public][public] */ 
enum __MIDL___MIDL_itf_danim_0151_0002
    {	DAEndFlat	= 0,
	DAEndSquare	= 1,
	DAEndRound	= 2
    }	DA_END_STYLE;

typedef /* [public][public][public] */ 
enum __MIDL___MIDL_itf_danim_0151_0003
    {	DAJoinBevel	= 0,
	DAJoinRound	= 1,
	DAJoinMiter	= 2
    }	DA_JOIN_STYLE;

typedef /* [public][public][public] */ 
enum __MIDL___MIDL_itf_danim_0156_0001
    {	DAMultimediaTimer	= 0,
	DAContainerTimer	= 1,
	DAWMTimer	= 2
    }	DA_TIMER_SOURCE;


EXTERN_C const IID LIBID_DirectAnimation;

#ifndef __IDAViewSite_INTERFACE_DEFINED__
#define __IDAViewSite_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDAViewSite
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDAViewSite;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("283807B3-2C60-11d0-A31D-00AA00B92C03")
    IDAViewSite : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetStatusText( 
            /* [in] */ BSTR StatusText) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDAViewSiteVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDAViewSite * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDAViewSite * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDAViewSite * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDAViewSite * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDAViewSite * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDAViewSite * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDAViewSite * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *SetStatusText )( 
            IDAViewSite * This,
            /* [in] */ BSTR StatusText);
        
        END_INTERFACE
    } IDAViewSiteVtbl;

    interface IDAViewSite
    {
        CONST_VTBL struct IDAViewSiteVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDAViewSite_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDAViewSite_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDAViewSite_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDAViewSite_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDAViewSite_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDAViewSite_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDAViewSite_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDAViewSite_SetStatusText(This,StatusText)	\
    (This)->lpVtbl -> SetStatusText(This,StatusText)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDAViewSite_SetStatusText_Proxy( 
    IDAViewSite * This,
    /* [in] */ BSTR StatusText);




#endif 	/* __IDAViewSite_INTERFACE_DEFINED__ */


#ifndef __IDAView_INTERFACE_DEFINED__
#define __IDAView_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDAView
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][hidden][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDAView;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("283807B4-2C60-11d0-A31D-00AA00B92C03")
    IDAView : public IDispatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SimulationTime( 
            /* [retval][out] */ double *simTime) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Tick( 
            /* [in] */ double simTime,
            /* [retval][out] */ VARIANT_BOOL *needToRender) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Render( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddBvrToRun( 
            /* [in] */ IDABehavior *bvr,
            /* [retval][out] */ LONG *pId) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RemoveRunningBvr( 
            /* [in] */ LONG id) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StartModel( 
            /* [in] */ IDAImage *pImage,
            /* [in] */ IDASound *pSound,
            /* [in] */ double startTime) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StopModel( void) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Window( 
            /* [retval][out] */ HWND *hwnd) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Window( 
            /* [in] */ HWND hwnd) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IDirectDrawSurface( 
            /* [retval][out] */ IUnknown **ddsurf) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_IDirectDrawSurface( 
            /* [in] */ IUnknown *ddsurf) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DC( 
            /* [retval][out] */ HDC *dc) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_DC( 
            /* [in] */ HDC dc) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CompositeDirectlyToTarget( 
            /* [retval][out] */ VARIANT_BOOL *composeToTarget) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_CompositeDirectlyToTarget( 
            /* [in] */ VARIANT_BOOL composeToTarget) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetViewport( 
            /* [in] */ LONG xPos,
            /* [in] */ LONG yPos,
            /* [in] */ LONG w,
            /* [in] */ LONG h) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetClipRect( 
            /* [in] */ LONG xPos,
            /* [in] */ LONG yPos,
            /* [in] */ LONG w,
            /* [in] */ LONG h) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RePaint( 
            /* [in] */ LONG xPos,
            /* [in] */ LONG yPos,
            /* [in] */ LONG w,
            /* [in] */ LONG h) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PaletteChanged( 
            /* [in] */ VARIANT_BOOL bNew) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Site( 
            /* [retval][out] */ IDAViewSite **pViewSite) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Site( 
            /* [in] */ IDAViewSite *pViewSite) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_ClientSite( 
            /* [in] */ IOleClientSite *pClientSite) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ClientSite( 
            /* [retval][out] */ IOleClientSite **pClientSite) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnMouseMove( 
            /* [in] */ double when,
            /* [in] */ LONG xPos,
            /* [in] */ LONG yPos,
            /* [in] */ BYTE modifiers) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnMouseButton( 
            /* [in] */ double when,
            /* [in] */ LONG xPos,
            /* [in] */ LONG yPos,
            /* [in] */ BYTE button,
            /* [in] */ VARIANT_BOOL bPressed,
            /* [in] */ BYTE modifiers) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnKey( 
            /* [in] */ double when,
            /* [in] */ LONG key,
            /* [in] */ VARIANT_BOOL bPressed,
            /* [in] */ BYTE modifiers) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnFocus( 
            /* [in] */ VARIANT_BOOL bHasFocus) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Preferences( 
            /* [retval][out] */ IDAPreferences **prefs) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE QueryHitPoint( 
            /* [in] */ DWORD dwAspect,
            /* [in] */ LPCRECT prcBounds,
            /* [in] */ POINT ptLoc,
            /* [in] */ LONG lCloseHint,
            /* [retval][out] */ DWORD *pHitResult) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDAViewVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDAView * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDAView * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDAView * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDAView * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDAView * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDAView * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDAView * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SimulationTime )( 
            IDAView * This,
            /* [retval][out] */ double *simTime);
        
        HRESULT ( STDMETHODCALLTYPE *Tick )( 
            IDAView * This,
            /* [in] */ double simTime,
            /* [retval][out] */ VARIANT_BOOL *needToRender);
        
        HRESULT ( STDMETHODCALLTYPE *Render )( 
            IDAView * This);
        
        HRESULT ( STDMETHODCALLTYPE *AddBvrToRun )( 
            IDAView * This,
            /* [in] */ IDABehavior *bvr,
            /* [retval][out] */ LONG *pId);
        
        HRESULT ( STDMETHODCALLTYPE *RemoveRunningBvr )( 
            IDAView * This,
            /* [in] */ LONG id);
        
        HRESULT ( STDMETHODCALLTYPE *StartModel )( 
            IDAView * This,
            /* [in] */ IDAImage *pImage,
            /* [in] */ IDASound *pSound,
            /* [in] */ double startTime);
        
        HRESULT ( STDMETHODCALLTYPE *StopModel )( 
            IDAView * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Window )( 
            IDAView * This,
            /* [retval][out] */ HWND *hwnd);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Window )( 
            IDAView * This,
            /* [in] */ HWND hwnd);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IDirectDrawSurface )( 
            IDAView * This,
            /* [retval][out] */ IUnknown **ddsurf);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_IDirectDrawSurface )( 
            IDAView * This,
            /* [in] */ IUnknown *ddsurf);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DC )( 
            IDAView * This,
            /* [retval][out] */ HDC *dc);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_DC )( 
            IDAView * This,
            /* [in] */ HDC dc);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CompositeDirectlyToTarget )( 
            IDAView * This,
            /* [retval][out] */ VARIANT_BOOL *composeToTarget);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_CompositeDirectlyToTarget )( 
            IDAView * This,
            /* [in] */ VARIANT_BOOL composeToTarget);
        
        HRESULT ( STDMETHODCALLTYPE *SetViewport )( 
            IDAView * This,
            /* [in] */ LONG xPos,
            /* [in] */ LONG yPos,
            /* [in] */ LONG w,
            /* [in] */ LONG h);
        
        HRESULT ( STDMETHODCALLTYPE *SetClipRect )( 
            IDAView * This,
            /* [in] */ LONG xPos,
            /* [in] */ LONG yPos,
            /* [in] */ LONG w,
            /* [in] */ LONG h);
        
        HRESULT ( STDMETHODCALLTYPE *RePaint )( 
            IDAView * This,
            /* [in] */ LONG xPos,
            /* [in] */ LONG yPos,
            /* [in] */ LONG w,
            /* [in] */ LONG h);
        
        HRESULT ( STDMETHODCALLTYPE *PaletteChanged )( 
            IDAView * This,
            /* [in] */ VARIANT_BOOL bNew);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Site )( 
            IDAView * This,
            /* [retval][out] */ IDAViewSite **pViewSite);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Site )( 
            IDAView * This,
            /* [in] */ IDAViewSite *pViewSite);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_ClientSite )( 
            IDAView * This,
            /* [in] */ IOleClientSite *pClientSite);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ClientSite )( 
            IDAView * This,
            /* [retval][out] */ IOleClientSite **pClientSite);
        
        HRESULT ( STDMETHODCALLTYPE *OnMouseMove )( 
            IDAView * This,
            /* [in] */ double when,
            /* [in] */ LONG xPos,
            /* [in] */ LONG yPos,
            /* [in] */ BYTE modifiers);
        
        HRESULT ( STDMETHODCALLTYPE *OnMouseButton )( 
            IDAView * This,
            /* [in] */ double when,
            /* [in] */ LONG xPos,
            /* [in] */ LONG yPos,
            /* [in] */ BYTE button,
            /* [in] */ VARIANT_BOOL bPressed,
            /* [in] */ BYTE modifiers);
        
        HRESULT ( STDMETHODCALLTYPE *OnKey )( 
            IDAView * This,
            /* [in] */ double when,
            /* [in] */ LONG key,
            /* [in] */ VARIANT_BOOL bPressed,
            /* [in] */ BYTE modifiers);
        
        HRESULT ( STDMETHODCALLTYPE *OnFocus )( 
            IDAView * This,
            /* [in] */ VARIANT_BOOL bHasFocus);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Preferences )( 
            IDAView * This,
            /* [retval][out] */ IDAPreferences **prefs);
        
        HRESULT ( STDMETHODCALLTYPE *QueryHitPoint )( 
            IDAView * This,
            /* [in] */ DWORD dwAspect,
            /* [in] */ LPCRECT prcBounds,
            /* [in] */ POINT ptLoc,
            /* [in] */ LONG lCloseHint,
            /* [retval][out] */ DWORD *pHitResult);
        
        END_INTERFACE
    } IDAViewVtbl;

    interface IDAView
    {
        CONST_VTBL struct IDAViewVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDAView_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDAView_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDAView_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDAView_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDAView_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDAView_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDAView_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDAView_get_SimulationTime(This,simTime)	\
    (This)->lpVtbl -> get_SimulationTime(This,simTime)

#define IDAView_Tick(This,simTime,needToRender)	\
    (This)->lpVtbl -> Tick(This,simTime,needToRender)

#define IDAView_Render(This)	\
    (This)->lpVtbl -> Render(This)

#define IDAView_AddBvrToRun(This,bvr,pId)	\
    (This)->lpVtbl -> AddBvrToRun(This,bvr,pId)

#define IDAView_RemoveRunningBvr(This,id)	\
    (This)->lpVtbl -> RemoveRunningBvr(This,id)

#define IDAView_StartModel(This,pImage,pSound,startTime)	\
    (This)->lpVtbl -> StartModel(This,pImage,pSound,startTime)

#define IDAView_StopModel(This)	\
    (This)->lpVtbl -> StopModel(This)

#define IDAView_get_Window(This,hwnd)	\
    (This)->lpVtbl -> get_Window(This,hwnd)

#define IDAView_put_Window(This,hwnd)	\
    (This)->lpVtbl -> put_Window(This,hwnd)

#define IDAView_get_IDirectDrawSurface(This,ddsurf)	\
    (This)->lpVtbl -> get_IDirectDrawSurface(This,ddsurf)

#define IDAView_put_IDirectDrawSurface(This,ddsurf)	\
    (This)->lpVtbl -> put_IDirectDrawSurface(This,ddsurf)

#define IDAView_get_DC(This,dc)	\
    (This)->lpVtbl -> get_DC(This,dc)

#define IDAView_put_DC(This,dc)	\
    (This)->lpVtbl -> put_DC(This,dc)

#define IDAView_get_CompositeDirectlyToTarget(This,composeToTarget)	\
    (This)->lpVtbl -> get_CompositeDirectlyToTarget(This,composeToTarget)

#define IDAView_put_CompositeDirectlyToTarget(This,composeToTarget)	\
    (This)->lpVtbl -> put_CompositeDirectlyToTarget(This,composeToTarget)

#define IDAView_SetViewport(This,xPos,yPos,w,h)	\
    (This)->lpVtbl -> SetViewport(This,xPos,yPos,w,h)

#define IDAView_SetClipRect(This,xPos,yPos,w,h)	\
    (This)->lpVtbl -> SetClipRect(This,xPos,yPos,w,h)

#define IDAView_RePaint(This,xPos,yPos,w,h)	\
    (This)->lpVtbl -> RePaint(This,xPos,yPos,w,h)

#define IDAView_PaletteChanged(This,bNew)	\
    (This)->lpVtbl -> PaletteChanged(This,bNew)

#define IDAView_get_Site(This,pViewSite)	\
    (This)->lpVtbl -> get_Site(This,pViewSite)

#define IDAView_put_Site(This,pViewSite)	\
    (This)->lpVtbl -> put_Site(This,pViewSite)

#define IDAView_put_ClientSite(This,pClientSite)	\
    (This)->lpVtbl -> put_ClientSite(This,pClientSite)

#define IDAView_get_ClientSite(This,pClientSite)	\
    (This)->lpVtbl -> get_ClientSite(This,pClientSite)

#define IDAView_OnMouseMove(This,when,xPos,yPos,modifiers)	\
    (This)->lpVtbl -> OnMouseMove(This,when,xPos,yPos,modifiers)

#define IDAView_OnMouseButton(This,when,xPos,yPos,button,bPressed,modifiers)	\
    (This)->lpVtbl -> OnMouseButton(This,when,xPos,yPos,button,bPressed,modifiers)

#define IDAView_OnKey(This,when,key,bPressed,modifiers)	\
    (This)->lpVtbl -> OnKey(This,when,key,bPressed,modifiers)

#define IDAView_OnFocus(This,bHasFocus)	\
    (This)->lpVtbl -> OnFocus(This,bHasFocus)

#define IDAView_get_Preferences(This,prefs)	\
    (This)->lpVtbl -> get_Preferences(This,prefs)

#define IDAView_QueryHitPoint(This,dwAspect,prcBounds,ptLoc,lCloseHint,pHitResult)	\
    (This)->lpVtbl -> QueryHitPoint(This,dwAspect,prcBounds,ptLoc,lCloseHint,pHitResult)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IDAView_get_SimulationTime_Proxy( 
    IDAView * This,
    /* [retval][out] */ double *simTime);



HRESULT STDMETHODCALLTYPE IDAView_Tick_Proxy( 
    IDAView * This,
    /* [in] */ double simTime,
    /* [retval][out] */ VARIANT_BOOL *needToRender);



HRESULT STDMETHODCALLTYPE IDAView_Render_Proxy( 
    IDAView * This);



HRESULT STDMETHODCALLTYPE IDAView_AddBvrToRun_Proxy( 
    IDAView * This,
    /* [in] */ IDABehavior *bvr,
    /* [retval][out] */ LONG *pId);



HRESULT STDMETHODCALLTYPE IDAView_RemoveRunningBvr_Proxy( 
    IDAView * This,
    /* [in] */ LONG id);



HRESULT STDMETHODCALLTYPE IDAView_StartModel_Proxy( 
    IDAView * This,
    /* [in] */ IDAImage *pImage,
    /* [in] */ IDASound *pSound,
    /* [in] */ double startTime);



HRESULT STDMETHODCALLTYPE IDAView_StopModel_Proxy( 
    IDAView * This);



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IDAView_get_Window_Proxy( 
    IDAView * This,
    /* [retval][out] */ HWND *hwnd);



/* [propput] */ HRESULT STDMETHODCALLTYPE IDAView_put_Window_Proxy( 
    IDAView * This,
    /* [in] */ HWND hwnd);



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IDAView_get_IDirectDrawSurface_Proxy( 
    IDAView * This,
    /* [retval][out] */ IUnknown **ddsurf);



/* [propput] */ HRESULT STDMETHODCALLTYPE IDAView_put_IDirectDrawSurface_Proxy( 
    IDAView * This,
    /* [in] */ IUnknown *ddsurf);



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IDAView_get_DC_Proxy( 
    IDAView * This,
    /* [retval][out] */ HDC *dc);



/* [propput] */ HRESULT STDMETHODCALLTYPE IDAView_put_DC_Proxy( 
    IDAView * This,
    /* [in] */ HDC dc);



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IDAView_get_CompositeDirectlyToTarget_Proxy( 
    IDAView * This,
    /* [retval][out] */ VARIANT_BOOL *composeToTarget);



/* [propput] */ HRESULT STDMETHODCALLTYPE IDAView_put_CompositeDirectlyToTarget_Proxy( 
    IDAView * This,
    /* [in] */ VARIANT_BOOL composeToTarget);



HRESULT STDMETHODCALLTYPE IDAView_SetViewport_Proxy( 
    IDAView * This,
    /* [in] */ LONG xPos,
    /* [in] */ LONG yPos,
    /* [in] */ LONG w,
    /* [in] */ LONG h);



HRESULT STDMETHODCALLTYPE IDAView_SetClipRect_Proxy( 
    IDAView * This,
    /* [in] */ LONG xPos,
    /* [in] */ LONG yPos,
    /* [in] */ LONG w,
    /* [in] */ LONG h);



HRESULT STDMETHODCALLTYPE IDAView_RePaint_Proxy( 
    IDAView * This,
    /* [in] */ LONG xPos,
    /* [in] */ LONG yPos,
    /* [in] */ LONG w,
    /* [in] */ LONG h);



HRESULT STDMETHODCALLTYPE IDAView_PaletteChanged_Proxy( 
    IDAView * This,
    /* [in] */ VARIANT_BOOL bNew);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAView_get_Site_Proxy( 
    IDAView * This,
    /* [retval][out] */ IDAViewSite **pViewSite);



/* [propput] */ HRESULT STDMETHODCALLTYPE IDAView_put_Site_Proxy( 
    IDAView * This,
    /* [in] */ IDAViewSite *pViewSite);



/* [propput] */ HRESULT STDMETHODCALLTYPE IDAView_put_ClientSite_Proxy( 
    IDAView * This,
    /* [in] */ IOleClientSite *pClientSite);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAView_get_ClientSite_Proxy( 
    IDAView * This,
    /* [retval][out] */ IOleClientSite **pClientSite);



HRESULT STDMETHODCALLTYPE IDAView_OnMouseMove_Proxy( 
    IDAView * This,
    /* [in] */ double when,
    /* [in] */ LONG xPos,
    /* [in] */ LONG yPos,
    /* [in] */ BYTE modifiers);



HRESULT STDMETHODCALLTYPE IDAView_OnMouseButton_Proxy( 
    IDAView * This,
    /* [in] */ double when,
    /* [in] */ LONG xPos,
    /* [in] */ LONG yPos,
    /* [in] */ BYTE button,
    /* [in] */ VARIANT_BOOL bPressed,
    /* [in] */ BYTE modifiers);



HRESULT STDMETHODCALLTYPE IDAView_OnKey_Proxy( 
    IDAView * This,
    /* [in] */ double when,
    /* [in] */ LONG key,
    /* [in] */ VARIANT_BOOL bPressed,
    /* [in] */ BYTE modifiers);



HRESULT STDMETHODCALLTYPE IDAView_OnFocus_Proxy( 
    IDAView * This,
    /* [in] */ VARIANT_BOOL bHasFocus);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAView_get_Preferences_Proxy( 
    IDAView * This,
    /* [retval][out] */ IDAPreferences **prefs);



HRESULT STDMETHODCALLTYPE IDAView_QueryHitPoint_Proxy( 
    IDAView * This,
    /* [in] */ DWORD dwAspect,
    /* [in] */ LPCRECT prcBounds,
    /* [in] */ POINT ptLoc,
    /* [in] */ LONG lCloseHint,
    /* [retval][out] */ DWORD *pHitResult);




#endif 	/* __IDAView_INTERFACE_DEFINED__ */


#ifndef __IDABehavior_INTERFACE_DEFINED__
#define __IDABehavior_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDABehavior
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][hidden][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDABehavior;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("283807B7-2C60-11d0-A31D-00AA00B92C03")
    IDABehavior : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetClassName( 
            /* [retval][out] */ BSTR *pClassName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Init( 
            /* [in] */ IDABehavior *toBvr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Importance( 
            /* [in] */ double relativeImportance,
            /* [retval][out] */ IDABehavior **ppBvr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RunOnce( 
            /* [retval][out] */ IDABehavior **bvr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SubstituteTime( 
            /* [in] */ IDANumber *xform,
            /* [retval][out] */ IDABehavior **bvr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SwitchTo( 
            /* [in] */ IDABehavior *switchTo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SwitchToNumber( 
            /* [in] */ double numToSwitchTo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SwitchToString( 
            /* [in] */ BSTR strToSwitchTo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Hook( 
            /* [in] */ IDABvrHook *notifier,
            /* [retval][out] */ IDABehavior **pBvr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Duration( 
            /* [in] */ double duration,
            /* [retval][out] */ IDABehavior **bvr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DurationAnim( 
            /* [in] */ IDANumber *duration,
            /* [retval][out] */ IDABehavior **bvr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Repeat( 
            /* [in] */ LONG count,
            /* [retval][out] */ IDABehavior **bvr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RepeatForever( 
            /* [retval][out] */ IDABehavior **bvr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsReady( 
            /* [in] */ VARIANT_BOOL bBlock,
            /* [retval][out] */ VARIANT_BOOL *b) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDABehaviorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDABehavior * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDABehavior * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDABehavior * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDABehavior * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDABehavior * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDABehavior * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDABehavior * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassName )( 
            IDABehavior * This,
            /* [retval][out] */ BSTR *pClassName);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            IDABehavior * This,
            /* [in] */ IDABehavior *toBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Importance )( 
            IDABehavior * This,
            /* [in] */ double relativeImportance,
            /* [retval][out] */ IDABehavior **ppBvr);
        
        HRESULT ( STDMETHODCALLTYPE *RunOnce )( 
            IDABehavior * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SubstituteTime )( 
            IDABehavior * This,
            /* [in] */ IDANumber *xform,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchTo )( 
            IDABehavior * This,
            /* [in] */ IDABehavior *switchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToNumber )( 
            IDABehavior * This,
            /* [in] */ double numToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToString )( 
            IDABehavior * This,
            /* [in] */ BSTR strToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *Hook )( 
            IDABehavior * This,
            /* [in] */ IDABvrHook *notifier,
            /* [retval][out] */ IDABehavior **pBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Duration )( 
            IDABehavior * This,
            /* [in] */ double duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *DurationAnim )( 
            IDABehavior * This,
            /* [in] */ IDANumber *duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Repeat )( 
            IDABehavior * This,
            /* [in] */ LONG count,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *RepeatForever )( 
            IDABehavior * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *IsReady )( 
            IDABehavior * This,
            /* [in] */ VARIANT_BOOL bBlock,
            /* [retval][out] */ VARIANT_BOOL *b);
        
        END_INTERFACE
    } IDABehaviorVtbl;

    interface IDABehavior
    {
        CONST_VTBL struct IDABehaviorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDABehavior_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDABehavior_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDABehavior_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDABehavior_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDABehavior_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDABehavior_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDABehavior_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDABehavior_GetClassName(This,pClassName)	\
    (This)->lpVtbl -> GetClassName(This,pClassName)

#define IDABehavior_Init(This,toBvr)	\
    (This)->lpVtbl -> Init(This,toBvr)

#define IDABehavior_Importance(This,relativeImportance,ppBvr)	\
    (This)->lpVtbl -> Importance(This,relativeImportance,ppBvr)

#define IDABehavior_RunOnce(This,bvr)	\
    (This)->lpVtbl -> RunOnce(This,bvr)

#define IDABehavior_SubstituteTime(This,xform,bvr)	\
    (This)->lpVtbl -> SubstituteTime(This,xform,bvr)

#define IDABehavior_SwitchTo(This,switchTo)	\
    (This)->lpVtbl -> SwitchTo(This,switchTo)

#define IDABehavior_SwitchToNumber(This,numToSwitchTo)	\
    (This)->lpVtbl -> SwitchToNumber(This,numToSwitchTo)

#define IDABehavior_SwitchToString(This,strToSwitchTo)	\
    (This)->lpVtbl -> SwitchToString(This,strToSwitchTo)

#define IDABehavior_Hook(This,notifier,pBvr)	\
    (This)->lpVtbl -> Hook(This,notifier,pBvr)

#define IDABehavior_Duration(This,duration,bvr)	\
    (This)->lpVtbl -> Duration(This,duration,bvr)

#define IDABehavior_DurationAnim(This,duration,bvr)	\
    (This)->lpVtbl -> DurationAnim(This,duration,bvr)

#define IDABehavior_Repeat(This,count,bvr)	\
    (This)->lpVtbl -> Repeat(This,count,bvr)

#define IDABehavior_RepeatForever(This,bvr)	\
    (This)->lpVtbl -> RepeatForever(This,bvr)

#define IDABehavior_IsReady(This,bBlock,b)	\
    (This)->lpVtbl -> IsReady(This,bBlock,b)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDABehavior_GetClassName_Proxy( 
    IDABehavior * This,
    /* [retval][out] */ BSTR *pClassName);



HRESULT STDMETHODCALLTYPE IDABehavior_Init_Proxy( 
    IDABehavior * This,
    /* [in] */ IDABehavior *toBvr);



HRESULT STDMETHODCALLTYPE IDABehavior_Importance_Proxy( 
    IDABehavior * This,
    /* [in] */ double relativeImportance,
    /* [retval][out] */ IDABehavior **ppBvr);



HRESULT STDMETHODCALLTYPE IDABehavior_RunOnce_Proxy( 
    IDABehavior * This,
    /* [retval][out] */ IDABehavior **bvr);



HRESULT STDMETHODCALLTYPE IDABehavior_SubstituteTime_Proxy( 
    IDABehavior * This,
    /* [in] */ IDANumber *xform,
    /* [retval][out] */ IDABehavior **bvr);



HRESULT STDMETHODCALLTYPE IDABehavior_SwitchTo_Proxy( 
    IDABehavior * This,
    /* [in] */ IDABehavior *switchTo);



HRESULT STDMETHODCALLTYPE IDABehavior_SwitchToNumber_Proxy( 
    IDABehavior * This,
    /* [in] */ double numToSwitchTo);



HRESULT STDMETHODCALLTYPE IDABehavior_SwitchToString_Proxy( 
    IDABehavior * This,
    /* [in] */ BSTR strToSwitchTo);



HRESULT STDMETHODCALLTYPE IDABehavior_Hook_Proxy( 
    IDABehavior * This,
    /* [in] */ IDABvrHook *notifier,
    /* [retval][out] */ IDABehavior **pBvr);



HRESULT STDMETHODCALLTYPE IDABehavior_Duration_Proxy( 
    IDABehavior * This,
    /* [in] */ double duration,
    /* [retval][out] */ IDABehavior **bvr);



HRESULT STDMETHODCALLTYPE IDABehavior_DurationAnim_Proxy( 
    IDABehavior * This,
    /* [in] */ IDANumber *duration,
    /* [retval][out] */ IDABehavior **bvr);



HRESULT STDMETHODCALLTYPE IDABehavior_Repeat_Proxy( 
    IDABehavior * This,
    /* [in] */ LONG count,
    /* [retval][out] */ IDABehavior **bvr);



HRESULT STDMETHODCALLTYPE IDABehavior_RepeatForever_Proxy( 
    IDABehavior * This,
    /* [retval][out] */ IDABehavior **bvr);



HRESULT STDMETHODCALLTYPE IDABehavior_IsReady_Proxy( 
    IDABehavior * This,
    /* [in] */ VARIANT_BOOL bBlock,
    /* [retval][out] */ VARIANT_BOOL *b);




#endif 	/* __IDABehavior_INTERFACE_DEFINED__ */


#ifndef __IDANumber_INTERFACE_DEFINED__
#define __IDANumber_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDANumber
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][hidden][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDANumber;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("9CDE7340-3C20-11d0-A330-00AA00B92C03")
    IDANumber : public IDABehavior
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Extract( 
            /* [retval][out] */ double *ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AnimateProperty( 
            /* [in] */ BSTR propertyPath_0,
            /* [in] */ BSTR scriptingLanguage_1,
            /* [in] */ VARIANT_BOOL invokeAsMethod_2,
            /* [in] */ double minUpdateInterval_3,
            /* [retval][out] */ IDANumber **ret_4) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ToStringAnim( 
            /* [in] */ IDANumber *precision_0,
            /* [retval][out] */ IDAString **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ToString( 
            /* [in] */ double precision_0,
            /* [retval][out] */ IDAString **ret_1) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDANumberVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDANumber * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDANumber * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDANumber * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDANumber * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDANumber * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDANumber * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDANumber * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassName )( 
            IDANumber * This,
            /* [retval][out] */ BSTR *pClassName);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            IDANumber * This,
            /* [in] */ IDABehavior *toBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Importance )( 
            IDANumber * This,
            /* [in] */ double relativeImportance,
            /* [retval][out] */ IDABehavior **ppBvr);
        
        HRESULT ( STDMETHODCALLTYPE *RunOnce )( 
            IDANumber * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SubstituteTime )( 
            IDANumber * This,
            /* [in] */ IDANumber *xform,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchTo )( 
            IDANumber * This,
            /* [in] */ IDABehavior *switchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToNumber )( 
            IDANumber * This,
            /* [in] */ double numToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToString )( 
            IDANumber * This,
            /* [in] */ BSTR strToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *Hook )( 
            IDANumber * This,
            /* [in] */ IDABvrHook *notifier,
            /* [retval][out] */ IDABehavior **pBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Duration )( 
            IDANumber * This,
            /* [in] */ double duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *DurationAnim )( 
            IDANumber * This,
            /* [in] */ IDANumber *duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Repeat )( 
            IDANumber * This,
            /* [in] */ LONG count,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *RepeatForever )( 
            IDANumber * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *IsReady )( 
            IDANumber * This,
            /* [in] */ VARIANT_BOOL bBlock,
            /* [retval][out] */ VARIANT_BOOL *b);
        
        HRESULT ( STDMETHODCALLTYPE *Extract )( 
            IDANumber * This,
            /* [retval][out] */ double *ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *AnimateProperty )( 
            IDANumber * This,
            /* [in] */ BSTR propertyPath_0,
            /* [in] */ BSTR scriptingLanguage_1,
            /* [in] */ VARIANT_BOOL invokeAsMethod_2,
            /* [in] */ double minUpdateInterval_3,
            /* [retval][out] */ IDANumber **ret_4);
        
        HRESULT ( STDMETHODCALLTYPE *ToStringAnim )( 
            IDANumber * This,
            /* [in] */ IDANumber *precision_0,
            /* [retval][out] */ IDAString **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *ToString )( 
            IDANumber * This,
            /* [in] */ double precision_0,
            /* [retval][out] */ IDAString **ret_1);
        
        END_INTERFACE
    } IDANumberVtbl;

    interface IDANumber
    {
        CONST_VTBL struct IDANumberVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDANumber_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDANumber_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDANumber_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDANumber_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDANumber_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDANumber_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDANumber_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDANumber_GetClassName(This,pClassName)	\
    (This)->lpVtbl -> GetClassName(This,pClassName)

#define IDANumber_Init(This,toBvr)	\
    (This)->lpVtbl -> Init(This,toBvr)

#define IDANumber_Importance(This,relativeImportance,ppBvr)	\
    (This)->lpVtbl -> Importance(This,relativeImportance,ppBvr)

#define IDANumber_RunOnce(This,bvr)	\
    (This)->lpVtbl -> RunOnce(This,bvr)

#define IDANumber_SubstituteTime(This,xform,bvr)	\
    (This)->lpVtbl -> SubstituteTime(This,xform,bvr)

#define IDANumber_SwitchTo(This,switchTo)	\
    (This)->lpVtbl -> SwitchTo(This,switchTo)

#define IDANumber_SwitchToNumber(This,numToSwitchTo)	\
    (This)->lpVtbl -> SwitchToNumber(This,numToSwitchTo)

#define IDANumber_SwitchToString(This,strToSwitchTo)	\
    (This)->lpVtbl -> SwitchToString(This,strToSwitchTo)

#define IDANumber_Hook(This,notifier,pBvr)	\
    (This)->lpVtbl -> Hook(This,notifier,pBvr)

#define IDANumber_Duration(This,duration,bvr)	\
    (This)->lpVtbl -> Duration(This,duration,bvr)

#define IDANumber_DurationAnim(This,duration,bvr)	\
    (This)->lpVtbl -> DurationAnim(This,duration,bvr)

#define IDANumber_Repeat(This,count,bvr)	\
    (This)->lpVtbl -> Repeat(This,count,bvr)

#define IDANumber_RepeatForever(This,bvr)	\
    (This)->lpVtbl -> RepeatForever(This,bvr)

#define IDANumber_IsReady(This,bBlock,b)	\
    (This)->lpVtbl -> IsReady(This,bBlock,b)


#define IDANumber_Extract(This,ret_0)	\
    (This)->lpVtbl -> Extract(This,ret_0)

#define IDANumber_AnimateProperty(This,propertyPath_0,scriptingLanguage_1,invokeAsMethod_2,minUpdateInterval_3,ret_4)	\
    (This)->lpVtbl -> AnimateProperty(This,propertyPath_0,scriptingLanguage_1,invokeAsMethod_2,minUpdateInterval_3,ret_4)

#define IDANumber_ToStringAnim(This,precision_0,ret_1)	\
    (This)->lpVtbl -> ToStringAnim(This,precision_0,ret_1)

#define IDANumber_ToString(This,precision_0,ret_1)	\
    (This)->lpVtbl -> ToString(This,precision_0,ret_1)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDANumber_Extract_Proxy( 
    IDANumber * This,
    /* [retval][out] */ double *ret_0);



HRESULT STDMETHODCALLTYPE IDANumber_AnimateProperty_Proxy( 
    IDANumber * This,
    /* [in] */ BSTR propertyPath_0,
    /* [in] */ BSTR scriptingLanguage_1,
    /* [in] */ VARIANT_BOOL invokeAsMethod_2,
    /* [in] */ double minUpdateInterval_3,
    /* [retval][out] */ IDANumber **ret_4);



HRESULT STDMETHODCALLTYPE IDANumber_ToStringAnim_Proxy( 
    IDANumber * This,
    /* [in] */ IDANumber *precision_0,
    /* [retval][out] */ IDAString **ret_1);



HRESULT STDMETHODCALLTYPE IDANumber_ToString_Proxy( 
    IDANumber * This,
    /* [in] */ double precision_0,
    /* [retval][out] */ IDAString **ret_1);




#endif 	/* __IDANumber_INTERFACE_DEFINED__ */


#ifndef __IDABvrHook_INTERFACE_DEFINED__
#define __IDABvrHook_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDABvrHook
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDABvrHook;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("3E2487C4-8709-11d0-B177-00C04FC2A0CA")
    IDABvrHook : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Notify( 
            /* [in] */ LONG id,
            /* [in] */ VARIANT_BOOL startingPerformance,
            /* [in] */ double startTime,
            /* [in] */ double gTime,
            /* [in] */ double lTime,
            /* [in] */ IDABehavior *sampleVal,
            /* [in] */ IDABehavior *curRunningBvr,
            /* [retval][out] */ IDABehavior **ppBvr) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDABvrHookVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDABvrHook * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDABvrHook * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDABvrHook * This);
        
        HRESULT ( STDMETHODCALLTYPE *Notify )( 
            IDABvrHook * This,
            /* [in] */ LONG id,
            /* [in] */ VARIANT_BOOL startingPerformance,
            /* [in] */ double startTime,
            /* [in] */ double gTime,
            /* [in] */ double lTime,
            /* [in] */ IDABehavior *sampleVal,
            /* [in] */ IDABehavior *curRunningBvr,
            /* [retval][out] */ IDABehavior **ppBvr);
        
        END_INTERFACE
    } IDABvrHookVtbl;

    interface IDABvrHook
    {
        CONST_VTBL struct IDABvrHookVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDABvrHook_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDABvrHook_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDABvrHook_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDABvrHook_Notify(This,id,startingPerformance,startTime,gTime,lTime,sampleVal,curRunningBvr,ppBvr)	\
    (This)->lpVtbl -> Notify(This,id,startingPerformance,startTime,gTime,lTime,sampleVal,curRunningBvr,ppBvr)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDABvrHook_Notify_Proxy( 
    IDABvrHook * This,
    /* [in] */ LONG id,
    /* [in] */ VARIANT_BOOL startingPerformance,
    /* [in] */ double startTime,
    /* [in] */ double gTime,
    /* [in] */ double lTime,
    /* [in] */ IDABehavior *sampleVal,
    /* [in] */ IDABehavior *curRunningBvr,
    /* [retval][out] */ IDABehavior **ppBvr);




#endif 	/* __IDABvrHook_INTERFACE_DEFINED__ */


#ifndef __IDADrawingSurface_INTERFACE_DEFINED__
#define __IDADrawingSurface_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDADrawingSurface
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDADrawingSurface;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("BC0BFD34-D21D-11d0-9385-00C04FB6BD36")
    IDADrawingSurface : public IDispatch
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Image( 
            /* [retval][out] */ IDAImage **img) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_LineStyle( 
            /* [in] */ IDALineStyle *ls) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_BorderStyle( 
            /* [in] */ IDALineStyle *bs) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_FontStyle( 
            /* [in] */ IDAFontStyle *fs) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_ClipMatte( 
            /* [in] */ IDAMatte *matte) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_MouseEventsEnabled( 
            /* [in] */ VARIANT_BOOL on) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_HatchFillTransparent( 
            /* [in] */ VARIANT_BOOL fillOff) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_LocalContextImage( 
            /* [retval][out] */ IDAImage **img) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SaveGraphicsState( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RestoreGraphicsState( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Opacity( 
            /* [in] */ double opac) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OpacityAnim( 
            /* [in] */ IDANumber *opac) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Crop( 
            /* [in] */ double lowerLeftX,
            /* [in] */ double lowerLeftY,
            /* [in] */ double upperRightX,
            /* [in] */ double upperRightY) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CropPoints( 
            /* [in] */ IDAPoint2 *min,
            /* [in] */ IDAPoint2 *max) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Transform( 
            /* [in] */ IDATransform2 *xform) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LineColor( 
            /* [in] */ IDAColor *clr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LineWidth( 
            /* [in] */ double w) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LineDashStyle( 
            /* [in] */ DA_DASH_STYLE id) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LineEndStyle( 
            /* [in] */ DA_END_STYLE id) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LineJoinStyle( 
            /* [in] */ DA_JOIN_STYLE id) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE BorderColor( 
            /* [in] */ IDAColor *clr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE BorderWidth( 
            /* [in] */ double w) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE BorderDashStyle( 
            /* [in] */ DA_DASH_STYLE id) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE BorderEndStyle( 
            /* [in] */ DA_END_STYLE obsolete) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE BorderJoinStyle( 
            /* [in] */ DA_JOIN_STYLE id) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Font( 
            /* [in] */ BSTR FontFace,
            /* [in] */ LONG sizeInPoints,
            /* [in] */ VARIANT_BOOL Bold,
            /* [in] */ VARIANT_BOOL italic,
            /* [in] */ VARIANT_BOOL underline,
            /* [in] */ VARIANT_BOOL strikethrough) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TextureFill( 
            /* [in] */ IDAImage *obsolete1,
            /* [in] */ double obsolete2,
            /* [in] */ double obsolete3) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ImageFill( 
            /* [in] */ IDAImage *obsolete1,
            /* [in] */ double obsolete2,
            /* [in] */ double obsolete3) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FillTexture( 
            /* [in] */ IDAImage *img) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FillImage( 
            /* [in] */ IDAImage *img) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FillStyle( 
            /* [in] */ int ID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FillColor( 
            /* [in] */ IDAColor *foreground) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SecondaryFillColor( 
            /* [in] */ IDAColor *val) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GradientShape( 
            /* [in] */ VARIANT pts) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GradientExtent( 
            /* [in] */ double startx,
            /* [in] */ double starty,
            /* [in] */ double finishx,
            /* [in] */ double finishy) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GradientExtentPoints( 
            /* [in] */ IDAPoint2 *startColor,
            /* [in] */ IDAPoint2 *stopColor) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GradientRolloffPower( 
            /* [in] */ double power) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GradientRolloffPowerAnim( 
            /* [in] */ IDANumber *power) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FixedFillScale( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HorizontalFillScale( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE VerticalFillScale( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AutoSizeFillScale( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PolylineEx( 
            /* [in] */ LONG numPts,
            /* [size_is][in] */ IDAPoint2 *pts[  ]) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Polyline( 
            /* [in] */ VARIANT v) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PolygonEx( 
            /* [in] */ LONG numPts,
            /* [size_is][in] */ IDAPoint2 *pts[  ]) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Polygon( 
            /* [in] */ VARIANT v) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LinePoints( 
            /* [in] */ IDAPoint2 *p1,
            /* [in] */ IDAPoint2 *p2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Line( 
            /* [in] */ double startX,
            /* [in] */ double startY,
            /* [in] */ double endX,
            /* [in] */ double endY) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ArcRadians( 
            /* [in] */ double xPos,
            /* [in] */ double yPos,
            /* [in] */ double startAngle,
            /* [in] */ double endAngle,
            /* [in] */ double arcWidth,
            /* [in] */ double arcHeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ArcDegrees( 
            /* [in] */ double xPos,
            /* [in] */ double yPos,
            /* [in] */ double startAngle,
            /* [in] */ double endAngle,
            /* [in] */ double arcWidth,
            /* [in] */ double arcHeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Oval( 
            /* [in] */ double xPos,
            /* [in] */ double yPos,
            /* [in] */ double w,
            /* [in] */ double h) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Rect( 
            /* [in] */ double xPos,
            /* [in] */ double yPos,
            /* [in] */ double w,
            /* [in] */ double h) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RoundRect( 
            /* [in] */ double xPos,
            /* [in] */ double yPos,
            /* [in] */ double w,
            /* [in] */ double h,
            /* [in] */ double arcWidth,
            /* [in] */ double arcHeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PieRadians( 
            /* [in] */ double xPos,
            /* [in] */ double yPos,
            /* [in] */ double startAngle,
            /* [in] */ double endAngle,
            /* [in] */ double arcWidth,
            /* [in] */ double arcHeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PieDegrees( 
            /* [in] */ double xPos,
            /* [in] */ double yPos,
            /* [in] */ double startAngle,
            /* [in] */ double endAngle,
            /* [in] */ double arcWidth,
            /* [in] */ double arcHeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Text( 
            /* [in] */ BSTR str,
            /* [in] */ double xPos,
            /* [in] */ double yPos) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TextPoint( 
            /* [in] */ BSTR str,
            /* [in] */ IDAPoint2 *point) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FillPath( 
            /* [in] */ IDAPath2 *path) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DrawPath( 
            /* [in] */ IDAPath2 *path) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OverlayImage( 
            /* [in] */ IDAImage *img) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDADrawingSurfaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDADrawingSurface * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDADrawingSurface * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDADrawingSurface * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDADrawingSurface * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDADrawingSurface * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDADrawingSurface * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDADrawingSurface * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Image )( 
            IDADrawingSurface * This,
            /* [retval][out] */ IDAImage **img);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_LineStyle )( 
            IDADrawingSurface * This,
            /* [in] */ IDALineStyle *ls);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_BorderStyle )( 
            IDADrawingSurface * This,
            /* [in] */ IDALineStyle *bs);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_FontStyle )( 
            IDADrawingSurface * This,
            /* [in] */ IDAFontStyle *fs);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_ClipMatte )( 
            IDADrawingSurface * This,
            /* [in] */ IDAMatte *matte);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_MouseEventsEnabled )( 
            IDADrawingSurface * This,
            /* [in] */ VARIANT_BOOL on);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_HatchFillTransparent )( 
            IDADrawingSurface * This,
            /* [in] */ VARIANT_BOOL fillOff);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_LocalContextImage )( 
            IDADrawingSurface * This,
            /* [retval][out] */ IDAImage **img);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IDADrawingSurface * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IDADrawingSurface * This);
        
        HRESULT ( STDMETHODCALLTYPE *SaveGraphicsState )( 
            IDADrawingSurface * This);
        
        HRESULT ( STDMETHODCALLTYPE *RestoreGraphicsState )( 
            IDADrawingSurface * This);
        
        HRESULT ( STDMETHODCALLTYPE *Opacity )( 
            IDADrawingSurface * This,
            /* [in] */ double opac);
        
        HRESULT ( STDMETHODCALLTYPE *OpacityAnim )( 
            IDADrawingSurface * This,
            /* [in] */ IDANumber *opac);
        
        HRESULT ( STDMETHODCALLTYPE *Crop )( 
            IDADrawingSurface * This,
            /* [in] */ double lowerLeftX,
            /* [in] */ double lowerLeftY,
            /* [in] */ double upperRightX,
            /* [in] */ double upperRightY);
        
        HRESULT ( STDMETHODCALLTYPE *CropPoints )( 
            IDADrawingSurface * This,
            /* [in] */ IDAPoint2 *min,
            /* [in] */ IDAPoint2 *max);
        
        HRESULT ( STDMETHODCALLTYPE *Transform )( 
            IDADrawingSurface * This,
            /* [in] */ IDATransform2 *xform);
        
        HRESULT ( STDMETHODCALLTYPE *LineColor )( 
            IDADrawingSurface * This,
            /* [in] */ IDAColor *clr);
        
        HRESULT ( STDMETHODCALLTYPE *LineWidth )( 
            IDADrawingSurface * This,
            /* [in] */ double w);
        
        HRESULT ( STDMETHODCALLTYPE *LineDashStyle )( 
            IDADrawingSurface * This,
            /* [in] */ DA_DASH_STYLE id);
        
        HRESULT ( STDMETHODCALLTYPE *LineEndStyle )( 
            IDADrawingSurface * This,
            /* [in] */ DA_END_STYLE id);
        
        HRESULT ( STDMETHODCALLTYPE *LineJoinStyle )( 
            IDADrawingSurface * This,
            /* [in] */ DA_JOIN_STYLE id);
        
        HRESULT ( STDMETHODCALLTYPE *BorderColor )( 
            IDADrawingSurface * This,
            /* [in] */ IDAColor *clr);
        
        HRESULT ( STDMETHODCALLTYPE *BorderWidth )( 
            IDADrawingSurface * This,
            /* [in] */ double w);
        
        HRESULT ( STDMETHODCALLTYPE *BorderDashStyle )( 
            IDADrawingSurface * This,
            /* [in] */ DA_DASH_STYLE id);
        
        HRESULT ( STDMETHODCALLTYPE *BorderEndStyle )( 
            IDADrawingSurface * This,
            /* [in] */ DA_END_STYLE obsolete);
        
        HRESULT ( STDMETHODCALLTYPE *BorderJoinStyle )( 
            IDADrawingSurface * This,
            /* [in] */ DA_JOIN_STYLE id);
        
        HRESULT ( STDMETHODCALLTYPE *Font )( 
            IDADrawingSurface * This,
            /* [in] */ BSTR FontFace,
            /* [in] */ LONG sizeInPoints,
            /* [in] */ VARIANT_BOOL Bold,
            /* [in] */ VARIANT_BOOL italic,
            /* [in] */ VARIANT_BOOL underline,
            /* [in] */ VARIANT_BOOL strikethrough);
        
        HRESULT ( STDMETHODCALLTYPE *TextureFill )( 
            IDADrawingSurface * This,
            /* [in] */ IDAImage *obsolete1,
            /* [in] */ double obsolete2,
            /* [in] */ double obsolete3);
        
        HRESULT ( STDMETHODCALLTYPE *ImageFill )( 
            IDADrawingSurface * This,
            /* [in] */ IDAImage *obsolete1,
            /* [in] */ double obsolete2,
            /* [in] */ double obsolete3);
        
        HRESULT ( STDMETHODCALLTYPE *FillTexture )( 
            IDADrawingSurface * This,
            /* [in] */ IDAImage *img);
        
        HRESULT ( STDMETHODCALLTYPE *FillImage )( 
            IDADrawingSurface * This,
            /* [in] */ IDAImage *img);
        
        HRESULT ( STDMETHODCALLTYPE *FillStyle )( 
            IDADrawingSurface * This,
            /* [in] */ int ID);
        
        HRESULT ( STDMETHODCALLTYPE *FillColor )( 
            IDADrawingSurface * This,
            /* [in] */ IDAColor *foreground);
        
        HRESULT ( STDMETHODCALLTYPE *SecondaryFillColor )( 
            IDADrawingSurface * This,
            /* [in] */ IDAColor *val);
        
        HRESULT ( STDMETHODCALLTYPE *GradientShape )( 
            IDADrawingSurface * This,
            /* [in] */ VARIANT pts);
        
        HRESULT ( STDMETHODCALLTYPE *GradientExtent )( 
            IDADrawingSurface * This,
            /* [in] */ double startx,
            /* [in] */ double starty,
            /* [in] */ double finishx,
            /* [in] */ double finishy);
        
        HRESULT ( STDMETHODCALLTYPE *GradientExtentPoints )( 
            IDADrawingSurface * This,
            /* [in] */ IDAPoint2 *startColor,
            /* [in] */ IDAPoint2 *stopColor);
        
        HRESULT ( STDMETHODCALLTYPE *GradientRolloffPower )( 
            IDADrawingSurface * This,
            /* [in] */ double power);
        
        HRESULT ( STDMETHODCALLTYPE *GradientRolloffPowerAnim )( 
            IDADrawingSurface * This,
            /* [in] */ IDANumber *power);
        
        HRESULT ( STDMETHODCALLTYPE *FixedFillScale )( 
            IDADrawingSurface * This);
        
        HRESULT ( STDMETHODCALLTYPE *HorizontalFillScale )( 
            IDADrawingSurface * This);
        
        HRESULT ( STDMETHODCALLTYPE *VerticalFillScale )( 
            IDADrawingSurface * This);
        
        HRESULT ( STDMETHODCALLTYPE *AutoSizeFillScale )( 
            IDADrawingSurface * This);
        
        HRESULT ( STDMETHODCALLTYPE *PolylineEx )( 
            IDADrawingSurface * This,
            /* [in] */ LONG numPts,
            /* [size_is][in] */ IDAPoint2 *pts[  ]);
        
        HRESULT ( STDMETHODCALLTYPE *Polyline )( 
            IDADrawingSurface * This,
            /* [in] */ VARIANT v);
        
        HRESULT ( STDMETHODCALLTYPE *PolygonEx )( 
            IDADrawingSurface * This,
            /* [in] */ LONG numPts,
            /* [size_is][in] */ IDAPoint2 *pts[  ]);
        
        HRESULT ( STDMETHODCALLTYPE *Polygon )( 
            IDADrawingSurface * This,
            /* [in] */ VARIANT v);
        
        HRESULT ( STDMETHODCALLTYPE *LinePoints )( 
            IDADrawingSurface * This,
            /* [in] */ IDAPoint2 *p1,
            /* [in] */ IDAPoint2 *p2);
        
        HRESULT ( STDMETHODCALLTYPE *Line )( 
            IDADrawingSurface * This,
            /* [in] */ double startX,
            /* [in] */ double startY,
            /* [in] */ double endX,
            /* [in] */ double endY);
        
        HRESULT ( STDMETHODCALLTYPE *ArcRadians )( 
            IDADrawingSurface * This,
            /* [in] */ double xPos,
            /* [in] */ double yPos,
            /* [in] */ double startAngle,
            /* [in] */ double endAngle,
            /* [in] */ double arcWidth,
            /* [in] */ double arcHeight);
        
        HRESULT ( STDMETHODCALLTYPE *ArcDegrees )( 
            IDADrawingSurface * This,
            /* [in] */ double xPos,
            /* [in] */ double yPos,
            /* [in] */ double startAngle,
            /* [in] */ double endAngle,
            /* [in] */ double arcWidth,
            /* [in] */ double arcHeight);
        
        HRESULT ( STDMETHODCALLTYPE *Oval )( 
            IDADrawingSurface * This,
            /* [in] */ double xPos,
            /* [in] */ double yPos,
            /* [in] */ double w,
            /* [in] */ double h);
        
        HRESULT ( STDMETHODCALLTYPE *Rect )( 
            IDADrawingSurface * This,
            /* [in] */ double xPos,
            /* [in] */ double yPos,
            /* [in] */ double w,
            /* [in] */ double h);
        
        HRESULT ( STDMETHODCALLTYPE *RoundRect )( 
            IDADrawingSurface * This,
            /* [in] */ double xPos,
            /* [in] */ double yPos,
            /* [in] */ double w,
            /* [in] */ double h,
            /* [in] */ double arcWidth,
            /* [in] */ double arcHeight);
        
        HRESULT ( STDMETHODCALLTYPE *PieRadians )( 
            IDADrawingSurface * This,
            /* [in] */ double xPos,
            /* [in] */ double yPos,
            /* [in] */ double startAngle,
            /* [in] */ double endAngle,
            /* [in] */ double arcWidth,
            /* [in] */ double arcHeight);
        
        HRESULT ( STDMETHODCALLTYPE *PieDegrees )( 
            IDADrawingSurface * This,
            /* [in] */ double xPos,
            /* [in] */ double yPos,
            /* [in] */ double startAngle,
            /* [in] */ double endAngle,
            /* [in] */ double arcWidth,
            /* [in] */ double arcHeight);
        
        HRESULT ( STDMETHODCALLTYPE *Text )( 
            IDADrawingSurface * This,
            /* [in] */ BSTR str,
            /* [in] */ double xPos,
            /* [in] */ double yPos);
        
        HRESULT ( STDMETHODCALLTYPE *TextPoint )( 
            IDADrawingSurface * This,
            /* [in] */ BSTR str,
            /* [in] */ IDAPoint2 *point);
        
        HRESULT ( STDMETHODCALLTYPE *FillPath )( 
            IDADrawingSurface * This,
            /* [in] */ IDAPath2 *path);
        
        HRESULT ( STDMETHODCALLTYPE *DrawPath )( 
            IDADrawingSurface * This,
            /* [in] */ IDAPath2 *path);
        
        HRESULT ( STDMETHODCALLTYPE *OverlayImage )( 
            IDADrawingSurface * This,
            /* [in] */ IDAImage *img);
        
        END_INTERFACE
    } IDADrawingSurfaceVtbl;

    interface IDADrawingSurface
    {
        CONST_VTBL struct IDADrawingSurfaceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDADrawingSurface_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDADrawingSurface_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDADrawingSurface_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDADrawingSurface_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDADrawingSurface_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDADrawingSurface_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDADrawingSurface_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDADrawingSurface_get_Image(This,img)	\
    (This)->lpVtbl -> get_Image(This,img)

#define IDADrawingSurface_put_LineStyle(This,ls)	\
    (This)->lpVtbl -> put_LineStyle(This,ls)

#define IDADrawingSurface_put_BorderStyle(This,bs)	\
    (This)->lpVtbl -> put_BorderStyle(This,bs)

#define IDADrawingSurface_put_FontStyle(This,fs)	\
    (This)->lpVtbl -> put_FontStyle(This,fs)

#define IDADrawingSurface_put_ClipMatte(This,matte)	\
    (This)->lpVtbl -> put_ClipMatte(This,matte)

#define IDADrawingSurface_put_MouseEventsEnabled(This,on)	\
    (This)->lpVtbl -> put_MouseEventsEnabled(This,on)

#define IDADrawingSurface_put_HatchFillTransparent(This,fillOff)	\
    (This)->lpVtbl -> put_HatchFillTransparent(This,fillOff)

#define IDADrawingSurface_get_LocalContextImage(This,img)	\
    (This)->lpVtbl -> get_LocalContextImage(This,img)

#define IDADrawingSurface_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IDADrawingSurface_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#define IDADrawingSurface_SaveGraphicsState(This)	\
    (This)->lpVtbl -> SaveGraphicsState(This)

#define IDADrawingSurface_RestoreGraphicsState(This)	\
    (This)->lpVtbl -> RestoreGraphicsState(This)

#define IDADrawingSurface_Opacity(This,opac)	\
    (This)->lpVtbl -> Opacity(This,opac)

#define IDADrawingSurface_OpacityAnim(This,opac)	\
    (This)->lpVtbl -> OpacityAnim(This,opac)

#define IDADrawingSurface_Crop(This,lowerLeftX,lowerLeftY,upperRightX,upperRightY)	\
    (This)->lpVtbl -> Crop(This,lowerLeftX,lowerLeftY,upperRightX,upperRightY)

#define IDADrawingSurface_CropPoints(This,min,max)	\
    (This)->lpVtbl -> CropPoints(This,min,max)

#define IDADrawingSurface_Transform(This,xform)	\
    (This)->lpVtbl -> Transform(This,xform)

#define IDADrawingSurface_LineColor(This,clr)	\
    (This)->lpVtbl -> LineColor(This,clr)

#define IDADrawingSurface_LineWidth(This,w)	\
    (This)->lpVtbl -> LineWidth(This,w)

#define IDADrawingSurface_LineDashStyle(This,id)	\
    (This)->lpVtbl -> LineDashStyle(This,id)

#define IDADrawingSurface_LineEndStyle(This,id)	\
    (This)->lpVtbl -> LineEndStyle(This,id)

#define IDADrawingSurface_LineJoinStyle(This,id)	\
    (This)->lpVtbl -> LineJoinStyle(This,id)

#define IDADrawingSurface_BorderColor(This,clr)	\
    (This)->lpVtbl -> BorderColor(This,clr)

#define IDADrawingSurface_BorderWidth(This,w)	\
    (This)->lpVtbl -> BorderWidth(This,w)

#define IDADrawingSurface_BorderDashStyle(This,id)	\
    (This)->lpVtbl -> BorderDashStyle(This,id)

#define IDADrawingSurface_BorderEndStyle(This,obsolete)	\
    (This)->lpVtbl -> BorderEndStyle(This,obsolete)

#define IDADrawingSurface_BorderJoinStyle(This,id)	\
    (This)->lpVtbl -> BorderJoinStyle(This,id)

#define IDADrawingSurface_Font(This,FontFace,sizeInPoints,Bold,italic,underline,strikethrough)	\
    (This)->lpVtbl -> Font(This,FontFace,sizeInPoints,Bold,italic,underline,strikethrough)

#define IDADrawingSurface_TextureFill(This,obsolete1,obsolete2,obsolete3)	\
    (This)->lpVtbl -> TextureFill(This,obsolete1,obsolete2,obsolete3)

#define IDADrawingSurface_ImageFill(This,obsolete1,obsolete2,obsolete3)	\
    (This)->lpVtbl -> ImageFill(This,obsolete1,obsolete2,obsolete3)

#define IDADrawingSurface_FillTexture(This,img)	\
    (This)->lpVtbl -> FillTexture(This,img)

#define IDADrawingSurface_FillImage(This,img)	\
    (This)->lpVtbl -> FillImage(This,img)

#define IDADrawingSurface_FillStyle(This,ID)	\
    (This)->lpVtbl -> FillStyle(This,ID)

#define IDADrawingSurface_FillColor(This,foreground)	\
    (This)->lpVtbl -> FillColor(This,foreground)

#define IDADrawingSurface_SecondaryFillColor(This,val)	\
    (This)->lpVtbl -> SecondaryFillColor(This,val)

#define IDADrawingSurface_GradientShape(This,pts)	\
    (This)->lpVtbl -> GradientShape(This,pts)

#define IDADrawingSurface_GradientExtent(This,startx,starty,finishx,finishy)	\
    (This)->lpVtbl -> GradientExtent(This,startx,starty,finishx,finishy)

#define IDADrawingSurface_GradientExtentPoints(This,startColor,stopColor)	\
    (This)->lpVtbl -> GradientExtentPoints(This,startColor,stopColor)

#define IDADrawingSurface_GradientRolloffPower(This,power)	\
    (This)->lpVtbl -> GradientRolloffPower(This,power)

#define IDADrawingSurface_GradientRolloffPowerAnim(This,power)	\
    (This)->lpVtbl -> GradientRolloffPowerAnim(This,power)

#define IDADrawingSurface_FixedFillScale(This)	\
    (This)->lpVtbl -> FixedFillScale(This)

#define IDADrawingSurface_HorizontalFillScale(This)	\
    (This)->lpVtbl -> HorizontalFillScale(This)

#define IDADrawingSurface_VerticalFillScale(This)	\
    (This)->lpVtbl -> VerticalFillScale(This)

#define IDADrawingSurface_AutoSizeFillScale(This)	\
    (This)->lpVtbl -> AutoSizeFillScale(This)

#define IDADrawingSurface_PolylineEx(This,numPts,pts)	\
    (This)->lpVtbl -> PolylineEx(This,numPts,pts)

#define IDADrawingSurface_Polyline(This,v)	\
    (This)->lpVtbl -> Polyline(This,v)

#define IDADrawingSurface_PolygonEx(This,numPts,pts)	\
    (This)->lpVtbl -> PolygonEx(This,numPts,pts)

#define IDADrawingSurface_Polygon(This,v)	\
    (This)->lpVtbl -> Polygon(This,v)

#define IDADrawingSurface_LinePoints(This,p1,p2)	\
    (This)->lpVtbl -> LinePoints(This,p1,p2)

#define IDADrawingSurface_Line(This,startX,startY,endX,endY)	\
    (This)->lpVtbl -> Line(This,startX,startY,endX,endY)

#define IDADrawingSurface_ArcRadians(This,xPos,yPos,startAngle,endAngle,arcWidth,arcHeight)	\
    (This)->lpVtbl -> ArcRadians(This,xPos,yPos,startAngle,endAngle,arcWidth,arcHeight)

#define IDADrawingSurface_ArcDegrees(This,xPos,yPos,startAngle,endAngle,arcWidth,arcHeight)	\
    (This)->lpVtbl -> ArcDegrees(This,xPos,yPos,startAngle,endAngle,arcWidth,arcHeight)

#define IDADrawingSurface_Oval(This,xPos,yPos,w,h)	\
    (This)->lpVtbl -> Oval(This,xPos,yPos,w,h)

#define IDADrawingSurface_Rect(This,xPos,yPos,w,h)	\
    (This)->lpVtbl -> Rect(This,xPos,yPos,w,h)

#define IDADrawingSurface_RoundRect(This,xPos,yPos,w,h,arcWidth,arcHeight)	\
    (This)->lpVtbl -> RoundRect(This,xPos,yPos,w,h,arcWidth,arcHeight)

#define IDADrawingSurface_PieRadians(This,xPos,yPos,startAngle,endAngle,arcWidth,arcHeight)	\
    (This)->lpVtbl -> PieRadians(This,xPos,yPos,startAngle,endAngle,arcWidth,arcHeight)

#define IDADrawingSurface_PieDegrees(This,xPos,yPos,startAngle,endAngle,arcWidth,arcHeight)	\
    (This)->lpVtbl -> PieDegrees(This,xPos,yPos,startAngle,endAngle,arcWidth,arcHeight)

#define IDADrawingSurface_Text(This,str,xPos,yPos)	\
    (This)->lpVtbl -> Text(This,str,xPos,yPos)

#define IDADrawingSurface_TextPoint(This,str,point)	\
    (This)->lpVtbl -> TextPoint(This,str,point)

#define IDADrawingSurface_FillPath(This,path)	\
    (This)->lpVtbl -> FillPath(This,path)

#define IDADrawingSurface_DrawPath(This,path)	\
    (This)->lpVtbl -> DrawPath(This,path)

#define IDADrawingSurface_OverlayImage(This,img)	\
    (This)->lpVtbl -> OverlayImage(This,img)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IDADrawingSurface_get_Image_Proxy( 
    IDADrawingSurface * This,
    /* [retval][out] */ IDAImage **img);



/* [propput] */ HRESULT STDMETHODCALLTYPE IDADrawingSurface_put_LineStyle_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ IDALineStyle *ls);



/* [propput] */ HRESULT STDMETHODCALLTYPE IDADrawingSurface_put_BorderStyle_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ IDALineStyle *bs);



/* [propput] */ HRESULT STDMETHODCALLTYPE IDADrawingSurface_put_FontStyle_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ IDAFontStyle *fs);



/* [propput] */ HRESULT STDMETHODCALLTYPE IDADrawingSurface_put_ClipMatte_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ IDAMatte *matte);



/* [propput] */ HRESULT STDMETHODCALLTYPE IDADrawingSurface_put_MouseEventsEnabled_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ VARIANT_BOOL on);



/* [propput] */ HRESULT STDMETHODCALLTYPE IDADrawingSurface_put_HatchFillTransparent_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ VARIANT_BOOL fillOff);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDADrawingSurface_get_LocalContextImage_Proxy( 
    IDADrawingSurface * This,
    /* [retval][out] */ IDAImage **img);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_Reset_Proxy( 
    IDADrawingSurface * This);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_Clear_Proxy( 
    IDADrawingSurface * This);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_SaveGraphicsState_Proxy( 
    IDADrawingSurface * This);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_RestoreGraphicsState_Proxy( 
    IDADrawingSurface * This);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_Opacity_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ double opac);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_OpacityAnim_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ IDANumber *opac);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_Crop_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ double lowerLeftX,
    /* [in] */ double lowerLeftY,
    /* [in] */ double upperRightX,
    /* [in] */ double upperRightY);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_CropPoints_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ IDAPoint2 *min,
    /* [in] */ IDAPoint2 *max);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_Transform_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ IDATransform2 *xform);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_LineColor_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ IDAColor *clr);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_LineWidth_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ double w);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_LineDashStyle_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ DA_DASH_STYLE id);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_LineEndStyle_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ DA_END_STYLE id);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_LineJoinStyle_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ DA_JOIN_STYLE id);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_BorderColor_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ IDAColor *clr);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_BorderWidth_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ double w);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_BorderDashStyle_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ DA_DASH_STYLE id);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_BorderEndStyle_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ DA_END_STYLE obsolete);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_BorderJoinStyle_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ DA_JOIN_STYLE id);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_Font_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ BSTR FontFace,
    /* [in] */ LONG sizeInPoints,
    /* [in] */ VARIANT_BOOL Bold,
    /* [in] */ VARIANT_BOOL italic,
    /* [in] */ VARIANT_BOOL underline,
    /* [in] */ VARIANT_BOOL strikethrough);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_TextureFill_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ IDAImage *obsolete1,
    /* [in] */ double obsolete2,
    /* [in] */ double obsolete3);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_ImageFill_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ IDAImage *obsolete1,
    /* [in] */ double obsolete2,
    /* [in] */ double obsolete3);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_FillTexture_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ IDAImage *img);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_FillImage_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ IDAImage *img);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_FillStyle_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ int ID);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_FillColor_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ IDAColor *foreground);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_SecondaryFillColor_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ IDAColor *val);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_GradientShape_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ VARIANT pts);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_GradientExtent_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ double startx,
    /* [in] */ double starty,
    /* [in] */ double finishx,
    /* [in] */ double finishy);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_GradientExtentPoints_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ IDAPoint2 *startColor,
    /* [in] */ IDAPoint2 *stopColor);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_GradientRolloffPower_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ double power);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_GradientRolloffPowerAnim_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ IDANumber *power);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_FixedFillScale_Proxy( 
    IDADrawingSurface * This);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_HorizontalFillScale_Proxy( 
    IDADrawingSurface * This);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_VerticalFillScale_Proxy( 
    IDADrawingSurface * This);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_AutoSizeFillScale_Proxy( 
    IDADrawingSurface * This);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_PolylineEx_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ LONG numPts,
    /* [size_is][in] */ IDAPoint2 *pts[  ]);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_Polyline_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ VARIANT v);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_PolygonEx_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ LONG numPts,
    /* [size_is][in] */ IDAPoint2 *pts[  ]);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_Polygon_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ VARIANT v);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_LinePoints_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ IDAPoint2 *p1,
    /* [in] */ IDAPoint2 *p2);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_Line_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ double startX,
    /* [in] */ double startY,
    /* [in] */ double endX,
    /* [in] */ double endY);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_ArcRadians_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ double xPos,
    /* [in] */ double yPos,
    /* [in] */ double startAngle,
    /* [in] */ double endAngle,
    /* [in] */ double arcWidth,
    /* [in] */ double arcHeight);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_ArcDegrees_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ double xPos,
    /* [in] */ double yPos,
    /* [in] */ double startAngle,
    /* [in] */ double endAngle,
    /* [in] */ double arcWidth,
    /* [in] */ double arcHeight);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_Oval_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ double xPos,
    /* [in] */ double yPos,
    /* [in] */ double w,
    /* [in] */ double h);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_Rect_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ double xPos,
    /* [in] */ double yPos,
    /* [in] */ double w,
    /* [in] */ double h);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_RoundRect_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ double xPos,
    /* [in] */ double yPos,
    /* [in] */ double w,
    /* [in] */ double h,
    /* [in] */ double arcWidth,
    /* [in] */ double arcHeight);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_PieRadians_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ double xPos,
    /* [in] */ double yPos,
    /* [in] */ double startAngle,
    /* [in] */ double endAngle,
    /* [in] */ double arcWidth,
    /* [in] */ double arcHeight);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_PieDegrees_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ double xPos,
    /* [in] */ double yPos,
    /* [in] */ double startAngle,
    /* [in] */ double endAngle,
    /* [in] */ double arcWidth,
    /* [in] */ double arcHeight);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_Text_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ BSTR str,
    /* [in] */ double xPos,
    /* [in] */ double yPos);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_TextPoint_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ BSTR str,
    /* [in] */ IDAPoint2 *point);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_FillPath_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ IDAPath2 *path);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_DrawPath_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ IDAPath2 *path);



HRESULT STDMETHODCALLTYPE IDADrawingSurface_OverlayImage_Proxy( 
    IDADrawingSurface * This,
    /* [in] */ IDAImage *img);




#endif 	/* __IDADrawingSurface_INTERFACE_DEFINED__ */


#ifndef __IDAPickableResult_INTERFACE_DEFINED__
#define __IDAPickableResult_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDAPickableResult
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDAPickableResult;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("4A933703-E36F-11d0-9B99-00C04FC2F51D")
    IDAPickableResult : public IDispatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Image( 
            /* [retval][out] */ IDAImage **ppImage) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Geometry( 
            /* [retval][out] */ IDAGeometry **ppGeometry) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PickEvent( 
            /* [retval][out] */ IDAEvent **ppPickEvent) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDAPickableResultVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDAPickableResult * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDAPickableResult * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDAPickableResult * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDAPickableResult * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDAPickableResult * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDAPickableResult * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDAPickableResult * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Image )( 
            IDAPickableResult * This,
            /* [retval][out] */ IDAImage **ppImage);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Geometry )( 
            IDAPickableResult * This,
            /* [retval][out] */ IDAGeometry **ppGeometry);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PickEvent )( 
            IDAPickableResult * This,
            /* [retval][out] */ IDAEvent **ppPickEvent);
        
        END_INTERFACE
    } IDAPickableResultVtbl;

    interface IDAPickableResult
    {
        CONST_VTBL struct IDAPickableResultVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDAPickableResult_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDAPickableResult_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDAPickableResult_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDAPickableResult_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDAPickableResult_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDAPickableResult_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDAPickableResult_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDAPickableResult_get_Image(This,ppImage)	\
    (This)->lpVtbl -> get_Image(This,ppImage)

#define IDAPickableResult_get_Geometry(This,ppGeometry)	\
    (This)->lpVtbl -> get_Geometry(This,ppGeometry)

#define IDAPickableResult_get_PickEvent(This,ppPickEvent)	\
    (This)->lpVtbl -> get_PickEvent(This,ppPickEvent)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IDAPickableResult_get_Image_Proxy( 
    IDAPickableResult * This,
    /* [retval][out] */ IDAImage **ppImage);



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IDAPickableResult_get_Geometry_Proxy( 
    IDAPickableResult * This,
    /* [retval][out] */ IDAGeometry **ppGeometry);



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IDAPickableResult_get_PickEvent_Proxy( 
    IDAPickableResult * This,
    /* [retval][out] */ IDAEvent **ppPickEvent);




#endif 	/* __IDAPickableResult_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_DABehavior;

#ifdef __cplusplus

class DECLSPEC_UUID("283807B8-2C60-11d0-A31D-00AA00B92C03")
DABehavior;
#endif

#ifndef __IDAUntilNotifier_INTERFACE_DEFINED__
#define __IDAUntilNotifier_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDAUntilNotifier
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDAUntilNotifier;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("3F3DA01A-4705-11d0-8710-00C04FC29D46")
    IDAUntilNotifier : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Notify( 
            /* [in] */ IDABehavior *eventData,
            /* [in] */ IDABehavior *curRunningBvr,
            /* [in] */ IDAView *curView,
            /* [retval][out] */ IDABehavior **ppBvr) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDAUntilNotifierVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDAUntilNotifier * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDAUntilNotifier * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDAUntilNotifier * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDAUntilNotifier * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDAUntilNotifier * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDAUntilNotifier * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDAUntilNotifier * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *Notify )( 
            IDAUntilNotifier * This,
            /* [in] */ IDABehavior *eventData,
            /* [in] */ IDABehavior *curRunningBvr,
            /* [in] */ IDAView *curView,
            /* [retval][out] */ IDABehavior **ppBvr);
        
        END_INTERFACE
    } IDAUntilNotifierVtbl;

    interface IDAUntilNotifier
    {
        CONST_VTBL struct IDAUntilNotifierVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDAUntilNotifier_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDAUntilNotifier_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDAUntilNotifier_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDAUntilNotifier_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDAUntilNotifier_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDAUntilNotifier_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDAUntilNotifier_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDAUntilNotifier_Notify(This,eventData,curRunningBvr,curView,ppBvr)	\
    (This)->lpVtbl -> Notify(This,eventData,curRunningBvr,curView,ppBvr)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDAUntilNotifier_Notify_Proxy( 
    IDAUntilNotifier * This,
    /* [in] */ IDABehavior *eventData,
    /* [in] */ IDABehavior *curRunningBvr,
    /* [in] */ IDAView *curView,
    /* [retval][out] */ IDABehavior **ppBvr);




#endif 	/* __IDAUntilNotifier_INTERFACE_DEFINED__ */


#ifndef __IDABoolean_INTERFACE_DEFINED__
#define __IDABoolean_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDABoolean
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][hidden][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDABoolean;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("C46C1BC0-3C52-11d0-9200-848C1D000000")
    IDABoolean : public IDABehavior
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Extract( 
            /* [retval][out] */ VARIANT_BOOL *ret_0) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDABooleanVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDABoolean * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDABoolean * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDABoolean * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDABoolean * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDABoolean * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDABoolean * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDABoolean * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassName )( 
            IDABoolean * This,
            /* [retval][out] */ BSTR *pClassName);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            IDABoolean * This,
            /* [in] */ IDABehavior *toBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Importance )( 
            IDABoolean * This,
            /* [in] */ double relativeImportance,
            /* [retval][out] */ IDABehavior **ppBvr);
        
        HRESULT ( STDMETHODCALLTYPE *RunOnce )( 
            IDABoolean * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SubstituteTime )( 
            IDABoolean * This,
            /* [in] */ IDANumber *xform,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchTo )( 
            IDABoolean * This,
            /* [in] */ IDABehavior *switchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToNumber )( 
            IDABoolean * This,
            /* [in] */ double numToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToString )( 
            IDABoolean * This,
            /* [in] */ BSTR strToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *Hook )( 
            IDABoolean * This,
            /* [in] */ IDABvrHook *notifier,
            /* [retval][out] */ IDABehavior **pBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Duration )( 
            IDABoolean * This,
            /* [in] */ double duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *DurationAnim )( 
            IDABoolean * This,
            /* [in] */ IDANumber *duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Repeat )( 
            IDABoolean * This,
            /* [in] */ LONG count,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *RepeatForever )( 
            IDABoolean * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *IsReady )( 
            IDABoolean * This,
            /* [in] */ VARIANT_BOOL bBlock,
            /* [retval][out] */ VARIANT_BOOL *b);
        
        HRESULT ( STDMETHODCALLTYPE *Extract )( 
            IDABoolean * This,
            /* [retval][out] */ VARIANT_BOOL *ret_0);
        
        END_INTERFACE
    } IDABooleanVtbl;

    interface IDABoolean
    {
        CONST_VTBL struct IDABooleanVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDABoolean_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDABoolean_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDABoolean_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDABoolean_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDABoolean_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDABoolean_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDABoolean_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDABoolean_GetClassName(This,pClassName)	\
    (This)->lpVtbl -> GetClassName(This,pClassName)

#define IDABoolean_Init(This,toBvr)	\
    (This)->lpVtbl -> Init(This,toBvr)

#define IDABoolean_Importance(This,relativeImportance,ppBvr)	\
    (This)->lpVtbl -> Importance(This,relativeImportance,ppBvr)

#define IDABoolean_RunOnce(This,bvr)	\
    (This)->lpVtbl -> RunOnce(This,bvr)

#define IDABoolean_SubstituteTime(This,xform,bvr)	\
    (This)->lpVtbl -> SubstituteTime(This,xform,bvr)

#define IDABoolean_SwitchTo(This,switchTo)	\
    (This)->lpVtbl -> SwitchTo(This,switchTo)

#define IDABoolean_SwitchToNumber(This,numToSwitchTo)	\
    (This)->lpVtbl -> SwitchToNumber(This,numToSwitchTo)

#define IDABoolean_SwitchToString(This,strToSwitchTo)	\
    (This)->lpVtbl -> SwitchToString(This,strToSwitchTo)

#define IDABoolean_Hook(This,notifier,pBvr)	\
    (This)->lpVtbl -> Hook(This,notifier,pBvr)

#define IDABoolean_Duration(This,duration,bvr)	\
    (This)->lpVtbl -> Duration(This,duration,bvr)

#define IDABoolean_DurationAnim(This,duration,bvr)	\
    (This)->lpVtbl -> DurationAnim(This,duration,bvr)

#define IDABoolean_Repeat(This,count,bvr)	\
    (This)->lpVtbl -> Repeat(This,count,bvr)

#define IDABoolean_RepeatForever(This,bvr)	\
    (This)->lpVtbl -> RepeatForever(This,bvr)

#define IDABoolean_IsReady(This,bBlock,b)	\
    (This)->lpVtbl -> IsReady(This,bBlock,b)


#define IDABoolean_Extract(This,ret_0)	\
    (This)->lpVtbl -> Extract(This,ret_0)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDABoolean_Extract_Proxy( 
    IDABoolean * This,
    /* [retval][out] */ VARIANT_BOOL *ret_0);




#endif 	/* __IDABoolean_INTERFACE_DEFINED__ */


#ifndef __IDACamera_INTERFACE_DEFINED__
#define __IDACamera_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDACamera
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][hidden][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDACamera;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("C46C1BE1-3C52-11d0-9200-848C1D000000")
    IDACamera : public IDABehavior
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Transform( 
            /* [in] */ IDATransform3 *xf_0,
            /* [retval][out] */ IDACamera **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Depth( 
            /* [in] */ double depth_0,
            /* [retval][out] */ IDACamera **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DepthAnim( 
            /* [in] */ IDANumber *depth_0,
            /* [retval][out] */ IDACamera **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DepthResolution( 
            /* [in] */ double resolution_0,
            /* [retval][out] */ IDACamera **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DepthResolutionAnim( 
            /* [in] */ IDANumber *resolution_0,
            /* [retval][out] */ IDACamera **ret_1) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDACameraVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDACamera * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDACamera * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDACamera * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDACamera * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDACamera * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDACamera * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDACamera * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassName )( 
            IDACamera * This,
            /* [retval][out] */ BSTR *pClassName);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            IDACamera * This,
            /* [in] */ IDABehavior *toBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Importance )( 
            IDACamera * This,
            /* [in] */ double relativeImportance,
            /* [retval][out] */ IDABehavior **ppBvr);
        
        HRESULT ( STDMETHODCALLTYPE *RunOnce )( 
            IDACamera * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SubstituteTime )( 
            IDACamera * This,
            /* [in] */ IDANumber *xform,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchTo )( 
            IDACamera * This,
            /* [in] */ IDABehavior *switchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToNumber )( 
            IDACamera * This,
            /* [in] */ double numToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToString )( 
            IDACamera * This,
            /* [in] */ BSTR strToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *Hook )( 
            IDACamera * This,
            /* [in] */ IDABvrHook *notifier,
            /* [retval][out] */ IDABehavior **pBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Duration )( 
            IDACamera * This,
            /* [in] */ double duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *DurationAnim )( 
            IDACamera * This,
            /* [in] */ IDANumber *duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Repeat )( 
            IDACamera * This,
            /* [in] */ LONG count,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *RepeatForever )( 
            IDACamera * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *IsReady )( 
            IDACamera * This,
            /* [in] */ VARIANT_BOOL bBlock,
            /* [retval][out] */ VARIANT_BOOL *b);
        
        HRESULT ( STDMETHODCALLTYPE *Transform )( 
            IDACamera * This,
            /* [in] */ IDATransform3 *xf_0,
            /* [retval][out] */ IDACamera **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Depth )( 
            IDACamera * This,
            /* [in] */ double depth_0,
            /* [retval][out] */ IDACamera **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *DepthAnim )( 
            IDACamera * This,
            /* [in] */ IDANumber *depth_0,
            /* [retval][out] */ IDACamera **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *DepthResolution )( 
            IDACamera * This,
            /* [in] */ double resolution_0,
            /* [retval][out] */ IDACamera **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *DepthResolutionAnim )( 
            IDACamera * This,
            /* [in] */ IDANumber *resolution_0,
            /* [retval][out] */ IDACamera **ret_1);
        
        END_INTERFACE
    } IDACameraVtbl;

    interface IDACamera
    {
        CONST_VTBL struct IDACameraVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDACamera_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDACamera_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDACamera_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDACamera_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDACamera_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDACamera_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDACamera_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDACamera_GetClassName(This,pClassName)	\
    (This)->lpVtbl -> GetClassName(This,pClassName)

#define IDACamera_Init(This,toBvr)	\
    (This)->lpVtbl -> Init(This,toBvr)

#define IDACamera_Importance(This,relativeImportance,ppBvr)	\
    (This)->lpVtbl -> Importance(This,relativeImportance,ppBvr)

#define IDACamera_RunOnce(This,bvr)	\
    (This)->lpVtbl -> RunOnce(This,bvr)

#define IDACamera_SubstituteTime(This,xform,bvr)	\
    (This)->lpVtbl -> SubstituteTime(This,xform,bvr)

#define IDACamera_SwitchTo(This,switchTo)	\
    (This)->lpVtbl -> SwitchTo(This,switchTo)

#define IDACamera_SwitchToNumber(This,numToSwitchTo)	\
    (This)->lpVtbl -> SwitchToNumber(This,numToSwitchTo)

#define IDACamera_SwitchToString(This,strToSwitchTo)	\
    (This)->lpVtbl -> SwitchToString(This,strToSwitchTo)

#define IDACamera_Hook(This,notifier,pBvr)	\
    (This)->lpVtbl -> Hook(This,notifier,pBvr)

#define IDACamera_Duration(This,duration,bvr)	\
    (This)->lpVtbl -> Duration(This,duration,bvr)

#define IDACamera_DurationAnim(This,duration,bvr)	\
    (This)->lpVtbl -> DurationAnim(This,duration,bvr)

#define IDACamera_Repeat(This,count,bvr)	\
    (This)->lpVtbl -> Repeat(This,count,bvr)

#define IDACamera_RepeatForever(This,bvr)	\
    (This)->lpVtbl -> RepeatForever(This,bvr)

#define IDACamera_IsReady(This,bBlock,b)	\
    (This)->lpVtbl -> IsReady(This,bBlock,b)


#define IDACamera_Transform(This,xf_0,ret_1)	\
    (This)->lpVtbl -> Transform(This,xf_0,ret_1)

#define IDACamera_Depth(This,depth_0,ret_1)	\
    (This)->lpVtbl -> Depth(This,depth_0,ret_1)

#define IDACamera_DepthAnim(This,depth_0,ret_1)	\
    (This)->lpVtbl -> DepthAnim(This,depth_0,ret_1)

#define IDACamera_DepthResolution(This,resolution_0,ret_1)	\
    (This)->lpVtbl -> DepthResolution(This,resolution_0,ret_1)

#define IDACamera_DepthResolutionAnim(This,resolution_0,ret_1)	\
    (This)->lpVtbl -> DepthResolutionAnim(This,resolution_0,ret_1)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDACamera_Transform_Proxy( 
    IDACamera * This,
    /* [in] */ IDATransform3 *xf_0,
    /* [retval][out] */ IDACamera **ret_1);



HRESULT STDMETHODCALLTYPE IDACamera_Depth_Proxy( 
    IDACamera * This,
    /* [in] */ double depth_0,
    /* [retval][out] */ IDACamera **ret_1);



HRESULT STDMETHODCALLTYPE IDACamera_DepthAnim_Proxy( 
    IDACamera * This,
    /* [in] */ IDANumber *depth_0,
    /* [retval][out] */ IDACamera **ret_1);



HRESULT STDMETHODCALLTYPE IDACamera_DepthResolution_Proxy( 
    IDACamera * This,
    /* [in] */ double resolution_0,
    /* [retval][out] */ IDACamera **ret_1);



HRESULT STDMETHODCALLTYPE IDACamera_DepthResolutionAnim_Proxy( 
    IDACamera * This,
    /* [in] */ IDANumber *resolution_0,
    /* [retval][out] */ IDACamera **ret_1);




#endif 	/* __IDACamera_INTERFACE_DEFINED__ */


#ifndef __IDAColor_INTERFACE_DEFINED__
#define __IDAColor_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDAColor
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][hidden][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDAColor;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("C46C1BC5-3C52-11d0-9200-848C1D000000")
    IDAColor : public IDABehavior
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Red( 
            /* [retval][out] */ IDANumber **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Green( 
            /* [retval][out] */ IDANumber **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Blue( 
            /* [retval][out] */ IDANumber **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Hue( 
            /* [retval][out] */ IDANumber **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Saturation( 
            /* [retval][out] */ IDANumber **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Lightness( 
            /* [retval][out] */ IDANumber **ret_0) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDAColorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDAColor * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDAColor * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDAColor * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDAColor * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDAColor * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDAColor * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDAColor * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassName )( 
            IDAColor * This,
            /* [retval][out] */ BSTR *pClassName);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            IDAColor * This,
            /* [in] */ IDABehavior *toBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Importance )( 
            IDAColor * This,
            /* [in] */ double relativeImportance,
            /* [retval][out] */ IDABehavior **ppBvr);
        
        HRESULT ( STDMETHODCALLTYPE *RunOnce )( 
            IDAColor * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SubstituteTime )( 
            IDAColor * This,
            /* [in] */ IDANumber *xform,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchTo )( 
            IDAColor * This,
            /* [in] */ IDABehavior *switchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToNumber )( 
            IDAColor * This,
            /* [in] */ double numToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToString )( 
            IDAColor * This,
            /* [in] */ BSTR strToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *Hook )( 
            IDAColor * This,
            /* [in] */ IDABvrHook *notifier,
            /* [retval][out] */ IDABehavior **pBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Duration )( 
            IDAColor * This,
            /* [in] */ double duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *DurationAnim )( 
            IDAColor * This,
            /* [in] */ IDANumber *duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Repeat )( 
            IDAColor * This,
            /* [in] */ LONG count,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *RepeatForever )( 
            IDAColor * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *IsReady )( 
            IDAColor * This,
            /* [in] */ VARIANT_BOOL bBlock,
            /* [retval][out] */ VARIANT_BOOL *b);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Red )( 
            IDAColor * This,
            /* [retval][out] */ IDANumber **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Green )( 
            IDAColor * This,
            /* [retval][out] */ IDANumber **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Blue )( 
            IDAColor * This,
            /* [retval][out] */ IDANumber **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Hue )( 
            IDAColor * This,
            /* [retval][out] */ IDANumber **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Saturation )( 
            IDAColor * This,
            /* [retval][out] */ IDANumber **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Lightness )( 
            IDAColor * This,
            /* [retval][out] */ IDANumber **ret_0);
        
        END_INTERFACE
    } IDAColorVtbl;

    interface IDAColor
    {
        CONST_VTBL struct IDAColorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDAColor_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDAColor_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDAColor_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDAColor_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDAColor_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDAColor_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDAColor_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDAColor_GetClassName(This,pClassName)	\
    (This)->lpVtbl -> GetClassName(This,pClassName)

#define IDAColor_Init(This,toBvr)	\
    (This)->lpVtbl -> Init(This,toBvr)

#define IDAColor_Importance(This,relativeImportance,ppBvr)	\
    (This)->lpVtbl -> Importance(This,relativeImportance,ppBvr)

#define IDAColor_RunOnce(This,bvr)	\
    (This)->lpVtbl -> RunOnce(This,bvr)

#define IDAColor_SubstituteTime(This,xform,bvr)	\
    (This)->lpVtbl -> SubstituteTime(This,xform,bvr)

#define IDAColor_SwitchTo(This,switchTo)	\
    (This)->lpVtbl -> SwitchTo(This,switchTo)

#define IDAColor_SwitchToNumber(This,numToSwitchTo)	\
    (This)->lpVtbl -> SwitchToNumber(This,numToSwitchTo)

#define IDAColor_SwitchToString(This,strToSwitchTo)	\
    (This)->lpVtbl -> SwitchToString(This,strToSwitchTo)

#define IDAColor_Hook(This,notifier,pBvr)	\
    (This)->lpVtbl -> Hook(This,notifier,pBvr)

#define IDAColor_Duration(This,duration,bvr)	\
    (This)->lpVtbl -> Duration(This,duration,bvr)

#define IDAColor_DurationAnim(This,duration,bvr)	\
    (This)->lpVtbl -> DurationAnim(This,duration,bvr)

#define IDAColor_Repeat(This,count,bvr)	\
    (This)->lpVtbl -> Repeat(This,count,bvr)

#define IDAColor_RepeatForever(This,bvr)	\
    (This)->lpVtbl -> RepeatForever(This,bvr)

#define IDAColor_IsReady(This,bBlock,b)	\
    (This)->lpVtbl -> IsReady(This,bBlock,b)


#define IDAColor_get_Red(This,ret_0)	\
    (This)->lpVtbl -> get_Red(This,ret_0)

#define IDAColor_get_Green(This,ret_0)	\
    (This)->lpVtbl -> get_Green(This,ret_0)

#define IDAColor_get_Blue(This,ret_0)	\
    (This)->lpVtbl -> get_Blue(This,ret_0)

#define IDAColor_get_Hue(This,ret_0)	\
    (This)->lpVtbl -> get_Hue(This,ret_0)

#define IDAColor_get_Saturation(This,ret_0)	\
    (This)->lpVtbl -> get_Saturation(This,ret_0)

#define IDAColor_get_Lightness(This,ret_0)	\
    (This)->lpVtbl -> get_Lightness(This,ret_0)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAColor_get_Red_Proxy( 
    IDAColor * This,
    /* [retval][out] */ IDANumber **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAColor_get_Green_Proxy( 
    IDAColor * This,
    /* [retval][out] */ IDANumber **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAColor_get_Blue_Proxy( 
    IDAColor * This,
    /* [retval][out] */ IDANumber **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAColor_get_Hue_Proxy( 
    IDAColor * This,
    /* [retval][out] */ IDANumber **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAColor_get_Saturation_Proxy( 
    IDAColor * This,
    /* [retval][out] */ IDANumber **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAColor_get_Lightness_Proxy( 
    IDAColor * This,
    /* [retval][out] */ IDANumber **ret_0);




#endif 	/* __IDAColor_INTERFACE_DEFINED__ */


#ifndef __IDAGeometry_INTERFACE_DEFINED__
#define __IDAGeometry_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDAGeometry
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][hidden][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDAGeometry;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("C46C1BDF-3C52-11d0-9200-848C1D000000")
    IDAGeometry : public IDABehavior
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE RenderSound( 
            /* [in] */ IDAMicrophone *mic_0,
            /* [retval][out] */ IDASound **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Pickable( 
            /* [retval][out] */ IDAPickableResult **ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PickableOccluded( 
            /* [retval][out] */ IDAPickableResult **ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Undetectable( 
            /* [retval][out] */ IDAGeometry **ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EmissiveColor( 
            /* [in] */ IDAColor *col_0,
            /* [retval][out] */ IDAGeometry **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DiffuseColor( 
            /* [in] */ IDAColor *col_0,
            /* [retval][out] */ IDAGeometry **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SpecularColor( 
            /* [in] */ IDAColor *col_0,
            /* [retval][out] */ IDAGeometry **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SpecularExponent( 
            /* [in] */ double power_0,
            /* [retval][out] */ IDAGeometry **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SpecularExponentAnim( 
            /* [in] */ IDANumber *power_0,
            /* [retval][out] */ IDAGeometry **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Texture( 
            /* [in] */ IDAImage *texture_0,
            /* [retval][out] */ IDAGeometry **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Opacity( 
            /* [in] */ double level_0,
            /* [retval][out] */ IDAGeometry **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OpacityAnim( 
            /* [in] */ IDANumber *level_0,
            /* [retval][out] */ IDAGeometry **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Transform( 
            /* [in] */ IDATransform3 *xf_0,
            /* [retval][out] */ IDAGeometry **ret_1) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_BoundingBox( 
            /* [retval][out] */ IDABbox3 **ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Render( 
            /* [in] */ IDACamera *cam_0,
            /* [retval][out] */ IDAImage **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LightColor( 
            /* [in] */ IDAColor *color_0,
            /* [retval][out] */ IDAGeometry **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LightAttenuationAnim( 
            /* [in] */ IDANumber *constant_0,
            /* [in] */ IDANumber *linear_1,
            /* [in] */ IDANumber *quadratic_2,
            /* [retval][out] */ IDAGeometry **ret_3) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LightAttenuation( 
            /* [in] */ double constant_0,
            /* [in] */ double linear_1,
            /* [in] */ double quadratic_2,
            /* [retval][out] */ IDAGeometry **ret_3) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDAGeometryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDAGeometry * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDAGeometry * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDAGeometry * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDAGeometry * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDAGeometry * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDAGeometry * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDAGeometry * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassName )( 
            IDAGeometry * This,
            /* [retval][out] */ BSTR *pClassName);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            IDAGeometry * This,
            /* [in] */ IDABehavior *toBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Importance )( 
            IDAGeometry * This,
            /* [in] */ double relativeImportance,
            /* [retval][out] */ IDABehavior **ppBvr);
        
        HRESULT ( STDMETHODCALLTYPE *RunOnce )( 
            IDAGeometry * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SubstituteTime )( 
            IDAGeometry * This,
            /* [in] */ IDANumber *xform,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchTo )( 
            IDAGeometry * This,
            /* [in] */ IDABehavior *switchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToNumber )( 
            IDAGeometry * This,
            /* [in] */ double numToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToString )( 
            IDAGeometry * This,
            /* [in] */ BSTR strToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *Hook )( 
            IDAGeometry * This,
            /* [in] */ IDABvrHook *notifier,
            /* [retval][out] */ IDABehavior **pBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Duration )( 
            IDAGeometry * This,
            /* [in] */ double duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *DurationAnim )( 
            IDAGeometry * This,
            /* [in] */ IDANumber *duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Repeat )( 
            IDAGeometry * This,
            /* [in] */ LONG count,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *RepeatForever )( 
            IDAGeometry * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *IsReady )( 
            IDAGeometry * This,
            /* [in] */ VARIANT_BOOL bBlock,
            /* [retval][out] */ VARIANT_BOOL *b);
        
        HRESULT ( STDMETHODCALLTYPE *RenderSound )( 
            IDAGeometry * This,
            /* [in] */ IDAMicrophone *mic_0,
            /* [retval][out] */ IDASound **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Pickable )( 
            IDAGeometry * This,
            /* [retval][out] */ IDAPickableResult **ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *PickableOccluded )( 
            IDAGeometry * This,
            /* [retval][out] */ IDAPickableResult **ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *Undetectable )( 
            IDAGeometry * This,
            /* [retval][out] */ IDAGeometry **ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *EmissiveColor )( 
            IDAGeometry * This,
            /* [in] */ IDAColor *col_0,
            /* [retval][out] */ IDAGeometry **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *DiffuseColor )( 
            IDAGeometry * This,
            /* [in] */ IDAColor *col_0,
            /* [retval][out] */ IDAGeometry **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *SpecularColor )( 
            IDAGeometry * This,
            /* [in] */ IDAColor *col_0,
            /* [retval][out] */ IDAGeometry **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *SpecularExponent )( 
            IDAGeometry * This,
            /* [in] */ double power_0,
            /* [retval][out] */ IDAGeometry **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *SpecularExponentAnim )( 
            IDAGeometry * This,
            /* [in] */ IDANumber *power_0,
            /* [retval][out] */ IDAGeometry **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Texture )( 
            IDAGeometry * This,
            /* [in] */ IDAImage *texture_0,
            /* [retval][out] */ IDAGeometry **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Opacity )( 
            IDAGeometry * This,
            /* [in] */ double level_0,
            /* [retval][out] */ IDAGeometry **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *OpacityAnim )( 
            IDAGeometry * This,
            /* [in] */ IDANumber *level_0,
            /* [retval][out] */ IDAGeometry **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Transform )( 
            IDAGeometry * This,
            /* [in] */ IDATransform3 *xf_0,
            /* [retval][out] */ IDAGeometry **ret_1);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_BoundingBox )( 
            IDAGeometry * This,
            /* [retval][out] */ IDABbox3 **ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *Render )( 
            IDAGeometry * This,
            /* [in] */ IDACamera *cam_0,
            /* [retval][out] */ IDAImage **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *LightColor )( 
            IDAGeometry * This,
            /* [in] */ IDAColor *color_0,
            /* [retval][out] */ IDAGeometry **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *LightAttenuationAnim )( 
            IDAGeometry * This,
            /* [in] */ IDANumber *constant_0,
            /* [in] */ IDANumber *linear_1,
            /* [in] */ IDANumber *quadratic_2,
            /* [retval][out] */ IDAGeometry **ret_3);
        
        HRESULT ( STDMETHODCALLTYPE *LightAttenuation )( 
            IDAGeometry * This,
            /* [in] */ double constant_0,
            /* [in] */ double linear_1,
            /* [in] */ double quadratic_2,
            /* [retval][out] */ IDAGeometry **ret_3);
        
        END_INTERFACE
    } IDAGeometryVtbl;

    interface IDAGeometry
    {
        CONST_VTBL struct IDAGeometryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDAGeometry_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDAGeometry_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDAGeometry_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDAGeometry_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDAGeometry_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDAGeometry_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDAGeometry_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDAGeometry_GetClassName(This,pClassName)	\
    (This)->lpVtbl -> GetClassName(This,pClassName)

#define IDAGeometry_Init(This,toBvr)	\
    (This)->lpVtbl -> Init(This,toBvr)

#define IDAGeometry_Importance(This,relativeImportance,ppBvr)	\
    (This)->lpVtbl -> Importance(This,relativeImportance,ppBvr)

#define IDAGeometry_RunOnce(This,bvr)	\
    (This)->lpVtbl -> RunOnce(This,bvr)

#define IDAGeometry_SubstituteTime(This,xform,bvr)	\
    (This)->lpVtbl -> SubstituteTime(This,xform,bvr)

#define IDAGeometry_SwitchTo(This,switchTo)	\
    (This)->lpVtbl -> SwitchTo(This,switchTo)

#define IDAGeometry_SwitchToNumber(This,numToSwitchTo)	\
    (This)->lpVtbl -> SwitchToNumber(This,numToSwitchTo)

#define IDAGeometry_SwitchToString(This,strToSwitchTo)	\
    (This)->lpVtbl -> SwitchToString(This,strToSwitchTo)

#define IDAGeometry_Hook(This,notifier,pBvr)	\
    (This)->lpVtbl -> Hook(This,notifier,pBvr)

#define IDAGeometry_Duration(This,duration,bvr)	\
    (This)->lpVtbl -> Duration(This,duration,bvr)

#define IDAGeometry_DurationAnim(This,duration,bvr)	\
    (This)->lpVtbl -> DurationAnim(This,duration,bvr)

#define IDAGeometry_Repeat(This,count,bvr)	\
    (This)->lpVtbl -> Repeat(This,count,bvr)

#define IDAGeometry_RepeatForever(This,bvr)	\
    (This)->lpVtbl -> RepeatForever(This,bvr)

#define IDAGeometry_IsReady(This,bBlock,b)	\
    (This)->lpVtbl -> IsReady(This,bBlock,b)


#define IDAGeometry_RenderSound(This,mic_0,ret_1)	\
    (This)->lpVtbl -> RenderSound(This,mic_0,ret_1)

#define IDAGeometry_Pickable(This,ret_0)	\
    (This)->lpVtbl -> Pickable(This,ret_0)

#define IDAGeometry_PickableOccluded(This,ret_0)	\
    (This)->lpVtbl -> PickableOccluded(This,ret_0)

#define IDAGeometry_Undetectable(This,ret_0)	\
    (This)->lpVtbl -> Undetectable(This,ret_0)

#define IDAGeometry_EmissiveColor(This,col_0,ret_1)	\
    (This)->lpVtbl -> EmissiveColor(This,col_0,ret_1)

#define IDAGeometry_DiffuseColor(This,col_0,ret_1)	\
    (This)->lpVtbl -> DiffuseColor(This,col_0,ret_1)

#define IDAGeometry_SpecularColor(This,col_0,ret_1)	\
    (This)->lpVtbl -> SpecularColor(This,col_0,ret_1)

#define IDAGeometry_SpecularExponent(This,power_0,ret_1)	\
    (This)->lpVtbl -> SpecularExponent(This,power_0,ret_1)

#define IDAGeometry_SpecularExponentAnim(This,power_0,ret_1)	\
    (This)->lpVtbl -> SpecularExponentAnim(This,power_0,ret_1)

#define IDAGeometry_Texture(This,texture_0,ret_1)	\
    (This)->lpVtbl -> Texture(This,texture_0,ret_1)

#define IDAGeometry_Opacity(This,level_0,ret_1)	\
    (This)->lpVtbl -> Opacity(This,level_0,ret_1)

#define IDAGeometry_OpacityAnim(This,level_0,ret_1)	\
    (This)->lpVtbl -> OpacityAnim(This,level_0,ret_1)

#define IDAGeometry_Transform(This,xf_0,ret_1)	\
    (This)->lpVtbl -> Transform(This,xf_0,ret_1)

#define IDAGeometry_get_BoundingBox(This,ret_0)	\
    (This)->lpVtbl -> get_BoundingBox(This,ret_0)

#define IDAGeometry_Render(This,cam_0,ret_1)	\
    (This)->lpVtbl -> Render(This,cam_0,ret_1)

#define IDAGeometry_LightColor(This,color_0,ret_1)	\
    (This)->lpVtbl -> LightColor(This,color_0,ret_1)

#define IDAGeometry_LightAttenuationAnim(This,constant_0,linear_1,quadratic_2,ret_3)	\
    (This)->lpVtbl -> LightAttenuationAnim(This,constant_0,linear_1,quadratic_2,ret_3)

#define IDAGeometry_LightAttenuation(This,constant_0,linear_1,quadratic_2,ret_3)	\
    (This)->lpVtbl -> LightAttenuation(This,constant_0,linear_1,quadratic_2,ret_3)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDAGeometry_RenderSound_Proxy( 
    IDAGeometry * This,
    /* [in] */ IDAMicrophone *mic_0,
    /* [retval][out] */ IDASound **ret_1);



HRESULT STDMETHODCALLTYPE IDAGeometry_Pickable_Proxy( 
    IDAGeometry * This,
    /* [retval][out] */ IDAPickableResult **ret_0);



HRESULT STDMETHODCALLTYPE IDAGeometry_PickableOccluded_Proxy( 
    IDAGeometry * This,
    /* [retval][out] */ IDAPickableResult **ret_0);



HRESULT STDMETHODCALLTYPE IDAGeometry_Undetectable_Proxy( 
    IDAGeometry * This,
    /* [retval][out] */ IDAGeometry **ret_0);



HRESULT STDMETHODCALLTYPE IDAGeometry_EmissiveColor_Proxy( 
    IDAGeometry * This,
    /* [in] */ IDAColor *col_0,
    /* [retval][out] */ IDAGeometry **ret_1);



HRESULT STDMETHODCALLTYPE IDAGeometry_DiffuseColor_Proxy( 
    IDAGeometry * This,
    /* [in] */ IDAColor *col_0,
    /* [retval][out] */ IDAGeometry **ret_1);



HRESULT STDMETHODCALLTYPE IDAGeometry_SpecularColor_Proxy( 
    IDAGeometry * This,
    /* [in] */ IDAColor *col_0,
    /* [retval][out] */ IDAGeometry **ret_1);



HRESULT STDMETHODCALLTYPE IDAGeometry_SpecularExponent_Proxy( 
    IDAGeometry * This,
    /* [in] */ double power_0,
    /* [retval][out] */ IDAGeometry **ret_1);



HRESULT STDMETHODCALLTYPE IDAGeometry_SpecularExponentAnim_Proxy( 
    IDAGeometry * This,
    /* [in] */ IDANumber *power_0,
    /* [retval][out] */ IDAGeometry **ret_1);



HRESULT STDMETHODCALLTYPE IDAGeometry_Texture_Proxy( 
    IDAGeometry * This,
    /* [in] */ IDAImage *texture_0,
    /* [retval][out] */ IDAGeometry **ret_1);



HRESULT STDMETHODCALLTYPE IDAGeometry_Opacity_Proxy( 
    IDAGeometry * This,
    /* [in] */ double level_0,
    /* [retval][out] */ IDAGeometry **ret_1);



HRESULT STDMETHODCALLTYPE IDAGeometry_OpacityAnim_Proxy( 
    IDAGeometry * This,
    /* [in] */ IDANumber *level_0,
    /* [retval][out] */ IDAGeometry **ret_1);



HRESULT STDMETHODCALLTYPE IDAGeometry_Transform_Proxy( 
    IDAGeometry * This,
    /* [in] */ IDATransform3 *xf_0,
    /* [retval][out] */ IDAGeometry **ret_1);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAGeometry_get_BoundingBox_Proxy( 
    IDAGeometry * This,
    /* [retval][out] */ IDABbox3 **ret_0);



HRESULT STDMETHODCALLTYPE IDAGeometry_Render_Proxy( 
    IDAGeometry * This,
    /* [in] */ IDACamera *cam_0,
    /* [retval][out] */ IDAImage **ret_1);



HRESULT STDMETHODCALLTYPE IDAGeometry_LightColor_Proxy( 
    IDAGeometry * This,
    /* [in] */ IDAColor *color_0,
    /* [retval][out] */ IDAGeometry **ret_1);



HRESULT STDMETHODCALLTYPE IDAGeometry_LightAttenuationAnim_Proxy( 
    IDAGeometry * This,
    /* [in] */ IDANumber *constant_0,
    /* [in] */ IDANumber *linear_1,
    /* [in] */ IDANumber *quadratic_2,
    /* [retval][out] */ IDAGeometry **ret_3);



HRESULT STDMETHODCALLTYPE IDAGeometry_LightAttenuation_Proxy( 
    IDAGeometry * This,
    /* [in] */ double constant_0,
    /* [in] */ double linear_1,
    /* [in] */ double quadratic_2,
    /* [retval][out] */ IDAGeometry **ret_3);




#endif 	/* __IDAGeometry_INTERFACE_DEFINED__ */


#ifndef __IDAImage_INTERFACE_DEFINED__
#define __IDAImage_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDAImage
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][hidden][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDAImage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("C46C1BD3-3C52-11d0-9200-848C1D000000")
    IDAImage : public IDABehavior
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Pickable( 
            /* [retval][out] */ IDAPickableResult **ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PickableOccluded( 
            /* [retval][out] */ IDAPickableResult **ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ApplyBitmapEffect( 
            /* [in] */ IUnknown *effectToApply_0,
            /* [in] */ IDAEvent *firesWhenChanged_1,
            /* [retval][out] */ IDAImage **ret_2) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_BoundingBox( 
            /* [retval][out] */ IDABbox2 **ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Crop( 
            /* [in] */ IDAPoint2 *min_0,
            /* [in] */ IDAPoint2 *max_1,
            /* [retval][out] */ IDAImage **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Transform( 
            /* [in] */ IDATransform2 *xf_0,
            /* [retval][out] */ IDAImage **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OpacityAnim( 
            /* [in] */ IDANumber *opacity_0,
            /* [retval][out] */ IDAImage **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Opacity( 
            /* [in] */ double opacity_0,
            /* [retval][out] */ IDAImage **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Undetectable( 
            /* [retval][out] */ IDAImage **ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Tile( 
            /* [retval][out] */ IDAImage **ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clip( 
            /* [in] */ IDAMatte *m_0,
            /* [retval][out] */ IDAImage **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MapToUnitSquare( 
            /* [retval][out] */ IDAImage **ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ClipPolygonImageEx( 
            /* [in] */ LONG points_0size,
            /* [size_is][in] */ IDAPoint2 *points_0[  ],
            /* [retval][out] */ IDAImage **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ClipPolygonImage( 
            /* [in] */ VARIANT points_0,
            /* [retval][out] */ IDAImage **ret_1) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDAImageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDAImage * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDAImage * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDAImage * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDAImage * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDAImage * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDAImage * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDAImage * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassName )( 
            IDAImage * This,
            /* [retval][out] */ BSTR *pClassName);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            IDAImage * This,
            /* [in] */ IDABehavior *toBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Importance )( 
            IDAImage * This,
            /* [in] */ double relativeImportance,
            /* [retval][out] */ IDABehavior **ppBvr);
        
        HRESULT ( STDMETHODCALLTYPE *RunOnce )( 
            IDAImage * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SubstituteTime )( 
            IDAImage * This,
            /* [in] */ IDANumber *xform,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchTo )( 
            IDAImage * This,
            /* [in] */ IDABehavior *switchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToNumber )( 
            IDAImage * This,
            /* [in] */ double numToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToString )( 
            IDAImage * This,
            /* [in] */ BSTR strToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *Hook )( 
            IDAImage * This,
            /* [in] */ IDABvrHook *notifier,
            /* [retval][out] */ IDABehavior **pBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Duration )( 
            IDAImage * This,
            /* [in] */ double duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *DurationAnim )( 
            IDAImage * This,
            /* [in] */ IDANumber *duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Repeat )( 
            IDAImage * This,
            /* [in] */ LONG count,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *RepeatForever )( 
            IDAImage * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *IsReady )( 
            IDAImage * This,
            /* [in] */ VARIANT_BOOL bBlock,
            /* [retval][out] */ VARIANT_BOOL *b);
        
        HRESULT ( STDMETHODCALLTYPE *Pickable )( 
            IDAImage * This,
            /* [retval][out] */ IDAPickableResult **ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *PickableOccluded )( 
            IDAImage * This,
            /* [retval][out] */ IDAPickableResult **ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *ApplyBitmapEffect )( 
            IDAImage * This,
            /* [in] */ IUnknown *effectToApply_0,
            /* [in] */ IDAEvent *firesWhenChanged_1,
            /* [retval][out] */ IDAImage **ret_2);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_BoundingBox )( 
            IDAImage * This,
            /* [retval][out] */ IDABbox2 **ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *Crop )( 
            IDAImage * This,
            /* [in] */ IDAPoint2 *min_0,
            /* [in] */ IDAPoint2 *max_1,
            /* [retval][out] */ IDAImage **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *Transform )( 
            IDAImage * This,
            /* [in] */ IDATransform2 *xf_0,
            /* [retval][out] */ IDAImage **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *OpacityAnim )( 
            IDAImage * This,
            /* [in] */ IDANumber *opacity_0,
            /* [retval][out] */ IDAImage **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Opacity )( 
            IDAImage * This,
            /* [in] */ double opacity_0,
            /* [retval][out] */ IDAImage **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Undetectable )( 
            IDAImage * This,
            /* [retval][out] */ IDAImage **ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *Tile )( 
            IDAImage * This,
            /* [retval][out] */ IDAImage **ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *Clip )( 
            IDAImage * This,
            /* [in] */ IDAMatte *m_0,
            /* [retval][out] */ IDAImage **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *MapToUnitSquare )( 
            IDAImage * This,
            /* [retval][out] */ IDAImage **ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *ClipPolygonImageEx )( 
            IDAImage * This,
            /* [in] */ LONG points_0size,
            /* [size_is][in] */ IDAPoint2 *points_0[  ],
            /* [retval][out] */ IDAImage **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *ClipPolygonImage )( 
            IDAImage * This,
            /* [in] */ VARIANT points_0,
            /* [retval][out] */ IDAImage **ret_1);
        
        END_INTERFACE
    } IDAImageVtbl;

    interface IDAImage
    {
        CONST_VTBL struct IDAImageVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDAImage_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDAImage_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDAImage_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDAImage_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDAImage_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDAImage_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDAImage_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDAImage_GetClassName(This,pClassName)	\
    (This)->lpVtbl -> GetClassName(This,pClassName)

#define IDAImage_Init(This,toBvr)	\
    (This)->lpVtbl -> Init(This,toBvr)

#define IDAImage_Importance(This,relativeImportance,ppBvr)	\
    (This)->lpVtbl -> Importance(This,relativeImportance,ppBvr)

#define IDAImage_RunOnce(This,bvr)	\
    (This)->lpVtbl -> RunOnce(This,bvr)

#define IDAImage_SubstituteTime(This,xform,bvr)	\
    (This)->lpVtbl -> SubstituteTime(This,xform,bvr)

#define IDAImage_SwitchTo(This,switchTo)	\
    (This)->lpVtbl -> SwitchTo(This,switchTo)

#define IDAImage_SwitchToNumber(This,numToSwitchTo)	\
    (This)->lpVtbl -> SwitchToNumber(This,numToSwitchTo)

#define IDAImage_SwitchToString(This,strToSwitchTo)	\
    (This)->lpVtbl -> SwitchToString(This,strToSwitchTo)

#define IDAImage_Hook(This,notifier,pBvr)	\
    (This)->lpVtbl -> Hook(This,notifier,pBvr)

#define IDAImage_Duration(This,duration,bvr)	\
    (This)->lpVtbl -> Duration(This,duration,bvr)

#define IDAImage_DurationAnim(This,duration,bvr)	\
    (This)->lpVtbl -> DurationAnim(This,duration,bvr)

#define IDAImage_Repeat(This,count,bvr)	\
    (This)->lpVtbl -> Repeat(This,count,bvr)

#define IDAImage_RepeatForever(This,bvr)	\
    (This)->lpVtbl -> RepeatForever(This,bvr)

#define IDAImage_IsReady(This,bBlock,b)	\
    (This)->lpVtbl -> IsReady(This,bBlock,b)


#define IDAImage_Pickable(This,ret_0)	\
    (This)->lpVtbl -> Pickable(This,ret_0)

#define IDAImage_PickableOccluded(This,ret_0)	\
    (This)->lpVtbl -> PickableOccluded(This,ret_0)

#define IDAImage_ApplyBitmapEffect(This,effectToApply_0,firesWhenChanged_1,ret_2)	\
    (This)->lpVtbl -> ApplyBitmapEffect(This,effectToApply_0,firesWhenChanged_1,ret_2)

#define IDAImage_get_BoundingBox(This,ret_0)	\
    (This)->lpVtbl -> get_BoundingBox(This,ret_0)

#define IDAImage_Crop(This,min_0,max_1,ret_2)	\
    (This)->lpVtbl -> Crop(This,min_0,max_1,ret_2)

#define IDAImage_Transform(This,xf_0,ret_1)	\
    (This)->lpVtbl -> Transform(This,xf_0,ret_1)

#define IDAImage_OpacityAnim(This,opacity_0,ret_1)	\
    (This)->lpVtbl -> OpacityAnim(This,opacity_0,ret_1)

#define IDAImage_Opacity(This,opacity_0,ret_1)	\
    (This)->lpVtbl -> Opacity(This,opacity_0,ret_1)

#define IDAImage_Undetectable(This,ret_0)	\
    (This)->lpVtbl -> Undetectable(This,ret_0)

#define IDAImage_Tile(This,ret_0)	\
    (This)->lpVtbl -> Tile(This,ret_0)

#define IDAImage_Clip(This,m_0,ret_1)	\
    (This)->lpVtbl -> Clip(This,m_0,ret_1)

#define IDAImage_MapToUnitSquare(This,ret_0)	\
    (This)->lpVtbl -> MapToUnitSquare(This,ret_0)

#define IDAImage_ClipPolygonImageEx(This,points_0size,points_0,ret_1)	\
    (This)->lpVtbl -> ClipPolygonImageEx(This,points_0size,points_0,ret_1)

#define IDAImage_ClipPolygonImage(This,points_0,ret_1)	\
    (This)->lpVtbl -> ClipPolygonImage(This,points_0,ret_1)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDAImage_Pickable_Proxy( 
    IDAImage * This,
    /* [retval][out] */ IDAPickableResult **ret_0);



HRESULT STDMETHODCALLTYPE IDAImage_PickableOccluded_Proxy( 
    IDAImage * This,
    /* [retval][out] */ IDAPickableResult **ret_0);



HRESULT STDMETHODCALLTYPE IDAImage_ApplyBitmapEffect_Proxy( 
    IDAImage * This,
    /* [in] */ IUnknown *effectToApply_0,
    /* [in] */ IDAEvent *firesWhenChanged_1,
    /* [retval][out] */ IDAImage **ret_2);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAImage_get_BoundingBox_Proxy( 
    IDAImage * This,
    /* [retval][out] */ IDABbox2 **ret_0);



HRESULT STDMETHODCALLTYPE IDAImage_Crop_Proxy( 
    IDAImage * This,
    /* [in] */ IDAPoint2 *min_0,
    /* [in] */ IDAPoint2 *max_1,
    /* [retval][out] */ IDAImage **ret_2);



HRESULT STDMETHODCALLTYPE IDAImage_Transform_Proxy( 
    IDAImage * This,
    /* [in] */ IDATransform2 *xf_0,
    /* [retval][out] */ IDAImage **ret_1);



HRESULT STDMETHODCALLTYPE IDAImage_OpacityAnim_Proxy( 
    IDAImage * This,
    /* [in] */ IDANumber *opacity_0,
    /* [retval][out] */ IDAImage **ret_1);



HRESULT STDMETHODCALLTYPE IDAImage_Opacity_Proxy( 
    IDAImage * This,
    /* [in] */ double opacity_0,
    /* [retval][out] */ IDAImage **ret_1);



HRESULT STDMETHODCALLTYPE IDAImage_Undetectable_Proxy( 
    IDAImage * This,
    /* [retval][out] */ IDAImage **ret_0);



HRESULT STDMETHODCALLTYPE IDAImage_Tile_Proxy( 
    IDAImage * This,
    /* [retval][out] */ IDAImage **ret_0);



HRESULT STDMETHODCALLTYPE IDAImage_Clip_Proxy( 
    IDAImage * This,
    /* [in] */ IDAMatte *m_0,
    /* [retval][out] */ IDAImage **ret_1);



HRESULT STDMETHODCALLTYPE IDAImage_MapToUnitSquare_Proxy( 
    IDAImage * This,
    /* [retval][out] */ IDAImage **ret_0);



HRESULT STDMETHODCALLTYPE IDAImage_ClipPolygonImageEx_Proxy( 
    IDAImage * This,
    /* [in] */ LONG points_0size,
    /* [size_is][in] */ IDAPoint2 *points_0[  ],
    /* [retval][out] */ IDAImage **ret_1);



HRESULT STDMETHODCALLTYPE IDAImage_ClipPolygonImage_Proxy( 
    IDAImage * This,
    /* [in] */ VARIANT points_0,
    /* [retval][out] */ IDAImage **ret_1);




#endif 	/* __IDAImage_INTERFACE_DEFINED__ */


#ifndef __IDAMatte_INTERFACE_DEFINED__
#define __IDAMatte_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDAMatte
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][hidden][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDAMatte;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("C46C1BD1-3C52-11d0-9200-848C1D000000")
    IDAMatte : public IDABehavior
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Transform( 
            /* [in] */ IDATransform2 *xf_0,
            /* [retval][out] */ IDAMatte **ret_1) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDAMatteVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDAMatte * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDAMatte * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDAMatte * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDAMatte * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDAMatte * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDAMatte * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDAMatte * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassName )( 
            IDAMatte * This,
            /* [retval][out] */ BSTR *pClassName);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            IDAMatte * This,
            /* [in] */ IDABehavior *toBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Importance )( 
            IDAMatte * This,
            /* [in] */ double relativeImportance,
            /* [retval][out] */ IDABehavior **ppBvr);
        
        HRESULT ( STDMETHODCALLTYPE *RunOnce )( 
            IDAMatte * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SubstituteTime )( 
            IDAMatte * This,
            /* [in] */ IDANumber *xform,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchTo )( 
            IDAMatte * This,
            /* [in] */ IDABehavior *switchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToNumber )( 
            IDAMatte * This,
            /* [in] */ double numToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToString )( 
            IDAMatte * This,
            /* [in] */ BSTR strToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *Hook )( 
            IDAMatte * This,
            /* [in] */ IDABvrHook *notifier,
            /* [retval][out] */ IDABehavior **pBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Duration )( 
            IDAMatte * This,
            /* [in] */ double duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *DurationAnim )( 
            IDAMatte * This,
            /* [in] */ IDANumber *duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Repeat )( 
            IDAMatte * This,
            /* [in] */ LONG count,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *RepeatForever )( 
            IDAMatte * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *IsReady )( 
            IDAMatte * This,
            /* [in] */ VARIANT_BOOL bBlock,
            /* [retval][out] */ VARIANT_BOOL *b);
        
        HRESULT ( STDMETHODCALLTYPE *Transform )( 
            IDAMatte * This,
            /* [in] */ IDATransform2 *xf_0,
            /* [retval][out] */ IDAMatte **ret_1);
        
        END_INTERFACE
    } IDAMatteVtbl;

    interface IDAMatte
    {
        CONST_VTBL struct IDAMatteVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDAMatte_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDAMatte_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDAMatte_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDAMatte_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDAMatte_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDAMatte_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDAMatte_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDAMatte_GetClassName(This,pClassName)	\
    (This)->lpVtbl -> GetClassName(This,pClassName)

#define IDAMatte_Init(This,toBvr)	\
    (This)->lpVtbl -> Init(This,toBvr)

#define IDAMatte_Importance(This,relativeImportance,ppBvr)	\
    (This)->lpVtbl -> Importance(This,relativeImportance,ppBvr)

#define IDAMatte_RunOnce(This,bvr)	\
    (This)->lpVtbl -> RunOnce(This,bvr)

#define IDAMatte_SubstituteTime(This,xform,bvr)	\
    (This)->lpVtbl -> SubstituteTime(This,xform,bvr)

#define IDAMatte_SwitchTo(This,switchTo)	\
    (This)->lpVtbl -> SwitchTo(This,switchTo)

#define IDAMatte_SwitchToNumber(This,numToSwitchTo)	\
    (This)->lpVtbl -> SwitchToNumber(This,numToSwitchTo)

#define IDAMatte_SwitchToString(This,strToSwitchTo)	\
    (This)->lpVtbl -> SwitchToString(This,strToSwitchTo)

#define IDAMatte_Hook(This,notifier,pBvr)	\
    (This)->lpVtbl -> Hook(This,notifier,pBvr)

#define IDAMatte_Duration(This,duration,bvr)	\
    (This)->lpVtbl -> Duration(This,duration,bvr)

#define IDAMatte_DurationAnim(This,duration,bvr)	\
    (This)->lpVtbl -> DurationAnim(This,duration,bvr)

#define IDAMatte_Repeat(This,count,bvr)	\
    (This)->lpVtbl -> Repeat(This,count,bvr)

#define IDAMatte_RepeatForever(This,bvr)	\
    (This)->lpVtbl -> RepeatForever(This,bvr)

#define IDAMatte_IsReady(This,bBlock,b)	\
    (This)->lpVtbl -> IsReady(This,bBlock,b)


#define IDAMatte_Transform(This,xf_0,ret_1)	\
    (This)->lpVtbl -> Transform(This,xf_0,ret_1)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDAMatte_Transform_Proxy( 
    IDAMatte * This,
    /* [in] */ IDATransform2 *xf_0,
    /* [retval][out] */ IDAMatte **ret_1);




#endif 	/* __IDAMatte_INTERFACE_DEFINED__ */


#ifndef __IDAMicrophone_INTERFACE_DEFINED__
#define __IDAMicrophone_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDAMicrophone
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][hidden][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDAMicrophone;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("C46C1BE5-3C52-11d0-9200-848C1D000000")
    IDAMicrophone : public IDABehavior
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Transform( 
            /* [in] */ IDATransform3 *xf_0,
            /* [retval][out] */ IDAMicrophone **ret_1) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDAMicrophoneVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDAMicrophone * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDAMicrophone * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDAMicrophone * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDAMicrophone * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDAMicrophone * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDAMicrophone * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDAMicrophone * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassName )( 
            IDAMicrophone * This,
            /* [retval][out] */ BSTR *pClassName);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            IDAMicrophone * This,
            /* [in] */ IDABehavior *toBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Importance )( 
            IDAMicrophone * This,
            /* [in] */ double relativeImportance,
            /* [retval][out] */ IDABehavior **ppBvr);
        
        HRESULT ( STDMETHODCALLTYPE *RunOnce )( 
            IDAMicrophone * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SubstituteTime )( 
            IDAMicrophone * This,
            /* [in] */ IDANumber *xform,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchTo )( 
            IDAMicrophone * This,
            /* [in] */ IDABehavior *switchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToNumber )( 
            IDAMicrophone * This,
            /* [in] */ double numToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToString )( 
            IDAMicrophone * This,
            /* [in] */ BSTR strToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *Hook )( 
            IDAMicrophone * This,
            /* [in] */ IDABvrHook *notifier,
            /* [retval][out] */ IDABehavior **pBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Duration )( 
            IDAMicrophone * This,
            /* [in] */ double duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *DurationAnim )( 
            IDAMicrophone * This,
            /* [in] */ IDANumber *duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Repeat )( 
            IDAMicrophone * This,
            /* [in] */ LONG count,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *RepeatForever )( 
            IDAMicrophone * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *IsReady )( 
            IDAMicrophone * This,
            /* [in] */ VARIANT_BOOL bBlock,
            /* [retval][out] */ VARIANT_BOOL *b);
        
        HRESULT ( STDMETHODCALLTYPE *Transform )( 
            IDAMicrophone * This,
            /* [in] */ IDATransform3 *xf_0,
            /* [retval][out] */ IDAMicrophone **ret_1);
        
        END_INTERFACE
    } IDAMicrophoneVtbl;

    interface IDAMicrophone
    {
        CONST_VTBL struct IDAMicrophoneVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDAMicrophone_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDAMicrophone_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDAMicrophone_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDAMicrophone_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDAMicrophone_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDAMicrophone_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDAMicrophone_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDAMicrophone_GetClassName(This,pClassName)	\
    (This)->lpVtbl -> GetClassName(This,pClassName)

#define IDAMicrophone_Init(This,toBvr)	\
    (This)->lpVtbl -> Init(This,toBvr)

#define IDAMicrophone_Importance(This,relativeImportance,ppBvr)	\
    (This)->lpVtbl -> Importance(This,relativeImportance,ppBvr)

#define IDAMicrophone_RunOnce(This,bvr)	\
    (This)->lpVtbl -> RunOnce(This,bvr)

#define IDAMicrophone_SubstituteTime(This,xform,bvr)	\
    (This)->lpVtbl -> SubstituteTime(This,xform,bvr)

#define IDAMicrophone_SwitchTo(This,switchTo)	\
    (This)->lpVtbl -> SwitchTo(This,switchTo)

#define IDAMicrophone_SwitchToNumber(This,numToSwitchTo)	\
    (This)->lpVtbl -> SwitchToNumber(This,numToSwitchTo)

#define IDAMicrophone_SwitchToString(This,strToSwitchTo)	\
    (This)->lpVtbl -> SwitchToString(This,strToSwitchTo)

#define IDAMicrophone_Hook(This,notifier,pBvr)	\
    (This)->lpVtbl -> Hook(This,notifier,pBvr)

#define IDAMicrophone_Duration(This,duration,bvr)	\
    (This)->lpVtbl -> Duration(This,duration,bvr)

#define IDAMicrophone_DurationAnim(This,duration,bvr)	\
    (This)->lpVtbl -> DurationAnim(This,duration,bvr)

#define IDAMicrophone_Repeat(This,count,bvr)	\
    (This)->lpVtbl -> Repeat(This,count,bvr)

#define IDAMicrophone_RepeatForever(This,bvr)	\
    (This)->lpVtbl -> RepeatForever(This,bvr)

#define IDAMicrophone_IsReady(This,bBlock,b)	\
    (This)->lpVtbl -> IsReady(This,bBlock,b)


#define IDAMicrophone_Transform(This,xf_0,ret_1)	\
    (This)->lpVtbl -> Transform(This,xf_0,ret_1)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDAMicrophone_Transform_Proxy( 
    IDAMicrophone * This,
    /* [in] */ IDATransform3 *xf_0,
    /* [retval][out] */ IDAMicrophone **ret_1);




#endif 	/* __IDAMicrophone_INTERFACE_DEFINED__ */


#ifndef __IDAMontage_INTERFACE_DEFINED__
#define __IDAMontage_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDAMontage
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][hidden][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDAMontage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("C46C1BD5-3C52-11d0-9200-848C1D000000")
    IDAMontage : public IDABehavior
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Render( 
            /* [retval][out] */ IDAImage **ret_0) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDAMontageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDAMontage * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDAMontage * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDAMontage * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDAMontage * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDAMontage * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDAMontage * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDAMontage * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassName )( 
            IDAMontage * This,
            /* [retval][out] */ BSTR *pClassName);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            IDAMontage * This,
            /* [in] */ IDABehavior *toBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Importance )( 
            IDAMontage * This,
            /* [in] */ double relativeImportance,
            /* [retval][out] */ IDABehavior **ppBvr);
        
        HRESULT ( STDMETHODCALLTYPE *RunOnce )( 
            IDAMontage * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SubstituteTime )( 
            IDAMontage * This,
            /* [in] */ IDANumber *xform,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchTo )( 
            IDAMontage * This,
            /* [in] */ IDABehavior *switchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToNumber )( 
            IDAMontage * This,
            /* [in] */ double numToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToString )( 
            IDAMontage * This,
            /* [in] */ BSTR strToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *Hook )( 
            IDAMontage * This,
            /* [in] */ IDABvrHook *notifier,
            /* [retval][out] */ IDABehavior **pBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Duration )( 
            IDAMontage * This,
            /* [in] */ double duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *DurationAnim )( 
            IDAMontage * This,
            /* [in] */ IDANumber *duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Repeat )( 
            IDAMontage * This,
            /* [in] */ LONG count,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *RepeatForever )( 
            IDAMontage * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *IsReady )( 
            IDAMontage * This,
            /* [in] */ VARIANT_BOOL bBlock,
            /* [retval][out] */ VARIANT_BOOL *b);
        
        HRESULT ( STDMETHODCALLTYPE *Render )( 
            IDAMontage * This,
            /* [retval][out] */ IDAImage **ret_0);
        
        END_INTERFACE
    } IDAMontageVtbl;

    interface IDAMontage
    {
        CONST_VTBL struct IDAMontageVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDAMontage_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDAMontage_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDAMontage_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDAMontage_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDAMontage_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDAMontage_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDAMontage_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDAMontage_GetClassName(This,pClassName)	\
    (This)->lpVtbl -> GetClassName(This,pClassName)

#define IDAMontage_Init(This,toBvr)	\
    (This)->lpVtbl -> Init(This,toBvr)

#define IDAMontage_Importance(This,relativeImportance,ppBvr)	\
    (This)->lpVtbl -> Importance(This,relativeImportance,ppBvr)

#define IDAMontage_RunOnce(This,bvr)	\
    (This)->lpVtbl -> RunOnce(This,bvr)

#define IDAMontage_SubstituteTime(This,xform,bvr)	\
    (This)->lpVtbl -> SubstituteTime(This,xform,bvr)

#define IDAMontage_SwitchTo(This,switchTo)	\
    (This)->lpVtbl -> SwitchTo(This,switchTo)

#define IDAMontage_SwitchToNumber(This,numToSwitchTo)	\
    (This)->lpVtbl -> SwitchToNumber(This,numToSwitchTo)

#define IDAMontage_SwitchToString(This,strToSwitchTo)	\
    (This)->lpVtbl -> SwitchToString(This,strToSwitchTo)

#define IDAMontage_Hook(This,notifier,pBvr)	\
    (This)->lpVtbl -> Hook(This,notifier,pBvr)

#define IDAMontage_Duration(This,duration,bvr)	\
    (This)->lpVtbl -> Duration(This,duration,bvr)

#define IDAMontage_DurationAnim(This,duration,bvr)	\
    (This)->lpVtbl -> DurationAnim(This,duration,bvr)

#define IDAMontage_Repeat(This,count,bvr)	\
    (This)->lpVtbl -> Repeat(This,count,bvr)

#define IDAMontage_RepeatForever(This,bvr)	\
    (This)->lpVtbl -> RepeatForever(This,bvr)

#define IDAMontage_IsReady(This,bBlock,b)	\
    (This)->lpVtbl -> IsReady(This,bBlock,b)


#define IDAMontage_Render(This,ret_0)	\
    (This)->lpVtbl -> Render(This,ret_0)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDAMontage_Render_Proxy( 
    IDAMontage * This,
    /* [retval][out] */ IDAImage **ret_0);




#endif 	/* __IDAMontage_INTERFACE_DEFINED__ */


#ifndef __IDAPath2_INTERFACE_DEFINED__
#define __IDAPath2_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDAPath2
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][hidden][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDAPath2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("C46C1BCF-3C52-11d0-9200-848C1D000000")
    IDAPath2 : public IDABehavior
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Transform( 
            /* [in] */ IDATransform2 *xf_0,
            /* [retval][out] */ IDAPath2 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE BoundingBox( 
            /* [in] */ IDALineStyle *style_0,
            /* [retval][out] */ IDABbox2 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Fill( 
            /* [in] */ IDALineStyle *border_0,
            /* [in] */ IDAImage *fill_1,
            /* [retval][out] */ IDAImage **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Draw( 
            /* [in] */ IDALineStyle *border_0,
            /* [retval][out] */ IDAImage **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Close( 
            /* [retval][out] */ IDAPath2 **ret_0) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDAPath2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDAPath2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDAPath2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDAPath2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDAPath2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDAPath2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDAPath2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDAPath2 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassName )( 
            IDAPath2 * This,
            /* [retval][out] */ BSTR *pClassName);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            IDAPath2 * This,
            /* [in] */ IDABehavior *toBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Importance )( 
            IDAPath2 * This,
            /* [in] */ double relativeImportance,
            /* [retval][out] */ IDABehavior **ppBvr);
        
        HRESULT ( STDMETHODCALLTYPE *RunOnce )( 
            IDAPath2 * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SubstituteTime )( 
            IDAPath2 * This,
            /* [in] */ IDANumber *xform,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchTo )( 
            IDAPath2 * This,
            /* [in] */ IDABehavior *switchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToNumber )( 
            IDAPath2 * This,
            /* [in] */ double numToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToString )( 
            IDAPath2 * This,
            /* [in] */ BSTR strToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *Hook )( 
            IDAPath2 * This,
            /* [in] */ IDABvrHook *notifier,
            /* [retval][out] */ IDABehavior **pBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Duration )( 
            IDAPath2 * This,
            /* [in] */ double duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *DurationAnim )( 
            IDAPath2 * This,
            /* [in] */ IDANumber *duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Repeat )( 
            IDAPath2 * This,
            /* [in] */ LONG count,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *RepeatForever )( 
            IDAPath2 * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *IsReady )( 
            IDAPath2 * This,
            /* [in] */ VARIANT_BOOL bBlock,
            /* [retval][out] */ VARIANT_BOOL *b);
        
        HRESULT ( STDMETHODCALLTYPE *Transform )( 
            IDAPath2 * This,
            /* [in] */ IDATransform2 *xf_0,
            /* [retval][out] */ IDAPath2 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *BoundingBox )( 
            IDAPath2 * This,
            /* [in] */ IDALineStyle *style_0,
            /* [retval][out] */ IDABbox2 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Fill )( 
            IDAPath2 * This,
            /* [in] */ IDALineStyle *border_0,
            /* [in] */ IDAImage *fill_1,
            /* [retval][out] */ IDAImage **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *Draw )( 
            IDAPath2 * This,
            /* [in] */ IDALineStyle *border_0,
            /* [retval][out] */ IDAImage **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Close )( 
            IDAPath2 * This,
            /* [retval][out] */ IDAPath2 **ret_0);
        
        END_INTERFACE
    } IDAPath2Vtbl;

    interface IDAPath2
    {
        CONST_VTBL struct IDAPath2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDAPath2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDAPath2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDAPath2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDAPath2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDAPath2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDAPath2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDAPath2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDAPath2_GetClassName(This,pClassName)	\
    (This)->lpVtbl -> GetClassName(This,pClassName)

#define IDAPath2_Init(This,toBvr)	\
    (This)->lpVtbl -> Init(This,toBvr)

#define IDAPath2_Importance(This,relativeImportance,ppBvr)	\
    (This)->lpVtbl -> Importance(This,relativeImportance,ppBvr)

#define IDAPath2_RunOnce(This,bvr)	\
    (This)->lpVtbl -> RunOnce(This,bvr)

#define IDAPath2_SubstituteTime(This,xform,bvr)	\
    (This)->lpVtbl -> SubstituteTime(This,xform,bvr)

#define IDAPath2_SwitchTo(This,switchTo)	\
    (This)->lpVtbl -> SwitchTo(This,switchTo)

#define IDAPath2_SwitchToNumber(This,numToSwitchTo)	\
    (This)->lpVtbl -> SwitchToNumber(This,numToSwitchTo)

#define IDAPath2_SwitchToString(This,strToSwitchTo)	\
    (This)->lpVtbl -> SwitchToString(This,strToSwitchTo)

#define IDAPath2_Hook(This,notifier,pBvr)	\
    (This)->lpVtbl -> Hook(This,notifier,pBvr)

#define IDAPath2_Duration(This,duration,bvr)	\
    (This)->lpVtbl -> Duration(This,duration,bvr)

#define IDAPath2_DurationAnim(This,duration,bvr)	\
    (This)->lpVtbl -> DurationAnim(This,duration,bvr)

#define IDAPath2_Repeat(This,count,bvr)	\
    (This)->lpVtbl -> Repeat(This,count,bvr)

#define IDAPath2_RepeatForever(This,bvr)	\
    (This)->lpVtbl -> RepeatForever(This,bvr)

#define IDAPath2_IsReady(This,bBlock,b)	\
    (This)->lpVtbl -> IsReady(This,bBlock,b)


#define IDAPath2_Transform(This,xf_0,ret_1)	\
    (This)->lpVtbl -> Transform(This,xf_0,ret_1)

#define IDAPath2_BoundingBox(This,style_0,ret_1)	\
    (This)->lpVtbl -> BoundingBox(This,style_0,ret_1)

#define IDAPath2_Fill(This,border_0,fill_1,ret_2)	\
    (This)->lpVtbl -> Fill(This,border_0,fill_1,ret_2)

#define IDAPath2_Draw(This,border_0,ret_1)	\
    (This)->lpVtbl -> Draw(This,border_0,ret_1)

#define IDAPath2_Close(This,ret_0)	\
    (This)->lpVtbl -> Close(This,ret_0)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDAPath2_Transform_Proxy( 
    IDAPath2 * This,
    /* [in] */ IDATransform2 *xf_0,
    /* [retval][out] */ IDAPath2 **ret_1);



HRESULT STDMETHODCALLTYPE IDAPath2_BoundingBox_Proxy( 
    IDAPath2 * This,
    /* [in] */ IDALineStyle *style_0,
    /* [retval][out] */ IDABbox2 **ret_1);



HRESULT STDMETHODCALLTYPE IDAPath2_Fill_Proxy( 
    IDAPath2 * This,
    /* [in] */ IDALineStyle *border_0,
    /* [in] */ IDAImage *fill_1,
    /* [retval][out] */ IDAImage **ret_2);



HRESULT STDMETHODCALLTYPE IDAPath2_Draw_Proxy( 
    IDAPath2 * This,
    /* [in] */ IDALineStyle *border_0,
    /* [retval][out] */ IDAImage **ret_1);



HRESULT STDMETHODCALLTYPE IDAPath2_Close_Proxy( 
    IDAPath2 * This,
    /* [retval][out] */ IDAPath2 **ret_0);




#endif 	/* __IDAPath2_INTERFACE_DEFINED__ */


#ifndef __IDAPoint2_INTERFACE_DEFINED__
#define __IDAPoint2_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDAPoint2
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][hidden][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDAPoint2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("C46C1BC7-3C52-11d0-9200-848C1D000000")
    IDAPoint2 : public IDABehavior
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE AnimateControlPosition( 
            /* [in] */ BSTR propertyPath_0,
            /* [in] */ BSTR scriptingLanguage_1,
            /* [in] */ VARIANT_BOOL invokeAsMethod_2,
            /* [in] */ double minUpdateInterval_3,
            /* [retval][out] */ IDAPoint2 **ret_4) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AnimateControlPositionPixel( 
            /* [in] */ BSTR propertyPath_0,
            /* [in] */ BSTR scriptingLanguage_1,
            /* [in] */ VARIANT_BOOL invokeAsMethod_2,
            /* [in] */ double minUpdateInterval_3,
            /* [retval][out] */ IDAPoint2 **ret_4) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_X( 
            /* [retval][out] */ IDANumber **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Y( 
            /* [retval][out] */ IDANumber **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_PolarCoordAngle( 
            /* [retval][out] */ IDANumber **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_PolarCoordLength( 
            /* [retval][out] */ IDANumber **ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Transform( 
            /* [in] */ IDATransform2 *xf_0,
            /* [retval][out] */ IDAPoint2 **ret_1) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDAPoint2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDAPoint2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDAPoint2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDAPoint2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDAPoint2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDAPoint2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDAPoint2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDAPoint2 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassName )( 
            IDAPoint2 * This,
            /* [retval][out] */ BSTR *pClassName);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            IDAPoint2 * This,
            /* [in] */ IDABehavior *toBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Importance )( 
            IDAPoint2 * This,
            /* [in] */ double relativeImportance,
            /* [retval][out] */ IDABehavior **ppBvr);
        
        HRESULT ( STDMETHODCALLTYPE *RunOnce )( 
            IDAPoint2 * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SubstituteTime )( 
            IDAPoint2 * This,
            /* [in] */ IDANumber *xform,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchTo )( 
            IDAPoint2 * This,
            /* [in] */ IDABehavior *switchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToNumber )( 
            IDAPoint2 * This,
            /* [in] */ double numToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToString )( 
            IDAPoint2 * This,
            /* [in] */ BSTR strToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *Hook )( 
            IDAPoint2 * This,
            /* [in] */ IDABvrHook *notifier,
            /* [retval][out] */ IDABehavior **pBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Duration )( 
            IDAPoint2 * This,
            /* [in] */ double duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *DurationAnim )( 
            IDAPoint2 * This,
            /* [in] */ IDANumber *duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Repeat )( 
            IDAPoint2 * This,
            /* [in] */ LONG count,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *RepeatForever )( 
            IDAPoint2 * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *IsReady )( 
            IDAPoint2 * This,
            /* [in] */ VARIANT_BOOL bBlock,
            /* [retval][out] */ VARIANT_BOOL *b);
        
        HRESULT ( STDMETHODCALLTYPE *AnimateControlPosition )( 
            IDAPoint2 * This,
            /* [in] */ BSTR propertyPath_0,
            /* [in] */ BSTR scriptingLanguage_1,
            /* [in] */ VARIANT_BOOL invokeAsMethod_2,
            /* [in] */ double minUpdateInterval_3,
            /* [retval][out] */ IDAPoint2 **ret_4);
        
        HRESULT ( STDMETHODCALLTYPE *AnimateControlPositionPixel )( 
            IDAPoint2 * This,
            /* [in] */ BSTR propertyPath_0,
            /* [in] */ BSTR scriptingLanguage_1,
            /* [in] */ VARIANT_BOOL invokeAsMethod_2,
            /* [in] */ double minUpdateInterval_3,
            /* [retval][out] */ IDAPoint2 **ret_4);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_X )( 
            IDAPoint2 * This,
            /* [retval][out] */ IDANumber **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Y )( 
            IDAPoint2 * This,
            /* [retval][out] */ IDANumber **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_PolarCoordAngle )( 
            IDAPoint2 * This,
            /* [retval][out] */ IDANumber **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_PolarCoordLength )( 
            IDAPoint2 * This,
            /* [retval][out] */ IDANumber **ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *Transform )( 
            IDAPoint2 * This,
            /* [in] */ IDATransform2 *xf_0,
            /* [retval][out] */ IDAPoint2 **ret_1);
        
        END_INTERFACE
    } IDAPoint2Vtbl;

    interface IDAPoint2
    {
        CONST_VTBL struct IDAPoint2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDAPoint2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDAPoint2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDAPoint2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDAPoint2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDAPoint2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDAPoint2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDAPoint2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDAPoint2_GetClassName(This,pClassName)	\
    (This)->lpVtbl -> GetClassName(This,pClassName)

#define IDAPoint2_Init(This,toBvr)	\
    (This)->lpVtbl -> Init(This,toBvr)

#define IDAPoint2_Importance(This,relativeImportance,ppBvr)	\
    (This)->lpVtbl -> Importance(This,relativeImportance,ppBvr)

#define IDAPoint2_RunOnce(This,bvr)	\
    (This)->lpVtbl -> RunOnce(This,bvr)

#define IDAPoint2_SubstituteTime(This,xform,bvr)	\
    (This)->lpVtbl -> SubstituteTime(This,xform,bvr)

#define IDAPoint2_SwitchTo(This,switchTo)	\
    (This)->lpVtbl -> SwitchTo(This,switchTo)

#define IDAPoint2_SwitchToNumber(This,numToSwitchTo)	\
    (This)->lpVtbl -> SwitchToNumber(This,numToSwitchTo)

#define IDAPoint2_SwitchToString(This,strToSwitchTo)	\
    (This)->lpVtbl -> SwitchToString(This,strToSwitchTo)

#define IDAPoint2_Hook(This,notifier,pBvr)	\
    (This)->lpVtbl -> Hook(This,notifier,pBvr)

#define IDAPoint2_Duration(This,duration,bvr)	\
    (This)->lpVtbl -> Duration(This,duration,bvr)

#define IDAPoint2_DurationAnim(This,duration,bvr)	\
    (This)->lpVtbl -> DurationAnim(This,duration,bvr)

#define IDAPoint2_Repeat(This,count,bvr)	\
    (This)->lpVtbl -> Repeat(This,count,bvr)

#define IDAPoint2_RepeatForever(This,bvr)	\
    (This)->lpVtbl -> RepeatForever(This,bvr)

#define IDAPoint2_IsReady(This,bBlock,b)	\
    (This)->lpVtbl -> IsReady(This,bBlock,b)


#define IDAPoint2_AnimateControlPosition(This,propertyPath_0,scriptingLanguage_1,invokeAsMethod_2,minUpdateInterval_3,ret_4)	\
    (This)->lpVtbl -> AnimateControlPosition(This,propertyPath_0,scriptingLanguage_1,invokeAsMethod_2,minUpdateInterval_3,ret_4)

#define IDAPoint2_AnimateControlPositionPixel(This,propertyPath_0,scriptingLanguage_1,invokeAsMethod_2,minUpdateInterval_3,ret_4)	\
    (This)->lpVtbl -> AnimateControlPositionPixel(This,propertyPath_0,scriptingLanguage_1,invokeAsMethod_2,minUpdateInterval_3,ret_4)

#define IDAPoint2_get_X(This,ret_0)	\
    (This)->lpVtbl -> get_X(This,ret_0)

#define IDAPoint2_get_Y(This,ret_0)	\
    (This)->lpVtbl -> get_Y(This,ret_0)

#define IDAPoint2_get_PolarCoordAngle(This,ret_0)	\
    (This)->lpVtbl -> get_PolarCoordAngle(This,ret_0)

#define IDAPoint2_get_PolarCoordLength(This,ret_0)	\
    (This)->lpVtbl -> get_PolarCoordLength(This,ret_0)

#define IDAPoint2_Transform(This,xf_0,ret_1)	\
    (This)->lpVtbl -> Transform(This,xf_0,ret_1)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDAPoint2_AnimateControlPosition_Proxy( 
    IDAPoint2 * This,
    /* [in] */ BSTR propertyPath_0,
    /* [in] */ BSTR scriptingLanguage_1,
    /* [in] */ VARIANT_BOOL invokeAsMethod_2,
    /* [in] */ double minUpdateInterval_3,
    /* [retval][out] */ IDAPoint2 **ret_4);



HRESULT STDMETHODCALLTYPE IDAPoint2_AnimateControlPositionPixel_Proxy( 
    IDAPoint2 * This,
    /* [in] */ BSTR propertyPath_0,
    /* [in] */ BSTR scriptingLanguage_1,
    /* [in] */ VARIANT_BOOL invokeAsMethod_2,
    /* [in] */ double minUpdateInterval_3,
    /* [retval][out] */ IDAPoint2 **ret_4);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAPoint2_get_X_Proxy( 
    IDAPoint2 * This,
    /* [retval][out] */ IDANumber **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAPoint2_get_Y_Proxy( 
    IDAPoint2 * This,
    /* [retval][out] */ IDANumber **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAPoint2_get_PolarCoordAngle_Proxy( 
    IDAPoint2 * This,
    /* [retval][out] */ IDANumber **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAPoint2_get_PolarCoordLength_Proxy( 
    IDAPoint2 * This,
    /* [retval][out] */ IDANumber **ret_0);



HRESULT STDMETHODCALLTYPE IDAPoint2_Transform_Proxy( 
    IDAPoint2 * This,
    /* [in] */ IDATransform2 *xf_0,
    /* [retval][out] */ IDAPoint2 **ret_1);




#endif 	/* __IDAPoint2_INTERFACE_DEFINED__ */


#ifndef __IDAPoint3_INTERFACE_DEFINED__
#define __IDAPoint3_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDAPoint3
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][hidden][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDAPoint3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("C46C1BD7-3C52-11d0-9200-848C1D000000")
    IDAPoint3 : public IDABehavior
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Project( 
            /* [in] */ IDACamera *cam_0,
            /* [retval][out] */ IDAPoint2 **ret_1) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_X( 
            /* [retval][out] */ IDANumber **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Y( 
            /* [retval][out] */ IDANumber **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Z( 
            /* [retval][out] */ IDANumber **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_SphericalCoordXYAngle( 
            /* [retval][out] */ IDANumber **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_SphericalCoordYZAngle( 
            /* [retval][out] */ IDANumber **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_SphericalCoordLength( 
            /* [retval][out] */ IDANumber **ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Transform( 
            /* [in] */ IDATransform3 *xf_0,
            /* [retval][out] */ IDAPoint3 **ret_1) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDAPoint3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDAPoint3 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDAPoint3 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDAPoint3 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDAPoint3 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDAPoint3 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDAPoint3 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDAPoint3 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassName )( 
            IDAPoint3 * This,
            /* [retval][out] */ BSTR *pClassName);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            IDAPoint3 * This,
            /* [in] */ IDABehavior *toBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Importance )( 
            IDAPoint3 * This,
            /* [in] */ double relativeImportance,
            /* [retval][out] */ IDABehavior **ppBvr);
        
        HRESULT ( STDMETHODCALLTYPE *RunOnce )( 
            IDAPoint3 * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SubstituteTime )( 
            IDAPoint3 * This,
            /* [in] */ IDANumber *xform,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchTo )( 
            IDAPoint3 * This,
            /* [in] */ IDABehavior *switchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToNumber )( 
            IDAPoint3 * This,
            /* [in] */ double numToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToString )( 
            IDAPoint3 * This,
            /* [in] */ BSTR strToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *Hook )( 
            IDAPoint3 * This,
            /* [in] */ IDABvrHook *notifier,
            /* [retval][out] */ IDABehavior **pBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Duration )( 
            IDAPoint3 * This,
            /* [in] */ double duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *DurationAnim )( 
            IDAPoint3 * This,
            /* [in] */ IDANumber *duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Repeat )( 
            IDAPoint3 * This,
            /* [in] */ LONG count,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *RepeatForever )( 
            IDAPoint3 * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *IsReady )( 
            IDAPoint3 * This,
            /* [in] */ VARIANT_BOOL bBlock,
            /* [retval][out] */ VARIANT_BOOL *b);
        
        HRESULT ( STDMETHODCALLTYPE *Project )( 
            IDAPoint3 * This,
            /* [in] */ IDACamera *cam_0,
            /* [retval][out] */ IDAPoint2 **ret_1);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_X )( 
            IDAPoint3 * This,
            /* [retval][out] */ IDANumber **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Y )( 
            IDAPoint3 * This,
            /* [retval][out] */ IDANumber **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Z )( 
            IDAPoint3 * This,
            /* [retval][out] */ IDANumber **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_SphericalCoordXYAngle )( 
            IDAPoint3 * This,
            /* [retval][out] */ IDANumber **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_SphericalCoordYZAngle )( 
            IDAPoint3 * This,
            /* [retval][out] */ IDANumber **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_SphericalCoordLength )( 
            IDAPoint3 * This,
            /* [retval][out] */ IDANumber **ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *Transform )( 
            IDAPoint3 * This,
            /* [in] */ IDATransform3 *xf_0,
            /* [retval][out] */ IDAPoint3 **ret_1);
        
        END_INTERFACE
    } IDAPoint3Vtbl;

    interface IDAPoint3
    {
        CONST_VTBL struct IDAPoint3Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDAPoint3_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDAPoint3_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDAPoint3_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDAPoint3_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDAPoint3_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDAPoint3_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDAPoint3_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDAPoint3_GetClassName(This,pClassName)	\
    (This)->lpVtbl -> GetClassName(This,pClassName)

#define IDAPoint3_Init(This,toBvr)	\
    (This)->lpVtbl -> Init(This,toBvr)

#define IDAPoint3_Importance(This,relativeImportance,ppBvr)	\
    (This)->lpVtbl -> Importance(This,relativeImportance,ppBvr)

#define IDAPoint3_RunOnce(This,bvr)	\
    (This)->lpVtbl -> RunOnce(This,bvr)

#define IDAPoint3_SubstituteTime(This,xform,bvr)	\
    (This)->lpVtbl -> SubstituteTime(This,xform,bvr)

#define IDAPoint3_SwitchTo(This,switchTo)	\
    (This)->lpVtbl -> SwitchTo(This,switchTo)

#define IDAPoint3_SwitchToNumber(This,numToSwitchTo)	\
    (This)->lpVtbl -> SwitchToNumber(This,numToSwitchTo)

#define IDAPoint3_SwitchToString(This,strToSwitchTo)	\
    (This)->lpVtbl -> SwitchToString(This,strToSwitchTo)

#define IDAPoint3_Hook(This,notifier,pBvr)	\
    (This)->lpVtbl -> Hook(This,notifier,pBvr)

#define IDAPoint3_Duration(This,duration,bvr)	\
    (This)->lpVtbl -> Duration(This,duration,bvr)

#define IDAPoint3_DurationAnim(This,duration,bvr)	\
    (This)->lpVtbl -> DurationAnim(This,duration,bvr)

#define IDAPoint3_Repeat(This,count,bvr)	\
    (This)->lpVtbl -> Repeat(This,count,bvr)

#define IDAPoint3_RepeatForever(This,bvr)	\
    (This)->lpVtbl -> RepeatForever(This,bvr)

#define IDAPoint3_IsReady(This,bBlock,b)	\
    (This)->lpVtbl -> IsReady(This,bBlock,b)


#define IDAPoint3_Project(This,cam_0,ret_1)	\
    (This)->lpVtbl -> Project(This,cam_0,ret_1)

#define IDAPoint3_get_X(This,ret_0)	\
    (This)->lpVtbl -> get_X(This,ret_0)

#define IDAPoint3_get_Y(This,ret_0)	\
    (This)->lpVtbl -> get_Y(This,ret_0)

#define IDAPoint3_get_Z(This,ret_0)	\
    (This)->lpVtbl -> get_Z(This,ret_0)

#define IDAPoint3_get_SphericalCoordXYAngle(This,ret_0)	\
    (This)->lpVtbl -> get_SphericalCoordXYAngle(This,ret_0)

#define IDAPoint3_get_SphericalCoordYZAngle(This,ret_0)	\
    (This)->lpVtbl -> get_SphericalCoordYZAngle(This,ret_0)

#define IDAPoint3_get_SphericalCoordLength(This,ret_0)	\
    (This)->lpVtbl -> get_SphericalCoordLength(This,ret_0)

#define IDAPoint3_Transform(This,xf_0,ret_1)	\
    (This)->lpVtbl -> Transform(This,xf_0,ret_1)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDAPoint3_Project_Proxy( 
    IDAPoint3 * This,
    /* [in] */ IDACamera *cam_0,
    /* [retval][out] */ IDAPoint2 **ret_1);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAPoint3_get_X_Proxy( 
    IDAPoint3 * This,
    /* [retval][out] */ IDANumber **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAPoint3_get_Y_Proxy( 
    IDAPoint3 * This,
    /* [retval][out] */ IDANumber **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAPoint3_get_Z_Proxy( 
    IDAPoint3 * This,
    /* [retval][out] */ IDANumber **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAPoint3_get_SphericalCoordXYAngle_Proxy( 
    IDAPoint3 * This,
    /* [retval][out] */ IDANumber **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAPoint3_get_SphericalCoordYZAngle_Proxy( 
    IDAPoint3 * This,
    /* [retval][out] */ IDANumber **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAPoint3_get_SphericalCoordLength_Proxy( 
    IDAPoint3 * This,
    /* [retval][out] */ IDANumber **ret_0);



HRESULT STDMETHODCALLTYPE IDAPoint3_Transform_Proxy( 
    IDAPoint3 * This,
    /* [in] */ IDATransform3 *xf_0,
    /* [retval][out] */ IDAPoint3 **ret_1);




#endif 	/* __IDAPoint3_INTERFACE_DEFINED__ */


#ifndef __IDASound_INTERFACE_DEFINED__
#define __IDASound_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDASound
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][hidden][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDASound;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("C46C1BE3-3C52-11d0-9200-848C1D000000")
    IDASound : public IDABehavior
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE PhaseAnim( 
            /* [in] */ IDANumber *phaseAmt_0,
            /* [retval][out] */ IDASound **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Phase( 
            /* [in] */ double phaseAmt_0,
            /* [retval][out] */ IDASound **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RateAnim( 
            /* [in] */ IDANumber *pitchShift_0,
            /* [retval][out] */ IDASound **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Rate( 
            /* [in] */ double pitchShift_0,
            /* [retval][out] */ IDASound **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PanAnim( 
            /* [in] */ IDANumber *panAmt_0,
            /* [retval][out] */ IDASound **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Pan( 
            /* [in] */ double panAmt_0,
            /* [retval][out] */ IDASound **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GainAnim( 
            /* [in] */ IDANumber *gainAmt_0,
            /* [retval][out] */ IDASound **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Gain( 
            /* [in] */ double gainAmt_0,
            /* [retval][out] */ IDASound **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Loop( 
            /* [retval][out] */ IDASound **ret_0) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDASoundVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDASound * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDASound * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDASound * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDASound * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDASound * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDASound * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDASound * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassName )( 
            IDASound * This,
            /* [retval][out] */ BSTR *pClassName);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            IDASound * This,
            /* [in] */ IDABehavior *toBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Importance )( 
            IDASound * This,
            /* [in] */ double relativeImportance,
            /* [retval][out] */ IDABehavior **ppBvr);
        
        HRESULT ( STDMETHODCALLTYPE *RunOnce )( 
            IDASound * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SubstituteTime )( 
            IDASound * This,
            /* [in] */ IDANumber *xform,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchTo )( 
            IDASound * This,
            /* [in] */ IDABehavior *switchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToNumber )( 
            IDASound * This,
            /* [in] */ double numToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToString )( 
            IDASound * This,
            /* [in] */ BSTR strToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *Hook )( 
            IDASound * This,
            /* [in] */ IDABvrHook *notifier,
            /* [retval][out] */ IDABehavior **pBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Duration )( 
            IDASound * This,
            /* [in] */ double duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *DurationAnim )( 
            IDASound * This,
            /* [in] */ IDANumber *duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Repeat )( 
            IDASound * This,
            /* [in] */ LONG count,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *RepeatForever )( 
            IDASound * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *IsReady )( 
            IDASound * This,
            /* [in] */ VARIANT_BOOL bBlock,
            /* [retval][out] */ VARIANT_BOOL *b);
        
        HRESULT ( STDMETHODCALLTYPE *PhaseAnim )( 
            IDASound * This,
            /* [in] */ IDANumber *phaseAmt_0,
            /* [retval][out] */ IDASound **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Phase )( 
            IDASound * This,
            /* [in] */ double phaseAmt_0,
            /* [retval][out] */ IDASound **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *RateAnim )( 
            IDASound * This,
            /* [in] */ IDANumber *pitchShift_0,
            /* [retval][out] */ IDASound **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Rate )( 
            IDASound * This,
            /* [in] */ double pitchShift_0,
            /* [retval][out] */ IDASound **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *PanAnim )( 
            IDASound * This,
            /* [in] */ IDANumber *panAmt_0,
            /* [retval][out] */ IDASound **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Pan )( 
            IDASound * This,
            /* [in] */ double panAmt_0,
            /* [retval][out] */ IDASound **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *GainAnim )( 
            IDASound * This,
            /* [in] */ IDANumber *gainAmt_0,
            /* [retval][out] */ IDASound **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Gain )( 
            IDASound * This,
            /* [in] */ double gainAmt_0,
            /* [retval][out] */ IDASound **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Loop )( 
            IDASound * This,
            /* [retval][out] */ IDASound **ret_0);
        
        END_INTERFACE
    } IDASoundVtbl;

    interface IDASound
    {
        CONST_VTBL struct IDASoundVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDASound_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDASound_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDASound_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDASound_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDASound_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDASound_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDASound_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDASound_GetClassName(This,pClassName)	\
    (This)->lpVtbl -> GetClassName(This,pClassName)

#define IDASound_Init(This,toBvr)	\
    (This)->lpVtbl -> Init(This,toBvr)

#define IDASound_Importance(This,relativeImportance,ppBvr)	\
    (This)->lpVtbl -> Importance(This,relativeImportance,ppBvr)

#define IDASound_RunOnce(This,bvr)	\
    (This)->lpVtbl -> RunOnce(This,bvr)

#define IDASound_SubstituteTime(This,xform,bvr)	\
    (This)->lpVtbl -> SubstituteTime(This,xform,bvr)

#define IDASound_SwitchTo(This,switchTo)	\
    (This)->lpVtbl -> SwitchTo(This,switchTo)

#define IDASound_SwitchToNumber(This,numToSwitchTo)	\
    (This)->lpVtbl -> SwitchToNumber(This,numToSwitchTo)

#define IDASound_SwitchToString(This,strToSwitchTo)	\
    (This)->lpVtbl -> SwitchToString(This,strToSwitchTo)

#define IDASound_Hook(This,notifier,pBvr)	\
    (This)->lpVtbl -> Hook(This,notifier,pBvr)

#define IDASound_Duration(This,duration,bvr)	\
    (This)->lpVtbl -> Duration(This,duration,bvr)

#define IDASound_DurationAnim(This,duration,bvr)	\
    (This)->lpVtbl -> DurationAnim(This,duration,bvr)

#define IDASound_Repeat(This,count,bvr)	\
    (This)->lpVtbl -> Repeat(This,count,bvr)

#define IDASound_RepeatForever(This,bvr)	\
    (This)->lpVtbl -> RepeatForever(This,bvr)

#define IDASound_IsReady(This,bBlock,b)	\
    (This)->lpVtbl -> IsReady(This,bBlock,b)


#define IDASound_PhaseAnim(This,phaseAmt_0,ret_1)	\
    (This)->lpVtbl -> PhaseAnim(This,phaseAmt_0,ret_1)

#define IDASound_Phase(This,phaseAmt_0,ret_1)	\
    (This)->lpVtbl -> Phase(This,phaseAmt_0,ret_1)

#define IDASound_RateAnim(This,pitchShift_0,ret_1)	\
    (This)->lpVtbl -> RateAnim(This,pitchShift_0,ret_1)

#define IDASound_Rate(This,pitchShift_0,ret_1)	\
    (This)->lpVtbl -> Rate(This,pitchShift_0,ret_1)

#define IDASound_PanAnim(This,panAmt_0,ret_1)	\
    (This)->lpVtbl -> PanAnim(This,panAmt_0,ret_1)

#define IDASound_Pan(This,panAmt_0,ret_1)	\
    (This)->lpVtbl -> Pan(This,panAmt_0,ret_1)

#define IDASound_GainAnim(This,gainAmt_0,ret_1)	\
    (This)->lpVtbl -> GainAnim(This,gainAmt_0,ret_1)

#define IDASound_Gain(This,gainAmt_0,ret_1)	\
    (This)->lpVtbl -> Gain(This,gainAmt_0,ret_1)

#define IDASound_Loop(This,ret_0)	\
    (This)->lpVtbl -> Loop(This,ret_0)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDASound_PhaseAnim_Proxy( 
    IDASound * This,
    /* [in] */ IDANumber *phaseAmt_0,
    /* [retval][out] */ IDASound **ret_1);



HRESULT STDMETHODCALLTYPE IDASound_Phase_Proxy( 
    IDASound * This,
    /* [in] */ double phaseAmt_0,
    /* [retval][out] */ IDASound **ret_1);



HRESULT STDMETHODCALLTYPE IDASound_RateAnim_Proxy( 
    IDASound * This,
    /* [in] */ IDANumber *pitchShift_0,
    /* [retval][out] */ IDASound **ret_1);



HRESULT STDMETHODCALLTYPE IDASound_Rate_Proxy( 
    IDASound * This,
    /* [in] */ double pitchShift_0,
    /* [retval][out] */ IDASound **ret_1);



HRESULT STDMETHODCALLTYPE IDASound_PanAnim_Proxy( 
    IDASound * This,
    /* [in] */ IDANumber *panAmt_0,
    /* [retval][out] */ IDASound **ret_1);



HRESULT STDMETHODCALLTYPE IDASound_Pan_Proxy( 
    IDASound * This,
    /* [in] */ double panAmt_0,
    /* [retval][out] */ IDASound **ret_1);



HRESULT STDMETHODCALLTYPE IDASound_GainAnim_Proxy( 
    IDASound * This,
    /* [in] */ IDANumber *gainAmt_0,
    /* [retval][out] */ IDASound **ret_1);



HRESULT STDMETHODCALLTYPE IDASound_Gain_Proxy( 
    IDASound * This,
    /* [in] */ double gainAmt_0,
    /* [retval][out] */ IDASound **ret_1);



HRESULT STDMETHODCALLTYPE IDASound_Loop_Proxy( 
    IDASound * This,
    /* [retval][out] */ IDASound **ret_0);




#endif 	/* __IDASound_INTERFACE_DEFINED__ */


#ifndef __IDAString_INTERFACE_DEFINED__
#define __IDAString_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDAString
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][hidden][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDAString;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("C46C1BC3-3C52-11d0-9200-848C1D000000")
    IDAString : public IDABehavior
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Extract( 
            /* [retval][out] */ BSTR *ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AnimateProperty( 
            /* [in] */ BSTR propertyPath_0,
            /* [in] */ BSTR scriptingLanguage_1,
            /* [in] */ VARIANT_BOOL invokeAsMethod_2,
            /* [in] */ double minUpdateInterval_3,
            /* [retval][out] */ IDAString **ret_4) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDAStringVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDAString * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDAString * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDAString * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDAString * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDAString * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDAString * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDAString * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassName )( 
            IDAString * This,
            /* [retval][out] */ BSTR *pClassName);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            IDAString * This,
            /* [in] */ IDABehavior *toBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Importance )( 
            IDAString * This,
            /* [in] */ double relativeImportance,
            /* [retval][out] */ IDABehavior **ppBvr);
        
        HRESULT ( STDMETHODCALLTYPE *RunOnce )( 
            IDAString * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SubstituteTime )( 
            IDAString * This,
            /* [in] */ IDANumber *xform,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchTo )( 
            IDAString * This,
            /* [in] */ IDABehavior *switchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToNumber )( 
            IDAString * This,
            /* [in] */ double numToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToString )( 
            IDAString * This,
            /* [in] */ BSTR strToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *Hook )( 
            IDAString * This,
            /* [in] */ IDABvrHook *notifier,
            /* [retval][out] */ IDABehavior **pBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Duration )( 
            IDAString * This,
            /* [in] */ double duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *DurationAnim )( 
            IDAString * This,
            /* [in] */ IDANumber *duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Repeat )( 
            IDAString * This,
            /* [in] */ LONG count,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *RepeatForever )( 
            IDAString * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *IsReady )( 
            IDAString * This,
            /* [in] */ VARIANT_BOOL bBlock,
            /* [retval][out] */ VARIANT_BOOL *b);
        
        HRESULT ( STDMETHODCALLTYPE *Extract )( 
            IDAString * This,
            /* [retval][out] */ BSTR *ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *AnimateProperty )( 
            IDAString * This,
            /* [in] */ BSTR propertyPath_0,
            /* [in] */ BSTR scriptingLanguage_1,
            /* [in] */ VARIANT_BOOL invokeAsMethod_2,
            /* [in] */ double minUpdateInterval_3,
            /* [retval][out] */ IDAString **ret_4);
        
        END_INTERFACE
    } IDAStringVtbl;

    interface IDAString
    {
        CONST_VTBL struct IDAStringVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDAString_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDAString_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDAString_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDAString_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDAString_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDAString_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDAString_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDAString_GetClassName(This,pClassName)	\
    (This)->lpVtbl -> GetClassName(This,pClassName)

#define IDAString_Init(This,toBvr)	\
    (This)->lpVtbl -> Init(This,toBvr)

#define IDAString_Importance(This,relativeImportance,ppBvr)	\
    (This)->lpVtbl -> Importance(This,relativeImportance,ppBvr)

#define IDAString_RunOnce(This,bvr)	\
    (This)->lpVtbl -> RunOnce(This,bvr)

#define IDAString_SubstituteTime(This,xform,bvr)	\
    (This)->lpVtbl -> SubstituteTime(This,xform,bvr)

#define IDAString_SwitchTo(This,switchTo)	\
    (This)->lpVtbl -> SwitchTo(This,switchTo)

#define IDAString_SwitchToNumber(This,numToSwitchTo)	\
    (This)->lpVtbl -> SwitchToNumber(This,numToSwitchTo)

#define IDAString_SwitchToString(This,strToSwitchTo)	\
    (This)->lpVtbl -> SwitchToString(This,strToSwitchTo)

#define IDAString_Hook(This,notifier,pBvr)	\
    (This)->lpVtbl -> Hook(This,notifier,pBvr)

#define IDAString_Duration(This,duration,bvr)	\
    (This)->lpVtbl -> Duration(This,duration,bvr)

#define IDAString_DurationAnim(This,duration,bvr)	\
    (This)->lpVtbl -> DurationAnim(This,duration,bvr)

#define IDAString_Repeat(This,count,bvr)	\
    (This)->lpVtbl -> Repeat(This,count,bvr)

#define IDAString_RepeatForever(This,bvr)	\
    (This)->lpVtbl -> RepeatForever(This,bvr)

#define IDAString_IsReady(This,bBlock,b)	\
    (This)->lpVtbl -> IsReady(This,bBlock,b)


#define IDAString_Extract(This,ret_0)	\
    (This)->lpVtbl -> Extract(This,ret_0)

#define IDAString_AnimateProperty(This,propertyPath_0,scriptingLanguage_1,invokeAsMethod_2,minUpdateInterval_3,ret_4)	\
    (This)->lpVtbl -> AnimateProperty(This,propertyPath_0,scriptingLanguage_1,invokeAsMethod_2,minUpdateInterval_3,ret_4)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDAString_Extract_Proxy( 
    IDAString * This,
    /* [retval][out] */ BSTR *ret_0);



HRESULT STDMETHODCALLTYPE IDAString_AnimateProperty_Proxy( 
    IDAString * This,
    /* [in] */ BSTR propertyPath_0,
    /* [in] */ BSTR scriptingLanguage_1,
    /* [in] */ VARIANT_BOOL invokeAsMethod_2,
    /* [in] */ double minUpdateInterval_3,
    /* [retval][out] */ IDAString **ret_4);




#endif 	/* __IDAString_INTERFACE_DEFINED__ */


#ifndef __IDATransform2_INTERFACE_DEFINED__
#define __IDATransform2_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDATransform2
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][hidden][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDATransform2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("C46C1BCB-3C52-11d0-9200-848C1D000000")
    IDATransform2 : public IDABehavior
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Inverse( 
            /* [retval][out] */ IDATransform2 **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_IsSingular( 
            /* [retval][out] */ IDABoolean **ret_0) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDATransform2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDATransform2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDATransform2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDATransform2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDATransform2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDATransform2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDATransform2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDATransform2 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassName )( 
            IDATransform2 * This,
            /* [retval][out] */ BSTR *pClassName);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            IDATransform2 * This,
            /* [in] */ IDABehavior *toBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Importance )( 
            IDATransform2 * This,
            /* [in] */ double relativeImportance,
            /* [retval][out] */ IDABehavior **ppBvr);
        
        HRESULT ( STDMETHODCALLTYPE *RunOnce )( 
            IDATransform2 * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SubstituteTime )( 
            IDATransform2 * This,
            /* [in] */ IDANumber *xform,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchTo )( 
            IDATransform2 * This,
            /* [in] */ IDABehavior *switchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToNumber )( 
            IDATransform2 * This,
            /* [in] */ double numToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToString )( 
            IDATransform2 * This,
            /* [in] */ BSTR strToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *Hook )( 
            IDATransform2 * This,
            /* [in] */ IDABvrHook *notifier,
            /* [retval][out] */ IDABehavior **pBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Duration )( 
            IDATransform2 * This,
            /* [in] */ double duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *DurationAnim )( 
            IDATransform2 * This,
            /* [in] */ IDANumber *duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Repeat )( 
            IDATransform2 * This,
            /* [in] */ LONG count,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *RepeatForever )( 
            IDATransform2 * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *IsReady )( 
            IDATransform2 * This,
            /* [in] */ VARIANT_BOOL bBlock,
            /* [retval][out] */ VARIANT_BOOL *b);
        
        HRESULT ( STDMETHODCALLTYPE *Inverse )( 
            IDATransform2 * This,
            /* [retval][out] */ IDATransform2 **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsSingular )( 
            IDATransform2 * This,
            /* [retval][out] */ IDABoolean **ret_0);
        
        END_INTERFACE
    } IDATransform2Vtbl;

    interface IDATransform2
    {
        CONST_VTBL struct IDATransform2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDATransform2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDATransform2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDATransform2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDATransform2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDATransform2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDATransform2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDATransform2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDATransform2_GetClassName(This,pClassName)	\
    (This)->lpVtbl -> GetClassName(This,pClassName)

#define IDATransform2_Init(This,toBvr)	\
    (This)->lpVtbl -> Init(This,toBvr)

#define IDATransform2_Importance(This,relativeImportance,ppBvr)	\
    (This)->lpVtbl -> Importance(This,relativeImportance,ppBvr)

#define IDATransform2_RunOnce(This,bvr)	\
    (This)->lpVtbl -> RunOnce(This,bvr)

#define IDATransform2_SubstituteTime(This,xform,bvr)	\
    (This)->lpVtbl -> SubstituteTime(This,xform,bvr)

#define IDATransform2_SwitchTo(This,switchTo)	\
    (This)->lpVtbl -> SwitchTo(This,switchTo)

#define IDATransform2_SwitchToNumber(This,numToSwitchTo)	\
    (This)->lpVtbl -> SwitchToNumber(This,numToSwitchTo)

#define IDATransform2_SwitchToString(This,strToSwitchTo)	\
    (This)->lpVtbl -> SwitchToString(This,strToSwitchTo)

#define IDATransform2_Hook(This,notifier,pBvr)	\
    (This)->lpVtbl -> Hook(This,notifier,pBvr)

#define IDATransform2_Duration(This,duration,bvr)	\
    (This)->lpVtbl -> Duration(This,duration,bvr)

#define IDATransform2_DurationAnim(This,duration,bvr)	\
    (This)->lpVtbl -> DurationAnim(This,duration,bvr)

#define IDATransform2_Repeat(This,count,bvr)	\
    (This)->lpVtbl -> Repeat(This,count,bvr)

#define IDATransform2_RepeatForever(This,bvr)	\
    (This)->lpVtbl -> RepeatForever(This,bvr)

#define IDATransform2_IsReady(This,bBlock,b)	\
    (This)->lpVtbl -> IsReady(This,bBlock,b)


#define IDATransform2_Inverse(This,ret_0)	\
    (This)->lpVtbl -> Inverse(This,ret_0)

#define IDATransform2_get_IsSingular(This,ret_0)	\
    (This)->lpVtbl -> get_IsSingular(This,ret_0)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDATransform2_Inverse_Proxy( 
    IDATransform2 * This,
    /* [retval][out] */ IDATransform2 **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDATransform2_get_IsSingular_Proxy( 
    IDATransform2 * This,
    /* [retval][out] */ IDABoolean **ret_0);




#endif 	/* __IDATransform2_INTERFACE_DEFINED__ */


#ifndef __IDATransform3_INTERFACE_DEFINED__
#define __IDATransform3_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDATransform3
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][hidden][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDATransform3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("C46C1BDB-3C52-11d0-9200-848C1D000000")
    IDATransform3 : public IDABehavior
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Inverse( 
            /* [retval][out] */ IDATransform3 **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_IsSingular( 
            /* [retval][out] */ IDABoolean **ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ParallelTransform2( 
            /* [retval][out] */ IDATransform2 **ret_0) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDATransform3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDATransform3 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDATransform3 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDATransform3 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDATransform3 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDATransform3 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDATransform3 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDATransform3 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassName )( 
            IDATransform3 * This,
            /* [retval][out] */ BSTR *pClassName);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            IDATransform3 * This,
            /* [in] */ IDABehavior *toBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Importance )( 
            IDATransform3 * This,
            /* [in] */ double relativeImportance,
            /* [retval][out] */ IDABehavior **ppBvr);
        
        HRESULT ( STDMETHODCALLTYPE *RunOnce )( 
            IDATransform3 * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SubstituteTime )( 
            IDATransform3 * This,
            /* [in] */ IDANumber *xform,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchTo )( 
            IDATransform3 * This,
            /* [in] */ IDABehavior *switchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToNumber )( 
            IDATransform3 * This,
            /* [in] */ double numToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToString )( 
            IDATransform3 * This,
            /* [in] */ BSTR strToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *Hook )( 
            IDATransform3 * This,
            /* [in] */ IDABvrHook *notifier,
            /* [retval][out] */ IDABehavior **pBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Duration )( 
            IDATransform3 * This,
            /* [in] */ double duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *DurationAnim )( 
            IDATransform3 * This,
            /* [in] */ IDANumber *duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Repeat )( 
            IDATransform3 * This,
            /* [in] */ LONG count,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *RepeatForever )( 
            IDATransform3 * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *IsReady )( 
            IDATransform3 * This,
            /* [in] */ VARIANT_BOOL bBlock,
            /* [retval][out] */ VARIANT_BOOL *b);
        
        HRESULT ( STDMETHODCALLTYPE *Inverse )( 
            IDATransform3 * This,
            /* [retval][out] */ IDATransform3 **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsSingular )( 
            IDATransform3 * This,
            /* [retval][out] */ IDABoolean **ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *ParallelTransform2 )( 
            IDATransform3 * This,
            /* [retval][out] */ IDATransform2 **ret_0);
        
        END_INTERFACE
    } IDATransform3Vtbl;

    interface IDATransform3
    {
        CONST_VTBL struct IDATransform3Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDATransform3_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDATransform3_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDATransform3_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDATransform3_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDATransform3_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDATransform3_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDATransform3_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDATransform3_GetClassName(This,pClassName)	\
    (This)->lpVtbl -> GetClassName(This,pClassName)

#define IDATransform3_Init(This,toBvr)	\
    (This)->lpVtbl -> Init(This,toBvr)

#define IDATransform3_Importance(This,relativeImportance,ppBvr)	\
    (This)->lpVtbl -> Importance(This,relativeImportance,ppBvr)

#define IDATransform3_RunOnce(This,bvr)	\
    (This)->lpVtbl -> RunOnce(This,bvr)

#define IDATransform3_SubstituteTime(This,xform,bvr)	\
    (This)->lpVtbl -> SubstituteTime(This,xform,bvr)

#define IDATransform3_SwitchTo(This,switchTo)	\
    (This)->lpVtbl -> SwitchTo(This,switchTo)

#define IDATransform3_SwitchToNumber(This,numToSwitchTo)	\
    (This)->lpVtbl -> SwitchToNumber(This,numToSwitchTo)

#define IDATransform3_SwitchToString(This,strToSwitchTo)	\
    (This)->lpVtbl -> SwitchToString(This,strToSwitchTo)

#define IDATransform3_Hook(This,notifier,pBvr)	\
    (This)->lpVtbl -> Hook(This,notifier,pBvr)

#define IDATransform3_Duration(This,duration,bvr)	\
    (This)->lpVtbl -> Duration(This,duration,bvr)

#define IDATransform3_DurationAnim(This,duration,bvr)	\
    (This)->lpVtbl -> DurationAnim(This,duration,bvr)

#define IDATransform3_Repeat(This,count,bvr)	\
    (This)->lpVtbl -> Repeat(This,count,bvr)

#define IDATransform3_RepeatForever(This,bvr)	\
    (This)->lpVtbl -> RepeatForever(This,bvr)

#define IDATransform3_IsReady(This,bBlock,b)	\
    (This)->lpVtbl -> IsReady(This,bBlock,b)


#define IDATransform3_Inverse(This,ret_0)	\
    (This)->lpVtbl -> Inverse(This,ret_0)

#define IDATransform3_get_IsSingular(This,ret_0)	\
    (This)->lpVtbl -> get_IsSingular(This,ret_0)

#define IDATransform3_ParallelTransform2(This,ret_0)	\
    (This)->lpVtbl -> ParallelTransform2(This,ret_0)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDATransform3_Inverse_Proxy( 
    IDATransform3 * This,
    /* [retval][out] */ IDATransform3 **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDATransform3_get_IsSingular_Proxy( 
    IDATransform3 * This,
    /* [retval][out] */ IDABoolean **ret_0);



HRESULT STDMETHODCALLTYPE IDATransform3_ParallelTransform2_Proxy( 
    IDATransform3 * This,
    /* [retval][out] */ IDATransform2 **ret_0);




#endif 	/* __IDATransform3_INTERFACE_DEFINED__ */


#ifndef __IDAVector2_INTERFACE_DEFINED__
#define __IDAVector2_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDAVector2
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][hidden][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDAVector2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("C46C1BC9-3C52-11d0-9200-848C1D000000")
    IDAVector2 : public IDABehavior
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ IDANumber **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_LengthSquared( 
            /* [retval][out] */ IDANumber **ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Normalize( 
            /* [retval][out] */ IDAVector2 **ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MulAnim( 
            /* [in] */ IDANumber *scalar_0,
            /* [retval][out] */ IDAVector2 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Mul( 
            /* [in] */ double scalar_0,
            /* [retval][out] */ IDAVector2 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DivAnim( 
            /* [in] */ IDANumber *scalar_0,
            /* [retval][out] */ IDAVector2 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Div( 
            /* [in] */ double scalar_0,
            /* [retval][out] */ IDAVector2 **ret_1) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_X( 
            /* [retval][out] */ IDANumber **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Y( 
            /* [retval][out] */ IDANumber **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_PolarCoordAngle( 
            /* [retval][out] */ IDANumber **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_PolarCoordLength( 
            /* [retval][out] */ IDANumber **ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Transform( 
            /* [in] */ IDATransform2 *xf_0,
            /* [retval][out] */ IDAVector2 **ret_1) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDAVector2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDAVector2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDAVector2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDAVector2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDAVector2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDAVector2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDAVector2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDAVector2 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassName )( 
            IDAVector2 * This,
            /* [retval][out] */ BSTR *pClassName);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            IDAVector2 * This,
            /* [in] */ IDABehavior *toBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Importance )( 
            IDAVector2 * This,
            /* [in] */ double relativeImportance,
            /* [retval][out] */ IDABehavior **ppBvr);
        
        HRESULT ( STDMETHODCALLTYPE *RunOnce )( 
            IDAVector2 * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SubstituteTime )( 
            IDAVector2 * This,
            /* [in] */ IDANumber *xform,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchTo )( 
            IDAVector2 * This,
            /* [in] */ IDABehavior *switchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToNumber )( 
            IDAVector2 * This,
            /* [in] */ double numToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToString )( 
            IDAVector2 * This,
            /* [in] */ BSTR strToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *Hook )( 
            IDAVector2 * This,
            /* [in] */ IDABvrHook *notifier,
            /* [retval][out] */ IDABehavior **pBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Duration )( 
            IDAVector2 * This,
            /* [in] */ double duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *DurationAnim )( 
            IDAVector2 * This,
            /* [in] */ IDANumber *duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Repeat )( 
            IDAVector2 * This,
            /* [in] */ LONG count,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *RepeatForever )( 
            IDAVector2 * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *IsReady )( 
            IDAVector2 * This,
            /* [in] */ VARIANT_BOOL bBlock,
            /* [retval][out] */ VARIANT_BOOL *b);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IDAVector2 * This,
            /* [retval][out] */ IDANumber **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_LengthSquared )( 
            IDAVector2 * This,
            /* [retval][out] */ IDANumber **ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *Normalize )( 
            IDAVector2 * This,
            /* [retval][out] */ IDAVector2 **ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *MulAnim )( 
            IDAVector2 * This,
            /* [in] */ IDANumber *scalar_0,
            /* [retval][out] */ IDAVector2 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Mul )( 
            IDAVector2 * This,
            /* [in] */ double scalar_0,
            /* [retval][out] */ IDAVector2 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *DivAnim )( 
            IDAVector2 * This,
            /* [in] */ IDANumber *scalar_0,
            /* [retval][out] */ IDAVector2 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Div )( 
            IDAVector2 * This,
            /* [in] */ double scalar_0,
            /* [retval][out] */ IDAVector2 **ret_1);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_X )( 
            IDAVector2 * This,
            /* [retval][out] */ IDANumber **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Y )( 
            IDAVector2 * This,
            /* [retval][out] */ IDANumber **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_PolarCoordAngle )( 
            IDAVector2 * This,
            /* [retval][out] */ IDANumber **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_PolarCoordLength )( 
            IDAVector2 * This,
            /* [retval][out] */ IDANumber **ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *Transform )( 
            IDAVector2 * This,
            /* [in] */ IDATransform2 *xf_0,
            /* [retval][out] */ IDAVector2 **ret_1);
        
        END_INTERFACE
    } IDAVector2Vtbl;

    interface IDAVector2
    {
        CONST_VTBL struct IDAVector2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDAVector2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDAVector2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDAVector2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDAVector2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDAVector2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDAVector2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDAVector2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDAVector2_GetClassName(This,pClassName)	\
    (This)->lpVtbl -> GetClassName(This,pClassName)

#define IDAVector2_Init(This,toBvr)	\
    (This)->lpVtbl -> Init(This,toBvr)

#define IDAVector2_Importance(This,relativeImportance,ppBvr)	\
    (This)->lpVtbl -> Importance(This,relativeImportance,ppBvr)

#define IDAVector2_RunOnce(This,bvr)	\
    (This)->lpVtbl -> RunOnce(This,bvr)

#define IDAVector2_SubstituteTime(This,xform,bvr)	\
    (This)->lpVtbl -> SubstituteTime(This,xform,bvr)

#define IDAVector2_SwitchTo(This,switchTo)	\
    (This)->lpVtbl -> SwitchTo(This,switchTo)

#define IDAVector2_SwitchToNumber(This,numToSwitchTo)	\
    (This)->lpVtbl -> SwitchToNumber(This,numToSwitchTo)

#define IDAVector2_SwitchToString(This,strToSwitchTo)	\
    (This)->lpVtbl -> SwitchToString(This,strToSwitchTo)

#define IDAVector2_Hook(This,notifier,pBvr)	\
    (This)->lpVtbl -> Hook(This,notifier,pBvr)

#define IDAVector2_Duration(This,duration,bvr)	\
    (This)->lpVtbl -> Duration(This,duration,bvr)

#define IDAVector2_DurationAnim(This,duration,bvr)	\
    (This)->lpVtbl -> DurationAnim(This,duration,bvr)

#define IDAVector2_Repeat(This,count,bvr)	\
    (This)->lpVtbl -> Repeat(This,count,bvr)

#define IDAVector2_RepeatForever(This,bvr)	\
    (This)->lpVtbl -> RepeatForever(This,bvr)

#define IDAVector2_IsReady(This,bBlock,b)	\
    (This)->lpVtbl -> IsReady(This,bBlock,b)


#define IDAVector2_get_Length(This,ret_0)	\
    (This)->lpVtbl -> get_Length(This,ret_0)

#define IDAVector2_get_LengthSquared(This,ret_0)	\
    (This)->lpVtbl -> get_LengthSquared(This,ret_0)

#define IDAVector2_Normalize(This,ret_0)	\
    (This)->lpVtbl -> Normalize(This,ret_0)

#define IDAVector2_MulAnim(This,scalar_0,ret_1)	\
    (This)->lpVtbl -> MulAnim(This,scalar_0,ret_1)

#define IDAVector2_Mul(This,scalar_0,ret_1)	\
    (This)->lpVtbl -> Mul(This,scalar_0,ret_1)

#define IDAVector2_DivAnim(This,scalar_0,ret_1)	\
    (This)->lpVtbl -> DivAnim(This,scalar_0,ret_1)

#define IDAVector2_Div(This,scalar_0,ret_1)	\
    (This)->lpVtbl -> Div(This,scalar_0,ret_1)

#define IDAVector2_get_X(This,ret_0)	\
    (This)->lpVtbl -> get_X(This,ret_0)

#define IDAVector2_get_Y(This,ret_0)	\
    (This)->lpVtbl -> get_Y(This,ret_0)

#define IDAVector2_get_PolarCoordAngle(This,ret_0)	\
    (This)->lpVtbl -> get_PolarCoordAngle(This,ret_0)

#define IDAVector2_get_PolarCoordLength(This,ret_0)	\
    (This)->lpVtbl -> get_PolarCoordLength(This,ret_0)

#define IDAVector2_Transform(This,xf_0,ret_1)	\
    (This)->lpVtbl -> Transform(This,xf_0,ret_1)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAVector2_get_Length_Proxy( 
    IDAVector2 * This,
    /* [retval][out] */ IDANumber **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAVector2_get_LengthSquared_Proxy( 
    IDAVector2 * This,
    /* [retval][out] */ IDANumber **ret_0);



HRESULT STDMETHODCALLTYPE IDAVector2_Normalize_Proxy( 
    IDAVector2 * This,
    /* [retval][out] */ IDAVector2 **ret_0);



HRESULT STDMETHODCALLTYPE IDAVector2_MulAnim_Proxy( 
    IDAVector2 * This,
    /* [in] */ IDANumber *scalar_0,
    /* [retval][out] */ IDAVector2 **ret_1);



HRESULT STDMETHODCALLTYPE IDAVector2_Mul_Proxy( 
    IDAVector2 * This,
    /* [in] */ double scalar_0,
    /* [retval][out] */ IDAVector2 **ret_1);



HRESULT STDMETHODCALLTYPE IDAVector2_DivAnim_Proxy( 
    IDAVector2 * This,
    /* [in] */ IDANumber *scalar_0,
    /* [retval][out] */ IDAVector2 **ret_1);



HRESULT STDMETHODCALLTYPE IDAVector2_Div_Proxy( 
    IDAVector2 * This,
    /* [in] */ double scalar_0,
    /* [retval][out] */ IDAVector2 **ret_1);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAVector2_get_X_Proxy( 
    IDAVector2 * This,
    /* [retval][out] */ IDANumber **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAVector2_get_Y_Proxy( 
    IDAVector2 * This,
    /* [retval][out] */ IDANumber **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAVector2_get_PolarCoordAngle_Proxy( 
    IDAVector2 * This,
    /* [retval][out] */ IDANumber **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAVector2_get_PolarCoordLength_Proxy( 
    IDAVector2 * This,
    /* [retval][out] */ IDANumber **ret_0);



HRESULT STDMETHODCALLTYPE IDAVector2_Transform_Proxy( 
    IDAVector2 * This,
    /* [in] */ IDATransform2 *xf_0,
    /* [retval][out] */ IDAVector2 **ret_1);




#endif 	/* __IDAVector2_INTERFACE_DEFINED__ */


#ifndef __IDAVector3_INTERFACE_DEFINED__
#define __IDAVector3_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDAVector3
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][hidden][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDAVector3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("C46C1BD9-3C52-11d0-9200-848C1D000000")
    IDAVector3 : public IDABehavior
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ IDANumber **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_LengthSquared( 
            /* [retval][out] */ IDANumber **ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Normalize( 
            /* [retval][out] */ IDAVector3 **ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MulAnim( 
            /* [in] */ IDANumber *scalar_0,
            /* [retval][out] */ IDAVector3 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Mul( 
            /* [in] */ double scalar_0,
            /* [retval][out] */ IDAVector3 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DivAnim( 
            /* [in] */ IDANumber *scalar_0,
            /* [retval][out] */ IDAVector3 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Div( 
            /* [in] */ double scalar_0,
            /* [retval][out] */ IDAVector3 **ret_1) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_X( 
            /* [retval][out] */ IDANumber **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Y( 
            /* [retval][out] */ IDANumber **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Z( 
            /* [retval][out] */ IDANumber **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_SphericalCoordXYAngle( 
            /* [retval][out] */ IDANumber **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_SphericalCoordYZAngle( 
            /* [retval][out] */ IDANumber **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_SphericalCoordLength( 
            /* [retval][out] */ IDANumber **ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Transform( 
            /* [in] */ IDATransform3 *xf_0,
            /* [retval][out] */ IDAVector3 **ret_1) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDAVector3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDAVector3 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDAVector3 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDAVector3 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDAVector3 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDAVector3 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDAVector3 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDAVector3 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassName )( 
            IDAVector3 * This,
            /* [retval][out] */ BSTR *pClassName);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            IDAVector3 * This,
            /* [in] */ IDABehavior *toBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Importance )( 
            IDAVector3 * This,
            /* [in] */ double relativeImportance,
            /* [retval][out] */ IDABehavior **ppBvr);
        
        HRESULT ( STDMETHODCALLTYPE *RunOnce )( 
            IDAVector3 * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SubstituteTime )( 
            IDAVector3 * This,
            /* [in] */ IDANumber *xform,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchTo )( 
            IDAVector3 * This,
            /* [in] */ IDABehavior *switchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToNumber )( 
            IDAVector3 * This,
            /* [in] */ double numToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToString )( 
            IDAVector3 * This,
            /* [in] */ BSTR strToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *Hook )( 
            IDAVector3 * This,
            /* [in] */ IDABvrHook *notifier,
            /* [retval][out] */ IDABehavior **pBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Duration )( 
            IDAVector3 * This,
            /* [in] */ double duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *DurationAnim )( 
            IDAVector3 * This,
            /* [in] */ IDANumber *duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Repeat )( 
            IDAVector3 * This,
            /* [in] */ LONG count,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *RepeatForever )( 
            IDAVector3 * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *IsReady )( 
            IDAVector3 * This,
            /* [in] */ VARIANT_BOOL bBlock,
            /* [retval][out] */ VARIANT_BOOL *b);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IDAVector3 * This,
            /* [retval][out] */ IDANumber **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_LengthSquared )( 
            IDAVector3 * This,
            /* [retval][out] */ IDANumber **ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *Normalize )( 
            IDAVector3 * This,
            /* [retval][out] */ IDAVector3 **ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *MulAnim )( 
            IDAVector3 * This,
            /* [in] */ IDANumber *scalar_0,
            /* [retval][out] */ IDAVector3 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Mul )( 
            IDAVector3 * This,
            /* [in] */ double scalar_0,
            /* [retval][out] */ IDAVector3 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *DivAnim )( 
            IDAVector3 * This,
            /* [in] */ IDANumber *scalar_0,
            /* [retval][out] */ IDAVector3 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Div )( 
            IDAVector3 * This,
            /* [in] */ double scalar_0,
            /* [retval][out] */ IDAVector3 **ret_1);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_X )( 
            IDAVector3 * This,
            /* [retval][out] */ IDANumber **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Y )( 
            IDAVector3 * This,
            /* [retval][out] */ IDANumber **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Z )( 
            IDAVector3 * This,
            /* [retval][out] */ IDANumber **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_SphericalCoordXYAngle )( 
            IDAVector3 * This,
            /* [retval][out] */ IDANumber **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_SphericalCoordYZAngle )( 
            IDAVector3 * This,
            /* [retval][out] */ IDANumber **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_SphericalCoordLength )( 
            IDAVector3 * This,
            /* [retval][out] */ IDANumber **ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *Transform )( 
            IDAVector3 * This,
            /* [in] */ IDATransform3 *xf_0,
            /* [retval][out] */ IDAVector3 **ret_1);
        
        END_INTERFACE
    } IDAVector3Vtbl;

    interface IDAVector3
    {
        CONST_VTBL struct IDAVector3Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDAVector3_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDAVector3_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDAVector3_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDAVector3_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDAVector3_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDAVector3_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDAVector3_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDAVector3_GetClassName(This,pClassName)	\
    (This)->lpVtbl -> GetClassName(This,pClassName)

#define IDAVector3_Init(This,toBvr)	\
    (This)->lpVtbl -> Init(This,toBvr)

#define IDAVector3_Importance(This,relativeImportance,ppBvr)	\
    (This)->lpVtbl -> Importance(This,relativeImportance,ppBvr)

#define IDAVector3_RunOnce(This,bvr)	\
    (This)->lpVtbl -> RunOnce(This,bvr)

#define IDAVector3_SubstituteTime(This,xform,bvr)	\
    (This)->lpVtbl -> SubstituteTime(This,xform,bvr)

#define IDAVector3_SwitchTo(This,switchTo)	\
    (This)->lpVtbl -> SwitchTo(This,switchTo)

#define IDAVector3_SwitchToNumber(This,numToSwitchTo)	\
    (This)->lpVtbl -> SwitchToNumber(This,numToSwitchTo)

#define IDAVector3_SwitchToString(This,strToSwitchTo)	\
    (This)->lpVtbl -> SwitchToString(This,strToSwitchTo)

#define IDAVector3_Hook(This,notifier,pBvr)	\
    (This)->lpVtbl -> Hook(This,notifier,pBvr)

#define IDAVector3_Duration(This,duration,bvr)	\
    (This)->lpVtbl -> Duration(This,duration,bvr)

#define IDAVector3_DurationAnim(This,duration,bvr)	\
    (This)->lpVtbl -> DurationAnim(This,duration,bvr)

#define IDAVector3_Repeat(This,count,bvr)	\
    (This)->lpVtbl -> Repeat(This,count,bvr)

#define IDAVector3_RepeatForever(This,bvr)	\
    (This)->lpVtbl -> RepeatForever(This,bvr)

#define IDAVector3_IsReady(This,bBlock,b)	\
    (This)->lpVtbl -> IsReady(This,bBlock,b)


#define IDAVector3_get_Length(This,ret_0)	\
    (This)->lpVtbl -> get_Length(This,ret_0)

#define IDAVector3_get_LengthSquared(This,ret_0)	\
    (This)->lpVtbl -> get_LengthSquared(This,ret_0)

#define IDAVector3_Normalize(This,ret_0)	\
    (This)->lpVtbl -> Normalize(This,ret_0)

#define IDAVector3_MulAnim(This,scalar_0,ret_1)	\
    (This)->lpVtbl -> MulAnim(This,scalar_0,ret_1)

#define IDAVector3_Mul(This,scalar_0,ret_1)	\
    (This)->lpVtbl -> Mul(This,scalar_0,ret_1)

#define IDAVector3_DivAnim(This,scalar_0,ret_1)	\
    (This)->lpVtbl -> DivAnim(This,scalar_0,ret_1)

#define IDAVector3_Div(This,scalar_0,ret_1)	\
    (This)->lpVtbl -> Div(This,scalar_0,ret_1)

#define IDAVector3_get_X(This,ret_0)	\
    (This)->lpVtbl -> get_X(This,ret_0)

#define IDAVector3_get_Y(This,ret_0)	\
    (This)->lpVtbl -> get_Y(This,ret_0)

#define IDAVector3_get_Z(This,ret_0)	\
    (This)->lpVtbl -> get_Z(This,ret_0)

#define IDAVector3_get_SphericalCoordXYAngle(This,ret_0)	\
    (This)->lpVtbl -> get_SphericalCoordXYAngle(This,ret_0)

#define IDAVector3_get_SphericalCoordYZAngle(This,ret_0)	\
    (This)->lpVtbl -> get_SphericalCoordYZAngle(This,ret_0)

#define IDAVector3_get_SphericalCoordLength(This,ret_0)	\
    (This)->lpVtbl -> get_SphericalCoordLength(This,ret_0)

#define IDAVector3_Transform(This,xf_0,ret_1)	\
    (This)->lpVtbl -> Transform(This,xf_0,ret_1)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAVector3_get_Length_Proxy( 
    IDAVector3 * This,
    /* [retval][out] */ IDANumber **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAVector3_get_LengthSquared_Proxy( 
    IDAVector3 * This,
    /* [retval][out] */ IDANumber **ret_0);



HRESULT STDMETHODCALLTYPE IDAVector3_Normalize_Proxy( 
    IDAVector3 * This,
    /* [retval][out] */ IDAVector3 **ret_0);



HRESULT STDMETHODCALLTYPE IDAVector3_MulAnim_Proxy( 
    IDAVector3 * This,
    /* [in] */ IDANumber *scalar_0,
    /* [retval][out] */ IDAVector3 **ret_1);



HRESULT STDMETHODCALLTYPE IDAVector3_Mul_Proxy( 
    IDAVector3 * This,
    /* [in] */ double scalar_0,
    /* [retval][out] */ IDAVector3 **ret_1);



HRESULT STDMETHODCALLTYPE IDAVector3_DivAnim_Proxy( 
    IDAVector3 * This,
    /* [in] */ IDANumber *scalar_0,
    /* [retval][out] */ IDAVector3 **ret_1);



HRESULT STDMETHODCALLTYPE IDAVector3_Div_Proxy( 
    IDAVector3 * This,
    /* [in] */ double scalar_0,
    /* [retval][out] */ IDAVector3 **ret_1);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAVector3_get_X_Proxy( 
    IDAVector3 * This,
    /* [retval][out] */ IDANumber **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAVector3_get_Y_Proxy( 
    IDAVector3 * This,
    /* [retval][out] */ IDANumber **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAVector3_get_Z_Proxy( 
    IDAVector3 * This,
    /* [retval][out] */ IDANumber **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAVector3_get_SphericalCoordXYAngle_Proxy( 
    IDAVector3 * This,
    /* [retval][out] */ IDANumber **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAVector3_get_SphericalCoordYZAngle_Proxy( 
    IDAVector3 * This,
    /* [retval][out] */ IDANumber **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAVector3_get_SphericalCoordLength_Proxy( 
    IDAVector3 * This,
    /* [retval][out] */ IDANumber **ret_0);



HRESULT STDMETHODCALLTYPE IDAVector3_Transform_Proxy( 
    IDAVector3 * This,
    /* [in] */ IDATransform3 *xf_0,
    /* [retval][out] */ IDAVector3 **ret_1);




#endif 	/* __IDAVector3_INTERFACE_DEFINED__ */


#ifndef __IDAFontStyle_INTERFACE_DEFINED__
#define __IDAFontStyle_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDAFontStyle
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][hidden][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDAFontStyle;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("25B0F91D-D23D-11d0-9B85-00C04FC2F51D")
    IDAFontStyle : public IDABehavior
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Bold( 
            /* [retval][out] */ IDAFontStyle **ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Italic( 
            /* [retval][out] */ IDAFontStyle **ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Underline( 
            /* [retval][out] */ IDAFontStyle **ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Strikethrough( 
            /* [retval][out] */ IDAFontStyle **ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AntiAliasing( 
            /* [in] */ double aaStyle_0,
            /* [retval][out] */ IDAFontStyle **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Color( 
            /* [in] */ IDAColor *col_0,
            /* [retval][out] */ IDAFontStyle **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FamilyAnim( 
            /* [in] */ IDAString *face_0,
            /* [retval][out] */ IDAFontStyle **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Family( 
            /* [in] */ BSTR face_0,
            /* [retval][out] */ IDAFontStyle **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SizeAnim( 
            /* [in] */ IDANumber *size_0,
            /* [retval][out] */ IDAFontStyle **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Size( 
            /* [in] */ double size_0,
            /* [retval][out] */ IDAFontStyle **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Weight( 
            /* [in] */ double weight_0,
            /* [retval][out] */ IDAFontStyle **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE WeightAnim( 
            /* [in] */ IDANumber *weight_0,
            /* [retval][out] */ IDAFontStyle **ret_1) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDAFontStyleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDAFontStyle * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDAFontStyle * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDAFontStyle * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDAFontStyle * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDAFontStyle * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDAFontStyle * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDAFontStyle * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassName )( 
            IDAFontStyle * This,
            /* [retval][out] */ BSTR *pClassName);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            IDAFontStyle * This,
            /* [in] */ IDABehavior *toBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Importance )( 
            IDAFontStyle * This,
            /* [in] */ double relativeImportance,
            /* [retval][out] */ IDABehavior **ppBvr);
        
        HRESULT ( STDMETHODCALLTYPE *RunOnce )( 
            IDAFontStyle * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SubstituteTime )( 
            IDAFontStyle * This,
            /* [in] */ IDANumber *xform,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchTo )( 
            IDAFontStyle * This,
            /* [in] */ IDABehavior *switchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToNumber )( 
            IDAFontStyle * This,
            /* [in] */ double numToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToString )( 
            IDAFontStyle * This,
            /* [in] */ BSTR strToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *Hook )( 
            IDAFontStyle * This,
            /* [in] */ IDABvrHook *notifier,
            /* [retval][out] */ IDABehavior **pBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Duration )( 
            IDAFontStyle * This,
            /* [in] */ double duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *DurationAnim )( 
            IDAFontStyle * This,
            /* [in] */ IDANumber *duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Repeat )( 
            IDAFontStyle * This,
            /* [in] */ LONG count,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *RepeatForever )( 
            IDAFontStyle * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *IsReady )( 
            IDAFontStyle * This,
            /* [in] */ VARIANT_BOOL bBlock,
            /* [retval][out] */ VARIANT_BOOL *b);
        
        HRESULT ( STDMETHODCALLTYPE *Bold )( 
            IDAFontStyle * This,
            /* [retval][out] */ IDAFontStyle **ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *Italic )( 
            IDAFontStyle * This,
            /* [retval][out] */ IDAFontStyle **ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *Underline )( 
            IDAFontStyle * This,
            /* [retval][out] */ IDAFontStyle **ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *Strikethrough )( 
            IDAFontStyle * This,
            /* [retval][out] */ IDAFontStyle **ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *AntiAliasing )( 
            IDAFontStyle * This,
            /* [in] */ double aaStyle_0,
            /* [retval][out] */ IDAFontStyle **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Color )( 
            IDAFontStyle * This,
            /* [in] */ IDAColor *col_0,
            /* [retval][out] */ IDAFontStyle **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *FamilyAnim )( 
            IDAFontStyle * This,
            /* [in] */ IDAString *face_0,
            /* [retval][out] */ IDAFontStyle **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Family )( 
            IDAFontStyle * This,
            /* [in] */ BSTR face_0,
            /* [retval][out] */ IDAFontStyle **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *SizeAnim )( 
            IDAFontStyle * This,
            /* [in] */ IDANumber *size_0,
            /* [retval][out] */ IDAFontStyle **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Size )( 
            IDAFontStyle * This,
            /* [in] */ double size_0,
            /* [retval][out] */ IDAFontStyle **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Weight )( 
            IDAFontStyle * This,
            /* [in] */ double weight_0,
            /* [retval][out] */ IDAFontStyle **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *WeightAnim )( 
            IDAFontStyle * This,
            /* [in] */ IDANumber *weight_0,
            /* [retval][out] */ IDAFontStyle **ret_1);
        
        END_INTERFACE
    } IDAFontStyleVtbl;

    interface IDAFontStyle
    {
        CONST_VTBL struct IDAFontStyleVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDAFontStyle_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDAFontStyle_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDAFontStyle_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDAFontStyle_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDAFontStyle_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDAFontStyle_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDAFontStyle_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDAFontStyle_GetClassName(This,pClassName)	\
    (This)->lpVtbl -> GetClassName(This,pClassName)

#define IDAFontStyle_Init(This,toBvr)	\
    (This)->lpVtbl -> Init(This,toBvr)

#define IDAFontStyle_Importance(This,relativeImportance,ppBvr)	\
    (This)->lpVtbl -> Importance(This,relativeImportance,ppBvr)

#define IDAFontStyle_RunOnce(This,bvr)	\
    (This)->lpVtbl -> RunOnce(This,bvr)

#define IDAFontStyle_SubstituteTime(This,xform,bvr)	\
    (This)->lpVtbl -> SubstituteTime(This,xform,bvr)

#define IDAFontStyle_SwitchTo(This,switchTo)	\
    (This)->lpVtbl -> SwitchTo(This,switchTo)

#define IDAFontStyle_SwitchToNumber(This,numToSwitchTo)	\
    (This)->lpVtbl -> SwitchToNumber(This,numToSwitchTo)

#define IDAFontStyle_SwitchToString(This,strToSwitchTo)	\
    (This)->lpVtbl -> SwitchToString(This,strToSwitchTo)

#define IDAFontStyle_Hook(This,notifier,pBvr)	\
    (This)->lpVtbl -> Hook(This,notifier,pBvr)

#define IDAFontStyle_Duration(This,duration,bvr)	\
    (This)->lpVtbl -> Duration(This,duration,bvr)

#define IDAFontStyle_DurationAnim(This,duration,bvr)	\
    (This)->lpVtbl -> DurationAnim(This,duration,bvr)

#define IDAFontStyle_Repeat(This,count,bvr)	\
    (This)->lpVtbl -> Repeat(This,count,bvr)

#define IDAFontStyle_RepeatForever(This,bvr)	\
    (This)->lpVtbl -> RepeatForever(This,bvr)

#define IDAFontStyle_IsReady(This,bBlock,b)	\
    (This)->lpVtbl -> IsReady(This,bBlock,b)


#define IDAFontStyle_Bold(This,ret_0)	\
    (This)->lpVtbl -> Bold(This,ret_0)

#define IDAFontStyle_Italic(This,ret_0)	\
    (This)->lpVtbl -> Italic(This,ret_0)

#define IDAFontStyle_Underline(This,ret_0)	\
    (This)->lpVtbl -> Underline(This,ret_0)

#define IDAFontStyle_Strikethrough(This,ret_0)	\
    (This)->lpVtbl -> Strikethrough(This,ret_0)

#define IDAFontStyle_AntiAliasing(This,aaStyle_0,ret_1)	\
    (This)->lpVtbl -> AntiAliasing(This,aaStyle_0,ret_1)

#define IDAFontStyle_Color(This,col_0,ret_1)	\
    (This)->lpVtbl -> Color(This,col_0,ret_1)

#define IDAFontStyle_FamilyAnim(This,face_0,ret_1)	\
    (This)->lpVtbl -> FamilyAnim(This,face_0,ret_1)

#define IDAFontStyle_Family(This,face_0,ret_1)	\
    (This)->lpVtbl -> Family(This,face_0,ret_1)

#define IDAFontStyle_SizeAnim(This,size_0,ret_1)	\
    (This)->lpVtbl -> SizeAnim(This,size_0,ret_1)

#define IDAFontStyle_Size(This,size_0,ret_1)	\
    (This)->lpVtbl -> Size(This,size_0,ret_1)

#define IDAFontStyle_Weight(This,weight_0,ret_1)	\
    (This)->lpVtbl -> Weight(This,weight_0,ret_1)

#define IDAFontStyle_WeightAnim(This,weight_0,ret_1)	\
    (This)->lpVtbl -> WeightAnim(This,weight_0,ret_1)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDAFontStyle_Bold_Proxy( 
    IDAFontStyle * This,
    /* [retval][out] */ IDAFontStyle **ret_0);



HRESULT STDMETHODCALLTYPE IDAFontStyle_Italic_Proxy( 
    IDAFontStyle * This,
    /* [retval][out] */ IDAFontStyle **ret_0);



HRESULT STDMETHODCALLTYPE IDAFontStyle_Underline_Proxy( 
    IDAFontStyle * This,
    /* [retval][out] */ IDAFontStyle **ret_0);



HRESULT STDMETHODCALLTYPE IDAFontStyle_Strikethrough_Proxy( 
    IDAFontStyle * This,
    /* [retval][out] */ IDAFontStyle **ret_0);



HRESULT STDMETHODCALLTYPE IDAFontStyle_AntiAliasing_Proxy( 
    IDAFontStyle * This,
    /* [in] */ double aaStyle_0,
    /* [retval][out] */ IDAFontStyle **ret_1);



HRESULT STDMETHODCALLTYPE IDAFontStyle_Color_Proxy( 
    IDAFontStyle * This,
    /* [in] */ IDAColor *col_0,
    /* [retval][out] */ IDAFontStyle **ret_1);



HRESULT STDMETHODCALLTYPE IDAFontStyle_FamilyAnim_Proxy( 
    IDAFontStyle * This,
    /* [in] */ IDAString *face_0,
    /* [retval][out] */ IDAFontStyle **ret_1);



HRESULT STDMETHODCALLTYPE IDAFontStyle_Family_Proxy( 
    IDAFontStyle * This,
    /* [in] */ BSTR face_0,
    /* [retval][out] */ IDAFontStyle **ret_1);



HRESULT STDMETHODCALLTYPE IDAFontStyle_SizeAnim_Proxy( 
    IDAFontStyle * This,
    /* [in] */ IDANumber *size_0,
    /* [retval][out] */ IDAFontStyle **ret_1);



HRESULT STDMETHODCALLTYPE IDAFontStyle_Size_Proxy( 
    IDAFontStyle * This,
    /* [in] */ double size_0,
    /* [retval][out] */ IDAFontStyle **ret_1);



HRESULT STDMETHODCALLTYPE IDAFontStyle_Weight_Proxy( 
    IDAFontStyle * This,
    /* [in] */ double weight_0,
    /* [retval][out] */ IDAFontStyle **ret_1);



HRESULT STDMETHODCALLTYPE IDAFontStyle_WeightAnim_Proxy( 
    IDAFontStyle * This,
    /* [in] */ IDANumber *weight_0,
    /* [retval][out] */ IDAFontStyle **ret_1);




#endif 	/* __IDAFontStyle_INTERFACE_DEFINED__ */


#ifndef __IDALineStyle_INTERFACE_DEFINED__
#define __IDALineStyle_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDALineStyle
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][hidden][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDALineStyle;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("C46C1BF1-3C52-11d0-9200-848C1D000000")
    IDALineStyle : public IDABehavior
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE End( 
            /* [in] */ IDAEndStyle *sty_0,
            /* [retval][out] */ IDALineStyle **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Join( 
            /* [in] */ IDAJoinStyle *sty_0,
            /* [retval][out] */ IDALineStyle **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Dash( 
            /* [in] */ IDADashStyle *sty_0,
            /* [retval][out] */ IDALineStyle **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE WidthAnim( 
            /* [in] */ IDANumber *sty_0,
            /* [retval][out] */ IDALineStyle **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE width( 
            /* [in] */ double sty_0,
            /* [retval][out] */ IDALineStyle **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AntiAliasing( 
            /* [in] */ double aaStyle_0,
            /* [retval][out] */ IDALineStyle **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Detail( 
            /* [retval][out] */ IDALineStyle **ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Color( 
            /* [in] */ IDAColor *clr_0,
            /* [retval][out] */ IDALineStyle **ret_1) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDALineStyleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDALineStyle * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDALineStyle * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDALineStyle * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDALineStyle * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDALineStyle * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDALineStyle * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDALineStyle * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassName )( 
            IDALineStyle * This,
            /* [retval][out] */ BSTR *pClassName);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            IDALineStyle * This,
            /* [in] */ IDABehavior *toBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Importance )( 
            IDALineStyle * This,
            /* [in] */ double relativeImportance,
            /* [retval][out] */ IDABehavior **ppBvr);
        
        HRESULT ( STDMETHODCALLTYPE *RunOnce )( 
            IDALineStyle * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SubstituteTime )( 
            IDALineStyle * This,
            /* [in] */ IDANumber *xform,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchTo )( 
            IDALineStyle * This,
            /* [in] */ IDABehavior *switchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToNumber )( 
            IDALineStyle * This,
            /* [in] */ double numToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToString )( 
            IDALineStyle * This,
            /* [in] */ BSTR strToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *Hook )( 
            IDALineStyle * This,
            /* [in] */ IDABvrHook *notifier,
            /* [retval][out] */ IDABehavior **pBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Duration )( 
            IDALineStyle * This,
            /* [in] */ double duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *DurationAnim )( 
            IDALineStyle * This,
            /* [in] */ IDANumber *duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Repeat )( 
            IDALineStyle * This,
            /* [in] */ LONG count,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *RepeatForever )( 
            IDALineStyle * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *IsReady )( 
            IDALineStyle * This,
            /* [in] */ VARIANT_BOOL bBlock,
            /* [retval][out] */ VARIANT_BOOL *b);
        
        HRESULT ( STDMETHODCALLTYPE *End )( 
            IDALineStyle * This,
            /* [in] */ IDAEndStyle *sty_0,
            /* [retval][out] */ IDALineStyle **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Join )( 
            IDALineStyle * This,
            /* [in] */ IDAJoinStyle *sty_0,
            /* [retval][out] */ IDALineStyle **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Dash )( 
            IDALineStyle * This,
            /* [in] */ IDADashStyle *sty_0,
            /* [retval][out] */ IDALineStyle **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *WidthAnim )( 
            IDALineStyle * This,
            /* [in] */ IDANumber *sty_0,
            /* [retval][out] */ IDALineStyle **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *width )( 
            IDALineStyle * This,
            /* [in] */ double sty_0,
            /* [retval][out] */ IDALineStyle **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *AntiAliasing )( 
            IDALineStyle * This,
            /* [in] */ double aaStyle_0,
            /* [retval][out] */ IDALineStyle **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Detail )( 
            IDALineStyle * This,
            /* [retval][out] */ IDALineStyle **ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *Color )( 
            IDALineStyle * This,
            /* [in] */ IDAColor *clr_0,
            /* [retval][out] */ IDALineStyle **ret_1);
        
        END_INTERFACE
    } IDALineStyleVtbl;

    interface IDALineStyle
    {
        CONST_VTBL struct IDALineStyleVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDALineStyle_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDALineStyle_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDALineStyle_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDALineStyle_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDALineStyle_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDALineStyle_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDALineStyle_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDALineStyle_GetClassName(This,pClassName)	\
    (This)->lpVtbl -> GetClassName(This,pClassName)

#define IDALineStyle_Init(This,toBvr)	\
    (This)->lpVtbl -> Init(This,toBvr)

#define IDALineStyle_Importance(This,relativeImportance,ppBvr)	\
    (This)->lpVtbl -> Importance(This,relativeImportance,ppBvr)

#define IDALineStyle_RunOnce(This,bvr)	\
    (This)->lpVtbl -> RunOnce(This,bvr)

#define IDALineStyle_SubstituteTime(This,xform,bvr)	\
    (This)->lpVtbl -> SubstituteTime(This,xform,bvr)

#define IDALineStyle_SwitchTo(This,switchTo)	\
    (This)->lpVtbl -> SwitchTo(This,switchTo)

#define IDALineStyle_SwitchToNumber(This,numToSwitchTo)	\
    (This)->lpVtbl -> SwitchToNumber(This,numToSwitchTo)

#define IDALineStyle_SwitchToString(This,strToSwitchTo)	\
    (This)->lpVtbl -> SwitchToString(This,strToSwitchTo)

#define IDALineStyle_Hook(This,notifier,pBvr)	\
    (This)->lpVtbl -> Hook(This,notifier,pBvr)

#define IDALineStyle_Duration(This,duration,bvr)	\
    (This)->lpVtbl -> Duration(This,duration,bvr)

#define IDALineStyle_DurationAnim(This,duration,bvr)	\
    (This)->lpVtbl -> DurationAnim(This,duration,bvr)

#define IDALineStyle_Repeat(This,count,bvr)	\
    (This)->lpVtbl -> Repeat(This,count,bvr)

#define IDALineStyle_RepeatForever(This,bvr)	\
    (This)->lpVtbl -> RepeatForever(This,bvr)

#define IDALineStyle_IsReady(This,bBlock,b)	\
    (This)->lpVtbl -> IsReady(This,bBlock,b)


#define IDALineStyle_End(This,sty_0,ret_1)	\
    (This)->lpVtbl -> End(This,sty_0,ret_1)

#define IDALineStyle_Join(This,sty_0,ret_1)	\
    (This)->lpVtbl -> Join(This,sty_0,ret_1)

#define IDALineStyle_Dash(This,sty_0,ret_1)	\
    (This)->lpVtbl -> Dash(This,sty_0,ret_1)

#define IDALineStyle_WidthAnim(This,sty_0,ret_1)	\
    (This)->lpVtbl -> WidthAnim(This,sty_0,ret_1)

#define IDALineStyle_width(This,sty_0,ret_1)	\
    (This)->lpVtbl -> width(This,sty_0,ret_1)

#define IDALineStyle_AntiAliasing(This,aaStyle_0,ret_1)	\
    (This)->lpVtbl -> AntiAliasing(This,aaStyle_0,ret_1)

#define IDALineStyle_Detail(This,ret_0)	\
    (This)->lpVtbl -> Detail(This,ret_0)

#define IDALineStyle_Color(This,clr_0,ret_1)	\
    (This)->lpVtbl -> Color(This,clr_0,ret_1)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDALineStyle_End_Proxy( 
    IDALineStyle * This,
    /* [in] */ IDAEndStyle *sty_0,
    /* [retval][out] */ IDALineStyle **ret_1);



HRESULT STDMETHODCALLTYPE IDALineStyle_Join_Proxy( 
    IDALineStyle * This,
    /* [in] */ IDAJoinStyle *sty_0,
    /* [retval][out] */ IDALineStyle **ret_1);



HRESULT STDMETHODCALLTYPE IDALineStyle_Dash_Proxy( 
    IDALineStyle * This,
    /* [in] */ IDADashStyle *sty_0,
    /* [retval][out] */ IDALineStyle **ret_1);



HRESULT STDMETHODCALLTYPE IDALineStyle_WidthAnim_Proxy( 
    IDALineStyle * This,
    /* [in] */ IDANumber *sty_0,
    /* [retval][out] */ IDALineStyle **ret_1);



HRESULT STDMETHODCALLTYPE IDALineStyle_width_Proxy( 
    IDALineStyle * This,
    /* [in] */ double sty_0,
    /* [retval][out] */ IDALineStyle **ret_1);



HRESULT STDMETHODCALLTYPE IDALineStyle_AntiAliasing_Proxy( 
    IDALineStyle * This,
    /* [in] */ double aaStyle_0,
    /* [retval][out] */ IDALineStyle **ret_1);



HRESULT STDMETHODCALLTYPE IDALineStyle_Detail_Proxy( 
    IDALineStyle * This,
    /* [retval][out] */ IDALineStyle **ret_0);



HRESULT STDMETHODCALLTYPE IDALineStyle_Color_Proxy( 
    IDALineStyle * This,
    /* [in] */ IDAColor *clr_0,
    /* [retval][out] */ IDALineStyle **ret_1);




#endif 	/* __IDALineStyle_INTERFACE_DEFINED__ */


#ifndef __IDAEndStyle_INTERFACE_DEFINED__
#define __IDAEndStyle_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDAEndStyle
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][hidden][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDAEndStyle;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("C46C1BEB-3C52-11d0-9200-848C1D000000")
    IDAEndStyle : public IDABehavior
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IDAEndStyleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDAEndStyle * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDAEndStyle * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDAEndStyle * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDAEndStyle * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDAEndStyle * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDAEndStyle * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDAEndStyle * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassName )( 
            IDAEndStyle * This,
            /* [retval][out] */ BSTR *pClassName);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            IDAEndStyle * This,
            /* [in] */ IDABehavior *toBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Importance )( 
            IDAEndStyle * This,
            /* [in] */ double relativeImportance,
            /* [retval][out] */ IDABehavior **ppBvr);
        
        HRESULT ( STDMETHODCALLTYPE *RunOnce )( 
            IDAEndStyle * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SubstituteTime )( 
            IDAEndStyle * This,
            /* [in] */ IDANumber *xform,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchTo )( 
            IDAEndStyle * This,
            /* [in] */ IDABehavior *switchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToNumber )( 
            IDAEndStyle * This,
            /* [in] */ double numToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToString )( 
            IDAEndStyle * This,
            /* [in] */ BSTR strToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *Hook )( 
            IDAEndStyle * This,
            /* [in] */ IDABvrHook *notifier,
            /* [retval][out] */ IDABehavior **pBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Duration )( 
            IDAEndStyle * This,
            /* [in] */ double duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *DurationAnim )( 
            IDAEndStyle * This,
            /* [in] */ IDANumber *duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Repeat )( 
            IDAEndStyle * This,
            /* [in] */ LONG count,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *RepeatForever )( 
            IDAEndStyle * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *IsReady )( 
            IDAEndStyle * This,
            /* [in] */ VARIANT_BOOL bBlock,
            /* [retval][out] */ VARIANT_BOOL *b);
        
        END_INTERFACE
    } IDAEndStyleVtbl;

    interface IDAEndStyle
    {
        CONST_VTBL struct IDAEndStyleVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDAEndStyle_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDAEndStyle_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDAEndStyle_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDAEndStyle_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDAEndStyle_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDAEndStyle_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDAEndStyle_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDAEndStyle_GetClassName(This,pClassName)	\
    (This)->lpVtbl -> GetClassName(This,pClassName)

#define IDAEndStyle_Init(This,toBvr)	\
    (This)->lpVtbl -> Init(This,toBvr)

#define IDAEndStyle_Importance(This,relativeImportance,ppBvr)	\
    (This)->lpVtbl -> Importance(This,relativeImportance,ppBvr)

#define IDAEndStyle_RunOnce(This,bvr)	\
    (This)->lpVtbl -> RunOnce(This,bvr)

#define IDAEndStyle_SubstituteTime(This,xform,bvr)	\
    (This)->lpVtbl -> SubstituteTime(This,xform,bvr)

#define IDAEndStyle_SwitchTo(This,switchTo)	\
    (This)->lpVtbl -> SwitchTo(This,switchTo)

#define IDAEndStyle_SwitchToNumber(This,numToSwitchTo)	\
    (This)->lpVtbl -> SwitchToNumber(This,numToSwitchTo)

#define IDAEndStyle_SwitchToString(This,strToSwitchTo)	\
    (This)->lpVtbl -> SwitchToString(This,strToSwitchTo)

#define IDAEndStyle_Hook(This,notifier,pBvr)	\
    (This)->lpVtbl -> Hook(This,notifier,pBvr)

#define IDAEndStyle_Duration(This,duration,bvr)	\
    (This)->lpVtbl -> Duration(This,duration,bvr)

#define IDAEndStyle_DurationAnim(This,duration,bvr)	\
    (This)->lpVtbl -> DurationAnim(This,duration,bvr)

#define IDAEndStyle_Repeat(This,count,bvr)	\
    (This)->lpVtbl -> Repeat(This,count,bvr)

#define IDAEndStyle_RepeatForever(This,bvr)	\
    (This)->lpVtbl -> RepeatForever(This,bvr)

#define IDAEndStyle_IsReady(This,bBlock,b)	\
    (This)->lpVtbl -> IsReady(This,bBlock,b)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDAEndStyle_INTERFACE_DEFINED__ */


#ifndef __IDAJoinStyle_INTERFACE_DEFINED__
#define __IDAJoinStyle_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDAJoinStyle
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][hidden][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDAJoinStyle;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("C46C1BED-3C52-11d0-9200-848C1D000000")
    IDAJoinStyle : public IDABehavior
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IDAJoinStyleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDAJoinStyle * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDAJoinStyle * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDAJoinStyle * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDAJoinStyle * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDAJoinStyle * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDAJoinStyle * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDAJoinStyle * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassName )( 
            IDAJoinStyle * This,
            /* [retval][out] */ BSTR *pClassName);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            IDAJoinStyle * This,
            /* [in] */ IDABehavior *toBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Importance )( 
            IDAJoinStyle * This,
            /* [in] */ double relativeImportance,
            /* [retval][out] */ IDABehavior **ppBvr);
        
        HRESULT ( STDMETHODCALLTYPE *RunOnce )( 
            IDAJoinStyle * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SubstituteTime )( 
            IDAJoinStyle * This,
            /* [in] */ IDANumber *xform,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchTo )( 
            IDAJoinStyle * This,
            /* [in] */ IDABehavior *switchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToNumber )( 
            IDAJoinStyle * This,
            /* [in] */ double numToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToString )( 
            IDAJoinStyle * This,
            /* [in] */ BSTR strToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *Hook )( 
            IDAJoinStyle * This,
            /* [in] */ IDABvrHook *notifier,
            /* [retval][out] */ IDABehavior **pBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Duration )( 
            IDAJoinStyle * This,
            /* [in] */ double duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *DurationAnim )( 
            IDAJoinStyle * This,
            /* [in] */ IDANumber *duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Repeat )( 
            IDAJoinStyle * This,
            /* [in] */ LONG count,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *RepeatForever )( 
            IDAJoinStyle * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *IsReady )( 
            IDAJoinStyle * This,
            /* [in] */ VARIANT_BOOL bBlock,
            /* [retval][out] */ VARIANT_BOOL *b);
        
        END_INTERFACE
    } IDAJoinStyleVtbl;

    interface IDAJoinStyle
    {
        CONST_VTBL struct IDAJoinStyleVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDAJoinStyle_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDAJoinStyle_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDAJoinStyle_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDAJoinStyle_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDAJoinStyle_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDAJoinStyle_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDAJoinStyle_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDAJoinStyle_GetClassName(This,pClassName)	\
    (This)->lpVtbl -> GetClassName(This,pClassName)

#define IDAJoinStyle_Init(This,toBvr)	\
    (This)->lpVtbl -> Init(This,toBvr)

#define IDAJoinStyle_Importance(This,relativeImportance,ppBvr)	\
    (This)->lpVtbl -> Importance(This,relativeImportance,ppBvr)

#define IDAJoinStyle_RunOnce(This,bvr)	\
    (This)->lpVtbl -> RunOnce(This,bvr)

#define IDAJoinStyle_SubstituteTime(This,xform,bvr)	\
    (This)->lpVtbl -> SubstituteTime(This,xform,bvr)

#define IDAJoinStyle_SwitchTo(This,switchTo)	\
    (This)->lpVtbl -> SwitchTo(This,switchTo)

#define IDAJoinStyle_SwitchToNumber(This,numToSwitchTo)	\
    (This)->lpVtbl -> SwitchToNumber(This,numToSwitchTo)

#define IDAJoinStyle_SwitchToString(This,strToSwitchTo)	\
    (This)->lpVtbl -> SwitchToString(This,strToSwitchTo)

#define IDAJoinStyle_Hook(This,notifier,pBvr)	\
    (This)->lpVtbl -> Hook(This,notifier,pBvr)

#define IDAJoinStyle_Duration(This,duration,bvr)	\
    (This)->lpVtbl -> Duration(This,duration,bvr)

#define IDAJoinStyle_DurationAnim(This,duration,bvr)	\
    (This)->lpVtbl -> DurationAnim(This,duration,bvr)

#define IDAJoinStyle_Repeat(This,count,bvr)	\
    (This)->lpVtbl -> Repeat(This,count,bvr)

#define IDAJoinStyle_RepeatForever(This,bvr)	\
    (This)->lpVtbl -> RepeatForever(This,bvr)

#define IDAJoinStyle_IsReady(This,bBlock,b)	\
    (This)->lpVtbl -> IsReady(This,bBlock,b)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDAJoinStyle_INTERFACE_DEFINED__ */


#ifndef __IDADashStyle_INTERFACE_DEFINED__
#define __IDADashStyle_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDADashStyle
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][hidden][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDADashStyle;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("C46C1BEF-3C52-11d0-9200-848C1D000000")
    IDADashStyle : public IDABehavior
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IDADashStyleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDADashStyle * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDADashStyle * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDADashStyle * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDADashStyle * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDADashStyle * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDADashStyle * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDADashStyle * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassName )( 
            IDADashStyle * This,
            /* [retval][out] */ BSTR *pClassName);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            IDADashStyle * This,
            /* [in] */ IDABehavior *toBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Importance )( 
            IDADashStyle * This,
            /* [in] */ double relativeImportance,
            /* [retval][out] */ IDABehavior **ppBvr);
        
        HRESULT ( STDMETHODCALLTYPE *RunOnce )( 
            IDADashStyle * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SubstituteTime )( 
            IDADashStyle * This,
            /* [in] */ IDANumber *xform,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchTo )( 
            IDADashStyle * This,
            /* [in] */ IDABehavior *switchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToNumber )( 
            IDADashStyle * This,
            /* [in] */ double numToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToString )( 
            IDADashStyle * This,
            /* [in] */ BSTR strToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *Hook )( 
            IDADashStyle * This,
            /* [in] */ IDABvrHook *notifier,
            /* [retval][out] */ IDABehavior **pBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Duration )( 
            IDADashStyle * This,
            /* [in] */ double duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *DurationAnim )( 
            IDADashStyle * This,
            /* [in] */ IDANumber *duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Repeat )( 
            IDADashStyle * This,
            /* [in] */ LONG count,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *RepeatForever )( 
            IDADashStyle * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *IsReady )( 
            IDADashStyle * This,
            /* [in] */ VARIANT_BOOL bBlock,
            /* [retval][out] */ VARIANT_BOOL *b);
        
        END_INTERFACE
    } IDADashStyleVtbl;

    interface IDADashStyle
    {
        CONST_VTBL struct IDADashStyleVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDADashStyle_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDADashStyle_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDADashStyle_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDADashStyle_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDADashStyle_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDADashStyle_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDADashStyle_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDADashStyle_GetClassName(This,pClassName)	\
    (This)->lpVtbl -> GetClassName(This,pClassName)

#define IDADashStyle_Init(This,toBvr)	\
    (This)->lpVtbl -> Init(This,toBvr)

#define IDADashStyle_Importance(This,relativeImportance,ppBvr)	\
    (This)->lpVtbl -> Importance(This,relativeImportance,ppBvr)

#define IDADashStyle_RunOnce(This,bvr)	\
    (This)->lpVtbl -> RunOnce(This,bvr)

#define IDADashStyle_SubstituteTime(This,xform,bvr)	\
    (This)->lpVtbl -> SubstituteTime(This,xform,bvr)

#define IDADashStyle_SwitchTo(This,switchTo)	\
    (This)->lpVtbl -> SwitchTo(This,switchTo)

#define IDADashStyle_SwitchToNumber(This,numToSwitchTo)	\
    (This)->lpVtbl -> SwitchToNumber(This,numToSwitchTo)

#define IDADashStyle_SwitchToString(This,strToSwitchTo)	\
    (This)->lpVtbl -> SwitchToString(This,strToSwitchTo)

#define IDADashStyle_Hook(This,notifier,pBvr)	\
    (This)->lpVtbl -> Hook(This,notifier,pBvr)

#define IDADashStyle_Duration(This,duration,bvr)	\
    (This)->lpVtbl -> Duration(This,duration,bvr)

#define IDADashStyle_DurationAnim(This,duration,bvr)	\
    (This)->lpVtbl -> DurationAnim(This,duration,bvr)

#define IDADashStyle_Repeat(This,count,bvr)	\
    (This)->lpVtbl -> Repeat(This,count,bvr)

#define IDADashStyle_RepeatForever(This,bvr)	\
    (This)->lpVtbl -> RepeatForever(This,bvr)

#define IDADashStyle_IsReady(This,bBlock,b)	\
    (This)->lpVtbl -> IsReady(This,bBlock,b)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDADashStyle_INTERFACE_DEFINED__ */


#ifndef __IDABbox2_INTERFACE_DEFINED__
#define __IDABbox2_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDABbox2
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][hidden][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDABbox2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("C46C1BCD-3C52-11d0-9200-848C1D000000")
    IDABbox2 : public IDABehavior
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Min( 
            /* [retval][out] */ IDAPoint2 **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Max( 
            /* [retval][out] */ IDAPoint2 **ret_0) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDABbox2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDABbox2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDABbox2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDABbox2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDABbox2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDABbox2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDABbox2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDABbox2 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassName )( 
            IDABbox2 * This,
            /* [retval][out] */ BSTR *pClassName);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            IDABbox2 * This,
            /* [in] */ IDABehavior *toBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Importance )( 
            IDABbox2 * This,
            /* [in] */ double relativeImportance,
            /* [retval][out] */ IDABehavior **ppBvr);
        
        HRESULT ( STDMETHODCALLTYPE *RunOnce )( 
            IDABbox2 * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SubstituteTime )( 
            IDABbox2 * This,
            /* [in] */ IDANumber *xform,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchTo )( 
            IDABbox2 * This,
            /* [in] */ IDABehavior *switchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToNumber )( 
            IDABbox2 * This,
            /* [in] */ double numToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToString )( 
            IDABbox2 * This,
            /* [in] */ BSTR strToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *Hook )( 
            IDABbox2 * This,
            /* [in] */ IDABvrHook *notifier,
            /* [retval][out] */ IDABehavior **pBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Duration )( 
            IDABbox2 * This,
            /* [in] */ double duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *DurationAnim )( 
            IDABbox2 * This,
            /* [in] */ IDANumber *duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Repeat )( 
            IDABbox2 * This,
            /* [in] */ LONG count,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *RepeatForever )( 
            IDABbox2 * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *IsReady )( 
            IDABbox2 * This,
            /* [in] */ VARIANT_BOOL bBlock,
            /* [retval][out] */ VARIANT_BOOL *b);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Min )( 
            IDABbox2 * This,
            /* [retval][out] */ IDAPoint2 **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Max )( 
            IDABbox2 * This,
            /* [retval][out] */ IDAPoint2 **ret_0);
        
        END_INTERFACE
    } IDABbox2Vtbl;

    interface IDABbox2
    {
        CONST_VTBL struct IDABbox2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDABbox2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDABbox2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDABbox2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDABbox2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDABbox2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDABbox2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDABbox2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDABbox2_GetClassName(This,pClassName)	\
    (This)->lpVtbl -> GetClassName(This,pClassName)

#define IDABbox2_Init(This,toBvr)	\
    (This)->lpVtbl -> Init(This,toBvr)

#define IDABbox2_Importance(This,relativeImportance,ppBvr)	\
    (This)->lpVtbl -> Importance(This,relativeImportance,ppBvr)

#define IDABbox2_RunOnce(This,bvr)	\
    (This)->lpVtbl -> RunOnce(This,bvr)

#define IDABbox2_SubstituteTime(This,xform,bvr)	\
    (This)->lpVtbl -> SubstituteTime(This,xform,bvr)

#define IDABbox2_SwitchTo(This,switchTo)	\
    (This)->lpVtbl -> SwitchTo(This,switchTo)

#define IDABbox2_SwitchToNumber(This,numToSwitchTo)	\
    (This)->lpVtbl -> SwitchToNumber(This,numToSwitchTo)

#define IDABbox2_SwitchToString(This,strToSwitchTo)	\
    (This)->lpVtbl -> SwitchToString(This,strToSwitchTo)

#define IDABbox2_Hook(This,notifier,pBvr)	\
    (This)->lpVtbl -> Hook(This,notifier,pBvr)

#define IDABbox2_Duration(This,duration,bvr)	\
    (This)->lpVtbl -> Duration(This,duration,bvr)

#define IDABbox2_DurationAnim(This,duration,bvr)	\
    (This)->lpVtbl -> DurationAnim(This,duration,bvr)

#define IDABbox2_Repeat(This,count,bvr)	\
    (This)->lpVtbl -> Repeat(This,count,bvr)

#define IDABbox2_RepeatForever(This,bvr)	\
    (This)->lpVtbl -> RepeatForever(This,bvr)

#define IDABbox2_IsReady(This,bBlock,b)	\
    (This)->lpVtbl -> IsReady(This,bBlock,b)


#define IDABbox2_get_Min(This,ret_0)	\
    (This)->lpVtbl -> get_Min(This,ret_0)

#define IDABbox2_get_Max(This,ret_0)	\
    (This)->lpVtbl -> get_Max(This,ret_0)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IDABbox2_get_Min_Proxy( 
    IDABbox2 * This,
    /* [retval][out] */ IDAPoint2 **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDABbox2_get_Max_Proxy( 
    IDABbox2 * This,
    /* [retval][out] */ IDAPoint2 **ret_0);




#endif 	/* __IDABbox2_INTERFACE_DEFINED__ */


#ifndef __IDABbox3_INTERFACE_DEFINED__
#define __IDABbox3_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDABbox3
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][hidden][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDABbox3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("C46C1BDD-3C52-11d0-9200-848C1D000000")
    IDABbox3 : public IDABehavior
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Min( 
            /* [retval][out] */ IDAPoint3 **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Max( 
            /* [retval][out] */ IDAPoint3 **ret_0) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDABbox3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDABbox3 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDABbox3 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDABbox3 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDABbox3 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDABbox3 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDABbox3 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDABbox3 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassName )( 
            IDABbox3 * This,
            /* [retval][out] */ BSTR *pClassName);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            IDABbox3 * This,
            /* [in] */ IDABehavior *toBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Importance )( 
            IDABbox3 * This,
            /* [in] */ double relativeImportance,
            /* [retval][out] */ IDABehavior **ppBvr);
        
        HRESULT ( STDMETHODCALLTYPE *RunOnce )( 
            IDABbox3 * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SubstituteTime )( 
            IDABbox3 * This,
            /* [in] */ IDANumber *xform,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchTo )( 
            IDABbox3 * This,
            /* [in] */ IDABehavior *switchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToNumber )( 
            IDABbox3 * This,
            /* [in] */ double numToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToString )( 
            IDABbox3 * This,
            /* [in] */ BSTR strToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *Hook )( 
            IDABbox3 * This,
            /* [in] */ IDABvrHook *notifier,
            /* [retval][out] */ IDABehavior **pBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Duration )( 
            IDABbox3 * This,
            /* [in] */ double duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *DurationAnim )( 
            IDABbox3 * This,
            /* [in] */ IDANumber *duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Repeat )( 
            IDABbox3 * This,
            /* [in] */ LONG count,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *RepeatForever )( 
            IDABbox3 * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *IsReady )( 
            IDABbox3 * This,
            /* [in] */ VARIANT_BOOL bBlock,
            /* [retval][out] */ VARIANT_BOOL *b);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Min )( 
            IDABbox3 * This,
            /* [retval][out] */ IDAPoint3 **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Max )( 
            IDABbox3 * This,
            /* [retval][out] */ IDAPoint3 **ret_0);
        
        END_INTERFACE
    } IDABbox3Vtbl;

    interface IDABbox3
    {
        CONST_VTBL struct IDABbox3Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDABbox3_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDABbox3_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDABbox3_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDABbox3_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDABbox3_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDABbox3_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDABbox3_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDABbox3_GetClassName(This,pClassName)	\
    (This)->lpVtbl -> GetClassName(This,pClassName)

#define IDABbox3_Init(This,toBvr)	\
    (This)->lpVtbl -> Init(This,toBvr)

#define IDABbox3_Importance(This,relativeImportance,ppBvr)	\
    (This)->lpVtbl -> Importance(This,relativeImportance,ppBvr)

#define IDABbox3_RunOnce(This,bvr)	\
    (This)->lpVtbl -> RunOnce(This,bvr)

#define IDABbox3_SubstituteTime(This,xform,bvr)	\
    (This)->lpVtbl -> SubstituteTime(This,xform,bvr)

#define IDABbox3_SwitchTo(This,switchTo)	\
    (This)->lpVtbl -> SwitchTo(This,switchTo)

#define IDABbox3_SwitchToNumber(This,numToSwitchTo)	\
    (This)->lpVtbl -> SwitchToNumber(This,numToSwitchTo)

#define IDABbox3_SwitchToString(This,strToSwitchTo)	\
    (This)->lpVtbl -> SwitchToString(This,strToSwitchTo)

#define IDABbox3_Hook(This,notifier,pBvr)	\
    (This)->lpVtbl -> Hook(This,notifier,pBvr)

#define IDABbox3_Duration(This,duration,bvr)	\
    (This)->lpVtbl -> Duration(This,duration,bvr)

#define IDABbox3_DurationAnim(This,duration,bvr)	\
    (This)->lpVtbl -> DurationAnim(This,duration,bvr)

#define IDABbox3_Repeat(This,count,bvr)	\
    (This)->lpVtbl -> Repeat(This,count,bvr)

#define IDABbox3_RepeatForever(This,bvr)	\
    (This)->lpVtbl -> RepeatForever(This,bvr)

#define IDABbox3_IsReady(This,bBlock,b)	\
    (This)->lpVtbl -> IsReady(This,bBlock,b)


#define IDABbox3_get_Min(This,ret_0)	\
    (This)->lpVtbl -> get_Min(This,ret_0)

#define IDABbox3_get_Max(This,ret_0)	\
    (This)->lpVtbl -> get_Max(This,ret_0)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IDABbox3_get_Min_Proxy( 
    IDABbox3 * This,
    /* [retval][out] */ IDAPoint3 **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDABbox3_get_Max_Proxy( 
    IDABbox3 * This,
    /* [retval][out] */ IDAPoint3 **ret_0);




#endif 	/* __IDABbox3_INTERFACE_DEFINED__ */


#ifndef __IDAPair_INTERFACE_DEFINED__
#define __IDAPair_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDAPair
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][hidden][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDAPair;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("C46C1BF3-3C52-11d0-9200-848C1D000000")
    IDAPair : public IDABehavior
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_First( 
            /* [retval][out] */ IDABehavior **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Second( 
            /* [retval][out] */ IDABehavior **ret_0) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDAPairVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDAPair * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDAPair * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDAPair * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDAPair * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDAPair * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDAPair * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDAPair * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassName )( 
            IDAPair * This,
            /* [retval][out] */ BSTR *pClassName);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            IDAPair * This,
            /* [in] */ IDABehavior *toBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Importance )( 
            IDAPair * This,
            /* [in] */ double relativeImportance,
            /* [retval][out] */ IDABehavior **ppBvr);
        
        HRESULT ( STDMETHODCALLTYPE *RunOnce )( 
            IDAPair * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SubstituteTime )( 
            IDAPair * This,
            /* [in] */ IDANumber *xform,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchTo )( 
            IDAPair * This,
            /* [in] */ IDABehavior *switchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToNumber )( 
            IDAPair * This,
            /* [in] */ double numToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToString )( 
            IDAPair * This,
            /* [in] */ BSTR strToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *Hook )( 
            IDAPair * This,
            /* [in] */ IDABvrHook *notifier,
            /* [retval][out] */ IDABehavior **pBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Duration )( 
            IDAPair * This,
            /* [in] */ double duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *DurationAnim )( 
            IDAPair * This,
            /* [in] */ IDANumber *duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Repeat )( 
            IDAPair * This,
            /* [in] */ LONG count,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *RepeatForever )( 
            IDAPair * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *IsReady )( 
            IDAPair * This,
            /* [in] */ VARIANT_BOOL bBlock,
            /* [retval][out] */ VARIANT_BOOL *b);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_First )( 
            IDAPair * This,
            /* [retval][out] */ IDABehavior **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Second )( 
            IDAPair * This,
            /* [retval][out] */ IDABehavior **ret_0);
        
        END_INTERFACE
    } IDAPairVtbl;

    interface IDAPair
    {
        CONST_VTBL struct IDAPairVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDAPair_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDAPair_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDAPair_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDAPair_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDAPair_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDAPair_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDAPair_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDAPair_GetClassName(This,pClassName)	\
    (This)->lpVtbl -> GetClassName(This,pClassName)

#define IDAPair_Init(This,toBvr)	\
    (This)->lpVtbl -> Init(This,toBvr)

#define IDAPair_Importance(This,relativeImportance,ppBvr)	\
    (This)->lpVtbl -> Importance(This,relativeImportance,ppBvr)

#define IDAPair_RunOnce(This,bvr)	\
    (This)->lpVtbl -> RunOnce(This,bvr)

#define IDAPair_SubstituteTime(This,xform,bvr)	\
    (This)->lpVtbl -> SubstituteTime(This,xform,bvr)

#define IDAPair_SwitchTo(This,switchTo)	\
    (This)->lpVtbl -> SwitchTo(This,switchTo)

#define IDAPair_SwitchToNumber(This,numToSwitchTo)	\
    (This)->lpVtbl -> SwitchToNumber(This,numToSwitchTo)

#define IDAPair_SwitchToString(This,strToSwitchTo)	\
    (This)->lpVtbl -> SwitchToString(This,strToSwitchTo)

#define IDAPair_Hook(This,notifier,pBvr)	\
    (This)->lpVtbl -> Hook(This,notifier,pBvr)

#define IDAPair_Duration(This,duration,bvr)	\
    (This)->lpVtbl -> Duration(This,duration,bvr)

#define IDAPair_DurationAnim(This,duration,bvr)	\
    (This)->lpVtbl -> DurationAnim(This,duration,bvr)

#define IDAPair_Repeat(This,count,bvr)	\
    (This)->lpVtbl -> Repeat(This,count,bvr)

#define IDAPair_RepeatForever(This,bvr)	\
    (This)->lpVtbl -> RepeatForever(This,bvr)

#define IDAPair_IsReady(This,bBlock,b)	\
    (This)->lpVtbl -> IsReady(This,bBlock,b)


#define IDAPair_get_First(This,ret_0)	\
    (This)->lpVtbl -> get_First(This,ret_0)

#define IDAPair_get_Second(This,ret_0)	\
    (This)->lpVtbl -> get_Second(This,ret_0)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAPair_get_First_Proxy( 
    IDAPair * This,
    /* [retval][out] */ IDABehavior **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAPair_get_Second_Proxy( 
    IDAPair * This,
    /* [retval][out] */ IDABehavior **ret_0);




#endif 	/* __IDAPair_INTERFACE_DEFINED__ */


#ifndef __IDAEvent_INTERFACE_DEFINED__
#define __IDAEvent_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDAEvent
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][hidden][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDAEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("50B4791E-4731-11d0-8912-00C04FC2A0CA")
    IDAEvent : public IDABehavior
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Notify( 
            /* [in] */ IDAUntilNotifier *notifier_0,
            /* [retval][out] */ IDAEvent **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Snapshot( 
            /* [in] */ IDABehavior *b_0,
            /* [retval][out] */ IDAEvent **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AttachData( 
            /* [in] */ IDABehavior *data_0,
            /* [retval][out] */ IDAEvent **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ScriptCallback( 
            /* [in] */ BSTR scriptlet_0,
            /* [in] */ BSTR language_1,
            /* [retval][out] */ IDAEvent **ret_2) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDAEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDAEvent * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDAEvent * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDAEvent * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDAEvent * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDAEvent * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDAEvent * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDAEvent * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassName )( 
            IDAEvent * This,
            /* [retval][out] */ BSTR *pClassName);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            IDAEvent * This,
            /* [in] */ IDABehavior *toBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Importance )( 
            IDAEvent * This,
            /* [in] */ double relativeImportance,
            /* [retval][out] */ IDABehavior **ppBvr);
        
        HRESULT ( STDMETHODCALLTYPE *RunOnce )( 
            IDAEvent * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SubstituteTime )( 
            IDAEvent * This,
            /* [in] */ IDANumber *xform,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchTo )( 
            IDAEvent * This,
            /* [in] */ IDABehavior *switchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToNumber )( 
            IDAEvent * This,
            /* [in] */ double numToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToString )( 
            IDAEvent * This,
            /* [in] */ BSTR strToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *Hook )( 
            IDAEvent * This,
            /* [in] */ IDABvrHook *notifier,
            /* [retval][out] */ IDABehavior **pBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Duration )( 
            IDAEvent * This,
            /* [in] */ double duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *DurationAnim )( 
            IDAEvent * This,
            /* [in] */ IDANumber *duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Repeat )( 
            IDAEvent * This,
            /* [in] */ LONG count,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *RepeatForever )( 
            IDAEvent * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *IsReady )( 
            IDAEvent * This,
            /* [in] */ VARIANT_BOOL bBlock,
            /* [retval][out] */ VARIANT_BOOL *b);
        
        HRESULT ( STDMETHODCALLTYPE *Notify )( 
            IDAEvent * This,
            /* [in] */ IDAUntilNotifier *notifier_0,
            /* [retval][out] */ IDAEvent **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Snapshot )( 
            IDAEvent * This,
            /* [in] */ IDABehavior *b_0,
            /* [retval][out] */ IDAEvent **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *AttachData )( 
            IDAEvent * This,
            /* [in] */ IDABehavior *data_0,
            /* [retval][out] */ IDAEvent **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *ScriptCallback )( 
            IDAEvent * This,
            /* [in] */ BSTR scriptlet_0,
            /* [in] */ BSTR language_1,
            /* [retval][out] */ IDAEvent **ret_2);
        
        END_INTERFACE
    } IDAEventVtbl;

    interface IDAEvent
    {
        CONST_VTBL struct IDAEventVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDAEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDAEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDAEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDAEvent_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDAEvent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDAEvent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDAEvent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDAEvent_GetClassName(This,pClassName)	\
    (This)->lpVtbl -> GetClassName(This,pClassName)

#define IDAEvent_Init(This,toBvr)	\
    (This)->lpVtbl -> Init(This,toBvr)

#define IDAEvent_Importance(This,relativeImportance,ppBvr)	\
    (This)->lpVtbl -> Importance(This,relativeImportance,ppBvr)

#define IDAEvent_RunOnce(This,bvr)	\
    (This)->lpVtbl -> RunOnce(This,bvr)

#define IDAEvent_SubstituteTime(This,xform,bvr)	\
    (This)->lpVtbl -> SubstituteTime(This,xform,bvr)

#define IDAEvent_SwitchTo(This,switchTo)	\
    (This)->lpVtbl -> SwitchTo(This,switchTo)

#define IDAEvent_SwitchToNumber(This,numToSwitchTo)	\
    (This)->lpVtbl -> SwitchToNumber(This,numToSwitchTo)

#define IDAEvent_SwitchToString(This,strToSwitchTo)	\
    (This)->lpVtbl -> SwitchToString(This,strToSwitchTo)

#define IDAEvent_Hook(This,notifier,pBvr)	\
    (This)->lpVtbl -> Hook(This,notifier,pBvr)

#define IDAEvent_Duration(This,duration,bvr)	\
    (This)->lpVtbl -> Duration(This,duration,bvr)

#define IDAEvent_DurationAnim(This,duration,bvr)	\
    (This)->lpVtbl -> DurationAnim(This,duration,bvr)

#define IDAEvent_Repeat(This,count,bvr)	\
    (This)->lpVtbl -> Repeat(This,count,bvr)

#define IDAEvent_RepeatForever(This,bvr)	\
    (This)->lpVtbl -> RepeatForever(This,bvr)

#define IDAEvent_IsReady(This,bBlock,b)	\
    (This)->lpVtbl -> IsReady(This,bBlock,b)


#define IDAEvent_Notify(This,notifier_0,ret_1)	\
    (This)->lpVtbl -> Notify(This,notifier_0,ret_1)

#define IDAEvent_Snapshot(This,b_0,ret_1)	\
    (This)->lpVtbl -> Snapshot(This,b_0,ret_1)

#define IDAEvent_AttachData(This,data_0,ret_1)	\
    (This)->lpVtbl -> AttachData(This,data_0,ret_1)

#define IDAEvent_ScriptCallback(This,scriptlet_0,language_1,ret_2)	\
    (This)->lpVtbl -> ScriptCallback(This,scriptlet_0,language_1,ret_2)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDAEvent_Notify_Proxy( 
    IDAEvent * This,
    /* [in] */ IDAUntilNotifier *notifier_0,
    /* [retval][out] */ IDAEvent **ret_1);



HRESULT STDMETHODCALLTYPE IDAEvent_Snapshot_Proxy( 
    IDAEvent * This,
    /* [in] */ IDABehavior *b_0,
    /* [retval][out] */ IDAEvent **ret_1);



HRESULT STDMETHODCALLTYPE IDAEvent_AttachData_Proxy( 
    IDAEvent * This,
    /* [in] */ IDABehavior *data_0,
    /* [retval][out] */ IDAEvent **ret_1);



HRESULT STDMETHODCALLTYPE IDAEvent_ScriptCallback_Proxy( 
    IDAEvent * This,
    /* [in] */ BSTR scriptlet_0,
    /* [in] */ BSTR language_1,
    /* [retval][out] */ IDAEvent **ret_2);




#endif 	/* __IDAEvent_INTERFACE_DEFINED__ */


#ifndef __IDAArray_INTERFACE_DEFINED__
#define __IDAArray_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDAArray
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][hidden][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDAArray;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("D17506C2-6B26-11d0-8914-00C04FC2A0CA")
    IDAArray : public IDABehavior
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE NthAnim( 
            /* [in] */ IDANumber *index_0,
            /* [retval][out] */ IDABehavior **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Length( 
            /* [retval][out] */ IDANumber **ret_0) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDAArrayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDAArray * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDAArray * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDAArray * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDAArray * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDAArray * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDAArray * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDAArray * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassName )( 
            IDAArray * This,
            /* [retval][out] */ BSTR *pClassName);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            IDAArray * This,
            /* [in] */ IDABehavior *toBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Importance )( 
            IDAArray * This,
            /* [in] */ double relativeImportance,
            /* [retval][out] */ IDABehavior **ppBvr);
        
        HRESULT ( STDMETHODCALLTYPE *RunOnce )( 
            IDAArray * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SubstituteTime )( 
            IDAArray * This,
            /* [in] */ IDANumber *xform,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchTo )( 
            IDAArray * This,
            /* [in] */ IDABehavior *switchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToNumber )( 
            IDAArray * This,
            /* [in] */ double numToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToString )( 
            IDAArray * This,
            /* [in] */ BSTR strToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *Hook )( 
            IDAArray * This,
            /* [in] */ IDABvrHook *notifier,
            /* [retval][out] */ IDABehavior **pBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Duration )( 
            IDAArray * This,
            /* [in] */ double duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *DurationAnim )( 
            IDAArray * This,
            /* [in] */ IDANumber *duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Repeat )( 
            IDAArray * This,
            /* [in] */ LONG count,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *RepeatForever )( 
            IDAArray * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *IsReady )( 
            IDAArray * This,
            /* [in] */ VARIANT_BOOL bBlock,
            /* [retval][out] */ VARIANT_BOOL *b);
        
        HRESULT ( STDMETHODCALLTYPE *NthAnim )( 
            IDAArray * This,
            /* [in] */ IDANumber *index_0,
            /* [retval][out] */ IDABehavior **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Length )( 
            IDAArray * This,
            /* [retval][out] */ IDANumber **ret_0);
        
        END_INTERFACE
    } IDAArrayVtbl;

    interface IDAArray
    {
        CONST_VTBL struct IDAArrayVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDAArray_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDAArray_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDAArray_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDAArray_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDAArray_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDAArray_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDAArray_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDAArray_GetClassName(This,pClassName)	\
    (This)->lpVtbl -> GetClassName(This,pClassName)

#define IDAArray_Init(This,toBvr)	\
    (This)->lpVtbl -> Init(This,toBvr)

#define IDAArray_Importance(This,relativeImportance,ppBvr)	\
    (This)->lpVtbl -> Importance(This,relativeImportance,ppBvr)

#define IDAArray_RunOnce(This,bvr)	\
    (This)->lpVtbl -> RunOnce(This,bvr)

#define IDAArray_SubstituteTime(This,xform,bvr)	\
    (This)->lpVtbl -> SubstituteTime(This,xform,bvr)

#define IDAArray_SwitchTo(This,switchTo)	\
    (This)->lpVtbl -> SwitchTo(This,switchTo)

#define IDAArray_SwitchToNumber(This,numToSwitchTo)	\
    (This)->lpVtbl -> SwitchToNumber(This,numToSwitchTo)

#define IDAArray_SwitchToString(This,strToSwitchTo)	\
    (This)->lpVtbl -> SwitchToString(This,strToSwitchTo)

#define IDAArray_Hook(This,notifier,pBvr)	\
    (This)->lpVtbl -> Hook(This,notifier,pBvr)

#define IDAArray_Duration(This,duration,bvr)	\
    (This)->lpVtbl -> Duration(This,duration,bvr)

#define IDAArray_DurationAnim(This,duration,bvr)	\
    (This)->lpVtbl -> DurationAnim(This,duration,bvr)

#define IDAArray_Repeat(This,count,bvr)	\
    (This)->lpVtbl -> Repeat(This,count,bvr)

#define IDAArray_RepeatForever(This,bvr)	\
    (This)->lpVtbl -> RepeatForever(This,bvr)

#define IDAArray_IsReady(This,bBlock,b)	\
    (This)->lpVtbl -> IsReady(This,bBlock,b)


#define IDAArray_NthAnim(This,index_0,ret_1)	\
    (This)->lpVtbl -> NthAnim(This,index_0,ret_1)

#define IDAArray_Length(This,ret_0)	\
    (This)->lpVtbl -> Length(This,ret_0)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDAArray_NthAnim_Proxy( 
    IDAArray * This,
    /* [in] */ IDANumber *index_0,
    /* [retval][out] */ IDABehavior **ret_1);



HRESULT STDMETHODCALLTYPE IDAArray_Length_Proxy( 
    IDAArray * This,
    /* [retval][out] */ IDANumber **ret_0);




#endif 	/* __IDAArray_INTERFACE_DEFINED__ */


#ifndef __IDATuple_INTERFACE_DEFINED__
#define __IDATuple_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDATuple
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][hidden][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDATuple;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("5DFB2650-9668-11d0-B17B-00C04FC2A0CA")
    IDATuple : public IDABehavior
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Nth( 
            /* [in] */ long index_0,
            /* [retval][out] */ IDABehavior **ret_1) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ long *ret_0) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDATupleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDATuple * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDATuple * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDATuple * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDATuple * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDATuple * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDATuple * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDATuple * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassName )( 
            IDATuple * This,
            /* [retval][out] */ BSTR *pClassName);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            IDATuple * This,
            /* [in] */ IDABehavior *toBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Importance )( 
            IDATuple * This,
            /* [in] */ double relativeImportance,
            /* [retval][out] */ IDABehavior **ppBvr);
        
        HRESULT ( STDMETHODCALLTYPE *RunOnce )( 
            IDATuple * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SubstituteTime )( 
            IDATuple * This,
            /* [in] */ IDANumber *xform,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchTo )( 
            IDATuple * This,
            /* [in] */ IDABehavior *switchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToNumber )( 
            IDATuple * This,
            /* [in] */ double numToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToString )( 
            IDATuple * This,
            /* [in] */ BSTR strToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *Hook )( 
            IDATuple * This,
            /* [in] */ IDABvrHook *notifier,
            /* [retval][out] */ IDABehavior **pBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Duration )( 
            IDATuple * This,
            /* [in] */ double duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *DurationAnim )( 
            IDATuple * This,
            /* [in] */ IDANumber *duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Repeat )( 
            IDATuple * This,
            /* [in] */ LONG count,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *RepeatForever )( 
            IDATuple * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *IsReady )( 
            IDATuple * This,
            /* [in] */ VARIANT_BOOL bBlock,
            /* [retval][out] */ VARIANT_BOOL *b);
        
        HRESULT ( STDMETHODCALLTYPE *Nth )( 
            IDATuple * This,
            /* [in] */ long index_0,
            /* [retval][out] */ IDABehavior **ret_1);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IDATuple * This,
            /* [retval][out] */ long *ret_0);
        
        END_INTERFACE
    } IDATupleVtbl;

    interface IDATuple
    {
        CONST_VTBL struct IDATupleVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDATuple_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDATuple_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDATuple_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDATuple_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDATuple_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDATuple_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDATuple_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDATuple_GetClassName(This,pClassName)	\
    (This)->lpVtbl -> GetClassName(This,pClassName)

#define IDATuple_Init(This,toBvr)	\
    (This)->lpVtbl -> Init(This,toBvr)

#define IDATuple_Importance(This,relativeImportance,ppBvr)	\
    (This)->lpVtbl -> Importance(This,relativeImportance,ppBvr)

#define IDATuple_RunOnce(This,bvr)	\
    (This)->lpVtbl -> RunOnce(This,bvr)

#define IDATuple_SubstituteTime(This,xform,bvr)	\
    (This)->lpVtbl -> SubstituteTime(This,xform,bvr)

#define IDATuple_SwitchTo(This,switchTo)	\
    (This)->lpVtbl -> SwitchTo(This,switchTo)

#define IDATuple_SwitchToNumber(This,numToSwitchTo)	\
    (This)->lpVtbl -> SwitchToNumber(This,numToSwitchTo)

#define IDATuple_SwitchToString(This,strToSwitchTo)	\
    (This)->lpVtbl -> SwitchToString(This,strToSwitchTo)

#define IDATuple_Hook(This,notifier,pBvr)	\
    (This)->lpVtbl -> Hook(This,notifier,pBvr)

#define IDATuple_Duration(This,duration,bvr)	\
    (This)->lpVtbl -> Duration(This,duration,bvr)

#define IDATuple_DurationAnim(This,duration,bvr)	\
    (This)->lpVtbl -> DurationAnim(This,duration,bvr)

#define IDATuple_Repeat(This,count,bvr)	\
    (This)->lpVtbl -> Repeat(This,count,bvr)

#define IDATuple_RepeatForever(This,bvr)	\
    (This)->lpVtbl -> RepeatForever(This,bvr)

#define IDATuple_IsReady(This,bBlock,b)	\
    (This)->lpVtbl -> IsReady(This,bBlock,b)


#define IDATuple_Nth(This,index_0,ret_1)	\
    (This)->lpVtbl -> Nth(This,index_0,ret_1)

#define IDATuple_get_Length(This,ret_0)	\
    (This)->lpVtbl -> get_Length(This,ret_0)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDATuple_Nth_Proxy( 
    IDATuple * This,
    /* [in] */ long index_0,
    /* [retval][out] */ IDABehavior **ret_1);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDATuple_get_Length_Proxy( 
    IDATuple * This,
    /* [retval][out] */ long *ret_0);




#endif 	/* __IDATuple_INTERFACE_DEFINED__ */


#ifndef __IDAUserData_INTERFACE_DEFINED__
#define __IDAUserData_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDAUserData
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][hidden][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDAUserData;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("AF868305-AB0B-11d0-876A-00C04FC29D46")
    IDAUserData : public IDABehavior
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Data( 
            /* [retval][out] */ IUnknown **ret_0) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDAUserDataVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDAUserData * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDAUserData * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDAUserData * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDAUserData * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDAUserData * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDAUserData * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDAUserData * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassName )( 
            IDAUserData * This,
            /* [retval][out] */ BSTR *pClassName);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            IDAUserData * This,
            /* [in] */ IDABehavior *toBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Importance )( 
            IDAUserData * This,
            /* [in] */ double relativeImportance,
            /* [retval][out] */ IDABehavior **ppBvr);
        
        HRESULT ( STDMETHODCALLTYPE *RunOnce )( 
            IDAUserData * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SubstituteTime )( 
            IDAUserData * This,
            /* [in] */ IDANumber *xform,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchTo )( 
            IDAUserData * This,
            /* [in] */ IDABehavior *switchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToNumber )( 
            IDAUserData * This,
            /* [in] */ double numToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *SwitchToString )( 
            IDAUserData * This,
            /* [in] */ BSTR strToSwitchTo);
        
        HRESULT ( STDMETHODCALLTYPE *Hook )( 
            IDAUserData * This,
            /* [in] */ IDABvrHook *notifier,
            /* [retval][out] */ IDABehavior **pBvr);
        
        HRESULT ( STDMETHODCALLTYPE *Duration )( 
            IDAUserData * This,
            /* [in] */ double duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *DurationAnim )( 
            IDAUserData * This,
            /* [in] */ IDANumber *duration,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Repeat )( 
            IDAUserData * This,
            /* [in] */ LONG count,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *RepeatForever )( 
            IDAUserData * This,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *IsReady )( 
            IDAUserData * This,
            /* [in] */ VARIANT_BOOL bBlock,
            /* [retval][out] */ VARIANT_BOOL *b);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Data )( 
            IDAUserData * This,
            /* [retval][out] */ IUnknown **ret_0);
        
        END_INTERFACE
    } IDAUserDataVtbl;

    interface IDAUserData
    {
        CONST_VTBL struct IDAUserDataVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDAUserData_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDAUserData_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDAUserData_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDAUserData_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDAUserData_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDAUserData_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDAUserData_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDAUserData_GetClassName(This,pClassName)	\
    (This)->lpVtbl -> GetClassName(This,pClassName)

#define IDAUserData_Init(This,toBvr)	\
    (This)->lpVtbl -> Init(This,toBvr)

#define IDAUserData_Importance(This,relativeImportance,ppBvr)	\
    (This)->lpVtbl -> Importance(This,relativeImportance,ppBvr)

#define IDAUserData_RunOnce(This,bvr)	\
    (This)->lpVtbl -> RunOnce(This,bvr)

#define IDAUserData_SubstituteTime(This,xform,bvr)	\
    (This)->lpVtbl -> SubstituteTime(This,xform,bvr)

#define IDAUserData_SwitchTo(This,switchTo)	\
    (This)->lpVtbl -> SwitchTo(This,switchTo)

#define IDAUserData_SwitchToNumber(This,numToSwitchTo)	\
    (This)->lpVtbl -> SwitchToNumber(This,numToSwitchTo)

#define IDAUserData_SwitchToString(This,strToSwitchTo)	\
    (This)->lpVtbl -> SwitchToString(This,strToSwitchTo)

#define IDAUserData_Hook(This,notifier,pBvr)	\
    (This)->lpVtbl -> Hook(This,notifier,pBvr)

#define IDAUserData_Duration(This,duration,bvr)	\
    (This)->lpVtbl -> Duration(This,duration,bvr)

#define IDAUserData_DurationAnim(This,duration,bvr)	\
    (This)->lpVtbl -> DurationAnim(This,duration,bvr)

#define IDAUserData_Repeat(This,count,bvr)	\
    (This)->lpVtbl -> Repeat(This,count,bvr)

#define IDAUserData_RepeatForever(This,bvr)	\
    (This)->lpVtbl -> RepeatForever(This,bvr)

#define IDAUserData_IsReady(This,bBlock,b)	\
    (This)->lpVtbl -> IsReady(This,bBlock,b)


#define IDAUserData_get_Data(This,ret_0)	\
    (This)->lpVtbl -> get_Data(This,ret_0)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAUserData_get_Data_Proxy( 
    IDAUserData * This,
    /* [retval][out] */ IUnknown **ret_0);




#endif 	/* __IDAUserData_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_DABoolean;

#ifdef __cplusplus

class DECLSPEC_UUID("C46C1BC1-3C52-11d0-9200-848C1D000000")
DABoolean;
#endif

EXTERN_C const CLSID CLSID_DACamera;

#ifdef __cplusplus

class DECLSPEC_UUID("C46C1BE2-3C52-11d0-9200-848C1D000000")
DACamera;
#endif

EXTERN_C const CLSID CLSID_DAColor;

#ifdef __cplusplus

class DECLSPEC_UUID("C46C1BC6-3C52-11d0-9200-848C1D000000")
DAColor;
#endif

EXTERN_C const CLSID CLSID_DAGeometry;

#ifdef __cplusplus

class DECLSPEC_UUID("C46C1BE0-3C52-11d0-9200-848C1D000000")
DAGeometry;
#endif

EXTERN_C const CLSID CLSID_DAImage;

#ifdef __cplusplus

class DECLSPEC_UUID("C46C1BD4-3C52-11d0-9200-848C1D000000")
DAImage;
#endif

EXTERN_C const CLSID CLSID_DAMatte;

#ifdef __cplusplus

class DECLSPEC_UUID("C46C1BD2-3C52-11d0-9200-848C1D000000")
DAMatte;
#endif

EXTERN_C const CLSID CLSID_DAMicrophone;

#ifdef __cplusplus

class DECLSPEC_UUID("C46C1BE6-3C52-11d0-9200-848C1D000000")
DAMicrophone;
#endif

EXTERN_C const CLSID CLSID_DAMontage;

#ifdef __cplusplus

class DECLSPEC_UUID("C46C1BD6-3C52-11d0-9200-848C1D000000")
DAMontage;
#endif

EXTERN_C const CLSID CLSID_DANumber;

#ifdef __cplusplus

class DECLSPEC_UUID("9CDE7341-3C20-11d0-A330-00AA00B92C03")
DANumber;
#endif

EXTERN_C const CLSID CLSID_DAPath2;

#ifdef __cplusplus

class DECLSPEC_UUID("C46C1BD0-3C52-11d0-9200-848C1D000000")
DAPath2;
#endif

EXTERN_C const CLSID CLSID_DAPoint2;

#ifdef __cplusplus

class DECLSPEC_UUID("C46C1BC8-3C52-11d0-9200-848C1D000000")
DAPoint2;
#endif

EXTERN_C const CLSID CLSID_DAPoint3;

#ifdef __cplusplus

class DECLSPEC_UUID("C46C1BD8-3C52-11d0-9200-848C1D000000")
DAPoint3;
#endif

EXTERN_C const CLSID CLSID_DASound;

#ifdef __cplusplus

class DECLSPEC_UUID("C46C1BE4-3C52-11d0-9200-848C1D000000")
DASound;
#endif

EXTERN_C const CLSID CLSID_DAString;

#ifdef __cplusplus

class DECLSPEC_UUID("C46C1BC4-3C52-11d0-9200-848C1D000000")
DAString;
#endif

EXTERN_C const CLSID CLSID_DATransform2;

#ifdef __cplusplus

class DECLSPEC_UUID("C46C1BCC-3C52-11d0-9200-848C1D000000")
DATransform2;
#endif

EXTERN_C const CLSID CLSID_DATransform3;

#ifdef __cplusplus

class DECLSPEC_UUID("C46C1BDC-3C52-11d0-9200-848C1D000000")
DATransform3;
#endif

EXTERN_C const CLSID CLSID_DAVector2;

#ifdef __cplusplus

class DECLSPEC_UUID("C46C1BCA-3C52-11d0-9200-848C1D000000")
DAVector2;
#endif

EXTERN_C const CLSID CLSID_DAVector3;

#ifdef __cplusplus

class DECLSPEC_UUID("C46C1BDA-3C52-11d0-9200-848C1D000000")
DAVector3;
#endif

EXTERN_C const CLSID CLSID_DAFontStyle;

#ifdef __cplusplus

class DECLSPEC_UUID("25B0F91C-D23D-11d0-9B85-00C04FC2F51D")
DAFontStyle;
#endif

EXTERN_C const CLSID CLSID_DALineStyle;

#ifdef __cplusplus

class DECLSPEC_UUID("C46C1BF2-3C52-11d0-9200-848C1D000000")
DALineStyle;
#endif

EXTERN_C const CLSID CLSID_DAEndStyle;

#ifdef __cplusplus

class DECLSPEC_UUID("C46C1BEC-3C52-11d0-9200-848C1D000000")
DAEndStyle;
#endif

EXTERN_C const CLSID CLSID_DAJoinStyle;

#ifdef __cplusplus

class DECLSPEC_UUID("C46C1BEE-3C52-11d0-9200-848C1D000000")
DAJoinStyle;
#endif

EXTERN_C const CLSID CLSID_DADashStyle;

#ifdef __cplusplus

class DECLSPEC_UUID("C46C1BF0-3C52-11d0-9200-848C1D000000")
DADashStyle;
#endif

EXTERN_C const CLSID CLSID_DABbox2;

#ifdef __cplusplus

class DECLSPEC_UUID("C46C1BCE-3C52-11d0-9200-848C1D000000")
DABbox2;
#endif

EXTERN_C const CLSID CLSID_DABbox3;

#ifdef __cplusplus

class DECLSPEC_UUID("C46C1BDE-3C52-11d0-9200-848C1D000000")
DABbox3;
#endif

EXTERN_C const CLSID CLSID_DAPair;

#ifdef __cplusplus

class DECLSPEC_UUID("C46C1BF4-3C52-11d0-9200-848C1D000000")
DAPair;
#endif

EXTERN_C const CLSID CLSID_DAEvent;

#ifdef __cplusplus

class DECLSPEC_UUID("50B4791F-4731-11d0-8912-00C04FC2A0CA")
DAEvent;
#endif

EXTERN_C const CLSID CLSID_DAArray;

#ifdef __cplusplus

class DECLSPEC_UUID("D17506C3-6B26-11d0-8914-00C04FC2A0CA")
DAArray;
#endif

EXTERN_C const CLSID CLSID_DATuple;

#ifdef __cplusplus

class DECLSPEC_UUID("5DFB2651-9668-11d0-B17B-00C04FC2A0CA")
DATuple;
#endif

EXTERN_C const CLSID CLSID_DAUserData;

#ifdef __cplusplus

class DECLSPEC_UUID("AF868304-AB0B-11d0-876A-00C04FC29D46")
DAUserData;
#endif

#ifndef __IDAPreferences_INTERFACE_DEFINED__
#define __IDAPreferences_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDAPreferences
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDAPreferences;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("69B5BC70-9B19-11d0-9B60-00C04FC2F51D")
    IDAPreferences : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE PutPreference( 
            /* [in] */ BSTR preferenceName,
            /* [in] */ VARIANT value) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPreference( 
            /* [in] */ BSTR preferenceName,
            /* [retval][out] */ VARIANT *value) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Propagate( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDAPreferencesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDAPreferences * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDAPreferences * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDAPreferences * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDAPreferences * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDAPreferences * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDAPreferences * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDAPreferences * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *PutPreference )( 
            IDAPreferences * This,
            /* [in] */ BSTR preferenceName,
            /* [in] */ VARIANT value);
        
        HRESULT ( STDMETHODCALLTYPE *GetPreference )( 
            IDAPreferences * This,
            /* [in] */ BSTR preferenceName,
            /* [retval][out] */ VARIANT *value);
        
        HRESULT ( STDMETHODCALLTYPE *Propagate )( 
            IDAPreferences * This);
        
        END_INTERFACE
    } IDAPreferencesVtbl;

    interface IDAPreferences
    {
        CONST_VTBL struct IDAPreferencesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDAPreferences_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDAPreferences_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDAPreferences_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDAPreferences_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDAPreferences_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDAPreferences_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDAPreferences_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDAPreferences_PutPreference(This,preferenceName,value)	\
    (This)->lpVtbl -> PutPreference(This,preferenceName,value)

#define IDAPreferences_GetPreference(This,preferenceName,value)	\
    (This)->lpVtbl -> GetPreference(This,preferenceName,value)

#define IDAPreferences_Propagate(This)	\
    (This)->lpVtbl -> Propagate(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDAPreferences_PutPreference_Proxy( 
    IDAPreferences * This,
    /* [in] */ BSTR preferenceName,
    /* [in] */ VARIANT value);



HRESULT STDMETHODCALLTYPE IDAPreferences_GetPreference_Proxy( 
    IDAPreferences * This,
    /* [in] */ BSTR preferenceName,
    /* [retval][out] */ VARIANT *value);



HRESULT STDMETHODCALLTYPE IDAPreferences_Propagate_Proxy( 
    IDAPreferences * This);




#endif 	/* __IDAPreferences_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_DAView;

#ifdef __cplusplus

class DECLSPEC_UUID("283807B5-2C60-11d0-A31D-00AA00B92C03")
DAView;
#endif

#ifndef __IDASite_INTERFACE_DEFINED__
#define __IDASite_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDASite
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDASite;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("45393DF0-54B9-11cf-92A2-00AA00B8A733")
    IDASite : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetStatusText( 
            /* [in] */ BSTR StatusText) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReportError( 
            /* [in] */ HRESULT hr,
            /* [in] */ BSTR ErrorText) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReportGC( 
            /* [in] */ VARIANT_BOOL bStarting) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDASiteVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDASite * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDASite * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDASite * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDASite * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDASite * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDASite * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDASite * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *SetStatusText )( 
            IDASite * This,
            /* [in] */ BSTR StatusText);
        
        HRESULT ( STDMETHODCALLTYPE *ReportError )( 
            IDASite * This,
            /* [in] */ HRESULT hr,
            /* [in] */ BSTR ErrorText);
        
        HRESULT ( STDMETHODCALLTYPE *ReportGC )( 
            IDASite * This,
            /* [in] */ VARIANT_BOOL bStarting);
        
        END_INTERFACE
    } IDASiteVtbl;

    interface IDASite
    {
        CONST_VTBL struct IDASiteVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDASite_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDASite_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDASite_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDASite_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDASite_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDASite_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDASite_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDASite_SetStatusText(This,StatusText)	\
    (This)->lpVtbl -> SetStatusText(This,StatusText)

#define IDASite_ReportError(This,hr,ErrorText)	\
    (This)->lpVtbl -> ReportError(This,hr,ErrorText)

#define IDASite_ReportGC(This,bStarting)	\
    (This)->lpVtbl -> ReportGC(This,bStarting)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDASite_SetStatusText_Proxy( 
    IDASite * This,
    /* [in] */ BSTR StatusText);



HRESULT STDMETHODCALLTYPE IDASite_ReportError_Proxy( 
    IDASite * This,
    /* [in] */ HRESULT hr,
    /* [in] */ BSTR ErrorText);



HRESULT STDMETHODCALLTYPE IDASite_ReportGC_Proxy( 
    IDASite * This,
    /* [in] */ VARIANT_BOOL bStarting);




#endif 	/* __IDASite_INTERFACE_DEFINED__ */


#ifndef __IDAImportationResult_INTERFACE_DEFINED__
#define __IDAImportationResult_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDAImportationResult
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDAImportationResult;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("4A933702-E36F-11d0-9B99-00C04FC2F51D")
    IDAImportationResult : public IDispatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Image( 
            /* [retval][out] */ IDAImage **ppImage) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Sound( 
            /* [retval][out] */ IDASound **ppSound) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Geometry( 
            /* [retval][out] */ IDAGeometry **ppGeometry) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Duration( 
            /* [retval][out] */ IDANumber **ppDuration) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CompletionEvent( 
            /* [retval][out] */ IDAEvent **ppCompletionEvent) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Progress( 
            /* [retval][out] */ IDANumber **ppProgress) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Size( 
            /* [retval][out] */ IDANumber **ppSizeInBytes) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDAImportationResultVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDAImportationResult * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDAImportationResult * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDAImportationResult * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDAImportationResult * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDAImportationResult * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDAImportationResult * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDAImportationResult * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Image )( 
            IDAImportationResult * This,
            /* [retval][out] */ IDAImage **ppImage);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Sound )( 
            IDAImportationResult * This,
            /* [retval][out] */ IDASound **ppSound);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Geometry )( 
            IDAImportationResult * This,
            /* [retval][out] */ IDAGeometry **ppGeometry);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Duration )( 
            IDAImportationResult * This,
            /* [retval][out] */ IDANumber **ppDuration);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CompletionEvent )( 
            IDAImportationResult * This,
            /* [retval][out] */ IDAEvent **ppCompletionEvent);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Progress )( 
            IDAImportationResult * This,
            /* [retval][out] */ IDANumber **ppProgress);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Size )( 
            IDAImportationResult * This,
            /* [retval][out] */ IDANumber **ppSizeInBytes);
        
        END_INTERFACE
    } IDAImportationResultVtbl;

    interface IDAImportationResult
    {
        CONST_VTBL struct IDAImportationResultVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDAImportationResult_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDAImportationResult_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDAImportationResult_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDAImportationResult_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDAImportationResult_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDAImportationResult_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDAImportationResult_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDAImportationResult_get_Image(This,ppImage)	\
    (This)->lpVtbl -> get_Image(This,ppImage)

#define IDAImportationResult_get_Sound(This,ppSound)	\
    (This)->lpVtbl -> get_Sound(This,ppSound)

#define IDAImportationResult_get_Geometry(This,ppGeometry)	\
    (This)->lpVtbl -> get_Geometry(This,ppGeometry)

#define IDAImportationResult_get_Duration(This,ppDuration)	\
    (This)->lpVtbl -> get_Duration(This,ppDuration)

#define IDAImportationResult_get_CompletionEvent(This,ppCompletionEvent)	\
    (This)->lpVtbl -> get_CompletionEvent(This,ppCompletionEvent)

#define IDAImportationResult_get_Progress(This,ppProgress)	\
    (This)->lpVtbl -> get_Progress(This,ppProgress)

#define IDAImportationResult_get_Size(This,ppSizeInBytes)	\
    (This)->lpVtbl -> get_Size(This,ppSizeInBytes)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IDAImportationResult_get_Image_Proxy( 
    IDAImportationResult * This,
    /* [retval][out] */ IDAImage **ppImage);



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IDAImportationResult_get_Sound_Proxy( 
    IDAImportationResult * This,
    /* [retval][out] */ IDASound **ppSound);



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IDAImportationResult_get_Geometry_Proxy( 
    IDAImportationResult * This,
    /* [retval][out] */ IDAGeometry **ppGeometry);



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IDAImportationResult_get_Duration_Proxy( 
    IDAImportationResult * This,
    /* [retval][out] */ IDANumber **ppDuration);



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IDAImportationResult_get_CompletionEvent_Proxy( 
    IDAImportationResult * This,
    /* [retval][out] */ IDAEvent **ppCompletionEvent);



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IDAImportationResult_get_Progress_Proxy( 
    IDAImportationResult * This,
    /* [retval][out] */ IDANumber **ppProgress);



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IDAImportationResult_get_Size_Proxy( 
    IDAImportationResult * This,
    /* [retval][out] */ IDANumber **ppSizeInBytes);




#endif 	/* __IDAImportationResult_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_DAImportationResult;

#ifdef __cplusplus

class DECLSPEC_UUID("BCBB1F75-E384-11d0-9B99-00C04FC2F51D")
DAImportationResult;
#endif

EXTERN_C const CLSID CLSID_DAPickableResult;

#ifdef __cplusplus

class DECLSPEC_UUID("BCBB1F74-E384-11d0-9B99-00C04FC2F51D")
DAPickableResult;
#endif

#ifndef __IDAStatics_INTERFACE_DEFINED__
#define __IDAStatics_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDAStatics
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [dual][hidden][oleautomation][unique][object][local][helpstring][uuid] */ 



EXTERN_C const IID IID_IDAStatics;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("542FB452-5003-11cf-92A2-00AA00B8A733")
    IDAStatics : public IDispatch
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_VersionString( 
            /* [retval][out] */ BSTR *str) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Site( 
            /* [retval][out] */ IDASite **pSite) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Site( 
            /* [in] */ IDASite *pSite) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_ClientSite( 
            /* [in] */ IOleClientSite *pClientSite) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ClientSite( 
            /* [retval][out] */ IOleClientSite **pClientSite) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_PixelConstructionMode( 
            /* [in] */ VARIANT_BOOL bMode) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_PixelConstructionMode( 
            /* [retval][out] */ VARIANT_BOOL *bMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TriggerEvent( 
            /* [in] */ IDAEvent *event,
            /* [in] */ IDABehavior *data) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NewDrawingSurface( 
            /* [retval][out] */ IDADrawingSurface **pds) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ImportMovie( 
            /* [in] */ BSTR url,
            /* [retval][out] */ IDAImportationResult **ppResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ImportMovieAsync( 
            /* [in] */ BSTR url,
            /* [in] */ IDAImage *pImageStandIn,
            /* [in] */ IDASound *pSoundStandIn,
            /* [retval][out] */ IDAImportationResult **ppResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ImportImage( 
            /* [in] */ BSTR url,
            /* [retval][out] */ IDAImage **ppImage) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ImportImageAsync( 
            /* [in] */ BSTR url,
            /* [in] */ IDAImage *pImageStandIn,
            /* [retval][out] */ IDAImportationResult **ppResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ImportImageColorKey( 
            /* [in] */ BSTR url,
            /* [in] */ BYTE colorKeyRed,
            /* [in] */ BYTE colorKeyGreen,
            /* [in] */ BYTE colorKeyBlue,
            /* [retval][out] */ IDAImage **ppImage) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ImportImageAsyncColorKey( 
            /* [in] */ BSTR url,
            /* [in] */ IDAImage *pImageStandIn,
            /* [in] */ BYTE colorKeyRed,
            /* [in] */ BYTE colorKeyGreen,
            /* [in] */ BYTE colorKeyBlue,
            /* [retval][out] */ IDAImportationResult **ppResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ImportSound( 
            /* [in] */ BSTR url,
            /* [retval][out] */ IDAImportationResult **ppResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ImportSoundAsync( 
            /* [in] */ BSTR url,
            /* [in] */ IDASound *pSoundStandIn,
            /* [retval][out] */ IDAImportationResult **ppResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ImportGeometry( 
            /* [in] */ BSTR url,
            /* [retval][out] */ IDAGeometry **ppGeometry) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ImportGeometryAsync( 
            /* [in] */ BSTR url,
            /* [in] */ IDAGeometry *pGeoStandIn,
            /* [retval][out] */ IDAImportationResult **ppResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ImportDirectDrawSurface( 
            /* [in] */ IUnknown *dds,
            /* [in] */ IDAEvent *updateEvent,
            /* [retval][out] */ IDAImage **ppImage) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Cond( 
            /* [in] */ IDABoolean *c,
            /* [in] */ IDABehavior *i,
            /* [in] */ IDABehavior *e,
            /* [retval][out] */ IDABehavior **pCondBvr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DAArrayEx( 
            /* [in] */ LONG s,
            /* [size_is][in] */ IDABehavior *pBvrs[  ],
            /* [retval][out] */ IDAArray **bvr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DAArray( 
            /* [in] */ VARIANT bvrs,
            /* [retval][out] */ IDAArray **bvr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DATupleEx( 
            /* [in] */ LONG s,
            /* [size_is][in] */ IDABehavior *pBvrs[  ],
            /* [retval][out] */ IDATuple **bvr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DATuple( 
            /* [in] */ VARIANT bvrs,
            /* [retval][out] */ IDATuple **bvr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ModifiableBehavior( 
            /* [in] */ IDABehavior *orig,
            /* [retval][out] */ IDABehavior **bvr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UninitializedArray( 
            /* [in] */ IDAArray *typeTmp,
            /* [retval][out] */ IDAArray **bvr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UninitializedTuple( 
            /* [in] */ IDATuple *typeTmp,
            /* [retval][out] */ IDATuple **bvr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NumberBSplineEx( 
            /* [in] */ int degree,
            /* [in] */ LONG numKnots,
            /* [size_is][in] */ IDANumber *knots[  ],
            /* [in] */ LONG numPts,
            /* [size_is][in] */ IDANumber *ctrlPts[  ],
            /* [in] */ LONG numWts,
            /* [size_is][in] */ IDANumber *weights[  ],
            /* [in] */ IDANumber *evaluator,
            /* [retval][out] */ IDANumber **bvr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NumberBSpline( 
            /* [in] */ int degree,
            /* [in] */ VARIANT knots,
            /* [in] */ VARIANT CtrlPts,
            /* [in] */ VARIANT weights,
            /* [in] */ IDANumber *evaluator,
            /* [retval][out] */ IDANumber **bvr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Point2BSplineEx( 
            /* [in] */ int degree,
            /* [in] */ LONG numKnots,
            /* [size_is][in] */ IDANumber *knots[  ],
            /* [in] */ LONG numPts,
            /* [size_is][in] */ IDAPoint2 *ctrlPts[  ],
            /* [in] */ LONG numWts,
            /* [size_is][in] */ IDANumber *weights[  ],
            /* [in] */ IDANumber *evaluator,
            /* [retval][out] */ IDAPoint2 **bvr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Point2BSpline( 
            /* [in] */ int degree,
            /* [in] */ VARIANT knots,
            /* [in] */ VARIANT CtrlPts,
            /* [in] */ VARIANT weights,
            /* [in] */ IDANumber *evaluator,
            /* [retval][out] */ IDAPoint2 **bvr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Point3BSplineEx( 
            /* [in] */ int degree,
            /* [in] */ LONG numKnots,
            /* [size_is][in] */ IDANumber *knots[  ],
            /* [in] */ LONG numPts,
            /* [size_is][in] */ IDAPoint3 *ctrlPts[  ],
            /* [in] */ LONG numWts,
            /* [size_is][in] */ IDANumber *weights[  ],
            /* [in] */ IDANumber *evaluator,
            /* [retval][out] */ IDAPoint3 **bvr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Point3BSpline( 
            /* [in] */ int degree,
            /* [in] */ VARIANT knots,
            /* [in] */ VARIANT CtrlPts,
            /* [in] */ VARIANT weights,
            /* [in] */ IDANumber *evaluator,
            /* [retval][out] */ IDAPoint3 **bvr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Vector2BSplineEx( 
            /* [in] */ int degree,
            /* [in] */ LONG numKnots,
            /* [size_is][in] */ IDANumber *knots[  ],
            /* [in] */ LONG numPts,
            /* [size_is][in] */ IDAVector2 *ctrlPts[  ],
            /* [in] */ LONG numWts,
            /* [size_is][in] */ IDANumber *weights[  ],
            /* [in] */ IDANumber *evaluator,
            /* [retval][out] */ IDAVector2 **bvr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Vector2BSpline( 
            /* [in] */ int degree,
            /* [in] */ VARIANT knots,
            /* [in] */ VARIANT CtrlPts,
            /* [in] */ VARIANT weights,
            /* [in] */ IDANumber *evaluator,
            /* [retval][out] */ IDAVector2 **bvr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Vector3BSplineEx( 
            /* [in] */ int degree,
            /* [in] */ LONG numKnots,
            /* [size_is][in] */ IDANumber *knots[  ],
            /* [in] */ LONG numPts,
            /* [size_is][in] */ IDAVector3 *ctrlPts[  ],
            /* [in] */ LONG numWts,
            /* [size_is][in] */ IDANumber *weights[  ],
            /* [in] */ IDANumber *evaluator,
            /* [retval][out] */ IDAVector3 **bvr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Vector3BSpline( 
            /* [in] */ int degree,
            /* [in] */ VARIANT knots,
            /* [in] */ VARIANT CtrlPts,
            /* [in] */ VARIANT weights,
            /* [in] */ IDANumber *evaluator,
            /* [retval][out] */ IDAVector3 **bvr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Pow( 
            /* [in] */ IDANumber *a_0,
            /* [in] */ IDANumber *b_1,
            /* [retval][out] */ IDANumber **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Abs( 
            /* [in] */ IDANumber *a_0,
            /* [retval][out] */ IDANumber **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Sqrt( 
            /* [in] */ IDANumber *a_0,
            /* [retval][out] */ IDANumber **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Floor( 
            /* [in] */ IDANumber *a_0,
            /* [retval][out] */ IDANumber **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Round( 
            /* [in] */ IDANumber *a_0,
            /* [retval][out] */ IDANumber **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Ceiling( 
            /* [in] */ IDANumber *a_0,
            /* [retval][out] */ IDANumber **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Asin( 
            /* [in] */ IDANumber *a_0,
            /* [retval][out] */ IDANumber **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Acos( 
            /* [in] */ IDANumber *a_0,
            /* [retval][out] */ IDANumber **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Atan( 
            /* [in] */ IDANumber *a_0,
            /* [retval][out] */ IDANumber **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Sin( 
            /* [in] */ IDANumber *a_0,
            /* [retval][out] */ IDANumber **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Cos( 
            /* [in] */ IDANumber *a_0,
            /* [retval][out] */ IDANumber **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Tan( 
            /* [in] */ IDANumber *a_0,
            /* [retval][out] */ IDANumber **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Exp( 
            /* [in] */ IDANumber *a_0,
            /* [retval][out] */ IDANumber **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Ln( 
            /* [in] */ IDANumber *a_0,
            /* [retval][out] */ IDANumber **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Log10( 
            /* [in] */ IDANumber *a_0,
            /* [retval][out] */ IDANumber **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ToDegrees( 
            /* [in] */ IDANumber *a_0,
            /* [retval][out] */ IDANumber **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ToRadians( 
            /* [in] */ IDANumber *a_0,
            /* [retval][out] */ IDANumber **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Mod( 
            /* [in] */ IDANumber *a_0,
            /* [in] */ IDANumber *b_1,
            /* [retval][out] */ IDANumber **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Atan2( 
            /* [in] */ IDANumber *a_0,
            /* [in] */ IDANumber *b_1,
            /* [retval][out] */ IDANumber **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ IDANumber *a_0,
            /* [in] */ IDANumber *b_1,
            /* [retval][out] */ IDANumber **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Sub( 
            /* [in] */ IDANumber *a_0,
            /* [in] */ IDANumber *b_1,
            /* [retval][out] */ IDANumber **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Mul( 
            /* [in] */ IDANumber *a_0,
            /* [in] */ IDANumber *b_1,
            /* [retval][out] */ IDANumber **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Div( 
            /* [in] */ IDANumber *a_0,
            /* [in] */ IDANumber *b_1,
            /* [retval][out] */ IDANumber **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LT( 
            /* [in] */ IDANumber *a_0,
            /* [in] */ IDANumber *b_1,
            /* [retval][out] */ IDABoolean **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LTE( 
            /* [in] */ IDANumber *a_0,
            /* [in] */ IDANumber *b_1,
            /* [retval][out] */ IDABoolean **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GT( 
            /* [in] */ IDANumber *a_0,
            /* [in] */ IDANumber *b_1,
            /* [retval][out] */ IDABoolean **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GTE( 
            /* [in] */ IDANumber *a_0,
            /* [in] */ IDANumber *b_1,
            /* [retval][out] */ IDABoolean **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EQ( 
            /* [in] */ IDANumber *a_0,
            /* [in] */ IDANumber *b_1,
            /* [retval][out] */ IDABoolean **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NE( 
            /* [in] */ IDANumber *a_0,
            /* [in] */ IDANumber *b_1,
            /* [retval][out] */ IDABoolean **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Neg( 
            /* [in] */ IDANumber *a_0,
            /* [retval][out] */ IDANumber **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InterpolateAnim( 
            /* [in] */ IDANumber *from_0,
            /* [in] */ IDANumber *to_1,
            /* [in] */ IDANumber *duration_2,
            /* [retval][out] */ IDANumber **ret_3) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Interpolate( 
            /* [in] */ double from_0,
            /* [in] */ double to_1,
            /* [in] */ double duration_2,
            /* [retval][out] */ IDANumber **ret_3) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SlowInSlowOutAnim( 
            /* [in] */ IDANumber *from_0,
            /* [in] */ IDANumber *to_1,
            /* [in] */ IDANumber *duration_2,
            /* [in] */ IDANumber *sharpness_3,
            /* [retval][out] */ IDANumber **ret_4) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SlowInSlowOut( 
            /* [in] */ double from_0,
            /* [in] */ double to_1,
            /* [in] */ double duration_2,
            /* [in] */ double sharpness_3,
            /* [retval][out] */ IDANumber **ret_4) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SoundSource( 
            /* [in] */ IDASound *snd_0,
            /* [retval][out] */ IDAGeometry **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Mix( 
            /* [in] */ IDASound *left_0,
            /* [in] */ IDASound *right_1,
            /* [retval][out] */ IDASound **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE And( 
            /* [in] */ IDABoolean *a_0,
            /* [in] */ IDABoolean *b_1,
            /* [retval][out] */ IDABoolean **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Or( 
            /* [in] */ IDABoolean *a_0,
            /* [in] */ IDABoolean *b_1,
            /* [retval][out] */ IDABoolean **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Not( 
            /* [in] */ IDABoolean *a_0,
            /* [retval][out] */ IDABoolean **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Integral( 
            /* [in] */ IDANumber *b_0,
            /* [retval][out] */ IDANumber **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Derivative( 
            /* [in] */ IDANumber *b_0,
            /* [retval][out] */ IDANumber **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IntegralVector2( 
            /* [in] */ IDAVector2 *v_0,
            /* [retval][out] */ IDAVector2 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IntegralVector3( 
            /* [in] */ IDAVector3 *v_0,
            /* [retval][out] */ IDAVector3 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DerivativeVector2( 
            /* [in] */ IDAVector2 *v_0,
            /* [retval][out] */ IDAVector2 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DerivativeVector3( 
            /* [in] */ IDAVector3 *v_0,
            /* [retval][out] */ IDAVector3 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DerivativePoint2( 
            /* [in] */ IDAPoint2 *v_0,
            /* [retval][out] */ IDAVector2 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DerivativePoint3( 
            /* [in] */ IDAPoint3 *v_0,
            /* [retval][out] */ IDAVector3 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE KeyState( 
            /* [in] */ IDANumber *n_0,
            /* [retval][out] */ IDABoolean **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE KeyUp( 
            /* [in] */ LONG arg_0,
            /* [retval][out] */ IDAEvent **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE KeyDown( 
            /* [in] */ LONG arg_0,
            /* [retval][out] */ IDAEvent **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DANumber( 
            /* [in] */ double num_0,
            /* [retval][out] */ IDANumber **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DAString( 
            /* [in] */ BSTR str_0,
            /* [retval][out] */ IDAString **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DABoolean( 
            /* [in] */ VARIANT_BOOL num_0,
            /* [retval][out] */ IDABoolean **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SeededRandom( 
            /* [in] */ double arg_0,
            /* [retval][out] */ IDANumber **ret_1) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_MousePosition( 
            /* [retval][out] */ IDAPoint2 **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_LeftButtonState( 
            /* [retval][out] */ IDABoolean **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_RightButtonState( 
            /* [retval][out] */ IDABoolean **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_DATrue( 
            /* [retval][out] */ IDABoolean **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_DAFalse( 
            /* [retval][out] */ IDABoolean **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_LocalTime( 
            /* [retval][out] */ IDANumber **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_GlobalTime( 
            /* [retval][out] */ IDANumber **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Pixel( 
            /* [retval][out] */ IDANumber **ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UserData( 
            /* [in] */ IUnknown *data_0,
            /* [retval][out] */ IDAUserData **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UntilNotify( 
            /* [in] */ IDABehavior *b0_0,
            /* [in] */ IDAEvent *event_1,
            /* [in] */ IDAUntilNotifier *notifier_2,
            /* [retval][out] */ IDABehavior **ret_3) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Until( 
            /* [in] */ IDABehavior *b0_0,
            /* [in] */ IDAEvent *event_1,
            /* [in] */ IDABehavior *b1_2,
            /* [retval][out] */ IDABehavior **ret_3) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UntilEx( 
            /* [in] */ IDABehavior *b0_0,
            /* [in] */ IDAEvent *event_1,
            /* [retval][out] */ IDABehavior **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Sequence( 
            /* [in] */ IDABehavior *s1_0,
            /* [in] */ IDABehavior *s2_1,
            /* [retval][out] */ IDABehavior **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FollowPath( 
            /* [in] */ IDAPath2 *path_0,
            /* [in] */ double duration_1,
            /* [retval][out] */ IDATransform2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FollowPathAngle( 
            /* [in] */ IDAPath2 *path_0,
            /* [in] */ double duration_1,
            /* [retval][out] */ IDATransform2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FollowPathAngleUpright( 
            /* [in] */ IDAPath2 *path_0,
            /* [in] */ double duration_1,
            /* [retval][out] */ IDATransform2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FollowPathEval( 
            /* [in] */ IDAPath2 *path_0,
            /* [in] */ IDANumber *eval_1,
            /* [retval][out] */ IDATransform2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FollowPathAngleEval( 
            /* [in] */ IDAPath2 *path_0,
            /* [in] */ IDANumber *eval_1,
            /* [retval][out] */ IDATransform2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FollowPathAngleUprightEval( 
            /* [in] */ IDAPath2 *path_0,
            /* [in] */ IDANumber *eval_1,
            /* [retval][out] */ IDATransform2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FollowPathAnim( 
            /* [in] */ IDAPath2 *obsoleted1_0,
            /* [in] */ IDANumber *obsoleted2_1,
            /* [retval][out] */ IDATransform2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FollowPathAngleAnim( 
            /* [in] */ IDAPath2 *obsoleted1_0,
            /* [in] */ IDANumber *obsoleted2_1,
            /* [retval][out] */ IDATransform2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FollowPathAngleUprightAnim( 
            /* [in] */ IDAPath2 *obsoleted1_0,
            /* [in] */ IDANumber *obsoleted2_1,
            /* [retval][out] */ IDATransform2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ConcatString( 
            /* [in] */ IDAString *s1_0,
            /* [in] */ IDAString *s2_1,
            /* [retval][out] */ IDAString **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PerspectiveCamera( 
            /* [in] */ double focalDist_0,
            /* [in] */ double nearClip_1,
            /* [retval][out] */ IDACamera **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PerspectiveCameraAnim( 
            /* [in] */ IDANumber *focalDist_0,
            /* [in] */ IDANumber *nearClip_1,
            /* [retval][out] */ IDACamera **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ParallelCamera( 
            /* [in] */ double nearClip_0,
            /* [retval][out] */ IDACamera **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ParallelCameraAnim( 
            /* [in] */ IDANumber *nearClip_0,
            /* [retval][out] */ IDACamera **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ColorRgbAnim( 
            /* [in] */ IDANumber *red_0,
            /* [in] */ IDANumber *green_1,
            /* [in] */ IDANumber *blue_2,
            /* [retval][out] */ IDAColor **ret_3) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ColorRgb( 
            /* [in] */ double red_0,
            /* [in] */ double green_1,
            /* [in] */ double blue_2,
            /* [retval][out] */ IDAColor **ret_3) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ColorRgb255( 
            /* [in] */ short red_0,
            /* [in] */ short green_1,
            /* [in] */ short blue_2,
            /* [retval][out] */ IDAColor **ret_3) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ColorHsl( 
            /* [in] */ double hue_0,
            /* [in] */ double saturation_1,
            /* [in] */ double lum_2,
            /* [retval][out] */ IDAColor **ret_3) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ColorHslAnim( 
            /* [in] */ IDANumber *hue_0,
            /* [in] */ IDANumber *saturation_1,
            /* [in] */ IDANumber *lum_2,
            /* [retval][out] */ IDAColor **ret_3) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Red( 
            /* [retval][out] */ IDAColor **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Green( 
            /* [retval][out] */ IDAColor **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Blue( 
            /* [retval][out] */ IDAColor **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Cyan( 
            /* [retval][out] */ IDAColor **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Magenta( 
            /* [retval][out] */ IDAColor **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Yellow( 
            /* [retval][out] */ IDAColor **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Black( 
            /* [retval][out] */ IDAColor **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_White( 
            /* [retval][out] */ IDAColor **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Aqua( 
            /* [retval][out] */ IDAColor **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Fuchsia( 
            /* [retval][out] */ IDAColor **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Gray( 
            /* [retval][out] */ IDAColor **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Lime( 
            /* [retval][out] */ IDAColor **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Maroon( 
            /* [retval][out] */ IDAColor **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Navy( 
            /* [retval][out] */ IDAColor **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Olive( 
            /* [retval][out] */ IDAColor **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Purple( 
            /* [retval][out] */ IDAColor **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Silver( 
            /* [retval][out] */ IDAColor **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Teal( 
            /* [retval][out] */ IDAColor **ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Predicate( 
            /* [in] */ IDABoolean *b_0,
            /* [retval][out] */ IDAEvent **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NotEvent( 
            /* [in] */ IDAEvent *event_0,
            /* [retval][out] */ IDAEvent **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AndEvent( 
            /* [in] */ IDAEvent *e1_0,
            /* [in] */ IDAEvent *e2_1,
            /* [retval][out] */ IDAEvent **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OrEvent( 
            /* [in] */ IDAEvent *e1_0,
            /* [in] */ IDAEvent *e2_1,
            /* [retval][out] */ IDAEvent **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ThenEvent( 
            /* [in] */ IDAEvent *e1_0,
            /* [in] */ IDAEvent *e2_1,
            /* [retval][out] */ IDAEvent **ret_2) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_LeftButtonDown( 
            /* [retval][out] */ IDAEvent **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_LeftButtonUp( 
            /* [retval][out] */ IDAEvent **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_RightButtonDown( 
            /* [retval][out] */ IDAEvent **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_RightButtonUp( 
            /* [retval][out] */ IDAEvent **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Always( 
            /* [retval][out] */ IDAEvent **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Never( 
            /* [retval][out] */ IDAEvent **ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TimerAnim( 
            /* [in] */ IDANumber *n_0,
            /* [retval][out] */ IDAEvent **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Timer( 
            /* [in] */ double n_0,
            /* [retval][out] */ IDAEvent **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AppTriggeredEvent( 
            /* [retval][out] */ IDAEvent **ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ScriptCallback( 
            /* [in] */ BSTR obsolete1_0,
            /* [in] */ IDAEvent *obsolete2_1,
            /* [in] */ BSTR obsolete3_2,
            /* [retval][out] */ IDAEvent **ret_3) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_EmptyGeometry( 
            /* [retval][out] */ IDAGeometry **ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnionGeometry( 
            /* [in] */ IDAGeometry *g1_0,
            /* [in] */ IDAGeometry *g2_1,
            /* [retval][out] */ IDAGeometry **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnionGeometryArrayEx( 
            /* [in] */ LONG imgs_0size,
            /* [size_is][in] */ IDAGeometry *imgs_0[  ],
            /* [retval][out] */ IDAGeometry **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnionGeometryArray( 
            /* [in] */ VARIANT imgs_0,
            /* [retval][out] */ IDAGeometry **ret_1) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_EmptyImage( 
            /* [retval][out] */ IDAImage **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_DetectableEmptyImage( 
            /* [retval][out] */ IDAImage **ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SolidColorImage( 
            /* [in] */ IDAColor *col_0,
            /* [retval][out] */ IDAImage **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GradientPolygonEx( 
            /* [in] */ LONG points_0size,
            /* [size_is][in] */ IDAPoint2 *points_0[  ],
            /* [in] */ LONG colors_1size,
            /* [size_is][in] */ IDAColor *colors_1[  ],
            /* [retval][out] */ IDAImage **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GradientPolygon( 
            /* [in] */ VARIANT points_0,
            /* [in] */ VARIANT colors_1,
            /* [retval][out] */ IDAImage **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RadialGradientPolygonEx( 
            /* [in] */ IDAColor *inner_0,
            /* [in] */ IDAColor *outer_1,
            /* [in] */ LONG points_2size,
            /* [size_is][in] */ IDAPoint2 *points_2[  ],
            /* [in] */ double fallOff_3,
            /* [retval][out] */ IDAImage **ret_4) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RadialGradientPolygon( 
            /* [in] */ IDAColor *inner_0,
            /* [in] */ IDAColor *outer_1,
            /* [in] */ VARIANT points_2,
            /* [in] */ double fallOff_3,
            /* [retval][out] */ IDAImage **ret_4) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RadialGradientPolygonAnimEx( 
            /* [in] */ IDAColor *inner_0,
            /* [in] */ IDAColor *outer_1,
            /* [in] */ LONG points_2size,
            /* [size_is][in] */ IDAPoint2 *points_2[  ],
            /* [in] */ IDANumber *fallOff_3,
            /* [retval][out] */ IDAImage **ret_4) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RadialGradientPolygonAnim( 
            /* [in] */ IDAColor *inner_0,
            /* [in] */ IDAColor *outer_1,
            /* [in] */ VARIANT points_2,
            /* [in] */ IDANumber *fallOff_3,
            /* [retval][out] */ IDAImage **ret_4) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GradientSquare( 
            /* [in] */ IDAColor *lowerLeft_0,
            /* [in] */ IDAColor *upperLeft_1,
            /* [in] */ IDAColor *upperRight_2,
            /* [in] */ IDAColor *lowerRight_3,
            /* [retval][out] */ IDAImage **ret_4) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RadialGradientSquare( 
            /* [in] */ IDAColor *inner_0,
            /* [in] */ IDAColor *outer_1,
            /* [in] */ double fallOff_2,
            /* [retval][out] */ IDAImage **ret_3) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RadialGradientSquareAnim( 
            /* [in] */ IDAColor *inner_0,
            /* [in] */ IDAColor *outer_1,
            /* [in] */ IDANumber *fallOff_2,
            /* [retval][out] */ IDAImage **ret_3) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RadialGradientRegularPoly( 
            /* [in] */ IDAColor *inner_0,
            /* [in] */ IDAColor *outer_1,
            /* [in] */ double numEdges_2,
            /* [in] */ double fallOff_3,
            /* [retval][out] */ IDAImage **ret_4) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RadialGradientRegularPolyAnim( 
            /* [in] */ IDAColor *inner_0,
            /* [in] */ IDAColor *outer_1,
            /* [in] */ IDANumber *numEdges_2,
            /* [in] */ IDANumber *fallOff_3,
            /* [retval][out] */ IDAImage **ret_4) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GradientHorizontal( 
            /* [in] */ IDAColor *start_0,
            /* [in] */ IDAColor *stop_1,
            /* [in] */ double fallOff_2,
            /* [retval][out] */ IDAImage **ret_3) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GradientHorizontalAnim( 
            /* [in] */ IDAColor *start_0,
            /* [in] */ IDAColor *stop_1,
            /* [in] */ IDANumber *fallOff_2,
            /* [retval][out] */ IDAImage **ret_3) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HatchHorizontal( 
            /* [in] */ IDAColor *lineClr_0,
            /* [in] */ double spacing_1,
            /* [retval][out] */ IDAImage **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HatchHorizontalAnim( 
            /* [in] */ IDAColor *lineClr_0,
            /* [in] */ IDANumber *spacing_1,
            /* [retval][out] */ IDAImage **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HatchVertical( 
            /* [in] */ IDAColor *lineClr_0,
            /* [in] */ double spacing_1,
            /* [retval][out] */ IDAImage **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HatchVerticalAnim( 
            /* [in] */ IDAColor *lineClr_0,
            /* [in] */ IDANumber *spacing_1,
            /* [retval][out] */ IDAImage **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HatchForwardDiagonal( 
            /* [in] */ IDAColor *lineClr_0,
            /* [in] */ double spacing_1,
            /* [retval][out] */ IDAImage **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HatchForwardDiagonalAnim( 
            /* [in] */ IDAColor *lineClr_0,
            /* [in] */ IDANumber *spacing_1,
            /* [retval][out] */ IDAImage **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HatchBackwardDiagonal( 
            /* [in] */ IDAColor *lineClr_0,
            /* [in] */ double spacing_1,
            /* [retval][out] */ IDAImage **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HatchBackwardDiagonalAnim( 
            /* [in] */ IDAColor *lineClr_0,
            /* [in] */ IDANumber *spacing_1,
            /* [retval][out] */ IDAImage **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HatchCross( 
            /* [in] */ IDAColor *lineClr_0,
            /* [in] */ double spacing_1,
            /* [retval][out] */ IDAImage **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HatchCrossAnim( 
            /* [in] */ IDAColor *lineClr_0,
            /* [in] */ IDANumber *spacing_1,
            /* [retval][out] */ IDAImage **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HatchDiagonalCross( 
            /* [in] */ IDAColor *lineClr_0,
            /* [in] */ double spacing_1,
            /* [retval][out] */ IDAImage **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HatchDiagonalCrossAnim( 
            /* [in] */ IDAColor *lineClr_0,
            /* [in] */ IDANumber *spacing_1,
            /* [retval][out] */ IDAImage **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Overlay( 
            /* [in] */ IDAImage *top_0,
            /* [in] */ IDAImage *bottom_1,
            /* [retval][out] */ IDAImage **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OverlayArrayEx( 
            /* [in] */ LONG imgs_0size,
            /* [size_is][in] */ IDAImage *imgs_0[  ],
            /* [retval][out] */ IDAImage **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OverlayArray( 
            /* [in] */ VARIANT imgs_0,
            /* [retval][out] */ IDAImage **ret_1) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_AmbientLight( 
            /* [retval][out] */ IDAGeometry **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_DirectionalLight( 
            /* [retval][out] */ IDAGeometry **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_PointLight( 
            /* [retval][out] */ IDAGeometry **ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SpotLightAnim( 
            /* [in] */ IDANumber *fullcone_0,
            /* [in] */ IDANumber *cutoff_1,
            /* [retval][out] */ IDAGeometry **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SpotLight( 
            /* [in] */ IDANumber *fullcone_0,
            /* [in] */ double cutoff_1,
            /* [retval][out] */ IDAGeometry **ret_2) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_DefaultLineStyle( 
            /* [retval][out] */ IDALineStyle **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_EmptyLineStyle( 
            /* [retval][out] */ IDALineStyle **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_JoinStyleBevel( 
            /* [retval][out] */ IDAJoinStyle **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_JoinStyleRound( 
            /* [retval][out] */ IDAJoinStyle **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_JoinStyleMiter( 
            /* [retval][out] */ IDAJoinStyle **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_EndStyleFlat( 
            /* [retval][out] */ IDAEndStyle **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_EndStyleSquare( 
            /* [retval][out] */ IDAEndStyle **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_EndStyleRound( 
            /* [retval][out] */ IDAEndStyle **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_DashStyleSolid( 
            /* [retval][out] */ IDADashStyle **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_DashStyleDashed( 
            /* [retval][out] */ IDADashStyle **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_DefaultMicrophone( 
            /* [retval][out] */ IDAMicrophone **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_OpaqueMatte( 
            /* [retval][out] */ IDAMatte **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ClearMatte( 
            /* [retval][out] */ IDAMatte **ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnionMatte( 
            /* [in] */ IDAMatte *m1_0,
            /* [in] */ IDAMatte *m2_1,
            /* [retval][out] */ IDAMatte **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IntersectMatte( 
            /* [in] */ IDAMatte *m1_0,
            /* [in] */ IDAMatte *m2_1,
            /* [retval][out] */ IDAMatte **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DifferenceMatte( 
            /* [in] */ IDAMatte *m1_0,
            /* [in] */ IDAMatte *m2_1,
            /* [retval][out] */ IDAMatte **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FillMatte( 
            /* [in] */ IDAPath2 *p_0,
            /* [retval][out] */ IDAMatte **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TextMatte( 
            /* [in] */ IDAString *str_0,
            /* [in] */ IDAFontStyle *fs_1,
            /* [retval][out] */ IDAMatte **ret_2) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_EmptyMontage( 
            /* [retval][out] */ IDAMontage **ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ImageMontage( 
            /* [in] */ IDAImage *im_0,
            /* [in] */ double depth_1,
            /* [retval][out] */ IDAMontage **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ImageMontageAnim( 
            /* [in] */ IDAImage *im_0,
            /* [in] */ IDANumber *depth_1,
            /* [retval][out] */ IDAMontage **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnionMontage( 
            /* [in] */ IDAMontage *m1_0,
            /* [in] */ IDAMontage *m2_1,
            /* [retval][out] */ IDAMontage **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Concat( 
            /* [in] */ IDAPath2 *p1_0,
            /* [in] */ IDAPath2 *p2_1,
            /* [retval][out] */ IDAPath2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ConcatArrayEx( 
            /* [in] */ LONG paths_0size,
            /* [size_is][in] */ IDAPath2 *paths_0[  ],
            /* [retval][out] */ IDAPath2 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ConcatArray( 
            /* [in] */ VARIANT paths_0,
            /* [retval][out] */ IDAPath2 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Line( 
            /* [in] */ IDAPoint2 *p1_0,
            /* [in] */ IDAPoint2 *p2_1,
            /* [retval][out] */ IDAPath2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Ray( 
            /* [in] */ IDAPoint2 *pt_0,
            /* [retval][out] */ IDAPath2 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StringPathAnim( 
            /* [in] */ IDAString *str_0,
            /* [in] */ IDAFontStyle *fs_1,
            /* [retval][out] */ IDAPath2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StringPath( 
            /* [in] */ BSTR str_0,
            /* [in] */ IDAFontStyle *fs_1,
            /* [retval][out] */ IDAPath2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PolylineEx( 
            /* [in] */ LONG points_0size,
            /* [size_is][in] */ IDAPoint2 *points_0[  ],
            /* [retval][out] */ IDAPath2 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Polyline( 
            /* [in] */ VARIANT points_0,
            /* [retval][out] */ IDAPath2 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PolydrawPathEx( 
            /* [in] */ LONG points_0size,
            /* [size_is][in] */ IDAPoint2 *points_0[  ],
            /* [in] */ LONG codes_1size,
            /* [size_is][in] */ IDANumber *codes_1[  ],
            /* [retval][out] */ IDAPath2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PolydrawPath( 
            /* [in] */ VARIANT points_0,
            /* [in] */ VARIANT codes_1,
            /* [retval][out] */ IDAPath2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ArcRadians( 
            /* [in] */ double startAngle_0,
            /* [in] */ double endAngle_1,
            /* [in] */ double arcWidth_2,
            /* [in] */ double arcHeight_3,
            /* [retval][out] */ IDAPath2 **ret_4) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ArcRadiansAnim( 
            /* [in] */ IDANumber *startAngle_0,
            /* [in] */ IDANumber *endAngle_1,
            /* [in] */ IDANumber *arcWidth_2,
            /* [in] */ IDANumber *arcHeight_3,
            /* [retval][out] */ IDAPath2 **ret_4) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ArcDegrees( 
            /* [in] */ double startAngle_0,
            /* [in] */ double endAngle_1,
            /* [in] */ double arcWidth_2,
            /* [in] */ double arcHeight_3,
            /* [retval][out] */ IDAPath2 **ret_4) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PieRadians( 
            /* [in] */ double startAngle_0,
            /* [in] */ double endAngle_1,
            /* [in] */ double arcWidth_2,
            /* [in] */ double arcHeight_3,
            /* [retval][out] */ IDAPath2 **ret_4) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PieRadiansAnim( 
            /* [in] */ IDANumber *startAngle_0,
            /* [in] */ IDANumber *endAngle_1,
            /* [in] */ IDANumber *arcWidth_2,
            /* [in] */ IDANumber *arcHeight_3,
            /* [retval][out] */ IDAPath2 **ret_4) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PieDegrees( 
            /* [in] */ double startAngle_0,
            /* [in] */ double endAngle_1,
            /* [in] */ double arcWidth_2,
            /* [in] */ double arcHeight_3,
            /* [retval][out] */ IDAPath2 **ret_4) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Oval( 
            /* [in] */ double width_0,
            /* [in] */ double height_1,
            /* [retval][out] */ IDAPath2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OvalAnim( 
            /* [in] */ IDANumber *width_0,
            /* [in] */ IDANumber *height_1,
            /* [retval][out] */ IDAPath2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Rect( 
            /* [in] */ double width_0,
            /* [in] */ double height_1,
            /* [retval][out] */ IDAPath2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RectAnim( 
            /* [in] */ IDANumber *width_0,
            /* [in] */ IDANumber *height_1,
            /* [retval][out] */ IDAPath2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RoundRect( 
            /* [in] */ double width_0,
            /* [in] */ double height_1,
            /* [in] */ double cornerArcWidth_2,
            /* [in] */ double cornerArcHeight_3,
            /* [retval][out] */ IDAPath2 **ret_4) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RoundRectAnim( 
            /* [in] */ IDANumber *width_0,
            /* [in] */ IDANumber *height_1,
            /* [in] */ IDANumber *cornerArcWidth_2,
            /* [in] */ IDANumber *cornerArcHeight_3,
            /* [retval][out] */ IDAPath2 **ret_4) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CubicBSplinePathEx( 
            /* [in] */ LONG points_0size,
            /* [size_is][in] */ IDAPoint2 *points_0[  ],
            /* [in] */ LONG knots_1size,
            /* [size_is][in] */ IDANumber *knots_1[  ],
            /* [retval][out] */ IDAPath2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CubicBSplinePath( 
            /* [in] */ VARIANT points_0,
            /* [in] */ VARIANT knots_1,
            /* [retval][out] */ IDAPath2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TextPath( 
            /* [in] */ IDAString *obsolete1_0,
            /* [in] */ IDAFontStyle *obsolete2_1,
            /* [retval][out] */ IDAPath2 **ret_2) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Silence( 
            /* [retval][out] */ IDASound **ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MixArrayEx( 
            /* [in] */ LONG snds_0size,
            /* [size_is][in] */ IDASound *snds_0[  ],
            /* [retval][out] */ IDASound **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MixArray( 
            /* [in] */ VARIANT snds_0,
            /* [retval][out] */ IDASound **ret_1) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_SinSynth( 
            /* [retval][out] */ IDASound **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_DefaultFont( 
            /* [retval][out] */ IDAFontStyle **ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FontAnim( 
            /* [in] */ IDAString *str_0,
            /* [in] */ IDANumber *size_1,
            /* [in] */ IDAColor *col_2,
            /* [retval][out] */ IDAFontStyle **ret_3) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Font( 
            /* [in] */ BSTR str_0,
            /* [in] */ double size_1,
            /* [in] */ IDAColor *col_2,
            /* [retval][out] */ IDAFontStyle **ret_3) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StringImageAnim( 
            /* [in] */ IDAString *str_0,
            /* [in] */ IDAFontStyle *fs_1,
            /* [retval][out] */ IDAImage **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StringImage( 
            /* [in] */ BSTR str_0,
            /* [in] */ IDAFontStyle *fs_1,
            /* [retval][out] */ IDAImage **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TextImageAnim( 
            /* [in] */ IDAString *obsoleted1_0,
            /* [in] */ IDAFontStyle *obsoleted2_1,
            /* [retval][out] */ IDAImage **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TextImage( 
            /* [in] */ BSTR obsoleted1_0,
            /* [in] */ IDAFontStyle *obsoleted2_1,
            /* [retval][out] */ IDAImage **ret_2) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_XVector2( 
            /* [retval][out] */ IDAVector2 **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_YVector2( 
            /* [retval][out] */ IDAVector2 **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ZeroVector2( 
            /* [retval][out] */ IDAVector2 **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Origin2( 
            /* [retval][out] */ IDAPoint2 **ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Vector2Anim( 
            /* [in] */ IDANumber *x_0,
            /* [in] */ IDANumber *y_1,
            /* [retval][out] */ IDAVector2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Vector2( 
            /* [in] */ double x_0,
            /* [in] */ double y_1,
            /* [retval][out] */ IDAVector2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Point2Anim( 
            /* [in] */ IDANumber *x_0,
            /* [in] */ IDANumber *y_1,
            /* [retval][out] */ IDAPoint2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Point2( 
            /* [in] */ double x_0,
            /* [in] */ double y_1,
            /* [retval][out] */ IDAPoint2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Vector2PolarAnim( 
            /* [in] */ IDANumber *theta_0,
            /* [in] */ IDANumber *radius_1,
            /* [retval][out] */ IDAVector2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Vector2Polar( 
            /* [in] */ double theta_0,
            /* [in] */ double radius_1,
            /* [retval][out] */ IDAVector2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Vector2PolarDegrees( 
            /* [in] */ double theta_0,
            /* [in] */ double radius_1,
            /* [retval][out] */ IDAVector2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Point2PolarAnim( 
            /* [in] */ IDANumber *theta_0,
            /* [in] */ IDANumber *radius_1,
            /* [retval][out] */ IDAPoint2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Point2Polar( 
            /* [in] */ double theta_0,
            /* [in] */ double radius_1,
            /* [retval][out] */ IDAPoint2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DotVector2( 
            /* [in] */ IDAVector2 *v_0,
            /* [in] */ IDAVector2 *u_1,
            /* [retval][out] */ IDANumber **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NegVector2( 
            /* [in] */ IDAVector2 *v_0,
            /* [retval][out] */ IDAVector2 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SubVector2( 
            /* [in] */ IDAVector2 *v1_0,
            /* [in] */ IDAVector2 *v2_1,
            /* [retval][out] */ IDAVector2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddVector2( 
            /* [in] */ IDAVector2 *v1_0,
            /* [in] */ IDAVector2 *v2_1,
            /* [retval][out] */ IDAVector2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddPoint2Vector( 
            /* [in] */ IDAPoint2 *p_0,
            /* [in] */ IDAVector2 *v_1,
            /* [retval][out] */ IDAPoint2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SubPoint2Vector( 
            /* [in] */ IDAPoint2 *p_0,
            /* [in] */ IDAVector2 *v_1,
            /* [retval][out] */ IDAPoint2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SubPoint2( 
            /* [in] */ IDAPoint2 *p1_0,
            /* [in] */ IDAPoint2 *p2_1,
            /* [retval][out] */ IDAVector2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DistancePoint2( 
            /* [in] */ IDAPoint2 *p_0,
            /* [in] */ IDAPoint2 *q_1,
            /* [retval][out] */ IDANumber **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DistanceSquaredPoint2( 
            /* [in] */ IDAPoint2 *p_0,
            /* [in] */ IDAPoint2 *q_1,
            /* [retval][out] */ IDANumber **ret_2) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_XVector3( 
            /* [retval][out] */ IDAVector3 **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_YVector3( 
            /* [retval][out] */ IDAVector3 **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ZVector3( 
            /* [retval][out] */ IDAVector3 **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ZeroVector3( 
            /* [retval][out] */ IDAVector3 **ret_0) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Origin3( 
            /* [retval][out] */ IDAPoint3 **ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Vector3Anim( 
            /* [in] */ IDANumber *x_0,
            /* [in] */ IDANumber *y_1,
            /* [in] */ IDANumber *z_2,
            /* [retval][out] */ IDAVector3 **ret_3) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Vector3( 
            /* [in] */ double x_0,
            /* [in] */ double y_1,
            /* [in] */ double z_2,
            /* [retval][out] */ IDAVector3 **ret_3) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Point3Anim( 
            /* [in] */ IDANumber *x_0,
            /* [in] */ IDANumber *y_1,
            /* [in] */ IDANumber *z_2,
            /* [retval][out] */ IDAPoint3 **ret_3) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Point3( 
            /* [in] */ double x_0,
            /* [in] */ double y_1,
            /* [in] */ double z_2,
            /* [retval][out] */ IDAPoint3 **ret_3) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Vector3SphericalAnim( 
            /* [in] */ IDANumber *xyAngle_0,
            /* [in] */ IDANumber *yzAngle_1,
            /* [in] */ IDANumber *radius_2,
            /* [retval][out] */ IDAVector3 **ret_3) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Vector3Spherical( 
            /* [in] */ double xyAngle_0,
            /* [in] */ double yzAngle_1,
            /* [in] */ double radius_2,
            /* [retval][out] */ IDAVector3 **ret_3) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Point3SphericalAnim( 
            /* [in] */ IDANumber *zxAngle_0,
            /* [in] */ IDANumber *xyAngle_1,
            /* [in] */ IDANumber *radius_2,
            /* [retval][out] */ IDAPoint3 **ret_3) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Point3Spherical( 
            /* [in] */ double zxAngle_0,
            /* [in] */ double xyAngle_1,
            /* [in] */ double radius_2,
            /* [retval][out] */ IDAPoint3 **ret_3) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DotVector3( 
            /* [in] */ IDAVector3 *v_0,
            /* [in] */ IDAVector3 *u_1,
            /* [retval][out] */ IDANumber **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CrossVector3( 
            /* [in] */ IDAVector3 *v_0,
            /* [in] */ IDAVector3 *u_1,
            /* [retval][out] */ IDAVector3 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NegVector3( 
            /* [in] */ IDAVector3 *v_0,
            /* [retval][out] */ IDAVector3 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SubVector3( 
            /* [in] */ IDAVector3 *v1_0,
            /* [in] */ IDAVector3 *v2_1,
            /* [retval][out] */ IDAVector3 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddVector3( 
            /* [in] */ IDAVector3 *v1_0,
            /* [in] */ IDAVector3 *v2_1,
            /* [retval][out] */ IDAVector3 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddPoint3Vector( 
            /* [in] */ IDAPoint3 *p_0,
            /* [in] */ IDAVector3 *v_1,
            /* [retval][out] */ IDAPoint3 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SubPoint3Vector( 
            /* [in] */ IDAPoint3 *p_0,
            /* [in] */ IDAVector3 *v_1,
            /* [retval][out] */ IDAPoint3 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SubPoint3( 
            /* [in] */ IDAPoint3 *p1_0,
            /* [in] */ IDAPoint3 *p2_1,
            /* [retval][out] */ IDAVector3 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DistancePoint3( 
            /* [in] */ IDAPoint3 *p_0,
            /* [in] */ IDAPoint3 *q_1,
            /* [retval][out] */ IDANumber **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DistanceSquaredPoint3( 
            /* [in] */ IDAPoint3 *p_0,
            /* [in] */ IDAPoint3 *q_1,
            /* [retval][out] */ IDANumber **ret_2) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_IdentityTransform3( 
            /* [retval][out] */ IDATransform3 **ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Translate3Anim( 
            /* [in] */ IDANumber *tx_0,
            /* [in] */ IDANumber *ty_1,
            /* [in] */ IDANumber *tz_2,
            /* [retval][out] */ IDATransform3 **ret_3) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Translate3( 
            /* [in] */ double tx_0,
            /* [in] */ double ty_1,
            /* [in] */ double tz_2,
            /* [retval][out] */ IDATransform3 **ret_3) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Translate3Rate( 
            /* [in] */ double tx_0,
            /* [in] */ double ty_1,
            /* [in] */ double tz_2,
            /* [retval][out] */ IDATransform3 **ret_3) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Translate3Vector( 
            /* [in] */ IDAVector3 *delta_0,
            /* [retval][out] */ IDATransform3 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Translate3Point( 
            /* [in] */ IDAPoint3 *new_origin_0,
            /* [retval][out] */ IDATransform3 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Scale3Anim( 
            /* [in] */ IDANumber *x_0,
            /* [in] */ IDANumber *y_1,
            /* [in] */ IDANumber *z_2,
            /* [retval][out] */ IDATransform3 **ret_3) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Scale3( 
            /* [in] */ double x_0,
            /* [in] */ double y_1,
            /* [in] */ double z_2,
            /* [retval][out] */ IDATransform3 **ret_3) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Scale3Rate( 
            /* [in] */ double x_0,
            /* [in] */ double y_1,
            /* [in] */ double z_2,
            /* [retval][out] */ IDATransform3 **ret_3) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Scale3Vector( 
            /* [in] */ IDAVector3 *scale_vec_0,
            /* [retval][out] */ IDATransform3 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Scale3UniformAnim( 
            /* [in] */ IDANumber *uniform_scale_0,
            /* [retval][out] */ IDATransform3 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Scale3Uniform( 
            /* [in] */ double uniform_scale_0,
            /* [retval][out] */ IDATransform3 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Scale3UniformRate( 
            /* [in] */ double uniform_scale_0,
            /* [retval][out] */ IDATransform3 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Rotate3Anim( 
            /* [in] */ IDAVector3 *axis_0,
            /* [in] */ IDANumber *angle_1,
            /* [retval][out] */ IDATransform3 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Rotate3( 
            /* [in] */ IDAVector3 *axis_0,
            /* [in] */ double angle_1,
            /* [retval][out] */ IDATransform3 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Rotate3Rate( 
            /* [in] */ IDAVector3 *axis_0,
            /* [in] */ double angle_1,
            /* [retval][out] */ IDATransform3 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Rotate3Degrees( 
            /* [in] */ IDAVector3 *axis_0,
            /* [in] */ double angle_1,
            /* [retval][out] */ IDATransform3 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Rotate3RateDegrees( 
            /* [in] */ IDAVector3 *axis_0,
            /* [in] */ double angle_1,
            /* [retval][out] */ IDATransform3 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE XShear3Anim( 
            /* [in] */ IDANumber *a_0,
            /* [in] */ IDANumber *b_1,
            /* [retval][out] */ IDATransform3 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE XShear3( 
            /* [in] */ double a_0,
            /* [in] */ double b_1,
            /* [retval][out] */ IDATransform3 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE XShear3Rate( 
            /* [in] */ double a_0,
            /* [in] */ double b_1,
            /* [retval][out] */ IDATransform3 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE YShear3Anim( 
            /* [in] */ IDANumber *c_0,
            /* [in] */ IDANumber *d_1,
            /* [retval][out] */ IDATransform3 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE YShear3( 
            /* [in] */ double c_0,
            /* [in] */ double d_1,
            /* [retval][out] */ IDATransform3 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE YShear3Rate( 
            /* [in] */ double c_0,
            /* [in] */ double d_1,
            /* [retval][out] */ IDATransform3 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ZShear3Anim( 
            /* [in] */ IDANumber *e_0,
            /* [in] */ IDANumber *f_1,
            /* [retval][out] */ IDATransform3 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ZShear3( 
            /* [in] */ double e_0,
            /* [in] */ double f_1,
            /* [retval][out] */ IDATransform3 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ZShear3Rate( 
            /* [in] */ double e_0,
            /* [in] */ double f_1,
            /* [retval][out] */ IDATransform3 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Transform4x4AnimEx( 
            /* [in] */ LONG m_0size,
            /* [size_is][in] */ IDANumber *m_0[  ],
            /* [retval][out] */ IDATransform3 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Transform4x4Anim( 
            /* [in] */ VARIANT m_0,
            /* [retval][out] */ IDATransform3 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Compose3( 
            /* [in] */ IDATransform3 *a_0,
            /* [in] */ IDATransform3 *b_1,
            /* [retval][out] */ IDATransform3 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Compose3ArrayEx( 
            /* [in] */ LONG xfs_0size,
            /* [size_is][in] */ IDATransform3 *xfs_0[  ],
            /* [retval][out] */ IDATransform3 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Compose3Array( 
            /* [in] */ VARIANT xfs_0,
            /* [retval][out] */ IDATransform3 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LookAtFrom( 
            /* [in] */ IDAPoint3 *to_0,
            /* [in] */ IDAPoint3 *from_1,
            /* [in] */ IDAVector3 *up_2,
            /* [retval][out] */ IDATransform3 **ret_3) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_IdentityTransform2( 
            /* [retval][out] */ IDATransform2 **ret_0) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Translate2Anim( 
            /* [in] */ IDANumber *Tx_0,
            /* [in] */ IDANumber *Ty_1,
            /* [retval][out] */ IDATransform2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Translate2( 
            /* [in] */ double Tx_0,
            /* [in] */ double Ty_1,
            /* [retval][out] */ IDATransform2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Translate2Rate( 
            /* [in] */ double Tx_0,
            /* [in] */ double Ty_1,
            /* [retval][out] */ IDATransform2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Translate2Vector( 
            /* [in] */ IDAVector2 *delta_0,
            /* [retval][out] */ IDATransform2 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Translate2Point( 
            /* [in] */ IDAPoint2 *pos_0,
            /* [retval][out] */ IDATransform2 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Scale2Anim( 
            /* [in] */ IDANumber *x_0,
            /* [in] */ IDANumber *y_1,
            /* [retval][out] */ IDATransform2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Scale2( 
            /* [in] */ double x_0,
            /* [in] */ double y_1,
            /* [retval][out] */ IDATransform2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Scale2Rate( 
            /* [in] */ double x_0,
            /* [in] */ double y_1,
            /* [retval][out] */ IDATransform2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Scale2Vector2( 
            /* [in] */ IDAVector2 *obsoleteMethod_0,
            /* [retval][out] */ IDATransform2 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Scale2Vector( 
            /* [in] */ IDAVector2 *scale_vec_0,
            /* [retval][out] */ IDATransform2 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Scale2UniformAnim( 
            /* [in] */ IDANumber *uniform_scale_0,
            /* [retval][out] */ IDATransform2 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Scale2Uniform( 
            /* [in] */ double uniform_scale_0,
            /* [retval][out] */ IDATransform2 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Scale2UniformRate( 
            /* [in] */ double uniform_scale_0,
            /* [retval][out] */ IDATransform2 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Rotate2Anim( 
            /* [in] */ IDANumber *angle_0,
            /* [retval][out] */ IDATransform2 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Rotate2( 
            /* [in] */ double angle_0,
            /* [retval][out] */ IDATransform2 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Rotate2Rate( 
            /* [in] */ double angle_0,
            /* [retval][out] */ IDATransform2 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Rotate2Degrees( 
            /* [in] */ double angle_0,
            /* [retval][out] */ IDATransform2 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Rotate2RateDegrees( 
            /* [in] */ double angle_0,
            /* [retval][out] */ IDATransform2 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE XShear2Anim( 
            /* [in] */ IDANumber *arg_0,
            /* [retval][out] */ IDATransform2 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE XShear2( 
            /* [in] */ double arg_0,
            /* [retval][out] */ IDATransform2 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE XShear2Rate( 
            /* [in] */ double arg_0,
            /* [retval][out] */ IDATransform2 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE YShear2Anim( 
            /* [in] */ IDANumber *arg_0,
            /* [retval][out] */ IDATransform2 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE YShear2( 
            /* [in] */ double arg_0,
            /* [retval][out] */ IDATransform2 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE YShear2Rate( 
            /* [in] */ double arg_0,
            /* [retval][out] */ IDATransform2 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Transform3x2AnimEx( 
            /* [in] */ LONG m_0size,
            /* [size_is][in] */ IDANumber *m_0[  ],
            /* [retval][out] */ IDATransform2 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Transform3x2Anim( 
            /* [in] */ VARIANT m_0,
            /* [retval][out] */ IDATransform2 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Compose2( 
            /* [in] */ IDATransform2 *a_0,
            /* [in] */ IDATransform2 *b_1,
            /* [retval][out] */ IDATransform2 **ret_2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Compose2ArrayEx( 
            /* [in] */ LONG xfs_0size,
            /* [size_is][in] */ IDATransform2 *xfs_0[  ],
            /* [retval][out] */ IDATransform2 **ret_1) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Compose2Array( 
            /* [in] */ VARIANT xfs_0,
            /* [retval][out] */ IDATransform2 **ret_1) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Tuple( 
            /* [in] */ VARIANT obsolete1,
            /* [retval][out] */ IDATuple **obsolete2) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Array( 
            /* [in] */ VARIANT obsolete1,
            /* [retval][out] */ IDAArray **obsolete2) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_AreBlockingImportsComplete( 
            /* [retval][out] */ VARIANT_BOOL *bComplete) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDAStaticsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDAStatics * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDAStatics * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDAStatics * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDAStatics * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDAStatics * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDAStatics * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDAStatics * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_VersionString )( 
            IDAStatics * This,
            /* [retval][out] */ BSTR *str);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Site )( 
            IDAStatics * This,
            /* [retval][out] */ IDASite **pSite);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Site )( 
            IDAStatics * This,
            /* [in] */ IDASite *pSite);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_ClientSite )( 
            IDAStatics * This,
            /* [in] */ IOleClientSite *pClientSite);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ClientSite )( 
            IDAStatics * This,
            /* [retval][out] */ IOleClientSite **pClientSite);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_PixelConstructionMode )( 
            IDAStatics * This,
            /* [in] */ VARIANT_BOOL bMode);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_PixelConstructionMode )( 
            IDAStatics * This,
            /* [retval][out] */ VARIANT_BOOL *bMode);
        
        HRESULT ( STDMETHODCALLTYPE *TriggerEvent )( 
            IDAStatics * This,
            /* [in] */ IDAEvent *event,
            /* [in] */ IDABehavior *data);
        
        HRESULT ( STDMETHODCALLTYPE *NewDrawingSurface )( 
            IDAStatics * This,
            /* [retval][out] */ IDADrawingSurface **pds);
        
        HRESULT ( STDMETHODCALLTYPE *ImportMovie )( 
            IDAStatics * This,
            /* [in] */ BSTR url,
            /* [retval][out] */ IDAImportationResult **ppResult);
        
        HRESULT ( STDMETHODCALLTYPE *ImportMovieAsync )( 
            IDAStatics * This,
            /* [in] */ BSTR url,
            /* [in] */ IDAImage *pImageStandIn,
            /* [in] */ IDASound *pSoundStandIn,
            /* [retval][out] */ IDAImportationResult **ppResult);
        
        HRESULT ( STDMETHODCALLTYPE *ImportImage )( 
            IDAStatics * This,
            /* [in] */ BSTR url,
            /* [retval][out] */ IDAImage **ppImage);
        
        HRESULT ( STDMETHODCALLTYPE *ImportImageAsync )( 
            IDAStatics * This,
            /* [in] */ BSTR url,
            /* [in] */ IDAImage *pImageStandIn,
            /* [retval][out] */ IDAImportationResult **ppResult);
        
        HRESULT ( STDMETHODCALLTYPE *ImportImageColorKey )( 
            IDAStatics * This,
            /* [in] */ BSTR url,
            /* [in] */ BYTE colorKeyRed,
            /* [in] */ BYTE colorKeyGreen,
            /* [in] */ BYTE colorKeyBlue,
            /* [retval][out] */ IDAImage **ppImage);
        
        HRESULT ( STDMETHODCALLTYPE *ImportImageAsyncColorKey )( 
            IDAStatics * This,
            /* [in] */ BSTR url,
            /* [in] */ IDAImage *pImageStandIn,
            /* [in] */ BYTE colorKeyRed,
            /* [in] */ BYTE colorKeyGreen,
            /* [in] */ BYTE colorKeyBlue,
            /* [retval][out] */ IDAImportationResult **ppResult);
        
        HRESULT ( STDMETHODCALLTYPE *ImportSound )( 
            IDAStatics * This,
            /* [in] */ BSTR url,
            /* [retval][out] */ IDAImportationResult **ppResult);
        
        HRESULT ( STDMETHODCALLTYPE *ImportSoundAsync )( 
            IDAStatics * This,
            /* [in] */ BSTR url,
            /* [in] */ IDASound *pSoundStandIn,
            /* [retval][out] */ IDAImportationResult **ppResult);
        
        HRESULT ( STDMETHODCALLTYPE *ImportGeometry )( 
            IDAStatics * This,
            /* [in] */ BSTR url,
            /* [retval][out] */ IDAGeometry **ppGeometry);
        
        HRESULT ( STDMETHODCALLTYPE *ImportGeometryAsync )( 
            IDAStatics * This,
            /* [in] */ BSTR url,
            /* [in] */ IDAGeometry *pGeoStandIn,
            /* [retval][out] */ IDAImportationResult **ppResult);
        
        HRESULT ( STDMETHODCALLTYPE *ImportDirectDrawSurface )( 
            IDAStatics * This,
            /* [in] */ IUnknown *dds,
            /* [in] */ IDAEvent *updateEvent,
            /* [retval][out] */ IDAImage **ppImage);
        
        HRESULT ( STDMETHODCALLTYPE *Cond )( 
            IDAStatics * This,
            /* [in] */ IDABoolean *c,
            /* [in] */ IDABehavior *i,
            /* [in] */ IDABehavior *e,
            /* [retval][out] */ IDABehavior **pCondBvr);
        
        HRESULT ( STDMETHODCALLTYPE *DAArrayEx )( 
            IDAStatics * This,
            /* [in] */ LONG s,
            /* [size_is][in] */ IDABehavior *pBvrs[  ],
            /* [retval][out] */ IDAArray **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *DAArray )( 
            IDAStatics * This,
            /* [in] */ VARIANT bvrs,
            /* [retval][out] */ IDAArray **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *DATupleEx )( 
            IDAStatics * This,
            /* [in] */ LONG s,
            /* [size_is][in] */ IDABehavior *pBvrs[  ],
            /* [retval][out] */ IDATuple **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *DATuple )( 
            IDAStatics * This,
            /* [in] */ VARIANT bvrs,
            /* [retval][out] */ IDATuple **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *ModifiableBehavior )( 
            IDAStatics * This,
            /* [in] */ IDABehavior *orig,
            /* [retval][out] */ IDABehavior **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *UninitializedArray )( 
            IDAStatics * This,
            /* [in] */ IDAArray *typeTmp,
            /* [retval][out] */ IDAArray **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *UninitializedTuple )( 
            IDAStatics * This,
            /* [in] */ IDATuple *typeTmp,
            /* [retval][out] */ IDATuple **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *NumberBSplineEx )( 
            IDAStatics * This,
            /* [in] */ int degree,
            /* [in] */ LONG numKnots,
            /* [size_is][in] */ IDANumber *knots[  ],
            /* [in] */ LONG numPts,
            /* [size_is][in] */ IDANumber *ctrlPts[  ],
            /* [in] */ LONG numWts,
            /* [size_is][in] */ IDANumber *weights[  ],
            /* [in] */ IDANumber *evaluator,
            /* [retval][out] */ IDANumber **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *NumberBSpline )( 
            IDAStatics * This,
            /* [in] */ int degree,
            /* [in] */ VARIANT knots,
            /* [in] */ VARIANT CtrlPts,
            /* [in] */ VARIANT weights,
            /* [in] */ IDANumber *evaluator,
            /* [retval][out] */ IDANumber **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Point2BSplineEx )( 
            IDAStatics * This,
            /* [in] */ int degree,
            /* [in] */ LONG numKnots,
            /* [size_is][in] */ IDANumber *knots[  ],
            /* [in] */ LONG numPts,
            /* [size_is][in] */ IDAPoint2 *ctrlPts[  ],
            /* [in] */ LONG numWts,
            /* [size_is][in] */ IDANumber *weights[  ],
            /* [in] */ IDANumber *evaluator,
            /* [retval][out] */ IDAPoint2 **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Point2BSpline )( 
            IDAStatics * This,
            /* [in] */ int degree,
            /* [in] */ VARIANT knots,
            /* [in] */ VARIANT CtrlPts,
            /* [in] */ VARIANT weights,
            /* [in] */ IDANumber *evaluator,
            /* [retval][out] */ IDAPoint2 **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Point3BSplineEx )( 
            IDAStatics * This,
            /* [in] */ int degree,
            /* [in] */ LONG numKnots,
            /* [size_is][in] */ IDANumber *knots[  ],
            /* [in] */ LONG numPts,
            /* [size_is][in] */ IDAPoint3 *ctrlPts[  ],
            /* [in] */ LONG numWts,
            /* [size_is][in] */ IDANumber *weights[  ],
            /* [in] */ IDANumber *evaluator,
            /* [retval][out] */ IDAPoint3 **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Point3BSpline )( 
            IDAStatics * This,
            /* [in] */ int degree,
            /* [in] */ VARIANT knots,
            /* [in] */ VARIANT CtrlPts,
            /* [in] */ VARIANT weights,
            /* [in] */ IDANumber *evaluator,
            /* [retval][out] */ IDAPoint3 **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Vector2BSplineEx )( 
            IDAStatics * This,
            /* [in] */ int degree,
            /* [in] */ LONG numKnots,
            /* [size_is][in] */ IDANumber *knots[  ],
            /* [in] */ LONG numPts,
            /* [size_is][in] */ IDAVector2 *ctrlPts[  ],
            /* [in] */ LONG numWts,
            /* [size_is][in] */ IDANumber *weights[  ],
            /* [in] */ IDANumber *evaluator,
            /* [retval][out] */ IDAVector2 **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Vector2BSpline )( 
            IDAStatics * This,
            /* [in] */ int degree,
            /* [in] */ VARIANT knots,
            /* [in] */ VARIANT CtrlPts,
            /* [in] */ VARIANT weights,
            /* [in] */ IDANumber *evaluator,
            /* [retval][out] */ IDAVector2 **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Vector3BSplineEx )( 
            IDAStatics * This,
            /* [in] */ int degree,
            /* [in] */ LONG numKnots,
            /* [size_is][in] */ IDANumber *knots[  ],
            /* [in] */ LONG numPts,
            /* [size_is][in] */ IDAVector3 *ctrlPts[  ],
            /* [in] */ LONG numWts,
            /* [size_is][in] */ IDANumber *weights[  ],
            /* [in] */ IDANumber *evaluator,
            /* [retval][out] */ IDAVector3 **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Vector3BSpline )( 
            IDAStatics * This,
            /* [in] */ int degree,
            /* [in] */ VARIANT knots,
            /* [in] */ VARIANT CtrlPts,
            /* [in] */ VARIANT weights,
            /* [in] */ IDANumber *evaluator,
            /* [retval][out] */ IDAVector3 **bvr);
        
        HRESULT ( STDMETHODCALLTYPE *Pow )( 
            IDAStatics * This,
            /* [in] */ IDANumber *a_0,
            /* [in] */ IDANumber *b_1,
            /* [retval][out] */ IDANumber **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *Abs )( 
            IDAStatics * This,
            /* [in] */ IDANumber *a_0,
            /* [retval][out] */ IDANumber **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Sqrt )( 
            IDAStatics * This,
            /* [in] */ IDANumber *a_0,
            /* [retval][out] */ IDANumber **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Floor )( 
            IDAStatics * This,
            /* [in] */ IDANumber *a_0,
            /* [retval][out] */ IDANumber **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Round )( 
            IDAStatics * This,
            /* [in] */ IDANumber *a_0,
            /* [retval][out] */ IDANumber **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Ceiling )( 
            IDAStatics * This,
            /* [in] */ IDANumber *a_0,
            /* [retval][out] */ IDANumber **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Asin )( 
            IDAStatics * This,
            /* [in] */ IDANumber *a_0,
            /* [retval][out] */ IDANumber **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Acos )( 
            IDAStatics * This,
            /* [in] */ IDANumber *a_0,
            /* [retval][out] */ IDANumber **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Atan )( 
            IDAStatics * This,
            /* [in] */ IDANumber *a_0,
            /* [retval][out] */ IDANumber **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Sin )( 
            IDAStatics * This,
            /* [in] */ IDANumber *a_0,
            /* [retval][out] */ IDANumber **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Cos )( 
            IDAStatics * This,
            /* [in] */ IDANumber *a_0,
            /* [retval][out] */ IDANumber **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Tan )( 
            IDAStatics * This,
            /* [in] */ IDANumber *a_0,
            /* [retval][out] */ IDANumber **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Exp )( 
            IDAStatics * This,
            /* [in] */ IDANumber *a_0,
            /* [retval][out] */ IDANumber **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Ln )( 
            IDAStatics * This,
            /* [in] */ IDANumber *a_0,
            /* [retval][out] */ IDANumber **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Log10 )( 
            IDAStatics * This,
            /* [in] */ IDANumber *a_0,
            /* [retval][out] */ IDANumber **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *ToDegrees )( 
            IDAStatics * This,
            /* [in] */ IDANumber *a_0,
            /* [retval][out] */ IDANumber **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *ToRadians )( 
            IDAStatics * This,
            /* [in] */ IDANumber *a_0,
            /* [retval][out] */ IDANumber **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Mod )( 
            IDAStatics * This,
            /* [in] */ IDANumber *a_0,
            /* [in] */ IDANumber *b_1,
            /* [retval][out] */ IDANumber **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *Atan2 )( 
            IDAStatics * This,
            /* [in] */ IDANumber *a_0,
            /* [in] */ IDANumber *b_1,
            /* [retval][out] */ IDANumber **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *Add )( 
            IDAStatics * This,
            /* [in] */ IDANumber *a_0,
            /* [in] */ IDANumber *b_1,
            /* [retval][out] */ IDANumber **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *Sub )( 
            IDAStatics * This,
            /* [in] */ IDANumber *a_0,
            /* [in] */ IDANumber *b_1,
            /* [retval][out] */ IDANumber **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *Mul )( 
            IDAStatics * This,
            /* [in] */ IDANumber *a_0,
            /* [in] */ IDANumber *b_1,
            /* [retval][out] */ IDANumber **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *Div )( 
            IDAStatics * This,
            /* [in] */ IDANumber *a_0,
            /* [in] */ IDANumber *b_1,
            /* [retval][out] */ IDANumber **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *LT )( 
            IDAStatics * This,
            /* [in] */ IDANumber *a_0,
            /* [in] */ IDANumber *b_1,
            /* [retval][out] */ IDABoolean **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *LTE )( 
            IDAStatics * This,
            /* [in] */ IDANumber *a_0,
            /* [in] */ IDANumber *b_1,
            /* [retval][out] */ IDABoolean **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *GT )( 
            IDAStatics * This,
            /* [in] */ IDANumber *a_0,
            /* [in] */ IDANumber *b_1,
            /* [retval][out] */ IDABoolean **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *GTE )( 
            IDAStatics * This,
            /* [in] */ IDANumber *a_0,
            /* [in] */ IDANumber *b_1,
            /* [retval][out] */ IDABoolean **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *EQ )( 
            IDAStatics * This,
            /* [in] */ IDANumber *a_0,
            /* [in] */ IDANumber *b_1,
            /* [retval][out] */ IDABoolean **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *NE )( 
            IDAStatics * This,
            /* [in] */ IDANumber *a_0,
            /* [in] */ IDANumber *b_1,
            /* [retval][out] */ IDABoolean **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *Neg )( 
            IDAStatics * This,
            /* [in] */ IDANumber *a_0,
            /* [retval][out] */ IDANumber **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *InterpolateAnim )( 
            IDAStatics * This,
            /* [in] */ IDANumber *from_0,
            /* [in] */ IDANumber *to_1,
            /* [in] */ IDANumber *duration_2,
            /* [retval][out] */ IDANumber **ret_3);
        
        HRESULT ( STDMETHODCALLTYPE *Interpolate )( 
            IDAStatics * This,
            /* [in] */ double from_0,
            /* [in] */ double to_1,
            /* [in] */ double duration_2,
            /* [retval][out] */ IDANumber **ret_3);
        
        HRESULT ( STDMETHODCALLTYPE *SlowInSlowOutAnim )( 
            IDAStatics * This,
            /* [in] */ IDANumber *from_0,
            /* [in] */ IDANumber *to_1,
            /* [in] */ IDANumber *duration_2,
            /* [in] */ IDANumber *sharpness_3,
            /* [retval][out] */ IDANumber **ret_4);
        
        HRESULT ( STDMETHODCALLTYPE *SlowInSlowOut )( 
            IDAStatics * This,
            /* [in] */ double from_0,
            /* [in] */ double to_1,
            /* [in] */ double duration_2,
            /* [in] */ double sharpness_3,
            /* [retval][out] */ IDANumber **ret_4);
        
        HRESULT ( STDMETHODCALLTYPE *SoundSource )( 
            IDAStatics * This,
            /* [in] */ IDASound *snd_0,
            /* [retval][out] */ IDAGeometry **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Mix )( 
            IDAStatics * This,
            /* [in] */ IDASound *left_0,
            /* [in] */ IDASound *right_1,
            /* [retval][out] */ IDASound **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *And )( 
            IDAStatics * This,
            /* [in] */ IDABoolean *a_0,
            /* [in] */ IDABoolean *b_1,
            /* [retval][out] */ IDABoolean **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *Or )( 
            IDAStatics * This,
            /* [in] */ IDABoolean *a_0,
            /* [in] */ IDABoolean *b_1,
            /* [retval][out] */ IDABoolean **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *Not )( 
            IDAStatics * This,
            /* [in] */ IDABoolean *a_0,
            /* [retval][out] */ IDABoolean **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Integral )( 
            IDAStatics * This,
            /* [in] */ IDANumber *b_0,
            /* [retval][out] */ IDANumber **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Derivative )( 
            IDAStatics * This,
            /* [in] */ IDANumber *b_0,
            /* [retval][out] */ IDANumber **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *IntegralVector2 )( 
            IDAStatics * This,
            /* [in] */ IDAVector2 *v_0,
            /* [retval][out] */ IDAVector2 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *IntegralVector3 )( 
            IDAStatics * This,
            /* [in] */ IDAVector3 *v_0,
            /* [retval][out] */ IDAVector3 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *DerivativeVector2 )( 
            IDAStatics * This,
            /* [in] */ IDAVector2 *v_0,
            /* [retval][out] */ IDAVector2 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *DerivativeVector3 )( 
            IDAStatics * This,
            /* [in] */ IDAVector3 *v_0,
            /* [retval][out] */ IDAVector3 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *DerivativePoint2 )( 
            IDAStatics * This,
            /* [in] */ IDAPoint2 *v_0,
            /* [retval][out] */ IDAVector2 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *DerivativePoint3 )( 
            IDAStatics * This,
            /* [in] */ IDAPoint3 *v_0,
            /* [retval][out] */ IDAVector3 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *KeyState )( 
            IDAStatics * This,
            /* [in] */ IDANumber *n_0,
            /* [retval][out] */ IDABoolean **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *KeyUp )( 
            IDAStatics * This,
            /* [in] */ LONG arg_0,
            /* [retval][out] */ IDAEvent **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *KeyDown )( 
            IDAStatics * This,
            /* [in] */ LONG arg_0,
            /* [retval][out] */ IDAEvent **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *DANumber )( 
            IDAStatics * This,
            /* [in] */ double num_0,
            /* [retval][out] */ IDANumber **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *DAString )( 
            IDAStatics * This,
            /* [in] */ BSTR str_0,
            /* [retval][out] */ IDAString **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *DABoolean )( 
            IDAStatics * This,
            /* [in] */ VARIANT_BOOL num_0,
            /* [retval][out] */ IDABoolean **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *SeededRandom )( 
            IDAStatics * This,
            /* [in] */ double arg_0,
            /* [retval][out] */ IDANumber **ret_1);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_MousePosition )( 
            IDAStatics * This,
            /* [retval][out] */ IDAPoint2 **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_LeftButtonState )( 
            IDAStatics * This,
            /* [retval][out] */ IDABoolean **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_RightButtonState )( 
            IDAStatics * This,
            /* [retval][out] */ IDABoolean **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_DATrue )( 
            IDAStatics * This,
            /* [retval][out] */ IDABoolean **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_DAFalse )( 
            IDAStatics * This,
            /* [retval][out] */ IDABoolean **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_LocalTime )( 
            IDAStatics * This,
            /* [retval][out] */ IDANumber **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_GlobalTime )( 
            IDAStatics * This,
            /* [retval][out] */ IDANumber **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Pixel )( 
            IDAStatics * This,
            /* [retval][out] */ IDANumber **ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *UserData )( 
            IDAStatics * This,
            /* [in] */ IUnknown *data_0,
            /* [retval][out] */ IDAUserData **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *UntilNotify )( 
            IDAStatics * This,
            /* [in] */ IDABehavior *b0_0,
            /* [in] */ IDAEvent *event_1,
            /* [in] */ IDAUntilNotifier *notifier_2,
            /* [retval][out] */ IDABehavior **ret_3);
        
        HRESULT ( STDMETHODCALLTYPE *Until )( 
            IDAStatics * This,
            /* [in] */ IDABehavior *b0_0,
            /* [in] */ IDAEvent *event_1,
            /* [in] */ IDABehavior *b1_2,
            /* [retval][out] */ IDABehavior **ret_3);
        
        HRESULT ( STDMETHODCALLTYPE *UntilEx )( 
            IDAStatics * This,
            /* [in] */ IDABehavior *b0_0,
            /* [in] */ IDAEvent *event_1,
            /* [retval][out] */ IDABehavior **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *Sequence )( 
            IDAStatics * This,
            /* [in] */ IDABehavior *s1_0,
            /* [in] */ IDABehavior *s2_1,
            /* [retval][out] */ IDABehavior **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *FollowPath )( 
            IDAStatics * This,
            /* [in] */ IDAPath2 *path_0,
            /* [in] */ double duration_1,
            /* [retval][out] */ IDATransform2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *FollowPathAngle )( 
            IDAStatics * This,
            /* [in] */ IDAPath2 *path_0,
            /* [in] */ double duration_1,
            /* [retval][out] */ IDATransform2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *FollowPathAngleUpright )( 
            IDAStatics * This,
            /* [in] */ IDAPath2 *path_0,
            /* [in] */ double duration_1,
            /* [retval][out] */ IDATransform2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *FollowPathEval )( 
            IDAStatics * This,
            /* [in] */ IDAPath2 *path_0,
            /* [in] */ IDANumber *eval_1,
            /* [retval][out] */ IDATransform2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *FollowPathAngleEval )( 
            IDAStatics * This,
            /* [in] */ IDAPath2 *path_0,
            /* [in] */ IDANumber *eval_1,
            /* [retval][out] */ IDATransform2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *FollowPathAngleUprightEval )( 
            IDAStatics * This,
            /* [in] */ IDAPath2 *path_0,
            /* [in] */ IDANumber *eval_1,
            /* [retval][out] */ IDATransform2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *FollowPathAnim )( 
            IDAStatics * This,
            /* [in] */ IDAPath2 *obsoleted1_0,
            /* [in] */ IDANumber *obsoleted2_1,
            /* [retval][out] */ IDATransform2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *FollowPathAngleAnim )( 
            IDAStatics * This,
            /* [in] */ IDAPath2 *obsoleted1_0,
            /* [in] */ IDANumber *obsoleted2_1,
            /* [retval][out] */ IDATransform2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *FollowPathAngleUprightAnim )( 
            IDAStatics * This,
            /* [in] */ IDAPath2 *obsoleted1_0,
            /* [in] */ IDANumber *obsoleted2_1,
            /* [retval][out] */ IDATransform2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *ConcatString )( 
            IDAStatics * This,
            /* [in] */ IDAString *s1_0,
            /* [in] */ IDAString *s2_1,
            /* [retval][out] */ IDAString **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *PerspectiveCamera )( 
            IDAStatics * This,
            /* [in] */ double focalDist_0,
            /* [in] */ double nearClip_1,
            /* [retval][out] */ IDACamera **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *PerspectiveCameraAnim )( 
            IDAStatics * This,
            /* [in] */ IDANumber *focalDist_0,
            /* [in] */ IDANumber *nearClip_1,
            /* [retval][out] */ IDACamera **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *ParallelCamera )( 
            IDAStatics * This,
            /* [in] */ double nearClip_0,
            /* [retval][out] */ IDACamera **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *ParallelCameraAnim )( 
            IDAStatics * This,
            /* [in] */ IDANumber *nearClip_0,
            /* [retval][out] */ IDACamera **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *ColorRgbAnim )( 
            IDAStatics * This,
            /* [in] */ IDANumber *red_0,
            /* [in] */ IDANumber *green_1,
            /* [in] */ IDANumber *blue_2,
            /* [retval][out] */ IDAColor **ret_3);
        
        HRESULT ( STDMETHODCALLTYPE *ColorRgb )( 
            IDAStatics * This,
            /* [in] */ double red_0,
            /* [in] */ double green_1,
            /* [in] */ double blue_2,
            /* [retval][out] */ IDAColor **ret_3);
        
        HRESULT ( STDMETHODCALLTYPE *ColorRgb255 )( 
            IDAStatics * This,
            /* [in] */ short red_0,
            /* [in] */ short green_1,
            /* [in] */ short blue_2,
            /* [retval][out] */ IDAColor **ret_3);
        
        HRESULT ( STDMETHODCALLTYPE *ColorHsl )( 
            IDAStatics * This,
            /* [in] */ double hue_0,
            /* [in] */ double saturation_1,
            /* [in] */ double lum_2,
            /* [retval][out] */ IDAColor **ret_3);
        
        HRESULT ( STDMETHODCALLTYPE *ColorHslAnim )( 
            IDAStatics * This,
            /* [in] */ IDANumber *hue_0,
            /* [in] */ IDANumber *saturation_1,
            /* [in] */ IDANumber *lum_2,
            /* [retval][out] */ IDAColor **ret_3);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Red )( 
            IDAStatics * This,
            /* [retval][out] */ IDAColor **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Green )( 
            IDAStatics * This,
            /* [retval][out] */ IDAColor **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Blue )( 
            IDAStatics * This,
            /* [retval][out] */ IDAColor **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Cyan )( 
            IDAStatics * This,
            /* [retval][out] */ IDAColor **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Magenta )( 
            IDAStatics * This,
            /* [retval][out] */ IDAColor **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Yellow )( 
            IDAStatics * This,
            /* [retval][out] */ IDAColor **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Black )( 
            IDAStatics * This,
            /* [retval][out] */ IDAColor **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_White )( 
            IDAStatics * This,
            /* [retval][out] */ IDAColor **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Aqua )( 
            IDAStatics * This,
            /* [retval][out] */ IDAColor **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Fuchsia )( 
            IDAStatics * This,
            /* [retval][out] */ IDAColor **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Gray )( 
            IDAStatics * This,
            /* [retval][out] */ IDAColor **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Lime )( 
            IDAStatics * This,
            /* [retval][out] */ IDAColor **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Maroon )( 
            IDAStatics * This,
            /* [retval][out] */ IDAColor **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Navy )( 
            IDAStatics * This,
            /* [retval][out] */ IDAColor **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Olive )( 
            IDAStatics * This,
            /* [retval][out] */ IDAColor **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Purple )( 
            IDAStatics * This,
            /* [retval][out] */ IDAColor **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Silver )( 
            IDAStatics * This,
            /* [retval][out] */ IDAColor **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Teal )( 
            IDAStatics * This,
            /* [retval][out] */ IDAColor **ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *Predicate )( 
            IDAStatics * This,
            /* [in] */ IDABoolean *b_0,
            /* [retval][out] */ IDAEvent **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *NotEvent )( 
            IDAStatics * This,
            /* [in] */ IDAEvent *event_0,
            /* [retval][out] */ IDAEvent **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *AndEvent )( 
            IDAStatics * This,
            /* [in] */ IDAEvent *e1_0,
            /* [in] */ IDAEvent *e2_1,
            /* [retval][out] */ IDAEvent **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *OrEvent )( 
            IDAStatics * This,
            /* [in] */ IDAEvent *e1_0,
            /* [in] */ IDAEvent *e2_1,
            /* [retval][out] */ IDAEvent **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *ThenEvent )( 
            IDAStatics * This,
            /* [in] */ IDAEvent *e1_0,
            /* [in] */ IDAEvent *e2_1,
            /* [retval][out] */ IDAEvent **ret_2);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_LeftButtonDown )( 
            IDAStatics * This,
            /* [retval][out] */ IDAEvent **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_LeftButtonUp )( 
            IDAStatics * This,
            /* [retval][out] */ IDAEvent **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_RightButtonDown )( 
            IDAStatics * This,
            /* [retval][out] */ IDAEvent **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_RightButtonUp )( 
            IDAStatics * This,
            /* [retval][out] */ IDAEvent **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Always )( 
            IDAStatics * This,
            /* [retval][out] */ IDAEvent **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Never )( 
            IDAStatics * This,
            /* [retval][out] */ IDAEvent **ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *TimerAnim )( 
            IDAStatics * This,
            /* [in] */ IDANumber *n_0,
            /* [retval][out] */ IDAEvent **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Timer )( 
            IDAStatics * This,
            /* [in] */ double n_0,
            /* [retval][out] */ IDAEvent **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *AppTriggeredEvent )( 
            IDAStatics * This,
            /* [retval][out] */ IDAEvent **ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *ScriptCallback )( 
            IDAStatics * This,
            /* [in] */ BSTR obsolete1_0,
            /* [in] */ IDAEvent *obsolete2_1,
            /* [in] */ BSTR obsolete3_2,
            /* [retval][out] */ IDAEvent **ret_3);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_EmptyGeometry )( 
            IDAStatics * This,
            /* [retval][out] */ IDAGeometry **ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *UnionGeometry )( 
            IDAStatics * This,
            /* [in] */ IDAGeometry *g1_0,
            /* [in] */ IDAGeometry *g2_1,
            /* [retval][out] */ IDAGeometry **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *UnionGeometryArrayEx )( 
            IDAStatics * This,
            /* [in] */ LONG imgs_0size,
            /* [size_is][in] */ IDAGeometry *imgs_0[  ],
            /* [retval][out] */ IDAGeometry **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *UnionGeometryArray )( 
            IDAStatics * This,
            /* [in] */ VARIANT imgs_0,
            /* [retval][out] */ IDAGeometry **ret_1);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_EmptyImage )( 
            IDAStatics * This,
            /* [retval][out] */ IDAImage **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_DetectableEmptyImage )( 
            IDAStatics * This,
            /* [retval][out] */ IDAImage **ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *SolidColorImage )( 
            IDAStatics * This,
            /* [in] */ IDAColor *col_0,
            /* [retval][out] */ IDAImage **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *GradientPolygonEx )( 
            IDAStatics * This,
            /* [in] */ LONG points_0size,
            /* [size_is][in] */ IDAPoint2 *points_0[  ],
            /* [in] */ LONG colors_1size,
            /* [size_is][in] */ IDAColor *colors_1[  ],
            /* [retval][out] */ IDAImage **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *GradientPolygon )( 
            IDAStatics * This,
            /* [in] */ VARIANT points_0,
            /* [in] */ VARIANT colors_1,
            /* [retval][out] */ IDAImage **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *RadialGradientPolygonEx )( 
            IDAStatics * This,
            /* [in] */ IDAColor *inner_0,
            /* [in] */ IDAColor *outer_1,
            /* [in] */ LONG points_2size,
            /* [size_is][in] */ IDAPoint2 *points_2[  ],
            /* [in] */ double fallOff_3,
            /* [retval][out] */ IDAImage **ret_4);
        
        HRESULT ( STDMETHODCALLTYPE *RadialGradientPolygon )( 
            IDAStatics * This,
            /* [in] */ IDAColor *inner_0,
            /* [in] */ IDAColor *outer_1,
            /* [in] */ VARIANT points_2,
            /* [in] */ double fallOff_3,
            /* [retval][out] */ IDAImage **ret_4);
        
        HRESULT ( STDMETHODCALLTYPE *RadialGradientPolygonAnimEx )( 
            IDAStatics * This,
            /* [in] */ IDAColor *inner_0,
            /* [in] */ IDAColor *outer_1,
            /* [in] */ LONG points_2size,
            /* [size_is][in] */ IDAPoint2 *points_2[  ],
            /* [in] */ IDANumber *fallOff_3,
            /* [retval][out] */ IDAImage **ret_4);
        
        HRESULT ( STDMETHODCALLTYPE *RadialGradientPolygonAnim )( 
            IDAStatics * This,
            /* [in] */ IDAColor *inner_0,
            /* [in] */ IDAColor *outer_1,
            /* [in] */ VARIANT points_2,
            /* [in] */ IDANumber *fallOff_3,
            /* [retval][out] */ IDAImage **ret_4);
        
        HRESULT ( STDMETHODCALLTYPE *GradientSquare )( 
            IDAStatics * This,
            /* [in] */ IDAColor *lowerLeft_0,
            /* [in] */ IDAColor *upperLeft_1,
            /* [in] */ IDAColor *upperRight_2,
            /* [in] */ IDAColor *lowerRight_3,
            /* [retval][out] */ IDAImage **ret_4);
        
        HRESULT ( STDMETHODCALLTYPE *RadialGradientSquare )( 
            IDAStatics * This,
            /* [in] */ IDAColor *inner_0,
            /* [in] */ IDAColor *outer_1,
            /* [in] */ double fallOff_2,
            /* [retval][out] */ IDAImage **ret_3);
        
        HRESULT ( STDMETHODCALLTYPE *RadialGradientSquareAnim )( 
            IDAStatics * This,
            /* [in] */ IDAColor *inner_0,
            /* [in] */ IDAColor *outer_1,
            /* [in] */ IDANumber *fallOff_2,
            /* [retval][out] */ IDAImage **ret_3);
        
        HRESULT ( STDMETHODCALLTYPE *RadialGradientRegularPoly )( 
            IDAStatics * This,
            /* [in] */ IDAColor *inner_0,
            /* [in] */ IDAColor *outer_1,
            /* [in] */ double numEdges_2,
            /* [in] */ double fallOff_3,
            /* [retval][out] */ IDAImage **ret_4);
        
        HRESULT ( STDMETHODCALLTYPE *RadialGradientRegularPolyAnim )( 
            IDAStatics * This,
            /* [in] */ IDAColor *inner_0,
            /* [in] */ IDAColor *outer_1,
            /* [in] */ IDANumber *numEdges_2,
            /* [in] */ IDANumber *fallOff_3,
            /* [retval][out] */ IDAImage **ret_4);
        
        HRESULT ( STDMETHODCALLTYPE *GradientHorizontal )( 
            IDAStatics * This,
            /* [in] */ IDAColor *start_0,
            /* [in] */ IDAColor *stop_1,
            /* [in] */ double fallOff_2,
            /* [retval][out] */ IDAImage **ret_3);
        
        HRESULT ( STDMETHODCALLTYPE *GradientHorizontalAnim )( 
            IDAStatics * This,
            /* [in] */ IDAColor *start_0,
            /* [in] */ IDAColor *stop_1,
            /* [in] */ IDANumber *fallOff_2,
            /* [retval][out] */ IDAImage **ret_3);
        
        HRESULT ( STDMETHODCALLTYPE *HatchHorizontal )( 
            IDAStatics * This,
            /* [in] */ IDAColor *lineClr_0,
            /* [in] */ double spacing_1,
            /* [retval][out] */ IDAImage **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *HatchHorizontalAnim )( 
            IDAStatics * This,
            /* [in] */ IDAColor *lineClr_0,
            /* [in] */ IDANumber *spacing_1,
            /* [retval][out] */ IDAImage **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *HatchVertical )( 
            IDAStatics * This,
            /* [in] */ IDAColor *lineClr_0,
            /* [in] */ double spacing_1,
            /* [retval][out] */ IDAImage **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *HatchVerticalAnim )( 
            IDAStatics * This,
            /* [in] */ IDAColor *lineClr_0,
            /* [in] */ IDANumber *spacing_1,
            /* [retval][out] */ IDAImage **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *HatchForwardDiagonal )( 
            IDAStatics * This,
            /* [in] */ IDAColor *lineClr_0,
            /* [in] */ double spacing_1,
            /* [retval][out] */ IDAImage **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *HatchForwardDiagonalAnim )( 
            IDAStatics * This,
            /* [in] */ IDAColor *lineClr_0,
            /* [in] */ IDANumber *spacing_1,
            /* [retval][out] */ IDAImage **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *HatchBackwardDiagonal )( 
            IDAStatics * This,
            /* [in] */ IDAColor *lineClr_0,
            /* [in] */ double spacing_1,
            /* [retval][out] */ IDAImage **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *HatchBackwardDiagonalAnim )( 
            IDAStatics * This,
            /* [in] */ IDAColor *lineClr_0,
            /* [in] */ IDANumber *spacing_1,
            /* [retval][out] */ IDAImage **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *HatchCross )( 
            IDAStatics * This,
            /* [in] */ IDAColor *lineClr_0,
            /* [in] */ double spacing_1,
            /* [retval][out] */ IDAImage **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *HatchCrossAnim )( 
            IDAStatics * This,
            /* [in] */ IDAColor *lineClr_0,
            /* [in] */ IDANumber *spacing_1,
            /* [retval][out] */ IDAImage **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *HatchDiagonalCross )( 
            IDAStatics * This,
            /* [in] */ IDAColor *lineClr_0,
            /* [in] */ double spacing_1,
            /* [retval][out] */ IDAImage **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *HatchDiagonalCrossAnim )( 
            IDAStatics * This,
            /* [in] */ IDAColor *lineClr_0,
            /* [in] */ IDANumber *spacing_1,
            /* [retval][out] */ IDAImage **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *Overlay )( 
            IDAStatics * This,
            /* [in] */ IDAImage *top_0,
            /* [in] */ IDAImage *bottom_1,
            /* [retval][out] */ IDAImage **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *OverlayArrayEx )( 
            IDAStatics * This,
            /* [in] */ LONG imgs_0size,
            /* [size_is][in] */ IDAImage *imgs_0[  ],
            /* [retval][out] */ IDAImage **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *OverlayArray )( 
            IDAStatics * This,
            /* [in] */ VARIANT imgs_0,
            /* [retval][out] */ IDAImage **ret_1);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_AmbientLight )( 
            IDAStatics * This,
            /* [retval][out] */ IDAGeometry **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_DirectionalLight )( 
            IDAStatics * This,
            /* [retval][out] */ IDAGeometry **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_PointLight )( 
            IDAStatics * This,
            /* [retval][out] */ IDAGeometry **ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *SpotLightAnim )( 
            IDAStatics * This,
            /* [in] */ IDANumber *fullcone_0,
            /* [in] */ IDANumber *cutoff_1,
            /* [retval][out] */ IDAGeometry **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *SpotLight )( 
            IDAStatics * This,
            /* [in] */ IDANumber *fullcone_0,
            /* [in] */ double cutoff_1,
            /* [retval][out] */ IDAGeometry **ret_2);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_DefaultLineStyle )( 
            IDAStatics * This,
            /* [retval][out] */ IDALineStyle **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_EmptyLineStyle )( 
            IDAStatics * This,
            /* [retval][out] */ IDALineStyle **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_JoinStyleBevel )( 
            IDAStatics * This,
            /* [retval][out] */ IDAJoinStyle **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_JoinStyleRound )( 
            IDAStatics * This,
            /* [retval][out] */ IDAJoinStyle **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_JoinStyleMiter )( 
            IDAStatics * This,
            /* [retval][out] */ IDAJoinStyle **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndStyleFlat )( 
            IDAStatics * This,
            /* [retval][out] */ IDAEndStyle **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndStyleSquare )( 
            IDAStatics * This,
            /* [retval][out] */ IDAEndStyle **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndStyleRound )( 
            IDAStatics * This,
            /* [retval][out] */ IDAEndStyle **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_DashStyleSolid )( 
            IDAStatics * This,
            /* [retval][out] */ IDADashStyle **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_DashStyleDashed )( 
            IDAStatics * This,
            /* [retval][out] */ IDADashStyle **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_DefaultMicrophone )( 
            IDAStatics * This,
            /* [retval][out] */ IDAMicrophone **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_OpaqueMatte )( 
            IDAStatics * This,
            /* [retval][out] */ IDAMatte **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ClearMatte )( 
            IDAStatics * This,
            /* [retval][out] */ IDAMatte **ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *UnionMatte )( 
            IDAStatics * This,
            /* [in] */ IDAMatte *m1_0,
            /* [in] */ IDAMatte *m2_1,
            /* [retval][out] */ IDAMatte **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *IntersectMatte )( 
            IDAStatics * This,
            /* [in] */ IDAMatte *m1_0,
            /* [in] */ IDAMatte *m2_1,
            /* [retval][out] */ IDAMatte **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *DifferenceMatte )( 
            IDAStatics * This,
            /* [in] */ IDAMatte *m1_0,
            /* [in] */ IDAMatte *m2_1,
            /* [retval][out] */ IDAMatte **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *FillMatte )( 
            IDAStatics * This,
            /* [in] */ IDAPath2 *p_0,
            /* [retval][out] */ IDAMatte **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *TextMatte )( 
            IDAStatics * This,
            /* [in] */ IDAString *str_0,
            /* [in] */ IDAFontStyle *fs_1,
            /* [retval][out] */ IDAMatte **ret_2);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_EmptyMontage )( 
            IDAStatics * This,
            /* [retval][out] */ IDAMontage **ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *ImageMontage )( 
            IDAStatics * This,
            /* [in] */ IDAImage *im_0,
            /* [in] */ double depth_1,
            /* [retval][out] */ IDAMontage **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *ImageMontageAnim )( 
            IDAStatics * This,
            /* [in] */ IDAImage *im_0,
            /* [in] */ IDANumber *depth_1,
            /* [retval][out] */ IDAMontage **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *UnionMontage )( 
            IDAStatics * This,
            /* [in] */ IDAMontage *m1_0,
            /* [in] */ IDAMontage *m2_1,
            /* [retval][out] */ IDAMontage **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *Concat )( 
            IDAStatics * This,
            /* [in] */ IDAPath2 *p1_0,
            /* [in] */ IDAPath2 *p2_1,
            /* [retval][out] */ IDAPath2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *ConcatArrayEx )( 
            IDAStatics * This,
            /* [in] */ LONG paths_0size,
            /* [size_is][in] */ IDAPath2 *paths_0[  ],
            /* [retval][out] */ IDAPath2 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *ConcatArray )( 
            IDAStatics * This,
            /* [in] */ VARIANT paths_0,
            /* [retval][out] */ IDAPath2 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Line )( 
            IDAStatics * This,
            /* [in] */ IDAPoint2 *p1_0,
            /* [in] */ IDAPoint2 *p2_1,
            /* [retval][out] */ IDAPath2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *Ray )( 
            IDAStatics * This,
            /* [in] */ IDAPoint2 *pt_0,
            /* [retval][out] */ IDAPath2 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *StringPathAnim )( 
            IDAStatics * This,
            /* [in] */ IDAString *str_0,
            /* [in] */ IDAFontStyle *fs_1,
            /* [retval][out] */ IDAPath2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *StringPath )( 
            IDAStatics * This,
            /* [in] */ BSTR str_0,
            /* [in] */ IDAFontStyle *fs_1,
            /* [retval][out] */ IDAPath2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *PolylineEx )( 
            IDAStatics * This,
            /* [in] */ LONG points_0size,
            /* [size_is][in] */ IDAPoint2 *points_0[  ],
            /* [retval][out] */ IDAPath2 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Polyline )( 
            IDAStatics * This,
            /* [in] */ VARIANT points_0,
            /* [retval][out] */ IDAPath2 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *PolydrawPathEx )( 
            IDAStatics * This,
            /* [in] */ LONG points_0size,
            /* [size_is][in] */ IDAPoint2 *points_0[  ],
            /* [in] */ LONG codes_1size,
            /* [size_is][in] */ IDANumber *codes_1[  ],
            /* [retval][out] */ IDAPath2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *PolydrawPath )( 
            IDAStatics * This,
            /* [in] */ VARIANT points_0,
            /* [in] */ VARIANT codes_1,
            /* [retval][out] */ IDAPath2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *ArcRadians )( 
            IDAStatics * This,
            /* [in] */ double startAngle_0,
            /* [in] */ double endAngle_1,
            /* [in] */ double arcWidth_2,
            /* [in] */ double arcHeight_3,
            /* [retval][out] */ IDAPath2 **ret_4);
        
        HRESULT ( STDMETHODCALLTYPE *ArcRadiansAnim )( 
            IDAStatics * This,
            /* [in] */ IDANumber *startAngle_0,
            /* [in] */ IDANumber *endAngle_1,
            /* [in] */ IDANumber *arcWidth_2,
            /* [in] */ IDANumber *arcHeight_3,
            /* [retval][out] */ IDAPath2 **ret_4);
        
        HRESULT ( STDMETHODCALLTYPE *ArcDegrees )( 
            IDAStatics * This,
            /* [in] */ double startAngle_0,
            /* [in] */ double endAngle_1,
            /* [in] */ double arcWidth_2,
            /* [in] */ double arcHeight_3,
            /* [retval][out] */ IDAPath2 **ret_4);
        
        HRESULT ( STDMETHODCALLTYPE *PieRadians )( 
            IDAStatics * This,
            /* [in] */ double startAngle_0,
            /* [in] */ double endAngle_1,
            /* [in] */ double arcWidth_2,
            /* [in] */ double arcHeight_3,
            /* [retval][out] */ IDAPath2 **ret_4);
        
        HRESULT ( STDMETHODCALLTYPE *PieRadiansAnim )( 
            IDAStatics * This,
            /* [in] */ IDANumber *startAngle_0,
            /* [in] */ IDANumber *endAngle_1,
            /* [in] */ IDANumber *arcWidth_2,
            /* [in] */ IDANumber *arcHeight_3,
            /* [retval][out] */ IDAPath2 **ret_4);
        
        HRESULT ( STDMETHODCALLTYPE *PieDegrees )( 
            IDAStatics * This,
            /* [in] */ double startAngle_0,
            /* [in] */ double endAngle_1,
            /* [in] */ double arcWidth_2,
            /* [in] */ double arcHeight_3,
            /* [retval][out] */ IDAPath2 **ret_4);
        
        HRESULT ( STDMETHODCALLTYPE *Oval )( 
            IDAStatics * This,
            /* [in] */ double width_0,
            /* [in] */ double height_1,
            /* [retval][out] */ IDAPath2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *OvalAnim )( 
            IDAStatics * This,
            /* [in] */ IDANumber *width_0,
            /* [in] */ IDANumber *height_1,
            /* [retval][out] */ IDAPath2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *Rect )( 
            IDAStatics * This,
            /* [in] */ double width_0,
            /* [in] */ double height_1,
            /* [retval][out] */ IDAPath2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *RectAnim )( 
            IDAStatics * This,
            /* [in] */ IDANumber *width_0,
            /* [in] */ IDANumber *height_1,
            /* [retval][out] */ IDAPath2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *RoundRect )( 
            IDAStatics * This,
            /* [in] */ double width_0,
            /* [in] */ double height_1,
            /* [in] */ double cornerArcWidth_2,
            /* [in] */ double cornerArcHeight_3,
            /* [retval][out] */ IDAPath2 **ret_4);
        
        HRESULT ( STDMETHODCALLTYPE *RoundRectAnim )( 
            IDAStatics * This,
            /* [in] */ IDANumber *width_0,
            /* [in] */ IDANumber *height_1,
            /* [in] */ IDANumber *cornerArcWidth_2,
            /* [in] */ IDANumber *cornerArcHeight_3,
            /* [retval][out] */ IDAPath2 **ret_4);
        
        HRESULT ( STDMETHODCALLTYPE *CubicBSplinePathEx )( 
            IDAStatics * This,
            /* [in] */ LONG points_0size,
            /* [size_is][in] */ IDAPoint2 *points_0[  ],
            /* [in] */ LONG knots_1size,
            /* [size_is][in] */ IDANumber *knots_1[  ],
            /* [retval][out] */ IDAPath2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *CubicBSplinePath )( 
            IDAStatics * This,
            /* [in] */ VARIANT points_0,
            /* [in] */ VARIANT knots_1,
            /* [retval][out] */ IDAPath2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *TextPath )( 
            IDAStatics * This,
            /* [in] */ IDAString *obsolete1_0,
            /* [in] */ IDAFontStyle *obsolete2_1,
            /* [retval][out] */ IDAPath2 **ret_2);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Silence )( 
            IDAStatics * This,
            /* [retval][out] */ IDASound **ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *MixArrayEx )( 
            IDAStatics * This,
            /* [in] */ LONG snds_0size,
            /* [size_is][in] */ IDASound *snds_0[  ],
            /* [retval][out] */ IDASound **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *MixArray )( 
            IDAStatics * This,
            /* [in] */ VARIANT snds_0,
            /* [retval][out] */ IDASound **ret_1);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_SinSynth )( 
            IDAStatics * This,
            /* [retval][out] */ IDASound **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_DefaultFont )( 
            IDAStatics * This,
            /* [retval][out] */ IDAFontStyle **ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *FontAnim )( 
            IDAStatics * This,
            /* [in] */ IDAString *str_0,
            /* [in] */ IDANumber *size_1,
            /* [in] */ IDAColor *col_2,
            /* [retval][out] */ IDAFontStyle **ret_3);
        
        HRESULT ( STDMETHODCALLTYPE *Font )( 
            IDAStatics * This,
            /* [in] */ BSTR str_0,
            /* [in] */ double size_1,
            /* [in] */ IDAColor *col_2,
            /* [retval][out] */ IDAFontStyle **ret_3);
        
        HRESULT ( STDMETHODCALLTYPE *StringImageAnim )( 
            IDAStatics * This,
            /* [in] */ IDAString *str_0,
            /* [in] */ IDAFontStyle *fs_1,
            /* [retval][out] */ IDAImage **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *StringImage )( 
            IDAStatics * This,
            /* [in] */ BSTR str_0,
            /* [in] */ IDAFontStyle *fs_1,
            /* [retval][out] */ IDAImage **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *TextImageAnim )( 
            IDAStatics * This,
            /* [in] */ IDAString *obsoleted1_0,
            /* [in] */ IDAFontStyle *obsoleted2_1,
            /* [retval][out] */ IDAImage **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *TextImage )( 
            IDAStatics * This,
            /* [in] */ BSTR obsoleted1_0,
            /* [in] */ IDAFontStyle *obsoleted2_1,
            /* [retval][out] */ IDAImage **ret_2);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_XVector2 )( 
            IDAStatics * This,
            /* [retval][out] */ IDAVector2 **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_YVector2 )( 
            IDAStatics * This,
            /* [retval][out] */ IDAVector2 **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ZeroVector2 )( 
            IDAStatics * This,
            /* [retval][out] */ IDAVector2 **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Origin2 )( 
            IDAStatics * This,
            /* [retval][out] */ IDAPoint2 **ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *Vector2Anim )( 
            IDAStatics * This,
            /* [in] */ IDANumber *x_0,
            /* [in] */ IDANumber *y_1,
            /* [retval][out] */ IDAVector2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *Vector2 )( 
            IDAStatics * This,
            /* [in] */ double x_0,
            /* [in] */ double y_1,
            /* [retval][out] */ IDAVector2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *Point2Anim )( 
            IDAStatics * This,
            /* [in] */ IDANumber *x_0,
            /* [in] */ IDANumber *y_1,
            /* [retval][out] */ IDAPoint2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *Point2 )( 
            IDAStatics * This,
            /* [in] */ double x_0,
            /* [in] */ double y_1,
            /* [retval][out] */ IDAPoint2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *Vector2PolarAnim )( 
            IDAStatics * This,
            /* [in] */ IDANumber *theta_0,
            /* [in] */ IDANumber *radius_1,
            /* [retval][out] */ IDAVector2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *Vector2Polar )( 
            IDAStatics * This,
            /* [in] */ double theta_0,
            /* [in] */ double radius_1,
            /* [retval][out] */ IDAVector2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *Vector2PolarDegrees )( 
            IDAStatics * This,
            /* [in] */ double theta_0,
            /* [in] */ double radius_1,
            /* [retval][out] */ IDAVector2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *Point2PolarAnim )( 
            IDAStatics * This,
            /* [in] */ IDANumber *theta_0,
            /* [in] */ IDANumber *radius_1,
            /* [retval][out] */ IDAPoint2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *Point2Polar )( 
            IDAStatics * This,
            /* [in] */ double theta_0,
            /* [in] */ double radius_1,
            /* [retval][out] */ IDAPoint2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *DotVector2 )( 
            IDAStatics * This,
            /* [in] */ IDAVector2 *v_0,
            /* [in] */ IDAVector2 *u_1,
            /* [retval][out] */ IDANumber **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *NegVector2 )( 
            IDAStatics * This,
            /* [in] */ IDAVector2 *v_0,
            /* [retval][out] */ IDAVector2 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *SubVector2 )( 
            IDAStatics * This,
            /* [in] */ IDAVector2 *v1_0,
            /* [in] */ IDAVector2 *v2_1,
            /* [retval][out] */ IDAVector2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *AddVector2 )( 
            IDAStatics * This,
            /* [in] */ IDAVector2 *v1_0,
            /* [in] */ IDAVector2 *v2_1,
            /* [retval][out] */ IDAVector2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *AddPoint2Vector )( 
            IDAStatics * This,
            /* [in] */ IDAPoint2 *p_0,
            /* [in] */ IDAVector2 *v_1,
            /* [retval][out] */ IDAPoint2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *SubPoint2Vector )( 
            IDAStatics * This,
            /* [in] */ IDAPoint2 *p_0,
            /* [in] */ IDAVector2 *v_1,
            /* [retval][out] */ IDAPoint2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *SubPoint2 )( 
            IDAStatics * This,
            /* [in] */ IDAPoint2 *p1_0,
            /* [in] */ IDAPoint2 *p2_1,
            /* [retval][out] */ IDAVector2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *DistancePoint2 )( 
            IDAStatics * This,
            /* [in] */ IDAPoint2 *p_0,
            /* [in] */ IDAPoint2 *q_1,
            /* [retval][out] */ IDANumber **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *DistanceSquaredPoint2 )( 
            IDAStatics * This,
            /* [in] */ IDAPoint2 *p_0,
            /* [in] */ IDAPoint2 *q_1,
            /* [retval][out] */ IDANumber **ret_2);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_XVector3 )( 
            IDAStatics * This,
            /* [retval][out] */ IDAVector3 **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_YVector3 )( 
            IDAStatics * This,
            /* [retval][out] */ IDAVector3 **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ZVector3 )( 
            IDAStatics * This,
            /* [retval][out] */ IDAVector3 **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ZeroVector3 )( 
            IDAStatics * This,
            /* [retval][out] */ IDAVector3 **ret_0);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Origin3 )( 
            IDAStatics * This,
            /* [retval][out] */ IDAPoint3 **ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *Vector3Anim )( 
            IDAStatics * This,
            /* [in] */ IDANumber *x_0,
            /* [in] */ IDANumber *y_1,
            /* [in] */ IDANumber *z_2,
            /* [retval][out] */ IDAVector3 **ret_3);
        
        HRESULT ( STDMETHODCALLTYPE *Vector3 )( 
            IDAStatics * This,
            /* [in] */ double x_0,
            /* [in] */ double y_1,
            /* [in] */ double z_2,
            /* [retval][out] */ IDAVector3 **ret_3);
        
        HRESULT ( STDMETHODCALLTYPE *Point3Anim )( 
            IDAStatics * This,
            /* [in] */ IDANumber *x_0,
            /* [in] */ IDANumber *y_1,
            /* [in] */ IDANumber *z_2,
            /* [retval][out] */ IDAPoint3 **ret_3);
        
        HRESULT ( STDMETHODCALLTYPE *Point3 )( 
            IDAStatics * This,
            /* [in] */ double x_0,
            /* [in] */ double y_1,
            /* [in] */ double z_2,
            /* [retval][out] */ IDAPoint3 **ret_3);
        
        HRESULT ( STDMETHODCALLTYPE *Vector3SphericalAnim )( 
            IDAStatics * This,
            /* [in] */ IDANumber *xyAngle_0,
            /* [in] */ IDANumber *yzAngle_1,
            /* [in] */ IDANumber *radius_2,
            /* [retval][out] */ IDAVector3 **ret_3);
        
        HRESULT ( STDMETHODCALLTYPE *Vector3Spherical )( 
            IDAStatics * This,
            /* [in] */ double xyAngle_0,
            /* [in] */ double yzAngle_1,
            /* [in] */ double radius_2,
            /* [retval][out] */ IDAVector3 **ret_3);
        
        HRESULT ( STDMETHODCALLTYPE *Point3SphericalAnim )( 
            IDAStatics * This,
            /* [in] */ IDANumber *zxAngle_0,
            /* [in] */ IDANumber *xyAngle_1,
            /* [in] */ IDANumber *radius_2,
            /* [retval][out] */ IDAPoint3 **ret_3);
        
        HRESULT ( STDMETHODCALLTYPE *Point3Spherical )( 
            IDAStatics * This,
            /* [in] */ double zxAngle_0,
            /* [in] */ double xyAngle_1,
            /* [in] */ double radius_2,
            /* [retval][out] */ IDAPoint3 **ret_3);
        
        HRESULT ( STDMETHODCALLTYPE *DotVector3 )( 
            IDAStatics * This,
            /* [in] */ IDAVector3 *v_0,
            /* [in] */ IDAVector3 *u_1,
            /* [retval][out] */ IDANumber **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *CrossVector3 )( 
            IDAStatics * This,
            /* [in] */ IDAVector3 *v_0,
            /* [in] */ IDAVector3 *u_1,
            /* [retval][out] */ IDAVector3 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *NegVector3 )( 
            IDAStatics * This,
            /* [in] */ IDAVector3 *v_0,
            /* [retval][out] */ IDAVector3 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *SubVector3 )( 
            IDAStatics * This,
            /* [in] */ IDAVector3 *v1_0,
            /* [in] */ IDAVector3 *v2_1,
            /* [retval][out] */ IDAVector3 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *AddVector3 )( 
            IDAStatics * This,
            /* [in] */ IDAVector3 *v1_0,
            /* [in] */ IDAVector3 *v2_1,
            /* [retval][out] */ IDAVector3 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *AddPoint3Vector )( 
            IDAStatics * This,
            /* [in] */ IDAPoint3 *p_0,
            /* [in] */ IDAVector3 *v_1,
            /* [retval][out] */ IDAPoint3 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *SubPoint3Vector )( 
            IDAStatics * This,
            /* [in] */ IDAPoint3 *p_0,
            /* [in] */ IDAVector3 *v_1,
            /* [retval][out] */ IDAPoint3 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *SubPoint3 )( 
            IDAStatics * This,
            /* [in] */ IDAPoint3 *p1_0,
            /* [in] */ IDAPoint3 *p2_1,
            /* [retval][out] */ IDAVector3 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *DistancePoint3 )( 
            IDAStatics * This,
            /* [in] */ IDAPoint3 *p_0,
            /* [in] */ IDAPoint3 *q_1,
            /* [retval][out] */ IDANumber **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *DistanceSquaredPoint3 )( 
            IDAStatics * This,
            /* [in] */ IDAPoint3 *p_0,
            /* [in] */ IDAPoint3 *q_1,
            /* [retval][out] */ IDANumber **ret_2);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_IdentityTransform3 )( 
            IDAStatics * This,
            /* [retval][out] */ IDATransform3 **ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *Translate3Anim )( 
            IDAStatics * This,
            /* [in] */ IDANumber *tx_0,
            /* [in] */ IDANumber *ty_1,
            /* [in] */ IDANumber *tz_2,
            /* [retval][out] */ IDATransform3 **ret_3);
        
        HRESULT ( STDMETHODCALLTYPE *Translate3 )( 
            IDAStatics * This,
            /* [in] */ double tx_0,
            /* [in] */ double ty_1,
            /* [in] */ double tz_2,
            /* [retval][out] */ IDATransform3 **ret_3);
        
        HRESULT ( STDMETHODCALLTYPE *Translate3Rate )( 
            IDAStatics * This,
            /* [in] */ double tx_0,
            /* [in] */ double ty_1,
            /* [in] */ double tz_2,
            /* [retval][out] */ IDATransform3 **ret_3);
        
        HRESULT ( STDMETHODCALLTYPE *Translate3Vector )( 
            IDAStatics * This,
            /* [in] */ IDAVector3 *delta_0,
            /* [retval][out] */ IDATransform3 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Translate3Point )( 
            IDAStatics * This,
            /* [in] */ IDAPoint3 *new_origin_0,
            /* [retval][out] */ IDATransform3 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Scale3Anim )( 
            IDAStatics * This,
            /* [in] */ IDANumber *x_0,
            /* [in] */ IDANumber *y_1,
            /* [in] */ IDANumber *z_2,
            /* [retval][out] */ IDATransform3 **ret_3);
        
        HRESULT ( STDMETHODCALLTYPE *Scale3 )( 
            IDAStatics * This,
            /* [in] */ double x_0,
            /* [in] */ double y_1,
            /* [in] */ double z_2,
            /* [retval][out] */ IDATransform3 **ret_3);
        
        HRESULT ( STDMETHODCALLTYPE *Scale3Rate )( 
            IDAStatics * This,
            /* [in] */ double x_0,
            /* [in] */ double y_1,
            /* [in] */ double z_2,
            /* [retval][out] */ IDATransform3 **ret_3);
        
        HRESULT ( STDMETHODCALLTYPE *Scale3Vector )( 
            IDAStatics * This,
            /* [in] */ IDAVector3 *scale_vec_0,
            /* [retval][out] */ IDATransform3 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Scale3UniformAnim )( 
            IDAStatics * This,
            /* [in] */ IDANumber *uniform_scale_0,
            /* [retval][out] */ IDATransform3 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Scale3Uniform )( 
            IDAStatics * This,
            /* [in] */ double uniform_scale_0,
            /* [retval][out] */ IDATransform3 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Scale3UniformRate )( 
            IDAStatics * This,
            /* [in] */ double uniform_scale_0,
            /* [retval][out] */ IDATransform3 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Rotate3Anim )( 
            IDAStatics * This,
            /* [in] */ IDAVector3 *axis_0,
            /* [in] */ IDANumber *angle_1,
            /* [retval][out] */ IDATransform3 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *Rotate3 )( 
            IDAStatics * This,
            /* [in] */ IDAVector3 *axis_0,
            /* [in] */ double angle_1,
            /* [retval][out] */ IDATransform3 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *Rotate3Rate )( 
            IDAStatics * This,
            /* [in] */ IDAVector3 *axis_0,
            /* [in] */ double angle_1,
            /* [retval][out] */ IDATransform3 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *Rotate3Degrees )( 
            IDAStatics * This,
            /* [in] */ IDAVector3 *axis_0,
            /* [in] */ double angle_1,
            /* [retval][out] */ IDATransform3 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *Rotate3RateDegrees )( 
            IDAStatics * This,
            /* [in] */ IDAVector3 *axis_0,
            /* [in] */ double angle_1,
            /* [retval][out] */ IDATransform3 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *XShear3Anim )( 
            IDAStatics * This,
            /* [in] */ IDANumber *a_0,
            /* [in] */ IDANumber *b_1,
            /* [retval][out] */ IDATransform3 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *XShear3 )( 
            IDAStatics * This,
            /* [in] */ double a_0,
            /* [in] */ double b_1,
            /* [retval][out] */ IDATransform3 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *XShear3Rate )( 
            IDAStatics * This,
            /* [in] */ double a_0,
            /* [in] */ double b_1,
            /* [retval][out] */ IDATransform3 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *YShear3Anim )( 
            IDAStatics * This,
            /* [in] */ IDANumber *c_0,
            /* [in] */ IDANumber *d_1,
            /* [retval][out] */ IDATransform3 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *YShear3 )( 
            IDAStatics * This,
            /* [in] */ double c_0,
            /* [in] */ double d_1,
            /* [retval][out] */ IDATransform3 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *YShear3Rate )( 
            IDAStatics * This,
            /* [in] */ double c_0,
            /* [in] */ double d_1,
            /* [retval][out] */ IDATransform3 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *ZShear3Anim )( 
            IDAStatics * This,
            /* [in] */ IDANumber *e_0,
            /* [in] */ IDANumber *f_1,
            /* [retval][out] */ IDATransform3 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *ZShear3 )( 
            IDAStatics * This,
            /* [in] */ double e_0,
            /* [in] */ double f_1,
            /* [retval][out] */ IDATransform3 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *ZShear3Rate )( 
            IDAStatics * This,
            /* [in] */ double e_0,
            /* [in] */ double f_1,
            /* [retval][out] */ IDATransform3 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *Transform4x4AnimEx )( 
            IDAStatics * This,
            /* [in] */ LONG m_0size,
            /* [size_is][in] */ IDANumber *m_0[  ],
            /* [retval][out] */ IDATransform3 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Transform4x4Anim )( 
            IDAStatics * This,
            /* [in] */ VARIANT m_0,
            /* [retval][out] */ IDATransform3 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Compose3 )( 
            IDAStatics * This,
            /* [in] */ IDATransform3 *a_0,
            /* [in] */ IDATransform3 *b_1,
            /* [retval][out] */ IDATransform3 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *Compose3ArrayEx )( 
            IDAStatics * This,
            /* [in] */ LONG xfs_0size,
            /* [size_is][in] */ IDATransform3 *xfs_0[  ],
            /* [retval][out] */ IDATransform3 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Compose3Array )( 
            IDAStatics * This,
            /* [in] */ VARIANT xfs_0,
            /* [retval][out] */ IDATransform3 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *LookAtFrom )( 
            IDAStatics * This,
            /* [in] */ IDAPoint3 *to_0,
            /* [in] */ IDAPoint3 *from_1,
            /* [in] */ IDAVector3 *up_2,
            /* [retval][out] */ IDATransform3 **ret_3);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_IdentityTransform2 )( 
            IDAStatics * This,
            /* [retval][out] */ IDATransform2 **ret_0);
        
        HRESULT ( STDMETHODCALLTYPE *Translate2Anim )( 
            IDAStatics * This,
            /* [in] */ IDANumber *Tx_0,
            /* [in] */ IDANumber *Ty_1,
            /* [retval][out] */ IDATransform2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *Translate2 )( 
            IDAStatics * This,
            /* [in] */ double Tx_0,
            /* [in] */ double Ty_1,
            /* [retval][out] */ IDATransform2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *Translate2Rate )( 
            IDAStatics * This,
            /* [in] */ double Tx_0,
            /* [in] */ double Ty_1,
            /* [retval][out] */ IDATransform2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *Translate2Vector )( 
            IDAStatics * This,
            /* [in] */ IDAVector2 *delta_0,
            /* [retval][out] */ IDATransform2 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Translate2Point )( 
            IDAStatics * This,
            /* [in] */ IDAPoint2 *pos_0,
            /* [retval][out] */ IDATransform2 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Scale2Anim )( 
            IDAStatics * This,
            /* [in] */ IDANumber *x_0,
            /* [in] */ IDANumber *y_1,
            /* [retval][out] */ IDATransform2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *Scale2 )( 
            IDAStatics * This,
            /* [in] */ double x_0,
            /* [in] */ double y_1,
            /* [retval][out] */ IDATransform2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *Scale2Rate )( 
            IDAStatics * This,
            /* [in] */ double x_0,
            /* [in] */ double y_1,
            /* [retval][out] */ IDATransform2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *Scale2Vector2 )( 
            IDAStatics * This,
            /* [in] */ IDAVector2 *obsoleteMethod_0,
            /* [retval][out] */ IDATransform2 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Scale2Vector )( 
            IDAStatics * This,
            /* [in] */ IDAVector2 *scale_vec_0,
            /* [retval][out] */ IDATransform2 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Scale2UniformAnim )( 
            IDAStatics * This,
            /* [in] */ IDANumber *uniform_scale_0,
            /* [retval][out] */ IDATransform2 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Scale2Uniform )( 
            IDAStatics * This,
            /* [in] */ double uniform_scale_0,
            /* [retval][out] */ IDATransform2 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Scale2UniformRate )( 
            IDAStatics * This,
            /* [in] */ double uniform_scale_0,
            /* [retval][out] */ IDATransform2 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Rotate2Anim )( 
            IDAStatics * This,
            /* [in] */ IDANumber *angle_0,
            /* [retval][out] */ IDATransform2 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Rotate2 )( 
            IDAStatics * This,
            /* [in] */ double angle_0,
            /* [retval][out] */ IDATransform2 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Rotate2Rate )( 
            IDAStatics * This,
            /* [in] */ double angle_0,
            /* [retval][out] */ IDATransform2 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Rotate2Degrees )( 
            IDAStatics * This,
            /* [in] */ double angle_0,
            /* [retval][out] */ IDATransform2 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Rotate2RateDegrees )( 
            IDAStatics * This,
            /* [in] */ double angle_0,
            /* [retval][out] */ IDATransform2 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *XShear2Anim )( 
            IDAStatics * This,
            /* [in] */ IDANumber *arg_0,
            /* [retval][out] */ IDATransform2 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *XShear2 )( 
            IDAStatics * This,
            /* [in] */ double arg_0,
            /* [retval][out] */ IDATransform2 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *XShear2Rate )( 
            IDAStatics * This,
            /* [in] */ double arg_0,
            /* [retval][out] */ IDATransform2 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *YShear2Anim )( 
            IDAStatics * This,
            /* [in] */ IDANumber *arg_0,
            /* [retval][out] */ IDATransform2 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *YShear2 )( 
            IDAStatics * This,
            /* [in] */ double arg_0,
            /* [retval][out] */ IDATransform2 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *YShear2Rate )( 
            IDAStatics * This,
            /* [in] */ double arg_0,
            /* [retval][out] */ IDATransform2 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Transform3x2AnimEx )( 
            IDAStatics * This,
            /* [in] */ LONG m_0size,
            /* [size_is][in] */ IDANumber *m_0[  ],
            /* [retval][out] */ IDATransform2 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Transform3x2Anim )( 
            IDAStatics * This,
            /* [in] */ VARIANT m_0,
            /* [retval][out] */ IDATransform2 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Compose2 )( 
            IDAStatics * This,
            /* [in] */ IDATransform2 *a_0,
            /* [in] */ IDATransform2 *b_1,
            /* [retval][out] */ IDATransform2 **ret_2);
        
        HRESULT ( STDMETHODCALLTYPE *Compose2ArrayEx )( 
            IDAStatics * This,
            /* [in] */ LONG xfs_0size,
            /* [size_is][in] */ IDATransform2 *xfs_0[  ],
            /* [retval][out] */ IDATransform2 **ret_1);
        
        HRESULT ( STDMETHODCALLTYPE *Compose2Array )( 
            IDAStatics * This,
            /* [in] */ VARIANT xfs_0,
            /* [retval][out] */ IDATransform2 **ret_1);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Tuple )( 
            IDAStatics * This,
            /* [in] */ VARIANT obsolete1,
            /* [retval][out] */ IDATuple **obsolete2);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Array )( 
            IDAStatics * This,
            /* [in] */ VARIANT obsolete1,
            /* [retval][out] */ IDAArray **obsolete2);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_AreBlockingImportsComplete )( 
            IDAStatics * This,
            /* [retval][out] */ VARIANT_BOOL *bComplete);
        
        END_INTERFACE
    } IDAStaticsVtbl;

    interface IDAStatics
    {
        CONST_VTBL struct IDAStaticsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDAStatics_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDAStatics_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDAStatics_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDAStatics_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDAStatics_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDAStatics_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDAStatics_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDAStatics_get_VersionString(This,str)	\
    (This)->lpVtbl -> get_VersionString(This,str)

#define IDAStatics_get_Site(This,pSite)	\
    (This)->lpVtbl -> get_Site(This,pSite)

#define IDAStatics_put_Site(This,pSite)	\
    (This)->lpVtbl -> put_Site(This,pSite)

#define IDAStatics_put_ClientSite(This,pClientSite)	\
    (This)->lpVtbl -> put_ClientSite(This,pClientSite)

#define IDAStatics_get_ClientSite(This,pClientSite)	\
    (This)->lpVtbl -> get_ClientSite(This,pClientSite)

#define IDAStatics_put_PixelConstructionMode(This,bMode)	\
    (This)->lpVtbl -> put_PixelConstructionMode(This,bMode)

#define IDAStatics_get_PixelConstructionMode(This,bMode)	\
    (This)->lpVtbl -> get_PixelConstructionMode(This,bMode)

#define IDAStatics_TriggerEvent(This,event,data)	\
    (This)->lpVtbl -> TriggerEvent(This,event,data)

#define IDAStatics_NewDrawingSurface(This,pds)	\
    (This)->lpVtbl -> NewDrawingSurface(This,pds)

#define IDAStatics_ImportMovie(This,url,ppResult)	\
    (This)->lpVtbl -> ImportMovie(This,url,ppResult)

#define IDAStatics_ImportMovieAsync(This,url,pImageStandIn,pSoundStandIn,ppResult)	\
    (This)->lpVtbl -> ImportMovieAsync(This,url,pImageStandIn,pSoundStandIn,ppResult)

#define IDAStatics_ImportImage(This,url,ppImage)	\
    (This)->lpVtbl -> ImportImage(This,url,ppImage)

#define IDAStatics_ImportImageAsync(This,url,pImageStandIn,ppResult)	\
    (This)->lpVtbl -> ImportImageAsync(This,url,pImageStandIn,ppResult)

#define IDAStatics_ImportImageColorKey(This,url,colorKeyRed,colorKeyGreen,colorKeyBlue,ppImage)	\
    (This)->lpVtbl -> ImportImageColorKey(This,url,colorKeyRed,colorKeyGreen,colorKeyBlue,ppImage)

#define IDAStatics_ImportImageAsyncColorKey(This,url,pImageStandIn,colorKeyRed,colorKeyGreen,colorKeyBlue,ppResult)	\
    (This)->lpVtbl -> ImportImageAsyncColorKey(This,url,pImageStandIn,colorKeyRed,colorKeyGreen,colorKeyBlue,ppResult)

#define IDAStatics_ImportSound(This,url,ppResult)	\
    (This)->lpVtbl -> ImportSound(This,url,ppResult)

#define IDAStatics_ImportSoundAsync(This,url,pSoundStandIn,ppResult)	\
    (This)->lpVtbl -> ImportSoundAsync(This,url,pSoundStandIn,ppResult)

#define IDAStatics_ImportGeometry(This,url,ppGeometry)	\
    (This)->lpVtbl -> ImportGeometry(This,url,ppGeometry)

#define IDAStatics_ImportGeometryAsync(This,url,pGeoStandIn,ppResult)	\
    (This)->lpVtbl -> ImportGeometryAsync(This,url,pGeoStandIn,ppResult)

#define IDAStatics_ImportDirectDrawSurface(This,dds,updateEvent,ppImage)	\
    (This)->lpVtbl -> ImportDirectDrawSurface(This,dds,updateEvent,ppImage)

#define IDAStatics_Cond(This,c,i,e,pCondBvr)	\
    (This)->lpVtbl -> Cond(This,c,i,e,pCondBvr)

#define IDAStatics_DAArrayEx(This,s,pBvrs,bvr)	\
    (This)->lpVtbl -> DAArrayEx(This,s,pBvrs,bvr)

#define IDAStatics_DAArray(This,bvrs,bvr)	\
    (This)->lpVtbl -> DAArray(This,bvrs,bvr)

#define IDAStatics_DATupleEx(This,s,pBvrs,bvr)	\
    (This)->lpVtbl -> DATupleEx(This,s,pBvrs,bvr)

#define IDAStatics_DATuple(This,bvrs,bvr)	\
    (This)->lpVtbl -> DATuple(This,bvrs,bvr)

#define IDAStatics_ModifiableBehavior(This,orig,bvr)	\
    (This)->lpVtbl -> ModifiableBehavior(This,orig,bvr)

#define IDAStatics_UninitializedArray(This,typeTmp,bvr)	\
    (This)->lpVtbl -> UninitializedArray(This,typeTmp,bvr)

#define IDAStatics_UninitializedTuple(This,typeTmp,bvr)	\
    (This)->lpVtbl -> UninitializedTuple(This,typeTmp,bvr)

#define IDAStatics_NumberBSplineEx(This,degree,numKnots,knots,numPts,ctrlPts,numWts,weights,evaluator,bvr)	\
    (This)->lpVtbl -> NumberBSplineEx(This,degree,numKnots,knots,numPts,ctrlPts,numWts,weights,evaluator,bvr)

#define IDAStatics_NumberBSpline(This,degree,knots,CtrlPts,weights,evaluator,bvr)	\
    (This)->lpVtbl -> NumberBSpline(This,degree,knots,CtrlPts,weights,evaluator,bvr)

#define IDAStatics_Point2BSplineEx(This,degree,numKnots,knots,numPts,ctrlPts,numWts,weights,evaluator,bvr)	\
    (This)->lpVtbl -> Point2BSplineEx(This,degree,numKnots,knots,numPts,ctrlPts,numWts,weights,evaluator,bvr)

#define IDAStatics_Point2BSpline(This,degree,knots,CtrlPts,weights,evaluator,bvr)	\
    (This)->lpVtbl -> Point2BSpline(This,degree,knots,CtrlPts,weights,evaluator,bvr)

#define IDAStatics_Point3BSplineEx(This,degree,numKnots,knots,numPts,ctrlPts,numWts,weights,evaluator,bvr)	\
    (This)->lpVtbl -> Point3BSplineEx(This,degree,numKnots,knots,numPts,ctrlPts,numWts,weights,evaluator,bvr)

#define IDAStatics_Point3BSpline(This,degree,knots,CtrlPts,weights,evaluator,bvr)	\
    (This)->lpVtbl -> Point3BSpline(This,degree,knots,CtrlPts,weights,evaluator,bvr)

#define IDAStatics_Vector2BSplineEx(This,degree,numKnots,knots,numPts,ctrlPts,numWts,weights,evaluator,bvr)	\
    (This)->lpVtbl -> Vector2BSplineEx(This,degree,numKnots,knots,numPts,ctrlPts,numWts,weights,evaluator,bvr)

#define IDAStatics_Vector2BSpline(This,degree,knots,CtrlPts,weights,evaluator,bvr)	\
    (This)->lpVtbl -> Vector2BSpline(This,degree,knots,CtrlPts,weights,evaluator,bvr)

#define IDAStatics_Vector3BSplineEx(This,degree,numKnots,knots,numPts,ctrlPts,numWts,weights,evaluator,bvr)	\
    (This)->lpVtbl -> Vector3BSplineEx(This,degree,numKnots,knots,numPts,ctrlPts,numWts,weights,evaluator,bvr)

#define IDAStatics_Vector3BSpline(This,degree,knots,CtrlPts,weights,evaluator,bvr)	\
    (This)->lpVtbl -> Vector3BSpline(This,degree,knots,CtrlPts,weights,evaluator,bvr)

#define IDAStatics_Pow(This,a_0,b_1,ret_2)	\
    (This)->lpVtbl -> Pow(This,a_0,b_1,ret_2)

#define IDAStatics_Abs(This,a_0,ret_1)	\
    (This)->lpVtbl -> Abs(This,a_0,ret_1)

#define IDAStatics_Sqrt(This,a_0,ret_1)	\
    (This)->lpVtbl -> Sqrt(This,a_0,ret_1)

#define IDAStatics_Floor(This,a_0,ret_1)	\
    (This)->lpVtbl -> Floor(This,a_0,ret_1)

#define IDAStatics_Round(This,a_0,ret_1)	\
    (This)->lpVtbl -> Round(This,a_0,ret_1)

#define IDAStatics_Ceiling(This,a_0,ret_1)	\
    (This)->lpVtbl -> Ceiling(This,a_0,ret_1)

#define IDAStatics_Asin(This,a_0,ret_1)	\
    (This)->lpVtbl -> Asin(This,a_0,ret_1)

#define IDAStatics_Acos(This,a_0,ret_1)	\
    (This)->lpVtbl -> Acos(This,a_0,ret_1)

#define IDAStatics_Atan(This,a_0,ret_1)	\
    (This)->lpVtbl -> Atan(This,a_0,ret_1)

#define IDAStatics_Sin(This,a_0,ret_1)	\
    (This)->lpVtbl -> Sin(This,a_0,ret_1)

#define IDAStatics_Cos(This,a_0,ret_1)	\
    (This)->lpVtbl -> Cos(This,a_0,ret_1)

#define IDAStatics_Tan(This,a_0,ret_1)	\
    (This)->lpVtbl -> Tan(This,a_0,ret_1)

#define IDAStatics_Exp(This,a_0,ret_1)	\
    (This)->lpVtbl -> Exp(This,a_0,ret_1)

#define IDAStatics_Ln(This,a_0,ret_1)	\
    (This)->lpVtbl -> Ln(This,a_0,ret_1)

#define IDAStatics_Log10(This,a_0,ret_1)	\
    (This)->lpVtbl -> Log10(This,a_0,ret_1)

#define IDAStatics_ToDegrees(This,a_0,ret_1)	\
    (This)->lpVtbl -> ToDegrees(This,a_0,ret_1)

#define IDAStatics_ToRadians(This,a_0,ret_1)	\
    (This)->lpVtbl -> ToRadians(This,a_0,ret_1)

#define IDAStatics_Mod(This,a_0,b_1,ret_2)	\
    (This)->lpVtbl -> Mod(This,a_0,b_1,ret_2)

#define IDAStatics_Atan2(This,a_0,b_1,ret_2)	\
    (This)->lpVtbl -> Atan2(This,a_0,b_1,ret_2)

#define IDAStatics_Add(This,a_0,b_1,ret_2)	\
    (This)->lpVtbl -> Add(This,a_0,b_1,ret_2)

#define IDAStatics_Sub(This,a_0,b_1,ret_2)	\
    (This)->lpVtbl -> Sub(This,a_0,b_1,ret_2)

#define IDAStatics_Mul(This,a_0,b_1,ret_2)	\
    (This)->lpVtbl -> Mul(This,a_0,b_1,ret_2)

#define IDAStatics_Div(This,a_0,b_1,ret_2)	\
    (This)->lpVtbl -> Div(This,a_0,b_1,ret_2)

#define IDAStatics_LT(This,a_0,b_1,ret_2)	\
    (This)->lpVtbl -> LT(This,a_0,b_1,ret_2)

#define IDAStatics_LTE(This,a_0,b_1,ret_2)	\
    (This)->lpVtbl -> LTE(This,a_0,b_1,ret_2)

#define IDAStatics_GT(This,a_0,b_1,ret_2)	\
    (This)->lpVtbl -> GT(This,a_0,b_1,ret_2)

#define IDAStatics_GTE(This,a_0,b_1,ret_2)	\
    (This)->lpVtbl -> GTE(This,a_0,b_1,ret_2)

#define IDAStatics_EQ(This,a_0,b_1,ret_2)	\
    (This)->lpVtbl -> EQ(This,a_0,b_1,ret_2)

#define IDAStatics_NE(This,a_0,b_1,ret_2)	\
    (This)->lpVtbl -> NE(This,a_0,b_1,ret_2)

#define IDAStatics_Neg(This,a_0,ret_1)	\
    (This)->lpVtbl -> Neg(This,a_0,ret_1)

#define IDAStatics_InterpolateAnim(This,from_0,to_1,duration_2,ret_3)	\
    (This)->lpVtbl -> InterpolateAnim(This,from_0,to_1,duration_2,ret_3)

#define IDAStatics_Interpolate(This,from_0,to_1,duration_2,ret_3)	\
    (This)->lpVtbl -> Interpolate(This,from_0,to_1,duration_2,ret_3)

#define IDAStatics_SlowInSlowOutAnim(This,from_0,to_1,duration_2,sharpness_3,ret_4)	\
    (This)->lpVtbl -> SlowInSlowOutAnim(This,from_0,to_1,duration_2,sharpness_3,ret_4)

#define IDAStatics_SlowInSlowOut(This,from_0,to_1,duration_2,sharpness_3,ret_4)	\
    (This)->lpVtbl -> SlowInSlowOut(This,from_0,to_1,duration_2,sharpness_3,ret_4)

#define IDAStatics_SoundSource(This,snd_0,ret_1)	\
    (This)->lpVtbl -> SoundSource(This,snd_0,ret_1)

#define IDAStatics_Mix(This,left_0,right_1,ret_2)	\
    (This)->lpVtbl -> Mix(This,left_0,right_1,ret_2)

#define IDAStatics_And(This,a_0,b_1,ret_2)	\
    (This)->lpVtbl -> And(This,a_0,b_1,ret_2)

#define IDAStatics_Or(This,a_0,b_1,ret_2)	\
    (This)->lpVtbl -> Or(This,a_0,b_1,ret_2)

#define IDAStatics_Not(This,a_0,ret_1)	\
    (This)->lpVtbl -> Not(This,a_0,ret_1)

#define IDAStatics_Integral(This,b_0,ret_1)	\
    (This)->lpVtbl -> Integral(This,b_0,ret_1)

#define IDAStatics_Derivative(This,b_0,ret_1)	\
    (This)->lpVtbl -> Derivative(This,b_0,ret_1)

#define IDAStatics_IntegralVector2(This,v_0,ret_1)	\
    (This)->lpVtbl -> IntegralVector2(This,v_0,ret_1)

#define IDAStatics_IntegralVector3(This,v_0,ret_1)	\
    (This)->lpVtbl -> IntegralVector3(This,v_0,ret_1)

#define IDAStatics_DerivativeVector2(This,v_0,ret_1)	\
    (This)->lpVtbl -> DerivativeVector2(This,v_0,ret_1)

#define IDAStatics_DerivativeVector3(This,v_0,ret_1)	\
    (This)->lpVtbl -> DerivativeVector3(This,v_0,ret_1)

#define IDAStatics_DerivativePoint2(This,v_0,ret_1)	\
    (This)->lpVtbl -> DerivativePoint2(This,v_0,ret_1)

#define IDAStatics_DerivativePoint3(This,v_0,ret_1)	\
    (This)->lpVtbl -> DerivativePoint3(This,v_0,ret_1)

#define IDAStatics_KeyState(This,n_0,ret_1)	\
    (This)->lpVtbl -> KeyState(This,n_0,ret_1)

#define IDAStatics_KeyUp(This,arg_0,ret_1)	\
    (This)->lpVtbl -> KeyUp(This,arg_0,ret_1)

#define IDAStatics_KeyDown(This,arg_0,ret_1)	\
    (This)->lpVtbl -> KeyDown(This,arg_0,ret_1)

#define IDAStatics_DANumber(This,num_0,ret_1)	\
    (This)->lpVtbl -> DANumber(This,num_0,ret_1)

#define IDAStatics_DAString(This,str_0,ret_1)	\
    (This)->lpVtbl -> DAString(This,str_0,ret_1)

#define IDAStatics_DABoolean(This,num_0,ret_1)	\
    (This)->lpVtbl -> DABoolean(This,num_0,ret_1)

#define IDAStatics_SeededRandom(This,arg_0,ret_1)	\
    (This)->lpVtbl -> SeededRandom(This,arg_0,ret_1)

#define IDAStatics_get_MousePosition(This,ret_0)	\
    (This)->lpVtbl -> get_MousePosition(This,ret_0)

#define IDAStatics_get_LeftButtonState(This,ret_0)	\
    (This)->lpVtbl -> get_LeftButtonState(This,ret_0)

#define IDAStatics_get_RightButtonState(This,ret_0)	\
    (This)->lpVtbl -> get_RightButtonState(This,ret_0)

#define IDAStatics_get_DATrue(This,ret_0)	\
    (This)->lpVtbl -> get_DATrue(This,ret_0)

#define IDAStatics_get_DAFalse(This,ret_0)	\
    (This)->lpVtbl -> get_DAFalse(This,ret_0)

#define IDAStatics_get_LocalTime(This,ret_0)	\
    (This)->lpVtbl -> get_LocalTime(This,ret_0)

#define IDAStatics_get_GlobalTime(This,ret_0)	\
    (This)->lpVtbl -> get_GlobalTime(This,ret_0)

#define IDAStatics_get_Pixel(This,ret_0)	\
    (This)->lpVtbl -> get_Pixel(This,ret_0)

#define IDAStatics_UserData(This,data_0,ret_1)	\
    (This)->lpVtbl -> UserData(This,data_0,ret_1)

#define IDAStatics_UntilNotify(This,b0_0,event_1,notifier_2,ret_3)	\
    (This)->lpVtbl -> UntilNotify(This,b0_0,event_1,notifier_2,ret_3)

#define IDAStatics_Until(This,b0_0,event_1,b1_2,ret_3)	\
    (This)->lpVtbl -> Until(This,b0_0,event_1,b1_2,ret_3)

#define IDAStatics_UntilEx(This,b0_0,event_1,ret_2)	\
    (This)->lpVtbl -> UntilEx(This,b0_0,event_1,ret_2)

#define IDAStatics_Sequence(This,s1_0,s2_1,ret_2)	\
    (This)->lpVtbl -> Sequence(This,s1_0,s2_1,ret_2)

#define IDAStatics_FollowPath(This,path_0,duration_1,ret_2)	\
    (This)->lpVtbl -> FollowPath(This,path_0,duration_1,ret_2)

#define IDAStatics_FollowPathAngle(This,path_0,duration_1,ret_2)	\
    (This)->lpVtbl -> FollowPathAngle(This,path_0,duration_1,ret_2)

#define IDAStatics_FollowPathAngleUpright(This,path_0,duration_1,ret_2)	\
    (This)->lpVtbl -> FollowPathAngleUpright(This,path_0,duration_1,ret_2)

#define IDAStatics_FollowPathEval(This,path_0,eval_1,ret_2)	\
    (This)->lpVtbl -> FollowPathEval(This,path_0,eval_1,ret_2)

#define IDAStatics_FollowPathAngleEval(This,path_0,eval_1,ret_2)	\
    (This)->lpVtbl -> FollowPathAngleEval(This,path_0,eval_1,ret_2)

#define IDAStatics_FollowPathAngleUprightEval(This,path_0,eval_1,ret_2)	\
    (This)->lpVtbl -> FollowPathAngleUprightEval(This,path_0,eval_1,ret_2)

#define IDAStatics_FollowPathAnim(This,obsoleted1_0,obsoleted2_1,ret_2)	\
    (This)->lpVtbl -> FollowPathAnim(This,obsoleted1_0,obsoleted2_1,ret_2)

#define IDAStatics_FollowPathAngleAnim(This,obsoleted1_0,obsoleted2_1,ret_2)	\
    (This)->lpVtbl -> FollowPathAngleAnim(This,obsoleted1_0,obsoleted2_1,ret_2)

#define IDAStatics_FollowPathAngleUprightAnim(This,obsoleted1_0,obsoleted2_1,ret_2)	\
    (This)->lpVtbl -> FollowPathAngleUprightAnim(This,obsoleted1_0,obsoleted2_1,ret_2)

#define IDAStatics_ConcatString(This,s1_0,s2_1,ret_2)	\
    (This)->lpVtbl -> ConcatString(This,s1_0,s2_1,ret_2)

#define IDAStatics_PerspectiveCamera(This,focalDist_0,nearClip_1,ret_2)	\
    (This)->lpVtbl -> PerspectiveCamera(This,focalDist_0,nearClip_1,ret_2)

#define IDAStatics_PerspectiveCameraAnim(This,focalDist_0,nearClip_1,ret_2)	\
    (This)->lpVtbl -> PerspectiveCameraAnim(This,focalDist_0,nearClip_1,ret_2)

#define IDAStatics_ParallelCamera(This,nearClip_0,ret_1)	\
    (This)->lpVtbl -> ParallelCamera(This,nearClip_0,ret_1)

#define IDAStatics_ParallelCameraAnim(This,nearClip_0,ret_1)	\
    (This)->lpVtbl -> ParallelCameraAnim(This,nearClip_0,ret_1)

#define IDAStatics_ColorRgbAnim(This,red_0,green_1,blue_2,ret_3)	\
    (This)->lpVtbl -> ColorRgbAnim(This,red_0,green_1,blue_2,ret_3)

#define IDAStatics_ColorRgb(This,red_0,green_1,blue_2,ret_3)	\
    (This)->lpVtbl -> ColorRgb(This,red_0,green_1,blue_2,ret_3)

#define IDAStatics_ColorRgb255(This,red_0,green_1,blue_2,ret_3)	\
    (This)->lpVtbl -> ColorRgb255(This,red_0,green_1,blue_2,ret_3)

#define IDAStatics_ColorHsl(This,hue_0,saturation_1,lum_2,ret_3)	\
    (This)->lpVtbl -> ColorHsl(This,hue_0,saturation_1,lum_2,ret_3)

#define IDAStatics_ColorHslAnim(This,hue_0,saturation_1,lum_2,ret_3)	\
    (This)->lpVtbl -> ColorHslAnim(This,hue_0,saturation_1,lum_2,ret_3)

#define IDAStatics_get_Red(This,ret_0)	\
    (This)->lpVtbl -> get_Red(This,ret_0)

#define IDAStatics_get_Green(This,ret_0)	\
    (This)->lpVtbl -> get_Green(This,ret_0)

#define IDAStatics_get_Blue(This,ret_0)	\
    (This)->lpVtbl -> get_Blue(This,ret_0)

#define IDAStatics_get_Cyan(This,ret_0)	\
    (This)->lpVtbl -> get_Cyan(This,ret_0)

#define IDAStatics_get_Magenta(This,ret_0)	\
    (This)->lpVtbl -> get_Magenta(This,ret_0)

#define IDAStatics_get_Yellow(This,ret_0)	\
    (This)->lpVtbl -> get_Yellow(This,ret_0)

#define IDAStatics_get_Black(This,ret_0)	\
    (This)->lpVtbl -> get_Black(This,ret_0)

#define IDAStatics_get_White(This,ret_0)	\
    (This)->lpVtbl -> get_White(This,ret_0)

#define IDAStatics_get_Aqua(This,ret_0)	\
    (This)->lpVtbl -> get_Aqua(This,ret_0)

#define IDAStatics_get_Fuchsia(This,ret_0)	\
    (This)->lpVtbl -> get_Fuchsia(This,ret_0)

#define IDAStatics_get_Gray(This,ret_0)	\
    (This)->lpVtbl -> get_Gray(This,ret_0)

#define IDAStatics_get_Lime(This,ret_0)	\
    (This)->lpVtbl -> get_Lime(This,ret_0)

#define IDAStatics_get_Maroon(This,ret_0)	\
    (This)->lpVtbl -> get_Maroon(This,ret_0)

#define IDAStatics_get_Navy(This,ret_0)	\
    (This)->lpVtbl -> get_Navy(This,ret_0)

#define IDAStatics_get_Olive(This,ret_0)	\
    (This)->lpVtbl -> get_Olive(This,ret_0)

#define IDAStatics_get_Purple(This,ret_0)	\
    (This)->lpVtbl -> get_Purple(This,ret_0)

#define IDAStatics_get_Silver(This,ret_0)	\
    (This)->lpVtbl -> get_Silver(This,ret_0)

#define IDAStatics_get_Teal(This,ret_0)	\
    (This)->lpVtbl -> get_Teal(This,ret_0)

#define IDAStatics_Predicate(This,b_0,ret_1)	\
    (This)->lpVtbl -> Predicate(This,b_0,ret_1)

#define IDAStatics_NotEvent(This,event_0,ret_1)	\
    (This)->lpVtbl -> NotEvent(This,event_0,ret_1)

#define IDAStatics_AndEvent(This,e1_0,e2_1,ret_2)	\
    (This)->lpVtbl -> AndEvent(This,e1_0,e2_1,ret_2)

#define IDAStatics_OrEvent(This,e1_0,e2_1,ret_2)	\
    (This)->lpVtbl -> OrEvent(This,e1_0,e2_1,ret_2)

#define IDAStatics_ThenEvent(This,e1_0,e2_1,ret_2)	\
    (This)->lpVtbl -> ThenEvent(This,e1_0,e2_1,ret_2)

#define IDAStatics_get_LeftButtonDown(This,ret_0)	\
    (This)->lpVtbl -> get_LeftButtonDown(This,ret_0)

#define IDAStatics_get_LeftButtonUp(This,ret_0)	\
    (This)->lpVtbl -> get_LeftButtonUp(This,ret_0)

#define IDAStatics_get_RightButtonDown(This,ret_0)	\
    (This)->lpVtbl -> get_RightButtonDown(This,ret_0)

#define IDAStatics_get_RightButtonUp(This,ret_0)	\
    (This)->lpVtbl -> get_RightButtonUp(This,ret_0)

#define IDAStatics_get_Always(This,ret_0)	\
    (This)->lpVtbl -> get_Always(This,ret_0)

#define IDAStatics_get_Never(This,ret_0)	\
    (This)->lpVtbl -> get_Never(This,ret_0)

#define IDAStatics_TimerAnim(This,n_0,ret_1)	\
    (This)->lpVtbl -> TimerAnim(This,n_0,ret_1)

#define IDAStatics_Timer(This,n_0,ret_1)	\
    (This)->lpVtbl -> Timer(This,n_0,ret_1)

#define IDAStatics_AppTriggeredEvent(This,ret_0)	\
    (This)->lpVtbl -> AppTriggeredEvent(This,ret_0)

#define IDAStatics_ScriptCallback(This,obsolete1_0,obsolete2_1,obsolete3_2,ret_3)	\
    (This)->lpVtbl -> ScriptCallback(This,obsolete1_0,obsolete2_1,obsolete3_2,ret_3)

#define IDAStatics_get_EmptyGeometry(This,ret_0)	\
    (This)->lpVtbl -> get_EmptyGeometry(This,ret_0)

#define IDAStatics_UnionGeometry(This,g1_0,g2_1,ret_2)	\
    (This)->lpVtbl -> UnionGeometry(This,g1_0,g2_1,ret_2)

#define IDAStatics_UnionGeometryArrayEx(This,imgs_0size,imgs_0,ret_1)	\
    (This)->lpVtbl -> UnionGeometryArrayEx(This,imgs_0size,imgs_0,ret_1)

#define IDAStatics_UnionGeometryArray(This,imgs_0,ret_1)	\
    (This)->lpVtbl -> UnionGeometryArray(This,imgs_0,ret_1)

#define IDAStatics_get_EmptyImage(This,ret_0)	\
    (This)->lpVtbl -> get_EmptyImage(This,ret_0)

#define IDAStatics_get_DetectableEmptyImage(This,ret_0)	\
    (This)->lpVtbl -> get_DetectableEmptyImage(This,ret_0)

#define IDAStatics_SolidColorImage(This,col_0,ret_1)	\
    (This)->lpVtbl -> SolidColorImage(This,col_0,ret_1)

#define IDAStatics_GradientPolygonEx(This,points_0size,points_0,colors_1size,colors_1,ret_2)	\
    (This)->lpVtbl -> GradientPolygonEx(This,points_0size,points_0,colors_1size,colors_1,ret_2)

#define IDAStatics_GradientPolygon(This,points_0,colors_1,ret_2)	\
    (This)->lpVtbl -> GradientPolygon(This,points_0,colors_1,ret_2)

#define IDAStatics_RadialGradientPolygonEx(This,inner_0,outer_1,points_2size,points_2,fallOff_3,ret_4)	\
    (This)->lpVtbl -> RadialGradientPolygonEx(This,inner_0,outer_1,points_2size,points_2,fallOff_3,ret_4)

#define IDAStatics_RadialGradientPolygon(This,inner_0,outer_1,points_2,fallOff_3,ret_4)	\
    (This)->lpVtbl -> RadialGradientPolygon(This,inner_0,outer_1,points_2,fallOff_3,ret_4)

#define IDAStatics_RadialGradientPolygonAnimEx(This,inner_0,outer_1,points_2size,points_2,fallOff_3,ret_4)	\
    (This)->lpVtbl -> RadialGradientPolygonAnimEx(This,inner_0,outer_1,points_2size,points_2,fallOff_3,ret_4)

#define IDAStatics_RadialGradientPolygonAnim(This,inner_0,outer_1,points_2,fallOff_3,ret_4)	\
    (This)->lpVtbl -> RadialGradientPolygonAnim(This,inner_0,outer_1,points_2,fallOff_3,ret_4)

#define IDAStatics_GradientSquare(This,lowerLeft_0,upperLeft_1,upperRight_2,lowerRight_3,ret_4)	\
    (This)->lpVtbl -> GradientSquare(This,lowerLeft_0,upperLeft_1,upperRight_2,lowerRight_3,ret_4)

#define IDAStatics_RadialGradientSquare(This,inner_0,outer_1,fallOff_2,ret_3)	\
    (This)->lpVtbl -> RadialGradientSquare(This,inner_0,outer_1,fallOff_2,ret_3)

#define IDAStatics_RadialGradientSquareAnim(This,inner_0,outer_1,fallOff_2,ret_3)	\
    (This)->lpVtbl -> RadialGradientSquareAnim(This,inner_0,outer_1,fallOff_2,ret_3)

#define IDAStatics_RadialGradientRegularPoly(This,inner_0,outer_1,numEdges_2,fallOff_3,ret_4)	\
    (This)->lpVtbl -> RadialGradientRegularPoly(This,inner_0,outer_1,numEdges_2,fallOff_3,ret_4)

#define IDAStatics_RadialGradientRegularPolyAnim(This,inner_0,outer_1,numEdges_2,fallOff_3,ret_4)	\
    (This)->lpVtbl -> RadialGradientRegularPolyAnim(This,inner_0,outer_1,numEdges_2,fallOff_3,ret_4)

#define IDAStatics_GradientHorizontal(This,start_0,stop_1,fallOff_2,ret_3)	\
    (This)->lpVtbl -> GradientHorizontal(This,start_0,stop_1,fallOff_2,ret_3)

#define IDAStatics_GradientHorizontalAnim(This,start_0,stop_1,fallOff_2,ret_3)	\
    (This)->lpVtbl -> GradientHorizontalAnim(This,start_0,stop_1,fallOff_2,ret_3)

#define IDAStatics_HatchHorizontal(This,lineClr_0,spacing_1,ret_2)	\
    (This)->lpVtbl -> HatchHorizontal(This,lineClr_0,spacing_1,ret_2)

#define IDAStatics_HatchHorizontalAnim(This,lineClr_0,spacing_1,ret_2)	\
    (This)->lpVtbl -> HatchHorizontalAnim(This,lineClr_0,spacing_1,ret_2)

#define IDAStatics_HatchVertical(This,lineClr_0,spacing_1,ret_2)	\
    (This)->lpVtbl -> HatchVertical(This,lineClr_0,spacing_1,ret_2)

#define IDAStatics_HatchVerticalAnim(This,lineClr_0,spacing_1,ret_2)	\
    (This)->lpVtbl -> HatchVerticalAnim(This,lineClr_0,spacing_1,ret_2)

#define IDAStatics_HatchForwardDiagonal(This,lineClr_0,spacing_1,ret_2)	\
    (This)->lpVtbl -> HatchForwardDiagonal(This,lineClr_0,spacing_1,ret_2)

#define IDAStatics_HatchForwardDiagonalAnim(This,lineClr_0,spacing_1,ret_2)	\
    (This)->lpVtbl -> HatchForwardDiagonalAnim(This,lineClr_0,spacing_1,ret_2)

#define IDAStatics_HatchBackwardDiagonal(This,lineClr_0,spacing_1,ret_2)	\
    (This)->lpVtbl -> HatchBackwardDiagonal(This,lineClr_0,spacing_1,ret_2)

#define IDAStatics_HatchBackwardDiagonalAnim(This,lineClr_0,spacing_1,ret_2)	\
    (This)->lpVtbl -> HatchBackwardDiagonalAnim(This,lineClr_0,spacing_1,ret_2)

#define IDAStatics_HatchCross(This,lineClr_0,spacing_1,ret_2)	\
    (This)->lpVtbl -> HatchCross(This,lineClr_0,spacing_1,ret_2)

#define IDAStatics_HatchCrossAnim(This,lineClr_0,spacing_1,ret_2)	\
    (This)->lpVtbl -> HatchCrossAnim(This,lineClr_0,spacing_1,ret_2)

#define IDAStatics_HatchDiagonalCross(This,lineClr_0,spacing_1,ret_2)	\
    (This)->lpVtbl -> HatchDiagonalCross(This,lineClr_0,spacing_1,ret_2)

#define IDAStatics_HatchDiagonalCrossAnim(This,lineClr_0,spacing_1,ret_2)	\
    (This)->lpVtbl -> HatchDiagonalCrossAnim(This,lineClr_0,spacing_1,ret_2)

#define IDAStatics_Overlay(This,top_0,bottom_1,ret_2)	\
    (This)->lpVtbl -> Overlay(This,top_0,bottom_1,ret_2)

#define IDAStatics_OverlayArrayEx(This,imgs_0size,imgs_0,ret_1)	\
    (This)->lpVtbl -> OverlayArrayEx(This,imgs_0size,imgs_0,ret_1)

#define IDAStatics_OverlayArray(This,imgs_0,ret_1)	\
    (This)->lpVtbl -> OverlayArray(This,imgs_0,ret_1)

#define IDAStatics_get_AmbientLight(This,ret_0)	\
    (This)->lpVtbl -> get_AmbientLight(This,ret_0)

#define IDAStatics_get_DirectionalLight(This,ret_0)	\
    (This)->lpVtbl -> get_DirectionalLight(This,ret_0)

#define IDAStatics_get_PointLight(This,ret_0)	\
    (This)->lpVtbl -> get_PointLight(This,ret_0)

#define IDAStatics_SpotLightAnim(This,fullcone_0,cutoff_1,ret_2)	\
    (This)->lpVtbl -> SpotLightAnim(This,fullcone_0,cutoff_1,ret_2)

#define IDAStatics_SpotLight(This,fullcone_0,cutoff_1,ret_2)	\
    (This)->lpVtbl -> SpotLight(This,fullcone_0,cutoff_1,ret_2)

#define IDAStatics_get_DefaultLineStyle(This,ret_0)	\
    (This)->lpVtbl -> get_DefaultLineStyle(This,ret_0)

#define IDAStatics_get_EmptyLineStyle(This,ret_0)	\
    (This)->lpVtbl -> get_EmptyLineStyle(This,ret_0)

#define IDAStatics_get_JoinStyleBevel(This,ret_0)	\
    (This)->lpVtbl -> get_JoinStyleBevel(This,ret_0)

#define IDAStatics_get_JoinStyleRound(This,ret_0)	\
    (This)->lpVtbl -> get_JoinStyleRound(This,ret_0)

#define IDAStatics_get_JoinStyleMiter(This,ret_0)	\
    (This)->lpVtbl -> get_JoinStyleMiter(This,ret_0)

#define IDAStatics_get_EndStyleFlat(This,ret_0)	\
    (This)->lpVtbl -> get_EndStyleFlat(This,ret_0)

#define IDAStatics_get_EndStyleSquare(This,ret_0)	\
    (This)->lpVtbl -> get_EndStyleSquare(This,ret_0)

#define IDAStatics_get_EndStyleRound(This,ret_0)	\
    (This)->lpVtbl -> get_EndStyleRound(This,ret_0)

#define IDAStatics_get_DashStyleSolid(This,ret_0)	\
    (This)->lpVtbl -> get_DashStyleSolid(This,ret_0)

#define IDAStatics_get_DashStyleDashed(This,ret_0)	\
    (This)->lpVtbl -> get_DashStyleDashed(This,ret_0)

#define IDAStatics_get_DefaultMicrophone(This,ret_0)	\
    (This)->lpVtbl -> get_DefaultMicrophone(This,ret_0)

#define IDAStatics_get_OpaqueMatte(This,ret_0)	\
    (This)->lpVtbl -> get_OpaqueMatte(This,ret_0)

#define IDAStatics_get_ClearMatte(This,ret_0)	\
    (This)->lpVtbl -> get_ClearMatte(This,ret_0)

#define IDAStatics_UnionMatte(This,m1_0,m2_1,ret_2)	\
    (This)->lpVtbl -> UnionMatte(This,m1_0,m2_1,ret_2)

#define IDAStatics_IntersectMatte(This,m1_0,m2_1,ret_2)	\
    (This)->lpVtbl -> IntersectMatte(This,m1_0,m2_1,ret_2)

#define IDAStatics_DifferenceMatte(This,m1_0,m2_1,ret_2)	\
    (This)->lpVtbl -> DifferenceMatte(This,m1_0,m2_1,ret_2)

#define IDAStatics_FillMatte(This,p_0,ret_1)	\
    (This)->lpVtbl -> FillMatte(This,p_0,ret_1)

#define IDAStatics_TextMatte(This,str_0,fs_1,ret_2)	\
    (This)->lpVtbl -> TextMatte(This,str_0,fs_1,ret_2)

#define IDAStatics_get_EmptyMontage(This,ret_0)	\
    (This)->lpVtbl -> get_EmptyMontage(This,ret_0)

#define IDAStatics_ImageMontage(This,im_0,depth_1,ret_2)	\
    (This)->lpVtbl -> ImageMontage(This,im_0,depth_1,ret_2)

#define IDAStatics_ImageMontageAnim(This,im_0,depth_1,ret_2)	\
    (This)->lpVtbl -> ImageMontageAnim(This,im_0,depth_1,ret_2)

#define IDAStatics_UnionMontage(This,m1_0,m2_1,ret_2)	\
    (This)->lpVtbl -> UnionMontage(This,m1_0,m2_1,ret_2)

#define IDAStatics_Concat(This,p1_0,p2_1,ret_2)	\
    (This)->lpVtbl -> Concat(This,p1_0,p2_1,ret_2)

#define IDAStatics_ConcatArrayEx(This,paths_0size,paths_0,ret_1)	\
    (This)->lpVtbl -> ConcatArrayEx(This,paths_0size,paths_0,ret_1)

#define IDAStatics_ConcatArray(This,paths_0,ret_1)	\
    (This)->lpVtbl -> ConcatArray(This,paths_0,ret_1)

#define IDAStatics_Line(This,p1_0,p2_1,ret_2)	\
    (This)->lpVtbl -> Line(This,p1_0,p2_1,ret_2)

#define IDAStatics_Ray(This,pt_0,ret_1)	\
    (This)->lpVtbl -> Ray(This,pt_0,ret_1)

#define IDAStatics_StringPathAnim(This,str_0,fs_1,ret_2)	\
    (This)->lpVtbl -> StringPathAnim(This,str_0,fs_1,ret_2)

#define IDAStatics_StringPath(This,str_0,fs_1,ret_2)	\
    (This)->lpVtbl -> StringPath(This,str_0,fs_1,ret_2)

#define IDAStatics_PolylineEx(This,points_0size,points_0,ret_1)	\
    (This)->lpVtbl -> PolylineEx(This,points_0size,points_0,ret_1)

#define IDAStatics_Polyline(This,points_0,ret_1)	\
    (This)->lpVtbl -> Polyline(This,points_0,ret_1)

#define IDAStatics_PolydrawPathEx(This,points_0size,points_0,codes_1size,codes_1,ret_2)	\
    (This)->lpVtbl -> PolydrawPathEx(This,points_0size,points_0,codes_1size,codes_1,ret_2)

#define IDAStatics_PolydrawPath(This,points_0,codes_1,ret_2)	\
    (This)->lpVtbl -> PolydrawPath(This,points_0,codes_1,ret_2)

#define IDAStatics_ArcRadians(This,startAngle_0,endAngle_1,arcWidth_2,arcHeight_3,ret_4)	\
    (This)->lpVtbl -> ArcRadians(This,startAngle_0,endAngle_1,arcWidth_2,arcHeight_3,ret_4)

#define IDAStatics_ArcRadiansAnim(This,startAngle_0,endAngle_1,arcWidth_2,arcHeight_3,ret_4)	\
    (This)->lpVtbl -> ArcRadiansAnim(This,startAngle_0,endAngle_1,arcWidth_2,arcHeight_3,ret_4)

#define IDAStatics_ArcDegrees(This,startAngle_0,endAngle_1,arcWidth_2,arcHeight_3,ret_4)	\
    (This)->lpVtbl -> ArcDegrees(This,startAngle_0,endAngle_1,arcWidth_2,arcHeight_3,ret_4)

#define IDAStatics_PieRadians(This,startAngle_0,endAngle_1,arcWidth_2,arcHeight_3,ret_4)	\
    (This)->lpVtbl -> PieRadians(This,startAngle_0,endAngle_1,arcWidth_2,arcHeight_3,ret_4)

#define IDAStatics_PieRadiansAnim(This,startAngle_0,endAngle_1,arcWidth_2,arcHeight_3,ret_4)	\
    (This)->lpVtbl -> PieRadiansAnim(This,startAngle_0,endAngle_1,arcWidth_2,arcHeight_3,ret_4)

#define IDAStatics_PieDegrees(This,startAngle_0,endAngle_1,arcWidth_2,arcHeight_3,ret_4)	\
    (This)->lpVtbl -> PieDegrees(This,startAngle_0,endAngle_1,arcWidth_2,arcHeight_3,ret_4)

#define IDAStatics_Oval(This,width_0,height_1,ret_2)	\
    (This)->lpVtbl -> Oval(This,width_0,height_1,ret_2)

#define IDAStatics_OvalAnim(This,width_0,height_1,ret_2)	\
    (This)->lpVtbl -> OvalAnim(This,width_0,height_1,ret_2)

#define IDAStatics_Rect(This,width_0,height_1,ret_2)	\
    (This)->lpVtbl -> Rect(This,width_0,height_1,ret_2)

#define IDAStatics_RectAnim(This,width_0,height_1,ret_2)	\
    (This)->lpVtbl -> RectAnim(This,width_0,height_1,ret_2)

#define IDAStatics_RoundRect(This,width_0,height_1,cornerArcWidth_2,cornerArcHeight_3,ret_4)	\
    (This)->lpVtbl -> RoundRect(This,width_0,height_1,cornerArcWidth_2,cornerArcHeight_3,ret_4)

#define IDAStatics_RoundRectAnim(This,width_0,height_1,cornerArcWidth_2,cornerArcHeight_3,ret_4)	\
    (This)->lpVtbl -> RoundRectAnim(This,width_0,height_1,cornerArcWidth_2,cornerArcHeight_3,ret_4)

#define IDAStatics_CubicBSplinePathEx(This,points_0size,points_0,knots_1size,knots_1,ret_2)	\
    (This)->lpVtbl -> CubicBSplinePathEx(This,points_0size,points_0,knots_1size,knots_1,ret_2)

#define IDAStatics_CubicBSplinePath(This,points_0,knots_1,ret_2)	\
    (This)->lpVtbl -> CubicBSplinePath(This,points_0,knots_1,ret_2)

#define IDAStatics_TextPath(This,obsolete1_0,obsolete2_1,ret_2)	\
    (This)->lpVtbl -> TextPath(This,obsolete1_0,obsolete2_1,ret_2)

#define IDAStatics_get_Silence(This,ret_0)	\
    (This)->lpVtbl -> get_Silence(This,ret_0)

#define IDAStatics_MixArrayEx(This,snds_0size,snds_0,ret_1)	\
    (This)->lpVtbl -> MixArrayEx(This,snds_0size,snds_0,ret_1)

#define IDAStatics_MixArray(This,snds_0,ret_1)	\
    (This)->lpVtbl -> MixArray(This,snds_0,ret_1)

#define IDAStatics_get_SinSynth(This,ret_0)	\
    (This)->lpVtbl -> get_SinSynth(This,ret_0)

#define IDAStatics_get_DefaultFont(This,ret_0)	\
    (This)->lpVtbl -> get_DefaultFont(This,ret_0)

#define IDAStatics_FontAnim(This,str_0,size_1,col_2,ret_3)	\
    (This)->lpVtbl -> FontAnim(This,str_0,size_1,col_2,ret_3)

#define IDAStatics_Font(This,str_0,size_1,col_2,ret_3)	\
    (This)->lpVtbl -> Font(This,str_0,size_1,col_2,ret_3)

#define IDAStatics_StringImageAnim(This,str_0,fs_1,ret_2)	\
    (This)->lpVtbl -> StringImageAnim(This,str_0,fs_1,ret_2)

#define IDAStatics_StringImage(This,str_0,fs_1,ret_2)	\
    (This)->lpVtbl -> StringImage(This,str_0,fs_1,ret_2)

#define IDAStatics_TextImageAnim(This,obsoleted1_0,obsoleted2_1,ret_2)	\
    (This)->lpVtbl -> TextImageAnim(This,obsoleted1_0,obsoleted2_1,ret_2)

#define IDAStatics_TextImage(This,obsoleted1_0,obsoleted2_1,ret_2)	\
    (This)->lpVtbl -> TextImage(This,obsoleted1_0,obsoleted2_1,ret_2)

#define IDAStatics_get_XVector2(This,ret_0)	\
    (This)->lpVtbl -> get_XVector2(This,ret_0)

#define IDAStatics_get_YVector2(This,ret_0)	\
    (This)->lpVtbl -> get_YVector2(This,ret_0)

#define IDAStatics_get_ZeroVector2(This,ret_0)	\
    (This)->lpVtbl -> get_ZeroVector2(This,ret_0)

#define IDAStatics_get_Origin2(This,ret_0)	\
    (This)->lpVtbl -> get_Origin2(This,ret_0)

#define IDAStatics_Vector2Anim(This,x_0,y_1,ret_2)	\
    (This)->lpVtbl -> Vector2Anim(This,x_0,y_1,ret_2)

#define IDAStatics_Vector2(This,x_0,y_1,ret_2)	\
    (This)->lpVtbl -> Vector2(This,x_0,y_1,ret_2)

#define IDAStatics_Point2Anim(This,x_0,y_1,ret_2)	\
    (This)->lpVtbl -> Point2Anim(This,x_0,y_1,ret_2)

#define IDAStatics_Point2(This,x_0,y_1,ret_2)	\
    (This)->lpVtbl -> Point2(This,x_0,y_1,ret_2)

#define IDAStatics_Vector2PolarAnim(This,theta_0,radius_1,ret_2)	\
    (This)->lpVtbl -> Vector2PolarAnim(This,theta_0,radius_1,ret_2)

#define IDAStatics_Vector2Polar(This,theta_0,radius_1,ret_2)	\
    (This)->lpVtbl -> Vector2Polar(This,theta_0,radius_1,ret_2)

#define IDAStatics_Vector2PolarDegrees(This,theta_0,radius_1,ret_2)	\
    (This)->lpVtbl -> Vector2PolarDegrees(This,theta_0,radius_1,ret_2)

#define IDAStatics_Point2PolarAnim(This,theta_0,radius_1,ret_2)	\
    (This)->lpVtbl -> Point2PolarAnim(This,theta_0,radius_1,ret_2)

#define IDAStatics_Point2Polar(This,theta_0,radius_1,ret_2)	\
    (This)->lpVtbl -> Point2Polar(This,theta_0,radius_1,ret_2)

#define IDAStatics_DotVector2(This,v_0,u_1,ret_2)	\
    (This)->lpVtbl -> DotVector2(This,v_0,u_1,ret_2)

#define IDAStatics_NegVector2(This,v_0,ret_1)	\
    (This)->lpVtbl -> NegVector2(This,v_0,ret_1)

#define IDAStatics_SubVector2(This,v1_0,v2_1,ret_2)	\
    (This)->lpVtbl -> SubVector2(This,v1_0,v2_1,ret_2)

#define IDAStatics_AddVector2(This,v1_0,v2_1,ret_2)	\
    (This)->lpVtbl -> AddVector2(This,v1_0,v2_1,ret_2)

#define IDAStatics_AddPoint2Vector(This,p_0,v_1,ret_2)	\
    (This)->lpVtbl -> AddPoint2Vector(This,p_0,v_1,ret_2)

#define IDAStatics_SubPoint2Vector(This,p_0,v_1,ret_2)	\
    (This)->lpVtbl -> SubPoint2Vector(This,p_0,v_1,ret_2)

#define IDAStatics_SubPoint2(This,p1_0,p2_1,ret_2)	\
    (This)->lpVtbl -> SubPoint2(This,p1_0,p2_1,ret_2)

#define IDAStatics_DistancePoint2(This,p_0,q_1,ret_2)	\
    (This)->lpVtbl -> DistancePoint2(This,p_0,q_1,ret_2)

#define IDAStatics_DistanceSquaredPoint2(This,p_0,q_1,ret_2)	\
    (This)->lpVtbl -> DistanceSquaredPoint2(This,p_0,q_1,ret_2)

#define IDAStatics_get_XVector3(This,ret_0)	\
    (This)->lpVtbl -> get_XVector3(This,ret_0)

#define IDAStatics_get_YVector3(This,ret_0)	\
    (This)->lpVtbl -> get_YVector3(This,ret_0)

#define IDAStatics_get_ZVector3(This,ret_0)	\
    (This)->lpVtbl -> get_ZVector3(This,ret_0)

#define IDAStatics_get_ZeroVector3(This,ret_0)	\
    (This)->lpVtbl -> get_ZeroVector3(This,ret_0)

#define IDAStatics_get_Origin3(This,ret_0)	\
    (This)->lpVtbl -> get_Origin3(This,ret_0)

#define IDAStatics_Vector3Anim(This,x_0,y_1,z_2,ret_3)	\
    (This)->lpVtbl -> Vector3Anim(This,x_0,y_1,z_2,ret_3)

#define IDAStatics_Vector3(This,x_0,y_1,z_2,ret_3)	\
    (This)->lpVtbl -> Vector3(This,x_0,y_1,z_2,ret_3)

#define IDAStatics_Point3Anim(This,x_0,y_1,z_2,ret_3)	\
    (This)->lpVtbl -> Point3Anim(This,x_0,y_1,z_2,ret_3)

#define IDAStatics_Point3(This,x_0,y_1,z_2,ret_3)	\
    (This)->lpVtbl -> Point3(This,x_0,y_1,z_2,ret_3)

#define IDAStatics_Vector3SphericalAnim(This,xyAngle_0,yzAngle_1,radius_2,ret_3)	\
    (This)->lpVtbl -> Vector3SphericalAnim(This,xyAngle_0,yzAngle_1,radius_2,ret_3)

#define IDAStatics_Vector3Spherical(This,xyAngle_0,yzAngle_1,radius_2,ret_3)	\
    (This)->lpVtbl -> Vector3Spherical(This,xyAngle_0,yzAngle_1,radius_2,ret_3)

#define IDAStatics_Point3SphericalAnim(This,zxAngle_0,xyAngle_1,radius_2,ret_3)	\
    (This)->lpVtbl -> Point3SphericalAnim(This,zxAngle_0,xyAngle_1,radius_2,ret_3)

#define IDAStatics_Point3Spherical(This,zxAngle_0,xyAngle_1,radius_2,ret_3)	\
    (This)->lpVtbl -> Point3Spherical(This,zxAngle_0,xyAngle_1,radius_2,ret_3)

#define IDAStatics_DotVector3(This,v_0,u_1,ret_2)	\
    (This)->lpVtbl -> DotVector3(This,v_0,u_1,ret_2)

#define IDAStatics_CrossVector3(This,v_0,u_1,ret_2)	\
    (This)->lpVtbl -> CrossVector3(This,v_0,u_1,ret_2)

#define IDAStatics_NegVector3(This,v_0,ret_1)	\
    (This)->lpVtbl -> NegVector3(This,v_0,ret_1)

#define IDAStatics_SubVector3(This,v1_0,v2_1,ret_2)	\
    (This)->lpVtbl -> SubVector3(This,v1_0,v2_1,ret_2)

#define IDAStatics_AddVector3(This,v1_0,v2_1,ret_2)	\
    (This)->lpVtbl -> AddVector3(This,v1_0,v2_1,ret_2)

#define IDAStatics_AddPoint3Vector(This,p_0,v_1,ret_2)	\
    (This)->lpVtbl -> AddPoint3Vector(This,p_0,v_1,ret_2)

#define IDAStatics_SubPoint3Vector(This,p_0,v_1,ret_2)	\
    (This)->lpVtbl -> SubPoint3Vector(This,p_0,v_1,ret_2)

#define IDAStatics_SubPoint3(This,p1_0,p2_1,ret_2)	\
    (This)->lpVtbl -> SubPoint3(This,p1_0,p2_1,ret_2)

#define IDAStatics_DistancePoint3(This,p_0,q_1,ret_2)	\
    (This)->lpVtbl -> DistancePoint3(This,p_0,q_1,ret_2)

#define IDAStatics_DistanceSquaredPoint3(This,p_0,q_1,ret_2)	\
    (This)->lpVtbl -> DistanceSquaredPoint3(This,p_0,q_1,ret_2)

#define IDAStatics_get_IdentityTransform3(This,ret_0)	\
    (This)->lpVtbl -> get_IdentityTransform3(This,ret_0)

#define IDAStatics_Translate3Anim(This,tx_0,ty_1,tz_2,ret_3)	\
    (This)->lpVtbl -> Translate3Anim(This,tx_0,ty_1,tz_2,ret_3)

#define IDAStatics_Translate3(This,tx_0,ty_1,tz_2,ret_3)	\
    (This)->lpVtbl -> Translate3(This,tx_0,ty_1,tz_2,ret_3)

#define IDAStatics_Translate3Rate(This,tx_0,ty_1,tz_2,ret_3)	\
    (This)->lpVtbl -> Translate3Rate(This,tx_0,ty_1,tz_2,ret_3)

#define IDAStatics_Translate3Vector(This,delta_0,ret_1)	\
    (This)->lpVtbl -> Translate3Vector(This,delta_0,ret_1)

#define IDAStatics_Translate3Point(This,new_origin_0,ret_1)	\
    (This)->lpVtbl -> Translate3Point(This,new_origin_0,ret_1)

#define IDAStatics_Scale3Anim(This,x_0,y_1,z_2,ret_3)	\
    (This)->lpVtbl -> Scale3Anim(This,x_0,y_1,z_2,ret_3)

#define IDAStatics_Scale3(This,x_0,y_1,z_2,ret_3)	\
    (This)->lpVtbl -> Scale3(This,x_0,y_1,z_2,ret_3)

#define IDAStatics_Scale3Rate(This,x_0,y_1,z_2,ret_3)	\
    (This)->lpVtbl -> Scale3Rate(This,x_0,y_1,z_2,ret_3)

#define IDAStatics_Scale3Vector(This,scale_vec_0,ret_1)	\
    (This)->lpVtbl -> Scale3Vector(This,scale_vec_0,ret_1)

#define IDAStatics_Scale3UniformAnim(This,uniform_scale_0,ret_1)	\
    (This)->lpVtbl -> Scale3UniformAnim(This,uniform_scale_0,ret_1)

#define IDAStatics_Scale3Uniform(This,uniform_scale_0,ret_1)	\
    (This)->lpVtbl -> Scale3Uniform(This,uniform_scale_0,ret_1)

#define IDAStatics_Scale3UniformRate(This,uniform_scale_0,ret_1)	\
    (This)->lpVtbl -> Scale3UniformRate(This,uniform_scale_0,ret_1)

#define IDAStatics_Rotate3Anim(This,axis_0,angle_1,ret_2)	\
    (This)->lpVtbl -> Rotate3Anim(This,axis_0,angle_1,ret_2)

#define IDAStatics_Rotate3(This,axis_0,angle_1,ret_2)	\
    (This)->lpVtbl -> Rotate3(This,axis_0,angle_1,ret_2)

#define IDAStatics_Rotate3Rate(This,axis_0,angle_1,ret_2)	\
    (This)->lpVtbl -> Rotate3Rate(This,axis_0,angle_1,ret_2)

#define IDAStatics_Rotate3Degrees(This,axis_0,angle_1,ret_2)	\
    (This)->lpVtbl -> Rotate3Degrees(This,axis_0,angle_1,ret_2)

#define IDAStatics_Rotate3RateDegrees(This,axis_0,angle_1,ret_2)	\
    (This)->lpVtbl -> Rotate3RateDegrees(This,axis_0,angle_1,ret_2)

#define IDAStatics_XShear3Anim(This,a_0,b_1,ret_2)	\
    (This)->lpVtbl -> XShear3Anim(This,a_0,b_1,ret_2)

#define IDAStatics_XShear3(This,a_0,b_1,ret_2)	\
    (This)->lpVtbl -> XShear3(This,a_0,b_1,ret_2)

#define IDAStatics_XShear3Rate(This,a_0,b_1,ret_2)	\
    (This)->lpVtbl -> XShear3Rate(This,a_0,b_1,ret_2)

#define IDAStatics_YShear3Anim(This,c_0,d_1,ret_2)	\
    (This)->lpVtbl -> YShear3Anim(This,c_0,d_1,ret_2)

#define IDAStatics_YShear3(This,c_0,d_1,ret_2)	\
    (This)->lpVtbl -> YShear3(This,c_0,d_1,ret_2)

#define IDAStatics_YShear3Rate(This,c_0,d_1,ret_2)	\
    (This)->lpVtbl -> YShear3Rate(This,c_0,d_1,ret_2)

#define IDAStatics_ZShear3Anim(This,e_0,f_1,ret_2)	\
    (This)->lpVtbl -> ZShear3Anim(This,e_0,f_1,ret_2)

#define IDAStatics_ZShear3(This,e_0,f_1,ret_2)	\
    (This)->lpVtbl -> ZShear3(This,e_0,f_1,ret_2)

#define IDAStatics_ZShear3Rate(This,e_0,f_1,ret_2)	\
    (This)->lpVtbl -> ZShear3Rate(This,e_0,f_1,ret_2)

#define IDAStatics_Transform4x4AnimEx(This,m_0size,m_0,ret_1)	\
    (This)->lpVtbl -> Transform4x4AnimEx(This,m_0size,m_0,ret_1)

#define IDAStatics_Transform4x4Anim(This,m_0,ret_1)	\
    (This)->lpVtbl -> Transform4x4Anim(This,m_0,ret_1)

#define IDAStatics_Compose3(This,a_0,b_1,ret_2)	\
    (This)->lpVtbl -> Compose3(This,a_0,b_1,ret_2)

#define IDAStatics_Compose3ArrayEx(This,xfs_0size,xfs_0,ret_1)	\
    (This)->lpVtbl -> Compose3ArrayEx(This,xfs_0size,xfs_0,ret_1)

#define IDAStatics_Compose3Array(This,xfs_0,ret_1)	\
    (This)->lpVtbl -> Compose3Array(This,xfs_0,ret_1)

#define IDAStatics_LookAtFrom(This,to_0,from_1,up_2,ret_3)	\
    (This)->lpVtbl -> LookAtFrom(This,to_0,from_1,up_2,ret_3)

#define IDAStatics_get_IdentityTransform2(This,ret_0)	\
    (This)->lpVtbl -> get_IdentityTransform2(This,ret_0)

#define IDAStatics_Translate2Anim(This,Tx_0,Ty_1,ret_2)	\
    (This)->lpVtbl -> Translate2Anim(This,Tx_0,Ty_1,ret_2)

#define IDAStatics_Translate2(This,Tx_0,Ty_1,ret_2)	\
    (This)->lpVtbl -> Translate2(This,Tx_0,Ty_1,ret_2)

#define IDAStatics_Translate2Rate(This,Tx_0,Ty_1,ret_2)	\
    (This)->lpVtbl -> Translate2Rate(This,Tx_0,Ty_1,ret_2)

#define IDAStatics_Translate2Vector(This,delta_0,ret_1)	\
    (This)->lpVtbl -> Translate2Vector(This,delta_0,ret_1)

#define IDAStatics_Translate2Point(This,pos_0,ret_1)	\
    (This)->lpVtbl -> Translate2Point(This,pos_0,ret_1)

#define IDAStatics_Scale2Anim(This,x_0,y_1,ret_2)	\
    (This)->lpVtbl -> Scale2Anim(This,x_0,y_1,ret_2)

#define IDAStatics_Scale2(This,x_0,y_1,ret_2)	\
    (This)->lpVtbl -> Scale2(This,x_0,y_1,ret_2)

#define IDAStatics_Scale2Rate(This,x_0,y_1,ret_2)	\
    (This)->lpVtbl -> Scale2Rate(This,x_0,y_1,ret_2)

#define IDAStatics_Scale2Vector2(This,obsoleteMethod_0,ret_1)	\
    (This)->lpVtbl -> Scale2Vector2(This,obsoleteMethod_0,ret_1)

#define IDAStatics_Scale2Vector(This,scale_vec_0,ret_1)	\
    (This)->lpVtbl -> Scale2Vector(This,scale_vec_0,ret_1)

#define IDAStatics_Scale2UniformAnim(This,uniform_scale_0,ret_1)	\
    (This)->lpVtbl -> Scale2UniformAnim(This,uniform_scale_0,ret_1)

#define IDAStatics_Scale2Uniform(This,uniform_scale_0,ret_1)	\
    (This)->lpVtbl -> Scale2Uniform(This,uniform_scale_0,ret_1)

#define IDAStatics_Scale2UniformRate(This,uniform_scale_0,ret_1)	\
    (This)->lpVtbl -> Scale2UniformRate(This,uniform_scale_0,ret_1)

#define IDAStatics_Rotate2Anim(This,angle_0,ret_1)	\
    (This)->lpVtbl -> Rotate2Anim(This,angle_0,ret_1)

#define IDAStatics_Rotate2(This,angle_0,ret_1)	\
    (This)->lpVtbl -> Rotate2(This,angle_0,ret_1)

#define IDAStatics_Rotate2Rate(This,angle_0,ret_1)	\
    (This)->lpVtbl -> Rotate2Rate(This,angle_0,ret_1)

#define IDAStatics_Rotate2Degrees(This,angle_0,ret_1)	\
    (This)->lpVtbl -> Rotate2Degrees(This,angle_0,ret_1)

#define IDAStatics_Rotate2RateDegrees(This,angle_0,ret_1)	\
    (This)->lpVtbl -> Rotate2RateDegrees(This,angle_0,ret_1)

#define IDAStatics_XShear2Anim(This,arg_0,ret_1)	\
    (This)->lpVtbl -> XShear2Anim(This,arg_0,ret_1)

#define IDAStatics_XShear2(This,arg_0,ret_1)	\
    (This)->lpVtbl -> XShear2(This,arg_0,ret_1)

#define IDAStatics_XShear2Rate(This,arg_0,ret_1)	\
    (This)->lpVtbl -> XShear2Rate(This,arg_0,ret_1)

#define IDAStatics_YShear2Anim(This,arg_0,ret_1)	\
    (This)->lpVtbl -> YShear2Anim(This,arg_0,ret_1)

#define IDAStatics_YShear2(This,arg_0,ret_1)	\
    (This)->lpVtbl -> YShear2(This,arg_0,ret_1)

#define IDAStatics_YShear2Rate(This,arg_0,ret_1)	\
    (This)->lpVtbl -> YShear2Rate(This,arg_0,ret_1)

#define IDAStatics_Transform3x2AnimEx(This,m_0size,m_0,ret_1)	\
    (This)->lpVtbl -> Transform3x2AnimEx(This,m_0size,m_0,ret_1)

#define IDAStatics_Transform3x2Anim(This,m_0,ret_1)	\
    (This)->lpVtbl -> Transform3x2Anim(This,m_0,ret_1)

#define IDAStatics_Compose2(This,a_0,b_1,ret_2)	\
    (This)->lpVtbl -> Compose2(This,a_0,b_1,ret_2)

#define IDAStatics_Compose2ArrayEx(This,xfs_0size,xfs_0,ret_1)	\
    (This)->lpVtbl -> Compose2ArrayEx(This,xfs_0size,xfs_0,ret_1)

#define IDAStatics_Compose2Array(This,xfs_0,ret_1)	\
    (This)->lpVtbl -> Compose2Array(This,xfs_0,ret_1)

#define IDAStatics_Tuple(This,obsolete1,obsolete2)	\
    (This)->lpVtbl -> Tuple(This,obsolete1,obsolete2)

#define IDAStatics_Array(This,obsolete1,obsolete2)	\
    (This)->lpVtbl -> Array(This,obsolete1,obsolete2)

#define IDAStatics_get_AreBlockingImportsComplete(This,bComplete)	\
    (This)->lpVtbl -> get_AreBlockingImportsComplete(This,bComplete)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_VersionString_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ BSTR *str);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_Site_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDASite **pSite);



/* [propput] */ HRESULT STDMETHODCALLTYPE IDAStatics_put_Site_Proxy( 
    IDAStatics * This,
    /* [in] */ IDASite *pSite);



/* [propput] */ HRESULT STDMETHODCALLTYPE IDAStatics_put_ClientSite_Proxy( 
    IDAStatics * This,
    /* [in] */ IOleClientSite *pClientSite);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_ClientSite_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IOleClientSite **pClientSite);



/* [propput] */ HRESULT STDMETHODCALLTYPE IDAStatics_put_PixelConstructionMode_Proxy( 
    IDAStatics * This,
    /* [in] */ VARIANT_BOOL bMode);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_PixelConstructionMode_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ VARIANT_BOOL *bMode);



HRESULT STDMETHODCALLTYPE IDAStatics_TriggerEvent_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAEvent *event,
    /* [in] */ IDABehavior *data);



HRESULT STDMETHODCALLTYPE IDAStatics_NewDrawingSurface_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDADrawingSurface **pds);



HRESULT STDMETHODCALLTYPE IDAStatics_ImportMovie_Proxy( 
    IDAStatics * This,
    /* [in] */ BSTR url,
    /* [retval][out] */ IDAImportationResult **ppResult);



HRESULT STDMETHODCALLTYPE IDAStatics_ImportMovieAsync_Proxy( 
    IDAStatics * This,
    /* [in] */ BSTR url,
    /* [in] */ IDAImage *pImageStandIn,
    /* [in] */ IDASound *pSoundStandIn,
    /* [retval][out] */ IDAImportationResult **ppResult);



HRESULT STDMETHODCALLTYPE IDAStatics_ImportImage_Proxy( 
    IDAStatics * This,
    /* [in] */ BSTR url,
    /* [retval][out] */ IDAImage **ppImage);



HRESULT STDMETHODCALLTYPE IDAStatics_ImportImageAsync_Proxy( 
    IDAStatics * This,
    /* [in] */ BSTR url,
    /* [in] */ IDAImage *pImageStandIn,
    /* [retval][out] */ IDAImportationResult **ppResult);



HRESULT STDMETHODCALLTYPE IDAStatics_ImportImageColorKey_Proxy( 
    IDAStatics * This,
    /* [in] */ BSTR url,
    /* [in] */ BYTE colorKeyRed,
    /* [in] */ BYTE colorKeyGreen,
    /* [in] */ BYTE colorKeyBlue,
    /* [retval][out] */ IDAImage **ppImage);



HRESULT STDMETHODCALLTYPE IDAStatics_ImportImageAsyncColorKey_Proxy( 
    IDAStatics * This,
    /* [in] */ BSTR url,
    /* [in] */ IDAImage *pImageStandIn,
    /* [in] */ BYTE colorKeyRed,
    /* [in] */ BYTE colorKeyGreen,
    /* [in] */ BYTE colorKeyBlue,
    /* [retval][out] */ IDAImportationResult **ppResult);



HRESULT STDMETHODCALLTYPE IDAStatics_ImportSound_Proxy( 
    IDAStatics * This,
    /* [in] */ BSTR url,
    /* [retval][out] */ IDAImportationResult **ppResult);



HRESULT STDMETHODCALLTYPE IDAStatics_ImportSoundAsync_Proxy( 
    IDAStatics * This,
    /* [in] */ BSTR url,
    /* [in] */ IDASound *pSoundStandIn,
    /* [retval][out] */ IDAImportationResult **ppResult);



HRESULT STDMETHODCALLTYPE IDAStatics_ImportGeometry_Proxy( 
    IDAStatics * This,
    /* [in] */ BSTR url,
    /* [retval][out] */ IDAGeometry **ppGeometry);



HRESULT STDMETHODCALLTYPE IDAStatics_ImportGeometryAsync_Proxy( 
    IDAStatics * This,
    /* [in] */ BSTR url,
    /* [in] */ IDAGeometry *pGeoStandIn,
    /* [retval][out] */ IDAImportationResult **ppResult);



HRESULT STDMETHODCALLTYPE IDAStatics_ImportDirectDrawSurface_Proxy( 
    IDAStatics * This,
    /* [in] */ IUnknown *dds,
    /* [in] */ IDAEvent *updateEvent,
    /* [retval][out] */ IDAImage **ppImage);



HRESULT STDMETHODCALLTYPE IDAStatics_Cond_Proxy( 
    IDAStatics * This,
    /* [in] */ IDABoolean *c,
    /* [in] */ IDABehavior *i,
    /* [in] */ IDABehavior *e,
    /* [retval][out] */ IDABehavior **pCondBvr);



HRESULT STDMETHODCALLTYPE IDAStatics_DAArrayEx_Proxy( 
    IDAStatics * This,
    /* [in] */ LONG s,
    /* [size_is][in] */ IDABehavior *pBvrs[  ],
    /* [retval][out] */ IDAArray **bvr);



HRESULT STDMETHODCALLTYPE IDAStatics_DAArray_Proxy( 
    IDAStatics * This,
    /* [in] */ VARIANT bvrs,
    /* [retval][out] */ IDAArray **bvr);



HRESULT STDMETHODCALLTYPE IDAStatics_DATupleEx_Proxy( 
    IDAStatics * This,
    /* [in] */ LONG s,
    /* [size_is][in] */ IDABehavior *pBvrs[  ],
    /* [retval][out] */ IDATuple **bvr);



HRESULT STDMETHODCALLTYPE IDAStatics_DATuple_Proxy( 
    IDAStatics * This,
    /* [in] */ VARIANT bvrs,
    /* [retval][out] */ IDATuple **bvr);



HRESULT STDMETHODCALLTYPE IDAStatics_ModifiableBehavior_Proxy( 
    IDAStatics * This,
    /* [in] */ IDABehavior *orig,
    /* [retval][out] */ IDABehavior **bvr);



HRESULT STDMETHODCALLTYPE IDAStatics_UninitializedArray_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAArray *typeTmp,
    /* [retval][out] */ IDAArray **bvr);



HRESULT STDMETHODCALLTYPE IDAStatics_UninitializedTuple_Proxy( 
    IDAStatics * This,
    /* [in] */ IDATuple *typeTmp,
    /* [retval][out] */ IDATuple **bvr);



HRESULT STDMETHODCALLTYPE IDAStatics_NumberBSplineEx_Proxy( 
    IDAStatics * This,
    /* [in] */ int degree,
    /* [in] */ LONG numKnots,
    /* [size_is][in] */ IDANumber *knots[  ],
    /* [in] */ LONG numPts,
    /* [size_is][in] */ IDANumber *ctrlPts[  ],
    /* [in] */ LONG numWts,
    /* [size_is][in] */ IDANumber *weights[  ],
    /* [in] */ IDANumber *evaluator,
    /* [retval][out] */ IDANumber **bvr);



HRESULT STDMETHODCALLTYPE IDAStatics_NumberBSpline_Proxy( 
    IDAStatics * This,
    /* [in] */ int degree,
    /* [in] */ VARIANT knots,
    /* [in] */ VARIANT CtrlPts,
    /* [in] */ VARIANT weights,
    /* [in] */ IDANumber *evaluator,
    /* [retval][out] */ IDANumber **bvr);



HRESULT STDMETHODCALLTYPE IDAStatics_Point2BSplineEx_Proxy( 
    IDAStatics * This,
    /* [in] */ int degree,
    /* [in] */ LONG numKnots,
    /* [size_is][in] */ IDANumber *knots[  ],
    /* [in] */ LONG numPts,
    /* [size_is][in] */ IDAPoint2 *ctrlPts[  ],
    /* [in] */ LONG numWts,
    /* [size_is][in] */ IDANumber *weights[  ],
    /* [in] */ IDANumber *evaluator,
    /* [retval][out] */ IDAPoint2 **bvr);



HRESULT STDMETHODCALLTYPE IDAStatics_Point2BSpline_Proxy( 
    IDAStatics * This,
    /* [in] */ int degree,
    /* [in] */ VARIANT knots,
    /* [in] */ VARIANT CtrlPts,
    /* [in] */ VARIANT weights,
    /* [in] */ IDANumber *evaluator,
    /* [retval][out] */ IDAPoint2 **bvr);



HRESULT STDMETHODCALLTYPE IDAStatics_Point3BSplineEx_Proxy( 
    IDAStatics * This,
    /* [in] */ int degree,
    /* [in] */ LONG numKnots,
    /* [size_is][in] */ IDANumber *knots[  ],
    /* [in] */ LONG numPts,
    /* [size_is][in] */ IDAPoint3 *ctrlPts[  ],
    /* [in] */ LONG numWts,
    /* [size_is][in] */ IDANumber *weights[  ],
    /* [in] */ IDANumber *evaluator,
    /* [retval][out] */ IDAPoint3 **bvr);



HRESULT STDMETHODCALLTYPE IDAStatics_Point3BSpline_Proxy( 
    IDAStatics * This,
    /* [in] */ int degree,
    /* [in] */ VARIANT knots,
    /* [in] */ VARIANT CtrlPts,
    /* [in] */ VARIANT weights,
    /* [in] */ IDANumber *evaluator,
    /* [retval][out] */ IDAPoint3 **bvr);



HRESULT STDMETHODCALLTYPE IDAStatics_Vector2BSplineEx_Proxy( 
    IDAStatics * This,
    /* [in] */ int degree,
    /* [in] */ LONG numKnots,
    /* [size_is][in] */ IDANumber *knots[  ],
    /* [in] */ LONG numPts,
    /* [size_is][in] */ IDAVector2 *ctrlPts[  ],
    /* [in] */ LONG numWts,
    /* [size_is][in] */ IDANumber *weights[  ],
    /* [in] */ IDANumber *evaluator,
    /* [retval][out] */ IDAVector2 **bvr);



HRESULT STDMETHODCALLTYPE IDAStatics_Vector2BSpline_Proxy( 
    IDAStatics * This,
    /* [in] */ int degree,
    /* [in] */ VARIANT knots,
    /* [in] */ VARIANT CtrlPts,
    /* [in] */ VARIANT weights,
    /* [in] */ IDANumber *evaluator,
    /* [retval][out] */ IDAVector2 **bvr);



HRESULT STDMETHODCALLTYPE IDAStatics_Vector3BSplineEx_Proxy( 
    IDAStatics * This,
    /* [in] */ int degree,
    /* [in] */ LONG numKnots,
    /* [size_is][in] */ IDANumber *knots[  ],
    /* [in] */ LONG numPts,
    /* [size_is][in] */ IDAVector3 *ctrlPts[  ],
    /* [in] */ LONG numWts,
    /* [size_is][in] */ IDANumber *weights[  ],
    /* [in] */ IDANumber *evaluator,
    /* [retval][out] */ IDAVector3 **bvr);



HRESULT STDMETHODCALLTYPE IDAStatics_Vector3BSpline_Proxy( 
    IDAStatics * This,
    /* [in] */ int degree,
    /* [in] */ VARIANT knots,
    /* [in] */ VARIANT CtrlPts,
    /* [in] */ VARIANT weights,
    /* [in] */ IDANumber *evaluator,
    /* [retval][out] */ IDAVector3 **bvr);



HRESULT STDMETHODCALLTYPE IDAStatics_Pow_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *a_0,
    /* [in] */ IDANumber *b_1,
    /* [retval][out] */ IDANumber **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_Abs_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *a_0,
    /* [retval][out] */ IDANumber **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Sqrt_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *a_0,
    /* [retval][out] */ IDANumber **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Floor_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *a_0,
    /* [retval][out] */ IDANumber **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Round_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *a_0,
    /* [retval][out] */ IDANumber **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Ceiling_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *a_0,
    /* [retval][out] */ IDANumber **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Asin_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *a_0,
    /* [retval][out] */ IDANumber **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Acos_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *a_0,
    /* [retval][out] */ IDANumber **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Atan_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *a_0,
    /* [retval][out] */ IDANumber **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Sin_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *a_0,
    /* [retval][out] */ IDANumber **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Cos_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *a_0,
    /* [retval][out] */ IDANumber **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Tan_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *a_0,
    /* [retval][out] */ IDANumber **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Exp_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *a_0,
    /* [retval][out] */ IDANumber **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Ln_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *a_0,
    /* [retval][out] */ IDANumber **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Log10_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *a_0,
    /* [retval][out] */ IDANumber **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_ToDegrees_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *a_0,
    /* [retval][out] */ IDANumber **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_ToRadians_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *a_0,
    /* [retval][out] */ IDANumber **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Mod_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *a_0,
    /* [in] */ IDANumber *b_1,
    /* [retval][out] */ IDANumber **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_Atan2_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *a_0,
    /* [in] */ IDANumber *b_1,
    /* [retval][out] */ IDANumber **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_Add_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *a_0,
    /* [in] */ IDANumber *b_1,
    /* [retval][out] */ IDANumber **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_Sub_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *a_0,
    /* [in] */ IDANumber *b_1,
    /* [retval][out] */ IDANumber **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_Mul_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *a_0,
    /* [in] */ IDANumber *b_1,
    /* [retval][out] */ IDANumber **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_Div_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *a_0,
    /* [in] */ IDANumber *b_1,
    /* [retval][out] */ IDANumber **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_LT_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *a_0,
    /* [in] */ IDANumber *b_1,
    /* [retval][out] */ IDABoolean **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_LTE_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *a_0,
    /* [in] */ IDANumber *b_1,
    /* [retval][out] */ IDABoolean **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_GT_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *a_0,
    /* [in] */ IDANumber *b_1,
    /* [retval][out] */ IDABoolean **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_GTE_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *a_0,
    /* [in] */ IDANumber *b_1,
    /* [retval][out] */ IDABoolean **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_EQ_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *a_0,
    /* [in] */ IDANumber *b_1,
    /* [retval][out] */ IDABoolean **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_NE_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *a_0,
    /* [in] */ IDANumber *b_1,
    /* [retval][out] */ IDABoolean **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_Neg_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *a_0,
    /* [retval][out] */ IDANumber **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_InterpolateAnim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *from_0,
    /* [in] */ IDANumber *to_1,
    /* [in] */ IDANumber *duration_2,
    /* [retval][out] */ IDANumber **ret_3);



HRESULT STDMETHODCALLTYPE IDAStatics_Interpolate_Proxy( 
    IDAStatics * This,
    /* [in] */ double from_0,
    /* [in] */ double to_1,
    /* [in] */ double duration_2,
    /* [retval][out] */ IDANumber **ret_3);



HRESULT STDMETHODCALLTYPE IDAStatics_SlowInSlowOutAnim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *from_0,
    /* [in] */ IDANumber *to_1,
    /* [in] */ IDANumber *duration_2,
    /* [in] */ IDANumber *sharpness_3,
    /* [retval][out] */ IDANumber **ret_4);



HRESULT STDMETHODCALLTYPE IDAStatics_SlowInSlowOut_Proxy( 
    IDAStatics * This,
    /* [in] */ double from_0,
    /* [in] */ double to_1,
    /* [in] */ double duration_2,
    /* [in] */ double sharpness_3,
    /* [retval][out] */ IDANumber **ret_4);



HRESULT STDMETHODCALLTYPE IDAStatics_SoundSource_Proxy( 
    IDAStatics * This,
    /* [in] */ IDASound *snd_0,
    /* [retval][out] */ IDAGeometry **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Mix_Proxy( 
    IDAStatics * This,
    /* [in] */ IDASound *left_0,
    /* [in] */ IDASound *right_1,
    /* [retval][out] */ IDASound **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_And_Proxy( 
    IDAStatics * This,
    /* [in] */ IDABoolean *a_0,
    /* [in] */ IDABoolean *b_1,
    /* [retval][out] */ IDABoolean **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_Or_Proxy( 
    IDAStatics * This,
    /* [in] */ IDABoolean *a_0,
    /* [in] */ IDABoolean *b_1,
    /* [retval][out] */ IDABoolean **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_Not_Proxy( 
    IDAStatics * This,
    /* [in] */ IDABoolean *a_0,
    /* [retval][out] */ IDABoolean **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Integral_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *b_0,
    /* [retval][out] */ IDANumber **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Derivative_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *b_0,
    /* [retval][out] */ IDANumber **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_IntegralVector2_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAVector2 *v_0,
    /* [retval][out] */ IDAVector2 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_IntegralVector3_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAVector3 *v_0,
    /* [retval][out] */ IDAVector3 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_DerivativeVector2_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAVector2 *v_0,
    /* [retval][out] */ IDAVector2 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_DerivativeVector3_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAVector3 *v_0,
    /* [retval][out] */ IDAVector3 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_DerivativePoint2_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAPoint2 *v_0,
    /* [retval][out] */ IDAVector2 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_DerivativePoint3_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAPoint3 *v_0,
    /* [retval][out] */ IDAVector3 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_KeyState_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *n_0,
    /* [retval][out] */ IDABoolean **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_KeyUp_Proxy( 
    IDAStatics * This,
    /* [in] */ LONG arg_0,
    /* [retval][out] */ IDAEvent **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_KeyDown_Proxy( 
    IDAStatics * This,
    /* [in] */ LONG arg_0,
    /* [retval][out] */ IDAEvent **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_DANumber_Proxy( 
    IDAStatics * This,
    /* [in] */ double num_0,
    /* [retval][out] */ IDANumber **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_DAString_Proxy( 
    IDAStatics * This,
    /* [in] */ BSTR str_0,
    /* [retval][out] */ IDAString **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_DABoolean_Proxy( 
    IDAStatics * This,
    /* [in] */ VARIANT_BOOL num_0,
    /* [retval][out] */ IDABoolean **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_SeededRandom_Proxy( 
    IDAStatics * This,
    /* [in] */ double arg_0,
    /* [retval][out] */ IDANumber **ret_1);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_MousePosition_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAPoint2 **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_LeftButtonState_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDABoolean **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_RightButtonState_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDABoolean **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_DATrue_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDABoolean **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_DAFalse_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDABoolean **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_LocalTime_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDANumber **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_GlobalTime_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDANumber **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_Pixel_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDANumber **ret_0);



HRESULT STDMETHODCALLTYPE IDAStatics_UserData_Proxy( 
    IDAStatics * This,
    /* [in] */ IUnknown *data_0,
    /* [retval][out] */ IDAUserData **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_UntilNotify_Proxy( 
    IDAStatics * This,
    /* [in] */ IDABehavior *b0_0,
    /* [in] */ IDAEvent *event_1,
    /* [in] */ IDAUntilNotifier *notifier_2,
    /* [retval][out] */ IDABehavior **ret_3);



HRESULT STDMETHODCALLTYPE IDAStatics_Until_Proxy( 
    IDAStatics * This,
    /* [in] */ IDABehavior *b0_0,
    /* [in] */ IDAEvent *event_1,
    /* [in] */ IDABehavior *b1_2,
    /* [retval][out] */ IDABehavior **ret_3);



HRESULT STDMETHODCALLTYPE IDAStatics_UntilEx_Proxy( 
    IDAStatics * This,
    /* [in] */ IDABehavior *b0_0,
    /* [in] */ IDAEvent *event_1,
    /* [retval][out] */ IDABehavior **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_Sequence_Proxy( 
    IDAStatics * This,
    /* [in] */ IDABehavior *s1_0,
    /* [in] */ IDABehavior *s2_1,
    /* [retval][out] */ IDABehavior **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_FollowPath_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAPath2 *path_0,
    /* [in] */ double duration_1,
    /* [retval][out] */ IDATransform2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_FollowPathAngle_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAPath2 *path_0,
    /* [in] */ double duration_1,
    /* [retval][out] */ IDATransform2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_FollowPathAngleUpright_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAPath2 *path_0,
    /* [in] */ double duration_1,
    /* [retval][out] */ IDATransform2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_FollowPathEval_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAPath2 *path_0,
    /* [in] */ IDANumber *eval_1,
    /* [retval][out] */ IDATransform2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_FollowPathAngleEval_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAPath2 *path_0,
    /* [in] */ IDANumber *eval_1,
    /* [retval][out] */ IDATransform2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_FollowPathAngleUprightEval_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAPath2 *path_0,
    /* [in] */ IDANumber *eval_1,
    /* [retval][out] */ IDATransform2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_FollowPathAnim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAPath2 *obsoleted1_0,
    /* [in] */ IDANumber *obsoleted2_1,
    /* [retval][out] */ IDATransform2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_FollowPathAngleAnim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAPath2 *obsoleted1_0,
    /* [in] */ IDANumber *obsoleted2_1,
    /* [retval][out] */ IDATransform2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_FollowPathAngleUprightAnim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAPath2 *obsoleted1_0,
    /* [in] */ IDANumber *obsoleted2_1,
    /* [retval][out] */ IDATransform2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_ConcatString_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAString *s1_0,
    /* [in] */ IDAString *s2_1,
    /* [retval][out] */ IDAString **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_PerspectiveCamera_Proxy( 
    IDAStatics * This,
    /* [in] */ double focalDist_0,
    /* [in] */ double nearClip_1,
    /* [retval][out] */ IDACamera **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_PerspectiveCameraAnim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *focalDist_0,
    /* [in] */ IDANumber *nearClip_1,
    /* [retval][out] */ IDACamera **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_ParallelCamera_Proxy( 
    IDAStatics * This,
    /* [in] */ double nearClip_0,
    /* [retval][out] */ IDACamera **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_ParallelCameraAnim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *nearClip_0,
    /* [retval][out] */ IDACamera **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_ColorRgbAnim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *red_0,
    /* [in] */ IDANumber *green_1,
    /* [in] */ IDANumber *blue_2,
    /* [retval][out] */ IDAColor **ret_3);



HRESULT STDMETHODCALLTYPE IDAStatics_ColorRgb_Proxy( 
    IDAStatics * This,
    /* [in] */ double red_0,
    /* [in] */ double green_1,
    /* [in] */ double blue_2,
    /* [retval][out] */ IDAColor **ret_3);



HRESULT STDMETHODCALLTYPE IDAStatics_ColorRgb255_Proxy( 
    IDAStatics * This,
    /* [in] */ short red_0,
    /* [in] */ short green_1,
    /* [in] */ short blue_2,
    /* [retval][out] */ IDAColor **ret_3);



HRESULT STDMETHODCALLTYPE IDAStatics_ColorHsl_Proxy( 
    IDAStatics * This,
    /* [in] */ double hue_0,
    /* [in] */ double saturation_1,
    /* [in] */ double lum_2,
    /* [retval][out] */ IDAColor **ret_3);



HRESULT STDMETHODCALLTYPE IDAStatics_ColorHslAnim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *hue_0,
    /* [in] */ IDANumber *saturation_1,
    /* [in] */ IDANumber *lum_2,
    /* [retval][out] */ IDAColor **ret_3);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_Red_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAColor **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_Green_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAColor **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_Blue_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAColor **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_Cyan_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAColor **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_Magenta_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAColor **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_Yellow_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAColor **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_Black_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAColor **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_White_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAColor **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_Aqua_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAColor **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_Fuchsia_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAColor **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_Gray_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAColor **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_Lime_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAColor **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_Maroon_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAColor **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_Navy_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAColor **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_Olive_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAColor **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_Purple_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAColor **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_Silver_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAColor **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_Teal_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAColor **ret_0);



HRESULT STDMETHODCALLTYPE IDAStatics_Predicate_Proxy( 
    IDAStatics * This,
    /* [in] */ IDABoolean *b_0,
    /* [retval][out] */ IDAEvent **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_NotEvent_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAEvent *event_0,
    /* [retval][out] */ IDAEvent **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_AndEvent_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAEvent *e1_0,
    /* [in] */ IDAEvent *e2_1,
    /* [retval][out] */ IDAEvent **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_OrEvent_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAEvent *e1_0,
    /* [in] */ IDAEvent *e2_1,
    /* [retval][out] */ IDAEvent **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_ThenEvent_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAEvent *e1_0,
    /* [in] */ IDAEvent *e2_1,
    /* [retval][out] */ IDAEvent **ret_2);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_LeftButtonDown_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAEvent **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_LeftButtonUp_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAEvent **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_RightButtonDown_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAEvent **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_RightButtonUp_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAEvent **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_Always_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAEvent **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_Never_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAEvent **ret_0);



HRESULT STDMETHODCALLTYPE IDAStatics_TimerAnim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *n_0,
    /* [retval][out] */ IDAEvent **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Timer_Proxy( 
    IDAStatics * This,
    /* [in] */ double n_0,
    /* [retval][out] */ IDAEvent **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_AppTriggeredEvent_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAEvent **ret_0);



HRESULT STDMETHODCALLTYPE IDAStatics_ScriptCallback_Proxy( 
    IDAStatics * This,
    /* [in] */ BSTR obsolete1_0,
    /* [in] */ IDAEvent *obsolete2_1,
    /* [in] */ BSTR obsolete3_2,
    /* [retval][out] */ IDAEvent **ret_3);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_EmptyGeometry_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAGeometry **ret_0);



HRESULT STDMETHODCALLTYPE IDAStatics_UnionGeometry_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAGeometry *g1_0,
    /* [in] */ IDAGeometry *g2_1,
    /* [retval][out] */ IDAGeometry **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_UnionGeometryArrayEx_Proxy( 
    IDAStatics * This,
    /* [in] */ LONG imgs_0size,
    /* [size_is][in] */ IDAGeometry *imgs_0[  ],
    /* [retval][out] */ IDAGeometry **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_UnionGeometryArray_Proxy( 
    IDAStatics * This,
    /* [in] */ VARIANT imgs_0,
    /* [retval][out] */ IDAGeometry **ret_1);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_EmptyImage_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAImage **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_DetectableEmptyImage_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAImage **ret_0);



HRESULT STDMETHODCALLTYPE IDAStatics_SolidColorImage_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAColor *col_0,
    /* [retval][out] */ IDAImage **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_GradientPolygonEx_Proxy( 
    IDAStatics * This,
    /* [in] */ LONG points_0size,
    /* [size_is][in] */ IDAPoint2 *points_0[  ],
    /* [in] */ LONG colors_1size,
    /* [size_is][in] */ IDAColor *colors_1[  ],
    /* [retval][out] */ IDAImage **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_GradientPolygon_Proxy( 
    IDAStatics * This,
    /* [in] */ VARIANT points_0,
    /* [in] */ VARIANT colors_1,
    /* [retval][out] */ IDAImage **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_RadialGradientPolygonEx_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAColor *inner_0,
    /* [in] */ IDAColor *outer_1,
    /* [in] */ LONG points_2size,
    /* [size_is][in] */ IDAPoint2 *points_2[  ],
    /* [in] */ double fallOff_3,
    /* [retval][out] */ IDAImage **ret_4);



HRESULT STDMETHODCALLTYPE IDAStatics_RadialGradientPolygon_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAColor *inner_0,
    /* [in] */ IDAColor *outer_1,
    /* [in] */ VARIANT points_2,
    /* [in] */ double fallOff_3,
    /* [retval][out] */ IDAImage **ret_4);



HRESULT STDMETHODCALLTYPE IDAStatics_RadialGradientPolygonAnimEx_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAColor *inner_0,
    /* [in] */ IDAColor *outer_1,
    /* [in] */ LONG points_2size,
    /* [size_is][in] */ IDAPoint2 *points_2[  ],
    /* [in] */ IDANumber *fallOff_3,
    /* [retval][out] */ IDAImage **ret_4);



HRESULT STDMETHODCALLTYPE IDAStatics_RadialGradientPolygonAnim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAColor *inner_0,
    /* [in] */ IDAColor *outer_1,
    /* [in] */ VARIANT points_2,
    /* [in] */ IDANumber *fallOff_3,
    /* [retval][out] */ IDAImage **ret_4);



HRESULT STDMETHODCALLTYPE IDAStatics_GradientSquare_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAColor *lowerLeft_0,
    /* [in] */ IDAColor *upperLeft_1,
    /* [in] */ IDAColor *upperRight_2,
    /* [in] */ IDAColor *lowerRight_3,
    /* [retval][out] */ IDAImage **ret_4);



HRESULT STDMETHODCALLTYPE IDAStatics_RadialGradientSquare_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAColor *inner_0,
    /* [in] */ IDAColor *outer_1,
    /* [in] */ double fallOff_2,
    /* [retval][out] */ IDAImage **ret_3);



HRESULT STDMETHODCALLTYPE IDAStatics_RadialGradientSquareAnim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAColor *inner_0,
    /* [in] */ IDAColor *outer_1,
    /* [in] */ IDANumber *fallOff_2,
    /* [retval][out] */ IDAImage **ret_3);



HRESULT STDMETHODCALLTYPE IDAStatics_RadialGradientRegularPoly_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAColor *inner_0,
    /* [in] */ IDAColor *outer_1,
    /* [in] */ double numEdges_2,
    /* [in] */ double fallOff_3,
    /* [retval][out] */ IDAImage **ret_4);



HRESULT STDMETHODCALLTYPE IDAStatics_RadialGradientRegularPolyAnim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAColor *inner_0,
    /* [in] */ IDAColor *outer_1,
    /* [in] */ IDANumber *numEdges_2,
    /* [in] */ IDANumber *fallOff_3,
    /* [retval][out] */ IDAImage **ret_4);



HRESULT STDMETHODCALLTYPE IDAStatics_GradientHorizontal_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAColor *start_0,
    /* [in] */ IDAColor *stop_1,
    /* [in] */ double fallOff_2,
    /* [retval][out] */ IDAImage **ret_3);



HRESULT STDMETHODCALLTYPE IDAStatics_GradientHorizontalAnim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAColor *start_0,
    /* [in] */ IDAColor *stop_1,
    /* [in] */ IDANumber *fallOff_2,
    /* [retval][out] */ IDAImage **ret_3);



HRESULT STDMETHODCALLTYPE IDAStatics_HatchHorizontal_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAColor *lineClr_0,
    /* [in] */ double spacing_1,
    /* [retval][out] */ IDAImage **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_HatchHorizontalAnim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAColor *lineClr_0,
    /* [in] */ IDANumber *spacing_1,
    /* [retval][out] */ IDAImage **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_HatchVertical_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAColor *lineClr_0,
    /* [in] */ double spacing_1,
    /* [retval][out] */ IDAImage **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_HatchVerticalAnim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAColor *lineClr_0,
    /* [in] */ IDANumber *spacing_1,
    /* [retval][out] */ IDAImage **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_HatchForwardDiagonal_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAColor *lineClr_0,
    /* [in] */ double spacing_1,
    /* [retval][out] */ IDAImage **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_HatchForwardDiagonalAnim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAColor *lineClr_0,
    /* [in] */ IDANumber *spacing_1,
    /* [retval][out] */ IDAImage **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_HatchBackwardDiagonal_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAColor *lineClr_0,
    /* [in] */ double spacing_1,
    /* [retval][out] */ IDAImage **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_HatchBackwardDiagonalAnim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAColor *lineClr_0,
    /* [in] */ IDANumber *spacing_1,
    /* [retval][out] */ IDAImage **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_HatchCross_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAColor *lineClr_0,
    /* [in] */ double spacing_1,
    /* [retval][out] */ IDAImage **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_HatchCrossAnim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAColor *lineClr_0,
    /* [in] */ IDANumber *spacing_1,
    /* [retval][out] */ IDAImage **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_HatchDiagonalCross_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAColor *lineClr_0,
    /* [in] */ double spacing_1,
    /* [retval][out] */ IDAImage **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_HatchDiagonalCrossAnim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAColor *lineClr_0,
    /* [in] */ IDANumber *spacing_1,
    /* [retval][out] */ IDAImage **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_Overlay_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAImage *top_0,
    /* [in] */ IDAImage *bottom_1,
    /* [retval][out] */ IDAImage **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_OverlayArrayEx_Proxy( 
    IDAStatics * This,
    /* [in] */ LONG imgs_0size,
    /* [size_is][in] */ IDAImage *imgs_0[  ],
    /* [retval][out] */ IDAImage **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_OverlayArray_Proxy( 
    IDAStatics * This,
    /* [in] */ VARIANT imgs_0,
    /* [retval][out] */ IDAImage **ret_1);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_AmbientLight_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAGeometry **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_DirectionalLight_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAGeometry **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_PointLight_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAGeometry **ret_0);



HRESULT STDMETHODCALLTYPE IDAStatics_SpotLightAnim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *fullcone_0,
    /* [in] */ IDANumber *cutoff_1,
    /* [retval][out] */ IDAGeometry **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_SpotLight_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *fullcone_0,
    /* [in] */ double cutoff_1,
    /* [retval][out] */ IDAGeometry **ret_2);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_DefaultLineStyle_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDALineStyle **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_EmptyLineStyle_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDALineStyle **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_JoinStyleBevel_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAJoinStyle **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_JoinStyleRound_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAJoinStyle **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_JoinStyleMiter_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAJoinStyle **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_EndStyleFlat_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAEndStyle **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_EndStyleSquare_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAEndStyle **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_EndStyleRound_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAEndStyle **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_DashStyleSolid_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDADashStyle **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_DashStyleDashed_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDADashStyle **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_DefaultMicrophone_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAMicrophone **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_OpaqueMatte_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAMatte **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_ClearMatte_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAMatte **ret_0);



HRESULT STDMETHODCALLTYPE IDAStatics_UnionMatte_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAMatte *m1_0,
    /* [in] */ IDAMatte *m2_1,
    /* [retval][out] */ IDAMatte **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_IntersectMatte_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAMatte *m1_0,
    /* [in] */ IDAMatte *m2_1,
    /* [retval][out] */ IDAMatte **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_DifferenceMatte_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAMatte *m1_0,
    /* [in] */ IDAMatte *m2_1,
    /* [retval][out] */ IDAMatte **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_FillMatte_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAPath2 *p_0,
    /* [retval][out] */ IDAMatte **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_TextMatte_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAString *str_0,
    /* [in] */ IDAFontStyle *fs_1,
    /* [retval][out] */ IDAMatte **ret_2);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_EmptyMontage_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAMontage **ret_0);



HRESULT STDMETHODCALLTYPE IDAStatics_ImageMontage_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAImage *im_0,
    /* [in] */ double depth_1,
    /* [retval][out] */ IDAMontage **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_ImageMontageAnim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAImage *im_0,
    /* [in] */ IDANumber *depth_1,
    /* [retval][out] */ IDAMontage **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_UnionMontage_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAMontage *m1_0,
    /* [in] */ IDAMontage *m2_1,
    /* [retval][out] */ IDAMontage **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_Concat_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAPath2 *p1_0,
    /* [in] */ IDAPath2 *p2_1,
    /* [retval][out] */ IDAPath2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_ConcatArrayEx_Proxy( 
    IDAStatics * This,
    /* [in] */ LONG paths_0size,
    /* [size_is][in] */ IDAPath2 *paths_0[  ],
    /* [retval][out] */ IDAPath2 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_ConcatArray_Proxy( 
    IDAStatics * This,
    /* [in] */ VARIANT paths_0,
    /* [retval][out] */ IDAPath2 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Line_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAPoint2 *p1_0,
    /* [in] */ IDAPoint2 *p2_1,
    /* [retval][out] */ IDAPath2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_Ray_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAPoint2 *pt_0,
    /* [retval][out] */ IDAPath2 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_StringPathAnim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAString *str_0,
    /* [in] */ IDAFontStyle *fs_1,
    /* [retval][out] */ IDAPath2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_StringPath_Proxy( 
    IDAStatics * This,
    /* [in] */ BSTR str_0,
    /* [in] */ IDAFontStyle *fs_1,
    /* [retval][out] */ IDAPath2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_PolylineEx_Proxy( 
    IDAStatics * This,
    /* [in] */ LONG points_0size,
    /* [size_is][in] */ IDAPoint2 *points_0[  ],
    /* [retval][out] */ IDAPath2 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Polyline_Proxy( 
    IDAStatics * This,
    /* [in] */ VARIANT points_0,
    /* [retval][out] */ IDAPath2 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_PolydrawPathEx_Proxy( 
    IDAStatics * This,
    /* [in] */ LONG points_0size,
    /* [size_is][in] */ IDAPoint2 *points_0[  ],
    /* [in] */ LONG codes_1size,
    /* [size_is][in] */ IDANumber *codes_1[  ],
    /* [retval][out] */ IDAPath2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_PolydrawPath_Proxy( 
    IDAStatics * This,
    /* [in] */ VARIANT points_0,
    /* [in] */ VARIANT codes_1,
    /* [retval][out] */ IDAPath2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_ArcRadians_Proxy( 
    IDAStatics * This,
    /* [in] */ double startAngle_0,
    /* [in] */ double endAngle_1,
    /* [in] */ double arcWidth_2,
    /* [in] */ double arcHeight_3,
    /* [retval][out] */ IDAPath2 **ret_4);



HRESULT STDMETHODCALLTYPE IDAStatics_ArcRadiansAnim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *startAngle_0,
    /* [in] */ IDANumber *endAngle_1,
    /* [in] */ IDANumber *arcWidth_2,
    /* [in] */ IDANumber *arcHeight_3,
    /* [retval][out] */ IDAPath2 **ret_4);



HRESULT STDMETHODCALLTYPE IDAStatics_ArcDegrees_Proxy( 
    IDAStatics * This,
    /* [in] */ double startAngle_0,
    /* [in] */ double endAngle_1,
    /* [in] */ double arcWidth_2,
    /* [in] */ double arcHeight_3,
    /* [retval][out] */ IDAPath2 **ret_4);



HRESULT STDMETHODCALLTYPE IDAStatics_PieRadians_Proxy( 
    IDAStatics * This,
    /* [in] */ double startAngle_0,
    /* [in] */ double endAngle_1,
    /* [in] */ double arcWidth_2,
    /* [in] */ double arcHeight_3,
    /* [retval][out] */ IDAPath2 **ret_4);



HRESULT STDMETHODCALLTYPE IDAStatics_PieRadiansAnim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *startAngle_0,
    /* [in] */ IDANumber *endAngle_1,
    /* [in] */ IDANumber *arcWidth_2,
    /* [in] */ IDANumber *arcHeight_3,
    /* [retval][out] */ IDAPath2 **ret_4);



HRESULT STDMETHODCALLTYPE IDAStatics_PieDegrees_Proxy( 
    IDAStatics * This,
    /* [in] */ double startAngle_0,
    /* [in] */ double endAngle_1,
    /* [in] */ double arcWidth_2,
    /* [in] */ double arcHeight_3,
    /* [retval][out] */ IDAPath2 **ret_4);



HRESULT STDMETHODCALLTYPE IDAStatics_Oval_Proxy( 
    IDAStatics * This,
    /* [in] */ double width_0,
    /* [in] */ double height_1,
    /* [retval][out] */ IDAPath2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_OvalAnim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *width_0,
    /* [in] */ IDANumber *height_1,
    /* [retval][out] */ IDAPath2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_Rect_Proxy( 
    IDAStatics * This,
    /* [in] */ double width_0,
    /* [in] */ double height_1,
    /* [retval][out] */ IDAPath2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_RectAnim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *width_0,
    /* [in] */ IDANumber *height_1,
    /* [retval][out] */ IDAPath2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_RoundRect_Proxy( 
    IDAStatics * This,
    /* [in] */ double width_0,
    /* [in] */ double height_1,
    /* [in] */ double cornerArcWidth_2,
    /* [in] */ double cornerArcHeight_3,
    /* [retval][out] */ IDAPath2 **ret_4);



HRESULT STDMETHODCALLTYPE IDAStatics_RoundRectAnim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *width_0,
    /* [in] */ IDANumber *height_1,
    /* [in] */ IDANumber *cornerArcWidth_2,
    /* [in] */ IDANumber *cornerArcHeight_3,
    /* [retval][out] */ IDAPath2 **ret_4);



HRESULT STDMETHODCALLTYPE IDAStatics_CubicBSplinePathEx_Proxy( 
    IDAStatics * This,
    /* [in] */ LONG points_0size,
    /* [size_is][in] */ IDAPoint2 *points_0[  ],
    /* [in] */ LONG knots_1size,
    /* [size_is][in] */ IDANumber *knots_1[  ],
    /* [retval][out] */ IDAPath2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_CubicBSplinePath_Proxy( 
    IDAStatics * This,
    /* [in] */ VARIANT points_0,
    /* [in] */ VARIANT knots_1,
    /* [retval][out] */ IDAPath2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_TextPath_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAString *obsolete1_0,
    /* [in] */ IDAFontStyle *obsolete2_1,
    /* [retval][out] */ IDAPath2 **ret_2);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_Silence_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDASound **ret_0);



HRESULT STDMETHODCALLTYPE IDAStatics_MixArrayEx_Proxy( 
    IDAStatics * This,
    /* [in] */ LONG snds_0size,
    /* [size_is][in] */ IDASound *snds_0[  ],
    /* [retval][out] */ IDASound **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_MixArray_Proxy( 
    IDAStatics * This,
    /* [in] */ VARIANT snds_0,
    /* [retval][out] */ IDASound **ret_1);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_SinSynth_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDASound **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_DefaultFont_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAFontStyle **ret_0);



HRESULT STDMETHODCALLTYPE IDAStatics_FontAnim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAString *str_0,
    /* [in] */ IDANumber *size_1,
    /* [in] */ IDAColor *col_2,
    /* [retval][out] */ IDAFontStyle **ret_3);



HRESULT STDMETHODCALLTYPE IDAStatics_Font_Proxy( 
    IDAStatics * This,
    /* [in] */ BSTR str_0,
    /* [in] */ double size_1,
    /* [in] */ IDAColor *col_2,
    /* [retval][out] */ IDAFontStyle **ret_3);



HRESULT STDMETHODCALLTYPE IDAStatics_StringImageAnim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAString *str_0,
    /* [in] */ IDAFontStyle *fs_1,
    /* [retval][out] */ IDAImage **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_StringImage_Proxy( 
    IDAStatics * This,
    /* [in] */ BSTR str_0,
    /* [in] */ IDAFontStyle *fs_1,
    /* [retval][out] */ IDAImage **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_TextImageAnim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAString *obsoleted1_0,
    /* [in] */ IDAFontStyle *obsoleted2_1,
    /* [retval][out] */ IDAImage **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_TextImage_Proxy( 
    IDAStatics * This,
    /* [in] */ BSTR obsoleted1_0,
    /* [in] */ IDAFontStyle *obsoleted2_1,
    /* [retval][out] */ IDAImage **ret_2);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_XVector2_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAVector2 **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_YVector2_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAVector2 **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_ZeroVector2_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAVector2 **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_Origin2_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAPoint2 **ret_0);



HRESULT STDMETHODCALLTYPE IDAStatics_Vector2Anim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *x_0,
    /* [in] */ IDANumber *y_1,
    /* [retval][out] */ IDAVector2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_Vector2_Proxy( 
    IDAStatics * This,
    /* [in] */ double x_0,
    /* [in] */ double y_1,
    /* [retval][out] */ IDAVector2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_Point2Anim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *x_0,
    /* [in] */ IDANumber *y_1,
    /* [retval][out] */ IDAPoint2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_Point2_Proxy( 
    IDAStatics * This,
    /* [in] */ double x_0,
    /* [in] */ double y_1,
    /* [retval][out] */ IDAPoint2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_Vector2PolarAnim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *theta_0,
    /* [in] */ IDANumber *radius_1,
    /* [retval][out] */ IDAVector2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_Vector2Polar_Proxy( 
    IDAStatics * This,
    /* [in] */ double theta_0,
    /* [in] */ double radius_1,
    /* [retval][out] */ IDAVector2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_Vector2PolarDegrees_Proxy( 
    IDAStatics * This,
    /* [in] */ double theta_0,
    /* [in] */ double radius_1,
    /* [retval][out] */ IDAVector2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_Point2PolarAnim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *theta_0,
    /* [in] */ IDANumber *radius_1,
    /* [retval][out] */ IDAPoint2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_Point2Polar_Proxy( 
    IDAStatics * This,
    /* [in] */ double theta_0,
    /* [in] */ double radius_1,
    /* [retval][out] */ IDAPoint2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_DotVector2_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAVector2 *v_0,
    /* [in] */ IDAVector2 *u_1,
    /* [retval][out] */ IDANumber **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_NegVector2_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAVector2 *v_0,
    /* [retval][out] */ IDAVector2 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_SubVector2_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAVector2 *v1_0,
    /* [in] */ IDAVector2 *v2_1,
    /* [retval][out] */ IDAVector2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_AddVector2_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAVector2 *v1_0,
    /* [in] */ IDAVector2 *v2_1,
    /* [retval][out] */ IDAVector2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_AddPoint2Vector_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAPoint2 *p_0,
    /* [in] */ IDAVector2 *v_1,
    /* [retval][out] */ IDAPoint2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_SubPoint2Vector_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAPoint2 *p_0,
    /* [in] */ IDAVector2 *v_1,
    /* [retval][out] */ IDAPoint2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_SubPoint2_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAPoint2 *p1_0,
    /* [in] */ IDAPoint2 *p2_1,
    /* [retval][out] */ IDAVector2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_DistancePoint2_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAPoint2 *p_0,
    /* [in] */ IDAPoint2 *q_1,
    /* [retval][out] */ IDANumber **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_DistanceSquaredPoint2_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAPoint2 *p_0,
    /* [in] */ IDAPoint2 *q_1,
    /* [retval][out] */ IDANumber **ret_2);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_XVector3_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAVector3 **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_YVector3_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAVector3 **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_ZVector3_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAVector3 **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_ZeroVector3_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAVector3 **ret_0);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_Origin3_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDAPoint3 **ret_0);



HRESULT STDMETHODCALLTYPE IDAStatics_Vector3Anim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *x_0,
    /* [in] */ IDANumber *y_1,
    /* [in] */ IDANumber *z_2,
    /* [retval][out] */ IDAVector3 **ret_3);



HRESULT STDMETHODCALLTYPE IDAStatics_Vector3_Proxy( 
    IDAStatics * This,
    /* [in] */ double x_0,
    /* [in] */ double y_1,
    /* [in] */ double z_2,
    /* [retval][out] */ IDAVector3 **ret_3);



HRESULT STDMETHODCALLTYPE IDAStatics_Point3Anim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *x_0,
    /* [in] */ IDANumber *y_1,
    /* [in] */ IDANumber *z_2,
    /* [retval][out] */ IDAPoint3 **ret_3);



HRESULT STDMETHODCALLTYPE IDAStatics_Point3_Proxy( 
    IDAStatics * This,
    /* [in] */ double x_0,
    /* [in] */ double y_1,
    /* [in] */ double z_2,
    /* [retval][out] */ IDAPoint3 **ret_3);



HRESULT STDMETHODCALLTYPE IDAStatics_Vector3SphericalAnim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *xyAngle_0,
    /* [in] */ IDANumber *yzAngle_1,
    /* [in] */ IDANumber *radius_2,
    /* [retval][out] */ IDAVector3 **ret_3);



HRESULT STDMETHODCALLTYPE IDAStatics_Vector3Spherical_Proxy( 
    IDAStatics * This,
    /* [in] */ double xyAngle_0,
    /* [in] */ double yzAngle_1,
    /* [in] */ double radius_2,
    /* [retval][out] */ IDAVector3 **ret_3);



HRESULT STDMETHODCALLTYPE IDAStatics_Point3SphericalAnim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *zxAngle_0,
    /* [in] */ IDANumber *xyAngle_1,
    /* [in] */ IDANumber *radius_2,
    /* [retval][out] */ IDAPoint3 **ret_3);



HRESULT STDMETHODCALLTYPE IDAStatics_Point3Spherical_Proxy( 
    IDAStatics * This,
    /* [in] */ double zxAngle_0,
    /* [in] */ double xyAngle_1,
    /* [in] */ double radius_2,
    /* [retval][out] */ IDAPoint3 **ret_3);



HRESULT STDMETHODCALLTYPE IDAStatics_DotVector3_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAVector3 *v_0,
    /* [in] */ IDAVector3 *u_1,
    /* [retval][out] */ IDANumber **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_CrossVector3_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAVector3 *v_0,
    /* [in] */ IDAVector3 *u_1,
    /* [retval][out] */ IDAVector3 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_NegVector3_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAVector3 *v_0,
    /* [retval][out] */ IDAVector3 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_SubVector3_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAVector3 *v1_0,
    /* [in] */ IDAVector3 *v2_1,
    /* [retval][out] */ IDAVector3 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_AddVector3_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAVector3 *v1_0,
    /* [in] */ IDAVector3 *v2_1,
    /* [retval][out] */ IDAVector3 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_AddPoint3Vector_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAPoint3 *p_0,
    /* [in] */ IDAVector3 *v_1,
    /* [retval][out] */ IDAPoint3 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_SubPoint3Vector_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAPoint3 *p_0,
    /* [in] */ IDAVector3 *v_1,
    /* [retval][out] */ IDAPoint3 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_SubPoint3_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAPoint3 *p1_0,
    /* [in] */ IDAPoint3 *p2_1,
    /* [retval][out] */ IDAVector3 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_DistancePoint3_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAPoint3 *p_0,
    /* [in] */ IDAPoint3 *q_1,
    /* [retval][out] */ IDANumber **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_DistanceSquaredPoint3_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAPoint3 *p_0,
    /* [in] */ IDAPoint3 *q_1,
    /* [retval][out] */ IDANumber **ret_2);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_IdentityTransform3_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDATransform3 **ret_0);



HRESULT STDMETHODCALLTYPE IDAStatics_Translate3Anim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *tx_0,
    /* [in] */ IDANumber *ty_1,
    /* [in] */ IDANumber *tz_2,
    /* [retval][out] */ IDATransform3 **ret_3);



HRESULT STDMETHODCALLTYPE IDAStatics_Translate3_Proxy( 
    IDAStatics * This,
    /* [in] */ double tx_0,
    /* [in] */ double ty_1,
    /* [in] */ double tz_2,
    /* [retval][out] */ IDATransform3 **ret_3);



HRESULT STDMETHODCALLTYPE IDAStatics_Translate3Rate_Proxy( 
    IDAStatics * This,
    /* [in] */ double tx_0,
    /* [in] */ double ty_1,
    /* [in] */ double tz_2,
    /* [retval][out] */ IDATransform3 **ret_3);



HRESULT STDMETHODCALLTYPE IDAStatics_Translate3Vector_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAVector3 *delta_0,
    /* [retval][out] */ IDATransform3 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Translate3Point_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAPoint3 *new_origin_0,
    /* [retval][out] */ IDATransform3 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Scale3Anim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *x_0,
    /* [in] */ IDANumber *y_1,
    /* [in] */ IDANumber *z_2,
    /* [retval][out] */ IDATransform3 **ret_3);



HRESULT STDMETHODCALLTYPE IDAStatics_Scale3_Proxy( 
    IDAStatics * This,
    /* [in] */ double x_0,
    /* [in] */ double y_1,
    /* [in] */ double z_2,
    /* [retval][out] */ IDATransform3 **ret_3);



HRESULT STDMETHODCALLTYPE IDAStatics_Scale3Rate_Proxy( 
    IDAStatics * This,
    /* [in] */ double x_0,
    /* [in] */ double y_1,
    /* [in] */ double z_2,
    /* [retval][out] */ IDATransform3 **ret_3);



HRESULT STDMETHODCALLTYPE IDAStatics_Scale3Vector_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAVector3 *scale_vec_0,
    /* [retval][out] */ IDATransform3 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Scale3UniformAnim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *uniform_scale_0,
    /* [retval][out] */ IDATransform3 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Scale3Uniform_Proxy( 
    IDAStatics * This,
    /* [in] */ double uniform_scale_0,
    /* [retval][out] */ IDATransform3 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Scale3UniformRate_Proxy( 
    IDAStatics * This,
    /* [in] */ double uniform_scale_0,
    /* [retval][out] */ IDATransform3 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Rotate3Anim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAVector3 *axis_0,
    /* [in] */ IDANumber *angle_1,
    /* [retval][out] */ IDATransform3 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_Rotate3_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAVector3 *axis_0,
    /* [in] */ double angle_1,
    /* [retval][out] */ IDATransform3 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_Rotate3Rate_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAVector3 *axis_0,
    /* [in] */ double angle_1,
    /* [retval][out] */ IDATransform3 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_Rotate3Degrees_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAVector3 *axis_0,
    /* [in] */ double angle_1,
    /* [retval][out] */ IDATransform3 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_Rotate3RateDegrees_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAVector3 *axis_0,
    /* [in] */ double angle_1,
    /* [retval][out] */ IDATransform3 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_XShear3Anim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *a_0,
    /* [in] */ IDANumber *b_1,
    /* [retval][out] */ IDATransform3 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_XShear3_Proxy( 
    IDAStatics * This,
    /* [in] */ double a_0,
    /* [in] */ double b_1,
    /* [retval][out] */ IDATransform3 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_XShear3Rate_Proxy( 
    IDAStatics * This,
    /* [in] */ double a_0,
    /* [in] */ double b_1,
    /* [retval][out] */ IDATransform3 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_YShear3Anim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *c_0,
    /* [in] */ IDANumber *d_1,
    /* [retval][out] */ IDATransform3 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_YShear3_Proxy( 
    IDAStatics * This,
    /* [in] */ double c_0,
    /* [in] */ double d_1,
    /* [retval][out] */ IDATransform3 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_YShear3Rate_Proxy( 
    IDAStatics * This,
    /* [in] */ double c_0,
    /* [in] */ double d_1,
    /* [retval][out] */ IDATransform3 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_ZShear3Anim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *e_0,
    /* [in] */ IDANumber *f_1,
    /* [retval][out] */ IDATransform3 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_ZShear3_Proxy( 
    IDAStatics * This,
    /* [in] */ double e_0,
    /* [in] */ double f_1,
    /* [retval][out] */ IDATransform3 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_ZShear3Rate_Proxy( 
    IDAStatics * This,
    /* [in] */ double e_0,
    /* [in] */ double f_1,
    /* [retval][out] */ IDATransform3 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_Transform4x4AnimEx_Proxy( 
    IDAStatics * This,
    /* [in] */ LONG m_0size,
    /* [size_is][in] */ IDANumber *m_0[  ],
    /* [retval][out] */ IDATransform3 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Transform4x4Anim_Proxy( 
    IDAStatics * This,
    /* [in] */ VARIANT m_0,
    /* [retval][out] */ IDATransform3 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Compose3_Proxy( 
    IDAStatics * This,
    /* [in] */ IDATransform3 *a_0,
    /* [in] */ IDATransform3 *b_1,
    /* [retval][out] */ IDATransform3 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_Compose3ArrayEx_Proxy( 
    IDAStatics * This,
    /* [in] */ LONG xfs_0size,
    /* [size_is][in] */ IDATransform3 *xfs_0[  ],
    /* [retval][out] */ IDATransform3 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Compose3Array_Proxy( 
    IDAStatics * This,
    /* [in] */ VARIANT xfs_0,
    /* [retval][out] */ IDATransform3 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_LookAtFrom_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAPoint3 *to_0,
    /* [in] */ IDAPoint3 *from_1,
    /* [in] */ IDAVector3 *up_2,
    /* [retval][out] */ IDATransform3 **ret_3);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_IdentityTransform2_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ IDATransform2 **ret_0);



HRESULT STDMETHODCALLTYPE IDAStatics_Translate2Anim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *Tx_0,
    /* [in] */ IDANumber *Ty_1,
    /* [retval][out] */ IDATransform2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_Translate2_Proxy( 
    IDAStatics * This,
    /* [in] */ double Tx_0,
    /* [in] */ double Ty_1,
    /* [retval][out] */ IDATransform2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_Translate2Rate_Proxy( 
    IDAStatics * This,
    /* [in] */ double Tx_0,
    /* [in] */ double Ty_1,
    /* [retval][out] */ IDATransform2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_Translate2Vector_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAVector2 *delta_0,
    /* [retval][out] */ IDATransform2 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Translate2Point_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAPoint2 *pos_0,
    /* [retval][out] */ IDATransform2 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Scale2Anim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *x_0,
    /* [in] */ IDANumber *y_1,
    /* [retval][out] */ IDATransform2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_Scale2_Proxy( 
    IDAStatics * This,
    /* [in] */ double x_0,
    /* [in] */ double y_1,
    /* [retval][out] */ IDATransform2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_Scale2Rate_Proxy( 
    IDAStatics * This,
    /* [in] */ double x_0,
    /* [in] */ double y_1,
    /* [retval][out] */ IDATransform2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_Scale2Vector2_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAVector2 *obsoleteMethod_0,
    /* [retval][out] */ IDATransform2 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Scale2Vector_Proxy( 
    IDAStatics * This,
    /* [in] */ IDAVector2 *scale_vec_0,
    /* [retval][out] */ IDATransform2 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Scale2UniformAnim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *uniform_scale_0,
    /* [retval][out] */ IDATransform2 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Scale2Uniform_Proxy( 
    IDAStatics * This,
    /* [in] */ double uniform_scale_0,
    /* [retval][out] */ IDATransform2 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Scale2UniformRate_Proxy( 
    IDAStatics * This,
    /* [in] */ double uniform_scale_0,
    /* [retval][out] */ IDATransform2 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Rotate2Anim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *angle_0,
    /* [retval][out] */ IDATransform2 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Rotate2_Proxy( 
    IDAStatics * This,
    /* [in] */ double angle_0,
    /* [retval][out] */ IDATransform2 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Rotate2Rate_Proxy( 
    IDAStatics * This,
    /* [in] */ double angle_0,
    /* [retval][out] */ IDATransform2 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Rotate2Degrees_Proxy( 
    IDAStatics * This,
    /* [in] */ double angle_0,
    /* [retval][out] */ IDATransform2 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Rotate2RateDegrees_Proxy( 
    IDAStatics * This,
    /* [in] */ double angle_0,
    /* [retval][out] */ IDATransform2 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_XShear2Anim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *arg_0,
    /* [retval][out] */ IDATransform2 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_XShear2_Proxy( 
    IDAStatics * This,
    /* [in] */ double arg_0,
    /* [retval][out] */ IDATransform2 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_XShear2Rate_Proxy( 
    IDAStatics * This,
    /* [in] */ double arg_0,
    /* [retval][out] */ IDATransform2 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_YShear2Anim_Proxy( 
    IDAStatics * This,
    /* [in] */ IDANumber *arg_0,
    /* [retval][out] */ IDATransform2 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_YShear2_Proxy( 
    IDAStatics * This,
    /* [in] */ double arg_0,
    /* [retval][out] */ IDATransform2 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_YShear2Rate_Proxy( 
    IDAStatics * This,
    /* [in] */ double arg_0,
    /* [retval][out] */ IDATransform2 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Transform3x2AnimEx_Proxy( 
    IDAStatics * This,
    /* [in] */ LONG m_0size,
    /* [size_is][in] */ IDANumber *m_0[  ],
    /* [retval][out] */ IDATransform2 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Transform3x2Anim_Proxy( 
    IDAStatics * This,
    /* [in] */ VARIANT m_0,
    /* [retval][out] */ IDATransform2 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Compose2_Proxy( 
    IDAStatics * This,
    /* [in] */ IDATransform2 *a_0,
    /* [in] */ IDATransform2 *b_1,
    /* [retval][out] */ IDATransform2 **ret_2);



HRESULT STDMETHODCALLTYPE IDAStatics_Compose2ArrayEx_Proxy( 
    IDAStatics * This,
    /* [in] */ LONG xfs_0size,
    /* [size_is][in] */ IDATransform2 *xfs_0[  ],
    /* [retval][out] */ IDATransform2 **ret_1);



HRESULT STDMETHODCALLTYPE IDAStatics_Compose2Array_Proxy( 
    IDAStatics * This,
    /* [in] */ VARIANT xfs_0,
    /* [retval][out] */ IDATransform2 **ret_1);



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDAStatics_Tuple_Proxy( 
    IDAStatics * This,
    /* [in] */ VARIANT obsolete1,
    /* [retval][out] */ IDATuple **obsolete2);



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDAStatics_Array_Proxy( 
    IDAStatics * This,
    /* [in] */ VARIANT obsolete1,
    /* [retval][out] */ IDAArray **obsolete2);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAStatics_get_AreBlockingImportsComplete_Proxy( 
    IDAStatics * This,
    /* [retval][out] */ VARIANT_BOOL *bComplete);




#endif 	/* __IDAStatics_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_DAStatics;

#ifdef __cplusplus

class DECLSPEC_UUID("542FB453-5003-11cf-92A2-00AA00B8A733")
DAStatics;
#endif

#ifndef __IDAViewerControl_INTERFACE_DEFINED__
#define __IDAViewerControl_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDAViewerControl
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IDAViewerControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0E41257B-812D-11D0-9B4A-00C04FC2F51D")
    IDAViewerControl : public IDispatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_UpdateInterval( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_UpdateInterval( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_View( 
            /* [retval][out] */ IDAView **ppView) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_View( 
            /* [in] */ IDAView *pView) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Image( 
            /* [retval][out] */ IDAImage **ppImage) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Image( 
            /* [in] */ IDAImage *pImage) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BackgroundImage( 
            /* [retval][out] */ IDAImage **ppImage) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_BackgroundImage( 
            /* [in] */ IDAImage *pImage) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Sound( 
            /* [retval][out] */ IDASound **ppSound) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Sound( 
            /* [in] */ IDASound *pSound) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PixelLibrary( 
            /* [retval][out] */ IDAStatics **ppStatics) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MeterLibrary( 
            /* [retval][out] */ IDAStatics **ppStatics) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddBehaviorToRun( 
            /* [in] */ IDABehavior *pBehavior) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Start( void) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_InputImage( 
            /* [retval][out] */ IDAImage **pVal) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_OpaqueForHitDetect( 
            /* [retval][out] */ VARIANT_BOOL *b) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_OpaqueForHitDetect( 
            /* [in] */ VARIANT_BOOL b) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_TimerSource( 
            /* [retval][out] */ DA_TIMER_SOURCE *ts) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_TimerSource( 
            /* [in] */ DA_TIMER_SOURCE ts) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDAViewerControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDAViewerControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDAViewerControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDAViewerControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDAViewerControl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDAViewerControl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDAViewerControl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDAViewerControl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UpdateInterval )( 
            IDAViewerControl * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UpdateInterval )( 
            IDAViewerControl * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_View )( 
            IDAViewerControl * This,
            /* [retval][out] */ IDAView **ppView);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_View )( 
            IDAViewerControl * This,
            /* [in] */ IDAView *pView);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Image )( 
            IDAViewerControl * This,
            /* [retval][out] */ IDAImage **ppImage);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Image )( 
            IDAViewerControl * This,
            /* [in] */ IDAImage *pImage);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackgroundImage )( 
            IDAViewerControl * This,
            /* [retval][out] */ IDAImage **ppImage);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BackgroundImage )( 
            IDAViewerControl * This,
            /* [in] */ IDAImage *pImage);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Sound )( 
            IDAViewerControl * This,
            /* [retval][out] */ IDASound **ppSound);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Sound )( 
            IDAViewerControl * This,
            /* [in] */ IDASound *pSound);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PixelLibrary )( 
            IDAViewerControl * This,
            /* [retval][out] */ IDAStatics **ppStatics);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MeterLibrary )( 
            IDAViewerControl * This,
            /* [retval][out] */ IDAStatics **ppStatics);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddBehaviorToRun )( 
            IDAViewerControl * This,
            /* [in] */ IDABehavior *pBehavior);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Start )( 
            IDAViewerControl * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InputImage )( 
            IDAViewerControl * This,
            /* [retval][out] */ IDAImage **pVal);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_OpaqueForHitDetect )( 
            IDAViewerControl * This,
            /* [retval][out] */ VARIANT_BOOL *b);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_OpaqueForHitDetect )( 
            IDAViewerControl * This,
            /* [in] */ VARIANT_BOOL b);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_TimerSource )( 
            IDAViewerControl * This,
            /* [retval][out] */ DA_TIMER_SOURCE *ts);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_TimerSource )( 
            IDAViewerControl * This,
            /* [in] */ DA_TIMER_SOURCE ts);
        
        END_INTERFACE
    } IDAViewerControlVtbl;

    interface IDAViewerControl
    {
        CONST_VTBL struct IDAViewerControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDAViewerControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDAViewerControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDAViewerControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDAViewerControl_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDAViewerControl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDAViewerControl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDAViewerControl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDAViewerControl_get_UpdateInterval(This,pVal)	\
    (This)->lpVtbl -> get_UpdateInterval(This,pVal)

#define IDAViewerControl_put_UpdateInterval(This,newVal)	\
    (This)->lpVtbl -> put_UpdateInterval(This,newVal)

#define IDAViewerControl_get_View(This,ppView)	\
    (This)->lpVtbl -> get_View(This,ppView)

#define IDAViewerControl_put_View(This,pView)	\
    (This)->lpVtbl -> put_View(This,pView)

#define IDAViewerControl_get_Image(This,ppImage)	\
    (This)->lpVtbl -> get_Image(This,ppImage)

#define IDAViewerControl_put_Image(This,pImage)	\
    (This)->lpVtbl -> put_Image(This,pImage)

#define IDAViewerControl_get_BackgroundImage(This,ppImage)	\
    (This)->lpVtbl -> get_BackgroundImage(This,ppImage)

#define IDAViewerControl_put_BackgroundImage(This,pImage)	\
    (This)->lpVtbl -> put_BackgroundImage(This,pImage)

#define IDAViewerControl_get_Sound(This,ppSound)	\
    (This)->lpVtbl -> get_Sound(This,ppSound)

#define IDAViewerControl_put_Sound(This,pSound)	\
    (This)->lpVtbl -> put_Sound(This,pSound)

#define IDAViewerControl_get_PixelLibrary(This,ppStatics)	\
    (This)->lpVtbl -> get_PixelLibrary(This,ppStatics)

#define IDAViewerControl_get_MeterLibrary(This,ppStatics)	\
    (This)->lpVtbl -> get_MeterLibrary(This,ppStatics)

#define IDAViewerControl_AddBehaviorToRun(This,pBehavior)	\
    (This)->lpVtbl -> AddBehaviorToRun(This,pBehavior)

#define IDAViewerControl_Start(This)	\
    (This)->lpVtbl -> Start(This)

#define IDAViewerControl_get_InputImage(This,pVal)	\
    (This)->lpVtbl -> get_InputImage(This,pVal)

#define IDAViewerControl_get_OpaqueForHitDetect(This,b)	\
    (This)->lpVtbl -> get_OpaqueForHitDetect(This,b)

#define IDAViewerControl_put_OpaqueForHitDetect(This,b)	\
    (This)->lpVtbl -> put_OpaqueForHitDetect(This,b)

#define IDAViewerControl_get_TimerSource(This,ts)	\
    (This)->lpVtbl -> get_TimerSource(This,ts)

#define IDAViewerControl_put_TimerSource(This,ts)	\
    (This)->lpVtbl -> put_TimerSource(This,ts)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IDAViewerControl_get_UpdateInterval_Proxy( 
    IDAViewerControl * This,
    /* [retval][out] */ double *pVal);



/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IDAViewerControl_put_UpdateInterval_Proxy( 
    IDAViewerControl * This,
    /* [in] */ double newVal);



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IDAViewerControl_get_View_Proxy( 
    IDAViewerControl * This,
    /* [retval][out] */ IDAView **ppView);



/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IDAViewerControl_put_View_Proxy( 
    IDAViewerControl * This,
    /* [in] */ IDAView *pView);



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IDAViewerControl_get_Image_Proxy( 
    IDAViewerControl * This,
    /* [retval][out] */ IDAImage **ppImage);



/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IDAViewerControl_put_Image_Proxy( 
    IDAViewerControl * This,
    /* [in] */ IDAImage *pImage);



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IDAViewerControl_get_BackgroundImage_Proxy( 
    IDAViewerControl * This,
    /* [retval][out] */ IDAImage **ppImage);



/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IDAViewerControl_put_BackgroundImage_Proxy( 
    IDAViewerControl * This,
    /* [in] */ IDAImage *pImage);



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IDAViewerControl_get_Sound_Proxy( 
    IDAViewerControl * This,
    /* [retval][out] */ IDASound **ppSound);



/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IDAViewerControl_put_Sound_Proxy( 
    IDAViewerControl * This,
    /* [in] */ IDASound *pSound);



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IDAViewerControl_get_PixelLibrary_Proxy( 
    IDAViewerControl * This,
    /* [retval][out] */ IDAStatics **ppStatics);



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IDAViewerControl_get_MeterLibrary_Proxy( 
    IDAViewerControl * This,
    /* [retval][out] */ IDAStatics **ppStatics);



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDAViewerControl_AddBehaviorToRun_Proxy( 
    IDAViewerControl * This,
    /* [in] */ IDABehavior *pBehavior);



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDAViewerControl_Start_Proxy( 
    IDAViewerControl * This);



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IDAViewerControl_get_InputImage_Proxy( 
    IDAViewerControl * This,
    /* [retval][out] */ IDAImage **pVal);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAViewerControl_get_OpaqueForHitDetect_Proxy( 
    IDAViewerControl * This,
    /* [retval][out] */ VARIANT_BOOL *b);



/* [propput] */ HRESULT STDMETHODCALLTYPE IDAViewerControl_put_OpaqueForHitDetect_Proxy( 
    IDAViewerControl * This,
    /* [in] */ VARIANT_BOOL b);



/* [propget] */ HRESULT STDMETHODCALLTYPE IDAViewerControl_get_TimerSource_Proxy( 
    IDAViewerControl * This,
    /* [retval][out] */ DA_TIMER_SOURCE *ts);



/* [propput] */ HRESULT STDMETHODCALLTYPE IDAViewerControl_put_TimerSource_Proxy( 
    IDAViewerControl * This,
    /* [in] */ DA_TIMER_SOURCE ts);




#endif 	/* __IDAViewerControl_INTERFACE_DEFINED__ */


#ifndef __IDAViewerControlWindowed_INTERFACE_DEFINED__
#define __IDAViewerControlWindowed_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDAViewerControlWindowed
 * at Tue Nov 11 05:16:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IDAViewerControlWindowed;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("BA8B033E-1E91-11d1-8809-00C04FC29D46")
    IDAViewerControlWindowed : public IDAViewerControl
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IDAViewerControlWindowedVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDAViewerControlWindowed * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDAViewerControlWindowed * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDAViewerControlWindowed * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDAViewerControlWindowed * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDAViewerControlWindowed * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDAViewerControlWindowed * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDAViewerControlWindowed * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UpdateInterval )( 
            IDAViewerControlWindowed * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UpdateInterval )( 
            IDAViewerControlWindowed * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_View )( 
            IDAViewerControlWindowed * This,
            /* [retval][out] */ IDAView **ppView);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_View )( 
            IDAViewerControlWindowed * This,
            /* [in] */ IDAView *pView);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Image )( 
            IDAViewerControlWindowed * This,
            /* [retval][out] */ IDAImage **ppImage);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Image )( 
            IDAViewerControlWindowed * This,
            /* [in] */ IDAImage *pImage);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackgroundImage )( 
            IDAViewerControlWindowed * This,
            /* [retval][out] */ IDAImage **ppImage);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BackgroundImage )( 
            IDAViewerControlWindowed * This,
            /* [in] */ IDAImage *pImage);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Sound )( 
            IDAViewerControlWindowed * This,
            /* [retval][out] */ IDASound **ppSound);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Sound )( 
            IDAViewerControlWindowed * This,
            /* [in] */ IDASound *pSound);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PixelLibrary )( 
            IDAViewerControlWindowed * This,
            /* [retval][out] */ IDAStatics **ppStatics);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MeterLibrary )( 
            IDAViewerControlWindowed * This,
            /* [retval][out] */ IDAStatics **ppStatics);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddBehaviorToRun )( 
            IDAViewerControlWindowed * This,
            /* [in] */ IDABehavior *pBehavior);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Start )( 
            IDAViewerControlWindowed * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InputImage )( 
            IDAViewerControlWindowed * This,
            /* [retval][out] */ IDAImage **pVal);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_OpaqueForHitDetect )( 
            IDAViewerControlWindowed * This,
            /* [retval][out] */ VARIANT_BOOL *b);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_OpaqueForHitDetect )( 
            IDAViewerControlWindowed * This,
            /* [in] */ VARIANT_BOOL b);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_TimerSource )( 
            IDAViewerControlWindowed * This,
            /* [retval][out] */ DA_TIMER_SOURCE *ts);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_TimerSource )( 
            IDAViewerControlWindowed * This,
            /* [in] */ DA_TIMER_SOURCE ts);
        
        END_INTERFACE
    } IDAViewerControlWindowedVtbl;

    interface IDAViewerControlWindowed
    {
        CONST_VTBL struct IDAViewerControlWindowedVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDAViewerControlWindowed_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDAViewerControlWindowed_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDAViewerControlWindowed_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDAViewerControlWindowed_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDAViewerControlWindowed_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDAViewerControlWindowed_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDAViewerControlWindowed_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDAViewerControlWindowed_get_UpdateInterval(This,pVal)	\
    (This)->lpVtbl -> get_UpdateInterval(This,pVal)

#define IDAViewerControlWindowed_put_UpdateInterval(This,newVal)	\
    (This)->lpVtbl -> put_UpdateInterval(This,newVal)

#define IDAViewerControlWindowed_get_View(This,ppView)	\
    (This)->lpVtbl -> get_View(This,ppView)

#define IDAViewerControlWindowed_put_View(This,pView)	\
    (This)->lpVtbl -> put_View(This,pView)

#define IDAViewerControlWindowed_get_Image(This,ppImage)	\
    (This)->lpVtbl -> get_Image(This,ppImage)

#define IDAViewerControlWindowed_put_Image(This,pImage)	\
    (This)->lpVtbl -> put_Image(This,pImage)

#define IDAViewerControlWindowed_get_BackgroundImage(This,ppImage)	\
    (This)->lpVtbl -> get_BackgroundImage(This,ppImage)

#define IDAViewerControlWindowed_put_BackgroundImage(This,pImage)	\
    (This)->lpVtbl -> put_BackgroundImage(This,pImage)

#define IDAViewerControlWindowed_get_Sound(This,ppSound)	\
    (This)->lpVtbl -> get_Sound(This,ppSound)

#define IDAViewerControlWindowed_put_Sound(This,pSound)	\
    (This)->lpVtbl -> put_Sound(This,pSound)

#define IDAViewerControlWindowed_get_PixelLibrary(This,ppStatics)	\
    (This)->lpVtbl -> get_PixelLibrary(This,ppStatics)

#define IDAViewerControlWindowed_get_MeterLibrary(This,ppStatics)	\
    (This)->lpVtbl -> get_MeterLibrary(This,ppStatics)

#define IDAViewerControlWindowed_AddBehaviorToRun(This,pBehavior)	\
    (This)->lpVtbl -> AddBehaviorToRun(This,pBehavior)

#define IDAViewerControlWindowed_Start(This)	\
    (This)->lpVtbl -> Start(This)

#define IDAViewerControlWindowed_get_InputImage(This,pVal)	\
    (This)->lpVtbl -> get_InputImage(This,pVal)

#define IDAViewerControlWindowed_get_OpaqueForHitDetect(This,b)	\
    (This)->lpVtbl -> get_OpaqueForHitDetect(This,b)

#define IDAViewerControlWindowed_put_OpaqueForHitDetect(This,b)	\
    (This)->lpVtbl -> put_OpaqueForHitDetect(This,b)

#define IDAViewerControlWindowed_get_TimerSource(This,ts)	\
    (This)->lpVtbl -> get_TimerSource(This,ts)

#define IDAViewerControlWindowed_put_TimerSource(This,ts)	\
    (This)->lpVtbl -> put_TimerSource(This,ts)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDAViewerControlWindowed_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_DAViewerControl;

#ifdef __cplusplus

class DECLSPEC_UUID("B6FFC24C-7E13-11D0-9B47-00C04FC2F51D")
DAViewerControl;
#endif

EXTERN_C const CLSID CLSID_DAViewerControlWindowed;

#ifdef __cplusplus

class DECLSPEC_UUID("69AD90EF-1C20-11d1-8801-00C04FC29D46")
DAViewerControlWindowed;
#endif
#endif /* __DirectAnimation_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
