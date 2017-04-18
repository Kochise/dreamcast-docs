#define FOXISAPIVERSION "FoxISAPI v1.2"

/*

FOXISAPI.CPP

Copyright (c)1995 Microsoft Corporation, All Right Reserved

Implements an ISAPI dll that will invoke OLE Automation objects
using IDispatch.  Any object that has a PROGID and implements one
or more methods with the following signature can be called by this dll:


URLs that invoke this service from a link will look like this:

http://machine/path/progid.method?foo=bar&baz=bleh

This dll will also work with HTML forms that use the POST method,
in which case the parameters to the call will come from the form
elements rather than the URL.  Any parameters sent as part of the
action URL will not be passed on to the OLE object.

Exports:

BOOL WINAPI GetExtensionVersion( HSE_VERSION_INFO *pVer )
BOOL WINAPI HttpExtensionProc(   EXTENSION_CONTROL_BLOCK *pECB )
DllMain(HINSTANCE hinstDLL, DWORD dwReason, LPVOID pvReserved)

  for more information, see KB Articles Q158838, Q156223 on MS Web site.

  Debug instructions:
  Start IIS, find the process ID of INETINFO, start MSDEV -p pid
  use a browser (from another machine perhaps) and hit the page
  Use IIS to stop/restart WWW services

  From MSDevStudio Technote 63:
    
If you have written an Internet Server Extension DLL, you might be interested in getting it
 running under the debugger so you can trace its execution, set breakpoints, or monitor variable 
 values after the extension is called. Getting the Microsoft Internet Information Server up and 
 running with your DLL in the debugger is possible, but a little tricky. 
 You will need to first find a quiet server where you can debug your DLL in a controlled 
 setting. Once you've found such a resource, you can start debugging your DLL by following 
 these steps:
 1.	Stop the Internet Information Server publishing services by using the Internet 
	Information Server Manager, or by stopping the services with the Services icon 
	in the Windows NT Advanced Server Control Panel. Note that you must stop all 
	three services even though you are only debugging extensions to the World-Wide
	Web publishing service. To make things easier, you might wish to make the services
	"Manually" started in Control Panel so you can avoid this step later in your 
	development.
 2.	Start Microsoft Developer Studio, and click the Close Workspace command on the File 
	menu to close any opened workspace.
 3.	On the File menu, click Open Workspace to open the INETINFO.EXE program. This file is 
	in the directory where you installed the Microsoft Internet Information Server. 
 4.	On the Build menu, click Settings, then click the Debug tab in the Project Settings 
	dialog box.
 5.	With General selected in the Category box, type the following in the Program Arguments 
	text box:
  
-e W3Svc
  
 6.	Choose Additional DLLs from the Category drop-down list. Then, in the Local Names box, 
	specify the complete path and name of your extension DLL or DLLs. Make sure the check 
	box next to each is marked.
 7.	Click OK to close the Project Settings dialog box.
 8.	Make sure that the .PDB file for your DLL is in the same directory as the DLLs you plan 
	to debug.
  
Debugging Tips
The Internet server can be run as an interactive application. This makes debugging it much 
easier. To do this you need to make a few changes to your system. For the user account that
you are going to run the server under, you need to add a few privileges. 
To add privileges, run User Manager (MUSRMGR.EXE), and select User Rights from the Policies
menu. Check the Show Advanced User Rights check box. Then select "Act as part of the 
operating system" from the Right drop-down list, and add the user account. 
Repeat this process with "Generate Security Audits" (also in the Rights drop-down list). 
Make sure that all Internet Services (WWW, ftp & gopher) are stopped and INetInfo.Exe is 
not running (use TLIST to check). Log off and log back on. You can then load the Internet 
Server with the command line:
  
INetInfo.Exe -e W3Svc

  
If you want to load this under a debugger just make sure that the command line to 
INetInfo.Exe is "-e W3Svc". (For example, to load it into WinDbg the command line is: 
WinDbg INetInfo.Exe -e W3Svc
You are ready to go. In Developer Studio, point to Debug on the Build menu and then choose 
Go. This action starts the WWW publishing service, and the debugger will be aware of 
symbols in your DLL. You'll get a warning that this file doesn't have debugging 
information in it, but you can ignore that message.
When you leave Microsoft Developer Studio, you will probably want to make sure that you 
let Developer Studio save the workspace for INETINFO.EXE. This will let you avoid 
reentering all of the settings you need to make instead, you can just open the 
INETINFO.MDS workspace file when you are ready to start the debugger again.

Cached DLLs
You can adjust the registry setting at 
HKEY_LOCAL_MACHINE/SYSTEM/CurrentControlSet/Services/W3SVC/Parameters/CacheExtensions 
to have the server reinitialize DLLs each time they are used. If this setting is 1, 
the server will keep DLLs loaded in memory as long as possible. This is the default 
setting for the server, since it helps the server achieve peak performance, and should 
only be changed if you are using the server for debugging. If you make the setting zero, 
the server will always reload extension DLLs each time they are used.
Forcing the server to reload your DLL is very helpful when your DLL might be crashing or 
upsetting any per-instance data that it maintains. By forcing the server to reinitialize 
the DLL, you can get your DLL back into a predictable state with very little effort. 
You should make sure you test your DLL using the normal CacheExtensions setting, however, 
to make sure code in your DLL isn't completely dependent on that initial state.


You can start and stop a service from the dos command prompt:
	net start <service name>
		or
  	net start "world wide web publishing service"
		or 
	net start w3svc



 
*/

#include <windows.h>
#include <httpext.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <mmsystem.h>
#include <assert.h>
#include <malloc.h>

#define PARAMLEN 1024
#define BUFLEN 4096
#define PROGIDSIZE 50

// TLS is used to store OLE initialization flag
static DWORD g_dwTLSIndex = (DWORD)-1;

//The following are configurable via the INI file
static DWORD g_BusyTimeout = 2000;
static DWORD g_ReleaseTimeout = 2000;
static char g_szResetUrl[30] = "reset";	//
static char g_szStatusUrl[30] = "status";	//
static char g_szSingleModeUrl[30] = "SingleMode";
static char g_szMultiModeUrl[30] = "MultiMode";
static char g_szDebugger[40] = "VisualFoxpro.Application";
static DWORD g_nAutoRefreshStatus = 0;	// Number of seconds that the status page will automatically refresh


static int g_fSingleMode = 0;	//0 = normal multi mode, 1 = limit to at most one instance of any fox server (for EXCLUSIVE use...maint mode)

static SYSTEMTIME stServerStartTimeStamp;		// time this dll loaded

//the full path dir of this dll
static char gszAppDir[MAX_PATH];
static char gszAppName[MAX_PATH];	// the name of our DLL


