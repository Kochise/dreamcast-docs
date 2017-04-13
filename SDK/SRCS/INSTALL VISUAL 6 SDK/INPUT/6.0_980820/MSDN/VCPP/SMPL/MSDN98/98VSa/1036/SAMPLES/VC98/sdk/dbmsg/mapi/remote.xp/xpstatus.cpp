///////////////////////////////////////////////////////////////////////////////
//
//  File Name
//      XPSTATUS.CPP 
//
//  Description
//      This file implements the methods for the IMAPIStatus interface.
//
//  Authors
//      Irving De la Cruz
//      Les Thaler
//
//  Revision: 1.7
//
// Written for Microsoft Windows Developer Support
// Copyright (c) 1995-1996 Microsoft Corporation. All rights reserved.
//
#include "XPWDSR.H"

// Remark this line to turn verbose tracing OFF
#define DO_INFO_TRACES
#ifdef DO_INFO_TRACES
#define InfoTrace(a)   TraceInfoMessage(a)
#else
#define InfoTrace(a)   
#endif // DO_INFO_TRACES

///////////////////////////////////////////////////////////////////////////////
//    CMAPIStatus::CMAPIStatus()
//
//    Parameters
//      pLogon          Parent logon session for this IMAPIStatus object
//      pProfSectObj    Profile section object for this provider
//
//    Purpose
//      Constructor of the object. Parameters are passed to initialize the
//      data members with the appropiate values.
//
//    Return Value
//      None
//
CMAPIStatus::CMAPIStatus (CXPLogon * pLogon, LPPROFSECT pProfSectObj)

