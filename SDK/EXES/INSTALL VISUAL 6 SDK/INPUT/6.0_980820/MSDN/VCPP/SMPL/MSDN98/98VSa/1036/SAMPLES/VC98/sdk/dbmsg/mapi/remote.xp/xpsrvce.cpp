///////////////////////////////////////////////////////////////////////////////
//
//  File Name 
//      XPSRVCE.CPP
//
//  Description
//      This file implements the entry points, XPProviderInit and 
//      ServiceEntry for this provider's DLL.
//
//  Author
//      Irving De la Cruz
//
//  Revision: 1.7
//
// Written for Microsoft Windows Developer Support
// Copyright (c) 1995-1996 Microsoft Corporation. All rights reserved.
//
#include "XPWDSR.H"

// Remark this line to turn verbose tracing OFF
#define DO_INFO_TRACES
#ifdef DO_INFO_TRACES
#define InfoTrace(a)   TraceInfoMessage(a)
#else
#define InfoTrace(a)   
#endif // DO_INFO_TRACES

DTBLEDIT     DtUploadTime = { sizeof(DTBLEDIT), fMapiUnicode, 5, PR_TMP_UPLOAD_TIME };
DTBLCHECKBOX DtGetHeaders = { sizeof(DTBLCHECKBOX), fMapiUnicode, PR_SMP_GET_HEADERS };

DTCTL XPConfigPage[] =
{
    { DTCT_PAGE,     0,           NULL, 0, NULL,     0,                  &DtPage       },
    { DTCT_EDIT,     DT_REQUIRED, NULL, 0, szFilter, IDC_UPLOAD_TIME,    &DtUploadTime },
    { DTCT_CHECKBOX, 0,           NULL, 0, NULL,     IDC_UPDATE_HEADERS, &DtGetHeaders },
    { DTCT_LABEL,    0,           NULL, 0, NULL,     IDC_STATIC1,        &DtLabel      },
    { DTCT_GROUPBOX, 0,           NULL, 0, NULL,     IDC_STATIC2,        &DtGroupBox   },
    { DTCT_GROUPBOX, 0,           NULL, 0, NULL,     IDC_STATIC3,        &DtGroupBox   }
};

TCHAR szDefaultTime[] = TEXT("23:59");

// Global pointer to the MAPI memory allocation functions
LPALLOCATEBUFFER    gpfnAllocateBuffer;  // MAPIAllocateBuffer function
LPALLOCATEMORE      gpfnAllocateMore;    // MAPIAllocateMore function    
LPFREEBUFFER        gpfnFreeBuffer;      // MAPIFreeBuffer function      

