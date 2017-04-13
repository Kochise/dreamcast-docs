/*
 *  M S P L O G O N . C
 *
 *  Logon to a MAPI Sample Message Store.
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 */

#include "msp.h"
#include "msprc.h"
#include <stddef.h>

#include "..\common\wrap3d.h"

#define MSL_CheckParameters(pobj, intf, method, arglist)        \
        OBJ_CheckParameters(pobj, intf, method, sizeof(MSL), &vtblMSL, arglist)
#define MSP_CheckParameters(pobj, intf, method, arglist)        \
        OBJ_CheckParameters(pobj, intf, method, sizeof(MSP), &vtblMSP, arglist)

#ifndef MB_SETFOREGROUND
#define MB_SETFOREGROUND 0
#endif

#define MSL_EnterCriticalSection(pmsl)  OBJ_EnterCriticalSection((POBJ)pmsl)
#define MSL_LeaveCriticalSection(pmsl)  OBJ_LeaveCriticalSection((POBJ)pmsl)

MSL_Vtbl vtblMSL =
{
    (MSL_QueryInterface_METHOD *)       OBJ_QueryInterface,
    (MSL_AddRef_METHOD *)               OBJ_AddRef,
    MSL_Release,
    (MSL_GetLastError_METHOD *)         IMS_GetLastError,
    MSL_Logoff,
    (MSL_OpenEntry_METHOD *)            IMS_OpenEntry,
    (MSL_CompareEntryIDs_METHOD *)      IMS_CompareEntryIDs,
    (MSL_Advise_METHOD *)               IMS_Advise,
    (MSL_Unadvise_METHOD *)             IMS_Unadvise,
    MSL_OpenStatusEntry
};

MAPIUID uidProvider = SMPMS_UID_PROVIDER;

/* Manifest constants */

#define ACCTSIZE    16          /* Our choice for maximum password length. */

static SPropTagArray sptaPass =
{
    1, {PR_SMS_PASSWORD}
};

TCHAR szPropFileName[] = TEXT("msgstore.prp");
TCHAR szFolderFileName[] = TEXT("recfldr.stg");
TCHAR szProviderDisplayName[] = TEXT("Sample Message Store");
TCHAR szDisplayPrefix[] = TEXT("Sample store at ");

/* property tags needed for service creation or configuration */
static  SizedSPropTagArray(4,ptaConfig) = {4, { PR_SMS_PATH,
                                            PR_SMS_PASSWORD,
                                            PR_SMS_REMEMBER_PW,
                                            PR_SMS_CREATE } };

/* property tags that should be removed from the profile after */
/* service creation or configuration */
static  SizedSPropTagArray(2,ptaDel)= {2, { PR_SMS_REMEMBER_PW,
                                            PR_SMS_CREATE } };

/* service parameter block */
typedef struct _ServicePBLK
{
    PMSP            pmsp;
    LPPROFSECT      pps;
    LPMAPISUP       psup;
    ULONG           ulUIParam;
    ULONG           ulContext;
    ULONG           ulSEFlags;
    ULONG           cvalsProf;
    LPSPropValue    pvalsProf;
    ULONG           cvalsClient;
    LPSPropValue    pvalsClient;
} SERVICEPBLK, FAR * PSERVICEPBLK;


#define LGNCRED_PATH        ((ULONG) 0x00000001)
#define LGNCRED_PASS        ((ULONG) 0x00000002)
#define LGNCRED_CREATE      ((ULONG) 0x00000004)
#define LGNCRED_REMEMBER    ((ULONG) 0x00000008)

/* Typedefs */

typedef struct _LGNCRED
{
    ULONG ulFieldMask;
    TCHAR szPath[MAX_PATH];
    TCHAR szPass[ACCTSIZE];
    BOOL fCreate;
    BOOL fRemember;
    BOOL fCancel;
    LPVOID lpCtl3d;
} LGNCRED, * PLGNCRED;

typedef struct _DLGPSWD
{
    TCHAR szPath[MAX_PATH];
    TCHAR szPass[ACCTSIZE];
    LPMAPISUP psup;
    PLMR plmr;
    BOOL fRemember;
    BOOL fCancel;
    LPVOID lpCtl3d;
} DLGPSWD, * PDLGPSWD;

/* Internal function prototypes */

static HRESULT HrOpenSingleProvider(LPPROVIDERADMIN padp,
    LPPROFSECT FAR *lppProfSect);
static SCODE ScCreateOrConfigure(PSERVICEPBLK pspb);
static SCODE ScCreateStore(PSERVICEPBLK pspb, LPTSTR szPath,
    LPTSTR szPass, PMSL * ppmsl, PIMS * ppims);
static BOOL FAlreadyOpenStore(PMSP pmsp, LPTSTR szPath, PIMS * ppims);

static HRESULT HrGetLogonDlgCred(HINSTANCE hInst, ULONG ulUIParam, LPTSTR szPath,
    LPTSTR szPass, BOOL *pfCreate, BOOL *pfRemember);
STDAPI_(BOOL) LogonDlgProc(HWND hDlg, UINT message, WPARAM wParam,
    LPARAM lParam);
static HRESULT HrGetPassword(HINSTANCE hInst, LPMAPISUP psup, PLMR plmr,
    ULONG ulUIParam, LPTSTR szPath, LPTSTR szPass, BOOL *pfRemember);
STDAPI_(BOOL) PasswordDlgProc(HWND hDlg, UINT message, WPARAM wParam,
    LPARAM lParam);
static HRESULT HrGetProfileCred(PLMR plmr, LPPROFSECT pps, LPTSTR szPass,
    BOOL *pfFound);
static HRESULT HrSetProfileCred(LPPROFSECT pps, LPTSTR szPass, LPTSTR szPath,
    BOOL fRemember, ULONG cbEntryID, LPBYTE lpEntryID, LPMAPIUID puidRK);
static HRESULT HrConfirmCred(LPTSTR szPath, LPTSTR szPass, LPMAPISUP psup,
    PLMR plmr);
static HRESULT HrFilePathExists(LPTSTR szStorePath, LPTSTR szFileName);
static HRESULT HrCheckStoreIntegrity(LPTSTR szPath);
static BOOL FIsValidPath(LPTSTR szPath, BOOL fCreate);
static void DecodeSpoolSecurity(ULONG cbSpoolSecurity, LPBYTE pbSpoolSecurity,
    LPTSTR szPath, LPTSTR szPass);
static HRESULT HrGetSpoolSecurity(LPTSTR szPath, LPTSTR szPass,
    PLMR plmr, ULONG * lpcbSpoolSecurity, LPBYTE * lppbSpoolSecurity);
static HRESULT HrCheckAndOpenStore(PMSP pmsp, LPMAPISUP psup, BOOL fModify,
    LPPROFSECT pps, LPTSTR szPath, LPTSTR szPass, BOOL fIsSpooler,
    PMSL *ppmsl, PIMS *ppims);
static SCODE ScCreateMSL(PMSP pmsp, PMSL * ppmsl);
static BOOL FFindPropInPSPB(PSERVICEPBLK pspb, ULONG ulPT, LPSPropValue *ppval);
static SCODE ScGetFullFileName(PSERVICEPBLK pspb, BOOL *pfCreate,
    LPSTR pszPath);

/*
 *  MSP_Logon
 *
 *  Purpose:
 *      Logs in one user to the message store and returns a logon object
 *      and a message store object.  Gets credentials through the
 *      profile or a dialog.  Prompts if more information is needed.
 *
 *  Arguments:
 *      pmsp                MSPROVIDER object returned at INIT time.
 *      psup                Pointer to MAPI Support object.
 *      ulUIParam           Handle to parent window cast to a ULONG.
 *      szProfileName       String with the name of profile.
 *                          (UNICODE if MAPI_UNICODE flag set in ulFlags)
 *      cbEntryID           Size of lpEntryID.
 *      lpEntryID           Provider component of store resource EntryID.
 *      ulFlags             Flags for access methods:
 *                          MDB_WRITE           Write access.
 *                          MAPI_BEST_ACCESS    Write access if possible.
 *                          MDB_NO_DIALOG       No logon dialog.
 *                          MAPI_UNICODE        If szProfileName UNICODE
 *      piid                Identifies what interface is desired on the
 *                          about-to-be-opened object.
 *      lpcbSpoolSecurity   Address of the variable in which the
 *                          provider returns size of *lppbSpoolSecurity.
 *      lppbSpoolSecurity   Address to return validation data
 *                          necessary for SpoolerLogon to
 *                          piggyback off this logon session.
 *      lpulLowLevelError   Possible low level error to return if
 *                          error or MAPI_W_EXTENDED_WARNING is returned.
 *      pszMessage          Error / Warning string on logon.  If MAPI_UNICODE
 *                          is set in ulFlags then it is UNICODE.
 *      ppmslogon           Address to return a pointer to MSLOGON
 *                          object for use by MAPI.DLL.
 *      ppmdb               Address of a pointer to the message
 *                          store object for use by the client.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      May put up logon screen to select/open store if
 *      MDB_NO_DIALOG is not set.  For store creation, Logon
 *      creates "hidden" files for MDB management.
 *
 *  Errors:
 *      MAPI_E_NOT_ENOUGH_MEMORY    Could not allocate memory.
 *      MAPI_E_CALL_FAILED          Failure creating a new store.
 *      MAPI_E_CALL_FAILED          Windowing system failure trying
 *                                  to display logon UI.
 *      MAPI_E_CORRUPT_STORE        One of the necessary store
 *                                  files is missing.
 *      MAPI_E_LOGON_FAILED         Insufficient or bad credentials.
 */
