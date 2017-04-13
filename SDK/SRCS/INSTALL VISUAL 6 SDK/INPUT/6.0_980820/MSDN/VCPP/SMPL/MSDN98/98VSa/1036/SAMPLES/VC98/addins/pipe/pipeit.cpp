// PipeIt.cpp : Implementation of CPipeIt
#include "stdafx.h"
#include "pipe.h"
#include "PipeIt.h"
#include "resource.h"
#include "dlgFilter.h"

/////////////////////////////////////////////////////////////////////////////
// CPipeIt

HRESULT CPipeIt::OnConnection(IApplication* pApp, VARIANT_BOOL bFirstTime, long dwAddInID, VARIANT_BOOL* bOnConnection)
{
	HRESULT hr = S_OK;
	CString strCmdFilter;
	CString strCmdNameFilter;

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_spApplication = pApp;
	m_dwAddInID = dwAddInID;

	hr = pApp->SetAddInInfo((long)_Module.GetModuleInstance(), 
		static_cast<IPipeIt*>(this), IDB_TOOLBAR_MEDIUM_PIPEIT, IDB_TOOLBAR_LARGE_PIPEIT, dwAddInID);
	VARIANT_BOOL bRet;
	if (SUCCEEDED(hr))
	{
		strCmdFilter.LoadString(IDS_CMD_FILTER);
		strCmdNameFilter.LoadString(IDS_CMDNAME_FILTER);
		strCmdNameFilter += _T('\n');
		strCmdNameFilter += strCmdFilter;
		hr = pApp->AddCommand(CComBSTR(strCmdNameFilter),CComBSTR(_T("Filter")), 0, dwAddInID, &bRet);
	}

	// Add toolbar buttons only if this is the first time the add-in
	// is being loaded.  Toolbar buttons are automatically remembered
	// by Developer Studio from session to session, so we should only
	// add the toolbar buttons once.
	if (bFirstTime)
	{
		if (SUCCEEDED(hr))
		{
			strCmdNameFilter.LoadString(IDS_CMDNAME_FILTER);
			hr = pApp->AddCommandBarButton(dsGlyph, CComBSTR(strCmdNameFilter), dwAddInID);
		}
	}

	*bOnConnection = SUCCEEDED(hr) ? VARIANT_TRUE :VARIANT_FALSE;
	return hr;
}

HRESULT CPipeIt::OnDisconnection(VARIANT_BOOL bLastTime)
{
	return S_OK;
}

HRESULT CPipeIt::Filter()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// Replace this with the actual code to execute this command
	// Use m_spApplication to access the Developer Studio Application object
	// TODO: WHAT ABOUT BEGINMODELESS??
	CDlgFilter dlgFilter;
	CComPtr<IDispatch> pDispDoc;

	m_spApplication->get_ActiveDocument(&pDispDoc);
	if (pDispDoc) // have a document open. Can reasonably do this...
	{
		dlgFilter.SetApp(m_spApplication);
		dlgFilter.DoModal();
	}

	return S_OK;
}

