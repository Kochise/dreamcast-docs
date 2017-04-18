//////////////////////////////////////////////////////////////////////////////
//
//  File Name
//      XPLOGON.CPP
//
//  Description
//      This file implements the IXPLogon interface with the methods specified
//      in the MAPI SPI 1.0.
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
//
#include "XPWDSR.H"

#define DO_INFO_TRACES
#ifdef DO_INFO_TRACES
#define InfoTrace(a)   TraceInfoMessage(a)
#else
#define InfoTrace(a)
#endif // DO_INFO_TRACES

// Remark this line to turn verbose tracing OFF
MAPIUID guidABEntries = AB_UID_PROVIDER;
MAPIUID guidXPABEntries = XP_WINDS_AB_ENTRIES;
MAPIUID * puidWINDSEntries;
TCHAR gszProviderName[] = TEXT("WINDS Transport Service");
LPTSTR gszWINDSAddressType = WINDS_ADDRESS_TYPE;
LPTSTR * gpszXPAddressTypes;

void CALLBACK UploadTimerProc (HWND    hOwnerWnd,
                               UINT    Message,
                               UINT    idEvent,
                               DWORD   dwTime);

///////////////////////////////////////////////////////////////////////////////
//    CXPLogon::CXPLogon()
//
//    Parameters
//      hInstance               Instance of the provider DLL
//      pSupObj                 Pointer to IMAPISupport object used in
//                              CXPLogon methods
//      pszHeadersFile          Full file path where the remote headers are
//                              store in the local computer.
//      fGetHeaders             Weather or not to get the headers of the
//                              mailbox during a scheduled connection.
//      pUserMailboxInfo        Pointer to a MAILBOX_INFO structure with the
//                              information of the logged user as store in
//                              the WINDS server.
//      dwMailboxID             ID of the user in the WINDS system.
//      pszRemoteServer         Name of the remote WINDS server to which
//                              this transport communicates
//      hUIMutex                Handle to a WINDS mutex to allow single access
//                              to the UI configuration of this provider.
//
//    Purpose
//      Constructor of the object. Parameters are passed to initialize the
//      data members with the appropiate values.
//
//    Return Value
//      None
//
CXPLogon::CXPLogon (HINSTANCE       hInstance,
                    LPMAPISUP       pSupObj,
                    LPTSTR          pszHeadersFile,
                    BOOL            fGetHeaders,
                    PMAILBOX_INFO   pUserMailboxInfo,
                    DWORD           dwMailboxID,
                    LPTSTR          pszRemoteServer,
                    HANDLE          hUIMutex)
{
    InfoTrace ("CXPLogon: Constructor called");
    m_cRef           = 1;
    m_pIdentityProps = NULL;
    m_hInstance      = hInstance;
    m_pSupObj        = pSupObj;
    m_pStatusObj     = NULL;
    m_pIdentityProps = NULL;
    ZeroMemory (&m_stDelivTime, sizeof(SYSTEMTIME));
    m_uTimerID       = 0;
    m_hTimerWnd      = NULL;
    m_fABWDSInstalled = FALSE;
    m_fGetHeaders    = fGetHeaders;
    m_hUIMutex       = hUIMutex;
    m_raAction       = REMOTE_ACTION_IDLE;
    m_UserInfo       = *pUserMailboxInfo;
    ZeroMemory (&m_UserEID, CB_PRIVATE_EID);
    m_UserEID.uidGlobal = guidABEntries;
    m_UserEID.bVersion = ENTRYID_VERSION;
    m_UserEID.bObject = MAPI_MAILUSER;
    m_UserEID.dwObjID = dwMailboxID;

    m_pSupObj->AddRef();

    lstrcpy (m_szHeaders, pszHeadersFile);
    lstrcpy (m_szServer, pszRemoteServer);

    wsprintf (m_szAddress, TEXT("%s\\%s"), m_szServer, m_UserInfo.szMailboxName);

    // Initialize the messages download list object
    m_List.SetLogon(this);
    if (!m_List.Init())
    {
        throw CException (E_OUTOFMEMORY);
    }
    SetTransportState (WAITING);
}

///////////////////////////////////////////////////////////////////////////////
//    CXPLogon::~CXPLogon()
//
//    Parameters
//      None
//
//    Purpose
//      Destructor of CXPLogon. Releases memory allocated for internal
//      properties during the life of this transport logon object.
//
//    Return Value
//      None
//
CXPLogon::~CXPLogon()
{
    InfoTrace ("CXPLogon: Destructor called");
    gpfnFreeBuffer (m_pIdentityProps);
    CloseHandle (m_hUIMutex);

    EmptyInboundQueue();

    // Delete CMAPIStatus Object
/*    if (m_pStatusObj)
    {
        m_pStatusObj->Release();
        m_pStatusObj = NULL;
    }
*/
    // Release the IMAPISupport object
    m_pSupObj->Release();
    m_pSupObj = NULL;

    // Just as a safety precaution, make sure the timer is off.
    StopUploadTimer();

    // Just in case the DLL is still hanging around
    PrivUninitialize3DCtl (m_hInstance);
}

///////////////////////////////////////////////////////////////////////////////
//    CXPLogon::QueryInterface()
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
STDMETHODIMP CXPLogon::QueryInterface (REFIID riid, LPVOID * ppvObj)
{
    // OLE requires NULLing parameter
    *ppvObj = NULL;
    // If this is one of the two IID return an interface pointer to it
    if (riid == IID_IXPLogon || riid == IID_IUnknown)
    {
        *ppvObj = (LPVOID)this;
        // Increase usage count of this object
        AddRef();
        return S_OK;
    }
    // This object does not support the interface requested
    return E_NOINTERFACE;
}

///////////////////////////////////////////////////////////////////////////////
// IXPLogon virtual member functions implementation
//

