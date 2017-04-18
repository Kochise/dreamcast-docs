/* --------------------------------------------------------------------------

Basic Forms example of a custom sendable form.  It is an EXE server
rather than a DLL.  It implements the minimum form interface required
to launch and send a form.

Copyright (C) 1995 Microsoft Corporation

-------------------------------------------------------------------------- */

//#define ALLOW_SUBCLASS_IPM // all other forms to subclass the reply behavior
                             // of this form (slower, but more correct)

#include <windows.h>
#include <windowsx.h>
#include <ole2.h>
#include <initguid.h>
#include <mapiform.h>
#define INITGUID
#include <initguid.h>
#include <mapix.h>
#include <mapiutil.h>
#include <mapinls.h>
#include "dbugit.h"
#include "check.h"
#include "form.h"
#include "dlg.h"

/*
 *  
 * Checkers form clsid.  This must match the configuration file.
 *  
 */

DEFINE_GUID(CLSID_MyFormsClsId,  0x86174010, 0x5030, 0x0076, 0x99, 0x12, 0x00, 0xaa, 0x00, 0x38, 0x90, 0x1b);

/*
 *  HrStartOleAndRegisterClassFactory
 *
 *  Purpose:
 *      Initialize OLE, MAPI, and the Forms Interface
 *      Should be called from WinMain() or InitApplication() in an SDI app
 *
 *      This function LoadLibraries the neccessary DLLs rather than
 *      linking with them.  This permits the form to run as a stand-
 *      alone executable even when MAPI and OLE are not installed.
 *
 *  Returns:
 *      HRESULT
 */

#ifdef _WIN32
#define szOleDll  "ole32.dll"
#define szMapiDll "mapi32.dll"
#else
#define szOleDll  "compobj.dll"
#define szMapiDll "mapi.dll"
#endif

HINSTANCE hinstOle   = NULL;
HINSTANCE hinstMapi  = NULL;


typedef HRESULT (FAR PASCAL *LPFNCOREGISTERCLASSOBJECT)(REFCLSID rclsid,
    IUnknown FAR * pUnk, DWORD dwClsContext, DWORD flags, LPDWORD lpdwRegister);
#ifdef WIN16
typedef BOOL (FAR PASCAL *LPFNISEQUALGUID)(REFGUID rguid1, REFGUID rguid2);
#undef IsEqualIID
#define IsEqualIID(riid1, riid2) (*lpfnIsEqualGUID)(riid1, riid2)
#endif
typedef HRESULT (FAR PASCAL *LPFNHRQUERYALLROWS)(LPMAPITABLE ptable, 
                        LPSPropTagArray ptaga, LPSRestriction pres,
                        LPSSortOrderSet psos, LONG crowsMax,
                        LPSRowSet FAR *pprows);
typedef ULONG   (FAR PASCAL *LPFNMAPIFREEBUFFER)(LPVOID pv);
typedef HRESULT (FAR PASCAL *LPFNMAPIINITIALIZE)(LPVOID lpvReserved);
typedef void    (FAR PASCAL *LPFNMAPIUNINITIALIZE)(VOID);
typedef void    (FAR PASCAL *LPFNMAPIFREEPADRLIST)(LPADRLIST);

LPFNCOREGISTERCLASSOBJECT lpfnCoRegisterClassObject;
#ifdef WIN16
LPFNISEQUALGUID           lpfnIsEqualGUID;
#endif
LPFNHRQUERYALLROWS        lpfnHrQueryAllRows       ;
LPFNMAPIFREEBUFFER        lpfnMAPIFreeBuffer       ;
LPFNMAPIINITIALIZE        lpfnMAPIInitialize       ;
LPFNMAPIUNINITIALIZE      lpfnMAPIUninitialize     ;
LPFNMAPIFREEPADRLIST      lpfnFreePadrlist          ;   

HRESULT
HrStartOleAndRegisterClassFactory(void)
{
    FRMFMR *    pfrmfmr = NULL;
    HRESULT     hr;

    TraceTag(tagFormFunc,"HrStartOleAndRegisterClassFactory");

    // ----- LoadLibrary the essentials
    hinstOle   = LoadLibrary(szOleDll);
    hinstMapi  = LoadLibrary(szMapiDll);
    #ifdef WIN16
    if (hinstOle   < HINSTANCE_ERROR) hinstOle   = 0;
    if (hinstMapi  < HINSTANCE_ERROR) hinstMapi  = 0;
    #endif
    if (0 == hinstOle || 0 == hinstMapi)
        {
        return ResultFromScode(E_FAIL);
        }
        

    // ----- Setup a few function pointers
    lpfnCoRegisterClassObject = (LPFNCOREGISTERCLASSOBJECT) GetProcAddress(hinstOle,  "CoRegisterClassObject");
#if defined(_WIN32) 
    #if defined(_X86_)
    lpfnHrQueryAllRows        = (LPFNHRQUERYALLROWS       ) GetProcAddress(hinstMapi,"HrQueryAllRows@24");
    lpfnFreePadrlist          = (LPFNMAPIFREEPADRLIST     ) GetProcAddress(hinstMapi,"FreePadrlist@4");
    #else
    lpfnHrQueryAllRows        = (LPFNHRQUERYALLROWS       ) GetProcAddress(hinstMapi,"HrQueryAllRows");
    lpfnFreePadrlist          = (LPFNMAPIFREEPADRLIST     ) GetProcAddress(hinstMapi,"FreePadrlist");
    #endif //_X86_
#else
    lpfnIsEqualGUID           = (LPFNISEQUALGUID          ) GetProcAddress(hinstOle,  "IsEqualGUID");
    lpfnHrQueryAllRows        = (LPFNHRQUERYALLROWS       ) GetProcAddress(hinstMapi,"HrQueryAllRows");
    lpfnFreePadrlist          = (LPFNMAPIFREEPADRLIST     ) GetProcAddress(hinstMapi,"FreePadrlist");
#endif //_WIN32
    lpfnMAPIFreeBuffer        = (LPFNMAPIFREEBUFFER       ) GetProcAddress(hinstMapi,"MAPIFreeBuffer");
    lpfnMAPIInitialize        = (LPFNMAPIINITIALIZE       ) GetProcAddress(hinstMapi,"MAPIInitialize");
    lpfnMAPIUninitialize      = (LPFNMAPIUNINITIALIZE     ) GetProcAddress(hinstMapi,"MAPIUninitialize");
    AssertSz(lpfnCoRegisterClassObject ,"missing lpfnCoRegisterClassObject");
    AssertSz(lpfnHrQueryAllRows        ,"missing lpfnHrQueryAllRows       ");
    AssertSz(lpfnMAPIFreeBuffer        ,"missing lpfnMAPIFreeBuffer       ");
    AssertSz(lpfnMAPIInitialize        ,"missing lpfnMAPIInitialize       ");
    AssertSz(lpfnMAPIUninitialize      ,"missing lpfnMAPIUninitialize     ");
    AssertSz(lpfnFreePadrlist          ,"missing lpfnFreePadrlist         ");
    if (0 == lpfnCoRegisterClassObject ||
        0 == lpfnHrQueryAllRows        ||
        0 == lpfnMAPIFreeBuffer        ||
        0 == lpfnMAPIInitialize        ||
        0 == lpfnMAPIUninitialize      ||
        0 == lpfnFreePadrlist)
        {
        AssertSz(0,"get procaddress failed");
        return ResultFromScode(E_FAIL);
        }    

    // ----- Initialize MAPI
    hr = (*lpfnMAPIInitialize)(NULL);
    if (S_OK != hr)
        {
        TraceTag(tagForm,"MapiInit failed 0x%08lx",hr);
        return hr;
        }

    // ----- Allocate Memory for our class factory
    pfrmfmr = new FRMFMR;
    if (NULL == pfrmfmr)
        {
        TraceTag(tagForm, "RegisterClassFactory: OOM 0x%08lx",hr);
        hr = ResultFromScode(E_OUTOFMEMORY);
        return hr;
        }

    // ----- Register our class object(s)
    DWORD dwRegMyForm = 0;
    hr = (*lpfnCoRegisterClassObject) (CLSID_MyFormsClsId, (LPUNKNOWN)pfrmfmr,
            CLSCTX_LOCAL_SERVER, REGCLS_SINGLEUSE,
            &dwRegMyForm); /* switch singleuse to multipleuse if you are an MDI app */
    if (FAILED(hr))
        {
        TraceTag(tagForm,"CoRegisterClassObject() failed 0x%08lx",hr);
        return hr;
        }

    TraceTag(tagForm,"return 0x%08lx",hr);
    return hr;
}

