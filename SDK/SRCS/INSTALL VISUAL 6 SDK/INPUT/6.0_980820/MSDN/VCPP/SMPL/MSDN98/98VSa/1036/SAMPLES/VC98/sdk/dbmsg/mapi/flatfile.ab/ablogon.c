/***********************************************************************
 *
 *  ABLOGON.C
 *
 *
 *  The Sample Address Book Provider.
 *
 *  This file has the code to implement the Sample Address Book's logon
 *  object.
 *
 *  The following routines are implemented in this file:
 *  
 *  ABPLOGON_QueryInterface
 *  ABPLOGON_Release
 *  ABPLOGON_Logoff
 *  ABPLOGON_OpenEntry
 *  ABPLOGON_CompareEntryIDs
 *  ABPLOGON_Advise
 *  ABPLOGON_Unadvise
 *  ABPLOGON_OpenStatusEntry
 *  ABPLOGON_OpenTemplateID
 *  ABPLOGON_GetOneOffTable
 *  ABPLOGON_PrepareRecips
 *  
 *  LpMuidFromLogon
 *  HrLpszGetCurrentFileName
 *  HrReplaceCurrentfileName
 *  GenerateContainerDN
 *  HrBuildRootHier
 *  
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 *
 ***********************************************************************/


#include "abp.h"
#include "sampabp.rh"
#include <smpab.h>


/*
 *  Definition of the logon object
 */
typedef struct _ABPLOGON {

    ABPLOGON_Vtbl FAR *     lpVtbl;

    SAB_IUnknown;

    /*
     *  Private structure
     */
    LPABPROVIDER lpABP;

    LPSTR lpszFileName;         /* Name of file that is browsed */
    MAPIUID muidID;             /* UID for this logon object */
    LPMAPISUP lpMapiSup;        /* MAPI Support object - gotten via ABP_Logon */

    /*
     *  Table Data for canned tables
     */


    LPTABLEDATA lpTDatRoot;     /*  Root hierarchy  */
    LPTABLEDATA lpTDatOO;       /*  One Off Table  */

} ABPLOGON, FAR *LPABPLOGON;



ABPLOGON_Vtbl vtblABPLOGON =
{
    ABPLOGON_QueryInterface,
    (ABPLOGON_AddRef_METHOD *) ROOT_AddRef,
    ABPLOGON_Release,
    (ABPLOGON_GetLastError_METHOD *) ROOT_GetLastError,
    ABPLOGON_Logoff,
    ABPLOGON_OpenEntry,
    ABPLOGON_CompareEntryIDs,
    ABPLOGON_Advise,
    ABPLOGON_Unadvise,
    ABPLOGON_OpenStatusEntry,
    ABPLOGON_OpenTemplateID,
    ABPLOGON_GetOneOffTable,
    ABPLOGON_PrepareRecips
};



/*
 -  HrNewABLogon
 -
 *
 *  Creates a new Sample AB Logon object.
 */

HRESULT
HrNewABLogon(   LPABLOGON *         lppABLogon,
                LPABPROVIDER        lpABP,
                LPMAPISUP           lpMAPISup,
                LPSTR               lpszSABFile,
                LPMAPIUID           lpmuid,
                HINSTANCE           hLibrary,
                LPALLOCATEBUFFER    lpAllocBuff,
                LPALLOCATEMORE      lpAllocMore,
                LPFREEBUFFER        lpFreeBuff,
                LPMALLOC            lpMalloc )
{
    SCODE sc;
    HRESULT hResult = hrSuccess;
    SPropValue rgSPVStat[6];
    LPABPLOGON lpABPLogon = NULL;

    /*
     *  Allocate space for the lpABPLogon object
     */

    sc = lpAllocBuff(sizeof(ABPLOGON), &lpABPLogon);
    if (FAILED(sc))
    {
        hResult = ResultFromScode(sc);
        goto out;
    }

    /*
     *  Initialize the ABPLogon object
     */

    lpABPLogon->lpVtbl = &vtblABPLOGON;

    lpABPLogon->lcInit = 1;
    lpABPLogon->hResult = hrSuccess;
    lpABPLogon->idsLastError = 0;

    lpABPLogon->hLibrary = hLibrary;

    lpABPLogon->lpMalloc = lpMalloc;
    lpABPLogon->lpAllocBuff = lpAllocBuff;
    lpABPLogon->lpAllocMore = lpAllocMore;
    lpABPLogon->lpFreeBuff = lpFreeBuff;

    lpABPLogon->lpMapiSup = lpMAPISup;
    lpABPLogon->lpABP = (LPABPROVIDER) lpABP;
    lpABPLogon->lpszFileName = lpszSABFile;
    lpABPLogon->muidID = *lpmuid;

    lpABPLogon->lpTDatRoot = NULL;
    lpABPLogon->lpTDatOO = NULL;

    /*
     *  Register my status row...
     */
    rgSPVStat[0].ulPropTag = PR_DISPLAY_NAME_A;
    rgSPVStat[0].Value.lpszA = lpszSABFile;
    rgSPVStat[1].ulPropTag = PR_RESOURCE_METHODS;
    rgSPVStat[1].Value.l = 0;   
    rgSPVStat[2].ulPropTag = PR_RESOURCE_FLAGS;
    rgSPVStat[2].Value.l = 0;
    rgSPVStat[3].ulPropTag = PR_STATUS_CODE;
    rgSPVStat[3].Value.l = STATUS_AVAILABLE;
    rgSPVStat[4].ulPropTag = PR_STATUS_STRING;
    rgSPVStat[4].Value.lpszA = "Available";
    rgSPVStat[5].ulPropTag = PR_PROVIDER_DISPLAY;
    rgSPVStat[5].Value.lpszA = "Sample Address Book Provider";

    /*
     *  Set the Status Row for this provider,
     *  but do not allow an error from setting the
     *  status row to cause failure to Logon.
     */

    (void)lpMAPISup->lpVtbl->ModifyStatusRow(lpMAPISup,
        sizeof(rgSPVStat) / sizeof(SPropValue), rgSPVStat, 0);

    /*
     *  AddRef the support object, because we're keeping
     *  a pointer to it in our Logon object.
     */
    lpMAPISup->lpVtbl->AddRef(lpMAPISup);

    /*
     *  AddRef our parent ABInit object
     */
    lpABP->lpVtbl->AddRef(lpABP);

    InitializeCriticalSection(&lpABPLogon->cs);
    
    *lppABLogon = (LPABLOGON) lpABPLogon;

out:

    DebugTraceResult(HrNewABPLogon, hResult);
    return hResult;
}   


