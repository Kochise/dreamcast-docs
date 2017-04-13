// CMethodDlg.Cpp : implementation file
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
// CMethodDlg dialog


CMethodDlg::CMethodDlg( CWnd* pParent, IDispatch* pDispatch,
   CInterfaceInfo* pInterfaceInfo ) :
   CDialog( CMethodDlg::IDD, pParent ),
   m_pDispatch( pDispatch ),
   m_pInterfaceInfo( pInterfaceInfo ),
   m_pMethodInfo( NULL ),
   m_pvarParams( NULL ),
   m_piParamTypes( NULL ),
   m_pvarCurrentParam( NULL ),
   m_tException( FALSE )
{
   _ASSERTE( m_pDispatch != NULL );
   _ASSERTE( m_pInterfaceInfo != NULL );

   //{{AFX_DATA_INIT(CMethodDlg)
   //}}AFX_DATA_INIT
}

CMethodDlg::~CMethodDlg()
{
   delete[] m_pvarParams;
   delete[] m_piParamTypes;
}

void CMethodDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMethodDlg)
	DDX_Control(pDX, IDC_STATIC_PARAMETERVALUE, m_staticParameterValue);
	DDX_Control(pDX, IDC_EXCEPTIONDESC, m_editExceptionDesc);
	DDX_Control(pDX, IDC_EXCEPTIONSOURCE, m_editExceptionSource);
	DDX_Control(pDX, IDC_RETURNVALUE, m_editReturnValue);
	DDX_Control(pDX, IDC_PARAMVALUE, m_editParamValue);
	DDX_Control(pDX, IDC_PARAMS, m_listParams);
	DDX_Control(pDX, IDC_PARAMTYPE, m_cboxParamType);
	DDX_Control(pDX, IDC_METHODNAME, m_cboxMethodName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMethodDlg, CDialog)
	//{{AFX_MSG_MAP(CMethodDlg)
	ON_CBN_SELCHANGE(IDC_METHODNAME, OnMethodNameSelChange)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_PARAMS, OnParamsItemChanged)
	ON_BN_CLICKED(IDC_SETVALUE, OnSetValue)
	ON_BN_CLICKED(IDC_INVOKE, OnInvoke)
	ON_EN_SETFOCUS(IDC_PARAMVALUE, OnParamValueSetFocus)
	ON_EN_CHANGE(IDC_PARAMVALUE, OnParamValueChange)
	ON_BN_CLICKED(IDC_EXCEPTIONHELP, OnExceptionHelp)
	ON_CBN_SELCHANGE(IDC_PARAMTYPE, OnParamTypeSelChange)
	ON_BN_CLICKED(IDC_CHOOSECOLOR, OnChooseColor)
	ON_BN_CLICKED(IDC_CHOOSEFONT, OnChooseFont)
	ON_WM_HELPINFO()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMethodDlg message handlers

BOOL CMethodDlg::OnInitDialog()
{
   int iMethod;
   int iType;
   int iItem;
   CMethodInfo* pMethodInfo;
   CString strMethodName;
   CString strColumnName;

   CDialog::OnInitDialog();

   // Populate the method name combo box with the names of all of the methods
   // on this interface.
   for( iMethod = 0; iMethod < m_pInterfaceInfo->GetNumMethods(); iMethod++ )
   {
	  pMethodInfo = m_pInterfaceInfo->GetMethod( iMethod );

	  // Add on a description of the method type (propget, propput, etc.).
	  strMethodName = pMethodInfo->GetName();
	  strMethodName += _T( " (" );
	  strMethodName += InvokeKindToString( pMethodInfo->GetInvokeKind() );
	  strMethodName += _T( ")" );

	  m_cboxMethodName.AddString( strMethodName );
   }

   // Add the appropriate columns to the parameter list control.
   strColumnName.LoadString( IDS_PARAMETER );
   m_listParams.InsertColumn( 0, strColumnName, LVCFMT_LEFT, 125 );
   strColumnName.LoadString( IDS_VALUE );
   m_listParams.InsertColumn( 1, strColumnName, LVCFMT_LEFT, 150 );
   strColumnName.LoadString( IDS_TYPE );
   m_listParams.InsertColumn( 2, strColumnName, LVCFMT_LEFT, 100 );

   m_listParams.SetColumnWidth( 2, LVSCW_AUTOSIZE_USEHEADER );

   // Add all available VARTYPEs to the parameter type combo box.
   for( iType = 0; iType < NUM_VARTYPES; iType++ )
   {
	  iItem = m_cboxParamType.AddString( VTIToString( iType ) );
	  m_cboxParamType.SetItemData( iItem, iType );
   }

   m_cboxMethodName.SetCurSel( 0 );
   OnMethodNameSelChange();

   return( TRUE );
}

