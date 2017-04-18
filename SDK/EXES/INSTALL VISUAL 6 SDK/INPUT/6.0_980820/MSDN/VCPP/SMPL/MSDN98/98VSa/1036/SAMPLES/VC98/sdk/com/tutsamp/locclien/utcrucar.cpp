/*+==========================================================================
  File:      UTCRUCAR.CPP

  Summary:   Implementation file for the aggregatable COUtilityCruiseCar
             COM object class.

             UTCRUCAR showcases the construction of the COUtilityCruiseCar
             COM object class with the IUnknown, ICar, ICruise, and
             IUtility interfaces.  This is done through Containment reuse
             of COCruiseCar's ICar and ICruise interface features.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial LOCCLIEN.HTM
             file.  For more specific technical details on the internal
             workings see the comments dispersed throughout the
             module's source code.

  Classes:   COUtilityCruiseCar.

  Functions: CreateUtilityCruiseCar.

  Origin:    11-20-95: atrent - Editor inheritance from DLLCLIEN source.

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
  We include MICARS.H and CARGUIDS.H for the common car-related Interface
    class, GUID, and CLSID specifications.
  We include LOCCLIEN.H because it has class and resource definitions
    specific to this LOCCLIEN application.
  We include UTCRUCAR.H because it has the COUtilityCruiseCar declarations.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <apputil.h>
#include <micars.h>
#include <carguids.h>
#include "locclien.h"
#include "utcrucar.h"


/*---------------------------------------------------------------------------
  COUtilityCruiseCar's implementation of its main COM object class including
  Constructor, Destructor, QueryInterface, AddRef, and Release.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::COUtilityCruiseCar

  Summary:  COUtilityCruiseCar Constructor. Note the member initializer:
            "m_ImpIUtility(this, pUnkOuter)" which is used to pass the 'this'
            and pUnkOuter pointers of this constructor function to the
            constructor in the instantiation of the implementation of
            the CImpIUtility interface (which is nested inside this present
            COUtilityCruiseCar Object Class).

  Args:     IUnknown* pUnkOuter)
              Pointer to the the outer Unknown.  NULL means this COM Object
              is not being Aggregated.  Non NULL means it is being created
              on behalf of an outside COM object that is reusing it via
              aggregation.

  Modifies: m_cRefs, m_pUnkOuter, m_pUnkCruiseCar.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COUtilityCruiseCar::COUtilityCruiseCar(
  IUnknown* pUnkOuter) :
  m_ImpICar(this, pUnkOuter),
  m_ImpICruise(this, pUnkOuter),
  m_ImpIUtility(this, pUnkOuter)
{
  // Zero the COM object's reference count.
  m_cRefs = 0;

  // No AddRef necessary if non-NULL, as this COM object's lifetime
  // is totally coupled with the controlling Outer object's lifetime.
  m_pUnkOuter = pUnkOuter;

  // Zero the pointer to the contained COCruiseCar object's ICar interface.
  m_pICar = NULL;

  // Zero the pointer to the contained COCruiseCar object's ICruise
  // interface.
  m_pICruise = NULL;

  LOGF1("C: COUtilityCruiseCar Constructor. m_pUnkOuter=0x%X.", m_pUnkOuter);

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::~COUtilityCruiseCar

  Summary:  COUtilityCruiseCar Destructor.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COUtilityCruiseCar::~COUtilityCruiseCar(void)
{
  LOG("C: COUtilityCruiseCar::Destructor.");

  // Release the contained CruiseCar interfaces.
  m_pICruise->Release();
  m_pICar->Release();

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::Init

  Summary:  COUtilityCruiseCar Initialization method.

  Args:     void

  Modifies: m_pICar, m_pICruise, m_cRefs.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT COUtilityCruiseCar::Init(void)
{
  HRESULT hr;
  IClassFactory* pICFCruiseCar;

  // Set up the right pIUnknown for delegation.  If we are being
  // aggregated then we pass the pUnkOuter in turn to any COM objects
  // that we are aggregating.  m_pUnkOuter was set in the Constructor.
  IUnknown* pUnkOuter = (NULL == m_pUnkOuter) ? this : m_pUnkOuter;

  LOGF1("C: COUtilityCruiseCar::Init. pUnkOuter=0x%X",pUnkOuter);

  // Get a class factory for LocCruiseCar and issue IClassFactory's
  // CreateInstance method to manufacture a COCruiseCar COM object.
  LOG("C: COUtilityCruiseCar::Init. Obtain CruiseCar Class Factory.");
  hr = CoGetClassObject(
         CLSID_LocCruiseCar,
         CLSCTX_LOCAL_SERVER,
         NULL,
         IID_IClassFactory,
         (PPVOID)&pICFCruiseCar);
  if (SUCCEEDED(hr))
  {
    LOG("C: COUtilityCruiseCar::Init. CruiseCar Class Factory obtained.");
    LOG("C: COUtilityCruiseCar::Init. Calling CFCruiseCar::CreateInstance.");
    // A NULL pUnkOuter is passed indicating that we are creating a
    // COCruiseCar component via the Containment reuse method.  We can
    // currently pass nothing other than this NULL pUnkOuter because
    // aggregation is not supported across process or machine boundaries.
    // Since we are not requesting a COCruiseCar create for aggregation we
    // can directly request for the ICruise interface on the new object.
    hr = pICFCruiseCar->CreateInstance(
                          NULL,
                          IID_ICruise,
                          (PPVOID)&m_pICruise);
    LOG("C: COUtilityCruiseCar::Init. Releasing CruiseCar Class Factory.");
    pICFCruiseCar->Release();
    if (SUCCEEDED(hr))
    {
      // Now that we have a valid interface pointer (m_pICruise) on the
      // new object we can obtain and cache a pointer to that contained
      // object's ICar interface as well.  We must QI using the obtained
      // ICruise pointer on the object to ensure that the marshaling proxy
      // is involved in the QueryInterface call to provide the pointer to
      // the ICar interface proxy.
      hr = m_pICruise->QueryInterface(IID_ICar, (PPVOID)&m_pICar);
    }
  }

  if (SUCCEEDED(hr))
  {
    LOG("C: COUtilityCruiseCar::Init (CruiseCar Containment) Succeeded.");
  }
  else
  {
    LOGF1("C: COUtilityCruiseCar::Init (CruiseCar Containment) Failed. hr=0x%X",hr);
  }

  return (hr);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::QueryInterface

  Summary:  QueryInterface of the COUtilityCruiseCar non-delegating
            IUnknown implementation.

  Args:     REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Modifies: .

  Returns:  HRESULT
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COUtilityCruiseCar::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  HRESULT hr = E_NOINTERFACE;
  *ppv = NULL;

  if (IID_IUnknown == riid)
  {
    *ppv = this;
    LOG("C: COUtilityCruiseCar::QueryInterface. 'this' pIUnknown returned.");
  }
  else if (IID_ICar == riid)
  {
    *ppv = &m_ImpICar;
    LOG("C: COUtilityCruiseCar::QueryInterface. pICar returned");
  }
  else if (IID_ICruise == riid)
  {
    *ppv = &m_ImpICruise;
    LOG("C: COUtilityCruiseCar::QueryInterface. pICruise returned");
  }
  else if (IID_IUtility == riid)
  {
    // This IUtility interface is implemented in this COUtilityCruiseCar
    // object as a native interface of COUtilityCruiseCar.
    *ppv = &m_ImpIUtility;
    LOG("C: COUtilityCruiseCar::QueryInterface. pIUtility returned.");
  }

  if (NULL != *ppv)
  {
    // We've handed out a pointer to an interface so obey the COM rules
    // and AddRef its reference count.
    ((LPUNKNOWN)*ppv)->AddRef();
    hr = NOERROR;
  }

  return (hr);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::AddRef

  Summary:  AddRef of the COUtilityCruiseCar non-delegating
            IUnknown implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COUtilityCruiseCar::AddRef(void)
{
  m_cRefs++;

  LOGF1("C: COUtilityCruiseCar::AddRef. New cRefs=%i.", m_cRefs);

  return m_cRefs;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::Release

  Summary:  Release of the COUtilityCruiseCar non-delegating IUnknown
            implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COUtilityCruiseCar::Release(void)
{
  ULONG ulCount = --m_cRefs;

  LOGF1("C: COUtilityCruiseCar::Release. New cRefs=%i.", m_cRefs);

  if (0 == m_cRefs)
  {
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
  COUtilityCruiseCar's nested implementation of the ICar interface
  including Constructor, Destructor, QueryInterface, AddRef, Release,
  Shift, Clutch, Speed, and Steer.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::CImpICar::CImpICar

  Summary:  Constructor for the CImpICar interface instantiation.

  Args:     COUtilityCruiseCar* pBackObj,
              Back pointer to the parent outer object.
            IUnknown* pUnkOuter,
              Pointer to the outer Unknown.  For delegation.

  Modifies: m_cRefI, m_pBackObj, m_pUnkOuter.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COUtilityCruiseCar::CImpICar::CImpICar(
  COUtilityCruiseCar* pBackObj,
  IUnknown* pUnkOuter)
{
  // Init the Interface Ref Count (used for debugging only).
  m_cRefI = 0;

  // Init the Back Object Pointer to point to the outer object.
  m_pBackObj = pBackObj;

  // Init the CImpICar interface's delegating Unknown pointer.  We use
  // the Back Object pointer for IUnknown delegation here if we are not
  // being aggregated.  If we are being aggregated we use the supplied
  // pUnkOuter for IUnknown delegation.  In either case the pointer
  // assignment requires no AddRef because the CImpICar lifetime is
  // quaranteed by the lifetime of the parent object in which
  // CImpICar is nested.
  if (NULL == pUnkOuter)
  {
    m_pUnkOuter = pBackObj;
    LOG("C: COUtilityCruiseCar::CImpICar Constructor. Non-Aggregating");
  }
  else
  {
    m_pUnkOuter = pUnkOuter;
    LOG("C: COUtilityCruiseCar::CImpICar Constructor. Aggregating");
  }

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::CImpICar::~CImpICar

  Summary:  Destructor for the CImpICar interface instantiation.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COUtilityCruiseCar::CImpICar::~CImpICar(void)
{
  LOG("C: COUtilityCruiseCar::CImpICar Destructor.");

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::CImpICar::QueryInterface

  Summary:  The QueryInterface IUnknown member of this ICar interface
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
STDMETHODIMP COUtilityCruiseCar::CImpICar::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  LOG("C: COUtilityCruiseCar::CImpICar::QueryInterface. Delegating.");

  // Delegate this call to the outer object's QueryInterface.
  return m_pUnkOuter->QueryInterface(riid, ppv);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::CImpICar::AddRef

  Summary:  The AddRef IUnknown member of this ICar interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: m_cRefI.

  Returns:  ULONG
              Returned by the delegated outer AddRef call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COUtilityCruiseCar::CImpICar::AddRef(void)
{
  // Increment the Interface Reference Count.
  ++m_cRefI;

  LOGF1("C: COUtilityCruiseCar::CImpICar::Addref. Delegating. New cI=%i.", m_cRefI);

  // Delegate this call to the outer object's AddRef.
  return m_pUnkOuter->AddRef();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::CImpICar::Release

  Summary:  The Release IUnknown member of this ICar interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: .

  Returns:  ULONG
              Returned by the delegated outer Release call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COUtilityCruiseCar::CImpICar::Release(void)
{
  // Decrement the Interface Reference Count.
  --m_cRefI;

  LOGF1("C: COUtilityCruiseCar::CImpICar::Release. Delegating. New cI=%i.", m_cRefI);

  // Delegate this call to the outer object's Release.
  return m_pUnkOuter->Release();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::CImpICar::Shift

  Summary:  The Shift member method of this ICar interface implementation.
            A simple empty method on a COUtilityCruiseCar COM object for
            tutorial purposes.  Presumably if this Car object were
            modeling a real Car then the Shift method would shift to the
            specified gear.

  Args:     short nGear
              0 - Neutral; 1 - 5 First 5 forward gears; 6 - Reverse.

  Modifies: .

  Returns:  HRESULT
              Delegated HRESULT.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COUtilityCruiseCar::CImpICar::Shift(
               short nGear)
{
  LOGF1("C: COUtilityCruiseCar::CImpICar::Shift. Delegating. nGear=%i.",nGear);

  // Delegate this call to the contained COCruiseCar's ICar::Shift.
  return m_pBackObj->m_pICar->Shift(nGear);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::CImpICar::Clutch

  Summary:  The Clutch member method of this ICar interface
            implementation. A simple empty method on a COUtilityCruiseCar
            COM object for tutorial purposes.  Presumably if this Car
            object were modeling a real Car then the Clutch method would
            engage the clutch the specified amount.

  Args:     short nEngaged)
              Percent clutch is engaged (0 to 100%).

  Modifies: .

  Returns:  HRESULT
              Delegated HRESULT.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COUtilityCruiseCar::CImpICar::Clutch(
               short nEngaged)
{
  LOGF1("C: COUtilityCruiseCar::CImpICar::Clutch. Delegating. nEngaged=%i.", nEngaged);

  // Delegate this call to the contained COCruiseCar's ICar::Clutch.
  return m_pBackObj->m_pICar->Clutch(nEngaged);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::CImpICar::Speed

  Summary:  The Propel member method of this ICar interface
            implementation. A simple empty method on a COUtilityCruiseCar
            COM object for tutorial purposes.  Presumably if this Car
            object were modeling a real Car then this method would
            accelerate/brake to bring the car to the specified speed.

  Args:     short nMph
              New speed in miles per hour.

  Modifies: .

  Returns:  HRESULT
              Delegated HRESULT.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COUtilityCruiseCar::CImpICar::Speed(
               short nMph)
{
  LOGF1("C: COUtilityCruiseCar::CImpICar::Speed. Delegating. nMph=%i.",nMph);

  // Delegate this call to the contained COCruiseCar's ICar::Speed.
  return m_pBackObj->m_pICar->Speed(nMph);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::CImpICar::Steer

  Summary:  The Steer member method of this ICar interface implementation.
            A simple empty method on a COUtilityCruiseCar COM object for
            tutorial purposes.  Presumably if this Car object were
            modeling a real Car then the Steer method would set the
            steering angle of the Car.

  Args:     short nAngle)
              0 degrees straight ahead, -45 Full left, +45 Full right.

  Modifies: .

  Returns:  HRESULT
              Delegated HRESULT.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COUtilityCruiseCar::CImpICar::Steer(
               short nAngle)
{
  LOGF1("C: COUtilityCruiseCar::CImpICar::Steer. Delegating. nAngle=%i.",nAngle);

  // Delegate this call to the contained COCruiseCar's ICar::Steer.
  return m_pBackObj->m_pICar->Steer(nAngle);
}


/*---------------------------------------------------------------------------
  COUtilityCruiseCar's nested implementation of the ICruise interface
  including Constructor, Destructor, QueryInterface, AddRef, Release,
  Engage, and Adjust.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::CImpICruise::CImpICruise

  Summary:  Constructor for the CImpICruise interface instantiation.

  Args:     COUtilityCruiseCar* pBackObj,
              Back pointer to the parent outer object.
            IUnknown* pUnkOuter,
              Pointer to the outer Unknown.  For delegation.

  Modifies: m_cRefI, m_pBackObj, m_pUnkOuter.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COUtilityCruiseCar::CImpICruise::CImpICruise(
  COUtilityCruiseCar* pBackObj,
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
    LOG("C: COUtilityCruiseCar::CImpICruise Constructor. Non-Aggregating");
  }
  else
  {
    m_pUnkOuter = pUnkOuter;
    LOG("C: COUtilityCruiseCar::CImpICruise Constructor. Aggregating");
  }

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::CImpICruise::~CImpICruise

  Summary:  Destructor for the CImpICruise interface instantiation.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COUtilityCruiseCar::CImpICruise::~CImpICruise(void)
{
  LOG("C: COUtilityCruiseCar::CImpICruise Destructor.");

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::CImpICruise::QueryInterface

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
STDMETHODIMP COUtilityCruiseCar::CImpICruise::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  LOG("C: COUtilityCruiseCar::CImpICruise::QueryInterface. Delegating.");

  // Delegate this call to the outer object's QueryInterface.
  return m_pUnkOuter->QueryInterface(riid, ppv);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::CImpICruise::AddRef

  Summary:  The AddRef IUnknown member of this ICruise interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: m_cRefI.

  Returns:  ULONG
              Returned by the delegated outer AddRef call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COUtilityCruiseCar::CImpICruise::AddRef(void)
{
  // Increment the Interface Reference Count.
  ++m_cRefI;

  LOGF1("C: COUtilityCruiseCar::CImpICruise::Addref. Delegating. New cI=%i.", m_cRefI);

  // Delegate this call to the outer object's AddRef.
  return m_pUnkOuter->AddRef();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::CImpICruise::Release

  Summary:  The Release IUnknown member of this ICruise interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: .

  Returns:  ULONG
              Returned by the delegated outer Release call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COUtilityCruiseCar::CImpICruise::Release(void)
{
  // Decrement the Interface Reference Count.
  --m_cRefI;

  LOGF1("C: COUtilityCruiseCar::CImpICruise::Release. Delegating. New cI=%i.", m_cRefI);

  // Delegate this call to the outer object's Release.
  return m_pUnkOuter->Release();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::CImpICruise::Engage

  Summary:  The Engage member method of this ICruise interface
            implementation.  A simple empty method on a COUtilityCruiseCar
            COM object for tutorial purposes.  Presumably if this Car
            object were modeling a real Car then the Engage method would
            turn the Cruise control system on or off.

  Args:     BOOL bOnOff)
              TRUE for On; FALSE for Off.

  Modifies: .

  Returns:  HRESULT
              Delegated HRESULT.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COUtilityCruiseCar::CImpICruise::Engage(
               BOOL bOnOff)
{
  LOGF1("C: COUtilityCruiseCar::CImpICruise::Engage. Delegating. bOnOff=%i.",bOnOff);

  // Delegate this call to the contained COCruiseCar's ICruise::Engage.
  m_pBackObj->m_pICruise->Engage(bOnOff);

  return NOERROR;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::CImpICruise::Adjust

  Summary:  The Adjust member method of this ICruise interface
            implementation.  A simple empty method on a COUtilityCruiseCar
            COM object for tutorial purposes.  Presumably if this Car
            object were modeling a real Car then the Adjust method would
            allow notching the cruise set speed up or down by increments
            of 3 mph.

  Args:     BOOL bUpDown)
              TRUE for Up; FALSE for Down.

  Modifies: .

  Returns:  HRESULT
              Delegated HRESULT.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COUtilityCruiseCar::CImpICruise::Adjust(
               BOOL bUpDown)
{
  LOGF1("C: COUtilityCruiseCar::CImpICruise::Adjust. Delegating. bUpDown=%i.",bUpDown);

  // Delegate this call to the contained COCruiseCar's ICruise::Adjust.
  m_pBackObj->m_pICruise->Adjust(bUpDown);

  return NOERROR;
}


/*---------------------------------------------------------------------------
  COUtilityCruiseCar's nested implementation of the IUtility interface
  including methods: Constructor, Destructor, QueryInterface, AddRef,
  Release, Offroad, and Winch.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::CImpIUtility::CImpIUtility

  Summary:  Constructor for the CImpIUtility interface instantiation.

  Args:     COUtilityCruiseCar* pBackObj,
              Back pointer to the parent outer object.
            IUnknown* pUnkOuter)
              Pointer to the outer Unknown.  For delegation.

  Modifies: m_cRefI, m_pBackObj, m_pUnkOuter.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COUtilityCruiseCar::CImpIUtility::CImpIUtility(
  COUtilityCruiseCar* pBackObj,
  IUnknown* pUnkOuter)
{
  // Init the Interface Ref Count (used for debugging only).
  m_cRefI = 0;

  // Init the Back Object Pointer to point to the outer object.
  m_pBackObj = pBackObj;

  // Init the CImpIUtility interface's delegating IUnknown pointer.  We use
  // the Back Object pointer for IUnknown delegation here if we are not
  // being aggregated.  If we are being aggregated we use the supplied
  // pUnkOuter for IUnknown delegation.  In either case the pointer
  // assignment requires no AddRef because the CImpIUtility lifetime is
  // quaranteed by the lifetime of the parent object in which
  // CImpIUtility is nested.
  if (NULL == pUnkOuter)
  {
    m_pUnkOuter = pBackObj;
    LOG("C: COUtilityCruiseCar::CImpIUtility Constructor. Non-Aggregating.");
  }
  else
  {
    m_pUnkOuter = pUnkOuter;
    LOG("C: COUtilityCruiseCar::CImpIUtility Constructor. Aggregating.");
  }

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::CImpIUtility::~CImpIUtility

  Summary:  Destructor for the CImpIUtility interface instantiation.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COUtilityCruiseCar::CImpIUtility::~CImpIUtility(void)
{
  LOG("C: COUtilityCruiseCar::CImpIUtility Destructor.");

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::CImpIUtility::QueryInterface

  Summary:  The QueryInterface IUnknown member of this IUtility interface
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
STDMETHODIMP COUtilityCruiseCar::CImpIUtility::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  LOG("C: COUtilityCruiseCar::CImpIUtility::QueryInterface. Delegating.");

  // Delegate this call to the outer object's QueryInterface.
  return m_pUnkOuter->QueryInterface(riid, ppv);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::CImpIUtility::AddRef

  Summary:  The AddRef IUnknown member of this IUtility interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: m_cRefI.

  Returns:  ULONG
              Returned by the delegated outer AddRef call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COUtilityCruiseCar::CImpIUtility::AddRef(void)
{
  // Increment the Interface Reference Count.
  ++m_cRefI;

  LOGF1("C: COUtilityCruiseCar::CImpIUtility::Addref. Delegating. New cI=%i.", m_cRefI);

  // Delegate this call to the outer object's AddRef.
  return m_pUnkOuter->AddRef();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::CImpIUtility::Release

  Summary:  The Release IUnknown member of this IUtility interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: .

  Returns:  ULONG
              Returned by the delegated outer Release call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COUtilityCruiseCar::CImpIUtility::Release(void)
{
  // Decrement the Interface Reference Count.
  --m_cRefI;

  LOGF1("C: COUtilityCruiseCar::CImpIUtility::Release. Delegating. New cI=%i.", m_cRefI);

  // Delegate this call to the outer object's Release.
  return m_pUnkOuter->Release();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::CImpIUtility::Offroad

  Summary:  The Offroad member method of this IUtility interface
            implementation.  A simple empty method on a COUtilityCruiseCar
            COM object for tutorial purposes.  Presumably if this
            UtilityCruise Car object were modeling a real Car then the
            Offroad method would function the 4-wheel drive transfer case
            and shift it to the specified 4-wheel drive mode.

  Args:     short nGear
              0 = 2H or regular 2-wheel drive;
              1 = 4H or 4-wheel drive high speed;
              2 = neutral; and
              3 = 4L or 4-wheel drive low speed).

  Modifies: .

  Returns:  HRESULT
              NOERROR
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COUtilityCruiseCar::CImpIUtility::Offroad(
               short nGear)
{
  LOGF1("C: COUtilityCruiseCar::CImpIUtility::Offroad. Called. nGear=%i.",nGear);

  // We don't delegate because this IUtility implementation is native to
  // the composite COUtilityCruiseCar object.

  return NOERROR;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::CImpIUtility::Winch

  Summary:  The Winch member method of this IUtility interface
            implementation.  A simple empty method on a COUtilityCruiseCar
            COM object for tutorial purposes.  Presumably if this
            UtilityCruiseCar object were modeling a real Car then the
            Winch method would turn on/off the front-mounted Winch to the
            specified RPMs.

  Args:     short nRpm
              0 = off; 1 - 50 RPM.

  Modifies: .

  Returns:  HRESULT
              NOERROR
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COUtilityCruiseCar::CImpIUtility::Winch(
               short nRpm)
{
  LOGF1("C: COUtilityCruiseCar::CImpIUtility::Winch. Called. nRpm=%i.",nRpm);

  // We don't delegate because this IUtility implementation is native to
  // the composite COUtilityCruiseCar object.

  return NOERROR;
}


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: CreateUtilityCruiseCar

  Summary:  Creates an instance of the COUtilityCruiseCar COM object class
            returning a requested interface pointer. COUtilityCruiseCar
            uses the Containment reuse technique to incorporate
            COCruiseCar features (ie, ICar and ICruise implementations)
            into its Interface offerings of IUnknown and IUtility. With
            this containment, the ICar and ICruise interfaces are
            implemented in COUtilityCruiseCar as delegating interfaces
            that delegate to their matching interface implementations in
            an instance of the contained COCruiseCar.  COCruiseCar is
            provided by the outside LOCSERVE.EXE server.

  Args:     IUnknown* pUnkOuter,
              Pointer the outer Unknown interface.  Non NULL implies
              that the new COM object is being created via an
              aggregation with an Outer object.  NULL implies that the
              object is not being created via aggregation.
            REFIID riid,
              The GUID of the interface requested on the new COM Object.
            PPVOID ppv)
              Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Returns:  HRESULT
              NOERROR if successful, CLASS_E_NOAGREGATION if IUnknown is
              not requested with non-NULL pUnkOuter, or other errors as
              appropriate.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
HRESULT CreateUtilityCruiseCar(
          IUnknown* pUnkOuter,
          REFIID riid,
          PPVOID ppv)
{
  HRESULT hr;
  COUtilityCruiseCar* pCob;

  LOGF1("C: CreateUtilityCruiseCar. pUnkOuter=0x%X.",pUnkOuter);

  // If the creation call is requesting aggregation (pUnkOuter != NULL),
  // the COM rules state the IUnknown interface MUST also be concomitantly
  // requested.  If it is not so requested ( riid != IID_IUnknown) then
  // an error must be returned indicating that no aggregate creation of
  // the COUtilityCruiseCar COM Object can be performed using anything
  // other than a controlling IUnknown interface.
  if (NULL != pUnkOuter && riid != IID_IUnknown)
    hr = CLASS_E_NOAGGREGATION;
  else
  {
    // Instantiate a COUtilityCruiseCar COM Object.
    pCob = new COUtilityCruiseCar(pUnkOuter);
    if (NULL != pCob)
    {
      // If we have succeeded in instantiating the COUtilityCruiseCar object
      // we initialize it (with any subordinate COM objects) to offer it's
      // interfaces.
      hr = pCob->Init();
      if (SUCCEEDED(hr))
      {
        // We QueryInterface this new COM Object not only to deposit the
        // main interface pointer to the caller's pointer variable, but to
        // also automatically bump the Reference Count on the new COM
        // Object after handing out this *ppv reference to it.
        hr = pCob->QueryInterface(riid, (PPVOID)ppv);
      }
      else
        DELETE_POINTER(pCob);
    }
    else
      hr = E_OUTOFMEMORY;
  }

  if (SUCCEEDED(hr))
  {
    LOGF1("C: CreateUtilityCruiseCar Succeeded. *ppv=0x%X.",*ppv);
  }
  else
  {
    LOGF1("C: CreateUtilityCruiseCar Failed. hr=0x%X.",hr);
  }

  return hr;
}
