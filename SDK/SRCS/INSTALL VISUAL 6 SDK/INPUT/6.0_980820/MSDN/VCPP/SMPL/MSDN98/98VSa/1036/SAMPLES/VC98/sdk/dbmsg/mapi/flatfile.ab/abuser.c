/***********************************************************************
 *
 *  ABUSER.C
 *
 *  Sample AB Mail User object
 *  This file contains the code for implementing the Sample AB
 *  Mail user.
 *
 *  The mail user has a read-only interface.  Hence a few of the methods
 *  will always return E_ACCESSDENIED.
 *
 *  Typically it would be in this module (particularly HrNewABUser) that
 *  your provider would validate the existance of the entry associated
 *  with a particular entryid.  The Sample Address Book doesn't do this
 *  because it doesn't need to.
 *
 *  The following routines are implemented in this file:
 *
 *  HrNewSampUser
 *  ABU_QueryInterface
 *  ABU_Release
 *  ABU_OpenProperty
 *  HrBuildListBoxTable
 *  HrBuildDDListboxTable
 *  HrBuildComboBoxTable
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 *
 ***********************************************************************/

#include "abp.h"
#include "sampabp.rh"

/*
 *  Defined in ABP.C
 */

#define MAX_ADDRTYPE                        25
#define MAX_EMAIL_ADDRESS                   MAX_PATH
#define MAX_COMBO_EDIT                      25
#define MAX_LISTBOX_ROWS                    25

/* property tags used on details property sheet */
#define PR_CHECKBOX_1_VALUE             PROP_TAG(PT_BOOLEAN,0x6601)
#define PR_CHECKBOX_2_VALUE             PROP_TAG(PT_BOOLEAN,0x6602)
#define PR_CHECKBOX_3_VALUE             PROP_TAG(PT_BOOLEAN,0x6603)
#define PR_LISTBOX_VALUE                PROP_TAG(PT_LONG,0x6604)
#define PR_COMBOBOX_VALUE               PROP_TAG(PT_STRING8,0x6606)
#define PR_DDLISTBOX_VALUE              PROP_TAG(PT_LONG,0x6608)

/* Display table control structures for the General and Options property sheets. */

/*  First Pane "General", this is the information specific about the first
 *  edit control, which is used to display the display name of this user. */
DTBLEDIT editUserDisplayName =
{
    sizeof(DTBLEDIT),
    0,
    MAX_DISPLAY_NAME,
    PR_DISPLAY_NAME_A
};

/*
 *  "General" pane.  This is the information about the email address type associated
 *  with this entry
 */
DTBLEDIT editUserEmailType =
{
    sizeof(DTBLEDIT),
    0,
    MAX_ADDRTYPE,
    PR_ADDRTYPE_A
};


/*
 *  "General" pane.  This is the information about the email address associated with
 *  this entry.
 */
DTBLEDIT editUserEmailAddress =
{
    sizeof(DTBLEDIT),
    0,
    MAX_EMAIL_ADDRESS,
    PR_EMAIL_ADDRESS_A
};


/*
 *  This is the actual definition for the "General" pane.  It lists all the controls
 *  found on it.
 */
DTCTL rgdtctlUserGeneral[] =
{
    /*
     * general property page
     *  MAPI UI will default this first pane to be named "General" in this release.
     *  However, subsequent releases will not include this behaviour.  Because of this
     *  it is stongly suggested that your provider provide a DTCT_PAGE control for each
     *  pane.
     */
    {DTCT_PAGE, 0, NULL, 0, NULL, 0,
        &dtblpage},

    /* display name control and edit control */
    {DTCT_LABEL, 0, NULL, 0, NULL, IDC_STATIC_CONTROL,
        &dtbllabel},
    {DTCT_EDIT, 0, NULL, 0, szNoFilter, IDC_USER_DISPLAY_NAME,
        &editUserDisplayName},

    /* inbox path control and edit control */
    {DTCT_LABEL, 0, NULL, 0, NULL, IDC_STATIC_CONTROL,
        &dtbllabel},
    {DTCT_EDIT, 0, NULL, 0, szNoFilter, IDC_USER_INBOX_PATH,
        &editUserEmailAddress},

    /* address type control and edit control */
    {DTCT_LABEL, 0, NULL, 0, NULL, IDC_STATIC_CONTROL,
        &dtbllabel},
    {DTCT_EDIT, 0, NULL, 0, szAddrTypeFilter, IDC_USER_EMAIL_TYPE,
        &editUserEmailType},
};

/* controls for the options property page */
/*
 *  "Options" property page.  This is the information that allows the
 *  UI to fill in the listbox control on this pane.
 */
 DTBLLBX listbox1 =
{
    0,
    PR_LISTBOX_VALUE,
    PR_LISTBOX_TABLE
};


/*
 *  "Options" property page.  The following three controls define a set of check boxes
 *  that are found on this pane.  Notice that the three prop tags in these structures
 *  are different - compare them to the radio buttons found in ABCONT.C.
 */
 DTBLCHECKBOX checkbox1 =
{
    sizeof(DTBLCHECKBOX),
    0,
    PR_CHECKBOX_1_VALUE
};

 DTBLCHECKBOX checkbox2 =
{
    sizeof(DTBLCHECKBOX),
    0,
    PR_CHECKBOX_2_VALUE
};

 DTBLCHECKBOX checkbox3 =
{
    sizeof(DTBLCHECKBOX),
    0,
    PR_CHECKBOX_3_VALUE
};


/*
 *   "Options" property page.  This is the information required for
 *  the UI to generate a drop down list box.
 */
 DTBLDDLBX ddlistbox1 =
{
    sizeof(DTBLDDLBX),
    PR_DISPLAY_NAME_A,
    PR_DDLISTBOX_VALUE,
    PR_DDLISTBOX_TABLE
};


/*
 *  "Options" property page.  This is the information required for the
 *  UI to generate a combo box control.
 */
 DTBLCOMBOBOX combobox1 =
{
    sizeof(DTBLCOMBOBOX),
    0,
    MAX_COMBO_EDIT,
    PR_COMBOBOX_VALUE,
    PR_COMBOBOX_TABLE
};

