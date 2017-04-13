/*+==========================================================================
  File:      FACTORY.CPP

  Summary:   Implementation file for the class factories of the PERTEXT
             server.  This server provides the TextPage COM component.
             For this component, IClassFactory is implemented in an
             appropriate class factory COM object: CFTextPage. The COM
             component that can be manufactured by this server is known
             outside the server by its CLSID: CLSID_TextPage.

             The class factories in this server use the CThreaded
             OwnThis mechanism to ensure mutually exclusive access by
             contending multiple threads.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial PERTEXT.HTM
             file. For more specific technical details on the internal
             workings see the comments dispersed throughout the module's
             source code.

  Classes:   CFTextPage.

  Functions: .

  Origin:    5-12-97: atrent - Editor-inheritance from FACTORY.CPP in
               the STOSERVE Tutorial Code Sample.

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
  We include OLECTL.H because it has definitions for connectable objects.
  We include APPUTIL.H because we will be building this DLL using
    the convenient Virtual Window and Dialog classes and other
    utility functions in the APPUTIL Library (ie, APPUTIL.LIB).
  We include IPAGES.H and PAGEGUID.H for the common page-related
    Interface class, GUID, and CLSID specifications.
  We include SERVER.H because it has the necessary internal class
    definitions for the server housing of this DLL.
  We include FACTORY.H because it has the necessary internal class factory
    declarations for this DLL component server.  Those factories we will be
    implementing in this module.
  We include CONNECT.H for object class declarations for the various
    connection point and connection COM objects used in PERTEXT.
  We include TEXTPAGE.H, for the object class declarations for the
    COTextPage COM object.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <olectl.h>
#include <apputil.h>
#include <ipages.h>
#include <pageguid.h>
#include "server.h"
#include "factory.h"
#include "connect.h"
#include "textpage.h"

/*---------------------------------------------------------------------------
  Implementation the CFTextPage Class Factory.  CFTextPage is the COM
  object class for the Class Factory that can manufacture COTextPage
  COM Components.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFTextPage::CFTextPage

  Summary:  CFTextPage Constructor. Note the member initializer:
            "m_ImpIClassFactory(this, pUnkOuter, pServer)" which is used
            to pass the 'this', pUnkOuter, and pServer pointers of this
            constructor function to the constructor executed in the
            instantiation of the CImpIClassFactory interface whose
            implementation is nested inside this present object class.

  Args:     IUnknown* pUnkOuter,
              Pointer to the the outer Unknown.  NULL means this COM Object
              is not being Aggregated.  Non NULL means it is being created
              on behalf of an outside COM object that is reusing it via
              aggregation.
            CServer* pServer)
              Pointer to the server's control object.

  Modifies: m_cRefs, m_pUnkOuter.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CFTextPage::CFTextPage(
  IUnknown* pUnkOuter,
  CServer* pServer) :
  m_ImpIClassFactory(this, pUnkOuter, pServer)
{
  // Zero the COM object's reference count.
  m_cRefs = 0;

  // No AddRef necessary if non-NULL, as we're nested.
  m_pUnkOuter = pUnkOuter;

  // Init the pointer to the server control object.
  m_pServer = pServer;

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFTextPage::~CFTextPage

  Summary:  CFTextPage Destructor.

  Args:     void

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CFTextPage::~CFTextPage(void)
{
  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFTextPage::QueryInterface

  Summary:  QueryInterface of the CFTextPage non-delegating
            IUnknown implementation.

  Args:     REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CFTextPage::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  HRESULT hr = E_NOINTERFACE;

  if (OwnThis())
  {
    *ppv = NULL;

    if (IID_IUnknown == riid)
      *ppv = this;
    else if (IID_IClassFactory == riid)
      *ppv = &m_ImpIClassFactory;

    if (NULL != *ppv)
    {
      // We've handed out a pointer to the interface so obey the COM rules
      // and AddRef the reference count.
      ((LPUNKNOWN)*ppv)->AddRef();
      hr = NOERROR;
    }

    UnOwnThis();
  }

  return (hr);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFTextPage::AddRef

  Summary:  AddRef of the CFTextPage non-delegating IUnknown implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CFTextPage::AddRef(void)
{
  ULONG cRefs;

  if (OwnThis())
  {
    cRefs = ++m_cRefs;

    UnOwnThis();
  }

  return cRefs;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFTextPage::Release

  Summary:  Release of the CFTextPage non-delegating IUnknown implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CFTextPage::Release(void)
{
  ULONG cRefs;

  if (OwnThis())
  {
    cRefs = --m_cRefs;

    if (0 == cRefs)
    {
      // We've reached a zero reference count for this COM object.
      // So we tell the server housing to decrement its global object
      // count so that the server will be unloaded if appropriate.
      if (NULL != m_pServer)
        m_pServer->ObjectsDown();

      // We artificially bump the main ref count to prevent reentrancy
      // via the main object destructor.  Not really needed in this
      // CFPageList but a good practice because we are aggregatable and
      // may at some point in the future add something entertaining like
      // some Releases to the CFPageList destructor.
      m_cRefs++;
      UnOwnThis();
      delete this;
    }
    else
      UnOwnThis();
  }

  return cRefs;
}


/*---------------------------------------------------------------------------
  CFTextPage's nested implementation of the IClassFactory interface
  including Constructor, Destructor, QueryInterface, AddRef, Release,
  CreateInstance, and LockServer methods.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFTextPage::CImpIClassFactory::CImpIClassFactory

  Summary:  Constructor for the CImpIClassFactory interface instantiation.

  Args:     CFTextPage* pCO,
              Back pointer to the parent outer object.
            IUnknown* pUnkOuter,
              Pointer to the outer Unknown.  For delegation.
            CServer* pServer)
              Pointer to the server's control object.

  Modifies: m_pCO, m_pUnkOuter, m_pServer.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CFTextPage::CImpIClassFactory::CImpIClassFactory(
  CFTextPage* pCO,
  IUnknown* pUnkOuter,
  CServer* pServer)
{
  // Init the Main Object Pointer to point to the parent object.
  m_pCO = pCO;

  // Init the pointer to the server control object.
  m_pServer = pServer;

  // Init the CImpIClassFactory interface's delegating Unknown pointer.
  // We use the Main Object pointer for IUnknown delegation here if we are
  // not being aggregated. If we are being aggregated we use the supplied
  // pUnkOuter for IUnknown delegation. In either case the pointer
  // assignment requires no AddRef because the CImpIClassFactory lifetime
  // is quaranteed by the lifetime of the parent object in which
  // CImpIClassFactory is nested.
  if (NULL == pUnkOuter)
    m_pUnkOuter = pCO;
  else
    m_pUnkOuter = pUnkOuter;

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFTextPage::CImpIClassFactory::~CImpIClassFactory

  Summary:  Destructor for the CImpIClassFactory interface instantiation.

  Args:     void

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CFTextPage::CImpIClassFactory::~CImpIClassFactory(void)
{
  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFTextPage::CImpIClassFactory::QueryInterface

  Summary:  The QueryInterface IUnknown member of this IClassFactory
            interface implementation that delegates to m_pUnkOuter,
            whatever it is.

  Args:     REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
              Returned by the delegated outer QueryInterface call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CFTextPage::CImpIClassFactory::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  // Delegate this call to the outer object's QueryInterface.
  return m_pUnkOuter->QueryInterface(riid, ppv);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFTextPage::CImpIClassFactory::AddRef

  Summary:  The AddRef IUnknown member of this IClassFactory interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Returns:  ULONG
              Returned by the delegated outer AddRef call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CFTextPage::CImpIClassFactory::AddRef(void)
{
  // Delegate this call to the outer object's AddRef.
  return m_pUnkOuter->AddRef();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFTextPage::CImpIClassFactory::Release

  Summary:  The Release IUnknown member of this IClassFactory interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Returns:  ULONG
              Returned by the delegated outer Release call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CFTextPage::CImpIClassFactory::Release(void)
{
  // Delegate this call to the outer object's Release.
  return m_pUnkOuter->Release();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFTextPage::CImpIClassFactory::CreateInstance

  Summary:  The CreateInstance member method of this IClassFactory
            interface implementation.  Creates an instance of the
            COTextPage COM component.

  Args:     IUnknown* pUnkOuter,
              [in] Pointer to the controlling IUnknown.
            REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CFTextPage::CImpIClassFactory::CreateInstance(
               IUnknown* pUnkOuter,
               REFIID riid,
               PPVOID ppv)
{
  HRESULT hr = E_FAIL;
  COTextPage* pCO = NULL;

  // NULL the output pointer.
  *ppv = NULL;

  // If the creation call is requesting aggregation (pUnkOuter != NULL),
  // the COM rules state the IUnknown interface MUST also be concomitantly
  // be requested.  If it is not so requested (riid != IID_IUnknown) then
  // an error must be returned indicating that no aggregate creation of
  // the CFTextPage COM Object can be performed.
  if (NULL != pUnkOuter && riid != IID_IUnknown)
    hr = CLASS_E_NOAGGREGATION;
  else
  {
    // Instantiate a COTextPage COM Object.
    pCO = new COTextPage(pUnkOuter, m_pServer);
    if (NULL != pCO)
    {
      // Create and initialize any subordinate objects. Rig connectivity.
      hr = pCO->Init();
      if (SUCCEEDED(hr))
      {
        // We successfully created the new COM object so tell the server
        // to increment its global server object count to help ensure
        // that the server remains loaded until this partial creation
        // of a COM component is completed.
        m_pServer->ObjectsUp();

        // We QueryInterface this new COM Object not only to deposit the
        // main interface pointer to the caller's pointer variable, but to
        // also automatically bump the Reference Count on the new COM
        // Object after handing out this reference to it.
        hr = pCO->QueryInterface(riid, (PPVOID)ppv);
        if (FAILED(hr))
        {
          m_pServer->ObjectsDown();
          delete pCO;
        }
      }
      else
        delete pCO;
    }
    else
      hr = E_OUTOFMEMORY;
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFTextPage::CImpIClassFactory::LockServer

  Summary:  The LockServer member method of this IClassFactory interface
            implementation.

  Args:     BOOL bLock)
              [in] Flag determining whether to Lock or Unlock the server.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CFTextPage::CImpIClassFactory::LockServer(
               BOOL bLock)
{
  HRESULT hr = NOERROR;

  if (bLock)
    m_pServer->Lock();
  else
    m_pServer->Unlock();

  return hr;
}
