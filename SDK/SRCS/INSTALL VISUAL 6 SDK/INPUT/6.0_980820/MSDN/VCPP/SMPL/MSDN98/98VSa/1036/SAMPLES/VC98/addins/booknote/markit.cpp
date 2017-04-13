// MarkIt.cpp : Implementation of CMarkIt
#include "stdafx.h"
#include "Booknote.h"
#include "MarkIt.h"
#include "dlgnote.h"

CString strMainKey = _T("Software\\Microsoft\\devstudio\\6.0\\AddIns\\Booknote.MarkIt.1\\");

/////////////////////////////////////////////////////////////////////////////
// CMarkIt
CMarkIt::CMarkIt()
{
	CRegKey regKey;
	long lRes;
	unsigned long lSize;

	lRes = regKey.Create(HKEY_CURRENT_USER, strMainKey);
	regKey.QueryValue(m_strFile.GetBuffer(_MAX_PATH), _T("LogFile"), &lSize);
	m_strFile.ReleaseBuffer();
	if (m_strFile.IsEmpty())
	{
		m_strFile = _T("c:\\booklog.txt");
	}
}

CMarkIt::~CMarkIt()
{
	CRegKey regKey;
	long lRes;

	lRes = regKey.Create(HKEY_CURRENT_USER, strMainKey);
	regKey.SetValue(m_strFile, _T("LogFile"));
}


HRESULT CMarkIt::OnConnection(IApplication* pApp, VARIANT_BOOL bFirstTime, long dwAddInID, VARIANT_BOOL* bOnConnection)
{
	HRESULT hr = S_OK;
	m_spApplication = pApp;
	m_dwAddInID = dwAddInID;

	hr = pApp->SetAddInInfo((long)_Module.GetModuleInstance(), 
		static_cast<IMarkIt*>(this), IDB_TOOLBAR_MEDIUM_MARKIT, IDB_TOOLBAR_LARGE_MARKIT, dwAddInID);
	LPCTSTR szCommand = _T("BookNote");
	VARIANT_BOOL bRet;
	if (SUCCEEDED(hr))
	{
		hr = pApp->AddCommand(CComBSTR(_T("BookNote\nBookNote\nBookNote\nBookNote")),CComBSTR(_T("BookNote")), 0, dwAddInID, &bRet);
	}

	// Add toolbar buttons only if this is the first time the add-in
	// is being loaded.  Toolbar buttons are automatically remembered
	// by Developer Studio from session to session, so we should only
	// add the toolbar buttons once.
	if (bFirstTime)
	{
		if (SUCCEEDED(hr))
		{
			hr = pApp->AddCommandBarButton(dsGlyph, CComBSTR(_T("BookNote")), dwAddInID);
		}
	}

	*bOnConnection = SUCCEEDED(hr) ? VARIANT_TRUE :VARIANT_FALSE;
	return hr;
}

HRESULT CMarkIt::OnDisconnection(VARIANT_BOOL bLastTime)
{
	return S_OK;
}

HRESULT CMarkIt::BookNote()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	m_spApplication->EnableModeless(VARIANT_FALSE);
	CComQIPtr<ITextDocument, &IID_ITextDocument> pDocument;
	CComPtr<IDispatch> pDispDocument;
	CDlgNote dlgNote;
	int iRes;
	CTime timeNow;
	CComBSTR bstrTime;

    m_spApplication->get_ActiveDocument(&pDispDocument);
    pDocument = pDispDocument;
    pDispDocument = NULL;
	if (pDocument)
	{
		CComBSTR bstrName;
		pDocument->get_FullName(&bstrName);
		CComQIPtr<ITextSelection, &IID_ITextSelection> pSelection;
		CComPtr<IDispatch> pDispSelection;
		pDocument->get_Selection(&pDispSelection);
		pSelection = pDispSelection;
		pDispSelection = NULL;
		if (pSelection)
		{
			long col, line;
			CComBSTR bstr(2048,LPCSTR(" "));
			CComBSTR bstrNote;
			HRESULT hr;
			hr = pSelection->get_CurrentColumn(&col);
			hr =  pSelection->get_CurrentLine(&line);

			dlgNote.m_strLogFile = m_strFile;
			dlgNote.SetMarkIt(this);
			iRes = dlgNote.DoModal();
			if (iRes == IDOK)
			{
				m_strFile = dlgNote.m_strLogFile;
				// produce output like "c:\test\foo.cpp(37) : warning C4310: cast truncates constant value"
				bstrNote = dlgNote.m_strNote;
				timeNow = CTime::GetCurrentTime();
				bstrTime = timeNow.Format(_T("%I:%M:%S %p  %d/%m/%Y"));
				swprintf(bstr,L"%s(%d): (%s) %s", bstrName, line, bstrTime, bstrNote);
				if (dlgNote.m_fEcho)
				{
					m_spApplication->PrintToOutputWindow(bstr);
				}

				CString strOut;
				strOut = bstr;
				CStdioFile log;
				try
				{
					if (!dlgNote.m_strLogFile.IsEmpty() && log.Open(dlgNote.m_strLogFile, CFile::modeNoTruncate | CFile::modeWrite | CFile::modeCreate))
					{
						log.SeekToEnd();
						strOut += _T("\n");
						log.WriteString(strOut);
						log.Close();
					}
				}
				catch (CFileException *eFile)
				{
					CString strMsg;
					CString strErr;
					eFile->GetErrorMessage(strErr.GetBuffer(_MAX_PATH), _MAX_PATH);
					strErr.ReleaseBuffer();
					strMsg.Format("%s \n    %s", strErr, dlgNote.m_strLogFile);
					MessageBox(NULL, strMsg, _T("BOOKNOTE"), MB_OK);
					eFile->Delete();
				}
			}

		}
	}
	m_spApplication->EnableModeless((VARIANT_BOOL)VARIANT_TRUE);
	return S_OK;
}


HRESULT CMarkIt::Dump(LPCTSTR szFile)
{
	CStdioFile file;
	CString str;
	HRESULT hr = E_FAIL;

	if (file.Open(szFile, CFile::modeRead))
	{ 
		while (file.ReadString(str))
		{
			CComBSTR bstr = str;
			hr = m_spApplication->PrintToOutputWindow(bstr);
		}
	}
	return (hr);
}
