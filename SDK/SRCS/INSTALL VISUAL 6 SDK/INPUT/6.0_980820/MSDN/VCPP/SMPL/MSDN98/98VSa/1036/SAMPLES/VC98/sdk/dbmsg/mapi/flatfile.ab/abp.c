/***********************************************************************
 *
 *  ABP.C
 *
 *
 *  The Sample Address Book Provider.
 *  This file contains the routines that handle the ABPJump table.
 *
 *  The following routines are implemented in this file:
 *
 *  ABProviderInit
 *  ABP_QueryInterface
 *  ABP_Release
 *  ABP_Shutdown
 *  ABP_Logon
 *
 *  ServiceEntry
 *  HrOpenSingleProvider
 *  
 *  RemoveLogonObject
 *  FindLogonObject
 *  ScLoadString
 *  
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 *
 ***********************************************************************/


#include "abp.h"
#include <smpab.h>


/*
 *  The Local Identifier
 */
LCID lcidUser;

/*
 *  This provider's MAPIUID.  It's used as part of the entryIDs generated from this provider.
 */
MAPIUID muidABSample = MUIDABSAMPLE;

/*
 *  This provider's value for PR_AB_PROVIDER_ID.  It's found in the hierarchy table exposed
 *  by this provider
 */
MAPIUID muidSABProviderID = SAB_PROVIDER_ID;

/*
 *  This provider's Email Type
 */

LPSTR lpszEMT = SZEMAILTYPE;

/*
 *  Used to keep track of all logon objects created on the ABPInit object
 */

typedef struct _object
{
    struct _object *lppNext;
    LPVOID lpObject;

} OBJECTLIST, *LPOBJECTLIST;


/*
 *  structures and filters defined for display tables
 *
 */

DTBLLABEL dtbllabel = {sizeof(DTBLLABEL), 0};
DTBLPAGE dtblpage = {sizeof(DTBLPAGE), 0, 0, 0};
DTBLGROUPBOX dtblgroupbox = {sizeof(DTBLGROUPBOX), 0};
CHAR szNoFilter[] = "*";
CHAR szAddrTypeFilter[] = "[~:]";
CHAR szFileNameFilter[] = "[~   \\\\]"; /* ends up [~<space><tab>\\] */

/*
 *  Prototypes for the functions in this file, most of which I return
 *  in the jump table returned from ABProviderInit().
 */

//ABPROVIDERINIT ABProviderInit;
MSGSERVICEENTRY ServiceEntry;
HRESULT HrOpenSingleProvider(LPPROVIDERADMIN lpAdminProviders,
                             LPPROFSECT FAR * lppProfSect);

/*
 *  Definition of the init object
 */
typedef struct _ABP {
    ABP_Vtbl FAR *      lpVtbl;
    SAB_IUnknown;

    /*
     * list of logon objects 
     */
    LPOBJECTLIST  lpObjectList;   

} ABP, FAR *LPABP;

/*
 *  The ABInit object's vtbl is filled in here
 */
ABP_Vtbl vtblABP =
{
    ABP_QueryInterface,
    (ABP_AddRef_METHOD *) ROOT_AddRef,
    ABP_Release,
    ABP_Shutdown,
    ABP_Logon
};

/*
 -  ABProviderInit
 -
 *  Initializes this provider.  Returns an IABProvider object.
 *
 */

