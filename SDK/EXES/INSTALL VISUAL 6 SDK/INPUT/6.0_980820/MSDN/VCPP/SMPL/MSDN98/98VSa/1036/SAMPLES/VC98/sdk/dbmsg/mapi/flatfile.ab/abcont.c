/***********************************************************************
 *
 *  ABCONT.C
 *
 *  Sample AB directory container object
 *
 *  This file contains the code for implementing the Sample AB
 *  directory container object.
 *
 *  This directory container was retrieved by OpenEntry on the entryid
 *  retrieved from the single row of the hierarchy table (IVTROOT in root.c).
 *
 *  The following routines are implemented in this file:
 *
 *      HrNewSampDirectory
 *      ABC_Release
 *      ABC_SaveChanges
 *      ABC_OpenProperty
 *      ABC_GetContentsTable
 *      ABC_GetHierarchyTable
 *
 *      HrGetDetailsDialog
 *
 *      HrNewABCButton
 *      ABCBUTT_QueryInterface
 *      ABCBUTT_Release
 *      ABCBUTT_Activate
 *      ABCBUTT_GetState
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 *
 ***********************************************************************/

#include "abp.h"
#include "sampabp.rh"
#include <smpab.h>


/*
 *  Proptags used only in this module
 */
#define PR_RADIO_BUTTON_VALUE       PROP_TAG(PT_LONG,   0x6601)
#define PR_BUTTON_PRESS             PROP_TAG(PT_OBJECT, 0x6603)
#define PR_SAB_FILE_TEMP            PROP_TAG(PT_TSTRING,0x6605)


/*
 *  Possible values for PR_RADIO_BUTTON_VALUE
 */
#define RADIO_BUTTON_1_RETURN_VALUE 1
#define RADIO_BUTTON_2_RETURN_VALUE 2
#define RADIO_BUTTON_3_RETURN_VALUE 3
#define RADIO_BUTTON_4_RETURN_VALUE 4



/*
 *  Structure for the 'this'
 */

typedef struct _ABCNT
{
    const ABC_Vtbl FAR * lpVtbl;

    SAB_Wrapped;

    /* details display table */
    LPTABLEDATA lpTDatDetails;

} ABCNT, *LPABCNT;



/*
 *  This is the data structure passed to the
 *  HrNotify method of the Table Data Object
 *  in ABCBUTT_Activate that uniquely identifies
 *  the control in the display table that needs
 *  to be updated.
 */
typedef struct
{
    MAPIUID muid;
    ULONG ulIdc;
} NOTIFDATA;

/*
 *  The actual data.  Note that the control
 *  is specified by IDC_DIR_SAB_FILE_NAME.
 */
NOTIFDATA notifdata =
{MUIDABSAMPLE, IDC_DIR_SAB_FILE_NAME};



/* Display table control structures for the Directory property sheet. */

/*
 *  Edit control that displays the current .SAB file.
 */
DTBLEDIT editDirFileName =
{
    sizeof(DTBLEDIT),
    0,
    MAX_PATH,
    PR_SAB_FILE_TEMP
};


/*
 *  Button control for changing the current .SAB file.
 */
DTBLBUTTON buttonDirChange =
{
    sizeof(DTBLBUTTON),
    0,
    PR_BUTTON_PRESS
};


/*
 *  The next four controls are radio buttons.  Note how they
 *  are related by their use of PR_RADIO_BUTTON_VALUE and
 *  differentiated by RADIO_BUTTON_x_RETURN_VALUE.  Also note
 *  the '4' which says how many controls are in this group
 *  of radio buttons.
 */
DTBLRADIOBUTTON radiobuttonDir1 =
{
    sizeof(DTBLRADIOBUTTON),
    0,
    4,
    PR_RADIO_BUTTON_VALUE,
    RADIO_BUTTON_1_RETURN_VALUE
};

DTBLRADIOBUTTON radiobuttonDir2 =
{
    sizeof(DTBLRADIOBUTTON),
    0,
    4,
    PR_RADIO_BUTTON_VALUE,
    RADIO_BUTTON_2_RETURN_VALUE
};

DTBLRADIOBUTTON radiobuttonDir3 =
{
    sizeof(DTBLRADIOBUTTON),
    0,
    4,
    PR_RADIO_BUTTON_VALUE,
    RADIO_BUTTON_3_RETURN_VALUE
};

DTBLRADIOBUTTON radiobuttonDir4 =
{
    sizeof(DTBLRADIOBUTTON),
    0,
    4,
    PR_RADIO_BUTTON_VALUE,
    RADIO_BUTTON_4_RETURN_VALUE
};



/*
 *  This is the page for the directory details.
 */
DTCTL rgdtctlDirGeneral[] =
{
    /*
     *  directory general propery page
     *  This names the pane for this page.
     *  Although not currently not required in
     *  this version, we expect to require it by
     *  the time MAPI 1.0 ships.
     */
    {DTCT_PAGE, 0, NULL, 0, NULL, 0,
        &dtblpage},

    /* controls and edit control containing sab file name */
    {DTCT_LABEL, 0, NULL, 0, NULL, IDC_STATIC_CONTROL,
        &dtbllabel},
    {DTCT_LABEL, 0, NULL, 0, NULL, IDC_STATIC_CONTROL,
        &dtbllabel},
    {DTCT_EDIT, 0, (LPBYTE) &notifdata, sizeof(NOTIFDATA),
        szNoFilter, IDC_DIR_SAB_FILE_NAME, &editDirFileName},

    /* control and push button for changing sab file */
    {DTCT_LABEL, 0, NULL, 0, NULL, IDC_STATIC_CONTROL,
        &dtbllabel},
    {DTCT_BUTTON, 0, NULL, 0, NULL, IDC_DIR_CHANGE,
        &buttonDirChange},

    /* radio button group box and radio buttons */
    {DTCT_GROUPBOX, 0, NULL, 0, NULL, IDC_STATIC_CONTROL,
        &dtblgroupbox},
    {DTCT_RADIOBUTTON, DT_EDITABLE, NULL, 0, NULL, IDC_DIR_RADIO_1,
        &radiobuttonDir1},
    {DTCT_RADIOBUTTON, DT_EDITABLE, NULL, 0, NULL, IDC_DIR_RADIO_2,
        &radiobuttonDir2},
    {DTCT_RADIOBUTTON, DT_EDITABLE, NULL, 0, NULL, IDC_DIR_RADIO_3,
        &radiobuttonDir3},
    {DTCT_RADIOBUTTON, DT_EDITABLE, NULL, 0, NULL, IDC_DIR_RADIO_4,
        &radiobuttonDir4},
};

