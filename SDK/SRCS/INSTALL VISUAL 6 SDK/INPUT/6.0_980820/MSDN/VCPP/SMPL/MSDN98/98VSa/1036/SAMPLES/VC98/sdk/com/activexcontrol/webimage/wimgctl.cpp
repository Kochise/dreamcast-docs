//=--------------------------------------------------------------------------=
// WImgCtl.Cpp
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
#include "Wimgctl.H"

// for ASSERT and FAIL
//
SZTHISFILE

WCHAR wszImage [] = L"Image";




//=--------------------------------------------------------------------------=
// all the events in this control
//
// TODO: add events here ...
//

//=--------------------------------------------------------------------------=
// array describing all of our property pages.  these clsids are typically
// in guids.h
//
// TODO: add any additional property page guids here ...
//
const GUID *rgWebImagePropPages [] = {
    &CLSID_WebImageGeneralPage
};

//=--------------------------------------------------------------------------=
// Custum Verb information
//
// TODO: add any custom verbs here in an array, using the VERBINFO structure.
//       then mark the controld def'n in WebImageCtl.H with
//       this verb array
//


//=--------------------------------------------------------------------------=
// CWebImageControl::Create
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
IUnknown *CWebImageControl::Create
(
    IUnknown *pUnkOuter
)
{
    // make sure we return the private unknown so that we support aggegation
    // correctly!
    //
    CWebImageControl *pNew = new CWebImageControl(pUnkOuter);
    return pNew->PrivateUnknown();
}

//=--------------------------------------------------------------------------=
// CWebImageControl::CWebImageControl
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
CWebImageControl::CWebImageControl
(
    IUnknown *pUnkOuter
)
: CInternetControl(pUnkOuter, OBJECT_TYPE_CTLWEBIMAGE, (IDispatch *)this)
{
	m_bmpPath = 0;
	m_dib = 0;
	m_dibFile = 0;
	m_state	= bdsNoBitsYet;

}
#pragma warning(default:4355)  // using 'this' in constructor

//=--------------------------------------------------------------------------=
// CWebImageControl::~CWebImageControl
//=--------------------------------------------------------------------------=
// "We all labour against our own cure, for death is the cure of all diseases"
//    - Sir Thomas Browne (1605 - 82)
//
// Notes:
//
CWebImageControl::~CWebImageControl ()
{
	if(m_bmpPath)
		delete [] m_bmpPath;
	if( m_dibFile )
		delete m_dibFile;
	if( m_dib )
		delete m_dib;
}

//=--------------------------------------------------------------------------=
// CWebImageControl:RegisterClassData
//=--------------------------------------------------------------------------=
// register the window class information for your control here.
// this information will automatically get cleaned up for you on DLL shutdown.
//
// Output:
//    BOOL            - FALSE means fatal error.
//
// Notes:
//
BOOL CWebImageControl::RegisterClassData()
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
    wndclass.lpszClassName  = WNDCLASSNAMEOFCONTROL(OBJECT_TYPE_CTLWEBIMAGE);

    return RegisterClass(&wndclass);
}

//=--------------------------------------------------------------------------=
// CWebImageControl::BeforeCreateWindow
//=--------------------------------------------------------------------------=
// called just before the window is created.  Great place to set up the
// window title, etc, so that they're passed in to the call to CreateWindowEx.
// speeds things up slightly.
//
// Notes:
//
void CWebImageControl::BeforeCreateWindow()
{
}

BOOL CWebImageControl::AfterCreateWindow()
{
	m_dc = ::GetDC(m_hwnd);
	HPALETTE hpal = ::CreateHalftonePalette(m_dc);
	::SelectPalette(m_dc, hpal, FALSE);

        UpdateImage();
        return TRUE;
}

//=--------------------------------------------------------------------------=
// CWebImageControl::InternalQueryInterface
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
HRESULT CWebImageControl::InternalQueryInterface
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
    if (DO_GUIDS_MATCH(riid, IID_IWebImage)) {
        pUnk = (IUnknown *)(IWebImage *)this;
    } else{
        return COleControl::InternalQueryInterface(riid, ppvObjOut);
    }

    pUnk->AddRef();
    *ppvObjOut = (void *)pUnk;
    return S_OK;
}

//=--------------------------------------------------------------------------=
// CWebImageControl::LoadTextState
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
STDMETHODIMP CWebImageControl::LoadTextState
(
    IPropertyBag *pPropertyBag,
    IErrorLog    *pErrorLog
)
{
    VARIANT v;

	VariantInit(&v);

    v.vt = VT_BSTR;
    v.bstrVal = NULL;

	HRESULT hr = S_OK;
    // try to load in the property.  if we can't get it, then leave
    // things at their default.
    //
    pPropertyBag->Read(::wszImage, &v, pErrorLog);
    if (v.bstrVal) {
        MAKE_ANSIPTR_FROMWIDE(psz, v.bstrVal);
		hr = SetBmpPath(psz);
        VariantClear(&v);
    }

    return hr;
}