STDINITMETHODIMP
ABProviderInit(
    HINSTANCE hLibrary,
    LPMALLOC lpMalloc,
    LPALLOCATEBUFFER lpAllocBuff,
    LPALLOCATEMORE lpAllocMore,
    LPFREEBUFFER lpFreeBuff,
    ULONG ulFlags,
    ULONG ulMAPIVersion,
    ULONG FAR * lpulABVersion,
    LPABPROVIDER FAR * lppABProvider)
{
    HRESULT hResult = hrSuccess;
    LPABP lpABP;
    SCODE sc;

    /*
     *  Check the version
     */
    if (ulMAPIVersion < CURRENT_SPI_VERSION)
    {
        /*
         *  MAPI's version is too old.
         */

        /*
         *  See if they understand my version
         */
        *lpulABVersion = CURRENT_SPI_VERSION;
        
        DebugTraceSc(ABProviderInit, MAPI_E_VERSION);
        return ResultFromScode(MAPI_E_VERSION);
    }

    /*
     *  Allocate memory for this Init Object
     */
    sc = lpAllocBuff (sizeof(ABP), &lpABP);
    if (FAILED(sc))
    {
        /*
         *  Out of memory
         */
        DebugTraceSc(ABProviderInit, sc);
        return ResultFromScode(sc);
    }

    /*
     *  Initialize the idle engine that MAPI supplies.  This is most useful
     *  when browsing the .SAB file.  See ABCTBLn.C.
     */
    if (MAPIInitIdle(NULL) == -1)
    {
        hResult = ResultFromScode(E_FAIL);
        goto err;
    }

    /*
     *  Hold on to the lpMalloc
     */
    Assert(lpMalloc);
    lpMalloc->lpVtbl->AddRef(lpMalloc);

    lpABP->lpVtbl = &vtblABP;
    lpABP->lcInit = 1;
    lpABP->hLibrary = hLibrary;

    lpABP->lpMalloc = lpMalloc;
    lpABP->lpAllocBuff = lpAllocBuff;
    lpABP->lpAllocMore = lpAllocMore;
    lpABP->lpFreeBuff = lpFreeBuff;
    lpABP->lpObjectList = NULL;

    InitializeCriticalSection(&lpABP->cs);

    *lppABProvider = (LPABPROVIDER) lpABP;
    *lpulABVersion = CURRENT_SPI_VERSION;

    /*
     *  Get our Locale Identifier
     */
    lcidUser = GetUserDefaultLCID();


out:
    DebugTraceResult(ABProviderInit, hResult);
    return hResult;

err:
    lpFreeBuff(lpABP);

    goto out;
}


/*
 -  ABP_QueryInterface
 -
 *  Supports QI'ing to IUnknown and IABProvider
 *  
 *  Note that for all the methods of IABProvider that parameter validation
 *  is unnecessary.  This is because MAPI is handling all the parameters
 *  being passed in.
 *  At best you can assert your parameters.
 */
STDMETHODIMP
ABP_QueryInterface(LPABP lpABP, REFIID lpiid, LPVOID * ppvObj)
{

    /*  See if the requested interface is one of ours */
    if (memcmp(lpiid, &IID_IUnknown, sizeof(IID)) &&
        memcmp(lpiid, &IID_IABProvider, sizeof(IID)))
    {
        *ppvObj = NULL;         /* OLE requires zeroing [out] parameter on error */
        DebugTraceSc(ABP_QueryInterface, E_NOINTERFACE);
        return ResultFromScode(E_NOINTERFACE);
    }

    /*  We'll do this one. Bump the usage count and return a new pointer. */

    EnterCriticalSection(&lpABP->cs);
    ++lpABP->lcInit;
    LeaveCriticalSection(&lpABP->cs);
    
    *ppvObj = lpABP;

    return hrSuccess;
}

/*
 -  ABP_Release
 -
 *  Releases and cleans up this object
 */
STDMETHODIMP_(ULONG)
ABP_Release(LPABP lpABP)
{
    long lcInit;

    EnterCriticalSection(&lpABP->cs);
    lcInit = --lpABP->lcInit;
    LeaveCriticalSection(&lpABP->cs);

    if (lcInit == 0)
    {
        DeleteCriticalSection(&lpABP->cs);

        lpABP->lpVtbl = NULL;
        lpABP->lpFreeBuff(lpABP);
        return (0);
    }
    return lcInit;
}

/*
 -  ABP_Shutdown
 -
 *  Informs this provider that MAPI is done with it.
 *
 *
 */
STDMETHODIMP
ABP_Shutdown(LPABP lpABP, ULONG FAR * lpulFlags)
{
    MAPIDeinitIdle();

    if (lpABP->lpMalloc)
    {
        lpABP->lpMalloc->lpVtbl->Release(lpABP->lpMalloc);
        lpABP->lpMalloc = NULL;
    }

    return hrSuccess;
}

/*
 -  ABP_Logon
 -
 *  Create a logon object and return it to MAPI.
 *
 */

/*
 *  The PropTagArray used to retrieve logon properties
 */
enum {  ivallogonPR_SAB_FILE,
        ivallogonPR_SAB_UID,
        cvallogonMax };

static const SizedSPropTagArray(cvallogonMax, tagaSABLogonProps) =
{
    cvallogonMax,
    {
        PR_SAB_FILE,
        PR_SAB_UID
    }
};

