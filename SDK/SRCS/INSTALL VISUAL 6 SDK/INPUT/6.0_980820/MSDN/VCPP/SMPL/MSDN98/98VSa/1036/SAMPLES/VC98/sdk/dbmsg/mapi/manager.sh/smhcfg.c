/*
 *  S M H C F G . C
 *
 *  Sample mail handling hook configuration
 *  Copyright 1992-95 Microsoft Corporation.  All Rights Reserved.
 */

#include "_pch.h"

/*
 *  Configuration Properties
 *  
 *  sptConfigProps
 *  
 *      This is the set of properties that we expect to find in the
 *      provider's profile section.
 *  
 *  sptRule
 *  
 *      This is the set of properties that are expected to be found in
 *      each rule's profile section.
 */
const SizedSPropTagArray (cpMax, sptConfigProps) =
{
    cpMax,
    {
        PR_PROFILE_NAME,
        PR_SMH_FLAGS,
        PR_SMH_RULES,
        PR_SMH_RULE_NAMES,
        PR_SMH_OOF_TEXT,
        PR_SMH_OOF_ENABLED,
        PR_SMH_OOF_RTF,
        PR_SMH_SOUND_SCHEMES,
        PR_SMH_REPFWD_SCHEMES,
        PR_SMH_EXCLUSIONS
    }
};
const SizedSPropTagArray (cpRLMax, sptRule) =
{
    cpRLMax,
    {
        PR_DISPLAY_NAME,
        PR_RULE_TYPE,
        PR_RULE_DATA,
        PR_RULE_FLAGS,
        PR_RULE_TARGET_ENTRYID,
        PR_RULE_TARGET_PATH,
        PR_RULE_STORE_ENTRYID,
        PR_RULE_STORE_DISPLAY_NAME,
        PR_RULE_SOUND_LOPRI,
        PR_RULE_SOUND_NORMAL,
        PR_RULE_SOUND_HIPRI,
        PR_RULE_FORWARD_RECIP,
        PR_RULE_FORWARD_RECIP_ENTRYID,
        PR_RULE_REP_FWD_RTF,
        PR_RULE_REP_FWD_TEXT
    }
};


/*
 *  Configuration event name
 */
const TCHAR lpszConfigEvt[] = "SMH_CONFIGURATION_EVENT";


/*
 *  HrOpenSingleProvider()
 *  
 *  Purpose:
 *  
 *      Opens the profile section of this service provider.  This is done
 *      by opening the message service table and querying all rows.
 *      Since the SMH service contains only one provider, there is only
 *      one row in the table.  This contains our profile section.  Use
 *      the PR_PROFILE_UID to open the section.
 *  
 *  Arguments:
 *  
 *      lpadmin         the IProfileAdmin object
 *      lppprof [OUT]   on return contains the profile section obj
 *  
 *  Returns:
 *  
 *      (HRESULT)
 *      lppprof [OUT]   contains the profile section object iff the call
 *                      is successful.
 */
HRESULT
HrOpenSingleProvider (LPPROVIDERADMIN lpadmin, LPPROFSECT FAR * lppprof)
{
    HRESULT hr;
    LPMAPITABLE lptbl = NULL;
    LPSRowSet lprws = NULL;
    SPropTagArray sptProvider = {1, {PR_PROVIDER_UID}};
    SRestriction res = {0};

    res.rt = RES_EXIST;
    res.res.resExist.ulPropTag = PR_PROVIDER_DLL_NAME;

    hr = lpadmin->lpVtbl->GetProviderTable (lpadmin, 0, &lptbl);
    if (!HR_FAILED (hr))
    {
        hr = lptbl->lpVtbl->SetColumns (lptbl, &sptProvider, 0L);
        if (!HR_FAILED (hr))
        {
            hr = lptbl->lpVtbl->Restrict (lptbl, &res, 0);
            if (!HR_FAILED (hr))
            {
                hr = lptbl->lpVtbl->QueryRows (lptbl, 10, 0, &lprws);
                if (!HR_FAILED (hr) && lprws->cRows)
                {
                    Assert (lprws->cRows == 1);
                    Assert (lprws->aRow[0].cValues == 1);
                    Assert (lprws->aRow[0].lpProps);
                    Assert (lprws->aRow[0].lpProps[0].ulPropTag == PR_PROVIDER_UID);
                    hr = lpadmin->lpVtbl->OpenProfileSection (lpadmin,
                        (LPMAPIUID)lprws->aRow[0].lpProps[0].Value.bin.lpb,
                        NULL,
                        MAPI_MODIFY,
                        lppprof);
                    MAPIFreeBuffer (lprws->aRow[0].lpProps);
                }
                MAPIFreeBuffer (lprws);
            }
        }
        UlRelease (lptbl);
    }
    DebugTraceResult (HrOpenSingleProvider, hr);
    return hr;
}


