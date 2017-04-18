// BrkPnts.cpp : Implementation of CBrkPnts
#include "stdafx.h"
#include "resource.h"
#include "Brkpntmgr.h"
#include "BrkPnts.h"
#include "DlgBrkPnts.h"
#include <objmodel\dbgdefs.h>

/////////////////////////////////////////////////////////////////////////////
// CBrkPnts

CBrkPnts::CBrkPnts()
{
	m_fOutputWnd = FALSE;
	m_fSaveOnlyEnabled = FALSE;
	m_dwAddInID = NULL;
	m_dwAppEvents = NULL;
	m_pDispBrkPnts = NULL;
}

CBrkPnts::~CBrkPnts()
{
}



HRESULT CBrkPnts::OnConnection(IApplication* pApp, VARIANT_BOOL bFirstTime, long dwAddInID, VARIANT_BOOL* bOnConnection)
{
	HRESULT hr = S_OK;
	m_spApplication = pApp;
	m_dwAddInID = dwAddInID;

	// Connect up to application event sink
	AtlAdvise(pApp, GetUnknown(), IID_IApplicationEvents, &m_dwAppEvents);

	// Connect up to debugger event sink
	CComPtr<IDispatch> pDebugger;
	hr = m_spApplication->get_Debugger(&pDebugger);
	if (SUCCEEDED(hr))
		AtlAdvise(pDebugger, GetUnknown(), IID_IDebuggerEvents, &m_dwDbgEvents);

	hr = pApp->SetAddInInfo((long)_Module.GetModuleInstance(), 
		static_cast<IBrkPnts*>(this), IDB_TOOLBAR_MEDIUM_BRKPNTS, IDB_TOOLBAR_LARGE_BRKPNTS, dwAddInID);
	LPCTSTR szCommand = _T("Break Point Manager");
	VARIANT_BOOL bRet;
	if (SUCCEEDED(hr))
	{
		hr = pApp->AddCommand(CComBSTR(_T("Break Point Manager\nBreak Point Manager\nBreak Point Manager\nBreak Point Manager")),CComBSTR(_T("BrkPntMgr")), 0, dwAddInID, &bRet);
	}

	// Add toolbar buttons only if this is the first time the add-in
	// is being loaded.  Toolbar buttons are automatically remembered
	// by Developer Studio from session to session, so we should only
	// add the toolbar buttons once.
	if (bFirstTime)
	{
		if (SUCCEEDED(hr))
		{
			hr = pApp->AddCommandBarButton(dsGlyph, CComBSTR(_T("Break Point Manager")), dwAddInID);
		}
	}

	*bOnConnection = SUCCEEDED(hr) ? VARIANT_TRUE :VARIANT_FALSE;
	return hr;
}