STDMETHODIMP
ABP_Logon(  LPABP             lpABP,
            LPMAPISUP         lpMAPISup,
            ULONG             ulUIParam,
            LPTSTR            lpszProfileName,
            ULONG             ulFlags,
            ULONG FAR *       lpulpcbSecurity,
            LPBYTE FAR *      lppbSecurity,
            LPMAPIERROR FAR * lppMapiError,
            LPABLOGON FAR *   lppABPLogon)
{
    LPABLOGON       lpABLogon       = NULL;
    HRESULT         hResult         = hrSuccess;
    SCODE           scode;
    LPPROFSECT      lpProfSect      = NULL;
    LPSPropValue    lpsPropVal      = NULL;
    ULONG           cValues         = 0;
    LPSTR           lpstrT          = NULL;
    BOOL            fUINeeded;
    BOOL            fNeedMAPIUID    = FALSE;
    MAPIUID         muidID;
    LPOBJECTLIST    lpObjectList;
    CHAR            szFileName[MAX_PATH];

    szFileName[0] = '\0';
    
    *lppMapiError = NULL;
    
    if ( ulFlags & MAPI_UNICODE )
    {
        DebugTraceArg( ABP_Logon, "Bad Character width" );
        return ResultFromScode( MAPI_E_BAD_CHARWIDTH );
    }
    
    /*
     *  Get the name of my browse file from the profile section
     */

    /*  Open the section for my provider */
    hResult = lpMAPISup->lpVtbl->OpenProfileSection(lpMAPISup,
                NULL,
                MAPI_MODIFY,
                &lpProfSect);

    if (HR_FAILED(hResult))
        goto out;

    /*  Get the property containing the browse file name and the sab uid. */
    hResult = lpProfSect->lpVtbl->GetProps(
        lpProfSect,
        (LPSPropTagArray) &tagaSABLogonProps,
        0,      /* ansi */
        &cValues,
        &lpsPropVal);

    if (HR_FAILED(hResult))
        goto out;

#ifdef DEBUG
    if (hResult != hrSuccess)
    {
        if (PROP_TYPE(lpsPropVal[ivallogonPR_SAB_FILE].ulPropTag) == PT_ERROR
            && lpsPropVal[0].Value.err != MAPI_E_NOT_FOUND)
        {
            TraceSz1("ABP_Logon (PR_SAB_FILE) got unexpected scode: %s\n",
                SzDecodeScode(lpsPropVal[ivallogonPR_SAB_FILE].Value.err));
        }
        if (PROP_TYPE(lpsPropVal[ivallogonPR_SAB_UID].ulPropTag) == PT_ERROR
            && lpsPropVal[ivallogonPR_SAB_UID].Value.err != MAPI_E_NOT_FOUND)
        {
            TraceSz1("ABP_Logon (PR_SAB_UID) got unexpected scode: %s\n",
                SzDecodeScode(lpsPropVal[1].Value.err));
        }
    }
#endif

    /*  Ignore warnings from reading the property. */
    hResult = hrSuccess;

    /* copy the sab file name */
    if (lpsPropVal[0].ulPropTag == PR_SAB_FILE)
    {
        UINT cch = lstrlenA(lpsPropVal[0].Value.lpszA);

        if (cch >= MAX_PATH)
            cch = MAX_PATH - 1;

        if (cch)
            memcpy(szFileName, lpsPropVal[0].Value.lpszA, cch);

        szFileName[cch] = '\0';
    }
    else
    {
        DebugTrace("ABP_Logon PR_SAB_FILE not found");
    }

    /* copy the sab uid */
    if (lpsPropVal[1].ulPropTag == PR_SAB_UID)
    {
        memcpy(&muidID, lpsPropVal[1].Value.bin.lpb, sizeof(MAPIUID));
    }
    else
    {
        DebugTrace("ABP_Logon PR_SAB_UID not found");
        fNeedMAPIUID = TRUE;
    }

    /*  Discard GetProps() return data, if any. */
    lpABP->lpFreeBuff(lpsPropVal);

    /*
     *  UI needed unless the file name is good and file exists.
     */

    fUINeeded = TRUE;

    if (szFileName[0] != 0)
    {
        /* Verify the file exists. */

        HANDLE hFile = CreateFile(
            szFileName,
            GENERIC_READ,
            FILE_SHARE_READ,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);

        if (hFile != INVALID_HANDLE_VALUE)
        {
            CloseHandle(hFile);

            fUINeeded = FALSE;
        }
    }

    /*
    *  if the sab file name was not found in the profile or the sab file
    *  does not exist we have to get the user to pick another one and
    *  save back into the profile
    */

    if (fUINeeded)
    {
        OPENFILENAME openfilename;
        SPropValue sProp[1];

        /*
         *  Can't bring up UI unless the client allows it
         */
        if (ulFlags & AB_NO_DIALOG)
        {
            hResult = ResultFromScode(MAPI_E_LOGON_FAILED);
            goto out;
        }

        /*
         *  Get the user to select a file
         */
        openfilename.lStructSize = sizeof(OPENFILENAME);
        openfilename.hwndOwner = (HWND) ulUIParam;
        openfilename.hInstance = 0; /* Ignored */
        openfilename.lpstrFilter = TEXT("Sample AB files\0*.sab\0\0");
        openfilename.lpstrCustomFilter = NULL;
        openfilename.nMaxCustFilter = 0;
        openfilename.nFilterIndex = 0;
        openfilename.lpstrFile = szFileName;
        openfilename.nMaxFile = MAX_PATH;
        openfilename.lpstrFileTitle = NULL;
        openfilename.nMaxFileTitle = 0;
        openfilename.lpstrInitialDir = NULL;
        openfilename.lpstrTitle = TEXT("Sample Address Book");
        openfilename.Flags = OFN_FILEMUSTEXIST |
            OFN_HIDEREADONLY |
            OFN_NOCHANGEDIR;
        openfilename.nFileOffset = 0;
        openfilename.nFileExtension = 0;
        openfilename.lpstrDefExt = TEXT("sab");
        openfilename.lCustData = 0;
        openfilename.lpfnHook = NULL;
        openfilename.lpTemplateName = NULL;

        /*
         *  Call up the common dialog
         */
        if (!GetOpenFileName(&openfilename))
        {
#ifdef DEBUG
            DWORD dwT;

            dwT = CommDlgExtendedError();
#endif /* DEBUG */
            
            hResult = ResultFromScode(MAPI_E_LOGON_FAILED);
            goto out;
        }

        /*
         *  Set the sab file name property value
         */
        sProp[0].ulPropTag = PR_SAB_FILE;
        sProp[0].Value.lpszA = szFileName;

        /*
         *  Save the sab file into the profile
         */
        if (hResult = lpProfSect->lpVtbl->SetProps(lpProfSect, 1, sProp, NULL))
        {
            /*
             *  Do nothing...  So I couldn't save it away this time...
             */
            DebugTraceResult("ABP_Logon got unexpected result on SetProps\n", hResult);
            hResult = hrSuccess;
        }
    }

    /*
    *  if the uid was not found we have to generate a new muid for the
    *  PR_SAB_ID property and save it back into the profile
    */

    if (fNeedMAPIUID)
    {
        SPropValue sProp[1];

        /*
         *  Get a new sab uid
         */
        hResult = lpMAPISup->lpVtbl->NewUID(lpMAPISup, &muidID);
        if (HR_FAILED(hResult))
        {
            goto out;
        }

        /*
         *  Set the sab uid property value
         */
        sProp[0].ulPropTag = PR_SAB_UID;
        sProp[0].Value.bin.cb = sizeof(MAPIUID);
        sProp[0].Value.bin.lpb = (LPBYTE) &muidID;

        /*
         *  Save the sab uid into the profile
         */
        if (hResult = lpProfSect->lpVtbl->SetProps(lpProfSect, 1, sProp, NULL))
        {
            /*
             *  Do nothing...  So I couldn't save it away this time...
             */
            DebugTraceResult("ABP_Logon got unexpected result on SetProps\n", hResult);
            hResult = hrSuccess;
        }
    }

    /*
     *  Allocate space for keeping the file name in the ABLogon object
     */

    if (scode = lpABP->lpAllocBuff(lstrlenA(szFileName)+1, &lpstrT))
    {
        hResult = ResultFromScode(scode);
        goto out;
    }
    lstrcpyA(lpstrT, szFileName);


    hResult = HrNewABLogon(&lpABLogon,
                            (LPABPROVIDER) lpABP,
                            lpMAPISup,
                            lpstrT,
                            &muidID,
                            lpABP->hLibrary,
                            lpABP->lpAllocBuff,
                            lpABP->lpAllocMore,
                            lpABP->lpFreeBuff,
                            lpABP->lpMalloc );
    if (HR_FAILED(hResult))
    {
        goto out;
    }


    /*
     *  Allocate space for another object list item
     */
    scode = lpABP->lpAllocBuff(sizeof(OBJECTLIST), &lpObjectList);
    if (FAILED(scode))
    {
        hResult = ResultFromScode(scode);
        goto out;
    }

    /* Get the Critical Section */
    EnterCriticalSection(&lpABP->cs);

    /* add logon object to begining of providers object list */
    lpObjectList->lpObject = (LPVOID) lpABLogon;
    lpObjectList->lppNext = lpABP->lpObjectList;

    /* insert new logon object into the head of the providers object list */
    lpABP->lpObjectList = lpObjectList;

    /* leave critical section */
    LeaveCriticalSection(&lpABP->cs);

    /*
     *  Register my MAPIUID for this provider,
     *  but do not allow an error from setting the
     *  MAPIUID to cause failure to Logon.
     */

    (void)lpMAPISup->lpVtbl->SetProviderUID(lpMAPISup,
        (LPMAPIUID) &muidABSample, 0);

    *lppABPLogon = lpABLogon;

out:
    if (lpProfSect)
        lpProfSect->lpVtbl->Release(lpProfSect);

    if (hResult)
    {
        lpABP->lpFreeBuff(lpstrT);

        Assert(lpABLogon == NULL);

        /* Verify we don't return warnings at this time. */
        Assert(HR_FAILED(hResult));
    }

    DebugTraceResult(ABP_Logon, hResult);
    return hResult;
}