/*
 *  HrMergeValues()
 *  
 *  Purpose:
 *  
 *      Merges two property value arrays into one.  By making a copy of
 *      the first and then adding/replacing props from the second.
 *  
 *      IMPORTANT: if there are any property values that are separately
 *      allocated with either MAPIAllocateBuffer() or MAPIAllocateMore(),
 *      then these property values must remain valid as long as the
 *      merged property array is expected to be valid.
 *  
 *  Returns:
 *  
 *      (HRESULT)
 */
HRESULT
HrMergeValues (ULONG cval1,
    LPSPropValue lpval1,
    ULONG cval2,
    LPSPropValue lpval2,
    LPALLOCATEBUFFER lpfnAlloc,
    ULONG FAR * lpcvalMerged,
    LPSPropValue FAR * lppvalMerged)
{
    SCODE sc;
    LPSPropValue lpval = NULL;
    UINT cb;
    UINT ip;

    cb = (UINT)(cval1 + cval2) * sizeof(SPropValue);
    sc = (*lpfnAlloc)(cb, &lpval);
    if (!FAILED (sc))
    {
        /*  Slurp the original data across */

        memcpy (lpval, lpval1, (UINT)cval1 * sizeof(SPropValue));

        /*  Move the new stuff over */

        while (cval2--)
        {
            for (ip = 0; ip < (UINT)cval1; ip++)
            {
                /*  See if we match properties */

                if (PROP_ID (lpval[ip].ulPropTag) == PROP_ID (lpval2[cval2].ulPropTag))
                {
                    /*  We matched, but are we a real property */

                    if (PROP_TYPE (lpval2[cval2].ulPropTag) != PT_ERROR)
                        lpval[ip] = lpval2[cval2];
                    break;
                }
            }
            if (ip == cval1)
                lpval[cval1++] = lpval2[cval2];
        }
        *lpcvalMerged = cval1;
        *lppvalMerged = lpval;
    }
    DebugTraceSc (HrMergeValues(), sc);
    return ResultFromScode (sc);
}


/*
 *  HrUpdateProfileFormat()
 *  
 *  Purpose:
 *  
 *      Converts the WMS level of SMH profile properties to post WMS
 *      levels.  Namely rules are now stored via a pair of properties
 *      in the profile.  PR_SMH_RULES has been changed to a multi-valued
 *      binary property and PR_SMH_RULE_NAMES contains the display names
 *      for the rules.  The prevents the configuration functions from
 *      opening all profile sections to build the list of rules.
 *  
 *  Arguments:
 *  
 *      lpvOPSCtxt          Context passed to OpenProfileSection()
 *                          (a session or an profadmin object)
 *      lpfnOpenProfSect    Pointer to OpenProfileSection()
 *      lpfnMore            MAPIAllocateMore() function
 *      lpfnFree            MAPIFreeBuffer() function
 *      lpvalNew            propvalue array for the converted values
 *      lpvalOld            propvalue of the old PR_SMH_RULES
 *  
 *  Returns:
 *  
 *      (HRESULT)
 */

