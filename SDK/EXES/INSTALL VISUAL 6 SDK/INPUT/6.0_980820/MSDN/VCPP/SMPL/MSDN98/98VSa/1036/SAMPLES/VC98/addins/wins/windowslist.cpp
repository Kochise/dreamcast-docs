// WindowsList.cpp : Implementation of CWindowsList
#include "stdafx.h"
#include "Wins.h"
#include "WindowsList.h"
#include "dlgwinmgr.h"


#pragma warning( disable : 4310 )  // Disable warning message: warning C4310: cast truncates constant value
// get this warning for lines containing VARIANT_BOOL, VARIANT_TRUE, or VARIANT_FALSE

/////////////////////////////////////////////////////////////////////////////
// CWindowsList

HRESULT CWindowsList::OnConnection(IApplication* pApp, VARIANT_BOOL bFirstTime, long dwAddInID, VARIANT_BOOL* bOnConnection)
{
	HRESULT hr = S_OK;
	CString strCmdString;
	CString strCmdName;

	AFX_MANAGE_STATE(AfxGetStaticModuleState()); // do this, or you will not be able to load resources

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
		static_cast<IWindowsList*>(this), IDB_TOOLBAR_MEDIUM_CWINMGR, IDB_TOOLBAR_LARGE_CWINMGR, dwAddInID);
	VARIANT_BOOL bRet;
	if (SUCCEEDED(hr))
	{
		strCmdString.LoadString(IDS_CMD_WINMGR);
		strCmdName.LoadString(IDS_CMDNAME_WINMGR);//             ,---- This is the name of the method in the IWindowsList interface
		strCmdName += _T('\n');
		strCmdName += strCmdString; //                           V
		hr = pApp->AddCommand(CComBSTR(strCmdName),CComBSTR(_T("WindowsManager")), 0, dwAddInID, &bRet);
		_ASSERTE(SUCCEEDED(hr));
		strCmdString.LoadString(IDS_CMD_MINWIN);
		strCmdName.LoadString(IDS_CMDNAME_MINWIN);
		strCmdName += _T('\n');
		strCmdName += strCmdString;
		hr = pApp->AddCommand(CComBSTR(strCmdName),CComBSTR(_T("MinWin")), 1, dwAddInID, &bRet);
		_ASSERTE(SUCCEEDED(hr));
		strCmdString.LoadString(IDS_CMD_AUTOSIZE);
		strCmdName.LoadString(IDS_CMDNAME_AUTOSIZE);
		strCmdName += _T('\n');
		strCmdName += strCmdString;
		hr = pApp->AddCommand(CComBSTR(strCmdName),CComBSTR(_T("SetLimit")), 2, dwAddInID, &bRet);
		_ASSERTE(SUCCEEDED(hr));
		strCmdString.LoadString(IDS_CMD_ALLVISIBLE);
		strCmdName.LoadString(IDS_CMDNAME_ALLVISIBLE);
		strCmdName += _T('\n');
		strCmdName += strCmdString;
		hr = pApp->AddCommand(CComBSTR(strCmdName),CComBSTR(_T("SetVisible")), 3, dwAddInID, &bRet);
		_ASSERTE(SUCCEEDED(hr));
		strCmdString.LoadString(IDS_CMD_CLOSEDEBUGWNDS);
		strCmdName.LoadString(IDS_CMDNAME_CLOSEDEBUGWNDS);
		strCmdName += _T('\n');
		strCmdName += strCmdString;
		hr = pApp->AddCommand(CComBSTR(strCmdName),CComBSTR(_T("CloseDebugWnds")), 4, dwAddInID, &bRet);
		_ASSERTE(SUCCEEDED(hr));
	}

	// Add toolbar buttons only if this is the first time the add-in
	// is being loaded.  Toolbar buttons are automatically remembered
	// by Developer Studio from session to session, so we should only
	// add the toolbar buttons once.
	if (bFirstTime == VARIANT_TRUE)
	{
		if (SUCCEEDED(hr))
		{
			strCmdName.LoadString(IDS_CMDNAME_WINMGR);
			hr = pApp->AddCommandBarButton(dsGlyph, CComBSTR(strCmdName), dwAddInID);
			_ASSERTE(SUCCEEDED(hr));
			strCmdName.LoadString(IDS_CMDNAME_MINWIN);
			hr = pApp->AddCommandBarButton(dsGlyph, CComBSTR(strCmdName), dwAddInID);
			_ASSERTE(SUCCEEDED(hr));
			strCmdName.LoadString(IDS_CMDNAME_AUTOSIZE);
			hr = pApp->AddCommandBarButton(dsGlyph, CComBSTR(strCmdName), dwAddInID);
			_ASSERTE(SUCCEEDED(hr));
			strCmdName.LoadString(IDS_CMDNAME_ALLVISIBLE);
			hr = pApp->AddCommandBarButton(dsGlyph, CComBSTR(strCmdName), dwAddInID);
			_ASSERTE(SUCCEEDED(hr));
			strCmdName.LoadString(IDS_CMDNAME_CLOSEDEBUGWNDS);
			hr = pApp->AddCommandBarButton(dsGlyph, CComBSTR(strCmdName), dwAddInID);
			_ASSERTE(SUCCEEDED(hr));
		}
	}

	*bOnConnection = (VARIANT_BOOL)(SUCCEEDED(hr) ? VARIANT_TRUE :VARIANT_FALSE);
	return hr;
}