/*
 *  Removes a particular logon object from the list of logon objects
 *  that's kept track of in the IABProvider object
 */
void
RemoveLogonObject(LPABPROVIDER lpABProvider, LPVOID lpvABLogon, LPFREEBUFFER lpFreeBuff)
{

    LPOBJECTLIST *lppObjectList;
    LPOBJECTLIST lpObjectListT;
    LPABP lpABP = (LPABP) lpABProvider;

#if defined DEBUG
    BOOL fFound = FALSE;

#endif

    /* Get the Critical Section */
    EnterCriticalSection(&lpABP->cs);

    /*
     *  remove this logon object from the provider init objects list
     *  of logon objects
     */
    lppObjectList = &(lpABP->lpObjectList);

    while (*lppObjectList)
    {
        /* is this the logon object? */
        if ((*lppObjectList)->lpObject == lpvABLogon)
        {
            /* save next list item */
            lpObjectListT = (*lppObjectList)->lppNext;

            /* free the object list item */
            lpFreeBuff(*lppObjectList);

            /* delete object from the list */
            *lppObjectList = lpObjectListT;

#if defined DEBUG
            fFound = TRUE;
#endif
            break;
        }

        lppObjectList = &(*lppObjectList)->lppNext;
    }

    /* leave critical section */
    LeaveCriticalSection(&lpABP->cs);

#if defined DEBUG
    AssertSz(fFound, TEXT("Logon object not found on providers object list"));
#endif

    return;
}   