STDMETHODIMP
MSP_Logon(PMSP pmsp, LPMAPISUP psup, ULONG ulUIParam, LPSTR szProfileName,
    ULONG cbEntryID, LPENTRYID lpEntryID, ULONG ulFlags, LPCIID piid,
    ULONG * lpcbSpoolSecurity, LPBYTE * lppbSpoolSecurity,
    LPMAPIERROR * lppMapiError, LPMSLOGON * ppmslogon, LPMDB * ppmdb)
{
    HRESULT hr = hrSuccess;
    HRESULT hrT;
    BOOL fRemember = FALSE;     /* Remember password in profile? */
    BOOL fFoundPassword;        /* TRUE if the password was in the profile */
    PIMS pims = NULL;           /* Internal IMsgStore implementation */
    PMSL pmsl = NULL;           /* logon object to give to MAPI */
    TCHAR szPath[MAX_PATH];     /* Path to store root */
    TCHAR szPass[ACCTSIZE];     /* Store account password */
    PEID peid = (PEID) lpEntryID;
    LPPROFSECT pps = NULL;      /* our profile section */

    MSP_CheckParameters(
            pmsp, 
            IMSProvider,
            Logon,
            (pmsp, 
            psup, 
            ulUIParam, 
            szProfileName, 
            cbEntryID, 
            lpEntryID, 
            ulFlags, 
            piid, 
            lpcbSpoolSecurity, 
            lppbSpoolSecurity, 
            lppMapiError,
            ppmslogon, 
            ppmdb));

    #ifdef VALIDATE
    if (ulFlags & MAPI_UNICODE)
        return ResultFromScode(MAPI_E_BAD_CHARWIDTH);
    #endif

    MSP_EnterCriticalSection(pmsp);

    AssertSz(!pmsp->fInvalid, "This MSProvider has already been shutdown");

    *lpcbSpoolSecurity = 0L;
    *lppbSpoolSecurity = NULL;
    *lppMapiError = NULL;
    *ppmslogon = NULL;
    *ppmdb = NULL;

    if (piid && !FQueryInterface(OT_MSGSTORE, piid))
    {
        hr = ResultFromScode(E_NOINTERFACE);
        goto exit;
    }

    hr = psup->lpVtbl->OpenProfileSection(psup, NULL, MAPI_MODIFY, &pps);
    if (hr != hrSuccess)
        goto exit;

    /* Get the full path to the store out of the EntryID */

    if (peid == NULL)
    {
        hr = ResultFromScode(MAPI_E_UNCONFIGURED);
        goto exit;
    }
    else if (FIsInvalidEID(cbEntryID, peid, NULL))
    {
        hr = ResultFromScode(MAPI_E_INVALID_PARAMETER);
        goto exit;
    }

    lstrcpy(szPath, peid->szPath);

    DebugTrace("\nSMS: MSP_Logon %s\n\n", szPath);
    
    /* If we can piggyback on an existing open message store on this */
    /* session then do so. If we piggyback, then don't return a logon */
    /* object or addref the support object. */

    if (FAlreadyOpenStore(pmsp, szPath, &pims))
    {
        DebugTrace("\nSMS: Piggybacking client logon\n");
        Assert(hr == hrSuccess);
        goto exit;
    }

    /* Get store credentials from profile. */

    hr = HrGetProfileCred(&pmsp->lmr, pps, szPass, &fFoundPassword);
    if (hr != hrSuccess)
        goto exit;

    /* If the password was in the profile, then the user wanted us to */
    /* remember it (that's the only way it would be in the profile). */

    if (fFoundPassword)
        fRemember = TRUE;

    while (TRUE)
    {
        SCODE sc;

        hr = HrCheckAndOpenStore(pmsp, psup,
            !!(ulFlags & (MDB_WRITE | MAPI_BEST_ACCESS)), pps, szPath,
            szPass, FALSE, &pmsl, &pims);
        if (hr == hrSuccess)
            break;

        sc = GetScode(hr);

        /* Preset hr to the value that will cause MAPI to bring up our */
        /* config UI */

        hr = ResultFromScode(MAPI_E_UNCONFIGURED);

        if (!(ulFlags & MDB_NO_DIALOG))
        {
            if (sc == MAPI_E_LOGON_FAILED)
            {
                hr = HrGetPassword(pmsp->hInst, psup, &pmsp->lmr, ulUIParam,
                    szPath, szPass, &fRemember);
            }
            else if (sc == MAPI_E_NOT_FOUND)
            {
                MessageBox(NULL, "The path to the message store is invalid.",
                    "Sample Message Store",
                    MB_OK | MB_TASKMODAL | MB_SETFOREGROUND);
            }
        }

        if (hr != hrSuccess)
            goto exit;
    }

    /* Complete regular logon tasks. */

    /* Update saved credentials if they have changed. */

    hrT = HrSetProfileCred(pps, szPass, szPath, fRemember, 
        pims->eidStore.cb, pims->eidStore.lpb, &pims->uidResource);

    if (hrT == hrSuccess)
        hrT = pps->lpVtbl->SaveChanges(pps, 0);

    /* Make the profile section permanent. */
    if (hrT == hrSuccess)
        hrT = psup->lpVtbl->ModifyProfile(psup, 0);

    hr = psup->lpVtbl->SetProviderUID(psup, &pims->uidResource, 0L);
    if (hr != hrSuccess)
        goto exit;

    hr = HrSetupPrivateNotifications(pims);
    if (hr != hrSuccess)
        goto exit;

    /* This call sets [out] parameters, and should therefore be the last */
    /* call that could fail. */
    hr = HrGetSpoolSecurity(szPath, szPass, &pims->lmr,
        lpcbSpoolSecurity, lppbSpoolSecurity);

    if (hr != hrSuccess)
        goto exit;

    /* Add this new store to the list of open stores. */
    OBJ_Enqueue((POBJ) pims, (POBJ) pmsp);

    UlAddRef(psup);         /* I'm keeping a reference */

    Assert(hr == hrSuccess);    /* no error */

exit:
    if (hr == hrSuccess)
    {
        /* Fill in [out] parameters. */
        *ppmdb = (LPMDB) pims;
        *ppmslogon = (LPMSLOGON) pmsl;
    }
    else
    {
        UlRelease(pims);

        /* Releasing the pmsl must come after releasing the pims. */
        UlRelease(pmsl);

        Assert(*lpcbSpoolSecurity == 0L);
        Assert(*lppbSpoolSecurity == NULL);
        Assert(*lppMapiError == NULL);
        Assert(*ppmslogon == NULL);
        Assert(*ppmdb == NULL);
    }

    UlRelease(pps);

    MSP_LeaveCriticalSection(pmsp);

    DebugTraceResult(MSP_Logon, hr);
    return HrCheckHr(hr, IMSProvider_Logon);
}

/*
 *  MSP_SpoolerLogon
 *
 *  Purpose:
 *      Logs in the Spooler to this message store.
 *
 *  Arguments:
 *      psup            Pointer to MAPI Support object.
 *      ulUIParam           HWND of parent window
 *      szProfileName       Name of profile
 *      cbEntryID           Size of lpEntryID.
 *      lpEntryID           Provider component of store resource
 *                          EntryID.
 *      ulFlags             Flags.  See Logon above, except
 *                          MDB_NO_DIALOG is normally (always?)
 *                          set on this call.
 *      piid                IID of desired interface for ppmdb
 *      cbSpoolSecurity     Size of data in lpbSpoolSecurity.
 *      lpbSpoolSecurity    Validation data necessary for
 *                          SpoolerLogon to complete.
 *      lpulLowLevelError   Possible low level error to return if
 *                          error or MAPI_W_EXTENDED_WARNING is returned.
 *      pszMessage          Error / Warning string on logon.  If MAPI_UNICODE
 *                          is set in ulFlags then it is UNICODE.
 *      ppmslogon           Address to return a pointer to MSLOGON
 *                          object for use by MAPI.DLL.
 *      ppmdb               Address of a pointer to the Spooler
 *                          Message Store Object.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      May put up logon screen to select/open store if
 *      MDB_NO_DIALOG is not set.  Calls HrNewIMS to create the
 *      message store object, which allocates memory.
 *
 *  Errors:
 *      MAPI_E_NO_MEMORY        Could not allocate memory.
 *      MAPI_E_LOGON_FAILED     Bad credentials
 */