// Many OA objects are not threadsafe, so we only allow one at a time
static CRITICAL_SECTION g_csRuntime;

class CInstances {
	public:
	IDispatch *m_lpDispatch;				// pointer to this instance's IDispatch
	CLSID m_clsid;							//CLSID of this instance
	class CInstances * m_pNextInstance;		// linked list pointer to next one
	LPSTREAM  m_pStm;						// stream for marshalling
	char m_szProgIdReq[PROGIDSIZE];					//the requested progid of this instance (the one in the URL)
	char m_szProgIdActual[PROGIDSIZE];				//the actual progid of this instance	(the one to map it to. Often the same, but can be diff)
	BOOL m_fIsBusy;							// flag indicates whether this server instance is busy
	DWORD m_dwTimeStamp;						// time this instance became busy or became not busy
	DWORD m_dwCumTime;						// the total amount of time spent in this server processing it's requests
	DWORD m_dwLastReqTime;						// the amount of time spent in this server processing the last request
	long m_lServiceCount;					// the total number of requests served by this server
	BOOL m_fIsDebugMode;					// flag indicates whether we're going to debug the VFP automation server

	// Methods:
	CInstances();
	~CInstances();
} *pRootInstances = NULL;

CInstances::CInstances() {
	m_pNextInstance = pRootInstances;
	pRootInstances = this;
	m_fIsBusy = FALSE;
	m_fIsDebugMode = FALSE;
	m_lServiceCount = 0;
	m_dwCumTime = 0;
	m_dwLastReqTime = 0;
	m_dwTimeStamp = timeGetTime();
	memset(&m_pStm,0,sizeof(m_pStm));
}

CInstances::~CInstances() {
	if (m_pStm) {
		CoGetInterfaceAndReleaseStream(m_pStm,IID_IDispatch,(void **)&m_lpDispatch);
		if (m_lpDispatch)
			m_lpDispatch->Release();
	}
}

class CInstances *AddOne(CLSID clsid,char *szProgIdReq,char *szProgIdActual,IDispatch * pdispObj) {
	class CInstances *pInstances;
	pInstances = new CInstances;	//the links are made in the constructor
	pInstances->m_clsid = clsid;
	pInstances->m_lpDispatch = pdispObj;
	lstrcpy(pInstances->m_szProgIdReq,szProgIdReq);
	lstrcpy(pInstances->m_szProgIdActual,szProgIdActual);
	if (pdispObj) {
		CoMarshalInterThreadInterfaceInStream(IID_IDispatch,pdispObj,&pInstances->m_pStm);
	}
	return pInstances;
}



//
// Retrieve the class Id from the registry given its program id name.
// The program ID name is converted from ASCII to wide char here since
// URL strings are always ASCII.
//
HRESULT GetClsidFromProgIdA(LPCLSID pclsid, CHAR* pszName)
{
	HRESULT hr;
	long cbName;
	OLECHAR wName[PARAMLEN];
	cbName = lstrlen(pszName)+1;
	// Allocate a wide char string for the Prog Id name.
	// Convert the ProgId name to wide chars.
	if (0 == MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, pszName, -1,
								 wName, cbName) ) {
		return HRESULT_FROM_WIN32(GetLastError());
	}

	// Now get the class Id from the Program Id.
	hr = CLSIDFromProgID(wName, pclsid);
	return hr;
}

void ErrorResponse(EXTENSION_CONTROL_BLOCK *pECB,
				CHAR *pszProgid, 
				CHAR *pszMethod,
				char *szErrorMessage)
{
	CHAR szBuf[BUFLEN];
	DWORD buflen;

	_snprintf(szBuf,sizeof(szBuf),"HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body><h1>"
		"FOXISAPI call failed</h1><p><b>Progid is:</b> %s\n<p><b>Method is:</b> %s\n<p>"
		"<b>Parameters are:</b> %s\n<p><b> parameters are:</b> %.*s\n</b>"
		"<p><b>%s\n</b></body>",
		((NULL != pszProgid) ? pszProgid : ""),
		((NULL != pszMethod) ? pszMethod : ""),
		((NULL != pECB->lpszQueryString) ? pECB->lpszQueryString : ""),
		(pECB->cbAvailable > 0 ? pECB->cbAvailable : 1),
		(pECB->cbAvailable > 0 ? (CHAR*)pECB->lpbData : ""),
		szErrorMessage);
	buflen = strlen(szBuf);
	pECB->WriteClient(pECB->ConnID,(void *)szBuf,&buflen,0);
}


