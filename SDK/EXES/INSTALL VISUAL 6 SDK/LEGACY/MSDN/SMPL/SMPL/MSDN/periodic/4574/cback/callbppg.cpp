// callbppg.cpp : Implementation of the CCallBackPropPage property page class.

#include "stdafx.h"
#include "cback.h"
#include "callbppg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CCallBackPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CCallBackPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CCallBackPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CCallBackPropPage, "CBACK.CallBackPropPage.1",
	0x3d76aaa4, 0x17aa, 0x11cf, 0xa0, 0x18, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0)


/////////////////////////////////////////////////////////////////////////////
// CCallBackPropPage::CCallBackPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CCallBackPropPage

BOOL CCallBackPropPage::CCallBackPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_CALLBACK_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CCallBackPropPage::CCallBackPropPage - Constructor

CCallBackPropPage::CCallBackPropPage() :
	COlePropertyPage(IDD, IDS_CALLBACK_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CCallBackPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CCallBackPropPage::DoDataExchange - Moves data between page and properties

void CCallBackPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CCallBackPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CCallBackPropPage message handlers