/*
 *  This is the actual definition of the "Options" pane.  This lists all the
 *  controls found on that page.
 */
 DTCTL rgdtctlUserAdvanced[] =
{

    /* options property page
     *  This tells the UI what the tab for this pane should say.
     */
    {DTCT_PAGE, 0, NULL, 0, NULL, 0, &dtblpage},

    /* control and listbox */
    {DTCT_LABEL, 0, NULL, 0, NULL,
        IDC_STATIC_CONTROL, &dtbllabel},
    {DTCT_LBX, 0, NULL, 0, NULL,
        IDC_USER_LISTBOX, &listbox1},

    /* group box and radio buttons */
    {DTCT_GROUPBOX, 0, NULL, 0, NULL,
        IDC_STATIC_CONTROL, &dtblgroupbox},
    {DTCT_CHECKBOX, DT_EDITABLE, NULL, 0, NULL,
        IDC_USER_CHECKBOX_1, &checkbox1},
    {DTCT_CHECKBOX, DT_EDITABLE, NULL, 0, NULL,
        IDC_USER_CHECKBOX_2, &checkbox2},
    {DTCT_CHECKBOX, DT_EDITABLE, NULL, 0, NULL,
        IDC_USER_CHECKBOX_3, &checkbox3},

    /* control and drop down listbox */
    {DTCT_LABEL, 0, NULL, 0, NULL,
        IDC_STATIC_CONTROL, &dtbllabel},
    {DTCT_DDLBX, DT_EDITABLE, NULL, 0, NULL,
        IDC_USER_DDLISTBOX, &ddlistbox1},

    /* control and combobox */
    {DTCT_LABEL, 0, NULL, 0, NULL,
        IDC_STATIC_CONTROL, &dtbllabel},
    {DTCT_COMBOBOX, DT_EDITABLE, NULL, 0, szNoFilter,
        IDC_USER_COMBOBOX, &combobox1},
};

/* Display table pages */

/*
 *  This lists the order in which the panes will appear in the UI.  The
 *  UI is driven by a display table which is generated by a call to
 *  BuildDisplayTable() which takes the following DTPAGE structure.
 */
DTPAGE rgdtpage[] =
{
    {
        sizeof(rgdtctlUserGeneral) / sizeof(DTCTL),
        (LPTSTR) MAKEINTRESOURCE(UserGeneralPage),
        "",
        rgdtctlUserGeneral
    },
    {
        sizeof(rgdtctlUserAdvanced) / sizeof(DTCTL),
        (LPTSTR) MAKEINTRESOURCE(UserAdvancedPage),
        "",
        rgdtctlUserAdvanced
    }

};


/*
 *  Definition of the ABUSER object
 */
typedef struct _ABUSER
{
    const ABU_Vtbl FAR * lpVtbl;

    SAB_Wrapped;

    /*
     *   Tables used in options property page
     */
    LPTABLEDATA lpTDatListBox;
    LPTABLEDATA lpTDatDDListBox;
    LPTABLEDATA lpTDatComboBox;


} ABUSER, *LPABUSER;

/*
 *  ABUser vtbl filled in here
 */
const ABU_Vtbl vtblABU =
{

    ABU_QueryInterface,
    (ABU_AddRef_METHOD *)           ROOT_AddRef,
    ABU_Release,
    (ABU_GetLastError_METHOD *)     ROOT_GetLastError,
    (ABU_SaveChanges_METHOD *)      WRAP_SaveChanges,
    (ABU_GetProps_METHOD *)         WRAP_GetProps,
    (ABU_GetPropList_METHOD *)      WRAP_GetPropList,
    ABU_OpenProperty,
    (ABU_SetProps_METHOD *)         WRAP_SetProps,
    (ABU_DeleteProps_METHOD *)      WRAP_DeleteProps,
    (ABU_CopyTo_METHOD *)           WRAP_CopyTo,
    (ABU_CopyProps_METHOD *)        WRAP_CopyProps,
    (ABU_GetNamesFromIDs_METHOD *)  WRAP_GetNamesFromIDs,
    (ABU_GetIDsFromNames_METHOD *)  WRAP_GetIDsFromNames,
};


HRESULT HrBuildListBoxTable(LPABUSER lpABUser);
HRESULT HrBuildDDListBoxTable(LPABUSER lpABUser);
HRESULT HrBuildComboBoxTable(LPABUSER lpABUser);

enum {  ivalusrPR_DISPLAY_TYPE = 0,
        ivalusrPR_OBJECT_TYPE,
        ivalusrPR_ENTRYID,
        ivalusrPR_RECORD_KEY,
        ivalusrPR_DISPLAY_NAME_A,
        ivalusrPR_TRANSMITABLE_DISPLAY_NAME_A,
        ivalusrPR_EMAIL_ADDRESS_A,
        ivalusrPR_ADDRTYPE_A,
        ivalusrPR_SEARCH_KEY,
        ivalusrPR_LISTBOX_VALUE,
        ivalusrPR_CHECKBOX_1_VALUE,
        ivalusrPR_CHECKBOX_2_VALUE,
        ivalusrPR_CHECKBOX_3_VALUE,
        ivalusrPR_DDLISTBOX_VALUE,
        ivalusrPR_COMBOBOX_VALUE,
        ivalusrPR_TEMPLATEID,
        cvalusrMax };

static SizedSPropTagArray( cvalusrMax, tagaABUAccess) =
{
    cvalusrMax,
    {   PR_DISPLAY_TYPE,
        PR_OBJECT_TYPE,
        PR_ENTRYID,
        PR_RECORD_KEY,
        PR_DISPLAY_NAME_A,
        PR_TRANSMITABLE_DISPLAY_NAME_A,
        PR_EMAIL_ADDRESS_A,
        PR_ADDRTYPE_A,
        PR_SEARCH_KEY,
        PR_LISTBOX_VALUE,
        PR_CHECKBOX_1_VALUE,
        PR_CHECKBOX_2_VALUE,
        PR_CHECKBOX_3_VALUE,
        PR_DDLISTBOX_VALUE,
        PR_COMBOBOX_VALUE,
        PR_TEMPLATEID
      }
};

