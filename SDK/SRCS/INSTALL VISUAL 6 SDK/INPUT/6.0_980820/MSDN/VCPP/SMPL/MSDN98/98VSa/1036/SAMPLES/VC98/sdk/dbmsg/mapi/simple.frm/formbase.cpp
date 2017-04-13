//////////////////////////////////////////////////////////////////////////////
//
//  FILE:           FORMBASE.CPP
//
//  
//
//  Copyright (c) 1986-1996, Microsoft Corporation.
//  All rights reserved.
//
//--

#include        "precomp.h"
#include        <cindex.h>

static BOOL     g_FModalUp = FALSE;
static BOOL     g_FMBoxUp = FALSE;
static HWND     g_hwndUp = NULL;


BOOL CALLBACK FormDlgProcSend(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK FormDlgProcRead(HWND, UINT, WPARAM, LPARAM);

SizedSPropTagArray(cpropMsg, tagaRead) = MESSAGE_TAGS;

//szRE_PREFIX and szFW_PREFIX have to have the same length
char szRE_PREFIX[] = "RE: ";
char szFW_PREFIX[] = "FW: ";


#define EXCLUDED_PROPS_ON_REPLY     32
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

        PR_BODY,
        PR_SUBJECT,
        PR_SUBJECT_PREFIX,
        PR_MESSAGE_ATTACHMENTS  

    } 
};


////    CBaseForm::CBaseForm
//

CBaseForm::CBaseForm(CClassFactory * pClassFactory) 
                : m_lsterr(g_szFormName)
{
    m_pClassFactory = pClassFactory;
    m_pClassFactory->AddRef();

    m_ulViewStatus = 0;
    m_ulSiteStatus = 0;
    m_cRef = 1;

    m_pviewctxOverride = NULL;
    m_pviewctx = NULL;
    m_pmsgsite = NULL;
    m_pmsg = NULL;

    m_hwnd = NULL;
    m_hwndDialog = NULL;
    
    m_pses = NULL;
    m_pab = NULL;
    m_pval = NULL;

        
    m_padrlist = NULL;
    m_fRecipientsDirty = FALSE;
    
    m_fDirty = FALSE;

    m_fSameAsLoaded = FALSE;

    //
    //  Add self to the head of the linked list of forms
    //

    m_pfrmNext = g_PfrmFirst;
    g_PfrmFirst = this;

    m_cbConvIdx = 0;
    m_lpbConvIdx = NULL;
    m_fConvTopicSet = FALSE;

    m_hChsFldDll = NULL;
    m_lpfnHrPickFolder = NULL;
    m_cbCFDState = 0;
    m_pbCFDState = NULL;


    m_state = stateUninit;
}


////    CBaseForm::~CBaseForm
//
CBaseForm::~CBaseForm()
{
    CBaseForm *         pfrm;
    //
    //  Remove ourselves from the form link list
    //

    if (g_PfrmFirst == this)
    {
        g_PfrmFirst = m_pfrmNext;
    }
    else
    {
        for (pfrm = g_PfrmFirst; pfrm != NULL; pfrm = pfrm->GetNext())
        {
            if (pfrm->m_pfrmNext == this)
            {
                pfrm->m_pfrmNext = m_pfrmNext;
                break;
            }
        }
        Assert(pfrm != NULL);
    }

    MAPIFreeBuffer(m_pval);

    FreePadrlist(m_padrlist);

    MAPIFreeBuffer(m_lpbConvIdx);

    if(m_hChsFldDll)
        FreeLibrary(m_hChsFldDll);

    MAPIFreeBuffer(m_pbCFDState);
    
    //
    //  Let the class factory know we are gone
    //

    UlRelease(m_pClassFactory);
    
}


////    CBaseForm::DeInitObjects
//

void CBaseForm::DeInitObjects()
{
    if (m_hwnd != NULL)
    {
        DestroyWindow(m_hwnd);            // Destroy the frame window
    }

    Assert(m_pmsg == NULL);
    Assert(m_pmsgsite == NULL);
    Assert(m_pviewctx == NULL);
    Assert(m_pviewctxOverride == NULL);
    Assert(m_pab == NULL);
    Assert(m_pses == NULL);

    m_state = stateDead;
}

///////////////////////////////////////////////////////////////////////////////
//
//  IUnknown interface
//
///////////////////////////////////////////////////////////////////////////////

////    CBaseForm::QueryInterface
//
//
//  DESCRIPTION:    The form supports IMAPIform,
//                  IPersistMessage and IAMPIFormAdviseSink

STDMETHODIMP CBaseForm::QueryInterface(REFIID riid, LPVOID * ppvObj)
{
    if (riid == IID_IUnknown || riid == IID_IMAPIForm)
    {
        *ppvObj = (LPVOID) (IMAPIForm *) this;
    }
    else if (riid == IID_IPersistMessage)
    {
        *ppvObj = (LPVOID) (IPersistMessage *) this;
    }
    else if (riid == IID_IMAPIFormAdviseSink)
    {
        *ppvObj = (LPVOID) (IMAPIFormAdviseSink *) this;
    }
    else
    {
        *ppvObj = NULL;
        return  m_lsterr.HrSetLastError(ResultFromScode(E_NOINTERFACE));
    }

    AddRef();
    return hrSuccess;
}

////    CBaseForm::AddRef
//
//  Description:
//

STDMETHODIMP_(ULONG) CBaseForm::AddRef ()
{
    m_cRef += 1;
    return m_cRef;
}

////    CBaseForm::Release
//

STDMETHODIMP_(ULONG) CBaseForm::Release ()
{
    ULONG cRef = -- m_cRef;

    if (cRef == 0)
    {
        // Let the class factory now we are gone
        m_pClassFactory->ObjDestroyedCallback();
        delete this;
    }

    return cRef;
}


///////////////////////////////////////////////////////////////////////////////
//
//  IMAPIForm interface
//
///////////////////////////////////////////////////////////////////////////////


////    IMAPIForm::SetViewContext
//
//

STDMETHODIMP CBaseForm::SetViewContext(IN IMAPIViewContext * pvc)
{
   
    //
    //  If we currently have a view context, then release it
    //

    if (m_pviewctx != NULL)
    {
        m_pviewctx->SetAdviseSink(NULL);
        m_pviewctx->Release();
    }

    //
    // Accept the new view context.
    //

    m_pviewctx = pvc;

    //
    //  If the new view context is non-null, then save it away, setup
    //  the advise sink back to check for things and get the current set
    //  of status flags
    //

    m_ulViewStatus = 0;
    if (pvc != NULL)
    {
        m_pviewctx->AddRef ();
        m_pviewctx->SetAdviseSink (this);
        m_pviewctx->GetViewStatus(&m_ulViewStatus);
    }
    
    ConfigWinMenu();
    
    return hrSuccess;
}


////    IMAPIForm::GetViewContext
//

STDMETHODIMP CBaseForm::GetViewContext(OUT IMAPIViewContext * FAR * ppvc)
{
    Assert(ppvc);

    *ppvc = m_pviewctx;
    
    if(m_pviewctx != NULL)
    {
        m_pviewctx->AddRef();
        return hrSuccess;
    }
    else
        return ResultFromScode(S_FALSE);
}


////    IMAPIForm::ShutdownForm
//
//  Description:
//      This routine is called to shut down the form and if necessary
//      to cause save changes to the form.
//

STDMETHODIMP CBaseForm::ShutdownForm(DWORD dwSaveOptions)
{
  HRESULT             hr;
    
    //
    //  Check for valid state to make the call
    //

    switch( m_state )
    {
        default:
        case stateDead:
            m_viewnotify.OnShutdown ();
            return m_lsterr.HrSetLastError(ResultFromScode(E_UNEXPECTED));

        case stateUninit:
        case stateNormal:
        case stateNoScribble:
        case stateHandsOffFromSave:
        case stateHandsOffFromNormal:
            break;
    }
 
 
    hr = HrQuerySave(dwSaveOptions);
    if(HR_FAILED(hr))
        return hr;
    //
    //  Save us from ourselfs by add-refing the object
    //

    AddRef();

    //
    //  Release the view context
    //

    if (m_pviewctx != NULL)
    {
        m_pviewctx->SetAdviseSink(NULL);
        m_pviewctx->Release();
        m_pviewctx = NULL;
    }

    //
    //  We need to notify anyone who has an advise on us that we are
    //  shutting down.  We want to do this in such a manner as to
    //  protect ourselves since we are referencing the data structure
    //  internally.  Thus the AddRef/Release pair.
    //

    m_viewnotify.OnShutdown ();

    //
    //  Release message objects if we have them
    //

    if(g_FModalUp)  
        m_pviewctxOverride = NULL;

    UlRelease(m_pmsg);
    m_pmsg = NULL;
    
    UlRelease(m_pmsgsite);
    m_pmsgsite = NULL;

    UlRelease(m_pab);
    m_pab = NULL;

    UlRelease(m_pses);
    m_pses = NULL;


    //
    //  Tell all objects to be closed and de-initialized, only IUnknown
    //          calls are legal after this.
    //

    DeInitObjects();

    //
    //  We are now all done -- release our internal reference
    //

    Release();

    return hrSuccess;
}
                   

////    IMAPIForm::DoVerb
//

