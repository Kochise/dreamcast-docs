// CContainerInfoDlg.Cpp : implementation file
//

#include "StdAfx.H"
#include "TestCon.H"
#include "resource.hm"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CContainerInfoDlg dialog


CContainerInfoDlg::CContainerInfoDlg( CWnd* pParent,
   CTestContainer98Doc* pDoc ) :
   CDialog( CContainerInfoDlg::IDD, pParent ),
   m_pDoc( pDoc )
{
   ASSERT( m_pDoc != NULL );

	//{{AFX_DATA_INIT(CContainerInfoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CContainerInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CContainerInfoDlg)
	DDX_Control(pDX, IDC_OBJECTS, m_listObjects);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CContainerInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CContainerInfoDlg)
	ON_WM_HELPINFO()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CContainerInfoDlg message handlers

BOOL CContainerInfoDlg::OnInitDialog()
{
   POSITION posItem;
   CTestContainer98Item* pItem;
   int iItem;
   CString strItemName;
   CString strState;
   CString strObject;
   CString strWindowStatus;
   int nAutoWidth;
   int nAutoHeaderWidth;

	CDialog::OnInitDialog();

   strObject.LoadString( IDS_CONTAINERINFOOBJECTHEADER );
   m_listObjects.InsertColumn( 0, strObject, LVCFMT_LEFT, 100 );

   strState.LoadString( IDS_CONTAINERINFOSTATEHEADER );
   m_listObjects.InsertColumn( 1, strState, LVCFMT_LEFT, 100 );

   strWindowStatus.LoadString( IDS_CONTAINERINFOWINDOWHEADER );
   m_listObjects.InsertColumn( 2, strWindowStatus, LVCFMT_LEFT, 100 );

   iItem = 0;
   posItem = m_pDoc->GetStartPosition();
   while( posItem != NULL )
   {
	  pItem = (CTestContainer98Item*)m_pDoc->GetNextItem( posItem );
	  strItemName = pItem->GetDisplayName();
	  m_listObjects.InsertItem( iItem, strItemName );
	  m_listObjects.SetItemText( iItem, 0, strItemName );
	  switch( pItem->GetItemState() )
	  {
	  case COleClientItem::activeState:
		 strState.LoadString( IDS_ACTIVESTATE );
		 if( pItem->IsWindowless() )
		 {
			strWindowStatus.LoadString( IDS_WINDOWLESS );
		 }
		 else
		 {
			strWindowStatus.LoadString( IDS_WINDOWED );
		 }
		 break;

	  case COleClientItem::activeUIState:
		 strState.LoadString( IDS_UIACTIVESTATE );
		 if( pItem->IsWindowless() )
		 {
			strWindowStatus.LoadString( IDS_WINDOWLESS );
		 }
		 else
		 {
			strWindowStatus.LoadString( IDS_WINDOWED );
		 }
		 break;

	  case COleClientItem::openState:
		 strState.LoadString( IDS_OPENSTATE );
		 strWindowStatus.Empty();
		 break;

	  case COleClientItem::loadedState:
		 strState.LoadString( IDS_LOADEDSTATE );
		 strWindowStatus.Empty();
		 break;

	  case COleClientItem::emptyState:
		 strState.LoadString( IDS_EMPTYSTATE );
		 strWindowStatus.Empty();
		 break;

	  default:
		 ASSERT( FALSE );
		 break;
	  }
	  m_listObjects.SetItemText( iItem, 1, strState );
	  m_listObjects.SetItemText( iItem, 2, strWindowStatus );
	  iItem++;
   }

   m_listObjects.SetColumnWidth( 0, LVSCW_AUTOSIZE );
   nAutoWidth = m_listObjects.GetColumnWidth( 0 );
   m_listObjects.SetColumnWidth( 0, LVSCW_AUTOSIZE_USEHEADER );
   nAutoHeaderWidth = m_listObjects.GetColumnWidth( 0 );
   m_listObjects.SetColumnWidth( 0, max( nAutoWidth, nAutoHeaderWidth ) );

   m_listObjects.SetColumnWidth( 1, LVSCW_AUTOSIZE );
   nAutoWidth = m_listObjects.GetColumnWidth( 1 );
   m_listObjects.SetColumnWidth( 1, LVSCW_AUTOSIZE_USEHEADER );
   nAutoHeaderWidth = m_listObjects.GetColumnWidth( 1 );
   m_listObjects.SetColumnWidth( 1, max( nAutoWidth, nAutoHeaderWidth ) );

   m_listObjects.SetColumnWidth( 2, LVSCW_AUTOSIZE );
   nAutoWidth = m_listObjects.GetColumnWidth( 2 );
   m_listObjects.SetColumnWidth( 2, LVSCW_AUTOSIZE_USEHEADER );
   nAutoHeaderWidth = m_listObjects.GetColumnWidth( 2 );
   m_listObjects.SetColumnWidth( 2, max( nAutoWidth, nAutoHeaderWidth ) );

	return( TRUE );
}

static DWORD rgmapCHID[] =
{
   IDC_OBJECTS, HIDC_OBJECTS,
   0, 0
};

BOOL CContainerInfoDlg::OnHelpInfo( HELPINFO* pHelpInfo )
{
   return( ::WinHelp( HWND( pHelpInfo->hItemHandle ),
	  AfxGetApp()->m_pszHelpFilePath, HELP_WM_HELP, DWORD( LPVOID(
	  rgmapCHID ) ) ) );
}

void CContainerInfoDlg::OnContextMenu( CWnd* pWnd, CPoint /* point */ )
{
   ::WinHelp( HWND( *pWnd ), AfxGetApp()->m_pszHelpFilePath, HELP_CONTEXTMENU,
	  DWORD( LPVOID( rgmapCHID ) ) );
}