HRESULT CWindowsList::OnDisconnection(VARIANT_BOOL bLastTime)
{
	bLastTime; // UNREFERENCED (don't care why we are disconnectino

	AtlUnadvise(m_spApplication, IID_IApplicationEvents, m_dwAppEvents);
	AtlUnadvise(m_spApplication, IID_IDebuggerEvents, m_dwDbgEvents);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Application events
HRESULT CWindowsList::BeforeBuildStart()
{
	return S_OK;
}
HRESULT CWindowsList::BuildFinish(long nNumErrors, long nNumWarnings)
{
	nNumWarnings;  // UNREFERENCED
	nNumErrors;  // UNREFERENCED

	return S_OK;
}
HRESULT CWindowsList::BeforeApplicationShutDown()
{
	return S_OK;
}
HRESULT CWindowsList::DocumentOpen(IDispatch* theDocument)
{
	HRESULT hr = E_FAIL;
	CComPtr<IDispatch> pDispWindow;
	CComQIPtr<IGenericDocument, &IID_IGenericDocument> pDoc;
	CComQIPtr<IGenericDocument, &IID_IGenericDocument> pGenericDocument;

	pDoc = theDocument;
	if (pDoc)
	{
		pGenericDocument = theDocument;
		if (pGenericDocument)
		{
			SetInfo(pGenericDocument);
		}
		hr = pDoc->get_ActiveWindow(&pDispWindow);
		if (SUCCEEDED(hr) && pDispWindow)
		{
			MakeLimit(pDispWindow);
		}
	}
	return hr;
}

HRESULT CWindowsList::BeforeDocumentClose(IDispatch* theDocument)
{
	theDocument;  // UNREFERENCED
	return S_OK;
}

HRESULT CWindowsList::DocumentSave(IDispatch* theDocument)
{
	CComQIPtr<IGenericDocument, &IID_IGenericDocument> pGenericDocument;
	pGenericDocument = theDocument;
	if (pGenericDocument)
	{
		SetInfo(pGenericDocument);
	}
	return S_OK;
}

HRESULT CWindowsList::NewDocument(IDispatch* theDocument)
{
	theDocument;  // UNREFERENCED
	return S_OK;
}

HRESULT CWindowsList::WindowActivate(IDispatch* theWindow)
{
	theWindow;  // UNREFERENCED
	SetInfo();
	MakeLimit();
	return S_OK;
}

HRESULT CWindowsList::WindowDeactivate(IDispatch* theWindow)
{
	theWindow;  // UNREFERENCED
	return S_OK;
}

HRESULT CWindowsList::WorkspaceOpen()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_spApplication->EnableModeless(VARIANT_FALSE);
	
	CComPtr<IDispatch> pDispDocuments;
	CComPtr<IDispatch> pDispDoc;
	CComQIPtr<IDocuments, &IID_IDocuments> pDocuments;
	CComQIPtr<IGenericDocument, &IID_IGenericDocument> pDocActive;
	m_spApplication->get_ActiveDocument(&pDispDoc);
	pDocActive = pDispDoc;
	pDispDoc = NULL;

	m_spApplication->get_Documents(&pDispDocuments);
	pDocuments = pDispDocuments;
	pDispDocuments = NULL;

	CComPtr<IUnknown> pUnk;
	CComQIPtr<IEnumVARIANT, &IID_IEnumVARIANT> pNewEnum;
	if (SUCCEEDED(pDocuments->get__NewEnum(&pUnk)) && pUnk != NULL)
	{
		pNewEnum = pUnk;
		VARIANT varTextDocument;
		CComQIPtr<IGenericDocument, &IID_IGenericDocument> pGenDoc;
		while (pNewEnum->Next(1, &varTextDocument, NULL) == S_OK)
		{
			_ASSERTE(varTextDocument.vt == VT_DISPATCH);
			pGenDoc = varTextDocument.pdispVal;
			if (pGenDoc)
			{
				SetInfo(pGenDoc, FALSE);
			}
			VariantClear(&varTextDocument);
		}
	}
	if (pDocActive)
	{
		pDocActive->put_Active(VARIANT_TRUE); // make this active again.
		SetInfo(pDocActive);
	}

	m_spApplication->EnableModeless((VARIANT_BOOL)VARIANT_TRUE);
	return S_OK;
}

