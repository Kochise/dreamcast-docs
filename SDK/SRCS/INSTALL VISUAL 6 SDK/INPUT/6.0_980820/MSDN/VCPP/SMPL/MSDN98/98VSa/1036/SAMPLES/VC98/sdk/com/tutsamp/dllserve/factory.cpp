/*+==========================================================================
  File:      FACTORY.CPP

  Summary:   Implementation file for the ClassFactories of the DLLSERVE
             server.  This server provides several Car-related COM
             Components: Car, UtilityCar, and CruiseCar.  For each of
             these components, IClassFactory is implemented in
             appropriate ClassFactory COM objects: CFCar, CFUtilityCar,
             and CFCruiseCar.  In addition a CFCarSample class factory
             is included to provide a component with the Code Sample
             utility interface (ISample).  This interface is primarily
             for use within the code samples for the purposes of setting
             them up as samples (eg, setting up the server so that it
             trace logs to the client's trace log facility).  The COM
             Components that can be manufactured by this server are
             known outside the server by their respective CLSIDs:
             CLSID_DllCar, CLSID_DllUtilityCar, CLSID_DllCruiseCar, and
             CLSID_DllCarSample.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial DLLSERVE.HTM file.
             For more specific technical details on the internal workings
             see the comments dispersed throughout the module's source code.

  Classes:   CFCar, CFUtilityCar, CFCruiseCar, CFCarSample.

  Functions: .

  Origin:    9-11-95: atrent - Editor-inheritance from CAR.CPP in
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
  We include SERVER.H because it has the necessary internal class and
    resource definitions for this DLL.
  We include FACTORY.H because it has the necessary internal class factory
    declarations for this DLL component server.  Those factories we will be
    implementing in this module.
  We include CAR.H, UTILCAR,H, and, CRUCAR.H for the object class
    declarations for the COCar, COUtilityCar, and COCruiseCar COM objects.
  We include SAMPLE.H for the utility Sample class COCarSample.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <apputil.h>
#include <icars.h>
#include <carguids.h>
#include "server.h"
#include "factory.h"
#include "car.h"
#include "utilcar.h"
#include "crucar.h"
#include "sample.h"

/*---------------------------------------------------------------------------
  Implementation the CFCar Class Factory.  CFCar is the COM
  object class for the Class Factory that can manufacture COCar
  COM Components.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFCar::CFCar

  Summary:  CFCar Constructor. Note the member initializer:
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
CFCar::CFCar(
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

  LOGF1("S: CFCar Constructor. m_pUnkOuter=0x%X.", m_pUnkOuter);

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFCar::~CFCar

  Summary:  CFCar Destructor.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CFCar::~CFCar(void)
{
  LOG("S: CFCar::Destructor.");

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFCar::QueryInterface

  Summary:  QueryInterface of the CFCar non-delegating
            IUnknown implementation.

  Args:     REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CFCar::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  HRESULT hr = E_NOINTERFACE;
  *ppv = NULL;

  if (IID_IUnknown == riid)
  {
    *ppv = this;
    LOG("S: CFCar::QueryInterface. 'this' pIUnknown returned.");
  }
  else if (IID_IClassFactory == riid)
  {
    *ppv = &m_ImpIClassFactory;
    LOG("S: CFCar::QueryInterface. pIClassFactory returned.");
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
  Method:   CFCar::AddRef

  Summary:  AddRef of the CFCar non-delegating IUnknown implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CFCar::AddRef(void)
{
  m_cRefs++;

  LOGF1("S: CFCar::AddRef. New cRefs=%i.", m_cRefs);

  return m_cRefs;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFCar::Release

  Summary:  Release of the CFCar non-delegating IUnknown implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CFCar::Release(void)
{
  m_cRefs--;

  LOGF1("S: CFCar::Release. New cRefs=%i.", m_cRefs);

  if (0 == m_cRefs)
  {
    // We've reached a zero reference count for this COM object.
    // So we tell the server housing to decrement its global object
    // count so that the server will be unloaded if appropriate.
    if (NULL != m_pServer)
      m_pServer->ObjectsDown();

    // We artificially bump the main ref count to prevent reentrancy
    // via the main object destructor.  Not really needed in this
    // CFCar but a good practice because we are aggregatable and
    // may at some point in the future add something entertaining like
    // some Releases to the CFCar destructor.
    m_cRefs++;
    delete this;
  }

  return m_cRefs;
}


/*---------------------------------------------------------------------------
  CFCar's nested implementation of the IClassFactory interface
  including Constructor, Destructor, QueryInterface, AddRef, Release,
  CreateInstance, and LockServer methods.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFCar::CImpIClassFactory::CImpIClassFactory

  Summary:  Constructor for the CImpIClassFactory interface instantiation.

  Args:     CFCar* pBackObj,
              Back pointer to the parent outer object.
            IUnknown* pUnkOuter,
              Pointer to the outer Unknown.  For delegation.
            CServer* pServer)
              Pointer to the server's control object.

  Modifies: m_cRefI, m_pBackObj, m_pUnkOuter, m_pServer.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CFCar::CImpIClassFactory::CImpIClassFactory(
  CFCar* pBackObj,
  IUnknown* pUnkOuter,
  CServer* pServer)
{
  // Init the Interface Ref Count (used for debugging only).
  m_cRefI = 0;

  // Init the Back Object Pointer to point to the parent object.
  m_pBackObj = pBackObj;

  // Init the pointer to the server control object.
  m_pServer = pServer;

  // Init the CImpIClassFactory interface's delegating Unknown pointer.
  // We use the Back Object pointer for IUnknown delegation here if we are
  // not being aggregated.  If we are being aggregated we use the supplied
  // pUnkOuter for IUnknown delegation.  In either case the pointer
  // assignment requires no AddRef because the CImpIClassFactory lifetime is
  // quaranteed by the lifetime of the parent object in which
  // CImpIClassFactory is nested.
  if (NULL == pUnkOuter)
  {
    m_pUnkOuter = pBackObj;
    LOG("S: CFCar::CImpIClassFactory Constructor. Non-Aggregating.");
  }
  else
  {
    m_pUnkOuter = pUnkOuter;
    LOG("S: CFCar::CImpIClassFactory Constructor. Aggregating.");
  }

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFCar::CImpIClassFactory::~CImpIClassFactory

  Summary:  Destructor for the CImpIClassFactory interface instantiation.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CFCar::CImpIClassFactory::~CImpIClassFactory(void)
{
  LOG("S: CFCar::CImpIClassFactory Destructor.");

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFCar::CImpIClassFactory::QueryInterface

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
STDMETHODIMP CFCar::CImpIClassFactory::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  LOG("S: CFCar::CImpIClassFactory::QueryInterface. Delegating.");

  // Delegate this call to the outer object's QueryInterface.
  return m_pUnkOuter->QueryInterface(riid, ppv);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFCar::CImpIClassFactory::AddRef

  Summary:  The AddRef IUnknown member of this IClassFactory interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: m_cRefI.

  Returns:  ULONG
              Returned by the delegated outer AddRef call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CFCar::CImpIClassFactory::AddRef(void)
{
  // Increment the Interface Reference Count.
  ++m_cRefI;

  LOGF1("S: CFCar::CImpIClassFactory::Addref. Delegating. New cI=%i.",m_cRefI);

  // Delegate this call to the outer object's AddRef.
  return m_pUnkOuter->AddRef();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFCar::CImpIClassFactory::Release

  Summary:  The Release IUnknown member of this IClassFactory interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: .

  Returns:  ULONG
              Returned by the delegated outer Release call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CFCar::CImpIClassFactory::Release(void)
{
  // Decrement the Interface Reference Count.
  --m_cRefI;

  LOGF1("S: CFCar::CImpIClassFactory::Release. Delegating. New cI=%i.",m_cRefI);

  // Delegate this call to the outer object's Release.
  return m_pUnkOuter->Release();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFCar::CImpIClassFactory::CreateInstance

  Summary:  The CreateInstance member method of this IClassFactory interface
            implementation.  Creates an instance of the COCar COM
            component.

  Args:     IUnknown* pUnkOuter,
              [in] Pointer to the controlling IUnknown.
            REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppvCob)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CFCar::CImpIClassFactory::CreateInstance(
               IUnknown* pUnkOuter,
               REFIID riid,
               PPVOID ppv)
{
  HRESULT hr = E_FAIL;
  COCar* pCob = NULL;

  LOGF1("S: CFCar::CImpIClassFactory::CreateInstance. pUnkOuter=0x%X.",pUnkOuter);

  // NULL the output pointer.
  *ppv = NULL;

  // If the creation call is requesting aggregation (pUnkOuter != NULL),
  // the COM rules state the IUnknown interface MUST also be concomitantly
  // be requested.  If it is not so requested (riid != IID_IUnknown) then
  // an error must be returned indicating that no aggregate creation of
  // the CFCar COM Object can be performed.
  if (NULL != pUnkOuter && riid != IID_IUnknown)
    hr = CLASS_E_NOAGGREGATION;
  else
  {
    // Instantiate a COCar COM Object.
    pCob = new COCar(pUnkOuter, m_pServer);
    if (NULL != pCob)
    {
      // We initially created the new COM object so tell the server
      // to increment its global server object count to help ensure
      // that the server remains loaded until this partial creation
      // of a COM component is completed.
      m_pServer->ObjectsUp();

      // We QueryInterface this new COM Object not only to deposit the
      // main interface pointer to the caller's pointer variable, but to
      // also automatically bump the Reference Count on the new COM
      // Object after handing out this reference to it.
      hr = pCob->QueryInterface(riid, (PPVOID)ppv);
      if (FAILED(hr))
      {
        m_pServer->ObjectsDown();
        delete pCob;
      }
    }
    else
      hr = E_OUTOFMEMORY;
  }

  if (SUCCEEDED(hr))
  {
    LOGF1("S: CFCar::CImpIClassFactory::CreateInstance Succeeded. *ppv=0x%X.",*ppv);
  }
  else
  {
    LOG("S: CFCar::CImpIClassFactory::CreateInstance Failed.");
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFCar::CImpIClassFactory::LockServer

  Summary:  The LockServer member method of this IClassFactory interface
            implementation.

  Args:     BOOL fLock)
              [in] Flag determining whether to Lock or Unlock the server.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CFCar::CImpIClassFactory::LockServer(
               BOOL fLock)
{
  HRESULT hr = NOERROR;

  LOG("S: CFCar::CImpIClassFactory::LockServer.");

  if (fLock)
    m_pServer->Lock();
  else
    m_pServer->Unlock();

  return hr;
}


/*---------------------------------------------------------------------------
  Implementation the CFUtilityCar Class Factory.  CFUtilityCar is the COM
  object class for the Class Factory that can manufacture COUtilityCar
  COM Components.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFUtilityCar::CFUtilityCar

  Summary:  CFUtilityCar Constructor. Note the member initializer:
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
CFUtilityCar::CFUtilityCar(
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

  LOGF1("S: CFUtilityCar Constructor. m_pUnkOuter=0x%X.", m_pUnkOuter);

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFUtilityCar::~CFUtilityCar

  Summary:  CFUtilityCar Destructor.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CFUtilityCar::~CFUtilityCar(void)
{
  LOG("S: CFUtilityCar::Destructor.");

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFUtilityCar::QueryInterface

  Summary:  QueryInterface of the CFUtilityCar non-delegating
            IUnknown implementation.

  Args:     REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CFUtilityCar::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  HRESULT hr = E_NOINTERFACE;
  *ppv = NULL;

  if (IID_IUnknown == riid)
  {
    *ppv = this;
    LOG("S: CFUtilityCar::QueryInterface. 'this' pIUnknown returned.");
  }
  else if (IID_IClassFactory == riid)
  {
    *ppv = &m_ImpIClassFactory;
    LOG("S: CFUtilityCar::QueryInterface. pIClassFactory returned.");
  }

  if (NULL != *ppv)
  {
    // We've handed out a pointer to the interface so obey the COM rules
    //   and AddRef the reference count.
    ((LPUNKNOWN)*ppv)->AddRef();
    hr = NOERROR;
  }

  return (hr);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFUtilityCar::AddRef

  Summary:  AddRef of the CFUtilityCar non-delegating IUnknown implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CFUtilityCar::AddRef(void)
{
  m_cRefs++;

  LOGF1("S: CFUtilityCar::AddRef. New cRefs=%i.", m_cRefs);

  return m_cRefs;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFUtilityCar::Release

  Summary:  Release of the CFUtilityCar non-delegating IUnknown implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CFUtilityCar::Release(void)
{
  m_cRefs--;

  LOGF1("S: CFUtilityCar::Release. New cRefs=%i.", m_cRefs);

  if (0 == m_cRefs)
  {
    // We've reached a zero reference count for this COM object.
    // So we tell the server housing to decrement its global object
    // count so that the server will be unloaded if appropriate.
    if (NULL != m_pServer)
      m_pServer->ObjectsDown();

    // We artificially bump the main ref count to prevent reentrancy
    // via the main object destructor.  Not really needed in this
    // CFUtilityCar but a good practice because we are aggregatable and
    // may at some point in the future add something entertaining like
    // some Releases to the CFUtilityCar destructor.
    m_cRefs++;
    delete this;
  }

  return m_cRefs;
}


/*---------------------------------------------------------------------------
  CFUtilityCar's nested implementation of the IClassFactory interface
  including Constructor, Destructor, QueryInterface, AddRef, Release,
  CreateInstance, and LockServer methods.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFUtilityCar::CImpIClassFactory::CImpIClassFactory

  Summary:  Constructor for the CImpIClassFactory interface instantiation.

  Args:     CFUtilityCar* pBackObj,
              Back pointer to the parent outer object.
            IUnknown* pUnkOuter,
              Pointer to the outer Unknown.  For delegation.
            CServer* pServer)
              Pointer to the server's control object.

  Modifies: m_cRefI, m_pBackObj, m_pUnkOuter, m_pServer.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CFUtilityCar::CImpIClassFactory::CImpIClassFactory(
  CFUtilityCar* pBackObj,
  IUnknown* pUnkOuter,
  CServer* pServer)
{
  // Init the Interface Ref Count (used for debugging only).
  m_cRefI = 0;

  // Init the Back Object Pointer to point to the parent object.
  m_pBackObj = pBackObj;

  // Init the pointer to the server control object.
  m_pServer = pServer;

  // Init the CImpIClassFactory interface's delegating Unknown pointer.
  // We use the Back Object pointer for IUnknown delegation here if we are
  // not being aggregated.  If we are being aggregated we use the supplied
  // pUnkOuter for IUnknown delegation.  In either case the pointer
  // assignment requires no AddRef because the CImpIClassFactory lifetime is
  // quaranteed by the lifetime of the parent object in which
  // CImpIClassFactory is nested.
  if (NULL == pUnkOuter)
  {
    m_pUnkOuter = pBackObj;
    LOG("S: CFUtilityCar::CImpIClassFactory Constructor. Non-Aggregating.");
  }
  else
  {
    m_pUnkOuter = pUnkOuter;
    LOG("S: CFUtilityCar::CImpIClassFactory Constructor. Aggregating.");
  }

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFUtilityCar::CImpIClassFactory::~CImpIClassFactory

  Summary:  Destructor for the CImpIClassFactory interface instantiation.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CFUtilityCar::CImpIClassFactory::~CImpIClassFactory(void)
{
  LOG("S: CFUtilityCar::CImpIClassFactory Destructor.");

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFUtilityCar::CImpIClassFactory::QueryInterface

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
STDMETHODIMP CFUtilityCar::CImpIClassFactory::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  LOG("S: CFUtilityCar::CImpIClassFactory::QueryInterface. Delegating.");

  // Delegate this call to the outer object's QueryInterface.
  return m_pUnkOuter->QueryInterface(riid, ppv);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFUtilityCar::CImpIClassFactory::AddRef

  Summary:  The AddRef IUnknown member of this IClassFactory interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: m_cRefI.

  Returns:  ULONG
              Returned by the delegated outer AddRef call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CFUtilityCar::CImpIClassFactory::AddRef(void)
{
  // Increment the Interface Reference Count.
  ++m_cRefI;

  LOGF1("S: CFUtilityCar::CImpIClassFactory::Addref. Delegating. New cI=%i.",m_cRefI);

  // Delegate this call to the outer object's AddRef.
  return m_pUnkOuter->AddRef();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFUtilityCar::CImpIClassFactory::Release

  Summary:  The Release IUnknown member of this IClassFactory interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: .

  Returns:  ULONG
              Returned by the delegated outer Release call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CFUtilityCar::CImpIClassFactory::Release(void)
{
  // Decrement the Interface Reference Count.
  --m_cRefI;

  LOGF1("S: CFUtilityCar::CImpIClassFactory::Release. Delegating. New cI=%i.",m_cRefI);

  // Delegate this call to the outer object's Release.
  return m_pUnkOuter->Release();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFUtilityCar::CImpIClassFactory::CreateInstance

  Summary:  The CreateInstance member method of this IClassFactory interface
            implementation.  Creates an instance of the COUtilityCar COM
            component.

  Args:     IUnknown* pUnkOuter,
              [in] Pointer to the controlling IUnknown.
            REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppvCob)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CFUtilityCar::CImpIClassFactory::CreateInstance(
               IUnknown* pUnkOuter,
               REFIID riid,
               PPVOID ppv)
{
  HRESULT hr = E_FAIL;
  COUtilityCar* pCob = NULL;

  LOGF1("S: CFUtilityCar::CImpIClassFactory::CreateInstance. pUnkOuter=0x%X.",pUnkOuter);

  // If the creation call is requesting aggregation (pUnkOuter != NULL),
  // the COM rules state the IUnknown interface MUST also be concomitantly
  // be requested.  If it is not so requested ( riid != IID_IUnknown) then
  // an error must be returned indicating that no aggregate creation of
  // the COUtilityCar COM Object can be performed.
  if (NULL != pUnkOuter && riid != IID_IUnknown)
    hr = CLASS_E_NOAGGREGATION;
  else
  {
    // Instantiate a COUtilityCar COM Object.
    pCob = new COUtilityCar(pUnkOuter, m_pServer);
    if (NULL != pCob)
    {
      // We initially created the new COM object so tell the server
      // to increment its global server object count to help ensure
      // that the server remains loaded until this partial creation
      // of a COM component is completed.
      m_pServer->ObjectsUp();

      // If we have succeeded in instantiating the COM object we
      // initialize it to set up any subordinate objects.
      hr = pCob->Init();
      if (SUCCEEDED(hr))
      {
        // We QueryInterface this new COM Object not only to deposit the
        // main interface pointer to the caller's pointer variable, but to
        // also automatically bump the Reference Count on the new COM
        // Object after handing out this reference to it.
        hr = pCob->QueryInterface(riid, (PPVOID)ppv);
      }

      if (FAILED(hr))
      {
        m_pServer->ObjectsDown();
        delete pCob;
      }
    }
    else
      hr = E_OUTOFMEMORY;
  }

  if (SUCCEEDED(hr))
  {
    LOGF1("S: CFUtilityCar::CImpIClassFactory::CreateInstance Succeeded. *ppv=0x%X.",*ppv);
  }
  else
  {
    LOG("S: CFUtilityCar::CImpIClassFactory::CreateInstance Failed.");
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFUtilityCar::CImpIClassFactory::LockServer

  Summary:  The LockServer member method of this IClassFactory interface
            implementation.

  Args:     BOOL fLock)
              [in] Flag determining whether to Lock or Unlock the server.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CFUtilityCar::CImpIClassFactory::LockServer(
               BOOL fLock)
{
  HRESULT hr = NOERROR;

  LOG("S: CFUtilityCar::CImpIClassFactory::LockServer.");

  if (fLock)
    m_pServer->Lock();
  else
    m_pServer->Unlock();

  return hr;
}


/*---------------------------------------------------------------------------
  Implementation the CFCruiseCar Class Factory.  CFCruiseCar is the COM
  object class for the Class Factory that can manufacture COCruiseCar
  COM Components.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFCruiseCar::CFCruiseCar

  Summary:  CFCruiseCar Constructor. Note the member initializer:
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

  Modifies: m_cRefs, m_pUnkOuter, m_pServer.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CFCruiseCar::CFCruiseCar(
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

  LOGF1("S: CFCruiseCar Constructor. m_pUnkOuter=0x%X.", m_pUnkOuter);

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFCruiseCar::~CFCruiseCar

  Summary:  CFCruiseCar Destructor.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CFCruiseCar::~CFCruiseCar(void)
{
  LOG("S: CFCruiseCar::Destructor.");

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFCruiseCar::QueryInterface

  Summary:  QueryInterface of the CFCruiseCar non-delegating
            IUnknown implementation.

  Args:     REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CFCruiseCar::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  HRESULT hr = E_NOINTERFACE;
  *ppv = NULL;

  if (IID_IUnknown == riid)
  {
    *ppv = this;
    LOG("S: CFCruiseCar::QueryInterface. 'this' pIUnknown returned.");
  }
  else if (IID_IClassFactory == riid)
  {
    *ppv = &m_ImpIClassFactory;
    LOG("S: CFCruiseCar::QueryInterface. pIClassFactory returned.");
  }

  if (NULL != *ppv)
  {
    // We've handed out a pointer to the interface so obey the COM rules
    //   and AddRef the reference count.
    ((LPUNKNOWN)*ppv)->AddRef();
    hr = NOERROR;
  }

  return (hr);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFCruiseCar::AddRef

  Summary:  AddRef of the CFCruiseCar non-delegating IUnknown implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CFCruiseCar::AddRef(void)
{
  m_cRefs++;

  LOGF1("S: CFCruiseCar::AddRef. New cRefs=%i.", m_cRefs);

  return m_cRefs;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFCruiseCar::Release

  Summary:  Release of the CFCruiseCar non-delegating IUnknown implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CFCruiseCar::Release(void)
{
  m_cRefs--;

  LOGF1("S: CFCruiseCar::Release. New cRefs=%i.", m_cRefs);

  if (0 == m_cRefs)
  {
    // We've reached a zero reference count for this COM object.
    // So we tell the server housing to decrement its global object
    // count so that the server will be unloaded if appropriate.
    if (NULL != m_pServer)
      m_pServer->ObjectsDown();

    // We artificially bump the main ref count to prevent reentrancy
    // via the main object destructor.  Not really needed in this
    // CFCruiseCar but a good practice because we are aggregatable and
    // may at some point in the future add something entertaining like
    // some Releases to the CFCruiseCar destructor.
    m_cRefs++;
    delete this;
  }

  return m_cRefs;
}


/*---------------------------------------------------------------------------
  CFCruiseCar's nested implementation of the IClassFactory interface
  including Constructor, Destructor, QueryInterface, AddRef, Release,
  CreateInstance, and LockServer methods.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFCruiseCar::CImpIClassFactory::CImpIClassFactory

  Summary:  Constructor for the CImpIClassFactory interface instantiation.

  Args:     CFCruiseCar* pBackObj,
              Back pointer to the parent outer object.
            IUnknown* pUnkOuter,
              Pointer to the outer Unknown.  For delegation.
            CServer* pServer)
              Pointer to the server's control object.

  Modifies: m_cRefI, m_pBackObj, m_pUnkOuter, m_pServer.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CFCruiseCar::CImpIClassFactory::CImpIClassFactory(
  CFCruiseCar* pBackObj,
  IUnknown* pUnkOuter,
  CServer* pServer)
{
  // Init the Interface Ref Count (used for debugging only).
  m_cRefI = 0;

  // Init the Back Object Pointer to point to the parent object.
  m_pBackObj = pBackObj;

  // Init the pointer to the server control object.
  m_pServer = pServer;

  // Init the CImpIClassFactory interface's delegating Unknown pointer.
  // We use the Back Object pointer for IUnknown delegation here if we are
  // not being aggregated.  If we are being aggregated we use the supplied
  // pUnkOuter for IUnknown delegation.  In either case the pointer
  // assignment requires no AddRef because the CImpIClassFactory lifetime is
  // quaranteed by the lifetime of the parent object in which
  // CImpIClassFactory is nested.
  if (NULL == pUnkOuter)
  {
    m_pUnkOuter = pBackObj;
    LOG("S: CFCruiseCar::CImpIClassFactory Constructor. Non-Aggregating.");
  }
  else
  {
    m_pUnkOuter = pUnkOuter;
    LOG("S: CFCruiseCar::CImpIClassFactory Constructor. Aggregating.");
  }

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFCruiseCar::CImpIClassFactory::~CImpIClassFactory

  Summary:  Destructor for the CImpIClassFactory interface instantiation.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CFCruiseCar::CImpIClassFactory::~CImpIClassFactory(void)
{
  LOG("S: CFCruiseCar::CImpIClassFactory Destructor.");

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFCruiseCar::CImpIClassFactory::QueryInterface

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
STDMETHODIMP CFCruiseCar::CImpIClassFactory::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  LOG("S: CFCruiseCar::CImpIClassFactory::QueryInterface. Delegating.");

  // Delegate this call to the outer object's QueryInterface.
  return m_pUnkOuter->QueryInterface(riid, ppv);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFCruiseCar::CImpIClassFactory::AddRef

  Summary:  The AddRef IUnknown member of this IClassFactory interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: m_cRefI.

  Returns:  ULONG
              Returned by the delegated outer AddRef call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CFCruiseCar::CImpIClassFactory::AddRef(void)
{
  // Increment the Interface Reference Count.
  ++m_cRefI;

  LOGF1("S: CFCruiseCar::CImpIClassFactory::Addref. Delegating. New cI=%i.",m_cRefI);

  // Delegate this call to the outer object's AddRef.
  return m_pUnkOuter->AddRef();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFCruiseCar::CImpIClassFactory::Release

  Summary:  The Release IUnknown member of this IClassFactory interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: .

  Returns:  ULONG
              Returned by the delegated outer Release call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CFCruiseCar::CImpIClassFactory::Release(void)
{
  // Decrement the Interface Reference Count.
  --m_cRefI;

  LOGF1("S: CFCruiseCar::CImpIClassFactory::Release. Delegating. New cI=%i.",m_cRefI);

  // Delegate this call to the outer object's Release.
  return m_pUnkOuter->Release();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFCruiseCar::CImpIClassFactory::CreateInstance

  Summary:  The CreateInstance member method of this IClassFactory interface
            implementation.  Creates an instance of the COCruiseCar COM
            component.

  Args:     IUnknown* pUnkOuter,
              [in] Pointer to the controlling IUnknown.
            REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppvCob)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CFCruiseCar::CImpIClassFactory::CreateInstance(
               IUnknown* pUnkOuter,
               REFIID riid,
               PPVOID ppv)
{
  HRESULT hr = E_FAIL;
  COCruiseCar* pCob = NULL;

  LOGF1("S: CFCruiseCar::CImpIClassFactory::CreateInstance. pUnkOuter=0x%X.",pUnkOuter);

  // If the creation call is requesting aggregation (pUnkOuter != NULL),
  // the COM rules state the IUnknown interface MUST also be concomitantly
  // be requested.  If it is not so requested ( riid != IID_IUnknown) then
  // an error must be returned indicating that no aggregate creation of
  // the COCruiseCarFactory COM Object can be performed.
  if (NULL != pUnkOuter && riid != IID_IUnknown)
    hr = CLASS_E_NOAGGREGATION;
  else
  {
    // Instantiate a COCruiseCar COM Object.
    pCob = new COCruiseCar(pUnkOuter, m_pServer);
    if (NULL != pCob)
    {
      // We initially created the new COM object so tell the server
      // to increment its global server object count to help ensure
      // that the server remains loaded until this partial creation
      // of a COM component is completed.
      m_pServer->ObjectsUp();

      // If we have succeeded in instantiating the COM object we
      // initialize it to set up any subordinate objects.
      hr = pCob->Init();
      if (SUCCEEDED(hr))
      {
        // We QueryInterface this new COM Object not only to deposit the
        // main interface pointer to the caller's pointer variable, but to
        // also automatically bump the Reference Count on the new COM
        // Object after handing out this reference to it.
        hr = pCob->QueryInterface(riid, (PPVOID)ppv);
      }

      if (FAILED(hr))
      {
        m_pServer->ObjectsDown();
        delete pCob;
      }
    }
    else
      hr = E_OUTOFMEMORY;
  }

  if (SUCCEEDED(hr))
  {
    LOGF1("S: CFCruiseCar::CImpIClassFactory::CreateInstance Succeeded. *ppv=0x%X.",*ppv);
  }
  else
  {
    LOG("S: CFCruiseCar::CImpIClassFactory::CreateInstance Failed.");
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFCruiseCar::CImpIClassFactory::LockServer

  Summary:  The LockServer member method of this IClassFactory interface
            implementation.

  Args:     BOOL fLock)
              [in] Flag determining whether to Lock or Unlock the server.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CFCruiseCar::CImpIClassFactory::LockServer(
               BOOL fLock)
{
  HRESULT hr = NOERROR;

  LOG("S: CFCruiseCar::CImpIClassFactory::LockServer.");

  if (fLock)
    m_pServer->Lock();
  else
    m_pServer->Unlock();

  return hr;
}


/*---------------------------------------------------------------------------
  Implementation the CFCarSample Class Factory.  CFCarSample is the COM
  object class for the Class Factory that can manufacture COCarSample
  COM Components.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFCarSample::CFCarSample

  Summary:  CFCruiseCar Constructor. Note the member initializer:
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
CFCarSample::CFCarSample(
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

  LOGF1("S: CFCarSample Constructor. m_pUnkOuter=0x%X.", m_pUnkOuter);

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFCarSample::~CFCarSample

  Summary:  CFCarSample Destructor.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CFCarSample::~CFCarSample(void)
{
  LOG("S: CFCarSample::Destructor.");

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFCarSample::QueryInterface

  Summary:  QueryInterface of the CFCarSample non-delegating
            IUnknown implementation.

  Args:     REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CFCarSample::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  HRESULT hr = E_NOINTERFACE;
  *ppv = NULL;

  if (IID_IUnknown == riid)
  {
    *ppv = this;
    LOG("S: CFCarSample::QueryInterface. 'this' pIUnknown returned.");
  }
  else if (IID_IClassFactory == riid)
  {
    *ppv = &m_ImpIClassFactory;
    LOG("S: CFCarSample::QueryInterface. pIClassFactory returned.");
  }

  if (NULL != *ppv)
  {
    // We've handed out a pointer to the interface so obey the COM rules
    //   and AddRef the reference count.
    ((LPUNKNOWN)*ppv)->AddRef();
    hr = NOERROR;
  }

  return (hr);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFCarSample::AddRef

  Summary:  AddRef of the CFCarSample non-delegating IUnknown implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CFCarSample::AddRef(void)
{
  m_cRefs++;

  LOGF1("S: CFCarSample::AddRef. New cRefs=%i.", m_cRefs);

  return m_cRefs;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFCarSample::Release

  Summary:  Release of the CFCarSample non-delegating IUnknown implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CFCarSample::Release(void)
{
  m_cRefs--;

  LOGF1("S: CFCarSample::Release. New cRefs=%i.", m_cRefs);

  if (0 == m_cRefs)
  {
    // We've reached a zero reference count for this COM object.
    // So we tell the server housing to decrement its global object
    // count so that the server will be unloaded if appropriate.
    if (NULL != m_pServer)
      m_pServer->ObjectsDown();

    // We artificially bump the main ref count to prevent reentrancy
    // via the main object destructor.  Not really needed in this
    // CFCarSample but a good practice because we are aggregatable and
    // may at some point in the future add something entertaining like
    // some Releases to the CFCarSample destructor.
    m_cRefs++;
    delete this;
  }

  return m_cRefs;
}


/*---------------------------------------------------------------------------
  CFCarSample's nested implementation of the IClassFactory interface
  including Constructor, Destructor, QueryInterface, AddRef, Release,
  CreateInstance, and LockServer methods.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFCarSample::CImpIClassFactory::CImpIClassFactory

  Summary:  Constructor for the CImpIClassFactory interface instantiation.

  Args:     CFCarSample* pBackObj,
              Back pointer to the parent outer object.
            IUnknown* pUnkOuter,
              Pointer to the outer Unknown.  For delegation.
            CServer* pServer)
              Pointer to the server's control object.

  Modifies: m_cRefI, m_pBackObj, m_pUnkOuter, m_pServer.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CFCarSample::CImpIClassFactory::CImpIClassFactory(
  CFCarSample* pBackObj,
  IUnknown* pUnkOuter,
  CServer* pServer)
{
  // Init the Interface Ref Count (used for debugging only).
  m_cRefI = 0;

  // Init the Back Object Pointer to point to the parent object.
  m_pBackObj = pBackObj;

  // Init the pointer to the server control object.
  m_pServer = pServer;

  // Init the CImpIClassFactory interface's delegating Unknown pointer.
  // We use the Back Object pointer for IUnknown delegation here if we are
  // not being aggregated.  If we are being aggregated we use the supplied
  // pUnkOuter for IUnknown delegation.  In either case the pointer
  // assignment requires no AddRef because the CImpIClassFactory lifetime is
  // quaranteed by the lifetime of the parent object in which
  // CImpIClassFactory is nested.
  if (NULL == pUnkOuter)
  {
    m_pUnkOuter = pBackObj;
    LOG("S: CFCarSample::CImpIClassFactory Constructor. Non-Aggregating.");
  }
  else
  {
    m_pUnkOuter = pUnkOuter;
    LOG("S: CFCarSample::CImpIClassFactory Constructor. Aggregating.");
  }

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFCarSample::CImpIClassFactory::~CImpIClassFactory

  Summary:  Destructor for the CImpIClassFactory interface instantiation.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CFCarSample::CImpIClassFactory::~CImpIClassFactory(void)
{
  LOG("S: CFCarSample::CImpIClassFactory Destructor.");

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFCarSample::CImpIClassFactory::QueryInterface

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
STDMETHODIMP CFCarSample::CImpIClassFactory::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  LOG("S: CFCarSample::CImpIClassFactory::QueryInterface. Delegating.");

  // Delegate this call to the outer object's QueryInterface.
  return m_pUnkOuter->QueryInterface(riid, ppv);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFCarSample::CImpIClassFactory::AddRef

  Summary:  The AddRef IUnknown member of this IClassFactory interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: m_cRefI.

  Returns:  ULONG
              Returned by the delegated outer AddRef call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CFCarSample::CImpIClassFactory::AddRef(void)
{
  // Increment the Interface Reference Count.
  ++m_cRefI;

  LOGF1("S: CFCarSample::CImpIClassFactory::Addref. Delegating. New cI=%i.",m_cRefI);

  // Delegate this call to the outer object's AddRef.
  return m_pUnkOuter->AddRef();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFCarSample::CImpIClassFactory::Release

  Summary:  The Release IUnknown member of this IClassFactory interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: .

  Returns:  ULONG
              Returned by the delegated outer Release call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CFCarSample::CImpIClassFactory::Release(void)
{
  // Decrement the Interface Reference Count.
  --m_cRefI;

  LOGF1("S: CFCarSample::CImpIClassFactory::Release. Delegating. New cI=%i.",m_cRefI);

  // Delegate this call to the outer object's Release.
  return m_pUnkOuter->Release();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFCarSample::CImpIClassFactory::CreateInstance

  Summary:  The CreateInstance member method of this IClassFactory
            interface implementation.  Creates an instance of the
            COCarSample COM component.

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
STDMETHODIMP CFCarSample::CImpIClassFactory::CreateInstance(
               IUnknown* pUnkOuter,
               REFIID riid,
               PPVOID ppv)
{
  HRESULT hr = E_FAIL;
  COCarSample* pCob = NULL;

  LOGF1("S: CFCarSample::CImpIClassFactory::CreateInstance. pUnkOuter=0x%X.",pUnkOuter);

  // If the creation call is requesting aggregation (pUnkOuter != NULL),
  // the COM rules state the IUnknown interface MUST also be concomitantly
  // be requested.  If it is not so requested ( riid != IID_IUnknown) then
  // an error must be returned indicating that no aggregate creation of
  // the CFCarSample COM Object can be performed.
  if (NULL != pUnkOuter && riid != IID_IUnknown)
    hr = CLASS_E_NOAGGREGATION;
  else
  {
    // Instantiate a COCarSample COM Object.
    pCob = new COCarSample(pUnkOuter, m_pServer);
    if (NULL != pCob)
    {
      // We initially created the new COM object so tell the server
      // to increment its global server object count to help ensure
      // that the server remains loaded until this partial creation
      // of a COM component is completed.
      m_pServer->ObjectsUp();

      // We QueryInterface this new COM Object not only to deposit the
      // main interface pointer to the caller's pointer variable, but to
      // also automatically bump the Reference Count on the new COM
      // Object after handing out this reference to it.
      hr = pCob->QueryInterface(riid, (PPVOID)ppv);
      if (FAILED(hr))
      {
        m_pServer->ObjectsDown();
        delete pCob;
      }
    }
    else
      hr = E_OUTOFMEMORY;
  }

  if (SUCCEEDED(hr))
  {
    LOGF1("S: CFCarSample::CImpIClassFactory::CreateInstance Succeeded. *ppv=0x%X.",*ppv);
  }
  else
  {
    LOG("S: CFCarSample::CImpIClassFactory::CreateInstance Failed.");
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFCarSample::CImpIClassFactory::LockServer

  Summary:  The LockServer member method of this IClassFactory interface
            implementation.

  Args:     BOOL fLock)
              [in] Flag determining whether to Lock or Unlock the server.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CFCarSample::CImpIClassFactory::LockServer(
               BOOL fLock)
{
  HRESULT hr = NOERROR;

  LOG("S: CFCarSample::CImpIClassFactory::LockServer.");

  if (fLock)
    m_pServer->Lock();
  else
    m_pServer->Unlock();

  return hr;
}