/*************************************************************************
 *
 -  ABPLOGON_QueryInterface
 -
 */
STDMETHODIMP
ABPLOGON_QueryInterface(LPABPLOGON lpABPLogon, REFIID lpiid,
    LPVOID * ppvObj)
{
    
    Validate_IUnknown_QueryInterface(lpABPLogon, lpiid, ppvObj);


    /*  See if the requested interface is one of ours */

    if (memcmp(lpiid, &IID_IUnknown, sizeof(IID)) &&
        memcmp(lpiid, &IID_IABLogon, sizeof(IID)))
    {
        *ppvObj = NULL;         /* OLE requires zeroing [out] parameter on error */
        DebugTraceSc(ABPLOGON_QueryInterface, E_NOINTERFACE);
        return ResultFromScode(E_NOINTERFACE);
    }

    /*  We'll do this one. Bump the usage count and return a new pointer. */

    EnterCriticalSection(&lpABPLogon->cs);
    ++lpABPLogon->lcInit;
    LeaveCriticalSection(&lpABPLogon->cs);
    
    *ppvObj = lpABPLogon;

    return hrSuccess;
}

/*
 *  Use ROOTs AddRef
 */

/*************************************************************************
 *
 -  ABPLOGON_Release
 -
 */
STDMETHODIMP_(ULONG)
ABPLOGON_Release(LPABPLOGON lpABPLogon)
{
    LONG lcInit;


    EnterCriticalSection(&lpABPLogon->cs);
    lcInit = --lpABPLogon->lcInit;
    LeaveCriticalSection(&lpABPLogon->cs);

    if (lcInit == 0)
    {
        /*
         *  Free up the file
         */
        lpABPLogon->lpFreeBuff(lpABPLogon->lpszFileName);

        /*
         *  Release the Hierarchy Table Data
         */
        if (lpABPLogon->lpTDatRoot)
            lpABPLogon->lpTDatRoot->lpVtbl->Release(lpABPLogon->lpTDatRoot);

        /*
         *  Release the One-Off Table Data
         */
        if (lpABPLogon->lpTDatOO)
            lpABPLogon->lpTDatOO->lpVtbl->Release(lpABPLogon->lpTDatOO);

        /*
         *  No longer need to be holding on to our parent
         */
        lpABPLogon->lpABP->lpVtbl->Release(lpABPLogon->lpABP);
    
        /*
         *  Release the support object last.
         */
        lpABPLogon->lpMapiSup->lpVtbl->Release(lpABPLogon->lpMapiSup);

        DeleteCriticalSection(&lpABPLogon->cs);
        lpABPLogon->lpVtbl = NULL;
        lpABPLogon->lpFreeBuff(lpABPLogon);
        return (0);
    }
    return lcInit;
}

/*************************************************************************
 *
 -  ABPLOGON_Logoff
 -
 *  Logoff from this logon object.  Clean up any resources/objects that
 *  our logon object has accumulated.
 *
 *
 */
STDMETHODIMP
ABPLOGON_Logoff(LPABPLOGON lpABPLogon, ULONG ulFlags)
{

    /*
     *  Remove this logon object from the list of known
     *  logon objects associated with this initialization
     *  of this provider.
     */
    (void) RemoveLogonObject(lpABPLogon->lpABP, lpABPLogon, lpABPLogon->lpFreeBuff);

    return hrSuccess;
}

/*************************************************************************
 *
 -  ABPLOGON_OpenEntry
 -
 *  Creates an object with (at least) the IMAPIProp interface from an
 *  entryID.
 *
 *  There are four valid types of entryIDs handled:
 *
 *    NULL          <- return back the root container object
 *    DIR_ENTRYID   <- return back the directory container object
 *    USR_ENTRYID   <- return back the MAILUSER object
 *    OOUSR_ENTRYID <- return back the OneOff MAILUSER object
 *
 *  Note:  This call is reused for all other internal objects that support OpenEntry().
 *    Those other calls *must* check their parameters before calling this method.
 *    The only other way this method is called is via MAPI which does parameter checking
 *    for us.  The most we'll do here is assert our parameters.
 */