//
// Invoke obtains the prog ID and method to be invoked and blasts away.
// If successful, it returns a string to be forced back up the pipe, else NULL
//
BOOL CallObject(EXTENSION_CONTROL_BLOCK *pECB,
		CHAR *pszProgid,CHAR *pszMethod, CHAR * lpszIniFile)
{
	BOOL fRetVal;
	HRESULT hr;
	CLSID clsid;
	IDispatch *pdispObj = NULL;
	IUnknown *punkObj = NULL;
	OLECHAR wzMethod[PARAMLEN];
	OLECHAR *pwParams;
	OLECHAR wzIniFile[MAX_PATH * 2];
	CHAR szDebugString[MAX_PATH * 2];
	BSTR bstrParams = NULL;
	BSTR bstrIniFile = NULL;
	CHAR *pszResults = NULL;
	DWORD buflen = 0;
	char szErrorMessage[4096];

	OLECHAR *pwzName;
	DISPID dispidMethod;
	DISPPARAMS dispparms;
	VARIANTARG varg[3];
	VARIANTARG vResult;
	EXCEPINFO excep;
	
	IDispatch * pdispDoRelease;
	BOOL fGotAvailableEntry,fIsInList;
	class CInstances *pInstances;

	// initialize everything up front so cleanup is safe
	*szErrorMessage = '\0';
	memset(&dispparms, 0, sizeof(DISPPARAMS));
	memset(&varg, 0, sizeof(VARIANTARG) * 3);
	memset(&excep, 0, sizeof(EXCEPINFO));

	VariantInit(&varg[0]);
	VariantInit(&varg[1]);
	VariantInit(&varg[2]);
	VariantInit(&vResult);

	try {
		DWORD EndTime;
		EndTime = timeGetTime() + g_BusyTimeout;
		pInstances = NULL;
		do {//loop until timeout if progid found in our list
			fGotAvailableEntry = fIsInList = FALSE;
			EnterCriticalSection(&g_csRuntime);
			//Look in our linked list to see if the progid is registered in our ini file
			while (1) {
				// we want to cycle through the pool and not start from the beginning of the list every time (in case some entries fail)
				//find a server instance. If it's busy and controlled by our INI file, then loop till we get one that's not busy
				if (timeGetTime() > EndTime) {
					if (!*szErrorMessage) {		//if there's already an error msg, use it
						sprintf(szErrorMessage,"Timed out %d secs",g_BusyTimeout/1000);
					}
					LeaveCriticalSection(&g_csRuntime);
					throw szErrorMessage;
				}
				if (!(g_fSingleMode && pInstances && fIsInList)) {//if singlemode and already have an entry, we must use it, so don't increment to next entry
					if (!pInstances) {
						if (!pRootInstances) {	//there is nothing in the list
							break;
						}
						pInstances = pRootInstances;
					} else {
						pInstances = pInstances->m_pNextInstance;
						if (!pInstances) {	//if at end of pool list
							if (!fIsInList) {	//requested may not be in our list at all
								break;
							}
							pInstances = pRootInstances;	// restart at top
						}
					}
				}
				if (lstrcmpi(pInstances->m_szProgIdReq,pszProgid) != 0) {	//is it the requested progid?
					continue;
				}
				fIsInList = TRUE;	//in our list, so we need to control instances of it
				if (!pInstances->m_fIsBusy) {	//is it available?
					pInstances->m_fIsBusy = TRUE;		//now mark this server as busy
					pInstances->m_dwTimeStamp = timeGetTime();
					fGotAvailableEntry = TRUE;	//we found a free class instance to use
					if (pInstances->m_lpDispatch) {// if the server has already been created
						hr = CoGetInterfaceAndReleaseStream(pInstances->m_pStm,IID_IDispatch,(void **)&pdispObj);	//marshal to our thread
						if (!FAILED(hr))
							hr = CoMarshalInterThreadInterfaceInStream(IID_IDispatch,pdispObj,&pInstances->m_pStm);

						if (FAILED(hr)) {
							pdispObj =pInstances->m_lpDispatch = NULL;	// don't call release on non-existent obj
							pInstances->m_dwTimeStamp = timeGetTime();
							pInstances->m_fIsBusy = FALSE;		//reuse this entry
							fGotAvailableEntry = FALSE;
							continue;
						}
					}
					break;	//got a nonbusy link list entry to use (the obj might not exist yet), so exit the link list loop
				} else {//must be busy
					hr = 0;	//executable code so we can set a breakpoint
				}
				if (g_fSingleMode) {// only allow one instance so only use the first eligible link list entry
					continue;
				}
			}  // we're looping through all of the link list entries
			LeaveCriticalSection(&g_csRuntime);
			if (!fIsInList) {	//not in the linklist: see if it's a subProgid (actual)
				for (pInstances = pRootInstances ; pInstances ; pInstances = pInstances->m_pNextInstance) {
					if (lstrcmpi(pInstances->m_szProgIdActual,pszProgid) == 0) {	//is it the Actual progid
						fIsInList = TRUE;
						lstrcpy(pszProgid,pInstances->m_szProgIdReq);	//force it to be the generic one, then retry it all
						break;
					}
				}

				if (fIsInList) {
					continue;	//found a subProgid, so loop back and try the whole thing again
				}
			}

			if (fIsInList && !fGotAvailableEntry) {
				continue;
			}
			if (!pdispObj) {	//if the object hasn't been created yet either because it's in list, and not created, or not in list
				if (!fGotAvailableEntry) {	//if we had not found the entry in our linklist, we need to add one (PROGID was not in INI file)
					// convert progid to clsid
					hr = GetClsidFromProgIdA(&clsid, pszProgid);	//get the clsid
					if (FAILED(hr)) {
						char szSysMsg[100];
						FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,0,hr,
							MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),szSysMsg,sizeof(szSysMsg),0);

						sprintf(szErrorMessage,"Class id for %s not found. Err code = %08x: %s",
								pszProgid,hr,szSysMsg);
						throw szErrorMessage;
					}
					EnterCriticalSection(&g_csRuntime);	//add an entry to our linklist
					pInstances = AddOne(clsid,pszProgid, pszProgid, pdispObj);	//the Requested and the Actual progid are the same
					pInstances->m_fIsBusy = TRUE;		//now this server's busy
					pInstances->m_dwTimeStamp = timeGetTime();
					LeaveCriticalSection(&g_csRuntime);
					fGotAvailableEntry=fIsInList=TRUE;

				}
				assert(pInstances);		//we must have a valid linklist entry by now: if it wasn't there originally, it must have been created
				// instantiate object
				hr = CoCreateInstance(pInstances->m_clsid, NULL, CLSCTX_SERVER, IID_IUnknown, (LPVOID *) &punkObj);	//create it
				if (FAILED(hr) || punkObj == NULL) {
					pInstances->m_fIsBusy = TRUE;		//mark this server as busy so it won't be used again
					char szSysMsg[100];
					FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,0,hr,
						MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),szSysMsg,sizeof(szSysMsg),0);

					punkObj = NULL;
					sprintf(szErrorMessage,"CoCreateInstance failed with err code %08x: %s",hr,szSysMsg);
					fGotAvailableEntry=FALSE;
					continue;	//try looping through to find another instance to try
				}
				hr = punkObj->QueryInterface(IID_IDispatch, (void**)&pdispObj);
				if (FAILED(hr) || pdispObj == NULL)  {
					pInstances->m_fIsBusy = TRUE;		//mark this server as busy so it won't be used again
					char szSysMsg[100];
					FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,0,hr,
						MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),szSysMsg,sizeof(szSysMsg),0);

					sprintf(szErrorMessage,"QueryInterface failed with err code %08x: %s",hr,szSysMsg);
					punkObj->Release();
					punkObj = NULL;
					continue;	//try looping through to find another instance to try
				}
				punkObj->Release();
				punkObj = NULL;
				fGotAvailableEntry=TRUE;
				pInstances->m_lpDispatch = pdispObj;	//keep the dispatch pointer around in our array
				CoMarshalInterThreadInterfaceInStream(IID_IDispatch,pdispObj,&pInstances->m_pStm);	//marshall to other threads
			}


		} while (fIsInList && !fGotAvailableEntry || !pInstances);	
		// Convert the method name and args to Wide character.
		assert(pInstances);		//we must have a valid linklist entry by now: if it wasn't there originally, it must have been created
		if (pInstances->m_fIsDebugMode) {
			//odebug([foxis.employee.startup('a','b',0)])
			sprintf(szDebugString,"odebug([%s.%s('",pszProgid,pszMethod);
			lstrcpy(pszMethod,"eval");
		}
		if (0 == MultiByteToWideChar(CP_ACP, 0, pszMethod, -1, wzMethod, PARAMLEN/2) ) {
			pInstances->m_fIsBusy = FALSE;		//mark this server as not busy
			sprintf(szErrorMessage,"MultiByteToWideChar failed for method name");
			throw szErrorMessage;
		}

		// If POST, grab data from control block
		if (0 == strcmp(pECB->lpszMethod, "POST")) {
			int len = MultiByteToWideChar(CP_ACP, 0, (const char*)pECB->lpbData, pECB->cbAvailable, 0, 0);
			assert(len);
			pwParams = (OLECHAR *) _alloca(len*2+4);
			if (0 == MultiByteToWideChar(CP_ACP, 0, (const char*)pECB->lpbData, pECB->cbAvailable, pwParams, len) ) {
				pInstances->m_fIsBusy = FALSE;		//mark this server as not busy
				sprintf(szErrorMessage,"MultiByteToWideChar failed for post");
				throw szErrorMessage;
			}
			pwParams[len] = 0;	//null terminate
			if (pInstances->m_fIsDebugMode) {
				lstrcpyn(szDebugString+lstrlen(szDebugString),(char *)pECB->lpbData,pECB->cbAvailable+1);
			}
		}
		// otherwise, get it from the query string
		else if (NULL != pECB->lpszQueryString) {
			int len = MultiByteToWideChar(CP_ACP, 0, pECB->lpszQueryString, -1, 0, 0);
			assert(len);
			pwParams = (OLECHAR *) _alloca(len*2);
			if (0 == MultiByteToWideChar(CP_ACP, 0, pECB->lpszQueryString, -1, pwParams, len) ) {
				pInstances->m_fIsBusy = FALSE;		//mark this server as not busy
				sprintf(szErrorMessage,"MultiByteToWideChar failed for query string");
				throw szErrorMessage;
			}
			if (pInstances->m_fIsDebugMode) {
				lstrcat(szDebugString,(char *)pECB->lpszQueryString);
			}
		} else {
			pwParams = (OLECHAR *) _alloca(4);
			pwParams[0] = (WCHAR)0;
		}
		if (0 == MultiByteToWideChar(CP_ACP, 0, (const char*)lpszIniFile, -1, wzIniFile, sizeof(wzIniFile)/2) ) {
			pInstances->m_fIsBusy = FALSE;		//mark this server as not busy
			sprintf(szErrorMessage,"MultiByteToWideChar failed for ini file");
			throw szErrorMessage;
		}

		if (pInstances->m_fIsDebugMode) {
			sprintf(szDebugString + lstrlen(szDebugString),"','%s',0)])",lpszIniFile);
			int len = MultiByteToWideChar(CP_ACP, 0, szDebugString, -1, 0, 0);
			assert(len);
			pwParams = (OLECHAR *) _alloca(len*2);
			if (0 == MultiByteToWideChar(CP_ACP, 0, szDebugString, -1, pwParams, len) ) {
				pInstances->m_fIsBusy = FALSE;		//mark this server as not busy
				sprintf(szErrorMessage,"MultiByteToWideChar failed for debug string");
				throw szErrorMessage;
			}
		} else {
			bstrIniFile = SysAllocString(wzIniFile);
			if (NULL == bstrIniFile) {
				pInstances->m_fIsBusy = FALSE;		//mark this server as not busy
				sprintf(szErrorMessage,"SysAllocString 2 failed");
				throw szErrorMessage;
			}
		}
		bstrParams = SysAllocString(pwParams);
		if (NULL == bstrParams) {
			pInstances->m_fIsBusy = FALSE;		//mark this server as not busy
			sprintf(szErrorMessage,"SysAllocString failed");
			throw szErrorMessage;
		}
		// Find method name
		pwzName = wzMethod;
		hr = pdispObj->GetIDsOfNames(IID_NULL, &pwzName, 1, LOCALE_USER_DEFAULT, &dispidMethod);
		if (FAILED(hr)) {
			pInstances->m_fIsBusy = FALSE;		//mark this server as not busy
			char szSysMsg[100];
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,0,hr,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),szSysMsg,sizeof(szSysMsg),0);

			sprintf(szErrorMessage,"GetIDsOfNames failed with err code %08x: %s",hr,szSysMsg);
			throw szErrorMessage;
		}
		// Setup parameters
		dispparms.rgvarg = varg;
		dispparms.rgdispidNamedArgs = NULL;
		dispparms.cNamedArgs = 0;

		if (pInstances->m_fIsDebugMode) {
			dispparms.cArgs = 1;
			varg[0].vt = VT_BSTR;
			varg[0].bstrVal = bstrParams;
			pdispDoRelease = 0;	// don't release ole server
		} else {
			dispparms.cArgs = 3;
			pdispDoRelease = pdispObj;
			// Push in reverse order
			varg[0].vt = VT_I4 | VT_BYREF ;
			varg[0].plVal = (long *)&pdispDoRelease;
			varg[1].vt = VT_BSTR ;
			varg[1].bstrVal = bstrIniFile;
			varg[2].vt = VT_BSTR ;
			varg[2].bstrVal = bstrParams;
		}

		pInstances->m_lServiceCount++;	//bump the service counter
		// Now make the invocation.
		hr = pdispObj->Invoke(dispidMethod, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD,
							&dispparms, &vResult, &excep, NULL);
		pInstances->m_dwCumTime += (pInstances->m_dwLastReqTime=timeGetTime() - pInstances->m_dwTimeStamp);
		pInstances->m_dwTimeStamp = timeGetTime();
		pInstances->m_fIsBusy = FALSE;	//now this server is available to service other threads
		if (FAILED(hr)) {
			char szSysMsg[100];
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,0,hr,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),szSysMsg,sizeof(szSysMsg),0);

			sprintf(szErrorMessage,"Invoke failed with err code %08x: %s",hr,szSysMsg);
			throw szErrorMessage;
		}
		// Assemble result
		if (vResult.vt != VT_BSTR) {
			throw("Server did not return a string");
		}
		//Calculate the length of the results (could be DBCS)... Make sure the DBCS string FONT is DBCS enabled
		buflen = WideCharToMultiByte(CP_ACP, 0, (unsigned short *)vResult.pbstrVal, -1, 0, 0, NULL, NULL);
		pszResults = (CHAR*)malloc(buflen + 1);
		if (0 == WideCharToMultiByte(CP_ACP, 0, (unsigned short *)vResult.pbstrVal, -1, pszResults, buflen + 1, NULL, NULL)) {
			sprintf(szErrorMessage,"WideCharToMultiByte for results failed");
			throw szErrorMessage;
		}
		*(pszResults + buflen) = 0;
		buflen++;
		if (pECB->WriteClient(pECB->ConnID,(void *)pszResults,&buflen,0) == FALSE) {
			char szSysMsg[100];
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,0,hr,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),szSysMsg,sizeof(szSysMsg),0);

			sprintf(szErrorMessage,"WriteClient failed",szSysMsg);
			throw szErrorMessage;
		}

		fRetVal = TRUE;
	} catch  (char *s) {
		if (szErrorMessage != s) {
			lstrcpy(szErrorMessage,s);
		}
		fRetVal = FALSE;
	}
	VariantClear(&varg[0]);
	VariantClear(&varg[1]);
	VariantClear(&varg[2]);
	VariantClear(&vResult);
	DeleteFile(lpszIniFile);	//delete the .INI
	
	if (pdispObj) {				//there was no error? we need to clean up obj refs
		pdispObj->Release();	//No error, so release the current object. 
								//We still have a ref to it in our linked list
		if (pdispDoRelease ) {	//did the OLE server signal to release?
			/*
			For each Web site hit, the OLE server gets instantiated.  The Server gets released after generating
			an HTML page. This means the entire VFP runtime will start up and shut down for
			each web hit.
			If the following Release() call is not executed, then the OLE Server will be left in memory with a reference to it,
			but subsequent web hits will use the same instance of the server, making performance 
			much better.
			*/
			CoGetInterfaceAndReleaseStream(pInstances->m_pStm,IID_IDispatch,(void **)&pInstances->m_lpDispatch);
			if (pInstances->m_lpDispatch)
				pInstances->m_lpDispatch->Release();
			pInstances->m_lpDispatch = 0;
			pInstances->m_fIsBusy = FALSE;
			pInstances->m_dwTimeStamp = timeGetTime();
			pInstances->m_lServiceCount = 0;	//reset hit counter to 0
			pInstances->m_dwCumTime = 0;
			pInstances->m_dwLastReqTime = 0;
			memset(&pInstances->m_pStm,0,sizeof(pInstances->m_pStm));
			CoFreeUnusedLibraries();
		}
	}
	if (NULL != pszResults) {
		free(pszResults);
	}
	if (fRetVal== FALSE) {
		ErrorResponse(pECB, pszProgid, pszMethod,szErrorMessage);
	}
	return fRetVal;
}


