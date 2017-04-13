// PropertyEditRequestsPage.Cpp : implementation file
//

#include "StdAfx.H"
#include "TestCon.H"
#include "Resource.hm"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CPropertyEditRequestsPage::CPropertyInfo::CPropertyInfo() :
   m_tLogged( TRUE ),
   m_iResponse( REQUESTEDIT_ALWAYS )
{
}

CPropertyEditRequestsPage::CPropertyInfo::CPropertyInfo( LPCTSTR pszName,
   BOOL tLogged, int iResponse ) :
   m_strName( pszName ),
   m_tLogged( tLogged ),
   m_iResponse( iResponse )
{
}

/////////////////////////////////////////////////////////////////////////////
// CPropertyEditRequestsPage dialog

IMPLEMENT_DYNCREATE( CPropertyEditRequestsPage, CPropertyPage )

CPropertyEditRequestsPage::CPropertyEditRequestsPage() :
   CPropertyPage( CPropertyEditRequestsPage::IDD )
{
   m_psp.dwFlags &= ~PSP_HASHELP;

	//{{AFX_DATA_INIT(CPropertyEditRequestsPage)
	m_iAllowEdit = -1;
	//}}AFX_DATA_INIT
}


void CPropertyEditRequestsPage::DoDataExchange( CDataExchange* pDX )
{
   int iProperty;
   int iItem;

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertyEditRequestsPage)
	DDX_Control(pDX, IDC_PROPERTIES_EDITREQUESTS, m_lbProperties);
	DDX_Radio(pDX, IDC_ALWAYS, m_iAllowEdit);
	//}}AFX_DATA_MAP

   if( m_lbProperties.GetCount() > 0 )
   {
	  for( iItem = 0; iItem < m_lbProperties.GetCount(); iItem++ )
	  {
		 iProperty = m_lbProperties.GetItemData( iItem );
		 if( pDX->m_bSaveAndValidate )
		 {
			m_aProperties[iProperty].m_tLogged = m_lbProperties.GetCheck(
			   iItem );
		 }
		 else
		 {
			m_lbProperties.SetCheck( iItem, m_aProperties[
			   iProperty].m_tLogged != FALSE );
		 }
	  }
   }
}


BEGIN_MESSAGE_MAP(CPropertyEditRequestsPage, CDialog)
	//{{AFX_MSG_MAP(CPropertyEditRequestsPage)
	ON_LBN_SELCHANGE(IDC_PROPERTIES_EDITREQUESTS, OnPropertiesSelChange)
	ON_BN_CLICKED(IDC_ALWAYS, OnAlways)
	ON_BN_CLICKED(IDC_NEVER, OnNever)
	ON_BN_CLICKED(IDC_PROMPT, OnPrompt)
	ON_BN_CLICKED(IDC_SELECTALL_EDITREQUESTS, OnSelectAll)
	ON_WM_HELPINFO()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertyEditRequestsPage message handlers

BOOL CPropertyEditRequestsPage::OnInitDialog()
{
   int iProperty;
   int iItem;

	CDialog::OnInitDialog();

   for( iProperty = 0; iProperty < m_aProperties.GetSize(); iProperty++ )
   {
	  iItem = m_lbProperties.AddString( m_aProperties[iProperty].m_strName );
	  m_lbProperties.SetItemData( iItem, iProperty );
   }

   UpdateData( FALSE );

   OnPropertiesSelChange();

	return( TRUE );
}

void CPropertyEditRequestsPage::OnPropertiesSelChange()
{
   int iResponse;
   CWnd* pAlways;
   CWnd* pNever;
   CWnd* pPrompt;

   pAlways = GetDlgItem( IDC_ALWAYS );
   pNever = GetDlgItem( IDC_NEVER );
   pPrompt = GetDlgItem( IDC_PROMPT );

   if( m_lbProperties.GetSelCount() == 0 )
   {
	  // Nothing is selected, so disable the radio buttons.
	  pAlways->EnableWindow( FALSE );
	  pNever->EnableWindow( FALSE );
	  pPrompt->EnableWindow( FALSE );
   }
   else
   {
	  pAlways->EnableWindow( TRUE );
	  pNever->EnableWindow( TRUE );
	  pPrompt->EnableWindow( TRUE );
   }

   iResponse = GetSelectionResponse();

   pAlways->SendMessage( BM_SETCHECK, 0, 0 );
   pNever->SendMessage( BM_SETCHECK, 0, 0 );
   pPrompt->SendMessage( BM_SETCHECK, 0, 0 );

   switch( iResponse )
   {
   case REQUESTEDIT_ALWAYS:
	  pAlways->SendMessage( BM_SETCHECK, 1, 0 );
	  break;

   case REQUESTEDIT_NEVER:
	  pNever->SendMessage( BM_SETCHECK, 1, 0 );
	  break;

   case REQUESTEDIT_PROMPT:
	  pPrompt->SendMessage( BM_SETCHECK, 1, 0 );
	  break;
   }
}

