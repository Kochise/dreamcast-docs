// Commands.cpp : implementation file
//

// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.

#include "stdafx.h"
#include "AutoBld.h"
#include "Commands.h"
#include "config.h"
#include <mapi.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommands

CCommands::CCommands()
{
	m_pApplication = NULL;
	m_pApplicationEventsObj = NULL;
	m_pDebuggerEventsObj = NULL;

	//Because AutoBuild has an event for capturing the buildfinish event, we
	//  need to set some flags to make sure only want to send mail when the
	//  AutoBuild command is invoked, not when you walk up and say "compile"
	m_bAutoBuilding = TRUE;

	// if there is a build in progress lets not try to start a second build
	m_bBuildInProgres = FALSE;

	m_bTesting = TRUE;

	//Here we retrieve all our information for the build from the registry
	m_bSendMail = (BOOL)(AfxGetApp()->GetProfileInt
			(_T("Configure"), _T("SendMail"), 0));
	m_strSendTo = AfxGetApp()->GetProfileString
			(_T("Configure"), _T("SendTo"), _T(""));
	m_strStatusLine = AfxGetApp()->GetProfileString
			(_T("Configure"), _T("StatusText"), _T(""));
	m_bMailOnEach = (BOOL)(AfxGetApp()->GetProfileInt
			(_T("Configure"), _T("MailOnEach"), 1));
	m_bIncBuildResults = (BOOL)(AfxGetApp()->GetProfileInt
			(_T("Configure"), _T("IncludeBuildResults"), 1));
	m_bSendFile = (BOOL)(AfxGetApp()->GetProfileInt
			(_T("Configure"), _T("SendFile"), 0));
	m_strFileToSend = AfxGetApp()->GetProfileString
			(_T("Configure"), _T("FileToSend"));
	m_bCloseWhenDone = (BOOL)(AfxGetApp()->GetProfileInt
			(_T("Configure"), _T("CloseWhenDone"), 0));

	//If the user wishes to send mail when all building is complete, a
	//  running count of the number of Warnings/Errors is needed
	m_nTotalErrors = 0;
	m_nTotalWarnings = 0;
}

