/*+==========================================================================
  File:      SAMPLE.CPP

  Summary:   Implementation file for the COCarSample sample utility COM
             object.  This object exposes the ISample interface
             that is used to allow better integration of server with
             client as a code sample (eg, set up trace logging from
             server to client's log display).

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial DLLSERVE.HTM file.
             For more specific technical details on the internal workings
             see the comments dispersed throughout the module's source code.

  Classes:   COCarSample.

  Functions:

  Origin:    9-11-95: atrent - Editor-inheritance from COMOBJ.CPP in
               the COMOBJ Tutorial Code Sample.

----------------------------------------------------------------------------
  This file is part of the Microsoft COM Tutorial Code Samples.

  Copyright (C) Microsoft Corporation, 1997.  All rights reserved.

  This source code is intended only as a supplement to Microsoft
  Development Tools and/or on-line documentation.  See these other
  materials for detailed information regarding Microsoft code samples.

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.
==========================================================================+*/

/*---------------------------------------------------------------------------
  We include WINDOWS.H for all Win32 applications.
  We include OLE2.H because we will be calling the COM/OLE Libraries.
  We include APPUTIL.H because we will be building this DLL using
    the convenient Virtual Window and Dialog classes and other
    utility functions in the APPUTIL Library (ie, APPUTIL.LIB).
  We include ICARS.H and CARGUIDS.H for the common car-related Interface
    class, GUID, and CLSID specifications.
  We include SERVER.H for the object class declarations for the
    CServer server control object.
  We include SAMPLE.H for the object class declarations for the
    COCarSample COM object.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <apputil.h>
#include <icars.h>
#include <carguids.h>
#include "server.h"
#include "sample.h"

/*---------------------------------------------------------------------------
  Implementation the COCarSample COM object.  Used to expose a utility
  server interface for the server as a code sample.  COCarSample exposes
  the ISample interface.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCarSample::COCarSample

  Summary:  COCarSample Constructor. Note the member initializer:
            "m_ImpISample(this, pUnkOuter, pServer)" which is used to pass
            the 'this', pUnkOuter, and pServer pointers of this
            constructor function to the constructor in the instantiation
            of the implementation of the CImpISample interface (which is
            nested inside this present COCarSample Object Class).

  Args:     IUnknown* pUnkOuter,
              Pointer to the the outer Unknown.  NULL means this COM Object
              is not being Aggregated.  Non NULL means it is being created
              on behalf of an outside COM object that is reusing it via
              aggregation.
            CServer* pServer
              Pointer to the server's control object.

  Modifies: m_cRefs, m_pUnkOuter.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COCarSample::COCarSample(
  IUnknown* pUnkOuter,
  CServer* pServer) :
  m_ImpISample(this, pUnkOuter, pServer)
{
  // Zero the COM object's reference count.
  m_cRefs = 0;

  // No AddRef necessary if non-NULL, as we're nested.
  m_pUnkOuter = pUnkOuter;

  // Init the pointer to the server's control object.
  m_pServer = pServer;

  LOGF1("S: COCarSample Constructor. m_pUnkOuter=0x%X.", m_pUnkOuter);

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCarSample::~COCarSample

  Summary:  COCarSample Destructor.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COCarSample::~COCarSample(void)
{
  LOG("S: COCarSample::Destructor.");

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCarSample::QueryInterface

  Summary:  QueryInterface of the COCarSample non-delegating
            IUnknown implementation.

  Args:     REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Modifies: .

  Returns:  HRESULT
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COCarSample::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  HRESULT hr = E_NOINTERFACE;
  *ppv = NULL;

  if (IID_IUnknown == riid)
  {
    *ppv = this;
    LOG("S: COCarSample::QueryInterface. 'this' pIUnknown returned.");
  }
  else if (IID_ISample == riid)
  {
    *ppv = &m_ImpISample;
    LOG("S: COCarSample::QueryInterface. pISample returned.");
  }

  if (NULL != *ppv)
  {
    // We've handed out a pointer to the interface so obey the COM rules
    // and AddRef the reference count.
    ((LPUNKNOWN)*ppv)->AddRef();
    hr = NOERROR;
  }

  return (hr);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCarSample::AddRef

  Summary:  AddRef of the COCarSample non-delegating IUnknown implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COCarSample::AddRef(void)
{
  m_cRefs++;

  LOGF1("S: COCarSample::AddRef. New cRefs=%i.", m_cRefs);

  return m_cRefs;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCarSample::Release

  Summary:  Release of the COCarSample non-delegating IUnknown
            implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COCarSample::Release(void)
{
  m_cRefs--;

  LOGF1("S: COCarSample::Release. New cRefs=%i.", m_cRefs);

  if (0 == m_cRefs)
  {
    // We've reached a zero reference count for this COM object.
    // So we tell the server housing to decrement its global object
    // count so that the server will be unloaded if appropriate.
    if (NULL != m_pServer)
      m_pServer->ObjectsDown();

    // We artificially bump the main ref count to prevent reentrancy
    // via the main object destructor.  Not really needed in this
    // COCarSample but a good practice because we are aggregatable and
    // may at some point in the future add something entertaining like
    // some Releases to the COCarSample destructor.
    m_cRefs++;
    delete this;
  }

  return m_cRefs;
}


/*---------------------------------------------------------------------------
  COCarSample's nested implementation of the ISample interface
  including Constructor, Destructor, QueryInterface, AddRef, Release,
  Init, and AboutBox methods.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCarSample::CImpISample::CImpISample

  Summary:  Constructor for the CImpISample interface instantiation.

  Args:     COCarSample* pBackObj,
              Back pointer to the parent outer object.
            IUnknown* pUnkOuter,
              Pointer to the outer Unknown.  For delegation.
            CServer* pServer)
              Pointer to the server's control object.

  Modifies: m_cRefI, m_pBackObj, m_pUnkOuter, m_pServer.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COCarSample::CImpISample::CImpISample(
  COCarSample* pBackObj,
  IUnknown* pUnkOuter,
  CServer* pServer)
{
  // Init the Interface Ref Count (used for debugging only).
  m_cRefI = 0;

  // Init the Back Object Pointer to point to the outer object.
  m_pBackObj = pBackObj;

  // Init the pointer to the server control object.
  m_pServer = pServer;

  // Init the CImpISample interface's delegating Unknown pointer.  We use
  // the Back Object pointer for IUnknown delegation here if we are not
  // being aggregated.  If we are being aggregated we use the supplied
  // pUnkOuter for IUnknown delegation.  In either case the pointer
  // assignment requires no AddRef because the CImpISample lifetime is
  // quaranteed by the lifetime of the parent object in which
  // CImpISample is nested.
  if (NULL == pUnkOuter)
  {
    m_pUnkOuter = pBackObj;
    LOG("S: COCarSample::CImpISample Constructor. Non-Aggregating.");
  }
  else
  {
    m_pUnkOuter = pUnkOuter;
    LOG("S: COCarSample::CImpISample Constructor. Aggregating.");
  }

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCarSample::CImpISample::~CImpISample

  Summary:  Destructor for the CImpISample interface instantiation.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COCarSample::CImpISample::~CImpISample(void)
{
  LOG("S: COCarSample::CImpISample Destructor.");

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCarSample::CImpISample::QueryInterface

  Summary:  The QueryInterface IUnknown member of this ISample interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Modifies: .

  Returns:  HRESULT
              Returned by the delegated outer QueryInterface call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COCarSample::CImpISample::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  LOG("S: COCarSample::CImpISample::QueryInterface. Delegating.");

  // Delegate this call to the outer object's QueryInterface.
  return m_pUnkOuter->QueryInterface(riid, ppv);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCarSample::CImpISample::AddRef

  Summary:  The AddRef IUnknown member of this ISample interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: m_cRefI.

  Returns:  ULONG
              Returned by the delegated outer AddRef call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COCarSample::CImpISample::AddRef(void)
{
  // Increment the Interface Reference Count.
  ++m_cRefI;

  LOGF1("S: COCarSample::CImpISample::Addref. Delegating. New cI=%i.", m_cRefI);

  // Delegate this call to the outer object's AddRef.
  return m_pUnkOuter->AddRef();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCarSample::CImpISample::Release

  Summary:  The Release IUnknown member of this ISample interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: .

  Returns:  ULONG
              Returned by the delegated outer Release call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COCarSample::CImpISample::Release(void)
{
  // Decrement the Interface Reference Count.
  --m_cRefI;

  LOGF1("S: COCarSample::CImpISample::Release. Delegating. New cI=%i.", m_cRefI);

  // Delegate this call to the outer object's Release.
  return m_pUnkOuter->Release();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCarSample::CImpISample::Init

  Summary:  Initialize the COCarSample object to enable trace logging
            from server to client.  This includes passing in a pointer
            that points the Client EXE's MsgLog facility so that the
            LOG* trace logging macros in the server will be logged in
            the Client's message log window.

  Args:     HWND hWndParent
              [in] Handle of a client's parent owning window.
            PVOID pvMsgLog
              [in] Pointer to the Client's MsgLog object.  If NULL
              then setup independent logging window for this DLL.

  Modifies: .

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COCarSample::CImpISample::Init(
               HWND hWndParent,
               PVOID pvMsgLog)
{
  HRESULT hr = NOERROR;

  // Init this DLL's MsgBox facility.
  g_pServer->m_pMsgBox->Init(g_pServer->m_hDllInst, hWndParent);

  if (NULL != pvMsgLog)
  {
    // Set up a pointer to the client EXE's Message Log facility so
    // that any LOG macros used in this DLL will log to the host EXE's
    // log window.
    g_pMsgLog = (CMsgLog *)pvMsgLog;
    LOG("S: --- DLLSERVE.DLL now logging to Client ---");
  }
  else
  {
    // But if pvMsgLog is passed in as NULL then Create an independent
    // logging facility for this DLL (use the client EXE's main window
    // as the parent window).
    CMsgLog* pMsgLog = new CMsgLog;

    if (NULL != pMsgLog)
    {
      if (pMsgLog->Create(g_pServer->m_hDllInst, hWndParent, FALSE))
      {
        g_pMsgLog = pMsgLog;
        LOG("S: --- DLLSERVE.DLL now logging ---");
      }
      else
        delete pMsgLog;
    }
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCarSample::CImpISample::AboutBox

  Summary:  The AboutBox method commands the Server to display its own
            About dialog box (using resources stored in this DLL itself.

  Args:     HWND hWnd
              [in] Handle of window (ie of client) that is to be parent of
              the About dialog window.

  Modifies: .

  Returns:  HRESULT
              Standard result code.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT COCarSample::CImpISample::AboutBox(
          HWND hWnd)
{
  HRESULT hr = NOERROR;

  LOG("S: COCarSample::CImpISample::AboutBox.");

  // Define one of those nifty APPUTIL CAboutBox modal dialog objects.
  CAboutBox dlgAboutBox;

  // Show the standard About Box dialog for this DLL by telling the dialog
  // C++ object to show itself by invoking its ShowDialog method.
  // Pass it this DLL instance and the parent window handle.  Use a dialog
  // resource ID for the dialog stored in this DLL module's resources.
  dlgAboutBox.ShowDialog(
    m_pServer->m_hDllInst,
    MAKEINTRESOURCE(IDD_ABOUTBOX),
    hWnd);

  return hr;
}