STDMETHODIMP CBaseForm::DoVerb(LONG iVerb, LPMAPIVIEWCONTEXT pviewctx,
                               ULONG hwndParent, LPCRECT lprcPosRect)
{
    HRESULT             hr;

    //
    //  If a view context was passed in, then we need to get the
    //  status bits from this view context.  Also we are going to save
    //  the current view context and use this view context for the
    //  duration of the verb execution.
    //

    if (pviewctx != NULL)
    {
        m_pviewctxOverride = pviewctx;
        pviewctx->GetViewStatus(&m_ulViewStatus);
    }

    //
    //   Execute the requested verb.  If we do not understand the verb
    //  or we do not support the verb then we return NO SUPPORT and let
    //  the viewer deal with this.
    //

    switch (iVerb)
    {
    
    case EXCHIVERB_OPEN:
        hr = HrOpenForm((HWND) hwndParent, lprcPosRect, m_ulViewStatus);
        break;

    case EXCHIVERB_REPLYTOSENDER:
        hr = HrReply(eREPLY, (HWND) hwndParent, lprcPosRect);
        if(HR_SUCCEEDED(hr))
        {
            m_pviewctxOverride = NULL;
            ShutdownForm(SAVEOPTS_NOSAVE);
        }
        break;

    case EXCHIVERB_FORWARD:
        hr = HrReply(eFORWARD, (HWND) hwndParent, lprcPosRect);
        if(HR_SUCCEEDED(hr))
        {
            m_pviewctxOverride = NULL;
            ShutdownForm(SAVEOPTS_NOSAVE);
        }
        break;
    
    case EXCHIVERB_PRINT:
    case EXCHIVERB_REPLYTOALL:
    case EXCHIVERB_SAVEAS:
    case EXCHIVERB_REPLYTOFOLDER:
        //the viewer should not call us here 
        //(see Value in extensions section of smpfrm.cfg)
        Assert(FALSE);

    default:
        hr = m_lsterr.HrSetLastError(ResultFromScode(MAPI_E_NO_SUPPORT));
        break;
    }

    //
    //  If we moved to a different view context, then switch back to
    //  the one we started with.
    //

    m_pviewctxOverride = NULL;
    
    if(m_pviewctx != NULL)
    {
        m_ulViewStatus =0;
        m_pviewctx->GetViewStatus(&m_ulViewStatus);
        ConfigWinMenu();
    }
    
    return hr;
}


////    IMAPIForm::Advise
//

STDMETHODIMP CBaseForm::Advise (IN IMAPIViewAdviseSink * pViewAdvise,
                                OUT ULONG FAR * pulConnection)
{
    HRESULT     hr;

    hr = m_viewnotify.Advise (pViewAdvise, pulConnection);
    if (FAILED(hr))
    {
        hr = m_lsterr.HrSetLastError(hr);
    }
    return hr;
}


////    IMAPIForm::Unadvise
//

STDMETHODIMP CBaseForm::Unadvise(ULONG ulConnection)
{
    HRESULT     hr;
    
    hr = m_viewnotify.Unadvise(ulConnection);
    if (FAILED(hr))
    {
        hr = m_lsterr.HrSetLastError(hr);
    }

    return hr;
}


///////////////////////////////////////////////////////////////////////////////
//
//  IPersistMessage interface
//
///////////////////////////////////////////////////////////////////////////////

////    IPersistMessage::GetClassID

STDMETHODIMP CBaseForm::GetClassID(LPCLSID lpClassID)
{
    *lpClassID = CLSID_IPM_NOTE_SAMPLE;
    return hrSuccess;
}


////  IPersistMessage::GetLastError
//
//  Description:  This routine is used to get back a string giving more
//              information about the last error in the form. 
//

STDMETHODIMP CBaseForm::GetLastError(HRESULT hr, ULONG ulFlags,
                                     LPMAPIERROR FAR * lppMAPIError)
{
    return m_lsterr.HrGetLastError(hr, ulFlags, lppMAPIError);
}


////    IPersistMessage::IsDirty
//

STDMETHODIMP CBaseForm::IsDirty ()
{

    if(m_fDirty)
        return ResultFromScode(S_OK);

    if(NULL == m_hwndDialog)
    {
        m_fDirty = FALSE;
    }
    else if(m_eFormType == eformRead)
    {
        m_fDirty = (m_fRecipientsDirty ||
                    Edit_GetModify(GetDlgItem(m_hwndDialog, ID_BODY)));
    }
    else
    {
        m_fDirty = (m_fRecipientsDirty ||
                    Edit_GetModify(GetDlgItem(m_hwndDialog, ID_BODY)) ||
                    Edit_GetModify(GetDlgItem(m_hwndDialog, ID_SUBJECT)) ||
                    Edit_GetModify(GetDlgItem(m_hwndDialog, ID_TO)) ||
                    Edit_GetModify(GetDlgItem(m_hwndDialog, ID_CC)));
    }

    return ResultFromScode ((m_fDirty ? S_OK : S_FALSE));
}


////  IPersistMessage::InitNew
//
//  Description: This function is called in the case of composing a new
//      message.  There is a small set of properties which are set by
//      the constructor of the message, however in general it can be
//      assumed the message is clean.
//

STDMETHODIMP CBaseForm::InitNew(LPMAPIMESSAGESITE pmsgsite, LPMESSAGE pmsg)
{
    //
    //  Ensure we are in a state where we can accept this call
    //

    switch(m_state)
    {
    case stateUninit:
    case stateHandsOffFromSave:
    case stateHandsOffFromNormal:
        break;

    default:
        return m_lsterr.HrSetLastError(ResultFromScode(E_UNEXPECTED));
    }

    //
    //  If we currently have a message site, then release it as we
    //  will no longer be using it.
    //
        
    UlRelease(m_pmsgsite);
    m_pmsgsite = NULL;
    
    //
    //  Save away the pointers to the message and message site
    //

    m_pmsgsite = pmsgsite;
    pmsgsite->AddRef();

    m_ulSiteStatus = 0;
    m_pmsgsite->GetSiteStatus(&m_ulSiteStatus);

    m_pmsg = pmsg;
    pmsg->AddRef();

    //
    //  Make an assumption on the message flags and status
    //

    m_ulMsgStatus = 0;
    m_ulMsgFlags = MSGFLAG_UNSENT;
    
    if(m_hwnd)
        DisplayMessage();

    //
    //  We succeeded in doing the InitNew so move to the normal state
    //

    m_state = stateNormal;

    //
    //  Tell everybody who cares that we just loaded a new message
    //

    m_viewnotify.OnNewMessage();
    return hrSuccess;

}

//// IPersistMessage::Load
//
//  Description:  This routine is called as part of loading an existing
//      message into the form.
//

STDMETHODIMP CBaseForm::Load(LPMAPIMESSAGESITE pmsgsite, LPMESSAGE pmsg,
                             ULONG ulMsgStatus, ULONG ulMsgFlags)
{
    //
    //  Ensure we are in a state where we can accept this call
    //

    switch(m_state)
    {
    case stateUninit:
    case stateHandsOffFromSave:
    case stateHandsOffFromNormal:
        break;

    default:
        return m_lsterr.HrSetLastError(ResultFromScode(E_UNEXPECTED));
    }

    //
    //  If we currently have a message site, then release it as we
    //  will no longer be using it.
    //
        
    UlRelease(m_pmsgsite);
    m_pmsgsite = NULL;

    UlRelease(m_pmsg);
    m_pmsg = NULL;
    

    HRESULT hr = HrGetMsgDataFromMsg(pmsg, ulMsgFlags);
    if(HR_FAILED(hr))
        goto err;

    //
    //  Save away the message and message site which are passed in.
    //

    m_pmsg = pmsg;
    pmsg->AddRef();

    m_pmsgsite = pmsgsite;
    pmsgsite->AddRef();

    //
    //  Get the site status flags for disabling buttons & menus
    //
    m_ulSiteStatus = 0;
    m_pmsgsite->GetSiteStatus(&m_ulSiteStatus);

    //
    //  Save away these properties
    //

    m_ulMsgStatus = ulMsgStatus;
    m_ulMsgFlags = ulMsgFlags;

    //
    //  Put us into the normal state
    //

    m_state = stateNormal;

    
    //
    //  if our form is up, display the message
    //
    if(m_hwnd)
        DisplayMessage();
    
    //
    //  Tell everybody who cares that we just loaded a new message
    //

    m_viewnotify.OnNewMessage();
    return hrSuccess;

err:
    return hr;
}

////    IPersistMessage::Save
//
//  Description:  
//      This function will be called whenever a save operation of the
//      information into the form should be done.  We should only make 
//      modifications to the message in this function.
//

STDMETHODIMP CBaseForm::Save(IN LPMESSAGE pmsg, IN ULONG fSameAsLoad)
{
    HRESULT             hr;
    
    //
    //  Check that we are in a state where we are willing to accept
    //  this call.  Must have a message.
    //

    switch( m_state )
    {
    default:
        Assert(FALSE);
    case stateDead:
    case stateUninit:
    case stateNoScribble:
    case stateHandsOffFromSave:
    case stateHandsOffFromNormal:
        return m_lsterr.HrSetLastError(ResultFromScode(E_UNEXPECTED));

    case stateNormal:
        break;
    }
    
    if (fSameAsLoad)
    {
        //
        //  Its the same message interface as was loaded into us.  We can
        //      assume that the pmsg passed in is either NULL or an interface
        //      on the same object as the message we already have loaded
        //

        hr = HrSaveInto(m_pmsg);
    }
    else
    {
        //
        //  We need to copy everything into the new message as we are going
        //      to clone ourselves into it.
        //

        hr = m_pmsg->CopyTo(0, NULL, NULL, 0, NULL, &IID_IMessage, pmsg, 0, NULL);
        if (FAILED(hr))
        {
            m_lsterr.HrSetLastError(hr, m_pmsg);
            return hr;
        }
                            
        //
        //  Now make all of the incremental changes
        //

        hr = HrSaveInto(pmsg);
    }
    
    if (FAILED(hr))
    {
        return hr;
    }
    
    m_state = stateNoScribble;
    m_fSameAsLoaded = fSameAsLoad;
    
    return S_OK;
}