CCommands::~CCommands()
{
	ASSERT (m_pApplication != NULL);
	m_pApplication->Release();
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
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::BuildFinish(long nNumErrors, long nNumWarnings)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_pCommands->m_bBuildInProgres = FALSE;

	if (m_pCommands->m_bAutoBuilding == TRUE) //See comment in the constructor
	{
		//here we create a mail message, and send it off...
		if ((m_pCommands->m_bSendMail == TRUE) &&
			(m_pCommands->m_bMailOnEach == TRUE))
		{

			HINSTANCE hInstMail = ::LoadLibrary("MAPI32.DLL");
			if (hInstMail != NULL)
			{
				ULONG (PASCAL *lpfnSendMail)(ULONG, ULONG, MapiMessage*,
					FLAGS, ULONG);
				(FARPROC&)lpfnSendMail = GetProcAddress(hInstMail,
					"MAPISendMail");
				if (lpfnSendMail != NULL)
				{
					MapiMessage message;
					memset((void*)&message, 0, sizeof(message));
					message.lpszSubject = const_cast<LPTSTR>
							((LPCSTR)m_pCommands->m_strStatusLine);
					CString strErrWarnCStr;
					if (m_pCommands->m_bIncBuildResults == TRUE)
					{
						CString strErrWarnText;
						strErrWarnText.Format(IDS_ERRWARNTEXT, nNumErrors,
								nNumWarnings);
						strErrWarnCStr = CString(message.lpszSubject) +
								strErrWarnText;
						message.lpszSubject = const_cast<LPTSTR>
								((LPCSTR)strErrWarnCStr);
					}
					CString strToMail;
					if (m_pCommands->m_bSendFile == FALSE)
					{
						strToMail.Format(IDS_DEFAULTMAILBODY,
								m_pCommands->m_strBuildingConfigurationName);
					}
					else
					{
						CString strResult;
						CStdioFile fileTextToMail;
						try
						{

							fileTextToMail.Open(m_pCommands->m_strFileToSend,
									CFile::modeRead | CFile::typeText);
							DWORD dwFileSize = fileTextToMail.GetLength();
							dwFileSize = fileTextToMail.Read(
									strResult.GetBuffer(dwFileSize), dwFileSize);
							strResult.ReleaseBuffer(dwFileSize);
							CString strLocal;
							strLocal.Format(strResult,
									m_pCommands->m_strBuildingConfigurationName,
									nNumErrors, nNumWarnings);
							strToMail = strLocal;
						}
						catch (...) //If some problem occurrs when working
									//  with the file, just send the default
									//  message body
						{
							if (m_pCommands->m_bTesting == TRUE)
								AfxMessageBox(IDS_WARNSENDDEF);
							strToMail.Format(IDS_DEFAULTMAILBODY,
								m_pCommands->m_strBuildingConfigurationName);
						}
					}
					message.lpszNoteText = const_cast<LPTSTR>((LPCSTR)strToMail);
					message.nRecipCount = 1;
					message.lpRecips = new MapiRecipDesc;
					memset(message.lpRecips, 0, sizeof(MapiRecipDesc));
					message.lpRecips->ulRecipClass = MAPI_TO;
					CString strTemp2 = CString("SMTP:") + m_pCommands->m_strSendTo;
					message.lpRecips->lpszName = const_cast<LPTSTR>
							((LPCSTR)m_pCommands->m_strSendTo);
					message.lpRecips->lpszAddress = const_cast<LPTSTR>
							((LPCSTR)strTemp2);

					int error = lpfnSendMail(0, (ULONG)0, &message, 0, 0);

					//error is not handled, because you really don't want to
					//  pop up a message box. Putting up a message box would
					//  suspend other pending builds until somebody would
					//  manually click the OK button. You may wish to place
					//  some sort of logging here, so that the error would be
					//  dumped to a file.

					// The reason you might get an error is because your email
					// may require a password. You can log into your email account first,
					// or create an account that doesn't require a password.

					if (error != SUCCESS_SUCCESS)
					{
						if (m_pCommands->m_bTesting == TRUE)
						{
							AfxMessageBox(IDS_MAPIERROR);

						}
						else
						{
							// log some other kind of error in a log file
						}
					}

					delete message.lpRecips;
				}
			::FreeLibrary(hInstMail);
			}
		}
	}
	m_pCommands->m_nTotalErrors += nNumErrors;
	m_pCommands->m_nTotalWarnings += nNumWarnings;
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

STDMETHODIMP CCommands::AutoBuildTest()
{
	// don't allow more than one test to go.
	if (m_bBuildInProgres)
		return S_OK;

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_pApplication->EnableModeless(VARIANT_FALSE);
	m_nTotalErrors = 0;
	m_nTotalWarnings = 0;

	m_bAutoBuilding = TRUE;    //See comment in the constructor
	m_bBuildInProgres = TRUE;  //See comment in the constructor

	long lCount;
	int nNumWorkspaces = AfxGetApp()->GetProfileInt(_T("Configure"),
			_T("NumWorkspaces"), 0);

	for (int nWorkspaceNumber = 1 ; nWorkspaceNumber <= nNumWorkspaces ;
			nWorkspaceNumber++)
	{
		char RegKey[50];
		wsprintf(RegKey, "Workspace%d", nWorkspaceNumber-1);
		CComBSTR bszWorkspacePathName = AfxGetApp()->GetProfileString(
					_T("Configure"), RegKey, "");

		CComPtr<IDispatch> pDispDocuments;
		VERIFY_OK(m_pApplication->get_Documents(&pDispDocuments));

		CComVariant OleVariant; //By default, the type is VT_EMPTY

		CComQIPtr<IDocuments, &IID_IDocuments> pDocuments(pDispDocuments);

		CComPtr<IDispatch> pWorkspace;  //Never gets used except in:
		VERIFY_OK(pDocuments->Open(bszWorkspacePathName, OleVariant,
										OleVariant, &pWorkspace));

		//First, get a pointer to the dispatch for the Projects collection
		CComPtr<IDispatch> pDispProjects;
		// clean out the output files from and old build.

		VERIFY_OK(m_pApplication->get_Projects(&pDispProjects));
		CComQIPtr<IProjects, &IID_IProjects> pProjects(pDispProjects);
		//Get the number of projects in the collection
		VERIFY_OK(pProjects->get_Count(&lCount));
		for (long i = 1 ; i < lCount+1 ; i++)
		{
			long lNumConfigs;
			CComVariant Vari = i;

			//Get the next project
			CComPtr<IGenericProject> pGenProject;
			VERIFY_OK(pProjects->Item(Vari, &pGenProject));
			CComQIPtr<IBuildProject, &IID_IBuildProject> pProject(pGenProject);
			//Each project has a configuration (Win32 Release, Win32 Debug,
			//  etc.), get the collection of these configurations
			CComPtr<IConfigurations> pConfigs;
			VERIFY_OK(pProject->get_Configurations(&pConfigs));
			VERIFY_OK(pConfigs->get_Count(&lNumConfigs));
			for (long j = 1 ; j < lNumConfigs+1 ; j++)
			{
				CComVariant Varj = j;
				//Get each individual configuration
				CComPtr<IConfiguration> pConfig;
				VERIFY_OK(pConfigs->Item(Varj, &pConfig));

				CComVariant VarDisp = pConfig;
				CComBSTR bszStr;
				VERIFY_OK(pConfig->get_Name(&bszStr));
				if (m_bMailOnEach == TRUE)
					m_strBuildingConfigurationName = bszStr;
				else
					m_strBuildingConfigurationName += CString(", ") +
							CString(bszStr);
				//Build this particular
				//  configuration, in this project,
				//  in this Workspace...
				VERIFY_OK(m_pApplication->Build(VarDisp));
			}
		}
	}
	if (m_bMailOnEach == FALSE)
	{
		//We only wish to send mail when everything is built.
		//  to do this, we just say "from now on we are sending Mail on each
		//  configuration build"
		m_bMailOnEach = TRUE;
		//  then manually call the BuildFinish event, as if a configuration is
		//  done, but this "Configuration" is the entire project
		ASSERT(m_pApplicationEventsObj != NULL);
		m_pApplicationEventsObj->BuildFinish(m_nTotalErrors, m_nTotalWarnings);
		//Reset MailOnEach
		m_bMailOnEach = FALSE;
	}

	m_bAutoBuilding = FALSE;    //See comment in the constructor

	m_pApplication->EnableModeless(VARIANT_TRUE);

	if (m_bTesting == FALSE)
	{
		if (m_bCloseWhenDone == TRUE)
			VERIFY_OK(m_pApplication->Quit());
	}
	else
	{
		if (m_bCloseWhenDone == TRUE)
			AfxMessageBox(IDS_WARNEXIT);
	}
	return S_OK;
}

STDMETHODIMP CCommands::AutoBuild()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	m_bTesting = FALSE;
	AutoBuildTest();
	m_bTesting = TRUE;

	return S_OK;
}