HRESULT CWindowsList::WorkspaceClose()
{
	return S_OK;
}
HRESULT CWindowsList::NewWorkspace()
{
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Debugger event
HRESULT CWindowsList::BreakpointHit(IDispatch* pBreakpoint)
{
	pBreakpoint;  // UNREFERENCED
	return S_OK;
}

/// IWindowsList
HRESULT CWindowsList::WindowsManager()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CDlgWinMgr dlgWinMgr;
	int iRes;

	m_fAutoVis = theApp.GetAutoVis();
	m_fAutoDir = theApp.GetAutoDir();
	m_fAutoSize = theApp.GetAutoSize();
	m_iSortedCol = theApp.GetSortedCol();
	m_lSize = theApp.GetSize();

	dlgWinMgr.SetVars(m_fAutoVis,m_fAutoDir, m_fAutoSize, m_iSortedCol, m_lSize);

	if (m_dirList.Count() == 0)
	{
		WorkspaceOpen(); // pretend we just did this...
	}
	dlgWinMgr.SetDirList(&m_dirList, this);
	iRes = dlgWinMgr.DoModal();

	dlgWinMgr.GetVars(m_fAutoVis,m_fAutoDir, m_fAutoSize, m_iSortedCol, m_lSize);
	theApp.SetAutoVis(m_fAutoVis);
	theApp.SetAutoDir(m_fAutoDir);
	theApp.SetAutoSize(m_fAutoSize);
	theApp.SetSize(m_lSize);

	return S_OK;
}


HRESULT CWindowsList::SetInfo(IGenericDocument *pTextDoc /* = NULL */, BOOL fDoExtras /* = TRUE*/)
{
	HRESULT hr = S_OK;
	int i;

	if (m_cIgnoreSetDir > 0)
	{
		m_cIgnoreSetDir--;
		return(S_OK);
	}

	CString strDir, strFile;
	CComQIPtr<IGenericDocument, &IID_IGenericDocument> pDocument;

	if (pTextDoc)
	{
		pDocument = pTextDoc;
	}
	else
	{
		CComPtr<IDispatch> pDispDocument;
		m_spApplication->get_ActiveDocument(&pDispDocument);
		pDocument = pDispDocument;
		pDispDocument = NULL;
	}
	if (pDocument)
	{
		CComBSTR bstrName;
		CString strFullPath;
		pDocument->get_FullName(&bstrName);
		strDir = bstrName;
		strFullPath = strDir;
		i = strDir.ReverseFind(_T('\\'));
		if (i >= 0)
		{
			strFile = strDir.Mid(i+1);
			strDir = strDir.Left(i);
			AddToList(strDir, strFile, strFullPath, fDoExtras);
			if (m_fAutoDir && fDoExtras)
			{
				SetCurrDir(strDir);
			}
		}
	}


	return(hr);
}

void CWindowsList::IgnoreNextSetDir()
{
	m_cIgnoreSetDir = 1; // don't bother going higher at moment.
}

void CWindowsList::SetCurrDir(LPCTSTR szDir)
{
	CComBSTR bstrName;

	bstrName = szDir;
	m_spApplication->put_CurrentDirectory(bstrName);
}