/*
 *  HrStopForms
 *
 *  Purpose:
 *      UnInitialize OLE, MAPI, and the Forms Interface
 *
 *  Returns:
 *      HRESULT == 0
 */
HRESULT
HrStopForms(void)
{
    HRESULT hr = ResultFromScode(S_OK);

    TraceTag(tagFormFunc,"HrStopForms");

    (*lpfnMAPIUninitialize)();

    FreeLibrary(hinstOle);
    FreeLibrary(hinstMapi);

    return hr;
}


/*
 *  S a m p l e   F o r m
 */

// Checkers form specific methods follow ///////////////////////////

/*
 *  FRM::ScGetRecipientAdrList
 *
 *  Purpose:
 *      Fill the addrlist with the current recipients in the message
 *
 *  Arguments:
 *      LPMESSAGE - the message (in)
 *      LPADRLIST - the addr list destination (out)
 *
 *  Returns:
 *      SCODE       Error status.
 */
SCODE
FRM::ScGetRecipientAdrlist(LPMESSAGE pmsg, LPADRLIST * ppal)
{
    SCODE           sc      = S_OK;
    HRESULT         hr;
    LPMAPITABLE     pmt     = NULL;
    LPSPropTagArray ptaga   = NULL;

    TraceTag(tagFormFunc,"ScGetRecipientAdrlist");
    AssertSz(!*ppal, "pal should be NULL on entry");
    AssertSz(cRef > 0,"excuse me.  are you refering to me?");

    // Get the recipient table from the message
    if (hr = pmsg->GetRecipientTable(MAPI_DEFERRED_ERRORS, &pmt))
    {
        TraceTag(tagForm,"2043 0x%08lx",hr);
        goto Cleanup;
    }

    if (hr = pmt->QueryColumns(TBL_ALL_COLUMNS, &ptaga))
    {
        TraceTag(tagForm,"sdlkfj 0x%08lx",hr);
        goto Cleanup;
    }

#ifdef NEVER
    ConvertToCorrectCharset(ptaga);
#endif

    // Read in the recipients
    hr = (*lpfnHrQueryAllRows)(pmt, ptaga, NULL, NULL, 0, (LPSRowSet *) ppal);
    if (hr)
    {
        TraceTag(tagForm,"sdfhjsadjfhadkflhxxxx 0x%08lx",hr);
        goto Cleanup;
    }

Cleanup:
    TraceTag(tagForm,"ScGetRecipientAdrlist 0x%08lx 0x%08lx", hr, sc);

    (*lpfnMAPIFreeBuffer)(ptaga);
    ReleaseObj(pmt);

    TraceTag(tagForm,"return 0x%08lx",ResultFromScode(sc));
    return sc;
}

/*
 *  FRM::SendForm
 *
 *  Purpose:
 *      Have the message site send us
 *      (also tries to send the message using mapi if message site fails)
 *
 *  Arguments:
 *      None.
 *
 *  Returns:
 *      HRESULT             Error status.
 */
HRESULT
FRM::SendForm(VOID)
{
    HRESULT hr = S_OK;

    TraceTag(tagFormFunc,"FRM::SendForm (this is not a standard form function)");

    AssertSz(cRef > 0,"excuse me.  are you refering to me?");
    Assert(pMessageSite);
    Assert(pMessage);

    // ----- Submit message
    if (hr = pMessageSite->SubmitMessage(0) )
    {
        TraceTag(tagForm,"failure pMessageSite->SubmitMessage 0x%08lx",hr);

        #ifndef GOOD_FORM_BEHAVIOR // the following is not standard behavior

        // ----- No harm in trying to send it myself
        if (IDYES == MessageBox(hMainWnd, "The message site failed to send this form.\nDo you want this form to attempt sending through the message interface?", "Checkers", MB_YESNO | MB_ICONSTOP))
        {
            // this is often times easier to debug than the remoted
            // message site interface (which does the same thing .. almost)

            if (hr = Save(NULL,TRUE))
                {
                TraceTag(tagForm,"NO: ::Save 0x%08lx",hr);
                }

            HandsOffMessage();

            if (hr = pMessage->SaveChanges(KEEP_OPEN_READWRITE) )
                {
                TraceTag(tagForm,"NO: pMessage->SaveChanges 0x%08lx",hr);
                }
            if (hr = pMessage->SubmitMessage(0) )
                {
                TraceTag(tagForm,"NO: pMessage->SubmitMessage 0x%08lx",hr);
                }
        }

        #endif // good_form_behavior
    }

    // ----- advise everyone of what we just did
    ADVISE(OnSubmitted)();

    TraceTag(tagForm,"return 0x%08lx",hr);
    return hr;
}

/*
 *  FRM::LaunchReplyMessage
 *
 *  Purpose:
 *      Construct a reply to PR_SENDER* (note: ignoring sent representing)
 *      Display any form user interface on the existing form
 *
 *  Arguments:
 *      HWND                Parent window
 *
 *  Returns:
 *      HRESULT             Error status.
 */
