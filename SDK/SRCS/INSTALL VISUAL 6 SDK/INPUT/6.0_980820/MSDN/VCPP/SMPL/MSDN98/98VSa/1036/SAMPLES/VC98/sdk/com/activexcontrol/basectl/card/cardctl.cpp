//=--------------------------------------------------------------------------=
// CardCtl.Cpp
//=--------------------------------------------------------------------------=
// Copyright 1995 - 1997 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
//
//
#include "IPServer.H"

#include "Guids.H"
#include "LocalObj.H"
#include "Util.H"
#include "Globals.H"
#include "Resource.H"
#include "cardctl.H"

#include "carddraw.h"

extern HBITMAP cardcacheMem[];
extern CRITICAL_SECTION drawCritSec;

// for ASSERT and FAIL
//
SZTHISFILE

WCHAR wszImage [] = L"Card";

//=--------------------------------------------------------------------------=
// all the events in this control
//
// TODO: add events here ...
//

static VARTYPE rgMouse[] = { VT_I2, VT_I2, VT_I4, VT_I4 };
enum { MouseMove=0, MouseDown, MouseUp, Click, DblClick };

static EVENTINFO rgEvents [] = {
    { DISPID_MOUSEMOVE, 4, rgMouse },
    { DISPID_MOUSEDOWN, 4, rgMouse },
    { DISPID_MOUSEUP, 4, rgMouse },
    { DISPID_CLICK, 0, NULL },
    { DISPID_DBLCLICK, 0, NULL },
};

//=--------------------------------------------------------------------------=
// array describing all of our property pages.  these clsids are typically
// in guids.h
//
// TODO: add any additional property page guids here ...
//
const GUID *rgCardPropPages [] = {
    &CLSID_CardGeneralPage
};

//=--------------------------------------------------------------------------=
// Custum Verb information
//
// TODO: add any custom verbs here in an array, using the VERBINFO structure.
//       then mark the controld def'n in CardCtl.H with
//       this verb array
//


//=--------------------------------------------------------------------------=
// CCardControl::CCardControl
//=--------------------------------------------------------------------------=
// "Being born is like being kidnapped.  And then sold into slavery."
//    - andy warhol (1928 - 87)
//
// Parameters:
//    IUnknown *        - [in]
//
// Notes:
//
#pragma warning(disable:4355)  // using 'this' in constructor
CCardControl::CCardControl
(
    IUnknown *pUnkOuter
)
: COleControl(pUnkOuter, OBJECT_TYPE_CTLCARD, (IDispatch *)this)
{
	static SIZEL size = { CCardDraw::CardSizeX, CCardDraw::CardSizeY };

	m_number = DefaultNumber;
	m_suite = DefaultSuite;
	m_invert = DefaultInvert;
	m_cardalignment = DefaultCardAlignment;
	BackBrush = NULL;

	SetControlSize( &size );

#if 0
// for better performance when the cards are first displayed (such as
// when a full deck is displayed to the user), un-ifdef this code.  
// for better initial control creation time, keep this code ifdef'd.  

	// initialize the standard 52 cards (no jokers, no backs)
	if( !cardcacheMem[0] )
	{
	        EnterCriticalSection( &drawCritSec );
		if( !cardcacheMem[0] )
		{
			CCardDraw cd( CCardDraw::DrawAll );
			HDC drawDc;
			HBITMAP drawDcMem;
			int t;

			drawDc = CreateCompatibleDC( NULL );

			for( t = 0; t < 52; t++ )
			{
				cardcacheMem[t] = cd.CreateDIBCard( drawDc );
				drawDcMem = SelectObject( drawDc, cardcacheMem[t] );	
				cd.DrawCard( drawDc, (t/14) + 1, (t%14) + 1 );
				SelectObject( drawDc, drawDcMem );
			}
			DeleteDC( drawDc );
		}
		LeaveCriticalSection( &drawCritSec );
	}
#endif
}
#pragma warning(default:4355)  // using 'this' in constructor