STDMETHODIMP
MSP_SpoolerLogon(PMSP pmsp, LPMAPISUP psup, ULONG ulUIParam,
    LPTSTR szProfileName, ULONG cbEntryID, LPENTRYID lpEntryID,
    ULONG ulFlags, LPCIID piid, ULONG cbSpoolSecurity,
    LPBYTE lpbSpoolSecurity, LPMAPIERROR * lppMapiError,
    LPMSLOGON * ppmslogon, LPMDB * ppmdb)
{
    TCHAR szPass[ACCTSIZE];     /* Store account password */
    TCHAR szPath[MAX_PATH];     /* path to store root */
    HRESULT hr = hrSuccess;
    PIMS pims = NULL;
    PMSL pmsl = NULL;
    LPPROFSECT pps = NULL;      /* our profile section */

    MSP_CheckParameters(
            pmsp, 
            IMSProvider,
            SpoolerLogon,
            (pmsp, 
            psup, 
            ulUIParam, 
            szProfileName, 
            cbEntryID, 
            lpEntryID, 
            ulFlags, 
            piid, 
            cbSpoolSecurity, 
            lpbSpoolSecurity, 
            lppMapiError, 
            ppmslogon, 
            ppmdb));

    #ifdef VALIDATE
    if (ulFlags & MAPI_UNICODE)
        return ResultFromScode(MAPI_E_BAD_CHARWIDTH);
    #endif
        
    MSP_EnterCriticalSection(pmsp);

    AssertSz(!pmsp->fInvalid, "This MSProvider has already been shutdown");

    *lppMapiError = NULL;
    *ppmslogon = NULL;
    *ppmdb = NULL;

    if (piid && !FQueryInterface(OT_MSGSTORE, piid))
    {
        hr = ResultFromScode(MAPI_E_INTERFACE_NOT_SUPPORTED);
        goto exit;
    }

    hr = psup->lpVtbl->OpenProfileSection(psup, NULL, MAPI_MODIFY, &pps);
    if (hr != hrSuccess)
        goto exit;

    DecodeSpoolSecurity(cbSpoolSecurity, lpbSpoolSecurity, szPath, szPass);

    DebugTrace("\nSMS: MSP_SpoolerLogon %s\n\n",szPath);

    /* If we can piggyback on an existing open message store */
    /* on this session then do so. If we piggyback, then don't return */
    /* a logon object or addref the support object. */

    if (FAlreadyOpenStore(pmsp, szPath, &pims))
    {
        DebugTrace("\nSMS: Piggybacking spooler logon\n");
        goto exit;
    }


    hr = HrCheckAndOpenStore(pmsp, psup, TRUE, pps, szPath, szPass, TRUE,
        &pmsl, &pims);
    if (hr == hrSuccess)
        hr = psup->lpVtbl->SetProviderUID(psup, &pims->uidResource, 0L);
    if (hr == hrSuccess)
        hr = HrSetupPrivateNotifications(pims);

    if (hr == hrSuccess)
    {
        /* Add this new store to the list of open stores. */
        OBJ_Enqueue((POBJ) pims, (POBJ) pmsp);
        UlAddRef(psup);
    }

exit:
    if (hr == hrSuccess)
    {
        *ppmdb = (LPMDB) pims;
        *ppmslogon = (LPMSLOGON) pmsl;
    }

    UlRelease(pps);

    MSP_LeaveCriticalSection(pmsp);

    DebugTraceResult(MSP_SpoolerLogon, hr);
    return hr;
}

/*
 -  MSL_Release
 -
 */

STDMETHODIMP_(ULONG) MSL_Release(PMSL pmsl)
{
    LONG cRef;

    MSL_EnterCriticalSection(pmsl);

    AssertSz1(pmsl->cRef > 0, "MSL_Release(): Bogus cRef (%08lX)", pmsl->cRef);

    cRef = --pmsl->cRef;

    MSL_LeaveCriticalSection(pmsl);

    if (cRef == 0)
    {
        Assert(pmsl->pims == NULL);
        DeleteCriticalSection(&pmsl->cs);
        LMFree(&pmsl->lmr, pmsl);
    }

    return (cRef);
}

/*
 *  MSL_Logoff()
 */

STDMETHODIMP MSL_Logoff(PMSL pmsl, ULONG * pulFlags)
{
    MSL_CheckParameters(
            pmsl, 
            IMSLogon,
            Logoff,
            (pmsl,
            pulFlags));

    MSL_EnterCriticalSection(pmsl);

    AssertSz(!pmsl->fInvalid, "Logon object already logged off");

    if (pmsl->pims)
        OBJ_Destroy((POBJ) pmsl->pims);
    else
        MSL_LeaveCriticalSection(pmsl);

#ifdef DEBUG
    pmsl->fInvalid = TRUE;
#endif

    return (hrSuccess);
}

/*
 *  MSL_OpenStatusEntry()
 *
 *  MAPI has determined that the client call to OpenStatusEntry
 *  is for OUR row in the status table.  Open the Status Object
 *  appropriate for our store.
 *
 *  This object is logically part of the store, and can be made
 *  invalid when the store (either the MSLogon or LPMDB object,
 *  at our choice) goes away.
 */

STDMETHODIMP MSL_OpenStatusEntry(PMSL pmsl, LPCIID lpiid, ULONG ulFlags,
    ULONG * lpulObjType, LPVOID * lppEntry)
{
    MSL_CheckParameters(
    pmsl, 
    IMSLogon,
    OpenStatusEntry,
    (pmsl, 
    lpiid, 
    ulFlags, 
    lpulObjType, 
    lppEntry));

    AssertSz(!pmsl->fInvalid, "Logon object already logged off");

    DebugTraceSc(MSL_OpenStatusEntry, MAPI_E_NO_SUPPORT);
    return ResultFromScode(MAPI_E_NO_SUPPORT);
}

STDAPI SMSServiceEntry(HINSTANCE hInst, LPMALLOC lpMalloc, LPMAPISUP psup,
        ULONG ulUIParam, ULONG ulSEFlags, ULONG ulContext, ULONG cvals,
        LPSPropValue pvals, LPPROVIDERADMIN lpAdminProviders,
        LPMAPIERROR FAR *lppMapiError)
{
    HRESULT             hr;
    LPALLOCATEBUFFER    lpAllocBuff;
    LPALLOCATEMORE      lpAllocMore;
    LPFREEBUFFER        lpFreeBuff      = NULL;
    PMSP                pmsp            = NULL;
    LPPROFSECT          pps             = NULL;
    SERVICEPBLK         spb;
    ULONG               ulProvVer;
    ULONG               cvalsProf;
    LPSPropValue        pvalsProf       = NULL;

    /* check the array of profile section objects */
    if (IsBadReadPtr(psup, sizeof(LPMAPISUP))
        ||  (cvals && IsBadReadPtr(pvals, (UINT)(sizeof(SPropValue) * cvals))))
        return ResultFromScode(MAPI_E_INVALID_PARAMETER);

    if (ulSEFlags & ~(MAPI_UNICODE
                    | MSG_SERVICE_UI_READ_ONLY
                    | SERVICE_UI_ALWAYS     /* Same value as UI_SERVICE */
                    | SERVICE_UI_ALLOWED    /* New */
                    | UI_CURRENT_PROVIDER_FIRST
                    | SERVICE_LOGON_FAILED))
        return ResultFromScode(MAPI_E_UNKNOWN_FLAGS);

    if (ulSEFlags & MAPI_UNICODE)
        return ResultFromScode(MAPI_E_BAD_CHARWIDTH);

    if (    (ulContext == MSG_SERVICE_INSTALL)
        ||  (ulContext == MSG_SERVICE_UNINSTALL)
        ||  (ulContext == MSG_SERVICE_DELETE))
        return (hrSuccess);

    if (ulContext != MSG_SERVICE_CONFIGURE && ulContext != MSG_SERVICE_CREATE)
        return (ResultFromScode(MAPI_E_NO_SUPPORT));

    /* get the profile section for the provider */
    hr = HrOpenSingleProvider(lpAdminProviders, &pps);
    if (hr != hrSuccess)
        goto err;

    /*  Get the memory allocation routines we'll be needing. */
    hr = psup->lpVtbl->GetMemAllocRoutines(psup, &lpAllocBuff, &lpAllocMore,
            &lpFreeBuff);
    if (hr != hrSuccess)
        goto err;

    hr = MSProviderInit(hInst, lpMalloc, lpAllocBuff, lpAllocMore,
            lpFreeBuff, 0, CURRENT_SPI_VERSION, &ulProvVer,
            &(LPMSPROVIDER)pmsp);
    if (hr != hrSuccess)
        goto err;

    /* get the properties out of the profile section that we will be */
    /* be needing */

    hr = pps->lpVtbl->GetProps(pps, (LPSPropTagArray) &ptaConfig, 0,
            &cvalsProf, &pvalsProf);
    if (HR_FAILED(hr))
        goto err;

    Assert (PROP_ID(pvalsProf[0].ulPropTag) == PROP_ID(PR_SMS_PATH));
    Assert (PROP_ID(pvalsProf[1].ulPropTag) == PROP_ID(PR_SMS_PASSWORD));
    Assert (PROP_ID(pvalsProf[2].ulPropTag) == PROP_ID(PR_SMS_REMEMBER_PW));
    Assert (PROP_ID(pvalsProf[3].ulPropTag) == PROP_ID(PR_SMS_CREATE));

    /* initialize the service parameter block */
    spb.pmsp            = pmsp;
    spb.pps             = pps;
    spb.psup            = psup;
    spb.ulUIParam       = ulUIParam;
    spb.ulSEFlags       = ulSEFlags;
    spb.ulContext       = ulContext;
    spb.cvalsProf       = cvalsProf;
    spb.pvalsProf       = pvalsProf;
    spb.cvalsClient     = cvals;
    spb.pvalsClient     = pvals;

    hr = ResultFromScode(ScCreateOrConfigure(&spb));

err:
    if (lpFreeBuff)
        (*lpFreeBuff)(pvalsProf);

    UlRelease(pmsp);
    UlRelease(pps);

    DebugTraceResult(SMSServiceEntry, hr);
    return hr;
}

