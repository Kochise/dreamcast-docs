#include "stdafx.h"
#include "combase.h"
#include "..\include\appliancesid.h"
#include "..\include\iapplianceui.h"
#include "..\include\idrawing.h"
#include "..\include\ibitmap.h"
#include "resource.h"
#include "CRadio.h"
#include "radiodlg.h"


//
// Constructor
//
CRadio::CRadio(IUnknown* pUnk, HRESULT* phr)
	: CUnknown(pUnk, phr) 
{
   m_bIsOn = FALSE;
   m_iStation = 1;
	m_punkBitmap = NULL;
}

//
// Destructor
//
CRadio::~CRadio() 
{
    ASSERT(m_punkBitmap);
    m_punkBitmap->Release();

	// Make sure the tune stops
    m_mciTune.Stop();
}

//
// CreateInstance is called by CClassFactory
//
CUnknown* CRadio::CreateInstance(IUnknown* pUnk, HRESULT* phr)
{
	CRadio* pNewObject = new CRadio(pUnk, phr) ;
	if (pNewObject == NULL)
		*phr = E_OUTOFMEMORY ;

	return pNewObject ;
}

//
// OnInit - Use to aggregate the Bitmap Object
//
BOOL CRadio::OnInit()
{
    // Create the objects we want to aggregate
    HRESULT hr = ::CoCreateInstance(CLSID_BitmapObject,
                                    GetOwner(),
                                    CLSCTX_INPROC_SERVER,
                                    IID_IUnknown,
                                    (LPVOID*)&m_punkBitmap);
    if (FAILED(hr)) {
        TRACE("Failed to create object. SCODE: %8.8lXH (%lu)\n",
              GetScode(hr),
              GetScode(hr) & 0x0000FFFF);
        m_punkBitmap = NULL;
        return FALSE;
    }
    ASSERT(m_punkBitmap);

    // get a pointer to the IBitmap interface so we can
    // set up the bitmap we want
    IBitmap* pIBitmap = NULL;
    if (m_punkBitmap->QueryInterface(IID_IBitmap, (LPVOID*)&pIBitmap) != S_OK) {
        TRACE("IBitmap not supported\n");
        return FALSE;
    }

    if (pIBitmap->LoadResource(IDR_DIB_RADIO) != S_OK) {
        TRACE("Failed to load bitmap resource\n");
    }

    // done with the interface now
    pIBitmap->Release();

    return TRUE;	
}


// Overload to support IApplianceUI 
// IBitmap and IDrawing support via aggregation.
HRESULT __stdcall CRadio::NonDelegatingQueryInterface(REFIID riid, void** ppv)
{
	if (riid == IID_IApplianceUI)
	{
		return GetInterface((IApplianceUI*)this, ppv) ;
	}
	else if ((riid == IID_IBitmap) || (riid == IID_IDrawing))
	{
		return m_punkBitmap->QueryInterface(riid, ppv);
	}
	else
	{
		return CUnknown::NonDelegatingQueryInterface(riid, ppv) ;
	}
}

//
//
// IApplianceUI Inteface Implementation
//
//

//
// ShowControl
//
HRESULT __stdcall CRadio::ShowControl(CWnd* pParent)
{
    CRadioDlg* pDlg = new CRadioDlg;
    pDlg->m_pRadio = this;
    pDlg->Create(pParent);
    return NOERROR;
}

/////////////////////////////////////////////////////////////////
// Direct object control functions 

void CRadio::Power(BOOL b)
{
    if (b == m_bIsOn) return;
    m_bIsOn = b;

    if (!m_bIsOn) {
        
        // Stop any tune that's playing
        m_mciTune.Stop();

    } else {

        // Play the current selection
        SetStation(m_iStation);
    }
}

//
//
//
BOOL CRadio::SetStation(int iStation)
{
    // radio has four stations 1 - 4
    if ((iStation < 1) || (iStation > 4)) return FALSE;
    m_iStation = iStation;
    if (!m_bIsOn) return TRUE;

    // Start this tune playing
    m_mciTune.Stop();

    char szTune[32];
    sprintf(szTune, "radio%d.mid", m_iStation);
    if (!m_mciTune.OpenFile(szTune)) {
        AfxMessageBox("Station not on the air.\n(Can't find MIDI file.)");
        return FALSE;
    }
    m_mciTune.Play();
    return TRUE;
}