int CPropertyEditRequestsPage::GetSelectionResponse()
{
   int iProperty;
   int iSelectedItem;
   int* piSelectedItems;
   int iResponse;
   int nSelectedItems;
   int nItemsInBuffer;
   int iMultiResponse;

   nSelectedItems = m_lbProperties.GetSelCount();
   if( nSelectedItems == 0 )
   {
	  iMultiResponse = -1;
   }
   else
   {
	  piSelectedItems = (int*)_alloca( nSelectedItems*sizeof( int ) );
	  nItemsInBuffer = m_lbProperties.GetSelItems( nSelectedItems,
		 piSelectedItems );
	  ASSERT( nItemsInBuffer == nSelectedItems );
	  iProperty = m_lbProperties.GetItemData( piSelectedItems[0] );
	  iMultiResponse = m_aProperties[iProperty].m_iResponse;
	  for( iSelectedItem = 1; iSelectedItem < nSelectedItems; iSelectedItem++ )
	  {
		 iProperty = m_lbProperties.GetItemData( piSelectedItems[
			iSelectedItem] );
		 iResponse = m_aProperties[iProperty].m_iResponse;
		 if( iResponse != iMultiResponse )
		 {
			iMultiResponse = -1;
		 }
	  }
   }

   return( iMultiResponse );
}

void CPropertyEditRequestsPage::SetSelectionResponse( int iResponse )
{
   int iSelectedItem;
   int* piSelectedItems;
   int nSelectedItems;
   int nItemsInBuffer;

   ASSERT( iResponse != -1 );

   nSelectedItems = m_lbProperties.GetSelCount();
   if( nSelectedItems > 0 )
   {
	  piSelectedItems = (int*)_alloca( nSelectedItems*sizeof( int ) );
	  nItemsInBuffer = m_lbProperties.GetSelItems( nSelectedItems,
		 piSelectedItems );
	  ASSERT( nItemsInBuffer == nSelectedItems );
	  for( iSelectedItem = 0; iSelectedItem < nSelectedItems; iSelectedItem++ )
	  {
		 m_aProperties[piSelectedItems[iSelectedItem]].m_iResponse = iResponse;
	  }
   }
}

void CPropertyEditRequestsPage::OnAlways()
{
   SetSelectionResponse( REQUESTEDIT_ALWAYS );
}

void CPropertyEditRequestsPage::OnNever()
{
   SetSelectionResponse( REQUESTEDIT_NEVER );
}

void CPropertyEditRequestsPage::OnPrompt()
{
   SetSelectionResponse( REQUESTEDIT_PROMPT );
}

void CPropertyEditRequestsPage::OnSelectAll()
{
   int nItems;

   nItems = m_lbProperties.GetCount();
   m_lbProperties.SelItemRange( TRUE, 0, nItems-1 );

   OnPropertiesSelChange();
}


static DWORD rgmapCHID[] =
{
   IDC_PROPERTIES_EDITREQUESTS, HIDC_PROPERTIES_EDITREQUESTS,
   IDC_PROMPT, HIDC_PROMPT,
   IDC_ALWAYS, HIDC_ALWAYS,
   IDC_NEVER, HIDC_NEVER,
   IDC_SELECTALL_EDITREQUESTS, HIDC_SELECTALL_EDITREQUESTS,
   0, 0
};

BOOL CPropertyEditRequestsPage::OnHelpInfo( HELPINFO* pHelpInfo )
{
   return( ::WinHelp( HWND( pHelpInfo->hItemHandle ),
	  AfxGetApp()->m_pszHelpFilePath, HELP_WM_HELP, DWORD( LPVOID(
	  rgmapCHID ) ) ) );
}

void CPropertyEditRequestsPage::OnContextMenu( CWnd* pWnd, CPoint /* point */ )
{
   ::WinHelp( HWND( *pWnd ), AfxGetApp()->m_pszHelpFilePath, HELP_CONTEXTMENU,
	  DWORD( LPVOID( rgmapCHID ) ) );
}