/*
 *  Module internal functions
 */

static HRESULT
HrOpenSingleProvider(LPPROVIDERADMIN padp, LPPROFSECT FAR *lppProfSect)
{
    HRESULT     hr;
    LPMAPITABLE pmt = NULL;
    LPSRowSet   prws = NULL;
    LPSPropValue pval;
    SPropTagArray ptaProvUID = {1, {PR_PROVIDER_UID}};

    hr = padp->lpVtbl->GetProviderTable(padp, 0, &pmt);
    if (hr)
        goto err;

    hr = pmt->lpVtbl->SetColumns(pmt, &ptaProvUID, 0L);
    if (hr)
        goto err;

    hr = pmt->lpVtbl->QueryRows(pmt, 1, 0, &prws);
    if (hr || prws == NULL || prws->cRows == 0)
    {
        hr = ResultFromScode(MAPI_E_NOT_FOUND);
        goto err;
    }

    Assert(prws->aRow[0].cValues == 1);
    pval = prws->aRow[0].lpProps;
    if (!pval || pval->ulPropTag != PR_PROVIDER_UID)
    {
        /* The property we need is missing. Error. */
        hr = ResultFromScode(MAPI_E_NOT_FOUND);
        goto err;
    }

    /* Found the right property; use it to open our section */
    hr = padp->lpVtbl->OpenProfileSection(padp,
        (LPMAPIUID) pval->Value.bin.lpb, NULL, MAPI_MODIFY, lppProfSect);

err:
    FreeProws(prws);
    UlRelease(pmt);

    DebugTraceResult(HrOpenSingleProvider, hr);
    return hr;
}

static SCODE ScCreateOrConfigure(PSERVICEPBLK pspb)
{
    SCODE           sc              = S_OK;
    LPSPropValue    pval;
    LPSTR           pszFileTitle;
    CHAR            szPath[MAX_PATH];
    CHAR            szPass[ACCTSIZE];
    LPPROFSECT      pps             = pspb->pps;
    BOOL            fNeedUI         = FALSE;
    BOOL            fAllowUI        = FALSE;
    BOOL            fCreate         = FALSE;
    BOOL            fRemember       = FALSE;

    /* Check for UI */

    if (pspb->ulSEFlags & SERVICE_UI_ALWAYS)
        fAllowUI = fNeedUI = TRUE;
    else    
        if (pspb->ulSEFlags & SERVICE_UI_ALLOWED)
            fAllowUI = TRUE;
        
    if (FFindPropInPSPB(pspb, PR_SMS_PASSWORD, &pval))
    {
        ULONG cbPass;

        /* Passwords must fit in ACCTSIZE bytes. Truncate the password if */
        /* it's too long. */

        cbPass = lstrlenA(pval->Value.lpszA) + 1;
        if (cbPass > ACCTSIZE)
            cbPass = ACCTSIZE;

        memcpy(szPass, pval->Value.lpszA, (UINT) cbPass);
        szPass[cbPass - 1] = '\0';

        /* We found the password. Since we found it, assume that the */
        /* user wants us to remember it. Only if PR_SMS_REMEMBER_PW is */
        /* present and FALSE will we remove the password. */

        fRemember = TRUE;
    }
    else
        szPass[0] = '\0';

    if (FFindPropInPSPB(pspb, PR_SMS_CREATE, &pval))
        fCreate = pval->Value.b;

    if (FFindPropInPSPB(pspb, PR_SMS_REMEMBER_PW, &pval))
        fRemember = pval->Value.b;

    /* try to find the path in either the properties passed in, or */
    /* the properties in the profile */

    if (    FFindPropInPSPB(pspb, PR_SMS_PATH, &pval)
        &&  GetFullPathName(pval->Value.lpszA, MAX_PATH, szPath,
                &pszFileTitle))
    {
        DWORD   dwFA;

        Assert (*(pszFileTitle - 1) == '\\');

        dwFA = GetFileAttributes(szPath);

        /* If the file isn't there, and we aren't creating, then error. */
        /* If the file is there, and we are creating, then error. */

        if (dwFA == 0xFFFFFFFF && fCreate == FALSE)
        {
            sc = MAPI_E_NOT_FOUND;
            fNeedUI = TRUE;
        }
        else if (dwFA != 0xFFFFFFFF && fCreate == TRUE)
        {
            sc = MAPI_E_NO_ACCESS;
            fNeedUI = TRUE;
        }
    }
    else
    {
        szPath[0] = '\0';
        sc = MAPI_E_NOT_FOUND;
        fNeedUI = TRUE;
    }

    while (TRUE)
    {
        if (sc == S_OK)
        {
            PMSL pmsl;
            PIMS pims;

            /* Verify that everything works before we exit. */
    
            if (fCreate)
                sc = ScCreateStore(pspb, szPath, szPass, &pmsl, &pims);
            else
                sc = GetScode(HrCheckAndOpenStore(pspb->pmsp, pspb->psup,
                    TRUE, pspb->pps, szPath, szPass, FALSE, &pmsl, &pims));
            if (sc)
                fNeedUI = TRUE;
            else
            {
                HRESULT hrT;
    
                /* delete the unnecessary properties from the profile */
                pps->lpVtbl->DeleteProps(pps, (LPSPropTagArray)&ptaDel,
                    NULL);

                /* Update saved credentials if they have changed. */
            
                hrT = HrSetProfileCred(pps, szPass, szPath, fRemember, 
                    pims->eidStore.cb, pims->eidStore.lpb,
                    &pims->uidResource);
            
                if (hrT == hrSuccess)
                    hrT = pps->lpVtbl->SaveChanges(pps, 0);
            
                /* Can't make the profile section permanent because */
                /* the support object we are given for config doesn't */
                /* support ModifyProfile. Make it permanent during Logon. */
            
                /* Addref the support object because we kept a reference */
                /* in pims, and releasing pims will release psup. We want */
                /* the refcount on psup to be the same at config exit as */
                /* it was when we were called. */

                UlAddRef(pspb->psup);

                UlRelease(pims);
                UlRelease(pmsl);
    
                if (!fNeedUI)
                    goto ret;   /* SUCCESS! */
            }
        }
        
        if (fNeedUI && !fAllowUI)
        {
            sc = MAPI_E_UNCONFIGURED;
            goto ret;
        }

        /* Do the UI */
    
        sc = GetScode(HrGetLogonDlgCred(pspb->pmsp->hInst, pspb->ulUIParam,
            szPath, szPass, &fCreate, &fRemember));
        
        if (sc != S_OK)
            goto ret;

        fNeedUI = FALSE;
    }

ret:
    DebugTraceSc(ScCreateOrConfigure, sc);
    return sc;
}

/*
 -  ScCreateStore
 -
 *  Create a Sample Store out on disk.
 *
 *  Returns the pims which points to the store, and the
 *  pmsl which points to the MSLogon object.
 */