STDMETHODIMP
ABPLOGON_OpenEntry(LPABPLOGON lpABPLogon,
    ULONG cbEntryID,
    LPENTRYID lpEntryID,
    LPCIID lpInterface,
    ULONG ulFlags,
    ULONG * lpulObjType,
    LPUNKNOWN * lppUnk)
{

    LPDIR_ENTRYID lpSampEID = (LPDIR_ENTRYID) lpEntryID;
    HRESULT hResult = hrSuccess;

    /*
     *  Check the EntryID
     */

    if (!cbEntryID)
    {
        LPABCONT lpABCont = NULL;

        /*
         *  Special case:  the root level object
         */

        NFAssertSz(!lpEntryID, "Non-NULL entry id passed with 0 cb to OpenEntry()\n");
        
        /*  Make this new object  */

        hResult = HrNewROOT((LPABCONT *) lppUnk,
                            lpulObjType,
                            (LPABLOGON) lpABPLogon,
                            lpInterface,
                            lpABPLogon->hLibrary,
                            lpABPLogon->lpAllocBuff,
                            lpABPLogon->lpAllocMore,
                            lpABPLogon->lpFreeBuff,
                            lpABPLogon->lpMalloc);
        goto out;
    }

    /*
     *  There's an entryID there, is it mine??
     *  I need to check because I'm reusing this routine for
     *  my Container->OpenEntry call, and I can't be sure the
     *  client will always be well behaved.
     *
     *  When this routine is called from MAPI, this call is redundant.  But
     *  because I'm reusing this routine, I gotta check.
     */

    /*  Compare MAPIUIDs  */
    if (memcmp(&(((LPDIR_ENTRYID) lpEntryID)->muid), &muidABSample,
            sizeof(MAPIUID)))
    {
        /*
         *  Not mine!
         */

        hResult = ResultFromScode(MAPI_E_INVALID_ENTRYID);
        goto out;
    }

    /*
     *  What object does this correspond to??
     */

    /*  I've only got two types: containers and users  */

    if (lpSampEID->ulType == SAMP_DIRECTORY)
    {
        LPABLOGON lpABPLogonT = NULL;

        /* entry id must have the same verson number */
        if (lpSampEID->ulVersion != SAMP_VERSION)
        {
            hResult = ResultFromScode(MAPI_E_UNKNOWN_ENTRYID);
            SetErrorIDS(lpABPLogon, hResult, IDS_OLD_EID);

            goto out;
        }

        /*
         *  find the correct logon object for this entryid
         */

        (void) FindLogonObject(lpABPLogon->lpABP, &lpSampEID->muidID, &lpABPLogonT);

        /* did we find the corresponding logon object */
        if (!lpABPLogonT)
        {
            hResult = ResultFromScode(MAPI_E_UNKNOWN_ENTRYID);
            goto out;
        }

        hResult = HrNewSampDirectory( (LPABCONT *) lppUnk,
                                    lpulObjType,
                                    (LPABLOGON) lpABPLogonT,
                                    lpInterface,
                                    lpABPLogon->hLibrary,
                                    lpABPLogon->lpAllocBuff,
                                    lpABPLogon->lpAllocMore,
                                    lpABPLogon->lpFreeBuff,
                                    lpABPLogon->lpMalloc);
        goto out;

    }

    if (lpSampEID->ulType == SAMP_USER)
        if (cbEntryID == (ULONG) sizeof(USR_ENTRYID))
        {
            hResult = HrNewSampUser( (LPMAILUSER *) lppUnk,
                                    lpulObjType,
                                    cbEntryID,
                                    lpEntryID,
                                    (LPABLOGON) lpABPLogon,
                                    lpInterface,
                                    lpABPLogon->hLibrary,
                                    lpABPLogon->lpAllocBuff,
                                    lpABPLogon->lpAllocMore,
                                    lpABPLogon->lpFreeBuff,
                                    lpABPLogon->lpMalloc);

            goto out;
        }

    if (lpSampEID->ulType == SAMP_OOUSER)
        if (cbEntryID == (ULONG) sizeof(OOUSR_ENTRYID))
        {
            hResult = HrNewSampOOUser( (LPMAILUSER *) lppUnk,
                                        lpulObjType,
                                        cbEntryID,
                                        lpEntryID,
                                        (LPABLOGON) lpABPLogon,
                                        lpInterface,
                                        lpABPLogon->hLibrary,
                                        lpABPLogon->lpAllocBuff,
                                        lpABPLogon->lpAllocMore,
                                        lpABPLogon->lpFreeBuff,
                                        lpABPLogon->lpMalloc);


            goto out;
        }

    hResult = ResultFromScode(MAPI_E_UNKNOWN_ENTRYID);

out:
    DebugTraceResult(ABPLOGON_OpenEntry, hResult);

    return hResult;

}

/*************************************************************************
 *
 -  ABPLOGON_CompareEntryIDs
 -
 *  If the two entryids are mine and they're of the same type, then
 *  just do a binary comparison to see if they're equal.
 *
 */
STDMETHODIMP
ABPLOGON_CompareEntryIDs(LPABPLOGON lpABPLogon,
    ULONG cbEntryID1,
    LPENTRYID lpEntryID1,
    ULONG cbEntryID2,
    LPENTRYID lpEntryID2,
    ULONG ulFlags,
    ULONG * lpulResult)
{

    LPDIR_ENTRYID lpSampEID1 = (LPDIR_ENTRYID) lpEntryID1;
    LPDIR_ENTRYID lpSampEID2 = (LPDIR_ENTRYID) lpEntryID2;
    HRESULT hResult = hrSuccess;

    /*
     *  Check to see if their MUID is mine
     */
    if (memcmp(&(lpSampEID1->muid), &muidABSample, sizeof(MAPIUID)) ||
        memcmp(&(lpSampEID2->muid), &muidABSample, sizeof(MAPIUID)))
    {
        /*
         *  No recognition of these entryids.
         */

        *lpulResult = (ULONG) FALSE;
        hResult = ResultFromScode(MAPI_E_UNKNOWN_ENTRYID);
        goto out;
    }

    /*
     *  See if the type of entryids are the same
     */
    if (lpSampEID1->ulType != lpSampEID2->ulType)
    {
        /*
         *  They're not, so they don't match
         */

        *lpulResult = (ULONG) FALSE;
        goto out;

    }

    /*
     *  See if the entryids are the same size.  They'd better be
     *  if they're the same type.
     */
    if (cbEntryID1 != cbEntryID2)
    {
        /*
         *  They're not?!?  Then I don't know these...
         */

        *lpulResult = (ULONG) FALSE;
        hResult = ResultFromScode(MAPI_E_UNKNOWN_ENTRYID);

        goto out;
    }

    /*
     *  Check for Directory entryids
     */
    if (lpSampEID1->ulType == SAMP_DIRECTORY)
    {
        /*
         *  Ok, I'm dealing with directory entryids
         */

        /*
         *  Better make sure it's the right size
         */
        if (cbEntryID1 != sizeof(DIR_ENTRYID))
        {
            /*
             *  This doesn't make sense.  I don't recognize this entryid.
             */

            *lpulResult = (ULONG) FALSE;
            hResult = ResultFromScode(MAPI_E_UNKNOWN_ENTRYID);

            goto out;
        }

        /*
         *  At this point it's just a memcmp
         */
        if (memcmp(lpSampEID1, lpSampEID2, sizeof(DIR_ENTRYID)))
        {
            /*
             *  They're not equal
             */

            *lpulResult = (ULONG) FALSE;

            goto out;
        }

        /*
         *  They must be the same
         */

        *lpulResult = (ULONG) TRUE;

        goto out;
    }

    if (lpSampEID1->ulType == SAMP_USER)
    {
        /*
         *  Ok, I'm dealing with user entryids
         */

        /*
         *  Better make sure it's the right size
         */
        if (cbEntryID1 != sizeof(USR_ENTRYID))
        {
            /*
             *  This doesn't make sense.  I don't recognize this entryid.
             */

            *lpulResult = (ULONG) FALSE;
            hResult = ResultFromScode(MAPI_E_UNKNOWN_ENTRYID);

            goto out;
        }

        /*
         *  At this point it's just a memcmp
         */
        if (memcmp(lpSampEID1, lpSampEID2, sizeof(USR_ENTRYID)))
        {
            /*
             *  They're not equal
             */

            *lpulResult = (ULONG) FALSE;

            goto out;
        }

        /*
         *  They must be the same
         */

        *lpulResult = (ULONG) TRUE;

        goto out;
    }

    if (lpSampEID1->ulType == SAMP_OOUSER)
    {
        /*
         *  Ok, I'm dealing with oneoff user entryids
         */

        /*
         *  Better make sure it's the right size
         */
        if (cbEntryID1 != sizeof(OOUSR_ENTRYID))
        {
            /*
             *  This doesn't make sense.  I don't recognize this entryid.
             */

            *lpulResult = (ULONG) FALSE;
            hResult = ResultFromScode(MAPI_E_UNKNOWN_ENTRYID);

            goto out;
        }

        /*
         *  At this point it's just a memcmp
         */
        if (memcmp(lpSampEID1, lpSampEID2, sizeof(OOUSR_ENTRYID)))
        {
            /*
             *  They're not equal
             */

            *lpulResult = (ULONG) FALSE;

            goto out;
        }

        /*
         *  They must be the same
         */

        *lpulResult = (ULONG) TRUE;

        goto out;
    }

    /*
     *  It's no entryid I know of
     */

    *lpulResult = (ULONG) FALSE;
    hResult = ResultFromScode(MAPI_E_UNKNOWN_ENTRYID);

out:

    DebugTraceResult(ABPLOGON_CompareEntryIDs, hResult);
    return hResult;

}