HRESULT
HrUpdateProfileFormat (LPVOID lpvOPSCtxt,
    LPOPENPROFSECT lpfnOpenProfSect,
    LPALLOCATEMORE lpfnMore,
    LPFREEBUFFER lpfnFree,
    LPSPropValue lpvalNew,
    LPSPropValue lpvalOld)
{
    SCODE sc = S_OK;
    LPMAPIUID lpmuid;
    LPPROFSECT lpsec = NULL;
    LPSBinary lpbin;
    LPSPropValue lpval = NULL;
    LPTSTR FAR * lppsz;
    SizedSPropTagArray (2, spt) = {2, {PR_DISPLAY_NAME, PR_RULE_TYPE}};
    UINT cb;
    UINT crl;
    UINT i;
    ULONG cval;
    
    DebugTrace ("SMH: updating profile to new format\n");

    /*  Make sure that the size is an even number of UIDs */

    Assert ((lpvalOld->Value.bin.cb % sizeof(MAPIUID)) == 0);
    crl = (UINT)lpvalOld->Value.bin.cb / sizeof(MAPIUID);

    /*  Allocate space for the two new properties */

    cb = crl * sizeof(SBinary);
    sc = (*lpfnMore) (cb, lpvalNew, &lpbin);
    if (FAILED (sc))
        goto ret;
    memset (lpbin, 0, cb);
    
    cb = crl * sizeof(LPTSTR);
    sc = (*lpfnMore) (cb, lpvalNew, (LPVOID FAR *)&lppsz);
    if (FAILED (sc))
        goto ret;
    memset (lppsz, 0, cb);
    
    /*  Iterate through the old list building the two new lists as we go */
    
    lpmuid = (LPMAPIUID)lpvalOld->Value.bin.lpb;
    for (i = 0; crl--; lpmuid++)
    {
        /*  Open the old profile section and get PR_DISPLAY_NAME
         *  and PR_RULE_TYPE for conversion purposes.  The type
         *  will be converted and reset into the profile section.
         *  Thus, completing the conversion for that section.
         *
         *  The display name will be extracted and copied out to
         *  the external names property and will be saved out when
         *  all section conversions are completed
         */
        if (!HR_FAILED ((*lpfnOpenProfSect) (lpvOPSCtxt, lpmuid, NULL, MAPI_MODIFY, &lpsec)) &&
            !HR_FAILED (lpsec->lpVtbl->GetProps (lpsec, (LPSPropTagArray)&spt, 0, &cval, &lpval)) &&
            !FAILED ((*lpfnMore) (sizeof(MAPIUID), lpvalNew, &lpbin[i].lpb)) &&
            !FAILED ((*lpfnMore) (lstrlen (lpval[0].Value.LPSZ) + 1, lpvalNew, &lppsz[i])))
        {
            switch (lpval[1].Value.l)
            {
              case 1:
                lpval[1].Value.l = RL_SUBJECT;
                break;
              case 2:
                lpval[1].Value.l = RL_SENDER;
                break;
              case 4:
                lpval[1].Value.l = RL_HAS_ATTACH;
                break;
              case 8:
                lpval[1].Value.l = RL_BODY;
                break;
              case 16:
                lpval[1].Value.l = RL_TO_RECIP;
                break;
              case 32:
                lpval[1].Value.l = RL_CC_RECIP;
                break;
              case 64:
                lpval[1].Value.l = RL_BCC_RECIP;
                break;
              case 128:
                lpval[1].Value.l = RL_ANY_RECIP;
                break;
              case 256:
                lpval[1].Value.l = RL_MSG_CLASS;
                break;
            }
            if (!HR_FAILED (HrSetOneProp ((LPMAPIPROP)lpsec, &lpval[1])))
            {
                DebugTrace ("SMH: converting '%s' rule\n", lpval[0].Value.LPSZ);
                lpbin[i].cb = sizeof(MAPIUID);
                memcpy (lpbin[i].lpb, lpmuid, sizeof(MAPIUID));
                lstrcpy (lppsz[i], lpval[0].Value.LPSZ);
                i++;
            }
        }
        (*lpfnFree) (lpval);
        UlRelease (lpsec);
        lpval = NULL;
        lpsec = NULL;
    }
    lpvalNew[ipRules].ulPropTag = PR_SMH_RULES;
    lpvalNew[ipRules].Value.MVbin.cValues = i;
    lpvalNew[ipRules].Value.MVbin.lpbin = lpbin;
    lpvalNew[ipNames].ulPropTag = PR_SMH_RULE_NAMES;
    lpvalNew[ipNames].Value.MVSZ.cValues = i;
    lpvalNew[ipNames].Value.MVSZ.LPPSZ = lppsz;

ret:

    DebugTraceSc (HrUpdateProfileFormat(), sc);
    return ResultFromScode (sc ? sc : ((i == crl) ? 0 : MAPI_W_ERRORS_RETURNED));
}
        