//=--------------------------------------------------------------------------=
// CCardControl::~CCardControl
//=--------------------------------------------------------------------------=
// "We all labour against our own cure, for death is the cure of all diseases"
//    - Sir Thomas Browne (1605 - 82)
//
// Notes:
//
CCardControl::~CCardControl ()
{
	if( BackBrush )
		DeleteObject( BackBrush );
}

//=--------------------------------------------------------------------------=
// CCardControl:RegisterClassData
//=--------------------------------------------------------------------------=
// register the window class information for your control here.
// this information will automatically get cleaned up for you on DLL shutdown.
//
// Output:
//    BOOL            - FALSE means fatal error.
//
// Notes:
//
BOOL CCardControl::RegisterClassData()
{
    WNDCLASS wndclass;

    // TODO: register any additional information you find interesting here.
    //       this method is only called once for each type of control
    //
    memset(&wndclass, 0, sizeof(WNDCLASS));
    wndclass.style          = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS | CS_OWNDC;
    wndclass.lpfnWndProc    = COleControl::ControlWindowProc;
    wndclass.hInstance      = g_hInstance;
    wndclass.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
    wndclass.lpszClassName  = WNDCLASSNAMEOFCONTROL(OBJECT_TYPE_CTLCARD);

    return RegisterClass(&wndclass);
}

//=--------------------------------------------------------------------------=
// CCardControl::InternalQueryInterface
//=--------------------------------------------------------------------------=
// qi for things only we support.
//
// Parameters:
// Parameters:
//    REFIID        - [in]  interface they want
//    void **       - [out] where they want to put the resulting object ptr.
//
// Output:
//    HRESULT       - S_OK, E_NOINTERFACE
//
// Notes:
//
HRESULT CCardControl::InternalQueryInterface
(
    REFIID  riid,
    void  **ppvObjOut
)
{
    IUnknown *pUnk;

    *ppvObjOut = NULL;

    // TODO: if you want to support any additional interrfaces, then you should
    // indicate that here.  never forget to call COleControl's version in the
    // case where you don't support the given interface.
    //
    if (DO_GUIDS_MATCH(riid, IID_ICard)) {
        pUnk = (IUnknown *)(ICard *)this;
    } else{
        return COleControl::InternalQueryInterface(riid, ppvObjOut);
    }

    pUnk->AddRef();
    *ppvObjOut = (void *)pUnk;
    return S_OK;
}

//=--------------------------------------------------------------------------=
// CCardControl::LoadTextState
//=--------------------------------------------------------------------------=
// load in our text state for this control.
//
// Parameters:
//    IPropertyBag *        - [in] property bag to read from
//    IErrorLog *           - [in] errorlog object to use with proeprty bag
//
// Output:
//    HRESULT
//
// Notes:
//    - NOTE: if you have a binary object, then you should pass an unknown
//      pointer to the property bag, and it will QI it for IPersistStream, and
//      get said object to do a Load()
//
STDMETHODIMP CCardControl::LoadTextState
(
    IPropertyBag *pPropertyBag,
    IErrorLog    *pErrorLog
)
{
	VARIANT v;
	HRESULT hr;

	VariantInit(&v);    

	v.vt = VT_I2;
	hr = pPropertyBag->Read(L"Number",&v,pErrorLog);
	if (SUCCEEDED(hr))
		m_number = (enumCardNumber) v.iVal;
	ValidateNumber();
	VariantClear(&v);

	v.vt = VT_I2;
	hr = pPropertyBag->Read(L"Suite",&v,pErrorLog);
	if (SUCCEEDED(hr))
		m_suite = (enumCardSuite) v.iVal;
	ValidateSuite();
	VariantClear(&v);

	v.vt = VT_BOOL;
	hr = pPropertyBag->Read(L"Invert",&v,pErrorLog);
	if (SUCCEEDED(hr))
		m_invert = v.boolVal;
	VariantClear(&v);

	v.vt = VT_I2;
	hr = pPropertyBag->Read(L"CardAlignment",&v,pErrorLog);
	if (SUCCEEDED(hr))
		m_cardalignment = (enumCardAlignment) v.iVal;
	ValidateCardAlignment();
	VariantClear(&v);

    return S_OK;
}