/*************************************************************************
 *
 -  ABPLOGON_OpenStatusEntry
 -
 *
 *
 *
 */
STDMETHODIMP
ABPLOGON_OpenStatusEntry(LPABPLOGON lpABPLogon,
    LPCIID lpIID,
    ULONG ulFlags,
    ULONG FAR * lpulObjType,
    LPMAPISTATUS FAR * lppEntry)
{
    HRESULT hr;

    /*
     *  Validate Parameters
     */
    Validate_IABLogon_OpenStatusEntry(lpABPLogon, lpIID, ulFlags,
                                        lpulObjType, lppEntry);


    hr = HrNewStatusObject( lppEntry,
                            lpulObjType,
                            ulFlags,
                            (LPABLOGON) lpABPLogon,
                            lpIID,
                            lpABPLogon->hLibrary,
                            lpABPLogon->lpAllocBuff,
                            lpABPLogon->lpAllocMore,
                            lpABPLogon->lpFreeBuff,
                            lpABPLogon->lpMalloc);

    DebugTraceResult(ABPLOGON_OpenStatusEntry, hr);
    return hr;
}

/*************************************************************************
 *
 -  ABPLOGON_OpenTemplateID
 -
 *
 *
 *
 */
STDMETHODIMP
ABPLOGON_OpenTemplateID(LPABPLOGON lpABPLogon,
    ULONG cbTemplateId,
    LPENTRYID lpTemplateId,
    ULONG ulTemplateFlags,
    LPMAPIPROP lpMAPIPropData,
    LPCIID lpInterface,
    LPMAPIPROP * lppMAPIPropNew,
    LPMAPIPROP lpMAPIPropSibling)
{
    HRESULT hResult;

    /*
     *  Validate Parameters
     */
    Validate_IABLogon_OpenTemplateID(lpABPLogon, cbTemplateId, lpTemplateId,
                            ulTemplateFlags, lpMAPIPropData, lpInterface,
                            lppMAPIPropNew, lpMAPIPropSibling);

    /* //$ need stronger checking here... */
    /* entryid better be right size */
    if (cbTemplateId != sizeof(OOUSR_ENTRYID) && cbTemplateId != sizeof(USR_ENTRYID))
    {
        hResult = ResultFromScode(MAPI_E_INVALID_ENTRYID);
        goto out;
    }

    /*  is it my entry id compare MAPIUIDs  */
    if (memcmp(&(((LPUSR_ENTRYID) lpTemplateId)->muid), &muidABSample,
            sizeof(MAPIUID)))
    {
        hResult = ResultFromScode( MAPI_E_INVALID_ENTRYID );
        goto out;
    }

    /* better be a oneoff user entryid or a user entry id */
    if (((LPUSR_ENTRYID) lpTemplateId)->ulType == SAMP_OOUSER)
    {

        hResult = HrNewOOTID(   lppMAPIPropNew,
                                cbTemplateId,
                                lpTemplateId,
                                ulTemplateFlags,
                                lpMAPIPropData,
                                (LPABLOGON) lpABPLogon,
                                lpInterface,
                                lpABPLogon->hLibrary,
                                lpABPLogon->lpAllocBuff,
                                lpABPLogon->lpAllocMore,
                                lpABPLogon->lpFreeBuff,
                                lpABPLogon->lpMalloc);
            
    }
    else if (((LPUSR_ENTRYID) lpTemplateId)->ulType == SAMP_USER)
    {
        hResult = HrNewTID( lppMAPIPropNew,
                            cbTemplateId,
                            lpTemplateId,
                            ulTemplateFlags,
                            lpMAPIPropData,
                            (LPABLOGON) lpABPLogon,
                            lpInterface,
                            lpABPLogon->hLibrary,
                            lpABPLogon->lpAllocBuff,
                            lpABPLogon->lpAllocMore,
                            lpABPLogon->lpFreeBuff,
                            lpABPLogon->lpMalloc);
    }
    else
    {
        hResult = MakeResult(MAPI_E_INVALID_ENTRYID);
    }

out:

    DebugTraceResult(ABPLOGON_OpenTemplateID, hResult);
    return hResult;
}

/*
 -  ABPLOGON_GetOneOffTable
 -
 *  Returns the lists of one-offs that this providers can support creation of.
 *  This list is added to the entries gathered from all the other AB logon objects
 *  and exposed to the user as the list of things that can be created on a 
 *  message.  Also this total list is available to other providers through the
 *  support method GetOneOffTable().
 *  
 *  Note:  There's a bug here that if there are more than one Sample Address Books
 *  installed on a particular profile, then there will be multiple entries in the
 *  one-off table from this provider.  This can be changed to only have one one-off
 *  entry, no matter how many SABs are configured in a profile, if the one-off table
 *  was associated with the ABInit object.
 */

/*
 *  Column set for the oneoff table
 */
enum {  ivalootPR_DISPLAY_NAME_A = 0,
        ivalootPR_ENTRYID,
        ivalootPR_DEPTH,
        ivalootPR_SELECTABLE,
        ivalootPR_ADDRTYPE_A,
        ivalootPR_DISPLAY_TYPE,
        ivalootPR_INSTANCE_KEY,
        ivalootMax };

static const SizedSPropTagArray(ivalootMax, tagaColSetOOTable) =
{
    ivalootMax,
    {
        PR_DISPLAY_NAME_A,
        PR_ENTRYID,
        PR_DEPTH,
        PR_SELECTABLE,
        PR_ADDRTYPE_A,
        PR_DISPLAY_TYPE,
        PR_INSTANCE_KEY
    }
};