// CREATE_INI_FILE will create a temp INI file and pass it to the Fox automation object as
// the second parameter. This INI file contains extra info available from the
// IIS


//
// GetVarAndWriteKey obtains an environment variable and saves it
// to the specified key in the profile.  This function cleans
// up the Fill code a lot.
//

void GetVarAndWriteKey (EXTENSION_CONTROL_BLOCK *pECB,char *lpszIniFile,
						LPCTSTR lpszSection,
						LPCTSTR lpszVar, LPCTSTR lpszKey)
	{
	TCHAR szBuffer[4096];
	DWORD dwBufferSize;
	BOOL bReturn;

	// Call server to get environment variable
	dwBufferSize = sizeof(szBuffer);
	bReturn = pECB->GetServerVariable (pECB->ConnID,
										(LPTSTR) lpszVar,
										szBuffer,
										&dwBufferSize);

	if (!bReturn)
		return;

    // Write variable to profile if data exists
	if (szBuffer[0]) {
		WritePrivateProfileString (lpszSection,
									lpszKey, 
									szBuffer, 
									lpszIniFile);
	}
}


int LogExtraInfo(EXTENSION_CONTROL_BLOCK *pECB,char *lpszIniFile) {
	DWORD dwBufferSize;
	BOOL bReturn;
	TCHAR *pChar, *pOpts, *pEnd;
	TCHAR szBuffer[4096];


	//create a temp INI file name
	GetTempFileName(gszAppDir,
			"FOX",	//prefix
			0,
			lpszIniFile);
	DeleteFile(lpszIniFile);	//delete the .TMP
	*strrchr(lpszIniFile,'.') = '\0';
	strcat(lpszIniFile,".ini");

	WritePrivateProfileString ("FOXISAPI","Request Method", pECB->lpszMethod, lpszIniFile);
	WritePrivateProfileString ("FOXISAPI","Query String", pECB->lpszQueryString, lpszIniFile);
	WritePrivateProfileString ("FOXISAPI","Logical Path", pECB->lpszPathInfo, lpszIniFile);
	WritePrivateProfileString ("FOXISAPI","Physical Path", pECB->lpszPathTranslated, lpszIniFile);
	WritePrivateProfileString ("FOXISAPI","FoxISAPI Version", FOXISAPIVERSION, lpszIniFile);
	//
	// Get server variables and write the values to the profile
	//

	GetVarAndWriteKey (pECB, lpszIniFile, "FOXISAPI",
						TEXT("SERVER_PROTOCOL"), TEXT("Request Protocol"));

	GetVarAndWriteKey (pECB, lpszIniFile, "FOXISAPI",
						TEXT("SCRIPT_NAME"), TEXT("Referer"));

	GetVarAndWriteKey (pECB, lpszIniFile, "FOXISAPI",
						TEXT("SERVER_SOFTWARE"), TEXT("Server Software"));

	GetVarAndWriteKey (pECB, lpszIniFile, "FOXISAPI",
						TEXT("SERVER_NAME"), TEXT("Server Name"));

	GetVarAndWriteKey (pECB, lpszIniFile, "FOXISAPI",
						TEXT("SERVER_PORT"), TEXT("Server Port"));

	GetVarAndWriteKey (pECB, lpszIniFile, "FOXISAPI",
						TEXT("REMOTE_HOST"), TEXT("Remote Host"));

	GetVarAndWriteKey (pECB, lpszIniFile, "FOXISAPI",
						TEXT("REMOTE_ADDR"), TEXT("Remote Address"));

	GetVarAndWriteKey (pECB, lpszIniFile, "FOXISAPI",
						TEXT("AUTHTEXTYPE"), TEXT("Authentication Method"));

	GetVarAndWriteKey (pECB, lpszIniFile, "FOXISAPI",
						TEXT("REMOTE_USER"), TEXT("Authenticated Username"));


	// Keys not supported:
	//
	// Executable Path
	// From
	// Server Admin
	// Authentication Realm (goes with Authenticated Username)

	// Retrieve ALL_HTTP

	dwBufferSize = sizeof (szBuffer);
	bReturn = pECB->GetServerVariable (pECB->ConnID,
										TEXT("ALL_HTTP"),
										szBuffer,
										&dwBufferSize);

	if (bReturn) {       // expected symbol is found
		//
		// Find lines, split key/data pair and write them to profile
		//

		pChar = szBuffer;
		while (*pChar)  {
			if (*pChar == TEXT('\r') || *pChar == TEXT ('\n'))      {
				pChar++;
				continue;
			}

			pOpts = strchr (pChar, TEXT(':'));  // look for separator
			if (!pOpts)
				break;
			if (!*pOpts)
				break;

			pEnd = pOpts;
			while (*pEnd && *pEnd != TEXT('\r') && *pEnd != TEXT('\n'))
				pEnd++;

			*pOpts = 0;     // split strings
			*pEnd = 0;

			WritePrivateProfileString ("ALL_HTTP",pChar, pOpts + 1, lpszIniFile);
    
			pChar = pEnd + 1;
		}
	}


    
	//
	// Accept section provides info about the client's capabilities.  We use
	// the header information stored in the HTTP_ACCEPT environment variable.
	//
	// The format of this variable is:
	//
	// type/subtype [;opt. parameters] [, type/subtype [;params]] [, ...]
	//
	// For example:
	// */*; q=0.300, audio/x-aiff, audio/basic, image/jpeg, image/gif, text/plain, text/html
	//
	// The above example becomes:
	//
	// [Accept]
	// */*=q=0.300
	// audio/x-aiff=Yes
	// audio/basic=Yes
	// image/jpeg=Yes
	// image/gif=Yes
	// text/plain=Yes
	// text/html=Yes
	//


	//
	// Get the inbound accept line
	//

	dwBufferSize = sizeof(szBuffer);
	bReturn = pECB->GetServerVariable (pECB->ConnID,
										TEXT("HTTP_ACCEPT"),
										szBuffer,
										&dwBufferSize);

    
	if (bReturn) {       // expected symbol is found

		//
		// Skip leading spaces and grab entire type/subtype[;opts] string
		//

		pChar = strtok (szBuffer, TEXT(" ,"));
		while (pChar)  {
			pOpts = strchr (pChar, TEXT(';'));  // look for opts, if any

			WritePrivateProfileString ("Accept",pChar, 
				pOpts == NULL ? TEXT("Yes") : pOpts, lpszIniFile);

			pChar = strtok (NULL, TEXT(" ,")); // get next type/subtype pair
		}
	}

	//
	// The [System] section must be filled out with GMT Offset
	//
	// GMT offset is the number of seconds added to GMT time to reach local
	// time.  For example, PST = GMT - 8 hours; GMT offset would equal 
	// -28,800.  Win32 call GetTimeZoneInformation returns the number of
	// minutes to subtract from GMT (UTC) to get local time.
	//
	// So, GMT Offset = -60*TZI.Bias.
	//
	TIME_ZONE_INFORMATION tzi;
	GetTimeZoneInformation (&tzi);
	_snprintf(szBuffer,sizeof(szBuffer),"%i", -60 * tzi.Bias);
	WritePrivateProfileString ("SYSTEM","GMT Offset", szBuffer, lpszIniFile);
	
	return 0;
}