/*
 * Display table pages for Directory Details
 */
DTPAGE rgdtpageDir[] =
{
    {
        sizeof(rgdtctlDirGeneral) / sizeof(DTCTL),
        (LPTSTR) MAKEINTRESOURCE(DirGeneralPage),
        "",
        rgdtctlDirGeneral
    }
};

/*
 *  ABCont vtbl is filled in here.
 */
ABC_Vtbl vtblABC =
{
    (ABC_QueryInterface_METHOD *)       ROOT_QueryInterface,
    (ABC_AddRef_METHOD *)               ROOT_AddRef,    
    ABC_Release,
    (ABC_GetLastError_METHOD *)         ROOT_GetLastError,
    ABC_SaveChanges,
    (ABC_GetProps_METHOD *)             WRAP_GetProps,
    (ABC_GetPropList_METHOD *)          WRAP_GetPropList,
    ABC_OpenProperty,
    (ABC_SetProps_METHOD *)             WRAP_SetProps,
    (ABC_DeleteProps_METHOD *)          WRAP_DeleteProps,
    (ABC_CopyTo_METHOD *)               WRAP_CopyTo,
    (ABC_CopyProps_METHOD *)            WRAP_CopyProps,
    (ABC_GetNamesFromIDs_METHOD *)      WRAP_GetNamesFromIDs,
    (ABC_GetIDsFromNames_METHOD *)      WRAP_GetIDsFromNames,
    ABC_GetContentsTable,
    ABC_GetHierarchyTable,
    (ABC_OpenEntry_METHOD *)            ROOT_OpenEntry,
    (ABC_SetSearchCriteria_METHOD *)    ROOT_SetSearchCriteria,
    (ABC_GetSearchCriteria_METHOD *)    ROOT_GetSearchCriteria,
    (ABC_CreateEntry_METHOD *)          ROOT_CreateEntry,
    (ABC_CopyEntries_METHOD *)          ROOT_CopyEntries,
    (ABC_DeleteEntries_METHOD *)        ROOT_DeleteEntries,
    (ABC_ResolveNames_METHOD *)         ROOT_ResolveNames
};



/*
 *  Private functions
 */
HRESULT HrNewABCButton( LPABCNT lpABC,
                        ULONG ulInterfaceOptions,
                        ULONG ulFlags,
                        LPMAPICONTROL FAR * lppMAPICont);

//HRESULT HrGetSearchDialog(LPABCNT lpABC, LPMAPITABLE * lppSearchTable);
HRESULT HrGetDetailsDialog(LPABCNT lpABC, LPMAPITABLE * lppDetailsTable);

/*
 -  NewSampDirectory
 -
 *  Creates a Directory container object.
 *
 *
 */

/*
 *  properties of which I want to track whether or not they've
 *  been changed.
 */
enum { ivalWatchPR_SAB_FILE_TEMP = 0,
        cvalWatchMax };

SizedSPropTagArray(cvalWatchMax, tagaPropsToWatch) =
{
    cvalWatchMax,
    {
        PR_SAB_FILE_TEMP
    }
};


/*
 *  Properties that are initially set on this object
 */
enum {  ivalabcPR_DISPLAY_TYPE = 0,
        ivalabcPR_OBJECT_TYPE,
        ivalabcPR_ENTRYID,
        ivalabcPR_RECORD_KEY,
        ivalabcPR_SEARCH_KEY,
        ivalabcPR_DISPLAY_NAME_A,
        ivalabcPR_CONTAINER_FLAGS,
        ivalabcPR_SAB_FILE,
        ivalabcPR_SAB_FILE_TEMP,
        ivalabcPR_RADIO_BUTTON_VALUE,
        cvalabcMax };


static SizedSPropTagArray( cvalabcMax, tagaABCAccess) =
{
    cvalabcMax,
    {   PR_DISPLAY_TYPE,
        PR_OBJECT_TYPE,
        PR_ENTRYID,
        PR_RECORD_KEY,
        PR_SEARCH_KEY,
        PR_DISPLAY_NAME_A,
        PR_CONTAINER_FLAGS,
        PR_SAB_FILE,
        PR_SAB_FILE_TEMP,
        PR_RADIO_BUTTON_VALUE
      }
};

static ULONG    rgulABCAccess[cvalabcMax] =
{
      IPROP_READONLY | IPROP_CLEAN,     /* PR_DISPLAY_TYPE */
      IPROP_READONLY | IPROP_CLEAN,     /* PR_OBJECT_TYPE */
      IPROP_READONLY | IPROP_CLEAN,     /* PR_ENTRYID */
      IPROP_READONLY | IPROP_CLEAN,     /* PR_RECORD_KEY */
      IPROP_READONLY | IPROP_CLEAN,     /* PR_SEARCH_KEY */
      IPROP_READONLY | IPROP_CLEAN,     /* PR_DISPLAY_NAME_A */
      IPROP_READONLY | IPROP_CLEAN,     /* PR_CONTAINER_FLAGS */
      IPROP_READWRITE | IPROP_CLEAN,    /* PR_SAB_FILE */
      IPROP_READWRITE | IPROP_CLEAN,    /* PR_SAB_FILE_TEMP */
      IPROP_READWRITE | IPROP_CLEAN     /* PR_RADIO_BUTTON_VALUE */
};

