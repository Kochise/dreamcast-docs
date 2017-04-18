//=--------------------------------------------------------------------------=
// WImgCtl.H
//=--------------------------------------------------------------------------=
// Copyright 1995 - 1997 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// class declaration for the WebImage control.
//
#ifndef _WEBIMAGECONTROL_H_

#include "IPServer.H"
#include "CtrlObj.H"
#include "Internet.h"
#include "WImgInterfaces.H"
#include "Dispids.H"


#include "DibCls.H"

typedef struct tagWEBIMAGECTLSTATE {

    // TOOD: put state variables here, and probably get rid of fGarbage, unless
    // you have a real need for it
    //
    VARIANT_BOOL fGarbage;

} WEBIMAGECTLSTATE;

//=--------------------------------------------------------------------------=
// CWebImageControl
//=--------------------------------------------------------------------------=
// our control.
//
class CWebImageControl :       public CInternetControl, 
                                                                        public IWebImage, 
									public ISupportErrorInfo {

  public:
    // IUnknown methods
    //
    DECLARE_STANDARD_UNKNOWN();

    // IDispatch methods
    //
    DECLARE_STANDARD_DISPATCH();

    // ISupportErrorInfo methods
    //
    DECLARE_STANDARD_SUPPORTERRORINFO();

    // IWebImage methods
    //
    // TODO: copy over the method declarations from WebImageInterfaces.H
    //       don't forget to remove the PURE from them.
    //
    STDMETHOD(get_Image)(THIS_ BSTR FAR* path) ;
    STDMETHOD(put_Image)(THIS_ BSTR path) ;
    STDMETHOD_(void, AboutBox)(THIS) ;
    STDMETHOD(Scramble)(THIS) ;

    // OLE Control stuff follows:
    //
    CWebImageControl(IUnknown *pUnkOuter);
    virtual ~CWebImageControl();

    // static creation function.  all controls must have one of these!
    //
    static IUnknown *Create(IUnknown *);

  private:
    // overridables that the control must implement.
    //
    STDMETHOD(LoadBinaryState)(IStream *pStream);
    STDMETHOD(SaveBinaryState)(IStream *pStream);
    STDMETHOD(LoadTextState)(IPropertyBag *pPropertyBag, IErrorLog *pErrorLog);
    STDMETHOD(SaveTextState)(IPropertyBag *pPropertyBag, BOOL fWriteDefault);
    STDMETHOD(OnDraw)(DWORD dvAspect, HDC hdcDraw, LPCRECTL prcBounds, LPCRECTL prcWBounds, HDC hicTargetDev, BOOL fOptimize);
    virtual LRESULT WindowProc(UINT msg, WPARAM wParam, LPARAM lParam);
    virtual BOOL    RegisterClassData(void);

    virtual HRESULT InternalQueryInterface(REFIID, void **);
    virtual void    BeforeCreateWindow(void);
	
    virtual BOOL    AfterCreateWindow(void);

	//	Internet specific callbacks:
	//
	///	OnData is called asynchronously as data for an object or property arrives...
	virtual HRESULT OnData( DISPID id, DWORD grfBSCF,IStream * bitstrm, DWORD amount );

	//	OnProgess is called to allow you to present progess indication UI
	virtual HRESULT OnProgress( DISPID, ULONG progress, ULONG themax, ULONG, LPCWSTR);


    // private state information.
    //

	HRESULT SetBmpPath(const char *psz);
	HRESULT SetBmpPath(IStream *);
    HRESULT UpdateImage();

	enum bmpDownloadStates
	{
		bdsNoBitsYet,
		bdsGotFileHeader,
        bdsGotBitmapInfo,
		bdsGettingBits,
		bdsBitsAreDone
	};


	HDC					m_dc;
	bmpDownloadStates	m_state;
	CDibFile *			m_dibFile;
	CDibSection *		m_dib;

	// Actual properties
	char *				m_bmpPath;

};


// TODO: if you have an array of verbs, then add an extern here with the name
//       of it, so that you can include it in the DEFINE_CONTROLOBJECT.
//       ie.  extern VERBINFO m_WebImageCustomVerbs [];
//
extern const GUID    *rgWebImagePropPages [];
DEFINE_CONTROLOBJECT(WebImage,
    &CLSID_WebImage,
    "WebImageCtl",
    CWebImageControl::Create,
    1,
    &IID_IWebImage,
    "WebImage.HLP",
    &DIID_DWebImageEvents,
    OLEMISC_SETCLIENTSITEFIRST|OLEMISC_ACTIVATEWHENVISIBLE|OLEMISC_RECOMPOSEONRESIZE|OLEMISC_CANTLINKINSIDE|OLEMISC_INSIDEOUT,
    0,
    RESID_TOOLBOX_BITMAP,
    "WebImageWndClass",
    1,
    rgWebImagePropPages,
    0,
    NULL);



#define _WEBIMAGECONTROL_H_
#endif // _WEBIMAGECONTROL_H_