{
    InfoTrace ("CMAPIStatus: Constructor called");
    m_cRef          = 1;
    m_pLogon        = pLogon; // Don't AddRef() this object (to avoid circular reference)
    m_pHeaderFolder = NULL;
    m_pProfSectObj  = pProfSectObj;
    if (m_pProfSectObj)
    {
        m_pProfSectObj->AddRef();
    }
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIStatus::~CMAPIStatus()
//
//    Parameters
//      None
//
//    Purpose
//      Destructor of CMAPIStatus
//
//    Return Value
//      None
//
CMAPIStatus::~CMAPIStatus ()
{
    InfoTrace ("CMAPIStatus: Destructor called");
    if (m_pProfSectObj)
    {
        m_pProfSectObj->Release();
    }
    if (m_pHeaderFolder && m_pHeaderFolder->m_cRef)
    {
        m_pHeaderFolder->Release();     // Release our instance of the folder
    }
    m_pHeaderFolder = NULL;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIStatus::QueryInterface()
//
//    Parameters
//      { Refer to OLE Documentation on this method }
//
//    Purpose
//      Returns a pointer to a interface requested if the interface is 
//      supported and implemented by this object. If it is not supported, it 
//      returns NULL
//
//    Return Value
//      An HRESULT
//
STDMETHODIMP CMAPIStatus::QueryInterface (REFIID riid, LPVOID * ppvObj)
{
    HRESULT hResult = S_OK;
    // OLE requires NULLing parameter
    *ppvObj = NULL;
    // If this is one of the supported IIDs return an interface pointer to it
    if (riid == IID_IMAPIStatus || riid == IID_IMAPIProp || riid == IID_IUnknown)
    {
        *ppvObj = (LPVOID)this;
        AddRef();
    }
    else
    {
        // The status object of a remote transport can return a folder object,
        // if the IID requested is for a MAPI folder object. The object returned in
        // this case is the folder that has the headers of messages available in
        // the remote host. A remote client viewer application requests operations
        // on those message by modifying the PR_MESSAGE_STATUS property in each
        // row of the contents table of this folder and later calls the
        // ValidateState method of this IMAPIStatus object
        if (riid == IID_IMAPIFolder)
        {
            // If we already have a folder around, return the same object to the caller.
            if (!m_pHeaderFolder)
            {
                m_pHeaderFolder = new CMAPIFolder (this, m_pLogon);
                if (!m_pHeaderFolder)
                {
                    TraceMessage("CMAPIStatus::QueryInterface: Unable to create remote viewer folder");
                    hResult = E_OUTOFMEMORY;
                }
            }
            if (!hResult)
            {
                m_pHeaderFolder->AddRef();      // One for the caller requesting it
                *ppvObj = (LPVOID)m_pHeaderFolder;
            }
        }
        else
        {
            // This object does not support the interface requested
            hResult = E_NOINTERFACE;
        }
    }
    return hResult;
}    

///////////////////////////////////////////////////////////////////////////////
// IMAPIProp virtual member functions
//

///////////////////////////////////////////////////////////////////////////////
//    CMAPIStatus::GetLastError()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Called by a client to get a string from the transport describing the
//      last error that occurred.
//
//    Return Value
//      An HRESULT
//
STDMETHODIMP CMAPIStatus::GetLastError (HRESULT         hError,
                                        ULONG           ulFlags,
                                        LPMAPIERROR *   ppMAPIError)
{
    InfoTrace ("CMAPIStatus::GetLastError method called");
    Validate_IMAPIProp_GetLastError (this, hError, ulFlags, ppMAPIError);
    // Allocate and fill a MAPIERROR structure with the error passed in.
    // Use the common helper function GetMAPIError
    return GetMAPIError (ppMAPIError, ulFlags, hError, m_pLogon->GetInstance());
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIStatus::SaveChanges()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Place holder. Replace this function with actual implementation 
//      if needed.
//
//    Return Value
//      S_OK always.
//
STDMETHODIMP CMAPIStatus::SaveChanges (ULONG ulFlags)
{
    InfoTrace ("CMAPIStatus::SaveChanges method called");
    Validate_IMAPIProp_SaveChanges (this, ulFlags);
    return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIStatus::GetProps()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      The caller specifies an array of tags, and this method returns a
//      property value array for thoses tag, if found. The tags are the ones
//      available in the transport ID array
//
//    Return Value
//      An HRESULT
//
STDMETHODIMP CMAPIStatus::GetProps (LPSPropTagArray     pTags,
                                    ULONG               ulFlags,
                                    ULONG *             pcValues,
                                    LPSPropValue *      ppPropArray)
{
    InfoTrace ("CMAPIStatus::GetProps method called");
    Validate_IMAPIProp_GetProps (this, pTags, ulFlags, pcValues, ppPropArray);
    
    #ifdef DO_INFO_TRACES
    if (!pTags)
    {
        TraceInfoMessage ("CMAPIStatus::GetProps: All properties requested");
    }
    else
    {
        TraceMessage ("CMAPIStatus::GetProps Properties requested..."); for (ULONG j=0; j<pTags->cValues; j++) { TraceProp (pTags->aulPropTag[j]); }
    }
    #endif // DO_INFO_TRACES

    BOOL fGetAllProps = pTags ? FALSE : TRUE;
    if (!pTags)
    {
        pTags = (LPSPropTagArray)&sptStatusObj;
    }
    
    *pcValues = pTags->cValues;
    HRESULT hResult = gpfnAllocateBuffer (sizeof(SPropValue)*(*pcValues), (LPVOID *)ppPropArray);
    if (hResult)
    {
        TraceResult ("CMAPIStatus::GetProps: Memory allocation failed", hResult);
        return hResult;
    }
    if (fGetAllProps)
    {
        for (ULONG i=0; i<sptStatusObj.cValues; i++)
        {
            (*ppPropArray)[i].ulPropTag = sptStatusObj.aulPropTag[i];
        }
    }
    else
    {
        // A client of the IMAPIProp::GetProps() method can pass PT_UNSPECIFIED in the
        // tag of a property. Is the provider's responsiblity to return
        // the proper type of the property.
        for (ULONG k=0; k<pTags->cValues; k++)
        {
            for (ULONG i=0; i<sptStatusObj.cValues; i++)
            {
                if (PROP_ID(pTags->aulPropTag[k]) == PROP_ID(sptStatusObj.aulPropTag[i]))
                {
                    (*ppPropArray)[k].ulPropTag = sptStatusObj.aulPropTag[i];
                }
                else
                {
                    (*ppPropArray)[k].ulPropTag = pTags->aulPropTag[k];
                }
            }
        }
    }

    TCHAR szBuffer[128];
    BOOL fGotErrors = FALSE;    
    LPVOID pSrc, pDst;
    ULONG cbSize;
    for (ULONG i=0; i<*pcValues; i++)
    {
        hResult = S_OK;
        switch ((*ppPropArray)[i].ulPropTag)
        {
            case PR_NULL :
                (*ppPropArray)[i].Value.err = S_OK;
                break;
            case PR_RESOURCE_METHODS :
                (*ppPropArray)[i].Value.l = STATUS_SETTINGS_DIALOG |
                                            STATUS_FLUSH_QUEUES |
                                            STATUS_VALIDATE_STATE |
                                            STATUS_CHANGE_PASSWORD;
                break;
            case PR_RESOURCE_TYPE :
                (*ppPropArray)[i].Value.l = MAPI_TRANSPORT_PROVIDER;
                break;
            case PR_RESOURCE_FLAGS :
                hResult = E_FAIL;
                if (m_pProfSectObj)
                {
                    LPSPropValue pResFlags;
                    SPropTagArray sptResFlags = { 1, { PR_RESOURCE_FLAGS } };
                    ULONG cValues;
                    hResult = m_pProfSectObj->GetProps (&sptResFlags, fMapiUnicode, &cValues, &pResFlags);
                    if (SUCCEEDED(hResult))
                    {
                        if (PR_RESOURCE_FLAGS == pResFlags->ulPropTag)
                        {
                            (*ppPropArray)[i].Value.l = pResFlags->Value.l;
                        }
                        gpfnFreeBuffer (pResFlags);
                    }
                }
                if (hResult)
                {
                    (*ppPropArray)[i].Value.l = STATUS_PRIMARY_IDENTITY;
                    hResult = S_OK;
                }
                break;
            case PR_DISPLAY_NAME :
                wsprintf (szBuffer,
                          TEXT("%s (%s)"),
                          TRANSPORT_DISPLAY_NAME_STRING,
                          m_pLogon->GetServerName());
                pSrc = (LPVOID)szBuffer;
                break;
            case PR_PROVIDER_DLL_NAME :
                pSrc = (LPVOID)TRANSPORT_DLL_NAME_STRING;
                break;
            case PR_PROVIDER_DISPLAY :
                pSrc = (LPVOID)TRANSPORT_DISPLAY_NAME_STRING;
                break;
            case PR_IDENTITY_DISPLAY :
                pSrc = (LPVOID)m_pLogon->m_pIdentityProps[XPID_NAME].Value.LPSZ;
                break;
            case PR_IDENTITY_ENTRYID :
                cbSize = m_pLogon->m_pIdentityProps[XPID_EID].Value.bin.cb;
                pSrc = (LPVOID)m_pLogon->m_pIdentityProps[XPID_EID].Value.bin.lpb;
                break;
            case PR_IDENTITY_SEARCH_KEY :
                cbSize = m_pLogon->m_pIdentityProps[XPID_SEARCH_KEY].Value.bin.cb;
                pSrc = (LPVOID)m_pLogon->m_pIdentityProps[XPID_SEARCH_KEY].Value.bin.lpb;
                break;
            case PR_STATUS_CODE :
                (*ppPropArray)[i].Value.l = (long)m_pLogon->GetTransportStatusCode();
                break;
            case PR_STATUS_STRING :
                szBuffer[0] = 0;
                m_pLogon->LoadStatusString (szBuffer, sizeof(szBuffer) - 1);
                pSrc = (LPVOID)szBuffer;
                break;
            case PR_CURRENT_VERSION :
                (*ppPropArray)[i].Value.li.LowPart = TRANSPORT_VERSION_MAJOR;
                (*ppPropArray)[i].Value.li.HighPart = TRANSPORT_VERSION_MINOR;
                break;
            case PR_OBJECT_TYPE :
                (*ppPropArray)[i].Value.l = MAPI_STATUS;
                break;
            default:
                hResult = MAPI_E_NOT_FOUND;
                #ifdef DO_INFO_TRACES
                TraceRaw ("CMAPIStatus::GetProps: Not Found - "); TraceProp ((*ppPropArray)[i].ulPropTag);
                #endif // #DO_INFO_TRACES
                break;
        }
        if (!hResult && 
            (PROP_TYPE((*ppPropArray)[i].ulPropTag) == PT_BINARY ||
             PROP_TYPE((*ppPropArray)[i].ulPropTag) == PT_TSTRING))
        {
            if (PROP_TYPE((*ppPropArray)[i].ulPropTag) == PT_TSTRING)
            {
                cbSize = Cbtszsize ((LPTSTR)pSrc);
            }
            hResult = gpfnAllocateMore (cbSize, *ppPropArray, &pDst);
            if (!hResult)
            {
                CopyMemory (pDst, pSrc, cbSize);
                if (PROP_TYPE((*ppPropArray)[i].ulPropTag) == PT_BINARY)
                {
                    (*ppPropArray)[i].Value.bin.cb  = cbSize;
                    (*ppPropArray)[i].Value.bin.lpb = (LPBYTE)pDst;
                }
                else
                {
                    (*ppPropArray)[i].Value.LPSZ = (LPTSTR)pDst;
                }
            }
        }
        if (hResult)
        {
            (*ppPropArray)[i].ulPropTag = PROP_TAG(PT_ERROR, PROP_ID((*ppPropArray)[i].ulPropTag));
            (*ppPropArray)[i].Value.err = hResult;
            fGotErrors = TRUE;
        }
    }
    if (fGotErrors)
    {
        hResult = MAPI_W_ERRORS_RETURNED;
    }
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIStatus::GetPropList()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Returns a tag array with the properties in the status row of this 
//      transport. The caller is responsible for freeing the memory allocated
//      for the tag array.
//
//    Return Value
//      An HRESULT
//
STDMETHODIMP CMAPIStatus::GetPropList (ULONG                ulFlags,
                                       LPSPropTagArray *    ppPropTagArray)
{
    InfoTrace ("CMAPIStatus::GetPropList method called");
    Validate_IMAPIProp_GetPropList (this, ulFlags, ppPropTagArray);

    ULONG cbTagsArraySize = CbNewSPropTagArray(NUM_STATUS_OBJECT_PROPS);
    // Allocate the required amount of memory
    HRESULT hResult = gpfnAllocateBuffer (cbTagsArraySize, (LPVOID *)ppPropTagArray);
    TraceResult ("CMAPIStatus::GetPropList: Memory allocation failed", hResult);
    if (!hResult)
    {
        // Copy the contents of our property tag array into the buffer
        CopyMemory (*ppPropTagArray, &sptStatusObj, cbTagsArraySize);
    }
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIStatus::OpenProperty()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Place holder. Replace this function with actual implementation 
//      if needed.
//
//    Return Value
//      MAPI_E_NO_SUPPORT always.
//
STDMETHODIMP CMAPIStatus::OpenProperty (ULONG           ulPropTag,
                                        LPCIID          piid,
                                        ULONG           ulInterfaceOptions,
                                        ULONG           ulFlags,
                                        LPUNKNOWN *     ppUnk)
{
    InfoTrace ("CMAPIStatus::OpenProperty method called");
    Validate_IMAPIProp_OpenProperty (this, ulPropTag,  piid, ulInterfaceOptions, ulFlags, ppUnk);
    return MAPI_E_NO_SUPPORT;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIStatus::SetProps()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Place holder. Replace this function with actual implementation 
//      if needed.
//
//    Return Value
//      MAPI_E_NO_SUPPORT always.
//
STDMETHODIMP CMAPIStatus::SetProps (ULONG                   cValues,
                                    LPSPropValue            pPropArray,
                                    LPSPropProblemArray *   ppProblems)
{
    InfoTrace ("CMAPIStatus::SetProps method called");
    Validate_IMAPIProp_SetProps (this, cValues, pPropArray, ppProblems);
    return MAPI_E_NO_SUPPORT;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIStatus::DeleteProps()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Place holder. Replace this function with actual implementation 
//      if needed.
//
//    Return Value
//      MAPI_E_NO_SUPPORT always.
//
STDMETHODIMP CMAPIStatus::DeleteProps (LPSPropTagArray          pPropTagArray,
                                       LPSPropProblemArray *    ppProblems)
{
    InfoTrace ("CMAPIStatus::DeleteProps method called");
    Validate_IMAPIProp_DeleteProps (this, pPropTagArray, ppProblems);
    return MAPI_E_NO_SUPPORT;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIStatus::CopyTo()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Place holder. Replace this function with actual implementation 
//      if needed.
//
//    Return Value
//      MAPI_E_NO_SUPPORT always.
//
STDMETHODIMP CMAPIStatus::CopyTo (ULONG                   ciidExclude,
                                  LPCIID                  rgiidExclude,
                                  LPSPropTagArray         pExcludeProps,
                                  ULONG                   ulUIParam,
                                  LPMAPIPROGRESS          pProgress,
                                  LPCIID                  pInterface,
                                  LPVOID                  pDestObj,
                                  ULONG                   ulFlags,
                                  LPSPropProblemArray *   ppProblems)
{
    InfoTrace ("CMAPIStatus::CopyTo method called");
    Validate_IMAPIProp_CopyTo (this,
                               ciidExclude,
                               rgiidExclude,
                               pExcludeProps,
                               ulUIParam,
                               pProgress,
                               pInterface,
                               pDestObj,
                               ulFlags,
                               ppProblems);
    return MAPI_E_NO_SUPPORT;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIStatus::CopyProps()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Place holder. Replace this function with actual implementation 
//      if needed.
//
//    Return Value
//      MAPI_E_NO_SUPPORT always.
//
STDMETHODIMP CMAPIStatus::CopyProps (LPSPropTagArray            pIncludeProps,
                                     ULONG                      ulUIParam,
                                     LPMAPIPROGRESS             pProgress,
                                     LPCIID                     pInterface,
                                     LPVOID                     pDestObj,
                                     ULONG                      ulFlags,
                                     LPSPropProblemArray *      ppProblems)
{
    InfoTrace ("CMAPIStatus::CopyProps method called");
    Validate_IMAPIProp_CopyProps (this,
                                  pIncludeProps,
                                  ulUIParam,
                                  pProgress,
                                  pInterface,
                                  pDestObj,
                                  ulFlags,
                                  ppProblems);
    return MAPI_E_NO_SUPPORT;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIStatus::GetNamesFromIDs()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Place holder. Replace this function with actual implementation 
//      if needed.
//
//    Return Value
//      MAPI_E_NO_SUPPORT always.
//
STDMETHODIMP CMAPIStatus::GetNamesFromIDs (LPSPropTagArray *    ppPropTags,
                                           LPGUID               pPropSetGuid,
                                           ULONG                ulFlags,
                                           ULONG *              pcPropNames,
                                           LPMAPINAMEID **      pppPropNames)
{
    InfoTrace ("CMAPIStatus::GetNamesFromIDs method called");
    Validate_IMAPIProp_GetNamesFromIDs (this,
                                        ppPropTags,
                                        pPropSetGuid,
                                        ulFlags,
                                        pcPropNames,
                                        pppPropNames);
    return MAPI_E_NO_SUPPORT;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIStatus::GetIDsFromNames()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Place holder. Replace this function with actual implementation 
//      if needed.
//
//    Return Value
//      MAPI_E_NO_SUPPORT always.
//
STDMETHODIMP CMAPIStatus::GetIDsFromNames (ULONG                cPropNames,
                                           LPMAPINAMEID *       ppPropNames,
                                           ULONG                ulFlags,
                                           LPSPropTagArray *    ppPropTags)
{
    InfoTrace ("CMAPIStatus::GetIDsFromNames method called");
    Validate_IMAPIProp_GetIDsFromNames (this,
                                        cPropNames,
                                        ppPropNames,
                                        ulFlags,
                                        ppPropTags);
    return MAPI_E_NO_SUPPORT;
}

///////////////////////////////////////////////////////////////////////////////
// IMAPIStatus virtual member functions implementation
//

///////////////////////////////////////////////////////////////////////////////
//    CMAPIStatus::ValidateState()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      This method is called by the REMOTE viewer UI to start the remote
//      processing. We check the ulFlags bits to see what operation is being
//      requested and do it. All the operation of this transport are
//      ASYNCHRONOUS meaning, that the call returns to the client before the
//      action is truly completed.
//      To control this, we dynamically change PR_REMOTE_VALIDATE_OK on the
//      status row so that the client calls us at intervals to check if we
//      finished or not.
//      When an action is requested, we change the internal state of the
//      transport and we tell the spooler to FLUSH us, so that it can better
//      manage interaction with multiple transport.
//      This is the recommended way for remote transports to connect using
//      shared resources such as COM port. In this transport, we do it this
//      way for purposes of demonstration of how it should be done.
//
//    Return Value
//      An HRESULT
//
STDMETHODIMP CMAPIStatus::ValidateState (ULONG ulUIParam, ULONG ulFlags)
{   
    InfoTrace ("CMAPIStatus::ValidateState method called");
    Validate_IMAPIStatus_ValidateState (this, ulUIParam, ulFlags);
    
    // We only support this flags
    if (ulFlags & ~(SHOW_XP_SESSION_UI |
                    REFRESH_XP_HEADER_CACHE |
                    PROCESS_XP_HEADER_CACHE |
                    FORCE_XP_CONNECT |
                    FORCE_XP_DISCONNECT |
                    ABORT_XP_HEADER_OPERATION))
    {
        return MAPI_E_UNKNOWN_FLAGS;
    }

    if (ulFlags & SHOW_XP_SESSION_UI)  
    {
        // We don't implement UI for processing the headers
        return MAPI_E_NO_SUPPORT;
    }
    if (ulFlags & ABORT_XP_HEADER_OPERATION)
    {
        // If we are called to cancel an opertaion, if we can't cancel we will set a
        // flag so that when the current operation finishes, we won't continue.
        if (HEADERS_AND_DOWNLOAD == m_pLogon->GetTransportState())
        {
            m_pLogon->m_fCancelPending = TRUE;
            return MAPI_E_BUSY;
        }
        // The cancel occured while we where flushing the inbound queue. We can
        // cancel this by telling the spooler to stop flushing us. Note that at
        // this point ALL the message have been downloaded to temporary files
        // and are simply pending to be placed in the default inbox
        if (DOWNLOADING_MESSAGES & m_pLogon->GetTransportStatusCode())
        {
            m_pLogon->RemoveStatusBits (DOWNLOADING_MESSAGES); // Tell the spooler to take us off from inbound flush
            m_pLogon->AddStatusBits (STATUS_OFFLINE); // The transport is now OFF line
            m_pLogon->UpdateStatus (TRUE, TRUE); // Set PR_REMOTE_VALIDATE_OK to TRUE
            m_pLogon->SetTransportState (WAITING); // The transport is now IDLE
        }
        return S_OK;
    }
    HRESULT hResult = S_OK;
    // The request is to process remote messages and upload any deferred messages
    if (ulFlags & PROCESS_XP_HEADER_CACHE)
    {
        if (PENDING_RETURN_CODE == m_pLogon->GetTransportState())
        {
            // The transport had finished a request and is ready to return the results error (if any)
            m_pLogon->SetTransportState (WAITING);
            m_pLogon->UpdateStatus (TRUE, FALSE);
            m_pLogon->UpdateProgress (-1, REMOTE_ACTION_IDLE); // Reset PR_REMOTE_PROGRESS_TEXT
            return m_pLogon->m_hRemoteActionErr;
        }
        if (HEADERS_AND_DOWNLOAD == m_pLogon->GetTransportState())
        {
            // We are busy, poll me later
            return MAPI_E_BUSY;
        }

        // The MS Exchange viewer wants a remote transport to update the headers
        // during this call with this flag, so we must update the headers.
        // The MS Exchange remote viewer does not call this method with
        // REFRESH_XP_HEADER_CACHE alone, any longer.
        ulFlags |= REFRESH_XP_HEADER_CACHE;
        m_pLogon->m_fCancelPending = FALSE;
    }
    // The request is to get remote headers
    if (!hResult && (ulFlags & REFRESH_XP_HEADER_CACHE))
    {
        if (PENDING_RETURN_CODE == m_pLogon->GetTransportState())
        {
            m_pLogon->SetTransportState (WAITING);
            m_pLogon->UpdateStatus (TRUE, FALSE);
            m_pLogon->UpdateProgress (-1, REMOTE_ACTION_IDLE); // Reset PR_REMOTE_PROGRESS_TEXT
            return m_pLogon->m_hRemoteActionErr;
        }
        if (HEADERS_AND_DOWNLOAD == m_pLogon->GetTransportState())
        {
            return MAPI_E_BUSY;
        }
        m_pLogon->m_fCancelPending = FALSE;

        // Fire up a request to the spooler to flush the INBOUD logic
        // which in turn will also get new headers.
        m_pLogon->SetTransportState (HEADERS_AND_DOWNLOAD);
        m_pLogon->AddStatusBits (DOWNLOADING_MESSAGES);
        m_pLogon->RemoveStatusBits (STATUS_OFFLINE);
        m_pLogon->UpdateStatus (TRUE, FALSE);
        return MAPI_E_BUSY;
    }
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIStatus::SettingsDialog()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Called by a client to display the configuration settings, if any, for
//      a particular transport. This method could be used to display the 
//      current setting in a READ-ONLY mode
//
//    Return Value
//      An HRESULT
//
STDMETHODIMP CMAPIStatus::SettingsDialog (ULONG ulUIParam, ULONG ulFlags)
{
    InfoTrace ("CMAPIStatus::SettingsDialog method called");
    Validate_IMAPIStatus_SettingsDialog (this, ulUIParam, ulFlags);
    
    ULONG ulPropCount;
    LPSPropValue pProps = NULL;
    LPPROFSECT pProfileObj = NULL;
    HRESULT hResult = S_OK;
    BOOL fChangeAccount = FALSE;
    TCHAR szOldMailboxName[MAX_ALIAS_SIZE+1], szOldServer[MAX_STRING_SIZE+1];
    CFGDLG CfgDialog = { 0 };

    PrivInitialize3DCtl (m_pLogon->GetInstance());
    DWORD dwWait = WaitForSingleObject (m_pLogon->m_hUIMutex, 1000); // Wait for the MUTEX for 1 second
    if (WAIT_TIMEOUT == dwWait)
    {
        PrivateMessageBox (IDS_MSG_CONFIG_UI_IN_USE, (HWND)ulUIParam);
        PrivUninitialize3DCtl (m_pLogon->GetInstance());
        return MAPI_E_BUSY;
    }

    // Open the profile for our provider and get what ever is set there
    hResult = OpenServiceProfileSection (m_pLogon->m_pSupObj, &pProfileObj, gpfnFreeBuffer);
    if (hResult)
    {
        TraceResult ("CMAPIStatus::SettingsDialog: Failed to open the profile section", hResult);
        goto ErrorExit;
    }
    
    hResult = pProfileObj->GetProps ((LPSPropTagArray)&sptLogonProps,
                                     fMapiUnicode,
                                     &ulPropCount,
                                     &pProps);
    if (FAILED(hResult))
    {
        TraceResult ("CMAPIStatus::SettingsDialog: Failed to get profile section properties", hResult);
        goto ErrorExit;
    }

    lstrcpy (szOldMailboxName, pProps[MAILBOX_NAME].Value.LPSZ);
    lstrcpy (szOldServer, pProps[SERVER_NAME].Value.LPSZ);

    // Fill in the logon UI structure
    CfgDialog.hInst   = m_pLogon->GetInstance();
    CfgDialog.hWnd    = (HWND)ulUIParam;
    CfgDialog.ppProps = &pProps;
    CfgDialog.pSupObj = m_pLogon->m_pSupObj;
    CfgDialog.ulFlags = ulFlags;

ShowPropsAgain:
    hResult = DoLogonDlg (&CfgDialog);
    // If the dialog was displayed READ-only, we don't need to verify
    // anything because the user didn't change anything and we are
    // still runnig with the logon settings of the session.
    if (hResult || (ulFlags & UI_READONLY))
    {
        goto ErrorExit;
    }
    if (!PingRemoteServer ((HWND)ulUIParam, pProps))
    {
        goto ShowPropsAgain;
    }

    // We don't need to set the header file name back into the profile.
    hResult = pProfileObj->SetProps (NUM_LOGON_PROPERTIES, pProps, NULL);
    if (hResult)
    {
        TraceResult ("CMAPIStatus::SetttingsDialog: Failed to save the properties back into the profile", hResult);
        goto ErrorExit;
    }
    if (lstrcmpi (szOldMailboxName, pProps[SERVER_NAME].Value.LPSZ))
    {
        m_pLogon->SetServerName (pProps[SERVER_NAME].Value.LPSZ);
        fChangeAccount = TRUE;
    }
    // If the configuration changed, we need to change the download directory
    // which is based on the mailbox name.
    if (PR_SMP_MAILBOX_NAME == pProps[MAILBOX_NAME].ulPropTag &&
        lstrcmpi (szOldMailboxName, pProps[MAILBOX_NAME].Value.LPSZ))
    {
        TCHAR szTmpDir[_MAX_PATH], szDownloadDir[_MAX_PATH];
        GetTempPath (_MAX_PATH, szTmpDir);
        lstrcat (szTmpDir, WINDS_DATA_DIRECTORY);
        // Remove the download directory for the old mailbox
        wsprintf (szDownloadDir, WINDS_DOWNLOAD_DIR_NAME_FORMAT, szTmpDir, szOldMailboxName);
        RemoveDirectory (szDownloadDir);
        // Create the download directory for the new mailbox
        wsprintf (szDownloadDir, WINDS_DOWNLOAD_DIR_NAME_FORMAT, szTmpDir, pProps[MAILBOX_NAME].Value.LPSZ);
        CreateDirectory (szDownloadDir, NULL);
        fChangeAccount = TRUE;
    }
    if (fChangeAccount)
    {
        m_pLogon->SetAccountProps (pProps[MAILBOX_NAME].Value.LPSZ,
                                   (DWORD)pProps[MAILBOX_ID].Value.l,
                                   pProps[USER_NAME].Value.LPSZ,
                                   pProps[PASSWORD].Value.LPSZ);
    }

    // Reflect the new changes in the status row.
    m_pLogon->InitializeStatusRow (STATUSROW_UPDATE);

    // If the user changed the upload time, reset the upload timer.
    if (m_pLogon->SetUploadTime (pProps[UPLOAD_TIME].Value.ft))
    {
        m_pLogon->StopUploadTimer();
        m_pLogon->InitializeTimer();
        m_pLogon->StartUploadTimer();
    }
    

ErrorExit:
    if (pProfileObj)
    {
        pProfileObj->Release();
    }
    gpfnFreeBuffer (pProps);
    PrivUninitialize3DCtl (m_pLogon->GetInstance());
    ReleaseMutex (m_pLogon->m_hUIMutex);
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIStatus::ChangePassword()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Changes the password for the mailbox the service is logged in.
//
//    Return Value
//      An HRESULT
//
STDMETHODIMP CMAPIStatus::ChangePassword (LPTSTR    pszOldPass,
                                          LPTSTR    pszNewPass,
                                          ULONG     ulFlags)
{
    InfoTrace ("CMAPIStatus::ChangePassword method called");
    Validate_IMAPIStatus_ChangePassword (this, pszOldPass, pszNewPass, ulFlags);
    HRESULT hResult = ChangeMBServerPassword (m_pLogon->GetServerName(),
                                              m_pLogon->GetAccountName(),
                                              pszOldPass,
                                              pszNewPass);
    if (hResult)
    {
        TraceResult ("CMAPIStatus::ChangePassword", hResult);
        if (HRESULT_FROM_WIN32 (ERROR_INVALID_PASSWORD) == hResult)
        {
            hResult = E_ACCESSDENIED;
        }
    }
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIStatus::FlushQueues()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Stub function that calls the IXPLogon object for this status object
//      to actually flush any deferred messages.
//      This only flushes messages deferred for delivery. It does not
//      downloads any messages from the server.
//
//    Return Value
//      S_OK always
//
STDMETHODIMP CMAPIStatus::FlushQueues (ULONG        ulUIParam,
                                       ULONG        cbTargetTransport,
                                       LPENTRYID    pTargetTransport,
                                       ULONG        ulFlags)
{
    InfoTrace ("CMAPIStatus::FlushQueues method called");
    Validate_IMAPIStatus_FlushQueues (this,
                                      ulUIParam,
                                      cbTargetTransport,
                                      pTargetTransport,
                                      ulFlags);
    DWORD dwFlushBits = 0;
    if (ulFlags & FLUSH_UPLOAD)
    {
        dwFlushBits |= UPLOADING_MESSAGES;
    }
    if (ulFlags & FLUSH_DOWNLOAD)
    {
        dwFlushBits |= DOWNLOADING_MESSAGES;
    }
    if (dwFlushBits)
    {
        m_pLogon->AddStatusBits (dwFlushBits);
        m_pLogon->UpdateStatus();
    }
    return S_OK;
}

// End of File for XPSTATUS.CPP
