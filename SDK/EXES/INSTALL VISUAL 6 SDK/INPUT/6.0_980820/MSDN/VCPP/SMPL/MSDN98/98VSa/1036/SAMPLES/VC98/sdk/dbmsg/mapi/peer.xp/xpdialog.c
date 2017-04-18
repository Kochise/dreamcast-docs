/*
 -  X P D I A L O G . C
 -
 *  Purpose:
 *      Logon UI code for use by the MAPI Sample Transport Provider.
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 */

#include "xppch.h"
#include "xpresrc.h"
#include <stdlib.h>
#include <mapiutil.h>

#ifdef DEBUG_DLGITEMS
#ifndef DEBUG
#define DEBUG
#endif
#endif

#define PropIndex(PROP)         (PROP_ID(PROP) - BASE_PROVIDER_ID - 1)

/* Generic control structures */

DTBLLABEL dtbllabel =
{sizeof(DTBLLABEL), 0};
DTBLPAGE dtblpage =
{sizeof(DTBLPAGE), 0, 0, 0};
TCHAR szNoFilter[] = TEXT("*");
TCHAR szDigitFilter[] = TEXT("[0-9]");

/* Display table control structures for the General property sheet. */

DTBLEDIT editWgapFname =
{sizeof(DTBLEDIT), fMapiUnicode, MAX_PATH,
    PR_SAMPLE_FILENAME};
DTBLEDIT editWgapDir =
{sizeof(DTBLEDIT), fMapiUnicode, MAX_PATH,
    PR_SAMPLE_DIRECTORY};
DTBLCHECKBOX chkLogEvents =
{sizeof(DTBLCHECKBOX), fMapiUnicode,
    PR_TEMP_LOG_EVENTS};
DTBLCHECKBOX chkPeer =
{sizeof(DTBLCHECKBOX), fMapiUnicode,
    PR_TEMP_PEER_TO_PEER};
DTBLCHECKBOX chkLogonUI =
{sizeof(DTBLCHECKBOX), fMapiUnicode,
    PR_TEMP_UI_ALWAYS};
DTBLCHECKBOX chkSaveDialog =
{sizeof(DTBLCHECKBOX), fMapiUnicode,
    PR_TEMP_SAVE_DATA};

DTCTL rgdtctlGeneral[] =
{
    {DTCT_PAGE, 0, NULL, 0, NULL, 0, &dtblpage},
    {DTCT_CHECKBOX, DT_EDITABLE, NULL, 0, NULL, IDC_LOG_EVENTS, &chkLogEvents},
    {DTCT_CHECKBOX, DT_EDITABLE, NULL, 0, NULL, IDC_PEER, &chkPeer},
    {DTCT_CHECKBOX, DT_EDITABLE, NULL, 0, NULL, IDC_LOGON_UI, &chkLogonUI},
    {DTCT_CHECKBOX, DT_EDITABLE, NULL, 0, NULL, IDC_SAVE_DIALOG, &chkSaveDialog},
    {DTCT_LABEL, 0, NULL, 0, NULL, IDT_WGAP_FNAME, &dtbllabel},
    {DTCT_EDIT, DT_EDITABLE, NULL, 0, szNoFilter, IDE_WGAP_FNAME, &editWgapFname},
    {DTCT_LABEL, 0, NULL, 0, NULL, IDT_WGAP_DIR, &dtbllabel},
    {DTCT_EDIT, DT_EDITABLE, NULL, 0, szNoFilter, IDE_WGAP_DIR, &editWgapDir}
};

/* Display table control structures for the Peer to Peer property sheet. */

DTBLEDIT editDisplay =
{sizeof(DTBLEDIT), fMapiUnicode, MAX_TEXTFIELD,
    PR_SAMPLE_DISPLAY_NAME};
DTBLEDIT editEmailType =
{sizeof(DTBLEDIT), fMapiUnicode, 32,
    PR_SAMPLE_EMAIL_ADDR_TYPE};
DTBLEDIT editEmailAddress =
{sizeof(DTBLEDIT), fMapiUnicode, MAX_TEXTFIELD,
    PR_SAMPLE_EMAIL_ADDRESS};