void CMethodDlg::OnMethodNameSelChange()
{
   int iMethod;
   int iParam;
   CMethodParamInfo* pParamInfo = 0;
   COleVariant* pvarParam = 0;

   iMethod = m_cboxMethodName.GetCurSel();
   ASSERT( iMethod != CB_ERR );
   m_pMethodInfo = m_pInterfaceInfo->GetMethod( iMethod );

   // Clean up from the old method.
   m_varResult.Clear();
   m_editReturnValue.SetWindowText( _T( "" ) );
   m_editParamValue.SetWindowText( _T( "" ) );
   m_listParams.DeleteAllItems();
   delete[] (COleVariant*)m_pvarParams;
   m_pvarParams = NULL;
   m_pvarCurrentParam = NULL;
   delete[] m_piParamTypes;
   m_piParamTypes = NULL;
   m_excepInfo.Clear();
   m_editExceptionSource.SetWindowText( _T( "" ) );
   m_editExceptionDesc.SetWindowText( _T( "" ) );
   GetDlgItem( IDC_EXCEPTIONHELP )->EnableWindow( FALSE );

   // Allocate the parameters for the new method.
   if( m_pMethodInfo->GetNumParams() > 0 )
   {
	  m_pvarParams = new COleVariant[m_pMethodInfo->GetNumParams()];
	  m_piParamTypes = new int[m_pMethodInfo->GetNumParams()];
   }

   // Fill in the info for each parameter.
   for( iParam = 0; iParam < m_pMethodInfo->GetNumParams(); iParam++ )
   {
	  pParamInfo = m_pMethodInfo->GetParam( iParam );
	  m_listParams.InsertItem( iParam, pParamInfo->GetName() );
	  m_listParams.SetItemText( iParam, 0, pParamInfo->GetName() );
	  TRY
	  {
		 pvarParam = GetParam( iParam );
		 pvarParam->ChangeType( pParamInfo->GetType() );
	  }
	  CATCH( COleException, e )
	  {
		 TRACE( "Warning: ChangeType failed during initialization.\n" );
	  }
	  END_CATCH
	  m_piParamTypes[iParam] = VTToVTI( pvarParam->vt );

	  DisplayParamValueInList( iParam );
   }

   if( m_pMethodInfo->GetNumParams() > 0 )
   {
	  // Enable the parameter entry controls.
	  m_cboxParamType.EnableWindow( TRUE );

	  // Select the first parameter.
	  m_listParams.SetItemState( 0, LVIS_SELECTED, LVIS_SELECTED );

	  // Let the user start editing the first parameter's value.
	  if( m_editParamValue.IsWindowEnabled() )
	  {
		 m_editParamValue.SetSel( 0, -1 );
	  }
   }
   else
   {
	  // OnParamsItemChanged isn't going to update the parameter type combo
	  // box, so do it here.
	  m_cboxParamType.SetCurSel( -1 );
	  OnParamTypeSelChange();

	  // Disable the parameter entry controls.
	  m_cboxParamType.EnableWindow( FALSE );

	  // Set the Invoke button to be the default.
	  SetDefID( IDC_INVOKE );
   }
}