//=--------------------------------------------------------------------------=
// CWebImageControl::LoadBinaryState
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
const DWORD STREAMHDR_MAGIC = 12345678L;

STDMETHODIMP CWebImageControl::LoadBinaryState
(
    IStream *pStream
)
{
	DWORD		sh;
    HRESULT		hr;

    // first read in the streamhdr, and make sure we like what we're getting
    //
    hr = pStream->Read(&sh, sizeof(sh), NULL);
    RETURN_ON_FAILURE(hr);

    // sanity check
    //
    if (sh != STREAMHDR_MAGIC )
		return E_UNEXPECTED;

	return(SetBmpPath(pStream));
}

//=--------------------------------------------------------------------------=
// CWebImageControl::SaveTextState
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
STDMETHODIMP CWebImageControl::SaveTextState
(
    IPropertyBag *pPropertyBag,
    BOOL          fWriteDefaults
)
{
    HRESULT hr;
    VARIANT v;

    v.vt = VT_BSTR;
    v.bstrVal = BSTRFROMANSI(m_bmpPath);
    RETURN_ON_NULLALLOC(v.bstrVal);

    // this control currently only persists out the caption property
    //
    hr = pPropertyBag->Write(::wszImage, &v);
    VariantClear(&v);
    return hr;}

//=--------------------------------------------------------------------------=
// CWebImageControl::SaveBinaryState
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
STDMETHODIMP CWebImageControl::SaveBinaryState
(
    IStream *pStream
)
{
    DWORD sh = STREAMHDR_MAGIC;
    HRESULT hr;

    // write out the stream hdr.
    //
    hr = pStream->Write(&sh, sizeof(sh), NULL);
    RETURN_ON_FAILURE(hr);

    // write out he control state information
    //

	DWORD dw = m_bmpPath ? lstrlen(m_bmpPath) : 0;

	hr = pStream->Write(&dw,sizeof(dw),0);
	RETURN_ON_FAILURE(hr);

	if( dw )
		hr = pStream->Write(m_bmpPath,dw+1,0);

    return hr;
}


//=--------------------------------------------------------------------------=
// CWebImageControl::OnDraw
//=--------------------------------------------------------------------------=
// "I don't very much enjoy looking at paintings in general.  i know too
//  much about them.  i take them apart."
//    - georgia o'keeffe (1887-1986)
//
// Parameters:
//    DWORD              - [in]  drawing aspect
//    HDC                - [in]  HDC to draw to
//    LPCRECTL           - [in]  rect we're drawing to
//    LPCRECTL           - [in]  window extent and origin for meta-files
//    HDC                - [in]  HIC for target device
//    BOOL               - [in]  can we optimize dc handling?
//
// Output:
//    HRESULT
//
// Notes:
//
HRESULT CWebImageControl::OnDraw
(
    DWORD    dvAspect,
    HDC      hdcDraw,
    LPCRECTL prcBounds,
    LPCRECTL prcWBounds,
    HDC      hicTargetDevice,
    BOOL     fOptimize
)
{
	if(m_dib) 
	{
		if (prcWBounds != NULL) //printing
		{
			SetMapMode(hdcDraw,MM_TEXT);
			HBITMAP hBitmap;
				//printing DIB
			hBitmap = (HBITMAP) HANDLE(*m_dib);
			DIBSECTION ds;
			GetObject(hBitmap,sizeof(DIBSECTION),(LPSTR)&ds);
			StretchDIBits(hdcDraw,prcBounds->left,prcBounds->top,prcBounds->right - prcBounds->left,
				prcBounds->bottom - prcBounds->top,0,0,
				ds.dsBm.bmWidth, ds.dsBm.bmHeight,
				ds.dsBm.bmBits, 
				(BITMAPINFO *)(*m_dibFile), 
				DIB_RGB_COLORS,
				SRCCOPY);
			return S_OK;
		}

		if( hdcDraw != m_dc )
		{
			HPALETTE hpal = ::CreateHalftonePalette(hdcDraw);
			::SelectPalette(hdcDraw, hpal, FALSE);
		}

		::RealizePalette(hdcDraw);

		m_dib->PaintTo(hdcDraw,prcBounds->left,prcBounds->top);

	}
    return S_OK;
}