STDMETHODIMP
ABPLOGON_GetOneOffTable(
    LPABPLOGON lpABPLogon,
    ULONG ulFlags,
    LPMAPITABLE * lppTable)
{
    SCODE sc;
    HRESULT hResult;
    SRow sRow;
    SPropValue rgsPropValue[ivalootMax];
    ULONG ulInstanceKey = 1;
    OOUSR_ENTRYID EntryID;

    /*
     *  Validate Parameters
     */
     
    
    Validate_IABLogon_GetOneOffTable(lpABPLogon, ulFlags, lppTable);


    if ( ulFlags & MAPI_UNICODE )
    {
        DebugTraceArg( APBLOGON_GetOneOffTable, "UNICODE not supported" );
        return ResultFromScode( MAPI_E_BAD_CHARWIDTH );
    }
    
    
    EnterCriticalSection(&lpABPLogon->cs);
    
    /*
     * If there's not one already associated with this logon object,
     * then create one.
     */
    if (!lpABPLogon->lpTDatOO)
    {
        /* Create a Table data object */
        sc = CreateTable(
            (LPIID) &IID_IMAPITableData,
            lpABPLogon->lpAllocBuff,
            lpABPLogon->lpAllocMore,
            lpABPLogon->lpFreeBuff,
            lpABPLogon->lpMalloc,
            0,
            PR_DISPLAY_NAME_A,
            (LPSPropTagArray) &tagaColSetOOTable,
            &(lpABPLogon->lpTDatOO));

        if (FAILED(sc))
        {
            hResult = ResultFromScode(sc);
            goto out;
        }

        /* Constants*/

        sRow.cValues = ivalootMax;
        sRow.lpProps = rgsPropValue;

        /* The Display Name */
        rgsPropValue[ivalootPR_DISPLAY_NAME_A].ulPropTag = PR_DISPLAY_NAME_A;
        rgsPropValue[ivalootPR_DISPLAY_NAME_A].Value.lpszA = "Sample Address Book Recipient";

        /* the Entry ID*/
        ZeroMemory(&EntryID, sizeof(OOUSR_ENTRYID));

        EntryID.muid = muidABSample;
        EntryID.ulVersion = SAMP_VERSION;
        EntryID.ulType = SAMP_OOUSER;

        rgsPropValue[ivalootPR_ENTRYID].ulPropTag = PR_ENTRYID;
        rgsPropValue[ivalootPR_ENTRYID].Value.bin.cb = sizeof(OOUSR_ENTRYID);
        rgsPropValue[ivalootPR_ENTRYID].Value.bin.lpb = (LPVOID) &EntryID;

        /* the depth property */
        rgsPropValue[ivalootPR_DEPTH].ulPropTag = PR_DEPTH;
        rgsPropValue[ivalootPR_DEPTH].Value.l = 0;

        /* the selectable property */
        rgsPropValue[ivalootPR_SELECTABLE].ulPropTag = PR_SELECTABLE;
        rgsPropValue[ivalootPR_SELECTABLE].Value.b = TRUE;

        /*
         *  The address type that would be generated by an entry
         *  created from this template
         */
        rgsPropValue[ivalootPR_ADDRTYPE_A].ulPropTag = PR_ADDRTYPE;
        rgsPropValue[ivalootPR_ADDRTYPE_A].Value.lpszA = lpszEMT;

        /*
         *  The display type associated with a recipient built with this template
         */
        rgsPropValue[ivalootPR_DISPLAY_TYPE].ulPropTag = PR_DISPLAY_TYPE;
        rgsPropValue[ivalootPR_DISPLAY_TYPE].Value.l = DT_MAILUSER;


        /*
         *  The instance key of this row in this one-off table.  Since there's only one
         *  row in this one-off table, just default it to a value of 1.
         */
        rgsPropValue[ivalootPR_INSTANCE_KEY].ulPropTag = PR_INSTANCE_KEY;
        rgsPropValue[ivalootPR_INSTANCE_KEY].Value.bin.cb = sizeof(ULONG);
        rgsPropValue[ivalootPR_INSTANCE_KEY].Value.bin.lpb = (LPBYTE) &ulInstanceKey;

        (void) lpABPLogon->lpTDatOO->lpVtbl->HrModifyRow(
                            lpABPLogon->lpTDatOO,
                            &sRow);

    }

    /*
     *  Get a view to return to the caller
     */
    hResult = lpABPLogon->lpTDatOO->lpVtbl->HrGetView(
        lpABPLogon->lpTDatOO,
        NULL,
        NULL,
        0,
        (LPMAPITABLE *) lppTable);

out:

    LeaveCriticalSection(&lpABPLogon->cs);

    DebugTraceResult(ABPLogon_GetOneOffTable, hResult);
    return hResult;
}

/*************************************************************************
 *
 -  ABPLOGON_Advise
 -
 *  NYI
 *
 *
 */
STDMETHODIMP
ABPLOGON_Advise(LPABPLOGON lpABPLogon,
    ULONG cbEntryID,
    LPENTRYID lpEntryID,
    ULONG ulEventMask,
    LPMAPIADVISESINK lpAdviseSink,
    ULONG FAR * lpulConnection)
{
    DebugTraceSc(ABPLOGON_Advise, MAPI_E_NO_SUPPORT);
    return ResultFromScode(MAPI_E_NO_SUPPORT);
}

/*************************************************************************
 *
 -  ABPLOGON_Unadvise
 -
 *  NYI
 *
 *
 */
STDMETHODIMP
ABPLOGON_Unadvise(LPABPLOGON lpABPLogon, ULONG ulConnection)
{
    DebugTraceSc(ABPLOGON_Unadvise, MAPI_E_NO_SUPPORT);
    return ResultFromScode(MAPI_E_NO_SUPPORT);
}

/*************************************************************************
 *
 -  ABPLOGON_PrepareRecips
 -
 *
 *
 *
 */