void CMethodDlg::OnParamsItemChanged( NMHDR* pNMHDR, LRESULT* pResult )
{
   NM_LISTVIEW* pNMListView;

   pNMListView = (NM_LISTVIEW*)pNMHDR;
   *pResult = 0;

   if( pNMListView->uChanged&LVIF_STATE )
   {
	  if( pNMListView->uNewState&LVIS_SELECTED )
	  {
		 // Display the info for the new parameter
		 m_iCurrentParam = pNMListView->iItem;
		 m_pParamInfo = m_pMethodInfo->GetParam( m_iCurrentParam );
		 m_pvarCurrentParam = GetParam( m_iCurrentParam );
//         m_cboxParamType.SetCurSel( m_piParamTypes[m_iCurrentParam] );
		 m_cboxParamType.SelectString( -1, VTIToString( m_piParamTypes[
			m_iCurrentParam] ) );
		 OnParamTypeSelChange();
//         DisplayParamValue( m_iCurrentParam );
	  }
   }
}

void CMethodDlg::OnSetValue()
{
   int iType;
   int iItem;
   CString strEditText;
   COleVariant varDisplay;
   CString strValue;

   m_editParamValue.GetWindowText( strEditText );

   *m_pvarCurrentParam = strEditText;

   TRY
   {
	  iItem = m_cboxParamType.GetCurSel();
	  ASSERT( iItem != CB_ERR );
	  iType = m_cboxParamType.GetItemData( iItem );
	 m_pvarCurrentParam->ChangeType( VTIToVT( iType ) );
	  DisplayParamValueInList( m_iCurrentParam );
	  m_piParamTypes[m_iCurrentParam] = iType;
	  if( m_iCurrentParam == (m_pMethodInfo->GetNumParams()-1) )
	  {
		 // We just set the last parameter, so set the Invoke button to be the
		 // default button.
		 SetDefID( IDC_INVOKE );
	  }
	  else
	  {
		 // Move on to the next parameter.
		 m_listParams.SetItemState( m_iCurrentParam+1, LVIS_SELECTED,
			LVIS_SELECTED );
		 SetDefID( IDC_SETVALUE );
		 m_editParamValue.SetSel( 0, -1 );
	  }
   }
   CATCH( COleException, e )
   {
	  TRACE( "ChangeType() failed.\n" );
   }
   END_CATCH
}

void CMethodDlg::OnInvoke()
{
   DISPPARAMS dpParams;
   HRESULT hResult;
   UINT iArgErr;
   DISPID dispidArg;
   CString strReturnValue;

   if( m_pvarCurrentParam != NULL )
   {
	  OnSetValue();
   }

   dpParams.rgvarg = m_pvarParams;
   dpParams.cArgs = m_pMethodInfo->GetNumParams();

   if( m_pMethodInfo->GetInvokeKind() == DISPATCH_PROPERTYPUT )
   {
	  dispidArg = DISPID_PROPERTYPUT;
	  dpParams.rgdispidNamedArgs = &dispidArg;
	  dpParams.cNamedArgs = 1;
   }
   else
   {
	  dpParams.rgdispidNamedArgs = NULL;
	  dpParams.cNamedArgs = 0;
   }

   m_varResult.Clear();
   m_excepInfo.Clear();
   m_tException = FALSE;

   TRY
   {
	  hResult = m_pDispatch->Invoke( m_pMethodInfo->GetID(), IID_NULL,
		 GetUserDefaultLCID(), WORD( m_pMethodInfo->GetInvokeKind() ),
		 &dpParams, &m_varResult, &m_excepInfo, &iArgErr );
	  if( FAILED( hResult ) )
	  {

		 TRACE( "Invoke() failed\n" );
	   if( hResult == DISP_E_EXCEPTION )
	   {
		  m_tException = TRUE;
	   }
		 AfxThrowOleException( hResult );
	  }
	  strReturnValue = VariantToString( m_varResult );
	  strReturnValue += _T( " (" );
	  strReturnValue += VTToString( m_varResult.vt );
	  strReturnValue += _T( ")" );
	  m_editReturnValue.SetWindowText( strReturnValue );
   }
   CATCH( COleException, e )
   {
   }
   END_CATCH

   DisplayExceptionInfo();
}