BOOL WINAPI GetExtensionVersion(HSE_VERSION_INFO *pVer)
{
	pVer->dwExtensionVersion = MAKELONG( HSE_VERSION_MINOR, HSE_VERSION_MAJOR );

	strncpy(pVer->lpszExtensionDesc,
		"FOX OLE Automation Gateway",
		HSE_MAX_EXT_DLL_NAME_LEN);
	return TRUE;
}

DWORD ShowStatus(EXTENSION_CONTROL_BLOCK *pECB,char *szDesc) {
	class CInstances *pInstances,*pNext;
	int ncnt=0,nBusy=0,nCreated=0;
	SYSTEMTIME systime;
//	TIME_ZONE_INFORMATION tzi;
	CHAR szBuf[16384];
	CHAR szDate[100];
	CHAR szTime[100];
	CHAR szRefresh[100];

	DWORD buflen;
	if (!pECB) 
		return HSE_STATUS_SUCCESS;
	__try {
		GetLocalTime(&systime);
		GetDateFormat(LOCALE_USER_DEFAULT,0,&systime,NULL,szDate,sizeof(szDate));
		GetTimeFormat(LOCALE_USER_DEFAULT,0,&systime,NULL,szTime,sizeof(szTime));
//		GetTimeZoneInformation(&tzi);
		if (!lstrcmpi(szDesc,g_szStatusUrl) && g_nAutoRefreshStatus) {//if doing a status page, and we want to send a refresh msg
			_snprintf(szRefresh,sizeof(szRefresh),"<META HTTP-EQUIV=""Refresh"" CONTENT=%d>",g_nAutoRefreshStatus);
		} else {
			*szRefresh = '\0';
		}

		_snprintf(szBuf,sizeof(szBuf), "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n"
			"Expires: Sunday 15-May-94 14:00:01 GMT"
			"\r\n\r\n<html><body bgcolor=%s><h1>%s"
			"FOXISAPI %s </h1>%s %s"
			"<a href=\042/default.htm\042> Back to Default home page</a><p>",
			lstrcmpi(szDesc,g_szStatusUrl)!=0? "808040":"80ff40",szRefresh,
			szDesc,szDate,szTime);
		buflen = lstrlen(szBuf);
		pECB->WriteClient(pECB->ConnID,(void *)szBuf,&buflen,0);
		_snprintf(szBuf,sizeof(szBuf),"<table border=5><th>#</th><th>ProgIDRequest</th>"
			"<th>ProgIDActual</th><th>Exists</th><th>Hits</th><th>AvgSrvTime</th><th>LastSrvTime</th>"
			"<th>Status</th><th>StatusDuration</th>");
		EnterCriticalSection(&g_csRuntime);
		for (pInstances = pRootInstances ; pInstances ; ) {
			pNext = pInstances->m_pNextInstance;
			_snprintf(szBuf+lstrlen(szBuf),sizeof(szBuf),"<tr>");
			_snprintf(szBuf+lstrlen(szBuf),sizeof(szBuf),"<td>%d</td>",++ncnt);
			_snprintf(szBuf+lstrlen(szBuf),sizeof(szBuf),"<td>%s</td>",pInstances->m_szProgIdReq);
			_snprintf(szBuf+lstrlen(szBuf),sizeof(szBuf),"<td>%s</td>",pInstances->m_szProgIdActual);
			if (pInstances->m_lpDispatch) {
				_snprintf(szBuf+lstrlen(szBuf),sizeof(szBuf),"<td>Y</td>");
				nCreated++;
			} else {
				_snprintf(szBuf+lstrlen(szBuf),sizeof(szBuf),"<td>N</td>");
			}
			_snprintf(szBuf+lstrlen(szBuf),sizeof(szBuf),"<td>%d</td>",pInstances->m_lServiceCount);
			_snprintf(szBuf+lstrlen(szBuf),sizeof(szBuf),"<td>%10.3f</td>", 	
				pInstances->m_lServiceCount ? (pInstances->m_dwCumTime /pInstances->m_lServiceCount)/1000.: 0);
			_snprintf(szBuf+lstrlen(szBuf),sizeof(szBuf),"<td>%10.3f</td>", 	
				pInstances->m_dwLastReqTime/1000.);
			_snprintf(szBuf+lstrlen(szBuf),sizeof(szBuf),"<td>%s%s</td>", 	
				pInstances->m_fIsBusy ? (pInstances->m_lpDispatch?"Busy":"?"):"Idle",
				pInstances->m_fIsDebugMode ? " Debug":"");
			if (pInstances->m_fIsBusy) {
				nBusy++;
			}
			float fsecs;
			int msecs,secs,mins, hrs;
			fsecs = (float)((timeGetTime() - pInstances->m_dwTimeStamp)/1000.);
			mins = (int)(fsecs / 60) ;
			hrs = mins / 60;
			mins -= hrs * 60;
			fsecs -= hrs * 3600 + mins * 60;
			secs = (int)fsecs;
			msecs = (int)(1000 * (fsecs - secs));
			_snprintf(szBuf+lstrlen(szBuf),sizeof(szBuf),"<td>%02d:%02d:%02d.%03d</td>",hrs,mins,secs,msecs);
			
			_snprintf(szBuf+lstrlen(szBuf),sizeof(szBuf),"</tr>");

			pInstances = pNext;
		}
		LeaveCriticalSection(&g_csRuntime);
		_snprintf(szBuf+lstrlen(szBuf),sizeof(szBuf),"</table>");
		_snprintf(szBuf+lstrlen(szBuf),sizeof(szBuf),"<p><p># busy instances = %d    # Created = %d    BusyTimeout = %d   ReleaseTimeout = %d",
			nBusy,nCreated, g_BusyTimeout/1000,g_ReleaseTimeout/1000);
		_snprintf(szBuf+lstrlen(szBuf),sizeof(szBuf),"    SingleMode = %d</pre>",g_fSingleMode);
		GetDateFormat(LOCALE_USER_DEFAULT,0,&stServerStartTimeStamp,NULL,szDate,sizeof(szDate));
		GetTimeFormat(LOCALE_USER_DEFAULT,0,&stServerStartTimeStamp,NULL,szTime,sizeof(szTime));
		_snprintf(szBuf+lstrlen(szBuf),sizeof(szBuf),"<p>Server started %s %s",szDate,szTime);
		buflen = strlen(szBuf);
		pECB->WriteClient(pECB->ConnID,(void *)szBuf,&buflen,0);
	} __except  (EXCEPTION_EXECUTE_HANDLER) {
		return HSE_STATUS_ERROR;
	}
	return HSE_STATUS_SUCCESS;
}