static ULONG    rgulABUAccess[cvalusrMax] =
{
    IPROP_READONLY | IPROP_CLEAN,   /* PR_DISPLAY_TYPE */
    IPROP_READONLY | IPROP_CLEAN,   /* PR_OBJECT_TYPE */
    IPROP_READONLY | IPROP_CLEAN,   /* PR_ENTRYID */
    IPROP_READONLY | IPROP_CLEAN,   /* PR_RECORD_KEY */
    IPROP_READONLY | IPROP_CLEAN,   /* PR_DISPLAY_NAME_A */
    IPROP_READONLY | IPROP_CLEAN,   /* PR_TRANSMITABLE_DISPLAY_NAME_A */
    IPROP_READONLY | IPROP_CLEAN,   /* PR_EMAIL_ADDRESS_A */
    IPROP_READONLY | IPROP_CLEAN,   /* PR_ADDRTYPE_A */
    IPROP_READONLY | IPROP_CLEAN,   /* PR_SEARCH_KEY */
    IPROP_READWRITE | IPROP_CLEAN,  /* PR_LISTBOX_VALUE */
    IPROP_READWRITE | IPROP_CLEAN,  /* PR_CHECKBOX_1_VALUE */
    IPROP_READWRITE | IPROP_CLEAN,  /* PR_CHECKBOX_2_VALUE */
    IPROP_READWRITE | IPROP_CLEAN,  /* PR_CHECKBOX_3_VALUE */
    IPROP_READWRITE | IPROP_CLEAN,  /* PR_DDLISTBOX_VALUE */
    IPROP_READWRITE | IPROP_CLEAN,  /* PR_COMBOBOX_VALUE */
    IPROP_READONLY | IPROP_CLEAN    /* PR_TEMPLATEID */
};


/*************************************************************************
 *
 -  HrNewSampUser
 -
 *  Creates the IMAPIProp associated with a mail user.
 *
 *
 */