void CMethodDlg::OnParamValueSetFocus()
{
   // The ParamValue edit box just got the keyboard focus.  The user should be
   // able to set the value to the contents of the edit box just by hitting
   // ENTER.
   SetDefID( IDC_SETVALUE );
}

void CMethodDlg::OnParamValueChange()
{
   // The user is typing in the ParamValue edit box, so set the default button
   // to SetValue.
   SetDefID( IDC_SETVALUE );
}

void CMethodDlg::DisplayParamValueInList( int iParam )
{
   COleVariant varDisplay;
   CString strTemp;
   CString strValue;
   COleVariant* pvarParam;

   pvarParam = GetParam( iParam );
   if( m_piParamTypes[iParam] == VTI_COLOR )
   {
	  ASSERT( pvarParam->vt == VT_I4 );
	  strValue.Format( "%#8.8x", pvarParam->lVal );
	  m_listParams.SetItemText( iParam, 1, strValue );
   }
   else
   {
	  TRY
	  {
		 varDisplay.ChangeType( VT_BSTR, pvarParam );
		 strValue = varDisplay.bstrVal;
		 m_listParams.SetItemText( iParam, 1, strValue );
		 m_editParamValue.SetWindowText( strValue );
	  }
	  CATCH( COleException, e )
	  {
		 TRACE( "ChangeType failed\n" );
		 strValue.LoadString( IDS_UNABLETOREPRESENT );
		 m_listParams.SetItemText( iParam, 1, strValue );
		 m_editParamValue.SetWindowText( _T( "" ) );
	  }
	  END_CATCH
   }

   m_listParams.SetItemText( iParam, 2, VTToString( pvarParam->vt ) );
//   m_cboxParamType.SetCurSel( m_piParamTypes[iParam] );
}

COleVariant* CMethodDlg::GetParam( int iParam )
{
   // Dispatch parameters are in reverse order.
   return( &m_pvarParams[(m_pMethodInfo->GetNumParams()-1)-iParam] );
}

void CMethodDlg::DisplayExceptionInfo()
{
   USES_CONVERSION;
   CString strSource;
   CString strDesc;

   if( m_tException )
   {
	  if( m_excepInfo.bstrSource != NULL )
	  {
		 m_editExceptionSource.SetWindowText( OLE2CT(
		   m_excepInfo.bstrSource ) );
	  }
	  else
	  {
		strSource.LoadString( IDS_UNSPECIFIEDSOURCE );
		 m_editExceptionSource.SetWindowText( strSource );
	  }

	  if( m_excepInfo.bstrDescription != NULL )
	  {
		 m_editExceptionDesc.SetWindowText( OLE2CT(
			m_excepInfo.bstrDescription ) );
	  }
	  else
	  {
		strDesc.LoadString( IDS_UNSPECIFIEDEXCEPTION );
		 m_editExceptionDesc.SetWindowText( strDesc );
	  }

	  if( m_excepInfo.bstrHelpFile != NULL )
	  {
		 GetDlgItem( IDC_EXCEPTIONHELP )->EnableWindow( TRUE );
	  }
	  else
	  {
		 GetDlgItem( IDC_EXCEPTIONHELP )->EnableWindow( FALSE );
	  }
   }
   else
   {
	  m_editExceptionSource.SetWindowText( _T( "" ) );
	  m_editExceptionDesc.SetWindowText( _T( "" ) );
	  GetDlgItem( IDC_EXCEPTIONHELP )->EnableWindow( FALSE );
   }
}