HRESULT
FRM::LaunchReplyMessage(ULONG ulhwndParent)
{
    #ifdef ALLOW_SUBCLASS_IPM
    LPMAPIFORM pNewForm;
    LPPERSISTMESSAGE pNewFormIPersist;
    #endif

    ULONG itaga;
    ADRLIST al = {1,0}; /* our adrlist will have exactly one entry */
    HRESULT hr = S_OK;
    LPMAPIMESSAGESITE pNewMessageSite;
    LPMAPIVIEWCONTEXT pNewMapiViewContext;
    LPMESSAGE pNewMessage;

    SizedSPropTagArray(6,tagaSender) =
        { 6,
        { PR_RECIPIENT_TYPE,
            PR_SENDER_NAME,
            PR_SENDER_ADDRTYPE,
            PR_SENDER_ENTRYID,
            PR_SENDER_EMAIL_ADDRESS,
            PR_SENDER_SEARCH_KEY } };
    SizedSPropTagArray(6,tagaRepliee) =
        { 6,
        { PR_RECIPIENT_TYPE,
            PR_DISPLAY_NAME,
            PR_ADDRTYPE,
            PR_ENTRYID,
            PR_EMAIL_ADDRESS,
            PR_SEARCH_KEY
        } };
    static SizedSPropTagArray(26,tagaRemoveFromNewReply) =
        { 26,
        {   // Stuff you would typically want to remove on reply
            PR_MESSAGE_FLAGS,               // Want unsent compose note
            PR_MESSAGE_RECIPIENTS,          // Will generate new recip list
            PR_SENDER_ENTRYID,              // Clear sender/recipient info
            PR_SENDER_NAME,                 //
            PR_RECEIVED_BY_ENTRYID,         //
            PR_RECEIVED_BY_NAME,            //
            PR_SENT_REPRESENTING_ENTRYID,   // Clear delegate access stuff
            PR_SENT_REPRESENTING_NAME,      //
            PR_SENT_REPRESENTING_ADDRTYPE,  // 10961
            PR_SENT_REPRESENTING_EMAIL_ADDRESS,
            PR_RCVD_REPRESENTING_ENTRYID,   // 
            PR_RCVD_REPRESENTING_NAME,      //
            PR_READ_RECEIPT_ENTRYID,        // Clear destination overrides
            PR_REPORT_ENTRYID,              //
            PR_REPLY_RECIPIENT_ENTRIES,     //
            PR_REPLY_RECIPIENT_NAMES,       //
            PR_ORIGINATOR_DELIVERY_REPORT_REQUESTED, // Clear delivery receipt
            PR_READ_RECEIPT_REQUESTED,      // Clear read receipt
            PR_CLIENT_SUBMIT_TIME,          // Clear submit time
            PR_MESSAGE_ATTACHMENTS,         // Drop attachments on reply
            PR_ORIGINAL_AUTHOR_ENTRYID,     // Keep original author information
            PR_ORIGINAL_AUTHOR_NAME,        //  on forwards
            PR_ORIGINAL_SUBMIT_TIME,        // Keep original time on forwards
            PR_IMPORTANCE,                  // Lose importance on reply
            PR_PRIORITY,                    // Lose priority on reply
            PR_SENSITIVITY                  // Lose sensitivity on reply
        } };

    TraceTag(tagFormFunc,"FRM::LaunchReplyMessage");
    AssertSz(cRef > 0,"excuse me.  are you refering to me?");
    Assert(pMessageSite);
    Assert(pSession);
    Assert(pMessage);

    #ifdef ALLOW_SUBCLASS_IPM

    /*
       Since I am a single instance exe, creating a new form results in
       a new process.  For performance reasons, this form does not conform
       to the forms API precisely. This effectively removes the ability to
       subclass the reply note for IPM.Checkers.  This is acceptable.

    */

    // ----- open form manager
    AssertSz(NULL == pFormMgr,"two form managers?");
    hr = pMessageSite->GetFormManager(&pFormMgr);
    if (FAILED(hr))
        {
        TraceTag(tagForm,"failure MAPIOpenFormMgr 0x%08lx",hr);
        return hr;
        }
    Assert(pFormMgr);

    // ----- Get form info
    hr = pFormMgr->ResolveMessageClass("IPM.Checkers",0,NULL,&pFormInfo);
    if (FAILED(hr))
        {
        TraceTag(tagForm,"failure to ResolveMessageClass 0x%08lx",hr);
        return hr;
        }

    // ----- Create the new form
    hr = pFormMgr->CreateForm(0,0,pFormInfo,IID_IMAPIForm,(LPVOID FAR*) &pNewForm);
    if (FAILED(hr))
        {
        TraceTag(tagForm,"failure to CreateForm 0x%08lx",hr);
        return hr;
        }

    hr = pNewForm->QueryInterface(IID_IPersistMessage, (LPVOID FAR*) &pNewFormIPersist);
    if (FAILED(hr))
        {
        TraceTag(tagForm,"failure asking form for IPersistMessage 0x%08lx",hr);
        return hr;
        }
    AssertSz(pNewFormIPersist,"have it?");

    #endif // ALLOW_SUBCLASS_IPM

    // ----- Create the reply message
    hr = pMessageSite->NewMessage(0,NULL,
        #ifdef ALLOW_SUBCLASS_IPM
        pNewFormIPersist
        #else
        this
        #endif // ALLOW_SUBCLASS_IPM
        ,&pNewMessage,&pNewMessageSite,&pNewMapiViewContext);
    if (FAILED(hr))
        {
        TraceTag(tagForm,"failure VDOG_*NewMessage* comform...c 0x%08lx",hr);
        return hr;
        }
    AssertSz(pNewMessage,"nothing new with you");
    AssertSz(pNewMessageSite,"no new site?");
    AssertSz(pNewMapiViewContext,"no new view context ... did NewMessage work at all?");

    // ----- Copy current message to new message
    hr = pMessage->CopyTo(0, NULL, (LPSPropTagArray)&tagaRemoveFromNewReply, 0, NULL,
                                    (LPIID) &IID_IMessage, pNewMessage, 0, NULL);
    if (FAILED(hr))
        {
        TraceTag(tagForm,"failure CopyTo 0x%08lx",hr);
        return hr;
        }

    // ----- who sent this to us?
    hr = pMessage->GetProps((LPSPropTagArray) &tagaSender, 0, &al.aEntries[0].cValues, &al.aEntries[0].rgPropVals);
    AssertSz(ResultFromScode(MAPI_W_ERRORS_RETURNED) == hr,"mapi gave me pr_recipient_type, but should not have");

    // ----- Make the sender the recipient
    if (al.aEntries && al.aEntries[0].rgPropVals)
    {
        al.aEntries[0].rgPropVals[0].ulPropTag = PR_RECIPIENT_TYPE;
        al.aEntries[0].rgPropVals[0].Value.ul = MAPI_TO;
    }
    else
    {
        AssertSz(0,"could not form reply message: al.aEntries && al.aEntries[0].rgPropVals");
        return ResultFromScode(E_FAIL);
    }

    // ----- Set our new recipients properties to their expected property ids
    itaga = 1;

    TraceTag(tagForm,"0x%08lx cEntries",al.cEntries);
    TraceTag(tagForm,"0x%08lx <0x%08lx> %s",al.aEntries[0].rgPropVals[itaga].ulPropTag,al.aEntries[0].rgPropVals[itaga].Value.ul,al.aEntries[0].rgPropVals[itaga].Value.LPSZ);

    for (itaga = 1; itaga < tagaRepliee.cValues; itaga++)
        {
        al.aEntries[0].rgPropVals[itaga].ulPropTag =
            PROP_TAG(PROP_TYPE(al.aEntries[0].rgPropVals[itaga].ulPropTag),
                PROP_ID(tagaRepliee.aulPropTag[itaga]));

        TraceTag(tagForm,"0x%08lx <0x%08lx> %d",al.aEntries[0].rgPropVals[itaga].ulPropTag,al.aEntries[0].rgPropVals[itaga].Value.ul,itaga);

        AssertSz(SUCCEEDED(al.aEntries[0].rgPropVals[itaga].Value.ul),"Failure to get PR_SENDER* 10961 ");
        }

    // ----- Save out addresses
    AssertSz(1 == al.cEntries,"we only reply to one person");
    hr = pNewMessage->ModifyRecipients(0, &al);
    if (FAILED(hr) )
        {
        TraceTag(tagForm,"pMessage->ModifyRecipients 0x%08lx",hr);
        return hr;
        }

    // ----- Release everything the read form was remembering (if we reply inplace)
    #ifndef ALLOW_SUBCLASS_IPM
    Forget();
    #endif

    // ----- Call LoadForm (this makes the current form the new form)
    hr =
    #ifdef ALLOW_SUBCLASS_IPM
    pNewFormIPersist->
    #endif
    Load(pNewMessageSite,pNewMessage,0,MSGFLAG_UNSENT);
    if (FAILED(hr))
        {
        TraceTag(tagForm,"failure LoadForm 0x%08lx",hr);
        return hr;
        }

    // ----- Call SetViewContext
    #ifdef ALLOW_SUBCLASS_IPM
    hr = pNewForm->SetViewContext(pNewMapiViewContext);
    if (FAILED(hr))
        {
        TraceTag(tagForm,"failure SetViewContext 0x%08lx",hr);
        return hr;
        }
    #endif

    // ----- Call DoVerb So we can see the reply form
    hr = 
    #ifdef ALLOW_SUBCLASS_IPM
    pNewForm->
    #endif
    DoVerb(OLEIVERB_PRIMARY,NULL,ulhwndParent,NULL);
    if (FAILED(hr))
        {
        TraceTag(tagForm,"failure DoVerb 0x%08lx",hr);
        return hr;
        }

    // ----- release stuff
    pNewMessage->Release();
    pNewMessageSite->Release();
    pNewMapiViewContext->Release();
    (*lpfnMAPIFreeBuffer)(al.aEntries[0].rgPropVals);

    // ----- Close down the read form (that's me)
    #ifdef ALLOW_SUBCLASS_IPM
    hr = ShutdownForm(OLECLOSE_NOSAVE);
    if (FAILED(hr))
        {
        TraceTag(tagForm,"failure ShutdownForm'ing read form 0x%08lx",hr);
        return hr;
        }
    #endif // ALLOW_SUBCLASS_IPM

    // ----- return to caller
    return hr;

}