static SCODE ScCreateStore(PSERVICEPBLK pspb, LPTSTR szPath,
    LPTSTR szPass, PMSL * ppmsl, PIMS * ppims)
{
    HRESULT hr = hrSuccess;
    SCODE sc = S_OK;
    PRFS prfs = NULL;           /* Struct for receive folder settings */
    BOOL fCreateDir = FALSE;    /* Was new directory created? */
    BOOL fCreateProp = FALSE;   /* Was new MsgStore props file created? */
    BOOL fCreateFld = FALSE;    /* Was new root folder created? */
    BOOL fCreateRFS = FALSE;    /* Was receive folder file created? */
    PIMS pims = NULL;
    PMSL pmsl = NULL;

    /* Create the directory */

    if (!CreateDirectory(szPath, NULL))
    {
        sc = MAPI_E_CALL_FAILED;
        goto exit;
    }

    fCreateDir = TRUE;

    /* Create file to hold receive folder settings */

    hr = OpenRFS(szPath, szFolderFileName, RFS_CREATE, &prfs);
    if (hr != hrSuccess)
    {
        sc = GetScode(hr);
        goto exit;
    }

    fCreateRFS = TRUE;

    /* Create the MSLogon object. */

    sc = ScCreateMSL(pspb->pmsp, &pmsl);
    if (sc != S_OK)
        goto exit;

    /* Create instance, creates Message Store props file as well */

    hr = HrNewIMS(szPath, szPropFileName, pspb->pmsp, pmsl, prfs,
            pspb->pps, pspb->psup, TRUE, &pims);
    if (hr != hrSuccess)
    {
        sc = GetScode(hr);
        goto exit;
    }

    OBJ_SetFlag(pims, OBJF_MODIFY);
    pmsl->pims = pims;

    fCreateProp = TRUE;

    hr = HrInitIMSProps(pims, szPass);
    if (hr != hrSuccess)
    {
        sc = GetScode(hr);
        goto exit;
    }

    /* Create file to hold root folder properties */

    {
        PEID peidTmp = NULL;

        hr = HrCreateFolderStorage(NULL, FOLDER_ROOT, "", "",
            FALSE, pims, &peidTmp);

        if (hr != hrSuccess)
        {
            sc = GetScode(hr);
            goto exit;
        }

        /* We can throw away the returned EntryID because we know */
        /* how to construct the EntryID for the root folder when  */
        /* we need to open it (see pims->OpenEntry()).           */

        LMFree(&pspb->pmsp->lmr, peidTmp);
    }

    fCreateFld = TRUE;

    *ppmsl = pmsl;
    *ppims = pims;

exit:
    if (sc != S_OK)
    {
        TCHAR rgch[MAX_PATH];

        if (pims)
        {
            FreeNull(pims->szStorePath);
            LMFree(&pspb->pmsp->lmr, pims->eidStore.lpb);
            LMFree(&pspb->pmsp->lmr, pims);
        }
        else if (prfs)
        {
            /* If we have an RFS but NO IMS, close RFS manually. */
            NFSideAssertSz(CloseRFS(prfs) == hrSuccess, "RFS not closed");
        }

        if ( pmsl )
        {
            pmsl->pims = NULL;

            /* Releasing the pmsl must come after releasing the IMS. */
            UlRelease(pmsl);
        }
        
        /* We need to use state flags to know how much work to undo  */
        /* on a create because otherwise we may accidentally erase   */
        /* files that we did not create (because they were created   */
        /* by another Sample Store creation in a different session). */

        if (fCreateProp == TRUE)
        {
            if (FAppendPathNoMem(szPath, szPropFileName, MAX_PATH, rgch))
                (void)DeleteFile(rgch);
            else
                TrapSz("Can't clean up create #1!");
        }

        if (fCreateRFS == TRUE)
        {
            if (FAppendPathNoMem(szPath, szFolderFileName, MAX_PATH, rgch))
                (void)DeleteFile(rgch);
            else
                TrapSz("Can't clean up create #2!");
        }

        if (fCreateFld == TRUE)
        {
            if (FAppendPathNoMem(szPath, szPropertyFileName, MAX_PATH, rgch))
                (void)DeleteFile(rgch);
            else
                TrapSz("Can't clean up create #3!");
        }

        if (fCreateDir == TRUE)
            (void)RemoveDirectory(szPath);
    }

    DebugTraceSc(ScCreateStore, sc);
    return sc;
}

/*
 *  FAlreadyOpenStore
 *
 *  Purpose:
 *      Searches the list of stores open in this MAPI session and
 *      returns the MS object of a store that matches the path
 *      that's passed in.
 *
 *  Arguments:
 *      pmsp    Pointer to the Message Store Provider (MAPI Session
 *              context).  This is where the list of open stores
 *              lives.
 *      szPath  String containing full path to the store to open.
 *      ppims   Location in which to return the address of a
 *              message store object already open (only valid if
 *              the function returns TRUE).
 *
 *  Returns:
 *      BOOL.  Will be TRUE if the message store is already open,
 *      FALSE if not.
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      None.
 */
static BOOL FAlreadyOpenStore(PMSP pmsp, LPTSTR szPath, PIMS * ppims)
{
    PIMS pimsPrev = NULL;

    for (pimsPrev = (PIMS) pmsp->pobjHead; pimsPrev;
        pimsPrev = (PIMS) pimsPrev->pobjNext)
    {
        if (!lstrcmpi(pimsPrev->szStorePath, szPath))
        {
            OBJ_EnterCriticalSection(pimsPrev);

            if(!OBJ_TestFlag(pimsPrev, MSF_BEINGDESTROYED))
            {
                *ppims = pimsPrev;
                UlAddRef(pimsPrev);

                OBJ_LeaveCriticalSection(pimsPrev);
                return TRUE;
            }
            
            DebugTrace("SMS: Attempt to OpenMsgStore at %s while a another IMsgStore\n"
                        "object opened on this directory is being released\n", szPath);

            OBJ_LeaveCriticalSection(pimsPrev);
        }
    }

    return FALSE;
}

/*
 *  HrGetPassword
 *
 *  Purpose:
 *      Get the password for a store interactively by putting up a dialog.
 *
 *  Parameters:
 *      hInst       [in] Instance handle of my DLL
 *      psup        [in] Pointer to the mapi support object.
 *      plmr        [in] Pointer to the memory allocation routines.
 *      ulUIParam   [in] Window handle cast to ULONG.
 *      szPath      [in] The pathname to the top of the message store.
 *      szPass      [out] Pointer to a buffer in which to place the password.
 *      pfRemember  [out] Address of boolean: should the password be saved
 *                        in profile?
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      Puts up password dialog.
 *
 *  Errors:
 *      None.
 */
static HRESULT HrGetPassword(HINSTANCE hInst, LPMAPISUP psup, PLMR plmr,
    ULONG ulUIParam, LPTSTR szPath, LPTSTR szPass, BOOL *pfRemember)
{
    HRESULT hr = hrSuccess;
    DLGPSWD dlgpswd;

    NFAssertSz(szPass, "Bad szPass");

    lstrcpy(dlgpswd.szPath, szPath);
    dlgpswd.psup = psup;
    dlgpswd.plmr = plmr;
    dlgpswd.fRemember = FALSE;
    dlgpswd.fCancel = FALSE;
    dlgpswd.lpCtl3d = CTL3D_Initialize(hInst);

    if (DialogBoxParam(hInst, TEXT("PSWDDIALOGBOX"), (HWND) ulUIParam,
            (DLGPROC) PasswordDlgProc, (LPARAM) &dlgpswd) == -1)
    {
        hr = ResultFromScode(MAPI_E_CALL_FAILED);
        goto exit;
    }

    if (dlgpswd.fCancel)
    {
        hr = ResultFromScode(MAPI_E_USER_CANCEL);
        goto exit;
    }

    if (szPass)
        lstrcpy(szPass, dlgpswd.szPass);

    if (pfRemember)
        *pfRemember = dlgpswd.fRemember;

    Assert(hr == hrSuccess);

exit:
    CTL3D_Uninitialize(dlgpswd.lpCtl3d);
    DebugTraceResult(HrGetPassword, hr);
    return hr;
}

/*
 *  PasswordDlgProc
 *
 *  Purpose:
 *      Dialog procedure to handle password dialog events.
 *
 *  Parameters:
 *      hDlg        Handle to the dialog.
 *      message     Message to be handled.
 *      wParam      Button ID if button is pressed.
 *      lParam      Context parameter from dialog creation (see
 *                  HrGetLogonDlgCred).
 *
 *  Returns:
 *      BOOL.  TRUE if handled, FALSE if not
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      None.
 */
STDAPI_(BOOL) PasswordDlgProc(HWND hDlg, UINT message, WPARAM wParam,
    LPARAM lParam)
{
    PDLGPSWD pdlgpswd;
    BOOL fHandled = FALSE;

    AssertSz(hDlg, "Bad hDlg");

    switch (message)
    {
    case WM_INITDIALOG:
        {
            SetWindowLong(hDlg, DWL_USER, lParam);
            pdlgpswd = (PDLGPSWD) lParam;

            CTL3D_Subclass(pdlgpswd->lpCtl3d, hDlg, CTL3D_ALL);

#ifdef _WIN32
            SetForegroundWindow(hDlg);
#endif
            BringWindowToTop(hDlg);

            SetDlgItemText(hDlg, TEXT_PATH, pdlgpswd->szPath);

            pdlgpswd->fRemember = FALSE;

            fHandled = TRUE;
            break;
        }

    case WM_COMMAND:
        {
            pdlgpswd = (PDLGPSWD) GetWindowLong(hDlg, DWL_USER);

            switch (LOWORD(wParam))
            {
            case IDOK:
                {
                    GetDlgItemText(hDlg, IDE_ACCOUNT_PASSWORD,
                        pdlgpswd->szPass, ACCTSIZE * sizeof(TCHAR));

                    if (HrConfirmCred(pdlgpswd->szPath, pdlgpswd->szPass,
                        pdlgpswd->psup, pdlgpswd->plmr) != hrSuccess)
                    {
                        /* put up a message box */
                        MessageBox(hDlg, "Password is incorrect.",
                            "Sample Store Password",
                            MB_OK | MB_APPLMODAL | MB_SETFOREGROUND);

                        /* highlight the password field */
                        SetFocus(hDlg);
                        break;
                    }

                    pdlgpswd->fRemember = 
                        IsDlgButtonChecked(hDlg, IDC_REMEMBER);

                    EndDialog(hDlg, 0);
                    fHandled = TRUE;
                    break;
                }
            case IDCANCEL:
                {
                    pdlgpswd->fCancel = TRUE;
                    EndDialog(hDlg, 0);
                    fHandled = TRUE;
                    break;
                }
            default:
                {
                    fHandled = FALSE;
                    break;
                }
            }
        }

    default:
        {
            fHandled = FALSE;
            break;
        }
    }

    return fHandled;
}