/*
 *  Finds a particular logon object by its muid.
 */
void
FindLogonObject(LPABPROVIDER lpABProvider, LPMAPIUID lpMuidToFind, LPABLOGON * lppABLogon)
{
    LPABP lpABP = (LPABP) lpABProvider;
    LPABLOGON lpABLogonT = NULL;
    LPOBJECTLIST lpObjectList = NULL;
    LPMAPIUID lpMuidLogon = NULL;

    Assert(!IsBadReadPtr(lpABP, sizeof(ABP)));
    Assert(!IsBadReadPtr(lpMuidToFind, sizeof(MAPIUID)));
    Assert(!IsBadReadPtr(lppABLogon, sizeof(LPABLOGON)));

    /* Get the Critical Section */
    EnterCriticalSection(&lpABP->cs);

    *lppABLogon = NULL;

    for (lpObjectList = lpABP->lpObjectList;
        lpObjectList; lpObjectList = lpObjectList->lppNext)
    {
        lpABLogonT = (LPABLOGON) lpObjectList->lpObject;
        
        lpMuidLogon = LpMuidFromLogon(lpABLogonT);

        if (memcmp((LPVOID) lpMuidLogon, (LPVOID) lpMuidToFind, sizeof(MAPIUID)) == 0)
        {
            *lppABLogon = lpABLogonT;
            break;
        }
    }

    /* leave critical section */
    LeaveCriticalSection(&lpABP->cs);
}