/*
[foxis.employee]
foxis.employee = 22	
;test comment
foxisr1.employee=23
foxisr2.employee=24


[intern.intern]
intern.intern=1

*/

DWORD ReadIniFile(BOOL fDoPreReload) {	//read foxisapi.ini file
	DWORD retval;
	char szIniFileName[MAX_PATH];
	char szBuf[16384],szBuf2[16384],*pBuf,*pBuf2,szBuf3[100];
	char szErrorMessage[4096];

	EnterCriticalSection(&g_csRuntime);
	__try {
		lstrcpy(szIniFileName,gszAppName);
		*strrchr(szIniFileName,'.') = '\0';
		lstrcat(szIniFileName,".ini");
		GetPrivateProfileString(0,0,"",szBuf,sizeof(szBuf),szIniFileName);
		for (pBuf = szBuf ; *pBuf ; ) {
			char szProgIdReq[PROGIDSIZE],szProgIdActual[PROGIDSIZE];
			int nInstances;
			CLSID clsid;
			lstrcpy(szProgIdReq,pBuf);
			pBuf += lstrlen(szProgIdReq) + 1;
			if (lstrcmpi(szProgIdReq,"foxisapi") == 0) {
				GetPrivateProfileString(szProgIdReq,"busytimeout","2",szBuf2,sizeof(szBuf2),szIniFileName);
				g_BusyTimeout = 1000 * atoi(szBuf2);
				GetPrivateProfileString(szProgIdReq,"releasetimeout","2",szBuf2,sizeof(szBuf2),szIniFileName);
				g_ReleaseTimeout = 1000 * atoi(szBuf2);
				GetPrivateProfileString(szProgIdReq,"AutoRefreshStatus","0",szBuf2,sizeof(szBuf2),szIniFileName);
				g_nAutoRefreshStatus = atoi(szBuf2);
				GetPrivateProfileString(szProgIdReq,"resetUrl","reset",g_szResetUrl,sizeof(g_szResetUrl),szIniFileName);
				GetPrivateProfileString(szProgIdReq,"statusUrl","status",g_szStatusUrl,sizeof(g_szStatusUrl),szIniFileName);
				GetPrivateProfileString(szProgIdReq,"SingleModeUrl","SingleMode",g_szSingleModeUrl,sizeof(g_szSingleModeUrl),szIniFileName);
				GetPrivateProfileString(szProgIdReq,"MultiModeUrl","MultiMode",g_szMultiModeUrl,sizeof(g_szMultiModeUrl),szIniFileName);
				GetPrivateProfileString(szProgIdReq,"Debugger","VisualFoxpro.Application",g_szDebugger,sizeof(g_szDebugger),szIniFileName);
				continue;
			}

			GetPrivateProfileString(szProgIdReq,0,"default",szBuf2,sizeof(szBuf2),szIniFileName);
			for (pBuf2 = szBuf2 ; *pBuf2 ; ) {				//now read in all the subProgids
				int fDebug = 0;
				lstrcpy(szProgIdActual,pBuf2);
				pBuf2 +=lstrlen(szProgIdActual) + 1;
				GetPrivateProfileString(szProgIdReq,szProgIdActual,"default",szBuf3,sizeof(szBuf3),szIniFileName);
				nInstances = atoi(szBuf3);
				if (nInstances == 0)	{ //debug mode
					nInstances++;
					fDebug = 1;
					lstrcpy(szProgIdActual,g_szDebugger);
				}
				if (S_OK ==  GetClsidFromProgIdA(&clsid, szProgIdActual)) {
					for (int n = 0 ; n< nInstances ; n++ ) {
						AddOne(clsid,szProgIdReq,szProgIdActual,0);
						if (fDoPreReload && strrchr(szBuf3,'*')) {	//precreate the server
							HRESULT hr;
							IDispatch *pdispObj = NULL;
							IUnknown *punkObj = NULL;
							class CInstances *pInstances;
							pInstances = pRootInstances;

							// instantiate object
							hr = CoCreateInstance(pInstances->m_clsid, NULL, CLSCTX_SERVER, IID_IUnknown, (LPVOID *) &punkObj);	//create it
							if (FAILED(hr) || punkObj == NULL) {
								char szSysMsg[100];
								FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,0,hr,
									MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),szSysMsg,sizeof(szSysMsg),0);

								sprintf(szErrorMessage,"CoCreateInstance failed with err code %08x: %s",hr,szSysMsg);
								throw szErrorMessage;
							}
							hr = punkObj->QueryInterface(IID_IDispatch, (void**)&pdispObj);
							if (FAILED(hr) || pdispObj == NULL)  {
								char szSysMsg[100];
								FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,0,hr,
									MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),szSysMsg,sizeof(szSysMsg),0);

								sprintf(szErrorMessage,"QueryInterface failed with err code %08x: %s",hr,szSysMsg);
								throw szErrorMessage;
							}
							punkObj->Release();
							punkObj = NULL;
							pInstances->m_lpDispatch = pdispObj;	//keep the dispatch pointer around in our array
							CoMarshalInterThreadInterfaceInStream(IID_IDispatch,pdispObj,&pInstances->m_pStm);	//marshall to other threads
							pdispObj->Release();
						}
					}
				}
				if (fDebug)
					pRootInstances->m_fIsDebugMode = 1;

			}
		}
		retval = HSE_STATUS_SUCCESS;
	} __except  (EXCEPTION_EXECUTE_HANDLER) {
		retval = HSE_STATUS_ERROR;
	}
	LeaveCriticalSection(&g_csRuntime);
	return retval;	
}