HRESULT
HrNewSampDirectory( LPABCONT *          lppABC,
                    ULONG *             lpulObjType,
                    LPABLOGON           lpABLogon,
                    LPCIID              lpInterface,
                    HINSTANCE           hLibrary,
                    LPALLOCATEBUFFER    lpAllocBuff,
                    LPALLOCATEMORE      lpAllocMore,
                    LPFREEBUFFER        lpFreeBuff,
                    LPMALLOC            lpMalloc )
{
    HRESULT hResult = hrSuccess;
    LPABCNT lpABC = NULL;
    SCODE sc;
    LPPROPDATA lpPropData = NULL;
    SPropValue spv[cvalabcMax];
    char szBuf[MAX_PATH];
    MAPIUID * lpMuidLogon;
    LPSTR lpszFileName;
    DIR_ENTRYID eidRoot =   {   {0, 0, 0, 0},
                                MUIDABSAMPLE,
                                SAMP_VERSION,
                                SAMP_DIRECTORY };
    
    /*  Do I support this interface?? */
    if (lpInterface)
    {
        if (memcmp(lpInterface, &IID_IABContainer, sizeof(IID)) &&
            memcmp(lpInterface, &IID_IMAPIContainer, sizeof(IID)) &&
            memcmp(lpInterface, &IID_IMAPIProp, sizeof(IID)) &&
            memcmp(lpInterface, &IID_IUnknown, sizeof(IID)))
        {
            DebugTraceSc(HrNewSampDirectory, MAPI_E_INTERFACE_NOT_SUPPORTED);
            return ResultFromScode(MAPI_E_INTERFACE_NOT_SUPPORTED);
        }
    }

    /*
     *  Allocate space for the directory container structure
     */

    sc = lpAllocBuff( sizeof(ABCNT), (LPVOID *) &lpABC );

    if (FAILED(sc))
    {
        hResult = ResultFromScode(sc);
        goto err;
    }

    lpABC->lpVtbl = &vtblABC;
    lpABC->lcInit = 1;
    lpABC->hResult = hrSuccess;
    lpABC->idsLastError = 0;

    lpABC->hLibrary = hLibrary;
    lpABC->lpAllocBuff = lpAllocBuff;
    lpABC->lpAllocMore = lpAllocMore;
    lpABC->lpFreeBuff = lpFreeBuff;
    lpABC->lpMalloc = lpMalloc;

    lpABC->lpABLogon = lpABLogon;
    lpABC->lpTDatDetails = NULL;

    /*
     *  Create property storage object
     */

    sc = CreateIProp((LPIID) &IID_IMAPIPropData,
        lpAllocBuff,
        lpAllocMore,
        lpFreeBuff,
        lpMalloc,
        &lpPropData);

    if (FAILED(sc))
    {
        hResult = ResultFromScode(sc);
        goto err;
    }

    /*
     *  initialize the muid in the entry id
     */
    lpMuidLogon = LpMuidFromLogon(lpABLogon);
    eidRoot.muidID = *lpMuidLogon;

    /*
     *  Set up initial set of properties associated with this
     *  container.
     */
    spv[ivalabcPR_DISPLAY_TYPE].ulPropTag = PR_DISPLAY_TYPE;
    spv[ivalabcPR_DISPLAY_TYPE].Value.l = DT_NOT_SPECIFIC;

    spv[ivalabcPR_OBJECT_TYPE].ulPropTag = PR_OBJECT_TYPE;
    spv[ivalabcPR_OBJECT_TYPE].Value.l = MAPI_ABCONT;

    spv[ivalabcPR_ENTRYID].ulPropTag = PR_ENTRYID;
    spv[ivalabcPR_ENTRYID].Value.bin.cb = sizeof(DIR_ENTRYID);
    spv[ivalabcPR_ENTRYID].Value.bin.lpb = (LPBYTE) &eidRoot;

    spv[ivalabcPR_RECORD_KEY].ulPropTag = PR_RECORD_KEY;
    spv[ivalabcPR_RECORD_KEY].Value.bin.cb = sizeof(DIR_ENTRYID);
    spv[ivalabcPR_RECORD_KEY].Value.bin.lpb = (LPBYTE) &eidRoot;

    spv[ivalabcPR_SEARCH_KEY].ulPropTag = PR_SEARCH_KEY;
    spv[ivalabcPR_SEARCH_KEY].Value.bin.cb = sizeof(DIR_ENTRYID);
    spv[ivalabcPR_SEARCH_KEY].Value.bin.lpb = (LPBYTE) &eidRoot;


    spv[ivalabcPR_DISPLAY_NAME_A].ulPropTag = PR_DISPLAY_NAME_A;

    GenerateContainerDN(lpABLogon, szBuf);
    spv[ivalabcPR_DISPLAY_NAME_A].Value.lpszA = szBuf;

    spv[ivalabcPR_CONTAINER_FLAGS].ulPropTag = PR_CONTAINER_FLAGS;
    spv[ivalabcPR_CONTAINER_FLAGS].Value.l = AB_RECIPIENTS;

    /*
     *  Get the current .SAB file name from our logon object
     */
    hResult = HrLpszGetCurrentFileName(lpABLogon, &lpszFileName);
    if (HR_FAILED(hResult))
    {
        goto err;
    }

    spv[ivalabcPR_SAB_FILE].ulPropTag = PR_SAB_FILE;
    spv[ivalabcPR_SAB_FILE].Value.lpszA = lpszFileName;

    spv[ivalabcPR_SAB_FILE_TEMP].ulPropTag = PR_SAB_FILE_TEMP;
    spv[ivalabcPR_SAB_FILE_TEMP].Value.lpszA = lpszFileName;

    spv[ivalabcPR_RADIO_BUTTON_VALUE].ulPropTag = PR_RADIO_BUTTON_VALUE;
    spv[ivalabcPR_RADIO_BUTTON_VALUE].Value.l = RADIO_BUTTON_1_RETURN_VALUE;

    /*
     *   Set the default properties
     */
    hResult = lpPropData->lpVtbl->SetProps(lpPropData,
        cvalabcMax,
        spv,
        NULL);

    /*
     *  No longer need this buffer
     */
    lpFreeBuff(lpszFileName);

    if (HR_FAILED(hResult))
    {
        goto err;
    }

    /*
     *  We mark all properties as being CLEAN initially.  Only PR_SAB_FILE,
     *  PR_SAB_FILE_TEMP, and PR_RADIO_BUTTON_VALUE are marked as READWRITE
     *  (Readable/Writable by the client) the others are marked as READONLY
     *  so that the client may not alter them.
     *
     *  Notice that the ABC_SaveChanges code checks the IPROP_DIRTY bit
     *  on PR_SAB_FILE_TEMP to see if the client altered it!
     */
    (void) lpPropData->lpVtbl->HrSetPropAccess(lpPropData,
                                (LPSPropTagArray) &tagaABCAccess,
                                rgulABCAccess);


    InitializeCriticalSection(&lpABC->cs);

    /*  We must AddRef the lpABLogon object since we will be using it
     */
    lpABLogon->lpVtbl->AddRef(lpABLogon);

    lpABC->lpPropData = (LPMAPIPROP) lpPropData;
    *lppABC = (LPABCONT) lpABC;
    *lpulObjType = MAPI_ABCONT;


out:

    DebugTraceResult(HrNewSampDirectory, hResult);
    return hResult;

err:
    /*
     *  free the ABContainer object
     */
    lpFreeBuff( lpABC );

    /*
     *  free the property storage object
     */
    if (lpPropData)
        lpPropData->lpVtbl->Release(lpPropData);

    goto out;
}