/*
 -  ServiceEntry
 -
 *  This funtion is used by MAPI to configure the Sample Address Book.  
 *  It's a lot like ABP_Logon, except that it doesn't return a logon object
 *  and it can be passed in its configuration information (as defined in
 *  smpab.h) from MAPI so that no UI is required.
 *
 */
STDAPI
ServiceEntry(HINSTANCE hInstance,
             LPMALLOC lpMalloc,
             LPMAPISUP lpMAPISup,
             ULONG ulUIParam,
             ULONG ulFlags,
             ULONG ulContext,
             ULONG cValues,
             LPSPropValue lpProps,
             LPPROVIDERADMIN lpAdminProviders,
             LPMAPIERROR FAR *lppMapiError)
{
    OPENFILENAME openfilename;
    char szFileName[MAX_PATH];
    HRESULT hResult = hrSuccess;
    LPSPropValue lpsPropVal = NULL;
    ULONG ulCount = 0;
    LPALLOCATEBUFFER lpAllocBuff;
    LPALLOCATEMORE lpAllocMore;
    LPFREEBUFFER lpFreeBuff;
    LPPROFSECT lpProf = NULL;
    BOOL fUINeeded = FALSE;
    BOOL fNeedMAPIUID = FALSE;
    SPropValue sProp[2];
    ULONG uliProp;
    MAPIUID muid;

    /*  Validate parameters */

    /* check the support object */
    if (IsBadReadPtr(lpMAPISup, sizeof(LPMAPISUP)))
    {
        DebugTraceSc(ServiceEntry, E_INVALIDARG);
        return ResultFromScode(E_INVALIDARG);
    }
    
    if ( ulFlags & MAPI_UNICODE )
    {
        DebugTraceArg( ServiceEntry, "Bad character width" );
        return ResultFromScode( MAPI_E_BAD_CHARWIDTH );
    }
    
    /*
     *  check for context
     */
    if (ulContext == MSG_SERVICE_DELETE || ulContext == MSG_SERVICE_INSTALL
        || ulContext == MSG_SERVICE_UNINSTALL)
        return hrSuccess;
    if (ulContext != MSG_SERVICE_CONFIGURE && ulContext != MSG_SERVICE_CREATE)
    {
        DebugTrace(TEXT("ServiceEntry unsupported context"));
        return ResultFromScode(MAPI_E_NO_SUPPORT);
    }

    /*  Get the memory allocation routines we'll be needing. */
    hResult = lpMAPISup->lpVtbl->GetMemAllocRoutines(lpMAPISup,
        &lpAllocBuff, &lpAllocMore, &lpFreeBuff);
    if (hResult)
    {
        DebugTraceResult(MAPISUP: :GetMemAllocRoutines, hResult);
        goto out;
    }

    /* Open the profile section associated with our provider */
    hResult = HrOpenSingleProvider(lpAdminProviders, &lpProf);
    if (hResult)
    {
        DebugTrace(TEXT("Unable to open the profile."));
        goto out;
    }

    szFileName[0] = '\0';

    /* get sab filename and uid from profile */
    hResult = lpProf->lpVtbl->GetProps(
        lpProf,
        (LPSPropTagArray) &tagaSABLogonProps,
        ulFlags & MAPI_UNICODE,
        &ulCount,
        &lpsPropVal);

    /*  Ignore errors/warnings from reading the property. */
    hResult = hrSuccess;

    /* Look for the .SAB in the config props first */
    for (uliProp = 0; uliProp < cValues; uliProp++)
    {
        if (PROP_ID(lpProps[uliProp].ulPropTag) == PROP_ID(PR_SAB_FILE))
            break;
    }

    if (uliProp < cValues &&
        PROP_TYPE(lpProps[uliProp].ulPropTag) != PT_ERROR)
    {
        ULONG cch = lstrlenA(lpProps[uliProp].Value.lpszA);

        if (cch >= MAX_PATH)
            cch = MAX_PATH - 1;
        if (cch)
            memcpy(szFileName, lpProps[uliProp].Value.lpszA, (size_t) cch);
        szFileName[cch] = '\0';

    }
    else if (lpsPropVal && PROP_ID(lpsPropVal[0].ulPropTag) ==
        PROP_ID(PR_SAB_FILE) &&
        PROP_TYPE(lpsPropVal[0].ulPropTag) != PT_ERROR)
    {
        ULONG cch = lstrlenA(lpsPropVal[0].Value.lpszA);

        if (cch >= MAX_PATH)
            cch = MAX_PATH - 1;
        if (cch)
            memcpy(szFileName, lpsPropVal[0].Value.lpszA, (size_t) cch);
        szFileName[cch] = '\0';
    }
    else
    {
        /* need to ask the user for the sab file */
        fUINeeded = TRUE;
    }

    /* Look for the SAB_UID in the config props first */
    for (uliProp = 0; uliProp < cValues; uliProp++)
    {
        if (PROP_ID(lpProps[uliProp].ulPropTag) == PROP_ID(PR_SAB_UID))
            break;

    }

    if (uliProp < cValues &&
        PROP_TYPE(lpProps[uliProp].ulPropTag) != PT_ERROR)
    {
        memcpy(&muid, lpProps[uliProp].Value.bin.lpb, sizeof(MAPIUID));
    }
    else if (lpsPropVal && PROP_ID(lpsPropVal[1].ulPropTag) ==
        PROP_ID(PR_SAB_UID) && PROP_TYPE(lpsPropVal[1].ulPropTag) != PT_ERROR)
    {
        memcpy(&muid, lpsPropVal[1].Value.bin.lpb, sizeof(MAPIUID));
    }
    else
    {
        /* need to generate a uid */
        fNeedMAPIUID = TRUE;
    }

    /*  Discard GetProps() return data, if any.
     */
    if (lpsPropVal)
        lpFreeBuff(lpsPropVal);

    /*
     *  if the sab file name was not found in the profile we have to
     *  get the user to pick one and save it back into the profile
     */
    if (   fUINeeded
        && !(ulFlags & (SERVICE_UI_ALLOWED | SERVICE_UI_ALWAYS | UI_SERVICE)))
    {
        /*  We need UI to configure but it's not allowed so we can't configure.
         */
        hResult = ResultFromScode(MAPI_E_UNCONFIGURED);

        DebugTrace("SMPAB::ServiceEntry - Missing properties required to configure service.\n");

        goto out;
    }

    if ((fUINeeded) || (ulFlags & UI_SERVICE))
    {
        /*
        *  Get the user to pick a SAB file
        */
        openfilename.lStructSize = sizeof(OPENFILENAME);
        openfilename.hwndOwner = (HWND) ulUIParam;
        openfilename.hInstance = 0; /* Ignored */
        openfilename.lpstrFilter = "Sample AB files\0*.sab\0\0";
        openfilename.lpstrCustomFilter = NULL;
        openfilename.nMaxCustFilter = 0;
        openfilename.nFilterIndex = 0;
        openfilename.lpstrFile = szFileName;
        openfilename.nMaxFile = MAX_PATH;
        openfilename.lpstrFileTitle = NULL;
        openfilename.nMaxFileTitle = 0;
        openfilename.lpstrInitialDir = NULL;
        openfilename.lpstrTitle = "Pick a Sample Address Book file";
        openfilename.Flags = OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR | OFN_HIDEREADONLY;
        openfilename.nFileOffset = 0;
        openfilename.nFileExtension = 0;
        openfilename.lpstrDefExt = "sab";
        openfilename.lCustData = 0;
        openfilename.lpfnHook = NULL;
        openfilename.lpTemplateName = NULL;

        /*
        *  Call up the common dialog
        */
        if (!GetOpenFileName(&openfilename))
        {
            /* user pressed cancel */
            goto out;
        }
    }

    /*
    *  if the uid was not found we have to generate a new muid for the
    *  PR_SAB_ID property and save it back into the profile
    */

    if (fNeedMAPIUID)
    {
        hResult = lpMAPISup->lpVtbl->NewUID(lpMAPISup, &muid);
        if (HR_FAILED(hResult))
        {
            /*
            *  Can't get a uid so just leave
            */
            goto out;
        }
    }

    /*
    *  Set the file name property
    */

    sProp[ivallogonPR_SAB_FILE].ulPropTag = PR_SAB_FILE;
    sProp[ivallogonPR_SAB_FILE].Value.lpszA = szFileName;

    /*
    *  Set the id property
    */

    sProp[ivallogonPR_SAB_UID].ulPropTag = PR_SAB_UID;
    sProp[ivallogonPR_SAB_UID].Value.bin.cb = sizeof(MAPIUID);
    sProp[ivallogonPR_SAB_UID].Value.bin.lpb = (LPBYTE) &muid;

    /*
    *  Save the sab file and the uid back into the profile
    */
    hResult = lpProf->lpVtbl->SetProps(
        lpProf,
        sizeof(sProp) / sizeof(SPropValue),
        sProp,
        NULL);

    if (HR_FAILED(hResult))
    {
        /*
        *  Do nothing...  So I couldn't save it away this time...
        */
        DebugTrace(TEXT("ServiceEntry could not SetProp in profile"));
        hResult = hrSuccess;
    }

out:
    if (lpProf)
        lpProf->lpVtbl->Release(lpProf);

    DebugTraceResult(ServiceEntry, hResult);
    return hResult;
}