STDMETHODIMP
ABPLOGON_PrepareRecips(LPABPLOGON lpABPLogon,
    ULONG ulFlags,
    LPSPropTagArray lpPropTagArray,
    LPADRLIST lpRecipList)
{
    HRESULT         hResult         = hrSuccess;
    UINT            iRecip;
    UINT            iProp;
    ULONG           cValues;
    LPSPropValue    lpspvUser       = NULL;
    LPSPropValue    lpNewRecip      = NULL;
    LPMAPIPROP      lpMAPIPropEntry = NULL;
    SCODE           sc              = S_OK;
    ULONG           ulObjType;
    BOOL            fUselpspvUser;

    /* loop through all the recipients */
    
    if (!lpPropTagArray)
    {
        /*
         *  They only want us to update our entryID from ephemeral to
         *  permanent.  Since ours are already permanent, we don't need to
         *  do anything.
         */
        goto out;
    }

    for (iRecip = 0; iRecip < lpRecipList->cEntries; iRecip++)
    {
        LPUSR_ENTRYID   lpEntryID   = NULL;
        ULONG           cbEntryID;
        LPSPropValue    lpPropVal       = NULL;
        LPSPropValue    rgpropvalsRecip = lpRecipList->aEntries[iRecip].rgPropVals;
        ULONG           cPropsRecip     = lpRecipList->aEntries[iRecip].cValues;

        /* For each recipient, find its entryid */
        
        lpPropVal = PpropFindProp( rgpropvalsRecip, cPropsRecip, PR_ENTRYID );
        
        if ( lpPropVal )
        {
            lpEntryID = (LPUSR_ENTRYID)lpPropVal->Value.bin.lpb;
            cbEntryID = lpPropVal->Value.bin.cb;
        }
        else
            continue;
                
        /* Is it one of ours? */
         
        if ( cbEntryID < CbNewENTRYID(0)
            || IsBadReadPtr( (LPVOID) lpEntryID, (UINT) cbEntryID ) )
        {
            continue;   /* no */
        }
         
        if ( memcmp( &(lpEntryID->muid), &muidABSample, sizeof(MAPIUID) ) )
            continue;   /* no */

        /* Try and open it. */
         
        hResult = HrNewSampUser((LPMAILUSER *)&lpMAPIPropEntry,
                                &ulObjType, 
                                cbEntryID, 
                                (LPENTRYID) lpEntryID, 
                                (LPABLOGON) lpABPLogon,
                                NULL, 
                                lpABPLogon->hLibrary,
                                lpABPLogon->lpAllocBuff,
                                lpABPLogon->lpAllocMore,
                                lpABPLogon->lpFreeBuff,
                                lpABPLogon->lpMalloc );

        if ( HR_FAILED(hResult) )
        {
             /* Couldn't open it...; Ignore it and keep looking */

            hResult = hrSuccess;
            DebugTrace( "ABPLOGON_PrepareRecips sees a bad user entry ID\n" );
            continue;
        }

        /* Get the properties requested */

        hResult = lpMAPIPropEntry->lpVtbl->GetProps( lpMAPIPropEntry, 
                lpPropTagArray, 0, /* ansi */
                &cValues, &lpspvUser );

        /* No longer need lpMAPIPropEntry  */
        
        lpMAPIPropEntry->lpVtbl->Release(lpMAPIPropEntry);
        lpMAPIPropEntry = NULL;

        if (HR_FAILED(hResult))
        {
            /* Failed getting properties. Cleanup and ignore this entry */

            hResult = hrSuccess;
            continue;
        }
        
        hResult = hrSuccess;

        Assert(cValues == lpPropTagArray->cValues);

        /*
         *  This is the hard part.
         *  Merge the two property sets: lpspvUser and lpsPropVal.  Note that
         *  both of these sets may have the same property - chances are they do.
         *  for these conflicts, lpspvUser should be the one we get the property
         *  from.
         *
         *  Guess how big the resultant SPropValue array is, and allocate one of that
         *  size.
         */

        sc = lpABPLogon->lpAllocBuff( (cValues + cPropsRecip) * sizeof( SPropValue ), 
                &lpNewRecip);
        if (FAILED(sc))
        {
            /*
             *  Ok, to fail the call here.  If we're running into out of memory conditions
             *  we're all in trouble.
             */

            hResult = ResultFromScode( sc );
            goto err;
        }

        /*
         *  Copy lpspvUser properties over to lpNewRecip
         *  Check each property in lpsvUser to ensure that it isn't PT_ERROR, if so
         *  find the propval in rgpropvalsRecip ( the [in] recip prop val array ), 
         *  if it exists and use that property.
         */
        
        for (iProp = 0; iProp < cValues; iProp++)
        {
            fUselpspvUser = TRUE;
            
            if ( PROP_TYPE( lpspvUser[iProp].ulPropTag ) == PT_ERROR )
            {
                lpPropVal = PpropFindProp( rgpropvalsRecip, cPropsRecip,
                         lpPropTagArray->aulPropTag[iProp] );
                         
                if ( lpPropVal )
                {
                    sc = PropCopyMore(  lpNewRecip + iProp, lpPropVal,
                            lpABPLogon->lpAllocMore, lpNewRecip );
                            
                    fUselpspvUser = FALSE;      
                }
            }
                
            if ( fUselpspvUser )
            {
                sc = PropCopyMore(  lpNewRecip + iProp, lpspvUser + iProp,
                        lpABPLogon->lpAllocMore, lpNewRecip );
            }
            
            if (FAILED(sc))
            {
                if (sc == MAPI_E_NOT_ENOUGH_MEMORY)
                {
                    hResult = MakeResult(sc);
                    goto err;
                }
                
                /*
                 *   Otherwise we've run into something wierd in the prop value array
                 *   like PT_UNSPECIFIED, PT_NULL, or PT_OBJECT.  In which case continue
                 *   on.
                 */
            }
        }
        
        /* Done with lpspvUser */
        
        lpABPLogon->lpFreeBuff( lpspvUser );
        lpspvUser = NULL;

        /*
         *  Copy those properties that aren't already in lpNewRecip
         *  from rgpropvalsRecip.  Don't copy over the PT_ERROR prop vals
         */
        for ( iProp = 0; iProp < cPropsRecip; iProp++ )
        {
        
            if ( PpropFindProp( lpNewRecip, cValues, rgpropvalsRecip[iProp].ulPropTag ) 
                || PROP_TYPE( rgpropvalsRecip[iProp].ulPropTag ) == PT_ERROR )
                continue;

            sc = PropCopyMore(  lpNewRecip + cValues, rgpropvalsRecip + iProp,
                    lpABPLogon->lpAllocMore, lpNewRecip );
            if ( FAILED( sc ) )
            {
                if (sc == MAPI_E_NOT_ENOUGH_MEMORY)
                {
                     
                    hResult = ResultFromScode( sc );
                    goto err;
                }
                
                /*
                 *  Otherwise we've run into something wierd in the prop value array
                 *  like PT_UNSPECIFIED, PT_NULL, or PT_OBJECT.  In which case continue
                 *  on.
                 */
            }
            
            cValues++;
        }

        /*
         *  Replace the AdrEntry in the AdrList with this new lpNewRecip.  And
         *  don't forget the cValues!
         */

        lpRecipList->aEntries[iRecip].rgPropVals = lpNewRecip;
        lpRecipList->aEntries[iRecip].cValues    = cValues;

        /* Finally, free up the old AdrEntry. */

        lpABPLogon->lpFreeBuff( rgpropvalsRecip );

    }
out:

    DebugTraceResult( ABPLOGON_PrepareRecips, hResult );
    return hResult;

err:

    lpABPLogon->lpFreeBuff( lpspvUser );
    goto out;
}