/*
 -  ABC_Release
 -
 *  Decrement lcInit.
 *      When lcInit == 0, free up the lpABC structure
 *
 */

STDMETHODIMP_(ULONG)
ABC_Release(LPABCNT lpABC)
{

    long lcInit;
    
    /*
     *  Check to see if it has a jump table
     */
    
    ABC_ValidateObject(Release, lpABC);

    Validate_IUnknown_Release(lpABC);


    EnterCriticalSection(&lpABC->cs);
    lcInit = --lpABC->lcInit;
    LeaveCriticalSection(&lpABC->cs);

    if (lcInit == 0)
    {

        /*
         *  Get rid of the lpPropData
         */
        if (lpABC->lpPropData)
            lpABC->lpPropData->lpVtbl->Release(lpABC->lpPropData);

        /*
         *  Get rid of the details table
         */
        if (lpABC->lpTDatDetails)
            lpABC->lpTDatDetails->lpVtbl->Release(lpABC->lpTDatDetails);

        /*  
         *  Release our reference to the ABLogon object.
         */
        if (lpABC->lpABLogon)
        {
            lpABC->lpABLogon->lpVtbl->Release(lpABC->lpABLogon);
            lpABC->lpABLogon = NULL;
        }

        /*
         *  Destroy the critical section for this object
         */

        DeleteCriticalSection(&lpABC->cs);

        /*
         *  Set the Jump table to NULL.  This way the client will find out
         *  real fast if it's calling a method on a released object.  That is,
         *  the client will crash.  Hopefully, this will happen during the
         *  development stage of the client.
         */
        lpABC->lpVtbl = NULL;

        /*
         *  Need to free the object
         */

        lpABC->lpFreeBuff(lpABC);
        return 0;
    }

    return lpABC->lcInit;

}


/*
 -  ABC_SaveChanges
 -
 *  This is used to save changes associated with the search dialog
 *  in order to get the advanced search restriction and to save changes
 *  associated with the container details dialog.
 *
 */

SPropTagArray tagaSAB_FILE =
{
    1,
    {
        PR_SAB_FILE_TEMP
    }
};

