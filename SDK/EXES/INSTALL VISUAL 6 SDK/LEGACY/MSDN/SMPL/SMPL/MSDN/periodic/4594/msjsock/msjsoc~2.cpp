// MSJSockPpg.cpp : Implementation of the CMSJSockPropPage property page class.

#include "stdafx.h"
#include "MSJSock.h"
#include "MSJSockPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CMSJSockPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMSJSockPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CMSJSockPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMSJSockPropPage, "MSJSOCK.MSJSockPropPage.1",
	0x9e638964, 0x2c21, 0x11cf, 0xa0, 0x18, 0x44, 0x45, 0x53, 0x54, 0, 0)


/////////////////////////////////////////////////////////////////////////////
// CMSJSockPropPage::CMSJSockPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CMSJSockPropPage

BOOL CMSJSockPropPage::CMSJSockPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_MSJSOCK_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CMSJSockPropPage::CMSJSockPropPage - Constructor

CMSJSockPropPage::CMSJSockPropPage() :
	COlePropertyPage(IDD, IDS_MSJSOCK_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CMSJSockPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CMSJSockPropPage::DoDataExchange - Moves data between page and properties

void CMSJSockPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CMSJSockPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CMSJSockPropPage message handlers