/*
 *  LpMuidFromLogon -
 *    Returns the particular ABPLOGON object's unique identifier.
 *
 */  

LPMAPIUID
LpMuidFromLogon(LPABLOGON lpABLogon)
{
    LPABPLOGON lpABPLogon = (LPABPLOGON) lpABLogon;

    AssertSz(!IsBadReadPtr(lpABPLogon, sizeof(ABPLOGON)), "Bad logon object!\n");

    return (&(lpABPLogon->muidID));
}


/*
 *  HrLpszGetCurrentFileName -
 *    Returns a copy of the current .SAB file pointed to by this logon object.
 *
 */

HRESULT
HrLpszGetCurrentFileName(LPABLOGON lpABLogon, LPSTR * lppszFileName)
{
    LPABPLOGON lpABPLogon = (LPABPLOGON) lpABLogon;
    SCODE sc;
    HRESULT hResult = hrSuccess;

    AssertSz(!IsBadReadPtr(lpABPLogon, sizeof(ABPLOGON)), "SAB: Bad logon object!\n");
    AssertSz(!IsBadWritePtr(lppszFileName, sizeof(LPSTR)), "SAB: Bad dest string!\n");

    EnterCriticalSection(&lpABPLogon->cs);
    
    sc = lpABPLogon->lpAllocBuff (lstrlenA(lpABPLogon->lpszFileName)+1, lppszFileName);
    if (FAILED(sc))
    {
        hResult = ResultFromScode(sc);
        goto ret;
    }

    lstrcpyA( *lppszFileName, lpABPLogon->lpszFileName);
    
ret:
    LeaveCriticalSection(&lpABPLogon->cs);

    DebugTraceResult(HrLpszGetCurrentFileName, hResult);
    return hResult;
}

/*
 *  HrReplaceCurrentFileName -
 *    Replaces the current file name associated with this logon object and tries
 *    to save it all away in the profile.
 */

HRESULT
HrReplaceCurrentFileName(LPABLOGON lpABLogon, LPSTR lpszNewFile)
{
    LPABPLOGON lpABPLogon = (LPABPLOGON) lpABLogon;
    HRESULT hResult = hrSuccess;
    LPPROFSECT lpProfSect = NULL;
    LPSTR lpstrT;
    SCODE sc;
    SPropValue rgspv[1];

    AssertSz(!IsBadReadPtr(lpABPLogon, sizeof(ABPLOGON)), "Bad logon object!\n");
    
    EnterCriticalSection(&lpABPLogon->cs);

    /*
     *  SAB file name has changed have to update profile and objects
     */
    if (lstrcmpA(lpszNewFile, lpABPLogon->lpszFileName))
    {

        /*
         *  Open the private profile section...
         */
        hResult = lpABPLogon->lpMapiSup->lpVtbl->OpenProfileSection(
            lpABPLogon->lpMapiSup,
            NULL,
            MAPI_MODIFY,
            &lpProfSect);
        if (HR_FAILED(hResult))
        {
            /*
             *  Shouldn't get here, but in case I do, just...
             */
            goto ret;
        }

        /*
         *  Save the new name back into the profile
         */
        rgspv[0].ulPropTag = PR_SAB_FILE;
        rgspv[0].Value.lpszA = lpszNewFile;

        /*
         *  Don't care if I can save it in the profile or not.
         *  Saving it's a nice to have, but absolutely required
         *  for operation of this particular provider.
         */
        (void) lpProfSect->lpVtbl->SetProps(
            lpProfSect,
            1,
            rgspv,
            NULL);

        lpProfSect->lpVtbl->Release(lpProfSect);

        /*
         *  Allocate and copy this new one
         */

        sc = lpABPLogon->lpAllocBuff (lstrlenA(lpszNewFile)+1, &lpstrT);
        if (FAILED(sc))
        {
            hResult = ResultFromScode(sc);
            goto ret;
        }

        lstrcpyA( lpstrT, lpszNewFile );

        /*
         *  Free up the old one...
         */
        lpABPLogon->lpFreeBuff(lpABPLogon->lpszFileName);

        /*
         *  Put in the new one.
         */
        lpABPLogon->lpszFileName = lpstrT;

        /*
         *  Update the hierarchy table
         */
        hResult = HrBuildRootHier((LPABLOGON)lpABPLogon, NULL);
    }

ret:
    LeaveCriticalSection(&lpABPLogon->cs);

    DebugTraceResult(HrReplaceCurrentFileName, hResult);
    return hResult;
}

/*
 *  GenerateContainerDN -
 *      Common code for generating the display name of the single
 *      container exposed from this logon object.
 */
void
GenerateContainerDN(LPABLOGON lpABLogon, LPSTR lpszName)
{
    LPABPLOGON lpABPLogon = (LPABPLOGON) lpABLogon;
    LPSTR lpszFileName;
    int ich;

    AssertSz(!IsBadReadPtr(lpABPLogon, sizeof(ABPLOGON)), "Bad logon object!\n");
    

    EnterCriticalSection(&lpABPLogon->cs);

    lpszFileName = lpABPLogon->lpszFileName;

    /* get the filename without the path */
    for (ich = lstrlenA(lpszFileName) - 1; ich >= 0; ich--)
    {
        if (lpszFileName[ich] == '\\')
            break;
    }

    /* skip past the backslash */
    ich++;

    wsprintfA(lpszName, "SAB using %s", lpszFileName + ich);

    LeaveCriticalSection(&lpABPLogon->cs);
}

/*
 -  HrBuildRootHier
 -
 *
 *  Builds up the root hierarchy for the Sample Address Book.  
 *
 *
 */
