// NewAmbientPropertyDlg.Cpp : implementation file
//

#include "StdAfx.H"
#include "TestCon.H"
#include "Resource.hm"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewAmbientPropertyDlg dialog


CNewAmbientPropertyDlg::CNewAmbientPropertyDlg( CWnd* pParent ) :
   CDialog( CNewAmbientPropertyDlg::IDD, pParent )
{
	//{{AFX_DATA_INIT(CNewAmbientPropertyDlg)
	m_dispid = 0;
	m_strName = _T("");
	//}}AFX_DATA_INIT
}


void CNewAmbientPropertyDlg::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewAmbientPropertyDlg)
	DDX_Control(pDX, IDC_PROPNAME_NEW, m_editName);
	DDX_Text(pDX, IDC_DISPID_NEW, m_dispid);
	DDX_Text(pDX, IDC_PROPNAME_NEW, m_strName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewAmbientPropertyDlg, CDialog)
	//{{AFX_MSG_MAP(CNewAmbientPropertyDlg)
	ON_WM_HELPINFO()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewAmbientPropertyDlg message handlers

BOOL CNewAmbientPropertyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

   m_editName.SetFocus();
   m_editName.SetSel( 0, -1 );

	return( FALSE );
}


static DWORD rgmapCHID[] =
{
   IDC_PROPNAME_NEW, HIDC_PROPNAME_NEW,
   IDC_DISPID_NEW, HIDC_DISPID_NEW,
   0, 0
};

BOOL CNewAmbientPropertyDlg::OnHelpInfo( HELPINFO* pHelpInfo )
{
   return( ::WinHelp( HWND( pHelpInfo->hItemHandle ),
	  AfxGetApp()->m_pszHelpFilePath, HELP_WM_HELP, DWORD( LPVOID(
	  rgmapCHID ) ) ) );
}

void CNewAmbientPropertyDlg::OnContextMenu( CWnd* pWnd, CPoint /* point */ )
{
   ::WinHelp( HWND( *pWnd ), AfxGetApp()->m_pszHelpFilePath, HELP_CONTEXTMENU,
	  DWORD( LPVOID( rgmapCHID ) ) );
}