DTBLEDIT editInboundDir =
{sizeof(DTBLEDIT), fMapiUnicode, MAX_PATH,
    PR_SAMPLE_INBOUND_DIR};
DTBLEDIT editOutboundDir =
{sizeof(DTBLEDIT), fMapiUnicode, MAX_PATH,
    PR_SAMPLE_OUTBOUND_DIR};

DTCTL rgdtctlPeer[] =
{
    {DTCT_PAGE, 0, NULL, 0, NULL, 0, &dtblpage},
    {DTCT_LABEL, 0, NULL, 0, NULL, IDT_DISPLAY, &dtbllabel},
    {DTCT_EDIT, DT_EDITABLE, NULL, 0, szNoFilter, IDE_DISPLAY, &editDisplay},
    {DTCT_LABEL, 0, NULL, 0, NULL, IDT_EMAIL_TYPE, &dtbllabel},
    {DTCT_EDIT, DT_EDITABLE, NULL, 0, szNoFilter, IDE_EMAIL_TYPE, &editEmailType},
    {DTCT_LABEL, 0, NULL, 0, NULL, IDT_EMAIL_ADDR, &dtbllabel},
    {DTCT_EDIT, DT_EDITABLE, NULL, 0, szNoFilter, IDE_EMAIL_ADDR, &editEmailAddress},
    {DTCT_LABEL, 0, NULL, 0, NULL, IDT_IN_DIR, &dtbllabel},
    {DTCT_EDIT, DT_EDITABLE, NULL, 0, szNoFilter, IDE_IN_DIR, &editInboundDir},
    {DTCT_LABEL, 0, NULL, 0, NULL, IDT_OUT_DIR, &dtbllabel},
    {DTCT_EDIT, DT_EDITABLE, NULL, 0, szNoFilter, IDE_OUT_DIR, &editOutboundDir}
};

/* Display table control structures for the Logging property sheet. */

DTBLEDIT editLogFile =
{sizeof(DTBLEDIT), fMapiUnicode, MAX_PATH,
    PR_SAMPLE_LOGFILE};
DTBLEDIT editLogHigh =
{sizeof(DTBLEDIT), fMapiUnicode, 11,
    PR_TEMP_LOGHIGHWATER};
DTBLEDIT editLogLow =
{sizeof(DTBLEDIT), fMapiUnicode, 11,
    PR_TEMP_LOGLOWWATER};
DTCTL rgdtctlLogging[] =
{
    {DTCT_PAGE, 0, NULL, 0, NULL, 0, &dtblpage},
    {DTCT_LABEL, 0, NULL, 0, NULL, IDT_LOG_NAME, &dtbllabel},
    {DTCT_EDIT, DT_EDITABLE, NULL, 0, szNoFilter, IDE_LOG_NAME, &editLogFile},
    {DTCT_LABEL, 0, NULL, 0, NULL, IDT_LOG_HIGH, &dtbllabel},
    {DTCT_EDIT, DT_EDITABLE, NULL, 0, szDigitFilter, IDE_LOG_HIGH, &editLogHigh},
    {DTCT_LABEL, 0, NULL, 0, NULL, IDT_LOG_LOW, &dtbllabel},
    {DTCT_EDIT, DT_EDITABLE, NULL, 0, szDigitFilter, IDE_LOG_LOW, &editLogLow}
};

/* Display table pages */

DTPAGE rgdtpage[] =
{
    {
        sizeof(rgdtctlGeneral) / sizeof(DTCTL),
        (LPTSTR) MAKEINTRESOURCE(GeneralPage),
        "",
        rgdtctlGeneral
    },
    {
        sizeof(rgdtctlPeer) / sizeof(DTCTL),
        (LPTSTR) MAKEINTRESOURCE(PeerPage),
        "",
        rgdtctlPeer
    },
    {
        sizeof(rgdtctlLogging) / sizeof(DTCTL),
        (LPTSTR) MAKEINTRESOURCE(LoggingPage),
        "",
        rgdtctlLogging
    }
};