BOOL CWindowsList::AddToList(LPCTSTR szDir, LPCTSTR szFile, LPCTSTR szFullPath, BOOL fTouch /* = TRUE*/)
{
	BOOL fOK = TRUE;
	BOOL fInDebugger;
	CRect rectWnd;

	fInDebugger = IsInDebugMode();
	GetSize(szFullPath, rectWnd);
	m_dirList.FAddDir(szDir, szFile, rectWnd, fInDebugger, fTouch);
	return(fOK);
}

HRESULT CWindowsList::OpenDoc(LPCTSTR szFile, IGenericDocument **ppDocRet /* = NULL*/)
{
	HRESULT hr = E_FAIL;
	CComPtr<IGenericDocument> pDoc;
	if (ppDocRet)
		*ppDocRet = NULL;
	hr = FindDoc(szFile, pDoc);
	if (pDoc)
	{
		hr = pDoc->put_Active((VARIANT_BOOL)VARIANT_TRUE);
		if (ppDocRet)
		{
			*ppDocRet = pDoc.p;
			(*ppDocRet)->AddRef();
		}
	}
	return(hr);
}

HRESULT CWindowsList::CloseDoc(LPCTSTR szFile)
{
	HRESULT hr = E_FAIL;
	CComPtr<IGenericDocument> pDoc;
	DsSaveStatus iSaved;
	CComVariant varSaveChanges = dsSaveChangesPrompt;

	hr = FindDoc(szFile, pDoc, FALSE);
	if (pDoc)
	{
		hr = pDoc->Close(varSaveChanges, &iSaved);
	}

	return(hr);
}



HRESULT CWindowsList::FindDoc(LPCTSTR szFile, CComPtr<IGenericDocument>& pDoc, BOOL fOkToOpen /*= TRUE*/)
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
					//varGenericDocument.pdispVal->Release();
					VariantClear(&varGenericDocument);
					CComBSTR bstrFullName;
					pGenericDocument->get_FullName(&bstrFullName);
					if (bstrFullName == szFile)
					{
						fFound = TRUE;
						pDoc = pGenericDocument;
						hr = S_OK;
					}
				}
			}


		}
	}

	return(hr);
}

void CWindowsList::Reset()
{
	m_dirList.Reset();
}



HRESULT CWindowsList::MinWin()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	m_spApplication->EnableModeless(VARIANT_FALSE);
	HRESULT hr;

	hr = DoMinWin();
	m_spApplication->EnableModeless((VARIANT_BOOL)VARIANT_TRUE);
	return(hr);
}

HRESULT CWindowsList::DoMinWin()
{
	// TODO: Replace this with the actual code to execute this command
	//  Use m_spApplication to access the Developer Studio Application object,
	//  and VERIFY_OK to see error strings in DEBUG builds of your add-in
	//  (see stdafx.h)

	

	CComPtr<IDispatch> pDispWindows;
    CComQIPtr<IWindows, &IID_IWindows> pWindows;
    m_spApplication->get_Windows(&pDispWindows);
    pWindows = pDispWindows;
    pDispWindows = NULL;

    CComPtr<IUnknown> pUnk;
    CComQIPtr<IEnumVARIANT, &IID_IEnumVARIANT> pNewEnum;
    if (SUCCEEDED(pWindows->get__NewEnum(&pUnk)) && pUnk != NULL)
    {
        pNewEnum = pUnk;
        VARIANT varWindow;
        CComQIPtr<IGenericWindow, &IID_IGenericWindow> pWindow;
		while (pNewEnum->Next(1, &varWindow, NULL) == S_OK)
        {
            ASSERT (varWindow.vt == VT_DISPATCH);
            pWindow = varWindow.pdispVal;
			//varWindow.pdispVal->Release();
            VariantClear(&varWindow);
            CComBSTR bstrCaption;
            pWindow->get_Caption(&bstrCaption);
			pWindow->put_WindowState(dsWindowStateMinimized);
        }
    }


	return S_OK;
}

HRESULT CWindowsList::DoMinWin(LPCTSTR szDoc)
{
	HRESULT hr = E_FAIL;
	CComPtr<IGenericDocument> pDoc;
	CComPtr<IDispatch> pDispWindow;
    CComQIPtr<IGenericWindow, &IID_IGenericWindow> pWindow;

	hr = FindDoc(szDoc, pDoc, FALSE);
	if (pDoc)
	{
		hr = pDoc->get_ActiveWindow(&pDispWindow);
		if (SUCCEEDED(hr) && pDispWindow)
		{
			pWindow = pDispWindow;
			pWindow->put_WindowState(dsWindowStateMinimized);
		}
	}

	return(hr);
}