//=--------------------------------------------------------------------------=
// CWebImageControl::OnProgress
//=--------------------------------------------------------------------------=
//
// Parameters:
//    DISPID	propId		- [in]  Same dispId that was passed into SetupDownload
//    ULONG		progress	- [in]  Size downlaoded so far
//    ULONG     themax		- [in]  Overall size of object being downloaded
//    ULONG		statusFlag	- [in]  Flags according 
//    LPCWSTR   statusStr	- [in]	Readable version of status
//
// Notes:
//
HRESULT CWebImageControl::OnProgress
(
	DISPID	propId, 
	ULONG	progress, 
	ULONG	themax, 
	ULONG	statusFlag,
	LPCWSTR	statusString
)
{
	// TODO: put custom progress UI notification code here. The default action
	//	(shown below) is to fire an OnProgress event to the host

	return(FireProgress(themax ? (progress * 100)/themax : 0));
}


//=--------------------------------------------------------------------------=
// CWebImageControl::WindowProc
//=--------------------------------------------------------------------------=
// window procedure for this control.  nothing terribly exciting.
//
// Parameters:
//     see win32sdk on window procs.
//
// Notes:
//
LRESULT CWebImageControl::WindowProc
(
    UINT   msg,
    WPARAM wParam,
    LPARAM lParam
)
{
    // TODO: handle any messages here, like in a normal window
    // proc.  note that for special keys, you'll want to override and
    // implement OnSpecialKey.
    //
    return OcxDefWindowProc(msg, wParam, lParam);
}

//=--------------------------------------------------------------------------=
// CWebImageControl::AboutBox
//=--------------------------------------------------------------------------=
// prints up an about box.  fweeeee.
//
// Notes:
//
void CWebImageControl::AboutBox
(
    void
)
{
    // TODO: Ideally, one would use DialogBox, and some sort of Dialog Box here if
    // they wanted a slightly more interesting About Box ...  you should
    // still call ModalDialog first, however.
    //
    ModalDialog(TRUE);
    MessageBox(NULL, "This is My Control", "About WebImage", MB_OK | MB_TASKMODAL);
    ModalDialog(FALSE);
}

STDMETHODIMP  CWebImageControl::get_Image(BSTR * path)
{
	CHECK_POINTER(path);

	// Actually we need to be accepting (happily IMoniker objects)

//	path->vt = VT_BSTR;
		
	BSTR * pbstrPath = path; //&path->bstrVal;
    
    *pbstrPath = (m_bmpPath && *m_bmpPath) ? BSTRFROMANSI(m_bmpPath) : SysAllocString(L"");

    return (*pbstrPath) ? S_OK : E_OUTOFMEMORY;
}

STDMETHODIMP  CWebImageControl::put_Image(BSTR path)
{
	// NOTE: We should reference and IMoniker*!!

//	if( path.vt != VT_BSTR )
//		return(E_UNEXPECTED);

	BSTR & bstrPath = path; //.bstrVal;
    // get an ANSI pointer, so we can stuff it in our local buffer for captions!
    //

    MAKE_ANSIPTR_FROMWIDE(pszPath, bstrPath);

	HRESULT hr = SetBmpPath(pszPath);

	// update anybody who cares about property changes and mark ourselves
	// as dirty
	//
	PropertyChanged(DISPID_BMPPATH);
	m_fDirty = TRUE;

    return hr;
}

STDMETHODIMP  CWebImageControl::Scramble()
{
	HRESULT hr;

        if (m_dib)
	{
		unsigned char * p = m_dib->Base();
		DWORD			dw = m_dib->ImageSize();

		for( DWORD i = 0; i < dw; i+=3,p+=3 )
			*p ^= 0x55;

		InvalidateControl(0);

		hr = S_OK;
	}
	else
	{
		hr = E_FAIL; // E_PENDING;
	}


	return(hr);
}

HRESULT CWebImageControl::SetBmpPath(const char *psz)
{
    // if it hasn't changed, don't waste any time.
    //
    if (psz && m_bmpPath )
	{
		CHECK_POINTER(psz);
		if( !lstrcmp(m_bmpPath, psz) )
			return S_OK;
	}

	if( m_bmpPath )
		delete [] m_bmpPath;

	if(!psz)
	{
		m_bmpPath = 0;
		return(S_OK);
	}

	CHECK_POINTER(psz);

	if( !*psz )
	{
		m_bmpPath = 0;
		return(S_OK);
	}

	DWORD dw = lstrlen(psz);

	m_bmpPath = new char[dw + 1];

	if( !m_bmpPath )
	{
		FAIL("No memory");
		return(E_OUTOFMEMORY);
	}

	lstrcpy(m_bmpPath, psz);

        UpdateImage();

	return(S_OK);
}