/*
 *  FRM::GetCheckersData
 *
 *  Purpose:
 *      Allows anyone to query the form for it's current data
 *
 *  Arguments:
 *      data members (out)
 *
 *  Returns:
 *      void
 */
VOID
FRM::GetCheckersData(SQUARE* out_b, int* out_turn, long* out_movenum, long* out_score)
{
    Assert(out_b);
    AssertSz(cRef > 0,"excuse me.  are you refering to me?");

    if (turn) /* set elements only if we have data to give out */
    {
        memcpy(out_b,b,sizeof(b));
        if (out_turn) *out_turn = turn;
        if (out_movenum) *out_movenum = movenum;
        if (out_score) *out_score = score;
    }
}

/*
 *  FRM::SetCheckersData
 *
 *  Purpose:
 *      Allows anyone to set the forms current data members
 *
 *  Arguments:
 *      data members (in)
 *
 *  Returns:
 *      void
 */
VOID
FRM::SetCheckersData(SQUARE* in_b, int in_turn, long in_movenumber, long in_score)
{
    AssertSz(cRef > 0,"excuse me.  are you refering to me?");
    Assert(in_b && in_turn);

    fDirty = TRUE;

    memcpy(b,in_b,sizeof(b));
    turn    = in_turn;
    movenum = in_movenumber;
    score   = in_score;
}


/*
 *  FRM::AddressForm
 *
 *  Purpose:
 *      Look at the current message addresses, and show user
 *      interface to address the message.
 *
 *  Arguments:
 *      HWND - parent
 *      BOOL - true if no user interface should be presented when
 *             recipients are already present
 *
 *  Returns:
 *      HRESULT Error Status.
 */
HRESULT
FRM::AddressForm(HWND hwnd, BOOL fDontShowIfRecipsExist)
{
    LPADRBOOK   pAdrBook;
    ULONG       ulUIParam = (ULONG) (UINT) hwnd;
    SCODE       sc;
    HRESULT     hr = S_OK;
    ADRPARM     ap = { 0 };
    LPADRLIST   pal = NULL;
    BOOL        fCloseForm = FALSE;

    TraceTag(tagFormFunc,"FRM::AddressForm");

    AssertSz(cRef > 0,"excuse me.  are you refering to me?");
    Assert(pMessageSite);
    Assert(pSession);
    Assert(pMessage);

    // ----- Read in addresses from message
    sc = ScGetRecipientAdrlist(pMessage, &pal);
    hr = ResultFromScode(sc);
    if (FAILED(hr))
        {
        TraceTag(tagForm,"failed to read address into pal 0x%08lx",hr);
        return hr;
        }

    // ----- remember address book from the session
    hr = pSession->OpenAddressBook(ulUIParam, NULL, 0, &pAdrBook);
    if (FAILED(hr))
        {
        TraceTag(tagForm,"failed to get pAdrBook object 0x%08lx",hr);
        goto cleanuppal;
        }

    // ----- Show the address book
    ap.ulFlags = AB_RESOLVE | DIALOG_OPTIONS | DIALOG_MODAL | fMapiUnicode;
    ap.lpszCaption = TEXT("Select Checkers Opponent");
    ap.cDestFields = 1;
    if (0 == fDontShowIfRecipsExist || 0 == pal->cEntries)
        hr = pAdrBook->Address(&ulUIParam, &ap, &pal);
    #ifdef DEBUG
    if (hwnd != hMainWnd)
    {
        TraceTag(tagNull,"ADDRESSFORM: pAdrBook->Address changed it's out parameter even though DIALOG_MODAL");
    }
    #endif
    if (FAILED(hr))
    {
        // cancel is a failed scode
        TraceTag(tagForm,"cant pop up addr book 0x%08lx %d",hr,pal?pal->cEntries:0);
    }

    // ----- Save out addresses
    AssertSz(pMessage,"pMessage said goodbye during the Address function");
    hr = pMessage->ModifyRecipients(0, pal);
    if (FAILED(hr) )
        {
        TraceTag(tagForm,"pMessage->ModifyRecipients 0x%08lx",hr);
        goto cleanup;
        }

    // ----- Close the form if there are no recipients for this move
    if (pal->cEntries <= 0) fCloseForm = TRUE;

    // ----- Release the address book, adrlist, and clean up
cleanup:
    Assert(pAdrBook);
    pAdrBook->Release();
cleanuppal:
    Assert(pal);
    (*lpfnFreePadrlist)(pal);
    if (fCloseForm) ShutdownForm(OLECLOSE_PROMPTSAVE);

    TraceTag(tagForm,"return 0x%08lx",hr);
    return hr;
}

/*
 *  FRM::Remember
 *
 *  Purpose:
 *      Store and addref the message site, the message, and the session
 *      for later use
 *
 *  Returns:
 *      HRESULT Error Status.
 */
HRESULT
FRM::Remember(LPMAPIMESSAGESITE pmsite, LPMESSAGE pmsg)
{
    HRESULT hr;

    TraceTag(tagFormFunc,"FRM::Remember");

    AssertSz(cRef > 0,"excuse me.  are you refering to me?");
    AssertSz(pmsite,"what am I going to do without it?");
    AssertSz(pmsg,"what am I going to do without it? pmsg that is");

    // ----- remember our message site object
    AssertSz(!pMessageSite,"who me? a message site?");
    pMessageSite = pmsite;
    pMessageSite->AddRef();

    // ----- remember our message
    AssertSz(!pMessage,"a message in my");
    pMessage = pmsg;
    pMessage->AddRef();

    // ----- remember mapi session
    AssertSz(!pSession,"another session?");
    hr = pMessageSite->GetSession(&pSession);

    #ifdef DEBUG    
    if (FAILED(hr))
    {
        TraceTag(tagForm,"failed to get session object %08lx",hr);
    }    
    #endif

    // ----- return result to caller
    TraceTag(tagForm,"return 0x%08lx",hr);
    return hr;

}