/*
 -  HrOpenSingleProvider
 -
 *  Opens the profile section associated with this provider.
 *
 *  If the ServiceEntry() function exported from a provider had
 *  more than 1 section associated with it, this is where you'd get the chance
 *  to get all of them.
 */

static SizedSPropTagArray(1, tagaProviderTable) =
{
    1,
    {
        PR_PROVIDER_UID
    }
};

HRESULT
HrOpenSingleProvider(LPPROVIDERADMIN lpAdminProviders,
                     LPPROFSECT FAR * lppProfSect)
{
    HRESULT hResult;
    LPMAPITABLE lpTable = NULL;
    LPSRowSet lpRows = NULL;
    LPSPropValue lpProp;

    hResult = lpAdminProviders->lpVtbl->GetProviderTable(
        lpAdminProviders,
        0,
        &lpTable);
    if (HR_FAILED(hResult))
        goto out;

    hResult = lpTable->lpVtbl->SetColumns(lpTable, (LPSPropTagArray) &tagaProviderTable, 0);
    if (HR_FAILED(hResult))
        goto out;

    hResult = lpTable->lpVtbl->QueryRows(lpTable, 1, 0, &lpRows);
    if (HR_FAILED(hResult))
        goto out;

    if (lpRows->cRows == 0)
    {
        hResult = ResultFromScode(MAPI_E_NOT_FOUND);
        goto out;
    }

    lpProp = lpRows->aRow[0].lpProps;

    hResult = lpAdminProviders->lpVtbl->OpenProfileSection(
                lpAdminProviders,
                (LPMAPIUID) lpProp->Value.bin.lpb,
                NULL,
                MAPI_MODIFY,
                lppProfSect);

out:
    FreeProws(lpRows);

    if (lpTable)
        lpTable->lpVtbl->Release(lpTable);

    DebugTraceResult(HrOpenSingleProvider, hResult);
    return hResult;
}



