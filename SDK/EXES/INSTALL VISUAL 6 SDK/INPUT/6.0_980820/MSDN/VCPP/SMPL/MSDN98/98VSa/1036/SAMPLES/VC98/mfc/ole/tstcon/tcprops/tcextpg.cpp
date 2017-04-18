// TCExtPg.Cpp : Implementation of CTCExtPage
#include "StdAfx.H"
#include "TCExtPg.H"
#include "TCProps.H"

/////////////////////////////////////////////////////////////////////////////
// CTCExtPage

LRESULT CTCExtPage::OnInitDialog( UINT /* nMessage */, WPARAM /* wParam */,
   LPARAM /* lParam */, BOOL& bHandled )
{
   USES_CONVERSION;
   BSTR bstrName;
   CComQIPtr< ITCExtendedControl, &IID_ITCExtendedControl > pControl;

   pControl = m_ppUnk[0];
   _ASSERTE( pControl != NULL );

   bstrName = NULL;
   pControl->get_Name( &bstrName );
   SetDlgItemText( IDC_NAME, OLE2CT( bstrName ) );
   SysFreeString( bstrName );

   bHandled = TRUE;

   return( FALSE );
}

STDMETHODIMP CTCExtPage::Apply()
{
   UINT iObject;
   BSTR bstrName;

   bstrName = NULL;
   GetDlgItemText( IDC_NAME, bstrName );

	ATLTRACE( _T( "CTCExtPage::Apply\n" ) );
	for( iObject = 0; iObject < m_nObjects; iObject++ )
	{
	  CComPtr< ITCExtendedControl > pControl;

	  m_ppUnk[iObject]->QueryInterface( IID_ITCExtendedControl,
		(void**)&pControl );
	  pControl->put_Name( bstrName );
	  pControl.Release();
   }
   SysFreeString( bstrName );

	m_bDirty = FALSE;

	return( S_OK );
}