STDMETHODIMP
ABC_SaveChanges(LPABCNT lpABC, ULONG ulFlags)
{
    HRESULT hResult = hrSuccess;
    ULONG ulCount;
    LPSPropValue lpspv = NULL;
    ULONG FAR *rgulAccess = NULL;
    ULONG ulAccess = IPROP_CLEAN | IPROP_READWRITE; 
    LPSPropTagArray ptagaSAB_FILE = (LPSPropTagArray) &tagaSAB_FILE;
    LPPROPDATA lpPropData = (LPPROPDATA) lpABC->lpPropData;

    
    ABC_ValidateObject(SaveChanges, lpABC);

    Validate_IMAPIProp_SaveChanges(lpABC, ulFlags);
    

    EnterCriticalSection(&lpABC->cs);

    /*
     *  Check to see if anyone has dirtied the PR_SAB_FILE_TEMP
     */
    (void) lpPropData->lpVtbl->HrGetPropAccess(lpPropData,
                                        &ptagaSAB_FILE,
                                        &rgulAccess);

    if (!rgulAccess || !((*rgulAccess) & IPROP_DIRTY))
    {
        /*
         *  No, nothing to update then head on out
         */

        goto ret;
    }

    /*
     *  Set back to being clean
     */
    (void )lpPropData->lpVtbl->HrSetPropAccess(lpPropData,
                                        ptagaSAB_FILE,
                                        &ulAccess);

    /*
     * Get the temporary sab file name
     */
    hResult = lpPropData->lpVtbl->GetProps(
        lpPropData,
        &tagaSAB_FILE,
        0,      /* ansi */
        &ulCount,
        &lpspv);
    if (HR_FAILED(hResult))
    {
        goto ret;
    }

    if (lpspv->ulPropTag != PR_SAB_FILE_TEMP)
    {
        /*
         *  There's no reason this property shouldn't be there.
         */
        hResult = ResultFromScode(MAPI_E_CORRUPT_DATA);
        goto ret;
    }

    /*
     *  Save the new name back into the object as PR_SAB_FILE
     */
    lpspv->ulPropTag = PR_SAB_FILE;
    
    hResult = lpPropData->lpVtbl->SetProps(
            lpPropData,
            1,
            lpspv, NULL);

    if (HR_FAILED(hResult))
    {
        /*
         *  Do nothing...  So I couldn't save it away this time...
         */
        hResult = hrSuccess;
        goto ret;
    }

    /*
     *  Update every other object that needs this new information
     */
    hResult = HrReplaceCurrentFileName(lpABC->lpABLogon, lpspv->Value.lpszA);


ret:

    LeaveCriticalSection(&lpABC->cs);

    lpABC->lpFreeBuff(lpspv);
    lpABC->lpFreeBuff(rgulAccess);
    DebugTraceResult(ABC_SaveChanges, hResult);
    return hResult;
}

/*************************************************************************
 *
 -  ABC_OpenProperty
 -
 *
 *  This method allows the opening of the following object:
 *
 *  PR_BUTTON_PRESS  :-  Gets the MAPIControl object associated
 *                       with the button on this container's details.
 *  PR_DETAILS_TABLE :-  Gets the display table associated with
 *                       the details for this container.
 *  PR_SEARCH        :-  Gets the advanced search object associated with
 *                       this container.
 *  PR_CONTAINER_CONTENTS  :-  Same as GetContentsTable()
 *  PR_CONTAINER_HIERARCHY :-  Same as GetHierarchyTable()
 *
 *
 */
STDMETHODIMP
ABC_OpenProperty(LPABCNT lpABC,
    ULONG ulPropTag,
    LPCIID lpiid,
    ULONG ulInterfaceOptions,
    ULONG ulFlags,
    LPUNKNOWN * lppUnk)
{
    HRESULT hResult;

    ABC_ValidateObject(OpenProperty, lpABC);

    Validate_IMAPIProp_OpenProperty(lpABC, ulPropTag, lpiid, ulInterfaceOptions,
                                    ulFlags, lppUnk);
    /*
     *  Check for flags we can't support
     */

    if (ulFlags & (MAPI_CREATE|MAPI_MODIFY))
    {
        hResult = ResultFromScode(E_ACCESSDENIED);
        goto out;
    }
        
    if (ulInterfaceOptions & ~MAPI_UNICODE)
    {
        /*
         *  Only UNICODE flag should be set for any of the objects that might
         *  be returned from this object.
         */
        
        hResult = ResultFromScode(MAPI_E_UNKNOWN_FLAGS);
        goto out;
    }
    
    if ( ulInterfaceOptions & MAPI_UNICODE )
    {
        hResult = ResultFromScode(MAPI_E_BAD_CHARWIDTH);
        DebugTraceArg( ABC_OpenProperty, "bad character width" );
        goto out;
        
    }
    

    /*
     *  Details for this directory entry
     */

    if ((ulPropTag == PR_DETAILS_TABLE) ||
        (ulPropTag == PR_BUTTON_PRESS) ||
        (ulPropTag == PR_CONTAINER_CONTENTS) ||
        (ulPropTag == PR_CONTAINER_HIERARCHY) ||
        (ulPropTag == PR_SEARCH))
    {

        /*
         *  Check to see if they're expecting a table interface for all props but
         *  PR_BUTTON_PRESS.
         */
        if ((ulPropTag != PR_BUTTON_PRESS) &&
            (ulPropTag != PR_SEARCH) &&
            memcmp(lpiid, &IID_IMAPITable, sizeof(IID)))
        {
            hResult = ResultFromScode(MAPI_E_INTERFACE_NOT_SUPPORTED);
            goto out;
        }

        switch (ulPropTag)
        {

        case PR_BUTTON_PRESS:
            {
                /*
                 *  Check to see if they're expecting a generic control interface
                 */
                if (memcmp(lpiid, &IID_IMAPIControl, sizeof(IID)))
                {
                    hResult = ResultFromScode(MAPI_E_INTERFACE_NOT_SUPPORTED);
                    goto out;
                }

                hResult = HrNewABCButton(lpABC,
                    ulInterfaceOptions,
                    ulFlags,
                    (LPMAPICONTROL FAR *) lppUnk);

                break;
            }

        case PR_DETAILS_TABLE:
            {
                hResult = HrGetDetailsDialog(lpABC, (LPMAPITABLE *) lppUnk);
                break;
            }

        case PR_SEARCH:
            {
                /*
                 *  Check to see if they're expecting a generic control interface
                 */
                if (memcmp(lpiid, &IID_IMAPIContainer, sizeof(IID)))
                {
                    hResult = ResultFromScode(MAPI_E_INTERFACE_NOT_SUPPORTED);
                    goto out;
                }

                hResult = HrNewSearch((LPMAPICONTAINER *) lppUnk,
                                        lpABC->lpABLogon,
                                        lpiid,
                                        lpABC->hLibrary,
                                        lpABC->lpAllocBuff,
                                        lpABC->lpAllocMore,
                                        lpABC->lpFreeBuff,
                                        lpABC->lpMalloc);
                break;
            }

        case PR_CONTAINER_CONTENTS:
            {
                hResult = ABC_GetContentsTable(lpABC, 0, (LPMAPITABLE *) lppUnk);
                break;
            }

        case PR_CONTAINER_HIERARCHY:
            {
                hResult = ABC_GetHierarchyTable(lpABC, 0, (LPMAPITABLE *) lppUnk);
                break;
            }

        default:
            Assert(FALSE);
            break;
        }
    } else
    {

        hResult = ResultFromScode(MAPI_E_NO_SUPPORT);
    }

out:

    DebugTraceResult(ABC_OpenProperty, hResult);
    return hResult;
}