/*
 -  ScLoadString
 -
 *  Loads a string from a resource.  It will optionally allocate the string if
 *  a allocation function is passed in.  Otherwise it assumes that the *lppsz
 *  is already allocated.
 */

SCODE ScLoadString( UINT                ids,
                    ULONG               ulcch,
                    LPALLOCATEBUFFER    lpAllocBuff,
                    HINSTANCE           hLibrary,
                    LPSTR *             lppsz)
{
    SCODE sc = S_OK;
    int iRet;

    /*
     *  Assert parameters
     */
    Assert((lpAllocBuff ? !IsBadCodePtr((FARPROC) lpAllocBuff):TRUE));
    Assert(ids!=0);

    if (lpAllocBuff)
    {
        sc = lpAllocBuff(ulcch, lppsz);
        if (FAILED(sc))
        {
            goto out;
        }
    }
#ifdef DEBUG
    else
    {
        Assert(!IsBadWritePtr(*lppsz, (UINT) ulcch));
    }
#endif /* DEBUG */
    
    iRet = LoadStringA( hLibrary,
                        ids,
                        *lppsz,
                        (UINT) ulcch);

    if (!iRet)
    {
        DebugTrace("LoadString() failed...\n");
        sc = E_FAIL;
        goto out;
    }
out:

    DebugTraceSc(ScLoadString, sc);
    return sc;
}