#define		STREAMHDR_MAGIC		1296924267

//=--------------------------------------------------------------------------=
// CCardControl::LoadBinaryState
//=--------------------------------------------------------------------------=
// loads in our binary state using streams.
//
// Parameters:
//    IStream *            - [in] stream to write to.
//
// Output:
//    HRESULT
//
// Notes:
//
STDMETHODIMP CCardControl::LoadBinaryState
(
    IStream *pStream
)
{
    HRESULT hr;
	DWORD sh;

	hr = pStream->Read(&sh, sizeof(sh), NULL);
	RETURN_ON_FAILURE(hr);

	if (sh != STREAMHDR_MAGIC )
		return E_UNEXPECTED;

	hr = pStream->Read(&(m_number),sizeof(m_number),NULL);
	RETURN_ON_FAILURE(hr);
	ValidateNumber();

	hr = pStream->Read(&(m_suite),sizeof(m_suite),NULL);
	RETURN_ON_FAILURE(hr);
	ValidateSuite();

	hr = pStream->Read(&(m_invert),sizeof(m_invert),NULL);
	RETURN_ON_FAILURE(hr);

	hr = pStream->Read(&(m_cardalignment),sizeof(m_cardalignment),NULL);
	RETURN_ON_FAILURE(hr);
	ValidateCardAlignment();

	return S_OK;
}

//=--------------------------------------------------------------------------=
// CCardControl::SaveTextState
//=--------------------------------------------------------------------------=
// saves out the text state for this control using a property bag.
//
// Parameters:
//    IPropertyBag *        - [in] the property bag with which to work.
//    BOOL                  - [in] if TRUE, then write out ALL properties, even
//                            if they're their the default value ...
//
// Output:
//    HRESULT
//
// Notes:
//
STDMETHODIMP CCardControl::SaveTextState
(
    IPropertyBag *pPropertyBag,
    BOOL          fWriteDefaults
)
{
	VARIANT v;
	HRESULT hr;

	if( m_number != DefaultNumber )
	{
		VariantInit(&v);
		v.vt = VT_I2;
		v.iVal = m_number;
		hr = pPropertyBag->Write( L"Number", &v);
	}

	if( m_suite != DefaultSuite )
	{
		VariantInit(&v);
		v.vt = VT_I2;
		v.iVal = m_suite;
		hr = pPropertyBag->Write( L"Suite", &v);
	}

	if( m_invert != DefaultInvert )
	{
		VariantInit(&v);
		v.vt = VT_BOOL;
		v.boolVal = m_invert;
		hr = pPropertyBag->Write( L"Invert", &v);
	}

	if( m_cardalignment != DefaultCardAlignment )
	{
		VariantInit(&v);
		v.vt = VT_I2;
		v.iVal = m_cardalignment;
		hr = pPropertyBag->Write( L"CardAlignment", &v);
	}

	return S_OK;
}

//=--------------------------------------------------------------------------=
// CCardControl::SaveBinaryState
//=--------------------------------------------------------------------------=
// save out the binary state for this control, using the given IStream object.
//
// Parameters:
//    IStream  *             - [in] save to which you should save.
//
// Output:
//    HRESULT
//
// Notes:
//    - it is important that you seek to the end of where you saved your
//      properties when you're done with the IStream.
//
STDMETHODIMP CCardControl::SaveBinaryState
(
    IStream *pStream
)
{
    HRESULT hr;
    DWORD sh = STREAMHDR_MAGIC;    

    // write out the stream hdr.
    //
    hr = pStream->Write(&sh, sizeof(sh), NULL);
    RETURN_ON_FAILURE(hr);

    hr = pStream->Write(&(m_number),sizeof(m_number),NULL);
    RETURN_ON_FAILURE(hr);

    hr = pStream->Write(&(m_suite),sizeof(m_suite),NULL);
    RETURN_ON_FAILURE(hr);

    hr = pStream->Write(&(m_invert),sizeof(m_invert),NULL);
    RETURN_ON_FAILURE(hr);

    hr = pStream->Write(&(m_cardalignment),sizeof(m_cardalignment),NULL);
    RETURN_ON_FAILURE(hr);

    return S_OK;
}