HRESULT
HrNewSampUser(  LPMAILUSER *        lppMAPIPropEntry,
                ULONG *             lpulObjType,
                ULONG               cbEntryID,
                LPENTRYID           lpEntryID,
                LPABLOGON           lpABPLogon,
                LPCIID              lpInterface,
                HINSTANCE           hLibrary,
                LPALLOCATEBUFFER    lpAllocBuff,
                LPALLOCATEMORE      lpAllocMore,
                LPFREEBUFFER        lpFreeBuff,
                LPMALLOC            lpMalloc )
{
    LPABUSER lpABUser = NULL;
    SCODE sc;
    HRESULT hr = hrSuccess;
    LPPROPDATA lpPropData = NULL;
    SPropValue spv[cvalusrMax];
    ULONG cbT = 0;
    LPBYTE lpbT = NULL;
    LPSTR lpszEMA = NULL;

    /*  Do I support this interface?? */
    if (lpInterface)
    {
        if (memcmp(lpInterface, &IID_IMailUser, sizeof(IID)) &&
            memcmp(lpInterface, &IID_IMAPIProp, sizeof(IID)) &&
            memcmp(lpInterface, &IID_IUnknown, sizeof(IID)))
        {
            DebugTraceSc(HrNewSampUser, MAPI_E_INTERFACE_NOT_SUPPORTED);
            return ResultFromScode(MAPI_E_INTERFACE_NOT_SUPPORTED);
        }
    }
    /*
     *  Allocate space for the ROOT structure
     */
    sc = lpAllocBuff(sizeof(ABUSER), (LPVOID *) &lpABUser);
    if (FAILED(sc))
    {
        hr = ResultFromScode(sc);
        goto err;
    }

    lpABUser->lpVtbl = &vtblABU;
    lpABUser->lcInit = 1;
    lpABUser->hResult = hrSuccess;
    lpABUser->idsLastError = 0;

    lpABUser->hLibrary = hLibrary;
    lpABUser->lpAllocBuff = lpAllocBuff;
    lpABUser->lpAllocMore = lpAllocMore;
    lpABUser->lpFreeBuff = lpFreeBuff;
    lpABUser->lpMalloc = lpMalloc;

    lpABUser->lpABLogon = lpABPLogon;
    lpABUser->lpTDatListBox = NULL;
    lpABUser->lpTDatDDListBox = NULL;
    lpABUser->lpTDatComboBox = NULL;

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
        hr = ResultFromScode(sc);
        goto err;
    }

    /*
     *  Set up initial set of properties associated with this
     *  mailuser.
     */

    /*
     *  Easy ones first
     */

    spv[ivalusrPR_DISPLAY_TYPE].ulPropTag = PR_DISPLAY_TYPE;
    spv[ivalusrPR_DISPLAY_TYPE].Value.l = DT_MAILUSER;

    spv[ivalusrPR_OBJECT_TYPE].ulPropTag = PR_OBJECT_TYPE;
    spv[ivalusrPR_OBJECT_TYPE].Value.l = MAPI_MAILUSER;

    spv[ivalusrPR_ENTRYID].ulPropTag = PR_ENTRYID;
    spv[ivalusrPR_ENTRYID].Value.bin.cb = sizeof(USR_ENTRYID);
    spv[ivalusrPR_ENTRYID].Value.bin.lpb = (LPBYTE) lpEntryID;

    /*
     *  Now the calculated props
     */

    spv[ivalusrPR_RECORD_KEY].ulPropTag = PR_RECORD_KEY;
    spv[ivalusrPR_RECORD_KEY].Value.bin.cb = sizeof(USR_ENTRYID);
    spv[ivalusrPR_RECORD_KEY].Value.bin.lpb = (LPBYTE) lpEntryID;

    spv[ivalusrPR_DISPLAY_NAME_A].ulPropTag = PR_DISPLAY_NAME_A;
    spv[ivalusrPR_DISPLAY_NAME_A].Value.lpszA = ((LPUSR_ENTRYID) lpEntryID)->abcrec.rgchDisplayName;

    /* Should always be the same as PR_DISPLAY_NAME */
    spv[ivalusrPR_TRANSMITABLE_DISPLAY_NAME_A].ulPropTag = PR_TRANSMITABLE_DISPLAY_NAME_A;
    spv[ivalusrPR_TRANSMITABLE_DISPLAY_NAME_A].Value.lpszA = ((LPUSR_ENTRYID) lpEntryID)->abcrec.rgchDisplayName;

    spv[ivalusrPR_EMAIL_ADDRESS_A].ulPropTag = PR_EMAIL_ADDRESS_A;
    spv[ivalusrPR_EMAIL_ADDRESS_A].Value.lpszA = ((LPUSR_ENTRYID) lpEntryID)->abcrec.rgchEmailAddress;
    lpszEMA = ((LPUSR_ENTRYID) lpEntryID)->abcrec.rgchEmailAddress;

    spv[ivalusrPR_ADDRTYPE_A].ulPropTag = PR_ADDRTYPE_A;
    spv[ivalusrPR_ADDRTYPE_A].Value.lpszA = lpszEMT;

    /*
     *  Build the search key...
     */
    /*  Search keys for mailable recipients that have email addresses are
     *  defined as "EmailType':'EmailAddress\0".  We do the +2 for the ':' and
     *  '\0'.
     */
    cbT = lstrlenA(lpszEMA) + lstrlenA(lpszEMT) + 2;

    sc = lpAllocBuff( cbT, (LPVOID *) &lpbT );
    if (FAILED(sc))
    {
        hr = ResultFromScode(sc);
        goto err;
    }
    lstrcpyA((LPSTR) lpbT, lpszEMT);
    lstrcatA((LPSTR) lpbT, ":");
    lstrcatA((LPSTR) lpbT, lpszEMA);
    CharUpperBuff((LPTSTR) lpbT, (UINT) cbT);

    spv[ivalusrPR_SEARCH_KEY].ulPropTag = PR_SEARCH_KEY;
    spv[ivalusrPR_SEARCH_KEY].Value.bin.cb = cbT;
    spv[ivalusrPR_SEARCH_KEY].Value.bin.lpb = lpbT;

    /* properties used by the options property page */
    spv[ivalusrPR_LISTBOX_VALUE].ulPropTag = PR_LISTBOX_VALUE;
    spv[ivalusrPR_LISTBOX_VALUE].Value.l = 5;

    spv[ivalusrPR_CHECKBOX_1_VALUE].ulPropTag = PR_CHECKBOX_1_VALUE;
    spv[ivalusrPR_CHECKBOX_1_VALUE].Value.b = TRUE;

    spv[ivalusrPR_CHECKBOX_2_VALUE].ulPropTag = PR_CHECKBOX_2_VALUE;
    spv[ivalusrPR_CHECKBOX_2_VALUE].Value.b = FALSE;

    spv[ivalusrPR_CHECKBOX_3_VALUE].ulPropTag = PR_CHECKBOX_3_VALUE;
    spv[ivalusrPR_CHECKBOX_3_VALUE].Value.b = TRUE;

    spv[ivalusrPR_DDLISTBOX_VALUE].ulPropTag = PR_DDLISTBOX_VALUE;
    spv[ivalusrPR_DDLISTBOX_VALUE].Value.l = 10;

    spv[ivalusrPR_COMBOBOX_VALUE].ulPropTag = PR_COMBOBOX_VALUE;
    spv[ivalusrPR_COMBOBOX_VALUE].Value.lpszA = "ComboBox item 10";

    /*
     *  Note that we're using our entryID for our templateID.
     *  This is a really simple way to implement templateIDs.
     *  (See TID.C)
     */
    spv[ivalusrPR_TEMPLATEID].ulPropTag = PR_TEMPLATEID;
    spv[ivalusrPR_TEMPLATEID].Value.bin.cb = sizeof(USR_ENTRYID);
    spv[ivalusrPR_TEMPLATEID].Value.bin.lpb = (LPBYTE) lpEntryID;

    /*
     *   Set the default properties
     */
    hr = lpPropData->lpVtbl->SetProps(
        lpPropData,
        cvalusrMax,
        spv,
        NULL);

    if (HR_FAILED(hr))
    {
        goto err;
    }

    /*
     *  Although this object is basically read only, we wanted to show
     *  an example of how the check-boxes and other controls on the
     *  "Options" pane work.  If we had set this object to be read only,
     *  the values behind those controls would have been static.
     */
    (void)lpPropData->lpVtbl->HrSetObjAccess(lpPropData, IPROP_READWRITE);

    /*
     *  Set the client access rights to the various properties.  Notice
     *  that everything is READONLY except for the properties related to
     *  the controls on the "Options" pane.
     *
     *  All properties are intially marked as CLEAN.
     */
    (void) lpPropData->lpVtbl->HrSetPropAccess(lpPropData,
                                (LPSPropTagArray) &tagaABUAccess,
                                rgulABUAccess);

    lpABUser->lpPropData = (LPMAPIPROP) lpPropData;

    InitializeCriticalSection(&lpABUser->cs);

    /*  We must AddRef the lpABPLogon object since we will be using it
     */
    lpABPLogon->lpVtbl->AddRef(lpABPLogon);

    *lppMAPIPropEntry = (LPVOID) lpABUser;
    *lpulObjType = MAPI_MAILUSER;

out:
    lpFreeBuff(lpbT);

    DebugTraceResult(HrNewSampUser, hr);
    return hr;

err:
    if (lpPropData)
        lpPropData->lpVtbl->Release(lpPropData);

    lpFreeBuff(lpABUser);

    goto out;

}


/*************************************************************************
 *
 *
 -  ABU_QueryInterface
 -
 *  Allows QI'ing to only IUnknown, IMAPIProp, and IMailUser.
 *
 *  This method is reused in TID.C, OOTID.C, and ABOOSER.C.  Hence the
 *  difference in checking of the 'this' pointer from other methods within
 *  this object.
 */