DWORD ResetAll(EXTENSION_CONTROL_BLOCK *pECB) {	//release all cached instances unless MultiMode = 1 (SingleMode)
	class CInstances *pInstances,*pNext;
	EnterCriticalSection(&g_csRuntime);
	__try {
		for (pInstances = pRootInstances ; pInstances ; ) {
			pNext = pInstances->m_pNextInstance;
			if (pInstances->m_fIsBusy) {
				if (pInstances->m_lpDispatch) {	
					DWORD EndTime;
					EndTime = timeGetTime() + g_ReleaseTimeout;
					while (timeGetTime() < EndTime && pInstances->m_fIsBusy) {
					}
				} else {
					pInstances->m_fIsBusy=0;
				}
			}
			if (!pInstances->m_fIsBusy) {
				delete pInstances;
			} else {	//what do we do with a server that is hung?...
			}
			pInstances = pNext;
		}
		pRootInstances = NULL;

	} __except  (EXCEPTION_EXECUTE_HANDLER) {
		return HSE_STATUS_ERROR;
	}
	CoFreeUnusedLibraries();
	if (pECB) {
		ReadIniFile(pECB && (*pECB->lpszQueryString == '1'));
	}
	LeaveCriticalSection(&g_csRuntime);
	if (pECB) {
		return ShowStatus(pECB,"Reset");
	}
	return 0;
}