//=--------------------------------------------------------------------------=
// CCardControl::OnDraw
//=--------------------------------------------------------------------------=
// "I don't very much enjoy looking at paintings in general.  i know too
//  much about them.  i take them apart."
//    - georgia o'keeffe (1887-1986)
//
// Parameters:
//    HDC                - [in]  HDC to draw to
//    LPCRECTL           - [in]  rect we're drawing to
//    LPCRECTL           - [in]  window extent and origin for meta-files
//    HDC                - [in]  HIC for target device
//
// Output:
//    HRESULT
//
// Notes:
//
HRESULT CCardControl::OnDraw
(
    DWORD    dvaspect,        
    HDC      hdcDraw,
    LPCRECTL prcBounds,
    LPCRECTL prcWBounds,
    HDC      hicTargetDevice,
    BOOL     fOptimize
)
{
	int OffsetX, OffsetY;
	RECTL rcBoundsDP;
	int width, height;
	int savedDC;
	HDC drawDc;
	HBITMAP drawDcMem;
	int c;

	if( !Windowless() && !BackBrush )
	{
		OLE_COLOR BackColor;
		COLORREF BackColorCR;
		if( !GetAmbientProperty( DISPID_AMBIENT_BACKCOLOR, VT_I4, &BackColor ) )
			BackColor = 0;
		OleTranslateColor( BackColor, NULL, &BackColorCR );
		BackBrush = CreateSolidBrush( BackColorCR );
	}
		
	rcBoundsDP = *prcBounds;
	LPtoDP( hdcDraw, (POINT *) &rcBoundsDP, 2 );

	width = rcBoundsDP.right - rcBoundsDP.left;
	height = rcBoundsDP.bottom - rcBoundsDP.top;

	switch( m_cardalignment )
	{
		case CardTopCenter: 
		case CardCenter:
		case CardBottomCenter:
			OffsetX = (width - CCardDraw::CardSizeX) / 2;
			break;
		case CardTopRight: 
		case CardCenterRight:
		case CardBottomRight:
			OffsetX = (width - CCardDraw::CardSizeX);
			break;
		default:
			OffsetX = 0;
			break;
	}
	switch( m_cardalignment )
	{
		case CardCenterRight:
		case CardCenter:
		case CardCenterLeft:
			OffsetY = (height - CCardDraw::CardSizeY) / 2;
			break;
		case CardBottomRight: 
		case CardBottomCenter: 
		case CardBottomLeft:
			OffsetY = (height - CCardDraw::CardSizeY);
			break;
		default:
			OffsetY = 0;
			break;
	}

	if( BackBrush )
		FillRect( hdcDraw, (RECT *) prcBounds, BackBrush );

	if( m_suite == CardBlank )
		return S_OK;

	savedDC = SaveDC( hdcDraw );

	SetMapMode( hdcDraw, MM_TEXT );
	SetWindowOrgEx( hdcDraw, -(OffsetX + rcBoundsDP.left), 
				 -(OffsetY + rcBoundsDP.top), NULL );
	SetViewportOrgEx( hdcDraw, 0, 0, NULL );

	if( width < CCardDraw::CardSizeX || height < CCardDraw::CardSizeY )
	{
		HRGN clipRgn;
		clipRgn = CreateRectRgn( rcBoundsDP.left, 
					 rcBoundsDP.top, 
					 rcBoundsDP.left + width, 
					 rcBoundsDP.top + height );
		SelectClipRgn( hdcDraw, clipRgn );
		DeleteObject( clipRgn );
	}		

	SelectObject( hdcDraw, GetStockObject( m_invert ? WHITE_PEN : BLACK_PEN ) );

	drawDc = CreateCompatibleDC( NULL );

	if( m_suite > 0 )
		c = (m_suite-1)*14 + (m_number-1);
	else
		c = (m_suite < -12) ? 56 : -m_suite + 56;

	if( !cardcacheMem[c] )
	{
		CCardDraw cd( (c > 55 ? CCardDraw::DrawBack : (int) m_number) );

	        EnterCriticalSection( &drawCritSec );
		if( !cardcacheMem[c] )
		{
			cardcacheMem[c] = cd.CreateDIBCard( hdcDraw );
			drawDcMem = (HBITMAP) SelectObject( drawDc, cardcacheMem[c] );	
			cd.DrawCard( drawDc, m_suite, m_number );
		}
		else
			drawDcMem = (HBITMAP) SelectObject( drawDc, cardcacheMem[c] );	
		LeaveCriticalSection( &drawCritSec );
	}
	else
		drawDcMem = (HBITMAP) SelectObject( drawDc, cardcacheMem[c] );	

	if( m_cardalignment != CardStretch )
	{
	  	BitBlt( hdcDraw, 1, 1, CCardDraw::CardSizeX-2, CCardDraw::CardSizeY-2,
		 	   drawDc, 1, 1, m_invert ? NOTSRCCOPY : SRCCOPY );
		Polyline( hdcDraw, CCardDraw::CardBorder, 
				sizeof(CCardDraw::CardBorder)/sizeof(POINT) );
	}
	else
	{
		POINT border[9];
		memcpy( border, CCardDraw::CardBorder, sizeof(border) );
		border[2].x = border[5].x = width-3;
		border[3].x = border[4].x = width-1;
		border[4].y = border[7].y = height-3;
		border[5].y = border[6].y = height-1;
		StretchBlt( hdcDraw, 1, 1, width-2, height-2,
				drawDc, 1, 1, 
				CCardDraw::CardSizeX-2,
				CCardDraw::CardSizeY-2,
				m_invert ? NOTSRCCOPY : SRCCOPY );
		Polyline( hdcDraw, border, sizeof(border)/sizeof(POINT) );
	}

	RestoreDC( hdcDraw, savedDC );

	SelectObject( drawDc, drawDcMem );
	DeleteDC( drawDc );
	
    return S_OK;
}