STDMETHODIMP
ABU_QueryInterface(LPABUSER lpABUser,
    REFIID lpiid,
    LPVOID FAR * lppNewObj)
{

    HRESULT hr = hrSuccess;

    
    /*  Minimally check the lpABUser object
     *  Can't do any more extensive checking that this because this method is reused
     *  in OOUSER.C.
     */

    if (IsBadReadPtr(lpABUser, offsetof(ABUSER, lpVtbl)+sizeof(ABU_Vtbl *)))
    {
        hr = ResultFromScode(E_INVALIDARG);
        goto out;
    }
        
    if (IsBadReadPtr(lpABUser->lpVtbl,
                     offsetof(ABU_Vtbl, QueryInterface)+sizeof(ABU_QueryInterface_METHOD *)))
    {
        hr = ResultFromScode(E_INVALIDARG);
        goto out;
    }
        
    if (ABU_QueryInterface != lpABUser->lpVtbl->QueryInterface)
    {
        hr = ResultFromScode(E_INVALIDARG);
        goto out;
    }

    Validate_IUnknown_QueryInterface(lpABUser, lpiid, lppNewObj);

    
    /*  See if the requested interface is one of ours */

    if (memcmp(lpiid, &IID_IUnknown, sizeof(IID)) &&
        memcmp(lpiid, &IID_IMAPIProp, sizeof(IID)) &&
        memcmp(lpiid, &IID_IMailUser, sizeof(IID)))
    {
        *lppNewObj = NULL;      /* OLE requires zeroing [out] parameter */
        hr = ResultFromScode(E_NOINTERFACE);
        goto out;
    }

    /*  Bump the usage count and return same object pointer. */

    EnterCriticalSection(&lpABUser->cs);
    ++lpABUser->lcInit;
    LeaveCriticalSection(&lpABUser->cs);
    
    *lppNewObj = lpABUser;

out:

    DebugTraceResult(ABU_QueryInterface, hr);
    return hr;
}


/**************************************************
 *
 -  ABU_Release
 -
 *      Decrement lcInit.
 *      When lcInit == 0, free up the lpABUser structure
 *
 */
STDMETHODIMP_(ULONG)
ABU_Release(LPABUSER lpABUser)
{

    LONG lcInit;
    /*
     *  Check to see if it's big enough to hold this object
     */
    if (IsBadReadPtr(lpABUser, sizeof(ABUSER)))
    {
        /*
         *  Not large enough
         */
        return 1;
    }

    /*
     *  Check to see that it's the correct vtbl
     */
    if (lpABUser->lpVtbl != &vtblABU)
    {
        /*
         *  Not my vtbl
         */
        return 1;
    }

    Validate_IUnknown_Release(lpABUser);


    EnterCriticalSection(&lpABUser->cs);
    lcInit = --lpABUser->lcInit;
    LeaveCriticalSection(&lpABUser->cs);

    if (lcInit == 0)
    {

        /*
         *  Get rid of the lpPropData
         */

        lpABUser->lpPropData->lpVtbl->Release(lpABUser->lpPropData);

        /*
         *  Get rid of the tables used by the options property page
         */

        if (lpABUser->lpTDatListBox)
            lpABUser->lpTDatListBox->lpVtbl->Release(lpABUser->lpTDatListBox);

        if (lpABUser->lpTDatDDListBox)
            lpABUser->lpTDatDDListBox->lpVtbl->Release(lpABUser->lpTDatDDListBox);

        if (lpABUser->lpTDatComboBox)
            lpABUser->lpTDatComboBox->lpVtbl->Release(lpABUser->lpTDatComboBox);

        /*  
         *  Release our reference to the ABLogon object.
         */
        if (lpABUser->lpABLogon)
        {
            lpABUser->lpABLogon->lpVtbl->Release(lpABUser->lpABLogon);
            lpABUser->lpABLogon = NULL;
        }

        /*
         *  Destroy the critical section for this object
         */

        DeleteCriticalSection(&lpABUser->cs);

        /*
         *  Set the vtbl to NULL.  This way the client will find out
         *  real fast if it's calling a method on a released object.  That is,
         *  the client will crash.  Hopefully, this will happen during the
         *  development stage of the client.
         */

        lpABUser->lpVtbl = NULL;

        /*
         *  Need to free the object
         */

        lpABUser->lpFreeBuff( lpABUser );
        return 0;
    }

    return lcInit;

}

/*************************************************************************
 *
 -  ABU_OpenProperty
 -
 *
 *  This is how we get the display table associated with this users
 *  details screen.  This is also how we get the tables which are needed
 *  to fill out the "Options" property pane.
 */
