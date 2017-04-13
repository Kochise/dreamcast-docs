// Commands.cpp : implementation file
//

#include "stdafx.h"
#include "bldrec.h"
#include "Commands.h"
#include "dlgfile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

LPCTSTR szMainKey = _T("Software\\Microsoft\\devstudio\\AddIns\\BldRec\\");
LPCTSTR szThisKey = _T("LogFile");

/////////////////////////////////////////////////////////////////////////////
// CCommands

CCommands::CCommands()
{
	m_pApplication = NULL;
	m_pApplicationEventsObj = NULL;
	m_pDebuggerEventsObj = NULL;
	m_theLastTime = CTime::GetCurrentTime();
}

CCommands::~CCommands()
{
	ASSERT (m_pApplication != NULL);
	m_pApplication->Release();

	SaveFileName();
}

void CCommands::SetApplicationObject(IApplication* pApplication)
{
	// This function assumes pApplication has already been AddRef'd
	//  for us, which CDSAddIn did in its QueryInterface call
	//  just before it called us.
	m_pApplication = pApplication;

	// Create Application event handlers
	XApplicationEventsObj::CreateInstance(&m_pApplicationEventsObj);
	m_pApplicationEventsObj->AddRef();
	m_pApplicationEventsObj->Connect(m_pApplication);
	m_pApplicationEventsObj->m_pCommands = this;

	// Create Debugger event handler
	CComPtr<IDispatch> pDebugger;
	if (SUCCEEDED(m_pApplication->get_Debugger(&pDebugger)) 
		&& pDebugger != NULL)
	{
		XDebuggerEventsObj::CreateInstance(&m_pDebuggerEventsObj);
		m_pDebuggerEventsObj->AddRef();
		m_pDebuggerEventsObj->Connect(pDebugger);
		m_pDebuggerEventsObj->m_pCommands = this;
	}
}

void CCommands::UnadviseFromEvents()
{
	ASSERT (m_pApplicationEventsObj != NULL);
	m_pApplicationEventsObj->Disconnect(m_pApplication);
	m_pApplicationEventsObj->Release();
	m_pApplicationEventsObj = NULL;

	if (m_pDebuggerEventsObj != NULL)
	{
		// Since we were able to connect to the Debugger events, we
		//  should be able to access the Debugger object again to
		//  unadvise from its events (thus the VERIFY_OK below--see stdafx.h).
		CComPtr<IDispatch> pDebugger;
		VERIFY_OK(m_pApplication->get_Debugger(&pDebugger));
		ASSERT (pDebugger != NULL);
		m_pDebuggerEventsObj->Disconnect(pDebugger);
		m_pDebuggerEventsObj->Release();
		m_pDebuggerEventsObj = NULL;
	}
}


/////////////////////////////////////////////////////////////////////////////
// Event handlers

// TODO: Fill out the implementation for those events you wish handle
//  Use m_pCommands->GetApplicationObject() to access the Developer
//  Studio Application object

// Application events

HRESULT CCommands::XApplicationEvents::BeforeBuildStart()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CComBSTR bstrProj;
	CComPtr<IGenericProject> pProj = NULL;
	CString strStart;

	m_pCommands->GetApplicationObject()->get_ActiveProject((IDispatch **)&pProj.p);
	if (pProj)
	{
		pProj->get_Name(&bstrProj);
	}
	strStart = "Build Started " + strStart;
	m_pCommands->MarkTime(strStart, TRUE);
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::BuildFinish(long nNumErrors, long nNumWarnings)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CString strBuildInfo;
	CStdioFile filePlg;

	strBuildInfo.Format("Build Finished! Errors=%d, Warnings=%d", nNumErrors, nNumWarnings);
	m_pCommands->MarkTime(strBuildInfo, FALSE);
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::BeforeApplicationShutDown()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::DocumentOpen(IDispatch* theDocument)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::BeforeDocumentClose(IDispatch* theDocument)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::DocumentSave(IDispatch* theDocument)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::NewDocument(IDispatch* theDocument)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::WindowActivate(IDispatch* theWindow)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::WindowDeactivate(IDispatch* theWindow)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::WorkspaceOpen()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::WorkspaceClose()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::NewWorkspace()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

