// ComponentCategoriesDlg.Cpp : implementation file
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
// CComponentCategoriesDlg dialog


CComponentCategoriesDlg::CComponentCategoriesDlg( UINT idCaption,
   CWnd* pParent ) :
   CDialog( CComponentCategoriesDlg::IDD, pParent ),
   m_idCaption( idCaption )
{
	//{{AFX_DATA_INIT(CComponentCategoriesDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CComponentCategoriesDlg::DoDataExchange(CDataExchange* pDX)
{
   int iItem;
   int iCategory;
   POSITION posSelectedCategory;
   CATID catid;

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CComponentCategoriesDlg)
	DDX_Control(pDX, IDC_CATEGORIES, m_lbCategories);
	//}}AFX_DATA_MAP

   if( pDX->m_bSaveAndValidate )
   {
	  m_lSelectedCategories.RemoveAll();
	  for( iItem = 0; iItem < m_lbCategories.GetCount(); iItem++ )
	  {
		 if( m_lbCategories.GetCheck( iItem ) )
		 {
			iCategory = m_lbCategories.GetItemData( iItem );
			m_lSelectedCategories.AddTail( m_aAvailableCategories[iCategory] );
		 }
	  }
   }
   else
   {
	  posSelectedCategory = m_lSelectedCategories.GetHeadPosition();
	  while( posSelectedCategory != NULL )
	  {
		 catid = m_lSelectedCategories.GetNext( posSelectedCategory );
		 iCategory = 0;
		 while( (iCategory < m_aAvailableCategories.GetSize()) && !IsEqualGUID(
			m_aAvailableCategories[iCategory], catid ) )
		 {
			iCategory++;
		 }
		 if( iCategory < m_aAvailableCategories.GetSize() )
		 {
			// We found the category
			iItem = 0;
			while( int( m_lbCategories.GetItemData( iItem ) ) != iCategory )
			{
			   iItem++;
			   ASSERT( iItem < m_lbCategories.GetCount() );
			}
			m_lbCategories.SetCheck( iItem, 1 );
		 }
	  }
   }
}


BEGIN_MESSAGE_MAP(CComponentCategoriesDlg, CDialog)
	//{{AFX_MSG_MAP(CComponentCategoriesDlg)
	ON_BN_CLICKED(IDC_SELECTALL, OnSelectAll)
	ON_WM_HELPINFO()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComponentCategoriesDlg message handlers

BOOL CComponentCategoriesDlg::OnInitDialog()
{
   IEnumCATEGORYINFOPtr pEnum;
   HRESULT hResult;
   BOOL tDone;
   CATEGORYINFO info;
   CString strCategory;
   CString strCaption;
   int iItem;
   int iCategory;

	CDialog::OnInitDialog();

   strCaption.LoadString( m_idCaption );
   SetWindowText( strCaption );

   hResult = m_pCatInfo.CreateInstance( CLSID_StdComponentCategoriesMgr, NULL,
	  CLSCTX_INPROC_SERVER );
   if( FAILED( hResult ) )
   {
	  TRACE( "Failed to create category manager.\n" );
	  return( TRUE );
   }

   strCaption.LoadString( m_idCaption );
   SetWindowText( strCaption );

   hResult = m_pCatInfo->EnumCategories( GetUserDefaultLCID(), &pEnum );
   if( FAILED( hResult ) )
   {
	  TRACE( "Failed to enumerate categories.\n" );
	  return( TRUE );
   }

   tDone = FALSE;
   while( !tDone )
   {
	  hResult = pEnum->Next( 1, &info, NULL );
	  if( hResult == S_OK )
	  {
		 strCategory = info.szDescription;
		 iItem = m_lbCategories.AddString( strCategory );
		 iCategory = m_aAvailableCategories.Add( info.catid );
		 m_lbCategories.SetItemData( iItem, iCategory );
	  }
	  else
	  {
		 tDone = TRUE;
	  }
   }

   UpdateData( FALSE );

	return( TRUE );
}

void CComponentCategoriesDlg::OnSelectAll()
{
   m_lbCategories.SelItemRange( TRUE, 0, m_lbCategories.GetCount() );
}

static DWORD rgmapCHID[] =
{
   IDC_CATEGORIES, HIDC_CATEGORIES,
   IDC_SELECTALL, HIDC_SELECTALL,
   0, 0
};

BOOL CComponentCategoriesDlg::OnHelpInfo( HELPINFO* pHelpInfo )
{
   return( ::WinHelp( HWND( pHelpInfo->hItemHandle ),
	  AfxGetApp()->m_pszHelpFilePath, HELP_WM_HELP, DWORD( LPVOID(
	  rgmapCHID ) ) ) );
}

void CComponentCategoriesDlg::OnContextMenu( CWnd* pWnd, CPoint /* point */ )
{
   ::WinHelp( HWND( *pWnd ), AfxGetApp()->m_pszHelpFilePath, HELP_CONTEXTMENU,
	  DWORD( LPVOID( rgmapCHID ) ) );
}