STDMETHODIMP
ABU_OpenProperty(LPABUSER lpABUser,
    ULONG ulPropTag,
    LPCIID lpiid,
    ULONG ulInterfaceOptions,
    ULONG ulFlags,
    LPUNKNOWN * lppUnk)
{

    HRESULT hResult;

    ABU_ValidateObject(OpenProperty, lpABUser);
    
    Validate_IMAPIProp_OpenProperty(lpABUser, ulPropTag, lpiid,
                    ulInterfaceOptions, ulFlags, lppUnk);


    if (ulInterfaceOptions & ~MAPI_UNICODE )
    {
        /*
         *  Only the Unicode flag should be set for any of the objects that might
         *  be returned from this object.
         */
        
        hResult = ResultFromScode(MAPI_E_UNKNOWN_FLAGS);

        DebugTraceResult(ABU_OpenProperty, hResult);
        return hResult;
    }
    
    if ( ulInterfaceOptions & MAPI_UNICODE )
    {
        hResult = ResultFromScode(MAPI_E_BAD_CHARWIDTH);
        DebugTraceResult(ABU_OpenProperty, hResult);
        return hResult;
        
    }
    
    if (ulFlags & MAPI_CREATE)
    {
        hResult = ResultFromScode(E_ACCESSDENIED);
        
        DebugTraceResult(ABU_OpenProperty, hResult);
        return hResult;
    }
    

    if (ulPropTag == PR_DETAILS_TABLE ||
        ulPropTag == PR_LISTBOX_TABLE ||
        ulPropTag == PR_DDLISTBOX_TABLE ||
        ulPropTag == PR_COMBOBOX_TABLE)
    {
        /* Check to see if they're expecting a table interface */

        if (memcmp(lpiid, &IID_IMAPITable, sizeof(IID)))
        {
            hResult = ResultFromScode(MAPI_E_INTERFACE_NOT_SUPPORTED);
            return hResult;
        }
    }



    EnterCriticalSection(&lpABUser->cs);



    switch (ulPropTag)
    {
        case PR_DETAILS_TABLE:
        {

            /* Looking for the display table*/
            /* Create a display table */

            hResult = BuildDisplayTable(
                lpABUser->lpAllocBuff,
                lpABUser->lpAllocMore,
                lpABUser->lpFreeBuff,
                lpABUser->lpMalloc,
                lpABUser->hLibrary,
                sizeof(rgdtpage) / sizeof(DTPAGE),
                rgdtpage,
                0,
                (LPMAPITABLE *) lppUnk,
                NULL);

            break;
        }

        case PR_LISTBOX_TABLE:
        {
            
            /*
             *  Looking for the table that fills the listbox
             *  on the Options pane on this user's details
             */

            /*
             *  If we don't already have a Table Data Object, make one.
             */
            if (!lpABUser->lpTDatListBox)
            {
                hResult = HrBuildListBoxTable(lpABUser);
                if (HR_FAILED(hResult))
                    goto out;
            }

            Assert(lpABUser->lpTDatListBox);

            /* Get a view from the table data object*/
            hResult = lpABUser->lpTDatListBox->lpVtbl->HrGetView(
                        lpABUser->lpTDatListBox,
                        NULL,
                        NULL,
                        0,
                        (LPMAPITABLE *) lppUnk);

            break;
        }

        case PR_DDLISTBOX_TABLE:
        {
            /*
             *  Locking for the table that fills the drop down listbox
             *  on the Options pane on this user's details.
             */

            if (!lpABUser->lpTDatDDListBox)
            {
                hResult = HrBuildDDListBoxTable(lpABUser);
                if (HR_FAILED(hResult))
                    goto out;
            }

            Assert(lpABUser->lpTDatDDListBox);

            /* Get a view from the table data object */
            hResult = lpABUser->lpTDatDDListBox->lpVtbl->HrGetView(
                        lpABUser->lpTDatDDListBox,
                        NULL,
                        NULL,
                        0,
                        (LPMAPITABLE *) lppUnk);


            break;
        }

        case PR_COMBOBOX_TABLE:
        {
            /*
             *  Locking for the table that fills the combobox
             *  on the Options pane on this user's details.
             */

            if (!lpABUser->lpTDatComboBox)
            {
                hResult = HrBuildComboBoxTable(lpABUser);
                if (HR_FAILED(hResult))
                    goto out;
            }

            Assert(lpABUser->lpTDatComboBox);

            /* Get a view from the table data object */
            hResult =
                lpABUser->lpTDatComboBox->lpVtbl->HrGetView(
                lpABUser->lpTDatComboBox,
                NULL,
                NULL,
                0,
                (LPMAPITABLE *) lppUnk);

            break;
        }

        default:
        {
            hResult = ResultFromScode(MAPI_E_NO_SUPPORT);

            break;
        }
    }

out:

    LeaveCriticalSection(&lpABUser->cs);
    
    DebugTraceResult(ABU_OpenProperty, hResult);
    return hResult;

}

/**********************************************************************
 *
 *  Private functions
 */

/*
 *  Default column set for listbox table
 */

enum {  ivallbxPR_DISPLAY_NAME_A = 0,
        ivallbxPR_COMMENT_A,
        ivallbxPR_ENTRYID,
        ivallbxPR_DISPLAY_TYPE,
        ivallbxPR_LISTBOX_VALUE,
        ivallbxPR_INSTANCE_KEY,
        cvallbxMax };

const SizedSPropTagArray(cvallbxMax, tagaColSetListBox) =
{
    cvallbxMax,
    {
        PR_DISPLAY_NAME_A,
        PR_COMMENT_A,
        PR_ENTRYID,
        PR_DISPLAY_TYPE,
        PR_LISTBOX_VALUE,
        PR_INSTANCE_KEY
    }
};

typedef struct _options_entryid
{
    BYTE abFlags[4];
    MAPIUID muid;
    ULONG ulVersion;
    ULONG ulType;
    ULONG ulRowNumber;
} OPTIONS_ENTRYID, *LPOPTIONS_ENTRYID;

#define CBOPTIONS_ENTRYID sizeof(OPTIONS_ENTRYID)

OPTIONS_ENTRYID OptionsEntryID =
{
    {0, 0, 0, 0},
    MUIDABSAMPLE,
    SAMP_VERSION,
    SAMP_UNKNOWN,
    0
};

