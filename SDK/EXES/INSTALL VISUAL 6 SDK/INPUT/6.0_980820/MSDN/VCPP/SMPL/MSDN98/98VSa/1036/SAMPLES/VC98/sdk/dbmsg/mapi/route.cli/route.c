/*
 -  ROUTE.C
 *
 *
 *      Functions used to implement routing.
 *
 *      To create a new routing message call:
 *         DialogBoxParam(hInst, "RouteNote", hWnd, RouteNoteDlgProc, (LPARAM) NULL );
 *      To route a routed message to the next recipient call:
 *          DialogBoxParam(hInst, "RouteNote", hWnd, RouteNoteDlgProc, (LPARAM) pmsg );
 *              where pmsg is a pointer to the message you want to route.
 *      To find out if a message was routed by this program call:
 *          HasRougingSlip();
 *
 *
 *      To use this functions in your own program change the line (in route.h):
 *          #define lpszSmplRTMsgClass "IPM.Note.SampleRoutingForm"
 *      to reflect the name of your own class for routing messages.
 *
 *
 *  Copyright 1986-1996, Microsoft Corporation. All Rights Reserved.
 */

#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <windowsx.h>
#ifdef _WIN32
#include <objerror.h>
#include <objbase.h>
#endif
#ifdef WIN16
#include <compobj.h>
#include <commdlg.h>
#endif
#include <mapiutil.h>
#include <mapix.h>
#include <mapiwin.h>
#include <mapidbg.h>
#include <cindex.h>

#ifdef WIN16
#define GWL_USERDATA    DWL_USER
#endif


/*
 To use a GUID XXX in a program you have to initialize it in exactly one
obj file of your project.
Line "#define USES_XXX" tells the compiler that you are going to use GUID XXX
in this file.
Lines "#define INITGUID"  and "#include<initguid.h>"
tell the compiler to init GUIDs in this file.*/

/* the GUID we'll be using */
#define USES_PS_ROUTING_EMAIL_ADDRESSES 1
#define USES_PS_ROUTING_ADDRTYPE 1
#define USES_PS_ROUTING_DISPLAY_NAME 1
#define USES_PS_ROUTING_ENTRYID 1
#define USES_PS_ROUTING_SEARCH_KEY 1
#define USES_PS_PUBLIC_STRINGS  1
#define USES_IID_IMessage 1
#define USES_IID_IMAPIStatus 1
#define USES_IID_IMAPIForm 1
/*initialize the GUIDs in this file*/
#define INITGUID 1
#include <initguid.h>
#include <mapiguid.h>
#include <pdkver.h>

#include "client.h"
#include "bitmap.h"
#include "route.h"

/* Routing Data. Used in RouteNoteDlgProc that handles composing/sending/reading of
routing messages */
typedef struct _ROUTEDATA
{
    LPADRLIST palAddrListOld;
    LPADRLIST palAddrListActive;
    ULONG nCurrentRouteRecip;
    ULONG nTotalRouteRecip;
    LPMAPITABLE ptblAttach;
    BOOL bNewMessage;
    LPMESSAGE pmsgRouteMsg;
    ULONG tagCurrent;
    ULONG tagTotal;
    ULONG cbConvIdx;
    LPBYTE lpbConvIdx;
} ROUTEDATA, FAR * LPROUTEDATA;

BOOL MakeNewRouteMessage(LPMESSAGE pmsgRead, LPROUTEDATA FAR * ppRouteData);
BOOL SetRouteProps(LPROUTEDATA pRouteData);
BOOL DelRouteProps(LPROUTEDATA pRouteData);
BOOL GetRoutePropTagArray(ULONG cb, LPMESSAGE lpM, LPSPropTagArray FAR * lppspta);
BOOL GetRoutePropTagArrayFast(ULONG nTotalRecip, LPMESSAGE lpM, BOOL fCreate,
                                LPSPropTagArray FAR * lppspta);