/*
 *  HrGetLogonDlgCred
 *
 *  Purpose:
 *      Obtain credentials interactively for opening a store by
 *      putting up a dialog.
 *
 *  Parameters:
 *      hInst       Instance of my DLL
 *      ulUIParam   Window handle cast to ULONG.
 *      szPath      Address of buffer in which to place the path to
 *                  the root directory.
 *      szPass      Address of buffer in which to place the logon
 *                  Account Password.
 *      pfCreate    Address of boolean: should store be created?
 *      pfRemember  Address of boolean: should password be saved in profile?
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      Puts up dialog.
 *
 *  Errors:
 *      None.
 */
static HRESULT HrGetLogonDlgCred(HINSTANCE hInst, ULONG ulUIParam,
    LPTSTR szPath, LPTSTR szPass, BOOL *pfCreate, BOOL *pfRemember)
{
    HRESULT hr = hrSuccess;
    LGNCRED lgncred;

    NFAssertSz(szPass, "Bad szPass");

    lstrcpy(lgncred.szPath, szPath);
    lstrcpy(lgncred.szPass, szPass);
    lgncred.fCreate = FALSE;
    lgncred.fRemember = *pfRemember;
    lgncred.fCancel = FALSE;
    lgncred.ulFieldMask = (szPath ? LGNCRED_PATH : 0L)
                        | (szPass ? LGNCRED_PASS : 0L)
                        | (pfCreate ? LGNCRED_CREATE : 0L)
                        | LGNCRED_REMEMBER;

    lgncred.lpCtl3d = CTL3D_Initialize(hInst);

    if (DialogBoxParam(hInst, TEXT("LOGONDIALOGBOX"), (HWND) ulUIParam,
            (DLGPROC) LogonDlgProc, (LPARAM) &lgncred) == -1)
    {
        hr = ResultFromScode(MAPI_E_CALL_FAILED);
        goto exit;
    }

    if (lgncred.fCancel)
    {
        hr = ResultFromScode(MAPI_E_USER_CANCEL);
        goto exit;
    }

    if (szPath)
    {
        DWORD dwPathLength = 0L;
        LPTSTR szPathName = NULL;

        dwPathLength = GetFullPathName(lgncred.szPath, MAX_PATH,
            szPath, &szPathName);
        if (!dwPathLength || dwPathLength > MAX_PATH)
        {
            hr = ResultFromScode(MAPI_E_UNCONFIGURED);
            goto exit;
        }
    }

    if (szPass)
        lstrcpy(szPass, lgncred.szPass);

    if (pfCreate)
        *pfCreate = lgncred.fCreate;

    *pfRemember = lgncred.fRemember;

    Assert(hr == hrSuccess);

exit:
    CTL3D_Uninitialize(lgncred.lpCtl3d);

    DebugTraceResult(HrGetLogonDlgCred, hr);
    return hr;
}

/*
 *  LogonDlgProc
 *
 *  Purpose:
 *      Dialog procedure to handle logon events.
 *
 *  Parameters:
 *      hDlg        Handle to the dialog.
 *      message     Message to be handled.
 *      wParam      Button ID if button is pressed.
 *      lParam      Context parameter from dialog creation (see
 *                  HrGetLogonDlgCred).
 *
 *  Returns:
 *      BOOL.  TRUE if handled, FALSE if not
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      None.
 */
STDAPI_(BOOL) LogonDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    PLGNCRED plgncred;
    BOOL fHandled = FALSE;

    AssertSz(hDlg, "Bad hDlg");

    switch (message)
    {
    case WM_INITDIALOG:
        {
            SetWindowLong(hDlg, DWL_USER, lParam);
            plgncred = (PLGNCRED) lParam;

            CTL3D_Subclass(plgncred->lpCtl3d, hDlg, CTL3D_ALL);

#ifdef _WIN32
            SetForegroundWindow(hDlg);
#endif
            BringWindowToTop(hDlg);

            if (plgncred->ulFieldMask & LGNCRED_PATH)
                SetDlgItemText(hDlg, IDE_ROOT_PATH, plgncred->szPath);
            else
                EnableWindow(GetDlgItem(hDlg, IDE_ROOT_PATH), FALSE);

            if (plgncred->ulFieldMask & LGNCRED_PASS)
                SetDlgItemText(hDlg, IDE_ACCOUNT_PASSWORD, plgncred->szPass);
            else
                EnableWindow(GetDlgItem(hDlg, IDE_ACCOUNT_PASSWORD), FALSE);

            if (!(plgncred->ulFieldMask & LGNCRED_CREATE))
                EnableWindow(GetDlgItem(hDlg, IDC_CREATE), FALSE);

            if (plgncred->ulFieldMask & LGNCRED_REMEMBER)
                CheckDlgButton(hDlg, IDC_REMEMBER, plgncred->fRemember);
            else
                EnableWindow(GetDlgItem(hDlg, IDC_REMEMBER), FALSE);

            fHandled = TRUE;
            break;
        }

    case WM_COMMAND:
        {
            plgncred = (PLGNCRED) GetWindowLong(hDlg, DWL_USER);

            switch (LOWORD(wParam))
            {
            case IDOK:
                {
                    if (plgncred->ulFieldMask & LGNCRED_CREATE)
                    {
                        plgncred->fCreate =
                            IsDlgButtonChecked(hDlg, IDC_CREATE);
                    }

                    if (plgncred->ulFieldMask & LGNCRED_PATH)
                    {
                        GetDlgItemText(hDlg, IDE_ROOT_PATH,
                            plgncred->szPath, MAX_PATH * sizeof(TCHAR));
                    }

                    /* check if this is a valid path */
                    if (!FIsValidPath(plgncred->szPath, plgncred->fCreate))
                    {
                        /* put up a message box */
                        MessageBox(hDlg, (plgncred->fCreate) ?
                            "Root directory can not be created." :
                            "Path to root directory not found.",
                            "Message Store Logon", MB_OK | MB_APPLMODAL | MB_SETFOREGROUND);

                        /* highlight the path field */
                        SetFocus(hDlg);
                        break;
                    }

                    if (plgncred->ulFieldMask & LGNCRED_PASS)
                    {
                        GetDlgItemText(hDlg, IDE_ACCOUNT_PASSWORD,
                            plgncred->szPass, ACCTSIZE * sizeof(TCHAR));
                    }

                    if (plgncred->ulFieldMask & LGNCRED_REMEMBER)
                    {
                        plgncred->fRemember = 
                            IsDlgButtonChecked(hDlg, IDC_REMEMBER);
                    }

                    EndDialog(hDlg, 0);
                    fHandled = TRUE;
                    break;
                }
            case IDCANCEL:
                {
                    plgncred->fCancel = TRUE;
                    EndDialog(hDlg, 0);
                    fHandled = TRUE;
                    break;
                }
            default:
                {
                    fHandled = FALSE;
                    break;
                }
            }
        }

    default:
        {
            fHandled = FALSE;
            break;
        }
    }

    return fHandled;
}

/*
 *  HrGetProfileCred
 *
 *  Purpose:
 *      Obtain password programmatically by reading the
 *      appropriate property out of the profile. If the 
 *      property isn't there, don't fail the call. Return 
 *      a NULL for the password, and clear the *pfFound flag.
 *
 *  Parameters:
 *      plmr    Pointer to the MAPI linked memory routines
 *      psup    Pointer to the MAPI support object (from which
 *              we can get the current profile section).
 *      szPass  Address of buffer in which to place the Logon
 *              Account Password.
 *      pfFound TRUE if the password was found in the profile.
 *              FALSE if the password wasn't in the profile.
 *
 *  Returns:
 *      HRESULT
 *
 *  Errors:
 *      None.
 */
