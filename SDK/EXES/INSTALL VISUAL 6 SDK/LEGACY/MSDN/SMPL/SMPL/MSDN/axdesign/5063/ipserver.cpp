//=--------------------------------------------------------------------------=
// InProcServer.Cpp
//=--------------------------------------------------------------------------=
// Copyright  1995  Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// implements all exported DLL functions for the program, as well as a few
// others that will be used by same
//
#include "IPServer.H"
#include "LocalSrv.H"

#include "AutoObj.H"
#include "ClassF.H"
#include "CtrlObj.H"
#include "Globals.H"
#include "Unknown.H"
#include "Util.H"

//=--------------------------------------------------------------------------=
// Private module level data
//
// for ASSERT and FAIL
//
SZTHISFILE

//=--------------------------------------------------------------------------=
// These are used for reflection in OLE Controls.  Not that big of a hit that
// we mind defining them for all servers, including automation or generic
// COM.
//
char g_szReflectClassName [] = "CtlFrameWork_ReflectWindow";
BYTE g_fRegisteredReflect = FALSE;

extern HINSTANCE g_hInstResources;

// ref count for LockServer
//
LONG  g_cLocks;


// private routines for this file.
//
int       IndexOfOleObject(REFCLSID);
HRESULT   RegisterAllObjects(void);
HRESULT   UnregisterAllObjects(void);
void      CleanupGlobalObjects(void);

//=--------------------------------------------------------------------------=
// DllMain
//=--------------------------------------------------------------------------=
// yon standard LibMain.
//
// Parameters and Output:
//    - see SDK Docs on DllMain
//
// Notes:
//
BOOL WINAPI DllMain
(
    HANDLE hInstance,
    DWORD  dwReason,
    void  *pvReserved
)
{
//    int i;

    switch (dwReason) {
      // set up some global variables, and get some OS/Version information
      // set up.
      //
      case DLL_PROCESS_ATTACH:
        {
        DWORD dwVer = GetVersion();
        DWORD dwWinVer;

        //  swap the two lowest bytes of dwVer so that the major and minor version
        //  numbers are in a usable order.
        //  for dwWinVer: high byte = major version, low byte = minor version
        //     OS               Sys_WinVersion  (as of 5/2/95)
        //     =-------------=  =-------------=
        //     Win95            0x035F   (3.95)
        //     WinNT ProgMan    0x0333   (3.51)
        //     WinNT Win95 UI   0x0400   (4.00)
        //
        dwWinVer = (UINT)(((dwVer & 0xFF) << 8) | ((dwVer >> 8) & 0xFF));
        g_fSysWinNT = FALSE;
        g_fSysWin95 = FALSE;
        g_fSysWin95Shell = FALSE;

        if (dwVer < 0x80000000) {
            g_fSysWinNT = TRUE;
            g_fSysWin95Shell = (dwWinVer >= 0x0334);
        } else  {
            g_fSysWin95 = TRUE;
            g_fSysWin95Shell = TRUE;
        }

        // initialize a critical seciton for our apartment threading support
        //
        InitializeCriticalSection(&g_CriticalSection);

        // create an initial heap for everybody to use.
        // currently, we're going to let the system make things thread-safe,
        // which will make them a little slower, but hopefully not enough
        // to notice
        //
        if (!g_hHeap)
            g_hHeap = GetProcessHeap();
        if (!g_hHeap) {
            FAIL("Couldn't get Process Heap.  Not good!");
            return FALSE;
        }

        g_hInstance = (HINSTANCE)hInstance;

        // give the user a chance to initialize whatever
        //
        InitializeLibrary();
        return TRUE;
        }

      // do  a little cleaning up!
      //
      case DLL_PROCESS_DETACH:

        // clean up some stuff
        //
        DeleteCriticalSection(&g_CriticalSection);
        CleanupGlobalObjects();

        // give the user a chance to do some cleaning up
        //
        UninitializeLibrary();

	// Make sure we free up our cached resource handle for localized resources
	//
	if (g_hInstResources && g_hInstResources != g_hInstance)
		FreeLibrary(g_hInstResources);
			
        return TRUE;
    }

    return TRUE;
}


