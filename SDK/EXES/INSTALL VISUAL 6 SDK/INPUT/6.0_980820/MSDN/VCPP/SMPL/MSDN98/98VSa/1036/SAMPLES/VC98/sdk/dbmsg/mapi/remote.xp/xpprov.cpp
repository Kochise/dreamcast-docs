///////////////////////////////////////////////////////////////////////////////
//
//  File Name 
//      XPPROV.CPP
//
//  Description
//      This file implements the IXPProvider interface with the methods 
//      specified in the MAPI SPI 1.0 specifications. Also some helper
//      functions are implemented in this file.
//
//  Author
//      Irving De la Cruz
//
//  Revision: 1.7
//
// Written for Microsoft Windows Developer Support
// Copyright (c) 1995-1996 Microsoft Corporation. All rights reserved.
//
#define INITGUID
#define USES_IID_IXPProvider
#define USES_IID_IXPLogon
#define USES_IID_IMAPIStatus
#define USES_IID_IMAPIProp
#define USES_IID_IMAPIPropData
#define USES_IID_IMAPIControl
#define USES_IID_IMAPIContainer
#define USES_IID_IMAPIFolder
#define USES_IID_IMAPITableData

#include "XPWDSR.H"

// Remark this line to turn verbose tracing OFF
#define DO_INFO_TRACES
#ifdef DO_INFO_TRACES
#define InfoTrace(a)   TraceInfoMessage(a)
#else
#define InfoTrace(a)   
#endif // DO_INFO_TRACES

///////////////////////////////////////////////////////////////////////////////
//    CXPProvider::CXPProvider()
//
//    Parameters
//      hInst                   Handle to instance of this XP DLL
//
//    Purpose
//      Constructor of the object. Parameters are passed to initialize the
//      data members with the appropiate values.
//
//    Return Value
//      None
//
CXPProvider::CXPProvider (HINSTANCE hInst)
{
    InfoTrace ("CXPProvider: Constructor called");
    m_hInstance    = hInst;
    m_cRef         = 1;
    // Initialize critical sections for this transport
    InitializeCriticalSection (&m_csTransport);
}

///////////////////////////////////////////////////////////////////////////////
//    CXPProvider::~CXPProvider()
//
//    Parameters
//      None
//
//    Purpose
//      Close down and release resources and libraries
//
//    Return Value
//      None
//
CXPProvider::~CXPProvider()
{
    InfoTrace ("CXPProvider: Destructor called");
    m_hInstance = NULL;

    // This is the last method called on a transport, close down the traces
    UnInitTraces();
    DeleteCriticalSection (&m_csTransport);
}