static HRESULT
HrGetProfileCred(PLMR plmr, LPPROFSECT pps, LPTSTR szPass, BOOL *pfFound)
{
    HRESULT hr;
    LPSPropValue pval = NULL;

    AssertSz(szPass, "Bad szPass");
    AssertSz(pps, "No profile section");

    hr = HrGetOneProp((LPMAPIPROP) pps, PR_SMS_PASSWORD, &pval);

    if (hr != hrSuccess)
    {
        *pfFound = FALSE;
        szPass[0] = (TCHAR) 0;
        hr = hrSuccess;
    }
    else
    {
        lstrcpy(szPass, pval[0].Value.LPSZ);
        *pfFound = TRUE;
    }

    LMFree(plmr, pval);

    DebugTraceResult(HrGetProfileCred, hr);
    return hr;
}

/*
 *  HrSetProfileCred
 *
 *  Purpose:
 *      Save credential information in the profile for future
 *      programmatic opening.
 *
 *  Parameters:
 *      pps         Pointer to the profile section.
 *      szPass      Logon Account Password.
 *      szPath      Path name of root of the store
 *      fRemember   TRUE means save the password in the store.
 *      cbEntryID   Number of bytes in lpEntryID
 *      lpEntryID   Pointer to Wrapped Store EntryID
 *      puidRK      pointer to PR_RECORD_KEY data (always &pims->uidResource)
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      None.
 */
static HRESULT HrSetProfileCred(LPPROFSECT pps, LPTSTR szPass, LPTSTR szPath,
    BOOL fRemember, ULONG cbEntryID, LPBYTE lpEntryID, LPMAPIUID puidRK)
{
    HRESULT hr = hrSuccess;
    LPTSTR szDisplayName = NULL;
    SPropValue rgProps[7];
    ULONG cValues;

    AssertSz(pps, "Bad profile section");
    AssertSz(szPass, "Bad szPass");
    AssertSz(lpEntryID, "Bad lpEntryID");

    /* fill in the Display Name */
    hr = HrAlloc((lstrlen(szDisplayPrefix) + lstrlen(szPath) + 1)
            * sizeof(TCHAR), &szDisplayName);
    if (hr != hrSuccess)
        goto hr_err;

    lstrcpy(szDisplayName, szDisplayPrefix);
    lstrcat(szDisplayName, szPath);

    rgProps[0].ulPropTag = PR_PROVIDER_DISPLAY;
    rgProps[0].Value.LPSZ = szProviderDisplayName;

    rgProps[1].ulPropTag = PR_DISPLAY_NAME;
    rgProps[1].Value.LPSZ = szDisplayName;

    rgProps[2].ulPropTag = PR_ENTRYID;
    rgProps[2].Value.bin.cb = cbEntryID;
    rgProps[2].Value.bin.lpb = lpEntryID;

    rgProps[3].ulPropTag = PR_SMS_PATH;
    rgProps[3].Value.LPSZ = szPath;

    rgProps[4].ulPropTag = PR_MDB_PROVIDER;
    rgProps[4].Value.bin.cb = sizeof(MAPIUID);
    rgProps[4].Value.bin.lpb = (LPBYTE) &uidProvider;

    rgProps[5].ulPropTag = PR_RECORD_KEY;
    rgProps[5].Value.bin.cb = sizeof(MAPIUID);
    rgProps[5].Value.bin.lpb = (LPBYTE) puidRK;

    cValues = 6;

    if (fRemember)
    {
        rgProps[6].ulPropTag = PR_SMS_PASSWORD;
        rgProps[6].Value.LPSZ = szPass;
        ++cValues;
    }
    else
    {
        /* If the user doesn't want to remember the password, then we */
        /* should try to remove it from the profile section. */

        (void) pps->lpVtbl->DeleteProps(pps, &sptaPass, NULL);
    }

    hr = pps->lpVtbl->SetProps(pps, cValues, rgProps, NULL);
    if (hr != hrSuccess)
        goto hr_err;

hr_err:
    FreeNull(szDisplayName);

    DebugTraceResult(HrSetProfileCred, hr);
    return hr;
}

/*
 *  HrConfirmCred
 *
 *  Purpose:
 *      Check user's store opening credentials against the account
 *      information in the store.
 *
 *  Arguments:
 *      szPath      Path to "root" directory of store.
 *      szPass      Logon Account Password.
 *      psup        Pointer to a MAPI Support object (passed to IMsgOnIStg).
 *      plmr        Pointer to the linked mem alloc routines.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 */
static HRESULT HrConfirmCred(LPTSTR szPath, LPTSTR szPass, LPMAPISUP psup,
    PLMR plmr)
{
    HRESULT hr;
    LPMESSAGE lpmsg = NULL;
    LPSPropValue pval = NULL;
    LPTSTR szT = NULL;

    AssertSz(szPath, "Bad szPath");
    AssertSz(szPass, "Bad szPass");

    /* Open the message store props file as an IMessage instance. */

    hr = HrAppendPath(szPath, szPropFileName, &szT);
    if (hr != hrSuccess)
        goto hr_err;

    hr = HrOpenIMSPropsFileRetry(NULL, szT, plmr, psup, FALSE, &lpmsg);
    if (hr != hrSuccess)
        goto hr_err;

    /* Get password from the message store props file   */
    /* and compare against the function parameter.      */

    hr = HrGetOneProp((LPMAPIPROP) lpmsg, PR_SMS_PASSWORD, &pval);

    if (hr != hrSuccess)
        goto hr_err;

    if (lstrcmp(szPass, pval[0].Value.LPSZ))
        hr = ResultFromScode(MAPI_E_LOGON_FAILED);

hr_err:
    FreeNull(szT);
    UlRelease(lpmsg);
    LMFree(plmr, pval);

    DebugTraceResult(HrConfirmCred, hr);
    return hr;
}

/*
 * HrFilePathExists
 *
 * Purpose:
 *      Helper function for HrCheckStoreIntegrity. This function creates a
 *      full pathname to the file given, and attempts to find it on disk.
 *
 * Returns:
 *      HRESULT
 *
 *      If the file exists, and no other errors occur, the function returns
 *      success. If the file doesn't exist, the function returns
 *      MAPI_E_CORRUPT_STORE. If the file exists, but the find can't be closed,
 *      the function returns MAPI_E_LOGON_FAILED.
 */
static HRESULT HrFilePathExists(LPTSTR szStorePath, LPTSTR szFileName)
{
    LPTSTR szT = NULL;
    WIN32_FIND_DATA filedata;
    HANDLE hFindFile;
    HRESULT hr;

    hr = HrAppendPath(szStorePath, szFileName, &szT);
    if (hr != hrSuccess)
        goto exit;

    hFindFile = FindFirstFile(szT, &filedata);
    if (hFindFile == INVALID_HANDLE_VALUE)
    {
        hr = ResultFromScode(MAPI_E_CORRUPT_STORE);
        goto exit;
    }

    if (!FindClose(hFindFile))
        hr = ResultFromScode(MAPI_E_LOGON_FAILED);

exit:
    FreeNull(szT);
    return hr;
}

/*
 *  HrCheckStoreIntegrity
 *
 *  Purpose:
 *      Quick check to see that all the necessary store components
 *      exist in the proper place (store root).  The check of file
 *      attributes assumes that OLE created its docfiles with
 *      normal file attributes.
 *
 *  Arguments:
 *      szPath      Path to "root" directory of store.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      MAPI_E_CORRUPT_STORE    A necessary store component was
 *                              missing.
 */
static HRESULT HrCheckStoreIntegrity(LPTSTR szStorePath)
{
    HRESULT hr;

    AssertSz(!IsBadStringPtr(szStorePath, (UINT) -1), "Bad szStorePath");

    /* Check for the message store properties file */

    hr = HrFilePathExists(szStorePath, szPropFileName);
    if (hr != hrSuccess)
        goto hr_err;

    /* Check for the root folder properties file */

    hr = HrFilePathExists(szStorePath, szPropertyFileName);
    if (hr != hrSuccess)
        goto hr_err;

    /* Check for the receive folder settings storage file */

    hr = HrFilePathExists(szStorePath, szFolderFileName);

hr_err:
    DebugTraceResult(HrCheckStoreIntegrity, hr);
    return hr;
}

/*
 *  FIsValidPath
 *
 *  Purpose:
 *      Returns TRUE if the path in szPath is a valid path to
 *      to an existing directory if fCreate is FALSE. Or the
 *      specified directory can be created if fCreate is TRUE.
 *
 *  Arguments:
 *      szPath      Path to "root" directory of store.
 *      fCreate         TRUE if directory is to be created.
 *
 *  Returns:
 *      BOOL
 *
 *  Side effects:
 *      None.
 *
 */
static BOOL FIsValidPath(LPTSTR szPath, BOOL fCreate)
{
    LPTSTR szLastSlash = NULL;  /* pointer to last slash in szPath */
    DWORD dwAttributes;

    if (*szPath == '\0')
        return FALSE;

    /* if creating a root folder, the folder to check is the parent */
    /* of the one in szPath */
    if (fCreate)
    {
        /* must not already exist */
        if (GetFileAttributes(szPath) != -1)
            return FALSE;

        /* parent directory must exist */
        szLastSlash = SzFindLastCh(szPath, '\\');
        if (szLastSlash && szLastSlash != szPath &&
            *(szLastSlash - 1) != ':')
        {
            *szLastSlash = '\0';
        }
        else
        {
            /* creating a directory at the root level */
            return TRUE;
        }
    }

    /* get the attributes of the directory that must exist */
    dwAttributes = GetFileAttributes(szPath);

    /* restore szPath */
    if (szLastSlash)
        *szLastSlash = '\\';

    return ((dwAttributes != -1) && (dwAttributes & FILE_ATTRIBUTE_DIRECTORY)) ?
        TRUE : FALSE;
}