// Debugger event

HRESULT CCommands::XDebuggerEvents::BreakpointHit(IDispatch* pBreakpoint)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}


/////////////////////////////////////////////////////////////////////////////
// CCommands methods

STDMETHODIMP CCommands::BldrecCommandMethod() 
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	VERIFY_OK(m_pApplication->EnableModeless(VARIANT_FALSE));
	
	CDlgFile dlgFile;
	CRegKey regKey;

	long lRes;
	unsigned long lSize = _MAX_PATH;

	lRes = regKey.Create(HKEY_CURRENT_USER, szMainKey);
	if (SUCCEEDED(lRes))
	{
		regKey.QueryValue(m_strFile.GetBuffer(lSize), szThisKey, &lSize);
		m_strFile.ReleaseBuffer();
	}
	if (m_strFile.IsEmpty())
	{
		m_strFile.LoadString(IDS_DEFAULTFILE);
	}
	
	dlgFile.SetFile(m_strFile);
	if (dlgFile.DoModal() == IDOK)
	{
		m_strFile = dlgFile.GetFile();
	}
	SaveFileName();
	VERIFY_OK(m_pApplication->EnableModeless(VARIANT_TRUE));
	return S_OK;
}

BOOL CCommands::SaveFileName()
{
	CRegKey regKey;
	long lRes = 0;

	if (!m_strFile.IsEmpty())
	{
		lRes = regKey.Create(HKEY_CURRENT_USER, szMainKey);
		regKey.SetValue(m_strFile, szThisKey);
	}
	return(lRes == ERROR_SUCCESS);
}

BOOL CCommands::MarkTime(LPCSTR szItem, BOOL fStart)
{
	if (m_strFile.IsEmpty())
		return(FALSE);


	CString strLogItem;
	CTime theTime = CTime::GetCurrentTime();
	CTimeSpan theDiff;
	CComPtr<IDispatch> pDispConfig;
	CComQIPtr<IConfiguration, &IID_IConfiguration> pConfig;
	CString strConfig;
	CComBSTR bstrConfig;

	try
	{
		if (SUCCEEDED(m_pApplication->get_ActiveConfiguration(&pDispConfig)) && pDispConfig)
		{
			pConfig = pDispConfig;
			pDispConfig = NULL;
			if (SUCCEEDED(pConfig->get_Name(&bstrConfig)))
			{
				strConfig = bstrConfig;
			}
		}
		CStdioFile logFile(m_strFile, CFile::modeNoTruncate | CFile::modeCreate | CFile::modeWrite);
		logFile.SeekToEnd();
		CTimeSpan theDiff = theTime - m_theLastTime;
		if (fStart)
		{
			strLogItem.Format(_T("%s :             %s -- %s\n"), theTime.Format(_T("%I:%M:%S %p %m/%d/%y")), szItem, strConfig);
		}
		else
		{
			strLogItem.Format(_T("%s : %s   %s -- %s\n"), theTime.Format(_T("%I:%M:%S %p %m/%d/%y")),
				theDiff.Format(_T("%H:%M:%S ")),
				szItem, strConfig);
		}
		m_theLastTime = theTime;
		logFile.WriteString(strLogItem);
		logFile.Close();
	}
	catch(...)
	{
	}
	return(TRUE);
}

BOOL AnalyzePlgFile(LPCSTR szProjName)
{
	/*
	To Find all files compiled
	Look for "Compiling..." and go until "Generating Code...", then repeat.
	Files inbetween have type *.obj.
	Catch "Stopped by user" (or whatever it is)
	*/
	BOOL fOK = TRUE;

	return(fOK);
}