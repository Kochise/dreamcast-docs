// ServicesPage.Cpp : implementation file
//

#include "StdAfx.H"
#include "TestCon.H"
#include "Resource.HM"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServicesPage property page

IMPLEMENT_DYNCREATE(CServicesPage, CPropertyPage)

CServicesPage::CServicesPage() : CPropertyPage(CServicesPage::IDD)
{
   m_psp.dwFlags &= ~PSP_HASHELP;

	//{{AFX_DATA_INIT(CServicesPage)
	m_tSBindHost = FALSE;
	//}}AFX_DATA_INIT
}

CServicesPage::~CServicesPage()
{
}

void CServicesPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CServicesPage)
	DDX_Check(pDX, IDC_SBINDHOST, m_tSBindHost);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CServicesPage, CPropertyPage)
	//{{AFX_MSG_MAP(CServicesPage)
	ON_WM_HELPINFO()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServicesPage message handlers


static DWORD rgmapCHID[] =
{
   IDC_SBINDHOST, HIDC_SBINDHOST,
   0, 0
};

BOOL CServicesPage::OnHelpInfo( HELPINFO* pHelpInfo )
{
   return( ::WinHelp( HWND( pHelpInfo->hItemHandle ),
	  AfxGetApp()->m_pszHelpFilePath, HELP_WM_HELP, DWORD( LPVOID(
	  rgmapCHID ) ) ) );
}

void CServicesPage::OnContextMenu( CWnd* pWnd, CPoint /* point */ )
{
   ::WinHelp( HWND( *pWnd ), AfxGetApp()->m_pszHelpFilePath, HELP_CONTEXTMENU,
	  DWORD( LPVOID( rgmapCHID ) ) );
}