//=--------------------------------------------------------------------------=
// CleanupGlobalObjects
//=--------------------------------------------------------------------------=
// duh
//
// Notes:
//
void CleanupGlobalObjects(void)
{
    int i = 0;

    while (!ISEMPTYOBJECT(i)) {
        if (g_ObjectInfo[i].usType == OI_CONTROL) {
            if (CTLWNDCLASSREGISTERED(i))
                UnregisterClass(WNDCLASSNAMEOFCONTROL(i), g_hInstance);
        }
        i++;
    }

    // clean up our parking window.
    //
    if (g_hwndParking) {
        DestroyWindow(g_hwndParking);
        g_hwndParking = NULL;
        UnregisterClass("CtlFrameWork_Parking", g_hInstance);
    }

    // clean up after reflection, if appropriate.
    //
    if (g_fRegisteredReflect) {
        UnregisterClass(g_szReflectClassName, g_hInstance);
        g_fRegisteredReflect = FALSE;
    }
}

//=--------------------------------------------------------------------------=
// DllRegisterServer
//=--------------------------------------------------------------------------=
// registers the Automation server
//
// Output:
//    HRESULT
//
// Notes:
//
STDAPI DllRegisterServer
(
    void
)
{
    HRESULT hr;

    hr = RegisterAllObjects();
    RETURN_ON_FAILURE(hr);

    // call user registration function.
    //
    return (RegisterData())? S_OK : E_FAIL;
}



//=--------------------------------------------------------------------------=
// DllUnregisterServer
//=--------------------------------------------------------------------------=
// unregister's the Automation server
//
// Output:
//    HRESULT
//
// Notes:
//
STDAPI DllUnregisterServer
(
    void
)
{
    HRESULT hr;

    hr = UnregisterAllObjects();
    RETURN_ON_FAILURE(hr);

    // call user unregistration function
    //
    return (UnregisterData()) ? S_OK : E_FAIL;
}


//=--------------------------------------------------------------------------=
// DllCanUnloadNow
//=--------------------------------------------------------------------------=
// we are being asked whether or not it's okay to unload the DLL.  just check
// the lock counts on remaining objects ...
//
// Output:
//    HRESULT        - S_OK, can unload now, S_FALSE, can't.
//
// Notes:
//
STDAPI DllCanUnloadNow
(
    void
)
{
    // if there are any objects lying around, then we can't unload.  The
    // controlling CUnknownObject class that people should be inheriting from
    // takes care of this
    //
    return (g_cLocks) ? S_FALSE : S_OK;
}


//=--------------------------------------------------------------------------=
// DllGetClassObject
//=--------------------------------------------------------------------------=
// creates a ClassFactory object, and returns it.
//
// Parameters:
//    REFCLSID        - CLSID for the class object
//    REFIID          - interface we want class object to be.
//    void **         - pointer to where we should ptr to new object.
//
// Output:
//    HRESULT         - S_OK, CLASS_E_CLASSNOTAVAILABLE, E_OUTOFMEMORY,
//                      E_INVALIDARG, E_UNEXPECTED
//
// Notes:
//
STDAPI DllGetClassObject
(
    REFCLSID rclsid,
    REFIID   riid,
    void   **ppvObjOut
)
{
    HRESULT hr;
    void   *pv;
    int     iIndex;

    // arg checking
    //
    if (!ppvObjOut)
        return E_INVALIDARG;

    // first of all, make sure they're asking for something we work with.
    //
    iIndex = IndexOfOleObject(rclsid);
    if (iIndex == -1)
        return CLASS_E_CLASSNOTAVAILABLE;

    // create the blank object.
    //
    pv = (void *)new CClassFactory(iIndex);
    if (!pv)
        return E_OUTOFMEMORY;

    // QI for whatever the user has asked for.
    //
    hr = ((IUnknown *)pv)->QueryInterface(riid, ppvObjOut);
    ((IUnknown *)pv)->Release();

    return hr;
}
//=--------------------------------------------------------------------------=
// IndexOfOleObject
//=--------------------------------------------------------------------------=
// returns the index in our global table of objects of the given CLSID.  if
// it's not a supported object, then we return -1
//
// Parameters:
//    REFCLSID     - [in] duh.
//
// Output:
//    int          - >= 0 is index into global table, -1 means not supported
//
// Notes:
//
int IndexOfOleObject
(
    REFCLSID rclsid
)
{
    int x = 0;

    // an object is creatable if it's CLSID is in the table of all allowable object
    // types.
    //
    while (!ISEMPTYOBJECT(x)) {
        if (OBJECTISCREATABLE(x)) {
            if (rclsid == CLSIDOFOBJECT(x))
                return x;
        }
        x++;
    }

    return -1;
}