HRESULT
HrBuildListBoxTable(LPABUSER lpABUser)
{
    SCODE sc;
    HRESULT hResult;
    SPropValue rgsPropValue[cvallbxMax];
    SRow sRow;
    char szDisplay[MAX_FMT_DET_DN+2]; /* +2 for digits */
    char szComment[MAX_FMT_DET_COMMENT+2]; /* +2 for digits */
    char szFmtDisplay[MAX_FMT_DET_DN];
    char szFmtComment[MAX_FMT_DET_COMMENT];
    LPSTR pszFmtComment = (LPSTR) szFmtComment;
    LPSTR pszFmtDisplay = (LPSTR) szFmtDisplay;

    ULONG uliRow;

    /*
     *  Get string resources
     */
    sc = ScLoadString(  IDS_FMT_DET_DN,
                        MAX_FMT_DET_DN,
                        NULL,
                        lpABUser->hLibrary,
                        (LPSTR *) &pszFmtDisplay);

    if (FAILED(sc))
    {
        hResult = ResultFromScode(sc);
        goto out;
    }

    sc = ScLoadString(  IDS_FMT_DET_COMMENT,
                        MAX_FMT_DET_COMMENT,
                        NULL,
                        lpABUser->hLibrary,
                        (LPSTR *) &pszFmtComment);
    if (FAILED(sc))
    {
        hResult = ResultFromScode(sc);
        goto out;
    }

    /* Create a Table Data object */
    sc = CreateTable(
        (LPIID) &IID_IMAPITableData,
        lpABUser->lpAllocBuff,
        lpABUser->lpAllocMore,
        lpABUser->lpFreeBuff,
        lpABUser->lpMalloc,
        0,
        PR_DISPLAY_NAME_A,
        (LPSPropTagArray) &tagaColSetListBox,
        &(lpABUser->lpTDatListBox));

    if (FAILED(sc))
    {
        hResult = ResultFromScode(sc);
        goto out;
    }

    /* constants */
    sRow.cValues = cvallbxMax;
    sRow.lpProps = rgsPropValue;

    /*
     *  Although assignment of szDisplay and szComment happen here, their actual
     *  values happen below in the for loop.
     */
    rgsPropValue[ivallbxPR_DISPLAY_NAME_A].ulPropTag = PR_DISPLAY_NAME_A;
    rgsPropValue[ivallbxPR_DISPLAY_NAME_A].Value.lpszA = szDisplay;

    rgsPropValue[ivallbxPR_COMMENT_A].ulPropTag = PR_COMMENT_A;
    rgsPropValue[ivallbxPR_COMMENT_A].Value.lpszA = szComment;


    /*
     *  For this release of MAPI the following two properties are required
     *  for all listboxes exposed in any details dialog.  This requirement is
     *  scheduled to be removed before ship
     */
    rgsPropValue[ivallbxPR_ENTRYID].ulPropTag = PR_ENTRYID;
    rgsPropValue[ivallbxPR_ENTRYID].Value.bin.lpb = (LPBYTE) &OptionsEntryID;
    rgsPropValue[ivallbxPR_ENTRYID].Value.bin.cb = CBOPTIONS_ENTRYID;

    rgsPropValue[ivallbxPR_DISPLAY_TYPE].ulPropTag = PR_DISPLAY_TYPE;
    rgsPropValue[ivallbxPR_DISPLAY_TYPE].Value.l = 0;  /*  There are no defines for this yet */


    rgsPropValue[ivallbxPR_LISTBOX_VALUE].ulPropTag = PR_LISTBOX_VALUE;

    rgsPropValue[ivallbxPR_INSTANCE_KEY].ulPropTag = PR_INSTANCE_KEY;
    rgsPropValue[ivallbxPR_INSTANCE_KEY].Value.bin.cb = sizeof(ULONG);

    /* fill up the table */
    for (uliRow = 0; uliRow < MAX_LISTBOX_ROWS; uliRow++)
    {
        wsprintfA(szDisplay, szFmtDisplay, uliRow);
        wsprintfA(szComment, szFmtComment, uliRow);

        OptionsEntryID.ulRowNumber = uliRow;
        rgsPropValue[ivallbxPR_LISTBOX_VALUE].Value.l = uliRow;

        rgsPropValue[ivallbxPR_INSTANCE_KEY].Value.bin.lpb = (LPBYTE) &uliRow;

        hResult = lpABUser->lpTDatListBox->lpVtbl->HrModifyRow(
            lpABUser->lpTDatListBox,
            &sRow);
        if (HR_FAILED(hResult))
        {
            /*
             *  Mask errors here...
             *  We want to do this because it's probibly still a valid
             *  table data object that I can get views from.  Most likely
             *  just some of the rows will be missing...
             */
            hResult = hrSuccess;
            break;
        }
        /*
         *  get rid of any warnings
         */
        hResult = hrSuccess;
    }


out:

    DebugTraceResult(hrBuildListBoxTable, hResult);
    return hResult;
}

/*
 *  Default column set for the dropdown listbox table
 */

enum {  ivalddPR_DISPLAY_NAME_A = 0,
        ivalddPR_ENTRYID,
        ivalddPR_DISPLAY_TYPE,
        ivalddPR_DDLISTBOX_VALUE,
        ivalddPR_INSTANCE_KEY,
        cvalddMax };

const SizedSPropTagArray(cvalddMax, tagaColSetDDListBox) =
{
    cvalddMax,
    {
        PR_DISPLAY_NAME_A,
        PR_ENTRYID,
        PR_DISPLAY_TYPE,
        PR_DDLISTBOX_VALUE,
        PR_INSTANCE_KEY
    }
};

HRESULT
HrBuildDDListBoxTable(LPABUSER lpABUser)
{
    SCODE sc;
    HRESULT hResult;
    SPropValue rgsPropValue[cvalddMax];
    SRow sRow;
    char szFmtDisplay[MAX_FMT_DD_DN];
    char szDisplay[MAX_FMT_DD_DN+2]; /* +2 for digits */
    ULONG uliRow;
    LPSTR pszFmtDisplay = (LPSTR) szFmtDisplay;

    /*
     *  Get resource strings
     */
    sc = ScLoadString(  IDS_FMT_DD_DN,
                        MAX_FMT_DD_DN,
                        NULL,
                        lpABUser->hLibrary,
                        (LPSTR *)&pszFmtDisplay );
    if (FAILED(sc))
    {
        hResult = ResultFromScode(sc);
        goto out;
    }

    /* Create a Table Data object */
    sc = CreateTable(
        (LPIID) &IID_IMAPITableData,
        lpABUser->lpAllocBuff,
        lpABUser->lpAllocMore,
        lpABUser->lpFreeBuff,
        lpABUser->lpMalloc,
        0,
        PR_DISPLAY_NAME_A,
        (LPSPropTagArray) &tagaColSetDDListBox,
        &(lpABUser->lpTDatDDListBox));

    if (FAILED(sc))
    {
        hResult = ResultFromScode(sc);
        goto out;
    }

    /* constants */
    sRow.cValues = cvalddMax;
    sRow.lpProps = rgsPropValue;


    /*
     *  Although assignment of szDisplay happens here, its actual
     *  values happen below in the for loop.
     */
    rgsPropValue[ivalddPR_DISPLAY_NAME_A].ulPropTag = PR_DISPLAY_NAME_A;
    rgsPropValue[ivalddPR_DISPLAY_NAME_A].Value.lpszA = szDisplay;

    /*
     *  For this release of MAPI the following two properties are required
     *  for all listboxes exposed in any details dialog.  This requirement is
     *  scheduled to be removed before ship
     */
    rgsPropValue[ivalddPR_ENTRYID].ulPropTag = PR_ENTRYID;
    rgsPropValue[ivalddPR_ENTRYID].Value.bin.lpb = (LPBYTE) &OptionsEntryID;
    rgsPropValue[ivalddPR_ENTRYID].Value.bin.cb = CBOPTIONS_ENTRYID;

    rgsPropValue[ivalddPR_DISPLAY_TYPE].ulPropTag = PR_DISPLAY_TYPE;
    rgsPropValue[ivalddPR_DISPLAY_TYPE].Value.l = 0;
    

    rgsPropValue[ivalddPR_DDLISTBOX_VALUE].ulPropTag = PR_DDLISTBOX_VALUE;

    rgsPropValue[ivalddPR_INSTANCE_KEY].ulPropTag = PR_INSTANCE_KEY;
    rgsPropValue[ivalddPR_INSTANCE_KEY].Value.bin.cb = sizeof(ULONG);

    /* fill up the table */
    for (uliRow = 0; uliRow < 25; uliRow++)
    {
        wsprintfA(szDisplay, szFmtDisplay, uliRow);

        OptionsEntryID.ulRowNumber = uliRow;
        rgsPropValue[ivalddPR_DDLISTBOX_VALUE].Value.l = uliRow;
        
        rgsPropValue[ivalddPR_INSTANCE_KEY].Value.bin.lpb = (LPBYTE) &uliRow;

        hResult = lpABUser->lpTDatDDListBox->lpVtbl->HrModifyRow(
            lpABUser->lpTDatDDListBox,
            &sRow);
        if (HR_FAILED(hResult))
        {
            /*
             *  Mask errors here...
             *  We want to do this because it's probibly still a valid
             *  table data object that I can get views from.  Most likely
             *  just some of the rows will be missing...
             */

            hResult = hrSuccess;
            break;
        }
        /*
         *  get rid of any warnings
         */
        hResult = hrSuccess;
    }

out:

    DebugTraceResult(HrBuildDDListBoxTable, hResult);
    return hResult;
}