HRESULT CWebImageControl::SetBmpPath(IStream * strm)
{
	CHECK_POINTER(strm);

	char * tmp = 0;

	if( m_bmpPath )
		delete [] m_bmpPath;

	DWORD	dw;
	HRESULT hr = strm->Read(&dw,sizeof(dw),0);

	if( SUCCEEDED(hr) )
	{
		if( !dw )
		{
			hr = S_OK;
		}
		else
		{
			tmp = new char[dw+1];

			if( !tmp )
			{
				FAIL("No memory");
				hr = E_OUTOFMEMORY;
			}
			else
			{
				hr = strm->Read(tmp,dw+1,0);
			}
		}
	}

	// if it hasn't changed, don't waste any time.
    //
    if ((!tmp && !m_bmpPath) || !lstrcmp(m_bmpPath, tmp))
        return S_OK;

	if( m_bmpPath )
		delete [] m_bmpPath;

	m_bmpPath = tmp;

        UpdateImage();

	return(hr);
}

HRESULT CWebImageControl::UpdateImage()
{
	if( !m_hwnd )
		return(S_OK);

	if( !m_bmpPath )
		return(S_OK);

	return( SetupDownload(OLESTRFROMANSI(m_bmpPath),DISPID_BMPPATH) );
}


//=--------------------------------------------------------------------------=
// CWebImageControl::OnData
//=--------------------------------------------------------------------------=
//
// Parameters:
//    DISPID	propId		- [in]  Same dispId that was passed into SetupDownload
//    DWORD		grfBSCF		- [in]  Notification flags ("URL Moniker" specification)
//    IStream *	strm		- [in]  Stream to read data from
//    DWORD		dwSize		- [in]  Overall size available so far
//
//
//	Notes:	This is the class that is monitering and interpreting the bits that
//	are being downloaded. The methods in class inherited from IBindStatusCallback
//	are only called during 'DispatchMessage' calls from the main applications loop.
//	This impelmentation maintains a state machine for the bits as they arrive:
//
//		Initial state:			No bits have been seen yet
//
//              Have BITMAPFILEHEADER   We now have this structure. At this point there is
//								enough information to calculate the following values:
//									- The file is actually a Windows BMP file
//									- The size of the entire image
//									- This size of the BITMAPINFO structure
//
//		Have BITMAPINFO			We now have enough information to call 
//								CreateDibSection! That function will return a 
//								a buffer it allocated.
//
//		Getting BITS			At this point the bits are arriving and all we 
//								have to do is strm->Read the bits directly into
//								buffer returned from the step above and notify
//								our view sink that we need refreshing.
//
//		BITS are done			(nothing to do!?)
//
HRESULT CWebImageControl::OnData
(
	DISPID		propId,
	DWORD		grfBSCF,
	IStream *	strm,
	DWORD		dwSize
)
{
	HRESULT		hr		= NOERROR;

	switch(m_state)
	{
		case bdsNoBitsYet:
			{
				if( dwSize >= sizeof(BITMAPFILEHEADER) )
				{
                    CHECK_POINTER(strm);
                    strm->AddRef();

					if( m_dibFile )
						delete m_dibFile;

					m_dibFile = new CDibFile;

					if( !m_dibFile )
					{
						hr = E_OUTOFMEMORY;
						break;
					}

					hr = m_dibFile->GetFileHeader(strm);

					if( FAILED(hr) )
						break;

					m_state = bdsGotFileHeader;

					// now FALL THRU!
				}
				else
				{
					break;
				}
			}
		
		case bdsGotFileHeader:
			{
				if( dwSize >= (m_dibFile->HeaderSize() + sizeof(BITMAPFILEHEADER)) )
				{
					if( m_dibFile )
						hr = m_dibFile->GetInfoHeader(strm);
					else
						hr = E_OUTOFMEMORY;

					if( FAILED(hr) )
						break;

					if( m_dib )
						delete m_dib;

					m_dib = new CDibSection;

					if( !m_dib )
					{
						hr = E_OUTOFMEMORY;
						break;
					}

					m_dib->Setup(m_dc);

					hr = m_dib->Create(*m_dibFile);

					if( FAILED(hr) )
						break;

					m_dib->ImageSize( m_dibFile->CalcImageSize() );
					m_state = bdsGotBitmapInfo;

					// FALL THRU!

				}
				else
				{
					break;
				}
			}
		
		case bdsGotBitmapInfo:
			{
				SIZEL	sz;
				m_dib->GetSize(sz);
				SetControlSize(&sz);

				// we need m_dibFile for printing
				//delete m_dibFile;
				//m_dibFile = 0;

				m_state = bdsGettingBits;

				// FALL THRU
			}

		case bdsGettingBits:
			{
				if( dwSize > 0 )
				{
					hr = m_dib->ReadFrom( strm, dwSize );

					if( FAILED(hr) )
						break;

					::RealizePalette(m_dc);

					m_dib->PaintTo(m_dc);
				}

				if( grfBSCF & BSCF_LASTDATANOTIFICATION )
					m_state = bdsBitsAreDone;
				else
					break;
			}
		
		case bdsBitsAreDone:
			{
				m_state = bdsNoBitsYet;
                strm->Release();
				break;
			}
		
	}

	return(hr);
}