///////////////////////////////////////////////////////////////////////////////
//    ServiceEntry()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Called by the profile setup API to display the provider
//      configuration properties for this transport provider
//
//    Return Value
//      An HRESULT
//
HRESULT STDAPICALLTYPE ServiceEntry (HINSTANCE          hInstance,
                                     LPMALLOC           pMallocObj,
                                     LPMAPISUP          pSupObj,
                                     ULONG              ulUIParam,
                                     ULONG              ulFlags,
                                     ULONG              ulContext,
                                     ULONG              ulCfgPropCount,
                                     LPSPropValue       pCfgProps,
                                     LPPROVIDERADMIN    pAdminProvObj,
                                     LPMAPIERROR *      ppMAPIError)
{
    // Look at TRACES.H and TRACES.CPP for more options to the InitTraces() function
    //InitTraces (0);                                       // Send output only to the COM1 port
    InitTraces (TRACES_CONSOLE | TRACES_NO_COM_OUTPUT);     // Send output to a console window BUT NOT to the COM1
    //InitTraces (TRACES_CONSOLE | TRACES_LOG_FILE);        // Send output to COM1 port AND a console window AND to a log file in C:\MAPILOG.TXT

    InfoTrace ("ServiceEntry function called");
    HRESULT hResult = S_OK;
    LPPROFSECT pProfileObj = NULL;
    ULONG ulPropCount;
    LPSPropValue pProps = NULL;
    HANDLE hUIMutex = NULL;

    // What context where were we called in?
    if (MSG_SERVICE_INSTALL         == ulContext ||
        MSG_SERVICE_UNINSTALL       == ulContext ||
        MSG_SERVICE_PROVIDER_CREATE == ulContext ||
        MSG_SERVICE_PROVIDER_DELETE == ulContext)
    {
        // We don't handle any of these contexts
        TraceString1 ("ServiceEntry: Immediate return. Context: %d", ulContext);
        goto ErrorExit;
    }
    TraceString1 ("ServiceEntry: Context for call: %d", ulContext);
    ghInstance = hInstance;
    
    // Get the MAPI memory allocation routines we'll be needing
    hResult = pSupObj->GetMemAllocRoutines (&gpfnAllocateBuffer, &gpfnAllocateMore, &gpfnFreeBuffer);
    if (hResult)
    {
        TraceResult ("ServiceEntry: Failed to get the memory allocation functions", hResult);
        goto ErrorExit;
    }

    // Open the Profile Section for this service
    hResult = pAdminProvObj->OpenProfileSection (NULL,
                                                 NULL,
                                                 MAPI_MODIFY,
                                                 &pProfileObj);
    if (hResult)
    {
        goto ErrorExit;
    }
    if (MSG_SERVICE_CREATE == ulContext)
    {
        // If ServiceEntry is called because it the service is being created, we create a temporary
        // file where we save the headers text file when the user updates them from
        // the remote host. The headers should be persistent from session to
        // session (using the same profile, of course) but unique per session.
        TCHAR szTmpDir[_MAX_PATH], szFile[_MAX_PATH];
        GetTempPath (_MAX_PATH, szTmpDir);
        lstrcat (szTmpDir, WINDS_DATA_DIRECTORY);
        CreateDirectory (szTmpDir, NULL);
        GetTempFileName (szTmpDir,      // Create the file in the system temp directory
                         TEXT("XRH"),   // Our transport fixed prefix for temp files
                         0,             // Use the time to create a pseudo-random number
                         szFile);       // Destination buffer
        SPropValue spvProps[4] = { 0 };
        spvProps[0].ulPropTag = PR_SMP_HEADERS_FILENAME;
        spvProps[0].Value.LPSZ = szFile;
        SYSTEMTIME st;
        GetLocalTime (&st);
        st.wHour = 23; st.wMinute = 59; st.wSecond = 0;
        spvProps[1].ulPropTag = PR_SMP_UPLOAD_TIME;
        SystemTimeToFileTime (&st, &spvProps[1].Value.ft);
        spvProps[2].ulPropTag = PR_SMP_CONNECTION_TYPE;
        spvProps[2].Value.l = OFFLINE_CONNECT;
        spvProps[3].ulPropTag = PR_SMP_GET_HEADERS;
        spvProps[3].Value.b = TRUE;
        hResult = pProfileObj->SetProps (sizeof(spvProps)/sizeof(SPropValue), spvProps, NULL);
        TraceResult ("ServiceEntry: Failed to save the headers file name back into the profile", hResult);
    }
    // The profile section is open, get the properties out of it
    hResult = pProfileObj->GetProps ((LPSPropTagArray)&sptLogonProps,
                                     fMapiUnicode,
                                     &ulPropCount,
                                     &pProps);
    if (FAILED(hResult))
    {
        TraceResult ("ServiceEntry: Failed to get profile section properties", hResult);
        goto ErrorExit;
    }
    ASSERT (NUM_LOGON_PROPERTIES == ulPropCount);

    if (MSG_SERVICE_DELETE == ulContext)
    {
        // If the service is being removed from a profile, we must cleanup
        // any temporary file (i.e. the headers text file)
        if (PR_SMP_HEADERS_FILENAME == pProps[HEADER_FILE].ulPropTag)
        {
            DeleteFile (pProps[HEADER_FILE].Value.LPSZ);
        }
        TCHAR szTmpDir[_MAX_PATH], szDownloadDir[_MAX_PATH];
        GetTempPath (_MAX_PATH, szTmpDir);
        lstrcat (szTmpDir, WINDS_DATA_DIRECTORY);
        if (PR_SMP_MAILBOX_NAME == pProps[MAILBOX_NAME].ulPropTag)
        {
            wsprintf (szDownloadDir, WINDS_DOWNLOAD_DIR_NAME_FORMAT, szTmpDir, pProps[MAILBOX_NAME].Value.LPSZ);
            RemoveDirectory (szDownloadDir);
        }
        RemoveDirectory (szTmpDir);
        // We are done
        hResult = S_OK;
        goto ErrorExit;
    }
    // After the setup wizard has been called the ServiceEntry functions gets called
    // with a set of properties obtained from the user for configuring this provider.
    // Merge or replace those properties onto the one we obtained from the profile section.
    if (pCfgProps && ulCfgPropCount)
    {
        hResult = MergeConfigProps (ulCfgPropCount, pCfgProps, pProps);
        if (hResult)
        {
            goto ErrorExit;
        }
    }
    // If we can, display the UI...
    if (SERVICE_UI_ALWAYS & ulFlags || SERVICE_UI_ALLOWED & ulFlags)
    {
        CFGDLG CfgDialog = { 0 };
        hUIMutex = CreateMutex (NULL, FALSE, CONFIG_UI_MUTEX);
        if (NULL == hUIMutex)
        {
            TraceResult ("ServiceEntry: Failed to create UI mutext", GetLastError());
        }
        PrivInitialize3DCtl (hInstance);
        if (WAIT_TIMEOUT == WaitForSingleObject (hUIMutex, 250)) // Wait for the MUTEX for 1/4 second
        {
            PrivateMessageBox (IDS_MSG_CONFIG_UI_IN_USE, (HWND)ulUIParam);
            hResult = MAPI_E_BUSY;
            goto ErrorExit;
        }

        // Fill in the logon UI structure
        CfgDialog.hInst    = hInstance;
        CfgDialog.hWnd     = (HWND)ulUIParam;
        CfgDialog.ppProps  = &pProps;
        CfgDialog.pSupObj  = pSupObj;
        CfgDialog.ulFlags  = MSG_SERVICE_UI_READ_ONLY & ulFlags ? UI_READONLY : 0;
        CfgDialog.hUIMutex = NULL; // So that the DoLogonDlg() won't have to wait.
ShowPropsAgain:
        hResult = DoLogonDlg (&CfgDialog);
        if (hResult)
        {
            goto ErrorExit;
        }
        if (!PingRemoteServer ((HWND)ulUIParam, pProps))
        {
            goto ShowPropsAgain;
        }
    }
    if (PR_SMP_MAILBOX_NAME == pProps[MAILBOX_NAME].ulPropTag)
    {
        TCHAR szTmpDir[_MAX_PATH], szDownloadDir[_MAX_PATH];
        GetTempPath (_MAX_PATH, szTmpDir);
        lstrcat (szTmpDir, WINDS_DATA_DIRECTORY);
        wsprintf (szDownloadDir, WINDS_DOWNLOAD_DIR_NAME_FORMAT, szTmpDir, pProps[MAILBOX_NAME].Value.LPSZ);
        CreateDirectory (szDownloadDir, NULL);
    }

    hResult = pProfileObj->SetProps (NUM_LOGON_PROPERTIES, pProps, NULL);
    TraceResult ("ServiceEntry: Failed to save the properties back into the profile", hResult);

ErrorExit:
    // Clean up
    if (pProfileObj)
    {
        pProfileObj->Release();
    }
    if (gpfnFreeBuffer)
    {
        gpfnFreeBuffer (pProps);
    }
    if (hUIMutex)
    {
        ReleaseMutex (hUIMutex);
        CloseHandle (hUIMutex);
    }
    // In case the DLL was loaded, unload it.
    // This DLL gets loaded and initialized in the call to DoLogonDlg()
    PrivUninitialize3DCtl (hInstance);
    
    // If we have remote connections going on, close them now
    TerminateRemoteConnections();

    // Close down the traces
    UnInitTraces();
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    DoLogonDlg()
//
//    Parameters
//      pCfgDialog   Pointer to an CFGDLG structure.
//
//    Purpose
//      This functions gets called to display the configuration properties for
//      this transport. When invoked, it will parse the transport logon 
//      property array and initialize the fields in the property sheet with it.
//      The function could also get invoked to display the settings in 
//      READ-ONLY mode in which case we disable writing to the editable fields.
//
//    Return Value
//      An HRESULT
//
HRESULT WINAPI DoLogonDlg (PCFGDLG pCfgDialog)
{
    DWORD dwWait = WaitForSingleObject (pCfgDialog->hUIMutex, 1000); // Wait for the MUTEX for 1 second
    PrivInitialize3DCtl (pCfgDialog->hInst);
    if (WAIT_TIMEOUT == dwWait)
    {
        PrivateMessageBox (IDS_MSG_CONFIG_UI_IN_USE, pCfgDialog->hWnd);
        return MAPI_E_BUSY;
    }

    LPMAPITABLE pTableObj= NULL;
    ULONG ulPropCount;
    SizedSPropTagArray(NUM_LOGON_PROPERTIES, sptCfgProps);
    CopyMemory (&sptCfgProps, &sptLogonProps, sizeof(sptLogonProps));
    sptCfgProps.aulPropTag[UPLOAD_TIME] = PR_TMP_UPLOAD_TIME;
    
    // Take ownership of the property value array, so calling code
    // will not leak memory
    LPSPropValue pProps = *pCfgDialog->ppProps;
    *pCfgDialog->ppProps = NULL;
    
    // Retrieve the dialog title string
    TCHAR szDialogTitle[64], szTimeString[32];
    LoadString (pCfgDialog->hInst, IDS_SERVICE_PROPERTY_SHEETS_TITLE, szDialogTitle, 64);
    CUIMAPIProp * pPropObj = NULL;
    HRESULT hResult = S_OK;
    try
    {
        pPropObj = new CUIMAPIProp (pCfgDialog->hInst,
                                    gpfnAllocateBuffer,
                                    gpfnAllocateMore,
                                    gpfnFreeBuffer,
                                    pCfgDialog->ulFlags & UI_READONLY);
        if (!pPropObj)
        {
            hResult = E_OUTOFMEMORY;
        }
    }
    catch (CException & Exception)
    {
        hResult = Exception.GetError();
    }
    if (hResult)
    {
        goto ErrorExit;
    }

    ASSERT (PR_SMP_UPLOAD_TIME == pProps[UPLOAD_TIME].ulPropTag);
    GetTimeString (szTimeString, pProps[UPLOAD_TIME].Value.ft);
    pProps[UPLOAD_TIME].ulPropTag = PR_TMP_UPLOAD_TIME;
    pProps[UPLOAD_TIME].Value.LPSZ = szTimeString;

    hResult = pPropObj->SetProps (NUM_LOGON_PROPERTIES, pProps, NULL);
    if (hResult)
    {
        TraceResult ("DoLogonDlg: Failed to set the properties", hResult);
        goto ErrorExit;
    }
    DTPAGE DtPropPages[2];
    DtPropPages[0].cctl = NUM_CFG_USERINFO_PAGE_CTLS;   // Count of controls in the ConfigPage array
    DtPropPages[0].lpszComponent = szBlank;
    DtPropPages[0].lpszResourceName = MAKEINTRESOURCE (IDD_CFG_USERINFO);
    DtPropPages[0].lpctl = UserConfigPage;

    DtPropPages[1].cctl = sizeof(XPConfigPage)/sizeof(DTCTL);   // Count of controls in the ConfigPage array
    DtPropPages[1].lpszComponent = szBlank;
    DtPropPages[1].lpszResourceName = MAKEINTRESOURCE (IDD_CFG_XPCONNECT);
    DtPropPages[1].lpctl = XPConfigPage;

    // If the UI_READONLY flag is set, then we are being called from the 
    // SettingDialog method in Read Only mode. Disable all of the controls
    // on the property sheets, else Enable them
    if (pCfgDialog->ulFlags & UI_READONLY)
    {
        // Disable the controls (make them read-only)
        DtPropPages[0].lpctl[1].ulCtlFlags &= ~(DT_EDITABLE | DT_SET_IMMEDIATE);
        DtPropPages[0].lpctl[7].ulCtlFlags &= ~(DT_EDITABLE | DT_SET_IMMEDIATE);
        DtPropPages[1].lpctl[1].ulCtlFlags &= ~DT_EDITABLE;
        DtPropPages[1].lpctl[2].ulCtlFlags &= ~DT_EDITABLE;
    }
    else
    {
        // Enable the controls (make them read/write)
        DtPropPages[0].lpctl[1].ulCtlFlags |= (DT_EDITABLE | DT_SET_IMMEDIATE);
        DtPropPages[0].lpctl[7].ulCtlFlags |= (DT_EDITABLE | DT_SET_IMMEDIATE);
        DtPropPages[1].lpctl[1].ulCtlFlags |= DT_EDITABLE;
        DtPropPages[1].lpctl[2].ulCtlFlags |= DT_EDITABLE;
    }

    // Create the display table for the logon dialog. It is based on dialog
    // resources plus the static information at the head of this module.
    LPTABLEDATA pTableData;
    hResult = BuildDisplayTable (gpfnAllocateBuffer,
                                 gpfnAllocateMore,
                                 gpfnFreeBuffer,
                                 NULL,
                                 pCfgDialog->hInst,
                                 sizeof(DtPropPages)/sizeof(DTPAGE),
                                 DtPropPages,
                                 fMapiUnicode,
                                 &pTableObj,
                                 &pTableData);
    if (!hResult)
    {
        pPropObj->SetTableData (pTableData);
        pTableData->Release();

        // Display the dialog/property sheets
DisplayPropsAgain:
        hResult = pCfgDialog->pSupObj->DoConfigPropsheet ((ULONG)pCfgDialog->hWnd,
                                                          0,
                                                          szDialogTitle,
                                                          pTableObj,
                                                          pPropObj,
                                                          0);     // Default index for the top property sheet
        if (!hResult)
        {
            // Retrieve the altered data
            gpfnFreeBuffer (pProps);
            pProps = NULL;
            hResult = pPropObj->GetProps ((LPSPropTagArray)&sptCfgProps, fMapiUnicode, &ulPropCount, &pProps);
            if (hResult)
            {
                if (MAPI_W_ERRORS_RETURNED == hResult)
                {
                    if (PR_TMP_UPLOAD_TIME != pProps[UPLOAD_TIME].ulPropTag)
                    {
                        pProps[UPLOAD_TIME].ulPropTag = PR_TMP_UPLOAD_TIME;
                        pProps[UPLOAD_TIME].Value.LPSZ = szDefaultTime;
                    }
                    hResult = S_OK;
                }
                else
                {
                    TraceResult ("DoLogonDlg: GetProps failed", hResult);
                    goto ErrorExit;
                }
            }
            // Check the Server name
            if (!IsValidServerName (pProps[SERVER_NAME].Value.LPSZ))
            {
                gpfnFreeBuffer (pProps);
                pProps = NULL;
                PrivateMessageBox (IDS_MSG_INVALID_SERVER_NAME, pCfgDialog->hWnd);
                goto DisplayPropsAgain;
            }

            ASSERT (PR_TMP_UPLOAD_TIME == pProps[UPLOAD_TIME].ulPropTag);
            SYSTEMTIME st;
            GetLocalTime (&st);
            if (ParseTime (pProps[UPLOAD_TIME].Value.LPSZ, &st.wHour, &st.wMinute))
            {
                pProps[UPLOAD_TIME].ulPropTag = PR_SMP_UPLOAD_TIME;
                SystemTimeToFileTime (&st, &pProps[UPLOAD_TIME].Value.ft);
            }
            else
            {
                gpfnFreeBuffer (pProps);
                pProps = NULL;
                PrivateMessageBox (IDS_MSG_BAD_TIME_FORMAT, pCfgDialog->hWnd);
                goto DisplayPropsAgain;
            }

            // Return the new property array
            *pCfgDialog->ppProps = pProps;
            pProps = NULL;      // do not free this in cleanup code below
        }
    }

ErrorExit:
    // Release objects
    if (pTableObj)
    {
        pTableObj->Release();
    }
    if (pPropObj)
    {
        pPropObj->Release();
    }    
    gpfnFreeBuffer (pProps);
    PrivUninitialize3DCtl (pCfgDialog->hInst);
    ReleaseMutex (pCfgDialog->hUIMutex);
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    ParseTime()
//
//    Parameters                        
//      [IN]    pszTime     String in the form HH:MM.
//      [OUT]   pwHour      Hour of day, 0-23
//      [OUT]   pwMinute    Minute of hour, 0-59
//
//    Purpose
//      This function parses the string in pszTime and returns the numbers
//      for the hour and minute of day in a 24 hour clock format.
//      
//    Return Value
//      TRUE on success, FALSE if we failed or the string passed
//      in is invalid.
//      
BOOL WINAPI ParseTime (LPTSTR pszTime, WORD * pwHour, WORD * pwMinute)
{
    TCHAR szTemp[6];
    lstrcpy (szTemp, pszTime);
    LPTSTR pszSubStr = strtok(szTemp, TEXT(":"));
    if (!pszSubStr)
    {
        return FALSE;
    }
    *pwHour = atoi (pszSubStr);
    if (*pwHour < 0 || *pwHour > 23)
    {
        return FALSE;
    }
    pszSubStr = strtok (NULL, TEXT(" "));
    if (!pszSubStr)
    {
        return FALSE;
    }
    *pwMinute = atoi(pszSubStr);
    if (*pwMinute < 0 || *pwMinute > 59)
    {
        return FALSE;
    }
    return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//    GetTimeString()
//
//    Parameters
//      [OUT]   pszTime     Pointer to a buffer where the function copies the
//                          formatted time string. The buffer must have been
//                          allocated by the caller.
//      [IN]    FileTime    FILETIME structure with the time for the string.
//
//    Purpose
//      This function returns a string formatted as "HH:MM"
//      The formatted string is returned in a buffer supplied by the caller
//      of the function.
//      
//    Return Value
//      None.
//
void WINAPI GetTimeString (LPTSTR pszTime, FILETIME FileTime)
{
    // Convert the FILETIME structure to a more readable form
    SYSTEMTIME sysTime;
    FileTimeToSystemTime (&FileTime, &sysTime);
    wsprintf (pszTime, TEXT("%d:%02d"), sysTime.wHour, sysTime.wMinute);
}

///////////////////////////////////////////////////////////////////////////////
//    GetMAPIError()
//
//    Parameters
//      ppMAPIError             Pointer to a location where the newly
//                              allocated MAPIERROR structure is returened. 
//      ulFlags                 Flags for the allocation of the structure
//      hError                  Handle to the error for which a string will
//                              be returned
//      hInstance               Handle to instance of DLL where the resource
//                              strings are located
//
//    Purpose
//      This provider implements a shared function for the two different
//      GetLastError methods in the IMAPIFolder and IMAPIStatus interfaces.
//      These interfaces do not maintain (cached) the last error result, so
//      we trust the client that the hError passed in is indeed the last error.
//      This simplifies implementation of GetLastError, but it will give up
//      giving error strings on the exact context of the actual last error
//      in the case a client passes the wrong hResult.
//      ISV's should weight the benefits and trade-off of this implementation.
//
//    Return Value
//      An HRESULT
//
HRESULT WINAPI GetMAPIError (LPMAPIERROR *          ppMAPIError,
                             ULONG                  ulFlags,
                             HRESULT                hError,
                             HINSTANCE              hInstance)
{
    // The following array maps a string identifier (IDS) to an hResult
    // The order of HRESULTs in the array has an external dependency:
    // the order of elements in the array is dictated by the IDS definitions
    // in RESOURCE.H. This implicit association must be maintained for the 
    // strings associated with string identifiers to make sense. Thus, if 
    // either this structure or the RESOURCE.H defines changes, the other 
    // must change to match it
    static const HRESULT MapOfhResults[] =
    {
        S_OK,

        E_FAIL,
        E_OUTOFMEMORY,
        E_INVALIDARG,
        E_NOINTERFACE,
        E_ACCESSDENIED,

        MAPI_E_BUSY,
        MAPI_E_NO_SUPPORT,
        MAPI_E_NOT_FOUND,
        MAPI_E_UNKNOWN_FLAGS,
        MAPI_E_VERSION,
        MAPI_E_INVALID_ENTRYID,
        MAPI_E_USER_CANCEL,
        MAPI_E_DISK_ERROR,
        MAPI_E_CORRUPT_DATA,
        MAPI_E_BAD_CHARWIDTH,
        MAPI_E_UNCONFIGURED,
        

        CO_E_NOTINITIALIZED,    // This error could only be comming from the server

        MAPI_W_ERRORS_RETURNED
    };

    // Default the a return value in case we don't have the specified error
    // Allocate the memory for the MAPIERROR structure. The caller is
    // responsible for free this
    HRESULT hResult = gpfnAllocateBuffer (sizeof(MAPIERROR), (LPVOID *)ppMAPIError);
    if (hResult)
    {
        TraceResult ("GetMAPIError: Failed to allocate memory for the MAPIERROR structure", hResult);
        return hResult;
    }

    // Zero-out all the members in the structure
    ZeroMemory (*ppMAPIError, sizeof(MAPIERROR));
    (*ppMAPIError)->ulVersion = MAPI_ERROR_VERSION;
    // See if we have the string for the error. If so, make a copy 
    // and pass it back. The memory for the string will be linked to
    // the memory of the structure so that the caller can make a
    // single release on the structure
    
    // Search for the hResult in the HRESULT map
    UINT i, uMaxNum, uStringID;
    uStringID = 0;
    uMaxNum = sizeof (MapOfhResults) / sizeof (HRESULT);
    for (i=0; i<uMaxNum; i++ )
    {
        if (MapOfhResults[i] == hError)
        {
            break;
        }
    }

    if (i == uMaxNum)
    {
        (*ppMAPIError)->ulLowLevelError = LOWORD(hError);
        if (HRESULT_FACILITY(hError) == FACILITY_RPC)
        {
            uStringID = IDS_RPC_ERROR;
        }
        else
        {
            if (HRESULT_FACILITY(hError) == FACILITY_WIN32 ||
                HRESULT_FACILITY(hError) == FACILITY_NULL)
            {
                uStringID = IDS_SYSTEM_ERROR;
            }
            else
            {
                uStringID = IDS_E_UNKNOWN_ERROR;
            }
        }
    }
    else
    {
        uStringID = i + IDS_SUCCESS;
    }
    
    TCHAR szBuffer[512];
    int nCharsRead = LoadString (hInstance, uStringID, szBuffer, sizeof(szBuffer) -1);
    if (!nCharsRead)
    {
        TraceString1 ("GetMAPIError: Could not find error string for ID %d", uStringID);
        hResult = MAPI_E_NOT_FOUND;
    }
    else
    {
        // Allocate memory for return variable and set it.
        // The memory for this string is linked to the memory in the pMemBlock parameter
        hResult = gpfnAllocateMore (Cbtszsize (szBuffer),
                                    *ppMAPIError,
                                    (LPVOID *)&(*ppMAPIError)->lpszError);
        if (!hResult)
        {
            lstrcpy ((*ppMAPIError)->lpszError, szBuffer);
            hResult = gpfnAllocateMore (Cbtszsize (TRANSPORT_DISPLAY_NAME_STRING),
                                        *ppMAPIError,
                                        (LPVOID *)&(*ppMAPIError)->lpszComponent);
            if (!hResult)
            {
                lstrcpy ((*ppMAPIError)->lpszComponent, TRANSPORT_DISPLAY_NAME_STRING);
            }
            else
            {
                TraceResult ("GetMAPIError: Failed to allocate the memory for the component string", hResult);
            }
        }
        else
        {
            TraceResult ("GetMAPIError: Failed to allocate the memory for the error string", hResult);
        }
    }

    if (hResult)
    {
        gpfnFreeBuffer (*ppMAPIError);
        *ppMAPIError = NULL;
    }
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    XPProviderInit()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Entry point called by the MAPI spooler when a profile uses this 
//      transport. The spooler calls this method and expects a pointer to an
//      implementation of the IXPProvider interface. MAPI uses the returned
//      IXPProvider interface pointer to logon on the transport provider
//
//    Return Value
//      An HRESULT
//
STDINITMETHODIMP XPProviderInit (HINSTANCE          hInstance, 
                                 LPMALLOC           pMallocObj,
                                 LPALLOCATEBUFFER   pfnAllocateBuffer,
                                 LPALLOCATEMORE     pfnAllocateMore,
                                 LPFREEBUFFER       pfnFreeBuffer,
                                 ULONG              ulFlags,
                                 ULONG              ulMAPIVer,
                                 ULONG *            pulProviderVer,
                                 LPXPPROVIDER *     ppXPProviderObj)
{
    // Look at TRACES.H and TRACES.CPP for more options to the InitTraces() function
    //InitTraces (0);                                       // Send output only to the COM1 port
    InitTraces (TRACES_CONSOLE | TRACES_NO_COM_OUTPUT);     // Send output to a console window BUT NOT to the COM1
    //InitTraces (TRACES_CONSOLE | TRACES_LOG_FILE);        // Send output to COM1 port AND a console window AND to a log file in C:\MAPILOG.TXT
    InfoTrace ("XPProviderInit function called");
    *pulProviderVer = CURRENT_SPI_VERSION;
    if (ulMAPIVer < CURRENT_SPI_VERSION)
    {
        TraceMessage ("XPProviderInit: The version of the subsystem cannot handle this version of the provider");
        return MAPI_E_VERSION;
    }
    // Save the pointer to the allocation routines in global variables
    gpfnAllocateBuffer = pfnAllocateBuffer;
    gpfnAllocateMore   = pfnAllocateMore;
    gpfnFreeBuffer     = pfnFreeBuffer;
    ghInstance         = hInstance;
    // Allocate a new XPProvider object, the constructor will initialize the data member
    CXPProvider * pXPProvider = new CXPProvider (hInstance);
    if (!pXPProvider)
    {
        TraceMessage ("XPProviderInit: Failed to allocate a new CXPProvider object");
        return E_OUTOFMEMORY;
    }
    // Copy pointer to the allocated object back into the return IXPProvider object pointer
    *ppXPProviderObj = (LPXPPROVIDER)pXPProvider;        
    return S_OK;
}

// End of file for XPSRVCE.CPP