void CMethodDlg::OnExceptionHelp()
{
   USES_CONVERSION;

   ASSERT( m_excepInfo.bstrHelpFile != NULL );

   ::WinHelp( AfxGetMainWnd()->GetSafeHwnd(), OLE2CT(
	  m_excepInfo.bstrHelpFile ), HELP_CONTEXT, m_excepInfo.dwHelpContext );
}

void CMethodDlg::OnParamTypeSelChange()
{
   int iType;
   int iItem;

   iItem = m_cboxParamType.GetCurSel();
   if( iItem == CB_ERR )
   {
	  iType = -1;
   }
   else
   {
	  iType = m_cboxParamType.GetItemData( iItem );
   }

   switch( iType )
   {
   case -1:
	  // No type was selected
	  GetDlgItem( IDC_CHOOSEFONT )->EnableWindow( FALSE );
	  GetDlgItem( IDC_CHOOSEFONT )->ShowWindow( SW_HIDE );
	  GetDlgItem( IDC_CHOOSECOLOR )->EnableWindow( FALSE );
	  GetDlgItem( IDC_CHOOSECOLOR )->ShowWindow( SW_HIDE );
	  GetDlgItem( IDC_SETVALUE )->EnableWindow( FALSE );
	  GetDlgItem( IDC_SETVALUE )->ShowWindow( SW_NORMAL );
	  m_staticParameterValue.ShowWindow( SW_NORMAL );
	  m_editParamValue.EnableWindow( FALSE );
	  m_editParamValue.ShowWindow( SW_NORMAL );
	  break;

   case VTI_COLOR:
	  GetDlgItem( IDC_CHOOSEFONT )->EnableWindow( FALSE );
	  GetDlgItem( IDC_CHOOSEFONT )->ShowWindow( SW_HIDE );
	  GetDlgItem( IDC_SETVALUE )->EnableWindow( FALSE );
	  GetDlgItem( IDC_SETVALUE )->ShowWindow( SW_HIDE );
	  m_staticParameterValue.ShowWindow( SW_HIDE );
	  m_editParamValue.EnableWindow( FALSE );
	  m_editParamValue.ShowWindow( SW_HIDE );
	  GetDlgItem( IDC_CHOOSECOLOR )->ShowWindow( SW_NORMAL );
	  GetDlgItem( IDC_CHOOSECOLOR )->EnableWindow( TRUE );
	  break;

   case VTI_FONT:
	  GetDlgItem( IDC_CHOOSECOLOR )->EnableWindow( FALSE );
	  GetDlgItem( IDC_CHOOSECOLOR )->ShowWindow( SW_HIDE );
	  GetDlgItem( IDC_SETVALUE )->EnableWindow( FALSE );
	  GetDlgItem( IDC_SETVALUE )->ShowWindow( SW_HIDE );
	  m_staticParameterValue.ShowWindow( SW_HIDE );
	  m_editParamValue.EnableWindow( FALSE );
	  m_editParamValue.ShowWindow( SW_HIDE );
	  GetDlgItem( IDC_CHOOSEFONT )->ShowWindow( SW_NORMAL );
	  GetDlgItem( IDC_CHOOSEFONT )->EnableWindow( TRUE );
	  break;

   default:
	  GetDlgItem( IDC_CHOOSEFONT )->EnableWindow( FALSE );
	  GetDlgItem( IDC_CHOOSEFONT )->ShowWindow( SW_HIDE );
	  GetDlgItem( IDC_CHOOSECOLOR )->EnableWindow( FALSE );
	  GetDlgItem( IDC_CHOOSECOLOR )->ShowWindow( SW_HIDE );
	  m_staticParameterValue.ShowWindow( SW_NORMAL );
	  m_editParamValue.ShowWindow( SW_SHOWNORMAL );
	  m_editParamValue.EnableWindow( TRUE );
	  GetDlgItem( IDC_SETVALUE )->ShowWindow( SW_NORMAL );
	  GetDlgItem( IDC_SETVALUE )->EnableWindow( TRUE );
	  break;
   }
}