/*
 *  HrGetConfigEvent()
 *  
 *  Purpose:
 *  
 *      Gets the configuration event handle.  The handle is used to
 *      signal logged in handlers that their configuration has been
 *      modified and, at the next reasonable chance, should be reloaded.
 *  
 *      Called at SMH init time only.
 *  
 *  Arguments:
 *  
 *      lphevt  [OUT]   contains the handle iff the call succeeds
 *  
 *  Returns:
 *  
 *      (HRESULT)
 */
#ifdef  _WIN32
HRESULT
HrGetConfigEvent (HANDLE FAR * lphevt)
{
    HANDLE hevt = NULL;
        
    if (!(hevt = CreateEvent (NULL, TRUE, FALSE, lpszConfigEvt)) &&
        !(hevt = OpenEvent (EVENT_MODIFY_STATE, FALSE, lpszConfigEvt)))
        ResultFromScode (MAPI_E_NOT_ENOUGH_RESOURCES);

    *lphevt = hevt;
    return hrSuccess;
}
#endif  /* _WIN32 */


/*
 *  SignalConfigChanged()
 *  
 *  Purpose:
 *  
 *      Sets the configuration event such that logged in hooks can update
 *      their configuration on the fly.
 *  
 *      Called from within the service entry when configuration changes
 *      are commited.
 */
#ifdef  _WIN32
VOID
SignalConfigChanged (VOID)
{
    HANDLE hevt = NULL;
    
    if (hevt = OpenEvent (EVENT_MODIFY_STATE, FALSE, lpszConfigEvt))
    {
        SetEvent (hevt);
        CloseHandle (hevt);
    }
    return;
}
#endif  /* _WIN32 */


/*
 *  FConfigChanged()
 *  
 *  Purpose:
 *  
 *      Tests the configuration event such that logged in hooks can update
 *      their configuration on the fly if the configuration has changed.
 *  
 *      Called from within the SMH object at regualr intervals
 *  
 *  Returns:
 *  
 *      TRUE iff the config changed
 *  
 */
#ifdef  _WIN32
BOOL
FConfigChanged (HANDLE hevt)
{
    ULONG dw;

    dw = WaitForSingleObject (hevt, 0);
    Assert (dw != WAIT_ABANDONED);
    return (dw == WAIT_OBJECT_0);
}
#endif  /* _WIN32 */


/*
 *  SMH_ServiceEntry()
 *  
 *  Purpose:
 *  
 *      The ServiceEntry() function is the MAPI entry point to configure
 *      a service for use in a profile.  The call can then bring up UI to
 *      ensure configuration of the SMH provider.
 *  
 *  Parameters:
 *  
 *      hinst           DLL instance
 *      lpmalloc        OLE style allocator (used by PropSheet())
 *      lpsup           MAPI profile support object
 *      ulUIParam       hwnd that is to be used as UI parent
 *      ulFlags         configuration flags
 *      ulContext       configuration action
 *      cval            count of caller supplied properties
 *      lpval           caller supplied properties to be configured
 *      lpadmin         IProviderAdmin object
 *      lppmerr [OUT]   extended error information
 *  
 *  Operation:
 *  
 *      The ServiceEntry() uses the IProviderAdmin object to open its
 *      profile section and retrieve the current set of properties.  The
 *      caller supplied properties are then merged into the set of
 *      current properties.
 *  
 *      If either this set of properties is not sufficient for
 *      configuration or the caller specifically asked for configuration
 *      UI, then ServiceEntry() will make calls to bring up its config
 *      UI.
 *  
 *      ServiceEntry() recognizes several configuration flags.  If
 *      SERVICE_UI_ALWAYS and/or SERVICE_UI_ALLOWED are set, UI is
 *      allowed and we be brought up if appropriate.  Is
 *      MSG_SERVICE_UI_READ_ONLY is set, then the UI should not 
 *      allow the configuration to be modified.
 *  
 *      The configuration contexts MSG_SERVICE_DELETE, MSG_SERVICE_INSTALL, 
 *      and MSG_SERVICE_UNINSTALL are ignored and no action is taken.
 *      MSG_SERVICE_CONFIGURE and MSG_SERVICE_CREATE allow the caller to
 *      create or update the configuration properties in this providers
 *      profile section. 
 *  
 *      SMH will not return extended information in the MAPIERROR in case
 *      of error
 */