/*************************************************************************
 *
 -  ABC_GetContentsTable
 -
 *
 *  Retrieves the IMAPITable that has the contents of this container.
 */
STDMETHODIMP
ABC_GetContentsTable(LPABCNT lpABC, ULONG ulFlags,
    LPMAPITABLE * lppTable)
{

    HRESULT hResult;

    /*
     *  Validate parameters
     */

    ABC_ValidateObject(GetContentsTable, lpABC);

    Validate_IMAPIContainer_GetContentsTable(lpABC, ulFlags, lppTable);
    

    /*
     *  Certain flags are not supported
     */
    if (ulFlags & (MAPI_ASSOCIATED))
    {
        hResult = ResultFromScode(MAPI_E_NO_SUPPORT);
        goto out;
    }
    
    if ( ulFlags & MAPI_UNICODE )
    {
        DebugTraceArg( ABC_GetContentsTable, "Bad character width" );
        hResult = ResultFromScode( MAPI_E_BAD_CHARWIDTH );
        goto out;
    }

    /*
     *  Create the new Contents table
     */
    hResult = HrNewIVTAbc(lppTable,
                          lpABC->lpABLogon,
                          (LPABCONT) lpABC,
                          lpABC->hLibrary,
                          lpABC->lpAllocBuff,
                          lpABC->lpAllocMore,
                          lpABC->lpFreeBuff,
                          lpABC->lpMalloc);

out:

    DebugTraceResult(ABC_GetContentsTable, hResult);
    return hResult;
}

/*
 -  ABC_GetHierarchyTable
 -
 *
 *  There is no hierarchy table associated with this object.
 *
 */
STDMETHODIMP
ABC_GetHierarchyTable(LPABCNT lpABC, ULONG ulFlags,
    LPMAPITABLE * lppTable)
{
    HRESULT hResult;

    /*
     *  Check to see if it has a lpVtbl object member
     */
    if (IsBadReadPtr(lpABC, offsetof(ABCNT, lpVtbl)+sizeof(ABC_Vtbl *)))
    {
        /*
         *  Not large enough
         */
        hResult = MakeResult(E_INVALIDARG);
        DebugTraceResult(ABC_HierarchyTable, hResult);
        return hResult;
    }

    /*
     *  Check to see that the Vtbl is large enough to include this method
     */
    if (IsBadReadPtr(lpABC->lpVtbl,
        offsetof(ABC_Vtbl, GetHierarchyTable)+sizeof(ABC_GetHierarchyTable_METHOD *)))
    {
        /*
         *  Jump table not derived from IUnknown
         */

        hResult = MakeResult(E_INVALIDARG);
        DebugTraceResult(ABC_HierarchyTable, hResult);
        return hResult;
    }

    /*
     *  Check to see if the method is the same
     */
    if (ABC_GetHierarchyTable != lpABC->lpVtbl->GetHierarchyTable)
    {
        /*
         *  Wrong object - the object passed doesn't have this
         *  method.
         */
        hResult = ResultFromScode(E_INVALIDARG);
        DebugTraceResult(ABC_HierarchyTable, hResult);
        return hResult;
    }

    Validate_IMAPIContainer_GetHierarchyTable(lpABC, ulFlags, lppTable);
    
    /*
     *  We don't support this method on this object
     */
    hResult = ResultFromScode(MAPI_E_NO_SUPPORT);

    DebugTraceResult(ABC_GetHierarchyTable, hResult);
    return hResult;
}

/*
 -  HrGetDetailsDialog
 -
 *  Builds a display table for this directory.
 */

HRESULT
HrGetDetailsDialog(LPABCNT lpABC, LPMAPITABLE * lppDetailsTable)
{
    HRESULT hResult;

    if (!lpABC->lpTDatDetails)
    {

        /* Create a display table */
        hResult = BuildDisplayTable(
            lpABC->lpAllocBuff,
            lpABC->lpAllocMore,
            lpABC->lpFreeBuff,
            lpABC->lpMalloc,
            lpABC->hLibrary,
            sizeof(rgdtpageDir) / sizeof(DTPAGE),
            rgdtpageDir,
            0,
            lppDetailsTable,
            &lpABC->lpTDatDetails);
    } else
    {
        hResult = lpABC->lpTDatDetails->lpVtbl->HrGetView(
            lpABC->lpTDatDetails,
            NULL,
            NULL,
            0,
            lppDetailsTable);
    }

    DebugTraceResult(HrGetDetailsDialog, hResult);
    return hResult;
}


/*
 *  Button object for this directory's details dialog
 */


/*
 *  Declaration of IMAPIControl object implementation
 */
#undef  INTERFACE
#define INTERFACE   struct _ABCBUTT