void CMethodDlg::OnChooseColor()
{
   CColorDialog dlg;
   int nResult;

   nResult = dlg.DoModal();
   if( nResult != IDOK )
   {
	  return;
   }

   *m_pvarCurrentParam = long( dlg.GetColor() );
   m_piParamTypes[m_iCurrentParam] = VTI_COLOR;
   DisplayParamValueInList( m_iCurrentParam );
}

void CMethodDlg::OnChooseFont()
{
   USES_CONVERSION;
   CFontDialog dlg;
   int nResult;
   IFontDispPtr pFont;
   FONTDESC desc;
   HRESULT hResult;

   nResult = dlg.DoModal();
   if( nResult != IDOK )
   {
	  return;
   }

   memset( &desc, 0, sizeof( desc ) );
   desc.cbSizeofstruct = sizeof( desc );
   desc.lpstrName = T2OLE( dlg.m_cf.lpLogFont->lfFaceName );
   desc.cySize = COleCurrency( dlg.m_cf.iPointSize/10, 1000*
	  (dlg.m_cf.iPointSize%10) );
   desc.sWeight = short( dlg.m_cf.lpLogFont->lfWeight );
   desc.sCharset = dlg.m_cf.lpLogFont->lfCharSet;
   desc.fItalic = dlg.m_cf.lpLogFont->lfItalic;
   desc.fUnderline = dlg.m_cf.lpLogFont->lfUnderline;
   desc.fStrikethrough = dlg.m_cf.lpLogFont->lfStrikeOut;

   hResult = OleCreateFontIndirect( &desc, IID_IFontDisp, (void**)&pFont );
   if( FAILED( hResult ) )
   {
	  TRACE( "OleCreateFontIndirect() failed\n" );
   }

   m_pvarCurrentParam->Clear();
   m_pvarCurrentParam->vt = VT_DISPATCH;
   m_pvarCurrentParam->pdispVal = pFont;
   m_pvarCurrentParam->pdispVal->AddRef();

   m_piParamTypes[m_iCurrentParam] = VTI_FONT;
   DisplayParamValueInList( m_iCurrentParam );
}

static DWORD rgmapCHID[] =
{
   IDC_METHODNAME, HIDC_METHODNAME,
   IDC_PARAMS, HIDC_PARAMS,
   IDC_INVOKE, HIDC_INVOKE,
   IDC_PARAMVALUE, HIDC_PARAMVALUE,
   IDC_PARAMTYPE, HIDC_PARAMTYPE,
   IDC_SETVALUE, HIDC_SETVALUE,
   IDC_RETURNVALUE, HIDC_RETURNVALUE,
   IDC_EXCEPTIONSOURCE, HIDC_EXCEPTIONSOURCE,
   IDC_EXCEPTIONDESC, HIDC_EXCEPTIONDESC,
   IDC_EXCEPTIONHELP, HIDC_EXCEPTIONHELP,
   IDC_CHOOSECOLOR, HIDC_CHOOSECOLOR,
   IDC_CHOOSEFONT, HIDC_CHOOSEFONT,
   IDC_STATIC_PARAMETERVALUE, DWORD( -1 ),
   0, 0
};

BOOL CMethodDlg::OnHelpInfo( HELPINFO* pHelpInfo )
{
   return( ::WinHelp( HWND( pHelpInfo->hItemHandle ),
	  AfxGetApp()->m_pszHelpFilePath, HELP_WM_HELP, DWORD( LPVOID(
	  rgmapCHID ) ) ) );
}

void CMethodDlg::OnContextMenu( CWnd* pWnd, CPoint /* point */ )
{
   ::WinHelp( HWND( *pWnd ), AfxGetApp()->m_pszHelpFilePath, HELP_CONTEXTMENU,
	  DWORD( LPVOID( rgmapCHID ) ) );
}