HRESULT STDAPICALLTYPE
SMH_ServiceEntry(
    HINSTANCE hinst,
    LPMALLOC lpmalloc,
    LPMAPISUP lpsup,
    ULONG ulUIParam,
    ULONG ulFlags,
    ULONG ulContext,
    ULONG cval,
    LPSPropValue lpval,
    LPPROVIDERADMIN lpadmin,
    LPMAPIERROR FAR * lppmerr)
{
    HRESULT hr = hrSuccess;
    BOOL fUI = FALSE;
    LPALLOCATEBUFFER lpfnAlloc = NULL;
    LPALLOCATEMORE lpfnAllocMore = NULL;
    LPFREEBUFFER lpfnFree = NULL;
    LPMAPIUID lpmuid = NULL;
    LPPROFSECT lpprof = NULL;
    LPPROFSECT lpprofSvc = NULL;
    LPSCD lpscd = NULL;
    LPSPropValue lpvalCur = NULL;
    LPSPropValue lpvalNew = NULL;
    LPSPropValue lpvalOld;
    SPropValue val;
    UINT csec = 0;
    UINT i;
    ULONG cvalCur;
    ULONG cvalNew;
    ULONG ulMyFlags;

    if ((ulContext == MSG_SERVICE_INSTALL) ||
        (ulContext == MSG_SERVICE_UNINSTALL))
        goto ret;

    if ((ulContext != MSG_SERVICE_CONFIGURE) &&
        (ulContext != MSG_SERVICE_CREATE) &&
        (ulContext != MSG_SERVICE_DELETE))
    {
        hr = ResultFromScode (MAPI_E_NO_SUPPORT);
        goto ret;
    }

    if (ulFlags & MAPI_UNICODE)
    {
        /*  Unicode is not supported by SMH */

        hr = ResultFromScode (MAPI_E_BAD_CHARWIDTH);
        goto ret;
    }

    /*  Find out our UI options */

    fUI = !!(ulFlags & SERVICE_UI_ALWAYS);
    ulMyFlags = (ulFlags & MSG_SERVICE_UI_READ_ONLY)
        ? UI_READONLY
        : 0;

    /*  Get memory routines */

    hr = lpsup->lpVtbl->GetMemAllocRoutines (lpsup,
                            &lpfnAlloc,
                            &lpfnAllocMore,
                            &lpfnFree);
    if (HR_FAILED (hr))
        goto ret;

    /*  Open the profile section */

    hr = HrOpenSingleProvider (lpadmin, &lpprof);
    if (HR_FAILED (hr))
        goto ret;

    /*  Get the values already in the profile */

    hr = lpprof->lpVtbl->GetProps (lpprof,
                            (LPSPropTagArray)&sptConfigProps,
                            0,
                            &cvalCur,
                            &lpvalCur);
    if (HR_FAILED (hr))
        goto ret;

    /*  Check that the rules are stored in the correct format */
    
    if (lpvalCur[ipRules].ulPropTag != PR_SMH_RULES)
    {
        hr = HrGetOneProp ((LPMAPIPROP)lpprof,
                    CHANGE_PROP_TYPE(PR_SMH_RULES, PT_BINARY),
                    &lpvalOld);
        if (!HR_FAILED (hr))
        {
            /*  The rules are stored in the wrong format */

            hr = HrUpdateProfileFormat (lpadmin,
                            lpadmin->lpVtbl->OpenProfileSection,
                            lpfnAllocMore,
                            lpfnFree,
                            lpvalCur,
                            lpvalOld);
            (*lpfnFree) (lpvalOld);
            if (HR_FAILED (hr))
                goto ret;

            /*  Save out anything we got back */

            lpprof->lpVtbl->SetProps (lpprof, cpMax, lpvalCur, NULL);
        }
    }

    if (ulContext != MSG_SERVICE_DELETE)
    {
        /*  Merge what was in the profile with what was passed in */

        hr = HrMergeValues (cvalCur,
                            lpvalCur,
                            cval,
                            lpval,
                            lpfnAlloc,
                            &cvalNew,
                            &lpvalNew);
        if (HR_FAILED (hr))
            goto ret;

        /*  If we dont have all the props we need, then
         *  we will have to ask for them
         */
        fUI = fUI || (lpvalNew[ipFlags].ulPropTag != PR_SMH_FLAGS);
        if ((lpvalNew[ipFlags].ulPropTag != PR_SMH_FLAGS) &&
            (!(ulFlags & (SERVICE_UI_ALLOWED | SERVICE_UI_ALWAYS)) ||
            (ulFlags & MSG_SERVICE_UI_READ_ONLY)))
        {
            /*  We need UI but can't have it. */

            hr = ResultFromScode (MAPI_E_UNCONFIGURED);
            goto ret;
        }

        if (fUI)
        {
            /*  Do the config dialog */

            if (!FAILED ((*lpfnAlloc) (sizeof(SCD), &lpscd)))
            {
                memset (lpscd, 0, sizeof(SCD));
                lpscd->hinst = hinst;
                lpscd->hwnd = (HWND)ulUIParam;
                lpscd->lpfnAlloc = lpfnAlloc;
                lpscd->lpfnAllocMore = lpfnAllocMore;
                lpscd->lpfnFree = lpfnFree;
                lpscd->lpmalloc = lpmalloc;
                lpscd->lpval = lpvalNew;
                lpscd->lpsec = lpprof;
                lpscd->lpsup = lpsup;
                lpscd->lpadmin = lpadmin;
                lpscd->ulFlags = ulMyFlags;
                hr = HrDisplayPropSheets (hinst, (HWND)ulUIParam, lpscd);
            }
            else
            {
                hr = ResultFromScode (MAPI_E_NOT_ENOUGH_MEMORY);
                goto ret;
            }
        }

        /*  Open the service profile section and set PR_SERVICE_EXTRA_UIDS */

        if (!HR_FAILED (lpadmin->lpVtbl->OpenProfileSection (lpadmin,
                                            NULL,
                                            NULL,
                                            MAPI_MODIFY,
                                            &lpprofSvc)))
        {
            /*  PR_SERVICE_EXTRA_UIDS is composed of all additional
             *  sections used by SMH.  By setting this value, we gain
             *  the ability to have the service copied and\or moved
             *  while having the additional sections move across with
             *  it.
             */
            if (lpvalNew[ipRules].ulPropTag == PR_SMH_RULES)
                csec += (UINT)lpvalNew[ipRules].Value.MVbin.cValues;
            
            if (csec && !FAILED ((*lpfnAlloc) (csec * sizeof(MAPIUID), &lpmuid)))
            {
                for (i = 0; i < csec; i++)
                    memcpy (&lpmuid[i],
                        lpvalNew[ipRules].Value.MVbin.lpbin[i].lpb,
                        sizeof(MAPIUID));

                val.ulPropTag = PR_SERVICE_EXTRA_UIDS;
                val.Value.bin.cb = csec * sizeof(MAPIUID);
                val.Value.bin.lpb = (LPBYTE)lpmuid;
                lpprofSvc->lpVtbl->SetProps (lpprofSvc, 1, &val, NULL);
                lpprofSvc->lpVtbl->SaveChanges (lpprofSvc, 0);
                (*lpfnFree) (lpmuid);
            }
            UlRelease (lpprofSvc);
        }
    }
    
ret:

#ifdef  _WIN32
    if (!HR_FAILED (hr))
        SignalConfigChanged ();
#endif

    /*  Cleanup what was left behind */

    if (lpscd)
    {   
        for (i = 0; i < lpscd->crl; i++)
        {
            (*lpfnFree) (lpscd->lppsz[i]);
            (*lpfnFree) (lpscd->lpbin[i].lpb);
        }
        (*lpfnFree) (lpscd->lppsz);
        (*lpfnFree) (lpscd->lpbin);
        (*lpfnFree) (lpscd);
    }
                
    if (lpfnFree)
    {
        (*lpfnFree) (lpvalCur);
        (*lpfnFree) (lpvalNew);
    }

    UlRelease (lpprof);
    DebugTraceResult (SMH_ServiceEntry, hr);
    return hr;
};