///////////////////////////////////////////////////////////////////////////////
//    CXPProvider::QueryInterface()
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
STDMETHODIMP CXPProvider::QueryInterface (REFIID riid, LPVOID * ppvObj)
{
    // OLE requires NULLing parameter
    *ppvObj = NULL;
    // If this is one of the two IID return an interface pointer to it
    if (riid == IID_IXPProvider || riid == IID_IUnknown)
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
// IXPProvider virtual member functions implementation
//

///////////////////////////////////////////////////////////////////////////////
//    CXPProvider::Shutdown()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Stub method.
//
//    Return Value
//      An HRESULT
//
STDMETHODIMP CXPProvider::Shutdown (ULONG * pulFlags)
{
    InfoTrace ("CXPProvider::Shutdown method called");
    CheckParameters_IXPProvider_Shutdown (this, pulFlags);
    return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//    CXPProvider::TransportLogon()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Display the logon dialog to show the options saved in the profile for
//      this provider and allow changes to it. Save new configuration settings
//      back in the profile.
//      Create a new CXPLogon object and return it to the spooler. Also, 
//      initialize the properties array for each address type handled
//      by this transport. Check all the flags and return them to the spooler
//
//    Return Value
//      An HRESULT
//
STDMETHODIMP CXPProvider::TransportLogon (LPMAPISUP     pSupObj,
                                          ULONG         ulUIParam,
                                          LPTSTR        pszProfileName,
                                          ULONG *       pulFlags,
                                          LPMAPIERROR * ppMAPIError,
                                          LPXPLOGON *   ppXPLogon)
{
    InfoTrace ("CXPProvider::TransportLogon method called");
    CheckParameters_IXPProvider_TransportLogon (this,
                                                pSupObj,
                                                ulUIParam,
                                                pszProfileName,
                                                pulFlags,
                                                ppMAPIError,
                                                ppXPLogon);
    CXPLogon * pXPLogon = NULL;
    ULONG ulPropCount;
    LPSPropValue pProps = NULL;
    MAILBOX_INFO UserMBInfo = { 0 };
    CFGDLG CfgDialog = { 0 };
    LPPROFSECT pProfileObj;
    HRESULT hResult = OpenServiceProfileSection (pSupObj, &pProfileObj, gpfnFreeBuffer);
    if (hResult)
    {
        TraceResult ("CXPProvider::TransportLogon: Failed to open the service profile section", hResult);
        return hResult;
    }

    HANDLE hUIMutex = CreateMutex (NULL, FALSE, CONFIG_UI_MUTEX);
    if (NULL == hUIMutex)
    {
        HRESULT hResult = HRESULT_FROM_WIN32 (GetLastError());
        TraceResult ("CXPProvider::TransportLogon: Failed to create UI mutext", hResult);
    }
    
    hResult = pProfileObj->GetProps ((LPSPropTagArray)&sptLogonProps,
                                     fMapiUnicode,
                                     &ulPropCount,
                                     &pProps);
    if (FAILED(hResult))
    {
        TraceResult ("CXPProvider::TransportLogon: Failed to get the logon props", hResult);
        goto ErrorExit;
    }

    // Fill in the logon UI structure
    CfgDialog.hInst    = m_hInstance;
    CfgDialog.hWnd     = (HWND)ulUIParam;
    CfgDialog.ppProps  = &pProps;
    CfgDialog.pSupObj  = pSupObj;
    CfgDialog.hUIMutex = hUIMutex;

    // In case we get MAPI_W_ERRORS_RETURNED, ignore it and reset 
    // to S_OK. Now display the logon configuration dialog
    if (MAPI_W_ERRORS_RETURNED == hResult)
    {
        if (PR_SMP_MAILBOX_ID       != pProps[MAILBOX_ID].ulPropTag  ||
            PR_SMP_CONNECTION_TYPE  != pProps[NET_CON].ulPropTag     ||
            PR_SMP_UPLOAD_TIME      != pProps[UPLOAD_TIME].ulPropTag ||
            PR_SMP_HEADERS_FILENAME != pProps[HEADER_FILE].ulPropTag ||
            PR_SMP_GET_HEADERS      != pProps[GET_HEADERS].ulPropTag)
        {
            TraceMessage ("CXPProvider::TransportLogon: Where are the provider properties?");
            hResult = MAPI_E_UNCONFIGURED;
            if (!(LOGON_NO_DIALOG & *pulFlags))
            {
                PrivInitialize3DCtl (m_hInstance);
                PrivateMessageBox (IDS_MSG_SERVICE_NOT_PROPERLY_CFG, (HWND)ulUIParam);
                PrivUninitialize3DCtl (m_hInstance);
            }
            goto ErrorExit;
        }

        if (PR_SMP_REMOTE_SERVER != pProps[SERVER_NAME].ulPropTag ||
            PR_SMP_MAILBOX_NAME != pProps[MAILBOX_NAME].ulPropTag ||
            PR_SMP_USER_NAME != pProps[USER_NAME].ulPropTag ||
            PR_SMP_MAILBOX_PASSWORD != pProps[PASSWORD].ulPropTag)
        {
            if (LOGON_NO_DIALOG & *pulFlags)
            {
                TraceMessage ("CXPProvider::TransportLogon: UI not allowed but it is needed");
                hResult = MAPI_E_UNCONFIGURED;
                goto ErrorExit;
            }
            PrivInitialize3DCtl (m_hInstance);
ReStartLogonDlg :
            if ((hResult = DoLogonDlg (&CfgDialog)))
            {
                goto ErrorExit;
            }
            hResult = pProfileObj->SetProps (4, pProps, NULL);
            if (hResult)
            {
                TraceResult ("CXPProvider::TransportLogon: Failed to set the properties", hResult);
                goto ErrorExit;
            }
        }
    }
    // Connect to the server with the stored information. If necessary (and allowed) display UI.
    hResult = DoServerLogon (&UserMBInfo,
                             pProps,
                             pProfileObj,
                             !(LOGON_NO_DIALOG & *pulFlags),
                             (HWND)ulUIParam,
                             FALSE,
                             0,
                             NULL,
                             TRUE);
    if (S_FALSE == hResult)
    {
        goto ReStartLogonDlg;
    }
    if (hResult)
    {
        goto ErrorExit;
    }

    // Once we have validated the remote credentials, terminate all connections
    TerminateRemoteConnections();

    try
    {
        // Allocate the IXPLogon-derived object. Initialize its data members with the necessary values
        pXPLogon = new CXPLogon (m_hInstance,
                                 pSupObj,
                                 pProps[HEADER_FILE].Value.LPSZ,
                                 pProps[GET_HEADERS].Value.b,
                                 &UserMBInfo,
                                 pProps[MAILBOX_ID].Value.l,
                                 pProps[SERVER_NAME].Value.LPSZ,
                                 hUIMutex);
        if (!pXPLogon)
        {
            // New failed, propably due to memory shortage
            TraceMessage ("CXPProvider::TransportLogon: Failed to allocate new CXPLogon object");
            hResult = E_OUTOFMEMORY;
        }
    }
    catch (CException & Exception)
    {
        hResult = Exception.GetError();
    }
    if (hResult)
    {
        goto ErrorExit;
    }
    hUIMutex = NULL;

    pXPLogon->CheckForUnfinishedDownloads();

    // Lock other threads because we are going to work on data that is 
    // global to all threads (sessions) using this transport
    EnterCriticalSection (&m_csTransport);
    // Check the mode in which MAPI is logging into our transport and set
    // the appropiate internal (this CXPLogon object) transport session flags
    pXPLogon->InitializeTransportStatusFlags (*pulFlags);
    // Initialize the transport ID prop array for this session
    hResult = pXPLogon->SetIdentityProps();
    if (!hResult)
    {
        // Build the transport status row for this session
        hResult = pXPLogon->InitializeStatusRow();
        if (!hResult)
        {
            // Set the session flags returned to MAPI by the transport
            pXPLogon->SetSessionFlags (pulFlags);
            // Set the upload delivery time to the current day, mo, yr and the hour and
            // minute from the config dialog saved in the profile. The profile info
            // is only valid for the hour and minute of day, the date can be old
            pXPLogon->SetUploadTime (pProps[UPLOAD_TIME].Value.ft);
            // Copy our allocated object back to the returned MAPI object pointer
            *ppXPLogon = (LPXPLOGON)pXPLogon;
        }
    }
    // Release the critical section
    LeaveCriticalSection (&m_csTransport);


ErrorExit:
    // Release pProfileObj. This object was AddRef() by MAPI before it 
    // came to us. The transport is in charge of cleaning it up (Release()ing it).
    if (pProfileObj)
    {
        pProfileObj->Release();
    }
    PrivUninitialize3DCtl (m_hInstance);

    if (hUIMutex)
    {
        CloseHandle (hUIMutex);
    }
    gpfnFreeBuffer (pProps);
    if (hResult)
    {   
        // Something failed, so clean the session if it has been allocated.
        // The Release() method of CXPLogon does the memory deallocation 
        // of this object. The destructor of CXPLogon does the rest of 
        // the clean up
        if (pXPLogon)
        {
            pXPLogon->Release();
        }
    }
    return hResult;
}                                        

// End of File for XPPROV.CPP
