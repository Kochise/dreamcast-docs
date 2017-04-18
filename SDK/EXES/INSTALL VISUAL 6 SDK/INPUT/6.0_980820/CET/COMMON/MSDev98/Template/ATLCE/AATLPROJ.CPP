[!if(InsertAfterApp)]
[!crlf]
C[!ProjectNameSafe]Module _Module;
[!crlf]
BEGIN_OBJECT_MAP(ObjectMap)
END_OBJECT_MAP()
[!crlf]
LONG C[!ProjectNameSafe]Module::Unlock()
{
	AfxOleUnlockApp();
	return 0;
}
[!crlf]
LONG C[!ProjectNameSafe]Module::Lock()
{
	AfxOleLockApp();
	return 1;
}
[!if!=(MFCOLE, "1")]
LPCTSTR C[!ProjectNameSafe]Module::FindOneOf(LPCTSTR p1, LPCTSTR p2)
{
	while (*p1 != NULL)
	{
		LPCTSTR p = p2;
		while (*p != NULL)
		{
			if (*p1 == *p)
				return CharNext(p1);
			p = CharNext(p);
		}
		p1++;
	}
	return NULL;
}
[!endif]
[!crlf]
[!endif]
[!if=(InsertInInitInstance, "1")]
	if (!InitATL())
		return FALSE;
[!endif]
[!if(INITATL)]
	[!ATLINITED] = TRUE;
[!crlf]
[!if=(MFCOLE, "0")]
#if _WIN32_WINNT >= 0x0400
	HRESULT hRes = CoInitializeEx(NULL, COINIT_MULTITHREADED);
#else
	HRESULT hRes = CoInitialize(NULL);
#endif

[!crlf]
	if (FAILED(hRes))
	{
		[!ATLINITED] = FALSE;
		return FALSE;
	}
[!crlf]
[!endif]
	_Module.Init(ObjectMap, AfxGetInstanceHandle());
	_Module.dwThreadID = GetCurrentThreadId();
[!crlf]
[!if=(MFCOLE, "0")]
	LPTSTR lpCmdLine = GetCommandLine(); //this line necessary for _ATL_MIN_CRT
	TCHAR szTokens[] = _T("-/");
[!crlf]
	BOOL bRun = TRUE;
	LPCTSTR lpszToken = _Module.FindOneOf(lpCmdLine, szTokens);
	while (lpszToken != NULL)
	{
		if (lstrcmpi(lpszToken, _T("UnregServer"))==0)
		{
			_Module.UpdateRegistryFromResource([!IDR_REGISTRYID], FALSE);
			_Module.UnregisterServer(TRUE); //TRUE means typelib is unreg'd
			bRun = FALSE;
			break;
		}
		if (lstrcmpi(lpszToken, _T("RegServer"))==0)
		{
			_Module.UpdateRegistryFromResource([!IDR_REGISTRYID], TRUE);
			_Module.RegisterServer(TRUE);
			bRun = FALSE;
			break;
		}
		lpszToken = _Module.FindOneOf(lpszToken, szTokens);
	}
[!crlf]
	if (!bRun)
	{
		[!ATLINITED] = FALSE;
		_Module.Term();
		CoUninitialize();
		return FALSE;
	}
[!crlf]
	hRes = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, 
		REGCLS_MULTIPLEUSE);
	if (FAILED(hRes))
	{
		[!ATLINITED] = FALSE;
		CoUninitialize();
		return FALSE;
	}	
[!crlf]
[!endif]
	return TRUE;
[!endif]
[!if(InsertAfterParseCommand)]
[!crlf]
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		return TRUE;
	}
[!crlf]
[!endif]
[!if(InsertAfterAfxEnableControlContainer)]
[!crlf]
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
[!crlf]
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		return TRUE;
	}
[!crlf]
[!endif]
[!if=(InsertIntoExitInstance, "1")]
	if ([!ATLINITED])
	{
		_Module.RevokeClassObjects();
		_Module.Term();
	[!if=(MFCOLE, "0")]
		CoUninitialize();
[!endif]
	}
[!crlf]
[!endif]
[!if=(AddExitInstance, "1")]
	if ([!ATLINITED])
	{
		_Module.RevokeClassObjects();
		_Module.Term();
[!if=(MFCOLE, "0")]
		CoUninitialize();
[!endif]
	}
[!crlf]
	return CWinApp::ExitInstance();
[!endif]
[!if=(REGSVR, "1")]
[!crlf]
    _Module.UpdateRegistryFromResource([!IDR_REGISTRYID], TRUE);
	_Module.RegisterServer(TRUE);
[!endif]
[!if=(REGCLASSOBJ, "1")]
	_Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, 
		REGCLS_MULTIPLEUSE);
[!endif]
[!if=(IFOLE, "1")]
[!crlf]
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		return TRUE;
	}
[!endif]