HRESULT CBrkPnts::OnDisconnection(VARIANT_BOOL bLastTime)
{
	AtlUnadvise(m_spApplication, IID_IApplicationEvents, m_dwAppEvents);
	AtlUnadvise(m_spApplication, IID_IDebuggerEvents, m_dwDbgEvents);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Application events
HRESULT CBrkPnts::BeforeBuildStart()
{
	return S_OK;
}
HRESULT CBrkPnts::BuildFinish(long nNumErrors, long nNumWarnings)
{
	return S_OK;
}
HRESULT CBrkPnts::BeforeApplicationShutDown()
{
	return S_OK;
}
HRESULT CBrkPnts::DocumentOpen(IDispatch* theDocument)
{
	return S_OK;
}
HRESULT CBrkPnts::BeforeDocumentClose(IDispatch* theDocument)
{
	return S_OK;
}
HRESULT CBrkPnts::DocumentSave(IDispatch* theDocument)
{
	return S_OK;
}
HRESULT CBrkPnts::NewDocument(IDispatch* theDocument)
{
	return S_OK;
}
HRESULT CBrkPnts::WindowActivate(IDispatch* theWindow)
{
	return S_OK;
}
HRESULT CBrkPnts::WindowDeactivate(IDispatch* theWindow)
{
	return S_OK;
}
HRESULT CBrkPnts::WorkspaceOpen()
{
	return S_OK;
}
HRESULT CBrkPnts::WorkspaceClose()
{
	return S_OK;
}
HRESULT CBrkPnts::NewWorkspace()
{
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Debugger event
HRESULT CBrkPnts::BreakpointHit(IDispatch* pBreakpoint)
{
	return S_OK;
}

HRESULT CBrkPnts::GetBrkPnts()
{
	HRESULT hr = S_OK;
	if (m_pDispBrkPnts == NULL)
	{
		CComPtr<IDispatch> pDispDebugger;
		CComQIPtr<IDebugger, &IID_IDebugger> pDebugger;

		hr = m_spApplication->get_Debugger(&pDispDebugger);
		pDebugger = pDispDebugger;
		ASSERT(SUCCEEDED(hr));
		if (SUCCEEDED(hr) && pDebugger)
		{
			hr = pDebugger->get_Breakpoints(&m_pDispBrkPnts);
			m_pBrkPnts = m_pDispBrkPnts;
		}
	}
	if (!m_pBrkPnts)
		hr = E_FAIL;
	return(hr);
}

HRESULT CBrkPnts::BrkPntMgr()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	m_spApplication->EnableModeless(VARIANT_FALSE);
	HRESULT hr;
	int iRes;
	CDlgBrkPnts dlgBrkPnts;

	hr = GetBrkPnts();
	ASSERT(SUCCEEDED(hr));
	if (m_pBrkPnts)
	{
		dlgBrkPnts.SetBrkPnts(this);
		iRes = dlgBrkPnts.DoModal();

	}
	m_spApplication->EnableModeless((VARIANT_BOOL)VARIANT_TRUE);
	return S_OK;
}


HRESULT CBrkPnts::Save(BOOL fToOutputWindow, LPCTSTR szFile, BOOL fSaveOnlyEnabled, CString& strComment)
{
	long l, cBrks = 0;
	CStringArray rgStrBrks;
	HRESULT hr;
	
	m_strFile = szFile;
	_ASSERTE(m_pBrkPnts);
	hr = m_pBrkPnts->get_Count(&cBrks);
	l = 0;
	rgStrBrks.Add(strComment); // put the comment string first.
	while (l < cBrks)
	{
		CComPtr<IDispatch> pDispBrkPnt;
		CComQIPtr<IBreakpoint, &IID_IBreakpoint> pBrkPnt;
		CComBSTR bstrLocation;
		CComBSTR bstrFile;
		CComBSTR bstrFunction;
		//long lElements;
		short sEnabled;
		//DsWindowsMessage dsWndMsg;
		//long lPassCount;
		CComBSTR bstrExecutable;
		DsBreakpointType lType;
		CComBSTR bstrWndProc;
		CComVariant varItem = l;
		/* Type:
		dsChangedExpression
		dsLocation
		dsLocationWithTrueExpression
		dsLocationWithChangedExpression
		dsMessage
		dsTrueExpression  
		*/

		hr = m_pBrkPnts->Item(varItem, &pDispBrkPnt);
		pBrkPnt = pDispBrkPnt;

		hr = pBrkPnt->get_Enabled(&sEnabled);
		CString strOut, strT;
		CComBSTR bstrT ;
		hr = pBrkPnt->get_Type((long *)&lType);
		hr = pBrkPnt->get_File(&bstrFile);
		hr = pBrkPnt->get_Function(&bstrFunction);
		hr = pBrkPnt->get_Executable(&bstrExecutable);
		hr = pBrkPnt->get_Location(&bstrLocation);
		strOut.Format("%d:",lType);
		bstrT = bstrFile;
		bstrT.Append(_T("("));
		strT = bstrLocation;
		if (strT.GetAt(0) == _T('.'))
			strT.Delete(0); // remove leading "."
		bstrT.Append(strT);
		bstrT.Append(_T("): "));
		bstrT.Append(strOut);
		bstrT.AppendBSTR(bstrExecutable);
		bstrT.Append(_T(";"));
		bstrT.AppendBSTR(bstrFunction);
		bstrT.Append(_T(";"));
		if (fToOutputWindow)
		{
			m_spApplication->PrintToOutputWindow(bstrT);
		}

		if (sEnabled || !fSaveOnlyEnabled)
		{
			strT = bstrT;
			rgStrBrks.Add(strT);
		}
		
		l++;
	}
	// save out the breakpoints
	if (!m_strFile.IsEmpty())
	{
		CFile fileBrkList;
		if (m_strFile.ReverseFind(_T('.')) == -1)
		{
			m_strFile += _T(".brk"); // add the missing extension
		}
		TRY
		{
			if (fileBrkList.Open(m_strFile, CFile::modeCreate | CFile::modeWrite))
			{
			CArchive ar( &fileBrkList, CArchive::store);
			
			rgStrBrks.Serialize(ar);
			}
		}
		CATCH(CFileException, e)
		{
			CString strMsg;
			CString strErr;
			e->GetErrorMessage(strErr.GetBuffer(_MAX_PATH), _MAX_PATH);
			strErr.ReleaseBuffer();
			strMsg.Format("%s \n    %s", strErr, m_strFile);
			MessageBox(NULL, strMsg, _T("Breakpoint Files"), MB_OK);
		}
		END_CATCH
	}
	return(S_OK);
}

HRESULT CBrkPnts::Load(LPCTSTR szFile, CString& strComment)
{
	CStringArray rgStrBrks, rgStrBrksFailed;
	CString strBrk;
	CComBSTR bstrT;
	HRESULT hr;

	m_strFile = szFile;
	if (!m_strFile.IsEmpty())
	{
		CFile fileBrkList;
		if (m_strFile.ReverseFind(_T('.')) == -1)
		{
			m_strFile += _T(".brk"); // add the missing extension
		}
		TRY
		{
			if (fileBrkList.Open(m_strFile, CFile::modeRead))
			{
			CArchive ar( &fileBrkList, CArchive::load);

			rgStrBrks.Serialize(ar);
			}
		}
		CATCH(CFileException, e)
		{
			CString strMsg;
			CString strErr;
			e->GetErrorMessage(strErr.GetBuffer(_MAX_PATH), _MAX_PATH);
			strErr.ReleaseBuffer();
			strMsg.Format("%s \n    %s", strErr, m_strFile);
			MessageBox(NULL, strMsg, _T("Breakpoint Files"), MB_OK);
		}
		END_CATCH;
		if (rgStrBrks.GetUpperBound() >= 0)
		{
			int i, ich;
			long l;
			i = 0;
			if (i <= rgStrBrks.GetUpperBound())
			{
				strComment = rgStrBrks.GetAt(i);
				i++;
			}
			while (i <= rgStrBrks.GetUpperBound())
			{	
				CString strLine;
				CComVariant varSel;
				CComPtr<IGenericDocument> pDoc = NULL;
				CComQIPtr<ITextDocument, &IID_ITextDocument> pTextDoc;
				CComPtr<IDispatch> pDispBrkPnt;
				CComPtr<IDispatch> pDispSel;
				CComQIPtr<ITextSelection, &IID_ITextSelection> pSel;
				strBrk = rgStrBrks.GetAt(i);
				ich = strBrk.Find(_T('('));
				_ASSERTE(ich >= 0);
				hr = FindDoc(strBrk.Left(ich), pDoc);
				if (SUCCEEDED(hr) && pDoc)
				{
					hr = pDoc->put_Active((VARIANT_BOOL)VARIANT_TRUE);
					pTextDoc = pDoc;
					if (pTextDoc)
					{
						strBrk = strBrk.Mid(ich+1);
						ich = strBrk.Find(_T(')'));
						strLine = strBrk.Left(ich);
						l = atol(strLine);

						hr = pTextDoc->get_Selection(&pDispSel);
						if (SUCCEEDED(hr) && pDispSel)
						{
							CComVariant varSelMode = dsMove;
							pSel = pDispSel;
							hr = pSel->GoToLine(l, varSelMode);

							varSel = l;
							hr = m_pBrkPnts->AddBreakpointAtLine(varSel, &pDispBrkPnt);
						}
					}
				}
				if (FAILED(hr))
				{
					rgStrBrksFailed.Add(rgStrBrks.GetAt(i));
				}
				i++;
			}
		}
	}
	return(S_OK);
}



HRESULT CBrkPnts::FindDoc(LPCTSTR szFile, CComPtr<IGenericDocument>& pDoc, BOOL fOkToOpen /*= TRUE*/)
{
	HRESULT hr = E_FAIL;
	CComPtr<IDispatch> pDispDocuments;
    CComQIPtr<IDocuments, &IID_IDocuments> pDocuments;
	CComBSTR bstrFile;
    m_spApplication->get_Documents(&pDispDocuments);
    pDocuments = pDispDocuments;
    pDispDocuments = NULL;
	BOOL fFound = FALSE;

	if (pDocuments)
	{	// ENSURE DOC IS OPEN -- WE KEEP FILES AROUND THAT MAY HAVE BEEN CLOSED
		CComVariant vtDocType = _T("Auto");
		CComVariant vtBoolReadOnly = FALSE;
		CComPtr<IDispatch> pDispDoc;
		bstrFile = szFile;
		CComQIPtr<IGenericDocument, &IID_IGenericDocument> pDocument;
		if (fOkToOpen)
		{
			hr = pDocuments->Open(bstrFile, vtDocType, vtBoolReadOnly, &pDispDoc);
			pDocument = pDispDoc;
			if (SUCCEEDED(hr) && pDocument)
			{
				fFound = TRUE;
				pDoc = pDocument;
			}
		}
		if (!fFound)
		{
			CComPtr<IUnknown> pUnk;
			CComQIPtr<IEnumVARIANT, &IID_IEnumVARIANT> pNewEnum;
			if (SUCCEEDED(pDocuments->get__NewEnum(&pUnk)) && pUnk != NULL)
			{
				pNewEnum = pUnk;
				VARIANT varGenericDocument;

				while (!fFound && pNewEnum->Next(1, &varGenericDocument, NULL) == S_OK)
				{
					CComQIPtr<IGenericDocument, &IID_IGenericDocument> pGenericDocument;
					ASSERT (varGenericDocument.vt == VT_DISPATCH);
					pGenericDocument = varGenericDocument.pdispVal;
					VariantClear(&varGenericDocument);
					CComBSTR bstrFullName;
					pGenericDocument->get_FullName(&bstrFullName);
					if (bstrFullName == szFile)
					{
						fFound = TRUE;
						pDoc = pGenericDocument;
					}
				}
			}


		}
	}

	return(hr);
}


HRESULT CBrkPnts::ClearAll()
{
	HRESULT hr;
	long l, cBrks, lLine;
	CString strT;
	short sEnabled;
	VARIANT_BOOL fRemoved;
	CComBSTR bstrCommand;

	bstrCommand = _T("DebugRemoveAllBreakpoints");
	hr = m_spApplication->ExecuteCommand(bstrCommand);
	if (SUCCEEDED(hr))
	{
		return(hr);
	}

	hr = GetBrkPnts();
	if (SUCCEEDED(hr) && m_pBrkPnts)
	{
		hr = m_pBrkPnts->get_Count(&cBrks);
		l = 0;
		while (l < cBrks)
		{
			CComPtr<IDispatch> pDispBrkPnt;
			CComQIPtr<IBreakpoint, &IID_IBreakpoint> pBrkPnt;
			CComBSTR bstrLocation;
			CComBSTR bstrFile;
			CComVariant varItem = l;

			hr = m_pBrkPnts->Item(varItem, &pDispBrkPnt);
			if (SUCCEEDED(hr) && pDispBrkPnt)
			{
				pBrkPnt = pDispBrkPnt;

				hr = pBrkPnt->get_Enabled(&sEnabled);
				hr = pBrkPnt->get_File(&bstrFile);
				hr = pBrkPnt->get_Location(&bstrLocation);

				CComPtr<IGenericDocument> pDoc = NULL;
				CComQIPtr<ITextDocument, &IID_ITextDocument> pTextDoc;
				
				strT = bstrFile;
				hr = FindDoc(strT, pDoc);
				if (SUCCEEDED(hr) && pDoc)
				{
					hr = pDoc->put_Active((VARIANT_BOOL)VARIANT_TRUE);
					pTextDoc = pDoc;
					if (SUCCEEDED(hr) && pTextDoc)
					{
						strT = bstrLocation;
						strT.Remove(_T('.'));
						lLine = atol(strT);
						varItem = lLine;
						hr = m_pBrkPnts->RemoveBreakpointAtLine(varItem, &fRemoved);
					}
				}
			}
			l++;
		}
	}
	return(hr);
}

void CBrkPnts::SetSaveOnlyEnabled(BOOL fSaveOnlyEnabled)
{
	m_fSaveOnlyEnabled = fSaveOnlyEnabled;
}

void CBrkPnts::SetFile(LPCTSTR szFile)
{
	m_strFile = szFile;
}


void CBrkPnts::GetCounts(long &lTotal, long &lEnabled)
{
	HRESULT hr;
	long l;
	lTotal = 0;
	lEnabled = 0;
	hr = m_pBrkPnts->get_Count(&lTotal);
	_ASSERTE(SUCCEEDED(hr));

	l = 0;
	while (l < lTotal)
	{
		CComPtr<IDispatch> pDispBrkPnt;
		CComQIPtr<IBreakpoint, &IID_IBreakpoint> pBrkPnt;
		short sEnabled;
		CComVariant varItem = l;

		hr = m_pBrkPnts->Item(varItem, &pDispBrkPnt);
		pBrkPnt = pDispBrkPnt;

		hr = pBrkPnt->get_Enabled(&sEnabled);
		if (sEnabled)
		{
			lEnabled++;
		}
		
		l++;
	}

}