/*
 *  FRM::Forget
 *
 *  Purpose:
 *      Release the message site, the message, and the session
 *
 *  Returns:
 *      HRESULT Error Status.
 */
HRESULT
FRM::Forget(VOID)
{
    TraceTag(tagFormFunc,"FRM::Forget");

    if (pMessage) pMessage->Release();
    if (pMessageSite) pMessageSite->Release();
    if (pSession) pSession->Release();

    pMessage = NULL;
    pMessageSite = NULL;
    pSession = NULL;

    return NOERROR;
}

/*
 *  FRM::ShowCurrentMessage
 *
 *  Purpose:
 *      Display any form user interface on a form
 *
 *  Arguments:
 *      HWND                Parent window
 *
 *  Returns:
 *      HRESULT             Error status.
 */
HRESULT
FRM::ShowCurrentMessage(ULONG ulhwndParent)
{
    HRESULT hr = NOERROR;

    TraceTag(tagFormFunc,"FRM::ShowCurrentMessage");

    AssertSz(cRef > 0,"excuse me.  are you refering to me?");
    Assert(pMessageSite);
    Assert(pSession);
    Assert(pMessage);

    // ----- Give our user access to our form interface
    SendMessage(hMainWnd,EM_GIVEFORMTOHWND,0,(LPARAM) this);

    // ----- Display address book modal to form if this message has not yet been addressed
    FORWARD_WM_COMMAND(hMainWnd, IDM_ADDRESS, 0, 1 /* Don't Show Recips */, PostMessage);

    return hr;
}

// IUnknown methods follow ///////////////////////////

/*
 *  FRM::QueryInterface
 *
 *  Purpose:
 *      Returns a pointer to the specified interface.
 *
 *  Arguments:
 *      REFIID              Interface we want.
 *      LPUNKNOWN *         Interface we return.
 *
 *  Returns:
 *      HRESULT             Error status.
 */
STDMETHODIMP
FRM::QueryInterface(REFIID riid, LPVOID FAR * ppvObj)
{
    HRESULT hr = NOERROR;

    TraceTag(tagFuncTriv,"FRM::QueryInterface %s",DumpCLSID(riid));
    AssertSz(cRef > 0,"excuse me.  are you refering to me?");

    if (IsEqualIID(riid, IID_IUnknown))
        {
        AddRef();
        *ppvObj = (IMAPIForm *)this;
        }
    else if (IsEqualIID(riid, IID_IPersistMessage))
        {
        AddRef();
        *ppvObj = (IPersistMessage *)this;
        }
    else if (IsEqualIID(riid, IID_IMAPIForm))
        {
        AddRef();
        *ppvObj = (IMAPIForm *)this;
        }
    else
        {
        hr = ResultFromScode(E_NOINTERFACE);
        *ppvObj = NULL;
        }
    
    #ifdef DEBUG
    if (hr != ResultFromScode(E_NOINTERFACE)) AssertSz(ppvObj,"no object pointer");
    #endif

    TraceTag(tagForm,"return 0x%08lx",hr);
    return hr;
}


/*
 *  FRM::AddRef
 *
 *  Purpose:
 *      Increments reference count on the sample extension.
 *
 *  Arguments:
 *
 *  Returns:
 *      ULONG               New value of reference count.
 */
STDMETHODIMP_(ULONG)
FRM::AddRef(void)
{
    TraceTag(tagFuncTriv,"FRM::AddRef ret %d",cRef + 1);
    AssertSz(cRef > 0,"excuse me.  are you refering to me?");
    return ++cRef;
}


/*
 *  FRM::Release
 *
 *  Purpose:
 *      Decrements reference count on the sample extension.  If count is
 *      decremented to zero, the object is freed.
 *
 *  Arguments:
 *
 *  Returns:
 *      ULONG               New value of reference count.
 */
STDMETHODIMP_(ULONG)
FRM::Release(void)
{
    TraceTag(tagFuncTriv,"FRM::Release cRef %d",cRef);
    AssertSz(cRef > 0,"excuse me.  are you refering to me?");

    if (!(--cRef))
        {
        // ----- be sure our ui is gone when we leave
        #ifdef DEBUG
        if (IsWindow(hMainWnd))
            {
            TraceTag(tagForm,"Last Release called, but IsWindow(hMainWnd).  ShutdownForm called?");
            }
        TraceTag(tagForm,"return 0");
        #endif //debug
        delete this;
        return 0;
        }
    return cRef;
}


// IPersistMessage methods follow ///////////////////////////

/*
 *  FRM::GetLastError
 *
 *  Purpose:
 *      Get the last error
 *
 *  Arguments:
 *
 *  Returns:
 *      HRESULT             NOERROR always.
 */
STDMETHODIMP
FRM::GetLastError(HRESULT hResult, ULONG ulFlags, LPMAPIERROR FAR * lppMAPIError)
{
    TraceTag(tagFormFunc,"FRM::GetLastError 0x%08x",hResult);
    AssertSz(cRef > 0,"excuse me.  are you refering to me?");
    if (lppMAPIError) *lppMAPIError = NULL;
    return NOERROR;
}

/*
 *  FRM::GetClassID
 *
 *  Purpose:
 *      Get the class ID associated with this message.
 *
 *  Arguments:
 *      LPCLSID             Where to put the class ID.
 *
 *  Returns:
 *      HRESULT             NOERROR always.
 */
STDMETHODIMP
FRM::GetClassID(LPCLSID pclsid)
{
    
    TraceTag(tagFormFunc,"FRM::GetClassID");
    AssertSz(cRef > 0,"excuse me.  are you refering to me?");

    // The form only plays with things of its own class ID, so
    // this is easy; it's more complicated if code supports multiple
    // classes, or can do "treat as" operations
    if (pclsid) *pclsid = clsid;

    return NOERROR;
}


/*
 *  FRM::IsDirty
 *
 *  Purpose:
 *      Returns whether the object has changed since the last save
 *
 *  Arguments:
 *
 *  Returns:
 *      HRESULT             S_OK if dirty, S_FALSE if not dirty.
 */
STDMETHODIMP
FRM::IsDirty(void)
{
    TraceTag(tagFormFunc,"FRM::IsDirty");
    AssertSz(cRef > 0,"excuse me.  are you refering to me?");
    
    return fDirty ? NOERROR : ResultFromScode(S_FALSE);
}


/*
 *  FRM::InitNew
 *
 *  Purpose:
 *      Create a new message of our message class in the provided pmsg.
 *
 *  Arguments:
 *      LPMAPISESSION       Session in which the message belongs.
 *      LPMESSAGE           Message to create the new form in.
 *
 *  Returns:
 *      HRESULT             S_OK, or error value.
 */