DWORD WINAPI TerminateExtension(void)
{
	int i=0;
	ResetAll(0);	//this doesn't work because OLE is already terminated
	return i;
}

DWORD WINAPI HttpExtensionProc(EXTENSION_CONTROL_BLOCK *pECB)
{
	CHAR pszPathString[PARAMLEN];
	CHAR *pszProgid = NULL;
	CHAR *pszMethod = NULL;
	CHAR *pszTemp = NULL;
	char lpszIniFile[4096];
	int hr;
	static BOOL fHaveReadIniFile = FALSE;
#ifdef _DEBUG
	__try	{	//uncomment the next line for a hard coded breakpoint
//		_asm int 3		
	}	
	__except (UnhandledExceptionFilter(GetExceptionInformation())) {
		int i;
		i=5;	//so we can set a breakpoint here
	}
#endif
	if (FALSE == TlsGetValue(g_dwTLSIndex)) {
		OleInitialize(NULL);
		TlsSetValue(g_dwTLSIndex, (void*)TRUE);
	}
	if (!fHaveReadIniFile) {	//must be done exactly once after oleinit
		fHaveReadIniFile = TRUE;
		ReadIniFile(TRUE);
	}

	// only GET and POST supported
	if (strcmp(pECB->lpszMethod, "GET") && strcmp(pECB->lpszMethod, "POST"))
	{
		return HSE_STATUS_ERROR;
	}


	// extract progid & method name from path info
	strncpy(pszPathString, pECB->lpszPathInfo, PARAMLEN);
	if ('/' == *pszPathString) {
		pszProgid = pszPathString + 1;
	}
	pszMethod = strchr(pszPathString, '.');
	if (NULL != pszMethod) {
		// progids can have zero or one periods in them
		pszTemp = strchr(pszMethod + 1, '.');
		// separate progid from args
		if (NULL != pszTemp) {
			*pszTemp = '\0';
			pszMethod = pszTemp + 1;
		} else {
			*pszMethod = '\0';
			pszMethod++;
		}
	}
	if (lstrcmpi(pszProgid,g_szResetUrl) == 0) {
		return ResetAll(pECB);
	}
	if (lstrcmpi(pszProgid,g_szSingleModeUrl) == 0) {
		g_fSingleMode =1;
		return ResetAll(pECB);
	}
	if (lstrcmpi(pszProgid,g_szMultiModeUrl) == 0) {
		g_fSingleMode =0;
		return ShowStatus(pECB,pszProgid);
	}
	if (lstrcmpi(pszProgid,g_szStatusUrl) == 0) {
		return ShowStatus(pECB,pszProgid);
	}
	if (hr = LogExtraInfo(pECB,lpszIniFile))	//assignment
		return hr;
	// startup object, invoke method, and return results
	if (FALSE == CallObject(pECB, pszProgid, pszMethod,lpszIniFile)) {
		return HSE_STATUS_ERROR;
	}
	return HSE_STATUS_SUCCESS;
}


BOOL WINAPI DllMain(HMODULE hMod, DWORD fReason, LPVOID pvRes)
{
	switch (fReason) {
	case DLL_PROCESS_ATTACH:
		GetModuleFileName(hMod,gszAppDir,sizeof(gszAppDir));
		GetLocalTime(&stServerStartTimeStamp);
		lstrcpy(gszAppName,gszAppDir);
		*strrchr(gszAppDir,'\\') = '\0';
		g_dwTLSIndex = TlsAlloc();
		InitializeCriticalSection(&g_csRuntime);
		if (-1 == g_dwTLSIndex)
			  return FALSE;
		break;

	case DLL_THREAD_ATTACH:
		// set this flag to true once ole has been initialized
		TlsSetValue(g_dwTLSIndex, FALSE);
		break;

	case DLL_PROCESS_DETACH:
		if (-1 != g_dwTLSIndex)
			TlsFree(g_dwTLSIndex);
		DeleteCriticalSection(&g_csRuntime);
		break;

	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}