//=--------------------------------------------------------------------------=
// CCardControl::WindowProc
//=--------------------------------------------------------------------------=
// window procedure for this control.  nothing terribly exciting.
//
// Parameters:
//     see win32sdk on window procs.
//
// Notes:
//
LRESULT CCardControl::WindowProc
(
    UINT   msg,
    WPARAM wParam,
    LPARAM lParam
)
{
    POINTS pt;
    RECT rect;
    int b, s;
    int ev = -1;

    switch( msg )
    {
	case WM_MOUSEMOVE:
		ev = MouseMove;
		// FALL THROUGH!
	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
		if( ev == -1 )	ev = MouseDown;
		// FALL THROUGH!
	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
		if( ev == -1 )  ev = MouseUp;
		pt = MAKEPOINTS( lParam );
		OcxGetWindowRect( &rect );
		b = (wParam & 3) == 3 ? 4 : wParam & 3;
		s = (wParam >> 2) & 7;
		FireEvent( &rgEvents[ev], b, s, pt.x-rect.left, pt.y-rect.top );
		if( msg == WM_LBUTTONUP )
			FireEvent( &rgEvents[Click] );
		break;
	case WM_LBUTTONDBLCLK:
		FireEvent( &rgEvents[DblClick] );
		break;
    }

    return OcxDefWindowProc(msg, wParam, lParam);
}

//=--------------------------------------------------------------------------=
// CCardControl::AboutBox
//=--------------------------------------------------------------------------=
// prints up an about box.  fweeeee.
//
// Notes:
//
void CCardControl::AboutBox
(
    void
)
{
    // TODO: Ideally, one would use DialogBox, and some sort of Dialog Box here if
    // they wanted a slightly more interesting About Box ...  you should
    // still call ModalDialog first, however.
    //
    ModalDialog(TRUE);
    MessageBox(NULL, "Microsoft ActiveX Card Control\n\n"
		     "Copyright © 1996 Microsoft Corp.",
		     "About Card", 
		     MB_OK | MB_TASKMODAL);
    ModalDialog(FALSE);
}