BOOL GetRouteIndices(LPROUTEDATA pRouteData);
BOOL SetRouteIndices(LPROUTEDATA pRouteData);
BOOL CreateOutMessage(LPMESSAGE FAR * lpmSrcMsgI);
BOOL GetRouteAddrLists(LPROUTEDATA pRouteData);
UINT FirstRecipient(LPADRLIST lpAL);
BOOL SetMessageClass(LPMESSAGE lpM, LPSTR lpszClass);
BOOL HasAttachment(LPMESSAGE lpM);
BOOL PopulateAttachList(HWND hDlg, LPROUTEDATA pRouteData);
BOOL CreateNewAttachment(HWND hDlg);
void SaveAttachment( HWND hDlg, UINT indx);
void RT_OnCommand(HWND hDlg, int id, HWND hwndCtl, UINT codeNotify);
BOOL RT_OnInitDialog(HWND hDlg, HWND hwndFocus, LPARAM lParam);
BOOL RBox_OnInitDialog(HWND hDlg, HWND hwndFocus, LPARAM lParam);
void RBox_OnCommand(HWND hDlg, int id, HWND hwndCtl, UINT codeNotify);
void DeInitRouteData(LPROUTEDATA pRouteData);
BOOL CALLBACK RouteBoxDlgProc (HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
void InitRouteNameIDArray(ULONG cb, LPMAPINAMEID lpPropNames);
void PopulateRouteListBox(HWND hDlg);
void ConfigMoveButtons(HWND hDlg, HWND hLB);


typedef enum _ROUTEPROPSETS
{
    ROUTEPROPSET_EMAIL_ADDRESS = 0,
    ROUTEPROPSET_ADDRTYPE,
    ROUTEPROPSET_DISPLAY_NAME,
    ROUTEPROPSET_ENTRYID,
    ROUTEPROPSET_SEARCH_KEY,
    ROUTEPROPSETDIM     /* used for dimension*/
} ROUTEPROPSETS;


LPGUID  lpguidA[ROUTEPROPSETDIM]  =
{
    (LPGUID)&PS_ROUTING_EMAIL_ADDRESSES,
    (LPGUID)&PS_ROUTING_ADDRTYPE,
    (LPGUID)&PS_ROUTING_DISPLAY_NAME,
    (LPGUID)&PS_ROUTING_ENTRYID,
    (LPGUID)&PS_ROUTING_SEARCH_KEY
};

ULONG  ulRoutePropTypes [ROUTEPROPSETDIM] =
{
    PT_STRING8,
    PT_STRING8,
    PT_STRING8,
    PT_BINARY,
    PT_BINARY
};



/*  used for PrepareRecips call*/
SizedSPropTagArray(ROUTEPROPSETDIM, sptRouteProps) =
{
    ROUTEPROPSETDIM,
    {
        PR_EMAIL_ADDRESS,
        PR_ADDRTYPE,
        PR_DISPLAY_NAME,
        PR_ENTRYID,
        PR_SEARCH_KEY
    }
};

enum {EMSG_SUBJ = 0, EMSG_BODY, EMSG_MSGFLAGS, EMSG_CONVIDX, EMSGPROPDIM};
SizedSPropTagArray( EMSGPROPDIM, tagaMsgProps) =
{
    EMSGPROPDIM,
    {PR_SUBJECT, PR_BODY, PR_MESSAGE_FLAGS, PR_CONVERSATION_INDEX}
};
/*
//
// the number of entries could vary from
// EXCLUDED_PROPS_ON_REPLY to EXCLUDED_PROPS_ON_REPLY - 1 and vice versa,
// depending if the message is being reply or fowarded. If forwarded, the
// PR_MESSAGE_ATTACHMENTS property is included in the forwarded message
// otherwise it is excluded
*/
#define EXCLUDED_PROPS_ON_REPLY     29
SizedSPropTagArray (EXCLUDED_PROPS_ON_REPLY, sptExcludedProps) =
{
    EXCLUDED_PROPS_ON_REPLY,
    {
        PR_SENDER_NAME,
        PR_SENDER_ENTRYID,
        PR_SENDER_SEARCH_KEY,
        PR_SENDER_EMAIL_ADDRESS,
        PR_SENDER_ADDRTYPE,

        PR_RECEIVED_BY_NAME,
        PR_RECEIVED_BY_ENTRYID,
        PR_RECEIVED_BY_SEARCH_KEY,

        PR_SENT_REPRESENTING_NAME,
        PR_SENT_REPRESENTING_ENTRYID,
        PR_SENT_REPRESENTING_SEARCH_KEY,
        PR_SENT_REPRESENTING_EMAIL_ADDRESS,
        PR_SENT_REPRESENTING_ADDRTYPE,

        PR_RCVD_REPRESENTING_NAME,
        PR_RCVD_REPRESENTING_ENTRYID,
        PR_RCVD_REPRESENTING_SEARCH_KEY,

        PR_MESSAGE_FLAGS,
        PR_MESSAGE_RECIPIENTS,

        PR_READ_RECEIPT_ENTRYID,
        PR_REPORT_ENTRYID,

        PR_REPLY_RECIPIENT_ENTRIES,
        PR_REPLY_RECIPIENT_NAMES,

        PR_PARENT_KEY,

        PR_ORIGINATOR_DELIVERY_REPORT_REQUESTED,

        PR_READ_RECEIPT_REQUESTED,

        PR_CLIENT_SUBMIT_TIME,
        PR_MESSAGE_DELIVERY_TIME,
        PR_MESSAGE_DOWNLOAD_TIME,

//        PR_SUBJECT_PREFIX,
        PR_MESSAGE_ATTACHMENTS
    }
};

LPADRBOOK
OpenAddressBook(HWND hwnd)
{
    HRESULT hr;
    LPADRBOOK pabAddrBook = NULL;

    Assert(pses);
    hr = pses->lpVtbl->OpenAddressBook(pses, (ULONG) hwnd, NULL, 0, &pabAddrBook);
    if(HR_FAILED(hr))
    {
        MakeMessageBox(hwnd, GetScode(hr),IDS_OPENAB, NULL, MBS_ERROR);
        return NULL;
    }
    if(hr) /*if we have a warning*/
    {
        LPMAPIERROR perr = NULL;

        pses->lpVtbl->GetLastError(pses, hr, 0, &perr);
        MakeMessageBox(hwnd, GetScode(hr), IDS_OPENABWARN, perr, MBS_ERROR);
        MAPIFreeBuffer(perr);
    }

    return pabAddrBook;
}

/*
 *  Handles the RouteSlipbox
 *
 *  Extracts all necessary data from GWL_USERDATA window long of
 *  its parent which is RouteNote dialog.
 */
BOOL CALLBACK
RouteBoxDlgProc (HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{

    switch (msg)
    {
    case WM_INITDIALOG:
        PopulateRouteListBox(hDlg);
        return TRUE;

    HANDLE_MSG(hDlg, WM_COMMAND, RBox_OnCommand);
    }

    return FALSE;
}


void RBox_OnCommand(HWND hDlg, int id, HWND hwndCtl, UINT codeNotify)
{
    ADRPARM AdrParm = { 0 };
    ULONG ulrectps = MAPI_TO;
    LPSTR  lpszTitles = "Route To ";
    UINT nIndex, nIndex1;
    LPSPropValue lpspv = NULL;
    LPROUTEDATA pRouteData = NULL;
    HRESULT hr;

    switch (id)
    {
    case IDC_ADDRLISTACTIVE:
    case IDC_ADDRLISTOLD:
            /*This is to disallow hitting "Remove" button when
            there is something selected in the old address list*/
        if(codeNotify == LBN_SETFOCUS)
        {
            if(id == IDC_ADDRLISTOLD)
            {
                EnableWindow(GetDlgItem(hDlg, IDC_REMOVEADDR), FALSE);
                EnableWindow(GetDlgItem(hDlg, IDC_MOVEUP), FALSE);
                EnableWindow(GetDlgItem(hDlg, IDC_MOVEDOWN), FALSE);
                ListBox_SetCurSel(GetDlgItem(hDlg, IDC_ADDRLISTACTIVE), -1);

            }

            else /*must be IDC_ADDRLISTACTIVE*/
            {
                EnableWindow(GetDlgItem(hDlg, IDC_REMOVEADDR), TRUE);
                ListBox_SetCurSel(GetDlgItem(hDlg, IDC_ADDRLISTOLD), -1);
            }
        }


        if(IDC_ADDRLISTACTIVE == id && LBN_SELCHANGE == codeNotify)
        {
            ConfigMoveButtons(hDlg, hwndCtl);
        }

        /* Details */
        if(codeNotify == LBN_DBLCLK)
        {
            LPSPropValue pvalDtls = NULL;
            ULONG cVals = 0;

            nIndex = (UINT)ListBox_GetCurSel(hwndCtl);
            if (nIndex == LB_ERR)
                break;
            nIndex1 = (UINT)ListBox_GetItemData(hwndCtl, nIndex);
            if(nIndex1 == LB_ERR)
            {
                DebugTrace("Client: error retrieving listbox item data");
                break;
            }

            pRouteData = (LPROUTEDATA) GetWindowLong(GetParent(hDlg), GWL_USERDATA);
            Assert(pRouteData);

            if(IDC_ADDRLISTACTIVE == id)
            {
                Assert(nIndex1 < pRouteData->palAddrListActive->cEntries);
                pvalDtls = pRouteData->palAddrListActive->aEntries[nIndex1].rgPropVals;
                cVals = pRouteData->palAddrListActive->aEntries[nIndex1].cValues;
            }
            else if(IDC_ADDRLISTOLD == id)
            {
                Assert(nIndex1 < pRouteData->palAddrListOld->cEntries);
                pvalDtls = pRouteData->palAddrListOld->aEntries[nIndex1].rgPropVals;
                cVals = pRouteData->palAddrListOld->aEntries[nIndex1].cValues;
            }
            else
                Assert(FALSE);

            Assert(pvalDtls);
            pvalDtls = PpropFindProp(pvalDtls, cVals, PR_ENTRYID);

            Assert(pvalDtls);
            if(pvalDtls)
            {
                hr = pabAddrB->lpVtbl->Details(pabAddrB, (LPULONG) &hDlg, NULL,
                                        NULL, pvalDtls->Value.bin.cb,
                                        (LPENTRYID)pvalDtls->Value.bin.lpb, NULL,
                                        NULL, NULL, DIALOG_MODAL);
            }
        }
        return;

    case IDC_MOVEDOWN:
    case IDC_MOVEUP:
        {
            int nInd, nIndNew;
            int nIndData, nIndDataNew;
#ifdef DEBUG
            int nTotal;
#endif
            char szStr[256];
            ADRENTRY ae = {0};
            HWND hLB = GetDlgItem(hDlg, IDC_ADDRLISTACTIVE);

            Assert(hLB);

            nInd = ListBox_GetCurSel(hLB);
            if (nInd == LB_ERR)
                break;
#ifdef DEBUG
            Assert(nInd != 0 || id != IDC_MOVEUP);

            nTotal = ListBox_GetCount(hLB);
            if(nTotal != LB_ERR)
                Assert(nInd != nTotal-1 || id != IDC_MOVEDOWN);
#endif

            if(IDC_MOVEDOWN == id)
                nIndNew = nInd + 1;
            else
                nIndNew = nInd - 1;

            nIndData = ListBox_GetItemData(hLB, nInd);
            if(nIndData == LB_ERR)
            {
                DebugTrace("Client: error retrieving listbox item data");
                break;
            }

            nIndDataNew = ListBox_GetItemData(hLB, nIndNew);
            if(nIndDataNew == LB_ERR)
            {
                DebugTrace("Client: error retrieving listbox item data");
                break;
            }

            pRouteData = (LPROUTEDATA) GetWindowLong(GetParent(hDlg), GWL_USERDATA);
            Assert(pRouteData);

            ae = pRouteData->palAddrListActive->aEntries[nIndData];
            pRouteData->palAddrListActive->aEntries[nIndData] =
            pRouteData->palAddrListActive->aEntries[nIndDataNew];
            pRouteData->palAddrListActive->aEntries[nIndDataNew] = ae;

            /*PopulateRouteListBox(hDlg);*/

            /*this works only because the two strings we swap are adjacent*/
            ListBox_GetText(hLB, nInd, szStr);
            ListBox_DeleteString(hLB, nInd);
            ListBox_InsertString(hLB, nIndNew, szStr);

            ListBox_SetItemData(hLB, nIndNew, nIndDataNew);
            ListBox_SetItemData(hLB, nInd, nIndData);

            ListBox_SetCurSel(GetDlgItem(hDlg, IDC_ADDRLISTACTIVE), nIndNew);
            ConfigMoveButtons(hDlg, GetDlgItem(hDlg, IDC_ADDRLISTACTIVE));
            break;
        }


    case IDC_ADDADDR:
        Assert(pabAddrB != NULL);
        memset(&AdrParm, 0, sizeof(AdrParm));
        AdrParm.ulFlags = AB_SELECTONLY | DIALOG_MODAL;
        AdrParm.lpszCaption = "Routing Slip";
        AdrParm.lpszNewEntryTitle = "NEW ENTRY";
        AdrParm.cDestFields = 1;
        AdrParm.nDestFieldFocus = 0;
        AdrParm.lppszDestTitles = &lpszTitles;
        AdrParm.lpulDestComps =  &ulrectps ;

        pRouteData = (LPROUTEDATA) GetWindowLong(GetParent(hDlg), GWL_USERDATA);
        Assert(pRouteData);

        hr = pabAddrB->lpVtbl->Address(pabAddrB, (LPULONG) &hDlg, &AdrParm, &pRouteData->palAddrListActive);

        if(GetScode(hr)!= MAPI_E_USER_CANCEL)
        {
            PopulateRouteListBox(hDlg);
            SetWindowText(GetDlgItem(hDlg, IDCANCEL), "Close");
            SetFocus(GetDlgItem(hDlg, IDCANCEL));

            ListBox_SetCurSel(GetDlgItem(hDlg, IDC_ADDRLISTACTIVE), 0);
            ConfigMoveButtons(hDlg, GetDlgItem(hDlg, IDC_ADDRLISTACTIVE));

        }
        return;

    case IDC_REMOVEADDR:
        nIndex = (UINT)ListBox_GetCurSel(GetDlgItem(hDlg, IDC_ADDRLISTACTIVE));
        if (nIndex == LB_ERR)
            break;

        /*items position in ADRLIST is stored with the item in the listbox*/
        nIndex1 = (UINT)ListBox_GetItemData(GetDlgItem(hDlg, IDC_ADDRLISTACTIVE), nIndex);
        if(nIndex1 == LB_ERR)
        {
            DebugTrace("Client: error retrieving listbox item data");
            break;
        }

        pRouteData = (LPROUTEDATA) GetWindowLong(GetParent(hDlg), GWL_USERDATA);
        Assert(pRouteData);

        /* Null out the removed item */
        MAPIFreeBuffer(pRouteData->palAddrListActive->aEntries[nIndex1].rgPropVals);
        pRouteData->palAddrListActive->aEntries[nIndex1].rgPropVals = NULL;
        pRouteData->palAddrListActive->aEntries[nIndex1].cValues = 0;

        ListBox_DeleteString(GetDlgItem(hDlg, IDC_ADDRLISTACTIVE), nIndex);

        if(nIndex > 0)
            --nIndex;

        ListBox_SetCurSel(GetDlgItem(hDlg, IDC_ADDRLISTACTIVE), nIndex);
        ConfigMoveButtons(hDlg, GetDlgItem(hDlg, IDC_ADDRLISTACTIVE));


        SetWindowText(GetDlgItem(hDlg, IDCANCEL), "Close");
        return;

    case IDCANCEL:

        EndDialog (hDlg, TRUE);
        return;

    default:
        break;
    }
}

void ConfigMoveButtons(HWND hDlg, HWND hLB)
{
    int nIndex;
    int nTotal;

    EnableWindow(GetDlgItem(hDlg, IDC_MOVEUP), FALSE);
    EnableWindow(GetDlgItem(hDlg, IDC_MOVEDOWN), FALSE);

    nIndex = (UINT)ListBox_GetCurSel(hLB);
    if (nIndex == LB_ERR)
        return;

    nTotal = ListBox_GetCount(hLB);
    if(nTotal == LB_ERR)
        return;

    if(nIndex)
        EnableWindow(GetDlgItem(hDlg, IDC_MOVEUP), TRUE);

    if(nIndex < nTotal-1)
        EnableWindow(GetDlgItem(hDlg, IDC_MOVEDOWN), TRUE);
}

/*
 *  Handles the Route Note dialog which is used for both composing
 *  and reading routing messages.
 *
 *  If RotueNoteDlg is called to route an existing msg, a pointer to
 *  the message is passed as a lParam to WM_INITDIALOG.
 *
 */

BOOL CALLBACK
RouteNoteDlgProc (HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    HANDLE_MSG(hDlg, WM_INITDIALOG, RT_OnInitDialog);

    HANDLE_MSG(hDlg, WM_COMMAND, RT_OnCommand);

    default:
        break;
    }
    return FALSE;
}

BOOL RT_OnInitDialog(HWND hDlg, HWND hwndFocus, LPARAM lParam)
{
    HRESULT hr;
    ULONG cVals = 0;
    LPSPropValue pvalProp = NULL;
    LPSTREAM lpstreamBody = NULL;
    STATSTG statstg = {0};
    LPSTR lpszNoteText = NULL;
    ULONG cb = 0;
    LPMESSAGE pmsgRead = (LPMESSAGE)lParam;
    LPROUTEDATA pRouteData = NULL;
    LPMESSAGE pmsgRoute = NULL;

    if(!MakeNewRouteMessage(pmsgRead, &pRouteData))
    {
        DebugTrace("Client: MakeNewRouteMessage failed (RT_OnInitDialog)");
        goto err;
    }

    if (pmsgRead)
    {
        hr = pmsgRead->lpVtbl->SetReadFlag(pmsgRead, MAPI_DEFERRED_ERRORS);
        /* RouteNote is being called to route  */
        /*  a message in the Inbox.  So, we'll initialize the   */
        /*  form with data from  pmsgRouteMsg */
        pmsgRoute = pRouteData->pmsgRouteMsg;
        Assert(pmsgRoute);

        hr = pmsgRoute->lpVtbl->GetProps(pmsgRoute, (LPSPropTagArray)&tagaMsgProps, 0,
                                                     &cVals, &pvalProp);
        Assert(cVals == EMSGPROPDIM);
        if(HR_SUCCEEDED(hr))
        {
            if(PROP_TYPE(pvalProp[EMSG_SUBJ].ulPropTag) == PT_ERROR)
            {
                DebugTrace("Client: Unable to retrieve subject");
                /*goto err;*/
            }
            else
            {
                SetDlgItemText(hDlg, IDC_RTSUBJECT, pvalProp[EMSG_SUBJ].Value.LPSZ);
                /* //$ */
            }

            if(PR_CONVERSATION_INDEX == pvalProp[EMSG_CONVIDX].ulPropTag)
            {
                LPSPropValue pval = &pvalProp[EMSG_CONVIDX];

                pRouteData->cbConvIdx = pval->Value.bin.cb;
                if(MAPIAllocateBuffer(pRouteData->cbConvIdx, &pRouteData->lpbConvIdx))
                {
                    DebugTrace("Client: MAPIAllocateBuffer failed\r\n");
                    pRouteData->lpbConvIdx = NULL;
                    pRouteData->cbConvIdx = 0;
                }
                else
                {
                    CopyMemory(pRouteData->lpbConvIdx, pval->Value.bin.lpb, pRouteData->cbConvIdx);
                }
            }
            else
            {
                pRouteData->lpbConvIdx = NULL;
                pRouteData->cbConvIdx = 0;
            }

            if(PROP_TYPE(pvalProp[EMSG_BODY].ulPropTag) == PT_ERROR)
            {
                if(GetScode(pvalProp[EMSG_BODY].Value.l) == MAPI_E_NOT_ENOUGH_MEMORY)
                {
                    hr = pmsgRoute->lpVtbl->OpenProperty(pmsgRoute, PR_BODY, &IID_IStream,
                                                STGM_READ, MAPI_DEFERRED_ERRORS,
                                                (LPUNKNOWN FAR *) &lpstreamBody);
                    if(S_OK != GetScode(hr))
                    {
                        DebugTraceResult(OpenProperty, hr);
                        goto err;
                    }
                    hr = lpstreamBody->lpVtbl->Stat(lpstreamBody, &statstg, STATFLAG_NONAME);
                    if(S_OK != GetScode(hr))
                    {
                        DebugTrace("IStream::Stat failed");
                        goto err;
                    }
                    Assert(statstg.cbSize.HighPart == 0);
                    if(MAPIAllocateBuffer(statstg.cbSize.LowPart + 1, (LPVOID FAR *) &lpszNoteText))
                    {
                        goto err;
                    }
                    hr = lpstreamBody->lpVtbl->Read(lpstreamBody, lpszNoteText,
                                                statstg.cbSize.LowPart, &cb);
                    if(S_OK != GetScode(hr))
                    {
                        DebugTrace("IStream::Read failed");
                        goto err;
                    }
                    lpszNoteText[statstg.cbSize.LowPart] = '\0';
                    SetDlgItemText(hDlg, IDC_RTNOTE, lpszNoteText);
                    MAPIFreeBuffer(lpszNoteText);
                    lpszNoteText = NULL;
                    lpstreamBody->lpVtbl->Release(lpstreamBody);
                    lpstreamBody = NULL;
                }
                else /* some other error (too bad) */
                {
                    DebugTrace("Client: error reading body");
                     /*//$goto err;*/
                }
            }
            else /* everything's fine */
            {
                SetDlgItemText(hDlg, IDC_RTNOTE, pvalProp[EMSG_BODY].Value.LPSZ);
            }
        }
        else  /* a real error*/
        {
            DebugTrace("Client: error reading body and subject");
            goto err;
        }
    
        if(pvalProp[EMSG_MSGFLAGS].ulPropTag == PR_MESSAGE_FLAGS)
        {
            if(pvalProp[EMSG_MSGFLAGS].Value.l & MSGFLAG_HASATTACH)
            {
                PopulateAttachList(hDlg, pRouteData);
            }
        }

        MAPIFreeBuffer(pvalProp);
        pvalProp = NULL;


        Assert(pRouteData->palAddrListOld || pRouteData->palAddrListActive);
    }
    else
    {
    /* if we are here it means we are creating a new message */
        pRouteData->lpbConvIdx = NULL;
        pRouteData->cbConvIdx = 0;
    }


    SetWindowLong(hDlg, GWL_USERDATA, (LONG) pRouteData);
    UlRelease(pmsgRead);
    return TRUE;

err:
    UlRelease(lpstreamBody);
    MAPIFreeBuffer(pvalProp);
    MAPIFreeBuffer(lpszNoteText);
    DeInitRouteData(pRouteData);
    UlRelease(pmsgRead);
    MakeMessageBox(hDlg, 0, IDS_INIDIAG, NULL, MBS_ERROR);
    EndDialog(hDlg, FALSE);
    return TRUE;
}

void RT_OnCommand(HWND hDlg, int id, HWND hwndCtl, UINT codeNotify)
{
    LONG cb, cLines;
    ULONG nAttNum;
    HRESULT hr;
    LPSTR lpszSubject = NULL;
    LPSTR lpszNoteText = NULL;
    /* +1 for SentMailEID; +2 for conversation topic*/  
    SPropValue spvProp[EMSGPROPDIM+2] = {0}; 
    LPSTREAM lpstreamBody = NULL;
    HCURSOR hcOld;
    UINT nFstRecip;
    LPROUTEDATA pRouteData = NULL;
    LPMESSAGE pmsgRoute = NULL;
    LPSPropProblemArray pProblems = NULL;
    ULONG cbNewConvIdx = 0;
    LPBYTE lpbNewConvIdx = NULL;


    switch (id)
        {
        case IDC_RTATTACH:
            if(!CreateNewAttachment(hDlg))
            {
                DebugTrace("CreateNewAttachment failed");
            }
            return;

        case IDC_RTDELATTACH:
            pRouteData = (LPROUTEDATA)GetWindowLong(hDlg, GWL_USERDATA);
            Assert(pRouteData);

            cb = ListBox_GetCurSel(GetDlgItem(hDlg, IDC_RTATTACHLIST));
            if(LB_ERR != cb)
            {
                nAttNum = ListBox_GetItemData(GetDlgItem(hDlg, IDC_RTATTACHLIST), cb);
                if(LB_ERR == nAttNum)
                {
                    DebugTrace("Client:GetItemData failed (routenote)");
                    break;
                }

                hr = pRouteData->pmsgRouteMsg->lpVtbl->DeleteAttach(pRouteData->pmsgRouteMsg, nAttNum, 0,
                                            NULL, 0);
                if(S_OK != GetScode(hr))
                {
                    DebugTrace("Client: DeleteAttach failed");
                    break;
                }
                ListBox_DeleteString(GetDlgItem(hDlg, IDC_RTATTACHLIST), cb);
            }

            break;

        case IDC_RTATTACHLIST:
            cb = ListBox_GetCurSel(hwndCtl);
                if(cb!=LB_ERR)
                {
                    EnableWindow(GetDlgItem(hDlg, IDC_RTSAVEATTACH), TRUE);
                    EnableWindow(GetDlgItem(hDlg, IDC_RTDELATTACH), TRUE);
                }
                else
                {
                    EnableWindow(GetDlgItem(hDlg, IDC_RTSAVEATTACH), FALSE);
                    EnableWindow(GetDlgItem(hDlg, IDC_RTDELATTACH), FALSE);
                }
            if(codeNotify != LBN_DBLCLK)
                break;
            /*fall through*/

        case IDC_RTSAVEATTACH:
            cb = ListBox_GetCurSel(GetDlgItem(hDlg, IDC_RTATTACHLIST));
            if(LB_ERR != cb)
            {
                SaveAttachment(hDlg, (UINT) cb);
            }
            break;

        case IDC_RTEDITROUTESLIP:
            DialogBox (hInst, "RouteSlipBox", hDlg, RouteBoxDlgProc);
            break;

        case IDC_RTROUTE:
            pRouteData = (LPROUTEDATA)GetWindowLong(hDlg, GWL_USERDATA);
            Assert(pRouteData);

            pmsgRoute = pRouteData->pmsgRouteMsg;
            Assert(pmsgRoute);
            if(!pRouteData->palAddrListActive && pRouteData->palAddrListOld)
            {
                MakeMessageBox(hDlg,0, IDS_LASTRECIP, NULL, MB_OK);
                break;
            }
            nFstRecip = FirstRecipient(pRouteData->palAddrListActive);
            if((!pRouteData->palAddrListActive && !pRouteData->palAddrListOld) || !nFstRecip)
            {
                MakeMessageBox(hDlg, 0, IDS_NORECIPS, NULL, MB_OK);
                break;
            }
            hcOld = SetCursor(hWaitCur);
            if (Edit_GetModify(GetDlgItem(hDlg, IDC_RTSUBJECT)))
            {
                cb = Edit_LineLength(GetDlgItem(hDlg, IDC_RTSUBJECT), 0);
                if (MAPIAllocateBuffer (cb + 1, (LPVOID far *) & lpszSubject))
                    goto err;

                GetDlgItemText (hDlg, IDC_RTSUBJECT, lpszSubject, (int)cb+1);
                spvProp[EMSG_SUBJ].ulPropTag = PR_SUBJECT;
                spvProp[EMSG_SUBJ].Value.LPSZ = lpszSubject;

            }
            else
            {
                spvProp[EMSG_SUBJ].ulPropTag = PR_NULL;
            }
            if (pRouteData->bNewMessage || Edit_GetModify(GetDlgItem(hDlg, IDC_RTNOTE)))
            {
                cLines = Edit_GetLineCount(GetDlgItem(hDlg, IDC_RTNOTE));

                if (cLines)
                {
                    /* Get the total number of bytes in the multi-line */

                    cb = Edit_LineIndex(GetDlgItem(hDlg, IDC_RTNOTE),(cLines - 1));
                    cb += Edit_LineLength(GetDlgItem(hDlg, IDC_RTNOTE), cb);

                    /* The next line is to account for CR-LF pairs per line. */

                    cb += cLines * 2;

                    if (MAPIAllocateBuffer (cb + 1, (LPVOID FAR *) & lpszNoteText))
                        goto err;

                    /* Get the Note Text from the edit */

                    GetDlgItemText (hDlg, IDC_RTNOTE, lpszNoteText, (int)cb);
                    spvProp[EMSG_BODY].ulPropTag = PR_BODY;
                    spvProp[EMSG_BODY].Value.LPSZ = lpszNoteText;
                }
            }
            else
            {
                spvProp[EMSG_BODY].ulPropTag = PR_NULL;
            }

            /*We want a copy of the message in the "Sent Mail" folder*/
            CopyMemory(&spvProp[EMSGPROPDIM], pvalSentMailEID, sizeof(SPropValue));

#ifdef DEBUG
            if(pRouteData->bNewMessage)
            {
                Assert(pRouteData->cbConvIdx == 0);
                Assert(pRouteData->lpbConvIdx == NULL);
            }
#endif
            if(!ScAddConversationIndex(pRouteData->cbConvIdx, pRouteData->lpbConvIdx,
                                        &cbNewConvIdx, &lpbNewConvIdx))
            {
                spvProp[EMSG_CONVIDX].ulPropTag = PR_CONVERSATION_INDEX;
                spvProp[EMSG_CONVIDX].Value.bin.cb = cbNewConvIdx;
                spvProp[EMSG_CONVIDX].Value.bin.lpb = lpbNewConvIdx;
            }
            else
            {
                spvProp[EMSG_CONVIDX].ulPropTag = PR_NULL;
            }

            if(pRouteData->bNewMessage)
            {
                spvProp[EMSGPROPDIM+1].ulPropTag = PR_CONVERSATION_TOPIC;
                if(PR_SUBJECT == spvProp[EMSG_SUBJ].ulPropTag)
                {
                    spvProp[EMSGPROPDIM+1].Value.LPSZ = spvProp[EMSG_SUBJ].Value.LPSZ;
                }
                else
                {
                    spvProp[EMSGPROPDIM+1].Value.LPSZ = "";
                }
            }
            else
            {
                spvProp[EMSGPROPDIM+1].ulPropTag = PR_NULL;
            }

            spvProp[EMSG_MSGFLAGS].ulPropTag = PR_NULL;
            
            hr = pmsgRoute->lpVtbl->SetProps(pmsgRoute, EMSGPROPDIM+2, spvProp, &pProblems);
            MAPIFreeBuffer(lpbNewConvIdx);
            lpbNewConvIdx = NULL;
            if(S_OK != GetScode(hr))
            {
                DebugTrace("Client: SetProps failed (RouteNote)");
                goto err;
            }
            else
            {
                if(pProblems)
                {   /* use nAttNum as an index for a sec */
                    for(nAttNum = 0; nAttNum < pProblems->cProblem; ++nAttNum)
                    {
                        switch(pProblems->aProblem[nAttNum].ulPropTag)
                        {
                        case PR_SENTMAIL_ENTRYID:
                            DebugTrace("Client: Error setting PR_SENTMAIL_ENTRYID");
                            goto err;

                        case PR_SUBJECT:
                            DebugTrace("Client: Error settting PR_SUBJECT");
                            goto err;
                        case PR_BODY:
                            if(MAPI_E_NOT_ENOUGH_MEMORY != pProblems->aProblem[nAttNum].scode)
                            {
                                DebugTrace("Client: Error settting PR_BODY");
                                goto err;
                            }
                            else /* have to use IStream */
                            {
                                hr = pmsgRoute->lpVtbl->OpenProperty(pmsgRoute, PR_BODY, &IID_IStream,
                                                STGM_READWRITE, MAPI_DEFERRED_ERRORS,
                                                (LPUNKNOWN FAR *) &lpstreamBody);
                                if(S_OK != GetScode(hr))
                                {
                                    DebugTraceResult(OpenProperty, hr);
                                    goto err;
                                }
                                hr = lpstreamBody->lpVtbl->Write(lpstreamBody, lpszNoteText, lstrlen(lpszNoteText), NULL);
                                if(S_OK != GetScode(hr))
                                {
                                    DebugTrace("IStream::Write failed");
                                    goto err;
                                }
                            }
                            break;
                        }
                    }
                }
            }


            DelRouteProps(pRouteData);
            if(!SetRouteProps(pRouteData))
            {
                DebugTrace("Client: SetRouteProps failed (RouteNote)");
                goto err;
            }

            if(!SetMessageClass(pRouteData->pmsgRouteMsg,  lpszSmplRTMsgClass))
            {
                DebugTrace("Client: SetMessageClass failed");
                goto err;
            }

            cb = pRouteData->palAddrListActive->cEntries;
            /* nFstRecip is the index of the first non NULL entry in the
            palAddrListActive. So we pretend for a sec that palAddrListActive had
            only one recipient to set a "TO" recipient in the pmsgRouteMsg */
            pRouteData->palAddrListActive->cEntries = nFstRecip;
            hr = pRouteData->pmsgRouteMsg->lpVtbl->ModifyRecipients(pRouteData->pmsgRouteMsg,
                                        0, pRouteData->palAddrListActive);
            pRouteData->palAddrListActive->cEntries = cb;
            if(S_OK != GetScode(hr))
            {
                DebugTrace("Client: ModifyRecipients faild (routenote)");
                goto err;
            }

            hr = pRouteData->pmsgRouteMsg->lpVtbl->SubmitMessage(pRouteData->pmsgRouteMsg, 0);
            if(S_OK != GetScode(hr))
            {
                MakeMessageBox(hDlg, GetScode(hr), IDS_SENDERROR, NULL, MBS_ERROR);
                goto err;
            }
            /*fall through*/

err:
        case IDCANCEL:

            if(IDCANCEL == id)
            {
                pRouteData = (LPROUTEDATA)GetWindowLong(hDlg, GWL_USERDATA);
                Assert(pRouteData);
                if(pRouteData->palAddrListActive||
                    Edit_GetModify(GetDlgItem(hDlg, IDC_RTNOTE)) ||
                    Edit_GetModify(GetDlgItem(hDlg, IDC_RTSUBJECT)))
                    {
                        if(MessageBox(hDlg, "Are you sure you want to close this form?",
                        "?", MB_YESNO) == IDNO)  break;
                    }
            }
            else
            {
                SetCursor(hcOld);
            }


            MAPIFreeBuffer (lpszSubject);
            MAPIFreeBuffer (lpszNoteText);
            UlRelease(lpstreamBody);
            lpstreamBody = NULL;
            DeInitRouteData(pRouteData);
            pRouteData = NULL;

            EndDialog (hDlg, TRUE);
            break;

        default:
            break;
        }
}

/* 
*   DeInitRouteData
*
*  releases pRouteData and everything that was in it
*/
void DeInitRouteData(LPROUTEDATA pRouteData)
{
    if(!pRouteData) return;

    FreePadrlist(pRouteData->palAddrListOld);
    FreePadrlist(pRouteData->palAddrListActive);
    UlRelease(pRouteData->pmsgRouteMsg);
    UlRelease(pRouteData->ptblAttach);
    MAPIFreeBuffer(pRouteData->lpbConvIdx);
    MAPIFreeBuffer(pRouteData);
}

/* Returns a 1-based index of the first recipent.
 returns 0 if all entries in the input address list are NULLs*/
UINT FirstRecipient(LPADRLIST lpAL)
{
    UINT idx;

    if(!lpAL || !lpAL->cEntries) return 0;

    for(idx = 0; idx < lpAL->cEntries; ++idx)
        if(lpAL->aEntries[idx].rgPropVals) return (idx+1);

    return 0;
}

void PopulateRouteListBox(HWND hDlg)
{
    LPADRENTRY lpadrent;
    LPSPropValue lpsprop;
    LPSTR pStr = NULL;
    LPROUTEDATA pRouteData = NULL;
    UINT iadrentry = 0, ilbitem = 0;



    UINT yOld = MINY, yActive = MINY;
    UINT cOld;
    UINT cActive;
    RECT rect;

    pRouteData = (LPROUTEDATA) GetWindowLong(GetParent(hDlg), GWL_USERDATA);

    Assert(pRouteData);

    if(!pRouteData->palAddrListOld && !pRouteData->palAddrListActive)
        return;

    /* some arithmetic to resize the listboxes.
       Make the listbox that has more entries taller*/
    if(pRouteData->palAddrListOld && pRouteData->palAddrListActive)
    {
        cOld = pRouteData->palAddrListOld->cEntries;
        cActive = pRouteData->palAddrListActive->cEntries;

        yOld = (UINT)LBLENGTH * cOld / (cOld + cActive);
        yActive = (UINT)LBLENGTH - yOld;
    }
    else if(pRouteData->palAddrListOld)
    {
        yActive = 0;
    }
    else
    {
        yOld = 0;
    }
    if(yOld < MINY)
    {
        yOld = MINY;
        yActive = LBLENGTH - MINY;
    }
    else if(yActive < MINY)
    {
        yActive = MINY;
        yOld = LBLENGTH - MINY;
    }

    rect.left = LBX;
    rect.top = OLDY;
    rect.right = DELTAX;
    rect.bottom = yOld;

    MapDialogRect(hDlg, &rect);

    SetWindowPos(GetDlgItem(hDlg, IDC_ADDRLISTOLD), 0,
                rect.left, rect.top, rect.right, rect.bottom, SWP_SHOWWINDOW);

    rect.left = LBX;
    rect.top = OLDY + yOld + DELTA;
    rect.right = DELTAX;
    rect.bottom = yActive;

    MapDialogRect(hDlg, &rect);

    SetWindowPos(GetDlgItem(hDlg, IDC_ADDRLISTACTIVE), 0,
                rect.left, rect.top, rect.right, rect.bottom, SWP_SHOWWINDOW);

    ListBox_ResetContent(GetDlgItem(hDlg, IDC_ADDRLISTOLD));
    ListBox_ResetContent(GetDlgItem(hDlg, IDC_ADDRLISTACTIVE));

    if(pRouteData->palAddrListOld)
    {

    for(iadrentry = 0, lpadrent = pRouteData->palAddrListOld->aEntries;
         lpadrent < pRouteData->palAddrListOld->aEntries+pRouteData->palAddrListOld->cEntries;
         ++lpadrent, ++iadrentry)
    {
        if(!lpadrent->rgPropVals) continue;

        /* IAddrBook::Addres doesn't guarantee the order of the props.
            So we have to loop through all of them */
        for(lpsprop = lpadrent->rgPropVals;
            lpsprop < lpadrent->rgPropVals + lpadrent->cValues; ++lpsprop)
        {
            if(lpsprop->ulPropTag ==  PR_DISPLAY_NAME)
            {
                pStr =  lpsprop->Value.LPSZ;
                ilbitem = ListBox_AddString(GetDlgItem(hDlg, IDC_ADDRLISTOLD), pStr);
                if(LB_ERR != ilbitem)
                    ListBox_SetItemData(GetDlgItem(hDlg, IDC_ADDRLISTOLD), ilbitem, iadrentry);
                break;
            }
        }
    }
    }
    if(pRouteData->palAddrListActive)
    {
        for(iadrentry = 0, lpadrent = pRouteData->palAddrListActive->aEntries;
             lpadrent < pRouteData->palAddrListActive->aEntries+pRouteData->palAddrListActive->cEntries;
             ++lpadrent, ++iadrentry)
        {
            if(!lpadrent->rgPropVals) continue;

            /* IAddrBook::Addres doesn't guarantee the order of the props.
            So we have to loop through all of them */
            for(lpsprop = lpadrent->rgPropVals;
                lpsprop < lpadrent->rgPropVals + lpadrent->cValues; ++lpsprop)
            {
                if(lpsprop->ulPropTag ==  PR_DISPLAY_NAME)
                {
                    pStr =  lpsprop->Value.LPSZ;
                    ilbitem = ListBox_AddString(GetDlgItem(hDlg, IDC_ADDRLISTACTIVE), pStr);
                    if(LB_ERR != ilbitem)    /* save the position of the entry in the addrlist for future refs*/
                        ListBox_SetItemData(GetDlgItem(hDlg, IDC_ADDRLISTACTIVE), ilbitem, iadrentry);
                    break;
                }
            }
        }
    }
}


/* Get the index of the current recip and total number of recipients
 * from the routing slip of the message
 */
BOOL GetRouteIndices(LPROUTEDATA pRouteData)
{
    HRESULT hr;
    LPSPropTagArray lpsptProp = NULL;
    LPSPropValue lpspv = NULL ;
    ULONG cProps = 0;
    LPMESSAGE pmsg = NULL;
    MAPINAMEID nmidRTPR[2];
    MAPINAMEID *pnmidRTPR[2] = {&nmidRTPR[0], &nmidRTPR[1]};

    nmidRTPR[0].lpguid = (LPGUID)&PS_PUBLIC_STRINGS;
    nmidRTPR[0].ulKind = MNID_STRING;
    nmidRTPR[0].Kind.lpwstrName =   L"CURRENT_RT_RECIP";
    nmidRTPR[1].lpguid = (LPGUID)&PS_PUBLIC_STRINGS;
    nmidRTPR[1].ulKind = MNID_STRING;
    nmidRTPR[1].Kind.lpwstrName =   L"TOTAL_RT_RECIP";

    Assert(pRouteData);

    pmsg = pRouteData->pmsgRouteMsg;
    Assert(pmsg);
    hr = pmsg->lpVtbl->GetIDsFromNames(pmsg, 2, pnmidRTPR, 0, &lpsptProp);
    if(S_OK != GetScode(hr))
    {
        DebugTraceResult(GetIDsFromNames, hr);
        goto err;
    }

    lpsptProp->aulPropTag[0] = PROP_TAG(PT_LONG, PROP_ID(lpsptProp->aulPropTag[0]));
    lpsptProp->aulPropTag[1] = PROP_TAG(PT_LONG, PROP_ID(lpsptProp->aulPropTag[1]));

    /* save for later use in setrouteindices() */
    pRouteData->tagCurrent = lpsptProp->aulPropTag[0];
    pRouteData->tagTotal = lpsptProp->aulPropTag[1];

    hr = pmsg->lpVtbl->GetProps(pmsg, lpsptProp, 0, &cProps, &lpspv);
    if(S_OK != GetScode(hr))
    {
        DebugTraceResult(GetProps, hr);
        goto err;
    }

    Assert(lpspv);
    pRouteData->nCurrentRouteRecip = lpspv[0].Value.l;
    pRouteData->nTotalRouteRecip = lpspv[1].Value.l;


err:
    MAPIFreeBuffer(lpsptProp);
    MAPIFreeBuffer(lpspv);
    return !hr;
}

BOOL SetRouteIndices(LPROUTEDATA pRouteData)
{

    HRESULT hr;
    LPSPropTagArray lpsptProp = NULL;
    SPropValue spvRTProp[2];
    LPSPropProblemArray pProblems = NULL;

    MAPINAMEID nmidRTPR[2];
    MAPINAMEID *pnmidRTPR[2] = {&nmidRTPR[0], &nmidRTPR[1]};

    Assert(pRouteData);

    ZeroMemory(&spvRTProp, 2*sizeof(SPropValue));

    /* if this is a new message, get PropIDs */
    if(pRouteData->bNewMessage)
    {
        nmidRTPR[0].lpguid = (LPGUID)&PS_PUBLIC_STRINGS;
        nmidRTPR[0].ulKind = MNID_STRING;
        nmidRTPR[0].Kind.lpwstrName =   L"CURRENT_RT_RECIP";
        nmidRTPR[1].lpguid = (LPGUID)&PS_PUBLIC_STRINGS;
        nmidRTPR[1].ulKind = MNID_STRING;
        nmidRTPR[1].Kind.lpwstrName =   L"TOTAL_RT_RECIP";

        hr = pRouteData->pmsgRouteMsg->lpVtbl->GetIDsFromNames(pRouteData->pmsgRouteMsg, 2, pnmidRTPR, MAPI_CREATE, &lpsptProp);
        if(S_OK != GetScode(hr))
        {
            DebugTraceResult(GetIDsFromNames, hr);
            goto err;
        }

        lpsptProp->aulPropTag[0] = PROP_TAG(PT_LONG, PROP_ID(lpsptProp->aulPropTag[0]));
        lpsptProp->aulPropTag[1] = PROP_TAG(PT_LONG, PROP_ID(lpsptProp->aulPropTag[1]));

        spvRTProp[0].ulPropTag = lpsptProp->aulPropTag[0];
        spvRTProp[1].ulPropTag = lpsptProp->aulPropTag[1];
    }
    else /* if we created this msg from one in the inbox, we already have the PropIDs*/
    {
        spvRTProp[0].ulPropTag = pRouteData->tagCurrent;
        spvRTProp[1].ulPropTag = pRouteData->tagTotal;

    }

    spvRTProp[0].Value.l = pRouteData->nCurrentRouteRecip;
    spvRTProp[1].Value.l = pRouteData->nTotalRouteRecip;

    hr = pRouteData->pmsgRouteMsg->lpVtbl->SetProps(pRouteData->pmsgRouteMsg, 2, spvRTProp, &pProblems);
    if(S_OK != GetScode(hr))
    {
        if(pProblems)
        {
            DebugTraceProblems("Client: ", pProblems);
            MAPIFreeBuffer(pProblems);
            pProblems = NULL;
        }
        DebugTraceResult(SetProps, hr);
        goto err;
    }


err:
    MAPIFreeBuffer(lpsptProp);

    return !hr;
}


void InitRouteNameIDArray(ULONG iRecip, LPMAPINAMEID  lpPropNames)
{
    ULONG idx;

    Assert (lpPropNames);
    for(idx = 0; idx < ROUTEPROPSETDIM; ++idx)
    {
        lpPropNames[idx].lpguid = (LPGUID)lpguidA[idx];
        lpPropNames[idx].ulKind = MNID_ID;
        lpPropNames[idx].Kind.lID = iRecip;
    }
}

BOOL GetRoutePropTagArray(ULONG iRecip, LPMESSAGE   lpM, LPSPropTagArray FAR * lppspta)
{
    MAPINAMEID nmidA[ROUTEPROPSETDIM];
    LPMAPINAMEID  lppnmidA[5];
    HRESULT hr;
    ULONG *pulptPropTag = NULL;
    UINT ulidx = 0;

    Assert(lpM);

    /*First create the 5 prop names and get IDs for them*/
    for(ulidx = 0; ulidx < ROUTEPROPSETDIM; ++ulidx)
        lppnmidA[ulidx] = &nmidA[ulidx];
    InitRouteNameIDArray(iRecip, nmidA);
    hr = lpM->lpVtbl->GetIDsFromNames(lpM, ROUTEPROPSETDIM, lppnmidA,
                                        MAPI_CREATE, lppspta);

    if(S_OK != GetScode(hr))
    {
        DebugTraceResult(GetIDsFromNames, hr);
        return FALSE;
    }
    Assert((*lppspta)->cValues == ROUTEPROPSETDIM);

    /*Now add right prop types */
    ulidx = 0;
    for(pulptPropTag = (*lppspta)->aulPropTag;
        pulptPropTag < (*lppspta)->aulPropTag + ROUTEPROPSETDIM; ++pulptPropTag, ++ulidx)
    {
     *pulptPropTag =  PROP_TAG(ulRoutePropTypes[ulidx], PROP_ID(*pulptPropTag));
    }

    return TRUE;
}


/* the output PropTag array contains nTotalRecip * ROUTEPROPSETDIM + 1
 * prop tags. The last one is PR_NULL.
 */
BOOL GetRoutePropTagArrayFast(ULONG nTotalRecip, LPMESSAGE lpM, BOOL fCreate,
                                LPSPropTagArray FAR * lppspta)
{
    LPMAPINAMEID pnmid = NULL;
    LPMAPINAMEID * ppnmid = NULL;
    HRESULT hr;
    ULONG *pulptPropTag = NULL;
    UINT ulidx = 0;
    /*//$ hack!!!  +1 is to save a spot for PR_RECIPIENT_TYPE */
    UINT nTotalProps = nTotalRecip * ROUTEPROPSETDIM + 1;
    

    Assert(lpM);

    if(hr = ResultFromScode(MAPIAllocateBuffer(nTotalProps * sizeof(MAPINAMEID),
                            (LPVOID FAR *)&pnmid)))
        return FALSE;

    ZeroMemory(pnmid, nTotalProps * sizeof(MAPINAMEID));

    if(hr = ResultFromScode(MAPIAllocateBuffer(nTotalProps * sizeof(LPMAPINAMEID),
                            (LPVOID FAR *)&ppnmid)))
        goto err;

    for(ulidx = 0; ulidx < nTotalProps; ++ulidx)
        ppnmid[ulidx] = &pnmid[ulidx];

    for(ulidx = 0; ulidx < nTotalRecip; ++ulidx )
        InitRouteNameIDArray(ulidx, &pnmid[ulidx * ROUTEPROPSETDIM]);

    //put someting reasonable in
    pnmid[nTotalProps-1].lpguid = (LPGUID)lpguidA[0];
    pnmid[nTotalProps-1].ulKind = MNID_ID;
    pnmid[nTotalProps-1].Kind.lID = 0;

    hr = lpM->lpVtbl->GetIDsFromNames(lpM, nTotalProps, ppnmid,
                        fCreate? MAPI_CREATE : 0, lppspta);
    if(hr) /* treat warnings as errors */
        goto err;

    Assert((*lppspta)->cValues == nTotalProps);
    
    ulidx = 0;
    for(pulptPropTag = (*lppspta)->aulPropTag;
        pulptPropTag < (*lppspta)->aulPropTag + nTotalProps - 1;
        ++pulptPropTag , ++ulidx)
    {
        *pulptPropTag = PROP_TAG(ulRoutePropTypes[ulidx % ROUTEPROPSETDIM],
                                PROP_ID(*pulptPropTag));
    }

    *pulptPropTag = PR_NULL;
    
err:
    MAPIFreeBuffer(pnmid);
    MAPIFreeBuffer(ppnmid);
        
    DebugTraceResult(ROUTECLI_GetRoutePropTagArray, hr);
    return (hr? FALSE : TRUE);
}

BOOL OpenOutFolder(HWND hWnd, LPMAPIFOLDER FAR * lppF)
{
    LPMAPIFOLDER lpfOutF = NULL;
    HRESULT hr;
    LPSPropValue lpspvFEID = NULL;
    ULONG  ulObjType = 0;

    Assert(pmdb);

    *lppF = NULL;
    hr = HrGetOneProp((LPMAPIPROP) pmdb, PR_IPM_OUTBOX_ENTRYID, &lpspvFEID);
    if(hr)
    {
        DebugTrace("Client: HrGetOneProp failed (OpneOutFolder)");
        goto err;
    }

    Assert(lpspvFEID->ulPropTag == PR_IPM_OUTBOX_ENTRYID);

    hr = pmdb->lpVtbl->OpenEntry(pmdb, lpspvFEID->Value.bin.cb,
                        (LPENTRYID)lpspvFEID->Value.bin.lpb, NULL,
                        MAPI_MODIFY | MAPI_DEFERRED_ERRORS,
                        &ulObjType, (LPUNKNOWN FAR *) &lpfOutF);
    if(S_OK != GetScode(hr))
    {
        DebugTrace("Client: OpenEntry (OpenOutFolder)");
        goto err;
    }

    *lppF = lpfOutF;


err:
    MAPIFreeBuffer(lpspvFEID);
    if(hr)
        MakeMessageBox(hWnd, GetScode(hr), IDS_OPENOUTB, NULL, MBS_ERROR);

    return !hr;

}

BOOL CreateOutMessage(LPMESSAGE FAR * lpmM)
{

    LPMESSAGE lpmResM = NULL;
    HRESULT hr;

    Assert(pfldOutBox);

    hr = pfldOutBox->lpVtbl->CreateMessage(pfldOutBox, NULL, MAPI_DEFERRED_ERRORS,
                                            &lpmResM);

    if(S_OK != GetScode(hr)) return FALSE;

    *lpmM = lpmResM;

    return TRUE;
}

BOOL MakeNewRouteMessage(LPMESSAGE pmsgRead, LPROUTEDATA FAR * ppRouteData)
{
    HRESULT hr;
    LPROUTEDATA pRouteData = NULL;
    LPSPropProblemArray pProblems = NULL;

    if(MAPIAllocateBuffer(sizeof(ROUTEDATA), (LPVOID FAR *) &pRouteData))
    {
        return FALSE;
    }
    ZeroMemory(pRouteData, sizeof(ROUTEDATA));

    if(!CreateOutMessage(&pRouteData->pmsgRouteMsg))
    {
        goto err;
    }

    if(!pmsgRead)   /*if called  to create a new message*/
    {
        pRouteData->bNewMessage = TRUE;
        *ppRouteData = pRouteData;
        return TRUE;
    }

     pRouteData->bNewMessage = FALSE;

    /* include attachments*/
    sptExcludedProps.cValues = EXCLUDED_PROPS_ON_REPLY - 1;

    hr = pmsgRead->lpVtbl->CopyTo(pmsgRead, 0, NULL,
                                  (LPSPropTagArray)&sptExcludedProps,
                                  0, NULL, &IID_IMessage,
                                  pRouteData->pmsgRouteMsg, 0, &pProblems);

    if(HR_FAILED(hr))
    {
        if(pProblems)

        {
            DebugTraceProblems("Client: ", pProblems);
            MAPIFreeBuffer(pProblems);
            pProblems = NULL;
        }

        goto err;
    }

    if(!GetRouteIndices(pRouteData))
    {
        goto err;
    }

    if(!GetRouteAddrLists(pRouteData))
    {
        goto err;
    }

    *ppRouteData = pRouteData;

    return TRUE;

err:
    UlRelease(pRouteData->pmsgRouteMsg);
    MAPIFreeBuffer(pRouteData);
    *ppRouteData = NULL;
    return FALSE;
}

/*Assumes that members nCurrentRouteRecip and nTotalRouteRecip were succesfully
 *set. Initializes palAddrListActive and palAddrListOld.
 */

BOOL GetRouteAddrLists(LPROUTEDATA pRouteData)
{
    LPSPropTagArray lpspta = NULL;
//  SizedSPropTagArray((ROUTEPROPSETDIM + 1), sspta);
    LPADRLIST lpalOld = NULL;
    LPADRLIST lpalActive = NULL;
    ULONG cbal = 0;
    HRESULT hr;
    UINT ulidx, ulidx1;
    ULONG cActiveRecip ;
    LPMESSAGE pmsg;
    ULONG cvalAllProps = 0;
    LPSPropValue pvalAllProps = NULL;
    
    Assert(pRouteData);
    Assert(!pRouteData->palAddrListActive);
    Assert(!pRouteData->palAddrListOld);

    pmsg = pRouteData->pmsgRouteMsg;
    Assert(pmsg);
    
    if(!GetRoutePropTagArrayFast(pRouteData->nTotalRouteRecip,
                            pmsg,
                            FALSE,
                            &lpspta))
        goto err;
        
    /* hack!! the output PropTag array contains nTotalRecip * ROUTEPROPSETDIM + 1
     * prop tags. The last one is PR_NULL. We do this to reserve a spot for
     * PR_RECIPIENT_TYPE
     */

    hr = pmsg->lpVtbl->GetProps(pmsg, lpspta, 0, &cvalAllProps, &pvalAllProps);
    MAPIFreeBuffer(lpspta);
    lpspta=NULL;
    if(HR_FAILED(hr))
        goto err;

    Assert(cvalAllProps == pRouteData->nTotalRouteRecip * ROUTEPROPSETDIM + 1);

    //
    // In case somebody does not handle PR_NULL in GetProps
    //
    pvalAllProps[cvalAllProps - 1].ulPropTag = PR_NULL;
    
    cActiveRecip = pRouteData->nTotalRouteRecip - pRouteData->nCurrentRouteRecip;

    /*First do the recipients already routed to */
    cbal =  CbNewADRLIST(pRouteData->nCurrentRouteRecip);
    if (MAPIAllocateBuffer(cbal, &lpalOld))
        goto err;
    ZeroMemory(lpalOld, cbal);

    lpalOld->cEntries = pRouteData->nCurrentRouteRecip;

    for(ulidx = 0; ulidx < pRouteData->nCurrentRouteRecip; ++ulidx)
    {
        LPSPropValue pval = NULL;

        hr = ResultFromScode(ScDupPropset(ROUTEPROPSETDIM +1,
                                &pvalAllProps[ulidx * ROUTEPROPSETDIM],
                                MAPIAllocateBuffer,
                                &pval));
        
        if(hr)
            goto err;
            
        lpalOld->aEntries[ulidx].rgPropVals = pval;
        lpalOld->aEntries[ulidx].cValues = ROUTEPROPSETDIM + 1;
            
        for(ulidx1 = 0; ulidx1 < ROUTEPROPSETDIM; ++ulidx1)
        {
            pval[ulidx1].ulPropTag = sptRouteProps.aulPropTag[ulidx1];
            pval[ulidx1].dwAlignPad = 0;
        }
        /*Have to set RECIPIENT_TYPE in order for IAddressBook::Address to show the
          recipient in one of its listboxes*/
        pval[ROUTEPROPSETDIM].ulPropTag = PR_RECIPIENT_TYPE;
        pval[ROUTEPROPSETDIM].dwAlignPad = 0;
        pval[ROUTEPROPSETDIM].Value.l = MAPI_TO;

    }
    
    if(cActiveRecip == 0)
    {
        pRouteData->palAddrListOld = lpalOld;
        pRouteData->palAddrListActive = NULL;
        goto ret;
    }

    /*Now the same for palAddrListActive*/
    cbal =  CbNewADRLIST(cActiveRecip);
    if (MAPIAllocateBuffer(cbal, &lpalActive))
        goto err;
    memset(lpalActive, 0, cbal);
    lpalActive->cEntries = cActiveRecip;
    for(ulidx = 0; ulidx < cActiveRecip; ++ulidx)
    {
        LPSPropValue pval = NULL;

        hr = ResultFromScode(ScDupPropset(ROUTEPROPSETDIM +1,
                            &pvalAllProps[(ulidx + pRouteData->nCurrentRouteRecip) *
                                                ROUTEPROPSETDIM],
                                MAPIAllocateBuffer,
                                &pval));
        
        if(hr)
            goto err;
            
        lpalActive->aEntries[ulidx].rgPropVals = pval;
        lpalActive->aEntries[ulidx].cValues = ROUTEPROPSETDIM + 1;
            
        for(ulidx1 = 0; ulidx1 < ROUTEPROPSETDIM; ++ulidx1)
        {
            pval[ulidx1].ulPropTag = sptRouteProps.aulPropTag[ulidx1];
            pval[ulidx1].dwAlignPad = 0;
        }
        /*Have to set RECIPIENT_TYPE in order for IAddressBook::Address to show the
          recipient in one of its listboxes*/
        pval[ROUTEPROPSETDIM].ulPropTag = PR_RECIPIENT_TYPE;
        pval[ROUTEPROPSETDIM].dwAlignPad = 0;
        pval[ROUTEPROPSETDIM].Value.l = MAPI_TO;

    }

    pRouteData->palAddrListOld = lpalOld;
    pRouteData->palAddrListActive = lpalActive;

ret:
    MAPIFreeBuffer(pvalAllProps);
    return TRUE;
err:
    FreePadrlist(lpalOld);
    FreePadrlist(lpalActive);
    MAPIFreeBuffer(pvalAllProps);
    
    return FALSE;
}


/*deletes all the props corresponding to the entries in palAddrListActive*/
BOOL  DelRouteProps(LPROUTEDATA pRouteData)
{
    UINT ulidx;
    LPSPropTagArray lpsptaRouteTags = NULL;
    LPSPropProblemArray lpsppaProblems = NULL;
    HRESULT hr = hrSuccess;

    if(!pRouteData->palAddrListActive) return TRUE;


    Assert(pRouteData);
    Assert(pRouteData->pmsgRouteMsg);

    for(ulidx = pRouteData->nCurrentRouteRecip; ulidx < pRouteData->nTotalRouteRecip; ++ulidx)
    {
        if(!GetRoutePropTagArray(ulidx, pRouteData->pmsgRouteMsg, &lpsptaRouteTags))
        {
            /*
            //$ even if it gives an error still have to go through all of them*/
            continue;
        }
        hr = pRouteData->pmsgRouteMsg->lpVtbl->DeleteProps(pRouteData->pmsgRouteMsg, lpsptaRouteTags, &lpsppaProblems);
        /* even if it gives an error still have to go through all of them*/
        if(lpsppaProblems)
        {
            DebugTraceProblems("Client:", lpsppaProblems);
            MAPIFreeBuffer(lpsppaProblems);
            lpsppaProblems = NULL;
        }

        MAPIFreeBuffer(lpsptaRouteTags);

        lpsptaRouteTags = NULL;

    }

    return (S_OK == GetScode(hr));
}

BOOL SetRouteProps(LPROUTEDATA pRouteData)
{
    //SPropValue pspvRouteProps[ROUTEPROPSETDIM];
    LPSPropTagArray lpsptaRouteTags = NULL;
    ULONG cRouteRecip;
    LPADRENTRY lpae = NULL;
    LPSPropValue lpspv = NULL;
    UINT ulidx;
    LPSPropProblemArray lpsppaProblems = NULL;
    HRESULT hr;
    UINT cNewRecips = 0;
    LPSPropValue pvalAll = NULL;
    LPSPropValue pval = NULL;

    Assert(pRouteData);
    if(!pRouteData->palAddrListActive) return TRUE;

    cRouteRecip = pRouteData->nCurrentRouteRecip;

    if(!GetRoutePropTagArrayFast(
                cRouteRecip + pRouteData->palAddrListActive->cEntries,
                pRouteData->pmsgRouteMsg,
                TRUE,
                &lpsptaRouteTags))
    {
        hr = ResultFromScode(E_FAIL);
        goto err;
    }

    if(hr = MAPIAllocateBuffer(
                    pRouteData->palAddrListActive->cEntries * ROUTEPROPSETDIM *
                        sizeof(SPropValue), (LPVOID *) &pvalAll))
        goto err;

    ZeroMemory(pvalAll, pRouteData->palAddrListActive->cEntries *
                        ROUTEPROPSETDIM * sizeof(SPropValue));

    /* get required properties missing in AddrlistActive*/
    hr = pabAddrB->lpVtbl->PrepareRecips(pabAddrB, 0, (LPSPropTagArray)&sptRouteProps,
                                                        pRouteData->palAddrListActive);
    if(S_OK != GetScode(hr))
    {
        DebugTrace("Client: PrepareRecips failed");
        goto err;
    }
    
    for(lpae = pRouteData->palAddrListActive->aEntries,
            pval = pvalAll, cNewRecips = 0;
        lpae < pRouteData->palAddrListActive->aEntries +
                pRouteData->palAddrListActive->cEntries;
            ++lpae )
    {
        if(!lpae->rgPropVals)
        {
            continue;
        }

        ++cNewRecips;
                
        Assert(lpae->rgPropVals[ROUTEPROPSET_EMAIL_ADDRESS].ulPropTag == PR_EMAIL_ADDRESS);
        pval[ROUTEPROPSET_EMAIL_ADDRESS].Value.LPSZ =
            lpae->rgPropVals[ROUTEPROPSET_EMAIL_ADDRESS].Value.LPSZ;

        Assert(lpae->rgPropVals[ROUTEPROPSET_ADDRTYPE].ulPropTag == PR_ADDRTYPE);
        pval[ROUTEPROPSET_ADDRTYPE].Value.LPSZ =
            lpae->rgPropVals[ROUTEPROPSET_ADDRTYPE].Value.LPSZ;

        Assert(lpae->rgPropVals[ROUTEPROPSET_DISPLAY_NAME].ulPropTag == PR_DISPLAY_NAME);
        pval[ROUTEPROPSET_DISPLAY_NAME].Value.LPSZ =
            lpae->rgPropVals[ROUTEPROPSET_DISPLAY_NAME].Value.LPSZ;
        
        Assert(lpae->rgPropVals[ROUTEPROPSET_ENTRYID].ulPropTag == PR_ENTRYID);
        pval[ROUTEPROPSET_ENTRYID].Value =
            lpae->rgPropVals[ROUTEPROPSET_ENTRYID].Value;

        Assert(lpae->rgPropVals[ROUTEPROPSET_SEARCH_KEY].ulPropTag == PR_SEARCH_KEY);
        pval[ROUTEPROPSET_SEARCH_KEY].Value =
            lpae->rgPropVals[ROUTEPROPSET_SEARCH_KEY].Value;

        pval += ROUTEPROPSETDIM;
    }

    
    for(ulidx = cRouteRecip * ROUTEPROPSETDIM, pval = pvalAll;
         ulidx < (cRouteRecip + cNewRecips)*ROUTEPROPSETDIM;
         ++pval, ++ulidx)
    {
        pval->ulPropTag = lpsptaRouteTags->aulPropTag[ulidx];
    }

    hr = pRouteData->pmsgRouteMsg->lpVtbl->SetProps(
                                            pRouteData->pmsgRouteMsg,
                                            cNewRecips * ROUTEPROPSETDIM,
                                            pvalAll,
                                            &lpsppaProblems);


    if(S_OK != GetScode(hr))
    {
        
        DebugTraceResult(SetProps, hr);
        goto err;
    }

    if(lpsppaProblems)
    {
        DebugTraceProblems("Client: SetProps", lpsppaProblems);
        MAPIFreeBuffer(lpsppaProblems);
        lpsppaProblems = NULL;
    }


    MAPIFreeBuffer(lpsptaRouteTags);
    lpsptaRouteTags = NULL;


    pRouteData->nTotalRouteRecip = pRouteData->nCurrentRouteRecip + cNewRecips;

    ++(pRouteData->nCurrentRouteRecip);
    if(!SetRouteIndices(pRouteData))
    {
        hr = ResultFromScode(E_FAIL);
        goto err;
    }

    
err:
    MAPIFreeBuffer(lpsptaRouteTags);
    MAPIFreeBuffer(lpsppaProblems);
    MAPIFreeBuffer(pvalAll);
    return ( hr ? FALSE : TRUE);
}

BOOL SetMessageClass(LPMESSAGE lpM, LPSTR lpszClass)
{
    HRESULT hr;
    SPropValue spvProp;

    spvProp.ulPropTag = PR_MESSAGE_CLASS;
    spvProp.dwAlignPad = 0;
    spvProp.Value.LPSZ = lpszClass;

    Assert(lpM);

    hr = HrSetOneProp((LPMAPIPROP)lpM, &spvProp);
    if(hr)
    {
        DebugTrace("Client: HrSetOneProp failed (SetMessageClass)");
        return FALSE;
    }

    return TRUE;
}

/* this functions works correctly only for received (saved) msgs*/
/*BOOL HasAttachment(LPMESSAGE lpM)
{
    HRESULT hr;
    LPSPropValue lpspvProp = NULL;
    LONG lflags = 0;

    Assert(lpM);

    hr = HrGetOneProp((LPMAPIPROP) lpM, PR_MESSAGE_FLAGS, &lpspvProp);
    if(hr)
    {
        DebugTrace("Client: HrGetOneProp failed (hasattachment)");
        goto err;
    }

    lflags = lpspvProp->Value.l;

err:
    MAPIFreeBuffer(lpspvProp);

    return lflags & MSGFLAG_HASATTACH;
}*/

BOOL PopulateAttachList(HWND hDlg, LPROUTEDATA pRouteData)
{
    SizedSPropTagArray (1, sptAttachNum) =  {   1,  {PR_ATTACH_NUM}  };
    LPSRowSet lprsRows = NULL;
    LPATTACH lpAttach = NULL;
    HRESULT hr;
    UINT idx, lbidx;
    LPSPropValue lpProp = NULL;
    SPropValue spvPosProp = {0};
    spvPosProp.ulPropTag = PR_RENDERING_POSITION;
    spvPosProp.Value.l = -1;

    Assert(pRouteData);
    Assert(pRouteData->pmsgRouteMsg);

    hr = pRouteData->pmsgRouteMsg->lpVtbl->
            GetAttachmentTable(pRouteData->pmsgRouteMsg, 0,
                                &pRouteData->ptblAttach);
    if(S_OK != hr)
    {
        DebugTrace("Client: GetAttachmentTable failed (PopulateAttachList)");
        goto err;
    }

    hr = HrQueryAllRows(pRouteData->ptblAttach, (LPSPropTagArray)&sptAttachNum, NULL,
                                        NULL, 0, &lprsRows);
    if(S_OK != hr)
    {
        DebugTrace("Client: QueryAllRows failed (PopulateAttachList)");
        goto err;
    }

    if(!lprsRows || !(lprsRows->cRows)) goto err;

    for(idx = 0; idx < lprsRows->cRows; ++idx)
    {
        Assert(lprsRows->aRow[idx].cValues == 1);
        Assert(lprsRows->aRow[idx].lpProps->ulPropTag == PR_ATTACH_NUM);

        hr = pRouteData->pmsgRouteMsg->lpVtbl->
            OpenAttach(pRouteData->pmsgRouteMsg,
                            lprsRows->aRow[idx].lpProps->Value.l,
                        NULL, MAPI_MODIFY | MAPI_DEFERRED_ERRORS, &lpAttach);
        if(S_OK != hr)
        {
            DebugTrace("Client: openattach failed (PopulateAttachList)");
            goto err;
        }

        hr = HrGetOneProp((LPMAPIPROP)lpAttach, PR_DISPLAY_NAME, &lpProp);
        if(hr)
        {
            DebugTrace("Client: HrGetOneProp failed (PopulateAttachList)");
            goto err;
        }
        lbidx = ListBox_AddString(GetDlgItem(hDlg, IDC_RTATTACHLIST), lpProp->Value.LPSZ);
        if(LB_ERR != lbidx)
        {
            ListBox_SetItemData(GetDlgItem(hDlg, IDC_RTATTACHLIST), lbidx,
                                    lprsRows->aRow[idx].lpProps->Value.l);
        }

        MAPIFreeBuffer(lpProp);
        lpProp = NULL;

        /* in received msgs attachment positions are not -1 any more.
            Set them to -1 again*/
        hr = HrSetOneProp((LPMAPIPROP)lpAttach, &spvPosProp);
        if(!hr)
        {
            hr = lpAttach->lpVtbl->SaveChanges(lpAttach, 0);
        }
        lpAttach->lpVtbl->Release(lpAttach);
        lpAttach = NULL;
    }

err:

    FreeProws(lprsRows);
    lprsRows = NULL;

    UlRelease(lpAttach);

    MAPIFreeBuffer(lpProp);

    return (S_OK == GetScode(hr));
}

BOOL CreateNewAttachment(HWND hDlg)
{
    OPENFILENAME ofn;
    char szFileName[MAX_PATH] = "";
    char szFilter[256];
    static char szFileTitle[16] = "";
    static char szDirName[256] = "";
    LPSTR lpszEndPath;
    UINT idx, lbidx;
    HRESULT hr;
    LPROUTEDATA pRouteData = NULL;

    enum { REND_POS, PATH_NAME, ATT_METHOD, DISP_NAME, ATT_FILENAME, ATT_DIM};

    SizedSPropTagArray(ATT_DIM , sptAttachTags) =
    { ATT_DIM,
        {   PR_RENDERING_POSITION, PR_ATTACH_PATHNAME,
            PR_ATTACH_METHOD, PR_DISPLAY_NAME, PR_ATTACH_FILENAME }
    };
    SPropValue spvAttachProps[ATT_DIM];

    LPATTACH lpAttach = NULL;
    ULONG ulAttachNum = 0;

    pRouteData = (LPROUTEDATA)GetWindowLong(hDlg, GWL_USERDATA);
    Assert(pRouteData);
    
#ifndef WIN16
    if (!szDirName[0])
        GetCurrentDirectory (255, (LPSTR) szDirName);
    else
#endif
        lstrcpy (szFileName, szFileTitle);

    if(!LoadString(hInst, IDS_FILTER, szFilter, sizeof(szFilter)))
    {
        DebugTrace("Client: failed to load a string");
        return FALSE;
    }

    for (idx = 0; szFilter[idx] != '\0'; idx++)
        if (szFilter[idx] == '|')
            szFilter[idx] = '\0';

    ofn.lStructSize = sizeof (OPENFILENAME);
    ofn.hwndOwner = 0;
    ofn.hInstance = 0;
    ofn.lpstrFilter = szFilter;
    ofn.lpstrCustomFilter = NULL;
    ofn.nMaxCustFilter = 0L;
    ofn.nFilterIndex = 1L;
    ofn.lpstrFile = szFileName;
    ofn.nMaxFile = 256;
    ofn.lpstrFileTitle = szFileTitle;
    ofn.nMaxFileTitle = 16;
    ofn.lpstrInitialDir = szDirName;
    ofn.lpstrTitle = "Attach";
    ofn.nFileOffset = 0;
    ofn.nFileExtension = 0;
    ofn.lpstrDefExt = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (!GetOpenFileName (&ofn))
        return FALSE;

    /* Save the directory for the next time we call this */

    lstrcpy (szDirName, szFileName);
    if (lpszEndPath = SzFindLastCh(szDirName, '\\'))
        *(lpszEndPath) = '\0';

    hr = pRouteData->pmsgRouteMsg->lpVtbl->CreateAttach(pRouteData->pmsgRouteMsg,
                                 NULL, MAPI_DEFERRED_ERRORS, &ulAttachNum, &lpAttach);
    if(S_OK != GetScode(hr))
    {
        DebugTrace("Client: CreateAttach failed (CreateNewAttach)");
        return FALSE;
    }

    for(idx = 0; idx < ATT_DIM; ++idx)
    {
        spvAttachProps[idx].ulPropTag = sptAttachTags.aulPropTag[idx];
        spvAttachProps[idx].dwAlignPad = 0;
    }

    spvAttachProps[REND_POS].Value.l = -1;
    spvAttachProps[PATH_NAME].Value.LPSZ = szFileName;
    spvAttachProps[ATT_METHOD].Value.l = ATTACH_BY_REF_RESOLVE;
    /* ATTACH_BY_REF_RESOLVE means the spooler wiil reslove the attachment into ATTACH_BY_VALUE
        and place the attachment data in PR_ATTACH_DATA_BIN */
    spvAttachProps[DISP_NAME].Value.LPSZ = szFileTitle;
    spvAttachProps[ATT_FILENAME].Value.LPSZ = szFileTitle;

    hr = lpAttach->lpVtbl->SetProps(lpAttach, ATT_DIM, spvAttachProps, NULL);
    if(S_OK != GetScode(hr))
    {
        DebugTrace("Client: SetProp failed (createnewattachment)");
        goto err;
    }

    hr = lpAttach->lpVtbl->SaveChanges(lpAttach, MAPI_DEFERRED_ERRORS);
    if(S_OK != GetScode(hr))
    {
        DebugTrace("Client: SaveChanges failed (createnewattachment)");
        goto err;
    }

    lbidx = ListBox_AddString(GetDlgItem(hDlg, IDC_RTATTACHLIST), szFileTitle);
    if(LB_ERR != lbidx)
    {
        /*Store the attachment # with its name in the listbox*/
        ListBox_SetItemData(GetDlgItem(hDlg, IDC_RTATTACHLIST), lbidx,
                                    ulAttachNum);
    }

err:
    UlRelease(lpAttach);

    return (S_OK == GetScode(hr));
}

void SaveAttachment( HWND hDlg, UINT itemindx)
{
    OPENFILENAME ofn;
    char szFileName[256] = "";
    char szFilter[256];
    static char szFileTitle[16];
    static char szDirName[256] = "";
    LPSTR lpszEndPath;
    ULONG idx;
    HRESULT hr;
    LPSPropValue lpProp = NULL;
    LPATTACH lpAttach = NULL;
    LPSTREAM lpstrAtt=NULL, lpstrFile=NULL;
    STATSTG statstg = {0};
    ULONG ulAttachNum;
    LPROUTEDATA pRouteData = NULL;

    pRouteData = (LPROUTEDATA)GetWindowLong(hDlg, GWL_USERDATA);
    if(!pRouteData)
    {
        DebugTrace("Client: pRouteData == 0 (saveattachment)");
        goto err;
    }

    if (!szDirName[0])
        GetTempPath (sizeof(szDirName), szDirName);

    if(!LoadString(hInst, IDS_FILTER, szFilter, sizeof(szFilter)))
    {
        DebugTrace("Client: failed to load a string");
        goto err;
    }

    for (idx = 0; szFilter[idx] != '\0'; idx++)
        if (szFilter[idx] == '|')
            szFilter[idx] = '\0';

    ulAttachNum = ListBox_GetItemData(GetDlgItem(hDlg, IDC_RTATTACHLIST), itemindx);
    if(LB_ERR == ulAttachNum)
    {
        DebugTrace("Client: can't get attach num (saveattachment)");
        return;
    }

    hr = pRouteData->pmsgRouteMsg->lpVtbl->
            OpenAttach(pRouteData->pmsgRouteMsg, ulAttachNum, NULL,
                        MAPI_BEST_ACCESS | MAPI_DEFERRED_ERRORS, &lpAttach);
    if(S_OK != GetScode(hr))
    {
        DebugTrace("Client: OpenAttach failed (saveattachment)");
        goto err;
    }

    hr = HrGetOneProp((LPMAPIPROP)lpAttach, PR_ATTACH_FILENAME, &lpProp);
    if(hr)
    {
        DebugTrace("Client: OpenAttach failed (saveattachment)");
        goto err;
    }

    lstrcpy (szFileName, lpProp->Value.LPSZ);
    MAPIFreeBuffer(lpProp);
    lpProp = NULL;

    ofn.lStructSize = sizeof (OPENFILENAME);
    ofn.hwndOwner = hDlg;
    ofn.hInstance = 0;
    ofn.lpstrFilter = szFilter;
    ofn.lpstrCustomFilter = NULL;
    ofn.nMaxCustFilter = 0L;
    ofn.nFilterIndex = 1L;
    ofn.lpstrFile = szFileName;
    ofn.nMaxFile = sizeof(szFileName);
    ofn.lpstrFileTitle = szFileTitle;
    ofn.nMaxFileTitle = sizeof(szFileTitle);
    ofn.lpstrInitialDir = szDirName;
    ofn.lpstrTitle = "Save Attachment";
    ofn.nFileOffset = 0;
    ofn.nFileExtension = 0;
    ofn.lpstrDefExt = NULL;
    ofn.Flags = OFN_SHOWHELP | OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;

    if (!GetSaveFileName (&ofn))
        goto err;

    /* Save the directory for the next time we call this */

    lstrcpy (szDirName, szFileName);
    if (lpszEndPath = SzFindLastCh(szDirName, '\\'))
        *(lpszEndPath) = '\0';


    hr = lpAttach->lpVtbl->OpenProperty (lpAttach, PR_ATTACH_DATA_BIN,
                                        (LPIID)&IID_IStream,
                                        0, MAPI_DEFERRED_ERRORS,
                                        (LPUNKNOWN *)&lpstrAtt);
    if(S_OK != GetScode(hr))
    {
        /*must be a new attachment*/
        hr = HrGetOneProp((LPMAPIPROP)lpAttach, PR_ATTACH_PATHNAME, &lpProp);
        if(hr)
        {
            DebugTrace("Client: PR_ATTACH_PATHNAME (saveattach)");
            goto err;
        }
        CopyFile(lpProp->Value.LPSZ, szFileName, TRUE);
        goto err;
    }

    hr = OpenStreamOnFile (MAPIAllocateBuffer, MAPIFreeBuffer,
                            STGM_CREATE | STGM_READWRITE | STGM_DIRECT | STGM_SHARE_EXCLUSIVE,
                            szFileName, NULL, &lpstrFile);
    if(S_OK != GetScode(hr))
    {
        DebugTrace("Client: OpenStreamOnFile failed (saveattachment)");
        goto err;
    }


    lpstrAtt->lpVtbl->Stat(lpstrAtt, &statstg, STATFLAG_NONAME);

    hr = lpstrAtt->lpVtbl->CopyTo(lpstrAtt, lpstrFile, statstg.cbSize, NULL, NULL);
    if(S_OK != GetScode(hr))
    {
        DebugTrace("Client: CopyTo failed (saveattachment)");
        goto err;
    }

err:
    UlRelease(lpstrAtt);
    UlRelease(lpstrFile);
    UlRelease(lpAttach);
    MAPIFreeBuffer(lpProp);
}