////    IPersistMessage::SaveCompleted
//
//


STDMETHODIMP CBaseForm::SaveCompleted(IN LPMESSAGE pmsg)
{

    switch( m_state )
    {
    case stateHandsOffFromNormal:
    case stateHandsOffFromSave:
    case stateNoScribble:
        break;

    default:
        return m_lsterr.HrSetLastError(ResultFromScode(E_UNEXPECTED));
    }

    if((stateHandsOffFromNormal == m_state || 
        stateHandsOffFromSave == m_state)  && NULL == pmsg)
    {
        DebugTrace("smpfrm: SaveCompleted called in handsOff state with pmsg==NULL\r\n");
        return  m_lsterr.HrSetLastError(ResultFromScode(E_INVALIDARG));
    }
    
    ULONG ulOldState = m_state;
    m_state = stateNormal;                        
       
    //state == NoScribble , pmsg == NULL
    if(NULL == pmsg)
    {
        if(m_fSameAsLoaded)
        {
            ClearDirty();
            m_viewnotify.OnSaved();
        }

        return hrSuccess;
    }
    

    //state == handsOffFromNormal, pmsg != NULL
    if(stateHandsOffFromNormal == ulOldState)
    {
        UlRelease(m_pmsg);
    
        m_pmsg = pmsg;
        pmsg->AddRef();

        return hrSuccess;
    }    

    //state == handsOffFromSave || NoScribble, pmsg != NULL
    if(stateNoScribble == ulOldState)
    {
        UlRelease(m_pmsg);
        m_pmsg = pmsg;
        pmsg->AddRef();
    }
    
    m_viewnotify.OnSaved();
    ClearDirty();
   
   return hrSuccess;
}


////  IPersistMessage::HandsOffMessage
//
//  Description: store, folder and message objects has to be released
//              in this method.
// 
//

STDMETHODIMP CBaseForm::HandsOffMessage ()
{
    
    switch( m_state )
    {
    case stateNormal:
    case stateNoScribble:
        break;

    default:
        return m_lsterr.HrSetLastError(ResultFromScode(E_UNEXPECTED));
    }

    if(stateNormal == m_state)
        m_state = stateHandsOffFromNormal;
    else
        m_state = stateHandsOffFromSave;

    //
    //  We must have a message
    //

    Assert(m_pmsg != NULL);
    m_pmsg->Release();
    m_pmsg = NULL;


    return hrSuccess;
}


///////////////////////////////////////////////////////////////////////////////
//
//  IMAPIFormAdviseSink interfaces
//
///////////////////////////////////////////////////////////////////////////////



////    IMAPIFormAdviseSink::OnChange
//
//  Description: called to notify about changes in viewctx status 

STDMETHODIMP CBaseForm::OnChange(ULONG ulflag)
{
    if(m_pviewctxOverride == NULL) 
    {
        m_ulViewStatus = ulflag;
        ConfigWinMenu();
    }

    return hrSuccess;
}

////    CBaseForm::OnActivateNext
//
//  Description:  We only say that we will handle the next message if
//              it is the exact same message class as the current message.
//              If the next message has the same "unsentness" will reuse the 
//              current object, otherwise ask our ClassFactory for a new one.
//

STDMETHODIMP CBaseForm::OnActivateNext(LPCSTR lpszMessageClass, ULONG ulMessageStatus,
                                        ULONG ulMessageFlags,
                                       LPPERSISTMESSAGE FAR * ppPersistMessage)
{
    HRESULT hr;

    *ppPersistMessage = NULL;

    Assert(m_pval);
    
    
    if(PR_MESSAGE_CLASS == m_pval[irtClass].ulPropTag)
    {
        //the message class comparison has to be case insensitive
        if((lstrcmpi(m_pval[irtClass].Value.LPSZ, lpszMessageClass) != 0) &&
            lstrcmpi(FormClassName, lpszMessageClass) != 0)
        {
            return ResultFromScode(S_FALSE);
        }
    }
    else
    {
        if(lstrcmpi(FormClassName, lpszMessageClass) != 0)
        {
            return ResultFromScode(S_FALSE);
        }
    }


    if((m_ulMsgFlags & MSGFLAG_UNSENT) == (ulMessageFlags & MSGFLAG_UNSENT))
        //tell the viewer to reuse our object
        return ResultFromScode(S_OK);

    
    //Get a new object from our class factory
    hr = m_pClassFactory->CreateInstance(NULL, IID_IPersistMessage, (LPVOID FAR *)ppPersistMessage);
    if(hr)
        return ResultFromScode (S_FALSE);
    else
        return ResultFromScode(S_OK);
}


///////////////////////////////////////////////////////////////////////////////
//
//  Non-IMAPIinterface functions
//
///////////////////////////////////////////////////////////////////////////////


///     CBaseForm::HrGetMsgDataFromMsg
//
//      fills in m_pval and m_padrlist (for unsent msgs only)
//      with the info from pmsg
HRESULT CBaseForm::HrGetMsgDataFromMsg(LPMESSAGE pmsg, ULONG ulMsgFlags)
{
    Assert(pmsg);

    FreePadrlist(m_padrlist);
    m_padrlist = NULL;


    ULONG   cValues = 0;
    MAPIFreeBuffer(m_pval);
    m_pval = NULL;

    MAPIFreeBuffer(m_lpbConvIdx);
    m_lpbConvIdx = NULL;

    HRESULT hr = pmsg->GetProps((LPSPropTagArray) &tagaRead, 0,
                                    &cValues, &m_pval);
    if (HR_FAILED(hr))
    {
        m_lsterr.HrSetLastError(hr, pmsg);
        goto err;
    }

    if(PROP_TYPE(m_pval[irtBody].ulPropTag) == PT_ERROR  &&
       GetScode(m_pval[irtBody].Value.l) == MAPI_E_NOT_ENOUGH_MEMORY)
    {
        hr = HrStreamInMsgBody(pmsg, m_pval, &m_pval[irtBody].Value.LPSZ, &m_lsterr);
        if(hr)
        {
            goto err;   
        }
        else
        {
            m_pval[irtBody].ulPropTag = PR_BODY;
        }
    }
    
    Assert(cValues ==  cpropMsg);

    if(PR_CONVERSATION_INDEX == m_pval[irtConvIdx].ulPropTag)
    {
        LPSPropValue pval = &m_pval[irtConvIdx];

        m_cbConvIdx = pval->Value.bin.cb;
        if(MAPIAllocateBuffer(m_cbConvIdx, (LPVOID *)&m_lpbConvIdx))
        {
            m_lpbConvIdx = NULL;
            m_cbConvIdx = 0;
        }
        else
        {
            CopyMemory(m_lpbConvIdx, pval->Value.bin.lpb, m_cbConvIdx);
        }
    }
    else
    {
        m_lpbConvIdx = NULL;
        m_cbConvIdx = 0;
    }
    
    m_fConvTopicSet = (PR_CONVERSATION_TOPIC == m_pval[irtConvTopic].ulPropTag);
        
    
    if(ulMsgFlags & MSGFLAG_UNSENT)
    {
        hr = GetMsgAdrlist (pmsg, &m_padrlist, &m_lsterr);
        if(HR_FAILED(hr))
        {
            goto err;
        }
    }

    return hrSuccess;

err:
    MAPIFreeBuffer(m_pval);
    m_pval = NULL;

    FreePadrlist(m_padrlist);
    m_padrlist = NULL;

    return hr;

}

///         CBaseForm::ClearDirty
//
//      Clears dirty state
void CBaseForm::ClearDirty(void)
{
    m_fDirty = FALSE;
    m_fRecipientsDirty = FALSE;

    if(m_eFormType == eformSend)
    {
        Edit_SetModify(GetDlgItem(m_hwndDialog, ID_BODY), FALSE);
        Edit_SetModify(GetDlgItem(m_hwndDialog, ID_SUBJECT), FALSE);
        Edit_SetModify(GetDlgItem(m_hwndDialog, ID_TO), FALSE);
        Edit_SetModify(GetDlgItem(m_hwndDialog, ID_CC), FALSE);
    }
    else
    {
        Edit_SetModify(GetDlgItem(m_hwndDialog, ID_BODY), FALSE);
    }
}

////    CBaseForm::Address
//
//  Description:
//      This function is used to address the form.
//      The parameter determines which button in the address
//      dialog has the focus.
//

void CBaseForm::Address(int id)
{
    Assert( ID_TO_BUTTON == id || ID_CC_BUTTON == id);

    HRESULT hr;

    if (m_pses == NULL)
    {
        hr = m_pmsgsite->GetSession(&m_pses);
        if(hr)
        {
            m_lsterr.HrSetLastError(hr, m_pmsgsite);
            ShowError();
            return;
        }
    }
    
    Assert(m_pses != NULL);

    if (m_pab == NULL)
    {
        hr = m_pses->OpenAddressBook((ULONG) m_hwnd, NULL, 0, &m_pab);
        if(hr)
        {
            m_lsterr.HrSetLastError(hr, m_pses);
            ShowError();
        }
        if(HR_FAILED(hr)) //if it's a real error (not a warning)
            return; 
    }
    
    Assert(m_pab != NULL);

    
    ADRPARM adrparm = { 0, NULL, AB_RESOLVE | DIALOG_MODAL, NULL, 0L,
                        NULL, NULL, NULL, NULL, "Address Book", NULL,
                        "Send Note To", 2, (id == ID_TO_BUTTON ? 0:1),
                        NULL, NULL, NULL, NULL };
    ULONG   ulHwndAddr = (ULONG) m_hwnd;
    
    hr = m_pab->Address(&ulHwndAddr, &adrparm, &m_padrlist);
    if (!hr)
    {
        m_fRecipientsDirty = TRUE;
        UpdateRecipientsDisplay();
    }
    else if(GetScode(hr) != MAPI_E_USER_CANCEL)
    {
        m_lsterr.HrSetLastError(hr, m_pab);
        ShowError();
    }
        
}