#ifdef DEBUG_DLGITEMS
static void
 DLGDump(LPXPDLG lpXPDialog);
#endif


/*
 -  ScDoLogonDlg
 -
 *  Purpose:
 *      Called by the TransportLogon code to present logon UI to the user.
 *
 *  Parameters:
 *      lpXPDialog          Structure through which we communicate
 *
 *  Returns:
 *      0                   Dialog came up, pLogonStruct->lppPropArray
 *                          contains a PropValueArray if OK, NULL if CANCEL
 *
 *      (Failure)           Some error occurred. lppPropArray will have
 *                          either the original array or NULL.
 *
 *  Operation:
 *      Gets the necessary information from Windows and activates the logon
 *      dialog box.
 */

SCODE
ScDoLogonDlg(LPXPDLG lpXPDialog)
{
    SCODE sc = S_OK;
    HRESULT hr;
    LPMAPITABLE ptable = NULL;
    LPPROPDATA pTempProps = NULL;
    ULONG flT = 0L;
    LPSPropValue rgprop;
    LPSPropValue pprop;
    LPSPropTagArray ptags;
    ULONG cprop;
    TCHAR szDialogTitle[128];
    TCHAR szLogHigh[12];
    TCHAR szLogLow[12];
    UINT i;

    /* Take ownership of the property value array, so calling code
       will not leak memory. */

    rgprop = *(lpXPDialog->lppPropArray);
    *(lpXPDialog->lppPropArray) = NULL;
    ptags = lpXPDialog->lpPTArray;

    /* Retrieve the dialog title string */

    if (!LoadString(lpXPDialog->hInst, IDS_CONFIG_TITLE, 
        szDialogTitle, sizeof(szDialogTitle)))
    {
        sc = MAPI_E_NOT_ENOUGH_MEMORY;
        DebugTrace("LoadString failed in ScDoLogonDlg.\n");
        goto ret;
    }

    /* Create the configuration data interface.
       First, split the PR_SAMPLE_FLAGS property into four individual
       Boolean properties. */

    pprop = rgprop + (MAX_LOGON_PROPERTIES - TEMP_LOGON_PROPERTIES);

    if (rgprop[PropIndex(PR_SAMPLE_FLAGS)].ulPropTag == PR_SAMPLE_FLAGS)
        flT = rgprop[PropIndex(PR_SAMPLE_FLAGS)].Value.ul;
    else
    {
        /*  The Peer to Peer and Save Data flags default to TRUE */
        rgprop[PropIndex(PR_SAMPLE_FLAGS)].ulPropTag = PR_SAMPLE_FLAGS;
        flT = PR_SAMPLE_FLAG_PEER_TO_PEER | PR_SAMPLE_FLAG_SAVE_DATA;
        rgprop[PropIndex(PR_SAMPLE_FLAGS)].Value.ul = flT;
    }

    pprop[0].ulPropTag = PR_TEMP_PEER_TO_PEER;
    pprop[0].Value.b = !!(flT & PR_SAMPLE_FLAG_PEER_TO_PEER);
    pprop[1].ulPropTag = PR_TEMP_UI_ALWAYS;
    pprop[1].Value.b = !!(flT & PR_SAMPLE_FLAG_UI_ALWAYS);
    pprop[2].ulPropTag = PR_TEMP_LOG_EVENTS;
    pprop[2].Value.b = !!(flT & PR_SAMPLE_FLAG_LOG_EVENTS);
    pprop[3].ulPropTag = PR_TEMP_SAVE_DATA;
    pprop[3].Value.b = !!(flT & PR_SAMPLE_FLAG_SAVE_DATA);

    /* Next, make strings out of the two numeric logging parameters */

    if (rgprop[PropIndex(PR_SAMPLE_LOGHIGHWATER)].ulPropTag == PR_SAMPLE_LOGHIGHWATER)
        wsprintf(szLogHigh, "%ld",
            rgprop[PropIndex(PR_SAMPLE_LOGHIGHWATER)].Value.l);
    else
        szLogHigh[0] = '\0';

    pprop[4].ulPropTag = PR_TEMP_LOGHIGHWATER;
    pprop[4].Value.LPSZ = szLogHigh;

    if (rgprop[PropIndex(PR_SAMPLE_LOGLOWWATER)].ulPropTag == PR_SAMPLE_LOGLOWWATER)
        wsprintf(szLogLow, "%ld",
            rgprop[PropIndex(PR_SAMPLE_LOGLOWWATER)].Value.l);
    else
        szLogLow[0] = '\0';

    pprop[5].ulPropTag = PR_TEMP_LOGLOWWATER;
    pprop[5].Value.LPSZ = szLogLow;

    /* Now make a temporary property interface and feed it the data. */

    sc = CreateIProp((LPIID) &IID_IMAPIPropData,
            lpXPDialog->AllocateBuffer,
            lpXPDialog->AllocateMore,
            lpXPDialog->FreeBuffer,
            lpXPDialog->lpMalloc,
            &pTempProps);

    if (FAILED(sc))
    {
        DebugTrace("CreateIProp failed in ScDoLogonDlg.\n");
        goto ret;
    }

    hr = pTempProps->lpVtbl->SetProps(pTempProps, MAX_LOGON_PROPERTIES, rgprop, NULL);

    if (HR_FAILED(hr))
    {
        sc = GetScode(hr);
        DebugTrace("SetProps failed in ScDoLogonDlg.\n");
        goto ret;
    }
    
    /* If the UI_READONLY flag is set, then we are being called from
       the SettingDialog() method in Read Only mode.  Disable all of
       the controls on the three property sheets, else Enable them.  */

    if (lpXPDialog->ulFlags & UI_READONLY)
    {
        /* Disable controls on the General PropSheet */
        rgdtpage[0].lpctl[1].ulCtlFlags &= ~DT_EDITABLE;
        rgdtpage[0].lpctl[2].ulCtlFlags &= ~DT_EDITABLE;
        rgdtpage[0].lpctl[3].ulCtlFlags &= ~DT_EDITABLE;
        rgdtpage[0].lpctl[4].ulCtlFlags &= ~DT_EDITABLE;
        rgdtpage[0].lpctl[6].ulCtlFlags &= ~DT_EDITABLE;
        rgdtpage[0].lpctl[8].ulCtlFlags &= ~DT_EDITABLE;

        /* Disable controls on the Peer-To-Peer PropSheet */
        rgdtpage[1].lpctl[2].ulCtlFlags &= ~DT_EDITABLE;
        rgdtpage[1].lpctl[4].ulCtlFlags &= ~DT_EDITABLE;
        rgdtpage[1].lpctl[6].ulCtlFlags &= ~DT_EDITABLE;
        rgdtpage[1].lpctl[8].ulCtlFlags &= ~DT_EDITABLE;
        rgdtpage[1].lpctl[10].ulCtlFlags &= ~DT_EDITABLE;

        /* Disable controls on the Logging PropSheet */
        rgdtpage[2].lpctl[2].ulCtlFlags &= ~DT_EDITABLE;
        rgdtpage[2].lpctl[4].ulCtlFlags &= ~DT_EDITABLE;
        rgdtpage[2].lpctl[6].ulCtlFlags &= ~DT_EDITABLE;
    }
    else
    {
        /* Enable controls on the General PropSheet */
        rgdtpage[0].lpctl[1].ulCtlFlags |= DT_EDITABLE;
        rgdtpage[0].lpctl[2].ulCtlFlags |= DT_EDITABLE;
        rgdtpage[0].lpctl[3].ulCtlFlags |= DT_EDITABLE;
        rgdtpage[0].lpctl[4].ulCtlFlags |= DT_EDITABLE;
        rgdtpage[0].lpctl[6].ulCtlFlags |= DT_EDITABLE;
        rgdtpage[0].lpctl[8].ulCtlFlags |= DT_EDITABLE;

        /* Enable controls on the Peer-To-Peer PropSheet */
        rgdtpage[1].lpctl[2].ulCtlFlags |= DT_EDITABLE;
        rgdtpage[1].lpctl[4].ulCtlFlags |= DT_EDITABLE;
        rgdtpage[1].lpctl[6].ulCtlFlags |= DT_EDITABLE;
        rgdtpage[1].lpctl[8].ulCtlFlags |= DT_EDITABLE;
        rgdtpage[1].lpctl[10].ulCtlFlags |= DT_EDITABLE;

        /* Enable controls on the Logging PropSheet */
        rgdtpage[2].lpctl[2].ulCtlFlags |= DT_EDITABLE;
        rgdtpage[2].lpctl[4].ulCtlFlags |= DT_EDITABLE;
        rgdtpage[2].lpctl[6].ulCtlFlags |= DT_EDITABLE;
    }

    /* Check if we are being called at Logon time or from a call to
       SettingsDialog().  If from SettingsDialog() then disable the
       IDE_EMAIL_TYPE edit control reguardless of ulFlags setting. */

    if (!lpXPDialog->fLogon)
        rgdtpage[1].lpctl[4].ulCtlFlags &= ~DT_EDITABLE;

    /* Create the display table for the logon dialog. It is based on dialog
       resources plus the static information at the head of this module. */

    hr = BuildDisplayTable(
        lpXPDialog->AllocateBuffer,
        lpXPDialog->AllocateMore,
        lpXPDialog->FreeBuffer,
        lpXPDialog->lpMalloc,
        lpXPDialog->hInst,
        sizeof(rgdtpage) / sizeof(DTPAGE),
        rgdtpage,
        0,
        &ptable,
        NULL);

    if (HR_FAILED(hr))
    {
        sc = GetScode(hr);
        DebugTrace("BuildDisplayTable failed in ScDoLogonDlg.\n");
        goto ret;
    }

    /* Run the dialog */

    hr = lpXPDialog->lpMAPISup->lpVtbl->DoConfigPropsheet(lpXPDialog->lpMAPISup,
        (ULONG) lpXPDialog->hwnd,
        0,
        szDialogTitle,
        ptable,
        (LPMAPIPROP) pTempProps,
        1);

    if (HR_FAILED(hr))
    {
        sc = GetScode(hr);
        DebugTrace("DoConfigPropsheet failed in ScDoLogonDlg.\n");
        goto ret;
    }

    /* Retrieve the altered data */

    (*(lpXPDialog->FreeBuffer)) (rgprop);
    rgprop = NULL;

    hr = pTempProps->lpVtbl->GetProps(pTempProps, ptags, 0, /* ansi */
            &cprop, &rgprop);

    if (HR_FAILED(hr))
    {
        sc = GetScode(hr);
        DebugTrace("GetProps failed in ScDoLogonDlg.\n");
        goto ret;
    }

    Assert(cprop == MAX_LOGON_PROPERTIES);

    /* Supply default values for any unfilled fields.
       Also ensure that the directory name fields end in a slash. */

    for (i = 0; i < MAX_LOGON_PROPERTIES - TEMP_LOGON_PROPERTIES; ++i)
    {
        ULONG tagT = rgprop[i].ulPropTag;
        UINT cch;
        LPTSTR lpszT;

        if (tagT != ptags->aulPropTag[i])
        {
            /* This property did not make it. Integer properties default
               to 0, and string properties default to empty. */

            tagT = ptags->aulPropTag[i];

            if (PROP_TYPE(tagT) == PT_LONG)
            {
                rgprop[i].Value.l = 0;
                rgprop[i].ulPropTag = tagT;
            }
            else if (PROP_TYPE(tagT) == PT_TSTRING)
            {
                if (FAILED((*(lpXPDialog->AllocateMore)) (sizeof(TCHAR),
                            rgprop, (LPVOID FAR *) &rgprop[i].Value.LPSZ)))
                {
                    rgprop[i].ulPropTag = PROP_TAG(PT_ERROR, PROP_ID(tagT));
                    rgprop[i].Value.err = MAPI_E_NOT_ENOUGH_MEMORY;
                }
                else
                {
                    rgprop[i].Value.LPSZ[0] = '\0';
                    rgprop[i].ulPropTag = tagT;
                }
            }
        }
        else if (tagT == PR_SAMPLE_INBOUND_DIR ||
                tagT == PR_SAMPLE_OUTBOUND_DIR ||
            tagT == PR_SAMPLE_DIRECTORY)
        {
            cch = lstrlen(rgprop[i].Value.LPSZ);

            if (cch && rgprop[i].Value.LPSZ[cch - 1] != '\\')
            {
                if (FAILED((*(lpXPDialog->AllocateMore)) (
                            (cch + 2) * sizeof(TCHAR), rgprop, (LPVOID FAR *) &lpszT)))
                {
                    rgprop[i].ulPropTag = PROP_TAG(PT_ERROR, PROP_ID(tagT));
                    rgprop[i].Value.err = MAPI_E_NOT_ENOUGH_MEMORY;
                }
                else
                {
                    lstrcpy(lpszT, rgprop[i].Value.LPSZ);
                    lpszT[cch] = '\\';
                    lpszT[cch + 1] = '\0';
                    rgprop[i].Value.LPSZ = lpszT;
                }
            }
        }
    }

    /* Reassemble the PR_SAMPLE_FLAGS property */

    pprop = rgprop + (MAX_LOGON_PROPERTIES - TEMP_LOGON_PROPERTIES);
    flT = 0L;

    if (pprop[0].ulPropTag == PR_TEMP_PEER_TO_PEER && pprop[0].Value.b)
        flT |= PR_SAMPLE_FLAG_PEER_TO_PEER;
    if (pprop[1].ulPropTag == PR_TEMP_UI_ALWAYS && pprop[1].Value.b)
        flT |= PR_SAMPLE_FLAG_UI_ALWAYS;
    if (pprop[2].ulPropTag == PR_TEMP_LOG_EVENTS && pprop[2].Value.b)
        flT |= PR_SAMPLE_FLAG_LOG_EVENTS;
    if (pprop[3].ulPropTag == PR_TEMP_SAVE_DATA && pprop[3].Value.b)
        flT |= PR_SAMPLE_FLAG_SAVE_DATA;

    rgprop[PropIndex(PR_SAMPLE_FLAGS)].ulPropTag = PR_SAMPLE_FLAGS;
    rgprop[PropIndex(PR_SAMPLE_FLAGS)].Value.ul = flT;

    /* Reassemble the high and low water marks for logging */

    if (rgprop[PropIndex(PR_TEMP_LOGHIGHWATER)].ulPropTag == PR_TEMP_LOGHIGHWATER)
        rgprop[PropIndex(PR_SAMPLE_LOGHIGHWATER)].Value.l =
            atoi(rgprop[PropIndex(PR_TEMP_LOGHIGHWATER)].Value.LPSZ);

    if (rgprop[PropIndex(PR_TEMP_LOGLOWWATER)].ulPropTag == PR_TEMP_LOGLOWWATER)
        rgprop[PropIndex(PR_SAMPLE_LOGLOWWATER)].Value.l =
            atoi(rgprop[PropIndex(PR_TEMP_LOGLOWWATER)].Value.LPSZ);

    /* Return the new property array */

    *(lpXPDialog->lppPropArray) = rgprop;
    rgprop = NULL;              /* do not free this in cleanup code */
    sc = S_OK;                  /* no warnings */

#ifdef DEBUG_DLGITEMS
    DLGDump(lpXPDialog);        /* dump debug data. */
#endif

ret:
    DebugTraceSc(ScDoLogonDialog(), sc);

    UlRelease(ptable);
    UlRelease(pTempProps);

    lpXPDialog->FreeBuffer(rgprop);

    return sc;
}