STDMETHODIMP CCommands::AutoBuildConfigure()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_pApplication->EnableModeless(VARIANT_FALSE);

	CConfigure AutoBuildConfigDlg;
	// stuff all the pre read data values in the dialog before
	// showing it
	AutoBuildConfigDlg.m_bSendMail      = m_bSendMail;
	AutoBuildConfigDlg.m_bCloseWhenDone = m_bCloseWhenDone;
	AutoBuildConfigDlg.m_bMailOnEach    = m_bMailOnEach;
	AutoBuildConfigDlg.m_bIncBuildResults = m_bIncBuildResults;
	AutoBuildConfigDlg.m_bSendFile      = m_bSendFile;
	AutoBuildConfigDlg.m_strFileToSend  = m_strFileToSend;
	AutoBuildConfigDlg.m_strStatusLine  = m_strStatusLine;
	AutoBuildConfigDlg.m_strSendTo      = m_strSendTo;

	AutoBuildConfigDlg.DoModal();
	// get the data values back.
	m_bSendMail = AutoBuildConfigDlg.m_bSendMail;
	m_bCloseWhenDone = AutoBuildConfigDlg.m_bCloseWhenDone;
	m_bMailOnEach = AutoBuildConfigDlg.m_bMailOnEach;
	m_bIncBuildResults = AutoBuildConfigDlg.m_bIncBuildResults;
	m_bSendFile = AutoBuildConfigDlg.m_bSendFile;
	m_strFileToSend = AutoBuildConfigDlg.m_strFileToSend;
	m_strStatusLine = AutoBuildConfigDlg.m_strStatusLine;
	m_strSendTo = AutoBuildConfigDlg.m_strSendTo;

	m_pApplication->EnableModeless(VARIANT_TRUE);

	return S_OK;
}