////    CBaseForm::ClearWindow
//
//  Description:
//      This routine is called when the window for this form object is
//      destroyed.  We clear out pointer to the window and the windows
//      pointer to us.
//

void CBaseForm::ClearWindow()
{
    Assert(m_hwnd != NULL);

    //
    //  Clear the back pointer to us and remove the reference count for it.
    //

    SetWindowLong(m_hwnd, 0, 0);
    Release();

    //
    //  Clear out pointer to the window since it is now dead
    //

    m_hwnd = NULL;
    m_hwndDialog = NULL;
}

////  CBaseForm::HrOpenForm
//
//  Description:  This is the internal routine which is called from the
//      open/display verb.  It will cause UI to appear if there is none
//      and force the window to the foreground if there is already UI.
//

HRESULT CBaseForm::HrOpenForm(HWND hwndParent, LPCRECT lprcPosRect,
                              ULONG ulViewFlags)
{

    if (lprcPosRect == NULL)
        return m_lsterr.HrSetLastError(ResultFromScode(E_INVALIDARG));

    //
    //  If any modal forms are visible then do not do anything 
    //

    Assert( g_FModalUp && g_hwndUp || !g_FModalUp && !g_hwndUp);
    if (g_FMBoxUp || (g_FModalUp && hwndParent != g_hwndUp))
        return m_lsterr.HrSetLastError(
                               ResultFromScode(OLEOBJ_S_CANNOT_DOVERB_NOW));
    
    if (!(ulViewFlags & VCSTATUS_MODAL))
    {
        //  If we are not modal then don't do anything relative to the parent
        hwndParent = NULL;
    }

    //
    //  Check to see if we have a window up
    //

    if (m_hwnd != 0)
    {
        MoveWindow(m_hwnd, lprcPosRect->left, lprcPosRect->top,
                   lprcPosRect->right - lprcPosRect->left,
                   lprcPosRect->bottom - lprcPosRect->top,
                   TRUE);
        SetForegroundWindow(m_hwnd);
        
        return S_OK;
    }
           
    m_hwnd = CreateWindow((m_ulMsgFlags & MSGFLAG_UNSENT) ?
                          g_szSendWinClass : g_szReadWinClass,
                          g_szWindowCaption, WS_OVERLAPPEDWINDOW,
                          0, 0, 10, 10, hwndParent, NULL, g_hinst, NULL);

    if (m_hwnd == NULL)
    {
        return m_lsterr.HrSetLastError(ResultFromScode(E_OUTOFMEMORY));
    }

    //
    //  Put the pointer to this object into the window
    //

    SetWindowLong(m_hwnd, 0, (long) (void FAR *) this);
    //we just created another pointer to ourself, so addref
    AddRef();

    //
    //  Create the dialog as a child of this window
    //

    if (m_ulMsgFlags & MSGFLAG_UNSENT)
    {
        m_eFormType = eformSend;
        m_hwndDialog = CreateDialog(g_hinst, MAKEINTRESOURCE(IDR_SEND_FORM),
                                    m_hwnd, &FormDlgProcSend);
        m_HAccelTable = LoadAccelerators(g_hinst, MAKEINTRESOURCE(IDR_SEND_FORM));
    }
    else
    {
        m_eFormType = eformRead;
        m_hwndDialog = CreateDialog(g_hinst, MAKEINTRESOURCE(IDR_READ_FORM),
                                    m_hwnd, &FormDlgProcRead);
        m_HAccelTable = LoadAccelerators(g_hinst, MAKEINTRESOURCE(IDR_READ_FORM));
    }
        

    DisplayMessage();

    //
    //  Position the window where it is suppose to be
    //
                                   
    MoveWindow(m_hwnd, lprcPosRect->left, lprcPosRect->top,
        lprcPosRect->right - lprcPosRect->left,
        lprcPosRect->bottom - lprcPosRect->top,
        TRUE);

    ShowWindow(m_hwnd, SW_SHOW);

    SetForegroundWindow(m_hwnd);
                 
    //
    //  If we are modal, then we loop until the form is closed
    //

    if (ulViewFlags & VCSTATUS_MODAL)
    {
        MSG         msg;

        BOOL fOldModalUp = g_FModalUp;
        HWND hwndOldUp = g_hwndUp;

        g_FModalUp = TRUE;
        g_hwndUp = m_hwnd;

        while ((m_hwnd != NULL) && (GetMessage(&msg, m_hwnd, 0, 0)))
        {
            //first call our method and see if this message makes sense to us.
            //if not, let WIN API care about it.
            if (!TranslateMessage(msg))
            {
                ::TranslateMessage(&msg);
                ::DispatchMessage(&msg);
            }
        }

        g_FModalUp = fOldModalUp;
        g_hwndUp = hwndOldUp;
    }

    return hrSuccess;
}

////    CBaseForm::HrSaveInto
//
//  Description:
//    This routine gives one central location which save all modified
//      properties into a message.
//

HRESULT CBaseForm::HrSaveInto(LPMESSAGE pmsg)
{
    ULONG               cval = 0;
    HRESULT             hr;                                    

    //
    //  First, write out the recipient table
    //
    
    if(m_padrlist && m_fRecipientsDirty)
    {
        hr = pmsg->ModifyRecipients(0, m_padrlist);
        if (FAILED(hr))
        {
            m_lsterr.HrSetLastError(hr, pmsg);
            return hr;
        }
    }
    //
    //  Next set up and save the rest of the info
    //
      
    HrGetMsgDataFromUI(m_hwndDialog);

    //PR_DISPLAY_TO AND PR_DISPLAY_CC can't be set
    ULONG ulToTag = m_pval[irtTo].ulPropTag;
    m_pval[irtTo].ulPropTag = PR_NULL;
    
    ULONG ulCcTag = m_pval[irtCc].ulPropTag;
    m_pval[irtCc].ulPropTag = PR_NULL;
    
    ULONG ulNormSubjectTag = m_pval[irtNormSubject].ulPropTag;
    m_pval[irtNormSubject].ulPropTag = PR_NULL;

    m_pval[irtClass].ulPropTag = PR_MESSAGE_CLASS;
    m_pval[irtClass].Value.lpszA = FormClassName;

    /*
     *If the message didn't have PR_CONVERSATION_TOPIC when we loaded it, we'll
     *  set it every time we save the message. Otherwise we don't touch it
     */
    if(!m_fConvTopicSet)
    {   
        m_pval[irtConvTopic].ulPropTag = PR_CONVERSATION_TOPIC;
        if(PR_SUBJECT == m_pval[irtSubject].ulPropTag)
        {
            m_pval[irtConvTopic].Value.LPSZ = m_pval[irtSubject].Value.LPSZ;
        }
        else
        {
            m_pval[irtConvTopic].Value.LPSZ = "";
        }
    }
    else
    {
        m_pval[irtConvTopic].ulPropTag = PR_NULL;
    }

    /*
     * if the message doesn't have a PR_CONVERSATION_INDEX, create and set it
     *
     */
    if(m_cbConvIdx == 0)
    {
        if(!ScAddConversationIndex(0, NULL, &m_cbConvIdx,   &m_lpbConvIdx))
        {
            m_pval[irtConvIdx].ulPropTag = PR_CONVERSATION_INDEX;
            m_pval[irtConvIdx].Value.bin.lpb = m_lpbConvIdx;
            m_pval[irtConvIdx].Value.bin.cb = m_cbConvIdx;
        }
        else
        {
            m_pval[irtConvIdx].ulPropTag = PR_NULL;
        }
    }
    else
    {
        m_pval[irtConvIdx].ulPropTag = PR_NULL;
    }

    LPSPropProblemArray pProblems = NULL;

    hr = pmsg->SetProps(cpropMsg, m_pval, &pProblems);
    if (hr)
    {
        m_lsterr.HrSetLastError(hr, pmsg);
        goto err;
    }
    
    if(pProblems)
    {
        for(UINT ind = 0; ind < pProblems->cProblem; ++ind)
        { 
            if(PR_BODY == pProblems->aProblem[ind].ulPropTag &&
               MAPI_E_NOT_ENOUGH_MEMORY == pProblems->aProblem[ind].scode)
            {
                hr = HrStreamOutMsgBody(pmsg, m_pval[irtBody].Value.LPSZ, &m_lsterr);
                if(hr)
                {
                    MAPIFreeBuffer(pProblems);
                    pProblems = NULL;
                    goto err;
                }
                break;
            }
        }

        MAPIFreeBuffer(pProblems);
        pProblems = NULL;
    }

err:
    m_pval[irtTo].ulPropTag = ulToTag;
    m_pval[irtCc].ulPropTag = ulCcTag;
    m_pval[irtNormSubject].ulPropTag = ulNormSubjectTag;
    
    return hr;
}


BOOL CBaseForm::TranslateMessage(MSG& msg)
{
    //
    //  We translate accelerators before the dialog message so that we
    //  can get our accelerators to override the dialog's.
    //

    if(msg.hwnd == m_hwnd || IsChild(m_hwnd, msg.hwnd))
    {
        if (::TranslateAccelerator(m_hwnd, m_HAccelTable, &msg))
        {
            return TRUE;
        }
    }
    
    if ((m_hwndDialog != NULL) && ::IsDialogMessage(m_hwndDialog, &msg))
    {
        return TRUE;
    }
    
    return FALSE;
}