#ifdef DEBUG_DLGITEMS

/*
 -  DLGDump
 -
 *  Purpose:
 *      Called by ScDoLogonDlg to dump the contents
 *      of the logon property array to the debugger.
 *
 *  Parameters:
 *      lpXPDialog      Pointer to logon parameter structure
 *
 *  Returns:
 *      none.
 *
 *  Operation:
 *      Walks through the property array inside the logon structure, and
 *      dumps its contents through DebugTrace().
 *
 *      This function only exists in the debug version.
 */

static void
DLGDump(LPXPDLG lpXPDialog)
{

    ULONG ulT, flT, ptT, ptT2;
    LPSPropValue lpPropArray;
    LPSPropTagArray lpPTArray;
    SPropValue propT;
    ULONG ulCount;

    if (!lpXPDialog)
    {
        DebugTrace("lpXPDialog is NULL");
        goto ret;
    }

    DebugTrace("LogonStruct:");

    lpPropArray = *(lpXPDialog->lppPropArray);
    lpPTArray = lpXPDialog->lpPTArray;

    if (!lpPropArray)
    {
        DebugTrace("NULL\n");
        goto ret;
    }

    ulCount = lpPTArray->cValues;

    for (ulT = 0; ulT < ulCount; ulT++)
    {
        propT = lpPropArray[ulT];
        ptT = lpPTArray->aulPropTag[ulT];
        ptT2 = propT.ulPropTag;

        switch (ptT)
        {
        case PR_SAMPLE_DISPLAY_NAME:
            DebugTrace("  DisplayName: %s", (ptT == ptT2) ? propT.Value.LPSZ : "NULL");
            break;

        case PR_SAMPLE_EMAIL_ADDR_TYPE:
            DebugTrace("  EmailAddressType: %s", (ptT == ptT2) ? propT.Value.LPSZ : "NULL");
            break;

        case PR_SAMPLE_EMAIL_ADDRESS:
            DebugTrace("  EmailAddress: %s", (ptT == ptT2) ? propT.Value.LPSZ : "NULL");
            break;

        case PR_SAMPLE_INBOUND_DIR:
            DebugTrace("  Inbound Directory: %s", (ptT == ptT2) ? propT.Value.LPSZ : "NULL");
            break;

        case PR_SAMPLE_OUTBOUND_DIR:
            DebugTrace("  Outbound Directory: %s", (ptT == ptT2) ? propT.Value.LPSZ : "NULL");
            break;

        case PR_SAMPLE_FILENAME:
            DebugTrace("  WGApp Filename: %s", (ptT == ptT2) ? propT.Value.LPSZ : "NULL");
            break;

        case PR_SAMPLE_DIRECTORY:
            DebugTrace("  WGApp Directory: %s", (ptT == ptT2) ? propT.Value.LPSZ : "NULL");
            break;

        case PR_SAMPLE_FLAGS:

            flT = (ptT == ptT2) ? propT.Value.ul : 0;

            DebugTrace("  Peer-To-Peer: %s", (flT & PR_SAMPLE_FLAG_PEER_TO_PEER) ? "TRUE" : "FALSE");
            DebugTrace("  Always show UI: %s", (flT & PR_SAMPLE_FLAG_UI_ALWAYS) ? "TRUE" : "FALSE");
            DebugTrace("  Log Events: %s", (flT & PR_SAMPLE_FLAG_LOG_EVENTS) ? "TRUE" : "FALSE");
            DebugTrace("  Save Logon Input: %s", (flT & PR_SAMPLE_FLAG_SAVE_DATA) ? "TRUE" : "FALSE");
            break;

        case PR_SAMPLE_LOGFILE:
            DebugTrace("  Log File Name: %s", (ptT == ptT2) ? propT.Value.LPSZ : "NULL");
            break;

        case PR_SAMPLE_LOGHIGHWATER:
            DebugTrace("  Log File HighWater: %ld", (ptT == ptT2) ? propT.Value.ul : 0);
            break;

        case PR_SAMPLE_LOGLOWWATER:
            DebugTrace("  Log File LowWater: %ld", (ptT == ptT2) ? propT.Value.ul : 0);
            break;
            
        default:
            DebugTrace("  Unknown Logon Property: %08X", ptT);
            break;
        }
    }
ret:
    return;
}

#endif                          /* DEBUG_DLGITEMS */