HRESULT CWindowsList::MakeLimit(IDispatch* pDispWindow)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	m_spApplication->EnableModeless(VARIANT_FALSE);

	if (m_fAutoSize)
	{
		m_spApplication->EnableModeless((VARIANT_BOOL)VARIANT_FALSE);

		CComPtr<IDispatch> pDispWindowT = pDispWindow;
		CComQIPtr<IGenericWindow, &IID_IGenericWindow> pWindow;
		if (pDispWindowT == NULL)
		{
			m_spApplication->get_ActiveWindow(&pDispWindowT);
		}
		if (pDispWindowT)
		{
			pWindow = pDispWindowT;
			pDispWindowT = NULL;
			CComBSTR bstrCaption;
			pWindow->get_Caption(&bstrCaption);
			pWindow->put_Width(m_lSize);
		}
		m_spApplication->EnableModeless((VARIANT_BOOL)VARIANT_TRUE);
	}
	m_spApplication->EnableModeless((VARIANT_BOOL)VARIANT_TRUE);
	return S_OK;

}

HRESULT CWindowsList::SetLimit()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	m_spApplication->EnableModeless((VARIANT_BOOL)VARIANT_FALSE);
	CComPtr<IDispatch> pDispWindow;
    CComQIPtr<IGenericWindow, &IID_IGenericWindow> pWindow;
    m_spApplication->get_ActiveWindow(&pDispWindow);
	if (pDispWindow)
	{
		pWindow = pDispWindow;
		pDispWindow = NULL;
		CComBSTR bstrCaption;
		pWindow->get_Caption(&bstrCaption);
		pWindow->get_Width(&m_lSize);
	}
	m_spApplication->EnableModeless((VARIANT_BOOL)VARIANT_TRUE);
	return S_OK;
}

STDMETHODIMP CWindowsList::SetVisible()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_spApplication->EnableModeless(VARIANT_FALSE);
	
	DsWindowState dsState;
	long t, l, w, h;
	CRect rectClient, rectWnd, rectNew, rectT;
	HRESULT hr;
	
	CComPtr<IDispatch> pDispWindow;
    CComQIPtr<IGenericWindow, &IID_IGenericWindow> pWindow;
    m_spApplication->get_ActiveWindow(&pDispWindow);
	if (pDispWindow) // is there an active window?
	{
		pWindow = pDispWindow;
		pDispWindow = NULL;


		hr = pWindow->get_WindowState(&dsState);
		if (dsState != dsWindowStateMaximized) // if maximized, nothing to do anyway
		{
			// maximize, temporarily the active window
			pWindow->put_WindowState(dsWindowStateMaximized);
			// get size and position  of maximize window
			pWindow->get_Width(&w);
			pWindow->get_Height(&h);
			pWindow->get_Left(&l);
			pWindow->get_Top(&t);
			rectClient.SetRect(l < 0 ? 0 : l,
				t < 0 ? 0 : t,
				w - abs(l) - 16, 
				h - abs(t) - 16);

			// reset window to previus state.
			pWindow->put_WindowState(dsState);

			// iterate through all windows and make sure that they fit...
			CComPtr<IDispatch> pDispWindows;
			m_spApplication->get_Windows(&pDispWindows);
			if (pDispWindows)
			{
				CComQIPtr<IWindows, &IID_IWindows> pWindows;
				pWindows = pDispWindows;
				pDispWindows = NULL;

				CComPtr<IUnknown> pUnk;
				CComQIPtr<IEnumVARIANT, &IID_IEnumVARIANT> pNewEnum;
				if (SUCCEEDED(pWindows->get__NewEnum(&pUnk)) && pUnk != NULL)
				{
					pNewEnum = pUnk;
					VARIANT varGenericWindow;

					while (pNewEnum->Next(1, &varGenericWindow, NULL) == S_OK)
					{
						CComQIPtr<IGenericWindow, &IID_IGenericWindow> pGenericWindow;
						ASSERT (varGenericWindow.vt == VT_DISPATCH);
						pGenericWindow = varGenericWindow.pdispVal;
						varGenericWindow.pdispVal->Release();
						pGenericWindow->get_Width(&w);
						pGenericWindow->get_Height(&h);
						pGenericWindow->get_Left(&l);
						pGenericWindow->get_Top(&t);
						rectWnd.SetRect(l, t, l+w, t+h);
						rectNew.IntersectRect(rectWnd, rectClient);
						if (rectWnd != rectNew)
						{ // this code could be done more efficiently by calculating offsets and doing one Offset and one Deflate, but this makes it more clear.
							rectNew = rectWnd; // the intersection may be zero -- translate rects
							// see if a simple translation will work
							if (h < rectClient.Height() || w < rectClient.Width())
							{
								if (l < rectClient.left) // window is to left -- shift positively
									rectNew.OffsetRect(rectClient.left - l, 0);
								else if (rectNew.right > rectClient.right) // window is to right -- shift negatively
									rectNew.OffsetRect(rectClient.right - rectNew.right, 0);
								if (t < rectClient.top) // window is to top -- shift positively
									rectNew.OffsetRect(0, rectClient.top - t);
								else if (rectNew.bottom > rectClient.bottom) // window is to bottom -- shift negatively
									rectNew.OffsetRect(0, rectClient.bottom - rectNew.bottom);
							}
							rectT.IntersectRect(rectNew, rectClient);
							if (rectT != rectWnd)
							{
								pGenericWindow->put_Left(rectT.left);
								pGenericWindow->put_Top(rectT.top);
								pGenericWindow->put_Width(rectT.Width());
								pGenericWindow->put_Height(rectT.Height());
							}

						}
					}
				}
			}
		}
		if (IsInDebugMode())
		{
			CComPtr<IDispatch> pDispDebugger;
			CComQIPtr<IDebugger, &IID_IDebugger> pDebugger;
			m_spApplication->get_Debugger(&pDispDebugger);
			if (pDispDebugger)
			{
				pDebugger = pDispDebugger;
				pDebugger->ShowNextStatement();
			}

		}
	}

	WorkspaceOpen(); // refresh

	m_spApplication->EnableModeless((VARIANT_BOOL)VARIANT_TRUE);

	return S_OK;
}