/*
 *  Default column set for the combobox table
 */
enum { ivalcbPR_DISPLAY_NAME_A = 0,
        ivalcbPR_ENTRYID,
        ivalcbPR_DISPLAY_TYPE,
        ivalcbPR_COMBOBOX_VALUE,
        ivalcbPR_INSTANCE_KEY,
        cvalcbMax };

const SizedSPropTagArray(cvalcbMax, tagaColSetComboBox) =
{
    cvalcbMax,
    {
        PR_DISPLAY_NAME_A,
        PR_ENTRYID,
        PR_DISPLAY_TYPE,
        PR_COMBOBOX_VALUE,
        PR_INSTANCE_KEY
    }
};

HRESULT
HrBuildComboBoxTable(LPABUSER lpABUser)
{
    SCODE sc;
    HRESULT hResult;
    SPropValue rgsPropValue[cvalcbMax];
    SRow sRow;
    char szFmtDisplay[MAX_FMT_COMBO_DN];
    char szDisplay[MAX_FMT_COMBO_DN + 2]; /* +2 for digits */
    ULONG uliRow;
    LPSTR pszFmtDisplay = (LPSTR) szFmtDisplay;

    /*
     *  Get resource strings
     */
    sc = ScLoadString(  IDS_FMT_COMBO_DN,
                        MAX_FMT_COMBO_DN,
                        NULL,
                        lpABUser->hLibrary,
                        (LPSTR *) &pszFmtDisplay );
    if (FAILED(sc))
    {
        hResult = ResultFromScode(sc);
        goto out;
    }

    /* Create a table data object */
    sc = CreateTable(
        (LPIID) &IID_IMAPITableData,
        lpABUser->lpAllocBuff,
        lpABUser->lpAllocMore,
        lpABUser->lpFreeBuff,
        lpABUser->lpMalloc,
        0,
        PR_DISPLAY_NAME_A,
        (LPSPropTagArray) &tagaColSetComboBox,
        &(lpABUser->lpTDatComboBox));

    if (FAILED(sc))
    {
        hResult = ResultFromScode(sc);
        goto out;
    }

    /* constants */
    sRow.cValues = cvalcbMax;
    sRow.lpProps = rgsPropValue;

    /*
     *  Although assignment of szDisplay happens here, its actual
     *  values happen below in the for loop.
     */
    rgsPropValue[ivalcbPR_DISPLAY_NAME_A].ulPropTag = PR_DISPLAY_NAME_A;
    rgsPropValue[ivalcbPR_DISPLAY_NAME_A].Value.lpszA = szDisplay;


    /*
     *  For this release of MAPI the following two properties are required
     *  for all listboxes exposed in any details dialog.  This requirement is
     *  scheduled to be removed before ship
     */
    rgsPropValue[ivalcbPR_ENTRYID].ulPropTag = PR_ENTRYID;
    rgsPropValue[ivalcbPR_ENTRYID].Value.bin.lpb = (LPBYTE) &OptionsEntryID;
    rgsPropValue[ivalcbPR_ENTRYID].Value.bin.cb = CBOPTIONS_ENTRYID;

    rgsPropValue[ivalcbPR_DISPLAY_TYPE].ulPropTag = PR_DISPLAY_TYPE;
    rgsPropValue[ivalcbPR_DISPLAY_TYPE].Value.l = 0;

    rgsPropValue[ivalcbPR_COMBOBOX_VALUE].ulPropTag = PR_COMBOBOX_VALUE;
    rgsPropValue[ivalcbPR_COMBOBOX_VALUE].Value.lpszA = szDisplay;

    rgsPropValue[ivalcbPR_INSTANCE_KEY].ulPropTag = PR_INSTANCE_KEY;
    rgsPropValue[ivalcbPR_INSTANCE_KEY].Value.bin.cb = sizeof(ULONG);


    /* fill up the table */
    for (uliRow = 0; uliRow < 25; uliRow++)
    {
        wsprintfA(szDisplay, szFmtDisplay, uliRow);

        OptionsEntryID.ulRowNumber = uliRow;

        rgsPropValue[ivalcbPR_INSTANCE_KEY].Value.bin.lpb = (LPBYTE) &uliRow;

        hResult = lpABUser->lpTDatComboBox->lpVtbl->HrModifyRow(
            lpABUser->lpTDatComboBox,
            &sRow);
        if (HR_FAILED(hResult))
        {
            /*
             *  Mask errors here...
             *  We want to do this because it's probibly still a valid
             *  table data object that I can get views from.  Most likely
             *  just some of the rows will be missing...
             */

            hResult = hrSuccess;
            break;
        }

        /*
         *  get rid of any warnings
         */
        hResult = hrSuccess;
    }

out:
    DebugTraceResult(HrBuildComboBoxTable, hResult);
    return hResult;
}