STDMETHODIMP
FRM::InitNew(LPMAPIMESSAGESITE pmsite, LPMESSAGE pmsg)
{
    HRESULT             hr;
    SPropValue          prop;

    TraceTag(tagFormFunc,"FRM::InitNew");
    AssertSz(cRef > 0,"excuse me.  are you refering to me?");

    // ----- Remember our pointers and such
    hr = Remember(pmsite,pmsg);
    if (FAILED(hr))
    {
        TraceTag(tagForm,"loss of memory in initnew 0x%08lx",hr);
        return hr;
    }

    // ----- set our message class
    prop.ulPropTag  = PR_MESSAGE_CLASS;
    prop.Value.LPSZ = TEXT("IPM.Checkers");
    hr = pMessage->SetProps(1, &prop, NULL);
    if (FAILED(hr) )
        {
        TraceTag(tagForm,"failed setprops in initnew 0x%08lx",hr);
        return hr;
        }

    // ----- remind ourselves that this new message could not have been sent
    fSentMessage = 0;

    // ----- set our special properties
    prop.ulPropTag  = PR_SUBJECT;
    prop.Value.LPSZ = TEXT("--- CHECKERS FORM ---");
    hr = pMessage->SetProps(1, &prop, NULL);
    if (FAILED(hr) )
        {
        TraceTag(tagForm,"failed setprops in on pr_subject here 0x%08lx",hr);
        return hr;
        }

    ADVISE(OnNewMessage)();
    return hr;
}


/*
 *  FRM::Load
 *
 *  Purpose:
 *      Attaches our object to the provided pmsg.
 *
 *  Arguments:
 *      LPMAPISESSION       Our session to remember.
 *      LPMESSAGE           Our message to remember.
 *
 *  Returns:
 *      HRESULT             S_OK, or error value.
 */
STDMETHODIMP
FRM::Load(LPMAPIMESSAGESITE pmsite, LPMESSAGE pmsg, ULONG ulMessageStatus, ULONG ulMessageFlags)
{
    ULONG cProps = 0;
    #define ctagMax 10
    char rgchTaga[sizeof(SPropTagArray) + (ctagMax * sizeof(ULONG))];
    LPSPropTagArray ptaga = (LPSPropTagArray) rgchTaga;
    LPSPropValue rgval = NULL;
    LPSPropValue pval = NULL;
    HRESULT         hr=S_OK;

    TraceTag(tagFormFunc,"FRM::Load status=0x%08lx flags=0x%08lx",ulMessageStatus,ulMessageFlags);
    AssertSz(cRef > 0,"excuse me.  are you refering to me?");

    // ----- Remember our pointers and such
    hr = Remember(pmsite,pmsg);
    if (FAILED(hr))
        {
        TraceTag(tagForm,"loads call to remember failed 0x%08lx",hr);
        return hr;
        }

    // ----- If this message has been sent we would like to remember that
    fSentMessage = !( ulMessageFlags & MSGFLAG_UNSENT);
    TraceTag(tagForm,"fSentMessage = %d",(int) fSentMessage);

    // ----- Load our data out of the message like a nice form
    ptaga->cValues = 0;
    ptaga->aulPropTag[ptaga->cValues++] = PR_SUBJECT;
    ptaga->aulPropTag[ptaga->cValues++] = PR_BODY;
    ptaga->aulPropTag[ptaga->cValues++] = PR_BOARD;
    ptaga->aulPropTag[ptaga->cValues++] = PR_TURN;
    ptaga->aulPropTag[ptaga->cValues++] = PR_MOVENUMBER;

    hr = pmsg->GetProps(ptaga,0, &cProps, &rgval);
    if (FAILED(hr) )
        {
        TraceTag(tagForm,"failed getprops on pr_board there 0x%08lx",hr);
        return hr;
        }
    AssertSz(ptaga->cValues <= ctagMax, "Too many properties to read!");
    AssertSz(cProps == ptaga->cValues,"to mucho values");
    pval = rgval;

    // ----- set properties to variables
    pval;   // subject
    pval++; // body
    pval++; // board
    if (pval->Value.bin.cb == sizeof(b)) /* if it's a valid board */
        {
        memcpy(b,pval->Value.bin.lpb,(int) pval->Value.bin.cb);
        pval++; // turn
        AssertSz(pval->Value.l == RED || pval->Value.l == BLACK,"cool: neither red or blacks turn according to mapi");
        turn = (int) pval->Value.l;
        pval++; // movenumber
        }
    Assert(rgval);
    (*lpfnMAPIFreeBuffer)(rgval);
    ADVISE(OnNewMessage)();
    return hr;
}


/*
 *  FRM::Save
 *
 *  Purpose:
 *      Writes out our information to the provided pmsg. Does NOT commit
 *      changes; this is the responsibility of the caller. Puts the form
 *      into no-scribble mode until SaveCompleted is called.
 *
 *  Arguments:
 *      LPMESSAGE           Message to write our changes to.
 *      BOOL                TRUE if this is our home message, FALSE if
 *                          this is a different message.
 *
 *  Returns:
 *      HRESULT             S_OK, or error value.
 */
STDMETHODIMP
FRM::Save(LPMESSAGE pmsg, ULONG fSameAsLoad)
{
    SPropValue prop;
    HRESULT hr = NOERROR;

    TraceTag(tagFormFunc,"FRM::Save");

    AssertSz(cRef > 0,"excuse me.  are you refering to me?");
    AssertSz(pMessage,"no pmesssg in ::Save");
    #ifdef DEBUG
    if (!pmsg)
    {
        TraceTag(tagNull,"NULL == pmsg in ::Save fsameasload==0x%08lx",fSameAsLoad);
    }
    #endif

    // ----- If this is the same pmsg as we got back when we loaded ...
    if (fSameAsLoad)
    {
        TraceTag(tagForm,"fSameAsLoad true");
        pmsg = pMessage;
    }

    // ----- Put ourselves in no-scribble mode
    fNoScribble = TRUE;

    // ----- set our message class
    prop.ulPropTag  = PR_MESSAGE_CLASS;
    prop.Value.LPSZ = TEXT("IPM.Checkers");
    hr = pMessage->SetProps(1, &prop, NULL);
    if (FAILED(hr) )
        {
        TraceTag(tagForm,"failed setprops in initnew 0x%08lx",hr);
        return hr;
        }

    // ----- Write out our data
    AssertSz(turn,"nobody's turn? this is not a good sign...");
    prop.ulPropTag  = PR_BOARD;
    prop.Value.bin.lpb = (unsigned char *) b;
    prop.Value.bin.cb  = sizeof(b);
    hr = pmsg->SetProps(1, &prop, NULL);
    if (FAILED(hr) )
        {
        TraceTag(tagForm,"failed setprops in on pr_board here 0x%08lx",hr);
        return hr;
        }
    prop.ulPropTag  = PR_TURN;
    prop.Value.l = (long) turn;
    hr = pmsg->SetProps(1, &prop, NULL);
    if (FAILED(hr) )
        {
        TraceTag(tagForm,"failed setprops in on pr_turn here 0x%08lx",hr);
        return hr;
        }
    prop.ulPropTag  = PR_MOVENUMBER;
    prop.Value.l = (long) movenum;
    hr = pmsg->SetProps(1, &prop, NULL);
    if (FAILED(hr) )
        {
        TraceTag(tagForm,"failed setprops in on pr_turn here 0x%08lx",hr);
        return hr;
        }
    prop.ulPropTag  = PR_SCORINGFUNC;
    prop.Value.l = (long) score;
    hr = pmsg->SetProps(1, &prop, NULL);
    if (FAILED(hr) )
        {
        TraceTag(tagForm,"failed setprops in on pr_turn here 0x%08lx",hr);
        return hr;
        }
    prop.ulPropTag  = PR_BODY;
    prop.Value.lpszA = TextizeBoard(b);
    TraceTag(tagForm,"Here's the board I saved:\n%s",prop.Value.lpszA);
    hr = pmsg->SetProps(1, &prop, NULL);
    if (FAILED(hr) )
        {
        TraceTag(tagForm,"failed setprops in on pr_body here 0x%08lx",hr);
        return hr;
        }


    ADVISE(OnSaved)();
    return hr;
}


