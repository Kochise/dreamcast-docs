// SmilePpg.cpp : Implementation of the CSmilePropPage property page class.

#include "stdafx.h"
#include "Smile.h"
#include "SmilePpg.h"

#ifndef _RUNTIME

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CSmilePropPage, COlePropertyPage)

#ifdef _USRDLL
IMPLEMENT_DYNCREATE(CSmileColorPropPage, CColorPropPage)
IMPLEMENT_DYNCREATE(CSmileFontPropPage, CFontPropPage)
#endif

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CSmilePropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CSmilePropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CSmilePropPage, "SMILE.SmilePropPage.1",
	0x175cb004, 0xbeed, 0x11ce, 0x96, 0x11, 0, 0xaa, 0, 0x4a, 0x75, 0xcf);

#ifdef _USRDLL
// {C7AB95CC-A54E-11d0-A2A3-00C04FD91807}
IMPLEMENT_OLECREATE_EX(CSmileColorPropPage, "SMILE.SmileColorPropPage.1",
	0xc7ab95cc, 0xa54e, 0x11d0, 0xa2, 0xa3, 0x0, 0xc0, 0x4f, 0xd9, 0x18, 0x7);
// {C7AB95CD-A54E-11d0-A2A3-00C04FD91807}
IMPLEMENT_OLECREATE_EX(CSmileFontPropPage, "SMILE.SmileFontPropPage.1",
	0xc7ab95cd, 0xa54e, 0x11d0, 0xa2, 0xa3, 0x0, 0xc0, 0x4f, 0xd9, 0x18, 0x7);
#endif

/////////////////////////////////////////////////////////////////////////////
// CSmilePropPage::CSmilePropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CSmilePropPage

BOOL CSmilePropPage::CSmilePropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_Smile_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}

#ifdef _USRDLL
BOOL CSmileColorPropPage::CSmileColorPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_SmileFont_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}

BOOL CSmileFontPropPage::CSmileFontPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_SmileFont_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}
#endif

/////////////////////////////////////////////////////////////////////////////
// CSmilePropPage::CSmilePropPage - Constructor

CSmilePropPage::CSmilePropPage() :
	COlePropertyPage(IDD, IDS_Smile_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CSmilePropPage)
	m_strCaption = _T("");
	m_bSad = FALSE;
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CSmilePropPage::DoDataExchange - Moves data between page and properties

void CSmilePropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CSmilePropPage)
	DDP_Text(pDX, IDC_EDIT1, m_strCaption, _T("Caption") );
	DDX_Text(pDX, IDC_EDIT1, m_strCaption);
	DDP_Check(pDX, IDC_CHECK1, m_bSad, _T("Sad") );
	DDX_Check(pDX, IDC_CHECK1, m_bSad);
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CSmilePropPage message handlers

#endif // !_RUNTIME