//=--------------------------------------------------------------------------=
// RegisterAllObjects
//=--------------------------------------------------------------------------=
// registers all the objects for the given automation server.
//
// Parameters:
//    none
//
// Output:
//    HERSULT        - S_OK, E_FAIL
//
// Notes:
//
HRESULT RegisterAllObjects
(
    void
)
{
    ITypeLib *pTypeLib;
    HRESULT hr;
    DWORD   dwPathLen;
    char    szTmp[MAX_PATH];
    char    szHelpPath[MAX_PATH];
    int     x = 0;
    BOOL    fHelpFile = FALSE;
    UINT    cbWinHelpPath = 0;
    OFSTRUCT ofs;
    OLECHAR *pwszHelpPath;
         
    // loop through all of our creatable objects [those that have a clsid in
    // our global table] and register them.
    //
    while (!ISEMPTYOBJECT(x)) {
        if (!OBJECTISCREATABLE(x)) {
            x++;
            continue;
        }
	
	// Check to see if there is a help file for the object
	// If so, look for it in the Windows\Help directory.  If a help file is 
	// found for any object in the Windows\Help directory, then we'll register it with 
	// the typelib.  Once we find the first help file we stop looking.
	//
	if (!fHelpFile)
	{
		if (cbWinHelpPath == 0)	
		{
			cbWinHelpPath = GetHelpFilePath(szHelpPath, MAX_PATH);
			lstrcat(szHelpPath, "\\");
			cbWinHelpPath++;
		}
		
		ASSERT(cbWinHelpPath > 0, "Help path is zero length");
		ASSERT(cbWinHelpPath + ((HELPFILEOFOBJECT(x)) ? lstrlen(HELPFILEOFOBJECT(x)) : 0) < MAX_PATH, "Help file path exceeds maxiumu path");
		
		// Make sure we have a non-NULL pointer before calling lstrlen
		//		
		if (HELPFILEOFOBJECT(x) && lstrlen(HELPFILEOFOBJECT(x)) > 0)
		{
			lstrcpyn(szHelpPath + cbWinHelpPath, HELPFILEOFOBJECT(x), lstrlen(HELPFILEOFOBJECT(x)) + 1);
			fHelpFile = (HFILE_ERROR != OpenFile(szHelpPath, &ofs, OF_EXIST | OF_READ));
		}
		
		// Once we've determined the help file exists, terminate after the filename
		// since all we care to register is the path.  Not the path and filename.  We also
		// don't want the terminating '\', so subtract 1 from cbWinHelpPath.
		//
		if (fHelpFile)
			szHelpPath[cbWinHelpPath - 1] = '\0';
		else
			szHelpPath[cbWinHelpPath] = '\0';
	}

        // depending on the object type, register different pieces of information
        //
        switch (g_ObjectInfo[x].usType) {

          // for both simple co-creatable objects and proeprty pages, do the same
          // thing
          //
          case OI_UNKNOWN:
          case OI_PROPERTYPAGE:
            RegisterUnknownObject(NAMEOFOBJECT(x), CLSIDOFOBJECT(x));
            break;

          case OI_AUTOMATION:
            RegisterAutomationObject(g_szLibName, NAMEOFOBJECT(x), VERSIONOFOBJECT(x), 
                                     *g_pLibid, CLSIDOFOBJECT(x));
            break;

          case OI_CONTROL:
            RegisterControlObject(g_szLibName, NAMEOFOBJECT(x), VERSIONOFOBJECT(x), VERSIONMINOROFOBJECT(x),
                                  *g_pLibid, CLSIDOFOBJECT(x), OLEMISCFLAGSOFCONTROL(x),
                                  BITMAPIDOFCONTROL(x));
            break;

        }
        x++;
    }

    // Load and register our type library.
    //
    if (g_fServerHasTypeLibrary) {
        dwPathLen = GetModuleFileName(g_hInstance, szTmp, MAX_PATH);
        MAKE_WIDEPTR_FROMANSI(pwsz, szTmp);
        hr = LoadTypeLib(pwsz, &pTypeLib);
        RETURN_ON_FAILURE(hr);
		
	if (fHelpFile)
		pwszHelpPath = OLESTRFROMANSI(szHelpPath);

        hr = RegisterTypeLib(pTypeLib, pwsz, fHelpFile ? pwszHelpPath : NULL);

	if (fHelpFile)
		CoTaskMemFree(pwszHelpPath);

        pTypeLib->Release();
        RETURN_ON_FAILURE(hr);
    }

    return S_OK;
}