/*
 *  FRM::SaveCompleted
 *
 *  Purpose:
 *      Terminates no-scribble and hands-off modes, returning the object
 *      to its normal storage mode.
 *
 *  Arguments:
 *      LPMESSAGE           Our new home message, if we need to change.
 *
 *  Returns:
 *      HRESULT             S_OK, or error value.
 */
STDMETHODIMP
FRM::SaveCompleted(LPMESSAGE pmsg)
{
    TraceTag(tagFormFunc,"FRM::SaveCompleted");
    AssertSz(cRef > 0,"excuse me.  are you refering to me?");

    // Reset modes
    fDirty = FALSE;
    fNoScribble = FALSE;

    return NOERROR;
}


/*
 *  FRM::HandsOffMessage
 *
 *  Purpose:
 *      Releases our reference on the message so that a Save As operation
 *      can occur.
 *
 *  Arguments:
 *
 *  Returns:
 *      HRESULT             S_OK, or error value.
 */
STDMETHODIMP
FRM::HandsOffMessage(void)
{
    TraceTag(tagFormFunc,"FRM::HandsOffMessage");
    AssertSz(cRef > 0,"excuse me.  are you refering to me?");
    return NOERROR;
}


// IMAPIForm methods follow /////////////////////////////

/*
 *  FRM::DoVerb
 *
 *  Purpose:
 *      Performs the specified verb on the message.
 *
 *  Arguments:
 *      LONG                What to do.
 *      LPMAPIVIEWCONTEXT   Our view context.
 *      HWND                Our parent window.
 *      LPCRECT             Where we should display ourselves given a choice.
 *
 *  Returns:
 *      HRESULT             S_OK, or error value.
 */
STDMETHODIMP
FRM::DoVerb(LONG iVerb, LPMAPIVIEWCONTEXT pmvc, ULONG ulhwndParent,
               LPCRECT prcPosRect)
{
    TraceTag(tagFormFunc,"FRM::DoVerb iVerb=%d",iVerb);
    AssertSz(cRef > 0,"excuse me.  are you refering to me?");

    switch (iVerb)
        {
        default:
        case OLEIVERB_HIDE:
        case OLEIVERB_DISCARDUNDOSTATE:
            TraceTag(tagForm,"DoVerb: not implemented iVerb");
            return ResultFromScode(E_NOTIMPL);

        case OLEIVERB_UIACTIVATE:
        case OLEIVERB_INPLACEACTIVATE:
            TraceTag(tagForm,"DoVerb: not implemented iVerb=%d",iVerb);
            if (iVerb < 0)
                return ResultFromScode(E_NOTIMPL);
            return ResultFromScode(OLEOBJ_S_INVALIDVERB);

        case OLEIVERB_SHOW:
            ShowCurrentMessage(ulhwndParent);
            return NOERROR;

        case OLEIVERB_OPEN:
        case OLEIVERB_PRIMARY:
            TraceTag(tagForm,"fSentMessage = %d",(int) fSentMessage);
            if (fSentMessage)
                LaunchReplyMessage(ulhwndParent);
            else
                ShowCurrentMessage(ulhwndParent);

            return NOERROR;
        }
}


/*
 *  FRM::ShutdownForm
 *
 *  Purpose:
 *      Closes down any UI associated with the form.
 *
 *  Arguments:
 *      DWORD               One of OLECLOSE_SAVEIFDIRTY, OLECLOSE_NOSAVE,
 *                          or OLECLOSE_PROMPTSAVE.
 *
 *  Returns:
 *      HRESULT             S_OK, or error value.
 */
STDMETHODIMP
FRM::ShutdownForm(DWORD dwSaveOptions)
{
    HRESULT hr = NOERROR;

    TraceTag(tagFormFunc,"FRM::ShutdownForm dwSaveOptions=%d",dwSaveOptions);
    TraceTag(tagForm,"pMessageSite 0x%08x",(ULONG) pMessageSite);
    AssertSz(cRef > 0,"excuse me.  are you refering to me?");

    // ----- no way I'm closeing if I'm in a modal dialog
    //       especially if the modal dialog occurs in a remoted interface
    if (!IsWindowEnabled(hMainWnd))
        return ResultFromScode(E_ABORT);

    // ----- be kind, and save ourself  
    switch (dwSaveOptions)
    {
        case OLECLOSE_NOSAVE:
            break;

        case OLECLOSE_SAVEIFDIRTY:
            if (fDirty)
                hr = pMessageSite->SaveMessage();
            break;

        default:
        case OLECLOSE_PROMPTSAVE:
            if (fDirty)
                if (IDYES == MessageBox(hMainWnd, "Save changes?", "Checkers", MB_YESNO))
                    hr = pMessageSite->SaveMessage();
            break;

    }

    Assert(hMainWnd && IsWindow(hMainWnd));
    if (NOERROR == hr)
    {
        // ----- let everyone know we're shutting down
        ADVISE(OnShutdown)();

        // ----- Release everything we have remembered thus far
        Forget();

        // ----- make sure everyone has Unadvised
        AssertSz(0==afAdvisee[0],"0 didn't Unadvise before ShutdownForm");
        AssertSz(0==afAdvisee[1],"1 didn't Unadvise before ShutdownForm");
        AssertSz(0==afAdvisee[2],"2 didn't Unadvise before ShutdownForm");
        AssertSz(0==afAdvisee[3],"3 didn't Unadvise before ShutdownForm");

        // ----- post a quit message to our UI
        SendMessage(hMainWnd,WM_CLOSE,0,0);
    }

    return hr;
}

STDMETHODIMP
FRM::SetViewContext(LPMAPIVIEWCONTEXT pViewContextNew)
{
    TraceTag(tagFormFunc,"FRM::SetViewContext");
    AssertSz(cRef > 0,"excuse me.  are you refering to me?");
    AssertSz(pViewContextNew,"no view context to set");

    /* View context is used for next and previous behavior
       The checkers form does not do next and previous because
       there is not a standard read note.  It is always in 
       reply mode */

    return NOERROR;
}

STDMETHODIMP
FRM::GetViewContext(LPMAPIVIEWCONTEXT FAR * ppViewContext)
{
    TraceTag(tagFormFunc,"FRM::GetViewContext");
    AssertSz(cRef > 0,"excuse me.  are you refering to me?");
    AssertSz(ppViewContext,"get view context to where?");

    if (ppViewContext) *ppViewContext = NULL; /* not supported */

    return NOERROR;
}

