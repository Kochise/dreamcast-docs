// MSJDragPpg.cpp : Implementation of the CMSJDragPropPage property page class.

#include "stdafx.h"
#include "msjdrag.h"
#include "MSJDragPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CMSJDragPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMSJDragPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CMSJDragPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMSJDragPropPage, "MSJDRAG.MSJDragPropPage.1",
	0xab688444, 0x632f, 0x11cf, 0xa0, 0x18, 0x44, 0x45, 0x53, 0x54, 0, 0)


/////////////////////////////////////////////////////////////////////////////
// CMSJDragPropPage::CMSJDragPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CMSJDragPropPage

BOOL CMSJDragPropPage::CMSJDragPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_MSJDRAG_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CMSJDragPropPage::CMSJDragPropPage - Constructor

CMSJDragPropPage::CMSJDragPropPage() :
	COlePropertyPage(IDD, IDS_MSJDRAG_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CMSJDragPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CMSJDragPropPage::DoDataExchange - Moves data between page and properties

void CMSJDragPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CMSJDragPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CMSJDragPropPage message handlers