///  CBaseForm::UpdateRecipientsDisplay
//  go through m_padrlist and display TO and CC recipients in the 
//  edit boxes.
// Called only for send form. The Read form can use PR_DISPLAY_*
void CBaseForm::UpdateRecipientsDisplay(void)
{
    Assert(m_hwndDialog);
    
    Assert(m_eFormType == eformSend);

    HWND hwTo = GetDlgItem(m_hwndDialog, ID_TO);
    HWND hwCC = GetDlgItem(m_hwndDialog, ID_CC);
    
    Edit_SetText(hwTo, "");
    Edit_SetText(hwCC, "");
    
    if(m_padrlist == NULL || m_padrlist->cEntries == 0) return;

    #define ADRTEXTLEN  512
    char szTo [ADRTEXTLEN] = "";
    char szCC [ADRTEXTLEN] = "";
    
    BOOL fToFull = FALSE;
    BOOL fCCFull = FALSE;

    
    LPADRENTRY pae;
    for(pae = m_padrlist->aEntries;
        pae < m_padrlist->aEntries + m_padrlist->cEntries;
        ++pae)
    {
        if( NULL == pae->rgPropVals) continue;

        LPSPropValue lpsprop;
        LPSTR szDisplay = NULL;
        LPSTR szName = NULL;
        BOOL * pfFull = NULL;
        for(lpsprop = pae->rgPropVals;
            lpsprop < pae->rgPropVals + pae->cValues;
            ++lpsprop)
        {
            if(lpsprop->ulPropTag == PR_RECIPIENT_TYPE)
            {
                if(lpsprop->Value.l == MAPI_TO)
                {
                    szDisplay = szTo;
                    pfFull = &fToFull;
                }
                else if(lpsprop->Value.l == MAPI_CC)
                {
                    szDisplay = szCC;
                    pfFull = &fCCFull;
                }
            }
            else if(lpsprop->ulPropTag == PR_DISPLAY_NAME)
            {
                szName = lpsprop->Value.LPSZ;
            }
            
            if(NULL != szName && NULL != szDisplay)
            {
                Assert(pfFull);

                if(*pfFull) break;

                if(lstrlen(szDisplay) + lstrlen(szName) + 7 < ADRTEXTLEN)
                {
                    lstrcat(szDisplay, szName);
                    lstrcat(szDisplay, "; ");
                }
                else
                {
                    lstrcat(szDisplay, "...");
                    *pfFull = TRUE;
                }

                break;
            }
        }
    }

    //get rid of the "; " after the last recipient
    if(lstrlen(szTo) > 0  &&  !fToFull) 
        szTo[lstrlen(szTo)-2] = 0;
    if(lstrlen(szCC) > 0  &&  !fCCFull) 
        szCC[lstrlen(szCC)-2] = 0;

    Edit_SetText(hwTo, szTo);
    Edit_SetText(hwCC, szCC);

}


///  CBaseForm::DisplayMessage
//
//  display the info from m_pval in the dialog
void CBaseForm::DisplayMessage(void)
{
    char    sz[256];

    Assert(m_hwnd);
    Assert(m_hwndDialog);

    if(NULL == m_pval) return;

    if (m_pval[irtSubject].ulPropTag == PR_SUBJECT)
    {
        SetDlgItemText(m_hwndDialog, ID_SUBJECT, m_pval[irtSubject].Value.LPSZ);
        lstrcpyn(sz, m_pval[irtSubject].Value.LPSZ, 200);
        sz[200] = 0;
        lstrcat(sz, " - ");
        lstrcat(sz, g_szWindowCaption);
        SetWindowText(m_hwnd, sz);
    }
    else
    {
        SetWindowText(m_hwnd, g_szWindowCaption);
    }

    if (m_pval[irtBody].ulPropTag == PR_BODY)
        SetDlgItemText(m_hwndDialog, ID_BODY, m_pval[irtBody].Value.LPSZ);

    if(m_eFormType == eformRead)
    {
        if (m_pval[irtFrom].ulPropTag == PR_SENDER_NAME)
        SetDlgItemText(m_hwndDialog, ID_FROM, m_pval[irtFrom].Value.LPSZ);

        if (m_pval[irtTime].ulPropTag == PR_CLIENT_SUBMIT_TIME) {
            FormatTime(&m_pval[irtTime].Value.ft, sz);
            SetDlgItemText(m_hwndDialog, ID_SENT, sz);
        }

        if (m_pval[irtTo].ulPropTag == PR_DISPLAY_TO)
            SetDlgItemText(m_hwndDialog, ID_TO, m_pval[irtTo].Value.LPSZ);

        Edit_SetModify(GetDlgItem(m_hwndDialog, ID_BODY), FALSE);
    }
    else if (m_eFormType == eformSend)
    {
        UpdateRecipientsDisplay();

        Edit_SetModify(GetDlgItem(m_hwndDialog, ID_BODY), FALSE);
        Edit_SetModify(GetDlgItem(m_hwndDialog, ID_SUBJECT), FALSE);
        Edit_SetModify(GetDlgItem(m_hwndDialog, ID_TO), FALSE);
        Edit_SetModify(GetDlgItem(m_hwndDialog, ID_CC), FALSE);
    }
    else
    {
        Assert(FALSE);
    }
  
}


/// CBaseForm::HrGetMsgDataFromUI
//
// save the  message info from the dialog into the m_pval
HRESULT CBaseForm::HrGetMsgDataFromUI(HWND hDlg)
{

    LONG cb = 0;
    HRESULT hr = hrSuccess;


    //have to call IsDirty() to make sure  m_fDirty is current
    if(!m_fDirty)
        IsDirty();
    
    if(m_eFormType == eformRead)
    {
        Assert(m_pval);

        if(!m_fDirty)
            return hrSuccess;

        //everything is read-only except for the body
        cb = GetWindowTextLength(GetDlgItem(hDlg, ID_BODY));
        if(m_pval[irtBody].ulPropTag == PR_BODY &&
         cb <= lstrlen(m_pval[irtBody].Value.LPSZ))
        {
            GetWindowText(GetDlgItem(hDlg, ID_BODY), m_pval[irtBody].Value.LPSZ, cb+1);
        }
        else
        {
            if(hr = MAPIAllocateMore(cb+1, m_pval, (LPVOID FAR *)&m_pval[irtBody].Value.LPSZ))
            {
                return m_lsterr.HrSetLastError(ResultFromScode(E_OUTOFMEMORY));
            }

            GetWindowText(GetDlgItem(hDlg, ID_BODY), m_pval[irtBody].Value.LPSZ, cb+1);
        }

        m_pval[irtBody].ulPropTag = PR_BODY;
    }
    else if (m_eFormType == eformSend)
    {
        if(!m_fDirty && m_pval != NULL) 
            return hrSuccess;

        if(NULL != m_pval)
        {
            MAPIFreeBuffer(m_pval);
            m_pval = NULL;
        }
        if(MAPIAllocateBuffer(sizeof(SPropValue)* cpropMsg, (LPVOID FAR *) &m_pval))
        {
            return m_lsterr.HrSetLastError(ResultFromScode(E_OUTOFMEMORY));
        }
        
        ZeroMemory(m_pval, sizeof(SPropValue)* cpropMsg);
        
        
        m_pval[irtTime].ulPropTag = PR_NULL;
        m_pval[irtFrom].ulPropTag = PR_NULL;                     

        cb = GetWindowTextLength(GetDlgItem(hDlg, ID_SUBJECT)) + 1;
        /*if(cb > 0)
        {*/
            if(MAPIAllocateMore(cb+1, m_pval, (LPVOID FAR *)&m_pval[irtSubject].Value.LPSZ))
            {
                return m_lsterr.HrSetLastError(ResultFromScode(E_OUTOFMEMORY));
            }

            cb = GetWindowText(GetDlgItem(hDlg, ID_SUBJECT), m_pval[irtSubject].Value.LPSZ, cb+1);
            m_pval[irtSubject].ulPropTag = PR_SUBJECT;
        /*}
        else
        { //no subject
    
            m_pval[irtSubject].ulPropTag = PR_NULL;
        } */
    
        cb = GetWindowTextLength(GetDlgItem(hDlg, ID_BODY)) +1 ;
        /*if(cb > 0)
        { */
            if(MAPIAllocateMore(cb+1, m_pval, (LPVOID FAR *)&m_pval[irtBody].Value.LPSZ))
            {
                return m_lsterr.HrSetLastError(ResultFromScode(E_OUTOFMEMORY));
            }

            cb = GetWindowText(GetDlgItem(hDlg, ID_BODY), m_pval[irtBody].Value.LPSZ, cb+1);
            m_pval[irtBody].ulPropTag = PR_BODY;
        /*}
        else
        { //no body
    
            m_pval[irtBody].ulPropTag = PR_NULL;
        } */
    
        cb = GetWindowTextLength(GetDlgItem(hDlg, ID_TO));
        if(cb > 0)
        {
            if(hr = MAPIAllocateMore(cb+1, m_pval, (LPVOID FAR *)&m_pval[irtTo].Value.LPSZ))
            {
                return m_lsterr.HrSetLastError(ResultFromScode(E_OUTOFMEMORY));
            }

            GetWindowText(GetDlgItem(hDlg, ID_TO), m_pval[irtTo].Value.LPSZ, cb+1);
            m_pval[irtTo].ulPropTag = PR_DISPLAY_TO;
        }
        else
        { //no to
    
            m_pval[irtTo].ulPropTag = PR_NULL;
        }
        
        cb = GetWindowTextLength(GetDlgItem(hDlg, ID_CC));
        if(cb > 0)
        {
            if(hr = MAPIAllocateMore(cb+1, m_pval, (LPVOID FAR *)&m_pval[irtCc].Value.LPSZ))
            {
                return m_lsterr.HrSetLastError(ResultFromScode(E_OUTOFMEMORY));
            }

            GetWindowText(GetDlgItem(hDlg, ID_CC), m_pval[irtCc].Value.LPSZ, cb+1);
            m_pval[irtTo].ulPropTag = PR_DISPLAY_CC;
        }
        else
        { //no cc
    
            m_pval[irtCc].ulPropTag = PR_NULL;
        }
    }   
    else
    {
        Assert(FALSE);
    }
    return hr;
}