STDMETHODIMP
FRM::Advise(LPMAPIVIEWADVISESINK pAdvise, ULONG FAR * pdwStatus)
{
    LONG i;

    TraceTag(tagFormFunc,"FRM::Advise");

    AssertSz(cRef > 0,"excuse me.  are you refering to me?");
    Assert(pdwStatus);
    Assert(pAdvise);

    // ----- remember who to advise    
    for (i=0; i<MAX_ADVISE; i++)
        if (!afAdvisee[i])
        {
            aAdvisePtrs[i] = pAdvise;
            afAdvisee[i] = 1;
            *pdwStatus = i + 1; /* ulConnection of zero is not valid */
            pAdvise->AddRef();
            return NOERROR;
        }

    // ----- bad news
    AssertSz(0,"out of aAdvisPtrs");
    return ResultFromScode(E_FAIL);
    return NOERROR;
}

STDMETHODIMP
FRM::Unadvise(ULONG ulConnection)
{
    TraceTag(tagFormFunc,"FRM::Unadvise");

    AssertSz(cRef > 0,"excuse me.  are you refering to me?");
    AssertSz(ulConnection < MAX_ADVISE && ulConnection >= 0,"testing, 123");
    AssertSz(ulConnection,"a non-zero ulConnection is not valid according to OLE");

    // ----- forget about advising this guy
    --ulConnection; // remember, we added one in advise
    AssertSz(afAdvisee[(int) ulConnection],"never wanted ::Advise in ::Unadvise?");
    afAdvisee[(int) ulConnection] = 0;
    aAdvisePtrs[(int) ulConnection]->Release();
    return NOERROR;
}


/*
 *  FRM::FRM
 *
 *  Purpose:
 *      Initialize or new form object
 *
 */
FRM::FRM(REFCLSID clsid)
{
    LONG i;

    TraceTag(tagFormFunc,"FRM::FRM .................");

    cRef = 1;
    this->clsid = clsid;

    pMessage = NULL;
    pMessageSite = NULL;
    pSession = NULL;

    pFormMgr = NULL;
    pFormInfo = NULL;

    fDirty = FALSE;

    for (i=0; i<MAX_ADVISE; i++)
        {
            aAdvisePtrs[i] = NULL;
            afAdvisee[i] = 0;
        }

    turn = 0;
}

/*
 *  FRM::~FRM
 *
 *  Purpose:
 *      Destroy our form object
 */
FRM::~FRM(void)
{
    TraceTag(tagFormFunc,"FRM::~FRM Bye now ...");
    AssertSz(0==cRef,"quit referring to this form please");
    AssertSz(NULL == pMessage,"still refing the message");
    AssertSz(NULL == pMessageSite,"still refing the messagesite");
    AssertSz(NULL == pSession,"still refing the session");
}

/*
 *  S a m p l e   F o r m   C l a s s   F a c t o r y
 *
 *  Because we are an exe server, we must implement a class factory
 *  so that other viewers (like Exchange) can learn of our clsid
 *
 */

/*
 *  FRMFAC::CreateInstance
 *
 *  Purpose:
 *      Creates a new form object of the IPM.Form class.
 *
 *  Arguments:
 *      LPUNKNOWN       Outer object to aggregate with (not supported).
 *      REFIID          Desired interface on new form object.
 *      LPVOID FAR *    Where to put new form object.
 *
 *  Returns:
 *      HRESULT         S_OK, or one of the following errors:
 *                      CLASS_E_NOAGGREGATION, E_OUTOFMEMORY,
 *                      E_NOINTERFACE, E_INVALIDARG.
 */
STDMETHODIMP
FRMFAC::CreateInstance(LPUNKNOWN punkOuter, REFIID riid, LPVOID FAR * ppvObject)
{
    FRM *   pfrm = NULL;
    HRESULT hr;

    TraceTag(tagFormFunc,"FRMFAC::CreateInstance");

    // ----- Initialize out parameter and check validity of parameters
    if (!ppvObject)
        {
        hr = ResultFromScode(E_INVALIDARG);
        goto Cleanup;
        }
    *ppvObject = NULL;

    if (punkOuter)
        {
        hr = ResultFromScode(CLASS_E_NOAGGREGATION);
        goto Cleanup;
        }

    // ----- Instantiate new form
    if (!(pfrm = new FRM(clsid)))
        {
        hr = ResultFromScode(E_OUTOFMEMORY);
        TraceTag(tagForm,"E_OUTOFMEMORY 0x%08lx",hr);
        goto Cleanup;
        }

    // ----- Get the desired interface
    hr = pfrm->QueryInterface(riid, ppvObject);
    AssertSz(0==hr,"QueryInterface failed");

Cleanup:
    ReleaseObj(pfrm);
    TraceTag(tagForm,"return 0x%08lx initial reference %d",hr,cRef);
    return hr;
}

/*
 *  FRMFAC::QueryInterface
 *
 *  Purpose:
 *      Returns a pointer to the specified interface.
 *
 *  Arguments:
 *      REFIID          Interface we want.
 *      LPUNKNOWN *     Interface we return.
 *
 *  Returns:
 *      HRESULT         Error status.
 */
STDMETHODIMP
FRMFAC::QueryInterface(REFIID riid, LPVOID FAR * ppvObj)
{
    TraceTag(tagFuncTriv,"FRMFAC::QueryInterface %s",DumpCLSID(riid));
    if (IsEqualIID(riid, IID_IUnknown) || 
        IsEqualIID(riid, IID_IClassFactory))
        {
        *ppvObj = this;
        AddRef();
        TraceTag(tagForm,"return ok");
        return NOERROR;
        }

    *ppvObj = NULL;
    TraceTag(tagForm,"return no interface");
    return ResultFromScode(E_NOINTERFACE);
}

/*
 *  FRMFAC::LockServer
 *
 *  Purpose:
 *      
 *
 *  Arguments:
 *      BOOL            Whether to increment or decrement DLL reference count.
 *
 *  Returns:
 *      HRESULT         S_OK always.
 */
STDMETHODIMP
FRMFAC::LockServer(BOOL fLock)
{
    TraceTag(tagFormFunc,"LockServer (not implemented)");
    return NOERROR;
}

/*
 *  FRMFAC::AddRef
 *
 *  Purpose:
 *      Increments reference count on the form class factory.
 *
 *  Arguments:
 *
 *  Returns:
 *      ULONG           New value of reference count.
 */
STDMETHODIMP_(ULONG)
FRMFAC::AddRef(void)
{
    TraceTag(tagFuncTriv,"FRMFAC::AddRef ret %d",cRef+1);
    return ++cRef;
}


/*
 *  FRMFAC::Release
 *
 *  Purpose:
 *      Decrements reference count on the form class factory.
 *      If count is decremented to zero, the object is freed.
 *
 *  Arguments:
 *
 *  Returns:
 *      ULONG           New value of reference count.
 */
STDMETHODIMP_(ULONG)
FRMFAC::Release(void)
{
    TraceTag(tagFuncTriv,"FRMFAC::Release cRef %d",cRef);
    if (!(--cRef))
        {
        TraceTag(tagForm,"return 0");
        delete this;
        return 0;
        }
    return cRef;
}


FRMFMR::FRMFMR()
{
    TraceTag(tagFuncTriv,"FRMFMR::FRMFMR");
    clsid = CLSID_MyFormsClsId;
}

FRMFAC::FRMFAC()
{
    TraceTag(tagFuncTriv,"FRMFAC::FRMFAC");
    cRef = 1;
}

FRMFAC::~FRMFAC(void)
{
    TraceTag(tagFuncTriv,"FRMFAC::~FRMFAC");
    AssertSz(!cRef,"0817236");
}