//=--------------------------------------------------------------------------=
// UnregisterAllObjects
//=--------------------------------------------------------------------------=
// un-registers all the objects for the given automation server.
//
// Parameters:
//    none
//
// Output:
//    HRESULT        - S_OK
//
// Notes:
//	WARNING! You must link with the new version of OLEAUT shipping with
//	         Visual Basic version 5.0 in order for this function to 
//	         work correctly.
//
HRESULT UnregisterAllObjects
(
    void
)
{
    HRESULT hr;
    int x = 0;
    
    char szTmp[MAX_PATH];
    TLIBATTR *ptlibattr = NULL;
    ITypeLib *pTypeLib = NULL;

    // loop through all of our creatable objects [those that have a clsid in
    // our global table] and register them.
    //
    while (!ISEMPTYOBJECT(x)) {
        if (!OBJECTISCREATABLE(x)) {
            x++;
            continue;
        }

        switch (g_ObjectInfo[x].usType) {

          case OI_UNKNOWN:
          case OI_PROPERTYPAGE:
            UnregisterUnknownObject(CLSIDOFOBJECT(x), NULL);
            break;

          case OI_CONTROL:
            UnregisterControlObject(g_szLibName, NAMEOFOBJECT(x), VERSIONOFOBJECT(x), 
                                    CLSIDOFOBJECT(x));
	    break;
    
          case OI_AUTOMATION:
            UnregisterAutomationObject(g_szLibName, NAMEOFOBJECT(x), VERSIONOFOBJECT(x), 
                                       CLSIDOFOBJECT(x));
            break;

        }
        x++;
    }

    // if we've got one, unregister our type library 
    if (g_pLibid)
    {
	GetModuleFileName(g_hInstance, szTmp, MAX_PATH);
	MAKE_WIDEPTR_FROMANSI(pwsz, szTmp);

	hr = LoadTypeLibEx(pwsz, REGKIND_NONE, &pTypeLib);
	if (FAILED(hr)) goto CleanUp;

	hr = pTypeLib->GetLibAttr(&ptlibattr);		
	if (FAILED(hr)) goto CleanUp;
	
	// Call OLEAUT to have it unregister our type library.  It will handle
	// the case where there is a 16-bit version of the control's typelib
	// registered and will only blow away the 32-bit related keys in this case.
	//
	UnRegisterTypeLib(*g_pLibid, ptlibattr->wMajorVerNum, ptlibattr->wMinorVerNum, ptlibattr->lcid, ptlibattr->syskind);

    }


CleanUp:
    if (ptlibattr)
	pTypeLib->ReleaseTLibAttr(ptlibattr);
    
    RELEASE_OBJECT(pTypeLib);
    
    return S_OK;
}