/// CBaseForm::IsAddressed
//
//Does m_padrlist contain a recipient?
BOOL CBaseForm::IsAddressed(void)
{
    Assert(m_eFormType == eformSend) ;
        
    if(NULL == m_padrlist || m_padrlist->cEntries == 0)
        return FALSE;
    
    for(LPADRENTRY pae = m_padrlist->aEntries;
        pae < m_padrlist->aEntries + m_padrlist->cEntries; ++pae)
    {
        if(pae->rgPropVals)
            return TRUE;
    }

    return FALSE;
}

///     CBaseForm::ConfigMenu
//Enable/disable menu commands based on the values of m_ulSiteStatus
// and m_ulViewStatus
void CBaseForm::ConfigMenu(HMENU hMenu)
{
    if(m_eFormType == eformRead)
    {
        EnableMenuItem(hMenu, IDC_MESSAGE_SAVE,
            MF_BYCOMMAND|((m_ulSiteStatus & VCSTATUS_SAVE)? MF_ENABLED:MF_GRAYED));
        EnableMenuItem(hMenu, IDC_MESSAGE_DELETE,
            MF_BYCOMMAND| (!(m_ulViewStatus & VCSTATUS_READONLY) &&
                            (m_ulSiteStatus & VCSTATUS_DELETE) ? MF_ENABLED:MF_GRAYED));
        EnableMenuItem(hMenu, IDC_MESSAGE_COPY,
            MF_BYCOMMAND| (!(m_ulViewStatus & VCSTATUS_READONLY) &&
                            (m_ulSiteStatus & VCSTATUS_COPY) ? MF_ENABLED:MF_GRAYED));
        EnableMenuItem(hMenu, IDC_MESSAGE_MOVE,
            MF_BYCOMMAND| (!(m_ulViewStatus & VCSTATUS_READONLY) &&
                            (m_ulSiteStatus & VCSTATUS_MOVE) ? MF_ENABLED:MF_GRAYED));
        EnableMenuItem(hMenu, IDC_VIEW_ITEMABOVE,
            MF_BYCOMMAND|(m_ulViewStatus & VCSTATUS_PREV ? MF_ENABLED:MF_GRAYED));
        EnableMenuItem(hMenu, IDC_VIEW_ITEMBELOW,
            MF_BYCOMMAND|(m_ulViewStatus & VCSTATUS_NEXT ? MF_ENABLED:MF_GRAYED));
    }

    else
    {
        EnableMenuItem(hMenu, IDC_MESSAGE_SUBMIT,
            MF_BYCOMMAND|((m_ulSiteStatus &VCSTATUS_SUBMIT) ? MF_ENABLED:MF_GRAYED));
        EnableMenuItem(hMenu, IDC_MESSAGE_SAVE,
            MF_BYCOMMAND|((m_ulSiteStatus & VCSTATUS_SAVE)? MF_ENABLED:MF_GRAYED));
        EnableMenuItem(hMenu, IDC_MESSAGE_DELETE,
            MF_BYCOMMAND| (!(m_ulViewStatus & VCSTATUS_READONLY) &&
                            (m_ulSiteStatus & VCSTATUS_DELETE) ? MF_ENABLED:MF_GRAYED));
        EnableMenuItem(hMenu, IDC_MESSAGE_COPY,
            MF_BYCOMMAND| (!(m_ulViewStatus & VCSTATUS_READONLY) &&
                            (m_ulSiteStatus & VCSTATUS_COPY) ? MF_ENABLED:MF_GRAYED));
        EnableMenuItem(hMenu, IDC_MESSAGE_MOVE,
            MF_BYCOMMAND| (!(m_ulViewStatus & VCSTATUS_READONLY) &&
                            (m_ulSiteStatus & VCSTATUS_MOVE) ? MF_ENABLED:MF_GRAYED));
                            
    }
}
        
///CBaseForm::HrReply
//
//
HRESULT CBaseForm::HrReply(eREPLYTYPE eReplyType, HWND hwndParent, LPCRECT prect)
{
    
    //reply all is not implemented
    Assert(eREPLY == eReplyType || eFORWARD == eReplyType);
    
    HRESULT hr;
    LONG cb;
    
    char * szBody = NULL;
    char * szSubject = NULL;
    SPropValue val[3] = {0};
    
    enum { eName, eAddrType, eEID, eRecipType, eDim};
    SizedSPropTagArray(eDim, sptSender) = 
        {eDim, {PR_SENDER_NAME, PR_SENDER_ADDRTYPE,
                PR_SENDER_ENTRYID, PR_NULL}};

    LPSPropProblemArray pProblems = NULL;
    LPMAPIFORM          pfrmReply = NULL;
    LPPERSISTMESSAGE    ppermsg = NULL;
    LPMAPIMESSAGESITE   pmsgsite = NULL;
    LPMAPIVIEWCONTEXT   pviewctx = NULL;
    LPMESSAGE           pmsg = NULL;
    ULONG cbNewConvIdx = 0;
    LPBYTE lpbNewConvIdx = NULL;
    
    Assert(m_pmsg);
    

    hr = m_pClassFactory->CreateInstance(NULL, IID_IMAPIForm, (LPVOID FAR *) &pfrmReply);
    if(hr)
    {
        m_lsterr.HrSetLastError(ResultFromScode(E_OUTOFMEMORY));
        goto err;
    }
     
    hr = pfrmReply->QueryInterface(IID_IPersistMessage, (LPVOID *) &ppermsg);
    if(hr)
    {
        m_lsterr.HrSetLastError(hr, pfrmReply);
        goto err;
    }
                                    
    hr = m_pmsgsite->NewMessage(FALSE, NULL, ppermsg, &pmsg, &pmsgsite, &pviewctx);
    if(hr)
    {
        m_lsterr.HrSetLastError(hr, m_pmsgsite);
        goto err;
    }
    
    hr = m_pmsg->CopyTo(0, NULL, (LPSPropTagArray)&sptExcludedProps,
                        0, NULL, &IID_IMessage, pmsg, 0, &pProblems);
    if(hr)
    {
        m_lsterr.HrSetLastError(hr, m_pmsg);
        goto err;
    }
    
    if(pProblems)
    {
        DebugTraceProblems("SmplForm: CopyTo returned ...", pProblems);
        //  if any of the errors is other than MAPI_E_COMPUTED, fail
        for(UINT ind = 0; ind < pProblems->cProblem; ++ind)
        { 
            if(MAPI_E_COMPUTED != pProblems->aProblem[ind].scode)
            {
                hr = m_lsterr.HrSetLastError(
                            ResultFromScode(pProblems->aProblem[ind].scode));
                MAPIFreeBuffer(pProblems);
                pProblems = NULL;
                goto err;
                
            }
        }
        MAPIFreeBuffer(pProblems);
        pProblems = NULL;
    }

    if(m_pval && m_pval[irtNormSubject].ulPropTag == PR_NORMALIZED_SUBJECT)
        cb = lstrlen(m_pval[irtNormSubject].Value.LPSZ);
    else
        cb = 0;
    
    if(hr = MAPIAllocateBuffer(cb+lstrlen(szRE_PREFIX)+1, (LPVOID FAR *) &szSubject))
    {
        m_lsterr.HrSetLastError(ResultFromScode(E_OUTOFMEMORY));
        goto err;
    }
    

    *szSubject = '\0';
    
    if(eREPLY == eReplyType)
    {
        lstrcat(szSubject, szRE_PREFIX);
    }
    else
    {
        lstrcat(szSubject, szFW_PREFIX);
    } 

    if(cb > 0)
    {
        lstrcat(szSubject, m_pval[irtNormSubject].Value.LPSZ);
    }

    val[1].Value.lpszA = szSubject;
    val[1].ulPropTag = PR_SUBJECT;
    
    HrSaveToString(&szBody);
    if(szBody)
    {
        val[0].Value.LPSZ = szBody;
        val[0].ulPropTag = PR_BODY;
    }
    else
        val[0].ulPropTag = PR_NULL;

    
    /*
     * Create a conversation index for the reply msg based on that of ours
     *
     */
    if(!ScAddConversationIndex(m_cbConvIdx, m_lpbConvIdx,
                                &cbNewConvIdx, &lpbNewConvIdx))
    {
        val[2].ulPropTag = PR_CONVERSATION_INDEX;
        val[2].Value.bin.cb = cbNewConvIdx;
        val[2].Value.bin.lpb = lpbNewConvIdx;
    }
    else
    {
        val[2].ulPropTag = PR_NULL;
    }

    hr = pmsg->SetProps(3, val, &pProblems);
    MAPIFreeBuffer(lpbNewConvIdx);
    lpbNewConvIdx = NULL;

    MAPIFreeBuffer(szSubject);
    szSubject = NULL;
    
    if(!hr)
    {
        if(pProblems)
        {
            for(UINT ind = 0; ind < pProblems->cProblem; ++ind)
            { 
                if(PR_BODY == pProblems->aProblem[ind].ulPropTag &&
                   MAPI_E_NOT_ENOUGH_MEMORY == pProblems->aProblem[ind].scode)
                {
                    hr = HrStreamOutMsgBody(pmsg, szBody, &m_lsterr);
                    if(hr)
                    {
                        MAPIFreeBuffer(pProblems);
                        pProblems = NULL;
                        goto err;
                    }
                    break;
                }
            }
            MAPIFreeBuffer(pProblems);
            pProblems = NULL;
        }
    }
    else
    {
        m_lsterr.HrSetLastError(hr, m_pmsg);
        goto err;
    }

    // if it's a reply, set the addressee
    if(eREPLY == eReplyType)
    {               
        LPADRLIST pal = NULL;
        ULONG cVal = 0;
        LPSPropValue pval = NULL;

        hr = MAPIAllocateBuffer(CbNewADRLIST(1), (LPVOID FAR *)&pal);
        if(hr)
        {
            m_lsterr.HrSetLastError(ResultFromScode(E_OUTOFMEMORY));
            goto err;
        }
        hr = m_pmsg->GetProps((LPSPropTagArray) &sptSender, 0, &cVal, &pval);
        if(hr) //treat warnings as an error, 'cause the props we ask for are required
        {
            m_lsterr.HrSetLastError(hr, m_pmsg);
            MAPIFreeBuffer(pal);
            goto err;
        }
        
        Assert(cVal == eDim);

        pval[eRecipType].ulPropTag = PR_RECIPIENT_TYPE;
        pval[eRecipType].Value.l = MAPI_TO;

        Assert(pval[eName].ulPropTag == PR_SENDER_NAME);
        pval[eName].ulPropTag = PR_DISPLAY_NAME;

        Assert(pval[eAddrType].ulPropTag == PR_SENDER_ADDRTYPE);
        pval[eAddrType].ulPropTag = PR_ADDRTYPE;

        Assert(pval[eEID].ulPropTag == PR_SENDER_ENTRYID);
        pval[eEID].ulPropTag = PR_ENTRYID;
        
        pal->aEntries[0].rgPropVals = pval;
        
        pal->cEntries = 1;
        pal->aEntries[0].cValues = eDim;
        
        hr = pmsg->ModifyRecipients(0, pal);
        FreePadrlist(pal); //this will also free pval
        pal = NULL;
        pval = NULL;
        if(hr)
        {
            m_lsterr.HrSetLastError(hr, pmsg);
            goto err;
        }
    }

    hr = ppermsg->Load(pmsgsite, pmsg, 0, MSGFLAG_UNSENT );
    if(hr)
    {
        m_lsterr.HrSetLastError(hr, ppermsg);
        goto err;
    }

    hr = pfrmReply->DoVerb(EXCHIVERB_OPEN, pviewctx, (ULONG)hwndParent, prect);
    if(hr)
    {
        m_lsterr.HrSetLastError(hr, pfrmReply);
        pfrmReply->ShutdownForm(SAVEOPTS_NOSAVE);
        goto err;
    }

err:
    
    UlRelease(pfrmReply);
    UlRelease(ppermsg);
    UlRelease(pmsgsite);
    UlRelease(pviewctx);
    UlRelease(pmsg);
    delete [] szBody;
    
    return hr;
}

