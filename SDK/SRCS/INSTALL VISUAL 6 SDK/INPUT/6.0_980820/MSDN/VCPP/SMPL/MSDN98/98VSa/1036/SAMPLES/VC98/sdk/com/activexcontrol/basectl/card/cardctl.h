//=--------------------------------------------------------------------------=
// CardCtl.H
//=--------------------------------------------------------------------------=
// Copyright 1995 - 1997 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// class declaration for the Card control.
//
#ifndef _CARDCONTROL_H_

#include "IPServer.H"
#include "CtrlObj.H"
#include "CardInterfaces.h"
#include "Dispids.H"

//=--------------------------------------------------------------------------=
// CCARDControl
//=--------------------------------------------------------------------------=
// our control.
//
class CCardControl :       public COleControl, 
                           public ICard, 
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

    // ICARD methods
    //
    // TODO: copy over the method declarations from CARDInterfaces.H
    //       don't forget to remove the PURE from them.
    //
    STDMETHOD(get_Number)(THIS_ enumCardNumber * number) ;
    STDMETHOD(put_Number)(THIS_ enumCardNumber number) ;
    STDMETHOD(get_Suite)(THIS_ enumCardSuite * suite) ;
    STDMETHOD(put_Suite)(THIS_ enumCardSuite suite) ;
    STDMETHOD(get_Invert)(THIS_ VARIANT_BOOL * invert) ;
    STDMETHOD(put_Invert)(THIS_ VARIANT_BOOL invert) ;
    STDMETHOD(get_CardAlignment)(THIS_ enumCardAlignment * align) ;
    STDMETHOD(put_CardAlignment)(THIS_ enumCardAlignment align) ;
    STDMETHOD_(void, AboutBox)(THIS) ;

    // OLE Control stuff follows:
    //
    CCardControl(IUnknown *pUnkOuter);
    virtual ~CCardControl();

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
    STDMETHOD(OnDraw)(DWORD dvaspect, HDC hdcDraw, LPCRECTL prcBounds, LPCRECTL prcWBounds, HDC hicTargetDev, BOOL fOptimize);
    virtual LRESULT WindowProc( UINT msg, WPARAM wParam, LPARAM lParam);
    virtual BOOL    RegisterClassData(void);

    virtual HRESULT InternalQueryInterface(REFIID, void **);

    // private state information.
    //
	HRESULT DrawMe( HDC hdcMem );
	void DrawBack(void);

	// Actual properties
	enumCardNumber	m_number;
#define DefaultNumber CardAce
	void ValidateNumber() 
	{
		if( m_number < CardAce ) m_number = CardAce;
		if( m_number > CardJoker ) m_number = CardJoker;
	}

	enumCardSuite m_suite;
#define DefaultSuite CardBlank
	void ValidateSuite()
	{
		if( m_suite > CardDiamond ) m_suite = CardDiamond;
	}

	VARIANT_BOOL m_invert;
	enum { DefaultInvert = VARIANT_FALSE };

	enumCardAlignment   m_cardalignment;
#define DefaultCardAlignment CardCenter
	void ValidateCardAlignment()
	{
		if( m_cardalignment < CardTopLeft ) m_cardalignment = CardTopLeft;
		if( m_cardalignment > CardStretch ) m_cardalignment = CardStretch;
	}

	HBRUSH BackBrush;
};


// TODO: if you have an array of verbs, then add an extern here with the name
//       of it, so that you can include it in the DEFINE_CONTROLOBJECT.
//       ie.  extern VERBINFO m_CARDCustomVerbs [];
//
extern const GUID    *rgCardPropPages [];
DEFINE_WINDOWLESSCONTROLOBJECT(Card,
    &CLSID_Card,
    "ActiveXCardControl",
    CCardControl::Create,
    1,
    &IID_ICard,
    "CARD.HLP",
    &DIID_DCardEvents,
    OLEMISC_SETCLIENTSITEFIRST|OLEMISC_ACTIVATEWHENVISIBLE|
OLEMISC_RECOMPOSEONRESIZE|OLEMISC_CANTLINKINSIDE|OLEMISC_INSIDEOUT,
	FALSE,
	FALSE,
    RESID_TOOLBOX_BITMAP,
    "CARDWndClass",
    1,
    rgCardPropPages,
    0,
    NULL);



#define _CARDCONTROL_H_
#endif // _CARDCONTROL_H_


