/*+==========================================================================
  File:      CRUCAR.CPP

  Summary:   Implementation file for the aggregatable COCruiseCar COM
             object class.

             CRUCAR showcases the construction of the COCruiseCar COM
             object class with the IUnknown, ICar, and ICruise interfaces.
             This is done through Containment reuse of COCar's ICar
             interface features.  This multiple interface COM Object Class
             is achieved via the technique of nested classes.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial APTSERVE.HTM file.
             For more specific technical details on the internal workings
             see the comments dispersed throughout the module's source code.

  Classes:   COCruiseCar.

  Functions: none.

  Origin:    3-20-96: atrent - Editor-inheritance from CRUCAR.CPP in
               the LOCSERVE Tutorial Code Sample.

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
  We include OLE2.H because we will make calls to the COM/OLE Libraries.
  We include APPUTIL.H because we will be building this application using
    the convenient Virtual Window and Dialog classes and other
    utility functions in the APPUTIL Library (ie, APPUTIL.LIB).
  We include MICARS.H and CARGUIDS.H for the common car-related Interface
    class, GUID, and CLSID specifications.
  We include SERVER.H because it has the necessary internal class and
    resource definitions for this DLL.
  We include CAR.H because it has the class COCar declarations.
  We include CRUCAR.H because it has the class COCruiseCar declarations.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <apputil.h>
#include <micars.h>
#include <carguids.h>
#include "server.h"
#include "car.h"
#include "crucar.h"


/*---------------------------------------------------------------------------
  COCruiseCar's implementation of its main COM object class including
  Constructor, Destructor, QueryInterface, AddRef, and Release.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCruiseCar::COCruiseCar

  Summary:  COCruiseCar Constructor. Note the member initializer:
            "m_ImpICruise(this, pUnkOuter)" which is used to pass the
            'this' and pUnkOuter pointers of this constructor function
            to the constructor in the instantiation of the implementation
            of the CImpICruise interface (which is nested inside this
            present COCruiseCar Object Class).

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
COCruiseCar::COCruiseCar(
  IUnknown* pUnkOuter,
  CServer* pServer) :
  m_ImpICar(this, pUnkOuter),
  m_ImpICruise(this, pUnkOuter)
{
  // Zero the COM object's reference count.
  m_cRefs = 0;

  // No AddRef necessary if non-NULL, as this present COM object's lifetime
  // is totally coupled with the controlling Outer object's lifetime.
  m_pUnkOuter = pUnkOuter;

  // Zero the pointer to the contained COCar object's ICar interface.
  m_pICar = NULL;

  // Assign the pointer to the server's control object.
  m_pServer = pServer;

  LOGF2("L<%X>: COCruiseCar Constructor. m_pUnkOuter=0x%X.",TID,m_pUnkOuter);

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCruiseCar::~COCruiseCar

  Summary:  COCruiseCar Destructor.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COCruiseCar::~COCruiseCar(void)
{
  LOGF1("L<%X>: COCruiseCar::Destructor.",TID);

  // Release the contained Car object.
  RELEASE_INTERFACE(m_pICar);

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCruiseCar::Init

  Summary:  COCruiseCar Initialization method.  Creates any subordinate
            COM objects.

  Args:     void

  Modifies: m_pUnkCar, m_pICar, m_cRefs.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT COCruiseCar::Init(void)
{
  HRESULT hr;

  LOGF1("L<%X>: COCruiseCar::Init.",TID);

  // Set up the right pIUnknown for delegation.  If we are being
  // aggregated then we pass the pUnkOuter in turn to any COM objects
  // that we are aggregating.  m_pUnkOuter was set in the Constructor.
  IUnknown* pUnkOuter = (NULL == m_pUnkOuter) ? this : m_pUnkOuter;

  // We create an instance of the COCar object and do this via the
  // Containment reuse technique.  We ask for the new COM object's
  // ICar interface directly.  We pass NULL for the pUnkOuter
  // aggregation pointer because we are not aggregating.  It is here
  // that we are reusing the COCar COM Object through the Containment
  // technique.  We cache the requested ICar interface pointer in this
  // COCruiseCar COM object for later use.  We don't need to AddRef
  // this interface because the CoCreateInstance will do this for us.
  hr = CoCreateInstance(
         CLSID_AptCar,
         NULL,
         CLSCTX_LOCAL_SERVER,
         IID_ICar,
         (PPVOID)&m_pICar);

  if (SUCCEEDED(hr))
  {
    LOGF1("L<%X>: COCruiseCar::Init (New Containment of COCar) Succeeded.",TID);
  }
  else
  {
    LOGF2("L<%X>: COCruiseCar::Init (New Containment of COCar) Failed. hr=0x%X.",TID,hr);
  }

  return (hr);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCruiseCar::QueryInterface

  Summary:  QueryInterface of the COCruiseCar non-delegating
            IUnknown implementation.

  Args:     REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Modifies: *ppv.

  Returns:  HRESULT
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COCruiseCar::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  HRESULT hr = E_NOINTERFACE;
  *ppv = NULL;

  if (IID_IUnknown == riid)
  {
    *ppv = this;
    LOGF1("L<%X>: COCruiseCar::QueryInterface. 'this' pIUnknown returned.",TID);
  }
  else if (IID_ICar == riid)
  {
    *ppv = &m_ImpICar;
    LOGF1("L<%X>: COCruiseCar::QueryInterface. pICar returned",TID);
  }
  else if (IID_ICruise == riid)
  {
    // This ICruise interface is implemented in this COCruiseCar object
    // and might be called a native interface of COCruiseCar.
    *ppv = &m_ImpICruise;
    LOGF1("L<%X>: COCruiseCar::QueryInterface. pICruise returned.",TID);
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
  Method:   COCruiseCar::AddRef

  Summary:  AddRef of the COCruiseCar non-delegating IUnknown implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COCruiseCar::AddRef(void)
{
  m_cRefs++;

  LOGF2("L<%X>: COCruiseCar::AddRef. New cRefs=%i.",TID,m_cRefs);

  return m_cRefs;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCruiseCar::Release

  Summary:  Release of the COCruiseCar non-delegating IUnknown
            implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COCruiseCar::Release(void)
{
  ULONG ulCount = --m_cRefs;

  LOGF2("L<%X>: COCruiseCar::Release. New cRefs=%i.",TID,m_cRefs);

  if (0 == m_cRefs)
  {
    // We artificially bump the main ref count to ensure that an indirect
    // recursive call to this release won't occur because of other
    // delegating releases that might happen in our own destructor.
    m_cRefs++;
    delete this;

    // We've reached a zero reference count for this COM object.
    // So we tell the server housing to decrement its global object
    // count so that the server will be unloaded if appropriate.
    if (NULL != m_pServer)
      m_pServer->ObjectsDown();
  }

  return ulCount;
}


/*---------------------------------------------------------------------------
  COCruiseCar's nested implementation of the ICar interface including
  Constructor, Destructor, QueryInterface, AddRef, Release,
  Shift, Clutch, Speed, and Steer.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCruiseCar::CImpICar::CImpICar

  Summary:  Constructor for the CImpICar interface instantiation.

  Args:     COCruiseCar* pBackObj,
              Back pointer to the parent outer object.
            IUnknown* pUnkOuter,
              Pointer to the outer Unknown.  For delegation.

  Modifies: m_cRefI, m_pBackObj, m_pUnkOuter.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COCruiseCar::CImpICar::CImpICar(
  COCruiseCar* pBackObj,
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
    LOGF1("L<%X>: COCruiseCar::CImpICar Constructor. Non-Aggregating",TID);
  }
  else
  {
    m_pUnkOuter = pUnkOuter;
    LOGF1("L<%X>: COCruiseCar::CImpICar Constructor. Aggregating",TID);
  }

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCruiseCar::CImpICar::~CImpICar

  Summary:  Destructor for the CImpICar interface instantiation.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COCruiseCar::CImpICar::~CImpICar(void)
{
  LOGF1("L<%X>: COCruiseCar::CImpICar Destructor.",TID);

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCruiseCar::CImpICar::QueryInterface

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
STDMETHODIMP COCruiseCar::CImpICar::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  LOGF1("L<%X>: COCruiseCar::CImpICar::QueryInterface. Delegating.",TID);

  // Delegate this call to the outer object's QueryInterface.
  return m_pUnkOuter->QueryInterface(riid, ppv);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCruiseCar::CImpICar::AddRef

  Summary:  The AddRef IUnknown member of this ICar interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: m_cRefI.

  Returns:  ULONG
              Returned by the delegated outer AddRef call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COCruiseCar::CImpICar::AddRef(void)
{
  // Increment the Interface Reference Count.
  ++m_cRefI;

  LOGF2("L<%X>: COCruiseCar::CImpICar::Addref. Delegating. New cI=%i.",TID,m_cRefI);

  // Delegate this call to the outer object's AddRef.
  return m_pUnkOuter->AddRef();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCruiseCar::CImpICar::Release

  Summary:  The Release IUnknown member of this ICar interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: m_cRefI.

  Returns:  ULONG
              Returned by the delegated outer Release call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COCruiseCar::CImpICar::Release(void)
{
  // Decrement the Interface Reference Count.
  --m_cRefI;

  LOGF2("L<%X>: COCruiseCar::CImpICar::Release. Delegating. New cI=%i.",TID,m_cRefI);

  // Delegate this call to the outer object's Release.
  return m_pUnkOuter->Release();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCruiseCar::CImpICar::Shift

  Summary:  The Shift member method of this ICar interface implementation.
            A simple empty method on a COCruiseCar COM object for tutorial
            purposes.  Presumably if this Car object were modeling
            a real Car then the Shift method would shift to the specified
            gear.

  Args:     short nGear
              0 - Neutral; 1 - 5 First 5 forward gears; 6 - Reverse.

  Modifies: .

  Returns:  HRESULT
              NOERROR
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COCruiseCar::CImpICar::Shift(
               short nGear)
{
  LOGF2("L<%X>: COCruiseCar::CImpICar::Shift. Delegating. nGear=%i.",TID,nGear);

  // Delegate to the contained object implementation of ICar.
  m_pBackObj->m_pICar->Shift(nGear);

  return NOERROR;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCruiseCar::CImpICar::Clutch

  Summary:  The Clutch member method of this ICar interface implementation.
            A simple empty method on a COCruiseCar COM object for tutorial
            purposes.  Presumably if this Car object were modeling
            a real Car then the Clutch method would engage the clutch the
            specified amount.

  Args:     short nEngaged)
              Percent clutch is engaged (0 to 100%).

  Modifies: .

  Returns:  HRESULT
              NOERROR
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COCruiseCar::CImpICar::Clutch(
               short nEngaged)
{
  LOGF2("L<%X>: COCruiseCar::CImpICar::Clutch. Delegating. nEngaged=%i.",TID,nEngaged);

  // Delegate to the contained object implementation of ICar.
  m_pBackObj->m_pICar->Clutch(nEngaged);

  return NOERROR;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCruiseCar::CImpICar::Speed

  Summary:  The Propel member method of this ICar interface implementation.
            A simple empty method on a COCruiseCar COM object for tutorial
            purposes.  Presumably if this Car object were modeling
            a real Car then this method would accelerate/brake to bring
            the car to the specified speed.

  Args:     short nMph
              New speed in miles per hour.

  Modifies: .

  Returns:  HRESULT
              NOERROR
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COCruiseCar::CImpICar::Speed(
               short nMph)
{
  LOGF2("L<%X>: COCruiseCar::CImpICar::Speed. Delegating. nMph=%i.",TID,nMph);

  // Delegate to the contained object implementation of ICar.
  m_pBackObj->m_pICar->Speed(nMph);

  return NOERROR;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCruiseCar::CImpICar::Steer

  Summary:  The Steer member method of this ICar interface implementation.
            A simple empty method on a COCruiseCar COM object for tutorial
            purposes.  Presumably if this Car object were modeling
            a real Car then the Steer method would set the steering
            angle of the Car.

  Args:     short nAngle)
              0 degrees straight ahead, -45 Full left, +45 Full right.

  Modifies: .

  Returns:  HRESULT
              NOERROR
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COCruiseCar::CImpICar::Steer(
               short nAngle)
{
  LOGF2("L<%X>: COCruiseCar::CImpICar::Steer. Delegating. nAngle=%i.",TID,nAngle);

  // Delegate to the contained object implementation of ICar.
  m_pBackObj->m_pICar->Steer(nAngle);

  return NOERROR;
}


/*---------------------------------------------------------------------------
  COCruiseCar's nested implementation of the ICruise interface including
  Constructor, Destructor, QueryInterface, AddRef, Release,
  Engage, and Adjust.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCruiseCar::CImpICruise::CImpICruise

  Summary:  Constructor for the CImpICruise interface instantiation.

  Args:     COCruiseCar* pBackObj,
              Back pointer to the parent outer object.
            IUnknown* pUnkOuter)
              Pointer to the outer Unknown.  For delegation.

  Modifies: m_cRefI, m_pBackObj, m_pUnkOuter.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COCruiseCar::CImpICruise::CImpICruise(
  COCruiseCar* pBackObj,
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
    LOGF1("L<%X>: COCruiseCar::CImpICruise Constructor. Non-Aggregating.",TID);
  }
  else
  {
    m_pUnkOuter = pUnkOuter;
    LOGF1("L<%X>: COCruiseCar::CImpICruise Constructor. Aggregating.",TID);
  }

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCruiseCar::CImpICruise::~CImpICruise

  Summary:  Destructor for the CImpICruise interface instantiation.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COCruiseCar::CImpICruise::~CImpICruise(void)
{
  LOGF1("L<%X>: COCruiseCar::CImpICruise Destructor.",TID);

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCruiseCar::CImpICruise::QueryInterface

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
STDMETHODIMP COCruiseCar::CImpICruise::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  LOGF1("L<%X>: COCruiseCar::CImpICruise::QueryInterface. Delegating.",TID);

  // Delegate this call to the outer object's QueryInterface.
  return m_pUnkOuter->QueryInterface(riid, ppv);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCruiseCar::CImpICruise::AddRef

  Summary:  The AddRef IUnknown member of this ICruise interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: m_cRefI.

  Returns:  ULONG
              Returned by the delegated outer AddRef call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COCruiseCar::CImpICruise::AddRef(void)
{
  // Increment the Interface Reference Count.
  ++m_cRefI;

  LOGF2("L<%X>: COCruiseCar::CImpICruise::Addref. Delegating. New cI=%i.",TID,m_cRefI);

  // Delegate this call to the outer object's AddRef.
  return m_pUnkOuter->AddRef();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCruiseCar::CImpICruise::Release

  Summary:  The Release IUnknown member of this ICruise interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: m_cRefI.

  Returns:  ULONG
              Returned by the delegated outer Release call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COCruiseCar::CImpICruise::Release(void)
{
  // Decrement the Interface Reference Count.
  --m_cRefI;

  LOGF2("L<%X>: COCruiseCar::CImpICruise::Release. Delegating. New cI=%i.",TID,m_cRefI);

  // Delegate this call to the outer object's Release.
  return m_pUnkOuter->Release();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCruiseCar::CImpICruise::Engage

  Summary:  The Engage member method of this ICruise interface
            implementation.  A simple empty method on a COCruiseCar COM
            object for tutorial purposes.  Presumably if this Car object
            were modeling a real Car then the Engage method would turn
            the Cruise control system on or off.

  Args:     BOOL bOnOff)
              TRUE for On; FALSE for Off.

  Modifies: .

  Returns:  HRESULT
              NOERROR
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COCruiseCar::CImpICruise::Engage(
               BOOL bOnOff)
{
  LOGF2("L<%X>: COCruiseCar::CImpICruise::Engage. Called. bOnOff=%i.",TID,bOnOff);

  return NOERROR;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCruiseCar::CImpICruise::Adjust

  Summary:  The Adjust member method of this ICruise interface
            implementation.  A simple empty method on a COCruiseCar COM
            object for tutorial purposes.  Presumably if this Car object
            were modeling a real Car then the Adjust method would allow
            notching the cruise set speed up or down by increments of 3 mph.

  Args:     BOOL bUpDown)
              TRUE for Up; FALSE for Down.

  Modifies: .

  Returns:  HRESULT
              NOERROR
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COCruiseCar::CImpICruise::Adjust(
               BOOL bUpDown)
{
  LOGF2("L<%X>: COCruiseCar::CImpICruise::Adjust. Called. bUpDown=%i.",TID,bUpDown);

  return NOERROR;
}