///     CBaseForm::HrSaveToString
//      
//  The returned string has to be freed using delete
HRESULT CBaseForm::HrSaveToString(LPSTR * pszMessage)
{
    Assert(m_pval);
    Assert(pszMessage);

    ostrstream  ostrBody;
    char *szMsg = NULL;

    ostrBody << "\r\n-----------------------------";
    ostrBody << "\r\nFrom:\t";
    if(m_pval[irtFrom].ulPropTag == PR_SENDER_NAME)
    {
        ostrBody << m_pval[irtFrom].Value.LPSZ;
    }
    else
    {
        ostrBody << "Unknown";
    }

    if(m_pval[irtTime].ulPropTag == PR_CLIENT_SUBMIT_TIME)
    {
        char sz[30];
        FormatTime(&m_pval[irtTime].Value.ft, sz);
        ostrBody << "\r\nSent:\t";
        ostrBody << sz;
    }
    
    if(m_pval[irtTo].ulPropTag == PR_DISPLAY_TO)
    {
        ostrBody << "\r\nTo:\t";
        ostrBody <<  m_pval[irtTo].Value.LPSZ;
    }

    if(m_pval[irtSubject].ulPropTag == PR_SUBJECT)
    {
        ostrBody << "\r\nSubject:\t";
        ostrBody << m_pval[irtSubject].Value.LPSZ;
    }

    ostrBody << "\r\n";
    if(m_pval && m_pval[irtBody].ulPropTag == PR_BODY)
        ostrBody << m_pval[irtBody].Value.LPSZ;
        
    ostrBody << ends;
    
    szMsg = ostrBody.str();

    if(szMsg != NULL)
    {
        *pszMessage = szMsg;
        return hrSuccess;
    }
    else
    {
        *pszMessage = NULL;
        return m_lsterr.HrSetLastError(ResultFromScode(E_OUTOFMEMORY));
    }
}

///     CBaseForm::HrQuerySave 
//
//
HRESULT CBaseForm::HrQuerySave (DWORD ulSaveOptions)
{
    HRESULT             hr = hrSuccess;
    UINT                ui;

    //
    // Check to see if we are marked as dirty.  If we are clean then
    //  we can just return without doing any work
    //

    if(GetScode(IsDirty()) != S_OK)
        return hrSuccess;

    switch( ulSaveOptions )
    {
    default:
        Assert(FALSE);

    case SAVEOPTS_SAVEIFDIRTY:
        break;

    case SAVEOPTS_NOSAVE:
        return hrSuccess;

    case SAVEOPTS_PROMPTSAVE:
        ui = ShowMessageBox (m_hwnd, "Would you like to save changes?",
                           g_szFormName, MB_ICONEXCLAMATION | MB_YESNOCANCEL);
        switch (ui)
        {
        case IDYES:
            break;

        default:
            Assert(FALSE);
        case IDNO:
            return hrSuccess;
        
        case IDCANCEL:
            return MAPI_E_USER_CANCEL;

        }
    }

    hr = m_pmsgsite->SaveMessage();
    if(hr)
        m_lsterr.HrSetLastError(hr, m_pmsgsite);

    return hr;
}

///  CBaseForm::DoDelete
//
//  called only from our UI
void CBaseForm::DoDelete(void)
{
    HRESULT hr;
    RECT rect;

    GetWindowRect(m_hwnd, &rect);
    
    hr = m_pmsgsite->DeleteMessage(m_pviewctx, &rect);
    if(HR_FAILED(hr))
    {
        m_lsterr.HrSetLastError(hr, m_pmsgsite);
        ShowError();
    }
    if(NULL == m_pmsg)
    {
        ShutdownForm(SAVEOPTS_NOSAVE);
    }
}

///  CBaseForm::DoSave
//
//  called only from our UI
void CBaseForm::DoSave(void)
{
    HRESULT hr;

    hr = m_pmsgsite->SaveMessage();
    if (FAILED(hr))
    {
        m_lsterr.HrSetLastError(hr, m_pmsgsite);
        ShowError();
    }
}
            
///  CBaseForm::DoSubmit
//
//  called only from our UI
void CBaseForm::DoSubmit(void)
{
    HRESULT hr;

    if(!IsAddressed())
    {
        ShowMessageBox(m_hwndDialog, "No recipients", g_szFormName, MB_OK);
        return;
    } 
    
    hr = m_pmsgsite->SubmitMessage(0);
    if (FAILED(hr))
    {
        m_lsterr.HrSetLastError(hr, m_pmsgsite);
        ShowError();
    }
    else
    {
        m_viewnotify.OnSubmitted();
    }   
    
    if (m_pmsg == NULL)
        ShutdownForm(SAVEOPTS_NOSAVE);
}

///  CBaseForm::DoNext
//
//  called only from our UI
void CBaseForm::DoNext(ULONG ulDir)
{   
    Assert(VCDIR_NEXT == ulDir || VCDIR_PREV == ulDir);

    HRESULT hr;
    
    hr = HrQuerySave(SAVEOPTS_PROMPTSAVE);
    if(hr)
    {
        if(hr != MAPI_E_USER_CANCEL)
            ShowError();
        return;
    }

    RECT rect;
    GetWindowRect(m_hwnd, &rect);
        
    hr = ViewCtx()->ActivateNext(ulDir, &rect);
    if(NULL == m_pmsg)
    {
        ShutdownForm(SAVEOPTS_NOSAVE);
    }
}

///  CBaseForm::DoReply
//
//  called only from our UI
void CBaseForm::DoReply(eREPLYTYPE eType)
{
    HRESULT hr;

    hr = HrQuerySave(SAVEOPTS_PROMPTSAVE);
    if(hr)
    {
        if(hr != MAPI_E_USER_CANCEL)
            ShowError();
        return;
    }

    RECT rect;
    GetWindowRect(m_hwnd, &rect);

    int iOffset = GetSystemMetrics(SM_CYCAPTION);
    OffsetRect(&rect, iOffset, iOffset);
    
    hr = HrReply(eType, m_hwnd, &rect);
    if(!hr)
    {
        ShutdownForm(SAVEOPTS_NOSAVE);
    }
    else
    {
        ShowError();
    }
}

