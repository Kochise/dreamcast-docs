/*+==========================================================================
  File:      CRUCAR.CPP

  Summary:   Implementation file for the aggregatable COLicCruiseCar COM
             object class.

             CRUCAR showcases the construction of the COLicCruiseCar COM
             object class with the IUnknown, ICar, and ICruise interfaces.
             This is done through Aggregation reuse of COCar's ICar
             interface features.  COCar is provided by a separate COM
             server (DLLSERVE).

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial DLLSERVE.HTM file.
             For more specific technical details on the internal workings
             see the comments dispersed throughout the module's source code.

  Classes:   COLicCruiseCar.

  Functions: none.

  Origin:    10-5-95: atrent - Editor-inheritance from CRUCAR.CPP in
               the DLLSERVE Tutorial Code Sample.

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
  We include APPUTIL.H because we will be building this application using
    the convenient Virtual Window and Dialog classes and other
    utility functions in the APPUTIL Library (ie, APPUTIL.LIB).
  We include ICARS.H and CARGUIDS.H for the common car-related Interface
    class, GUID, and CLSID specifications.
  We include SERVER.H because it has the necessary internal class and
    resource definitions for this DLL.
  We include CRUCAR.H because it has the class COLicCruiseCar declarations.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <apputil.h>
#include <icars.h>
#include <carguids.h>
#include "server.h"
#include "crucar.h"


/*---------------------------------------------------------------------------
  COLicCruiseCar's implementation of its main COM object class including
  Constructor, Destructor, QueryInterface, AddRef, and Release.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COLicCruiseCar::COLicCruiseCar

  Summary:  COLicCruiseCar Constructor. Note the member initializer:
            "m_ImpICruise(this, pUnkOuter)" which is used to pass the
            'this' and pUnkOuter pointers of this constructor function
            to the constructor in the instantiation of the implementation
            of the CImpICruise interface (which is nested inside this
            present COLicCruiseCar Object Class).

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
COLicCruiseCar::COLicCruiseCar(
  IUnknown* pUnkOuter,
  CServer* pServer) :
  m_ImpICruise(this, pUnkOuter)
{
  // Zero the COM object's reference count.
  m_cRefs = 0;

  // No AddRef necessary if non-NULL, as this present COM object's lifetime
  // is totally coupled with the controlling Outer object's lifetime.
  m_pUnkOuter = pUnkOuter;

  // Zero the pointer to the aggregated COCar object's IUnknown
  // interface (for delegation of IUnknown calls to it).
  m_pUnkCar = NULL;

  // Assign the pointer to the server's control object.
  m_pServer = pServer;

  LOGF1("P: COLicCruiseCar Constructor. m_pUnkOuter=0x%X.", m_pUnkOuter);

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COLicCruiseCar::~COLicCruiseCar

  Summary:  COLicCruiseCar Destructor.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COLicCruiseCar::~COLicCruiseCar(void)
{
  LOG("P: COLicCruiseCar::Destructor.");

  RELEASE_INTERFACE(m_pUnkCar);

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COLicCruiseCar::Init

  Summary:  COLicCruiseCar Initialization method.

  Args:     void

  Modifies: m_pUnkCar, m_pICar, m_cRefs.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT COLicCruiseCar::Init(void)
{
  HRESULT hr;

  LOG("P: COLicCruiseCar::Init.");

  // Set up the right pIUnknown for delegation.  If we are being
  // aggregated then we pass the pUnkOuter in turn to any COM objects
  // that we are aggregating.  m_pUnkOuter was set in the Constructor.
  IUnknown* pUnkOuter = (NULL == m_pUnkOuter) ? this : m_pUnkOuter;

  // We create an instance of the COCar object and do this via the
  // Aggregation reuse technique.  Note we pass pUnkOuter as the
  // Aggregation pointer.  It is the 'this' pointer to this present
  // LicCruiseCar object if we are not being aggregated; otherwise it is
  // the pointer to the outermost object's controlling IUnknown.  Following
  // the rules of Aggregation we must ask for an IID_IUnknown interface.
  // We cache the requested  pointer to the IUnknown of the new COCar COM
  // object for later use in delegating IUnknown calls.
  hr = CoCreateInstance(
         CLSID_DllCar,
         pUnkOuter,
         CLSCTX_INPROC_SERVER,
         IID_IUnknown,
         (PPVOID)&m_pUnkCar);

  if (SUCCEEDED(hr))
  {
    LOG("P: COLicCruiseCar::Init (New Aggregation of COCar) Succeeded.");
  }
  else
  {
    LOG("P: COLicCruiseCar::Init (New Aggregation of COCar) Failed.");
  }

  return (hr);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COLicCruiseCar::QueryInterface

  Summary:  QueryInterface of the COLicCruiseCar non-delegating
            IUnknown implementation.

  Args:     REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Modifies: .

  Returns:  HRESULT
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COLicCruiseCar::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  HRESULT hr = E_NOINTERFACE;
  *ppv = NULL;

  if (IID_IUnknown == riid)
  {
    *ppv = this;
    LOG("P: COLicCruiseCar::QueryInterface. 'this' pIUnknown returned.");
  }
  else if (IID_ICruise == riid)
  {
    // This ICruise interface is implemented in this COLicCruiseCar object
    // and might be called a native interface of COLicCruiseCar.
    *ppv = &m_ImpICruise;
    LOG("P: COLicCruiseCar::QueryInterface. pICruise returned.");
  }

  if (NULL != *ppv)
  {
    // We've handed out a pointer to an interface so obey the COM rules
    //   and AddRef its reference count.
    ((LPUNKNOWN)*ppv)->AddRef();
    hr = NOERROR;
  }
  else if (IID_ICar == riid)
  {
    LOG("P: COLicCruiseCar::QueryInterface. ICar delegating.");
    // We didn't implement the ICar interface in this COLicCruiseCar object.
    // The aggregated inner COCar object is contributing the ICar interface
    // to this present composite or aggregating LicCruiseCar object. So, to
    // satisfy a QI request for the ICar interface, we delegate the
    // QueryInterface to the inner object's principal IUnknown.
    hr = m_pUnkCar->QueryInterface(riid, ppv);
  }

  return (hr);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COLicCruiseCar::AddRef

  Summary:  AddRef of the COLicCruiseCar non-delegating IUnknown
            implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COLicCruiseCar::AddRef(void)
{
  m_cRefs++;

  LOGF1("P: COLicCruiseCar::AddRef. New cRefs=%i.", m_cRefs);

  return m_cRefs;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COLicCruiseCar::Release

  Summary:  Release of the COLicCruiseCar non-delegating IUnknown
            implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COLicCruiseCar::Release(void)
{
  ULONG ulCount = --m_cRefs;

  LOGF1("P: COLicCruiseCar::Release. New cRefs=%i.", m_cRefs);

  if (0 == m_cRefs)
  {
    // We've reached a zero reference count for this COM object.
    // So we tell the server housing to decrement its global object
    // count so that the server will be unloaded if appropriate.
    if (NULL != m_pServer)
      m_pServer->ObjectsDown();

    // We artificially bump the main ref count.  This fulfills one of
    // the rules of aggregated objects and ensures that an indirect
    // recursive call to this release won't occur because of other
    // delegating releases that might happen in our own destructor.
    m_cRefs++;
    delete this;
  }

  return ulCount;
}


/*---------------------------------------------------------------------------
  COLicCruiseCar's nested implementation of the ICruise interface including
  Constructor, Destructor, QueryInterface, AddRef, Release,
  Engage, and Adjust.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COLicCruiseCar::CImpICruise::CImpICruise

  Summary:  Constructor for the CImpICruise interface instantiation.

  Args:     COLicCruiseCar* pBackObj,
              Back pointer to the parent outer object.
            IUnknown* pUnkOuter)
              Pointer to the outer Unknown.  For delegation.

  Modifies: m_cRefI, m_pBackObj, m_pUnkOuter.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COLicCruiseCar::CImpICruise::CImpICruise(
  COLicCruiseCar* pBackObj,
  IUnknown* pUnkOuter)
{
  // Init the Interface Ref Count (used for debugging only).
  m_cRefI = 0;

  // Init the Back Object Pointer to point to the outer object.
  m_pBackObj = pBackObj;

  // Init the CImpICruise interface's delegating Unknown pointer.  We use
  // the Back Object pointer for IUnknown delegation here if we are not
  // being aggregated.  If we are being aggregated we use the supplied
  // pUnkOuter for IUnknown delegation.  In either case the pointer
  // assignment requires no AddRef because the CImpICruise lifetime is
  // quaranteed by the lifetime of the parent object in which
  // CImpICruise is nested.
  if (NULL == pUnkOuter)
  {
    m_pUnkOuter = pBackObj;
    LOG("P: COLicCruiseCar::CImpICruise Constructor. Non-Aggregating.");
  }
  else
  {
    m_pUnkOuter = pUnkOuter;
    LOG("P: COLicCruiseCar::CImpICruise Constructor. Aggregating.");
  }

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COLicCruiseCar::CImpICruise::~CImpICruise

  Summary:  Destructor for the CImpICruise interface instantiation.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COLicCruiseCar::CImpICruise::~CImpICruise(void)
{
  LOG("P: COLicCruiseCar::CImpICruise Destructor.");

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COLicCruiseCar::CImpICruise::QueryInterface

  Summary:  The QueryInterface IUnknown member of this ICruise interface
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
STDMETHODIMP COLicCruiseCar::CImpICruise::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  LOG("P: COLicCruiseCar::CImpICruise::QueryInterface. Delegating.");

  // Delegate this call to the outer object's QueryInterface.
  return m_pUnkOuter->QueryInterface(riid, ppv);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COLicCruiseCar::CImpICruise::AddRef

  Summary:  The AddRef IUnknown member of this ICruise interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: m_cRefI.

  Returns:  ULONG
              Returned by the delegated outer AddRef call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COLicCruiseCar::CImpICruise::AddRef(void)
{
  // Increment the Interface Reference Count.
  ++m_cRefI;

  LOGF1("P: COLicCruiseCar::CImpICruise::Addref. Delegating. New cI=%i.", m_cRefI);

  // Delegate this call to the outer object's AddRef.
  return m_pUnkOuter->AddRef();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COLicCruiseCar::CImpICruise::Release

  Summary:  The Release IUnknown member of this ICruise interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: .

  Returns:  ULONG
              Returned by the delegated outer Release call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COLicCruiseCar::CImpICruise::Release(void)
{
  // Decrement the Interface Reference Count.
  --m_cRefI;

  LOGF1("P: COLicCruiseCar::CImpICruise::Release. Delegating. New cI=%i.",m_cRefI);

  // Delegate this call to the outer object's Release.
  return m_pUnkOuter->Release();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COLicCruiseCar::CImpICruise::Engage

  Summary:  The Engage member method of this ICruise interface
            implementation.  A simple empty method on a COLicCruiseCar COM
            object for tutorial purposes.  Presumably if this Car object
            were modeling a real Car then the Engage method would turn
            the Cruise control system on or off.

  Args:     BOOL bOnOff)
              TRUE for On; FALSE for Off.

  Modifies: .

  Returns:  HRESULT
              NOERROR
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COLicCruiseCar::CImpICruise::Engage(
               BOOL bOnOff)
{
  LOGF1("P: COLicCruiseCar::CImpICruise::Engage. Called. bOnOff=%i.",bOnOff);

  return NOERROR;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COLicCruiseCar::CImpICruise::Adjust

  Summary:  The Adjust member method of this ICruise interface
            implementation.  A simple empty method on a COLicCruiseCar COM
            object for tutorial purposes.  Presumably if this Car object
            were modeling a real Car then the Adjust method would allow
            notching the cruise set speed up or down by increments of 3 mph.

  Args:     BOOL bUpDown)
              TRUE for Up; FALSE for Down.

  Modifies: .

  Returns:  HRESULT
              NOERROR
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COLicCruiseCar::CImpICruise::Adjust(
               BOOL bUpDown)
{
  LOGF1("P: COLicCruiseCar::CImpICruise::Adjust. Called. bUpDown=%i.",bUpDown);

  return NOERROR;
}