enum {  ivalPR_DISPLAY_NAME_A = 0,
        ivalPR_ENTRYID,
        ivalPR_DEPTH,
        ivalPR_OBJECT_TYPE,
        ivalPR_DISPLAY_TYPE,
        ivalPR_CONTAINER_FLAGS,
        ivalPR_INSTANCE_KEY,
        ivalPR_AB_PROVIDER_ID,
        cvalMax };

static const SizedSPropTagArray(cvalMax, tagaRootColSet) =
{
    cvalMax,
    {
        PR_DISPLAY_NAME_A,
        PR_ENTRYID,
        PR_DEPTH,
        PR_OBJECT_TYPE,
        PR_DISPLAY_TYPE,
        PR_CONTAINER_FLAGS,
        PR_INSTANCE_KEY,
        PR_AB_PROVIDER_ID
    }
};

HRESULT
HrBuildRootHier(LPABLOGON lpABLogon, LPMAPITABLE * lppMAPITable)
{
    HRESULT hResult;
    SCODE sc;
    SRow sRow;
    SPropValue rgsPropValue[cvalMax];
    ULONG ulInstanceKey = 1;
    char szBuf[MAX_PATH];
    LPABPLOGON lpABPLogon = (LPABPLOGON) lpABLogon;
    DIR_ENTRYID eidRoot =   {   {0, 0, 0, 0},
                                MUIDABSAMPLE,
                                SAMP_VERSION,
                                SAMP_DIRECTORY };
    

    EnterCriticalSection(&lpABPLogon->cs);

    /*
     *  See if we have a TaD yet
     */
    if (!lpABPLogon->lpTDatRoot)
    {
        /* Create a Table Data object */
        if (sc = CreateTable((LPIID) &IID_IMAPITableData,
                    lpABPLogon->lpAllocBuff,
                    lpABPLogon->lpAllocMore,
                    lpABPLogon->lpFreeBuff,
                    lpABPLogon->lpMalloc,
                    0,
                    PR_ENTRYID,
                    (LPSPropTagArray) &tagaRootColSet,
                    &(lpABPLogon->lpTDatRoot)))
        {
            hResult = ResultFromScode(sc);
            goto out;
        }
    }
    /* Constants */

    sRow.cValues = cvalMax;
    sRow.lpProps = rgsPropValue;


    /* First, the Display Name stuff*/

    rgsPropValue[ivalPR_DISPLAY_NAME_A].ulPropTag   = PR_DISPLAY_NAME_A;
    GenerateContainerDN((LPABLOGON) lpABPLogon, szBuf);
    rgsPropValue[ivalPR_DISPLAY_NAME_A].Value.lpszA = szBuf;

    /*
     *  For each SAB logon object associated with it's init object,
     *  we have a unique MAPIUID.  It's the only thing that distinguishes
     *  one SAB entryid from another in the merged hierarchy table that
     *  MAPI generates.
     */

    rgsPropValue[ivalPR_ENTRYID].ulPropTag          = PR_ENTRYID;
    eidRoot.muidID = lpABPLogon->muidID;
    rgsPropValue[ivalPR_ENTRYID].Value.bin.cb       = sizeof(DIR_ENTRYID);
    rgsPropValue[ivalPR_ENTRYID].Value.bin.lpb      = (LPVOID) &eidRoot;


    rgsPropValue[ivalPR_DEPTH].ulPropTag            = PR_DEPTH;
    rgsPropValue[ivalPR_DEPTH].Value.l              = 0;


    rgsPropValue[ivalPR_OBJECT_TYPE].ulPropTag      = PR_OBJECT_TYPE;
    rgsPropValue[ivalPR_OBJECT_TYPE].Value.l        = MAPI_ABCONT;


    rgsPropValue[ivalPR_DISPLAY_TYPE].ulPropTag     = PR_DISPLAY_TYPE;
    rgsPropValue[ivalPR_DISPLAY_TYPE].Value.l       = DT_NOT_SPECIFIC;


    rgsPropValue[ivalPR_CONTAINER_FLAGS].ulPropTag  = PR_CONTAINER_FLAGS;
    rgsPropValue[ivalPR_CONTAINER_FLAGS].Value.l    = AB_RECIPIENTS | AB_UNMODIFIABLE;


    rgsPropValue[ivalPR_INSTANCE_KEY].ulPropTag     = PR_INSTANCE_KEY;
    rgsPropValue[ivalPR_INSTANCE_KEY].Value.bin.cb  = sizeof(ULONG);
    rgsPropValue[ivalPR_INSTANCE_KEY].Value.bin.lpb = (LPBYTE) &ulInstanceKey;


    rgsPropValue[ivalPR_AB_PROVIDER_ID].ulPropTag   = PR_AB_PROVIDER_ID;
    rgsPropValue[ivalPR_AB_PROVIDER_ID].Value.bin.cb= sizeof(MAPIUID);
    rgsPropValue[ivalPR_AB_PROVIDER_ID].Value.bin.lpb= (LPBYTE) &muidSABProviderID;

    hResult = lpABPLogon->lpTDatRoot->lpVtbl->HrModifyRow(
        lpABPLogon->lpTDatRoot, &sRow);

    if (HR_FAILED(hResult))
        goto out;


    /*
     *  Check to see if they want a view returned as well
     */
    if (lppMAPITable)
    {
        /* Get a view from the Table data object */
        hResult =
            lpABPLogon->lpTDatRoot->lpVtbl->HrGetView(
            lpABPLogon->lpTDatRoot,
            NULL,
            NULL,
            0,
            lppMAPITable);
    }

out:

    LeaveCriticalSection(&lpABPLogon->cs);
    
    DebugTraceResult(HrBuildRootHier, hResult);
    return hResult;
}



/*
 *  Checks to see if the file passed in is still the actual file that
 *  should be browsed.
 */
BOOL
FEqualSABFiles( LPABLOGON lpABLogon,
                LPSTR lpszFileName)
{
    LPABPLOGON lpABPLogon = (LPABPLOGON) lpABLogon;
    BOOL fEqual;

    AssertSz(!IsBadReadPtr(lpABPLogon, sizeof(ABPLOGON)), "Bad logon object!\n");
    
    EnterCriticalSection(&lpABPLogon->cs);

    fEqual = !lstrcmpA( lpszFileName, lpABPLogon->lpszFileName );

    LeaveCriticalSection(&lpABPLogon->cs);

    return fEqual;
}