///  CBaseForm::DoCopy
//
//  called only from our UI
void CBaseForm::DoCopy(void)
{
    HRESULT         hr;
    LPMAPIFOLDER    pfld = NULL;
    LPMDB           pmdb = NULL;
    
    if(!FGetFoldChooser())
    {
        ShowMessageBox(m_hwnd, "Can't copy", g_szFormName, MB_OK | MB_ICONSTOP);
        return;
    }

    Assert(m_lpfnHrPickFolder && m_hChsFldDll);
    
    if (m_pses == NULL)
    {
        hr = m_pmsgsite->GetSession(&m_pses);
        if(hr)
        {
            m_lsterr.HrSetLastError(hr, m_pmsgsite);
            ShowError();
            return;
        }
    }

    BOOL fOldModalUp = g_FModalUp;

    g_FModalUp = TRUE;

    hr = (*m_lpfnHrPickFolder)(g_hinst, m_hwnd, m_pses, &pfld, &pmdb,
                                &m_cbCFDState, &m_pbCFDState);

    
    g_FModalUp = fOldModalUp;

    if(hr)
    {
        if(GetScode(hr) != MAPI_E_USER_CANCEL)
            ShowMessageBox(m_hwnd, "Can't copy", g_szFormName, MB_OK | MB_ICONSTOP);

        return;
    }

    Assert(m_pmsgsite);
    Assert(pfld);
    Assert(pmdb);

    hr = m_pmsgsite->CopyMessage(pfld);
    pfld->Release();
    pmdb->Release();
    if(hr)
    {
        m_lsterr.HrSetLastError(hr, m_pmsgsite);
        ShowError();
        return;
    }

}


///  CBaseForm::DoMove
//
//  called only from our UI
void CBaseForm::DoMove(void)
{
    HRESULT         hr;
    LPMAPIFOLDER    pfld = NULL;
    LPMDB           pmdb = NULL;
    
    if(!FGetFoldChooser())
    {
        ShowMessageBox(m_hwnd, "Can't move", g_szFormName, MB_OK | MB_ICONSTOP);
        return;
    }

    Assert(m_lpfnHrPickFolder && m_hChsFldDll);
    
    if (m_pses == NULL)
    {
        hr = m_pmsgsite->GetSession(&m_pses);
        if(hr)
        {
            m_lsterr.HrSetLastError(hr, m_pmsgsite);
            ShowError();
            return;
        }
    }

    
    BOOL fOldModalUp = g_FModalUp;

    g_FModalUp = TRUE;

    hr = (*m_lpfnHrPickFolder)(g_hinst, m_hwnd, m_pses, &pfld, &pmdb,
                                //&m_cbCFDState, &m_pbCFDState);
                                NULL, NULL);

    g_FModalUp = fOldModalUp;

    if(hr)
    {
        if(GetScode(hr) != MAPI_E_USER_CANCEL)
            ShowMessageBox(m_hwnd, "Can't move", g_szFormName, MB_OK | MB_ICONSTOP);

        return;
    }

    Assert(m_pmsgsite);
    Assert(pfld);
    Assert(pmdb);

    RECT rect;
    GetWindowRect(m_hwnd, &rect);

    hr = m_pmsgsite->MoveMessage(pfld, ViewCtx(), &rect);
    pfld->Release();
    pmdb->Release();
    if(HR_FAILED(hr))
    {
        m_lsterr.HrSetLastError(hr, m_pmsgsite);
        ShowError();
        return;
    }

    if(NULL == m_pmsg)
    {
        ShutdownForm(SAVEOPTS_NOSAVE);
    }


}

//wraper for MessageBox()
int CBaseForm::ShowMessageBox(HWND hwnd, LPCTSTR lpszText, LPCTSTR lpszTitle, UINT uiStyle)
{
    int iret;
    BOOL fOldModalUp = g_FMBoxUp;
    
    g_FMBoxUp = TRUE;

    iret = MessageBox(hwnd, lpszText, lpszTitle, uiStyle);

    g_FMBoxUp = fOldModalUp;

    return iret;
}
        
//wraper for m_lsterr.ShowError()
void CBaseForm::ShowError(void)
{
    int iret;
    BOOL fOldModalUp = g_FMBoxUp;
    
    g_FMBoxUp = TRUE;

    iret = m_lsterr.ShowError(m_hwnd);

    g_FMBoxUp = fOldModalUp;

}

BOOL CBaseForm::FGetFoldChooser(void)
{
    if(m_lpfnHrPickFolder)
        return TRUE;

    Assert(!m_hChsFldDll);

    UINT uiErrMode = SetErrorMode(SEM_NOOPENFILEERRORBOX);

    m_hChsFldDll = LoadLibrary(szChsFldDllName);

    SetErrorMode(uiErrMode);

    if(m_hChsFldDll)
    {
        if((m_lpfnHrPickFolder = (HRPICKFOLDER)GetProcAddress(m_hChsFldDll,
                                        szChsFldFnName)))
        {
            return TRUE;
        }

        DebugTrace("smpfrm: GetProcAddress for %s failed", szChsFldFnName);
        
        FreeLibrary(m_hChsFldDll);
        m_hChsFldDll = NULL;
    }
    else
    {
        DebugTrace("smpfrm: failed to load choose folder dll\n");
    }

    return FALSE;
}

//
//if the body is to large for GetProps, have to use IStream
//
HRESULT HrStreamInMsgBody(LPMESSAGE pmsg, LPVOID pbase,
                            LPSTR *  pszBody, CLastError * plasterror)
{
    Assert(pmsg);
    Assert(pszBody);
    Assert(plasterror);

    HRESULT hr;
    LPSTREAM lpstreamBody = NULL;
    STATSTG statstg;
    LPSTR szRet = NULL;
    ULONG cb = 0;

    Assert(pszBody);
    *pszBody = NULL;

    hr = pmsg->OpenProperty(PR_BODY, &IID_IStream,
                            STGM_READ, 0, (LPUNKNOWN FAR *) &lpstreamBody);
    if(S_OK != GetScode(hr))
    {
        plasterror->HrSetLastError(hr, pmsg);
        goto err;
    }
    
    hr = lpstreamBody->Stat(&statstg, STATFLAG_NONAME);
    if(S_OK != GetScode(hr))
    {
        plasterror->HrSetLastError(hr, lpstreamBody);
        goto err;
    }
    Assert(statstg.cbSize.HighPart == 0);
    
    //if p base is not null, link the new buffer to it
    if(pbase)
    {
        if(MAPIAllocateMore(statstg.cbSize.LowPart + 1, pbase, (LPVOID FAR *) &szRet))
        {
            plasterror->HrSetLastError(ResultFromScode(E_OUTOFMEMORY));
            goto err;
        }
    }
    else
    {
        if(MAPIAllocateBuffer(statstg.cbSize.LowPart + 1, (LPVOID FAR *) &szRet))
        {
            plasterror->HrSetLastError(ResultFromScode(E_OUTOFMEMORY));
            goto err;
        }
    }
    
    hr = lpstreamBody->Read(szRet, statstg.cbSize.LowPart, &cb);
    if(S_OK != GetScode(hr))
    {
        plasterror->HrSetLastError(hr);
        goto err;
    }
    szRet[statstg.cbSize.LowPart] = '\0';
    
err:
    UlRelease(lpstreamBody);
    lpstreamBody = NULL;
    if(hr)
    {
        if(!pbase)
            MAPIFreeBuffer(szRet);
        szRet = NULL;

    }

    *pszBody = szRet;

    return hr;
}
//
//if the body is to large for SetProps, have to use IStream
//
HRESULT HrStreamOutMsgBody(LPMESSAGE pmsg, LPSTR szBody, CLastError * plasterror)
{
    Assert(pmsg);
    Assert(szBody);
    Assert(plasterror);

    HRESULT hr;
    LPSTREAM lpstreamBody = NULL;
    ULONG cb = 0;

    Assert(szBody);
    
    hr = pmsg->OpenProperty(PR_BODY, &IID_IStream,
                            STGM_READWRITE, 0, (LPUNKNOWN FAR *) &lpstreamBody);
    if(S_OK != GetScode(hr))
    {
        plasterror->HrSetLastError(hr, pmsg);
        goto err;
    }
    
    hr = lpstreamBody->Write(szBody, lstrlen(szBody)+1, NULL);
    if(hr)
        plasterror->HrSetLastError(hr);
    
err:
    UlRelease(lpstreamBody);
    lpstreamBody = NULL;

    return hr;
}

/*
 *  Formats a Win32 file time as a MAPI date/time string.
 *  NOTE: converts from GMT to local time.
 */
void FormatTime(FILETIME *pft, LPSTR szTime)
{
    FILETIME        ft;
    SYSTEMTIME      systime;

    FileTimeToLocalFileTime(pft, &ft);
    FileTimeToSystemTime(&ft, &systime);
    wsprintf(szTime,
        "%04.4d/%02.2d/%02.2d %02.2d:%02.2d",
        systime.wYear, systime.wMonth, systime.wDay,
        systime.wHour, systime.wMinute);
}

///     GetMsgAdrlist 
//    retrieves recipients adrlist of a message
HRESULT GetMsgAdrlist (LPMESSAGE pmsg, LPADRLIST *  ppAdrList, CLastError * plasterror)
{
    *ppAdrList = NULL;
 
    LPMAPITABLE pTable = NULL;
    HRESULT hr;
    
    hr = pmsg->GetRecipientTable (0, &pTable);
    if(!hr)
    {
        hr = HrQueryAllRows(pTable, NULL, NULL, NULL, 0, (LPSRowSet *)ppAdrList);
        if(hr)
        {
            plasterror->HrSetLastError(hr, pTable);
        }
    }
    else
    {
        plasterror->HrSetLastError(hr, pmsg);
    }
    
    pTable->Release();
    
    return hr;
}