#undef  MAPIMETHOD_
#define MAPIMETHOD_(type,method)    MAPIMETHOD_DECLARE(type,method,ABCBUTT_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IMAPICONTROL_METHODS(IMPL)

#undef  MAPIMETHOD_
#define MAPIMETHOD_(type,method)    MAPIMETHOD_TYPEDEF(type,method,ABCBUTT_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IMAPICONTROL_METHODS(IMPL)

#undef  MAPIMETHOD_
#define MAPIMETHOD_(type,method)    STDMETHOD_(type,method)

DECLARE_MAPI_INTERFACE(ABCBUTT_)
{
    MAPI_IUNKNOWN_METHODS(IMPL)
    MAPI_IMAPICONTROL_METHODS(IMPL)
};

/*
 *
 *  Declaration of structure behind button
 *
 */
typedef struct _ABCBUTT
{
    ABCBUTT_Vtbl FAR * lpVtbl;

    SAB_IUnknown;
    /*
     *  My parent container object
     */
    LPABCNT     lpABC;

} ABCBUTT, *LPABCBUTT;


/*
 *  Fill in the vtbl
 */
ABCBUTT_Vtbl vtblABCBUTT =
{
    ABCBUTT_QueryInterface,
    (ABCBUTT_AddRef_METHOD *)       ROOT_AddRef,
    ABCBUTT_Release,
    (ABCBUTT_GetLastError_METHOD *) ROOT_GetLastError,
    ABCBUTT_Activate,
    ABCBUTT_GetState
};