///////////////////////////////////////////////////////////////////////////////
//    CXPLogon::AddressType()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Called by the MAPI Spooler when initializing this XP logon object to
//      allow the transport to register the address it will handle
//
//    Return Value
//      S_OK always
//
STDMETHODIMP CXPLogon::AddressTypes (ULONG *        pulFlags,
                                     ULONG *        pcAdrType,
                                     LPTSTR **      pppAdrTypeArray,
                                     ULONG *        pcMAPIUID,
                                     LPMAPIUID **   pppMAPIUIDArray)
{
    InfoTrace ("CXPLogon::AddressTypes method called");
    CheckParameters_IXPLogon_AddressTypes (this,
                                           pulFlags,
                                           pcAdrType,
                                           pppAdrTypeArray,
                                           pcMAPIUID,
                                           pppMAPIUIDArray);

    // This is how many address type strings we are returning in pppAdrTypeArray
    *pcAdrType = 1;

    // Copy address types back to the MAPI pointer
    gpszXPAddressTypes = &gszWINDSAddressType;
    *pppAdrTypeArray = gpszXPAddressTypes;
    *pulFlags = fMapiUnicode;

    // The UID for routing message has to be set here. If it is not used, set it NULL.
    // In the case of WINDS transport registers support for the UID of
    // the WINDS address book's entry ID
    puidWINDSEntries = &guidABEntries;
    *pcMAPIUID = 1;
    *pppMAPIUIDArray = &puidWINDSEntries;
    return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//    CXPLogon::RegisterOptions()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      This transport does not registers any per-recipient or per-message
//      option processing, so we return 0 options. And NULL in the OPTIONDATA
//      structure pointer.
//
//    Return Value
//      An HRESULT
//
STDMETHODIMP CXPLogon::RegisterOptions (ULONG *         pulFlags,
                                        ULONG *         pcOptions,
                                        LPOPTIONDATA *  ppOptions)
{
    InfoTrace ("CXPLogon::RegisterOptions method called");
    CheckParameters_IXPLogon_RegisterOptions (this,
                                              pulFlags,
                                              pcOptions,
                                              ppOptions);
    *pulFlags = 0;
    *pcOptions = 0;
    *ppOptions = NULL;
    return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//    CXPLogon::TransportNotify()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Update the status row registered by this transport with MAPI
//
//    Return Value
//      An HRESULT
//
STDMETHODIMP CXPLogon::TransportNotify (ULONG * pulFlags, LPVOID * ppvData)
{
    InfoTrace ("CXPLogon::TransportNotify method called");
    CheckParameters_IXPLogon_TransportNotify (this,
                                              pulFlags,
                                              ppvData);

    ULONG ulOldStatus = GetTransportStatusCode();
    // Set appropriate status flags and re-register status row
    if (*pulFlags & NOTIFY_BEGIN_INBOUND)
    {
        InfoTrace ("CXPLogon::TransportNotify: Begin INBOUND logic");
        AddStatusBits (STATUS_INBOUND_ENABLED);
    }
    if (*pulFlags & NOTIFY_END_INBOUND)
    {
        InfoTrace ("CXPLogon::TransportNotify: Terminate INBOUND logic");
        RemoveStatusBits (STATUS_INBOUND_ENABLED);
    }
    if (*pulFlags & NOTIFY_BEGIN_OUTBOUND)
    {
        InfoTrace ("CXPLogon::TransportNotify: Begin OUTBOUND logic");
        AddStatusBits (STATUS_OUTBOUND_ENABLED);
        InitializeTimer();
        StartUploadTimer();
    }
    if (*pulFlags & NOTIFY_END_OUTBOUND)
    {
        InfoTrace ("CXPLogon::TransportNotify: Terminate OUTBOUND logic");
        RemoveStatusBits (STATUS_OUTBOUND_ENABLED);
        StopUploadTimer();
    }
    if (*pulFlags & NOTIFY_BEGIN_OUTBOUND_FLUSH)
    {
        InfoTrace ("CXPLogon::TransportNotify: Begin OUTBOUND flush");
        // If the spooler need to flush us for some reason, we put ourselves
        // in FLUSH and tell the spooler to give us any deferred messages
        // it has queued up for us.
        AddStatusBits (UPLOADING_MESSAGES); // Add these bits to the status code
        SetTransportState (READY);
        m_pSupObj->SpoolerNotify (NOTIFY_SENTDEFERRED, NULL);
    }
    if (*pulFlags & NOTIFY_END_INBOUND_FLUSH)
    {
        InfoTrace ("CXPLogon::TransportNotify: Terminate INBOUND flush");
        if (FALSE == m_List.AreTherePendingDownloads())
        {
            RemoveStatusBits (DOWNLOADING_MESSAGES); // Tell the spooler to take us off from inbound flush
            AddStatusBits (STATUS_OFFLINE); // The transport is now OFF line
            UpdateStatus (TRUE, TRUE);
        }
    }
    if (*pulFlags & NOTIFY_END_OUTBOUND_FLUSH)
    {
        InfoTrace ("CXPLogon::TransportNotify: Terminate OUTBOUND flush");
        if (GetTransportStatusCode() & UPLOADING_MESSAGES)
        {
            // When the spooler finished sending messages to our CXPLogon::SubmitMessage
            // method, he will call us to let us know there is nothing else we need to
            // flush, and we need to reset our status row.
            RemoveStatusBits (UPLOADING_MESSAGES); // Tell the spooler to take us off from outbound flush
            AddStatusBits (STATUS_OFFLINE); // The transport is now OFF line
            if (PENDING_RETURN_CODE != GetTransportState())
            {
                SetTransportState (WAITING);
            }
        }
    }

    // We get called here if user deletes/modifies queued msg in Outbox.
    // If the user modifies and resends it, we get called again at SubmitMessage.
    // If the user closes the message viewer or just saves it, it's removed
    // from the spooler queue and discarded.
    if (*pulFlags & NOTIFY_ABORT_DEFERRED)
    {
        InfoTrace ("CXPLogon::TransportNotify: Abort deferred message");
    }
    if (*pulFlags & NOTIFY_CANCEL_MESSAGE)
    {
        InfoTrace ("CXPLogon::TransportNotify: Cancel message");
    }
    if (ulOldStatus != GetTransportStatusCode())
    {
        UpdateStatus();
    }
    if (*pulFlags & NOTIFY_BEGIN_INBOUND)
    {
        // If we have pending message from a previous session, notify the
        // spooler that we are ready to give them to the store.
        if (m_List.AreTherePendingDownloads())
        {
            // Put ourselves into flush mode and have the spooler call us until
            // we are finished putting the downloaded messages into the default store.
            AddStatusBits (DOWNLOADING_MESSAGES); // Add these bits to the status code
            UpdateStatus();
        }
    }
    return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//    CXPLogon::Idle()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Stub method. We should not get called here, because we told
//      the spooler not to call us here.
//
//    Return Value
//      S_OK always.
//
STDMETHODIMP CXPLogon::Idle (ULONG ulFlags)
{
    InfoTrace ("CXPLogon::Idle method called");
    CheckParameters_IXPLogon_Idle (this, ulFlags);
    return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//    CXPLogon::TransportLogoff()
//
//    Parameters
//      ulFlags     Priority with which the transport should log off
//
//    Purpose
//      This method is called by the spooler when the transport should do final
//      arragements before it gets released.
//
//    Return Value
//      An HRESULT
//
STDMETHODIMP CXPLogon::TransportLogoff (ULONG ulFlags)
{
    InfoTrace ("CXPLogon::TransportLogoff method called");
    CheckParameters_IXPLogon_TransportLogoff (this, ulFlags);
    StopUploadTimer();

    EmptyInboundQueue();

    // We should attempt to remove the transport's status row from
    // the system, but if we fail we won't fail the call.
    HRESULT hResult = m_pSupObj->ModifyStatusRow (0, NULL, 0);
    TraceResult ("CXPLogon::TransportLogoff: Failed to remove status row", hResult);

    if (m_pStatusObj)
    {
        m_pStatusObj->Release();
        m_pStatusObj = NULL;
    }

    return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//    CXPLogon::SubmitMessage()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      This method is called by the spooler when a client submits a
//      message to a recipient whose address type this transport handles.
//      The spooler calls this method twice for each deferred message.
//      The first time (before the delivery time) when the message is
//      submitted by the client, we simply return. The message is then queued
//      by the spooler for later delivery. We keep track of when it's time
//      to send deferred messages.
//
//      The second time we're called, the state variable will be 'READY' and
//      we go ahead and start the actual transmission. While we're in the
//      body of this function, the implied state is 'SENDING'
//
//      If the client logs out of this session, any pending messages get
//      queued again the next time it logs in.
//
//      In this transport we get a recipient table, we restrict the table for
//      unmarked recipients. After the table is ready we invoke a helper
//      method to do the actual transmission.
//
//    Return Value
//      An HRESULT
//
STDMETHODIMP CXPLogon::SubmitMessage (ULONG     ulFlags,
                                      LPMESSAGE pMsgObj,
                                      ULONG *   pulMsgRef,
                                      ULONG *   pulReturnParm)
{
    InfoTrace ("CXPLogon::SubmitMessage method called");
    CheckParameters_IXPLogon_SubmitMessage (this,
                                            ulFlags,
                                            pMsgObj,
                                            pulMsgRef,
                                            pulReturnParm);

    #ifdef _DEBUG
    // Before we get called in SubmitMessage or StartMessage, the spooler should have called
    // us in TransportNotify() to let us know which logic (IN, OUT, BOTH) of the
    // transporting mechanism should be activated for this IXPLogon session.
    if (!(GetTransportStatusCode() & STATUS_OUTBOUND_ENABLED))
    {
        TraceMessage ("CXPLogon::SubmitMessage: We can't send a message if the outbound is not enabled");
        ASSERTMSG (FALSE, "We can't submit a message if we have not started OUTBOUND logic");
        return MAPI_E_NOT_ME;
    }
    #endif // _DEBUG

    // Lock the object against the timer thread re-entrancy. Timer events are handle
    // in a separate thread. This section will get unlocked in the CPXLogon::EndMessage() call
    if (WAITING == GetTransportState())
    {
        // Not scheduled upload time, return and let IXPLogon::EndMessage() defer the message
        InfoTrace ("CXPLogon::SubmitMessage: Deferring message for scheduled submission");
        return S_OK;
    }
    InfoTrace ("CXPLogon::SubmitMessage: Processing deferred message");

    CheckSpoolerYield (TRUE);

    // Notify the MAPI spooler the transport is going to flush any queued up messages and submit them.
    // Transport to used shared resources, such as COM ports, should put them selves into flush mode
    // when submitting a batch of messages. This gives the transport the advantage of locking shared
    // resources across submitted messages and ensures that the spooler does not call other
    // transports while another is flushing because it could have something locked.
    // This transport does not uses any shared resources that we would need to lock, but for the
    // purposes of demonstration, we put our selves into flush mode until the MAPI spooler
    // tells us to step down.
    if (!(GetTransportStatusCode() & UPLOADING_MESSAGES))
    {
        AddStatusBits (UPLOADING_MESSAGES);
        UpdateStatus();
    }

    // Get the recipient table from the message
    LPMAPITABLE pTable = NULL;
    HRESULT hResult = pMsgObj->GetRecipientTable (fMapiUnicode, &pTable);
    if (hResult)
    {
        TraceResult ("CXPLogon::SubmitMessage: Failed to get the recipient table", hResult);
        goto ErrorExit;
    }

    // The spooler marks all the message recipients this transport has to
    // handle with PR_RESPONSIBILITY set to FALSE
    SPropValue spvRecipUnsent;
    spvRecipUnsent.ulPropTag                       = PR_RESPONSIBILITY;
    spvRecipUnsent.Value.b                         = FALSE;

    SRestriction srRecipientUnhandled;
    srRecipientUnhandled.rt                        = RES_PROPERTY;
    srRecipientUnhandled.res.resProperty.relop     = RELOP_EQ;
    srRecipientUnhandled.res.resProperty.ulPropTag = PR_RESPONSIBILITY;
    srRecipientUnhandled.res.resProperty.lpProp    = &spvRecipUnsent;

    hResult = pTable->Restrict (&srRecipientUnhandled, 0L);
    if (hResult)
    {
        TraceResult ("CXPLogon::SubmitMessage: Failed to restrict the recipient table", hResult);
        goto ErrorExit;
    }

    // Let the MAPI spooler do other things
    CheckSpoolerYield();

    hResult = HrAddColumns (pTable,
                            (LPSPropTagArray)&sptRecipTable,
                            gpfnAllocateBuffer,
                            gpfnFreeBuffer);
    if (hResult)
    {
        TraceResult ("CXPLogon::SubmitMessage: Failed to expand the columns in the recipient table", hResult);
        goto ErrorExit;
    }

    LPSRowSet pRecipRows;
    hResult = HrQueryAllRows (pTable,
                              NULL,
                              NULL,
                              NULL,
                              0,
                              &pRecipRows);
    if (!hResult)
    {
        // Let the MAPI spooler do other things
        CheckSpoolerYield();
        // Send to the recipients which we can reach, and generate NDR's for the ones we can't
        hResult = SendMailMessage (pMsgObj, pRecipRows);
        FreeProws (pRecipRows);
        if (!hResult)
        {
            // Now we need to save changes on the message and close it.
            // After this, the message object can't be used.
            hResult = pMsgObj->SaveChanges (0);
            TraceResult ("CXPLogon::SubmitMessage: Failed to save the message object", hResult);
        }
    }

ErrorExit:
     // Release the table, we're finished with it
    if (pTable)
    {
        pTable->Release();
    }

    // Release the spooler's message if needed to
    if (pMsgObj)
    {
        pMsgObj->Release ();
    }

    // In case there is a warning or error floating around, don't let it escape to the spooler.
    if (FAILED(hResult))
    {
        // We default to MAPI_E_NOT_ME so that the spooler would attempt handle
        // the message to other transport (currently running in this profile)
        // that handle the same address type as ours.
        TraceMessage ("CXPLogon::SubmitMessage: An error occurred in the submission, returning MAPI_E_NOT_ME");
        hResult = MAPI_E_NOT_ME;
    }
    else
    {
        hResult = S_OK;
    }
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    CXPLogon::EndMessage()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      This method is called by the spooler for each message we're to
//      deliver. It's the mate to SubmitMessage. We're called here twice
//      for each deferred message and once for non-deferred (realtime)
//      messages.
//
//      We first check the transport state, and if we're
//      WAITING for the scheduled delivery time to arrive, we return
//      END_DONT_RESEND in *pulFlags, which tells the spooler to queue this
//      message for deferred delivery.
//
//      If the state is SENDING, we're getting called here after
//      a message has been dequeued and delivered. Return 0 in *pulFlags
//      to tell the spooler the message has been delivered.
//
//    Return Value
//      An HRESULT
//
STDMETHODIMP CXPLogon::EndMessage (ULONG ulMsgRef, ULONG * pulFlags)
{
    InfoTrace ("CXPLogon::EndMessage method called");
    CheckParameters_IXPLogon_EndMessage (this, ulMsgRef, pulFlags);

    if (WAITING == GetTransportState())
    {
        // Tell spooler to queue msg for deferred delivery
        *pulFlags = END_DONT_RESEND;
    }
    else
    {
        *pulFlags = 0;
    }
    return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//    CXPLogon::Poll()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Stub method. We should not get called here, because we told
//      the spooler not to call us here.
//
//    Return Value
//      An HRESULT
//
STDMETHODIMP CXPLogon::Poll (ULONG * pulIncoming)
{
    InfoTrace ("CXPLogon::Poll method called");
    CheckParameters_IXPLogon_Poll (this, pulIncoming);
    return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//    CXPLogon::StartMessage()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      This method gets called when an incoming message is pending to be
//      processed.
//
//    Return Value
//      An HRESULT
//
STDMETHODIMP CXPLogon::StartMessage (ULONG      ulFlags,
                                     LPMESSAGE  pMsgObj,
                                     ULONG *    pulMsgRef)
{
    InfoTrace ("CXPLogon::StartMessage method called");
    CheckParameters_IXPLogon_StartMessage (this, ulFlags, pMsgObj, pulMsgRef);

    // Initialize the pseudo-timer for the SpoolerYield() call
    CheckSpoolerYield (TRUE);

    HRESULT hResult = S_OK;
    LPSTREAM pFileStream = NULL;
    CCachedStream * pStream = NULL;
    LPITNEF pTNEFObj = NULL;
    SPropTagArray sptExcludedProps = { 0 };

    PLIST_NODE pNode = m_List.GetDownloadNode();
    if (!pNode)
    {
        RemoveStatusBits (DOWNLOADING_MESSAGES); // Remove these bits from the status code
        UpdateStatus();
        if (READY == GetTransportState())
        {
            SetTransportState (WAITING);
        }
        goto ErrorExit;
    }
    // Close the file so that we may open it in the call below
    if (pNode->hFile)
    {
        CloseHandle (pNode->hFile);
        // NULL the handle to avoid closing the file again during cleanup.
        pNode->hFile = NULL;
    }
    // Open the stream where the message properties are.
    hResult = OpenStreamOnFile (gpfnAllocateBuffer,
                                gpfnFreeBuffer,
                                STGM_READ,
                                pNode->szFileName,
                                NULL,
                                &pFileStream);
    if (hResult)
    {
        TraceResult ("CXPLogon::StartMessage: Failed to open stream on the message file", hResult);
        goto ErrorExit;
    }
    try
    {
        // Create a buffer IStream interface for the TNEF decoding
        pStream = new CCachedStream (pFileStream, XPSOF_READ);
        if (!pStream)
        {
            TraceMessage ("CXPLogon::StartMessage: Failed to allocate cached stream object");
            hResult = E_OUTOFMEMORY;
        }
    }
    catch (CException & Exception)
    {
        hResult = Exception.GetError();
    }
    pFileStream->Release();
    pFileStream = NULL;
    if (hResult)
    {
        goto ErrorExit;
    }
    hResult = OpenTnefStream (m_pSupObj,
                              pStream,
                              TNEF_FILE_NAME,
                              TNEF_DECODE,
                              pMsgObj,
                              0,    // Not needed when decoding TNEF
                              &pTNEFObj);
    if (hResult)
    {
        TraceResult ("CXPLogon::StartMessage: Failed to open TNEF stream object", hResult);
        goto ErrorExit;
    }

    // Let the MAPI spooler do other things
    CheckSpoolerYield();

    // Get the properties for the message which are encoded in the TNEF
    // message stream. The sptExcludedProps argument, is just a stub,
    // we are not excluding any properties
    LPSTnefProblemArray pProblems;
    pProblems = NULL;
    hResult = pTNEFObj->ExtractProps (TNEF_PROP_EXCLUDE, &sptExcludedProps, &pProblems);
    if (pProblems)
    {
        gpfnFreeBuffer (pProblems);
        pProblems = NULL;
    }
    if (hResult)
    {
        TraceResult ("CXPLogon::StartMessage: Failed to open TNEF stream", hResult);
        goto ErrorExit;
    }
    if (MAPI_E_CORRUPT_DATA == SetIncomingProps (pMsgObj, pNode))
    {
        pNode = NULL; // To avoid deleting it below.
    }

    // Save all chages and new properties, back on the message
    // Don't release the message object. The spooler is still using it.
    // After this, the message object can't be used by this transport.
    hResult = pMsgObj->SaveChanges (0);
    TraceResult ("CXPLogon::StartMessage: Failed to save the message object", hResult);

    // Let the MAPI spooler do other things
    CheckSpoolerYield();

ErrorExit:
    // Release used objects
    if (pTNEFObj)
    {
        pTNEFObj->Release();
    }
    if (pStream)
    {
        pStream->Release();
    }
    if (pNode)
    {
        if (pNode->hFile)
        {
            CloseHandle (pNode->hFile);
        }
        // Delete the file ONLY if the we were successful putting the
        // file data into the message. Otherwise leave the file in
        // the directory, and it will be picked up later
        if (S_OK == hResult)
        {
            DeleteFile (pNode->szFileName);
        }
        delete pNode;
    }
    m_List.UpdateProgress();
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    CXPLogon::OpenStatusEntry()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      This method is called to get an IMAPIStatus object for this XPLOGON
//      session.
//
//    Return Value
//      An HRESULT
//
STDMETHODIMP CXPLogon::OpenStatusEntry (LPCIID          pInterface,
                                        ULONG           ulFlags,
                                        ULONG *         pulObjType,
                                        LPMAPISTATUS *  ppEntry)
{
    InfoTrace ("CXPLogon::OpenStatusEntry method called");
    CheckParameters_IXPLogon_OpenStatusEntry (this,
                                              pInterface,
                                              ulFlags,
                                              pulObjType,
                                              ppEntry);
    if (MAPI_MODIFY & ulFlags)
    {
        TraceMessage ("CXPLogon::OpenStatusEntry: We don't support WRITE access to the status object");
        return E_ACCESSDENIED;
    }

    HRESULT hResult = S_OK;
    // Now, if we already have created a status object on this logon context,
    // we'll just use QueryInterface to get a new copy (AddRef() it) of the object
    if (!m_pStatusObj)
    {
        // Get the profile section of the PROVIDER so that we may get some properties,
        // assigned by MAPI to this provider, directly on the status object.
        LPPROFSECT pProfileObj = NULL;
        m_pSupObj->OpenProfileSection (NULL, 0, &pProfileObj);
        // If we don't have an object, create it, and save a copy in the logon object
        m_pStatusObj = new CMAPIStatus (this, pProfileObj);
        if (!m_pStatusObj)
        {
            TraceMessage ("CXPLogon::OpenStatusEntry: Could not allocate new CMAPIStatus object");
            hResult = E_OUTOFMEMORY;
        }
        // The constructor of CMAPIStatus AddRef()'ed this object
        if (pProfileObj)
        {
            pProfileObj->Release();
        }
    }
    if (!hResult)
    {
        // The transport will return *ppEntry == NULL or a pointer to the new memory allocated
        m_pStatusObj->AddRef();
        *ppEntry = m_pStatusObj;
        *pulObjType = MAPI_STATUS;
    }
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    CXPLogon::ValidateState()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      This function gets caller by a client in order to validate the
//      transport logon properties. This function open the profile with the
//      most up-to-date properties and then compares them to what the transport
//      has stored internally
//
//    Return Value
//      An HRESULT
//
STDMETHODIMP CXPLogon::ValidateState (ULONG ulUIParam, ULONG ulFlags)
{
    InfoTrace ("CXPLogon::ValidateState method called");
    CheckParameters_IXPLogon_ValidateState (this,
                                            ulUIParam,
                                            ulFlags);

    // Try to open the transport profile section
    LPPROFSECT pProfileObj;
    HRESULT hResult = OpenServiceProfileSection (m_pSupObj, &pProfileObj, gpfnFreeBuffer);
    if (hResult)
    {
        return hResult;
    }

    LPSPropValue pProps = NULL;
    ULONG ulPropCount;
    // Read the properties stored in the profile of this user
    hResult = pProfileObj->GetProps ((LPSPropTagArray)&sptLogonProps,
                                     fMapiUnicode,
                                     &ulPropCount,
                                     &pProps);
    TraceResult ("CXPLogon::ValidateState: Failed to get profile properties", hResult);
    if (!hResult)
    {
        // Now, compare what the transport thinks the information in the profile is
        // to the real data. If they are different, tell the spooler the transport
        // would like to be reloaded
        if (lstrcmp (m_UserInfo.szMailboxName, pProps[MAILBOX_NAME].Value.LPSZ)||
            lstrcmp (m_UserInfo.szPassword, pProps[PASSWORD].Value.LPSZ) ||
            lstrcmp (m_UserInfo.szFullName, pProps[USER_NAME].Value.LPSZ) ||
            lstrcmpi (m_szServer, pProps[SERVER_NAME].Value.LPSZ))
        {
            hResult = m_pSupObj->SpoolerNotify (NOTIFY_CONFIG_CHANGE, NULL);
            TraceResult ("CXPLogon::ValidateState: Failed to notify the spooler", hResult);
        }
    }
    pProfileObj->Release();
    gpfnFreeBuffer (pProps);
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    CXPLogon::FlushQueues()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Called by the MAPI spooler when, upon request of the client or
//      ourselves, we need to flush the inbound or outbound queue.
//      Here we make connections to the server to download messages, refresh
//      the remote message headers, and request the spooler to send us any
//      deferred messages.
//      Transport connecting only in FlushQueues() allow the MAPI spooler to
//      better manage contention of multiple transport accessing common
//      communication resources (such as COM ports) and let the spooler give us
//      messages to process when is best for the overall subsystem.
//
//    Return Value
//      An HRESULT
//
STDMETHODIMP CXPLogon::FlushQueues (ULONG       ulUIParam,
                                    ULONG       cbTargetTransport,
                                    LPENTRYID   pTargetTransport,
                                    ULONG       ulFlags)
{
    InfoTrace ("CXPLogon::FlushQueues method called");
    CheckParameters_IXPLogon_FlushQueues (this,
                                          ulUIParam,
                                          cbTargetTransport,
                                          pTargetTransport,
                                          ulFlags);

    HRESULT hResult = S_OK;
    // Update status flags and then update update the transport status rows
    if (ulFlags & FLUSH_UPLOAD)
    {
        // If the remote server is offline, the transport is not going to send the deferred messages
        if (TRUE == IsWINDSServerAvailable (m_szServer))
        {
            // If we are already in delivery mode submitted messages will not get deferred,
            // so don't bother the spooler asking for deferred messages.
            if (READY != GetTransportState())
            {
                // Guard against re-entrancy from the timer call back which happens on a separate thread
                if (PROCESSING_TIMER_EVENT != GetTransportState())
                {
                    SetTransportState (READY);
                }
                // We pass NULL for the entry ID so that the spooler would resend ALL the
                // deferred messages. Transport may pass individual entry IDs for specific messages.
                hResult = m_pSupObj->SpoolerNotify (NOTIFY_SENTDEFERRED, NULL);
            }
        }
    }
    if (ulFlags & FLUSH_DOWNLOAD)
    {
        if (HEADERS_AND_DOWNLOAD == GetTransportState())
        {
            m_hRemoteActionErr = ProcessHeaders();
            if (!m_hRemoteActionErr && !m_fCancelPending)
            {
                m_pSupObj->SpoolerYield (0);
                if (m_List.AreTherePendingDownloads())
                {
                    // Put ourselves into flush mode and have the spooler call us until
                    // we are finished putting the downloaded messages into the default store.
                    AddStatusBits (DOWNLOADING_MESSAGES); // Add these bits to the status code
                }
                if (!m_fCancelPending)
                {
                    // Upload any deferred messages the spooler has for our transport
                    if (IsWINDSServerAvailable (m_szServer))
                    {
                        m_pSupObj->SpoolerNotify (NOTIFY_SENTDEFERRED, NULL);
                    }
                    if (!m_fCancelPending)
                    {
                        m_hRemoteActionErr = DownloadMessageHeaders();
                        if (!m_hRemoteActionErr && !(GetTransportStatusCode() & DOWNLOADING_MESSAGES))
                        {
                            RemoveStatusBits (STATUS_INBOUND_FLUSH);
                            UpdateStatus (TRUE, TRUE);
                            m_pSupObj->SpoolerYield (0);
                        }
                    }
                }
            }
            SetTransportState (PENDING_RETURN_CODE);
            AddStatusBits (STATUS_OFFLINE);
            if (m_hRemoteActionErr)
            {
                RemoveStatusBits (STATUS_INBOUND_FLUSH);
                UpdateStatus (TRUE, TRUE);
            }
            else
            {
                if (m_fCancelPending)
                {
                    UpdateStatus (TRUE, TRUE);
                }
                else
                {
                    UpdateStatus();
                }
            }
        }
        else
        {
            if (PROCESSING_TIMER_EVENT == GetTransportState())
            {
                if (m_fGetHeaders)
                {
                    RemoveStatusBits (STATUS_OFFLINE);
                    UpdateStatus();
                    DownloadMessageHeaders();
                    AddStatusBits (STATUS_OFFLINE);
                    UpdateStatus();
                }
            }
            else
            {
                if (m_List.AreTherePendingDownloads())
                {
                    // Put ourselves into flush mode and have the spooler call us until
                    // we are finished putting the downloaded messages into the default store.
                    AddStatusBits (DOWNLOADING_MESSAGES); // Add these bits to the status code
                    UpdateStatus();
                }
            }
        }
    }
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    CXPLogon::ProcessHeaders()
//
//    Parameters
//      None.
//
//    Purpose
//      This method is called from the status object's ValidateState when
//      it's passed PROCESS_XP_HEADER_CACHE. It starts the download processing.
//      First we get the header folder contents table and restrict it to rows
//      where PR_MSG_STATUS is >= MSGSTATUS_REMOTE_DOWNLOAD. These are rows
//      for messages that have the MSGSTATUS_REMOTE_DOWNLOAD, or
//      MSGSTATUS_REMOTE_DELETE, or both, bits set.
//
//      We then connect to the server to obtain the download named pipe and
//      start the download.
//
//    Return Value
//      An HRESULT
//
STDMETHODIMP CXPLogon::ProcessHeaders()
{
    // If we don't have a folder in the status object or the folder doesn't
    // have an initialized contents table, there is nothing to do.
    if (!m_pStatusObj->m_pHeaderFolder || !m_pStatusObj->m_pHeaderFolder->m_pTableData)
    {
        return S_OK;
    }

    // Get headers folder contents table, some are marked for download
    LPMAPITABLE pTable;
    HRESULT hResult = m_pStatusObj->m_pHeaderFolder->m_pTableData->HrGetView (NULL, NULL, 0, &pTable);
    if (hResult)
    {
        TraceResult ("CXPLogon::ProcessHeaders: Failed to get a view on the contents table", hResult);
        return hResult;
    }

    // we only want rows marked for download, form restriction
    SPropValue spvFilter = { 0 };
    spvFilter.ulPropTag = PR_MSG_STATUS;
    spvFilter.Value.l = MSGSTATUS_REMOTE_DOWNLOAD;

    // This restriction relies in the current values of the flags in PR_MSG_STATUS
    SRestriction srStatus = { 0 };
    srStatus.rt = RES_PROPERTY;
    srStatus.res.resProperty.relop = RELOP_GE;
    srStatus.res.resProperty.ulPropTag = PR_MSG_STATUS;
    srStatus.res.resProperty.lpProp = &spvFilter;

    hResult = pTable->Restrict (&srStatus, 0);
    if (hResult)
    {
        // This is a non-fatal error (i.e. the implementation does not support restrictions)
        TraceResult ("CXPLogon::ProcessHeaders: Failed to restrict the table", hResult);
    }
    ULONG ulRowCount;
    // Providers and client should not, when ever possible, use IMAPITable::GetRowCount()
    // because depending on the implementation of the table, the returned count by not
    // be exact.
    // We use it here for convenience knowing the fact the MAPI's ITableData implementation
    // returns and EXACT count of the rows in the memory table.
    hResult = pTable->GetRowCount (0, &ulRowCount);
    if (hResult)
    {
        goto ErrorExit;
    }
    // Nothing to do.
    if (0 == ulRowCount)
    {
        goto ErrorExit;
    }
    else
    {
        // Make sure our download directory is around.
        TCHAR szTmpDir[_MAX_PATH], szDownloadDir[_MAX_PATH];
        GetTempPath (_MAX_PATH, szTmpDir);
        lstrcat (szTmpDir, WINDS_DATA_DIRECTORY);
        wsprintf (szDownloadDir, WINDS_DOWNLOAD_DIR_NAME_FORMAT, szTmpDir, m_UserInfo.szMailboxName);
        CreateDirectory (szDownloadDir, NULL);
    }

    // Initialize the progress property in the status row of this transport.
    UpdateProgress (0, REMOTE_ACTION_DOWNLOADING_MSGS);

    // Make a call to the remote server to open the connection
    HANDLE hPipe;
    hResult = OpenRemoteServerDownLoadPipe (m_szServer, m_UserInfo.szMailboxName, &hPipe);
    if (hResult)
    {
        goto ErrorExit;
    }
    // Do the actual download transmission now.
    hResult = m_List.DownLoadMsgs (pTable, ulRowCount, hPipe);
    CloseHandle (hPipe);

    TerminateRemoteConnections();

ErrorExit:
    TraceResult ("CXPLogon::ProcessHeaders", hResult);
    pTable->Release();
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    CXPLogon::UpdateProgress()
//
//    Parameters
//      lPercentComplete    Percent completion of download
//      raFlag              Flag that indicate to what remote action the
//                          update is tied to, so that we may properly
//                          update PR_REMOTE_PROGRESS_TEXT.
//
//    Purpose
//      Sets the status row property PR_REMOTE_PROGRESS with a number from
//      0-100. In example, if 10 messages are queued and 5 have been
//      downloaded, lPercentComplete will be 50, regardless of individual
//      messages' sizes.
//
//    Return Value
//      None.
//
void WINAPI CXPLogon::UpdateProgress (long          lPercentComplete,
                                      REMOTE_ACTION raFlag)
{
    SPropValue spProgress[2] = { 0 };
    ULONG cProps = 1;
    TCHAR szRemoteProgress[64] = { 0 };
    spProgress[0].ulPropTag = PR_REMOTE_PROGRESS;
    spProgress[0].Value.l = lPercentComplete;
    if (raFlag != m_raAction)
    {
        spProgress[1].ulPropTag = PR_REMOTE_PROGRESS_TEXT;
        spProgress[1].Value.LPSZ = szRemoteProgress;
        DWORD idString;
        m_raAction = raFlag;
        switch (raFlag)
        {
            case REMOTE_ACTION_DOWNLOADING_MSGS :
                idString = IDS_REMOTE_DOWNLOADING;
                break;
            case REMOTE_ACTION_PROCESSING_MSGS :
                idString = IDS_REMOTE_PROCESSING_MSGS;
                break;
            case REMOTE_ACTION_HEADER_REFRESH :
                idString = IDS_REMOTE_REFRESHING_HEADERS;
                break;
            case REMOTE_ACTION_IDLE :
                idString = 0;
                break;
        }
        if (idString)
        {
            LoadString (m_hInstance, idString, szRemoteProgress, 64);
        }
        cProps++;
    }

    HRESULT hResult = m_pSupObj->ModifyStatusRow (cProps, spProgress, STATUSROW_UPDATE);
    TraceResult ("CXPLogon::UpdateProgress: Failed to modify the status row", hResult);
}

///////////////////////////////////////////////////////////////////////////////
//    CXPLogon::LoadStatusString()
//
//    Parameters
//      pString         Pointer to a string which will hold the status string
//      uStringSize     Maximum number of characters allowed in the string
//
//    Purpose
//      Loads a string from the transport's stringtable. This method is called
//      by the CXPLogon::UpdateStatus method when updating a status row. This
//      method loads the string based on the status bits of the transport
//      status code
//
//    Return Value
//      TRUE            If the string was found in the string table.
//      FALSE           The string was not found. The String indicated by
//                      pString is set to hold 0 characters
//
BOOL WINAPI CXPLogon::LoadStatusString (LPTSTR pString, UINT uStringSize)
{
    UINT uStringID;
    DWORD dwStatusCode = GetTransportStatusCode();
    if (dwStatusCode & (DOWNLOADING_MESSAGES | UPLOADING_MESSAGES))
    {
        uStringID = IDS_XP_STATUS_TIMER_EVENT;
    }
    else
    {
        if (dwStatusCode & DOWNLOADING_MESSAGES)
        {
            if (dwStatusCode & STATUS_OFFLINE)
            {
                uStringID = IDS_XP_STATUS_FLUSHING_INBOUND;
            }
            else
            {
                uStringID = IDS_XP_STATUS_INBOUND_AND_HEADERS;
            }
        }
        else
        {
            if (dwStatusCode & UPLOADING_MESSAGES)
            {
                uStringID = IDS_XP_STATUS_FLUSHING_OUTBOUND;
            }
            else
            {
                if (dwStatusCode & STATUS_INBOUND_ENABLED &&
                    dwStatusCode & STATUS_OUTBOUND_ENABLED)
                {
                    uStringID = IDS_XP_STATUS_READY;
                }
                else
                {
                    uStringID = IDS_XP_STATUS_AVAILABLE;
                }
            }
        }
    }
    if (LoadString (m_hInstance, uStringID, pString, uStringSize))
    {
        return TRUE;
    }
    pString[0] = '\0';
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//    CXPLogon::MakeSearchKey()
//
//    Parameters
//      pParentMemBlock     Pointer the a block of memory allocated with the
//                          MAPI Mem. alloc. functions.
//      pszAddress          String with the actual mail address
//      pcbSearchKey        Pointer to a ULONG which returns the size
//                          (in bytes) of the newly created search key
//      ppSearchKey         Pointer to an array ob BYTES
//
//    Purpose
//      Returns a MAPI search key of the form TYPE:ADDRESS in upper case.
//      The string is allocated with the MAPI Mem Alloc functions and linked
//      to the block of memory indicated by pParentMemBlock
//
//    Return Value
//      An HRESULT
//
STDMETHODIMP CXPLogon::MakeSearchKey (LPVOID        pParentMemBlock,
                                      LPTSTR        pszAddress,
                                      ULONG *       pcbSearchKey,
                                      LPBYTE *      ppSearchKey)
{
    LPTSTR pszSearchKey;
    // The 2 is for the COLON and the NULL terminator
    ULONG cbStrSize = sizeof (TCHAR) * (2 + lstrlen (WINDS_ADDRESS_TYPE) + lstrlen (pszAddress));
    HRESULT hResult = gpfnAllocateMore (cbStrSize, pParentMemBlock, (LPVOID *)&pszSearchKey);
    TraceResult ("CXPLogon::MakeSearchKey: Failed to allocate search key string", hResult);
    if (!hResult)
    {
        // We need to convert the address to upper case
        wsprintf (pszSearchKey, TEXT("%s:%s"), WINDS_ADDRESS_TYPE, pszAddress);
        CharUpper (pszSearchKey);
        *pcbSearchKey = cbStrSize;
        *ppSearchKey = (LPBYTE)pszSearchKey;
    }
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    CXPLogon::UpdateStatus()
//
//    Parameters
//      fAddValidate
//      fValidateOkState
//
//    Purpose
//      Updates the transport status row of this transport in the MAPI Mail
//      subsystem. Updates the flags according the internal state flags
//      maintained in status code of the transport and loads a readable status
//      string to reset the status row. The caller of this method should update
//      the status code member variable prior to calling UpdateStatus()
//
//    Return Value
//      None
//
void WINAPI CXPLogon::UpdateStatus (BOOL fAddValidate, BOOL fValidateOkState)
{
    ULONG cProps = 1;
    SPropValue rgProps[3] = { 0 };
    //  Store the new Transport Provider Status Code
    rgProps[0].ulPropTag = PR_STATUS_CODE;
    rgProps[0].Value.l = GetTransportStatusCode();

    TCHAR szStatus[64];
    if  (LoadStatusString (szStatus, sizeof(szStatus) - 1 ))
    {
        rgProps[1].ulPropTag = PR_STATUS_STRING;
        rgProps[1].Value.LPSZ = szStatus;
        cProps++;
    }
    if (fAddValidate)
    {
        ULONG index;
        if (2 == cProps)
        {
            index = 2;
        }
        else
        {
            index = 1;
        }
        rgProps[index].ulPropTag = PR_REMOTE_VALIDATE_OK;
        rgProps[index].Value.b = fValidateOkState;
        cProps++;
    }
    //  OK. Notify the messaging subsystem of state changes in this transport.
    HRESULT hResult = m_pSupObj->ModifyStatusRow (cProps, rgProps, STATUSROW_UPDATE);
    TraceResult ("CXPLogon::UpdateStatus: ModifyStatusRow failed", hResult);
}

///////////////////////////////////////////////////////////////////////////////
//    CXPLogon::InitializeTransportStatusFlags()
//
//    Parameters
//      ulFlags     Flags passed in to initialize the transport status flags.
//
//    Purpose
//      Initialize the transport status flags with the flags passed in by the
//      MAPI spooler. This method gets called when initializing a CXPLogon
//      object in the CXPProvider::TransportLogon method.
//
//    Return Value
//      None
//
void WINAPI CXPLogon::InitializeTransportStatusFlags (ULONG ulFlags)
{
    AddStatusBits (STATUS_AVAILABLE | STATUS_OFFLINE | STATUS_REMOTE_ACCESS);
    if (!(ulFlags & LOGON_NO_INBOUND))
    {
        AddStatusBits (STATUS_INBOUND_ENABLED);
    }
    if (!(ulFlags & LOGON_NO_OUTBOUND))
    {
        AddStatusBits (STATUS_OUTBOUND_ENABLED);
    }
}

///////////////////////////////////////////////////////////////////////////////
//    CXPLogon::SetIdentityProps()
//
//    Parameters
//      None
//
//    Purpose
//      Initializes the transport ID array with the properties found in the
//      profile for the user.
//      If the ABWDS address book is installed, we open an entry in it to
//      supply the identity properties.
//
//    Return Value
//      An HRESULT
//
STDMETHODIMP CXPLogon::SetIdentityProps()
{
    // Allocate the property array for transport. This memory block is freed
    // in the destructor of the CXPLogon object
    HRESULT hResult = gpfnAllocateBuffer (sizeof(SPropValue)*NUM_IDENTITY_PROPS, (LPVOID *)&m_pIdentityProps);
    if (hResult)
    {
        TraceResult ("CXPLogon::SetIdentityProps: Failed to allocate property array", hResult);
        return hResult;
    }
    LPMAILUSER pUser;
    ULONG ulObjType;
    TCHAR szSearchKey[128];
    LPTSTR pStr;
    // Try to open out entry ID in the ABWDS address book (see if it is around)
    // If the call fails, we must create a one-off for our identity.
    hResult = m_pSupObj->OpenEntry (CB_PRIVATE_EID,
                                    (LPENTRYID)&m_UserEID,
                                    NULL,
                                    0,
                                    &ulObjType,
                                    (LPUNKNOWN *)&pUser);
    if (S_OK == hResult)
    {
        ASSERTMSG (MAPI_MAILUSER == ulObjType, "What kind object is this?");

        // Looks like ABWDS is around, mark the internal flag.
        // ABWDS is the native WINDS address book service provider. If present,
        // instead of creating a one-off entry for the transport identity, we
        // will simply open an entry in the WINDS address book and get the
        // necessary properties out from it.
        m_fABWDSInstalled = TRUE;

        m_pIdentityProps[XPID_NAME].ulPropTag = PR_SENDER_NAME;
        m_pIdentityProps[XPID_NAME].Value.LPSZ = m_UserInfo.szFullName;
        m_pIdentityProps[XPID_EID].ulPropTag = PR_SENDER_ENTRYID;
        m_pIdentityProps[XPID_EID].Value.bin.cb = CB_PRIVATE_EID;
        m_pIdentityProps[XPID_EID].Value.bin.lpb = (LPBYTE)&m_UserEID;
        wsprintf (szSearchKey,
                  TEXT("%s:%s\\%s"),
                  WINDS_ADDRESS_TYPE,
                  m_szServer,       // this is already in the format "\\<servername>"
                  m_UserInfo.szMailboxName);
        CharUpper (szSearchKey);
        hResult = gpfnAllocateMore (Cbtszsize(szSearchKey), m_pIdentityProps, (LPVOID *)&pStr);
        if (hResult)
        {
            TraceResult ("CXPLogon::SetIdentityProps: Failed to allocate string for native search key", hResult);
            m_pIdentityProps[XPID_SEARCH_KEY].ulPropTag = PROP_TAG (PT_ERROR, PROP_ID (PR_SENDER_SEARCH_KEY));
        }
        else
        {
            lstrcpy (pStr, szSearchKey);
            m_pIdentityProps[XPID_SEARCH_KEY].ulPropTag = PR_SENDER_SEARCH_KEY;
            m_pIdentityProps[XPID_SEARCH_KEY].Value.bin.cb = Cbtszsize(pStr);
            m_pIdentityProps[XPID_SEARCH_KEY].Value.bin.lpb = (LPBYTE)pStr;
        }
        pUser->Release();
        return hResult;
    }

    ///////////////////////////////////////////////////////////////////////////
    // Set the PR_SENDER_ENTRYID property. Create an entry for the user and
    // set it in the property array
    m_pIdentityProps[XPID_EID].ulPropTag = PR_SENDER_ENTRYID;
    LPBYTE lpeid = NULL;
    ULONG  cbeid = 0;
    hResult = m_pSupObj->CreateOneOff (m_UserInfo.szFullName,
                                       WINDS_ADDRESS_TYPE,
                                       m_szAddress,
                                       fMapiUnicode,
                                       &cbeid,
                                       (LPENTRYID *)&lpeid);
 if (hResult)
    {
        TraceResult ("CXPLogon::SetIdentityProps: Failed to create a one off identity", hResult);
        m_pIdentityProps[XPID_EID].ulPropTag = PROP_TAG (PT_ERROR, PROP_ID (PR_SENDER_ENTRYID));
        return hResult;
    }

    hResult = gpfnAllocateMore(cbeid, m_pIdentityProps,
                            (LPVOID *)&m_pIdentityProps[XPID_EID].Value.bin.lpb);
    if(hResult)
    {
        TraceResult ("CXPLogon::SetIdentityProps: Failed to allocate memory", hResult);
        m_pIdentityProps[XPID_EID].ulPropTag = PROP_TAG (PT_ERROR, PROP_ID (PR_SENDER_ENTRYID));
        gpfnFreeBuffer(lpeid);
        lpeid = NULL;
        return hResult;
    }

    m_pIdentityProps[XPID_EID].Value.bin.cb = cbeid;
    CopyMemory(m_pIdentityProps[XPID_EID].Value.bin.lpb, lpeid, cbeid);

    gpfnFreeBuffer(lpeid);
    lpeid = NULL;

    //////////////////////////////////////////////////////////////////////////
    // Set the PR_SENDER_NAME property
    m_pIdentityProps[XPID_NAME].ulPropTag = PR_SENDER_NAME;
    LPTSTR pStr1, pStr2 = m_UserInfo.szFullName;
    hResult = gpfnAllocateMore (Cbtszsize(pStr2), m_pIdentityProps, (LPVOID *)&pStr1);
    if (hResult)
    {
        TraceResult ("CXPLogon::SetIdentityProps: Memory allocation failed for display name string", hResult);
        m_pIdentityProps[XPID_NAME].ulPropTag = PROP_TAG (PT_ERROR, PROP_ID (PR_SENDER_NAME));
        return hResult;
    }
    lstrcpy (pStr1, pStr2);
    m_pIdentityProps[XPID_NAME].Value.LPSZ = pStr1;

    //////////////////////////////////////////////////////////////////////////
    // Set the PR_SENDER_SEARCH_KEY property
    m_pIdentityProps[XPID_SEARCH_KEY].ulPropTag = PR_SENDER_SEARCH_KEY;
    // First, create the search key
    hResult = MakeSearchKey (m_pIdentityProps,
                             m_szAddress,
                             &m_pIdentityProps[XPID_SEARCH_KEY].Value.bin.cb,
                             &m_pIdentityProps[XPID_SEARCH_KEY].Value.bin.lpb);
    if (hResult)
    {
        m_pIdentityProps[XPID_SEARCH_KEY].ulPropTag = PROP_TAG (PT_ERROR, PROP_ID (PR_SENDER_SEARCH_KEY));
    }
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    CXPLogon::SetSessionFlags()
//
//    Parameters
//      [IN, OUT]   pulFlags    Flags returned to caller
//
//    Purpose
//      To set the flags we will return to the spooler during the CXPLogon
//      initialization in the CXPProvider::TransportLogon method. The ulFlags
//      parameter is filled as a return value to the caller
//
//    Return Value
//      None
//
void WINAPI CXPLogon::SetSessionFlags (ULONG * pulFlags)
{
    if (*pulFlags & LOGON_NO_CONNECT)
    {
        // Nothing is set
        *pulFlags = 0;
    }
    else
    {
        // We DON'T want the MAPI spooler to call our IXPLogon::Idle method (LOGON_SP_IDLE not added)
        // We DON'T want the MAPI spooler to call our IXPLogon::Poll method (LOGON_SP_POLL not added)
        // Also the names have to be fully resolved (LOGON_SP_RESOLVE)
        *pulFlags = LOGON_SP_RESOLVE;
    }
}

///////////////////////////////////////////////////////////////////////////////
//    CXPLogon::SendMailMessage()
//
//    Parameters
//      pMsgObj     Pointer to an IMessage object passed to us by the
//                  MAPI spooler.
//      pRecipRows  Row set with ALL the rows from the recipient table which
//                  have the properties of the recipients we are sending the
//                  message to.
//
//    Purpose
//      This method gets called by SubmitMessage() to do the delivery of the
//      message to the list of recipients. Each recipient will have the
//      PR_RESPONSIBILITY property set indicating weather or not message
//      reached the recipient.
//
//    Return Value
//      An HRESULT
//
STDMETHODIMP CXPLogon::SendMailMessage (LPMESSAGE pMsgObj, LPSRowSet pRecipRows)
{
    LPSPropValue pMsgProps = NULL;
    LPADRLIST pAdrList = NULL, pAdrListFailed = NULL;
    LPSTnefProblemArray pProblems = NULL;
    CCachedStream * pStream = NULL;
    LPSTREAM pFileStream;
    HANDLE hMsgFile = NULL;
    HRESULT hOpenConnect, hUploadError;
    BOOL fErrorInServer, fSentSuccessfully;
    ULONG ulRow, ulCount1 = 0 , ulCount2 = 0;
    LPTSTR pszServer, pszMailbox;
    LPSPropValue pProps;
    TCHAR szHeaderText[1024], szTmpFile[_MAX_PATH], szConnectInfo[MAX_STRING_SIZE+1] = { 0 };
    if (!GetMsgTempFileName (szTmpFile))   // Not the Win32 API, but an internal implementation
    {
        return E_FAIL;
    }

    // Create a stream where all message information will be saved.
    HRESULT hResult = OpenStreamOnFile (gpfnAllocateBuffer,
                                        gpfnFreeBuffer,
                                        STGM_CREATE | STGM_READWRITE,
                                        szTmpFile,
                                        NULL,
                                        &pFileStream);
    if (hResult)
    {
        TraceResult ("CXPLogon::SendMailMessage: Failed to create stream object", hResult);
        return hResult;
    }
    try
    {
        pStream = new CCachedStream (pFileStream, XPSOF_READWRITE);
        if (!pStream)
        {
            TraceMessage ("CXPLogon::SendMailMessage: Failed to allocate cached stream object");
            hResult = E_OUTOFMEMORY;
        }
    }
    catch (CException & Exception)
    {
        hResult = Exception.GetError();
    }
    pFileStream->Release();
    pFileStream = NULL;
    if (hResult)
    {
        return hResult;
    }

    // The wKey is a key used to identify the TNEF property stream. Transports
    // should generate a pseudo-random number for this field. Here we get
    // a number based upon the system's tic count
    // Note that this number cannot be zero of the  OpenTnefStream call will be fail.
    WORD wKey = LOWORD (GetTickCount());
    if (!wKey)
    {
        ASSERTMSG (FALSE, "I'll be darn! It's zero!!!");
        wKey = LOWORD (GetTickCount()) + 1;
        ASSERTMSG (0 != wKey, "No way! What is going on!?!?");
    }
    LPITNEF pTNEFObj = NULL;
    hResult = OpenTnefStream (m_pSupObj,
                              pStream,
                              TNEF_FILE_NAME,
                              TNEF_ENCODE | TNEF_PURE,
                              pMsgObj,
                              wKey,
                              &pTNEFObj);
    if (hResult)
    {
        TraceResult ("CXPLogon::SendMailMessage: Failed to create TNEF object", hResult);
        goto ErrorExit;
    }

    // Let the MAPI spooler do other things
    CheckSpoolerYield();

    // Get the current time. We need to set some properties that require the time
    SYSTEMTIME st;
    FILETIME ft;
    GetSystemTime (&st);
    SystemTimeToFileTime (&st, &ft);

    SetOutgoingProps (pMsgObj, ft);

    // Check what properties there are and exclude the Non-Transmittables ones
    LPSPropTagArray pTags;
    hResult = pMsgObj->GetPropList (fMapiUnicode, &pTags);
    if (hResult)
    {
        TraceResult ("CXPLogon::SendMailMessage: Failed to get the message property tags", hResult);
        goto ErrorExit;
    }

    // Let the MAPI spooler do other things
    CheckSpoolerYield();

    // In this sample transport we opted to let TNEF encapsulate
    // the table of recipients of this message. This has a side effect: The
    // addresses of the recipients get munged into the TNEF stream. So, for
    // example, if the TNEF file goes through a foreign mail system and it
    // needs to translate the address of the recipients, it will not be
    // able to. A tranport using TNEF which trasmits messages to a foreign
    // mail system, must do custom processing of the recipients and their
    // address so the receiving side will understands them.
    // This sample code must be modified if you want it as the base code
    // for a gateway transport.
    // Here we also let TNEF encode all the attachments we want to send.
    ULONG cValues, i;
    cValues = 0;
    for (i=0; i<pTags->cValues; i++)
    {
        // Use the FIsTransmittable macro in MAPI to determine if a
        // property is transmittable or not.
        if (!FIsTransmittable(pTags->aulPropTag[i]) &&
            PR_MESSAGE_RECIPIENTS != pTags->aulPropTag[i] &&
            PR_MESSAGE_ATTACHMENTS != pTags->aulPropTag[i])
        {
            pTags->aulPropTag[cValues++] = pTags->aulPropTag[i];
        }
    }
    pTags->cValues = cValues;

    // Encode the properties now
    hResult = pTNEFObj->AddProps (TNEF_PROP_EXCLUDE, 0, NULL, pTags);
    gpfnFreeBuffer (pTags);
    if (FAILED(hResult)) // There could be warnings
    {
        TraceResult ("CXPLogon::SendMailMessage: Failed to Add the TNEF properties to the message stream", hResult);
        goto ErrorExit;
    }

    hResult = pTNEFObj->Finish (0, &wKey, &pProblems);
    if (FAILED(hResult)) // There could be warnings
    {
        TraceResult ("CXPLogon::SendMailMessage: Failed to save the TNEF props", hResult);
        goto ErrorExit;
    }
    if (pProblems)
    {
        TraceMessage ("CXPLogon::SendMailMessage: Some problem(s) occurred while finishing the TNEF encoding");
        gpfnFreeBuffer (pProblems);
        pProblems = NULL;
        // Don't have to fail submission
    }

    // Release used objects and NULL the object pointers to avoid re-releasing them during cleanup
    if (NULL != pTNEFObj)
    {
        pTNEFObj->Release();
        pTNEFObj = NULL;
    }
    if (NULL != pStream)
    {
        pStream->Release();
        pStream = NULL;
    }

    hMsgFile = CreateFile (szTmpFile,
                           GENERIC_READ,
                           0,
                           NULL,
                           OPEN_EXISTING,
                           FILE_ATTRIBUTE_TEMPORARY |
                           FILE_FLAG_DELETE_ON_CLOSE |
                           FILE_FLAG_SEQUENTIAL_SCAN,
                           NULL);
    if (INVALID_HANDLE_VALUE == hMsgFile)
    {
        TraceResult ("CXPLogon::SendMailMessage: Failed to open local msg file", GetLastError());
        hResult = E_FAIL;
        goto ErrorExit;
    }

    // Get some properties in the message need to send the message
    // and delivery report information
    hResult = pMsgObj->GetProps ((LPSPropTagArray)&sptPropsForHeader,
                                 fMapiUnicode,
                                 &cValues,
                                 &pMsgProps);
    if (FAILED(hResult))
    {
        TraceResult ("CXPLogon::SendMailMessage: Failed to get message props", hResult);
        goto ErrorExit;
    }

    // We need to check if the sender requeste a delivery report or not.
    BOOL fNeedDeliveryReport;
    if (PR_ORIGINATOR_DELIVERY_REPORT_REQUESTED == pMsgProps[MSG_DR_REPORT].ulPropTag &&
        pMsgProps[MSG_DR_REPORT].Value.b)
    {
        fNeedDeliveryReport = TRUE;
    }
    else
    {
        fNeedDeliveryReport = FALSE;
    }

    // Create the header that we transmit to the server. The remote host will
    // store this information and make it available to us when then recipients
    // of the message ask for a headers update on their remote mailboxes.
    CreateMsgHeaderTextLine (pMsgProps, szHeaderText, ft);

    // Let the MAPI spooler do other things
    CheckSpoolerYield();

    hOpenConnect = OpenServerUploadPipe (m_szServer,
                                         m_UserInfo.szMailboxName,
                                         hMsgFile,
                                         szConnectInfo,
                                         &fErrorInServer);
    for (ulRow=0; ulRow<pRecipRows->cRows; ulRow++)
    {
        pProps = pRecipRows->aRow[ulRow].lpProps;

        // Assume the worst. If hOpenConnect is not S_OK, the fSentSuccessfully
        // must be FALSE to generate NDR for each recipient.
        fSentSuccessfully = FALSE;
        if (S_OK == hOpenConnect)
        {
            if (IsValidAddress (pProps[RECIP_EMAIL_ADR].Value.LPSZ, &pszServer, &pszMailbox))
            {
                // pszServer should be the same as m_szServer
                hUploadError = SendMsgToAccount (pszServer,
                                                 pszMailbox,
                                                 szHeaderText,
                                                 szConnectInfo,
                                                 &fErrorInServer);
                if (!hUploadError)
                {
                    // If we got here, we assume the message has been received in the server
                    fSentSuccessfully = TRUE;
                }
            }
            else
            {
                hUploadError = MAKE_HRESULT(1, FACILITY_WIN32, ERROR_INVALID_ADDRESS);
            }
        }
        else
        {
            hUploadError = hOpenConnect;
        }

        // Let the MAPI spooler do other things
        CheckSpoolerYield();

        // Set the PR_RESPONSIBILITY flag to indicated we have handled this
        // recipient (row). If the flag is not modified, MAPI will pass this
        // message to the next transport in the profile that knows how to
        // handle the address types this transport knows.
        // In this case WE want to be the last to handle the message. If
        // we fail the submission, we should tell MAPI to generate an NDR.
        pProps[RECIP_RESPONSIBILITY].ulPropTag = PR_RESPONSIBILITY;
        pProps[RECIP_RESPONSIBILITY].Value.b = TRUE;

        // Set the report time for DR's and NDR's
        pProps[RECIP_REPORT_TIME].ulPropTag = PR_REPORT_TIME;
        pProps[RECIP_REPORT_TIME].Value.ft = ft;

        if (!fSentSuccessfully)
        {
            // Make the spooler generate an NDR instead of DR
            pProps[RECIP_DELIVER_TIME].ulPropTag = PR_NULL;

            // The Spooler will generate an NDR report and will fill in
            // all required properties in the StatusRecips call. The only
            // thing we need to do is to fill in a specific per-recipient
            // text description of the problem. It's good to have real
            // info from the transport indicating the real cause for the
            // failure
            wsprintf (szHeaderText,
                      TEXT("\tThe WINDS transport service failed to deliver the message to this recipient.\r\n"
                           "\tRecipient Address: Server: %s  Mailbox: %s. Delivery error: %#08X.  %s"),
                           (pszServer ? pszServer : ""),
                           (pszMailbox ? pszMailbox : ""),
                           hUploadError,
                      (fErrorInServer ? TEXT("The error occurred in the server host.") :
                                        TEXT("The error occurred in local processing.")));
            if (fErrorInServer && hUploadError)
            {
                DWORD dwServerErrorIDS = 0;
                switch (hUploadError)
                {
                    case HRESULT_FROM_WIN32(ERROR_INVALID_ACCOUNT_NAME) :
                        dwServerErrorIDS = IDS_DELIVERY_ERROR_INVALID_ACCT;
                        break;
                    case HRESULT_FROM_WIN32(ERROR_NO_SUCH_USER) :
                        dwServerErrorIDS = IDS_DELIVERY_ERROR_NO_SUCH_USER;
                        break;
                    case HRESULT_FROM_WIN32 (ERROR_HOST_UNREACHABLE) :
                        dwServerErrorIDS = IDS_DELIVERY_ERROR_OFFLINE_SERVER;
                        break;
                    case HRESULT_FROM_WIN32 (ERROR_INVALID_ADDRESS) :
                        dwServerErrorIDS = IDS_DELIVERY_ERROR_INVALID_ADDRESS;
                        break;
                    case E_OUTOFMEMORY :
                        dwServerErrorIDS = IDS_DELIVERY_ERROR_OUTOFMEMORY;
                        break;
                    case E_INVALIDARG :
                        dwServerErrorIDS = IDS_DELIVERY_ERROR_INVALID_PARAM;
                        break;
                }
                if (!dwServerErrorIDS && FACILITY_STORAGE == HRESULT_FACILITY(hUploadError))
                {
                    dwServerErrorIDS = IDS_DELIVERY_ERROR_ISTORAGE;
                }
                if (!dwServerErrorIDS && FACILITY_WIN32 == HRESULT_FACILITY(hUploadError))
                {
                    dwServerErrorIDS = IDS_DELIVERY_ERROR_WIN32;
                }
                if (dwServerErrorIDS)
                {
                    TCHAR szBuffer[256];
                    if (LoadString (m_hInstance, dwServerErrorIDS, szBuffer, 255))
                    {
                        lstrcat (szHeaderText, TEXT("\r\n\t"));
                        lstrcat (szHeaderText, szBuffer);
                    }
                }
            }
            LPTSTR pStr;
            hResult = gpfnAllocateMore (Cbtszsize(szHeaderText), pProps, (LPVOID *)&pStr);
            if (SUCCEEDED(hResult))
            {
                // Copy the formatted string and hook it into the
                // pre-allocated (by MAPI) column
                lstrcpy (pStr, szHeaderText);
                pProps[RECIP_REPORT_TEXT].ulPropTag = PR_REPORT_TEXT;
                pProps[RECIP_REPORT_TEXT].Value.LPSZ = pStr;
            }
            else
            {
                pProps[RECIP_REPORT_TEXT].ulPropTag = PROP_TAG (PT_ERROR, PROP_ID (PR_REPORT_TEXT));
                pProps[RECIP_REPORT_TEXT].Value.err = hResult;
                TraceResult ("CXPLogon::SendMailMessage: memory allocation failed for the NDR report string", hResult);
            }
        }
        else
        {
            // For delivery report, each recipient must have this property set.
            // Otherwise the spooler will default to generate an NDR instead.
            pProps[RECIP_DELIVER_TIME].ulPropTag = PR_DELIVER_TIME;
            pProps[RECIP_DELIVER_TIME].Value.ft = ft;

            pProps[RECIP_REPORT_TEXT].ulPropTag = PROP_TAG (PT_ERROR, PROP_ID (PR_REPORT_TEXT));
            pProps[RECIP_REPORT_TEXT].Value.err = S_OK;
        }

        // Based on the result of the submission to the remote host we determine into
        // which address list to add this recipient
        LPADRLIST * ppTmpList = (fSentSuccessfully ? &pAdrList : &pAdrListFailed);
        ULONG ulTmpCount = (fSentSuccessfully ? ulCount1 : ulCount2);

        // Does the list where this recipient goes have enough room for one more entry?
        // If not, resize the address list to hold QUERY_SIZE more entries.
        if (!(*ppTmpList) || ((*ppTmpList)->cEntries + 1 > ulTmpCount))
        {
            hResult= GrowAddressList (ppTmpList, 10, &ulTmpCount);
            if (hResult)
            {
                goto ErrorExit;
            }
            ulCount1 = (fSentSuccessfully ? ulTmpCount : ulCount1);
            ulCount2 = (!fSentSuccessfully ? ulTmpCount : ulCount2);
        }

        // We have room now so store the new ADRENTRY. As part of the
        // storage, we're going to copy the SRow pointer from the SRowSet
        // into the ADRENTRY. Once we've done this, we won't need the
        // SRowSet any more ... and the SRow will be released when
        // we unwind the ADRLIST
        (*ppTmpList)->aEntries[(*ppTmpList)->cEntries].cValues = pRecipRows->aRow[ulRow].cValues;
        (*ppTmpList)->aEntries[(*ppTmpList)->cEntries].rgPropVals = pRecipRows->aRow[ulRow].lpProps;

        // Increase the number of entries in the address list
        (*ppTmpList)->cEntries++;

        // Now that we are finished with this row (it is in the right
        // adrlist) we want to disassociate it from the rowset
        // so we don't delete this before we modify the recipients list
        pRecipRows->aRow[ulRow].lpProps = NULL;
        pRecipRows->aRow[ulRow].cValues = 0;

    }

    // Let the MAPI spooler do other things
    CheckSpoolerYield();

    // Do we have some recipients that the message arrived to?
    if (pAdrList)
    {
        hResult = pMsgObj->ModifyRecipients (MODRECIP_MODIFY, pAdrList);
        TraceResult ("CXPLogon::SendMailMessage: ModifyRecipients failed (DELIVERED)", hResult);
        hResult = S_OK; // We'll drop the error code from the modify recipients call
        if (fNeedDeliveryReport)
        {
            hResult = m_pSupObj->StatusRecips (pMsgObj, pAdrList);
            TraceResult ("CXPLogon::SendMailMessage: StatusRecips (DR) failed", hResult);
            if (!HR_FAILED(hResult))
            {
                // If we were successful, we should null out the pointer becase MAPI released
                // the memory for this structure. And we should not try to release it
                // again in the cleanup code.
                pAdrList = NULL;
            }
        }
    }
    // Do we have some recipients that the message DID NOT arrived to?
    if (pAdrListFailed)
    {
        hResult = pMsgObj->ModifyRecipients (MODRECIP_MODIFY, pAdrListFailed);
        // We'll drop the error code from the modify recipients call
        TraceResult ("CXPLogon::SendMailMessage: ModifyRecipients failed (NON-DELIVERED)", hResult);

        // The address list has the entries with the PR_RESPONSIBILITY set, so the
        // spooler will know if it has to generate NDR reports.
        hResult = m_pSupObj->StatusRecips (pMsgObj, pAdrListFailed);
        TraceResult ("CXPLogon::SendMailMessage: StatusRecips (NDR) failed", hResult);
        if (!HR_FAILED(hResult))
        {
            // If we were successful, we should null out the pointer becase MAPI released
            // the memory for this structure. And we should not try to release it
            // again in the cleanup code.
            pAdrListFailed = NULL;
        }
    }

ErrorExit:
    gpfnFreeBuffer (pProblems);
    gpfnFreeBuffer (pMsgProps);
    FreePadrlist (pAdrList);
    FreePadrlist (pAdrListFailed);

    // Release used objects
    if (pTNEFObj)
    {
        pTNEFObj->Release();
    }
    if (pStream)
    {
        pStream->Release();
    }
    // Close the file if it has been opened
    CloseHandle (hMsgFile);

    // Delete the message file in case the function fails before the call to CreateFile() above
    DeleteFile (szTmpFile);

    // Call the sender function will NULL parameters to reset internal data buffers
    if (lstrlen(szConnectInfo))
    {
        FinishUploadConnection (m_szServer, szConnectInfo);
    }

    // Once we have sent all messages to the remote server(s), terminate all connections
    TerminateRemoteConnections();

    // Let the MAPI spooler do other things
    CheckSpoolerYield();

    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    CXPLogon::SetOutgoingProps()
//
//    Parameters
//      pMsgObj     Pointer to the IMessage object we are processing.
//      ft          FILETIME structure with the time the message is
//                  being delivered.
//
//    Purpose
//      This function checks that the sender information is on the message
//      so that we may get replies from the intended recipients.
//
//    Return Value
//      None.
//
void WINAPI CXPLogon::SetOutgoingProps (LPMESSAGE pMsgObj, FILETIME ft)
{
    LPSPropValue pSender;
    ULONG ulValues;
    HRESULT hResult = pMsgObj->GetProps ((LPSPropTagArray)&sptOutMsgProps, fMapiUnicode, &ulValues, &pSender);
    if (FAILED(hResult))
    {
        TraceResult ("CXPLogon::SetOutgoingProps: Failed to get properties from the message", hResult);
        pSender = NULL; // So that we may recover and continue using default values
    }
    ASSERT (2 == ulValues);
    #define NUM_OUTGOING_PROPS  11
    SPropValue spvProps[NUM_OUTGOING_PROPS] = { 0 };
    ULONG i = 0;
    // If no sender has been stamped on the message use the identity of the transport
    if (!pSender || PR_SENDER_ENTRYID != pSender[0].ulPropTag)
    {
        spvProps[i].ulPropTag = PR_SENDER_NAME;
        spvProps[i++].Value.LPSZ = m_UserInfo.szFullName;

        spvProps[i].ulPropTag = PR_SENDER_EMAIL_ADDRESS;
        spvProps[i++].Value.LPSZ = m_szAddress;

        spvProps[i].ulPropTag = PR_SENDER_ADDRTYPE;
        spvProps[i++].Value.LPSZ = WINDS_ADDRESS_TYPE;

        spvProps[i].ulPropTag = PR_SENDER_ENTRYID;
        spvProps[i++].Value.bin = m_pIdentityProps[XPID_EID].Value.bin;

        spvProps[i].ulPropTag = PR_SENDER_SEARCH_KEY;
        spvProps[i++].Value.bin = m_pIdentityProps[XPID_SEARCH_KEY].Value.bin;
    }
    // The MS Exchange mail viewer requires these properties
    if (!pSender || PR_SENT_REPRESENTING_NAME != pSender[1].ulPropTag)
    {
        spvProps[i].ulPropTag = PR_SENT_REPRESENTING_NAME;
        spvProps[i++].Value.LPSZ = m_UserInfo.szFullName;
        spvProps[i].ulPropTag = PR_SENT_REPRESENTING_SEARCH_KEY;
        spvProps[i++].Value.bin = m_pIdentityProps[XPID_SEARCH_KEY].Value.bin;
        spvProps[i].ulPropTag = PR_SENT_REPRESENTING_ENTRYID;
        spvProps[i++].Value.bin = m_pIdentityProps[XPID_EID].Value.bin;
        spvProps[i].ulPropTag = PR_SENT_REPRESENTING_ADDRTYPE;
        spvProps[i++].Value.LPSZ = WINDS_ADDRESS_TYPE;
        spvProps[i].ulPropTag = PR_SENT_REPRESENTING_EMAIL_ADDRESS;
        spvProps[i++].Value.LPSZ = m_szAddress;
    }
    gpfnFreeBuffer (pSender);

    // Set the time when this transport actually transmitted the message
    spvProps[i].ulPropTag = PR_MESSAGE_DELIVERY_TIME;
    spvProps[i++].Value.ft = ft;
    spvProps[i].ulPropTag = PR_PROVIDER_SUBMIT_TIME;
    spvProps[i++].Value.ft = ft;

    ASSERT (i <= NUM_OUTGOING_PROPS);
    hResult = pMsgObj->SetProps (i, spvProps, NULL);
    TraceResult ("CXPLogon::SetOutgoingProps: Failed to set properties in the message", hResult);
}

///////////////////////////////////////////////////////////////////////////////
//    CXPLogon::SetIncomingProps()
//
//    Parameters
//      pMsgObj     Pointer to the IMessage object we are processing.
//
//    Purpose
//      This function sets the PR_SENT_REPRESENTING_xxx properties in an
//      incoming message if those properties aren't already in the message.
//      For these properties we use the values for the sender of the message.
//      We also walk the recipient list restricted to the address type of our
//      transport looking for us, the recipient of the message, s that we may
//      set the PR_MESSAGE_TO_xxx and PR_MESSAGE_RECIP_ME properties in
//      the message.
//
//    Return Value
//      An HRESULT
//
HRESULT WINAPI CXPLogon::SetIncomingProps (LPMESSAGE pMsgObj, PLIST_NODE pNode)
{
    // This is the maximum number of properties that we could set in the message
    #define NUM_INCOMING_PROPS      28
    SPropValue spvProps[NUM_INCOMING_PROPS] =  { 0 };
    ULONG ulValues, i = 0;
    BOOL fNameIsMissing = FALSE, fAddressIsMissing = FALSE;
    TCHAR szUnknown[] = TEXT("Unknown"), szAddress[128];
    TCHAR szUnknownAddress[] = TEXT("\\\\Unknown\\Unknown"), szSender[MAX_STRING_SIZE+1];
    LPTSTR pszAlias, pszServer;
    LPSPropValue pProps = NULL, pSenderSKEY = NULL, pSenderEID = NULL, pObjProps = NULL;
    LPVOID lpToBeFreed = NULL;

    HRESULT hResult = pMsgObj->GetProps ((LPSPropTagArray)&sptNewMsgProps, fMapiUnicode, &ulValues, &pProps);
    if (FAILED(hResult))
    {
        TraceResult ("CXPLogon::SetIncomingProps: Failed to get the message changes", hResult);
        goto RecoverAndContinue;
    }
    hResult = S_OK; // Get rid of any warnings
    // These properties should ALWAYS be in an incoming message, but just in case, we have a backup plan.
    if ((PR_SENDER_NAME != pProps[NEW_SENDER_NAME].ulPropTag ||
        PR_SENDER_EMAIL_ADDRESS != pProps[NEW_SENDER_EMAIL].ulPropTag) && !pNode->fRetry)
    {
        pNode->fRetry = TRUE;
        m_List.ReQueueNode (pNode);
        gpfnFreeBuffer (pProps);
        return MAPI_E_CORRUPT_DATA;
    }

    if (PR_SENDER_NAME != pProps[NEW_SENDER_NAME].ulPropTag)
    {
        fNameIsMissing = TRUE;
        pProps[NEW_SENDER_NAME].ulPropTag = PR_SENDER_NAME;
        if (PR_SENDER_EMAIL_ADDRESS == pProps[NEW_SENDER_EMAIL].ulPropTag)
        {
            // Decompose the address and get the alias. At least this is better that UNKNOWN!
            lstrcpy (szAddress, pProps[NEW_SENDER_EMAIL].Value.LPSZ);
            DecomposeAddress (szAddress, &pszServer, &pszAlias);
            lstrcpy (szSender, pszAlias);
            pProps[NEW_SENDER_NAME].Value.LPSZ = szSender;
        }
        else
        {
            // This is the best we can do.
            pProps[NEW_SENDER_NAME].Value.LPSZ = szUnknown;
        }
    }
    if (PR_SENDER_EMAIL_ADDRESS != pProps[NEW_SENDER_EMAIL].ulPropTag)
    {
        pProps[NEW_SENDER_EMAIL].ulPropTag = PR_SENDER_EMAIL_ADDRESS;
        pProps[NEW_SENDER_EMAIL].Value.LPSZ = szUnknownAddress;
        fAddressIsMissing = TRUE;
    }
    spvProps[i].ulPropTag = PR_SENDER_ADDRTYPE;
    spvProps[i++].Value.LPSZ = WINDS_ADDRESS_TYPE;
    spvProps[i].ulPropTag = PR_SENT_REPRESENTING_ADDRTYPE;
    spvProps[i++].Value.LPSZ = WINDS_ADDRESS_TYPE;

    // Looks like ABWDS is around, mark the internal flag.
    // ABWDS is the native WINDS address book service provider. If present,
    // instead of creating a one-off entry for the sender, we
    // will simply open the entry in the WINDS address book and get the
    // necessary properties out from it.
    // Note that in other to open an entry in the ABWDS address book provider
    // we need to have at least the email address of the sender, otherwise we
    // will default to create one-off entries in the sender (and delagate sender)
    if (m_fABWDSInstalled && !fAddressIsMissing)
    {
        PRIVATE_XP_ENTRYID eidEntry = { 0 };
        eidEntry.uidGlobal = guidXPABEntries;
        eidEntry.uidWINDSEntries = guidABEntries;
        // Decompose the address and get the alias.
        DecomposeAddress (pProps[NEW_SENDER_EMAIL].Value.LPSZ, &pszServer, &pszAlias);
        lstrcpy (eidEntry.szObjectAlias, pszAlias);
        // Put the Email address back to what it was
        RecomposeAddress (pszServer, pszAlias, pProps[NEW_SENDER_EMAIL].Value.LPSZ);
        LPMAILUSER pUser = NULL;
        ULONG ulObjType;
        const static SizedSPropTagArray (3, sptWINDSObjProps) =
        {
            3,
            {
                PR_DISPLAY_NAME,
                PR_SEARCH_KEY,
                PR_ENTRYID
            }
        };

        HRESULT hTmpResult = m_pSupObj->OpenEntry (CB_PRIVATE_XP_EID,
                                                   (LPENTRYID)&eidEntry,
                                                   NULL,
                                                   0,
                                                   &ulObjType,
                                                   (LPUNKNOWN *)&pUser);
        if (!hTmpResult)
        {
            hTmpResult = pUser->GetProps ((LPSPropTagArray)&sptWINDSObjProps,
                                          fMapiUnicode,
                                          &ulValues,
                                          &pObjProps);
            if (SUCCEEDED(hTmpResult)) // We might get warnings
            {
                if (PR_DISPLAY_NAME == pObjProps[0].ulPropTag &&
                    PR_SEARCH_KEY == pObjProps[1].ulPropTag &&
                    PR_ENTRYID == pObjProps[2].ulPropTag)
                {
                    if (fNameIsMissing)
                    {
                        spvProps[i].ulPropTag = PR_SENDER_NAME;
                        spvProps[i++].Value.LPSZ = pObjProps[0].Value.LPSZ;
                    }
                    spvProps[i].ulPropTag = PR_SENDER_SEARCH_KEY;
                    spvProps[i++].Value.bin = pObjProps[1].Value.bin;
                    spvProps[i].ulPropTag = PR_ENTRYID;
                    spvProps[i++].Value.bin = pObjProps[2].Value.bin;
                    if (PR_SENT_REPRESENTING_NAME != pProps[NEW_SENT_NAME].ulPropTag &&
                        PR_SENT_REPRESENTING_EMAIL_ADDRESS != pProps[NEW_SENT_EMAIL].ulPropTag)
                    {
                        // If the message doesn't have PR_SENT_REPRESENTING_xxx use the sender
                        // properties for the delagate sender properties
                        spvProps[i].ulPropTag    = PR_SENT_REPRESENTING_NAME;
                        spvProps[i++].Value.LPSZ = pObjProps[0].Value.LPSZ;
                        spvProps[i].ulPropTag    = PR_SENT_REPRESENTING_SEARCH_KEY;
                        spvProps[i++].Value.bin  = pObjProps[1].Value.bin;
                        spvProps[i].ulPropTag    = PR_SENT_REPRESENTING_ENTRYID;
                        spvProps[i++].Value.bin  = pObjProps[2].Value.bin;
                        spvProps[i].ulPropTag    = PR_SENT_REPRESENTING_ADDRTYPE;
                        spvProps[i++].Value.LPSZ = WINDS_ADDRESS_TYPE;
                        spvProps[i].ulPropTag    = PR_SENT_REPRESENTING_EMAIL_ADDRESS;
                        spvProps[i++].Value.LPSZ = pProps[NEW_SENDER_EMAIL].Value.LPSZ;
                    }
                }
                else
                {
                    // We couldn't find the properties needed from the WINDS
                    // address book entry. Continue with one-off entries
                    hTmpResult = MAPI_W_ERRORS_RETURNED;
                }
            }
            pUser->Release();
        }
        if (S_OK == hTmpResult)
        {
            goto ContinueAddingProps;
        }
    }

    // We need to make a search key for this recipient.
    spvProps[i].ulPropTag = PR_SENDER_SEARCH_KEY;
    hResult = MakeSearchKey (pProps,
                             pProps[NEW_SENDER_EMAIL].Value.LPSZ,
                             &spvProps[i].Value.bin.cb,
                             &spvProps[i].Value.bin.lpb);
    if (!hResult)
    {
        pSenderSKEY = &spvProps[i];
        i++;
        // We need to create a one-off entry in the address book so that we may
        // reply to this recipient. If the recipient already exist, its
        // entry Id will be returned instead.
        spvProps[i].ulPropTag = PR_SENDER_ENTRYID;

        //else
        {
            hResult = m_pSupObj->CreateOneOff (pProps[NEW_SENDER_NAME].Value.LPSZ,
                                               WINDS_ADDRESS_TYPE,
                                               pProps[NEW_SENDER_EMAIL].Value.LPSZ,
                                               fMapiUnicode,
                                               &spvProps[i].Value.bin.cb,
                                               (LPENTRYID *)&spvProps[i].Value.bin.lpb);
        }
        if (hResult)
        {
            i--; // Ignore this property and the previous
        }
        else
        {
            pSenderEID = &spvProps[i];
            i++;
        }
    }
    TraceResult ("CXPLogon::SetIncomingProps: Failed to create a one-off for the sender", hResult);

    if (PR_SENT_REPRESENTING_NAME == pProps[NEW_SENT_NAME].ulPropTag &&
        PR_SENT_REPRESENTING_EMAIL_ADDRESS == pProps[NEW_SENT_EMAIL].ulPropTag)
    {
        spvProps[i].ulPropTag = PR_SENT_REPRESENTING_SEARCH_KEY;
        hResult = MakeSearchKey (pProps,
                                 pProps[NEW_SENT_EMAIL].Value.LPSZ,
                                 &spvProps[i].Value.bin.cb,
                                 &spvProps[i].Value.bin.lpb);
        if (!hResult)
        {
            i++;
            spvProps[i].ulPropTag = PR_SENT_REPRESENTING_ENTRYID;
            hResult = m_pSupObj->CreateOneOff (pProps[NEW_SENT_NAME].Value.LPSZ,
                                               WINDS_ADDRESS_TYPE,
                                               pProps[NEW_SENT_EMAIL].Value.LPSZ,
                                               fMapiUnicode,
                                               &spvProps[i].Value.bin.cb,
                                               (LPENTRYID *)&spvProps[i].Value.bin.lpb);
            if (hResult)
            {
                i--; // Ignore this property and the previous
            }
            else
            {
                lpToBeFreed = spvProps[i].Value.bin.lpb;
                i++;
            }
        }
        // We trace the error but is not fatal
        TraceResult ("CXPLogon::SetIncomingProps: Failed to create a oneoff for the delegated sender", hResult);
    }
    else
    {
        // If the message doesn't have PR_SENT_REPRESENTING_xxx properties AND we were
        // successful at creating the one-off for the sender, we set PR_SENT_REPRESENTING_xxx
        // to the same values as PR_SENDER_xxx
        if (!hResult)
        {
            spvProps[i].ulPropTag       = PR_SENT_REPRESENTING_NAME;
            spvProps[i++].Value.LPSZ    = pProps[NEW_SENDER_NAME].Value.LPSZ;
            spvProps[i].ulPropTag       = PR_SENT_REPRESENTING_ADDRTYPE;
            spvProps[i++].Value.LPSZ    = WINDS_ADDRESS_TYPE;
            spvProps[i].ulPropTag       = PR_SENT_REPRESENTING_EMAIL_ADDRESS;
            spvProps[i++].Value.LPSZ    = pProps[NEW_SENDER_EMAIL].Value.LPSZ;

            ASSERT (PR_SENDER_ENTRYID == pSenderEID->ulPropTag);
            spvProps[i].ulPropTag       = PR_SENT_REPRESENTING_ENTRYID;
            spvProps[i++].Value         = pSenderEID->Value;

            ASSERT (PR_SENDER_SEARCH_KEY == pSenderSKEY->ulPropTag);
            spvProps[i].ulPropTag       = PR_SENT_REPRESENTING_SEARCH_KEY;
            spvProps[i++].Value         = pSenderSKEY->Value;
        }
    }

ContinueAddingProps:
    // If the sender's address is the same as our address (the recipient), then the message
    // was sent from us, to ourselves, therefore we must set the flag bit in the message.
    if (0 == lstrcmpi (pProps[NEW_SENDER_EMAIL].Value.LPSZ, m_szAddress))
    {
        ASSERT (PR_MESSAGE_FLAGS == pProps[NEW_MSG_FLAGS].ulPropTag);
        spvProps[i].ulPropTag = PR_MESSAGE_FLAGS;
        spvProps[i++].Value.l = pProps[NEW_MSG_FLAGS].Value.l | MSGFLAG_FROMME;
    }

RecoverAndContinue:
    // We must stamp the message with this properties since we (this transport)
    // were the ones who processed the incoming message.
    spvProps[i].ulPropTag       = PR_RECEIVED_BY_ENTRYID;
    spvProps[i++].Value.bin     = m_pIdentityProps[XPID_EID].Value.bin;
    spvProps[i].ulPropTag       = PR_RECEIVED_BY_NAME;
    spvProps[i++].Value.LPSZ    = m_pIdentityProps[XPID_NAME].Value.LPSZ;
    spvProps[i].ulPropTag       = PR_RECEIVED_BY_SEARCH_KEY;
    spvProps[i++].Value.bin     = m_pIdentityProps[XPID_SEARCH_KEY].Value.bin;
    spvProps[i].ulPropTag       = PR_RECEIVED_BY_ADDRTYPE;
    spvProps[i++].Value.LPSZ    = WINDS_ADDRESS_TYPE;
    spvProps[i].ulPropTag       = PR_RECEIVED_BY_EMAIL_ADDRESS;
    spvProps[i++].Value.LPSZ    = m_szAddress;

    // In this transport we set PR_RCVD_xxx with the values of PR_RECEIVED_xxx
    spvProps[i].ulPropTag       = PR_RCVD_REPRESENTING_ENTRYID;
    spvProps[i++].Value.bin     = m_pIdentityProps[XPID_EID].Value.bin;
    spvProps[i].ulPropTag       = PR_RCVD_REPRESENTING_NAME;
    spvProps[i++].Value.LPSZ    = m_pIdentityProps[XPID_NAME].Value.LPSZ;
    spvProps[i].ulPropTag       = PR_RCVD_REPRESENTING_SEARCH_KEY;
    spvProps[i++].Value.bin     = m_pIdentityProps[XPID_SEARCH_KEY].Value.bin;
    spvProps[i].ulPropTag       = PR_RCVD_REPRESENTING_ADDRTYPE;
    spvProps[i++].Value.LPSZ    = WINDS_ADDRESS_TYPE;
    spvProps[i].ulPropTag       = PR_RCVD_REPRESENTING_EMAIL_ADDRESS;
    spvProps[i++].Value.LPSZ    = m_szAddress;

    SYSTEMTIME st;
    FILETIME ftTime;
    GetSystemTime (&st);
    SystemTimeToFileTime (&st, &ftTime);
    spvProps[i].ulPropTag = PR_MESSAGE_DOWNLOAD_TIME;
    spvProps[i++].Value.ft = ftTime;

    LPMAPITABLE pTable;
    LPSRowSet pRows;
    BOOL fFoundCC, fFoundTO;
    fFoundCC = fFoundTO = FALSE;
    LPSPropValue pRecip;
    SPropValue spvFilter = { 0 };
    spvFilter.ulPropTag = PR_ADDRTYPE;
    spvFilter.Value.LPSZ = WINDS_ADDRESS_TYPE;

    SRestriction srRecips = { 0 };
    srRecips.rt = RES_PROPERTY;
    srRecips.res.resProperty.relop = RELOP_EQ;
    srRecips.res.resProperty.ulPropTag = PR_ADDRTYPE;
    srRecips.res.resProperty.lpProp = &spvFilter;

    hResult = pMsgObj->GetRecipientTable (fMapiUnicode, &pTable);
    if (!hResult)
    {
        hResult = HrQueryAllRows (pTable,
                                  (LPSPropTagArray)&sptMsgRecipProps,
                                  &srRecips,
                                  NULL,
                                  0,
                                  &pRows);
        if (!hResult)
        {
            ASSERTMSG (pRows->cRows > 0, "Huh?, Zero rows?");
            for (ULONG ulIndex=0; ulIndex<pRows->cRows; ulIndex++)
            {
                pRecip = pRows->aRow[ulIndex].lpProps;
                ASSERTMSG (PR_EMAIL_ADDRESS == pRecip[0].ulPropTag, "Where is the PR_EMAIL_ADDRESS?");
                ASSERTMSG (PR_RECIPIENT_TYPE == pRecip[1].ulPropTag, , "Where is the PR_RECIPIENT_TYPE?");
                if (PR_EMAIL_ADDRESS == pRecip[0].ulPropTag)
                {
                    // We use the address for the comparison because the sender might
                    // have create a one-off to send us this message and the only thing that this
                    // transport can count on being the same across all computers
                    // is the email address. The display name is modifyable by the user.
                    if (0 == lstrcmpi (pRecip[0].Value.LPSZ, m_szAddress))
                    {
                        if (PR_RECIPIENT_TYPE == pRecip[1].ulPropTag)
                        {
                            if (MAPI_TO == pRecip[1].Value.l)
                            {
                                fFoundTO = TRUE;
                            }
                            else
                            {
                                if (MAPI_CC == pRecip[1].Value.l)
                                {
                                    fFoundCC = TRUE;
                                }
                            }
                        }
                    }
                }
            }
            FreeProws (pRows);
        }
        pTable->Release();
    }
    TraceResult ("CXPLogon::SetIncomingProps: Something went wrong setting PR_MESSAGE_xxx", hResult);

    if (!hResult)
    {
        spvProps[i].ulPropTag = PR_MESSAGE_TO_ME;
        spvProps[i++].Value.b = fFoundTO;

        spvProps[i].ulPropTag = PR_MESSAGE_CC_ME;
        spvProps[i++].Value.b = fFoundCC;

        spvProps[i].ulPropTag = PR_MESSAGE_RECIP_ME;
        spvProps[i++].Value.b = fFoundTO || fFoundCC;
    }
    ASSERT (i <= NUM_INCOMING_PROPS);
    hResult = pMsgObj->SetProps (i, spvProps, NULL);
    TraceResult ("CXPLogon::SetIncomingProps: Failed to set properties in the message", hResult);
    gpfnFreeBuffer(lpToBeFreed);
    if(pSenderEID)
        gpfnFreeBuffer(pSenderEID->Value.bin.lpb);
    gpfnFreeBuffer (pProps);
    gpfnFreeBuffer (pObjProps);
    return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//    CXPLogon::GetMsgTempFileName()
//
//    Parameters
//      pszFileName     Pointer to a buffer allocated by the caller where the
//                      function returns a fully qualified path and file for
//                      a uniquely named temporary file.
//
//    Purpose
//      This function creates a temporary file name. The file name will be
//      returned in the pszFileName buffer which must have been allocated by
//      the caller. The file will have a fully qualified path to its location.
//      The location of the file is on the TEMP directory, as set in the system,
//      and within it, in the directory for the downloads of the WINDS
//      message transport
//
//    Return Value
//      TRUE if the function is successful at creating a temporary
//      unique file name. FALSE otherwise.
//
BOOL WINAPI CXPLogon::GetMsgTempFileName (LPTSTR pszFileName)
{
    TCHAR szTmpDir[_MAX_PATH], szDownloadDir[_MAX_PATH];
    // Ask the system for the TEMP directory
    DWORD dwChars = GetTempPath (_MAX_PATH, szTmpDir);
    if (dwChars)
    {
        lstrcat (szTmpDir, WINDS_DATA_DIRECTORY);
        wsprintf (szDownloadDir, WINDS_DOWNLOAD_DIR_NAME_FORMAT, szTmpDir, m_UserInfo.szMailboxName);
        dwChars = ::GetTempFileName (szDownloadDir,         // Call the Win32 API
                                     XP_MSG_FILE_PREFIX,    // Our transport's fixed prefix for temp files
                                     0,                     // Use the time to create a pseudo-random number
                                     pszFileName);          // Destination buffer
    }
    if (!dwChars)
    {
        TraceResult ("CXPLogon::GetMsgTempFileName: Failed to get temp path or file name", GetLastError());
    }
    return (0 != dwChars ? TRUE : FALSE);
}

///////////////////////////////////////////////////////////////////////////////
//    CXPLogon::CreateMsgHeaderTextLine()
//
//    Parameters
//      pProps              Array of properties of the message being
//                          submitted where we get the information to create a
//                          message header string to send to the server
//      pszBuffer           Buffer where the function copies the formated data
//                          for the server message header string
//      time                Reference to a FILETIME structure with the time
//                          the transport is delivering the message.
//
//    Purpose
//      This function creates a string with the data needed in the server
//      side to update the remote server mailboxes message header file of
//      the recipients.
//
//    Return Value
//      None
//
void WINAPI CXPLogon::CreateMsgHeaderTextLine (LPSPropValue     pProps,
                                               LPTSTR           pszBuffer,
                                               FILETIME &       time)
{
    // In case we don't find the properties in the array, we need
    // to supply default values for the strings. This method
    // should never fail.
    LPTSTR pszSubject = TEXT("<Subject Not Found>");
    LPTSTR pszMsgClass = TEXT("IPM.Note");
    TCHAR szDisplayTo[256] = { 0 };

    // In case we don't have the expected properties, assign default values.
    long lMsgFlags = 0;
    if (PR_MESSAGE_FLAGS == pProps[MSG_FLAGS].ulPropTag)
    {
        // Filter out the flags to only allow the ones listed
        lMsgFlags = pProps[MSG_FLAGS].Value.l & (MSGFLAG_UNMODIFIED |
                                                 MSGFLAG_HASATTACH |
                                                 MSGFLAG_FROMME |
                                                 MSGFLAG_RESEND);
    }
    if (pProps[MSG_SIZE].ulPropTag != PR_MESSAGE_SIZE)
    {
        pProps[MSG_SIZE].Value.l = 1024; // Default to 1Kb
    }
    if (pProps[MSG_PRIORITY].ulPropTag != PR_PRIORITY)
    {
        pProps[MSG_PRIORITY].Value.l = PRIO_NORMAL;
    }
    if (pProps[MSG_IMPORTANCE].ulPropTag != PR_IMPORTANCE)
    {
        pProps[MSG_IMPORTANCE].Value.l = IMPORTANCE_NORMAL;
    }
    if (pProps[MSG_SENSITIVITY].ulPropTag != PR_SENSITIVITY)
    {
        pProps[MSG_SENSITIVITY].Value.l = SENSITIVITY_NONE;
    }

    // Get the string of TO recipients. If the string is too long, set the elipsis at the end of the buffer
    if (pProps[MSG_DISP_TO].ulPropTag == PR_DISPLAY_TO)
    {
        LPTSTR pszDisplayTo = pProps[MSG_DISP_TO].Value.LPSZ;
        if (lstrlen (pszDisplayTo) > 256)
        {
            pszDisplayTo[252] = '.'; // Copy the elipsis for a long string
            pszDisplayTo[253] = '.';
            pszDisplayTo[254] = '.';
            pszDisplayTo[255] = 0;
        }
        LPTSTR pszOneName = strtok (pszDisplayTo, ";");
        if (pszOneName)
        {
            pszOneName[lstrlen(pszOneName) - 1] = 0;
            lstrcpy (szDisplayTo, &pszOneName[1]);
        }
        while (pszOneName)
        {
            pszOneName = strtok (NULL, ";");
            if (pszOneName)
            {
                pszOneName[0] = TEXT(';');
                pszOneName[1] = TEXT(' ');
                pszOneName[lstrlen(pszOneName) - 1] = 0;
                lstrcat (szDisplayTo, pszOneName);
            }
        }
    }
    if (0 == szDisplayTo[0])
    {
        lstrcpy (szDisplayTo, TEXT("<Display To Names Not Found>"));
    }
    // Get the message class string.
    if (pProps[MSG_CLASS].ulPropTag == PR_MESSAGE_CLASS)
    {
        pszMsgClass = pProps[MSG_CLASS].Value.LPSZ;
    }
    // Get the subject. If the string is too long, set the elipsis at the end of the buffer
    if (pProps[MSG_SUBJECT].ulPropTag == PR_SUBJECT)
    {
        pszSubject = pProps[MSG_SUBJECT].Value.LPSZ;
        if (lstrlen (pszSubject) > 256)
        {
            pszSubject[252] = '.'; // Copy the elipsis for a long string
            pszSubject[253] = '.';
            pszSubject[254] = '.';
            pszSubject[255] = 0;
        }
    }
    // Write the properties into the buffer. This buffer is the header
    // information we send to the server The buffer passed in must hold
    // at least 1024 characters
    wsprintf (pszBuffer,
              // The string must end with a ',' (for the parsing logic
              // in the downloading of the headers)
              TEXT("%d,%s,%d,%s,%d,%s,%s,%d,%d,%d,%d,%d,%d,%d,"),
              lstrlen(m_UserInfo.szFullName),
              m_UserInfo.szFullName,
              lstrlen(szDisplayTo),
              szDisplayTo,
              lstrlen(pszSubject),
              pszSubject,
              pszMsgClass,
              lMsgFlags,
              pProps[MSG_SIZE].Value.l,
              pProps[MSG_PRIORITY].Value.l,
              pProps[MSG_IMPORTANCE].Value.l,
              pProps[MSG_SENSITIVITY].Value.l,
              time.dwLowDateTime,
              time.dwHighDateTime);
}

///////////////////////////////////////////////////////////////////////////////
//    CXPLogon::IsValidAddress()
//
//    Parameters
//      pszAddress      The address of the recipient. This string gets
//                      decomposed locally, so it can't be re-used by
//                      the caller.
//      ppszServer      Pointer to a location where the function returns
//                      the remote server name
//      ppszMailbox     Pointer to a location where the function returns
//                      the remote user mailbox name
//
//    Purpose
//      This functions takes the address of a recipient and makes sure it is
//      valid (as far as syntax) and decomposes the address into two
//      components: Remote server name and Remote user mailbox name. The
//      two component strings are returned to the caller.
//
//    Return Value
//      TRUE if the address of the recipient is valid. FALSE otherwise.
//
BOOL WINAPI CXPLogon::IsValidAddress (LPTSTR        pszAddress,
                                      LPTSTR *      ppszServer,
                                      LPTSTR *      ppszMailbox)
{
    // Make sure that we can read the string
    if (!pszAddress || IsBadStringPtr (pszAddress, 32))
    {
        TraceMessage ("CXPLogon::IsValidAddress: Invalid string pointer");
        return FALSE;
    }
    DecomposeAddress (pszAddress, ppszServer, ppszMailbox);
    // Validate the names of the server and the mailbox
    if (!IsValidServerName (*ppszServer) || !*ppszMailbox)
    {
        TraceMessage ("CXPLogon::IsValidAddress: Invalid address for remote server host");
        return FALSE;
    }
    return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//    CXPLogon::GrowAddressList()
//
//    Parameters
//      ppAdrList           Pointer to an address where the old address list
//                          is and where the new resized address list will
//                          be returned
//      ulResizeBy          Number of new address entries to add to the list
//      pulOldAndNewCount   Number of entries in the old address list. In
//                          this parameter, upon sucessful return, will have
//                          the number of in the new address list
//
//    Purpose
//      In this function, given an address list with pulOldAndNewCount of
//      entries, we resize the address list to hold the old number of
//      entries plus the ulResizeBy entries. The old address list contents
//      are copied to the new list and the count reset. The memory for the
//      old address list is released here.
//
//    Return Value
//      An HRESULT
//
STDMETHODIMP CXPLogon::GrowAddressList (LPADRLIST *   ppAdrList,
                                        ULONG         ulResizeBy,
                                        ULONG *       pulOldAndNewCount)
{
    LPADRLIST pNewAdrList;
    // Calculate how big the new buffer for the expanded address list should be
    ULONG cbSize = CbNewADRLIST ((*pulOldAndNewCount) + ulResizeBy);
    // Allocate the memory for it
    HRESULT hResult = gpfnAllocateBuffer (cbSize, (LPVOID *)&pNewAdrList);
    if (hResult)
    {
        // We can't continue
        TraceResult ("CXPLogon::GrowAddressList: Failed to allocate memory for resized address list", hResult);
        return hResult;
    }

    // Zero-out all memory for neatness
    ZeroMemory (pNewAdrList, cbSize);

    // If we had entries in the old address list, copy the memory from
    // the old addres list into the new expanded list
    if ((*pulOldAndNewCount))
    {
        CopyMemory (pNewAdrList, *ppAdrList, CbNewADRLIST ((*pulOldAndNewCount)));
    }

    // Set the number of entries in the new address list to the OLD size
    pNewAdrList->cEntries = (*pulOldAndNewCount);

    // We must return the number of available entries in the new expanded address list
    (*pulOldAndNewCount) += ulResizeBy;

    // Free the old memory and put the new pointer in place
    gpfnFreeBuffer (*ppAdrList);
    *ppAdrList = pNewAdrList;
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    CXPLogon::CheckSpoolerYield()
//
//    Parameters
//      fReset      Resets the pseudo-timer
//
//    Purpose
//      Enforce the 0.2 second rule for transport that need to yield to the
//      MAPI spooler.  Called periodically while processing a message to
//      determine if we have used more than 0.2 seconds.  If so, then call
//      SpoolerYield(), else just continue.
//      This is called with fReset set to TRUE when we first enter one
//      of the Transport Logon methods (usually one that is known to
//      take a long time like StartMessage() or SubmitMessage(). )
//
//    Return Value
//      None.
//
void WINAPI CXPLogon::CheckSpoolerYield (BOOL fReset)
{
    DWORD dwStop;
    static DWORD dwStart;
    if (fReset)
    {
        dwStart = GetTickCount();
    }
    else
    {
        dwStop = GetTickCount();
        if ((dwStop - dwStart) > 200) // 200 milliseconds
        {
            m_pSupObj->SpoolerYield (0);
            dwStart = GetTickCount();
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
//    CXPLogon::InitializeStatusRow()
//
//    Parameters
//      ulFlags     0 if the properties are being created the first time.
//                  MODIFY_FLAGS if a change is being made to the properties
//
//    Purpose
//      To initialize or modify the status properties of a CXPLogon
//      object. This function allocates an array with NUM_STATUS_ROW_PROPS
//      properties and initializes them.
//
//    Return Value
//      An HRESULT
//
STDMETHODIMP CXPLogon::InitializeStatusRow (ULONG ulFlags)
{
    #define NUM_STATUS_ROW_PROPS    10
    SPropValue spvStatusRow[NUM_STATUS_ROW_PROPS] = { 0 };
    ULONG i = 0;

    ///////////////////////////////////////////////////////////////////////////
    // Set the PR_PROVIDER_DISPLAY property: The transport readable name
    spvStatusRow[i].ulPropTag = PR_PROVIDER_DISPLAY;
    spvStatusRow[i++].Value.LPSZ = TRANSPORT_DISPLAY_NAME_STRING;

    ///////////////////////////////////////////////////////////////////////////
    // Set the PR_RESOURCE_METHODS property. These are the methods implemented
    // in the our IMAPIStatus implementation (CMAPIStatus class.)
    spvStatusRow[i].ulPropTag = PR_RESOURCE_METHODS;
    // we support ALL the methods in our implementation of IMAPIStatus interface (except the WRITABLE ones)
    spvStatusRow[i++].Value.l = STATUS_SETTINGS_DIALOG |
                                STATUS_FLUSH_QUEUES |
                                STATUS_VALIDATE_STATE |
                                STATUS_CHANGE_PASSWORD;

    ///////////////////////////////////////////////////////////////////////////
    // Set the PR_STATUS_CODE property.
    spvStatusRow[i].ulPropTag = PR_STATUS_CODE;
    spvStatusRow[i++].Value.l = GetTransportStatusCode();

    ///////////////////////////////////////////////////////////////////////////
    // Set the PR_STATUS_STRING property
    TCHAR szStatus[64];
    LoadStatusString (szStatus, sizeof(szStatus));
    spvStatusRow[i].ulPropTag = PR_STATUS_STRING;
    spvStatusRow[i++].Value.LPSZ = szStatus;

    ///////////////////////////////////////////////////////////////////////////
    // Set the PR_DISPLAY_NAME property
    TCHAR szDisplayName[64];
    wsprintf (szDisplayName, TEXT("%s (%s)"), TRANSPORT_DISPLAY_NAME_STRING, m_szServer);
    spvStatusRow[i].ulPropTag = PR_DISPLAY_NAME;
    spvStatusRow[i++].Value.LPSZ = szDisplayName;

    ///////////////////////////////////////////////////////////////////////////
    // Set the PR_IDENTITY_ENTRYID property
    spvStatusRow[i].ulPropTag = PR_IDENTITY_ENTRYID;
    spvStatusRow[i++].Value = m_pIdentityProps[XPID_EID].Value;

    ///////////////////////////////////////////////////////////////////////////
    // Set the PR_IDENTITY_DISPLAY property
    spvStatusRow[i].ulPropTag = PR_IDENTITY_DISPLAY;
    spvStatusRow[i++].Value.LPSZ = m_pIdentityProps[XPID_NAME].Value.LPSZ;

    ///////////////////////////////////////////////////////////////////////////
    // Set the PR_IDENTITY_SEARCH_KEY property
    spvStatusRow[i].ulPropTag = PR_IDENTITY_SEARCH_KEY;
    spvStatusRow[i++].Value = m_pIdentityProps[XPID_SEARCH_KEY].Value;

    ///////////////////////////////////////////////////////////////////////////
    // Set the PR_REMOTE_PROGRESS property
    spvStatusRow[i].ulPropTag = PR_REMOTE_PROGRESS;
    spvStatusRow[i++].Value.l = -1; // Not initialized

    ///////////////////////////////////////////////////////////////////////////
    // Set the PR_REMOTE_VALIDATE_OK property
    spvStatusRow[i].ulPropTag = PR_REMOTE_VALIDATE_OK;
    spvStatusRow[i++].Value.b = TRUE;
    ASSERT (NUM_STATUS_ROW_PROPS == i);

    // Write the entries on the provider's session status row
    HRESULT hResult = m_pSupObj->ModifyStatusRow (i, spvStatusRow, ulFlags);
    TraceResult ("CXPLogon::InitializeStatusRow: Failed to modify the status row", hResult);
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    CXPLogon::CheckForUnfinishedDownloads()
//
//    Parameters
//      None.
//
//    Purpose
//      This function checks to see if we have files where downloaded messages
//      were lefted from a previous session or from a previous failed download
//      sequence. The message files, if any, should be in the data directory of
//      this service. If any files are found, the message queue is loaded and
//      the during out inbound logic initialization in
//      IXPLogon::TransportNotify(), we check the queue. If the queue is not
//      empty, we tell the transport to flush our inbound flush.
//
//    Return Value
//      None.
//
void WINAPI CXPLogon::CheckForUnfinishedDownloads()
{
    WIN32_FIND_DATA wfdFile = { 0 };
    TCHAR szTmpDir[_MAX_PATH], szDownloadDir[_MAX_PATH], szSearchMask[512];
    GetTempPath (_MAX_PATH, szTmpDir);
    lstrcat (szTmpDir, WINDS_DATA_DIRECTORY);
    wsprintf (szDownloadDir, WINDS_DOWNLOAD_DIR_NAME_FORMAT, szTmpDir, m_UserInfo.szMailboxName);
    wsprintf (szSearchMask, TEXT("%s\\%s*.%s"), szDownloadDir, XP_MSG_FILE_PREFIX, XP_MSG_FILE_SUFFIX);
    HANDLE hSearch = FindFirstFile (szSearchMask, &wfdFile);
    if (hSearch == INVALID_HANDLE_VALUE)
    {
        return;
    }
    BOOL fFound = TRUE;
    while (fFound)
    {
        wsprintf (szTmpDir, TEXT("%s\\%s"), szDownloadDir, wfdFile.cFileName);
        // If the file size of 0, then is probably some garbage file. Get rid of it.
        // A zero-sized file does not contains a message.
        if (0 == wfdFile.nFileSizeHigh && 0 == wfdFile.nFileSizeLow)
        {
            DeleteFile (szTmpDir);
        }
        else
        {
            m_List.QueuePendingMsgFile (szTmpDir);
        }
        fFound = FindNextFile (hSearch, &wfdFile);
    }
}

///////////////////////////////////////////////////////////////////////////////
//    CXPLogon::DownloadMessageHeaders()
//
//    Parameters
//      None
//
//    Purpose
//      This function downloads the message headers for the user's mailbox and
//      is a remote folder is available, re-load the contents table of the
//      folder with the new message headers information.
//
//    Return Value
//      An HRESULT
//
STDMETHODIMP CXPLogon::DownloadMessageHeaders()
{
    // Guard against re-entrancy from the timer call back which happens on a separate thread
    UpdateProgress (0, REMOTE_ACTION_HEADER_REFRESH);     // Start the progress bar
    HRESULT hResult = GetHeadersFromServer (m_szServer,
                                            m_UserInfo.szMailboxName,
                                            m_szHeaders);
    UpdateProgress (50, REMOTE_ACTION_HEADER_REFRESH);    // Half way through
    if (!hResult && m_pStatusObj && m_pStatusObj->m_pHeaderFolder)
    {
        hResult = m_pStatusObj->m_pHeaderFolder->FillContentsTable (m_szHeaders);
    }
    UpdateProgress (100, REMOTE_ACTION_HEADER_REFRESH);   // Finish
    TraceResult ("CXPLogon::DownloadMessageHeaders", hResult);
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    CXPLogon::EmptyInboundQueue()
//
//    Parameters
//      None
//
//    Purpose
//      Deletes all the node in the queue of downloaded messages, deleting
//      the used memory and closing the handle to the local temporary
//      message file.
//
//    Return Value
//      None
//
void WINAPI CXPLogon::EmptyInboundQueue()
{
    // If we have nodes at this point, is because the transport could not
    // process them at this time. They will be retrieved in the next time this
    // transport comes on line on the same profile or on a profile that has
    // the same user identity.
    PLIST_NODE pNode = m_List.GetDownloadNode();
    while (pNode)
    {
        CloseHandle (pNode->hFile);
        delete pNode;
        // If the list is empty, pNode will be NULL.
        // CList::GetDownloadNode() returns NULL for an empty list.
        pNode = m_List.GetDownloadNode();
    }
}

///////////////////////////////////////////////////////////////////////////////
//    TimerWndProc()
//
//    Parameters
//      { Refer to Win32 documentation }
//
//    Purpose
//      Stub window procedure for the hidden timer window class.
//
//    Return Value
//      Default value return by the default window procedure
//
LRESULT CALLBACK TimerWndProc (HWND      hWnd,
                               UINT      message,
                               WPARAM    wParam,
                               LPARAM    lParam)
{
    return DefWindowProc(hWnd, message, wParam, lParam);
}


///////////////////////////////////////////////////////////////////////////////
//    CXPLogon::InitializeTimer()
//
//    Parameters
//      None.
//
//    Purpose
//      Initialize the hidden window for the upload timer.
//
//    Return Value
//      None.
//
void WINAPI CXPLogon::InitializeTimer()
{
    WNDCLASS wc = { 0 };
    // Register the class for this application
    wc.lpfnWndProc      = TimerWndProc;
    wc.hInstance        = m_hInstance;
    wc.lpszClassName    = TIMER_WND_CLASS;
    if (!RegisterClass (&wc))
    {
        TraceResult ("InitializeTimer: Failed to register the timer window class", GetLastError());
        return;
    }
    m_hTimerWnd = CreateWindow (TIMER_WND_CLASS,
                                NULL,
                                WS_OVERLAPPEDWINDOW,
                                0, 0, 0, 0,
                                NULL,
                                NULL,
                                m_hInstance,
                                NULL);
    if (NULL == m_hTimerWnd)
    {
        TraceResult ("InitializeTimer: Failed to create timer window", GetLastError());
        return;
    }
    SetWindowLong (m_hTimerWnd, GWL_USERDATA, (LONG)this);
}

///////////////////////////////////////////////////////////////////////////////
//    CXPLogon::StartUploadTimer()
//
//    Parameters
//      None.
//
//    Purpose
//      This function sets a timer with the operating system. When
//      the specified period elapses, we will get called in the procedure
//      specified and we will then flush the incoming and outgoing queues.
//      Note that we round the delivery time to the HOUR
//
//    Return Value
//      None.
//
void WINAPI CXPLogon::StartUploadTimer()
{
    SYSTEMTIME stNow = { 0 };
    GetLocalTime (&stNow);
    WORD wUploadHour = m_stDelivTime.wHour;
    // If the time is 0:00, this is 12:00 AM midnight
    if (!wUploadHour)
    {
        wUploadHour = 24;
    }
    UINT uDelay = 0;
    // How many hours before the next upload?
    int nHours = wUploadHour - stNow.wHour;
    if (nHours <= 0)
    {
        // If the hours is 0 and the time hasn't arrived with in this hour,
        // set the upload timer for THIS hour.
        if (0 == nHours && stNow.wMinute < m_stDelivTime.wMinute)
        {
            nHours = -24;
            uDelay += (UINT)(m_stDelivTime.wMinute - stNow.wMinute) * 60 * 1000;
        }
        nHours += 24;
    }
    uDelay += (UINT)nHours * 60 * 60 * 1000; // Number of milliseconds in the hours
    m_uTimerID = SetTimer (m_hTimerWnd, 0, uDelay, UploadTimerProc);
    if (0 == m_uTimerID)
    {
        TraceResult ("CXPLogon::StartUploadTimer: Failed to set the timer", GetLastError());
    }
}

///////////////////////////////////////////////////////////////////////////////
//    CXPLogon::StopUploadTimer()
//
//    Parameters
//      None.
//
//    Purpose
//      Terminates the timer used for the upload time.
//
//    Return Value
//      None
//
void WINAPI CXPLogon::StopUploadTimer()
{
    // If we have a timer around, terminate it and all its associated resources
    if (m_uTimerID)
    {
        KillTimer (m_hTimerWnd, m_uTimerID);
        DestroyWindow (m_hTimerWnd);
        UnregisterClass (TIMER_WND_CLASS, m_hInstance);
        m_hTimerWnd = NULL;
        m_uTimerID = 0;
    }
}

///////////////////////////////////////////////////////////////////////////////
//    UploadTimerProc()
//
//    Parameters
//      { Refer to the Win32 TIMERPROC callback parameters }
//
//    Purpose
//      This function executes when the timer delay has expired.
//      Now we ask the spooler to send us the deferred messages, and we set
//      the transport state ready to receive updated headers.
//
//    Return Value
//      None
//
void CALLBACK UploadTimerProc (HWND    hTimerWnd,
                               UINT    Message,
                               UINT    idEvent,
                               DWORD   dwTime)
{
    KillTimer (hTimerWnd, idEvent);
    // We asked to get the CXPLogon object who set the timer. We now
    // check and see if the object is valid before we attempt to use it.
    CXPLogon * pLogon = (CXPLogon *)GetWindowLong (hTimerWnd, GWL_USERDATA);
    if (!pLogon ||
        IsBadWritePtr (pLogon, sizeof(CXPLogon)) ||
        IsBadReadPtr (pLogon, sizeof(CXPLogon)))
    {
        TraceMessage ("UploadTimerProc: We got a bogus logon object");
        return;
    }
    pLogon->m_uTimerID = 0;

    // If the transport's outgoing logic has been activated in this session,
    // send all the deferred messages, by flushing the transport.
    if (pLogon->GetTransportStatusCode() & STATUS_OUTBOUND_ENABLED)
    {
        pLogon->AddStatusBits (UPLOADING_MESSAGES);
    }
    // If the transport's incoming logic has been activated in this session,
    // get any pending messages that need to be placed in the default inbox,
    // and set the transport state, ready to get the headers from the server..
    if (pLogon->GetTransportStatusCode() & STATUS_INBOUND_ENABLED)
    {
        pLogon->AddStatusBits (DOWNLOADING_MESSAGES);
        pLogon->SetTransportState (PROCESSING_TIMER_EVENT);
    }
    // Modify the status row now
    pLogon->UpdateStatus();
    // Reset the time for the next upload. Uploading time is a recurring event.
    pLogon->StartUploadTimer();
}

// End of file for XPLOGON.CPP