STDMETHODIMP  CCardControl::get_Number(enumCardNumber * number)
{
	CHECK_POINTER(number);

	*number = m_number;

	return( S_OK );
}

STDMETHODIMP  CCardControl::put_Number(enumCardNumber number)
{
	if( m_number == number ) 
		return S_OK;

	m_number = number;
	ValidateNumber();
	if( m_suite >= 1 )
	{
		if( Windowless() )
		{
			RECT rect;
			OcxGetWindowRect( &rect );
			OcxInvalidateRect( &rect, TRUE );
		}
		else
			InvalidateControl( NULL );
	}

	// update anybody who cares about property changes and mark ourselves
	// as dirty
	//
	PropertyChanged(DISPID_NUMBER);
	m_fDirty = TRUE;

    return S_OK;
}

STDMETHODIMP  CCardControl::get_Invert( VARIANT_BOOL *invert )
{
	CHECK_POINTER(invert);

	*invert = m_invert;

	return( S_OK );
}

STDMETHODIMP  CCardControl::put_Invert( VARIANT_BOOL invert )
{
	if( m_invert == invert )
		return S_OK;

	m_invert = invert;

	{
		if( Windowless() )
		{
			RECT rect;
			OcxGetWindowRect( &rect );
			OcxInvalidateRect( &rect, TRUE );
		}
		else
			InvalidateControl( NULL );
	}

	// update anybody who cares about property changes and mark ourselves
	// as dirty
	//
	PropertyChanged(DISPID_INVERT);
	m_fDirty = TRUE;

    return S_OK;
}

STDMETHODIMP  CCardControl::get_CardAlignment( enumCardAlignment *cardalignment )
{
	CHECK_POINTER(cardalignment);

	*cardalignment = m_cardalignment;

	return( S_OK );
}

STDMETHODIMP  CCardControl::put_CardAlignment( enumCardAlignment cardalignment )
{
	if( m_cardalignment == cardalignment )
		return S_OK;

	m_cardalignment = cardalignment;	
	ValidateCardAlignment();

	{
		if( Windowless() )
		{
			RECT rect;
			OcxGetWindowRect( &rect );
			OcxInvalidateRect( &rect, TRUE );
		}
		else
			InvalidateControl( NULL );
	}

	// update anybody who cares about property changes and mark ourselves
	// as dirty
	//
	PropertyChanged(DISPID_CARDALIGNMENT);
	m_fDirty = TRUE;

    return S_OK;
}

STDMETHODIMP  CCardControl::get_Suite(enumCardSuite * suite)
{
	CHECK_POINTER(suite);

	*suite = m_suite;

	return( S_OK );
}

STDMETHODIMP  CCardControl::put_Suite(enumCardSuite suite)
{
	if( m_suite == suite ) 
		return S_OK;

	m_suite = suite;
	ValidateSuite();

	{
		if( Windowless() )
		{
			RECT rect;
			OcxGetWindowRect( &rect );
			OcxInvalidateRect( &rect, TRUE );
		}
		else
			InvalidateControl( NULL );
	}

	// update anybody who cares about property changes and mark ourselves
	// as dirty
	//
	PropertyChanged(DISPID_SUITE);
	m_fDirty = TRUE;

    return S_OK;
}

//=--------------------------------------------------------------------------=
// CCardControl::Create
//=--------------------------------------------------------------------------=
// global static function that creates an instance of the control an returns
// an IUnknown pointer for it.
//
// Parameters:
//    IUnknown *        - [in] controlling unknown for aggregation
//
// Output:
//    IUnknown *        - new object.
//
// Notes:
//
IUnknown *CCardControl::Create
(
    IUnknown *pUnkOuter
)
{
    // make sure we return the private unknown so that we support aggegation
    // correctly!
    //
    CCardControl *pNew = new CCardControl(pUnkOuter);
    return pNew->PrivateUnknown();
}

  				  	   	 	
  			 		   	  	