/*
 * HrGetSpoolSecurity
 *
 * Purpose
 *          return the spooler security information for use in SpoolerLogon
 *
 * Parameters
 *  szPath              path to root of store
 *  szPass              store account password
 *  plmr                pointer to the MAPI linked allocation routines
 *  lpcbSpoolSecurity   byte count of the security information
 *  lppbSpoolSecurity   security information
 */
static HRESULT HrGetSpoolSecurity(LPTSTR szPath, LPTSTR szPass,
    PLMR plmr, ULONG * lpcbSpoolSecurity, LPBYTE * lppbSpoolSecurity)
{
    ULONG cbPath = Cbtszsize(szPath);
    ULONG cbPass = Cbtszsize(szPass);
    SCODE sc = S_OK;

    /* allocate memory for the security information */
    *lpcbSpoolSecurity = cbPass + cbPath;
    sc = LMAlloc(plmr, *lpcbSpoolSecurity, lppbSpoolSecurity);
    if (sc)
    {
        *lpcbSpoolSecurity = 0;
        DebugTraceSc(HrGetSpoolSecurity, sc);
        return ResultFromScode(sc);
    }

    /* fill in the  spooler security information */
    if (cbPath)
        memcpy(*lppbSpoolSecurity, szPath, (UINT) cbPath);
    if (cbPass)
        memcpy(*lppbSpoolSecurity + (UINT) cbPath, szPass, (UINT) cbPass);

    return hrSuccess;
}

/*
 * DecodeSpoolSecurity
 *
 * Purpose
 *          return the spooler security information for use in SpoolerLogon
 *
 * Parameters
 *  cbSpoolSecurity     byte count of the security information
 *  pbSpoolSecurity     security information
 *  szPath              pointer to variable for path to root of store
 *  szPass              poitner to varaible for store account password
 */
static void DecodeSpoolSecurity(ULONG cbSpoolSecurity, LPBYTE pbSpoolSecurity,
    LPTSTR szPath, LPTSTR szPass)
{
    ULONG cbPath = 0;

    lstrcpy(szPath, pbSpoolSecurity);
    cbPath = Cbtszsize(szPath);

    lstrcpy(szPass, pbSpoolSecurity + cbPath);

    return;
}

/*
 * HrCheckAndOpenStore
 *
 * Purpose
 *          check the integrity of store specified in szPath and return
 *          an open store if it's OK
 *
 * Parameters
 *  pmsp                pointer to our MSProvider object
 *  psup                mapi support object
 *  fModify             TRUE if write access desired
 *  pps                 pointer to our profile section
 *  szPath              path name to root of the store
 *  szPass              password to store
 *  fIsSpooler          TRUE if this is a spooler logon
 *  ppmsl               pointer to variable to hold MSLogon object
 *  ppims               pointer to variable to hold the opened store object
 */
static HRESULT HrCheckAndOpenStore(PMSP pmsp, LPMAPISUP psup, BOOL fModify,
    LPPROFSECT pps, LPTSTR szPath, LPTSTR szPass, BOOL fIsSpooler,
    PMSL *ppmsl, PIMS *ppims)
{
    HRESULT hr;
    PRFS prfs = NULL;
    PMSL pmsl = NULL;
    PIMS pims = NULL;
    SCODE sc;

    *ppmsl = NULL;

    hr = HrConfirmCred(szPath, szPass, psup, &pmsp->lmr);
    if (hr != hrSuccess)
        goto exit;

    hr = HrCheckStoreIntegrity(szPath);
    if (hr != hrSuccess)
        goto exit;

    hr = OpenRFS(szPath, szFolderFileName, 0, &prfs);
    if (hr != hrSuccess)
        goto exit;

    /* Create MSLogon object */

    sc = ScCreateMSL(pmsp, &pmsl);
    if (sc != S_OK)
    {
        hr = ResultFromScode(sc);
        goto exit;
    }

    /* Create Message Store object */

    hr = HrNewIMS(szPath, szPropFileName, pmsp, pmsl, prfs, pps, psup,
            FALSE, &pims);
    if (hr != hrSuccess)
        goto exit;

    if (fIsSpooler)
        OBJ_SetFlag(pims, MSF_SPOOLER);

    if (fModify)
        OBJ_SetFlag(pims, OBJF_MODIFY);

    pmsl->pims = pims;

    *ppims = pims;
    *ppmsl = pmsl;

exit:
    if (hr != hrSuccess)
    {
        /* If we have an RFS but failed to create the MS, close RFS manually. */
        if (prfs)
            NFSideAssertSz(CloseRFS(prfs) == hrSuccess, "RFS not closed");

        UlRelease(pmsl);
        pmsl = NULL;
    }

    DebugTraceResult(HrCheckAndOpenStore, hr);
    return hr;
}

/*
 * ScCreateMSL
 *
 * Purpose
 *          returns a new logon object
 *
 * Parameters
 *      pmsp    A pointer to the MS Provider object.
 *      ppmsl   Location in which to return the address of the
 *              newly allocated MSL object.
 *
 *  Returns:
 *      SCODE
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      MAPI_E_NOT_ENOUGH_MEMORY    Could not allocate space for
 *                                  the MSL object.
 */
static SCODE ScCreateMSL(PMSP pmsp, PMSL *ppmsl)
{
    PMSL pmsl;
    SCODE sc;

    sc = LMAllocZ(&pmsp->lmr, sizeof(MSL), &pmsl);

    if (sc == S_OK)
    {
        OBJ_Initialize(pmsl, &vtblMSL, OT_MSLOGON, NULL, &pmsl->cs);

        InitializeCriticalSection(&pmsl->cs);

        pmsl->lmr = pmsp->lmr;

        *ppmsl = pmsl;
    }

    DebugTraceSc(ScCreateMSL, sc);
    return sc;
}

/*
 *  FFindPropInPSPB
 *
 *  Purpose:
 *      Look for the given property in the PSPB structure. Search the
 *      client prop array before the profile prop array.
 *
 *  Arguments:
 *      pspb    pointer to the service parameter block
 *      ulPT    the property tag to look for
 *      ppval   location to place the pointer to the pval
 *
 *  Returns:
 */
static BOOL FFindPropInPSPB(PSERVICEPBLK pspb, ULONG ulPT, LPSPropValue *ppval)
{
    LPSPropValue pval;

    /* First, look in the client's array. If it's not there, look for */
    /* it in the profile array. */

    pval = PpropFindProp(pspb->pvalsClient, pspb->cvalsClient, ulPT);

    if (!pval)
        pval = PpropFindProp(pspb->pvalsProf, pspb->cvalsProf, ulPT);

    if (pval)
    {
        *ppval = pval;
        return TRUE;
    }

    return FALSE;
}

/*
 *  ScGetFullFileName
 *
 *  Purpose:
 *      Look for the file path and name in the property list given.  If
 *      found, convert it to a full (non-relative) path name, and check for
 *      the existence of the directory. Note that we return values even 
 *      when an error occurs.
 *
 *  Arguments:
 *
 *  Returns:
 */
static SCODE ScGetFullFileName(PSERVICEPBLK pspb, BOOL *pfCreate,
    LPSTR pszPath)
{
    SCODE           sc  = S_OK;
    LPSTR           pszFileTitle;
    LPSPropValue    pval;
    BOOL            fCreate = FALSE;

    *pszPath = '\0';
    *pfCreate = FALSE;

    /* get the path to the file */
    if (    FFindPropInPSPB(pspb, PR_SMS_PATH, &pval)
        &&  GetFullPathName(pval->Value.lpszA, MAX_PATH, pszPath,
                &pszFileTitle))
    {
        DWORD   dwFA;
        LPSPropValue pvalT;

        if (FFindPropInPSPB(pspb, PR_SMS_CREATE, &pvalT))
            *pfCreate = pvalT->Value.b;

        Assert (*(pszFileTitle - 1) == '\\');

        dwFA = GetFileAttributes(pszPath);

        /* If the file isn't there, and we aren't creating, then error. */
        /* If the file is there, and we are creating, then error. */

        if (dwFA == 0xFFFFFFFF && *pfCreate == FALSE)
            sc = MAPI_E_NOT_FOUND;
        else if (dwFA != 0xFFFFFFFF && *pfCreate == TRUE)
            sc = MAPI_E_NO_ACCESS;
    }
    else
    {
        *pszPath = '\0';
        sc = MAPI_E_NOT_FOUND;
    }

    DebugTraceSc(ScGetFullFileName, sc);
    return sc;
}