#define ABCBUTT_ValidateObject(Method, pThis)       \
{                                                   \
    HRESULT hResult;                                \
    if (IsBadReadPtr(pThis, sizeof(ABCBUTT)))       \
    {                                               \
        hResult = ResultFromScode(E_INVALIDARG);    \
        DebugTraceResult(ABCBUTT##_##Method, hResult);  \
        return hResult;                             \
    }                                               \
                                                    \
    if (pThis->lpVtbl != &vtblABCBUTT)              \
    {                                               \
        hResult = ResultFromScode(E_INVALIDARG);    \
        DebugTraceResult(ABCBUTT##_##Method, hResult);  \
        return hResult;                             \
    }                                               \
}



/*
 -  HrNewABCButton
 -
 *  Creates the MAPIControl object that is the code behind the button
 *  on the Sample AB's directory details.
 */
HRESULT
HrNewABCButton( LPABCNT lpABC,
                ULONG ulInterfaceOptions,
                ULONG ulFlags,
                LPMAPICONTROL FAR * lppMAPICont)
{
    LPABCBUTT lpABCButt = NULL;
    SCODE scode;

    scode = lpABC->lpAllocBuff(sizeof(ABCBUTT),(LPVOID *) &lpABCButt);

    if (FAILED(scode))
    {
        DebugTraceSc(HrNewABCButton, scode);
        return ResultFromScode(scode);
    }

    lpABCButt->lpVtbl = &vtblABCBUTT;
    lpABCButt->lcInit = 1;
    lpABCButt->hResult = hrSuccess;
    lpABCButt->idsLastError = 0;

    lpABCButt->hLibrary = lpABC->hLibrary;
    lpABCButt->lpAllocBuff = lpABC->lpAllocBuff;
    lpABCButt->lpAllocMore = lpABC->lpAllocMore;
    lpABCButt->lpFreeBuff = lpABC->lpFreeBuff;
    lpABCButt->lpMalloc = lpABC->lpMalloc;
    lpABCButt->lpABC = lpABC;

    /*
     *  I need my parent object to stay around while this object
     *  does so that I can get to it in my Activate() method.
     *  To do this just AddRef() it.
     */
    lpABC->lpVtbl->AddRef(lpABC);

    InitializeCriticalSection(&lpABCButt->cs);
    
    *lppMAPICont = (LPMAPICONTROL) lpABCButt;

    return hrSuccess;
}


/*************************************************************************
 *
 *
 -  ABCBUTT_QueryInterface
 -
 *
 *  Allows QI'ing to IUnknown and IMAPIControl.
 *
 */
STDMETHODIMP
ABCBUTT_QueryInterface( LPABCBUTT lpABCButt,
                        REFIID lpiid,
                        LPVOID FAR * lppNewObj)
{

    HRESULT hResult = hrSuccess;

    /*  Minimally validate the lpABCButt parameter */

    ABCBUTT_ValidateObject(QueryInterface, lpABCButt);

    Validate_IUnknown_QueryInterface(lpABCButt, lpiid, lppNewObj);

    /*  See if the requested interface is one of ours */

    if (memcmp(lpiid, &IID_IUnknown, sizeof(IID)) &&
        memcmp(lpiid, &IID_IMAPIControl, sizeof(IID)))
    {
        *lppNewObj = NULL;      /* OLE requires zeroing [out] parameter */
        hResult = ResultFromScode(E_NOINTERFACE);
        goto out;
    }

    /*  We'll do this one. Bump the usage count and return a new pointer. */

    EnterCriticalSection(&lpABCButt->cs);
    ++lpABCButt->lcInit;
    LeaveCriticalSection(&lpABCButt->cs);
    
    *lppNewObj = lpABCButt;

out:

    DebugTraceResult(ABCBUTT_QueryInterface, hResult);
    return hResult;
}

/*
 -  ABCBUTT_Release
 -
 *  Releases and cleans up this object
 */
STDMETHODIMP_(ULONG)
ABCBUTT_Release(LPABCBUTT lpABCButt)
{
    long lcInit;

    /*  Minimally validate the lpABCButt parameter */

    if (IsBadReadPtr(lpABCButt, sizeof(ABCBUTT)))
    {
        return 1;
    }

    if (lpABCButt->lpVtbl != &vtblABCBUTT)
    {
        return 1;
    }

    Validate_IUnknown_Release(lpABCButt);

    EnterCriticalSection(&lpABCButt->cs);
    lcInit = --lpABCButt->lcInit;
    LeaveCriticalSection(&lpABCButt->cs);
    
    if (lcInit == 0)
    {

        /*
         *  Release my parent
         */
        lpABCButt->lpABC->lpVtbl->Release(lpABCButt->lpABC);

        /*
         *  Destroy the critical section for this object
         */

        DeleteCriticalSection(&lpABCButt->cs);

        /*
         *  Set the Jump table to NULL.  This way the client will find out
         *  real fast if it's calling a method on a released object.  That is,
         *  the client will crash.  Hopefully, this will happen during the
         *  development stage of the client.
         */
        lpABCButt->lpVtbl = NULL;

        /*
         *  Free the object
         */

        lpABCButt->lpFreeBuff(lpABCButt);
        return 0;
    }

    return lcInit;

}


/*
 -  ABCBUTT_Activate
 -
 *
 *  Activates this control.  In this case, it brings up the common file browsing
 *  dialog and allows the user to pick a different .SAB file.
 *
 *  Note that if all is successful it sends a display table notification.  The UI
 *  will respond to this by updating the particular control that was said to have
 *  changed in the notification.
 */
STDMETHODIMP
ABCBUTT_Activate(LPABCBUTT lpABCButt, ULONG ulFlags,
    ULONG ulUIParam)
{
    HRESULT hResult = hrSuccess;
    OPENFILENAME openfilename;
    char szFileName[MAX_PATH];
    char szDirName[MAX_PATH];
    SPropValue sProp;
    LPSPropValue lpspv = NULL;
    ULONG ulCount, ich;


    /*  Minimally validate the lpABCButt parameter */

    ABCBUTT_ValidateObject(Activate, lpABCButt);

    Validate_IMAPIControl_Activate(lpABCButt, ulFlags, ulUIParam);
    

    if (ulFlags)
    {
        /*
         *  No flags defined for this method
         */
        hResult = ResultFromScode(MAPI_E_UNKNOWN_FLAGS);
        goto out;
    }

    
    /*
     *  First, get the old SAB file name so that it shows up in the
     *  choose file dialog
     */

    hResult = lpABCButt->lpABC->lpPropData->lpVtbl->GetProps(
        lpABCButt->lpABC->lpPropData,
        &tagaSAB_FILE,
        0,              /* ansi */
        &ulCount,
        &lpspv);
    if (HR_FAILED(hResult))
    {
        goto out;
    }

    if (lpspv->ulPropTag != PR_SAB_FILE_TEMP)
    {
        /*
         *  Property wasn't there...
         */
        hResult = ResultFromScode(MAPI_E_CORRUPT_DATA);

        goto out;
    }

    lstrcpyA(szFileName, lpspv->Value.lpszA);

    szDirName[0] = '\0';


    /* get the path name */
    for (ich = lstrlenA(lpspv->Value.lpszA) - 1; ich > 0; ich--)
    {
        if (lpspv->Value.lpszA[ich] == '\\')
        {
            lpspv->Value.lpszA[ich] = '\0';
            break;
        }
        else if (lpspv->Value.lpszA[ich] == ':')
        {
            lpspv->Value.lpszA[ich + 1] = '\0';
            break;
        }
    }

    lstrcpyA(szDirName, lpspv->Value.lpszA);

    /*
     *  Get the user to select one
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
    openfilename.lpstrInitialDir = szDirName;
    openfilename.lpstrTitle = "Sample Address Book";
    openfilename.Flags = OFN_FILEMUSTEXIST |
        OFN_HIDEREADONLY |
        OFN_NOCHANGEDIR;
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
        hResult = hrSuccess;
        goto out;
    }

    /*
     *  Save SAB FileName into the container object
     */

    sProp.ulPropTag = PR_SAB_FILE_TEMP;
    sProp.Value.lpszA = szFileName;

    hResult = lpABCButt->lpABC->lpPropData->lpVtbl->SetProps(
        lpABCButt->lpABC->lpPropData,
        1,
        &sProp,
        NULL);
    if (HR_FAILED(hResult))
    {
        goto out;
    }

    /*
     *  Notify the details table so that everyone with a view open
     *  will get notified
     */
    if (lpABCButt->lpABC->lpTDatDetails)
    {
        sProp.ulPropTag = PR_CONTROL_ID;
        sProp.Value.bin.lpb = (LPBYTE) &notifdata;
        sProp.Value.bin.cb = sizeof(NOTIFDATA);

        hResult = lpABCButt->lpABC->lpTDatDetails->lpVtbl->HrNotify(
            lpABCButt->lpABC->lpTDatDetails,
            0,
            1,
            &sProp);
    }

out:
    lpABCButt->lpFreeBuff(lpspv);
    DebugTraceResult(ABCBUTT_Activate, hResult);
    return hResult;
}

/*
 -  ABCBUTT_GetState
 -
 *  Says whether this control should appear enabled or not at this time.
 *
 */
STDMETHODIMP
ABCBUTT_GetState(LPABCBUTT lpABCButt, ULONG ulFlags,
    ULONG * lpulState)
{

    HRESULT hResult = hrSuccess;

    /*  Minimally validate the lpABCButt parameter */

    ABCBUTT_ValidateObject(GetStatus, lpABCButt);

    Validate_IMAPIControl_GetState(lpABCButt, ulFlags, lpulState);
    
    
    /*
     *  Means that at this time this button should appear enabled.
     */
    *lpulState = MAPI_ENABLED;


    DebugTraceResult(ABCBUTT_GetState, hResult);
    return hResult;
}

