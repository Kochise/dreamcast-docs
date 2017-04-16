// VControlPpg.cpp : Implementation of the CVControlPropPage property page class.

#include "stdafx.h"
#include "VControl.h"
#include "VConPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CVControlPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CVControlPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CVControlPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CVControlPropPage, "VCONTROL.VControlPropPage.1",
	0xf351f23, 0x20db, 0x11cf, 0xaa, 0xc, 0, 0x80, 0xc7, 0x8a, 0x1d, 0x7f)


/////////////////////////////////////////////////////////////////////////////
// CVControlPropPage::CVControlPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CVControlPropPage

BOOL CVControlPropPage::CVControlPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_VCONTROL_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CVControlPropPage::CVControlPropPage - Constructor

CVControlPropPage::CVControlPropPage() :
	COlePropertyPage(IDD, IDS_VCONTROL_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CVControlPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CVControlPropPage::DoDataExchange - Moves data between page and properties

void CVControlPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CVControlPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CVControlPropPage message handlers
