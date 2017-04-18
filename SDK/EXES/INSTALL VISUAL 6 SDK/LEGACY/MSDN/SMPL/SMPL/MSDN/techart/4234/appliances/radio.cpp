// radio.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\impiunk.h"
#include "appliances.h"
#include "..\include\appliancesid.h"
#include "..\include\iapplianceui.h"
#include "..\include\ibitmap.h"
#include "resource.h"
#include "radio.h"
#include "radiodlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRadio

IMPLEMENT_DYNCREATE(CRadio, CCmdTarget)

CRadio::CRadio()
{
	TRACE("CRadio::CRadio()\n");
    m_bIsOn = FALSE;
    m_iStation = 1;
	m_punkBitmap = NULL;
	
	EnableAutomation();
	
	// To keep the application running as long as an OLE automation 
	//	object is active, the constructor calls AfxOleLockApp.
	
	AfxOleLockApp();
}

CRadio::~CRadio()
{
	TRACE("CRadio::~CRadio()\n");
	// To terminate the application when all objects created with
	// 	with OLE automation, the destructor calls AfxOleUnlockApp.
	
	// Make sure the tune stops
    m_mciTune.Stop();

	AfxOleUnlockApp();
}

void CRadio::OnFinalRelease()
{
    // let go of any aggregated objects
    ASSERT(m_punkBitmap);
    m_punkBitmap->Release();

	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}


BEGIN_MESSAGE_MAP(CRadio, CCmdTarget)
	//{{AFX_MSG_MAP(CRadio)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CRadio, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CRadio)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

IMPLEMENT_OLECREATE(CRadio, "Radio", 0x44434a20, 0x4374, 0x11ce, 0x9e, 0xe8, 0x0, 0xaa, 0x0, 0x42, 0x31, 0xbf)

BEGIN_INTERFACE_MAP(CRadio, CCmdTarget)
    INTERFACE_PART(CRadio, IID_IApplianceUI, ApplianceUI)
    INTERFACE_AGGREGATE(CRadio, m_punkBitmap)
END_INTERFACE_MAP()


// IUnknown for IApplianceUI
    IMPLEMENT_IUNKNOWN(CRadio, ApplianceUI)

// IApplianceUI methods
STDMETHODIMP CRadio::XApplianceUI::ShowControl(CWnd* pParent)
{
    METHOD_PROLOGUE(CRadio, ApplianceUI);
    CRadioDlg* pDlg = new CRadioDlg;
    pDlg->m_pRadio = pThis;
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

BOOL CRadio::OnCreateAggregates()
{
    // Create the objects we want to aggregate
    HRESULT hr = ::CoCreateInstance(CLSID_BitmapObject,
                                    GetControllingUnknown(),
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