HRESULT CWindowsList::GetSize(LPCTSTR szFilePath, CRect& rect)
{
	HRESULT hr = E_FAIL;
	CComPtr<IGenericDocument> pDoc = NULL;
	CComQIPtr<IGenericWindow, &IID_IGenericWindow> pGenericWindow;
	CComPtr<IDispatch> pDispWindow;
	long t, l, w, h;
	
	rect.SetRectEmpty();
	hr = FindDoc(szFilePath, pDoc, FALSE);
	if (pDoc && SUCCEEDED(hr))
	{
		hr = pDoc->get_ActiveWindow(&pDispWindow);
		pGenericWindow = pDispWindow;
		pDispWindow = NULL;
		if (pGenericWindow)
		{
			pGenericWindow->get_Width(&w);
			pGenericWindow->get_Height(&h);
			pGenericWindow->get_Left(&l);
			pGenericWindow->get_Top(&t);
			rect.SetRect(l, t, l+w, t+h);
		}
	}

	return(hr);

}

BOOL CWindowsList::IsInDebugMode()
{
	HRESULT hr = E_FAIL;
	BOOL fOK = FALSE;
	DsExecutionState debugstate;
	
	CComPtr<IDispatch> pDispDebugger;
    CComQIPtr<IDebugger, &IID_IDebugger> pDebugger;
    m_spApplication->get_Debugger(&pDispDebugger);
	if (pDispDebugger)
	{
		pDebugger = pDispDebugger;
		hr = pDebugger->get_State(&debugstate);
		if (debugstate != dsNoDebugee)
			fOK = TRUE;
	}
	return(fOK);
}

STDMETHODIMP CWindowsList::CloseDebugWnds()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	m_spApplication->EnableModeless(VARIANT_FALSE);
	POSITION p;
	CFileItem *pFileItem;
	CRect rectDbg, rect;

	p = m_dirList.GetHeadPosition();
	while (p)
	{
		pFileItem = m_dirList.GetNextPos(p);
		if (pFileItem->FOpenedInDebug())
		{
			CString strPath;

			strPath = pFileItem->GetDir();
			strPath += _T('\\');
			strPath += pFileItem->GetFile();
			CloseDoc(strPath);
		}
	}
	m_spApplication->EnableModeless((VARIANT_BOOL)VARIANT_TRUE);
	return S_OK;
}
